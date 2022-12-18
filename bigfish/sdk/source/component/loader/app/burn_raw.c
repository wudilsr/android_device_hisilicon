/*******************************************************************************
 *             Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: burn.c
 * Description:
 *              burn raw image implemention.
 * History:
 * Version   Date         Author     DefectNum    Description
 * 
 ******************************************************************************/
#include "loader_upgrade.h"
#include "upgrd_osd.h"
#include "upgrd_common.h"
#include "hi_flash.h"
#include "burn.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*
 * global variable import from burn.c
 */
extern FLASH_DATA_INFO_S *g_pstFlashDataInfo;
extern LOADER_OSD_CALLBACK g_pfnOSDCallback;

/*****************************************************************************
* Function:      LOADER_BURN_WriteData_raw
* Description:   update data to flash
* Data Accessed:
* Data Updated:
* Input:            
* Output:          
* Return: HI_SUCCESS
* Others:
*****************************************************************************/
HI_S32 LOADER_BURN_WriteData_raw(FLASH_DATA_INFO_S *pstFlashDataInfo, HI_U8 * pucSrcDataBuff, HI_U32 u32SrcDataLen, HI_VOID * private)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S64 s64Ret = HI_SUCCESS;
    HI_U8* p;
    HI_U32 u32len = 0;
    HI_U32 u32RemainLen = 0;
    HI_U32 u32DataBlockLen  = 0;
    HI_U32 u32FlashBlockLen = 0;
    HI_HANDLE hHandle = HI_INVALID_HANDLE;
    HI_U32 u32DataLen = 0;
    HI_U32 write_len = 0;
    HI_U32 u32AdjustValue = 0;
    HI_U8  *pucBuff;
    HI_BOOL bLastData = (HI_BOOL)((HI_U32)private);

    if (HI_NULL == pucSrcDataBuff || HI_NULL == pstFlashDataInfo)
    {
        return HI_UPGRD_ERR_PARA;
    }

    /*record  buffer  point*/
    u32len = 0;
    hHandle = pstFlashDataInfo->hFlashHandle;
    u32DataBlockLen  = pstFlashDataInfo->u32DataBlockSize;
    u32FlashBlockLen = pstFlashDataInfo->u32FlashBlockSize;

    if (HI_FALSE == pstFlashDataInfo->bErased)
    {
        s64Ret = HI_Flash_Erase64(hHandle, (HI_U64)0, pstFlashDataInfo->u64PartitionSize);
        if (0 > s64Ret)
        {
            HI_ERR_LOADER("Burn Erase flash error! s64Ret:0x%x\n", s64Ret);
            return HI_UPGRD_UPGRDPRO_WRFLASH;
        }

        pstFlashDataInfo->bErased = HI_TRUE;
    }

    pucBuff = (HI_U8*)malloc(u32DataBlockLen);
    if (NULL == pucBuff)
    {
        HI_ERR_LOADER("malloc error");
        return HI_UPGRD_ERR_MALLOC;
    }

    u32RemainLen = pstFlashDataInfo->u32BuffLen;
    p = pucSrcDataBuff;
    u32DataLen = u32SrcDataLen;

    /*把上次剩下的数据写入flash*/
    if (u32RemainLen != 0)
    {
        memcpy(pucBuff, pstFlashDataInfo->pu8Buff, u32RemainLen);

        if (u32DataLen > u32DataBlockLen - u32RemainLen)
        {
            memcpy(pucBuff + u32RemainLen, pucSrcDataBuff, u32DataBlockLen - u32RemainLen);
            u32DataLen -= u32DataBlockLen - u32RemainLen;
        }
        else
        {
            memcpy(pucBuff + u32RemainLen, pucSrcDataBuff, u32DataLen);
            memset(pucBuff + u32RemainLen + u32DataLen, 0xff, u32DataBlockLen - u32RemainLen - u32DataLen);
            u32DataLen = 0;
        }

        s32Ret = HI_Flash_Write(hHandle,
					pstFlashDataInfo->u64WriteOffset,
					pucBuff,
					u32DataBlockLen,
					pstFlashDataInfo->u32WriteFlags);

        if (0 >= s32Ret)
        {
            HI_ERR_LOADER("Write flash error!\n");
            free(pucBuff);
            return (HI_S32)HI_UPGRD_UPGRDPRO_WRFLASH;
        }

        IncCurWriteLen(u32DataBlockLen);
        pstFlashDataInfo->u64WriteOffset += u32FlashBlockLen;

        if (u32DataLen > 0)
        {
            p = pucSrcDataBuff + u32DataBlockLen - u32RemainLen;
        }
    }

    while (u32len < u32DataLen)
    {
        /*Insure Write len accuracy*/
        if ((u32DataLen - u32len) >= u32DataBlockLen)
        {
            write_len = u32DataBlockLen;
        }
        else
        {
            write_len = u32DataLen - u32len;

            /*为了做到块对齐,如果不是最后的数据,将不足一块的数据拷贝到缓冲区*/
            if (HI_FALSE == bLastData)
            {
                memcpy(pstFlashDataInfo->pu8Buff, p + u32len, write_len);
					pstFlashDataInfo->u32BuffLen = write_len;
					break;
            }
        }

        if (write_len < u32DataBlockLen)
        {
            memset(pucBuff, 0xff, u32DataBlockLen);
        }

        memcpy(pucBuff, (p + u32len), write_len);
        HI_DBG_LOADER("adjust after, data addrs :"
					"0x%x,data len :%d,"
					"adjust addrs : 0x%x,"
					" adjust offset : %d\n",
					(HI_U32)p + u32len,
					u32len,
					(HI_U32)pucBuff,
					u32AdjustValue);

        s32Ret = HI_Flash_Write(hHandle,
					pstFlashDataInfo->u64WriteOffset,
					pucBuff,
					u32DataBlockLen,
					pstFlashDataInfo->u32WriteFlags);

        if (0 >= s32Ret)
        {
            HI_ERR_LOADER("\n[ERROR]: Flash write fail!\n");
            free(pucBuff);
            pucBuff = NULL;
            return (HI_S32)HI_UPGRD_UPGRDPRO_WRFLASH;
        }
        else
        {
            HI_DBG_LOADER("UPGRD_FLASH_DO  write(TYPE %d :"
						"writeflag:%d)  offset:0x%016llx  bytes:0x%x\r\n",
						pstFlashDataInfo->enFlashType,
						pstFlashDataInfo->u32WriteFlags,
						pstFlashDataInfo->u64WriteOffset,
						write_len);
        }

        u32len += write_len;
        IncCurWriteLen(write_len);
        pstFlashDataInfo->u64WriteOffset += u32FlashBlockLen;

        if (g_pfnOSDCallback)
        {
            g_pfnOSDCallback(OSD_EVENT_TYPE_BURN, GetCurWriteLen(), GetTotalWriteLen());
        }
            
    }

    free(pucBuff);

    return HI_SUCCESS;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
