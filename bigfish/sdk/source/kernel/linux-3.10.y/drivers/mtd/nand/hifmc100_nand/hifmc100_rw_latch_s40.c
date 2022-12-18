/******************************************************************************
 *    Copyright (c) 2009-2014 by  Hisilicon Tech. Co., Ltd.
 *    All rights reserved.
 * ***
 *    Create By Czyong
******************************************************************************/

#include "hifmc100_rw_latch.h"
/*****************************************************************************/

struct hifmc_rw_latch hifmc100_rw_latch_s40[] = {
	{
		.name   = "general",
		.id     = {0x00},
		.length = 0,
		.rw_latch = 0x375,
	}
};

struct hifmc_rw_latch *hifmc_rw_latch_table = hifmc100_rw_latch_s40;

