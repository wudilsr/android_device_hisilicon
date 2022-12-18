#ifndef QaTestFuncDeclaration_h__
#define QaTestFuncDeclaration_h__

#include "DxTypes.h"
#include "DxTzCommon.h"
#include "DxTzServiceAPITypes.h"
#include "QaErrorMessage.h"
#include "QaTestEnumeration.h"

DxStatus getQaError(QaErrorMessage* outQaErrMsg);

/**
* @brief test value in parameters - called from CTstParamCheckInValue test
*
* Test Steps:
* 1. receive 8 DX_TZ_PARAM_TYPE_VALUE_INPUT arguments form HLOS
* 1. insure that all the difference between parameters is 1
* 1. increment all parameters by 1
*/
DxStatus paramValueIn(DxTzServiceValue *param1, DxTzServiceValue *param2, DxTzServiceValue *param3, DxTzServiceValue *param4);


/**
* @brief test value inout parameters - called from CTstParamCheckInOutValue test
*
* Test Steps:
* 1. receive 8 DX_TZ_PARAM_TYPE_VALUE_INOUT arguments form HLOS
* 1. insure that all the difference between parameters is 1
* 1. increment all parameters by 1
*/
DxStatus paramValueInOut(DxTzServiceValue *param1, DxTzServiceValue *param2, DxTzServiceValue *param3, DxTzServiceValue *param4);

/**
* @brief test value inout parameters - called from CTstParamCheckOutValue test
*
* Test Steps:
* 1. receive 8 DX_TZ_PARAM_TYPE_VALUE_OUTPUT arguments form HLOS
* 1. fill in all the parameters with values 1000->1007 accordingly
*/
DxStatus paramValueOut(DxTzServiceValue *param1, DxTzServiceValue *param2, DxTzServiceValue *param3, DxTzServiceValue *param4);

/**
* @brief test IN memory reference arguments passed from HLOS - called from CTstParamCheckInMemRef
*
* Test Steps:
* 1. receive 4 DX_TZ_PARAM_TYPE_MEMREF_INPUT arguments form HLOS
* 1. verify that buffers contain expected data
* 1. modify data contained in received buffers
*/
DxStatus paramMemRefIn(DxTzServiceMemRef *param1, DxTzServiceMemRef *param2, DxTzServiceMemRef *param3, DxTzServiceMemRef *param4);

/**
* @brief test IN memory reference arguments passed from HLOS - called from CTstParamCheckInOutMemRef
*
* Test Steps:
* 1. receive 4 DX_TZ_PARAM_TYPE_MEMREF_INOUT or DX_TZ_PARAM_TYPE_PHYS_MEMREF_INPUT arguments form HLOS
* 1. verify that buffers contain expected data
* 1. modify data contained in received buffers
*/
DxStatus paramMemRefInOut(DxTzServiceMemRef *param1, DxTzServiceMemRef *param2, DxTzServiceMemRef *param3, DxTzServiceMemRef *param4, DxUint32 nParamTypes);


/**
* @brief Validates input memory reference arguments passed from HLOS - check if existing arguments has
*	appropriate content and length, after that input argument changed in predefined way.
*
* Test Steps:
* 1. receive 4 DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT or NONE arguments form HLOS
* 2. verify that buffers contain expected data
* 3. modify data contained in received buffers
*/
DxStatus paramSharedMemRefInOut( DxTzServiceParameter pParams[], DxUint32 nParamTypes);





/**
* @brief test IN memory reference arguments passed from HLOS - called from CTstParamCheckOutMemRef
*
* Test Steps:
* 1. receive 4 DX_TZ_PARAM_TYPE_MEMREF_OUTPUT arguments form HLOS
* 1. verify that buffers contain expected data
* 1. modify data contained in received buffers
*/
DxStatus paramMemRefOut(DxTzServiceMemRef *param1, DxTzServiceMemRef *param2, DxTzServiceMemRef *param3, DxTzServiceMemRef *param4);


/**
* @brief reverses data in input arguments
*
* Test Steps:
* 1. receive 1 DX_TZ_PARAM_TYPE_SHARED_MEMREF_OUTPUT arguments form HLOS
* 2. verify that buffers contain expected data
* 3. modify data contained in received buffers
*/
DxStatus paramMemRefInOutReverse(DxTzServiceSharedMemRef *sharedMemRefParam);


/**
* @brief changed size of buffers and reverses data in first argument
*
* Test Steps:
* 1. receive 3 input arguments form HLOS
* 2. verify that buffers contain expected data
* 3. modify data contained in received buffers
*/
DxStatus paramBufferSizeUpdate(DxTzServiceSharedMemRef *sharedMemRefParam, DxTzServiceMemRef *param2, DxTzServiceMemRef *param3);


/**
* @brief test memory allocation and release APIs - called by CTstMemoryAlloc
*
* Perform large number of memory alloc and free iterations (the exact number of iterations is set by HLOS).
* Allocate (2^i)<MAX_SIZE and (2^i)+3<MAX_SIZE memory blocks, where MAX_SIZE specifed by HLOS
*/
DxStatus memoryAlloc(DxUint32 maxMemorySize);


/**
* @brief test memory allocation and release APIs - called by CTstMemoryAlloc
*
* Perform large number of memory alloc realloc and free iterations (the exact number of iterations is set by HLOS).
* Allocate (2^i)<MAX_SIZE and (2^i)+3<MAX_SIZE memory blocks, where MAX_SIZE specifed by HLOS
*
* Test Steps:
* 1. loop start
* 1. allocate buffer
* 1. fill in the buffer with series of numbers
* 1. reallocate the buffer to greater size
* 1. insure that original series of numbers is not changed
* 1. loop end
* 1. loop start
* 1. allocate buffer
* 1. fill in the buffer with series of numbers
* 1. reallocate the buffer to smaller size
* 1. insure that remaining part original series of numbers is not changed
* 1. loop end

*/
DxStatus memoryReAlloc( DxUint32 maxMemorySize);
DxStatus memorySet(DxUint32 maxMemorySize);
DxStatus memoryCopy(DxUint32 maxMemorySize);
DxStatus memoryReverseCopy(DxUint32 maxMemorySize);
DxStatus memoryCompare(DxUint32 maxMemorySize);

//////////////////////////////////////////////
//Hash functions
//////////////////////////////////////////////
DxStatus cryptoSha1(const DxUint8 *aBuffer, DxUint32 aBufferLength, DxUint8 * aDigest, DxBool isBufferShallDivided);
DxStatus cryptoSha256(const DxUint8 *aBuffer, DxUint32 aBufferLength, DxUint8 * aDigest, DxBool isBufferShallDivided);
DxStatus cryptoMD5(const DxUint8 *aBuffer, DxUint32 aBufferLength, DxUint8 * aDigest, DxBool isBufferShallDivided);

//////////////////////////////////////////////
//HMAC functions
//////////////////////////////////////////////
DxStatus cryptoHmacSha256(const DxUint8 *aBuffer, DxUint32 aBufferLength, const DxUint8 *aKey, DxUint32 aKeyLength, DxUint8 * aDigest, DxBool isBufferShallDivided);
//////////////////////////////////////////////
//AES128CTR
//////////////////////////////////////////////
DxStatus cryptoAES128Ecb(const DxUint8 *aBuffer,
                         DxUint32 aBufferLength,
                         DxUint8 * aOutputBuff,
                         DxUint32 aOutputBufferLength,
                         DxUint8 * aKey,
                         DxUint32 aKeyLen,
                         EDxCipherDirection direction,
                         DxBool isAlinged);
DxStatus cryptoAES128Ctr(const DxUint8 *aBuffer,
                         DxUint32 aBufferLength,
                         DxUint8 * aOutputBuff,
                         DxUint32 aOutputBufferLength,
                         DxUint8 * aKey,
                         DxUint32 aKeyLen,
                         DxUint8 * aIv,
                         DxUint32 aIvLen,
                         EDxCipherDirection direction,
                         DxBool isAlinged);
DxStatus cryptoAES128Cbc(const DxUint8 *aBuffer,
                         DxUint32 aBufferLength,
                         DxUint8 * aOutputBuff,
                         DxUint32 aOutputBufferLength,
                         DxUint8 * aKey,
                         DxUint32 aKeyLen,
                         DxUint8 * aIv,
                         DxUint32 aIvLen,
                         EDxCipherDirection direction,
                         DxBool isAlinged);
DxStatus cryptoAES128Operation(DxTzServiceSharedMemRef *clearBuffer, DxTzServiceSharedMemRef *encBuffer, DxTzServiceMemRef *key, DxUint32 aesMode, DxUint32 aesDirection);

DxStatus cryptoRSA_encryptionTest(DxUint32 commandID, DxTzServiceParameter *params, DxUint32 paramTypes);
DxStatus cryptoRSA_signVerify(DxUint32 commandID, DxTzServiceParameter *params, DxUint32 nParamTypes);

//////////////////////////////////////////////
// For use of Random Generation Test
// Calling DxTzService_RandomGenerate() function to fill in a buffer with random values.
// The test will later check how good the randomization is.
//
// void *pBuf
// DxUint32 uiSize
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus cryptoRandomGenerate(void *pBuf, DxUint32 uiSize);


//////////////////////////////////////////////
// Read Secure Storage test
// Tries to create files and validates file's creation
//
// const DxChar* fileName
// DxUint fileLength
// DxStatus expectedResult
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus secureStorage_ReadWriteTest(const DxChar* fileName, DxUint fileLength, DxStatus expectedResult);

//////////////////////////////////////////////
// Update read buffer length test
// Receives file name and buffer
// reads file in to buffer and validates that buffer length after file read updated appropriately.
//
// const DxChar* fileName
// DxUint fileLength
// DxStatus expectedResult
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus secureStorage_UpdateBuffLenTest(const DxChar* aFileName, DxUint anInOutLen, DxStatus expectedResult);

//////////////////////////////////////////////
// delete file test
// Receives file lengh as a parameter
// deletes an existing SFS file and checks that thle does not exists after deletion
//
// DxUint fileLength
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus secureStorage_DeleteFileTest(DxUint32 fileLength);

//////////////////////////////////////////////
// create new SFS file test
// Receives file lengh as a parameter
// checking that when file does not exists, read function returns correct error code and trying to create creates new file
//
// DxUint fileLength
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus secureStorage_CreateNewFileTest(DxUint32 fileLength);


//////////////////////////////////////////////
// get SFS file name test
// Receives file name and size.
// Checks file size of given file with given length. If length is zero, the length will be checked for not exising file
//
// const DxChar* fileName
// DxUint fileLength
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus secureStorage_GetSizeTest(const DxChar* fileName, DxUint fileLength);

//////////////////////////////////////////////
// createDeviceKey test -
// receives an id, length and return a
// unique buffer. repeats the test few times while
// rebooting the TzInfra every time to see that this is true
//
// @param [in] id - Key id
// @param [out] buff - points the output buffer.
//           The allocated buffer must be big enough
//           to include the required key length.
// @param [in] length - the required key length.
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus createDeviceKey(DxUint32 id, DxUint8 *buff, DxUint32 length);

//////////////////////////////////////////////
// GetUniqueDeviceKey test
// Gets unique device id. must be always the same device id.
// repeats the test few times while
// rebooting the TzInfra every time to see that this is true
//
// @param [out] pDevUniqueID - buffer to be filled with unique id
// @param [in,out] length     - in: points max buffer
//            length; out: points required buffer size.
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus GetUniqueDeviceKey(DxUint8* pDevUniqueID, DxUint32 *length);

//////////////////////////////////////////////
// IsDeviceRooted test
// Gets the status of the device. and check
// it compare to the input parameter
//
// @param [in] expectedResult -
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus IsDeviceRooted(DxBool expectedResult);

//////////////////////////////////////////////
// IsBootLoaderUnlock test
// Gets the status of the device. and check
// it compare to the input parameter
//
// @param [in] expectedResult -
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus IsBootLoaderUnlock(DxBool expectedResult);

//////////////////////////////////////////////
// Function returns HDMI status in out parameter
// @return DX_SUCCESS on success, else non ZERO error.
DxStatus hdmiStatusTest( DxTzServiceParameter pParams[4]);

//////////////////////////////////////////////
// GetSetHdcp2ConnectionStatus test
// Test get/set HDCP2 connnection functionality
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus GetSetHdcp2ConnectionStatus(void);

//////////////////////////////////////////////
// MultipaleInitTermSecureContentPath test
// will call the DxTzService_InitSecureContentPath and
// DxTzService_TerminateSecureContentPath
//
// @numberOfTimes [IN] - the number of time to iterate
// over init and terminate the secure content path
//
// @return DX_SUCCESS on success, else non ZERO error.
//////////////////////////////////////////////
DxStatus MultipaleInitTermSecureContentPath(DxInt32 numberOfTimes );

//////////////////////////////////////////////
// Check if a given buffer is secured / non-secured according given expected result
//
// @bufferSize 					[IN] The size of the tested buffer
// @bTestForSecureBuffer 		[IN] Should buffer be tested for being secure
// @expectedResultSecureTest 	[IN] Expected result in case of a secure buffer test
// @bTestForNonSecureBuffer 	[IN] Should buffer be tested for being non secure
// @expectedResultNonSecureTest [IN] Expected result in case of a non secure buffer test
// @bIsShared 					[IN] Test type: shared memory or locally allocated by malloc()
// @pSharedMemRef 				[IN] Reference to the shared memory (in case shared memory is tested)
//
// @return DX_SUCCESS if result is as expected, else non ZERO error.
DxStatus IsMemorySecuredAsExpected( DxUint32 bufferSize,
									DxBool bTestForSecureBuffer,
									DxBool expectedResultSecureTest,
									DxBool bTestForNonSecureBuffer,
									DxBool expectedResultNonSecureTest,
									DxBool bIsShared,
									DxTzServiceSharedMemRef *pSharedMemRef
								  );


//////////////////////////////////////////////
// Copies regular memory (allocated in client) to shared memory (allocated in client).
//
// [IN]  type [0] in nParamTypes must be DX_TZ_PARAM_TYPE_MEMREF_INPUT			- source buffer
// [OUT] type [1] in nParamTypes must be DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	- destination buffer
//
// [IN]  type [2] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_INPUT
// [IN]  type [3] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_INPUT
//
// pParams[2] and pParams[3] details:
// [IN] pParams[2].value.a	- offset in source buffer
// [IN] pParams[2].value.b	- source size
// [IN] pParams[3].value.a 	- offset in destination buffer
// [IN] pParams[3].value.b  - destination size
//
// return DX_SUCCESS on success, else non ZERO error.
DxStatus CopyMemToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4]);


//////////////////////////////////////////////
// Copies shared memory (allocated in client) to regular memory (allocated in client).
//
// [IN]  type [0] in nParamTypes must be DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	- source buffer
// [OUT] type [1] in nParamTypes must be DX_TZ_PARAM_TYPE_MEMREF_INOUT			- destination buffer
//
// [IN]  type [2] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_INPUT
// [IN]  type [3] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_INPUT
//
// pParams[2] and pParams[3] details:
// [IN] pParams[2].value.a	- offset in source buffer
// [IN] pParams[2].value.b	- source size
// [IN] pParams[3].value.a 	- offset in destination buffer
// [IN] pParams[3].value.b  - destination size
//
// return DX_SUCCESS on success, else non ZERO error.
DxStatus CopyExToMem(DxUint32 nParamTypes, DxTzServiceParameter pParams[4]);


//////////////////////////////////////////////
// Copies shared memory (allocated in client) to shared memory (allocated in client).
//
// [IN]  type [0] in nParamTypes must be DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	- source buffer
// [OUT] type [1] in nParamTypes must be DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	- destination buffer
//
// [IN]  type [2] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_INPUT
// [IN]  type [3] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_INPUT
//
// pParams[2] and pParams[3] details:
// [IN] pParams[2].value.a	- offset in source buffer
// [IN] pParams[2].value.b	- source size
// [IN] pParams[3].value.a 	- offset in destination buffer
// [IN] pParams[3].value.b  - destination size
//
// return DX_SUCCESS on success, else non ZERO error.
DxStatus CopyExToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4]);


//////////////////////////////////////////////
// Compares regular memory (allocated in client) to shared memory (allocated in client).
//
// [IN]  	type [0] in nParamTypes must be DX_TZ_PARAM_TYPE_MEMREF_INPUT			- first buffer
// [OUT] 	type [1] in nParamTypes must be DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	- second buffer
// [INOUT] 	type [2] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_OUTPUT			- comparison result and dataSize to proceed
//				  (pParams[2].value.a - will contain comparison result, pParams[2].value.b contains input data size)
// type [3] - NONE
// return DX_SUCCESS on success, else non ZERO error.
DxStatus CompareMemToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4]);


//////////////////////////////////////////////
// Compares shared memory (allocated in client) to regular memory (allocated in client).
//
// [IN]  	type [0] in nParamTypes must be DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	- first buffer
// [OUT] 	type [1] in nParamTypes must be DX_TZ_PARAM_TYPE_MEMREF_INPUT			- second buffer
// [INOUT] 	type [2] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_OUTPUT			- comparison result and dataSize to proceed
//				  (pParams[2].value.a - will contain comparison result, pParams[2].value.b contains input data size)
// type [3] - NONE
// return DX_SUCCESS on success, else non ZERO error.
DxStatus CompareExToMem(DxUint32 nParamTypes, DxTzServiceParameter pParams[4]);


//////////////////////////////////////////////
// Compares shared memory (allocated in client) to shared memory (allocated in client).
//
// [IN]  	type [0] in nParamTypes must be DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	- first buffer
// [OUT] 	type [1] in nParamTypes must be DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	- second buffer
// [INOUT] 	type [2] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_OUTPUT			- comparison result and dataSize to proceed
//				  (pParams[2].value.a - will contain comparison result, pParams[2].value.b contains input data size)
// type [3] - NONE
// return DX_SUCCESS on success, else non ZERO error.
DxStatus CompareExToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4]);


//////////////////////////////////////////////
// Sets shared memory (allocated in client) to value.
//
// [IN]  type [0] in nParamTypes must be DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	- destination buffer to set
// [OUT] type [1] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_INPUT			- offset and length to set
// [OUT] type [2] in nParamTypes must be DX_TZ_PARAM_TYPE_VALUE_INPUT			- value to set
// type [3] - NONE
// return DX_SUCCESS on success, else non ZERO error.
DxStatus SetExMem(DxUint32 nParamTypes, DxTzServiceParameter pParams[4]);


//////////////////////////////////////////////
// Function makes AES decryption/encryption in following combinations :
// 1.  from regular memory (allocated in client) to shared memory (allocated in client)
// 2.  from shared memory (allocated in client) to regular memory (allocated in client).
// 3.  from shared memory (allocated in client) to shared memory (allocated in client).
// Combination chosen according to nCommandID.
// @return DX_SUCCESS on success, else non ZERO error.
DxStatus AES_BlockCipher_ExMemoryOperations(DxUint32 nParamTypes, DxTzServiceParameter pParams[4], EQaTstEnum nCommandID);


//////////////////////////////////////////////
// Function makes AES decryption/encryption on non-contiguous buffers.
//
// Encrypt/decrypt data from shared memory buffer to another shared memory buffer.
// params:
// [0] INOUT - input buffer and its size (shared buffer)
// [1] IN - value.a = data size
// [2] INOUT - output buffer for IV and KEY (regular buffer)
// [3] IN - NOT USED
// @return DX_SUCCESS on success, else non ZERO error.
DxStatus AES_BlockCipher_NonContiguousBuffersOperations(DxUint32 nParamTypes, DxTzServiceParameter pParams[4], EQaTstEnum nCommandID);


//////////////////////////////////////////////
// Function makes AES block mode cipher initialization :
// @return DX_SUCCESS on success, else non ZERO error.
DxStatus AES_BlockCipher_Init(DxUint32 nParamTypes, DxTzServiceParameter pParams[4]);

//////////////////////////////////////////////
// Function makes AES block mode cipher finalization :
// @return DX_SUCCESS on success, else non ZERO error.
DxStatus AES_BlockCipher_Finish(void);

//////////////////////////////////////////////
// Function runs all the relevant tests based on
// the value of containerSize for initial container creation
DxStatus testSfsSw (DxUint containerSize);

#endif // QaTestFuncDeclaration_h__

