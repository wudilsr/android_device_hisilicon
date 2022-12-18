#include "tee_common.h"
#include "tee_internal_api.h"
#include "tee_mem_mgmt_api.h"
//#define TA_DEBUG
#include "tee_log.h"
#include "tee_fs.h"
#include "tee_trusted_storage_api.h"
#include "tee_time_api.h"
#include "mmz_struct.h"
#include "mmz.h"

#define SEC_MMZ_ERR_NOMEM  1
#define SEC_MMZ_ERR_MAP_S  2
#define SEC_MMZ_ERR_MAP_NS 3

typedef enum {
	HI_MMZ_NEW = 0x1000,
	HI_MMZ_DEL,
	HI_MMZ_CP_CA2TA,
	HI_MMZ_CP_TA2CA,
	HI_MMZ_CP_TA2TA,
	HI_MMZ_TEST,
	HI_MMZ_DEBUG
} E_HI_MMZ_CommandId;

extern int sec_mmz_test_start(void);
extern int sec_mmz_sample(void);

int isPaddrSecure(unsigned long pa, unsigned size)
{
    return HI_TEE_IsSecureMem(pa, size);
}

int isPaddrNonSecure(unsigned long pa, unsigned size)
{
    return HI_TEE_IsNonSecureMem(pa, size);
}

TEE_Result TA_CreateEntryPoint(void)
{
	TEE_Result ret = TEE_SUCCESS;

	ta_debug("New sec mmz TEE context\n");
	return ret;
}


TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes, TEE_Param params[4],
    void** sessionContext)
{
	ta_debug("New sec mmz session, session context %p\n", sessionContext);
	TEE_Result ret = TEE_SUCCESS;

	return ret;
}

TEE_Result TA_InvokeCommandEntryPoint(void* session_context, uint32_t cmd_id,
    uint32_t paramTypes, TEE_Param params[4])
{
	TEE_Result ret = TEE_SUCCESS;
	unsigned int size;
	char *mmz_name = NULL;
	char *mmb_name = NULL;
	unsigned long pa;
	unsigned long pa1;
	unsigned long pa2;

	switch(cmd_id) {
		case HI_MMZ_NEW:
			if (params[0].memref.size){
				mmz_name = params[0].memref.buffer;
			}

			if (params[1].memref.size){
				mmb_name = params[1].memref.buffer;
			}

			size = params[2].value.a;
			ta_debug("%d New size=%d\n", __LINE__, size);
			pa = HI_MMZ_New(size, 0, mmz_name, mmb_name);
			ta_debug("%d New pa=0x%X\n", __LINE__, pa);

			params[3].value.a = pa;
			if (NULL == (void *)pa)
				ret = SEC_MMZ_ERR_NOMEM;
			break;

		case HI_MMZ_DEL:
			pa = params[0].value.a;
			ta_debug("%d pa=0x%X, size=%d\n", __LINE__, pa, size);
			HI_MMZ_Delete(pa);
			ta_debug("%d Success\n", __LINE__, pa, size);
			break;

		case HI_MMZ_CP_CA2TA:
			pa1 = params[0].value.a;
			pa2 = params[1].value.a;
			size = params[2].value.a;

			params[3].value.a = 0;
			ta_debug("%d HI_MMZ_CP_CA2TA pa1=0x%X, pa2=0x%X, size=%d\n", __LINE__, pa1, pa2, size);

			if (isPaddrSecure(pa2, size) && isPaddrNonSecure(pa1, size)) {
				if (0 != __map_to_s_nocache(pa2,size)) {
					ta_error("map secure memory(addr:0x%x, size:0x%x) failed.\n", pa2, size);
					params[3].value.a = -1;
					ret = SEC_MMZ_ERR_MAP_S;
					break;
				}

			    	ta_debug("%d pa1=0x%X, pa2=0x%X, size=%d\n", __LINE__, pa1, pa2, size);
				if (0 != __map_to_ns_nocache(pa1,size)) {
					ta_error("map non secure memory(addr:0x%x, size:0x%x) failed.\n", pa1, size);
					params[3].value.a = -1;
					ret = SEC_MMZ_ERR_MAP_NS;
					break;
				}

				ta_debug("__mem_copy %d bytes from 0x%X to 0x%X\n", size, pa1, pa2);
				__mem_copy(pa1, pa2, size);

				__unmap_from_s_nocache(pa2,size);
				__unmap_from_ns_nocache(pa1,size);

			} else {
				params[3].value.a = -1;
				ta_error("do HI_MMZ_CP_CA2TA failed(Invalid parameter)!!!pa1=0x%X, pa2=0x%X, size=%d\n", pa1, pa2, size);
			}

			break;
#ifdef CONFIG_SEC_MMZ_TA2CA
		case HI_MMZ_CP_TA2CA:
			pa1 = params[0].value.a;
			pa2 = params[1].value.a;
			size = params[2].value.a;
			ta_debug("%d CONFIG_SEC_MMZ_TA2CA pa1=0x%X, pa2=0x%X, size=%d\n", __LINE__, pa1, pa2, size);

			if (isPaddrNonSecure(pa2, size) && isPaddrSecure(pa1, size)) {
				if (0 != __map_to_s_nocache(pa1,size)) {
					ta_error("map secure memory(addr:0x%x, size:0x%x) failed.\n", pa1, size);
					params[3].value.a = -1;
					ret = SEC_MMZ_ERR_MAP_S;
					break;
				}

				if (0 != __map_to_ns_nocache(pa2,size)) {
					ta_error("map non secure memory(addr:0x%x, size:0x%x) failed.\n", pa2, size);
					params[3].value.a = -1;
					ret = SEC_MMZ_ERR_MAP_NS;
					break;
				}

				// memcpy(pa2, pa1, size);
				__mem_copy(pa1, pa2, size);

				__unmap_from_s_nocache(pa1,size);
				__unmap_from_ns_nocache(pa2,size);
			} else {
				params[3].value.a = -1;
				ta_error("do HI_MMZ_CP_TA2CA failed(Invalid parameter)!!!pa1=0x%X, pa2=0x%X, size=%d\n", pa1, pa2, size);
			}
			break;
#endif
		case HI_MMZ_CP_TA2TA:
			pa1 = params[0].value.a;
			pa2 = params[1].value.a;
			size = params[2].value.a;

			params[3].value.a = 0;

			ta_debug("%d HI_MMZ_CP_TA2TA pa1=0x%X, pa2=0x%X, size=%d\n", __LINE__, pa1, pa2, size);

			if (isPaddrSecure(pa2, size) && isPaddrSecure(pa1, size)) {
				if (0 != __map_to_s_nocache(pa2,size)) {
					ta_error("map secure memory(addr:0x%x, size:0x%x) failed.\n", pa2, size);
					params[3].value.a = -1;
					ret = SEC_MMZ_ERR_MAP_S;
					break;
				}

				if (0 != __map_to_s_nocache(pa1,size)) {
					ta_error("map secure memory(addr:0x%x, size:0x%x) failed.\n", pa2, size);
					params[3].value.a = -1;
					ret = SEC_MMZ_ERR_MAP_NS;
					break;
				}

				// memcpy(pa2, pa1, size);
				__mem_copy(pa1, pa2, size);

				__unmap_from_s_nocache(pa2,size);
				__unmap_from_s_nocache(pa1,size);
			} else {
				params[3].value.a = -1;
				ta_error("do HI_MMZ_CP_TA2TA failed(Invalid parameter)!!!pa1=0x%X, pa2=0x%X, size=%d\n", pa1, pa2, size);
				break;
			}


			break;

		case HI_MMZ_TEST:
#define CONFIG_SEC_MMZ_TEST
#ifdef  CONFIG_SEC_MMZ_TEST
			sec_mmz_test_start();
			sec_mmz_sample();
#endif
			break;
		case HI_MMZ_DEBUG:
#define CONFIG_SEC_MMZ_DEBUG
#ifdef  CONFIG_SEC_MMZ_DEBUG
			__call_debug(0, 0, 0, 0);
#else
			uart_printf_func("MMZ debug not supported\n");
#endif
			break;
		default:
			ta_debug("Invalid TA invoke command, cmd = %d!\n", cmd_id);
			ret = TEE_FAIL;
			break;
	}

	if(TEE_SUCCESS != ret) {
		ta_debug("TA Invoke command falied, ret = 0x%x!\n", ret);
		return ret;
	} else {
		return TEE_SUCCESS;
	}
}

void TA_CloseSessionEntryPoint(void* session_context)
{
	ta_debug("Sec mmz session close\n");
}

void TA_DestroyEntryPoint(void)
{
	ta_debug("Sec mmz destory\n");
}
