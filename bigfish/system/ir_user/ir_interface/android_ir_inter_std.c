/***********************************************************************************
 * just reference sdk/source/msp/api/ir/unf_ir_std.c, 2013,07,15
 ***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>
#include <semaphore.h>
#include <utils/Log.h>

#include "android_ir_inter.h"
//#include "android_ir_drv.h"
#include "hi_drv_ir.h"
#include "hi_module.h"
#include "drv_ir_ioctl.h"
#include "hi_unf_ir.h"

static int g_IrDevFd = -1;
extern unsigned int read_timeout ;
#define  UMAP_DEVNAME_IR "/dev/hi_ir"

#define  SUCCESS 0
#define  FAILURE -1

static HI_UNF_IR_PROTOCOL_E g_IrProtocol = -1;
static char g_szLastProtocolName[PROTOCOL_NAME_SZ];

#define  IR_LOG(fmt ...) printf(fmt)

#define CHECK_IR_OPEN()\
	do{\
		if (g_IrDevFd < 0)\
		{\
			IR_LOG("IR is not open.\n");\
			return FAILURE;\
		}\
	}while(0)

/*************************************************************
Function:       IR_Init
Description:    open ir device,and do the basical initialization
Calls:
Data Accessed:
Data Updated:   NA
Input:
Output:
Return:         SUCCESS
FAILURE
Others:         NA
 *************************************************************/
signed int IR_Init(void)
{
	/* if had opened will return success*/
	if (g_IrDevFd > 0)
	{
		return SUCCESS;
	}
	g_IrDevFd = open(UMAP_DEVNAME_IR, O_RDWR, 0);
	if (g_IrDevFd < 0)
	{
		IR_LOG("open IR err.%s\n",UMAP_DEVNAME_IR);

		return FAILURE;
	}
	HI_S32 Ret = ioctl(g_IrDevFd, CMD_IR_SET_BLOCKTIME, read_timeout);
	if(Ret != SUCCESS)
	{
		return FAILURE;
	}
	return SUCCESS;
}

/*************************************************************
Function:       IR_Deinit
Description:    close ir device
Calls:
Data Accessed:
Data Updated:   NA
Input:
Output:
Return:         SUCCESS
FAILURE
Others:         NA
 *************************************************************/
signed int IR_DeInit(void)
{
	signed int Ret;

	if (g_IrDevFd < 0)
	{
		return SUCCESS;
	}

	Ret = close(g_IrDevFd);

	if(SUCCESS != Ret)
	{
		IR_LOG("Close IR err.\n");
		return FAILURE;
	}
	g_IrDevFd = -1;
	return SUCCESS;
}

/*************************************************************
Function:       IR_Enable
Description:    Enable ir device
Calls:
Data Accessed:
Data Updated:   NA
Input:
Output:
Return:         SUCCESS
FAILURE
Others:         NA
 *************************************************************/
signed int IR_Enable(BOOL bEnable)
{
	signed int  Ret;

	if ((bEnable != TRUE)
			&&(bEnable != FALSE))
	{
		IR_LOG("para bEnable is invalid,please set 1,or 0,\n");
		return FAILURE;
	}
	CHECK_IR_OPEN();



	Ret = ioctl(g_IrDevFd, CMD_IR_SET_ENABLE, bEnable);

	if (Ret != SUCCESS)
	{
		return Ret;
	}

	return SUCCESS;
}

/*************************************************************
Function:       IR_GetValueWithProtocol
Description:    get the value and status of key
Calls:
Data Accessed:
Data Updated:   NA
Input:          u32TimeOut: overtime value with unit of ms : 0 means no block while 0xFFFFFFFF means block forever
name_sz, buffer size of protocol_name.
Output:         pu32PressStatus:    status of the key
0:  means press or hold
1:  means release
pu32KeyId:          value of the key

protocol_name: protocol name defined by customer.

Return:         SUCCESS
FAILURE
Others:         NA
 *************************************************************/
unsigned int  IR_GetValueWithProtocol (KEY_STATUS_E *penPressStatus, unsigned long long *pu64KeyId,
		char *pszProtocolName, signed int  s32NameSize, unsigned int u32TimeoutMs)
{
    HI_S32 Ret;
    IR_KEY_S Irkey;

	if (!penPressStatus)
	{
		IR_LOG("para penPressStatus is null.\n");
		return FAILURE;
	}

	if (!pu64KeyId)
	{
		IR_LOG("para pu64KeyId is null.\n");
		return FAILURE;
	}
    if (pszProtocolName && (s32NameSize < PROTOCOL_NAME_SZ))
	{
		IR_LOG("Invalid protocol buffer!\n");
		return FAILURE;
	}
	CHECK_IR_OPEN();

    Ret = read(g_IrDevFd, &Irkey, sizeof(IR_KEY_S));
    if (Ret == sizeof(IR_KEY_S))
    {
        g_IrProtocol = Irkey.IrProtocol;
		*penPressStatus = Irkey.IrKeyState;
		*pu64KeyId = Irkey.IrKeyDataH & 0xFFFF;
		*pu64KeyId = *pu64KeyId << 32;
		*pu64KeyId = *pu64KeyId | Irkey.IrKeyDataL;
    }
    else
	{
		return FAILURE;
	}

	return SUCCESS;
}

/*************************************************************
Function:       IR_SetFetchMode
Description:    set key fetch mode or symbol mode.
Calls:
Data Accessed:
Data Updated:   NA
Input:          mode: 0-> key mode. 1-> raw symbol mode.
Output:
Return:         SUCCESS on success.
others fail.
Others:         NA
 *************************************************************/
signed int IR_SetFetchMode(signed int s32Mode)
{
#if 0
	signed int Ret;

	if (s32Mode != 0 && s32Mode != 1)
	{
		IR_LOG("only 0 or 1 is allowed!\n");
		return FAILURE;
	}

	CHECK_IR_OPEN();

	if ((Ret = ioctl(g_IrDevFd, CMD_IR_SET_FETCH_METHOD, s32Mode)) != SUCCESS)
	{
		IR_LOG("Fail to set symbol mode!\n");
		return Ret;
	}
#endif
	return SUCCESS;
}


/*************************************************************
Function:       IR_GetSymbol
Description:    get one raw symbols from ir module.
Calls:
Data Accessed:
Data Updated:   NA
Input:          u32TimeoutMs: npars of symbols including pu64First and pu64Second
Output:         pu64lower, pu64upper.
Return:         SUCCESS on success.
others fail.
Others:         NA
 *************************************************************/
signed int IR_GetSymbol(unsigned long long *pu64First, unsigned long long* pu64Second, unsigned int u32TimeoutMs)
{
#if 0
	signed int Ret;
	struct key_attr key;

	if (!pu64First || !pu64Second)
	{
		IR_LOG("Invalid parameters!\n");
		return FAILURE;
	}

	CHECK_IR_OPEN();

	Ret = ioctl(g_IrDevFd, CMD_IR_SET_BLOCKTIME, u32TimeoutMs);
	if(Ret != SUCCESS)
	{
		return Ret;
	}

	Ret = read(g_IrDevFd, &key, sizeof(struct key_attr));
	if (Ret != (signed int)sizeof(struct key_attr))
	{
		return FAILURE;
	}

	*pu64First = key.lower;
	*pu64Second = key.upper;
#endif
	return SUCCESS;
}


/*************************************************************
Function:       HI_UNF_IR_EnableKeyUp
Description:    config whether report the state of key release
Calls:
Data Accessed:
Data Updated:   NA
Input:
Output:
Return:         SUCCESS
FAILURE
Others:         NA
 *************************************************************/
signed int IR_EnableKeyUp(BOOL bEnable)
{
	signed int Ret;

	if ((bEnable != TRUE)
			&&(bEnable != FALSE))
	{
		IR_LOG("para bEnable is invalid.\n");
		return FAILURE;
	}

	CHECK_IR_OPEN();


	Ret = ioctl(g_IrDevFd, CMD_IR_ENABLE_KEYUP, bEnable);
	if (Ret != SUCCESS)
	{
		return Ret;
	}

	return SUCCESS;
}


/*************************************************************
Function:       IR_EnableRepKey
Description:    config whether report repeat key
Calls:
Data Accessed:
Data Updated:   NA
Input:
Output:
Return:         SUCCESS
FAILURE
Others:         NA
 *************************************************************/
signed int IR_EnableRepKey(BOOL bEnable)
{
	signed int Ret;

	if ((bEnable != TRUE)
			&&(bEnable != FALSE))
	{
		IR_LOG("para bEnable is invalid.\n");
		return FAILURE;
	}
	CHECK_IR_OPEN();


	Ret = ioctl(g_IrDevFd, CMD_IR_ENABLE_REPKEY, bEnable);
	if (Ret != SUCCESS)
	{
		return Ret;
	}

	return SUCCESS;
}



/*************************************************************
Function:       IR_SetRepKeyTimeoutAttr
Description:    Set the reporting interval when you keep pressing button.
Calls:
Data Accessed:
Data Updated:   NA
Input:          u32TimeoutMs  The minimum interval to report repeat key
Output:
Return:         SUCCESS
FAILURE
Others:         NA
 *************************************************************/
signed int IR_SetRepKeyTimeoutAttr(unsigned int u32TimeoutMs)
{
	signed int Ret;

	CHECK_IR_OPEN();

	/* Remove 108 minimal time limit.
	 * For some user require every key press event should
	 * be reported.
	 */
	if (u32TimeoutMs == 0)
	{
		IR_LOG("prompt:u32TimeoutMs == 0, set to 108\n");
		u32TimeoutMs = 108;
	}

	if (u32TimeoutMs > 65536)
	{
		IR_LOG("prompt:u32TimeoutMs > 65536, set to 65536\n");
		u32TimeoutMs = 65536;
	}

	Ret = ioctl(g_IrDevFd, CMD_IR_SET_REPKEY_TIMEOUT, u32TimeoutMs);
	if (Ret != SUCCESS)
	{
		return Ret;
	}

	return SUCCESS;
}
/*************************************************************
Function:       HI_UNF_IR_SetCodeType
Description:    reserved interface.
Calls:
Data Accessed:
Data Updated:   NA
Input:          enIRCode
Output:
Return:         HI_SUCCESS

Others:         NA
*************************************************************/

signed int IR_SetCodeType(signed int enIRCode)
{
    signed int Ret = 0;

    if (enIRCode >= HI_UNF_IR_CODE_BUTT)
    {
        IR_LOG("para enIRCode is invalid.\n");
        return Ret;
    }

    CHECK_IR_OPEN();

    Ret = ioctl(g_IrDevFd, CMD_IR_SET_FORMAT, enIRCode);
    if (Ret != SUCCESS)
    {
        IR_LOG("SET_FORMAT error.\n");
        return Ret;
    }

    return SUCCESS;
}

/*************************************************************
Function:       IR_Reset
Description:    Reset ir device
Calls:
Data Accessed:
Data Updated:   NA
Input:
Output:
Return:         SUCCESS
FAILURE
Others:         NA
 *************************************************************/
signed int IR_Reset(void)
{
	signed int Ret;

	CHECK_IR_OPEN();

	Ret = ioctl(g_IrDevFd, CMD_IR_RESET);
	if (Ret != SUCCESS)
	{
		return Ret;
	}

	return SUCCESS;
}


/*************************************************************
Function:       IR_EnableProtocol
Description:    enable a infrared code specified by @prot_name
Calls:
Data Accessed:
Data Updated:   NA
Input:          pszProtocolName: infrared code name.
Output:
Return:         SUCCESS
others on fail
Others:         NA
 *************************************************************/
signed int IR_EnableProtocol(char* pszProtocolName)
{
   return FAILURE;

}

/*************************************************************
Function:       IR_DisableProtocol
Description:    disable a infrared code specified by @prot_name
Calls:
Data Accessed:
Data Updated:   NA
Input:          pszProtocolName: infrared code name.
Output:
Return:         SUCCESS
others on fail
Others:         NA
 *************************************************************/
signed int IR_DisableProtocol(char * pszProtocolName)
{
   return FAILURE;

}

/*************************************************************
Function:        IR_GetProtocolEnabled
Description:    get the enable status of a infrared code specified by @prot_name
Calls:
Data Accessed:
Data Updated:   NA
Input:          pszProtocolName: infrared code name.
Output:         pbEnabled: 1 means protocol effative, can received keys.
Return:         SUCCESS
others on fail
Others:         NA
 *************************************************************/
signed int  IR_GetProtocolEnabled(char* pszProtocolName, BOOL *pbEnabled)

{
    return FAILURE;
}
