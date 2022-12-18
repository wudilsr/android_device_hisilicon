/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : hifb_wbc.c
Version             : Initial Draft
Author              : 
Created             : 2015/06/15
Description         : 回写处理
Function List       : 
History             :
Date                       Author                   Modification
2015/06/15                y00181162                Created file        
******************************************************************************/


/*********************************add include here******************************/
#ifndef HI_BUILD_IN_BOOT
	#include <linux/string.h>
	#include <linux/fb.h>
	#include <linux/time.h>
	#include <linux/version.h>
	#include <linux/module.h>
	#include <linux/types.h>
	#include <linux/errno.h>
	#include <linux/fcntl.h>
	#include <linux/mm.h>
	#include <linux/miscdevice.h>
	#include <linux/proc_fs.h>
	#include <linux/fs.h>
	#include <linux/slab.h>
	#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36))
		#include <linux/smp_lock.h>
	#endif
	#include <linux/init.h>
	#include <linux/delay.h>
	#include <asm/uaccess.h>
	#include <asm/io.h>
	#include <asm/system.h>
	#include <linux/interrupt.h>
	#include <linux/ioport.h>
	#include <linux/string.h>
	#include <linux/workqueue.h>

	#include "hi_module.h"
	#include "hi_drv_module.h"
	#include "drv_disp_ext.h"
#else
	#include "drv_display.h"
	#include "hifb_debug.h"
	#ifndef HI_PQ_V1_0
		#include "hi_drv_pq.h"
	#endif
#endif


#include "hifb_wbc.h"
#include "hifb_config.h"

/***************************** Macro Definition ******************************/
#define OPTM_GFX_WBC_WIDTH              (gs_bTcWbc2Flag? 1920 : 720)
#define OPTM_GFX_WBC_HEIGHT             (gs_bTcWbc2Flag? 1200 : 576)
#define OPTM_GFXDATA_DEFAULTBYTES       4

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/
OPTM_GFX_WBC_S  g_stGfxWbc2;
static HI_BOOL  gs_bTcWbc2Flag = HI_FALSE;

/******************************* API declaration *****************************/


/***************************************************************************************
* func          : HIFB_WBC2_WorkQueue
* description   : CNcomment: 同源回写工作对列 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
#ifndef HI_BUILD_IN_BOOT

HI_VOID HIFB_WBC2_WorkQueue(struct work_struct *data)
{
    HIFB_LAYER_ID_E u32LayerID = HIFB_LAYER_ID_BUTT;
    OPTM_GFX_WORK_S *pstOpenSlvWork = container_of(data, OPTM_GFX_WORK_S, work);
    u32LayerID = (HIFB_LAYER_ID_E)(pstOpenSlvWork->u32Data);
    HIFB_WBC2_OpenSlvLayer(u32LayerID);
}

#endif


/***************************************************************************************
* func          : HIFB_WBC2_SetTcFlag
* description   : CNcomment: 设置TC回写标记 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_SetTcFlag(HI_BOOL bFlag)
{
	gs_bTcWbc2Flag = bFlag;
}


/***************************************************************************************
* func          : HIFB_WBC2_SetCropReso
* description   : CNcomment: 设置WBC_GP0裁剪分辨率，也就输入的起始和结束坐标 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_SetCropReso(OPTM_VDP_DISP_RECT_S stInputRect)
{
	OPTM_VDP_DISP_RECT_S stWbcRect = {0};

	stWbcRect.u32DXL = stInputRect.u32IWth;
    stWbcRect.u32DYL = stInputRect.u32IHgt;

    #ifdef GFX_CONFIG_WBC_GP0_PRE_ZME_EN
		/**
	 	 **预缩放的输出
	 	 **/
		if( (stWbcRect.u32DXL >= 3840) && (stWbcRect.u32DYL >= 2160)){
			stWbcRect.u32DXL /= 2;
		}
	#endif
	
    OPTM_VDP_WBC_SetCropReso (g_stGfxWbc2.enWbcHalId, stWbcRect);
	
}

/***************************************************************************************
* func          : HIFB_WBC2_SetPreZmeEn
* description   : CNcomment: 设置ZME使能 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_SetPreZmeEn(OPTM_ALG_GZME_DRV_PARA_S *pstZmeDrvPara)
{
#ifdef GFX_CONFIG_WBC_GP0_PRE_ZME_EN
	 if( (pstZmeDrvPara->u32ZmeFrmWIn >= 3840) && (pstZmeDrvPara->u32ZmeFrmHIn >= 2160)){
		pstZmeDrvPara->u32ZmeFrmWIn = pstZmeDrvPara->u32ZmeFrmWIn / 2;
	    OPTM_VDP_WBC_SetPreZmeEnable(OPTM_VDP_LAYER_WBC_GP0,HI_TRUE);
	  }else{
		OPTM_VDP_WBC_SetPreZmeEnable(OPTM_VDP_LAYER_WBC_GP0,HI_FALSE);
	  }
#endif
}

/***************************************************************************************
* func          : HIFB_WBC2_Open
* description   : CNcomment: 打开回写 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIFB_WBC2_Open(HI_VOID)
{

	HI_S32 s32WbcSzie = 0;
	
    if (HI_TRUE == g_stGfxWbc2.bOpened){
    /** 已经打开了就不需要再打开了 **/
        return HI_SUCCESS;
    }

	g_stGfxWbc2.u32BufIndex     = 0;
    g_stGfxWbc2.s32BufferWidth  = OPTM_GFX_WBC_WIDTH;
    g_stGfxWbc2.s32BufferHeight = OPTM_GFX_WBC_HEIGHT;
    g_stGfxWbc2.u32BufferStride = g_stGfxWbc2.s32BufferWidth * OPTM_GFXDATA_DEFAULTBYTES;
    s32WbcSzie = g_stGfxWbc2.u32BufferStride * g_stGfxWbc2.s32BufferHeight * OPTM_WBCBUFFER_NUM;
    
    if(g_stGfxWbc2.stFrameBuffer.u32StartVirAddr == 0){
        if (OPTM_AllocAndMap(OPTM_GFX_WBC2_BUFFER,    \
			                 HI_NULL,                 \
                             s32WbcSzie,              \
                             0,                       \
                             &(g_stGfxWbc2.stFrameBuffer)) != 0){
            HIFB_ERROR("GFX Get wbc2 buffer failed!\n");
            return HI_FAILURE;
        }
    }

    if (1 == OPTM_WBCBUFFER_NUM){
        g_stGfxWbc2.u32WBCBuffer[0] = g_stGfxWbc2.stFrameBuffer.u32StartPhyAddr;
        g_stGfxWbc2.u32WriteBufAddr = g_stGfxWbc2.u32WBCBuffer[0];
        g_stGfxWbc2.u32ReadBufAddr  = g_stGfxWbc2.u32WBCBuffer[0];
    }else if (2 == OPTM_WBCBUFFER_NUM){
        g_stGfxWbc2.u32WBCBuffer[0] = g_stGfxWbc2.stFrameBuffer.u32StartPhyAddr;
        g_stGfxWbc2.u32WBCBuffer[1] = g_stGfxWbc2.u32WBCBuffer[0] + g_stGfxWbc2.u32BufferStride * g_stGfxWbc2.s32BufferHeight;
		g_stGfxWbc2.u32WriteBufAddr = g_stGfxWbc2.u32WBCBuffer[0];
        g_stGfxWbc2.u32ReadBufAddr  = g_stGfxWbc2.u32WBCBuffer[1];
    }else{
        HIFB_ERROR("Allocate wbc buffer failure!\n");
        return HI_FAILURE;
    }

#ifndef HI_BUILD_IN_BOOT
    memset((HI_U8 *)(g_stGfxWbc2.stFrameBuffer.u32StartVirAddr), 0, s32WbcSzie);
#endif

    g_stGfxWbc2.bEnable      = HI_FALSE;  /** 这个变量没有用到,只有在这里赋值 **/
    g_stGfxWbc2.enWbcHalId   = OPTM_VDP_LAYER_WBC_GP0;
    g_stGfxWbc2.u32DataPoint = 0;
    g_stGfxWbc2.enDataFmt    = HIFB_FMT_AYUV8888;
    g_stGfxWbc2.enDitherMode = VDP_DITHER_TMP_SPA_8;
    g_stGfxWbc2.stWBCFmt     = VDP_WBC_OFMT_ARGB8888;
    g_stGfxWbc2.enReadMode   = VDP_RMODE_SELF_ADAPTION;
	/**
	 ** 输出用逐行更新，否则会突然出现标清回写没有数据
	 ** 要不然隔行的时候回写要更新两次
	 **/
	g_stGfxWbc2.enOutMode    = VDP_RMODE_PROGRESSIVE;
    g_stGfxWbc2.enWbcMode    = OPTM_WBC_MODE_MONO;  
    g_stGfxWbc2.enWbcInt     = OPTM_VDP_INTMSK_WBC_GP0_INT;
	g_stGfxWbc2.bOpened      = HI_TRUE;
    g_stGfxWbc2.bWorking     = HI_FALSE;
    
    OPTM_VDP_WBC_SetThreeMd    (g_stGfxWbc2.enWbcHalId, g_stGfxWbc2.enWbcMode);
    OPTM_VDP_WBC_SetDitherMode (g_stGfxWbc2.enWbcHalId, g_stGfxWbc2.enDitherMode);
    OPTM_VDP_WBC_SetOutFmt     (g_stGfxWbc2.enWbcHalId, g_stGfxWbc2.stWBCFmt);
    OPTM_VDP_WBC_SetOutIntf    (g_stGfxWbc2.enWbcHalId, g_stGfxWbc2.enOutMode);

    return HI_SUCCESS;
}


/***************************************************************************************
* func          : HIFB_WBC2_Close
* description   : CNcomment: 关闭回写设备 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_Close(HI_VOID)
{
    if(HI_FALSE == g_stGfxWbc2.bOpened){
        return;
    }

    g_stGfxWbc2.bOpened = HI_FALSE;

    OPTM_VDP_WBC_SetEnable(g_stGfxWbc2.enWbcHalId, HI_FALSE);
    
    return;
}

/***************************************************************************************
* func          : HIFB_WBC2_Init
* description   : wbc initial
                  CNcomment: 回写初始化 CNend\n
* param[in]     : 
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_Init(HI_VOID)
{
	memset(&g_stGfxWbc2, 0, sizeof(OPTM_GFX_WBC_S));
}

/***************************************************************************************
* func          : HIFB_WBC2_Dinit
* description   : wbc initial
                  CNcomment: 回写去初始化 CNend\n
* param[in]     : 
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_Dinit(HI_VOID)
{
	if (g_stGfxWbc2.stFrameBuffer.u32StartVirAddr != 0){
        OPTM_UnmapAndRelease(&(g_stGfxWbc2.stFrameBuffer));
        g_stGfxWbc2.stFrameBuffer.u32StartVirAddr = 0;
        g_stGfxWbc2.stFrameBuffer.u32StartPhyAddr = 0;
    }
}
