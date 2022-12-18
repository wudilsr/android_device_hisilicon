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
//#define PANIC
//#define TESTALL

#define TEST_Case1                                          0x00000011

//objectType is TEE_TYPE_AES
#define objectType  0xA0000010

#define maxObjectSize   0x00000800
//attributeID is TEE_ATTR_SECRET_VALUE
#define attributeID 0xC0000000

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

//testcase No.1
TEEC_Result CCmdAllocateTransientChain(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);
    operation.params[0].value.a = objectType;
    operation.params[0].value.b = maxObjectSize;

    result = TEEC_InvokeCommand(&session, CMD_AllocateTransientChain, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    return result;
}

//testcase No.2 should panic, but now DATA ABORT
TEEC_Result CCmdGetObjectInfoPanic(void)
{
    TEEC_Result result;

    result = TEEC_InvokeCommand(&session, CMD_GetObjectInfoPanic, NULL, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    return result;
}

//testcase No.3 should panic, but now DATA ABORT
TEEC_Result CCmdRestrictObjectUsagePanic(void)
{
    TEEC_Result result;

    result = TEEC_InvokeCommand(&session, CMD_RestrictObjectUsagePanic, NULL, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    return result;
}

//testcase No.4 should panic, but now DATA ABORT
TEEC_Result CCmdCloseObjectPanic(void)
{
    TEEC_Result result;
    result = TEEC_InvokeCommand(&session, CMD_CloseObjectPanic, NULL, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    return result;
}

//testcase No.5 test for TEE_HANDLE_NULL
TEEC_Result CCmdCloseFreeAndResetObjectSuccessHandleNull(void)
{
    TEEC_Result result;
    result = TEEC_InvokeCommand(&session, CMD_CloseFreeAndResetObjectSuccessHandleNull, NULL, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    return result;
}

//testcase No.6 should panic, but now DATA ABORT
TEEC_Result CCmdFreeTransientObjectPanic(void)
{
    TEEC_Result result;
    result = TEEC_InvokeCommand(&session, CMD_FreeTransientObjectPanic, NULL, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    return result;
}

//testcase No.7 should panic, but now DATA ABORT
TEEC_Result CCmdResetTransientObjectPanic(void)
{
    TEEC_Result result;
    result = TEEC_InvokeCommand(&session, CMD_ResetTransientObjectPanic, NULL, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    return result;
}

//testcase No.8
TEEC_Result CCmdStoreAndReadBufferAttribute(void)
{
    TEEC_Operation operation;
    TEEC_Result result;
    char attrbuf[64]="test for attrbuf";

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_NONE);
    operation.params[0].value.a = objectType;
    operation.params[0].value.b = maxObjectSize;
    operation.params[1].value.a = attributeID;
    operation.params[2].tmpref.buffer = attrbuf;
    operation.params[2].tmpref.size = strlen(attrbuf);

    result = TEEC_InvokeCommand(&session, CMD_StoreAndReadBufferAttribute, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    return result;
}

//testcase No.9 should panic, but now pass, because not use uninitial object handle
TEEC_Result CCmdInitRefAttributePanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;
    char attrbuf[64]="test for attrbuf";

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_NONE);
    //operation.params[0].value.a = objectType;
    //operation.params[0].value.b = maxObjectSize;
    operation.params[1].value.a = attributeID;
    operation.params[2].tmpref.buffer = attrbuf;
    operation.params[2].tmpref.size = 64;

    result = TEEC_InvokeCommand(&session, CMD_InitRefAttributePanic, &operation, &origin);
    if (result != 0xFFFF0000) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        return 1;
    }
    return 0;
}

//testcase No.10:in populate, object->attribute.content.ref.buffer is null, so return TEE_ERROR_BAD_PARAMETERS
TEEC_Result CCmdInitObjectAndAttributes_1(void)
{
    TEEC_Operation operation;
    TEEC_Result result;
    char attrbuf[64]="test";
    uint32_t num=1;

    uint32_t attrID1 = attributeID;
    char *attrbuff_addr1;
    uint32_t attrbuff_len1 = strlen(attrbuf);
    char *attr_3buf;
    attr_3buf = (char *)malloc(12*num);

    attrbuff_addr1 = attrbuf;
    retrieveBufferFromUint32(attrID1, attr_3buf);
    retrieveBufferFromUint32(0, attr_3buf+4);
    retrieveBufferFromUint32(attrbuff_len1, attr_3buf+8);

    //CASE_POPULATE_BAD_PARAM
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_VALUE_INPUT);

    operation.params[0].value.a = objectType;
    operation.params[0].value.b = maxObjectSize;
    operation.params[1].tmpref.buffer = attr_3buf;
    operation.params[1].tmpref.size = 12;
    operation.params[2].tmpref.buffer = attrbuf;
    operation.params[2].tmpref.size = strlen(attrbuf);
    operation.params[3].value.a = CASE_POPULATE_BAD_PARAM;
    operation.params[3].value.b = 0;

    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result == TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        free(attr_3buf);
        return 1;
    }
    free(attr_3buf);
    return result;
}

//testcase No.10:in TEE_InitRefAttribute, attributeID 29bit is 1, shound panic, now return 0x0000f006
TEEC_Result CCmdInitObjectAndAttributes_10(void)
{
    TEEC_Operation operation;
    TEEC_Result result;
    char attrbuf[64]="test";
    uint32_t num=1;

    uint32_t attrID1 = attributeID;
    char *attrbuff_addr1;
    uint32_t attrbuff_len1 = strlen(attrbuf);
    char *attr_3buf;
    attr_3buf = (char *)malloc(12*num);

    attrbuff_addr1 = attrbuf;
    retrieveBufferFromUint32(attrID1, attr_3buf);
    retrieveBufferFromUint32(0, attr_3buf+4);
    retrieveBufferFromUint32(attrbuff_len1, attr_3buf+8);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_VALUE_INPUT);

    operation.params[0].value.a = objectType;
    operation.params[0].value.b = maxObjectSize;
    operation.params[1].tmpref.buffer = attr_3buf;
    operation.params[1].tmpref.size = 12;
    operation.params[2].tmpref.buffer = attrbuf;
    operation.params[2].tmpref.size = strlen(attrbuf);
    operation.params[3].value.a = CASE_INIT_ATTRIBUTE_PANIC;
    operation.params[3].value.b = 0;

    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0x0000f006) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        free(attr_3buf);
        return 1;
    }
    free(attr_3buf);
    return result;
}

//testcase No.10
TEEC_Result CCmdInitObjectAndAttributes_20_26(void)
{
    TEEC_Operation operation;
    TEEC_Result result;
    char attrbuf[64]="testTESTTEST";
    uint32_t num=1;

    uint32_t attrID1 = attributeID;
    char *attrbuff_addr1;
    uint32_t attrbuff_len1 = strlen(attrbuf);
    char *attr_3buf;
    attr_3buf = (char *)malloc(12*num);

    attrbuff_addr1 = attrbuf;
    retrieveBufferFromUint32(attrID1, attr_3buf);
    retrieveBufferFromUint32(0, attr_3buf+4);
    retrieveBufferFromUint32(attrbuff_len1, attr_3buf+8);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_VALUE_INPUT);

    operation.params[0].value.a = objectType;
    operation.params[0].value.b = maxObjectSize;
    operation.params[1].tmpref.buffer = attr_3buf;
    operation.params[1].tmpref.size = 12;
    operation.params[2].tmpref.buffer = attrbuf;
    operation.params[2].tmpref.size = strlen(attrbuf);
    operation.params[3].value.b = 0;

    //attributeID BIT28 set 0, so no permission to TEE_GetObjectBufferAttribute, return TEE_ERROR_ACCESS_DENIED,should panic
    operation.params[3].value.a = CASE_GET_OBJECT_BUFFER_ATTRIB_BIT28;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    //attributeID BIT29 set 1, so attrbute is value, not to excute TEE_GetObjectBufferAttribute, return TEE_ERROR_BAD_PARAMETERS, should panic
    operation.params[3].value.a = CASE_GET_OBJECT_BUFFER_ATTRIB_BIT29;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0006) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }

    //object is uninitial so return TEE_ERROR_ITEM_NOT_FOUND, should panic
    operation.params[3].value.a = CASE_GET_OBJECT_BUFFER_ATTRIB_NOT_INIT;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0008) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }

    //this attrbuteID is not exist, return TEE_ERROR_ITEM_NOT_FOUND
    operation.params[3].value.a = CASE_GET_OBJECT_BUFFER_ATTRIB_ITEM_NOT_FOUND;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0008) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }

    //this output buffer is smaller to attr_buff, so return TEE_ERROR_SHORT_BUFFER
    operation.params[3].value.a = CASE_GET_OBJECT_BUFFER_ATTRIB_TOO_SHORT_BUFFER;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0010) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }

    //this output buffer is NULL, so return TEE_ERROR_SHORT_BUFFER
    operation.params[3].value.a = CASE_GET_OBJECT_BUFFER_ATTRIB_BUFFER_NULL;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0010) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }

    //object is 0xFFFFDEAD,so should panic, now DATA ABORT
    /*operation.params[3].value.a = CASE_GET_OBJECT_BUFFER_ATTRIB_INVALID_OBJECT;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0006) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }*/

    free(attr_3buf);
    return 0;
    error:
        return result;

}

//testcase No.10
TEEC_Result CCmdInitObjectAndAttributes_30_52(void)
{
    TEEC_Operation operation;
    TEEC_Result result;
    char attrbuf[64]="test";
    uint32_t num=1;

    uint32_t attrID1 = attributeID;
    char *attrbuff_addr1;
    uint32_t attrbuff_len1 = strlen(attrbuf);
    char *attr_3buf;
    attr_3buf = (char *)malloc(12*num);

    attrbuff_addr1 = attrbuf;
    retrieveBufferFromUint32(attrID1, attr_3buf);
    retrieveBufferFromUint32(0, attr_3buf+4);
    retrieveBufferFromUint32(attrbuff_len1, attr_3buf+8);

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_VALUE_INPUT);

    operation.params[0].value.a = objectType;
    operation.params[0].value.b = maxObjectSize;
    operation.params[1].tmpref.buffer = attr_3buf;
    operation.params[1].tmpref.size = 12;
    operation.params[2].tmpref.buffer = attrbuf;
    operation.params[2].tmpref.size = strlen(attrbuf);
    operation.params[3].value.b = 0;

    //in copy, dest object has been populate, so fail to copy, should panic, now return TEEC_SUCCESS
    operation.params[3].value.a = CASE_COPY_OBJECT_ATTRIBUTE_DEST_NOT_UNINIT;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }
    printf("CASE_COPY_OBJECT_ATTRIBUTE_DEST_NOT_UNINIT success!\n");

    //TODO:Generatekey
    /*
    operation.params[3].value.a = CASE_COPY_OBJECT_ATTRIBUTE_SRC_DEST_NOT_COMPAT;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0008) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }
    printf("CASE_COPY_OBJECT_ATTRIBUTE_SRC_DEST_NOT_COMPAT success!\n");
    */

    //copy the unitialized into the initialized, should panic, now return TEEC_SUCCESS
    operation.params[3].value.a = CASE_COPY_OBJECT_ATTRIBUTE_SRC_NOT_INIT;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }
    printf("CASE_COPY_OBJECT_ATTRIBUTE_SRC_NOT_INIT success!\n");

    //in TEE_CopyObjectAttributes, src object is Persistent Object, return TEEC_SUCCESS
    operation.params[3].value.a = CASE_COPY_OBJECT_ATTRIBUTE_SRC_IS_PERSISTENT;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }

    //not implementation, test dafult branch
    operation.params[3].value.a = CASE_ATTRIBUTE_MISSING;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }

    #if 0
    //object is 0xFFFFDEAD, when populate  should panic, now DATA ABORT
    operation.params[3].value.a = CASE_POPULATE_OBJECT_INVALID_OBJECT;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }
    #endif

    //tries to repopulate the same object that has been populated, should panic, now return TEE_ERROR_BAD_PARAMETERS
    operation.params[3].value.a = CASE_POPULATE_OBJECT_NOT_UNINIT;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0006) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }

    // tries to populate a persistent object, should panic, now return TEE_ERROR_BAD_PARAMETERS
    operation.params[3].value.a = CASE_POPULATE_OBJECT_NOT_TRANSIENT;
    result = TEEC_InvokeCommand(&session, CMD_InitObjectAndAttributes, &operation, &origin);
    if (result != 0xFFFF0006) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
         goto error;
    }

    free(attr_3buf);
    return 0;
    error:
        return result;
}

//testcase No.11
TEEC_Result CCmdGenerateKey()
{
    return TEEC_SUCCESS;
}

//testcase No.12
TEEC_Result CCmdCreatePersistentObjectPanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    printf("test for CASE_CREATE_PERSISTENT_OBJECT_OBJECT_ID_TOO_LONG\n");
    //test for right case, OBJECTID is not long, the next case is too long
    operation.params[0].value.a = CASE_CREATE_PERSISTENT_OBJECT_OBJECT_ID_TOO_LONG;
    result = TEEC_InvokeCommand(&session, CMD_CreatePersistentObjectPanic, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    printf("test for CASE_CREATE_PERSISTENT_OBJECT_NOT_VALID_HANDLE\n");
    //test for OBJECT_ID_TOO_LONG
    operation.params[0].value.a = CASE_CREATE_PERSISTENT_OBJECT_NOT_VALID_HANDLE;
    result = TEEC_InvokeCommand(&session, CMD_CreatePersistentObjectPanic, &operation, &origin);
    if (result != 0xFFFF0006) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.13 test for TEE_STORAGE_PRIVATE + 1,so return TEE_ERROR_ITEM_NOT_FOUND
TEEC_Result CCmdCreatePersistentObject_ItemNotFound(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_CreatePersistentObject_ItemNotFound\n");
    //test for right case

    result = TEEC_InvokeCommand(&session, CMD_CreatePersistentObject_ItemNotFound, &operation, &origin);
    if (result != 0xFFFF0008) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.14 this testcase has some doubts, should return TEE_ERROR_ITEM_NOT_FOUND
TEEC_Result CCmdCreatePersistentObject_AccessConflict(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_CreatePersistentObject_AccessConflict\n");
    //test for right case

    result = TEEC_InvokeCommand(&session, CMD_CreatePersistentObject_AccessConflict, &operation, &origin);
    if (result != 0XFFFF0008) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.15 create persistent object with all kinds of permission
TEEC_Result CCmdCreatePersistentObject_Success(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    printf("test for CCmdCreatePersistentObject_Success\n");
    //
    operation.params[0].value.a = CASE_CREATE_PERSISTENT_OBJECT_READ;
    result = TEEC_InvokeCommand(&session, CMD_CreatePersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    //
    operation.params[0].value.a = CASE_CREATE_PERSISTENT_OBJECT_WRITE;
    result = TEEC_InvokeCommand(&session, CMD_CreatePersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

     //
    operation.params[0].value.a = CASE_CREATE_PERSISTENT_OBJECT_WRITE_META;
    result = TEEC_InvokeCommand(&session, CMD_CreatePersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

     //
    operation.params[0].value.a = CASE_CREATE_PERSISTENT_OBJECT_SHARE_READ;
    result = TEEC_InvokeCommand(&session, CMD_CreatePersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;

    }

    //
    operation.params[0].value.a = CASE_CREATE_PERSISTENT_OBJECT_SHARE_WRITE;
    result = TEEC_InvokeCommand(&session, CMD_CreatePersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
        error:
        return result;
}

//testcase No.16 should TA panic, but now return TEE_ERROR_BAD_PARAMETERS
TEEC_Result CCmdOpenPersistentObjectPanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_OpenPersistentObjectPanic\n");
    //test for right case

    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObjectPanic, &operation, &origin);
    if (result != 0xFFFF0006) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.17
TEEC_Result CCmdOpenPersistentObject_ItemNotFound(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CCmdOpenPersistentObject_ItemNotFound\n");
    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    //open object that is not exist
    operation.params[0].value.a = CASE_OPEN_PERSISTENT_OBJECT_UNKNOWN_OBJECTID;
    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObject_ItemNotFound, &operation, &origin);
    if (result != 0xFFFF0008) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    //open object whose storageID is TEE_STORAGE_PRIVATE + 1
    operation.params[0].value.a = CASE_OPEN_PERSISTENT_OBJECT_UNKNOWN_STORAGEID;
    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObject_ItemNotFound, &operation, &origin);
    if (result != 0xFFFF0008) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.18 open persistent object with all kinds of permission
TEEC_Result CCmdOpenPersistentObject_Success(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_OpenPersistentObject_Success\n");
    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    //test for right case
    printf("test for CASE_OPEN_PERSISTENT_OBJECT_READ\n");
    operation.params[0].value.a = CASE_OPEN_PERSISTENT_OBJECT_READ;
    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    //
    printf("test for CASE_OPEN_PERSISTENT_OBJECT_WRITE\n");
    operation.params[0].value.a = CASE_OPEN_PERSISTENT_OBJECT_WRITE;
    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    //
    printf("test for CASE_OPEN_PERSISTENT_OBJECT_WRITE_META\n");
    operation.params[0].value.a = CASE_OPEN_PERSISTENT_OBJECT_WRITE_META;
    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

     //
    printf("test for CASE_OPEN_PERSISTENT_OBJECT_SHARE_READ\n");
    operation.params[0].value.a = CASE_OPEN_PERSISTENT_OBJECT_SHARE_READ;
    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

     //
    printf("test for CASE_OPEN_PERSISTENT_OBJECT_SHARE_WRITE\n");
    operation.params[0].value.a = CASE_OPEN_PERSISTENT_OBJECT_SHARE_WRITE;
    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;

    }
    return 0;
    error:
        return result;
}


//testcase No.19 should TA panic, but now return TEE_ERROR_BAD_PARAMETERS
TEEC_Result CCmdRenamePersistentObjectPanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);
    printf("test for CMD_RenamePersistentObjectPanic\n");
    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    //test for no WRITE_META, rename failed return TEE_ERROR_ACCESS_DENIED,should panic
    printf("test for CASE_RENAME_PERSISTENT_OBJECT_WRITE_META\n");
    operation.params[0].value.a = CASE_RENAME_PERSISTENT_OBJECT_WRITE_META;
    result = TEEC_InvokeCommand(&session, CMD_RenamePersistentObjectPanic, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    //test for valid object handle , should TA panic,now DATA ABORT
    /*
    printf("test for CASE_RENAME_PERSISTENT_OBJECT_HANDLE_NOT_VALID\n");
    operation.params[0].value.a = CASE_RENAME_PERSISTENT_OBJECT_HANDLE_NOT_VALID;
    result = TEEC_InvokeCommand(&session, CMD_RenamePersistentObjectPanic, &operation, &origin);
    if (result != 0xFFFF0006) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }
    */

    //test for rename ,the new name is too long, should panic now return TEE_ERROR_BAD_PARAMETERS
    printf("test for CASE_RENAME_PERSISTENT_OBJECT_ID_TOO_LONG\n");
    operation.params[0].value.a = CASE_RENAME_PERSISTENT_OBJECT_ID_TOO_LONG;
    result = TEEC_InvokeCommand(&session, CMD_RenamePersistentObjectPanic, &operation, &origin);
    if (result != 0xFFFF0006) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}


//testcase No.20 should TA panic, but now return TEE_ERROR_BAD_PARAMETERS
TEEC_Result CCmdRenamePersistentObject_AccessConflict(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    //CASE_POPULATE_BAD_PARAM
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_RenamePersistentObject_AccessConflict\n");
    //test for right case

    result = TEEC_InvokeCommand(&session, CMD_RenamePersistentObject_AccessConflict, &operation, &origin);
    if (result != 0xFFFF0003) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}


//testcase No.21 right testcase for rename
TEEC_Result CCmdRenamePersistentObject_Success(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    //CASE_POPULATE_BAD_PARAM
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_RenamePersistentObject_Success\n");
    //test for right case

    result = TEEC_InvokeCommand(&session, CMD_RenamePersistentObject_Success, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.22 Enumerator
TEEC_Result CCmdEnumeratorOnPersistentObjects(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    //CASE_POPULATE_BAD_PARAM
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_OUTPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    operation.params[0].value.a = TEEC_VALUE_UNDEF;

    //test for
    printf("test for CMD_EnumeratorOnPersistentObjects\n");

    result = TEEC_InvokeCommand(&session, CMD_EnumeratorOnPersistentObjects, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }
    printf("operation.params[0].value.a  is %d\n", operation.params[0].value.a );
    printf("operation.params[0].value.b  is %d\n", operation.params[0].value.b );

    return 0;
    error:
        return result;
}
//testcase No.23
TEEC_Result CCmdCloseAndDeletePersistentObjectPanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);
    printf("test for CMD_CloseAndDeletePersistentObjectPanic\n");
    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    //test for closeanddelete invalid object (0xFFFFDEAD) should panic, now DATA ABORT
    /*
    printf("test for CASE_CLOSE_N_DELETE_PERSISTENT_OBJ_HANDLE_NOT_VALID\n");
    operation.params[0].value.a = CASE_CLOSE_N_DELETE_PERSISTENT_OBJ_HANDLE_NOT_VALID;
    result = TEEC_InvokeCommand(&session, CMD_CloseAndDeletePersistentObjectPanic, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }
*/
    //test for closeanddelete without WRITE_META , should TA panic, now return TEE_ERROR_GENERIC
    printf("test for CASE_CLOSE_N_DELETE_PERSISTENT_OBJ_WRITE_META\n");
    operation.params[0].value.a = CASE_CLOSE_N_DELETE_PERSISTENT_OBJ_WRITE_META;
    result = TEEC_InvokeCommand(&session, CMD_CloseAndDeletePersistentObjectPanic, &operation, &origin);
    if (result != 0xFFFF0000) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}



//testcase No.24 TEE_FreePersistentObjectEnumerator TEE_CloseAndDeletePersistentObject deal with TEE_HANDLE_NULL
TEEC_Result CCmdFreeCloseAndDeletePersistentObjectSuccessHandleNull(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_FreeCloseAndDeletePersistentObjectSuccessHandleNull\n");
    result = TEEC_InvokeCommand(&session, CMD_FreeCloseAndDeletePersistentObjectSuccessHandleNull, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.25
TEEC_Result CCmdFreePersistentObjectEnumeratorPanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_FreePersistentObjectEnumeratorPanic\n");
    result = TEEC_InvokeCommand(&session, CMD_FreePersistentObjectEnumeratorPanic, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.26
TEEC_Result CCmdResetPersistentObjectEnumeratorPanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_ResetPersistentObjectEnumeratorPanic\n");
    result = TEEC_InvokeCommand(&session, CMD_ResetPersistentObjectEnumeratorPanic, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.27
TEEC_Result CCmdStartPersistentObjectEnumeratorPanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_StartPersistentObjectEnumeratorPanic\n");
    result = TEEC_InvokeCommand(&session, CMD_StartPersistentObjectEnumeratorPanic, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.28
TEEC_Result CCmdGetNextPersistentObjectPanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_GetNextPersistentObjectPanic\n");
    result = TEEC_InvokeCommand(&session, CMD_GetNextPersistentObjectPanic, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.29 test for Enumerator
TEEC_Result CCmdStartNGetPersistentObjectEnumerator_itemNotFound(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_OUTPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    operation.params[0].value.a = TEEC_VALUE_UNDEF;

    printf("test for CMD_StartNGetPersistentObjectEnumerator_itemNotFound\n");
    result = TEEC_InvokeCommand(&session, CMD_StartNGetPersistentObjectEnumerator_itemNotFound, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.30 InitValueAttribute
TEEC_Result CCmdInitValueAttribute(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);
    printf("test for CMD_InitValueAttribute\n");
    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    operation.params[0].value.a = 0xF0001332;
    result = TEEC_InvokeCommand(&session, CMD_InitValueAttribute, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.31 GetBufferAttribute from object uninitialized
TEEC_Result CCmdGetBufferAttribute_object_uninitialized(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.a = objectType;
    operation.params[0].value.b = maxObjectSize;

    printf("test for CMD_GetBufferAttribute_object_uninitialized\n");
    result = TEEC_InvokeCommand(&session, CMD_GetBufferAttribute_object_uninitialized, &operation, &origin);
    if (result != 0xFFFF0008) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.32 open object after create, permission conflict
TEEC_Result CCmdOpenPersistentObject_conflict(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_OpenPersistentObject_conflict\n");
    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObject_conflict, &operation, &origin);
    if (result != 0xFFFF0003) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.33 TODO: generatekey
TEEC_Result CCmdGetRSAAttributes(void)
{
    TEEC_Operation operation;
    TEEC_Result result;
        char attrbuf[64]="test";
    uint32_t num=1;
    uint32_t nAttribType;


    char *attrbuff_addr1;
    uint32_t attrbuff_len1 = strlen(attrbuf);
    char *attr_0buf;
    char *attr_1buf;
    char *attr_2buf;
    char *attr_3buf;
    attr_0buf = (char *)malloc(64);
    attr_1buf = (char *)malloc(64);
    attr_2buf = (char *)malloc(64);
    attr_3buf = (char *)malloc(64);

    uint32_t attrID1 = attributeID;
    nAttribType =0;
    retrieveBufferFromUint32(nAttribType, attr_0buf);
    retrieveBufferFromUint32(attrID1, attr_0buf+4);



    //CASE_POPULATE_BAD_PARAM
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_MEMREF_TEMP_INOUT,
            TEEC_MEMREF_TEMP_OUTPUT,
            TEEC_MEMREF_TEMP_OUTPUT,
            TEEC_MEMREF_TEMP_OUTPUT);

    operation.params[0].tmpref.buffer = attr_0buf;
    operation.params[0].tmpref.size = 64;
    operation.params[1].tmpref.buffer = attr_1buf;
    operation.params[1].tmpref.size = 64;
    operation.params[2].tmpref.buffer = attr_2buf;
    operation.params[2].tmpref.size = 64;
    operation.params[3].tmpref.buffer = attr_3buf;
    operation.params[3].tmpref.size = 64;

    printf("test for CMD_GetRSAAttributes\n");
    //test for right case

    result = TEEC_InvokeCommand(&session, CMD_GetRSAAttributes, &operation, &origin);
    if (result != 0xFFFF0003) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }
     free(attr_0buf);
     free(attr_1buf);
     free(attr_2buf);
     free(attr_3buf);
    return 0;
    error:
         free(attr_0buf);
         free(attr_1buf);
         free(attr_2buf);
         free(attr_3buf);
        return result;
}

//testcase No.34 invalic object
TEEC_Result CCmdGetObjectValueAttributePanic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    //CASE_POPULATE_BAD_PARAM
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_GetObjectValueAttributePanic\n");
    //test for right case

    result = TEEC_InvokeCommand(&session, CMD_GetObjectValueAttributePanic, &operation, &origin);
    if (result != 0xFFFF0003) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.35 TODO: generatekey
TEEC_Result CCmdGetDHAttributes(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    //CASE_POPULATE_BAD_PARAM
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    printf("test for CMD_OpenPersistentObject_conflict\n");
    //test for right case

    result = TEEC_InvokeCommand(&session, CMD_OpenPersistentObject_conflict, &operation, &origin);
    if (result != 0xFFFF0003) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.36 ReadObjectData_panic
TEEC_Result CCmdReadObjectData_panic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    printf("test for CMD_ReadObjectData_panic\n");

    //test for badhadle 0xFFFFDEAD result data abort
    /*
    operation.params[0].value.a = CASE_DATA_BAD_HANDLE;
    result = TEEC_InvokeCommand(&session, CMD_ReadObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0003) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }*/

    //test for not have read permission
    operation.params[0].value.a = CASE_DATA_ACCESS_RIGHT_NOT_SET;
    result = TEEC_InvokeCommand(&session, CMD_ReadObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    //test for readdata from transient object should panic, but now return access deny
    operation.params[0].value.a = CASE_DATA_OBJECT_NOT_PERSISTENT;
    result = TEEC_InvokeCommand(&session, CMD_ReadObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.37 WriteObjectData_panic
TEEC_Result CCmdWriteObjectData_panic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    printf("test for CMD_WriteObjectData_panic\n");

    //test for badhadle 0xFFFFDEAD result data abort
    /*
    operation.params[0].value.a = CASE_DATA_BAD_HANDLE;
    result = TEEC_InvokeCommand(&session, CMD_WriteObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0003) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }*/

    //test for right case
    operation.params[0].value.a = CASE_DATA_ACCESS_RIGHT_NOT_SET;
    result = TEEC_InvokeCommand(&session, CMD_WriteObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    //test for readdata from transient object should panic, but now return access deny
    operation.params[0].value.a = CASE_DATA_OBJECT_NOT_PERSISTENT;
    result = TEEC_InvokeCommand(&session, CMD_WriteObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.38 TruncateObjectData_panic
TEEC_Result CCmdTruncateObjectData_panic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    printf("test for CMD_TruncateObjectData_panic\n");

    //test for badhadle 0xFFFFDEAD result data abort
    /*
    operation.params[0].value.a = CASE_DATA_BAD_HANDLE;
    result = TEEC_InvokeCommand(&session, CMD_TruncateObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0003) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }
    */

    //test for right case
    operation.params[0].value.a = CASE_DATA_ACCESS_RIGHT_NOT_SET;
    result = TEEC_InvokeCommand(&session, CMD_TruncateObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    printf("CASE_DATA_ACCESS_RIGHT_NOT_SET pass\n");
    //test for readdata from transient object should panic, but now return access deny
    operation.params[0].value.a = CASE_DATA_OBJECT_NOT_PERSISTENT;
    result = TEEC_InvokeCommand(&session, CMD_TruncateObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.39 SeekObjectData_panic
TEEC_Result CCmdSeekObjectData_panic(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_NONE);

    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    printf("test for CMD_SeekObjectData_panic\n");

    //test for badhadle data abort
    /*
    operation.params[0].value.a = CASE_DATA_BAD_HANDLE;
    result = TEEC_InvokeCommand(&session, CMD_SeekObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0003) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }*/

    //test for readdata from transient object should panic, but now return access deny
    operation.params[0].value.a = CASE_DATA_OBJECT_NOT_PERSISTENT;
    result = TEEC_InvokeCommand(&session, CMD_SeekObjectData_panic, &operation, &origin);
    if (result != 0xFFFF0001) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.40
TEEC_Result CCmdReadObjectData(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_TEMP_OUTPUT,
            TEEC_NONE,
            TEEC_NONE);

    char attr_1buf[64];
    operation.params[1].tmpref.buffer = attr_1buf;
    operation.params[1].tmpref.size = 64;
    operation.params[0].value.a = 10;
    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    printf("test for CMD_ReadObjectData\n");

    //test for readdata from transient object should panic, but now return access deny
    result = TEEC_InvokeCommand(&session, CMD_ReadObjectData, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    printf("operation.params[1].tmpref.buffer is %s\n",(char *)(operation.params[1].tmpref.buffer));
    printf("operation.params[1].tmpref.size is %d\n",operation.params[1].tmpref.size);
    return 0;
    error:
        return result;
}

//testcase No.29
TEEC_Result CCmdSeekWriteReadObjectData(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    //CASE_POPULATE_BAD_PARAM
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_VALUE_INPUT,
            TEEC_MEMREF_TEMP_INPUT,
            TEEC_MEMREF_TEMP_OUTPUT);

    char attr_2buf[4] = {"abc"};
    char attr_3buf[64];
    operation.params[0].value.a = 0;//TEE_DATA_SEEK_SET;
    operation.params[0].value.b = 5;
    operation.params[1].value.a = 10;
    operation.params[1].value.b = TEEC_VALUE_UNDEF;
    operation.params[2].tmpref.buffer = attr_2buf;
    operation.params[2].tmpref.size = 4;
    operation.params[3].tmpref.buffer = attr_3buf;
    operation.params[3].tmpref.size = 64;
    printf("test for CMD_SeekWriteReadObjectData\n");


    //test for readdata from transient object should panic, but now return access deny
    result = TEEC_InvokeCommand(&session, CMD_SeekWriteReadObjectData, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }

    return 0;
    error:
        return result;
}

//testcase No.29
TEEC_Result CCmdTruncateReadObjectData(void)
{
    TEEC_Operation operation;
    TEEC_Result result;

    //CASE_POPULATE_BAD_PARAM
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
            TEEC_VALUE_INPUT,
            TEEC_NONE,
            TEEC_NONE,
            TEEC_MEMREF_TEMP_OUTPUT);

    char attr_3buf[1024];
    operation.params[0].value.a = 10;
    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    operation.params[3].tmpref.buffer = attr_3buf;
    operation.params[3].tmpref.size = 1024;
    printf("test for CMD_TruncateReadObjectData\n");

    //test for readdata from transient object should panic, but now return access deny

    result = TEEC_InvokeCommand(&session, CMD_TruncateReadObjectData, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto error;
    }
    printf("operation.params[3].tmpref.buffer is %s\n",(char *)(operation.params[3].tmpref.buffer));
    printf("operation.params[3].tmpref.size is %d\n",operation.params[3].tmpref.size);
    return 0;
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
#if 1
    if(TEEC_SUCCESS != CCmdAllocateTransientChain())
    {
        TEEC_Error("CmdAllocateTransientChain failed\n");
        goto error;
    }
    printf("No.1 CCmdAllocateTransientChain test success!\n");
#endif


#ifdef PANIC
    if(TEEC_SUCCESS != CCmdGetObjectInfoPanic())
    {
        TEEC_Error("CMD_GetObjectInfoPanic failed\n");
        goto error;
    }
    printf("No.2 CMD_GetObjectInfoPanic test success!\n");
#endif

#ifdef PANIC
    if(TEEC_SUCCESS != CCmdRestrictObjectUsagePanic())
    {
        TEEC_Error("CCmdRestrictObjectUsagePanic failed\n");
        goto error;
    }
    printf("No.3 CCmdRestrictObjectUsagePanic test success!\n");
#endif

#ifdef PANIC
    if(TEEC_SUCCESS != CCmdCloseObjectPanic())
    {
        TEEC_Error("CCmdCloseObjectPanic failed\n");
        goto error;
    }
    printf("No.4 CCmdRestrictObjectUsagePanic test success!\n");
#endif

#if 1
    if(TEEC_SUCCESS != CCmdCloseFreeAndResetObjectSuccessHandleNull())
    {
        TEEC_Error("CCmdCloseFreeAndResetObjectSuccessHandleNull failed\n");
        goto error;
    }
    printf("No.5 CCmdRestrictObjectUsagePanic test success!\n");
#endif

#ifdef PANIC
    if(TEEC_SUCCESS != CCmdFreeTransientObjectPanic())
    {
        TEEC_Error("CCmdFreeTransientObjectPanic failed\n");
        goto error;
    }
    printf("No.6 CCmdRestrictObjectUsagePanic test success!\n");
#endif

#ifdef PANIC
    if(TEEC_SUCCESS != CCmdResetTransientObjectPanic())
    {
        TEEC_Error("CCmdResetTransientObjectPanic failed\n");
        goto error;
    }
    printf("No.7 CCmdRestrictObjectUsagePanic test success!\n");
#endif

#if 1
    if(TEEC_SUCCESS != CCmdStoreAndReadBufferAttribute())
    {
        TEEC_Error("CCmdStoreAndReadBufferAttribute failed\n");
        goto error;
    }
    printf("No.8 CCmdStoreAndReadBufferAttribute test success!\n");
#endif

#if 1
    if(TEEC_SUCCESS != CCmdInitRefAttributePanic())
    {
        TEEC_Error("CCmdInitRefAttributePanic failed\n");
        goto error;
    }
    printf("No.9 CCmdInitRefAttributePanic test success!\n");
#endif

#if 1
    if(0xFFFF0006 != CCmdInitObjectAndAttributes_1())   //TEE_ERROR_BAD_PARAMETERS
    {
        TEEC_Error("CCmdInitObjectAndAttributes_1 failed\n");
        goto error;
    }
    printf("No.10 CCmdInitObjectAndAttributes_1 test success!\n");

    if(0x0000f006 != CCmdInitObjectAndAttributes_10())   //CASE_INIT_ATTRIBUTE_PANIC
    {
        TEEC_Error("CCmdInitObjectAndAttributes_10 failed\n");
        goto error;
    }
    printf("No.10 CCmdInitObjectAndAttributes_10 test success!\n");

    if((result= CCmdInitObjectAndAttributes_20_26()) != 0)   //CASE_GET_OBJECT_BUFFER_ATTRIB_BIT28
    {
        TEEC_Error("CCmdInitObjectAndAttributes_20_26 failed\n");
        goto error;
    }
    printf("No.10 CCmdInitObjectAndAttributes_20_26 test success!\n");

    if((result= CCmdInitObjectAndAttributes_30_52()) != 0)   //CASE_GET_OBJECT_BUFFER_ATTRIB_BIT28
    {
        TEEC_Error("CCmdInitObjectAndAttributes_30_52 failed\n");
        goto error;
    }
    printf("No.10 CCmdInitObjectAndAttributes_30_52 test success!\n");
    printf("No.10 CCmdInitObjectAndAttributes test success!\n");
#endif

#if 1
    if((result= CCmdCreatePersistentObjectPanic()) != 0)
    {
        TEEC_Error("CCmdCreatePersistentObjectPanic failed\n");
        goto error;
    }
    printf("No.12 CCmdCreatePersistentObjectPanic test success!\n");
#endif

#if 1
    if((result= CCmdCreatePersistentObject_ItemNotFound()) != 0)
    {
        TEEC_Error("CCmdCreatePersistentObject_ItemNotFound failed\n");
        goto error;
    }
    printf("No.13 CCmdCreatePersistentObject_ItemNotFound test success!\n");
#endif

#if 1
    // this testcase has doubts
    if((result= CCmdCreatePersistentObject_AccessConflict()) != 0)
    {
        TEEC_Error("CCmdCreatePersistentObject_AccessConflict failed\n");
        goto error;
    }
    printf("No.14 CCmdCreatePersistentObject_AccessConflict test success!\n");
#endif

#if 1
    if((result= CCmdCreatePersistentObject_Success()) != 0)
    {
        TEEC_Error("CCmdCreatePersistentObject_Success failed\n");
        goto error;
    }
    printf("No.15 CCmdCreatePersistentObject_Success test success!\n");
#endif

#if 1
    if((result= CCmdOpenPersistentObjectPanic()) != 0)
    {
        TEEC_Error("CCmdOpenPersistentObjectPanic failed\n");
        goto error;
    }
    printf("No.16 CCmdOpenPersistentObjectPanic test success!\n");
#endif

#if 1
    if((result= CCmdOpenPersistentObject_ItemNotFound()) != 0)
    {
        TEEC_Error("CCmdOpenPersistentObject_ItemNotFound failed\n");
        goto error;
    }
    printf("No.17 CCmdOpenPersistentObject_ItemNotFound test success!\n");
#endif

#if 1
    if((result= CCmdOpenPersistentObject_Success()) != 0)
    {
        TEEC_Error("CCmdCreatePersistentObject_Success failed\n");
        goto error;
    }
    printf("No.18 CCmdOpenPersistentObject_Success test success!\n");
#endif

#if 1
    if((result= CCmdRenamePersistentObjectPanic()) != 0)
    {
        TEEC_Error("CCmdRenamePersistentObjectPanic failed\n");
        goto error;
    }
    printf("No.19 CCmdRenamePersistentObjectPanic test success!\n");
#endif

#if 1
    if((result= CCmdRenamePersistentObject_AccessConflict()) != 0)
    {
        TEEC_Error("CCmdRenamePersistentObject_AccessConflict failed\n");
        goto error;
    }
    printf("No.20 CCmdRenamePersistentObject_AccessConflict test success!\n");
#endif

#if 1
    if((result= CCmdRenamePersistentObject_Success()) != 0)
    {
        TEEC_Error("CCmdRenamePersistentObject_Success failed\n");
        goto error;
    }
    printf("No.21 CCmdRenamePersistentObject_Success test success!\n");
#endif

#if 1
    if((result= CCmdEnumeratorOnPersistentObjects()) != 0)
    {
        TEEC_Error("CCmdEnumeratorOnPersistentObjects failed\n");
        goto error;
    }
    printf("No.22 CCmdEnumeratorOnPersistentObjects test success!\n");
#endif

#if 1
    if((result= CCmdCloseAndDeletePersistentObjectPanic()) != 0)
    {
        TEEC_Error("CCmdCloseAndDeletePersistentObjectPanic failed\n");
        goto error;
    }
    printf("No.23 CCmdEnumeratorOnPersistentObjects test success!\n");
#endif

#if 1
    if((result= CCmdFreeCloseAndDeletePersistentObjectSuccessHandleNull()) != 0)
    {
        TEEC_Error("CCmdFreeCloseAndDeletePersistentObjectSuccessHandleNull failed\n");
        goto error;
    }
    printf("No.24 CCmdEnumeratorOnPersistentObjects test success!\n");
#endif

    //TEE_ObjectEnumHandle IS 0xFFFFDEAD so DATA ABORT test 25-28
#if 0
    if((result= CCmdFreePersistentObjectEnumeratorPanic()) != 0)
    {
        TEEC_Error("CCmdFreePersistentObjectEnumeratorPanic failed\n");
        goto error;
    }


    if((result= CCmdResetPersistentObjectEnumeratorPanic()) != 0)
    {
        TEEC_Error("CCmdResetPersistentObjectEnumeratorPanic failed\n");
        goto error;
    }

    if((result= CCmdStartPersistentObjectEnumeratorPanic()) != 0)
    {
        TEEC_Error("CCmdStartPersistentObjectEnumeratorPanic failed\n");
        goto error;
    }

    if((result= CCmdGetNextPersistentObjectPanic()) != 0)
    {
        TEEC_Error("CCmdGetNextPersistentObjectPanic failed\n");
        goto error;
    }
#endif

#if 1
    if((result= CCmdStartNGetPersistentObjectEnumerator_itemNotFound()) != 0)
    {
        TEEC_Error("CCmdStartNGetPersistentObjectEnumerator_itemNotFound failed\n");
        goto error;
    }
    printf("No.29 CCmdStartNGetPersistentObjectEnumerator_itemNotFound test success!\n");
#endif

#if 1
    if((result= CCmdInitValueAttribute()) != 0)
    {
        TEEC_Error("CCmdInitValueAttribute failed\n");
        goto error;
    }
    printf("No.30 CCmdInitValueAttribute test success!\n");
#endif

#if 1
    if((result= CCmdGetBufferAttribute_object_uninitialized()) != 0)
    {
        TEEC_Error("CCmdGetBufferAttribute_object_uninitialized failed\n");
        goto error;
    }
    printf("No.31 CCmdGetBufferAttribute_object_uninitialized test success!\n");
#endif

#if 1
    if((result= CCmdOpenPersistentObject_conflict()) != 0)
    {
        TEEC_Error("CCmdOpenPersistentObject_conflict failed\n");
        goto error;
    }
    printf("No.32 CCmdOpenPersistentObject_conflict test success!\n");
#endif

#if 0
    //TODO generatekey
    if((result= CCmdGetRSAAttributes()) != 0)
    {
        TEEC_Error("CCmdGetRSAAttributes failed\n");
        goto error;
    }
    printf("No.33 CCmdGetRSAAttributes test success!\n");
#endif

#if 0
    //data abort
    if((result= CCmdGetObjectValueAttributePanic()) != 0)
    {
        TEEC_Error("CCmdGetObjectValueAttributePanic failed\n");
        goto error;
    }
    printf("No.34 CCmdGetObjectValueAttributePanic test success!\n");
#endif

#if 0
     //TODO generatekey
    if((result= CCmdGetDHAttributes()) != 0)
    {
        TEEC_Error("CCmdGetDHAttributes failed\n");
        goto error;
    }
    printf("No.35 CCmdGetDHAttributes test success!\n");
#endif

#if 1
    if((result= CCmdReadObjectData_panic()) != 0)
    {
        TEEC_Error("CCmdReadObjectData_panic failed\n");
        goto error;
    }
    printf("No.36 CCmdReadObjectData_panic test success!\n");
#endif

#if 1
    if((result= CCmdWriteObjectData_panic()) != 0)
    {
        TEEC_Error("CCmdWriteObjectData_panic failed\n");
        goto error;
    }
    printf("No.37 CCmdWriteObjectData_panic test success!\n");
#endif


#if 1
printf("No.38 CCmdTruncateObjectData_panic test start!\n");
    if((result= CCmdTruncateObjectData_panic()) != 0)
    {
        TEEC_Error("CCmdTruncateObjectData_panic failed\n");
        goto error;
    }
    printf("No.38 CCmdTruncateObjectData_panic test success!\n");
#endif

#if 1
    if((result= CCmdSeekObjectData_panic()) != 0)
    {
        TEEC_Error("CCmdSeekObjectData_panic failed\n");
        goto error;
    }
    printf("No.39 CCmdSeekObjectData_panic test success!\n");
#endif

#if 1
    if((result= CCmdReadObjectData()) != 0)
    {
        TEEC_Error("CCmdReadObjectData failed\n");
        goto error;
    }
    printf("No.40 CCmdReadObjectData test success!\n");
#endif

#if 1
    if((result= CCmdSeekWriteReadObjectData()) != 0)
    {
        TEEC_Error("CCmdSeekWriteReadObjectData failed\n");
        goto error;
    }
    printf("No.41 CCmdInitValueAttribute test success!\n");
#endif

#if 1
    if((result= CCmdTruncateReadObjectData()) != 0)
    {
        TEEC_Error("CCmdTruncateReadObjectData failed\n");
        goto error;
    }
    printf("No.42 CCmdInitValueAttribute test success!\n");
#endif

    printf("ALL test case are PASS\n");
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
