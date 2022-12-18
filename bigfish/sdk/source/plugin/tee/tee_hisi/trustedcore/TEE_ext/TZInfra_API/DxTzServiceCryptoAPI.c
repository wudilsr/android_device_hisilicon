//#include <sw_types.h>
//#include <otz_tee_mem_mgmt.h>

//#include "DxTzService_InternalDefs.h"
#ifdef STB_CIPHER_DRIVER
#include "DxTzServiceAPI.h"
#include "drv_cipher_define.h"
#include "sre_syscall.h"
#include "sre_syscalls_ext.h"
#if 0   //def USE_CRYS
#include "DxTzRSA_CRYS_Impl.h"
#include "DxTzRandom_CRYS_Impl.h"
#include "DxTzHash_CRYS_Impl.h"
#include "DxTzHmac_CRYS_Impl.h"
#include "DxTzAES128_CRYS_Impl.h"
#else
//#include "DX_VOS_Rng.h"
#endif
#define TC_CHANGE
extern void uart_printf_func(const char *fmt, ...);

//#define QA_LOG_MSG(fmt, args...) uart_printf_func("%s %s: " fmt "\n", __FUNCTION__, ## args)
#define QA_LOG_MSG uart_printf_func
//#define DxHwLogTrace QA_LOG_MSG

/**
 * These API functions defined in order to supply CRYS dependent
 * implementation of Crypto API (declared in DxTzServiceCryptoAPI.h) for SW Platform.
 *
 * All functions will need USE_CRYS flag defined in order to call
 * CRYS functions, otherwise function will return DX_TZ_NOT_IMPLEMENTED.
 *
 * File defines following CRYS implementations for API according in DxTzServiceCryptoAPI.h:
 * Random generation
 * AES Create/Ternimate Context
 * CTR - (Ex functions defined platform dependan in DxTzServiceCryptoAPI.c platform)
 * CBC - (Ex functions defined platform dependan in DxTzServiceCryptoAPI.c platform)
 * ECB
 * SHA1
 * SHA256
 * MD5
 * HMAC SHA256
 */



//------------------------------------  Random generation -------------------------------------
#if 0
void    printf_data(DxUint8* data, DxUint32 size)
{
    DxUint32    i;

    sw_printf("\n***** Data Start, size [%d] : ******\n", size);
    for(i=0;i<size;i++)
    {
        sw_printf("%02x ", data[i]);
    }
    sw_printf("\n***** Data End ******\n");
}

void    printf_key(DxUint8* key, DxUint32 size)
{
    DxUint32    i;

    sw_printf("\n***** Key Start: ******\n");
    for(i=0;i<size;i++)
    {
        sw_printf("%02x ", key[i]);
    }
    sw_printf("\n***** Key End ******\n");
}

void    printf_iv(DxUint8* iv, DxUint32 size, DxBool bIn)
{
    DxUint32    i;

    sw_printf("\n***** IV %s Start: ******\n", bIn?"In":"Out");
    for(i=0;i<size;i++)
    {
        sw_printf("%02x ", iv[i]);
    }
    sw_printf("\n***** IV %s End: ******\n", bIn?"In":"Out");
}

void    printf_result(DxUint8* src, DxUint8* dst, DxUint32 size)
{
    DxUint32    i;

    sw_printf("\n***** Source data Start: ******\n");
    for(i=0;i<size;i++)
    {
        sw_printf("%02x ", src[i]);
    }
    sw_printf("\n***** Source data End ******\n");

    sw_printf("\n***** Dest data Start: ******\n");
    for(i=0;i<size;i++)
    {
        sw_printf("%02x ", dst[i]);
    }
    sw_printf("\n***** Dest data End ******\n\n");
}
#endif

DxStatus DxTzService_RandomGenerate(DxUint8* buffer,DxUint32 length)
{
    DxInt32 ret = DX_SUCCESS;
    DxUint32 u32Rnd = 0;
    DxUint32 u32TmpLen = 0;

    if((buffer == DX_NULL )||(length == 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter\n");
        return DX_BAD_ARGUMENTS;
    }

    while(length > 0)
    {
        ret = __Cipher_GetRandomNumber((HI_U32 *)&u32Rnd);
        if(ret != HI_SUCCESS)
        {
            DxHwLogError(DX_FALSE, "Get random number failure\n");
            return DX_FAILURE;
        }
        if(length >= sizeof(u32Rnd))
        {
            u32TmpLen = sizeof(u32Rnd);
        }
        else
        {
            u32TmpLen = length;
        }

        DxTzService_MemCpy(buffer, &u32Rnd, u32TmpLen);
        length -= u32TmpLen;
        buffer += u32TmpLen;
    }
    return DX_SUCCESS;
}

//------------------------------------  AES Create/Terminate Context ----------------------------

DxStatus DxTzService_AES128_CreateContext(DxCipher_AES128_Context_t *ctx)
{
    DxInt32 ret = DX_SUCCESS;

    if((DxBool)(*ctx) == DX_TRUE)
    {
        return DX_ALREADY_INITIALIZED;
    }

#if 0
    *ctx = (DxCipher_AES128_Context_t)DX_FALSE;
    ret = __Cipher_Init();
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_Init failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
#endif

    *ctx = (DxCipher_AES128_Context_t)DX_TRUE;
    return DX_SUCCESS;
}

DxStatus DxTzService_AES128_TerminateContext(DxCipher_AES128_Context_t* ctx)
{
    if((DxBool)(*ctx) == DX_FALSE)
    {
        return DX_NOT_INITIALIZED;
    }

//    Cipher_Exit();
    *ctx = (DxCipher_AES128_Context_t)DX_FALSE;
    return DX_SUCCESS;
}




//------------------------------------  CTR ----------------------------


DxStatus DxTzService_AES128CTR_Init(DxCipher_AES128CTR_Context_t *ctx,
                                    DxCipher_AES128_Context_t internalCtx,
                                    const DxUint8 *pKey,
                                    DxUint32 key_len,
                                    EDxCipherDirection direction)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hCipher = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;

    if((DxBool)internalCtx == DX_FALSE)
    {
        DxHwLogError(DX_FALSE, "Cipher is not initialed\n");
        return DX_NOT_INITIALIZED;
    }

    if((ctx == DX_NULL) || (pKey == DX_NULL )||(key_len != 16))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter.\n");
        return DX_BAD_ARGUMENTS;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    ret = __Cipher_CreateHandle(&hCipher, &stCipherAttr);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_CreateHandle failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    else
    {
        DxHwLogTrace(DX_FALSE, "Cipher_CreateHandle success, cipher handle is =0x%x\n", hCipher);
    }

    DxTzService_MemSet(&stCipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));

    DxTzService_MemCpy(stCipherCtrl.u32Key, (void *)pKey,16);

    stCipherCtrl.bKeyByCA = HI_FALSE;
    stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CTR;
    stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;

    ret = __Cipher_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        __Cipher_DestroyHandle(hCipher);
        DxHwLogTrace(DX_FALSE, "Cipher_ConfigHandle failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    *ctx = (DxCipher_AES128CTR_Context_t) hCipher;

    return DX_SUCCESS;
}

DxStatus DxTzService_AES128CTR_DecryptData(DxCipher_AES128CTR_Context_t ctx,
                                           const void *pSrc,
                                           void *pDst,
                                           DxUint32 dataSize,
                                           /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hCipher = (HI_HANDLE)ctx;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;

    DxUint32 u32TempLen, u32TotalSize = dataSize;


    if((pSrc == DX_NULL) || (pDst == DX_NULL) || (dataSize==0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter.\n");
        return DX_BAD_ARGUMENTS;
    }

    ret = __Cipher_GetHandleConfig(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Get cipher config failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    DxTzService_MemCpy(stCipherCtrl.u32IV, iv, DX_TZ_AES128_IV_SIZE);
    DxTzService_MemSet(&stCipherCtrl.stChangeFlags, 0, sizeof(HI_UNF_CIPHER_CTRL_CHANGE_FLAG_S));
    stCipherCtrl.stChangeFlags.bit1IV = 1;

    ret = __Cipher_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Cipher_ConfigHandle failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    while(dataSize > 0)
    {
        if(dataSize > SECURE_MEM_CIPHER_MAX_SIZE)
        {
            u32TempLen = SECURE_MEM_CIPHER_MAX_SIZE;
        }
        else
        {
            u32TempLen = dataSize;
        }
        ret = __Cipher_Decrypt(hCipher, (HI_U32)pSrc, (HI_U32)pDst, u32TempLen);

        if(ret != HI_SUCCESS)
        {
            DxHwLogTrace(DX_FALSE, "Cipher_Decrypt failure, ret=0x%x\n", ret);
            return DX_FAILURE;
        }
        dataSize -= u32TempLen;
        pSrc += u32TempLen;
        pDst += u32TempLen;
    }

#if 0
    ret = __Cipher_GetIVOut(hCipher, iv);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Cipher_GetIVOut failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
#else
    {
        DxUint32    u32Counter = 0;
        DxTzService_MemCpyReverse(&u32Counter, &iv[12], 4);
        u32Counter += ((u32TotalSize+DX_TZ_AES128_BLOCK_SIZE-1)/DX_TZ_AES128_BLOCK_SIZE);
        DxTzService_MemCpyReverse(&iv[12], &u32Counter, 4);
    }
#endif

    return DX_SUCCESS;
}

DxStatus DxTzService_AES128CTR_EncryptData(DxCipher_AES128CTR_Context_t ctx,
                                           const void *pSrc,
                                           void *pDst,
                                           DxUint32 dataSize,
                                           /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hCipher = (HI_HANDLE)ctx;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    /*DxUint32 u32SrcPhyAddr = SECURE_MEM_CIPHER_SRC_PHY;
    DxUint32 u32SrcVirAddr = SECURE_MEM_CIPHER_SRC;
    DxUint32 u32DestPhyAddr = SECURE_MEM_CIPHER_DEST_PHY;
    DxUint32 u32DestVirAddr = SECURE_MEM_CIPHER_DEST;*/
    DxUint32 u32TempLen, u32TotalSize = dataSize;

    if((pSrc == DX_NULL) || (pDst == DX_NULL) || (dataSize==0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter.\n");
        return DX_BAD_ARGUMENTS;
    }

    ret = __Cipher_GetHandleConfig(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Get cipher config failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    DxTzService_MemCpy(stCipherCtrl.u32IV, iv, DX_TZ_AES128_IV_SIZE);
    DxTzService_MemSet(&stCipherCtrl.stChangeFlags, 0, sizeof(HI_UNF_CIPHER_CTRL_CHANGE_FLAG_S));
    stCipherCtrl.stChangeFlags.bit1IV = 1;

    ret = __Cipher_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Cipher_ConfigHandle failure, ret=0x%x\n", ret);
        return DX_FAILURE;
    }

    while(dataSize > 0)
    {
        if(dataSize > SECURE_MEM_CIPHER_MAX_SIZE)
        {
            u32TempLen = SECURE_MEM_CIPHER_MAX_SIZE;
        }
        else
        {
            u32TempLen = dataSize;
        }
        //DxTzService_MemCpy((void *)u32SrcVirAddr, (void *)pSrc, u32TempLen);
        //ret = __Cipher_Encrypt(hCipher, (void *)pSrc, (void *)pDst, ((u32TempLen+DX_TZ_AES128_BLOCK_SIZE-1)/DX_TZ_AES128_BLOCK_SIZE)*DX_TZ_AES128_BLOCK_SIZE);
        ret = __Cipher_Encrypt(hCipher, (HI_U32)pSrc, (HI_U32)pDst, u32TempLen);
        if(ret != HI_SUCCESS)
        {
            DxHwLogTrace(DX_FALSE, "Cipher_Encrypt failure, ret=%d\n", ret);
            return DX_FAILURE;
        }
        //DxTzService_MemCpy(pDst, (void *) u32DestVirAddr, u32TempLen);

        dataSize -= u32TempLen;
        pSrc += u32TempLen;
        pDst += u32TempLen;
    }

#if 0
    ret = __Cipher_GetIVOut(hCipher, iv);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Cipher_GetIVOut failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
#else
    {
        DxUint32    u32Counter = 0;
        DxTzService_MemCpyReverse(&u32Counter, &iv[12], 4);
        u32Counter += ((u32TotalSize+DX_TZ_AES128_BLOCK_SIZE-1)/DX_TZ_AES128_BLOCK_SIZE);
        DxTzService_MemCpyReverse(&iv[12], &u32Counter, 4);
    }
#endif

    return DX_SUCCESS;
}


DxStatus DxTzService_AES128CTR_Finish(DxCipher_AES128CTR_Context_t *ctx)
{
    DxStatus ret = DX_SUCCESS;
    if(ctx == DX_NULL )
    {
        DxHwLogError(DX_FALSE, "Null pointer\n");
        return DX_FAILURE;
    }

    ret = __Cipher_DestroyHandle((HI_HANDLE)(*ctx));
    return ret;
}


//----------------- CTR Ex functions ----------------------------------------------------


static DxStatus DxTzService_AES128CTR_EncryptDecryptDataEx(DxCipher_AES128CTR_Context_t ctx,
                                                           DxTzServiceSharedMemRef *pSrc,
                                                           DxUint32 srcOffset,
                                                           DxTzServiceSharedMemRef *pDest,
                                                           DxUint32 destOffset,
                                                           DxUint32 dataSize,
                                                           /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE],
                                                           DxBool toEncrypt)
{
    DxUint32 srcSize, destSize;
    const DxByte *srcBuffP;
    DxByte *destBuffP;

    if(pDest==DX_NULL || pSrc==DX_NULL)
    {
        DxHwLogError(DX_FALSE, "DxTzService_MemCpyEx failed: pDest=0x%X, pSrc=0x%X",pDest, pSrc);
        return DX_BAD_ARGUMENTS;
    }
    srcSize = pSrc->nSize;
    destSize = pDest->nSize;
    if(pDest->handle1==DX_NULL || pSrc->handle1==DX_NULL || srcSize<dataSize+srcOffset || destSize<dataSize+destOffset)
    {
        DxHwLogError(DX_FALSE, "%s failed: bad arguments :pDest->handle1=0x%X, destSize=%d, destOffset=%d, pSrc->handle1=0x%X, srcSize=%d, srcOffset=%d, dataSize=%d",__FUNCTION__,
            pDest->handle1, destSize, destOffset, pSrc->handle1, srcSize, srcOffset, dataSize);
        return DX_BAD_ARGUMENTS;
    }

    srcBuffP = ((DxByte *)pSrc->handle1) + (pSrc->offset+srcOffset);
    destBuffP = ((DxByte *)pDest->handle1) + (pDest->offset+destOffset);

    if(toEncrypt)
        return DxTzService_AES128CTR_EncryptData(ctx, srcBuffP, destBuffP, dataSize, iv);
    else
        return DxTzService_AES128CTR_DecryptData(ctx, srcBuffP, destBuffP, dataSize, iv);
}

DxStatus DxTzService_AES128CTR_DecryptDataEx(DxCipher_AES128CTR_Context_t ctx,
                                             DxTzServiceSharedMemRef *pSrc,
                                             DxUint32 srcOffset,
                                             DxTzServiceSharedMemRef *pDest,
                                             DxUint32 destOffset,
                                             DxUint32 dataSize,
                                             /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{
    return DxTzService_AES128CTR_EncryptDecryptDataEx(ctx, pSrc, srcOffset, pDest, destOffset, dataSize, iv, DX_FALSE);
}

DxStatus DxTzService_AES128CTR_EncryptDataEx(DxCipher_AES128CTR_Context_t ctx,
                                             DxTzServiceSharedMemRef *pSrc,
                                             DxUint32 srcOffset,
                                             DxTzServiceSharedMemRef *pDst,
                                             DxUint32 destOffset,
                                             DxUint32 dataSize,
                                             /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{
    return DxTzService_AES128CTR_EncryptDecryptDataEx(ctx, pSrc, srcOffset, pDst, destOffset, dataSize, iv, DX_TRUE);
}








//------------------------------------  CBC ----------------------------


DxStatus DxTzService_AES128CBC_Init(DxCipher_AES128CBC_Context_t *ctx,
                                    DxCipher_AES128_Context_t internalCtx,
                                    const DxUint8 *pKey,
                                    DxUint32 key_len,
                                    EDxCipherDirection direction)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hCipher = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;

    if((DxBool)internalCtx == DX_FALSE)
    {
        DxHwLogError(DX_FALSE, "Cipher is not initialed\n");
        return DX_NOT_INITIALIZED;
    }

    if((ctx == DX_NULL) || (pKey == DX_NULL )||(key_len != 16))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter.\n");
        return DX_BAD_ARGUMENTS;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    ret = __Cipher_CreateHandle(&hCipher, &stCipherAttr);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_CreateHandle failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    else
    {
        DxHwLogTrace(DX_FALSE, "Cipher_CreateHandle success, cipher handle is =0x%x\n", hCipher);
    }

    DxTzService_MemSet(&stCipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));

    DxTzService_MemCpy(stCipherCtrl.u32Key, (void *)pKey,16);

    stCipherCtrl.bKeyByCA = HI_FALSE;
    stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
    stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;

    ret = __Cipher_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        __Cipher_DestroyHandle(hCipher);
        DxHwLogTrace(DX_FALSE, "Cipher_ConfigHandle failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    *ctx = (DxCipher_AES128CBC_Context_t) hCipher;

    return DX_SUCCESS;
}


DxStatus DxTzService_AES128CBC_DecryptData(DxCipher_AES128CBC_Context_t ctx,
                                           const void *pSrc,
                                           void *pDst,
                                           DxUint32 dataSize,
                                           /*IN OUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hCipher = (HI_HANDLE)ctx;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    /*DxUint32 u32SrcPhyAddr = SECURE_MEM_CIPHER_SRC_PHY;
    DxUint32 u32SrcVirAddr = SECURE_MEM_CIPHER_SRC;
    DxUint32 u32DestPhyAddr = SECURE_MEM_CIPHER_DEST_PHY;
    DxUint32 u32DestVirAddr = SECURE_MEM_CIPHER_DEST;*/
    DxUint32 u32TempLen;

    if((pSrc == DX_NULL) || (pDst == DX_NULL )
        ||(dataSize==0)||((dataSize%DX_TZ_AES128_BLOCK_SIZE) != 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter.\n");
        return DX_BAD_ARGUMENTS;
    }

    ret = __Cipher_GetHandleConfig(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Get cipher config failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    DxTzService_MemCpy(stCipherCtrl.u32IV, iv, DX_TZ_AES128_IV_SIZE);
    DxTzService_MemSet(&stCipherCtrl.stChangeFlags, 0, sizeof(HI_UNF_CIPHER_CTRL_CHANGE_FLAG_S));
    stCipherCtrl.stChangeFlags.bit1IV = 1;

    ret = __Cipher_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Cipher_ConfigHandle failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    while(dataSize > 0)
    {
        if(dataSize > SECURE_MEM_CIPHER_MAX_SIZE)
        {
            u32TempLen = SECURE_MEM_CIPHER_MAX_SIZE;
        }
        else
        {
            u32TempLen = dataSize;
        }
        //DxTzService_MemCpy((void *)u32SrcVirAddr, (void *)pSrc, u32TempLen);
        ret = __Cipher_Decrypt(hCipher, (HI_U32)pSrc, (HI_U32)pDst, u32TempLen);
        if(ret != HI_SUCCESS)
        {
            DxHwLogTrace(DX_FALSE, "Cipher_Decrypt failure, ret=0x%x\n", ret);
            return DX_FAILURE;
        }
        //DxTzService_MemCpy(pDst, (void *) u32DestVirAddr, u32TempLen);

        dataSize -= u32TempLen;
        pSrc += u32TempLen;
        pDst += u32TempLen;
    }

#if 0
    ret = __Cipher_GetIVOut(hCipher, iv);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Cipher_GetIVOut failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
#else
    DxTzService_MemCpy((DxUint8 *)iv, (DxUint8 *)pSrc-DX_TZ_AES128_IV_SIZE, DX_TZ_AES128_IV_SIZE);
#endif

    return DX_SUCCESS;
}


DxStatus DxTzService_AES128CBC_EncryptData(DxCipher_AES128CBC_Context_t ctx,
                                           const void *pSrc,
                                           void *pDst,
                                           DxUint32 dataSize,
                                           /*IN OUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hCipher = (HI_HANDLE)ctx;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    /*DxUint32 u32SrcPhyAddr = SECURE_MEM_CIPHER_SRC_PHY;
    DxUint32 u32SrcVirAddr = SECURE_MEM_CIPHER_SRC;
    DxUint32 u32DestPhyAddr = SECURE_MEM_CIPHER_DEST_PHY;
    DxUint32 u32DestVirAddr = SECURE_MEM_CIPHER_DEST;*/
    DxUint32 u32TempLen;

    if((pSrc == DX_NULL) || (pDst == DX_NULL )
        ||(dataSize==0)||((dataSize%DX_TZ_AES128_BLOCK_SIZE) != 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter.\n");
        return DX_BAD_ARGUMENTS;
    }

    ret = __Cipher_GetHandleConfig(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Get cipher config failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    DxTzService_MemCpy(stCipherCtrl.u32IV, iv, DX_TZ_AES128_IV_SIZE);
    DxTzService_MemSet(&stCipherCtrl.stChangeFlags, 0, sizeof(HI_UNF_CIPHER_CTRL_CHANGE_FLAG_S));
    stCipherCtrl.stChangeFlags.bit1IV = 1;

    ret = __Cipher_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Cipher_ConfigHandle failure, ret=0x%x\n", ret);
        return DX_FAILURE;
    }

    while(dataSize > 0)
    {
        if(dataSize > SECURE_MEM_CIPHER_MAX_SIZE)
        {
            u32TempLen = SECURE_MEM_CIPHER_MAX_SIZE;
        }
        else
        {
            u32TempLen = dataSize;
        }
        //DxTzService_MemCpy((void *)u32SrcVirAddr, (void *)pSrc, u32TempLen);
        ret = __Cipher_Encrypt(hCipher, (HI_U32)pSrc, (HI_U32)pDst, u32TempLen);
        if(ret != HI_SUCCESS)
        {
            DxHwLogTrace(DX_FALSE, "Cipher_Encrypt failure, ret=%d\n", ret);
            return DX_FAILURE;
        }
        //DxTzService_MemCpy(pDst, (void *) u32DestVirAddr, u32TempLen);

        dataSize -= u32TempLen;
        pSrc += u32TempLen;
        pDst += u32TempLen;
    }
#if 0
    ret = Cipher_GetIVOut(hCipher, iv);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Cipher_GetIVOut failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
#else
    DxTzService_MemCpy((DxUint8 *)iv, (DxUint8 *)pDst-DX_TZ_AES128_IV_SIZE, DX_TZ_AES128_IV_SIZE);
#endif

    return DX_SUCCESS;
}



DxStatus DxTzService_AES128CBC_Finish(DxCipher_AES128CBC_Context_t *ctx)
{
    DxStatus ret = DX_SUCCESS;
    if(ctx == DX_NULL )
    {
        DxHwLogError(DX_FALSE, "Null pointer\n");
        return DX_FAILURE;
    }

    ret = __Cipher_DestroyHandle((HI_HANDLE)(*ctx));
    return ret;
}




//----------------- CBC extended memory encrypt/decrypt functions  ----------------------


static DxStatus AES128CBC_ProcessDataEx (DxCipher_AES128CBC_Context_t  context,
                                         DxTzServiceSharedMemRef*      pSrc,
                                         DxUint32                      srcOffset,
                                         DxTzServiceSharedMemRef*      pDest,
                                         DxUint32                      destOffset,
                                         DxUint32                      dataSize,
                                         DxUint8       iv[DX_TZ_AES128_BLOCK_SIZE],
                                         DxStatus (*pf) (DxCipher_AES128CBC_Context_t,
                                                         const void*, void*, DxUint32, DxUint8*))
{
    const DxByte *srcBuffP;
    DxByte *destBuffP;

    /* Context pointer and object are inspected in the upper API function */
    if (DX_NULL == context || DX_NULL == pSrc || DX_NULL == pDest || DX_NULL == iv)
    {
        DxHwLogError(DX_TRUE, "bad arguments :pDest=0x%X, pSrc=0x%X",
                     pDest, pSrc);
        return DX_BAD_ARGUMENTS;
    }

    srcBuffP = ((DxByte *)pSrc->handle1) + (pSrc->offset+srcOffset);
    destBuffP = ((DxByte *)pDest->handle1) + (pDest->offset+destOffset);

    return (*pf) (context, srcBuffP, destBuffP, dataSize, iv);
}


DxStatus DxTzService_AES128CBC_DecryptDataEx (DxCipher_AES128CBC_Context_t  context,
                                              DxTzServiceSharedMemRef*      pSrc,
                                              DxUint32                      srcOffset,
                                              DxTzServiceSharedMemRef*      pDest,
                                              DxUint32                      destOffset,
                                              DxUint32                      dataSize,
                                              DxUint8       iv[DX_TZ_AES128_BLOCK_SIZE])
{
    if( (dataSize==0) || (dataSize%DX_TZ_AES128_BLOCK_SIZE !=0) )
    {
        DxHwLogError(DX_FALSE, "%s failed: bad arguments :dataSize=%d is not multiply of DX_TZ_AES128_BLOCK_SIZE", __FUNCTION__, dataSize);
        return DX_BAD_ARGUMENTS;
    }

    return AES128CBC_ProcessDataEx (context, pSrc, srcOffset, pDest, destOffset, dataSize,
                                    iv, DxTzService_AES128CBC_DecryptData);
}


DxStatus DxTzService_AES128CBC_EncryptDataEx (DxCipher_AES128CBC_Context_t  context,
                                              DxTzServiceSharedMemRef*      pSrc,
                                              DxUint32                      srcOffset,
                                              DxTzServiceSharedMemRef*      pDest,
                                              DxUint32                      destOffset,
                                              DxUint32                      dataSize,
                                              DxUint8       iv[DX_TZ_AES128_BLOCK_SIZE])
{
    if( (dataSize==0) || (dataSize%DX_TZ_AES128_BLOCK_SIZE !=0) )
    {
        DxHwLogError(DX_FALSE, "%s failed: bad arguments :dataSize=%d is not multiply of DX_TZ_AES128_BLOCK_SIZE", __FUNCTION__, dataSize);
        return DX_BAD_ARGUMENTS;
    }

    return AES128CBC_ProcessDataEx (context, pSrc, srcOffset, pDest, destOffset, dataSize,
                                    iv, DxTzService_AES128CBC_EncryptData);
}









//------------------------------------  ECB  ----------------------------




DxStatus DxTzService_AES128ECB_Init(DxCipher_AES128ECB_Context_t *ctx,
                                    DxCipher_AES128_Context_t internalCtx,
                                    const DxUint8 *pKey,
                                    DxUint32 key_len,
                                    EDxCipherDirection direction)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hCipher = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;

    QA_LOG_MSG("Start:\n");
    if((DxBool)internalCtx == DX_FALSE)
    {
        DxHwLogError(DX_FALSE, "Cipher is not initialed\n");
        return DX_NOT_INITIALIZED;
    }

    if((ctx == DX_NULL) || (pKey == DX_NULL )||(key_len != 16))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter.\n");
        return DX_BAD_ARGUMENTS;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    ret = __Cipher_CreateHandle(&hCipher, &stCipherAttr);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_CreateHandle failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    else
    {
        DxHwLogTrace(DX_FALSE, "Cipher_CreateHandle success, cipher handle is =0x%x\n", hCipher);
    }

    DxTzService_MemSet(&stCipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));

    //char g_HostKey[16] = {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf};
    DxTzService_MemCpy(stCipherCtrl.u32Key, (void *)pKey,16);
    //DxTzService_MemCpy(stCipherCtrl.u32Key, (void *)g_HostKey,16);

    stCipherCtrl.bKeyByCA = HI_FALSE;
    stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
    stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;

    ret = __Cipher_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        __Cipher_DestroyHandle(hCipher);
        DxHwLogTrace(DX_FALSE, "Cipher_ConfigHandle failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    QA_LOG_MSG("__Cipher_ConfigHandle ok\n");
    *ctx = (DxCipher_AES128ECB_Context_t) hCipher;
    return DX_SUCCESS;
}

DxStatus DxTzService_AES128ECB_DecryptData(DxCipher_AES128ECB_Context_t ctx,
                                           const void *pSrc,
                                           void *pDst,
                                           DxUint32 dataSize)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hCipher = (HI_HANDLE)ctx;
    /*DxUint32 u32SrcPhyAddr = SECURE_MEM_CIPHER_SRC_PHY;
    DxUint32 u32SrcVirAddr = SECURE_MEM_CIPHER_SRC;
    DxUint32 u32DestPhyAddr = SECURE_MEM_CIPHER_DEST_PHY;
    DxUint32 u32DestVirAddr = SECURE_MEM_CIPHER_DEST;*/
    DxUint32 u32TempLen;

    if((pSrc == DX_NULL) || (pDst == DX_NULL )
        ||(dataSize==0)||((dataSize%DX_TZ_AES128_BLOCK_SIZE) != 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter.\n");
        return DX_BAD_ARGUMENTS;
    }

#if 1
    while(dataSize > 0)
    {
        if(dataSize > SECURE_MEM_CIPHER_MAX_SIZE)
        {
            u32TempLen = SECURE_MEM_CIPHER_MAX_SIZE;
        }
        else
        {
            u32TempLen = dataSize;
        }
        //DxTzService_MemCpy((void *)u32SrcVirAddr, (void *)pSrc, u32TempLen);
        ret = __Cipher_Decrypt(hCipher, (HI_U32)pSrc, (HI_U32)pDst, u32TempLen);
        if(ret != HI_SUCCESS)
        {
            DxHwLogTrace(DX_FALSE, "Cipher_Decrypt failure, ret=0x%x\n", ret);
            return DX_FAILURE;
        }
        QA_LOG_MSG("__Cipher_Decrypt ok\n");
        //DxTzService_MemCpy(pDst, (void *) u32DestVirAddr, u32TempLen);
        dataSize -= u32TempLen;
        pSrc += u32TempLen;
        pDst += u32TempLen;
    }
#else
        ret = __Cipher_Decrypt(hCipher, (HI_U32)pSrc, (HI_U32)pDst, dataSize);
#endif

        if(ret != HI_SUCCESS)
        {
            DxHwLogTrace(DX_FALSE, "Cipher_Decrypt failure, ret=0x%x\n", ret);
            return DX_FAILURE;
        }
    return DX_SUCCESS;
}

DxStatus DxTzService_AES128ECB_EncryptData(DxCipher_AES128ECB_Context_t ctx,
                                           const void *pSrc,
                                           void *pDst,
                                           DxUint32 dataSize)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hCipher = (HI_HANDLE)ctx;
    /*DxUint32 u32SrcPhyAddr = SECURE_MEM_CIPHER_SRC_PHY;
    DxUint32 u32SrcVirAddr = SECURE_MEM_CIPHER_SRC;
    DxUint32 u32DestPhyAddr = SECURE_MEM_CIPHER_DEST_PHY;
    DxUint32 u32DestVirAddr = SECURE_MEM_CIPHER_DEST;*/
    DxUint32 u32TempLen;

    if((pSrc == DX_NULL) || (pDst == DX_NULL )
        ||(dataSize==0)||((dataSize%DX_TZ_AES128_BLOCK_SIZE) != 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameter.\n");
        return DX_BAD_ARGUMENTS;
    }

#if 1
    while(dataSize > 0)
    {
        if(dataSize > SECURE_MEM_CIPHER_MAX_SIZE)
        {
            u32TempLen = SECURE_MEM_CIPHER_MAX_SIZE;
        }
        else
        {
            u32TempLen = dataSize;
        }
        //DxTzService_MemCpy((void *)u32SrcVirAddr, (void *)pSrc, u32TempLen);
        ret = __Cipher_Encrypt(hCipher, (HI_U32)pSrc, (HI_U32) pDst, u32TempLen);
        //ret = __Cipher_Encrypt(hCipher, (HI_U32)g_PlainText, (HI_U32) pDst, u32TempLen);
        if(ret != HI_SUCCESS)
        {
            DxHwLogTrace(DX_FALSE, "Cipher_Encrypt failure, ret=0x%x\n", ret);
            return DX_FAILURE;
        }
        QA_LOG_MSG("__Cipher_Encrypt ok\n");
        //DxTzService_MemCpy(pDst, (void *) u32DestVirAddr, u32TempLen);
        dataSize -= u32TempLen;
        pSrc += u32TempLen;
        pDst += u32TempLen;
    }
#else
    ret = __Cipher_Encrypt(hCipher, (HI_U32)pSrc, (HI_U32)pDst, dataSize);
    if(ret != HI_SUCCESS)
    {
        DxHwLogTrace(DX_FALSE, "Cipher_Encrypt failure, ret=0x%x\n", ret);
        return DX_FAILURE;
    }

#endif

    return DX_SUCCESS;
}

DxStatus DxTzService_AES128ECB_Finish(DxCipher_AES128ECB_Context_t *ctx)
{
    DxStatus ret = DX_SUCCESS;
    if(ctx == DX_NULL )
    {
        DxHwLogError(DX_FALSE, "Null pointer\n");
        return DX_FAILURE;
    }

    ret = __Cipher_DestroyHandle((HI_HANDLE)(*ctx));
    QA_LOG_MSG("__Cipher_DestroyHandle ok\n");
    return ret;
}





//------------------------------------  SHA1 ------------------------------------------


DxStatus DxTzService_SHA1Init(DxTzSHA1Context_t* aContext)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

    if(aContext == DX_NULL)
    {
        DxHwLogError(DX_FALSE, "Null pointer.\n");
        return DX_BAD_ARGUMENTS;
    }

    DxTzService_MemSet(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA1;
    ret = __Cipher_HashInit(&stHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashInit failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    *aContext = (DxTzSHA1Context_t) hHash;

    return DX_SUCCESS;
}

DxStatus DxTzService_SHA1Update(DxTzSHA1Context_t aContext, const DxUint8 *aBuffer, DxUint32 aBufferLength)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = (HI_HANDLE)aContext;

    if((aBuffer == DX_NULL)||(aBufferLength == 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameters.\n");
        return DX_BAD_ARGUMENTS;
    }
    ret = __Cipher_HashUpdate(hHash, (HI_U8 *)aBuffer, aBufferLength);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashUpdate failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    return DX_SUCCESS;
}

DxStatus DxTzService_SHA1Final(DxTzSHA1Context_t aContext, DxUint8 aDigest[SHA1_SIGNATURE_SIZE])
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = (HI_HANDLE)aContext;

    ret = __Cipher_HashFinal(hHash, aDigest);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashFinal failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    return DX_SUCCESS;
}

DxStatus DxTzService_SHA1Terminate(DxTzSHA1Context_t aContext)
{
    return DX_SUCCESS;
}


//------------------------------------  SHA256 ----------------------------------------



DxStatus DxTzService_SHA256Init(DxTzSHA256Context_t* aContext)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

    if(aContext == DX_NULL)
    {
        DxHwLogError(DX_FALSE, "Null pointer.\n");
        return DX_BAD_ARGUMENTS;
    }

    DxTzService_MemSet(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
    ret = __Cipher_HashInit(&stHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashInit failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    *aContext = (DxTzSHA256Context_t) hHash;

    return DX_SUCCESS;
}

DxStatus DxTzService_SHA256Update(DxTzSHA256Context_t aContext, const DxUint8 *aBuffer, DxUint32 aBufferLength)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = (HI_HANDLE)aContext;

    if((aBuffer == DX_NULL)||(aBufferLength == 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameters.\n");
        return DX_BAD_ARGUMENTS;
    }

    ret = __Cipher_HashUpdate(hHash, (HI_U8 *)aBuffer, aBufferLength);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashUpdate failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    return DX_SUCCESS;
}

DxStatus DxTzService_SHA256Final(DxTzSHA256Context_t aContext, DxUint8 aDigest[SHA256_SIGNATURE_SIZE])
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = (HI_HANDLE)aContext;

    ret = __Cipher_HashFinal(hHash, aDigest);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashFinal failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    return DX_SUCCESS;
}

DxStatus DxTzService_SHA256Terminate(DxTzSHA256Context_t aContext)
{
    return DX_SUCCESS;
}




// ---------------------------- MD5 ----------------------------

DxStatus DxTzService_MD5Init(DxTzMD5Context_t *context)
{
#ifdef USE_CRYS
    return TzCrysImpl_MD5Init(context);
#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif
}

DxStatus DxTzService_MD5Update(DxTzMD5Context_t context, const DxUint8 *aBuffer, DxUint32 aBufferLength)
{
#ifdef USE_CRYS
    return TzCrysImpl_MD5Update(context,aBuffer,aBufferLength);
#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif
}

DxStatus DxTzService_MD5Final(DxTzMD5Context_t context, DxUint8 aDigest[MD5_SIGNATURE_SIZE])
{
#ifdef USE_CRYS
    return TzCrysImpl_MD5Final(context,aDigest);
#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif
}

DxStatus DxTzService_MD5Terminate(DxTzMD5Context_t context)
{
#ifdef USE_CRYS
    return TzCrysImpl_MD5Terminate(context);
#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif
}




//------------------------------------  HMAC SHA256 -------------------------------------
#define HMAC_BLOCK_SIZE_SHA256     64
static DxUint8 hmac_key[HMAC_BLOCK_SIZE_SHA256];

DxStatus HMAC_Key_Initial(const DxUint8 *pKey, DxUint32 key_len, DxUint8 hmac_key[HMAC_BLOCK_SIZE_SHA256])
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

    if((pKey == DX_NULL)||(hmac_key == DX_NULL)||(key_len == 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameters.\n");
        return DX_BAD_ARGUMENTS;
    }
    DxTzService_MemSet(hmac_key, 0, HMAC_BLOCK_SIZE_SHA256);

    /*key length is less than 64bytes, copy directly*/
    if(key_len <= HMAC_BLOCK_SIZE_SHA256)
    {
        DxTzService_MemCpy(hmac_key, pKey, key_len);
        return DX_SUCCESS;
    }

    /*key length more than 64bytes, calcute the hash result*/
    DxTzService_MemSet(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
    ret = __Cipher_HashInit(&stHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashInit failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    ret = __Cipher_HashUpdate(hHash, (HI_U8 *)pKey, key_len);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashUpdate failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    ret = __Cipher_HashFinal(hHash, hmac_key);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashFinal failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    return DX_SUCCESS;
}

DxStatus DxTzService_HMAC_SHA256Init(DxTzHMAC_SHA256Context_t *context,
                                 const DxUint8 *pKey,
                                 DxUint32 key_len)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = 0;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    DxUint8  i_key_pad[HMAC_BLOCK_SIZE_SHA256];
    DxUint32 i;

    if((context == DX_NULL)||(pKey == DX_NULL)||(key_len == 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameters.\n");
        return DX_BAD_ARGUMENTS;
    }

    /*Initial hmac key*/
    ret = HMAC_Key_Initial(pKey, key_len, hmac_key);
    if(ret != DX_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "HMAC_Key_Initial failure.\n");
        return DX_FAILURE;
    }

    /*hash i_key_pad+message start*/
    DxTzService_MemSet(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
    ret = __Cipher_HashInit(&stHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashInit failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    /*generate i_key_pad*/
    DxTzService_MemSet(i_key_pad, 0x36, HMAC_BLOCK_SIZE_SHA256);
    for(i=0;i<HMAC_BLOCK_SIZE_SHA256;i++)
    {
        i_key_pad[i] = i_key_pad[i] ^ hmac_key[i];
    }

    /*hash i_key_pad*/
    ret = __Cipher_HashUpdate(hHash, (HI_U8 *)i_key_pad, HMAC_BLOCK_SIZE_SHA256);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashUpdate failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    *context = (DxTzHMAC_SHA256Context_t) hHash;

    return DX_SUCCESS;
}

DxStatus DxTzService_HMAC_SHA256Update(DxTzHMAC_SHA256Context_t context,
                                   const DxUint8 *data,
                                   DxUint32 datLength)
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = (HI_HANDLE)context;

    if((data == DX_NULL)||(datLength == 0))
    {
        DxHwLogError(DX_FALSE, "Invalid parameters.\n");
        return DX_BAD_ARGUMENTS;
    }

    ret = __Cipher_HashUpdate(hHash, (HI_U8 *)data, datLength);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashUpdate failure, ret=%d\n", ret);
        return DX_FAILURE;
    }
    return DX_SUCCESS;
}

DxStatus DxTzService_HMAC_SHA256Final(DxTzHMAC_SHA256Context_t context,
                                  DxUint8 aDigest[SHA256_SIGNATURE_SIZE])
{
    DxInt32 ret = DX_SUCCESS;
    HI_HANDLE hHash = (HI_HANDLE)context;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    DxUint8 hash_sum_1[SHA256_SIGNATURE_SIZE];
    DxUint8  o_key_pad[HMAC_BLOCK_SIZE_SHA256];
    DxUint32 i;

    /*hash i_key_pad+message finished*/
    DxTzService_MemSet(hash_sum_1, 0, SHA256_SIGNATURE_SIZE);
    ret = __Cipher_HashFinal(hHash, hash_sum_1);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashFinal failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    /*generate o_key_pad*/
    DxTzService_MemSet(o_key_pad, 0x5c, HMAC_BLOCK_SIZE_SHA256);
    for(i=0;i<HMAC_BLOCK_SIZE_SHA256;i++)
    {
        o_key_pad[i] = o_key_pad[i] ^ hmac_key[i];
    }

    /*hash o_key_pad+hash_sum_1 start*/
    DxTzService_MemSet(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
    ret = __Cipher_HashInit(&stHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashInit failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    /*hash o_key_pad*/
    ret = __Cipher_HashUpdate(hHash, (HI_U8 *)o_key_pad, HMAC_BLOCK_SIZE_SHA256);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashUpdate failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    /*hash hash_sum_1*/
    ret = __Cipher_HashUpdate(hHash, (HI_U8 *)hash_sum_1, SHA256_SIGNATURE_SIZE);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashUpdate failure, ret=%d\n", ret);
        return DX_FAILURE;
    }

    /*hash o_key_pad+hash_sum_1 finished*/
    ret = __Cipher_HashFinal(hHash, aDigest);
    if(ret != HI_SUCCESS)
    {
        DxHwLogError(DX_FALSE, "Cipher_HashFinal failure, ret=%d\n", ret);
        return DX_FAILURE;
    }


    return DX_SUCCESS;
}

DxStatus DxTzService_HMAC_SHA256Terminate(DxTzHMAC_SHA256Context_t context)
{
    return DX_SUCCESS;
}








//------------------------------------  RSA -------------------------------------


DxStatus DxTzService_RSA_OAEP_DecryptData(DxTzService_RSA_PrivKey_s *privKey_ptr,
                                      EDxTzGenericRsaHashOpMode_t   hashFunc,
                                      DxByte    *DataIn_ptr,
                                      DxUint16  DataInSize,
                                      DxByte    *Output_ptr,
                                      DxUint16  *OutputSize)
{
#ifdef USE_CRYS
    return TzCrysImpl_RSA_OAEP_DecryptData(privKey_ptr,hashFunc,DataIn_ptr,DataInSize,Output_ptr,OutputSize);
#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif
}


DxStatus DxTzService_RSA_OAEP_EncryptData(DxTzService_RSA_PubKey_s *pubKey_ptr,
                                      EDxTzGenericRsaHashOpMode_t   hashFunc,
                                      DxByte    *DataIn_ptr,
                                      DxUint16  DataInSize,
                                      DxByte    *Output_ptr)
{
#ifdef USE_CRYS

    void* rngState = DxTzService_GetCrysRndState();


    if (rngState != DX_NULL)
    {
        return TzCrysImpl_RSA_OAEP_EncryptData(pubKey_ptr,
            hashFunc,
            DataIn_ptr,
            DataInSize,
            Output_ptr,
            rngState);
    }
    else
    {
        DxHwLogError(DX_FALSE, "%s: rngState was not initialized",__FUNCTION__);
        return DX_TZ_BAD_STATE;
    }

#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif



}



DxStatus DxTzService_RSA_PKCS1v15_DecryptData(DxTzService_RSA_PrivKey_s *privKey_ptr,
                                      DxByte                        *DataIn_ptr,
                                      DxUint16                      DataInSize,
                                      DxByte                        *Output_ptr,
                                      DxUint16                      *OutputSize)
{
#ifdef USE_CRYS
    return TzCrysImpl_RSA_PKCS1v15_DecryptData(privKey_ptr,DataIn_ptr,DataInSize,Output_ptr,OutputSize);
#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif
}



DxStatus DxTzService_RSA_PKCS1v15_EncryptData(DxTzService_RSA_PubKey_s *pubKey_ptr,
                                      DxByte                        *DataIn_ptr,
                                      DxUint16                      DataInSize,
                                      DxByte                        *Output_ptr)
{
#ifdef USE_CRYS

    void* rngState = DxTzService_GetCrysRndState();

    if (rngState != DX_NULL)
    {
        return TzCrysImpl_RSA_PKCS1v15_EncryptData(pubKey_ptr,DataIn_ptr,DataInSize,Output_ptr,rngState);
    }
    else
    {
        DxHwLogError(DX_FALSE, "%s: rngState was not initialized",__FUNCTION__);
        return DX_TZ_BAD_STATE;
    }



#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif
}



DxStatus DxTzService_RSA_PSS_VerifyDataSignature(DxTzService_RSA_PubKey_s *pubKey_ptr,
                                         EDxTzGenericRsaHashOpMode_t    hashFunc,
                                         DxUint16                       saltLen,
                                         DxByte                         *DataIn_ptr,
                                         DxUint32                       DataInSize,
                                         DxByte                         *Sig_ptr)
{
#ifdef USE_CRYS
    return TzCrysImpl_RSA_PSS_VerifyDataSignature(pubKey_ptr,hashFunc,saltLen,DataIn_ptr,DataInSize,Sig_ptr);
#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif
}




DxStatus DxTzService_RSA_PKCS1v15_VerifyDataSignature(DxTzService_RSA_PubKey_s *pubKey_ptr,
                                         EDxTzGenericRsaHashOpMode_t    hashFunc,
                                         DxByte                         *DataIn_ptr,
                                         DxUint32                       DataInSize,
                                         DxByte                         *Sig_ptr)
{
#ifdef USE_CRYS
    return TzCrysImpl_RSA_PKCS1v15_VerifyDataSignature(pubKey_ptr,hashFunc,DataIn_ptr,DataInSize,Sig_ptr);
#else
    return DX_TZ_NOT_IMPLEMENTED;
#endif
}

#if 0
HI_S32 Dx_Sample_Cipher(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;
    static HI_HANDLE hCipher = 0;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    HI_U32 i, value;
    HI_U8 g_PlainText[16] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
    HI_U8 g_HostKey[16] = {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf};
    HI_U8 g_EncData[16] = {0xd1,0x17,0xbd,0x63,0x73,0x54,0x9f,0xaa,0x2c,0xa9,0x72,0xdf,0xfa,0x10,0x11,0x4d};
    /*HI_U8 *pu8VirSrc = (HI_U8 *)SECURE_MEM_CIPHER_SRC;
    HI_U8 *pu8VirDst = (HI_U8 *)SECURE_MEM_CIPHER_DEST;
    HI_U8 *pu8PhySrc = (HI_U8 *)SECURE_MEM_CIPHER_SRC_PHY;
    HI_U8 *pu8PhyDst = (HI_U8 *)SECURE_MEM_CIPHER_DEST_PHY;*/
    HI_U8 pu8VirSrc[16];
    HI_U8 pu8VirDst[16];
    HI_U8 pu8PhySrc[16];
    HI_U8 pu8PhyDst[16];

    HI_UNF_CIPHER_ATTS_S    stCipherAttr;

    QA_LOG_MSG("\n***************  Cipher test Start *****************\n");
    ret = __Cipher_Init();
    if(ret != HI_SUCCESS)
    {
        QA_LOG_MSG("Cipher_Init failure, ret=%d\n", ret);
        return HI_FAILURE;
    }
    memset(&stCipherAttr, 0, sizeof(HI_UNF_CIPHER_ATTS_S));
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    ret = __Cipher_CreateHandle(&hCipher, &stCipherAttr);
    if(ret != HI_SUCCESS)
    {
        QA_LOG_MSG("Cipher_CreateHandle failure, ret=%d\n", ret);
        goto __Exit;
    }
    else
    {
        QA_LOG_MSG("Cipher_CreateHandle success, cipher handle is =0x%x\n", hCipher);
    }

    memset(&stCipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));

    memcpy(stCipherCtrl.u32Key,g_HostKey,16);
#if 0
    stCipherCtrl.bKeyByCA = HI_FALSE;
    stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
    stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
    stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
#else
    stCipherCtrl.bKeyByCA = HI_FALSE;
    stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
    stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
#endif
    ret = __Cipher_ConfigHandle(hCipher, &stCipherCtrl);
    if(ret != HI_SUCCESS)
    {
        QA_LOG_MSG("Cipher_ConfigHandle failure, ret=%d\n", ret);
        goto __Destroy;
    }

    memcpy(pu8VirSrc, g_PlainText, sizeof(g_PlainText));
    memset(pu8VirDst, 0, sizeof(g_PlainText));

    QA_LOG_MSG("\nPlain  data is :\n");
    for(i=0;i<16;i++)
    {
        QA_LOG_MSG("%x ",pu8VirSrc[i]);
    }
    QA_LOG_MSG("\n");

    ret = __Cipher_Encrypt(hCipher, (HI_U32)pu8PhySrc, (HI_U32)pu8PhyDst, sizeof(g_PlainText));
    if(ret != HI_SUCCESS)
    {
        QA_LOG_MSG("Cipher_Encrypt failure, ret=%d\n", ret);
        goto __Destroy;
    }
    /*
    {
        sw_printf("\nEncrypted data is :\n");
        for(i=0;i<16;i++)
        {
            sw_printf("%x ",pu8VirDst[i]);
        }
        sw_printf("\n");

        if(0 == sw_memcmp(pu8VirDst, g_EncData, sizeof(g_PlainText)))
        {
            sw_printf("\nEncrypt data SUCCESS\n");
        }
        else
        {
            sw_printf("\nEncrypt data failed,  should be:\n");
            for(i=0;i<16;i++)
            {
                sw_printf("%x ",g_EncData[i]);
            }
            sw_printf("\n");
        }

    }*/
    //add for AES128 ECB test y00201671
    memcpy(g_EncData, pu8PhyDst, sizeof(g_EncData));
#if 1
    memcpy(pu8VirSrc, g_EncData, sizeof(g_EncData));
    memset(pu8VirDst, 0, sizeof(g_EncData));
    ret = __Cipher_Decrypt(hCipher, (HI_U32)pu8VirSrc, (HI_U32)pu8VirDst, sizeof(g_EncData));
    if(ret != HI_SUCCESS)
    {
        QA_LOG_MSG("Cipher_Decrypt failure, ret=%d\n", ret);
        goto __Destroy;
    }

    QA_LOG_MSG("\nDecrypted data is :\n");
    for(i=0;i<16;i++)
    {
        QA_LOG_MSG("%x ",pu8VirDst[i]);
    }
    QA_LOG_MSG("\n");
#endif

//    sw_printf("\n***************  Cipher test End *****************\n");
//    return ret;

__Destroy:
    if(0 != hCipher)
    {
        __Cipher_DestroyHandle(hCipher);
        hCipher = 0;
    }
__Exit:
    __Cipher_Exit();
    //CIPHER_USLEEP(10*1000);
    QA_LOG_MSG("\n***************  Cipher test End *****************\n");
    return ret;
}
#endif

#else
#include "DxTzServiceCryptoAPI.h"

#if 0
DxStatus DxTzService_RandomGenerate(DxUint8* buffer, DxUint32 length)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128_CreateContext(DxCipher_AES128_Context_t *ctx)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128_TerminateContext(DxCipher_AES128_Context_t* ctx)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128CTR_Init(DxCipher_AES128CTR_Context_t *ctx,
									DxCipher_AES128_Context_t internalCtx,
									const DxUint8 *pKey,
									DxUint32 key_len,
									EDxCipherDirection direction)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128CTR_DecryptData(DxCipher_AES128CTR_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128CTR_EncryptData(DxCipher_AES128CTR_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{return DX_TZ_FAILURE;}
#endif

DxStatus DxTzService_AES128CTR_DecryptDataEx(DxCipher_AES128CTR_Context_t ctx,
										   DxTzServiceSharedMemRef *pSrc,
										   DxUint32 srcOffset,
										   DxTzServiceSharedMemRef *pDst,
										   DxUint32 dstOffset,
										   DxUint32 dataSize,
    									   /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128CTR_EncryptDataEx(DxCipher_AES128CTR_Context_t ctx,
										   DxTzServiceSharedMemRef *pSrc,
										   DxUint32 srcOffset,
										   DxTzServiceSharedMemRef *pDst,
										   DxUint32 dstOffset,
										   DxUint32 dataSize,
											/*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{return DX_TZ_FAILURE;}

#if 0
DxStatus DxTzService_AES128CTR_Finish(DxCipher_AES128CTR_Context_t *ctx)
{return DX_TZ_FAILURE;}
#endif

DxStatus DxTzService_AES128CBC_Init(DxCipher_AES128CBC_Context_t *ctx,
									DxCipher_AES128_Context_t internalCtx,
									const DxUint8 *pKey,
									DxUint32 key_len,
									EDxCipherDirection direction)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128CBC_DecryptData(DxCipher_AES128CBC_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*IN OUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128CBC_EncryptData(DxCipher_AES128CBC_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*IN OUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128CBC_DecryptDataEx (DxCipher_AES128CBC_Context_t  context,
											  DxTzServiceSharedMemRef*      pSrc,
											  DxUint32                      srcOffset,
											  DxTzServiceSharedMemRef*      pDest,
											  DxUint32                      destOffset,
											  DxUint32                      dataSize,
											  /*INOUT*/ DxUint8       iv[DX_TZ_AES128_BLOCK_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128CBC_EncryptDataEx (DxCipher_AES128CBC_Context_t  context,
											  DxTzServiceSharedMemRef*      pSrc,
											  DxUint32                      srcOffset,
											  DxTzServiceSharedMemRef*      pDest,
											  DxUint32                      destOffset,
											  DxUint32                      dataSize,
											  /*INOUT*/ DxUint8       iv[DX_TZ_AES128_BLOCK_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128CBC_Finish(DxCipher_AES128CBC_Context_t *ctx)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128ECB_Init(DxCipher_AES128ECB_Context_t *ctx,
									DxCipher_AES128_Context_t internalCtx,
									const DxUint8 *pKey,
									DxUint32 key_len,
									EDxCipherDirection direction)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128ECB_DecryptData(DxCipher_AES128ECB_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128ECB_EncryptData(DxCipher_AES128ECB_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_AES128ECB_Finish(DxCipher_AES128ECB_Context_t *ctx)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_SHA1Init(DxTzSHA1Context_t* aContext)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_SHA1Update(DxTzSHA1Context_t aContext, const DxUint8 *aBuffer, DxUint32 aBufferLength)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_SHA1Final(DxTzSHA1Context_t aContext, DxUint8 aDigest[SHA1_SIGNATURE_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_SHA1Terminate(DxTzSHA1Context_t aContext)
{return DX_TZ_FAILURE;}

#if 0
DxStatus DxTzService_SHA256Init(DxTzSHA256Context_t* aContext)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_SHA256Update(DxTzSHA256Context_t aContext, const DxUint8 *aBuffer, DxUint32 aBufferLength)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_SHA256Final(DxTzSHA256Context_t aContext, DxUint8 aDigest[SHA256_SIGNATURE_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_SHA256Terminate(DxTzSHA256Context_t aContext)
{return DX_TZ_FAILURE;}
#endif

DxStatus DxTzService_MD5Init(DxTzMD5Context_t* aContext)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_MD5Update(DxTzMD5Context_t aContext, const DxUint8 *aBuffer, DxUint32 aBufferLength)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_MD5Final(DxTzMD5Context_t aContext, DxUint8 aDigest[MD5_SIGNATURE_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_MD5Terminate(DxTzMD5Context_t aContext)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_HMAC_SHA256Init(DxTzHMAC_SHA256Context_t *context,
								 const DxUint8 *pKey,
								 DxUint32 key_len)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_HMAC_SHA256Update(DxTzHMAC_SHA256Context_t context,
								   const DxUint8 *data,
								   DxUint32 datLength)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_HMAC_SHA256Final(DxTzHMAC_SHA256Context_t context,
								  DxUint8 aDigest[SHA256_SIGNATURE_SIZE])
{return DX_TZ_FAILURE;}

DxStatus DxTzService_HMAC_SHA256Terminate(DxTzHMAC_SHA256Context_t context)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_RSA_OAEP_DecryptData(DxTzService_RSA_PrivKey_s *privKey_ptr,
									  EDxTzGenericRsaHashOpMode_t	hashFunc,
									  DxByte	*DataIn_ptr,
									  DxUint16	DataInSize,
									  DxByte	*Output_ptr,
									  DxUint16  *OutputSize)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_RSA_OAEP_EncryptData(DxTzService_RSA_PubKey_s *pubKey_ptr,
									  EDxTzGenericRsaHashOpMode_t	hashFunc,
									  DxByte	*DataIn_ptr,
									  DxUint16	DataInSize,
									  DxByte	*Output_ptr)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_RSA_PKCS1v15_DecryptData(DxTzService_RSA_PrivKey_s *privKey_ptr,
									  DxByte						*DataIn_ptr,
									  DxUint16						DataInSize,
									  DxByte						*Output_ptr,
									  DxUint16						*OutputSize)
{return DX_TZ_FAILURE;}


DxStatus DxTzService_RSA_PKCS1v15_EncryptData(DxTzService_RSA_PubKey_s *pubKey_ptr,
									  DxByte						*DataIn_ptr,
									  DxUint16						DataInSize,
									  DxByte						*Output_ptr)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_RSA_PSS_VerifyDataSignature(DxTzService_RSA_PubKey_s *pubKey_ptr,
										 EDxTzGenericRsaHashOpMode_t	hashFunc,
										 DxUint16						saltLen,
										 DxByte							*DataIn_ptr,
										 DxUint32						DataInSize,
										 DxByte							*Sig_ptr)
{return DX_TZ_FAILURE;}

DxStatus DxTzService_RSA_PKCS1v15_VerifyDataSignature(DxTzService_RSA_PubKey_s *pubKey_ptr,
										 EDxTzGenericRsaHashOpMode_t	hashFunc,
										 DxByte							*DataIn_ptr,
										 DxUint32						DataInSize,
										 DxByte							*Sig_ptr)
{return DX_TZ_FAILURE;}
#endif
