/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_cipher.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2014-09-16
Last Modified :
Description   :  
Function List :
History       :
******************************************************************************/
#include "drv_cipher_intf.h"

HI_S32 HI_UNF_CIPHER_Init()
{
	return Cipher_Init();
}

HI_S32 HI_UNF_CIPHER_DeInit()
{
	(HI_VOID)Cipher_Exit();

	return HI_SUCCESS;
}

HI_S32 HI_UNF_CIPHER_CreateHandle(HI_HANDLE * phCipher, const HI_UNF_CIPHER_ATTS_S * pstCipherAttr)
{
	return Cipher_CreateHandle(phCipher, pstCipherAttr);
}

HI_S32 HI_UNF_CIPHER_DestroyHandle(HI_HANDLE hCipher)
{
	return Cipher_DestroyHandle(hCipher);
}

HI_S32 HI_UNF_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S * pstCtrl)
{
	return Cipher_ConfigHandle(hCipher, pstCtrl);
}

HI_S32 HI_UNF_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
	return Cipher_Encrypt(hCipher, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
}

HI_S32 HI_UNF_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
	return Cipher_Decrypt(hCipher, u32SrcPhyAddr, u32DestPhyAddr, u32ByteLength);
}

HI_S32 HI_UNF_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S * pstHashAttr, HI_HANDLE * pHashHandle)
{
	return Cipher_HashInit(pstHashAttr, pHashHandle);
}

HI_S32 HI_UNF_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 * pu8InputData, HI_U32 u32InputDataLen)
{
	return Cipher_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);
}

HI_S32 HI_UNF_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 * pu8OutputHash)
{
	return Cipher_HashFinal(hHashHandle, pu8OutputHash);
}

/* for test, encrypt data buffer by a given cipher handle, in a loop inside */
HI_S32 HI_CIPHER_EncryptEx(HI_HANDLE hCipherHandle, HI_U8 *input, HI_U32 datalen, HI_U8 *output)
{
    HI_U32 u32EncryptDataLen = 0;
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32LeftDataLen;
    HI_U32 i;
    HI_U32 u32BlockNum;

    u32LeftDataLen = datalen;
    u32BlockNum = (datalen + MAX_DATA_LEN - 1) / MAX_DATA_LEN;
    for(i = 0; i < u32BlockNum; i++)
    {
        u32EncryptDataLen = u32LeftDataLen >= MAX_DATA_LEN ? MAX_DATA_LEN : u32LeftDataLen;
        u32LeftDataLen -= u32EncryptDataLen;

        Ret = HI_UNF_CIPHER_Encrypt(hCipherHandle, (HI_U32)(input + i * MAX_DATA_LEN), (HI_U32)(output + i * MAX_DATA_LEN), u32EncryptDataLen);
        if(Ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Cipher encrypt failed!\n");
            return Ret;
        }
    }

    return Ret;
}

HI_S32 HI_CIPHER_SHA(HI_UNF_CIPHER_HASH_TYPE_E enType,
						const unsigned char *input,
						int iBufLen,
						unsigned char *output,
						int oBufLen)
{
    HI_S32 Ret = HI_SUCCESS;
    
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_HANDLE HashHandle = 0;

	if(NULL == input || output == NULL)
	{
		HI_ERR_CIPHER("Invalid params, null pointer!\n");
		return HI_FAILURE;
	}
	
    if(HI_UNF_CIPHER_HASH_TYPE_SHA1 != enType
    && HI_UNF_CIPHER_HASH_TYPE_SHA256 != enType)
    {
		HI_ERR_CIPHER("Not supported hash type(%d)!\n", enType);
		return HI_FAILURE;
    }

    if(HI_UNF_CIPHER_HASH_TYPE_SHA1 == enType)
    {
		if(oBufLen < 20)
		{
			HI_ERR_CIPHER("Hash output buffer(%d) too small!\n", oBufLen);
			return HI_FAILURE;
		}
    }

    if(HI_UNF_CIPHER_HASH_TYPE_SHA256 == enType)
    {
		if(oBufLen < 32)
		{
			HI_ERR_CIPHER("Hash output buffer(%d) too small!\n", oBufLen);
			return HI_FAILURE;
		}
    }

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = enType;
    stHashAttr.u32TotalDataLen = iBufLen;
    Ret = HI_UNF_CIPHER_HashInit(&stHashAttr, &HashHandle);
    if(Ret != HI_SUCCESS)
    {
    	HI_ERR_CIPHER("HI_UNF_CIPHER_HashInit failed!\n");
        HashHandle = -1;
        return Ret;
    }

    Ret = HI_UNF_CIPHER_HashUpdate(HashHandle, input, iBufLen);
    if(Ret != HI_SUCCESS)
    {
    	HI_ERR_CIPHER("HI_UNF_CIPHER_HashUpdate failed!\n");
        HashHandle = -1;
        return Ret;
    }
    Ret = HI_UNF_CIPHER_HashFinal(HashHandle, output);
    if(Ret != HI_SUCCESS)
    {
    	HI_ERR_CIPHER("HI_UNF_CIPHER_HashFinal failed!\n");
        HashHandle = -1;
        return Ret;
    }
    
    return HI_SUCCESS;
}

