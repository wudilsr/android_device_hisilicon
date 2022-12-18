/*******************************************************************  
* (c) Copyright 2011-2012 Discretix Technologies Ltd.              *
* This software is protected by copyright, international           *
* treaties and patents.                                            *
* Use of this Software as part of or with the Discretix CryptoCell *
* or Packet Engine products is governed by the products'           *
* commercial end user license agreement ("EULA").                  *
* It is possible that copies of this Software might be distributed *
* under some type of GNU General Public License ("GPL").           *
* Notwithstanding any such distribution under the terms of GPL,    *
* GPL does not govern the use of this Software as part of or with  *
* the Discretix CryptoCell or Packet Engine products, for which a  *
* EULA is required.                                                *
* If the product's EULA allows any copy or reproduction of this    *
* Software, then such copy or reproduction must include this       *
* Copyright Notice as well as any other notices provided           *
* thereunder.                                                      *
********************************************************************/

/************* Include Files ****************/
#include "hi_type.h"
#include "drv_cipher.h"
#include "drv_cipher_intf.h"
#include "drv_cipher_define.h"
#include "sre_debug.h"
#include "hi_mmz.h"
#include "crys_aes.h"
#include <boot.h>
#include "dx_pal_types.h"
#include "crys_rsa_error.h"
#include "crys_rsa_types.h"
#include "dx_error.h"
#include "crys_rsa_local.h"
#include "crys_rsa_schemes.h"
#include "crys_cipher_common.h"
#include "crys_hash.h"

/************************ Defines ******************************/



/************************ Typedefs ******************************/


/************************ Global Data ******************************/

#define RSA_SIGN        1
#define ASN1_HASH_SHA1    "\x30\x21\x30\x09\x06\x05\x2b\x0e\x03\x02\x1a\x05\x00\x04\x14"
#define ASN1_HASH_SHA256  "\x30\x31\x30\x0d\x06\x09\x60\x86\x48\x01\x65\x03\x04\x02\x01\x05\x00\x04\x20"

/************* Private function prototype ****************/


/************************ Public Functions ******************************/

#ifndef _INTERNAL_CRYS_NO_RSA_SIGN_SUPPORT
static HI_S32 RSA_GetAttr(CRYS_RSA_HASH_OpMode_t hashFunc,
                          HI_U16 u16NLen,
                          HI_U32 *pu32HLen,
                          HI_U32 *pu32KeyLen,
                          CRYS_HASH_OperationMode_t *pstenHashType,
                          HI_U8 *pbIsAfterHash)
{
    HI_S32 ret = HI_SUCCESS;

    
    if ((pu32HLen == HI_NULL) || (pu32KeyLen == HI_NULL) || (pstenHashType == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }
    
    *pu32HLen = 0;
    *pu32KeyLen = 0;
    *pstenHashType = HI_UNF_CIPHER_HASH_TYPE_BUTT;

    if (u16NLen <= 512)
    {
        *pu32KeyLen = u16NLen;
    }
    else 
    {
        HI_ERR_CIPHER("u16NLen(0x%x) is invalid\n", u16NLen);
        return HI_ERR_CIPHER_INVALID_POINT;
    }
    
    switch(hashFunc)
    {
    case CRYS_RSA_HASH_MD5_mode:
        *pu32HLen = 16;
        *pbIsAfterHash = HI_FALSE;
        *pstenHashType = CRYS_HASH_MD5_mode;
        break;
    case CRYS_RSA_After_MD5_mode:
        *pu32HLen = 16;
        *pbIsAfterHash = HI_TRUE;
        *pstenHashType = CRYS_HASH_MD5_mode;
        break;
    case CRYS_RSA_HASH_SHA1_mode:
        *pu32HLen = 20;
        *pbIsAfterHash = HI_FALSE;
        *pstenHashType = CRYS_HASH_SHA1_mode;
        break;
    case CRYS_RSA_After_SHA1_mode:
        *pu32HLen = 20;
        *pbIsAfterHash = HI_TRUE;
        *pstenHashType = CRYS_HASH_SHA1_mode;
        break;
    case CRYS_RSA_HASH_SHA224_mode:
        *pu32HLen = 28;
        *pbIsAfterHash = HI_FALSE;
        *pstenHashType = CRYS_HASH_SHA224_mode;
        break;
    case CRYS_RSA_After_SHA224_mode:
        *pu32HLen = 28;
        *pbIsAfterHash = HI_TRUE;
        *pstenHashType = CRYS_HASH_SHA224_mode;
        break;
    case CRYS_RSA_HASH_SHA256_mode:
        *pu32HLen = 32;
        *pbIsAfterHash = HI_FALSE;
        *pstenHashType = CRYS_HASH_SHA256_mode;
        break;
    case CRYS_RSA_After_SHA256_mode:
        *pu32HLen = 32;
        *pbIsAfterHash = HI_TRUE;
        *pstenHashType = CRYS_HASH_SHA256_mode;
        break;
    case CRYS_RSA_HASH_SHA384_mode:
        *pu32HLen = 48;
        *pbIsAfterHash = HI_FALSE;
        *pstenHashType = CRYS_HASH_SHA384_mode;
        break;
    case CRYS_RSA_After_SHA384_mode:
        *pu32HLen = 48;
        *pbIsAfterHash = HI_TRUE;
        *pstenHashType = CRYS_HASH_SHA384_mode;
        break;
    case CRYS_RSA_HASH_SHA512_mode:
        *pu32HLen = 64;
        *pbIsAfterHash = HI_FALSE;
        *pstenHashType = CRYS_HASH_SHA512_mode;
        break;
    case CRYS_RSA_After_SHA512_mode:
        *pu32HLen = 64;
        *pbIsAfterHash = HI_TRUE;
        *pstenHashType = CRYS_HASH_SHA512_mode;
        break;
    case CRYS_RSA_HASH_NO_HASH_mode:
        *pu32HLen = 0;
        *pbIsAfterHash = HI_TRUE;
        *pstenHashType = CRYS_HASH_NumOfModes;
        break;
    default:
        HI_ERR_CIPHER("hashFunc (0x%x) is invalid.\n", hashFunc);
        ret = HI_ERR_CIPHER_INVALID_PARA;
    }

    return ret;
}

/*!
 * Converts Symmetric Adaptor return code to CRYS error code.
 * 
 * \param symRetCode Symmetric Adaptor return error.
 * \param errorInfo Ignored.
 *  
 * \return CRYSError_t one of CRYS_* error codes defined in crys_error.h
 */
static CRYSError_t SymAdaptor2CrysRsaErr(int symRetCode, DxUint32_t errorInfo)
{
    CRYSError_t err;
    
	switch (symRetCode) {
	case HI_ERR_CIPHER_NOT_INIT:
		err = CRYS_RSA_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_FAILED_INIT:
        err = CRYS_RSA_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_INVALID_POINT:
		err =  CRYS_RSA_DATA_POINTER_INVALID_ERROR;
        break;
	case HI_ERR_CIPHER_INVALID_PARA:
        err = CRYS_RSA_DATA_POINTER_INVALID_ERROR;
        break;
	case HI_ERR_CIPHER_BUSY:
	case HI_ERR_CIPHER_NO_AVAILABLE_RNG:
        err = CRYS_RSA_IS_NOT_SUPPORTED;
        break;
    case HI_SUCCESS:
        err = CRYS_OK;
        break;
	default:
		err = CRYS_FATAL_ERROR;
        break;
	}

    return err | errorInfo;
}

static HI_S32 RSA_PKCS1_MGF1(CRYS_HASH_OperationMode_t hashFunc, HI_U32 u32MdLen,
                             HI_U8  *pu8Seed,  
                             HI_U32 u32Seedlen, 
                             HI_U8 *pu8Mask, HI_U32 u32MaskLen)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 i,j, u32Outlen = 0;
    HI_U8 u8Cnt[4];
    CRYS_HASH_Result_t u8Md;
    HI_U8* pMd;
    CRYS_HASHUserContext_t UserContext;
    CRYSError_t err;
    if ((pu8Seed == HI_NULL) || (pu8Mask == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    /*PKCS#1 V2.1 only use sha1 function, Others allow for future expansion*/
//    HI_PRINT_HEX ("MGF-IN", pu8Mask, u32MaskLen);

    for (i = 0; u32Outlen < u32MaskLen; i++) 
    {
        u8Cnt[0] = (HI_U8)((i >> 24) & 0xFF);
        u8Cnt[1] = (HI_U8)((i >> 16) & 0xFF);
        u8Cnt[2] = (HI_U8)((i >> 8)) & 0xFF;
        u8Cnt[3] = (HI_U8)(i & 0xFF);
        
        err = CRYS_HASH_Init(&UserContext, hashFunc);
        if( err != CRYS_OK)
        {
            HI_ERR_CIPHER("CRYS_HASH_Init failed, err = 0x%x.\n", err);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        err = CRYS_HASH_Update(&UserContext, pu8Seed, u32Seedlen);
        if (Ret != CRYS_OK)
        {
    		return HI_FAILURE;
        }
        err = CRYS_HASH_Update(&UserContext, u8Cnt, 4);
        if (Ret != CRYS_OK)
        {
    		return HI_FAILURE;
        }
        Ret = CRYS_HASH_Finish(&UserContext, u8Md);
        if (Ret != CRYS_OK)
        {
    		return HI_FAILURE;
        }
        pMd = (HI_U8*)u8Md;    
        for(j=0; (j<u32MdLen) && (u32Outlen < u32MaskLen); j++)
		{
			pu8Mask[u32Outlen++] ^= pMd[j];	
		}
    }

//    HI_PRINT_HEX ("MGF-OUT", pu8Mask, u32MaskLen);

    return HI_SUCCESS;
}

/******************************************************************
								  +-----------+
								  |     M     |
								  +-----------+
										|
										V
									   Hash
										|
										V
					     +--------+----------+----------+
			       M' =  |Padding1|  mHash   |   salt   |
					     +--------+----------+----------+
										|
		    +--------+----------+       V
	 DB =   |Padding2|maskedseed|      Hash
			+--------+----------+       |
					|					|
					V					|	  +--+
					xor <----- MGF <----|	  |bc|
					|					|	  +--+
					|					|      |
					V					V      V
			+-------------------+----- -------+--+
	EM =    |    maskedDB       |  maskedseed |bc|
			+-------------------+-------------+--+
 ******************************************************************/
static HI_S32 RSA_padding_add_PKCS1_PSS(CRYS_HASH_OperationMode_t hashFunc,
                                        HI_U32 u32HLen,
                                        HI_U32 u32SLen,
                                        HI_U32 u32EmBit, 
							            HI_U8 *pu8Input,
							            HI_U32 u32InLen,
							            HI_U8 *pu8Output,
                                        HI_U32 *pu32OutLen)
{
	HI_U32 ret = 0;
	HI_U8 *pu8M;
	HI_U8 u8Salt[64];
	HI_U8 *pu8MaskedDB;
	HI_U8 *pu8Maskedseed;
	HI_U32 u32Index;
	HI_U32 u32KeyLen;
	HI_U32 u32MSBits;
    CRYS_HASH_Result_t HashRes;
    CRYSError_t err;

	if ((pu8Input == NULL) || (pu8Output == NULL))
	{
		HI_ERR_CIPHER("zero point\n");
		return HI_ERR_CIPHER_INVALID_POINT;
	}

    u32KeyLen = (u32EmBit + 7)/8;
	u32MSBits = (u32EmBit - 1) & 0x07;

    *pu32OutLen = u32KeyLen;
    
	if (u32KeyLen < (u32HLen + u32SLen + 2))
	{
		HI_ERR_CIPHER("message too long: u32KeyLen: 0x%x, u32HLen: 0x%x, u32SLen: 0x%x\n", u32KeyLen, u32HLen, u32SLen);
		return HI_ERR_CIPHER_INVALID_PARA;
	}

	if (u32MSBits == 0)
	{
		*pu8Output++ = 0;
		u32KeyLen--;
	}

	pu8MaskedDB = pu8Output;
	pu8Maskedseed = pu8Output + u32KeyLen - u32HLen -1;
    
	/* Generate a random octet string salt of length sLen */
	ret = CRYS_GetRandomNumber(u8Salt, u32SLen);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("GET_GetRandomNumber failed\n");
        return ret;
    }

    pu8M = (HI_U8*)malloc(u32SLen + u32HLen + 8);
	if (pu8M == HI_NULL)
	{
		HI_ERR_CIPHER("malloc failed\n");
		return HI_FAILURE;
	}
    
	/*M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt*/
	u32Index = 0;
	memset(pu8M, 0x00, 8);
	u32Index+=8;
	memcpy(&pu8M[u32Index], pu8Input, u32InLen);
	u32Index+=u32InLen;
    memcpy(&pu8M[u32Index], u8Salt, u32SLen);
	u32Index+=u32SLen;
    err = CRYS_HASH (hashFunc, pu8M, u32Index, HashRes);    
    if (err != CRYS_OK)
    {
        HI_ERR_CIPHER("CRYS_HASH failed, err = 0x%x\n", err);
        free(pu8M);
        return HI_FAILURE;
    }
    free(pu8M);
    memcpy(pu8Maskedseed, HashRes, u32HLen);
	/*maskedDB = DB xor dbMask, DB = PS || 0x01 || salt*/
	u32Index = 0;
	memset(&pu8MaskedDB[u32Index], 0x00, u32KeyLen - u32SLen -u32HLen - 2);
	u32Index+=u32KeyLen - u32SLen -u32HLen - 2;
	pu8MaskedDB[u32Index++] = 0x01;
	memcpy(&pu8MaskedDB[u32Index], u8Salt, u32SLen);
	RSA_PKCS1_MGF1(hashFunc, u32HLen, pu8Maskedseed, u32HLen, pu8MaskedDB, u32KeyLen - u32HLen -1);

	pu8Output[u32KeyLen - 1] = 0xBC;

	if (u32MSBits)
	{
		pu8Output[0] &= 0xFF >> (8 - u32MSBits);
	}

	return HI_SUCCESS;
}

/*PKCS #1: EME-OAEP encoding*/
/*************************************************************
                    +----------+---------+--+-------+
               DB = |  lHash   |    PS   |01|   M   |
                    +----------+---------+--+-------+
                                   |
         +----------+              V
         |   seed   |--> MGF ---> xor
         +----------+              |
               |                   |
      +--+     V                   |
      |00|    xor <----- MGF <-----|
      +--+     |                   |
        |      |                   |
        V      V                   V
      +--+----------+----------------------------+
EM =  |00|maskedSeed|          maskedDB          |
      +--+----------+----------------------------+
       1     hlen              k - hlen- 1          

so: PS_LEN = k - hlen - 1 -  (hlen  + mlen + 1) = k - 2hlen - mlen - 2 > 0
so: mlen < k - 2hlen - 2 
*************************************************************/
static HI_S32 RSA_padding_add_PKCS1_OAEP(CRYS_HASH_OperationMode_t hashFunc,
                                  HI_U32 u32HLen,
                                  HI_U8  *L,
                                  HI_U32  Llen,
                                  HI_U32 u32KeyLen,
                                  HI_U8 *pu8Input,
                                  HI_U32 u32InLen,
                                  HI_U8 *pu8Output,
                                  HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32DBLen;
    HI_U8 *pu8DB;
    HI_U8 *pu8Seed;
    CRYS_HASH_Result_t u8LHASH;
    CRYSError_t err;

    if ((pu8Input == HI_NULL) || (pu8Output == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }
    err = CRYS_HASH (hashFunc, L, Llen, u8LHASH);    
    if (err != CRYS_OK)
    {
        HI_ERR_CIPHER("CRYS_HASH failed, err = 0x%x\n", err);
        return HI_FAILURE;
    }

    if (u32InLen > u32KeyLen - 2 * u32HLen - 2)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    *pu32OutLen = 0;
    pu8Output[0] = 0;
    pu8Seed = pu8Output + 1;
    pu8DB = pu8Output + u32HLen + 1;
    u32DBLen = u32KeyLen - u32HLen -1;
        
    memcpy(pu8DB, u8LHASH, u32HLen);                                 /*set lHash*/
    memset(&pu8DB[u32HLen], 0, u32DBLen - u32InLen - u32HLen -1);     /*set PS with 0x00*/
    pu8DB[u32DBLen - u32InLen - 1] = 0x01;                            /*set 0x01 after PS*/
    memcpy(&pu8DB[u32DBLen - u32InLen], pu8Input, u32InLen);          /*set M*/
    ret = CRYS_GetRandomNumber(pu8Seed, u32HLen);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_GET_GetRandomNumber failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    ret = RSA_PKCS1_MGF1(hashFunc, u32HLen, pu8Seed, u32HLen, pu8DB, u32KeyLen - u32HLen - 1);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    ret = RSA_PKCS1_MGF1(hashFunc, u32HLen, pu8DB, u32KeyLen - u32HLen - 1, pu8Seed, u32HLen);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    *pu32OutLen = u32KeyLen;

     return HI_SUCCESS;
}

static HI_U32 RSA_padding_check_PKCS1_PSS(CRYS_HASH_OperationMode_t hashFunc,
                                          HI_U32 u32SLen,
                                          HI_U32 u32HLen,
                                          HI_U32 u32EmBit, 
							              HI_U8 *pu8Input,
							              HI_U32 u32InLen,
							              HI_U8 *pu8MHash)
{
	HI_U32 ret = 0;
	HI_U8 *pu8M;
	HI_U8 u8Salt[64];
    CRYS_HASH_Result_t u8H;
	HI_U8 *pu8MaskedDB;
	HI_U8 *pu8Maskedseed;
	HI_U32 u32Index;
	HI_U32 u32KeyLen;
	HI_U32 u32MSBits;
    CRYSError_t err;
    
	if ((pu8Input == NULL) || (pu8MHash == NULL))
	{
		HI_ERR_CIPHER("zero point\n");
		return HI_ERR_CIPHER_INVALID_POINT;
	}

    u32KeyLen = (u32EmBit + 7)/8;
	u32MSBits = (u32EmBit - 1) & 0x07;

    if (u32InLen != u32KeyLen)
	{
		HI_ERR_CIPHER("inconsistent, u32InLen != 0xBC\n");
		return HI_ERR_CIPHER_INVALID_PARA;
	}

	if (pu8Input[0] & (0xFF << u32MSBits))
	{
		HI_ERR_CIPHER("inconsistent, EM[0] invalid\n");
		return HI_FAILURE;
	}
	
	if (u32MSBits == 0)
	{
		pu8Input++;
		u32KeyLen--;
	}
	
	pu8MaskedDB = pu8Input;
	pu8Maskedseed = pu8Input + u32KeyLen - u32HLen -1;
    
	if (pu8Input[u32KeyLen - 1] != 0xBC)
	{
		HI_ERR_CIPHER("inconsistent, EM[u32KeyLen - 1] != 0xBC\n");
		return HI_ERR_CIPHER_INVALID_PARA;
	}

	/*maskedDB = DB xor dbMask, DB = PS || 0x01 || salt*/
	ret = RSA_PKCS1_MGF1(hashFunc, u32HLen, pu8Maskedseed, u32HLen, pu8MaskedDB, u32KeyLen - u32HLen -1);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return ret;
    }
    if (u32MSBits)
	{
		pu8MaskedDB[0] &= 0xFF >> (8 - u32MSBits);
	}
	for (u32Index=0; u32Index<u32KeyLen - u32SLen -u32HLen - 2; u32Index++)
	{
		if (pu8MaskedDB[u32Index] != 0x00)
		{
			HI_ERR_CIPHER("inconsistent, PS != 0x00 in DB\n");
			return HI_FAILURE;
		}
	}
	if (pu8MaskedDB[u32Index++] != 0x01)
	{
		HI_ERR_CIPHER("inconsistent, can't find 0x01 in DB\n");
		return HI_FAILURE;
	}
	memcpy(u8Salt, &pu8MaskedDB[u32Index], u32SLen);

	pu8M = (HI_U8*)malloc(u32SLen + u32HLen + 8);
	if (pu8M == NULL)
	{
		HI_ERR_CIPHER("malloc failed\n");
		return HI_FAILURE;
	}

	/*M' = (0x)00 00 00 00 00 00 00 00 || mHash || salt*/
	u32Index = 0;
	memset(pu8M, 0x00, 8);
	u32Index+=8;
	memcpy(&pu8M[u32Index], pu8MHash, u32HLen);
	u32Index+=u32HLen;
    memcpy(&pu8M[u32Index], u8Salt, u32SLen);
	u32Index+=u32SLen;
    err = CRYS_HASH (hashFunc, pu8M, u32Index, u8H);    
    if (err != CRYS_OK)
    {
        HI_ERR_CIPHER("CRYS_HASH failed, err = 0x%x\n", err);
        free(pu8M);
        return HI_FAILURE;
    }
    free(pu8M);
   
	ret = memcmp(u8H, pu8Maskedseed, u32HLen);
	if (ret != 0)
	{
		HI_ERR_CIPHER("consistent, hash compare failed\n");
        ret = HI_FAILURE;
	}

	return ret;
}

static HI_S32 RSA_padding_check_PKCS1_OAEP(CRYS_HASH_OperationMode_t hashFunc,
                                  HI_U32 u32HLen,
                                  HI_U8  *L,
                                  HI_U32  Llen,
                                  HI_U32 u32KeyLen,
                                  HI_U8 *pu8Input, 
                                  HI_U32 u32InLen,
                                  HI_U8 *pu8Output,
                                  HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i;
    HI_U8 *pu8Seed;
    HI_U8 *pu8DB;
    HI_U8 *pu8MaskedDB;
    CRYS_HASH_Result_t u8LHASH;
    CRYSError_t err;

    if ((pu8Input == HI_NULL) || (pu8Output == HI_NULL))
    {
        HI_ERR_CIPHER("para is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    err = CRYS_HASH (hashFunc, L, Llen, u8LHASH);    
    if (err != CRYS_OK)
    {
        HI_ERR_CIPHER("CRYS_HASH failed, err = 0x%x\n", err);
        return HI_FAILURE;
    }
    
    if (u32InLen != u32KeyLen)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (u32KeyLen < 2 * u32HLen + 2)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(pu8Input[0] != 0x00)
    {
        HI_ERR_CIPHER("EM[0] != 0.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    *pu32OutLen = 0;
    pu8MaskedDB= pu8Input + u32HLen + 1;
    pu8Seed = pu8Input + 1;
    pu8DB = pu8Input + u32HLen + 1;
    ret = RSA_PKCS1_MGF1(hashFunc, u32HLen, pu8MaskedDB, u32KeyLen - u32HLen - 1, pu8Seed, u32HLen);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    ret = RSA_PKCS1_MGF1(hashFunc, u32HLen, pu8Seed, u32HLen, pu8DB, u32KeyLen - u32HLen - 1);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA_PKCS1_MGF1 failed, ret = %x\n", ret);
        return HI_FAILURE;
    }
    if(memcmp(pu8DB, u8LHASH, u32HLen) != 0)
    {
        HI_ERR_CIPHER("LHASH error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    for(i=u32HLen; i < u32KeyLen - u32HLen - 1; i++)
    {
        if((pu8DB[i] == 0x01)) 
        {
            memcpy(pu8Output, pu8DB+i+1, u32KeyLen - u32HLen - i - 2); 
            *pu32OutLen = u32KeyLen - u32HLen - i - 2;
            break;
        } 
    }
    if (i >= u32KeyLen - u32HLen - 1)
    {
        HI_ERR_CIPHER("PS error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    return HI_SUCCESS;
}

/*PKCS #1: block type 0,1,2 message padding*/
/*************************************************
EB = 00 || BT || PS || 00 || D

PS_LEN >= 8, mlen < u32KeyLen - 11
*************************************************/
static HI_S32 RSA_padding_add_PKCS1_type(HI_U32 u32KeyLen,
                               CRYS_PKCS1_Block_Type  u8BT,
                               HI_U8 *pu8Input,
                               HI_U32 u32InLen,
                               HI_U8 *pu8Output,
                               HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32PLen;
    HI_U8 *pu8EB;

    if (u32InLen > u32KeyLen - 11)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    *pu32OutLen =0;
    pu8EB = pu8Output;
    
    *(pu8EB++) = 0;
    *(pu8EB++) = u8BT;                 /* Private Key BT (Block Type) */

    /* pad out with 0xff data */
    u32PLen = u32KeyLen - 3 - u32InLen;
    switch(u8BT)
    {
    case CRYS_RSA_PKCS1_15_MODE00:
        memset(pu8EB, 0x00, u32PLen);
        break;
    case CRYS_RSA_PKCS1_15_MODE01:
        memset(pu8EB, 0xFF, u32PLen);
        break;
    case CRYS_RSA_PKCS1_15_MODE02:
        ret = CRYS_GetRandomNumber(pu8EB, u32PLen);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("RSA_GET_GetRandomNumber failed, ret = %x\n", ret);
            return HI_FAILURE;
        }
        break;
    default:
        HI_ERR_CIPHER("BT(0x%x) is invalid.\n", u8BT);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    pu8EB += u32PLen;
    *(pu8EB++) = 0x00;
    memcpy(pu8EB, pu8Input, u32InLen);

    *pu32OutLen = u32KeyLen;
    
    return HI_SUCCESS;
}

static HI_S32 RSA_padding_check_PKCS1_type(HI_U32 u32KeyLen,
                               CRYS_PKCS1_Block_Type  u8BT,
                               HI_U8 *pu8Input, 
                               HI_U32 u32InLen,
                               HI_U8 *pu8Output,
                               HI_U32 *pu32OutLen)
{
    HI_U8 *pu8EB;

    if (u32InLen != u32KeyLen)
    {
        HI_ERR_CIPHER("u32InLen is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    *pu32OutLen = 0x00;
    pu8EB = pu8Input;
    if(*pu8EB != 0x00)
    {
        HI_ERR_CIPHER("EB[0] != 0x00.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }
    pu8EB++;
    if(*pu8EB != u8BT)
    {
        HI_ERR_CIPHER("EB[1] != BT(0x%x).\n", u8BT);
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }
    pu8EB++;
    switch(u8BT)
    {
    case CRYS_RSA_PKCS1_15_MODE00:
        for( ; pu8EB < pu8Input + u32InLen - 1; pu8EB++)
        {
            if( (*pu8EB == 0x00) && (*(pu8EB+1) != 0)) 
            {
                break;
            } 
        }
        break;
    case CRYS_RSA_PKCS1_15_MODE01:
        for( ; pu8EB < pu8Input + u32InLen - 1; pu8EB++)
        {
            if(*pu8EB == 0xFF)
            {
                continue;
            }
            else if (*pu8EB == 0x00)
            {
                break;
            }
            else
            {
                pu8EB = pu8Input + u32InLen - 1;
                break;
            }
        }
        break;
    case CRYS_RSA_PKCS1_15_MODE02:
        for( ; pu8EB < pu8Input + u32InLen - 1; pu8EB++)
        {
            if(*pu8EB == 0x00)
            {
                break; 
            }   
        }
        break;
    default:
        HI_ERR_CIPHER("BT(0x%x) is invalid.\n", u8BT);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(pu8EB >= (pu8Input + u32InLen - 1))
    {
        HI_ERR_CIPHER("PS Error.\n");
        return HI_ERR_CIPHER_FAILED_DECRYPT;
    }

    pu8EB++;
    *pu32OutLen = pu8Input + u32KeyLen - pu8EB;
    memcpy(pu8Output, pu8EB, *pu32OutLen); 
    
    return HI_SUCCESS;
}

/**********************************************************************************************************/
/**
   @brief
   RSA_Sign implements the Signing algorithm as defined
   in PKCS#1 v1.5 or v2.1, using a single function

   The actual macros that will be used by the user are:
   CRYS_RSA_PKCS1v15_Sign		- for v1.5
   CRYS_RSA_PKCS1v15_SHA1_Sign	- for v1.5 data is hashed with SHA1
   CRYS_RSA_PKCS1v15_MD5_Sign	- for v1.5 data is hashed with MD5
   CRYS_RSA_PSS_Sign			- for v2.1
   CRYS_RSA_PSS_SHA1_Sign		- for v2.1 data is hashed with SHA1
					- for v2.1 MD5 is not supported, since 
					according to the PKCS#1 ver2.1 it is not recommended
   
   @param[in] UserContext_ptr - A pointer to a Context. For the use of the 
   								function as a space to work on.
   @param[in] UserPrivKey_ptr - A pointer to the private key data
                            structure of the user. \note The representation
                            (pair or quintuple) and hence the
                            algorithm (CRT or not) is determined
                            by the Private Key data
                            structure - using CRYS_Build_PrivKey
                            or CRYS_Build_PrivKeyCRT determines
                            which algorithm will be used.
   @param[in] hashFunc - The hash function to be used. Currently
                         only CRYS_PKCS1_SHA1 and CRYS_PKCS1_MD5
                         are supported. 
   @param[in] MGF - The mask generation function. Only for PKCS#1 v2.1
                    defines MGF1, so the only value allowed for v2.1 
                    is CRYS_PKCS1_MGF1. 
   @param[in] SaltLen - The Length of the Salt buffer. relevant for PKCS#1 Ver 2.1 Only
   						Typical lengths are 0 and hLen (20 for SHA1)
   						The maximum length allowed is NSize - hLen - 2                                                                                       
   @param[in] DataIn_ptr - A pointer to the data to sign.
   @param[in] DataInSize - The size, in bytes, of the data to sign.
   @param[out] Output_ptr - A pointer to the signature. 
                            The buffer must be at least PrivKey_ptr->N.len bytes long 
                            (that is, the size of the modulus in bytes).
   @param[in,out] OutputSize_ptr - A pointer to the Signature Size value - the input value
                            is the signature buffer size allocated, the output value is 
                            the signature size actually used.
                            The buffer must be at least PrivKey_ptr->N.len bytes long 
                            (that is, the size of the modulus in bytes).
   @param[in] PKCS1_ver - Ver 1.5 or 2.1, according to the functionality required
      
   @return CRYSError_t - CRYS_OK,
                         CRYS_RSA_INVALID_USER_CONTEXT_POINTER_ERROR,
                         CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR,
                         CRYS_RSA_PRIV_KEY_VALIDATION_TAG_ERROR,
                         CRYS_RSA_HASH_ILLEGAL_OPERATION_MODE_ERROR,
                         CRYS_RSA_MGF_ILLEGAL_ARG_ERROR,
                         CRYS_RSA_PKCS1_VER_ARG_ERROR,
                         CRYS_RSA_INVALID_MESSAGE_DATA_SIZE,
                         CRYS_RSA_INVALID_OUTPUT_POINTER_ERROR,
                         CRYS_RSA_INVALID_SIGNATURE_BUFFER_SIZE
*/


CEXPORT_C CRYSError_t _DX_RSA_Sign(CRYS_RSAPrivUserContext_t *UserContext_ptr,
                         CRYS_RSAUserPrivKey_t *UserPrivKey_ptr,
                         CRYS_RSA_HASH_OpMode_t hashFunc,
                         CRYS_PKCS1_MGF_t MGF,
                         DxUint16_t SaltLen,				  				  			      
                         DxUint8_t     *DataIn_ptr,
                         DxUint32_t     DataInSize,
                         DxUint8_t     *Output_ptr,
                         DxUint16_t    *OutputSize_ptr,
                         CRYS_PKCS1_version PKCS1_ver)

{
    HI_U32 u32KeyLen;
    HI_U32 u32HLen;
    CRYS_HASH_Result_t  u8Hash;
    HI_S32 ret = HI_SUCCESS;
    CRYS_HASH_OperationMode_t enHashType;
    HI_U8 *pHash;
    HI_U8 bIsAfterHash;
    CRYSRSAPrivKey_t *PrivKey_ptr ;
    DxUint16_t ModulusSizeBytes;
    HI_U32 u32OutLen = 0;
    HI_U32 u32EmBit;
    HI_U8 *pu8EM;
    HI_U8 *pu8UserContext;
    CRYSError_t err;

   /* if the users context ID pointer is DX_NULL return an error */
   if( UserContext_ptr == DX_NULL )
      return CRYS_RSA_INVALID_USER_CONTEXT_POINTER_ERROR;
      
   /*if the private key object is DX_NULL return an error*/   
   if (UserPrivKey_ptr == DX_NULL)
   	  return CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR;
   	  
   /* check if the hash operation mode is legal */
   if( hashFunc >= CRYS_RSA_HASH_NumOfModes)
      return CRYS_RSA_HASH_ILLEGAL_OPERATION_MODE_ERROR;
      
   /* check if the MGF operation mode is legal */   
   if(MGF >= CRYS_RSA_NumOfMGFFunctions)
   	  return CRYS_RSA_MGF_ILLEGAL_ARG_ERROR;
   	  
   /* check that the PKCS1 version argument is legal*/
   if(PKCS1_ver >= CRYS_RSA_NumOf_PKCS1_versions)
   	  return CRYS_RSA_PKCS1_VER_ARG_ERROR;
   	  
   /*According to the PKCS1 ver 2.1 standart it is not recommended to use MD5 hash
   	therefore we do not support it */
   if(PKCS1_ver == CRYS_PKCS1_VER21 && hashFunc == CRYS_RSA_HASH_MD5_mode)
   		return CRYS_RSA_HASH_ILLEGAL_OPERATION_MODE_ERROR;

   if(UserPrivKey_ptr->valid_tag != CRYS_RSA_PRIV_KEY_VALIDATION_TAG)
   	  return CRYS_RSA_PRIV_KEY_VALIDATION_TAG_ERROR;

   if(PKCS1_ver < CRYS_RSA_NumOf_PKCS1_versions)
   {
        /*Initializing the Modulus Size in Bytes needed for SaltLength parameter check*/
        PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr->PrivateKeyDbBuff;

        /*Note: the (-1) is due to the PKCS#1 Ver2.1 standard section 9.1.1*/
        ModulusSizeBytes =  (DxUint16_t)((PrivKey_ptr->nSizeInBits -1) / 8);
        if((PrivKey_ptr->nSizeInBits -1) % 8)
   		        ModulusSizeBytes++;
   }
   else
   {
        return CRYS_RSA_PKCS1_VER_ARG_ERROR;
   }

   if (PrivKey_ptr->OperationMode >= CRYS_RSADecryptionNumOfOptions)
   {
        HI_ERR_CIPHER("PrivKey OperationMode unsuport\n");
        return CRYS_RSA_INVALID_CRT_PARAMETR_SIZE_ERROR;
   }

   pu8EM  = (HI_U8*)UserContext_ptr;
   pu8UserContext = (HI_U8*)UserContext_ptr + RSA_MAX_RSA_KEY_LEN;

    ret = RSA_GetAttr(hashFunc, ModulusSizeBytes, 
        &u32HLen, &u32KeyLen, &enHashType, &bIsAfterHash);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return SymAdaptor2CrysRsaErr(ret, 0);
    }

    if(!bIsAfterHash)
    {
        err = CRYS_HASH (enHashType, DataIn_ptr, DataInSize, u8Hash);    
        if (err != CRYS_OK)
        {
            HI_ERR_CIPHER("CRYS_HASH failed, err = 0x%x\n", err);
            return HI_FAILURE;
        }
        pHash = (HI_U8*)u8Hash;
    }
    else
    {
        pHash = DataIn_ptr;
    }


    if ((MGF == CRYS_PKCS1_MGF1) && (PKCS1_ver == CRYS_PKCS1_VER21))
    {
        u32EmBit = PrivKey_ptr->nSizeInBits;
        ret = RSA_padding_add_PKCS1_PSS(enHashType, u32HLen, SaltLen, u32EmBit, 
            pHash, u32HLen, pu8EM, &u32OutLen);
    }
    else if ((MGF == CRYS_PKCS1_NO_MGF) && (PKCS1_ver == CRYS_PKCS1_VER15))
    {
        ret = RSA_padding_add_PKCS1_type(u32KeyLen, CRYS_RSA_PKCS1_15_MODE01, pHash, u32HLen, pu8EM, &u32OutLen);
    }
    else
    {
        return CRYS_RSA_PKCS1_VER_ARG_ERROR;
    }

    if(u32OutLen != u32KeyLen)
    {
        HI_ERR_CIPHER("Error, u32InSigntLen != u32KeyLen.\n");
        return CRYS_RSA_BASE_MGF_MASK_TOO_LONG;
    }

    *OutputSize_ptr = u32KeyLen;

    return  CRYS_RSA_Private(pu8UserContext, PrivKey_ptr, pu8EM, Output_ptr, u32KeyLen);




}/* END OF _DX_RSA_Sign */

/**********************************************************************************************************/
/**
   \brief RSA_Verify implements the RSASSA-PKCS1v15 algorithm
    in a single function, as defined in PKCS#1 v1.5 and v2.1

	The actual macro that will be used by the users is:
	CRYS_RSA_PKCS1v15_Verify			- for v1.5
	CRYS_RSA_PKCS1v15_MD5_Verify		- for v1.5 data in is hashed with MD5
	CRYS_RSA_PKCS1v15_SHA1_Verify		- for v1.5 data in is hashed with SHA1
	CRYS_RSA_PSS_Verify					- for v2.1
	CRYS_RSA_PSS_SHA1_Verify			- for v2.1 data in is hashed with SHA1
							- for v2.1 MD5 is not supported, since
							according to the PKCS#1 ver2.1 it is not recommended	
	
   @param[in] UserContext_ptr - A pointer to the public Context, 
   				for the use of the function as a space to work on
   @param[in] UserPubKey_ptr - A pointer to the public key data
                           structure of the user.
   @param[in] hashFunc - The hash function to be used. 
                         Currently only CRYS_PKCS1_SHA1 and CRYS_PKCS1_MD5
                         are supported. The other hash functions
                         recommended by PKCS#1 v2.1 are
                         SHA-256/284/512.  If PKCS1_ver is CRYS_PKCS1_VER15, then
			 the value CRYS_RSA_After_HASH_NOT_KNOWN_mode will allow
			 the signature data to determine the hash function to be used.
   @param[in] MGF - The mask generation function. only for PKCS#1 v2.1
                    defines MGF1, so the only value allowed for v2.1 
                    is CRYS_PKCS1_MGF1. 
   @param[in] SaltLen - The Length of the Salt buffer. relevant for PKCS#1 Ver 2.1 Only
   						Typical lengths are 0 and hLen (20 for SHA1)
   						The maximum length allowed is NSize - hLen - 2                                             
   @param[in] DataIn_ptr - A pointer to the data whose signature is
                         to be verified.
   @param[in] DataInSize - The size, in bytes, of the data whose
                         signature is to be verified.
   @param[in] Sig_ptr - A pointer to the signature to be verified. 
                        The length of the signature is PubKey_ptr->N.len bytes 
                        (that is, the size of the modulus, in bytes).
   @param[in] PKCS1_ver - Ver 1.5 or 2.1, according to the functionality required

   @return CRYSError_t - CRYS_OK, CRYS_INVALID_SIGNATURE,
                         CRYS_BAD_PARAM, CRYS_OUT_OF_RANGE 
*/
				     
CEXPORT_C CRYSError_t _DX_RSA_Verify(CRYS_RSAPubUserContext_t *UserContext_ptr,
                           CRYS_RSAUserPubKey_t *UserPubKey_ptr,
                           CRYS_RSA_HASH_OpMode_t hashFunc,
                           CRYS_PKCS1_MGF_t MGF,
                           DxUint16_t SaltLen,
                           DxUint8_t     *DataIn_ptr,
                           DxUint32_t     DataInSize,
                           DxUint8_t     *Sig_ptr,
                           CRYS_PKCS1_version PKCS1_ver)
{
    HI_U32 u32KeyLen;
    HI_U32 u32HLen;
    CRYS_HASH_Result_t  u8Hash;
    HI_U8  u8HashVerify[64];
    HI_U32 u32HLenVerify;
    HI_S32 ret = HI_SUCCESS;
    CRYS_HASH_OperationMode_t enHashType;
    HI_U8 *pHash;
    HI_U8 bIsAfterHash;
    CRYSRSAPubKey_t *PubKey_ptr;
    DxUint16_t ModulusSizeBytes;
    HI_U32 u32EmBit;
    HI_U8 *pu8UserContext;
    HI_U8 *pu8EM;
    CRYSError_t err;

   /* if the users context ID pointer is DX_NULL return an error */
   if( UserContext_ptr == DX_NULL )
      return CRYS_RSA_INVALID_USER_CONTEXT_POINTER_ERROR;
      
   /*if the private key object is DX_NULL return an error*/   
   if (UserPubKey_ptr == DX_NULL)
   	  return CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR;
   	  
   /* check if the hash operation mode is legal */
   if( hashFunc >= CRYS_RSA_HASH_NumOfModes)
      return CRYS_RSA_HASH_ILLEGAL_OPERATION_MODE_ERROR;
      
   /* check if the MGF operation mode is legal */   
   if(MGF >= CRYS_RSA_NumOfMGFFunctions)
   	  return CRYS_RSA_MGF_ILLEGAL_ARG_ERROR;
   	  
   /* check that the PKCS1 version argument is legal*/
   if(PKCS1_ver >= CRYS_RSA_NumOf_PKCS1_versions)
   	  return CRYS_RSA_PKCS1_VER_ARG_ERROR;
   	  
   /*According to the PKCS1 ver 2.1 standart it is not recommended to use MD5 hash
   	therefore we do not support it */
   if(PKCS1_ver == CRYS_PKCS1_VER21 && hashFunc == CRYS_RSA_HASH_MD5_mode)
   		return CRYS_RSA_HASH_ILLEGAL_OPERATION_MODE_ERROR;

   if(UserPubKey_ptr->valid_tag != CRYS_RSA_PUB_KEY_VALIDATION_TAG)
   	  return CRYS_RSA_PRIV_KEY_VALIDATION_TAG_ERROR;

   if(PKCS1_ver < CRYS_RSA_NumOf_PKCS1_versions)
   {
       /*Initializing the Modulus Size in Bytes needed for SaltLength parameter check*/
        PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr->PublicKeyDbBuff;

        /*Note: the (-1) is due to the PKCS#1 Ver2.1 standard section 9.1.1*/
        ModulusSizeBytes =  (DxUint16_t)((PubKey_ptr->nSizeInBits -1) / 8);
        if((PubKey_ptr->nSizeInBits -1) % 8)
   		        ModulusSizeBytes++;
   }
   else
   {
        return CRYS_RSA_PKCS1_VER_ARG_ERROR;
   }

   pu8EM = (HI_U8*)UserContext_ptr;
   pu8UserContext = pu8EM + RSA_MAX_RSA_KEY_LEN;
   
    ret = RSA_GetAttr(hashFunc, ModulusSizeBytes, 
        &u32HLen, &u32KeyLen, &enHashType, &bIsAfterHash);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return SymAdaptor2CrysRsaErr(ret, 0);
    }

    err = CRYS_RSA_Public(pu8UserContext, PubKey_ptr, Sig_ptr, pu8EM, u32KeyLen);
    
//    HI_PRINT_HEX ("N", stRsaData.pu8N, stRsaData.u16NLen);
//    HI_PRINT_HEX ("K", stRsaData.pu8K, stRsaData.u16KLen);
//    HI_PRINT_HEX ("M", stRsaData.pu8Input, stRsaData.u32DataLen);

    if (ret != CRYS_OK)
    {
        HI_ERR_CIPHER("DRV_CIPHER_CalcRsa_SW error\n");
        return err;
    }

    if(!bIsAfterHash)
    {
        err = CRYS_HASH (enHashType, DataIn_ptr, DataInSize, u8Hash);    
        if (err != CRYS_OK)
        {
            HI_ERR_CIPHER("CRYS_HASH failed, err = 0x%x\n", err);
            return HI_FAILURE;
        }
        pHash = (HI_U8*)u8Hash;
    }
    else
    {
        pHash = DataIn_ptr;
    }

    if ((MGF == CRYS_PKCS1_MGF1) && (PKCS1_ver == CRYS_PKCS1_VER21))
    {
        u32EmBit = PubKey_ptr->nSizeInBits;
        ret = RSA_padding_check_PKCS1_PSS(enHashType, SaltLen, u32HLen, u32EmBit, 
            pu8EM, u32KeyLen, pHash);
    }
    else if ((MGF == CRYS_PKCS1_NO_MGF) && (PKCS1_ver == CRYS_PKCS1_VER15))
    {
        ret = RSA_padding_check_PKCS1_type(u32KeyLen, CRYS_RSA_PKCS1_15_MODE01, pu8EM, u32KeyLen, u8HashVerify, &u32HLenVerify);
        if ((u32HLenVerify != u32HLen) || (memcmp(pHash, u8HashVerify, u32HLen) != 0))
        {
            HI_ERR_CIPHER("consistent, hash compare failed\n");
            return CRYS_RSA_ERROR_VER15_INCONSISTENT_VERIFY;
        }
    }
    else
    {
        return CRYS_RSA_PKCS1_VER_ARG_ERROR;
    }

    return DX_CRYS_RETURN_ERROR(ret, 0, SymAdaptor2CrysRsaErr);                                 
    
}/* END OF _DX_RSA_Verify */

/**********************************************************************************************************/

/**
   @brief
   RSA_SCHEMES_Encrypt implements the RSAES-OAEP algorithm as defined
   in PKCS#1 v2.1 8.1 and in PKCS#1 v1.5 8.1

   This function combines the RSA encryption primitive and the
   EME-OAEP encoding method, to provide an RSA-based encryption
   method that is semantically secure against adaptive
   chosen-ciphertext attacks. For more details, please refere to
   the PKCS#1 standard.

	The actual macro that will be used by the user is:
	CRYS_RSA_OAEP_Encrypt 	  - for v2.1
	CRYS_RSA_PKCS1v15_Encrypt - for v1.5
	

   @param[in] UserPubKey_ptr - A pointer to the public key data structure of the User.
   @param[in] PrimeData_ptr - A pointer to a CRYS_RSAPrimeData_t 
   				that is used for the Encryption operation
   @param[in] hashFunc - The hash function to be used. 
                         The hash functions supported: SHA1, SHA-256/284/512, 
                         MD5 (MD5 - allowed only for PKCS#1 v1.5).
   @param[in] L - The label input pointer. Relevant for PKCS#1 Ver2.1 only, may be NULL also.
                  For PKCS#1 Ver1.5 it is an empty string (NULL). 
   @param[in] Llen - The label length. Relevant for PKCS#1 Ver2.1 only (see notes above).                 
   @param[in] MGF - the mask generation function. PKCS#1 v2.1
                    defines MGF1, so the currently allowed value is CRYS_PKCS1_MGF1.
   @param[in] Data_ptr - Pointer to the data to encrypt.
   @param[in] DataSize - The size, in bytes, of the data to encrypt. 
                         \Note: The data size must be:
                            1. for PKCS #1 v.2.1  DataSize <= PrivKey_ptr->N.len - 2*HashLen - 2.
							2. for PKCS #1 v.1.5  DataSize <= PrivKey_ptr->N.len - 11.
   @param[out] Output_ptr - Pointer to the encrypted data, the buffer must be at least 
                            of the modulus size, in bytes.

   @return CRYSError_t - CRYS_OK, CRYS_BAD_PARAM, CRYS_OUT_OF_RANGE
*/

CEXPORT_C CRYSError_t _DX_RSA_SCHEMES_Encrypt(CRYS_RSAUserPubKey_t *UserPubKey_ptr,
                                    CRYS_RSAPrimeData_t  *PrimeData_ptr,
                                    CRYS_RSA_HASH_OpMode_t hashFunc,
                                    DxUint8_t            *L,
                                    DxUint16_t           Llen,
                                    CRYS_PKCS1_MGF_t   MGF,
                                    DxUint8_t           *DataIn_ptr,
                                    DxUint16_t           DataInSize,
                                    DxUint8_t            *Output_ptr,
                                    CRYS_PKCS1_version PKCS1_ver)
				  
{
   /* FUNCTION DECLERATIONS */
   
    DxUint16_t ModulusSizeBytes; 
    CRYSRSAPubKey_t *PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr->PublicKeyDbBuff;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    CRYS_HASH_OperationMode_t enHashType;
    HI_U8 bIsAfterHash;
    HI_U32 u32OutLen = 0;
    HI_U8 *pu8UserContext;
    HI_U8 *pu8EM;

   /* FUNCTION LOGIC */   
   /* .................. initializing local variables ................... */
   /* ------------------------------------------------------------------- */   
     

   
   /* if the users context pointer is DX_NULL return an error */
   if( UserPubKey_ptr == DX_NULL )
      return CRYS_RSA_INVALID_PUB_KEY_STRUCT_POINTER_ERROR;
      
   /* checking the Prime Data pointer */
   if( PrimeData_ptr == DX_NULL )
      return CRYS_RSA_PRIM_DATA_STRUCT_POINTER_INVALID;

   /* check if the hash operation mode is legal */
   if( hashFunc >= CRYS_RSA_HASH_NumOfModes)
      return CRYS_RSA_HASH_ILLEGAL_OPERATION_MODE_ERROR;
      
   /* check if the MGF operation mode is legal */   
   if(MGF >= CRYS_RSA_NumOfMGFFunctions)
   	  return CRYS_RSA_MGF_ILLEGAL_ARG_ERROR;
   	  
      /* check that the PKCS1 version argument is legal*/
   if(PKCS1_ver >= CRYS_RSA_NumOf_PKCS1_versions)
   	  return CRYS_RSA_PKCS1_VER_ARG_ERROR;	        
   	  
   /* if the users Data In pointer is illegal return an error */
   /* note - it is allowed to encrypt a message of size zero ; only on this case a NULL is allowed */
   if( DataIn_ptr == DX_NULL && DataInSize != 0)
      return CRYS_RSA_DATA_POINTER_INVALID_ERROR;
           
   /*If the output pointer is DX_NULL return Error*/   
   if(Output_ptr == DX_NULL)
   	  return CRYS_RSA_INVALID_OUTPUT_POINTER_ERROR;
   	  
   if(UserPubKey_ptr->valid_tag != CRYS_RSA_PUB_KEY_VALIDATION_TAG)
	  return CRYS_RSA_PUB_KEY_VALIDATION_TAG_ERROR;   

   if(Llen == 0)
		L = DX_NULL;

   /* .................. initializing local variables ................... */
   /* ------------------------------------------------------------------- */

    pu8EM = (HI_U8*)PrimeData_ptr;
    pu8UserContext = pu8EM + RSA_MAX_RSA_KEY_LEN;
    
	/*Initialize K with the modulus size in Bytes*/   
	ModulusSizeBytes = (DxUint16_t)(PubKey_ptr->nSizeInBits / 8);
	if(PubKey_ptr->nSizeInBits % 8)
		ModulusSizeBytes++;

    ret = RSA_GetAttr(hashFunc, ModulusSizeBytes, 
        &u32HLen, &u32KeyLen, &enHashType, &bIsAfterHash);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return SymAdaptor2CrysRsaErr(ret, 0);
    }

    if ((MGF == CRYS_PKCS1_MGF1) && (PKCS1_ver == CRYS_PKCS1_VER21))
    {
        ret = RSA_padding_add_PKCS1_OAEP(enHashType, u32HLen, L, Llen, u32KeyLen, 
            DataIn_ptr, DataInSize, pu8EM, &u32OutLen);
    }
    else if ((MGF == CRYS_PKCS1_NO_MGF) && (PKCS1_ver == CRYS_PKCS1_VER15))
    {
        ret = RSA_padding_add_PKCS1_type(u32KeyLen, CRYS_RSA_PKCS1_15_MODE02, DataIn_ptr, 
            DataInSize, pu8EM, &u32OutLen);
    }
    else
    {
        return CRYS_RSA_PKCS1_VER_ARG_ERROR;
    }
    
    if(u32OutLen != u32KeyLen)
    {
        HI_ERR_CIPHER("Error, u32InSigntLen != u32KeyLen.\n");
        return CRYS_RSA_BASE_MGF_MASK_TOO_LONG;
    }
    

    return CRYS_RSA_Public(pu8UserContext, PubKey_ptr, pu8EM, Output_ptr, u32KeyLen);


//    HI_PRINT_HEX ("N", stRsaData.pu8N, stRsaData.u16NLen);
//    HI_PRINT_HEX ("K", stRsaData.pu8K, stRsaData.u16KLen);
//    HI_PRINT_HEX ("M", stRsaData.pu8Input, stRsaData.u32DataLen);


	  	
}/* END OF _DX_RSA_SCHEMES_Encrypt */				  

CEXPORT_C CRYSError_t _DX_RSA_SCHEMES_Decrypt(
	                                CRYS_RSAUserPrivKey_t  *UserPrivKey_ptr,
                                    CRYS_RSAPrimeData_t    *PrimeData_ptr,
                                    CRYS_RSA_HASH_OpMode_t  hashFunc,
                                    DxUint8_t              *L,
                                    DxUint16_t              Llen,
                                    CRYS_PKCS1_MGF_t        MGF,
                                    DxUint8_t              *DataIn_ptr,
                                    DxUint16_t              DataInSize,
                                    DxUint8_t              *Output_ptr,
                                    DxUint16_t             *OutputSize_ptr,
                                    CRYS_PKCS1_version      PKCS1_ver)
{
    DxUint16_t ModulusSizeBytes; 
    CRYSRSAPrivKey_t *PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr->PrivateKeyDbBuff;
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32HLen;
    HI_U32 u32KeyLen;
    CRYS_HASH_OperationMode_t enHashType;
    HI_U8 bIsAfterHash;
    HI_U32 u32OutLen = 0;
    HI_U8 *pu8UserContext;
    HI_U8 *pu8EM;
    CRYSError_t err;
    
   /* FUNCTION LOGIC */   
   /* .................. initializing local variables ................... */
   /* ------------------------------------------------------------------- */   
     
   /* if the users context pointer is DX_NULL return an error */
   if( PrivKey_ptr == DX_NULL )
      return CRYS_RSA_INVALID_PUB_KEY_STRUCT_POINTER_ERROR;
      
   /* checking the Prime Data pointer */
   if( PrimeData_ptr == DX_NULL )
      return CRYS_RSA_PRIM_DATA_STRUCT_POINTER_INVALID;

   /* check if the hash operation mode is legal */
   if( hashFunc >= CRYS_RSA_HASH_NumOfModes)
      return CRYS_RSA_HASH_ILLEGAL_OPERATION_MODE_ERROR;
      
   /* check if the MGF operation mode is legal */   
   if(MGF >= CRYS_RSA_NumOfMGFFunctions)
   	  return CRYS_RSA_MGF_ILLEGAL_ARG_ERROR;
   	  
      /* check that the PKCS1 version argument is legal*/
   if(PKCS1_ver >= CRYS_RSA_NumOf_PKCS1_versions)
   	  return CRYS_RSA_PKCS1_VER_ARG_ERROR;	        
   	  
   /* if the users Data In pointer is illegal return an error */
   /* note - it is allowed to encrypt a message of size zero ; only on this case a NULL is allowed */
   if( DataIn_ptr == DX_NULL && DataInSize != 0)
      return CRYS_RSA_DATA_POINTER_INVALID_ERROR;
           
   /*If the output pointer is DX_NULL return Error*/   
   if(Output_ptr == DX_NULL)
   	  return CRYS_RSA_INVALID_OUTPUT_POINTER_ERROR;
   	  
   if(UserPrivKey_ptr->valid_tag != CRYS_RSA_PRIV_KEY_VALIDATION_TAG)
   	  return CRYS_RSA_PRIV_KEY_VALIDATION_TAG_ERROR;

   if(Llen == 0)
		L = DX_NULL;

   /* .................. initializing local variables ................... */
   /* ------------------------------------------------------------------- */
    pu8EM = (HI_U8*)PrimeData_ptr;
    pu8UserContext = pu8EM + RSA_MAX_RSA_KEY_LEN;
    
	/*Initialize K with the modulus size in Bytes*/   
	ModulusSizeBytes = (DxUint16_t)(PrivKey_ptr->nSizeInBits / 8);
	if(PrivKey_ptr->nSizeInBits % 8)
		ModulusSizeBytes++;

    ret = RSA_GetAttr(hashFunc, ModulusSizeBytes, 
        &u32HLen, &u32KeyLen, &enHashType, &bIsAfterHash);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("RSA attr config error\n");
        return SymAdaptor2CrysRsaErr(ret, 0);
    }
    

    err = CRYS_RSA_Private(pu8UserContext, PrivKey_ptr, DataIn_ptr, pu8EM, u32KeyLen);
    if (err != CRYS_OK)
    {
        HI_ERR_CIPHER("RSA Private error, ret = 0x%x\n", err);
        return ret;
//    HI_PRINT_HEX ("M", stRsaData.pu8Input, stRsaData.u32DataLen);
    }

    if ((MGF == CRYS_PKCS1_MGF1) && (PKCS1_ver == CRYS_PKCS1_VER21))
    {
        ret = RSA_padding_check_PKCS1_OAEP(enHashType, u32HLen, L, Llen, u32KeyLen, pu8EM, u32KeyLen, Output_ptr, &u32OutLen);
    }
    else if ((MGF == CRYS_PKCS1_NO_MGF) && (PKCS1_ver == CRYS_PKCS1_VER15))
    {
        ret = RSA_padding_check_PKCS1_type(u32KeyLen, CRYS_RSA_PKCS1_15_MODE02, pu8EM, u32KeyLen, Output_ptr, &u32OutLen);
    }
    else
    {
        return CRYS_RSA_PKCS1_VER_ARG_ERROR;
    }

    *OutputSize_ptr = (HI_U16)u32OutLen;

    return DX_CRYS_RETURN_ERROR(ret, 0, SymAdaptor2CrysRsaErr);
}
#endif /*_INTERNAL_CRYS_NO_RSA_SIGN_SUPPORT*/

#ifdef HI_CIPHER_TEST
#define TEST_KEY_SIZE   256
static HI_U8 tN[]  = 
{
    0x82, 0x78, 0xA0, 0xC5, 0x39, 0xE6, 0xF6, 0xA1, 0x5E, 0xD1, 0xC6, 0x8B, 0x9C, 0xF9, 0xC4, 0x3F, 
    0xEA, 0x19, 0x16, 0xB0, 0x96, 0x3A, 0xB0, 0x5A, 0x94, 0xED, 0x6A, 0xD3, 0x83, 0xE8, 0xA0, 0xFD, 
    0x01, 0x5E, 0x92, 0x2A, 0x7D, 0x0D, 0xF9, 0x72, 0x1E, 0x03, 0x8A, 0x68, 0x8B, 0x4D, 0x57, 0x55, 
    0xF5, 0x2F, 0x9A, 0xC9, 0x45, 0xCF, 0x9B, 0xB7, 0xF5, 0x11, 0x94, 0x7A, 0x16, 0x0B, 0xED, 0xD9, 
    0xA3, 0xF0, 0x63, 0x8A, 0xEC, 0xD3, 0x21, 0xAB, 0xCF, 0x74, 0xFC, 0x6B, 0xCE, 0x06, 0x4A, 0x51, 
    0xC9, 0x7C, 0x7C, 0xA3, 0xC4, 0x10, 0x63, 0x7B, 0x00, 0xEC, 0x2D, 0x02, 0x18, 0xD5, 0xF1, 0x8E, 
    0x19, 0x7F, 0xBE, 0xE2, 0x45, 0x5E, 0xD7, 0xA8, 0x95, 0x90, 0x88, 0xB0, 0x73, 0x35, 0x89, 0x66, 
    0x1C, 0x23, 0xB9, 0x6E, 0x88, 0xE0, 0x7A, 0x57, 0xB0, 0x55, 0x8B, 0x81, 0x9B, 0x9C, 0x34, 0x9F, 
    0x86, 0x0E, 0x15, 0x94, 0x2C, 0x6B, 0x12, 0xC3, 0xB9, 0x56, 0x60, 0x25, 0x59, 0x3E, 0x50, 0x7B, 
    0x62, 0x4A, 0xD0, 0xF0, 0xB6, 0xB1, 0x94, 0x83, 0x51, 0x66, 0x6F, 0x60, 0x4D, 0xEF, 0x8F, 0x94, 
    0xA6, 0xD1, 0xA2, 0x80, 0x06, 0x24, 0xF2, 0x6E, 0xD2, 0xC7, 0x01, 0x34, 0x8D, 0x2B, 0x6B, 0x03, 
    0xF7, 0x05, 0xA3, 0x99, 0xCC, 0xC5, 0x16, 0x75, 0x1A, 0x81, 0xC1, 0x67, 0xA0, 0x88, 0xE6, 0xE9, 
    0x00, 0xFA, 0x62, 0xAF, 0x2D, 0xA9, 0xFA, 0xC3, 0x30, 0x34, 0x98, 0x05, 0x4C, 0x1A, 0x81, 0x0C, 
    0x52, 0xCE, 0xBA, 0xD6, 0xEB, 0x9C, 0x1E, 0x76, 0x01, 0x41, 0x6C, 0x34, 0xFB, 0xC0, 0x83, 0xC5, 
    0x4E, 0xB3, 0xF2, 0x5B, 0x4F, 0x94, 0x08, 0x33, 0x87, 0x5E, 0xF8, 0x39, 0xEF, 0x7F, 0x72, 0x94, 
    0xFF, 0xD7, 0x51, 0xE8, 0xA2, 0x5E, 0x26, 0x25, 0x5F, 0xE9, 0xCC, 0x2A, 0x7D, 0xAC, 0x5B, 0x35
};
static HI_U8 tE[]  = 
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01
};
static HI_U8 tD[]  = 
{
    0x49, 0x7E, 0x93, 0xE9, 0xA5, 0x7D, 0x42, 0x0E, 0x92, 0xB0, 0x0E, 0x6C, 0x94, 0xC7, 0x69, 0x52, 
    0x2B, 0x97, 0x68, 0x5D, 0x9E, 0xB2, 0x7E, 0xA6, 0xF7, 0xDF, 0x69, 0x5E, 0xAE, 0x9E, 0x7B, 0x19, 
    0x2A, 0x0D, 0x50, 0xBE, 0xD8, 0x64, 0xE7, 0xCF, 0xED, 0xB2, 0x46, 0xE4, 0x2F, 0x1C, 0x29, 0x07, 
    0x45, 0xAF, 0x44, 0x3C, 0xFE, 0xB3, 0x3C, 0xDF, 0x7A, 0x10, 0x26, 0x18, 0x43, 0x95, 0x02, 0xAD, 
    0xA7, 0x98, 0x81, 0x2A, 0x3F, 0xCF, 0x8A, 0xD7, 0x12, 0x6C, 0xAE, 0xC8, 0x37, 0x6C, 0xF9, 0xAE, 
    0x6A, 0x96, 0x52, 0x4B, 0x99, 0xE5, 0x35, 0x74, 0x93, 0x87, 0x76, 0xAF, 0x08, 0xB8, 0x73, 0x72, 
    0x7D, 0x50, 0xA5, 0x81, 0x26, 0x5C, 0x8F, 0x94, 0xEA, 0x73, 0x59, 0x5C, 0x33, 0xF9, 0xC3, 0x65, 
    0x1E, 0x92, 0xCD, 0x20, 0xC3, 0xBF, 0xD7, 0x8A, 0xCF, 0xCC, 0xD0, 0x61, 0xF8, 0xFB, 0x1B, 0xF4, 
    0xB6, 0x0F, 0xD4, 0xCF, 0x3E, 0x55, 0x48, 0x4C, 0x99, 0x2D, 0x40, 0x44, 0x7C, 0xBA, 0x7B, 0x6F, 
    0xDB, 0x5D, 0x71, 0x91, 0x2D, 0x93, 0x80, 0x19, 0xE3, 0x26, 0x5D, 0x59, 0xBE, 0x46, 0x6D, 0x90, 
    0x4B, 0xDF, 0x72, 0xCE, 0x6C, 0x69, 0x72, 0x8F, 0x5B, 0xA4, 0x74, 0x50, 0x2A, 0x42, 0x95, 0xB2, 
    0x19, 0x04, 0x88, 0xD7, 0xDA, 0xBB, 0x17, 0x23, 0x69, 0xF4, 0x52, 0xEB, 0xC8, 0x55, 0xBE, 0xBC, 
    0x2E, 0xA9, 0xD0, 0x57, 0x7D, 0xC6, 0xC8, 0x8B, 0x86, 0x7B, 0x73, 0xCD, 0xE4, 0x32, 0x79, 0xC0, 
    0x75, 0x53, 0x53, 0xE7, 0x59, 0x38, 0x0A, 0x8C, 0xEC, 0x06, 0xA9, 0xFC, 0xA5, 0x15, 0x81, 0x61, 
    0x3E, 0x44, 0xCD, 0x05, 0xF8, 0x54, 0x04, 0x00, 0x79, 0xB2, 0x0D, 0x69, 0x2A, 0x47, 0x60, 0x1A, 
    0x2B, 0x79, 0x3D, 0x4B, 0x50, 0x8A, 0x31, 0x72, 0x48, 0xBB, 0x75, 0x78, 0xD6, 0x35, 0x90, 0xE1,
};

static HI_U8 P[]  = 
{
    0xC4, 0x29, 0x15, 0xFD, 0xE6, 0xAD, 0x5D, 0x4D, 0xC5, 0xDE, 0x95, 0xB6, 0x4A, 0xA8, 0x25, 0x42, 
    0x15, 0x1D, 0x58, 0x0E, 0xA5, 0xEB, 0xDD, 0xE4, 0xDC, 0x70, 0xA4, 0x28, 0xA7, 0xC1, 0xC9, 0x1C, 
    0xBA, 0x2F, 0xA7, 0xAF, 0xE4, 0xCF, 0xC7, 0xBD, 0x87, 0x3F, 0x7C, 0xD6, 0xD7, 0x7B, 0x7D, 0x4F, 
    0xA1, 0xBB, 0x79, 0x06, 0x2D, 0xF1, 0xDE, 0x00, 0x1E, 0xA9, 0x87, 0x29, 0xFD, 0xE1, 0xA8, 0x43, 
    0xB6, 0x28, 0xC5, 0xF7, 0x2F, 0xFB, 0x64, 0x05, 0x7C, 0x6C, 0xD2, 0xFD, 0x54, 0xE4, 0x43, 0xE0, 
    0x80, 0xD2, 0xE3, 0xE3, 0xB4, 0xBC, 0x4E, 0xE5, 0x59, 0x93, 0x36, 0x5E, 0x9A, 0x79, 0x49, 0x7B, 
    0x40, 0x5F, 0xCE, 0xAE, 0x4A, 0x1B, 0x59, 0x63, 0x5F, 0xA1, 0x37, 0x6C, 0x18, 0x65, 0xA9, 0x2F, 
    0x71, 0x0C, 0x1A, 0xB4, 0xA1, 0x00, 0xD3, 0x20, 0x0D, 0x9A, 0xC1, 0x0B, 0x96, 0x88, 0x16, 0xC9, 
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
static HI_U8 Q[] = 
{
    0xAA, 0x45, 0x9E, 0x08, 0x44, 0x6B, 0x7B, 0x7D, 0x47, 0x09, 0x4C, 0xFA, 0x24, 0x4A, 0xAD, 0xD3, 
    0x4B, 0xF6, 0x46, 0x35, 0x63, 0xA0, 0xAD, 0xB6, 0x61, 0x0A, 0xE6, 0x1D, 0x8E, 0xAB, 0x74, 0xF1, 
    0x16, 0x5F, 0x83, 0xD8, 0x96, 0xB8, 0x69, 0xC5, 0x17, 0x70, 0x5B, 0x31, 0x18, 0xA4, 0xD7, 0x32, 
    0x83, 0xCD, 0x41, 0xAF, 0xC1, 0xAB, 0xD3, 0xA2, 0x15, 0xBF, 0x29, 0x05, 0x8F, 0xB9, 0xB7, 0xB8, 
    0xDB, 0xCC, 0x42, 0x3C, 0x4E, 0x8C, 0xC7, 0xF2, 0x27, 0x89, 0xA6, 0x0D, 0x6C, 0x4F, 0xD2, 0x11, 
    0x94, 0x64, 0xAA, 0xA0, 0x8C, 0x31, 0x7E, 0x5B, 0x0D, 0xF0, 0x6B, 0xAA, 0xE8, 0x43, 0x80, 0x2B, 
    0x73, 0x1B, 0x69, 0xD0, 0x0F, 0x0F, 0xD8, 0x5E, 0x35, 0xC5, 0xDF, 0x67, 0x86, 0x33, 0x0B, 0xDD, 
    0xE6, 0xCF, 0x6D, 0x2D, 0x60, 0x8B, 0x2B, 0x0F, 0x9F, 0xFA, 0x06, 0x7E, 0x4D, 0x7C, 0x1B, 0x0D, 
};      
static HI_U8 DP[] = 
{
    0x3E, 0xCD, 0x40, 0xA3, 0x37, 0x55, 0x4D, 0xC7, 0xF6, 0x8F, 0x9A, 0xB2, 0xF0, 0x18, 0x01, 0x45, 
    0xB4, 0xE8, 0xDE, 0x26, 0x62, 0x6C, 0xAF, 0x6F, 0xF4, 0x3B, 0x83, 0xF3, 0x18, 0x32, 0x6C, 0xA6, 
    0xEB, 0xDD, 0x11, 0xFC, 0xB8, 0x6E, 0xE5, 0x6E, 0x02, 0x7D, 0x0B, 0x04, 0xE5, 0x9C, 0x3D, 0xB4, 
    0x5E, 0xFD, 0x5C, 0x73, 0xE4, 0x05, 0xC9, 0xA3, 0x94, 0x2D, 0x86, 0x7E, 0xA5, 0x2F, 0xB7, 0xE5, 
    0x65, 0xCE, 0x8C, 0x02, 0xE5, 0xB3, 0xC0, 0x84, 0x19, 0x1F, 0xE6, 0x35, 0x01, 0x16, 0xCB, 0xBC, 
    0x76, 0xC2, 0x0D, 0xFF, 0xFA, 0xFF, 0x46, 0xEB, 0x1A, 0xD0, 0x8C, 0xD9, 0xA0, 0xEF, 0x2F, 0xDD, 
    0x6B, 0xF0, 0xC0, 0x85, 0x00, 0x68, 0xDD, 0x27, 0x79, 0x98, 0x6D, 0xDC, 0x07, 0xBB, 0x94, 0x7D, 
    0x01, 0xDE, 0x74, 0x36, 0x5C, 0x4D, 0x9D, 0x4A, 0x67, 0xD0, 0xA1, 0xF9, 0x89, 0xCA, 0x2C, 0x31,
};     
static HI_U8 DQ[] = 
{
    0x6F, 0xE5, 0x28, 0x21, 0x4E, 0xB5, 0x43, 0x85, 0xE4, 0x74, 0xDC, 0x3D, 0x56, 0x34, 0x2D, 0x5F, 
    0x3A, 0x00, 0x31, 0xCB, 0x4C, 0x19, 0x7F, 0x8E, 0xE6, 0xDE, 0xFE, 0xB2, 0x55, 0xDB, 0x9F, 0x12, 
    0x00, 0x1D, 0xEC, 0xCB, 0x1C, 0xE1, 0x3B, 0xC0, 0xE5, 0xD2, 0x54, 0x5B, 0x43, 0x52, 0xB0, 0x88, 
    0xE5, 0xCC, 0xB1, 0x6A, 0x0A, 0xE0, 0x1C, 0x47, 0xDB, 0xFA, 0xAF, 0xBE, 0x93, 0xE0, 0xFC, 0x37, 
    0x63, 0x5A, 0x2B, 0xFC, 0xED, 0xB1, 0xDE, 0x83, 0xE8, 0x2F, 0xB1, 0x0C, 0x09, 0x2D, 0xBB, 0x63, 
    0x0A, 0x1D, 0xCD, 0x73, 0x8C, 0x2D, 0xCA, 0x57, 0x94, 0x25, 0x76, 0xDB, 0xED, 0x9E, 0xCE, 0x4F, 
    0xBF, 0x69, 0x38, 0x74, 0x1E, 0x31, 0xCF, 0x82, 0xB9, 0xDB, 0xBB, 0x20, 0x91, 0x34, 0x62, 0x8C, 
    0x04, 0xEE, 0x33, 0x55, 0x2A, 0xA8, 0xCA, 0x37, 0x8E, 0x6E, 0x04, 0x6E, 0x64, 0x05, 0x36, 0xD1,
};     
static HI_U8 QP[] = 
{
    0xBA, 0xBE, 0x60, 0x75, 0x6A, 0x59, 0x4B, 0x63, 0xE6, 0x2D, 0xBF, 0x48, 0x28, 0xDD, 0xC2, 0x8F, 
    0x3F, 0x59, 0x74, 0xCC, 0xD0, 0xC4, 0x0B, 0xD4, 0x19, 0x2E, 0x88, 0x80, 0x58, 0x8E, 0x28, 0x11, 
    0x69, 0x55, 0xB3, 0xC5, 0x16, 0x12, 0x0F, 0xF5, 0xDB, 0x99, 0x2A, 0xCA, 0x02, 0x1B, 0xA7, 0xBA, 
    0xC0, 0x80, 0x97, 0x63, 0x3A, 0xD7, 0x9F, 0x8C, 0xF4, 0xC7, 0xA8, 0x26, 0xEC, 0x03, 0x36, 0x5C, 
    0xE2, 0x01, 0x07, 0xF4, 0xD6, 0x6E, 0xAF, 0x31, 0x3B, 0x0E, 0xD8, 0xA5, 0x84, 0x9D, 0x8F, 0x20, 
    0x29, 0xA9, 0x28, 0xFB, 0x8D, 0x5D, 0xD4, 0xBD, 0xF0, 0x08, 0x31, 0x88, 0x9E, 0x04, 0x43, 0x5F, 
    0x0F, 0x21, 0x50, 0xBD, 0x25, 0x01, 0xFA, 0xD9, 0x0A, 0xA0, 0xDE, 0xA6, 0x16, 0xDA, 0x11, 0xC3, 
    0x99, 0x05, 0xCA, 0x16, 0x59, 0x62, 0x1F, 0xB4, 0x78, 0xE7, 0x96, 0x1D, 0xCF, 0x2F, 0x23, 0xE8,
}; 
void rsa_test1(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint16_t    OutputSize;
    DxUint8_t     DataIn_ptr[TEST_KEY_SIZE] = {0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D};
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    CRYS_RSAPrivUserContext_t UserPriContext_ptr;
    CRYS_RSAPubUserContext_t UserPubContext_ptr;

    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
    PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, 256);
    PrivKey_ptr->nSizeInBits = 2048;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, tD, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.e, tE, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PSS_SHA1_Sign(&UserPriContext_ptr, &UserPrivKey_ptr, CRYS_PKCS1_MGF1,
        20, DataIn_ptr, Output_ptr, &OutputSize);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA1_Sign failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("SIGN", Output_ptr, OutputSize);

    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, TEST_KEY_SIZE);
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PubKey_ptr->e, tE, TEST_KEY_SIZE);
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PSS_SHA1_Verify(&UserPubContext_ptr,&UserPubKey_ptr, CRYS_PKCS1_MGF1,
        20, DataIn_ptr, Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA1_Verify failed, err= 0x%x\n", err);	
        return;
	}
	
    
}

void rsa_test2(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint16_t    OutputSize;
    DxUint8_t     DataIn_ptr[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    DxUint8_t        L[5] = {"\x01\x02\x03\x04\x05"};
    CRYS_RSAPrimeData_t    PrimeData_ptr;
    
#if 0
    CIPHER_RSA_KEY_S stRsaKey;

    stRsaKey.u32Exponent = 0x03;
    stRsaKey.u32NumBits = TEST_KEY_SIZE*8;
    stRsaKey.stPriKey.pu8N = tN;
    stRsaKey.stPriKey.pu8E = tE;
    stRsaKey.stPriKey.pu8D= tD;
    stRsaKey.stPriKey.pu8P= P;
    stRsaKey.stPriKey.pu8Q= Q;
    stRsaKey.stPriKey.pu8DP = DP;
    stRsaKey.stPriKey.pu8DQ = DQ;
    stRsaKey.stPriKey.pu8QP = QP;    
    DRV_CIPHER_GenRsaKey_SW(&stRsaKey);
    
    memset(stRsaKey.stPriKey.pu8E, 0, TEST_KEY_SIZE);
    stRsaKey.stPriKey.u16ELen = TEST_KEY_SIZE;
    stRsaKey.stPriKey.pu8E[TEST_KEY_SIZE-1] = 0x03;
    
    HI_PRINT_HEX ("N", stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
    HI_PRINT_HEX ("E", stRsaKey.stPriKey.pu8E, stRsaKey.stPriKey.u16ELen);
    HI_PRINT_HEX ("D", stRsaKey.stPriKey.pu8D, stRsaKey.stPriKey.u16DLen);
#endif

    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, TEST_KEY_SIZE);
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PubKey_ptr->e, tE, TEST_KEY_SIZE);
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_OAEP_Encrypt(&UserPubKey_ptr, &PrimeData_ptr, CRYS_RSA_HASH_SHA1_mode,
        L, sizeof(L), CRYS_PKCS1_MGF1, DataIn_ptr, sizeof(DataIn_ptr), Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Encrypt failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("OAEP-ENC", Output_ptr, TEST_KEY_SIZE);

    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
    PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, TEST_KEY_SIZE);
    PrivKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, tD, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.e, tE, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_OAEP_Decrypt(&UserPrivKey_ptr, &PrimeData_ptr, CRYS_RSA_HASH_SHA1_mode,
        L, sizeof(L), CRYS_PKCS1_MGF1, Output_ptr, TEST_KEY_SIZE, Output_ptr, &OutputSize);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Decrypt failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("OAEP-DEC", Output_ptr, OutputSize);
    if (memcmp(Output_ptr, DataIn_ptr, OutputSize) != 0)
    {
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Decrypt failed\n");	
        return;
	}
    
}

void rsa_test3(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint16_t    OutputSize;
    DxUint8_t     DataIn_ptr[TEST_KEY_SIZE] = {0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D};
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    CRYS_RSAPrivUserContext_t UserPriContext_ptr;
    CRYS_RSAPubUserContext_t UserPubContext_ptr;

    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
    PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, 256);
    PrivKey_ptr->nSizeInBits = 2048;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, tD, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.e, tE, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PKCS1v15_SHA1_Sign(&UserPriContext_ptr, &UserPrivKey_ptr, DataIn_ptr, Output_ptr, &OutputSize);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA1_Sign failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("SIGN", Output_ptr, OutputSize);

    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, TEST_KEY_SIZE);
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PubKey_ptr->e, tE, TEST_KEY_SIZE);
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PKCS1v15_SHA1_Verify(&UserPubContext_ptr,&UserPubKey_ptr, DataIn_ptr, Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA1_Verify failed, err= 0x%x\n", err);	
        return;
	}
	
    
}

void rsa_test4(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint16_t    OutputSize;
    DxUint8_t     DataIn_ptr[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    CRYS_RSAPrimeData_t    PrimeData_ptr;
    
    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
#if 1
    CIPHER_RSA_KEY_S stRsaKey;

    stRsaKey.u32Exponent = 0x03;
    stRsaKey.u32NumBits = TEST_KEY_SIZE*8;
    stRsaKey.stPriKey.pu8N = tN;
    stRsaKey.stPriKey.pu8E = tE;
    stRsaKey.stPriKey.pu8D= tD;
    stRsaKey.stPriKey.pu8P= P;
    stRsaKey.stPriKey.pu8Q= Q;
    stRsaKey.stPriKey.pu8DP = DP;
    stRsaKey.stPriKey.pu8DQ = DQ;
    stRsaKey.stPriKey.pu8QP = QP;    
    DRV_CIPHER_GenRsaKey_SW(&stRsaKey);
    
    PubKey_ptr->nSizeInBits = stRsaKey.stPriKey.u16NLen*8;
    PubKey_ptr->eSizeInBits = stRsaKey.stPriKey.u16ELen*8;
    PrivKey_ptr->nSizeInBits = stRsaKey.stPriKey.u16NLen*8;
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = stRsaKey.stPriKey.u16DLen*8;

    /*    
    HI_PRINT_HEX ("N", stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
    HI_PRINT_HEX ("E", stRsaKey.stPriKey.pu8E, stRsaKey.stPriKey.u16ELen);
    HI_PRINT_HEX ("D", stRsaKey.stPriKey.pu8D, stRsaKey.stPriKey.u16DLen);
    */
#else
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8; 
    PrivKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = TEST_KEY_SIZE*8;
#endif

    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, (PubKey_ptr->nSizeInBits+7)/8);
    CRYS_Bin2Bn(PubKey_ptr->e, tE, (PubKey_ptr->eSizeInBits+7)/8);

    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, (PrivKey_ptr->nSizeInBits+7)/8);
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, tD, (PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits+7)/8);

    err = CRYS_RSA_PKCS1v15_Encrypt(&UserPubKey_ptr, &PrimeData_ptr, DataIn_ptr, sizeof(DataIn_ptr), Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Encrypt failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("PKCS1v15-ENC", Output_ptr, TEST_KEY_SIZE);


    err = CRYS_RSA_PKCS1v15_Decrypt(&UserPrivKey_ptr, &PrimeData_ptr, Output_ptr, TEST_KEY_SIZE, Output_ptr, &OutputSize);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Decrypt failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("PKCS1v15-DEC", Output_ptr, OutputSize);
    if (memcmp(Output_ptr, DataIn_ptr, OutputSize) != 0)
    {
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Decrypt failed\n");	
        return;
	}
    
}

void rsa_test5(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint16_t    OutputSize;
    DxUint8_t     DataIn_ptr[TEST_KEY_SIZE] = {0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D};
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    CRYS_RSAPrivUserContext_t UserPriContext_ptr;
    CRYS_RSAPubUserContext_t UserPubContext_ptr;

    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
    PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, 256);
    PrivKey_ptr->nSizeInBits = 2048;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, tD, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.e, tE, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PKCS1v15_MD5_Sign(&UserPriContext_ptr, &UserPrivKey_ptr, DataIn_ptr, Output_ptr, &OutputSize);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA1_Sign failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("MD5-SIGN", Output_ptr, OutputSize);

    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, TEST_KEY_SIZE);
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PubKey_ptr->e, tE, TEST_KEY_SIZE);
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PKCS1v15_MD5_Verify(&UserPubContext_ptr,&UserPubKey_ptr, DataIn_ptr, Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA1_Verify failed, err= 0x%x\n", err);	
        return;
	}
	
    
}

void rsa_test6(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint16_t    OutputSize;
    DxUint8_t     DataIn_ptr[TEST_KEY_SIZE] = 
    {
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
    };
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    CRYS_RSAPrivUserContext_t UserPriContext_ptr;
    CRYS_RSAPubUserContext_t UserPubContext_ptr;

    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
    PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, 256);
    PrivKey_ptr->nSizeInBits = 2048;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, tD, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.e, tE, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PSS_SHA224_Sign(&UserPriContext_ptr, &UserPrivKey_ptr, CRYS_PKCS1_MGF1,
        20, DataIn_ptr, Output_ptr, &OutputSize);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA1_Sign failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("SHA224-SIGN", Output_ptr, OutputSize);

    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, TEST_KEY_SIZE);
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PubKey_ptr->e, tE, TEST_KEY_SIZE);
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PSS_SHA224_Verify(&UserPubContext_ptr,&UserPubKey_ptr, CRYS_PKCS1_MGF1,
        20, DataIn_ptr, Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA224_Verify failed, err= 0x%x\n", err);	
        return;
	}
	
    
}

void rsa_test7(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint16_t    OutputSize;
    DxUint8_t     DataIn_ptr[TEST_KEY_SIZE] = 
    {
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
    };    
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    CRYS_RSAPrivUserContext_t UserPriContext_ptr;
    CRYS_RSAPubUserContext_t UserPubContext_ptr;

    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
    PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, 256);
    PrivKey_ptr->nSizeInBits = 2048;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, tD, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.e, tE, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PSS_SHA384_Sign(&UserPriContext_ptr, &UserPrivKey_ptr, CRYS_PKCS1_MGF1,
        20, DataIn_ptr, Output_ptr, &OutputSize);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA1_Sign failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("SHA384-SIGN", Output_ptr, OutputSize);

    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, TEST_KEY_SIZE);
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PubKey_ptr->e, tE, TEST_KEY_SIZE);
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PSS_SHA384_Verify(&UserPubContext_ptr,&UserPubKey_ptr, CRYS_PKCS1_MGF1,
        20, DataIn_ptr, Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA384_Verify failed, err= 0x%x\n", err);	
        return;
	}
	
    
}

void rsa_test8(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint16_t    OutputSize;
    DxUint8_t     DataIn_ptr[TEST_KEY_SIZE] = 
    {
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
        0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E, 0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D, 
    };    
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    CRYS_RSAPrivUserContext_t UserPriContext_ptr;
    CRYS_RSAPubUserContext_t UserPubContext_ptr;

    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
    PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, 256);
    PrivKey_ptr->nSizeInBits = 2048;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, tD, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.e, tE, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PSS_SHA512_Sign(&UserPriContext_ptr, &UserPrivKey_ptr, CRYS_PKCS1_MGF1,
        20, DataIn_ptr, Output_ptr, &OutputSize);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA1_Sign failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("SHA512-SIGN", Output_ptr, OutputSize);

    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, TEST_KEY_SIZE);
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PubKey_ptr->e, tE, TEST_KEY_SIZE);
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PSS_SHA512_Verify(&UserPubContext_ptr,&UserPubKey_ptr, CRYS_PKCS1_MGF1,
        20, DataIn_ptr, Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_PSS_SHA512_Verify failed, err= 0x%x\n", err);	
        return;
    }
}

void rsa_test(void)
{
    rsa_test1();
    rsa_test2();
    rsa_test3();
    rsa_test4();
 /* rsa_test5();
    rsa_test6();
    rsa_test7(); */
//    rsa_test8();
}

#endif

