#include "QaTestFuncDeclaration.h"
#include "QaUtils.h"
//////////////////////////////////////////////
//Read Secure Storage
//
// const DxChar* fileName-
// DxUint fileLength
//////////////////////////////////////////////
DxStatus secureStorage_ReadWriteTest(const DxChar* fileName, DxUint fileLength, DxStatus expectedResult)
{
    DxStatus status=DX_SUCCESS;
    DxUint8* localBuf=DX_NULL;
    DxUint8* localInputBuffer=DX_NULL;
    DxUint32   localLen, allocatedSize;

    QA_LOG_MSG("SFS ReadWriteTest fileName=\"%s\"", fileName);
    QA_LOG_MSG("SFS ReadWriteTest dataSize=\"%d\"", fileLength);
    QA_LOG_MSG("SFS ReadWriteTest expectedResult=\"0x%X\"", expectedResult);

	/*Create a buffer of size bigger than 0*/
	allocatedSize = (fileLength==0)? 1 : fileLength;


	// createExtendedBuff creates buffer and writes in to it numbers
	localInputBuffer = createExtendedBuff(allocatedSize);

	if (localInputBuffer==DX_NULL){
		REPORT_ERROR1("secureStorage_ReadWriteTest: createExtendedBuff failed to allocate %d bytes.",allocatedSize);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}


	localBuf=DxTzService_Malloc(allocatedSize);
	if (localBuf==DX_NULL){
		REPORT_ERROR1("secureStorage_ReadWriteTest: DxTzService_Malloc failed to allocate %d bytes.",allocatedSize);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	// 1. create file and write buffer in to it
    localLen=fileLength;
	QA_LOG_MSG("executing secureStorage_ReadWriteTest: DxTzService_WriteToSecureStorage with %d bytes", localLen);
    status = DxTzService_WriteToSecureStorage( fileName, localInputBuffer,  localLen);
    if (expectedResult == status ) {
		status = DX_SUCCESS;
	}
	else {
        REPORT_ERROR2("secureStorage_ReadWriteTest: DxTzService_WriteToSecureStorage failed with return value 0x%x expectedResult: 0x%x",status, expectedResult);
		if (status == DX_SUCCESS)
			status = DX_FAILURE;
        PERFORM_CLEANUP;
    }


	// 2. open and read created in 1. file
    localLen=fileLength;
	QA_LOG_MSG("executing secureStorage_ReadWriteTest: DxTzService_ReadFromSecureStorage");
    status = DxTzService_ReadFromSecureStorage(fileName,  localBuf, &localLen);
    if (expectedResult == status ) {
		status = DX_SUCCESS;
	}
	else {
        REPORT_ERROR2("secureStorage_ReadWriteTest: DxTzService_ReadFromSecureStorage failed with return value 0x%x expectedResult: 0x%x",status, expectedResult);
		if (status == DX_SUCCESS)
			status = DX_FAILURE;
        PERFORM_CLEANUP;
    }

	if (expectedResult == DX_SUCCESS)
	{
		// 3. validate that read exactly number of bytes that was written
	    if (localLen != fileLength){
			REPORT_ERROR1("secureStorage_ReadWriteTest: DxTzService_ReadFromSecureStorage read wrong number of bytes 0x%x",localLen);
			status=DX_FAILURE;
	        PERFORM_CLEANUP;
	    }

		// 4. check buffer content read from file
	    if (DxTzService_MemCmp(localInputBuffer,localBuf,fileLength) !=0){
			REPORT_ERROR0("secureStorage_ReadWriteTest: the read buffer is different from the input write buffer");
			status=DX_FAILURE;
	        PERFORM_CLEANUP;
		}
    }



CLEANUP_SECTION:
    QA_LOG_MSG("CLEANUP_SECTION");

    if (DX_NULL != localInputBuffer)
	{
  	    destroyExtendedBuff(localInputBuffer);
    }


    if (DX_NULL != localBuf)
	{
	    DxTzService_Free(localBuf);
	}


    return status;

}


DxStatus secureStorage_UpdateBuffLenTest(const DxChar* fileName, DxUint fileLength, DxStatus expectedResult)
{
    DxStatus status=DX_SUCCESS;
    DxUint8 *bigReadBuff=DX_NULL, *smallReadBuff = DX_NULL;
    DxUint32 readBuffSize, smallReadBuffSize, bigReadBuffSize;
	const DxInt32 bufferSizeDiff=10;
	DxStatus readWriteFilesStatus;

	QA_LOG_MSG("SFS UpdateBuffLenTest fileName=\"%s\"", fileName);
	QA_LOG_MSG("SFS UpdateBuffLenTest dataSize=\"%d\"", fileLength);
	QA_LOG_MSG("SFS UpdateBuffLenTest expectedResult=\"0x%x\"", expectedResult);

	// create file
	readWriteFilesStatus = secureStorage_ReadWriteTest(fileName, fileLength, expectedResult);
	if(readWriteFilesStatus != DX_SUCCESS)
	{
		// test prerequisites did not succeed
		REPORT_ERROR1("secureStorage_UpdateBuffLenTest: secureStorage_ReadWriteTest failed with return value 0x%x", readWriteFilesStatus);
		return readWriteFilesStatus;
	}

	// 1. allocate buffer bigger than file size by 10 bytes
	bigReadBuffSize   = fileLength+bufferSizeDiff;
	bigReadBuff = DxTzService_Malloc(bigReadBuffSize);
	if (bigReadBuff == DX_NULL){
		REPORT_ERROR1("secureStorage_UpdateBuffLenTest: DxTzService_Malloc failed to allocate %d bytes.",bigReadBuffSize);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	// 2. open and read created in secureStorage_ReadWriteTest file
	QA_LOG_MSG("executing secureStorage_UpdateBuffLenTest: DxTzService_ReadFromSecureStorage");
	status = DxTzService_ReadFromSecureStorage(fileName,  bigReadBuff, &bigReadBuffSize);
    if (expectedResult == status ) {
		status = DX_SUCCESS;
	}
	else {
		REPORT_ERROR2("secureStorage_UpdateBuffLenTest: DxTzService_ReadFromSecureStorage failed with return value 0x%x expectedResult: 0x%x",status, expectedResult);
		if (status == DX_SUCCESS)
			status = DX_FAILURE;
		PERFORM_CLEANUP;
	}

	// 3. validate that was read fileLength number of bytes from file => bigReadBuffSize was truncated to fileLength
	if (bigReadBuffSize != fileLength){
		status = DX_FAILURE;
		REPORT_ERROR2("secureStorage_UpdateBuffLenTest: read %d bytes instead %d bytes",bigReadBuffSize,fileLength);
        PERFORM_CLEANUP;
    }


	if(bufferSizeDiff >= (DxInt32)fileLength)
	{
		status = DX_FAILURE;
		REPORT_ERROR1("secureStorage_UpdateBuffLenTest: internal test error : bad input parameter fileLength is too small = %d",fileLength);
        PERFORM_CLEANUP;
	}

	// 4. allocate buffer smaller than file size by 10 bytes
	smallReadBuffSize = fileLength - bufferSizeDiff;
	readBuffSize = smallReadBuffSize;
	smallReadBuff = DxTzService_Malloc(smallReadBuffSize);
	if (smallReadBuff == DX_NULL){
		REPORT_ERROR1("secureStorage_UpdateBuffLenTest: DxTzService_Malloc failed to allocate %d bytes.",smallReadBuffSize);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	// 5. open and read created in secureStorage_ReadWriteTest file
	QA_LOG_MSG("executing secureStorage_UpdateBuffLenTest: DxTzService_ReadFromSecureStorage");
	status = DxTzService_ReadFromSecureStorage(fileName,  smallReadBuff, &readBuffSize);
	if (expectedResult == status ) {
		status = DX_SUCCESS;
	}
	else {
		REPORT_ERROR2("secureStorage_UpdateBuffLenTest: DxTzService_ReadFromSecureStorage failed with return value 0x%x expectedResult: 0x%x",status, expectedResult);
		if (status == DX_SUCCESS)
			status = DX_FAILURE;
		PERFORM_CLEANUP;
	}

	// 6. validate that was read smallReadBuffSize number of bytes from file
	if (smallReadBuffSize != readBuffSize){
		status = DX_FAILURE;
		REPORT_ERROR2("secureStorage_UpdateBuffLenTest: read %d bytes instead %d bytes",bigReadBuffSize,fileLength);
		PERFORM_CLEANUP;
	}


CLEANUP_SECTION:
    QA_LOG_MSG("CLEANUP_SECTION");

	if (DX_NULL != bigReadBuff){
	    DxTzService_Free(bigReadBuff);
	}

	if (DX_NULL != smallReadBuff){
		DxTzService_Free(smallReadBuff);
	}

	return status;
}

#define TEST_FILE_NAME "test_file.bin"

DxStatus secureStorage_DeleteFileTest(DxUint32 fileLength)
{
    DxStatus status=DX_SUCCESS;
    DxUint8* localBuf=DX_NULL;
	DxUint32 i;

    QA_LOG_MSG("secureStorage_DeleteFileTest dataSize=\"%d\"", fileLength);

	if (fileLength == 0)
	{
		REPORT_ERROR0("secureStorage_DeleteFileTest: fileLength cannot be zero");
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	localBuf=DxTzService_Malloc(fileLength);
	if (localBuf==DX_NULL){
		REPORT_ERROR1("secureStorage_DeleteFileTest: DxTzService_Malloc failed to allocate %d bytes.",fileLength);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	/* Fill the buffer */
	for (i = 0; i < fileLength; i++)
	{
		localBuf[i] = (DxUint8)i;
	}

	QA_LOG_MSG("executing secureStorage_DeleteFileTest: Writing file");
	status = DxTzService_WriteToSecureStorage(TEST_FILE_NAME, localBuf, fileLength);
	if (status != DX_SUCCESS)
	{
		REPORT_ERROR1("secureStorage_DeleteFileTest: write to SFS failed with error code: 0x%x", status);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	QA_LOG_MSG("executing secureStorage_DeleteFileTest: Deleting file");
	status = DxTzService_WriteToSecureStorage(TEST_FILE_NAME, DX_NULL, 0);
	if (status != DX_SUCCESS)
	{
		REPORT_ERROR1("secureStorage_DeleteFileTest: delete SFS file failed with error code: 0x%x", status);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

CLEANUP_SECTION:
    QA_LOG_MSG("CLEANUP_SECTION");

	if (DX_NULL != localBuf){
	    DxTzService_Free(localBuf);
	}

	return status;
}

DxStatus secureStorage_CreateNewFileTest(DxUint32 fileLength)
{
    DxStatus status=DX_SUCCESS;
    DxUint8* localBuf=DX_NULL;
    DxUint8* localBuf2=DX_NULL;
	DxUint32 i;
	DxUint32 readSize = 0;

    QA_LOG_MSG("secureStorage_CreateNewFileTest dataSize=\"%d\"", fileLength);

	if (fileLength == 0)
	{
		REPORT_ERROR0("secureStorage_CreateNewFileTest: fileLength cannot be zero");
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	localBuf=DxTzService_Malloc(fileLength);
	if (localBuf==DX_NULL){
		REPORT_ERROR1("secureStorage_CreateNewFileTest: DxTzService_Malloc failed to allocate %d bytes.",fileLength);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	localBuf2=DxTzService_Malloc(fileLength);
	if (localBuf2==DX_NULL){
		REPORT_ERROR1("secureStorage_CreateNewFileTest: DxTzService_Malloc failed to allocate %d bytes.",fileLength);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	/* Fill the buffer */
	for (i = 0; i < fileLength; i++)
	{
		localBuf[i] = (DxUint8)i;
	}

	QA_LOG_MSG("executing secureStorage_CreateNewFileTest: Writing file");
	status = DxTzService_WriteToSecureStorage(TEST_FILE_NAME, localBuf, fileLength);
	if (status != DX_SUCCESS)
	{
		REPORT_ERROR1("secureStorage_CreateNewFileTest: write to SFS failed with error code: 0x%x", status);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	QA_LOG_MSG("executing secureStorage_CreateNewFileTest: Deleting file");
	status = DxTzService_WriteToSecureStorage(TEST_FILE_NAME, DX_NULL, 0);
	if (status != DX_SUCCESS)
	{
		REPORT_ERROR1("secureStorage_CreateNewFileTest: delete SFS file failed with error code: 0x%x", status);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	QA_LOG_MSG("executing secureStorage_CreateNewFileTest: Writing file");
	status = DxTzService_WriteToSecureStorage(TEST_FILE_NAME, localBuf, fileLength);
	if (status != DX_SUCCESS)
	{
		REPORT_ERROR1("secureStorage_CreateNewFileTest: write to SFS failed with error code: 0x%x", status);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	QA_LOG_MSG("executing secureStorage_CreateNewFileTest: Reading file");
	readSize = fileLength;
	status = DxTzService_ReadFromSecureStorage(TEST_FILE_NAME,  localBuf2, &readSize);
	if (DX_SUCCESS != status )
	{
		REPORT_ERROR1("secureStorage_CreateNewFileTest: read from SFS failed with error code: 0x%x", status);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}
	if (readSize != fileLength)
	{
		REPORT_ERROR2("secureStorage_CreateNewFileTest: wrong size returned by DxTzService_ReadFromSecureStorage: Actual value: 0x%x, Expected value: 0x%x", readSize, fileLength);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

    if (DxTzService_MemCmp(localBuf,localBuf2,fileLength) !=0 )
	{
		REPORT_ERROR0("secureStorage_CreateNewFileTest: the read buffer is different from the input write buffer");
		status=DX_FAILURE;
        PERFORM_CLEANUP;
	}

CLEANUP_SECTION:
    QA_LOG_MSG("CLEANUP_SECTION");

	if (DX_NULL != localBuf){
	    DxTzService_Free(localBuf);
	}

	if (DX_NULL != localBuf2){
	    DxTzService_Free(localBuf2);
	}

	return status;
}

DxStatus secureStorage_GetSizeTest(const DxChar* fileName, DxUint fileLength)
{
    DxStatus status=DX_SUCCESS;
    DxUint8* localBuf=DX_NULL;
	DxUint32 Len = 0;
	DxUint i;
	DxUint allocLength = (fileLength == 0) ? 1 : fileLength;

	QA_LOG_MSG("SFS GetSizeTest fileName=\"%s\"", fileName);
	QA_LOG_MSG("SFS GetSizeTest dataSize=\"%d\"", fileLength);

	localBuf=DxTzService_Malloc(allocLength);
	if (localBuf==DX_NULL){
		REPORT_ERROR1("secureStorage_GetSizeTest: DxTzService_Malloc failed to allocate %d bytes.",allocLength);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	/* Fill the buffer */
	for (i = 0; i < allocLength; i++)
	{
		localBuf[i] = (DxUint8)i;
	}

	QA_LOG_MSG("executing secureStorage_GetSizeTest: Writing file\"%s\"", fileName);
	status = DxTzService_WriteToSecureStorage(fileName, localBuf, allocLength);
	if (status != DX_SUCCESS)
	{
		REPORT_ERROR1("secureStorage_GetSizeTest: write to SFS failed with error code: 0x%x", status);
		status=DX_FAILURE;
		PERFORM_CLEANUP;
	}

	if (fileLength == 0)
	{
		QA_LOG_MSG("executing secureStorage_GetSizeTest: Deleting file \"%s\"", fileName);
		status = DxTzService_WriteToSecureStorage(fileName, DX_NULL, 0);
		if (status != DX_SUCCESS)
		{
			REPORT_ERROR1("secureStorage_GetSizeTest: delete SFS file failed with error code: 0x%x", status);
			status=DX_FAILURE;
			PERFORM_CLEANUP;
		}
	}

	status = DxTzService_GetSecureStorageFileSize(fileName, &Len);
	if (fileLength == 0)
	{
		if (status == DX_ITEM_NOT_FOUND)
		{
			status = DX_SUCCESS;
		}
		else
		{
			REPORT_ERROR2("secureStorage_GetSizeTest: Got wrong error code (0x%x) while reading size of non-existing file. Expected error code: DX_ITEM_NOT_FOUND (0x%x)", status, DX_ITEM_NOT_FOUND);
			status=DX_FAILURE;
			PERFORM_CLEANUP;
		}
	}
	else
	{
		if (status != DX_SUCCESS)
		{
			REPORT_ERROR1("secureStorage_GetSizeTest: DxTzService_GetSecureStorageFileSize() failed with error code 0x%x", status);
			status=DX_FAILURE;
			PERFORM_CLEANUP;
		}
		else
		{
			if (Len != (DxUint32)fileLength)
			{
				REPORT_ERROR2("secureStorage_GetSizeTest: DxTzService_GetSecureStorageFileSize() returned wrong file size (%d), Expected file size: %d", Len, fileLength);
				status=DX_FAILURE;
				PERFORM_CLEANUP;
			}
		}
	}

CLEANUP_SECTION:
    QA_LOG_MSG("CLEANUP_SECTION");

	if (DX_NULL != localBuf){
	    DxTzService_Free(localBuf);
	}
	return status;
}

