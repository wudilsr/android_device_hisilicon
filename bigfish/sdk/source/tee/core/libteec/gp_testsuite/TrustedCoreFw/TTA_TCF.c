#include "tee_client_api.h"
#include "tee_client_id.h"
#include <string.h>

/** Commands ids **/
#define CMD_TEE_Panic                                       0x00000104
#define CMD_TEE_CheckMemoryAccessRight                      0x00000103
#define CMD_TEE_GetCancellationFlag_RequestedCancel         0x00000105
#define CMD_TEE_MaskUnmaskCancellations                     0x00000106
#define CMD_ProcessInvokeTAOpenSession                      0x00000200
#define CMD_ProcessTAInvokeTA_simple                        0x00000201
#define CMD_ProcessTAInvokeTA_PayloadValue                  0x00000202
#define CMD_TEE_GetNextPropertyEnumerator_notStarted        0x00000203
#define CMD_ProcessTAInvokeTA_PayloadMemref                 0x00000204
#define CMD_ProcessTAInvokeTA_PayloadValue_In_Out           0x00000205

/** Types and Structures **/
enum propType {
   undefined = 0,
   string = 1,
   boolean = 2,
   integer = 3,
   binaryblock = 4,
   uuuid = 5,
   identity = 6
};

typedef enum{
    TEE_PROPSET_UNKNOW = 0,
    TEE_PROPSET_TEE_IMPLEMENTATION = 0xFFFFFFFD,
    TEE_PROPSET_CURRENT_CLIENT = 0xFFFFFFFE,
    TEE_PROPSET_CURRENT_TA = 0xFFFFFFFF,
}Pseudo_PropSetHandle;

//without enumarator
#define CMD_TEE_GetPropertyAsString_withoutEnum             0x00000010
#define CMD_TEE_GetPropertyAsBool_withoutEnum               0x00000015
#define CMD_TEE_GetPropertyAsInt_withoutEnum                0x00000020
#define CMD_TEE_GetPropertyAsBinaryBlock_withoutEnum        0x00000025
#define CMD_TEE_GetPropertyAsUUID_withoutEnum               0x00000030
#define CMD_TEE_GetPropertyAsIdentity_withoutEnum           0x00000035
//with enumarator
#define CMD_TEE_GetPropertyAsXXXX_fromEnum                  0x00000045
#define CMD_TEE_AllocatePropertyEnumerator                  0x00000060
#define CMD_TEE_StartPropertyEnumerator                     0x00000065
#define CMD_TEE_ResetPropertyEnumerator                     0x00000070
#define CMD_TEE_FreePropertyEnumerator                      0x00000075
#define CMD_TEE_GetPropertyName                             0x00000080

static TEEC_Result test_property(TEEC_Session *session)
{
    TEEC_Operation operation;
    TEEC_Result result;
#define TMP_BUFF_SIZE   64
    char tmp_in_buff[TMP_BUFF_SIZE], tmp_out_buff[TMP_BUFF_SIZE];
    uint32_t cmd[] = {CMD_TEE_GetPropertyAsString_withoutEnum,
                      CMD_TEE_GetPropertyAsString_withoutEnum,
                      CMD_TEE_GetPropertyAsBool_withoutEnum,
                      CMD_TEE_GetPropertyAsBool_withoutEnum,
                      CMD_TEE_GetPropertyAsInt_withoutEnum,
                      CMD_TEE_GetPropertyAsBinaryBlock_withoutEnum,
                      CMD_TEE_GetPropertyAsUUID_withoutEnum,
                      CMD_TEE_GetPropertyAsIdentity_withoutEnum};
    char *cmd_name[] = {"CMD_TEE_GetPropertyAsString_withoutEnum",
                        "CMD_TEE_GetPropertyAsString_withoutEnum",
                        "CMD_TEE_GetPropertyAsBool_withoutEnum",
                        "CMD_TEE_GetPropertyAsBool_withoutEnum",
                        "CMD_TEE_GetPropertyAsInt_withoutEnum",
                        "CMD_TEE_GetPropertyAsBinaryBlock_withoutEnum",
                        "CMD_TEE_GetPropertyAsUUID_withoutEnum",
                        "CMD_TEE_GetPropertyAsIdentity_withoutEnum"};
    char *prop_names[] = {"gp.test.description",
                         "smc.ta.teststring",
                         "smc.ta.testbooltrue",
                         "smc.ta.testboolfalse",
                         "smc.ta.testu32",
                         "smc.ta.testbinaryblock",
                         "smc.ta.testuuid",
                         "smc.ta.testidentity"};
    char *right_val[] = {"TTA_TCF v1.9",
                        "this is a test string",
                        "true",
                        "false",
                        "48059",
                        "VGhpcyBpcyBhIHRleHQgYmluYXJ5IGJsb2Nr",
                        "534D4152-542D-4353-4C54-2D54412D3031",
                        "F0000000:534D4152-542D-4353-4C54-2D54412D3031"};
    uint32_t i;
    uint32_t enumarator_handle;
    uint32_t prop_set;

    /* without enumarator */
    for(i=0; i<sizeof(cmd)/sizeof(cmd[0]); i++){
        memset(tmp_in_buff, 0, 64);
        memset(tmp_out_buff, 0, 64);

        memcpy(tmp_in_buff, prop_names[i], strlen(prop_names[i]));
        operation.started = 1;
        operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_OUTPUT,
            TEEC_NONE);
        operation.params[0].value.a = TEE_PROPSET_CURRENT_TA;
        operation.params[1].tmpref.buffer = tmp_in_buff;
        operation.params[1].tmpref.size = TMP_BUFF_SIZE;
        operation.params[2].tmpref.buffer = tmp_out_buff;
        operation.params[2].tmpref.size = TMP_BUFF_SIZE;

        result = TEEC_InvokeCommand(
                     session,
                     cmd[i],
                     &operation,
                     NULL);

        if(result != TEEC_SUCCESS){
            printf("%s failed, ret = 0x%x\n", cmd_name[i], result);
            goto end;
        }else{
            if(memcmp(right_val[i], operation.params[2].tmpref.buffer, operation.params[2].tmpref.size)){
                printf("%s get wrong val: right-%s, wrong-%s\n",
                       cmd_name[i], right_val[i], operation.params[2].tmpref.buffer);
                return TEEC_ERROR_GENERIC;
            }else{
                printf("%s success: property[%s] is %s\n", cmd_name[i], tmp_in_buff, tmp_out_buff);
            }
        }
    }

    /* with enumarator */
    //CMD_TEE_AllocatePropertyEnumerator
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_OUTPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_AllocatePropertyEnumerator,
                 &operation,
                 NULL);

    if(result == TEEC_SUCCESS){
        enumarator_handle = operation.params[0].value.a;
        printf("CMD_TEE_AllocatePropertyEnumerator success: enumarator_handle = %d\n", enumarator_handle);
    }else{
        printf("CMD_TEE_AllocatePropertyEnumerator failed, ret = 0x%x\n", result);
        goto end;
    }

    //CMD_TEE_StartPropertyEnumerator
    prop_set = TEE_PROPSET_TEE_IMPLEMENTATION;
    for(i = 0; i < 3; i++, prop_set++){
        operation.started = 1;
        operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE);
        operation.params[0].value.a = enumarator_handle;
        operation.params[1].value.a = prop_set;

        result = TEEC_InvokeCommand(
                     session,
                     CMD_TEE_StartPropertyEnumerator,
                     &operation,
                     NULL);

        if(result == TEEC_SUCCESS){
            printf("CMD_TEE_StartPropertyEnumerator success: prop_set = 0x%x\n", prop_set);
        }else{
            printf("CMD_TEE_AllocatePropertyEnumerator failed, ret = 0x%x\n", result);
            goto end;
        }

        //CMD_TEE_GetPropertyAsXXXX_fromEnum
        operation.started = 1;
        operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE);
        operation.params[0].value.a = enumarator_handle;
        operation.params[1].value.a = prop_set;

        result = TEEC_InvokeCommand(
                     session,
                     CMD_TEE_GetPropertyAsXXXX_fromEnum,
                     &operation,
                     NULL);

        if(result == TEEC_SUCCESS){
            printf("CMD_TEE_GetPropertyAsXXXX_fromEnum success: prop_set = 0x%x\n", prop_set);
        }else{
            printf("CMD_TEE_GetPropertyAsXXXX_fromEnum failed, ret = 0x%x\n", result);
            goto end;
        }
    }

    //CMD_TEE_StartPropertyEnumerator
    prop_set = TEE_PROPSET_TEE_IMPLEMENTATION;
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = enumarator_handle;
    operation.params[1].value.a = prop_set;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_StartPropertyEnumerator,
                 &operation,
                 NULL);

    if(result == TEEC_SUCCESS){
        printf("CMD_TEE_StartPropertyEnumerator success: prop_set = 0x%x\n", prop_set);
    }else{
        printf("CMD_TEE_AllocatePropertyEnumerator failed, ret = 0x%x\n", result);
        goto end;
    }

    //CMD_TEE_GetPropertyName
    memset(tmp_out_buff, 0, TMP_BUFF_SIZE);
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_TEMP_OUTPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = enumarator_handle;
    operation.params[1].tmpref.buffer = tmp_out_buff;
    operation.params[1].tmpref.size = TMP_BUFF_SIZE;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_GetPropertyName,
                 &operation,
                 NULL);

    if(result == TEEC_SUCCESS){
        printf("CMD_TEE_GetPropertyName success: prop name = %s\n", operation.params[1].tmpref.buffer);
    }else{
        printf("CMD_TEE_GetPropertyName failed, ret = 0x%x\n", result);
        goto end;
    }

    //CMD_TEE_ResetPropertyEnumerator
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = enumarator_handle;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_ResetPropertyEnumerator,
                 &operation,
                 NULL);

    if(result == TEEC_SUCCESS){
        printf("CMD_TEE_ResetPropertyEnumerator success\n");
    }else{
        printf("CMD_TEE_ResetPropertyEnumerator failed, ret = 0x%x\n", result);
        goto end;
    }

    //CMD_TEE_FreePropertyEnumerator
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = enumarator_handle;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_FreePropertyEnumerator,
                 &operation,
                 NULL);

    if(result == TEEC_SUCCESS){
        printf("CMD_TEE_FreePropertyEnumerator success\n");
    }else{
        printf("CMD_TEE_FreePropertyEnumerator failed, ret = 0x%x\n", result);
        goto end;
    }

end:

    return result;
}

#define CMD_TEE_Malloc                                      0x00000100
#define CMD_TEE_Free                                        0x00000107
#define CMD_TEE_Realloc                                     0x00000110
#define CMD_TEE_MemMove                                     0x00000120
#define CMD_TEE_MemCompare                                  0x00000130
#define CMD_TEE_MemFill                                     0x00000140

static TEEC_Result test_mem_management(TEEC_Session *session)
{
    TEEC_Operation operation;
    TEEC_Result result;

    //CMD_TEE_Malloc
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = 1000;
    operation.params[1].value.a = 0;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_Malloc,
                 &operation,
                 NULL);

    if(result != TEEC_SUCCESS){
        printf("CMD_TEE_Malloc failed, ret = %x\n", result);
        goto end;
    }
    printf("CMD_TEE_Malloc success\n");

    //CMD_TEE_Realloc
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = 1000;
    operation.params[1].value.a = 500;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_Realloc,
                 &operation,
                 NULL);

    if(result != TEEC_SUCCESS){
        printf("CMD_TEE_Realloc 1 failed, ret = 0x%x\n", result);
        goto end;
    }
    printf("CMD_TEE_Realloc 1 success\n");

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = 500;
    operation.params[1].value.a = 1000;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_Realloc,
                 &operation,
                 NULL);

    if(result != TEEC_SUCCESS){
        printf("CMD_TEE_Realloc 2 failed, ret = 0x%x\n", result);
        goto end;
    }
    printf("CMD_TEE_Realloc 2 success\n");

    //CMD_TEE_Free
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = 1000;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_Free,
                 &operation,
                 NULL);

    if(result != TEEC_SUCCESS){
        printf("CMD_TEE_Free failed, ret = 0x%x\n", result);
        goto end;
    }
    printf("CMD_TEE_Free success\n");

    //CMD_TEE_MemMove
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = 2000;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_MemMove,
                 &operation,
                 NULL);

    if(result != TEEC_SUCCESS){
        printf("CMD_TEE_MemMove failed, ret = 0x%x\n", result);
        goto end;
    }
    printf("CMD_TEE_MemMove success\n");

    //CMD_TEE_MemCompare
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_VALUE_OUTPUT,
        TEEC_NONE);
    operation.params[0].value.a = 200;
    operation.params[1].value.a = 1;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_MemCompare,
                 &operation,
                 NULL);

    if(result != TEEC_SUCCESS){
        printf("CMD_TEE_MemCompare failed, ret = 0x%x\n", result);
        goto end;
    }
    printf("CMD_TEE_MemCompare success\n");

    //CMD_TEE_MemFill
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = 500;
    operation.params[1].value.a = 23;

    result = TEEC_InvokeCommand(
                 session,
                 CMD_TEE_MemFill,
                 &operation,
                 NULL);

    if(result != TEEC_SUCCESS){
        printf("CMD_TEE_MemFill failed, ret = 0x%x\n", result);
        goto end;
    }
    printf("CMD_TEE_MemFill success\n");

end:
    return result;
}

int main(void)
{
    TEEC_Context context;
    TEEC_Session session;
    TEEC_UUID uuid = { 0x534D4152, 0x542D, 0x4353, { 0x4C, 0x54, 0x2D, 0x54, 0x41, 0x2D, 0x30, 0x31 } };
    TEEC_Result result;

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
#if 1
    if((result = test_property(&session)) != TEEC_SUCCESS){
        goto err_1;
    }
    printf("property test success\n");
#endif
    if((result = test_mem_management(&session)) != TEEC_SUCCESS){
        goto err_1;
    }
    printf("mem management test success\n");

    TEEC_CloseSession(&session);
    TEEC_FinalizeContext(&context);

    if(result == TEEC_SUCCESS)
        printf("TTA_TCF test success\n");

    return 0;

err_1:
    TEEC_CloseSession(&session);
err_2:
    TEEC_FinalizeContext(&context);

    return -1;
}
