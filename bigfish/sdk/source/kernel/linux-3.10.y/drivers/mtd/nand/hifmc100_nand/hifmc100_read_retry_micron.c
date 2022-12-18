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

#define MICRON_RR_ADDR         0x89

static int hifmc100_micron_set_rr_reg(struct hifmc_host *host, int rr)
{
	u32 regval;
	u32 reg_pwidth;

	reg_pwidth = hifmc_read(host, HIFMC100_PND_PWIDTH_CFG);
	hifmc_write(host, 0xFFF, HIFMC100_PND_PWIDTH_CFG);

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	hifmc_write(host, 1, HIFMC100_DATA_NUM);

	writel(rr, host->chip->IO_ADDR_W);
	hifmc_write(host, MICRON_RR_ADDR, HIFMC100_ADDRL);
	/* set read retry */
	hifmc_write(host, 0xEF, HIFMC100_CMD);

	/* need to config WAIT_READY_EN, here config WAIT_READY_EN bit. */
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	/* need to config WAIT_READY_EN, here config WAIT_READY_EN bit. */
	hifmc_write(host, HIFMC100_WRITE_1CMD_1ADD_DATA_WAIT_READY, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	host->enable_ecc_randomizer(host, ENABLE, ENABLE);
	hifmc_write(host, reg_pwidth, HIFMC100_PND_PWIDTH_CFG);

	return 0;
}
/*****************************************************************************/

#if 0
static int hifmc100_micron_get_rr_param(struct hifmc_host *host)
{
	u32 regval;
#define MICRON_GET_RR          0xEE
	hifmc_write(host, 1, HIFMC100_DATA_NUM);

	hifmc_write(host, MICRON_RR_ADDR, HIFMC100_ADDRL);
	hifmc_write(host, MICRON_GET_RR, HIFMC100_CMD);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_READ_1CMD_1ADD_DATA, HIFMC100_OP);
	HIFMC100_CMD_WAIT_CPU_FINISH(host);
	hifmc_write(host, NAND_CMD_READ0, HIFMC100_CMD);
	hifmc_write(host, HIFMC100_READ_1CMD_0ADD_NODATA, HIFMC100_OP);
#undef MICRON_GET_RR
	return (readl(host->chip->IO_ADDR_R) & 0xff);
}
#endif
#undef MICRON_RR_ADDR
/*****************************************************************************/

static int hifmc100_micron_set_rr_param(void *host, int rr_option)
{
	return hifmc100_micron_set_rr_reg((struct hifmc_host *)host, rr_option);
}
/*****************************************************************************/

static int hifmc100_micron_reset_rr_param(void *host)
{
	return hifmc100_micron_set_rr_reg((struct hifmc_host *)host, 0);
}
/*****************************************************************************/

struct read_retry_t hifmc100_micron_read_retry = {
	.type = NAND_RR_MICRON,
	.count = 8,
	.set_rr_param = hifmc100_micron_set_rr_param,
	.get_rr_param = NULL,
	.reset_rr_param = hifmc100_micron_reset_rr_param,
};
