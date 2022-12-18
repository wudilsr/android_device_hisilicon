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
    TEEC_UUID uuid = UUID_TTA_answerSuccessTo_OpenSession_Invoke;
    TEEC_Result result;

    result = TEEC_InitializeContext(
               NULL,
               &context);
    if (result != TEEC_SUCCESS) {
        printf("OpenSession_success_nullReturnOrigin: TEEC_InitializeContext failed\n");
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
        printf("OpenSession_success_nullReturnOrigin: TEEC_OpenSession failed, result=0x%x\n", result);
        goto clean;
    }

    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);

    printf("OpenSession_success_nullReturnOrigin success\n");
    return 0;
clean:
    TEEC_FinalizeContext(&context);
error:
    return -1;
}
