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
* Description:   �ָ�����״̬,�ͷ���������
* Input:         ��
* Output:        ��
* Return:        �ɹ� / ʧ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeOsiReset(HI_VOID);

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
* Function:      TdeOsiSetDeflickerLevel
* Description:   ���ÿ���˸����
* Input:         eDeflickerLevel: ����˸����
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiSetDeflickerLevel(TDE_DEFLICKER_LEVEL_E eDeflickerLevel);

/*****************************************************************************
* Function:      TdeOsiGetDeflickerLevel
* Description:   ��ȡ����˸����
* Input:         ��
* Output:        pDeflickerLevel: ����˸����
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiGetDeflickerLevel(TDE_DEFLICKER_LEVEL_E *pDeflickerLevel);

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
* Function:      TdeOsiGetAlphaThreshold
* Description:   ��ȡalpha�о���ֵ
* Input:         ��
* Output:        pu8ThresholdValue: alpha�о���ֵ
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiGetAlphaThresholdValue(HI_U8 * pu8ThresholdValue);

/*****************************************************************************
* Function:      TdeOsiSetAlphaThresholdState
* Description:   ����alpha�о�����
* Input:         bEnAlphaThreshold:�Ƿ��alpha�о���ʶ
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiSetAlphaThresholdState(HI_BOOL bEnAlphaThreshold);

/*****************************************************************************
* Function:      TdeOsiGetAlphaThresholdState
* Description:   ��ȡalpha�о�����
* Input:         pbEnAlphaThreshold:alpha�о����ر�ʶ
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiGetAlphaThresholdState(HI_BOOL *pbEnAlphaThreshold);
/*****************************************************************************
* Function:      TdeOsiPatternFill
* Description:   ģʽ���
* Input:         ��
* Output:        s32Handle:������
                 pstBackGround:����λͼ��Ϣ
                 pstBackGroundRect:������������
                 pstForeGround:ǰ��λͼ��Ϣ
                 pstForeGroundRect:ǰ��λ��������
                 pstDst:Ŀ��λͼ��Ϣ
                 pstDstRect:Ŀ���������
                 pstOpt:ģʽ������ѡ��
* Return:        �ɹ� / ������
* Others:        ���֧��pattern���Ϊ256,�߶�û������
*****************************************************************************/

#if 0
/*****************************************************************************
* Function:      TdeOsiQuickCopy
* Description:   ���ٴ�Դ���Ƶ�Ŀ��λͼ��û���κι��ܲ�����Դ��Ŀ�Ĳ�������ߴ�һ�������ظ�ʽһ��
* Input:         s32Handle: ������
*                pSrc: Դλͼ��Ϣ�ṹ
*                pstSrcRect: Դλͼ��������
*                pDst: Ŀ��λͼ��Ϣ�ṹ
*                pstDstRect: Ŀ��λͼ��������
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32     TdeOsiQuickCopy(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect,
                           TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect);

/*****************************************************************************
* Function:      TdeOsiQuickResize
* Description:   ��Դλͼ�Ĵ�С����ΪĿ��λͼָ���Ĵ�С��Դ��Ŀ�����Ϊͬһλͼ
* Input:         s32Handle: ������
*                pSrc: Դλͼ��Ϣ�ṹ
*                pstSrcRect: Դλͼ��������
*                pDst: Ŀ��λͼ��Ϣ�ṹ
*                pstDstRect: Ŀ��λͼ��������
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32     TdeOsiQuickResize(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect,
                             TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect);


/*****************************************************************************
* Function:      TdeOsiQuickFlicker
* Description:   ��Դλͼ���п���˸�������Ŀ��λͼ��Դ��Ŀ�����Ϊͬһλͼ
* Input:         s32Handle: ������
*                pSrc: Դλͼ��Ϣ�ṹ
*                pstSrcRect: Դλͼ��������
*                pDst: Ŀ��λͼ��Ϣ�ṹ
*                pstDstRect: Ŀ��λͼ��������
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32     TdeOsiQuickFlicker(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect,
                                TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect);

/*****************************************************************************
* Function:      TdeOsiBitmapMaskRop
* Description:   ���Ƚ�Դ2��Maskλͼ����RopMask, Ȼ����Դ1���м�λͼRopMask��
*                ����������Ŀ��λͼ�С�
* Input:         s32Handle: ������
*                pstBackGround: ����λͼ��Ϣ�ṹ
*                pstBackGroundRect: ����λͼ��������
*                pstForeGround: ǰ��λͼ��Ϣ�ṹ
*                pstForeGroundRect: ǰ��λͼ��������
*                pstMask: �����������λͼ��Ϣ�ṹ
*                pstMaskRect: �����������λͼ��������
*                pstDst:  Ŀ��λͼ��Ϣ�ṹ
*                pstDstRect:  Ŀ��λͼ��������
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32     TdeOsiBitmapMaskRop(TDE_HANDLE s32Handle, 
                        TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                        TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForGroundRect, 
                        TDE2_SURFACE_S* pstMask, TDE2_RECT_S  *pstMaskRect,
                        TDE2_SURFACE_S* pDst, TDE2_RECT_S  *pstDstRect,
                        TDE2_ROP_CODE_E enRopCode_Color, TDE2_ROP_CODE_E enRopCode_Alpha);

/*****************************************************************************
* Function:      TdeOsiBitmapMaskBlend
* Description:   ���Ƚ�Դ2��Maskλͼ����BlendMask, Ȼ����Դ1���м�λͼBlend��
*                ����������Ŀ��λͼ�С�
* Input:         s32Handle: ������
*                pstBackGround: ����λͼ��Ϣ�ṹ
*                pstBackGroundRect: ����λͼ��������
*                pstForeGround: ǰ��λͼ��Ϣ�ṹ
*                pstForeGroundRect: ǰ��λͼ��������
*                pstMask: �����������λͼ��Ϣ�ṹ
*                pstMaskRect: �����������λͼ��������
*                pstDst:  Ŀ��λͼ��Ϣ�ṹ
*                pstDstRect:  Ŀ��λͼ��������
*                u8Alpha:  ��������Alpha��ֵ
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32     TdeOsiBitmapMaskBlend(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                                 TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForGroundRect, TDE2_SURFACE_S* pstMask,
                                 TDE2_RECT_S  *pstMaskRect, TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect,
                                 HI_U8 u8Alpha, TDE2_ALUCMD_E enBlendMode);


/*****************************************************************************
* Function:      TdeOsiSolidDraw
* Description:   ����ɫֵ��Դλͼ�������㽫��������pDst�У�����������pOpt
* Input:         s32Handle: ������
*                pSrc: Դλͼ��Ϣ�ṹ
*                pstDst: Ŀ��λͼ��Ϣ�ṹ
*                pstFillColor:  ��ɫ��Ϣ
*                pstOpt:  ����������ýṹ
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32  TdeOsiSolidDraw(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc, TDE2_RECT_S  *pstSrcRect, TDE2_SURFACE_S *pstDst,
                           TDE2_RECT_S  *pstDstRect, TDE2_FILLCOLOR_S *pstFillColor, TDE2_OPT_S *pstOpt);

/*****************************************************************************
* Function:      TdeOsiRegisterTrigFunc
* Description:   �ú�������VOע��TDEͬ�������ź����ýӿ�
* Input:         TDE_TRIG_SEL: ͬ�������ź�����callback����ָ��
* Output:        ��
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiTriggerSel(HI_U32 u32TrigSel);

HI_S32 TdeOsiPatternFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S * pstBackGround, 
    TDE2_RECT_S * pstBackGroundRect, TDE2_SURFACE_S * pstForeGround, 
    TDE2_RECT_S * pstForeGroundRect, TDE2_SURFACE_S * pstDst, 
    TDE2_RECT_S * pstDstRect, TDE2_PATTERN_FILL_OPT_S *pstOpt);

/*****************************************************************************
* Function:      TdeOsiEnableRegionDeflicker
* Description:   ʹ��/ȥʹ�ֲܾ�����˸
* Input:         ��
* Output:        bRegionDeflicker:�Ƿ�ʹ�ܱ�־
* Return:        �ɹ� / ������
* Others:        ��
*****************************************************************************/
HI_S32 TdeOsiEnableRegionDeflicker(HI_BOOL bRegionDeflicker);
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* _TDE_OSICTL_H_ */
