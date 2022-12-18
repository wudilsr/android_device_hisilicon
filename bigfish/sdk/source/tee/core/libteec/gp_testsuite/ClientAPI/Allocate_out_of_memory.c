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

    result = TEEC_InitializeContext(
               NULL,
               &context);
    if (result != TEEC_SUCCESS) {
        printf("Allocate_out_of_memory: TEEC_InitializeContext context failed\n");
        goto error;
    }

    sharedMem.size = SIZE_OVER_MEMORY;
    sharedMem.flags = TEEC_MEM_INPUT ;
    result = TEEC_AllocateSharedMemory(
                &context,
                &sharedMem);
    if(result != TEEC_ERROR_OUT_OF_MEMORY) {
        printf("Allocate_out_of_memory: TEEC_AllocateSharedMemory failed\n");
        TEEC_ReleaseSharedMemory(&sharedMem);
        goto clean;
    }

    TEEC_FinalizeContext(&context);

    printf("Allocate_out_of_memory success\n");
    return 0;
clean:
    TEEC_FinalizeContext(&context);
error:
    return -1;
}
