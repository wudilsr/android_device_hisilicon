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

#define HIFMC100_MAX_READY_WAIT_JIFFIES			(40 * HZ)

#define READ_ID_LEN					8

/*****************************************************************************/
#define HIFMC100_REG_BASE_ADDRESS_LEN			(0x100)
#define HIFMC100_BUFFER_BASE_ADDRESS_LEN		(2048 + 128)

#define HIFMC100_DMA_MAX_SIZE			(4096)
#define HIFMC100_DMA_MAX_MASK			(HIFMC100_DMA_MAX_SIZE - 1)

#define HIFMC100_OP_MAX_SIZE			(0x100)  /* FMC 256B per page */
#define HIFMC100_OP_MAX_MASK			(HIFMC100_OP_MAX_SIZE - 1)

/*****************************************************************************/
#define HIFMC100_SPI_NOR_SUPPORT_READ (SPI_IF_READ_STD \
		| SPI_IF_READ_FAST \
		| SPI_IF_READ_DUAL \
		| SPI_IF_READ_DUAL_ADDR \
		| SPI_IF_READ_QUAD \
		| SPI_IF_READ_QUAD_ADDR)

#define HIFMC100_SPI_NOR_SUPPORT_WRITE (SPI_IF_WRITE_STD \
		| SPI_IF_WRITE_DUAL \
		| SPI_IF_WRITE_DUAL_ADDR \
		| SPI_IF_WRITE_QUAD \
		| SPI_IF_WRITE_QUAD_ADDR)

#define HIFMC100_SPI_NOR_SUPPORT_MAX_DUMMY        (7)

/*****************************************************************************/
/* These macroes are for debug only, reg option is slower then dma option */
#undef HIFMC100_SPI_NAND_SUPPORT_REG_READ
/* #define HIFMC100_SPI_NAND_SUPPORT_REG_READ */

#undef HIFMC100_SPI_NAND_SUPPORT_REG_WRITE
/* #define HIFMC100_SPI_NAND_SUPPORT_REG_WRITE */

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

#define HIFMC100_DMA_ADDR_OFFSET		4096

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
#define HIFMC100_RD_OP_MASK			(0x3 << HIFMC100_RD_OP_SHIFT)

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

#define GET_OP					0
#define SET_OP					1

#define PROTECTION_BRWD_MASK			(1 << 7)
#define PROTECTION_BP3_MASK			(1 << 6)
#define PROTECTION_BP2_MASK			(1 << 5)
#define PROTECTION_BP1_MASK			(1 << 4)
#define PROTECTION_BP0_MASK			(1 << 3)

#define ANY_BP_ENABLE(_val)			((PROTECTION_BP3_MASK & _val) \
						|| (PROTECTION_BP2_MASK & _val) \
						|| (PROTECTION_BP1_MASK & _val) \
						|| (PROTECTION_BP0_MASK & _val))

#define ALL_BP_MASK				(PROTECTION_BP3_MASK \
						| PROTECTION_BP2_MASK \
						| PROTECTION_BP1_MASK \
						| PROTECTION_BP0_MASK)

#define FEATURE_ECC_ENABLE			(1 << 4)
#define FEATURE_QE_ENABLE			(1 << 0)

#define STATUS_ECC_MASK				(0x3 << 4)
#define STATUS_P_FAIL_MASK			(1 << 3)
#define STATUS_E_FAIL_MASK			(1 << 2)
#define STATUS_WEL_MASK				(1 << 1)
#define STATUS_OIP_MASK				(1 << 0)


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
#ifndef DBG_MSG
#define DBG_MSG(_fmt, arg...) \
	printk(KERN_INFO "%s(%d): " _fmt, __FILE__, __LINE__, ##arg);
#endif

#ifndef DBG_BUG
#define DBG_BUG(fmt, args...) do { \
	printk(KERN_INFO "%s(%d): BUG: " fmt, __FILE__, __LINE__, ##args); \
	while (1); \
} while (0)
#endif

#define FMC_WAIT_TIMEOUT 10000000

#define FMC_CMD_WAIT_CPU_FINISH(_host) do { \
	unsigned regval, timeout = FMC_WAIT_TIMEOUT; \
	do { \
		regval = hifmc_read((_host), HIFMC100_OP); \
		--timeout; \
	} while ((regval & HIFMC100_OP_REG_OP_START) && timeout); \
	if (!timeout) \
		DBG_BUG("Wait cmd cpu finish timeout!\n"); \
} while (0)
/*****************************************************************************/
#define FMC_DMA_WAIT_INT_FINISH(_host) do { \
	unsigned regval, timeout = FMC_WAIT_TIMEOUT; \
	do { \
		regval = hifmc_read((_host), HIFMC100_INT); \
		--timeout; \
	} while ((!(regval & HIFMC100_INT_OP_DONE) && timeout)); \
	if (!timeout) { \
		DBG_BUG("Wait dma int finish timeout!\n"); \
	} \
} while (0)

/*****************************************************************************/
#define FMC_DMA_WAIT_CPU_FINISH(_host) do { \
	unsigned regval, timeout = FMC_WAIT_TIMEOUT; \
	do { \
		regval = hifmc_read((_host), FMC_OP); \
		--timeout; \
	} while ((regval & FMC_OP_REG_OP_START) && timeout); \
	if (!timeout) \
		DBG_BUG("Wait cpu finish timeout\n"); \
} while (0)

/*****************************************************************************/
#undef  READ
#define READ           1

#undef  WRITE
#define WRITE          0

#undef  DISABLE
#define DISABLE        0

#undef  ENABLE
#define ENABLE         1

#define SPI_NOR_SR_LEN		1	/* Status Register length(byte) */
#define SPI_NOR_CR_LEN		1	/* Config Register length(byte) */

#define SPI_NOR_CR_SHIFT	8	/* Config Register shift(bit) */

#define SPI_NOR_CR_QE_SHIFT	1
#define SPI_NOR_CR_QE_MASK	(1 << SPI_NOR_CR_QE_SHIFT)

#define SPI_NOR_SR_WIP_MASK	(1 << 0)

/*****************************************************************************/
/* Debug SPI Nor flash boot init */
#define DEBUG_SPI_NOR_BOOT	0

/* Debug SPI Nor flash Quad Enable */
#define DEBUG_SPI_NOR_QE	0

/* Debug SPI Nor flash 3-4byte Address Cycle */
#define DEBUG_SPI_NOR_AC	0

/*****************************************************************************/
#define SPI_NAND_MAX_PAGESIZE			0x1000
#define SPI_NAND_MAX_OOBSIZE			0x100

#define HIFMC100_BUFFER_LEN			(0x2000 + 0x400)  /* 9K */

#define HIFMC100_NAND_OOBSIZE_FOR_YAFFS		32

/* DMA address align with 32 bytes. */
#define HIFMC100_DMA_ALIGN			32

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
	struct hifmc_op spi[CONFIG_HIFMC100_MAX_CHIP];

	void __iomem *iobase;
	void __iomem *regbase;
	void __iomem *sysreg;

	unsigned int FMC_CFG;
	unsigned int FMC_CFG_ECC_NONE;

	unsigned int offset;

	unsigned int command;

	int chipselect;

	struct device *dev;
	unsigned int irq;
	struct completion dma_done;

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
int hifmc100_host_init(struct hifmc_host *host);
void hifmc100_spi_nand_init(struct hifmc_host *host, struct nand_chip *chip);
int hifmc100_ecc_probe(struct mtd_info *mtd, struct nand_chip *chip,
		       struct nand_dev_t *nand_dev);

/******************************************************************************/
#endif /* HIFMC100H */

