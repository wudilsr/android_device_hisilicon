/******************************************************************************
Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : vmx_ssd.h
Version       : Initial Draft
Author        : Hisilicon hisecurity team
Created       : 2014/09/24
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/

#ifndef __LOADER_VMX_SSD_H__
#define __LOADER_VMX_SSD_H__

#include "../../../../api/src/cx_ssd.h"

/**
\brief authenticate the data CNcomment:�����ݽ���У��
\param[in]  StartVirAddr start virtual address of data CNcomment:StartVirAddr ������ʼ�����ַ
\param[out] CodeAddr  real Code address CNcomment:length ��������������ĵ�ַ
\retval ::HI_SUCCESS  success CNcomment:�ɹ�
\retval ::HI_FAILURE failure CNcomment:ʧ��
\see \n
*/
HI_S32 VMX_Authenticate(HI_U8* pu8StartVirAddr,HI_U32* pu32CodeOffset);

/**
\brief authenticate the data CNcomment:�����ݽ���У��
\param[in]  StartVirAddr start virtual address of data CNcomment:StartVirAddr ������ʼ�����ַ
\param[in]  Addrlength  data  length CNcomment:Addrlength ���ݳ���
\decryption:Signature data use the structure of HI_CASignImageTail_S.
\retval ::HI_SUCCESS  success CNcomment:�ɹ�
\retval ::HI_FAILURE failure CNcomment:ʧ��
\see \n
*/
HI_S32 VMX_CommonVerify_Authenticate(HI_U8* pu8StartVirAddr,HI_U32 u32Addrlength);

/**
\brief authenticate the data CNcomment:�����ݽ���У��
\param[in]  StartVirAddr start virtual address of data CNcomment:StartVirAddr ������ʼ�����ַ
\param[in]  length  data  length CNcomment:length ���ݳ���
\decryption:Signature data use the structure of HI_CASignImageTail_S.
\retval ::HI_SUCCESS  success CNcomment:�ɹ�
\retval ::HI_FAILURE failure CNcomment:ʧ��
\see \n
*/
HI_S32 VMX_CommonVerify_AuthenticateEx(HI_U8* pu8StartVirAddr,HI_U32 u32Addrlength, HI_CASignImageTail_S *pstSignImageInfo);

/**
\brief authenticate the data, no matter the authenticate type is common or special CNcomment:�����ݽ���У�飬��������Common��Special
\param[in]  StartVirAddr start virtual address of data CNcomment:StartVirAddr ������ʼ�����ַ
\param[in]  Addrlength  data  length CNcomment:Addrlength ���ݳ���
\decryption:Signature data use the structure of HI_CASignImageTail_S.
\retval ::HI_SUCCESS  success CNcomment:�ɹ�
\retval ::HI_FAILURE failure CNcomment:ʧ��
\see \n
*/
HI_S32 VMX_Verify_Authenticate(HI_U8* pu8StartVirAddr, HI_U32 u32Addrlength, HI_U32 u32FlashStartAddr, HI_U32 u32FlashType);

HI_S32 HI_VMX_Authenticate(HI_U8* BlockStartAddr, HI_S32 Blocklength, HI_U8* sign);

#endif /* __LOADER_VMX_SSD_H__ */

