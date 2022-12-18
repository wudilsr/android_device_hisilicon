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
* Description:   ���TDE ������
* Input:         ps32Handle:��ȡ��������ָ��
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiBeginJob(TDE_HANDLE *ps32Handle);

/*****************************************************************************
* Function:      TdeOsiEndJob
* Description:   �ύTDE����
* Input:         s32Handle: ������
*                bBlock: �Ƿ�����
*                u32TimeOut: ��ʱʱ��ֵ(10msΪ��λ)
*                bSync: �ύ����ͬ�����������첽����
*                pFuncComplCB: ��ɲ����ص�����
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiEndJob(TDE_HANDLE s32Handle, HI_BOOL bBlock, HI_U32 u32TimeOut, 
                    HI_BOOL bSync, TDE_FUNC_CB pFuncComplCB, HI_VOID *pFuncPara);

/*****************************************************************************
* Function:      TdeOsiCancelJob
* Description:   ɾ��������TDE����,ֻ����EndJob֮ǰ���òŻ���Ч,
*                �����ͷ���Ӧ�������Ӧ������������Դ
* Input:         s32Handle: ������
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32     TdeOsiCancelJob(TDE_HANDLE s32Handle);


/*****************************************************************************
* Function:      TdeOsiQuickFill
* Description:   ���ٽ��̶�ֵ��䵽Ŀ��λͼ��
* Input:         s32Handle: ������
*                pDst: Ŀ��λͼ��Ϣ�ṹ
*                pstDstRect: Ŀ��λͼ��������
*                u32FillData: ���ֵ��Ϣ�����ظ�ʽҪ��Ŀ��λͼ����һ��
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32     TdeOsiQuickFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect,
                           HI_U32 u32FillData);

/*****************************************************************************
* Function:      TdeOsiBlit
* Description:   ��pstBackGround��pstForeGround��λͼ�������㽫��������pDst�У�����������pOpt
* Input:         s32Handle: ������
*                pstBackGround: ����λͼ��Ϣ�ṹ
*                pstBackGroundRect: ����λͼ��������
*                pstForeGround: ǰ��λͼ��Ϣ�ṹ
*                pstForeGroundRect: ǰ��λͼ��������
*                pstDst:  Ŀ��λͼ��Ϣ�ṹ
*                pstDstRect:  Ŀ��λͼ��������
*                pOpt:  ����������ýṹ
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32     TdeOsiBlit(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                          TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect, TDE2_SURFACE_S* pstDst,
                          TDE2_RECT_S  *pstDstRect, TDE2_OPT_S* pOpt);

/*****************************************************************************
* Function:      TdeOsiMbBlit
* Description:   ��鴦��ӿ�
* Input:         s32Handle: ������
*                pstMB: ���λͼ��Ϣ�ṹ
*                pstMbRect: ���λͼ��������
*                pstDst: Ŀ��λͼ��Ϣ�ṹ
*                pstDstRect:  Ŀ��λͼ��������
*                pstMbOpt:  ����������ýṹ
* Output:        ��
* Return:        >0: ���ص�ǰ�������������id ; <0: ʧ��
* Others:        ��
*****************************************************************************/
HI_S32     TdeOsiMbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, 
                        TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect, TDE2_MBOPT_S* pstMbOpt);

/*****************************************************************************
* Function:      TdeOsiSetAlphaThreshold
* Description:   ����alpha�о���ֵ
* Input:         ��
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiSetAlphaThresholdValue(HI_U8 u8ThresholdValue);


/*****************************************************************************
* Function:      TdeOsiSetAlphaThresholdState
* Description:   ����alpha�о�����
* Input:         bEnAlphaThreshold:�Ƿ��alpha�о���ʶ
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiSetAlphaThresholdState(HI_BOOL bEnAlphaThreshold);


#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __TDE_OSICTL_H__ */
