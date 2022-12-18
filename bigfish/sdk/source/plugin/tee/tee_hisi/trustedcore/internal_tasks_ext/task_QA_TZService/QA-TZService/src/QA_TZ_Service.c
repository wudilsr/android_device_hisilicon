
#include "QaTestEnumeration.h"
#include "QaCallbackSequence.h"


#include "QaTestFuncDeclaration.h"
#include "QaUtils.h"
#include "DxTzService_Utils.h"


//todo - remove folloowing include
#include "DX_VOS_DbgPrint.h"


#include "DxTzServiceAPI.h"
#include "DxTypes.h"


//#define SFS_SW_TEST

/**********************************************************************************
 * 	Tz Qa Test Application callbacks imlementations
 ***********************************************************************************/


static void ReleaseQaGlobalData(QaGlobalInstance* qaGlobal)
{
	if (DX_NULL != qaGlobal)
	{
		terminateQaGlobalInstance(qaGlobal);
	}

	/* free qa global instance */
	DxTzService_Free(qaGlobal);
	qaGlobal=DX_NULL;
}

DxUint32 SRVXCreate_impl(void)
//DxUint32 TA_CreateEntryPoint(void)
{
	DxStatus result = DX_SUCCESS;

        if(sfs_init() != DX_SUCCESS)
            return DX_FAILURE;

	// allocate global instance
	QaGlobalInstance* qaGlobal = (QaGlobalInstance*)DxTzService_Malloc(sizeof(QaGlobalInstance));
	if (DX_NULL == qaGlobal)
	{
		QA_ERR_MSG("Failed to create QA global instance");
		return DX_MEM_ALLOCATION_ERROR;
	}

	// initialize global instance
	result = initQaGlobalInstance(qaGlobal);
	if (DX_SUCCESS != result)
	{
		ReleaseQaGlobalData(qaGlobal);
		QA_LOG_MSG("%s : initQaGlobalInstance failed", __FUNCTION__);
		return result;
	}

	/* store global instance pointer */
	DxTzService_SetGlobalInstance(qaGlobal);

	/* Callback sequence test :
	   1. iniitalize data struct at CreateContext callback*/
	ClbSequenceDataInit();

	/* 2. write that was CreateContext callback*/
	SetClbSequenceEvent(QA_CREATE_CONTEXT_IDX);

	return result;
}

void SRVXDestroy_impl(void)
//void TA_DestroyEntryPoint(void)
{
	QaGlobalInstance* qaGlobal = (QaGlobalInstance*)DxTzService_GetGlobalInstance();

	SetClbSequenceEvent(QA_DESTROY_CONTEXT_IDX);

	if (DX_SUCCESS != WriteClbSequenceDataToSfs())
	{
		QA_LOG_MSG("%s : WriteCallbackDataToSfs failed", __FUNCTION__);
	}

	ReleaseQaGlobalData(qaGlobal);
}

DxUint32 SRVXOpenClientSession_impl(DxUint32 nParamTypes,
		IN OUT DX_TZ_PARAM pParams[4],
		OUT void** ppSessionContext )
/*DxUint32 TA_OpenSessionEntryPoint(DxUint32 nParamTypes,
		DX_TZ_PARAM pParams[4],
		void** ppSessionContext )*/
{

	QaGlobalInstance* qaGlobal = DX_NULL;
	DxUint32 numOfLoops;

	UNREFERENCED_PARAMETER(ppSessionContext);

	SetClbSequenceEvent(QA_OPEN_SESSION_IDX);

	qaGlobal = (QaGlobalInstance*)DxTzService_GetGlobalInstance();
	if (DX_NULL == qaGlobal)
	{
		QA_ERR_MSG("QA global instance is not created");
		return DX_FAILURE;
	}

	/* number of loops */
	numOfLoops = (DX_TZ_PARAM_TYPE_VALUE_INPUT == DX_TZ_PARAM_TYPE_GET(nParamTypes,0)) ? (pParams[0].value.a) : 10;
	setNumOfLoopsQaGlobalInstance(qaGlobal, numOfLoops);

	return DX_SUCCESS;
}

void SRVXCloseClientSession_impl(IN OUT void* pSessionContext)
//void TA_CloseSessionEntryPoint(void* pSessionContext)
{
	UNREFERENCED_PARAMETER(pSessionContext)

	SetClbSequenceEvent(QA_CLOSE_SESSION_IDX);
}

DxUint32 SRVXInvokeCommand_impl(IN OUT void* pSessionContext,
		DxUint32 nCommandID,
		DxUint32 nParamTypes,
		IN OUT DX_TZ_PARAM pParams[4])
/*DxUint32 TA_InvokeCommandEntryPoint(void* pSessionContext,
		DxUint32 nCommandID,
		DxUint32 nParamTypes,
		DX_TZ_PARAM pParams[4])*/
{
	DxUint32    result = DX_SUCCESS;

	UNREFERENCED_PARAMETER(pSessionContext)
	UNREFERENCED_PARAMETER(nParamTypes);

	if (nCommandID == QA_TST_LOOPBACK){
		return DX_SUCCESS;
	}
	QA_LOG_MSG("**** SRVXInvokeCommand_impl nCommandID=0x%x ****", nCommandID);

    get_mem_usage(1);
	switch (nCommandID){

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_GET_ERR_MSG:
		if (sizeof(QaErrorMessage) != pParams[0].memRef.nSize){

			QA_ERR_MSG("buffer too small to host QaErrorMessage");

			result = DX_TZ_BUFFER_IS_NOT_BIG_ENOUGH;

		} else {

			result = getQaError((QaErrorMessage*)pParams[0].memRef.pBuffer);
		}

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_PARAM_CHECK_VALUE_IN:

		result = paramValueIn(&pParams[0].value, &pParams[1].value, &pParams[2].value, &pParams[3].value);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_PARAM_CHECK_VALUE_INOUT:

		result = paramValueInOut(&pParams[0].value, &pParams[1].value, &pParams[2].value, &pParams[3].value);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_PARAM_CHECK_VALUE_OUT:

		result = paramValueOut(&pParams[0].value, &pParams[1].value, &pParams[2].value, &pParams[3].value);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_PARAM_CHECK_MEMREF_IN:

		result = paramMemRefIn(&pParams[0].memRef, &pParams[1].memRef, &pParams[2].memRef, &pParams[3].memRef);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_PARAM_CHECK_SHARED_MEMREF_INOUT:

		result = paramSharedMemRefInOut(pParams, nParamTypes);

		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_PARAM_CHECK_MEMREF_INOUT:

		result = paramMemRefInOut(&pParams[0].memRef, &pParams[1].memRef, &pParams[2].memRef, &pParams[3].memRef, nParamTypes);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_PARAM_CHECK_MEMREF_OUT:

		result = paramMemRefOut(&pParams[0].memRef, &pParams[1].memRef, &pParams[2].memRef, &pParams[3].memRef);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_ALLOC:

		result = memoryAlloc(pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_REALLOC:

		result = memoryReAlloc(pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_SET:

		result = memorySet(pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_COPY:

		result = memoryCopy(pParams[0].value.a);

		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_REVERSE_COPY:

		result = memoryReverseCopy(pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_COMPARE:

		result = memoryCompare(pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_SHA1:

		result = cryptoSha1((const DxUint8 *) pParams[0].memRef.pBuffer, pParams[0].memRef.nSize, pParams[1].memRef.pBuffer, pParams[2].value.a == 0 ? DX_FALSE : DX_TRUE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_SHA256:

		result=cryptoSha256(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize, pParams[1].memRef.pBuffer, pParams[2].value.a == 0 ? DX_FALSE : DX_TRUE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_MD5:

		if(DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_MEMREF_INPUT	||
				DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_MEMREF_OUTPUT  ||
				DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INPUT	||
				DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_NONE			)
		{
			QA_ERR_MSG("case QA_TST_CRYPTO_MD5 : params are bad");
			result = DX_TZ_BAD_PARAMETERS;
		}
		else
		{
			result=cryptoMD5(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize, pParams[1].memRef.pBuffer, pParams[2].value.a == 0 ? DX_FALSE : DX_TRUE);
		}
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_HMAC_SHA256:

		if(DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_MEMREF_INPUT	||
				DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_MEMREF_INPUT	||
				DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_MEMREF_OUTPUT  ||
				DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_VALUE_INPUT	)
		{
			QA_ERR_MSG("case QA_TST_CRYPTO_HMAC_SHA256 : params are bad");
			result = DX_TZ_BAD_PARAMETERS;
		}
		else
		{
			result=cryptoHmacSha256(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize, // input data
					pParams[1].memRef.pBuffer, pParams[1].memRef.nSize, // input key
					pParams[2].memRef.pBuffer,							// output buffer for digest
					pParams[3].value.a == 0 ? DX_FALSE : DX_TRUE);		// is test block mode
		}
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_CBC_DECRIPT_ALIGNED:

		result = cryptoAES128Cbc(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,/*ENC BUFFER*/
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize, /*DEC BUFFER*/
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize, /*KEY*/
				pParams[2].memRef.pBuffer,pParams[2].memRef.nSize, /*IV*/
				DXCIPHER_DEC,
				DX_TRUE);

		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_ECB_DECRIPT_ALIGNED:

		result = cryptoAES128Ecb(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				DXCIPHER_DEC, DX_TRUE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_CTR_DECRIPT_ALIGNED:

		result = cryptoAES128Ctr(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				pParams[2].memRef.pBuffer,pParams[2].memRef.nSize,
				DXCIPHER_DEC, DX_TRUE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_CBC_ENCRIPT_ALIGNED:

		result = cryptoAES128Cbc(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,/*ENC BUFFER*/
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize, /*DEC BUFFER*/
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize, /*KEY*/
				pParams[2].memRef.pBuffer,pParams[2].memRef.nSize, /*IV*/
				DXCIPHER_ENC,
				DX_TRUE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_ECB_ENCRIPT_ALIGNED:

		result = cryptoAES128Ecb(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				DXCIPHER_ENC, DX_TRUE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_CTR_ENCRIPT_ALIGNED:

		result = cryptoAES128Ctr(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				pParams[2].memRef.pBuffer,pParams[2].memRef.nSize,
				DXCIPHER_ENC, DX_TRUE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_CBC_DECRIPT_NOT_ALIGNED:

		result = cryptoAES128Cbc(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				pParams[2].memRef.pBuffer,pParams[2].memRef.nSize,
				DXCIPHER_DEC, DX_FALSE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_ECB_DECRIPT_NOT_ALIGNED:

		result = cryptoAES128Ecb(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				DXCIPHER_DEC, DX_FALSE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_CTR_DECRIPT_NOT_ALIGNED:

		result = cryptoAES128Ctr(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				pParams[2].memRef.pBuffer,pParams[2].memRef.nSize,
				DXCIPHER_DEC, DX_FALSE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_CBC_ENCRIPT_NOT_ALIGNED:

		result = cryptoAES128Cbc(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				pParams[2].memRef.pBuffer,pParams[2].memRef.nSize,
				DXCIPHER_ENC, DX_FALSE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_ECB_ENCRIPT_NOT_ALIGNED:
		result = cryptoAES128Ecb(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				DXCIPHER_ENC, DX_FALSE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_CTR_ENCRIPT_NOT_ALIGNED:

		result = cryptoAES128Ctr(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize,
				pParams[1].memRef.pBuffer,pParams[1].memRef.nSize,
				pParams[3].memRef.pBuffer,pParams[3].memRef.nSize,
				pParams[2].memRef.pBuffer,pParams[2].memRef.nSize,
				DXCIPHER_ENC, DX_FALSE);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_OAEP_RSA_OAEP_ENCRYPT:
	case QA_TST_CRYPTO_OAEP_RSA_OAEP_DECRYPT:
	case QA_TST_CRYPTO_PKCS1_V1_5_RSA_ENCRYPT:
	case QA_TST_CRYPTO_PKCS1_V1_5_RSA_DECRYPT:

		result = cryptoRSA_encryptionTest(nCommandID, pParams, nParamTypes);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_PSS_RSA_SIGN_VERIFY:
	case QA_TST_CRYPTO_PKCS1_V1_5_RSA_SIGN_VERIFY:

		result = cryptoRSA_signVerify(nCommandID, pParams, nParamTypes);

		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_SECURE_STORAGE_READ_WRITE_TEST:

		result = secureStorage_ReadWriteTest(pParams[0].memRef.pBuffer,
				pParams[1].value.a, pParams[1].value.b);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_SECURE_STORAGE_UPDATE_BUFF_LEN_TEST:

		result = secureStorage_UpdateBuffLenTest(pParams[0].memRef.pBuffer,
				pParams[1].value.a, pParams[1].value.b);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	case QA_TST_SECURE_STORAGE_CREATE_NEW_TEST:

		result = secureStorage_CreateNewFileTest(pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_SECURE_STORAGE_DELETE_TEST:

		result = secureStorage_DeleteFileTest(pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_SECURE_STORAGE_GET_SIZE_TEST:

		result = secureStorage_GetSizeTest(pParams[0].memRef.pBuffer, pParams[1].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CREATE_DEVICE_KEY:

		result = createDeviceKey(pParams[0].value.a,
				pParams[1].memRef.pBuffer,
				pParams[1].memRef.nSize);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_GET_UNIQUE_DEVICE_ID:

		result = GetUniqueDeviceKey(pParams[0].memRef.pBuffer,
				&pParams[0].memRef.nSize);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_IS_DEVICE_ROOTED:

		result = IsDeviceRooted((DxBool)pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_IS_BOOT_LOADER_UNLOCK:

		result = IsBootLoaderUnlock((DxBool)pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_GET_SET_HDCP2_CONNECTION_STATUS:

		result = GetSetHdcp2ConnectionStatus();

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_SECURE_CONTENT_PATH:

		result = MultipaleInitTermSecureContentPath(pParams[0].value.a);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_IS_SECURE_NON_SECURE_CONTENT_MEMORY:

		// Check arguments validity
		if( (DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_VALUE_INPUT) ||
			(DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_VALUE_INPUT) ||
			(DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INPUT)
		  )
		{
			QA_ERR_MSG("case QA_TST_IS_SECURE_NON_SECURE_CONTENT_MEMORY : Bad arguments");

			result = DX_TZ_BAD_PARAMETERS;

			break;
		}

		// Check if the test is performed on a shared buffer or not, and call IsMemorySecuredAsExpected() accordingly
		if (DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) == DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT)	// Shared Buffer
		{
			result = IsMemorySecuredAsExpected( pParams[0].value.a,			// Buffer size
												pParams[1].value.a,			// Should test for secure buffer
												pParams[1].value.b,			// Expected result for secure buffer
												pParams[2].value.a,			// Should test for non secure buffer
												pParams[2].value.b,			// Expected result for non secure buffer
												DX_TRUE,					// Is shared buffer
												&pParams[3].sharedMemRef	// Shared buffer
											  );
		}
		else if (DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) == DX_TZ_PARAM_TYPE_NONE)	// Non Shared Buffer
		{
			result = IsMemorySecuredAsExpected( pParams[0].value.a,	// Buffer size
												pParams[1].value.a,	// Should test for secure buffer
												pParams[1].value.b,	// Expected result for secure buffer
												pParams[2].value.a,	// Should test for non secure buffer
												pParams[2].value.b,	// Expected result for non secure buffer
												DX_FALSE,			// Is shared buffer
												DX_NULL				// Shared buffer
											  );
		}
		else
		{
			QA_ERR_MSG("case QA_TST_IS_SECURE_NON_SECURE_CONTENT_MEMORY : param 3 is bad");
			result = DX_TZ_BAD_PARAMETERS;
		}
		break;

#ifdef SFS_SW_TEST
    case QA_TST_SFS_SW:

        result = testSfsSw (pParams[0].value.a);

        break;
#endif /* SFS_SW_TEST */
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_AES128_OPERATION:

		// first two parameters changed to DxTzServiceSharedMemRef
		result = cryptoAES128Operation(&pParams[0].sharedMemRef, &pParams[1].sharedMemRef, &pParams[2].memRef , pParams[3].value.a, pParams[3].value.b);

		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_PARAM_CHECK_MEMREF_INOUT_REVERSE:

		// first parameter is DxTzServiceSharedMemRef
		if(DX_TZ_PARAM_TYPE_GET(nParamTypes,0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT)
		{
			// if here => pParams[0] is NOT sharedMemRef, so it is error
			QA_ERR_MSG("case QA_TST_PARAM_CHECK_MEMREF_INOUT_REVERSE : pParams[0] is not DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT");
			result = DX_TZ_BAD_PARAMETERS;
		}
		else
		{
			// pParams[0] sent as sharedMemRef
			result = paramMemRefInOutReverse(&pParams[0].sharedMemRef);
		}
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_PARAM_CHECK_UPDATE_BUFFER_SIZE:

		// first parameter is DxTzServiceSharedMemRef
		if(DX_TZ_PARAM_TYPE_GET(nParamTypes,0) != DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT)
		{
			// if here => pParams[0] is NOT sharedMemRef, so it is error
			QA_ERR_MSG("case QA_TST_PARAM_CHECK_UPDATE_BUFFER_SIZE : pParams[0] is not DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT");
			result = DX_TZ_BAD_PARAMETERS;
		}
		else
		{
			// pParams[0] sent as sharedMemRef
			result = paramBufferSizeUpdate(&pParams[0].sharedMemRef, &pParams[1].memRef, &pParams[2].memRef);
		}
		break;



		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_COPY_MEM_TO_EX:
		result = CopyMemToEx(nParamTypes, pParams);
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_COMPARE_MEM_TO_EX:
		result = CompareMemToEx(nParamTypes, pParams);
		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_COPY_EX_TO_MEM:
		result = CopyExToMem(nParamTypes, pParams);
		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_COMPARE_EX_TO_MEM:
		result = CompareExToMem(nParamTypes, pParams);
		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_COPY_EX_TO_EX:
		result = CopyExToEx(nParamTypes, pParams);
		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_COMPARE_EX_TO_EX:
		result = CompareExToEx(nParamTypes, pParams);
		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_MEMORY_SET_EX:
		result = SetExMem(nParamTypes,pParams);
		break;




		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_AES_CTR_MEM_TO_EX:
		result = AES_BlockCipher_ExMemoryOperations(nParamTypes,pParams, QA_TST_AES_CTR_MEM_TO_EX);
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_AES_CTR_EX_TO_MEM:
		result = AES_BlockCipher_ExMemoryOperations(nParamTypes,pParams, QA_TST_AES_CTR_EX_TO_MEM);
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_AES_CTR_EX_TO_EX:
		result = AES_BlockCipher_ExMemoryOperations(nParamTypes,pParams, QA_TST_AES_CTR_EX_TO_EX);
		break;




		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_AES_CBC_MEM_TO_EX:
		result = AES_BlockCipher_ExMemoryOperations(nParamTypes,pParams, QA_TST_AES_CBC_MEM_TO_EX);
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_AES_CBC_EX_TO_MEM:
		result = AES_BlockCipher_ExMemoryOperations(nParamTypes,pParams, QA_TST_AES_CBC_EX_TO_MEM);
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_AES_CBC_EX_TO_EX:
		result = AES_BlockCipher_ExMemoryOperations(nParamTypes,pParams, QA_TST_AES_CBC_EX_TO_EX);
		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_NON_CONTIGUOUS_BUFFERS_CTR:

		// convert pParams

		result = AES_BlockCipher_NonContiguousBuffersOperations(nParamTypes,pParams, QA_TST_NON_CONTIGUOUS_BUFFERS_CTR);

		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_NON_CONTIGUOUS_BUFFERS_CBC:

		// convert pParams

		result = AES_BlockCipher_NonContiguousBuffersOperations(nParamTypes,pParams, QA_TST_NON_CONTIGUOUS_BUFFERS_CBC);
		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_AES_BLOCK_CIPHER_INIT:
		result = AES_BlockCipher_Init(nParamTypes,pParams);
		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_AES_BLOCK_CIPHER_FINISH:
		result = AES_BlockCipher_Finish();
		break;


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CALLBACK_SEQUENCE_INVOKE_COMMAND:
		SetClbSequenceEvent(QA_INVOKE_COMMAND_IDX);
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CALLBACK_SEQUENCE_READ_FROM_SFS:

		// first parameter is DxTzServiceSharedMemRef
		if(DX_TZ_PARAM_TYPE_GET(nParamTypes,0) != DX_TZ_PARAM_TYPE_MEMREF_INOUT)
		{
			// if here => pParams[0] is NOT sharedMemRef, so it is error
			QA_ERR_MSG("case QA_TST_CALLBACK_SEQUENCE_READ_FROM_SFS : pParams[0] is not DX_TZ_PARAM_TYPE_MEMREF_INOUT");
			result = DX_TZ_BAD_PARAMETERS;
		}
		else
		{
			// pParams[0] sent as sharedMemRef
			result = ReadClbSequenceDataFromSfs(&pParams[0].memRef);
		}
		break;

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CALLBACK_SEQUENCE_DELETE_FROM_SFS:

		result = DeleteClbSequenceDataFromSfs();
		break;

	    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_CRYPTO_RANDOM_NUM_GEN:
		result = cryptoRandomGenerate(pParams[0].memRef.pBuffer, pParams[0].memRef.nSize);
		break;

	    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_IS_AUDIO_PACKET_API:
	{
		DxUint8 IV_Nonce_Counter[16] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
		DxBool 	bResult 			 = DX_TRUE;



		result =  DxTzService_IsAudioPacket( &(pParams[0].sharedMemRef),
											 pParams[1].value.a,							// uiDataOffset
											 pParams[1].value.b,							// uiDataSize
											 pParams[2].value.b,							// Stream Type - Used as expected sum result for the test
											 (EDxTzCipherAlgorithm_t)pParams[2].value.a,	// Cipher algorithm	[DX_TZ_CIPHER_ALG_AES128CBC / DX_TZ_CIPHER_ALG_AES128CTR]
											 IV_Nonce_Counter,
											 &bResult
										   );

		break;
	}



    	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case QA_TST_HDMI_STATUS_API:
	{
		result = hdmiStatusTest(pParams);
		break;
	}


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	default:
		QA_ERR_MSG("Unknown test case 0x%08X", nCommandID);
		result = DX_FAILURE;
		break;
	}

    get_mem_usage(1);

	return result;
}


