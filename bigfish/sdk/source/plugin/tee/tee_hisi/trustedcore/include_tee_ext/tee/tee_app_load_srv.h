/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : tee_app_load_srv.h
* Description : tee app image load service
* Author      : luchenggang@huawei.com
* Date        : 2013.5.20
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

#ifndef __TEE_APP_LOAD_SRV_
#define __TEE_APP_LOAD_SRV_

#include "tee_internal_api.h"

typedef struct{
    uint32_t context_len;   /* manifest_crypto_len + cipher_bin_len */
    uint32_t manifest_crypto_len; /* manifest crypto len */
    uint32_t manifest_plain_len; /* manfiest str + manifest binary */
    uint32_t manifest_str_len;
    uint32_t cipher_bin_len;
}TEEC_image_head;

#define SHA1_LEN 20
#define SHA1_BUF_LEN 64
#define HASH_UPDATA_LEN 64
#define HASH_LEN 18
#define KEY_LEN 18
typedef struct{
    int32_t multi_instance;
    int32_t multi_session;
    int32_t multi_command;
    int32_t heap_size;
    int32_t stack_size;
    int32_t instance_keep_alive;
    int32_t elf_hash_len;
    int32_t elf_cryptkey_len;
/* DTS: 2013061708036, l00202565 modify begin, add task_name */
    int32_t service_name_len;
/* DTS: 2013061708036, l00202565 modify end, add task_name */
}Manifest_info;

typedef struct{
    TEE_UUID srv_uuid;
    Manifest_info Mani_info;
    int8_t *hash_val;
    int8_t *key_val;
/* DTS: 2013061708036, l00202565 modify begin, add task_name */
    int8_t *service_name;
/* DTS: 2013061708036, l00202565 modify end, add task_name */
}Manifest;

typedef struct{
    Manifest manifest; /* save manifest info */
    int8_t* manifest_buf; /* use malloc, save manifest str */
    int8_t* img_buf; /* use rtosck mem, save image */
    int32_t img_offset;
}load_img_info;

#define KEY_SIZE_MAX 64

#define TEE_ERROR_IMG_DECRYPTO_FAIL       0xFF01         /**< ¿ÉÐÅ¾µÏñ½âÃÜ´íÎó */
#define TEE_ERROR_IMG_VERIFY_FAIL         0xFF02         /**< ¿ÉÐÅ¾µÏñÐ£Ñé´íÎó */
#define TEE_ERROR_IMG_ELF_LOAD_FAIL       0xFF03         /**< ¿ÉÐÅ¾µÏñ¼ÓÔØ´íÎó */
#define TEE_ERROR_IMG_NEED_LOAD_FAIL      0xFF04         /**< ¿ÉÐÅ¾µÏñ¼ÓÔØÅÐ¶Ï´íÎó*/
#define TEE_ERROR_IMG_PARSE_FAIL          0xFF05         /**< ¿ÉÐÅ¾µÏñ½âÎö´íÎó */

#define SECURE_IMG_MAX_LEN   200*1024

TEE_Result load_secure_app_image(void);
TEE_Result need_load_app(void);

#endif
