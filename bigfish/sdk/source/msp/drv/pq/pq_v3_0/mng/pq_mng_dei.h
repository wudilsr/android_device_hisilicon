/******************************************************************************
 Copyright (C), 2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mng_pq_dei.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2013/10/12
Last Modified :
Description   : PQ MNG层DEI模块的数据结构和接口函数
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
    HI_U32 u32GlobalMotion; /* TNR 计算值 */
    HI_U32 u32AdjustGain;   /* Global Motion 调整值 */
} MOTION_RESULT_S; //MotionResult_S;


/**
 \brief 初始化DEI硬件参数
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DEI_ParaInit(HI_VOID);


/**
 \brief 初始化DEI模块;
 \attention \n

 \param[in] pstDeiParameter, Dei初始化参数配置

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitDei(HI_VOID);

/**
 \brief 去初始化DEI模块;
 \attention \n


 \param[in]

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DeInitDei(HI_VOID);

/**
 \brief 获取Globalmotion信息;
 \attention \n

 \param[in] :MOTION_HIST_OUT_S *pstMotionHist 寄存器获得的motion hist信息
            :MOTION_RESULT_S *pstMotionResult 软件计算gain值和globalmotion
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

