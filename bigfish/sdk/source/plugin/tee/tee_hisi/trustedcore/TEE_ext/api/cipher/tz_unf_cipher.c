/******************************************************************************
 *
 * Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : tz_unf_cipher.c
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   : 
 * Function List :
 * History       :
 * ******************************************************************************/

#include "tz_unf_cipher.h"
#include "hi_drv_cipher.h"
#include "sre_syscalls_ext.h"
#include "drv_cipher_ioctl.h"
#include "hi_type.h"

static HI_S32 s_CipherDevFd = -1;

#define CHECK_CIPHER_INIT()\
do{\
    if (s_CipherDevFd < 0)\
    {\
        return HI_ERR_CIPHER_NOT_INIT;\
    }\
}while(0)


#define TZ_ERR_CIPHER(fmt...)	uart_printf_func(fmt)
#define TZ_INFO_CIPHER(fmt...)	uart_printf_func(fmt)

HI_S32 TZ_UNF_CIPHER_Init(HI_VOID)
{
	HI_S32 ret = HI_SUCCESS;

	if (s_CipherDevFd > 0)
	{
	    s_CipherDevFd++;
		return HI_SUCCESS;
	}

	ret = __Cipher_Init();
	if ( HI_SUCCESS != ret )
	{
	    TZ_ERR_CIPHER("CIPHER init failed.\n");
		return HI_FAILURE;
	}

	s_CipherDevFd = 1;

	return HI_SUCCESS;
}

HI_S32 TZ_UNF_CIPHER_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr)
{
	CHECK_CIPHER_INIT();

	return __Cipher_CreateHandle(phCipher, pstCipherAttr);
}

HI_S32 TZ_UNF_CIPHER_DestroyHandle(HI_HANDLE hCipher)
{
	CHECK_CIPHER_INIT();
	return __Cipher_DestroyHandle(hCipher);
}

HI_S32 TZ_UNF_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
	CHECK_CIPHER_INIT();
	return __Cipher_ConfigHandle(hCipher, pstCtrl);
}

HI_S32 TZ_UNF_CIPHER_GetHandleConfig(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
	CHECK_CIPHER_INIT();

	return __Cipher_GetHandleConfig(hCipher, pstCtrl);
}

HI_S32 TZ_UNF_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Offset = 0;
    HI_U32 u32TempLen = 0;

	CHECK_CIPHER_INIT();
    
    while(u32ByteLength > 0)
    {
        if(u32ByteLength > SECURE_MEM_CIPHER_MAX_SIZE)
        {
            u32TempLen = SECURE_MEM_CIPHER_MAX_SIZE;
        }
        else
        {
            u32TempLen = u32ByteLength;
        }
        ret = __Cipher_Encrypt(hCipher, u32SrcPhyAddr+u32Offset, u32DestPhyAddr+u32Offset, u32TempLen);
        if(ret != HI_SUCCESS)
        {
            TZ_ERR_CIPHER("Cipher_Decrypt failure, ret=0x%x\n", ret);
            return HI_FAILURE;
        }

        u32ByteLength -= u32TempLen;
        u32Offset += u32TempLen;
    }
    
	return HI_SUCCESS;
}

HI_S32 TZ_UNF_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32Offset = 0;
    HI_U32 u32TempLen = 0;

	CHECK_CIPHER_INIT();
    
    while(u32ByteLength > 0)
    {
        if(u32ByteLength > SECURE_MEM_CIPHER_MAX_SIZE)
        {
            u32TempLen = SECURE_MEM_CIPHER_MAX_SIZE;
        }
        else
        {
            u32TempLen = u32ByteLength;
        }
        ret = __Cipher_Decrypt(hCipher, u32SrcPhyAddr+u32Offset, u32DestPhyAddr+u32Offset, u32TempLen);
        if(ret != HI_SUCCESS)
        {
            TZ_ERR_CIPHER("Cipher_Decrypt failure, ret=0x%x\n", ret);
            return HI_FAILURE;
        }

        u32ByteLength -= u32TempLen;
        u32Offset += u32TempLen;
    }
    
	return ret;
}

HI_S32 TZ_UNF_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
	CHECK_CIPHER_INIT();
	return __Cipher_EncryptMulti(hCipher, pstDataPkg, u32DataPkgNum);
}

HI_S32 TZ_UNF_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
	CHECK_CIPHER_INIT();
	return __Cipher_DecryptMulti(hCipher, pstDataPkg, u32DataPkgNum);
}

HI_S32 TZ_UNF_CIPHER_GetRandomNumber(HI_U32 *pu32Rnd)
{
	return __Cipher_GetRandomNumber(pu32Rnd);
}

HI_S32 TZ_UNF_CIPHER_EncryptHdcpKey(OTP_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer)
{
	CHECK_CIPHER_INIT();
	return __Cipher_EncryptHDCPKey(pstHdcpKeyTransfer);
}

HI_S32 TZ_UNF_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey)
{
	CHECK_CIPHER_INIT();
	return __Cipher_LoadHDCPKey(pstFlashHdcpKey);
}

HI_S32 TZ_UNF_CIPHER_GetIVOut(HI_HANDLE hCipher, HI_U8 *pu8IVOut)
{
	CHECK_CIPHER_INIT();
	return __Cipher_GetIVOut(hCipher, pu8IVOut);
}

HI_VOID TZ_UNF_CIPHER_DeInit(HI_VOID)
{
    if(s_CipherDevFd > 0)
    {
        s_CipherDevFd--;
    }
	if(s_CipherDevFd != 0)
	{
		return;
	}
	__Cipher_DeInit();
	s_CipherDevFd = -1;

	return;
}

HI_S32 TZ_UNF_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    return __Cipher_HashInit(pstHashAttr,pHashHandle);
}

HI_S32 TZ_UNF_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    return __Cipher_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);
}

HI_S32 TZ_UNF_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    return __Cipher_HashFinal(hHashHandle, pu8OutputHash);
}

HI_S32 TZ_UNF_CIPHER_Test(HI_U32 u32Cmd, HI_U32 *pu32Result, HI_U32 u32Param1, HI_U32 u32Param2)
{
     return __Cipher_Test(u32Cmd, pu32Result, u32Param1, u32Param2);
}


