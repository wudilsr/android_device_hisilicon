/*6PASS*/
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

TEEC_Result Invoke_InitObjectAndAttributes_buffer_too_small(TEEC_Context* context)
{
    TEEC_Result result; 
    TEEC_Operation operation;
    TEEC_SharedMemory shrdMem01, shrdMem02;
    uint32_t OUT_ExpectedReturn = TEE_ERROR_TOO_SHORT_BUFFER ;

    //allocate shared memory 
    shrdMem01.size = BIG_SIZE;
    shrdMem01.flags = TEEC_MEM_INPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem01);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_InitObjectAndAttributes_buffer_too_small: TEEC_AllocateSharedMemory shrdMem01 failed\n");
        goto error;
    }

    memset(shrdMem01.buffer, 0, shrdMem01.size);
    shrdMem02.size = DS_BIG_SIZE;
    shrdMem02.flags = TEEC_MEM_INPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem02);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_InitObjectAndAttributes_buffer_too_small: TEEC_AllocateSharedMemory shrdMem02 failed\n");
        goto error2;
    }
    memset(shrdMem02.buffer, 0, shrdMem02.size);

    //config params
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_PARTIAL_INPUT,
            TEEC_MEMREF_PARTIAL_INPUT,
            TEEC_VALUE_INPUT);

    retrieveBufferFromUint32(TEE_ATTR_SECRET_VALUE , shrdMem01.buffer);
    retrieveBufferFromUint32(0, shrdMem01.buffer+4);
    retrieveBufferFromUint32(sizeof(TEE_ATTR_HMAC_SHA512_512_VALUE01  ), shrdMem01.buffer+8);
    
    void * p2=shrdMem02.buffer;
    strncpy(p2,TEE_ATTR_HMAC_SHA512_512_VALUE01  ,sizeof(TEE_ATTR_HMAC_SHA512_512_VALUE01  ));

    operation.params[0].value.a = TEE_TYPE_HMAC_SHA512 ;
    operation.params[0].value.b = SIZE_HMAC_SHA512_512 ;
    
    operation.params[1].memref.parent = &shrdMem01;
    operation.params[1].memref.size = 1*12;
    operation.params[1].memref.offset = OFFSET0 ;
    
    operation.params[2].memref.parent = &shrdMem02;
    operation.params[2].memref.size = DS_BIG_SIZE;
    operation.params[2].memref.offset = OFFSET0 ;
    
    operation.params[3].value.b = 0;

    //IN_SubTestCase 
    operation.params[3].value.a = CASE_GET_OBJECT_BUFFER_ATTRIB_TOO_SHORT_BUFFER  ;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != OUT_ExpectedReturn) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error1;
    }
    result = TEEC_SUCCESS;

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
    if((result= Invoke_InitObjectAndAttributes_buffer_too_small(&context)) != 0)   //CASE_GET_OBJECT_BUFFER_ATTRIB_BIT28
    {
        TEEC_Error("Invoke_InitObjectAndAttributes_buffer_too_small is failed!\n");
        goto error;
    }
    printf("Invoke_InitObjectAndAttributes_buffer_too_small is successful!\n");

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
