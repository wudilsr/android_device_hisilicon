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

static int hynix_bg_bdie_rr_org_exist = 0;
static char hynix_bg_bdie_rr_org[4] = {0};

/*****************************************************************************/

static int hifmc100_hynix_bg_bdie_set_rr_reg(struct hifmc_host *host, int index)
{
	int ix;
	u32 regval;
	u32 pnd_pwidth;
	char HYNIX_BG_BDIE_RR_REG[4] = {0xA7,  0xAD,  0xAE,  0xAF};
	char value_offset[7][4] = {
		{0x00,  0x00,  0x00,  0x00},
		{0x00,  0x06,  0x0A,  0x06},
		{0x7F, -0x03, -0x07, -0x08},
		{0x7F, -0x06, -0x0D, -0x0F},
		{0x7F, -0x09, -0x14, -0x17},
		{0x7F,  0x7F, -0x1A, -0x1E},
		{0x7F,  0x7F, -0x20, -0x25}
	};
	char *value = &value_offset[index][0];

	pnd_pwidth = hifmc_read(host, HIFMC100_PND_PWIDTH_CFG);
	hifmc_write(host, 0xFFF, HIFMC100_PND_PWIDTH_CFG);

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);
	hifmc_write(host, 1, HIFMC100_DATA_NUM);

	if (!hynix_bg_bdie_rr_org_exist) {

		for (ix = 0; ix < 4; ix++) {

			memset(host->chip->IO_ADDR_R, 0xff, 32);

			hifmc_write(host, 0x37, HIFMC100_CMD);
			hifmc_write(host, HYNIX_BG_BDIE_RR_REG[ix],
				HIFMC100_ADDRL);
			/* 
			 * according to hynix doc, no need to config HIFMC100_OP_WAIT_READY_EN,
			 * here not config this bit, confirmed by yubingxu.
			 */
			regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
					| HIFMC100_OP_CFG_ADDR_NUM(1);
			hifmc_write(host, regval, HIFMC100_OP_CFG);

			hifmc_write(host, HIFMC100_READ_1CMD_1ADD_DATA,
				HIFMC100_OP);
			FMC_CMD_WAIT_CPU_FINISH(host);

			hynix_bg_bdie_rr_org[ix]
				= (char)(readl(host->chip->IO_ADDR_R) & 0xff);
		}
		hynix_bg_bdie_rr_org_exist = 1;
	}

	for (ix = 0; ix < 4; ix++) {
		if (value[ix] == 0x7F)
			value[ix] = 0x00;
		else
			value[ix] += hynix_bg_bdie_rr_org[ix];
	}

	writel(value[0], host->chip->IO_ADDR_W);
	hifmc_write(host, HYNIX_BG_BDIE_RR_REG[0], HIFMC100_ADDRL);
	hifmc_write(host, 0x36, HIFMC100_CMD);
	/*
	 * according to hynix doc, no need to config HIFMC100_OP_WAIT_READY_EN,
	 * here not config this bit.
	 */
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_WRITE_1CMD_1ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	for (ix = 1; ix < 4; ix++) {
		writel(value[ix], host->chip->IO_ADDR_W);
		hifmc_write(host, HYNIX_BG_BDIE_RR_REG[ix], HIFMC100_ADDRL);
		/*
		 * according to hynix doc, no need to config HIFMC100_OP_WAIT_READY_EN,
		 * here not config this bit.
		 */
		regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
				| HIFMC100_OP_CFG_ADDR_NUM(1);
		hifmc_write(host, regval, HIFMC100_OP_CFG);

		hifmc_write(host, HIFMC100_WRITE_0CMD_1ADD_DATA, HIFMC100_OP);
		FMC_CMD_WAIT_CPU_FINISH(host);
	}

	hifmc_write(host, 0x16, HIFMC100_CMD);
	/*
	 * according to hynix doc, only 1 cmd: 0x16. 
	 * And no need to config HIFMC100_OP_WAIT_READY_EN, here not config this bit.
	 */
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_WRITE_1CMD_0ADD_NODATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	host->enable_ecc_randomizer(host, ENABLE, ENABLE);
	hifmc_write(host, pnd_pwidth, HIFMC100_PND_PWIDTH_CFG);

	return 0;
}
/*****************************************************************************/

static int hifmc100_hynix_bg_bdie_set_rr_param(void *host, int param)
{
	if (!param)
		return 0;
	return hifmc100_hynix_bg_bdie_set_rr_reg((struct hifmc_host *)host, param);
}
/*****************************************************************************/

static int hifmc100_hynix_bg_bdie_reset_rr_param(void *host)
{
	return hifmc100_hynix_bg_bdie_set_rr_param(host, 0);
}
/*****************************************************************************/

struct read_retry_t hifmc100_hynix_bg_bdie_read_retry = {
	.type = NAND_RR_HYNIX_BG_BDIE,
	.count = 7,
	.set_rr_param = hifmc100_hynix_bg_bdie_set_rr_param,
	.get_rr_param = NULL,
	.reset_rr_param = hifmc100_hynix_bg_bdie_reset_rr_param,
};
