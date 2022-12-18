/******************************************************************************
 *    Copyright (c) 2014 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By hisilicon
******************************************************************************/
#include <linux/sizes.h>
#include "hinfc_gen.h"
#include "hisfc_spl_ids.h"

/*****************************************************************************/
#define SET_READ_STD(_dummy_, _size_, _clk_) \
	static struct spi_operation read_std_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_STD, SPI_CMD_READ_STD, _dummy_, _size_, _clk_ }

#define READ_STD(_dummy_, _size_, _clk_) read_std_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_FAST(_dummy_, _size_, _clk_) \
	static struct spi_operation read_fast_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_FAST, SPI_CMD_READ_FAST, _dummy_, _size_, _clk_ }

#define READ_FAST(_dummy_, _size_, _clk_) read_fast_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_DUAL(_dummy_, _size_, _clk_) \
	static struct spi_operation read_dual_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_DUAL, SPI_CMD_READ_DUAL, _dummy_, _size_, _clk_ }

#define READ_DUAL(_dummy_, _size_, _clk_) read_dual_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_DUAL_ADDR(_dummy_, _size_, _clk_) \
	static struct spi_operation \
		read_dual_addr_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_DUAL_ADDR, SPI_CMD_READ_DUAL_ADDR, _dummy_, _size_, _clk_ }

#define READ_DUAL_ADDR(_dummy_, _size_, _clk_) \
	read_dual_addr_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_QUAD(_dummy_, _size_, _clk_) \
	static struct spi_operation read_quad_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD, SPI_CMD_READ_QUAD, _dummy_, _size_, _clk_ }

#define READ_QUAD(_dummy_, _size_, _clk_) read_quad_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_READ_QUAD_ADDR(_dummy_, _size_, _clk_) \
	static struct \
		spi_operation read_quad_addr_##_dummy_##_size_##_clk_ = { \
	SPI_IF_READ_QUAD_ADDR, SPI_CMD_READ_QUAD_ADDR, _dummy_, _size_, _clk_ }

#define READ_QUAD_ADDR(_dummy_, _size_, _clk_) \
	read_quad_addr_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_WRITE_STD(_dummy_, _size_, _clk_) \
	static struct spi_operation write_std_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_STD, SPI_CMD_WRITE_STD, _dummy_, _size_, _clk_ }

#define WRITE_STD(_dummy_, _size_, _clk_) write_std_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_WRITE_QUAD(_dummy_, _size_, _clk_) \
	static struct spi_operation write_quad_##_dummy_##_size_##_clk_ = { \
	SPI_IF_WRITE_QUAD, SPI_CMD_WRITE_QUAD, _dummy_, _size_, _clk_ }

#define WRITE_QUAD(_dummy_, _size_, _clk_) \
	write_quad_##_dummy_##_size_##_clk_

/*****************************************************************************/
#define SET_ERASE_SECTOR_128K(_dummy_, _size_, _clk_) \
	static struct spi_operation \
		erase_sector_128k_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_128K, SPI_CMD_SE_128K, _dummy_, _size_, _clk_ }

#define ERASE_SECTOR_128K(_dummy_, _size_, _clk_) \
	erase_sector_128k_##_dummy_##_size_##_clk_

#define SET_ERASE_SECTOR_256K(_dummy_, _size_, _clk_) \
	static struct spi_operation \
		erase_sector_256k_##_dummy_##_size_##_clk_ = { \
	SPI_IF_ERASE_SECTOR_256K, SPI_CMD_SE_256K, _dummy_, _size_, _clk_ }

#define ERASE_SECTOR_256K(_dummy_, _size_, _clk_) \
	erase_sector_256k_##_dummy_##_size_##_clk_

/*****************************************************************************/
SET_READ_STD(1, INFINITE, 24);
SET_READ_STD(1, INFINITE, 50);
SET_READ_STD(1, INFINITE, 75);
SET_READ_STD(1, INFINITE, 104);
SET_READ_STD(1, INFINITE, 120);

SET_READ_DUAL(1, INFINITE, 50);
SET_READ_DUAL(1, INFINITE, 75);
SET_READ_DUAL(1, INFINITE, 104);
SET_READ_DUAL(1, INFINITE, 120);

SET_READ_DUAL_ADDR(1, INFINITE, 104);
SET_READ_DUAL_ADDR(1, INFINITE, 120);

SET_READ_QUAD(1, INFINITE, 50);
SET_READ_QUAD(1, INFINITE, 75);
SET_READ_QUAD(1, INFINITE, 104);
SET_READ_QUAD(1, INFINITE, 120);

SET_READ_QUAD_ADDR(2, INFINITE, 104);
SET_READ_QUAD_ADDR(1, INFINITE, 120);

/*****************************************************************************/
SET_WRITE_STD(0, 256, 24);
SET_WRITE_STD(0, 256, 50);
SET_WRITE_STD(0, 256, 75);
SET_WRITE_STD(0, 256, 104);
SET_WRITE_STD(0, 256, 120);

SET_WRITE_QUAD(0, 256, 50);
SET_WRITE_QUAD(0, 256, 75);
SET_WRITE_QUAD(0, 256, 104);
SET_WRITE_QUAD(0, 256, 120);

/*****************************************************************************/
SET_ERASE_SECTOR_128K(0, SZ_128K, 24);
SET_ERASE_SECTOR_128K(0, SZ_128K, 50);
SET_ERASE_SECTOR_128K(0, SZ_128K, 75);
SET_ERASE_SECTOR_128K(0, SZ_128K, 104);
SET_ERASE_SECTOR_128K(0, SZ_128K, 120);

SET_ERASE_SECTOR_256K(0, SZ_256K, 75);
SET_ERASE_SECTOR_256K(0, SZ_256K, 120);

/*****************************************************************************/

extern int spi_general_wait_ready(struct hisfc_operation *spi);
extern int spi_general_write_enable(struct hisfc_operation *spi);
extern int spi_giga_qaud_enable(struct hisfc_operation *spi);
/*****************************************************************************/

static struct spi_nand_driver spi_nand_driver_general = {
	.wait_ready   = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.quad_enable  = NULL,
};

static struct spi_nand_driver spi_nand_driver_giga = {
	.wait_ready   = spi_general_wait_ready,
	.write_enable = spi_general_write_enable,
	.quad_enable  = spi_giga_qaud_enable,
};

/*****************************************************************************/
#define DRV_VERSION     "1.0"

/*****************************************************************************/
static struct nand_flash_special_dev nand_flash_special_dev[] = {
	/* ALL-FLASH AFS1GQ4UAGWC4 */
	{
		.name      = "AFS1GQ4UAGWC4",
		.id        = {0xc2, 0xd4},
		.length    = 2,
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
		.driver    = &spi_nand_driver_giga,
	},
	/* ALL-FLASH AFS1GQ4UADWC2 */
	{
		.name      = "AFS1GQ4UADWC2",
		.id        = {0xc1, 0x52},
		.length    = 2,
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
		.driver    = &spi_nand_driver_giga,
	},
	/* ALL-FLASH AFS1GQ4UACWC2 */
	{
		.name      = "AFS1GQ4UACWC2",
		.id        = {0xc1, 0x51},
		.length    = 2,
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
		.driver    = &spi_nand_driver_giga,
	},

	/* ALL-FLASH AFS1GQ4UAAWC2 */
	{
		.name      = "AFS1GQ4UAAWC2",
		.id        = {0xc8, 0x31},
		.length    = 2,
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
		.driver    = &spi_nand_driver_giga,
	},
	/* ATO F501G41A 1Gbit */
	{
		.name      = "ATO25D1GA",
		.id        = {0x9B, 0x12},
		.length    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos  = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 104),
			&READ_QUAD(1, INFINITE, 104),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 104),
			&WRITE_QUAD(0, 256, 104),
			0
		},
		.erase    = {
			&ERASE_SECTOR_128K(0, SZ_128K, 104),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	/* ESMT F50L512M41A 512Mbit and EON EN25LN512 512Mbit */
	{
		.name      = "F50L512M41A",
		.id        = {0xC8, 0x20},
		.length    = 2,
		.chipsize  = SZ_64M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 104),
			&READ_DUAL(1, INFINITE, 104),
			&READ_QUAD(1, INFINITE, 104),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 104),
			&WRITE_QUAD(0, 256, 104),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 104),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	/* ESMT F501G41A 1Gbit */
	{
		.name	   = "F501G41A",
		.id	   = {0xC8, 0x21, 0x7F, 0x7F, 0x7F},
		.length    = 5,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos  = BBP_FIRST_PAGE,
		.read	   = {
			&READ_STD(1, INFINITE, 104),
			&READ_DUAL(1, INFINITE, 104),
			&READ_QUAD(1, INFINITE, 104),
			0
		},
		.write	   = {
			&WRITE_STD(0, 256, 104),
			&WRITE_QUAD(0, 256, 104),
			0
		},
		.erase	   = {
			&ERASE_SECTOR_128K(0, SZ_128K, 104),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	/* Giga GD5F1GQ4UAYIG 1Gbit */
	{
		.name      = "GD5F1GQ4UAYIG",
		.id        = {0xC8, 0xF1},
		.length    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
		//	&READ_DUAL(1, INFINITE, 120),
		//	&READ_DUAL_ADDR(1, INFINITE, 120),
		//	&READ_QUAD(1, INFINITE, 120),
		//	&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
		//	&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 24),
			0
		},
		.driver    = &spi_nand_driver_giga,
	},
	/* Giga GD5F1GQ4UBYIG 1Gbit */
	{
		.name      = "GD5F1GQ4UBYIG",
		.id        = {0xC8, 0xD1},
		.length    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 128,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 120),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 120),
			0
		},
		.driver    = &spi_nand_driver_giga,
	},
	/* GD GD5F2GQ4UAYIG 2Gbit */
	{
		.name      = "GD5F2GQ4UAYIG",
		.id        = {0xC8, 0xF2},
		.length    = 2,
		.chipsize  = SZ_256M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 120),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 120),
			0
		},
		.driver    = &spi_nand_driver_giga,
	},
	/* GD GD5F2GQ4UBYIG 2Gbit */
	{
		.name      = "GD5F2GQ4UBYIG",
		.id        = {0xC8, 0xD2},
		.length    = 2,
		.chipsize  = SZ_256M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 128,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 120),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 120),
			0
		},
		.driver    = &spi_nand_driver_giga,
	},
	/* GD GD5F4GQ4UAYIG 4Gbit */
	{
		.name      = "GD5F4GQ4UAYIG",
		.id        = {0xC8, 0xF4},
		.length    = 2,
		.chipsize  = SZ_512M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 120),
			&READ_DUAL(1, INFINITE, 120),
			&READ_DUAL_ADDR(1, INFINITE, 120),
			&READ_QUAD(1, INFINITE, 120),
			&READ_QUAD_ADDR(1, INFINITE, 120),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 120),
			&WRITE_QUAD(0, 256, 120),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 120),
			0
		},
		.driver    = &spi_nand_driver_giga,
	},
	/* GD GD5F4GQ4UBYIG 4Gbit */
	{
		.name      = "GD5F4GQ4UBYIG",
		.id        = {0xC8, 0xD4},
		.length    = 2,
		.chipsize  = SZ_512M,
		.erasesize = SZ_256K,
		.pagesize  = SZ_4K,
		.oobsize   = 256,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 24),
//			&READ_DUAL(1, INFINITE, 24),
//			&READ_DUAL_ADDR(1, INFINITE, 24),
//			&READ_QUAD(1, INFINITE, 24),
//			&READ_QUAD_ADDR(1, INFINITE, 24),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 24),
//			&WRITE_QUAD(0, 256, 24),
			0
		},
		.erase     = {
			&ERASE_SECTOR_256K(0, SZ_256K, 75),
			0
		},
		.driver    = &spi_nand_driver_giga,
	},
	/* Micron MT29F1G01AAADDH4 1Gbit */
	{
		.name      = "MT29F1G01AAADDH4",
		.id        = {0x2C, 0x12},
		.length    = 2,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 50),
			&READ_DUAL(1, INFINITE, 50),
			&READ_QUAD(1, INFINITE, 50),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 50),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 50),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	/* Micron MT29F2G01AAAEDH4 2Gbit */
	{
		.name      = "MT29F2G01AAAEDH4",
		.id        = {0x2C, 0x22},
		.length    = 2,
		.chipsize  = SZ_256M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 50),
			&READ_DUAL(1, INFINITE, 50),
			&READ_QUAD(1, INFINITE, 50),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 50),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 50),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	/* Micron MT29F4G01AAADDH4 4Gbit */
	{
		.name      = "MT29F4G01AAADDH4",
		.id        = {0x2C, 0x32},
		.length    = 2,
		.chipsize  = SZ_512M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 50),
			&READ_DUAL(1, INFINITE, 50),
			&READ_QUAD(1, INFINITE, 50),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 50),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 50),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	/* WINBOND W25N01GV 1Gbit */
	{
		.name      = "W25N01GV",
		.id        = {0xEF, 0xAA, 0x21},
		.length    = 3,
		.chipsize  = SZ_128M,
		.erasesize = SZ_128K,
		.pagesize  = SZ_2K,
		.oobsize   = 64,
		.badblock_pos    = BBP_FIRST_PAGE,
		.read      = {
			&READ_STD(1, INFINITE, 104),
			&READ_DUAL(1, INFINITE, 104),
			&READ_DUAL_ADDR(1, INFINITE, 104),
			&READ_QUAD(1, INFINITE, 104),
			&READ_QUAD_ADDR(2, INFINITE, 104),
			0
		},
		.write     = {
			&WRITE_STD(0, 256, 104),
			&WRITE_QUAD(0, 256, 104),
			0
		},
		.erase     = {
			&ERASE_SECTOR_128K(0, SZ_128K, 104),
			0
		},
		.driver    = &spi_nand_driver_general,
	},
	{	.length    = 0,	},
};

/*****************************************************************************/

struct nand_flash_dev *hisfc_nand_probe(struct mtd_info *mtd,
					struct nand_chip *chip,
					struct nand_dev_t *nand_dev)
{

	unsigned char *byte = nand_dev->ids;
	struct nand_flash_dev *type = &nand_dev->flash_dev;
	struct nand_flash_special_dev *spl_dev;
	struct nand_flash_special_dev *nand_spl_dev = nand_flash_special_dev;

	extern void hisfc400_spi_probe(struct nand_chip *chip, 
				       struct nand_flash_special_dev *spl_dev);

	hinfc_pr_msg("Nand ID: 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
		byte[0], byte[1], byte[2], byte[3],
		byte[4], byte[5], byte[6], byte[7]);

	for (spl_dev = nand_spl_dev; spl_dev->length; spl_dev++) {
		if (memcmp(byte, spl_dev->id, spl_dev->length))
			continue;

		type->pagesize  = spl_dev->pagesize;
		type->erasesize = spl_dev->erasesize;
		nand_dev->oobsize = spl_dev->oobsize;

		hisfc400_spi_probe(chip, spl_dev);

		type->id[1] = byte[1];
		type->chipsize = (unsigned long)(spl_dev->chipsize >> 20);
		type->name = spl_dev->name;
		return type;
	}
	nand_dev->read_retry_type = NAND_RR_NONE;

	return NULL;
}
