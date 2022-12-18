#include "tee_common.h"
#include "tee_internal_api.h"
#include "tee_mem_mgmt_api.h"
#define TA_DEBUG
#include "tee_log.h"
#include "tee_fs.h"
#include "tee_trusted_storage_api.h"
#include "tee_time_api.h"
//#include "sre_syscall.h"
#include "mmz_struct.h"
#include "mmz.h"


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


#define TEST_MEM_SIZE ((2<<20) - 1)
#define SEC_MMZ_ZONE "SEC-MMZ"
#define TEST_PAD 0x5A

void test1(void)
{
	int i = 0;
	int j = 0;
	void *phy=NULL;
	void *vir=NULL;
	char *mmb;
	int result = 0;

	for (; i < 10; i++)
	{
		//ret = HI_SYS_GetTimeStampMs(&u32Time0);
		phy = HI_MMZ_New(1<<20, 0, NULL, "MMB_TEST");
		if(NULL==phy)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		vir=HI_MMZ_Map((unsigned long)phy,0);
		if(NULL==vir)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		mmb = (char *)vir;
		ta_debug("mmb = 0x%x\n", mmb);
		for(j=0; j<(1<<20); j++)
		{
			mmb[j] = 100;
		}

		for(j=0; j<(1<<20); j++)
		{
			if (mmb[j] != 100)
			{
				ta_debug("error write!!!!!!!!!!!!!!!!!!!!!\n");
			}
		}

		ta_debug("user write end!!!!!!!!!!!!!!!!!!!!!\n");

		HI_MMZ_Unmap(phy);
		HI_MMZ_Delete(phy);

		//HI_MMZ_Free(pstBuf);//ummap free
	}

	ta_debug("%s end!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", __func__);
}

void test2(void)
{
	int i = 0;
	void *phy=NULL;

	for (; i < 10; i++)
	{
		//ret = HI_SYS_GetTimeStampMs(&u32Time0);
		phy = HI_MMZ_New(1<<20, 0, NULL, "MMB_TEST");
		if(NULL==phy)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		HI_MMZ_Delete(phy);

		//HI_MMZ_Free(pstBuf);//ummap free
	}

	ta_debug("%s end!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", __func__);
}

void test3(void)
{
	int i = 0;
	void *phy=NULL;

	for (; i < 10; i++)
	{
		//ret = HI_SYS_GetTimeStampMs(&u32Time0);
		phy = HI_MMZ_New(1<<20, 1, NULL, "MMB_TEST");
		if(NULL==phy)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		HI_MMZ_Delete(phy);

		//HI_MMZ_Free(pstBuf);//ummap free
	}

	ta_debug("%s end!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", __func__);
}

void test4(void)
{
	int i = 0;
	int j = 0;
	void *phy=NULL;
	void *vir=NULL;
	char *mmb;
	int result = 0;

	for (; i < 10; i++)
	{
		//ret = HI_SYS_GetTimeStampMs(&u32Time0);
		phy = HI_MMZ_New(1<<20, 1, NULL, "MMB_TEST");
		if(NULL==phy)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		vir=HI_MMZ_Map((unsigned long)phy,0);
		if(NULL==vir)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		mmb = (char *)vir;
		ta_debug("mmb = 0x%x\n", mmb);
		for(j=0; j<(1<<20); j++)
		{
			mmb[j] = 100;
		}

		for(j=0; j<(1<<20); j++)
		{
			if (mmb[j] != 100)
			{
				ta_debug("error write!!!!!!!!!!!!!!!!!!!!!\n");
			}
		}

		ta_debug("user write end!!!!!!!!!!!!!!!!!!!!!\n");

		HI_MMZ_Unmap(phy);
		HI_MMZ_Delete(phy);

		//HI_MMZ_Free(pstBuf);//ummap free
	}

	ta_debug("%s end!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", __func__);
}

void test5(void)
{
	int i = 0;
	int j = 0;
	void *phy=NULL;
	void *vir=NULL;
	char *mmb;
	int result = 0;

	HI_MMZ_BUF_S buf = {"MMB_TEST",};
	buf.alloc_type = 0;
	buf.bufsize = 1 << 20;

	for (; i < 10; i++)
	{
		//ret = HI_SYS_GetTimeStampMs(&u32Time0);
		result = HI_MMZ_Malloc(&buf);
		if(0 > result)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		mmb = (char *)(buf.user_viraddr);
		ta_debug("mmb = 0x%x\n", mmb);
		for(j=0; j<(1<<20); j++)
		{
			mmb[j] = 100;
		}

		for(j=0; j<(1<<20); j++)
		{
			if (mmb[j] != 100)
			{
				ta_debug("error write!!!!!!!!!!!!!!!!!!!!!\n");
			}
		}

		ta_debug("user write end!!!!!!!!!!!!!!!!!!!!!\n");

		result = HI_MMZ_Free(&buf);
		if(0 > result)
		{
			ta_debug("i = %d, LINE:%d\n", i, __LINE__);
			break;
		}
		//HI_MMZ_Free(pstBuf);//ummap free
	}

	ta_debug("%s end!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", __func__);
}

void test6(void)
{
	int i = 0;
	int j = 0;
	void *phy=NULL;
	void *vir=NULL;
	char *mmb;
	int result = 0;

	HI_MMZ_BUF_S buf = {"MMB_TEST",};
	buf.alloc_type = 1;
	buf.bufsize = 1 << 20;

	for (; i < 10; i++)
	{
		//ret = HI_SYS_GetTimeStampMs(&u32Time0);
		result = HI_MMZ_Malloc(&buf);
		if(0 > result)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		mmb = (char *)(buf.user_viraddr);
		ta_debug("mmb = 0x%x\n", mmb);
		for(j=0; j<(1<<20); j++)
		{
			mmb[j] = 100;
		}

		for(j=0; j<(1<<20); j++)
		{
			if (mmb[j] != 100)
			{
				ta_debug("error write!!!!!!!!!!!!!!!!!!!!!\n");
			}
		}

		ta_debug("user write end!!!!!!!!!!!!!!!!!!!!!\n");

		result = HI_MMZ_Free(&buf);
		if(0 > result)
		{
			ta_debug("i = %d, LINE:%d\n", i, __LINE__);
			break;
		}
		//HI_MMZ_Free(pstBuf);//ummap free
	}

	ta_debug("%s end!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", __func__);
}

void test7(void)
{
	int i = 0;
	int j = 0;
	void *phy=NULL;
	void *vir=NULL;
	char *mmb;
	int result = 0;

	for (; i < 10; i++)
	{
		//ret = HI_SYS_GetTimeStampMs(&u32Time0);
		phy = HI_MMZ_New(1<<20, 1, NULL, "MMB_TEST");
		if(NULL==phy)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		vir=HI_MMZ_Map((unsigned long)phy,1);
		if(NULL==vir)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		mmb = (char *)vir;
		ta_debug("mmb = 0x%x\n", mmb);
		for(j=0; j<(1<<20); j++)
		{
			mmb[j] = 100;
		}

		HI_MMZ_Flush(phy);

		for(j=0; j<(1<<20); j++)
		{
			if (mmb[j] != 100)
			{
				ta_debug("error write!!!!!!!!!!!!!!!!!!!!!\n");
			}
		}

		ta_debug("user write end!!!!!!!!!!!!!!!!!!!!!\n");

		HI_MMZ_Unmap(phy);
		HI_MMZ_Delete(phy);

		//HI_MMZ_Free(pstBuf);//ummap free
	}

	ta_debug("%s end!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", __func__);
}

void test8(void)
{
	int i = 0;
	int j = 0;
	void *phy=NULL;
	void *vir=NULL;
	char *mmb;
	int result = 0;

	for (; i < 10; i++)
	{
		//ret = HI_SYS_GetTimeStampMs(&u32Time0);
		phy = HI_MMZ_New(1<<20, 0, NULL, "MMB_TEST");
		if(NULL==phy)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		vir=HI_MMZ_Map((unsigned long)phy,1);
		if(NULL==vir)
		{
			ta_debug("i = %d\n", i);
			break;
		}

		mmb = (char *)vir;
		ta_debug("mmb = 0x%x\n", mmb);
		for(j=0; j<(1<<20); j++)
		{
			mmb[j] = 100;
		}

		HI_MMZ_Flush(phy);

		for(j=0; j<(1<<20); j++)
		{
			if (mmb[j] != 100)
			{
				ta_debug("error write!!!!!!!!!!!!!!!!!!!!!\n");
			}
		}

		ta_debug("user write end!!!!!!!!!!!!!!!!!!!!!\n");

		HI_MMZ_Unmap(phy);
		HI_MMZ_Delete(phy);

		//HI_MMZ_Free(pstBuf);//ummap free
	}

	ta_debug("%s end!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", __func__);
}


int test_new_delete(void)
{
	int i;
	int ret = 0;
	void *pa1 = NULL;
	void *pa2 = NULL;

	ta_debug("start\n");

	for (i = 0; i < 2000; i++) {
		pa1 = HI_SEC_MMZ_New(TEST_MEM_SIZE, SEC_MMZ_ZONE, "aaa1");
		pa2 = HI_SEC_MMZ_New(TEST_MEM_SIZE, SEC_MMZ_ZONE, "aaa2");

		SEC_MMZ_ASSERT(pa1);
		SEC_MMZ_ASSERT(pa2);
		SEC_MMZ_ASSERT(pa1 != pa2);
		//ta_debug("pa1=%p, pa2=%p\n", pa1, pa2);

		ret = HI_SEC_MMZ_Delete((unsigned long)pa1);
		if (ret < 0)
			ta_error("function return %d\n", ret);
		SEC_MMZ_ASSERT(!ret);

		ret = HI_SEC_MMZ_Delete((unsigned long)pa2);
		if (ret < 0)
			ta_error("function return %d\n", ret);
		SEC_MMZ_ASSERT(!ret);
	}

	return 0;
}

void test_new_del_map(void)
{
	int i;
	int j;
	int ret = 0;
	void *pa1 = NULL;
	void *pa2 = NULL;
	char *va1 = NULL;
	char *va2 = NULL;

	ta_debug("start\n");

	for (i = 0; i < 10; i++) {
		pa1 = HI_SEC_MMZ_New(TEST_MEM_SIZE, SEC_MMZ_ZONE, "aaa1");
		pa2 = HI_SEC_MMZ_New(TEST_MEM_SIZE, SEC_MMZ_ZONE, "aaa2");

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
		
		memset(va1, TEST_PAD, TEST_MEM_SIZE);
		memset(va2, TEST_PAD, TEST_MEM_SIZE);
		ret = HI_SEC_MMZ_Flush(pa2);
		if (ret < 0)
			ta_error("function return %d\n", ret);
		SEC_MMZ_ASSERT(!ret);

		for (j = 0; j < TEST_MEM_SIZE; j++) {
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
	}

	return 0;
}

void test_new_and_map(void)
{
	int i;
	int j;
	int ret = 0;
	char *pa1 = NULL;
	char *pa2 = NULL;
	char *va1 = NULL;
	char *va2 = NULL;

	ta_debug("start\n");

	for (i = 0; i < 10; i++) {
		va1 = HI_SEC_MMZ_NewAndMap(TEST_MEM_SIZE, 0, SEC_MMZ_ZONE, "aaa1", &pa1);
		va2 = HI_SEC_MMZ_NewAndMap(TEST_MEM_SIZE, 1, SEC_MMZ_ZONE, "aaa2", &pa2);

		SEC_MMZ_ASSERT(pa1);
		SEC_MMZ_ASSERT(pa2);
		SEC_MMZ_ASSERT(pa1 != pa2);
		ta_debug("pa1=%p, pa2=%p\n", pa1, pa2);
		SEC_MMZ_ASSERT(va1);
		SEC_MMZ_ASSERT(va2);
		SEC_MMZ_ASSERT(va1 != va2);
		ta_debug("va1=%p, va2=%p\n", va1, va2);
		
		memset(va1, TEST_PAD, TEST_MEM_SIZE);
		memset(va2, TEST_PAD, TEST_MEM_SIZE);
		ret = HI_SEC_MMZ_Flush(pa2);
		if (ret < 0)
			ta_error("function return %d\n", ret);
		SEC_MMZ_ASSERT(!ret);

		for (j = 0; j < TEST_MEM_SIZE; j++) {
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
	}

	return 0;
}

void test_del_and_unmap(void)
{
	int i;
	int j;
	int ret = 0;
	void *pa1 = NULL;
	void *pa2 = NULL;
	char *va1 = NULL;
	char *va2 = NULL;

	ta_debug("start\n");

	for (i = 0; i < 10; i++) {
		pa1 = HI_SEC_MMZ_New(TEST_MEM_SIZE, SEC_MMZ_ZONE, "aaa1");
		pa2 = HI_SEC_MMZ_New(TEST_MEM_SIZE, SEC_MMZ_ZONE, "aaa2");

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
		
		memset(va1, TEST_PAD, TEST_MEM_SIZE);
		memset(va2, TEST_PAD, TEST_MEM_SIZE);
		ret = HI_SEC_MMZ_Flush(pa2);
		if (ret < 0)
			ta_error("function return %d\n", ret);
		SEC_MMZ_ASSERT(!ret);

		for (j = 0; j < TEST_MEM_SIZE; j++) {
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
	}

	return 0;
}

#define MB (1024UL*1024UL)

void test_tee_is_sec_mem(void)
{
    int ret = 0;
    ta_debug("test_tee_is_sec_mem start\n");
#ifdef CONFIG_SYS_MEM_2G
    ret = HI_TEE_IsSecureMem(0, 10*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(1710*MB, 4*MB);
    SEC_MMZ_ASSERT(ret == 0);
    
    ret = HI_TEE_IsSecureMem(1024*1024, 1756*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(0, 2041*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(1024*1024, 2041*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(0, 2041*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(1760*MB, 240*MB);
    SEC_MMZ_ASSERT(ret == 1);

    ret = HI_TEE_IsSecureMem(1713*MB, 287*MB);
    SEC_MMZ_ASSERT(ret == 1);

    ret = HI_TEE_IsNonSecureMem(0, 1122*MB);
    SEC_MMZ_ASSERT(ret == 1);

    ret = HI_TEE_IsNonSecureMem(2041*MB, 7*MB);
    SEC_MMZ_ASSERT(ret == 1);

    ret = HI_TEE_IsNonSecureMem(100*MB, 1900*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsNonSecureMem(500*MB, 1545*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsNonSecureMem(2000*MB, 45*MB);
    SEC_MMZ_ASSERT(ret == 0);
#endif

#ifdef CONFIG_SYS_MEM_1G
    ret = HI_TEE_IsSecureMem(0, 10*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(864*MB, 4*MB);
    SEC_MMZ_ASSERT(ret == 1);
    
    ret = HI_TEE_IsSecureMem(1024*1024, 1756*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(0, 2041*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(1024*1024, 2041*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(0, 2041*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsSecureMem(904*MB, 111*MB);
    SEC_MMZ_ASSERT(ret == 1);

    ret = HI_TEE_IsSecureMem(864*MB, 39*MB);
    SEC_MMZ_ASSERT(ret == 1);

    ret = HI_TEE_IsNonSecureMem(0, 863*MB);
    SEC_MMZ_ASSERT(ret == 1);

    ret = HI_TEE_IsNonSecureMem(1016*MB, 7*MB);
    SEC_MMZ_ASSERT(ret == 1);

    ret = HI_TEE_IsNonSecureMem(863*MB, 10*MB);
    SEC_MMZ_ASSERT(ret == 0);

    ret = HI_TEE_IsNonSecureMem(904*MB, 111*MB);
    SEC_MMZ_ASSERT(ret == 0);

#endif
}


void test_new_map_and_del_unmap(void)
{
	int i;
	int j;
	int ret = 0;
	char *pa1 = NULL;
	char *pa2 = NULL;
	char *va1 = NULL;
	char *va2 = NULL;

	ta_debug("start\n");

	for (i = 0; i < 10; i++) {
		va1 = HI_SEC_MMZ_NewAndMap(TEST_MEM_SIZE, 0, SEC_MMZ_ZONE, "aaa1", &pa1);
		va2 = HI_SEC_MMZ_NewAndMap(TEST_MEM_SIZE, 1, SEC_MMZ_ZONE, "aaa2", &pa2);

		SEC_MMZ_ASSERT(pa1);
		SEC_MMZ_ASSERT(pa2);
		SEC_MMZ_ASSERT(pa1 != pa2);
		ta_debug("pa1=%p, pa2=%p\n", pa1, pa2);
		SEC_MMZ_ASSERT(va1);
		SEC_MMZ_ASSERT(va2);
		SEC_MMZ_ASSERT(va1 != va2);
		ta_debug("va1=%p, va2=%p\n", va1, va2);
		
		memset(va1, TEST_PAD, TEST_MEM_SIZE);
		memset(va2, TEST_PAD, TEST_MEM_SIZE);
		ret = HI_SEC_MMZ_Flush(pa2);
		if (ret < 0)
			ta_error("function return %d\n", ret);
		SEC_MMZ_ASSERT(!ret);

		for (j = 0; j < TEST_MEM_SIZE; j++) {
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
	}

	return 0;
}

int sec_mmz_test_start(void)
{
/*
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	*/
	test8();
	//test_tee_is_sec_mem();
	test_new_delete();
	test_new_del_map();
	test_new_and_map();
	test_del_and_unmap();
	test_new_map_and_del_unmap();
}
