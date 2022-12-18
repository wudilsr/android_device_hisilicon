/******************************************************************************
 *    Copyright (c) 2009-2014 by  Hisilicon Tech. Co., Ltd.
 *    All rights reserved.
 * ***
 *    Create By Czyong
******************************************************************************/
#ifndef HIFMC_RW_LATCH_H
#define HIFMC_RW_LATCH_H

struct hifmc_rw_latch {
	char *name;
	unsigned char id[8];
	int length;
	unsigned int rw_latch;
};

struct hifmc_rw_latch *get_hifmc_rw_latch(unsigned char id[8]);

extern struct hifmc_rw_latch *hifmc_rw_latch_table;

#endif /* HIFMC_RW_LATCH_H */
