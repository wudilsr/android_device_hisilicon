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

/******************************************************************************/
/* These macroes are for debug only, reg option is slower then dma option */
#undef HIFMC100_NAND_SUPPORT_REG_READ
/* #define HIFMC100_NAND_SUPPORT_REG_READ */

#undef HIFMC100_NAND_SUPPORT_REG_WRITE
/* #define HIFMC100_NAND_SUPPORT_REG_WRITE */

/*****************************************************************************/
#define HIFMC100_NAND_RW_LATCH			(0xa)
#define HIFMC100_NAND_R_LATCH			(0xa)
#define HIFMC100_NAND_W_LATCH			(0xa)

#define HIFMC100_NAND_BUFFER_BASE_ADDRESS_LEN	(2048 + 128)

#define CONFIG_SUPPORT_YAFFS
#define HIFMC100_NAND_OOBSIZE_FOR_YAFFS		32


/* DMA address align with 32 bytes. */
#define HIFMC100_NAND_DMA_ALIGN			64

/*****************************************************************************/
#define READ_ID_ADDR_NUM			1
#define READ_ID_ADDR                            0x00
#define READ_ID_LEN				8

/* read nand status, return from nand data length */
#define MAX_NANDINFO_LEN                        0x10

#define HIFMC100_BUFFER_LEN			(0x2000 + 0x400)  /* 9K */

/* DMA address align with 32 bytes. */
#define HIFMC100_DMA_ALIGN			32

#define HIFMC100_CHIP_DELAY			25

#define HIFMC100_ADDR_CYCLE_MASK		0x4

/*****************************************************************************/

int hifmc100_nand_block_bad(struct mtd_info *mtd, loff_t ofs, int getchip);
/*****************************************************************************/

#define PR_BUG(fmt, args...) do{\
	printk("%s(%d): !!! BUG " fmt, __FILE__, __LINE__, ##args); \
	while(1); \
} while (0)

#define PR_OUT(fmt, args...) do{\
	printk("%s(%d): " fmt, __FILE__, __LINE__, ##args); \
} while (0)

/*****************************************************************************/
#define HIFMC_CMD_SEQ(_cmd0, _cmd1)        \
	(((_cmd0) & 0xFF) | ((_cmd1) & 0xFF) << 8)

/*****************************************************************************/
struct hifmc_host {
	struct nand_chip *chip;
	struct mtd_info  *mtd;
	void __iomem *regbase;

	unsigned int offset;
	unsigned int oob_offset;
	unsigned int command;

	int chipselect;

	unsigned int FMC_CFG;
	unsigned int FMC_CFG_ECC_NONE;

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
	
	int  need_rr_data;
#define HIFMC100_READ_RETRY_DATA_LEN         128
	char rr_data[HIFMC100_READ_RETRY_DATA_LEN];
	int  version;

	struct {
		/* when ecc number more than this value, return bitflip to mtd. */
		unsigned int threshold;
		int max_bitsflap;
		int section; /* the ecc correct unit */
		unsigned char bbm_bitsflap;
		void (*dump)(struct hifmc_host *host, unsigned char *ecc,
				int *max_bitsflap);
	} ecc;

	/* BOOTROM read two bytes to detect the bad block flag */
#define HIFMC100_BAD_BLOCK_POS              0
	unsigned char *bbm;  /* nand bad block mark */
	unsigned short *epm;  /* nand empty page mark */
	unsigned int flags;
	
#define HIFMC100_PS_UC_ECC        0x01 /* page has ecc error */
#define HIFMC100_PS_BAD_BLOCK     0x02 /* bad block */
#define HIFMC100_PS_EMPTY_PAGE    0x04 /* page is empty */
#define HIFMC100_PS_EPM_ERROR     0x0100 /* empty page mark word has error. */
#define HIFMC100_PS_BBM_ERROR     0x0200 /* bad block mark word has error. */
	unsigned int page_status;

	int (*send_cmd_pageprog)(struct hifmc_host *host);
	int (*send_cmd_status)(struct hifmc_host *host);
	int (*send_cmd_readstart)(struct hifmc_host *host);
	int (*send_cmd_erase)(struct hifmc_host *host);
	int (*send_cmd_readid)(struct hifmc_host *host);
	int (*send_cmd_reset)(struct hifmc_host *host, int chipselect);
	
	int (*enable_ecc_randomizer)(struct hifmc_host *host,
				     int ecc_en, int randomizer_en);

	void (*detect_ecc)(struct hifmc_host *host);

	struct read_retry_t *read_retry;
};

#define IS_PS_EMPTY_PAGE(_host)  ((_host)->page_status & HIFMC100_PS_EMPTY_PAGE)
#define IS_PS_BAD_BLOCK(_host)   ((_host)->page_status & HIFMC100_PS_BAD_BLOCK)
#define IS_PS_UN_ECC(_host)      ((_host)->page_status & HIFMC100_PS_UC_ECC)
#define IS_PS_EPM_ERR(_host)     ((_host)->page_status & HIFMC100_PS_EPM_ERROR)
#define IS_PS_BBM_ERR(_host)     ((_host)->page_status & HIFMC100_PS_BBM_ERROR)

/*****************************************************************************/
#define HIFMC100_WRITE_1CMD_1ADD_DATA \
	(HIFMC100_OP_CMD1_EN(1) \
	| HIFMC100_OP_ADDR_EN(1) \
	| HIFMC100_OP_WRITE_DATE_EN(1) \
	| HIFMC100_OP_REG_OP_START)

#define HIFMC100_WRITE_1CMD_1ADD_DATA_WAIT_READY \
	(HIFMC100_OP_CMD1_EN(1) \
	| HIFMC100_OP_ADDR_EN(1) \
	| HIFMC100_OP_WRITE_DATE_EN(1) \
	| HIFMC100_OP_WAIT_READY_EN(1) \
	| HIFMC100_OP_REG_OP_START)

#define HIFMC100_WRITE_0CMD_1ADD_DATA \
	(HIFMC100_OP_ADDR_EN(1) \
	| HIFMC100_OP_WRITE_DATE_EN(1) \
	| HIFMC100_OP_REG_OP_START)
	
#define HIFMC100_WRITE_2CMD_0ADD_NODATA \
	(HIFMC100_OP_CMD1_EN(1) \
	| HIFMC100_OP_CMD2_EN(1) \
	| HIFMC100_OP_REG_OP_START)

#define HIFMC100_READ_2CMD_5ADD \
	(HIFMC100_OP_READ_DATE_EN(1)\
	| HIFMC100_OP_CMD1_EN(1) \
	| HIFMC100_OP_CMD2_EN(1) \
	| HIFMC100_OP_ADDR_EN(1) \
	| HIFMC100_OP_WAIT_READY_EN(1) \
	| HIFMC100_OP_REG_OP_START)

#define HIFMC100_WRITE_1CMD_0ADD_NODATA \
	(HIFMC100_OP_CMD1_EN(1) \
	| HIFMC100_OP_REG_OP_START)

#define HIFMC100_WRITE_1CMD_0ADD_NODATA_WAIT_READY \
	(HIFMC100_OP_CMD1_EN(1) \
	| HIFMC100_OP_WAIT_READY_EN(1) \
	| HIFMC100_OP_REG_OP_START)

#define HIFMC100_READ_1CMD_1ADD_DATA \
	(HIFMC100_OP_CMD1_EN(1) \
	| HIFMC100_OP_ADDR_EN(1) \
	| HIFMC100_OP_READ_DATE_EN(1) \
	| HIFMC100_OP_REG_OP_START)

#define HIFMC100_READ_1CMD_0ADD_NODATA \
	(HIFMC100_OP_CMD1_EN(1) \
	| HIFMC100_OP_REG_OP_START)

#define HIFMC100_WRITE_1CMD_2ADD_DATA \
	(HIFMC100_OP_CMD1_EN(1) \
	| HIFMC100_OP_ADDR_EN(1) \
	| HIFMC100_OP_WRITE_DATE_EN(1) \
	| HIFMC100_OP_REG_OP_START)

/*****************************************************************************/

int hifmc100_host_init(struct hifmc_host *host);

int hifmc100_nand_init(struct nand_chip *chip);

int hifmc100_ecc_probe(struct mtd_info *mtd, struct nand_chip *chip,
			struct nand_dev_t *nand_dev);

/******************************************************************************/
#endif /* HIFMC100H */

