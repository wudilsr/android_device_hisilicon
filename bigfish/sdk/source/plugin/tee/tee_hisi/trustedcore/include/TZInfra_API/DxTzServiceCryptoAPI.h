/**
 * @file DxTzServiceCryptoAPI.h
 * @brief cryptographic API functions for the TEE service
 *
 * These functions must be implemented using the platform methodology and functionality.
 *
 */
#ifndef	__DXTZSERVICECRYPTOAPI_H__
#define	__DXTZSERVICECRYPTOAPI_H__


#include "DxTypes.h"
#include "DxTzCommon.h"
#include "DxTzServiceAPITypes.h"

#define DX_TZ_AES128_BLOCK_SIZE    16
#define DX_TZ_AES128_IV_SIZE       16


/**
 * The following Crypto API declared in file :
 *
 * Random generation
 * AES Create/Ternimate Context
 * AES CTR
 * AES CBC
 * AES ECB
 * SHA1
 * SHA256
 * MD5
 * HMAC SHA256
 */



//------------------------------------  Random generation -------------------------------------

/**
 * Assign the specified number of bytes in the buffer with random values.
 *
 * @param[in,out] buffer points destination.
 * @param[in] length specifies a number of bytes to be randomly assigned.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_RandomGenerate(DxUint8* buffer, DxUint32 length);






//------------------------------------  AES Create/Ternimate Context ----------------------------



/** Allocate context structure for further AES processing.
 *
 * @param[out] ctx	Processing structure handle
 *						(any required storage is allocated by this function).
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128_CreateContext(DxCipher_AES128_Context_t *ctx);

/** Free a context structure.
 *
 * @param[in,out] ctx	Processing context structure handle
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128_TerminateContext(DxCipher_AES128_Context_t* ctx);





//------------------------------------  CTR ----------------------------


/** Initialize context structure for AES128CTR processing.
 *
 * @param[out] ctx		Processing structure handle
 *						(any required storage is allocated by this function)
 * @param[in] internalCtx		Pointer to an internal AES context
 *						(previously created by DxTzService_AES128_CreateContext)
 * @param[in] pKey		Key to use in encryption/decryption
 * @param[in] key_len	Key length in bytes
 * @param[in] direction	Direction of processing operations to be used (encryption/decryption)
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128CTR_Init(DxCipher_AES128CTR_Context_t *ctx,
									DxCipher_AES128_Context_t internalCtx,
									const DxUint8 *pKey,
									DxUint32 key_len,
									EDxCipherDirection direction);


/** Decrypt a block of data using AES in CTR mode.
 *
 * The key for the decryption process is set in prior calls to DxTzService_AES128CTR_Init()
 *
 * @param[in,out] ctx		Decryption context handle
 * @param[in] pSrc			Source data to decrypt
 * @param[out] pDst			Buffer for output data
 * @param[in] dataSize		Size of data block
 * @param[inout] iv			value for the block counter - updated to iv value after operation
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128CTR_DecryptData(DxCipher_AES128CTR_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE]);

/** Encrypt a block of data using AES in CTR mode.
 *
 * The key for the encryption process is set in prior calls to DxTzService_AES128CTR_Init()
 *
 * @param[in,out] ctx		Encryption context handle
 * @param[in] pSrc			Source data to decrypt
 * @param[out] pDst			Buffer for output data
 * @param[in] dataSize		Size of data block
 * @param[inout] iv			value for the block counter - updated to iv value after operation
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */

DxStatus DxTzService_AES128CTR_EncryptData(DxCipher_AES128CTR_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE]);


DxStatus DxTzService_AES128CTR_DecryptDataEx(DxCipher_AES128CTR_Context_t ctx,
										   DxTzServiceSharedMemRef *pSrc,
										   DxUint32 srcOffset,
										   DxTzServiceSharedMemRef *pDst,
										   DxUint32 dstOffset,
										   DxUint32 dataSize,
    									   /*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE]);

DxStatus DxTzService_AES128CTR_EncryptDataEx(DxCipher_AES128CTR_Context_t ctx,
										   DxTzServiceSharedMemRef *pSrc,
										   DxUint32 srcOffset,
										   DxTzServiceSharedMemRef *pDst,
										   DxUint32 dstOffset,
										   DxUint32 dataSize,
											/*INOUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE]);



/** Free a context structure.
 *
 * @param[in,out] ctx	Processing context structure handle
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128CTR_Finish(DxCipher_AES128CTR_Context_t *ctx);







//------------------------------------  CBC ----------------------------



/** Initialize context structure for AES128CBC processing.
 *
 * @param[out] ctx		Processing structure handle
 *						(any required storage is allocated by this function)
 * @param[in] pKey		Key to use in encryption/decryption
 * @param[in] key_len	Key length in bytes
 * @param[in] direction	Direction of processing operations to be used (encryption/decryption)
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128CBC_Init(DxCipher_AES128CBC_Context_t *ctx,
									DxCipher_AES128_Context_t internalCtx,
									const DxUint8 *pKey,
									DxUint32 key_len,
									EDxCipherDirection direction);

/** Decrypt a block of data using AES in CBC mode.
 *
 * The key for the decryption process is set in prior calls to DxTzService_AES128CBC_Init()
 *
 * @param[in,out] ctx		Encryption context handle
 * @param[in] pSrc			Source data to encrypt
 * @param[out] pDst			Buffer for output data
 * @param[in] dataSize		Size of source data
 * @param[inout] iv			value for the block chaining - updated to iv value after operation
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128CBC_DecryptData(DxCipher_AES128CBC_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*IN OUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE]);

/** Encrypt a block of data using AES in CBC mode.
 *
 * The key for the decryption process is set in prior calls to DxTzService_AES128CBC_Init()
 *
 * @param[in,out] ctx		Encryption context handle
 * @param[in] pSrc			Source data to encrypt
 * @param[out] pDst			Buffer for output data
 * @param[in] dataSize		Size of data block
 * @param[inout] iv			value for the block chaining - updated to iv value after operation
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128CBC_EncryptData(DxCipher_AES128CBC_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize,
										   /*IN OUT*/ DxUint8 iv[DX_TZ_AES128_IV_SIZE]);


DxStatus DxTzService_AES128CBC_DecryptDataEx (DxCipher_AES128CBC_Context_t  context,
											  DxTzServiceSharedMemRef*      pSrc,
											  DxUint32                      srcOffset,
											  DxTzServiceSharedMemRef*      pDest,
											  DxUint32                      destOffset,
											  DxUint32                      dataSize,
											  /*INOUT*/ DxUint8       iv[DX_TZ_AES128_BLOCK_SIZE]);

DxStatus DxTzService_AES128CBC_EncryptDataEx (DxCipher_AES128CBC_Context_t  context,
											  DxTzServiceSharedMemRef*      pSrc,
											  DxUint32                      srcOffset,
											  DxTzServiceSharedMemRef*      pDest,
											  DxUint32                      destOffset,
											  DxUint32                      dataSize,
											  /*INOUT*/ DxUint8       iv[DX_TZ_AES128_BLOCK_SIZE]);

/** Free a context structure.
 *
 * @param[in,out] ctx	Processing context structure handle
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128CBC_Finish(DxCipher_AES128CBC_Context_t *ctx);




//------------------------------------  ECB  ----------------------------



/** Initialize context structure for AES128ECB processing.
 *
 * @param[out] ctx		Processing structure handle
 *						(any required storage is allocated by this function)
 * @param[in] internalCtx	Pointer to an internal AES context
 *							(previously created by DxTzService_AES128_CreateContext)
 * @param[in] pKey		Key to use in encryption/decryption
 * @param[in] key_len	Key length in bytes
 * @param[in] direction	Direction of processing operations to be used (encryption/decryption)
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128ECB_Init(DxCipher_AES128ECB_Context_t *ctx,
									DxCipher_AES128_Context_t internalCtx,
									const DxUint8 *pKey,
									DxUint32 key_len,
									EDxCipherDirection direction);

/** Decrypt a block of data using AES in ECB mode.
 *
 * The key for the decryption process is set in prior calls to DxTzService_AES128ECB_Init()
 *
 * @param[in,out] ctx		Decryption context handle
 * @param[in] pSrc			Source data to decrypt
 * @param[out] pDst			Buffer for output data
 * @param[in] dataSize		Size of data block
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128ECB_DecryptData(DxCipher_AES128ECB_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize);

/** Encrypt a block of data using AES in ECB mode.
 *
 * The key and IV for the encryption process are set in prior calls to DxTzService_AES128ECB_Init()
 *
 * @param[in,out] ctx		Encryption context handle
 * @param[in] pSrc			Source data to encrypt
 * @param[out] pDst			Buffer for output data
 * @param[in] dataSize		Size of data block
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128ECB_EncryptData(DxCipher_AES128ECB_Context_t ctx,
										   const void *pSrc,
										   void *pDst,
										   DxUint32 dataSize);

/** Free a context structure.
 *
 * @param[in,out] ctx	Processing context structure handle
 *
 * @return DX_SUCCESS on successful operation, any other value indicates a failure.
 */
DxStatus DxTzService_AES128ECB_Finish(DxCipher_AES128ECB_Context_t *ctx);



//------------------------------------  SHA1 ------------------------------------------


/**
 * Initializes the HASH machine for the SHA1 operation mode.
 *
 * @param[in,out] aContext - a pointer to the HASH context handle.
 * The parameter type is platform-dependent.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_SHA1Init(DxTzSHA1Context_t* aContext);

/**
 * Process a block of data via the HASH Hardware/Software
 * for the SHA1 operation mode.
 *
 * @param[in,out] aContext - HASH context handle.
 * The parameter type is platform-dependent.
 *
 * @param[in] aBuffer - The pointer to the buffer of the input data to the HASH.
 *
 * @param[in] aBufferLength - The size of the data to be hashed in bytes.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_SHA1Update(DxTzSHA1Context_t aContext, const DxUint8 *aBuffer, DxUint32 aBufferLength);

/**
 * Finalizes the hashing process of data block.
 *
 * @param[in,out] aContext - HASH context handle.
 * The parameter type is platform-dependent.
 *
 *  @param[in,out] aDigest a pointer to the target buffer where the
 *  HASH result stored in the context is loaded to.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_SHA1Final(DxTzSHA1Context_t aContext, DxUint8 aDigest[SHA1_SIGNATURE_SIZE]);

/**
 * Performs cleanup and free an allocated memory
 * in the hashing process.
 *
 * @param[in,out] aContext - HASH context handle.
 * The parameter type is platform-dependent.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_SHA1Terminate(DxTzSHA1Context_t aContext);



//------------------------------------  SHA256 -------------------------------------


/**
 * Initializes the HASH machine for the SHA256 operation mode.
 *
 * @param[in,out] aContext - a pointer to the HASH context buffer allocated by the user that
 * is used for the HASH machine operation.
 * The parameter type is platform-dependent.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_SHA256Init(DxTzSHA256Context_t* aContext);

/**
 * Process a block of data via the HASH Hardware/Software
 * for the SHA256 operation mode.
 *
 * @param[in,out] aContext - a pointer to the HASH context buffer allocated by the user that
 *	is used for the HASH machine operation.
 *	The parameter type is platform-dependent.
 * @param[in] aBuffer - The pointer to the buffer of the input data to the HASH.
 * @param[in] aBufferLength - The size of the data to be hashed in bytes.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_SHA256Update(DxTzSHA256Context_t aContext, const DxUint8 *aBuffer, DxUint32 aBufferLength);

/**
 * Finalizes the hashing process of data block.
 *
 * @param[in,out] aContext - a pointer to the HASH context buffer allocated by the user that
 *	is used for the HASH machine operation.
 *	The parameter type is platform-dependent.
 * @param[out] aDigest a pointer to the target buffer where the
 * HASH result stored in the context is loaded to.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_SHA256Final(DxTzSHA256Context_t aContext, DxUint8 aDigest[SHA256_SIGNATURE_SIZE]);

/**
 * Performs cleanup and free an allocated memory
 *	in the hashing process.
 *
 * @param[in] aContext - a pointer to the HASH context buffer allocated by the user that
 *	is used for the HASH machine operation.
 *	The parameter type is platform-dependent.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 */
DxStatus DxTzService_SHA256Terminate(DxTzSHA256Context_t aContext);





//------------------------------------  MD5 -------------------------------------



/**
 * Initializes the HASH machine for the MD5 operation mode.
 *
 * @param[in,out] aContext - a pointer to the HASH context buffer allocated by the user that
 * is used for the HASH machine operation.
 * The parameter type is platform-dependent.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_MD5Init(DxTzMD5Context_t* aContext);

/**
 * Process a block of data via the HASH Hardware/Software
 * for the MD5 operation mode.
 *
 * @param[in,out] aContext - a pointer to the HASH context buffer allocated by the user that
 * is used for the HASH machine operation.
 * The parameter type is platform-dependent.
 *
 * @param[in] aBuffer - The pointer to the buffer of the input data to the HASH.
 *
 * @param[in] aBufferLength - The size of the data to be hashed in bytes.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_MD5Update(DxTzMD5Context_t aContext, const DxUint8 *aBuffer, DxUint32 aBufferLength);

/**
 * Finalizes the hashing process of data block.
 *
 * @param[in,out] aContext - a pointer to the HASH context buffer allocated by the user that
 * is used for the HASH machine operation.
 * The parameter type is platform-dependent.
 *
 *  @param[in,out] aDigest a pointer to the target buffer where the
 *  HASH result stored in the context is loaded to.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_MD5Final(DxTzMD5Context_t aContext, DxUint8 aDigest[MD5_SIGNATURE_SIZE]);

/**
 * Performs cleanup and free an allocated memory
 * in the hashing process.
 *
 * @param[in,out] aContext - a pointer to the HASH context buffer allocated by the user that
 * is used for the HASH machine operation.
 * The parameter type is platform-dependent.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_MD5Terminate(DxTzMD5Context_t aContext);




//------------------------------------  HMAC SHA256 -------------------------------------

/**
 * Initializes the HMAC machine for the SHA256 operation mode.
 *
 * @param[in,out] aContext - a pointer to the HASH context buffer allocated by the user that
 * is used for the HASH machine operation.
 * The parameter type is platform-dependent.
 * @param[in] pKey - The pointer to the structure containing key details.
 * @param[in] key_len - Key length in bytes
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_HMAC_SHA256Init(DxTzHMAC_SHA256Context_t *context,
								 const DxUint8 *pKey,
								 DxUint32 key_len);

/**
 * Process a block of data via the HMAC Hardware/Software
 * for the SHA256 operation mode.
 *
 * @param[in,out] context - a pointer to the HMAC context buffer allocated by the user that
 * is used for the HMAC machine operation.
 * The parameter type is platform-dependent.
 * @param[in] data - The pointer to the buffer of the input data to the HMAC.
 * @param[in] dataLength - The size of the data to be hashed in bytes.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_HMAC_SHA256Update(DxTzHMAC_SHA256Context_t context,
								   const DxUint8 *data,
								   DxUint32 datLength);

/**
 * Finalizes the HMAC process of data block.
 *
 * @param[in,out] context - a pointer to the HMAC context buffer allocated by the user that
 *	is used for the HMAC machine operation.
 *	The parameter type is platform-dependent.
 * @param[out] aDigest a pointer to the target buffer where the
 * HASH result stored in the context is loaded to.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 * any other value indicates a failure.
 */
DxStatus DxTzService_HMAC_SHA256Final(DxTzHMAC_SHA256Context_t context,
								  DxUint8 aDigest[SHA256_SIGNATURE_SIZE]);

/**
 * Performs cleanup and free an allocated memory
 *	in the hashing process.
 *
 * @param[in] context - a pointer to the HMAC context buffer allocated by the user that
 *	is used for the HMAC machine operation.
 *	The parameter type is platform-dependent.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
 */
DxStatus DxTzService_HMAC_SHA256Terminate(DxTzHMAC_SHA256Context_t context);






//------------------------------------  RSA -------------------------------------






/**
 * Decrypt data with using RSAES-OAEP Encryption scheme.
 *
 * The mask generation function used in MGF1 which uses the specified underlying hash function.
 *
 * @param [in] privKey_ptr points an instance of structure containing the private key details.
 * @param [in] hashFunc is the underlying hash function.
 * @param[in] DataIn_ptr - A pointer to the data to decrypt.
 * @param[in] DataInSize - The size, in bytes, of the data to decrypt.
 * @param[out] Output_ptr - Pointer to the decrypted data,
 *	the buffer must be at least of the public key modulus size, in bytes.
 * @param[out] OutputSize - Size of data Output_ptr points to.
 *
 * @return DX_SUCCESS  if operation has been successfully completed and the data is decrypted.
 * @return DX_FAILURE if operation failed.
*/
DxStatus DxTzService_RSA_OAEP_DecryptData(DxTzService_RSA_PrivKey_s *privKey_ptr,
									  EDxTzGenericRsaHashOpMode_t	hashFunc,
									  DxByte	*DataIn_ptr,
									  DxUint16	DataInSize,
									  DxByte	*Output_ptr,
									  DxUint16  *OutputSize);


/**
 * Encrypt data with using RSAES-OAEP Encryption scheme.
 *
 * The mask generation function used in MGF1 which uses the specified underlying hash function.
 *
 * @param [in] pubKey_ptr points an instance of structure containing the public key details.
 * @param [in] hashFunc is the underlying hash function.
 * @param[in] DataIn_ptr - A pointer to the data to encrypt.
 * @param[in] DataInSize - The size, in bytes, of the data to encrypt.
 * @param[out] Output_ptr - Pointer to the encrypted data,
 *	the buffer must be at least of the public key modulus size, in bytes.
 *
 * @return DX_SUCCESS  if operation has been successfully completed and the data is encrypted.
 * @return DX_FAILURE if operation failed.
*/
DxStatus DxTzService_RSA_OAEP_EncryptData(DxTzService_RSA_PubKey_s *pubKey_ptr,
									  EDxTzGenericRsaHashOpMode_t	hashFunc,
									  DxByte	*DataIn_ptr,
									  DxUint16	DataInSize,
									  DxByte	*Output_ptr);







/**
 * Decrypt data with using the RSAES-PKCS1v15 algorithm.
 *
 * @param [in] privKey_ptr points an instance of structure containing the private key details.
 * @param[in] DataIn_ptr - A pointer to the data to decrypt.
 * @param[in] DataInSize - The size, in bytes, of the data to decrypt.
 * @param[out] Output_ptr - Pointer to the decrypted data,
 *	the buffer must be at least of the public key modulus size, in bytes.
 *
 * @return DX_SUCCESS  if operation has been successfully completed and the data is decrypted.
 * @return DX_FAILURE if operation failed.
*/
DxStatus DxTzService_RSA_PKCS1v15_DecryptData(DxTzService_RSA_PrivKey_s *privKey_ptr,
									  DxByte						*DataIn_ptr,
									  DxUint16						DataInSize,
									  DxByte						*Output_ptr,
									  DxUint16						*OutputSize);

/**
 * Encrypt data with using the RSAES-PKCS1v15 algorithm.
 *
 * @param [in] pubKey_ptr points an instance of structure containing the public key details.
 * @param[in] DataIn_ptr - A pointer to the data to encrypt.
 * @param[in] DataInSize - The size, in bytes, of the data to encrypt.
 * @param[out] Output_ptr - Pointer to the encrypted data,
 *	the buffer must be at least of the public key modulus size, in bytes.
 *
 * @return DX_SUCCESS  if operation has been successfully completed and the data is encrypted.
 * @return DX_FAILURE if operation failed.
*/
DxStatus DxTzService_RSA_PKCS1v15_EncryptData(DxTzService_RSA_PubKey_s *pubKey_ptr,
									  DxByte						*DataIn_ptr,
									  DxUint16						DataInSize,
									  DxByte						*Output_ptr);


/**
 * Verify the data signature with using the PKCS1v21 Verify algorithm.
 *
 * A cryptographic signature calculated over the passed data.
 *
 * @param [in] pubKey_ptr points an instance of structure containing the public key details.
 * @param [in] hashFunc is the underlying hash function.
 * @param [in] saltLen  - The Length of the Salt buffer.
 * @param[in] DataIn_ptr - A pointer to the data whose signature is to be verified.
 * @param[in] DataInSize - The size, in bytes, of the data whose signature is to be verified.
 * @param[in] Sig_ptr - A pointer to the signature to be verified.
 *
 * @return DX_SUCCESS  if operation has been successfully completed and the data is verified.
 * @return DX_FAILURE if operation failed.
*/
DxStatus DxTzService_RSA_PSS_VerifyDataSignature(DxTzService_RSA_PubKey_s *pubKey_ptr,
										 EDxTzGenericRsaHashOpMode_t	hashFunc,
										 DxUint16						saltLen,
										 DxByte							*DataIn_ptr,
										 DxUint32						DataInSize,
										 DxByte							*Sig_ptr);

/**
* Verify the data signature with using the RSASSA-PKCS1v15 Verify algorithm.
 *
 * A cryptographic signature calculated over the passed data.
 *
 * @param [in] pubKey_ptr points an instance of structure containing the public key details.
 * @param [in] hashFunc is the underlying hash function.
 * @param[in] DataIn_ptr - A pointer to the data whose signature is to be verified.
 * @param[in] DataInSize - The size, in bytes, of the data whose signature is to be verified.
 * @param[in] Sig_ptr - A pointer to the signature to be verified.
 *
 * @return DX_SUCCESS  if operation has been successfully completed and the data is verified.
 * @return DX_FAILURE if operation failed.
*/
DxStatus DxTzService_RSA_PKCS1v15_VerifyDataSignature(DxTzService_RSA_PubKey_s *pubKey_ptr,
										 EDxTzGenericRsaHashOpMode_t	hashFunc,
										 DxByte							*DataIn_ptr,
										 DxUint32						DataInSize,
										 DxByte							*Sig_ptr);

#endif
