/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Hisilicon Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv/JzwTgKEHe/9N4yU5rqhECzcd0qHjxrE76U1z7jqu9Y5M3Mt4N+LrDnKskR
p9kctiNm0guWTA37fbbZiinVgD48B6Yq5+hplNfA+qygU8oBM1QgCuHJ6r207ReVg/THafdw
CY9XSq9qY7SDA2xE9/gA+WiE0TYlOOKXmHbgIbDoTVoumTCxqqjQFB1PrYdtLQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************

  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
    �� �� ��   : vdmv300plus_hal.h
    �� �� ��   : ����
    ��    ��   : 
    ��������   : 
    ����޸�   :
    ��������   : VDMV300plusӲ������
         

  �޸���ʷ   :
    1.��    �� : 2009-03-04
    ��    ��   : 
    �޸�����   : 

******************************************************************************/

#ifndef __VDM_HAL_V200R004_H264_H__
#define __VDM_HAL_V200R004_H264_H__

#include "basedef.h"
#include "mem_manage.h"

#ifdef __cplusplus
extern "C" {
#endif

SINT32 H264HAL_V200R004_InitHal(SINT32 H264MnAddr);
SINT32 H264HAL_V200R004_StartDec(H264_DEC_PIC_PARAM_S *pParam, SINT32 VdhId);

#ifdef __cplusplus
}
#endif


#endif //__VDM_HAL_H264_H__
