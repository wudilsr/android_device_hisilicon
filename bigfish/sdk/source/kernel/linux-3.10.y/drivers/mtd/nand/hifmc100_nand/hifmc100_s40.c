/******************************************************************************
*    FMC Flash Memory Controller V100 Device Driver
*    Copyright (c) 2009-2010 by Hisilicon.
*    All rights reserved.
* ***
*
******************************************************************************/
#include <mach/platform.h>
#include <mach/hardware.h>

#include "hifmc100.h"
#include "hifmc100_os.h"

#define HIFMC100_CRG23				0x5C
#define CRG23_SPI_NAND_CLK_SEL(_clk)		(((_clk) & 0x7) << 4)
#define CRG23_SPI_NAND_CLK_EN			(1 << 0)
#define CRG23_SPI_NAND_SOFT_RST_REQ		(1 << 1)

#define HIFMC100_SPI_NAND_CLK_SEL_MASK		(0x7 << 4)
#define HIFMC100_SPI_NAND_CLK_SEL_12M		0x40
#define HIFMC100_SPI_NAND_CLK_SEL_37M		0x70
#define HIFMC100_SPI_NAND_CLK_SEL_50M		0x60
#define HIFMC100_SPI_NAND_CLK_SEL_62M		0x50 
#define HIFMC100_SPI_NAND_CLK_SEL_75M		0x30
#define HIFMC100_SPI_NAND_CLK_SEL_86M		0x20
#define HIFMC100_SPI_NAND_CLK_SEL_100M		0x10
#define HIFMC100_SPI_NAND_CLK_SEL_200M		0x00


/*****************************************************************************/
void hifmc100_nand_controller_enable(struct hifmc_host *host, int enable)
{
	u32 regval = readl(host->sysreg + HIFMC100_CRG23);

	if (!(regval & HIFMC100_SPI_NAND_CLK_SEL_MASK))
		regval |= HIFMC100_SPI_NAND_CLK_SEL_200M;

	if (enable)
		regval |= CRG23_SPI_NAND_CLK_EN;
	else
		regval &= ~CRG23_SPI_NAND_CLK_EN;

	regval &= ~CRG23_SPI_NAND_SOFT_RST_REQ;

	if (readl(host->sysreg + HIFMC100_CRG23) != regval)
		writel(regval, (host->sysreg + HIFMC100_CRG23));
}

/*****************************************************************************/

