#include "tee_common.h"
#include "tee_internal_api.h"
#include "tee_mem_mgmt_api.h"
#define TA_DEBUG
#include "tee_log.h"
#include "tee_fs.h"
#include "tee_trusted_storage_api.h"
#include "tee_time_api.h"

#include "sec_mmz.h"


#define NULL 0
#define SEC_MMZ_ASSERT_PRINT(cond, fmt, arg...) \
		if (!(cond)) { \
			ta_error("[%s, %d]:" fmt "\n", __func__, __LINE__, ##arg); \
			while(1); \
		}

#define SEC_MMZ_ASSERT(cond) \
		SEC_MMZ_ASSERT_PRINT(cond, "%s", "assert");

#define sec_mmz_printf(fmt, arg...) \
	ta_debug("[%s, %d]:" fmt "\n", __func__, __LINE__, ##arg);


#define MEM_SIZE ((2<<20) - 1)
#define SEC_MMZ_ZONE "SEC-MMZ"
#define MEM_PAD 0x5A

void run_new_del_map(void)
{
	int i;
	int j;
	int ret = 0;
	void *pa1 = NULL;
	void *pa2 = NULL;
	char *va1 = NULL;
	char *va2 = NULL;

	ta_debug("start\n");

	pa1 = HI_SEC_MMZ_New(MEM_SIZE, SEC_MMZ_ZONE, "mem1");
	pa2 = HI_SEC_MMZ_New(MEM_SIZE, SEC_MMZ_ZONE, "mem2");

	SEC_MMZ_ASSERT(pa1);
	SEC_MMZ_ASSERT(pa2);
	SEC_MMZ_ASSERT(pa1 != pa2);
	ta_debug("pa1=%p, pa2=%p\n", pa1, pa2);

	va1 = HI_SEC_MMZ_Map(pa1, 0);
	va2 = HI_SEC_MMZ_Map(pa2, 1);
	SEC_MMZ_ASSERT(va1);
	SEC_MMZ_ASSERT(va2);
	SEC_MMZ_ASSERT(va1 != va2);
	ta_debug("va1=%p, va2=%p\n", va1, va2);
	
	memset(va1, MEM_PAD, MEM_SIZE);
	memset(va2, MEM_PAD, MEM_SIZE);
	ret = HI_SEC_MMZ_Flush(pa2);
	if (ret < 0)
		ta_error("function return %d\n", ret);
	SEC_MMZ_ASSERT(!ret);

	for (j = 0; j < MEM_SIZE; j++) {
		SEC_MMZ_ASSERT(va1[j] == va2[j]);
	}

	ret = HI_SEC_MMZ_Unmap(pa1);
	if (ret < 0)
		ta_error("function return %d\n", ret);
	SEC_MMZ_ASSERT(!ret);
	ret = HI_SEC_MMZ_Delete((unsigned long)pa1);
	if (ret < 0)
		ta_error("function return %d\n", ret);
	SEC_MMZ_ASSERT(!ret);

	ret = HI_SEC_MMZ_Unmap(pa2);
	if (ret < 0)
		ta_error("function return %d\n", ret);
	SEC_MMZ_ASSERT(!ret);
	ret = HI_SEC_MMZ_Delete((unsigned long)pa2);
	if (ret < 0)
		ta_error("function return %d\n", ret);
	SEC_MMZ_ASSERT(!ret);

	return 0;
}

void run_newmap_and_delmap(void)
{
	int i;
	int j;
	int ret = 0;
	char *pa1 = NULL;
	char *pa2 = NULL;
	char *va1 = NULL;
	char *va2 = NULL;

	ta_debug("start\n");

	va1 = HI_SEC_MMZ_NewAndMap(MEM_SIZE, 0, SEC_MMZ_ZONE, "mem1", &pa1);
	va2 = HI_SEC_MMZ_NewAndMap(MEM_SIZE, 1, SEC_MMZ_ZONE, "mem2", &pa2);

	SEC_MMZ_ASSERT(pa1);
	SEC_MMZ_ASSERT(pa2);
	SEC_MMZ_ASSERT(pa1 != pa2);
	ta_debug("pa1=%p, pa2=%p\n", pa1, pa2);
	SEC_MMZ_ASSERT(va1);
	SEC_MMZ_ASSERT(va2);
	SEC_MMZ_ASSERT(va1 != va2);
	ta_debug("va1=%p, va2=%p\n", va1, va2);
	
	memset(va1, MEM_PAD, MEM_SIZE);
	memset(va2, MEM_PAD, MEM_SIZE);
	ret = HI_SEC_MMZ_Flush(pa2);
	if (ret < 0)
		ta_error("function return %d\n", ret);
	SEC_MMZ_ASSERT(!ret);

	for (j = 0; j < MEM_SIZE; j++) {
		SEC_MMZ_ASSERT(va1[j] == va2[j]);
	}

	ret = HI_SEC_MMZ_DelAndUnmap(pa1);
	if (ret < 0)
		ta_error("function return %d\n", ret);
	SEC_MMZ_ASSERT(!ret);

	ret = HI_SEC_MMZ_DelAndUnmap(pa2);
	if (ret < 0)
		ta_error("function return %d\n", ret);
	SEC_MMZ_ASSERT(!ret);

	return 0;
}

int sec_mmz_sample(void)
{
	ta_debug("Secure MMZ TEE Sample\n");
	run_new_del_map();
	run_newmap_and_delmap();
}
