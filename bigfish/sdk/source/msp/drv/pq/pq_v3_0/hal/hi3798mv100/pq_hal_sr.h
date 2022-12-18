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


/* sr_disp_state: SR֧��������ʾ״̬ */
typedef enum hiSR_ZME_E
{
    SR_AND_ZME_EN = 0x0 , /* ������ʾ��ZME+SR */ /*ȫ��*/
    SR_ONLY_ZME_EN      , /* ������ʾ��ZME */    /*�ص�SR,ֻZME*/
    SR_AND_ZME_EN_L     , /* demo��ʾ�����ZME+SR ���ұ�ZME */ /*���SR*/
    SR_AND_ZME_EN_R     , /* demo��ʾ�����ZME ���ұ�ZME+SR */ /*�ұ�SR*/

    SR_ZME_EN_BUTT
} SR_ZME_E;

/*SR��ʾģʽ*/
typedef enum hiDRV_SR_DEMO_E
{
    DRV_SR_DISABLE  = 0 , /* �ص�SR,ֻZME */
    DRV_SR_ENABLE_R     , /* �ұ�SR */
    DRV_SR_ENABLE_L     , /* ���SR */
    DRV_SR_ENABLE_A     , /* ȫ�� */

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
    SR_SHARP_MODE_DETAIL = 0x0 , /* ϸ����ǿ */
    SR_SHARP_MODE_TRAD         , /* ������ǿ */
    
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


/*SR�����ṹ*/
typedef struct hiSR_PARA_S
{
    HI_U32              u32sr_en;             /* SRʹ�ܡ�0����ֹ��1��ʹ�� */
    SR_ZME_E            sr_zme_en;            /* SR֧��������ʾ״̬ */
    SR_SHARP_E          sharp_en;             /* ��ʹ�ܡ�0����ʹ�ܣ�1��ʹ�� */
    SR_SHARP_MODE_E     hsh_nodir;            /* ��ǿģʽ��0��ϸ����ǿ��1��������ǿ */
    HI_U16              u16grd_sub_ratio;     /* �����ݶȲ�ֵ�ں�ϵ�� */
    HI_S16              s16grd_thrl;          /* ��Եǿ�ȵ���ֵ */
    HI_S16              s16grd_thrh;          /* ��Եǿ�ȸ���ֵ */
    HI_U8               u8grd_thrh_subl;      /* ��Եǿ��б�� */
    HI_U8               u8grd_add_ctrl;       /* ��Եǿ�ȳ˷����� */
    HI_U16              u16disc_detail_gain;  /* ��ֵ��scaler��ϸ��ǿ�� */
    HI_U16              u16ensc_detail_gain;  /* ϸ�ڵ��ӷ�������ǿǿ�� */
    HI_U8               u8sharp_coring;       /* coring������ֵ */
    HI_U16              u16sharp_gain;        /* ��ǿ�ȼĴ��� */
    HI_U8               u8over_thrsh;         /* ��ǿ����ֵ */
    HI_U8               u8under_thrsh;        /* ��ǿ����ֵ */
    HI_BOOL             bsmooth_en;           /* ˮƽƽ��ʹ�ܡ�0����ֹ��1��ʹ�� */
    HI_BOOL             bplus_en;             /* ͻ���ʹ�ܡ�0����ֹ��1��ʹ�� */
    HI_U16              u16plus_ctrl;         /* ͻ������ */
} SR_PARA_S;


/*--------------------------------------------------------------------------------*
Function        : HI_S32 PQ_HAL_GetSRParam(SR_PARA_S *pstsrPara)
Description     : ��ȡSR�Ĵ���ֵ
Calls           :
Data Accessed   :
Data Updated    :
Input           : NA
Output          : *pstsrPara     SR���ò���
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_S32 PQ_HAL_GetSRParam(PQ_HAL_LAYER_VP_E u32ChId, SR_PARA_S* pstsrPara);


/*--------------------------------------------------------------------------------*
Function        : HI_VOID PQ_HAL_SetSRParam(HI_U32 u32ChId, SR_PARA_S* pstSRPara)

Description     : ����SR�Ĵ���ֵ
Calls           :
Data Accessed   :
Data Updated    :
Input           : pstSRPara     SR���ò���
Output          : NA
Return          : NA
Others          : NA
*--------------------------------------------------------------------------------*/
HI_VOID PQ_HAL_SetSRParam(HI_U32 u32ChId, SR_PARA_S* pstSRPara);



/**
 \brief ��ȡ����SRģ��
 \attention \n
��

 \param[out] *bOnOff

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_GetSREnable(HI_U32 u32ChId, HI_BOOL* bOnOff);


/**
 \brief ����SRģ��
 \attention \n
��

 \param[in] bOnOff

 \retval ::

 */
HI_VOID PQ_HAL_EnableSR(HI_U32 u32ChId, HI_BOOL bOnOff);


/**
 \brief ����SRģ��ZME DEMOģʽ
 \attention \n

 \param[in] SR_ZME_E enZme

 \retval ::HI_SUCCESS

 */
HI_VOID PQ_HAL_SR_EnZme(HI_U32 u32ChId, SR_ZME_E enZme);


/**
 \brief SRģ���е�Sharpen��ģ����ǿ��ϸ����ǿ
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
