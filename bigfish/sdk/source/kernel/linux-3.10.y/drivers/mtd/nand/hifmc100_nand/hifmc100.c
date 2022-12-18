/******************************************************************************
 *    Flash Memory Controller v100 Device Driver
 *    Copyright (c) 2014 Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By hisilicon
 *
******************************************************************************/

#define pr_fmt(fmt) "hifmc100: " fmt

#include "hifmc100_os.h"
#include "hifmc100.h"
#include "hifmc100_dbg_inf.h"
#include "../hifmc100_gen.h"
#include "hifmc100_rw_latch.h"
#include "hifmc100_read_retry.h"
#include "hifmc100_ecc_info.h"
#include "hifmc100_cache.h"

/*****************************************************************************/
#ifdef CONFIG_ARCH_S40
	#include "hifmc100_s40.c"
#endif

/******************************************************************************/

static void hifmc100_dma_transfer(struct hifmc_host *host, int todev)
{
	u32 regval;
	int ret;
	unsigned int phyaddr;
	unsigned int phy_pageaddr;
	unsigned int phy_oobaddr;
	enum dma_data_direction direction =
		todev ? DMA_TO_DEVICE : DMA_FROM_DEVICE;

	phy_oobaddr = dma_map_single(host->dev, host->oobbuf,
		host->oobsize, direction);
	hifmc_write(host, phy_oobaddr, HIFMC100_DMA_SADDR_OOB);

	phyaddr = phy_pageaddr = dma_map_single(host->dev, host->pagebuf,
		host->pagesize, direction);

	hifmc_write(host, phyaddr, HIFMC100_DMA_SADDR_D0);

	phyaddr += HIFMC100_DMA_ADDR_OFFSET;
	hifmc_write(host, phyaddr, HIFMC100_DMA_SADDR_D1);

	phyaddr += HIFMC100_DMA_ADDR_OFFSET;
	hifmc_write(host, phyaddr, HIFMC100_DMA_SADDR_D2);

	phyaddr += HIFMC100_DMA_ADDR_OFFSET;
	hifmc_write(host, phyaddr, HIFMC100_DMA_SADDR_D3);


	if (host->ecctype == NAND_ECC_NONE) {
		hifmc_write(host, HIFMC100_DMA_LEN_SET(host->oobsize), 
			    HIFMC100_DMA_LEN);
	}

	hifmc_write(host, HIFMC100_OP_READ_DATE_EN(1) 
			  | HIFMC100_OP_WRITE_DATE_EN(1), HIFMC100_OP);

	hifmc_write(host, 
		HIFMC100_DMA_AHB_CTRL_DMA_PP_EN
		| HIFMC100_DMA_AHB_CTRL_BURST16_EN
		| HIFMC100_DMA_AHB_CTRL_BURST8_EN
		| HIFMC100_DMA_AHB_CTRL_BURST4_EN,
		HIFMC100_DMA_AHB_CTRL);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
		  | HIFMC100_OP_CFG_ADDR_NUM(host->addr_cycle);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	init_completion(&host->dma_done);

	/* enable dma done interrupt. */
	regval = hifmc_read(host, HIFMC100_INT_EN);
	regval |= HIFMC100_INT_EN_OP_DONE;
	hifmc_write(host, regval, HIFMC100_INT_EN);

	regval = HIFMC100_OP_CTRL_DMA_OP_READY;

	if (todev)
		regval |= HIFMC100_OP_CTRL_RW_OP(1);
#ifdef CONFIG_HIFMC100_OOB_READ
	else if (host->command == NAND_CMD_READOOB)
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

	dma_unmap_single(host->dev, phy_pageaddr, host->pagesize, direction);
	dma_unmap_single(host->dev, phy_oobaddr, host->oobsize, direction);
}
/*****************************************************************************/

void hifmc100_cmd_ctrl(struct mtd_info *mtd, int dat, unsigned int ctrl)
{
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
			addr_offset =
			    (host->addr_cycle - HIFMC100_ADDR_CYCLE_MASK) << 3;
			addr_value = 1;
		}

		host->addr_value[addr_value] |=
			((dat & 0xff) << addr_offset);

		host->addr_cycle++;
	}

	if ((ctrl & NAND_CLE) && (ctrl & NAND_CTRL_CHANGE)) {
#ifdef CONFIG_HIFMC100_NAND_CACHE_ENABLE
		unsigned int pageindex;
#endif /* CONFIG_HIFMC100_NAND_CACHE_ENABLE */

		host->command = dat & 0xff;
		if (host->page_status)
			host->page_status = 0;

		switch (host->command) {
		case NAND_CMD_PAGEPROG:
#ifdef CONFIG_HIFMC100_NAND_CACHE_ENABLE
			pageindex = GET_RW_PAGE_INDEX(host);

			hifmc_remove_cache(host->cache, pageindex, 1, 1,
				HIFMC_CACHE_REMOVE_CAUSE_WRITE);
#endif /* CONFIG_HIFMC100_NAND_CACHE_ENABLE */
			host->send_cmd_pageprog(host);

			hifmc100_dbg_write(host);

			break;

		case NAND_CMD_READSTART: {
#ifdef CONFIG_HIFMC100_NAND_CACHE_ENABLE
			int ret;
			char *pagebuf;
			char *oobbuf;
			int status;
			pageindex = GET_RW_PAGE_INDEX(host);

			ret = hifmc_read_cache(host->cache, pageindex,
				&pagebuf, &oobbuf, &status);

			if (status & HIFMC_CACHE_STATUS_EMPTY_PAGE) {
				host->page_status |= HIFMC100_PS_EMPTY_PAGE;
				break;
			}

			if (ret) {
				ret = hifmc_save_cache(host->cache, pageindex,
					&pagebuf, &oobbuf);

				host->pagebuf = ret ? host->fix_pagebuf : pagebuf;
#endif /* CONFIG_HIFMC100_NAND_CACHE_ENABLE */
#ifdef CONFIG_HIFMC100_OOB_READ
				/* In case READ OOB only. */
				if (host->addr_value[0] == host->pagesize) {
					host->command = NAND_CMD_READOOB;
				}
#endif /* CONFIG_HIFMC100_OOB_READ */
				host->send_cmd_readstart(host);
				hifmc100_dbg_read(host);

				if (IS_PS_UN_ECC(host) &&
				    !IS_PS_EMPTY_PAGE(host) &&
				    !IS_PS_BAD_BLOCK(host))
					mtd->ecc_stats.failed++;
#ifdef CONFIG_HIFMC100_NAND_CACHE_ENABLE
				if (!ret) {
					if (IS_PS_EMPTY_PAGE(host)) {
						hifmc_remove_cache(host->cache,
							pageindex, 1, 1,
							HIFMC_CACHE_REMOVE_CAUSE_EMPTY_PAGE);
						hifmc_set_cache_status(host->cache,
							pageindex, HIFMC_CACHE_STATUS_EMPTY_PAGE);

						host->pagebuf = NULL;
					} else {
						memcpy(oobbuf, host->oobbuf + HIFMC100_OOB_OFFSET,
							HIFMC100_OOB_SIZE);
						hifmc_cache_save_crc(host->cache, pageindex);
					}
				}

			} else {
				hifmc_cache_check_crc(host->cache, pageindex);
				host->pagebuf = pagebuf;
				memcpy(host->oobbuf + HIFMC100_OOB_OFFSET,
					oobbuf, HIFMC100_OOB_SIZE);
			}
#endif /* CONFIG_HIFMC100_NAND_CACHE_ENABLE */
			break;

		}
		case NAND_CMD_ERASE2:
#ifdef CONFIG_HIFMC100_NAND_CACHE_ENABLE
			pageindex = GET_ERASE_PAGE_INDEX(host);

			host->pagebuf = NULL;
			hifmc_remove_cache(host->cache, pageindex,
				host->page_per_block, 1,
				HIFMC_CACHE_REMOVE_CAUSE_ERASE);
#endif /* CONFIG_HIFMC100_NAND_CACHE_ENABLE */

			host->send_cmd_erase(host);
			hifmc100_dbg_erase(host);

			break;

		case NAND_CMD_READID:
			memset((unsigned char *)(chip->IO_ADDR_R), 0,
				READ_ID_LEN);
			host->send_cmd_readid(host);
			break;

		case NAND_CMD_STATUS:
			host->send_cmd_status(host);
			break;

		case NAND_CMD_SEQIN:
			host->pagebuf = host->fix_pagebuf;
			break;

		case NAND_CMD_ERASE1:
		case NAND_CMD_READ0:
			break;

		case NAND_CMD_RESET:
			host->send_cmd_reset(host, host->chipselect);
			break;

		default:
			break;
		}
	}

	if ((dat == NAND_CMD_NONE) && host->addr_cycle) {
		if (host->command == NAND_CMD_SEQIN
		    || host->command == NAND_CMD_READ0
		    || host->command == NAND_CMD_READID
		    || host->command == NAND_CMD_READOOB) {
			host->offset = 0x0;
			host->column = (host->addr_value[0] & 0xffff);
		}
	}
}
/*****************************************************************************/

static int hifmc100_send_cmd_pageprog(struct hifmc_host *host)
{
	if (*host->bbm != 0xFF && *host->bbm != 0x00)
		pr_warn("Attempt to write an invalid bbm. page: 0x%08x, mark: 0x%02x, current process(pid): %s(%d).\n",
			GET_RW_PAGE_INDEX(host), *host->bbm,
			current->comm, current->pid);

	host->enable_ecc_randomizer(host, ENABLE, ENABLE);

	/* clear ints */
	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	hifmc_write(host, host->addr_value[0] & 0xffff0000, HIFMC100_ADDRL);
	hifmc_write(host, host->addr_value[1], HIFMC100_ADDRH);
	hifmc_write(host,
		HIFMC100_CMD_CMD2(NAND_CMD_PAGEPROG) 
		| HIFMC100_CMD_CMD1(NAND_CMD_SEQIN),
		HIFMC100_CMD);

	*host->epm = 0x0000;

	hifmc100_dma_transfer(host, 1);

	return 0;
}
/*****************************************************************************/

static int hifmc100_get_data_status(struct hifmc_host *host)
{
	unsigned int page_status = 0;

	if (IS_PS_UN_ECC(host))
		page_status = HIFMC100_PS_UC_ECC;

	/* this is block start address */
	if (!((host->addr_value[0] >> 16) & host->block_page_mask)) {

		/* it is a bad block */
		if (*host->bbm == 0x00) {
			page_status |= HIFMC100_PS_BAD_BLOCK;
			goto out;
		}

		if (*host->bbm != 0xFF) {
			page_status |= HIFMC100_PS_BBM_ERROR;

			/*
			 * if there are more than 2 bits flipping, it is
			 * maybe a bad block
			 */
			if (!IS_PS_UN_ECC(host) || get_bits(*host->bbm) < 6) {
				page_status |= HIFMC100_PS_BAD_BLOCK;
				goto out;
			}
		}
	}

	if (*host->epm == 0x0000)
		goto out;

	if (*host->epm == 0xFFFF) {
		page_status |= HIFMC100_PS_EMPTY_PAGE;
		goto out;
	}

	page_status |= HIFMC100_PS_EPM_ERROR;

	if (IS_PS_UN_ECC(host) && get_bits(*host->epm) > 12) {
		page_status |= HIFMC100_PS_EMPTY_PAGE;
		goto out;
	}

out:
	return page_status;
}
/*****************************************************************************/

static int hifmc100_do_read_retry(struct hifmc_host *host)
{
	int ix;

	for (ix = 1; IS_PS_UN_ECC(host) && ix < host->read_retry->count; ix++) {

		hifmc_write(host, 
			    HIFMC100_INT_CLR_ERR_INVALID 
			    | HIFMC100_INT_CLR_ERR_VALID,
			    HIFMC100_INT_CLR);

		host->enable_ecc_randomizer(host, DISABLE, DISABLE);
		host->read_retry->set_rr_param(host, ix);

		/* enable ecc and randomizer */
		host->enable_ecc_randomizer(host, ENABLE, ENABLE);

		hifmc_write(host, 
				HIFMC100_INT_CLR_ERR_INVALID 
				| HIFMC100_INT_CLR_ERR_VALID,
			    HIFMC100_INT_CLR);
		hifmc_write(host, host->addr_value[0] & 0xffff0000,
			    HIFMC100_ADDRL);
		hifmc_write(host, host->addr_value[1], HIFMC100_ADDRH);
		hifmc_write(host,
				HIFMC100_CMD_CMD2(NAND_CMD_READSTART) 
			    	| HIFMC100_CMD_CMD1(NAND_CMD_READ0),
			    HIFMC100_CMD);

		hifmc100_dma_transfer(host, 0);

		if (hifmc_read(host, HIFMC100_INT) & HIFMC100_INT_CLR_ERR_VALID)
			host->page_status |= HIFMC100_PS_UC_ECC;
		else
			host->page_status &= ~HIFMC100_PS_UC_ECC;
	}

	host->page_status = hifmc100_get_data_status(host);

	hifmc100_dbg_read_retry(host, ix - 1);

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);
	host->read_retry->reset_rr_param(host);

	return 0;
}
/*****************************************************************************/

static int hifmc100_send_cmd_readstart(struct hifmc_host *host)
{
	host->enable_ecc_randomizer(host, ENABLE, ENABLE);

	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	hifmc_write(host, host->FMC_CFG, HIFMC100_CFG);
	hifmc_write(host, host->addr_value[0] & 0xffff0000, HIFMC100_ADDRL);
	hifmc_write(host, host->addr_value[1], HIFMC100_ADDRH);
	hifmc_write(host, HIFMC100_CMD_CMD2(NAND_CMD_READSTART) 
			  | HIFMC100_CMD_CMD1(NAND_CMD_READ0),
		    HIFMC100_CMD);

	hifmc100_dma_transfer(host, 0);

	if (hifmc_read(host, HIFMC100_INT) & HIFMC100_INT_ERR_INVALID)
		host->page_status |= HIFMC100_PS_UC_ECC;

	if (host->read_retry || IS_NAND_RANDOM(host)) {
		host->page_status |= hifmc100_get_data_status(host);

		if (IS_PS_EMPTY_PAGE(host)) {
			/* return 0xFF to MTD. */
		} else if (!IS_PS_BAD_BLOCK(host)) {
			/* if NAND chip support read retry */
			if (IS_PS_UN_ECC(host) && host->read_retry)
				hifmc100_do_read_retry(host);

		} /* 'else' NAND have a bad block, do nothing. */
	}

	if (!IS_PS_UN_ECC(host))
		host->ecc.dump(host, NULL, &host->ecc.max_bitsflap);
	else
		host->ecc.max_bitsflap = -1;

	return 0;
}
/*****************************************************************************/

static int hifmc100_send_cmd_erase(struct hifmc_host *host)
{
	u32 regval;

	/* Don't case the read retry config */
	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	hifmc_write(host, host->addr_value[0], HIFMC100_ADDRL);
	hifmc_write(host, HIFMC100_CMD_CMD2(NAND_CMD_ERASE2) 
			  | HIFMC100_CMD_CMD1(NAND_CMD_ERASE1),
		    HIFMC100_CMD);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(host->addr_cycle);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	/* need to config WAIT_READY_EN */
	regval = HIFMC100_OP_WAIT_READY_EN(1)
			| HIFMC100_OP_CMD1_EN(1)
			| HIFMC100_OP_CMD2_EN(1)
			| HIFMC100_OP_ADDR_EN(1)
			| HIFMC100_OP_REG_OP_START;

	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	return 0;
}
/*****************************************************************************/

static int hifmc100_send_cmd_readid(struct hifmc_host *host)
{
	u32 regval;

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(READ_ID_LEN), 
		    HIFMC100_DATA_NUM);
	hifmc_write(host, HIFMC100_CMD_CMD1(NAND_CMD_READID), HIFMC100_CMD);
	hifmc_write(host, READ_ID_ADDR, HIFMC100_ADDRL);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(READ_ID_ADDR_NUM);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	regval = HIFMC100_OP_CMD1_EN(1)
		 | HIFMC100_OP_ADDR_EN(1)
		 | HIFMC100_OP_READ_DATE_EN(1)
		 | HIFMC100_OP_REG_OP_START;

 	hifmc_write(host, regval, HIFMC100_OP);

	host->addr_cycle = 0x0;

	FMC_CMD_WAIT_CPU_FINISH(host);

	return 0;
}
/*****************************************************************************/

static int hifmc100_enable_ecc_randomizer(struct hifmc_host *host, int ecc_en,
					  int randomizer_en)
{
	u32 regval;

	if (IS_NAND_RANDOM(host)) {
		regval = hifmc_read(host, HIFMC100_GLOBAL_CFG);
		if (randomizer_en) {
			regval |= HIFMC100_GLOBAL_CFG_RANDOMIZER_EN;
		} else {
			regval &= ~HIFMC100_GLOBAL_CFG_RANDOMIZER_EN;
		}
		hifmc_write(host, regval, HIFMC100_GLOBAL_CFG);
	}

	regval = (ecc_en ? host->FMC_CFG : host->FMC_CFG_ECC_NONE);

	hifmc_write(host, regval, HIFMC100_CFG);

	return 0;
}
/*****************************************************************************/

static int hifmc100_send_cmd_status(struct hifmc_host *host)
{
	u32 regval;

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	hifmc_write(host, HIFMC100_DATA_NUM_CNT(MAX_NANDINFO_LEN), 
		    HIFMC100_DATA_NUM);
	hifmc_write(host, HIFMC100_CMD_CMD1(NAND_CMD_STATUS), HIFMC100_CMD);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	regval = HIFMC100_OP_CMD1_EN(1)
		| HIFMC100_OP_READ_DATE_EN(1)
		| HIFMC100_OP_READ_STATUS_EN(1)
		| HIFMC100_OP_REG_OP_START;

	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	return 0;
}
/*****************************************************************************/

static int hifmc100_send_cmd_reset(struct hifmc_host *host, int chipselect)
{
	u32 regval;

	hifmc_write(host, HIFMC100_CMD_CMD1(NAND_CMD_RESET), HIFMC100_CMD);

	hifmc_write(host, HIFMC100_OP_CFG_FM_CS(chipselect), 
		    HIFMC100_OP_CFG);

	regval = HIFMC100_OP_CMD1_EN(1)
		 | HIFMC100_OP_WAIT_READY_EN(1)
		 | HIFMC100_OP_REG_OP_START;

	hifmc_write(host, regval, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(host);

	return 0;
}
/*****************************************************************************/

int hifmc100_dev_ready(struct mtd_info *mtd)
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
		if (regval & NAND_STATUS_READY)
			return 1;

		udelay(1);

	} while (deadline--);

	PR_OUT("ERROR: nand wait ready timeout, status[%#x]\n", regval);

	return 0;
}
/*****************************************************************************/

void hifmc100_select_chip(struct mtd_info *mtd, int chipselect)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	if (chipselect < 0) {
#ifdef CONFIG_HIFMC100_NAND_CACHE_ENABLE
		if (host->cache)
			hifmc_read_cache_finish(host->cache);
#endif /* CONFIG_HIFMC100_NAND_CACHE_ENABLE */
		return;
	}

	if (chipselect > CONFIG_HIFMC100_NAND_MAX_CHIP)
		PR_OUT("invalid chipselect: %d\n", chipselect);

	host->chipselect = chipselect;
}
/*****************************************************************************/

uint8_t hifmc100_read_byte(struct mtd_info *mtd)
{
	int offset;
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	if (host->command == NAND_CMD_STATUS)
		return hifmc_read(host, HIFMC100_STATUS);

	host->offset++;

	if (host->command == NAND_CMD_READID)
		return readb(chip->IO_ADDR_R + host->offset - 1);

	if (IS_PS_EMPTY_PAGE(host))
		return 0xFF;

	offset = host->column + host->offset - 1;

	if (offset < host->pagesize)
		return readb(host->pagebuf + offset);
	else
		return readb(host->oobbuf + offset - host->pagesize);
}
/*****************************************************************************/

u16 hifmc100_read_word(struct mtd_info *mtd)
{
	int offset;
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	host->offset += 2;

	if (IS_PS_EMPTY_PAGE(host))
		return 0xFFFF;

	offset = host->column + host->offset - 2;

	if (offset < host->pagesize)
		return readw(host->pagebuf + offset);
	else
		return readw(host->oobbuf + offset - host->pagesize);
}
/*****************************************************************************/

void hifmc100_write_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	int offset;
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	offset = host->column + host->offset;

	if (offset >= host->pagesize)
		memcpy(host->oobbuf + offset - host->pagesize, buf, len);
	else if (offset + len <= host->pagesize)
		memcpy(host->pagebuf + offset, buf, len);
	else {
		int nr_copy = host->pagesize - offset;

		memcpy(host->pagebuf + offset, buf, nr_copy);
		memcpy(host->oobbuf, buf + nr_copy, len - nr_copy);
	}

	host->offset += len;
}
/*****************************************************************************/

void hifmc100_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	int offset;
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	if (IS_PS_EMPTY_PAGE(host)) {
		memset(buf, 0xFF, len);
		host->offset += len;
		return;
	}

	offset = host->column + host->offset;

	if (offset >= host->pagesize)
		memcpy(buf, host->oobbuf + offset - host->pagesize, len);
	else if (offset + len <= host->pagesize)
		memcpy(buf, host->pagebuf + offset, len);
	else {
		int nr_copy = host->pagesize - offset;

		memcpy(buf, host->pagebuf + offset, nr_copy);
		memcpy(buf + nr_copy, host->oobbuf, len - nr_copy);
	}

	host->offset += len;
}
/*****************************************************************************/

static unsigned int  nand_otp_len = 0;
static unsigned char nand_otp[128] = {0};

/* Get NAND parameter table. */
static int __init parse_nand_param(const struct tag *tag)
{
	if (tag->hdr.size <= 2)
		return 0;

	nand_otp_len = ((tag->hdr.size << 2) - sizeof(struct tag_header));

	if (nand_otp_len > sizeof(nand_otp)) {
		printk("%s(%d): Get Nand OTP from tag fail.\n",
			__FUNCTION__, __LINE__);
		return 0;
	}
	memcpy(nand_otp, &tag->u, nand_otp_len);
	return 0;
}
/* 0x48694E77 equal to fastoot ATAG_NAND_PARAM */
__tagtable(0x48694E77, parse_nand_param);
/*****************************************************************************/

int hifmc100_config_rw_latch(struct nand_chip *chip, unsigned int rw_latch)
{
	struct hifmc_host *host = chip->priv;

	/* set pwidth register */
	hifmc_write(host, rw_latch, HIFMC100_PND_PWIDTH_CFG);

	return 0;
}
/*****************************************************************************/

static int hifmc100_param_adjust(struct mtd_info *mtd, struct nand_chip *chip,
				 struct nand_dev_t *nand_dev)
{
	int ret = 0;
	int pagesize;
	int ecctype;
	int page_shift;
	u32 regval;
	char *start_type = "unknown";
	struct nand_ctrl_info_t *best = NULL;
	struct hifmc_host *host = chip->priv;
	struct hifmc_rw_latch *hifmc100_rw_latch;

	if (IS_NANDC_HW_AUTO(host))
		start_type = "HW-Auto";
	else
		start_type = "HW-Reg";

	pagesize = hifmc100_page_reg2type((host->FMC_CFG >> HIFMC100_PAGE_SIZE_SHIFT) & HIFMC100_PAGE_SIZE_MASK);
	ecctype = hifmc100_ecc_reg2type((host->FMC_CFG >> HIFMC100_ECC_TYPE_SHIFT) & HIFMC100_ECC_TYPE_MASK);
	best = hifmc100_force_ecc(mtd, pagesize, ecctype, start_type, 0);

#ifdef CONFIG_HIFMC100_NAND_PAGESIZE_AUTO_ECC_NONE
#  ifdef CONFIG_HIFMC100_NAND_AUTO_PAGESIZE_ECC
#  error you SHOULD NOT define CONFIG_HIFMC100_NAND_PAGESIZE_AUTO_ECC_NONE and CONFIG_HIFMC100_NAND_AUTO_PAGESIZE_ECC at the same time
#  endif
#  ifdef CONFIG_HIFMC100_NAND_HARDWARE_PAGESIZE_ECC
#  error you SHOULD NOT define CONFIG_HIFMC100_NAND_PAGESIZE_AUTO_ECC_NONE and CONFIG_HIFMC100_NAND_HARDWARE_PAGESIZE_ECC at the same time
#  endif

	best = hifmc100_force_ecc(mtd, mtd->writesize, NAND_ECC_NONE,
				  "force config", 0);
	start_type = "AutoForce";

#endif /* CONFIG_HIFMC100_NAND_PAGESIZE_AUTO_ECC_NONE */

	if (!best)
		PR_BUG(ERSTR_HARDWARE
			"Please configure Nand Flash pagesize and ecctype!\n");

	/* only in case fastboot check randomizer failed. 
	 * Update fastboot or configure hardware randomizer pin fix this problem.
	 */
	if (IS_NAND_RANDOM(nand_dev) && !(IS_NAND_RANDOM(host)))
		PR_BUG(ERSTR_HARDWARE "Hardware is not configure randomizer, but it is more suitable for this Nand Flash. "
			     "1. Please configure hardware randomizer PIN. "
			     "2. Please updata fastboot.\n");

	host->flags |= (IS_NAND_RANDOM(nand_dev) |
		IS_NAND_SYNC_ASYNC(nand_dev) |
		IS_NAND_ONLY_SYNC(nand_dev) |
		IS_NAND_ONFI(nand_dev));

	/* only for print nand info. */
	nand_dev->flags |= IS_NANDC_HW_AUTO(host);

	if (best->ecctype != NAND_ECC_NONE)
		mtd->oobsize = best->oobsize;
	chip->ecc.layout = best->layout;

	host->ecctype  = best->ecctype;
	host->pagesize = best->pagesize;
	host->oobsize  = mtd->oobsize;
	host->block_page_mask = ((mtd->erasesize / mtd->writesize) - 1);

	host->fix_pagebuf = kmalloc(host->pagesize, GFP_KERNEL);
	if (!host->fix_pagebuf) {
		PR_OUT("out of memory.\n");
		return -EIO;
	}

	host->fix_oobbuf = kmalloc(host->oobsize, GFP_KERNEL);
	if (!host->fix_oobbuf) {
		PR_OUT("out of memory.\n");
		return -EIO;
	}

	host->pagebuf = host->fix_pagebuf;
	host->oobbuf = host->fix_oobbuf;
	host->epm = (unsigned short *)(host->oobbuf
		+ chip->ecc.layout->oobfree[0].offset + HIFMC100_EPM_OFFSET);
	host->bbm = (unsigned char *)(host->oobbuf + HIFMC100_BB_OFFSET);

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

	if (mtd->writesize > NAND_MAX_PAGESIZE ||
	    mtd->oobsize > NAND_MAX_OOBSIZE) {
		PR_BUG(ERSTR_DRIVER
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
		PR_OUT("Nand divide into 1/%u\n", (1 << shift));
	}

	page_shift = ffs(host->pagesize) - 1;
	host->page_per_chip = chip->chipsize >> page_shift;
	host->page_per_block = mtd->erasesize >> page_shift;

	nand_dev->start_type = start_type;
	nand_dev->ecctype = host->ecctype;

	host->read_retry = NULL;
	if (nand_dev->read_retry_type != NAND_RR_NONE) {
		host->read_retry
		    = hifmc100_find_read_retry(nand_dev->read_retry_type);
		if (!host->read_retry) {
			PR_BUG(ERSTR_DRIVER "This Nand Flash need to enable the 'read retry' feature. "
				     "but the driver dose not offer the feature");
		}

		if (nand_otp_len) {
			memcpy(host->rr_data, nand_otp, nand_otp_len);
		}
	}

	/*
	 * If it want to support the 'read retry' feature, the 'randomizer'
	 * feature must be support first.
	 */
	if (host->read_retry && !IS_NAND_RANDOM(host)) {
		pr_err(ERSTR_HARDWARE "This Nand flash need to enable 'randomizer' feature. "
			     "Please configure hardware randomizer PIN.");
	}

	if (hifmc100_ecc_info_init(host))
		pr_err(ERSTR_DRIVER "No found ecc dump function. pagesize:%d ecctype:%d.",
			host->pagesize, host->ecctype);

	hifmc100_rw_latch = get_hifmc_rw_latch(nand_dev->ids);
	if (!hifmc100_rw_latch) {
		pr_err(ERSTR_DRIVER
			     "RW Latch table is not implemented.\n");
	}
	hifmc100_config_rw_latch(chip, hifmc100_rw_latch->rw_latch);

	host->dbgfs_root = debugfs_create_dir("nand", NULL);
	if (!host->dbgfs_root) {
		pr_err("Can't create debugfs 'nand' dir.\n");
		return -ENOENT;
	}
#ifdef CONFIG_HIFMC100_NAND_CACHE_ENABLE
	ret = hifmc_cache_init(&host->cache,
		host->page_per_chip, host->page_per_chip,
		host->pagesize, HIFMC100_OOB_SIZE, host->dbgfs_root);
	if (ret)
		PR_OUT(ERSTR_DRIVER "cache module init fail.");
#endif /* CONFIG_HIFMC100_NAND_CACHE_ENABLE */

	if (hifmc100_dbg_init(host))
		PR_OUT(ERSTR_DRIVER "create debugfs fail.");

	return ret;
}
/*****************************************************************************/

int hifmc100_nand_init(struct hifmc_host *host, struct nand_chip *chip)
{
	u32 regval;
	host->version = hifmc_read(host, HIFMC100_VERSION);
	host->enable(host, ENABLE);

	host->addr_cycle    = 0;
	host->addr_value[0] = 0;
	host->addr_value[1] = 0;
	host->chipselect    = 0;

	host->send_cmd_pageprog = hifmc100_send_cmd_pageprog;
	host->send_cmd_readstart = hifmc100_send_cmd_readstart;
	host->send_cmd_erase  = hifmc100_send_cmd_erase;
	host->send_cmd_readid = hifmc100_send_cmd_readid;
	host->send_cmd_status = hifmc100_send_cmd_status;
	host->send_cmd_reset  = hifmc100_send_cmd_reset;

	host->flags = 0;

	regval = hifmc_read(host, HIFMC100_GLOBAL_CFG);
	if (regval & HIFMC100_GLOBAL_CFG_RANDOMIZER_EN)
		host->flags |= NAND_RANDOMIZER;

	regval = hifmc_read(host, HIFMC100_CFG);
	host->FMC_CFG = regval | HIFMC100_CFG_OP_MODE(HIFMC100_OP_MODE_NORMAL);

	host->FMC_CFG_ECC_NONE = host->FMC_CFG & 
			(~(HIFMC100_ECC_TYPE_MASK << HIFMC100_ECC_TYPE_SHIFT));

	hifmc_write(host,
		(SET_HIFMC100_PWIDTH(CONFIG_HIFMC100_W_LATCH,
				     CONFIG_HIFMC100_R_LATCH,
				     CONFIG_HIFMC100_RW_LATCH)),
		HIFMC100_PND_PWIDTH_CFG);

	hifmc_write(host, 0, HIFMC100_DMA_SADDR_OOB);
	hifmc_write(host, 0, HIFMC100_DMA_SADDR_D0);
	hifmc_write(host, 0, HIFMC100_DMA_SADDR_D1);
	hifmc_write(host, 0, HIFMC100_DMA_SADDR_D2);
	hifmc_write(host, 0, HIFMC100_DMA_SADDR_D3);

	host->flags |= NANDC_HW_AUTO;

	host->enable_ecc_randomizer = hifmc100_enable_ecc_randomizer;
	hinfc_param_adjust = hifmc100_param_adjust;

	return 0;
}
/******************************************************************************/

int hifmc100_nand_destory(struct hifmc_host *host)
{
	if (host->fix_pagebuf) {
		kfree(host->fix_pagebuf);
		host->fix_pagebuf = NULL;
	}

	if (host->fix_oobbuf) {
		kfree(host->fix_oobbuf);
		host->fix_pagebuf = NULL;
	}
#ifdef CONFIG_HIFMC100_NAND_CACHE_ENABLE 
	if (host->cache) {
		hifmc_cache_destory(host->cache);
		host->cache = NULL;
	}
#endif /* CONFIG_HIFMC100_NAND_CACHE_ENABLE */
	return 0;
}
