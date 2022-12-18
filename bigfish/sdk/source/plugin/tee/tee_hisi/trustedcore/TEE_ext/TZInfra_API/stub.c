/**
 * @file    stub.c
 * @brief   Platform API functions' implementation for Linux
 * @author  Discretix
 *  		2013-05-29	Yan Polak
 */
//#include <stdio.h>
//#include <stdlib.h>
#include <stdarg.h>
//#include <string.h>
#include "DxTzService_Utils.h"
#include "DxTzServiceCryptoAPI.h"

DxUint DxTzService_IsNotMemEqualSecured (const void *p1, const void * p2, DxUint32 nBytes)
{
    return TEE_MemCompare(p1, p2, nBytes);
}

#if 0
DxInt DxTzService_snprintf(DxChar *buffer, DxUint32 n, DxChar *format, /*args*/ ...)
{
	va_list ap;
	DxInt ret;

	va_start(ap, format);
	ret = (DxInt)vsnprintf(buffer, n, format, ap);
	va_end(ap);
	return ret;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

DxStatus DxTzService_StrNCopy (DxChar *aTarget, DxUint aTargetSize, const DxChar *aSource)
{
    strncpy (aTarget, aSource, aTargetSize);

    return DX_SUCCESS;
}

DxUint DxTzService_StrNLen (const DxChar *aStr, DxUint aMaxSize)
{
	DxUint i = 0;
	if ( aStr == DX_NULL)
		return 0;

	while (*aStr++ != 0 && i < aMaxSize)
		i++;

	return i;
}

DxInt DxTzService_StrNCmp (const DxChar* Str1, const DxChar* Str2, DxUint aMaxSize)
{
    return strncmp (Str1, Str2, aMaxSize);
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

void *DxTzService_Malloc (DxUint32 size)
{
    return malloc (size);
}

void DxTzService_Free (void* ptr)
{
    free (ptr);
}

void *DxTzService_MemCpy (void *pDest, const void *pSrc, DxUint32 nBytes)
{
    return memcpy (pDest, pSrc, nBytes);
}

void *DxTzService_MemSet (void *pDest, DxChar c, DxUint32 nBytes)
{
    return memset (pDest, c, nBytes);
}

void *DxTzService_MemMove(void *pDest, const void *pSrc, DxUint32 nBytes)
{
    return memmove (pDest, pSrc, nBytes);
}
#endif
/*******************************************************************************
********************************************************************************
*******************************************************************************/

#ifndef STB_CIPHER_DRIVER
typedef struct
{
    DxUint sum;
} tmpSha256Ctx_t;

static DxUint byteSum (const DxByte* b, DxUint s)
{
    DxUint sum = 0;

    while (s--)
        sum += *b++;

    return sum;
}


DxStatus DxTzService_SHA256Init (DxTzSHA256Context_t* aContext)
{
    tmpSha256Ctx_t* ctx = (tmpSha256Ctx_t*)TEE_Malloc(sizeof(tmpSha256Ctx_t));

    if (!ctx) return DX_FAILURE;

    ctx->sum = 0;
    *aContext = (DxTzSHA256Context_t)ctx;

    return DX_SUCCESS;
}

DxStatus DxTzService_SHA256Update (DxTzSHA256Context_t  aContext,
                                   const DxUint8*       aBuffer,
                                   DxUint32             aBufferLength)
{
    tmpSha256Ctx_t* ctx = (tmpSha256Ctx_t*)aContext;

    if (!ctx) return DX_FAILURE;

    ctx->sum = byteSum (aBuffer, aBufferLength);

    return DX_SUCCESS;
}

DxStatus DxTzService_SHA256Final (DxTzSHA256Context_t   aContext,
                                  DxUint8               aDigest[SHA256_SIGNATURE_SIZE])
{
    tmpSha256Ctx_t* ctx = (tmpSha256Ctx_t*)aContext;

    if (!ctx) return DX_FAILURE;

    *(DxUint*)aDigest = ctx->sum;

    return DX_SUCCESS;
}

DxStatus DxTzService_SHA256Terminate (DxTzSHA256Context_t   aContext)
{
    tmpSha256Ctx_t* ctx = (tmpSha256Ctx_t*)aContext;

    if (!ctx) return DX_FAILURE;

    TEE_Free(ctx);

    return DX_SUCCESS;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static const DxCipher_AES128_Context_t      AES_STUB_CTX =
                                                (DxCipher_AES128_Context_t)0x22;
static const DxCipher_AES128CTR_Context_t   AES_CTR_STUB_CTX =
                                                (DxCipher_AES128CTR_Context_t)0x33;

DxStatus DxTzService_AES128_CreateContext(DxCipher_AES128_Context_t *ctx)
{
    *ctx = AES_STUB_CTX;
    return DX_SUCCESS;
}

DxStatus DxTzService_AES128_TerminateContext(DxCipher_AES128_Context_t* ctx)
{
    if (AES_STUB_CTX != *ctx)
        return DX_FAILURE;

    return DX_SUCCESS;
}

DxStatus DxTzService_AES128CTR_Init (DxCipher_AES128CTR_Context_t*  ctx,
                                     DxCipher_AES128_Context_t      internalCtx,
									 const DxUint8*                 pKey,
									 DxUint32                       key_len,
									 EDxCipherDirection             direction)
{
    if (AES_STUB_CTX != internalCtx)
        return DX_FAILURE;

    *ctx = AES_CTR_STUB_CTX;
    return DX_SUCCESS;
}

DxStatus DxTzService_AES128CTR_Finish (DxCipher_AES128CTR_Context_t *ctx)
{
    if (AES_CTR_STUB_CTX != *ctx)
        return DX_FAILURE;

    return DX_SUCCESS;
}

DxStatus DxTzService_AES128CTR_DecryptData(DxCipher_AES128CTR_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{
    if (AES_CTR_STUB_CTX != ctx)
        return DX_FAILURE;

    memcpy (pDst, pSrc, dataSize);

    return DX_SUCCESS;
}

DxStatus DxTzService_AES128CTR_EncryptData(DxCipher_AES128CTR_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{
    return DxTzService_AES128CTR_DecryptData (ctx, pSrc, pDst, dataSize, iv);
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

#endif

#if 0
DxStatus DxTzService_RandomGenerate (DxUint8* buffer, DxUint32 length)
{
    DxUint  i;

    for (i = 0; i < length; ++i)
        buffer[i] = (DxByte)(i % 0x100);

    return DX_SUCCESS;
}
#endif

/*******************************************************************************
********************************************************************************
*******************************************************************************/

DxUint DxTzService_EstimateUnwrappedSize (DxUint wrappedSize)
{
    return wrappedSize;
}

DxUint DxTzService_EstimateWrappedSize (DxUint clearSize)
{
	return clearSize;
}

DxStatus DxTzService_UnwrapBuffer (const void* pSrc, DxUint srcLen,
                                   void* pDst, DxUint *pDstLen)
{
	if (*pDstLen < srcLen) return DX_BAD_ARGUMENTS;
	DxTzService_MemCpy (pDst, pSrc, srcLen);
	*pDstLen = srcLen;
	return DX_SUCCESS;
}

DxStatus DxTzService_WrapBuffer (const void* pSrc, DxUint srcLen,
                                 void* pDst, DxUint *pDstLen)
{
	if (*pDstLen < srcLen) return DX_BAD_ARGUMENTS;
	DxTzService_MemCpy (pDst, pSrc, srcLen);
	*pDstLen = srcLen;
	return DX_SUCCESS;
}



