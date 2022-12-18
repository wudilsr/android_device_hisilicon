#include "tee_common.h"
#include "tee_internal_api.h"
#include "tee_mem_mgmt_api.h"
#define TA_DEBUG
#include "tee_log.h"
#include "tee_fs.h"
#include "tee_trusted_storage_api.h"
#include "tee_time_api.h"

#define HELLO_CMD0 0
#define HELLO_CMD1 1

TEE_Result TA_CreateEntryPoint(void)
{
    TEE_Result ret=TEE_SUCCESS;

    ta_debug("New entry!\n");
    return ret;
}


TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes, TEE_Param params[4], void** sessionContext)
{
    TEE_Result ret=TEE_SUCCESS;
    ta_debug("New session!\n");

    return ret;
}

TEE_Result TA_InvokeCommandEntryPoint(void* session_context, uint32_t cmd_id, uint32_t paramTypes, TEE_Param params[4])
{
    TEE_Result ret=TEE_SUCCESS;
    
    switch(cmd_id) {
	case HELLO_CMD0:
		ta_debug("Hello, Secure World!\n");
		params[3].value.a = ')';
		break;
	case HELLO_CMD1:
		params[3].value.a = ')';
		ta_debug("%s\n", params[0].memref.buffer);
		ta_debug("%s\n", params[1].memref.buffer);
		break;
	default:
		ta_debug("Invalid command!\n");
		break;
    }
    
    return  ret;
}

void TA_CloseSessionEntryPoint(void* session_context)
{
    ta_debug("Close session!\n");
}

void TA_DestroyEntryPoint(void)
{
    ta_debug("Destroy entry!\n");
}
