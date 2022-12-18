/******************************************************************************
 *    Flash Memory Controller v100 Device Driver
 *    Copyright (c) 2014 Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By hisilicon
 *
******************************************************************************/

#include <common.h>
#include <nand.h>
#include <asm/io.h>
#include <asm/errno.h>
#include <malloc.h>
#include <match_table.h>
#include <asm/arch/platform.h>
#include <linux/mtd/nand.h>
#include <hinfc_gen.h>
#include <hifmcv100_reg.h>
#include "hifmc100.h"
#include "../hifmc100_nand_gen.h"

#ifdef CONFIG_ARCH_HI3716MV410
  #include "hifmc100_hi3716mv410.c"
#endif

static struct hifmc_host fmc_host = {
	.chip = NULL,
};

//#define CONFIG_HIFMC100_BULK_READ  /* enable BULK READ MODE support. */
/*****************************************************************************/
static void nand_register_dump(void)
{
	int ix;
	u32 regbase = CONFIG_HIFMC100_REG_BASE_ADDRESS;

	printf("Register dump:");
	for (ix = 0; ix <= 0x98; ix += 0x04) {
		if (!(ix & 0x0F))
			printf("\n0x%08X: ", (regbase + ix));
		printf("%08X ", readl(regbase + ix));
	}
	printf("\n");
}

/*****************************************************************************/
#ifdef HIFMC100_SPI_NAND_SUPPORT_REG_WRITE
static void hifmc100_send_cmd_pageprog(struct hifmc_host *host)
{
	u32 regval;
	struct hifmc_op *spi = host->spi;

	spi->driver->wait_ready(spi);

	if (spi->driver->write_enable(spi))
		return;

	host->set_system_clock(host, spi->write, TRUE);

	hifmc_write(host, host->FMC_CFG, HIFMC100_CFG);

	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(host->chipselect)
			  | HIFMC100_OP_CFG_MEM_IF_TYPE(spi->write->iftype), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, host->addr_value[0] & 0xffff0000, HIFMC100_ADDRL);
	hifmc_write(host, host->addr_value[1], HIFMC100_ADDRH);

	*host->epm = 0x0000;

	regval = HIFMC100_OP_CTRL_WR_OPCODE(spi->write->cmd)
		| HIFMC100_OP_CTRL_DMA_OP(HIFMC100_OP_TYPE_REG)
		| HIFMC100_OP_CTRL_RW_OP(HIFMC100_RW_OP_WRITE)
		| HIFMC100_OP_CTRL_DMA_OP_READY;
	hifmc_write(host, regval, HIFMC100_OP_CTRL);

	FMC_DMA_WAIT_INT_FINISH(host);
}

#else
/*****************************************************************************/

static void hifmc100_send_cmd_pageprog(struct hifmc_host *host)
{
	u32 regval;
	struct hifmc_op *spi = host->spi;

	spi->driver->wait_ready(spi);

	if (spi->driver->write_enable(spi))
		return;

	host->set_system_clock(host, spi->write, TRUE);

	hifmc_write(host, host->FMC_CFG, HIFMC100_CFG);

	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(host->chipselect)
			  | HIFMC100_OP_CFG_MEM_IF_TYPE(spi->write->iftype), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, host->addr_value[0] & 0xffff0000, HIFMC100_ADDRL);
	hifmc_write(host, host->addr_value[1], HIFMC100_ADDRH);

	*host->epm = 0x0000;

	hifmc_write(host, host->dma_buffer, HIFMC100_DMA_SADDR_D0);

	hifmc_write(host, host->dma_oob, HIFMC100_DMA_SADDR_OOB);

	regval = HIFMC100_OP_CTRL_WR_OPCODE(spi->write->cmd)
		| HIFMC100_OP_CTRL_DMA_OP(HIFMC100_OP_TYPE_DMA)
		| HIFMC100_OP_CTRL_RW_OP(HIFMC100_RW_OP_WRITE)
		| HIFMC100_OP_CTRL_DMA_OP_READY;
	hifmc_write(host, regval, HIFMC100_OP_CTRL);

	FMC_DMA_WAIT_INT_FINISH(host);
}
#endif /* HIFMC100_SPI_NAND_SUPPORT_REG_WRITE */
/*****************************************************************************/

#ifdef HIFMC100_SPI_NAND_SUPPORT_REG_READ
static void hifmc100_send_cmd_readstart(struct hifmc_host *host)
{
	unsigned char pages_per_block_shift, only_oob = 0;
	unsigned short wrap = 0;
	u32 regval, block_num, block_num_h, page_num, addr_of = 0;
	struct hifmc_op *spi = host->spi;
	struct nand_chip *chip = host->chip;

	if ((host->addr_value[0] == host->cache_addr_value[0])
	    && (host->addr_value[1] == host->cache_addr_value[1])) {
		return;

	spi->driver->wait_ready(spi);

	host->set_system_clock(host, spi->read, TRUE);

	hifmc_write(host, host->FMC_CFG, HIFMC100_CFG);

	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
		| HIFMC100_OP_CFG_MEM_IF_TYPE(spi->read->iftype)
		| HIFMC100_OP_CFG_DUMMY_NUM(spi->read->dummy);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	pages_per_block_shift = chip->phys_erase_shift - chip->page_shift;
	block_num = host->addr_value[1] >> pages_per_block_shift;
	block_num_h = block_num >> REG_CNT_HIGH_BLOCK_NUM_SHIFT;

	regval = HIFMC100_ADDRH_SET(block_num_h);
	hifmc_write(host, regval, HIFMC100_ADDRH);

	page_num = host->addr_value[1] - (block_num << pages_per_block_shift);
	if (only_oob)
		switch (host->ecctype) {
		case NAND_ECC_8BIT:
			addr_of = REG_CNT_ECC_8BIT_OFFSET;
			break;
		case NAND_ECC_16BIT:
			addr_of = REG_CNT_ECC_16BIT_OFFSET;
			break;
		case NAND_ECC_24BIT:
			addr_of = REG_CNT_ECC_24BIT_OFFSET;
			break;
		case NAND_ECC_NONE:
		default:
			break;
		}

	regval = ((block_num & REG_CNT_BLOCK_NUM_MASK) << REG_CNT_BLOCK_NUM_SHIFT)
		| ((page_num & REG_CNT_PAGE_NUM_MASK) << REG_CNT_PAGE_NUM_SHIFT)
		| ((wrap & REG_CNT_WRAP_MASK) << REG_CNT_WRAP_SHIFT)
		| (addr_of & REG_CNT_ECC_OFFSET_MASK);
	hifmc_write(host, regval, HIFMC100_ADDRL);

	regval = HIFMC100_OP_CTRL_RD_OPCODE(spi->read->cmd)
		| host->cmd_option.op_config
		| HIFMC100_OP_CTRL_DMA_OP(HIFMC100_OP_TYPE_REG)
		| HIFMC100_OP_CTRL_RW_OP(HIFMC100_RW_OP_READ)
		| HIFMC100_OP_CTRL_DMA_OP_READY;
	
	if (host->command == NAND_CMD_READOOB) {
		regval |= HIFMC100_OP_CTRL_RD_OP_SEL(HIFMC100_RD_OP_READ_OOB);
	} else
		regval |= HIFMC100_OP_CTRL_RD_OP_SEL(HIFMC100_RD_OP_READ_ALL_PAGE);

	hifmc_write(host, regval, HIFMC100_OP_CTRL);

	FMC_DMA_WAIT_INT_FINISH(host);

	host->cache_addr_value[0] = host->addr_value[0];
	host->cache_addr_value[1] = host->addr_value[1];
}

#else
/*****************************************************************************/

static void hifmc100_send_cmd_readstart(struct hifmc_host *host)
{
	u32 regval;
	u32 dma_buffer, dma_oob;
	struct hifmc_op *spi = host->spi;
	struct nand_chip *chip = host->chip;
	struct mtd_info  *mtd = host->mtd;

	if ((host->addr_value[0] == host->cache_addr_value[0])
		&& (host->addr_value[1] == host->cache_addr_value[1]))
		return;

	spi->driver->wait_ready(spi);

	host->set_system_clock(host, spi->read, TRUE);

	hifmc_write(host, host->FMC_CFG, HIFMC100_CFG);

	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	hifmc_write(host, host->addr_value[0] & 0xffff0000, HIFMC100_ADDRL);

	hifmc_write(host, host->addr_value[1], HIFMC100_ADDRH);

	if (host->ecctype == NAND_ECC_NONE)
		hifmc_write(host, HIFMC100_DMA_LEN_SET(host->oobsize), 
			    HIFMC100_DMA_LEN);

#ifdef CONFIG_HIFMC100_BULK_READ
	if (chip->ops.rmode.mode == MTD_READ_BULK) {
		if (chip->ops.rmode.pagenum > (host->block_page_mask + 1)) {
			PR_BUG("Bulk read len(0x%x) is invalid, max is 0x%x.\n",
				chip->ops.rmode.pagenum * host->pagesize,
				mtd->erasesize);
		}

		hifmc_write(host, 
			HIFMC100_DMA_BLK_SADDR_SET(chip->ops.rmode.pageoff), 
			HIFMC100_DMA_BLK_SADDR);
		hifmc_write(host, 
			HIFMC100_DMA_BLK_LEN_SET(chip->ops.rmode.pagenum), 
			HIFMC100_DMA_BLK_LEN);
		dma_buffer = (u32)host->cache_read_pagebuf;
		dma_oob    = (u32)host->cache_read_oobbuf;
	} else 
#endif /* CONFIG_HIFMC100_BULK_READ */
#ifdef CONFIG_HIFMC100_CACHE_READ
	if (chip->ops.rmode.mode == MTD_READ_CACHE) {
		PR_BUG("ERROR: Not support cache read mode.\n ");
	} else
#endif /* CONFIG_HIFMC100_CACHE_READ */
	{
		dma_buffer = host->dma_buffer;
		dma_oob = (u32)host->dma_oob;
	}

	hifmc_write(host, dma_buffer, HIFMC100_DMA_SADDR_D0);

	dma_buffer += HIFMC100_DMA_ADDR_OFFSET;
	hifmc_write(host, dma_buffer, HIFMC100_DMA_SADDR_D1);

	dma_buffer += HIFMC100_DMA_ADDR_OFFSET;
	hifmc_write(host, dma_buffer, HIFMC100_DMA_SADDR_D2);

	dma_buffer += HIFMC100_DMA_ADDR_OFFSET;
	hifmc_write(host, dma_buffer, HIFMC100_DMA_SADDR_D3);

	hifmc_write(host, dma_oob, HIFMC100_DMA_SADDR_OOB);


	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
		| HIFMC100_OP_CFG_MEM_IF_TYPE(spi->read->iftype)
		| HIFMC100_OP_CFG_DUMMY_NUM(spi->read->dummy);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	regval = HIFMC100_OP_CTRL_RD_OPCODE(spi->read->cmd)
		| HIFMC100_OP_CTRL_DMA_OP(HIFMC100_OP_TYPE_DMA)
		| HIFMC100_OP_CTRL_RW_OP(HIFMC100_RW_OP_READ)
		| HIFMC100_OP_CTRL_DMA_OP_READY;

#ifdef CONFIG_HIFMC100_OOB_READ
	if (host->command == NAND_CMD_READOOB)
		regval |= HIFMC100_OP_CTRL_RD_OP_SEL(HIFMC100_RD_OP_READ_OOB);
#endif /* HIFMC100_RD_OP_READ_OOB */

#ifdef CONFIG_HIFMC100_BULK_READ
	{
		u32 read_type = chip->ops.rmode.mode;
		if (read_type == MTD_READ_BULK)
			regval |= HIFMC100_OP_CTRL_RD_OP_SEL(HIFMC100_RD_OP_BULK_READ);
	}
#endif /* CONFIG_HIFMC100_BULK_READ */

	hifmc_write(host, regval, HIFMC100_OP_CTRL);

	FMC_DMA_WAIT_INT_FINISH(host);

	chip->ops.rmode.mode = MTD_READ_PAGE;

	host->cache_addr_value[0] = host->addr_value[0];
	host->cache_addr_value[1] = host->addr_value[1];
}

#endif /* HIFMC100_SPI_NAND_SUPPORT_REG_READ */

/*****************************************************************************/
static void hifmc100_send_cmd_erase(struct hifmc_host *host)
{
	u32 regval;
	struct hifmc_op *spi = host->spi;

	spi->driver->wait_ready(spi);

	if (spi->driver->write_enable(spi))
		return;

	host->set_system_clock(host, spi->erase, TRUE);

	hifmc_write(host, host->FMC_CFG_ECC_NONE, HIFMC100_CFG);

	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	hifmc_write(host, HIFMC100_CMD_CMD1(spi->erase->cmd), HIFMC100_CMD);

	hifmc_write(host, host->addr_value[0], HIFMC100_ADDRL);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
		| HIFMC100_OP_CFG_MEM_IF_TYPE(spi->erase->iftype)
		| HIFMC100_OP_CFG_ADDR_NUM(HIFMC100_STD_OP_ADDR_NUM)
		| HIFMC100_OP_CFG_DUMMY_NUM(spi->erase->dummy);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_ADDR_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);
}

/*****************************************************************************/
static void hifmc100_send_cmd_status(struct hifmc_host *host)
{
	unsigned char status, addr;
	struct nand_chip *chip = host->chip;

	/* in case nand_check_wp, should read protection register. */
	if (chip->state == FL_READING)
		addr = PROTECTION_REGISTER;
	else
		addr = STATUS_REGISTER;

	spi_nand_feature_op(host, GET_FEATURE, addr, &status);
}

/*****************************************************************************/
static void hifmc100_send_cmd_readid(struct hifmc_host *host)
{
	u32 regval;

	hifmc_write(host, host->FMC_CFG_ECC_NONE, HIFMC100_CFG);

	hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_RDID), HIFMC100_CMD);
	hifmc_write(host, READ_ID_ADDR, HIFMC100_ADDRL);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
		| HIFMC100_OP_CFG_ADDR_NUM(READ_ID_ADDR_NUM);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	regval = HIFMC100_DATA_NUM_CNT(READ_ID_LEN);
	hifmc_write(host, regval, HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CMD1_EN(ENABLE)
		| HIFMC100_OP_ADDR_EN(ENABLE)
		| HIFMC100_OP_READ_DATE_EN(ENABLE)
		| HIFMC100_OP_REG_OP_START;
	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	hifmc_write(host, host->FMC_CFG, HIFMC100_CFG);
}

/*****************************************************************************/
static void hifmc100_send_cmd_reset(struct hifmc_host *host)
{
	hifmc_write(host, HIFMC100_CMD_CMD1(SPI_CMD_RESET), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(host->chipselect), 
		    HIFMC100_OP_CFG);

	hifmc_write(host, HIFMC100_OP_CMD1_EN(ENABLE) 
			  | HIFMC100_OP_REG_OP_START, 
		    HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);
}

/*****************************************************************************/
static void status_register_reorganize(struct mtd_info *mtd, 
					unsigned char *value)
{
	unsigned char status_register;
	struct nand_chip *chip = mtd->priv;

	/* init: no protect, no error. */
	status_register = NAND_STATUS_WP;
	/* in case nand_check_wp, should read protection register. */
	if (chip->state == FL_READING) {
		if (*value & ALL_BP_MASK)
			status_register &= ~NAND_STATUS_WP;

	} else {
		if (!(*value & STATUS_OIP_MASK))
			status_register |= NAND_STATUS_READY;
		
		if ((*value & STATUS_P_FAIL_MASK) || (*value & STATUS_E_FAIL_MASK))
			status_register |= NAND_STATUS_FAIL;
	}

	*value = status_register;
}
/*****************************************************************************/
static u8 hifmc100_read_byte(struct mtd_info *mtd)
{
	unsigned char value = 0;
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	host->offset++;

	if (host->command == NAND_CMD_STATUS) {
		value = readb(chip->IO_ADDR_R + host->offset - 1);
		status_register_reorganize(mtd, &value);
		return value;
	}

	if (host->command == NAND_CMD_READID)
		return readb(chip->IO_ADDR_R + host->offset - 1);

	if (host->command == NAND_CMD_READOOB)
		return readb(host->dma_oob + host->offset - 1);

	return readb(host->buffer + host->column + host->offset - 1);
}

/*****************************************************************************/
static u16 hifmc100_read_word(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	host->offset += 2;
	return readw(host->buffer + host->column + host->offset - 2);
}

/*****************************************************************************/
static void hifmc100_write_buf(struct mtd_info *mtd,
	const uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

#ifdef HIFMC100_SPI_NAND_SUPPORT_REG_WRITE
	memcpy((char *)host->iobase + + host->column + host->offset, buf, len);
	host->offset += len;
#else
	memcpy(host->buffer + host->column + host->offset, buf, len);
	host->offset += len;
#endif
}

/*****************************************************************************/
static void hifmc100_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

#ifdef HIFMC100_SPI_NAND_SUPPORT_REG_READ
	memcpy(buf, (char *)host->iobase + host->column + host->offset, len);
	host->offset += len;
#else
	memcpy(buf, host->buffer + host->column + host->offset, len);
	host->offset += len;
#endif
}

/*****************************************************************************/
#ifdef CONFIG_HIFMC100_BULK_READ
static void hifmc100_cache_read_buf(struct mtd_info *mtd, 
				    uint8_t *pagebuf, int datalen,
				    uint8_t *oobbuf, int ooblen)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	memcpy(oobbuf, HIFMC100_GET_HOST_OOBBUF(host) 
	       + host->column + host->oob_offset, ooblen);
	host->oob_offset += ooblen;

	memcpy(pagebuf, HIFMC100_GET_HOST_BUF(host) 
	       + host->column + host->offset, datalen);
	host->offset += datalen;
}
#endif /* CONFIG_HIFMC100_BULK_READ */
/*****************************************************************************/
static void hifmc100_select_chip(struct mtd_info *mtd, int chipselect)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	if (chipselect < 0)
		return;

	if (chipselect > CONFIG_SYS_MAX_NAND_DEVICE)
		PR_BUG("invalid chipselect: %d\n", chipselect);

	host->chipselect = chipselect;
}

/*****************************************************************************/
static void hifmc100_cmd_ctrl(struct mtd_info *mtd, int dat, unsigned ctrl)
{
	int is_cache_invalid = 1;
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	if (ctrl & NAND_ALE) {
		unsigned int addr_value = 0;
		unsigned int addr_offset = 0;

		if (ctrl & NAND_CTRL_CHANGE) {
			host->addr_cycle = 0x0;
			host->addr_value[0] = 0x0;
			host->addr_value[1] = 0x0;
		}
		addr_offset = host->addr_cycle << 3;

		if (host->addr_cycle >= HIFMC100_ADDR_CYCLE_MASK) {
			addr_offset = (host->addr_cycle -
					HIFMC100_ADDR_CYCLE_MASK) << 3;
			addr_value = 1;
		}

		host->addr_value[addr_value] |=
			((dat & 0xff) << addr_offset);

		host->addr_cycle++;
	}

	if ((ctrl & NAND_CLE) && (ctrl & NAND_CTRL_CHANGE)) {
		host->command = dat & 0xff;
		switch (host->command) {
		case NAND_CMD_PAGEPROG:
			host->offset = 0;
			host->send_cmd_pageprog(host);
			break;

		case NAND_CMD_READSTART:
			is_cache_invalid = 0;
#ifdef CONFIG_HIFMC100_OOB_READ
			/* In case READ OOB only. */
			if (host->addr_value[0] == host->pagesize) {
				host->command = NAND_CMD_READOOB;
				chip->ops.rmode.mode = MTD_READ_OOB;
			}
#endif /* CONFIG_HIFMC100_OOB_READ */
			host->send_cmd_readstart(host);
			break;

		case NAND_CMD_ERASE2:
			host->send_cmd_erase(host);
			break;

		case NAND_CMD_READID:
			memset((unsigned char *)(chip->IO_ADDR_R), 0,
				READ_ID_LEN);
			host->send_cmd_readid(host);
			break;

		case NAND_CMD_STATUS:
			memset((unsigned char *)(chip->IO_ADDR_R), 0,
				FEATURES_DATA_NUM);
			host->send_cmd_status(host);
			break;

		case NAND_CMD_SEQIN:
			break;

		case NAND_CMD_ERASE1:
			break;

		case NAND_CMD_READ0:
			break;

		case NAND_CMD_RESET:
			host->send_cmd_reset(host);
			break;

		default:
			break;
		}
	}

	/* pass pagesize and ecctype to kernel when startup. */
	hifmc_write(host, host->FMC_CFG, HIFMC100_CFG);

	if ((dat == NAND_CMD_NONE) && host->addr_cycle) {
		if (host->command == NAND_CMD_SEQIN
		    || host->command == NAND_CMD_READ0
		    || host->command == NAND_CMD_READID
		    || host->command == NAND_CMD_READOOB
		    || host->command == NAND_CMD_STATUS) {
			host->offset = 0x0;
			host->oob_offset = 0x0;
			host->column = (host->addr_value[0] & 0xffff);
		}
	}

	if (is_cache_invalid) {
		host->cache_addr_value[0] = ~0;
		host->cache_addr_value[1] = ~0;
	}
}

/*****************************************************************************/
static int hifmc100_dev_ready(struct mtd_info *mtd)
{
	u32 regval;
	unsigned long deadline = 1 << 15;
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	do {
		hifmc_write(host, HIFMC100_OP_CFG_FM_CS(host->chipselect),
			    HIFMC100_OP_CFG);

		hifmc_write(host, HIFMC100_OP_READ_STATUS_EN(ENABLE)
				  | HIFMC100_OP_REG_OP_START, HIFMC100_OP);

		FMC_CMD_WAIT_CPU_FINISH(host);

		regval = hifmc_read(host, HIFMC100_STATUS);
		if (!(regval & STATUS_OIP_MASK))
			return 1;

		udelay(1);

	} while (deadline--);

	PR_OUT("ERROR: nand wait ready timeout, status[%#x]\n", regval);

	return 0;
}

/*****************************************************************************/
/*
 * 'host->epm' only use the first oobfree[0] field, it looks very simple, But...
 */
static struct nand_ecclayout nand_ecc_default = {
	.oobfree = {{2, 30} }
};

/*****************************************************************************/
static struct nand_config_table hifmc100_spi_nand_config_table[] = {
	{NAND_PAGE_4K,	NAND_ECC_24BIT,	200,	&nand_ecc_default},
	{NAND_PAGE_4K,	NAND_ECC_8BIT,	88,	&nand_ecc_default},
	{NAND_PAGE_4K,	NAND_ECC_NONE,	32,	&nand_ecc_default},

	{NAND_PAGE_2K,	NAND_ECC_24BIT,	116,	&nand_ecc_default},
	{NAND_PAGE_2K,	NAND_ECC_8BIT,	60,	&nand_ecc_default},
	{NAND_PAGE_2K,	NAND_ECC_NONE,	32,	&nand_ecc_default},

	{0, 0, 0, NULL},
};

/*****************************************************************************/
/* used the best correct arithmetic. */
static struct nand_config_table *
hifmc100_get_best_ecc(struct nand_config_table *config, struct mtd_info *mtd)
{
	struct nand_config_table *best = NULL;

	for (; config->layout; config++) {
		if (nandpage_type2size(config->pagetype) != mtd->writesize)
			continue;

		if (mtd->oobsize < config->oobsize)
			continue;

		if (!best || (best->ecctype < config->ecctype))
			best = config;
	}

	if (!best)
		PR_BUG(ERSTR_DRIVER "Driver does not support the pagesize" \
		"(%d) and oobsize(%d).\n", mtd->writesize, mtd->oobsize);

	return best;
}

/*****************************************************************************/
#if (defined (CONFIG_HIFMC100_HARDWARE_PAGESIZE_ECC) \
     || defined (CONFIG_HIFMC100_AUTO_PAGESIZE_ECC_NONE))
/* force the pagesize and ecctype */
static struct nand_config_table *hifmc100_force_ecc(struct mtd_info *mtd, int pagetype,
		int ecctype, char *cfgmsg, int allow_pagediv)
{
	int pagesize;
	struct nand_config_table *fit = NULL;
	struct nand_config_table *info = hifmc100_spi_nand_config_table;

	for (; info->layout; info++) {
		if (info->pagetype == pagetype && info->ecctype == ecctype) {
			fit = info;
			break;
		}
	}

	if (!fit) {
		nand_register_dump();
		PR_BUG(ERSTR_DRIVER "Driver(%s mode) does not support this" \
			" Nand Flash pagesize:%s, ecctype:%s\n", cfgmsg,
			nand_page_name(pagetype), nand_ecc_name(ecctype));
		return NULL;
	}

	pagesize = nandpage_type2size(pagetype);
	if ((pagesize != mtd->writesize)
		&& (pagesize > mtd->writesize || !allow_pagediv)) {
		nand_register_dump();
		PR_BUG(ERSTR_HARDWARE "Hardware (%s mode) configure pagesize" \
			" %d, but the Nand Flash pageszie is %d\n", cfgmsg,
			pagesize, mtd->writesize);
		return NULL;
	}

	if (fit->oobsize > mtd->oobsize) {
		PR_BUG(ERSTR_HARDWARE "(%s mode) The Nand Flash offer space" \
			" area is %d bytes, but the controller request %d" \
			"bytes in ecc %s. Please make sure the hardware ECC " \
			"configuration is correct.", cfgmsg, mtd->oobsize,
			fit->oobsize, nand_ecc_name(ecctype));
		return NULL;
	}

	return fit;
}
#endif
/*****************************************************************************/

static int hifmc_check_config(struct hifmc_host *host,
				struct nand_dev_t *nand_dev,
				struct nand_config_table *best, int is_hw_auto)
{
	int isdump = 0;
	int ecctype;
	int pagetype;

	pagetype = hifmc100_nand_page_reg2type(
			(host->FMC_CFG >> HIFMC100_PAGE_SIZE_SHIFT) 
			 & HIFMC100_PAGE_SIZE_MASK);

	ecctype = hifmc100_nand_ecc_reg2type(
			(host->FMC_CFG >> HIFMC100_ECC_TYPE_SHIFT) 
			 & HIFMC100_ECC_TYPE_MASK);

	if (pagetype != best->pagetype) {
		if (!isdump++)
			nand_register_dump();
		if (is_hw_auto) {
			PR_BUG("!!! warning: "
				"Hardware configure pagesize %s, "
				"but the Nand Flash pageszie is %s. "
				"Update fastboot will resolve this problem.\n",
				nand_page_name(pagetype),
				nand_page_name(best->pagetype));
		} else {
			PR_BUG("!!! warning: "
				"Hardware configure pagesize %s, "
				"but the Nand Flash pageszie is %s. "
				"Modify hardware pin will resolve this problem.\n",
				nand_page_name(pagetype),
				nand_page_name(best->pagetype));
		}
	}

	if (ecctype < best->ecctype) {
		if (!is_hw_auto)
			best->ecctype = ecctype;
	} else if (ecctype > best->ecctype) {
		PR_BUG("!!! warning: "
			"Hardware configure ecctype %s, "
			"but %s is more suitable for this Nand Flash."
			"Modify hardware pin will resolve this problem.\n",
			nand_ecc_name(ecctype),
			nand_ecc_name(best->ecctype));
	}

	return 0;
}

/*****************************************************************************/

static void hifmc100_set_blocksize(struct hifmc_host *host)
{
	u32 regval;
	regval = hifmc_read(host, HIFMC100_CFG);
	regval &= ~HIFMC100_BLOCK_SIZE_MASK;
	int pagenum = host->block_page_mask + 1;

	switch (pagenum) {
	case 64:
		regval |= HIFMC100_BLOCK_SIZE_64_PAGE;
		hifmc_write(host, regval, HIFMC100_CFG);
		break;
	case 128:
		regval |= HIFMC100_BLOCK_SIZE_128_PAGE;
		hifmc_write(host, regval, HIFMC100_CFG);
		break;
	case 256:
		regval |= HIFMC100_BLOCK_SIZE_256_PAGE;
		hifmc_write(host, regval, HIFMC100_CFG);
		break;
	case 512:
		regval |= HIFMC100_BLOCK_SIZE_512_PAGE;
		hifmc_write(host, regval, HIFMC100_CFG);
		break;
	default:
		break;
	}
}
/*****************************************************************************/

static void hifmc100_config_chiptype(struct hifmc_host *host, 
				     struct nand_dev_t *nand_dev)
{
	unsigned char mfr = nand_dev->ids[0];

	host->FMC_CFG &= ~HIFMC100_SPI_NAND_SEL_MASK;
	host->FMC_CFG_ECC_NONE &= ~HIFMC100_SPI_NAND_SEL_MASK;
	
	switch (mfr) {
	case NAND_MFR_MICRON:
		host->FMC_CFG |= 
			HIFMC100_CFG_SPI_NAND_SEL(HIFMC100_SPI_NAND_SEL_MICRON);
		host->FMC_CFG_ECC_NONE |= 
			HIFMC100_CFG_SPI_NAND_SEL(HIFMC100_SPI_NAND_SEL_MICRON);
		break;
	default:
		break;
	}

	hifmc_write(host, host->FMC_CFG, HIFMC100_CFG);
}
/*****************************************************************************/

static int hifmc100_param_adjust(struct mtd_info *mtd, struct nand_chip *chip,
	struct nand_dev_t *nand_dev)
{
	char *start_type = "unknown";
	struct nand_config_table *best = NULL;
	struct nand_config_table *config = NULL;
	struct hifmc_host *host = chip->priv;
	u32 regval;

	start_type = "HW-Auto";
	config = hifmc100_spi_nand_config_table;
	best = hifmc100_get_best_ecc(config, mtd);
	if (IS_NANDC_CONFIG_DONE(host))
		hifmc_check_config(host, nand_dev, best, 1);
	
#ifdef CONFIG_HIFMC100_AUTO_PAGESIZE_ECC_NONE
{
	#ifdef CONFIG_HIFMC100_AUTO_PAGESIZE_ECC
	#error you SHOULD NOT define CONFIG_HIFMC100_PAGESIZE_AUTO_ECC_NONE \
		and CONFIG_HIFMC100_AUTO_PAGESIZE_ECC at the same time
	#endif

	#ifdef CONFIG_HIFMC100_HARDWARE_PAGESIZE_ECC
	#error you SHOULD NOT define CONFIG_HIFMC100_PAGESIZE_AUTO_ECC_NONE \
		and CONFIG_HIFMC100_HARDWARE_PAGESIZE_ECC at the same time
	#endif

	int pagetype = nandpage_size2type(mtd->writesize);
	int ecctype = NAND_ECC_NONE;
	best = hifmc100_force_ecc(config, mtd, pagetype, ecctype,
		"force config", 0);
	start_type = "NoECC";
}

#endif /* CONFIG_HIFMC100_AUTO_PAGESIZE_ECC_NONE */

#ifdef CONFIG_HIFMC100_HARDWARE_PAGESIZE_ECC
	#ifdef CONFIG_HIFMC100_AUTO_PAGESIZE_ECC
	#error you SHOULD NOT define CONFIG_HIFMC100_AUTO_PAGESIZE_ECC \
		and CONFIG_HIFMC100_HARDWARE_PAGESIZE_ECC at the same time
	#endif

	#ifdef CONFIG_HIFMC100_AUTO_PAGESIZE_ECC_NONE
	#error you SHOULD NOT define CONFIG_HIFMC100_AUTO_PAGESIZE_ECC_NONE \
		and CONFIG_HIFMC100_AUTO_PAGESIZE_ECC at the same time
	#endif

	int pagetype = hifmc100_nand_page_reg2type((host->FMC_CFG & HIFMC100_PAGE_SIZE_MASK) >> HIFMC100_PAGE_SIZE_SHIFT);
	int ecctype = hifmc100_nand_ecc_reg2type((host->FMC_CFG & HIFMC100_ECC_TYPE_MASK) >> HIFMC100_ECC_TYPE_SHIFT);

	best = hifmc100_force_ecc(mtd, pagetype, ecctype, "hardware config", 0);
	hifmc_check_config(host, nand_dev, best, 0);
	start_type = "Hardware";

#endif /* CONFIG_HIFMC100_HARDWARE_PAGESIZE_ECC */

	if (!best)
		PR_BUG(ERSTR_HARDWARE "Please configure SPI Nand Flash " \
				"pagesize and ecctype!\n");

	if (best->ecctype != NAND_ECC_NONE)
		mtd->oobsize = best->oobsize;
	mtd->oobused = HIFMC100_NAND_OOBSIZE_FOR_YAFFS;

	chip->ecc.layout = best->layout;

	host->ecctype  = best->ecctype;
	host->pagesize = nandpage_type2size(best->pagetype);
	host->oobsize  = mtd->oobsize;
	host->block_page_mask = ((mtd->erasesize / mtd->writesize) - 1);


	host->buforg = kmalloc((host->pagesize
		+ host->oobsize + HIFMC100_NAND_DMA_ALIGN), GFP_KERNEL);
	if (!host->buforg) {
		PR_BUG(ERSTR_DRIVER
			"Can't malloc memory for NAND driver.");
		return 1;
	}
	/* 32 bytes alignment */
	host->buffer = (char *)((unsigned int)(host->buforg
		+ HIFMC100_NAND_DMA_ALIGN - 1) & ~(HIFMC100_NAND_DMA_ALIGN - 1));
	host->dma_buffer = (unsigned int)host->buffer;
	memset(host->buffer, 0xff, (host->pagesize + host->oobsize));

	host->dma_oob = host->dma_buffer + host->pagesize;
	host->bbm = (unsigned char *)(host->buffer
		+ host->pagesize + HIFMC_BAD_BLOCK_POS);

	host->epm = (unsigned short *)(host->buffer
		+ host->pagesize + chip->ecc.layout->oobfree[0].offset + 28);

#if (defined CONFIG_HIFMC100_BULK_READ || defined CONFIG_HIFMC100_CACHE_READ)
	host->buforg = kmalloc(((host->pagesize + host->oobsize) 
				* (host->block_page_mask + 1)) + 
				HIFMC100_NAND_DMA_ALIGN, GFP_KERNEL);
	if (!host->buforg) {
		PR_BUG(ERSTR_DRIVER
			"Can't malloc memory for NAND driver.");
		return 1;
	}
	/* 32 bytes alignment */
	host->cache_read_pagebuf = (char *)((unsigned int)(host->buforg
		+ HIFMC100_NAND_DMA_ALIGN - 1) & ~(HIFMC100_NAND_DMA_ALIGN - 1));
	host->cache_read_oobbuf = host->cache_read_pagebuf + host->pagesize
				  * (host->block_page_mask + 1);
#endif


	regval = ~((HIFMC100_PAGE_SIZE_MASK << HIFMC100_PAGE_SIZE_SHIFT) 
		| (HIFMC100_ECC_TYPE_MASK << HIFMC100_ECC_TYPE_SHIFT));
	host->FMC_CFG &= regval;
	host->FMC_CFG |= (HIFMC100_CFG_ECC_TYPE(best->ecctype)
			  | HIFMC100_CFG_PAGE_SIZE(best->pagetype)
			  | HIFMC100_CFG_OP_MODE(HIFMC100_OP_MODE_NORMAL));

	if (mtd->writesize > SPI_NAND_MAX_PAGESIZE
		|| mtd->oobsize > SPI_NAND_MAX_OOBSIZE) {
		PR_BUG(ERSTR_DRIVER "Driver does not support this Nand " \
			"Flash. Please increase SPI_NAND_MAX_PAGESIZE and " \
			"SPI_NAND_MAX_OOBSIZE.\n");
	}

	if (mtd->writesize != host->pagesize) {
		unsigned int shift = 0;
		unsigned int writesize = mtd->writesize;
		while (writesize > host->pagesize) {
			writesize >>= 1;
			shift++;
		}
		chip->chipsize = chip->chipsize >> shift;
		mtd->erasesize = mtd->erasesize >> shift;
		mtd->writesize = host->pagesize;
		PR_OUT("Nand divide into 1/%u\n", (1 << shift));
	}

	HIFMC100_SET_PAGESIZE(host);
	HIFMC100_SET_ECCTYPE(host);
	hifmc100_set_blocksize(host);

	/* for micron chip, need to config chip type. */
	hifmc100_config_chiptype(host, nand_dev);

	nand_dev->start_type = start_type;
	nand_dev->ecctype = host->ecctype;
	nand_dev->oobsize = host->oobsize;
	nand_dev->hostver = HIFMC_VER_100;

	return 0;
}

/*****************************************************************************/
static void hifmc100_nand_init(struct nand_chip *chip)
{
	chip->read_byte   = hifmc100_read_byte;
	chip->read_word   = hifmc100_read_word;
	chip->write_buf   = hifmc100_write_buf;
	chip->read_buf    = hifmc100_read_buf;

#ifdef CONFIG_HIFMC100_BULK_READ
	chip->cache_read_buf = hifmc100_cache_read_buf;
#endif /* CONFIG_HIFMC100_BULK_READ */

	chip->select_chip = hifmc100_select_chip;

	chip->cmd_ctrl    = hifmc100_cmd_ctrl;
	chip->dev_ready   = hifmc100_dev_ready;

	chip->chip_delay  = HIFMC100_CHIP_DELAY;

	chip->options     = NAND_NO_AUTOINCR | NAND_BBT_SCANNED;

	chip->ecc.layout  = NULL;
	chip->ecc.mode    = NAND_ECC_NONE;
}

/*****************************************************************************/
static int hifmc100_host_init(struct hifmc_host *host)
{
	u32 regval, flash_type;

	regval = hifmc_read(host, HIFMC100_CFG);
	flash_type = (regval & HIFMC100_FLASH_SEL_MASK) 
		      >> HIFMC100_FLASH_SEL_SHIFT;
	if (flash_type != HIFMC100_FLASH_TYPE_SPI_NAND) {
		PR_OUT("ERROR: Flash type[%d] check failed!\n", flash_type);
		return -ENODEV;
	}

	if ((regval & HIFMC100_OP_MODE_MASK) == HIFMC100_OP_MODE_BOOT)
		regval |= HIFMC100_CFG_OP_MODE(HIFMC100_OP_MODE_NORMAL);

	hifmc_write(host, regval, HIFMC100_CFG);

	host->FMC_CFG = regval;
	host->FMC_CFG_ECC_NONE = host->FMC_CFG 
				& ~(HIFMC100_ECC_TYPE_MASK 
				    << HIFMC100_ECC_TYPE_SHIFT);

	/* enable LP control. */
	regval = hifmc_read(host, HIFMC100_LP_CTRL);
	regval |= HIFMC100_CLK_GATE_EN;
	hifmc_write(host, regval, HIFMC100_LP_CTRL);

	host->addr_cycle    = 0;
	host->addr_value[0] = 0;
	host->addr_value[1] = 0;
	host->cache_addr_value[0] = ~0;
	host->cache_addr_value[1] = ~0;

	host->send_cmd_pageprog  = hifmc100_send_cmd_pageprog;
	host->send_cmd_status    = hifmc100_send_cmd_status;
	host->send_cmd_readstart = hifmc100_send_cmd_readstart;
	host->send_cmd_erase     = hifmc100_send_cmd_erase;
	host->send_cmd_readid    = hifmc100_send_cmd_readid;
	host->send_cmd_reset     = hifmc100_send_cmd_reset;
	host->set_system_clock   = hifmc100_set_system_clock;

	hifmc_write(host,
			HIFMC100_TIMING_SPI_CFG_TCSH(HIFMC100_CS_HOLD_TIME)
			| HIFMC100_TIMING_SPI_CFG_TCSS(HIFMC100_CS_SETUP_TIME)
			| HIFMC100_TIMING_SPI_CFG_TSHSL(HIFMC100_CS_DESELECT_TIME), 
		    HIFMC100_TIMING_SPI_CFG);

	hifmc_write(host, HIFMC100_ALL_BURST_ENABLE, HIFMC100_DMA_AHB_CTRL);

	/*
	 * check if start from nand.
	 * This register REG_SC_GEN15 is set in start.S
	 * When start in NAND (Auto), the ECC/PAGESIZE driver don't detect.
	 */
	if (readl(REG_BASE_SCTL + REG_SC_GEN15) == BOOT_FROM_SPINAND)
		host->flags |= NANDC_CONFIG_DONE;

	regval = hifmc_read(host, HIFMC100_BOOT_SET);
	if (regval & HIFMC100_BOOT_SET_HW_AUTO)
		host->flags |= NANDC_HW_AUTO;
	else {
		PR_OUT("ERROR: Not support hardware pin mode. "
			"Enable hardware auto mode to resolve this problem.\n");
		return -ENODEV;
	}

	host->set_system_clock(host, NULL, TRUE);

	return 0;
}
/*****************************************************************************/

static int hifmc100_version_check(void)
{
	u32 regval;
	regval = readl(CONFIG_HIFMC100_REG_BASE_ADDRESS + HIFMC100_VERSION);
	return (regval == HIFMC_VER_100);
}

/*****************************************************************************/
int hifmc100_spi_nand_init(struct nand_chip *chip)
{
	struct hifmc_host *host = &fmc_host;

        if (host->chip)
                return 0;

	/* hifmc flash type check */
	if (get_bootmedia(NULL, NULL) != BOOT_MEDIA_SPI_NAND) {
		return -ENODEV;
	}

	/* hifmc ip version check */
	printf("SPI Nand Check Flash Memory Controller v100 ... ");
	if (!hifmc100_version_check()) {
		printf("\n");
		return -ENODEV;
	}
	printf("Found\n");
	
	memset(host, 0, sizeof(struct hifmc_host));
	host->regbase = (void __iomem *)CONFIG_HIFMC100_REG_BASE_ADDRESS;
	host->iobase = chip->IO_ADDR_R = chip->IO_ADDR_W =
		(void *)CONFIG_HIFMC100_BUFFER_BASE_ADDRESS;

	memset((char *)host->iobase, 0xff, HIFMC100_BUFFER_LEN);
	/* hifmc host init */
	if (hifmc100_host_init(host)) {
		PR_OUT("SPI Nand host init failed!\n");
		return -ENOMEM;
	}

	chip->is_spi_nand = 1;
	chip->priv = host;

	host->chip = chip;

	hifmc100_nand_init(chip);

	spi_nand_ids_register();

	nand_param_adjust = hifmc100_param_adjust;

	return 0;
}
