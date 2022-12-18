/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : test_crypto.c
* Description :
* Platform    :
* Author      : qiqingchao
* Version     : V1.0
* Date        : 2013.7.17
* Notes       :
*
*------------------------------------------------------------------------------
* Modifications:
*   Date        Author          Modifications
*******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "tee_client_api.h"
#include "../gp_testsuite/CommomData_for_TestSuite.h"
#if 0
uint8_t AAD1_VALUE[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};
uint8_t TEE_ATTR_AES_256_VALUE01[] = {0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae,
                                      0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61,
                                      0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4};
uint8_t IV1_VALUE_64bits_DES_DES3[] = {0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0x0,0xa,0xb,0xc,0xd,0xe,0xf};
uint8_t IV2_VALUE_128bits_AES[] = {0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0x0,0xa,0xb,0xc,0xd,0xe,0xf,
                                    0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0x0,0xa,0xb,0xc,0xd,0xe,0xf};
uint8_t IV_INVALID_LENGTH_VALUE[] = {0x01,0x02,0x03,0x04,0x05};
uint8_t NONCE1_VALUE_AES_CCM[] = {0x00,0x8D,0x49,0x3B,0x30,0xAE,0x8B,0x3C,0x96,0x96,0x76,0x6C,0xFA};
uint8_t NONCE2_VALUE_AES_GCM[] = {0xca,0xfe,0xba,0xbe,0xfa,0xce,0xdb,0xad,0xde,0xca,0xf8,0x88};

uint8_t DATA_FOR_CRYPTO1[] = {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf,
                              0xa,0xb,0xc,0xd,0xe,0xf,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,
                              0xf,0xe,0xd,0xc,0xb,0xa,0x9,0x8,0x7,0x6,0x5,0x4,0x3,0x2,0x1,0x0,
                              0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf,
                              0xa,0xb,0xc,0xd,0xe,0xf,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,
                              0xf,0xe,0xd,0xc,0xb,0xa,0x9,0x8,0x7,0x6,0x5,0x4,0x3,0x2,0x1,0x0};
uint8_t DATA_FOR_CRYPTO1_PART1[] = {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf,
                                    0xa,0xb,0xc,0xd,0xe,0xf,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9};
uint8_t DATA_FOR_CRYPTO1_PART2[] = {0xf,0xe,0xd,0xc,0xb,0xa,0x9,0x8,0x7,0x6,0x5,0x4,0x3,0x2,0x1,0x0,
                                    0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,0xc,0xd,0xe,0xf};
uint8_t DATA_FOR_CRYPTO1_PART3[] = {0xa,0xb,0xc,0xd,0xe,0xf,0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,
                                    0xf,0xe,0xd,0xc,0xb,0xa,0x9,0x8,0x7,0x6,0x5,0x4,0x3,0x2,0x1,0x0};
uint8_t TEE_ATTR_RSA_MODULUS_VALUE01[] = {
0xf0,0x1a,0x95,0xcd,0x5f,0x9f,0x1c,0xbc,0x5c,0x2e,0xc8,0x00,0x3b,0xfa,0xe0,0xd5,
0x72,0xea,0xfc,0x9e,0x74,0xe1,0x02,0x66,0xa8,0x13,0x3f,0x0c,0xe6,0x24,0xcb,0x1c,
0xa5,0xdf,0x64,0xfb,0x06,0xd7,0x13,0xce,0xaa,0x6c,0xee,0x16,0x7b,0xf8,0x92,0xaf,
0xc4,0x5b,0x46,0x18,0xc6,0x30,0xb6,0x04,0x1c,0x3a,0x2e,0xd7,0xca,0xb8,0xb5,0x00,
0x78,0x89,0xa0,0x69,0x37,0x84,0x59,0x99,0x0c,0x2f,0x00,0xe5,0x3b,0xe1,0x18,0xe0,
0xb9,0x2e,0x77,0x1d,0x32,0x7e,0x5f,0xf4,0x18,0xf3,0x9f,0x58,0xc6,0x83,0xe2,0x7a,
0xcb,0x89,0x18,0xc2,0x09,0x84,0x7e,0x9d,0x96,0xe0,0xb9,0x49,0x75,0xef,0xcf,0xff,
0xf0,0xb6,0x18,0xd3,0x7a,0xc1,0x6f,0x0c,0x55,0x33,0xbe,0x9d,0x63,0x06,0xd6,0x9f,
0xc1,0xa5,0xe9,0xbd,0xb1,0xb2,0x5d,0x5c,0xf9,0xab,0xa9,0xb5,0x6a,0x4e,0xa4,0xfa,
0x44,0x32,0xd6,0x71,0x2e,0x5f,0xa6,0x25,0xf8,0x40,0x24,0xc4,0x5b,0x61,0x55,0x1b,
0xac,0xa3,0x0a,0x11,0x8e,0x65,0x20,0xda,0x2c,0x0d,0xdf,0xdb,0x47,0x6b,0x61,0x18,
0x4d,0xfe,0xfd,0x2a,0x7e,0x77,0x40,0x44,0x43,0xc6,0x33,0x6c,0xe5,0x1b,0x8d,0x80,
0xf9,0x97,0xa2,0xe4,0xb9,0x34,0x3e,0x28,0x94,0x9f,0xbd,0xa8,0x2b,0x0a,0x4d,0x1a,
0xa8,0x06,0xe5,0x99,0x4e,0xb9,0x13,0x45,0xc8,0xf6,0x0f,0xd0,0x4d,0xbf,0xe7,0x8f,
0xed,0xca,0x8e,0xf8,0x8d,0x87,0x5f,0xd4,0xb4,0x1a,0x2c,0xc9,0xa7,0x67,0x7e,0xb2,
0x1b,0xc1,0xce,0xb6,0x83,0x7c,0xce,0xb4,0x3d,0x85,0xc7,0x53,0x30,0x7c,0xfe,0x85};
uint32_t TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01 = 0x10001;
static const TEEC_UUID UUID_TTA_testingInternalAPI_crypto =
{
        0x534D4152, 0x5443, 0x534C,
            { 0x54, 0x43, 0x52, 0x59, 0x50, 0x54, 0x4f, 0x31 }
};
#endif
static TEEC_UUID uuid = UUID_TTA_testingInternalAPI_crypto;
static uint8_t sign[512];
static uint8_t buffer[4];
static uint8_t AES_MAC_result[16];
static uint8_t HMAC_result[64];//MAX size

uint8_t *retrieveUint32toBuffer(uint32_t i)
{
    buffer[3] = i & 0xff;
    buffer[2] = i>>8 & 0xff;
    buffer[1] = i>>16 & 0xff;
    buffer[0] = i>>24 & 0xff;
    //TEEC_Error("%x,%x,%x,%x\n", buffer[0], buffer[1],buffer[2], buffer[3]);
    return buffer;
}

//Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_GCM_Success
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_GCM_Success(uint32_t tagLen)
{
    TEEC_Result result = 0;
    return result;
}
//Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(uint32_t tagLen, uint32_t mac_case,
            uint32_t algorithm, uint32_t short_buffer, uint32_t encrypt_decrypt, uint32_t AEupdate)
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    TEEC_SharedMemory SharedMem3;
    uint8_t IN_AttributeID[60] = {0};
    uint8_t encrypt_Data[3][32] = {0};
    uint8_t decrypt_Data[3][32] = {0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_SECRET_VALUE), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_AES_256_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }

    operation.started = 1;
    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    #if 0
    TEEC_Debug("%x, %x, %x\n", *(uint32_t *)SharedMem1.buffer, *(uint32_t *)(SharedMem1.buffer+4),
        *(uint32_t *)(SharedMem1.buffer+8));
    #endif
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = algorithm;
    operation.params[0].value.b = TEE_MODE_ENCRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)NONCE1_VALUE_AES_CCM, sizeof(NONCE1_VALUE_AES_CCM));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = tagLen/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(NONCE1_VALUE_AES_CCM);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }

    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdate_for_encryption
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    if(AEupdate == 1 && short_buffer == OUTPUT_BUFFER_TOO_SHORT)
        operation.params[3].memref.size = 1;
    else
        operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy((void *)encrypt_Data[0], SharedMem2.buffer, 32);
    #if 0
    for(i=0; i<32; i++){
        TEEC_Debug("encrypt_Data[0][%d] = %x\n", i, *((uint8_t *)SharedMem2.buffer+i));
    }
    #endif
    //Invoke_Crypto_AEUpdate_for_encryption
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)encrypt_Data[1], SharedMem2.buffer, 32);
    #if 0
    for(i=0; i<32; i++){
        TEEC_Debug("encrypt_Data[1][%d] = %x\n", i, encrypt_Data[1][i]);
    }
    #endif

    //Invoke_Crypto_AEEncryptFinal
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    if(short_buffer == OUTPUT_BUFFER_TOO_SHORT && encrypt_decrypt == TEE_MODE_ENCRYPT)
        operation.params[3].memref.size = 1;
    else
        operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEEncryptFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy((void *)encrypt_Data[2], SharedMem2.buffer, 32);
    #if 0
    for(i=0; i<32; i++){
        TEEC_Debug("encrypt_Data[2][%d] = %x\n", i, encrypt_Data[2][i]);
    }
    #endif

    //++++++++++++++++++++++++decrypt+++++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = algorithm;
    operation.params[0].value.b = TEE_MODE_DECRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)NONCE1_VALUE_AES_CCM, sizeof(NONCE1_VALUE_AES_CCM));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = tagLen/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(NONCE1_VALUE_AES_CCM);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdate_for_decryption
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)encrypt_Data[0], sizeof(encrypt_Data[0]));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(encrypt_Data[0]);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(encrypt_Data[0]);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)decrypt_Data[0], SharedMem2.buffer, 32);

    //Invoke_Crypto_AEUpdate_for_decryption
    memcpy(SharedMem1.buffer, (void *)encrypt_Data[1], sizeof(encrypt_Data[1]));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(encrypt_Data[1]);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(encrypt_Data[1]);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)decrypt_Data[1], SharedMem2.buffer, 32);

    //Invoke_Crypto_AEDecryptFinal
    if(mac_case == INVALID_MAC){
        *(char *)(SharedMem3.buffer) = 0xff;
    }
    memcpy(SharedMem1.buffer, (void *)encrypt_Data[2], sizeof(encrypt_Data[2]));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(encrypt_Data[2]);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(encrypt_Data[2]);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    if(short_buffer == OUTPUT_BUFFER_TOO_SHORT && encrypt_decrypt == TEE_MODE_DECRYPT)
        operation.params[3].memref.size = 1;
    else
        operation.params[3].memref.size = sizeof(encrypt_Data[2]);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEDecryptFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy((void *)decrypt_Data[2], SharedMem2.buffer, 32);

    if(memcmp(DATA_FOR_CRYPTO1, decrypt_Data, sizeof(decrypt_Data))){
        TEEC_Error("decrypt data is not equal to encrypt\n");
        #if 1
        for(i=0; i<sizeof(DATA_FOR_CRYPTO1); i++){
            TEEC_Error("DATA_FOR_CRYPTO1[%d] = %x, decrypt_Data[%d] = %x\n",
                i, DATA_FOR_CRYPTO1[i], i, *((uint8_t *)decrypt_Data+i));
        }
        #endif
        result = TEEC_ERROR_MAC_INVALID;
    }
cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed OPERATION_HANDLE_01, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed OPERATION_HANDLE_02, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(SharedMem3.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem3);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

#if 0
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_96_bits_TEE_ALG_AES_GCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_GCM_Success(AES_96_bits);
    return result;
}
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_104_bits_TEE_ALG_AES_GCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_GCM_Success(AES_104_bits);
    return result;
}
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_112_bits_TEE_ALG_AES_GCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_GCM_Success(AES_112_bits);
    return result;
}
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_120_bits_TEE_ALG_AES_GCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_GCM_Success(AES_120_bits);
    return result;
}
#endif
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_32_bits_TEE_ALG_AES_CCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_32_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_NORMAL, TEE_MODE_ENCRYPT, 0);
    return result;
}
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_48_bits_TEE_ALG_AES_CCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_48_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_NORMAL, TEE_MODE_ENCRYPT, 0);
    return result;
}
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_64_bits_TEE_ALG_AES_CCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_64_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_NORMAL, TEE_MODE_ENCRYPT, 0);
    return result;
}
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_96_bits_TEE_ALG_AES_CCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_96_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_NORMAL, TEE_MODE_ENCRYPT, 0);
    return result;
}
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_112_bits_TEE_ALG_AES_CCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_112_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_NORMAL, TEE_MODE_ENCRYPT, 0);
    return result;
}
TEEC_Result Invoke_Crypto_AEDecryptFinal_AES_128_bits_TEE_ALG_AES_CCM_Success()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_128_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_NORMAL, TEE_MODE_ENCRYPT, 0);
    return result;
}

TEEC_Result Invoke_Crypto_AEDecryptFinal_invalid_mac()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_128_bits, INVALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_NORMAL, TEE_MODE_ENCRYPT, 0);
    if(result == TEE_ERROR_MAC_INVALID)
        result = TEEC_SUCCESS;
    return result;
}
//manual
TEEC_Result Invoke_Crypto_AEDecryptFinal_invalid_operation_class()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    TEEC_SharedMemory SharedMem3;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    uint8_t encrypt_Data[3][32] = {0};
    uint8_t decrypt_Data[3][32] = {0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));

    operation.started = 1;

    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;
    operation.params[0].value.b = TEE_MODE_ENCRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)NONCE1_VALUE_AES_CCM, sizeof(NONCE1_VALUE_AES_CCM));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = AES_128_bits;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(NONCE1_VALUE_AES_CCM);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdate_for_encryption
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)encrypt_Data[0], SharedMem2.buffer, 32);

    //Invoke_Crypto_AEUpdate_for_encryption
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)encrypt_Data[1], SharedMem2.buffer, 32);

    //Invoke_Crypto_AEEncryptFinal
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEEncryptFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)encrypt_Data[2], SharedMem2.buffer, 32);

    //++++++++++++++++++++++++decrypt+++++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_MD5;//invalid algorithm
    operation.params[0].value.b = TEE_MODE_DIGEST;//invalid mode
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AEDecryptFinal
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(encrypt_Data[2]);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(encrypt_Data[2]);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(encrypt_Data[2]);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEDecryptFinal, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
        goto cleanup_4;
    }

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(SharedMem3.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem3);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}
//manual
TEEC_Result Invoke_Crypto_AEDecryptFinal_invalid_value_handle()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    TEEC_SharedMemory SharedMem3;

    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    uint8_t encrypt_Data[3][32] = {0};
    uint8_t decrypt_Data[3][32] = {0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));

    operation.started = 1;
    //Invoke_Crypto_AEDecryptFinal
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_INVALID;//invalid handle
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(encrypt_Data[2]);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(encrypt_Data[2]);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(encrypt_Data[2]);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEDecryptFinal, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
        goto cleanup_4;
    }
cleanup_4:

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(SharedMem3.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem3);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}
//manual
TEEC_Result Invoke_Crypto_AEDecryptFinal_operation_not_started()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    TEEC_SharedMemory SharedMem3;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    uint8_t encrypt_Data[3][32] = {0};
    uint8_t decrypt_Data[3][32] = {0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));

    operation.started = 1;

    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;
    operation.params[0].value.b = TEE_MODE_ENCRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)NONCE1_VALUE_AES_CCM, sizeof(NONCE1_VALUE_AES_CCM));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = AES_128_bits;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(NONCE1_VALUE_AES_CCM);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdate_for_encryption
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)encrypt_Data[0], SharedMem2.buffer, 32);

    //Invoke_Crypto_AEUpdate_for_encryption
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)encrypt_Data[1], SharedMem2.buffer, 32);

    //Invoke_Crypto_AEEncryptFinal
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEEncryptFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)encrypt_Data[2], SharedMem2.buffer, 32);

    //++++++++++++++++++++++++decrypt+++++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;
    operation.params[0].value.b = TEE_MODE_DECRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //operation_not_started
    //Invoke_Crypto_AEDecryptFinal
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(encrypt_Data[2]);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(encrypt_Data[2]);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(encrypt_Data[2]);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEDecryptFinal, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
        goto cleanup_4;
    }

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(SharedMem3.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem3);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}

TEEC_Result Invoke_Crypto_AEDecryptFinal_short_buffer()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_128_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_TOO_SHORT, TEE_MODE_DECRYPT, 0);
    if(result == TEE_ERROR_SHORT_BUFFER)
        result = TEEC_SUCCESS;
    return result;
}
//manual
TEEC_Result Invoke_Crypto_AEEncryptFinal_invalid_operation_class()
{

    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;

    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    TEEC_SharedMemory SharedMem3;

    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));


    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_SHA224;//invalid algorithm
    operation.params[0].value.b = TEE_MODE_DIGEST;//invalid mode
    operation.params[1].value.a = SIZE_ZERO + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEEncryptFinal
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEEncryptFinal, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(SharedMem3.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem3);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}
//manual
TEEC_Result Invoke_Crypto_AEEncryptFinal_invalid_value_handle()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;

    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    TEEC_SharedMemory SharedMem3;

    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));


    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }

    //Invoke_Crypto_AEEncryptFinal
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_INVALID;//invalid operation
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEEncryptFinal, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(SharedMem3.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem3);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}
//manual
TEEC_Result Invoke_Crypto_AEEncryptFinal_operation_not_started()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;

    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    TEEC_SharedMemory SharedMem3;

    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));

    operation.started = 1;

    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;
    operation.params[0].value.b = TEE_MODE_ENCRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //operation not started
    //Invoke_Crypto_AEEncryptFinal
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[2].memref.parent = &SharedMem3;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEEncryptFinal, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(SharedMem3.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem3);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AEEncryptFinal_short_buffer()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_128_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_TOO_SHORT, TEE_MODE_ENCRYPT, 0);
    if(result == TEE_ERROR_SHORT_BUFFER)
        result = TEEC_SUCCESS;
    return result;
}

TEEC_Result Invoke_Crypto_AEInit_AES_104_bits_TEE_ALG_AES_CCM_tag_length_not_supported()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_104_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_NORMAL, TEE_MODE_ENCRYPT, 0);
    if (result == TEE_ERROR_NOT_SUPPORTED)
        result = TEEC_SUCCESS;
    return result;
}

TEEC_Result Invoke_Crypto_AEInit_AES_120_bits_TEE_ALG_AES_CCM_tag_length_not_supported()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_120_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_NORMAL, TEE_MODE_ENCRYPT, 0);
    if (result == TEE_ERROR_NOT_SUPPORTED)
        result = TEEC_SUCCESS;
    return result;
}
//manual
TEEC_Result Invoke_Crypto_AEInit_incompatible_nonce_length()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    TEEC_SharedMemory SharedMem3;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));

    operation.started = 1;

    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;
    operation.params[0].value.b = TEE_MODE_ENCRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IV2_VALUE_128bits_AES, sizeof(IV2_VALUE_128bits_AES));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = AES_128_bits;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(IV2_VALUE_128bits_AES);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(SharedMem3.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem3);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}
//manual
TEEC_Result Invoke_Crypto_AEInit_invalid_operation_class()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    TEEC_SharedMemory SharedMem3;

    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));


    SharedMem3.buffer = NULL;
    SharedMem3.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    SharedMem3.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem3);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem3.buffer, 0, sizeof(DATA_FOR_CRYPTO1_PART1));

    operation.started = 1;

    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_ECB_NOPAD;//invalied algorithm
    operation.params[0].value.b = TEE_MODE_ENCRYPT;//invalid mode
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IV2_VALUE_128bits_AES, sizeof(IV2_VALUE_128bits_AES));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = AES_128_bits;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(IV2_VALUE_128bits_AES);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(SharedMem3.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem3);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}

TEEC_Result Invoke_Crypto_AEInit_invalid_value_handle()
{

    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;

    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)NONCE1_VALUE_AES_CCM, sizeof(NONCE1_VALUE_AES_CCM));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_INVALID;
    operation.params[0].value.b = AES_128_bits;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(NONCE1_VALUE_AES_CCM);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AEInit_no_key_programmed()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }

    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;//invalied algorithm
    operation.params[0].value.b = TEE_MODE_DECRYPT;//invalid mode
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)NONCE1_VALUE_AES_CCM, sizeof(NONCE1_VALUE_AES_CCM));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_INVALID;
    operation.params[0].value.b = AES_128_bits;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(NONCE1_VALUE_AES_CCM);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AEUpdateAAD_AAD_length_reached()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }

    operation.started = 1;
    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;
    operation.params[0].value.b = TEE_MODE_DECRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)NONCE1_VALUE_AES_CCM, sizeof(NONCE1_VALUE_AES_CCM));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = AES_128_bits;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(NONCE1_VALUE_AES_CCM);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result != TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AEUpdateAAD_invalid_operation_class()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;

    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_MD5;
    operation.params[0].value.b = TEE_MODE_DIGEST;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AEUpdateAAD_invalid_value_handle()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;

    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_INVALID;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);

cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AEUpdateAAD_operation_not_started()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }

    operation.started = 1;
    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;
    operation.params[0].value.b = TEE_MODE_DECRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result != TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AEUpdate_AAD_length_not_provided()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }

    operation.started = 1;
    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;
    operation.params[0].value.b = TEE_MODE_DECRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)NONCE1_VALUE_AES_CCM, sizeof(NONCE1_VALUE_AES_CCM));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = AES_128_bits;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(NONCE1_VALUE_AES_CCM);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AEUpdate_for_encryption
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }

    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AEUpdate_invalid_operation_class()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_MD5;
    operation.params[0].value.b = TEE_MODE_DIGEST;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AEUpdate_for_encryption
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }

    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}

TEEC_Result Invoke_Crypto_AEUpdate_invalid_value_handle()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    //Invoke_Crypto_AEUpdate_for_encryption
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_INVALID;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}

TEEC_Result Invoke_Crypto_AEUpdate_payload_length_reached()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint32_t IN_AttributeID[] = {TEE_ATTR_SECRET_VALUE, 0, 256,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_2;
    }
    operation.started = 1;
    //Invoke_Crypto_InitObjectWithKeys
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CCM;
    operation.params[0].value.b = TEE_MODE_DECRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AEInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)NONCE1_VALUE_AES_CCM, sizeof(NONCE1_VALUE_AES_CCM));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = AES_128_bits;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(NONCE1_VALUE_AES_CCM);
    operation.params[2].value.a = AAD1_LENGTH;
    operation.params[2].value.b = LENGTH_DATA_FOR_CRYPTO1;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdateAAD
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)AAD1_VALUE, sizeof(AAD1_VALUE));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(AAD1_VALUE);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdateAAD, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdate_for_encryption
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdate_for_encryption
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdate_for_encryption
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AEUpdate_for_encryption
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AEUpdate, &operation, &origin);
    if (result == TEE_ERROR_TARGET_DEAD) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        result = TEEC_SUCCESS;
    }

    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AEUpdate_short_buffer()
{
    TEEC_Result result = Invoke_Crypto_AEDecryptFinal_AES_TEE_ALG_AES_CCM_Success(AES_128_bits, VALID_MAC, TEE_ALG_AES_CCM, OUTPUT_BUFFER_TOO_SHORT, TEE_MODE_SIGN, 1);
    if(result == TEE_ERROR_SHORT_BUFFER)
        result = TEEC_SUCCESS;
    return result;
}

TEEC_Result Invoke_Crypto_AsymmetricDecrypt_TEE_ALG_RSAES_PKCS1_OAEP_MGF1_Success(uint32_t algorithm)
{

    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    #if 0
    uint32_t IN_AttributeID[] = {TEE_ATTR_RSA_MODULUS, 0, 256,
                                 TEE_ATTR_RSA_PUBLIC_EXPONENT, 256, 4,
                                    0, 0, 0,
                                    0, 0, 0,
                                    0, 0, 0};
    #endif
    uint8_t IN_AttributeID[60] = {0};
    uint8_t encrypt_result[512] = {0};
    uint8_t decrypt_result[512] = {0};
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }

    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    //encode IN_AttributeID
    /*SharedMem1 filled with a concatenation of
    (uint_32)$IN_AttributeID_1$|(uint_32)offset of  $IN_Attrib_Value_1$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_1$|
    (uint_32)$IN_AttributeID_2$|(uint_32)offset of  $IN_Attrib_Value_2$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_2$|
    (uint_32)$IN_AttributeID_3$|(uint_32)offset of  $IN_Attrib_Value_3$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_3$|
    ... and so on*/
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_RSA_MODULUS), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+12, retrieveUint32toBuffer(TEE_ATTR_RSA_PUBLIC_EXPONENT), sizeof(uint32_t));
    memcpy(IN_AttributeID+16, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+20, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    /*SharedMem2 filled with a concatenation of
    $IN_Attrib_Value_1$|$IN_Attrib_Value_2$|$IN_Attrib_Value_3$|$IN_Attrib_Value_4$|$IN_Attrib_Value_5$*/
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_RSA_MODULUS_VALUE01, sizeof(TEE_ATTR_RSA_MODULUS_VALUE01));
    memcpy(SharedMem2.buffer+sizeof(TEE_ATTR_RSA_MODULUS_VALUE01), (void *)TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01, sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01));
    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }

    //Invoke_Crypto_InitObjectWithKeys
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_RSA_PUBLIC_KEY;
    operation.params[0].value.b = SIZE_RSA_KEYPAIR_2048/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)+sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_InitObjectWithKeys failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //+++++++++++++++++++++encrypt++++++++++++++++++++++++++++
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = algorithm;
    operation.params[0].value.b = TEE_MODE_ENCRYPT;
    operation.params[1].value.a = SIZE_RSA_KEYPAIR_2048/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_AllocateOperation failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_SetOperationKey failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_AsymmetricEncrypt
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1, sizeof(DATA_FOR_CRYPTO1));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = 512;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AsymmetricEncrypt, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_AsymmetricEncrypt failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy((void *)encrypt_result, SharedMem2.buffer, 512);
    //++++++++++++++++++++++++decrypt+++++++++++++++++++++++++++++++
    //Invoke_Crypto_InitObjectWithKeys

    memset(SharedMem1.buffer, 0, BIG_SIZE);
    //encode IN_AttributeID
    /*SharedMem1 filled with a concatenation of
    (uint_32)$IN_AttributeID_1$|(uint_32)offset of  $IN_Attrib_Value_1$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_1$|
    (uint_32)$IN_AttributeID_2$|(uint_32)offset of  $IN_Attrib_Value_2$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_2$|
    (uint_32)$IN_AttributeID_3$|(uint_32)offset of  $IN_Attrib_Value_3$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_3$|
    ... and so on*/
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_RSA_MODULUS), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+12, retrieveUint32toBuffer(TEE_ATTR_RSA_PUBLIC_EXPONENT), sizeof(uint32_t));
    memcpy(IN_AttributeID+16, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+20, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+24, retrieveUint32toBuffer(TEE_ATTR_RSA_PRIVATE_EXPONENT), sizeof(uint32_t));
    memcpy(IN_AttributeID+28, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)+sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+32, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    /*SharedMem2 filled with a concatenation of
    $IN_Attrib_Value_1$|$IN_Attrib_Value_2$|$IN_Attrib_Value_3$|$IN_Attrib_Value_4$|$IN_Attrib_Value_5$*/
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_RSA_MODULUS_VALUE01, sizeof(TEE_ATTR_RSA_MODULUS_VALUE01));
    memcpy(SharedMem2.buffer+sizeof(TEE_ATTR_RSA_MODULUS_VALUE01), (void *)TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01, sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01));
    memcpy(SharedMem2.buffer+sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)+sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01), (void *)TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01, sizeof(TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01));

    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_RSA_KEYPAIR;
    operation.params[0].value.b = SIZE_RSA_KEYPAIR_2048/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)+sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01)+sizeof(TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_InitObjectWithKeys failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = algorithm;
    operation.params[0].value.b = TEE_MODE_DECRYPT;
    operation.params[1].value.a = SIZE_RSA_KEYPAIR_2048/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_AllocateOperation failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_SetOperationKey failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AsymmetricDecrypt
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)encrypt_result, sizeof(encrypt_result));
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = 512;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AsymmetricDecrypt, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_AsymmetricDecrypt failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy((void *)decrypt_result, SharedMem2.buffer, 512);

    if(memcmp(DATA_FOR_CRYPTO1, decrypt_result, sizeof(DATA_FOR_CRYPTO1))){
        TEEC_Error("decrypt data is not equal to encrypt\n");
        for(i=0; i<sizeof(DATA_FOR_CRYPTO1); i++){
            TEEC_Error("DATA_FOR_CRYPTO1[%d] = %x, decrypt_Data[%d] = %x\n",
                i, DATA_FOR_CRYPTO1[i], i, *((uint8_t *)decrypt_result+i));
        }
        result = TEEC_ERROR_MAC_INVALID;
    }

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}

TEEC_Result Invoke_Crypto_AsymmetricDecrypt_TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1_Success()
{
    TEEC_Result result = Invoke_Crypto_AsymmetricDecrypt_TEE_ALG_RSAES_PKCS1_OAEP_MGF1_Success(TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1);
    return result;
}

TEEC_Result Invoke_Crypto_AsymmetricDecrypt_TEE_ALG_RSAES_PKCS1_V1_5_Success()
{
    TEEC_Result result = Invoke_Crypto_AsymmetricDecrypt_TEE_ALG_RSAES_PKCS1_OAEP_MGF1_Success(TEE_ALG_RSAES_PKCS1_V1_5);
    return result;

}

TEEC_Result Invoke_Crypto_AsymmetricSignDigest_TEE_ALG_RSASSA_PKCS1(uint32_t algorithm, uint32_t hash_algorithm)
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint8_t IN_AttributeID[60] = {0};
    uint32_t hash_len;
    uint8_t *hash_result = NULL;
    switch(hash_algorithm)
    {
        case TEE_ALG_SHA1:
        {
            hash_len = 20;
            break;
        }
        case TEE_ALG_SHA224:
        {
            hash_len = 28;
            break;
        }
        case TEE_ALG_SHA256:
        {
            hash_len = 32;
            break;
        }
        case TEE_ALG_SHA384:
        {
            hash_len = 48;
            break;
        }
        case TEE_ALG_SHA512:
        {
            hash_len = 64;
            break;
        }
        default:
        {
            break;
        }
    }
    hash_result = (uint8_t *)malloc(hash_len);
    memset(hash_result, 0, hash_len);
    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }
    //Invoke_Crypto_AllocateOperation
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = hash_algorithm;
    operation.params[0].value.b = TEE_MODE_DIGEST;
    operation.params[1].value.a = SIZE_ZERO + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_AllocateOperation failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_DigestUpdate
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_DigestUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_DigestUpdate1 failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_DigestUpdate
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_DigestUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_DigestUpdate2 failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_DigestDoFinal
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_DigestDoFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_DigestDoFinal failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //compare hash result
    #if 0
    if(memcmp(hash_result, SharedMem2.buffer, hash_len)){
        TEEC_Error("digest result is wrong!!\n");
        for(i=0; i<hash_len; i++){
            TEEC_Error("hash_result[%d] = %x, digest[%d] = %x\n",
                i, hash_result[i], i, *((uint8_t *)SharedMem2.buffer+i));
        }
        result = TEEC_ERROR_MAC_INVALID;
    }
    #endif
    memcpy(hash_result, SharedMem2.buffer, hash_len);

    //Invoke_Crypto_InitObjectWithKeys
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    //encode IN_AttributeID
    /*SharedMem1 filled with a concatenation of
    (uint_32)$IN_AttributeID_1$|(uint_32)offset of  $IN_Attrib_Value_1$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_1$|
    (uint_32)$IN_AttributeID_2$|(uint_32)offset of  $IN_Attrib_Value_2$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_2$|
    (uint_32)$IN_AttributeID_3$|(uint_32)offset of  $IN_Attrib_Value_3$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_3$|
    ... and so on*/
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_RSA_MODULUS), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+12, retrieveUint32toBuffer(TEE_ATTR_RSA_PUBLIC_EXPONENT), sizeof(uint32_t));
    memcpy(IN_AttributeID+16, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+20, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+24, retrieveUint32toBuffer(TEE_ATTR_RSA_PRIVATE_EXPONENT), sizeof(uint32_t));
    memcpy(IN_AttributeID+28, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)+sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+32, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    /*SharedMem2 filled with a concatenation of
    $IN_Attrib_Value_1$|$IN_Attrib_Value_2$|$IN_Attrib_Value_3$|$IN_Attrib_Value_4$|$IN_Attrib_Value_5$*/
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_RSA_MODULUS_VALUE01, sizeof(TEE_ATTR_RSA_MODULUS_VALUE01));
    memcpy(SharedMem2.buffer+sizeof(TEE_ATTR_RSA_MODULUS_VALUE01), (void *)TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01, sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01));
    memcpy(SharedMem2.buffer+sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)+sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01), (void *)TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01, sizeof(TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01));

    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_RSA_KEYPAIR;
    operation.params[0].value.b = SIZE_RSA_KEYPAIR_2048/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)+sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01)+sizeof(TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_InitObjectWithKeys failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = algorithm;
    operation.params[0].value.b = TEE_MODE_SIGN;
    operation.params[1].value.a = SIZE_RSA_KEYPAIR_2048/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_AllocateOperation failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_SetOperationKey failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_AsymmetricSignDigest
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)hash_result, hash_len);
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = hash_len;
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = 512;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AsymmetricSignDigest, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_AsymmetricSignDigest failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy(sign, SharedMem2.buffer, 512);
cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_FreeAllKeysAndOperations1 failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke CMD_Crypto_FreeAllKeysAndOperations2 failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(hash_result)
        free(hash_result);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_AsymmetricSignDigest_TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1_Success()
{
    TEEC_Result result = Invoke_Crypto_AsymmetricSignDigest_TEE_ALG_RSASSA_PKCS1(TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1, TEE_ALG_SHA1);
    return result;
}

TEEC_Result Invoke_Crypto_AsymmetricSignDigest_TEE_ALG_RSASSA_PKCS1_V1_5_SHA1_Success()
{
    TEEC_Result result = Invoke_Crypto_AsymmetricSignDigest_TEE_ALG_RSASSA_PKCS1(TEE_ALG_RSASSA_PKCS1_V1_5_SHA1, TEE_ALG_SHA1);
    return result;
}

TEEC_Result Invoke_Crypto_AsymmetricVerifyDigest_TEE_ALG_RSASSA_PKCS1(uint32_t algorithm, uint32_t hash_algorithm)
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint8_t IN_AttributeID[60] = {0};
    uint32_t hash_len;
    uint8_t *hash_result = NULL;
    switch(hash_algorithm)
    {
        case TEE_ALG_SHA1:
        {
            hash_len = 20;
            break;
        }
        case TEE_ALG_SHA224:
        {
            hash_len = 28;
            break;
        }
        case TEE_ALG_SHA256:
        {
            hash_len = 32;
            break;
        }
        case TEE_ALG_SHA384:
        {
            hash_len = 48;
            break;
        }
        case TEE_ALG_SHA512:
        {
            hash_len = 64;
            break;
        }
        default:
        {
            break;
        }
    }
    hash_result = (uint8_t *)malloc(hash_len);
    memset(hash_result, 0, hash_len);

    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }
    //Invoke_Crypto_AllocateOperation
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = hash_algorithm;
    operation.params[0].value.b = TEE_MODE_DIGEST;
    operation.params[1].value.a = SIZE_ZERO + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_DigestUpdate
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_DigestUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_DigestUpdate
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_DigestUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_DigestDoFinal
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_DigestDoFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //compare hash result
#if 0
    if(memcmp(hash_result, SharedMem2.buffer, hash_len)){
        TEEC_Error("digest result is wrong!!\n");
        for(i=0; i<hash_len; i++){
            TEEC_Error("hash_result[%d] = %x, digest[%d] = %x\n",
                i, hash_result[i], i, *((uint8_t *)SharedMem2.buffer+i));
        }
        result = TEEC_ERROR_MAC_INVALID;
    }
#endif
    memcpy(hash_result, SharedMem2.buffer, hash_len);

    //Invoke_Crypto_InitObjectWithKeys
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    //encode IN_AttributeID
    /*SharedMem1 filled with a concatenation of
    (uint_32)$IN_AttributeID_1$|(uint_32)offset of  $IN_Attrib_Value_1$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_1$|
    (uint_32)$IN_AttributeID_2$|(uint_32)offset of  $IN_Attrib_Value_2$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_2$|
    (uint_32)$IN_AttributeID_3$|(uint_32)offset of  $IN_Attrib_Value_3$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_3$|
    ... and so on*/
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_RSA_MODULUS), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+12, retrieveUint32toBuffer(TEE_ATTR_RSA_PUBLIC_EXPONENT), sizeof(uint32_t));
    memcpy(IN_AttributeID+16, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+20, retrieveUint32toBuffer(sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    /*SharedMem2 filled with a concatenation of
    $IN_Attrib_Value_1$|$IN_Attrib_Value_2$|$IN_Attrib_Value_3$|$IN_Attrib_Value_4$|$IN_Attrib_Value_5$*/
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_RSA_MODULUS_VALUE01, sizeof(TEE_ATTR_RSA_MODULUS_VALUE01));
    memcpy(SharedMem2.buffer+sizeof(TEE_ATTR_RSA_MODULUS_VALUE01), (void *)TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01, sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01));

    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_RSA_PUBLIC_KEY;
    operation.params[0].value.b = SIZE_RSA_KEYPAIR_2048/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_RSA_MODULUS_VALUE01)+sizeof(TEE_ATTR_RSA_PUBLIC_EXPONENT_VALUE01)+sizeof(TEE_ATTR_RSA_PRIVATE_EXPONENT_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = algorithm;
    operation.params[0].value.b = TEE_MODE_VERIFY;
    operation.params[1].value.a = SIZE_RSA_KEYPAIR_2048/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_AsymmetricVerifyDigest
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)hash_result, hash_len);
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, sign, 512);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_INPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = hash_len;
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = 512;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AsymmetricVerifyDigest, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
    if(hash_result)
        free(hash_result);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}

TEEC_Result Invoke_Crypto_AsymmetricVerifyDigest_TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1_Success()
{
    TEEC_Result result = Invoke_Crypto_AsymmetricVerifyDigest_TEE_ALG_RSASSA_PKCS1(TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1, TEE_ALG_SHA1);
    return result;
}

TEEC_Result Invoke_Crypto_AsymmetricVerifyDigest_TEE_ALG_RSASSA_PKCS1_V1_5_SHA1_Success()
{
    TEEC_Result result = Invoke_Crypto_AsymmetricVerifyDigest_TEE_ALG_RSASSA_PKCS1(TEE_ALG_RSASSA_PKCS1_V1_5_SHA1, TEE_ALG_SHA1);
    return result;
}

TEEC_Result Invoke_Crypto_CipherDoFinal_TEE_ALG_AES_ECB_NOPAD_Success()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint8_t IN_AttributeID[60] = {0};
    uint8_t encrypt_result[3][32] = {0};
    uint8_t decrypt_result[3][32] = {0};

    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_SECRET_VALUE), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_AES_256_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }
    //Invoke_Crypto_InitObjectWithKeys
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_ECB_NOPAD;
    operation.params[0].value.b = TEE_MODE_ENCRYPT;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }

    //Invoke_Crypto_CipherInit
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 0;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_CipherInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_CipherUpdate
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_CipherUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy(encrypt_result[0], SharedMem2.buffer, sizeof(DATA_FOR_CRYPTO1_PART1));

    //Invoke_Crypto_CipherUpdate
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_CipherUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy(encrypt_result[1], SharedMem2.buffer, sizeof(DATA_FOR_CRYPTO1_PART2));

    //Invoke_Crypto_CipherDoFinal
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_CipherDoFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy(encrypt_result[2], SharedMem2.buffer, sizeof(DATA_FOR_CRYPTO1_PART3));

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_CipherDoFinal_TEE_ALG_DES_ECB_NOPAD_Success()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint8_t IN_AttributeID[60] = {0};
    uint8_t encrypt_result[3][32] = {0};
    uint8_t decrypt_result[3][32] = {0};

    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_SECRET_VALUE), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_DES_64_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_DES_64_VALUE01, sizeof(TEE_ATTR_DES_64_VALUE01));

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }
    //Invoke_Crypto_InitObjectWithKeys
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_DES;
    operation.params[0].value.b = SIZE_DES_64/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_DES_64_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_DES_ECB_NOPAD;
    operation.params[0].value.b = TEE_MODE_ENCRYPT;
    operation.params[1].value.a = SIZE_DES_64/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }

    //Invoke_Crypto_CipherInit
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 0;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_CipherInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_CipherUpdate
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_CipherUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy(encrypt_result[0], SharedMem2.buffer, sizeof(DATA_FOR_CRYPTO1_PART1));

    //Invoke_Crypto_CipherUpdate
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_CipherUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy(encrypt_result[1], SharedMem2.buffer, sizeof(DATA_FOR_CRYPTO1_PART2));

    //Invoke_Crypto_CipherDoFinal
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_CipherDoFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    memcpy(encrypt_result[2], SharedMem2.buffer, sizeof(DATA_FOR_CRYPTO1_PART3));

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_DeriveKey_Success()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint8_t IN_AttributeID[60] = {0};

    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }

    //Invoke_Crypto_InitObjectWithKeys
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    //encode IN_AttributeID
    /*SharedMem1 filled with a concatenation of
    (uint_32)$IN_AttributeID_1$|(uint_32)offset of  $IN_Attrib_Value_1$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_1$|
    (uint_32)$IN_AttributeID_2$|(uint_32)offset of  $IN_Attrib_Value_2$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_2$|
    (uint_32)$IN_AttributeID_3$|(uint_32)offset of  $IN_Attrib_Value_3$ in SharedMem2|(uint_32)length of $IN_Attrib_Value_3$|
    ... and so on*/
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_DH_PRIME), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_DH_PRIME_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+12, retrieveUint32toBuffer(TEE_ATTR_DH_BASE), sizeof(uint32_t));
    memcpy(IN_AttributeID+16, retrieveUint32toBuffer(sizeof(TEE_ATTR_DH_PRIME_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+20, retrieveUint32toBuffer(sizeof(TEE_ATTR_DH_BASE_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+24, retrieveUint32toBuffer(TEE_ATTR_DH_PUBLIC_VALUE), sizeof(uint32_t));
    memcpy(IN_AttributeID+28, retrieveUint32toBuffer(sizeof(TEE_ATTR_DH_PRIME_VALUE01)+sizeof(TEE_ATTR_DH_BASE_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+32, retrieveUint32toBuffer(sizeof(TEE_ATTR_DH_PUBLIC_VALUE_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+36, retrieveUint32toBuffer(TEE_ATTR_DH_PRIVATE_VALUE ), sizeof(uint32_t));
    memcpy(IN_AttributeID+40, retrieveUint32toBuffer(sizeof(TEE_ATTR_DH_PRIME_VALUE01)+sizeof(TEE_ATTR_DH_BASE_VALUE01)+sizeof(TEE_ATTR_DH_PUBLIC_VALUE_VALUE01)), sizeof(uint32_t));
    memcpy(IN_AttributeID+44, retrieveUint32toBuffer(sizeof(TEE_ATTR_DH_PRIVATE_VALUE_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    /*SharedMem2 filled with a concatenation of
    $IN_Attrib_Value_1$|$IN_Attrib_Value_2$|$IN_Attrib_Value_3$|$IN_Attrib_Value_4$|$IN_Attrib_Value_5$*/
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_DH_PRIME_VALUE01, sizeof(TEE_ATTR_DH_PRIME_VALUE01));
    memcpy(SharedMem2.buffer+sizeof(TEE_ATTR_DH_PRIME_VALUE01), (void *)TEE_ATTR_DH_BASE_VALUE01,
        sizeof(TEE_ATTR_DH_BASE_VALUE01));
    memcpy(SharedMem2.buffer+sizeof(TEE_ATTR_DH_PRIME_VALUE01)+sizeof(TEE_ATTR_DH_BASE_VALUE01),
        (void *)TEE_ATTR_DH_PUBLIC_VALUE_VALUE01, sizeof(TEE_ATTR_DH_PUBLIC_VALUE_VALUE01));
    memcpy(SharedMem2.buffer+sizeof(TEE_ATTR_DH_PRIME_VALUE01)+sizeof(TEE_ATTR_DH_BASE_VALUE01)+sizeof(TEE_ATTR_DH_PUBLIC_VALUE_VALUE01),
        (void *)TEE_ATTR_DH_PRIVATE_VALUE_VALUE01, sizeof(TEE_ATTR_DH_PRIVATE_VALUE_VALUE01));

    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_DH_KEYPAIR;
    operation.params[0].value.b = SIZE_DH_KEYPAIR_1024/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_DH_PRIME_VALUE01)+sizeof(TEE_ATTR_DH_BASE_VALUE01)
        +sizeof(TEE_ATTR_DH_PUBLIC_VALUE_VALUE01)+sizeof(TEE_ATTR_DH_PRIVATE_VALUE_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_DH_DERIVE_SHARED_SECRET;
    operation.params[0].value.b = TEE_MODE_DERIVE;
    operation.params[1].value.a = SIZE_DH_KEYPAIR_1024/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_DeriveKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_DeriveKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_GenerateRandom()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    uint8_t random1[BIG_SIZE] = {0};
    uint8_t random2[BIG_SIZE] = {0};

    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }
    //Invoke_Crypto_GenerateRandom
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[3].memref.parent = &SharedMem1;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = BIG_SIZE;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_GenerateRandom, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy(random1, SharedMem1.buffer, BIG_SIZE);

    //Invoke_Crypto_GenerateRandom
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_OUTPUT);
    operation.params[3].memref.parent = &SharedMem1;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = BIG_SIZE;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_GenerateRandom, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy(random2, SharedMem1.buffer, BIG_SIZE);

    if(!memcmp(random1, random2, BIG_SIZE)){
        TEEC_Error("random1 == random2\n");
        result = TEEC_ERROR_GENERIC;
    }
cleanup_4:
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_MACComputeFinal_TEE_ALG_AES_CBC_MAC_NOPAD_Success()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint8_t IN_AttributeID[60] = {0};

    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_SECRET_VALUE), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_AES_256_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }
    //Invoke_Crypto_InitObjectWithKeys
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CBC_MAC_NOPAD;
    operation.params[0].value.b = TEE_MODE_MAC;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_MACInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 0;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_MACUpdate
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_MACUpdate
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_MACComputeFinal
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(AES_MAC_result);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACComputeFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)AES_MAC_result, SharedMem2.buffer, sizeof(AES_MAC_result));

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_MACCompareFinal_TEE_ALG_AES_CBC_MAC_NOPAD_Success()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint8_t IN_AttributeID[60] = {0};

    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_SECRET_VALUE), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_AES_256_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_AES_256_VALUE01, sizeof(TEE_ATTR_AES_256_VALUE01));

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }
    //Invoke_Crypto_InitObjectWithKeys
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_AES;
    operation.params[0].value.b = SIZE_AES_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_AES_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_AES_CBC_MAC_NOPAD;
    operation.params[0].value.b = TEE_MODE_MAC;
    operation.params[1].value.a = SIZE_AES_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_MACInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 0;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_MACUpdate
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_MACUpdate
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_MACCompareFinal
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    memcpy(SharedMem2.buffer, (void *)AES_MAC_result, 16);
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(AES_MAC_result);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACCompareFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

TEEC_Result Invoke_Crypto_MACComputeFinal_TEE_ALG_HMAC_SHA1_Success()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint8_t IN_AttributeID[60] = {0};

    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_SECRET_VALUE), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_HMAC_SHA1_256_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_HMAC_SHA1_256_VALUE01, sizeof(TEE_ATTR_HMAC_SHA1_256_VALUE01));

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }
    //Invoke_Crypto_InitObjectWithKeys
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_HMAC_SHA1;
    operation.params[0].value.b = SIZE_HMAC_SHA1_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_HMAC_SHA1_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_HMAC_SHA1;
    operation.params[0].value.b = TEE_MODE_MAC;
    operation.params[1].value.a = SIZE_HMAC_SHA1_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[0].value.b = OBJECT_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_MACInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, IV2_VALUE_128bits_AES, sizeof(IV2_VALUE_128bits_AES));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(IV2_VALUE_128bits_AES);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_MACUpdate
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    memcpy(SharedMem1.buffer+sizeof(DATA_FOR_CRYPTO1_PART1), (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1)+sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    #if 0
    //Invoke_Crypto_MACUpdate
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    #endif
    //Invoke_Crypto_MACCompareFinal
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_MEMREF_PARTIAL_INPUT);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[3].memref.parent = &SharedMem2;
    operation.params[3].memref.offset = 0;
    operation.params[3].memref.size = sizeof(HMAC_result);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACComputeFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    memcpy((void *)HMAC_result, SharedMem2.buffer, sizeof(HMAC_result));

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;
}

TEEC_Result Invoke_Crypto_MACCompareFinal_TEE_ALG_HMAC_SHA1_Success()
{
    TEEC_Context context02;
    TEEC_Session session01;
    TEEC_Result result;
    uint32_t origin, i;
    TEEC_Operation operation;
    TEEC_SharedMemory SharedMem1;
    TEEC_SharedMemory SharedMem2;
    uint8_t IN_AttributeID[60] = {0};

    //InitializeContext
    result = TEEC_InitializeContext(NULL, &context02);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec initial failed\n");
        goto cleanup_1;
    }
    //Allocate a shared memory
    SharedMem1.buffer = NULL;
    SharedMem1.size = BIG_SIZE;
    SharedMem1.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem1);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(IN_AttributeID, retrieveUint32toBuffer(TEE_ATTR_SECRET_VALUE), sizeof(uint32_t));
    memcpy(IN_AttributeID+8, retrieveUint32toBuffer(sizeof(TEE_ATTR_HMAC_SHA1_256_VALUE01)), sizeof(uint32_t));
    memcpy(SharedMem1.buffer, (void *)IN_AttributeID, sizeof(IN_AttributeID));

    SharedMem2.buffer = NULL;
    SharedMem2.size = DS_BIG_SIZE;
    SharedMem2.flags = TEEC_MEM_INOUT;
    result = TEEC_AllocateSharedMemory(
                &context02,
                &SharedMem2);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("allocate failed\n");
        goto cleanup_3;
    }
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem2.buffer, (void *)TEE_ATTR_HMAC_SHA1_256_VALUE01, sizeof(TEE_ATTR_HMAC_SHA1_256_VALUE01));

    //OpenSession
    result = TEEC_OpenSession(&context02, &session01, &uuid,
            TEEC_LOGIN_PUBLIC, NULL, NULL, NULL);
    if(result != TEEC_SUCCESS) {
        TEEC_Error("teec open session failed\n");
        goto cleanup_3;
    }
    //Invoke_Crypto_InitObjectWithKeys
    operation.started = 1;
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_TYPE_HMAC_SHA1;
    operation.params[0].value.b = SIZE_HMAC_SHA1_256/8;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = 4*3*5;//IN_AttributeID
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(TEE_ATTR_HMAC_SHA1_256_VALUE01);
    operation.params[3].value.a = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_InitObjectWithKeys, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_AllocateOperation
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_VALUE_INPUT);
    operation.params[0].value.a = TEE_ALG_HMAC_SHA1;
    operation.params[0].value.b = TEE_MODE_MAC;
    operation.params[1].value.a = SIZE_HMAC_SHA1_256/8 + SIZE_ZERO;
    operation.params[3].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_AllocateOperation, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_SetOperationKey
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[0].value.b = OBJECT_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_SetOperationKey, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
        goto cleanup_4;
    }
    //Invoke_Crypto_MACInit
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, IV2_VALUE_128bits_AES, sizeof(IV2_VALUE_128bits_AES));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(IV2_VALUE_128bits_AES);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACInit, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_MACUpdate
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART1, sizeof(DATA_FOR_CRYPTO1_PART1));
    memcpy(SharedMem1.buffer+sizeof(DATA_FOR_CRYPTO1_PART1), (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART1)+sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    #if 0
    //Invoke_Crypto_MACUpdate
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART2, sizeof(DATA_FOR_CRYPTO1_PART2));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART2);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACUpdate, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    #endif
    //Invoke_Crypto_MACCompareFinal
    memset(SharedMem1.buffer, 0, BIG_SIZE);
    memset(SharedMem2.buffer, 0, DS_BIG_SIZE);
    memcpy(SharedMem1.buffer, (void *)DATA_FOR_CRYPTO1_PART3, sizeof(DATA_FOR_CRYPTO1_PART3));
    memcpy(SharedMem2.buffer, (void *)HMAC_result, sizeof(HMAC_result));
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_MEMREF_PARTIAL_INPUT,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    operation.params[1].memref.parent = &SharedMem1;
    operation.params[1].memref.offset = 0;
    operation.params[1].memref.size = sizeof(DATA_FOR_CRYPTO1_PART3);
    operation.params[2].memref.parent = &SharedMem2;
    operation.params[2].memref.offset = 0;
    operation.params[2].memref.size = sizeof(HMAC_result);
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_MACCompareFinal, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }

cleanup_4:
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_01;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //Invoke_Crypto_FreeAllKeysAndOperations
    operation.paramTypes = TEEC_PARAM_TYPES(
        TEEC_VALUE_INPUT,
        TEEC_NONE,
        TEEC_NONE,
        TEEC_NONE);
    operation.params[0].value.a = OPERATION_HANDLE_02;
    result = TEEC_InvokeCommand(&session01, CMD_Crypto_FreeAllKeysAndOperations, &operation, &origin);
    if (result != TEEC_SUCCESS) {
        TEEC_Error("invoke failed, codes=0x%x, origin=0x%x\n", result, origin);
    }
    //CloseSession
    TEEC_CloseSession(&session01);
cleanup_3:
    if(SharedMem1.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem1);
    if(SharedMem2.buffer)
        TEEC_ReleaseSharedMemory(&SharedMem2);
cleanup_2:
    //FinalizeContext
    TEEC_FinalizeContext(&context02);
cleanup_1:
    return result;

}

Test_GP_FUNC test_gp_func[] =
{
    #if 1
    COMMAND(Invoke_Crypto_AEDecryptFinal_AES_32_bits_TEE_ALG_AES_CCM_Success),
    COMMAND(Invoke_Crypto_CipherDoFinal_TEE_ALG_AES_ECB_NOPAD_Success),
    COMMAND(Invoke_Crypto_CipherDoFinal_TEE_ALG_DES_ECB_NOPAD_Success),
    COMMAND(Invoke_Crypto_GenerateRandom),
    #endif
    #if 0 //输入数据长度与DX不一致
    COMMAND(Invoke_Crypto_AsymmetricSignDigest_TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1_Success),
    COMMAND(Invoke_Crypto_AsymmetricSignDigest_TEE_ALG_RSASSA_PKCS1_V1_5_SHA1_Success),
    COMMAND(Invoke_Crypto_AsymmetricVerifyDigest_TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1_Success),
    COMMAND(Invoke_Crypto_AsymmetricVerifyDigest_TEE_ALG_RSASSA_PKCS1_V1_5_SHA1_Success),
    COMMAND(Invoke_Crypto_MACComputeFinal_TEE_ALG_HMAC_SHA1_Success),
    COMMAND(Invoke_Crypto_MACCompareFinal_TEE_ALG_HMAC_SHA1_Success),
    #endif
    #if 0
    COMMAND(Invoke_Crypto_AsymmetricDecrypt_TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1_Success),
    COMMAND(Invoke_Crypto_AsymmetricDecrypt_TEE_ALG_RSAES_PKCS1_V1_5_Success),
    COMMAND(Invoke_Crypto_DeriveKey_Success),
    COMMAND(Invoke_Crypto_MACComputeFinal_TEE_ALG_AES_CBC_MAC_NOPAD_Success),
    COMMAND(Invoke_Crypto_MACCompareFinal_TEE_ALG_AES_CBC_MAC_NOPAD_Success),
    #endif
};

void main(void)
{
    int i = 0;
    TEEC_Result ret;
    int num = sizeof(test_gp_func)/sizeof(test_gp_func[0]);
    for(i=0; i<num; i++){
        ret = test_gp_func[i].test_func();
        if(ret != TEEC_SUCCESS){
            TEEC_Error("%s failed\n", test_gp_func[i].name);
        }else{
            TEEC_Debug("%s OK\n", test_gp_func[i].name);
        }
    }
}
