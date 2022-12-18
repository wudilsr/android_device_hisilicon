#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "tee_client_api.h"
#include "CommomData_for_TestSuite.h"

int main(void)
{
    TEEC_Context context;
    TEEC_Result result;

    result = TEEC_InitializeContext(
               INVALID_NOT_EXISTING_TEE,
               &context);
    if (result == TEEC_SUCCESS) {
        printf("InitializeContext_NotExistingTEE: TEEC_InitializeContext context failed\n");
        TEEC_FinalizeContext(&context);
        goto error;
    }

    printf("InitializeContext_NotExistingTEE success\n");
    return 0;
error:
    return -1;
}
