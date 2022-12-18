#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tee_client_api.h"
#include "CommomData_for_TestSuite.h"

TEEC_Result Invoke_Remember_Expected_ParamTypes(TEEC_Session *session)
{
    TEEC_Operation operation;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = TEEC_PARAM_TYPES(
        TEE_PARAM_TYPE_MEMREF_INOUT,
        TEE_PARAM_TYPE_NONE,
        TEE_PARAM_TYPE_NONE,
        TEE_PARAM_TYPE_NONE);
    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    return TEEC_InvokeCommand(
        session,
        COMMAND_TTA_Remember_Expected_ParamTypes,
        &operation,
        NULL);
}

TEEC_Result Invoke_1param_and_check_expectedParameterType(TEEC_Context *context, TEEC_Session *session)
{
    TEEC_SharedMemory shrdMem;
    TEEC_Operation operation;
    TEEC_Result result;
    uint8_t testdata[BIG_SIZE];

    shrdMem.buffer = testdata;
    shrdMem.size = BIG_SIZE;
    shrdMem.flags = TEEC_MEM_INOUT;
    result = TEEC_RegisterSharedMemory(context, &shrdMem);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_1param_memrefPartialInOut_allocated: TEEC_RegisterSharedMemory failed\n");
        goto error;
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_MEMREF_PARTIAL_INOUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    *(uint32_t*)shrdMem.buffer = BIG_VALUE;
    operation.params[0].memref.parent = &shrdMem;
    operation.params[0].memref.offset = OFFSET0;
    operation.params[0].memref.size = BIG_SIZE;

    result = TEEC_InvokeCommand(
        session,
        COMMAND_TTA_Check_Expected_ParamTypes,
        &operation,
        NULL);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_1param_memrefPartialInOut_allocated: TEEC_InvokeCommand failed, result = 0x%x\n", result);
        goto clean;
    }

    if (*(uint32_t*)shrdMem.buffer != BIG_VALUE) {
        printf("Invoke_1param_and_check_expectedParameterType: *(uint32_t*)shrdMem.buffer=0x%x\n", *(uint32_t*)shrdMem.buffer);
        result = TEEC_ERROR_GENERIC;
    }

clean:
    TEEC_ReleaseSharedMemory(&shrdMem);
error:
    return result;
}

int main(void)
{
    TEEC_Context context;
    TEEC_Session session;
    TEEC_UUID uuid = UUID_TTA_testingClientAPI;
    TEEC_Result result;
    uint32_t origin = TEEC_ORIGIN_TRUSTED_APP;

    result = TEEC_InitializeContext(
               NULL,
               &context);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_1param_memrefWhole_registered: TEEC_InitializeContext failed\n");
        goto error;
    }

    result = TEEC_OpenSession(
        &context,
        &session,
        &uuid,
        TEEC_LOGIN_PUBLIC,
        NULL,
        NULL,
        NULL);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_1param_memrefWhole_registered: TEEC_OpenSession failed, result=0x%x\n", result);
        goto clean;
    }

    result = Invoke_Remember_Expected_ParamTypes(&session);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_1param_memrefWhole_registered: Invoke_Remember_Expected_ParamTypes failed, result=0x%x\n", result);
        goto clean1;
    }

    result = Invoke_1param_and_check_expectedParameterType (&context, &session);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_1param_memrefWhole_registered: Invoke_1param_and_check_expectedParameterType   failed, result=0x%x\n", result);
        goto clean1;
    }

    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);

    printf("Invoke_1param_memrefWhole_registered success\n");
    return 0;
clean1:
    TEEC_CloseSession(&session);
clean:
    TEEC_FinalizeContext(&context);
error:
    return -1;
}
