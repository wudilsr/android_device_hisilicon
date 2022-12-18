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
    TEEC_UUID uuid = UUID_TTA_answerErrorTo_OpenSession;
    TEEC_Result result;
    uint32_t origin = TEEC_ORIGIN_TRUSTED_APP;

    result = TEEC_InitializeContext(
               NULL,
               &context);
    if (result != TEEC_SUCCESS) {
        printf("OpenSession_error_originTrustedApp: TEEC_InitializeContext failed\n");
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
    if (result == TEEC_SUCCESS) {
        printf("OpenSession_error_originTrustedApp: TEEC_OpenSession failed\n");
        TEEC_CloseSession(&session);
        goto clean;
    }

    if ((result != TEEC_ERROR_GENERIC) || (origin != TEEC_ORIGIN_TRUSTED_APP)) {
        printf("OpenSession_error_originTrustedApp: result failed, result=0x%x, origin=%d\n", result, origin);
        goto clean;
    }

    TEEC_FinalizeContext(&context);

    printf("OpenSession_error_originTrustedApp success\n");
    return 0;
clean:
    TEEC_FinalizeContext(&context);
error:
    return -1;
}
