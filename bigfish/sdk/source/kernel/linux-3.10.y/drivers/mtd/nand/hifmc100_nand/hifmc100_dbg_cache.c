/******************************************************************************
 *  Copyright (C) 2014 Cai Zhiyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Create By Cai Zhiying 2014.11.17
 *
******************************************************************************/


#include <linux/vmalloc.h>
#include <linux/debugfs.h>
#include <asm/uaccess.h>

#include "hifmc100_os.h"
#include "hifmc100.h"
#include "hifmc100_dbg.h"
#include "hifmc100_cache.h"

/******************************************************************************/

static int hifmc100_cache_enable(struct dentry *root, struct hifmc_host *host)
{
	hifmc_cache_enable(host->cache, 1);
	return 0;
}
/******************************************************************************/

static int hifmc100_cache_disable(struct hifmc_host *host)
{
	hifmc_cache_enable(host->cache, 0);
	return 0;
}
/******************************************************************************/

struct hifmc100_dbg_inf_t hifmc100_dbg_if_cache_enable = {
	"cache", 1,
	hifmc100_cache_enable,
	hifmc100_cache_disable,
	NULL,
	NULL,
	NULL,
	NULL,
};
/******************************************************************************/

static int hifmc100_cache_crc_enable(struct dentry *root, struct hifmc_host *host)
{
	hifmc_cache_crc_enable(host->cache, 1);
	return 0;
}
/******************************************************************************/

static int hifmc100_cache_crc_disable(struct hifmc_host *host)
{
	hifmc_cache_crc_enable(host->cache, 0);
	return 0;
}
/******************************************************************************/

struct hifmc100_dbg_inf_t hifmc100_dbg_if_cache_crc = {
	"cache_crc", 0,
	hifmc100_cache_crc_enable,
	hifmc100_cache_crc_disable,
	NULL,
	NULL,
	NULL,
	NULL,
};
