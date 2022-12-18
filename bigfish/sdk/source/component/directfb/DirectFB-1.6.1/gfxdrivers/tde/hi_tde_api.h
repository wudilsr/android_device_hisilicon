/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_api_tde.h
* Description:TDE2 API define
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/

#ifndef _HI_API_TDE2_H_
#define _HI_API_TDE2_H_

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#include "hi_type.h"
#include "hi_tde_type.h"

#define HI_TDE_Open HI_TDE2_Open
#define HI_TDE_Close HI_TDE2_Close
#define HI_TDE_BeginJob HI_TDE2_BeginJob

/****************************************************************************/
/*                             TDE2 API define                               */
/****************************************************************************/

/** 
\brief ��TDE2�豸
\attention \n
 �ڽ���TDE��ز���ǰӦ�����ȵ��ô˽ӿڣ���֤TDE�豸���ڴ�״̬\n
 TDE�豸���������ظ���\n
 
\param  ��
\retval ::HI_SUCCESS �ɹ�
\retval ::HI_ERR_TDE_DEV_OPEN_FAILED TDE�豸��ʧ��
\see \n
��
*/
HI_S32      HI_TDE2_Open(HI_VOID);


/** 
\brief �ر�TDE2�豸
\attention \n
����HI_TDE2_Open��HI_TDE2_Close�Ĵ�����Ҫ��Ӧ\n
\param  ��
\retval none
\see \n
��
*/
HI_VOID     HI_TDE2_Close(HI_VOID);


/** 
\brief ����1��TDE����
\attention ��
\param  ��
\retval ����0���Ϸ���TDE������
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_INVALID_HANDLE �Ƿ���TDE������
\see \n
��
*/
TDE_HANDLE  HI_TDE2_BeginJob(HI_VOID);


/** 
\brief �ύ�Ѵ�����TDE����
\attention \n
�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
������Ϊ����������������ʱ���ػ��жϷ���ʱӦ��ע�⣺��ʱTDE������API������ǰ���أ���ִ�еĲ����Ի����\n
�������Ϊͬ��ģʽ���������еĲ�����ȵ���Ƶ�����֡��ͬ���ź����˲Ż�ִ�У����������Ϊͬ��ģʽ���������еĲ��������ȫ���첽������еȺ�ִ�У�Ŀǰ\n
�ݲ�֧��ͬ��ģʽ\n
�ύ����󣬴������Ӧ��handle���Ϊ��Ч���ٴ��ύ����ִ�����HI_ERR_TDE_INVALID_HANDLE \n

\param[in] s32Handle  TDE������
\param[in] bSync  �Ƿ�ʹ��ͬ����ʽ�ύ
\param[in] bBlock  ������־
\param[in] u32TimeOut  ��ʱʱ�䣬��λjiffies��10ms��
\retval ::HI_SUCCESS  �����������ύ�ɹ�
\retval ::HI_ERR_TDE_INVALID_HANDLE  �����Job handler��Ч
\retval ::HI_ERR_TDE_JOB_TIMEOUT  ����ʱδ���
\see \n
��
*/
HI_S32      HI_TDE2_EndJob(TDE_HANDLE s32Handle, HI_BOOL bSync, HI_BOOL bBlock, HI_U32 u32TimeOut);


/** 
\brief ȡ���Ѿ����뵽TDE�����еĲ���
\attention \n
�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
�Ѿ��ύ�������ܹ���ȡ��\n
ȡ�������������Ч��������Ӳ���\n
�˽ӿڵ�Ӧ�ó�����������TDE��������ʱʹ��\n

\param[in] s32Handle ������
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_FAILURE  ָ���������Ѿ��ύ�޷�ȡ��

\see \n
��
*/
HI_S32      HI_TDE2_CancelJob(TDE_HANDLE s32Handle);



/** 
\brief �ȴ�ָ�����������
\attention \n
 �˽ӿ�Ϊ�����ӿڣ��������ȴ�ָ�����������\n
 
\param[in] s32Handle ������
\retval 0  ָ����TDE����δ���
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_QUERY_TIMEOUT  ָ��������ʱδ���
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  ��֧�ֵĲ���

\see \n
��
*/
HI_S32      HI_TDE2_WaitForDone(TDE_HANDLE s32Handle);


/** 
\brief �ȴ�TDE�������������
\attention \n
�˽ӿ�Ϊ�����ӿڣ��������ȴ����е�TDE�������\n
\param  ��
\retval 0  ָ����TDE����δ���
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  ��֧�ֵĲ���
\see \n
��
*/
HI_S32 HI_TDE2_WaitAllDone(HI_VOID);


/** 
\brief ��λTDE����״̬
\attention \n
�˽ӿ�һ�����ڴ���������Ӳ����ƥ��ʱ���ֳ�ʱ����ʱ���ã����ڸ�λ��Ӳ��\n
\param  ��
\retval 0  ָ����TDE����δ���
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\see \n
��
*/
HI_S32 HI_TDE2_Reset(HI_VOID);


/** 
\brief ����������ӿ��ٿ�������
\attention \n
�˽ӿ�ʹ�õ���ֱ��DMA���ƣ������������HI_TDE2_Bitblit����\n
���ٿ���������֧�ָ�ʽת����Դλͼ��Ŀ��λͼ��ʽ����һ��\n
���ٿ�����֧�����Ź��ܣ�������Դ��Ŀ�ĵĲ�������ߴ粻һ�£�����������С�Ŀ�߽��п�������\n
ָ���Ĳ�������Ҫ��ָ����λͼ�й������򣬷���᷵�ش��������������д�Ҫ��\n
���ظ�ʽ���ڵ���Byte��λͼ��ʽ�Ļ���ַ��λͼ��Stride���밴�����ظ�ʽ���룬���ظ�ʽ����Byte��λͼ��ʽ�Ļ���ַ��Stride��Ҫ����Byte���룻�����������д�Ҫ��\n
���ظ�ʽ����Byte��λͼ��ʽ��ˮƽ��ʼλ�úͿ�ȱ��밴�����ض���\n
YCbCr422��ʽ��λͼ��ˮƽ��ʼλ�úͿ�ȱ���Ϊż���������������д�Ҫ��\n

\param[in] s32Handle  TDE������
\param[in] pstSrc  Դλͼ
\param[in] pstSrcRect  Դλͼ��������
\param[in] pstDst  Ŀ��λͼ
\param[in] pstDstRect  Ŀ��λͼ��������
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  �ڴ治�㣬�޷���Ӳ���
\retval ::HI_FAILURE  ϵͳ�����δ֪����
\see \n
��
*/
HI_S32      HI_TDE2_QuickCopy(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect,
                              TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect);


/** 
\brief ���ٽ��̶�ֵ��䵽Ŀ��λͼ
\attention \n
��������ֵ��Ҫ����Ŀ��λͼ�ĸ�ʽָ��\n
\param[in] s32Handle  TDE������
\param[in] pstDst  Ŀ��λͼ
\param[in] pstDstRect  Ŀ��λͼ��������
\param[in] u32FillData  ���ֵ
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  �ڴ治�㣬�޷���Ӳ���
\retval ::HI_FAILURE  ϵͳ�����δ֪����
\see \n
��
*/
HI_S32      HI_TDE2_QuickFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect,
                              HI_U32 u32FillData);


/** 
\brief ��Դλͼ������ΪĿ��λͼָ����С��Դ��Ŀ���Ϊͬһλͼ
\attention \n
��С�������Ϊ15�����Ŵ�����û������\n
����ʱԴλͼ��Ŀ��λͼ����Ϊͬһλͼ��������Ϊ�ڴ����ص��Ĳ�ͬλͼ\n

\param[in] s32Handle  TDE������
\param[in] pstSrc  Դλͼ
\param[in] pstSrcRect  Դλͼ��������
\param[in] pstDst  Ŀ��λͼ
\param[in] pstDstRect  Ŀ��λͼ��������
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  �ڴ治�㣬�޷���Ӳ���
\retval ::HI_ERR_TDE_NOT_ALIGNED  λͼ��ʼ��ַ��Strideû�а������ض���
\retval ::HI_ERR_TDE_MINIFICATION  ��С��������
\retval ::HI_ERR_TDE_NOT_ALIGNED  Clut�����ʼ��ַû�а���4byte����
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  ��֧�ֵĲ�������
\retval ::HI_FAILURE  ϵͳ�����δ֪����
\see \n
��
*/
HI_S32      HI_TDE2_QuickResize(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect,
                                TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect);


/** 
\brief ����������ӿ���˸���� 
\attention \n
����˸ֻ����ֱ��������˲�\n
����˸��Դ��Ŀ��λͼ������ͬһ���ڴ�\n
���ָ�������������������һ�£����������Ŵ���\n
 	
\param[in] s32Handle  TDE������
\param[in] pstSrc  Դλͼ
\param[in] pstSrcRect  Դλͼ��������
\param[in] pstDst  Ŀ��λͼ
\param[in] pstDstRect  Ŀ��λͼ��������
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  �ڴ治�㣬�޷���Ӳ���
\retval ::HI_ERR_TDE_NOT_ALIGNED  λͼ��ʼ��ַ��Strideû�а������ض���
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  ��֧�ֵĲ�������
\retval ::HI_ERR_TDE_MINIFICATION  ��С��������
\retval ::HI_FAILURE  ϵͳ�����δ֪����
\see \n
��
*/
HI_S32      HI_TDE2_QuickDeflicker(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect,
                                   TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect);



/** 
\brief ����������ӶԹ�դ/���λͼ�����и��ӹ��ܵİ��Ʋ���
\attention \n
�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
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

\param[in] s32Handle  TDE������
\param[in] pstBackGround  ����λͼ
\param[in] pstBackGroundRect  ����λͼ��������
\param[in] pstForeGround  ǰ��λͼ
\param[in] pstForeGroundRect  ǰ��λͼ��������
\param[in] pstDst  Ŀ��λͼ
\param[in] pstDstRect  Ŀ��λͼ��������
\param[in] pstOpt  ����������ýṹ
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  �ڴ治�㣬�޷���Ӳ���
\retval ::HI_ERR_TDE_NOT_ALIGNED  Clut�����ʼ��ַû�а���4byte����
\retval ::HI_ERR_TDE_MINIFICATION  ��С��������
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  λͼ�ĸ�ʽ������֧�ִ˲���
\retval ::HI_ERR_TDE_CLIP_AREA  ����������Clip����û�н�������ʾ�����и���
\retval ::HI_FAILURE  ϵͳ�����δ֪����
\see \n
��
*/
HI_S32      HI_TDE2_Bitblit(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                            TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect, TDE2_SURFACE_S* pstDst,
                            TDE2_RECT_S  *pstDstRect, TDE2_OPT_S* pstOpt);


/** 
\brief ����������ӶԹ�դλͼ�����и��Ӳ����������Ʋ�����ʵ����surface�ϻ��㡢���ߡ�ɫ�������ڴ����ȹ���
\attention \n
�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
��ǰ��λͼΪNULLʱ���ýӿں�HI_TDE2_QuickFillʵ�ֵĹ���һ��\n
��Solid Drawʱ��ֻ�ܶ�ǰ����Color Key\n
Solid Draw���ƾ��λ���ˮƽ/��ֱֱ�ߵķ�����ͨ�����������εĿ�/������ɡ����磺��ֱֱ�߾��ǻ��ƿ��Ϊ1���صľ���\n
 	 	 	 	
\param[in] s32Handle  TDE������
\param[in] pstForeGround  ǰ��λͼ
\param[in] pstForeGroundRect  ǰ��λͼ�Ĳ�������
\param[in] pstDst  Ŀ��λͼ
\param[in] pstDstRect  Ŀ��λͼ�Ĳ�������
\param[in] pstFillColor  ���ɫ�ṹ��
\param[in] pstOpt  �������Խṹ��
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  �ڴ治�㣬�޷���Ӳ���
\retval ::HI_ERR_TDE_NOT_ALIGNED  Clut�����ʼ��ַû�а���4byte����
\retval ::HI_ERR_TDE_MINIFICATION  ��С��������
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  λͼ�ĸ�ʽ������֧�ִ˲���
\retval ::HI_ERR_TDE_CLIP_AREA  ����������Clip����û�н�������ʾ�����и���
\retval ::HI_FAILURE  ϵͳ�����δ֪����
\see \n
��
*/
HI_S32      HI_TDE2_SolidDraw(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect,
                              TDE2_SURFACE_S *pstDst,
                              TDE2_RECT_S  *pstDstRect, TDE2_FILLCOLOR_S *pstFillColor,
                              TDE2_OPT_S *pstOpt);


/** 
\brief ����������ӶԺ��λͼ�����и��ӹ��ܵİ��Ʋ����������Ⱥ�ɫ�Ⱥ�����ݺϲ��ɹ�դ��ʽ�����԰������š�����˸��Clip����
\attention \n
�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
����YCbCr422��ʽ�ĺ�飬����������ʼ��ˮƽ���������ż��\n
Ŀ��λͼ������YCbCr��ɫ�ռ�\n
 	 	 	
\param[in] s32Handle  TDE������
\param[in] pstMB  ���surface
\param[in] pstMbRect  ����������
\param[in] pstDst  Ŀ��λͼ
\param[in] pstDstRect  Ŀ���������
\param[in] pstMbOpt  ����������
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  �ڴ治�㣬�޷���Ӳ���
\retval ::HI_ERR_TDE_MINIFICATION  ��С�����������ƣ����Ϊ��С15����
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  λͼ�ĸ�ʽ������֧�ִ˲���
\retval ::HI_ERR_TDE_CLIP_AREA  ����������Clip����û�н�������ʾ�����и���
\retval ::HI_FAILURE  ϵͳ�����δ֪����
\see \n
��
*/
HI_S32      HI_TDE2_MbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect,
                           TDE2_MBOPT_S* pstMbOpt);


/** 
\brief ����������ӶԹ�դλͼ����Mask Rop���Ʋ���������Maskλͼʵ��ǰ��λͼ�ͱ���λͼROP��Ч��
\attention \n
�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
����λͼ�Ĳ��������С����һ��\n
Maskλͼ������A1��ʽ��λͼ\n
Ŀ��λͼ��ǰ��λͼ����λ��ͬһ��ɫ�ռ�\n
 	 	 	 	
\param[in] s32Handle  TDE������
\param[in] pstBackGround  ����λͼ
\param[in] pstBackGroundRect  ����λͼ��������
\param[in] pstForeGround  ǰ��λͼ
\param[in] pstForeGroundRect  ǰ��λͼ��������
\param[in] pstMask  Maskλͼ
\param[in] pstMaskRect  Maskλͼ��������
\param[in] pstDst  Ŀ��λͼ
\param[in] pstDstRect  Ŀ��λͼ��������
\param[in] enRopCode_Color  ��ɫ������ROP������
\param[in] enRopCode_Alpha  Alpha������ROP������
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  �ڴ治�㣬�޷���Ӳ���
\retval ::HI_FAILURE  ϵͳ�����δ֪����
\see \n
��
*/
HI_S32      HI_TDE2_BitmapMaskRop(TDE_HANDLE s32Handle, 
                                  TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                                  TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect,
                                  TDE2_SURFACE_S* pstMask, TDE2_RECT_S  *pstMaskRect, 
                                  TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect,
                                  TDE2_ROP_CODE_E enRopCode_Color, TDE2_ROP_CODE_E enRopCode_Alpha);


/** 
\brief ����������ӶԹ�դλͼ����Mask Blend���Ʋ���������Maskλͼʵ��ǰ��λͼ�ͱ���λͼ��Maskλͼ�ĵ���Ч��
\attention \n
�ڵ��ô˽ӿ�ǰӦ��֤����HI_TDE2_Open��TDE�豸�����ҵ���HI_TDE2_BeginJob�������Ч��������\n
Ŀ��λͼ�ͱ���λͼ����λ��ͬһ��ɫ�ռ�\n
���ǰ����λͼ��Ԥ���˵����ݣ�Alpha����ģʽӦ��ѡ��Ԥ��ģʽ������ѡ���Ԥ��ģʽ\n
enBlendMode����ѡ��TDE2_ALUCMD_ROPģʽ\n

\param[in] s32Handle  TDE������
\param[in] pstBackGround  ����λͼ
\param[in] pstBackGroundRect  ����λͼ��������
\param[in] pstForeGround  ǰ��λͼ
\param[in] pstForeGroundRect  ǰ��λͼ��������
\param[in] pstMask  Maskλͼ
\param[in] pstMaskRect  Maskλͼ��������
\param[in] pstDst  Ŀ��λͼ
\param[in] pstDstRect  Ŀ��λͼ��������
\param[in] u8Alpha  Alpha����ʱ��ȫ��Alphaֵ
\param[in] enBlendMode  Alpha����ģʽѡ��
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\retval ::HI_ERR_TDE_NO_MEM  �ڴ治�㣬�޷���Ӳ���
\retval ::HI_FAILURE  ϵͳ�����δ֪����
\see \n
��
*/
HI_S32      HI_TDE2_BitmapMaskBlend(TDE_HANDLE s32Handle, 
                                    TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                                    TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect,
                                    TDE2_SURFACE_S* pstMask, TDE2_RECT_S  *pstMaskRect,
                                    TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect,
                                    HI_U8 u8Alpha, TDE2_ALUCMD_E enBlendMode);


/** 
\brief  �������������ת����
\attention \n
Դ��Ŀ������ظ�ʽ������ͬ�����Ҳ�����YUV��CLUT1��CLUT4��ʽ\n
����s32DstPointX��s32DstPointYĬ��Ϊ0��Ŀǰ����������û���õ������������κ�ֵ\n

\param[in] s32Handle  TDE������
\param[in] pstSrc  Դλͼ
\param[in] pstSrcRect  Դλͼ��������
\param[in] pstDst  Ŀ��λͼ
\param[in] s32DstPointX  Ŀ��λͼ�����������ʼ�������
\param[in] s32DstPointY  Ŀ��λͼ�����������ʼ��������
\param[in] enRotateAngle  ��ת�ĽǶ�
\retval 0 �ɹ�
\retval ::HI_ERR_TDE_DEV_NOT_OPEN  TDE�豸δ�򿪣�API����ʧ��
\retval ::HI_ERR_TDE_INVALID_HANDLE  �Ƿ���������
\retval ::HI_ERR_TDE_NULL_PTR  �������п�ָ�����
\retval ::HI_ERR_TDE_UNSUPPORTED_OPERATION  ��֧�ֵĲ���
\retval ::HI_ERR_TDE_INVALID_PARA  ��Ч�Ĳ�������
\see \n
��
*/
HI_S32 HI_TDE2_Rotate(TDE_HANDLE s32Handle, 
                    TDE2_SURFACE_S *pstSrc, TDE2_RECT_S *pstSrcRect, 
                    TDE2_SURFACE_S *pstDst, HI_S32 s32DstPointX,  HI_S32 s32DstPointY,
                    TDE_ROTATE_ANGLE_E enRotateAngle);



/** 
\brief ���ÿ���˸����
\attention \n
��
\param[in] enDeflickerLevel  ����˸ϵ������
\retval 0 �ɹ�
\retval ::

\see none
*/
HI_S32 HI_TDE2_SetDeflickerLevel(TDE_DEFLICKER_LEVEL_E enDeflickerLevel);


/** 
\brief ��ȡ����˸����
\attention \n
��
\param[in] pDeflickerLevel  ����˸����
\retval 0 �ɹ�
\retval ::

\see \n
��
*/
HI_S32 HI_TDE2_GetDeflickerLevel(TDE_DEFLICKER_LEVEL_E *pDeflickerLevel);


/** 
\brief ����alpha�о���ֵ
\attention \n
��
\param[in] u8ThresholdValue  �о���ֵ
\retval 0 �ɹ�
\retval ::

\see \n
��
*/
HI_S32 HI_TDE2_SetAlphaThresholdValue(HI_U8 u8ThresholdValue);


/** 
\brief ��ȡalpha�о���ֵ
\attention \n
��
\param[in] pu8ThresholdValue  �о���ֵ
\retval 0 �ɹ�
\retval ::

\see \n
��
*/
HI_S32 HI_TDE2_GetAlphaThresholdValue(HI_U8 *pu8ThresholdValue);


/** 
\brief ����alpha�о�����
\attention ��
\param[in] bEnAlphaThreshold  alpha�о�����
\retval 0 �ɹ�
\retval ::
\see \n
��
*/
HI_S32 HI_TDE2_SetAlphaThresholdState(HI_BOOL bEnAlphaThreshold);


/** 
\brief ��ȡalpha�о�����
\attention ��
\param[in]  p_bEnAlphaThreshold  alpha�о�����
\retval 0 �ɹ�
\retval ::

\see \n
��
*/
HI_S32 HI_TDE2_GetAlphaThresholdState(HI_BOOL * p_bEnAlphaThreshold);


/** 
\brief ģʽ���
\attention ��
\param[in] s32Handle  ������
\param[in] pstBackGround  ����λͼ��Ϣ
\param[in] pstBackGroundRect  ������������
\param[in] pstForeGround  ǰ��λͼ��Ϣ
\param[in] pstForeGroundRect  ǰ��λ��������
\param[in] pstDst  Ŀ��λͼ��Ϣ
\param[in] pstDstRect  Ŀ���������
\param[in] pstOpt  ģʽ������ѡ��
\retval 0 �ɹ�
\retval ::

\see \n
��
*/
HI_S32 HI_TDE2_PatternFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S *pstBackGround, 
                           TDE2_RECT_S *pstBackGroundRect, TDE2_SURFACE_S *pstForeGround,
                           TDE2_RECT_S *pstForeGroundRect, TDE2_SURFACE_S *pstDst,
                           TDE2_RECT_S *pstDstRect, TDE2_PATTERN_FILL_OPT_S *pstOpt);

/** 
\brief ʹ��/ȥʹ�ֲܾ�����˸
\attention ��
\param[in] bRegionDeflicker  ʹ��/ȥʹ�ܱ�־
\retval 0 �ɹ�
\retval ::

\see \n
��
*/
HI_S32 HI_TDE2_EnableRegionDeflicker(HI_BOOL bRegionDeflicker);


#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* _HI_API_TDE2_H_ */
