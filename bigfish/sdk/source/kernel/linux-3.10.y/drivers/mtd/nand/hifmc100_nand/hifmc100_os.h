/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-02-07
 *
******************************************************************************/
#ifndef HIFMC100_OSH
#define HIFMC100_OSH
/******************************************************************************/

#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/delay.h>
#include <linux/dma-mapping.h>
#include <asm/io.h>
#include <asm/setup.h>
#include <asm/errno.h>
#include <linux/platform_device.h>
#include <linux/mtd/partitions.h>
#include <mach/clkdev.h>
#include <asm/mach/resource.h>
#include <linux/clk.h>
#include <linux/clkdev.h>
#include <linux/debugfs.h>
#include <mach/clkdev.h>
#include <asm/irq.h>
#include <linux/irqreturn.h>
#include <linux/interrupt.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 4, 5))
#  include "../../mtdcore.h"
#endif

/*****************************************************************************/
#ifndef CONFIG_HIFMC100_REG_BASE_ADDRESS
  #define CONFIG_HIFMC100_REG_BASE_ADDRESS	(0xF9950000)
#endif /* CONFIG_HIFMC100_REG_BASE_ADDRESS */
#define CONFIG_HIFMC100_REG_BASE_ADDRESS_LEN	0x100

/*****************************************************************************/
#ifndef CONFIG_HIFMC100_BUFFER_BASE_ADDRESS
  #define CONFIG_HIFMC100_BUFFER_BASE_ADDRESS	(0xFE200000)
#endif /* CONFIG_HIFMC100_BUFFER_BASE_ADDRESS */
#define CONFIG_HIFMC100_BUFFER_BASE_LEN		(0x2000 + 0x400)

/*****************************************************************************/
#ifndef CONFIG_HIFMC100_PERIPHERY_REGBASE
  #define CONFIG_HIFMC100_PERIPHERY_REGBASE	(0xF8A22000)
#endif /* CONFIG_HIFMC100_PERIPHERY_REGBASE */
#define CONFIG_HIFMC100_PERIPHERY_REG_LEN	100

/*****************************************************************************/
/******************************************************************************/
#endif /* HIFMC100_OSH */
