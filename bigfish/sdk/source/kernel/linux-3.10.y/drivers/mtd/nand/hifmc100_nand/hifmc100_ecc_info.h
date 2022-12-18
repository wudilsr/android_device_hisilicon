/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-07-05
 *
******************************************************************************/

#ifndef HIFMC100_ECC_INFOH
#define HIFMC100_ECC_INFOH

#include "hifmc100.h"

/*
 * oob area for user, this MACRO used by cache.
 * include all mark in oob area.
 */
#define HIFMC100_OOB_OFFSET       0
#define HIFMC100_BB_OFFSET        0
#define HIFMC100_EPM_OFFSET       28
#define HIFMC100_OOB_SIZE         32

int hifmc100_ecc_info_init(struct hifmc_host *host);

struct nand_ctrl_info_t *hifmc100_get_best_ecc(struct mtd_info *mtd);

struct nand_ctrl_info_t *hifmc100_force_ecc(struct mtd_info *mtd, int pagesize,
					     int ecctype, char *cfgmsg,
					     int allow_pagediv);

#endif /* HIFMC100_ECC_INFOH */
