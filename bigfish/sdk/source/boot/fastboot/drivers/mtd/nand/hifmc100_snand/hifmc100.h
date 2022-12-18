/******************************************************************************
 *    Flash Memory Controller v100 Device Driver
 *    Copyright (c) 2014 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By Hisilicon
 *
******************************************************************************/

#ifndef HIFMC100H
#define HIFMC100H

#include "hifmc100_spi_ids.h"

/******************************************************************************/
/* These macroes are for debug only, reg option is slower then dma option */
#undef HIFMC100_SPI_NAND_SUPPORT_REG_READ
/* #define HIFMC100_SPI_NAND_SUPPORT_REG_READ */

#undef HIFMC100_SPI_NAND_SUPPORT_REG_WRITE
/* #define HIFMC100_SPI_NAND_SUPPORT_REG_WRITE */

/*****************************************************************************/
#define REG_CNT_HIGH_BLOCK_NUM_SHIFT		10

#define REG_CNT_BLOCK_NUM_MASK			0x3ff
#define REG_CNT_BLOCK_NUM_SHIFT			22

#define REG_CNT_PAGE_NUM_MASK			0x3f
#define REG_CNT_PAGE_NUM_SHIFT			16

#define REG_CNT_WRAP_MASK			0xf
#define REG_CNT_WRAP_SHIFT			12

#define REG_CNT_ECC_OFFSET_MASK			0xfff
#define REG_CNT_ECC_8BIT_OFFSET			1054
#define REG_CNT_ECC_16BIT_OFFSET		1056
#define REG_CNT_ECC_24BIT_OFFSET		1082

/*****************************************************************************/
#define SPI_NAND_MAX_PAGESIZE			0x1000
#define SPI_NAND_MAX_OOBSIZE			0x100

#define HIFMC100_BUFFER_LEN			(0x2000 + 0x400)  /* 9K */

#define HIFMC100_NAND_OOBSIZE_FOR_YAFFS		32

/* DMA address align with 32 bytes. */
#define HIFMC100_NAND_DMA_ALIGN			64

#define HIFMC100_CHIP_DELAY			25

#define HIFMC100_ADDR_CYCLE_MASK		0x4

/*****************************************************************************/

#undef  FALSE
#define FALSE          0

#undef  TRUE
#define TRUE           1
/*****************************************************************************/
#define READ_ID_ADDR_NUM			1
#define READ_ID_ADDR                            0x00

#define PROTECTION_REGISTER			0xa0
#define FEATURE_REGISTER			0xb0
#define STATUS_REGISTER				0xc0

#define FEATURES_OP_ADDR_NUM			1
#define FEATURES_DATA_NUM			1

/*****************************************************************************/

#define PR_BUG(fmt, args...) do{\
	printk("%s(%d): !!! BUG " fmt, __FILE__, __LINE__, ##args); \
	while(1); \
} while (0)

#define PR_OUT(fmt, args...) do{\
	printk("%s(%d): " fmt, __FILE__, __LINE__, ##args); \
} while (0)

/*****************************************************************************/

struct hifmc_host;

struct hifmc_host {
	struct nand_chip *chip;
	struct mtd_info  *mtd;
	struct hifmc_op spi[CONFIG_SYS_MAX_NAND_DEVICE];

	void __iomem *iobase;
	void __iomem *regbase;

	unsigned int FMC_CFG;
	unsigned int FMC_CFG_ECC_NONE;

	unsigned int offset;
	unsigned int oob_offset;

	unsigned int command;

	int chipselect;

	struct device *dev;

	unsigned int addr_cycle;
	unsigned int addr_value[2];
	unsigned int cache_addr_value[2];
	unsigned int column;
	unsigned int block_page_mask;

	unsigned int dma_buffer;
	unsigned int dma_oob;

	unsigned int ecctype;
	unsigned int pagesize;
	unsigned int oobsize;

	/* This is maybe an un-aligment address, only for malloc or free */
	char *buforg;
	char *buffer;
	char *cache_read_pagebuf;
	char *cache_read_oobbuf;

	int add_partition;

	/* BOOTROM read two bytes to detect the bad block flag */
#define HIFMC_BAD_BLOCK_POS              0
	unsigned char *bbm;  /* nand bad block mark */
	unsigned short *epm;  /* nand empty page mark */
	unsigned int flags; /*  */

	unsigned int uc_er;

	void (*set_system_clock)(struct hifmc_host *host, 
				 struct spi_op_info *op, int clk_en);
	void (*send_cmd_pageprog)(struct hifmc_host *host);
	void (*send_cmd_status)(struct hifmc_host *host);
	void (*send_cmd_readstart)(struct hifmc_host *host);
	void (*send_cmd_erase)(struct hifmc_host *host);
	void (*send_cmd_readid)(struct hifmc_host *host);
	void (*send_cmd_reset)(struct hifmc_host *host);
};

/*****************************************************************************/
#endif /* HIFMC100H */

