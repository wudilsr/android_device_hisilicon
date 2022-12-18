/*********************************************************************

Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

**********************************************************************
File Name     :	amp_i2s_tas5711.h
Version	     :	Initial	Draft
Author	     :	l00191026
Created	     :	2014/2/28
Last Modified:
Description   :	TAS5711 Driver
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
#define TAS5711_MAX_VOL (0x05)
#define TAS5711_MIN_VOL (0xff) //Mute
#define TAS5711_INIT_INTERVAL (65) //Delay 65ms

static AMP_GLOBAL_PARAM_S* pstTas5711Drv = HI_NULL;

typedef struct
{
    HI_U8 bAddr;
    HI_U8 bLength;
    HI_U8 bArray[MAX_AMP_REG_LEN];
}TAS5711_REGMAP;

static TAS5711_REGMAP Tas5711_DefautTbl[] = //Skyworth name: DrvTas5711InitTbl1_8K10_U1
{
	{0x1B,1,{0x00}},
	{0x06,1,{0x00}},
	{0x0A,1,{0xff}},
	{0x09,1,{0x29}},
	{0x08,1,{0x29}},
	{0x14,1,{0x54}},
	{0x13,1,{0xAC}},
	{0x12,1,{0x54}},
	{0x11,1,{0xAC}},
	{0x0E,1,{0xD1}},
	{0x1A,1,{0x95}},
	{0x20,4,{0x00,0x10,0x77,0x72}},
	{0x21,4,{0x00,0x00,0x42,0x03}},
	{0x10,1,{0x02}},
	{0x0B,1,{0x00}},
	{0x10,1,{0x02}},
	{0x1C,1,{0x02}},
	{0x19,1,{0x30}},
	{0x25,4,{0x01,0x01,0x32,0x45}},
	{0x50,4,{0x00,0x00,0x00,0x00}},

	{0x29,0x14,{0x00,0x7E,0xF0,0x1F,0x0F,0x02,0x1F,0xC2,0x00,0x7E,0xF0,0x1F,0x00,0xFD,0xDD,0xFD,0x0F,0x82,0x1D,0x80}},
	{0x2A,0x14,{0x00,0x7E,0xF0,0x1F,0x0F,0x02,0x1F,0xC2,0x00,0x7E,0xF0,0x1F,0x00,0xFD,0xDD,0xFD,0x0F,0x82,0x1D,0x80}},
	{0x2B,0x14,{0x00,0x7F,0xB3,0x2D,0x0F,0x05,0xB6,0x4E,0x00,0x7A,0xC7,0xF5,0x00,0xFA,0x49,0xB2,0x0F,0x85,0x84,0xDE}},
	{0x2C,0x14,{0x00,0x7F,0xE6,0xEE,0x0F,0x04,0x0A,0xB8,0x00,0x7C,0x98,0xC0,0x00,0xFB,0xF5,0x48,0x0F,0x83,0x80,0x52}},
	{0x2D,0x14,{0x00,0x82,0xED,0xAB,0x0F,0x2F,0xEF,0xED,0x00,0x58,0xCB,0x8C,0x00,0xD0,0x10,0x13,0x0F,0xA4,0x46,0xC9}},
	{0x2E,0x14,{0x00,0x82,0xED,0xAB,0x0F,0x51,0xAE,0x7F,0x00,0x58,0xCB,0x8C,0x00,0xAE,0x51,0x81,0x0F,0xA4,0x46,0xC9}},
	{0x2F,0x14,{0x00,0x85,0x3C,0xB7,0x0F,0xCE,0x88,0xA9,0x00,0x39,0xE2,0xAB,0x00,0x31,0x77,0x57,0x0F,0xC0,0xE0,0x9D}},
	{0x30,0x14,{0x00,0x7E,0xF0,0x1F,0x0F,0x02,0x1F,0xC2,0x00,0x7E,0xF0,0x1F,0x00,0xFD,0xDD,0xFD,0x0F,0x82,0x1D,0x80}},
	{0x31,0x14,{0x00,0x7E,0xF0,0x1F,0x0F,0x02,0x1F,0xC2,0x00,0x7E,0xF0,0x1F,0x00,0xFD,0xDD,0xFD,0x0F,0x82,0x1D,0x80}},
	{0x32,0x14,{0x00,0x7F,0xB3,0x2D,0x0F,0x05,0xB6,0x4E,0x00,0x7A,0xC7,0xF5,0x00,0xFA,0x49,0xB2,0x0F,0x85,0x84,0xDE}},
	{0x33,0x14,{0x00,0x7F,0xE6,0xEE,0x0F,0x04,0x0A,0xB8,0x00,0x7C,0x98,0xC0,0x00,0xFB,0xF5,0x48,0x0F,0x83,0x80,0x52}},
	{0x34,0x14,{0x00,0x82,0xED,0xAB,0x0F,0x2F,0xEF,0xED,0x00,0x58,0xCB,0x8C,0x00,0xD0,0x10,0x13,0x0F,0xA4,0x46,0xC9}},
	{0x35,0x14,{0x00,0x82,0xED,0xAB,0x0F,0x51,0xAE,0x7F,0x00,0x58,0xCB,0x8C,0x00,0xAE,0x51,0x81,0x0F,0xA4,0x46,0xC9}},
	{0x36,0x14,{0x00,0x85,0x3C,0xB7,0x0F,0xCE,0x88,0xA9,0x00,0x39,0xE2,0xAB,0x00,0x31,0x77,0x57,0x0F,0xC0,0xE0,0x9D}},
	
	{0x5A,0x14,{0x00,0x7F,0x0E,0x38,0x0F,0x01,0xE3,0x90,0x00,0x7F,0x0E,0x38,0x00,0xFE,0x1A,0xA7,0x0F,0x81,0xE1,0xC8}},
	{0x5B,0x14,{0x00,0x00,0x10,0xA7,0x00,0x00,0x21,0x4E,0x00,0x00,0x10,0xA7,0x00,0xF7,0xB5,0x4D,0x0F,0x88,0x08,0x17}},

	{0x3A,8,{0x00,0x05,0x39,0x47,0x00,0x7A,0xC6,0xB8}},
	{0x3B,8,{0x00,0x05,0x39,0x47,0x00,0x7A,0xC6,0xB8}},
	{0x3C,8,{0x00,0x00,0x00,0xF9,0x00,0x7F,0xFF,0x06}},
	{0x40,4,{0xFD,0xA2,0x14,0x90}},
	{0x41,4,{0x0F,0x81,0x47,0xAF}},
	{0x42,4,{0x00,0x08,0x42,0x10}},

	{0x39,8,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{0x3D,8,{0x00,0x05,0x39,0x47,0x00,0x7A,0xC6,0xB8}},
	{0x3E,8,{0x00,0x05,0x39,0x47,0x00,0x7A,0xC6,0xB8}},
	{0x3F,8,{0x00,0x00,0x00,0xF9,0x00,0x7F,0xFF,0x06}},
	{0x43,4,{0xFD,0x8C,0xD1,0xEA}},// -5.5dB
	{0x44,4,{0x0F,0x84,0x44,0x44}},
	{0x45,4,{0x00,0x08,0x42,0x10}},
	{0x46,4,{0x00,0x00,0x00,0x03}},//0x03,

	{0x07,1,{0x1D}},// 0xFF}},
	{0x05,1,{0x84}},
	{0x0D,1,{0x35}},

	{ENDTBL_FLAG ,0x01,{0x00}},
};

static HI_S32 AMPWriteReg(HI_U8 u1Addr, HI_U8 *pu1Buf, HI_U16 u2ByteCnt)
{
    HI_S32 s32Ret = 0;

	if (pstTas5711Drv->pI2CFunc  == HI_NULL)
	{
		HI_ERR_AMP("I2C Function Null \n");
		return HI_FAILURE;
	}
	
	s32Ret = pstTas5711Drv->pI2CFunc->pfnI2cWrite(pstTas5711Drv->u32I2CNum,
			 pstTas5711Drv->u8DeviceAddr, u1Addr, 1, pu1Buf, u2ByteCnt);
    if (s32Ret != HI_SUCCESS)
    {
    	
		HI_ERR_AMP("Tas5711 i2c write error :I2cNum:0x%x, I2cDevAddr:0x%x, "
				   "u1Addr:0x%x, addlen:0x%x, pu1Buf:0x%x, u2ByteCnt:0x%x\n",
				   pstTas5711Drv->u32I2CNum, pstTas5711Drv->u8DeviceAddr,
				   u1Addr, 1, pu1Buf[0], u2ByteCnt);
    }
    return s32Ret;
}

static HI_S32 AMPReadReg(HI_U8 u1Addr, HI_U8 *pu1Buf, HI_U16 u2ByteCnt)
{
    HI_S32 s32Ret = 0;

	if (pstTas5711Drv->pI2CFunc == HI_NULL)
	{
		HI_ERR_AMP("I2C Function Null \n");
		return HI_FAILURE;
	}

	s32Ret = pstTas5711Drv->pI2CFunc->pfnI2cRead(pstTas5711Drv->u32I2CNum,
			 pstTas5711Drv->u8DeviceAddr, u1Addr, 1, pu1Buf, u2ByteCnt);
    if (s32Ret != HI_SUCCESS)
    {
        //HI_ERR_AMP("5711read fail :%d!\n", s32Ret );
    }
    return s32Ret;
}

static HI_VOID AMPReset(HI_BOOL bReset)
{
	if (pstTas5711Drv == HI_NULL)
	{
		HI_ERR_AMP("TAS5711 no Init! \n");
		return;
	}

	if (pstTas5711Drv->pGpioFunc== HI_NULL)
	{
		HI_ERR_AMP("GPIO Function Null \n");
		return;
	}	
	
	if (pstTas5711Drv->pGpioFunc->pfnGpioDirSetBit)
	{
		pstTas5711Drv->pGpioFunc->pfnGpioDirSetBit(pstTas5711Drv->u32ResetGPIONum,
				pstTas5711Drv->u32GPIOOutputPolarity); //Output Mode
	}
	
	msleep(1);
	
	if (pstTas5711Drv->pGpioFunc->pfnGpioWriteBit)
	{ 
		if (bReset)
        {        	
            pstTas5711Drv->pGpioFunc->pfnGpioWriteBit(pstTas5711Drv->u32ResetGPIONum, 
													   pstTas5711Drv->u32ResetPolarity);
        }
		else
		{
			pstTas5711Drv->pGpioFunc->pfnGpioWriteBit(pstTas5711Drv->u32ResetGPIONum, 
													   !(pstTas5711Drv->u32ResetPolarity));
		}
	}		
	
	msleep(TAS5711_INIT_INTERVAL);

	return;
}

#if 1
static HI_VOID AMPHWMute(HI_BOOL bMute)
{
	if (pstTas5711Drv == HI_NULL)
	{
		HI_ERR_AMP("TAS5711 no Init! \n");
		return;
	}

	if (pstTas5711Drv->pGpioFunc== HI_NULL)
	{
		HI_ERR_AMP("GPIO Function Null \n");
		return;
	}	
	if (pstTas5711Drv->pGpioFunc->pfnGpioDirSetBit)
	{
		pstTas5711Drv->pGpioFunc->pfnGpioDirSetBit(pstTas5711Drv->u32HWMuteGPIONum, 
									  pstTas5711Drv->u32GPIOOutputPolarity); //Output Mode
	}
	
	msleep(1);
	
	if (pstTas5711Drv->pGpioFunc->pfnGpioWriteBit)
	{ 
		if (bMute)
        {        	
            pstTas5711Drv->pGpioFunc->pfnGpioWriteBit(pstTas5711Drv->u32HWMuteGPIONum, 
													   pstTas5711Drv->u32HWMutePolarity);
        }
		else
		{
			pstTas5711Drv->pGpioFunc->pfnGpioWriteBit(pstTas5711Drv->u32HWMuteGPIONum, 
													   !(pstTas5711Drv->u32HWMutePolarity));
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
	TAS5711_REGMAP 	*pstTas5711InitTbl;

	//Set TAS5711 Software ops and Hardware setting
	if (pstAmpDrv == HI_NULL)
	{
		HI_ERR_AMP("Cannot get Any Setting for TAS5711! \n");
		return HI_FAILURE;
	}
	else
	{
		pstTas5711Drv 		= pstAmpDrv;
	}
	
	pstTas5711InitTbl 	= Tas5711_DefautTbl;

    AMPHWMute(HI_FALSE);
	msleep(10);
	AMPReset(HI_TRUE);		//gmh add 20140423
	msleep(10);
	//Release Reset AMP
	AMPReset(HI_FALSE);		

	for(u8Index = 0; ; u8Index ++)
	{
		u8Addr = pstTas5711InitTbl[u8Index].bAddr;
		if(u8Addr == ENDTBL_FLAG)
		{
			break;
		}

		u8Length = pstTas5711InitTbl[u8Index].bLength;
		for(u8CountLoop = 0; u8CountLoop < u8Length; u8CountLoop ++)
		{		
			u8Array[u8CountLoop] = *(pstTas5711InitTbl[u8Index].bArray + u8CountLoop);
		}
		
		s32Ret = AMPWriteReg(u8Addr, u8Array, u8Length);
		if(s32Ret != HI_SUCCESS)
		{
		//	HI_ERR_AMP("TAS5711Init Fail \n");
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

	pstTas5711Drv = HI_NULL;
	
    return;
}

static HI_S32 AMP_SetMute(HI_BOOL bMute)
{
	HI_S32 s32Ret;
	HI_U8  u8Gain[1]= {0};

	if (bMute)
	{
		u8Gain[0] = TAS5711_MIN_VOL;
		s32Ret = AMPWriteReg(0x07, u8Gain, 1);
	}
	else
	{
		u8Gain[0] = TAS5711_MAX_VOL;
		s32Ret = AMPWriteReg(0x07, u8Gain, 1);
	}
	return s32Ret;
}

static HI_S32 AMP_GetMute(HI_BOOL* pbMute)
{
	HI_S32 s32Ret;
	HI_U8  u8Gain = 0;
	
	s32Ret = AMPReadReg(0x07, &u8Gain, 1);
	if (u8Gain == TAS5711_MIN_VOL)
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
		HI_ERR_AMP("TAS5711 reg length MAX is 20\n");
		u32ByteSize = MAX_AMP_REG_LEN;
	}

    Ret = copy_from_user(RegArray, pu8Value, u32ByteSize);
	if(Ret != HI_SUCCESS)
	{
		HI_ERR_AMP("TAS5711 copy_from_user Fail \n");
	}

	Ret = AMPWriteReg(u32RegAddr, RegArray, u32ByteSize);
    if(Ret != HI_SUCCESS)
	{
		HI_ERR_AMP("TAS5711 write I2C Fail \n");
	}
    
    return HI_SUCCESS; 
}

static HI_S32 AMP_ReadReg(HI_U32 u32RegAddr, HI_U32 u32ByteSize, HI_U8* pu8Value)
{
    HI_S32 Ret;
	HI_U8  RegArray[MAX_AMP_REG_LEN];

	if (u32ByteSize > MAX_AMP_REG_LEN)
	{
		HI_ERR_AMP("TAS5711 reg length MAX is 20\n");
		u32ByteSize = MAX_AMP_REG_LEN;
	}
	
	Ret = AMPReadReg(u32RegAddr, RegArray, u32ByteSize);
    if(Ret != HI_SUCCESS)
	{
		HI_ERR_AMP("TAS5711 Read I2C Fail \n");
	}

    Ret = copy_to_user(pu8Value, RegArray, u32ByteSize);
	if(Ret != HI_SUCCESS)
	{
		HI_ERR_AMP("TAS5711 copy_to_user Fail \n");
	}

    return HI_SUCCESS; 
}

static HI_VOID AMP_Proc(struct seq_file* p)
{
	HI_U8 			u8Index, u8Addr, u8Length, u8CountLoop;
	HI_U8 			u8Array[MAX_AMP_REG_LEN];
	TAS5711_REGMAP 	*pstTas5711InitTbl;

	PROC_PRINT(p, "AMP Modul:        TI TAS5711\n");
	PROC_PRINT(p, "I2C Num:          %d\n" ,  pstTas5711Drv->u32I2CNum);
	PROC_PRINT(p, "I2C Addr:         0x%x\n", pstTas5711Drv->u8DeviceAddr);	
	PROC_PRINT(p, "Mute  GPIO Group: %d\n", pstTas5711Drv->u32HWMuteGPIONum/8);
	PROC_PRINT(p, "Mute  GPIO Bit:   %d\n",	pstTas5711Drv->u32HWMuteGPIONum%8);
	PROC_PRINT(p, "Mute  Polarity:   %d\n",	pstTas5711Drv->u32HWMutePolarity);																	
	
	PROC_PRINT(p, "Reset GPIO Group: %d\n", pstTas5711Drv->u32ResetGPIONum/8);
	PROC_PRINT(p, "Reset GPIO Bit:   %d\n", pstTas5711Drv->u32ResetGPIONum%8);
	PROC_PRINT(p, "Reset Polarity:   %d\n", pstTas5711Drv->u32ResetPolarity);

	pstTas5711InitTbl 	= Tas5711_DefautTbl;

	PROC_PRINT(p,"\n--------------------- TAS5711 REGMAP -------------------------------------------------");
	for(u8Index = 0; ; u8Index ++)
	{
		u8Addr = pstTas5711InitTbl[u8Index].bAddr;
		if(u8Addr == ENDTBL_FLAG)
		{
			break;
		}
		u8Length = pstTas5711InitTbl[u8Index].bLength;
		PROC_PRINT(p, "\nAddr[0x%x] Len[%d]: ",u8Addr,u8Length);
		memset(u8Array,0,MAX_AMP_REG_LEN);	
		AMPReadReg(u8Addr, u8Array, u8Length);
		
		for(u8CountLoop = 0; u8CountLoop < u8Length; u8CountLoop ++)
		{
			PROC_PRINT(p, "0x%x ", u8Array[u8CountLoop]);
		}	
	}
	PROC_PRINT(p,"\n--------------------- END TAS5711 REGMAP -------------------------------------------------\n");
	
}

AMP_DRV_FUNC_S stTas5711Func =
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

