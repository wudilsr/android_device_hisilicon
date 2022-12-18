#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tee_client_api.h"
#include "CommomData_for_TestSuite.h"

int main(void)
{
    TEEC_Context context;
    TEEC_Session session;
    TEEC_UUID uuid = UUID_TTA_answerSuccessTo_OpenSession_Invoke;
    TEEC_Result result;
    uint32_t origin = TEEC_ORIGIN_TRUSTED_APP;

    result = TEEC_InitializeContext(
               NULL,
               &context);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_success_originTrustedApp: TEEC_InitializeContext failed\n");
        goto error;
    }

    result = TEEC_OpenSession(
        &context,
        &session,
        &uuid,
        TEEC_LOGIN_PUBLIC,
        NULL,
        NULL,
        &origin);
    if ((result != TEEC_SUCCESS) || (origin != TEEC_ORIGIN_TRUSTED_APP)) {
        printf("Invoke_success_originTrustedApp: TEEC_OpenSession failed, result=0x%x, origin=%d\n", result, origin);
        goto clean;
    }

    result = TEEC_InvokeCommand(
        &session,
        COMMAND_TTA_Check_Expected_ParamTypes,
        NULL,
        &origin);
    if ((result != TEEC_SUCCESS) || (origin != TEEC_ORIGIN_TRUSTED_APP)) {
        printf("Invoke_success_originTrustedApp: TEEC_InvokeCommand failed, result=0x%x, origin=%d\n", result, origin);
        goto clean1;
    }

    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);

    printf("Invoke_success_originTrustedApp success\n");
    return 0;
clean1:
    TEEC_CloseSession(&session);
clean:
    TEEC_FinalizeContext(&context);
error:
    return -1;
}
