/******************************************************************************
Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : nocs_csd.c
Version       : Initial Draft
Author        : Hisilicon hisecurity team
Created       : 2013/08/29
Last Modified :
Description   : Implementation of CSD API
Function List :
History       :
******************************************************************************/
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "hi_unf_advca.h"
#include "nocs_csd_impl.h"
#include "nocs_csd.h"
#include "hi_common.h"
#include "hi_drv_advca.h"
#include "drv_advca_ioctl.h"
#include "hi_unf_demux.h"
#include "hi_unf_descrambler.h"
#include "hi_drv_struct.h"
#include "hi_unf_otp.h"

#define SOFTWARE_VERSION "1.0.1.5\0"

static HI_S32 g_s32NagraFd = -1;
static HI_S32 g_s32CSDInitialize = 0;

static sem_t g_CSDSem;

#define P32 0xEDB88320L
static int crc_tab32_init = 0;
static HI_U32 crc_tab32[256];

/*judge CSD is initialized or not*/
#define CHECK_CSD_INIT()\
do{\
    if (0 == g_s32CSDInitialize)\
    {\
        HI_ERR_CA("CSD Not Initialize!\n");\
        return CSD_ERROR;\
    }\
    else\
    {\
        if (g_s32NagraFd <= 0)\
        {\
            g_s32NagraFd = open("/dev/" UMAP_DEVNAME_CA, O_RDWR, 0);\
            if (g_s32NagraFd < 0)\
            {\
                HI_ERR_CA("OTP open ERROR!\n");\
                return CSD_ERROR;\
            }\
        }\
    }\
}while(0)

/*judge OTP is open or not, if not, it will be opened (In CTD API, OTP must be open)*/
#define CHECK_OTP_OPEN()\
do{\
    if (g_s32NagraFd <= 0)\
    {\
        HI_ERR_CA("OTP Not Open!\n");\
        return CTD_ERROR;\
    }\
}while(0)

#define CSD_CHECK_NULL_PTR(ptr)\
do{\
    if (NULL == ptr )\
    {\
        HI_ERR_CA("null pointer.\n");\
        return CSD_ERROR;\
    }\
}while(0)

#define CSD_CHECK_PARAM(ptr)\
    do{\
        if (NULL == ptr )\
        {\
            HI_ERR_CA("null pointer.\n");\
            return CSD_ERROR_INVALID_PARAMETERS;\
        }\
    }while(0)


#define CSD_CHECK_HANDLE(hCSDHandle)\
do{\
    if ((0 == hCSDHandle) || (0xFFFFFFFF == hCSDHandle))\
    {\
        HI_ERR_CA("invalid handle.\n");\
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;\
    }\
}while(0)


const TCsdR2RCipheredProtectingKeys g_csd_xR2RCipheredProtectingKeys =
        {{0xe4, 0x21, 0x13, 0xa7, 0x99, 0xca, 0xf4, 0xc7,
          0x05, 0xff, 0x14, 0x32, 0x23, 0x32, 0x91, 0xcb}};

const TCsdUnsignedInt8 g_csd_pxCipheredContentKey[16] = 
        {0xe4, 0x21, 0x13, 0xa7, 0x99, 0xca, 0xf4, 0xc7,
         0x05, 0xff, 0x14, 0x32, 0x23, 0x32, 0x91, 0xcb};

const TCsdUnsignedInt8 g_KeySafe[16] = 
        {0xbf, 0x18, 0x6a, 0x73, 0xec, 0x86, 0x3f, 0x25,
         0x9b, 0xe8, 0x03, 0x52, 0x40, 0xd7, 0x37, 0x8c};

static void init_crc32_tab( void ) 
{
    int i,j;
    HI_U32 crc;
 
    for (i=0; i<256; i++) {
        crc = (HI_U32) i;
        for (j=0; j<8; j++) {
            if (crc & 0x00000001L) {
                crc = (crc >> 1) ^ P32;
            } else {
                crc = crc >> 1;
            }
        }
        crc_tab32[i] = crc;
    }
    crc_tab32_init = 1;
} 

static HI_U32 update_crc_32(HI_U32 crc, char c) 
{
    HI_U32 tmp, long_c;

    long_c = 0x000000ffL & c;
    tmp = crc ^ long_c;
    crc = (crc >> 8) ^ crc_tab32[tmp & 0xff];
    return crc;
} 

/*lint -save -e818 ignored by m00190812, because these function prototypes could not be changed*/
HI_U32 CalcCRC32( HI_U8* pBuff,HI_U32 length)
{
    HI_U32 crc32;
    HI_U32 i;
    crc32 = 0xffffffffL;

    if (!crc_tab32_init) {
		init_crc32_tab();
    }
    for(i=0 ; i < length ; i++) {
        crc32 = update_crc_32(crc32,(char)pBuff[i]);
    }
    crc32 ^= 0xffffffffL;
    return crc32;
}

/*pad the input data xInputData into 16 Bytes*/
TCsdStatus csd_Pad(const TCsdUnsignedInt8 *xInputData, TCsdUnsignedInt8* xOutData, TCsdUnsignedInt16 length)
{
    TCsdUnsignedInt8 zeroData[16] = {0};
    TCsdUnsignedInt16 zeroLength = 16 -length;
    
    if ((length < 1) || (length > 16))
    {
        return CSD_ERROR;
    }

    memcpy(xOutData, zeroData, zeroLength);
    memcpy(xOutData + zeroLength, xInputData, length);

    return CSD_NO_ERROR;
}

TCsdStatus csdInitialize(TCsdInitParameters*  pxInitParameters)
{
    HI_S32 s32DevFd = 0;
    HI_S32 Ret = HI_SUCCESS;

    if (0 != g_s32CSDInitialize)
    {
        HI_ERR_CA("CSD Driver Already Initialized!\n");
        return CSD_ERROR_DRIVER_ALREADY_INITIALIZED;
    }

    if (g_s32NagraFd < 0)
    {
        s32DevFd = open("/dev/" UMAP_DEVNAME_CA, O_RDWR, 0);
        if (s32DevFd < 0)
        {
            HI_ERR_CA("CSD Open Device ERROR!\n");
            return CSD_ERROR;
        }

        g_s32NagraFd = s32DevFd;
        
        Ret = sem_init(&g_CSDSem, 0, 1);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("Init semaphore ERROR!\n");
            close(s32DevFd);
            return CSD_ERROR;
        }
    }

    g_s32CSDInitialize = 1;

    return CSD_NO_ERROR;
}

TCsdStatus csdTerminate(TCsdTerminateParameters*  pxTerminateParameters)
{
    HI_S32 Ret = HI_SUCCESS;
    
    if (0 == g_s32CSDInitialize)
    {
        return CSD_ERROR;
    }
    
    if (g_s32NagraFd >= 0)
    {
        close(g_s32NagraFd);
        g_s32NagraFd = -1;

        Ret = sem_destroy(&g_CSDSem);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("Destroy semaphore ERROR!\n");
            return CSD_ERROR;
        }
    }

    g_s32CSDInitialize = 0;

    return CSD_NO_ERROR;
}

TCsdStatus csdGetApiVersion(TCsdUnsignedInt32*  pxCsdApiVersion)
{
    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(pxCsdApiVersion);

    *pxCsdApiVersion = CSDAPI_VERSION_INT;

    return CSD_NO_ERROR;
}

TCsdStatus csdGetSoftwareVersion(TCsd20CharsString  xSoftwareVersion)
{
    CHECK_CSD_INIT();
    CSD_CHECK_NULL_PTR(xSoftwareVersion);

    memcpy(xSoftwareVersion, SOFTWARE_VERSION, sizeof(SOFTWARE_VERSION));

    return CSD_NO_ERROR;
}

TCsdStatus csdGetChipRevision(TCsd20CharsString xChipRevision)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_CHAR chipVersion[5];

    CHECK_CSD_INIT();
    CSD_CHECK_NULL_PTR(xChipRevision);
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_GET_CHIP_VERSION, chipVersion);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Chip Revision ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    (HI_VOID)snprintf((HI_CHAR *)xChipRevision, sizeof(TCsd20CharsString), "%s", chipVersion);

    return CSD_NO_ERROR;
}

TCsdStatus csdGetChipExtension(TCsd20CharsString xChipExtension)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdGetNuid(TCsd4BytesVector xNuid)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32Nuid = 0;

    CHECK_CSD_INIT();
    CSD_CHECK_NULL_PTR(xNuid);
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_GET_CHIPID, &u32Nuid);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get NUID ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    xNuid[0] = (HI_U8)(u32Nuid);
    xNuid[1] = (HI_U8)(u32Nuid >> 8);
    xNuid[2] = (HI_U8)(u32Nuid >> 16);
    xNuid[3] = (HI_U8)(u32Nuid >> 24);

    return CSD_NO_ERROR;
}

TCsdStatus csdGetNuid64(TCsd8BytesVector xNuid64)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdGetNUIDCheckNumber(TCsd4BytesVector xNUIDCheckNumber)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdStatus = CSD_NO_ERROR;
    TCsd4BytesVector xNuid = {0};
    TCsdUnsignedInt8 paddedNuid[16] = {0};
    TCsdUnsignedInt8 encryptedData[16] = {0};
    TCsdR2RKeyPathHandle r2rKeyPathHandle;
    HI_U32 resultData = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr = {0};

    CHECK_CSD_INIT();
    CSD_CHECK_NULL_PTR(xNUIDCheckNumber);
    
    csdStatus = csdGetNuid(xNuid);
    if (CSD_NO_ERROR != csdStatus)
    {
        HI_ERR_CA("CSD Get Nuid Check Number Get Nuid ERROR! csdStatus = 0x%x\n", csdStatus);
        return CSD_ERROR;
    }

    csdStatus = csd_Pad(xNuid, paddedNuid, 4);
    if (CSD_NO_ERROR != csdStatus)
    {
        HI_ERR_CA("CSD Get Nuid Check Number pad Nuid ERROR! csdStatus = 0x%x\n", csdStatus);
        return CSD_ERROR;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&(r2rKeyPathHandle.handle), &stCipherAttr);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Nuid Check Number Create Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    csdStatus = csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
                                    CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
                                    g_csd_xR2RCipheredProtectingKeys,
                                    g_csd_pxCipheredContentKey,
                                    16,
                                    NULL, 0, FALSE,
                                    &r2rKeyPathHandle,
                                    paddedNuid,
                                    encryptedData,
                                    16);
    if (CSD_NO_ERROR != csdStatus)
    {
        HI_ERR_CA("CSD Get Nuid Check Number Encrypt ERROR! csdStatus = 0x%x\n", csdStatus);
        return CSD_ERROR;
    }

    resultData = CalcCRC32(encryptedData, sizeof(encryptedData));

    xNUIDCheckNumber[0] = (HI_U8)(resultData >> 24);
    xNUIDCheckNumber[1] = (HI_U8)(resultData >> 16);
    xNUIDCheckNumber[2] = (HI_U8)(resultData >> 8);
    xNUIDCheckNumber[3] = (HI_U8)(resultData);

    Ret = HI_UNF_CIPHER_DestroyHandle(r2rKeyPathHandle.handle);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Nuid Check Number Destroy Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    return CSD_NO_ERROR;
}

TCsdStatus csdGetCSCDCheckNumber(const TCsdUnsignedInt8 *xCSCData, TCsd4BytesVector xCSCDCheckNumber)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdStatus = CSD_NO_ERROR;
    TCsdUnsignedInt8 encryptedData[16] = {0};
    TCsdR2RKeyPathHandle r2rKeyPathHandle;
    HI_U32 resultData = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr = {0};

    CHECK_CSD_INIT();

    if ((NULL == xCSCData) || (NULL == xCSCDCheckNumber))
    {
        HI_ERR_CA("CSD Get CSCD Check Number Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }
    
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&(r2rKeyPathHandle.handle), &stCipherAttr);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get CSCD Check Number Create Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    csdStatus = csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
                                    CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
                                    g_csd_xR2RCipheredProtectingKeys,
                                    g_csd_pxCipheredContentKey,
                                    16,
                                    NULL, 0, FALSE,
                                    &r2rKeyPathHandle,
                                    xCSCData,
                                    encryptedData,
                                    16);
    if (CSD_NO_ERROR != csdStatus)
    {
        HI_ERR_CA("CSD Get CSCD Check Number Encrypt ERROR! csdStatus = 0x%x\n", csdStatus);
        return CSD_ERROR;
    }
    
    resultData = CalcCRC32(encryptedData, sizeof(encryptedData));

    xCSCDCheckNumber[0] = (HI_U8)(resultData >> 24);
    xCSCDCheckNumber[1] = (HI_U8)(resultData >> 16);
    xCSCDCheckNumber[2] = (HI_U8)(resultData >> 8);
    xCSCDCheckNumber[3] = (HI_U8)(resultData);

    Ret = HI_UNF_CIPHER_DestroyHandle(r2rKeyPathHandle.handle);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get CSCD Check Number Destroy Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    return CSD_NO_ERROR;
}

TCsdStatus csdGetSTBCASNCheckNumber(const TCsdUnsignedInt8 *xSTBCASNData, TCsd4BytesVector xSTBCASNCheckNumber)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdStatus = CSD_NO_ERROR;
    TCsdUnsignedInt8 paddedSTBCASN[16] = {0};
    TCsdUnsignedInt8 encryptedData[16] = {0};
    TCsdR2RKeyPathHandle r2rKeyPathHandle;
    HI_U32 resultData = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr = {0};

    CHECK_CSD_INIT();

    if ((NULL == xSTBCASNData) || (NULL == xSTBCASNCheckNumber))
    {
        HI_ERR_CA("CSD Get STBCASN Check Number Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }
    
    csdStatus = csd_Pad(xSTBCASNData, paddedSTBCASN, 4);
    if (CSD_NO_ERROR != csdStatus)
    {
        HI_ERR_CA("CSD Get STBCASN Check Number pad STBCASN ERROR! csdStatus = 0x%x\n", csdStatus);
        return CSD_ERROR;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&(r2rKeyPathHandle.handle), &stCipherAttr);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get STBCASN Check Number Create Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    csdStatus = csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
                                    CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
                                    g_csd_xR2RCipheredProtectingKeys,
                                    g_csd_pxCipheredContentKey,
                                    16,
                                    NULL, 0, FALSE,
                                    &r2rKeyPathHandle,
                                    paddedSTBCASN,
                                    encryptedData,
                                    16);
    if (CSD_NO_ERROR != csdStatus)
    {
        HI_ERR_CA("CSD Get STBCASN Check Number Encrypt ERROR! csdStatus = 0x%x\n", csdStatus);
        return CSD_ERROR;
    }
    
    resultData = CalcCRC32(encryptedData, sizeof(encryptedData));    

    xSTBCASNCheckNumber[0] = (HI_U8)(resultData >> 24);
    xSTBCASNCheckNumber[1] = (HI_U8)(resultData >> 16);
    xSTBCASNCheckNumber[2] = (HI_U8)(resultData >> 8);
    xSTBCASNCheckNumber[3] = (HI_U8)(resultData);

    Ret = HI_UNF_CIPHER_DestroyHandle(r2rKeyPathHandle.handle);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get STBCASN Check Number Destroy Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    return CSD_NO_ERROR;
}

TCsdStatus csdGetDataIntegrityCheckNumber(const TCsdUnsignedInt8* pxData, TCsdSize xDataSize, TCsd4BytesVector xDataIntegrityCheckNumber)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdStatus = CSD_NO_ERROR;
    TCsdUnsignedInt8 paddedDataIntegrity[16] = {0};
    TCsdUnsignedInt8 encryptedData[16] = {0};
    TCsdR2RKeyPathHandle r2rKeyPathHandle;
    HI_U32 resultData = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr = {0};

    CHECK_CSD_INIT();

    if ((NULL == pxData) || (NULL == xDataIntegrityCheckNumber))
    {
        HI_ERR_CA("CSD Get Data Integrity Check Number Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if ((xDataSize < 1) || (xDataSize > 16))
    {
        HI_ERR_CA("CSD Get Data Integrity Check Number Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    csdStatus = csd_Pad(pxData, paddedDataIntegrity, (TCsdUnsignedInt16)xDataSize);
    if (CSD_NO_ERROR != csdStatus)
    {
        HI_ERR_CA("CSD Get Data Integrity Check Number pad Data Integrity ERROR! csdStatus = 0x%x\n", csdStatus);
        return CSD_ERROR;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&(r2rKeyPathHandle.handle), &stCipherAttr);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Data Integrity Check Number Create Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    csdStatus = csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
                                    CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
                                    g_csd_xR2RCipheredProtectingKeys,
                                    g_csd_pxCipheredContentKey,
                                    16,
                                    NULL, 0, FALSE,
                                    &r2rKeyPathHandle,
                                    paddedDataIntegrity,
                                    encryptedData,
                                    16);
    if (CSD_NO_ERROR != csdStatus)
    {
        HI_ERR_CA("CSD Get Data Integrity Check Number Encrypt ERROR! csdStatus = 0x%x\n", csdStatus);
        return CSD_ERROR;
    }
    
    resultData = CalcCRC32(encryptedData, sizeof(encryptedData));

    xDataIntegrityCheckNumber[0] = (HI_U8)(resultData >> 24);
    xDataIntegrityCheckNumber[1] = (HI_U8)(resultData >> 16);
    xDataIntegrityCheckNumber[2] = (HI_U8)(resultData >> 8);
    xDataIntegrityCheckNumber[3] = (HI_U8)(resultData);

    Ret = HI_UNF_CIPHER_DestroyHandle(r2rKeyPathHandle.handle);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Data Integrity Check Number Destroy Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    return CSD_NO_ERROR;
}

TCsdStatus csdSetStbCaSn(const TCsd4BytesVector xStbCaSn)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32STBCASN = 0;

    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(xStbCaSn);
    
    u32STBCASN += xStbCaSn[0] << 24;
    u32STBCASN += xStbCaSn[1] << 16;
    u32STBCASN += xStbCaSn[2] << 8;
    u32STBCASN += xStbCaSn[3];

    Ret = ioctl(g_s32NagraFd, CMD_CA_SET_STBSN, &u32STBCASN);
    if (HI_ERR_CA_SETPARAM_AGAIN == Ret)
    {
        HI_ERR_CA("CSD  STBCASN Already Set!\n");
        return CSD_ERROR_OPERATION_NOT_ALLOWED;
    }
    else if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Set STBCASN ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    return CSD_NO_ERROR;
}

TCsdStatus csdGetStbCaSn(TCsd4BytesVector xStbCaSn)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32STBCASN = 0;

    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(xStbCaSn);
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_GET_STBSN, &u32STBCASN);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get STBCASN ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    xStbCaSn[0] = (HI_U8)(u32STBCASN >> 24);
    xStbCaSn[1] = (HI_U8)(u32STBCASN >> 16);
    xStbCaSn[2] = (HI_U8)(u32STBCASN >> 8);
    xStbCaSn[3] = (HI_U8)(u32STBCASN);

    return CSD_NO_ERROR;
}

TCsdStatus csdSetMarketSegmentId(const TCsd4BytesVector xMarketSegmentId)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32MarketId = 0;

    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(xMarketSegmentId);

    u32MarketId += xMarketSegmentId[0] << 24;
    u32MarketId += xMarketSegmentId[1] << 16;
    u32MarketId += xMarketSegmentId[2] << 8;
    u32MarketId += xMarketSegmentId[3];

    Ret = ioctl(g_s32NagraFd, CMD_CA_SET_MARKETID, &u32MarketId);
    if (HI_ERR_CA_SETPARAM_AGAIN == Ret)
    {
        HI_ERR_CA("CSD  Market Segment Id Already Set!\n");
        return CSD_ERROR_OPERATION_NOT_ALLOWED;
    }
    else if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Set Market Segment Id ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    return CSD_NO_ERROR;
}

TCsdStatus csdGetMarketSegmentId(TCsd4BytesVector xMarketSegmentId)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32MarketId = 0;

    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(xMarketSegmentId);
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_GET_MARKETID, &u32MarketId);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Market Segment Id ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    xMarketSegmentId[0] = (HI_U8)(u32MarketId >> 24);
    xMarketSegmentId[1] = (HI_U8)(u32MarketId >> 16);
    xMarketSegmentId[2] = (HI_U8)(u32MarketId >> 8);
    xMarketSegmentId[3] = (HI_U8)(u32MarketId);

    return CSD_NO_ERROR;
}

TCsdStatus csdSetRamUnscrambledStorageSize(TCsdUnsignedInt8*  pxPvRamUnscrambledStorageSize, TCsdUnsignedInt16   xPvLength)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdGetRamUnscrambledStorageSize(TCsdUnsignedInt8*  pxPvRamUnscrambledStorageSize, TCsdUnsignedInt16   xPvLength)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdDeactivateKeyLadder()
{
    HI_S32 Ret = HI_SUCCESS;
    
    CHECK_CSD_INIT();

    /*Deactivate CW and R2R Key Ladder*/
    Ret = ioctl(g_s32NagraFd, CMD_CA_EXT0_SETCWDEACTIVE, NULL);
    Ret |= ioctl(g_s32NagraFd, CMD_CA_EXT0_SETR2RDEACTIVE, NULL);
    Ret |= ioctl(g_s32NagraFd, CMD_CA_EXT0_SETSPDEACTIVE, NULL);
    Ret |= ioctl(g_s32NagraFd, CMD_CA_EXT0_SETCSA3DEACTIVE, NULL);
    
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Deactive Key Ladder ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    return CSD_NO_ERROR;
}

TCsdStatus csdGetKeyLadderDeactivationFlag(TCsdKeyLadderDeactivationFlag* pxKeyLadderDeactivationFlagState)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 cwDeactiveFlag = 0;
    HI_U32 r2rDeactiveFlag = 0;
    HI_U32 spDeactiveFlag = 0;
    HI_U32 csa3DeactiveFlag = 0;
    
    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(pxKeyLadderDeactivationFlagState);

    Ret = ioctl(g_s32NagraFd, CMD_CA_EXT0_GETCWDEACTIVE, &cwDeactiveFlag);
    Ret |= ioctl(g_s32NagraFd, CMD_CA_EXT0_GETR2RDEACTIVE, &r2rDeactiveFlag);
    Ret |= ioctl(g_s32NagraFd, CMD_CA_EXT0_GETSPDEACTIVE, &spDeactiveFlag);
    Ret |= ioctl(g_s32NagraFd, CMD_CA_EXT0_GETCSA3DEACTIVE, &csa3DeactiveFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Key Ladder Deactivation ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    if ((0 == cwDeactiveFlag) && (0 == r2rDeactiveFlag) && (0 == spDeactiveFlag) && (0 == csa3DeactiveFlag))
    {
        *pxKeyLadderDeactivationFlagState = CSD_ACTIVATION_FLAG_NOT_SET;
    }
    else if ((1 == cwDeactiveFlag) && (1 == r2rDeactiveFlag) && (1 == spDeactiveFlag) && (1 == csa3DeactiveFlag))
    {
        *pxKeyLadderDeactivationFlagState = CSD_ACTIVATION_FLAG_SET;
    }
    else
    {
        *pxKeyLadderDeactivationFlagState = LAST_CSD_ACTIVATION_FLAG;
        return CSD_ERROR;
    }

    return CSD_NO_ERROR;
}

TCsdStatus csdSetBootMode(TCsdBootMode xBootMode)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_ADVCA_FLASH_TYPE_E flashType;
    HI_U32 u32SelfBootDisableFlag = 1;
    HI_U32 u32BootselCtrlFlag = 1;
    CA_CMD_SUPPER_ID_S cmdSupperId;

    CHECK_CSD_INIT();

    switch (xBootMode)
    {
        case CSD_FLASH_TYPE_SPI:
        {
            flashType = HI_UNF_ADVCA_FLASH_TYPE_SPI;
            break;
        }
        case CSD_FLASH_TYPE_NAND:
        {
            flashType = HI_UNF_ADVCA_FLASH_TYPE_NAND;
            break;
        }
        default:
        {
            HI_ERR_CA("CSD Set Boot Mode Parameters Invalid!\n");
            return CSD_ERROR_INVALID_PARAMETERS;
        }
    }
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_SET_SELFBOOT, &u32SelfBootDisableFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Set Self Boot Flag ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    cmdSupperId.enCmdChildID = CMD_CHILD_ID_SET_BOOTMODE_0;
    memcpy(cmdSupperId.pu8ParamBuf, &flashType, 1);
    cmdSupperId.u32ParamLen = 1;
    Ret = ioctl(g_s32NagraFd, CMD_CA_SUPPER_ID, &cmdSupperId);
    if (HI_ERR_CA_SETPARAM_AGAIN == Ret)
    {
        HI_ERR_CA("CSD Boot Mode Already Set!\n");
        return CSD_ERROR_OPERATION_NOT_ALLOWED;
    }
    else if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Set Boot Mode ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    Ret = ioctl(g_s32NagraFd, CMD_CA_SET_BOOTSEL_CTRL, &u32BootselCtrlFlag);
    if (HI_ERR_CA_SETPARAM_AGAIN == Ret)
    {
        HI_ERR_CA("CSD Bootsel Ctrl Flag Already Set!\n");
        return CSD_ERROR_OPERATION_NOT_ALLOWED;
    }
    else if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Set Bootsel Ctrl Flag ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    return CSD_NO_ERROR;
}

TCsdStatus csdGetBootMode(TCsdBootMode* pxBootMode)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_ADVCA_FLASH_TYPE_E flashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;
    CA_CMD_SUPPER_ID_S cmdSupperId;
    HI_U32 u32Value = 0;
    HI_U32 u32BootselCtrlFlag = 0;
    
    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(pxBootMode);

    Ret = ioctl(g_s32NagraFd, CMD_CA_GET_BOOT_SEL_LOCK_1, &u32Value);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Boot Mode Lock ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    if (1 != u32Value)
    {
        HI_ERR_CA("Boot mode 1 is not locked!\n");
        return CSD_ERROR;
    }

    cmdSupperId.enCmdChildID = CMD_CHILD_ID_GET_BOOTMODE_1;
    Ret = ioctl(g_s32NagraFd, CMD_CA_SUPPER_ID, &cmdSupperId);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Boot Mode ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    memcpy(&u32Value, cmdSupperId.pu8ParamBuf, 1);
    if (0 != u32Value)
    {
        HI_ERR_CA("Boot mode 1 is not locked to 0!\n");
        return CSD_ERROR;
    }

    Ret = ioctl(g_s32NagraFd, CMD_CA_GET_BOOTSEL_CTRL, &u32BootselCtrlFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Bootsel Ctrl Flag ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    if (1 == u32BootselCtrlFlag)
    {
        cmdSupperId.enCmdChildID = CMD_CHILD_ID_GET_BOOTMODE_0;
        Ret = ioctl(g_s32NagraFd, CMD_CA_SUPPER_ID, &cmdSupperId);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Get Boot Mode ERROR! Ret = 0x%x\n", Ret);
            return CSD_ERROR;
        }

        memcpy(&flashType, cmdSupperId.pu8ParamBuf, 1);

        switch (flashType)
        {
            case HI_UNF_ADVCA_FLASH_TYPE_SPI:
            {
                *pxBootMode = CSD_FLASH_TYPE_SPI;
                break;
            }
            case HI_UNF_ADVCA_FLASH_TYPE_NAND:
            {
                *pxBootMode = CSD_FLASH_TYPE_NAND;
                break;
            }
            default:
            {
                *pxBootMode = LAST_CSD_FLASH_TYPE;
                return CSD_ERROR;
            }
        }
    }
    else
    {
        *pxBootMode = CSD_FLASH_TYPE_UNPROGRAMMED;
    } 
 
    return CSD_NO_ERROR;
}

TCsdStatus csdEnableScs()
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32SelfBootDisableFlag = 1;

    CHECK_CSD_INIT();

    Ret = ioctl(g_s32NagraFd, CMD_CA_SET_SELFBOOT, &u32SelfBootDisableFlag);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Set Self Boot Flag ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    Ret = ioctl(g_s32NagraFd, CMD_CA_SET_SCSACTIVE, NULL);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Enable SCS ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    return CSD_NO_ERROR;
}

TCsdStatus csdGetScsActivationFlag(TCsdScsActivationFlag* pxScsActivationFlagState)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 scsActivation = 0;

    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(pxScsActivationFlagState);
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_GET_SCSACTIVE, &scsActivation);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get SCS Activation Flag ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    if (0 == scsActivation)
    {
        *pxScsActivationFlagState = CSD_ACTIVATION_FLAG_NOT_SET;
    }
    else if (1 == scsActivation)
    {
        *pxScsActivationFlagState = CSD_ACTIVATION_FLAG_SET;
    }
    else
    {
        *pxScsActivationFlagState = LAST_CSD_ACTIVATION_FLAG;
        return CSD_ERROR;
    }

    return CSD_NO_ERROR;
}

TCsdStatus csdSetScsPv(TCsdScsPvId            xScsPvParamsId,
                        TCsdScsPvPathHandle*  pxPvPathHandle, 
                        TCsdUnsignedInt16      xPvLength,
                        TCsdUnsignedInt8*     pxPvValue)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdGetScsPv(TCsdScsPvId            xScsPvParamsId,
                        TCsdScsPvPathHandle*  pxPvPathHandle,
                        TCsdUnsignedInt16      xPvLength,
                        TCsdUnsignedInt8*     pxPvValue)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdSetScsTotalAreaSize(TCsdScsTotalAreaSize xScsTotalAreaSize)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdGetScsTotalAreaSize(TCsdScsTotalAreaSize* pxTotalAreaSize)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdEnableRamScrambling()
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdGetScramblingActivationFlag(TCsdActivationFlag* pxScramblingActivationFlagState)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdEnableFlashProtection()
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdGetFlashProtectionActivationFlag(TCsdActivationFlag* pxFlashProtectionActivationFlagState)
{
    return CSD_ERROR_OPERATION_NOT_SUPPORTED;
}

TCsdStatus csdSelectDebugInterfaceProtectionLevel(TCsdDebugInterfaceAccessMode xDebugInterfaceProtectionLevel)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_ADVCA_JTAG_MODE_E jtagMode;

    CHECK_CSD_INIT();

    switch (xDebugInterfaceProtectionLevel)
    {
        case CSD_DEBUG_INTERFACE_ACCESS_MODE_OPEN:
        {
            jtagMode = HI_UNF_ADVCA_JTAG_MODE_OPEN;
            break;
        }
        case CSD_DEBUG_INTERFACE_ACCESS_MODE_PASSWORD_PROTECTED:
        {
            jtagMode = HI_UNF_ADVCA_JTAG_MODE_PROTECT;
            break;
        }
        case CSD_DEBUG_INTERFACE_ACCESS_MODE_CLOSED:
        {
            jtagMode = HI_UNF_ADVCA_JTAG_MODE_CLOSED;
            break;
        }
        case CSD_DEBUG_INTERFACE_ACCESS_MODE_INCONSISTENT_STATE:
        default:
        {
            HI_ERR_CA("CSD Set Debug Interface Protection Level Parameters Invalid!\n");
            return CSD_ERROR_INVALID_PARAMETERS;
        }
    }
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_SET_JTAGPRTMODE, &jtagMode);
    if (HI_ERR_CA_NOT_SUPPORT == Ret)
    {
        HI_ERR_CA("CSD Debug Interface Protection Level Already Set!\n");
        return CSD_ERROR_OPERATION_NOT_ALLOWED;
    }
    else if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Set Debug Interface Protection Level ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    return CSD_NO_ERROR;
}

TCsdStatus csdGetDebugInterfaceProtectionLevel(TCsdDebugInterfaceAccessMode* pxDebugInterfaceProtectionLevel)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_ADVCA_JTAG_MODE_E jtagMode = HI_UNF_ADVCA_JTAG_MODE_BUTT;

    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(pxDebugInterfaceProtectionLevel);
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_GET_JTAGPRTMODE, &jtagMode);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get Debug Interface Protection Level ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }

    switch (jtagMode)
    {
        case HI_UNF_ADVCA_JTAG_MODE_OPEN:
        {
            *pxDebugInterfaceProtectionLevel = CSD_DEBUG_INTERFACE_ACCESS_MODE_OPEN;
            break;
        }
        case HI_UNF_ADVCA_JTAG_MODE_PROTECT:
        {
            *pxDebugInterfaceProtectionLevel = CSD_DEBUG_INTERFACE_ACCESS_MODE_PASSWORD_PROTECTED;
            break;
        }
        case HI_UNF_ADVCA_JTAG_MODE_CLOSED:
        {
            *pxDebugInterfaceProtectionLevel = CSD_DEBUG_INTERFACE_ACCESS_MODE_CLOSED;
            break;
        }
        default:
        {
            *pxDebugInterfaceProtectionLevel = LAST_CSD_DEBUG_INTERFACE_ACCESS_MODE;
            return CSD_ERROR;
        }
    }

    return CSD_NO_ERROR;
}

TCsdStatus csdGetDvrKey(TCsdUnsignedInt8 xDvrKey[16])
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdStatus = CSD_NO_ERROR;
    TCsdUnsignedInt8 encryptedData[16] = {0};
    TCsdR2RKeyPathHandle r2rKeyPathHandle;
    HI_UNF_CIPHER_ATTS_S stCipherAttr = {0};

    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(xDvrKey);

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&(r2rKeyPathHandle.handle), &stCipherAttr);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get DVR Key Create Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    csdStatus = csdDecryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
                                    CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
                                    g_csd_xR2RCipheredProtectingKeys,
                                    g_csd_pxCipheredContentKey,
                                    16,
                                    NULL, 0, FALSE,
                                    &r2rKeyPathHandle,
                                    g_KeySafe,
                                    encryptedData,
                                    16);
    if (CSD_NO_ERROR != csdStatus)
    {
        HI_ERR_CA("CSD Get DVR Key Encrypt ERROR! csdStatus = 0x%x\n", csdStatus);
        return CSD_ERROR;
    }
    
    memcpy(xDvrKey, encryptedData, 16);

    Ret = HI_UNF_CIPHER_DestroyHandle(r2rKeyPathHandle.handle);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Get DVR Key Destroy Handle ERROR! Ret = 0x%x\n", Ret);
        return CSD_ERROR;
    }
    
    return CSD_NO_ERROR;
}

TCsdStatus csdEncryptDataWithClearTextHostKey(TCsdR2RAlgorithm            xAlgorithm,
                                        TCsdR2RCryptoOperationMode  xMode,
                                  const TCsdUnsignedInt8*          pxClearTextHostKey,
                                        TCsdSize                    xClearTextHostKeySize,
                                  const TCsdUnsignedInt8*          pxInitializationVector,
                                        TCsdSize                    xInitializationVectorSize,
                                        TCsdBoolean                    xRefreshIv,
                                        TCsdR2RKeyPathHandle*      pxR2RKeyPathHandle,
                                  const TCsdUnsignedInt8*          pxInputData,
                                        TCsdUnsignedInt8*          pxOutputData,
                                        TCsdSize                    xDataSize)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U32  UnitSize = 16;
    HI_MMZ_BUF_S stTmpBuf;

    CHECK_CSD_INIT();
    
    memset((HI_VOID*)&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    switch (xAlgorithm)
    {
        case CSD_R2R_ALGORITHM_AES_128 :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            UnitSize = 16;
            break;
        case CSD_R2R_ALGORITHM_TDES_K1K2K1:
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
            UnitSize = 8;
            break;
        default:
        {
            HI_ERR_CA("CSD Encrypt Data With Clear Text HostKey Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    switch (xMode)
    {
        case CSD_R2R_CRYPTO_OPERATION_MODE_ECB:
        {
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
            break;
        }
        case CSD_R2R_CRYPTO_OPERATION_MODE_CBC:
        {
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
            break;
        }
        default:
        {
            HI_ERR_CA("CSD Encrypt Data With Clear Text HostKey Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    /*clear text host key should be 16 Bytes long*/
    if ((16 != xClearTextHostKeySize) || (NULL == pxClearTextHostKey))
    {
        HI_ERR_CA("CSD Encrypt Data With Clear Text HostKey Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if ((NULL == pxInputData) || (NULL == pxOutputData))
    {
        HI_ERR_CA("CSD Encrypt Data With Clear Text HostKey Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }
    
    /*the size of the input data block must be a multiple of 8 bytes if it must be encrypted with the TDES algorithm or
     a multiple of 16 bytes if it must be encrypted with the AES algorithm*/
    if (0 != (xDataSize % UnitSize))
    {
        HI_ERR_CA("CSD Encrypt Data With Clear Text HostKey Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    /*IV should be 16 Bytes in AES and 8 Bytes in TDES*/
    if ((CSD_R2R_CRYPTO_OPERATION_MODE_CBC  == xMode) && xRefreshIv)
    {
        if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
        {
            HI_ERR_CA("CSD Encrypt Data With Clear Text HostKey Parameters Invalid!\n");
            return CSD_ERROR_INVALID_PARAMETERS;
        }
    }

    if (NULL == pxR2RKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }
    CSD_CHECK_HANDLE(pxR2RKeyPathHandle->handle);

    CipherCtrl.bKeyByCA = HI_FALSE;

    memcpy((HI_VOID*)CipherCtrl.u32Key, pxClearTextHostKey, xClearTextHostKeySize);

    if (xRefreshIv)
    {
        CipherCtrl.stChangeFlags.bit1IV = 1;
        memcpy((HI_VOID*)CipherCtrl.u32IV, pxInitializationVector, xInitializationVectorSize);
    }

    Ret = sem_wait(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Wait semaphore ERROR!\n");
        return CSD_ERROR;
    }

    Ret = HI_UNF_CIPHER_ConfigHandle(pxR2RKeyPathHandle->handle, &CipherCtrl);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Config Handle ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    strncpy(stTmpBuf.bufname, "NagraEncrypt", MAX_BUFFER_NAME_SIZE);
    stTmpBuf.bufsize = xDataSize;
    stTmpBuf.overflow_threshold = 100;
    stTmpBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&stTmpBuf);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("HI_MMZ_Malloc failed:%x\n",Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    memcpy(stTmpBuf.user_viraddr,pxInputData,xDataSize);

    Ret = HI_UNF_CIPHER_Encrypt(pxR2RKeyPathHandle->handle, stTmpBuf.phyaddr, stTmpBuf.phyaddr, xDataSize);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Encrypt ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto MMZ_FREE;
    }
    memcpy(pxOutputData,stTmpBuf.user_viraddr,xDataSize);

MMZ_FREE:
    (HI_VOID)HI_MMZ_Free(&stTmpBuf);

SEM_POST:
    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }

    return csdRet;
}

TCsdStatus csdDecryptDataWithClearTextHostKey(TCsdR2RAlgorithm            xAlgorithm,
                                        TCsdR2RCryptoOperationMode  xMode,
                                  const TCsdUnsignedInt8*          pxClearTextHostKey,
                                        TCsdSize                    xClearTextHostKeySize,
                                  const TCsdUnsignedInt8*          pxInitializationVector,
                                        TCsdSize                    xInitializationVectorSize,
                                        TCsdBoolean                    xRefreshIv,
                                        TCsdR2RKeyPathHandle*      pxR2RKeyPathHandle,
                                  const TCsdUnsignedInt8*          pxInputData,
                                        TCsdUnsignedInt8*          pxOutputData,
                                        TCsdSize                    xDataSize)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U32  UnitSize = 16;
    HI_MMZ_BUF_S stTmpBuf;

    CHECK_CSD_INIT();
    
    memset((HI_VOID*)&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    switch (xAlgorithm)
    {
        case CSD_R2R_ALGORITHM_AES_128 :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            UnitSize = 16;
            break;
        case CSD_R2R_ALGORITHM_TDES_K1K2K1:
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
            UnitSize = 8;
            break;
        default:
        {
            HI_ERR_CA("CSD Encrypt Data With Clear Text HostKey Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    switch (xMode)
    {
        case CSD_R2R_CRYPTO_OPERATION_MODE_ECB:
        {
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
            break;
        }
        case CSD_R2R_CRYPTO_OPERATION_MODE_CBC:
        {
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
            break;
        }
        default:
        {
            HI_ERR_CA("CSD Decrypt Data With Clear Text HostKey Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    /*clear text host key should be 16 Bytes long*/
    if ((16 != xClearTextHostKeySize) || (NULL == pxClearTextHostKey))
    {
        HI_ERR_CA("CSD Decrypt Data With Clear Text HostKey Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if ((NULL == pxInputData) || (NULL == pxOutputData))
    {
        HI_ERR_CA("CSD Decrypt Data With Clear Text HostKey Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }
    
    /*the size of the input data block must be a multiple of 8 bytes if it must be encrypted with the TDES algorithm or
     a multiple of 16 bytes if it must be encrypted with the AES algorithm*/
    if (0 != (xDataSize % UnitSize))
    {
        HI_ERR_CA("CSD Encrypt Data With Clear Text HostKey Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    /*IV should be 16 Bytes in AES and 8 Bytes in TDES*/
    if ((CSD_R2R_CRYPTO_OPERATION_MODE_CBC  == xMode) && xRefreshIv)
    {
        if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
        {
            HI_ERR_CA("CSD Encrypt Data With Clear Text HostKey Parameters Invalid!\n");
            return CSD_ERROR_INVALID_PARAMETERS;
        }
    }

    if (NULL == pxR2RKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }
    CSD_CHECK_HANDLE(pxR2RKeyPathHandle->handle);

    CipherCtrl.bKeyByCA = HI_FALSE;

    memcpy((HI_VOID*)CipherCtrl.u32Key, pxClearTextHostKey, xClearTextHostKeySize);        

    if (xRefreshIv)
    {
        CipherCtrl.stChangeFlags.bit1IV = 1;
        memcpy((HI_VOID*)CipherCtrl.u32IV, pxInitializationVector, xInitializationVectorSize);
    }

    Ret = sem_wait(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Wait semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    Ret = HI_UNF_CIPHER_ConfigHandle(pxR2RKeyPathHandle->handle, &CipherCtrl);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Config Handle ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    strncpy(stTmpBuf.bufname, "NagraDecrypt", MAX_BUFFER_NAME_SIZE);
    stTmpBuf.bufsize = xDataSize;
    stTmpBuf.overflow_threshold = 100;
    stTmpBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&stTmpBuf);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("HI_MMZ_Malloc failed:%x\n",Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    memcpy(stTmpBuf.user_viraddr,pxInputData,xDataSize);

    Ret = HI_UNF_CIPHER_Decrypt(pxR2RKeyPathHandle->handle, stTmpBuf.phyaddr, stTmpBuf.phyaddr, xDataSize);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Decrypt ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto MMZ_FREE;
    }
    memcpy(pxOutputData,stTmpBuf.user_viraddr,xDataSize);

MMZ_FREE:
    (HI_VOID)HI_MMZ_Free(&stTmpBuf);

SEM_POST:
    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    return csdRet;
}

TCsdStatus csdEncryptDataWithSecretContentKey(TCsdR2RAlgorithm                xAlgorithm,
                                        TCsdR2RCryptoOperationMode      xMode,
                                  const TCsdR2RCipheredProtectingKeys   xR2RCipheredProtectingKeys,
                                  const TCsdUnsignedInt8*              pxCipheredContentKey,
                                        TCsdSize                        xCipheredContentKeySize,
                                  const TCsdUnsignedInt8*              pxInitializationVector,
                                        TCsdSize                        xInitializationVectorSize,
                                        TCsdBoolean                        xRefreshIv,
                                        TCsdR2RKeyPathHandle*          pxR2RKeyPathHandle,
                                  const TCsdUnsignedInt8*              pxInputData,
                                        TCsdUnsignedInt8*              pxOutputData,
                                        TCsdSize                        xDataSize)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U32  UnitSize = 16;
    HI_MMZ_BUF_S stTmpBuf;

    HI_UNF_ADVCA_ALG_TYPE_E r2rAlg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    CA_CRYPTPM_S cryptPm;

    CHECK_CSD_INIT();
    
    memset((HI_VOID*)&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    switch (xAlgorithm)
    {
        case CSD_R2R_ALGORITHM_AES_128 :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            UnitSize = 16;
            break;
        case CSD_R2R_ALGORITHM_TDES_K1K2K1:
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
            UnitSize = 8;
            break;
        default:
        {
            HI_ERR_CA("CSD Encrypt Data With Secret Content Key Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    switch (xMode)
    {
        case CSD_R2R_CRYPTO_OPERATION_MODE_ECB:
        {
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
            break;
        }
        case CSD_R2R_CRYPTO_OPERATION_MODE_CBC:
        {
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
            break;
        }
        default:
        {
            HI_ERR_CA("CSD Encrypt Data With Secret Content Key Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    /*ciphered content key should be 16 Bytes long*/
    if ((16 != xCipheredContentKeySize) || (NULL == pxCipheredContentKey))
    {
        HI_ERR_CA("CSD Encrypt Data With Secret Content Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if (NULL == xR2RCipheredProtectingKeys)
    {
        HI_ERR_CA("CSD Encrypt Data With Secret Content Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if ((NULL == pxInputData) || (NULL == pxOutputData))
    {
        HI_ERR_CA("CSD Encrypt Data With Secret Content Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }
    
    /*the size of the input data block must be a multiple of 8 bytes if it must be encrypted with the TDES algorithm or
        a multiple of 16 bytes if it must be encrypted with the AES algorithm*/
    if (0 != (xDataSize % UnitSize))
    {
        HI_ERR_CA("CSD Encrypt Data With Secret Content Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    /*IV should be 16 Bytes in AES and 8 Bytes in TDES*/
    if ((CSD_R2R_CRYPTO_OPERATION_MODE_CBC  == xMode) && xRefreshIv)
    {
        if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
        {
            HI_ERR_CA("CSD Encrypt Data With Secret Content Key Parameters Invalid!\n");
            return CSD_ERROR_INVALID_PARAMETERS;
        }
    }

    if (NULL == pxR2RKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }
    CSD_CHECK_HANDLE(pxR2RKeyPathHandle->handle);

    CipherCtrl.bKeyByCA = HI_TRUE;

    memcpy((HI_VOID*)CipherCtrl.u32Key, pxCipheredContentKey, xCipheredContentKeySize);

    if (xRefreshIv)
    {
        CipherCtrl.stChangeFlags.bit1IV = 1;
        memcpy((HI_VOID*)CipherCtrl.u32IV, pxInitializationVector, xInitializationVectorSize);
    }

    Ret = sem_wait(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Wait semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    /* perform ciphered protecting level 1 */
    cryptPm.ladder = HI_UNF_ADVCA_KEYLADDER_LEV1;
    memcpy((HI_VOID*)cryptPm.pDin, xR2RCipheredProtectingKeys[0], 16);
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_R2R_SETALG, &r2rAlg);
    Ret |= ioctl(g_s32NagraFd, CMD_CA_R2R_CRYPT, &cryptPm);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Encrypt Data With Secret Content Key Genarate Private Key ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    Ret = HI_UNF_CIPHER_ConfigHandle(pxR2RKeyPathHandle->handle, &CipherCtrl);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Config Handle ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    strncpy(stTmpBuf.bufname, "NagraEncrypt", MAX_BUFFER_NAME_SIZE);
    stTmpBuf.bufsize = xDataSize;
    stTmpBuf.overflow_threshold = 100;
    stTmpBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&stTmpBuf);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("HI_MMZ_Malloc failed:%x\n",Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    memcpy(stTmpBuf.user_viraddr,pxInputData,xDataSize);

    Ret = HI_UNF_CIPHER_Encrypt(pxR2RKeyPathHandle->handle, stTmpBuf.phyaddr, stTmpBuf.phyaddr, xDataSize);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Encrypt ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto MMZ_FREE;
    }
    memcpy(pxOutputData,stTmpBuf.user_viraddr,xDataSize);

MMZ_FREE:
    (HI_VOID)HI_MMZ_Free(&stTmpBuf);

SEM_POST:
    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    return csdRet;
}

TCsdStatus csdDecryptDataWithSecretContentKey(TCsdR2RAlgorithm                xAlgorithm,
                                        TCsdR2RCryptoOperationMode      xMode,
                                  const TCsdR2RCipheredProtectingKeys   xR2RCipheredProtectingKeys,
                                  const TCsdUnsignedInt8*              pxCipheredContentKey,
                                        TCsdSize                        xCipheredContentKeySize,
                                  const TCsdUnsignedInt8*              pxInitializationVector,
                                        TCsdSize                        xInitializationVectorSize,
                                        TCsdBoolean                        xRefreshIv,
                                        TCsdR2RKeyPathHandle*          pxR2RKeyPathHandle,
                                  const TCsdUnsignedInt8*              pxInputData,
                                        TCsdUnsignedInt8*              pxOutputData,
                                        TCsdSize                        xDataSize)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U32  UnitSize = 16;
    HI_MMZ_BUF_S stTmpBuf;

    HI_UNF_ADVCA_ALG_TYPE_E r2rAlg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    CA_CRYPTPM_S cryptPm;

    CHECK_CSD_INIT();
    
    memset((HI_VOID*)&CipherCtrl,0,sizeof(HI_UNF_CIPHER_CTRL_S));
    switch (xAlgorithm)
    {
        case CSD_R2R_ALGORITHM_AES_128 :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            UnitSize = 16;
            break;
        case CSD_R2R_ALGORITHM_TDES_K1K2K1:
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
            UnitSize = 8;
            break;
        default:
        {
            HI_ERR_CA("CSD Encrypt Data With Secret Content Key Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    switch (xMode)
    {
        case CSD_R2R_CRYPTO_OPERATION_MODE_ECB:
        {
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
            break;
        }
        case CSD_R2R_CRYPTO_OPERATION_MODE_CBC:
        {
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
            break;
        }
        default:
        {
            HI_ERR_CA("CSD Decrypt Data With Secret Content Key Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    /*ciphered content key should be 16 Bytes long*/
    if ((16 != xCipheredContentKeySize) || (NULL == pxCipheredContentKey))
    {
        HI_ERR_CA("CSD Decrypt Data With Secret Content Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if (NULL == xR2RCipheredProtectingKeys)
    {
        HI_ERR_CA("CSD Decrypt Data With Secret Content Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if ((NULL == pxInputData) || (NULL == pxOutputData))
    {
        HI_ERR_CA("CSD Decrypt Data With Secret Content Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }
    
    /*the size of the input data block must be a multiple of 8 bytes if it must be encrypted with the TDES algorithm or
     a multiple of 16 bytes if it must be encrypted with the AES algorithm*/
    if (0 != (xDataSize % UnitSize))
    {
        HI_ERR_CA("CSD Encrypt Data With Secret Content Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }
    
    /*IV should be 16 Bytes in AES and 8 Bytes in TDES*/
    if ((CSD_R2R_CRYPTO_OPERATION_MODE_CBC  == xMode) && xRefreshIv)
    {
        if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
        {
            HI_ERR_CA("CSD Encrypt Data With Secret Content Key Parameters Invalid!\n");
            return CSD_ERROR_INVALID_PARAMETERS;
        }
    }

    if (NULL == pxR2RKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }
    CSD_CHECK_HANDLE(pxR2RKeyPathHandle->handle);

    CipherCtrl.bKeyByCA = HI_TRUE;

    memcpy((HI_VOID*)CipherCtrl.u32Key, pxCipheredContentKey, xCipheredContentKeySize);

    if (xRefreshIv)
    {
        CipherCtrl.stChangeFlags.bit1IV = 1;
        memcpy((HI_VOID*)CipherCtrl.u32IV, pxInitializationVector, xInitializationVectorSize);
    }

    Ret = sem_wait(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Wait semaphore ERROR!\n");
        return CSD_ERROR;
    }

    /* perform ciphered protecting level 1 */
    cryptPm.ladder = HI_UNF_ADVCA_KEYLADDER_LEV1;
    memcpy((HI_VOID*)cryptPm.pDin, xR2RCipheredProtectingKeys[0], 16);
    
    Ret = ioctl(g_s32NagraFd, CMD_CA_R2R_SETALG, &r2rAlg);
    Ret |= ioctl(g_s32NagraFd, CMD_CA_R2R_CRYPT, &cryptPm);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Decrypt Data With Secret Content Key Genarate Private Key ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    Ret = HI_UNF_CIPHER_ConfigHandle(pxR2RKeyPathHandle->handle, &CipherCtrl);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Config Handle ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    strncpy(stTmpBuf.bufname, "NagraDecrypt", MAX_BUFFER_NAME_SIZE);
    stTmpBuf.bufsize = xDataSize;
    stTmpBuf.overflow_threshold = 100;
    stTmpBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&stTmpBuf);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("HI_MMZ_Malloc failed:%x\n",Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    memcpy(stTmpBuf.user_viraddr,pxInputData,xDataSize);

    Ret = HI_UNF_CIPHER_Decrypt(pxR2RKeyPathHandle->handle, stTmpBuf.phyaddr, stTmpBuf.phyaddr, xDataSize);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Decrypt ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto MMZ_FREE;
    }
    memcpy(pxOutputData,stTmpBuf.user_viraddr,xDataSize);

MMZ_FREE:
    (HI_VOID)HI_MMZ_Free(&stTmpBuf);

SEM_POST:
    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    return csdRet;
}

TCsdStatus csdSetClearTextDscHostKeys(TCsdUnsignedInt16         xEmi,
                                  const TCsdUnsignedInt8*        pxClearTextDscOddHostKey,
                                        TCsdSize                  xClearTextDscOddHostKeySize,
                                  const TCsdUnsignedInt8*        pxClearTextDscEvenHostKey,
                                        TCsdSize                  xClearTextDscEvenHostKeySize,
                                        TCsdDscKeyPathHandle*    pxDscKeyPathHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_U32 u32KeySize = 8;
    HI_U8 u32IV[16] = {0};
    HI_BOOL bOddKeySet = HI_FALSE;
    HI_BOOL bEvenKeySet = HI_FALSE;

    CHECK_CSD_INIT();

    switch (xEmi)
    {
        case DVB_CSA_V2 :
            u32KeySize = 8;
            break;
        case DVB_CSA_V3:
        case PAYLOAD_AES_CBC_IDSA :
        case PAYLOAD_AES_ECB :
        case PAYLOAD_AES_CBC_CI :
            u32KeySize = 16;
            break;
        default:
        {
            HI_ERR_CA("CSD Set Clear Text DSC Host Keys Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    if ((NULL == pxClearTextDscOddHostKey) && (NULL == pxClearTextDscEvenHostKey))
    {
        HI_ERR_CA("Invalid host key!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if (NULL != pxClearTextDscOddHostKey)
    {
        if (u32KeySize == xClearTextDscOddHostKeySize)
        {
            bOddKeySet = HI_TRUE;      //Odd key should be set
        }
        else
        {
            HI_ERR_CA("Invalid Odd host key kize, expect %d, real %d !\n",u32KeySize,xClearTextDscOddHostKeySize);
            return CSD_ERROR_INVALID_PARAMETERS;
        }
    }
    
    if (NULL != pxClearTextDscEvenHostKey)
    {
        if (u32KeySize == xClearTextDscEvenHostKeySize)
        {
            bEvenKeySet = HI_TRUE;      //Even key should be set
        }
        else
        {
            HI_ERR_CA("Invalid Even host key kize, expect %d, real %d !\n",u32KeySize,xClearTextDscEvenHostKeySize);
            return CSD_ERROR_INVALID_PARAMETERS;
        }
    }

    if (NULL == pxDscKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }
    CSD_CHECK_HANDLE(pxDscKeyPathHandle->hDescrambler);

    Ret = sem_wait(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Wait semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    if ((PAYLOAD_AES_CBC_IDSA == xEmi) || (PAYLOAD_AES_CBC_CI == xEmi))
    {
        /*IV should be set in CBC mode*/
        memset(u32IV, 0, sizeof(u32IV));
		
        if (PAYLOAD_AES_CBC_CI == xEmi)
        {
            CSD_CHECK_NULL_PTR(pxDscKeyPathHandle->dscIVAesCIplusPayload);
            memcpy(u32IV, pxDscKeyPathHandle->dscIVAesCIplusPayload, sizeof(pxDscKeyPathHandle->dscIVAesCIplusPayload));
        }

        if (bEvenKeySet)
        {
            Ret = HI_UNF_DMX_SetDescramblerEvenIVKey(pxDscKeyPathHandle->hDescrambler, u32IV);
        }
        
        if (bOddKeySet)
        {
            Ret |= HI_UNF_DMX_SetDescramblerOddIVKey(pxDscKeyPathHandle->hDescrambler, u32IV);
        }

        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Set Descrambler IV ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
            goto SEM_POST;
        }
    }
    
    /*set the clear text host keys*/
    if (bOddKeySet)
    {
        Ret = HI_UNF_DMX_SetDescramblerOddKey(pxDscKeyPathHandle->hDescrambler, pxClearTextDscOddHostKey);
    }

    if (bEvenKeySet)
    {
        Ret |= HI_UNF_DMX_SetDescramblerEvenKey(pxDscKeyPathHandle->hDescrambler, pxClearTextDscEvenHostKey);
    }
    
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Set Descrambler Key ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
    }

SEM_POST:
    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }

    return csdRet;
}

TCsdStatus csdSetProtectedDscContentKeys(TCsdUnsignedInt16               xEmi,
                                  const TCsdDscCipheredProtectingKeys   xDscCipheredProtectingKeys,
                                  const TCsdUnsignedInt8*              pxCipheredDscOddContentKey,
                                        TCsdSize                        xCipheredDscOddContentKeySize,
                                  const TCsdUnsignedInt8*              pxCipheredDscEvenContentKey,
                                        TCsdSize                        xCipheredDscEvenContentKeySize,
                                        TCsdDscKeyPathHandle*          pxDscKeyPathHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_ADVCA_ALG_TYPE_E enAlg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    CA_CRYPTPM_S cryptPm;
    HI_U32 u32KeySize = 8;
    HI_U8 u32IV[16] = {0};
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_BOOL bOddKeySet = HI_FALSE;
    HI_BOOL bEvenKeySet = HI_FALSE;
    
    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(xDscCipheredProtectingKeys);

    switch (xEmi)
    {
        case DVB_CSA_V2 :
            u32KeySize = 8;
            break;
        case DVB_CSA_V3:
        case PAYLOAD_AES_CBC_IDSA :
        case PAYLOAD_AES_ECB:
        case PAYLOAD_AES_CBC_CI :
            u32KeySize = 16;
            break;
        default:
        {
            HI_ERR_CA("CSD Set Protected DSC Content Keys Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }
    }

    if ((NULL == pxCipheredDscOddContentKey) && (NULL == pxCipheredDscEvenContentKey))
    {
        HI_ERR_CA("Invalid content key!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if (NULL != pxCipheredDscOddContentKey)
    {
        if (u32KeySize == xCipheredDscOddContentKeySize)
        {
            bOddKeySet = HI_TRUE;      //Odd key should be set
        }
        else
        {
            HI_ERR_CA("Invalid Odd content key kize, expect %d, real %d !\n",u32KeySize,xCipheredDscOddContentKeySize);
            return CSD_ERROR_INVALID_PARAMETERS;
        } 
    }
    
    if (NULL != pxCipheredDscEvenContentKey)
    {
        if (u32KeySize == xCipheredDscEvenContentKeySize)
        {
            bEvenKeySet = HI_TRUE;      //Even key should be set
        }
        else
        {
            HI_ERR_CA("Invalid Even content key kize, expect %d, real %d !\n",u32KeySize,xCipheredDscEvenContentKeySize);
            return CSD_ERROR_INVALID_PARAMETERS;
        }
    }

    if (NULL == pxDscKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }
    CSD_CHECK_HANDLE(pxDscKeyPathHandle->hDescrambler);

    Ret = sem_wait(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Wait semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    if (DVB_CSA_V2 == xEmi)
    {
        Ret |= ioctl(g_s32NagraFd, CMD_CA_DVB_SETALG, &enAlg);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Set DVB Properties ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
            goto SEM_POST;
        }

        /* perform ciphered protecting level 1 */
        cryptPm.ladder = HI_UNF_ADVCA_KEYLADDER_LEV1;
        memcpy((HI_VOID*)cryptPm.pDin, xDscCipheredProtectingKeys, 16);
        Ret = ioctl(g_s32NagraFd, CMD_CA_DVB_CRYPT, &cryptPm);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Set Protected DSC Content Keys Genarate Private Key ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
            goto SEM_POST;
        }
    }
    else if (DVB_CSA_V3 == xEmi)
    {
        Ret |= ioctl(g_s32NagraFd, CMD_CA_DVB_CSA3_SETALG, &enAlg);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Set DVB Properties ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
            goto SEM_POST;
        }

        /* perform ciphered protecting level 1 */
        cryptPm.ladder = HI_UNF_ADVCA_KEYLADDER_LEV1;
        memcpy((HI_VOID*)cryptPm.pDin, xDscCipheredProtectingKeys, 16);
        Ret = ioctl(g_s32NagraFd, CMD_CA_CSA3_CRYPT, &cryptPm);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Set Protected DSC Content Keys Genarate Private Key ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
            goto SEM_POST;
        }
    }
    else
    {
        HI_UNF_ADVCA_SP_DSC_MODE_E eSPDscMode;
        /* perform ciphered protecting level 1 */
        cryptPm.ladder = HI_UNF_ADVCA_KEYLADDER_LEV1;
        memcpy((HI_VOID*)cryptPm.pDin, xDscCipheredProtectingKeys, 16); 
                   
        eSPDscMode = (HI_UNF_ADVCA_SP_DSC_MODE_E)xEmi;
        Ret = ioctl(g_s32NagraFd, CMD_CA_SP_SET_DSC_MODE, &eSPDscMode);
        Ret |= ioctl(g_s32NagraFd, CMD_CA_SP_CRYPT, &cryptPm);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Decrypt Data With Secret Content Key Genarate Private Key ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
            goto SEM_POST;
        }
    }

    if ((PAYLOAD_AES_CBC_IDSA == xEmi) || (PAYLOAD_AES_CBC_CI == xEmi))
    {
        /*IV should be set in CBC mode*/
        memset(u32IV, 0, sizeof(u32IV));
		
        if (PAYLOAD_AES_CBC_CI == xEmi)
        {
            CSD_CHECK_NULL_PTR(pxDscKeyPathHandle->dscIVAesCIplusPayload);
            memcpy(u32IV, pxDscKeyPathHandle->dscIVAesCIplusPayload, sizeof(pxDscKeyPathHandle->dscIVAesCIplusPayload));
        }

        if (bEvenKeySet)
        {
            Ret = HI_UNF_DMX_SetDescramblerEvenIVKey(pxDscKeyPathHandle->hDescrambler, u32IV);
        }
        
        if (bOddKeySet)
        {
            Ret |= HI_UNF_DMX_SetDescramblerOddIVKey(pxDscKeyPathHandle->hDescrambler, u32IV);
        }

        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Set Descrambler IV ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
            goto SEM_POST;
        }
    }
    
    /*perform ciphered content key level and set keys*/
    if (bOddKeySet)
    {
        Ret = HI_UNF_DMX_SetDescramblerOddKey(pxDscKeyPathHandle->hDescrambler, pxCipheredDscOddContentKey);
    }

    if (bEvenKeySet)
    {
        Ret |= HI_UNF_DMX_SetDescramblerEvenKey(pxDscKeyPathHandle->hDescrambler, pxCipheredDscEvenContentKey);
    }
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Set Descrambler Key ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
    }

SEM_POST:
    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }

    return csdRet;
}

TCsdStatus csdSetClearTextScrEncryptionKey(TCsdUnsignedInt16           xEmi,
                                  const TCsdUnsignedInt8*          pxClearTextScrHostKey,
                                        TCsdSize                    xClearTextScrHostKeySize,
                                  const TCsdUnsignedInt8*          pxInitializationVector,
                                        TCsdSize                    xInitializationVectorSize,
                                        TCsdScrKeyPathHandle*      pxScrKeyPathHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U32  UnitSize = 16;

    CHECK_CSD_INIT();

    if ((16 != xClearTextScrHostKeySize) || (NULL == pxClearTextScrHostKey))
    {
        HI_ERR_CA("CSD Set Clear Text SCR Encryption Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    memset((HI_VOID*)&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    if(xEmi & NAGRA_EMI_MASK_TDES)
    {
        UnitSize = 8;
    }
    else
    {
        UnitSize = 16;
    }

    /*IV should be set in CBC mode*/
    if((RAW_AES_CBC == xEmi) || (RAW_TDES_CBC == xEmi) || (RAW_AES_CBC_PIFF == xEmi) || (RAW_AES_CBC_APPLE == xEmi) || (RAW_AES_CTR == xEmi))
    {
        if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
        {
            HI_ERR_CA("CSD Set Clear Text SCR Encryption Key Parameters Invalid!\n");
            return CSD_ERROR_INVALID_PARAMETERS;
        }

        CipherCtrl.stChangeFlags.bit1IV = 1;
        memcpy((HI_VOID*)CipherCtrl.u32IV, pxInitializationVector, xInitializationVectorSize);
    }

    switch (xEmi)
    {
        case RAW_AES_CBC:
        case RAW_AES_CBC_PIFF:
        case RAW_AES_CBC_APPLE:
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
            break;
        case RAW_AES_ECB :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
            break;
        case RAW_AES_CTR:
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CTR;
            break;
        case RAW_TDES_CBC :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
            break;
        case RAW_TDES_ECB :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
            break;
        default:
            HI_ERR_CA("CSD Set Clear Text SCR Encryption Key Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
    }

    if (NULL == pxScrKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }
    CSD_CHECK_HANDLE(pxScrKeyPathHandle->handle);

    CipherCtrl.bKeyByCA = HI_FALSE;

    memcpy((HI_VOID*)CipherCtrl.u32Key, pxClearTextScrHostKey, xClearTextScrHostKeySize);

    Ret = sem_wait(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Wait semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    Ret = HI_UNF_CIPHER_ConfigHandle(pxScrKeyPathHandle->handle, &CipherCtrl);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Config Handle ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
    }

    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }

    return csdRet;
}

TCsdStatus csdSetClearTextScrDecryptionKey(TCsdUnsignedInt16           xEmi,
                                  const TCsdUnsignedInt8*          pxClearTextScrHostKey,
                                        TCsdSize                    xClearTextScrHostKeySize,
                                  const TCsdUnsignedInt8*             pxInitializationVector,
                                        TCsdSize                    xInitializationVectorSize,
                                        TCsdScrKeyPathHandle*      pxScrKeyPathHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U32  UnitSize = 16;
    TCsdStatus csdRet = CSD_NO_ERROR;
    
    CHECK_CSD_INIT();

    if ((16 != xClearTextScrHostKeySize) || (NULL == pxClearTextScrHostKey))
    {
        HI_ERR_CA("CSD Set Clear Text SCR Decryption Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if (NULL == pxScrKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }

    memset((HI_VOID*)&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));

    if (0 == (xEmi & NAGRA_EMI_MASK_RAW))
    {
        switch (xEmi)
        {
            case PAYLOAD_AES_CBC_IDSA :
            case PAYLOAD_AES_ECB :
            case PAYLOAD_AES_CBC_CI :
                UnitSize = 16;
                break;
            default:
                HI_ERR_CA("CSD Set Clear Text SCR Decryption Key Operation Not Supported!\n");
                return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }

        CSD_CHECK_HANDLE(pxScrKeyPathHandle->hDescrambler);

        Ret = sem_wait(&g_CSDSem);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("Wait semaphore ERROR!\n");
            return CSD_ERROR;
        }
            
        if((PAYLOAD_AES_CBC_IDSA == xEmi)||(PAYLOAD_AES_CBC_CI == xEmi))
        {
            /*IV should be set in CBC mode*/
            if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
            {
                HI_ERR_CA("CSD Set Clear Text SCR Decryption Key Parameters Invalid!\n");
                csdRet = CSD_ERROR_INVALID_PARAMETERS;
                goto SEM_POST;
            }

            Ret = HI_UNF_DMX_SetDescramblerOddIVKey(pxScrKeyPathHandle->hDescrambler, pxInitializationVector);
            Ret |= HI_UNF_DMX_SetDescramblerEvenIVKey(pxScrKeyPathHandle->hDescrambler, pxInitializationVector);
            if (HI_SUCCESS != Ret)
            {
                HI_ERR_CA("CSD Set Descrambler IV ERROR! Ret = 0x%x\n", Ret);
                csdRet = CSD_ERROR;
                goto SEM_POST;
            }
        }

        /*set the clear text host keys*/
        Ret = HI_UNF_DMX_SetDescramblerOddKey(pxScrKeyPathHandle->hDescrambler, pxClearTextScrHostKey);
        Ret |= HI_UNF_DMX_SetDescramblerEvenKey(pxScrKeyPathHandle->hDescrambler, pxClearTextScrHostKey);

        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Set Descrambler Key ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
        }
    }
    else
    {
        if (xEmi & NAGRA_EMI_MASK_TDES)
        {
            UnitSize = 8;
        }
        else
        {
            UnitSize = 16;
        }

        switch (xEmi)
        {
            case RAW_AES_CBC:
            case RAW_AES_CBC_PIFF:
            case RAW_AES_CBC_APPLE:
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
                break;
            case RAW_AES_ECB :
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
                break;
            case RAW_AES_CTR:
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CTR;
                break;
            case RAW_TDES_CBC :
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
                break;
            case RAW_TDES_ECB :
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
                break;
            default:
                HI_ERR_CA("CSD Set Clear Text SCR Decryption Key Operation Not Supported!\n");
                return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }

        /*IV should be set in CBC or CTR mode*/
        if((RAW_AES_CBC == xEmi) || (RAW_TDES_CBC == xEmi) || (RAW_AES_CBC_PIFF == xEmi) 
            || (RAW_AES_CBC_APPLE == xEmi) || (RAW_AES_CTR == xEmi))
        {
            if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
            {
                HI_ERR_CA("CSD Set Clear Text SCR Decryption Key Parameters Invalid!\n");
                return CSD_ERROR_INVALID_PARAMETERS;
            }

            CipherCtrl.stChangeFlags.bit1IV = 1;
            memcpy((HI_VOID*)CipherCtrl.u32IV, pxInitializationVector, xInitializationVectorSize);
        }

        CSD_CHECK_HANDLE(pxScrKeyPathHandle->handle);

        CipherCtrl.bKeyByCA = HI_FALSE;
        memcpy((HI_VOID*)CipherCtrl.u32Key, pxClearTextScrHostKey, xClearTextScrHostKeySize);
        Ret = sem_wait(&g_CSDSem);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("Wait semaphore ERROR!\n");
            return CSD_ERROR;
        }

        Ret = HI_UNF_CIPHER_ConfigHandle(pxScrKeyPathHandle->handle, &CipherCtrl);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD CIPHER Config Handle ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
        }
    }

SEM_POST:
    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }

    return csdRet;
}

TCsdStatus csdSetProtectedScrEncryptionKey(TCsdUnsignedInt16               xEmi,
                                  const TCsdScrCipheredProtectingKeys   xScrCipheredProtectingKeys,
                                  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
                                        TCsdSize                        xCipheredScrContentKeySize,
                                  const TCsdUnsignedInt8*               pxInitializationVector,
                                        TCsdSize                        xInitializationVectorSize,
                                        TCsdScrKeyPathHandle*           pxScrKeyPathHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U32  UnitSize = 16;
    CA_CRYPTPM_S cryptPm;
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_UNF_ADVCA_SP_DSC_MODE_E eSPDscMode;

    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(xScrCipheredProtectingKeys);

    if ((16 != xCipheredScrContentKeySize) || (NULL == pxCipheredScrContentKey))
    {
        HI_ERR_CA("CSD Set Protected SCR Encryption Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    memset((HI_VOID*)&CipherCtrl,0,sizeof(HI_UNF_CIPHER_CTRL_S));

    if(xEmi & NAGRA_EMI_MASK_TDES)
    {
        UnitSize = 8;
    }
    else
    {
        UnitSize = 16;
    }
    
    switch (xEmi)
    {
        case RAW_AES_CBC:
        case RAW_AES_CBC_PIFF:
        case RAW_AES_CBC_APPLE:
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
            break;
        case RAW_AES_ECB :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
            break;
        case RAW_AES_CTR:
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CTR;
            break;
        case RAW_TDES_CBC :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
            break;
        case RAW_TDES_ECB :
            CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
            CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
            CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
            CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
            break;
        default:
            HI_ERR_CA("CSD Set Protected SCR Encryption Key Operation Not Supported!\n");
            return CSD_ERROR_OPERATION_NOT_SUPPORTED;
    }

    /*IV should be set in CBC mode*/
    if((RAW_AES_CBC == xEmi) || (RAW_TDES_CBC == xEmi) || (RAW_AES_CBC_PIFF == xEmi) 
        || (RAW_AES_CBC_APPLE == xEmi) || (RAW_AES_CTR == xEmi))
    {
        if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
        {
            HI_ERR_CA("CSD Set Protected SCR Encryption Key Parameters Invalid!\n");
            return CSD_ERROR_INVALID_PARAMETERS;
        }

        CipherCtrl.stChangeFlags.bit1IV = 1;
        memcpy((HI_VOID*)CipherCtrl.u32IV, pxInitializationVector, xInitializationVectorSize);
    }

    if (NULL == pxScrKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }
    CSD_CHECK_HANDLE(pxScrKeyPathHandle->handle);

    Ret = sem_wait(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Wait semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    /* perform ciphered protecting level 1 */
    cryptPm.ladder = HI_UNF_ADVCA_KEYLADDER_LEV1;
    memcpy((HI_VOID*)cryptPm.pDin, xScrCipheredProtectingKeys, 16);

    eSPDscMode = (HI_UNF_ADVCA_SP_DSC_MODE_E)xEmi;
    Ret = ioctl(g_s32NagraFd, CMD_CA_SP_SET_DSC_MODE, &eSPDscMode);
    Ret |= ioctl(g_s32NagraFd, CMD_CA_SP_CRYPT, &cryptPm);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD Encrypt Data With Secret Content Key Genarate Private Key ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
        goto SEM_POST;
    }

    CipherCtrl.enCaType = HI_UNF_CIPHER_CA_TYPE_SP;
    
    CipherCtrl.bKeyByCA = HI_TRUE;

    memcpy((HI_VOID*)CipherCtrl.u32Key, pxCipheredScrContentKey, xCipheredScrContentKeySize);

    Ret = HI_UNF_CIPHER_ConfigHandle(pxScrKeyPathHandle->handle, &CipherCtrl);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("CSD CIPHER Config Handle ERROR! Ret = 0x%x\n", Ret);
        csdRet = CSD_ERROR;
    }

SEM_POST:
    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }

    return csdRet;
}

TCsdStatus csdSetProtectedScrDecryptionKey(TCsdUnsignedInt16               xEmi,
                                  const TCsdScrCipheredProtectingKeys   xScrCipheredProtectingKeys,
                                  const TCsdUnsignedInt8*               pxCipheredScrContentKey,
                                        TCsdSize                        xCipheredScrContentKeySize,
                                  const TCsdUnsignedInt8*               pxInitializationVector,
                                        TCsdSize                        xInitializationVectorSize,
                                        TCsdScrKeyPathHandle*           pxScrKeyPathHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U32  UnitSize = 16;
    CA_CRYPTPM_S cryptPm;
    TCsdStatus csdRet = CSD_NO_ERROR;
    HI_UNF_ADVCA_SP_DSC_MODE_E eSPDscMode;

    CHECK_CSD_INIT();
    CSD_CHECK_PARAM(xScrCipheredProtectingKeys);
    
    if ((16 != xCipheredScrContentKeySize) || (NULL == pxCipheredScrContentKey))
    {
        HI_ERR_CA("CSD Set Protected SCR Decryption Key Parameters Invalid!\n");
        return CSD_ERROR_INVALID_PARAMETERS;
    }

    if (NULL == pxScrKeyPathHandle)
    {
        HI_ERR_CA("invalid handle.\n");
        return CSD_ERROR_INVALID_KEY_PATH_HANDLE;
    }
    
    memset((HI_VOID*)&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));

    if (0 == (xEmi & NAGRA_EMI_MASK_RAW))
    {
        switch (xEmi)
        {
            case PAYLOAD_AES_CBC_IDSA :
            case PAYLOAD_AES_ECB :
            case PAYLOAD_AES_CBC_CI :
                UnitSize = 16;
                break;
            default:
                HI_ERR_CA("CSD Set Protected SCR Decryption Key Operation Not Supported!\n");
                return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }

        CSD_CHECK_HANDLE(pxScrKeyPathHandle->hDescrambler);

        Ret = sem_wait(&g_CSDSem);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("Wait semaphore ERROR!\n");
            return CSD_ERROR;
        }
        
        /* perform ciphered protecting level 1 */
        cryptPm.ladder = HI_UNF_ADVCA_KEYLADDER_LEV1;
        memcpy((HI_VOID*)cryptPm.pDin, xScrCipheredProtectingKeys, 16);

        eSPDscMode = (HI_UNF_ADVCA_SP_DSC_MODE_E)xEmi;
        Ret = ioctl(g_s32NagraFd, CMD_CA_SP_SET_DSC_MODE, &eSPDscMode);
        Ret |= ioctl(g_s32NagraFd, CMD_CA_SP_CRYPT, &cryptPm);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Decrypt Data With Secret Content Key Genarate Private Key ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
            goto SEM_POST;
        }

        if((PAYLOAD_AES_CBC_IDSA == xEmi)||(PAYLOAD_AES_CBC_CI == xEmi))
        {
            /*IV should be set in CBC mode*/
            if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
            {
                HI_ERR_CA("CSD Set Protected SCR Decryption Key Parameters Invalid!\n");
                csdRet = CSD_ERROR_INVALID_PARAMETERS;
                goto SEM_POST;
            }

            Ret = HI_UNF_DMX_SetDescramblerOddIVKey(pxScrKeyPathHandle->hDescrambler, pxInitializationVector);
            Ret |= HI_UNF_DMX_SetDescramblerEvenIVKey(pxScrKeyPathHandle->hDescrambler, pxInitializationVector);
            if (HI_SUCCESS != Ret)
            {
                HI_ERR_CA("CSD Set Descrambler IV ERROR! Ret = 0x%x\n", Ret);
                csdRet = CSD_ERROR;
                goto SEM_POST;
            }
        }
        
        /*perform ciphered content key level and set keys*/
        Ret = HI_UNF_DMX_SetDescramblerOddKey(pxScrKeyPathHandle->hDescrambler, pxCipheredScrContentKey);
        Ret |= HI_UNF_DMX_SetDescramblerEvenKey(pxScrKeyPathHandle->hDescrambler, pxCipheredScrContentKey);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Set Descrambler Key ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
        }
    }
    else
    {
        if(xEmi & NAGRA_EMI_MASK_TDES)
        {
            UnitSize = 8;
        }
        else
        {
            UnitSize = 16;
        }

        switch (xEmi)
        {
            case RAW_AES_CBC:
            case RAW_AES_CBC_PIFF:
            case RAW_AES_CBC_APPLE:
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
                break;
            case RAW_AES_ECB :
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
                break;
            case RAW_AES_CTR:
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CTR;
                break;
            case RAW_TDES_CBC :
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
                break;
            case RAW_TDES_ECB :
                CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
                CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
                CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
                CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
                break;
            default:
                HI_ERR_CA("CSD Set Protected SCR Decryption Key Operation Not Supported!\n");
                return CSD_ERROR_OPERATION_NOT_SUPPORTED;
        }

        /*IV should be set in CBC mode*/
        if((RAW_AES_CBC == xEmi)||(RAW_TDES_CBC == xEmi) || (RAW_AES_CBC_PIFF == xEmi)
            || (RAW_AES_CBC_APPLE == xEmi) || (RAW_AES_CTR == xEmi))
        {
            if ((UnitSize != xInitializationVectorSize) || (NULL == pxInitializationVector))
            {
                HI_ERR_CA("CSD Set Protected SCR Decryption Key Parameters Invalid!\n");
                return CSD_ERROR_INVALID_PARAMETERS;
            }

            CipherCtrl.stChangeFlags.bit1IV = 1;
            memcpy((HI_VOID*)CipherCtrl.u32IV, pxInitializationVector, xInitializationVectorSize);
        }

        CSD_CHECK_HANDLE(pxScrKeyPathHandle->handle);

        Ret = sem_wait(&g_CSDSem);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("Wait semaphore ERROR!\n");
            return CSD_ERROR;
        }

        /* perform ciphered protecting level 1 */
        cryptPm.ladder = HI_UNF_ADVCA_KEYLADDER_LEV1;
        memcpy((HI_VOID*)cryptPm.pDin, xScrCipheredProtectingKeys, 16);
        eSPDscMode = (HI_UNF_ADVCA_SP_DSC_MODE_E)xEmi;

        Ret = ioctl(g_s32NagraFd, CMD_CA_SP_SET_DSC_MODE, &eSPDscMode);
        Ret |= ioctl(g_s32NagraFd, CMD_CA_SP_CRYPT, &cryptPm);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD Decrypt Data With Secret Content Key Genarate Private Key ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
            goto SEM_POST;
        }

        CipherCtrl.enCaType = HI_UNF_CIPHER_CA_TYPE_SP;
        CipherCtrl.bKeyByCA = HI_TRUE;
        memcpy((HI_VOID*)CipherCtrl.u32Key, pxCipheredScrContentKey, xCipheredScrContentKeySize);
        Ret = HI_UNF_CIPHER_ConfigHandle(pxScrKeyPathHandle->handle, &CipherCtrl);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("CSD CIPHER Config Handle ERROR! Ret = 0x%x\n", Ret);
            csdRet = CSD_ERROR;
        }
    }

SEM_POST:
    Ret = sem_post(&g_CSDSem);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Post semaphore ERROR!\n");
        return CSD_ERROR;
    }
    
    return csdRet;
}

