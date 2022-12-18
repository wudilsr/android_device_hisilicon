#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "tee_client_api.h"
#include "CommomData_for_TestSuite.h"

int main(void)
{
    TEEC_Context context;
    TEEC_SharedMemory sharedMem;
    TEEC_Result result;
    char *testdata = NULL;

    if ((testdata = (char*)malloc(SIZE_VALUE01)) == NULL) {
        printf("Register_In: malloc failed\n");
        goto error;
    }

    result = TEEC_InitializeContext(
               NULL,
               &context);
    if (result != TEEC_SUCCESS) {
        printf("Register_In: TEEC_InitializeContext context failed\n");
        goto error;
    }

    sharedMem.buffer = testdata;
    sharedMem.size = SIZE_VALUE01;
    sharedMem.flags = TEEC_MEM_INPUT;
    result = TEEC_RegisterSharedMemory(
                &context,
                &sharedMem);
    if(result != TEEC_SUCCESS) {
        printf("Register_In: TEEC_RegisterSharedMemory failed\n");
        goto clean;
    }

    TEEC_ReleaseSharedMemory(&sharedMem);
    TEEC_FinalizeContext(&context);
    free(testdata);

    printf("Register_In success\n");
    return 0;
clean:
    TEEC_FinalizeContext(&context);
    free(testdata);
error:
    return -1;
}
