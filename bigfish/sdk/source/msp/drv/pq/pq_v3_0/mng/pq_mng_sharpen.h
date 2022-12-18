/******************************************************************************
 Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mng_pq_sharp.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2013/10/12
Last Modified :
Description   : PQ MNG层SHARPEN模块的 数据结构和接口函数
Function List :
History       :
******************************************************************************/

#ifndef __PQ_MNG_SHARPEN_H__
#define __PQ_MNG_SHARPEN_H__

#include "hi_type.h"
#include "pq_hal_sharpen.h"

//#include "drv_pq_define.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */



/**
 \brief 初始化SHARPEN模块
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitSharpen(PQ_PARAM_S* pstPqParam);


/**
 \brief 去初始化SHARPEN模块
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DeinitSharpen(HI_VOID);


/**
 \brief 设置清晰度强度
 \attention \n
无

 \param[in] u32ShpStr  清晰度强度值，取值范围[0,255]

 \retval ::HI_SUCCESS

 */
 HI_S32 PQ_MNG_SetSharpenStr(HI_S32 s32ShpStr, HI_U32 u32SourceMode, HI_U32 u32OutputMode);

/**
 \brief 获取清晰度强度
 \attention \n

 \param[in] none
 \param[out]


 \retval ::清晰度强度,返回值范围[0,255]

 */
HI_S32 PQ_MNG_GetSharpenStr(HI_S32* ps32ShpStr);

/**
 \brief 开关SHARPEN模块
 \attention \n

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableSharpen(HI_U8 u8Enable);

/**
 \brief 获取Sharpen开关
 \attention \n
无

 \param[in]*bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetSharpenEnable(HI_BOOL* pbOnOff);

/**
 \brief 开关SHARPEN模块DEMO模式
 \attention \n

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableSharpenDemo(HI_BOOL bOnOff);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

