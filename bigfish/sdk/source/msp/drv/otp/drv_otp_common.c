/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_otp_common.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 
  Last Modified :
  Description   : 
  Function List :
  History       :
******************************************************************************/
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <asm/delay.h>
#include <linux/kernel.h>
#include <mach/platform.h>
#include <mach/hardware.h>
#include <asm/io.h>
#include <asm/memory.h>
#include "hi_type.h"
#include "drv_otp.h"
#if defined(CHIP_TYPE_hi3716mv310)
#include "drv_reg_ext.h"
#else
#include "hi_drv_reg.h"
#endif

#ifndef SDK_OTP_ARCH_VERSION_V3
#ifndef HI_REG_READ32
#define HI_REG_READ32(addr,result)  ((result) = *(volatile unsigned int *)(addr))
#endif

#ifndef HI_REG_WRITE32
#define HI_REG_WRITE32(addr,result)  (*(volatile unsigned int *)(addr) = (result))
#endif
#endif

HI_VOID otp_write_reg(HI_U32 addr, HI_U32 val)
{
    HI_REG_WRITE32(IO_ADDRESS(addr), val);
	return;
}

HI_U32 otp_read_reg(HI_U32 addr)
{
	HI_U32 val = 0;
	HI_REG_READ32(IO_ADDRESS(addr), val);
    return val;
}

HI_VOID otp_wait(HI_U32 us)
{
    HI_U32 u32Tmp = us%1000;
    
    if(us >= 1000)
    {
        msleep(us/1000);
    }
    if(u32Tmp > 0)
    {
        udelay(u32Tmp);
    }
}

/*---------------------------------------------END--------------------------------------*/

