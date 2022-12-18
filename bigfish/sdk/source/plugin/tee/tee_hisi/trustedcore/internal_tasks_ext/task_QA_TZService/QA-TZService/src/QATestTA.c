#include "QaTestEnumeration.h"
#include "QaCallbackSequence.h"
#include "DxTzServiceCallbacks.h"

#include "QaTestFuncDeclaration.h"
#include "QaUtils.h"
#include "DxTzService_Utils.h"


//todo - remove folloowing include
#include "DX_VOS_DbgPrint.h"


#include "DxTzServiceAPI.h"
#include "DxTypes.h"


DxUint32 TA_CreateEntryPoint(void)
{
    return SRVXCreate_impl();
}

void TA_DestroyEntryPoint(void)
{
    SRVXDestroy_impl();
}

DxUint32 TA_OpenSessionEntryPoint(DxUint32 nParamTypes,
		DX_TZ_PARAM pParams[4],
		void** ppSessionContext )
{
    return SRVXOpenClientSession_impl(nParamTypes, pParams, ppSessionContext);
}

void TA_CloseSessionEntryPoint(void* pSessionContext)
{
    SRVXCloseClientSession_impl(pSessionContext);
}

DxUint32 TA_InvokeCommandEntryPoint(void* pSessionContext,
		DxUint32 nCommandID,
		DxUint32 nParamTypes,
		DX_TZ_PARAM pParams[4])
{
    SRVXInvokeCommand_impl(pSessionContext, nCommandID, nParamTypes, pParams);
}

