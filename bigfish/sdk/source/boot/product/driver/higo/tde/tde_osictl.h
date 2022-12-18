/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tde_osi.h
* Description:TDE osi interface define
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/

#ifndef _TDE_OSICTL_H_
#define _TDE_OSICTL_H_

#include "hi_tde_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */

/****************************************************************************/
/*                             TDE osi ctl functions define                 */
/****************************************************************************/

/*****************************************************************************
* Function:      TdeOsiReset
* Description:   恢复所有状态,释放所有链表
* Input:         无
* Output:        无
* Return:        成功 / 失败
* Others:        无
*****************************************************************************/
HI_VOID TdeOsiReset(HI_VOID);

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
* Function:      TdeOsiSetDeflickerLevel
* Description:   设置抗闪烁级别
* Input:         eDeflickerLevel: 抗闪烁级别
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiSetDeflickerLevel(TDE_DEFLICKER_LEVEL_E eDeflickerLevel);

/*****************************************************************************
* Function:      TdeOsiGetDeflickerLevel
* Description:   获取抗闪烁级别
* Input:         无
* Output:        pDeflickerLevel: 抗闪烁级别
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiGetDeflickerLevel(TDE_DEFLICKER_LEVEL_E *pDeflickerLevel);

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
* Function:      TdeOsiGetAlphaThreshold
* Description:   获取alpha判决阈值
* Input:         无
* Output:        pu8ThresholdValue: alpha判决阈值
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiGetAlphaThresholdValue(HI_U8 * pu8ThresholdValue);

/*****************************************************************************
* Function:      TdeOsiSetAlphaThresholdState
* Description:   设置alpha判决开关
* Input:         bEnAlphaThreshold:是否打开alpha判决标识
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiSetAlphaThresholdState(HI_BOOL bEnAlphaThreshold);

/*****************************************************************************
* Function:      TdeOsiGetAlphaThresholdState
* Description:   获取alpha判决开关
* Input:         pbEnAlphaThreshold:alpha判决开关标识
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiGetAlphaThresholdState(HI_BOOL *pbEnAlphaThreshold);
/*****************************************************************************
* Function:      TdeOsiPatternFill
* Description:   模式填充
* Input:         无
* Output:        s32Handle:任务句柄
                 pstBackGround:背景位图信息
                 pstBackGroundRect:背景操作矩形
                 pstForeGround:前景位图信息
                 pstForeGroundRect:前景位操作矩形
                 pstDst:目标位图信息
                 pstDstRect:目标操作矩形
                 pstOpt:模式填充操作选项
* Return:        成功 / 错误码
* Others:        最大支持pattern宽度为256,高度没有限制
*****************************************************************************/

#if 0
/*****************************************************************************
* Function:      TdeOsiQuickCopy
* Description:   快速从源搬移到目的位图，没有任何功能操作，源和目的操作区域尺寸一样，象素格式一样
* Input:         s32Handle: 任务句柄
*                pSrc: 源位图信息结构
*                pstSrcRect: 源位图操作区域
*                pDst: 目标位图信息结构
*                pstDstRect: 目标位图操作区域
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiQuickCopy(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect,
                           TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect);

/*****************************************************************************
* Function:      TdeOsiQuickResize
* Description:   将源位图的大小缩放为目标位图指定的大小，源和目标可以为同一位图
* Input:         s32Handle: 任务句柄
*                pSrc: 源位图信息结构
*                pstSrcRect: 源位图操作区域
*                pDst: 目标位图信息结构
*                pstDstRect: 目标位图操作区域
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiQuickResize(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect,
                             TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect);


/*****************************************************************************
* Function:      TdeOsiQuickFlicker
* Description:   将源位图进行抗闪烁，输出到目标位图，源和目标可以为同一位图
* Input:         s32Handle: 任务句柄
*                pSrc: 源位图信息结构
*                pstSrcRect: 源位图操作区域
*                pDst: 目标位图信息结构
*                pstDstRect: 目标位图操作区域
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiQuickFlicker(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect,
                                TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect);

/*****************************************************************************
* Function:      TdeOsiBitmapMaskRop
* Description:   首先将源2与Mask位图进行RopMask, 然后与源1与中间位图RopMask，
*                将结果输出到目的位图中。
* Input:         s32Handle: 任务句柄
*                pstBackGround: 背景位图信息结构
*                pstBackGroundRect: 背景位图操作区域
*                pstForeGround: 前景位图信息结构
*                pstForeGroundRect: 前景位图操作区域
*                pstMask: 作掩码运算的位图信息结构
*                pstMaskRect: 作掩码运算的位图操作区域
*                pstDst:  目标位图信息结构
*                pstDstRect:  目标位图操作区域
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiBitmapMaskRop(TDE_HANDLE s32Handle, 
                        TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                        TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForGroundRect, 
                        TDE2_SURFACE_S* pstMask, TDE2_RECT_S  *pstMaskRect,
                        TDE2_SURFACE_S* pDst, TDE2_RECT_S  *pstDstRect,
                        TDE2_ROP_CODE_E enRopCode_Color, TDE2_ROP_CODE_E enRopCode_Alpha);

/*****************************************************************************
* Function:      TdeOsiBitmapMaskBlend
* Description:   首先将源2与Mask位图进行BlendMask, 然后与源1与中间位图Blend，
*                将结果输出到目的位图中。
* Input:         s32Handle: 任务句柄
*                pstBackGround: 背景位图信息结构
*                pstBackGroundRect: 背景位图操作区域
*                pstForeGround: 前景位图信息结构
*                pstForeGroundRect: 前景位图操作区域
*                pstMask: 作掩码运算的位图信息结构
*                pstMaskRect: 作掩码运算的位图操作区域
*                pstDst:  目标位图信息结构
*                pstDstRect:  目标位图操作区域
*                u8Alpha:  参与运算Alpha数值
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiBitmapMaskBlend(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                                 TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForGroundRect, TDE2_SURFACE_S* pstMask,
                                 TDE2_RECT_S  *pstMaskRect, TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect,
                                 HI_U8 u8Alpha, TDE2_ALUCMD_E enBlendMode);


/*****************************************************************************
* Function:      TdeOsiSolidDraw
* Description:   将单色值与源位图进行运算将结果输出到pDst中，运算设置在pOpt
* Input:         s32Handle: 任务句柄
*                pSrc: 源位图信息结构
*                pstDst: 目标位图信息结构
*                pstFillColor:  颜色信息
*                pstOpt:  运算参数设置结构
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32  TdeOsiSolidDraw(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect, TDE2_SURFACE_S *pstDst,
                           TDE2_RECT_S  *pstDstRect, TDE2_FILLCOLOR_S *pstFillColor, TDE2_OPT_S *pstOpt);

/*****************************************************************************
* Function:      TdeOsiRegisterTrigFunc
* Description:   该函数用于VO注册TDE同步触发信号设置接口
* Input:         TDE_TRIG_SEL: 同步触发信号设置callback函数指针
* Output:        无
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiTriggerSel(HI_U32 u32TrigSel);

HI_S32 TdeOsiPatternFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S * pstBackGround, 
    TDE2_RECT_S * pstBackGroundRect, TDE2_SURFACE_S * pstForeGround, 
    TDE2_RECT_S * pstForeGroundRect, TDE2_SURFACE_S * pstDst, 
    TDE2_RECT_S * pstDstRect, TDE2_PATTERN_FILL_OPT_S *pstOpt);

/*****************************************************************************
* Function:      TdeOsiEnableRegionDeflicker
* Description:   使能/去使能局部抗闪烁
* Input:         无
* Output:        bRegionDeflicker:是否使能标志
* Return:        成功 / 错误码
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiEnableRegionDeflicker(HI_BOOL bRegionDeflicker);
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* _TDE_OSICTL_H_ */
