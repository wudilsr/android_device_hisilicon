/******************************************************************************
Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : vmx_auth.c
Version       : Initial Draft
Author        : Hisilicon hisecurity team
Created       : 2014/09/24
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/
#include "vmx_ssd.h"

extern int VMX_printBuffer(const char *string, unsigned char *pu8Input, int u32Length);

int verifySignature( unsigned char* signature, 
                     unsigned char* src, 
                     unsigned char* tmp, 
                     unsigned int len, 
                     unsigned int maxLen, 
                     unsigned char mode, 
                     unsigned char *errorCode )
{
	int ret = 0;
	unsigned char au8MagicNumber[8] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};

	VMX_printBuffer("verifySignature.signature first 32 bytes:", signature, 32);
	VMX_printBuffer("verifySignature.src first 32 bytes:", src, 32);

	ret = memcmp(au8MagicNumber, signature, 8);
	if(0 != ret)
	{
		*errorCode = 1;	//means no valid signature found - reboot 
		return 0;		//indicates do not start the application
	}

	*errorCode = 2;		//means store src part to flash and reboot after it 
	return 0;			//indicates do not start the application 
}

