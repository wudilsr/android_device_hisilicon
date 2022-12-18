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
   /* NOTE : Tools must write integers in BIG ENDIAN format */

   return;
}

//testcase No.31 GetBufferAttribute from object uninitialized
TEEC_Result CCmdGetBufferAttribute_object_uninitialized(void)
{
    TEEC_Operation operation;
    TEEC_Result result;
    uint32_t OUT_ExpectedReturn = TEE_ERROR_ITEM_NOT_FOUND;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.a = objectType;
    operation.params[0].value.b = maxObjectSize;

    result = TEEC_InvokeCommand(&session, CMD_GetBufferAttribute_object_uninitialized, &operation, &origin);
    if (result != OUT_ExpectedReturn) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return TEEC_SUCCESS;
    error:
        return -1;
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
    if((result= CCmdGetBufferAttribute_object_uninitialized()) != 0)
    {
        TEEC_Error("Invoke_GetBufferAttribute_object_uninitialized is failed!\n");
        goto error;
    }
    printf("Invoke_GetBufferAttribute_object_uninitialized is successful!\n");
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
