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
\brief Starts a two-dimensional engine 2 (TDE2) device. CNcomment:��TDE2�豸
\attention \n
Before using the TDE, you must call this API to ensure that a TDE device is started.\n
A TDE device can be started repeatedly by using multiple processes.\n.
CNcomment:�ڽ���TDE��ز���ǰӦ�����ȵ��ô˽ӿڣ���֤TDE�豸���ڴ�״̬\n
TDE�豸���������ظ���\n
 
\param  N/A
\retval ::HI_SUCCESS Success. CNcomment:�ɹ�
\retval ::HI_ERR_TDE_DEV_OPEN_FAILED Starting a TDE device fails. CNcomment:TDE�豸��ʧ��
\see \n
N/A
*/
HI_S32      HI_TDE2_Open(HI_VOID);


/** 
\brief Stops a TDE2 device. CNcomment:�ر�TDE2�豸
\attention \n
HI_TDE2_Open must work with HI_TDE2_Close.\n
CNcomment:����HI_TDE2_Open��HI_TDE2_Close�Ĵ�����Ҫ��Ӧ\n
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
\retval If the return value is greater than 0, it indicates that the TDE task handle is valid. CNcomment:����0���Ϸ���TDE������
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  Calling this API fails because no TDE device is started. CNcomment:TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_INVALID_HANDLE The handle of a TDE task is invalid. CNcomment:�Ƿ���TDE������
\see \n
N/A
*/
TDE_HANDLE  HI_TDE2_BeginJob(HI_VOID);


/** 
\brief Submits an existing TDE task. CNcomment:�ύ�Ѵ�����TDE����
\attention \n
Before calling this API, you must call HI_TDE2_Open to start a TDE device and call HI_TDE2_BeginJob to obtain a valid task handle.\n
If the calling mode is set to block mode, and the API is returned due to timeout or interruption, the operation continues till it is complete even though the API called by the TDE is returned in advance.\n
If the calling mode is set to synchronization mode, the operations in a TDE task are performed only after the frame or field synchronization signals from the video output unit (VOU) are received. If the calling mode is set to another mode, the operations in a TDE task are added to the global asynchronous command queue.\n
The synchronization mode is not supported currently.\n
After a task is submitted, its handle becomes invalid. If the task is submitted again, the error code HI_ERR_TDE_INVALID_HANDLE is returned. \n.
CNcomment:�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
������Ϊ����������������ʱ���ػ��жϷ���ʱӦ��ע�⣺��ʱTDE������API������ǰ���أ���ִ�еĲ����Ի����\n
�������Ϊͬ��ģʽ���������еĲ�����ȵ���Ƶ�����֡��ͬ���ź����˲Ż�ִ�У����������Ϊͬ��ģʽ���������еĲ��������ȫ���첽������еȺ�ִ�У�Ŀǰ\n
�ݲ�֧��ͬ��ģʽ\n
�ύ����󣬴������Ӧ��handle���Ϊ��Ч���ٴ��ύ����ִ�����HI_ERR_TDE_INVALID_HANDLE \n

\param[in] s32Handle  Handle of a TDE task. CNcomment:TDE������
\param[in] bSync  Whether to submit a TDE task in synchronization mode. CNcomment:�Ƿ�ʹ��ͬ����ʽ�ύ
\param[in] bBlock  Block flag. CNcomment:������־
\param[in] u32TimeOut  Timeout period 10 ms. CNcomment:��ʱʱ�䣬��λjiffies��10ms��
\retval ::HI_SUCCESS  A task is submitted successfully in non-block mode. CNcomment:�����������ύ�ɹ�
\retval ::HI_ERR_TDE_INVALID_HANDLE  The input task handle is invalid. CNcomment:�����Job handler��Ч
\retval ::HI_ERR_TDE_JOB_TIMEOUT  A task is not completed due to timeout. CNcomment:����ʱδ���
\see \n
N/A
*/
HI_S32      HI_TDE2_EndJob(TDE_HANDLE s32Handle, HI_BOOL bSync, HI_BOOL bBlock, HI_U32 u32TimeOut);

/** 
\brief Rapidly fills in the target bitmap with a fixed value. CNcomment:���ٽ��̶�ֵ��䵽Ŀ��λͼ
\attention \n
The data to be filled in must be specified based on the format of the target bitmap.\n
CNcomment:��������ֵ��Ҫ����Ŀ��λͼ�ĸ�ʽָ��\n
\param[in] s32Handle  Handle of a TDE task. CNcomment:TDE������
\param[in] pstDst  Target bitmap. CNcomment:Ŀ��λͼ
\param[in] pstDstRect  Operating area of the target bitmap. CNcomment:Ŀ��λͼ��������
\param[in] u32FillData  Data to be filled in. CNcomment:���ֵ
\retval 0 success. CNcomment:�ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  Calling this API fails because no TDE device is started. CNcomment:TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  The parameter contains a null pointer. CNcomment:�������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  The handle of a TDE task is invalid. CNcomment:�Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  The parameter is invalid. CNcomment:��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  Adding an operation fails due to insufficient memory. CNcomment:�ڴ治�㣬�޷���Ӳ���
\retval ::HI_FAILURE  A system error or an unknown error occurs. CNcomment:ϵͳ�����δ֪����
\see \n
N/A
*/
HI_S32      HI_TDE2_QuickFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect,
                              HI_U32 u32FillData);



/** 
\brief Adds the transfer operation (with additional functions available for the raster or macroblock bitmap) to a TDE task.
CNcomment:����������ӶԹ�դ/���λͼ�����и��ӹ��ܵİ��Ʋ���
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
CNcomment:�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
Ŀ��λͼ�����뱳��λͼ����ɫ�ռ�һ�£�ǰ��λͼ����ɫ�ռ�����뱳��/Ŀ��λͼ��һ�£���������»������ɫ�ռ�ת������\n
��ǰ��Դλͼ��Ŀ��λͼ�ߴ粻һ��ʱ��������������������趨������������ţ����������ù����������Сֵ���вü�����\n
Global Alpha��Alplh0��Alpha1������ֵͳһ����[0,255]�ķ�Χ��������\n
����λͼ������Ŀ��λͼΪͬһλͼ\n
��ֻ��Ҫʹ�õ�Դ���Ʋ���ʱ������ֻ��Դλͼ����ROPȡ�ǲ����������Խ������򱳾�λͼ�Ľṹ��Ϣ�Ͳ�������ṹָ������Ϊ��\n
���ܹ������þ����ͬʱ��������\n
��Clip����ʱ���ü������������������й�������������᷵�ش���\n
�ڵ�һ������ɫ��չ������ԴΪClut��ʽ��Ŀ��ΪARGB/AYCbCr��ʽ��ʱ����Ҫ��Clut Reload���\n
���򵥵İ��Ʋ���(�������ӹ��ܣ���Դ��Ŀ������ظ�ʽһ��)ʱ�����Խ�����ѡ��ṹ��ָ������Ϊ��,��ʱ����п��ٰ���\n
��֧��Ŀ�����ظ�ʽΪ����ʽ\n

\param[in] s32Handle  Handle of a TDE task. CNcomment:TDE������
\param[in] pstBackGround  Background bitmap. CNcomment:����λͼ
\param[in] pstBackGroundRect  Operating area of the background bitmap. CNcomment:����λͼ��������
\param[in] pstForeGround  Foreground bitmap. CNcomment:ǰ��λͼ
\param[in] pstForeGroundRect  Operating area of the foreground bitmap. CNcomment:ǰ��λͼ��������
\param[in] pstDst  Target bitmap. CNcomment:Ŀ��λͼ
\param[in] pstDstRect  Operating area of the target bitmap. CNcomment:Ŀ��λͼ��������
\param[in] pstOpt  Structure for setting operation parameters. CNcomment:����������ýṹ
\retval 0 success. CNcomment:�ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  Calling this API fails because no TDE device is started. CNcomment:TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  The parameter contains a null pointer. CNcomment:�������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  The handle of a TDE task is invalid. CNcomment:�Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  The parameter is invalid. CNcomment:��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  Adding an operation fails due to insufficient memory. CNcomment:�ڴ治�㣬�޷���Ӳ���
\retval ::HI_ERR_TDE_NOT_ALIGNED  The start address of the CLUT is not 4-byte aligned. CNcomment:Clut�����ʼ��ַû�а���4byte����
\retval ::HI_ERR_TDE_MINIFICATION  The minification is too large. CNcomment:��С��������
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  The bitmap does not support this operation. CNcomment:λͼ�ĸ�ʽ������֧�ִ˲���
\retval ::HI_ERR_TDE_CLIP_AREA  The operating area does not overlap the clipping area, and the displayed information is not updated. CNcomment:����������Clip����û�н�������ʾ�����и���
\retval ::HI_FAILURE  A system error or an unknown error occurs. CNcomment:ϵͳ�����δ֪����
\see \n
N/A
*/
HI_S32      HI_TDE2_Bitblit(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                            TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect, TDE2_SURFACE_S* pstDst,
                            TDE2_RECT_S  *pstDstRect, TDE2_OPT_S* pstOpt);


/** 
\brief Adds the transfer operation (with additional functions available for the macroblock bitmap) to a TDE task. That is, the luminance macroblock data and the chrominance macroblock data are combined into raster data. During the combination, the scaling, anti-flicker, and clip operations can be performed concurrently.
CNcomment:����������ӶԺ��λͼ�����и��ӹ��ܵİ��Ʋ����������Ⱥ�ɫ�Ⱥ�����ݺϲ��ɹ�դ��ʽ�����԰������š�����˸��Clip����
\attention \n
Before calling this API, you must call HI_TDE2_Open to start a TDE device and call HI_TDE2_BeginJob to obtain a valid task handle.\n
For the YCbCr422 macroblock, the horizontal coordination of the start point of the operating area must be an even number.\n
The target bitmap must be in YCbCr format.\n
CNcomment:�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
����YCbCr422��ʽ�ĺ�飬����������ʼ��ˮƽ���������ż��\n
Ŀ��λͼ������YCbCr��ɫ�ռ�\n
 	 	 	
\param[in] s32Handle  Handle of a TDE task. CNcomment:TDE������
\param[in] pstMB  Surface of a macroblock. CNcomment:���surface
\param[in] pstMbRect  Operating area of a macroblock. CNcomment:����������
\param[in] pstDst  Target bitmap. CNcomment:Ŀ��λͼ
\param[in] pstDstRect  Operating area of the target bitmap. CNcomment:Ŀ���������
\param[in] pstMbOpt  Operation attributes of a macroblock. CNcomment:����������
\retval 0 success. CNcomment:�ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  Calling this API fails because no TDE device is started. CNcomment:TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  The parameter contains a null pointer. CNcomment:�������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  The handle of a TDE task is invalid. CNcomment:�Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  The parameter is invalid. CNcomment:��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  Adding an operation fails due to insufficient memory. CNcomment:�ڴ治�㣬�޷���Ӳ���
\retval ::HI_ERR_TDE_MINIFICATION  The minification is too large because its maximum value is 15. CNcomment:��С�����������ƣ����Ϊ��С15����
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  The bitmap does not support this operation. CNcomment:λͼ�ĸ�ʽ������֧�ִ˲���
\retval ::HI_ERR_TDE_CLIP_AREA  The operating area does not overlap the clipping area, and the displayed information is not updated. CNcomment:����������Clip����û�н�������ʾ�����и���
\retval ::HI_FAILURE  A system error or an unknown error occurs. CNcomment:ϵͳ�����δ֪����
\see \n
N/A
*/
HI_S32      HI_TDE2_MbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect,
                           TDE2_MBOPT_S* pstMbOpt);

/** 
\brief Sets the alpha judgment threshold. CNcomment:����alpha�о���ֵ
\attention \n
N/A
\param[in] u8ThresholdValue  Judgment threshold. CNcomment:�о���ֵ
\retval 0 success. CNcomment:�ɹ�
\retval ::

\see \n
N/A
*/
HI_S32 HI_TDE2_SetAlphaThresholdValue(HI_U8 u8ThresholdValue);

/** 
\brief Enables or disables the alpha judgment. CNcomment:����alpha�о�����
\attention  N/A
\param[in] bEnAlphaThreshold  Whether to enable the alpha judgment. CNcomment:alpha�о�����
\retval 0 success. CNcomment:�ɹ�
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
