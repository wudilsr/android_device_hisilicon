/******************************************************************************
*    Copyright (c) 2014 by Hisilicon.
*    All rights reserved.
******************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100.h"

#define HIFMC100_CRG23				0x5C
#define HIFMC100_CRG23_SPI_NAND_CLK_EN		(1 << 0)
#define HIFMC100_CRG23_SPI_NAND_SOFT_RST_REQ	(1 << 1)
#define HIFMC100_CRG23_SPI_NAND_CLK_OFFSET	4

#define HIFMC100_SPI_NAND_CLK_SEL_MASK		(0x7 << HIFMC100_CRG23_SPI_NAND_CLK_OFFSET)
#define HIFMC100_SPI_NAND_CLK_SEL_12M		0x40
#define HIFMC100_SPI_NAND_CLK_SEL_37M		0x70
#define HIFMC100_SPI_NAND_CLK_SEL_50M		0x60
#define HIFMC100_SPI_NAND_CLK_SEL_62M		0x50
#define HIFMC100_SPI_NAND_CLK_SEL_75M		0x30
#define HIFMC100_SPI_NAND_CLK_SEL_86M		0x20
#define HIFMC100_SPI_NAND_CLK_SEL_100M		0x10
#define HIFMC100_SPI_NAND_CLK_SEL_200M		0x00

/*****************************************************************************/
void hifmc100_set_system_clock(struct hifmc_host *host, 
			       struct spi_op_info *op, int clk_en)
{

	u32 regval = HIFMC100_SPI_NAND_CLK_SEL_37M;
	if (op && op->clock)
		regval = (op->clock & 0x70);

	if (clk_en) {
		regval |= HIFMC100_CRG23_SPI_NAND_CLK_EN;

		if (readl(host->sysreg + HIFMC100_CRG23) != regval)
			writel(regval, (host->sysreg + HIFMC100_CRG23));
	} else {
		regval &= ~HIFMC100_CRG23_SPI_NAND_CLK_EN;
		writel(regval, (host->sysreg + HIFMC100_CRG23));
	}
}

/*****************************************************************************/
void hifmc100_spi_nand_get_best_clock(unsigned int *clock)
{
	int ix,clk;
	unsigned int sysclk[] = {
		38,  HIFMC100_SPI_NAND_CLK_SEL_37M,
		50,  HIFMC100_SPI_NAND_CLK_SEL_50M,
		62,  HIFMC100_SPI_NAND_CLK_SEL_62M,
		75,  HIFMC100_SPI_NAND_CLK_SEL_75M,
		86,  HIFMC100_SPI_NAND_CLK_SEL_86M,
		100, HIFMC100_SPI_NAND_CLK_SEL_100M,
		200, HIFMC100_SPI_NAND_CLK_SEL_200M,

		0,0,
	};

	clk = HIFMC100_SPI_NAND_CLK_SEL_37M; 
	for (ix = 0; sysclk[ix] != 0; ix += 2) {
		if (*clock < sysclk[ix])
			break;
		clk = sysclk[ix+1];
	}

	*clock = clk;
}

