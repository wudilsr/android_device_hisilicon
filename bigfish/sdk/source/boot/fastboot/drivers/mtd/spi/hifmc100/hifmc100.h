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


/*****************************************************************************/
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
/* These macroes are for debug only, reg read is slower then dma read */
#undef HIFMC100_SPI_NOR_SUPPORT_REG_READ
//#define HIFMC100_SPI_NOR_SUPPORT_REG_READ
/* #define HIFMC100_SPI_NOR_SUPPORT_REG_READ */

#undef HIFMC100_SPI_NOR_SUPPORT_REG_WRITE
//#define HIFMC100_SPI_NOR_SUPPORT_REG_WRITE
/* #define HIFMC100_SPI_NOR_SUPPORT_REG_WRITE */

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

#define READ_ID_LEN		8

/*****************************************************************************/
struct hifmc_spi;

struct spi_driver {
	int (*wait_ready)(struct hifmc_spi *spi);
	int (*write_enable)(struct hifmc_spi *spi);
	int (*entry_4addr)(struct hifmc_spi *spi, int enable);
	int (*quad_enable)(struct hifmc_spi *spi);
};

struct hifmc_spi {
	char *name;
	int chipselect;
	unsigned long long chipsize;
	unsigned int erasesize;
	unsigned int addrcycle;

	struct spi_operation  read[1];
	struct spi_operation  write[1];
	struct spi_operation  erase[MAX_SPI_OP];
	void *host;
	void *iobase;
	struct spi_driver *driver;
};

struct hifmc_host {
	struct spi_flash spiflash[1];
	void __iomem *iobase;
	void __iomem *regbase;
	unsigned int erasesize;

	void (*set_system_clock)(struct hifmc_host *host,
					struct spi_operation *op, int clk_en);

	void (*set_host_addr_mode)(struct hifmc_host *host, int enable);

	unsigned int dma_buffer;
	unsigned int flags;
	int num_chip;
	struct hifmc_spi spi[CONFIG_HIFMC100_SPI_NOR_CHIP_NUM + 1];
	char buffer[HIFMC100_DMA_MAX_SIZE];
};

#define SPIFLASH_TO_HOST(_spiflash)     ((struct hifmc_host *)(_spiflash))

/*****************************************************************************/

extern struct spi_info hifmc100_spi_info_table[];

/*****************************************************************************/
#endif /* HIFMC100H */

