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

#define TEE_ATTR_NONE 0x0;

/* example uuid */
static const TEEC_UUID EXAMPLE_uuid =
{
    0x534D4152, 0x5443, 0x534C,
    { 0x54, 0x44, 0x41, 0x54, 0x41, 0x53, 0x54, 0x31 }
};

char TEE_ATTR_DH_PRIME_VALUE01 []=
{0xe0,0x01,0xe8,0x96,0x7d,0xb4,0x93,0x53,
    0xe1,0x6f,0x8e,0x89,0x22,0x0c,0xce,0xfc,
    0x5c,0x5f,0x12,0xe3,0xdf,0xf8,0xf1,0xd1,
    0x49,0x90,0x12,0xe6,0xef,0x53,0xe3,0x1f,
    0x02,0xea,0xcc,0x5a,0xdd,0xf3,0x37,0x89,
    0x35,0xc9,0x5b,0x21,0xea,0x3d,0x6f,0x1c,
    0xd7,0xce,0x63,0x75,0x52,0xec,0x38,0x6c,
    0x0e,0x34,0xf7,0x36,0xad,0x95,0x17,0xef,
    0xfe,0x5e,0x4d,0xa7,0xa8,0x6a,0xf9,0x0e,
    0x2c,0x22,0x8f,0xe4,0xb9,0xe6,0xd8,0xf8,
    0xf0,0x2d,0x20,0xaf,0x78,0xab,0xb6,0x92,
    0xac,0xbc,0x4b,0x23,0xfa,0xf2,0xc5,0xcc,
    0xd4,0x9a,0x0c,0x9a,0x8b,0xcd,0x91,0xac,
    0x0c,0x55,0x92,0x01,0xe6,0xc2,0xfd,0x1f,
    0x47,0xc2,0xcb,0x2a,0x88,0xa8,0x3c,0x21,
    0x0f,0xc0,0x54,0xdb,0x29,0x2d,0xbc,0x45};

char TEE_ATTR_DH_PRIME_VALUE_WRONG01[] =
{0xe0,0x01,0xe8,0x96,0x7d,0xb4,0x93,0x53,0xe1,0x6f,0x8e,0x89,0x22,0x0c,0xce,0xfc,
    0x5c,0x5f,0x12,0xe3,0xdf,0xf8,0xf1,0xd1,0x49,0x90,0x12,0xe6,0xef,0x53,0xe3,0x1f,
    0x02,0xea,0xcc,0x5a,0xdd,0xf3,0x37,0x89,0x35,0xc9,0x5b,0x21,0xea,0x3d,0x6f,0x1c,
    0xd7,0xce,0x63,0x75,0x52,0xec,0x38,0x6c,0x0e,0x34,0xf7,0x36,0xad,0x95,0x17,0xef,
    0xfe,0x5e,0x4d,0xa7,0xa8,0x6a,0xf9,0x0e,0x2c,0x22,0x8f,0xe4,0xb9,0xe6,0xff,0xff,
    0xff,0x2d,0x20,0xaf,0x78,0xab,0xb6,0x92,0xac,0xbc,0x4b,0x23,0xfa,0xf2,0xc5,0xcc,
    0xd4,0x9a,0x0c,0x9a,0x8b,0xcd,0x91,0xac,0x0c,0x55,0x92,0x01,0xe6,0xc2,0xfd,0x1f,
    0x47,0xc2,0xcb,0x2a,0x88,0xa8,0x3c,0x21,0x0f,0xc0,0x54,0xdb,0x29,0x2d,0xbc,0x45};

char TEE_ATTR_DH_BASE_VALUE01[] =
{0x1c,0xe0,0xf6,0x69,0x26,0x46,0x11,0x97,
    0xef,0x45,0xc4,0x65,0x8b,0x83,0xb8,0xab,
    0x04,0xa9,0x22,0x42,0x68,0x50,0x4d,0x05,
    0xb8,0x19,0x83,0x99,0xdd,0x71,0x37,0x18,
    0xcc,0x1f,0x24,0x5d,0x47,0x6c,0xcf,0x61,
    0xa2,0xf9,0x34,0x93,0xf4,0x1f,0x55,0x52,
    0x48,0x65,0x57,0xe6,0xd4,0xca,0xa8,0x00,
    0xd6,0xd0,0xdb,0x3c,0xbf,0x5a,0x95,0x4b,
    0x20,0x8a,0x4e,0xba,0xf7,0xe6,0x49,0xfb,
    0x61,0x24,0xd8,0xa2,0x1e,0xf2,0xf2,0x2b,
    0xaa,0xae,0x29,0x21,0x10,0x19,0x10,0x51,
    0x46,0x47,0x31,0xb6,0xcc,0x3c,0x93,0xdc,
    0x6e,0x80,0xba,0x16,0x0b,0x66,0x64,0xa5,
    0x6c,0xfa,0x96,0xea,0xf1,0xb2,0x83,0x39,
    0x8e,0xb4,0x61,0x64,0xe5,0xe9,0x43,0x84,
    0xee,0x02,0x24,0xe7,0x1f,0x03,0x7c,0x23};

char TEE_ATTR_DSA_PRIME_VALUE01[] =
    {0xf6,0xad,0x20,0x71,0xe1,0x5a,0x4b,0x9c,0x2b,0x7e,0x53,0x26,0xda,0x43,
    0x9d,0xc1,0x47,0x4c,0x1a,0xd1,0x6f,0x2f,0x85,0xe9,0x2c,0xea,0x89,0xfc,0xdc,
0x74,0x66,0x11,0xcf,0x30,0xdd,0xc8,0x5e,0x33,0xf5,0x83,0xc1,0x9d,0x10,0xbc,
0x1a,0xc3,0x93,0x22,0x26,0x24,0x6f,0xa7,0xb9,0xe0,0xdd,0x25,0x77,0xb5,0xf4,
0x27,0x59,0x4c,0x39,0xfa,0xeb,0xfc,0x59,0x8a,0x32,0xe1,0x74,0xcb,0x8a,0x68,
0x03,0x57,0xf8,0x62,0xf2,0x0b,0x6e,0x84,0x32,0xa5,0x30,0x65,0x2f,0x1c,0x21,
0x39,0xae,0x1f,0xaf,0x76,0x8b,0x83};

char TEE_ATTR_DSA_SUBPRIME_VALUE01[] =
{ 87,0x44,0xe4,0xdd,0xc6,0xd0,0x19,0xa5,0xea,0xc2,0xb1,0x5a,0x15,0xd7,
0xe1,0xc7,0xf6,0x63,0x35,0xf7};

char TEE_ATTR_DSA_BASE_VALUE01[] =
{0x9a,0x09,0x32,0xb3,0x8c,0xb2,0x10,0x5b,0x93,0x00,0xdc,0xb8,0x66,0xc0,
0x66,0xd9,0xce,0xc6,0x43,0x19,0x2f,0xcb,0x28,0x34,0xa1,0x23,0x9d,0xba,0x28,
0xbd,0x09,0xfe,0x01,0x00,0x1e,0x04,0x51,0xf9,0xd6,0x35,0x1f,0x6e,0x56,0x4a,
0xfb,0xc8,0xf8,0xc3,0x9b,0x10,0x59,0x86,0x3e,0xbd,0x09,0x85,0x09,0x0b,0xd5,
0x5c,0x82,0x8e,0x9f,0xc1,0x57,0xac,0x7d,0xa3,0xcf,0xc2,0x89,0x2a,0x0e,0xd9,
0xb9,0x32,0x39,0x05,0x82,0xf2,0x97,0x1e,0x4a,0x0c,0x48,0x3e,0x06,0x22,0xd7,
0x31,0x66,0xbf,0x62,0xa5,0x9f,0x26};

enum TEE_ObjectAttribute{
    TEE_ATTR_SECRET_VALUE = 0xC0000000,                   /**< attribute为SECRET_VALUE */
    TEE_ATTR_RSA_MODULUS = 0xD0000130,                    /**< attribute为RSA_MODULUS */
    TEE_ATTR_RSA_PUBLIC_EXPONENT = 0xD0000230,            /**< attribute为RSA_PUBLIC_EXPONENT */
    TEE_ATTR_RSA_PRIVATE_EXPONENT = 0xC0000330,           /**< attribute为RSA_PRIVATE_EXPONENT */
    TEE_ATTR_RSA_PRIME1 = 0xC0000430,                     /**< attribute为RSA_PRIME1 */
    TEE_ATTR_RSA_PRIME2 = 0xC0000530,                     /**< attribute为RSA_PRIME2 */
    TEE_ATTR_RSA_EXPONENT1 = 0xC0000630,                  /**< attribute为RSA_EXPONENT1 */
    TEE_ATTR_RSA_EXPONENT2 = 0xC0000730,                  /**< attribute为RSA_EXPONENT2 */
    TEE_ATTR_RSA_COEFFICIENT  = 0xC0000830,               /**< attribute为RSA_COEFFICIENT */
    TEE_ATTR_DSA_PRIME = 0xD0001031,                      /**< attribute为DSA_PRIME */
    TEE_ATTR_DSA_SUBPRIME = 0xD0001131,                   /**< attribute为DSA_SUBPRIME */
    TEE_ATTR_DSA_BASE = 0xD0001231,                       /**< attribute为DSA_BASE */
    TEE_ATTR_DSA_PUBLIC_VALUE = 0xD0000131,               /**< attribute为DSA_PUBLIC_VALUE */
    TEE_ATTR_DSA_PRIVATE_VALUE = 0xC0000231,              /**< attribute为DSA_PRIVATE_VALUE */
    TEE_ATTR_DH_PRIME = 0xD0001032,                       /**< attribute为DH_PRIME */
    TEE_ATTR_DH_SUBPRIME = 0xD0001132,                    /**< attribute为DH_SUBPRIME */
    TEE_ATTR_DH_BASE = 0xD0001232,                        /**< attribute为DH_BASE */
    TEE_ATTR_DH_X_BITS = 0xF0001332,                      /**< attribute为DH_X_BITS */
    TEE_ATTR_DH_PUBLIC_VALUE = 0xD0000132,                /**< attribute为DH_PUBLIC_VALUE */
    TEE_ATTR_DH_PRIVATE_VALUE = 0xC0000232,               /**< attribute为DH_PRIVATE_VALUE */
    TEE_ATTR_RSA_OAEP_LABEL = 0xD0000930,                 /**< attribute为RSA_OAEP_LABEL*/
    TEE_ATTR_RSA_PSS_SALT_LENGTH = 0xF0000A30             /**< attribute为RSA_OAEP_LABEL */
};

enum TEE_ObjectType{
    TEE_TYPE_AES = 0xA0000010,                    /**< object中的key为AES类型 */
    TEE_TYPE_DES = 0xA0000011,                    /**< object中的key为DES类型 */
    TEE_TYPE_DES3 = 0xA0000013,                   /**< object中的key为DES3类型 */
    TEE_TYPE_HMAC_MD5 = 0xA0000001,               /**< object中的key为HMAC_MD5类型 */
    TEE_TYPE_HMAC_SHA1 = 0xA0000002,              /**< object中的key为HMAC_SHA1类型 */
    TEE_TYPE_HMAC_SHA224 = 0xA0000003,            /**< object中的key为HMAC_SHA224类型 */
    TEE_TYPE_HMAC_SHA256 = 0xA0000004,            /**< object中的key为HMAC_SHA256类型 */
    TEE_TYPE_HMAC_SHA384 = 0xA0000005,            /**< object中的key为HMAC_SHA384类型 */
    TEE_TYPE_HMAC_SHA512 = 0xA0000006,            /**< object中的key为HMAC_SHA512类型 */
    TEE_TYPE_RSA_PUBLIC_KEY = 0xA0000030,         /**< object中的key为RSA_PUBLIC_KEY类型 */
    TEE_TYPE_RSA_KEYPAIR = 0xA1000030,            /**< object中的key为RSA_KEYPAIR类型 */
    TEE_TYPE_DSA_PUBLIC_KEY = 0xA0000031,         /**< object中的key为DSA_PUBLIC_KEY类型 */
    TEE_TYPE_DSA_KEYPAIR = 0xA1000031,            /**< object中的key为DSA_KEYPAIR类型 */
    TEE_TYPE_DH_KEYPAIR = 0xA1000032,             /**< object中的key为DH_KEYPAIR类型 */
    TEE_TYPE_GENERIC_SECRET = 0xA0000000,         /**< object中的key为GENERIC_SECRET类型 */
    TEE_TYPE_DATA = 0xA1000033,                   /**< object没有key，为纯数据类型 */
};

#define BIG_SIZE   1024
#define DS_BIG_SIZE   16384
#define SIZE_OVER_MEMORY   0xFFFFFFFE
#define SIZE_ZERO   0
#define SMALL_SIZE   0xA


#define KEY_SIZE_TOO_LARGE   4096
#define SIZE_AES_256     256
#define SIZE_DES3_192    192
#define SIZE_DES_64      64
#define SIZE_DH_KEYPAIR_1024     1024
#define SIZE_DSA_KEYPAIR_768     768
#define SIZE_DSA_PUBLIC_KEY_768      768
#define SIZE_GENERIC_SECRET_2048     2048
#define SIZE_HMAC_MD5_256    256
#define SIZE_HMAC_SHA1_256   256
#define SIZE_HMAC_SHA224_256     256
#define SIZE_HMAC_SHA256_512     512
#define SIZE_HMAC_SHA384_512     512
#define SIZE_HMAC_SHA512_512     512
#define SIZE_RSA_KEYPAIR_2048    2048
#define SIZE_RSA_PUBLIC_KEY_2048     2048
#define SIZE_ZERO    0
#define WRONG_SIZE   5

//self-define
//objectType is TEE_TYPE_AES
#define objectType  0xA0000010
#define maxObjectSize   0x00000800
//attributeID is TEE_ATTR_SECRET_VALUE
#define attributeID 0xC0000000

/** Command ids **/
#define CMD_AllocateTransientChain                          0x00001001
#define CMD_GetObjectInfoPanic                              0x00001002
#define CMD_RestrictObjectUsagePanic                        0x00001003
#define CMD_CloseObjectPanic                                0x00001004
#define CMD_CloseFreeAndResetObjectSuccessHandleNull        0x00001005
#define CMD_FreeTransientObjectPanic                        0x00001006
#define CMD_ResetTransientObjectPanic                       0x00001007
#define CMD_StoreAndReadBufferAttribute                     0x00001008
#define CMD_InitRefAttributePanic                           0x00001009
#define CMD_InitObjectAndAttributes                         0x0000100A
#define CMD_GenerateKey                                     0x0000100B
#define CMD_CreatePersistentObjectPanic                     0x0000100C
#define CMD_CreatePersistentObject_ItemNotFound             0x0000100D
#define CMD_CreatePersistentObject_AccessConflict           0x0000100E
#define CMD_CreatePersistentObject_Success                  0x0000100F
#define CMD_OpenPersistentObjectPanic                       0x00001010
#define CMD_OpenPersistentObject_ItemNotFound               0x00001011
#define CMD_OpenPersistentObject_Success                    0x00001012
#define CMD_RenamePersistentObjectPanic                     0x00001013
#define CMD_RenamePersistentObject_AccessConflict           0x00001014
#define CMD_RenamePersistentObject_Success                  0x00001015
#define CMD_EnumeratorOnPersistentObjects                   0x00001016
#define CMD_CloseAndDeletePersistentObjectPanic             0x00001017
#define CMD_FreeCloseAndDeletePersistentObjectSuccessHandleNull   0x00001018
#define CMD_FreePersistentObjectEnumeratorPanic             0x00001019
#define CMD_ResetPersistentObjectEnumeratorPanic            0x0000101A
#define CMD_StartPersistentObjectEnumeratorPanic            0x0000101B
#define CMD_GetNextPersistentObjectPanic                    0x0000101C
#define CMD_StartNGetPersistentObjectEnumerator_itemNotFound   0x0000101D
#define CMD_GetBufferAttribute_object_uninitialized         0x0000101E
#define CMD_InitValueAttribute                              0x0000101F
#define CMD_OpenPersistentObject_conflict                   0x00001020
#define CMD_GetRSAAttributes                                0x00001021
#define CMD_GetObjectValueAttributePanic                    0x00001022
#define CMD_GetDHAttributes                                 0x00001023
#define CMD_ReadObjectData_panic                            0x00001024
#define CMD_WriteObjectData_panic                           0x00001025
#define CMD_TruncateObjectData_panic                        0x00001026
#define CMD_SeekObjectData_panic                            0x00001027
#define CMD_ReadObjectData                                  0x00001028
#define CMD_SeekWriteReadObjectData                         0x00001029
#define CMD_TruncateReadObjectData                          0x0000102A

/* CmdInitObjectAndAttributes */
#define CASE_POPULATE_BAD_PARAM                                      1
#define CASE_INIT_ATTRIBUTE_PANIC                                    10
#define CASE_GET_OBJECT_BUFFER_ATTRIB_BIT28                          20
#define CASE_GET_OBJECT_BUFFER_ATTRIB_BIT29                          21
#define CASE_GET_OBJECT_BUFFER_ATTRIB_NOT_INIT                       22
#define CASE_GET_OBJECT_BUFFER_ATTRIB_ITEM_NOT_FOUND                 23
#define CASE_GET_OBJECT_BUFFER_ATTRIB_TOO_SHORT_BUFFER               24
#define CASE_GET_OBJECT_BUFFER_ATTRIB_BUFFER_NULL                    25
#define CASE_GET_OBJECT_BUFFER_ATTRIB_INVALID_OBJECT                 26
#define CASE_COPY_OBJECT_ATTRIBUTE_DEST_NOT_UNINIT                   30
#define CASE_COPY_OBJECT_ATTRIBUTE_SRC_DEST_NOT_COMPAT               31
#define CASE_COPY_OBJECT_ATTRIBUTE_SRC_NOT_INIT                      32
#define CASE_COPY_OBJECT_ATTRIBUTE_SRC_IS_PERSISTENT                 33
#define CASE_ATTRIBUTE_MISSING                                       40
#define CASE_POPULATE_OBJECT_INVALID_OBJECT                          50
#define CASE_POPULATE_OBJECT_NOT_UNINIT                              51
#define CASE_POPULATE_OBJECT_NOT_TRANSIENT                           52

/* CmdGenerateKey */
#define CASE_GENERATE_KEY_BAD_HANDLE                                 100
#define CASE_GENERATE_KEY_PARAM_MISSING                              101
#define CASE_GENERATE_KEY_KEY_SIZE_TOO_LARGE                         102
#define CASE_GENERATE_KEY_BAD_PARAMETER                              103
#define CASE_GENERATE_KEY_OBJECT_NOT_UNINIT                          104
#define CASE_GENERATE_KEY_OBJECT_NOT_TRANSIENT                       105
#define NOMINAL_CASE 106

/* CmdCreatePersistentObject */
#define CASE_CREATE_PERSISTENT_OBJECT_OBJECT_ID_TOO_LONG             110
#define CASE_CREATE_PERSISTENT_OBJECT_NOT_VALID_HANDLE               111
#define CASE_CREATE_PERSISTENT_OBJECT_READ                           112
#define CASE_CREATE_PERSISTENT_OBJECT_WRITE                          113
#define CASE_CREATE_PERSISTENT_OBJECT_WRITE_META                     114
#define CASE_CREATE_PERSISTENT_OBJECT_SHARE_READ                     115
#define CASE_CREATE_PERSISTENT_OBJECT_SHARE_WRITE                    116
/* CmdOpenPersistentObject */
#define CASE_OPEN_PERSISTENT_OBJECT_READ                             117
#define CASE_OPEN_PERSISTENT_OBJECT_WRITE                            118
#define CASE_OPEN_PERSISTENT_OBJECT_WRITE_META                       119
#define CASE_OPEN_PERSISTENT_OBJECT_SHARE_READ                       120
#define CASE_OPEN_PERSISTENT_OBJECT_SHARE_WRITE                      121
#define CASE_OPEN_PERSISTENT_OBJECT_UNKNOWN_OBJECTID                 130
#define CASE_OPEN_PERSISTENT_OBJECT_UNKNOWN_STORAGEID                131
/* CmdRenamePersistentObjectPanic */
#define CASE_RENAME_PERSISTENT_OBJECT_ID_TOO_LONG                    122
#define CASE_RENAME_PERSISTENT_OBJECT_HANDLE_NOT_VALID               123
#define CASE_RENAME_PERSISTENT_OBJECT_WRITE_META                     124
/* CmdCloseAndDeletePersistentObjectPanic */
#define CASE_CLOSE_N_DELETE_PERSISTENT_OBJ_HANDLE_NOT_VALID          125
#define CASE_CLOSE_N_DELETE_PERSISTENT_OBJ_WRITE_META                126
/* Cases for manage data functions */
#define CASE_DATA_BAD_HANDLE                                         130
#define CASE_DATA_ACCESS_RIGHT_NOT_SET                               131
#define CASE_DATA_OBJECT_NOT_PERSISTENT                              132

void retrieveBufferFromUint32(uint32_t n, char buffer[]);
