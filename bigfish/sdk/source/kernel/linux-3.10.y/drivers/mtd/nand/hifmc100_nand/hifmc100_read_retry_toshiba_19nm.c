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

static int hifmc100_toshiba_19nm_set_rr_reg(struct hifmc_host *host, int param)
{
#define TOSHIBA_RR_CMD          0x55
#define TOSHIBA_RR_DATA_NUM     0x5
	u32 regval;

	static char toshiba_rr_param[][TOSHIBA_RR_DATA_NUM] = 
	{
		{0x00, 0x00, 0x00, 0x00, 0x00},
		{0x04, 0x04, 0x7c, 0x7e, 0x00},
		{0x00, 0x7c, 0x78, 0x78, 0x00},
		{0x7c, 0x76, 0x74, 0x72, 0x00},
		{0x08, 0x08, 0x00, 0x00, 0x00},
		{0x0b, 0x7e, 0x76, 0x74, 0x00},
		{0x10, 0x76, 0x72, 0x70, 0x00},
		{0x02, 0x7c, 0x7e, 0x70, 0x00},
	};

	if (param > 7)
		param = (param % 7);

	/* 
	 * no need to config WAIT_READY_EN, here not config WAIT_READY_EN
	 */

	hifmc_write(host, 1, HIFMC100_DATA_NUM);

	writel(toshiba_rr_param[param][0], host->chip->IO_ADDR_R);
	hifmc_write(host, 0x4, HIFMC100_ADDRL);
	hifmc_write(host, TOSHIBA_RR_CMD, HIFMC100_CMD);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	/* 
	 * no need to config WAIT_READY_EN, here not config WAIT_READY_EN
	 */
	hifmc_write(host, HIFMC100_WRITE_1CMD_1ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	writel(toshiba_rr_param[param][1], host->chip->IO_ADDR_R);
	hifmc_write(host, 0x5, HIFMC100_ADDRL);
	hifmc_write(host, TOSHIBA_RR_CMD, HIFMC100_CMD);
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_WRITE_1CMD_1ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	writel(toshiba_rr_param[param][2], host->chip->IO_ADDR_R);
	hifmc_write(host, 0x6, HIFMC100_ADDRL);
	hifmc_write(host, TOSHIBA_RR_CMD, HIFMC100_CMD);
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_WRITE_1CMD_1ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	writel(toshiba_rr_param[param][3], host->chip->IO_ADDR_R);
	hifmc_write(host, 0x7, HIFMC100_ADDRL);
	hifmc_write(host, TOSHIBA_RR_CMD, HIFMC100_CMD);
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_WRITE_1CMD_1ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	writel(toshiba_rr_param[param][4], host->chip->IO_ADDR_R);
	hifmc_write(host, 0xd, HIFMC100_ADDRL);
	hifmc_write(host, TOSHIBA_RR_CMD, HIFMC100_CMD);
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_WRITE_1CMD_1ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(host);

	return 0;

#undef TOSHIBA_RR_CMD
#undef TOSHIBA_RR_DATA_NUM
}
/*****************************************************************************/

static int hifmc100_toshiba_19nm_set_rr_param(void *host, int param)
{
	static int entry_rr_flag = 0;
	int regval;
	struct hifmc_host *hifmc_host = (struct hifmc_host *)host;

	regval = hifmc_read(hifmc_host, HIFMC100_PND_PWIDTH_CFG);
	hifmc_write(hifmc_host, 0xFFF, HIFMC100_PND_PWIDTH_CFG);

	hifmc_host->enable_ecc_randomizer(hifmc_host, DISABLE, DISABLE);

	regval = HIFMC100_OP_CFG_FM_CS(hifmc_host->chipselect);
	hifmc_write(hifmc_host, regval, HIFMC100_OP_CFG);

	/* first entry RR mode. */
	if (!entry_rr_flag) {
		hifmc_write(hifmc_host, (0xc5 << 8 | 0x5c), HIFMC100_CMD);
		hifmc_write(hifmc_host, HIFMC100_WRITE_2CMD_0ADD_NODATA, 
			    HIFMC100_OP);
		FMC_CMD_WAIT_CPU_FINISH(hifmc_host);

		entry_rr_flag = 1;
	}

	hifmc100_toshiba_19nm_set_rr_reg(hifmc_host, param);

	/* according to 19nm rr spec, 4th rr need send 0xb3 cmd befor 0x5d26 cmd */
	if (param == 4) {
		hifmc_write(hifmc_host, 0xB3, HIFMC100_CMD);
		regval = HIFMC100_OP_CFG_FM_CS(hifmc_host->chipselect);
		hifmc_write(hifmc_host, regval, HIFMC100_OP_CFG);
		hifmc_write(hifmc_host, HIFMC100_WRITE_1CMD_0ADD_NODATA, 
			    HIFMC100_OP);
		FMC_CMD_WAIT_CPU_FINISH(hifmc_host);
	}

	if (param) {
		hifmc_write(hifmc_host, (0x5d << 8 | 0x26), HIFMC100_CMD);
		regval = HIFMC100_OP_CFG_FM_CS(hifmc_host->chipselect);
		hifmc_write(hifmc_host, regval, HIFMC100_OP_CFG);
		hifmc_write(hifmc_host, HIFMC100_WRITE_2CMD_0ADD_NODATA, 
			    HIFMC100_OP);

		FMC_CMD_WAIT_CPU_FINISH(hifmc_host);
	} else {
		/* exit RR mode. */
		hifmc_host->send_cmd_reset(hifmc_host, hifmc_host->chipselect);
		entry_rr_flag = 0;
	}

	hifmc_host->enable_ecc_randomizer(hifmc_host, ENABLE, ENABLE);
	hifmc_write(hifmc_host, regval, HIFMC100_PND_PWIDTH_CFG);

	return 0;
}
/*****************************************************************************/

static int hifmc100_toshiba_19nm_reset_rr_param(void *host)
{
	return hifmc100_toshiba_19nm_set_rr_reg((struct hifmc_host *)host, 0);
}
/*****************************************************************************/
struct read_retry_t hifmc100_toshiba_19nm_read_retry = {
	.type = NAND_RR_TOSHIBA_19nm,
	.count = 8,
	.set_rr_param = hifmc100_toshiba_19nm_set_rr_param,
	.get_rr_param = NULL,
	.reset_rr_param = hifmc100_toshiba_19nm_reset_rr_param,
};
