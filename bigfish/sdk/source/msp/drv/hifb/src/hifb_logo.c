/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : hifb_logo.c
Version             : Initial Draft
Author              : 
Created             : 2014/09/09
Description         : 
Function List       : 
History             :
Date                       Author                   Modification
2015/05/19                 y00181162                Created file        
******************************************************************************/

#ifdef CFG_HIFB_LOGO_SUPPORT

/*********************************add include here******************************/

#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/time.h>
#include <linux/fb.h>
#include <asm/uaccess.h>
#include <linux/file.h>
#include <asm/types.h>
#include <asm/stat.h>
#include <asm/fcntl.h>

#include "hifb_drv.h"
#include "hifb_comm.h"
#include "hifb_logo.h"
#include "hifb_p.h"

#include "drv_pdm_ext.h"

/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/
static HIFB_LOGO_S gs_stLogo;


/******************************* API declaration *****************************/


/***************************************************************************************
* func          : hifb_convertbootfmt2fbfmt
* description   : CNcomment: ��boot�����ظ�ʽת��HiFB�����ظ�ʽ CNend\n
* param[in]     : enBootFmt
* retval        : NA
* others:       : NA
***************************************************************************************/
static HIFB_COLOR_FMT_E hifb_convertbootfmt2fbfmt(HI_U32 enBootFmt)
{
	switch(enBootFmt){
		case HIFB_BOOT_FMT_1555:
			return HIFB_FMT_ARGB1555;
		case HIFB_BOOT_FMT_8888:
			return HIFB_FMT_ARGB8888;
		default:
			return HIFB_FMT_BUTT;        
	}
}
/***************************************************************************************
* func          : hifb_convertlogochn2dispchn
* description   : CNcomment: ��logoͨ��ת��dispͨ�� CNend\n
* param[in]     : enLogoChn
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_UNF_DISP_E hifb_convertlogochn2dispchn(HIFB_LOGO_CHANNEL_E enLogoChn)
{
	if (enLogoChn >= HIFB_LOGO_CHN_BUTT){
		return HI_UNF_DISPLAY_BUTT;
	}
	
	switch(enLogoChn){
		case HIFB_LOGO_CHN_HD:
			return HI_UNF_DISPLAY1;
		case HIFB_LOGO_CHN_SD:
			return HI_UNF_DISPLAY0;
		default:
			return HI_UNF_DISPLAY_BUTT;        
	}
}


/***************************************************************************************
* func          : hifb_freelogomem
* description   : free logo mem CNcomment
                             CNcomment: ��logo�ڴ棬ж��������ʱ����� CNend\n
* param[in]     : enLogoChn  CNcomment: Logoʹ�õ�ͨ�� CNend\n
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID hifb_freelogomem(HIFB_LOGO_CHANNEL_E enLogoChn)
{

    PDM_EXPORT_FUNC_S *ps_PdmExportFuncs = HI_NULL;

    if (HI_SUCCESS != HI_DRV_MODULE_GetFunction(HI_ID_PDM, (HI_VOID**)&ps_PdmExportFuncs)){
        return;
    }

    if(HI_NULL == ps_PdmExportFuncs){
        return;
    }

	/**
	 ** msleep 80ms to asure wbc closed or screen addr switched
	 ** max time or each fps is 1000 / 24 = 42ms
	 **/
	msleep(80);
	
    if (HIFB_LOGO_CHN_HD == enLogoChn){
		#if !defined(CONFIG_PM_HIBERNATE) && !defined(CONFIG_HISI_SNAPSHOT_BOOT)
        	ps_PdmExportFuncs->pfnPDM_ReleaseReserveMem(DISPLAY_BUFFER_HD);
        	ps_PdmExportFuncs->pfnPDM_ReleaseReserveMem(OPTM_GFX_WBC2_BUFFER);
		#endif
        HIFB_INFO("<<<<<<<<freen mem %s>>>>>>>>>\n", DISPLAY_BUFFER_HD);
        HIFB_INFO("<<<<<<<<freen mem %s>>>>>>>>>\n", OPTM_GFX_WBC2_BUFFER);
    }else{
		#if !defined(CONFIG_PM_HIBERNATE) && !defined(CONFIG_HISI_SNAPSHOT_BOOT)
        	ps_PdmExportFuncs->pfnPDM_ReleaseReserveMem(DISPLAY_BUFFER_SD);
		#endif
        HIFB_INFO("<<<<<<<<freen mem %s>>>>>>>>>\n", DISPLAY_BUFFER_SD);
    }

    if (0 == gs_stLogo.u32LogoNum){
		#if !defined(CONFIG_PM_HIBERNATE) && !defined(CONFIG_HISI_SNAPSHOT_BOOT)
        	ps_PdmExportFuncs->pfnPDM_ReleaseReserveMem(HIFB_ZME_COEF_BUFFER);
		#endif
        HIFB_INFO("<<<<<<<<freen mem %s>>>>>>>>>\n", HIFB_ZME_COEF_BUFFER);
    }

    return;
}


/***************************************************************************************
* func          : hifb_freelogomem_work
* description   : free logo mem CNcomment
                             CNcomment: ��logo�ڴ棬����logo���ɵ�ʱ����� CNend\n
* param[in]     : enLogoChn  CNcomment: �������� CNend\n
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID hifb_freelogomem_work(struct work_struct *work)
{
	HIFB_LOGO_INFO_S *pstLogoInfo  = NULL;
	HIFB_LOGO_CHANNEL_E enLogoChn  = HIFB_LOGO_CHN_BUTT;

	pstLogoInfo = (HIFB_LOGO_INFO_S *)container_of(work, HIFB_LOGO_INFO_S, freeLogoMemWork); 

	if (IS_HD_LAYER(pstLogoInfo->enLogoID) || IS_MINOR_HD_LAYER(pstLogoInfo->enLogoID)){
		enLogoChn = HIFB_LOGO_CHN_HD;
	}else{
		enLogoChn = HIFB_LOGO_CHN_SD;
	}	

	hifb_freelogomem(enLogoChn);
	
    return;
}


/***************************************************************************************
* func          : hifb_logo_init
* description   : CNcomment: logo��ʼ��������ֻ������һ������Ͷ�Ӧ��ͼ��򿪱�� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID hifb_logo_init(HI_VOID)
{

	HIFB_LOGO_CHANNEL_E enLogoChn     = HIFB_LOGO_CHN_BUTT;
    HIFB_OSD_DATA_S pstLogoLayerData; 

	gs_stLogo.u32LogoNum = 0;
	
	/**
	 ** ���������ȥ��ʼ��logo�еĴ������е�����
	 ** ����ͨ��������ͨ��������ͨ����������TC˫����
	 **/
	for (enLogoChn = 0; enLogoChn < HIFB_LOGO_CHN_BUTT; enLogoChn++){
		/**
		 **98M��HD1��SD0��Ϊ����logo
		 **/
		gs_stLogo.stLogoInfo[enLogoChn].enLogoID = (HIFB_LOGO_CHN_HD == enLogoChn) ? HIFB_HD_LOGO_LAYER_ID : HIFB_SD_LOGO_LAYER_ID;		
		/**
		 ** judge whether has logo
		 ** ����ֻ���ȡͼ���Ƿ�ʹ��
		 **/
		s_stDrvOps.HIFB_DRV_GetOSDData(gs_stLogo.stLogoInfo[enLogoChn].enLogoID, &pstLogoLayerData);
	
		if (pstLogoLayerData.eState == HIFB_LAYER_STATE_ENABLE){
			/** ֻ�����п���logo������²��ܽ��� **/
	    	gs_stLogo.u32LogoNum++;
	        gs_stLogo.stLogoInfo[enLogoChn].bShow = HI_TRUE;
			/** ����logoû�й����� **/
	        s_stDrvOps.HIFB_DRV_SetLayerMaskFlag(gs_stLogo.stLogoInfo[enLogoChn].enLogoID, HI_TRUE);
			HIFB_INFO("<<<<<<<<<<<<<start with boot logo, ID:%d>>>>>>>>>>>>>>>\n", gs_stLogo.stLogoInfo[enLogoChn].enLogoID);
	    }

	}
}


/***************************************************************************************
* func          : hifb_clear_logo
* description   : clear logo   CNcomment: ��logo CNend\n
* param[in]     : u32LayerID
* param[in]     : bModExit
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID hifb_clear_logo(HI_U32 u32LayerID, HI_BOOL bModExit)
{

	HIFB_LAYER_ID_E enLogoLayerId;
	HIFB_LOGO_CHANNEL_E enLogoChn;
	
	if (IS_HD_LAYER(u32LayerID) || IS_MINOR_HD_LAYER(u32LayerID)){
		enLogoChn = HIFB_LOGO_CHN_HD;
	}else{
		enLogoChn = HIFB_LOGO_CHN_SD;
	}

	if (!gs_stLogo.stLogoInfo[enLogoChn].bShow){
	/** û�п���logo����Ҫ������ֻ֤����һ��gs_stLogo.u32LogoNum = 1������**/
		return;
	}
	
	/** ������G1 **/
	enLogoLayerId = gs_stLogo.stLogoInfo[enLogoChn].enLogoID;
	/** ����������л���ʾ��ַ�� **/
    s_stDrvOps.HIFB_DRV_SetLayerMaskFlag(enLogoLayerId, HI_FALSE);
    s_stDrvOps.HIFB_DRV_ClearLogo(enLogoLayerId);
    s_stDrvOps.HIFB_DRV_UpdataLayerReg(enLogoLayerId);

    /**
     ** wait for logo closed ,so we can free logo buffer
     **/
    if (bModExit){
		hifb_freelogomem(enLogoChn);
	}else{
		INIT_WORK(&(gs_stLogo.stLogoInfo[enLogoChn].freeLogoMemWork), hifb_freelogomem_work);
    	schedule_work(&(gs_stLogo.stLogoInfo[enLogoChn].freeLogoMemWork));    
	}
	
    gs_stLogo.stLogoInfo[enLogoChn].bShow       = HI_FALSE;

    HIFB_INFO("<<<<<<<<<<<<<hifb_clear_logo>>>>>>>>>>>>>>>\n");
}

/***************************************************************************************
* func          : hifb_set_logosd
* description   : set logo sd 
                               CNcomment: ����logo������Ϣ CNend\n
* param[in]     : u32LayerID   CNcomment: layer id     CNend\n
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 hifb_set_logosd(HI_U32 u32LayerID)
{

	HI_S32 s32Ret        = HI_SUCCESS;     	
    HIFB_PAR_S *par      = NULL;
	struct fb_info *info = NULL;
	HIFB_LOGO_CHANNEL_E enLogoChn  = HIFB_LOGO_CHN_BUTT;
	HIFB_RECT         stInRect     = {0};
	HIFB_COLOR_FMT_E  enHifbFmt    = HIFB_FMT_BUTT;
	PDM_EXPORT_FUNC_S *pstPdmFuncs = NULL;	
    HI_DISP_PARAM_S   stDispParam;
    
	info   = s_stLayer[u32LayerID].pstInfo;
	par    = (HIFB_PAR_S *)(info->par);	

	if (IS_HD_LAYER(u32LayerID) || IS_MINOR_HD_LAYER(u32LayerID)){
		enLogoChn = HIFB_LOGO_CHN_HD;
	}else if(IS_SD_LAYER(u32LayerID) || IS_MINOR_SD_LAYER(u32LayerID)){
		enLogoChn = HIFB_LOGO_CHN_SD;
	}else{
		return HI_SUCCESS;
	}

#if 0
	if (!gs_stLogo.stLogoInfo[enLogoChn].bShow){
	/** û�п���logo��**/
		return HI_SUCCESS;
	}
#endif
	
    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_PDM, (HI_VOID**)&pstPdmFuncs);
    if(    HI_FAILURE == s32Ret
		|| NULL == pstPdmFuncs
		|| NULL == pstPdmFuncs->pfnPDM_GetDispParam){
        HIFB_WARNING("get pdm module function failed\r\n");
		s32Ret = HI_FAILURE;
		goto FINISHED;
    }
    
	s32Ret = pstPdmFuncs->pfnPDM_GetDispParam(hifb_convertlogochn2dispchn(enLogoChn), &stDispParam);
	if (s32Ret == HI_FAILURE){
    /** û�п���logo������������û�в����ˣ�ֱ���˳� **/
        HIFB_WARNING("PDM_GetDispParam failed\r\n");
		goto FINISHED;
    }

	if (   stDispParam.u32VirtScreenWidth == 0
		|| stDispParam.u32VirtScreenHeight == 0){
		s32Ret = HI_FAILURE;
		goto FINISHED;
	}
	
	enHifbFmt = hifb_convertbootfmt2fbfmt((HI_U32)stDispParam.enPixelFormat);
	if (enHifbFmt >= HIFB_FMT_PUYVY){
		s32Ret = HI_FAILURE;
		goto FINISHED;
	}

	info->var.bits_per_pixel = hifb_getbppbyfmt(enHifbFmt);
	if (info->var.bits_per_pixel == 0){
		HIFB_WARNING("unsupported fmt received from boot!\n");
		s32Ret = HI_FAILURE;
		goto FINISHED;
	}	

	info->var.red    = s_stArgbBitField[enHifbFmt].stRed;
    info->var.green  = s_stArgbBitField[enHifbFmt].stGreen;
    info->var.blue   = s_stArgbBitField[enHifbFmt].stBlue;
    info->var.transp = s_stArgbBitField[enHifbFmt].stTransp;

	info->var.xres = stDispParam.u32VirtScreenWidth;
	info->var.yres = stDispParam.u32VirtScreenHeight;
	info->var.xres_virtual = info->var.xres;
	info->var.yres_virtual = info->var.yres;
	info->fix.line_length  = ((((info->var.xres_virtual * info->var.bits_per_pixel) >> 3) + 0xf) & 0xfffffff0);

    par->stExtendInfo.enColFmt         = enHifbFmt;
	par->stExtendInfo.stPos.s32XPos    = 0;
	par->stExtendInfo.stPos.s32YPos    = 0;
	par->stExtendInfo.u32DisplayWidth  = info->var.xres;
	par->stExtendInfo.u32DisplayHeight = info->var.yres;

	stInRect.x = par->stExtendInfo.stPos.s32XPos;
	stInRect.y = par->stExtendInfo.stPos.s32YPos;
	stInRect.w = par->stExtendInfo.u32DisplayWidth;
	stInRect.h = par->stExtendInfo.u32DisplayHeight;

	/**
	 ** ���µļ�������
	 **/
    s_stDrvOps.HIFB_DRV_SetLayerInRect (u32LayerID, &stInRect);
	s_stDrvOps.HIFB_DRV_SetLayerStride (u32LayerID, info->fix.line_length);
	s_stDrvOps.HIFB_DRV_SetLayerDataFmt(u32LayerID, par->stExtendInfo.enColFmt);

	HIFB_INFO("<<<<<<<<<<<<<get logo data width %d, height %d>>>>>>>>>>>>>>>>>\n", info->var.xres, info->var.yres);	

	s32Ret = HI_SUCCESS;
	
FINISHED:
	return s32Ret;

}

#endif
