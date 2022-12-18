/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : vmx_auth.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2014-09-19
Last Modified :
Description   :  
Function List :
History       :
******************************************************************************/

/*
	return value:
	    0: indicates do not start this application
	    1: indicates the application can be started
*/
int verifySignature( unsigned char* signature, 
					unsigned char	* src, 
					unsigned char* tmp, 
					unsigned int len, 
					unsigned int maxLen, 
					unsigned char mode, 
					unsigned char *errorCode )
{
	*errorCode = 0;

	return 1;
}
