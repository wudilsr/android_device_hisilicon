#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "tee_client_api.h"

void thread02(TEEC_Result *ret)
{
    TEEC_Context context02;

    *ret = TEEC_InitializeContext(
               NULL,
               &context02);
    if(*ret != TEEC_SUCCESS) {
        printf("InitializeContext_concurrentContext: TEEC_InitializeContext context02 failed\n");
    } else {
        TEEC_FinalizeContext(&context02);
    }
}

int main(void)
{
    TEEC_Context context01;
    TEEC_Result result, pret = 1;
    pthread_t id;

    pthread_create(&id, NULL, thread02, &pret);

    result = TEEC_InitializeContext(
               NULL,
               &context01);
    if (result != TEEC_SUCCESS) {
        printf("InitializeContext_concurrentContext: TEEC_InitializeContext context01 failed\n");
        goto error;
    }
    TEEC_FinalizeContext(&context01);

    pthread_join(id, NULL);
    if (pret != TEEC_SUCCESS)
        goto error;

    printf("InitializeContext_concurrentContext success\n");
    return 0;
error:
    return -1;
}
