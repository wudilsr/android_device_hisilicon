#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "tee_client_api.h"
#include "tee_client_id.h"
#include "hi_tz_common.h"


static const TEEC_UUID s_stTeecCipherUUID =
{ 
    0x79b77788, 
    0x9789, 
    0x4a7a, 
    {0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf6} 
};

typedef enum {
    CIPHER_TEST_PRINT_PHY = 0x01,
    CIPHER_TEST_PRINT_VIA,  
    CIPHER_TEST_AES  = 0x10,
    CIPHER_TEST_HMAC,
    CIPHER_TEST_RSA,
    CIPHER_TEST_HASH,
    CIPHER_TEST_DES,
    CIPHER_TEST_RSA_PRIM,
    CIPHER_TEST_RSA_KG,
    CIPHER_TEST_RND,  
    CIPHER_TEST_BUTT,
}CIPHER_TEST;

static int cipher_cmd(TEEC_Session session, unsigned int u32Cmd, unsigned int *pu32Result, 
    unsigned int u32Param1, unsigned int u32Param2)
{
    TEEC_Result result;
    TEEC_Operation operation;
    unsigned int returnOrigin;
    
    operation.started = 1;
    operation.params[0].value.a = u32Cmd; 
    operation.params[1].value.a = 0;
    operation.params[2].value.a = u32Param1;
    operation.params[2].value.b = u32Param2;

    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,
                                            TEEC_VALUE_OUTPUT,
                                            TEEC_VALUE_INPUT,
                                            TEEC_NONE);

    result = TEEC_InvokeCommand(&session, CMD_TZ_TEST, &operation, &returnOrigin);
    if (result != TEEC_SUCCESS) {
        printf("invoke failed, codes=0x%x, returnOrigin=0x%x\n", result, returnOrigin);
        return -1;
    }
    
    *pu32Result = operation.params[1].value.a;
    
    return 0;
}

int main(int argc,char *argv[])
{
    TEEC_Context context;
    TEEC_Session session;
    unsigned int result;
    unsigned int mode = 0;
    
    if (argc <= 1)
    {
        printf("Usage: teec_cipher mode \n"
               "       mode: 0--AES Test\n"
               "             1--HAMC Test\n"
               "             2--RSA Test\n"
               "             3--HASH Test\n"
               "             4--DES Test\n"
               "             5--RSA PRIM Test\n"
               "             6--RSA KG Test\n"
               "             7--RND Test\n");
        printf("Example:./teec_cipher 0\n");
        return -1;
    }
        
    if (argc >= 2)
    {
        mode = strtol(argv[1],NULL,0);
        printf("mode = %d\n",mode);
    }

    usleep(100*1000);

    result = TEEC_InitializeContext(NULL, &context);
    if(result != TEEC_SUCCESS) {
        printf("teec initial failed\n");
        goto cleanup_1;
    }
   
    result = TEEC_OpenSession(&context, &session, &s_stTeecCipherUUID,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        printf("teec open session failed\n");
        goto cleanup_2;
    }

    mode += CIPHER_TEST_AES;

    cipher_cmd(session, mode, &result, 0, 0);

    printf("result: 0x%x\n", result);
        
    TEEC_CloseSession(&session);
cleanup_2:
    TEEC_FinalizeContext(&context);
cleanup_1:
    return 0;
}
