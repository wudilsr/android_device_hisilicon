#ifndef __TEE_EXT_API_H
#define __TEE_EXT_API_H
#include "tee_internal_api.h"

#define TEE_INFO_RESERVED (0xFFFFFFFF)
/* Any reasons for these command IDs??? */
#define TEE_RETURN_AGENT_BUFFER  0x99
#define TEE_INVALID_AGENT        0x66
#define TEE_AGENT_LOCK           0x33
struct __tee_info {
    uint32_t version;
    uint32_t reserve1;
    uint32_t reserve2;
    uint32_t reserve3;
};
typedef struct __tee_info tee_info;
TEE_Result TEE_EXT_GetDeviceUniqueId ( uint8_t * DevUniqueID,  uint32_t * length);
TEE_Result TEE_EXT_GetTEEInfo (tee_info * tee_info_data,  uint32_t * length);
TEE_Result TEE_EXT_GetTEEInfo1 (tee_info * tee_info_data,  uint32_t * length);
TEE_Result TEE_EXT_GetTEEInfo2 (tee_info * tee_info_data,  uint32_t * length);
TEE_Result TEE_EXT_GetAgentBuffer(uint32_t agent_id, void** buffer, uint32_t* length);
TEE_Result TEE_EXT_SendAgentRequest(uint32_t agent_id);
TEE_Result TEE_EXT_Mmap(uint32_t phy_addr , uint32_t size, uint32_t *virt_addr, uint32_t secure_mode, uint32_t cache_mode);
TEE_Result TEE_EXT_Unmap(uint32_t va_addr, uint32_t size);
uint32_t TEE_EXT_IsSecureContentMemory(uint32_t addr, uint32_t size);


#define TEE_GET_REEINFO_SUCCESS 0
#define TEE_GET_REEINFO_FAILED 1
struct __ree_info {
    uint32_t userid;
    uint32_t appid;
    uint32_t reserve;
};
typedef struct __ree_info ree_info;
TEE_Result TEE_EXT_GetREEInfo (ree_info * ree_info_data,  uint32_t * length);
#define TEE_EXT_GET_REE_USERID ({ \
    TEE_Result ret; \
    ree_info ree_info_data; \
    uint32_t length = sizeof(ree_info); \
    uint32_t userid; \
    ret = TEE_EXT_GetREEInfo(&ree_info_data, &length); \
    if (ret == TEE_SUCCESS) \
        userid = ree_info_data.userid; \
    else \
        userid = 0; \
    userid;})

#define RESERVED_BUF_SIZE   (32)
typedef struct __caller_info {
    uint32_t session_type;
    union {
        TEE_UUID caller_uuid;
        uint8_t ca_info[RESERVED_BUF_SIZE]; //reserved
    }caller_identity;
    uint8_t reserved[RESERVED_BUF_SIZE]; //reserved
}caller_info;

TEE_Result TEE_EXT_GetCallerInfo (caller_info* caller_info_data, uint32_t length);
/**
 * @ingroup  crypto
 * @brief AES�ӽ��ܼ���ģʽ
 *
 * @par ����:
 * AES���ɼӽ��ܣ�Ŀǰ֧��AES_CBC_NOPAD,AES_ECB_PKCS5������ͨ��rootkey������Կ
 *
 * @attention Ŀǰֻ֧��ECB��CBC
 * @param DB        [IN]        �Ƿ��ô����key��rootkey������Կ
 * @param IV        [IN]        ��ʼ������ָ��
 * @param mode      [IN]        0:����;1:����
 * @param algothem  [IN]        AES�㷨 #TEE_CRYPTO_ALGORITHM_ID
 * @param key       [IN]        ��Կָ��
 * @param key_len   [IN]        ָ�볤��
 * @param cyp_src   [IN]        ��������
 * @param dst       [OUT]       �������
 * @param srclen    [IN]        �������ݳ���
 * @param dstlen    [OUT]       ������ݳ���
 *
 * @retval #TEE_SUCCESS                 �ӽ��ܳɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see TEE_CipherInit | TEE_CipherUpdate | TEE_CipherDoFinal
 * @since V100R005C00
*/
TEE_Result TEE_EXT_AES_CRYPTO(bool DB,uint8_t* IV,bool mode, uint32_t algothem, uint8_t* key, uint32_t key_len,
	uint8_t* cyp_src, uint8_t* dst, uint32_t srclen, uint32_t *dstlen);

/**
 * @ingroup  crypto
 * @brief ����ժҪ
 *
 * @par ����:
 * ����ժҪ
 *
 * @attention
 * @param algorithm     [IN]            ժҪ�㷨����SHA1,SHA256
 * @param DataIn_ptr    [IN]            ��������
 * @param DataSize      [IN]            �������ݳ���
 * @param hash_result   [OUT]           ժҪ��� SHA1 20bytes;SHA256 32bytes
 *
 * @retval #TEE_SUCCESS                 ժҪ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_GENERIC           ժҪʧ��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @since V100R005C00
*/
TEE_Result TEE_EXT_HASH(TEE_CRYPTO_ALGORITHM_ID algorithm, uint8_t *DataIn_ptr, uint32_t DataSize, uint8_t *hash_result);

/**
 * @ingroup  crypto
 * @brief ����RSA��Կ��
 *
 * @par ����:
 * RSA��Կ�����ɣ����Ϊ���ܺ���Կ�����ݽṹ
 *
 * @attention �����Կ�����ݽṹֻ�����ڱ�ģ�������Կ
 * @param pubExp        [IN]        ��Կ��exponent ����0x10001
 * @param key_size      [IN]        ��Կ���� һ��Ϊ2048bit
 * @param key_blob      [OUT]       ���ܺ����Կ�����ݽṹ
 * @param key_blob_size [OUT]       key_blob����
 *
 * @retval #TEE_SUCCESS                 �ӽ��ܳɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see
 * @since V100R005C00
*/
TEE_Result TEE_EXT_generate_keypair(uint32_t pubExp, uint32_t key_size, uint8_t *key_blob, uint32_t *key_blob_size);

/**
 * @ingroup  crypto
 * @brief ��ȡ��Կ
 *
 * @par ����:
 * RSA��Կ��ȡ
 *
 * @attention
 * @param key_blob      [IN]        ��Կ�����ݽṹ
 * @param exopnent      [OUT]       ��Կ��exponent
 * @param modulus       [OUT]       ��Կ��modulus
 * @param exponentSize  [OUT]       exponent����
 * @param modulusSize   [OUT]       modulus����
 *
 * @retval #TEE_SUCCESS                 ��ȡ��Կ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_GENERIC           ��ȡ��Կʧ��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see
 * @since V100R005C00
*/
TEE_Result TEE_EXT_get_keypair_public(uint8_t *key_blob, uint8_t *exopnent, uint8_t *modulus,
    uint32_t *exponentSize, uint32_t *modulusSize);

/**
 * @ingroup  crypto
 * @brief ������ǩ��
 *
 * @par ����:
 * ������ǩ�����㷨�����ƣ�Ŀǰ֧��pkcs1v15��pkcs1v21�Լ�nopad
 *
 * @attention
 * @param algorithm     [IN]        RSA�㷨
 * @param key_blob      [IN]        ��Կ�����ݽṹ
 * @param datain        [IN]        ��Ҫǩ��������
 * @param inSize        [IN]        ��Ҫǩ�����ݳ���
 * @param dataout       [OUT]       ǩ���������
 * @param outSize       [OUT]       ǩ��������ݳ���
 *
 * @retval #TEE_SUCCESS                 ��ȡ��Կ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_GENERIC           ��ȡ��Կʧ��
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 * @retval #TEE_ERROR_NOT_SUPPORTED     �㷨��֧��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see
 * @since V100R005C00
*/
TEE_Result TEE_EXT_sign_data(TEE_CRYPTO_ALGORITHM_ID algorithm, uint8_t *key_blob, uint8_t *datain,
    uint32_t inSize, uint8_t *dataout, uint32_t *outSize);

/**
 * @ingroup  crypto
 * @brief ������ǩ��
 *
 * @par ����:
 * ������ǩ�����㷨�����ƣ�Ŀǰ֧��pkcs1v15��pkcs1v21�Լ�nopad
 *
 * @attention
 * @param algorithm     [IN]        RSA�㷨
 * @param key_blob      [IN]        ��Կ�����ݽṹ
 * @param srcData       [IN]        ��Ҫ���ܵ�����
 * @param srcLen        [IN]        ��Ҫ�������ݳ���
 * @param destData      [OUT]       ���ܺ������
 * @param destLen       [OUT]       ���ܺ�����ݳ���
 *
 * @retval #TEE_SUCCESS                 ��ȡ��Կ�ɹ�
 * @retval #TEE_ERROR_BAD_PARAMETERS    �����������
 * @retval #TEE_ERROR_GENERIC           ��ȡ��Կʧ��
 * @retval #TEE_ERROR_OUT_OF_MEMORY     �����ڴ�ʧ��
 * @retval #TEE_ERROR_NOT_SUPPORTED     �㷨��֧��
 *
 * @par ����:
 * @li crypto �ӽ���ģ��
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see
 * @since V100R005C00
*/
TEE_Result TEE_EXT_RSA_decrypt(TEE_CRYPTO_ALGORITHM_ID algorithm, uint8_t *key_blob,
        uint8_t *srcData, uint32_t srcLen, uint8_t *destData, uint32_t *destLen);

/**
 * @ingroup  TEE_TRUSTED_STORAGE_API
 * @brief �ڰ�ȫ��ɾ��ĳ���ļ���Ŀ¼
 *
 * @par ����:
 * �ڰ�ȫ��ɾ��ĳ���ļ���Ŀ¼
 *
 * @attention
 * �˽ӿڻὫ����Ŀ¼ɾ��������
 * @param path     [IN]        ��Ҫɾ�����ļ���Ŀ¼
 *
 * @retval
 *
 * @par ����:
 * @li tee_ext_api.h ��չAPIͷ�ļ�
 * @see
 * @since V100R005C00
*/
void TEE_EXT_rmDir(const char *path);

/**
 * @ingroup  TEE_HWI_IPC_MESSAGE
 * @brief Wait for registered messages from IRQs
*/
TEE_Result TEE_EXT_HwiMsgRegister(uint32_t hwi);

/**
 * @ingroup  TEE_HWI_IPC_MESSAGE
 * @brief Unregister to receive message for HWI number
 *
 * @param hwi     [IN]        IRQ number to unregister for
*/
TEE_Result TEE_EXT_HwiMsgDeregister(uint32_t hwi);

/**
 * @ingroup  TEE_HWI_IPC_MESSAGE
 * @brief Wait for registered messages from IRQs
*/
uint32_t TEE_EXT_HwiMsgWait();
/**
 * @ingroup  TEE_DEVICE_STATUS_CHECK
 * @brief check wheather device rooted 1:rooted, 0:unrooted
*/
bool TEE_EXT_IsDeviceRooted(void);
/**
 * @ingroup  TEE_DEVICE_VSIM SHAREMEM GET
 * @brief get vsim sharemem:return:TEE_SUCCESS success to get, TEE_ERROR_BAD_PARAMETERS params error, TEE_ERROR_GENERIC:map error
*/
TEE_Result TEE_EXT_GetVsimShareMem(uint32_t *addr, uint32_t *size);


/**
 * @ingroup  TEE_TA_CALLER_INDENTIFY
 * @brief  verify TA's caller's identify
 *
 * @par  TA can call this API to add caller's info,
 *       which is allowed to call this TA.
 *       this API is for CA in form of binary-excuteble file.
 *
 * @param ca_name     [IN]		CA caller's packagename
 * @param ca_uid      [IN]		CA caller's uid
 *
 * @retval
 *
 * @par dependence:
 * @li tee_ext_api.h
 * @see
 * @since V100R007C00
*/
TEE_Result AddCaller_CA_exec(char* ca_name, uint32_t ca_uid);

/**
 * @ingroup  TEE_TA_CALLER_INDENTIFY
 * @brief  verify TA's caller's identify
 *
 * @par  TA can call this API to add caller's info,
 *       which is allowed to call this TA.
 *       this API is for CA in form of APK.
 *
 * @param ca_name       [IN]		CA caller's packagename
 * @param modulus       [IN]		CA caller's modulus
 * @param pub_exponent  [IN]		CA caller's pub_exponent
 *
 * @retval
 *
 * @par dependence:
 * @li tee_ext_api.h
 * @see
 * @since V100R007C00
*/
TEE_Result AddCaller_CA_apk(char* ca_name, char *modulus, char *pub_exponent);

/**
 * @ingroup  TEE_TA_CALLER_INDENTIFY
 * @brief  verify TA's caller's identify
 *
 * @par  TA can call this API to add caller's info,
 *       which is allowed to call this TA.
 *       this API is for caller is a TA.
 *       And there is no uuid check with this TA.
 *
 * @retval
 *
 * @par dependence:
 * @li tee_ext_api.h
 * @see
 * @since V100R007C00
*/
TEE_Result AddCaller_TA_all(void);

#endif
