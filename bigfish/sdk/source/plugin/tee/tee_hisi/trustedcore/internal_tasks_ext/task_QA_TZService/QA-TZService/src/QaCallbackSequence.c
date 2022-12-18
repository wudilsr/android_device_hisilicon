#include "QaCallbackSequence.h"
#include "QaTestDataStruct.h"
#include "DxTzServiceAPI.h"
#include "QaUtils.h"


void ClbSequenceDataInit(void)
{
	QA_TZ_ClbSequenceData * clbSequenceDataPtr = &(((QaGlobalInstance *)DxTzService_GetGlobalInstance())->clbSequenceData);

	DxTzService_MemSet(	clbSequenceDataPtr->clbSequenceArr, 0x00, sizeof(QaClbSecuenceValueArray) );

	clbSequenceDataPtr->fileName = "CalbackSequenceDataFile";

	clbSequenceDataPtr->wasClbSecuenceCmdSent = DX_FALSE;
	clbSequenceDataPtr->sequentialNumber = SEQUENTIAL_NUMBER_INIT_VALUE;
}


/* this functiuon called from SRVX_XXXXX callbacks */
void SetClbSequenceEvent(EQaClbSecuenceIndex callbackType)
{
	QA_TZ_ClbSequenceData * clbSequenceDataPtr = &((QaGlobalInstance *)DxTzService_GetGlobalInstance())->clbSequenceData;

	if(callbackType==QA_INVOKE_COMMAND_IDX)
	{
		/* if here, so Callbak Secuence Test is activated, so recognize this in wasClbSecuenceCmdSent */
		clbSequenceDataPtr->wasClbSecuenceCmdSent=DX_TRUE;
	}

	/* fill appropriate cell in array */
	clbSequenceDataPtr->clbSequenceArr[callbackType] = clbSequenceDataPtr->sequentialNumber;
	++clbSequenceDataPtr->sequentialNumber;
}


DxStatus WriteClbSequenceDataToSfs(void)
{
	QA_TZ_ClbSequenceData * clbSequenceDataPtr = &((QaGlobalInstance *)DxTzService_GetGlobalInstance())->clbSequenceData;

	DxStatus result;

	/* check if QA_TST_CALLBACK_SEQUENCE_INVOKE_COMMAND was sent,
	 * if yes,this is CALLBACK_SEQUENCE test, and we need to write data to SFS */

	if( ! clbSequenceDataPtr->wasClbSecuenceCmdSent)
	{
		/* this is not CALLBACK_SEQUENCE test, do nothing here*/
		return DX_SUCCESS;
	}

	result = DxTzService_WriteToSecureStorage( clbSequenceDataPtr->fileName, (DxByte*)(&(clbSequenceDataPtr->clbSequenceArr)), sizeof(QaClbSecuenceValueArray));
    if (DX_SUCCESS != result)
    {
    	QA_LOG_MSG("%s : DxTzService_WriteToSecureStorage failed, returned 0x%x", __FUNCTION__, result);
    	return result;
    }

    return DX_SUCCESS;
}


DxStatus ReadClbSequenceDataFromSfs(DxTzServiceMemRef *memRefBufferPtr)
{
	QA_TZ_ClbSequenceData * clbSequenceDataPtr = &((QaGlobalInstance *)DxTzService_GetGlobalInstance())->clbSequenceData;

	DxStatus result;
	QaClbSecuenceValueArray localBuf = {0};
	DxUint32 bufferLen = sizeof(QaClbSecuenceValueArray);

	if(memRefBufferPtr->nSize < bufferLen)
	{
    	QA_LOG_MSG("%s : memRefBufferPtr has length %d, %d bytes at least required", __FUNCTION__, memRefBufferPtr->nSize, bufferLen);
    	return DX_TZ_BAD_PARAMETERS;
	}

	/* 1. read file from sfs */
	result = DxTzService_ReadFromSecureStorage(clbSequenceDataPtr->fileName,  (DxByte*)(&localBuf), &bufferLen);
    if (DX_SUCCESS != result)
    {
    	QA_LOG_MSG("%s : DxTzService_ReadFromSecureStorage failed, returned 0x%x", __FUNCTION__, result);
    	return result;
    }

	/* 2. copy data to user */
    DxTzService_MemCpy( memRefBufferPtr->pBuffer, localBuf, bufferLen);

    /* 3. delete file from sfs after read */
    result = DeleteClbSequenceDataFromSfs();
    if (DX_SUCCESS != result)
    {
       	QA_LOG_MSG("%s : DeleteClbSequenceDataFromSfs failed, returned 0x%x", __FUNCTION__, result);
      	return result;
    }

    return DX_SUCCESS;
}


DxStatus DeleteClbSequenceDataFromSfs(void)
{
	QA_TZ_ClbSequenceData * clbSequenceDataPtr = &((QaGlobalInstance *)DxTzService_GetGlobalInstance())->clbSequenceData;

	DxStatus result;

	result = DxTzService_WriteToSecureStorage(clbSequenceDataPtr->fileName, DX_NULL, 0);
	if (result != DX_SUCCESS)
	{
		QA_ERR_MSG("%s: delete SFS file failed with error code: 0x%x", __FUNCTION__, result);
	}



	return result;
}
