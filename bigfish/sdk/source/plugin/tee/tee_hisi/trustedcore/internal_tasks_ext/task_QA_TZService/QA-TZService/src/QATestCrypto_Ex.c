#include "QaTestFuncDeclaration.h"
#include "QaTestEnumeration.h"
#include "DxTzServiceAPI.h"
#include "QaUtils.h"
#include "DxTzCommon.h"
#include "DxTzServiceAPITypes.h"


//////////////////////////////////////////////////////////////////////////
//	AES CTR Memory encryption / decryption functions (Mem->Ex, Ex->Mem, Ex->Ex)
//////////////////////////////////////////////////////////////////////////



// static strucure for holding the state of block mode cipher
static struct{
	DxCipher_AES128_Context_t m_aesCipherContext;			// Block cipher mode
	DxCipher_AES128CTR_Context_t m_aesCtrCipherContext;   	// CTR context
	DxCipher_AES128CBC_Context_t m_aesCbcCipherContext;	  	// CBC context
	EAES_MODE m_mode;
	EAES_DIRECTION m_cipherDirection;

	DxUint32 m_isInitialized;

}g_cipherDataStruct =  {DX_NULL,DX_NULL,DX_NULL,eAES_MODE_CBC,eAES_DIRECTION_ENC, DX_FALSE};


static void CleanCipherStruct()
{
	DxTzService_MemSet(&g_cipherDataStruct,0x00,sizeof(g_cipherDataStruct));
}


DxStatus AES_BlockCipher_Init(DxUint32 nParamTypes, DxTzServiceParameter pParams[4])
{
	DxByte * key = DX_NULL;
	const DxUint32 key_length = DX_TZ_AES128_BLOCK_SIZE;


	DxStatus contextRes;

	/*
		Init context:
		[0] IN -
				value.a = cipher to init(CBC or CTR),
				value.b = cipher direction
		[1] IN - input/output buffer for KEY(regular)
		[2] NONE
		[3] NONE
	*/

	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_VALUE_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_MEMREF_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_NONE ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_NONE)
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	if(DX_TRUE == g_cipherDataStruct.m_isInitialized)
	{
		QA_ERR_MSG("%s: context already initialized, call to AES_BlockCipher_Finish previously",__FUNCTION__);
		return DX_TZ_BAD_STATE;
	}


	/* extract cipher direction */
	if(pParams[0].value.b != eAES_DIRECTION_ENC && pParams[0].value.b != eAES_DIRECTION_DEC)
	{
		CleanCipherStruct();
		QA_ERR_MSG("%s: bad cipher direction",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}
	g_cipherDataStruct.m_cipherDirection = (EAES_DIRECTION)pParams[0].value.b;

	/* extract key, key_length*/
	if(pParams[1].memRef.nSize != DX_TZ_AES128_BLOCK_SIZE)
	{
		CleanCipherStruct();
		QA_ERR_MSG("%s: bad key size (got %u, expected %u)",__FUNCTION__, pParams[1].memRef.nSize, DX_TZ_AES128_BLOCK_SIZE);
		return DX_TZ_BAD_PARAMETERS;
	}
	key = ((DxByte*)(pParams[1].memRef.pBuffer));


	QA_LOG_MSG("%s: initializing aesCipherContext",__FUNCTION__);


	/* Create Cipher Context */
	contextRes = DxTzService_AES128_CreateContext(&g_cipherDataStruct.m_aesCipherContext);
	if (contextRes != DX_SUCCESS)
	{
		CleanCipherStruct();
		QA_ERR_MSG("%s:DxTzService_AES128_CreateContext failed, contextRes=0x%X",__FUNCTION__,contextRes);
		return contextRes;
	}


	/* Init Specific Cipher Context : CTR or CBC */
	switch (pParams[0].value.a)
	{
		case eAES_MODE_CTR:
			QA_LOG_MSG("%s: initializing aesCtrCipherContext",__FUNCTION__);
			contextRes = DxTzService_AES128CTR_Init(&g_cipherDataStruct.m_aesCtrCipherContext, g_cipherDataStruct.m_aesCipherContext, key, key_length, (EDxCipherDirection)g_cipherDataStruct.m_cipherDirection);
			break;

		case eAES_MODE_CBC:
			QA_LOG_MSG("%s: initializing aesCbcCipherContext",__FUNCTION__);
			contextRes = DxTzService_AES128CBC_Init(&g_cipherDataStruct.m_aesCbcCipherContext, g_cipherDataStruct.m_aesCipherContext, key, key_length, (EDxCipherDirection)g_cipherDataStruct.m_cipherDirection);
			break;

		default:
			QA_ERR_MSG("%s: bad mode type",__FUNCTION__);
			break;
	}

	if( contextRes != DX_SUCCESS )
	{
		// release
		DxTzService_AES128_TerminateContext(&g_cipherDataStruct.m_aesCipherContext);
		CleanCipherStruct();
		QA_ERR_MSG("%s: AES128 specific cipher init failed, contextRes=0x%X",__FUNCTION__, contextRes);
		return contextRes;
	}


	// save mode
	g_cipherDataStruct.m_mode = (EAES_MODE)pParams[0].value.a;


	g_cipherDataStruct.m_isInitialized = DX_TRUE;

	return DX_SUCCESS;
}




DxStatus AES_BlockCipher_Finish(void)
{
	/*
		Finish context:
		[0] NONE
		[1] NONE
		[2] NONE
		[3] NONE
	*/
	DxStatus contextRes=DX_FAILURE;

	if( DX_FALSE == g_cipherDataStruct.m_isInitialized)
	{
		QA_ERR_MSG("%s: context is NOT initialized, AES_BlockCipher_Finish invalid call",__FUNCTION__);
		return DX_TZ_BAD_STATE;
	}

	QA_LOG_MSG("%s: terminating context",__FUNCTION__);


	// terminate specific context first

	/* Init Specific Cipher Context : CTR or CBC */
	switch (g_cipherDataStruct.m_mode)
	{
		case eAES_MODE_CTR:
			QA_LOG_MSG("%s: finishing aesCtrCipherContext",__FUNCTION__);
			contextRes = DxTzService_AES128CTR_Finish(&g_cipherDataStruct.m_aesCtrCipherContext);
			break;

		case eAES_MODE_CBC:
			QA_LOG_MSG("%s: finishing aesCbcCipherContext",__FUNCTION__);
		    contextRes = DxTzService_AES128CBC_Finish(&g_cipherDataStruct.m_aesCbcCipherContext);
		    break;

		default:
			QA_ERR_MSG("%s: bad mode type",__FUNCTION__);
			break;
	}

	if( contextRes != DX_SUCCESS )
	{
		// release
		DxTzService_AES128_TerminateContext(&g_cipherDataStruct.m_aesCipherContext);
		CleanCipherStruct();
		QA_ERR_MSG("%s: AES128 specific cipher finish failed, contextRes=0x%X",__FUNCTION__, contextRes);
		return contextRes;
	}

	contextRes = DxTzService_AES128_TerminateContext(&g_cipherDataStruct.m_aesCipherContext);
	if( contextRes != DX_SUCCESS )
	{
		QA_ERR_MSG("%s: DxTzService_AES128_TerminateContext failed, contextRes=0x%X",__FUNCTION__, contextRes);
	}

	CleanCipherStruct();
	return contextRes;
}





static DxStatus PerformEncryptDecrypt(DxChar* name, DxTzServiceSharedMemRef *pSrc,
									  DxUint32 srcOffset,
									  DxTzServiceSharedMemRef *pDest,
									  DxUint32 destOffset,
									  DxUint32 dataSize,
									  DxUint8  iv[16])
{
	DxStatus result;

	switch(g_cipherDataStruct.m_mode)
	{
	case eAES_MODE_CTR:
		if(g_cipherDataStruct.m_cipherDirection==(EAES_DIRECTION)DXCIPHER_ENC)
		{
			QA_LOG_MSG("%s calling DxTzService_AES128CTR_EncryptDataEx",name);
			result = DxTzService_AES128CTR_EncryptDataEx(g_cipherDataStruct.m_aesCtrCipherContext, pSrc, srcOffset, pDest, destOffset, dataSize, iv);
		}
		else
		{
			QA_LOG_MSG("%s calling DxTzService_AES128CTR_DecryptDataEx",name);
			result = DxTzService_AES128CTR_DecryptDataEx(g_cipherDataStruct.m_aesCtrCipherContext, pSrc, srcOffset, pDest, destOffset, dataSize, iv);
		}
		break;

	case eAES_MODE_CBC:
		if(g_cipherDataStruct.m_cipherDirection==(EAES_DIRECTION)DXCIPHER_ENC)
		{
			QA_LOG_MSG("%s calling DxTzService_AES128CBC_EncryptDataEx",name);
			result = DxTzService_AES128CBC_EncryptDataEx(g_cipherDataStruct.m_aesCbcCipherContext, pSrc, srcOffset, pDest, destOffset, dataSize, iv);
		}
		else
		{
			QA_LOG_MSG("%s calling DxTzService_AES128CBC_DecryptDataEx",name);
			result = DxTzService_AES128CBC_DecryptDataEx(g_cipherDataStruct.m_aesCbcCipherContext, pSrc, srcOffset, pDest, destOffset, dataSize, iv);
		}
		break;

	default:
		QA_ERR_MSG("%s: bad mode parameter",name);
		return DX_TZ_BAD_PARAMETERS;
	};

	return result;
}





static DxStatus AES_BlockCipher_MemToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4],
										DxByte * iv, DxUint32 srcOffset, DxUint32 dstOffset, DxUint32 lengthOfBufferToProcess)
{
/*
	Encrypt/decrypt data from regular memory to shared memory buffer.
	params:
	[0] IN - input buffer and its size (regular buffer)
	[1] INOUT - output buffer and its size (shared buffer)
*/

	DxStatus result;
	DxUint8 *inData;
	DxUint32 inDataSize;
	DxTzServiceSharedMemRef tmpSharedMemRef;

	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_MEMREF_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT)
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}


	QA_LOG_MSG("%s started",__FUNCTION__);

	// input data array
	inData = pParams[0].memRef.pBuffer;
	inDataSize = pParams[0].memRef.nSize;


	// check consistency
	if(iv==DX_NULL || srcOffset+lengthOfBufferToProcess > inDataSize || dstOffset+lengthOfBufferToProcess > inDataSize)
	{
		QA_ERR_MSG("%s: bad parameter function values",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	result = DxTzService_ConvertToSharedMemRef(&tmpSharedMemRef,0, inData, inDataSize);
	if( result != DX_SUCCESS )
	{
		QA_ERR_MSG("%s: DxTzService_ConvertToSharedMemRef failed, returned = 0x%X",__FUNCTION__, result);
		return result;
	}

	result = PerformEncryptDecrypt("MemToEx",&tmpSharedMemRef, srcOffset, &pParams[1].sharedMemRef, dstOffset, lengthOfBufferToProcess, iv);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_AES128CTR(CBC)_En(De)cryptDataEx returned 0x%X",__FUNCTION__, result);
		return result;
	}

	return DX_SUCCESS;
}



static DxStatus AES_BlockCipher_ExToMem(DxUint32 nParamTypes, DxTzServiceParameter pParams[4],
										DxByte * iv, DxUint32 srcOffset, DxUint32 dstOffset, DxUint32 lengthOfBufferToProcess)
{
	/*
	Encrypt/decrypt data from shared memory buffer to regular memory.
	params:
	[0] IN - input buffer and its size (shared buffer)
	[1] INOUT - output buffer and its size (regular buffer)
*/

	DxStatus result;
	DxUint8 *outData;
	DxUint32 outDataSize;
	DxTzServiceSharedMemRef tmpSharedMemRef;

	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_MEMREF_INOUT )
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	// output buffer
	outData = pParams[1].memRef.pBuffer;
	outDataSize = pParams[1].memRef.nSize;


	// check consistency
	if(iv==DX_NULL || srcOffset+lengthOfBufferToProcess > outDataSize || dstOffset+lengthOfBufferToProcess > outDataSize)
	{
		QA_ERR_MSG("%s: bad parameter function values",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	result = DxTzService_ConvertToSharedMemRef(&tmpSharedMemRef,0, outData, outDataSize);
	if( result != DX_SUCCESS )
	{
		QA_ERR_MSG("%s: DxTzService_ConvertToSharedMemRef failed, returned = 0x%X",__FUNCTION__, result);
		return result;
	}

	result = PerformEncryptDecrypt("ExToMem",&pParams[0].sharedMemRef, srcOffset, &tmpSharedMemRef, dstOffset, lengthOfBufferToProcess, iv);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_AES128CTR(CBC)_En(De)cryptDataEx returned 0x%X",__FUNCTION__, result);
		return result;
	}


	return DX_SUCCESS;
}



static DxStatus AES_BlockCipher_ExToEx(DxUint32 nParamTypes, DxTzServiceParameter pParams[4],
								DxByte * iv, DxUint32 srcOffset, DxUint32 dstOffset, DxUint32 lengthOfBufferToProcess)
{
/*
	Encrypt/decrypt data from shared memory buffer to another shared memory buffer.
	params:
	[0] IN		- input  buffer and its size (shared buffer)
	[1] INOUT	- output buffer and its size (shared buffer)
*/

	DxStatus result;


	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT )
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}


	// check consistency
	if(iv==DX_NULL || srcOffset+lengthOfBufferToProcess >  pParams[0].sharedMemRef.nSize || dstOffset+lengthOfBufferToProcess > pParams[0].sharedMemRef.nSize)
	{
		QA_ERR_MSG("%s: bad parameter function values",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	result = PerformEncryptDecrypt("ExToEx",&pParams[0].sharedMemRef, srcOffset, &pParams[1].sharedMemRef, dstOffset, lengthOfBufferToProcess, iv);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_AES128CTR(CBC)_En(De)cryptDataEx returned 0x%X",__FUNCTION__, result);
		return result;
	}


	return DX_SUCCESS;
}




DxStatus AES_BlockCipher_ExMemoryOperations(DxUint32 nParamTypes, DxTzServiceParameter pParams[4], EQaTstEnum nCommandID)
{
	DxStatus result;
	DxUint32 dataSizeTotal, srcOffset, dstOffset, lengthOfBufferToProcess, halfNumber, numberOfHalvesTotal;
	EAES_MODE mode;
	DxByte * iv;

/* 	Encrypt/decrypt data from SOURCE BUFFER to DESTINATION BUFFER.
	params:

	[0] IN		- PLAIN TEXT  INPUT BUFFER,can be shared or regular
	[1] INOUT	- CIPHER TEXT OUTPUT BUFFER,can be shared or regular
	[2] INOUT	- output buffer for IV (regular buffer) - will be updated after Encrypt/Decrypt
	[3] IN		-
				value.a = which half to work on(halfNumber),
				value.b = how much there are halfes at all(numberOfHalfsTotal)
*/
	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_MEMREF_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_VALUE_INPUT )
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	if(g_cipherDataStruct.m_isInitialized == DX_FALSE)
	{
		QA_ERR_MSG("%s: context is not initialized, call to AES_BlockCipher_Init first",__FUNCTION__);
		return DX_TZ_BAD_STATE;
	}

	/* 1. extract dataSize : Source data is always in pParams[0] */
	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) == DX_TZ_PARAM_TYPE_MEMREF_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) == DX_TZ_PARAM_TYPE_MEMREF_INOUT)
	{
		dataSizeTotal=pParams[0].memRef.nSize;
	}
	else if(DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) == DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT)
	{
		dataSizeTotal=pParams[0].sharedMemRef.nSize;
	}
	else
	{
		QA_ERR_MSG("%s: bad parameter pParam[0] type",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	/* 2. extract and validate mode against initialized struct  */
	switch (nCommandID)
	{

	case QA_TST_AES_CTR_MEM_TO_EX:
	case QA_TST_AES_CTR_EX_TO_MEM:
	case QA_TST_AES_CTR_EX_TO_EX:
		mode = eAES_MODE_CTR;
		break;

	case QA_TST_AES_CBC_MEM_TO_EX:
	case QA_TST_AES_CBC_EX_TO_MEM:
	case QA_TST_AES_CBC_EX_TO_EX:
		mode = eAES_MODE_CBC;
		break;

	default:
		QA_ERR_MSG("%s: bad nCommandID",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	};

	if(mode != g_cipherDataStruct.m_mode)
	{
		QA_ERR_MSG("%s: mode calculated via nCommandID",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	QA_LOG_MSG("%s: started for nCommandID=%d, dataSize=%d, mode=%s",__FUNCTION__, nCommandID, dataSizeTotal, (mode == eAES_MODE_CTR)?"CTR":"CBC");

	// extract offsets, processing data size
	halfNumber			= pParams[3].value.a;
	numberOfHalvesTotal	= pParams[3].value.b;

	srcOffset = (dataSizeTotal*halfNumber)/numberOfHalvesTotal;
	dstOffset = srcOffset;
	lengthOfBufferToProcess = dataSizeTotal/numberOfHalvesTotal;

	// extract iv
	if(DX_TZ_AES128_IV_SIZE != pParams[2].memRef.nSize)
	{
		QA_ERR_MSG("%s: iv size is not as expected(got %d, expected %d)", __FUNCTION__, pParams[2].memRef.nSize, DX_TZ_AES128_IV_SIZE);
		return DX_TZ_BAD_PARAMETERS;
	}
	iv = ((DxByte*)(pParams[2].memRef.pBuffer));


	// perform encrypt/decrypt
	switch (nCommandID)
	{
	case QA_TST_AES_CBC_MEM_TO_EX:
	case QA_TST_AES_CTR_MEM_TO_EX:
		result = AES_BlockCipher_MemToEx(nParamTypes, pParams, iv,srcOffset,dstOffset,lengthOfBufferToProcess);
	break;

	case QA_TST_AES_CTR_EX_TO_MEM:
	case QA_TST_AES_CBC_EX_TO_MEM:
		result = AES_BlockCipher_ExToMem(nParamTypes, pParams, iv,srcOffset,dstOffset,lengthOfBufferToProcess);
		break;

	case QA_TST_AES_CTR_EX_TO_EX:
	case QA_TST_AES_CBC_EX_TO_EX :
		result = AES_BlockCipher_ExToEx(nParamTypes, pParams, iv,srcOffset,dstOffset,lengthOfBufferToProcess);
		break;

	default:
		result = DX_TZ_BAD_PARAMETERS;
		break;
	}


	// return result of tests, not last operation
	return result;
}






DxStatus AES_BlockCipher_NonContiguousBuffersOperations(DxUint32 nParamTypes, DxTzServiceParameter pParams[4], EQaTstEnum nCommandID)
{
	DxStatus result;
	DxUint32 dataSizeToProceed, srcOffset, dstOffset;
	EAES_MODE mode;
	DxByte * iv;

/* 	Encrypt/decrypt data from SOURCE BUFFER to DESTINATION BUFFER.
	params:

	[0] IN		- PLAIN TEXT  INPUT BUFFER,can be shared or regular
	[1] IN		- value.a = data size
	[2] INOUT	- output buffer for IV (regular buffer) - will be updated after Encrypt/Decrypt
	[3] IN		- not used (value is not DX_TZ_PARAM_TYPE_NONE for other tests compatibility)
*/

	if( DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT	||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_VALUE_INPUT			||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_MEMREF_INOUT			)
		// third parameter is not used for non-contiguous test
	{
		QA_ERR_MSG("%s: bad parameter types",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	if(g_cipherDataStruct.m_isInitialized == DX_FALSE)
	{
		QA_ERR_MSG("%s: context is not initialized, call to AES_BlockCipher_Init first",__FUNCTION__);
		return DX_TZ_BAD_STATE;
	}

	/* 1. extract dataSize : Source data size to proceed is always in pParams[1] */
	dataSizeToProceed = pParams[1].value.a;

	/* 2. extract and validate mode against initialized struct  */
	switch (nCommandID)
	{
	case QA_TST_NON_CONTIGUOUS_BUFFERS_CTR:
		mode = eAES_MODE_CTR;
		break;

	case QA_TST_NON_CONTIGUOUS_BUFFERS_CBC:
		mode = eAES_MODE_CBC;
		break;

	default:
		QA_ERR_MSG("%s: bad nCommandID",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	};

	if(mode != g_cipherDataStruct.m_mode)
	{
		QA_ERR_MSG("%s: mode calculated via nCommandID",__FUNCTION__);
		return DX_TZ_BAD_PARAMETERS;
	}

	QA_LOG_MSG("%s: started for nCommandID=%d, dataSize=%d, mode=%s",__FUNCTION__, nCommandID, dataSizeToProceed, (mode == eAES_MODE_CTR)?"CTR":"CBC");


	srcOffset = 0; /* source resides on first byte of available memory */
	dstOffset = dataSizeToProceed;	/* dest.  resides immediately after source, source size is dataSizeToProceed */

	// extract iv
	if(DX_TZ_AES128_IV_SIZE != pParams[2].memRef.nSize)
	{
		QA_ERR_MSG("%s: iv size is not as expected(got %d, expected %d)", __FUNCTION__, pParams[2].memRef.nSize, DX_TZ_AES128_IV_SIZE);
		return DX_TZ_BAD_PARAMETERS;
	}
	iv = ((DxByte*)(pParams[2].memRef.pBuffer));


	// perform encrypt/decrypt
	result = PerformEncryptDecrypt("ExToEx",&pParams[0].sharedMemRef, srcOffset, &pParams[0].sharedMemRef, dstOffset, dataSizeToProceed, iv);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: DxTzService_AES128CTR(CBC)_En(De)cryptDataEx returned 0x%X",__FUNCTION__, result);
		return result;
	}

	return DX_SUCCESS;
}







