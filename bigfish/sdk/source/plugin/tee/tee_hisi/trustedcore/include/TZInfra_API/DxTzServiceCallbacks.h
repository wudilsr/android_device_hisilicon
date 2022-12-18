/**
 * @file DxTzServiceCallbacks.h
 * @brief Callback functions for the TEE service
 *
 * These functions must be implemented using the platform methodology and functionality.
 *
 */
#ifndef	__DXTZSERVICECALLBACKS_H__
#define	__DXTZSERVICECALLBACKS_H__


#include "DxTypes.h"
#include "DxTzCommon.h"


/**
 * TEE service constructor.
 * It should be called only once in the life-time of the service instance.
 * On Trusted foundation platform, it should be called from the SRVXCreate callback;
 * in another platform, call it when initializing client context for TZ.
 *
 * @return DX_SUCCESS on success, else non ZERO error.
 */
DxStatus SRVXCreate_impl(void);

/**
 * TEE service destructor.
 * It should be called only once before the service instance is terminated.
 *
 * On Trusted foundation platform, it should be called from the SRVXDestroy callback;
 * in another platform, call it when finalizing client context for TZ.
 */
void SRVXDestroy_impl(void);

/**
 * This function is called whenever a new client attempts to connect to the service instance.
 * If this functions fails, the connection is rejected.
 * On Trusted foundation platform, it should be called from the SRVXOpenClientSession callback;
 * in another platform, call it when opening client session for TZ service.
 *
 * @param [in] nParamTypes - encodes the type of each of the four parameters passed to the function.
 * @param [in,out] pParams - array of unions; each element of the array contains a parameter,
 *		whose type is specified by appropriate element of the nParamTypes.
 *		Parameter types are described in DxTzCommon.h file.
 *		Note that due to platform restriction, can use only 3 parameters of DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT type.
 * @param [out] ppSessionContext - a pointer to a variable that can be filled by the service with an opaque void* data pointer.
 *
 * @return DX_SUCCESS on success, else non ZERO error.
 */
DxStatus SRVXOpenClientSession_impl(
									DxUint32 nParamTypes,
									DxTzServiceParameter pParams[DX_TZ_OPERATION_NUM_PARAMS],
									void** ppSessionContext );


/**
 * This function is called whenever the client disconnects from the service instance.
 * On Trusted foundation platform, it should be called from the SRVXCloseClientSession callback;
 * in another platform, call it when closing client session for TZ service.
 *
 * @param [in, out] pSessionContext - the value of the void* opaque data pointer
 *  set by the service in the function SRVXOpenClientSession for this session.
 *
 * @return DX_SUCCESS on success, else non ZERO error.
 */
void SRVXCloseClientSession_impl(void* pSessionContext);

/**
 * This function is called whenever a client invokes a service command.
 * On Trusted foundation platform, it should be called from the SRVXInvokeCommand callback;
 * in another platform, call it when invoking a service command.
 *
 * @param [in, out] pSessionContext - the value of the void* opaque data pointer
 *		set by the service in the function SRVXOpenClientSession for this session.
 * @param [in] nCommandID - a service-specific code that identifies the command to be invoked
 *		The nCommandID used in an application must not use a values between 0x0 and 0x01000,
 *		as they are reserved for internal TZ implementation.
 * @param [in] nParamTypes - encodes the type of each of the four parameters passed to the function.
 * @param [in,out] pParams - array of unions; each element of the array contains a parameter,
 *		Parameter types are described in DxTzCommon.h file.
 *		Note that due to platform restriction, can use only 3 parameters of DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT type.
 *
 * @return DX_SUCCESS on success, else non ZERO error.
 */
DxStatus SRVXInvokeCommand_impl(void* pSessionContext,
								DxUint32 nCommandID,
								DxUint32 nParamTypes,
								DxTzServiceParameter pParams[DX_TZ_OPERATION_NUM_PARAMS]);


#endif
