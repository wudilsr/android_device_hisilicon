/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-07-04
 *
******************************************************************************/

#include <linux/debugfs.h>
#include <asm/uaccess.h>

#include "hifmc100_os.h"
#include "hifmc100.h"
#include "hifmc100_dbg.h"

extern int hifmc100_dbgfs_debug_init(struct hifmc_host *host);

#ifdef CONFIG_HIFMC100_NAND_DBG_NAND_DEBUG
extern struct hifmc100_dbg_inf_t *hifmc100_dbg_inf[];
#endif

void hifmc100_dbg_write(struct hifmc_host *host)
{
#ifdef CONFIG_HIFMC100_NAND_DBG_NAND_DEBUG
	struct hifmc100_dbg_inf_t **inf;
	for (inf = hifmc100_dbg_inf; *inf; inf++)
		if ((*inf)->enable && (*inf)->write)
			(*inf)->write(host);
#endif
}

void hifmc100_dbg_erase(struct hifmc_host *host)
{
#ifdef CONFIG_HIFMC100_NAND_DBG_NAND_DEBUG
	struct hifmc100_dbg_inf_t **inf;
	for (inf = hifmc100_dbg_inf; *inf; inf++)
		if ((*inf)->enable && (*inf)->erase)
			(*inf)->erase(host);
#endif
}

void hifmc100_dbg_read(struct hifmc_host *host)
{
#ifdef CONFIG_HIFMC100_NAND_DBG_NAND_DEBUG
	struct hifmc100_dbg_inf_t **inf;
	for (inf = hifmc100_dbg_inf; *inf; inf++)
		if ((*inf)->enable && (*inf)->read)
			(*inf)->read(host);
#endif
}

void hifmc100_dbg_read_retry(struct hifmc_host *host, int index)
{
#ifdef CONFIG_HIFMC100_NAND_DBG_NAND_DEBUG
	struct hifmc100_dbg_inf_t **inf;
	for (inf = hifmc100_dbg_inf; *inf; inf++)
		if ((*inf)->enable && (*inf)->read_retry)
			(*inf)->read_retry(host, index);
#endif
}

int hifmc100_dbg_init(struct hifmc_host *host)
{
#ifdef CONFIG_HIFMC100_NAND_DBG_NAND_DEBUG
	return hifmc100_dbgfs_debug_init(host);
#else
	return 0;
#endif
}
