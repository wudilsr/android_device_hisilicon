#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tee_client_api.h"
#include "tee_client_random_api.h"

int main()
{
    TEEC_Result ret;
    if ((ret = TEEC_InitCryptoService()) != TEEC_SUCCESS) {
        TEEC_Error("InitCryptoService error, errno=0x%x\n", ret);
        while(1);
    }

    uint8_t *rand_buffer;
    uint32_t rand_size;
    uint32_t i;

/////////////////////////////////////////////////////////////////////
    for (rand_size = 0; rand_size <= 33; rand_size++) {
        rand_buffer = (uint8_t*)malloc(rand_size);
        memset(rand_buffer, 0x00, rand_size);

        if ((ret = TEEC_Random(rand_buffer, rand_size)) == TEEC_SUCCESS) {
            TEEC_Debug("Generate Random success\n");
            printf("rand_buffer [%d]: ", rand_size);
            for (i = 0;i < rand_size; i++)
                printf("%x ", *(rand_buffer + i));
            printf("\n");
        } else {
            TEEC_Error("Generate Random failed\n");
        }

        free(rand_buffer);
    }
/////////////////////////////////////////////////////////////////////

    TEEC_UninitCryptoService();

    printf("ALL test case are PASS\n");
    return 0;
}
