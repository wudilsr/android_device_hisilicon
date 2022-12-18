/******************************************************************************
 *    Copyright (c) 2009-2010 by Hisilicon
 *    All rights reserved.
 ******************************************************************************/

/*****************************************************************************/
#include <common.h>
#include <malloc.h>
#include <asm/io.h>
#include <spi_flash.h>
#include <linux/mtd/mtd.h>
#include <asm/errno.h>
#include <asm/arch/platform.h>

#include <hifmcv100_reg.h>
#include "../spi_ids.h"
#include "hifmc100.h"

/*****************************************************************************/
static struct hifmc_host fmc_host;
static struct mtd_info_ex spi_info_ex = {.type = 0, };

#ifdef CONFIG_ARCH_HI3716MV410
	#include "hifmc100_hi3716mv410.c"
#endif

extern int get_boot_media(void);

/*****************************************************************************/
#ifdef CONFIG_HIFMC100_SHOW_CYCLE_TIMING
static char *hifmc100_get_ifcycle_str(int ifcycle)
{
	static char *ifcycle_str[] = {
		"single",
		"dual",
		"dual-addr",
		"quad",
		"quad-addr",
		"unknown",
		"unknown",
		"unknown"
	};

	return ifcycle_str[(ifcycle & 0x07)];
}
#endif /* CONFIG_HISFC350_SHOW_CYCLE_TIMING */

/*****************************************************************************/
static void debug_register_dump(void)
{
	int ix;
	unsigned int regbase = CONFIG_HIFMC100_REG_BASE_ADDRESS;

	printf("Register dump:");
	for (ix = 0; ix <= 0x98; ix += 0x04) {
		if (!(ix & 0x0F))
			printf("\n0x%08X: ", (regbase + ix));
		printf("%08X ", readl(regbase + ix));
	}
	printf("\n");
}

/*****************************************************************************/
/* 
 * set controler to 3B/4B mode.
 * enable: 1->4B; 0->3B
 */
static void hifmc100_set_host_addr_mode(struct hifmc_host *host, int enable)
{
	unsigned int regval = hifmc_read(host, HIFMC100_CFG);

	if (enable)
		regval |= HIFMC100_SPI_NOR_ADDR_MODE_MASK;
	else
		regval &= ~HIFMC100_SPI_NOR_ADDR_MODE_MASK;

	hifmc_write(host, regval, HIFMC100_CFG);
}

/*****************************************************************************/
static void hifmc100_shutdown(void)
{
	int ix;
	struct hifmc_host *host = &fmc_host;
	struct hifmc_spi *spi = host->spi;
	u32 regval = hifmc_read(host, HIFMC100_CFG);

	if (regval & HIFMC100_SPI_NOR_ADDR_MODE_MASK && IS_SPI_NOR_4B(host))
		return;

	for (ix = 0; ix < host->num_chip; ix++, spi++) {
		spi->driver->wait_ready(spi);
		spi->driver->entry_4addr(spi, DISABLE);
	}
}

/*****************************************************************************/
static void hifmc100_map_iftype_and_clock(struct hifmc_spi *spi)
{
	int ix;
	const int iftype_read[] = {
		SPI_IF_READ_STD,       HIFMC100_IF_TYPE_STD,
		SPI_IF_READ_FAST,      HIFMC100_IF_TYPE_STD,
		SPI_IF_READ_DUAL,      HIFMC100_IF_TYPE_DUAL,
		SPI_IF_READ_DUAL_ADDR, HIFMC100_IF_TYPE_DUAL_ADDR,
		SPI_IF_READ_QUAD,      HIFMC100_IF_TYPE_QUAD,
		SPI_IF_READ_QUAD_ADDR, HIFMC100_IF_TYPE_QUAD_ADDR,
		0, 0,
	};
	const int iftype_write[] = {
		SPI_IF_WRITE_STD,       HIFMC100_IF_TYPE_STD,
		SPI_IF_WRITE_DUAL,      HIFMC100_IF_TYPE_DUAL,
		SPI_IF_WRITE_DUAL_ADDR, HIFMC100_IF_TYPE_DUAL_ADDR,
		SPI_IF_WRITE_QUAD,      HIFMC100_IF_TYPE_QUAD,
		SPI_IF_WRITE_QUAD_ADDR, HIFMC100_IF_TYPE_QUAD_ADDR,
		0, 0,
	};

	for (ix = 0; iftype_write[ix]; ix += 2) {
		if (spi->write->iftype == iftype_write[ix]) {
			spi->write->iftype = iftype_write[ix + 1];
			break;
		}
	}
	hifmc100_spi_nor_get_best_clock(&spi->write->clock);

	for (ix = 0; iftype_read[ix]; ix += 2) {
		if (spi->read->iftype == iftype_read[ix]) {
			spi->read->iftype = iftype_read[ix + 1];
			break;
		}
	}
	hifmc100_spi_nor_get_best_clock(&spi->read->clock);

	hifmc100_spi_nor_get_best_clock(&spi->erase->clock);

	spi->erase->iftype = HIFMC100_IF_TYPE_STD;
}

/*****************************************************************************/
static void hifmc100_dma_transfer(struct hifmc_host *host,
				  unsigned int spi_start_addr, 
				  unsigned char *dma_buffer,
				  unsigned char rw_op, unsigned int size)
{
	unsigned char if_type = 0, dummy = 0;
	u32 regval;
	struct hifmc_spi *spi = host->spi;

	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	hifmc_write(host, spi_start_addr, HIFMC100_ADDRL);

	if (rw_op == HIFMC100_RW_OP_WRITE) {
		if_type = spi->write->iftype;
		dummy = spi->write->dummy;
	} else if (rw_op == HIFMC100_RW_OP_READ) {
		if_type = spi->read->iftype;
		dummy = spi->read->dummy;
	}

	regval = HIFMC100_OP_CFG_FM_CS(spi->chipselect)
		| HIFMC100_OP_CFG_MEM_IF_TYPE(if_type)
		| HIFMC100_OP_CFG_ADDR_NUM(HIFMC100_STD_OP_ADDR_NUM)
		| HIFMC100_OP_CFG_DUMMY_NUM(dummy);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_DMA_LEN_SET(size), HIFMC100_DMA_LEN);

	hifmc_write(host, (unsigned int)dma_buffer, HIFMC100_DMA_SADDR_D0);

	regval = HIFMC100_OP_CTRL_RD_OPCODE(spi->read->cmd)
		| HIFMC100_OP_CTRL_WR_OPCODE(spi->write->cmd)
		| HIFMC100_OP_CTRL_RW_OP(rw_op)
		| HIFMC100_OP_CTRL_DMA_OP_READY;
	hifmc_write(host, regval, HIFMC100_OP_CTRL);

	FMC_DMA_WAIT_INT_FINISH(host);
}

/*****************************************************************************/
#ifdef HIFMC100_SPI_NOR_SUPPORT_REG_READ
static char *hifmc100_reg_read_buf(struct hifmc_host *host,
	struct hifmc_spi *spi, unsigned int spi_start_addr,
	unsigned int size, unsigned char *buffer)
{
	u32 regval;

	if (size > HIFMC100_OP_MAX_SIZE)
		DBG_BUG("reg read out of reg range.\n");


	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	hifmc_write(host, HIFMC100_CMD_CMD1(spi->read->cmd), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect)
			  | HIFMC100_OP_CFG_MEM_IF_TYPE(spi->read->iftype)
			  | HIFMC100_OP_CFG_ADDR_NUM(HIFMC100_STD_OP_ADDR_NUM)
			  | HIFMC100_OP_CFG_DUMMY_NUM(spi->read->dummy), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, spi_start_addr, HIFMC100_ADDRL);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(size), HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_DUMMY_EN(ENABLE) 
		| HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_ADDR_EN(ENABLE)
		| HIFMC100_OP_READ_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	memcpy(buffer, host->iobase, size);

	return buffer;
}

/*****************************************************************************/
static int hifmc100_reg_read(struct spi_flash *spiflash, u32 from,
	size_t len, void *buf)
{
	int num;
	int result = -EIO;
	unsigned char *ptr = (unsigned char *)buf;
	struct hifmc_host *host = SPIFLASH_TO_HOST(spiflash);
	struct hifmc_spi *spi = host->spi;

	if ((from + len) > spiflash->size) {
		DBG_MSG("read area out of range.\n");
		return -EINVAL;
	}

	if (!len) {
		DBG_MSG("read length is 0.\n");
		return 0;
	}

	if (spi->driver->wait_ready(spi)) {
		DBG_MSG("ERROR: Dma read wait ready fail!\n");
		return -EBUSY;
	}

	host->set_system_clock(host, spi->read, ENABLE);

	while (len > 0) {
		while (from >= spi->chipsize) {
			from -= spi->chipsize;
			spi++;
			if (!spi->name)
				DBG_BUG("read memory out of range.\n");
			if (spi->driver->wait_ready(spi))
				goto fail;
			host->set_system_clock(host, spi->read, ENABLE);
		}

		num = ((from + len) >= spi->chipsize) ? \
				(spi->chipsize - from) : len;

		while (num >= HIFMC100_OP_MAX_SIZE) {
			hifmc100_reg_read_buf(host, spi,
				from, HIFMC100_OP_MAX_SIZE, ptr);
			ptr  += HIFMC100_OP_MAX_SIZE;
			from += HIFMC100_OP_MAX_SIZE;
			len  -= HIFMC100_OP_MAX_SIZE;
			num  -= HIFMC100_OP_MAX_SIZE;
		}

		if (num) {
			hifmc100_reg_read_buf(host, spi,
				from, num, ptr);
			from += num;
			ptr  += num;
			len  -= num;
		}
	}
	result = 0;
fail:

	return result;
}
#endif /* HIFMC100_SPI_NOR_SUPPORT_REG_READ */

/*****************************************************************************/
static int hifmc100_dma_read(struct spi_flash *spiflash, u32 from, size_t len,
			     void *buf)
{
	int num;
	unsigned char *ptr = (unsigned char *)buf;
	struct hifmc_host *host = SPIFLASH_TO_HOST(spiflash);
	struct hifmc_spi *spi = host->spi;

	if ((from + len) > spiflash->size) {
		DBG_MSG("read area out of range.\n");
		return -EINVAL;
	}

	if (!len) {
		DBG_MSG("read length is 0.\n");
		return 0;
	}

	if (spi->driver->wait_ready(spi)) {
		DBG_MSG("ERROR: Dma read wait ready fail!\n");
		return -EBUSY;
	}

	host->set_system_clock(host, spi->read, ENABLE);

	while (len > 0) {
		while (from >= spi->chipsize) {
			from -= spi->chipsize;
			spi++;
			if (!spi->name)
				DBG_BUG("read memory out of range.\n");
		}

		num = ((from + len) >= spi->chipsize)
			? (spi->chipsize - from) : len;
		while (num >= HIFMC100_DMA_MAX_SIZE) {
			hifmc100_dma_transfer(host, from,
				(unsigned char *)host->dma_buffer, 
				HIFMC100_RW_OP_READ,
				HIFMC100_DMA_MAX_SIZE);
			memcpy(ptr, host->buffer, HIFMC100_DMA_MAX_SIZE);
			ptr  += HIFMC100_DMA_MAX_SIZE;
			from += HIFMC100_DMA_MAX_SIZE;
			len  -= HIFMC100_DMA_MAX_SIZE;
			num  -= HIFMC100_DMA_MAX_SIZE;
		}

		if (num) {
			hifmc100_dma_transfer(host, from,
					(unsigned char *)host->dma_buffer,
					 HIFMC100_RW_OP_READ, num);
			memcpy(ptr, host->buffer, num);
			from += num;
			ptr  += num;
			len  -= num;
		}
	}

	return 0;
}

/*****************************************************************************/
static void hifmc100_read_ids(struct hifmc_host *host,
			unsigned char chipselect, unsigned char *buffer)
{
	u32 regval;

	hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_RDID), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(chipselect), HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(READ_ID_LEN), 
		    HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_READ_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	memcpy(buffer, host->iobase, READ_ID_LEN);
}

/*****************************************************************************/
static int hifmc100_reg_erase_one_block(struct hifmc_host *host,
	struct hifmc_spi *spi, unsigned int offset)
{
	unsigned int regval;

	regval = spi->driver->wait_ready(spi);
	if (regval) {
		DBG_MSG("Erase wait ready fail! status[%#x]\n", regval);
		return 1;
	}

	spi->driver->write_enable(spi);

	host->set_system_clock(host, spi->erase, ENABLE);

	hifmc_write(host, HIFMC100_CMD_CMD1(spi->erase->cmd), HIFMC100_CMD);

	hifmc_write(host, offset, HIFMC100_ADDRL);

	regval = HIFMC100_OP_CFG_FM_CS(spi->chipselect)
		| HIFMC100_OP_CFG_MEM_IF_TYPE(spi->erase->iftype)
		| HIFMC100_OP_CFG_ADDR_NUM(HIFMC100_STD_OP_ADDR_NUM)
		| HIFMC100_OP_CFG_DUMMY_NUM(spi->erase->dummy);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_ADDR_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	return 0;
}

/*****************************************************************************/
static int hifmc100_dma_write(struct spi_flash *spiflash, u32 to, size_t len,
	const void *buf)
{
	int num;
	int result = -EIO;

	unsigned char *ptr = (unsigned char *)buf;
	struct hifmc_host *host = SPIFLASH_TO_HOST(spiflash);
	struct hifmc_spi *spi = host->spi;

	if ((to + len) > spiflash->size) {
		DBG_MSG("write data out of range.\n");
		return -EINVAL;
	}

	if (!len) {
		DBG_MSG("write length is 0.\n");
		return 0;
	}

	if (spi->driver->wait_ready(spi))
		goto fail;

	spi->driver->write_enable(spi);

	host->set_system_clock(host, spi->write, ENABLE);

	if (to & HIFMC100_DMA_MAX_MASK) {
		num = HIFMC100_DMA_MAX_SIZE - (to & HIFMC100_DMA_MAX_MASK);
		if (num > len)
			num = len;
		while (to >= spi->chipsize) {
			to -= spi->chipsize;
			spi++;
			if (!spi->name)
				DBG_BUG("write memory out of range.\n");

			if (spi->driver->wait_ready(spi))
				goto fail;

			spi->driver->write_enable(spi);

			host->set_system_clock(host, spi->write, ENABLE);
		}
		memcpy(host->buffer, ptr, num);
		hifmc100_dma_transfer(host, to,
			(unsigned char *)host->dma_buffer, HIFMC100_RW_OP_WRITE, num);

		to  += num;
		ptr += num;
		len -= num;
	}

	while (len > 0) {
		num = ((len >= HIFMC100_DMA_MAX_SIZE)
			? HIFMC100_DMA_MAX_SIZE : len);
		while (to >= spi->chipsize) {
			to -= spi->chipsize;
			spi++;
			if (!spi->name)
				DBG_BUG("write memory out of range.\n");

			if (spi->driver->wait_ready(spi))
				goto fail;

			spi->driver->write_enable(spi);

			host->set_system_clock(host, spi->write, ENABLE);
		}

		memcpy(host->buffer, ptr, num);
		hifmc100_dma_transfer(host, to,
			(unsigned char *)host->dma_buffer, 
			 HIFMC100_RW_OP_WRITE, num);

		to  += num;
		ptr += num;
		len -= num;
	}

	result = 0;
fail:
	return result;
}

/*****************************************************************************/
#ifdef HIFMC100_SPI_NOR_SUPPORT_REG_WRITE
static int hifmc100_reg_write_buf(struct hifmc_host *host,
		struct hifmc_spi *spi, u32 spi_start_addr,
	size_t size, unsigned char *buffer)
{
	unsigned int regval;
	if (size > HIFMC100_OP_MAX_SIZE)
		DBG_BUG("reg read out of reg range.\n");

	if (spi->driver->wait_ready(spi))
		return 1;

	spi->driver->write_enable(spi);

	memcpy((char *)host->iobase, buffer, size);

	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	hifmc_write(host, HIFMC100_CMD_CMD1(spi->write->cmd), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(spi->chipselect)
			  | HIFMC100_OP_CFG_MEM_IF_TYPE(spi->write->iftype)
			  | HIFMC100_OP_CFG_ADDR_NUM(HIFMC100_STD_OP_ADDR_NUM)
			  | HIFMC100_OP_CFG_DUMMY_NUM(spi->write->dummy), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, spi_start_addr, HIFMC100_ADDRL);
	
	regval = HIFMC100_OP_CMD1_EN(ENABLE) 
		| HIFMC100_OP_ADDR_EN(ENABLE)
		| HIFMC100_OP_WRITE_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_DMA_WAIT_CPU_FINISH(host);

	return 0;
}

/*****************************************************************************/
static int hifmc100_reg_write(struct spi_flash *spiflash, u32 to, size_t len,
	const void *buf)
{
	int num;
	int result = -EIO;
	unsigned char *ptr = (unsigned char *)buf;
	struct hifmc_host *host = SPIFLASH_TO_HOST(spiflash);
	struct hifmc_spi *spi = host->spi;

	if ((to + len) > spiflash->size) {
		DBG_MSG("write data out of range.\n");
		return -EINVAL;
	}

	if (!len) {
		DBG_MSG("write length is 0.\n");
		return 0;
	}

	if (spi->driver->wait_ready(spi))
		goto fail;

	host->set_system_clock(host, spi->write, ENABLE);

	if (to & HIFMC100_OP_MAX_MASK) {
		num = HIFMC100_OP_MAX_SIZE - (to & HIFMC100_OP_MAX_MASK);
		if (num > (int)len)
			num = (int)len;

		while (to >= spi->chipsize) {
			to -= spi->chipsize;
			spi++;
			if (!spi->name)
				DBG_BUG("write memory out of range.\n");

			if (spi->driver->wait_ready(spi))
				goto fail;

			host->set_system_clock(host, spi->write, ENABLE);
		}

		if (hifmc100_reg_write_buf(host, spi, to, num, ptr))
			goto fail;

		to  += num;
		ptr += num;
		len -= num;
	}

	while (len > 0)	{
		num = ((len >= HIFMC100_OP_MAX_SIZE) ?
				HIFMC100_OP_MAX_SIZE : len);
		while (to >= spi->chipsize) {
			to -= spi->chipsize;
			spi++;
			if (!spi->name)
				DBG_BUG("write memory out of range.\n");

			if (spi->driver->wait_ready(spi))
				goto fail;
			host->set_system_clock(host, spi->write, ENABLE);
		}
		if (hifmc100_reg_write_buf(host, spi, to, num, ptr))
			goto fail;
		to  += num;
		ptr += num;
		len -= num;
	}
fail:
	return 0;
}
#endif /* HIFMC100_SPI_NOR_SUPPORT_REG_WRITE */

/*****************************************************************************/
static int hifmc100_reg_erase(struct spi_flash *spiflash, u32 offset,
	size_t length)
{
	struct hifmc_host *host = SPIFLASH_TO_HOST(spiflash);
	struct hifmc_spi *spi = host->spi;

	if (offset + length > spiflash->size) {
		DBG_MSG("erase area out of range of mtd.\n");
		return -EINVAL;
	}

	if (offset & (host->erasesize - 1)) {
		DBG_MSG("erase start address is not alignment.\n");
		return -EINVAL;
	}

	if (length & (host->erasesize - 1)) {
		DBG_MSG("erase length is not alignment.\n");
		return -EINVAL;
	}

	while (length) {
		if (spi->chipsize <= offset) {
			offset -= spi->chipsize;
			spi++;
			if (!spi->name)
				DBG_BUG("erase memory out of range.\n");
		}

		if (hifmc100_reg_erase_one_block(host, spi, offset))
			return -1;

		offset += spi->erase->size;
		length -= spi->erase->size;
	}

	return 0;
}

/*****************************************************************************/
static int hifmc100_check_addr_mode(struct hifmc_host *host)
{
	u32 regval = hifmc_read(host, HIFMC100_CFG);

	if (regval & HIFMC100_SPI_NOR_ADDR_MODE_MASK && !IS_SPI_NOR_4B(host)) {
		printf("hardware config addr mode is 4B, "
			"but spi nor is not 4B addr mode only.\n");
		return -1;		
	} else if (!(regval & HIFMC100_SPI_NOR_ADDR_MODE_MASK) 
		   && IS_SPI_NOR_4B(host)) {
		printf("hardware config addr mode is 3B, "
			"but spi nor support 4B addr mode only.\n");
		return -1;
	}

	return 0;
}
/*****************************************************************************/

static void hifmc100_show_spi(struct hifmc_spi *spi)
{
	printf("Spi(cs%d): ", spi->chipselect);
	printf("Block:%sB ",  ultohstr((unsigned long long)spi->erasesize));
	printf("Chip:%sB ",   ultohstr(spi->chipsize));
	printf("Name:\"%s\"\n", spi->name);

#ifdef CONFIG_HIFMC100_SHOW_CYCLE_TIMING
	printf("Spi(cs%d): ", spi->chipselect);
	if (spi->addrcycle == 4)
		printf("4 addrcycle ");
	printf("read:%s,%02X,%s ",
		hifmc100_get_ifcycle_str(spi->read->iftype),
		spi->read->cmd,
		hifmc100_get_clock_str(spi->read->clock));
	printf("write:%s,%02X,%s ",
		hifmc100_get_ifcycle_str(spi->write->iftype),
		spi->write->cmd,
		hifmc100_get_clock_str(spi->write->clock));
	printf("erase:%s,%02X,%s\n",
		hifmc100_get_ifcycle_str(spi->erase->iftype),
		spi->erase->cmd,
		hifmc100_get_clock_str(spi->erase->clock));
#endif /* CONFIG_HIFMC100_SHOW_CYCLE_TIMING */
}
/*****************************************************************************/
static int hifmc100_spi_probe(struct hifmc_host *host)
{
	unsigned int total = 0;
	unsigned char ids[READ_ID_LEN], chipselect = 0;
	struct spi_info *spiinfo;
	struct hifmc_spi *spi = host->spi;

	host->num_chip = 0;

	for (; chipselect < CONFIG_HIFMC100_SPI_NOR_CHIP_NUM; chipselect++) {

		hifmc100_read_ids(host, chipselect, ids);

		/* can't find spi flash device. */
		if (!(ids[0] | ids[1] | ids[2])
			|| ((ids[0] & ids[1] & ids[2]) == 0xFF))
			continue;

		printf("Spi(cs%d) ID: 0x%02X 0x%02X 0x%02X" \
				" 0x%02X 0x%02X 0x%02X\n", chipselect,
				ids[0], ids[1], ids[2], ids[3], ids[4], ids[5]);

		spiinfo = spi_serach_ids(hifmc100_spi_info_table, ids);

		if (!spiinfo) {
			printf("Spi(cs%d): find unrecognized spi flash.\n",
				chipselect);
			continue;
		}

		spi->name = spiinfo->name;
		spi->chipselect = chipselect;
		spi->chipsize   = spiinfo->chipsize;
		spi->erasesize  = spiinfo->erasesize;
		spi->addrcycle  = spiinfo->addrcycle;
		spi->driver     = spiinfo->driver;
		host->flags     = spiinfo->flags;

		spi->host       = host;
		spi->iobase = (char *)host->iobase + total;

		spi->driver->quad_enable(spi);

		spi_search_rw(spiinfo, spi->read,
			HIFMC100_SPI_NOR_SUPPORT_READ,
			HIFMC100_SPI_NOR_SUPPORT_MAX_DUMMY, READ);

		spi_search_rw(spiinfo, spi->write,
			HIFMC100_SPI_NOR_SUPPORT_WRITE,
			HIFMC100_SPI_NOR_SUPPORT_MAX_DUMMY, WRITE);

		spi_get_erase(spiinfo, spi->erase);
		hifmc100_map_iftype_and_clock(spi);

		/* auto check sfc_addr_mode 3 bytes or 4 bytes */
		hifmc100_check_addr_mode(host);
		if (spi->addrcycle == 4)
			spi->driver->entry_4addr(spi, ENABLE);

		hifmc100_show_spi(spi);

		if (spi_info_ex.type == 0) {
			spi_info_ex.type      = MTD_NORFLASH;
			spi_info_ex.chipsize  = spi->chipsize;
			spi_info_ex.erasesize = spi->erasesize;
			spi_info_ex.pagesize  = 1;
			spi_info_ex.addrcycle = spi->addrcycle;

			if (spiinfo->id_len > sizeof(spi_info_ex.ids)) {
				printf("BUG! ID len out of range.\n");
				BUG();
			}

			spi_info_ex.id_length = spiinfo->id_len;
			memcpy(spi_info_ex.ids, spiinfo->id,
					spiinfo->id_len);

			strncpy(spi_info_ex.name, spi->name,
					sizeof(spi_info_ex.name));
			spi_info_ex.name[sizeof(spi_info_ex.name) - 1]
				= '\0';
		}

		host->num_chip++;
		total += spi->chipsize;
		spi++;
	}

	spi_info_ex.numchips = host->num_chip;

	return host->num_chip;
}

/*****************************************************************************/
static int hifmc100_probe(struct hifmc_host *host)
{
	struct spi_flash *spiflash = host->spiflash;

	host->set_system_clock(host, NULL, ENABLE);
	hifmc_write(host,
		HIFMC100_TIMING_SPI_CFG_TCSH(HIFMC100_CS_HOLD_TIME)
		| HIFMC100_TIMING_SPI_CFG_TCSS(HIFMC100_CS_SETUP_TIME)
		| HIFMC100_TIMING_SPI_CFG_TSHSL(HIFMC100_CS_DESELECT_TIME), 
		HIFMC100_TIMING_SPI_CFG);

	if (!hifmc100_spi_probe(host))
		return -1;

	spiflash->erase = hifmc100_reg_erase;
#ifdef HIFMC100_SPI_NOR_SUPPORT_REG_WRITE
	spiflash->write = hifmc100_reg_write;
#else
	spiflash->write = hifmc100_dma_write;
#endif

#ifdef HIFMC100_SPI_NOR_SUPPORT_REG_READ
	spiflash->read  = hifmc100_reg_read;
#else
	spiflash->read  = hifmc100_dma_read;
#endif
	return 0;
}

/*****************************************************************************/
static void hifmc_probe_spi_size(struct hifmc_host *host,
		struct spi_flash *spiflash)
{
	int ix = 1;
	struct hifmc_spi *spi = host->spi;
	int total = spi->chipsize;
	int erasesize = spi->erasesize;

	for (++spi; ix < host->num_chip; ix++, spi++)
		total += spi->chipsize;

	spiflash->size = total;
	host->erasesize = erasesize;
}

/*****************************************************************************/
static struct spi_flash *hifmc100_init(void)
{
	u32 regval, flash_type;
	struct hifmc_host *host = &fmc_host;
	static struct spi_flash *spiflash;

	if (spiflash)
		return spiflash;

	memset(host, 0, sizeof(struct hifmc_host));
	memset(&spi_info_ex, 0, sizeof(struct mtd_info_ex));

	host->iobase = (void *)CONFIG_HIFMC100_BUFFER_BASE_ADDRESS;
	host->regbase  = (void *)CONFIG_HIFMC100_REG_BASE_ADDRESS;

	regval = hifmc_read(host, HIFMC100_CFG);
	flash_type = (regval & HIFMC100_FLASH_SEL_MASK) 
		      >> HIFMC100_FLASH_SEL_SHIFT;
	if (flash_type != HIFMC100_FLASH_TYPE_SPI_NOR) {
		printf("ERROR: Flash type[%d] check failed!\n", flash_type);
		return NULL;
	}

	if ((regval & HIFMC100_OP_MODE_MASK) == HIFMC100_OP_MODE_BOOT)
		regval |= HIFMC100_CFG_OP_MODE(HIFMC100_OP_MODE_NORMAL);

	hifmc_write(host, regval, HIFMC100_CFG);

	/* enable lp control. */
	regval = hifmc_read(host, HIFMC100_LP_CTRL);
	regval |= HIFMC100_CLK_GATE_EN;
	hifmc_write(host, regval, HIFMC100_LP_CTRL);

	host->dma_buffer = (unsigned int)host->buffer;
	host->set_system_clock = hifmc100_set_spi_nor_system_clock;
	host->set_host_addr_mode = hifmc100_set_host_addr_mode;

	spiflash = host->spiflash;

	spiflash->name = "hi_fmc";

	if (hifmc100_probe(host)) {
		printf("Can't find a valid spi nor flash chip.\n");
		if (spiflash)
			spiflash = NULL;
		return NULL;
	}

	hifmc_probe_spi_size(host, spiflash);

	add_shutdown(hifmc100_shutdown);

	return spiflash;
}

/*****************************************************************************/
static struct mtd_info_ex *hifmc100_getinfo(void)
{
	if (spi_info_ex.type == 0) {
		if (hifmc100_init() == NULL)
			return NULL;
	}
	return &spi_info_ex;
}

/*****************************************************************************/
static int hifmc100_version_check(void)
{
	u32 regval;
	regval = readl(CONFIG_HIFMC100_REG_BASE_ADDRESS + HIFMC100_VERSION);
	return (regval == HIFMC_VER_100);
}

/*****************************************************************************/
int hifmc100_spiflash_init(struct spi_flash **spiflash,
				struct mtd_info_ex **spiinfo)
{
	/* hifmc flash type check */
	if (get_boot_media() != BOOT_MEDIA_SPIFLASH)
		return -ENODEV;

	/* hifmc ip version check */
	printf("SPI Nor Check Flash Memory Controller v100 ... ");
	if (!hifmc100_version_check()) {
		printf("\n");
		return -ENODEV;
	}
	printf("Found\n");

	(*spiflash) = hifmc100_init();
	(*spiinfo) = hifmc100_getinfo();

	return 1;
}

