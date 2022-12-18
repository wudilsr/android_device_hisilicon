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
        TEE_PARAM_TYPE_MEMREF_INPUT,
        TEE_PARAM_TYPE_MEMREF_OUTPUT,
        TEE_PARAM_TYPE_NONE,
        TEE_PARAM_TYPE_NONE);
    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    return TEEC_InvokeCommand(
        session,
        COMMAND_TTA_Remember_Expected_ParamTypes,
        &operation,
        NULL);
}

TEEC_Result Invoke_2param_Copy_ParamIn_to_ParamOut(TEEC_Context *context, TEEC_Session *session)
{
    TEEC_SharedMemory shrdMem01, shrdMem02;
    TEEC_Operation operation;
    TEEC_Result result;
    uint8_t data01[BIG_SIZE], data02[BIG_SIZE];

    shrdMem01.buffer = data01;
    shrdMem01.size = BIG_SIZE;
    shrdMem01.flags = TEEC_MEM_INPUT;
    result = TEEC_RegisterSharedMemory(context, &shrdMem01);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_2param_Copy_ParamIn_to_ParamOut: TEEC_RegisterSharedMemory shrdMem01 failed\n");
        goto error;
    }

    shrdMem02.buffer = data02;
    shrdMem02.size = BIG_SIZE;
    shrdMem02.flags = TEEC_MEM_OUTPUT;
    result = TEEC_RegisterSharedMemory(context, &shrdMem02);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_2param_Copy_ParamIn_to_ParamOut: TEEC_RegisterSharedMemory shrdMem02 failed\n");
        goto clean1;
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT,
        TEEC_NONE,
        TEEC_NONE);
    *(uint32_t*)shrdMem01.buffer = VALUE01;
    operation.params[0].memref.parent = &shrdMem01;
    operation.params[0].memref.offset = OFFSET0;
    operation.params[0].memref.size = SIZE_VALUE01;
    operation.params[1].memref.parent = &shrdMem02;
    operation.params[1].memref.offset = OFFSET0;
    operation.params[1].memref.size = SIZE_VALUE01;

    result = TEEC_InvokeCommand(
        session,
        COMMAND_TTA_Copy_ParamIn_to_ParamOut,
        &operation,
        NULL);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_2param_Copy_ParamIn_to_ParamOut: TEEC_InvokeCommand failed, result = 0x%x\n", result);
        goto clean2;
    }

    if (*(uint32_t*)shrdMem02.buffer != VALUE01) {
        printf("Invoke_2param_Copy_ParamIn_to_ParamOut: *(uint32_t*)shrdMem02.buffer=0x%x\n", *(uint32_t*)shrdMem02.buffer);
        result = TEEC_ERROR_GENERIC;
    }
    if (operation.params[1].memref.size != SIZE_VALUE01) {
        printf("Invoke_2param_Copy_ParamIn_to_ParamOut: operation.params[1].memref.size=0x%x\n", operation.params[1].memref.size);
        result = TEEC_ERROR_GENERIC;
    }

clean2:
    TEEC_ReleaseSharedMemory(&shrdMem02);
clean1:
    TEEC_ReleaseSharedMemory(&shrdMem01);
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
        printf("Invoke_2param_memrefPartialIn_memrefPartialOut_registered: TEEC_InitializeContext failed\n");
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
        printf("Invoke_2param_memrefPartialIn_memrefPartialOut_registered: TEEC_OpenSession failed, result=0x%x\n", result);
        goto clean;
    }

    result = Invoke_Remember_Expected_ParamTypes(&session);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_2param_memrefPartialIn_memrefPartialOut_registered: Invoke_Remember_Expected_ParamTypes failed, result=0x%x\n", result);
        goto clean1;
    }

    result = Invoke_2param_Copy_ParamIn_to_ParamOut (&context, &session);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_2param_memrefPartialIn_memrefPartialOut_registered: Invoke_2param_Copy_ParamIn_to_ParamOut  failed, result=0x%x\n", result);
        goto clean1;
    }

    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);

    printf("Invoke_2param_memrefPartialIn_memrefPartialOut_registered success\n");
    return 0;
clean1:
    TEEC_CloseSession(&session);
clean:
    TEEC_FinalizeContext(&context);
error:
    return -1;
}

