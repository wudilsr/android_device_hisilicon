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
	*errorCode = 0;

	VMX_printBuffer("verifySignature.signature first 32 bytes:", signature, 32);

	VMX_printBuffer("verifySignature.src first 32 bytes:", src, 32);
	
	return 1;
}

