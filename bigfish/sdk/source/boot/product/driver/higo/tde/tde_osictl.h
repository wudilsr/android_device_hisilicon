/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : tde_osictl.h
Version             : Initial Draft
Author              : 
Created             : 2014/08/06
Description         : 
Function List       : 
History             :
Date                       Author                   Modification
2014/08/06                 y00181162                Created file        
******************************************************************************/

#ifndef _TDE_OSICTL_H_
#define _TDE_OSICTL_H_


/*********************************add include here******************************/
#include "hi_tde_type.h"


/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/

/*****************************************************************************
* Function:      TdeOsiBeginJob
* Description:   获得TDE 任务句柄
* Input:         ps32Handle:获取任务句柄的指针
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiBeginJob(TDE_HANDLE *ps32Handle);

/*****************************************************************************
* Function:      TdeOsiEndJob
* Description:   提交TDE任务
* Input:         s32Handle: 任务句柄
*                bBlock: 是否阻塞
*                u32TimeOut: 超时时间值(10ms为单位)
*                bSync: 提交的是同步操作还是异步操作
*                pFuncComplCB: 完成操作回调函数
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiEndJob(TDE_HANDLE s32Handle, HI_BOOL bBlock, HI_U32 u32TimeOut, 
                    HI_BOOL bSync, TDE_FUNC_CB pFuncComplCB, HI_VOID *pFuncPara);

/*****************************************************************************
* Function:      TdeOsiCancelJob
* Description:   删除创建的TDE任务,只能在EndJob之前调用才会有效,
*                用于释放相应的任务对应的链表的软件资源
* Input:         s32Handle: 任务句柄
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiCancelJob(TDE_HANDLE s32Handle);


/*****************************************************************************
* Function:      TdeOsiQuickFill
* Description:   快速将固定值填充到目标位图，
* Input:         s32Handle: 任务句柄
*                pDst: 目标位图信息结构
*                pstDstRect: 目标位图操作区域
*                u32FillData: 填充值信息，象素格式要和目标位图保持一致
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiQuickFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect,
                           HI_U32 u32FillData);

/*****************************************************************************
* Function:      TdeOsiBlit
* Description:   将pstBackGround与pstForeGround的位图进行运算将结果输出到pDst中，运算设置在pOpt
* Input:         s32Handle: 任务句柄
*                pstBackGround: 背景位图信息结构
*                pstBackGroundRect: 背景位图操作区域
*                pstForeGround: 前景位图信息结构
*                pstForeGroundRect: 前景位图操作区域
*                pstDst:  目标位图信息结构
*                pstDstRect:  目标位图操作区域
*                pOpt:  运算参数设置结构
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiBlit(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                          TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect, TDE2_SURFACE_S* pstDst,
                          TDE2_RECT_S  *pstDstRect, TDE2_OPT_S* pOpt);

/*****************************************************************************
* Function:      TdeOsiMbBlit
* Description:   宏块处理接口
* Input:         s32Handle: 任务句柄
*                pstMB: 宏块位图信息结构
*                pstMbRect: 宏块位图操作区域
*                pstDst: 目的位图信息结构
*                pstDstRect:  目标位图操作区域
*                pstMbOpt:  运算参数设置结构
* Output:        无
* Return:        >0: 返回当前操作所属任务的id ; <0: 失败
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiMbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, 
                        TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect, TDE2_MBOPT_S* pstMbOpt);

/*****************************************************************************
* Function:      TdeOsiSetAlphaThreshold
* Description:   设置alpha判决阈值
* Input:         无
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiSetAlphaThresholdValue(HI_U8 u8ThresholdValue);


/*****************************************************************************
* Function:      TdeOsiSetAlphaThresholdState
* Description:   设置alpha判决开关
* Input:         bEnAlphaThreshold:是否打开alpha判决标识
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiSetAlphaThresholdState(HI_BOOL bEnAlphaThreshold);


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __TDE_OSICTL_H__ */
