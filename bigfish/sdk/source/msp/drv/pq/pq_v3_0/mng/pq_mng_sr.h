/******************************************************************************
 Copyright (C), 2001-2012, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mng_pq_sr.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2014/01/16
Last Modified :
Description   : PQ MNG��SRģ������ݽṹ�ͽӿں���
Function List :
History       :
******************************************************************************/

#ifndef __PQ_MNG_SR_H__
#define __PQ_MNG_SR_H__

#include "hi_type.h"
#include "pq_hal_sr.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

typedef enum
{
    SR_DISABLE  = 0, /* �ص�SR,ֻZME */
    SR_ENABLE_R,     /* �ұ�SR */
    SR_ENABLE_L,     /* ���SR */
    SR_ENABLE_A,     /* ȫ�� */

    SR_DEMO_BUTT
} SR_DEMO_E;


/**
 \brief ��ʼ��SRģ��
 \attention \n

 \param[in] none;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_InitSR(HI_VOID);


/**
 \brief ȥ��ʼ��SRģ��
 \attention \n

 \param[in] none;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_DeinitSR(HI_VOID);



/**
 \brief ����SRģ��
 \attention \n

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableSR(HI_BOOL bOnOff);


/**
 \brief ��ȡSRģ��DEMOģʽ
 \attention \n

 \param[in] *pu32Type

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetSRDemo(HI_U32* pu32Type);


/**
 \brief ����SRģ��DEMOģʽ
 \attention \n

 \param[in] democtrl

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableSRDemo(SR_DEMO_E edemoctrl);


/**
 \brief SRģ���е�Sharpen��ģ����ǿ��ϸ����ǿ
 \attention \n

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_UpdateSRSpMode(HI_U32 u32Width, HI_U32 u32Hight);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


