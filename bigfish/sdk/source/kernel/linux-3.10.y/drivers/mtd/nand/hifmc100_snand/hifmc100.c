/******************************************************************************
 *    Flash Memory Controller v100 Device Driver
 *    Copyright (c) 2014 Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By hisilicon
 *
******************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100_spi_ids.h"
#include "hifmc100.h"
#include "../hifmc100_gen.h"

#ifdef CONFIG_ARCH_S40
	#include "hifmc100_s40.c"
#endif

/*****************************************************************************/
static char *len_to_str(unsigned long long size)
{
	int ix;
	static char buffer[20];
	char *fmt[] = {"%u", "%uK", "%uM", "%uG", "%uT", "%uT"};

	for (ix = 0; (ix < 5) && !(size & 0x3FF) && size; ix++)
		size = (size >> 10);

	sprintf(buffer, fmt[ix], size);
	return buffer;
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
	int ret;
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

	init_completion(&host->dma_done);

	/* enable dma done interrupt. */
	regval = hifmc_read(host, HIFMC100_INT_EN);
	regval |= HIFMC100_INT_EN_OP_DONE;
	hifmc_write(host, regval, HIFMC100_INT_EN);

	regval = HIFMC100_OP_CTRL_WR_OPCODE(spi->write->cmd)
		| HIFMC100_OP_CTRL_DMA_OP(HIFMC100_OP_TYPE_DMA)
		| HIFMC100_OP_CTRL_RW_OP(HIFMC100_RW_OP_WRITE)
		| HIFMC100_OP_CTRL_DMA_OP_READY;
	hifmc_write(host, regval, HIFMC100_OP_CTRL);

	ret = wait_for_completion_timeout(&host->dma_done,
					  msecs_to_jiffies(2000));
	if (!ret)
		PR_OUT("wait dma transfer complete timeout!");

	/* disable dma done interrupt */
	regval = hifmc_read(host, HIFMC100_INT_EN);
	regval &= ~HIFMC100_INT_EN_OP_DONE;
	hifmc_write(host, regval, HIFMC100_INT_EN);
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
	int ret;
	struct hifmc_op *spi = host->spi;

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

	regval = host->dma_buffer;
	hifmc_write(host, regval, HIFMC100_DMA_SADDR_D0);

	regval += HIFMC100_DMA_ADDR_OFFSET;
	hifmc_write(host, regval, HIFMC100_DMA_SADDR_D1);

	regval += HIFMC100_DMA_ADDR_OFFSET;
	hifmc_write(host, regval, HIFMC100_DMA_SADDR_D2);

	regval += HIFMC100_DMA_ADDR_OFFSET;
	hifmc_write(host, regval, HIFMC100_DMA_SADDR_D3);

	hifmc_write(host, host->dma_oob, HIFMC100_DMA_SADDR_OOB);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
		| HIFMC100_OP_CFG_MEM_IF_TYPE(spi->read->iftype)
		| HIFMC100_OP_CFG_DUMMY_NUM(spi->read->dummy);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	init_completion(&host->dma_done);

	/* enable dma done interrupt. */
	regval = hifmc_read(host, HIFMC100_INT_EN);
	regval |= HIFMC100_INT_EN_OP_DONE;
	hifmc_write(host, regval, HIFMC100_INT_EN);

	regval = HIFMC100_OP_CTRL_RD_OPCODE(spi->read->cmd)
		| HIFMC100_OP_CTRL_DMA_OP(HIFMC100_OP_TYPE_DMA)
		| HIFMC100_OP_CTRL_RW_OP(HIFMC100_RW_OP_READ)
		| HIFMC100_OP_CTRL_DMA_OP_READY;

#ifdef CONFIG_HIFMC100_OOB_READ
	if (host->command == NAND_CMD_READOOB)
		regval |= HIFMC100_OP_CTRL_RD_OP_SEL(HIFMC100_RD_OP_READ_OOB);
#endif /* CONFIG_HIFMC100_OOB_READ */
	hifmc_write(host, regval, HIFMC100_OP_CTRL);

	ret = wait_for_completion_timeout(&host->dma_done,
					  msecs_to_jiffies(2000));
	if (!ret)
		PR_OUT("wait dma transfer complete timeout!");

	/* disable dma done interrupt */
	regval = hifmc_read(host, HIFMC100_INT_EN);
	regval &= ~HIFMC100_INT_EN_OP_DONE;
	hifmc_write(host, regval, HIFMC100_INT_EN);

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

unsigned char hifmc100_trans_spi_status(unsigned char reg)
{
	unsigned char status = 0;

	if (!(reg & STATUS_OIP_MASK))
		status |= NAND_STATUS_READY;

	if (!(reg & STATUS_WEL_MASK))
		status |= NAND_STATUS_WP;

	if ((reg & STATUS_P_FAIL_MASK) || (reg & STATUS_E_FAIL_MASK))
		status |= NAND_STATUS_FAIL;

	return status;
}

/*****************************************************************************/
static uint8_t hifmc100_read_byte(struct mtd_info *mtd)
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


//	if (host->command == NAND_CMD_READOOB)
//		return readb(host->buffer + host->column + host->offset - 1);

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
static void hifmc100_select_chip(struct mtd_info *mtd, int chipselect)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	if (chipselect < 0)
		return;

	if (chipselect > CONFIG_HIFMC100_MAX_CHIP)
		DBG_BUG("invalid chipselect: %d\n", chipselect);

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

	if ((dat == NAND_CMD_NONE) && host->addr_cycle) {
		if (host->command == NAND_CMD_SEQIN
		    || host->command == NAND_CMD_READ0
		    || host->command == NAND_CMD_READID
		    || host->command == NAND_CMD_READOOB
		    || host->command == NAND_CMD_STATUS) {
			host->offset = 0x0;
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
	unsigned long deadline = jiffies + HIFMC100_MAX_READY_WAIT_JIFFIES;
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

		cond_resched();

	} while (!time_after_eq(jiffies, deadline));

	DBG_MSG("ERROR: spi nand wait ready timeout, status[%#x]\n", regval);

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
static struct nand_ctrl_info_t hifmc_spi_nand_config_table[] = {
	{SZ_4K,	NAND_ECC_24BIT,	200,	&nand_ecc_default},
	{SZ_4K,	NAND_ECC_8BIT,	88,	&nand_ecc_default},
	{SZ_4K,	NAND_ECC_NONE,	32,	&nand_ecc_default},

	{SZ_2K,	NAND_ECC_24BIT,	116,	&nand_ecc_default},
	{SZ_2K,	NAND_ECC_8BIT,	60,	&nand_ecc_default},
	{SZ_2K,	NAND_ECC_NONE,	32,	&nand_ecc_default},

	{0, 0, 0, NULL},
};

/*****************************************************************************/
#ifdef CONFIG_HIFMC100_SPINAND_AUTO_PAGESIZE_ECC
/* used the best correct arithmetic. */
static struct nand_ctrl_info_t *hifmc100_get_best_ecc(struct mtd_info *mtd)
{
	struct nand_ctrl_info_t *best = NULL;
	struct nand_ctrl_info_t *info = hifmc_spi_nand_config_table;

	for (; info->layout; info++) {
		if (info->pagesize != mtd->writesize)
			continue;

		if (mtd->oobsize < info->oobsize)
			continue;

		if (!best || (best->ecctype < info->ecctype))
			best = info;
	}

	if (!best)
		DBG_BUG(ERSTR_DRIVER "Driver does not support the pagesize" \
		"(%d) and oobsize(%d).\n", mtd->writesize, mtd->oobsize);

	return best;
}
#endif

/*****************************************************************************/
/* force the pagesize and ecctype */
static struct nand_ctrl_info_t *hifmc100_force_ecc(struct mtd_info *mtd, int pagesize,
		int ecctype, char *cfgmsg, int allow_pagediv)
{
	struct nand_ctrl_info_t *fit = NULL;
	struct nand_ctrl_info_t *info = hifmc_spi_nand_config_table;

	for (; info->layout; info++) {
		if (info->pagesize == pagesize && info->ecctype == ecctype) {
			fit = info;
			break;
		}
	}

	if (!fit) {
		DBG_BUG(ERSTR_DRIVER "Driver(%s mode) does not support this" \
			" Nand Flash pagesize:%s, ecctype:%s\n", cfgmsg,
			len_to_str(pagesize), nand_ecc_name(ecctype));
		return NULL;
	}

	if ((pagesize != mtd->writesize)
		&& (pagesize > mtd->writesize || !allow_pagediv)) {
		DBG_BUG(ERSTR_HARDWARE "Hardware (%s mode) configure pagesize" \
			" %d, but the Nand Flash pageszie is %d\n", cfgmsg,
			pagesize, mtd->writesize);
		return NULL;
	}

	if (fit->oobsize > mtd->oobsize) {
		DBG_BUG(ERSTR_HARDWARE "(%s mode) The Nand Flash offer space" \
			" area is %d bytes, but the controller request %d" \
			"bytes in ecc %s. Please make sure the hardware ECC " \
			"configuration is correct.", cfgmsg, mtd->oobsize,
			fit->oobsize, nand_ecc_name(ecctype));
		return NULL;
	}

	return fit;
}

/*****************************************************************************/

int hifmc100_param_adjust(struct mtd_info *mtd, struct nand_chip *chip,
		struct nand_dev_t *nand_dev)
{
	char *start_type = "unknown";
	u32 regval;
	struct nand_ctrl_info_t *best = NULL;
	struct hifmc_host *host = chip->priv;

#ifdef CONFIG_HIFMC100_SPINAND_AUTO_PAGESIZE_ECC
	unsigned int reg;

	best = hifmc100_get_best_ecc(mtd);
	start_type = "Auto";
#endif /* CONFIG_HIFMC100_SPINAND_AUTO_PAGESIZE_ECC */

#ifdef CONFIG_HIFMC100_SPINAND_HARDWARE_PAGESIZE_ECC
	int pagesize, ecctype;
	#ifdef CONFIG_HIFMC100_SPINAND_AUTO_PAGESIZE_ECC
	#error you SHOULD NOT define CONFIG_HIFMC100_SPINAND_AUTO_PAGESIZE_ECC \
		and CONFIG_HIFMC100_SPINAND_HARDWARE_PAGESIZE_ECC at the same time
	#endif

	pagesize = hifmc100_page_reg2type((host->FMC_CFG >> HIFMC100_PAGE_SIZE_SHIFT) & HIFMC100_PAGE_SIZE_MASK);
	ecctype = hifmc100_ecc_reg2type((host->FMC_CFG >> HIFMC100_ECC_TYPE_SHIFT) & HIFMC100_ECC_TYPE_MASK);

	start_type = "Hardware";
	best = hifmc100_force_ecc(mtd, pagesize, ecctype, "Hardware config", 0);
#endif /* CONFIG_HIFMC100_SPINAND_HARDWARE_PAGESIZE_ECC */

#ifdef CONFIG_HIFMC100_SPINAND_PAGESIZE_AUTO_ECC_NONE
	#ifdef CONFIG_HIFMC100_SPINAND_AUTO_PAGESIZE_ECC
	#error you SHOULD NOT define CONFIG_HIFMC100_SPINAND_PAGESIZE_AUTO_ECC_NONE \
		and CONFIG_HIFMC100_SPINAND_AUTO_PAGESIZE_ECC at the same time
	#endif

	#ifdef CONFIG_HIFMC100_SPINAND_HARDWARE_PAGESIZE_ECC
	#error you SHOULD NOT define CONFIG_HIFMC100_SPINAND_PAGESIZE_AUTO_ECC_NONE \
		and CONFIG_HIFMC100_SPINAND_HARDWARE_PAGESIZE_ECC at the same time
	#endif

	best = hifmc100_force_ecc(mtd, mtd->writesize, NAND_ECC_NONE,
				  "force config", 0);
	start_type = "AutoForce";
#endif /* CONFIG_HIFMC100_SPINAND_PAGESIZE_AUTO_ECC_NONE */

	if (!best)
		DBG_BUG(ERSTR_HARDWARE
			"Please configure Nand Flash pagesize and ecctype!\n");

	if (best->ecctype != NAND_ECC_NONE)
		mtd->oobsize = best->oobsize;

	chip->ecc.layout = best->layout;

	host->ecctype  = best->ecctype;
	host->pagesize = best->pagesize;
	host->oobsize  = mtd->oobsize;
	host->block_page_mask = ((mtd->erasesize / mtd->writesize) - 1);

	host->dma_oob = host->dma_buffer + host->pagesize;

	host->bbm = (unsigned char *)(host->buffer + host->pagesize
		     + HIFMC_BAD_BLOCK_POS);

	host->epm = (unsigned short *)(host->buffer + host->pagesize
			+ chip->ecc.layout->oobfree[0].offset + 28);

	regval = ~(HIFMC100_PAGE_SIZE_MASK << HIFMC100_PAGE_SIZE_SHIFT);
	host->FMC_CFG &= regval;
	host->FMC_CFG_ECC_NONE &= regval;
	regval = (hifmc100_page_type2reg(best->pagesize) 
		  & HIFMC100_PAGE_SIZE_MASK) << HIFMC100_PAGE_SIZE_SHIFT;
	host->FMC_CFG |= regval;
	host->FMC_CFG_ECC_NONE |= regval;

	regval = ~(HIFMC100_ECC_TYPE_MASK << HIFMC100_ECC_TYPE_SHIFT);
	host->FMC_CFG &= regval;
	host->FMC_CFG_ECC_NONE &= regval;
	regval = (hifmc100_ecc_type2reg(best->ecctype) 
		  & HIFMC100_ECC_TYPE_MASK) << HIFMC100_ECC_TYPE_SHIFT; 
	host->FMC_CFG |= regval;

	if (mtd->writesize > SPI_NAND_MAX_PAGESIZE
	    || mtd->oobsize > SPI_NAND_MAX_OOBSIZE) {
		DBG_BUG(ERSTR_DRIVER
			"Driver does not support this Nand Flash. Please "
			"increase SPI_NAND_MAX_PAGESIZE and SPI_NAND_MAX_OOBSIZE.\n");
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
		DBG_MSG("Nand divide into 1/%u\n", (1 << shift));
	}

	nand_dev->start_type = start_type;
	nand_dev->oobsize = host->oobsize;
	nand_dev->ecctype = host->ecctype;

	return 0;
}

/*****************************************************************************/
void hifmc100_spi_nand_init(struct hifmc_host *host, struct nand_chip *chip)
{
	chip->read_byte   = hifmc100_read_byte;
	chip->read_word   = hifmc100_read_word;
	chip->write_buf   = hifmc100_write_buf;
	chip->read_buf    = hifmc100_read_buf;

	chip->select_chip = hifmc100_select_chip;

	chip->cmd_ctrl    = hifmc100_cmd_ctrl;
	chip->dev_ready   = hifmc100_dev_ready;

	chip->chip_delay  = HIFMC100_CHIP_DELAY;

	chip->options     = NAND_NO_AUTOINCR | NAND_SKIP_BBTSCAN;

	chip->ecc.layout  = NULL;
	chip->ecc.mode    = NAND_ECC_NONE;

	chip->priv        = host;
}

/*****************************************************************************/
int hifmc100_host_init(struct hifmc_host *host)
{
	u32 regval;

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

	regval = hifmc_read(host, HIFMC100_CFG);
	if ((regval & HIFMC100_OP_MODE_MASK) == HIFMC100_OP_MODE_BOOT)
		regval |= HIFMC100_CFG_OP_MODE(HIFMC100_OP_MODE_NORMAL);

	hifmc_write(host, regval, HIFMC100_CFG);

	host->FMC_CFG = regval;
	host->FMC_CFG_ECC_NONE = host->FMC_CFG 
				& ~(HIFMC100_ECC_TYPE_MASK 
				    << HIFMC100_ECC_TYPE_SHIFT);

	hifmc_write(host,
			HIFMC100_TIMING_SPI_CFG_TCSH(HIFMC100_CS_HOLD_TIME)
			| HIFMC100_TIMING_SPI_CFG_TCSS(HIFMC100_CS_SETUP_TIME)
			| HIFMC100_TIMING_SPI_CFG_TSHSL(HIFMC100_CS_DESELECT_TIME), 
		    HIFMC100_TIMING_SPI_CFG);

	hifmc_write(host, HIFMC100_ALL_BURST_ENABLE, HIFMC100_DMA_AHB_CTRL);

	host->set_system_clock(host, NULL, TRUE);

	hinfc_param_adjust = hifmc100_param_adjust;

	return 0;
}

