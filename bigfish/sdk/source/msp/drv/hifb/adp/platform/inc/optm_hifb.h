/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : optm_hifb.h
Version             : Initial Draft
Author              : 
Created             : 2014/09/09
Description         : ALG��һ����������㷨�ṩ��
Function List       : 
History             :
Date                       Author                   Modification
2014/09/09                 y00181162                Created file        
******************************************************************************/

#ifndef __OPTM_HIFB_H__
#define __OPTM_HIFB_H__


/*********************************add include here******************************/
#ifndef HI_BUILD_IN_BOOT
#include "hi_type.h"
#include "hi_common.h"
#include "hifb_drv_common.h"
#else
#include "hifb_debug.h"
#endif


/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/

#ifdef HI_BUILD_IN_BOOT
	#ifdef HIGO_DEBUG
		#define HIFB_ERROR               printf
		#define HIFB_WARNING             printf
		#define HIFB_INFO(fmt...)
		#define HIFB_FATAL               printf
	#else
		#define HIFB_ERROR(fmt...)
		#define HIFB_WARNING(fmt...)
		#define HIFB_INFO(fmt...)
		#define HIFB_FATAL(fmt...)
	#endif
#endif


/*************************** Structure Definition ****************************/


typedef struct tagOPTM_GFX_CSC_PARA_S
{
	HI_U32               u32Bright;
    HI_U32               u32Contrast;
    HI_U32               u32Saturation;
    HI_U32               u32Hue;
    HI_U32               u32Kr;
    HI_U32               u32Kg;
    HI_U32               u32Kb;
}OPTM_GFX_CSC_PARA_S;

typedef enum tagOPTM_GFX_GP_E
{
	OPTM_GFX_GP_0 = 0x0,/** process gfx0,gfx1,gfx2,gfx3*/
	OPTM_GFX_GP_1,		/** process gfx4,gfx5                */
	OPTM_GFX_GP_BUTT
}OPTM_GFX_GP_E;

typedef struct tagOPTM_GFX_OFFSET_S
{
    HI_U32 u32Left;    /*left offset */
    HI_U32 u32Top;     /*top offset */
    HI_U32 u32Right;   /*right offset */
    HI_U32 u32Bottom;  /*bottom offset */
}OPTM_GFX_OFFSET_S;



/** csc state*/
typedef enum tagOPTM_CSC_STATE_E
{
    OPTM_CSC_SET_PARA_ENABLE = 0x0, 
    OPTM_CSC_SET_PARA_RGB,       
    OPTM_CSC_SET_PARA_BGR,
    OPTM_CSC_SET_PARA_CLUT,
    OPTM_CSC_SET_PARA_CbYCrY,
    OPTM_CSC_SET_PARA_YCbYCr,
    OPTM_CSC_SET_PARA_BUTT 
} OPTM_CSC_STATE_E;

typedef enum optm_COLOR_SPACE_E
{
    OPTM_CS_UNKNOWN = 0,
    
    OPTM_CS_BT601_YUV_LIMITED,/* BT.601 */
    OPTM_CS_BT601_YUV_FULL,
    OPTM_CS_BT601_RGB_LIMITED,
    OPTM_CS_BT601_RGB_FULL,    

    OPTM_CS_BT709_YUV_LIMITED,/* BT.709 */
    OPTM_CS_BT709_YUV_FULL,
    OPTM_CS_BT709_RGB_LIMITED,
    OPTM_CS_BT709_RGB_FULL,
    
    OPTM_CS_BUTT
} OPTM_COLOR_SPACE_E;



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
            initial operation
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
typedef struct
{
	/*gfx init*/
	/*CNcomment:ͼ�γ�ʼ��*/
	HI_S32 (*OPTM_GfxInit)(HI_VOID);

	/*gfx deinit*/
	/*CNcomment:ͼ��ȥ��ʼ��*/
	HI_S32 (*OPTM_GfxDeInit)(HI_VOID);

	/*open layer*/
	/*CNcomment:ͼ���*/
	HI_S32 (*OPTM_GfxOpenLayer)(HIFB_LAYER_ID_E enLayerId);

	/*close layer*/
	/*CNcomment:ͼ��ر�*/
	HI_S32 (*OPTM_GfxCloseLayer)(HIFB_LAYER_ID_E enLayerId);

	/*enable/disable layer*/
	/*CNcomment:ͼ��ʹ�ܻ��߷�ʹ��*/
	HI_S32 (*OPTM_GfxSetEnable)(HIFB_LAYER_ID_E enLayerId, HI_BOOL bEnable);

	/*mask layer*/
	/*CNcomment:�Ƿ�����ͼ��*/
	HI_S32 (*OPTM_GfxMaskLayer)(HIFB_LAYER_ID_E enLayerId, HI_BOOL bMask);

	/*set layer address*/
	/*CNcomment:����ͼ����ʾ��ַ*/
	HI_S32 (*OPTM_GfxSetLayerAddr)(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Addr);

	/*set layer stride*/
	/*CNcomment:����ͼ���о�*/
	HI_S32 (*OPTM_GfxSetLayerStride)(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Stride);

	/*set layer data format*/
	/*CNcomment:����ͼ�����ظ�ʽ*/
	HI_S32 (*OPTM_GfxSetLayerDataFmt)(HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt);

	HI_S32 (*OPTM_GfxSetColorReg)(HIFB_LAYER_ID_E u32LayerId, HI_U32 u32OffSet, HI_U32 u32Color, HI_S32 UpFlag);

	/*wait for vertical blank*/
	/*CNcomment:�ȴ���ֱ����*/
	HI_S32 (*OPTM_GfxWaitVBlank)(HIFB_LAYER_ID_E u32LayerId);

	/*set layer deflick level*/
	/*CNcomment:���ÿ�������*/
	HI_S32 (*OPTM_GfxSetLayerDeFlicker)(HIFB_LAYER_ID_E enLayerId, HIFB_DEFLICKER_S *pstDeFlicker);

	/*set layer alpha*/
	/*CNcomment:����ͼ��alpha ֵ*/
	HI_S32 (*OPTM_GfxSetLayerAlpha)(HIFB_LAYER_ID_E enLayerId, HIFB_ALPHA_S *pstAlpha);

	/*set layer rect*/
	/*CNcomment:����ͼ���������*/
	HI_S32 (*OPTM_GfxSetLayerRect)(HIFB_LAYER_ID_E enLayerId, const HIFB_RECT *pstRect);

	/*set graphics process device Inrect and Outrect*/
	/*CNcomment:����ͼ������������������*/
	HI_S32 (*OPTM_GfxSetGpRect)(OPTM_GFX_GP_E enGpId, const HIFB_RECT *pstInputRect);

	HI_S32 (*OPTM_GfxSetGpInPutSize)(OPTM_GFX_GP_E enGpId, HI_U32 u32Width, HI_U32 u32Height);

	/*set layer key mask*/
	/*CNcomment:����ͼ��colorkey mask*/
	HI_S32 (*OPTM_GfxSetLayKeyMask)(HIFB_LAYER_ID_E enLayerId, const HIFB_COLORKEYEX_S *pstColorkey);
#if 0
	/* set bit-extension mode */
	HI_S32 OPTM_GfxSetLayerBitExtMode(HIFB_LAYER_ID_E enLayerId, OPTM_GFX_BITEXTEND_E enBtMode);
#endif

	/*set layer pre mult*/
	/*CNcomment:����ͼ��Ԥ��*/
	HI_S32 (*OPTM_GfxSetLayerPreMult)(HIFB_LAYER_ID_E enLayerId, HI_BOOL bEnable);

	/*set clut address*/
	/*CNcomment:����CLUT ��ַ*/
	HI_S32 (*OPTM_GfxSetClutAddr)(HIFB_LAYER_ID_E enLayerId, HI_U32 u32PhyAddr);

	HI_VOID (*OPTM_GfxGetOSDData)(HIFB_LAYER_ID_E enLayerId, HIFB_OSD_DATA_S *pstLayerData);

	/*set call back*/
	/*CNcomment:ע��ص�����*/
#ifndef HI_BUILD_IN_BOOT	
	HI_S32 (*OPTM_GfxSetCallback)(HIFB_LAYER_ID_E enLayerId, IntCallBack pCallBack, HIFB_CALLBACK_TPYE_E eIntType);
#endif
	/*update layer register*/
	/*CNcomment:���¼Ĵ���*/
	HI_S32 (*OPTM_GfxUpLayerReg)(HIFB_LAYER_ID_E enLayerId);
#ifdef CFG_HIFB_STEREO3D_HW_SUPPORT
	/*enable/disable stereo*/
	/*CNcomment:����3D ʹ�ܻ��߷�ʹ��*/
	HI_S32 (*OPTM_GfxSetTriDimEnable)(HIFB_LAYER_ID_E enLayerId, HI_U32 bEnable);

	/*set stereo mode*/
	/*CNcomment:����3D ģʽSBS/TB/MVC*/
	HI_S32 (*OPTM_GfxSetTriDimMode)(HIFB_LAYER_ID_E enLayerId, HIFB_STEREO_MODE_E enMode, HIFB_STEREO_MODE_E enWbcSteroMode);

	/*set stereo address*/
	/*CNcomment:����3D ģʽ�����۵�ַ*/
	HI_S32 (*OPTM_GfxSetTriDimAddr)(HIFB_LAYER_ID_E enLayerId, HI_U32 u32TriDimAddr);
#endif	
	/*set the priority of layer in gp*/
	/*CNcomment:����ͼ����GP �е����ȼ�*/
	HI_S32 (*OPTM_GfxSetLayerPriority)(HIFB_LAYER_ID_E u32LayerId, HIFB_ZORDER_E enZOrder);

	/*get the priority of layer in gp*/
	/*CNcomment:��ȡͼ����GP �е����ȼ�*/
	HI_S32 (*OPTM_GfxGetLayerPriority)(HIFB_LAYER_ID_E u32LayerId, HI_U32 *pU32Priority);
	
	/*��ȡͼ���������*/
	HI_VOID (*OPTM_GFX_GetDevCap)(const HIFB_CAPABILITY_S **pstCap);
	/*��ȡͼ�����������С*/
	HI_S32 (*OPTM_GfxGetOutRect)(HIFB_LAYER_ID_E enLayerId, HIFB_RECT * pstOutputRect);
	/*��ȡͼ������������С*/
	HI_S32 (*OPTM_GfxGetLayerRect)(HIFB_LAYER_ID_E enLayerId, HIFB_RECT *pstRect);
	/*�����û�����GP����ֱ��ʱ�־*/
	HI_S32 (*OPTM_GFX_SetGpInUsrFlag)(OPTM_GFX_GP_E enGpId, HI_BOOL bFlag);
	/*��ȡ�û�����GP����ֱ��ʱ�־*/
	HI_S32 (*OPTM_GFX_GetGpInUsrFlag)(OPTM_GFX_GP_E enGpId);
	/*�����û�����GP����ֱ��ʱ�־*/
	HI_S32 (*OPTM_GFX_SetGpInInitFlag)(OPTM_GFX_GP_E enGpId, HI_BOOL bFlag);
	/*��ȡ�û�����GP����ֱ��ʱ�־*/
	HI_S32 (*OPTM_GFX_GetGpInInitFlag)(OPTM_GFX_GP_E enGpId);
	/*set gp mask flag*/
	HI_S32 (*OPTM_GFX_SetGPMask)(OPTM_GFX_GP_E enGpId, HI_BOOL bFlag);
	/*get gfx mask flag*/
	HI_S32 (*OPTM_GFX_GetGfxMask)(OPTM_GFX_GP_E enGpId);
	HI_S32 (*OPTM_GfxGetDispFMTSize)(OPTM_GFX_GP_E enGpId, HIFB_RECT *pstOutRect);
#ifndef HI_BUILD_IN_BOOT	
	HI_S32 (*OPTM_GFX_ClearLogoOsd)(HIFB_LAYER_ID_E enLayerId);
	HI_S32 (*OPTM_GFX_SetStereoDepth)(HIFB_LAYER_ID_E enLayerId, HI_S32 s32Depth);
	HI_S32 (*OPTM_GFX_CMP_Open)(HIFB_LAYER_ID_E enLayerId);
	HI_S32 (*OPTM_GFX_CMP_Close)(HIFB_LAYER_ID_E enLayerId);
	HI_S32 (*OPTM_GFX_CMP_GetSwitch)(HIFB_LAYER_ID_E enLayerId);
	HI_S32 (*OPTM_GFX_SetCmpRect)(HIFB_LAYER_ID_E enLayerId, HIFB_RECT *pstRect);
	/*Set compression Mode*/
	HI_S32 (*OPTM_GFX_SetCmpMode)(HIFB_LAYER_ID_E enLayerId, HIFB_CMP_MODE_E enCMPMode);
	/*Get compression Mode*/
	HIFB_CMP_MODE_E (*OPTM_GFX_GetCmpMode)(HIFB_LAYER_ID_E enLayerId);
	/*Get compression Mode*/
	HI_S32 (*OPTM_GFX_SetCmpDDROpen)(HIFB_LAYER_ID_E enLayerId, HI_BOOL bOpen);
	/*Get slvavery layer info*/
	HI_S32 (*OPTM_GFX_GetSlvLayerInfo)(HIFB_SLVLAYER_DATA_S *pstLayerInfo);
#endif	
	HI_S32 (*OPTM_GFX_SetTCFlag)(HI_BOOL bFlag);
    HI_S32 (*OPTM_GfxSetGpDeflicker)(OPTM_GFX_GP_E enGpId, HI_BOOL bDeflicker);
	HI_S32 (*OPTM_GFX_GetHaltDispStatus)(HIFB_LAYER_ID_E enLayerId, HI_BOOL *pbDispInit);
}OPTM_GFX_OPS_S;


/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/


/***************************************************************************************
* func          : OPTM_GFX_GetOps
* description   : get hifb options, then can call the functions \n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_GFX_GetOps(OPTM_GFX_OPS_S *ops);

/***************************************************************************************
* func          : OPTM_UnmapAndRelease
* description   : unmap the ddr and release it\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID OPTM_UnmapAndRelease(MMZ_BUFFER_S *psMBuf);

/***************************************************************************************
* func          : OPTM_AllocAndMap
* description   : CNcomment: alloc and map mem CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 OPTM_AllocAndMap(const char *bufname, char *zone_name, HI_U32 size, int align, MMZ_BUFFER_S *psMBuf);

/***************************************************************************************
* func          : HIFB_WBC2_OpenSlvLayer
* description   : CNcomment: ͬԴ��д������´򿪱���ͼ�㣬��������ر�����
                             ��ز��� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HIFB_WBC2_OpenSlvLayer(HIFB_LAYER_ID_E enLayerId);

#ifdef HI_BUILD_IN_BOOT
HI_S32 OPTM_GfxInit(HI_VOID);
HI_S32 OPTM_GfxOpenLayer(HIFB_LAYER_ID_E enLayerId);
HI_S32 OPTM_GfxCloseLayer(HIFB_LAYER_ID_E enLayerId);
HI_S32 OPTM_GfxSetLayerAlpha(HIFB_LAYER_ID_E enLayerId, HIFB_ALPHA_S *pstAlpha);
HI_S32 OPTM_GfxSetLayerAddr(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Addr);
HI_S32 OPTM_GfxSetLayerStride(HIFB_LAYER_ID_E enLayerId, HI_U32 u32Stride);
HI_S32 OPTM_GfxSetLayerDataFmt(HIFB_LAYER_ID_E enLayerId, HIFB_COLOR_FMT_E enDataFmt);
HI_S32 OPTM_GfxSetLayerRect(HIFB_LAYER_ID_E enLayerId, const HIFB_RECT *pstRect);
HI_S32 OPTM_GfxSetLayKeyMask(HIFB_LAYER_ID_E enLayerId, const HIFB_COLORKEYEX_S *pstColorkey);
HI_VOID OPTM_Wbc2Isr(HI_VOID* pParam0, HI_VOID *pParam1);
HI_S32 OPTM_GfxSetEnable(HIFB_LAYER_ID_E enLayerId, HI_BOOL bEnable);
HI_S32 OPTM_GfxSetGpRect(OPTM_GFX_GP_E enGpId, const HIFB_RECT * pstInputRect);
HI_S32 OPTM_GfxUpLayerReg(HIFB_LAYER_ID_E enLayerId);
HIFB_GFX_MODE_EN OPTM_Get_GfxWorkMode(HI_VOID);
HI_S32 OPTM_GpInitFromDisp(OPTM_GFX_GP_E enGPId);
HI_S32 OPTM_GfxSetDispFMTSize(OPTM_GFX_GP_E enGpId, const HI_RECT_S *pstOutRect);
HI_S32 OPTM_GFX_SetTCFlag(HI_BOOL bFlag);
#endif



#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __OPTM_HIFB_H__ */
