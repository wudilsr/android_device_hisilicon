/*****************************************************************************
 *    Copyright (c) 2009-2011 by Hisilicon
 *    All rights reserved.
 *****************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100.h"

/*****************************************************************************/
unsigned char spi_general_get_status_register(struct hifmc_spi *spi)
{
	unsigned char status;
	u32 regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	regval = HIFMC100_OP_READ_STATUS_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	status = hifmc_read(host, HIFMC100_STATUS);

	return status;
}

/*****************************************************************************/
unsigned char spi_general_get_config_register(struct hifmc_spi *spi)
{
	u32 regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_RDCR), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(SPI_NOR_CR_LEN), 
		    HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_READ_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	return readb(host->iobase);
}

/*****************************************************************************/
static int spi_general_wait_ready(struct hifmc_spi *spi)
{
	unsigned char status;
	unsigned long deadline = jiffies + HIFMC100_MAX_READY_WAIT_JIFFIES;

	do {
		status = spi_general_get_status_register(spi);
		if (!(status & SPI_NOR_SR_WIP_MASK))
			return 0;

		cond_resched();

	} while (!time_after_eq(jiffies, deadline));

	PR_OUT("ERROR: spi nor wait ready timeout, status: 0x%x\n", status);

	return 1;
}

/*****************************************************************************/
static int spi_general_write_enable(struct hifmc_spi *spi)
{
	unsigned char status;
	unsigned int regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	status = spi_general_get_status_register(spi);
	if (status & STATUS_WEL_MASK) {
		PR_OUT("Warning: Write Enable was opened! reg[%#x]\n",
				status);
		return status;
	}

	hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_WREN), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	status = spi_general_get_status_register(spi);
	if (!(status & STATUS_WEL_MASK)) {
		PR_OUT("ERROR: Write Enable failed! status: 0x%x\n", status);
		return status;
	}

	return 0;
}

/*****************************************************************************/
/*
  enable 4byte address for SPI which memory more than 16M
*/
static int spi_general_entry_4addr(struct hifmc_spi *spi, int enable)
{
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	if (spi->addrcycle != SPI_4BYTE_ADDR_LEN)
		return 0;

	if (enable)
		hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_EN4B), HIFMC100_CMD);
	else
		hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_EX4B), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_OP_CMD1_EN(ENABLE)
			| HIFMC100_OP_WRITE_DATE_EN(ENABLE)
			| HIFMC100_OP_REG_OP_START, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	host->set_host_addr_mode(host, enable);

	return 0;
}

/*****************************************************************************/
/*
  judge whether SPI Nor support QUAD read write or not
*/
static int hifmc100_iftype_quad_support(struct hifmc_spi *spi)
{
	if (HIFMC100_IF_TYPE_QUAD == spi->write->iftype
	    || HIFMC100_IF_TYPE_QUAD == spi->read->iftype
	    || HIFMC100_IF_TYPE_QUAD_ADDR == spi->read->iftype)
		return 1;

	return 0;
}

/*****************************************************************************/
/*
  enable QE bit if QUAD read write is supported by SPI
*/
static int spi_general_quad_enable(struct hifmc_spi *spi)
{
	unsigned char status, config, op;
	u32 regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	op = hifmc100_iftype_quad_support(spi);

	config = spi_general_get_config_register(spi);

	if ((config & SPI_NOR_CR_QE_MASK) >> SPI_NOR_CR_QE_SHIFT == op)
		return op;

	status = spi_general_get_status_register(spi);

	spi->driver->write_enable(spi);

	if (op)
		config |= SPI_NOR_CR_QE_MASK;
	else
		config &= ~SPI_NOR_CR_QE_MASK;

	writeb(status, host->iobase);
	writeb(config, host->iobase + SPI_NOR_SR_LEN);

	hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_WRSR), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, 
		    HIFMC100_DATA_NUM_CNT(SPI_NOR_SR_LEN + SPI_NOR_CR_LEN), 
		    HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_WRITE_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	spi->driver->wait_ready(spi);

	config = spi_general_get_config_register(spi);
	if ((config & SPI_NOR_CR_QE_MASK) >> SPI_NOR_CR_QE_SHIFT != op)
		PR_OUT("Config QE failed: controler %s, but spi nor %s\n", 
			op ? "enabled" : "disabled",
			(config & SPI_NOR_CR_QE_MASK) >> SPI_NOR_CR_QE_SHIFT ? 
			 "enabled" : "disabled");
	return op;
}

/*****************************************************************************/
/*
  some chip don't QUAD enable
*/
static int spi_do_not_quad_enable(struct hifmc_spi *spi)
{
	return 0;
}

