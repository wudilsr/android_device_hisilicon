/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_cipher.c
  Version       : Initial Draft
  Author        :
  Created       :
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "hi_mpi_cipher.h"
#include "hi_unf_hdcp.h"

HI_S32 g_CipherDevFd = -1;
static HI_S32 g_CipherInitCounter = -1;
static pthread_mutex_t   g_CipherMutex = PTHREAD_MUTEX_INITIALIZER;

#define HI_CIPHER_LOCK()  	     (void)pthread_mutex_lock(&g_CipherMutex);
#define HI_CIPHER_UNLOCK()  	 (void)pthread_mutex_unlock(&g_CipherMutex);

#define CHECK_CIPHER_OPEN()\
do{\
    HI_CIPHER_LOCK();\
    if (g_CipherInitCounter < 0)\
    {\
        HI_ERR_CIPHER("CIPHER is not open.\n");\
        HI_CIPHER_UNLOCK();\
        return HI_ERR_CIPHER_NOT_INIT;\
    }\
    HI_CIPHER_UNLOCK();\
}while(0)

static HI_S32 g_HashDevFd = -1;
static CIPHER_HASH_DATA_S g_stCipherHashData;

#define HASH_BLOCK_SIZE		(64)
#define HASH_PAD_MAX_LEN	(64)
#define HASH1_SIGNATURE_SIZE		(20)
#define HASH256_SIGNATURE_SIZE		(32)
#define HASH_MMZ_BUF_LEN	(10*1024*1024)		//10M
#define HASH_MMZ_TAIL_LEN	(8*1024)			//8K

static HI_U8 g_au8HmacKey[HASH_BLOCK_SIZE];
static HI_U32 u32HmacKeyLen = 0;
static HI_U32 g_u32HashBaseBufferLen = HASH_MMZ_BUF_LEN;

static HI_U8 g_u8CbcMac[16]; //Irdeto MSR2.2 CBC-MAC

/*----------------------------------------------*
 * external variables                           *
 *----------------------------------------------*/

/*----------------------------------------------*
 * external routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * internal routine prototypes                  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * project-wide global variables                *
 *----------------------------------------------*/

/*----------------------------------------------*
 * module-wide global variables                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * constants                                    *
 *----------------------------------------------*/

/*----------------------------------------------*
 * macros                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * routines' implementations                    *
 *----------------------------------------------*/

/*********************************************************
 * The function below is added for AES CBC-MAC
 *
 *********************************************************/
#define MAX_DATA_LEN    (0x2000) //the max data length for encryption / decryption is  8k one time



#if 0
static HI_U8 const_Zero[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#endif

/* For CMAC Calculation */

static HI_U8 const_Rb[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
};

/* Basic Functions */
static HI_VOID xor_128(HI_U8 *a, HI_U8 *b, HI_U8 *out)
{
    HI_U32 i;

    if(a == NULL || b == NULL || out == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return;
    }
    
    for (i = 0; i < 16; i++)
    {
        out[i] = a[i] ^ b[i];
    }
}

/* AES-CMAC Generation Function */
static HI_VOID leftshift_onebit(HI_U8 *input, HI_U8 *output)
{
    HI_S32 i;
    HI_U8 overflow = 0;

    if(input == NULL || output == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return;
    }
    
    for ( i = 15; i >= 0; i-- )
    {
        output[i] = input[i] << 1;
        output[i] |= overflow;
        overflow = (input[i] & 0x80) ? 1 : 0;
    }
    return;
}

//the output is the last 16 bytes only
static HI_S32 AES_Encrypt(HI_HANDLE hCipherHandle, HI_U8 *input, HI_U32 datalen, HI_U8 *output)
{
    HI_U32 u32InputAddrPhy = 0;
    HI_U32 u32OutPutAddrPhy = 0;
    HI_U32 u32MmzCached = 0;
    HI_U8* pu8InputAddrVir = NULL;
    HI_U8* pu8OutputAddrVir = NULL;
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32EncryptDataLen = 0;
    HI_U32 u32LeftDataLen = 0;
    HI_U32 i = 0;
    HI_U32 u32BlockNum = 0;
    
    u32InputAddrPhy = (HI_U32)HI_MMZ_New(MAX_DATA_LEN, 0, NULL, "CIPHER_BufIn");
    if (0 == u32InputAddrPhy)
    {
        HI_ERR_CIPHER("mmz new for u32InputAddrPhy failed!\n");
        return HI_FAILURE;
    }
    pu8InputAddrVir = HI_MMZ_Map(u32InputAddrPhy, u32MmzCached);
    if( NULL == pu8InputAddrVir )
    {
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
        HI_ERR_CIPHER("mmz map for pu8InputAddrVir failed!\n");
        return HI_FAILURE;
    }
    
    u32OutPutAddrPhy = (HI_U32)HI_MMZ_New(MAX_DATA_LEN, 0, NULL, "CIPHER_BufOut");
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("mmz new for u32OutPutAddrPhy failed!\n");
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);      
        return HI_FAILURE;
    }

    pu8OutputAddrVir = HI_MMZ_Map(u32OutPutAddrPhy, u32MmzCached);
    if( NULL == pu8OutputAddrVir )
    {
        HI_ERR_CIPHER("mmz map for pu8OutputAddrVir failed!\n");
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
        HI_MMZ_Unmap(u32OutPutAddrPhy);
        HI_MMZ_Delete(u32OutPutAddrPhy);
        return HI_FAILURE;
    }

    memset(pu8OutputAddrVir, 0, MAX_DATA_LEN);

    u32LeftDataLen = datalen;
    u32BlockNum = (datalen + MAX_DATA_LEN - 1) / MAX_DATA_LEN;
    for(i = 0; i < u32BlockNum; i++)
    {
        u32EncryptDataLen = u32LeftDataLen >= MAX_DATA_LEN ? MAX_DATA_LEN : u32LeftDataLen;
        u32LeftDataLen -= u32EncryptDataLen;
        memcpy(pu8InputAddrVir, input + i * MAX_DATA_LEN, u32EncryptDataLen);
        Ret = HI_MPI_CIPHER_Encrypt(hCipherHandle, u32InputAddrPhy, u32OutPutAddrPhy, u32EncryptDataLen);
        if(Ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Cipher encrypt failed!\n");
            goto CIPHER_RELEASE_BUF;
        }
    }
    memcpy(output, pu8OutputAddrVir + u32EncryptDataLen - 16, 16);

CIPHER_RELEASE_BUF:
    HI_MMZ_Unmap(u32InputAddrPhy);
    HI_MMZ_Delete(u32InputAddrPhy);
    HI_MMZ_Unmap(u32OutPutAddrPhy);
    HI_MMZ_Delete(u32OutPutAddrPhy);

    return Ret;
}

static HI_S32 generate_subkey(HI_HANDLE hCipherHandle, HI_U8 *K1, HI_U8 *K2)
{
    HI_U8 L[16];
    HI_U8 Z[16];
    HI_U8 tmp[16];
    HI_U32 u32DataLen = 16;
    HI_S32 Ret = HI_SUCCESS;

    if(K1 == NULL || K2 == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_FAILURE;
    }

    memset(tmp, 0x0, sizeof(tmp));
    memset(L, 0x0, sizeof(L));
    memset(Z, 0x0, sizeof(Z));

    Ret = AES_Encrypt(hCipherHandle, Z, u32DataLen, L);
    if(Ret != HI_SUCCESS)
    {
        return Ret;
    }
    
    if ( (L[0] & 0x80) == 0 ) /* If MSB(L) = 0, then K1 = L << 1 */
    {
        leftshift_onebit(L, K1);
    }
    else  /* Else K1 = ( L << 1 ) (+) Rb */
    {
        leftshift_onebit(L, tmp);
        xor_128(tmp, const_Rb, K1);
    }
    
    if ( (K1[0] & 0x80) == 0 )
    {
        leftshift_onebit(K1,K2);
    }
    else
    {
        leftshift_onebit(K1, tmp);
        xor_128(tmp, const_Rb, K2);
    }
   
    return HI_SUCCESS;
}

static HI_VOID padding ( HI_U8 *lastb, HI_U8 *pad, HI_U32 length )
{
    HI_U32 j;

    if(lastb == NULL || pad == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return;
    }
    
    /* original last block */
    for ( j = 0; j < 16; j++ )
    {
        if ( j < length )
        {
            pad[j] = lastb[j];
        }
        else if ( j == length )
        {
            pad[j] = 0x80;
        }
        else
        {
            pad[j] = 0x00;
        }
    }
}

static HI_S32 Cipher_HashMmzInit(HI_VOID)
{
	HI_U32 u32Testcached = 0;
	HI_U32 u32HashBufLen = 0;

	u32HashBufLen = g_u32HashBaseBufferLen + HASH_MMZ_TAIL_LEN;
	
    g_stCipherHashData.stMMZBuffer.u32StartPhyAddr = (HI_U32)HI_MMZ_New(u32HashBufLen, 0, NULL, "CIPHER_HashBuffer");
    if (0 == g_stCipherHashData.stMMZBuffer.u32StartPhyAddr)
    {
    	g_u32HashBaseBufferLen = g_u32HashBaseBufferLen / 2;
    	u32HashBufLen = g_u32HashBaseBufferLen + HASH_MMZ_TAIL_LEN;
	    g_stCipherHashData.stMMZBuffer.u32StartPhyAddr = (HI_U32)HI_MMZ_New(u32HashBufLen, 0, NULL, "CIPHER_HashBuffer");
	    if (0 == g_stCipherHashData.stMMZBuffer.u32StartPhyAddr)
	    {
	    	g_u32HashBaseBufferLen = g_u32HashBaseBufferLen / 2;
	        u32HashBufLen = g_u32HashBaseBufferLen + HASH_MMZ_TAIL_LEN;
		    g_stCipherHashData.stMMZBuffer.u32StartPhyAddr = (HI_U32)HI_MMZ_New(u32HashBufLen, 0, NULL, "CIPHER_HashBuffer");
		    if (0 == g_stCipherHashData.stMMZBuffer.u32StartPhyAddr)
		    {
		        HI_ERR_CIPHER("Error: Get mmz buffer for hash failed!\n");
		        return HI_FAILURE;
		    }
	    }
    }

    g_stCipherHashData.stMMZBuffer.u32StartVirAddr = (HI_U32)HI_MMZ_Map(g_stCipherHashData.stMMZBuffer.u32StartPhyAddr, u32Testcached);
	if( 0 == (HI_VOID *)g_stCipherHashData.stMMZBuffer.u32StartVirAddr )
	{
        HI_ERR_CIPHER("Error: Map mmz buffer for hash failed!\n");
		HI_MMZ_Delete(g_stCipherHashData.stMMZBuffer.u32StartPhyAddr);
		memset(&(g_stCipherHashData.stMMZBuffer), 0, sizeof(g_stCipherHashData.stMMZBuffer));
        return HI_FAILURE;
	}

	return HI_SUCCESS;
}

static HI_VOID Cipher_HashMmzDeInit(HI_VOID)
{
	(HI_VOID)HI_MMZ_Unmap(g_stCipherHashData.stMMZBuffer.u32StartPhyAddr);
	(HI_VOID)HI_MMZ_Delete(g_stCipherHashData.stMMZBuffer.u32StartPhyAddr);
	memset(&g_stCipherHashData.stMMZBuffer, 0, sizeof(g_stCipherHashData.stMMZBuffer));
}

static HI_S32 Cipher_HashMsgPadding(CIPHER_HASH_DATA_S *pCipherHashData)
{
    HI_U32 u32Tmp = 0;
    HI_U32 i = 0;
    HI_U8 u8PadLen[8];

    if( NULL == pCipherHashData )
    {
        HI_ERR_CIPHER("Error! Null pointer input!\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    memset(pCipherHashData->u8Padding, 0, sizeof(pCipherHashData->u8Padding));

    u32Tmp = pCipherHashData->u32TotalDataLen % HASH_PAD_MAX_LEN;
    /* 56 = 64 - 8, 120 = 56 + 64 */
    pCipherHashData->u32PaddingLen = (u32Tmp < 56) ? (56 - u32Tmp) : (120 - u32Tmp);
    /* add 8 bytes fix data length */
    pCipherHashData->u32PaddingLen += 8;

    /* Format(binary): {data|1000...00| fix_data_len(bits)} */
    memset(pCipherHashData->u8Padding, 0x80, 1);
    memset(pCipherHashData->u8Padding + 1, 0, pCipherHashData->u32PaddingLen - 1 - 8);
    /* write 8 bytes fix data length */
    memset(u8PadLen, 0, sizeof(u8PadLen));
    u32Tmp = pCipherHashData->u32TotalDataLen;

#if 0
    if( (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pCipherHashData->enShaType)
     || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pCipherHashData->enShaType) )
    {
        for (i = 0; i < 8; i++)
        {
            u8PadLen[i] = ((u32Tmp * 8 + 512) >> (7 - i) * 8) & 0xff;
        }
    }
    else
#endif
    {
        for (i = 0; i < 8; i++)
        {
            u8PadLen[i] = ((u32Tmp * 8) >> ((7 - i) * 8)) & 0xff;
        }
    }

    memcpy(pCipherHashData->u8Padding + pCipherHashData->u32PaddingLen - 8, u8PadLen, 8);

    return HI_SUCCESS;
}

static HI_S32 CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_SUCCESS;
	HI_UNF_CIPHER_HASH_TYPE_E enShaTypeBak = HI_UNF_CIPHER_HASH_TYPE_BUTT;

    if( (NULL == pstHashAttr)
     || (NULL == pHashHandle)
     || (pstHashAttr->eShaType >= HI_UNF_CIPHER_HASH_TYPE_BUTT))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    enShaTypeBak = pstHashAttr->eShaType;

    CHECK_CIPHER_OPEN();

    if(g_HashDevFd > 0)
    {
        HI_ERR_CIPHER("Hash module is busy!\n");
        return HI_FAILURE;       
    }

    g_HashDevFd = 1;
	memset(&g_stCipherHashData, 0, sizeof(g_stCipherHashData));
	g_u32HashBaseBufferLen = HASH_MMZ_BUF_LEN;
	ret = Cipher_HashMmzInit();
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("Hash mmz buffer initial failed!\n");
		g_HashDevFd = -1;
		return HI_FAILURE;
	}

	if ( (HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstHashAttr->eShaType)
	  || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashAttr->eShaType ))
	{
	    g_stCipherHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA1;
	}
	else if ( (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstHashAttr->eShaType)
		 || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashAttr->eShaType))
	{
	    g_stCipherHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
	}
	else
	{
	    ;/* Invalid hash/hmac type, no need to be processed, it have been processed before */
	}

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHINIT, &g_stCipherHashData);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Error, ioctl for hash initial failed!\n");
        g_HashDevFd = -1;
		Cipher_HashMmzDeInit();
        return ret;
    }

	g_stCipherHashData.enShaType = enShaTypeBak;
    *pHashHandle = (HI_U32)&g_stCipherHashData;
	
    return HI_SUCCESS;
}

static HI_S32 CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S *)hHashHandle;
	HI_U32 u32Tmp = 0;
	HI_U32 u32OffsetBak = 0;
	HI_U32 u32BufInUsedLen = 0;
	HI_U32 i = 0;

    if((NULL == pu8InputData) || (NULL == pstCipherHashData))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        g_HashDevFd = -1;
		Cipher_HashMmzDeInit();
        return HI_ERR_CIPHER_INVALID_PARA;
    }

	if (0 == u32InputDataLen)
	{
		if( pstCipherHashData->u32TotalDataLen > 0)
		{
			return HI_SUCCESS;
		}
		else
		{
	        g_HashDevFd = -1;
			Cipher_HashMmzDeInit();
		    return HI_ERR_CIPHER_INVALID_PARA;
		}
	}

    CHECK_CIPHER_OPEN();

	pstCipherHashData->u32TotalDataLen += u32InputDataLen;
	u32OffsetBak = pstCipherHashData->u32Offset;

	u32Tmp = (u32InputDataLen+ pstCipherHashData->u32Offset) / g_u32HashBaseBufferLen;
	if ( 0 == u32Tmp )
	{
		/* Total length is less than g_u32HashBaseBufferLen, move data to mmz buffer directly */
        memcpy((HI_U8 *)pstCipherHashData->stMMZBuffer.u32StartVirAddr + pstCipherHashData->u32Offset, pu8InputData, u32InputDataLen);
		pstCipherHashData->u32Offset += u32InputDataLen;
		return HI_SUCCESS;
	}
	else
	{
		/* Send data down piece by piece */
	    for ( i = 0 ; i < u32Tmp; i++ )
	    {
	        memcpy((HI_U8 *)pstCipherHashData->stMMZBuffer.u32StartVirAddr + pstCipherHashData->u32Offset,
					pu8InputData + u32BufInUsedLen,
					g_u32HashBaseBufferLen - pstCipherHashData->u32Offset);
			u32BufInUsedLen += g_u32HashBaseBufferLen - pstCipherHashData->u32Offset;
			pstCipherHashData->u32InputDataLen = g_u32HashBaseBufferLen;
			pstCipherHashData->u32Offset = 0;
			ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHUPDATE, pstCipherHashData);
		    if(ret != HI_SUCCESS)
		    {
		        HI_ERR_CIPHER("Error, ioctl for hash update failed!\n");
		        g_HashDevFd = -1;
				Cipher_HashMmzDeInit();
		        return ret;
		    }
	    }
	}

	/* Move tail data to mmz buffer */
	pstCipherHashData->u32Offset = u32OffsetBak;
	u32Tmp = (u32InputDataLen+ pstCipherHashData->u32Offset) % g_u32HashBaseBufferLen;
	memcpy((HI_U8 *)pstCipherHashData->stMMZBuffer.u32StartVirAddr, pu8InputData + u32BufInUsedLen, u32Tmp);
	pstCipherHashData->u32Offset = u32Tmp;

    return HI_SUCCESS;
}

static HI_S32 CIPHER_CbcMacUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S *)hHashHandle;

    if((NULL == pu8InputData) || (NULL == pstCipherHashData))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if(u32InputDataLen % 16 != 0)
    {
        HI_ERR_CIPHER("Invalid parameter, u32InputDataLen should be aligned with 16 byte!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CHECK_CIPHER_OPEN();  
    ret = AES_Encrypt(pstCipherHashData->hHandle, pu8InputData, u32InputDataLen, g_u8CbcMac);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("CBC-MAC update failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S *)hHashHandle;
	HI_U32 u32Tmp = 0;

    if(( NULL == pu8OutputHash ) || ( NULL == pstCipherHashData ))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        g_HashDevFd = -1;
		Cipher_HashMmzDeInit();
        return HI_FAILURE;
    }

    CHECK_CIPHER_OPEN();

	ret = Cipher_HashMsgPadding(pstCipherHashData);
	if ( HI_SUCCESS != ret )
	{
        HI_ERR_CIPHER("Error, hash message padding failed!\n");
        g_HashDevFd = -1;
		Cipher_HashMmzDeInit();
	    return ret;
	}

	/* the remained data length must be 64 bytes aligned */
	u32Tmp = (pstCipherHashData->u32Offset + pstCipherHashData->u32PaddingLen) % HASH_BLOCK_SIZE;
	if ( 0 != u32Tmp)
	{
	    HI_ERR_CIPHER("Error, invalid length for hash final!\n");
        g_HashDevFd = -1;
		Cipher_HashMmzDeInit();
		return HI_FAILURE;
	}

	/* copy all the remained data to mmz buffer */
	memcpy((HI_U8 *)pstCipherHashData->stMMZBuffer.u32StartVirAddr + pstCipherHashData->u32Offset,
					pstCipherHashData->u8Padding,
					pstCipherHashData->u32PaddingLen);

	pstCipherHashData->u32InputDataLen = pstCipherHashData->u32Offset + pstCipherHashData->u32PaddingLen;
    pstCipherHashData->pu8Output= pu8OutputHash;
    ret = ioctl(g_CipherDevFd, CMD_CIPHER_CALCHASHFINAL, pstCipherHashData);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Error, ioctl for hash final failed!\n");
        g_HashDevFd = -1;
		Cipher_HashMmzDeInit();
        return ret;
    }

    g_HashDevFd = -1;
	Cipher_HashMmzDeInit();

    return HI_SUCCESS;
}

static HI_S32 CIPHER_CbcMacFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S *)hHashHandle;

    if((NULL == pu8OutputHash) || (NULL == pstCipherHashData))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CHECK_CIPHER_OPEN();

    memcpy(pu8OutputHash, g_u8CbcMac, 16);
    ret = HI_UNF_CIPHER_DestroyHandle(pstCipherHashData->hHandle);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Destroy cipher handle failed!\n");
        return ret;
    }

    return HI_SUCCESS;
}


static HI_S32 CIPHER_HmacKeyInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_U8 au8Hmackey[HASH_BLOCK_SIZE])
{
    HI_S32 ret = HI_SUCCESS;
    HI_HANDLE hHash = 0;

    if((pstHashAttr == NULL)||(pstHashAttr->pu8HMACKey == NULL)||(pstHashAttr->u32HMACKeyLen == 0))
    {
        HI_ERR_CIPHER("Invalid parameters.\n");
		g_HashDevFd = -1;
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*key length is less than 64bytes, copy directly*/
    if(pstHashAttr->u32HMACKeyLen <= HASH_BLOCK_SIZE)
    {
        memcpy(au8Hmackey, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen);
		u32HmacKeyLen = pstHashAttr->u32HMACKeyLen;
        return HI_SUCCESS;
    }

    /*key length more than 64bytes, calcute the hash result*/
    ret = CIPHER_HashInit(pstHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Cipher_HashInit failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    ret = CIPHER_HashUpdate(hHash, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Cipher_HashUpdate failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    ret = CIPHER_HashFinal(hHash,au8Hmackey);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Cipher_HashFinal failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

	if ( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashAttr->eShaType )
	{
		u32HmacKeyLen = 20;
	}
	else
	{
		u32HmacKeyLen = 32;
	}

    return HI_SUCCESS;
}

static HI_S32 CIPHER_HmacInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 i_key_pad[HASH_BLOCK_SIZE];
	HI_U32 i = 0;

    if( (NULL == pstHashAttr)
     || (NULL == pHashHandle)
     || (pstHashAttr->eShaType >= HI_UNF_CIPHER_HASH_TYPE_BUTT)
     || (NULL == pstHashAttr->pu8HMACKey)
     || (0 == pstHashAttr->u32HMACKeyLen))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CHECK_CIPHER_OPEN();

	/* Init hmac key */
    memset(g_au8HmacKey, 0, sizeof(g_au8HmacKey));
    ret = CIPHER_HmacKeyInit(pstHashAttr, g_au8HmacKey);
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("Hmac key initial failed!\n");
        g_HashDevFd = -1;
		return HI_FAILURE;
	} 

	/* hash i_key_pad and message start */
	ret = CIPHER_HashInit(pstHashAttr, pHashHandle);
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("hash i_key_pad and message start failed!\n");
		return HI_FAILURE;
	}

	/* generate i_key_pad */
	memset(i_key_pad, 0x36, HASH_BLOCK_SIZE);
    for(i=0; i < u32HmacKeyLen; i++)
    {
        i_key_pad[i] = i_key_pad[i] ^ g_au8HmacKey[i];
    }

	/* hash i_key_pad update */
	ret = CIPHER_HashUpdate(*pHashHandle, i_key_pad, sizeof(i_key_pad));
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("hash i_key_pad and message update failed!\n"); 
		return HI_FAILURE;
	}

    return HI_SUCCESS;
}

static HI_S32 CIPHER_CbcMacInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    HI_HANDLE hCipher;

    if( (NULL == pstHashAttr) || (NULL == pHashHandle) || (pstHashAttr->eShaType >= HI_UNF_CIPHER_HASH_TYPE_BUTT))
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CHECK_CIPHER_OPEN();    

    memset(&stCipherAttr, 0, sizeof(HI_UNF_CIPHER_ATTS_S));
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    ret = HI_UNF_CIPHER_CreateHandle(&hCipher, &stCipherAttr);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Create cipher handle failed!\n");
        return ret;
    }
    memset(&g_stCipherHashData, 0, sizeof(CIPHER_HASH_DATA_S));
    g_stCipherHashData.enShaType = HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC;
    g_stCipherHashData.hHandle = hCipher;
    *pHashHandle = (HI_HANDLE)(&g_stCipherHashData);

    memset(&stCipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    stCipherCtrl.bKeyByCA = HI_TRUE;
    stCipherCtrl.enCaType = HI_UNF_CIPHER_CA_TYPE_IRDETO_HCA;
    stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
    stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    stCipherCtrl.stChangeFlags.bit1IV = HI_TRUE;
    ret = HI_UNF_CIPHER_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Configure cipher handle failed!\n");
        return ret;
    }    
    
    return ret;
}

static HI_S32 CIPHER_HmacUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_SUCCESS;

	ret = CIPHER_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);
	if ( HI_SUCCESS != ret )
	{
	    HI_ERR_CIPHER("hmac message update failed!\n"); 
		return HI_FAILURE;
	}

    return HI_SUCCESS;
}

static HI_S32 CIPHER_HmacFinal(HI_HANDLE hHashHandle, HI_U8 *pu8Output)
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S *)hHashHandle;
	HI_HANDLE hHash = HI_INVALID_HANDLE;
	HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U8 hash_sum_1[HASH256_SIGNATURE_SIZE];
    HI_U8 o_key_pad[HASH_BLOCK_SIZE];
    HI_U32 i;

	if ( NULL == pu8Output )
	{
   	    HI_ERR_CIPHER("Invalid param input, hmac final failed!\n"); 
		return HI_ERR_CIPHER_INVALID_POINT;
	}

    /* hash i_key_pad+message finished */
    memset(hash_sum_1, 0, sizeof(hash_sum_1));
    ret = CIPHER_HashFinal(hHashHandle, hash_sum_1);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Final i_key_pad+message failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    /* generate o_key_pad */
    memset(o_key_pad, 0x5c, HASH_BLOCK_SIZE);
    for(i=0; i < u32HmacKeyLen; i++)
    {
        o_key_pad[i] = o_key_pad[i] ^ g_au8HmacKey[i];
    }

    /* hash o_key_pad+hash_sum_1 start */
	memset(&stHashAttr, 0, sizeof(stHashAttr));
	stHashAttr.eShaType = pstCipherHashData->enShaType;
    ret = CIPHER_HashInit(&stHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Init o_key_pad+hash_sum_1 failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    /* hash o_key_pad */
    ret = CIPHER_HashUpdate(hHash, (HI_U8 *)o_key_pad, HASH_BLOCK_SIZE);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Update o_key_pad failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    /* hash hash_sum_1 */
	if ( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstCipherHashData->enShaType )
	{
	    ret = CIPHER_HashUpdate(hHash, (HI_U8 *)hash_sum_1, HASH1_SIGNATURE_SIZE);	
	}
	else
	{
	    ret = CIPHER_HashUpdate(hHash, (HI_U8 *)hash_sum_1, HASH256_SIGNATURE_SIZE);
	}

    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Update hash_sum_1 failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    /* hash o_key_pad+hash_sum_1 finished */
    ret = CIPHER_HashFinal(hHash, pu8Output);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Final o_key_pad+hash_sum_1 failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_Init(HI_VOID)
{
    HI_CIPHER_LOCK();

    if (g_CipherInitCounter > 0)
    {
	    g_CipherInitCounter++;
        HI_CIPHER_UNLOCK();
        return HI_SUCCESS;
    }

    g_CipherDevFd = open("/dev/"UMAP_DEVNAME_CIPHER, O_RDWR, 0);
    if (g_CipherDevFd < 0)
    {
        HI_FATAL_CIPHER("Open CIPHER err.\n");
        HI_CIPHER_UNLOCK();
        return HI_ERR_CIPHER_FAILED_INIT;
    }

	g_CipherInitCounter = 1;
    HI_CIPHER_UNLOCK();

    return HI_SUCCESS;
}



HI_S32 HI_MPI_CIPHER_DeInit(HI_VOID)
{
    HI_S32 Ret;

    HI_CIPHER_LOCK();

    if(g_CipherInitCounter > 0)
    {
        g_CipherInitCounter--;
    }
	if(g_CipherInitCounter != 0)
	{
        HI_CIPHER_UNLOCK();
        return HI_SUCCESS;
    }

    Ret = close(g_CipherDevFd);

    if(HI_SUCCESS != Ret)
    {
        HI_FATAL_CIPHER("Close cipher err.\n");
		g_CipherInitCounter++;
        HI_CIPHER_UNLOCK();
        return HI_ERR_CIPHER_NOT_INIT;
    }

    g_CipherDevFd = -1;
	g_CipherInitCounter = -1;

    HI_CIPHER_UNLOCK();

    return HI_SUCCESS;
}


HI_S32 HI_MPI_CIPHER_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr)
{
    HI_S32 Ret = HI_SUCCESS;
    CIPHER_HANDLE_S stCIHandle = {0};

if ( ( NULL == phCipher ) || ( NULL == pstCipherAttr ) )
    {
        HI_ERR_CIPHER("Invalid param, null pointer!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CHECK_CIPHER_OPEN();

    stCIHandle.stCipherAtts.enCipherType = pstCipherAttr->enCipherType;
    Ret=ioctl(g_CipherDevFd, CMD_CIPHER_CREATEHANDLE, &stCIHandle);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    *phCipher = stCIHandle.hCIHandle;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_DestroyHandle(HI_HANDLE hCipher)
{
    HI_S32 Ret;
    
    CHECK_CIPHER_OPEN();

    Ret=ioctl(g_CipherDevFd, CMD_CIPHER_DESTROYHANDLE, &hCipher);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }
   
    return HI_SUCCESS;
}


HI_S32 HI_MPI_CIPHER_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    HI_S32 Ret;
    CIPHER_Config_CTRL configdata;

    if (NULL == pstCtrl)
    {
        HI_ERR_CIPHER("para pstCtrl is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    memcpy(&configdata.CIpstCtrl, pstCtrl, sizeof(HI_UNF_CIPHER_CTRL_S));
    configdata.CIHandle=hCipher;

    if(configdata.CIpstCtrl.enWorkMode >= HI_UNF_CIPHER_WORK_MODE_BUTT)
    {
        HI_ERR_CIPHER("para set CIPHER wokemode is invalid.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CHECK_CIPHER_OPEN();

    Ret=ioctl(g_CipherDevFd, CMD_CIPHER_CONFIGHANDLE, &configdata);

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}


HI_S32 HI_MPI_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_S32 Ret;
    CIPHER_DATA_S CIdata;
    
    if ( u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN || u32ByteLength > HI_UNF_CIPHER_MAX_CRYPT_LEN)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.u32DataLength=u32ByteLength;
    CIdata.CIHandle=hCipher;

    CHECK_CIPHER_OPEN();

    Ret=ioctl(g_CipherDevFd, CMD_CIPHER_ENCRYPT, &CIdata);

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}


HI_S32 HI_MPI_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    HI_S32 Ret;
    CIPHER_DATA_S CIdata;

    if (u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN || u32ByteLength > HI_UNF_CIPHER_MAX_CRYPT_LEN)
    {
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CIdata.ScrPhyAddr=u32SrcPhyAddr;
    CIdata.DestPhyAddr=u32DestPhyAddr;
    CIdata.u32DataLength = u32ByteLength;
    CIdata.CIHandle=hCipher;

    CHECK_CIPHER_OPEN();

    Ret=ioctl(g_CipherDevFd,CMD_CIPHER_DECRYPT, &CIdata);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_EncryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    HI_S32 Ret;
    HI_U32 chnid;
    HI_U32 i;
    CIPHER_DATA_S CIdata;
    HI_UNF_CIPHER_DATA_S *pPkgTmp;
    
    chnid=hCipher&0x00ff;
    if ( 0 == chnid )
    {
        HI_ERR_CIPHER("invalid chnid 0.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    
    for (i = 0; i < u32DataPkgNum; i++)
    {
        pPkgTmp = pstDataPkg + i;
        if (pPkgTmp->u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN || pPkgTmp->u32ByteLength > HI_UNF_CIPHER_MAX_CRYPT_LEN)
        {
            HI_ERR_CIPHER("Pkg%d 's length(%d) invalid.\n", i, pPkgTmp->u32ByteLength);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    CIdata.ScrPhyAddr=(HI_U32)pstDataPkg;
    CIdata.DestPhyAddr= 0;
    CIdata.u32DataLength=u32DataPkgNum;
    CIdata.CIHandle=hCipher;

    CHECK_CIPHER_OPEN();

    Ret=ioctl(g_CipherDevFd,CMD_CIPHER_ENCRYPTMULTI, &CIdata); 

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_DecryptMulti(HI_HANDLE hCipher, HI_UNF_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    HI_S32 Ret;
    HI_U32 chnid;
    HI_U32 i;
    CIPHER_DATA_S CIdata;
    HI_UNF_CIPHER_DATA_S *pPkgTmp;
    
    chnid=hCipher&0x00ff;
    if ( 0 == chnid )
    {
        HI_ERR_CIPHER("invalid chnid 0.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    
    for (i = 0; i < u32DataPkgNum; i++)
    {
        pPkgTmp = pstDataPkg + i;
        if (pPkgTmp->u32ByteLength < HI_UNF_CIPHER_MIN_CRYPT_LEN || pPkgTmp->u32ByteLength > HI_UNF_CIPHER_MAX_CRYPT_LEN)
        {
            HI_ERR_CIPHER("Pkg%d 's length(%d) invalid.\n", i, pPkgTmp->u32ByteLength);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    CIdata.ScrPhyAddr=(HI_U32)pstDataPkg;
    CIdata.DestPhyAddr= 0;
    CIdata.u32DataLength=u32DataPkgNum;
    CIdata.CIHandle=hCipher;

    CHECK_CIPHER_OPEN();

    Ret=ioctl(g_CipherDevFd,CMD_CIPHER_DECRYPTMULTI, &CIdata); 

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtrl)
{
    HI_S32 Ret;
    CIPHER_Config_CTRL  configdata;

    CHECK_CIPHER_OPEN();

    configdata.CIHandle = hCipherHandle;
    memset(&configdata.CIpstCtrl, 0, sizeof(configdata.CIpstCtrl));
    
    Ret = ioctl(g_CipherDevFd, CMD_CIPHER_GETHANDLECONFIG, &configdata);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }
    memcpy(pstCtrl, &configdata.CIpstCtrl, sizeof(configdata.CIpstCtrl));

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_CalcMAC(HI_HANDLE hCipherHandle, HI_U8 *pInputData, HI_U32 u32InputDataLen,
                                        HI_U8 *pOutputMAC, HI_BOOL bIsLastBlock)
{
    HI_U8 X[16], M_last[16], padded[16];
    static HI_U8 K1[16] = {0};
	static HI_U8 K2[16] = {0};
    HI_U32 n, i, flag;
    HI_U8 u8TmpBuf[16];
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    static HI_BOOL bIsFirstBlock = HI_TRUE;

    CHECK_CIPHER_OPEN();

    memset(&stCipherCtrl, 0, sizeof(stCipherCtrl));
    memset(u8TmpBuf, 0, sizeof(u8TmpBuf));
    memset(X, 0, sizeof(X));
    memset(M_last, 0, sizeof(M_last));
    memset(padded, 0, sizeof(padded));

    if(bIsFirstBlock) //if first block, reset the configure handle and generate the subkey again
    {
        Ret = HI_MPI_CIPHER_GetHandleConfig(hCipherHandle, &stCipherCtrl);
        stCipherCtrl.stChangeFlags.bit1IV = 1;
        memset ((HI_U8*)stCipherCtrl.u32IV, 0, 16);
        Ret |= HI_MPI_CIPHER_ConfigHandle(hCipherHandle, &stCipherCtrl);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }
       
        Ret = generate_subkey(hCipherHandle, K1, K2);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }

        //After genreate the subkey, reset the configure handle
        Ret = HI_MPI_CIPHER_GetHandleConfig(hCipherHandle, &stCipherCtrl);
        stCipherCtrl.stChangeFlags.bit1IV = 1;
        memset ((HI_U8*)stCipherCtrl.u32IV, 0, 16);
        Ret |= HI_MPI_CIPHER_ConfigHandle(hCipherHandle, &stCipherCtrl);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }
        bIsFirstBlock = HI_FALSE;
    }

    if(!bIsLastBlock)
    {
       Ret = AES_Encrypt(hCipherHandle, pInputData, u32InputDataLen, u8TmpBuf); /* X := AES-128(KEY, Y); */
       if(Ret != HI_SUCCESS)
       {
            return Ret;
       }
    }
    else
    {    
        bIsFirstBlock = HI_TRUE;
        
        n = (u32InputDataLen + 15) / 16; /* n is number of rounds */
        if ( n == 0 )
        {
            n = 1;
            flag = 0;
        }
        else
        {
            if ( (u32InputDataLen % 16) == 0 ) /* last block is a complete block */
            {
                flag = 1;
            }
            else /* last block is not complete block */
            {
                flag = 0;
            }
        }
        
        if ( flag )  /* last block is complete block */
        {
            xor_128(&pInputData[16 * (n - 1)], K1, M_last);
        }
        else
        {
            padding(&pInputData[16 * (n - 1)], padded, u32InputDataLen % 16);
            xor_128(padded, K2, M_last);
        }
        
        if(n > 1)
        {
           Ret = AES_Encrypt(hCipherHandle, pInputData, 16 * (n - 1), u8TmpBuf); /* X := AES-128(KEY, Y); */
           if(Ret != HI_SUCCESS)
           {
                return Ret;
           }
        }
        
        Ret = AES_Encrypt(hCipherHandle, M_last, 16, X);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }    
        
        for ( i = 0; i < 16; i++ )
        {
            pOutputMAC[i] = X[i];
        }
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_HashInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
	if ((HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstHashAttr->eShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstHashAttr->eShaType) )
	{
	    return CIPHER_HashInit(pstHashAttr, pHashHandle);
	}
    else if ((HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashAttr->eShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstHashAttr->eShaType))
    {
        return CIPHER_HmacInit(pstHashAttr, pHashHandle);
    }
    else if (HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC == pstHashAttr->eShaType)
    {
        return CIPHER_CbcMacInit(pstHashAttr, pHashHandle);
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S *)hHashHandle;

	if ( (HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstCipherHashData->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstCipherHashData->enShaType ) )
	{
		return CIPHER_HashUpdate(hHashHandle, pu8InputData, u32InputDataLen);
	}
    else if ((HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstCipherHashData->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstCipherHashData->enShaType))
    {
        return CIPHER_HmacUpdate(hHashHandle, pu8InputData, u32InputDataLen);
    }
    else if (HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC == pstCipherHashData->enShaType)
    {
        return CIPHER_CbcMacUpdate(hHashHandle, pu8InputData, u32InputDataLen);
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    CIPHER_HASH_DATA_S *pstCipherHashData = (CIPHER_HASH_DATA_S *)hHashHandle;

	if ((HI_UNF_CIPHER_HASH_TYPE_SHA1 == pstCipherHashData->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_SHA256 == pstCipherHashData->enShaType) )
	{
		return CIPHER_HashFinal(hHashHandle, pu8OutputHash);
	}
    else if ((HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstCipherHashData->enShaType) || (HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256 == pstCipherHashData->enShaType))
    {
        return CIPHER_HmacFinal(hHashHandle, pu8OutputHash);
    }
    else if (HI_UNF_CIPHER_HASH_TYPE_IRDETO_CBCMAC == pstCipherHashData->enShaType)
    {
        return CIPHER_CbcMacFinal(hHashHandle, pu8OutputHash);
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_CbcMac_Auth(HI_U8 *pu8RefCbcMac, HI_U32 u32AppLen)
{
    HI_S32 Ret;
    CIPHER_CBCMAC_DATA_S CIdata;

    if (pu8RefCbcMac == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }    
  
    if (u32AppLen % 16 != 0)
    {
        HI_ERR_CIPHER("Invalid parameter, u32AppLen should be algined with 16 byte!\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CIdata.pu8RefCbcMac = pu8RefCbcMac;
    CIdata.u32AppLen = u32AppLen;

    CHECK_CIPHER_OPEN();

    Ret = ioctl(g_CipherDevFd, CMD_CIPHER_CBCMAC_AUTH, &CIdata);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    return HI_SUCCESS;
}


HI_S32 HI_MPI_CIPHER_EncryptHDCPKey(HI_UNF_HDCP_HDCPKEY_S *pstHdcpKey, HI_BOOL bIsUseOTPRootKey, HI_U8 u8OutEncryptKey[HDCP_KEY_CHIP_FILE_SIZE])
{
    HI_S32 ret = HI_SUCCESS;
    CIPHER_HDCP_KEY_TRANSFER_S stDecryptHdcpKeyTransfer;

    if ( NULL == u8OutEncryptKey)
    {
        HI_ERR_CIPHER("Invalid param , null pointer!\n");
        return HI_FAILURE;
    }

    if ( (HI_TRUE != bIsUseOTPRootKey) && (HI_FALSE != bIsUseOTPRootKey) )
    {
        HI_ERR_CIPHER("Invalid param, unexpected bIsUseOTPRootKey!");
        return HI_FAILURE;
    }

    memset(&stDecryptHdcpKeyTransfer, 0x0, sizeof(CIPHER_HDCP_KEY_TRANSFER_S));
    stDecryptHdcpKeyTransfer.bIsUseOTPRootKey = bIsUseOTPRootKey;
    memcpy(&stDecryptHdcpKeyTransfer.stHdcpKey, pstHdcpKey, sizeof(HI_UNF_HDCP_HDCPKEY_S));

    if(g_CipherDevFd <0)
    {
        HI_ERR_CIPHER("Cipher not init!\n");
        return HI_FAILURE;
    }
    ret = ioctl(g_CipherDevFd, CMD_CIPHER_ENCRYPTHDCPKEY, &stDecryptHdcpKeyTransfer);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("cmd encrypt hdcpkey failed!\n");
        return HI_FAILURE;
    }

    memcpy(u8OutEncryptKey, stDecryptHdcpKeyTransfer.u8FlashEncryptedHdcpKey, HDCP_KEY_CHIP_FILE_SIZE);

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_LoadHDCPKey(HI_U8 *pu8EncryptedHDCPKey, HI_U32 u32Len)
{
    HI_S32 ret = HI_SUCCESS;
    HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S stHdcpKey;

    if ( (NULL == pu8EncryptedHDCPKey) || (HDCP_KEY_CHIP_FILE_SIZE != u32Len) )
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    if(g_CipherDevFd <0)
    {
        HI_ERR_CIPHER("Cipher not init!\n");
        return HI_FAILURE;
    }

    memset(&stHdcpKey, 0, sizeof(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S));
    memcpy(stHdcpKey.u8Key, pu8EncryptedHDCPKey, u32Len);
    stHdcpKey.u32KeyLen = u32Len;
    stHdcpKey.enHDCPVersion = HI_DRV_HDCP_VERIOSN_1x;
    stHdcpKey.enHDCPKeyType = HI_DRV_HDCPKEY_TX0;

    ret = ioctl(g_CipherDevFd, CMD_CIPHER_LOADHDCPKEY, &stHdcpKey);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("Load hdcpkey failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber, HI_U32 u32TimeOutUs)
{
    HI_S32 Ret = HI_SUCCESS;
    CIPHER_RNG_S stRNG;
    
    if (NULL == pu32RandomNumber)
    {
        HI_ERR_CIPHER("Input pointer is null.\n");
        return HI_ERR_CIPHER_INVALID_POINT;
    }

    CHECK_CIPHER_OPEN();

    stRNG.u32RNG = 0;
    stRNG.u32TimeOutUs = u32TimeOutUs;
    Ret = ioctl(g_CipherDevFd, CMD_CIPHER_GETRANDOMNUMBER, &stRNG);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Get random number failed, ret = %x\n", Ret);
		return Ret;
    }

    *pu32RandomNumber = stRNG.u32RNG;

    return HI_SUCCESS;
}

