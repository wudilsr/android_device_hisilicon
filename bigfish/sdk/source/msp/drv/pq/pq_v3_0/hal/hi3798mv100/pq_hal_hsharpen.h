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
    HI_U8  u8HspMarketEn;    /* 1bit ����ģʽʹ�� */
    HI_U8  u8HspMarketMode;  /* 1bit ����ģʽѡ��0:��ߴ���,1:�ұߴ��� */   
    HI_U16 u16GlbOverThrsh;  /* 9bit */
    HI_U16 u16GlbUnderThrsh; /* 9bit */
    HI_U8  u8LTIHEn;         /* 1bit */
    HI_U8  u8CTIHEn;         /* 1bit */
    HI_U8  u8AdpShootDiv;    /* 3bit ��Ƶ������λϵ�����޷��� */
    HI_U8  u8LTIRatio;       /* (u,8,7) ������ǿ���� */
    HI_U8  u8LTIGainH;       /* (u,8,5) */
    HI_U8  u8CTIGainH;       /* (u,8,5) */

    HI_U8  u8H0SharpEn;      /* 1bit ��Ƶ�˲�0ʹ��*/
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


    HI_U8  u8H1SharpEn;      /* 1bit ��Ƶ�˲�1ʹ�� */
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
Description     : ����hsharpenǿ����صļĴ���ֵ
Calls           :
Data Accessed   :
Data Updated    :
Input           : s32ShpStr��ȫ��ǿ�ȿ��Ʋ���,ȡֵ��Χ[0, 255]
Output          : NA
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_SetHSharpStrReg(HI_U32 u32HandleNo, HI_S32 s32ShpStr, PQ_HSHARPEN_GAIN_S *pstHsharpenGain);


/*--------------------------------------------------------------------------------*
Function        : PQ_HAL_GetHSharpStrReg(HI_S32 *s32ShpStr)
Description     : ��ȡhsharpenǿ��
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
Description     : ��ȡhsharpen�Ĵ���ֵ
Calls           :
Data Accessed   :
Data Updated    :
Input           : pstHSharpPara hsharpen�Ĳ���;u32HandleNo
Output          : NA
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_GetHSharpRegist(HSHARPEN_PARA_S * pstHSharpPara,HI_U32 u32HandleNo);

/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_SetHSharpRegist(HI_U32 u32HandleNo,HSHARPEN_PARA_S * pstHSharpPara)
Description     :����hsharpen�Ĵ���ֵ
Calls           :
Data Accessed   :
Data Updated    :
Input           : u32HandleNo
                : pstHSharpPara     hsharpen�Ĳ���
Output          :NA
Return          :HI_SUCCESS
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_SetHSharpRegist(HI_U32 u32HandleNo,HSHARPEN_PARA_S * pstHSharpPara);


/**
 \brief ����HSHARPENģ��
 \attention \n
��

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_EnableHSharp(HI_U32 u32HandleNo,HI_BOOL bOnOff);

/**
 \brief ��ȡHSHARPENģ�鿪��״̬
 \attention \n
��

 \param[out] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_GetEnableHSharp(HI_U32 u32HandleNo, HI_BOOL *bOnOff);

/**
 \brief ����HSHARPEN����ģʽ
 \attention \n
��

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_HSharpDemoEn(HI_U32 u32HandleNo, HI_BOOL bOnOff);


/**
 \brief ѡ��HSHARPEN����ģʽ
 \attention \n
��

 \param[in]
           0������Ϊ������ֵ���Ұ��Ϊԭֵ��
           1������Ϊ����ֵ���Ұ��Ϊ������ֵ��

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_HSharpDemoMode(HI_U32 u32HandleNo, HI_U32 u32HshpDemoMode);




#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __PQ_HAL_SHARPEN_H__ */

