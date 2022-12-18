/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-07-05
 *
******************************************************************************/

#ifndef HIFMC100_ECC_INFOH
#define HIFMC100_ECC_INFOH

#include "hifmc100_nand.h"

/*
 * oob area for user, this MACRO used by cache.
 * include all mark in oob area.
 */
#define HIFMC100_OOB_OFFSET       0
#define HIFMC100_OOB_SIZE         32

struct ecc_info_t {
	int pagesize;
	int ecctype;
	int threshold;
	int section;
	void (*dump)(struct hifmc_host *host, unsigned char ecc[],
			int *max_bitsflag);
};

int hifmc100_ecc_info_init(struct hifmc_host *host);

#endif /* HIFMC100_ECC_INFOH */
