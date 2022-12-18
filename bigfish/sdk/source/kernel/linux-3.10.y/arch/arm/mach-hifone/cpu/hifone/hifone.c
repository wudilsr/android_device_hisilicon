/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-02-07
 *
******************************************************************************/

#include <linux/err.h>
#include <linux/completion.h>
#include <linux/kernel.h>
#include <asm/mach/resource.h>
#include <asm/system.h>
#include <mach/platform.h>
#include <asm/io.h>
#include <mach/clock.h>
#include <mach/io.h>
#include <mach/cpu.h>


extern struct device_resource hifone_hinfc610_device_resource;
/*****************************************************************************/

int usb_dev_dma_fixed  = 1;
EXPORT_SYMBOL(usb_dev_dma_fixed);

static struct device_resource *hifone_device_resource[] = {
	&hifone_hinfc610_device_resource,
	NULL,
};
/*****************************************************************************/
extern struct clk hifone_hinfc610_clk;

static struct clk hifone_uart_clk = {
#ifdef CONFIG_HIFONE_FPGA
	.rate = 54000000,
#else
	.rate = 83300000,
#endif
};
static struct clk hifone_uart1_clk = {
#ifdef CONFIG_HIFONE_FPGA
	.rate = 54000000,
#else
	.rate = 3000000,
#endif
};

static struct clk_lookup hifone_lookups[] = {
	{
		.dev_id = "hinfc610",
		.clk    = &hifone_hinfc610_clk,
	}, { /* UART0 */
		.dev_id		= "uart:0",
		.clk		= &hifone_uart_clk,
	}, { /* UART1 */
		.dev_id		= "uart:1",
		.clk		= &hifone_uart1_clk,
	}, { /* UART2 */
		.dev_id		= "uart:2",
		.clk		= &hifone_uart_clk,
	}, 
};

/*****************************************************************************/

static void hifone_cpu_init(struct cpu_info *info)
{
	info->clk_cpu    = 800000000;
	info->clk_timer  = 24000000;
	info->cpuversion = "";
	clkdev_add_table(hifone_lookups,
		ARRAY_SIZE(hifone_lookups));	
}
/*****************************************************************************/
/* Hi3798Cv200_a */
struct cpu_info hi3798cv200_a_cpu_info =
{
	.name = "Hi3798Cv200_a",
	.chipid = _HIFONEB02,
	.chipid_mask = _HIFONEB02_MASK,
	.resource = hifone_device_resource,
	.init = hifone_cpu_init,
};


