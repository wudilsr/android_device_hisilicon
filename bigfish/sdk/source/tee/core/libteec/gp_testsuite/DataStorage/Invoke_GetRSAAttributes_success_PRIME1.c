#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "tee_client_api.h"
#include "tee_client_id.h"
#include "client_ds.h"

static TEEC_Session session;
static uint32_t origin;

void retrieveBufferFromUint32(uint32_t n, char *buffer)
{
   uint32_t i;
   for (i=0;i<4;i++)
    {
        buffer[i] = (n<<i*8)>>24;
    }
   return;
}

TEEC_Result Invoke_GetRSAAttributes_success_PRIME1(TEEC_Context *context)
{
    TEEC_Result result; 
    TEEC_Operation operation;
    TEEC_SharedMemory shrdMem01, shrdMem02, shrdMem03, shrdMem04;
    uint32_t offset = 0;
    uint32_t OUT_ExpectedReturn = TEEC_SUCCESS;

    //allocate shared memory 
    shrdMem01.size = DS_BIG_SIZE;
    shrdMem01.flags = TEEC_MEM_OUTPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem01);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_GetRSAAttributes_success_PRIME1: TEEC_AllocateSharedMemory shrdMem01 failed\n");
        goto error;
    }
    memset(shrdMem01.buffer, 0, shrdMem01.size);
    
    shrdMem02.size = DS_BIG_SIZE;
    shrdMem02.flags = TEEC_MEM_OUTPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem02);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_GetRSAAttributes_success_PRIME1: TEEC_AllocateSharedMemory shrdMem02 failed\n");
        goto error2;
    }
    memset(shrdMem02.buffer, 0, shrdMem02.size);

    shrdMem03.size = DS_BIG_SIZE;
    shrdMem03.flags = TEEC_MEM_OUTPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem03);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_GetRSAAttributes_success_PRIME1: TEEC_AllocateSharedMemory shrdMem03failed\n");
        goto error0;
    }
    memset(shrdMem03.buffer, 0, shrdMem03.size);

    shrdMem04.size = DS_BIG_SIZE;
    shrdMem04.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem04);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_GetRSAAttributes_success_PRIME1: TEEC_AllocateSharedMemory shrdMem04failed\n");
        goto error_1;
    }
    memset(shrdMem04.buffer, 0, shrdMem04.size);

    //config params
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_MEMREF_PARTIAL_INOUT,
            TEEC_MEMREF_PARTIAL_OUTPUT,
            TEEC_MEMREF_PARTIAL_OUTPUT,
            TEEC_MEMREF_PARTIAL_OUTPUT);

    retrieveBufferFromUint32(BUFFER_ATTRIBUTE, shrdMem04.buffer);
    retrieveBufferFromUint32(TEE_ATTR_RSA_PRIME1, shrdMem04.buffer+4);

    operation.params[0].memref.parent = &shrdMem04;
    operation.params[0].memref.size = DS_BIG_SIZE;
    operation.params[0].memref.offset = OFFSET0 ;
    
    operation.params[1].memref.parent = &shrdMem01;
    operation.params[1].memref.size = DS_BIG_SIZE;
    operation.params[1].memref.offset = OFFSET0 ;
    
    operation.params[2].memref.parent = &shrdMem02;
    operation.params[2].memref.size = DS_BIG_SIZE;
    operation.params[2].memref.offset = OFFSET0 ;
    
    operation.params[3].memref.parent = &shrdMem03;
    operation.params[3].memref.size = DS_BIG_SIZE;
    operation.params[3].memref.offset = OFFSET0 ;
    
    result = TEEC_InvokeCommand(&session, CMD_DS_GetRSAAttributes , &operation, &origin);
    if (result != OUT_ExpectedReturn) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        printf("OUT_ExpectedReturn is 0x%x\n",OUT_ExpectedReturn);
        goto error1;
    }
    
    result = TEEC_SUCCESS;
    error_1:
         TEEC_ReleaseSharedMemory(&shrdMem04);
    error0:
         TEEC_ReleaseSharedMemory(&shrdMem03);
    error1:
         TEEC_ReleaseSharedMemory(&shrdMem02);
    error2:
         TEEC_ReleaseSharedMemory(&shrdMem01);
         
    error:
        return result;
}

int main(void)
{
    TEEC_Context context;
    TEEC_Result result;

    result = TEEC_InitializeContext(NULL, &context);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    result = TEEC_OpenSession(&context, &session, &EXAMPLE_uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    
    //start test
    if((result= Invoke_GetRSAAttributes_success_PRIME1(&context)) != 0)   //CASE_GET_OBJECT_BUFFER_ATTRIB_BIT28
    {
        TEEC_Error("Invoke_GetRSAAttributes_success_PRIME1 is failed\n");
        goto error;
    }
    printf("Invoke_GetRSAAttributes_success_PRIME1 is successful!\n");

    TEEC_CloseSession(&session);
cleanup_2:
    TEEC_FinalizeContext(&context);
cleanup_1:
    return 0;
    error:
        TEEC_CloseSession(&session);
        TEEC_FinalizeContext(&context);
        return result;
}
