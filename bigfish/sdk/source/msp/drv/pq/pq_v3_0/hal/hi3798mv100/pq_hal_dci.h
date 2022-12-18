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


/*DCI参数结构*/
typedef struct hiDCI_PARA_S
{   
    HI_U32 u32DCIYLinear;       /* full rang统计值 */
    HI_U8  u8DCIStateCtrl;      /* 直方图统计模式控制。00：在DCI算法区域全统计；01：在DCI算法区域只统计偶数点。10：在DCI算法区域只统计偶数点，11：不统计（DCI不使能）*/
    HI_U8  u8DCIHistState;      /* 0：目前在像素区域，软件不能读取硬件直方图统计的结果  1：目前在消隐区，软件可以读取硬件直方图统计的结果 */
    HI_U8  u8DCISwCfgEn;        /* 0：选择硬件计算得到的曲线 1：选择软件配置的曲线 */
    HI_U8  u8DCIHistLpfEn;      /* 直方图低通滤波是能信号。0：不使能 1：使能 */
    HI_U8  u8DCIShiftCtrl;      /* 00：右移6位；01：右移7位；10：右移8位；11：右移9位；*/
    HI_U8  u8DCIOutRange;       /* 输出范围配置：0：limit range，输出的10bit像素数据范围是Y-64~940，C-64~960。1：full  range，输出的10bit像素数据范围是Y-0~1023，C-0~1023。 */
    HI_U8  u8DCIInRange;        /* 输入范围配置：0：limit range，输入的10bit像素数据范围是Y-64~940，C-64~960。1：full  range，输入的10bit像素数据范围是Y-0~1023，C-0~1023。 */
    HI_U8  u8DCICbCrStaEn;      /* 直方图统计选择信号：0：仅对亮度分量进行直方图统计。1：对YCbCr三个分量加权后的分量进行直方图统计。 */
    HI_U8  u8DCICbCrCmpEn;      /* DCI 色度补偿使能：0：DCI算法不对色度分量进行调节。1：DCI算法对色度分量进行调节。 */
    HI_U8  u8DCIManAdj[3];      /* 曲线0/1/2调整模式选择：0：自动模式，使用硬件计算的结果。1：手动模式，使用软件配置的结果。 */
    HI_U8  u8DCISceneFlg;       /* DCI 场景切换使能信号：0：不使能1：使能 */
    HI_U8  u8DCIDbgMode;        /* DCI demo模式。0：屏幕左边为原始图像，右边为DCI调整后的图像；1：屏幕左边为DCI调整后的图像，右边为原始图像。*/
    HI_U8  u8DCIDbgEn;          /* DCI demo模式使能信号。0：不使能1：屏幕左边显示原始图像，右边为DCI处理后的图像。 */
    HI_U8  u8DCIEn;             /* DCI模块使能寄存器：0：DCI功能关闭，数据bypass输出。1：DCI功能使能，实现亮度对比度调节。 */
    HI_U16 u16DCIHEnd;          /* DCI算法水平作用区域的结束值 */
    HI_U16 u16DCIHStart;        /* DCI算法水平作用区域的起始值 */
    HI_U16 u16DCIVEnd;          /* DCI算法垂直作用区域的起始值 */
    HI_U16 u16DCIVStart;        /* DCI算法垂直作用区域的结束值 */
    HI_S8  s8DCICbCrStaCr;      /* 直方图统计叠加时，cr分量的加权系数。8bit有符号数，最高bit为符号位。 */
    HI_S8  s8DCICbCrStaCb;      /* 直方图统计叠加时，cb分量的加权系数。8bit有符号数，最高bit为符号位。 */
    HI_S8  s8DCICbCrStaY;       /* 直方图统计叠加时，Y分量的加权系数。8bit有符号数，最高bit为符号位。 */
    HI_S16 s16DCICbCrStaOft;    /* 直方图统计叠加时的偏移量。9bit有符号数，最高bit是符号位 */
    HI_U8  u8DCIHistCorTh[3];   /* 直方图0/1/2 coring的阈值 */
    HI_U8  u8DCIOrgAbld;        /* 亮度分量调节时的alpha blend值 */
    HI_U8  u8DCIHistAbld;       /* 当前直方图和前一帧直方图alphablend的加权值 */
    HI_U8  u8DCIMetrAbld[3];    /* Metric 0/1/2 alphablend当前帧的加权值 */
    HI_U8  u8DCIManAdjWgt[3];   /* 在手动模式下，配置曲线0/1/2的权重值 */
    HI_U8  u8DCIWgtClipHigh[3]; /* 曲线0/1/2权重值的上限 */
    HI_U8  u8DCIWgtClipLow[3];  /* 曲线0/1/2权重值的下限 */
    HI_U8  u8DCIGlbGain[3];     /* 亮度分量调节时的全局增益0/1/2 */
    HI_U8  u8DCIGainPosTh[9];   /* 图像由暗变亮调整时，亮度Y的阈值0-8 */
    HI_U8  u8DCIGainPosCbCr[9]; /* 图像由暗变亮调整时，阈值0-8的色度补偿增益 */
    HI_S16 s16DCIGainPosSlp[8]; /* 图像由暗变亮调整时，区间1-8的斜率，10bit有符号数 */
    HI_U8  u8DCIGainNegTh[9];   /* 图像由亮变暗调整时，亮度Y的阈值0-8 */
    HI_U8  u8DCIGainNegCbCr[9]; /* 图像由亮变暗调整时，阈值0-8的色度补偿增益 */
    HI_S16 s16DCIGainNegSlp[8]; /* 图像由亮变暗调整时，区间1-8的斜率，10bit有符号数 */
    HI_S16 s16DCIAdjSw[33];     /* 手动配置的调整曲线阈值0-32，10bit有符号数 */
    HI_U8  u8DCILutRdEn;        /* DCI直方图加权系数查找表读使能: 0：禁止；1：使能。*/
    HI_U8  u8DCIDivRdEn;        /* DCI除法查找表读使能: 0：禁止；1：使能。*/
    HI_U8  u8DCIHbwRdEn;        /* DCI直方图统计值寄存器读使能: 0：禁止；1：使能。*/
    
} DCI_PARA_S;

/*DCI LUT表结构*/
typedef struct hiDCI_LUT_S
{
    HI_S16 s16HistCoef0[32];  /* 直方图加权系数0 */
    HI_S16 s16HistCoef1[32];  /* 直方图加权系数1 */
    HI_S16 s16HistCoef2[32];  /* 直方图加权系数2 */
    HI_S16 s16YDivCoef[64];   /* 除法表 */
    HI_S16 s16WgtCoef0[33];   /* DCI weight LUT0 */
    HI_S16 s16WgtCoef1[33];   /* DCI weight LUT1 */
    HI_S16 s16WgtCoef2[33];   /* DCI weight LUT2 */
    HI_U16 u16Reserve;
} DCI_LUT_S;


/*DCI曲线配置表*/
typedef struct hiDCI_WGT_S
{
    HI_S16 s16WgtCoef0[33];
    HI_S16 s16WgtCoef1[33];
    HI_S16 s16WgtCoef2[33];
    HI_U16 u16Gain0;
    HI_U16 u16Gain1;
    HI_U16 u16Gain2;
} DCI_WGT_S;

/*DCI直方图结构*/
typedef struct hiDCI_HISTGRAM_S
{
    HI_S32 s32HistGram[32];
} DCI_HISTGRAM_S;

/*DCI窗口配置*/
typedef struct hiDCI_WINDOW_S
{
    HI_U16 u16Hstart;
    HI_U16 u16Hend;
    HI_U16 u16Vstart;
    HI_U16 u16Vend;
} DCI_WINDOW_S;


/**
 \brief 初始化DCI模块
 \attention \n
无

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_DCIInit(HI_VOID);


/**
 \brief 去初始化DCI模块;
 \attention \n
无

 \param[in] none

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_HAL_DCIDeinit(HI_VOID);

/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_GetDCIParam(DCI_PARA_S *pstdciPara)
Description     : 获取DCI寄存器值
Calls           :
Data Accessed   :
Data Updated    :
Input           : NA
Output          :*pstdciPara     DCI的参数
Return          :NA
Others          :NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_GetDCIParam(PQ_HAL_LAYER_VP_E u32ChId, DCI_PARA_S* pstdciPara);


/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_SetDCIParam(DCI_PARA_S *pstdciPara)
Description     :设置DCI寄存器值
Calls           :
Data Accessed   :
Data Updated    :
Input           : *pstdciPara     DCI配置参数
Output          :NA
Return          :NA
Others          :NA
*--------------------------------------------------------------------------------*/
HI_VOID PQ_HAL_SetDCIParam(PQ_HAL_LAYER_VP_E u32ChId, DCI_PARA_S* pstdciPara);


/**
 \brief 开关卖场模式;
 \attention \n
无

 \param[in] bOnOff

 \retval ::

 */
HI_VOID PQ_HAL_DCIDemoMode(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff);

/**
 \brief 获取开关DCI模块
 \attention \n
无

 \param[out] *bOnOff

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_GetDCIEnable(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL* bOnOff);


/**
 \brief 开关DCI模块
 \attention \n
无

 \param[in] bOnOff

 \retval ::

 */
HI_VOID PQ_HAL_EnableDCI(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff);


/**
 \brief 获取DCI强度
 \attention \n
无

 \param[out] pu16Gain0,pu16Gain1,pu16Gain2

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_GetDCIlevel(PQ_HAL_LAYER_VP_E u32ChId, HI_U16* pu16Gain0, HI_U16* pu16Gain1, HI_U16* pu16Gain2);


/**
 \brief 设置DCI强度
 \attention \n
无

 \param[in] u16Gain0,u16Gain1,u16Gain2

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_SetDCIlevel(PQ_HAL_LAYER_VP_E u32ChId, HI_U16 u16Gain0, HI_U16 u16Gain1, HI_U16 u16Gain2);


/**
 \brief 设置DCI统计窗口
 \attention \n
无

 \param[in] u16HStar,u16HEnd,u16VStar,u16VEnd

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_SetDCIWindow(PQ_HAL_LAYER_VP_E u32ChId, HI_U16 u16HStar, HI_U16 u16HEnd, HI_U16 u16VStar, HI_U16 u16VEnd);

/*--------------------------------------------------------------------------------*
Function        :HI_S32 PQ_HAL_SetDCIWgtLut(DCI_WGT_S *pstDciCoef)
Description     : 设置DCI配置曲线
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
Description     :获取DCI配置曲线
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
Description     : 设置DCI的LUT
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
Description     :获取DCI配置曲线
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
