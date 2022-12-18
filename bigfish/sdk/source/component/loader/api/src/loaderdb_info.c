/*******************************************************************************
 *             Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: upgrdstartup.c
 * Description:
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 ******************************************************************************/
#include "hi_loader_info.h"
#include "hi_flash.h"
#include "crc32.h"
#include "loaderdb_info.h"
#include "ca_ssd.h"

/* for avoid conflict with libhiloader.a & so */
#if defined(HI_LOADER_BOOTLOADER) || defined(HI_LOADER_APPLOADER)
#include "upgrd_common.h"
#else
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 #undef HI_FATAL_LOADER 
 #undef HI_ERR_LOADER        
 #undef HI_WARN_LOADER     
 #undef HI_INFO_LOADER 
 #undef HI_DBG_LOADER

 /* for debug libhiloader.a */
 #define HI_ERR_LOADER(arg...) HI_PRINT(arg)
 #define HI_INFO_LOADER(arg...) 
 #define HI_DBG_LOADER(arg...) 
#endif

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define PARTION_NAME_LEN (32)

typedef struct tagLOADER_DATABLOCK_INFO_S
{
    HI_CHAR         ac8PartionName[PARTION_NAME_LEN];     /*数据所在分区的分区名，在bootargs中描述，不同数据
                                                          可能位于同一分区内，此时这些数据的分区名相同*/
    HI_FLASH_TYPE_E eFlashType;                     /*分区所在Flash的类型*/
    HI_U32          u32Offset;                          /*数据在分区中的地址偏移,如某分区只保存一种数据，
                                                        则这种数据的地址偏移位０*/
    HI_U32          u32Size;                            /*数据在分区中预留的长度*/
} LOADER_DATABLOCK_INFO_S;

#define SAVE_FREE( p ) \
    do {\
        if (p){\
            free(p); p = NULL;} \
    } while (0)

static HI_S32 Upgrd_checkTagSector(HI_U8 *pucBuf);
static HI_S32 Upgrd_checkOtaSector(HI_U8 *pucBuf);

HI_S32 Upgrd_ReadLoaderDBInfo(UPGRD_LOADER_INFO_S *pstInfoParam)
{
	HI_U8 *au8Buf1 = NULL;
	HI_U8 *au8Buf2 = NULL;

	HI_U32 u32Offset1 = 0;
	HI_U32 u32Offset2 = 0;
	HI_U32 u32Size1 = 0;
	HI_U32 u32Size2 = 0;

	HI_U32 u32RegionSize1 = 0;
	HI_U32 u32RegionSize2 = 0;

	HI_HANDLE hMainHandle = HI_INVALID_HANDLE;
	HI_HANDLE hBakHandle = HI_INVALID_HANDLE;

	HI_S8  s8SaveTodb      = 0;
	HI_S8  s8SaveTodbbak = 0;

	UPGRD_LOADER_INFO_S  *basicInfo = NULL;
	UPGRD_LOADER_INFO_S  *bakupInfo = NULL;

	HI_S32 s32Ret = HI_FAILURE;

	if (NULL == pstInfoParam)
	{
		HI_ERR_LOADER("invalid input params.");
		return HI_FAILURE;
	}

	/* 1: loaderdb */
	if (HI_SUCCESS != Upgrd_OpenDataBlock(LOADERDB, &hMainHandle, &u32RegionSize1, &u32Offset1, &u32Size1))
	{
		s32Ret = HI_FAILURE;
		goto out;
	}
	else 
	{
		/* check size is enough */
		if (u32Size1 < sizeof(UPGRD_LOADER_INFO_S) || (u32Offset1 + u32Size1 > u32RegionSize1))
		{
			HI_ERR_LOADER("%s offset:0x%08x Or size:0x%08x invalid .\n", LOADERDB, u32Offset1, u32Size1);
			s32Ret = HI_FAILURE;
			goto out;
		}

		/* prepare flash block buffer */
		au8Buf1 = (HI_U8*)malloc(u32RegionSize1);
		if (NULL == au8Buf1)
		{
			s32Ret = HI_FAILURE;
			goto out;
		}

		HI_DBG_LOADER(" %s regionSize:0x%08x, offset: 0x%08x, size: 0x%08x\n", LOADERDB, u32RegionSize1, u32Offset1, u32Size1);

		/* NOT check return value for badblock */
		HI_Flash_Read(hMainHandle, (HI_U64)0, au8Buf1, u32RegionSize1, HI_FLASH_RW_FLAG_RAW);

        s32Ret = CA_SSD_DecryptImage(au8Buf1, u32RegionSize1, CA_SSD_KEY_GROUP2);
        if ( HI_SUCCESS != s32Ret )
        {
			goto out;
        }

		if (u32Offset1 < u32RegionSize1)
		{
			basicInfo = (UPGRD_LOADER_INFO_S*)(au8Buf1 + u32Offset1);
		}
		else
		{
			s32Ret = HI_FAILURE;
			goto out;
		}

		if ((HI_SUCCESS == Upgrd_checkTagSector(au8Buf1 + u32Offset1))
				&& (HI_SUCCESS == Upgrd_checkOtaSector(au8Buf1 + u32Offset1)))
		{
			memcpy(pstInfoParam, basicInfo, sizeof(UPGRD_LOADER_INFO_S));
			s32Ret = HI_SUCCESS;
			goto out;
		}
	}

	/* 2: loaderdbbak if exist */
	if (HI_SUCCESS != Upgrd_OpenDataBlock(LOADERDBBAK, &hBakHandle, &u32RegionSize2, &u32Offset2, &u32Size2))
	{
		u32RegionSize2 = sizeof(UPGRD_LOADER_INFO_S); /* avoid malloc 0 bytes space checking */
		HI_DBG_LOADER("loaderdbbak not existed.\n");
	}
	else
	{
		/*loaderdb and loaderdbbak region size must be same */
		if (u32RegionSize1 != u32RegionSize2)
		{
			HI_ERR_LOADER("loaderdb regionSize(%u) is not same with loaderdbbak regionSize(%u). ", u32RegionSize1, u32RegionSize2);
			s32Ret = HI_FAILURE;
			goto out;
		}

		/* check size is enough */
		if (u32Size2 < sizeof(UPGRD_LOADER_INFO_S) || (u32Offset2 + u32Size2 > u32RegionSize2) )
		{
			HI_ERR_LOADER("%s offset:0x%08x Or size:0x%08x invalid .\n", LOADERDBBAK, u32Offset2, u32Size2);
			s32Ret = HI_FAILURE;
			goto out;
		}

		/* prepare flash block buffer */
		au8Buf2 = (HI_U8*)malloc(u32RegionSize2);
		if (NULL == au8Buf2)
		{
			s32Ret = HI_FAILURE;
			goto out;
		}

		HI_DBG_LOADER(" %s regionSize:0x%08x, offset: 0x%08x, size: 0x%08x\n", LOADERDBBAK, u32RegionSize2, u32Offset2, u32Size2);

		/* NOT check return value for badblock */
		HI_Flash_Read(hBakHandle, (HI_U64)0, au8Buf2, u32RegionSize2, HI_FLASH_RW_FLAG_RAW);

        s32Ret = CA_SSD_DecryptImage(au8Buf2, u32RegionSize2, CA_SSD_KEY_GROUP2);
        if ( HI_SUCCESS != s32Ret )
        {
			goto out;
        }

		if (u32Offset2  <  u32RegionSize2)
		{
			bakupInfo = (UPGRD_LOADER_INFO_S*)(au8Buf2 + u32Offset2);
		}		
		else
		{
			s32Ret = HI_FAILURE;
			goto out;
		}

		if ((HI_SUCCESS == Upgrd_checkTagSector(au8Buf2 + u32Offset2))
				&& (HI_SUCCESS == Upgrd_checkOtaSector(au8Buf2 + u32Offset2)))
		{
			HI_DBG_LOADER("Get upgrade tag info from loaderdbbak ok.\n");
			
			memcpy(pstInfoParam, bakupInfo, sizeof(UPGRD_LOADER_INFO_S));
			memcpy(basicInfo, bakupInfo, sizeof(UPGRD_LOADER_INFO_S));

            s32Ret = CA_SSD_EncryptImage(au8Buf1, u32RegionSize1, CA_SSD_KEY_GROUP2);
            if ( HI_SUCCESS != s32Ret )
            {
    			goto out;
            }

			/* for bad block ,this call maybe failed. */
			if (0 >= HI_Flash_Write(hMainHandle, (HI_U64)0, au8Buf1, u32RegionSize1, HI_FLASH_RW_FLAG_ERASE_FIRST))
			{
				HI_INFO_LOADER("[Warning]sync loaderdb from loaderdbbak failed but continue to run normally.\n");
			}
			else
			{
				HI_DBG_LOADER("Sync upgrade tag info to loaderdb partition finished.\n ");
			}
			
			s32Ret = HI_SUCCESS;
			goto out;
		}
	}

	/* 3: Both of the main block and the backup(if existed) block are not correct, use the default */
	/* setting to update the main block                   */

	HI_ERR_LOADER("[Warning] both Sector damage, use default setting\n");
	
	if (HI_SUCCESS != Upgrd_checkTagSector(au8Buf1 + u32Offset1))
	{
		basicInfo->stTagParaHead.u32MagicNumber = LOADER_MAGIC_NUMBER;
		basicInfo->stTagParaHead.u32Length = sizeof(UPGRD_TAG_PARA_S);

		basicInfo->stTagPara.bTagNeedUpgrd = HI_FALSE;
		basicInfo->stTagPara.bTagManuForceUpgrd = HI_FALSE;

		basicInfo->stTagParaHead.u32Crc = crc32(0, au8Buf1 + u32Offset1 + sizeof(UPGRD_PARA_HEAD_S) - sizeof(HI_U32),
				(basicInfo->stTagParaHead.u32Length + sizeof(HI_U32)));

		HI_DBG_LOADER("write tag crc: 0x%08x\n", basicInfo->stTagParaHead.u32Crc);
	}

	basicInfo->stLoaderParaHead.u32MagicNumber = LOADER_MAGIC_NUMBER;
	basicInfo->stLoaderParaHead.u32Length = sizeof(HI_LOADER_PARAMETER_S) + sizeof(UPGRD_PRIVATE_PARAM_S);

	memset(&basicInfo->stLoaderParam, 0x00, sizeof(HI_LOADER_PARAMETER_S));
	basicInfo->stLoaderPrivate.u32FailedCnt = 0;
	basicInfo->stLoaderPrivate.bTagDestroy = HI_FALSE;
	basicInfo->stLoaderParam.eUpdateType = HI_LOADER_TYPE_BUTT;
	/*
		 *******************************************************************
		 * UPGRD_PARA_HEAD_S     stLoaderParaHead;
		 *    HI_U32 u32MagicNumber;
		 *    HI_U32 u32Crc;
		 *    HI_U32 u32Length;                       ---|
		 * HI_LOADER_PARAMETER_S stLoaderParam;       ---| ==> crc region 
		 * UPGRD_PRIVATE_PARAM_S stLoaderPrivate;     ---|
		 *******************************************************************
	*/
	basicInfo->stLoaderParaHead.u32Crc = crc32(0, (HI_U8*)&basicInfo->stLoaderParaHead.u32Length,
			(sizeof(basicInfo->stLoaderParaHead.u32Length)  + basicInfo->stLoaderParaHead.u32Length ));

	HI_DBG_LOADER("write ota crc: 0x%08x\n", basicInfo->stLoaderParaHead.u32Crc);

    s32Ret = CA_SSD_EncryptImage(au8Buf1, u32RegionSize1, CA_SSD_KEY_GROUP2);
    if ( HI_SUCCESS != s32Ret )
    {
		goto out;
    }

	if (0 >= HI_Flash_Write(hMainHandle, (HI_U64)0, au8Buf1, u32RegionSize1, HI_FLASH_RW_FLAG_ERASE_FIRST))
	{
		HI_DBG_LOADER("Failed to write block '%s' of flash.", LOADERDB);
		s8SaveTodb = 0;
	}
	else
	{
		s8SaveTodb = 1;
	}

	memcpy(pstInfoParam, basicInfo, sizeof(UPGRD_LOADER_INFO_S));

	/*update info to backup partition*/
	if (HI_INVALID_HANDLE != hBakHandle && NULL != bakupInfo)
	{
		memcpy(bakupInfo, basicInfo, sizeof(UPGRD_LOADER_INFO_S));

        s32Ret = CA_SSD_EncryptImage(au8Buf2, u32RegionSize2, CA_SSD_KEY_GROUP2);
        if ( HI_SUCCESS != s32Ret )
        {
    		goto out;
        }

		if (0 >= HI_Flash_Write(hBakHandle, (HI_U64)0, au8Buf2, u32RegionSize2, HI_FLASH_RW_FLAG_ERASE_FIRST))
		{	
			HI_DBG_LOADER("Failed to write block '%s' of flash.\n", LOADERDBBAK);
			s8SaveTodbbak =  0;
		}
		else
		{
			s8SaveTodbbak =  1;
		}
	}

	/* AT least one of db partition saved successful  */
	if (s8SaveTodb || (HI_INVALID_HANDLE != hBakHandle && s8SaveTodbbak) )
	{
		s32Ret = HI_SUCCESS;
	}
	else
	{
		HI_ERR_LOADER("Failed to save upgrade parameter into %s or %s partition.\n", LOADERDB, LOADERDBBAK);
		s32Ret = HI_FAILURE;
	}

out:
	SAVE_FREE(au8Buf1);
	SAVE_FREE(au8Buf2);
	
	if (HI_INVALID_HANDLE != hBakHandle)
		HI_Flash_Close(hBakHandle);
	if (HI_INVALID_HANDLE != hMainHandle)
		HI_Flash_Close(hMainHandle);

	return s32Ret;
}

HI_S32 Upgrd_WriteLoaderDBInfo(UPGRD_LOADER_INFO_S *pstInfoParam)
{
	HI_U32 u32RegionSize1 = 0;
	HI_U32 u32RegionSize2 = 0;
	
	HI_U32 u32Offset = 0;
	HI_U32 u32Size = 0;
	
	HI_HANDLE hMainHandle = HI_INVALID_HANDLE;
	HI_HANDLE hBakHandle = HI_INVALID_HANDLE;
	
	HI_S8  s8SaveTodb      = 0;
	HI_S8  s8SaveTodbbak = 0;
	
	HI_U8 *pucBuf1 = NULL;
	HI_U8 *pucBuf2 = NULL;

	HI_S32 s32Ret = HI_FAILURE;

	if (NULL == pstInfoParam)
	{
		HI_ERR_LOADER("invaled params.");
		return HI_FAILURE;
	}

	/* 1: loaderdb */
	if (HI_SUCCESS != Upgrd_OpenDataBlock(LOADERDB, &hMainHandle, &u32RegionSize1, &u32Offset, &u32Size))
	{
		s32Ret = HI_FAILURE;
		goto out;
	}
	else 
	{
		/* check size is enough */
		if (u32Size < sizeof(UPGRD_LOADER_INFO_S) || (u32Offset + u32Size > u32RegionSize1))
		{
			HI_ERR_LOADER("%s offset:0x%08x Or size:0x%08x invalid .\n", LOADERDB, u32Offset, u32Size);
			s32Ret = HI_FAILURE;
			goto out;
		}

		/* prepare flash block buffer */
		if (NULL == (pucBuf1 = (HI_U8*)malloc(u32RegionSize1)))
		{
			s32Ret = HI_FAILURE;
			goto out;
		}

		HI_DBG_LOADER(" %s offset: 0x%08x, size: 0x%08x\n", LOADERDB, u32Offset, u32Size);

		/* NOT check return value for badblock */
		HI_Flash_Read(hMainHandle, (HI_U64)0, pucBuf1, u32RegionSize1, HI_FLASH_RW_FLAG_RAW);

        s32Ret = CA_SSD_DecryptImage(pucBuf1, u32RegionSize1, CA_SSD_KEY_GROUP2);
        if ( HI_SUCCESS != s32Ret )
        {
            goto out;
        }

		/*Set Tag parameter head.*/
		pstInfoParam->stTagParaHead.u32MagicNumber = LOADER_MAGIC_NUMBER;
		pstInfoParam->stTagParaHead.u32Length = sizeof(UPGRD_TAG_PARA_S);

		pstInfoParam->stTagParaHead.u32Crc = crc32(0, (HI_U8*)pstInfoParam + sizeof(UPGRD_PARA_HEAD_S) - sizeof(HI_U32),
				(pstInfoParam->stTagParaHead.u32Length + sizeof(HI_U32)));

		/*Set Ota parameter head.*/
		pstInfoParam->stLoaderParaHead.u32MagicNumber = LOADER_MAGIC_NUMBER;
		pstInfoParam->stLoaderParaHead.u32Length = sizeof(HI_LOADER_PARAMETER_S) + sizeof(UPGRD_PRIVATE_PARAM_S);

		/*
		 *******************************************************************
		 * UPGRD_PARA_HEAD_S     stLoaderParaHead;
		 *    HI_U32 u32MagicNumber;
		 *    HI_U32 u32Crc;
		 *    HI_U32 u32Length;                       ---|
		 * HI_LOADER_PARAMETER_S stLoaderParam;       ---| ==> crc region 
		 * UPGRD_PRIVATE_PARAM_S stLoaderPrivate;     ---|
		 *******************************************************************
		*/
		pstInfoParam->stLoaderParaHead.u32Crc = crc32(0, (HI_U8*)&pstInfoParam->stLoaderParaHead.u32Length,
				( sizeof(pstInfoParam->stLoaderParaHead.u32Length) + pstInfoParam->stLoaderParaHead.u32Length ));

		if (u32Offset < u32RegionSize1)
		{
			memcpy(pucBuf1 + u32Offset, pstInfoParam, sizeof(UPGRD_LOADER_INFO_S));
		}
		else
		{
			s32Ret = HI_FAILURE;
			goto out;
		}

		HI_DBG_LOADER("loaderdb offset: 0x%08x, size: 0x%08x\n", u32Offset, u32Size);

        s32Ret = CA_SSD_EncryptImage(pucBuf1, u32RegionSize1, CA_SSD_KEY_GROUP2);
        if ( HI_SUCCESS != s32Ret )
        {
            goto out;
        }

		/* Writing data to the main block */
		if (0 >= HI_Flash_Write(hMainHandle, (HI_U64)0, (HI_U8*)pucBuf1, u32RegionSize1, HI_FLASH_RW_FLAG_ERASE_FIRST))
		{
			HI_DBG_LOADER("Failed to write block '%s' of flash.", LOADERDB);
			s8SaveTodb = 0;
		}
		else
		{
			s8SaveTodb = 1;
		}
	}

	/* 2: loaderdbbak if exist */
	if (HI_SUCCESS != Upgrd_OpenDataBlock(LOADERDBBAK, &hBakHandle, &u32RegionSize2, &u32Offset, &u32Size))
	{
		u32RegionSize2 = sizeof(UPGRD_LOADER_INFO_S); /* avoid malloc 0 bytes space checking */
		HI_DBG_LOADER("loaderdbbak not existed.\n");
	}
	else  
	{
		/*loaderdb and loaderdbbak region size must be same */
		if (u32RegionSize1 != u32RegionSize2)
		{
			HI_ERR_LOADER("loaderdb regionSize(%u) is not same with loaderdbbak regionSize(%u). ", u32RegionSize1, u32RegionSize2);
			s32Ret = HI_FAILURE;
			goto out;
		}
		
		/* check size is enough */
		if (u32Size < sizeof(UPGRD_LOADER_INFO_S) || (u32Offset + u32Size > u32RegionSize2))
		{
			HI_ERR_LOADER("%s offset:0x%08x Or size:0x%08x invalid .\n", LOADERDB, u32Offset, u32Size);
			s32Ret = HI_FAILURE;
			goto out;
		}

		/* prepare flash block buffer */
		if (NULL == (pucBuf2 = (HI_U8*)malloc(u32RegionSize2)))
		{
			HI_ERR_LOADER("Failed to malloc space.");
			s32Ret = HI_FAILURE;
			goto out;
		}

		HI_DBG_LOADER("loaderdbbak offset: 0x%08x, size: 0x%08x\n", u32Offset, u32Size);

		/* NOT check return value for badblock */
		HI_Flash_Read(hBakHandle, (HI_U64)0, pucBuf2, u32RegionSize2, HI_FLASH_RW_FLAG_RAW);

        s32Ret = CA_SSD_DecryptImage(pucBuf2, u32RegionSize2, CA_SSD_KEY_GROUP2);
        if ( HI_SUCCESS != s32Ret )
        {
            goto out;
        }

		if (u32Offset < u32RegionSize2)
		{
			memcpy(pucBuf2 + u32Offset, pstInfoParam, sizeof(UPGRD_LOADER_INFO_S));
		}
		else
		{
			s32Ret = HI_FAILURE;
			goto out;
		}

        s32Ret = CA_SSD_EncryptImage(pucBuf2, u32RegionSize2, CA_SSD_KEY_GROUP2);
        if ( HI_SUCCESS != s32Ret )
        {
            goto out;
        }

		/* Keeping a backup of original parameters */
		if (0 >= HI_Flash_Write(hBakHandle, (HI_U64)0, (HI_U8*)pucBuf2, u32RegionSize2, HI_FLASH_RW_FLAG_ERASE_FIRST))
		{
			HI_DBG_LOADER("Failed to write block '%s' of flash.", LOADERDBBAK);
			s8SaveTodbbak = 0;
		}
		else
		{
			s8SaveTodbbak = 1;
		}
	}

	/* 3: AT least one of db partition saved successful */
	if (s8SaveTodb || (HI_INVALID_HANDLE != hBakHandle && s8SaveTodbbak ))
	{
		s32Ret = HI_SUCCESS;
	}
	else
	{
		HI_ERR_LOADER("Failed to save upgrade parameter into %s or %s partition.\n", LOADERDB, LOADERDBBAK);
		s32Ret = HI_FAILURE;
	}
	
	HI_DBG_LOADER("update loaderdb success.\n");

out:
	SAVE_FREE(pucBuf2);
	SAVE_FREE(pucBuf1);

	if (HI_INVALID_HANDLE != hBakHandle )
		HI_Flash_Close(hBakHandle);
	if (HI_INVALID_HANDLE != hMainHandle)
		HI_Flash_Close(hMainHandle);

	return s32Ret;
}

HI_S32 Upgrd_ClearRequest(UPGRD_LOADER_INFO_S *pstLoaderInfo)
{
	//add for first time to use dataclr

	pstLoaderInfo->stLoaderPrivate.u32FailedCnt = 0;
	pstLoaderInfo->stLoaderParam.eUpdateType = HI_LOADER_TYPE_BUTT;
	pstLoaderInfo->stTagPara.bTagNeedUpgrd = HI_FALSE;
	Upgrd_WriteLoaderDBInfo(pstLoaderInfo);

	return HI_SUCCESS;
}

static HI_S32 Upgrd_checkTagSector(HI_U8 *pucBuf)
{
	UPGRD_LOADER_INFO_S *pstInfoParam;
	HI_U32 u32Crc = 0;

	if (HI_NULL == pucBuf)
	{
		HI_ERR_LOADER("Invalid pointer parameter.");
		return HI_FAILURE;
	}

	pstInfoParam = (UPGRD_LOADER_INFO_S *)pucBuf;

	if (LOADER_MAGIC_NUMBER == pstInfoParam->stTagParaHead.u32MagicNumber)
	{
		u32Crc = crc32(0, pucBuf + sizeof(UPGRD_PARA_HEAD_S) - sizeof(HI_U32),
				(pstInfoParam->stTagParaHead.u32Length + sizeof(HI_U32)));

		if (u32Crc == pstInfoParam->stTagParaHead.u32Crc)
		{
			return HI_SUCCESS;
		}
		else
		{
			HI_ERR_LOADER("read tag crc: 0x%08x, cal crc: 0x%08x\n", pstInfoParam->stTagParaHead.u32Crc, u32Crc);
		}
	}

	HI_DBG_LOADER("Failed to check tag sector.\n");
	return HI_FAILURE;
}

static HI_S32 Upgrd_checkOtaSector(HI_U8 *pucBuf)
{
	UPGRD_LOADER_INFO_S *pstInfoParam;
	HI_U32 u32Crc = 0;

	if (HI_NULL == pucBuf)
	{
		HI_ERR_LOADER("Invalid pointer parameter.");
		return HI_FAILURE;
	}

	pstInfoParam = (UPGRD_LOADER_INFO_S *)pucBuf;

	if (LOADER_MAGIC_NUMBER == pstInfoParam->stLoaderParaHead.u32MagicNumber)
	{
		/*
		 *******************************************************************
		 * UPGRD_PARA_HEAD_S     stLoaderParaHead;
		 *    HI_U32 u32MagicNumber;
		 *    HI_U32 u32Crc;
		 *    HI_U32 u32Length;                       ---|
		 * HI_LOADER_PARAMETER_S stLoaderParam;       ---| ==> crc region 
		 * UPGRD_PRIVATE_PARAM_S stLoaderPrivate;     ---|
		 *******************************************************************
		*/
		u32Crc = crc32(0, (HI_U8*)&pstInfoParam->stLoaderParaHead.u32Length,
				(sizeof(pstInfoParam->stLoaderParaHead.u32Length) + pstInfoParam->stLoaderParaHead.u32Length));

		if (u32Crc == pstInfoParam->stLoaderParaHead.u32Crc)
		{
			return HI_SUCCESS;
		}
		else
		{
			HI_ERR_LOADER("read ota crc: 0x%08x, cal crc: 0x%08x\n", pstInfoParam->stLoaderParaHead.u32Crc, u32Crc);
		}
	}

	HI_DBG_LOADER("Failed to check ota sector.\n");
	return HI_FAILURE;
}

/*
 * search loader config parameter from bootargs in secondary style: loaderdb=part_name,offset,size.
 */
static HI_S32 GetDataBlockInfo(const HI_CHAR *pstrDataName, const HI_CHAR *bootargs,
		LOADER_DATABLOCK_INFO_S *pstDataInfo)
{
	HI_CHAR *pstr  = (HI_CHAR *)pstrDataName;
	HI_CHAR *pstr2 = (HI_CHAR *)bootargs;
	HI_CHAR buf[12];

	if ((HI_NULL == pstrDataName) || (HI_NULL == bootargs) || (HI_NULL == pstDataInfo))
		return HI_FAILURE;

	pstr = strstr(pstr2, pstr);

	if ((HI_NULL == pstr) || (strlen(pstr) <= strlen(pstrDataName)))
		return HI_FAILURE;

	if (pstr[strlen(pstrDataName)] == '=')
	{
		/* get partition name */
		pstr += strlen(pstrDataName) + 1; //point to the char after '='
		pstr2 = strstr(pstr, ",");

		if (HI_NULL == pstr2)
			return HI_FAILURE;

		if ((HI_U32)(pstr2 - pstr) >= sizeof(pstDataInfo->ac8PartionName))
		{
			HI_ERR_LOADER("datablock name is too long in bootargs!");
			return HI_FAILURE;
		}

		memset(pstDataInfo->ac8PartionName, 0, sizeof(pstDataInfo->ac8PartionName));
		memcpy(pstDataInfo->ac8PartionName, pstr, pstr2 - pstr);

		/* get offset */
		pstr  = pstr2 + 1;
		pstr2 = strstr(pstr, ",");

		if (HI_NULL == pstr2)
			return HI_FAILURE;

		if ((HI_U32)(pstr2 - pstr) >= sizeof(buf))
		{
			HI_ERR_LOADER("offset is invalid in bootargs!");
			return HI_FAILURE;
		}

		memset(buf, 0, sizeof(buf));
		memcpy(buf, pstr, pstr2 - pstr);
#ifdef HI_LOADER_BOOTLOADER
		pstDataInfo->u32Offset = simple_strtoul(buf, HI_NULL, 16);
#else
		pstDataInfo->u32Offset = strtoul(buf, HI_NULL, 16);    
#endif
		/* get size */
		pstr  = pstr2 + 1;
		pstr2 = strstr(pstr, " ");

		if (HI_NULL == pstr2)
			return HI_FAILURE;

		if ((HI_U32)(pstr2 - pstr) >= sizeof(buf))
		{
			HI_ERR_LOADER("size is invalid in bootargs!");
			return HI_FAILURE;
		}

		memset(buf, 0, sizeof(buf));
		memcpy(buf, pstr, pstr2 - pstr);
#ifdef HI_LOADER_BOOTLOADER
		pstDataInfo->u32Size = simple_strtoul(buf, HI_NULL, 16);
#else
		pstDataInfo->u32Size = strtoul(buf, HI_NULL, 16);    
#endif
		return HI_SUCCESS;
	}

	return HI_FAILURE;
}

#ifdef HI_LOADER_BOOTLOADER
static HI_CHAR* get_bootargs(HI_VOID)
{
	return getenv("bootargs");
}
#else
static HI_CHAR* get_bootargs(HI_VOID)
{
	/* bootargs size according to arch/arm/include/asm/setup.h COMMAND_LINE_SIZE */
	static HI_CHAR bootargs[1024];
	FILE *pf;

	if (NULL == (pf = fopen("/proc/cmdline", "r")))
	{
		HI_ERR_LOADER("Failed to open '/proc/cmdline'.\n");
		return HI_NULL;
	}

	if (NULL == fgets((char*)bootargs, sizeof(bootargs), pf))
	{
		HI_ERR_LOADER("Failed to fgets string.\n");
		fclose(pf);
		return HI_NULL;
	}

	fclose(pf);
	
	return bootargs;
}
#endif

HI_S32 Upgrd_OpenDataBlock(const HI_CHAR* pstDBName, HI_HANDLE *hFlash, HI_U32 *pu32RegionSize, HI_U32 *pu32Offset,
		HI_U32 *pu32Size)
{
	HI_Flash_InterInfo_S stFlashInfo;
	LOADER_DATABLOCK_INFO_S stDBInfo;

	if ((HI_NULL == pstDBName)
			|| (HI_NULL == hFlash)
			|| (HI_NULL == pu32RegionSize)
			|| (HI_NULL == pu32Offset)
			|| (HI_NULL == pu32Size))
	{
		return HI_FAILURE;
	}

	*hFlash = HI_Flash_Open(HI_FLASH_TYPE_BUTT, (HI_CHAR*)pstDBName, (HI_U64)0, (HI_U64)0);

	if (HI_INVALID_HANDLE == *hFlash)
	{        
		HI_CHAR *bootargs = get_bootargs();
		if (HI_NULL == bootargs)
		{
			HI_ERR_LOADER("bootargs is null!");
			return HI_FAILURE;
		}
		
		if (HI_SUCCESS != GetDataBlockInfo(pstDBName, (const HI_CHAR *) bootargs, &stDBInfo))
		{
			HI_INFO_LOADER("no found %s=part_name,offset,size parameter from bootargs.\n", pstDBName);
			return HI_FAILURE;
		}

		*hFlash = HI_Flash_Open(HI_FLASH_TYPE_BUTT, stDBInfo.ac8PartionName, (HI_U64)0, (HI_U64)0);
		if (HI_INVALID_HANDLE == *hFlash)
		{
			HI_ERR_LOADER("open partition[%s] failed.\n", stDBInfo.ac8PartionName);
			return HI_FAILURE;
		}

		*pu32Offset = stDBInfo.u32Offset;
		*pu32Size = stDBInfo.u32Size;

		if (HI_SUCCESS != HI_Flash_GetInfo(*hFlash, &stFlashInfo))
		{
			return HI_FAILURE;
		}

		*pu32RegionSize = stFlashInfo.BlockSize;
	}
	else
	{
		*pu32Offset = 0;
		if (HI_SUCCESS != HI_Flash_GetInfo(*hFlash, &stFlashInfo))
		{
			return HI_FAILURE;
		}

		*pu32RegionSize = stFlashInfo.PartSize;
		*pu32Size = stFlashInfo.PartSize;
	}

	return HI_SUCCESS;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
