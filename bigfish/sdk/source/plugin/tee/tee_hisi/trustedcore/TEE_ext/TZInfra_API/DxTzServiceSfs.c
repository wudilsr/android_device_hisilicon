/**
 * @file DxSFS.c
 * @brief API functions Secure File System backend implementation
 * @author Discretix
 *  		2013-05-16	Yan Polak
 */

#include "DxTzServiceAPI.h"
#include "DxTzService_InternalDefs.h"
#include "DxSfsFormat.h"
#include "DxTzCommonSfs.h"
#include "DxTzServiceSfs.h"
//#define TA_DEBUG
#include "tee_log.h"

/*******************************************************************************
********************************************************************************
*
*       PRIVATE DEFINITIONS, DECLARATIONS AND MACROS
*
********************************************************************************
*******************************************************************************/

#define INIT_MAGIC  0xabcd

typedef struct
{
	DxCipher_AES128_Context_t   hAesCtx;
	FatHdrV1_t*                 pFatHdr;
    FatEntryV1_t*               pFirstEntry;
    DxUint                      entryAndNameSize;
    DxUint                      fatSize;
    DxByte*                     pDataStart;
    DxUint                      init_magic;
}
SfsInstance_t;

//static SfsInstance_t* g_pInstance = DX_NULL;

#define IS_ENTRY_VALID(e)       ('\0' != *((DxChar*)(e) + sizeof(FatEntryV1_t)))
#define INVALIDATE_ENTRY(e, p)  {                                                   \
                                 if (DX_NULL != (p))                                \
                                    *(p) = *((DxChar*)(e) + sizeof(FatEntryV1_t));  \
                                 *((DxChar*)(e) + sizeof(FatEntryV1_t)) = '\0';     \
                                }
#define RESTORE_ENTRY(e, c)     (*((DxChar*)(e) + sizeof(FatEntryV1_t)) = (c))
#define SPACE_AVAILABLE(h)      ((h)->dataBlockSize - (h)->dataSizeUsed)

/*#define SFS_SW_DBG_PRINT*/

#ifdef SFS_SW_DBG_PRINT
    #ifdef __DXTZ_DBG_PRINTF__
        #include "stdio.h"
        #define TMP_PRINT   printf (
    #else
        #define TMP_PRINT   DxHwLogError (DX_FALSE,
    #endif /* __DXTZ_DBG_PRINTF__ */
#else
    #define TMP_PRINT   printDummy (
#endif

#define TMP_PRINT uart_printf_func(

/*******************************************************************************
********************************************************************************
*
*       PRIVATE FUNCTIONS
*
********************************************************************************
*******************************************************************************/
#ifdef SFS_SW_DBG_PRINT
static void printContainerHdr (const ContainerHdr_t* pContainer)
{
    if (!pContainer) return;

    TMP_PRINT "Container(%p): magic=%8x, wrappedSize=%u\n",
              (void *)pContainer,
              (DxUint)pContainer->magic, (DxUint)pContainer->wrappedFatSize);
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static void printFatHdrV1 (const FatHdrV1_t* pFatHdr)
{
    if (!pFatHdr) return;

    TMP_PRINT "FatHdr(version %u):\n"
              "dataBlockSize=%u, numEntries=%u, nameLength=%u, dataSizeUsed=%u\n",
              (DxUint)pFatHdr->version, (DxUint)pFatHdr->dataBlockSize,
              (DxUint)pFatHdr->numEntries, (DxUint)pFatHdr->nameLength,
              (DxUint)pFatHdr->dataSizeUsed);
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static void printInstance (const SfsInstance_t* pinst)
{
    if (!pinst) return;

    TMP_PRINT "Instance(%p):\n pFatHdr=%p, pFirstEntry=%p, pDataStart=%p\n"
              "entryAndNameSize=%u, fatSize=%u\n",
              (void*)pinst, (void*)pinst->pFatHdr, (void*)pinst->pFirstEntry,
              (void*)pinst->pDataStart, pinst->entryAndNameSize, pinst->fatSize);
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static void printBuf (const DxUint8* b, DxUint s, DxUint r, const DxChar* n)
{
    DxUint32    i;
    DxChar      tmp[512];
    DxUint32    count = 0;

    TMP_PRINT "Printing buffer %s (%u):\n", n, s);

    for (i = 0; i < s; ++i)
    {
        count += DxTzService_snprintf (tmp + count, sizeof(tmp), "%02x ", b[i]);
        if (0 == (i + 1) % r)
        {
            TMP_PRINT "%s\n", tmp);
            count = 0;
        }
    }

    if (0 != (i % r))
        TMP_PRINT "%s\n", tmp);
}
#else
static void printDummy (const DxChar* fmt, ...)
{
}
#endif /* SFS_SW_DBG_PRINT */

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus getEmptyFatEntry (SfsInstance_t*   pinst, FatEntryV1_t** ppEntry)
{
    FatEntryV1_t*   pCurEntry = pinst->pFirstEntry;
	DxUint          i;

	for (i = 0; i < pinst->pFatHdr->numEntries; ++i)
    {
		if (!IS_ENTRY_VALID(pCurEntry))
        {
			*ppEntry = pCurEntry;
			return DX_SUCCESS;
		}

        pCurEntry = (FatEntryV1_t*)((DxByte*)pCurEntry + pinst->entryAndNameSize);
	}

    TMP_PRINT "getEmptyFatEntry: Empty entry was not found\n");

	return DX_ITEM_NOT_FOUND;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus getFatEntry (SfsInstance_t* pinst,
                             const DxChar*  name,
                             FatEntryV1_t** ppEntry)
{
    DxChar* pCurName = (DxChar*)pinst->pFirstEntry + sizeof(FatEntryV1_t);
	DxUint  i;

	for (i = 0; i < pinst->pFatHdr->numEntries; ++i)
    {
		if (0 == DxTzService_StrNCmp (pCurName, name, pinst->pFatHdr->nameLength))
        {
			*ppEntry = (FatEntryV1_t*)(pCurName - sizeof(FatEntryV1_t));
			return DX_SUCCESS;
		}

        pCurName += pinst->entryAndNameSize;
	}

    TMP_PRINT "getFatEntry: Item %s is not present\n", name);

	return DX_ITEM_NOT_FOUND;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static void  updateFatDataOffsets (SfsInstance_t* pinst, DxUint refOffset, DxUint size)
{
    FatEntryV1_t*   pCurEntry = pinst->pFirstEntry;
	DxUint          i;

	for (i = 0; i < pinst->pFatHdr->numEntries; ++i)
    {
		if (IS_ENTRY_VALID (pCurEntry) &&
            pCurEntry->offset > refOffset)
        {
			pCurEntry->offset -= size;
		}

        pCurEntry = (FatEntryV1_t*)((DxByte*)pCurEntry + pinst->entryAndNameSize);
    }
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus calculateDigest (const DxByte*  pSrc,
                                 DxByte         digest[DIGEST_SIZE],
                                 DxUint         size)
{
	DxTzSHA256Context_t hShaContext;
    DxStatus result = DX_SUCCESS;

	if (DxTzService_SHA256Init (&hShaContext) != DX_SUCCESS                 ||
	    DxTzService_SHA256Update (hShaContext, pSrc, size) != DX_SUCCESS    ||
	    DxTzService_SHA256Final (hShaContext, digest) != DX_SUCCESS)
    {
        result = DX_FAILURE;
    }

    DxTzService_SHA256Terminate (hShaContext);

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxBool isNameValid (SfsInstance_t* pinst, const DxChar *name)
{
	if (DxTzService_StrNLen (name, pinst->pFatHdr->nameLength) ==
        pinst->pFatHdr->nameLength)
    {
        /* The filename is too long (not enough space fot NULL terminator) */
        return DX_FALSE;
    }

	return DX_TRUE;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus verifyIntegrityData (SfsInstance_t* pinst)
{
    DxByte      digest[DIGEST_SIZE] = {0};
    DxStatus    result = calculateDigest (pinst->pDataStart,
                                          digest,
                                          pinst->pFatHdr->dataBlockSize);

	if (DX_SUCCESS != result)
    {
        TMP_PRINT "verifyIntegrityData: "
                  "Digest calculation on buffer %p (%u bytes) failed\n",
                  (void*)pinst->pDataStart, (DxUint)pinst->pFatHdr->dataBlockSize);
        return result;
    }

    if (0 != DxTzService_IsNotMemEqualSecured (digest,
                                               pinst->pFatHdr->dataDigest,
                                               DIGEST_SIZE))
    {
        TMP_PRINT "verifyIntegrityData: Buffer %p (%u bytes) is corrupted\n",
                   (void*)pinst->pDataStart, (DxUint)pinst->pFatHdr->dataBlockSize);
#ifdef SFS_SW_DBG_PRINT
    printBuf (pinst->pFatHdr->dataDigest, DIGEST_SIZE, 16, "FAT Digest");
    printBuf (digest, DIGEST_SIZE, 16, "Calculated Digest");
    /*
    printBuf (pinst->pDataStart, (DxUint)pinst->pFatHdr->dataBlockSize, 32, "Data start");
    */
#endif /*SFS_SW_DBG_PRINT*/

        return DX_FAILURE;
    }

    return DX_SUCCESS;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus decryptData (const SfsInstance_t*   pinst,
                             const FatEntryV1_t*    pEntry,
                             DxByte*                pDst,
                             const DxByte*          pSrc,
                             DxUint                 size)
{
    DxStatus                        result = DX_SUCCESS;
	DxCipher_AES128CTR_Context_t    hAesCtrCtx;
    DxByte                          iv[IV_SIZE_V1];

    /* Current implementation of AES decryptor changes the iv. Since we must not change
       this value ever, we need this temporary variable */
    DxTzService_MemCpy (iv, pEntry->iv, IV_SIZE_V1);

    result = DxTzService_AES128CTR_Init (
                &hAesCtrCtx, pinst->hAesCtx, pEntry->key, KEY_SIZE_V1, DXCIPHER_DEC);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "decryptData: Failed to create AES CTR context (%x)\n", (DxUint)result);
        return result;
    }

    /*TMP_PRINT "decryptData: %p->%p,(%u)\n", (void*)pSrc, (void*)pDst, size);*/
    result = DxTzService_AES128CTR_DecryptData (hAesCtrCtx, pSrc, pDst, size, iv);
    if (result != DX_SUCCESS)
    {
        TMP_PRINT "decryptData: Failed to decrypt AES CTR (%x)\n", (DxUint)result);
    }

	DxTzService_AES128CTR_Finish (&hAesCtrCtx);

	return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus encryptData (const SfsInstance_t*   pinst,
                             const FatEntryV1_t*    pEntry,
                             DxByte*                pDst,
                             const DxByte*          pSrc,
                             DxUint                 size)
{
    DxStatus                        result = DX_SUCCESS;
	DxCipher_AES128CTR_Context_t    hAesCtrCtx;
    DxByte                          iv[IV_SIZE_V1];

    /* Current implementation of AES decryptor changes the iv. Since we must not change
       this value ever, we need this temporary variable */
    DxTzService_MemCpy (iv, pEntry->iv, IV_SIZE_V1);

    result = DxTzService_AES128CTR_Init (
                &hAesCtrCtx, pinst->hAesCtx, pEntry->key, KEY_SIZE_V1, DXCIPHER_ENC);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "encryptData: Failed to create AES CTR context (%x)\n", (DxUint)result);
        return result;
    }


    result = DxTzService_AES128CTR_EncryptData (hAesCtrCtx, pSrc, pDst, size, iv);
    if (result != DX_SUCCESS)
    {
        TMP_PRINT "encryptData: Failed to encrypt AES CTR (%x)\n", (DxUint)result);
    }

	DxTzService_AES128CTR_Finish (&hAesCtrCtx);

	return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus verifyInstance (const HSFS hSfs)
{
	SfsInstance_t*  pinst = (SfsInstance_t*)hSfs;
    //DxStatus        result = ((g_pInstance == pinst) ? DX_SUCCESS : DX_BAD_ARGUMENTS);
    //DxStatus        result = DX_SUCCESS;

    if(pinst == DX_NULL)
        return DX_BAD_ARGUMENTS;
    if(pinst->init_magic != INIT_MAGIC)
        return DX_BAD_ARGUMENTS;

    return DX_SUCCESS;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus verifyIntegrityFat (const SfsInstance_t*    pinst,
                                    const DxUint            fatSize)
{
    DxUint      calculatedSize;
    DxStatus    result = DX_SUCCESS;

    switch (pinst->pFatHdr->version)
    {
        case SFS_VERSION_V1:
        {
            DxUint entryAndNameSize = sizeof(FatEntryV1_t) + NAME_LEN_MAX;
            calculatedSize  = sizeof(FatHdrV1_t) +
                              entryAndNameSize * pinst->pFatHdr->numEntries;
            result          = (fatSize >= calculatedSize ? DX_SUCCESS : DX_BAD_ARGUMENTS);
            if (DX_SUCCESS != result)
            {
                TMP_PRINT "verifyIntegrityFat:"
                          "estimated size(%u) differs from the calculated one "
                          "based on the values in the header (%u)\n",
                          fatSize, calculatedSize);
            }
        }
        break;

        default:

            TMP_PRINT "verifyIntegrityFat: "
                      "Version %u currently is not supported\n",
                      (DxUint)pinst->pFatHdr->version);
            result = DX_NOT_SUPPORTED;

        break;
    }

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus initInstance (SfsInstance_t*    pinst,
                              const DxByte*     pWrappedFat,
                              DxUint            containerBodySize)
{
    DxStatus    result = DX_SUCCESS;
    DxUint      wrappedFatSize;

    pinst->entryAndNameSize = sizeof(FatEntryV1_t) + NAME_LEN_MAX;
    pinst->fatSize = sizeof(FatHdrV1_t) + NUM_FAT_ENTRIES * pinst->entryAndNameSize;
    wrappedFatSize = DxTzService_EstimateWrappedSize (pinst->fatSize);

    if (containerBodySize < wrappedFatSize)
    {
        TMP_PRINT "initInstance: The container size(%u) "
                  "is smaller then wrapped FAT header(%u)\n",
                  containerBodySize, wrappedFatSize);
        result = DX_FAILURE;
        goto end;
    }

    pinst->pFatHdr = DxTzService_Malloc (pinst->fatSize);
	if (DX_NULL == pinst->pFatHdr)
    {
        TMP_PRINT "initInstance: Failed to allocate %u bytes\n",
                  (DxUint)sizeof(pinst->fatSize));
        result = DX_MEM_ALLOCATION_ERROR;
        goto end;
    }

    DxTzService_MemSet (pinst->pFatHdr, 0, pinst->fatSize);

    pinst->pDataStart   = (DxByte*)pWrappedFat + wrappedFatSize;
    pinst->pFirstEntry  = (FatEntryV1_t*)((DxByte*)pinst->pFatHdr + sizeof(FatHdrV1_t));

    pinst->pFatHdr->version         = SFS_VERSION_V1;
    pinst->pFatHdr->dataBlockSize   = containerBodySize - wrappedFatSize;
    pinst->pFatHdr->numEntries      = NUM_FAT_ENTRIES;
    pinst->pFatHdr->nameLength      = NAME_LEN_MAX;
    pinst->pFatHdr->dataSizeUsed    = 0;

    result = DxTzService_RandomGenerate (pinst->pDataStart,
                                         pinst->pFatHdr->dataBlockSize);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "initInstance: Failed to randomize buffer of size %u (%x)\n",
                  (DxUint)pinst->pFatHdr->dataBlockSize, (DxUint)result);
        goto end;
    }

    result = calculateDigest (pinst->pDataStart,
                              pinst->pFatHdr->dataDigest,
                              pinst->pFatHdr->dataBlockSize);
    if (DX_SUCCESS != result)
        goto end;

	result = DxTzService_AES128_CreateContext (&pinst->hAesCtx);
    if (result != DX_SUCCESS)
    {
        TMP_PRINT "initInstance: Failed to create AES128 context(%x)\n", (DxUint)result);
        goto end;
    }

#ifdef SFS_SW_DBG_PRINT
    TMP_PRINT "initInstance debug data:\n");
    printInstance (pinst);
    printFatHdrV1 (pinst->pFatHdr);
    printBuf (pinst->pFatHdr->dataDigest, DIGEST_SIZE, 16, "Digest");
/*    printBuf (pinst->pDataStart, pinst->dataBlockSize, 16, "Data"); */
#endif /* SFS_SW_DBG_PRINT */

end:

    if (DX_SUCCESS != result)
    {
        if (DX_NULL != pinst->pFatHdr)
        {
            DxTzService_Free (pinst->pFatHdr);
            pinst->pFatHdr = DX_NULL;
        }
    }

    pinst->init_magic = INIT_MAGIC;

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus setupInstance (SfsInstance_t*   pinst,
                               const DxByte*    pWrappedFat,
                               DxUint           wrappedFatSize,
                               DxUint           containerBodySize)
{
    DxStatus    result = DX_SUCCESS;

    pinst->pFatHdr = DxTzService_Malloc (wrappedFatSize);
	if (DX_NULL == pinst->pFatHdr)
    {
        TMP_PRINT "setupInstance: Failed to allocate %u bytes\n", wrappedFatSize);
        result = DX_MEM_ALLOCATION_ERROR;
    }

    pinst->fatSize = wrappedFatSize;
    result = DxTzService_UnwrapBuffer (pWrappedFat, wrappedFatSize,
                                       pinst->pFatHdr, &pinst->fatSize);
    if (DX_SUCCESS != result || pinst->fatSize > wrappedFatSize)
    {
        TMP_PRINT "setupInstance: Failed to unwrap buffer of %u(%u) bytes, rc=%x)\n",
                  pinst->fatSize, wrappedFatSize, (DxUint)result);
        result = DX_FAILURE;
        goto end;
    }

    result = verifyIntegrityFat (pinst, pinst->fatSize);
    if (DX_SUCCESS != result)
        goto end;

    if (wrappedFatSize + pinst->pFatHdr->dataBlockSize != containerBodySize)
    {
        TMP_PRINT "setupInstance: The actual data block size(%u) "
                  "is not equal to the one declared by SFS header(%u)\n",
                  containerBodySize - wrappedFatSize,
                  (DxUint)pinst->pFatHdr->dataBlockSize);
        result = DX_FAILURE;
        goto end;
    }

    pinst->pFirstEntry = (FatEntryV1_t*)((DxByte*)pinst->pFatHdr + sizeof(FatHdrV1_t));
    pinst->entryAndNameSize = sizeof(FatEntryV1_t) + NAME_LEN_MAX;
    pinst->pDataStart = (DxByte*)pWrappedFat + wrappedFatSize;

#ifdef SFS_SW_DBG_PRINT
    TMP_PRINT "setupInstance debug data:\n");
    printInstance (pinst);
    printFatHdrV1 (pinst->pFatHdr);
    printBuf (pinst->pFatHdr->dataDigest, DIGEST_SIZE, 16, "Digest");
/*    printBuf (pWrappedFat + wrappedFatSize,
              pinst->pFatHdr->dataBlockSize, 16, "Data"); */
#endif /* SFS_SW_DBG_PRINT */

    result = verifyIntegrityData (pinst);
    if (DX_SUCCESS != result)
        goto end;

	result = DxTzService_AES128_CreateContext (&pinst->hAesCtx);
    if (result != DX_SUCCESS)
        TMP_PRINT "setupInstance: Failed to create AES128 context(%x)\n", (DxUint)result);

end:

    if (DX_SUCCESS != result)
    {
        if (DX_NULL != pinst->pFatHdr)
        {
            DxTzService_Free (pinst->pFatHdr);
            pinst->pFatHdr = DX_NULL;
        }
    }

    pinst->init_magic = INIT_MAGIC;

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus createFile (SfsInstance_t*  pinst,
                            const DxChar*   name,
                            const DxByte*   pSrc,
                            DxUint          size2write)
{
    DxStatus        result = DX_SUCCESS;
    FatEntryV1_t*   pEntry = DX_NULL;

    if (size2write > SPACE_AVAILABLE (pinst->pFatHdr))
    {
        TMP_PRINT "createFile: Requested size(%u) is bigger then the free data area(%u)\n",
                  size2write, (DxUint)SPACE_AVAILABLE (pinst->pFatHdr));
        return DX_BAD_ARGUMENTS;
    }

	result = getEmptyFatEntry (pinst, &pEntry);
	if (DX_SUCCESS != result)
    {
        return result;
    }

    /* Entry is not valid until its name is not valid */
    pEntry->offset = pinst->pFatHdr->dataSizeUsed;
    if (DX_SUCCESS != DxTzService_RandomGenerate (pEntry->key, KEY_SIZE_V1) ||
        DX_SUCCESS != DxTzService_RandomGenerate (pEntry->iv, IV_SIZE_V1))
    {
        TMP_PRINT "createFile: Generation of key and iv failed\n");
        return DX_FAILURE;
    }

    result = encryptData (pinst, pEntry,
                          pinst->pDataStart + pEntry->offset, pSrc, size2write);
	if (DX_SUCCESS != result)
    {
        return result;
    }
    pEntry->size = size2write;

    /* INCONSISTENCY WINDOW START */
    result = calculateDigest (pinst->pDataStart,
                              pinst->pFatHdr->dataDigest,
                              pinst->pFatHdr->dataBlockSize);
	if (DX_SUCCESS != result)
    {
        TMP_PRINT "createFile: Digest calculation on buffer %p (%u bytes) failed\n",
                  pinst->pDataStart, (DxUint)pinst->pFatHdr->dataBlockSize);
        return result;
    }

    pinst->pFatHdr->dataSizeUsed += size2write;
    DxTzService_StrNCopy ((DxChar*)pEntry + sizeof(FatEntryV1_t),
                          pinst->pFatHdr->nameLength,
                          name);

    /* INCONSISTENCY WINDOW END */

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/
#if 0
static DxStatus trySaveConsistency (SfsInstance_t*  pinst, FatEntryV1_t* pEntry)
{
    /* If there is a change in data, invalidate the entry and calculate new digest */
    DxByte  tmpDigest[DIGEST_SIZE];

    DxStatus result = calculateDigest (pinst->pDataStart,
                                       tmpDigest,
                                       pinst->pFatHdr->dataBlockSize);

    INVALIDATE_ENTRY (pEntry, DX_NULL);

    DxTzService_MemCpy (pinst->pFatHdr->dataDigest, tmpDigest, DIGEST_SIZE);

    return result;
}
#endif
/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus deleteFile (SfsInstance_t*  pinst,
                            FatEntryV1_t*   pEntry,
                            DxBool          killEntry)
{
    /*                      all data                   before this file  this file */
    DxUint  size2move = pinst->pFatHdr->dataSizeUsed - pEntry->offset - pEntry->size;
    DxChar  c;

    INVALIDATE_ENTRY (pEntry, &c);

    /* INCONSISTENCY WINDOW START */
    pinst->pFatHdr->dataSizeUsed -= pEntry->size;

    if (0 != size2move)
    {
        DxTzService_MemMove (pinst->pDataStart + pEntry->offset,
                             pinst->pDataStart + pEntry->offset + pEntry->size,
                             size2move);
        updateFatDataOffsets (pinst, pEntry->offset, pEntry->size);

        return calculateDigest (pinst->pDataStart,
                                pinst->pFatHdr->dataDigest,
                                pinst->pFatHdr->dataBlockSize);
    }

    if (DX_TRUE != killEntry)
        RESTORE_ENTRY (pEntry, c);
    /* INCONSISTENCY WINDOW END */

    return DX_SUCCESS; /* The case were the deleted file was the last one */
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus updateFile (SfsInstance_t*  pinst,
                            FatEntryV1_t*   pEntry,
                            const DxByte*   pSrc,
                            DxUint          offset,
                            DxUint          size2write)
{
    DxStatus    result = DX_SUCCESS;
    DxByte*     pUnifiedBuffer = DX_NULL;

    if (size2write > SPACE_AVAILABLE (pinst->pFatHdr) + pEntry->size - offset)
    {
        TMP_PRINT "updateFile: Requested size(%u) is bigger then the free data area(%u)\n",
                  size2write,
                  (DxUint)(SPACE_AVAILABLE (pinst->pFatHdr) + pEntry->size - offset));
        return DX_BAD_ARGUMENTS;
    }

    if (0 != offset)
    {
        pUnifiedBuffer  = DxTzService_Malloc (offset + size2write);
        if (DX_NULL == pUnifiedBuffer)
        {
            TMP_PRINT "updateFile: Failed to allocate %u bytes\n", offset);
            result = DX_MEM_ALLOCATION_ERROR;
            goto end;
        }

        result = decryptData (pinst, pEntry,
                              pUnifiedBuffer,
                              pinst->pDataStart + pEntry->offset,
                              offset);
        if (DX_SUCCESS != result)
        {
            goto end;
        }

        DxTzService_MemCpy (&pUnifiedBuffer[offset], pSrc, size2write);
    }
    else
    {
        pUnifiedBuffer = (DxByte*)pSrc;
    }

    /* INCONSISTENCY WINDOW START */
    /* There is no point in changing FAT entry if the new size equals the old one */
    if (offset + size2write != pEntry->size)
    {
        result =  deleteFile (pinst, pEntry, DX_FALSE);
        if (DX_SUCCESS != result)
        {
            TMP_PRINT "updateFile: Failed to delete file %s (%u bytes from offset %u)\n",
                      (DxChar*)pEntry + sizeof(FatEntryV1_t),
                      (DxUint)pEntry->size, (DxUint)pEntry->offset);
            INVALIDATE_ENTRY (pEntry, (DxChar *)DX_NULL);
            goto end;
        }

        pEntry->size = offset + size2write;
        pEntry->offset = pinst->pFatHdr->dataSizeUsed;
        pinst->pFatHdr->dataSizeUsed += pEntry->size;
    }

    result = encryptData (pinst, pEntry,
                          pinst->pDataStart + pEntry->offset,
                          pUnifiedBuffer,
                          offset + size2write);

	if (DX_SUCCESS != result)
        goto end;
/*
	if (DX_SUCCESS != result)
    {
        result = trySaveConsistency (pinst, pEntry);
        goto end;
    }
*/
    result = calculateDigest (pinst->pDataStart,
                              pinst->pFatHdr->dataDigest,
                              pinst->pFatHdr->dataBlockSize);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "updateFile: Digest calculation on buffer %p (%u bytes) failed\n",
                  pinst->pDataStart, (DxUint)pinst->pFatHdr->dataBlockSize);
        INVALIDATE_ENTRY (pEntry, (DxChar *)DX_NULL);

        goto end;
    }
    /* INCONSISTENCY WINDOW END */

end:

    if (DX_NULL != pUnifiedBuffer &&
        pSrc != pUnifiedBuffer)
        DxTzService_Free (pUnifiedBuffer);

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus parseContainer (SfsInstance_t*  pinst,
                                const DxByte*   pContainer,
                                DxUint          containerSize)
{
    ContainerHdr_t* pHdr = (ContainerHdr_t*)pContainer;
	DxStatus        result = DX_SUCCESS;


#ifdef SFS_SW_DBG_PRINT
    printContainerHdr (pHdr);
#endif

    /* Verify integrity of the container header */
    switch (pHdr->magic)
    {
        case SFS_MAGIC_VALUE:

            result = setupInstance (pinst,
                                    (DxByte*)pContainer + sizeof(ContainerHdr_t),
                                    pHdr->wrappedFatSize,
                                    containerSize - sizeof(ContainerHdr_t));

            break;

        case 0:

            result = initInstance (pinst,
                                   (DxByte*)pContainer + sizeof(ContainerHdr_t),
                                   containerSize - sizeof(ContainerHdr_t));

            break;

        default:

            TMP_PRINT "parseContainer: Invalid container header:%08x %08x\n",
                      (DxUint)pHdr->magic, (DxUint)pHdr->wrappedFatSize);
            result = DX_BAD_ARGUMENTS;

            break;
    }

    return result;
}

static DxChar isSfsInitialed(HSFS phSfs)
{
    SfsInstance_t*  pinst = phSfs;

    if(phSfs == DX_NULL)
        return 0;

    return (pinst->init_magic == INIT_MAGIC ? 1 : 0);
}

/*******************************************************************************
********************************************************************************
*
*       PUBLIC FUNCTIONS
*
********************************************************************************
*******************************************************************************/

DxStatus DxSfsInitialize (HSFS*         phSfs,
                          const DxByte* pContainer,
                          DxUint        containerSize)
{
	SfsInstance_t*  pinst = DX_NULL;
	DxStatus        result = DX_SUCCESS;
/*
    printf ("sizeof(DxUint32) = %u, sizeof(DxUint64) = %u, sizeof(void*) = %u\n",
            sizeof(DxUint32), sizeof(DxUint64), sizeof(void*));
    return DX_FAILURE;
*/
	if (DX_NULL == phSfs ||
        DX_NULL == pContainer)
    {
        TMP_PRINT "DxSfsInitialize: Invalid arguments %p, %p\n",
                  phSfs, pContainer);
        return DX_BAD_ARGUMENTS;
    }

    if  (isSfsInitialed(*phSfs) == 1)
    {
        TMP_PRINT "DxSfsInitialize: Instance is already initialized\n");
        return DX_ALREADY_INITIALIZED;
    }

	pinst = DxTzService_Malloc (sizeof(SfsInstance_t));
	if (DX_NULL == pinst)
    {
        TMP_PRINT "DxSfsInitialize: Failed to allocate %u bytes\n",
                  (DxUint)sizeof(SfsInstance_t));
        return DX_MEM_ALLOCATION_ERROR;
    }

    DxTzService_MemSet (pinst, 0, sizeof(SfsInstance_t));

    /* From this point down we should deallocate the pinst in case of error */
    result = parseContainer (pinst, pContainer, containerSize);
    if (DX_SUCCESS != result)
    {
        goto end;
    }

end:

    //g_pInstance = pinst;

    if (DX_SUCCESS == result)
    {
        *phSfs = (HSFS)pinst;
    }
    else
    {
        DxSfsFinalize ((HSFS)pinst);
    }

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

DxStatus DxSfsFinalize (HSFS    hSfs)
{
    DxStatus        result = verifyInstance (hSfs);
	SfsInstance_t*  pinst = (SfsInstance_t*) hSfs;

    if (DX_SUCCESS != result)
    {
        return DX_BAD_ARGUMENTS;
    }

	DxTzService_AES128_TerminateContext (&pinst->hAesCtx);

    if (DX_NULL != pinst->pFatHdr)
        DxTzService_Free (pinst->pFatHdr);

    pinst->init_magic = 0;

    DxTzService_Free (pinst);

    //g_pInstance = DX_NULL;

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

DxStatus DxSfsGetSize (HSFS hSfs, const DxChar* name, DxUint* pLen)
{
    DxStatus        result = verifyInstance (hSfs);
	SfsInstance_t*  pinst = (SfsInstance_t*) hSfs;
    FatEntryV1_t*   pEntry = DX_NULL;

    if (DX_SUCCESS != result    ||
        DX_NULL == name         ||
        DX_NULL == pLen)
    {
        TMP_PRINT "DxSfsGetSize: Invalid arguments\n");
        return DX_BAD_ARGUMENTS;
    }

	result = getFatEntry (pinst, name, &pEntry);
	if (DX_SUCCESS != result)
    {
        return result;
    }

	*pLen = pEntry->size;

	return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

DxStatus DxSfsRead (HSFS            hSfs,
                    const DxChar*   name,
                    DxUint          offset,
                    DxByte*         pDst,
                    DxUint*         pSize2read)
{
    DxStatus        result = verifyInstance (hSfs);
	SfsInstance_t*  pinst = (SfsInstance_t*) hSfs;
    FatEntryV1_t*   pEntry = DX_NULL;
    DxByte*         pTmpDst = DX_NULL;

    if (DX_SUCCESS != result    ||
        DX_NULL == name         ||
        DX_NULL == pDst         ||
        DX_NULL == pSize2read)
    {
        TMP_PRINT "DxSfsRead: Invalid arguments\n");
        return DX_BAD_ARGUMENTS;
    }

    result = verifyIntegrityData (pinst);
	if (DX_SUCCESS != result)
    {
        return result;
    }

	result = getFatEntry (pinst, name, &pEntry);
	if (DX_SUCCESS != result)
    {
        return result;
    }

    if (offset >= pEntry->size)
    {
        TMP_PRINT "DxSfsRead: Required offset %u is illegal for the file size %u\n",
                  offset, (DxUint)pEntry->size);
        return DX_BAD_ARGUMENTS;
    }

    /* If the offset is not 0, we still need to read the whole file in order to
       decrypt it */
    pTmpDst = DxTzService_Malloc (pEntry->size);
#if 0
    if (0 != offset)
    {
        pTmpDst = DxTzService_Malloc (pEntry->size);
        if (DX_NULL == pTmpDst)
        {
            TMP_PRINT "DxSfsRead: Failed to allocate tmp buffer of %u bytes\n",
                      (DxUint)pEntry->size);
            return DX_MEM_ALLOCATION_ERROR;
        }
    }
    else
    {
        pTmpDst = pDst;
    }
#endif

	result = decryptData (pinst, pEntry,
                          pTmpDst, pinst->pDataStart + pEntry->offset, pEntry->size);
	if (DX_SUCCESS != result)
    {
        TMP_PRINT "DxSfsRead: Failed to decrypt file %s (%u bytes)\n",
                  name, (DxUint)pEntry->size);
        goto end;
    }

    if (*pSize2read > pEntry->size - offset)
    {
        *pSize2read = pEntry->size - offset;
    }

    DxTzService_MemCpy (pDst, &pTmpDst[offset], *pSize2read);
#if 0
    if (0 != offset)
    {
        DxTzService_MemCpy (pDst, &pTmpDst[offset], *pSize2read);
    }
#endif

end:

    if (DX_NULL != pTmpDst  &&
        pDst != pTmpDst)
    {
        DxTzService_Free (pTmpDst);
    }

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

DxStatus DxSfsWrite (HSFS           hSfs,
                     const DxChar*  name,
                     const DxByte*  pSrc,
                     DxUint         offset,
                     DxUint         size2write)
{
    DxStatus        result = verifyInstance (hSfs);
	SfsInstance_t*  pinst = (SfsInstance_t*) hSfs;
    FatEntryV1_t*   pEntry = DX_NULL;

    if (DX_SUCCESS != result    ||
	    DX_NULL == name         ||
        DX_NULL == pSrc)
    {
        TMP_PRINT "DxSfsWrite:: Invalid arguments\n");
        return DX_BAD_ARGUMENTS;
    }

    if (0 == size2write)
    {
        return DxSfsDelete (hSfs, name);
    }

	if (DX_TRUE != isNameValid (pinst, name))
    {
        TMP_PRINT "DxSfsWrite: Input filename is too long (more then %u bytes)\n",
                  (DxUint)pinst->pFatHdr->nameLength - 1);
        return DX_BAD_ARGUMENTS;
    }

    result = verifyIntegrityData (pinst);
	if (DX_SUCCESS != result)
    {
        return result;
    }

    /* Differentiate between an existent file and a new one */
    if (DX_SUCCESS == getFatEntry (pinst, name, &pEntry))
    {
        result = updateFile (pinst, pEntry, pSrc, offset, size2write);
    }
    else
    {
        result = createFile (pinst, name, pSrc, size2write);
    }

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

DxStatus DxSfsDelete (HSFS hSfs, const DxChar* name)
{
	SfsInstance_t*  pinst = (SfsInstance_t*) hSfs;
    FatEntryV1_t*   pEntry = DX_NULL;
    DxStatus        result = verifyInstance (hSfs);

    if (DX_SUCCESS != result    ||
        DX_NULL == name)
    {
        TMP_PRINT "DxSfsWrite:: Invalid arguments\n");
        return DX_BAD_ARGUMENTS;
    }

	if (DX_TRUE != isNameValid (pinst, name))
    {
        TMP_PRINT "DxSfsDelete: Input filename is too long (more then %u bytes)\n",
                  (DxUint)pinst->pFatHdr->nameLength);
        return DX_BAD_ARGUMENTS;
    }

    result = verifyIntegrityData (pinst);
	if (DX_SUCCESS != result)
    {
        return result;
    }

    result = getFatEntry (pinst, name, &pEntry);
    if (DX_SUCCESS == result)
    {
        result = deleteFile (pinst, pEntry, DX_TRUE);
    }

    if (DX_SUCCESS != result)
    {
        TMP_PRINT "DxSfsDelete: Failed to delete file %s (%x)\n", name, (DxUint)result);
    }

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

DxStatus DxSfsCreateContainer (HSFS   hSfs, DxByte* pContainer, DxUint* pSize)
{
    DxStatus        result = verifyInstance (hSfs);
	SfsInstance_t*  pinst = (SfsInstance_t*) hSfs;
    ContainerHdr_t* pHdr = (ContainerHdr_t*) pContainer;
    DxUint          actSize;

    if (DX_SUCCESS != result)
    {
        return DX_BAD_ARGUMENTS;
    }

	if (DX_NULL == pSize ||
        DX_NULL == pContainer)
    {
        TMP_PRINT "DxSfsCreateContainer: Invalid arguments\n");
        return DX_BAD_ARGUMENTS;
    }

    pHdr->wrappedFatSize = DxTzService_EstimateWrappedSize (pinst->fatSize);
    actSize = sizeof(ContainerHdr_t)    +
              pHdr->wrappedFatSize      +
              pinst->pFatHdr->dataBlockSize;
    if (actSize > *pSize)
    {
        TMP_PRINT "DxSfsCreateContainer: Actual size of the container(%u) is bigger "
                  "then the reserved buffer (%u)\n",
                  actSize, *pSize);
        return DX_BUFFER_IS_NOT_BIG_ENOUGH;
    }

    *pSize = actSize;

    actSize = pHdr->wrappedFatSize;
    result = DxTzService_WrapBuffer (pinst->pFatHdr, pinst->fatSize,
                                     pContainer + sizeof(ContainerHdr_t), &actSize);
    if (DX_SUCCESS != result || actSize != pHdr->wrappedFatSize)
    {
        TMP_PRINT "DxSfsCreateContainer: Failed to wrap buffer of %u(%u) bytes, rc=%x)\n",
                  actSize, pinst->fatSize, (DxUint)result);
        result = DX_FAILURE;
    }
    pHdr->magic = SFS_MAGIC_VALUE;

#ifdef SFS_SW_DBG_PRINT
    TMP_PRINT "DxSfsCreateContainer debug data (%u overall):\n", *pSize);
    printContainerHdr (pHdr);
    printFatHdrV1 ((FatHdrV1_t*)(pContainer + sizeof(ContainerHdr_t)));
    printBuf (pContainer + sizeof(ContainerHdr_t),
              sizeof(FatHdrV1_t), 16, "FAT header");
    /*
    printBuf (pinst->pDataStart, (DxUint)pinst->pFatHdr->dataBlockSize, 32, "Data start");
    */
#endif /* SFS_SW_DBG_PRINT */

    return result;
}

