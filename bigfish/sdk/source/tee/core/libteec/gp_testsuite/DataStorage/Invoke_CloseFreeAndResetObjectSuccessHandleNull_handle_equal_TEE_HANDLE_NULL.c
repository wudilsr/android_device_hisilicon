/*PASS*/
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

// test for TEE_HANDLE_NULL
TEEC_Result Invoke_CloseFreeAndResetObjectSuccessHandleNull_handle_equal_TEE_HANDLE_NULL(void)
{
    TEEC_Result result;
    uint32_t OUT_ExpectedReturn = TEEC_SUCCESS;
    result = TEEC_InvokeCommand(&session, CMD_CloseFreeAndResetObjectSuccessHandleNull, NULL, &origin);
    if (result != OUT_ExpectedReturn) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
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

    if(TEEC_SUCCESS != Invoke_CloseFreeAndResetObjectSuccessHandleNull_handle_equal_TEE_HANDLE_NULL())
    {
        TEEC_Error("Invoke_CloseFreeAndResetObjectSuccessHandleNull_handle_equal_TEE_HANDLE_NULL is failed\n");
        goto error;
    }
    printf("Invoke_CloseFreeAndResetObjectSuccessHandleNull_handle_equal_TEE_HANDLE_NULL is successful!\n");

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
