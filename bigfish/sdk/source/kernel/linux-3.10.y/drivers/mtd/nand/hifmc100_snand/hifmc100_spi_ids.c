/******************************************************************************
 *    Copyright (c) 2014 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By hisilicon
******************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100_spi_ids.h"
#include "hifmc100.h"

/*****************************************************************************/
#define SET_READ_STD(_dummy_, _size_, _clk_) \
	static struct spi_op_info read_std_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_STD, SPI_CMD_READ_STD, _dummy_, _size_, _clk_ }

#define READ_STD(_dummy_, _size_, _clk_) read_std_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_FAST(_dummy_, _size_, _clk_) \
	static struct spi_op_info read_fast_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_FAST, SPI_CMD_READ_FAST, _dummy_, _size_, _clk_ }

#define READ_FAST(_dummy_, _size_, _clk_) read_fast_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_DUAL(_dummy_, _size_, _clk_) \
	static struct spi_op_info read_dual_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_DUAL, SPI_CMD_READ_DUAL, _dummy_, _size_, _clk_ }

#define READ_DUAL(_dummy_, _size_, _clk_) read_dual_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_DUAL_ADDR(_dummy_, _size_, _clk_) \
	static struct spi_op_info read_dual_addr_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_DUAL_ADDR, SPI_CMD_READ_DUAL_ADDR, _dummy_, _size_, _clk_ }

#define READ_DUAL_ADDR(_dummy_, _size_, _clk_) \
	read_dual_addr_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_QUAD(_dummy_, _size_, _clk_) \
	static struct spi_op_info read_quad_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD, SPI_CMD_READ_QUAD, _dummy_, _size_, _clk_ }

#define READ_QUAD(_dummy_, _size_, _clk_) read_quad_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_QUAD_ADDR(_dummy_, _size_, _clk_) \
	static struct spi_op_info read_quad_addr_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD_ADDR, SPI_CMD_READ_QUAD_ADDR, _dummy_, _size_, _clk_ }

#define READ_QUAD_ADDR(_dummy_, _size_, _clk_) \
	read_quad_addr_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_WRITE_STD(_dummy_, _size_, _clk_) \
	static struct spi_op_info write_std_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_STD, SPI_CMD_WRITE_STD, _dummy_, _size_, _clk_ }

#define WRITE_STD(_dummy_, _size_, _clk_) write_std_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_WRITE_QUAD(_dummy_, _size_, _clk_) \
	static struct spi_op_info write_quad_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_QUAD, SPI_CMD_WRITE_QUAD, _dummy_, _size_, _clk_ }

#define WRITE_QUAD(_dummy_, _size_, _clk_) \
	write_quad_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_ERASE_SECTOR_128K(_dummy_, _size_, _clk_) \
	static struct spi_op_info erase_sector_128k_##_dummy_##_size_##_clk_ \
	= { SPI_IF_ERASE_SECTOR_128K, SPI_CMD_SE_128K, _dummy_, _size_, _clk_ }

#define ERASE_SECTOR_128K(_dummy_, _size_, _clk_) \
	erase_sector_128k_##_dummy_##_size_##_clk_

#define SET_ERASE_SECTOR_256K(_dummy_, _size_, _clk_) \
	static struct spi_op_info erase_sector_256k_##_dummy_##_size_##_clk_ \
	= { SPI_IF_ERASE_SECTOR_256K, SPI_CMD_SE_256K, _dummy_, _size_, _clk_ }

#define ERASE_SECTOR_256K(_dummy_, _size_, _clk_) \
	erase_sector_256k_##_dummy_##_size_##_clk_

/*****************************************************************************/
SET_READ_STD(1, INFINITE, 24);
SET_READ_STD(1, INFINITE, 75);
SET_READ_FAST(1, INFINITE, 104);
SET_READ_FAST(1, INFINITE, 120);

SET_READ_DUAL(1, INFINITE, 50);
SET_READ_DUAL(1, INFINITE, 75);
SET_READ_DUAL(1, INFINITE, 104);
SET_READ_DUAL(1, INFINITE, 120);

SET_READ_DUAL_ADDR(1, INFINITE, 104);
SET_READ_DUAL_ADDR(1, INFINITE, 120);
SET_READ_DUAL_ADDR(1, INFINITE, 75);

SET_READ_QUAD(1, INFINITE, 50);
SET_READ_QUAD(1, INFINITE, 75);
SET_READ_QUAD(1, INFINITE, 104);
SET_READ_QUAD(1, INFINITE, 120);

SET_READ_QUAD_ADDR(1, INFINITE, 75);
SET_READ_QUAD_ADDR(2, INFINITE, 104);
SET_READ_QUAD_ADDR(1, INFINITE, 120);

/*****************************************************************************/
SET_WRITE_STD(0, 256, 24);
SET_WRITE_STD(0, 256, 75);

SET_WRITE_QUAD(0, 256, 50);
SET_WRITE_QUAD(0, 256, 75);
SET_WRITE_QUAD(0, 256, 104);
SET_WRITE_QUAD(0, 256, 120);

/*****************************************************************************/
SET_ERASE_SECTOR_128K(0, SZ_128K, 24);
SET_ERASE_SECTOR_128K(0, SZ_128K, 75);

SET_ERASE_SECTOR_256K(0, SZ_256K, 75);
SET_ERASE_SECTOR_256K(0, SZ_256K, 24);

/*****************************************************************************/
#include "hifmc100_spi_general.c"
static struct spi_nand_driver spi_nand_driver_general = {
	.wait_ready   = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.quad_enable  = spi_general_quad_enable, /* giga is this kind*/
};

#include "hifmc100_spi_nand_esmt.c"
static struct spi_nand_driver  spi_nand_driver_esmt = {
	.wait_ready   = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.quad_enable  = spi_nand_esmt_quad_enable,
};
/*****************************************************************************/
#define SPI_NAND_ID_TAB_VER		"1.1"

/******* SPI Nand ID Table ***************************************************
* Version	Manufacturer	Chip Name	Size		Operation
*  1.0		ESMT		F50L512M41A	64MB		Add 5 chip
*		GD		5F1GQ4UAYIG	128MB
*		GD		5F2GQ4UAYIG	256MB
*		GD		5F4GQ4UAYIG	512MB
*		GD		5F4GQ4UBYIG	512MB
*  1.1		ESMT		F50L1G41A	128MB		Add 2 chip
*		Winbond		W25N01GV	128MB
******************************************************************************/
struct hifmc_chip_info hifmc_spi_nand_flash_table[] = {
	/* PARA 1Gbit */
	{
		.name      = "PN26G01WSIUG",
		.id        = {0xA1, 0xF1},
		.id_len    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
			&READ_DUAL(1, INFINITE, 75),
			&READ_DUAL_ADDR(1, INFINITE, 75),
			&READ_QUAD(1, INFINITE, 75),
			&READ_QUAD_ADDR(1, INFINITE, 75),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 75),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
		},
		.driver    = &spi_nand_driver_general,
	},

	/* ALL-FLASH AFS4GQ4UAGWC4 */
	{
		.name      = "AFS4GQ4UAGWC4",
		.id        = {0xc2, 0xd4},
		.id_len    = 2,
		.chipsize  = SZ_512M,
		.erasesize = SZ_256K,
		.pagesize  = SZ_4K,
		.oobsize   = 256,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 75),
			&READ_DUAL(1, INFINITE, 75),
			&READ_QUAD(1, INFINITE, 75),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 75),
			&WRITE_QUAD(0, 256, 75),
			0
		},
		.erase     = {
			&ERASE_SECTOR_256K(0, SZ_256K, 75),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	/* ALL-FLASH AFS2GQ4UADWC2 */
	{
		.name      = "AFS2GQ4UADWC2",
		.id        = {0xc1, 0x52},
		.id_len    = 2,
		.chipsize  = SZ_256M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 128,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 75),
			&READ_DUAL(1, INFINITE, 75),
			&READ_QUAD(1, INFINITE, 75),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 75),
			&WRITE_QUAD(0, 256, 75),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 75),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	/* ALL-FLASH AFS1GQ4UACWC2 */
	{
		.name      = "AFS1GQ4UACWC2",
		.id        = {0xc1, 0x51},
		.id_len    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 128,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 75),
			&READ_DUAL(1, INFINITE, 75),
			&READ_QUAD(1, INFINITE, 75),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 75),
			&WRITE_QUAD(0, 256, 75),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 75),
			0
		},
		.driver    = &spi_nand_driver_general,
	},

	/* ALL-FLASH AFS1GQ4UAAWC2 */
	{
		.name      = "AFS1GQ4UAAWC2",
		.id        = {0xc8, 0x31},
		.id_len    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_256K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 75),
			&READ_DUAL(1, INFINITE, 50),
			&READ_QUAD(1, INFINITE, 50),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 75),
			&WRITE_QUAD(0, 256, 50),
			0
		},
		.erase     = {
			&ERASE_SECTOR_256K(0, SZ_256K, 75),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	/* ESMT F50L512M41A 512Mbit */
	{
		.name      = "F50L512M41A",
		.id        = {0xC8, 0x20},
		.id_len    = 2,
		.chipsize  = SZ_64M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
			&READ_FAST(1, INFINITE, 104),
			&READ_DUAL(1, INFINITE, 104),
			&READ_QUAD(1, INFINITE, 104),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 104),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
			0
		},
		.driver    = &spi_nand_driver_esmt,
	},

	/* ESMT F50L1G41A 1Gbit */
	{
		.name      = "F50L1G41A",
		.id        = {0xC8, 0x21},
		.id_len    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
//			&READ_FAST(1, INFINITE, 104),
//			&READ_DUAL(1, INFINITE, 104),
//			&READ_QUAD(1, INFINITE, 104),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 104),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
			0
		},
		.driver    = &spi_nand_driver_esmt,
	},

	/* GD 5F1GQ4UAYIG 1Gbit */
	{
		.name      = "5F1GQ4UAYIG",
		.id        = {0xc8, 0xf1},
		.id_len    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
			&READ_FAST(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
			0
		},
		.driver    = &spi_nand_driver_general,
	},

	/* GD 5F1GQ4UBYIG 1Gbit */
	{
		.name      = "5F1GQ4UBYIG",
		.id        = {0xc8, 0xd1},
		.id_len    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 128,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
			&READ_FAST(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
			0
		},
		.driver    = &spi_nand_driver_general,
	},

	/* GD 5F2GQ4UAYIG 2Gbit */
	{
		.name      = "5F2GQ4UAYIG",
		.id        = {0xc8, 0xf2},
		.id_len    = 2,
		.chipsize  = SZ_256M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
			&READ_FAST(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
			0
		},
		.driver    = &spi_nand_driver_general,
	},

	/* GD 5F2GQ4UBYIG 2Gbit */
	{
		.name      = "5F2GQ4UBYIG",
		.id        = {0xc8, 0xd2},
		.id_len    = 2,
		.chipsize  = SZ_256M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 128,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
			&READ_FAST(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
			0
		},
		.driver    = &spi_nand_driver_general,
	},

	/* GD 5F4GQ4UAYIG 4Gbit */
	{
		.name      = "5F4GQ4UAYIG",
		.id        = {0xc8, 0xf4},
		.id_len    = 2,
		.chipsize  = SZ_512M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
			&READ_FAST(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
			0
		},
		.driver    = &spi_nand_driver_general,
	},

	/* GD 5F4GQ4UBYIG 4Gbit */
	{
		.name      = "5F4GQ4UBYIG",
		.id        = {0xc8, 0xd4},
		.id_len    = 2,
		.chipsize  = SZ_512M,
		.erasesize = SZ_256K,
		.pagesize  = SZ_4K,
		.oobsize   = 256,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
			&READ_FAST(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_256K(0, SZ_256K, 24),
			0
		},
		.driver    = &spi_nand_driver_general,
	},

	/* TODO: check qe enable. */
	/* Winbond W25N01GV 1Gbit */
	{
		.name      = "W25N01GV",
		.id        = {0xef, 0xaa, 0x21},
		.id_len    = 3,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
			&READ_FAST(1, INFINITE, 104),
			&READ_DUAL(1, INFINITE, 104),
			&READ_DUAL_ADDR(1, INFINITE, 104),
			&READ_QUAD(1, INFINITE, 104),
			&READ_QUAD_ADDR(2, INFINITE, 104),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
			&WRITE_QUAD(0, 256, 104),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
			0
		},
		.driver    = &spi_nand_driver_general,
	},

	{	.id_len    = 0,	},
};

/*****************************************************************************/
static void hifmc100_spi_search_rw(struct hifmc_chip_info *spiinfo,
				struct spi_op_info *spiop_rw, unsigned iftype,
				unsigned max_dummy, int rw_type)
{
	int ix = 0;
	struct spi_op_info **spiop, **fitspiop;

	for (fitspiop = spiop = (rw_type ? spiinfo->write : spiinfo->read);
		(*spiop) && ix < MAX_SPI_NAND_OP; spiop++, ix++)
		if (((*spiop)->iftype & iftype)
			&& ((*spiop)->dummy <= max_dummy)
			&& (*fitspiop)->iftype < (*spiop)->iftype) {
			fitspiop = spiop;
		}

	memcpy(spiop_rw, (*fitspiop), sizeof(struct spi_op_info));
}

/*****************************************************************************/
static void hifmc100_spi_get_erase(struct hifmc_chip_info *spiinfo,
				   struct spi_op_info *spiop_erase)
{
	int ix;

	spiop_erase->size = 0;
	for (ix = 0; ix < MAX_SPI_NAND_OP; ix++) {
		if (spiinfo->erase[ix] == NULL)
			break;
		if (spiinfo->erasesize == spiinfo->erase[ix]->size) {
			memcpy(&spiop_erase[ix], spiinfo->erase[ix],
					sizeof(struct spi_op_info));
			break;
		}
	}
}

/*****************************************************************************/
static void hifmc100_map_iftype_and_clock(struct hifmc_op *spi)
{
	int ix;
	const int iftype_read[] = {
		SPI_IF_READ_STD,        HIFMC100_IF_TYPE_STD,
		SPI_IF_READ_FAST,       HIFMC100_IF_TYPE_STD,
		SPI_IF_READ_DUAL,       HIFMC100_IF_TYPE_DUAL,
		SPI_IF_READ_DUAL_ADDR,  HIFMC100_IF_TYPE_DUAL_ADDR,
		SPI_IF_READ_QUAD,       HIFMC100_IF_TYPE_QUAD,
		SPI_IF_READ_QUAD_ADDR,  HIFMC100_IF_TYPE_QUAD_ADDR,
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
	hifmc100_spi_nand_get_best_clock(&spi->write->clock);

	for (ix = 0; iftype_read[ix]; ix += 2) {
		if (spi->read->iftype == iftype_read[ix]) {
			spi->read->iftype = iftype_read[ix + 1];
			break;
		}
	}
	hifmc100_spi_nand_get_best_clock(&spi->read->clock);

	hifmc100_spi_nand_get_best_clock(&spi->erase->clock);

	spi->erase->iftype = HIFMC100_IF_TYPE_STD;
}

/*****************************************************************************/
static void hifmc100_chip_init(struct hifmc_host *host, 
			       struct hifmc_chip_info *spl_dev)
{
	unsigned char mfr = spl_dev->id[0];
	unsigned int maxtry = 3;
	unsigned char protect = 0;
	unsigned char feature = 0;
	unsigned int protect_mask = 0;
	unsigned char regval;

	if (mfr == NAND_MFR_WINBOND)
		protect_mask = WRITE_PROTECTION_ENABLE_WINBOND;
	else
		protect_mask = WRITE_PROTECTION_ENABLE_GIGA;

	spi_nand_feature_op(host, GET_FEATURE, PROTECTION_REGISTER, &protect);

	if (protect & protect_mask) {
		protect &= ~protect_mask;
		do {
			spi_nand_feature_op(host, SET_FEATURE, 
					    PROTECTION_REGISTER, &protect);

			regval = 0;
			spi_nand_feature_op(host, GET_FEATURE, 
					    PROTECTION_REGISTER, &regval);
			if (!(regval & protect_mask))
				break;

		} while (--maxtry > 0);

		if (regval & protect_mask)
			printk("Write protection disable fail, "
				"Status Register: 0x%x\n", regval);
	}

	maxtry = 3;

	spi_nand_feature_op(host, GET_FEATURE, FEATURE_REGISTER, &feature);

	if (feature & (FEATURE_ECC_ENABLE | FEATURE_OTP_ENABLE)
	    || ((mfr == NAND_MFR_WINBOND) 
	        && (!(feature & FEATURE_BUF_ENABLE)))) {
		feature &= ~(FEATURE_ECC_ENABLE | FEATURE_OTP_ENABLE);

		/* for WINBOND chip, force set BUF read mode. */
		if ((mfr == NAND_MFR_WINBOND) 
		    && (!(feature & FEATURE_BUF_ENABLE)))
				feature |= FEATURE_BUF_ENABLE;

		do {
			spi_nand_feature_op(host, SET_FEATURE, FEATURE_REGISTER, 
					    &feature);

			regval = 0;
			spi_nand_feature_op(host, GET_FEATURE, FEATURE_REGISTER, 
					    &regval);

			if (!(regval & (FEATURE_ECC_ENABLE 
					| FEATURE_OTP_ENABLE)))
				break;

			if ((mfr == NAND_MFR_WINBOND) 
			    && (!(regval & FEATURE_BUF_ENABLE)))
				break;

		} while ((--maxtry > 0));

		if (regval & (FEATURE_ECC_ENABLE | FEATURE_OTP_ENABLE))
			printk("Internal ECC/OTP disable fail, "
				"Status Register: 0x%x.\n", regval);

		if ((mfr == NAND_MFR_WINBOND) 
		    && (!(regval & FEATURE_BUF_ENABLE)))
			printk("enable Buffer Read Mode failed, "
				"Status Register: 0x%x.\n", regval);
	}

}
/*****************************************************************************/

static void hifmc100_spi_ids_probe(struct mtd_info *mtd,
				   struct hifmc_chip_info *spl_dev)
{
	struct nand_chip *chip = mtd->priv;
	struct hifmc_host *host = chip->priv;
	struct hifmc_op *spi = host->spi;

	spi->host = host;
	spi->driver = spl_dev->driver;

	hifmc100_spi_search_rw(spl_dev, spi->read,
				HIFMC100_SPI_NAND_SUPPORT_READ,
				HIFMC100_SPI_NAND_SUPPORT_MAX_DUMMY, 
				SPI_NAND_READ);

	hifmc100_spi_search_rw(spl_dev, spi->write,
				HIFMC100_SPI_NAND_SUPPORT_WRITE,
				HIFMC100_SPI_NAND_SUPPORT_MAX_DUMMY, 
				SPI_NAND_WRITE);

	hifmc100_spi_get_erase(spl_dev, spi->erase);

	hifmc100_map_iftype_and_clock(spi);

	/* if chip support qe mode, set qe mode. */
	if (spi->driver->quad_enable)
		spi->driver->quad_enable(spi);

	/* disable write protection */
	hifmc100_chip_init(host, spl_dev);
}

static struct nand_flash_dev spi_nand_dev;
/*****************************************************************************/
static struct nand_flash_dev *
spi_nand_get_special_flash_type(struct mtd_info *mtd, unsigned char *id)
{
	unsigned char byte[READ_ID_LEN] = {0};
	struct nand_chip *chip = mtd->priv;
	struct hifmc_chip_info *nand_spl_dev = hifmc_spi_nand_flash_table;
	struct hifmc_chip_info *spl_dev = NULL;
	struct nand_flash_dev *type = &spi_nand_dev;

	memcpy(byte, id, READ_ID_LEN);
	printk("Nand ID: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
		byte[0], byte[1], byte[2], byte[3],
		byte[4], byte[5], byte[6], byte[7]);


	for (spl_dev = nand_spl_dev; spl_dev->id_len; spl_dev++) {
		if (memcmp(byte, spl_dev->id, spl_dev->id_len))
			continue;

		type->name = spl_dev->name;
		type->mfr_id = id[0];
		type->pagesize  = spl_dev->pagesize;
		type->chipsize  = spl_dev->chipsize >> 20;
		type->erasesize = spl_dev->erasesize;
		type->id_len    = spl_dev->id_len;
		type->oobsize   = spl_dev->oobsize;

		if (!mtd->name)
			mtd->name = type->name;

		chip->chipsize = (uint64_t)type->chipsize << 20;
		mtd->size = type->chipsize;
		mtd->erasesize = type->erasesize;
		mtd->writesize = type->pagesize;
		mtd->oobsize = spl_dev->oobsize;

		hifmc100_spi_ids_probe(mtd, spl_dev);

		return type;
	}

	return NULL;
}

/*****************************************************************************/
void spi_nand_ids_register(void)
{
	pr_info("SPI Nand ID Table Version %s\n", SPI_NAND_ID_TAB_VER);
	get_spi_nand_flash_type = spi_nand_get_special_flash_type;
}

