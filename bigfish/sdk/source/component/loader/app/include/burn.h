/*******************************************************************************
 *             Copyright 2013 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: burn.h
 * Description:
 *       deinition burn interface.
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 ******************************************************************************/
#ifndef __BURN_H__
#define __BURN_H__

#include "hi_type.h"
#include "hi_flash.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

/*
 * basic burn definition
 */
typedef struct tagFLASH_DATA_INFO_S
{
    HI_HANDLE         hFlashHandle;
    HI_U32              u32PartitionId;
    HI_U32              u64PartitionSize;
    HI_BOOL            bErased;
    HI_FLASH_TYPE_E     enFlashType;
    HI_U32              u32FlashBlockSize;
    HI_U32              u32DataBlockSize;
    HI_U32              u32WriteFlags;
    HI_U64              u64WriteOffset;
    HI_U32              u32PartitionOriCRC;
    HI_U32              u32PartitionCalCRC;
    HI_U8*              pu8Buff;
    HI_U32              u32BuffLen;
    HI_S32              (*LOADER_BURN_WriteData)(struct tagFLASH_DATA_INFO_S *pstFlashDataInfo, HI_U8 * pucDataBuff, HI_U32 u32DataLen, HI_VOID * private);
    HI_VOID             *private;
} FLASH_DATA_INFO_S;

/*
 * export public burn interface 
 */
HI_S32 LOADER_BURN_Init(LOADER_PARTITION_INFO_S * pstPartInfo, HI_U32 u32PartNum, LOADER_OSD_CALLBACK pfnOsdCallback);
HI_S32 LOADER_BURN_WriteData(LOADER_DATA_S *pstPartInfo, HI_U32 u32PartNum);
HI_S32 LOADER_BURN_DeInit(HI_VOID);

/*
 * internal helper functions
 */
HI_S32 GetIndexById(HI_U32 id, HI_U32 *pu32Index);
HI_U32 GetTotalWriteLen(HI_VOID);
HI_U32 GetCurWriteLen(HI_VOID);
HI_U32 IncCurWriteLen(HI_U32 len);


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __BURN_H__ */
