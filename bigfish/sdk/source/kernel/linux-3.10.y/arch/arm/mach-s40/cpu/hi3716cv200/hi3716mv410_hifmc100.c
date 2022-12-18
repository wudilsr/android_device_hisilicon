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
#include <mach/clock.h>
#include <asm/setup.h>
#include <mach/hardware.h>

/*****************************************************************************/

#define PERI_CRG_REG_BASE  __io_address(REG_BASE_CRG)
#define PERI_CRG23                  (PERI_CRG_REG_BASE + 0x5C)
#define PERI_CRG23_CLK_EN           (0x1U << 0)
#define PERI_CRG23_CLK_SEL_MASK     (0x7U << 4)
#define PERI_CRG23_CLK_SEL_24M      (0x4U << 4)
#define PERI_CRG23_CLK_SEL_200M     (0x1U << 4)
#define PERI_CRG23_CLK_SEL_150M     (0x3U << 4)
#define PERI_CRG23_CLK_SEL_125M     (0x5U << 4)
#define PERI_CRG23_CLK_SEL_100M     (0x6U << 4)
#define PERI_CRG23_NF_SRST_REQ      (0x1U << 1)

static int hi3716mv410_hifmc100_enable(struct clk *clk)
{
	unsigned long reg_val;

	reg_val = readl(PERI_CRG23);
	reg_val &= ~PERI_CRG23_CLK_SEL_MASK;
	reg_val |= (PERI_CRG23_CLK_EN
		| PERI_CRG23_CLK_SEL_200M);
	writel(reg_val, PERI_CRG23);

	return 0;
}
/*****************************************************************************/

static void hi3716mv410_hifmc100_disable(struct clk *clk)
{
	unsigned long reg_val;

	reg_val = readl(PERI_CRG23);
	reg_val &= ~PERI_CRG23_CLK_SEL_MASK;
	reg_val &= ~PERI_CRG23_CLK_EN;
	writel(reg_val, PERI_CRG23);
}
/*****************************************************************************/

static struct clk_ops hi3716mv410_hifmc100_clk_ops = {
	.enable = hi3716mv410_hifmc100_enable,
	.disable = hi3716mv410_hifmc100_disable,
	.set_rate = NULL,
	.get_rate = NULL,
	.round_rate = NULL,
};
/*****************************************************************************/

struct clk hi3716mv410_hifmc100_clk = {
	.ops  = &hi3716mv410_hifmc100_clk_ops,
};
/*****************************************************************************/

static struct resource hi3716mv410_hifmc100_resources[] = {
	{
		.name   = "base",
		.start  = 0xF9950000,
		.end    = 0xF9950000 + 0x100,
		.flags  = IORESOURCE_MEM,
	}, {
		.name   = "buffer",
		.start  = 0xFE200000,
		.end    = 0xFE200000 + 2048 + 128,
		.flags  = IORESOURCE_MEM,
	}, {
		.name   = "peri",
		.start  = 0xF8A22000,
		.end    = 0xF8A22000 + 100,
		.flags  = IORESOURCE_MEM,
	}, {
		.name   = "irq",
		.start  = 86,
		.end    = 86,
		.flags  = IORESOURCE_IRQ,
	}
};
/*****************************************************************************/

struct device_resource hi3716mv410_hifmc100_device_resource = {
	.name           = "hifmc100",
	.resource       = hi3716mv410_hifmc100_resources,
	.num_resources  = ARRAY_SIZE(hi3716mv410_hifmc100_resources),
};
/*****************************************************************************/
