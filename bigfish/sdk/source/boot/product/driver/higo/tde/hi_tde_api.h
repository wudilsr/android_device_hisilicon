/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : hi_tde_api.h
Version             : Initial Draft
Author              : 
Created             : 2014/08/06
Description         : 
Function List       : 
History             :
Date                       Author                   Modification
2014/08/06                 y00181162                Created file        
******************************************************************************/

#ifndef __HI_TDE_API_H__
#define __HI_TDE_API_H__


/*********************************add include here******************************/
#include "hi_type.h"
#include "hi_tde_type.h"


/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/


#define HI_TDE_Open HI_TDE2_Open
#define HI_TDE_Close HI_TDE2_Close
#define HI_TDE_BeginJob HI_TDE2_BeginJob

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/

/** 
\brief Starts a two-dimensional engine 2 (TDE2) device. CNcomment:打开TDE2设备
\attention \n
Before using the TDE, you must call this API to ensure that a TDE device is started.\n
A TDE device can be started repeatedly by using multiple processes.\n.
CNcomment:在进行TDE相关操作前应该首先调用此接口，保证TDE设备处于打开状态\n
TDE设备允许多进程重复打开\n
 
\param  N/A
\retval ::HI_SUCCESS Success. CNcomment:成功
\retval ::HI_ERR_TDE_DEV_OPEN_FAILED Starting a TDE device fails. CNcomment:TDE设备打开失败
\see \n
N/A
*/
HI_S32      HI_TDE2_Open(HI_VOID);


/** 
\brief Stops a TDE2 device. CNcomment:关闭TDE2设备
\attention \n
HI_TDE2_Open must work with HI_TDE2_Close.\n
CNcomment:调用HI_TDE2_Open与HI_TDE2_Close的次数需要对应\n
\param  N/A
\retval N/A
\see \n
N/A
*/
HI_VOID     HI_TDE2_Close(HI_VOID);


/** 
\brief Creates a TDE task.
\attention N/A
\param  N/A
\retval If the return value is greater than 0, it indicates that the TDE task handle is valid. CNcomment:大于0：合法的TDE任务句柄
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  Calling this API fails because no TDE device is started. CNcomment:TDE设备未打开，API调用失败
\retval ::HI_ERR_TDE_INVALID_HANDLE The handle of a TDE task is invalid. CNcomment:非法的TDE任务句柄
\see \n
N/A
*/
TDE_HANDLE  HI_TDE2_BeginJob(HI_VOID);


/** 
\brief Submits an existing TDE task. CNcomment:提交已创建的TDE任务
\attention \n
Before calling this API, you must call HI_TDE2_Open to start a TDE device and call HI_TDE2_BeginJob to obtain a valid task handle.\n
If the calling mode is set to block mode, and the API is returned due to timeout or interruption, the operation continues till it is complete even though the API called by the TDE is returned in advance.\n
If the calling mode is set to synchronization mode, the operations in a TDE task are performed only after the frame or field synchronization signals from the video output unit (VOU) are received. If the calling mode is set to another mode, the operations in a TDE task are added to the global asynchronous command queue.\n
The synchronization mode is not supported currently.\n
After a task is submitted, its handle becomes invalid. If the task is submitted again, the error code HI_ERR_TDE_INVALID_HANDLE is returned. \n.
CNcomment:在调用此接口前应保证调用HI_TDE2_Open打开TDE设备，并且调用HI_TDE2_BeginJob获得了有效的任务句柄\n
若设置为阻塞操作，函数超时返回或被中断返回时应该注意：此时TDE操作的API函数提前返回，但执行的操作仍会完成\n
如果设置为同步模式，则任务中的操作会等到视频输出的帧或场同步信号来了才会执行；如果不设置为同步模式，则任务中的操作会加入全局异步命令队列等候执行；目前\n
暂不支持同步模式\n
提交任务后，此任务对应的handle会变为无效，再次提交会出现错误码HI_ERR_TDE_INVALID_HANDLE \n

\param[in] s32Handle  Handle of a TDE task. CNcomment:TDE任务句柄
\param[in] bSync  Whether to submit a TDE task in synchronization mode. CNcomment:是否使用同步方式提交
\param[in] bBlock  Block flag. CNcomment:阻塞标志
\param[in] u32TimeOut  Timeout period 10 ms. CNcomment:超时时间，单位jiffies（10ms）
\retval ::HI_SUCCESS  A task is submitted successfully in non-block mode. CNcomment:非阻塞任务提交成功
\retval ::HI_ERR_TDE_INVALID_HANDLE  The input task handle is invalid. CNcomment:输入的Job handler无效
\retval ::HI_ERR_TDE_JOB_TIMEOUT  A task is not completed due to timeout. CNcomment:任务超时未完成
\see \n
N/A
*/
HI_S32      HI_TDE2_EndJob(TDE_HANDLE s32Handle, HI_BOOL bSync, HI_BOOL bBlock, HI_U32 u32TimeOut);

/** 
\brief Rapidly fills in the target bitmap with a fixed value. CNcomment:快速将固定值填充到目的位图
\attention \n
The data to be filled in must be specified based on the format of the target bitmap.\n
CNcomment:填充的数据值需要按照目标位图的格式指定\n
\param[in] s32Handle  Handle of a TDE task. CNcomment:TDE任务句柄
\param[in] pstDst  Target bitmap. CNcomment:目标位图
\param[in] pstDstRect  Operating area of the target bitmap. CNcomment:目标位图操作区域
\param[in] u32FillData  Data to be filled in. CNcomment:填充值
\retval 0 success. CNcomment:成功
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  Calling this API fails because no TDE device is started. CNcomment:TDE设备未打开，API调用失败
\retval ::HI_ERR_TDE_NULL_PTR  The parameter contains a null pointer. CNcomment:参数中有空指针错误
\retval ::HI_ERR_TDE_INVALID_HANDLE  The handle of a TDE task is invalid. CNcomment:非法的任务句柄
\retval ::HI_ERR_TDE_INVALID_PARA  The parameter is invalid. CNcomment:无效的参数设置
\retval ::HI_ERR_TDE_NO_MEM  Adding an operation fails due to insufficient memory. CNcomment:内存不足，无法添加操作
\retval ::HI_FAILURE  A system error or an unknown error occurs. CNcomment:系统错误或未知错误
\see \n
N/A
*/
HI_S32      HI_TDE2_QuickFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect,
                              HI_U32 u32FillData);



/** 
\brief Adds the transfer operation (with additional functions available for the raster or macroblock bitmap) to a TDE task.
CNcomment:向任务中添加对光栅/宏块位图进行有附加功能的搬移操作
\attention \n
Before calling this API, you must call HI_TDE2_Open to start a TDE device and call HI_TDE2_BeginJob to obtain a valid task handle.\n
The color space of the target bitmap must be the same as that of the background bitmap. The color space of the foreground bitmap can be different from that of the background or target bitmap. In this case, color space conversion is performed.\n
If the sizes of the foreground bitmap and target bitmap are different, scaling is performed based on the preset scaling area. If no scaling area is set, the clip and transfer operations are performed based on the minimum value of the public area.\n
The value of the global alpha, Alpha0, or Alpha1 ranges from 0 to 255.\n
The background bitmap and the target bitmap can be the same.\n
If only the single-source transfer operation (for example, performing the ROP and reverse operations on the source bitmap only) is required, you can set the structure information and the pointer of the operating area of the background or the background bitmap to null.\n
Scaling is not supported if the mirror function is enabled.\n
The clip operation can be performed only when the clipping area overlaps the operating area; otherwise, an error occurs.\n
When the color extension (from CLUT to ARGB/AYCbCr) is performed for the first time, the CLUT Reload flag function must be enabled.\n
During a simple transfer operation (the operation does not contain additional functions and the pixel format of source and target bitmaps are the same), you can set the pointer to the operation option type to null. Then fast transfer is implemented.\n
The pixel format of the target bitmap cannot be the macroblock format.\n
CNcomment:在调用此接口前应保证调用HI_TDE2_Open打开TDE设备，并且调用HI_TDE2_BeginJob获得了有效的任务句柄\n
目标位图必须与背景位图的颜色空间一致，前景位图的颜色空间可以与背景/目标位图不一致，这种情况下会进行颜色空间转换功能\n
当前景源位图与目标位图尺寸不一致时，如果设置了缩放则按照设定的区域进行缩放，否则按照设置公共区域的最小值进行裁减搬移\n
Global Alpha和Alplh0、Alpha1的设置值统一按照[0,255]的范围进行设置\n
背景位图可以与目标位图为同一位图\n
当只需要使用单源搬移操作时（比如只对源位图进行ROP取非操作），可以将背景或背景位图的结构信息和操作区域结构指针设置为空\n
不能够在启用镜像的同时进行缩放\n
作Clip操作时，裁减区域必须与操作区域有公共交集，否则会返回错误\n
在第一次作颜色扩展操作（源为Clut格式，目的为ARGB/AYCbCr格式）时，需要打开Clut Reload标记\n
作简单的搬移操作(不带附加功能，且源和目标的象素格式一致)时，可以将操作选项结构体指针设置为空,这时会进行快速搬移\n
不支持目标象素格式为宏块格式\n

\param[in] s32Handle  Handle of a TDE task. CNcomment:TDE任务句柄
\param[in] pstBackGround  Background bitmap. CNcomment:背景位图
\param[in] pstBackGroundRect  Operating area of the background bitmap. CNcomment:背景位图操作区域
\param[in] pstForeGround  Foreground bitmap. CNcomment:前景位图
\param[in] pstForeGroundRect  Operating area of the foreground bitmap. CNcomment:前景位图操作区域
\param[in] pstDst  Target bitmap. CNcomment:目标位图
\param[in] pstDstRect  Operating area of the target bitmap. CNcomment:目标位图操作区域
\param[in] pstOpt  Structure for setting operation parameters. CNcomment:运算参数设置结构
\retval 0 success. CNcomment:成功
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  Calling this API fails because no TDE device is started. CNcomment:TDE设备未打开，API调用失败
\retval ::HI_ERR_TDE_NULL_PTR  The parameter contains a null pointer. CNcomment:参数中有空指针错误
\retval ::HI_ERR_TDE_INVALID_HANDLE  The handle of a TDE task is invalid. CNcomment:非法的任务句柄
\retval ::HI_ERR_TDE_INVALID_PARA  The parameter is invalid. CNcomment:无效的参数设置
\retval ::HI_ERR_TDE_NO_MEM  Adding an operation fails due to insufficient memory. CNcomment:内存不足，无法添加操作
\retval ::HI_ERR_TDE_NOT_ALIGNED  The start address of the CLUT is not 4-byte aligned. CNcomment:Clut表的起始地址没有按照4byte对齐
\retval ::HI_ERR_TDE_MINIFICATION  The minification is too large. CNcomment:缩小倍数过大
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  The bitmap does not support this operation. CNcomment:位图的格式操作不支持此操作
\retval ::HI_ERR_TDE_CLIP_AREA  The operating area does not overlap the clipping area, and the displayed information is not updated. CNcomment:操作区域与Clip区域没有交集，显示不会有更新
\retval ::HI_FAILURE  A system error or an unknown error occurs. CNcomment:系统错误或未知错误
\see \n
N/A
*/
HI_S32      HI_TDE2_Bitblit(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                            TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect, TDE2_SURFACE_S* pstDst,
                            TDE2_RECT_S  *pstDstRect, TDE2_OPT_S* pstOpt);


/** 
\brief Adds the transfer operation (with additional functions available for the macroblock bitmap) to a TDE task. That is, the luminance macroblock data and the chrominance macroblock data are combined into raster data. During the combination, the scaling, anti-flicker, and clip operations can be performed concurrently.
CNcomment:向任务中添加对宏块位图进行有附加功能的搬移操作。将亮度和色度宏块数据合并成光栅格式，可以伴随缩放、抗闪烁、Clip处理
\attention \n
Before calling this API, you must call HI_TDE2_Open to start a TDE device and call HI_TDE2_BeginJob to obtain a valid task handle.\n
For the YCbCr422 macroblock, the horizontal coordination of the start point of the operating area must be an even number.\n
The target bitmap must be in YCbCr format.\n
CNcomment:在调用此接口前应保证调用HI_TDE2_Open打开TDE设备，并且调用HI_TDE2_BeginJob获得了有效的任务句柄\n
对于YCbCr422格式的宏块，操作区域起始点水平坐标必须是偶数\n
目标位图必须是YCbCr颜色空间\n
 	 	 	
\param[in] s32Handle  Handle of a TDE task. CNcomment:TDE任务句柄
\param[in] pstMB  Surface of a macroblock. CNcomment:宏块surface
\param[in] pstMbRect  Operating area of a macroblock. CNcomment:宏块操作区域
\param[in] pstDst  Target bitmap. CNcomment:目标位图
\param[in] pstDstRect  Operating area of the target bitmap. CNcomment:目标操作区域
\param[in] pstMbOpt  Operation attributes of a macroblock. CNcomment:宏块操作属性
\retval 0 success. CNcomment:成功
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  Calling this API fails because no TDE device is started. CNcomment:TDE设备未打开，API调用失败
\retval ::HI_ERR_TDE_NULL_PTR  The parameter contains a null pointer. CNcomment:参数中有空指针错误
\retval ::HI_ERR_TDE_INVALID_HANDLE  The handle of a TDE task is invalid. CNcomment:非法的任务句柄
\retval ::HI_ERR_TDE_INVALID_PARA  The parameter is invalid. CNcomment:无效的参数设置
\retval ::HI_ERR_TDE_NO_MEM  Adding an operation fails due to insufficient memory. CNcomment:内存不足，无法添加操作
\retval ::HI_ERR_TDE_MINIFICATION  The minification is too large because its maximum value is 15. CNcomment:缩小倍数超出限制（最大为缩小15倍）
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  The bitmap does not support this operation. CNcomment:位图的格式操作不支持此操作
\retval ::HI_ERR_TDE_CLIP_AREA  The operating area does not overlap the clipping area, and the displayed information is not updated. CNcomment:操作区域与Clip区域没有交集，显示不会有更新
\retval ::HI_FAILURE  A system error or an unknown error occurs. CNcomment:系统错误或未知错误
\see \n
N/A
*/
HI_S32      HI_TDE2_MbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect,
                           TDE2_MBOPT_S* pstMbOpt);

/** 
\brief Sets the alpha judgment threshold. CNcomment:设置alpha判决阈值
\attention \n
N/A
\param[in] u8ThresholdValue  Judgment threshold. CNcomment:判决阈值
\retval 0 success. CNcomment:成功
\retval ::

\see \n
N/A
*/
HI_S32 HI_TDE2_SetAlphaThresholdValue(HI_U8 u8ThresholdValue);

/** 
\brief Enables or disables the alpha judgment. CNcomment:设置alpha判决开关
\attention  N/A
\param[in] bEnAlphaThreshold  Whether to enable the alpha judgment. CNcomment:alpha判决开关
\retval 0 success. CNcomment:成功
\retval ::
\see \n
N/A
*/
HI_S32 HI_TDE2_SetAlphaThresholdState(HI_BOOL bEnAlphaThreshold);


#ifdef __cplusplus
					   
#if __cplusplus
					   
}

#endif
#endif /* __cplusplus */
					   
#endif /* __HI_TDE_API_H__ */
