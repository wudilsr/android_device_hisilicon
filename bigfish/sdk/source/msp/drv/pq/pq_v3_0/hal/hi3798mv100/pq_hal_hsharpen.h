/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_hsharpen.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/10
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_HSHARPEN_H__
#define __PQ_HAL_HSHARPEN_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

typedef struct hiHSHARPEN_PARA_S
{
    HI_U8  u8HSharpEn;       /* 1bit */
    HI_U8  u8PeakRatio;      /* (u,8,7) */
    HI_U8  u8HspMarketEn;    /* 1bit 卖场模式使能 */
    HI_U8  u8HspMarketMode;  /* 1bit 卖场模式选择0:左边处理,1:右边处理 */   
    HI_U16 u16GlbOverThrsh;  /* 9bit */
    HI_U16 u16GlbUnderThrsh; /* 9bit */
    HI_U8  u8LTIHEn;         /* 1bit */
    HI_U8  u8CTIHEn;         /* 1bit */
    HI_U8  u8AdpShootDiv;    /* 3bit 高频调整移位系数，无符号 */
    HI_U8  u8LTIRatio;       /* (u,8,7) 亮度增强比率 */
    HI_U8  u8LTIGainH;       /* (u,8,5) */
    HI_U8  u8CTIGainH;       /* (u,8,5) */

    HI_U8  u8H0SharpEn;      /* 1bit 高频滤波0使能*/
    HI_S8  s8H0Tmp3;         /* 8bit, signed,[-128,127] */
    HI_S8  s8H0Tmp2;         /* 8bit, signed,[-128,127] */
    HI_S8  s8H0Tmp1;         /* 8bit, signed,[-128,127] */
    HI_S8  s8H0Tmp0;         /* 8bit, signed,[-128,127] */
    HI_S16 s16H0GainPos;     /* (s,10,7);[-512,511] */
    HI_S16 s16H0GainNeg;     /* (s,10,7);[-512,511] */
    HI_U8  u8H0Coring;       /* 8bit */
    HI_U8  u8H0OverThrsh;    /* 8bit */
    HI_U8  u8H0UnderThrsh;   /* 8bit */
    HI_U8  u8H0MixRatio;     /* (u,8,7) */
    HI_U8  u8H0WinSize;      /* 3bit */
    HI_U8  u8H0AdpShootEn;   /* 1bit */


    HI_U8  u8H1SharpEn;      /* 1bit 高频滤波1使能 */
    HI_S8  s8H1Tmp3;         /* 8bit, signed,[-128,127] */
    HI_S8  s8H1Tmp2;         /* 8bit, signed,[-128,127] */
    HI_S8  s8H1Tmp1;         /* 8bit, signed,[-128,127] */
    HI_S8  s8H1Tmp0;         /* 8bit, signed,[-128,127] */
    HI_S16 s16H1GainPos;     /* (s,10,7);[-512,511] */
    HI_S16 s16H1GainNeg;     /* (s,10,7);[-512,511] */
    HI_U8  u8H1Coring;       /* 8bit */
    HI_U8  u8H1OverThrsh;    /* 8bit */
    HI_U8  u8H1UnderThrsh;   /* 8bit */
    HI_U8  u8H1MixRatio;     /* (u,8,7) */
    HI_U8  u8H1WinSize;      /* 3bit */
    HI_U8  u8H1AdpShootEn;   /* 1bit */

} HSHARPEN_PARA_S;

typedef struct hiPQ_HSHARPEN_GAIN_S
{
    HI_S32 s32H0GainPos;
    HI_S32 s32H0GainNeg;
    HI_S32 s32H1GainPos;
    HI_S32 s32H1GainNeg;
    
}PQ_HSHARPEN_GAIN_S;

/* HSharp Demo Mode*/
typedef enum hiHSHARP_DEMO_MODE_E
{
    HSHARP_DEMO_LEFT_OPEN =0  ,
    HSHARP_DEMO_RIGHT_OPEN    ,

    HSHARP_DEMO_BUTT
    
}HSHARP_DEMO_MODE_E;


/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_SetHSharpStrReg(HI_U32 u32HandleNo,HI_S32 s32ShpStr)
Description     : 设置hsharpen强度相关的寄存器值
Calls           :
Data Accessed   :
Data Updated    :
Input           : s32ShpStr，全局强度控制参数,取值范围[0, 255]
Output          : NA
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_SetHSharpStrReg(HI_U32 u32HandleNo, HI_S32 s32ShpStr, PQ_HSHARPEN_GAIN_S *pstHsharpenGain);


/*--------------------------------------------------------------------------------*
Function        : PQ_HAL_GetHSharpStrReg(HI_S32 *s32ShpStr)
Description     : 获取hsharpen强度
Calls           :
Data Accessed   :
Data Updated    :
Input           : 
Output          : s32ShpStr
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_GetHSharpStrReg(HI_S32 *s32ShpStr);


/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_GetHSharpRegist(HSHARPEN_PARA_S * pstHSharpPara)
Description     : 获取hsharpen寄存器值
Calls           :
Data Accessed   :
Data Updated    :
Input           : pstHSharpPara hsharpen的参数;u32HandleNo
Output          : NA
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_GetHSharpRegist(HSHARPEN_PARA_S * pstHSharpPara,HI_U32 u32HandleNo);

/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_SetHSharpRegist(HI_U32 u32HandleNo,HSHARPEN_PARA_S * pstHSharpPara)
Description     :设置hsharpen寄存器值
Calls           :
Data Accessed   :
Data Updated    :
Input           : u32HandleNo
                : pstHSharpPara     hsharpen的参数
Output          :NA
Return          :HI_SUCCESS
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_SetHSharpRegist(HI_U32 u32HandleNo,HSHARPEN_PARA_S * pstHSharpPara);


/**
 \brief 开关HSHARPEN模块
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_EnableHSharp(HI_U32 u32HandleNo,HI_BOOL bOnOff);

/**
 \brief 获取HSHARPEN模块开关状态
 \attention \n
无

 \param[out] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_GetEnableHSharp(HI_U32 u32HandleNo, HI_BOOL *bOnOff);

/**
 \brief 开关HSHARPEN卖场模式
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_HSharpDemoEn(HI_U32 u32HandleNo, HI_BOOL bOnOff);


/**
 \brief 选择HSHARPEN卖场模式
 \attention \n
无

 \param[in]
           0：左半边为处理后的值，右半边为原值；
           1：左半边为输入值，右半边为处理后的值。

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_HSharpDemoMode(HI_U32 u32HandleNo, HI_U32 u32HshpDemoMode);




#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __PQ_HAL_SHARPEN_H__ */

