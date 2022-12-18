/******************************************************************************
 Copyright (C), 2001-2012, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mng_pq_sr.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2014/01/16
Last Modified :
Description   : PQ MNG层SR模块的数据结构和接口函数
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
    SR_DISABLE  = 0, /* 关掉SR,只ZME */
    SR_ENABLE_R,     /* 右边SR */
    SR_ENABLE_L,     /* 左边SR */
    SR_ENABLE_A,     /* 全屏 */

    SR_DEMO_BUTT
} SR_DEMO_E;


/**
 \brief 初始化SR模块
 \attention \n

 \param[in] none;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_InitSR(HI_VOID);


/**
 \brief 去初始化SR模块
 \attention \n

 \param[in] none;

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_DeinitSR(HI_VOID);



/**
 \brief 开关SR模块
 \attention \n

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableSR(HI_BOOL bOnOff);


/**
 \brief 获取SR模块DEMO模式
 \attention \n

 \param[in] *pu32Type

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetSRDemo(HI_U32* pu32Type);


/**
 \brief 开关SR模块DEMO模式
 \attention \n

 \param[in] democtrl

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableSRDemo(SR_DEMO_E edemoctrl);


/**
 \brief SR模块中的Sharpen的模块增强和细节增强
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


