/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_acm_convert.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2012/09/11
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_ACM_CONVERT_H__
#define __PQ_HAL_ACM_CONVERT_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define COEFACMCNT 255
#define LUT0_PIXEL_NUM 180
#define LUT1_PIXEL_NUM 120
#define LUT2_PIXEL_NUM 135
#define LUT3_PIXEL_NUM 90
#define LUT4_PIXEL_NUM 168
#define LUT5_PIXEL_NUM 112
#define LUT6_PIXEL_NUM 126
#define LUT7_PIXEL_NUM 84


typedef struct acm_split_Table
{
    HI_S32 LUT0[LUT0_PIXEL_NUM];
    HI_S32 LUT1[LUT1_PIXEL_NUM];
    HI_S32 LUT2[LUT2_PIXEL_NUM];
    HI_S32 LUT3[LUT3_PIXEL_NUM];
    HI_S32 LUT4[LUT4_PIXEL_NUM];
    HI_S32 LUT5[LUT5_PIXEL_NUM];
    HI_S32 LUT6[LUT6_PIXEL_NUM];
    HI_S32 LUT7[LUT7_PIXEL_NUM];
} ACM_SPLIT_TABLE;

#if 0

typedef struct llllong
{
    HI_U32 u32Data[4];
} LLLONG_S;

typedef struct acm_convert_Table
{
    LLLONG_S LUT0_CONF[45];
    LLLONG_S LUT1_CONF[30];
    LLLONG_S LUT2_CONF[34];
    LLLONG_S LUT3_CONF[23];
    LLLONG_S LUT4_CONF[42];
    LLLONG_S LUT5_CONF[28];
    LLLONG_S LUT6_CONF[32];
    LLLONG_S LUT7_CONF[21];
} ACM_CONVERT_TABLE;
#endif

typedef struct
{
    HI_S32  bits_0    : 9 ;
    HI_S32  bits_1    : 9 ;
    HI_S32  bits_2    : 9 ;
    HI_S32  bits_35   : 5 ;
    HI_S32  bits_34   : 4 ;
    HI_S32  bits_4    : 7 ;
    HI_S32  bits_5    : 7 ;
    HI_S32  bits_6    : 9 ;
    HI_S32  bits_75   : 5 ;
    HI_S32  bits_74   : 4 ;
    HI_S32  bits_8    : 9 ;
    HI_S32  bits_9    : 9 ;
    HI_S32  bits_10   : 7 ;
    HI_S32  bits_113  : 3 ;
    HI_S32  bits_114  : 4 ;
    HI_S32  bits_12   : 28  ;
} ACM_COEF_BIT_S;

typedef struct
{
    HI_U32          u32Size;
    ACM_COEF_BIT_S  stBit[COEFACMCNT];
} ACM_COEF_BITARRAY_S;


HI_S32 PQ_HAL_Split_Table(HI_S16 ps16OriLUT[5][7][29], ACM_SPLIT_TABLE* pSplitTbl);

HI_U32 PQ_HAL_AcmCoefConvert(ACM_SPLIT_TABLE* pstSplitTable_Y,
                             ACM_SPLIT_TABLE* pstSplitTable_S,
                             ACM_SPLIT_TABLE* pstSplitTable_H,
                             ACM_COEF_BITARRAY_S* pBitCoef);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
