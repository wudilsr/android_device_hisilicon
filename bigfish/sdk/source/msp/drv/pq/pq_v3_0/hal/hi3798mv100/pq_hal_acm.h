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

/*ACM �Ĵ������Ʋ����ṹ*/
typedef struct hiACM_CTRL_S
{
    HI_U32 u32En;
    HI_U32 u32DbgEn;
    HI_U32 u32Stretch;
    HI_U32 u32Cliprange;
    HI_U32 u32Cliporwrap;
    HI_U32 u32Cbcrthr;      /*CbCr������ֵ������������ֵ�Ͳ���Color����*/
} ACM_CTRL_S;

/*ACM table�ṹ*/
typedef struct hiCOLOR_LUT_S
{
    HI_S16 as16Color[5][7][29];  /*ACM ���ұ�*/
} COLOR_LUT_S;

typedef struct hiCOLOR_ACM_LUT_S
{
    HI_S16 as16Luma[5][7][29];   /*Luma���ұ�*/
    HI_S16 as16Hue[5][7][29];    /*Hue���ұ�*/
    HI_S16 as16Sat[5][7][29];    /*Saturation���ұ�*/
} COLOR_ACM_LUT_S;


/*����ɫӳ���*/
typedef struct hiHUE_RANG_S
{
    HI_U32  u32HueStart;
    HI_U32  u32HueEnd;
} HUE_RANG_S;

/*����ɫ����*/
typedef enum hiSIX_BASE_COLOR_E
{
    SIX_BASE_COLOR_R       ,//��
    SIX_BASE_COLOR_G       ,//��
    SIX_BASE_COLOR_B1      ,//��
    SIX_BASE_COLOR_B2      ,//��
    SIX_BASE_COLOR_CYAN    ,//��
    SIX_BASE_COLOR_MAGENTA ,//��
    SIX_BASE_COLOR_YELLOW  ,//��
    SIX_BASE_COLOR_ALL     ,

    SIX_BASE_COLOR_BUTT
} SIX_BASE_COLOR_E;


/**
 \brief ȥ��ʼ��ACMģ��;
 \attention \n
  ��

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_DeInitACM(HI_VOID);

/**
 \brief ��ʼ��ACMģ��;
 \attention \n
  ��

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32  PQ_HAL_InitACM(HI_VOID);

/**
 \brief ����Color����;
 \attention \n
��

 \param[in] *pstColorTable ����COLOR Table;

 \retval ::HI_SUCCESS

 */

HI_S32  PQ_HAL_SetACMParam(COLOR_ACM_LUT_S* pstColorTable);

/**
 \brief ��ȡColor����;
 \attention \n
��

 \param[out] *pstColorTable ;

 \retval ::HI_SUCCESS

 */

HI_S32  PQ_HAL_GetACMParam(COLOR_ACM_LUT_S* pstColorTable);

/**
 \brief ��������ģʽ;
 \attention \n
��

 \param[in] u32ChId
 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_VOID PQ_HAL_ACMDemoMode(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff);

/**
 \brief ��ACMģ��
 \attention \n
��

 \param[in] u32ChId

 \retval ::HI_SUCCESS

 */

HI_VOID PQ_HAL_EnableACM(PQ_HAL_LAYER_VP_E u32ChId);

/**
 \brief �ر�ACMģ��
 \attention \n
��

 \param[in] u32ChId

 \retval ::HI_SUCCESS

 */

HI_VOID PQ_HAL_DisableACM(PQ_HAL_LAYER_VP_E u32ChId);

/**
 \brief ��ȡACM���ر�־
 \attention \n
��

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
