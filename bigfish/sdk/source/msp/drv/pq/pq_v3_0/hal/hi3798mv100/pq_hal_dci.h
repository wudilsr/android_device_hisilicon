/******************************************************************************
  *
  * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
  *
  * This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
  *  and may not be copied, reproduced, modified, disclosed to others, published or used, in
  * whole or in part, without the express prior written permission of Hisilicon.
  *
******************************************************************************
  File Name     : pq_hal_dci.h
  Version       : Initial Draft
  Author        : l00212594
  Created       : 2013/04/20
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_DCI_H__
#define __PQ_HAL_DCI_H__

#include "hi_type.h"
#include "pq_hal_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


/*DCI�����ṹ*/
typedef struct hiDCI_PARA_S
{   
    HI_U32 u32DCIYLinear;       /* full rangͳ��ֵ */
    HI_U8  u8DCIStateCtrl;      /* ֱ��ͼͳ��ģʽ���ơ�00����DCI�㷨����ȫͳ�ƣ�01����DCI�㷨����ֻͳ��ż���㡣10����DCI�㷨����ֻͳ��ż���㣬11����ͳ�ƣ�DCI��ʹ�ܣ�*/
    HI_U8  u8DCIHistState;      /* 0��Ŀǰ����������������ܶ�ȡӲ��ֱ��ͼͳ�ƵĽ��  1��Ŀǰ����������������Զ�ȡӲ��ֱ��ͼͳ�ƵĽ�� */
    HI_U8  u8DCISwCfgEn;        /* 0��ѡ��Ӳ������õ������� 1��ѡ��������õ����� */
    HI_U8  u8DCIHistLpfEn;      /* ֱ��ͼ��ͨ�˲������źš�0����ʹ�� 1��ʹ�� */
    HI_U8  u8DCIShiftCtrl;      /* 00������6λ��01������7λ��10������8λ��11������9λ��*/
    HI_U8  u8DCIOutRange;       /* �����Χ���ã�0��limit range�������10bit�������ݷ�Χ��Y-64~940��C-64~960��1��full  range�������10bit�������ݷ�Χ��Y-0~1023��C-0~1023�� */
    HI_U8  u8DCIInRange;        /* ���뷶Χ���ã�0��limit range�������10bit�������ݷ�Χ��Y-64~940��C-64~960��1��full  range�������10bit�������ݷ�Χ��Y-0~1023��C-0~1023�� */
    HI_U8  u8DCICbCrStaEn;      /* ֱ��ͼͳ��ѡ���źţ�0���������ȷ�������ֱ��ͼͳ�ơ�1����YCbCr����������Ȩ��ķ�������ֱ��ͼͳ�ơ� */
    HI_U8  u8DCICbCrCmpEn;      /* DCI ɫ�Ȳ���ʹ�ܣ�0��DCI�㷨����ɫ�ȷ������е��ڡ�1��DCI�㷨��ɫ�ȷ������е��ڡ� */
    HI_U8  u8DCIManAdj[3];      /* ����0/1/2����ģʽѡ��0���Զ�ģʽ��ʹ��Ӳ������Ľ����1���ֶ�ģʽ��ʹ��������õĽ���� */
    HI_U8  u8DCISceneFlg;       /* DCI �����л�ʹ���źţ�0����ʹ��1��ʹ�� */
    HI_U8  u8DCIDbgMode;        /* DCI demoģʽ��0����Ļ���Ϊԭʼͼ���ұ�ΪDCI�������ͼ��1����Ļ���ΪDCI�������ͼ���ұ�Ϊԭʼͼ��*/
    HI_U8  u8DCIDbgEn;          /* DCI demoģʽʹ���źš�0����ʹ��1����Ļ�����ʾԭʼͼ���ұ�ΪDCI������ͼ�� */
    HI_U8  u8DCIEn;             /* DCIģ��ʹ�ܼĴ�����0��DCI���ܹرգ�����bypass�����1��DCI����ʹ�ܣ�ʵ�����ȶԱȶȵ��ڡ� */
    HI_U16 u16DCIHEnd;          /* DCI�㷨ˮƽ��������Ľ���ֵ */
    HI_U16 u16DCIHStart;        /* DCI�㷨ˮƽ�����������ʼֵ */
    HI_U16 u16DCIVEnd;          /* DCI�㷨��ֱ�����������ʼֵ */
    HI_U16 u16DCIVStart;        /* DCI�㷨��ֱ��������Ľ���ֵ */
    HI_S8  s8DCICbCrStaCr;      /* ֱ��ͼͳ�Ƶ���ʱ��cr�����ļ�Ȩϵ����8bit�з����������bitΪ����λ�� */
    HI_S8  s8DCICbCrStaCb;      /* ֱ��ͼͳ�Ƶ���ʱ��cb�����ļ�Ȩϵ����8bit�з����������bitΪ����λ�� */
    HI_S8  s8DCICbCrStaY;       /* ֱ��ͼͳ�Ƶ���ʱ��Y�����ļ�Ȩϵ����8bit�з����������bitΪ����λ�� */
    HI_S16 s16DCICbCrStaOft;    /* ֱ��ͼͳ�Ƶ���ʱ��ƫ������9bit�з����������bit�Ƿ���λ */
    HI_U8  u8DCIHistCorTh[3];   /* ֱ��ͼ0/1/2 coring����ֵ */
    HI_U8  u8DCIOrgAbld;        /* ���ȷ�������ʱ��alpha blendֵ */
    HI_U8  u8DCIHistAbld;       /* ��ǰֱ��ͼ��ǰһֱ֡��ͼalphablend�ļ�Ȩֵ */
    HI_U8  u8DCIMetrAbld[3];    /* Metric 0/1/2 alphablend��ǰ֡�ļ�Ȩֵ */
    HI_U8  u8DCIManAdjWgt[3];   /* ���ֶ�ģʽ�£���������0/1/2��Ȩ��ֵ */
    HI_U8  u8DCIWgtClipHigh[3]; /* ����0/1/2Ȩ��ֵ������ */
    HI_U8  u8DCIWgtClipLow[3];  /* ����0/1/2Ȩ��ֵ������ */
    HI_U8  u8DCIGlbGain[3];     /* ���ȷ�������ʱ��ȫ������0/1/2 */
    HI_U8  u8DCIGainPosTh[9];   /* ͼ���ɰ���������ʱ������Y����ֵ0-8 */
    HI_U8  u8DCIGainPosCbCr[9]; /* ͼ���ɰ���������ʱ����ֵ0-8��ɫ�Ȳ������� */
    HI_S16 s16DCIGainPosSlp[8]; /* ͼ���ɰ���������ʱ������1-8��б�ʣ�10bit�з����� */
    HI_U8  u8DCIGainNegTh[9];   /* ͼ�������䰵����ʱ������Y����ֵ0-8 */
    HI_U8  u8DCIGainNegCbCr[9]; /* ͼ�������䰵����ʱ����ֵ0-8��ɫ�Ȳ������� */
    HI_S16 s16DCIGainNegSlp[8]; /* ͼ�������䰵����ʱ������1-8��б�ʣ�10bit�з����� */
    HI_S16 s16DCIAdjSw[33];     /* �ֶ����õĵ���������ֵ0-32��10bit�з����� */
    HI_U8  u8DCILutRdEn;        /* DCIֱ��ͼ��Ȩϵ�����ұ��ʹ��: 0����ֹ��1��ʹ�ܡ�*/
    HI_U8  u8DCIDivRdEn;        /* DCI�������ұ��ʹ��: 0����ֹ��1��ʹ�ܡ�*/
    HI_U8  u8DCIHbwRdEn;        /* DCIֱ��ͼͳ��ֵ�Ĵ�����ʹ��: 0����ֹ��1��ʹ�ܡ�*/
    
} DCI_PARA_S;

/*DCI LUT��ṹ*/
typedef struct hiDCI_LUT_S
{
    HI_S16 s16HistCoef0[32];  /* ֱ��ͼ��Ȩϵ��0 */
    HI_S16 s16HistCoef1[32];  /* ֱ��ͼ��Ȩϵ��1 */
    HI_S16 s16HistCoef2[32];  /* ֱ��ͼ��Ȩϵ��2 */
    HI_S16 s16YDivCoef[64];   /* ������ */
    HI_S16 s16WgtCoef0[33];   /* DCI weight LUT0 */
    HI_S16 s16WgtCoef1[33];   /* DCI weight LUT1 */
    HI_S16 s16WgtCoef2[33];   /* DCI weight LUT2 */
    HI_U16 u16Reserve;
} DCI_LUT_S;


/*DCI�������ñ�*/
typedef struct hiDCI_WGT_S
{
    HI_S16 s16WgtCoef0[33];
    HI_S16 s16WgtCoef1[33];
    HI_S16 s16WgtCoef2[33];
    HI_U16 u16Gain0;
    HI_U16 u16Gain1;
    HI_U16 u16Gain2;
} DCI_WGT_S;

/*DCIֱ��ͼ�ṹ*/
typedef struct hiDCI_HISTGRAM_S
{
    HI_S32 s32HistGram[32];
} DCI_HISTGRAM_S;

/*DCI��������*/
typedef struct hiDCI_WINDOW_S
{
    HI_U16 u16Hstart;
    HI_U16 u16Hend;
    HI_U16 u16Vstart;
    HI_U16 u16Vend;
} DCI_WINDOW_S;


/**
 \brief ��ʼ��DCIģ��
 \attention \n
��

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_DCIInit(HI_VOID);


/**
 \brief ȥ��ʼ��DCIģ��;
 \attention \n
��

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_DCIDeinit(HI_VOID);

/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_GetDCIParam(DCI_PARA_S *pstdciPara)
Description     : ��ȡDCI�Ĵ���ֵ
Calls           :
Data Accessed   :
Data Updated    :
Input           : NA
Output          :*pstdciPara     DCI�Ĳ���
Return          :NA
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_GetDCIParam(PQ_HAL_LAYER_VP_E u32ChId, DCI_PARA_S* pstdciPara);


/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_SetDCIParam(DCI_PARA_S *pstdciPara)
Description     :����DCI�Ĵ���ֵ
Calls           :
Data Accessed   :
Data Updated    :
Input           : *pstdciPara     DCI���ò���
Output          :NA
Return          :NA
Others          :NA
*--------------------------------------------------------------------------------*/
HI_VOID PQ_HAL_SetDCIParam(PQ_HAL_LAYER_VP_E u32ChId, DCI_PARA_S* pstdciPara);


/**
 \brief ��������ģʽ;
 \attention \n
��

 \param[in] bOnOff

 \retval ::

 */
HI_VOID PQ_HAL_DCIDemoMode(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff);

/**
 \brief ��ȡ����DCIģ��
 \attention \n
��

 \param[out] *bOnOff

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_GetDCIEnable(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL* bOnOff);


/**
 \brief ����DCIģ��
 \attention \n
��

 \param[in] bOnOff

 \retval ::

 */
HI_VOID PQ_HAL_EnableDCI(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff);


/**
 \brief ��ȡDCIǿ��
 \attention \n
��

 \param[out] pu16Gain0,pu16Gain1,pu16Gain2

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_GetDCIlevel(PQ_HAL_LAYER_VP_E u32ChId, HI_U16* pu16Gain0, HI_U16* pu16Gain1, HI_U16* pu16Gain2);


/**
 \brief ����DCIǿ��
 \attention \n
��

 \param[in] u16Gain0,u16Gain1,u16Gain2

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_SetDCIlevel(PQ_HAL_LAYER_VP_E u32ChId, HI_U16 u16Gain0, HI_U16 u16Gain1, HI_U16 u16Gain2);


/**
 \brief ����DCIͳ�ƴ���
 \attention \n
��

 \param[in] u16HStar,u16HEnd,u16VStar,u16VEnd

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_SetDCIWindow(PQ_HAL_LAYER_VP_E u32ChId, HI_U16 u16HStar, HI_U16 u16HEnd, HI_U16 u16VStar, HI_U16 u16VEnd);

/*--------------------------------------------------------------------------------*
Function        :HI_S32 PQ_HAL_SetDCIWgtLut(DCI_WGT_S *pstDciCoef)
Description     : ����DCI��������
Calls           :
Data Accessed   :
Data Updated    :
Input           :*pstDciCoef
Output          :NA
Return          :NA
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_SetDCIWgtLut(DCI_WGT_S* pstDciCoef);


/*--------------------------------------------------------------------------------*
Function        :HI_S32 PQ_HAL_GetDCIWgtLut(DCI_WGT_S *pstDciCoef)
Description     :��ȡDCI��������
Calls           :
Data Accessed   :
Data Updated    :
Input           :NA
Output          :*pstDciCoef
Return          :NA
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_GetDCIWgtLut(DCI_WGT_S* pstDciCoef);

/*--------------------------------------------------------------------------------*
Function        :HI_VOID PQ_HAL_SetDCILut(DCI_LUT_S *pstDciLut)
Description     : ����DCI��LUT
Calls           :
Data Accessed   :
Data Updated    :
Input           :*pstDciLut
Output          :NA
Return          :NA
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_SetDCILut(DCI_LUT_S* pstDciLut);

/*--------------------------------------------------------------------------------*
Function        :HI_S32 PQ_HAL_GetDCIHistgram(DCI_HISTGRAM_S *pstDciHist)
Description     :��ȡDCI��������
Calls           :
Data Accessed   :
Data Updated    :
Input           :NA
Output          :*pstDciHist
Return          :NA
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_GetDCIHistgram(DCI_HISTGRAM_S* pstDciHist);

HI_VOID PQ_HAL_UpdateDCICoef(PQ_HAL_LAYER_VP_E u32ChId);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
