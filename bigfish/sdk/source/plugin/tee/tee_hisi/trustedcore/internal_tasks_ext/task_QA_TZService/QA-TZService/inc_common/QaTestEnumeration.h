#ifndef QaTestEnumeration_h__
#define QaTestEnumeration_h__

typedef enum{
    eAES_DIRECTION_ENC,
    eAES_DIRECTION_DEC,
} EAES_DIRECTION;

typedef enum {
    eAES_MODE_CBC,
    eAES_MODE_CTR,
    eAES_MODE_ECB
}EAES_MODE;

enum HashFuncType{
    eSHA_TYPE_1,
    eSHA_TYPE_256,
	eMD5_TYPE
};

/* The following enum represents index of appropriate callback in callback data array*/
typedef enum
{
    QA_CREATE_CONTEXT_IDX	= 0, /* don't change this */
    QA_OPEN_SESSION_IDX,
    QA_INVOKE_COMMAND_IDX,
    QA_CLOSE_SESSION_IDX,
    QA_DESTROY_CONTEXT_IDX,
    QA_MAX_CALLBACK_IDX,

} EQaClbSecuenceIndex;



/* The following enum represents value of appropriate callback type in callback data array that must be
	after runing callback sequence */
typedef enum
{
    QA_CREATE_CONTEXT_VALUE = QA_CREATE_CONTEXT_IDX+1,
    QA_OPEN_SESSION_VALUE   = QA_OPEN_SESSION_IDX+1,
    QA_INVOKE_COMMAND_VALUE = QA_INVOKE_COMMAND_IDX+1,
    QA_CLOSE_SESSION_VALUE	= QA_CLOSE_SESSION_IDX+1,
    QA_DESTROY_CONTEXT_VALUE= QA_DESTROY_CONTEXT_IDX+1

} EQaClbSecuenceValue;


#define SEQUENTIAL_NUMBER_INIT_VALUE QA_CREATE_CONTEXT_VALUE




/**
 * Defines the enum for a status of HDMI and HDCP1
 * for APIs in a TEE.
 * PAY TTENTION : must be consistent with DxTzServiceAPITypes.h::EDxTz_HDMIHDCP1_Status_t.
 */
typedef enum
{
	TST_HDMIHDCP1_HDCP1_AUTHENTICATED	= 1,		// HDMI with HDCP1 authenticated
	TST_HDMIHDCP1_HDCP1_DISABLED_OR_NOT_CONNECTED,	// HDMI disabled or not connected
	TST_HDMIHDCP1_HDCP1_FAILURE,					// HDCP1 failure (HDCP1 authentication failure or we are hacked)
	TST_HDMIHDCP1_STATUS_UNKNOWN,					// in case of status function failure
	TST_HDMIHDCP1_NOT_SUPPORTED,					// Not supported (platform does not support HDMI/HDCP1 status reading)

} ETst_HDMIHDCP1_Status;




typedef enum {
	/*0xF000*/ QA_GET_ERR_MSG = 0x0100,

	/*0xF001*/ QA_TST_LOOPBACK,

	/*0xF002*/ QA_TST_PARAM_CHECK_NONE,
	/*0xF003*/ QA_TST_PARAM_CHECK_VALUE_IN,
	/*0xF004*/ QA_TST_PARAM_CHECK_VALUE_OUT,
	/*0xF005*/ QA_TST_PARAM_CHECK_VALUE_INOUT,
	/*0xF006*/ QA_TST_PARAM_CHECK_MEMREF_IN,
	/*0xF007*/ QA_TST_PARAM_CHECK_MEMREF_OUT,
	/*0xF008*/ QA_TST_PARAM_CHECK_MEMREF_INOUT,
    /*0xF009*/ QA_TST_PARAM_CHECK_MEMREF_INOUT_REVERSE,
    /*0xF00A*/ QA_TST_PARAM_CHECK_UPDATE_BUFFER_SIZE,
	/*0xF00B*/ QA_TST_PARAM_CHECK_SHARED_MEMREF_INOUT,

	/*0xF00C*/ QA_TST_CALLBACK_SEQUENCE_INVOKE_COMMAND,
	/*0xF00D*/ QA_TST_CALLBACK_SEQUENCE_READ_FROM_SFS,
	/*0cFOOE*/ QA_TST_CALLBACK_SEQUENCE_DELETE_FROM_SFS,

	/*0xF010*/ QA_TST_MEMORY_ALLOC = 0x0110,
	/*0xF011*/ QA_TST_MEMORY_REALLOC,
	/*0xF012*/ QA_TST_MEMORY_SET,
	/*0xF013*/ QA_TST_MEMORY_COPY,
	/*0xF014*/ QA_TST_MEMORY_REVERSE_COPY,
	/*0xF015*/ QA_TST_MEMORY_COMPARE,
	/*0xF016*/ QA_TST_IS_AUDIO_PACKET_API,
	/*0xF017*/ QA_TST_HDMI_STATUS_API,


	/*0xF020*/ QA_TST_CRYPTO_SHA1  = 0x0120,
	/*0xF021*/ QA_TST_CRYPTO_SHA256,
	/*0xF022*/ QA_TST_CRYPTO_MD5,
	/*0xF023*/ QA_TST_CRYPTO_HMAC_SHA256,
	/*0xF022*/ QA_TST_CRYPTO_AES128_ECB_DECRIPT_ALIGNED,
	/*0xF023*/ QA_TST_CRYPTO_AES128_CBC_DECRIPT_ALIGNED,
	/*0xF024*/ QA_TST_CRYPTO_AES128_CTR_DECRIPT_ALIGNED,
	/*0xF025*/ QA_TST_CRYPTO_AES128_ECB_DECRIPT_NOT_ALIGNED,
	/*0xF026*/ QA_TST_CRYPTO_AES128_CBC_DECRIPT_NOT_ALIGNED,
	/*0xF027*/ QA_TST_CRYPTO_AES128_CTR_DECRIPT_NOT_ALIGNED,
	/*0xF028*/ QA_TST_CRYPTO_AES128_ECB_ENCRIPT_ALIGNED,
	/*0xF029*/ QA_TST_CRYPTO_AES128_CBC_ENCRIPT_ALIGNED,
	/*0xF02A*/ QA_TST_CRYPTO_AES128_CTR_ENCRIPT_ALIGNED,
	/*0xF02B*/ QA_TST_CRYPTO_AES128_ECB_ENCRIPT_NOT_ALIGNED,
	/*0xF02C*/ QA_TST_CRYPTO_AES128_CBC_ENCRIPT_NOT_ALIGNED,
	/*0xF02D*/ QA_TST_CRYPTO_AES128_CTR_ENCRIPT_NOT_ALIGNED,
    /*0xF02E*/ QA_TST_CRYPTO_AES128_OPERATION,
	/*0xF02F*/ QA_TST_CRYPTO_OAEP_RSA_OAEP_ENCRYPT,
	/*0xF030*/ QA_TST_CRYPTO_OAEP_RSA_OAEP_DECRYPT,
	/*0xF031*/ QA_TST_CRYPTO_PKCS1_V1_5_RSA_ENCRYPT,
	/*0xF032*/ QA_TST_CRYPTO_PKCS1_V1_5_RSA_DECRYPT,
	/*0xF033*/ QA_TST_CRYPTO_PSS_RSA_SIGN_VERIFY,
	/*0xF034*/ QA_TST_CRYPTO_PKCS1_V1_5_RSA_SIGN_VERIFY,
	/*0xF035*/ QA_TST_CRYPTO_RANDOM_NUM_GEN,


    /*0xF040*/ QA_TST_SECURE_STORAGE_READ_WRITE_TEST = 0x0140,
	/*0xF041*/ QA_TST_SECURE_STORAGE_UPDATE_BUFF_LEN_TEST,
	/*0xF042*/ QA_TST_SECURE_STORAGE_DELETE_TEST,
	/*0xF043*/ QA_TST_SECURE_STORAGE_CREATE_NEW_TEST,
	/*0xF044*/ QA_TST_SECURE_STORAGE_GET_SIZE_TEST,
	/*0xF045*/ QA_TST_CREATE_DEVICE_KEY,
	/*0xF046*/ QA_TST_GET_UNIQUE_DEVICE_ID,
	/*0xF047*/ QA_TST_IS_DEVICE_ROOTED,
	/*0xF048*/ QA_TST_IS_BOOT_LOADER_UNLOCK,
	/*0xF049*/ QA_TST_GET_SET_HDCP2_CONNECTION_STATUS,
	/*0xF04A*/ QA_TST_SECURE_CONTENT_PATH,
	/*0xF04B*/ QA_TST_IS_SECURE_NON_SECURE_CONTENT_MEMORY,

	/*0xF04C*/ QA_TST_SFS_SW,


	/*0xF060*/ QA_TST_MEMORY_COPY_MEM_TO_EX = 0x0160,
	/*0xF061*/ QA_TST_MEMORY_COPY_EX_TO_MEM,
	/*0xF062*/ QA_TST_MEMORY_COPY_EX_TO_EX,
	/*0xF063*/ QA_TST_MEMORY_COMPARE_MEM_TO_EX,
	/*0xF064*/ QA_TST_MEMORY_COMPARE_EX_TO_MEM,
	/*0xF065*/ QA_TST_MEMORY_COMPARE_EX_TO_EX,

	/*0xF066*/ QA_TST_MEMORY_SET_EX,


	/*0xF067*/ QA_TST_AES_CTR_MEM_TO_EX,
	/*0xF068*/ QA_TST_AES_CTR_EX_TO_MEM,
	/*0xF069*/ QA_TST_AES_CTR_EX_TO_EX,

	/*0xF067*/ QA_TST_AES_CBC_MEM_TO_EX,
	/*0xF068*/ QA_TST_AES_CBC_EX_TO_MEM,
	/*0xF069*/ QA_TST_AES_CBC_EX_TO_EX,

	/*0xF06A*/ QA_TST_AES_BLOCK_CIPHER_INIT,
	/*0xF06B*/ QA_TST_AES_BLOCK_CIPHER_FINISH,

	/*0xF06C*/ QA_TST_NON_CONTIGUOUS_BUFFERS_CTR,
	/*0xF06D*/ QA_TST_NON_CONTIGUOUS_BUFFERS_CBC

} EQaTstEnum;

#endif // QaTestEnumeration_h__