/******************************************************************************
 *    NAND Flash Controller V610 Device Driver
 *    Copyright (c) 2009-2010 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By Czyong.
 *
******************************************************************************/

#ifndef HIFMC100H
#define HIFMC100H
/******************************************************************************/

#ifndef CONFIG_HIFMC100_W_LATCH
#  define CONFIG_HIFMC100_W_LATCH		(0xa)
#endif /* CONFIG_HIFMC100_W_LATCH */

#ifndef CONFIG_HIFMC100_R_LATCH
#  define CONFIG_HIFMC100_R_LATCH		(0xa)
#endif /* CONFIG_HIFMC100_R_LATCH */

#ifndef CONFIG_HIFMC100_RW_LATCH
#  define CONFIG_HIFMC100_RW_LATCH		(0xa)
#endif /* CONFIG_HIFMC100_RW_LATCH */

#ifndef CONFIG_HIFMC100_NAND_MAX_CHIP
#  define CONFIG_HIFMC100_NAND_MAX_CHIP		(2)
//#  warning NOT config CONFIG_HIFMC100_NAND_MAX_CHIP, used default value, maybe invalid.
#endif /* CONFIG_HIFMC100_NAND_MAX_CHIP */

/*****************************************************************************/

#define HIFMC100_CHIP_DELAY			(25)

#define READ_ID_ADDR				0x00
#define READ_ID_LEN				8
#define READ_ID_ADDR_NUM			1

#define MAX_NANDINFO_LEN			0x10

/*****************************************************************************/
#define HIFMC100_CFG					0x00
#define HIFMC100_CFG_SPI_NAND_SEL(_type)	(((_type) & 0x3) << 11)
#define HIFMC100_CFG_SPI_NOR_ADDR_MODE(_mode)	((_mode) << 10)
#define HIFMC100_CFG_BLOCK_SIZE(_size)		(((_size) & 0x3) << 8)
#define HIFMC100_CFG_ECC_TYPE(_type)		(((_type) & 0x7) << 5)
#define HIFMC100_CFG_PAGE_SIZE(_size)		(((_size) & 0x3) << 3)
#define HIFMC100_CFG_FLASH_SEL(_type)		(((_type) & 0x3) << 1)
#define HIFMC100_CFG_OP_MODE(_mode)		((_mode) & 0x1)

#define HIFMC100_SPI_NAND_SEL_SHIFT		11
#define HIFMC100_SPI_NAND_SEL_MASK		(0x3 << HIFMC100_SPI_NAND_SEL_SHIFT)
#define HIFMC100_SPI_NAND_SEL_WINBOND		1
#define HIFMC100_SPI_NAND_SEL_ESMT		2
#define HIFMC100_SPI_NAND_SEL_MICRON		3
#define HIFMC100_SPI_NAND_SEL_OTHERS		0

#define HIFMC100_SPI_NOR_ADDR_MODE_SHIFT	10
#define HIFMC100_SPI_NOR_ADDR_MODE_MASK		(0x1 << HIFMC100_SPI_NOR_ADDR_MODE_SHIFT)

#define HIFMC100_BLOCK_SIZE_SHIFT		8
#define HIFMC100_BLOCK_SIZE_MASK		(0x3 << HIFMC100_BLOCK_SIZE_SHIFT)
#define HIFMC100_BLOCK_SIZE_64_PAGE		0x0
#define HIFMC100_BLOCK_SIZE_128_PAGE		0x1
#define HIFMC100_BLOCK_SIZE_256_PAGE		0x2
#define HIFMC100_BLOCK_SIZE_512_PAGE		0x3

#define HIFMC100_ECC_TYPE_SHIFT			5
#define HIFMC100_ECC_TYPE_MASK			(0x7)

#define HIFMC100_PAGE_SIZE_SHIFT		3
#define HIFMC100_PAGE_SIZE_MASK			(0x3)

#define HIFMC100_FLASH_SEL_SHIFT		1
#define HIFMC100_FLASH_SEL_MASK			(0x3 << HIFMC100_FLASH_SEL_SHIFT)
#define HIFMC100_FLASH_TYPE_SPI_NOR		0x0
#define HIFMC100_FLASH_TYPE_SPI_NAND		0x1
#define HIFMC100_FLASH_TYPE_NAND		0x2


#define HIFMC100_OP_MODE_BOOT			0x0
#define HIFMC100_OP_MODE_NORMAL			0x1
#define HIFMC100_OP_MODE_MASK			0x1
/*****************************************************************************/
#define HIFMC100_GLOBAL_CFG			0x04
#define HIFMC100_GLOBAL_CFG_WP_ENABLE		(1 << 6)
#define HIFMC100_GLOBAL_CFG_RANDOMIZER_EN	(1 << 2)

/*****************************************************************************/
#define HIFMC100_TIMING_SPI_CFG			0x08
#define HIFMC100_TIMING_SPI_CFG_TCSH(_n)	(((_n) & 0xf) << 8)
#define HIFMC100_TIMING_SPI_CFG_TCSS(_n)	(((_n) & 0xf) << 4)
#define HIFMC100_TIMING_SPI_CFG_TSHSL(_n)	((_n) & 0xf)

#define HIFMC100_CS_HOLD_TIME			0x6
#define HIFMC100_CS_SETUP_TIME			0x6
#define HIFMC100_CS_DESELECT_TIME		0xf

/*****************************************************************************/
#define HIFMC100_PND_PWIDTH_CFG			0x0c
#define HIFMC100_PND_PWIDTH_CFG_RW_HCNT(_n)	(((_n) & 0xf) << 8)
#define HIFMC100_PND_PWIDTH_CFG_R_LCNT(_n)	(((_n) & 0xf) << 4)
#define HIFMC100_PND_PWIDTH_CFG_W_LCNT(_n)	((_n) & 0xf)

#define SET_HIFMC100_PWIDTH(_w_lcnt, _r_lcnt, _rw_hcnt) \
	((_w_lcnt) | (((_r_lcnt) & 0x0F) << 4) | (((_rw_hcnt) & 0x0F) << 8))

/*****************************************************************************/
#define HIFMC100_INT				0x18
#define HIFMC100_INT_AHB_OP			(1 << 7)
#define HIFMC100_INT_WR_LOCK			(1 << 6)
#define HIFMC100_INT_DMA_ERR			(1 << 5)
#define HIFMC100_INT_ERR_ALARM			(1 << 4)
#define HIFMC100_INT_ERR_INVALID		(1 << 3)
#define HIFMC100_INT_ERR_VALID			(1 << 2)
#define HIFMC100_INT_OP_FAIL			(1 << 1)
#define HIFMC100_INT_OP_DONE			(1 << 0)

/*****************************************************************************/
#define HIFMC100_INT_EN				0x1c
#define HIFMC100_INT_EN_AHB_OP			(1 << 7)
#define HIFMC100_INT_EN_WR_LOCK			(1 << 6)
#define HIFMC100_INT_EN_DMA_ERR			(1 << 5)
#define HIFMC100_INT_EN_ERR_ALARM		(1 << 4)
#define HIFMC100_INT_EN_ERR_INVALID		(1 << 3)
#define HIFMC100_INT_EN_ERR_VALID		(1 << 2)
#define HIFMC100_INT_EN_OP_FAIL			(1 << 1)
#define HIFMC100_INT_EN_OP_DONE			(1 << 0)
#define HIFMC100_INT_EN_ALL			0xff
/*****************************************************************************/
#define HIFMC100_INT_CLR			0x20
#define HIFMC100_INT_CLR_AHB_OP			(1 << 7)
#define HIFMC100_INT_CLR_WR_LOCK		(1 << 6)
#define HIFMC100_INT_CLR_DMA_ERR		(1 << 5)
#define HIFMC100_INT_CLR_ERR_ALARM		(1 << 4)
#define HIFMC100_INT_CLR_ERR_INVALID		(1 << 3)
#define HIFMC100_INT_CLR_ERR_VALID		(1 << 2)
#define HIFMC100_INT_CLR_OP_FAIL		(1 << 1)
#define HIFMC100_INT_CLR_OP_DONE		(1 << 0)

#define HIFMC100_INT_CLR_ALL			0xff

/*****************************************************************************/
#define HIFMC100_CMD				0x24
#define HIFMC100_CMD_CMD2(_cmd)			(((_cmd) & 0xff) << 8)
#define HIFMC100_CMD_CMD1(_cmd)			((_cmd) & 0xff)

/*****************************************************************************/
#define HIFMC100_ADDRH				0x28
#define HIFMC100_ADDRH_SET(_addr)		((_addr) & 0xff)

/*****************************************************************************/
#define HIFMC100_ADDRL				0x2c
#define HIFMC100_ADDRL_BLOCK_H_MASK(_page)	(((_page) & 0xffff) << 16)
#define HIFMC100_ADDRL_BLOCK_L_MASK(_page)	((_page) & 0xffc0)

/*****************************************************************************/
#define HIFMC100_OP_CFG				0x30
#define HIFMC100_OP_CFG_FM_CS(_cs)		((_cs) << 11)
#define HIFMC100_OP_CFG_FORCE_CS_EN(_en)	((_en) << 10)
#define HIFMC100_OP_CFG_MEM_IF_TYPE(_type)	(((_type) & 0x7) << 7)
#define HIFMC100_OP_CFG_ADDR_NUM(_addr)		(((_addr) & 0x7) << 4)
#define HIFMC100_OP_CFG_DUMMY_NUM(_dummy)	((_dummy) & 0xf)

#define HIFMC100_IF_TYPE_STD			0x0
#define HIFMC100_IF_TYPE_DUAL			0x1
#define HIFMC100_IF_TYPE_DUAL_ADDR		0x2
#define HIFMC100_IF_TYPE_QUAD			0x3
#define HIFMC100_IF_TYPE_QUAD_ADDR		0x4

#define HIFMC100_IF_TYPE_SHIFT			7
#define HIFMC100_IF_TYPE_MASK			(0x7 << HIFMC100_IF_TYPE_SHIFT)

#define HIFMC100_STD_OP_ADDR_NUM		3

/*****************************************************************************/
#define HIFMC100_SPI_OP_ADDR			0x34

/*****************************************************************************/
#define HIFMC100_DATA_NUM			0x38
#define HIFMC100_DATA_NUM_CNT(_n)		((_n) & 0x3fff)

/*****************************************************************************/
#define HIFMC100_OP				0x3c
#define HIFMC100_OP_DUMMY_EN(_en)		((_en) << 8)
#define HIFMC100_OP_CMD1_EN(_en)		((_en) << 7)
#define HIFMC100_OP_ADDR_EN(_en)		((_en) << 6)
#define HIFMC100_OP_WRITE_DATE_EN(_en)		((_en) << 5)
#define HIFMC100_OP_CMD2_EN(_en)		((_en) << 4)
#define HIFMC100_OP_WAIT_READY_EN(_en)		((_en) << 3)
#define HIFMC100_OP_READ_DATE_EN(_en)		((_en) << 2)
#define HIFMC100_OP_READ_STATUS_EN(_en)		((_en) << 1)
#define HIFMC100_OP_REG_OP_START		1

/*****************************************************************************/
#define HIFMC100_DMA_LEN			0x40
#define HIFMC100_DMA_LEN_SET(_len)		((_len) & 0x0fffffff)

/*****************************************************************************/
#define HIFMC100_DMA_AHB_CTRL			0x48
#define HIFMC100_DMA_AHB_CTRL_DMA_PP_EN		(1 << 3)
#define HIFMC100_DMA_AHB_CTRL_BURST16_EN	(1 << 2)
#define HIFMC100_DMA_AHB_CTRL_BURST8_EN		(1 << 1)
#define HIFMC100_DMA_AHB_CTRL_BURST4_EN		1

#define HIFMC100_ALL_BURST_ENABLE	(HIFMC100_DMA_AHB_CTRL_BURST16_EN \
					| HIFMC100_DMA_AHB_CTRL_BURST8_EN \
					| HIFMC100_DMA_AHB_CTRL_BURST4_EN)

#define HIFMC100_ADDR_CYCLE_MASK		0x4
#define HIFMC100_DMA_ADDR_OFFSET		0x1000

/*****************************************************************************/
#define HIFMC100_DMA_SADDR_D0			0x4c

/*****************************************************************************/
#define HIFMC100_DMA_SADDR_D1			0x50

/*****************************************************************************/
#define HIFMC100_DMA_SADDR_D2			0x54

/*****************************************************************************/
#define HIFMC100_DMA_SADDR_D3			0x58

/*****************************************************************************/
#define HIFMC100_DMA_SADDR_OOB			0x5c

/*****************************************************************************/
#define HIFMC100_DMA_BLK_SADDR			0x60
#define HIFMC100_DMA_BLK_SADDR_SET(_addr)	((_addr) & 0xffffff)

/*****************************************************************************/
#define HIFMC100_DMA_BLK_LEN			0x64
#define HIFMC100_DMA_BLK_LEN_SET(_len)		((_len) & 0xffff)

/*****************************************************************************/
#define HIFMC100_OP_CTRL			0x68
#define HIFMC100_OP_CTRL_RD_OPCODE(_code)	(((_code) & 0xff) << 16)
#define HIFMC100_OP_CTRL_WR_OPCODE(_code)	(((_code) & 0xff) << 8)
#define HIFMC100_OP_CTRL_RD_OP_SEL(_op)		(((_op) & 0x3) << 4)
#define HIFMC100_OP_CTRL_DMA_OP(_type)		((_type) << 2)
#define HIFMC100_OP_CTRL_RW_OP(_op)		((_op) << 1)
#define HIFMC100_OP_CTRL_DMA_OP_READY		1

#define HIFMC100_RD_OP_READ_ALL_PAGE		0x0
#define HIFMC100_RD_OP_READ_OOB			0x1
#define HIFMC100_RD_OP_BULK_READ		0x2
#define HIFMC100_RD_OP_CACHE_READ		0x3

#define HIFMC100_RD_OP_SHIFT			4
#define HIFMC100_RD_OP_MASK			(0x3 << RD_OP_SHIFT)

#define HIFMC100_OP_TYPE_DMA			0x0
#define HIFMC100_OP_TYPE_REG			0x1

#define HIFMC100_RW_OP_READ			0x0
#define HIFMC100_RW_OP_WRITE			0x1

/*****************************************************************************/
#define HIFMC100_OP_PARA			0x70
#define HIFMC100_OP_PARA_RD_OOB_ONLY		(1 << 1)
/*****************************************************************************/
#define HIFMC100_BOOT_SET			0x74
#define HIFMC100_BOOT_SET_OTP			(1 << 4)
#define HIFMC100_BOOT_SET_DEVICE_ECC_EN		(1 << 3)
#define HIFMC100_BOOT_SET_BOOT_QUAD_EN		(1 << 1)
#define HIFMC100_BOOT_SET_HW_AUTO			(1 << 0)
/*****************************************************************************/
#define HIFMC100_STATUS				0xac

/*****************************************************************************/
#define HIFMC100_VERSION			0xbc

#define HIFMC_VER_100				(0x100)

/*****************************************************************************/

#define HIFMC100_CACHE_CTRL			0x150
#define HIFMC100_EXIT_CACHE_OP_EN		(1 << 11)
#define HIFMC100_CACHE_MEM_SADDR_SEL(_sel)	(_sel << 10)
#define HIFMC100_CACHE_TERMINATE(_en)		(_en << 9)
#define HIFMC100_CACHE_PAGE_NUM(_num)		(_num & 0x1ff)

#define HIFMC100_CACHE_MEM_SADDR_SEL_CONTINOUS	1
#define HIFMC100_CACHE_MEM_SADDR_SEL_DISPERSE	0
/*****************************************************************************/

#define hifmc_read(_host, _reg) \
	readl((void __iomem *)(_host->regbase + (_reg)))

#define hifmc_write(_host, _value, _reg) do {\
		writel((unsigned)(_value), (void __iomem *)(_host->regbase + (_reg))); \
	} while (0)

#define GET_PAGE_INDEX(host) \
		((host->addr_value[0] >> 16) | (host->addr_value[1] << 16))

/*****************************************************************************/
#define PR_BUG(fmt, args...) do{\
	printk("%s(%d): !!! BUG " fmt, __FILE__, __LINE__, ##args); \
	while(1); \
} while (0)

#define PR_OUT(fmt, args...) do{\
	printk("%s(%d): " fmt, __FILE__, __LINE__, ##args); \
} while (0)

#define FMC_WAIT_TIMEOUT 10000000

#define FMC_CMD_WAIT_CPU_FINISH(_host) do { \
	unsigned regval, timeout = FMC_WAIT_TIMEOUT; \
	do { \
		regval = hifmc_read(_host, HIFMC100_OP); \
		--timeout; \
	} while ((regval & HIFMC100_OP_REG_OP_START) && timeout); \
	if (!timeout) \
		PR_BUG("Wait cmd cpu finish timeout!\n"); \
} while (0)
/*****************************************************************************/
#define FMC_DMA_WAIT_INT_FINISH() do { \
	unsigned regval, timeout = FMC_WAIT_TIMEOUT; \
	do { \
		regval = hifmc_read(host, HIFMC100_INT); \
		--timeout; \
	} while ((!(regval & HIFMC100_INT_OP_DONE) && timeout)); \
	if (!timeout) { \
		PR_BUG("Wait dma int finish timeout!\n"); \
	} \
} while (0)

/*****************************************************************************/
#define FMC_DMA_WAIT_CPU_FINISH() do { \
	unsigned regval, timeout = FMC_WAIT_TIMEOUT; \
	do { \
		regval = hifmc_read(host, FMC_OP); \
		--timeout; \
	} while ((regval & HIFMC100_OP_REG_OP_START) && timeout); \
	if (!timeout) \
		PR_BUG("Wait cpu finish timeout\n"); \
} while (0)

/*****************************************************************************/
#include "hinfc_gen.h"

#undef  READ
#define READ           1

#undef  WRITE
#define WRITE          0

#undef  FALSE
#define FALSE          0

#undef  TRUE
#define TRUE           1

#undef ENABLE
#define ENABLE         1

#undef DISABLE
#define DISABLE        0
/*****************************************************************************/

struct hifmc_host
{
	struct nand_chip *chip;
	struct mtd_info  *mtd;
	void __iomem *regbase;
	void __iomem *sysreg;
	struct device *dev;
	unsigned int irq;
	struct completion dma_done;

	unsigned int offset;
	unsigned int command;

	int chipselect;

	int ecctype;

	unsigned int FMC_CFG;
	unsigned int FMC_CFG_ECC_NONE;
	unsigned int addr_cycle;
	unsigned int addr_value[2];
	unsigned int column;

	unsigned int block_page_mask;
	unsigned int page_per_chip;
	unsigned int page_per_block;
	unsigned int pagesize;
	unsigned int oobsize;

	char *fix_pagebuf;
	char *fix_oobbuf;

	char *pagebuf;
	char *oobbuf;

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
		void (*dump)(void *host, unsigned char *ecc,
			     int *max_bitsflap);
	} ecc;

	/* BOOTROM read two bytes to detect the bad block flag */
	unsigned char *bbm;  /* nand bad block mark */
	unsigned short *epm; /* nand empty page mark */
	unsigned int flags;

#define HIFMC100_PS_UC_ECC        0x01 /* page has ecc error */
#define HIFMC100_PS_BAD_BLOCK     0x02 /* bad block */
#define HIFMC100_PS_EMPTY_PAGE    0x04 /* page is empty */
#define HIFMC100_PS_EPM_ERROR     0x0100 /* empty page mark word has ecc error. */
#define HIFMC100_PS_BBM_ERROR     0x0200 /* bad block mark word has ecc error. */
	unsigned int page_status;

	struct clk *clk;

	int (*send_cmd_pageprog)(struct hifmc_host *host);
	int (*send_cmd_status)(struct hifmc_host *host);
	int (*send_cmd_readstart)(struct hifmc_host *host);
	int (*send_cmd_erase)(struct hifmc_host *host);
	int (*send_cmd_readid)(struct hifmc_host *host);
	int (*send_cmd_reset)(struct hifmc_host *host, int chipselect);
	int (*enable)(struct hifmc_host *host, int enable);

	int (*enable_ecc_randomizer)(struct hifmc_host *host,
				     int ecc_en, int randomizer_en);

	struct read_retry_t *read_retry;

	struct nand_sync *sync;

	void *cache;

	struct dentry *dbgfs_root;
};

#define HIFMC100_UC_ECC               0x01
#define HIFMC100_BAD_BLOCK            0x02
#define HIFMC100_EMPTY_PAGE           0x04

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

#define GET_RW_PAGE_INDEX(host) \
	(((host->addr_value[0] >> 16) | (host->addr_value[1] << 16)) + \
		host->page_per_chip * host->chipselect)

#define GET_ERASE_PAGE_INDEX(host) \
	(host->addr_value[0])

/*****************************************************************************/

void hifmc100_cmd_ctrl(struct mtd_info *mtd, int dat, unsigned int ctrl);
int hifmc100_dev_ready(struct mtd_info *mtd);
void hifmc100_select_chip(struct mtd_info *mtd, int chipselect);
uint8_t hifmc100_read_byte(struct mtd_info *mtd);
u16 hifmc100_read_word(struct mtd_info *mtd);
void hifmc100_write_buf(struct mtd_info *mtd, 
			       const uint8_t *buf, int len);
void hifmc100_read_buf(struct mtd_info *mtd, uint8_t *buf, int len);
int hifmc100_nand_init(struct hifmc_host *host, struct nand_chip *chip);
int hifmc100_nand_destory(struct hifmc_host *host);
/******************************************************************************/
#endif /* HIFMC100H */
