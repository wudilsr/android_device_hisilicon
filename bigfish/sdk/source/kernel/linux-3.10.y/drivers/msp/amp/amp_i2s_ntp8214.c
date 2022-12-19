/*********************************************************************

Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

**********************************************************************
File Name     :	amp_i2s_NTP8214.h
Version	     :	Initial	Draft
Author	     :	l00191026
Created	     :	2014/2/28
Last Modified:
Description   :	NTP8214 Driver
Function List :
History	     :
* Version     Date	   Author     DefectNum	      Description
		   2014/6/25   l00191026      NULL            Update driver.
*********************************************************************/

/******************************* Include Files *******************************/

/* Sys headers */
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/vmalloc.h>
#include <linux/interrupt.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <mach/hardware.h>

/* Unf headers */
#include "hi_error_mpi.h"
#include "hi_drv_mem.h"
#include "hi_module.h"

/* Drv headers */
#include "hi_drv_amp.h"
#include "drv_amp_ext.h"
#include "amp_i2s.h"
//========== Board Changed! ================== 		
#include "hi_board.h"
//================= End ===================


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define ENDTBL_FLAG 	(0xff)
#define AMP_DEBUG 		(0)
#define MAX_AMP_REG_LEN (20)
#define NTP8214_MAX_VOL (0xff)
#define NTP8214_MIN_VOL (0x00) //Mute
#define NTP8214_INIT_INTERVAL (10) //Delay 65ms

static AMP_GLOBAL_PARAM_S* pstNTP8214Drv = HI_NULL;

typedef struct
{
    HI_U8 bAddr;
    HI_U8 bLength;
    HI_U8 bArray[MAX_AMP_REG_LEN];
} NTP8214_REGMAP;

static NTP8214_REGMAP NTP8214_DefautTbl[] = 
{
    // Address  DataLength   DataN       DataN+1...
    // I2C Configuration file for NTP8212
	{0x00, 1, {0x00}},
	{0x01, 1, {0x00}},
	{0x02, 1, {0x00}},
	{0x03, 1, {0x4e}},
	{0x04, 1, {0x00}},
	{0x05, 1, {0x00}},
	{0x06, 1, {0x4e}},
	{0x0e, 1, {0x00}},
	{0x0f, 1, {0x00}},
	{0x10, 1, {0x00}},
	{0x11, 1, {0x00}},
	{0x12, 1, {0x00}},
	{0x13, 1, {0x00}},
	{0x14, 1, {0x00}},
	{0x15, 1, {0x00}},
	{0x19, 1, {0x00}},
	{0x20, 1, {0x00}},
	{0x21, 1, {0x01}},
	{0x22, 1, {0x00}},
	{0x23, 1, {0x01}},
	{0x2a, 1, {0x6a}},
	{0x2b, 1, {0x01}},
	{0x26, 1, {0x00}},
	{0x27, 1, {0x41}},
	{0x16, 1, {0x00}},
	{0x17, 1, {0x9f}},
	{0x18, 1, {0x9f}},
	{0x3c, 1, {0x4a}},
	{0x41, 1, {0x12}},
	{0x67, 1, {0x00}},
	{0x62, 1, {0x00}},
	{0x63, 1, {0x05}},
	{0x64, 1, {0x55}},
	{0x0c, 1, {0x00}},//0xff=0db,  0x00=-128db
	{ENDTBL_FLAG ,0x01,{0x00}},
};

static HI_S32 AMPWriteReg(HI_U8 u1Addr, HI_U8 *pu1Buf, HI_U16 u2ByteCnt)
{
    HI_S32 s32Ret = 0;

	if (pstNTP8214Drv->pI2CFunc  == HI_NULL)
	{
		HI_ERR_AMP("I2C Function Null \n");
		return HI_FAILURE;
	}
	
	s32Ret = pstNTP8214Drv->pI2CFunc->pfnI2cWrite(pstNTP8214Drv->u32I2CNum,
			 pstNTP8214Drv->u8DeviceAddr, u1Addr, 1, pu1Buf, u2ByteCnt);
    if (s32Ret != HI_SUCCESS)
    {
    	
		HI_ERR_AMP("NTP8214 i2c write error :I2cNum:0x%x, I2cDevAddr:0x%x, "
				   "u1Addr:0x%x, addlen:0x%x, pu1Buf:0x%x, u2ByteCnt:0x%x\n",
				   pstNTP8214Drv->u32I2CNum, pstNTP8214Drv->u8DeviceAddr,
				   u1Addr, 1, pu1Buf[0], u2ByteCnt);
    }
    return s32Ret;
}

static HI_S32 AMPReadReg(HI_U8 u1Addr, HI_U8 *pu1Buf, HI_U16 u2ByteCnt)
{
    HI_S32 s32Ret = 0;

	if (pstNTP8214Drv->pI2CFunc == HI_NULL)
	{
		HI_ERR_AMP("I2C Function Null \n");
		return HI_FAILURE;
	}

	s32Ret = pstNTP8214Drv->pI2CFunc->pfnI2cRead(pstNTP8214Drv->u32I2CNum,
			 pstNTP8214Drv->u8DeviceAddr, u1Addr, 1, pu1Buf, u2ByteCnt);
    if (s32Ret != HI_SUCCESS)
    {
        //HI_ERR_AMP("5711read fail :%d!\n", s32Ret );
    }
    return s32Ret;
}

static HI_VOID AMPReset(HI_BOOL bReset)
{
	if (pstNTP8214Drv == HI_NULL)
	{
		HI_ERR_AMP("NTP8214 no Init! \n");
		return;
	}

	if (pstNTP8214Drv->pGpioFunc== HI_NULL)
	{
		HI_ERR_AMP("GPIO Function Null \n");
		return;
	}	
	
	if (pstNTP8214Drv->pGpioFunc->pfnGpioDirSetBit)
	{
		pstNTP8214Drv->pGpioFunc->pfnGpioDirSetBit(pstNTP8214Drv->u32ResetGPIONum,
				pstNTP8214Drv->u32GPIOOutputPolarity); //Output Mode
	}
	
	msleep(1);
	
	if (pstNTP8214Drv->pGpioFunc->pfnGpioWriteBit)
	{ 
		if (bReset)
        {        	
            pstNTP8214Drv->pGpioFunc->pfnGpioWriteBit(pstNTP8214Drv->u32ResetGPIONum, 
													   pstNTP8214Drv->u32ResetPolarity);
        }
		else
		{
			pstNTP8214Drv->pGpioFunc->pfnGpioWriteBit(pstNTP8214Drv->u32ResetGPIONum, 
													   !(pstNTP8214Drv->u32ResetPolarity));
		}
	}		
	
	msleep(NTP8214_INIT_INTERVAL);

	return;
}

#if 1
static HI_VOID AMPHWMute(HI_BOOL bMute)
{
	if (pstNTP8214Drv == HI_NULL)
	{
		HI_ERR_AMP("NTP8214 no Init! \n");
		return;
	}

	if (pstNTP8214Drv->pGpioFunc== HI_NULL)
	{
		HI_ERR_AMP("GPIO Function Null \n");
		return;
	}	
	if (pstNTP8214Drv->pGpioFunc->pfnGpioDirSetBit)
	{
		pstNTP8214Drv->pGpioFunc->pfnGpioDirSetBit(pstNTP8214Drv->u32HWMuteGPIONum, 
									  pstNTP8214Drv->u32GPIOOutputPolarity); //Output Mode
	}
	
	msleep(1);
	
	if (pstNTP8214Drv->pGpioFunc->pfnGpioWriteBit)
	{ 
		if (bMute)
        {        	
            pstNTP8214Drv->pGpioFunc->pfnGpioWriteBit(pstNTP8214Drv->u32HWMuteGPIONum, 
													   pstNTP8214Drv->u32HWMutePolarity);
        }
		else
		{
			pstNTP8214Drv->pGpioFunc->pfnGpioWriteBit(pstNTP8214Drv->u32HWMuteGPIONum, 
													   !(pstNTP8214Drv->u32HWMutePolarity));
		}
	}		
	
	return;
}
#endif

/*Ref from Skyworth*/
static HI_S32 AMP_Init(AMP_GLOBAL_PARAM_S* pstAmpDrv)
{
	HI_S32 			s32Ret = 0;
	HI_U8 			u8Index, u8Addr, u8Length, u8CountLoop;
	HI_U8 			u8Array[MAX_AMP_REG_LEN];
	NTP8214_REGMAP 	*pstNTP8214InitTbl;

	//Set NTP8214 Software ops and Hardware setting
	if (pstAmpDrv == HI_NULL)
	{
		HI_ERR_AMP("Cannot get Any Setting for NTP8214! \n");
		return HI_FAILURE;
	}
	else
	{
		pstNTP8214Drv 		= pstAmpDrv;
	}
	
	pstNTP8214InitTbl 	= NTP8214_DefautTbl;

    AMPHWMute(HI_FALSE);

	msleep(10);
	
	//Release Reset AMP
	AMPReset(HI_FALSE);		

	for(u8Index = 0; ; u8Index ++)
	{
		u8Addr = pstNTP8214InitTbl[u8Index].bAddr;
		if(u8Addr == ENDTBL_FLAG)
		{
			break;
		}

		u8Length = pstNTP8214InitTbl[u8Index].bLength;
		for(u8CountLoop = 0; u8CountLoop < u8Length; u8CountLoop ++)
		{		
			u8Array[u8CountLoop] = *(pstNTP8214InitTbl[u8Index].bArray + u8CountLoop);
		}
		
		s32Ret = AMPWriteReg(u8Addr, u8Array, u8Length);
		if(s32Ret != HI_SUCCESS)
		{
		//	HI_ERR_AMP("NTP8214Init Fail \n");
		}

		//0x1B:Oscillator Trim, 0x46:DRC Control, 0x50:EQ Control, 0xF9:I2C Device Addr
		if((u8Addr == 0x1B) || (u8Addr == 0x46) || (u8Addr == 0x50) || (u8Addr == 0xF9))
		{	
			msleep(1);
		}

#if AMP_DEBUG
		HI_U8 readArray[MAX_AMP_REG_LEN]	=	{0};
		s32Ret = AMPReadReg(u8Addr, readArray, u8Length);
		printk("addr:0x%x, length:0x%x, ",	u8Addr,	u8Length);
		for(u8CountLoop = 0;	u8CountLoop < u8Length;	u8CountLoop ++)
		{
			printk("0x%x,",	readArray[u8CountLoop]);
		}	
		printk("\n");
#endif

	}

	return HI_SUCCESS; 
}

static HI_VOID AMP_DeInit(HI_VOID)
{
	//Reset AMP
	AMPReset(HI_TRUE);	

	pstNTP8214Drv = HI_NULL;
	
    return;
}

static HI_S32 AMP_SetMute(HI_BOOL bMute)
{
	HI_S32 s32Ret;
	HI_U8  u8Gain[1]= {0};

	if (bMute)
	{
		u8Gain[0] = NTP8214_MIN_VOL;
		s32Ret = AMPWriteReg(0x0c, u8Gain, 1);
	}
	else
	{
		u8Gain[0] = NTP8214_MAX_VOL;
		s32Ret = AMPWriteReg(0x0c, u8Gain, 1);
	}
	return s32Ret;
}

static HI_S32 AMP_GetMute(HI_BOOL* pbMute)
{
	HI_S32 s32Ret;
	HI_U8  u8Gain = 0;
	
	s32Ret = AMPReadReg(0x0c, &u8Gain, 1);
	if (u8Gain == NTP8214_MIN_VOL)
	{
		*pbMute = HI_TRUE;
	}
	else
	{
		*pbMute = HI_FALSE;
	}
    return s32Ret; 
}

static HI_S32 AMP_SetSubWooferVol(HI_U32 u32Volume)
{
    return HI_SUCCESS; 
}

static HI_S32 AMP_GetSubWooferVol(HI_U32* pu32Volume)
{
    return HI_SUCCESS; 
}

static HI_S32 AMP_WriteReg(HI_U32 u32RegAddr, HI_U32 u32ByteSize, HI_U8* pu8Value)
{
    HI_S32 Ret;
	HI_U8  RegArray[MAX_AMP_REG_LEN];

	if (u32ByteSize > MAX_AMP_REG_LEN)
	{
		HI_ERR_AMP("NTP8214 reg length MAX is 20\n");
		u32ByteSize = MAX_AMP_REG_LEN;
	}

    Ret = copy_from_user(RegArray, pu8Value, u32ByteSize);
	if(Ret != HI_SUCCESS)
	{
		HI_ERR_AMP("NTP8214 copy_from_user Fail \n");
	}

	Ret = AMPWriteReg(u32RegAddr, RegArray, u32ByteSize);
    if(Ret != HI_SUCCESS)
	{
		HI_ERR_AMP("NTP8214 write I2C Fail \n");
	}
    
    return HI_SUCCESS; 
}

static HI_S32 AMP_ReadReg(HI_U32 u32RegAddr, HI_U32 u32ByteSize, HI_U8* pu8Value)
{
    HI_S32 Ret;
	HI_U8  RegArray[MAX_AMP_REG_LEN];

	if (u32ByteSize > MAX_AMP_REG_LEN)
	{
		HI_ERR_AMP("NTP8214 reg length MAX is 20\n");
		u32ByteSize = MAX_AMP_REG_LEN;
	}
	
	Ret = AMPReadReg(u32RegAddr, RegArray, u32ByteSize);
    if(Ret != HI_SUCCESS)
	{
		HI_ERR_AMP("NTP8214 Read I2C Fail \n");
	}

    Ret = copy_to_user(pu8Value, RegArray, u32ByteSize);
	if(Ret != HI_SUCCESS)
	{
		HI_ERR_AMP("NTP8214 copy_to_user Fail \n");
	}

    return HI_SUCCESS; 
}

static HI_VOID AMP_Proc(struct seq_file* p)
{
	HI_U8 			u8Index, u8Addr, u8Length, u8CountLoop;
	HI_U8 			u8Array[MAX_AMP_REG_LEN];
	NTP8214_REGMAP 	*pstNTP8214InitTbl;

	PROC_PRINT(p, "AMP Modul:        NTP8214\n");
	PROC_PRINT(p, "I2C Num:          %d\n" ,  pstNTP8214Drv->u32I2CNum);
	PROC_PRINT(p, "I2C Addr:         0x%x\n", pstNTP8214Drv->u8DeviceAddr);	
	PROC_PRINT(p, "Mute  GPIO Group: %d\n", pstNTP8214Drv->u32HWMuteGPIONum/8);
	PROC_PRINT(p, "Mute  GPIO Bit:   %d\n",	pstNTP8214Drv->u32HWMuteGPIONum%8);
	PROC_PRINT(p, "Mute  Polarity:   %d\n",	pstNTP8214Drv->u32HWMutePolarity);																	
	
	PROC_PRINT(p, "Reset GPIO Group: %d\n", pstNTP8214Drv->u32ResetGPIONum/8);
	PROC_PRINT(p, "Reset GPIO Bit:   %d\n", pstNTP8214Drv->u32ResetGPIONum%8);
	PROC_PRINT(p, "Reset Polarity:   %d\n", pstNTP8214Drv->u32ResetPolarity);

	pstNTP8214InitTbl 	= NTP8214_DefautTbl;

	PROC_PRINT(p,"\n--------------------- NTP8214 REGMAP -------------------------------------------------");
	for(u8Index = 0; ; u8Index ++)
	{
		u8Addr = pstNTP8214InitTbl[u8Index].bAddr;
		if(u8Addr == ENDTBL_FLAG)
		{
			break;
		}
		u8Length = pstNTP8214InitTbl[u8Index].bLength;
		PROC_PRINT(p, "\nAddr[0x%x] Len[%d]: ",u8Addr,u8Length);
		memset(u8Array,0,MAX_AMP_REG_LEN);	
		AMPReadReg(u8Addr, u8Array, u8Length);
		
		for(u8CountLoop = 0; u8CountLoop < u8Length; u8CountLoop ++)
		{
			PROC_PRINT(p, "0x%x ", u8Array[u8CountLoop]);
		}	
	}
	PROC_PRINT(p,"\n--------------------- END NTP8214 REGMAP -------------------------------------------------\n");
	
}

AMP_DRV_FUNC_S stNTP8214Func =
{
	.pfnAmpProc = AMP_Proc,
	.pfnAmpReadReg = AMP_ReadReg,
	.pfnAmpWriteReg = AMP_WriteReg,
	.pfnAmpGetSubWooferVol = AMP_GetSubWooferVol,
	.pfnAmpSetSubWooferVol = AMP_SetSubWooferVol,
	.pfnAmpGetMute = AMP_GetMute,
	.pfnAmpSetMute = AMP_SetMute,
	.pfnAmpDeinit = AMP_DeInit,
	.pfnAmpInit = AMP_Init,
};

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

