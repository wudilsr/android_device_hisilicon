/**
 * @file DxTzClientAPI.h
 * @brief Platform-independent definitions for Client side of TEE.
 */
#ifndef	__DXTZCLIENTAPI_H__
#define	__DXTZCLIENTAPI_H__

#include	"DxTypes.h"
#include	"DxTzCommon.h"

/** Shared memory handle.
 */
typedef struct Dx_Client_Tz_MemHandler_s	*Dx_Client_Tz_MemHandler;

/** TEE Client context handle.
 */
typedef struct Dx_Client_Tz_Context_s 		*Dx_Client_Tz_Context;

/** TEE Client session handle.
 */
typedef struct Dx_Client_Tz_Session_s 		*Dx_Client_Tz_Session;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates the client context before usage.
 *
 * It is called before a call to DxTzClient_OpenSession().
 * The returned context is used to open a session.
 *
 * @param [out] context will point an instance of Dx_Client_Tz_Context structure,
 *	allocated in this function.
 *	The Dx_Client_Tz_Context is platform-independent opaque type of structure,
 *	whose complete type is defined in the platform-dependent code.
 *
 * @param [in] appId points the structure, which contains
 *	a name of the application running in the TEE, and/or UUID.
 *  The uuid usually points Unique ID identifying the service to be instantiated.
 *	The parameter appId maybe NULL if it's unused on the current platform.
 *
 * @return DX_SUCCESS  if operation has been successfully completed.
 * @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_CreateContext(Dx_Client_Tz_Context *context, Dx_TzAppId  *appId);

/*
 * Structure which represents list of client's capabilities.
 * Instance of this structure must be initialized by function
 * DxTzClient_InitializeCapabilitiesStruct, before initializing,
 * this structure is unusable.
 *
 * List of fields :
 * preAllocatedSharedBufferSizeBytes - size of preallocated shared buffer on which client's memref memory buffer
 *										will pass to from client to TEE.
 * useNativeTzLog - set to TRUE if you want to use platform native log.
 * useSerializedBufferTzLog - set to TRUE if you want to use client trace buffer log mechanism.
 * sfsPath - location of a file which contains encrypted SFS
 */
#define CLIENT_CAPABILITIES_SFS_PATH_MAX_LEN 128
typedef struct
{
	DxUint32    magic;
	DxUint32    preAllocatedSharedBufferSizeBytes;
	DxBool      useNativeTzLog;
	DxBool      useSerializedBufferTzLog;
    DxChar      sfsPath[CLIENT_CAPABILITIES_SFS_PATH_MAX_LEN];
}DxTzClientCapabilities;

/**
 * Creates the client context before usage.
 *
 * It is called before a call to DxTzClient_OpenSession().
 * The returned context is used to open a session.
 *
 * @param [out] context will point an instance of Dx_Client_Tz_Context structure,
 *	allocated in this function.
 *	The Dx_Client_Tz_Context is platform-independent opaque type of structure,
 *	whose complete type is defined in the platform-dependent code.
 *
 * @param [in] appId points the structure, which contains
 *	a name of the application running in the TEE, and/or UUID.
 *  The uuid usually points Unique ID identifying the service to be instantiated.
 *	The parameter appId maybe NULL if it's unused on the current platform.
 *
 * @param [in] clientCapabilitiesPtr address of list of client capabilities.
 * 				Configurable client capabilities :
 * 				preAllocatedSharedBufferSizeBytes - size of Preallocated SharedBuffer.
 * 				If client's memref buffers are too big for being serialized on
 * 				Serialization Buffer, error will be returned.
 * 				Set this field to 0 in order not to use PSB.
 *
 * @return DX_SUCCESS  if operation has been successfully completed.
 * @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_CreateContext2(Dx_Client_Tz_Context *context, Dx_TzAppId  *appId,
									DxTzClientCapabilities * clientCapabilitiesPtr);

/**
 * Destroys the previously created client context.
 *
 * It is called after DxTzClient_CloseSession().
 *
 * @param [in] context points an of Dx_Client_Tz_Context structure.
 *	The Dx_Client_Tz_Context is platform-independent opaque type of structure,
 *	whose complete type is defined in the platform-dependent code.
 *	Its instance is deallocated in this function.
*/
void DxTzClient_DestroyContext(Dx_Client_Tz_Context context);

/**
* Open client session (that means communication channel to the trust zone).
*
* @param [in] context points previously allocated and initialized instance of Dx_Client_Tz_Context structure.
*	The Dx_Client_Tz_Context is platform-independent opaque type of structure,
*	whose complete type is defined in the platform-dependent code.
*
* @param [out] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*	Will be used to call DxTzClient_InvokeCommand.
*	The Dx_Client_Tz_Session is platform-independent opaque type of structure,
*	whose complete type is defined in the platform-dependent code.
*	Its instance is allocated in this function.
*
* @param [in,out] operation points additional data used to create a session.
*	The Dx_Client_Tz_Operation is platform-independent structure type, defined in the DxTzCommon.h.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_OpenSession (
    Dx_Client_Tz_Context    context,
    Dx_Client_Tz_Session*    session,
    Dx_Client_Tz_Operation*  operation);


/**
* Close previously open client session.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*	The Dx_Client_Tz_Session is platform-independent opaque type of structure,
*	whose complete type is defined in the platform-dependent code.
*	Its instance is deallocated in this function.
*
*/
void DxTzClient_CloseSession (
    Dx_Client_Tz_Session session);


/**
* Execute the specified command on the trust zone.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @param [in] commandID: Unique ID agreed between the client and the service defining each operation.
* The command ID used in an application must not use a values between 0x0 and 0x01000,
* as they are reserved for internal TZ implementation.
*
* @param [in,out] operation: parameters passed from the client and values returned from the service.
* The Dx_Client_Tz_Operation is platform-depended structure type, defined in the DxTzPlatClientAPI.h.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus	 DxTzClient_InvokeCommand(
    Dx_Client_Tz_Session   session,
    DxUint32				commandID,
    Dx_Client_Tz_Operation* operation);


/**
* Set the root directory for provisioning and secure data storage on the trust zone.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @param [in] sfsPath is null-terminated string, which contains a path
*		to be used as root directory for provisioning and secure data storage in the specified session.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus	 DxTzClient_SetSfsPath(
	Dx_Client_Tz_Session   session,
	const DxChar *sfsPath);


/**
* This is required to be called just before first play of secure buffer.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_InitSecureContentPath(Dx_Client_Tz_Session pSession);


/**
* This is required to be called after finishing last play of secure buffer.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return platform-specified value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_TerminateSecureContentPath(Dx_Client_Tz_Session pSession);


/**
* Answer maximal size of the physical memory that can be allocated.
*
* @param [in] session is an identifier of a communication channel to a specific instance of a service allocated in the TZ.
*
* @return the maximal possible size.
*/
DxUint32 DxTzClient_MaxPhysicalMemoryChunk(Dx_Client_Tz_Session pSession);

/**
* Bit values used in allocationFlags parameter of the DxTzClient_ShaaredmemAlloc.
*
* DX_ALLOC_PHYS_ADDR_REQUIRED
*	(0/1)to be used on platforms, required physical address of memory buffer for TEE operations.
* (0/1)DX_ALLOC_TZ_VIRT_ADDR_REQUIRED
*	to be used on platforms, required virtual address of memory buffer related to the specified TEE context.
* (0/1)DX_ALLOC_SECURE
*	if the specified bit is set, allocate secure memory buffer, which can't be mapped in HLOS.
*
*/
#define DX_ALLOC_PHYS_ADDR_REQUIRED			0x01
#define DX_ALLOC_TZ_VIRT_ADDR_REQUIRED		0x02
#define DX_ALLOC_SECURE						0x04

/**
* Allocate shared memory buffer.
*
* @param [in] context points previously allocated and initialized instance of Dx_Client_Tz_Context structure.
* @param [in,out] memHandler: points a pointer to platform-dependent handle to keep full information about allocated data.
*     To be filled in this function.
* @param [in] size: Required allocated memory size in bytes.
* @param [in] allocationFlags: set of bit flags :
* DX_ALLOC_PHYS_ADDR_REQUIRED       - physical memory should be allocated
* DX_ALLOC_TZ_VIRT_ADDR_REQUIRED    - TZ virtual memory should be allocated
* DX_ALLOC_SECURE                   - secured memory should be allocated
* *** Note : OR-ed combination of flag is possible.
* ***        Not all combinations are supported on all platforms.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemAlloc(Dx_Client_Tz_Context context, Dx_Client_Tz_MemHandler *memHandler, DxUint32 size, DxUint32 allocationFlags);


/**
* Free shared memory buffer, previously allocated with the DxTzClient_SharedMemAlloc().
*
* @param [in] context points previously allocated and initialized instance of Dx_Client_Tz_Context structure.
* @param [in] memHandler: points a platform-dependent handle to keep full information about allocated data
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemFree(Dx_Client_Tz_Context context, Dx_Client_Tz_MemHandler memHandler);


/**
* Get allocation flags used by DxTzClient_SharedMemAlloc() function.
*
* @param [in] memHandler: Handler to opaque structure, which holds all the necessary mapping data (allocated through DxTzClient_SharedMemAlloc() call)
* @param [out] *pAllocationFlags: allocation flags used by DxTzClient_SharedMemAlloc()
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemGetFlags(Dx_Client_Tz_MemHandler memHandler, DxUint32 *pAllocationFlags);

/**
* Map user space pointer onto shared memory buffer.
*
* @param [in] memHandler: Handler to opaque structure, which holds all the necessary mapping data (allocated through DxTzClient_SharedMemAlloc() call)
* @param [out] virtualMemBuffer: Address, which will hold a pointer to a shared memory buffer (allocated through DxTzClient_SharedMemAlloc() call)
*   using information, provided with memHandler.
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemMap(Dx_Client_Tz_MemHandler memHandler, DxByte **virtualMemBuffer);


/**
* Unmap virtual memory buffer previously mapped with the DxTzClient_SharedMemMap().
*
* @param [in] memHandler: points a platform-dependent handle to keep full information about allocated data
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_SharedMemUnmap(Dx_Client_Tz_MemHandler memHandler);


/* This is special value for bufferSize parameter in function DxTzClient_ConvertToSharedMemRef.
	When function gets this value instead of bufferSize, it will set buffer size to maximal possible value*/
#define BUFFER_SIZE_MAX_AVAILABLE 0xFFFFFFFF

/**
* Prior to sending shared memory buffer through DxTzClient_InvokeCommand, transform it into appropriate structure.
* This function converts allocation metadata structire (Dx_Client_Tz_MemHandler) to structure which can be sent
* to TZ (Dx_Client_Tz_SharedMemRef).
*
* @param [out] destSharedMemRefPtr: points structure, whose fields are to be assigned
*   using information, provided with memHandler.
*
* @param [in] bufferOffset: offset from which buffer starts
*
* @param [in] bufferSize: desired buffer size of destination buffer. This size should be smaller or equal to
* 						  maximal available memory size.
*   *** Note : pass BUFFER_SIZE_MAX_AVAILABLE to set destination buffer size to maximal available memory size.
*
* @param [in] srcMemHandler: points a platform-dependent handle to keep full information about allocated data
*
* @return DX_SUCCESS  if operation has been successfully completed.
* @return a value other than DX_SUCCESS if operation failed.
*/
DxStatus DxTzClient_ConvertToSharedMemRef(Dx_Client_Tz_SharedMemRef *destSharedMemRefPtr, DxUint32 bufferOffset, DxUint32 bufferSize, Dx_Client_Tz_MemHandler srcMemHandler);

#ifdef __cplusplus
}
#endif

#endif

