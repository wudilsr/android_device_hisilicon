#include "QaTestFuncDeclaration.h"
#include "DxTzServiceAPI.h"
#include "QaUtils.h"

DxStatus MultipaleInitTermSecureContentPath(DxInt32 numberOfTimes )
{
    int index;
    DxStatus result=DX_SUCCESS;

    for (index = 0; index < numberOfTimes; index++)
	{
        result = DxTzService_InitSecureContentPath();
        if(DX_SUCCESS != result){
            REPORT_ERROR1("DxTzService_InitSecureContentPath failed with return value 0x%08X",result);
            return DX_FAILURE;
        }

        result = DxTzService_TerminateSecureContentPath();
        if(DX_SUCCESS != result){
            REPORT_ERROR1("DxTzService_InitSecureContentPath failed with return value 0x%08X",result);
            return DX_FAILURE;
        }
    }

    return DX_SUCCESS;
}

DxStatus IsMemorySecuredAsExpected( DxUint32 dataSize,
									DxBool bTestForSecureBuffer,
									DxBool expectedResultSecureTest,
									DxBool bTestForNonSecureBuffer,
									DxBool expectedResultNonSecureTest,
									DxBool bIsShared,
									DxTzServiceSharedMemRef *pSharedMemRef
								  )
{
	DxTzServiceSharedMemRef  localMemRef;
	DxTzServiceSharedMemRef *pMemRef;
	DxByte 					*buffer 	      	 = DX_NULL;
	DxBool 					 resultSecureTest 	 = DX_SUCCESS;
	DxBool 					 resultNonSecureTest = DX_SUCCESS;
    DxStatus 				 finalResult		 = DX_SUCCESS;


    // If tested buffer memory is shared, set pMemRef to the shared memory that was already allocated.
    // Otherwise, allocate now memory for the buffer.
	if (bIsShared)
	{
		pMemRef = pSharedMemRef;
	}
	else
	{
		buffer = DxTzService_Malloc(dataSize);

		if (DX_NULL == buffer)
		{
			REPORT_ERROR0("DxTzService_Malloc failed to allocate memory");
			finalResult = DX_FAILURE;
	        PERFORM_CLEANUP;
		}

		/* convert allocated buffer to handle */
		if (DX_SUCCESS != DxTzService_ConvertToSharedMemRef(&localMemRef, 0, buffer, dataSize))
		{
			REPORT_ERROR0("DxTzService_ConvertToSharedMemRef failed to convert handle");
			finalResult = DX_FAILURE;
	        PERFORM_CLEANUP;
		}

		pMemRef = &localMemRef;
	}


	// Perform secure buffer test
	if(bTestForSecureBuffer)
	{
		if (DX_SUCCESS != DxTzService_IsSecureContentMemory(pMemRef, 0, dataSize, &resultSecureTest))
		{
			REPORT_ERROR0("DxTzService_IsSecureContentMemory failed to check if memory secured");
			finalResult = DX_FAILURE;
			PERFORM_CLEANUP;
		}

		if(resultSecureTest != expectedResultSecureTest)
		{
			REPORT_ERROR2("DxTzService_IsSecureContentMemory result is not as expected. Actual result = Secured:%d .Expected result = Secured:%d.", resultSecureTest, expectedResultSecureTest);
			finalResult = DX_FAILURE;
			PERFORM_CLEANUP;
		}
	}

	// Perform non secure buffer test
	if(bTestForNonSecureBuffer)
	{
		if (DX_SUCCESS != DxTzService_IsNonSecureContentMemory(pMemRef, 0, dataSize, &resultNonSecureTest))
		{
			REPORT_ERROR0("DxTzService_IsNonSecureContentMemory failed to check if memory non secured");
			finalResult = DX_FAILURE;
			PERFORM_CLEANUP;
		}

		if(resultNonSecureTest != expectedResultNonSecureTest)
		{
			REPORT_ERROR2("DxTzService_IsNonSecureContentMemory result is not as expected. Actual result = NotSecured:%d .Expected result = NotSecured:%d.", resultNonSecureTest, expectedResultNonSecureTest);
			finalResult = DX_FAILURE;
			PERFORM_CLEANUP;
		}
	}


CLEANUP_SECTION:

	if (buffer != DX_NULL)
    {
        DxTzService_Free(buffer);
    }

    return finalResult;
}

