#include "QaTestFuncDeclaration.h"
#include "DxTzServiceAPI.h"

#include "QaTestEnumeration.h"

#include "QaUtils.h"

#define PARTIAL_NUMBER_OF_BLOCKS 4
#define EXTENDED_BUFFER_SIZE 512
#define DIVIDE_ROUND_UP(num, divider)	 (((num) + (divider) - 1) / (divider))


//////////////////////////////////////////////////////////////////////////
//	HASH tests functions TZ implementations : SHA1, SHA256, MD5
//////////////////////////////////////////////////////////////////////////


DxStatus cryptoSha1(const DxUint8 *aBuffer, DxUint32 aBufferLength, DxUint8 * aDigest, DxBool isBufferShallDivided){
    DxTzSHA1Context_t aContext=DX_NULL;
    DxStatus result = DX_SUCCESS;
    DxStatus resultCleanup;
    DxUint8 *newExtendedToBuffer=DX_NULL;
    DxUint8 localDigest[SHA1_SIGNATURE_SIZE];
    DxUint8 *pointerToBuffer=DX_NULL;
    DxUint32 partialDataLength=0;
    DxUint32 timesToLoop=0;
    DxUint32 index=0;
    DxUint32 partialSize=0;


    newExtendedToBuffer = expandTestingDataWithDummyBuffers(aBuffer, aBufferLength, EXTENDED_BUFFER_SIZE, eEXTEND_TO_BOTH_SIDE);
    if (newExtendedToBuffer==DX_NULL){
        REPORT_ERROR0("ExpandTestingDataWithDummyBuffers failed to extend the memory for the test.");
        PERFORM_CLEANUP;
    }
    pointerToBuffer=newExtendedToBuffer+EXTENDED_BUFFER_SIZE;// pointing to the real buffer

    result =  DxTzService_SHA1Init(&aContext);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_SHA1Init failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    if ((isBufferShallDivided==DX_TRUE ) && (PARTIAL_NUMBER_OF_BLOCKS > 1)){

        partialSize = aBufferLength/PARTIAL_NUMBER_OF_BLOCKS;
        timesToLoop = DIVIDE_ROUND_UP(aBufferLength,partialSize);

        for(index=0; index<timesToLoop; index++){

            //point to the next buffer.
            pointerToBuffer=pointerToBuffer+partialDataLength;
            //if this is the last loop the partial data length shell be calculate differently
            partialDataLength = timesToLoop == index+1 ? aBufferLength-index*partialSize : partialSize;

            result = DxTzService_SHA1Update(aContext, pointerToBuffer, partialDataLength);
            if (DX_SUCCESS != result )    {
                REPORT_ERROR2("DxTzService_SHA1Update failed with return value 0x%08X for partial buffer part 0x%08X",result, index);
                PERFORM_CLEANUP;
            }
        }
    }
    else{
        result = DxTzService_SHA1Update(aContext, aBuffer, aBufferLength);
        if (DX_SUCCESS != result )    {
            REPORT_ERROR1("DxTzService_SHA1Update failed with return value 0x%08X",result);
            PERFORM_CLEANUP;
        }
    }

    result = DxTzService_SHA1Final(aContext, localDigest);
    if (DX_SUCCESS != result )    {
        REPORT_ERROR1("DxTzService_SHA1Final failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    //check if we have overwritten the extended memory
	result = checkExtendedDummyBuffers(newExtendedToBuffer, aBufferLength, EXTENDED_BUFFER_SIZE, eEXTEND_TO_BOTH_SIDE);
	if ( DX_SUCCESS != result){
        REPORT_ERROR0("CheckExtendedDummyBuffers has found a memory corruption at the extended buffer");
        PERFORM_CLEANUP;
    }

CLEANUP_SECTION:
    resultCleanup = DxTzService_SHA1Terminate(aContext);

    if ((DX_SUCCESS != resultCleanup) && (result==DX_SUCCESS) ){

        REPORT_ERROR1("DxTzService_SHA1Terminate failed with return value 0x%08X",resultCleanup);

    }

    if (newExtendedToBuffer != DX_NULL)
        DxTzService_Free(newExtendedToBuffer);

    DxTzService_MemCpy(aDigest,localDigest,SHA1_SIGNATURE_SIZE);

    return result == DX_SUCCESS ? resultCleanup : result;
}

DxStatus cryptoSha256(const DxUint8 *aBuffer, DxUint32 aBufferLength, DxUint8 * aDigest, DxBool isBufferShallDivided)
{
    DxTzSHA256Context_t aContext=DX_NULL;
    DxStatus result = DX_SUCCESS;
    DxStatus resultCleanup;
    DxUint8 localDigest[SHA256_SIGNATURE_SIZE];
    DxUint8 *newExtendedToBuffer=DX_NULL;
    DxUint8 *pointerToBuffer=DX_NULL;
    DxUint32 partialDataLength=0;
    DxUint32 timesToLoop=0;
    DxUint32 index=0;
    DxUint32 partialSize=0;

    newExtendedToBuffer = expandTestingDataWithDummyBuffers(aBuffer, aBufferLength, EXTENDED_BUFFER_SIZE, eEXTEND_TO_BOTH_SIDE);
    if (newExtendedToBuffer==DX_NULL){
        REPORT_ERROR0("ExpandTestingDataWithDummyBuffers failed to extend the memory for the test.");
        PERFORM_CLEANUP;
    }
    pointerToBuffer=newExtendedToBuffer+EXTENDED_BUFFER_SIZE;// pointing to the real buffer


    result =  DxTzService_SHA256Init(&aContext);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_SHA256Init failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    if ((isBufferShallDivided==DX_TRUE ) && (PARTIAL_NUMBER_OF_BLOCKS > 1)){

        partialSize = aBufferLength/PARTIAL_NUMBER_OF_BLOCKS;
        timesToLoop = DIVIDE_ROUND_UP(aBufferLength,partialSize);

        for( index=0; index<timesToLoop; index++){

            //point to the next buffer.
            pointerToBuffer=pointerToBuffer+partialDataLength;

            //if this is the last loop the partial data length shell be calculate differently
            partialDataLength = timesToLoop == index+1 ? aBufferLength-index*partialSize : partialSize;

            result = DxTzService_SHA256Update(aContext, pointerToBuffer, partialDataLength);
            if (DX_SUCCESS != result )    {
                REPORT_ERROR2("DxTzService_SHA256Update failed with return value 0x%08X for partial buffer part 0x%08X",result, index);
                PERFORM_CLEANUP;
            }
        }
    }
    else{
        result = DxTzService_SHA256Update(aContext, pointerToBuffer, aBufferLength);
        if (DX_SUCCESS != result )    {
            REPORT_ERROR1("DxTzService_SHA256Update failed with return value 0x%08X",result);
            PERFORM_CLEANUP;
        }
    }
    result = DxTzService_SHA256Final(aContext, localDigest);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_SHA256Final failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    //check if we have overwritten the extended memory
	result = checkExtendedDummyBuffers(newExtendedToBuffer, aBufferLength, EXTENDED_BUFFER_SIZE, eEXTEND_TO_BOTH_SIDE);
	if ( DX_SUCCESS != result){
        REPORT_ERROR0("CheckExtendedDummyBuffers has found a memory corruption at the extended buffer");
        PERFORM_CLEANUP;
    }

CLEANUP_SECTION:

    resultCleanup = DxTzService_SHA256Terminate(aContext);
    if (DX_SUCCESS != resultCleanup ){
        REPORT_ERROR1("DxTzService_SHA256Terminate failed with return value 0x%08X",resultCleanup);
    }

    if (newExtendedToBuffer != DX_NULL)
        DxTzService_Free(newExtendedToBuffer);

    DxTzService_MemCpy(aDigest,localDigest,SHA256_SIGNATURE_SIZE);

    return result == DX_SUCCESS ? resultCleanup : result;
}


DxStatus cryptoMD5(const DxUint8 *aBuffer, DxUint32 aBufferLength, DxUint8 * aDigest, DxBool isBufferShallDivided){
	DxTzMD5Context_t aContext=DX_NULL;
	DxStatus result = DX_SUCCESS;
	DxStatus resultCleanup;
	DxUint8 *newExtendedToBuffer=DX_NULL;
	DxUint8 localDigest[MD5_SIGNATURE_SIZE];
	DxUint8 *pointerToBuffer=DX_NULL;
	DxUint32 partialDataLength=0;
	DxUint32 timesToLoop=0;
	DxUint32 index=0;
	DxUint32 partialSize=0;


	newExtendedToBuffer = expandTestingDataWithDummyBuffers(aBuffer, aBufferLength, EXTENDED_BUFFER_SIZE, eEXTEND_TO_BOTH_SIDE);
	if (newExtendedToBuffer==DX_NULL){
		REPORT_ERROR0("ExpandTestingDataWithDummyBuffers failed to extend the memory for the test.");
		PERFORM_CLEANUP;
	}
	pointerToBuffer=newExtendedToBuffer+EXTENDED_BUFFER_SIZE;// pointing to the real buffer

	result =  DxTzService_MD5Init(&aContext);
	if (DX_SUCCESS != result ){
		REPORT_ERROR1("DxTzService_MD5Init failed with return value 0x%08X",result);
		PERFORM_CLEANUP;
	}

	if ((isBufferShallDivided==DX_TRUE ) && (PARTIAL_NUMBER_OF_BLOCKS > 1)){

		partialSize = aBufferLength/PARTIAL_NUMBER_OF_BLOCKS;
		timesToLoop = DIVIDE_ROUND_UP(aBufferLength,partialSize);

		for(index=0; index<timesToLoop; index++){

			//point to the next buffer.
			pointerToBuffer=pointerToBuffer+partialDataLength;
			//if this is the last loop the partial data length shell be calculate differently
			partialDataLength = timesToLoop == index+1 ? aBufferLength-index*partialSize : partialSize;

			result = DxTzService_MD5Update(aContext, pointerToBuffer, partialDataLength);
			if (DX_SUCCESS != result )    {
				REPORT_ERROR2("DxTzService_MD5Update failed with return value 0x%08X for partial buffer part 0x%08X",result, index);
				PERFORM_CLEANUP;
			}
		}
	}
	else{
		result = DxTzService_MD5Update(aContext, aBuffer, aBufferLength);
		if (DX_SUCCESS != result )    {
			REPORT_ERROR1("DxTzService_MD5Update failed with return value 0x%08X",result);
			PERFORM_CLEANUP;
		}
	}

	result = DxTzService_MD5Final(aContext, localDigest);
	if (DX_SUCCESS != result )    {
		REPORT_ERROR1("DxTzService_MD5Final failed with return value 0x%08X",result);
		PERFORM_CLEANUP;
	}

	//check if we have overwritten the extended memory
	result = checkExtendedDummyBuffers(newExtendedToBuffer, aBufferLength, EXTENDED_BUFFER_SIZE, eEXTEND_TO_BOTH_SIDE);
	if ( DX_SUCCESS != result){
		REPORT_ERROR0("CheckExtendedDummyBuffers has found a memory corruption at the extended buffer");
		PERFORM_CLEANUP;
	}

CLEANUP_SECTION:
	resultCleanup = DxTzService_MD5Terminate(aContext);

	if ((DX_SUCCESS != resultCleanup) && (result==DX_SUCCESS) ){
		REPORT_ERROR1("DxTzService_MD5Terminate failed with return value 0x%08X",resultCleanup);
	}

	if (newExtendedToBuffer != DX_NULL)
		DxTzService_Free(newExtendedToBuffer);

	DxTzService_MemCpy(aDigest,localDigest,MD5_SIGNATURE_SIZE);

	return result == DX_SUCCESS ? resultCleanup : result;
}


//////////////////////////////////////////////////////////////////////////
//	HMAC tests functions TZ implementations : HMAC SHA256
//////////////////////////////////////////////////////////////////////////
DxStatus cryptoHmacSha256(const DxUint8 *aBuffer, DxUint32 aBufferLength, const DxUint8 *aKey, DxUint32 aKeyLength, DxUint8 * aDigest, DxBool isBufferShallDivided)
{
	DxTzHMAC_SHA256Context_t aContext=DX_NULL;
	DxStatus result = DX_SUCCESS;
	DxStatus resultCleanup;
	DxUint8 *newExtendedToBuffer=DX_NULL;
	DxUint8 localDigest[SHA256_SIGNATURE_SIZE];
	DxUint8 *pointerToBuffer=DX_NULL;
	DxUint32 partialDataLength=0;
	DxUint32 timesToLoop=0;
	DxUint32 index=0;
	DxUint32 partialSize=0;


	newExtendedToBuffer = expandTestingDataWithDummyBuffers(aBuffer, aBufferLength, EXTENDED_BUFFER_SIZE, eEXTEND_TO_BOTH_SIDE);
	if (newExtendedToBuffer==DX_NULL){
		REPORT_ERROR0("ExpandTestingDataWithDummyBuffers failed to extend the memory for the test.");
		PERFORM_CLEANUP;
	}
	pointerToBuffer=newExtendedToBuffer+EXTENDED_BUFFER_SIZE;// pointing to the real buffer

	result =  DxTzService_HMAC_SHA256Init(&aContext, aKey, aKeyLength);
	if (DX_SUCCESS != result ){
		REPORT_ERROR1("DxTzService_HMAC_SHA256Init failed with return value 0x%08X",result);
		PERFORM_CLEANUP;
	}

	if ((isBufferShallDivided==DX_TRUE ) && (PARTIAL_NUMBER_OF_BLOCKS > 1)){

		partialSize = aBufferLength/PARTIAL_NUMBER_OF_BLOCKS;
		timesToLoop = DIVIDE_ROUND_UP(aBufferLength,partialSize);

		for(index=0; index<timesToLoop; index++){

			//point to the next buffer.
			pointerToBuffer=pointerToBuffer+partialDataLength;
			//if this is the last loop the partial data length shell be calculate differently
			partialDataLength = timesToLoop == index+1 ? aBufferLength-index*partialSize : partialSize;

			result = DxTzService_HMAC_SHA256Update(aContext, pointerToBuffer, partialDataLength);
			if (DX_SUCCESS != result )    {
				REPORT_ERROR2("DxTzService_HMAC_SHA256Update failed with return value 0x%08X for partial buffer part 0x%08X",result, index);
				PERFORM_CLEANUP;
			}
		}
	}
	else{
		result = DxTzService_HMAC_SHA256Update(aContext, aBuffer, aBufferLength);
		if (DX_SUCCESS != result )    {
			REPORT_ERROR1("DxTzService_HMAC_SHA256Update failed with return value 0x%08X",result);
			PERFORM_CLEANUP;
		}
	}

	result = DxTzService_HMAC_SHA256Final(aContext, localDigest);
	if (DX_SUCCESS != result )    {
		REPORT_ERROR1("DxTzService_HMAC_SHA256Final failed with return value 0x%08X",result);
		PERFORM_CLEANUP;
	}

	//check if we have overwritten the extended memory
	result = checkExtendedDummyBuffers(newExtendedToBuffer, aBufferLength, EXTENDED_BUFFER_SIZE, eEXTEND_TO_BOTH_SIDE);
	if ( DX_SUCCESS != result){
		REPORT_ERROR0("CheckExtendedDummyBuffers has found a memory corruption at the extended buffer");
		PERFORM_CLEANUP;
	}

CLEANUP_SECTION:
	resultCleanup = DxTzService_HMAC_SHA256Terminate(aContext);

	if ((DX_SUCCESS != resultCleanup) && (result==DX_SUCCESS) ){
		REPORT_ERROR1("DxTzService_HMAC_SHA256Terminate failed with return value 0x%08X",resultCleanup);
	}

	if (newExtendedToBuffer != DX_NULL)
		DxTzService_Free(newExtendedToBuffer);

	DxTzService_MemCpy(aDigest,localDigest,SHA256_SIGNATURE_SIZE);

	return result == DX_SUCCESS ? resultCleanup : result;
}



//////////////////////////////////////////////
//AES128CTR
//////////////////////////////////////////////
DxStatus cryptoAES128Cbc(const DxUint8 *aBuffer,
                         DxUint32 aBufferLength,
                         DxUint8 * aOutputBuff,
                         DxUint32 aOutputBufferLength,
                         DxUint8 * aKey,
                         DxUint32 aKeyLen,
                         DxUint8 * aIv,
                         DxUint32 aIvLen,
                         EDxCipherDirection direction,
                         DxBool isAlinged)
{
    DxCipher_AES128CBC_Context_t aContext=DX_NULL;
    DxCipher_AES128_Context_t aInternalCtx=DX_NULL;
    DxStatus result = DX_SUCCESS;
    DxStatus resultCleanup;
    DxUint8 *localOutputBuffer=DX_NULL;
    DxUint8 *newExtendedToBuffer=DX_NULL;
    DxUint8 *pointerToBuffer=DX_NULL;
    DxUint8 *newExtendedIv=DX_NULL;
    DxUint8 *pointerToIv=DX_NULL;
    DxUint32 extendedBufferSize=EXTENDED_BUFFER_SIZE;

	/* in CBC mode size should be divided by 16 */
    if ( (aBufferLength== 0) || ((aBufferLength%16) != 0) )
    {
        REPORT_ERROR0("input buffer must be devidable by 16 and > 0");
        PERFORM_CLEANUP;
    }


    if (aBufferLength > aOutputBufferLength){
        REPORT_ERROR0("out buffer is too small");
        PERFORM_CLEANUP;
    }

    localOutputBuffer=DxTzService_Malloc(aBufferLength);
    if (localOutputBuffer==DX_NULL){
        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory of size 0x%08X.",aBufferLength);
        PERFORM_CLEANUP;
    }

    if(isAlinged==DX_FALSE)
        extendedBufferSize=extendedBufferSize-1;

    newExtendedToBuffer = expandTestingDataWithDummyBuffers(aBuffer, aBufferLength, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
    if (newExtendedToBuffer==DX_NULL){
        REPORT_ERROR0("ExpandTestingDataWithDummyBuffers failed to extend the memory for the test.");
        PERFORM_CLEANUP;
    }
    pointerToBuffer=newExtendedToBuffer+extendedBufferSize;// pointing to the real buffer

    newExtendedIv = expandTestingDataWithDummyBuffers(aIv, aIvLen, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
    if (newExtendedToBuffer==DX_NULL){
        REPORT_ERROR0("ExpandTestingDataWithDummyBuffers failed to extend the Iv memory for the test.");
        PERFORM_CLEANUP;
    }
    pointerToIv=newExtendedIv+extendedBufferSize;// pointing to the real buffer

    result = DxTzService_AES128_CreateContext(&aInternalCtx);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128_CreateContext failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    result = DxTzService_AES128CBC_Init(&aContext,aInternalCtx,aKey,aKeyLen,direction);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128CBC_Init failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }


	if( direction==DXCIPHER_DEC)
	{

        result = DxTzService_AES128CBC_DecryptData(aContext, pointerToBuffer, localOutputBuffer, aBufferLength, pointerToIv);
        if (DX_SUCCESS != result )    {
            REPORT_ERROR1("DxTzService_AES128CBC_DecryptData failed with return value 0x%08X", result);
            PERFORM_CLEANUP;
        }
	}
    else
	{
        result = DxTzService_AES128CBC_EncryptData(aContext, pointerToBuffer, localOutputBuffer, aBufferLength, pointerToIv);
        if (DX_SUCCESS != result )    {
			REPORT_ERROR1("DxTzService_AES128CBC_EncryptData failed with return value 0x%08X", result);
            PERFORM_CLEANUP;
        }
    }


	/* return iv to hlos, in hlos it will be validated */
	DxTzService_MemCpy(aIv, pointerToIv, DX_TZ_AES128_IV_SIZE);


    result = DxTzService_AES128CBC_Finish(&aContext);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128CBC_Finish failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    //check if we have overwritten the extended memory
    result = checkExtendedDummyBuffers(newExtendedToBuffer, aBufferLength, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
    if ( result != DX_SUCCESS)
    {
        REPORT_ERROR0("CheckExtendedDummyBuffers has found a memory corruption at the extended buffer");
        PERFORM_CLEANUP;
    }

    //check if we have overwritten the extended memory
    result = checkExtendedDummyBuffers(newExtendedIv, aIvLen, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
    if ( result != DX_SUCCESS)
    {
        REPORT_ERROR0("CheckExtendedDummyBuffers has found a memory corruption at the Iv extended buffer");
        PERFORM_CLEANUP;
    }

CLEANUP_SECTION:

    resultCleanup = DxTzService_AES128_TerminateContext(&aInternalCtx);
    if (DX_SUCCESS != resultCleanup ){
        REPORT_ERROR1("DxTzService_AES128_TerminateContext failed with return value 0x%08X",resultCleanup);
    }

    DxTzService_MemCpy(aOutputBuff,localOutputBuffer,aBufferLength);

    if (newExtendedToBuffer != DX_NULL)
        DxTzService_Free(newExtendedToBuffer);

    if (newExtendedIv != DX_NULL)
        DxTzService_Free(newExtendedIv);

    DxTzService_Free(localOutputBuffer);


    return result == DX_SUCCESS ? resultCleanup : result;
}








DxStatus cryptoAES128Ctr(const DxUint8 *aBuffer,
                         DxUint32 aBufferLength,
                         DxUint8 * aOutputBuff,
                         DxUint32 aOutputBufferLength,
                         DxUint8 * aKey,
                         DxUint32 aKeyLen,
                         DxUint8 * aIv,
                         DxUint32 aIvLen,
                         EDxCipherDirection direction,
                         DxBool isAlinged)
{
    DxCipher_AES128CTR_Context_t aContext=DX_NULL;
    DxCipher_AES128_Context_t aInternalCtx=DX_NULL;
    DxStatus result = DX_SUCCESS;
    DxStatus resultCleanup;
    DxUint8 *localOutputBuffer=DX_NULL;
    DxUint8 *newExtendedToBuffer=DX_NULL;
    DxUint8 *pointerToBuffer=DX_NULL;
    DxUint8 *newExtendedIv=DX_NULL;
    DxUint8 *pointerToIv=DX_NULL;
    DxUint32 extendedBufferSize=EXTENDED_BUFFER_SIZE;

    if (aBufferLength > aOutputBufferLength){
        REPORT_ERROR0("out buffer is too small");
        PERFORM_CLEANUP;
    }

    localOutputBuffer=DxTzService_Malloc(aBufferLength);
    if (localOutputBuffer==DX_NULL){
        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory of size 0x%08X.",aBufferLength);
        PERFORM_CLEANUP;
    }

    if(isAlinged==DX_FALSE)
        extendedBufferSize=extendedBufferSize-1;

    newExtendedToBuffer = expandTestingDataWithDummyBuffers(aBuffer, aBufferLength, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
    if (newExtendedToBuffer==DX_NULL){
        REPORT_ERROR0("ExpandTestingDataWithDummyBuffers failed to extend the memory for the test.");
        PERFORM_CLEANUP;
    }
    pointerToBuffer=newExtendedToBuffer+extendedBufferSize;// pointing to the real buffer

    newExtendedIv = expandTestingDataWithDummyBuffers(aIv, aIvLen, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
    if (newExtendedToBuffer==DX_NULL){
        REPORT_ERROR0("ExpandTestingDataWithDummyBuffers failed to extend the Iv memory for the test.");
        PERFORM_CLEANUP;
    }
    pointerToIv=newExtendedIv+extendedBufferSize;// pointing to the real buffer


    result = DxTzService_AES128_CreateContext(&aInternalCtx);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128_CreateContext failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    result = DxTzService_AES128CTR_Init(&aContext,aInternalCtx,aKey,aKeyLen,direction);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128CTR_Init failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }


    if( direction==DXCIPHER_DEC){
        result = DxTzService_AES128CTR_DecryptData(aContext, pointerToBuffer, localOutputBuffer, aBufferLength, pointerToIv);
        if (DX_SUCCESS != result )    {
            REPORT_ERROR1("DxTzService_AES128CTR_DecryptData failed with return value 0x%X",result);
            PERFORM_CLEANUP;
        }
    }
    else{
        result = DxTzService_AES128CTR_EncryptData(aContext, pointerToBuffer, localOutputBuffer, aBufferLength, pointerToIv);
        if (DX_SUCCESS != result )    {
            REPORT_ERROR1("DxTzService_AES128CTR_EncryptData failed with return value 0x%X",result);
            PERFORM_CLEANUP;
        }
    }

	/* return iv to hlos, in hlos it will be validated */
	DxTzService_MemCpy(aIv, pointerToIv, DX_TZ_AES128_IV_SIZE);



    result = DxTzService_AES128CTR_Finish(&aContext);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128CTR_Finish failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

	//check if we have overwritten the extended memory
	result = checkExtendedDummyBuffers(newExtendedToBuffer, aBufferLength, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
	if ( result != DX_SUCCESS)
	{
		REPORT_ERROR0("CheckExtendedDummyBuffers has found a memory corruption at the extended buffer");
		PERFORM_CLEANUP;
	}

	//check if we have overwritten the extended memory
	result = checkExtendedDummyBuffers(newExtendedIv, aIvLen, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
	if ( result != DX_SUCCESS)
	{
		REPORT_ERROR0("CheckExtendedDummyBuffers has found a memory corruption at the Iv extended buffer");
		PERFORM_CLEANUP;
	}



CLEANUP_SECTION:

    resultCleanup = DxTzService_AES128_TerminateContext(&aInternalCtx);
    if (DX_SUCCESS != resultCleanup ){
        REPORT_ERROR1("DxTzService_AES128_TerminateContext failed with return value 0x%08X",resultCleanup);
    }

    DxTzService_MemCpy(aOutputBuff,localOutputBuffer,aBufferLength);

    DxTzService_Free(localOutputBuffer);

    if (newExtendedToBuffer != DX_NULL)
        DxTzService_Free(newExtendedToBuffer);

    if (newExtendedIv != DX_NULL)
        DxTzService_Free(newExtendedIv);

    return result == DX_SUCCESS ? resultCleanup : result;
}

DxStatus cryptoAES128Ecb(const DxUint8 *aBuffer,
                         DxUint32 aBufferLength,
                         DxUint8 * aOutputBuff,
                          DxUint32 aOutputBufferLength,
                         DxUint8 * aKey,
                         DxUint32 aKeyLen,
                         EDxCipherDirection direction,
                         DxBool isAlinged)
{
    DxCipher_AES128ECB_Context_t aContext=DX_NULL;
    DxCipher_AES128_Context_t aInternalCtx=DX_NULL;
    DxStatus result = DX_SUCCESS;
    DxStatus resultCleanup;
    DxUint8 *localOutputBuffer=DX_NULL;
    DxUint8 *newExtendedToBuffer=DX_NULL;
    DxUint8 *pointerToBuffer=DX_NULL;
    DxUint32 extendedBufferSize=EXTENDED_BUFFER_SIZE;
#if 1
    if (aBufferLength > aOutputBufferLength){
        REPORT_ERROR0("out buffer is too small");
        PERFORM_CLEANUP;
    }

    localOutputBuffer=DxTzService_Malloc(aBufferLength);
    if (localOutputBuffer==DX_NULL){
        REPORT_ERROR1("DxTzService_Malloc failed to allocate memory of size 0x%08X.",aBufferLength);
        PERFORM_CLEANUP;
    }

    if(isAlinged==DX_FALSE)
        extendedBufferSize=extendedBufferSize-1;

    newExtendedToBuffer = expandTestingDataWithDummyBuffers(aBuffer, aBufferLength, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
    if (newExtendedToBuffer==DX_NULL){
        REPORT_ERROR0("ExpandTestingDataWithDummyBuffers failed to extend the memory for the test.");
        PERFORM_CLEANUP;
    }
    pointerToBuffer=newExtendedToBuffer+extendedBufferSize;// pointing to the real buffer

    result = DxTzService_AES128_CreateContext(&aInternalCtx);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128_CreateContext failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    QA_LOG_MSG("Key len is %d", aKeyLen);
#endif
    result = DxTzService_AES128ECB_Init(&aContext, aInternalCtx, aKey, aKeyLen, direction);
#if 1
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128ECB_Init failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    QA_LOG_MSG("DxTzService_AES128ECB_Init ok\n");

    if( direction==DXCIPHER_DEC){
        result = DxTzService_AES128ECB_DecryptData(aContext, pointerToBuffer, localOutputBuffer, aBufferLength);
        if (DX_SUCCESS != result )    {
            REPORT_ERROR1("DxTzService_AES128ECB_DecryptData failed with return value 0x%08X",result);
            PERFORM_CLEANUP;
        }
    }
    else{
        result = DxTzService_AES128ECB_EncryptData(aContext, pointerToBuffer, localOutputBuffer, aBufferLength);
        if (DX_SUCCESS != result )    {
            REPORT_ERROR1("DxTzService_AES128ECB_EncryptData failed with return value 0x%08X",result);
            PERFORM_CLEANUP;
        }
    }


    QA_LOG_MSG("DxTzService_AES128ECB_EncryptData ok\n");

    result = DxTzService_AES128ECB_Finish(&aContext);

    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128ECB_Finish failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    QA_LOG_MSG("DxTzService_AES128ECB_Finish ok\n");
	//check if we have overwritten the extended memory
	result = checkExtendedDummyBuffers(newExtendedToBuffer, aBufferLength, extendedBufferSize, eEXTEND_TO_BOTH_SIDE);
	if ( result != DX_SUCCESS)
	{
		REPORT_ERROR0("CheckExtendedDummyBuffers has found a memory corruption at the extended buffer");
		PERFORM_CLEANUP;
	}
    QA_LOG_MSG("checkExtendedDummyBuffers ok\n");

CLEANUP_SECTION:

    resultCleanup = DxTzService_AES128_TerminateContext(&aInternalCtx);
    if (DX_SUCCESS != resultCleanup ){
        REPORT_ERROR1("DxTzService_AES128_TerminateContext failed with return value 0x%08X",resultCleanup);
    }

    QA_LOG_MSG("DxTzService_AES128_TerminateContext ok\n");
    DxTzService_MemCpy(aOutputBuff,localOutputBuffer,aBufferLength);

    DxTzService_Free(localOutputBuffer);

    if (newExtendedToBuffer != DX_NULL)
        DxTzService_Free(newExtendedToBuffer);

    QA_LOG_MSG("cryptoAES128Ecb ok\n");
    return result == DX_SUCCESS ? resultCleanup : result;
#endif
    return DX_SUCCESS;
}



// private cleaning function
static void cryptoAES128Operation_printAndCleanAfterError(const DxChar *errorStr, void *clearBufferPtrToFree, void *encBufferPtrToFree)
{
	DxHwLogTrace(DX_FALSE, errorStr);
	DxTzService_Free(clearBufferPtrToFree);
	DxTzService_Free(encBufferPtrToFree);
}


DxStatus cryptoAES128Operation(DxTzServiceSharedMemRef *clearBufferInputSharedMemRefPtr, DxTzServiceSharedMemRef *encBufferInputSharedMemRefPtr, DxTzServiceMemRef* key, DxUint32 aesMode, DxUint32 aesDirection){
    DxCipher_AES128ECB_Context_t ecbContext = DX_NULL;
    DxCipher_AES128CBC_Context_t cbcContext = DX_NULL;
    DxCipher_AES128CTR_Context_t ctrContext = DX_NULL;
    DxCipher_AES128_Context_t internalCtx   = DX_NULL;
    DxStatus result = DX_SUCCESS;
    DxStatus resultCleanup = DX_SUCCESS;
    EDxCipherDirection chipherDirection;
    DxUint8 iv[16] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xE, 0xF};

	DxTzServiceSharedMemRef clearBufferSharedMemRef, encBufferSharedMemRef;
	DxByte *clearBuffer=DX_NULL, *encBuffer=DX_NULL;
	DxUint32 clearBufferSize = clearBufferInputSharedMemRefPtr->nSize, encBufferSize = encBufferInputSharedMemRefPtr->nSize;
	DxStatus operationStatus, duplicateStatus;

	// 1. get buffers from clearBufferInputSharedMemRef and encBufferInputSharedMemRef


	// allocate memory for clearBuffer
	if((clearBuffer = (DxByte*)DxTzService_Malloc(clearBufferInputSharedMemRefPtr->nSize)) == DX_NULL)
	{
		// allocation failed -> clean encBuffer and exit
		DxHwLogTrace(DX_FALSE, "cryptoAES128Operation: DxTzService_Malloc 1 failed");
		return DX_MEM_ALLOCATION_ERROR;
	}

	// allocate memory for encBuffer
	if((encBuffer = (DxByte*)DxTzService_Malloc(encBufferInputSharedMemRefPtr->nSize)) == DX_NULL)
	{
		// allocation failed
		DxHwLogTrace(DX_FALSE, "cryptoAES128Operation: DxTzService_Malloc 2 failed");
		DxTzService_Free(clearBuffer);
		return DX_MEM_ALLOCATION_ERROR;
	}

	// create handle and copy memory
	if( (duplicateStatus = CreateAndCopySharedMemRef( &clearBufferSharedMemRef, clearBuffer, clearBufferInputSharedMemRefPtr, 0, clearBufferSize )) != DX_SUCCESS)
	{
		cryptoAES128Operation_printAndCleanAfterError("cryptoAES128Operation: CreateAndDuplicateSharedMemRef 1 failed", clearBuffer, encBuffer);
		return duplicateStatus;
	}

	if( (duplicateStatus = CreateAndCopySharedMemRef( &encBufferSharedMemRef, encBuffer, encBufferInputSharedMemRefPtr,0,encBufferSize)) != DX_SUCCESS)
	{
		cryptoAES128Operation_printAndCleanAfterError("cryptoAES128Operation: CreateAndDuplicateSharedMemRef 2 failed", clearBuffer, encBuffer);
		return duplicateStatus;
	}

	// 2. manipulate the data
    if (eAES_DIRECTION_DEC == aesDirection){
        chipherDirection = DXCIPHER_DEC;
    } else {
        chipherDirection = DXCIPHER_ENC;
    }

    result = DxTzService_AES128_CreateContext(&internalCtx);
    if (DX_SUCCESS != result ){
        REPORT_ERROR1("DxTzService_AES128_CreateContext failed with return value 0x%08X",result);
        PERFORM_CLEANUP;
    }

    switch(aesMode){
    case eAES_MODE_CBC:
        result = DxTzService_AES128CBC_Init(&cbcContext, internalCtx, key->pBuffer, key->nSize, chipherDirection);

        if (DX_SUCCESS != result ){
            REPORT_ERROR1("DxTzService_AES128CBC_Init failed with return value 0x%08X",result);
            PERFORM_CLEANUP;
        }

        if (eAES_DIRECTION_DEC == aesDirection){

            result = DxTzService_AES128CBC_DecryptData(cbcContext, encBuffer, clearBuffer, clearBufferSize, iv);

            if (DX_SUCCESS != result ){
                REPORT_ERROR1("DxTzService_AES128CBC_DecryptData failed with return value 0x%08X",result);
                PERFORM_CLEANUP;
            }
        } else {

            result = DxTzService_AES128CBC_EncryptData(cbcContext, clearBuffer, encBuffer, encBufferSize, iv);

            if (DX_SUCCESS != result ){
                REPORT_ERROR1("DxTzService_AES128CBC_EncryptData failed with return value 0x%08X",result);
                PERFORM_CLEANUP;
            }
        }

        break;
    case eAES_MODE_CTR:
        result = DxTzService_AES128CTR_Init(&ctrContext, internalCtx, key->pBuffer, key->nSize, chipherDirection);

        if (DX_SUCCESS != result ){
            REPORT_ERROR1("DxTzService_AES128CTR_Init failed with return value 0x%08X",result);
            PERFORM_CLEANUP;
        }

        if (eAES_DIRECTION_DEC == aesDirection){

            result = DxTzService_AES128CTR_DecryptData(ctrContext, encBuffer, clearBuffer, clearBufferSize, iv);

            if (DX_SUCCESS != result ){
                REPORT_ERROR1("DxTzService_AES128CTR_DecryptData failed with return value 0x%08X",result);
                PERFORM_CLEANUP;
            }
        } else {

            result = DxTzService_AES128CTR_EncryptData(ctrContext, clearBuffer, encBuffer, encBufferSize, iv);

            if (DX_SUCCESS != result ){
                REPORT_ERROR1("DxTzService_AES128CTR_EncryptData failed with return value 0x%08X",result);
                PERFORM_CLEANUP;
            }
        }

        break;
    case eAES_MODE_ECB:

        result = DxTzService_AES128ECB_Init(&ecbContext, internalCtx, key->pBuffer, key->nSize, chipherDirection);

        if (DX_SUCCESS != result ){
            REPORT_ERROR1("DxTzService_AES128ECB_Init failed with return value 0x%08X",result);
            PERFORM_CLEANUP;
        }

        if (eAES_DIRECTION_DEC == aesDirection){

            result = DxTzService_AES128ECB_DecryptData(ecbContext, encBuffer, clearBuffer, clearBufferSize);

            if (DX_SUCCESS != result ){
                REPORT_ERROR1("DxTzService_AES128ECB_DecryptData failed with return value 0x%08X",result);
                PERFORM_CLEANUP;
            }
        } else {

            result = DxTzService_AES128ECB_EncryptData(ecbContext, clearBuffer, encBuffer, encBufferSize);

            if (DX_SUCCESS != result ){
                REPORT_ERROR1("DxTzService_AES128ECB_EncryptData failed with return value 0x%08X",result);
                PERFORM_CLEANUP;
            }
        }
    };


	// 3. copy manipulated data to clearBufferInputSharedMemRef and encBufferInputSharedMemRef
	if( (operationStatus = DxTzService_MemCpyEx(clearBufferInputSharedMemRefPtr, 0, &clearBufferSharedMemRef, 0, clearBufferSize)) != DX_SUCCESS)
	{
		// memcopy failed -> clean and exit
		cryptoAES128Operation_printAndCleanAfterError("cryptoAES128Operation: DxTzService_MemCpyEx 1 failed", clearBuffer, encBuffer);
		return operationStatus;
	}

	if( (operationStatus = DxTzService_MemCpyEx(encBufferInputSharedMemRefPtr, 0, &encBufferSharedMemRef, 0, encBufferSize)) != DX_SUCCESS)
	{
		// memcopy failed -> clean and exit
		cryptoAES128Operation_printAndCleanAfterError("cryptoAES128Operation: DxTzService_MemCpyEx 2 failed", clearBuffer, encBuffer);
		return operationStatus;
	}


CLEANUP_SECTION:

    if (DX_NULL != ecbContext){
        resultCleanup = DxTzService_AES128ECB_Finish(&ecbContext);
    }

    if (DX_NULL != cbcContext){
        resultCleanup = DxTzService_AES128CBC_Finish(&cbcContext);
    }

    if (DX_NULL != ctrContext){
        resultCleanup = DxTzService_AES128CTR_Finish(&ctrContext);
    }

    if (DX_NULL != internalCtx){
        resultCleanup = DxTzService_AES128_TerminateContext(&internalCtx);
    }

	// allocation cleanup
	DxTzService_Free(clearBuffer);
	DxTzService_Free(encBuffer);

    return (result == DX_SUCCESS ? resultCleanup : result);
}


DxStatus cryptoRandomGenerate(void *pBuf, DxUint32 uiSize)
{
	DxStatus result = DX_SUCCESS;

	result = DxTzService_RandomGenerate((DxUint8 *)pBuf, uiSize);

	return result;
}

