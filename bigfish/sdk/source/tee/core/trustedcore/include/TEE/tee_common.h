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
* Copyright(C), 2008-2013, Hisilicon Tech. Co., Ltd. ALL RIGHTS RESERVED.
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
 * widevine 服务
 */
#define TEE_SERVICE_WIDEVINE \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf8 \
    } \
}


/**
 * @ingroup  TEE_COMMON_DATA
 *
 * playready 服务
 */
#define TEE_SERVICE_PLAYREADY \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf9 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * efuse读写服务
 */
#define TEE_SERVICE_EFUSE \
{ \
    0x05050505, \
    0x0505, \
    0x0505, \
    { \
        0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * HDCP安全存储服务
 */
#define TEE_SERVICE_HDCP \
{ \
    0x06060606, \
    0x0606, \
    0x0606, \
    { \
        0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 \
    } \
}


/**
 * @ingroup  TEE_COMMON_DATA
 *
 * KeyMaster服务
 */
#define TEE_SERVICE_KEYMASTER \
{ \
     0x07070707, \
     0x0707, \
     0x0707, \
     { \
         0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07 \
     } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * secboot服务
 */
#define TEE_SERVICE_SECBOOT \
{ \
     0x08080808, \
     0x0808, \
     0x0808, \
     { \
         0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 \
     } \
}

#define TEE_SERVICE_IMAXCRYPTO \
{ \
     0x09090909, \
     0x0909, \
     0x0909, \
     { \
         0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09 \
     } \
}

#define TEE_SERVICE_GATEKEEPER \
{ \
    0x0B0B0B0B, \
    0x0B0B, \
    0x0B0B, \
    { \
        0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * HDMI HDCP 加密服务
 */
#define TEE_SERVICE_HDMI \
{ \
    0x08080601, \
    0x0100, \
    0x0000, \
    { \
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 \
    } \
}

#define TEE_SERVICE_SSA \
{ \
    0x999286b9, \
    0x54da, \
    0x4235, \
    { \
        0x9e, 0x77, 0x96, 0xe8, 0x1f, 0xea, 0x1e, 0xe4 \
    } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务imax支持的命令ID
 */
enum SVC_IMAX_CMD_ID {
     IMAX_CMD_ID_INVALID = 0x0,         /**< IMAX Task 无效ID*/
     IMAX_CMD_ID_AES_CBC_256,           /**< IMAX AES对称加解密*/
     IMAX_CMD_ID_GKEYPAIR_GPUB,         /**< IMAX 生成公私钥对和公钥*/
     IMAX_CMD_ID_MESSAGE_DECRYPT,       /**< IMAX 消息解密*/
     IMAX_CMD_ID_MESSAGE_AESKEY_DECRYPT,
	 IMAX_CMD_ID_CLOUND_KEY_STORE,      /**< IMAX 云端密钥认证存储*/
     IMAX_CMD_ID_CLOUND_DATA_CIPHER,   /**< IMAX .......*/
     IMAX_CMD_ID_CLOUND_DATA_AES_CBC_NOPADDING_CIPHER, /**IMAX CIPHER*/
};

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_REET \
{ \
     0x0A0A0A0A, \
     0x0A0A, \
     0x0A0A, \
     { \
         0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A \
     } \
}

//del by fanzongqian 216599
#if 0
#define TEE_SERVICE_TUI_KEYBOARD \
{ \
     0x11111111, \
     0x1111, \
     0x1111, \
     { \
         0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 \
     } \
}
#endif
/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_HISI_DEMO \
{ \
     0x0B0B0B0B, \
     0x0B0B, \
     0x0B0B, \
     { \
         0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B \
     } \
}

#define TEE_SERVICE_DRM \
{ \
	0x14047d2d, \
	0xf236, \
	0x48a0, \
	{ \
		0xa0, 0xc4, 0xc1, 0xcc, 0xcb, 0xb6, 0x45, 0x46 \
	} \
}


/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_SEC_MMZ \
{ \
     0x0C0C0C0C, \
     0x0C0C, \
     0x0C0C, \
     { \
         0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C \
     } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_VFMW \
{ \
     0x0D0D0D0D, \
     0x0D0D, \
     0x0D0D, \
     { \
         0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D \
     } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_HISI_TEST \
{ \
     0x0E0E0E0E, \
     0x0E0E, \
     0x0E0E, \
     { \
         0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E \
     } \
}

#define TEE_SERVICE_HISI_VDP \
{ \
     0x1E1E1E1E, \
     0x1E1E, \
     0x1E1E, \
     { \
         0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E \
     } \
}

/**
 * SMMU TASK
 *
 */
#if 0
#define TEE_SERVICE_SMMU \
{\
	0x70e6926a, \
	0x816b, \
	0x19f4, \
	{\
		0xa6, 0x28, 0x3f, 0xcc, 0xaa, 0xb1, 0x21, 0xfa \
	}\
}
#else
#define TEE_SERVICE_SMMU \
{\
	0x0F0F0F0F, \
	0x0F0F, \
	0x0F0F, \
	{\
		0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F \
	}\
}
#endif

#define TEE_SERVICE_VPSS \
{\
       0x3acc8b1b, \
       0xa7e1, \
       0xe511, \
       {\
               0xb8,0x6d,0x9a,0x79,0xf0,0x6e,0x94,0x78 \
       }\
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * Notification task
 */
#define TEE_SERVICE_DMX \
{\
	0x10101010, \
	0x1010, \
	0x1010, \
	{\
		0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 \
	}\
}

/**
 * @ingroup  TEE_STB_PVR
 *
 * Notification task
 */
#define TEE_SERVICE_PVR \
{ \
     0x11111111, \
     0x1111, \
     0x1111, \
     { \
         0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 \
     } \
}


#define TEE_SERVICE_MDPP \
{ \
    0x41d21d0f, \
    0x9757, \
    0x41f1, \
    { \
        0x87, 0x06, 0xb3, 0xba, 0xa3, 0x5f, 0xe8, 0x2f \
    } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA VMXTA task
 */
#define TEE_SERVICE_STB_VMX_ULTRA_VMXTA \
{ \
     0x22222222, \
     0x2222, \
     0x2222, \
     { \
         0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA videomarkTA task
 */
#define TEE_SERVICE_STB_VMX_ULTRA_videomarkTA \
{ \
     0x33333333, \
     0x3333, \
     0x3333, \
     { \
         0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA VMXTAC_TEST_TA2
 */
#define TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA2 \
{ \
     0x44444444, \
     0x4444, \
     0x4444, \
     { \
         0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44 \
     } \
}
/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA VMXTAC_TEST_TA3
 */
#define TEE_SERVICE_STB_VMX_ULTRA_VMXTAC_TEST_TA3 \
{ \
     0x55555555, \
     0x5555, \
     0x5555, \
     { \
         0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA update TA
 */
#define TEE_SERVICE_STB_UPDATE_TA \
{ \
     0x66666666, \
     0x6666, \
     0x6666, \
     { \
         0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66 \
     } \
}

/**
 * @ingroup  TEE_ID
 *
 * VMX ULTRA diplay TA
 */
#define TEE_SERVICE_STB_DISPLAY_TA \
{ \
     0x77777777, \
     0x7777, \
     0x7777, \
     { \
         0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77 \
     } \
}

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务secboot支持的命令ID
 */
enum SVC_SECBOOT_CMD_ID {
     SECBOOT_CMD_ID_INVALID = 0x0,      /**< Secboot Task 无效ID*/
     SECBOOT_CMD_ID_COPY_VRL,           /**< Secboot Task 拷贝VRL*/
     SECBOOT_CMD_ID_COPY_DATA,          /**< Secboot Task 拷贝镜像*/
     SECBOOT_CMD_ID_VERIFY_DATA,        /**< Secboot Task 验证*/
     SECBOOT_CMD_ID_RESET_IMAGE,        /**< Secboot Task 复位SoC请求*/
     SECBOOT_CMD_ID_COPY_VRL_TYPE,     /**< Secboot Task 拷贝VRL，并传递SoC Type*/
     SECBOOT_CMD_ID_COPY_DATA_TYPE,     /**< Secboot Task 拷贝镜像,并传递SoC Type*/
     SECBOOT_CMD_ID_VERIFY_DATA_TYPE,    /**< Secboot Task 校验，并传递SoC Type，校验成功解复位SoC*/
     SECBOOT_CMD_ID_VERIFY_DATA_TYPE_LOCAL, /**< Secboot Task原地校验，并传递SoC Type,校验成功解复位SoC*/
     SECBOOT_CMD_ID_BSP_SEC_CALL,           /**< Secboot Task 执行对应函数*/
};

/**
 * @ingroup TEE_COMMON_DATA
 * 
 * 安全服务secboot支持的镜像类型
 */
enum SVC_SECBOOT_IMG_TYPE {
    MODEM,
    HIFI,
    DSP,
    XDSP,
    TAS,
    WAS,
    CAS,
    MODEM_DTB,
    SOC_MAX
};

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务keymaster支持的命令ID
 */
enum SVC_KEYMASTER_CMD_ID {
     KM_CMD_ID_INVALID = 0x0,       /**< KeyMaster Task 无效ID*/
     KM_CMD_ID_GENERATE_KEYPAIR,    /**< KeyMaster Task 生成密钥对*/
     KM_CMD_ID_GET_PUBLIC_KEY,      /**< KeyMaster Task 获取公钥*/
     KM_CMD_ID_IMPORT_KEYPAIR,      /**< KeyMaster Task 导入密钥对参数*/
     KM_CMD_ID_SIGN_DATA,           /**< KeyMaster Task 签名*/
     KM_CMD_ID_VERIFY_DATA,         /**< KeyMaster Task 验证*/
     KM_CMD_ID_INIT_ABILITY,
     KM_CMD_ID_GENERATE_KEY,
     KM_CMD_ID_GET_KEY_CHARACTER,
     KM_CMD_ID_IMPORT_KEY,
     KM_CMD_ID_EXPORT_KEY,
     KM_CMD_ID_BEGIN,
     KM_CMD_ID_UPDATE,
     KM_CMD_ID_FINISH,
     KM_CMD_ID_ABORT,
};

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务gatekeeper支持的命令ID
 */
enum SVC_GATEKEEPER_CMD_ID {
    GK_CMD_ID_INVALID = 0x0,
    GK_CMD_ID_ENROLL,
    GK_CMD_ID_VERIFY,
};

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
    GLOBAL_CMD_ID_TEE_TIME,         /**< Global Task 获取安全OS的时间 */
    GLOBAL_CMD_ID_TEE_INFO,        /** tlogcat 获取安全OS  状态 */
    GLOBAL_CMD_ID_REGISTER_RDR_MEM, /**注册RDR 内存*/    
    GLOBAL_CMD_ID_KILL_TASK,       /** Global Task Kill session */
    GLOBAL_CMD_ID_TUI_EXCEPTION,       /** TUI异常事件处理 */
    GLOBAL_CMD_ID_ADJUST_TIME,       /** TIME时间校正处理 */
    GLOBAL_CMD_ID_UNKNOWN         = 0x7FFFFFFE, /**< Global Task 未知ID*/
    GLOBAL_CMD_ID_MAX             = 0x7FFFFFFF  /**< Global Task 最大ID*/
};

/**
 * @ingroup  TEE_COMMON_DATA
 *
 * 安全服务echo支持的命令ID
 */
enum echo_service_cmd_id {
    ECHO_CMD_ID_INVALID = 0x0,     /**< Echo Task 无效ID*/
    ECHO_CMD_ID_SEND_CMD,           /**< Echo Task发送命令*/
    ECHO_CMD_ID_EFUSE_READ,
    ECHO_CMD_ID_EFUSE_WRITE,
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
    CRYPT_CMD_ID_CIPHER_AES_ECB_PKCS5,
    CRYPT_CMD_ID_CIPHER_AES_CBC_PKCS5,
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

enum crypt_tz_cmd_id {
	CMD_TZ_CIPHER_INIT = 2,
	CMD_TZ_CIPHER_DEINIT,
	CMD_TZ_CIPHER_ENCRYPT,
	CMD_TZ_CIPHER_ENCRYPTMULTI,
	CMD_TZ_CIPHER_DECRYPT,
	CMD_TZ_CIPHER_DECRYPTMULTI,
	CMD_TZ_CIPHER_CONFIGHANDLE,
	CMD_TZ_CIPHER_CREATEHANDLE,
	CMD_TZ_CIPHER_DESTROYHANDLE,
	CMD_TZ_CIPHER_GETHANDLECONFIG,
	CMD_TZ_CIPHER_GETRANDOMNUMBER,
	CMD_TZ_CIPHER_ENCRYPTHDCPKEY,
	CMD_TZ_CIPHER_LOADHDCPKEY,
	CMD_TZ_CIPHER_HASHINIT,  //15
	CMD_TZ_CIPHER_HASHUPDATE,
	CMD_TZ_CIPHER_HASHFINAL,
	CMD_TZ_OTP_TEST,
	CMD_TZ_CIPHER_TEST,
	CMD_TZ_ADVCA_GDRMENCRYPT,
	CMD_TZ_TEST,
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
    STORAGE_CMD_ID_SEEK,                    /**< Storage Task获取当前文件位置*/
    STORAGE_CMD_ID_TELL,                    /**< Storage Task重定位文件*/
    STORAGE_CMD_ID_TRUNCATE,                /**< Storage Task改变文件大小*/
    STORAGE_CMD_ID_REMOVE,                  /**< Storage Task删除文件*/
    STORAGE_CMD_ID_FINFO,                   /**< Storage Task返回文件状态*/
    STORAGE_CMD_ID_FSYNC,                   /**< Storage Task同步文件到存储设备*/
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
