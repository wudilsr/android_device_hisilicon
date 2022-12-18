/******************************************************************************
*    Copyright (c) 2009-2012 by Hisi.
*    All rights reserved.
******************************************************************************/
#include "hifmc100_os.h"
#include "hifmc100.h"

/* MXIC QE(bit) include in Status Register */
#define MX_SPI_NOR_SR_QE_SHIFT	6
#define MX_SPI_NOR_SR_QE_MASK	(1 << MX_SPI_NOR_SR_QE_SHIFT)

/*
   enable QE bit if QUAD read write is supported by MXIC "25L25635E" SPI
*/
static int spi_mx25l25635e_quad_enable(struct hifmc_spi *spi)
{
	unsigned char status, op;
	u32 regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	op = hifmc100_iftype_quad_support(spi);

	status = spi_general_get_status_register(spi);

	if ((status & MX_SPI_NOR_SR_QE_MASK) >> MX_SPI_NOR_SR_QE_SHIFT == op)
		return op;

	spi->driver->write_enable(spi);

	if (op)
		status |= MX_SPI_NOR_SR_QE_MASK;
	else
		status &= ~MX_SPI_NOR_SR_QE_MASK;

	writeb(status, host->iobase);

	hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_WRSR), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(SPI_NOR_SR_LEN), 
		    HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_WRITE_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	spi->driver->wait_ready(spi);

	status = spi_general_get_status_register(spi);
	if ((status & MX_SPI_NOR_SR_QE_MASK) >> MX_SPI_NOR_SR_QE_SHIFT != op)
		PR_OUT("Config QE failed: controler %s, but spi nor %s\n", 
			op ? "enabled" : "disabled",
			(status & MX_SPI_NOR_SR_QE_MASK) 
			 >> MX_SPI_NOR_SR_QE_SHIFT ? 
			 "enabled" : "disabled");
	return op;
}
