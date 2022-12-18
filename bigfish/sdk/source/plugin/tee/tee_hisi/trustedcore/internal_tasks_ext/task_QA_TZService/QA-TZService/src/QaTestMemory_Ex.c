#include "QaTestFuncDeclaration.h"
#include "QaTestEnumeration.h"
#include "DxTzServiceAPI.h"
#include "QaUtils.h"
#include "DxTzCommon.h"
#include "DxTzServiceAPITypes.h"



//////////////////////////////////////////////////////////////////////////
//	Copy Memory functions (Mem->Ex, Ex->Mem, Ex->Ex
//////////////////////////////////////////////////////////////////////////
DxStatus CopyMemToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4])
{
	DxStatus result;
	DxTzServiceSharedMemRef tmpSharedMemRef;
	DxUint32 srcOffset,	srcSize, destOffset, destSize, dataSize;
	DxUint32 initialDestSize,initialSrcSize;

	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_MEMREF_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_VALUE_INPUT)
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	srcOffset = pParams[2].value.a;
	srcSize = pParams[2].value.b;
	destOffset = pParams[3].value.a;
	destSize = pParams[3].value.b;

	if( srcSize!=destSize)
	{
		QA_ERR_MSG("%s: bad srcSize or destSize parameter value",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	// convert input memref buffer in to ShredMemRef that will go in to DxTzService_MemCpyEx
	result = DxTzService_ConvertToSharedMemRef(&tmpSharedMemRef, 0, pParams[0].memRef.pBuffer, pParams[0].memRef.nSize);
	if( result != DX_SUCCESS )
	{
		QA_ERR_MSG("%s: DxTzService_ConvertToSharedMemRef failed! returned = %ld",__FUNCTION__, result);
		return result;
	}

	dataSize = srcSize;

	initialDestSize =   pParams[1].sharedMemRef.nSize;
	initialSrcSize  =   tmpSharedMemRef.nSize;

	result = DxTzService_MemCpyEx(&pParams[1].sharedMemRef, destOffset, &tmpSharedMemRef, srcOffset, dataSize);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_MemCpyEx failed! returned %ld",__FUNCTION__, result);
		return result;
	}

	/* validate that initial Data Size was not corrupted */
	if(	initialDestSize != pParams[1].sharedMemRef.nSize || initialSrcSize  !=   tmpSharedMemRef.nSize)
	{
		QA_ERR_MSG("%s: buffer size corrupted",__FUNCTION__);
		return DX_FAILURE;
	}

	return DX_SUCCESS;
}


DxStatus CopyExToMem(DxUint32 nParamTypes, DxTzServiceParameter pParams[4])
{
	DxStatus result;
	DxTzServiceSharedMemRef tmpSharedMemRef;
	DxUint32 srcOffset, srcSize, destOffset, destSize, dataSize;
	DxUint32 initialDestSize,initialSrcSize;

	if(DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_VALUE_INPUT)
	{
		DxHwLogError(DX_TRUE, "CopyExToMem: bad parameter types");
		return DX_TZ_BAD_PARAMETERS;
	}

	srcOffset = pParams[2].value.a;
	srcSize = pParams[2].value.b;
	destOffset = pParams[3].value.a;
	destSize = pParams[3].value.b;

	if( srcSize!=destSize)
	{
		QA_ERR_MSG("%s: bad srcSize or destSize parameter value",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	result = DxTzService_ConvertToSharedMemRef(&tmpSharedMemRef, 0, pParams[1].memRef.pBuffer, pParams[1].memRef.nSize);
	if( result != DX_SUCCESS )
	{
		QA_ERR_MSG("%s: DxTzService_ConvertToSharedMemRef failed! returned = %ld",__FUNCTION__, result);
		return result;
	}

	dataSize = srcSize;

	initialDestSize =   tmpSharedMemRef.nSize;
	initialSrcSize  =   pParams[0].sharedMemRef.nSize;

	result = DxTzService_MemCpyEx(&tmpSharedMemRef, destOffset, &pParams[0].sharedMemRef, srcOffset, dataSize);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_MemCpyEx failed! returned %ld",__FUNCTION__, result);
		return result;
	}

	/* validate that initial Data Size was not corrupted */
	if(	initialDestSize != tmpSharedMemRef.nSize || initialSrcSize  != pParams[0].sharedMemRef.nSize)
	{
		QA_ERR_MSG("%s: buffer size corrupted",__FUNCTION__);
		return DX_FAILURE;
	}

	return DX_SUCCESS;
}




DxStatus CopyExToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4])
{
	DxStatus result;
	DxUint32 srcOffset, srcSize, destOffset, destSize, dataSize;
	DxUint32 initialDestSize,initialSrcSize;

	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_VALUE_INPUT)
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	srcOffset = pParams[2].value.a;
	srcSize = pParams[2].value.b;
	destOffset = pParams[3].value.a;
	destSize = pParams[3].value.b;

	if( srcSize!=destSize)
	{
		QA_ERR_MSG("%s: bad srcSize or destSize parameter value",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	dataSize = srcSize;

	initialDestSize =   pParams[1].sharedMemRef.nSize;
	initialSrcSize  =   pParams[0].sharedMemRef.nSize;

	result = DxTzService_MemCpyEx(&pParams[1].sharedMemRef, destOffset, &pParams[0].sharedMemRef, srcOffset, dataSize);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_MemCpyEx failed! returned %ld",__FUNCTION__, result);
		return result;
	}

	/* validate that initial Data Size was not corrupted */
	if(	initialDestSize != pParams[1].sharedMemRef.nSize || initialSrcSize  != pParams[0].sharedMemRef.nSize)
	{
		QA_ERR_MSG("%s: buffer size corrupted",__FUNCTION__);
		return DX_FAILURE;
	}

	return DX_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////
//	Compare Memory functions (Mem->Ex, Ex->Mem, Ex->Ex)
//////////////////////////////////////////////////////////////////////////

DxStatus CompareMemToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4])
{
	DxStatus result;
	DxUint8 *data;
	DxUint32 dataSize;
	DxTzServiceSharedMemRef tmpSharedMemRef;
	DxInt cmpRes = 456;	// other than zero value

	if(DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_MEMREF_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_NONE)
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	data = pParams[0].memRef.pBuffer;
	dataSize = pParams[0].memRef.nSize;

	if(pParams[2].value.b != dataSize)
	{
		QA_ERR_MSG("%s: input parameters data not consistent : %d=pParams[2].value.b != dataSize=%d",__FUNCTION__,pParams[2].value.b,dataSize );
		return DX_TZ_BAD_PARAMETERS;
	}

	result = DxTzService_ConvertToSharedMemRef(&tmpSharedMemRef, 0, data, dataSize);
	if( result != 0 )
	{
		QA_ERR_MSG("%s: DxTzService_ConvertToSharedMemRef failed! returned = %ld",__FUNCTION__, result);
		return result;
	}

	result = DxTzService_MemCmpEx(&pParams[1].sharedMemRef, 0, &tmpSharedMemRef, 0, dataSize, &cmpRes);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_MemCmpEx failed! returned %ld",__FUNCTION__, result);
		return result;
	}

	pParams[2].value.a = (DxUint32)cmpRes;

	return DX_SUCCESS;
}


DxStatus CompareExToMem(DxUint32 nParamTypes, DxTzServiceParameter pParams[4])
{
	DxStatus result;
	DxUint8 *data;
	DxUint32 dataSize;
	DxTzServiceSharedMemRef tmpSharedMemRef;
	DxInt cmpRes = 456;

	if(DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_MEMREF_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_NONE)
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	data = pParams[1].memRef.pBuffer;
	dataSize = pParams[1].memRef.nSize;

	if(pParams[2].value.b != dataSize)
	{
		QA_ERR_MSG("%s: param data not consistent : %d=pParams[2].value.b != dataSize=%d",__FUNCTION__,pParams[2].value.b,dataSize );
		return DX_TZ_BAD_PARAMETERS;
	}

	result = DxTzService_ConvertToSharedMemRef(&tmpSharedMemRef, 0, data, dataSize);
	if( result != DX_SUCCESS )
	{
		QA_ERR_MSG("%s: DxTzService_ConvertToSharedMemRef failed! returned = %ld",__FUNCTION__, result);
		return result;
	}

	result = DxTzService_MemCmpEx(&pParams[0].sharedMemRef, 0, &tmpSharedMemRef, 0, dataSize, &cmpRes);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_MemCmpEx failed! returned %ld",__FUNCTION__, result);
		return result;
	}

	pParams[2].value.a = (DxUint32)cmpRes;

	return DX_SUCCESS;
}



DxStatus CompareExToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4])
{
	DxStatus result;
	DxInt cmpRes = 456;
	DxUint32 dataSize;

	if(DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_NONE)
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	dataSize = pParams[2].value.b;
	if(0 == dataSize)
	{
		QA_ERR_MSG("%s: param data not consistent : dataSize=%d",__FUNCTION__,dataSize );
		return DX_TZ_BAD_PARAMETERS;
	}

	result = DxTzService_MemCmpEx(&pParams[0].sharedMemRef, 0, &pParams[1].sharedMemRef, 0, dataSize, &cmpRes);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_MemCmpEx failed! returned %ld",__FUNCTION__, result);
		return result;
	}

	pParams[2].value.a = (DxUint32)cmpRes;

	return DX_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////
//	Set Ex memory function
//////////////////////////////////////////////////////////////////////////
DxStatus SetExMem(DxUint32 nParamTypes, DxTzServiceParameter pParams[4])
{
	DxStatus result;
	DxUint32 nBytes, offset;
	DxByte value;

	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_VALUE_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_NONE)
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	nBytes = pParams[1].value.a;
	offset = pParams[1].value.b;

	value = (DxByte)pParams[2].value.a;

	result = DxTzService_MemSetEx(&pParams[0].sharedMemRef, offset, value, nBytes);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_MemSetEx failed! returned %ld",__FUNCTION__, result);
		return result;
	}

	return DX_SUCCESS;
}

