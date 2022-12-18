/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_sr.h
  Version       : Initial Draft
  Author        : y00220178
  Created       : 2014/01/16
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_SR_H__
#define __PQ_HAL_SR_H__

#include "hi_type.h"
#include "pq_hal_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


/* sr_disp_state: SR支持四种显示状态 */
typedef enum hiSR_ZME_E
{
    SR_AND_ZME_EN = 0x0 , /* 正常显示，ZME+SR */ /*全屏*/
    SR_ONLY_ZME_EN      , /* 正常显示，ZME */    /*关掉SR,只ZME*/
    SR_AND_ZME_EN_L     , /* demo显示，左边ZME+SR ，右边ZME */ /*左边SR*/
    SR_AND_ZME_EN_R     , /* demo显示，左边ZME ，右边ZME+SR */ /*右边SR*/

    SR_ZME_EN_BUTT
} SR_ZME_E;

/*SR演示模式*/
typedef enum hiDRV_SR_DEMO_E
{
    DRV_SR_DISABLE  = 0 , /* 关掉SR,只ZME */
    DRV_SR_ENABLE_R     , /* 右边SR */
    DRV_SR_ENABLE_L     , /* 左边SR */
    DRV_SR_ENABLE_A     , /* 全屏 */

    DRV_SR_DEMO_BUTT
} DRV_SR_DEMO_E;


/*
typedef enum hiSR_ZME_E
{
    SR_AND_ZME_EN = 0x0 ,
    SR_AND_ZME_EN_L     ,
    SR_AND_ZME_EN_R     ,
    SR_ONLY_ZME_EN      ,

    SR_ZME_EN_BUTT
} SR_ZME_E;
*/

/*
typedef enum hiSR_DEMO_MODE_E
{
    SR_DEMO_EN = 0x0 ,
    SR_DEMO_EN_L     ,
    SR_DEMO_EN_R     ,

    SR_DEMO_EN_BUTT
} SR_DEMO_MODE_E;
*/

typedef enum tagVDP_WBC_LOCATE_E
{
    VDP_WBC_LOCATE_CBM1 = 0x0 ,
    VDP_WBC_LOCATE_CBM2 = 0x1 ,

    VDP_WBC_LOCATE_E_BUTT
} VDP_WBC_LOCATE_E;

/*
typedef enum hiSR_SERVE_MODE_E
{
    SR_2IN_2OUT = 0x0  ,
    SR_1IN_2OUT        ,
    SR_1IN_1OUT        ,
    
    SR_SERVE_MODE_BUTT
} SR_SERVE_MODE_E;
*/
typedef enum hiSR_SHARP_MODE_E
{
    SR_SHARP_MODE_DETAIL = 0x0 , /* 细节增强 */
    SR_SHARP_MODE_TRAD         , /* 方向增强 */
    
    SR_SHARP_MODE_BUTT
} SR_SHARP_MODE_E;

typedef enum hiVDP_SR_E
{
    VDP_SR_UENABLE = 0x0 ,
    VDP_SR_ENABLE        ,
    
    VDP_SR_BUTT
} SR_E;

typedef enum hiSR_SHARP_E
{
    SR_SHARP_UENABLE = 0x0 ,
    SR_SHARP_ENABLE        ,
    
    SR_SHARP_BUTT
} SR_SHARP_E;

/*
typedef enum hiSR_SHARP_E
{
    SR_SHARP_UENABLE = 0x0 ,
    SR_SHARP_R_ENABLE      ,
    SR_SHARP_L_ENABLE      ,
    SR_SHARP_ENABLE        ,

    SR_SHARP_BUTT
} SR_SHARP_E;
*/
typedef enum hiSR_SMOOTH_E
{
    SR_SMOOTH_UENABLE = 0x0 ,
    SR_SMOOTH_ENABLE        ,
    
    SR_SMOOTH_BUTT
} SR_SMOOTH_E;

typedef enum hiSR_PLUS_E
{
    VDP_SR_PLUS_UENABLE = 0x0 ,
    VDP_SR_PLUS_ENABLE        ,
    
    VDP_SR_PLUS_BUTT
} SR_PLUS_E;


/*SR参数结构*/
typedef struct hiSR_PARA_S
{
    HI_U32              u32sr_en;             /* SR使能。0：禁止；1：使能 */
    SR_ZME_E            sr_zme_en;            /* SR支持四种显示状态 */
    SR_SHARP_E          sharp_en;             /* 锐化使能。0：不使能；1：使能 */
    SR_SHARP_MODE_E     hsh_nodir;            /* 增强模式。0：细节增强；1：方向增强 */
    HI_U16              u16grd_sub_ratio;     /* 方向梯度差值融合系数 */
    HI_S16              s16grd_thrl;          /* 边缘强度低阈值 */
    HI_S16              s16grd_thrh;          /* 边缘强度高阈值 */
    HI_U8               u8grd_thrh_subl;      /* 边缘强度斜率 */
    HI_U8               u8grd_add_ctrl;       /* 边缘强度乘法因子 */
    HI_U16              u16disc_detail_gain;  /* 插值到scaler的细节强度 */
    HI_U16              u16ensc_detail_gain;  /* 细节叠加方法的增强强度 */
    HI_U8               u8sharp_coring;       /* coring控制阈值 */
    HI_U16              u16sharp_gain;        /* 锐化强度寄存器 */
    HI_U8               u8over_thrsh;         /* 增强高阈值 */
    HI_U8               u8under_thrsh;        /* 增强低阈值 */
    HI_BOOL             bsmooth_en;           /* 水平平滑使能。0：禁止；1：使能 */
    HI_BOOL             bplus_en;             /* 突变点使能。0：禁止；1：使能 */
    HI_U16              u16plus_ctrl;         /* 突变点控制 */
} SR_PARA_S;


/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_GetSRParam(SR_PARA_S *pstsrPara)
Description     : 获取SR寄存器值
Calls           :
Data Accessed   :
Data Updated    :
Input           : NA
Output          : *pstsrPara     SR配置参数
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_GetSRParam(PQ_HAL_LAYER_VP_E u32ChId, SR_PARA_S* pstsrPara);


/*--------------------------------------------------------------------------------*
Function        : HI_VOID PQ_HAL_SetSRParam(HI_U32 u32ChId, SR_PARA_S* pstSRPara)

Description     : 设置SR寄存器值
Calls           :
Data Accessed   :
Data Updated    :
Input           : pstSRPara     SR配置参数
Output          : NA
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_VOID PQ_HAL_SetSRParam(HI_U32 u32ChId, SR_PARA_S* pstSRPara);



/**
 \brief 获取开关SR模块
 \attention \n
无

 \param[out] *bOnOff

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_GetSREnable(HI_U32 u32ChId, HI_BOOL* bOnOff);


/**
 \brief 开关SR模块
 \attention \n
无

 \param[in] bOnOff

 \retval ::

 */
HI_VOID PQ_HAL_EnableSR(HI_U32 u32ChId, HI_BOOL bOnOff);


/**
 \brief 开关SR模块ZME DEMO模式
 \attention \n

 \param[in] SR_ZME_E enZme

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_SR_EnZme(HI_U32 u32ChId, SR_ZME_E enZme);


/**
 \brief SR模块中的Sharpen的模块增强和细节增强
 \attention \n

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_SetSRSpMode(HI_U32 u32ChId, SR_SHARP_MODE_E eHsh_nodir);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
