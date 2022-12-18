/******************************************************************************
*    Copyright (c) 2009-2012 by Hisi.
*    All rights reserved.
******************************************************************************/
#include "hifmc100_os.h"
#include "hifmc100.h"

#define SPI_CMD_FIRST_RESET_4ADDR  (0x66)
#define SPI_CMD_SECOND_RESET_4ADDR (0x99)

static int spi_w25q256fv_entry_4addr(struct hifmc_spi *spi, int enable)
{
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	if (spi->addrcycle != SPI_4BYTE_ADDR_LEN)
		return 0;

	/* This chip should not write enable here,
	 * we have confirmed with the WINBOND */
	/* spi->driver->write_enable(spi); */

	if (enable) {
		hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_EN4B), HIFMC100_CMD);

		hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect),
			    HIFMC100_OP_CFG);

		hifmc_write(host, HIFMC100_OP_CMD1_EN(ENABLE) 
				  | HIFMC100_OP_REG_OP_START,
			    HIFMC100_OP);

		FMC_CMD_WAIT_CPU_FINISH(host);
	} else {
		/* reset cmd */
		hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_FIRST_RESET_4ADDR), 
			    HIFMC100_CMD);

		hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect),
			    HIFMC100_OP_CFG);

		hifmc_write(host, HIFMC100_OP_CMD1_EN(ENABLE)
				  | HIFMC100_OP_REG_OP_START,
			    HIFMC100_OP);

		FMC_CMD_WAIT_CPU_FINISH(host);

		hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_SECOND_RESET_4ADDR),
			    HIFMC100_CMD);

		hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
			    HIFMC100_OP_CFG);

		hifmc_write(host, HIFMC100_OP_CMD1_EN(ENABLE)
				  | HIFMC100_OP_REG_OP_START,
			    HIFMC100_OP);

		FMC_CMD_WAIT_CPU_FINISH(host);
	}

	host->set_host_addr_mode(host, enable);

	return 0;
}

