/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-07-05
 *
******************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100.h"
#include "hifmc100_gen.h"

/*****************************************************************************/
/*
 * 'host->epm' only use the first oobfree[0] field, it looks very simple, But...
 */
static struct nand_ecclayout nand_ecc_default =
{
	.oobfree = {{2, 30}}
};
/*****************************************************************************/

static struct nand_ctrl_info_t hifmc100_soft_auto_config_table[] =
{
	{SZ_16K, NAND_ECC_64BIT, 1824/*1824*/, &nand_ecc_default},
	{SZ_16K, NAND_ECC_40BIT, 1152/*1152*/, &nand_ecc_default},
	{SZ_16K, NAND_ECC_NONE,  32 ,          &nand_ecc_default},

	{SZ_8K, NAND_ECC_64BIT, 928 /*928*/,  &nand_ecc_default},
	{SZ_8K, NAND_ECC_40BIT, 592 /*592*/,  &nand_ecc_default},
	{SZ_8K, NAND_ECC_24BIT, 368 /*368*/,  &nand_ecc_default},
	{SZ_8K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{SZ_4K, NAND_ECC_24BIT, 200 /*200*/,  &nand_ecc_default},
	{SZ_4K, NAND_ECC_16BIT,  128 /*128*/,  &nand_ecc_default},
	{SZ_4K, NAND_ECC_8BIT,  88 /*88*/,    &nand_ecc_default},
	{SZ_4K, NAND_ECC_NONE,  32,           &nand_ecc_default},

	{SZ_2K, NAND_ECC_24BIT, 116 /*116*/, &nand_ecc_default},
	{SZ_2K, NAND_ECC_16BIT,  64 /*64*/, &nand_ecc_default},
	{SZ_2K, NAND_ECC_8BIT,   60  /*60*/,  &nand_ecc_default},
	{SZ_2K, NAND_ECC_NONE,   32,          &nand_ecc_default},

	{0,0,0,NULL},
};

/*****************************************************************************/
/* used the best correct arithmetic. */
struct nand_ctrl_info_t *hifmc100_get_best_ecc(struct mtd_info *mtd)
{
	struct nand_ctrl_info_t *best = NULL;
	struct nand_ctrl_info_t *config = hifmc100_soft_auto_config_table;

	for (; config->layout; config++) {
		if (config->pagesize != mtd->writesize)
			continue;

		if (mtd->oobsize < config->oobsize)
			continue;

		if (!best || (best->ecctype < config->ecctype))
			best = config;
	}

	if (!best)
		hinfc_pr_bug(ERSTR_DRIVER "Driver does not support the pagesize(%d) and oobsize(%d).\n",
			     mtd->writesize, mtd->oobsize);

	return best;
}
/*****************************************************************************/
/* force the pagesize and ecctype */
struct nand_ctrl_info_t *hifmc100_force_ecc(struct mtd_info *mtd, int pagesize,
					     int ecctype, char *cfgmsg,
					     int allow_pagediv)
{
	struct nand_ctrl_info_t *fit = NULL;
	struct nand_ctrl_info_t *config = NULL;

	config = hifmc100_soft_auto_config_table;

	for (; config->layout; config++) {
		if (config->pagesize == pagesize
			&& config->ecctype == ecctype) {
			fit = config;
			break;
		}
	}

	if (!fit) {
		hinfc_pr_bug(ERSTR_DRIVER "Driver(%s mode) does not support this Nand Flash pagesize:%d, ecctype:%s\n",
			     cfgmsg, pagesize, nand_ecc_name(ecctype));
		return NULL;
	}

	if ((pagesize != mtd->writesize)
		&& (pagesize > mtd->writesize || !allow_pagediv)) {
		hinfc_pr_bug(ERSTR_HARDWARE "Hardware (%s mode) configure pagesize %d, but the Nand Flash pageszie is %d\n",
			     cfgmsg, pagesize, mtd->writesize);
		return NULL;
	}

	if (fit->oobsize > mtd->oobsize) {
		hinfc_pr_bug(ERSTR_HARDWARE "(%s mode) The Nand Flash offer space area is %d bytes, but the controller request %d bytes in ecc %s. "
			     "Please make sure the hardware ECC configuration is correct.",
			     cfgmsg, mtd->oobsize, fit->oobsize,
			     nand_ecc_name(ecctype));
		return NULL;
	}

	return fit;
}
/*****************************************************************************/

static void hifmc100_read_bitsflaps_reg(unsigned char ecc[], int begin, int end,
					u32 reg)
{
	while (begin < end) {
		ecc[begin] = (reg & 0xff);
		reg = (reg >> 8);
		begin++;
	}
}
/*****************************************************************************/

static int hifmc100_max_bitsflags(unsigned char *ecc, int section)
{
	int num = 0;

	while (section-- > 0) {
		if (ecc[section] > num)
			num = ecc[section];
	}

	return num;
}
/*****************************************************************************/

static void hifmc100_read_bitsflap_16k(void *host,
				       unsigned char *bitsflap,
				       int *max_bitsflags)
{
	int ix, jx;
	unsigned char __bitsflap[16] = {0};
	struct hifmc_host *hifmc_host = (struct hifmc_host *)host;

	for (ix = 0, jx = 0; ix < 4; ix ++, jx += 4)
		hifmc100_read_bitsflaps_reg(__bitsflap, jx, jx + 4,
					    hifmc_read(hifmc_host, 0xC0 + jx));

	if (max_bitsflags)
		*max_bitsflags = hifmc100_max_bitsflags(__bitsflap, 16);
	if (bitsflap)
		memcpy(bitsflap, __bitsflap, sizeof(__bitsflap));

	hifmc_host->ecc.bbm_bitsflap = __bitsflap[15];
}
/*****************************************************************************/

static void hifmc100_read_bitsflap_8k(void *host,
				      unsigned char *bitsflap,
				      int *max_bitsflags)
{
	int ix, jx;
	unsigned char __bitsflap[8] = {0};
	struct hifmc_host *hifmc_host = (struct hifmc_host *)host;

	for (ix = 0, jx = 0; ix < 2; ix ++, jx += 4)
		hifmc100_read_bitsflaps_reg(__bitsflap, jx, jx + 4,
					    hifmc_read(hifmc_host, 0xC0 + jx));

	if (max_bitsflags)
		*max_bitsflags = hifmc100_max_bitsflags(__bitsflap, 8);
	if (bitsflap)
		memcpy(bitsflap, __bitsflap, sizeof(__bitsflap));

	hifmc_host->ecc.bbm_bitsflap = __bitsflap[7];
}
/*****************************************************************************/

static void hifmc100_read_bitsflap_4k(void *host,
				      unsigned char *bitsflap,
				      int *max_bitsflags)
{
	unsigned char __bitsflap[4] = {0};
	struct hifmc_host *hifmc_host = (struct hifmc_host *)host;

	hifmc100_read_bitsflaps_reg(__bitsflap, 0, 4, hifmc_read(hifmc_host, 0xC0));

	if (max_bitsflags)
		*max_bitsflags = hifmc100_max_bitsflags(__bitsflap, 4);
	if (bitsflap)
		memcpy(bitsflap, __bitsflap, sizeof(__bitsflap));

	hifmc_host->ecc.bbm_bitsflap = __bitsflap[3];
}
/*****************************************************************************/

static void hifmc100_read_bitsflap_2k(void *host,
				      unsigned char *bitsflap,
				      int *max_bitsflags)
{
	unsigned char __bitsflap[2] = {0};
	struct hifmc_host *hifmc_host = (struct hifmc_host *)host;

	hifmc100_read_bitsflaps_reg(__bitsflap, 0, 2, hifmc_read(hifmc_host, 0xC0));

	if (max_bitsflags)
		*max_bitsflags = hifmc100_max_bitsflags(__bitsflap, 2);
	if (bitsflap)
		memcpy(bitsflap, __bitsflap, sizeof(__bitsflap));

	hifmc_host->ecc.bbm_bitsflap = __bitsflap[1];
}
/*****************************************************************************/

static struct ecc_info_t hifmc100_ecc_info[] = {
	/* pagesize  ecctype   threshold section dump */
	{16384,   NAND_ECC_64BIT,  58, 16,   hifmc100_read_bitsflap_16k},
	{16384,   NAND_ECC_40BIT,  34, 16,   hifmc100_read_bitsflap_16k},

	{8192,    NAND_ECC_64BIT, 58,  8,   hifmc100_read_bitsflap_8k},
	{8192,    NAND_ECC_40BIT, 34,  8,   hifmc100_read_bitsflap_8k},
	{8192,    NAND_ECC_28BIT, 25,  8,   hifmc100_read_bitsflap_8k},
	{8192,    NAND_ECC_24BIT, 21,  8,   hifmc100_read_bitsflap_8k},

	{4096,    NAND_ECC_28BIT, 25,  4,   hifmc100_read_bitsflap_4k},
	{4096,    NAND_ECC_24BIT, 21,  4,   hifmc100_read_bitsflap_4k},
	{4096,    NAND_ECC_16BIT, 13,  4,   hifmc100_read_bitsflap_4k},
	{4096,    NAND_ECC_8BIT,  7,   4,   hifmc100_read_bitsflap_4k},

	{2048,    NAND_ECC_28BIT, 25, 2, hifmc100_read_bitsflap_2k},
	{2048,    NAND_ECC_24BIT, 21, 2, hifmc100_read_bitsflap_2k},
	{2048,    NAND_ECC_16BIT, 13, 2, hifmc100_read_bitsflap_2k},
	{2048,    NAND_ECC_8BIT,  7,  2, hifmc100_read_bitsflap_2k},
	{0, 0, 0, 0, 0},
};
/******************************************************************************/

int hifmc100_ecc_info_init(struct hifmc_host *host)
{
	struct ecc_info_t *info = hifmc100_ecc_info;

	for (; info->ecctype; info++)
		if (info->ecctype == host->ecctype &&
		    info->pagesize == host->pagesize)
			goto found;
	return -1;

found:
	host->ecc.threshold = info->threshold;
	host->ecc.section = info->section;
	host->ecc.dump = info->dump;

	return 0;
}
