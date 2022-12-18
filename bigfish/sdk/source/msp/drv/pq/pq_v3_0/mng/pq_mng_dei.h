/******************************************************************************
 Copyright (C), 2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mng_pq_dei.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2013/10/12
Last Modified :
Description   : PQ MNG��DEIģ������ݽṹ�ͽӿں���
Function List :
History       :
******************************************************************************/

#ifndef __PQ_MNG_DEI_H__
#define __PQ_MNG_DEI_H__

#include "hi_type.h"
#include "pq_hal_dei.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

//output of logic
typedef struct
{
    //HI_U32 au32MotionHist[32];
    HI_S32 s32WidthY;
    HI_S32 s32HeightY;

    HI_U32 u32SmallMotionNum; /* output of logic,32bit unsigned */
    HI_U32 u32SmallMotionSum; /* output of logic,32bit unsigned */
    HI_U32 u32LargeMotionNum; /* output of logic,32bit unsigned */
    HI_U32 u32LargeMotionSum; /* output of logic,32bit unsigned */
    HI_U32 u32MiddlMotionNum; /* output of logic,32bit unsigned */
    HI_U32 u32MiddlMotionSum; /* output of logic,32bit unsigned */
} MOTION_HIST_OUT_S; //MotionHistOut_S


typedef struct
{
    HI_U32 u32GlobalMotion; /* TNR ����ֵ */
    HI_U32 u32AdjustGain;   /* Global Motion ����ֵ */
} MOTION_RESULT_S; //MotionResult_S;


/**
 \brief ��ʼ��DEIӲ������
 \attention \n
��

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DEI_ParaInit(HI_VOID);


/**
 \brief ��ʼ��DEIģ��;
 \attention \n

 \param[in] pstDeiParameter, Dei��ʼ����������

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitDei(HI_VOID);

/**
 \brief ȥ��ʼ��DEIģ��;
 \attention \n


 \param[in]

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DeInitDei(HI_VOID);

/**
 \brief ��ȡGlobalmotion��Ϣ;
 \attention \n

 \param[in] :MOTION_HIST_OUT_S *pstMotionHist �Ĵ�����õ�motion hist��Ϣ
            :MOTION_RESULT_S *pstMotionResult �������gainֵ��globalmotion
 \retval ::

 */

HI_S32 PQ_MNG_GetGlobalMotion(MOTION_INPUT_S* pstMotionInput);

HI_S32 PQ_MNG_SetInterlaceMotionEn(HI_U32 u32HandleNo, HI_BOOL bIglben);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*End of #ifndef __MNG_PQ_DEI_H__ */

