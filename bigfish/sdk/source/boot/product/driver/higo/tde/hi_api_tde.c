/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           :hi_api_tde.c
Version             : Initial Draft
Author              : 
Created             : 2014/08/06
Description         :
Function List       : 
History             :
Date                       Author                   Modification
2014/08/06                 y0081162                 Created file        
******************************************************************************/

/*********************************add include here******************************/
#include "tde_osictl.h"

#include "hi_tde_api.h"
#include "tde_define.h"


/***************************** Macro Definition ******************************/
#define TDE_CHECK_FD() \
    do {                                         \
        if (0 == g_s32TDeRef)                    \
        {                                        \
            return HI_ERR_TDE_DEV_NOT_OPEN;      \
        }                                        \
    } while (0)

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

static HI_S32 g_s32TDeRef = 0;

/******************************* API declaration *****************************/

extern int  tde_osr_init(void);
extern void tde_osr_deinit(void);

HI_S32 HI_TDE2_Open(HI_VOID)
{
    HI_S32 s32Ret;
    
    if (g_s32TDeRef)
    {
        g_s32TDeRef++;
        return HI_SUCCESS;
    }

    /* ��ʼ���ڴ桢�Ĵ�����״̬�� */
    s32Ret = tde_osr_init();
    if (s32Ret < 0)
    {
        return HI_ERR_TDE_DEV_OPEN_FAILED;
    }
    
    g_s32TDeRef++;
    return HI_SUCCESS;
}

HI_VOID HI_TDE2_Close(HI_VOID)
{
    if (g_s32TDeRef == 0)
    {
        return;
    }
    
    g_s32TDeRef--;
    
    if(g_s32TDeRef > 0)
    {
        return ;
    }

    /* ȥ��ʼ���ڴ桢�Ĵ�����״̬�� */
    tde_osr_deinit();

    return;
}

TDE_HANDLE  HI_TDE2_BeginJob(HI_VOID)
{
    TDE_HANDLE s32Handle;

    TDE_CHECK_FD();

    if (TdeOsiBeginJob(&s32Handle) < 0)
    {
        return HI_ERR_TDE_INVALID_HANDLE;
    }

    return s32Handle;
}

HI_S32 HI_TDE2_Bitblit(TDE_HANDLE s32Handle, TDE2_SURFACE_S * pstBackGround, TDE2_RECT_S * pstBackGroundRect,
                       TDE2_SURFACE_S * pstForeGround, TDE2_RECT_S * pstForeGroundRect, TDE2_SURFACE_S * pstDst,
                       TDE2_RECT_S * pstDstRect,
                       TDE2_OPT_S * pstOpt)
{
    return TdeOsiBlit(s32Handle, pstBackGround, pstBackGroundRect, pstForeGround, pstForeGroundRect, pstDst, pstDstRect, pstOpt);
}

/*****************************************************************************
* Function:      HI_TDE2_QuickFill
* Description:   ���ٽ��̶�ֵ��䵽Ŀ��λͼ��
* Input:         s32Handle: ������
*                pDst: Ŀ��λͼ��Ϣ�ṹ
*                u32FillData: ���ֵ��Ϣ�����ظ�ʽҪ��Ŀ��λͼ����һ��
* Output:        ��
* Return:        >0: ���ص�ǰ�������������id ; <0: ʧ��
* Others:        ��
*****************************************************************************/
HI_S32   HI_TDE2_QuickFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect,
                           HI_U32 u32FillData)
{
    TDE_CHECK_FD();
    if ((NULL == pstDst) || (NULL == pstDstRect))
    {
        return HI_ERR_TDE_NULL_PTR;
    }

    return TdeOsiQuickFill(s32Handle, pstDst, pstDstRect, u32FillData);
}

/*****************************************************************************
* Function:      HI_TDE2_EndJob
* Description:   �ύTDE2����
* Input:         s32Handle: ������
*                bSync:�Ƿ�ͬ��
*                bBlock: �Ƿ�����
*                u32TimeOut: ��ʱʱ��ֵ(10msΪ��λ)
* Output:        ��
* Return:        �ɹ� / ʧ��
* Others:        ��
*****************************************************************************/
HI_S32   HI_TDE2_EndJob(TDE_HANDLE s32Handle, HI_BOOL bSync, HI_BOOL bBlock, HI_U32 u32TimeOut)
{
    TDE_CHECK_FD();
    
    return TdeOsiEndJob(s32Handle, bBlock, u32TimeOut, bSync, HI_NULL, HI_NULL);
}

/*****************************************************************************
* Function:      HI_TDE2_MbBlit
* Description:   ��鴦��ӿ�
* Input:         s32Handle: ������
*                pY:    ���ȿ���Ϣ�ṹ
*                pCbCr: ɫ�ȿ���Ϣ�ṹ
*                pDst:  Ŀ��λͼ��Ϣ�ṹ
*                pMbOpt:  ����������ýṹ
* Output:        ��
* Return:        >0: ���ص�ǰ�������������id ; <0: ʧ��
* Others:        ��
*****************************************************************************/
HI_S32      HI_TDE2_MbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, TDE2_SURFACE_S* pstDst,
                           TDE2_RECT_S  *pstDstRect,
                           TDE2_MBOPT_S* pstMbOpt)
{
    TDE_CHECK_FD();

    if ((NULL == pstMB) || (NULL == pstDst) || (NULL == pstMbOpt))
    {
        return HI_ERR_TDE_NULL_PTR;
    }

    return TdeOsiMbBlit(s32Handle, pstMB, pstMbRect, pstDst, pstDstRect, pstMbOpt);
}


HI_S32 HI_TDE2_SetAlphaThresholdValue(HI_U8 u8ThresholdValue)
{
    TDE_CHECK_FD();

    return TdeOsiSetAlphaThresholdValue(u8ThresholdValue);
}

HI_S32 HI_TDE2_SetAlphaThresholdState(HI_BOOL bEnAlphaThreshold)
{
    TDE_CHECK_FD();

    return TdeOsiSetAlphaThresholdState(bEnAlphaThreshold);
}
