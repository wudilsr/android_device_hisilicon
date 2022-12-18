#include "QaUtils.h"
#include "DxTzService_Utils.h"


//////////////////////////////////////////////////////////////////////////
DxUint32 power(DxUint32 number, DxUint32 power){
    DxUint32 result = number;

    if (0 == number){

        return 0;
    }

    if (0 == power){

        return 1;
    }

    while (--power > 0){

        result *= number;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////
void reportError(const DxChar* file, DxUint32 line, const DxChar* func, const DxChar* msg){

    reportError3(file, line, func, msg, 0, 0, 0);
}

//////////////////////////////////////////////////////////////////////////
void reportError1(const DxChar* file, DxUint32 line, const DxChar* func, const DxChar* format, DxUint32 param1){

    reportError3(file, line, func, format, param1, 0, 0);
}

//////////////////////////////////////////////////////////////////////////
void reportError2(const DxChar* file, DxUint32 line, const DxChar* func, const DxChar* format, DxUint32 param1, DxUint32 param2){

    reportError3(file, line, func, format, param1, param2, 0);

}

//////////////////////////////////////////////////////////////////////////
void reportError3(const DxChar* file, DxUint32 line, const DxChar* func, const DxChar* format, DxUint32 param1, DxUint32 param2, DxUint32 param3){
    QaGlobalInstance* qaGlobal = DxTzService_GetGlobalInstance();

    if ((DX_NULL == qaGlobal) || (DX_NULL == qaGlobal->qaErrMsg)){

    	QA_ERR_MSG("qaError handler not set!");

    } else {

        //we are only interested in first error message - so in case it is already filled we won't overwrite it
        // we assuming that HLOS test will reset the buffer before calling the service
        if (0 == qaGlobal->qaErrMsg->mesageFormat[0]){

            DxTzService_MemCpy(qaGlobal->qaErrMsg->mesageFormat, format, qaStrlen(format)+1);

            DxTzService_MemCpy(qaGlobal->qaErrMsg->file, file, qaStrlen(file)+1);

            DxTzService_MemCpy(qaGlobal->qaErrMsg->funcName, func, qaStrlen(func)+1);

            qaGlobal->qaErrMsg->line = line;

            qaGlobal->qaErrMsg->param1 = param1;

            qaGlobal->qaErrMsg->param2 = param2;

            qaGlobal->qaErrMsg->param3 = param3;

        } else {

        	QA_LOG_MSG("error ignored - already set!");
        }

    }

}

//////////////////////////////////////////////////////////////////////////
DxUint32 qaStrlen(const DxChar* str){
    DxUint32 charCounter = 0;

    if (DX_NULL == str){

        return 0;
    }

    while ((charCounter < 1024) && (0 != str[charCounter])){

        charCounter ++;
    }

    return charCounter;

}





//////////////////////////////////////////////////////////////////////////
DxStatus initQaGlobalInstance( QaGlobalInstance* qaGlobal)
{

	QA_LOG_MSG("allocate QaErrorMessage");
	qaGlobal->qaErrMsg = (QaErrorMessage*)DxTzService_Malloc(sizeof(QaErrorMessage));
	if (DX_NULL == qaGlobal->qaErrMsg)
	{
		QA_ERR_MSG("failed to allocate buffer for QaErrorMessage struct");
		return DX_TZ_MEM_ALLOCATION_ERROR;
	}

	//init QA error buffer
	DxTzService_MemSet(qaGlobal->qaErrMsg->mesageFormat, 0, sizeof(QaErrorMessage));

    return DX_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////
DxStatus setNumOfLoopsQaGlobalInstance( QaGlobalInstance* qaGlobal, DxUint32 numOfLoops )
{
	if (DX_NULL == qaGlobal)
	{
		QA_ERR_MSG("%s: qaGlobal is NULL");
		return DX_TZ_BAD_PARAMETERS;
	}

	qaGlobal->muxNumOfLoops = numOfLoops;

	return DX_SUCCESS;
}




void terminateQaGlobalInstance(QaGlobalInstance* qaGlobal)
{
	if (DX_NULL == qaGlobal->qaErrMsg){//reset QA ERROR MSG

		QA_LOG_MSG("reset QaErrorMessage");

		DxTzService_MemSet(qaGlobal->qaErrMsg->mesageFormat, 0, sizeof(QaErrorMessage));
	}

	DxTzService_Free(qaGlobal->qaErrMsg);
}

//////////////////////////////////////////////////////////////////////////////////
//Clean memory at the end of the Expand buffer functions
// free up to 3 buffers
void onCleenupExpandBuffers(DxUint8 * buff1,DxUint8 * buff2, DxUint8 * buff3 ){

    if (buff1 != DX_NULL)
        DxTzService_Free(buff1);

    if (buff2 != DX_NULL)
        DxTzService_Free(buff2);

    if (buff3 != DX_NULL)
        DxTzService_Free(buff3);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Create an extended buffer part and fill it with ascending numbers between 0-MAX(DxUint8)
DxUint8 * createExtendedBuff(DxUint32 size){

    DxUint8 * aExtendedBuff = DX_NULL;
    DxUint32 index=0;

    //creating the extending buf and initialize it
    aExtendedBuff = DxTzService_Malloc(size);

    if (aExtendedBuff==DX_NULL){

        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory 0x%08X", size);

        return DX_NULL;
    }

    for(index = 0; index<size; index++){

        aExtendedBuff[index]=(DxUint8)index;

    }

    return aExtendedBuff;
}

//////////////////////////////////////////////////////////////////////////////////////////
//for the propose of releasing the buffer which was created with CreateExtendedBuff
DxStatus destroyExtendedBuff(DxUint8 * aBuff){

    if(aBuff != DX_NULL)
        DxTzService_Free(aBuff);

    return DX_SUCCESS;
}


DxUint8 * expandTestingDataWithDummyBuffers(const DxUint8 *aBuffer, DxUint32 aOriginalBufferLength, DxUint32 aExtendedLength, EExtendBufferSide leftOrRightSide){

    //calculate number of extensions
    DxUint32 extSize=aExtendedLength;
    DxUint8 * aNewBuff = DX_NULL;
    DxUint8 * aExtendedBuff = DX_NULL;
    DxUint8 * aNewBuffCopyPosition = DX_NULL;

    //creating the extending buf and initialize it
    aExtendedBuff = createExtendedBuff(aExtendedLength);

    if (aExtendedBuff==DX_NULL)

        return DX_NULL;

    //if it is both side extension then we overwrite the extSize with double length
    if(leftOrRightSide !=eEXTEND_TO_LEFT_SIDE && leftOrRightSide !=eEXTEND_TO_RIGHT_SIDE){

        extSize=2*aExtendedLength;
    }

    //creating a new buffer
    aNewBuff = DxTzService_Malloc(aOriginalBufferLength+extSize);

    if (aNewBuff == DX_NULL){

        onCleenupExpandBuffers(aExtendedBuff, DX_NULL, DX_NULL);

        return DX_NULL;
    }

    aNewBuffCopyPosition = aNewBuff;

    //populate the buffer with the correct data
    if(leftOrRightSide ==eEXTEND_TO_LEFT_SIDE || leftOrRightSide !=eEXTEND_TO_RIGHT_SIDE){ //if left size

        if (DxTzService_MemCpy(aNewBuffCopyPosition,aExtendedBuff,aExtendedLength) == DX_NULL){

            onCleenupExpandBuffers(aNewBuff,aExtendedBuff,DX_NULL);

            return DX_NULL;
        }

        aNewBuffCopyPosition += aExtendedLength;
    }

    //now copy the original buffer
    if (DxTzService_MemCpy(aNewBuffCopyPosition,aBuffer,aOriginalBufferLength) == DX_NULL){

        onCleenupExpandBuffers(aNewBuff,aExtendedBuff, DX_NULL);

        return DX_NULL;
    }

    aNewBuffCopyPosition += aOriginalBufferLength;

    if(leftOrRightSide ==eEXTEND_TO_RIGHT_SIDE || leftOrRightSide !=eEXTEND_TO_LEFT_SIDE){ //if right size

        if (DxTzService_MemCpy(aNewBuffCopyPosition,aExtendedBuff,aExtendedLength) == DX_NULL){

            onCleenupExpandBuffers(aNewBuff, aExtendedBuff, DX_NULL);

            return DX_NULL;
        }

        aNewBuffCopyPosition += aExtendedLength;
    }
    /*add by y00201671 solve memory leak:begin:*/
    onCleenupExpandBuffers(aExtendedBuff, DX_NULL, DX_NULL);
    /*add by y00201671 solve memory leak:end*/

    return aNewBuff;
}

DxStatus checkExtendedDummyBuffers(DxUint8 *aBuffer, DxUint32 aOriginalBufferLength, DxUint32 aExtendedLength, EExtendBufferSide leftOrRightSide){

    //calculate number of extensions
    DxUint8 * aExtendedBuff = DX_NULL;
    DxUint8 * aBuffPosition = DX_NULL;


    //creating the extending buf and initialize it
    aExtendedBuff = createExtendedBuff(aExtendedLength);

    if (aExtendedBuff==DX_NULL){ return DX_FAILURE; }

    aBuffPosition = aBuffer;

    //checking the input buffer for valid extension
    if(leftOrRightSide == eEXTEND_TO_LEFT_SIDE || leftOrRightSide != eEXTEND_TO_RIGHT_SIDE){ //if left size

        if (DxTzService_MemCmp(aBuffPosition, aExtendedBuff, aExtendedLength) != 0){

            onCleenupExpandBuffers(aExtendedBuff, DX_NULL, DX_NULL);

            return DX_FAILURE;
        }

        aBuffPosition += aExtendedLength;
    }

    if(leftOrRightSide == eEXTEND_TO_RIGHT_SIDE || leftOrRightSide != eEXTEND_TO_LEFT_SIDE){ //if right size

        aBuffPosition+=aOriginalBufferLength;

        if (DxTzService_MemCmp(aBuffPosition, aExtendedBuff, aExtendedLength) != 0){

            onCleenupExpandBuffers(aExtendedBuff, DX_NULL ,DX_NULL);

            return DX_FAILURE;
        }

        aBuffPosition += aExtendedLength;
    }

    /*add by y00201671 solve memory leak:begin:*/
    onCleenupExpandBuffers(aExtendedBuff, DX_NULL ,DX_NULL);
    /*add by y00201671 solve memory leak:end*/

    return DX_SUCCESS;
}

DxStatus getQaError(QaErrorMessage* outQaErrMsg){
	DxStatus result = DX_SUCCESS;
	QaGlobalInstance* qaGlobal = DxTzService_GetGlobalInstance();

	if ((DX_NULL == qaGlobal) || (DX_NULL == qaGlobal->qaErrMsg)){

		//DxTzService_MemSet(outQaErrMsg, 0, sizeof(QaErrorMessage));
		result = DX_FAILURE;

	} else {

		DxTzService_MemCpy(outQaErrMsg, qaGlobal->qaErrMsg, sizeof(QaErrorMessage));

	}
	return result;
}

DxUint32 getNumOfLoops(void){
    QaGlobalInstance* qaInstance = (QaGlobalInstance*)DxTzService_GetGlobalInstance();
    if (DX_NULL == qaInstance){
        QA_ERR_MSG("DxTzService_GetGlobalInstance returned NULL - return 1000 loop count");
        return 1000;
    }
    return qaInstance->muxNumOfLoops;
}



DxStatus CreateAndCopySharedMemRef(DxTzServiceSharedMemRef *destSharedMemRefPtr, DxByte *destRegularBuffer,
									DxTzServiceSharedMemRef *srcSharedMemRefPtr, unsigned int offsetInSrc,
									unsigned int bufferSize)
{
	DxStatus operationStatus;

	// create clearBufferSharedMemRef from clearBuffer
	if( DX_SUCCESS != (operationStatus = DxTzService_ConvertToSharedMemRef(destSharedMemRefPtr, 0, destRegularBuffer, bufferSize)))
	{
		// sharedMemRefDestPtr creation failed
		DxHwLogTrace(DX_FALSE, "%s: DxTzService_ConvertToSharedMemRef failed!",__FUNCTION__);
		return operationStatus;
	}
	// copy from buffer pointed by sharedMemRefSrcPtr to sharedMemRefDestPtr
	if( DX_SUCCESS != (operationStatus = DxTzService_MemCpyEx(destSharedMemRefPtr, 0, srcSharedMemRefPtr, offsetInSrc, bufferSize)))
	{
		// memcpy failed
		DxHwLogTrace(DX_FALSE, "%s: DxTzService_MemCpyEx failed",__FUNCTION__);
		return operationStatus;
	}

	return DX_SUCCESS;
}

