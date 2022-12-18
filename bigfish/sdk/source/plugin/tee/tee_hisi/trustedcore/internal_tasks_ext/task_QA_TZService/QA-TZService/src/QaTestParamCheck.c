#include "QaTestFuncDeclaration.h"
#include "DxTzServiceAPI.h"
#include "QaUtils.h"
DxStatus paramValueIn(DxTzServiceValue *param1, DxTzServiceValue *param2, DxTzServiceValue *param3, DxTzServiceValue *param4){

    DxStatus result = DX_SUCCESS;

    if ((param1->b != (param1->a+1)) ||
        (param2->a != (param1->a+2)) ||
        (param2->b != (param1->a+3)) ||
        (param3->a != (param1->a+4)) ||
        (param3->b != (param1->a+5)) ||
        (param4->a != (param1->a+6)) ||
        (param4->b != (param1->a+7)) )  {

        result = DX_FAILURE;

        REPORT_ERROR0("value in received unexpected value");
    }

    //change values to insure they wont be changed in caller function
    param1->a++;

    param1->b++;

    param2->a++;

    param2->b++;

    param3->a++;

    param3->b++;

    param4->a++;

    param4->b++;

    return result;
}

DxStatus paramValueInOut( DxTzServiceValue *param1, DxTzServiceValue *param2, DxTzServiceValue *param3, DxTzServiceValue *param4 ){
    DxStatus result = DX_SUCCESS;
    if ((param1->b != (param1->a+1)) ||
        (param2->a != (param1->a+2)) ||
        (param2->b != (param1->a+3)) ||
        (param3->a != (param1->a+4)) ||
        (param3->b != (param1->a+5)) ||
        (param4->a != (param1->a+6)) ||
        (param4->b != (param1->a+7)) ){

        REPORT_ERROR0("value inout received unexpected value");

        result = DX_FAILURE;
    }

    param1->a++;

    param1->b++;

    param2->a++;

    param2->b++;

    param3->a++;

    param3->b++;

    param4->a++;

    param4->b++;

    return result;

}

DxStatus paramValueOut( DxTzServiceValue *param1, DxTzServiceValue *param2, DxTzServiceValue *param3, DxTzServiceValue *param4 ){

    param1->a = 1000;
    param1->b = param1->a + 1;

    param2->a = param1->a + 2;
    param2->b = param1->a + 3;

    param3->a = param1->a + 4;
    param3->b = param1->a + 5;

    param4->a = param1->a + 6;
    param4->b = param1->a + 7;

    return DX_SUCCESS;
}

DxStatus paramMemRefIn( DxTzServiceMemRef *param1, DxTzServiceMemRef *param2, DxTzServiceMemRef *param3, DxTzServiceMemRef *param4 ){
    DxStatus result = DX_SUCCESS;

	const DxUint32 hlosBufferLength = 11;

    if ((param1->nSize != hlosBufferLength) || (0 != DxTzService_MemCmp((DxChar*)param1->pBuffer, "inbuffer1", hlosBufferLength-1))||
        (param2->nSize != hlosBufferLength) || (0 != DxTzService_MemCmp((DxChar*)param2->pBuffer, "inbuffer2", hlosBufferLength-1))||
        (param3->nSize != hlosBufferLength) || (0 != DxTzService_MemCmp((DxChar*)param3->pBuffer, "inbuffer3", hlosBufferLength-1))||
        (param4->nSize != hlosBufferLength) || (0 != DxTzService_MemCmp((DxChar*)param4->pBuffer, "inbuffer4", hlosBufferLength-1))){

         result = DX_FAILURE;

         REPORT_ERROR0("memref in received unexpected value");

    }


    return result;
}

DxStatus paramMemRefInOut( DxTzServiceMemRef *param1, DxTzServiceMemRef *param2, DxTzServiceMemRef *param3, DxTzServiceMemRef *param4, DxUint32 nParamTypes)
{
	const DxUint32 hlosBufferLength = 11;

    if (DX_TZ_PARAM_TYPE_GET(nParamTypes,3) != DX_TZ_PARAM_TYPE_NONE){
        QA_LOG_MSG("param 3 is not NONE");
        if ((param4->nSize != hlosBufferLength) || (0 != DxTzService_MemCmp((DxChar*)param4->pBuffer, "inbuffer4", hlosBufferLength-1))){

            REPORT_ERROR0("memref inout received unexpected value");

            return DX_FAILURE;

        }

    } else {

        param4 = DX_NULL;
    }

    if (DX_TZ_PARAM_TYPE_GET(nParamTypes,2) != DX_TZ_PARAM_TYPE_NONE){

        QA_LOG_MSG("param 2 is not NONE");

        if ((param3->nSize != hlosBufferLength) || (0 != DxTzService_MemCmp((DxChar*)param3->pBuffer, "inbuffer3", hlosBufferLength-1))){

            REPORT_ERROR0("memref inout received unexpected value");

            return DX_FAILURE;

        }

    } else {

        param3 = DX_NULL;
    }

    if (DX_TZ_PARAM_TYPE_GET(nParamTypes,1) != DX_TZ_PARAM_TYPE_NONE){

        QA_LOG_MSG("param 1 is not NONE");

        if ((param2->nSize != hlosBufferLength) || (0 != DxTzService_MemCmp((DxChar*)param2->pBuffer, "inbuffer2", hlosBufferLength-1))){

            REPORT_ERROR0("memref inout received unexpected value");

            return DX_FAILURE;

        }
    }
    else {

        param2 = DX_NULL;
    }

    if (DX_TZ_PARAM_TYPE_GET(nParamTypes,0) != DX_TZ_PARAM_TYPE_NONE){

        QA_LOG_MSG("param 0 is not NONE");

        if ((param1->nSize != hlosBufferLength) || (0 != DxTzService_MemCmp((DxChar*)param1->pBuffer, "inbuffer1", hlosBufferLength-1))){

            REPORT_ERROR0("memref inout received unexpected value");

            return DX_FAILURE;

        }

    } else {

        param1 = DX_NULL;
    }

    return paramMemRefOut(param1, param2, param3, param4);
}




static void paramSharedMemRefInOut_clean(DxUint32 fromIdx, DxUint32 limitIdx, DxChar *pParamBufferArr[])
{
	for( /*empty*/; fromIdx<limitIdx; fromIdx++)
	{
		if(pParamBufferArr[fromIdx] != DX_NULL)
		{
			DxTzService_Free(pParamBufferArr[fromIdx]);
		}
	}
}



static void paramSharedMemRefInOut_printAndCleanAfterError(const DxChar *errorStr, DxUint32 fromIdx, DxUint32 limitIdx, DxChar *pParamBufferArr[])
{
	DxHwLogTrace(DX_FALSE, errorStr);
	paramSharedMemRefInOut_clean(fromIdx, limitIdx, pParamBufferArr);
}


DxStatus paramSharedMemRefInOut( DxTzServiceParameter pParams[], DxUint32 nParamTypes)
{
	const DxUint32 hlosBufferLength = 11; // length of buffers gotten from HLOS

	// array of buffers
	DxChar *pParamBufferArr[DX_TZ_OPERATION_NUM_PARAMS] = {0};


	// array of SharedMemRef handlers
	DxTzServiceSharedMemRef pParamsSharedMemRefArr[DX_TZ_OPERATION_NUM_PARAMS];

	// output buffer filling string : outbuffer'i+1' will be written in output buffer, and this pattern will be checked by HLOS
	DxChar outbufferString[] = "outbuffer#";

	// input buffer validation string : if pParams[i].sharedBuffer.buffer != inbuffer'i+1' => buffer corrupted
	DxChar inbufferString[] =  "inbuffer#";

	DxStatus operationStatus;

	DxInt32 idx;


	for(idx = DX_TZ_OPERATION_NUM_PARAMS-1; idx>=0; idx--)
	{
		// 1. validate that buffer received correctly
		if (DX_TZ_PARAM_TYPE_GET(nParamTypes,idx) == DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT)
		{
			QA_LOG_MSG("param %d is not NONE",idx);

			// allocate memory for paramBuffer at idx
			if((pParamBufferArr[idx] = (DxChar *)DxTzService_Malloc(hlosBufferLength)) == DX_NULL)
			{
				paramSharedMemRefInOut_printAndCleanAfterError("paramSharedMemRefInOut: DxTzService_Malloc failed", idx+1,
																DX_TZ_OPERATION_NUM_PARAMS, pParamBufferArr);
				return DX_MEM_ALLOCATION_ERROR;
			}

			// create handle and copy memory from pParams[idx].sharedMemRef to pParamBufferArr[idx] via pParamsSharedMemRefArr[idx]
			if( DX_SUCCESS != (operationStatus = CreateAndCopySharedMemRef( &pParamsSharedMemRefArr[idx], (DxByte *)pParamBufferArr[idx], &(pParams[idx].sharedMemRef), 0, hlosBufferLength)) )
			{
				paramSharedMemRefInOut_printAndCleanAfterError("paramSharedMemRefInOut: CreateAndCopySharedMemRef failed", idx+1,
																DX_TZ_OPERATION_NUM_PARAMS, pParamBufferArr);

				return operationStatus;
			}

			// build buffer received from HLOS validation string
			inbufferString[hlosBufferLength-3] = (DxChar)('1'+idx);

			// validate that buffer received from HLOS has appropriate length and contains appropriate string
			if (( pParams[idx].sharedMemRef.nSize != hlosBufferLength) || (0 != DxTzService_MemCmp((DxChar*)pParamBufferArr[idx], inbufferString, hlosBufferLength-1)))
			{
				paramSharedMemRefInOut_printAndCleanAfterError("paramSharedMemRefInOut: DxsharedMemRef has unexpected value", idx+1,
																DX_TZ_OPERATION_NUM_PARAMS, pParamBufferArr);

				REPORT_ERROR0("paramSharedMemRefInOut: sharedMemRef.nSize has unexpected value");
				return DX_FAILURE;
			}

			// 2. copy outbuffer'idx+1' pattern in to output buffer

			// build input buffer
			outbufferString[hlosBufferLength-2] = (DxChar)('1'+idx);


			// copy string to pParamBufferArr[idx]
			DxTzService_MemCpy(pParamBufferArr[idx], outbufferString, hlosBufferLength);

			if( (operationStatus = DxTzService_MemCpyEx(&(pParams[idx].sharedMemRef), 0, &(pParamsSharedMemRefArr[idx]), 0, hlosBufferLength)) != DX_SUCCESS)
			{
				// memcopy failed -> clean and exit
				paramSharedMemRefInOut_printAndCleanAfterError("paramSharedMemRefInOut: DxTzService_MemCpyEx failed", idx+1,
																DX_TZ_OPERATION_NUM_PARAMS, pParamBufferArr);
				return operationStatus;
			}

		}
		else
		{
			// validate that param is DX_TZ_PARAM_TYPE_NONE and not something unexpected
			if (DX_TZ_PARAM_TYPE_GET(nParamTypes,idx) != DX_TZ_PARAM_TYPE_NONE)
			{
				paramSharedMemRefInOut_printAndCleanAfterError("paramSharedMemRefInOut: nParamTypes has unexpected value", idx+1,
																DX_TZ_OPERATION_NUM_PARAMS, pParamBufferArr);

				REPORT_ERROR0("paramSharedMemRefInOut: sharedMemRef.nSize has unexpected value");
				return DX_FAILURE;
			}
		}
	}

	// 3. release all allocated buffers
	paramSharedMemRefInOut_clean(0,DX_TZ_OPERATION_NUM_PARAMS,pParamBufferArr);


	return DX_SUCCESS;
}


DxStatus paramMemRefOut( DxTzServiceMemRef *param1, DxTzServiceMemRef *param2, DxTzServiceMemRef *param3, DxTzServiceMemRef *param4 ){
    DxStatus result = DX_SUCCESS;


    if (DX_NULL != param1)
        DxTzService_MemCpy((DxChar*)param1->pBuffer,"outbuffer1",param1->nSize);

    if (DX_NULL != param2)
        DxTzService_MemCpy((DxChar*)param2->pBuffer,"outbuffer2",param2->nSize);

    if (DX_NULL != param3)
        DxTzService_MemCpy((DxChar*)param3->pBuffer,"outbuffer3",param3->nSize);

    if (DX_NULL != param4)
        DxTzService_MemCpy((DxChar*)param4->pBuffer,"outbuffer4",param4->nSize);

    return result;
}




static DxStatus ReverseLeftChunkWithRightChunk(DxTzServiceSharedMemRef * inputHandlePtr, DxUint32 leftOffsetBytes, DxUint32 rightOffsetBytes,
											   DxByte *leftBuffer, DxByte *rightBuffer, DxByte *tmpBuffer, DxUint32 bufferSizeBytes)
{
	DxTzServiceSharedMemRef leftHandle, rightHandle;
	DxStatus operationStatus;
	DxUint32 *tmpBufferSource, *leftBufferDest, *rightBufferSource;

	if(bufferSizeBytes%sizeof(DxUint32) != 0)
	{
		QA_LOG_MSG("ReverseLeftChunkWithRightChunk: buffer must be multiplication of sizeof(DxUint32), but bufferSizeBytes=%d",bufferSizeBytes);
		return DX_BAD_ARGUMENTS;
	}



	if(leftBuffer==DX_NULL || rightBuffer==DX_NULL || tmpBuffer==DX_NULL)
	{
		QA_LOG_MSG("ReverseLeftChunkWithRightChunk: NULL parameters (%d,%d,%d)",leftBuffer,rightBuffer,tmpBuffer);
		return DX_BAD_ARGUMENTS;
	}



	if(DX_SUCCESS != (operationStatus = CreateAndCopySharedMemRef(&leftHandle, leftBuffer, inputHandlePtr, leftOffsetBytes, bufferSizeBytes)))
	{
		QA_LOG_MSG("ReverseLeftChunkWithRightChunk: CreateAndCopySharedMemRef 1 failed");
		return operationStatus;
	}



	if(DX_SUCCESS != (operationStatus = CreateAndCopySharedMemRef(&rightHandle, rightBuffer, inputHandlePtr, rightOffsetBytes, bufferSizeBytes)))
	{
		QA_LOG_MSG("ReverseLeftChunkWithRightChunk: CreateAndCopySharedMemRef 2 failed");
		return operationStatus;
	}




	// buckup left buffer in tmpBuffer
	DxTzService_MemCpy(tmpBuffer,leftBuffer,bufferSizeBytes);



	// coping :
	//	1. from [END OF RIGHT BUFFER] to [START OF LEFT BUFFER]
	//	2. from [START OF TMP BUFFER] to [END OF RIGHT BUFFER]
	//  when TMP BUFFER is a copy of LEFT BUFFER
	for( tmpBufferSource = (DxUint32 *)tmpBuffer, leftBufferDest = (DxUint32 *)leftBuffer, rightBufferSource = (DxUint32 *)( rightBuffer + bufferSizeBytes - sizeof(DxUint32));
		 leftBufferDest < ((DxUint32 *)(leftBuffer + bufferSizeBytes));
		 --rightBufferSource, ++leftBufferDest, ++tmpBufferSource)
	{
		*leftBufferDest = *rightBufferSource;

		*rightBufferSource = *tmpBufferSource;
	}

	// put content of tmpLeftBuffer to offset leftOffset in inputHandlePtr
	if(DX_SUCCESS != (operationStatus = DxTzService_MemCpyEx(inputHandlePtr, leftOffsetBytes, &leftHandle, 0, bufferSizeBytes)))
	{
		QA_LOG_MSG("ReverseLeftChunkWithRightChunk: DxTzService_MemCpyEx left failed");
		return operationStatus;
	}


	// put content of tmpRightBuffer to offset rightOffset in inputHandlePtr
	if(DX_SUCCESS != (operationStatus = DxTzService_MemCpyEx(inputHandlePtr, rightOffsetBytes, &rightHandle, 0, bufferSizeBytes)))
	{
		QA_LOG_MSG("ReverseLeftChunkWithRightChunk: DxTzService_MemCpyEx right failed");
		return operationStatus;
	}

	// everything succeed, clean and return success
	return DX_SUCCESS;
}




static void ReverseLeftChunkWithRightChunk_ReleaseBuffers(void* buff1, void* buff2, void* buff3)
{
	DxTzService_Free(buff1);
	DxTzService_Free(buff2);
	DxTzService_Free(buff3);
}


DxStatus paramMemRefInOutReverse(DxTzServiceSharedMemRef * inputHandlePtr)
{
    const DxInt32 MAXIMAL_SAFELY_ALLOCTED_SIZE_BYTES = 128;		// size of memory chunk which can be safely allocated with DxTzService_Malloc
    DxUint32 workingBufferSizeBytes;							// size, that less or equal to MAXIMAL_SAFELY_ALLOCTED_SIZE
	DxInt32 leftOffsetBytes=0;										// offset from the left  end of buffer pointed by inputHandlePtr
    DxInt32 rightOffsetBytes=inputHandlePtr->nSize;					// offset from the right end of buffer pointed by inputHandlePtr
    DxInt32 amountOfWorkBytes = inputHandlePtr->nSize;			// overall amount of bytes to reverse
	DxStatus operationStatus;

	DxByte *leftBuffer	=	(DxByte*)DxTzService_Malloc(MAXIMAL_SAFELY_ALLOCTED_SIZE_BYTES);
	DxByte *rightBuffer =	(DxByte*)DxTzService_Malloc(MAXIMAL_SAFELY_ALLOCTED_SIZE_BYTES);
	DxByte *tmpBuffer	=	(DxByte*)DxTzService_Malloc(MAXIMAL_SAFELY_ALLOCTED_SIZE_BYTES);

	// allocations of buffers for performing reverse
	if(leftBuffer==DX_NULL || rightBuffer==DX_NULL || tmpBuffer==DX_NULL)
	{
        QA_LOG_MSG("paramMemRefInOutReverse: DxTzService_Malloc failed\n");
		ReverseLeftChunkWithRightChunk_ReleaseBuffers(leftBuffer,rightBuffer,tmpBuffer);
		return DX_MEM_ALLOCATION_ERROR;
	}


    /*  while we can continue to work with maximal possible workingBuffer -
		reverse workingBufferSizeBytes from end with workingBufferSizeBytes from start of inputHandlePtr */
    while(amountOfWorkBytes>1)
    {
        // calculate workingBufferSizeBytes : it can't be bigger than MAXIMAL_SAFELY_ALLOCTED_SIZE_BYTES
        workingBufferSizeBytes = (MAXIMAL_SAFELY_ALLOCTED_SIZE_BYTES * 2 <= amountOfWorkBytes)?
                            MAXIMAL_SAFELY_ALLOCTED_SIZE_BYTES :
                            (DxUint32)(amountOfWorkBytes/2);

        // update rightOffset to point workingBufferSizeBytes backward
        rightOffsetBytes -= workingBufferSizeBytes;

        if(DX_SUCCESS != (operationStatus = ReverseLeftChunkWithRightChunk( inputHandlePtr, leftOffsetBytes, rightOffsetBytes,
																			leftBuffer, rightBuffer, tmpBuffer, workingBufferSizeBytes)))
		{
	        QA_LOG_MSG("paramMemRefInOutReverse: ReverseLeftChunkWithRightChunk failed\n");
			ReverseLeftChunkWithRightChunk_ReleaseBuffers(leftBuffer,rightBuffer,tmpBuffer);
			return operationStatus;
		}

        leftOffsetBytes += workingBufferSizeBytes;

        amountOfWorkBytes -= (2*workingBufferSizeBytes);
    }

	ReverseLeftChunkWithRightChunk_ReleaseBuffers(leftBuffer,rightBuffer,tmpBuffer);

	return DX_SUCCESS;
}



DxStatus paramBufferSizeUpdate(DxTzServiceSharedMemRef *sharedMemRefParam, DxTzServiceMemRef *param2, DxTzServiceMemRef *param3)
{
	DxByte i;
    DxByte* inOutBuffer = (DxByte*)(param2->pBuffer);
    DxByte* outBuffer   = (DxByte*)(param3->pBuffer);

    sharedMemRefParam->nSize = sharedMemRefParam->nSize - sizeof(DxUint32);

    param2->nSize = param2->nSize - 1;

    param3->nSize = param3->nSize - 1;

    paramMemRefInOutReverse(sharedMemRefParam);

    for (i = 0; i < param3->nSize; i++) {
        inOutBuffer[i]=i + 1;
        outBuffer[i]=i;
    }
    return DX_SUCCESS;
}

