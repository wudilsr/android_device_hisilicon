/******************************************************************************
 *    NAND Flash Controller V610 Device Driver
 *    Copyright (c) 2009-2010 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By Czyong.
 *
******************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100.h"

/*****************************************************************************/

static int hifmc100_samsung_set_rr_reg(struct hifmc_host *host,int param)
{
#define SAMSUNG_RR_CMD     0xA1
	u32 regval;

	unsigned char samsung_rr_params[15][4] = {
		{0x00, 0x00, 0x00, 0x00},
		{0x05, 0x0A, 0x00, 0x00},
		{0x28, 0x00, 0xEC, 0xD8},
		{0xED, 0xF5, 0xED, 0xE6},
		{0x0A, 0x0F, 0x05, 0x00},
		{0x0F, 0x0A, 0xFB, 0xEC},
		{0xE8, 0xEF, 0xE8, 0xDC},
		{0xF1, 0xFB, 0xFE, 0xF0},
		{0x0A, 0x00, 0xFB, 0xEC},
		{0xD0, 0xE2, 0xD0, 0xC2},
		{0x14, 0x0F, 0xFB, 0xEC},
		{0xE8, 0xFB, 0xE8, 0xDC},
		{0x1E, 0x14, 0xFB, 0xEC},
		{0xFB, 0xFF, 0xFB, 0xF8},
		{0x07, 0x0C, 0x02, 0x00}
	};

	if (param >= 15)
		param = (param % 15);

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(2);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	/* no need to config WAIT_READY_EN, here not config WAIT_READY_EN bit */
	hifmc_write(host, 1, HIFMC100_DATA_NUM);

	writel(samsung_rr_params[param][0], host->chip->IO_ADDR_R);
	hifmc_write(host, 0xA700, HIFMC100_ADDRL);
	hifmc_write(host, SAMSUNG_RR_CMD, HIFMC100_CMD);

	hifmc_write(host, HIFMC100_WRITE_1CMD_2ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	writel(samsung_rr_params[param][1], host->chip->IO_ADDR_R);
	hifmc_write(host, 0xA400, HIFMC100_ADDRL);
	hifmc_write(host, SAMSUNG_RR_CMD, HIFMC100_CMD);
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(2);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_WRITE_1CMD_2ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	writel(samsung_rr_params[param][2], host->chip->IO_ADDR_R);
	hifmc_write(host, 0xA500, HIFMC100_ADDRL);
	hifmc_write(host, SAMSUNG_RR_CMD, HIFMC100_CMD);
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(2);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_WRITE_1CMD_2ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	writel(samsung_rr_params[param][3], host->chip->IO_ADDR_R);
	hifmc_write(host, 0xA600, HIFMC100_ADDRL);
	hifmc_write(host, SAMSUNG_RR_CMD, HIFMC100_CMD);
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(2);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_WRITE_1CMD_2ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	host->enable_ecc_randomizer(host, ENABLE, ENABLE);

	return 0;

#undef SAMSUNG_RR_CMD
}
/*****************************************************************************/

static int hifmc100_samsung_set_rr_param(void *host,int param)
{
	return hifmc100_samsung_set_rr_reg((struct hifmc_host *)host, param);
}
/*****************************************************************************/

static int hifmc100_samsung_reset_rr_param(void *host)
{
	return hifmc100_samsung_set_rr_reg((struct hifmc_host *)host, 0);
}
/*****************************************************************************/

struct read_retry_t hifmc100_samsung_read_retry = {
	.type = NAND_RR_SAMSUNG,
	.count = 15,
	.set_rr_param = hifmc100_samsung_set_rr_param,
	.get_rr_param = NULL,
	.reset_rr_param = hifmc100_samsung_reset_rr_param,
};

