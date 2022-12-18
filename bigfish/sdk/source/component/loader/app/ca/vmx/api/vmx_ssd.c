/******************************************************************************
Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : vmx_ssd.c
Version       : Initial Draft
Author        : Hisilicon hisecurity team
Created       : 2014/09/23
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vmx_ssd.h"
#include "hi_flash.h"

static HI_HANDLE VMX_flash_open_addr(HI_FLASH_TYPE_E enFlashType, HI_U64 u64addr, HI_U64 u64Len, HI_U32 *block_size)
{
    HI_HANDLE hFlashHandle;
    HI_Flash_InterInfo_S stFlashInfo;
    HI_S32 ret = HI_SUCCESS;
    HI_U64 u64OpenSize;
    
    u64Len = (u64Len + 0x200000 -1)& (~(0x200000 -1) );//¿é¶ÔÆë
    hFlashHandle = HI_Flash_OpenByTypeAndAddr(enFlashType, u64addr, u64Len);
    if(HI_INVALID_HANDLE == hFlashHandle)
    {
    	HI_SIMPLEINFO_CA("HI_Flash_OpenByTypeAndAddr failed\n");
		return HI_INVALID_HANDLE;
    }
      
	ret = HI_Flash_GetInfo(hFlashHandle, &stFlashInfo);
	if(HI_SUCCESS != ret)
	{
		HI_SIMPLEINFO_CA("HI_Flash_GetInfo() error, result %x!\n",ret);
		(HI_VOID)HI_Flash_Close(hFlashHandle);
		return HI_INVALID_HANDLE;
	}
	(HI_VOID)HI_Flash_Close(hFlashHandle);

	*block_size = stFlashInfo.BlockSize;
	u64OpenSize = (HI_U64)stFlashInfo.TotalSize - u64addr;

    hFlashHandle = HI_Flash_OpenByTypeAndAddr(enFlashType, u64addr,u64OpenSize);
    if(HI_INVALID_HANDLE == hFlashHandle)
    {
    	HI_SIMPLEINFO_CA("HI_Flash_OpenByTypeAndAddr() failed!\n");
		return HI_INVALID_HANDLE;
    }
	
	return hFlashHandle;    
}
extern HI_VOID GenerateMagicNum(HI_VOID);

HI_S32 VMX_printBuffer(const HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{
    HI_U32 i = 0;
    
    if ( NULL != string )
    {
        HI_SIMPLEINFO_CA("%s\n", string);
    }

    for ( i = 0 ; i < u32Length; i++ )
    {
        if( (i % 16 == 0) && (i != 0)) HI_SIMPLEINFO_CA("\n");
        HI_SIMPLEINFO_CA("0x%02x ", pu8Input[i]);
    }
    HI_SIMPLEINFO_CA("\n");

    return HI_SUCCESS;
}

#define VMX_SSD_HEADER_LEN (16)
#define VMX_SSD_SIG_LEN (256)
HI_S32 VMX_Verify_Authenticate(HI_U8* pu8StartVirAddr, HI_U32 u32Addrlength, HI_U32 u32FlashStartAddr, HI_U32 u32FlashType)
{
	HI_S32 ret = HI_SUCCESS;
	unsigned char errorCode = 0;
	HI_U8 *tmp = NULL;
	HI_U32 image_offset = VMX_SSD_HEADER_LEN + VMX_SSD_SIG_LEN;
	HI_U32 sig_offset = VMX_SSD_HEADER_LEN;
	HI_U32 image_len = u32Addrlength - image_offset;

	if((NULL == pu8StartVirAddr) || (0 == u32Addrlength) || (0xFFFFFFFF == u32Addrlength))
	{
		HI_SIMPLEINFO_CA("VMX_Verify_Authenticate, invalid params!\n");
		return HI_FAILURE;
	}

	HI_SIMPLEINFO_CA("VMX_Verify_Authenticate: u32FlashStartAddr: 0x%x, u32Addrlength: 0x%x\n", u32FlashStartAddr, u32Addrlength);
	VMX_printBuffer("VMX_Verify_Authenticate, first 32 bytes:", pu8StartVirAddr, 32);

	tmp = (HI_U8 *)malloc(image_len);
	if(NULL == tmp)
	{
		HI_SIMPLEINFO_CA("VMX_Verify_Authenticate: malloc for tmp failed!\n");
		return HI_FAILURE;
	}

	ret = verifySignature(pu8StartVirAddr + sig_offset, 
							pu8StartVirAddr + image_offset, 
							tmp, 
							image_len, 
							image_len, 
							1, 
							&errorCode);
	if(1 == ret)
	{
		HI_SIMPLEINFO_CA("VMX_Verify_Authenticate: verifySignature() success! ret:0x%x, Continue ...\n", ret);
		free(tmp);
		return HI_SUCCESS;
	}
	else if((1 == errorCode) && (0 == ret))			/* Invalid signature, maybe */
	{
		HI_SIMPLEINFO_CA("VMX_Verify_Authenticate: verifySignature() failed, do not start the application, reset! errorCode: 0x%x, ret: 0x%x, Resetting ...\n", errorCode, ret);
		free(tmp);
		system("reboot");
	}
	else if((2 == errorCode) && (0 == ret)) 		/* Src is re-encrypted inside BL library, burn to flash */
	{
		HI_SIMPLEINFO_CA("VMX_Verify_Authenticate: verifySignature() success! burn src to flash, errorCode:0x%x\n", errorCode);

		HI_U32 BlockSize = 0;
		HI_U32 write_length = 0;
		HI_HANDLE hFlash = HI_INVALID_HANDLE;

		hFlash = VMX_flash_open_addr(HI_FLASH_TYPE_NAND_0, u32FlashStartAddr, u32Addrlength, &BlockSize);
		if(HI_INVALID_HANDLE == hFlash)
		{
			HI_SIMPLEINFO_CA("VMX_flash_open_addr failed, u32FlashStartAddr:0x%x, u32Addrlength:0x%x\n", u32FlashStartAddr, u32Addrlength);
			return HI_FAILURE;
		}

		if(0 == (u32Addrlength % BlockSize))
		{
		    write_length = u32Addrlength;
		}
		else
		{
		    write_length = (u32Addrlength + BlockSize - 1) & (~(BlockSize -1));
		}

	    HI_SIMPLEINFO_CA("VMX_Verify_Authenticate: BlockSize: 0x%x, write addr: 0x%x, write_length:0x%x\n", BlockSize, u32FlashStartAddr, write_length);

		ret = HI_Flash_Write(hFlash, 0, pu8StartVirAddr, write_length, HI_FLASH_RW_FLAG_ERASE_FIRST);
		if(write_length != ret)
		{
			HI_SIMPLEINFO_CA("VMX_Verify_Authenticate: Burn image to flash failed! ret:0x%x, Resetting ...\n", ret);
			free(tmp);
			HI_Flash_Close(hFlash);
			system("reboot");
		}
		else
		{
			HI_SIMPLEINFO_CA("\nVMX_Verify_Authenticate: Burn image to flash success, ret:0x%x! Resetting ...\n", ret);
			HI_Flash_Close(hFlash);
			//system("reboot");
		}
	}
	else
	{
		//not supported;
	}

	if(NULL != tmp)
	{
		free(tmp);
	}
	return HI_SUCCESS;
}

/*-----------------------------------END----------------------------------*/

