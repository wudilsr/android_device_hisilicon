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
        TEE_PARAM_TYPE_VALUE_INPUT,
        TEE_PARAM_TYPE_VALUE_OUTPUT,
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
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_OUTPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = VALUE01;
    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    operation.params[1].value.a = TEEC_VALUE_UNDEF;
    operation.params[1].value.b = TEEC_VALUE_UNDEF;

    result = TEEC_InvokeCommand(
        session,
        COMMAND_TTA_Copy_ParamIn_to_ParamOut,
        &operation,
        NULL);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_2param_Copy_ParamIn_to_ParamOut: TEEC_InvokeCommand failed, result = 0x%x\n", result);
        goto error;
    }

    if (operation.params[1].value.a != VALUE01) {
        printf("Invoke_2param_Copy_ParamIn_to_ParamOut: operation.params[1].value.a=0x%x\n", operation.params[1].value.a);
        result = TEEC_ERROR_GENERIC;
    }
    if (operation.params[1].value.b != TEEC_VALUE_UNDEF) {
        printf("Invoke_2param_Copy_ParamIn_to_ParamOut: operation.params[1].value.b=0x%x\n", operation.params[1].value.b);
        result = TEEC_ERROR_GENERIC;
    }

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
        printf("Invoke_2param_valueIn_valueOut: TEEC_InitializeContext failed\n");
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
        printf("Invoke_2param_valueIn_valueOut: TEEC_OpenSession failed, result=0x%x\n", result);
        goto clean;
    }

    result = Invoke_Remember_Expected_ParamTypes(&session);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_2param_valueIn_valueOut: Invoke_Remember_Expected_ParamTypes failed, result=0x%x\n", result);
        goto clean1;
    }

    result = Invoke_2param_Copy_ParamIn_to_ParamOut (&context, &session);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_2param_valueIn_valueOut: Invoke_2param_Copy_ParamIn_to_ParamOut  failed, result=0x%x\n", result);
        goto clean1;
    }

    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);

    printf("Invoke_2param_valueIn_valueOut success\n");
    return 0;
clean1:
    TEEC_CloseSession(&session);
clean:
    TEEC_FinalizeContext(&context);
error:
    return -1;
}
