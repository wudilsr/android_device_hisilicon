/******************************************************************************
 *
 * Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tz_unf_cipher.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   : 
 * Function List :
 * History       :
 * ******************************************************************************/

#ifndef __TZ_UNF_CIPHER_H__
#define __TZ_UNF_CIPHER_H__

#include "drv_cipher_define.h"
#include "drv_cipher_ioctl.h"
#include "hi_type.h"

HI_S32 TZ_UNF_CIPHER_Init(HI_VOID);
HI_VOID TZ_UNF_CIPHER_DeInit(HI_VOID);
HI_S32 TZ_UNF_CIPHER_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr);
HI_S32 TZ_UNF_CIPHER_DestroyHandle(HI_HANDLE hCipher);
HI_S32 TZ_UNF_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl);
HI_S32 TZ_UNF_CIPHER_GetHandleConfig(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl);
HI_S32 TZ_UNF_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
HI_S32 TZ_UNF_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);
HI_S32 TZ_UNF_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 TZ_UNF_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum);
HI_S32 TZ_UNF_CIPHER_GetRandomNumber(HI_U32 *pu32Rnd);
HI_S32 TZ_UNF_CIPHER_EncryptHdcpKey(OTP_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer);
HI_S32 TZ_UNF_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey);
HI_S32 TZ_UNF_CIPHER_GetIVOut(HI_HANDLE hCipher, HI_U8 *pu8IVOut);
HI_S32 TZ_UNF_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle);
HI_S32 TZ_UNF_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen);
HI_S32 TZ_UNF_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash);
HI_S32 TZ_UNF_CIPHER_Test(HI_U32 u32Cmd, HI_U32 *pu32Result, HI_U32 u32Param1, HI_U32 u32Param2);

#endif

