/**
 * @file DxTzService_InternalDefs.h
 * @brief non-public definitions for TEE service
 *
 */
#ifndef	__DXTZSERVICE_INTERNALDEFS_H__
#define	__DXTZSERVICE_INTERNALDEFS_H__


#include "DxTypes.h"


/**
 * Defines the structure containing global data.
*/
typedef struct {
	void *rngState;			/* random generator context */
	void *globalInstance;
	void *secretStore;
	void *sfsPath;
	void *memrefArray;
} DxTzService_GlobalData_s;

/**
 * This is a special case, when client invokes a service command, dedicated for provisioning operation.
 * On Trusted foundation platform, it should be called from the SRVXInvokeCommand callback with special nCommandID values;
 * in another platform, call it when invoking a service command with special nCommandID values.
 *
 * @param [in, out] pSessionContext - the value of the void* opaque data pointer
 *  set by the service in the function SRVXOpenClientSession for this session.
 * @param [in] nCommandID - a service-specific code that identifies the command to be invoked.
 *  For this function the range of these commands must be between SVC_DX_PROV_INIT_CTXT and SVC_DX_PROV_LAST,
 *  which are specified for the case of provisioning actions.
 * @param [in] nParamTypes - encodes the type of each of the four parameters passed to the function.
 * @param [in,out] pParams - array of unions; each element of the array contains a parameter,
 *
 * @return DX_SUCCESS on success, else non ZERO error.
 */
DxStatus DxTzProvInvokeCommand(void* pSessionContext,
							   DxUint32 nCommandID,
							   DxUint32 nParamTypes,
							   DxTzServiceParameter pParams[DX_TZ_OPERATION_NUM_PARAMS]);

/**
 * answers an internal field of global data.
 *
 * @return pointer to the crysRndState.
 */
void *DxTzService_GetCrysRndState(void);


/**
 * Initialize TZ service application.
 * This API is to be called when the TZ service application is uploaded
 * as an entry point for the HLOS application's call to the DxTzClient_InitializeContext API.
 * An implementation of this API and the point of its call is fully platform dependent.
 *
 * @return DX_SUCCESS  if operation has been successfully completed,
 *	any other value indicates a failure.
*/
DxStatus DxTzService_Initialize(void);


/**
 * Finalize TZ service application.
 * This API is to be called before the TZ service application is terminated
 * as an entry point for the HLOS application's call to the DxTzClient_FinalizeContext API.
 * An implementation of this API and the point of its call is fully platform dependent.
*/
void DxTzService_Finalize(void);


/**
 * Retrieves TZ service secret store.
 * An implementation of this API and the point of its call is fully platform dependent.
 *
 * @return address of secure storage if operation has been successfully completed,
 *	otherwise return DX_NULL.
*/
void *DxTzService_GetSecretStore(void);

/**
 * Estimates clear size given a wrapped buffer size
 *
 * @param [in] wrappedSize  - wrapped buffer size
 * @return clear buffer size after unwrapping
 * @note Platform dependent
 */
DxUint DxTzService_EstimateUnwrappedSize (DxUint wrappedSize);

/**
 * Estimates wrapped size given a clear buffer size
 *
 * @param [in] clearSize  - clear buffer size
 * @return wrapped buffer size
 * @note Platform dependent
 */
DxUint DxTzService_EstimateWrappedSize (DxUint clearSize);

/**
 * Extracts clear buffer with a platform dependant cryptographic procedure
 *
 * @param [in] pSrc         - pointer to a wrapped buffer
 * @param [in] srcLen       - size of a wrapped buffer
 * @param [out] pDst        - pointer to a clear buffer
 * @param [inout] pDstLen   - pointer to be filled with:
 *                            in: size of the destination(clear) buffer
 *                            out: actual size of data in the destination(clear) buffer
 * @return DX_BAD_ARGUMENTS - invalid parameters including not big enough buffer
 *         DX_FAILURE       - unwrapping operation fails
 *         DX_SUCCESS       - otherwise
 * @note Platform dependent
 */
DxStatus DxTzService_UnwrapBuffer (const void* pSrc, DxUint srcLen,
                                   void* pDst, DxUint *pDstLen);

/**
 * Protects clear buffer with a platform dependant cryptographic procedure
 *
 * @param [in] pSrc         - pointer to a clear buffer
 * @param [in] srcLen       - size of a clear buffer
 * @param [out] pDst        - pointer to a wrapped buffer
 * @param [inout] pDstLen   - pointer to be filled with:
 *                            in: size of the destination(wrapped) buffer
 *                            out: actual size of data in the destination(wrapped) buffer
 * @return DX_BAD_ARGUMENTS - invalid parameters including not big enough buffer
 *         DX_FAILURE       - unwrapping operation fails
 *         DX_SUCCESS       - otherwise
 * @note Platform dependent
 */
DxStatus DxTzService_WrapBuffer (const void* pSrc, DxUint srcLen,
                                 void* pDst, DxUint *pDstLen);

#endif
