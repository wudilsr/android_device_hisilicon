/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_csc.h
  Version       : Initial Draft
  Author        : Hisilicon PQ software group
  Created       : 2012/09/18
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_CSC_H__
#define __PQ_HAL_CSC_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

/*视频层类型*/
typedef enum hiHAL_DISP_LAYER_E
{
    HAL_DISP_LAYER_V0 = 0,
    HAL_DISP_LAYER_V1    ,
    HAL_DISP_LAYER_V2    ,
    HAL_DISP_LAYER_V3    ,
    HAL_DISP_LAYER_V4    ,
  //HAL_DISP_LAYER_VP0   ,
  //HAL_DISP_LAYER_VP1   ,

    HAL_DISP_LAYER_BUTT
} HAL_DISP_LAYER_E;

/*色彩空间转换类型*/
typedef enum hiCSC_MODE_E
{
    HAL_CSC_YUV2RGB_601 = 0  ,   // YCbCr_601 LIMIT-> RGB
    HAL_CSC_YUV2RGB_709      ,   // YCbCr_709 LIMIT-> RGB
    HAL_CSC_RGB2YUV_601      ,   // RGB->YCbCr_601 LIMIT  
    HAL_CSC_RGB2YUV_709      ,   // RGB->YCbCr_709 LIMIT
    HAL_CSC_YUV2YUV_709_601  ,   // YCbCr_709 LIMIT->YCbCr_601 LIMIT
    HAL_CSC_YUV2YUV_601_709  ,   // YCbCr_601 LIMIT->YCbCr_709 LIMIT
    HAL_CSC_YUV2YUV          ,   // YCbCr LIMIT->YCbCr LIMIT
    HAL_CSC_YUV2RGB_601_FULL ,   // YCbCr_601 FULL-> RGB
    HAL_CSC_YUV2RGB_709_FULL ,   // YCbCr_709 FULL-> RGB
    HAL_CSC_RGB2YUV_601_FULL ,   // RGB->YCbCr_601 FULL  
    HAL_CSC_RGB2YUV_709_FULL ,   // RGB->YCbCr_709 FULL
    HAL_CSC_RGB2RGB          ,   // RGB->RGB

    HAL_CSC_BUTT
} CSC_MODE_E;

/*色彩空间标准*/
typedef enum hiCOLOR_SPACE_TYPE_E
{
    OPTM_CS_eUnknown = 0           ,
    OPTM_CS_eItu_R_BT_709 = 1      ,
    OPTM_CS_eFCC = 4               ,
    OPTM_CS_eItu_R_BT_470_2_BG = 5 ,
    OPTM_CS_eSmpte_170M = 6        ,
    OPTM_CS_eSmpte_240M = 7        ,
    OPTM_CS_eXvYCC_709 = OPTM_CS_eItu_R_BT_709,
    OPTM_CS_eXvYCC_601 = 8         ,
    OPTM_CS_eRGB = 9               ,
    
    OPTM_CS_BUTT
} COLOR_SPACE_TYPE_E;

/*色温通道*/
typedef enum hiCOLORTEMP_CHANNEL_E
{
    COLORTEMP_R = 0  ,
    COLORTEMP_G = 1  ,
    COLORTEMP_B = 2  ,

    COLORTEMP_ALL = 3
} COLORTEMP_CHANNEL_E;

/*CSC 参数结构*/
typedef struct hiCSC_PARA_S
{
    HI_U32  u16Brightness;
    HI_U32  u16Contrast;
    HI_U32  u16Hue;
    HI_U32  u16Saturation;
    HI_U32  as16ColorTempGain[COLORTEMP_ALL];
    HI_U32  as16ColorTempOffset[COLORTEMP_ALL];
    HI_U16  u16InputColorSpace;
    HI_U16  u16OutputColorSpace;
    HI_BOOL bFullRange;
} CSC_PARA_S;

/*CSC 矩阵系数结构*/
typedef struct  hiCSC_COEF_S
{
    HI_S32 csc_coef00;
    HI_S32 csc_coef01;
    HI_S32 csc_coef02;

    HI_S32 csc_coef10;
    HI_S32 csc_coef11;
    HI_S32 csc_coef12;

    HI_S32 csc_coef20;
    HI_S32 csc_coef21;
    HI_S32 csc_coef22;
} CSC_COEF_S;

typedef struct  hiCSC_DCCOEF_S
{
    HI_S32 csc_in_dc0;
    HI_S32 csc_in_dc1;
    HI_S32 csc_in_dc2;

    HI_S32 csc_out_dc0;
    HI_S32 csc_out_dc1;
    HI_S32 csc_out_dc2;
} CSC_DCCOEF_S;

typedef struct  hiCSC_MODE_S
{
    HI_BOOL     bCSCEn;
    CSC_MODE_E  enCSC;
} CSC_MODE_S;

/**
 \brief 设置CSC参数;
 \attention \n
无

 \param[in] enDisplayId
 \param[in] pstCSCParameter

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_SetCSCPictureParam(HAL_DISP_LAYER_E enDisplayId, CSC_PARA_S *pstCSCParameter);

/**
 \brief 获取CSC转换模式;
 \attention \n
无

 \param[in] enDisplayId
 \param[out] pstCscMode

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_GetCSCMode(HAL_DISP_LAYER_E enDisplayId, CSC_MODE_S *pstCscMode);

/**
 \brief 设置CSC转换模式;
 \attention \n
无

 \param[in] eLayer
 \param[in] eCSCMode

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_SetCSCMode(HAL_DISP_LAYER_E enLayer, CSC_MODE_E enCscMode);

/**
 \brief 打开CSC模块
 \attention \n
无

 \param[in] enLayer
 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_EnableCSC(HAL_DISP_LAYER_E enLayer, HI_BOOL bCscEn);

HI_S32 PQ_HAL_GetCscCoef(CSC_MODE_E enCscMode, CSC_COEF_S *pstCscCoef, CSC_DCCOEF_S *pstCscDCCoef);

HI_S32 PQ_HAL_Get8BitCscCoef(CSC_MODE_E enCscMode, CSC_COEF_S *pstCscCoef, CSC_DCCOEF_S *pstCscDCCoef);
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif
