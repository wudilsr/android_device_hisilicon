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


TEEC_Result Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_Low(TEEC_Context *context)
{
    TEEC_Result result; 
    TEEC_Operation operation;
    TEEC_SharedMemory shrdMem01, shrdMem02;
    uint32_t OUT_ExpectedReturn = TEEC_SUCCESS ;
    //allocate shared memory 
    shrdMem01.size = BIG_SIZE;
    shrdMem01.flags = TEEC_MEM_INPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem01);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_Low: TEEC_AllocateSharedMemory shrdMem01 failed\n");
        goto error;
    }

    memset(shrdMem01.buffer, 0xBB, 300);
    shrdMem02.size = DS_BIG_SIZE;
    shrdMem02.flags = TEEC_MEM_OUTPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem02);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_Low: TEEC_AllocateSharedMemory shrdMem02 failed\n");
        goto error2;
    }
    memset(shrdMem02.buffer, 0, shrdMem02.size);

    //config params
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_PARTIAL_INPUT,
            TEEC_MEMREF_PARTIAL_OUTPUT);

    operation.params[0].value.a = TEE_DATA_SEEK_SET ;
    operation.params[0].value.b = OFFSET_LOW ;

    operation.params[1].value.a = OFFSET_HIGH ;
    operation.params[1].value.b = 0 ;
    
    operation.params[2].memref.parent = &shrdMem01;
    operation.params[2].memref.size = 300;
    operation.params[2].memref.offset = OFFSET0 ;
    
    operation.params[3].memref.parent = &shrdMem02;
    operation.params[3].memref.size = DS_BIG_SIZE;
    operation.params[3].memref.offset = OFFSET0 ;
    result = TEEC_InvokeCommand(&session, CMD_DS_SeekWriteReadObjectData , &operation, &origin);
    if (result != OUT_ExpectedReturn) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        printf("OUT_ExpectedReturn is 0x%x\n",OUT_ExpectedReturn);
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
    if((result= Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_Low(&context)) != 0)   //CASE_GET_OBJECT_BUFFER_ATTRIB_BIT28
    {
        TEEC_Error("Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_Low is failed\n");
        goto error;
    }
    printf("Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_Low is successful!\n");
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
