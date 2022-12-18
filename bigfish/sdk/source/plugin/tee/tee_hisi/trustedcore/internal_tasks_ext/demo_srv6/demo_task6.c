#include "tee_common.h"
#include "tee_internal_api.h"
#include "tee_mem_mgmt_api.h"
#define TA_DEBUG
#include "tee_log.h"
#include "tee_fs.h"
#include "tee_trusted_storage_api.h"
#include "tee_time_api.h"

TEE_Result TA_CreateEntryPoint(void)
{
    TEE_Result ret=TEE_SUCCESS;

    ta_debug("TA_CreateEntryPoint test\n");
    return ret;
}


TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes, TEE_Param params[4], void** sessionContext)
{
    TEE_Result ret=TEE_SUCCESS;
    ta_debug("--test\n");

    return ret;
}

TEE_Result TA_InvokeCommandEntryPoint(void* session_context, uint32_t cmd_id, uint32_t paramTypes, TEE_Param params[4])
{
    TEE_Result ret=TEE_SUCCESS;
    ta_debug("--demo6-test\n");
    return  ret;
}

void TA_CloseSessionEntryPoint(void* session_context)
{
    ta_debug("test\n");
}

void TA_DestroyEntryPoint(void)
{
    ta_debug("test\n");
}
