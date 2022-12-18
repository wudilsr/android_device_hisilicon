
#include <config.h>
#include <stdio.h>
#include <asm/io.h>
#include <delay.h>

#include "mmc_drv.h"

extern int mmu_cache_enable(void);
extern int mmu_cache_disable(void);
extern unsigned int get_timer_clock(void);
#define CONFIG_SYS_HZ get_timer_clock()
#define hang() do { printf("System hang!\n"); while(1); } while(0);

uint32 mmc_wr_pattern[12] = {
	0x00ff00ff,
	0xff00ff00,
	0x5a5a5a5a,
	0xa5a5a5a5,
	0x01010101,
	0x02020202,
	0x04040404,
	0x08080808,
	0x10101010,
	0x20202020,
	0x40404040,
	0x80808080
};

typedef struct{
	struct mmc_dev_t *mmc_dev;
	int dev;
	void *addr_in;
	void *addr_out;
	uint32 cnt;
	int blk;
}mmc_wr_val_t;

int memcmp_pr(const void * cs,const void * ct,size_t count)
{
	const unsigned char *su1, *su2;
	int res = 0;
	printf("mem compare: src 0x%p, dst 0x%p\n", cs, ct);
	for( su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0) {
			printf("differ at src 0x%p[0x%X], dst 0x%p[0x%X]\n", su1, *su1, su2, *su2);
			break;
		}
	return res;
}
static int mmc_check_wr(mmc_wr_val_t* val, uint32 pattern, int cmp)
{ 
	unsigned long long start_ticks, end_ticks;
	unsigned long long size = 0;
	mmc_wr_val_t *p = val;
	uint32 pat = pattern;
	uint32 n;
	int i;

	size = p->mmc_dev->w_blk_len * (p->cnt);

	mmu_cache_enable();
	for (i = 0; i < size/sizeof(pat); i++) {
		*((uint32 *)(p->addr_in) + i) = pat;		
	}
	mmu_cache_disable();
	/*
	printf("IN: i=%d, *0x%08X=0x%08X, *0x%08X=0x%08X, *0x%08X=0x%08X, *0x%08X=0x%08X\n",
		i, (uint32)(p->addr_in + 0), *((uint32 *)(p->addr_in) + 0), 
		(uint32)(p->addr_in) + 4, *((uint32 *)(p->addr_in) + 1), 
		(uint32)(p->addr_in + (i - 2) * 4), *((uint32 *)(p->addr_in) + i - 2),
		(uint32)(p->addr_in + (i - 1)*4), *((uint32 *)(p->addr_in) + i - 1));
	*/

	printf("\nMMC write: dev # %d, block # 0x%x, count 0x%x, pattern 0x%X\n",p->dev, p->blk,
		p->cnt, pat);
	start_ticks = get_ticks();
	n = p->mmc_dev->write(p->mmc_dev, p->blk, p->cnt, p->addr_in);
	end_ticks = get_ticks();

	if (n != p->cnt) {
		printf("0x%x blocks written: %s\n", n, "ERROR");
		return -1;
	}

	printf("0x%x blocks writen: %s, write speed: %llu KB/s\n", n, "OK",
		((size >> 10) * CONFIG_SYS_HZ)/(end_ticks - start_ticks));

	printf("MMC read: dev # %d, block # 0x%x, count 0x%x, pattern 0x%X\n",
		p->dev, p->blk,	p->cnt, pat);
	start_ticks = get_ticks();
	n = p->mmc_dev->read(p->mmc_dev, p->blk, p->cnt, p->addr_out);
	end_ticks = get_ticks();

	if (n != p->cnt) {
	    printf("0x%x blocks read: %s\n", n, "ERROR");
	    return -1;
	}

	mmu_cache_enable();
	for (i = 0; i < size/sizeof(pat); i++) {
		*((uint32 *)(p->addr_out) + i) = pat;		
	}
	mmu_cache_disable();

	/*
	printf("OUT: i=%d, *0x%08X=0x%08X, *0x%08X=0x%08X, *0x%08X=0x%08X, *0x%08X=0x%08X\n",
		i, (uint32)(p->addr_out + 0), *((uint32 *)(p->addr_out) + 0),
		(uint32)(p->addr_out) + 4, *((uint32 *)(p->addr_out) + 1),
		(uint32)(p->addr_out + (i - 2) * 4), *((uint32 *)(p->addr_out) + i - 2),
		(uint32)(p->addr_out + (i - 1)*4), *((uint32 *)(p->addr_out) + i - 1));
	*/

	printf("0x%x blocks read: %s, read speed: %llu KB/s\n", n, "OK",
		((size >> 10) * CONFIG_SYS_HZ)/(end_ticks - start_ticks));


	if (cmp) {
		mmu_cache_enable();
		n = memcmp_pr(p->addr_in, p->addr_out, size);
		mmu_cache_disable();
		if (n) {
			printf("cmp check fail\n");
			return -1;
		}
		printf("cmp check ok\n");
		
	}
	

	return 0;
}

int mmc_test_wr(mmc_wr_val_t* val)
{
	int ret = 0;
	int j;

	printf("MMC R/W test start\n");
	for(j = 0; j < sizeof(mmc_wr_pattern)/sizeof(mmc_wr_pattern[0]); j++) {
		ret = mmc_check_wr(val, mmc_wr_pattern[j], 1);
		if (ret) {
			 printf("fail!\n");
			 hang();
			 return ret;
		}
	}
	printf("done!\n");
	return ret;
}

int mmc_test(struct mmc_dev_t *mmc_dev, int dev, void *addr_in, void *addr_out, int blk, uint32 cnt)
{
	mmc_wr_val_t mmc_wr_val;
	int ret = -1;

	mmc_wr_val.mmc_dev = mmc_dev;
	mmc_wr_val.dev = dev;
	mmc_wr_val.addr_in = addr_in;
	mmc_wr_val.addr_out = addr_out;
	mmc_wr_val.cnt = cnt;
	mmc_wr_val.blk = blk;

	ret = mmc_test_wr(&mmc_wr_val);
	if (ret)
		goto error;

	return 0;
error:
	return -1;
}

