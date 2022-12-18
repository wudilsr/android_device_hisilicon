/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_acm.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2012/09/11
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_ACM_H__
#define __PQ_HAL_ACM_H__

#include "hi_type.h"
#include "pq_hal_comm.h"
#include "hi_drv_mmz.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*ACM 寄存器控制参数结构*/
typedef struct hiACM_CTRL_S
{
    HI_U32 u32En;
    HI_U32 u32DbgEn;
    HI_U32 u32Stretch;
    HI_U32 u32Cliprange;
    HI_U32 u32Cliporwrap;
    HI_U32 u32Cbcrthr;      /*CbCr的门限值，若低于门限值就不做Color处理*/
} ACM_CTRL_S;

/*ACM table结构*/
typedef struct hiCOLOR_LUT_S
{
    HI_S16 as16Color[5][7][29];  /*ACM 查找表*/
} COLOR_LUT_S;

typedef struct hiCOLOR_ACM_LUT_S
{
    HI_S16 as16Luma[5][7][29];   /*Luma查找表*/
    HI_S16 as16Hue[5][7][29];    /*Hue查找表*/
    HI_S16 as16Sat[5][7][29];    /*Saturation查找表*/
} COLOR_ACM_LUT_S;


/*六基色映射表*/
typedef struct hiHUE_RANG_S
{
    HI_U32  u32HueStart;
    HI_U32  u32HueEnd;
} HUE_RANG_S;

/*六基色类型*/
typedef enum hiSIX_BASE_COLOR_E
{
    SIX_BASE_COLOR_R       ,//红
    SIX_BASE_COLOR_G       ,//绿
    SIX_BASE_COLOR_B1      ,//蓝
    SIX_BASE_COLOR_B2      ,//蓝
    SIX_BASE_COLOR_CYAN    ,//青
    SIX_BASE_COLOR_MAGENTA ,//紫
    SIX_BASE_COLOR_YELLOW  ,//黄
    SIX_BASE_COLOR_ALL     ,

    SIX_BASE_COLOR_BUTT
} SIX_BASE_COLOR_E;


/**
 \brief 去初始化ACM模块;
 \attention \n
  无

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_DeInitACM(HI_VOID);

/**
 \brief 初始化ACM模块;
 \attention \n
  无

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32  PQ_HAL_InitACM(HI_VOID);

/**
 \brief 设置Color参数;
 \attention \n
无

 \param[in] *pstColorTable 输入COLOR Table;

 \retval ::HI_SUCCESS

 */

HI_S32  PQ_HAL_SetACMParam(COLOR_ACM_LUT_S* pstColorTable);

/**
 \brief 获取Color参数;
 \attention \n
无

 \param[out] *pstColorTable ;

 \retval ::HI_SUCCESS

 */

HI_S32  PQ_HAL_GetACMParam(COLOR_ACM_LUT_S* pstColorTable);

/**
 \brief 开关卖场模式;
 \attention \n
无

 \param[in] u32ChId
 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_VOID PQ_HAL_ACMDemoMode(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff);

/**
 \brief 打开ACM模块
 \attention \n
无

 \param[in] u32ChId

 \retval ::HI_SUCCESS

 */

HI_VOID PQ_HAL_EnableACM(PQ_HAL_LAYER_VP_E u32ChId);

/**
 \brief 关闭ACM模块
 \attention \n
无

 \param[in] u32ChId

 \retval ::HI_SUCCESS

 */

HI_VOID PQ_HAL_DisableACM(PQ_HAL_LAYER_VP_E u32ChId);

/**
 \brief 获取ACM开关标志
 \attention \n
无

 \param[out] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32  PQ_HAL_GetACMEnableFlag(HI_BOOL* bOnOff);

HI_VOID PQ_HAL_SetACMCbcrThd(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Data);
HI_VOID PQ_HAL_SetACMStretch(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Data);
HI_VOID PQ_HAL_SetACMClipRange(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Data);
HI_VOID PQ_HAL_SetACMCliporWrap(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Data);
HI_VOID PQ_HAL_SetACMGain(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Luma, HI_U32 u32Hue, HI_U32 u32Sat);
HI_VOID PQ_HAL_GetACMGain(PQ_HAL_LAYER_VP_E u32ChId, HI_U32* pu32Luma, HI_U32* pu32Hue, HI_U32* pu32Sat);
HI_S32 PQ_HAL_SetACMLumaTbl(COLOR_LUT_S* pstColorData);
HI_S32 PQ_HAL_SetACMHueTbl(COLOR_LUT_S* pstColorData);
HI_S32 PQ_HAL_SetACMSatTbl(COLOR_LUT_S* pstColorData);
HI_S32 PQ_HAL_GetACMLumaTbl(COLOR_LUT_S* pstColorData);
HI_S32 PQ_HAL_GetACMHueTbl(COLOR_LUT_S* pstColorData);
HI_S32 PQ_HAL_GetACMSatTbl(COLOR_LUT_S* pstColorData);
HI_VOID PQ_HAL_UpdatACMCoef(PQ_HAL_LAYER_VP_E u32ChId);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
