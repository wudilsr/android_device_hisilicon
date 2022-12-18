/******************************************************************************
*	 Copyright (c) 2009-2015 by Hisilicon.
*	 All rights reserved.
******************************************************************************/

#include <match_table.h>
#include <common.h>
#include <hifmcv100_reg.h>
#include "hifmc100_nand_gen.h"

/*****************************************************************************/

enum hifmc100_nand_page_reg hifmc100_nand_page_type2reg(int type)
{
	return type2reg(page_type2reg, ARRAY_SIZE(page_type2reg), type, 0);
}

int hifmc100_nand_page_reg2type(enum hifmc100_nand_page_reg reg)
{
	return reg2type(page_type2reg, ARRAY_SIZE(page_type2reg), reg, 0);
}
/*****************************************************************************/

enum hifmc100_nand_ecc_reg hifmc100_nand_ecc_type2reg(int type)
{
	return type2reg(ecc_type2reg, ARRAY_SIZE(ecc_type2reg), type, 0);
}

int hifmc100_nand_ecc_reg2type(enum hifmc100_nand_ecc_reg reg)
{
	return reg2type(ecc_type2reg, ARRAY_SIZE(ecc_type2reg), reg, 0);
}
