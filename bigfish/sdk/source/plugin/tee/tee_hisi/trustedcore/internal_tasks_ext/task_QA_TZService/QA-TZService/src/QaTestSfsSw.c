/**
 * @brief acceptance test to verify the API functions Secure File System backend
 * @author Discretix
 *  		2013-03-05	Ben Baron
 */

//#include <stdio.h>
#include "DX_VOS_Errors.h"
#include "DxTzServiceAPITypes.h"
#include "DxTzServiceAPI.h"
#include "DxTzService_Utils.h"
#include "DxTzService_InternalDefs.h"
#include "DxTzCommonSfs.h"
#include "DxSfsFormat.h"
#include "DxTzServiceSfs.h"

/*******************************************************************************
********************************************************************************
*
*       PRIVATE DEFINITIONS, DECLARATIONS AND MACROS
*
********************************************************************************
*******************************************************************************/

typedef struct
{
    HSFS    hSfs;
    DxByte* sfsBuf;
    DxUint  size;
}
SfsTest_t;

static SfsTest_t g_Test = {0};

#define SFS_SW_TEST_DBG_PRINT
#ifdef SFS_SW_TEST_DBG_PRINT
    #ifdef __DXTZ_DBG_PRINTF__
        #include "stdio.h"
        #define TMP_PRINT   printf (
    #else
        #define TMP_PRINT   DxHwLogTrace (DX_TRUE,
    #endif /* __DXTZ_DBG_PRINTF__ */
#else
    static void printDummy (const DxChar* fmt, ...)
    {
    }
    #define TMP_PRINT   printDummy (
#endif

#define TMP_PRINT uart_printf_func(

/*
static void printBuf (const DxUint8* b, DxUint s, DxUint r, const DxChar* n)
{
    DxUint32    i;
    DxChar      tmp[512];
    DxUint32    count = 0;

    TMP_PRINT "Printing buffer %s (%u):\n", n, s);

    for (i = 0; i < s; ++i)
    {
        count += DxTzService_snTMP_PRINT tmp + count, sizeof(tmp), "%02x ", b[i]);
        if (0 == (i + 1) % r)
        {
            TMP_PRINT "%s\n", tmp);
            count = 0;
        }
    }

    if (0 != (i % r))
        TMP_PRINT "%s\n", tmp);
}
*/

/*******************************************************************************
********************************************************************************
*
*       PRIVATE FUNCTIONS
*
********************************************************************************
*******************************************************************************/

static DxStatus test_InitializeTerminate (void)
{
    DxStatus result;

    /*------------------------------------------------------------------------*/
    TMP_PRINT "test_InitializeTerminate: testing invalid input parameters ...\n");
    result = DxSfsInitialize (DX_NULL, g_Test.sfsBuf,  g_Test.size);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL handle pointer wasn't rejected\n");
        return DX_FAILURE;
    }
    result = DxSfsInitialize (&g_Test.hSfs, DX_NULL,  g_Test.size);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL container pointer wasn't rejected\n");
        return DX_FAILURE;
    }
    TMP_PRINT "... SUCCEEDED :-)\n");

    /*------------------------------------------------------------------------*/
    TMP_PRINT "test_InitializeTerminate: testing first time initialization ...\n");
    result = DxSfsInitialize (&g_Test.hSfs, g_Test.sfsBuf,  g_Test.size);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( \n");
        return DX_FAILURE;
    }

    result = DxSfsInitialize (&g_Test.hSfs, g_Test.sfsBuf,  g_Test.size);
    if (DX_ALREADY_INITIALIZED != result)
    {
        TMP_PRINT "... FAILED :-( Double initialization was not rejected\n");
        return DX_FAILURE;
    }
    TMP_PRINT "... SUCCEEDED :-)\n");

    /*------------------------------------------------------------------------*/
    TMP_PRINT "test_InitializeTerminate: testing termination ...\n");
    result = DxSfsFinalize (DX_NULL);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL handle pointer wasn't rejected\n");
        return DX_FAILURE;
    }

    result = DxSfsFinalize (g_Test.hSfs);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Valid handle wasn't recognized\n");
        return DX_FAILURE;
    }

    result = DxSfsInitialize (&g_Test.hSfs, g_Test.sfsBuf,  g_Test.size);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( First time initialization after termination\n");
        return DX_FAILURE;
    }

    result = DxSfsFinalize (g_Test.hSfs);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Failed to terminate after second initialization\n");
        return DX_FAILURE;
    }

    TMP_PRINT "... SUCCEEDED :-)\n");

    return DX_SUCCESS;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus test_CreateContainer (void)
{
    DxStatus    result;
    DxUint      size;

    /*------------------------------------------------------------------------*/
    TMP_PRINT "test_CreateContainer: testing invalid input parameters ...\n");
    result = DxSfsCreateContainer (g_Test.hSfs, g_Test.sfsBuf, &size);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL handle pointer wasn't rejected\n");
        return DX_FAILURE;
    }

    result = DxSfsCreateContainer (g_Test.hSfs, DX_NULL, &size);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL container pointer wasn't rejected\n");
        return DX_FAILURE;
    }

    result = DxSfsCreateContainer (g_Test.hSfs, g_Test.sfsBuf, DX_NULL);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL size pointer wasn't rejected\n");
        return DX_FAILURE;
    }

    result = DxSfsInitialize (&g_Test.hSfs, g_Test.sfsBuf,  g_Test.size);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( First time initialization\n");
        return DX_FAILURE;
    }

    size = 100;
    result = DxSfsCreateContainer (g_Test.hSfs, g_Test.sfsBuf, &size);
    if (DX_BUFFER_IS_NOT_BIG_ENOUGH != result)
    {
        TMP_PRINT "... FAILED :-( Insufficient buffer(%u) wasn't rejected\n", size);
        return DX_FAILURE;
    }
    TMP_PRINT "... SUCCEEDED :-)\n");

    /*------------------------------------------------------------------------*/
    TMP_PRINT "test_CreateContainer: testing container creation ...\n");
    size =  g_Test.size;
    result = DxSfsCreateContainer (g_Test.hSfs, g_Test.sfsBuf, &size);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Container wasn't created\n");
        return DX_FAILURE;
    }

    result = DxSfsFinalize (g_Test.hSfs);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Terminate after initial container creation\n");
        return DX_FAILURE;
    }

    result = DxSfsInitialize (&g_Test.hSfs, g_Test.sfsBuf,  g_Test.size);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Initialization with valid container\n");
        return DX_FAILURE;
    }

    size =  g_Test.size;
    result = DxSfsCreateContainer (g_Test.hSfs, g_Test.sfsBuf, &size);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Container wasn't created after initialization with "
                "valid container\n");
        return DX_FAILURE;
    }

    result = DxSfsFinalize (g_Test.hSfs);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Termination after second container creation\n");
        return DX_FAILURE;
    }
    TMP_PRINT "... SUCCEEDED :-)\n");

    return DX_SUCCESS;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus testReadOffsets (DxChar*    testFileName,
                                 DxByte*    buffer,
                                 DxUint     size)
{
    DxStatus    result = DX_SUCCESS;
    DxUint      usedSize = size;
    DxByte*     testBuf = DxTzService_Malloc (usedSize);

    testBuf = DxTzService_Malloc (size);
    if (DX_NULL == testBuf)
    {
        TMP_PRINT "... FAILED :-( Test read buffer allocation\n");
        return DX_MEM_ALLOCATION_ERROR;
    }

    while (usedSize)
    {
        DxUint  actSize = size; /* The size should be adjusted in DxSfsRead */
        DxUint  offset = size - usedSize;
        result = DxSfsRead (g_Test.hSfs, testFileName,
                            offset, testBuf, &actSize);
        if (DX_SUCCESS != result    ||
            actSize != usedSize     ||
            0 != DxTzService_IsNotMemEqualSecured (&buffer[offset], testBuf, actSize))
        {
            TMP_PRINT "... FAILED :-( Reading file %s of size %u/%u from offset %u (%x)\n",
                    testFileName, usedSize, actSize, offset, (DxUint)result);
            result = DX_FAILURE;
            goto end;
        }

        --usedSize;
    }

end:

    DxTzService_Free (testBuf);
    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus testWriteOffsets (DxChar*       testFileName,
                                  const DxByte* buffer,
                                  DxUint        size)
{
    DxStatus    result;
    DxUint      usedSize = size;
    DxByte*     testBuf = DxTzService_Malloc (usedSize);

    testBuf = DxTzService_Malloc (size);
    if (DX_NULL == testBuf)
    {
        TMP_PRINT "... FAILED :-( Test write buffer allocation\n");
        return DX_MEM_ALLOCATION_ERROR;
    }

    while (usedSize)
    {
        DxUint  actSize;
        DxUint  offset = size - usedSize;

        result = DxSfsWrite (g_Test.hSfs, testFileName, buffer, offset, usedSize);
        /* Another option for test
           result = DxSfsWrite (g_Test.hSfs, testFileName, &buffer[offset], 0, usedSize);
        */
        if (DX_SUCCESS != result)
        {
            TMP_PRINT "... FAILED :-( Writing file %s to offset %u (%u bytes)\n",
                    testFileName, offset, usedSize);
            result = DX_FAILURE;
            goto end;
        }

        actSize = size;
        result = DxSfsRead (g_Test.hSfs, testFileName, 0, testBuf, &actSize);
        if (DX_SUCCESS != result    ||
            actSize != size         ||
            0 != DxTzService_IsNotMemEqualSecured (buffer, &testBuf[offset], usedSize))
        {
            TMP_PRINT "... FAILED :-( Reading file %s of size %u from offset %u\n",
                    testFileName, actSize, offset);
            result = DX_FAILURE;
            goto end;
        }
        --usedSize;
    }

end:

    DxTzService_Free (testBuf);
    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

static DxStatus test_WriteRead (DxChar* testFileName,
                                DxByte* buffer,
                                DxUint  size)
{
    DxStatus    result;
    DxChar      fakeName[NAME_LEN_MAX];
    DxByte      dummyBuf[NAME_LEN_MAX];
    DxUint      dummySize = NAME_LEN_MAX;

    result = DxSfsInitialize (&g_Test.hSfs, g_Test.sfsBuf,  g_Test.size);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "test_WriteRead: Failed first time initialization from valid container\n");
        return DX_FAILURE;
    }

    /*------------------------------------------------------------------------*/
    TMP_PRINT "test_WriteRead: testing invalid input parameters ...\n");
    result = DxSfsWrite (DX_NULL, testFileName, buffer, 0, size);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL handle pointer wasn't rejected (write)\n");
        return DX_FAILURE;
    }

    result = DxSfsWrite (g_Test.hSfs, DX_NULL, buffer, 0, size);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL filename wasn't rejected (write)\n");
        return DX_FAILURE;
    }

    result = DxSfsWrite (g_Test.hSfs, testFileName, DX_NULL, 0, size);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL buffer pointer wasn't rejected (write)\n");
        return DX_FAILURE;
    }

    result = DxSfsWrite (g_Test.hSfs, testFileName, buffer, 0,  g_Test.size);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( Bigger then maximal buffer wasn't rejected (write)\n");
        return DX_FAILURE;
    }

    DxTzService_MemSet (fakeName, 'a', NAME_LEN_MAX);
    result = DxSfsWrite (g_Test.hSfs, fakeName, buffer, 0, size);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( Longer then available file name wasn't rejected (write)\n");
        return DX_FAILURE;
    }

    result = DxSfsRead (g_Test.hSfs, testFileName, 0, DX_NULL, &dummySize);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL buffer pointer wasn't rejected (read)\n");
        return DX_FAILURE;
    }

    result = DxSfsRead (g_Test.hSfs, testFileName, 0, dummyBuf, DX_NULL);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL size pointer wasn't rejected (read)\n");
        return DX_FAILURE;
    }

    result = DxSfsRead (g_Test.hSfs, "kuku", 0, dummyBuf, &dummySize);
    if (DX_ITEM_NOT_FOUND != result)
    {
        TMP_PRINT "... FAILED :-( Reading nonexistent filename wasn't rejected (read)\n");
        return DX_FAILURE;
    }

    result = DxSfsWrite (g_Test.hSfs, testFileName, buffer, 0, size);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Initial write\n");
        return DX_FAILURE;
    }

    dummySize = NAME_LEN_MAX;
    result = DxSfsRead (g_Test.hSfs, testFileName, size, dummyBuf, &dummySize);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( Illegal offset  wasn't rejected (read)\n");
        return DX_FAILURE;
    }

    result = DxSfsGetSize (g_Test.hSfs, DX_NULL, &dummySize);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL filename wasn't rejected (getsize)\n");
        return DX_FAILURE;
    }

    result = DxSfsGetSize (g_Test.hSfs, testFileName, DX_NULL);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL size pointer wasn't rejected (getsize)\n");
        return DX_FAILURE;
    }

    result = DxSfsGetSize (g_Test.hSfs, "kuku", &dummySize);
    if (DX_ITEM_NOT_FOUND != result)
    {
        TMP_PRINT "... FAILED :-( Nonexistent filename wasn't rejected (getsize)\n");
        return DX_FAILURE;
    }

    result = DxSfsGetSize (g_Test.hSfs, testFileName, &dummySize);
    if (DX_SUCCESS != result || size != dummySize)
    {
        TMP_PRINT "... FAILED :-( getting file size %u instead of %u \n", dummySize, size);
        return DX_FAILURE;
    }

    result = DxSfsDelete (g_Test.hSfs, DX_NULL);
    if (DX_BAD_ARGUMENTS != result)
    {
        TMP_PRINT "... FAILED :-( NULL filename wasn't rejected (delete)\n");
        return DX_FAILURE;
    }


    TMP_PRINT "... SUCCEEDED :-)\n");

    /*------------------------------------------------------------------------*/
    TMP_PRINT "test_WriteRead: testing reading from different offsets\n");
    result = testReadOffsets (testFileName, buffer, size);
    if (DX_SUCCESS != result)
        return DX_FAILURE;
    TMP_PRINT "... SUCCEEDED :-)\n");

    /*------------------------------------------------------------------------*/
    TMP_PRINT "test_WriteRead: testing writing to different offsets\n");
    result = testWriteOffsets (testFileName, buffer, size);
    if (DX_SUCCESS != result)
        return DX_FAILURE;

    result = DxSfsDelete (g_Test.hSfs, testFileName);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( test buffer %s deletion\n", testFileName);
        return DX_FAILURE;
    }

    dummySize =  g_Test.size;
    result = DxSfsCreateContainer (g_Test.hSfs, g_Test.sfsBuf, &dummySize);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Container wasn't created\n");
        return DX_FAILURE;
    }

    result = DxSfsFinalize (g_Test.hSfs);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Final termination\n");
        return DX_FAILURE;
    }
    TMP_PRINT "... SUCCEEDED :-)\n");

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

typedef struct
{
    DxUint  size;
    DxByte* buffer;
    DxChar  name[NAME_LEN_MAX];
}
TestFileDesc_t;

#define TEST_DESC_NUM       10
#define TEST_BUF_SIZE_BASE  100
#define TEST_FILENAME_BASE  "tbuf"
static DxStatus test_Boundaries  ()
{
    DxStatus        result;
    DxUint          i = 0;
    DxUint          j = 0;
    TestFileDesc_t  testDesc[TEST_DESC_NUM] = {{0}, {0}, {0}, {0}, {0},
                                               {0}, {0}, {0}, {0}, {0}};
    DxUint          usedSize = 0;

    DxUint          fatSize = sizeof(FatHdrV1_t) +
                              NUM_FAT_ENTRIES * (sizeof(FatEntryV1_t) + NAME_LEN_MAX);

    const DxUint    dataSizeMax = g_Test.size - sizeof(ContainerHdr_t) -
                                  DxTzService_EstimateWrappedSize (fatSize);

    for (i = 0; i < TEST_DESC_NUM; ++i)
    {
        testDesc[i].size = (i + 1) * TEST_BUF_SIZE_BASE;
        /*DxTzService_snprintf (testDesc[i].name, NAME_LEN_MAX, "%s%u",
                              TEST_FILENAME_BASE, testDesc[i].size); */
        snprintf(testDesc[i].name, NAME_LEN_MAX, "%s%d",
                              TEST_FILENAME_BASE, testDesc[i].size);
        testDesc[i].buffer = DxTzService_Malloc (testDesc[i].size);
        if (DX_NULL == testDesc[i].buffer)
        {
            TMP_PRINT "test_Boundaries: Failed to initialize test descriptors (%u)\n", i);
            result = DX_MEM_ALLOCATION_ERROR;
            goto end;
        }
        DxTzService_RandomGenerate (testDesc[i].buffer, testDesc[i].size);
    }

    result = DxSfsInitialize (&g_Test.hSfs, g_Test.sfsBuf, g_Test.size);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "test_Boundaries: Failed first time initialization from valid container\n");
        goto end;
    }

    /*------------------------------------------------------------------------*/
    TMP_PRINT "test_Boundaries: testing overflow of data area\n");
    for (i = 0; i < TEST_DESC_NUM; ++i)
    {
        DxStatus expected = DX_SUCCESS;

        usedSize += testDesc[i].size;
        if (usedSize > dataSizeMax)
            expected = DX_BAD_ARGUMENTS;

        result = DxSfsWrite (g_Test.hSfs, testDesc[i].name,
                             testDesc[i].buffer, 0, testDesc[i].size);
        if (result != expected)
        {
            TMP_PRINT "... FAILED :-( writing(1) file %s returned %x when expected %x\n",
                    testDesc[i].name, (DxUint)result, (DxUint)expected);
            goto end;
        }
        else
        {
            /* Store the index of the first rejected file, restore the actual datasize
               and break out */
            if (DX_SUCCESS != result)
            {
                j = i;
                usedSize -= testDesc[i].size;
                break;
            }
        }
    }

    for (i = 0; i < TEST_DESC_NUM && dataSizeMax > testDesc[j].size; ++i)
    {
        DxStatus expected = DX_BAD_ARGUMENTS;
        if (usedSize <= dataSizeMax - testDesc[j].size)
            expected = DX_SUCCESS;

        result = DxSfsWrite (g_Test.hSfs, testDesc[j].name,
                             testDesc[j].buffer, 0, testDesc[j].size);
        if (result != expected)
        {
            TMP_PRINT "... FAILED :-( writing(2) file %s returned %x when expected %x\n",
                    testDesc[j].name, (DxUint)result, (DxUint)expected);
            /*TMP_PRINT "Writing(sizeMax=%u): i=%u, j=%u, sfsSize=%u, filesize=%u\n",
                  dataSizeMax, i, j, usedSize, testDesc[j].size);*/

            goto end;
        }
        else
        {
            if (DX_SUCCESS == result)
            {
                usedSize += testDesc[j].size;
                ++j;
                if (TEST_DESC_NUM == j) /* We are done */
                    break;
            }
        }

        result = DxSfsDelete (g_Test.hSfs, testDesc[i].name);
        if (DX_SUCCESS != result)
        {
            TMP_PRINT "... FAILED :-( deleting file %s\n", testDesc[i].name);
            goto end;
        }
        usedSize -= testDesc[i].size;
    }

    result = DxSfsFinalize (g_Test.hSfs);
    if (DX_SUCCESS != result)
    {
        TMP_PRINT "... FAILED :-( Final termination\n");
        goto end;
    }

    TMP_PRINT "... SUCCEEDED :-)\n");

end:

    for (i = 0; i < TEST_DESC_NUM; ++i)
    {
        if (DX_NULL != testDesc[i].buffer)
        {
            DxTzService_Free (testDesc[i].buffer);
        }
    }

    return result;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

#ifdef DX_LINUX_TEST
int main(int argc, char **argv)
{
    DxUint containerSize = DXSFS_CONTAINER_SIZE_MAX;
#else
DxStatus testSfsSw (DxUint containerSize)
{
#endif
	DxStatus result = DX_SUCCESS;
    DxChar   name[]  = "f16b";
    DxByte   buffer[16] = {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF};

    if (DXSFS_CONTAINER_SIZE_MAX < containerSize)
    {
        TMP_PRINT "testSfsSw(main): The requested length %u is bigger then maximal one %u\n",
                containerSize, DXSFS_CONTAINER_SIZE_MAX);
        return DX_BAD_ARGUMENTS;
    }

    if (sizeof(ContainerHdr_t) + sizeof(FatHdrV1_t) +
        NUM_FAT_ENTRIES * (sizeof(FatEntryV1_t) + NAME_LEN_MAX) >=
        containerSize)
    {
        TMP_PRINT "testSfsSw(main): The requested length is too small %u\n",
                containerSize);
        return DX_BAD_ARGUMENTS;
    }

    g_Test.size = containerSize;
    g_Test.sfsBuf = DxTzService_Malloc (g_Test.size);
    if (DX_NULL == g_Test.sfsBuf)
    {
        TMP_PRINT "testSfsSw(main): Failed to allocate test buffer of %u bytes\n",
                containerSize);
        return  DX_MEM_ALLOCATION_ERROR;
    }
    DxTzService_MemSet (g_Test.sfsBuf, 0, g_Test.size);

    result = test_InitializeTerminate ();
    if (DX_SUCCESS != result)
        goto end;
    result = test_CreateContainer ();
    if (DX_SUCCESS != result)
        goto end;
    result = test_WriteRead (name, buffer, sizeof(buffer));
    if (DX_SUCCESS != result)
        goto end;
    result = test_Boundaries ();
    if (DX_SUCCESS != result)
        goto end;

end:

    if (DX_NULL != g_Test.sfsBuf)
        DxTzService_Free (g_Test.sfsBuf);

    return  result;
}
