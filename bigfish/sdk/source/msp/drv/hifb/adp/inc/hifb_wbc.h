/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : hifb_wbc.h
Version             : Initial Draft
Author              : 
Created             : 2015/06/15
Description         : ��д����
Function List       : 
History             :
Date                       Author                   Modification
2015/06/15                y00181162                Created file        
******************************************************************************/

#ifndef __HIFB_WBC_H__
#define __HIFB_WBC_H__


/*********************************add include here******************************/
#include "optm_hal.h"
#include "optm_hifb.h"
#include "optm_alg_csc.h"
#include "optm_alg_gzme.h"
#include "optm_alg_gsharp.h"
#include "hi_drv_disp.h"

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/
/**
 **ʹ�õĻ�дbuffer����LOGOֻ��Ҫһ��Ϳ����ˣ���Ϊֻ��дһ��
 **/
#ifndef HI_BUILD_IN_BOOT
	#define OPTM_WBCBUFFER_NUM               2
#else
	#define OPTM_WBCBUFFER_NUM               1
#endif
	
/*************************** Structure Definition ****************************/
typedef enum tagOPTM_WBC_MODE_E{
    OPTM_WBC_MODE_MONO      = 0x0,
    OPTM_WBC_MODE_LFET_EYE  = 0x2,
    OPTM_WBC_MODE_RIGHT_EYE = 0x3,
    OPTM_WBC_MODE_BUTT,
}OPTM_WBC_MODE_E;

typedef struct tagOPTM_GFX_WBC_S{
    HI_BOOL                bOpened;
    HI_BOOL                bEnable;
	HI_BOOL				   bWorking;
    OPTM_VDP_LAYER_WBC_E   enWbcHalId;
    /* setting */
    HI_S32                 s32BufferWidth;
    HI_S32                 s32BufferHeight;
    HI_U32                 u32BufferStride;
    HI_U32                 u32BufIndex;
    HI_S32                 s32WbcCnt;
    HI_U32                 u32WBCBuffer[OPTM_WBCBUFFER_NUM];
    HI_U32                 u32WriteBufAddr;
    HI_U32                 u32ReadBufAddr;
    MMZ_BUFFER_S           stFrameBuffer;
    HI_U32                 u32DataPoint;  /* 0, feeder; others, reserve */
    HIFB_COLOR_FMT_E       enDataFmt;
    HIFB_RECT              stInRect;
    HI_BOOL                bInProgressive;
    HIFB_RECT              stOutRect;
    HI_BOOL                bOutProgressive;
    HI_U32                 u32BtmOffset;
    HI_BOOL                bHdDispProgressive;
    OPTM_VDP_DITHER_E      enDitherMode;
    OPTM_VDP_WBC_OFMT_E    stWBCFmt;
    OPTM_VDP_DATA_RMODE_E  enReadMode;
    OPTM_VDP_DATA_RMODE_E  enOutMode;
    OPTM_WBC_MODE_E        enWbcMode;
    OPTM_VDP_INTMSK_E      enWbcInt;
}OPTM_GFX_WBC_S;


#ifndef HI_BUILD_IN_BOOT
	typedef struct tagOPTM_GFX_WORK_S
	{
	    HI_U32                   u32Data;
	    struct work_struct       work;
	}OPTM_GFX_WORK_S;
#endif

/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/


#ifndef HI_BUILD_IN_BOOT
/***************************************************************************************
* func          : HIFB_WBC2_WorkQueue
* description   : CNcomment: ͬԴ��д�������� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_WorkQueue(struct work_struct *data);
#endif


/***************************************************************************************
* func          : HIFB_WBC2_SetTcFlag
* description   : CNcomment: ����TC��д��� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_SetTcFlag(HI_BOOL bFlag);

/***************************************************************************************
* func          : HIFB_WBC2_SetCropReso
* description   : CNcomment: ����WBC_GP0�ü��ֱ��ʣ�Ҳ���������ʼ�ͽ������� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_SetCropReso(OPTM_VDP_DISP_RECT_S stInputRect);

/***************************************************************************************
* func          : HIFB_WBC2_SetPreZmeEn
* description   : CNcomment: ����ZMEʹ�� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_SetPreZmeEn(OPTM_ALG_GZME_DRV_PARA_S *pstZmeDrvPara);

/***************************************************************************************
* func          : HIFB_WBC2_Open
* description   : CNcomment: �򿪻�д CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIFB_WBC2_Open(HI_VOID);


/***************************************************************************************
* func          : HIFB_WBC2_Close
* description   : CNcomment: �رջ�д�豸 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_Close(HI_VOID);

/***************************************************************************************
* func          : HIFB_WBC2_Init
* description   : wbc initial
                  CNcomment: ��д��ʼ�� CNend\n
* param[in]     : 
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_Init(HI_VOID);

/***************************************************************************************
* func          : HIFB_WBC2_Dinit
* description   : wbc initial
                  CNcomment: ��дȥ��ʼ�� CNend\n
* param[in]     : 
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID HIFB_WBC2_Dinit(HI_VOID);


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __HIFB_WBC_H__ */
