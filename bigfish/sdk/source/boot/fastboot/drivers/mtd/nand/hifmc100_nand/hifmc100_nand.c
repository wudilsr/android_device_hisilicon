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

#include "hifmc100_nand.h"
#include "../hifmc100_nand_gen.h"
#include "hifmc100_rw_latch.h"
#include "hifmc100_read_retry.h"
#include "hifmc100_ecc_info.h"

#ifdef CONFIG_ARCH_HI3716MV410
	#include "hifmc100_nand_hi3716mv410.c"
#endif

static struct hifmc_host fmc_host = {
	.chip = NULL,
};

extern void nand_spl_ids_register(void);
extern int nand_get_device(struct nand_chip *chip, struct mtd_info *mtd, 
			   int new_state);
extern void nand_release_device(struct mtd_info *mtd);

/*****************************************************************************/
//#define CONFIG_HIFMC100_OOB_READ    /* enable OOB-ONLY READ MODE support. */
//#define CONFIG_HIFMC100_BULK_READ   /* enable BULK READ MODE support. */
//#define CONFIG_HIFMC100_CACHE_READ  /* enable CACHE READ MODE support. */

/*****************************************************************************/
static void nand_register_dump(void)
{
	int ix;
	u32 regbase = CONFIG_HIFMC100_REG_BASE_ADDRESS;

	printf("Register dump:");
	for (ix = 0; ix <= 0xDC; ix += 0x04) {
		if (!(ix & 0x0F))
			printf("\n0x%08X: ", (regbase + ix));
		printf("%08X ", readl(regbase + ix));
	}
	printf("\n");
}

/*****************************************************************************/
static unsigned int get_8bits(unsigned char byte)
{
	int ix = 0;
	int num = 0;

	if (byte == 0xFF) return 8;
	if (!byte) return 0;

	while (ix++ < 8) {
		if ((byte & 1))
			num++;
		byte = (byte >> 1);
	}
	return num;
}
/*****************************************************************************/

static unsigned int get_16bits(unsigned short byte)
{
	int ix = 0;
	int num = 0;

	if (byte == 0xFFFF) return 16;
	if (!byte) return 0;

	while (ix++ < 16) {
		if ((byte & 1))
			num++;
		byte = (byte >> 1);
	}
	return num;
}

/*****************************************************************************/

static void hifmc100_dma_transfer(struct hifmc_host *host, int todev)
{
	u32 regval;
	struct nand_chip *chip = host->chip;
	struct mtd_info *mtd = host->mtd;
	u32 dma_buffer, dma_oob;

	if (host->ecctype == NAND_ECC_NONE) {
		hifmc_write(host, HIFMC100_DMA_LEN_SET(host->oobsize), 
			    HIFMC100_DMA_LEN);
	}
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
		if (chip->ops.rmode.pagenum > (host->block_page_mask + 1)) {
			PR_BUG("Cache read len(0x%x) is invalid, max is 0x%x.\n",
				chip->ops.rmode.pagenum * host->pagesize,
				mtd->erasesize);
		}

		/* cache read use continuous mode default, not use DISPERSE mode. */
		regval = (HIFMC100_EXIT_CACHE_OP_EN
			| HIFMC100_CACHE_MEM_SADDR_SEL(HIFMC100_CACHE_MEM_SADDR_SEL_CONTINOUS)
			| HIFMC100_CACHE_PAGE_NUM(chip->ops.rmode.pagenum));

		hifmc_write(host, regval, HIFMC100_CACHE_CTRL);

		dma_buffer = (u32)host->cache_read_pagebuf;
		dma_oob    = (u32)host->cache_read_oobbuf;
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

	hifmc_write(host, 
		HIFMC100_DMA_AHB_CTRL_DMA_PP_EN
		| HIFMC100_DMA_AHB_CTRL_BURST16_EN
		| HIFMC100_DMA_AHB_CTRL_BURST8_EN
		| HIFMC100_DMA_AHB_CTRL_BURST4_EN,
		HIFMC100_DMA_AHB_CTRL);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
		  | HIFMC100_OP_CFG_ADDR_NUM(host->addr_cycle);
	hifmc_write(host, regval, HIFMC100_OP_CFG);
	
	regval = HIFMC100_OP_CTRL_DMA_OP_READY;

	if (todev)
		regval |= HIFMC100_OP_CTRL_RW_OP(1);
#ifdef CONFIG_HIFMC100_OOB_READ
	else if (host->command == NAND_CMD_READOOB)
		regval |= HIFMC100_OP_CTRL_RD_OP_SEL(HIFMC100_OP_CTRL_READOOB);
#endif /* CONFIG_HIFMC100_OOB_READ */
#if (defined CONFIG_HIFMC100_CACHE_READ || defined CONFIG_HIFMC100_BULK_READ)
	else {
		u32 read_type = chip->ops.rmode.mode;
		regval |= HIFMC100_OP_CTRL_RD_OP_SEL(read_type);
	}
#endif /* (defined CONFIG_HIFMC100_CACHE_READ || defined CONFIG_HIFMC100_BULK_READ) */

	hifmc_write(host, regval, HIFMC100_OP_CTRL);

	chip->ops.rmode.mode = MTD_READ_PAGE;

	FMC_DMA_WAIT_INT_FINISH(host);

}

/*****************************************************************************/
static int hifmc100_send_cmd_pageprog(struct hifmc_host *host)
{
	if (*host->bbm != 0xFF && *host->bbm != 0x00)
		printf("WARNING: attempt to write an invalid bbm. "
		       "page: 0x%08x, mark: 0x%02x,\n",
		       GET_PAGE_INDEX(host), *host->bbm);

	host->enable_ecc_randomizer(host, ENABLE, ENABLE);

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
			if (!IS_PS_UN_ECC(host) || get_8bits(*host->bbm) < 6) {
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

	if (IS_PS_UN_ECC(host) && get_16bits(*host->epm) > 12) {
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
			    HIFMC_CMD_SEQ(NAND_CMD_READ0, NAND_CMD_READSTART),
			    HIFMC100_CMD);

		hifmc100_dma_transfer(host, 0);

		if (hifmc_read(host, HIFMC100_INT) & HIFMC100_INT_CLR_ERR_VALID)
			host->page_status |= HIFMC100_PS_UC_ECC;
		else
			host->page_status &= ~HIFMC100_PS_UC_ECC;
	}

#ifdef CONFIG_NAND_NOTICE_RR
	printf("\nPage %d Do RR(%d/%d) %s.\n", GET_PAGE_INDEX(host),
	       ix-1, host->read_retry->count, (IS_PS_UN_ECC(host) ? "Fail" : "Success"));
#endif

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);
	host->read_retry->reset_rr_param(host);

	return 0;
}
/*****************************************************************************/
static int hifmc100_read_raw_data(struct hifmc_host *host, int page, int offset,
				  unsigned int size)
{
	u32 regval;
	struct nand_chip *chip = host->chip;

	memset((char *)chip->IO_ADDR_R, 0, size);

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	hifmc_write(host, HIFMC100_INT_CLR_ALL, HIFMC100_INT_CLR);

	host->addr_cycle = 4;
	host->addr_value[0] = (offset & 0xFFFF) | ((page & 0xFFFF) << 16);

	if (chip->chipsize > (128 << 20)) {
		host->addr_value[1] = (page >> 16) & 0xFF;
		host->addr_cycle++;
	} else {
		host->addr_value[1] = 0;
	}

	hifmc_write(host, host->addr_value[0], HIFMC100_ADDRL);
	hifmc_write(host, host->addr_value[1], HIFMC100_ADDRH);
	hifmc_write(host, NAND_CMD_READSTART << 8 | NAND_CMD_READ0,
		HIFMC100_CMD);

	hifmc_write(host, size, HIFMC100_DATA_NUM);
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(host->addr_cycle);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	regval = HIFMC100_OP_CMD1_EN(1)
		 | HIFMC100_OP_CMD2_EN(1)
		 | HIFMC100_OP_ADDR_EN(1)
		 | HIFMC100_OP_WAIT_READY_EN(1)
		 | HIFMC100_OP_READ_DATE_EN(1)
		 | HIFMC100_OP_REG_OP_START;

	hifmc_write(host, regval, HIFMC100_OP);

	host->addr_cycle = 0x0;

	FMC_CMD_WAIT_CPU_FINISH(host);

	return 0;
}
/*****************************************************************************/

static int hifmc100_send_cmd_readstart(struct hifmc_host *host)
{
	if ((host->addr_value[0] == host->cache_addr_value[0])
		&& (host->addr_value[1] == host->cache_addr_value[1]))
		return 0;

	host->page_status = 0;

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
			/*
			 * oob area used by yaffs2 only 32 bytes,
			 * so we only fill 32 bytes.
			 */
			if (IS_NAND_RANDOM(host))
				memset(host->buffer, 0xFF,
				       host->pagesize + host->oobsize);

		} else if (!IS_PS_BAD_BLOCK(host)) {
			/* if NAND chip support read retry */
			if (IS_PS_UN_ECC(host) && host->read_retry)
				hifmc100_do_read_retry(host);

		} /* 'else' NAND have a bad block, do nothing. */
	}

	host->cache_addr_value[0] = host->addr_value[0];
	host->cache_addr_value[1] = host->addr_value[1];

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
static u8 hifmc100_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	host->offset++;

	if (host->command == NAND_CMD_READID)
		return readb(chip->IO_ADDR_R + host->offset - 1);

	if (host->command == NAND_CMD_STATUS)
		return hifmc_read(host, HIFMC100_STATUS);

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

	memcpy(host->buffer + host->column + host->offset, buf, len);
	host->offset += len;
}

/*****************************************************************************/
static void hifmc100_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;

	memcpy(buf, host->buffer + host->column + host->offset, len);
	host->offset += len;
}

/*****************************************************************************/
#if (defined CONFIG_HIFMC100_BULK_READ || defined CONFIG_HIFMC100_CACHE_READ)
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
#endif /* (defined CONFIG_HIFMC100_BULK_READ || defined CONFIG_HIFMC100_CACHE_READ) */

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
			host->send_cmd_status(host);
			break;

		case NAND_CMD_SEQIN:
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

	/* pass pagesize and ecctype to kernel when startup. */
	host->enable_ecc_randomizer(host, ENABLE, ENABLE);

	if ((dat == NAND_CMD_NONE) && host->addr_cycle) {
		if (host->command == NAND_CMD_SEQIN
		    || host->command == NAND_CMD_READ0
		    || host->command == NAND_CMD_READID
		    || host->command == NAND_CMD_READOOB) {
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
		if (regval & NAND_STATUS_READY)
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

#ifndef CONFIG_SUPPORT_YAFFS
static struct nand_ecclayout nand_ecc_2k16bit =
{
	.oobfree = {{2, 6}}
};
#endif

/*****************************************************************************/
/* ecc/pagesize get from CPU PIN. */
static struct nand_config_table hifmc100_nand_hw_pin_config_table[] =
{
	{NAND_PAGE_16K, NAND_ECC_64BIT, 1824/*1824*/, &nand_ecc_default},
	{NAND_PAGE_16K, NAND_ECC_40BIT, 1152/*1152*/, &nand_ecc_default},
	{NAND_PAGE_16K, NAND_ECC_NONE,  32 ,          &nand_ecc_default},

	{NAND_PAGE_8K, NAND_ECC_64BIT, 928 /*928*/,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_40BIT, 592 /*592 */,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_24BIT, 368 /*368*/,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{NAND_PAGE_4K, NAND_ECC_24BIT, 200 /*200*/,  &nand_ecc_default},
#ifndef CONFIG_SUPPORT_YAFFS
	{NAND_PAGE_4K, NAND_ECC_16BIT, 128 /*128*/,  &nand_ecc_2k16bit},
#endif
	{NAND_PAGE_4K, NAND_ECC_8BIT,  88  /*88*/,   &nand_ecc_default},
	{NAND_PAGE_4K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{NAND_PAGE_2K, NAND_ECC_24BIT, 116 /*116*/, &nand_ecc_default},
#ifndef CONFIG_SUPPORT_YAFFS
	{NAND_PAGE_2K, NAND_ECC_16BIT, 64  /*64*/,  &nand_ecc_2k16bit},
#endif
	{NAND_PAGE_2K, NAND_ECC_8BIT,  60  /*60*/,  &nand_ecc_default},
	{NAND_PAGE_2K, NAND_ECC_NONE,  32,          &nand_ecc_default},

	{0,0,0,NULL},
};
/*****************************************************************************/
/* ecc/pagesize get from NAND controller */
static struct nand_config_table hifmc100_nand_hw_auto_config_table[] =
{
	{NAND_PAGE_16K, NAND_ECC_64BIT, 1824/*1824*/, &nand_ecc_default},
	{NAND_PAGE_16K, NAND_ECC_40BIT, 1152/*1152*/, &nand_ecc_default},
	{NAND_PAGE_16K, NAND_ECC_NONE,  32 ,          &nand_ecc_default},

	{NAND_PAGE_8K, NAND_ECC_64BIT, 928 /*928*/,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_40BIT, 592 /*592*/,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_24BIT, 368 /*368*/,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{NAND_PAGE_4K, NAND_ECC_24BIT, 200 /*200*/,  &nand_ecc_default},
#ifndef CONFIG_SUPPORT_YAFFS
	{NAND_PAGE_4K, NAND_ECC_16BIT,  128 /*128*/,  &nand_ecc_2k16bit},
#endif
	{NAND_PAGE_4K, NAND_ECC_8BIT,  88 /*88*/,    &nand_ecc_default},
	{NAND_PAGE_4K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{NAND_PAGE_2K, NAND_ECC_24BIT, 116 /*116*/, &nand_ecc_default},
#ifndef CONFIG_SUPPORT_YAFFS
	{NAND_PAGE_2K, NAND_ECC_16BIT,  64 /*64*/, &nand_ecc_2k16bit},
#endif
	{NAND_PAGE_2K, NAND_ECC_8BIT,  60  /*60*/,  &nand_ecc_default},
	{NAND_PAGE_2K, NAND_ECC_NONE,  32,          &nand_ecc_default},

	{0,0,0,NULL},
};
/*****************************************************************************/
/* ecc/pagesize get from NAND id */
static struct nand_config_table hifmc100_nand_soft_auto_config_table[] =
{
	{NAND_PAGE_16K, NAND_ECC_64BIT, 1824/*1824*/, &nand_ecc_default},
	{NAND_PAGE_16K, NAND_ECC_40BIT, 1152/*1152*/, &nand_ecc_default},
	{NAND_PAGE_16K, NAND_ECC_NONE,  32 ,          &nand_ecc_default},

	{NAND_PAGE_8K, NAND_ECC_64BIT, 928 /*928*/,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_40BIT, 592 /*592*/,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_28BIT, 432 /*432*/,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_24BIT, 368 /*368*/,  &nand_ecc_default},
	{NAND_PAGE_8K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{NAND_PAGE_4K, NAND_ECC_28BIT, 232 /*232*/,  &nand_ecc_default},
	{NAND_PAGE_4K, NAND_ECC_24BIT, 200 /*200*/,  &nand_ecc_default},
#ifndef CONFIG_SUPPORT_YAFFS
	{NAND_PAGE_4K, NAND_ECC_16BIT,  128 /*128*/,  &nand_ecc_2k16bit},
#endif
	{NAND_PAGE_4K, NAND_ECC_8BIT,  88 /*88*/,    &nand_ecc_default},
	{NAND_PAGE_4K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{NAND_PAGE_2K, NAND_ECC_28BIT, 132 /*132*/, &nand_ecc_default},
	{NAND_PAGE_2K, NAND_ECC_24BIT, 116 /*116*/, &nand_ecc_default},
#ifndef CONFIG_SUPPORT_YAFFS
	{NAND_PAGE_2K, NAND_ECC_16BIT,  64 /*64*/, &nand_ecc_2k16bit},
#endif
	{NAND_PAGE_2K, NAND_ECC_8BIT,  60  /*60*/,  &nand_ecc_default},
	{NAND_PAGE_2K, NAND_ECC_NONE,  32,          &nand_ecc_default},

	{0,0,0,NULL},
};
/*****************************************************************************/
/*
 *  0 - This NAND NOT support randomizer
 *  1 - This NAND support randomizer.
 */
static int hifmc100_nand_support_randomizer(unsigned int pageisze,
				       unsigned int ecctype)
{
	switch (pageisze) {
	case _8K:
		return (ecctype >= NAND_ECC_24BIT && ecctype <= NAND_ECC_80BIT);
	case _16K:
		return (ecctype >= NAND_ECC_40BIT && ecctype <= NAND_ECC_80BIT);
	case _32K:
		return (ecctype >= NAND_ECC_40BIT && ecctype <= NAND_ECC_80BIT);
	/* in case pagesize < 8K, randomizer is auto disabled by controler. */
	default:
		return 1;
	}
}

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
		PR_BUG(ERSTR_DRIVER
		       "Driver does not support the pagesize(%d) "
		       "and oobsize(%d).\n",
		       mtd->writesize, mtd->oobsize);

	return best;
}

/*****************************************************************************/

static int hifmc100_check_config(struct hifmc_host *host,
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
		(host->FMC_CFG & HIFMC100_ECC_TYPE_MASK) 
		 >> HIFMC100_ECC_TYPE_SHIFT);

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

	if (IS_NAND_RANDOM(nand_dev) && !IS_NAND_RANDOM(host)) {
		if (is_hw_auto) {
			PR_BUG("Hardware is not configure randomizer, "
				"but it is more suitable for this Nand Flash. "
				"Update fastboot will resolve this problem.\n");
		} else {
			PR_BUG("Hardware is not configure randomizer, "
				"but it is more suitable for this Nand Flash. "
				"Modify hardware pin will resolve this problem.\n");
		}
	}

	return 0;
}

/*****************************************************************************/

int hifmc100_config_rw_latch(struct nand_chip *chip, unsigned int rw_latch)
{
	struct hifmc_host *host = chip->priv;

	/* set pwidth register */
	hifmc_write(host, rw_latch, HIFMC100_PND_PWIDTH_CFG);

	return 0;
}
/*****************************************************************************/
#if defined (CONFIG_HIFMC100_PAGESIZE_AUTO_ECC_NONE)
/* force the pagesize and ecctype */
static struct nand_config_table *
hifmc100_force_ecc(struct nand_config_table *config, struct mtd_info *mtd, 
		   int pagetype, int ecctype, char *cfgmsg, int allow_pagediv)
{
	int pagesize;
	struct nand_config_table *fit = NULL;

	for (; config->layout; info++) {
		if (config->pagetype == pagetype && info->ecctype == ecctype) {
			fit = config;
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
#endif /* CONFIG_HIFMC100_PAGESIZE_AUTO_ECC_NONE */
/*****************************************************************************/

static void hifmc100_chip_adjust(struct nand_chip *chip, unsigned char manf)
{
	if ((manf != NAND_MFR_TOSHIBA)
		&& (manf != NAND_MFR_SAMSUNG)
		&& (manf != NAND_MFR_HYNIX)
		&& (manf != NAND_MFR_MICRON)) {

		chip->block_bad = hifmc100_nand_block_bad;

		chip->options |= (NAND_BBT_2ND_PAGE | NAND_BBT_LAST_PAGE);
	}
}
/*****************************************************************************/

static int hifmc100_param_adjust(struct mtd_info *mtd, struct nand_chip *chip,
				 struct nand_dev_t *nand_dev)
{
	int regval;
	char *start_type = "unknown";
	struct nand_config_table *best = NULL;
	struct nand_config_table *config = NULL;
	struct hifmc_host *host = chip->priv;
	struct hifmc_rw_latch *hifmc100_rw_latch;

	if (get_bootmedia(NULL, NULL) == BOOT_MEDIA_NAND) {
		if (IS_NANDC_HW_AUTO(host)) {
			config = hifmc100_nand_hw_auto_config_table;

			start_type = "HW-Auto";
			best = hifmc100_get_best_ecc(config, mtd);
			if (IS_NANDC_CONFIG_DONE(host))
				hifmc100_check_config(host, nand_dev, best, 1);
			else if (!IS_NAND_RANDOM(nand_dev) && IS_NAND_RANDOM(host))
				host->flags &= ~NAND_RANDOMIZER;
		} else {
			config = hifmc100_nand_hw_pin_config_table;
			start_type = "HW-Pin";
			best = hifmc100_get_best_ecc(config, mtd);
			hifmc100_check_config(host, nand_dev, best, 0);
		}
	} else {
		config = hifmc100_nand_soft_auto_config_table;
		start_type = "Soft-Auto";
		best = hifmc100_get_best_ecc(config, mtd);
		if (!IS_NAND_RANDOM(nand_dev) && IS_NAND_RANDOM(host))
			host->flags &= ~NAND_RANDOMIZER;
	}

	host->flags |= IS_NAND_RANDOM(nand_dev); 

	nand_dev->flags |= (IS_NANDC_HW_AUTO(host) |
			    IS_NANDC_CONFIG_DONE(host)); 

#ifdef CONFIG_HIFMC100_PAGESIZE_AUTO_ECC_NONE
	{
		int pagetype = nandpage_size2type(mtd->writesize);
		int ecctype = NAND_ECC_NONE;
		best = hifmc100_force_ecc(config, mtd, pagetype, ecctype,
			"force config", 0);
		start_type = "NoECC";
	}
#endif /* CONFIG_HIFMC100_PAGESIZE_AUTO_ECC_NONE */

	if (!best)
		PR_BUG(ERSTR_HARDWARE
		        "Please configure Nand Flash pagesize and ecctype!\n");

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

	memset((char *)chip->IO_ADDR_R, 0xff,
	       HIFMC100_NAND_BUFFER_BASE_ADDRESS_LEN);
	memset(host->buffer, 0xff, (host->pagesize + host->oobsize));

	host->dma_oob = host->dma_buffer + host->pagesize;
	host->bbm = (unsigned char *)(host->buffer
		+ host->pagesize + HIFMC100_BAD_BLOCK_POS);

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

	regval = ~(HIFMC100_PAGE_SIZE_MASK << HIFMC100_PAGE_SIZE_SHIFT);
	host->FMC_CFG &= regval;
	host->FMC_CFG_ECC_NONE &= regval;
	regval = (hifmc100_nand_page_type2reg(best->pagetype)
		& HIFMC100_PAGE_SIZE_MASK) << HIFMC100_PAGE_SIZE_SHIFT;
	host->FMC_CFG |= regval;
	host->FMC_CFG_ECC_NONE |= regval;

	regval = ~(HIFMC100_ECC_TYPE_MASK << HIFMC100_ECC_TYPE_SHIFT);
	host->FMC_CFG &= regval;
	host->FMC_CFG_ECC_NONE &= regval;
	regval = (hifmc100_nand_ecc_type2reg(best->ecctype)
		& HIFMC100_ECC_TYPE_MASK) << HIFMC100_ECC_TYPE_SHIFT;
	host->FMC_CFG |= regval;

	/* pass pagesize and ecctype to kernel when spiflash startup. */
	host->enable_ecc_randomizer(host, ENABLE, ENABLE);

	if (mtd->writesize > NAND_MAX_PAGESIZE ||
	    mtd->oobsize > NAND_MAX_OOBSIZE) {
		PR_BUG(ERSTR_DRIVER
			"Driver does not support this Nand Flash. "
			"Please increase NAND_MAX_PAGESIZE and NAND_MAX_OOBSIZE.\n");
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
		printk("Nand divide into 1/%u\n", (1 << shift));
	}

	nand_dev->start_type = start_type;
	nand_dev->ecctype = host->ecctype;

	host->read_retry = NULL;
	if (nand_dev->read_retry_type != NAND_RR_NONE) {
		host->read_retry
			= hifmc100_find_read_retry(nand_dev->read_retry_type);
		if (!host->read_retry) {
			PR_BUG(ERSTR_DRIVER
				"This Nand Flash need to enable the 'read retry' feature. "
				"But the driver dose not offer the feature");
		}
	}

	/*
	 * If it want to support the 'read retry' feature, the 'randomizer'
	 * feature must be support first.
	 */
	if (host->read_retry && !IS_NAND_RANDOM(host)) {
		PR_BUG(ERSTR_HARDWARE
			"This Nand flash need to enable 'randomizer' feature. "
			"Please configure hardware randomizer PIN.");
	}

	/*
	 * Check if hardware enable randomizer PIN, But NAND does not need
	 * randomizer. We will notice user.
	 */
	if (IS_NAND_RANDOM(host) &&
	    !hifmc100_nand_support_randomizer(host->pagesize, host->ecctype))
		PR_BUG(ERSTR_HARDWARE
			"This NAND flash does not support `randomizer`, "
			"Please don't configure hardware randomizer PIN.");

	if (hifmc100_ecc_info_init(host))
		PR_BUG(ERSTR_DRIVER "No found ecc dump function.");

	hifmc100_rw_latch = get_hifmc_rw_latch(nand_dev->ids);
	if (!hifmc100_rw_latch) {
		PR_BUG(ERSTR_DRIVER
			"RW Latch table is not implemented.\n");
	}
	hifmc100_config_rw_latch(chip, hifmc100_rw_latch->rw_latch);

	hifmc100_chip_adjust(chip, nand_dev->ids[0]);

	nand_dev->hostver = HIFMC_VER_100;

	return 0;
}

/*****************************************************************************/
int hifmc100_nand_host_init(struct hifmc_host *host, struct nand_chip *chip)
{
	u32 regval, flash_type;
	
	regval = hifmc_read(host, HIFMC100_CFG);
	flash_type = (regval & HIFMC100_FLASH_SEL_MASK) 
		      >> HIFMC100_FLASH_SEL_SHIFT;
	if (flash_type != HIFMC100_FLASH_TYPE_NAND) {
		PR_OUT("ERROR: Flash type[%d] check failed!\n", flash_type);
		return -ENODEV;
	}

	if ((regval & HIFMC100_OP_MODE_MASK) == HIFMC100_OP_MODE_BOOT)
		regval |= HIFMC100_CFG_OP_MODE(HIFMC100_OP_MODE_NORMAL);

	hifmc_write(host, regval, HIFMC100_CFG);

	host->FMC_CFG = regval;
	host->FMC_CFG_ECC_NONE = host->FMC_CFG & (~(HIFMC100_ECC_TYPE_MASK 
					   	   << HIFMC100_ECC_TYPE_SHIFT));

	/* enable LP control. */
	regval = hifmc_read(host, HIFMC100_LP_CTRL);
	regval |= HIFMC100_CLK_GATE_EN;
	hifmc_write(host, regval, HIFMC100_LP_CTRL);

	chip->priv        = host;
	chip->cmd_ctrl    = hifmc100_cmd_ctrl;
	chip->dev_ready   = hifmc100_dev_ready;
	chip->select_chip = hifmc100_select_chip;
	chip->read_byte   = hifmc100_read_byte;
	chip->read_word   = hifmc100_read_word;
	chip->write_buf   = hifmc100_write_buf;
	chip->read_buf    = hifmc100_read_buf;

#if (defined CONFIG_HIFMC100_BULK_READ || defined CONFIG_HIFMC100_CACHE_READ)
	chip->cache_read_buf = hifmc100_cache_read_buf;
#endif /* defined CONFIG_HIFMC100_BULK_READ || defined CONFIG_HIFMC100_CACHE_READ */

	chip->chip_delay  = HIFMC100_CHIP_DELAY;
	chip->options     = NAND_NO_AUTOINCR | NAND_BBT_SCANNED;

	chip->ecc.layout  = NULL;
	chip->ecc.mode    = NAND_ECC_NONE;

	host->chip          = chip;
	host->addr_cycle    = 0;
	host->addr_value[0] = 0;
	host->addr_value[1] = 0;
	host->cache_addr_value[0] = ~0;
	host->cache_addr_value[1] = ~0;
	host->chipselect    = 0;
	
	host->send_cmd_pageprog  = hifmc100_send_cmd_pageprog;
	host->send_cmd_status    = hifmc100_send_cmd_status;
	host->send_cmd_readstart = hifmc100_send_cmd_readstart;
	host->send_cmd_erase     = hifmc100_send_cmd_erase;
	host->send_cmd_readid    = hifmc100_send_cmd_readid;
	host->send_cmd_reset     = hifmc100_send_cmd_reset;
	
	host->flags = 0;
	host->version = hifmc_read(host, HIFMC100_VERSION);
	
	hifmc_write(host,
			HIFMC100_PND_PWIDTH_CFG_RW_HCNT(HIFMC100_NAND_RW_LATCH)
			| HIFMC100_PND_PWIDTH_CFG_R_LCNT(HIFMC100_NAND_R_LATCH)
			| HIFMC100_PND_PWIDTH_CFG_W_LCNT(HIFMC100_NAND_W_LATCH), 
		    HIFMC100_PND_PWIDTH_CFG);

	regval = hifmc_read(host, HIFMC100_GLOBAL_CFG);
	if (regval & HIFMC100_GLOBAL_CFG_RANDOMIZER_EN)
		host->flags |= NAND_RANDOMIZER;

	/*
	* check if start from nand.
	* This register REG_SC_GEN15 is set in start.S
	* When start in NAND (Auto), the ECC/PAGESIZE driver don't detect.
	*/
	if (readl(REG_BASE_SCTL + REG_SC_GEN15) == BOOT_FROM_NAND)
		host->flags |= NANDC_CONFIG_DONE;

	regval = hifmc_read(host, HIFMC100_BOOT_SET);
	if (regval & HIFMC100_BOOT_SET_HW_AUTO)
		host->flags |= NANDC_HW_AUTO;
	else {
		PR_OUT("ERROR: Not support hardware pin mode. "
			"Enable hardware auto mode to resolve this problem.\n");
		return -ENODEV;
	}

	host->enable_ecc_randomizer = hifmc100_enable_ecc_randomizer;
	nand_param_adjust = hifmc100_param_adjust;

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
int hifmc100_nand_init(struct nand_chip *chip)
{
	struct hifmc_host *host = &fmc_host;

	/* hifmc flash type check */
	if (get_bootmedia(NULL, NULL) != BOOT_MEDIA_NAND) {
		return -ENODEV;
	}

	/* hifmc ip version check */
	printf("NAND Check Flash Memory Controller v100 ... ");
	if (!hifmc100_version_check()) {
		printf("\n");
		return -ENODEV;
	}
	printf("Found\n");

	if (host->chip) {
		return 0;
	}

	chip->is_spi_nand = 0;
	memset(host, 0, sizeof(struct hifmc_host));

	host->regbase = (void __iomem *)CONFIG_HIFMC100_REG_BASE_ADDRESS;
	chip->IO_ADDR_R = chip->IO_ADDR_W =
		(void *)CONFIG_HIFMC100_BUFFER_BASE_ADDRESS;
	memset((char *)chip->IO_ADDR_R, 0xff, HIFMC100_BUFFER_LEN);

	hifmc100_nand_controller_enable(host, ENABLE);

	if (hifmc100_nand_host_init(host, chip)) {
		printk("failed to allocate device buffer.\n");
		return -ENOMEM;
	}

	nand_spl_ids_register();

	return 0;
}
/******************************************************************************/

int hifmc100_nand_block_bad(struct mtd_info *mtd, loff_t ofs, int getchip)
{
	u16 bad;
	int offset;
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;
	int page, chipnr, res = 0;
	unsigned int bbm = 0;

	if (!(chip->options & NAND_BBT_2ND_PAGE) && 
	     (chip->options & NAND_BBT_LAST_PAGE))
		bbm = NAND_BBT_2ND_PAGE;

	offset = chip->badblockpos + mtd->writesize;
	page = (int)(ofs >> chip->page_shift) & chip->pagemask;

	if (getchip) {
		chipnr = (int)(ofs >> chip->chip_shift);

		nand_get_device(chip, mtd, FL_READING);

		/* Select the NAND device */
		chip->select_chip(mtd, chipnr);
	}
	do {
		chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos, page);
		bad = chip->read_byte(mtd);
		res = bad != 0xFF;

		if (res) {
			if (host->ecc.bbm_bitsflap != 0xff)
				break;

			if (get_8bits(bad) < 6)
				break;

			res = 0;
			goto next;
		}
		host->page_status |= hifmc100_get_data_status(host);
		if (!IS_PS_EMPTY_PAGE(host))
			goto next;

		if (host->ecc.bbm_bitsflap < 8) {
			res = 0;
			goto next;
		}

		hifmc100_read_raw_data(host, page, offset, 4);
		bad = *(unsigned char *)chip->IO_ADDR_R;
		if (get_8bits(bad) <= 2) {
			res = 1;
			break;
		} else
			res = 0;

next:
		if (!bbm) {
			bbm = NAND_BBT_2ND_PAGE;
			ofs += mtd->writesize;
			page = (int)(ofs >> chip->page_shift) & chip->pagemask;
		} else if (bbm == NAND_BBT_2ND_PAGE) {
			bbm = NAND_BBT_LAST_PAGE;
			ofs -= mtd->writesize;
			ofs += mtd->erasesize - mtd->writesize;
			page = (int)(ofs >> chip->page_shift) & chip->pagemask;
		} else if (bbm == NAND_BBT_LAST_PAGE) {
			break;
		}
	} while (!res && (chip->options & bbm));

	if (getchip) {
		chip->select_chip(mtd, -1);
		nand_release_device(mtd);
	}

	return res;
}
