/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_sharp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/10
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_SHARPEN_H__
#define __PQ_HAL_SHARPEN_H__

#include "hi_type.h"
#include "pq_hal_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef struct hiPQ_SHARP_GAIN_RATIO_S
{
    HI_U32 u32HD_Lgain_ratio;
    HI_U32 u32HD_Cgain_ratio;
    HI_U32 u32SD_Lgain_ratio;
    HI_U32 u32SD_Cgain_ratio;
}
PQ_SHARP_GAIN_RATIO_S;

/******************************************DEFINR SHARP START**************************************/
typedef struct hi_PQ_SHARP_LUMA_S
{
    HI_U32 u32Lti_en;                   // luma sharpen enable
    HI_U32 u32Lti_demo_en;              // luma sharpen demo enable
    HI_U32 u32SharpIntensity;           // Sharp Intensity
    HI_U32 u32Lgain_ratio;              // gain ratio for luma
    HI_U32 u32Lmixing_ratio;            // mixing weight for luma (u,1,7）
    HI_S32 s32Lhpass_coef0;             // HPL coefficient 0 for luma
    HI_S32 s32Lhpass_coef1;             // HPL coefficient 1 for luma
    HI_S32 s32Lhpass_coef2;             // HPL coefficient 2 for luma
    HI_S32 s32Lhpass_coef3;             // HPL coefficient 3 for luma
    HI_S32 s32Lhpass_coef4;             // HPL coefficient 4 for luma
    HI_U32 u32Lcoring_thd;              // coring threshold for luma
    HI_U32 u32Lunder_swing;             // minimum swing value for luma
    HI_U32 u32Lover_swing;              // maximum swing value for luma
    HI_U32 u32Lhfreq_thd0;              // HF threshold 0 of HF gain curve for luma
    HI_U32 u32Lhfreq_thd1;              // HF threshold 1 of HF gain curve for luma
    HI_U32 u32Lgain_coef0;              // gain ratio 0 of HF gain curve for luma
    HI_U32 u32Lgain_coef1;              // gain ratio 1 of HF gain curve for luma
    HI_U32 u32Lgain_coef2;              // gain ratio 2 of HF gain curve for luma

} PQ_SHARP_LUMA_S;

typedef struct hi_PQ_SHARP_CHROMA_S
{
    HI_U32 u32Cti_en;                   // chroma sharpen enable
    HI_U32 u32Cti_demo_en;              // chroma sharpen demo enable
    HI_U32 u32Cgain_ratio;              // gain ratio for chroma
    HI_U32 u32Cmixing_ratio;            // mixing weight for chroma (u,1,7）
    HI_S32 s32Chpass_coef0;             // HPL coefficient 0 for chroma
    HI_S32 s32Chpass_coef1;             // HPL coefficient 1 for chroma
    HI_S32 s32Chpass_coef2;             // HPL coefficient 2 for chroma
    HI_U32 u32Ccoring_thd;              // coring threshold for chroma
    HI_U32 u32Cunder_swing;             // minimum swing value for chroma
    HI_U32 u32Cover_swing;              // maximum swing value for chroma

} PQ_SHARP_CHROMA_S;

typedef struct hi_PQ_SHARP_DATA_S
{
    PQ_SHARP_LUMA_S  stPqSharpLuma;
    PQ_SHARP_CHROMA_S stPqSharpChroma;

} PQ_SHARP_DATA_S;

typedef struct hi_PQ_SHARP_COEF_S
{
    PQ_SHARP_DATA_S  stSharpHdData;
    PQ_SHARP_DATA_S  stSharpSdData;
    //PQ_SHARP_DATA_S  stSharpGp0Data;
    //PQ_SHARP_DATA_S  stSharpGp1Data;
} PQ_SHARP_COEF_S;
/************************************DEFINR SHARP END******************************************/



/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_SetHSharpRegist(HI_U32 u32HandleNo,HSHARPEN_PARA_S * pstHSharpPara)
Description     :设置hsharpen寄存器值
Calls           :
Data Accessed   :
Data Updated    :
Input           : pstHSharpPara     hsharpen的参数
Output          :NA
Return          :HI_SUCCESS
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_SetSharpRegist(HI_U32 u32HandleNo, PQ_SHARP_COEF_S* pstSharpPara);


/**
 \brief 获取LTI开关
 \attention \n
无

 \param[in]*bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_GetLTIEnable(HI_U32 u32HandleNo, HI_U8* pu8Enable);


/**
 \brief 获取CTI开关
 \attention \n
无

 \param[in]*bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_GetCTIEnable(HI_U32 u32HandleNo, HI_U8* pu8Enable);


/**
 \brief 开关SHARPEN LTI模块
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_EnableLTI(HI_U32 u32HandleNo, HI_U8 u8Enable);


/**
 \brief 开关SHARPEN CTI模块
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_EnableCTI(HI_U32 u32HandleNo, HI_U8 u8Enable);


/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_SetSharpStrReg(HI_U32 u32HandleNo, HI_S32 s32ShpStr, PQ_SHARP_GAIN_RATIO_S* pstSharpGainRatio);
Description     : 设置sharpen强度相关的寄存器值
Calls           :
Data Accessed   :
Data Updated    :
Input           : PQ_SHARP_GAIN_RATIO_S* pstSharpGainRatio
Output          : NA
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_SetSharpStrReg(HI_U32 u32HandleNo, HI_S32 s32ShpStr, PQ_SHARP_GAIN_RATIO_S* pstSharpGainRatio);


/**
 \brief 开关SHARPEN LTI模块DEMO模式
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_EnableLTIDemo(HI_U32 u32HandleNo, HI_BOOL bOnOff);


/**
 \brief 开关SHARPEN CTI模块DEMO模式
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_EnableCTIDemo(HI_U32 u32HandleNo, HI_BOOL bOnOff);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __PQ_HAL_SHARPEN_H__ */

