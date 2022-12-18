/*1PASS*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "tee_client_api.h"
#include "tee_client_id.h"
#include "client_ds.h"

static TEEC_Session session;
static uint32_t origin;

TEEC_Result Invoke_OpenPersistentObject_Access_conflict(TEEC_Context *context)
{
    TEEC_Result result; 
    TEEC_Operation operation;
    uint32_t OUT_ExpectedReturn = TEE_ERROR_ACCESS_CONFLICT ;

    //config params
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    result = TEEC_InvokeCommand(&session, CMD_DS_OpenPersistentObject_conflict  , &operation, &origin);
    if (result != OUT_ExpectedReturn) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        printf("OUT_ExpectedReturn is 0x%x\n",OUT_ExpectedReturn);
        goto error1;
    }
    
    result = TEEC_SUCCESS;

    error1:
        return result;
}

int main(void)
{
    TEEC_Context context;
    TEEC_Result result;

    result = TEEC_InitializeContext(NULL, &context);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    result = TEEC_OpenSession(&context, &session, &EXAMPLE_uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    
    //start test
    if((result= Invoke_OpenPersistentObject_Access_conflict(&context)) != 0)   //CASE_GET_OBJECT_BUFFER_ATTRIB_BIT28
    {
        TEEC_Error("Invoke_OpenPersistentObject_Access_conflict is failed!\n");
        goto error;
    }
    printf("Invoke_OpenPersistentObject_Access_conflict is successful!\n");

    TEEC_CloseSession(&session);
cleanup_2:
    TEEC_FinalizeContext(&context);
cleanup_1:
    return 0;
    error:
        TEEC_CloseSession(&session);
        TEEC_FinalizeContext(&context);
        return result;
}
