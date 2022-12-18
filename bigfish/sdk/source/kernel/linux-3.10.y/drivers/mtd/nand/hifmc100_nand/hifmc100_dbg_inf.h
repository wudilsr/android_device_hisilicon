/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-07-04
 *
******************************************************************************/
#ifndef HIFMC100_DBG_INFH
#define HIFMC100_DBG_INFH
/******************************************************************************/

int hifmc100_dbg_init(struct hifmc_host *host);

void hifmc100_dbg_write(struct hifmc_host *host);

void hifmc100_dbg_erase(struct hifmc_host *host);

void hifmc100_dbg_read(struct hifmc_host *host);

void hifmc100_dbg_read_retry(struct hifmc_host *host, int index);

/******************************************************************************/
#endif /* HIFMC100_DBG_INFH */
