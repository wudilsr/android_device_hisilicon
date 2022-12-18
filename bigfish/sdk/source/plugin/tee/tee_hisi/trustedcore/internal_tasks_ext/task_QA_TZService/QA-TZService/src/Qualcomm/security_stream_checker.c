#include "security_stream_checker.h"


uint32 security_stream_checker_init( IN	uint32 caller_application,
 							 	 	 IN	uint32 crypto_mode
								   )
{
	return TZAPP_SCHK_R_OK;
}


uint32 security_stream_checker( uint32	caller_application,
							    uint32	crypto_mode,
								uint32	stream_type,
								uint8  *data,
								uint32	data_length,
								uint8  *vector1,
								uint8  *vector2
							  )
{
	uint32 uiSum = 0;
	uint32 i	 = 0;



	// Check if vectors are as expected
	// The vector is hard-coded in the test to {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF}

	// Vector1 should never be NULL
	if(vector1 == NULL)
	{
		return TZAPP_SCHK_R_INVALID_PARAM;
	}

	// Vector1 should always point to the hard-coded vector
	if(vector1[0] != 0x00)
	{
		return TZAPP_SCHK_R_INVALID_PARAM + 1;
	}

	// In TZAPP_SCHK_AES128_CBC case, vector2 must be NULL
	if( (crypto_mode == TZAPP_SCHK_AES128_CBC) && (vector2 != NULL) )
	{
		return TZAPP_SCHK_R_INVALID_PARAM + 2;
	}

	// In TZAPP_SCHK_AES128_CTR case, vector1 should not be NULL, and vector2 should point to index 8 (counting from 0) of the hard-coded vector
	if(crypto_mode == TZAPP_SCHK_AES128_CTR)
	{
		if(vector2 == NULL)
		{
			return TZAPP_SCHK_R_INVALID_PARAM + 3;
		}

		if(vector2[0] != 0x08)
		{
			return TZAPP_SCHK_R_INVALID_PARAM + 4;
		}
	}

	// data should not be NULL
	if(data == NULL)
	{
		return TZAPP_SCHK_R_INVALID_PARAM + 5;
	}


	// Calculate sum of items to compare later with the expected sum
	for(i = 0; i < data_length; i++)
	{
		uiSum += data[i];
	}

	// Compare calculate sum with expected sum (stream_type is used to pass the expected sum)
	if(uiSum != stream_type)
	{
		return TZAPP_SCHK_R_INVALID_PARAM + 6;
	}


	return TZAPP_SCHK_R_OK;
}
