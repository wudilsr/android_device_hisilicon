#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "tee_client_api.h"
#include "CommomData_for_TestSuite.h"

int main(void)
{
    TEEC_Context context;
    TEEC_Session session;
    TEEC_Operation operation;
    TEEC_UUID uuid = UUID_TTA_check_OpenSession_with_4_parameters;
    TEEC_Result result;

    result = TEEC_InitializeContext(
               NULL,
               &context);
    if (result != TEEC_SUCCESS) {
        printf("OpenSession_with_operation_parameters: TEEC_InitializeContext failed\n");
        goto error;
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = VALUE01;
    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    operation.params[1].value.a = TEEC_VALUE_UNDEF;
    operation.params[1].value.b = VALUE01;
    operation.params[2].value.a = VALUE01;
    operation.params[2].value.b = VALUE01;
    operation.params[3].value.a = VALUE01;
    operation.params[3].value.b = VALUE02;
    result = TEEC_OpenSession(
        &context,
        &session,
        &uuid,
        TEEC_LOGIN_PUBLIC,
        NULL,
        &operation,
        NULL);
    if (result != TEEC_SUCCESS) {
        printf("OpenSession_with_operation_parameters: TEEC_OpenSession failed, result=0x%x\n", result);
        goto clean;
    }

    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);

    printf("OpenSession_with_operation_parameters success\n");
    return 0;
clean:
    TEEC_FinalizeContext(&context);
error:
    return -1;
}
