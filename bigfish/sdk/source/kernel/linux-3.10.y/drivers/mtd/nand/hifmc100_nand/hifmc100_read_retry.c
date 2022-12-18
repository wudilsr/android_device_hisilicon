/******************************************************************************
 *    NAND Flash Controller V610 Device Driver
 *    Copyright (c) 2012-2013 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By Czyong.
 *
******************************************************************************/
#include "hifmc100_gen.h"
#include "hifmc100.h"
#include "hifmc100_read_retry.h"

extern struct read_retry_t hifmc100_hynix_bg_cdie_read_retry;
extern struct read_retry_t hifmc100_hynix_bg_bdie_read_retry;
extern struct read_retry_t hifmc100_hynix_cg_adie_read_retry;
extern struct read_retry_t hifmc100_micron_read_retry;
extern struct read_retry_t hifmc100_toshiba_24nm_read_retry;
extern struct read_retry_t hifmc100_toshiba_19nm_read_retry;
extern struct read_retry_t hifmc100_samsung_read_retry;

static struct read_retry_t *read_retry_table[] = {
	&hifmc100_hynix_bg_bdie_read_retry,
	&hifmc100_hynix_bg_cdie_read_retry,
	&hifmc100_hynix_cg_adie_read_retry,
	&hifmc100_micron_read_retry,
	&hifmc100_toshiba_24nm_read_retry,
	&hifmc100_toshiba_19nm_read_retry,
	&hifmc100_samsung_read_retry,
	NULL,
};

struct read_retry_t *hifmc100_find_read_retry(int type)
{
	struct read_retry_t **rr;

	for (rr = read_retry_table; rr; rr++) {
		if ((*rr)->type == type)
			return *rr;
	}

	return NULL;
}
