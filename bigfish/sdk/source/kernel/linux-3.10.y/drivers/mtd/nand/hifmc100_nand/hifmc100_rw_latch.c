/******************************************************************************
 *    Copyright (c) 2009-2014 by  Hisilicon Tech. Co., Ltd.
 *    All rights reserved.
 * ***
 *    Create By Czyong
******************************************************************************/
#include <linux/string.h>

#include "hifmc100_rw_latch.h"
/*****************************************************************************/

struct hifmc_rw_latch *get_hifmc_rw_latch(unsigned char id[8])
{
	struct hifmc_rw_latch *rw_latch_table;

	for (rw_latch_table = hifmc_rw_latch_table; 
	     rw_latch_table && rw_latch_table->length; rw_latch_table++) {
		if (!memcmp(id, rw_latch_table->id, rw_latch_table->length))
			break;
	}

	return rw_latch_table;
}
