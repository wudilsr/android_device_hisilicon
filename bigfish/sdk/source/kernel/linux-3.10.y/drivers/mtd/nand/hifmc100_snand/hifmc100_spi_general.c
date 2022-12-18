/*****************************************************************************
 *    Copyright (c) 2014 by Hisilicon
 *    All rights reserved.
 *****************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100.h"

/*****************************************************************************/
/*
  Send set/get features command to SPI Nand flash
*/
void spi_nand_feature_op(struct hifmc_host *host, unsigned char op,
			unsigned char addr, unsigned char *val)
{
	u32 regval;

	/* get/set feature need set ecc0. */
	hifmc_write(host, host->FMC_CFG_ECC_NONE, HIFMC100_CFG);

	hifmc_write(host, op ? SPI_CMD_SET_FEATURE : SPI_CMD_GET_FEATURE, 
		    HIFMC100_CMD);

	hifmc_write(host, addr, HIFMC100_ADDRL);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
		| HIFMC100_OP_CFG_ADDR_NUM(FEATURES_OP_ADDR_NUM);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(FEATURES_DATA_NUM), 
		    HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_ADDR_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;

	if (SET_FEATURE == op) {
		regval |= HIFMC100_OP_WRITE_DATE_EN(ENABLE);
		writeb(*val, host->iobase);

		hifmc_write(host, regval, HIFMC100_OP);

		FMC_CMD_WAIT_CPU_FINISH(host);
	} else {
		regval |= HIFMC100_OP_READ_DATE_EN(ENABLE);
		hifmc_write(host, regval, HIFMC100_OP);

		FMC_CMD_WAIT_CPU_FINISH(host);

		*val = readb(host->iobase);
	}

	/* restore HIFMC100_CFG */
	hifmc_write(host, host->FMC_CFG, HIFMC100_CFG);
}

/*****************************************************************************/
/*
  Read status[C0H]:[0]bit OIP, judge whether the device is busy or not
*/
static int spi_general_wait_ready(struct hifmc_op *spi)
{
	unsigned char regval = 0;
	unsigned long deadline = jiffies + HIFMC100_MAX_READY_WAIT_JIFFIES;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	do {
		spi_nand_feature_op(host, GET_FEATURE, STATUS_REGISTER, 
					     &regval);
		if (!(regval & STATUS_OIP_MASK))
			return 0;

		cond_resched();

	} while (!time_after_eq(jiffies, deadline));

	printk("Wait spi nand chip ready timeout: status: 0x%x!\n", regval);

	return 1;
}

/*****************************************************************************/
/*
  Send write enable command to SPI Nand, status[C0H]:[2]bit WEL must be set 1
*/
static int spi_general_write_enable(struct hifmc_op *spi)
{
	u32 regval;
	unsigned char status;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	spi_nand_feature_op(host, GET_FEATURE, STATUS_REGISTER, &status);
	if (status & STATUS_WEL_MASK) {
		PR_OUT("Warning: Write Enable was already enabled! "
			"status: 0x%x\n", status);
		return 0;
	}

	regval = hifmc_read(host, HIFMC100_GLOBAL_CFG);
	if (regval & HIFMC100_GLOBAL_CFG_WP_ENABLE) {
		regval &= ~HIFMC100_GLOBAL_CFG_WP_ENABLE;
		hifmc_write(host, regval, HIFMC100_GLOBAL_CFG);
	}

	hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_WREN), HIFMC100_CMD);
	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(host->chipselect), 
		    HIFMC100_OP_CFG);
	regval = HIFMC100_OP_CMD1_EN(ENABLE) | HIFMC100_OP_REG_OP_START;
	hifmc_write(host, HIFMC100_OP_CMD1_EN(ENABLE) 
			  | HIFMC100_OP_REG_OP_START, 
		    HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	spi_nand_feature_op(host, GET_FEATURE, STATUS_REGISTER, &status);
	if (!(status & STATUS_WEL_MASK)) {
		PR_OUT("Config WEL failed, Status Register: 0x%x.\n", status);
		return 1;
	}

	return 0;
}

/*****************************************************************************/
/*
  judge whether SPI Nand support QUAD read/write or not
*/
static int hifmc100_iftype_quad_support(struct hifmc_op *spi)
{

	if (HIFMC100_IF_TYPE_QUAD == spi->write->iftype
	    || HIFMC100_IF_TYPE_QUAD == spi->read->iftype
	    || HIFMC100_IF_TYPE_QUAD_ADDR == spi->read->iftype)
		return 1;

	return 0;
}

/*****************************************************************************/
/*
  Send set features command to SPI Nand, feature[B0H]:[0]bit QE would be set
*/
static int spi_general_quad_enable(struct hifmc_op *spi)
{
	int op;
	unsigned char regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	op = hifmc100_iftype_quad_support(spi);

	spi_nand_feature_op(host, GET_FEATURE, FEATURE_REGISTER, &regval);
	if ((regval & FEATURE_QE_ENABLE) == op)
		return op;

	if (op == ENABLE)
		regval |= FEATURE_QE_ENABLE;
	else
		regval &= ~FEATURE_QE_ENABLE;

	spi_nand_feature_op(host, SET_FEATURE, FEATURE_REGISTER, &regval);

	/* set feature is 200-500ms, wait for command complete. --pbquan */
	spi->driver->wait_ready(spi);

	spi_nand_feature_op(host, GET_FEATURE, FEATURE_REGISTER, &regval);
	if ((regval & FEATURE_QE_ENABLE) != op)
		PR_OUT("Config QE failed: controler %s, but flash %s\n", 
			op ? "enabled" : "disabled",
			(regval & FEATURE_QE_ENABLE) ? "enabled" : "disabled");

	return op;
}

