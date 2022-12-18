/***********************************************************
 *                      Copyright    , 2009-2014, Hisilicon Tech. Co., Ltd.
 *                                   ALL RIGHTS RESERVED
 * FileName:  protocol_hisi_file_ca.c
 * Description: usb upgrade mode for ca
 *
 * History:
 * Version   Date               Author            DefectNum      Description
 * main\1    2013-10-25    m00190812     NULL              Create this file.
 ************************************************************/
#ifndef __PROTOCOL_HISI_FILE_CA_C__
#define __PROTOCOL_HISI_FILE_CA_C__

/* C++ support */
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

/*include header files  */
#include <malloc.h>
#include "hi_type.h"
#include "download.h"
#include "hi_loader_info.h"
#include "upgrd_common.h"
#include "protocol_hisi_file.h"
#include "ca_ssd.h"
#include "wrapper_ca.h"

#define USB_MAGIC_NUM 0x4C4F4144
static HI_U32 g_u32USBHeaderNotAligned = 0;     /*The unaligned data size of USB header*/
static HI_U32 g_u32USBHeaderLen = 0;            /*The length of USB header*/

static UsbHeader s_stFileHeader;


static HI_U8 *g_pu8DataBuf = HI_NULL;

static LOADER_DATA_S g_astData[MAX_UPGRADE_IMAGE_NUM];

/**
 \brief initialize hisi OTA file protocol .
 \attention \n
 \param[] None
 \retval ::HI_SUCCESS : initialize success
 \retval ::HI_FAILURE : initialize failed
 */
HI_S32 LOADER_PROTOCOL_HisiFILE_Init_OTA(HI_VOID)
{
    g_pu8DataBuf = (HI_U8 *)malloc(8 * 1024);

    if (HI_NULL == g_pu8DataBuf)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/**
 \brief initialize hisi CA file protocol .
 \attention \n
 \param[in] enType: download data type
 \param[in] para: download parameters
 \retval ::HI_SUCCESS : initialize success
 \retval ::HI_FAILURE : initialize failed
 */
HI_S32 LOADER_PROTOCOL_HisiCAFILE_Init(HI_LOADER_TYPE_E enType, HI_VOID * para)
{
    g_pu8DataBuf = (HI_U8 *)malloc(8 * 1024);

    if (HI_NULL == g_pu8DataBuf)
    {
        return HI_FAILURE;
    }

    if (HI_SUCCESS != CA_SSD_Init())
    {
        return HI_FAILURE;
    }

    return LOADER_DOWNLOAD_Init(enType, para);
}

/**
 \brief deinitialize hisi CA file protocol.
 \attention \n
 \retval ::HI_SUCCESS : deinitialize success
 \retval ::HI_FAILURE : deinitialize failed
 */

HI_VOID LOADER_PROTOCOL_HisiCAFILE_DeInit(HI_VOID)
{
    free(g_pu8DataBuf);
    g_pu8DataBuf = HI_NULL;

    (HI_VOID)FreeMemory();

    (HI_VOID)LOADER_DOWNLOAD_DeInit();

    (HI_VOID)CA_SSD_DeInit();
}

/**
 \brief get version of hisi OTA file.
 \attention \n
 \param[in] pu8Data: The data from OTA
 \param[in] u32Len: The length of pu8Data
 \param[out] pstVersionInfo: The version of the data
 \retval ::HI_SUCCESS : success
 \retval ::HI_FAILURE : failure
 */
HI_S32 LOADER_PROTOCOL_HisiFILE_GetVersionInfo_OTA(LOADER_VERSION_INFO_S * pstVersionInfo, const HI_U8 *pu8Data, HI_U32 u32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32MagicNum = 0;
    HI_U32 u32HeaderLen = 0;
    HI_U8 *pTmp = g_pu8DataBuf;
    HI_U32 u32crc = 0;
    HI_U32 u32ReadLenTmp = 0;

    if ((HI_NULL == pstVersionInfo) || (HI_NULL == pu8Data) || (u32Len < 16))
    {
        return HI_FAILURE;
    }

    do
    {
        memcpy(pTmp, pu8Data, 16);

        /* ca */
        s32Ret = CA_SSD_DecryptUpgradeImage(pTmp, 16);
        if ( HI_SUCCESS != s32Ret)
        {
            HI_ERR_LOADER("ca ssd decrypt upgrade image failed!\n");
            return s32Ret;
        }

        /*magic number check*/
        u32MagicNum = getBits(g_pu8DataBuf, 0, 0, 32);
        if ( USB_MAGIC_NUM !=  u32MagicNum)
        {
            HI_ERR_LOADER("stream magic num error 0x%x.", u32MagicNum);
            s32Ret = HI_FAILURE;
            break;
        }
        
        u32HeaderLen = getBits(g_pu8DataBuf, 0, 64, 32);
        g_u32USBHeaderLen = u32HeaderLen;
        g_u32USBHeaderNotAligned = g_u32USBHeaderLen % 16;

        if (u32Len < g_u32USBHeaderLen)
        {
            return HI_FAILURE;
        }

        pTmp += 16;

        /* To read data aligned with 16 Bytes */
        if ( 0 != g_u32USBHeaderNotAligned )
        {
            /* 16 Bytes have been downloaded already. Read more to align with 16 Bytes */
            u32ReadLenTmp = (g_u32USBHeaderLen - 16) + (16 - g_u32USBHeaderNotAligned);
        }
        else
        {
            u32ReadLenTmp = g_u32USBHeaderLen - 16;
        }

        memcpy(pTmp, pu8Data + 16, u32ReadLenTmp);

        /* Decrypt USB header */
        s32Ret = CA_SSD_DecryptUpgradeImage(pTmp, u32ReadLenTmp);
        if ( HI_SUCCESS != s32Ret)
        {
            HI_ERR_LOADER("ca ssd decrypt upgrade image failed!\n");
            return s32Ret;
        }

        ParseHeader(g_pu8DataBuf, &s_stFileHeader);

        if (s_stFileHeader.u16ManuNum > 0)
            s_pstManu = &s_stFileHeader.astManuInfo[0];

        if (s_pstManu == HI_NULL)
        {
            HI_ERR_LOADER("can't find upgrade image!\n");
            s32Ret = HI_UPGRD_OUI_NOT_MATCH;
            break;
        }

        /*crc check*/
        memset(g_pu8DataBuf + sizeof(s_stFileHeader.u32MagicNum), 0, sizeof(s_stFileHeader.u32HeaderCrc));
        (HI_VOID)LOADER_Entire_CRC32(g_pu8DataBuf, s_stFileHeader.u32HeaderLen, &u32crc);
        if (u32crc != s_stFileHeader.u32HeaderCrc)
        {
            HI_ERR_LOADER("Bad head crc 0x%x, calc crc 0x%x.", s_stFileHeader.u32HeaderCrc, u32crc);
            s32Ret = HI_FAILURE;
            break;
        }

        pstVersionInfo->u32FactoryId   = s_pstManu->u32ManuId;
        pstVersionInfo->u32HardwareVer = s_pstManu->u32HardVersion;
        pstVersionInfo->u32Softwarever = s_pstManu->u32SoftVersion;

        s32Ret = HI_SUCCESS;
    } while (0);

    return s32Ret;
}

/**
 \brief get version of hisi CA file protocol upgrade file.
 \attention \n
 \param[out] pstVersionInfo: The version info of CA file
 \retval ::HI_SUCCESS : success
 \retval ::HI_FAILURE : failure
 */
HI_S32 LOADER_PROTOCOL_HisiCAFILE_GetVersionInfo(LOADER_VERSION_INFO_S * pstVersionInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32MagicNum = 0;
    HI_U32 u32HeaderLen = 0;
    HI_U32 u32ReadLen = 0;
    HI_U8 *pTmp = g_pu8DataBuf;
    HI_U32 u32crc = 0;
    HI_U32 u32ReadLenTmp = 0;

    if (HI_NULL == pstVersionInfo)
        return HI_FAILURE;

    do
    {
        s32Ret = LOADER_DOWNLOAD_Getdata(pTmp, 16, &u32ReadLen);
        if ((s32Ret != HI_SUCCESS) || (u32ReadLen != 16))
        {
            s32Ret = (s32Ret == HI_SUCCESS) ? HI_FAILURE : s32Ret;
            break;
        }

        /* ca */
        s32Ret = CA_SSD_DecryptUpgradeImage(pTmp, u32ReadLen);
        if ( HI_SUCCESS != s32Ret)
        {
            HI_ERR_LOADER("ca ssd decrypt upgrade image failed!\n");
            return s32Ret;
        }

        /*magic number check*/
        u32MagicNum = getBits(g_pu8DataBuf, 0, 0, 32);
        if ( USB_MAGIC_NUM !=  u32MagicNum)
        {
            HI_ERR_LOADER("stream magic num error 0x%x.", u32MagicNum);
            s32Ret = HI_FAILURE;
            break;
        }
        
        u32HeaderLen = getBits(g_pu8DataBuf, 0, 64, 32);
        g_u32USBHeaderLen = u32HeaderLen;
        g_u32USBHeaderNotAligned = g_u32USBHeaderLen % 16;

        pTmp += 16;

        /* To read data aligned with 16 Bytes */
        if ( 0 != g_u32USBHeaderNotAligned )
        {
            /*16 Bytes have been downloaded already. Read more to align with 16 Bytes */
            u32ReadLenTmp = (g_u32USBHeaderLen - 16) + (16 - g_u32USBHeaderNotAligned);
        }
        else
        {
            u32ReadLenTmp = g_u32USBHeaderLen - 16;
        }

        s32Ret = LOADER_DOWNLOAD_Getdata(pTmp, u32ReadLenTmp, &u32ReadLen);
        if ((s32Ret != HI_SUCCESS) || (u32ReadLen != u32ReadLenTmp))
        {
            s32Ret = (s32Ret == HI_SUCCESS) ? HI_FAILURE : s32Ret;
            break;
        }

        /* Decrypt USB header */
        s32Ret = CA_SSD_DecryptUpgradeImage(pTmp, u32ReadLen);
        if ( HI_SUCCESS != s32Ret)
        {
            HI_ERR_LOADER("ca ssd decrypt upgrade image failed!\n");
            return s32Ret;
        }

        ParseHeader(g_pu8DataBuf, &s_stFileHeader);

        if (s_stFileHeader.u16ManuNum > 0)
            s_pstManu = &s_stFileHeader.astManuInfo[0];

        if (s_pstManu == HI_NULL)
        {
            HI_ERR_LOADER("can't find upgrade image!\n");
            s32Ret = HI_UPGRD_OUI_NOT_MATCH;
            break;
        }

        /*crc check*/
        memset(g_pu8DataBuf + sizeof(s_stFileHeader.u32MagicNum), 0, sizeof(s_stFileHeader.u32HeaderCrc));
        (HI_VOID)LOADER_Entire_CRC32(g_pu8DataBuf, s_stFileHeader.u32HeaderLen, &u32crc);
        if (u32crc != s_stFileHeader.u32HeaderCrc)
        {
            HI_ERR_LOADER("Bad head crc 0x%x, calc crc 0x%x.", s_stFileHeader.u32HeaderCrc, u32crc);
            s32Ret = HI_FAILURE;
            break;
        }

        pstVersionInfo->u32FactoryId   = s_pstManu->u32ManuId;
        pstVersionInfo->u32HardwareVer = s_pstManu->u32HardVersion;
        pstVersionInfo->u32Softwarever = s_pstManu->u32SoftVersion;
        pstVersionInfo->u32StartSn = s_pstManu->u32SNStart;
        pstVersionInfo->u32EndSn = s_pstManu->u32SNEnd;

        s32Ret = HI_SUCCESS;
    } while (0);

    return s32Ret;
}

/**
 \brief process the OTA file, and call datacallback to notice caller the data.
 \attention \n
 \param[in] u32MaxMemorySize:  max memory size the implementer can malloc
 \param[in] pu8Data:  The data from OTA to process
 \param[in] u32Len:   The length of pu8Data
 \retval ::HI_SUCCESS : success
 \retval ::HI_FAILURE : failure
 */
HI_S32 LOADER_PROTOCOL_HisiFILE_Process_OTA(HI_U32 u32MaxMemorySize, const HI_U8 *pu8Data, HI_U32 u32Len)
{
    HI_S32 ret = HI_SUCCESS;
    UsbImgMap *pImg = HI_NULL;
    HI_U32 u32TmpCRC = 0;
    HI_U8 *pMemAddr = HI_NULL;
    HI_U32 u32Size = 0;
    HI_U32 u32MemSize = 0;
    HI_U8 offset = 0;

    if ((0 == u32MaxMemorySize) || (HI_NULL == pu8Data) || ((HI_U32)s_stFileHeader.u64FileLen > u32Len))
    {
        return HI_FAILURE;
    }

    if ((g_pstCallback == HI_NULL) || (g_pstCallback->pfnDataCallback == HI_NULL))
    {
        return HI_FAILURE;
    }

    if (HI_NULL == s_pstManu)
    {
        return HI_FAILURE;
    }

    ret = InitUpgradeBuff(s_pstManu);
    if ( HI_FAILURE == ret )
    {
        return HI_FAILURE;
    }

    u32MemSize = (HI_U32)s_stFileHeader.u64FileLen + PLUS_MEM_SIZE;
    /* Malloc more size to store the data unaligned with 16 Bytes */
    pMemAddr = (HI_U8 *)LOADER_GetUsableMemory(u32MemSize, &u32Size);
    /* Malloc the whole size */
    if ((NULL == pMemAddr) || (u32MemSize != u32Size))
    {
        HI_ERR_LOADER("There is no Usable Memory.\n");
        return HI_FAILURE;
    }

    /* Decrypt the whole data */
    memcpy(pMemAddr, pu8Data, (HI_U32)s_stFileHeader.u64FileLen);

    ret = CA_SSD_DecryptUpgradeImage(pMemAddr, (HI_U32)s_stFileHeader.u64FileLen);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_LOADER("Decrypt upgrade image failed.\n");
        LOADER_FreeUsableMemory(pMemAddr);
        return HI_FAILURE;
    }

    ret = CA_SSD_AuthenticatePrepare((const HI_U32 *)&s_stFileHeader, pMemAddr, g_u32USBHeaderLen);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_LOADER("ca auth prepare failed!\n");
        LOADER_FreeUsableMemory(pMemAddr);
        return HI_FAILURE;
    }

    for (offset = 0; offset < s_stFileHeader.astManuInfo[0].u16ImgMapNum; offset++)
    {
        pImg = &(s_pstManu->astImgMap[offset]);
        pImg->u32DataCRC = getBits(pMemAddr + pImg->u32Offset, 0, 32, 32);

        /* CRC check */
        (HI_VOID)LOADER_Entire_CRC32(pMemAddr + pImg->u32Offset + 8, pImg->u32FileLength, &u32TmpCRC);
        if ( pImg->u32DataCRC != u32TmpCRC )
        {
            HI_ERR_LOADER("crc auth failed!\n");
            LOADER_FreeUsableMemory(pMemAddr);
            return HI_FAILURE;
        }

        /* SSD Authenticate */
        ret = CA_SSD_Authenticate(pMemAddr + pImg->u32Offset + 8, 
                                &(pImg->u32FileLength), 
                                (HI_U32)pImg->u64FlashAddr, 
                                pImg->uFlashType);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_LOADER("ca auth failed!\n");
            LOADER_FreeUsableMemory(pMemAddr);
            return HI_FAILURE;
        }

        /* Write image */
        g_astData[offset].u8DataBuff = pMemAddr + pImg->u32Offset + 8;
        g_astData[offset].u32DataSize = pImg->u32FileLength;
        g_astData[offset].u32PartitionId = offset + 1;
        g_astData[offset].bLastData = HI_TRUE;
    }

    if (g_pstCallback && g_pstCallback->pfnDataCallback)
    {
        ret = g_pstCallback->pfnDataCallback(g_astData, offset);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_LOADER("pfnDataCallback error");
            LOADER_FreeUsableMemory(pMemAddr);
            return ret;
        }
    }

    LOADER_FreeUsableMemory(pMemAddr);

    return ret;
}


/**
 \brief receive upgrade data, and call datacallback to notice caller the data.
 \attention \n
 \param[in] u32MaxMemorySize:  max memory size the implementer can malloc
 \retval ::HI_SUCCESS : success
 \retval ::HI_FAILURE : failure
 */
HI_S32 LOADER_PROTOCOL_HisiCAFILE_Process(HI_U32 u32MaxMemorySize)
{
    HI_S32 ret = HI_SUCCESS;
    UsbImgMap *pImg = HI_NULL;
    HI_U32 u32TmpCRC = 0;
    HI_U8 *pMemAddr = HI_NULL;
    HI_U32 u32Size = 0;
    HI_U32 u32MemSize = 0;
    HI_U32 u32FileNotAlignedByte = 0;
    HI_U8 offset = 0;

    if (0 == u32MaxMemorySize)
        return HI_FAILURE;

    if ((g_pstCallback == HI_NULL) || (g_pstCallback->pfnDataCallback == HI_NULL))
        return HI_FAILURE;

    if (HI_NULL == s_pstManu)
        return HI_FAILURE;

    ret = InitUpgradeBuff(s_pstManu);
    if ( HI_FAILURE == ret )
    {
        return HI_FAILURE;
    }

    if (0 != g_u32USBHeaderNotAligned)
    {
        u32FileNotAlignedByte = 16 - g_u32USBHeaderNotAligned;
    }

    u32MemSize = (HI_U32)s_stFileHeader.u64FileLen + PLUS_MEM_SIZE;
    /* Malloc more size to store the data unaligned with 16 Bytes */
    pMemAddr = (HI_U8 *)LOADER_GetUsableMemory(u32MemSize, &u32Size);
    /* Malloc the whole size */
    if ((NULL == pMemAddr) || (u32Size != u32MemSize))
    {
        HI_ERR_LOADER("There is no Usable Memory.\n");
        return HI_FAILURE;
    }

    ret = LOADER_DOWNLOAD_Getdata(pMemAddr + g_u32USBHeaderLen + u32FileNotAlignedByte, ((HI_U32)s_stFileHeader.u64FileLen - g_u32USBHeaderLen) - u32FileNotAlignedByte, &u32Size);
    if ((HI_SUCCESS != ret) || (u32Size != ((HI_U32)s_stFileHeader.u64FileLen - g_u32USBHeaderLen) - u32FileNotAlignedByte))
    {
        HI_ERR_LOADER("download upgrade failed.\n");
        LOADER_FreeUsableMemory(pMemAddr);
        return HI_FAILURE;
    }

    if (g_pstCallback && g_pstCallback->pfnOSDCallback)
    {
    	(HI_VOID)g_pstCallback->pfnOSDCallback(OSD_EVENT_TYPE_DOWNLOAD, (HI_U32)s_stFileHeader.u64FileLen, (HI_U32)s_stFileHeader.u64FileLen);
    }

    /* Copy the data decrypted already before */
    memcpy(pMemAddr, g_pu8DataBuf, g_u32USBHeaderLen + u32FileNotAlignedByte);

    ret = CA_SSD_DecryptUpgradeImage(pMemAddr + g_u32USBHeaderLen + u32FileNotAlignedByte, u32Size);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_LOADER("Decrypt upgrade image failed.\n");
        LOADER_FreeUsableMemory(pMemAddr);
        return HI_FAILURE;
    }

    ret = CA_SSD_AuthenticatePrepare((const HI_U32 *)&s_stFileHeader, pMemAddr, g_u32USBHeaderLen);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_LOADER("ca auth prepare failed!\n");
        LOADER_FreeUsableMemory(pMemAddr);
        return HI_FAILURE;
    }

    for (offset = 0; offset < s_stFileHeader.astManuInfo[0].u16ImgMapNum; offset++)
    {
        pImg = &(s_pstManu->astImgMap[offset]);
        pImg->u32DataCRC = getBits(pMemAddr + pImg->u32Offset, 0, 32, 32);

        /* CRC check */
        (HI_VOID)LOADER_Entire_CRC32(pMemAddr + pImg->u32Offset + 8, pImg->u32FileLength, &u32TmpCRC);
        if ( pImg->u32DataCRC != u32TmpCRC )
        {
            HI_ERR_LOADER("crc auth failed! pImg->u32DataCRC = %x, u32TmpCRC = %x\n", pImg->u32DataCRC, u32TmpCRC);
            LOADER_FreeUsableMemory(pMemAddr);
            return HI_FAILURE;
        }

        /* SSD Authenticate */
        ret = CA_SSD_Authenticate(pMemAddr + pImg->u32Offset + 8, 
                                &(pImg->u32FileLength), 
                                (HI_U32)pImg->u64FlashAddr, 
                                pImg->uFlashType);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_LOADER("ca auth failed!\n");
            LOADER_FreeUsableMemory(pMemAddr);
            return HI_FAILURE;
        }

        /* Write image */
        g_astData[offset].u8DataBuff = pMemAddr + pImg->u32Offset + 8;
        g_astData[offset].u32DataSize = pImg->u32FileLength;
        g_astData[offset].u32PartitionId = offset + 1;
        g_astData[offset].bLastData = HI_TRUE;
    }

    if (g_pstCallback && g_pstCallback->pfnDataCallback)
    {
        ret = g_pstCallback->pfnDataCallback(g_astData, offset);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_LOADER("pfnDataCallback error");
            LOADER_FreeUsableMemory(pMemAddr);
            return ret;
        }
    }

    LOADER_FreeUsableMemory(pMemAddr);

    return ret;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif  /* __cplusplus */

#endif  /*__PROTOCOL_HISI_FILE_CA_C__*/
