/**
 * @file DxTzServiceAPITypes.h
 * @brief Type definitions for TEE service
 *
 */
#ifndef	__DXTZSERVICEAPITYPES_H__
#define	__DXTZSERVICEAPITYPES_H__


#include "DxTypes.h"


/** Size in bytes of vector holding the IV, Nonce, and Counter [passed as a parameter to the DxTzService_IsAudioPacket() API]
 */
#define IV_NONCE_COUNTER_LENGTH			16


#ifndef DECLARE_OPAQUE
#define DECLARE_OPAQUE(name)  struct name##__ { DxInt unused; }; \
                    typedef const struct name##__ * name;
#endif

/** Digest result size in bytes in MD5 hash operation.
 */
#define MD5_SIGNATURE_SIZE		16

/** Digest result size in bytes in SHA1 hash operation.
 */
#define SHA1_SIGNATURE_SIZE		20


/** Digest result size in bytes in SHA256 hash operation.
 */
#define SHA256_SIGNATURE_SIZE		32


/** Direction of cipher operations.
 */
typedef enum { DXCIPHER_ENC, DXCIPHER_DEC } EDxCipherDirection;

/** Context handle for use in AES-<mode> processing.
 */
typedef struct DxCipher_AES128_Context_s*   DxCipher_AES128_Context_t;

DECLARE_OPAQUE(DxCipher_AES128CTR_Context_t)
DECLARE_OPAQUE(DxCipher_AES128ECB_Context_t)
DECLARE_OPAQUE(DxCipher_AES128CBC_Context_t)

/** Context handle for use in MD5 processing.
 */
typedef struct DxTzMD5Context_s *DxTzMD5Context_t;

/** Context handle for use in SHA1 processing.
 */
typedef struct DxTzSHA1Context_s *DxTzSHA1Context_t;

/** Context handle for use in SHA256 processing.
 */
typedef struct DxTzSHA256Context_s *DxTzSHA256Context_t;

/** Context handle for use in HMAC_SHA256 processing.
 */
typedef struct DxTzHMAC_SHA256Context_s *DxTzHMAC_SHA256Context_t;

/** Context handle for use in RNG processing.
 */
typedef struct DxTzRNGContext_s *DxTzRNGContext_t;

/** Timestamp for use in timer count operations.
 */
typedef DxUint32 DxTzTimestamp_t;

/** Defines the enumeration for Cipher Algorithm
 */
typedef enum
{
	DX_TZ_CIPHER_ALG_NONE 		= 0,

	DX_TZ_CIPHER_ALG_AES128CTR 	= 1,
	DX_TZ_CIPHER_ALG_AES128CBC 	= 2,

	// Must be last
	DX_TZ_CIPHER_ALG_NOT_SUPPORTED

} EDxTzCipherAlgorithm_t;

/** Defines the enumeration for RSA Key Types
 */
typedef enum
{
	DX_TZ_RSA_PUBLIC_KEY  = 0,
	DX_TZ_RSA_PRIVATE_KEY = 1,
	DX_TZ_RSA_PRIVATE_KEY_CRT = 2
} EDxTzRSA_key_type_t;

/**
 * Defines the structure containing RSA key details
*/
typedef struct {
	EDxTzRSA_key_type_t	type;
	DxInt		bitLength;
	DxByte		*Exp;
	DxUint16	ExpSize;
	DxByte		*Modulus;
	DxUint16	ModulusSize;
	DxByte		*privExp;
	DxUint16	privExpSize;
	DxByte		*P;
	DxUint16	PSize;
	DxByte		*Q;
	DxUint16	QSize;
	DxByte		*Dp;
	DxUint16	DpSize;
	DxByte		*Dq;
	DxUint16	DqSize;
	DxByte		*QInt;
	DxUint16	QIntSize;
} DxTzService_RSA_PrivKey_s;

/**
 * Defines the structure containing public key details.
*/
typedef struct {
	EDxTzRSA_key_type_t	type;
	DxInt		bitLength;
	DxByte		*Exp;
	DxUint16	ExpSize;
	DxByte		*Modulus;
	DxUint16	ModulusSize;
} DxTzService_RSA_PubKey_s;

/** Defines the enum for the HASH operation mode.
 * It is synchronized to the CRYS_RSA_HASH_OpMode_t,
 * in order to simplify its usage.
 */
typedef enum
{
	DX_TZ_RSA_HASH_MD5_mode  = 0,
	DX_TZ_RSA_HASH_SHA1_mode = 1,
	DX_TZ_RSA_HASH_SHA256_mode = 3
} EDxTzGenericRsaHashOpMode_t;


/**
 * Defines the enum for a connection status
 * for APIs in a TEE.
 */
typedef enum
{
	DX_TZ_CONNECTION_NOT_CONNECTED,
	DX_TZ_CONNECTION_CONNECTED,
	DX_TZ_CONNECTION_STATUS_UNKNOWN,
	DX_TZ_CONNECTION_STATUS_UNSUPPORTED
} EDxTzConnectionStatus_t;


/**
 * Defines the enum for a status of HDMI and HDCP1
 * for APIs in a TEE.
 */
typedef enum
{
	DX_TZ_HDMI_HDCP1_HDCP1_AUTHENTICATED	= 1,		// HDMI with HDCP1 authenticated
	DX_TZ_HDMI_HDCP1_HDCP1_DISABLED_OR_NOT_CONNECTED,	// HDMI disabled or not connected

	DX_TZ_HDMI_HDCP1_HDCP1_NOT_AUTH,					// HDMI cable connected, but HDCP1 is not authenticated
	DX_TZ_HDMI_HDCP1_HDCP1_FAILURE,						// HDMI cable IS NOT connected, but HDCP1 IS authenticated (seems like hack case)

	DX_TZ_HDMI_HDCP1_STATUS_UNKNOWN,					// in case of status function failure

	DX_TZ_HDMI_HDCP1_NOT_SUPPORTED,						// Not supported (platform does not support HDMI/HDCP1 status reading)

} EDxTz_HDMI_HDCP1_Status_t;






#endif
