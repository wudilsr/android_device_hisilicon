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

void retrieveBufferFromUint32(uint32_t n, char buffer[])
{
   uint32_t i;
   for (i=0;i<4;i++)
    {
        buffer[i] = (n<<i*8)>>24;
    }
   /* NOTE : Tools must write integers in BIG ENDIAN format */
   return;
}

TEEC_Result Invoke_GenerateKey_BadParameters_TEE_TYPE_DH_KEYPAIR(TEEC_Context*  context)
{
    TEEC_Operation operation;
    TEEC_Result result;
    TEEC_SharedMemory sharedMem1, sharedMem2;

    //attribute 1
    uint32_t attrID1 = TEE_ATTR_DSA_PRIME  ;
    char *attrbuff_addr1;
    attrbuff_addr1 = TEE_ATTR_DH_PRIME_VALUE_WRONG01;
    uint32_t attrbuff_len1 = sizeof(TEE_ATTR_DH_PRIME_VALUE_WRONG01);

    //attribute 2
    uint32_t attrID2 = TEE_ATTR_DH_BASE ;
    char *attrbuff_addr2 = TEE_ATTR_DH_BASE_VALUE01;
    uint32_t attrbuff_len2 = sizeof(TEE_ATTR_DH_BASE_VALUE01);

    //attribute 3
    uint32_t attrID3 = TEE_ATTR_NONE ;
    char *attrbuff_addr3 = NULL;
    uint32_t attrbuff_len3 = 0;

    /**allocate shared memory 1, right test case**/
    sharedMem1.size = BIG_SIZE;
    sharedMem1.flags = TEEC_MEM_INPUT;
    result = TEEC_AllocateSharedMemory(
                context,
                &sharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        return 1;
    }

    retrieveBufferFromUint32(attrID1, (char *)(sharedMem1.buffer));
    retrieveBufferFromUint32(0, sharedMem1.buffer+4);
    retrieveBufferFromUint32(attrbuff_len1, sharedMem1.buffer+8);

    retrieveBufferFromUint32(attrID2, sharedMem1.buffer+12);
    retrieveBufferFromUint32(attrbuff_len1, sharedMem1.buffer+16);
    retrieveBufferFromUint32(attrbuff_len2, sharedMem1.buffer+20);

    retrieveBufferFromUint32(0, sharedMem1.buffer+24);
    retrieveBufferFromUint32(0, sharedMem1.buffer+28);
    retrieveBufferFromUint32(0, sharedMem1.buffer+32);

    /**allocate shared memory 2, right test case**/
    sharedMem2.size = DS_BIG_SIZE;
    sharedMem2.flags = TEEC_MEM_INPUT;
    result = TEEC_AllocateSharedMemory(
                context,
                &sharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        return 1;
    }

    strncpy(sharedMem2.buffer, attrbuff_addr1,attrbuff_len1);
    strncpy(sharedMem2.buffer+attrbuff_len1, attrbuff_addr2,attrbuff_len2);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_PARTIAL_INPUT,
            TEEC_MEMREF_PARTIAL_INPUT,
            TEEC_VALUE_INPUT);

    operation.params[0].value.a = TEE_TYPE_DH_KEYPAIR;
    operation.params[0].value.b = SIZE_DH_KEYPAIR_1024;
    operation.params[1].memref.parent = &sharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 36;
    operation.params[2].memref.parent = &sharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = attrbuff_len2+attrbuff_len1;
    operation.params[3].value.a = CASE_GENERATE_KEY_BAD_PARAMETER;
    operation.params[3].value.b = SIZE_DH_KEYPAIR_1024;

    result = TEEC_InvokeCommand(&session, CMD_GenerateKey, &operation, &origin);
    if (result != TEEC_SUCCESS)
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    TEEC_ReleaseSharedMemory(&sharedMem1);
    TEEC_ReleaseSharedMemory(&sharedMem2);
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

    if(TEEC_SUCCESS != Invoke_GenerateKey_BadParameters_TEE_TYPE_DH_KEYPAIR(&context))
    {
        TEEC_Error("Invoke_GenerateKey_BadParameters_TEE_TYPE_DH_KEYPAIR failed\n");
        goto error;
    }
    printf("Invoke_GenerateKey_BadParameters_TEE_TYPE_DH_KEYPAIR test success!\n");


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
