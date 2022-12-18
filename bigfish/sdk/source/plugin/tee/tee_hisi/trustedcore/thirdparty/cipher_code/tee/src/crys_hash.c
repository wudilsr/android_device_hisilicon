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
#include "crys_hash_error.h"
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

typedef struct hiCIPHER_HASH_INFO_S
{
    HI_HANDLE hHash;
    HI_UNF_CIPHER_HASH_TYPE_E enHashType;
}CIPHER_HASH_INFO_S;

/************************ Type definitions **********************/
typedef struct hiHASHUserContext_t
{
    CRYS_HASH_OperationMode_t  OperationMode;
    union
    {
        HI_HANDLE      hHash;
    }unCtx;
}HASHUserContext_t;

/************************ Private Functions **********************/


/*!
 * Converts Symmetric Adaptor return code to CRYS error code.
 * 
 * \param symRetCode Symmetric Adaptor return error.
 * \param errorInfo Ignored.
 *  
 * \return CRYSError_t one of CRYS_* error codes defined in crys_error.h
 */
static CRYSError_t SymAdaptor2CrysHashErr(int symRetCode, DxUint32_t errorInfo)
{
    CRYSError_t err;
    
	switch (symRetCode) {
	case HI_ERR_CIPHER_NOT_INIT:
		err = CRYS_HASH_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_FAILED_INIT:
        err = CRYS_HASH_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_INVALID_POINT:
		err =  CRYS_HASH_DATA_IN_POINTER_INVALID_ERROR;
        break;
	case HI_ERR_CIPHER_INVALID_PARA:
        err = CRYS_HASH_DATA_SIZE_ILLEGAL;
        break;
	case HI_ERR_CIPHER_BUSY:
	case HI_ERR_CIPHER_NO_AVAILABLE_RNG:
        err = CRYS_HASH_IS_NOT_SUPPORTED;
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

/**
 * This function initializes the HASH machine on the CRYS level.
 *
 * This function allocates and initializes the HASH Context .
 * The function receives as input a pointer to store the context handle to HASH Context , 
 * it initializes the 
 * HASH Context with the cryptographic attributes that are needed for 
 * the HASH block operation ( initialize H's value for the HASH algorithm ).
 *
 * The function flow:
 *
 * 1) checking the validity of the arguments - returnes an error on an illegal argument case.
 * 2) Aquiring the working context from the CCM manager.
 * 3) Initializing the context with the parameters passed by the user and with the init values
 *    of the HASH.
 * 4) loading the user tag to the context.
 * 5) release the CCM context.
 * 
 * @param[in] ContextID_ptr - a pointer to the HASH context buffer allocated by the user that
 *                       is used for the HASH machine operation.
 *
 * @param[in] OperationMode - The operation mode : MD5 or SHA1.
 *
 * @return CRYSError_t on success the function returns CRYS_OK else non ZERO error.
 *      
 */
CEXPORT_C CRYSError_t CRYS_HASH_Init(CRYS_HASHUserContext_t*    ContextID_ptr,
                                     CRYS_HASH_OperationMode_t  OperationMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HASHUserContext_t *pstHashUserContext;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    
	if ( ContextID_ptr == DX_NULL ) {
		return CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

	if( OperationMode >= CRYS_HASH_NumOfModes ) {
		return CRYS_HASH_ILLEGAL_OPERATION_MODE_ERROR;
	}

    pstHashUserContext = (HASHUserContext_t *)ContextID_ptr;
    memset(pstHashUserContext, 0, sizeof(HASHUserContext_t));

    switch (OperationMode) 
    {
 
		case CRYS_HASH_SHA1_mode:
            stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA1;
            s32Ret = Cipher_HashInit(&stHashAttr, &pstHashUserContext->unCtx.hHash);
            break;
        case CRYS_HASH_SHA256_mode:
            stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
            s32Ret = Cipher_HashInit(&stHashAttr, &pstHashUserContext->unCtx.hHash);
			break;

		default:
			return CRYS_HASH_ILLEGAL_OPERATION_MODE_ERROR;
	}
    pstHashUserContext->OperationMode = OperationMode;

	return DX_CRYS_RETURN_ERROR(s32Ret, 0, SymAdaptor2CrysHashErr);
}

/**
 * This function process a block of data via the HASH Hardware.
 * The function receives as input an handle to the  HASH Context , that was initialized before
 * by an CRYS_HASH_Init function or by other CRYS_HASH_Update 
 * function. The function Sets the hardware with the last H's 
 * value that where stored in the CRYS HASH context and then 
 * process the data block using the hardware and in the end of 
 * the process stores in the HASH context the H's value HASH 
 * Context with the cryptographic attributes that are needed for 
 * the HASH block operation ( initialize H's value for the HASH 
 * algorithm ). This function is used in cases not all the data 
 * is arrange in one continues buffer.
 *
 * The function flow:
 *
 * 1) checking the parameters validty if there is an error the function shall exit with an error code. 
 * 2) Aquiring the working context from the CCM manager.
 * 3) If there isnt enouth data in the previous update data buff in the context plus the received data
 *    load it to the context buffer and exit the function.
 * 4) fill the previous update data buffer to contain an entire block. 
 * 5) Calling the hardware low level function to execute the update.
 * 6) fill the previous update data buffer with the data not processed at the end of the received data.
 * 7) release the CCM context.
 * 
 * @param[in] ContextID_ptr - a pointer to the HASH context buffer allocated by the user that
 *                       is used for the HASH machine operation.
 *
 * @param DataIn_ptr a pointer to the buffer that stores the data to be 
 *                       hashed .
 * 
 * @param DataInSize  The size of the data to be hashed in bytes. 
 *
 * @return CRYSError_t on success the function returns CRYS_OK else non ZERO error.
 *
 */
CEXPORT_C CRYSError_t CRYS_HASH_Update(CRYS_HASHUserContext_t*    ContextID_ptr,
                                       DxUint8_t*                 DataIn_ptr,
                                       DxUint32_t                 DataInSize )
{                             
    HI_S32 s32Ret = HI_SUCCESS;
    HASHUserContext_t *pstHashUserContext;
	
	/* if the users context ID pointer is DX_NULL return an error */
	if( ContextID_ptr == DX_NULL ) {
		return CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

	/* if the users Data In pointer is illegal and the size is not 0 return an error */
	if( (DataIn_ptr == DX_NULL) && DataInSize ) {
		return CRYS_HASH_DATA_IN_POINTER_INVALID_ERROR;
	}
	   
	/* if the data size is zero no need to execute an update , return CRYS_OK */
	if( DataInSize == 0 ) {
		return CRYS_OK;
	}

    pstHashUserContext = (HASHUserContext_t *)ContextID_ptr;
    switch (pstHashUserContext->OperationMode) 
    {

		case CRYS_HASH_SHA1_mode:
            s32Ret = Cipher_HashUpdate(pstHashUserContext->unCtx.hHash, DataIn_ptr, DataInSize);
            break;

        case CRYS_HASH_SHA256_mode:
            s32Ret = Cipher_HashUpdate(pstHashUserContext->unCtx.hHash, DataIn_ptr, DataInSize);
			break;

		default:
			return CRYS_HASH_ILLEGAL_OPERATION_MODE_ERROR;
	}

	return DX_CRYS_RETURN_ERROR(s32Ret, 0, SymAdaptor2CrysHashErr);

}

/**
 * This function finalize the hashing process of data block.
 * The function receives as input an handle to the HASH Context , that was initialized before
 * by an CRYS_HASH_Init function or by CRYS_HASH_Update function.
 * The function "adds" an header to the data block as the specific hash standard 
 * specifics , then it loads the hardware and reads the final message digest.
 *
 *  the function flow:
 *
 * 1) checking the parameters validty if there is an error the function shall exit with an error code. 
 * 2) Calling the hardware low level function to execute the 
 *    finish. 
 *
 *  @param[in] ContextID_ptr - a pointer to the HASH context buffer allocated by the user that
 *                       is used for the HASH machine operation.
 *
 *  @retval HashResultBuff a pointer to the target buffer where the 
 *                       HASE result stored in the context is loaded to.
 *
 *  @return CRYSError_t on success the function returns CRYS_OK else non ZERO error.
 */

CEXPORT_C CRYSError_t CRYS_HASH_Finish( CRYS_HASHUserContext_t*   ContextID_ptr,
                                        CRYS_HASH_Result_t        HashResultBuff )
{  
    HI_S32 s32Ret = HI_SUCCESS;
    HASHUserContext_t *pstHashUserContext;

	/* if the users context ID pointer is DX_NULL return an error */
	if( ContextID_ptr == DX_NULL ) {
		return CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR;
	}
	
    pstHashUserContext = (HASHUserContext_t *)ContextID_ptr;
    switch (pstHashUserContext->OperationMode) 
    {

		case CRYS_HASH_SHA1_mode:
            s32Ret = Cipher_HashFinal(pstHashUserContext->unCtx.hHash, (HI_U8*)HashResultBuff);
            break;

        case CRYS_HASH_SHA256_mode:
            s32Ret = Cipher_HashFinal(pstHashUserContext->unCtx.hHash, (HI_U8*)HashResultBuff);
			break;

		default:
			return CRYS_HASH_ILLEGAL_OPERATION_MODE_ERROR;
	}

	return DX_CRYS_RETURN_ERROR(s32Ret, 0, SymAdaptor2CrysHashErr);
}

/**
 * @brief This function clears the hash context
 *
 * @param[in] ContextID_ptr - a pointer to the HASH context
 *  					 buffer allocated by the user that is
 *  					 used for the HASH machine operation.
 *  					 This should be the same context that
 *  					 was used on the previous call of this
 *  					 session.
 *
 * @return CRYSError_t - On success CRYS_OK is returned, on failure a
 *                        value MODULE_* crys_hash_error.h
 */
CEXPORT_C CRYSError_t  CRYS_HASH_Free( CRYS_HASHUserContext_t *ContextID_ptr )
{
	if ( ContextID_ptr == DX_NULL ) {
		return CRYS_HASH_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

	memset(ContextID_ptr, 0, sizeof(CRYS_HASHUserContext_t));
    
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
 * @param[in] OperationMode - The operation mode : MD5 or SHA1.
 * 
 * @param DataIn_ptr a pointer to the buffer that stores the data to be 
 *                       hashed .
 * 
 * @param DataInSize  The size of the data to be hashed in bytes. 
 *
 * @retval HashResultBuff a pointer to the target buffer where the 
 *                      HASE result stored in the context is loaded to.
 *
 * @return CRYSError_t on success the function returns CRYS_OK else non ZERO error.
 *
 */
CEXPORT_C CRYSError_t CRYS_HASH  ( CRYS_HASH_OperationMode_t    OperationMode,
                                   DxUint8_t*                   DataIn_ptr,
                                   DxUint32_t                   DataSize,
                                   CRYS_HASH_Result_t           HashResultBuff )
{    
	CRYSError_t Error = CRYS_OK;
	CRYS_HASHUserContext_t UserContext;
	
	Error = CRYS_HASH_Init( &UserContext, OperationMode);
	if (Error != CRYS_OK) {
		goto end;
	}

	Error = CRYS_HASH_Update( &UserContext, DataIn_ptr, DataSize );
	if (Error != CRYS_OK) {
		goto end;
	}

	Error = CRYS_HASH_Finish( &UserContext, HashResultBuff );
	
end:
	CRYS_HASH_Free( &UserContext );

	return Error;
}
    
#ifdef HI_CIPHER_TEST
//Only for test
void hash_test1(void)
{
    CRYSError_t  err;
	DxUint8_t             DataIn_ptr[3] = {"abc"};
    HI_U8                 HashDest[20] = {"\xA9\x99\x3E\x36\x47\x06\x81\x6A\xBA\x3E\x25\x71\x78\x50\xC2\x6C\x9C\xD0\xD8\x9D"};
	CRYS_HASH_Result_t    HashResultBuff;

    err = CRYS_HASH(CRYS_HASH_SHA1_mode, DataIn_ptr, sizeof(DataIn_ptr), HashResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HASH-1", HashResultBuff, 20);
    if (memcmp(HashResultBuff,HashDest, 20)!=0)
    {
        HI_ERR_CIPHER ("HASH-1 failed\n");	
        return;
    }
}

void hash_test2(void)
{
    CRYSError_t  err;
	DxUint8_t             DataIn_ptr[56] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
    HI_U8                 HashDest[20] = {"\x84\x98\x3E\x44\x1C\x3B\xD2\x6E\xBA\xAE\x4A\xA1\xF9\x51\x29\xE5\xE5\x46\x70\xF1"};
	CRYS_HASH_Result_t    HashResultBuff;

    err = CRYS_HASH(CRYS_HASH_SHA1_mode, DataIn_ptr, sizeof(DataIn_ptr), HashResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HASH-1", HashResultBuff, 20);
    if (memcmp(HashResultBuff,HashDest, 20)!=0)
    {
        HI_ERR_CIPHER ("HASH-1 failed\n");	
        return;
    }
}

void hash_test3(void)
{
    CRYSError_t  err;
	DxUint8_t             DataIn_ptr[56] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
    HI_U8                 HashDest[32] = {"\x24\x8D\x6A\x61\xD2\x06\x38\xB8\xE5\xC0\x26\x93\x0C\x3E\x60\x39\xA3\x3C\xE4\x59\x64\xFF\x21\x67\xF6\xEC\xED\xD4\x19\xDB\x06\xC1"};
	CRYS_HASH_Result_t    HashResultBuff;

    err = CRYS_HASH(CRYS_HASH_SHA256_mode, DataIn_ptr, sizeof(DataIn_ptr), HashResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HASH-256", HashResultBuff, 32);
    if (memcmp(HashResultBuff,HashDest, 32)!=0)
    {
        HI_ERR_CIPHER ("HASH-256 failed\n");	
        return;
    }
}

void hash_test4(void)
{
    CRYSError_t  err;
	DxUint8_t             DataIn_ptr[56] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
    HI_U8                 HashDest[28] = {"\x75\x38\x8b\x16\x51\x27\x76\xcc\x5d\xba\x5d\xa1\xfd\x89\x01\x50\xb0\xc6\x45\x5c\xb4\xf5\x8b\x19\x52\x52\x25\x25"};
    CRYS_HASH_Result_t    HashResultBuff;

    err = CRYS_HASH(CRYS_HASH_SHA224_mode, DataIn_ptr, sizeof(DataIn_ptr), HashResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HASH-224", HashResultBuff, 28);
    if (memcmp(HashResultBuff,HashDest, 28)!=0)
    {
        HI_ERR_CIPHER ("HASH-224 failed\n");	
        return;
    }
}

void hash_test5(void)
{
    CRYSError_t  err;
	DxUint8_t             DataIn_ptr[112] = {"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"};
    HI_U8                 HashDest[48] = {"\x09\x33\x0c\x33\xf7\x11\x47\xe8\x3d\x19\x2f\xc7\x82\xcd\x1b\x47\x53\x11\x1b\x17\x3b\x3b\x05\xd2\x2f\xa0\x80\x86\xe3\xb0\xf7\x12\xfc\xc7\xc7\x1a\x55\x7e\x2d\xb9\x66\xc3\xe9\xfa\x91\x74\x60\x39"};
    CRYS_HASH_Result_t    HashResultBuff;

    err = CRYS_HASH(CRYS_HASH_SHA384_mode, DataIn_ptr, sizeof(DataIn_ptr), HashResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HASH-384", HashResultBuff, 48);
    if (memcmp(HashResultBuff,HashDest, 48)!=0)
    {
        HI_ERR_CIPHER ("HASH-384 failed\n");	
        return;
    }
}

void hash_test6(void)
{
    CRYSError_t  err;
	DxUint8_t             DataIn_ptr[112] = {"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"};
    HI_U8                 HashDest[64] = {"\x8e\x95\x9b\x75\xda\xe3\x13\xda\x8c\xf4\xf7\x28\x14\xfc\x14\x3f\x8f\x77\x79\xc6\xeb\x9f\x7f\xa1\x72\x99\xae\xad\xb6\x88\x90\x18\x50\x1d\x28\x9e\x49\x00\xf7\xe4\x33\x1b\x99\xde\xc4\xb5\x43\x3a\xc7\xd3\x29\xee\xb6\xdd\x26\x54\x5e\xe5\x5b\x87\x4b\xe9\x09"};
    CRYS_HASH_Result_t    HashResultBuff;

    err = CRYS_HASH(CRYS_HASH_SHA512_mode, DataIn_ptr, sizeof(DataIn_ptr), HashResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HASH-512", HashResultBuff, 48);
    if (memcmp(HashResultBuff,HashDest, 48)!=0)
    {
        HI_ERR_CIPHER ("HASH-512 failed\n");	
        return;
    }
}

void hash_test7(void)
{
    CRYSError_t  err;
	DxUint8_t             DataIn_ptr[3] = {"abc"};
    HI_U8                 HashDest[16] = {0x90, 0x01, 0x50, 0x98, 0x3C, 0xD2, 0x4F, 0xB0, 0xD6, 0x96, 0x3F, 0x7D, 0x28, 0xE1, 0x7F, 0x72};
    CRYS_HASH_Result_t    HashResultBuff;

    err = CRYS_HASH(CRYS_HASH_MD5_mode, DataIn_ptr, sizeof(DataIn_ptr), HashResultBuff);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX ("HASH-MD5", HashResultBuff, 16);
    if (memcmp(HashResultBuff,HashDest, 16)!=0)
    {
        HI_ERR_CIPHER ("HASH-MD5 failed\n");	
        return;
    }
}

void hash_test(void)
{
    hash_test1();
    hash_test2();
    hash_test3();
    /*hash_test4();
    hash_test5();
    hash_test6();
    hash_test7();*/
}
#endif
