#include "QaTestFuncDeclaration.h"
#include "DxTzServiceAPI.h"
#include "DxTzServiceCryptoAPI.h"
#include "QaTestEnumeration.h"
#include "QaTestDataStruct.h"

#include "QaUtils.h"

#ifndef DX_BITS_IN_BYTE
#define DX_BITS_IN_BYTE 8
#endif

//-------------------------------------- RSA Test functions -------------------------------

DxStatus cryptoRSA_encryptionTest(DxUint32 commandID, DxTzServiceParameter *params, DxUint32 nParamTypes)
{
	// param[0].tmpref.buffer - test data structure
	// param[1].tmpref.buffer - output buffer
	// param[2].value.a - bit set of test options (TST_RSA_CRT_OPT & TST_RSA_ALIGNED_OPT)
	// param[2].value.b - ESHA_MODE (SHA1(0) or SHA256(1)) - unused in V1.5 RSA encryption test
	// param[3].value.a - [out] - output data size
	DxStatus result;
	EDxTzGenericRsaHashOpMode_t hashMode;
	DxByte *inData;
	DxUint16 inDataSize;
	DxByte *outData;
	DxUint16 outDataSize;
	struct QaRSA_EncryptTestData *testData;
	DxBool alignedTest;
	DxBool isCRTkey;
	DxBool isV1_5 = (commandID==QA_TST_CRYPTO_PKCS1_V1_5_RSA_ENCRYPT || commandID==QA_TST_CRYPTO_PKCS1_V1_5_RSA_DECRYPT)? DX_TRUE : DX_FALSE;

	QA_LOG_MSG("cryptoRSA_encryptionTest called");

	if(DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_MEMREF_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_MEMREF_OUTPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_VALUE_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_VALUE_OUTPUT)
	{
		REPORT_ERROR0("cryptoRSA_encryptionTest: bad parameter types");
		return DX_TZ_BAD_PARAMETERS;
	}
	if(params[0].memRef.pBuffer==DX_NULL)
	{
		REPORT_ERROR0("cryptoRSA_encryptionTest: tstData is NULL");
		return DX_TZ_BAD_PARAMETERS;
	}
	if(params[0].memRef.nSize != sizeof(struct QaRSA_EncryptTestData))
	{
		REPORT_ERROR1("cryptoRSA_encryptionTest: invalid size of tstData (%d)",params[0].memRef.nSize);
		return DX_TZ_BAD_PARAMETERS;
	}

	if(params[1].memRef.pBuffer==DX_NULL || params[1].memRef.nSize < TST_MAX_MOD_SIZE_IN_BYTES)
	{
		REPORT_ERROR2("cryptoRSA_encryptionTest invalid params: outBuff=0x%x, outBuffSize=%u",
			(DxUint32)(params[1].memRef.pBuffer), params[1].memRef.nSize);
		return DX_TZ_BAD_PARAMETERS;
	}

	if(params[2].value.a > TST_RSA_MAX_OPT || params[2].value.b > eSHA_TYPE_256)
	{
		REPORT_ERROR2("cryptoRSA_encryptionTest: invalid params testOpt=%d, hash=%d",
									params[2].value.a, params[2].value.b);
		return DX_TZ_BAD_PARAMETERS;
	}

	testData = (struct QaRSA_EncryptTestData *)params[0].memRef.pBuffer;
	outData = (DxByte *)params[1].memRef.pBuffer;
	outDataSize = (DxUint16)params[1].memRef.nSize;

	isCRTkey = ((params[2].value.a & TST_RSA_CRT_OPT) ? DX_TRUE : DX_FALSE);
	alignedTest = ((params[2].value.a & TST_RSA_ALIGNED_OPT) ? DX_TRUE : DX_FALSE);
	hashMode = (params[2].value.b== eSHA_TYPE_1 ? DX_TZ_RSA_HASH_SHA1_mode : DX_TZ_RSA_HASH_SHA256_mode);

	inData = testData->inputData;
	inDataSize = (DxUint16)testData->inputDataSize;
	if(!alignedTest)
	{
		inData++;
		outData++;
	}
	switch(commandID)
	{
	case QA_TST_CRYPTO_OAEP_RSA_OAEP_ENCRYPT:
	case QA_TST_CRYPTO_PKCS1_V1_5_RSA_ENCRYPT:
		{
			DxTzService_RSA_PubKey_s pubKey;
			pubKey.bitLength = testData->modulusSize * DX_BITS_IN_BYTE;
			pubKey.type = DX_TZ_RSA_PUBLIC_KEY;
			pubKey.Modulus = testData->modulus_N;
			pubKey.ModulusSize = testData->modulusSize;
			pubKey.Exp = testData->publicExponent_E;
			pubKey.ExpSize = testData->pubExponentSize;
			if(!alignedTest)
			{
				inDataSize--;
			}
			if(isV1_5)
			{
				result = DxTzService_RSA_PKCS1v15_EncryptData(&pubKey, inData, inDataSize, outData);
			}
			else
			{
				result = DxTzService_RSA_OAEP_EncryptData(&pubKey, hashMode, inData, inDataSize, outData);
			}
			params[1].memRef.nSize = testData->modulusSize;
			params[3].value.a = testData->modulusSize;
			if(!alignedTest)
				params[1].memRef.nSize++;
		}
		break;
	case QA_TST_CRYPTO_OAEP_RSA_OAEP_DECRYPT:
	case QA_TST_CRYPTO_PKCS1_V1_5_RSA_DECRYPT:
		{
			DxTzService_RSA_PrivKey_s privKey;
			privKey.bitLength = testData->modulusSize * DX_BITS_IN_BYTE;
			privKey.type = (isCRTkey? DX_TZ_RSA_PRIVATE_KEY_CRT : DX_TZ_RSA_PRIVATE_KEY);
			privKey.Modulus = testData->modulus_N;
			privKey.ModulusSize = testData->modulusSize;
			privKey.Exp = testData->publicExponent_E;
			privKey.ExpSize = testData->pubExponentSize;
			privKey.privExp = (testData->privExponentSize ? testData->privetExponent_D : DX_NULL);
			privKey.privExpSize = testData->privExponentSize;
			privKey.P = testData->P;
			privKey.PSize = testData->PSize;
			privKey.Q = testData->Q;
			privKey.QSize = testData->QSize;
			privKey.Dp = testData->dP;
			privKey.DpSize = testData->dPSize;
			privKey.Dq = testData->dQ;
			privKey.DqSize = testData->dQSize;
			privKey.QInt = testData->Qinv;
			privKey.QIntSize = testData->QinvSize;
			if(isV1_5)
			{
				result = DxTzService_RSA_PKCS1v15_DecryptData(&privKey, inData, inDataSize, outData, &outDataSize);
			}
			else
			{
				result = DxTzService_RSA_OAEP_DecryptData(&privKey, hashMode, inData, inDataSize, outData, &outDataSize);
			}
			params[1].memRef.nSize = outDataSize;
			params[3].value.a = outDataSize;
			if(!alignedTest)
				params[1].memRef.nSize++;
		}
		break;
	default:
		REPORT_ERROR1("cryptoRSA_encryptionTest: invalid commandID=0x%02x", commandID);
		return DX_FAILURE;
	}

	if(result != DX_SUCCESS)
	{
		REPORT_ERROR1("cryptoRSA_encryptionTest  failed, result=0x%X", result);
	}

	return result;
}

DxStatus cryptoRSA_signVerify(DxUint32 commandID, DxTzServiceParameter *params, DxUint32 nParamTypes)
{
	// param[0].tmpref.buffer - test data structure
	// param[1].value.a - ESHA_MODE (SHA1(0) or SHA256(1))
	// param[2].value.b - intput: 0xFF; output: verification succeeded (1) failed(0)
	DxStatus result;
	EDxTzGenericRsaHashOpMode_t hashMode;
	DxByte *inData;
	DxUint16 inDataSize;
	DxByte *signature;
	DxUint16 saltLen;
	struct QaRSA_VerifySignTestData *testData;
	DxBool isV1_5 = (commandID==QA_TST_CRYPTO_PKCS1_V1_5_RSA_SIGN_VERIFY ? DX_TRUE : DX_FALSE);
	DxTzService_RSA_PubKey_s pubKey;

	QA_LOG_MSG("cryptoRSA_signVerify called");

	if(DX_TZ_PARAM_TYPE_GET(nParamTypes, 0) != DX_TZ_PARAM_TYPE_MEMREF_INPUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 1) != DX_TZ_PARAM_TYPE_VALUE_INOUT ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 2) != DX_TZ_PARAM_TYPE_NONE ||
		DX_TZ_PARAM_TYPE_GET(nParamTypes, 3) != DX_TZ_PARAM_TYPE_NONE)
	{
		REPORT_ERROR0("cryptoRSA_signVerify: bad parameter types");
		return DX_TZ_BAD_PARAMETERS;
	}
	if(params[0].memRef.pBuffer==DX_NULL)
	{
		REPORT_ERROR0("cryptoRSA_signVerify: tstData is NULL");
		return DX_TZ_BAD_PARAMETERS;
	}
	if(params[0].memRef.nSize != sizeof(struct QaRSA_VerifySignTestData))
	{
		REPORT_ERROR1("cryptoRSA_signVerify: invalid size of tstData (%d)",params[0].memRef.nSize);
		return DX_TZ_BAD_PARAMETERS;
	}

	if(params[1].value.a > eSHA_TYPE_256)
	{
		REPORT_ERROR1("cryptoRSA_signVerify: invalid params hash=%d", params[1].value.a);
		return DX_TZ_BAD_PARAMETERS;
	}

	testData = (struct QaRSA_VerifySignTestData *)params[0].memRef.pBuffer;
	hashMode = (params[1].value.a== eSHA_TYPE_1 ? DX_TZ_RSA_HASH_SHA1_mode : DX_TZ_RSA_HASH_SHA256_mode);

	inData = testData->inputData;
	inDataSize = (DxUint16)testData->inputDataSize;
	signature = testData->signature;
	saltLen =(DxUint16) testData->saltLength;

	pubKey.bitLength = testData->modulusSize * DX_BITS_IN_BYTE;
	pubKey.type = DX_TZ_RSA_PUBLIC_KEY;
	pubKey.Modulus = testData->modulus_N;
	pubKey.ModulusSize = testData->modulusSize;
	pubKey.Exp = testData->publicExponent_E;
	pubKey.ExpSize = testData->pubExponentSize;

	if(isV1_5)
	{
		result = DxTzService_RSA_PKCS1v15_VerifyDataSignature(&pubKey, hashMode, inData, inDataSize, signature);
	}
	else
	{
		result = DxTzService_RSA_PSS_VerifyDataSignature(&pubKey, hashMode, saltLen, inData, inDataSize, signature);
	}

	if(result != DX_SUCCESS)
	{
		params[1].value.b = 0;
		REPORT_ERROR1("cryptoRSA_signVerify failed, result=0x%X", result);
	}
	else
	{
		params[1].value.b = 1;
	}
	return result;
}
