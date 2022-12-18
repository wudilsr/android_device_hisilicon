#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tee_client_api.h"
#include "CommomData_for_TestSuite.h"
#include "TCA_DS.h"


#define NOMINAL_CASE (0)

TEEC_Result Invoke_Remember_Expected_ParamTypes(TEEC_Context* context,TEEC_Session *session)
{
    TEEC_Operation operation;
    TEEC_SharedMemory shrdMem01, shrdMem02;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_RSA_KEYPAIR;
    operation.params[0].value.b = SIZE_RSA_KEYPAIR_2048;

    /*(uint_32)$IN_AttributeID_1$|(uint_32)offset of  $IN_Attrib_Value_1$ in SharedMem2||(uint_32)length of $IN_Attrib_Value_1$...*/
    shrdMem01.size = BIG_SIZE;
    shrdMem01.flags = TEEC_MEM_INPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem01);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_GenerateKey_TEE_TYPE_RSA_KEYPAIR_correct_size_handle_different_from_TEE_HANDLE_NULL: TEEC_AllocateSharedMemory shrdMem01 failed\n");
        goto error;
    }
    memset(shrdMem01.buffer, 0, 3*3*4);
    operation.params[1].memref.parent = &shrdMem01;
    operation.params[1].memref.size = 3*3*4;
    operation.params[1].memref.offset = OFFSET0;

    /*(uint_32)$IN_AttributeID_1$|(uint_32)offset of  $IN_Attrib_Value_1$ in SharedMem2||(uint_32)length of $IN_Attrib_Value_1$...*/
    shrdMem02.size = BIG_SIZE;
    shrdMem02.flags = TEEC_MEM_INPUT;
    result = TEEC_AllocateSharedMemory(context, &shrdMem02);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_GenerateKey_TEE_TYPE_RSA_KEYPAIR_correct_size_handle_different_from_TEE_HANDLE_NULL: TEEC_AllocateSharedMemory shrdMem01 failed\n");
        goto clean1;
    }
    memset(shrdMem02.buffer, 0, 3*3*4);
    operation.params[2].memref.parent = &shrdMem02;
    operation.params[2].memref.size = 3*3*4;
    operation.params[2].memref.offset = OFFSET0;

    operation.params[3].value.a = NOMINAL_CASE;
    operation.params[3].value.b = TEE_TYPE_RSA_KEYPAIR;


    result = TEEC_InvokeCommand(
        session,
        CMD_DS_GenerateKey,
        &operation,
        NULL);

clean2:
    TEEC_ReleaseSharedMemory(&shrdMem02);
clean1:
    TEEC_ReleaseSharedMemory(&shrdMem01);
error:
    return result;



}

int main(void)
{
    TEEC_Context context;
    TEEC_Session session;
    TEEC_UUID uuid = UUID_TTA_testingInternalAPI_dataStorage;
    TEEC_Result result;
    uint32_t origin = TEEC_ORIGIN_TRUSTED_APP;

    result = TEEC_InitializeContext(
               NULL,
               &context);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_GenerateKey_TEE_TYPE_RSA_KEYPAIR_correct_size_handle_different_from_TEE_HANDLE_NULL: TEEC_InitializeContext failed\n");
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
        printf("Invoke_GenerateKey_TEE_TYPE_RSA_KEYPAIR_correct_size_handle_different_from_TEE_HANDLE_NULL: TEEC_OpenSession failed, result=0x%x\n", result);
        goto clean;
    }

    result = Invoke_Remember_Expected_ParamTypes(&context, &session);
    if (result != TEEC_SUCCESS) {
        printf("Invoke_GenerateKey_TEE_TYPE_RSA_KEYPAIR_correct_size_handle_different_from_TEE_HANDLE_NULL: Invoke_Remember_Expected_ParamTypes failed, result=0x%x\n", result);
        goto clean1;
    }


    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);

    printf("Invoke_GenerateKey_TEE_TYPE_RSA_KEYPAIR_correct_size_handle_different_from_TEE_HANDLE_NULL success\n");
    return 0;
clean1:
    TEEC_CloseSession(&session);
clean:
    TEEC_FinalizeContext(&context);
error:
    return -1;
}
