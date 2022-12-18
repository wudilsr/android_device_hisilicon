/*******************************************************************************
 *             Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: burn_ca.c
 * Description: Burn function for ca
 *
 * History:
 * Version   Date               Author          DefectNum    Description
 * main1     2013-10-25    m00190812
 ******************************************************************************/
#ifndef __BURN_CA_C__
#define __BURN_CA_C__

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif
#include "loader_upgrade.h"
#include "hi_loader_info.h"
#include "upgrd_osd.h"
#include "loaderdb_info.h"
#include "upgrd_common.h"
#include "hi_flash.h"
#include "upgrd_emmc.h"
#include "ca_ssd.h"
#include "wrapper_ca.h"
#include "burn.h"

extern FLASH_DATA_INFO_S *g_pstFlashDataInfo;

/*****************************************************************************
* Function:      UpgrdPro_UpdateData
* Description:   update data to flash
* Data Accessed:
* Data Updated:
* Input:            HI_VOID*
* Output:           None
* Return: HI_SUCCESS
* Others:
*****************************************************************************/
HI_S32 LOADER_BURN_WriteData_CA(FLASH_DATA_INFO_S *pstFlashDataInfo, HI_U8 * pucSrcDataBuff, HI_U32 u32SrcDataLen, HI_VOID * private)
{
    HI_S32 ret = HI_SUCCESS;
    HI_S64 s64Ret = HI_SUCCESS;
    HI_HANDLE hHandle = HI_INVALID_HANDLE;
    HI_U32 u32DataLen = 0;
    HI_U32 i = 0;
    HI_U32 u32Times = 0;
    HI_U64 u64WriteOffset = 0;
    HI_U8 *pu8DataBuf = NULL;
    HI_FLASH_TYPE_E enFlashType = HI_FLASH_TYPE_BUTT;

    if (HI_NULL == pucSrcDataBuff || HI_NULL == pstFlashDataInfo)
    {
        return HI_UPGRD_ERR_PARA;
    }
    
    hHandle = pstFlashDataInfo->hFlashHandle;
    enFlashType = pstFlashDataInfo->enFlashType;
    pu8DataBuf = pucSrcDataBuff;
    u32DataLen = u32SrcDataLen;

    if (HI_FALSE == pstFlashDataInfo->bErased)
    {
        if((HI_FLASH_TYPE_SPI_0 == enFlashType) || (HI_FLASH_TYPE_NAND_0 == enFlashType))
        {
            s64Ret = HI_Flash_Erase64(hHandle, (HI_U64)0, pstFlashDataInfo->u64PartitionSize);
            if (0 > s64Ret)
            {
                HI_ERR_LOADER("Erase flash error! s64Ret:0x%x\n", s64Ret);
                return HI_UPGRD_UPGRDPRO_WRFLASH;
            }
        }

        pstFlashDataInfo->bErased = HI_TRUE;
    }

    ret = CA_SSD_EncryptImage(pu8DataBuf, u32DataLen, CA_SSD_KEY_GROUP1);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_LOADER("CA SSD Encrypt Image error!\n");
        return (HI_S32)HI_UPGRD_CA_SSD_CRYPT_FAIL;
    }

    u32Times = u32DataLen / LOADER_BURN_SIZE_PERTIME;
    u64WriteOffset = pstFlashDataInfo->u64WriteOffset;
    for (i = 1; i < u32Times; i++)
    {
        ret = CA_SSD_BurnImageToFlash(hHandle,
                                      u64WriteOffset,
                                      pu8DataBuf,
                                      LOADER_BURN_SIZE_PERTIME,
                                      pstFlashDataInfo->u32WriteFlags,
                                      enFlashType,
                                      HI_Flash_Write);
        if (0 > ret)
        {
            HI_ERR_LOADER("Write flash error!\n");
            return (HI_S32)HI_UPGRD_UPGRDPRO_WRFLASH;
        }

        u64WriteOffset += LOADER_BURN_SIZE_PERTIME;
        pu8DataBuf += LOADER_BURN_SIZE_PERTIME;

        if (g_pfnOSDCallback)
        {
            IncCurWriteLen(LOADER_BURN_SIZE_PERTIME);
            g_pfnOSDCallback(OSD_EVENT_TYPE_BURN, GetCurWriteLen(), GetTotalWriteLen());
        }
    }

    ret = CA_SSD_BurnImageToFlash(hHandle,
                                  u64WriteOffset,
                                  pu8DataBuf,
                                  (0 == u32Times)?u32DataLen:LOADER_BURN_SIZE_PERTIME + u32DataLen % LOADER_BURN_SIZE_PERTIME,
                                  pstFlashDataInfo->u32WriteFlags,
                                  enFlashType,
                                  HI_Flash_Write);
    if (0 > ret)
    {
        HI_ERR_LOADER("Write flash error!\n");
        return (HI_S32)HI_UPGRD_UPGRDPRO_WRFLASH;
    }
    u64WriteOffset += ((0 == u32Times)?u32DataLen:LOADER_BURN_SIZE_PERTIME + u32DataLen % LOADER_BURN_SIZE_PERTIME);

    if (g_pfnOSDCallback)
    {
        IncCurWriteLen(LOADER_BURN_SIZE_PERTIME);
        g_pfnOSDCallback(OSD_EVENT_TYPE_BURN, GetCurWriteLen(), GetTotalWriteLen());
    }

    return HI_SUCCESS;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif  /*__BURN_CA_C__*/
