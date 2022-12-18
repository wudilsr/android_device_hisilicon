#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "tee_client_api.h"
#include "CommomData_for_TestSuite.h"

int main(void)
{
    TEEC_FinalizeContext(NULL);
    printf("FinalizeContext_null success\n");
    return 0;
}
