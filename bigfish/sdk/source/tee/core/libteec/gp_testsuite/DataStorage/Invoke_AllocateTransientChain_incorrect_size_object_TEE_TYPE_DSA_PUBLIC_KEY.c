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

TEEC_Result Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DSA_PUBLIC_KEY(void)
{
    TEEC_Operation operation;
    TEEC_Result result;
    uint32_t OUT_ExpectedReturn = TEE_ERROR_NOT_SUPPORTED ;
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);
    operation.params[0].value.a = TEE_TYPE_DSA_PUBLIC_KEY  ;
    operation.params[0].value.b = WRONG_SIZE ;

    result = TEEC_InvokeCommand(&session, CMD_AllocateTransientChain, &operation, &origin);
    if (result != OUT_ExpectedReturn) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        printf("OUT_ExpectedReturn is 0x%x\n",OUT_ExpectedReturn);
        goto error;
    }
    return TEEC_SUCCESS;
    error:
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

    if(TEEC_SUCCESS != Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DSA_PUBLIC_KEY())
    {
        TEEC_Error("TestCase Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DSA_PUBLIC_KEY is Failed!\n");
        goto error;
    }
    printf("TestCase Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DSA_PUBLIC_KEY is Successful!\n");

    TEEC_CloseSession(&session);
cleanup_2:
    TEEC_FinalizeContext(&context);
cleanup_1:
    return TEEC_SUCCESS;
    error:
        TEEC_CloseSession(&session);
        TEEC_FinalizeContext(&context);
        return result;
}
