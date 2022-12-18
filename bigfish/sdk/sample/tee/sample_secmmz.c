#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/mman.h>


#include "tee_client_api.h"
#include "tee_client_id.h"
#include "tee_client_app_load.h"

#include <sec_mmz.h>
#include <sec_mmz_common.h>
#include "drv_mmz_ioctl.h"

static const TEEC_UUID sec_mmz_uuid =
{
	SEC_MMZ_UUID
};

#define SEC_MMZ_ASSERT_PRINT(cond, fmt, arg...) \
		if (!(cond)) { \
			printf("[%s, %d]:" fmt "\n", __func__, __LINE__, ##arg); \
			while(1); \
		}

#define SEC_MMZ_ASSERT(cond) \
		SEC_MMZ_ASSERT_PRINT(cond, "%s", "assert");

#define sec_mmz_printf(fmt, arg...) \
	printf("[%s, %d]:" fmt "\n", __func__, __LINE__, ##arg);


#define MEM_SIZE ((2<<20) - 1)
#define SEC_MMZ_ZONE "SEC-MMZ"

static int nonsecmmzdev = -1;
static TEEC_Context sec_mmz_context;
static TEEC_Session sec_mmz_session;

void *alloc_buffer(size_t size, void **phyaddr)
{
	struct mmb_info mmi = {0};
	int ret = 0;

	nonsecmmzdev = open("/dev/mmz_userdev", O_RDWR);
	SEC_MMZ_ASSERT(nonsecmmzdev >= 0);

	mmi.size = MEM_SIZE;
	mmi.align = 0x100000;
	strncpy(mmi.mmb_name, "secmmzmmb", HIL_MMB_NAME_LEN - 1);
	mmi.mmb_name[HIL_MMB_NAME_LEN - 1] = '\0';

	ret = ioctl(nonsecmmzdev, IOC_MMB_ALLOC, &mmi);
	SEC_MMZ_ASSERT(!ret);
	mmi.prot = PROT_READ | PROT_WRITE;
	mmi.flags = MAP_SHARED;
	ret = ioctl(nonsecmmzdev, IOC_MMB_USER_REMAP, &mmi);
	SEC_MMZ_ASSERT(!ret);

	close(nonsecmmzdev);
	if (phyaddr)
		*phyaddr = (void *)(mmi.phys_addr);

	return mmi.mapped;
}

void free_buffer(void*virtaddr, void *phyaddr)
{
	struct mmb_info mmi;
	int ret = 0;

	if (nonsecmmzdev == -1) {
		nonsecmmzdev = open("/dev/mmz_userdev", O_RDWR);
		SEC_MMZ_ASSERT(nonsecmmzdev >= 0);
	}


	mmi.phys_addr = (unsigned long)phyaddr;
	mmi.mapped = virtaddr;

	ioctl(nonsecmmzdev, IOC_MMB_USER_UNMAP, &mmi);

	/*call ioctl to free*/
	ioctl(nonsecmmzdev, IOC_MMB_FREE, &mmi);
}

int run_ree_secmmz_api(void)
{
	void *pa1 = NULL;
	void *pa2 = NULL;
	void *buf1  = NULL;
	void *buf1_phyaddr = NULL;
	void *buf2 = NULL;
	void *buf2_phyaddr = NULL;

	int ret = 0;

	sec_mmz_printf("start\n");
	ret = HI_SEC_MMZ_Init();
	if (ret < 0) {
		sec_mmz_printf("function return %d\n", ret);
		return -1;
	}

	pa1 = HI_SEC_MMZ_New(MEM_SIZE, SEC_MMZ_ZONE, "mem1");
	pa2 = HI_SEC_MMZ_New(MEM_SIZE, SEC_MMZ_ZONE, "mem2");

	if (!pa1 || !pa2) {
		sec_mmz_printf("fail to alloc mem mem1(%p) or mem2(%p)\n", pa1, pa2);
		goto out;
	}

	sec_mmz_printf("pa1 = %p\n", pa1);
	sec_mmz_printf("pa2 = %p\n", pa2);

	buf1 = alloc_buffer(MEM_SIZE, &buf1_phyaddr);
	SEC_MMZ_ASSERT(buf1);
	buf2 = alloc_buffer(MEM_SIZE, &buf2_phyaddr);
	SEC_MMZ_ASSERT(buf2);

	memset(buf1, 0x5A, MEM_SIZE);

	ret = HI_SEC_MMZ_CA2TA((unsigned long)buf1_phyaddr, (unsigned long)pa1, MEM_SIZE);
	if (ret < 0) {
		sec_mmz_printf("function return %d\n", ret);
		goto out;
	}

	memset(buf2, 0xA5, MEM_SIZE);
	ret = HI_SEC_MMZ_CA2TA((unsigned long)buf2_phyaddr, (unsigned long)pa2, MEM_SIZE);
	if (ret < 0) {
		sec_mmz_printf("function return %d\n", ret);
		goto out;
	}

	ret = HI_SEC_MMZ_TA2TA((unsigned long)pa1, (unsigned long)pa2, MEM_SIZE);
	if (ret < 0) {
		sec_mmz_printf("function return %d\n", ret);
		goto out;
	}

out:
	if (pa1) {
		ret = HI_SEC_MMZ_Delete((unsigned long)pa1);
		SEC_MMZ_ASSERT(!ret);
	}

	if (pa2) {
		ret = HI_SEC_MMZ_Delete((unsigned long)pa2);
		SEC_MMZ_ASSERT(!ret);
	}

	HI_SEC_MMZ_DeInit();

	if (buf1)
		free_buffer(buf1, buf1_phyaddr);
	if (buf2)
		free_buffer(buf2, buf2_phyaddr);

	sec_mmz_printf("end\n");
	return 0;
}

int run_tee_secmmz_api(void)
{
	TEEC_Result result;
	TEEC_Operation operation;
	uint32_t cmd = 0;
	uint32_t origin;
	int32_t ret = 0;

	result = TEEC_InitializeContext(NULL, &sec_mmz_context);
	if(result != TEEC_SUCCESS) {
		TEEC_Error("teec initial failed\n");
		goto error1;
	}

	result = TEEC_OpenSession(&sec_mmz_context, &sec_mmz_session, &sec_mmz_uuid,
				TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
	if(result != TEEC_SUCCESS) {
		TEEC_Error("teec open sec_mmz_session failed\n");
		goto error2;
	}

	operation.started = 1;

	operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE,
				TEEC_NONE,
				TEEC_NONE,
				TEEC_NONE);

	result = TEEC_InvokeCommand(&sec_mmz_session, HI_MMZ_TEST, &operation, &origin);
	if (result != TEEC_SUCCESS) {
		TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
		ret = ERR_IN_SEC_OS;
		goto error3;
	}

	TEEC_CloseSession(&sec_mmz_session);
	TEEC_FinalizeContext(&sec_mmz_context);
	return 0;
error3:
	TEEC_CloseSession(&sec_mmz_session);
error2:
	TEEC_FinalizeContext(&sec_mmz_context);
error1:
	return ret;
}

int main(void)
{
	printf("Secure MMZ REE Sample!\n");
	run_ree_secmmz_api();
	run_tee_secmmz_api();
	return 0;
}
