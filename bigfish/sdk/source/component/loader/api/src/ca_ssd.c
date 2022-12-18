/******************************************************************************

Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : ca_ssd.c
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "hi_common.h"
#include "hi_flash.h"
#include "ca_ssd.h"

#if defined(HI_ADVCA_SUPPORT) && !defined(HI_ADVCA_TYPE_NAGRA)
#include "cx_ssd.h"
#endif

#define LOADER_BOOT         "boot"
#define LOADER_CADATA       "cadata"

#define SWPK_LEN            (16)
#define SWPK_OFFSET         (0x1800)
#define SWPK_ENC_FLAG       (0x48)

HI_U8 g_M2MEncryptedSWPK[SWPK_LEN] = {0x0};
HI_BOOL g_bDA2BurnedAlready = HI_FALSE;

#ifdef HI_ADVCA_SUPPORT

HI_S32 CA_SSD_DecryptImage(HI_U8 *pu8Buffer, HI_U32 u32Len, CA_SSD_KEY_TYPE enKeyType)
{
#ifndef HI_ADVCA_TYPE_VERIMATRIX
#ifndef HI_ADVCA_TYPE_NAGRA
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CA_KEY_GROUP_E enKeyGroup;

    if ( (NULL == pu8Buffer) || (0 == u32Len) || (0xFFFFFFFF == u32Len) || (CA_SSD_KEY_BUTT == enKeyType) )
    {
        HI_ERR_CA_SSD("Invalid parameter input.\n");
        return HI_ERR_CA_SSD_INVALID_PARAM;
    }

    if ( CA_SSD_KEY_GROUP2 == enKeyType )
    {
        enKeyGroup = HI_CA_KEY_GROUP_2;
    }
    else
    {
        enKeyGroup = HI_CA_KEY_GROUP_1;
    }

    
    s32Ret = CA_DecryptImageUsingR2RKeyladder(enKeyGroup, pu8Buffer, u32Len);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("Decrypt image failed.\n");
        return HI_ERR_CA_SSD_DEC_FAILED;
    }
#else
    HI_INFO_CA_SSD("No need to decrypt image for nagra.\n");
#endif
#else
    HI_INFO_CA_SSD("No need to decrypt image for verimatrix.\n");
#endif

    return HI_SUCCESS;
}

HI_S32 CA_SSD_EncryptImage(HI_U8 *pu8Buffer, HI_U32 u32Len, CA_SSD_KEY_TYPE enKeyType)
{
#ifndef HI_ADVCA_TYPE_VERIMATRIX
#ifndef HI_ADVCA_TYPE_NAGRA
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CA_KEY_GROUP_E enKeyGroup;

    if ( (NULL == pu8Buffer) || (0 == u32Len) || (0xFFFFFFFF == u32Len) || (CA_SSD_KEY_BUTT == enKeyType) )
    {
        HI_ERR_CA_SSD("Invalid parameter input.\n");
        return HI_ERR_CA_SSD_INVALID_PARAM;
    }

    if ( CA_SSD_KEY_GROUP2 == enKeyType )
    {
        enKeyGroup = HI_CA_KEY_GROUP_2;
    }
    else
    {
        enKeyGroup = HI_CA_KEY_GROUP_1;
    }

    s32Ret = CA_EncryptImageUsingR2RKeyladder(enKeyGroup, pu8Buffer, u32Len);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("Encrypt image failed.\n");
        return HI_ERR_CA_SSD_ENC_FAILED;
    }
#else
    HI_INFO_CA_SSD("No need to encrypt image for nagra.\n");
#endif
#else

    HI_INFO_CA_SSD("No need to encrypt image for verimatrix.\n");
#endif
    return HI_SUCCESS;
}

HI_S32 CA_SSD_AuthenticateEx(HI_U8 *ppu8Buffer, HI_U32 *pu32Len)
{
#ifndef HI_ADVCA_TYPE_VERIMATRIX
    HI_S32 s32Ret = HI_SUCCESS;
#ifndef HI_ADVCA_TYPE_NAGRA
    HI_U32 u32CodeOffset = 0;
#endif

    if ( (NULL == ppu8Buffer) || (NULL == pu32Len) )
    {
        HI_ERR_CA_SSD("Invalid parameter input.\n");
        return HI_ERR_CA_SSD_INVALID_PARAM;
    }

#ifndef HI_ADVCA_TYPE_NAGRA
    s32Ret = CA_AuthenticateEx(ppu8Buffer, &u32CodeOffset);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("ssd authenticate failed.\n");
        return HI_ERR_CA_SSD_AUTH_FAILED;
    }
#endif
#else
	HI_INFO_CA_SSD("Not needed\n");
#endif
    return HI_SUCCESS;
}

#endif  /*HI_ADVCA_SUPPORT*/

