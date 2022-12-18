/******************************************************************************
*    Copyright (c) 2009-2012 by Hisi.
*    All rights reserved.
******************************************************************************/
#include "hifmc100_os.h"
#include "hifmc100.h"

/*
   enable QE bit if QUAD read write is supported by GD "25qxxx" and Winbond SPI
*/
static int spi_gd25qxxx_quad_enable(struct hifmc_spi *spi)
{
	unsigned char config, op;
	u32 regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	op = hifmc100_iftype_quad_support(spi);

	config = spi_general_get_config_register(spi);

	if ((config & SPI_NOR_CR_QE_MASK) >> SPI_NOR_CR_QE_SHIFT == op)
		return op;

	spi->driver->write_enable(spi);

	if (op)
		config |= SPI_NOR_CR_QE_MASK;
	else
		config &= ~SPI_NOR_CR_QE_MASK;

	writeb(config, host->iobase);

	/* There is new command for Write status register 2 by GD chio */
	hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_WRSR2), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(SPI_NOR_CR_LEN), 
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

