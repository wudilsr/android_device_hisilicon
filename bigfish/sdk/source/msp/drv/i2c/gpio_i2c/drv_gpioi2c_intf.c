/*********************************************************************************
*
*  Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
*  This program is confidential and proprietary to Hisilicon Technologies Co., Ltd.
*  (Hisilicon), and may not be copied, reproduced, modified, disclosed to
*  others, published or used, in whole or in part, without the express prior
*  written permission of Hisilicon.
*
***********************************************************************************/

#include <linux/vmalloc.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <asm/unistd.h>

#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/mm.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>
#include <linux/slab.h>
//#include <linux/smp_lock.h>

#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/system.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>

//#include <kcom/mmz.h>

#include <mach/hardware.h>
#include <asm/signal.h>
#include <linux/time.h>

#include <linux/unistd.h>

#include <linux/delay.h>
#include <linux/mm.h>

#include "hi_common.h"
#include "drv_gpioi2c_ext.h"
#include "drv_gpioi2c.h"
#include "hi_drv_gpioi2c.h"
#include "drv_i2c_ioctl.h"
#include "drv_gpio_ext.h"
#include "hi_drv_sys.h"

#if 0
static int gpioidclock = 11;
static int gpioiddata = 12;
static int clockbit = 3;
static int databit = 5;
module_param(gpioidclock, int, S_IRUGO);
module_param(gpioiddata, int, S_IRUGO);
module_param(clockbit, int, S_IRUGO);
module_param(databit, int, S_IRUGO);
static HI_CHIP_TYPE_E g_enChipType;
static HI_CHIP_VERSION_E g_enChipVersion;
#endif
extern int i2cmode;
module_param(i2cmode, int, S_IRUGO);

/*************************************************************************/

HI_S32 GPIOI2C_DRV_ModInit(HI_VOID)
{
    HI_S32 ret = 0;

#ifndef HI_MCE_SUPPORT
    ret = HI_DRV_GPIOI2C_Init();
#endif

#ifdef MODULE
    HI_PRINT("Load hi_gpioi2c.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;
}

HI_VOID GPIOI2C_DRV_ModExit(HI_VOID)
{
#ifndef HI_MCE_SUPPORT
    HI_DRV_GPIOI2C_DeInit();
#endif

    return;
}

#ifdef MODULE
module_init(GPIOI2C_DRV_ModInit);
module_exit(GPIOI2C_DRV_ModExit);
#endif

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HISILICON");
