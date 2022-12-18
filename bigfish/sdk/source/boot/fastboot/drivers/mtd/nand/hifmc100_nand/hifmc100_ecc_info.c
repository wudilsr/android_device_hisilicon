/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-07-05
 *
******************************************************************************/
#include <asm/io.h>
#include <common.h>
#include <hinfc_gen.h>
#include <hifmcv100_reg.h>

#include "hifmc100_nand.h"
#include "hifmc100_ecc_info.h"

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

static void hifmc100_read_bitsflap_16k(struct hifmc_host *host,
				       unsigned char *bitsflap,
				       int *max_bitsflags)
{
	int ix, jx;
	unsigned char __bitsflap[16] = {0};

	for (ix = 0, jx = 0; ix < 4; ix ++, jx += 4)
		hifmc100_read_bitsflaps_reg(__bitsflap, jx, jx + 4,
					    hifmc_read(host, 0xC0 + jx));

	if (max_bitsflags)
		*max_bitsflags = hifmc100_max_bitsflags(__bitsflap, 16);
	if (bitsflap)
		memcpy(bitsflap, __bitsflap, sizeof(__bitsflap));

	host->ecc.bbm_bitsflap = __bitsflap[15];
}
/*****************************************************************************/

static void hifmc100_read_bitsflap_8k(struct hifmc_host *host,
				      unsigned char *bitsflap,
				      int *max_bitsflags)
{
	int ix, jx;
	unsigned char __bitsflap[8] = {0};

	for (ix = 0, jx = 0; ix < 2; ix ++, jx += 4)
		hifmc100_read_bitsflaps_reg(__bitsflap, jx, jx + 4,
					    hifmc_read(host, 0xC0 + jx));

	if (max_bitsflags)
		*max_bitsflags = hifmc100_max_bitsflags(__bitsflap, 8);
	if (bitsflap)
		memcpy(bitsflap, __bitsflap, sizeof(__bitsflap));

	host->ecc.bbm_bitsflap = __bitsflap[7];
}
/*****************************************************************************/

static void hifmc100_read_bitsflap_4k(struct hifmc_host *host,
				      unsigned char *bitsflap,
				      int *max_bitsflags)
{
	unsigned char __bitsflap[4] = {0};

	hifmc100_read_bitsflaps_reg(__bitsflap, 0, 4, hifmc_read(host, 0xC0));

	if (max_bitsflags)
		*max_bitsflags = hifmc100_max_bitsflags(__bitsflap, 4);
	if (bitsflap)
		memcpy(bitsflap, __bitsflap, sizeof(__bitsflap));

	host->ecc.bbm_bitsflap = __bitsflap[3];
}
/*****************************************************************************/

static void hifmc100_read_bitsflap_2k(struct hifmc_host *host,
				      unsigned char *bitsflap,
				      int *max_bitsflags)
{
	unsigned char __bitsflap[2] = {0};

	hifmc100_read_bitsflaps_reg(__bitsflap, 0, 2, hifmc_read(host, 0xC0));

	if (max_bitsflags)
		*max_bitsflags = hifmc100_max_bitsflags(__bitsflap, 2);
	if (bitsflap)
		memcpy(bitsflap, __bitsflap, sizeof(__bitsflap));

	host->ecc.bbm_bitsflap = __bitsflap[1];
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
