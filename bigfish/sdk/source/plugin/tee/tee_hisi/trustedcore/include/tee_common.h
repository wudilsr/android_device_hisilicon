/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : tee_common.h
* Description : tee common definitions, must be consistent with teec definitions
* Author      : yaodongdong@huawei.com
* Date        : 2012.12.31
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

/**
* @file tee_common.h
*
* Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED.
*
* 描述：ServiceID、CommandID定义头文件
*/

/** @defgroup TEE_API 安全侧接口 */
/** @defgroup TEE_COMMON_DATA 公共数据定义
* @ingroup TEE_API
*/

#ifndef __TEE_COMMON_H_
#define __TEE_COMMON_H_

#define CIPHER_ENCRYPT 0
#define CIPHER_DECRYPT 1

#define MD5_OUTPUT_LEN 16
#define SHA1_OUTPUT_LEN 20
#define SHA224_OUTPUT_LEN 28
#define SHA256_OUTPUT_LEN 32
#define SHA384_OUTPUT_LEN 48
#define SHA512_OUTPUT_LEN 64
#define HMAC_KEY_LEN 16
#define HMAC_DATA_LEN 50
#define HMAC_OUTPUT_LEN 16
#define AES_128_CBC_LEN 16
#define AES_128_ECB_LEN 16
#define AES_128_CTR_LEN 16
#define AES_128_XTS_LEN 16
#define DES_ECB_LEN 8
#define DES_CBC_LEN 8
#define DES3_CBC_LEN 8
#define DES3_ECB_LEN 8
#define IGNORE_PARAM  0xff
#if 1
/**
 * @ingroup  TEE_COMMON_DATA
 * 密钥派生时补充结构体最大字节
 *
*/
#define TEE_DK_MAX_SIZE_OF_OTHER_INFO  64 /*bytes*/
#endif

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务Global
 */
#define TEE_SERVICE_GLOBAL \
{ \
    0x00000000, \
    0x0000, \
    0x0000, \
    { \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务Echo
 */
#define TEE_SERVICE_ECHO \
{ \
    0x01010101, \
    0x0101, \
    0x0101, \
    { \
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全存储服务
 */
#define TEE_SERVICE_STORAGE \
{ \
    0x02020202, \
    0x0202, \
    0x0202, \
    { \
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务UT测试
 */
#define TEE_SERVICE_UT \
{ \
    0x03030303, \
    0x0303, \
    0x0303, \
    { \
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 加解密服务
 */
#define TEE_SERVICE_CRYPT \
{ \
    0x04040404, \
    0x0404, \
    0x0404, \
    { \
        0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * demo service
 */

#define TEE_SERVICE_DEMO \
{ \
    0xffffffff, \
    0x0000, \
    0x0000, \
    { \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03 \
    } \
}

/*
#define TEE_SERVICE_DEMO \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf3 \
    } \
}
*/

#define TEE_SERVICE_DEMO1 \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf4 \
    } \
}

#define TEE_SERVICE_DEMO2 \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf5 \
    } \
}

#define TEE_SERVICE_DEMO3 \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf6 \
    } \
}

#define TEE_SERVICE_DEMO4 \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf7 \
    } \
}

#define TEE_SERVICE_DEMO5 \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf8 \
    } \
}

#define TEE_SERVICE_DEMO6 \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf9 \
    } \
}

#define TEE_SERVICE_DEMO7 \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xfa \
    } \
}

#define TEE_SERVICE_DEMO8 \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xfb \
    } \
}

#define TEE_SERVICE_DEMO9 \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xfc \
    } \
}


/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务global支持的命令ID
 */
enum global_service_cmd_id {
    GLOBAL_CMD_ID_INVALID = 0x0,    /**< Global Task 无效ID*/
    GLOBAL_CMD_ID_BOOT_ACK,         /**< Global Task 启动应答*/
    GLOBAL_CMD_ID_OPEN_SESSION,     /**< Global Task 打开Session*/
    GLOBAL_CMD_ID_CLOSE_SESSION,    /**< Global Task 关闭Session*/
    GLOBAL_CMD_ID_LOAD_SECURE_APP,  /**< Global Task 动态加载安全应用*/
    GLOBAL_CMD_ID_NEED_LOAD_APP,    /**< Global Task 判断是否是需要加载安全应用*/
    GLOBAL_CMD_ID_REGISTER_AGENT,   /**< Global Task 注册代理*/
    GLOBAL_CMD_ID_UNREGISTER_AGENT, /**< Global Task 注销代理*/
    GLOBAL_CMD_ID_REGISTER_NOTIFY_MEMORY,   /**< Global Task 注册异步调用缓冲区*/
    GLOBAL_CMD_ID_UNREGISTER_NOTIFY_MEMORY, /**< Global Task 注销异步调用缓冲区*/
    GLOBAL_CMD_ID_INIT_CONTENT_PATH,      /**< Global Task初始化content path*/
    GLOBAL_CMD_ID_TERMINATE_CONTENT_PATH,   /**< Global Task释放content path*/
    GLOBAL_CMD_ID_ALLOC_EXCEPTION_MEM,  /**< Global Task 分配异常信息保存空间*/
    GLOBAL_CMD_ID_ALLOC_SMC_MEM,
    GLOBAL_CMD_ID_FREE_SMC_MEM,
    GLOBAL_CMD_ID_TEE_TIME,         /**< 安全服务Global，获取安全OS的时间 */
    GLOBAL_CMD_ID_UNKNOWN         = 0x7FFFFFFE, /**< Global Task 未知ID*/
    GLOBAL_CMD_ID_MAX             = 0x7FFFFFFF  /**< Global Task 最大ID*/
};

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务echo支持的命令ID
 */
enum echo_service_cmd_id {
    ECHO_CMD_ID_INVALID = 0x10,     /**< Echo Task 无效ID*/
    ECHO_CMD_ID_SEND_CMD,           /**< Echo Task发送命令*/
    ECHO_CMD_ID_UNKNOWN         = 0x7FFFFFFE,   /**< Echo Task 未知ID*/
    ECHO_CMD_ID_MAX             = 0x7FFFFFFF    /**< Echo Task 最大ID*/
};

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务CRYPTO支持的命令ID, 包括对称加解密、非对称加解密、摘要HMAC等\n
 * 注意:对称算法中的nopad模式需要TA(Trusted Application，可信应用)来做填充
 */
enum crypt_service_cmd_id {
    CRYPT_CMD_ID_INVALID = 0x10,            /**< 无效ID */
    //CRYPT_CMD_ID_LOAD_LIBS,               /**< 加载加解密库 */
    //CRYPT_CMD_ID_UNLOAD_LIBS,             /**< 卸载加解密库 */
    CRYPT_CMD_ID_ENCRYPT,                   /**< 加密 */
    CRYPT_CMD_ID_DECRYPT,                   /**< 解密 */
    CRYPT_CMD_ID_MD5,                       /**< 摘要算法MD5 */
    CRYPT_CMD_ID_SHA1,                      /**< 摘要算法SHA1 */
    CRYPT_CMD_ID_SHA224,                    /**< 摘要算法SHA224 */
    CRYPT_CMD_ID_SHA256,                    /**< 摘要算法SHA256 */
    CRYPT_CMD_ID_SHA384,                    /**< 摘要算法SHA384 */
    CRYPT_CMD_ID_SHA512,                    /**< 摘要算法SHA512 */
    CRYPT_CMD_ID_HMAC_MD5,                  /**< HMAC MD5 */
    CRYPT_CMD_ID_HMAC_SHA1,                 /**< HMAC SHA1 */
    CRYPT_CMD_ID_HMAC_SHA224,               /**< HMAC SHA224 */
    CRYPT_CMD_ID_HMAC_SHA256,               /**< HMAC SHA256 */
    CRYPT_CMD_ID_HMAC_SHA384,               /**< HMAC SHA384 */
    CRYPT_CMD_ID_HMAC_SHA512,               /**< HMAC SHA512 */
    CRYPT_CMD_ID_CIPHER_AES_CBC,        /**< 对称加解密AES 128bits密钥 CBC模式 */
    CRYPT_CMD_ID_CIPHER_AES_CBC_CTS,    /**< 对称加解密AES 128bits密钥 CBC_CTS模式 */
    CRYPT_CMD_ID_CIPHER_AES_ECB,        /**< 对称加解密AES 128bits密钥 ECB模式 */
    CRYPT_CMD_ID_CIPHER_AES_CTR,        /**< 对称加解密AES 128bits密钥 CTR模式 */
    CRYPT_CMD_ID_CIPHER_AES_CBC_MAC,    /**< 对称加解密AES 128bits密钥 CBC_MAC模式 */
    CRYPT_CMD_ID_CIPHER_AES_XCBC_MAC,   /**< 对称加解密AES 128bits密钥 XCBC_MAC模式 */
    CRYPT_CMD_ID_CIPHER_AES_CMAC,       /**< 对称加解密AES 128bits密钥 CMAC模式 */
    CRYPT_CMD_ID_CIPHER_AES_CCM,        /**< 对称加解密AES 128bits密钥 CCM模式 */
    CRYPT_CMD_ID_CIPHER_AES_XTS,        /**< 对称加解密AES 128bits密钥 XTS模式 */
    CRYPT_CMD_ID_CIPHER_DES_ECB,            /**< 对称加解密DES ECB模式 */
    CRYPT_CMD_ID_CIPHER_DES_CBC,            /**< 对称加解密DES CBC模式 */
    CRYPT_CMD_ID_CIPHER_DES3_ECB,           /**< 对称加解密DES3 ECB模式 */
    CRYPT_CMD_ID_CIPHER_DES3_CBC,           /**< 对称加解密DES3 CBC模式 */
    CRYPT_CMD_ID_CIPHER_RND,                /**< 随机数模式 */
    CRYPT_CMD_ID_CIPHER_DK,                 /**< 密钥派生模式 */
    CRYPT_CMD_ID_RSAES_PKCS1_V1_5,          /**< 非对称加解密PKCS1_V1_5模式 */
    CRYPT_CMD_ID_RSAES_PKCS1_OAEP_MGF1_SHA1,/**< 非对称加解密OAEP_SHA1模式 */
    CRYPT_CMD_ID_RSAES_PKCS1_OAEP_MGF1_SHA224,/**< 非对称加解密OAEP_SHA224模式 */
    CRYPT_CMD_ID_RSAES_PKCS1_OAEP_MGF1_SHA256,/**< 非对称加解密OAEP_SHA256模式 */
    CRYPT_CMD_ID_RSAES_PKCS1_OAEP_MGF1_SHA384,/**< 非对称加解密OAEP_SHA384模式 */
    CRYPT_CMD_ID_RSAES_PKCS1_OAEP_MGF1_SHA512,/**< 非对称加解密OAEP_SHA512模式 */
    CRYPT_CMD_ID_RSA_NOPAD,                 /**< 非对称加解密无填充模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_V1_5_MD5,     /**< 非对称签名验证PKCS1_V1_5_MD5模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_V1_5_SHA1,    /**< 非对称签名验证PKCS1_V1_5_SHA1模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_V1_5_SHA224,  /**< 非对称签名验证PKCS1_V1_5_SHA224模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_V1_5_SHA256,  /**< 非对称签名验证PKCS1_V1_5_SHA256模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_V1_5_SHA384,  /**< 非对称签名验证PKCS1_V1_5_SHA384模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_V1_5_SHA512,  /**< 非对称签名验证PKCS1_V1_5_SHA512模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_PSS_MGF1_SHA1,/**< 非对称签名验证PSS_MGF1_SHA1模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_PSS_MGF1_SHA224,/**< 非对称签名验证PSS_MGF1_SHA224模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_PSS_MGF1_SHA256,/**< 非对称签名验证PSS_MGF1_SHA256模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_PSS_MGF1_SHA384,/**< 非对称签名验证PSS_MGF1_SHA384模式 */
    CRYPT_CMD_ID_RSASSA_PKCS1_PSS_MGF1_SHA512,/**< 非对称签名验证PSS_MGF1_SHA512模式 */
    CRYPT_CMD_ID_DSA_SHA1,                  /**< 非对称签名验证DSA模式 */
    CRYPT_CMD_ID_UNKNOWN = 0x7FFFFFFE,      /**< 未知模式 */
    CRYPT_CMD_ID_MAX = 0x7FFFFFFF           /**< 最大CMD ID */
};

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务CRYPTO状态定义
 */
typedef enum crypt_cmd_status{
    CRYPT_INIT = 0,         /**< 初始化 */
    CRYPT_UPDATE,           /**< 块运算 */
    CRYPT_UPDATEAAD,        /**< AE中认证数据块运算 */
    CRYPT_DOFINAL,          /**< 结束 */
    CRYPT_CMPFINAL,         /**< 结束并验证 */
    CRYPT_SIGNDIGEST,       /**< 签名 */
    CRYPT_VERIFYDIGEST,     /**< 认证 */
    CRYPT_STATUS_NUM        /**< 状态个数 */
} crypt_status;

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务STORAGE支持的命令ID
 */
enum storage_service_cmd_id {
    STORAGE_CMD_ID_INVALID = 0x10,          /**< Storage Task 无效ID*/
    STORAGE_CMD_ID_OPEN,                    /**< Storage Task打开文件*/
    STORAGE_CMD_ID_CLOSE,                   /**< Storage Task关闭文件*/
    STORAGE_CMD_ID_CLOSEALL,                /**< Storage Task关闭所有文件*/
    STORAGE_CMD_ID_READ,                    /**< Storage Task读取文件*/
    STORAGE_CMD_ID_WRITE,                   /**< Storage Task写入文件*/
    STORAGE_CMD_ID_UNKNOWN = 0x7FFFFFFE,    /**< Storage Task 未知ID*/
    STORAGE_CMD_ID_MAX = 0x7FFFFFFF         /**< Storage Task 最大ID*/
};
#if 1
/**
 * ingroup  TEE_COMMON_DATA
 *
 * tee DK other structure, containing the optional data for KDF,
 * if any data is not needed, then the pointer value and
 * the size must be set to NULL
 */
typedef struct
{
    /* a unique object identifier (OID), indicating algorithm(s)
    for which the keying data will be used*/
    unsigned char    AlgorithmID[TEE_DK_MAX_SIZE_OF_OTHER_INFO];    /**< a unique object identifier (OID) */
    unsigned int   SizeOfAlgorithmID;                           /**< size of AlgorithmID */
    /* Public information contributed by the initiator */
    unsigned char    PartyUInfo[TEE_DK_MAX_SIZE_OF_OTHER_INFO]; /**< Public information contributed by the initiator */
    unsigned int   SizeOfPartyUInfo;                            /**< size of PartyUInfo */
    /* Public information contributed by the responder */
    unsigned char    PartyVInfo[TEE_DK_MAX_SIZE_OF_OTHER_INFO]; /**< Public information contributed by the responder */
    unsigned int   SizeOfPartyVInfo;                            /**< size of PartyVInfo */
    /* Mutually-known private information, e.g. shared information
    communicated throgh a separate channel */
    unsigned char    SuppPrivInfo[TEE_DK_MAX_SIZE_OF_OTHER_INFO];   /**< Mutually-known private information */
    unsigned int   SizeOfSuppPrivInfo;                          /**< size of SuppPrivInfo */
    /* Mutually-known public information, */
    unsigned char    SuppPubInfo[TEE_DK_MAX_SIZE_OF_OTHER_INFO];    /**< Mutually-known public information */
    unsigned int   SizeOfSuppPubInfo;                           /**< size of SuppPubInfo */
}tee_DK_OtherInfo;

/**
 * ingroup  TEE_COMMON_DATA
 *
 * TEE的密钥派生函数模式定义
*/
typedef enum
{
    TEE_DK_ASN1_DerivMode = 0,                          /**< ASN1_DerivMode */
    TEE_DK_ConcatDerivMode = 1,                         /**< ConcatDerivMode */
    TEE_DK_X963_DerivMode = TEE_DK_ConcatDerivMode,     /**< X963_DerivMode */
    TEE_DK_OMADRM_DerivMode = 2,                        /**< OMADRM_DerivMode */
    TEE_DK_ISO18033_KDF1_DerivMode = 3,                 /**< ISO18033_KDF1_DerivMode */
    TEE_DK_ISO18033_KDF2_DerivMode = 4,                 /**< ISO18033_KDF2_DerivMode */
    TEE_DK_DerivFunc_NumOfModes,                        /**< num of modes */
}tee_DK_DerivFuncMode;

/**
 * ingroup  TEE_COMMON_DATA
 *
 * TEE的密钥派生HASH模式定义
*/
typedef enum
{
    TEE_DK_HASH_SHA1_mode = 0,              /**< HASH_SHA1 */
    TEE_DK_HASH_SHA224_mode = 1,            /**< HASH_SHA224 */
    TEE_DK_HASH_SHA256_mode = 2,            /**< HASH_SHA256 */
    TEE_DK_HASH_SHA384_mode = 3,            /**< HASH_SHA384 */
    TEE_DK_HASH_SHA512_mode = 4,            /**< HASH_SHA512 */
    TEE_DK_HASH_NumOfModes,                 /**< num of modes */
}tee_DK_HASH_Mode;
#endif
#endif

/**
* History: \n
* 2013-05-03，y00204347，Create \n
*
* vi: set expandtab ts=4 sw=4 tw=80:
*/
