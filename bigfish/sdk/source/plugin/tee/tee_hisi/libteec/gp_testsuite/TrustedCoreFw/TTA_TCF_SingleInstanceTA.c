#include "tee_client_api.h"
#include "tee_client_id.h"
#include <string.h>

/** Command ids **/
#define CMD_TEE_GetInstanceData                             0x00000101
#define CMD_TEE_SetInstanceData                             0x00000102

int main(void)
{
    TEEC_Context context;
    TEEC_Session session;
    TEEC_UUID uuid = { 0x534D4152, 0x5443, 0x534C, { 0x53, 0x47, 0x4C, 0x49, 0x4E, 0x53, 0x54, 0x43 } };
    TEEC_Result result;
    TEEC_Operation operation;
#define TEST_BUFF_SIZE 64
    char test_in_buff[TEST_BUFF_SIZE] = {0}, test_out_buff[TEST_BUFF_SIZE] = {0};

    TEEC_InitializeContext(NULL, &context);

    result = TEEC_OpenSession(
                    &context,
                    &session,
                    &uuid,
                    TEEC_LOGIN_PUBLIC,
                    NULL,
                    NULL,
                    NULL);

    if(result != TEEC_SUCCESS) {
        goto err_2;
    }

    memcpy(test_in_buff, "This is a TTA TCF Single Instace TA Test!", sizeof("This is a TTA TCF Single Instace TA Test!"));
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_MEMREF_TEMP_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].tmpref.buffer = test_in_buff;
    operation.params[0].tmpref.size = TEST_BUFF_SIZE;

    result = TEEC_InvokeCommand(
                 &session,
                 CMD_TEE_SetInstanceData,
                 &operation,
                 NULL);

    if(result != TEEC_SUCCESS){
        printf("CMD_TEE_SetInstanceData failed\n");
        goto err_1;
    }

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].tmpref.buffer = test_out_buff;
    operation.params[0].tmpref.size = TEST_BUFF_SIZE;

    result = TEEC_InvokeCommand(
                 &session,
                 CMD_TEE_GetInstanceData,
                 &operation,
                 NULL);

    if(result != TEEC_SUCCESS){
        printf("CMD_TEE_GetInstanceData failed\n");
        goto err_1;
    }

    if(memcmp(test_in_buff, test_out_buff, TEST_BUFF_SIZE)){
        printf("Instance data error: in-%s, out-%s\n", test_in_buff, test_out_buff);
        goto err_1;
    }

    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);

    if(result == TEEC_SUCCESS)
        printf("TTA_TCF_SingleInstanceTA test success\n");

    return 0;

err_1:
    TEEC_CloseSession(&session);
err_2:
    TEEC_FinalizeContext(&context);

    return -1;
}
