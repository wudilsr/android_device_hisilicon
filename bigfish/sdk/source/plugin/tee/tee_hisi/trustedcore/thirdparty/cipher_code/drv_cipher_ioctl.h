/******************************************************************************

  Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_cipher_ioctl.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 
  Last Modified :
  Description   : 
  Function List :
  History       :
******************************************************************************/

#ifndef __DRV_CIPHER_IOCTL_H__
#define __DRV_CIPHER_IOCTL_H__

#include "hi_type.h"
#include "drv_cipher_define.h"
#include "drv_cipher_ioctl.h"
#include "hi_drv_cipher.h"


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */


/* special handle creation parameter */
typedef struct  hiCIPHER_HANDLE_S
{
    HI_HANDLE hCIHandle;
    HI_UNF_CIPHER_ATTS_S stCipherAtts;
}CIPHER_HANDLE_S;

typedef struct hiCIPHER_Config_CTRL
{
    HI_HANDLE CIHandle;
    HI_UNF_CIPHER_CTRL_S CIpstCtrl;
}CIPHER_Config_CTRL;


typedef struct hiCIPHER_PROC_ITEM_S
{
    HI_U32    u32Resv;
}CIPHER_PROC_ITEM_S;

typedef enum
{
    HI_CIPHER_HMAC_KEY_FROM_CA  = 0,
    HI_CIPHER_HMAC_KEY_FROM_CPU = 1,
}CIPHER_HMAC_KEY_FROM_E;

typedef struct hiCIPHER_HASH_DATA_S
{
    HI_HANDLE hHandle;
    HI_UNF_CIPHER_HASH_TYPE_E enShaType;
    HI_U32 u32TotalDataLen;
    HI_U8  *pu8InputData;
    HI_U32 u32InputDataLen;
    /* max padding data (64bytes) | fix data length(8bytes) */
    HI_U8  u8Padding[64+8];
    HI_U32 u32PaddingLen;
    HI_U8  u8HMACKey[16];
    CIPHER_HMAC_KEY_FROM_E enHMACKeyFrom;
    HI_U8  *pu8Output;
}CIPHER_HASH_DATA_S;

typedef struct hiOTP_HDCPKEY_S
{
	HI_U8 HdcpKey[320];
}OTP_HDCPKEY_S;

typedef struct
{
    HI_BOOL bIsUseOTPRootKey;
    HI_UNF_HDCP_HDCPKEY_S stHdcpKey;
    HI_U8 u8FlashEncryptedHdcpKey[332];
}OTP_HDCP_KEY_TRANSFER_S;

typedef enum {
    CIPHER_TEST_PRINT_PHY = 0x01,
    CIPHER_TEST_PRINT_VIA,  
    CIPHER_TEST_AES  = 0x10,
    CIPHER_TEST_HMAC,
    CIPHER_TEST_RSA,
    CIPHER_TEST_HASH,
    CIPHER_TEST_DES,
    CIPHER_TEST_RSA_PRIM,
    CIPHER_TEST_RSA_KG,
    CIPHER_TEST_RND,  
    CIPHER_TEST_BUTT,
}CIPHER_TEST;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_CIPHER_IOCTL_H__*/
