/******************************************************************************

Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : ca_ssd.c
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/
#include "loader_upgrade.h"
#include "hi_loader_info.h"
#include "protocol_hisi_file.h"
#include "protocol_hisi_ota.h"
#include "ca_ssd.h"

#if defined(HI_ADVCA_SUPPORT) && !defined(HI_ADVCA_TYPE_NAGRA) && !defined(HI_ADVCA_TYPE_VERIMATRIX)
#include "cx_ssd.h"
#endif

#ifdef HI_ADVCA_TYPE_NAGRA
#include "nasc1x_ssd.h"
#endif

#ifdef HI_ADVCA_TYPE_VERIMATRIX
#include "vmx_ssd.h"

typedef enum tagVMX_SSD_TYPE_E
{
    LOADER_SSD_TYPE_NONE = 0,
    LOADER_SSD_TYPE_VMX_ADVANCE,
    LOADER_SSD_TYPE_VMX_ULTRA,
    LOADER_SSD_TYPE_BUTT

} VMX_SSD_TYPE_E;

typedef struct tagVMX_PARTITITON_INFO
{
    HI_CHAR*        pcPartitionName;
    HI_U64          u64FlashStartAddr;
    VMX_SSD_TYPE_E  enSSDType;

} VMX_PARTITITON_INFO_S;


VMX_PARTITITON_INFO_S s_astPartitionInfo[] =
{
    {"boot",            0, LOADER_SSD_TYPE_VMX_ADVANCE},        /** Linux */
    {"fastboot",        0, LOADER_SSD_TYPE_VMX_ADVANCE},        /** Android */
    {"bootargs",        0, LOADER_SSD_TYPE_VMX_ADVANCE},
    {"stbinfo",         0, LOADER_SSD_TYPE_NONE},               /** Android */
    {"deviceinfo",      0, LOADER_SSD_TYPE_NONE},
    {"softwareinfo",    0, LOADER_SSD_TYPE_NONE},
    {"loaderdb",        0, LOADER_SSD_TYPE_NONE},
    {"loaderdbbk",      0, LOADER_SSD_TYPE_NONE},
    {"loader",          0, LOADER_SSD_TYPE_VMX_ADVANCE},
    {"loaderbak",       0, LOADER_SSD_TYPE_VMX_ADVANCE},
    {"baseparam",       0, LOADER_SSD_TYPE_NONE},
    {"pqparam",         0, LOADER_SSD_TYPE_NONE},
    {"logo",            0, LOADER_SSD_TYPE_NONE},
    {"logobak",         0, LOADER_SSD_TYPE_NONE},
    {"fastplay",        0, LOADER_SSD_TYPE_NONE},
    {"fastplaybak",     0, LOADER_SSD_TYPE_NONE},
    {"kernel",          0, LOADER_SSD_TYPE_VMX_ADVANCE},        /** Android */
    {"misc",            0, LOADER_SSD_TYPE_NONE},               /** Android */
    {"cadata",          0, LOADER_SSD_TYPE_NONE},               /** Android */
    {"shatable",        0, LOADER_SSD_TYPE_VMX_ADVANCE},        /** Android */
    {"system",          0, LOADER_SSD_TYPE_NONE},               /** Android */
    {"userdata",        0, LOADER_SSD_TYPE_NONE},               /** Android */
    {"cache",           0, LOADER_SSD_TYPE_NONE},               /** Android */
    {"private",         0, LOADER_SSD_TYPE_NONE},               /** Android */
    {"sdcard",          0, LOADER_SSD_TYPE_NONE},               /** Android */
    {"trustedcore",     0, LOADER_SSD_TYPE_VMX_ADVANCE},        /** Linux */
    {"rootfs",          0, LOADER_SSD_TYPE_VMX_ADVANCE}         /** Linux */
};

HI_VOID vmxSSDPrintPartitionInfo(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 u32ImageCount = 0;

    u32ImageCount = sizeof(s_astPartitionInfo)/sizeof(VMX_PARTITITON_INFO_S);

    for (i = 0; i < u32ImageCount; i++)
    {
        HI_ERR_CA_SSD("PartitionName: %s SSDType: %u FlashStartAddr:%llu\n",
                      s_astPartitionInfo[i].pcPartitionName,
                      s_astPartitionInfo[i].enSSDType,
                      s_astPartitionInfo[i].u64FlashStartAddr);
    }

    return;
}

HI_S32 vmxSSDGetPartitionStartAddr(HI_CHAR *pcPartitionName, HI_U64 *pu64FlashStartAddr)
{
    HI_Flash_InterInfo_S stFlashInfo;
    HI_HANDLE hFlashHandle = HI_INVALID_HANDLE;
    HI_S32 s32Ret = HI_FAILURE;

    hFlashHandle = HI_Flash_OpenByName(pcPartitionName);
    if (HI_INVALID_HANDLE == hFlashHandle)
    {
        HI_ERR_CA_SSD("Call HI_Flash_OpenByName failed.\n");
        return HI_FAILURE;
    }

    memset(&stFlashInfo, 0x00, sizeof(stFlashInfo));
    s32Ret = HI_Flash_GetInfo(hFlashHandle, &stFlashInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_CA_SSD("Call HI_Flash_GetInfo failed.\n");
        HI_Flash_Close(hFlashHandle);
        return HI_FAILURE;
    }

    HI_Flash_Close(hFlashHandle);
    hFlashHandle = HI_INVALID_HANDLE;

    *pu64FlashStartAddr = stFlashInfo.OpenAddr;

    return HI_SUCCESS;
}

VMX_PARTITITON_INFO_S * vmxSSDGetPartitionInfo(HI_U64 u64FlashStartAddr)
{
    HI_U32 i = 0;
    HI_U32 u32ImageCount = 0;

    u32ImageCount = sizeof(s_astPartitionInfo)/sizeof(VMX_PARTITITON_INFO_S);

    for (i = 0; i < u32ImageCount; i++)
    {
        if (u64FlashStartAddr == s_astPartitionInfo[i].u64FlashStartAddr)
        {
            return &s_astPartitionInfo[i];
        }
    }

    return HI_NULL_PTR;
}

HI_BOOL vmxSSDIsSignatured(HI_U32 u32FlashStartAddr)
{
    VMX_PARTITITON_INFO_S *pstPartition = HI_NULL_PTR;
    pstPartition = vmxSSDGetPartitionInfo(u32FlashStartAddr);

    if ((HI_NULL_PTR == pstPartition)
        || (LOADER_SSD_TYPE_NONE == pstPartition->enSSDType)
        || (LOADER_SSD_TYPE_BUTT == pstPartition->enSSDType))
    {
        return HI_FALSE;
    }

    HI_ERR_CA_SSD("Partition need to verify: %s 0x%016llx\n", pstPartition->pcPartitionName, pstPartition->u64FlashStartAddr);
    return HI_TRUE;
}
HI_S32 vmxSSDPartitionInfoInit(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 u32ImageCount = 0;
    HI_S32 s32Ret = HI_FAILURE;

    u32ImageCount = sizeof(s_astPartitionInfo)/sizeof(VMX_PARTITITON_INFO_S);

    for (i = 0; i < u32ImageCount; i++)
    {
        s32Ret = vmxSSDGetPartitionStartAddr(s_astPartitionInfo[i].pcPartitionName, &s_astPartitionInfo[i].u64FlashStartAddr);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_CA_SSD("Call vmxSSDGetPartitionStartAddr failed.\n");
            continue;
        }
    }

    vmxSSDPrintPartitionInfo();
    return HI_SUCCESS;
}
#endif

#include "../../api/src/ca_ssd.c"

#ifdef HI_ADVCA_SUPPORT

#ifdef HI_ADVCA_TYPE_VERIMATRIX
extern HI_VMX_SSD_S g_stVMXSSD[VMX_SSD_MAX_PARTITIONS];
#endif

#ifndef HI_ADVCA_TYPE_VERIMATRIX
static HI_S32 SSD_ReadEncrytedSwpk(HI_U8 *pu8EncryptedSwpk)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 *pu8Buf = NULL;
    HI_HANDLE hFlashHandle = HI_INVALID_HANDLE;
    HI_U8 u8EncryptFlag = 0;
    HI_Flash_InterInfo_S stFlashInfo;

    if (NULL == pu8EncryptedSwpk)
    {
        HI_ERR_CA_SSD("Invalid params.");
        return HI_ERR_CA_SSD_INVALID_PARAM;
    }

    memset(&stFlashInfo, 0, sizeof(stFlashInfo));
    hFlashHandle = HI_Flash_Open(HI_FLASH_TYPE_BUTT, LOADER_BOOT, (HI_U64)0, (HI_U64)0);
    if( HI_INVALID_HANDLE == hFlashHandle)
    {
        HI_ERR_CA_SSD("Failed to open partition 'boot' of flash");
        return HI_FAILURE;
    }

    s32Ret = HI_Flash_GetInfo(hFlashHandle, &stFlashInfo);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("Failed to get flash infomation.\n");
        HI_Flash_Close(hFlashHandle);
        return HI_FAILURE;
    }

    SSD_Malloc(pu8Buf, stFlashInfo.BlockSize);
    if ( NULL == pu8Buf)
    {
        HI_ERR_CA_SSD("Failed to malloc.\n");
        HI_Flash_Close(hFlashHandle);
        return HI_FAILURE;
    }

    s32Ret = HI_Flash_Read(hFlashHandle, 0, pu8Buf, stFlashInfo.BlockSize, HI_FLASH_RW_FLAG_RAW);
    if ( 0 > s32Ret )
    {
        HI_ERR_CA_SSD("Failed to read block 'boot' of flash.");
        SSD_Free(pu8Buf);
        HI_Flash_Close(hFlashHandle);
        return HI_FAILURE;
    }

    HI_Flash_Close(hFlashHandle);

    u8EncryptFlag = *(pu8Buf + SWPK_OFFSET + SWPK_LEN);
    if (SWPK_ENC_FLAG == u8EncryptFlag)
    {
        memcpy(pu8EncryptedSwpk, pu8Buf + SWPK_OFFSET, SWPK_LEN);
    }
    else
    {
        memset(pu8EncryptedSwpk, 0, SWPK_LEN);
        SSD_Free(pu8Buf);
        return HI_FAILURE;
    }

    SSD_Free(pu8Buf);

    return HI_SUCCESS;
}
#endif

HI_S32 CA_SSD_Init(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
	
#if defined (HI_ADVCA_TYPE_NAGRA)
    s32Ret = HI_SSD_Init();
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("ssd init failed.\n");
        return HI_ERR_CA_SSD_INIT_FAILED;
    }
#elif defined (HI_ADVCA_TYPE_VERIMATRIX)
	HI_S32 index = 0;

    s32Ret = vmxSSDPartitionInfoInit();
    if (HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("ssd init, call vmxSSDPartitionInfoInit failed.\n");
        return HI_ERR_CA_SSD_INIT_FAILED;
    }

	for(index = 0; index < VMX_SSD_MAX_PARTITIONS; index++)
	{
		g_stVMXSSD[index].bIsValid = HI_FALSE;
		g_stVMXSSD[index].bBurnFlag = HI_TRUE;	//default, need to burn
		g_stVMXSSD[index].u64FlashAddress = 0;
	}
#else
    s32Ret = SSD_ReadEncrytedSwpk((HI_U8 *)g_M2MEncryptedSWPK);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("ssd init, read swpk failed.\n");
        return HI_ERR_CA_SSD_INIT_FAILED;
    }
#endif

    return HI_SUCCESS;
}

HI_S32 CA_SSD_DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

#if defined (HI_ADVCA_TYPE_NAGRA)
    s32Ret = HI_SSD_DeInit();
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("ssd deinit failed.\n");
        return HI_ERR_CA_SSD_DEINIT_FAILED;
    }
#elif !defined (HI_ADVCA_TYPE_VERIMATRIX)
    memset(g_M2MEncryptedSWPK, 0, SWPK_LEN);
#endif

    return s32Ret;
}

#ifdef HI_ADVCA_TYPE_NAGRA
static HI_S32 SSD_UsbUpgrdPrepare(const UsbHeader *pstUsbHeader, HI_U8 *pu8FileBuffer, HI_U32 u32HeaderLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32DA2Addr = 0;
    HI_U32 u32DA2Size = 0;
    HI_U32 u32PartitionNum = 0;
    HI_U32 u32DA2Index = 0;
    HI_U32 offset = 0;
    HI_U32 u32DA2Pos = 0;
    HI_FLASH_TYPE_E enFlashType = HI_FLASH_TYPE_BUTT;
    UsbImgMap stUsbImgMapTmp;
    HI_U8 *pu8TmpBuf = HI_NULL;
    HI_U32 u32TmpSize = 0;

    if ( (NULL == pstUsbHeader) || ( 0 == u32HeaderLen ) || (NULL == pu8FileBuffer))
    {
        HI_ERR_CA_SSD("Invalid parameter input.\n");
        return HI_ERR_CA_SSD_INVALID_PARAM;
    }

    /* process DA2 */
    s32Ret = HI_SSD_GetDA2Address(&enFlashType, &u32DA2Addr, &u32DA2Size);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("ca ssd get da2 address failed.\n");
        return HI_ERR_CA_SSD_AUTH_FAILED;
    }

    u32PartitionNum = pstUsbHeader->astManuInfo[0].u16ImgMapNum;

    /* 寻找DA2分区 */
    for ( u32DA2Index = 0 ; u32DA2Index < u32PartitionNum; u32DA2Index++ )
    {
        if ( (u32DA2Addr == pstUsbHeader->astManuInfo[0].astImgMap[u32DA2Index].u32FlashAddr)
            && (enFlashType == pstUsbHeader->astManuInfo[0].astImgMap[u32DA2Index].uFlashType) )
        {
            HI_INFO_CA_SSD("DA2 exists.\n");
            break;
        }
    }

    if (u32DA2Index != u32PartitionNum)
    {
        /*分配用于数据交换所使用的内存空间*/
        pu8TmpBuf = (HI_U8 *)malloc(pstUsbHeader->astManuInfo[0].astImgMap[offset].u32FileLength);
        if (NULL == pu8TmpBuf)
        {
            HI_ERR_CA_SSD("There is no Usable Memory.\n");
            return HI_FAILURE;
        }

        memcpy(pu8TmpBuf, pu8FileBuffer + pstUsbHeader->astManuInfo[0].astImgMap[offset].u32Offset, pstUsbHeader->astManuInfo[0].astImgMap[offset].u32FileLength);
        memcpy(pu8FileBuffer + u32HeaderLen + pstUsbHeader->astManuInfo[0].astImgMap[offset].u32FileLength, pu8FileBuffer + u32HeaderLen, pstUsbHeader->astManuInfo[0].astImgMap[offset].u32Offset);
        memcpy(pu8FileBuffer + u32HeaderLen, pu8TmpBuf, pstUsbHeader->astManuInfo[0].astImgMap[offset].u32FileLength);

        LOADER_FreeUsableMemory(pu8TmpBuf);

        /* 交换分区，把DA2分区信息放在Header第一个分区 */
        memset(&stUsbImgMapTmp, 0, sizeof(stUsbImgMapTmp));
        memcpy(&stUsbImgMapTmp, &pstUsbHeader->astManuInfo[0].astImgMap[0], sizeof(stUsbImgMapTmp));
        memcpy(&pstUsbHeader->astManuInfo[0].astImgMap[0], &pstUsbHeader->astManuInfo[0].astImgMap[u32DA2Index], sizeof(stUsbImgMapTmp));
        memcpy(&pstUsbHeader->astManuInfo[0].astImgMap[u32DA2Index], &stUsbImgMapTmp, sizeof(stUsbImgMapTmp));
    }

    return HI_SUCCESS;
}
#endif  /*HI_ADVCA_TYPE_NAGRA*/

HI_S32 CA_SSD_AuthenticatePrepare(const HI_U32 *pu32LoaderHeader, HI_U8 *pu8FileBuffer, HI_U32 u32HeaderLen)
{
    HI_S32 s32Ret = HI_SUCCESS;
	
#ifdef HI_ADVCA_TYPE_NAGRA
    if ( (NULL == pu32LoaderHeader) || ( 0 == u32HeaderLen ) || (NULL == pu8FileBuffer))
    {
        HI_ERR_CA_SSD("Invalid parameter input.\n");
        return HI_ERR_CA_SSD_INVALID_PARAM;
    }

#if defined(HI_LOADER_PROTOCOL_HISI_FILE) || defined(HI_LOADER_PROTOCOL_HISI_OTA)
    UsbHeader *pstUsbHeader = (UsbHeader *)pu32LoaderHeader;
    s32Ret = SSD_UsbUpgrdPrepare(pstUsbHeader, pu8FileBuffer, u32HeaderLen);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("Usb upgrade prepare failed.\n");
        return HI_ERR_CA_SSD_AUTH_FAILED;
    }
#endif

#endif

    return s32Ret;
}

HI_S32 CA_SSD_DecryptUpgradeImage(HI_U8 *pu8Buffer, HI_U32 u32Len)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if ( (NULL == pu8Buffer) || (0 == u32Len) || (0xFFFFFFFF == u32Len) )
    {
        HI_ERR_CA_SSD("Invalid parameter input.\n");
        return HI_ERR_CA_SSD_INVALID_PARAM;
    }

#if !defined (HI_ADVCA_TYPE_NAGRA) && !defined (HI_ADVCA_TYPE_VERIMATRIX)
    s32Ret = CA_DecryptUpgradeImage(pu8Buffer, u32Len, g_M2MEncryptedSWPK);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("Decrypt upgrade image failed.\n");
        return HI_ERR_CA_SSD_DEC_FAILED;
    }
#elif defined (HI_ADVCA_TYPE_NAGRA)
    s32Ret = HI_SSD_DecryptUpgradeImage(pu8Buffer, u32Len);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("Decrypt upgrade image failed.\n");
        return HI_ERR_CA_SSD_DEC_FAILED;
    }
#endif

    return HI_SUCCESS;
}

HI_S32 CA_SSD_Authenticate(HI_U8 *ppu8Buffer, HI_U32 *pu32Len, HI_U32 u32FlashStartAddr, HI_U32 u32FlashType)
{
    HI_S32 s32Ret = HI_SUCCESS;
#ifdef HI_ADVCA_TYPE_NAGRA
    HI_SSD_BlockInfo_S stBlockInfo;
    HI_FLASH_TYPE_E enFlashType = HI_FLASH_TYPE_BUTT;
    LOADER_DATA_INFO_S *pstLoaderUpgrdInfo = NULL;
    HI_U32 u32DA2Addr = 0;
    HI_U32 u32DA2Size = 0;
    HI_U32 u32PartitionNum = 0;
#endif

    if ( (NULL == ppu8Buffer) || (NULL == pu32Len) )
    {
        HI_ERR_CA_SSD("Invalid parameter input.\n");
        return HI_ERR_CA_SSD_INVALID_PARAM;
    }

#if defined (HI_ADVCA_TYPE_NAGRA)
    memset(&stBlockInfo, 0, sizeof(stBlockInfo));
    s32Ret = HI_SSD_Authenticate(ppu8Buffer, *pu32Len, &stBlockInfo);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("ssd authenticate failed.\n");
        return HI_ERR_CA_SSD_AUTH_FAILED;
    }

    *pu32Len = stBlockInfo.u32BlockSize;
    ppu8Buffer += stBlockInfo.u32BlockOffset;

#elif defined (HI_ADVCA_TYPE_VERIMATRIX)
    if (HI_TRUE == vmxSSDIsSignatured(u32FlashStartAddr))
    {
        s32Ret = VMX_Verify_Authenticate(ppu8Buffer, *pu32Len, u32FlashStartAddr, u32FlashType);
        if (HI_SUCCESS != s32Ret )
        {
            HI_ERR_CA_SSD("ssd authenticate failed, ret: 0x%x.\n", s32Ret);
            return HI_ERR_CA_SSD_AUTH_FAILED;
        }
    }

#else
    s32Ret = CA_Verify_Authenticate(ppu8Buffer, *pu32Len);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_CA_SSD("ssd authenticate failed.\n");
        return HI_ERR_CA_SSD_AUTH_FAILED;
    }
#endif

    return HI_SUCCESS;
}

#ifdef HI_ADVCA_TYPE_VERIMATRIX
extern HI_S32 VMX_GetBurnParams(HI_U64 u64FlashAddress, HI_BOOL *pbNeedToBurn);
#endif

HI_S32 CA_SSD_BurnImageToFlash(HI_HANDLE hFlash, 
                                        HI_U64 u64FlashAddress, 
                                        HI_U8 *pBuf, 
                                        HI_U32 u32Len, 
                                        HI_U32 u32Flags,
                                        HI_FLASH_TYPE_E enFlashType,
                                        SSD_Burn_CallBack pFuncCallBackBurnData)
{
    HI_S32 ret = HI_SUCCESS;
#ifdef HI_ADVCA_TYPE_NAGRA
    HI_FLASH_TYPE_E enDA2FlashType = HI_FLASH_TYPE_BUTT;
    HI_U32 u32DA2Addr = 0;
    HI_U32 u32DA2Size = 0;
#endif

    if ( (NULL == pBuf) || (NULL == pFuncCallBackBurnData) || (0 == u32Len) )
    {
        HI_ERR_CA_SSD("Null pointer, Invalid parameter input.\n");
        return HI_ERR_CA_SSD_INVALID_PARAM;
    }

#if defined (HI_ADVCA_TYPE_NAGRA)
    ret = HI_SSD_GetDA2Address(&enDA2FlashType, &u32DA2Addr, &u32DA2Size);
    if ( HI_SUCCESS != ret )
    {
        HI_ERR_CA_SSD("ssd authenticate failed.\n");
        return HI_ERR_CA_SSD_AUTH_FAILED;
    }

    if ( (u32DA2Addr == (HI_U32)u64FlashAddress) && (enFlashType == enDA2FlashType) )
    {
        if(HI_FALSE == g_bDA2BurnedAlready)
        {
            HI_INFO_CA_SSD("DA2 exists.\n");
            ret = HI_SSD_DA2_Process(pBuf, u32Len);
            if ( HI_SUCCESS != ret )
            {
                HI_ERR_CA_SSD("ssd authenticate(DA2) failed.\n");
                return HI_ERR_CA_SSD_AUTH_FAILED;
            }
            g_bDA2BurnedAlready = HI_TRUE;
        }
    }
    else
    {
        ret = pFuncCallBackBurnData(hFlash, u64FlashAddress, pBuf, u32Len, u32Flags);
        if ( HI_SUCCESS != ret )
        {
            HI_ERR_CA_SSD("ca burn flash faield.\n");
            return HI_ERR_CA_SSD_BURN_FAILED;
        }
    }

#elif defined (HI_ADVCA_TYPE_VERIMATRIX)
	HI_Flash_InterInfo_S stFlashInfo;
	HI_BOOL bNeedToBurn = HI_FALSE;

	memset(&stFlashInfo, 0, sizeof(stFlashInfo));
	ret = HI_Flash_GetInfo(hFlash, &stFlashInfo);
	if(ret != HI_SUCCESS)
	{
		HI_ERR_CA_SSD("HI_Flash_GetInfo failed.\n");
		return HI_ERR_CA_SSD_BURN_FAILED;
	}

	ret = VMX_GetBurnParams(stFlashInfo.OpenAddr, &bNeedToBurn);
	if ( HI_SUCCESS != ret)
	{
		HI_ERR_CA_SSD("get burn params failed, flash address:0x%llx.\n", stFlashInfo.OpenAddr);
		return HI_ERR_CA_SSD_BURN_FAILED;
	}

	if(HI_FALSE == bNeedToBurn)
	{
		HI_ERR_CA_SSD("no need to burn:0x%llx\n", stFlashInfo.OpenAddr);
		return HI_SUCCESS;
	}

	HI_INFO_CA_SSD("begin to burn flash:0x%llx\n", stFlashInfo.OpenAddr);
	ret = pFuncCallBackBurnData(hFlash, u64FlashAddress, pBuf, u32Len, u32Flags);
	if ( 0 > ret)
	{
		HI_ERR_CA_SSD("ca burn flash failed.\n");
		return HI_ERR_CA_SSD_BURN_FAILED;
	}
	HI_INFO_CA_SSD("finish to burn flash:0x%llx\n", stFlashInfo.OpenAddr);
#else
    ret = pFuncCallBackBurnData(hFlash, u64FlashAddress, pBuf, u32Len, u32Flags);
    if ( 0 > ret)
    {
        HI_ERR_CA_SSD("ca burn flash failed.\n");
        return HI_ERR_CA_SSD_BURN_FAILED;
    }
#endif
    return HI_SUCCESS;
}
#endif  /*HI_ADVCA_SUPPORT*/

