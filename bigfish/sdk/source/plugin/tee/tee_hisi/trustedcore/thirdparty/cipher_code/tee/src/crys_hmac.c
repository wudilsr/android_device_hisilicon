/*******************************************************************  
* (c) Copyright 2011-2012 Discretix Technologies Ltd.              *
* This software is protected by copyright, international           *
* treaties and patents.                                            *
* Use of this Software as part of or with the Discretix CryptoCell *
* or Packet Engine products is governed by the products'           *
* commercial end user license agreement ("EULA").                  *
* It is possible that copies of this Software might be distributed *
* under some type of GNU General Public License ("GPL").           *
* Notwithstanding any such distribution under the terms of GPL,    *
* GPL does not govern the use of this Software as part of or with  *
* the Discretix CryptoCell or Packet Engine products, for which a  *
* EULA is required.                                                *
* If the product's EULA allows any copy or reproduction of this    *
* Software, then such copy or reproduction must include this       *
* Copyright Notice as well as any other notices provided           *
* thereunder.                                                      *
********************************************************************/
#include "hi_type.h"
#include "drv_cipher.h"
#include "drv_cipher_intf.h"
#include "drv_cipher_define.h"
#include "sre_debug.h"
#include "hi_mmz.h"
#include "crys_aes.h"
#include <boot.h>
#include "dx_pal_types.h"
#include "crys_hash.h"
#include "crys_hmac.h"
#include "crys_hmac_error.h"
#include "dx_error.h"


/************************ Defines ******************************/
#define  HI_ERR_CIPHER_NOT_INIT                     (HI_S32)(0x804D0001)
#define  HI_ERR_CIPHER_INVALID_HANDLE               (HI_S32)(0x804D0002)
#define  HI_ERR_CIPHER_INVALID_POINT                (HI_S32)(0x804D0003)
#define  HI_ERR_CIPHER_INVALID_PARA                 (HI_S32)(0x804D0004)
#define  HI_ERR_CIPHER_FAILED_INIT                  (HI_S32)(0x804D0005)
#define  HI_ERR_CIPHER_FAILED_GETHANDLE             (HI_S32)(0x804D0006)
#define  HI_ERR_CIPHER_FAILED_RELEASEHANDLE         (HI_S32)(0x804D0007)
#define  HI_ERR_CIPHER_FAILED_CONFIGAES             (HI_S32)(0x804D0008)
#define  HI_ERR_CIPHER_FAILED_CONFIGDES             (HI_S32)(0x804D0009)
#define  HI_ERR_CIPHER_FAILED_ENCRYPT               (HI_S32)(0x804D000A)
#define  HI_ERR_CIPHER_FAILED_DECRYPT               (HI_S32)(0x804D000B)
#define  HI_ERR_CIPHER_BUSY                         (HI_S32)(0x804D000C)
#define  HI_ERR_CIPHER_NO_AVAILABLE_RNG             (HI_S32)(0x804D000D)

#define HMAC_MMZ_BUFF_SIZE  (0x2000)
#define HASH_BLOCK_SIZE		(64)
#define HASH_PAD_MAX_LEN	(64)
#define HASH1_SIGNATURE_SIZE		(20)
#define HASH256_SIGNATURE_SIZE		(32)

/************************ Type definitions **********************/
typedef struct hiAESUserContext_t
{
    HI_HANDLE hHash;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
    HI_U8 au8HmacKey[HASH_BLOCK_SIZE];
    HI_U32 u32HmacKeyLen;
}HMACUserContext_t;

/************************ Private Functions **********************/


/*!
 * Converts Symmetric Adaptor return code to CRYS error code.
 * 
 * \param symRetCode Symmetric Adaptor return error.
 * \param errorInfo Ignored.
 *  
 * \return CRYSError_t one of CRYS_* error codes defined in crys_error.h
 */
static CRYSError_t SymAdaptor2CrysHmacErr(int symRetCode, DxUint32_t errorInfo)
{
    CRYSError_t err;
    
	switch (symRetCode) {
	case HI_ERR_CIPHER_NOT_INIT:
		err = CRYS_HMAC_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_FAILED_INIT:
        err = CRYS_HMAC_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_INVALID_POINT:
		err =  CRYS_HMAC_DATA_IN_POINTER_INVALID_ERROR;
        break;
	case HI_ERR_CIPHER_INVALID_PARA:
        err = CRYS_HMAC_ILLEGAL_PARAMS_ERROR;
        break;
	case HI_ERR_CIPHER_BUSY:
	case HI_ERR_CIPHER_NO_AVAILABLE_RNG:
        err = CRYS_HMAC_IS_NOT_SUPPORTED;
        break;
    case HI_SUCCESS:
        err = CRYS_OK;
        break;
	default:
		err = CRYS_FATAL_ERROR;
        break;
	}

    return err | errorInfo;
}




static HI_S32 CIPHER_HmacKeyInit(HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr, HI_U8 au8Hmackey[HASH_BLOCK_SIZE], HI_U32 *pKeyLen)
{
    HI_S32 ret = HI_SUCCESS;
    HI_HANDLE hHash = 0;

    if((pstHashAttr == NULL)||(pstHashAttr->pu8HMACKey == NULL)||(pstHashAttr->u32HMACKeyLen == 0))
    {
        HI_ERR_CIPHER("Invalid parameters.\n");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*key length is less than 64bytes, copy directly*/
    if(pstHashAttr->u32HMACKeyLen <= HASH_BLOCK_SIZE)
    {
        memcpy(au8Hmackey, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen);
		*pKeyLen = pstHashAttr->u32HMACKeyLen;
        return HI_SUCCESS;
    }

    /*key length more than 64bytes, calcute the hash result*/
    ret = Cipher_HashInit(pstHashAttr, &hHash);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Cipher_HashInit failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    ret = Cipher_HashUpdate(hHash, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Cipher_HashUpdate failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    ret = Cipher_HashFinal(hHash,au8Hmackey);
    if(ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Cipher_HashFinal failure, ret=%d\n", ret);
        return HI_FAILURE;
    }

    if ( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHashAttr->eShaType )
	{
		*pKeyLen = 20;
	}
	else
	{
		*pKeyLen = 32;
	}

    return HI_SUCCESS;
}

/************************ Public Functions **********************/

/**
 * This function initializes the HMAC machine on the CRYS level.
 *
 * The function allocates and initializes the HMAC Context .
 * The function receives as input a pointer to store the context handle to HMAC Context. 
 *
 * The function executes a HASH_init session and processes a HASH update 
 * on the Key XOR ipad and stores it in the context.
 *
 * @param[in] ContextID_ptr - A pointer to the HMAC context buffer allocated by the user 
 *                       that is used for the HMAC machine operation.
 *
 * @param[in] OperationMode - The operation mode: MD5 or SHA1.
 *
 * @param[in] key_ptr - The pointer to the user's key buffer, 
 *			or its digest (if larger than the hash block size).
 *
 * @param[in] keySize - The size of the received key. Must not exceed the associated
 *                      hash block size. For larger keys the caller must provide
 *                      a hash digest of the key as the actual key.
 *
 * @return CRYSError_t - On success the function returns the value CRYS_OK, 
 *			and on failure a non-ZERO error.
 *      
 */
CIMPORT_C CRYSError_t CRYS_HMAC_Init(CRYS_HMACUserContext_t *ContextID_ptr,
                           CRYS_HASH_OperationMode_t OperationMode,
                           DxUint8_t *key_ptr,
                           DxUint16_t keySize)
{
    HI_S32 s32Ret;
    HMACUserContext_t *pstHMACUserContext;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U8 u8KeyPad[HASH_BLOCK_SIZE];
    HI_U32 i;

	/* if the users context ID pointer is DX_NULL return an error */
	if( ContextID_ptr == DX_NULL ) {
		return CRYS_HMAC_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

	/* check if the key pointer is valid */
	if( key_ptr == DX_NULL ) {
		return CRYS_HMAC_INVALID_KEY_POINTER_ERROR;
	}

    pstHMACUserContext = (HMACUserContext_t *)ContextID_ptr;
    memset(pstHMACUserContext, 0, sizeof(HMACUserContext_t));
	
	/* check if the key size is valid */
	if (keySize == 0) {
		return CRYS_HMAC_UNVALID_KEY_SIZE_ERROR;
	}

    switch (OperationMode) 
    {
		case CRYS_HASH_SHA1_mode:
            stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA1;
            break;
        case CRYS_HASH_SHA256_mode:
            stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
			break;
		default:
			return CRYS_HMAC_ILLEGAL_OPERATION_MODE_ERROR;
	}
    /* Init hmac key */
    stHashAttr.pu8HMACKey = key_ptr;
    stHashAttr.u32HMACKeyLen = keySize;
    pstHMACUserContext->enHashType = stHashAttr.eShaType;
    s32Ret = CIPHER_HmacKeyInit(&stHashAttr, pstHMACUserContext->au8HmacKey, &pstHMACUserContext->u32HmacKeyLen);
	if ( HI_SUCCESS != s32Ret )
	{
	    HI_ERR_CIPHER("Hmac key initial failed!\n");
		return SymAdaptor2CrysHmacErr(s32Ret, 0);
	} 

	/* hash i_key_pad and message start */
	s32Ret = Cipher_HashInit(&stHashAttr, &pstHMACUserContext->hHash);
	if ( HI_SUCCESS != s32Ret )
	{
	    HI_ERR_CIPHER("hash i_key_pad and message start failed!\n");
		return SymAdaptor2CrysHmacErr(s32Ret, 0);
	}

	/* generate i_key_pad */
	memset(u8KeyPad, 0x36, HASH_BLOCK_SIZE);
    for(i=0; i < pstHMACUserContext->u32HmacKeyLen; i++)
    {
        u8KeyPad[i] = u8KeyPad[i] ^ pstHMACUserContext->au8HmacKey[i];
    }

	/* hash i_key_pad update */
	s32Ret = Cipher_HashUpdate(pstHMACUserContext->hHash, u8KeyPad, HASH_BLOCK_SIZE);
	if ( HI_SUCCESS != s32Ret )
	{
	    HI_ERR_CIPHER("hash i_key_pad and message update failed!\n"); 
		return SymAdaptor2CrysHmacErr(s32Ret, 0);
	}

	return DX_CRYS_RETURN_ERROR(s32Ret, 0, SymAdaptor2CrysHmacErr);
}


/**
 * This function processes a HMAC block of data via the HASH hardware/software.
 * The function receives as input a handle to the HMAC Context, 
 * and performs a HASH update on the data described below.
 * 
 * @param[in] ContextID_ptr - A pointer to the HMAC context buffer allocated by the user 
 *                       that is used for the HMAC machine operation.
 *
 * @param DataIn_ptr - A pointer to the buffer that stores the data to be hashed.
 * 
 * @param DataInSize - The size of the data to be hashed, in bytes. 
 *
 * @return CRYSError_t - On success the function returns CRYS_OK, 
 *			and on failure a non-ZERO error.
 */

CIMPORT_C CRYSError_t CRYS_HMAC_Update(CRYS_HMACUserContext_t  *ContextID_ptr,
                             DxUint8_t                 *DataIn_ptr,
                             DxUint32_t                 DataInSize )
{
    HI_S32 s32Ret;
    HMACUserContext_t *pstHMACUserContext;
	/* if the users context ID pointer is DX_NULL return an error */
	if( ContextID_ptr == DX_NULL ) {
		return CRYS_HMAC_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

	/* if the users Data In pointer is illegal and the size is not 0 return an error */
	if( (DataIn_ptr == DX_NULL) && DataInSize ) {
		return CRYS_HMAC_DATA_IN_POINTER_INVALID_ERROR;
	}
	   
	/* if the data size is zero no need to execute an update , return CRYS_OK */
	if( DataInSize == 0 ) {
		return CRYS_OK;
	}

    pstHMACUserContext = (HMACUserContext_t *)ContextID_ptr;
	s32Ret = Cipher_HashUpdate(pstHMACUserContext->hHash, DataIn_ptr, DataInSize);
	if ( HI_SUCCESS != s32Ret )
	{
	    HI_ERR_CIPHER("hmac message update failed!\n"); 
		return SymAdaptor2CrysHmacErr(s32Ret, 0);
	}

	return CRYS_OK;
}


/**
 * This function finalizes the HMAC processing of a data block.
 * The function receives as input a handle to the HMAC Context that was previously initialized 
 * by a CRYS_HMAC_Init function or by a CRYS_HMAC_Update function.
 * This function finishes the HASH operation on the ipad and text, and then 
 * executes a new HASH operation with the key XOR opad and the previous HASH operation result.
 *
 *  @param[in] ContextID_ptr - A pointer to the HMAC context buffer allocated by the user 
 *                       that is used for the HMAC machine operation.
 *
 *  @retval HmacResultBuff - A pointer to the target buffer where the 
 *                       HMAC result stored in the context is loaded to.
 *
 * @return CRYSError_t - On success the function returns CRYS_OK, 
 *			and on failure a non-ZERO error.
 */
CIMPORT_C CRYSError_t CRYS_HMAC_Finish( CRYS_HMACUserContext_t  *ContextID_ptr,
					CRYS_HASH_Result_t       HmacResultBuff )
{
    HI_S32 s32Ret;
    HMACUserContext_t *pstHMACUserContext;
	HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U8 hash_sum_1[32];
    HI_HANDLE hHash = HI_INVALID_HANDLE;
    HI_U8 o_key_pad[HASH_BLOCK_SIZE];
    HI_U32 i;
	/* if the users context ID pointer is DX_NULL return an error */
	if( ContextID_ptr == DX_NULL ) {
		return CRYS_HMAC_INVALID_USER_CONTEXT_POINTER_ERROR;
	}
	
    pstHMACUserContext = (HMACUserContext_t *)ContextID_ptr;

    /* hash i_key_pad+message finished */
    memset(hash_sum_1, 0, sizeof(hash_sum_1));
    s32Ret = Cipher_HashFinal(pstHMACUserContext->hHash, hash_sum_1);
    if(s32Ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Final i_key_pad+message failure, ret=%d\n", s32Ret);
        return SymAdaptor2CrysHmacErr(s32Ret, 0);
    }

    /* generate o_key_pad */
    memset(o_key_pad, 0x5c, HASH_BLOCK_SIZE);
    for(i=0; i < pstHMACUserContext->u32HmacKeyLen; i++)
    {
        o_key_pad[i] = o_key_pad[i] ^ pstHMACUserContext->au8HmacKey[i];
    }

    /* hash o_key_pad+hash_sum_1 start */
	memset(&stHashAttr, 0, sizeof(stHashAttr));
	stHashAttr.eShaType = pstHMACUserContext->enHashType;
    s32Ret = Cipher_HashInit(&stHashAttr, &hHash);
    if(s32Ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Init o_key_pad+hash_sum_1 failure, ret=%d\n", s32Ret);
        return SymAdaptor2CrysHmacErr(s32Ret, 0);
    }

    /* hash o_key_pad */
    s32Ret = Cipher_HashUpdate(hHash, (HI_U8 *)o_key_pad, HASH_BLOCK_SIZE);
    if(s32Ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Update o_key_pad failure, ret=%d\n", s32Ret);
        return SymAdaptor2CrysHmacErr(s32Ret, 0);
    }

    /* hash hash_sum_1 */
	if ( HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1 == pstHMACUserContext->enHashType)
	{
	    s32Ret = Cipher_HashUpdate(hHash, (HI_U8 *)hash_sum_1, 20);	
	}
	else
	{
	    s32Ret = Cipher_HashUpdate(hHash, (HI_U8 *)hash_sum_1, 32);
	}

    if(s32Ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Update hash_sum_1 failure, ret=%d\n", s32Ret);
        return SymAdaptor2CrysHmacErr(s32Ret, 0);
    }

    /* hash o_key_pad+hash_sum_1 finished */
    s32Ret = Cipher_HashFinal(hHash, (HI_U8*)HmacResultBuff);
    if(s32Ret != HI_SUCCESS)
    {
        HI_ERR_CIPHER("Hash Final o_key_pad+hash_sum_1 failure, ret=%d\n", s32Ret);
        return SymAdaptor2CrysHmacErr(s32Ret, 0);
    }


	return CRYS_OK;
}

/**
 * @brief This function clears the hash context
 *
 * @param[in] ContextID_ptr - a pointer to the HMAC context
 *  					 buffer allocated by the user that is
 *  					 used for the HMAC machine operation.
 *  					 This should be the same context that
 *  					 was used on the previous call of this
 *  					 session.
 *
 * @return CRYSError_t - On success CRYS_OK is returned, on failure a
 *                        value MODULE_* crys_hash_error.h
 */
CEXPORT_C CRYSError_t CRYS_HMAC_Free(CRYS_HMACUserContext_t *ContextID_ptr)
{
	if ( ContextID_ptr == DX_NULL ) {
		return CRYS_HMAC_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

	memset(ContextID_ptr, 0, sizeof(CRYS_HMACUserContext_t));
   
	return CRYS_OK;   
}


/**
 * This function provide HASH function to process one buffer of data.
 * The function allocates an internal HASH Context , it initializes the 
 * HASH Context with the cryptographic attributes that are needed for 
 * the HASH block operation ( initialize H's value for the HASH algorithm ).
 * Then the function loads the Hardware with the initializing values and after 
 * that process the data block using the hardware to do hash .
 * At the end the function return the message digest of the data buffer .
 *
 *
 * @param[in] OperationMode - The operation mode : MD5 or SHA1.
 *
 * @param[in] key_ptr - The pointer to the users key buffer.
 *
 * @oaram[in] keySize - The size of the received key.
 * 
 * @param[in] ContextID_ptr - a pointer to the HMAC context buffer allocated by the user that
 *                       is used for the HMAC machine operation.
 *
 * @param[in] DataIn_ptr - The pointer to the buffer of the input data to the HMAC. The pointer does 
 *                         not need to be aligned. On CSI input mode the pointer must be equal to
 *                         value (0xFFFFFFFC | DataInAlignment). 
 * 
 * @param[in] DataInSize - The size of the data to be hashed in bytes. On CSI data transfer mode the size must  
 *                         multiple of HASH_BLOCK_SIZE for used HASH mode.
 *
 * param[out] HashResultBuff - a pointer to the target buffer where the 
 *                      HMAC result stored in the context is loaded to.
 *
 * @return CRYSError_t on success the function returns CRYS_OK else non ZERO error.
 *
 */
CIMPORT_C CRYSError_t CRYS_HMAC(CRYS_HASH_OperationMode_t   OperationMode, 
				DxUint8_t                  *key_ptr,
				DxUint16_t                  keySize,
				DxUint8_t                  *DataIn_ptr,
				DxUint32_t                  DataSize,
				CRYS_HASH_Result_t          HmacResultBuff)
{
	CRYS_HMACUserContext_t  UserContext;
	CRYSError_t Error = CRYS_OK;

	Error = CRYS_HMAC_Init(&UserContext, OperationMode, key_ptr, keySize);
	if(Error != CRYS_OK) {
		goto end;
	}

	Error = CRYS_HMAC_Update(&UserContext, DataIn_ptr, DataSize);
	if(Error != CRYS_OK) {
		goto end;
	}
	Error = CRYS_HMAC_Finish(&UserContext, HmacResultBuff);

end:
	return Error;
}

#ifdef HI_CIPHER_TEST
//Only for test
void hamc_test1(void)
{
    CRYSError_t  err;
    DxUint8_t             key_ptr[4] = {"Jefe"};
	DxUint8_t             DataIn_ptr[28] = {"what do ya want for nothing?"};
    HI_U8                 HmacDest[32] = {"\x5b\xdc\xc1\x46\xbf\x60\x75\x4e\x6a\x04\x24\x26\x08\x95\x75\xc7\x5a\x00\x3f\x08\x9d\x27\x39\x83\x9d\xec\x58\xb9\x64\xec\x38\x43"};
	CRYS_HASH_Result_t    HmacResultBuff;

    err = CRYS_HMAC(CRYS_HASH_SHA256_mode, key_ptr, sizeof(key_ptr), DataIn_ptr, sizeof(DataIn_ptr), HmacResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HMAC-256", HmacResultBuff, 32);
    if (memcmp(HmacResultBuff,HmacDest, 32)!=0)
    {
        HI_ERR_CIPHER ("HMAC-256 failed\n");	
        return;
    }
}

void hamc_test2(void)
{
    CRYSError_t  err;
    DxUint8_t             key_ptr[20];
	DxUint8_t             DataIn_ptr[50];
    HI_U8                 HmacDest[32] = {"\x77\x3e\xa9\x1e\x36\x80\x0e\x46\x85\x4d\xb8\xeb\xd0\x91\x81\xa7\x29\x59\x09\x8b\x3e\xf8\xc1\x22\xd9\x63\x55\x14\xce\xd5\x65\xfe"};
	CRYS_HASH_Result_t    HmacResultBuff;

    memset(key_ptr, 0xaa, 20);
    memset(DataIn_ptr, 0xdd, 50);
    
    err = CRYS_HMAC(CRYS_HASH_SHA256_mode, key_ptr, sizeof(key_ptr), DataIn_ptr, sizeof(DataIn_ptr), HmacResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HMAC-256", HmacResultBuff, 32);
    if (memcmp(HmacResultBuff,HmacDest, 32)!=0)
    {
        HI_ERR_CIPHER ("HMAC-256 failed\n");	
        return;
    }
}

void hamc_test3(void)
{
    CRYSError_t  err;
    DxUint8_t             key_ptr[131];
	DxUint8_t             DataIn_ptr[54] = {"Test Using Larger Than Block-Size Key - Hash Key First"};
    HI_U8                 HmacDest[32] = {"\x60\xe4\x31\x59\x1e\xe0\xb6\x7f\x0d\x8a\x26\xaa\xcb\xf5\xb7\x7f\x8e\x0b\xc6\x21\x37\x28\xc5\x14\x05\x46\x04\x0f\x0e\xe3\x7f\x54"};
	CRYS_HASH_Result_t    HmacResultBuff;

    memset(key_ptr, 0xaa, 131);
    
    err = CRYS_HMAC(CRYS_HASH_SHA256_mode, key_ptr, sizeof(key_ptr), DataIn_ptr, sizeof(DataIn_ptr), HmacResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HMAC-256", HmacResultBuff, 32);
    if (memcmp(HmacResultBuff,HmacDest, 32)!=0)
    {
        HI_ERR_CIPHER ("HMAC-256 failed\n");	
        return;
    }
}

void hamc_test(void)
{
    hamc_test1();
    hamc_test2();
    hamc_test3();
}
#endif

