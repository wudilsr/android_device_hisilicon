/******************************************************************************
*    Copyright (c) 2009-2012 by Hisi.
*    All rights reserved.
******************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100.h"

/* SpanSion SPI Nor Flash "S25FL256S" Bank Address Register command */
#define SS_SPI_CMD_BRRD			0x16	/* Read Bank Register */
#define SS_SPI_CMD_BRWR			0x17	/* Write Bank Register */

/* Bank Address Register length(byte) */
#define SS_SPI_NOR_BR_LEN		1

/* Extended Address Enable bit[7] include in Bank Address Register */
#define SS_SPI_NOR_BR_EAE_SHIFT	7
#define SS_SPI_NOR_BR_EAE_MASK	(1 << SS_SPI_NOR_BR_EAE_SHIFT)

/*
  enable 4byte address mode for s25fl256
*/
static int spi_s25fl256s_entry_4addr(struct hifmc_spi *spi, int enable)
{
	unsigned char bank;
	unsigned int regval;
	struct hifmc_host *host = (struct hifmc_host *)spi->host;

	if (spi->addrcycle != SPI_4BYTE_ADDR_LEN)
		return 0;

	/* Read old Bank Register value */
	hifmc_write(host, HIFMC100_CMD_CMD1(SS_SPI_CMD_BRRD), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(SS_SPI_NOR_BR_LEN), 
		    HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_READ_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	bank = readb(host->iobase);
	if (((bank & SS_SPI_NOR_BR_EAE_MASK) >> SS_SPI_NOR_BR_EAE_SHIFT) \
		== enable)
		return 0;

	/* Write new Bank Register value */
	hifmc_write(host, HIFMC100_CMD_CMD1(SS_SPI_CMD_BRWR), HIFMC100_CMD);
	/*
	  when enable == 1 enable 4byte address
	  when enable == 0 change address mode from 4byte to 3byte, for reset
	*/
	if (enable)
		bank |= SS_SPI_NOR_BR_EAE_MASK;
	else
		bank &= ~SS_SPI_NOR_BR_EAE_MASK;

	writeb(bank, host->iobase);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(SS_SPI_NOR_BR_LEN), 
		    HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_WRITE_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	/* Check out Bank Register value */
	hifmc_write(host, HIFMC100_CMD_CMD1(SS_SPI_CMD_BRRD), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(SS_SPI_NOR_BR_LEN), 
		    HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_READ_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	bank = readb(host->iobase);
	if (((bank & SS_SPI_NOR_BR_EAE_MASK) >> \
		SS_SPI_NOR_BR_EAE_SHIFT) != enable)
		PR_OUT("ERROR: %s 4 bytes mode failed! bank[%#x]\n",
			enable ? "enter" : "exit", bank);
	else
		host->set_host_addr_mode(host, enable);

	return 0;
}

