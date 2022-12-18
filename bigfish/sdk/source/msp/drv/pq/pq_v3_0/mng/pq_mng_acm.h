/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_acm.h
  Version       : Initial Draft
  Author        : p00203646
  Created       : 2014/4/22
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_ACM_H__
#define __PQ_MNG_ACM_H__

#include "hi_type.h"
#include "pq_hal_acm.h"
#include "drv_pq_define.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


/*肤色增益类型*/
typedef enum hiFLESHTONE_LEVEL_E
{
    FLESHTONE_GAIN_OFF = 0 ,
    FLESHTONE_GAIN_LOW     ,
    FLESHTONE_GAIN_MID     ,
    FLESHTONE_GAIN_HIGH    ,

    FLESHTONE_GAIN_BUTT
} FLESHTONE_LEVEL_E;

/*六基色偏移值*/
typedef struct hiSIX_BASE_COLOR_OFFSET_S
{
    HI_U32  u32RedOffset;
    HI_U32  u32GreenOffset;
    HI_U32  u32BlueOffset;
    HI_U32  u32CyanOffset;
    HI_U32  u32MagentaOffset;
    HI_U32  u32YellowOffset;

} SIX_BASE_COLOR_OFFSET_S;

/*颜色增强类型*/
typedef enum hiCOLOR_SPEC_MODE_E
{
    COLOR_MODE_RECOMMEND = 0  , //推荐的颜色增强模式
    COLOR_MODE_BLUE           , //固定的蓝色增强模式
    COLOR_MODE_GREEN          , //固定的绿色增强模式
    COLOR_MODE_BG             , //固定的蓝绿色增强模式

    COLOR_MODE_BUTT
} COLOR_SPEC_MODE_E;

/*ACM GAIN 消息结构*/
typedef struct hiCOLOR_GAIN_S
{
    HI_U32 u32GainMode;   /*0:SD;1:HD;2:UHD*/
    HI_U32 u32Gainluma;   /*表示对Hue的增益，范围0-1023*/
    HI_U32 u32Gainhue;    /*表示对Hue的增益，范围0-1023*/
    HI_U32 u32Gainsat;    /*表示对Luma的增益*/

} COLOR_GAIN_S;


/**
 \brief去初始化Color;
 \attention \n
  无

 \param[in]

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_DeInitColor(HI_VOID);


/**
 \brief 初始化Color模块;
 \attention \n
无

 \param[in] pszPath 文件路径;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_InitColor(PQ_PARAM_S* pstPqParam, HI_BOOL bDefault);


/**
 \brief 获取Color增益
 \attention \n
  无

 \param[in] *pu32ColorLevel;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetColorGainLevel(HI_U32* pu32ColorLevel);


/**
 \brief Color增强增益控制
 \attention \n
  无

 \param[in] enGainLevel;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_SetColorGainLevel(HI_U32 enGainLevel);

/**
 \brief 获取肤色增益
 \attention \n
  无

 \param[in] *pu32FleshToneLevel;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetFleshToneLevel(HI_U32* pu32FleshToneLevel);


/**
 \brief 肤色增益控制
 \attention \n
  无

 \param[in] enGainLevel;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_SetFleshToneLevel(FLESHTONE_LEVEL_E enGainLevel, HI_U32 u32SourceMode);


/**
 \brief 六基色控制设置
 \attention \n
  无

 \param[in] enSixColorType;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_SetSixBaseColorLevel(SIX_BASE_COLOR_OFFSET_S* pstSixBaseColorOffset, HI_U32 u32SourceMode);


/**
 \brief 获取六基色设置值
 \attention \n
  无

 \param[in] pu32SixColorType;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetSixBaseColorLevel(SIX_BASE_COLOR_OFFSET_S* pstSixBaseColorOffset);


/**
 \brief 开关卖场模式
 \attention \n
无

 \param[in] bOnOff;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_ColorDemoMode(HI_BOOL bOnOff);


/**
 \brief 打开ACM模块
 \attention \n
  无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableColorEnhance(HI_BOOL bOnOff);


/**
 \brief 获取颜色增强模式
 \attention \n
  无

 \param[in] pu32ColorEnhanceMode;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetColorEnhanceMode(HI_U32* pu32ColorEnhanceMode);


/**
 \brief 颜色增强模式设置
 \attention \n
  无

 \param[in] enColorSpecMode 0-RECOMMEND;1-BLUE;2-GREEN;3-BG;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_SetColorEnhanceMode(COLOR_SPEC_MODE_E  enColorSpecMode, HI_U32 u32SourceMode);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
