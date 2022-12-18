/******************************************************************************

Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : ca_ssd.h
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/
#ifndef __CA_SSD_H__
#define __CA_SSD_H__

#ifdef HI_LOADER_APPLOADER

#ifdef HI_ADVCA_TYPE_NAGRA
#include "nasc1x_ssd.h"
#endif
#include "../../api/src/ca_ssd.h"

typedef HI_S32 (*SSD_Burn_CallBack)(HI_HANDLE hFlash, 
									HI_U64 u64FlashAddress, 
									HI_U8 *pBuf, 
									HI_U32 u32Len, 
									HI_U32 u32Flags);


#ifdef HI_ADVCA_SUPPORT
/* 
 Descryption�� Loader SSD�ĳ�ʼ����
 return��HI_SUCCESSΪ�ɹ���
 */
HI_S32 CA_SSD_Init(HI_VOID);

/* 
 Descryption:   Loader SSD��ȥ��ʼ��
 return��HI_SUCCESSΪ�ɹ���
*/

HI_S32 CA_SSD_DeInit(HI_VOID);

/*
 Descryption�� �����������ݰ�
 param pu8StartVirAddr [in/out]: ��Ҫ���ܵ��������ݰ�Buffer��ʼ��ַ��
 param u32Len [in]: ��Ҫ���ܵ��������ݰ��ܳ��ȡ�
 return��HI_SUCCESSΪ�ɹ���
 */
HI_S32 CA_SSD_DecryptUpgradeImage(HI_U8 *pu8StartVirAddr, HI_U32 u32Len);

/*
 Descryption�� �Խ�Ҫ�������������ݰ�����Ԥ�������ȴ������������
 param pu32LoaderHeader [in]: ���ܺ���������ݰ�buffer��ʼ��ַ��
 param u32HeaderLen [in]: ���ݰ��ܳ��ȡ�
 return��HI_SUCCESSΪ�ɹ���
 */
HI_S32 CA_SSD_AuthenticatePrepare(const HI_U32 *pu32LoaderHeader, HI_U8 *pu8FileBuffer, HI_U32 u32HeaderLen);

/* 
 Descryption�� У��Loader�������񣬰������ܾ���У�龵�������ֲ��������в���u32StartFlashAddr ��u32EndFlashAddr �����жϣ��Ƿ��к�CADATA������conax����ͻ���Ƿ����DA2������nagra����
 param pu8StartVirAddr [in]:��ҪУ���Buffer��ʼ��ַ��
 param u32Len [in]�� ��ҪУ���Buffer�ĳ��ȡ�
 param u32StartFlashAddr [in]�� ��������Flash��ʼ��ַ��
 param u32EndFlashAddr [in]�� ��������Flash�Ľ�����ַ��
 return��HI_SUCCESSΪ�ɹ���
*/
HI_S32 CA_SSD_Authenticate(HI_U8 *ppu8Buffer, HI_U32 *pu32Len, HI_U32 u32FlashStartAddr, HI_U32 u32FlashType);

HI_S32 CA_SSD_BurnImageToFlash(HI_HANDLE hFlash, 
										HI_U64 u64FlashAddress, 
										HI_U8 *pBuf, 
										HI_U32 u32Len, 
										HI_U32 u32Flags,
										HI_FLASH_TYPE_E enFlashType,
										SSD_Burn_CallBack pFuncCallBackBurnData);

#else           /*#ifdef HI_ADVCA_SUPPORT*/

static inline HI_S32 CA_SSD_Init(HI_VOID){ return HI_SUCCESS;}

static inline HI_S32 CA_SSD_DeInit(HI_VOID) { return HI_SUCCESS;}

static inline HI_S32 CA_SSD_DecryptUpgradeImage(HI_U8 *pu8StartVirAddr, HI_U32 u32Len) { return HI_SUCCESS;}

static inline HI_S32 CA_SSD_AuthenticatePrepare(const HI_U32 *pu32LoaderHeader, HI_U8 *pu8FileBuffer, HI_U32 u32HeaderLen) { return HI_SUCCESS;}

static inline HI_S32 CA_SSD_Authenticate(HI_U8 *pu8StartVirAddr, HI_U32 *pu32Len, HI_U32 u32FlashStartAddr, HI_U32 u32FlashType) { return HI_SUCCESS;}

static inline HI_S32 CA_SSD_BurnImageToFlash(HI_HANDLE hFlash, 
										HI_U64 u64FlashAddress, 
										HI_U8 *pBuf, 
										HI_U32 u32Len, 
										HI_U32 u32Flags,
										HI_FLASH_TYPE_E enFlashType,
										SSD_Burn_CallBack pFuncCallBackBurnData)
{
	return pFuncCallBackBurnData(hFlash, u64FlashAddress, pBuf, u32Len, u32Flags);
}

#endif  /*HI_ADVCA_SUPPORT*/

#else
/* crypto key type */
typedef enum CA_SSD_KEY_TYPE
{
    CA_SSD_KEY_GROUP1,
    CA_SSD_KEY_GROUP2,
    CA_SSD_KEY_BUTT,
}CA_SSD_KEY_TYPE;

static inline HI_S32 CA_SSD_DecryptImage(HI_U8 *pu8StartVirAddr, HI_U32 u32Len, CA_SSD_KEY_TYPE enKeyType) { return HI_SUCCESS;}

static inline HI_S32 CA_SSD_EncryptImage(HI_U8 *pu8StartVirAddr, HI_U32 u32Len, CA_SSD_KEY_TYPE enKeyType) { return HI_SUCCESS;}

static inline HI_S32 CA_SSD_AuthenticateEx(HI_U8 *ppu8Buffer, HI_U32 *pu32Len) { return HI_SUCCESS;}

#endif  /*HI_LOADER_APPLOADER*/

#endif  /*__CA_SSD_H__*/

