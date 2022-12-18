/******************************************************************************
*	 Copyright (c) 2009-2015 by Hisilicon.
*	 All rights reserved.
******************************************************************************/

#ifndef HIFMC100_NAND_GENH
#define HIFMC100_NAND_GENH
/******************************************************************************/

#include <hinfc_gen.h>
#include <match_table.h>

enum hifmc100_nand_ecc_reg {
	hifmc100_nand_ecc_none   = 0x00,
	hifmc100_nand_ecc_8bit   = 0x01,
	hifmc100_nand_ecc_16bit  = 0x02,
	hifmc100_nand_ecc_24bit  = 0x03,
	hifmc100_nand_ecc_28bit  = 0x04,
	hifmc100_nand_ecc_40bit  = 0x05,
	hifmc100_nand_ecc_64bit  = 0x06,
};

enum hifmc100_nand_page_reg {
	hifmc100_nand_pagesize_2K    = 0x00,
	hifmc100_nand_pagesize_4K    = 0x01,
	hifmc100_nand_pagesize_8K    = 0x02,
	hifmc100_nand_pagesize_16K   = 0x03,
};

enum hifmc100_nand_page_reg hifmc100_nand_page_type2reg(int type);

int hifmc100_nand_page_reg2type(enum hifmc100_nand_page_reg reg);

enum hifmc100_nand_ecc_reg hifmc100_nand_ecc_type2reg(int type);

int hifmc100_nand_ecc_reg2type(enum hifmc100_nand_ecc_reg reg);

/*****************************************************************************/

static struct match_reg_type page_type2reg[] = {
	{
		hifmc100_nand_pagesize_2K, NAND_PAGE_2K,
	}, {
		hifmc100_nand_pagesize_4K, NAND_PAGE_4K,
	}, {
		hifmc100_nand_pagesize_8K, NAND_PAGE_8K,
	}, {
		hifmc100_nand_pagesize_16K, NAND_PAGE_16K,
	}
};

static struct match_reg_type ecc_type2reg[] = {
	{
		hifmc100_nand_ecc_none, NAND_ECC_NONE,
	}, {
		hifmc100_nand_ecc_8bit, NAND_ECC_8BIT,
	}, {
		hifmc100_nand_ecc_16bit, NAND_ECC_16BIT,
	}, {
		hifmc100_nand_ecc_24bit, NAND_ECC_24BIT,
	}, {
		hifmc100_nand_ecc_28bit, NAND_ECC_28BIT,
	}, {
		hifmc100_nand_ecc_40bit, NAND_ECC_40BIT,
	}, {
		hifmc100_nand_ecc_64bit, NAND_ECC_64BIT,
	}
};
/*****************************************************************************/

#define HIFMC100_SET_ECCTYPE(_host) \
	do { \
		int regval = type2reg(ecc_type2reg, ARRAY_SIZE(ecc_type2reg), \
			_host->ecctype, hifmc100_nand_ecc_8bit); \
		_host->FMC_CFG &= ~(HIFMC100_ECC_TYPE_MASK \
				    << HIFMC100_ECC_TYPE_SHIFT); \
		_host->FMC_CFG |= (regval & HIFMC100_ECC_TYPE_MASK) \
				   << HIFMC100_ECC_TYPE_SHIFT; \
	} while (0)
/*****************************************************************************/

#define HIFMC100_SET_PAGESIZE(_host) \
	do { \
		int pagetype = nandpage_size2type(_host->pagesize); \
		int mask = ~(HIFMC100_PAGE_SIZE_MASK << HIFMC100_PAGE_SIZE_SHIFT);\
		int regval = type2reg(page_type2reg, \
					ARRAY_SIZE(page_type2reg), \
					pagetype, hifmc100_nand_pagesize_2K); \
		regval = (regval & HIFMC100_PAGE_SIZE_MASK) \
			  << HIFMC100_PAGE_SIZE_SHIFT; \
		_host->FMC_CFG &=  mask; \
		_host->FMC_CFG |=  regval; \
		_host->FMC_CFG_ECC_NONE = _host->FMC_CFG \
			& ~(HIFMC100_ECC_TYPE_MASK << HIFMC100_ECC_TYPE_SHIFT); \
	} while (0)
/******************************************************************************/
#endif /* HIFMC100_NAND_GENH */
