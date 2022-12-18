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


/************* Include Files ****************/

/************* Include Files ****************/
#include "hi_type.h"
#include "drv_cipher.h"
#include "drv_cipher_intf.h"
#include "drv_cipher_define.h"
#include "sre_debug.h"
#include "hi_mmz.h"
#include "crys_aes.h"
#include <sre_mem.h>
#include <boot.h>
#include "dx_pal_types.h"
#include "crys_rsa_error.h"
#include "crys_rsa_types.h"
#include "dx_error.h"
#include "crys_rsa_local.h"
#include "crys_rsa_schemes.h"
#include "crys_cipher_common.h"

/************************ Defines ******************************/
#define RSA_MAX_RSA_KEY_LEN  512

/* canceling the lint warning:
   Use of goto is deprecated */
/*lint --e{801} */
/************************ Enums ******************************/

/************************ Typedefs ******************************/

/************************ Global Data ******************************/

/*!
 * Converts Symmetric Adaptor return code to CRYS error code.
 * 
 * \param symRetCode Symmetric Adaptor return error.
 * \param errorInfo Ignored.
 *  
 * \return CRYSError_t one of CRYS_* error codes defined in crys_error.h
 */
    



/************************ Public Functions ******************************/

#if !defined(_INTERNAL_CRYS_NO_RSA_ENCRYPT_SUPPORT) && !defined(_INTERNALCRYS_NO_RSA_VERIFY_SUPPORT)

/**********************************************************************************/ 
/**
@brief
CRYS_RSA_PRIM_Encrypt implements the RSAEP algorithm as defined in PKCS#1 v2.1 6.1.1

  @param[in] UserPubKey_ptr - Pointer to the public key data structure.
  @param[in] PrimeData_ptr - A pointer to a structure containing temp buffers.
  @param[in] Data_ptr - Pointer to the input data to be encrypted.
  @param[in] DataSize - The size, in bytes, of the input data. 
			\Note: DataSize <= modulus size is supported, but recommended
			that size is equal to modulus size. If smaller, the data will be 
			zero-padded on left side up to the modulus size and therefore, 
			after further decrypt operation its result will contain 
			padding zeros also.
  @param[out] Output_ptr - Pointer to the encrypted data. The size of output data 
			is always equal to size modulus size. The output buffer
                        must be at least of modulus size in bytes.

  @return CRYSError_t - CRYS_OK,
                        CRYS_RSA_INVALID_PUB_KEY_STRUCT_POINTER_ERROR,
                        CRYS_RSA_PUB_KEY_VALIDATION_TAG_ERROR,
                        CRYS_RSA_PRIM_DATA_STRUCT_POINTER_INVALID,
                        CRYS_RSA_DATA_POINTER_INVALID_ERROR,
                        CRYS_RSA_INVALID_OUTPUT_POINTER_ERROR,
                        CRYS_RSA_INVALID_MESSAGE_BUFFER_SIZE,
                        CRYS_RSA_INVALID_MESSAGE_DATA_SIZE,
                        CRYS_RSA_INVALID_MESSAGE_VAL
 */
CEXPORT_C CRYSError_t CRYS_RSA_PRIM_Encrypt(CRYS_RSAUserPubKey_t *UserPubKey_ptr,
                                  CRYS_RSAPrimeData_t    *PrimeData_ptr,
                                  DxUint8_t              *Data_ptr,
                                  DxUint16_t              DataSize,
                                  DxUint8_t              *Output_ptr)
{
   /* FUNCTION LOCAL DECLERATIONS */
   CIPHER_RSA_DATA_S stRsaData;
   HI_S32 s32Ret;

    /* the effective size in bits of the data message buffer */
   DxUint32_t ModulusSizeBytes;

   /* the public key database pointer */
   CRYSRSAPubKey_t *PubKey_ptr;
   
   /* the modulus size in bytes */
   DxUint32_t nSizeInBytes;
   HI_U8 *pu8UserContext;
   CRYSError_t err;
  
   /* FUNCTION LOGIC */

   /* ............... if not supported exit .............................. */
   /* -------------------------------------------------------------------- */   

                              
   #ifndef CRYS_NO_HASH_SUPPORT                                      
   #ifndef CRYS_NO_PKI_SUPPORT                                      
 
   /* ............... initialize local variables ......................... */
   /* -------------------------------------------------------------------- */
   
   /* initialize the error identifier to O.K - success */
   
   /* ............... checking the parameters pointers validity .......... */
   /* -------------------------------------------------------------------- */
   
   /* checking the key database handle pointer */
   if(UserPubKey_ptr == DX_NULL)
      return CRYS_RSA_INVALID_PUB_KEY_STRUCT_POINTER_ERROR;
      
   /* if the users TAG is illegal return an error - the context is invalid */
   if(UserPubKey_ptr->valid_tag != CRYS_RSA_PUB_KEY_VALIDATION_TAG)
      return CRYS_RSA_PUB_KEY_VALIDATION_TAG_ERROR;      

   /* checking the Prime Data pointer */
   if(PrimeData_ptr == DX_NULL)
      return CRYS_RSA_PRIM_DATA_STRUCT_POINTER_INVALID;

   /* if the users Data pointer is illegal return an error */
   if(Data_ptr == DX_NULL)
      return CRYS_RSA_DATA_POINTER_INVALID_ERROR;

   /* if the users output pointer is illegal return an error */
   if(Output_ptr == DX_NULL)
      return CRYS_RSA_INVALID_OUTPUT_POINTER_ERROR;

   /* if the data size is larger then the internal buffer return error */
   if(DataSize > sizeof(PrimeData_ptr->DataIn))
      return CRYS_RSA_INVALID_MESSAGE_BUFFER_SIZE;

   /* setting the pointer to the key database */
   PubKey_ptr = (CRYSRSAPubKey_t*)UserPubKey_ptr->PublicKeyDbBuff;   
   
   /* setting the modulus size in bytes */
   nSizeInBytes = (PubKey_ptr->nSizeInBits+7)/8;
   
   /* if the data size is larger then the modulus, return error */
   if(DataSize > nSizeInBytes)
	   return CRYS_RSA_INVALID_MESSAGE_DATA_SIZE;

    pu8UserContext = (HI_U8*)PrimeData_ptr;
    
   /* ................ copying the input data to the buffer .............. */
   /* -------------------------------------------------------------------- */   
  	/*Initialize K with the modulus size in Bytes*/   
	ModulusSizeBytes = (DxUint16_t)(PubKey_ptr->nSizeInBits / 8);
	if(PubKey_ptr->nSizeInBits % 8)
		ModulusSizeBytes++;

    err = CRYS_RSA_Public(pu8UserContext, PubKey_ptr, Data_ptr, Output_ptr, ModulusSizeBytes);
    if (err != CRYS_OK)
    
    {
        HI_ERR_CIPHER("RSA public error, ret = 0x%x\n", err);
        return err;
//    HI_PRINT_HEX ("M", stRsaData.pu8Input, stRsaData.u32DataLen);
    }

    return err;

   #endif /* !CRYS_NO_HASH_SUPPORT */
   #endif /* !CRYS_NO_PKI_SUPPORT */                                     

}/* END OF CRYS_RSA_PRIM_Encrypt */

#endif /*!defined(_INTERNAL_CRYS_NO_RSA_ENCRYPT_SUPPORT) && !defined(_INTERNAL_CRYS_NO_RSA_VERIFY_SUPPORT)*/





#if !defined(_INTERNALCRYS_NO_RSA_DECRYPT_SUPPORT) && !defined(_INTERNAL_CRYS_NO_RSA_SIGN_SUPPORT)

/**********************************************************************************/ 
/**
@brief
CRYS_RSA_PRIM_Decrypt implements the RSADP algorithm as defined in PKCS#1 v2.1 6.1.2

  @param[in] PrivKey_ptr - Pointer to the private key data
                           structure. \note The RSA key parameters and hence the algorithm (CRT
                           or not) are determined by this structure. Using CRYS_Build_PrivKey or
                           CRYS_Build_PrivKeyCRT determines which algorithm will be used.
                           
  @param[in] PrimeData_ptr - A pointer to a structure containing internal
        		     buffers required for the RSA operation.
  @param[in] Data_ptr - Pointer to the data to be decrypted. 
  @param[in] DataSize - The size, in bytes, of the input data. To decrypt
			previously encrypted data its size must be equal to
			modulus size.
        		\Note: DataSize <= modulus size is supported, but
        		it is recommended that the size is equal to modulus size. 
			If smaller, the data will be zero-padded on left side 
			up to the modulus size and therefore, after further decrypt 
			operation its result will contain padding zeros also.
  @param[out] Output_ptr - Pointer to the decrypted data. The size of output data 
			is always equal to size modulus size. The output buffer
                        must be at least of modulus size in bytes.

  @return CRYSError_t - CRYS_OK,
                        CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR,
                        CRYS_RSA_PRIM_DATA_STRUCT_POINTER_INVALID,
                        CRYS_RSA_PRIV_KEY_VALIDATION_TAG_ERROR,
                        CRYS_RSA_DATA_POINTER_INVALID_ERROR,
                        CRYS_RSA_INVALID_OUTPUT_POINTER_ERROR,
                        CRYS_RSA_INVALID_MESSAGE_DATA_SIZE,
                        CRYS_RSA_INVALID_MESSAGE_VAL
 */

CEXPORT_C CRYSError_t CRYS_RSA_PRIM_Decrypt(
                                  CRYS_RSAUserPrivKey_t *UserPrivKey_ptr,
                                  CRYS_RSAPrimeData_t   *PrimeData_ptr,
                                  DxUint8_t             *Data_ptr,
                                  DxUint16_t             DataSize,
                                  DxUint8_t             *Output_ptr)
{				  
   /* FUNCTION LOCAL DECLERATIONS */
 
   CIPHER_RSA_DATA_S stRsaData;
   HI_S32 s32Ret;
   HI_U8 *pu8UserContext;
   CRYSError_t err;

    /* the effective size in bits of the data message buffer */
   DxUint32_t ModulusSizeBytes;

   /* the private key database pointer */
   CRYSRSAPrivKey_t *PrivKey_ptr;
   
   /* the modulus size in bytes */
   DxUint32_t nSizeInBytes; 

   /* FUNCTION LOGIC */
 
   /* ............... if not supported exit .............................. */
   /* -------------------------------------------------------------------- */   

                              
   #ifndef CRYS_NO_HASH_SUPPORT                                      
   #ifndef CRYS_NO_PKI_SUPPORT                                      
  
   /* ............... initialize local variables ......................... */
   /* -------------------------------------------------------------------- */
   
   
   /* ............... checking the parameters pointers validity .......... */
   /* -------------------------------------------------------------------- */
   
   /* ...... checking the key database handle pointer .................... */
   if(UserPrivKey_ptr == DX_NULL)
      return CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR;

   /* ...... checking the Prime Data pointer .................... */
   if(PrimeData_ptr == DX_NULL)
      return CRYS_RSA_PRIM_DATA_STRUCT_POINTER_INVALID;

   /* if the users TAG is illegal return an error - the context is invalid */
   if(UserPrivKey_ptr->valid_tag != CRYS_RSA_PRIV_KEY_VALIDATION_TAG)
      return CRYS_RSA_PRIV_KEY_VALIDATION_TAG_ERROR;      

   /* if the users Data pointer is DX_NULL return an error */
   if(Data_ptr == DX_NULL)
      return CRYS_RSA_DATA_POINTER_INVALID_ERROR;
      
   /* if the users Output pointer is DX_NULL return an error */
   if(Output_ptr == DX_NULL)
      return CRYS_RSA_INVALID_OUTPUT_POINTER_ERROR;

   /* setting the pointer to the key database */
   PrivKey_ptr = (CRYSRSAPrivKey_t*)UserPrivKey_ptr->PrivateKeyDbBuff;

   /* setting the modulus size in bytes */
   nSizeInBytes = (PrivKey_ptr->nSizeInBits+7)/8;

   /* if the data size is larger then the modulus, return error */
   if(DataSize > nSizeInBytes)
	   return CRYS_RSA_INVALID_MESSAGE_DATA_SIZE;


  	/*Initialize K with the modulus size in Bytes*/   
	ModulusSizeBytes = (DxUint16_t)(PrivKey_ptr->nSizeInBits / 8);
	if(PrivKey_ptr->nSizeInBits % 8)
		ModulusSizeBytes++;

    pu8UserContext = (HI_U8*)PrimeData_ptr;

   /* ................ copying the input data to the buffer .............. */
   /* -------------------------------------------------------------------- */
   
    err = CRYS_RSA_Private(pu8UserContext, PrivKey_ptr, Data_ptr, Output_ptr, ModulusSizeBytes);
    if (err != CRYS_OK)
    {
        HI_ERR_CIPHER("RSA private error, ret = 0x%x\n", err);
        return err;
//    HI_PRINT_HEX ("M", stRsaData.pu8Input, stRsaData.u32DataLen);
    }

   return err;
  
   #endif /* !CRYS_NO_HASH_SUPPORT */
   #endif /* !CRYS_NO_PKI_SUPPORT */                                     
  							       
}/* END OF CRYS_RSA_PRIM_Decrypt */

#ifdef HI_CIPHER_TEST
//Only for test
#define TEST_KEY_SIZE   256
static HI_U8 tN[]  = 
{
    0x82, 0x78, 0xA0, 0xC5, 0x39, 0xE6, 0xF6, 0xA1, 0x5E, 0xD1, 0xC6, 0x8B, 0x9C, 0xF9, 0xC4, 0x3F, 
    0xEA, 0x19, 0x16, 0xB0, 0x96, 0x3A, 0xB0, 0x5A, 0x94, 0xED, 0x6A, 0xD3, 0x83, 0xE8, 0xA0, 0xFD, 
    0x01, 0x5E, 0x92, 0x2A, 0x7D, 0x0D, 0xF9, 0x72, 0x1E, 0x03, 0x8A, 0x68, 0x8B, 0x4D, 0x57, 0x55, 
    0xF5, 0x2F, 0x9A, 0xC9, 0x45, 0xCF, 0x9B, 0xB7, 0xF5, 0x11, 0x94, 0x7A, 0x16, 0x0B, 0xED, 0xD9, 
    0xA3, 0xF0, 0x63, 0x8A, 0xEC, 0xD3, 0x21, 0xAB, 0xCF, 0x74, 0xFC, 0x6B, 0xCE, 0x06, 0x4A, 0x51, 
    0xC9, 0x7C, 0x7C, 0xA3, 0xC4, 0x10, 0x63, 0x7B, 0x00, 0xEC, 0x2D, 0x02, 0x18, 0xD5, 0xF1, 0x8E, 
    0x19, 0x7F, 0xBE, 0xE2, 0x45, 0x5E, 0xD7, 0xA8, 0x95, 0x90, 0x88, 0xB0, 0x73, 0x35, 0x89, 0x66, 
    0x1C, 0x23, 0xB9, 0x6E, 0x88, 0xE0, 0x7A, 0x57, 0xB0, 0x55, 0x8B, 0x81, 0x9B, 0x9C, 0x34, 0x9F, 
    0x86, 0x0E, 0x15, 0x94, 0x2C, 0x6B, 0x12, 0xC3, 0xB9, 0x56, 0x60, 0x25, 0x59, 0x3E, 0x50, 0x7B, 
    0x62, 0x4A, 0xD0, 0xF0, 0xB6, 0xB1, 0x94, 0x83, 0x51, 0x66, 0x6F, 0x60, 0x4D, 0xEF, 0x8F, 0x94, 
    0xA6, 0xD1, 0xA2, 0x80, 0x06, 0x24, 0xF2, 0x6E, 0xD2, 0xC7, 0x01, 0x34, 0x8D, 0x2B, 0x6B, 0x03, 
    0xF7, 0x05, 0xA3, 0x99, 0xCC, 0xC5, 0x16, 0x75, 0x1A, 0x81, 0xC1, 0x67, 0xA0, 0x88, 0xE6, 0xE9, 
    0x00, 0xFA, 0x62, 0xAF, 0x2D, 0xA9, 0xFA, 0xC3, 0x30, 0x34, 0x98, 0x05, 0x4C, 0x1A, 0x81, 0x0C, 
    0x52, 0xCE, 0xBA, 0xD6, 0xEB, 0x9C, 0x1E, 0x76, 0x01, 0x41, 0x6C, 0x34, 0xFB, 0xC0, 0x83, 0xC5, 
    0x4E, 0xB3, 0xF2, 0x5B, 0x4F, 0x94, 0x08, 0x33, 0x87, 0x5E, 0xF8, 0x39, 0xEF, 0x7F, 0x72, 0x94, 
    0xFF, 0xD7, 0x51, 0xE8, 0xA2, 0x5E, 0x26, 0x25, 0x5F, 0xE9, 0xCC, 0x2A, 0x7D, 0xAC, 0x5B, 0x35
};
static HI_U8 tE[]  = 
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01
};
static HI_U8 tD[]  = 
{
    0x49, 0x7E, 0x93, 0xE9, 0xA5, 0x7D, 0x42, 0x0E, 0x92, 0xB0, 0x0E, 0x6C, 0x94, 0xC7, 0x69, 0x52, 
    0x2B, 0x97, 0x68, 0x5D, 0x9E, 0xB2, 0x7E, 0xA6, 0xF7, 0xDF, 0x69, 0x5E, 0xAE, 0x9E, 0x7B, 0x19, 
    0x2A, 0x0D, 0x50, 0xBE, 0xD8, 0x64, 0xE7, 0xCF, 0xED, 0xB2, 0x46, 0xE4, 0x2F, 0x1C, 0x29, 0x07, 
    0x45, 0xAF, 0x44, 0x3C, 0xFE, 0xB3, 0x3C, 0xDF, 0x7A, 0x10, 0x26, 0x18, 0x43, 0x95, 0x02, 0xAD, 
    0xA7, 0x98, 0x81, 0x2A, 0x3F, 0xCF, 0x8A, 0xD7, 0x12, 0x6C, 0xAE, 0xC8, 0x37, 0x6C, 0xF9, 0xAE, 
    0x6A, 0x96, 0x52, 0x4B, 0x99, 0xE5, 0x35, 0x74, 0x93, 0x87, 0x76, 0xAF, 0x08, 0xB8, 0x73, 0x72, 
    0x7D, 0x50, 0xA5, 0x81, 0x26, 0x5C, 0x8F, 0x94, 0xEA, 0x73, 0x59, 0x5C, 0x33, 0xF9, 0xC3, 0x65, 
    0x1E, 0x92, 0xCD, 0x20, 0xC3, 0xBF, 0xD7, 0x8A, 0xCF, 0xCC, 0xD0, 0x61, 0xF8, 0xFB, 0x1B, 0xF4, 
    0xB6, 0x0F, 0xD4, 0xCF, 0x3E, 0x55, 0x48, 0x4C, 0x99, 0x2D, 0x40, 0x44, 0x7C, 0xBA, 0x7B, 0x6F, 
    0xDB, 0x5D, 0x71, 0x91, 0x2D, 0x93, 0x80, 0x19, 0xE3, 0x26, 0x5D, 0x59, 0xBE, 0x46, 0x6D, 0x90, 
    0x4B, 0xDF, 0x72, 0xCE, 0x6C, 0x69, 0x72, 0x8F, 0x5B, 0xA4, 0x74, 0x50, 0x2A, 0x42, 0x95, 0xB2, 
    0x19, 0x04, 0x88, 0xD7, 0xDA, 0xBB, 0x17, 0x23, 0x69, 0xF4, 0x52, 0xEB, 0xC8, 0x55, 0xBE, 0xBC, 
    0x2E, 0xA9, 0xD0, 0x57, 0x7D, 0xC6, 0xC8, 0x8B, 0x86, 0x7B, 0x73, 0xCD, 0xE4, 0x32, 0x79, 0xC0, 
    0x75, 0x53, 0x53, 0xE7, 0x59, 0x38, 0x0A, 0x8C, 0xEC, 0x06, 0xA9, 0xFC, 0xA5, 0x15, 0x81, 0x61, 
    0x3E, 0x44, 0xCD, 0x05, 0xF8, 0x54, 0x04, 0x00, 0x79, 0xB2, 0x0D, 0x69, 0x2A, 0x47, 0x60, 0x1A, 
    0x2B, 0x79, 0x3D, 0x4B, 0x50, 0x8A, 0x31, 0x72, 0x48, 0xBB, 0x75, 0x78, 0xD6, 0x35, 0x90, 0xE1,
};
static HI_U8 P[]  = 
{
    0xC4, 0x29, 0x15, 0xFD, 0xE6, 0xAD, 0x5D, 0x4D, 0xC5, 0xDE, 0x95, 0xB6, 0x4A, 0xA8, 0x25, 0x42, 
    0x15, 0x1D, 0x58, 0x0E, 0xA5, 0xEB, 0xDD, 0xE4, 0xDC, 0x70, 0xA4, 0x28, 0xA7, 0xC1, 0xC9, 0x1C, 
    0xBA, 0x2F, 0xA7, 0xAF, 0xE4, 0xCF, 0xC7, 0xBD, 0x87, 0x3F, 0x7C, 0xD6, 0xD7, 0x7B, 0x7D, 0x4F, 
    0xA1, 0xBB, 0x79, 0x06, 0x2D, 0xF1, 0xDE, 0x00, 0x1E, 0xA9, 0x87, 0x29, 0xFD, 0xE1, 0xA8, 0x43, 
    0xB6, 0x28, 0xC5, 0xF7, 0x2F, 0xFB, 0x64, 0x05, 0x7C, 0x6C, 0xD2, 0xFD, 0x54, 0xE4, 0x43, 0xE0, 
    0x80, 0xD2, 0xE3, 0xE3, 0xB4, 0xBC, 0x4E, 0xE5, 0x59, 0x93, 0x36, 0x5E, 0x9A, 0x79, 0x49, 0x7B, 
    0x40, 0x5F, 0xCE, 0xAE, 0x4A, 0x1B, 0x59, 0x63, 0x5F, 0xA1, 0x37, 0x6C, 0x18, 0x65, 0xA9, 0x2F, 
    0x71, 0x0C, 0x1A, 0xB4, 0xA1, 0x00, 0xD3, 0x20, 0x0D, 0x9A, 0xC1, 0x0B, 0x96, 0x88, 0x16, 0xC9, 
};
static HI_U8 Q[] = 
{
    0xAA, 0x45, 0x9E, 0x08, 0x44, 0x6B, 0x7B, 0x7D, 0x47, 0x09, 0x4C, 0xFA, 0x24, 0x4A, 0xAD, 0xD3, 
    0x4B, 0xF6, 0x46, 0x35, 0x63, 0xA0, 0xAD, 0xB6, 0x61, 0x0A, 0xE6, 0x1D, 0x8E, 0xAB, 0x74, 0xF1, 
    0x16, 0x5F, 0x83, 0xD8, 0x96, 0xB8, 0x69, 0xC5, 0x17, 0x70, 0x5B, 0x31, 0x18, 0xA4, 0xD7, 0x32, 
    0x83, 0xCD, 0x41, 0xAF, 0xC1, 0xAB, 0xD3, 0xA2, 0x15, 0xBF, 0x29, 0x05, 0x8F, 0xB9, 0xB7, 0xB8, 
    0xDB, 0xCC, 0x42, 0x3C, 0x4E, 0x8C, 0xC7, 0xF2, 0x27, 0x89, 0xA6, 0x0D, 0x6C, 0x4F, 0xD2, 0x11, 
    0x94, 0x64, 0xAA, 0xA0, 0x8C, 0x31, 0x7E, 0x5B, 0x0D, 0xF0, 0x6B, 0xAA, 0xE8, 0x43, 0x80, 0x2B, 
    0x73, 0x1B, 0x69, 0xD0, 0x0F, 0x0F, 0xD8, 0x5E, 0x35, 0xC5, 0xDF, 0x67, 0x86, 0x33, 0x0B, 0xDD, 
    0xE6, 0xCF, 0x6D, 0x2D, 0x60, 0x8B, 0x2B, 0x0F, 0x9F, 0xFA, 0x06, 0x7E, 0x4D, 0x7C, 0x1B, 0x0D, 
};
static HI_U8 DP[] = 
{
    0x3E, 0xCD, 0x40, 0xA3, 0x37, 0x55, 0x4D, 0xC7, 0xF6, 0x8F, 0x9A, 0xB2, 0xF0, 0x18, 0x01, 0x45, 
    0xB4, 0xE8, 0xDE, 0x26, 0x62, 0x6C, 0xAF, 0x6F, 0xF4, 0x3B, 0x83, 0xF3, 0x18, 0x32, 0x6C, 0xA6, 
    0xEB, 0xDD, 0x11, 0xFC, 0xB8, 0x6E, 0xE5, 0x6E, 0x02, 0x7D, 0x0B, 0x04, 0xE5, 0x9C, 0x3D, 0xB4, 
    0x5E, 0xFD, 0x5C, 0x73, 0xE4, 0x05, 0xC9, 0xA3, 0x94, 0x2D, 0x86, 0x7E, 0xA5, 0x2F, 0xB7, 0xE5, 
    0x65, 0xCE, 0x8C, 0x02, 0xE5, 0xB3, 0xC0, 0x84, 0x19, 0x1F, 0xE6, 0x35, 0x01, 0x16, 0xCB, 0xBC, 
    0x76, 0xC2, 0x0D, 0xFF, 0xFA, 0xFF, 0x46, 0xEB, 0x1A, 0xD0, 0x8C, 0xD9, 0xA0, 0xEF, 0x2F, 0xDD, 
    0x6B, 0xF0, 0xC0, 0x85, 0x00, 0x68, 0xDD, 0x27, 0x79, 0x98, 0x6D, 0xDC, 0x07, 0xBB, 0x94, 0x7D, 
    0x01, 0xDE, 0x74, 0x36, 0x5C, 0x4D, 0x9D, 0x4A, 0x67, 0xD0, 0xA1, 0xF9, 0x89, 0xCA, 0x2C, 0x31,
};
static HI_U8 DQ[] = 
{
    0x6F, 0xE5, 0x28, 0x21, 0x4E, 0xB5, 0x43, 0x85, 0xE4, 0x74, 0xDC, 0x3D, 0x56, 0x34, 0x2D, 0x5F, 
    0x3A, 0x00, 0x31, 0xCB, 0x4C, 0x19, 0x7F, 0x8E, 0xE6, 0xDE, 0xFE, 0xB2, 0x55, 0xDB, 0x9F, 0x12, 
    0x00, 0x1D, 0xEC, 0xCB, 0x1C, 0xE1, 0x3B, 0xC0, 0xE5, 0xD2, 0x54, 0x5B, 0x43, 0x52, 0xB0, 0x88, 
    0xE5, 0xCC, 0xB1, 0x6A, 0x0A, 0xE0, 0x1C, 0x47, 0xDB, 0xFA, 0xAF, 0xBE, 0x93, 0xE0, 0xFC, 0x37, 
    0x63, 0x5A, 0x2B, 0xFC, 0xED, 0xB1, 0xDE, 0x83, 0xE8, 0x2F, 0xB1, 0x0C, 0x09, 0x2D, 0xBB, 0x63, 
    0x0A, 0x1D, 0xCD, 0x73, 0x8C, 0x2D, 0xCA, 0x57, 0x94, 0x25, 0x76, 0xDB, 0xED, 0x9E, 0xCE, 0x4F, 
    0xBF, 0x69, 0x38, 0x74, 0x1E, 0x31, 0xCF, 0x82, 0xB9, 0xDB, 0xBB, 0x20, 0x91, 0x34, 0x62, 0x8C, 
    0x04, 0xEE, 0x33, 0x55, 0x2A, 0xA8, 0xCA, 0x37, 0x8E, 0x6E, 0x04, 0x6E, 0x64, 0x05, 0x36, 0xD1,
};   
static HI_U8 QP[] = 
{
    0xBA, 0xBE, 0x60, 0x75, 0x6A, 0x59, 0x4B, 0x63, 0xE6, 0x2D, 0xBF, 0x48, 0x28, 0xDD, 0xC2, 0x8F, 
    0x3F, 0x59, 0x74, 0xCC, 0xD0, 0xC4, 0x0B, 0xD4, 0x19, 0x2E, 0x88, 0x80, 0x58, 0x8E, 0x28, 0x11, 
    0x69, 0x55, 0xB3, 0xC5, 0x16, 0x12, 0x0F, 0xF5, 0xDB, 0x99, 0x2A, 0xCA, 0x02, 0x1B, 0xA7, 0xBA, 
    0xC0, 0x80, 0x97, 0x63, 0x3A, 0xD7, 0x9F, 0x8C, 0xF4, 0xC7, 0xA8, 0x26, 0xEC, 0x03, 0x36, 0x5C, 
    0xE2, 0x01, 0x07, 0xF4, 0xD6, 0x6E, 0xAF, 0x31, 0x3B, 0x0E, 0xD8, 0xA5, 0x84, 0x9D, 0x8F, 0x20, 
    0x29, 0xA9, 0x28, 0xFB, 0x8D, 0x5D, 0xD4, 0xBD, 0xF0, 0x08, 0x31, 0x88, 0x9E, 0x04, 0x43, 0x5F, 
    0x0F, 0x21, 0x50, 0xBD, 0x25, 0x01, 0xFA, 0xD9, 0x0A, 0xA0, 0xDE, 0xA6, 0x16, 0xDA, 0x11, 0xC3, 
    0x99, 0x05, 0xCA, 0x16, 0x59, 0x62, 0x1F, 0xB4, 0x78, 0xE7, 0x96, 0x1D, 0xCF, 0x2F, 0x23, 0xE8,
}; 

void rsa_prim_test1(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint8_t     DataIn_ptr[TEST_KEY_SIZE];
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    CRYS_RSAPrimeData_t   PrimeData_ptr;
    HI_U32 i;

    for(i=0;i<TEST_KEY_SIZE;i++)
    {
        DataIn_ptr[i] = i;
    }

#if 0
    CIPHER_RSA_KEY_S stRsaKey;

    stRsaKey.u32Exponent = 0x03;
    stRsaKey.u32NumBits = TEST_KEY_SIZE*8;
    stRsaKey.stPriKey.pu8N = tN;
    stRsaKey.stPriKey.pu8E = tE;
    stRsaKey.stPriKey.pu8D= tD;
    stRsaKey.stPriKey.pu8P= P;
    stRsaKey.stPriKey.pu8Q= Q;
    stRsaKey.stPriKey.pu8DP = DP;
    stRsaKey.stPriKey.pu8DQ = DQ;
    stRsaKey.stPriKey.pu8QP = QP;    
    DRV_CIPHER_GenRsaKey_SW(&stRsaKey);
    
    memset(stRsaKey.stPriKey.pu8E, 0, TEST_KEY_SIZE);
    stRsaKey.stPriKey.u16ELen = TEST_KEY_SIZE;
    stRsaKey.stPriKey.pu8E[TEST_KEY_SIZE-1] = 0x03;
    
    HI_PRINT_HEX ("N", stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
    HI_PRINT_HEX ("E", stRsaKey.stPriKey.pu8E, stRsaKey.stPriKey.u16ELen);
    HI_PRINT_HEX ("D", stRsaKey.stPriKey.pu8D, stRsaKey.stPriKey.u16DLen);
#endif

    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, TEST_KEY_SIZE);
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PubKey_ptr->e, tE, TEST_KEY_SIZE);
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PRIM_Encrypt(&UserPubKey_ptr, &PrimeData_ptr, DataIn_ptr, sizeof(DataIn_ptr), Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Encrypt failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("CRYS_RSA_PRIM_Encrypt-ENC", Output_ptr, TEST_KEY_SIZE);

    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
    PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, TEST_KEY_SIZE);
    PrivKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, tD, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.e, tE, TEST_KEY_SIZE);
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = TEST_KEY_SIZE*8;

    err = CRYS_RSA_PRIM_Decrypt(&UserPrivKey_ptr, &PrimeData_ptr, Output_ptr, TEST_KEY_SIZE, Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Decrypt failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("CRYS_RSA_PRIM_Encrypt-DEC", Output_ptr, TEST_KEY_SIZE);
    if (memcmp(Output_ptr, DataIn_ptr, TEST_KEY_SIZE) != 0)
    {
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Decrypt failed\n");	
        return;
	}
    
}

void rsa_prim_test2(void)
{
    CRYSError_t  err;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;  				  			      
    DxUint8_t     DataIn_ptr[TEST_KEY_SIZE];
    DxUint8_t     Output_ptr[TEST_KEY_SIZE];
    CRYSRSAPrivKey_t *PrivKey_ptr;
    CRYSRSAPubKey_t *PubKey_ptr;
    CRYS_RSAPrimeData_t   PrimeData_ptr;
    HI_U32 i;
    for(i=0;i<TEST_KEY_SIZE;i++)
    {
        DataIn_ptr[i] = i;
    }
#if 0
    CIPHER_RSA_KEY_S stRsaKey;
    stRsaKey.u32Exponent = 0x03;
    stRsaKey.u32NumBits = TEST_KEY_SIZE*8;
    stRsaKey.stPriKey.pu8N = tN;
    stRsaKey.stPriKey.pu8E = tE;
    stRsaKey.stPriKey.pu8D= tD;
    stRsaKey.stPriKey.pu8P= P;
    stRsaKey.stPriKey.pu8Q= Q;
    stRsaKey.stPriKey.pu8DP = DP;
    stRsaKey.stPriKey.pu8DQ = DQ;
    stRsaKey.stPriKey.pu8QP = QP;    
    DRV_CIPHER_GenRsaKey_SW(&stRsaKey);
    memset(stRsaKey.stPriKey.pu8E, 0, TEST_KEY_SIZE);
    stRsaKey.stPriKey.u16ELen = TEST_KEY_SIZE;
    stRsaKey.stPriKey.pu8E[TEST_KEY_SIZE-1] = 0x03;
    HI_PRINT_HEX ("N", stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
    HI_PRINT_HEX ("E", stRsaKey.stPriKey.pu8E, stRsaKey.stPriKey.u16ELen);
    HI_PRINT_HEX ("D", stRsaKey.stPriKey.pu8D, stRsaKey.stPriKey.u16DLen);
#endif
    PubKey_ptr = (CRYSRSAPubKey_t *)UserPubKey_ptr.PublicKeyDbBuff;
    UserPubKey_ptr.valid_tag = CRYS_RSA_PUB_KEY_VALIDATION_TAG;
    CRYS_Bin2Bn(PubKey_ptr->n, tN, TEST_KEY_SIZE);
    PubKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PubKey_ptr->e, tE, TEST_KEY_SIZE);
    PubKey_ptr->eSizeInBits = TEST_KEY_SIZE*8;
    err = CRYS_RSA_PRIM_Encrypt(&UserPubKey_ptr, &PrimeData_ptr, DataIn_ptr, sizeof(DataIn_ptr), Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Encrypt failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("CRYS_RSA_PRIM_Encrypt-ENC", Output_ptr, TEST_KEY_SIZE);
    UserPrivKey_ptr.valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG;
    PrivKey_ptr = (CRYSRSAPrivKey_t *)UserPrivKey_ptr.PrivateKeyDbBuff;
    PrivKey_ptr->OperationMode = CRYS_RSA_Crt;
    CRYS_Bin2Bn(PrivKey_ptr->n, tN, TEST_KEY_SIZE);
    PrivKey_ptr->nSizeInBits = TEST_KEY_SIZE*8;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.P, P, TEST_KEY_SIZE/2);
    PrivKey_ptr->PriveKeyDb.Crt.PSizeInBits = TEST_KEY_SIZE*4;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.Q, Q, TEST_KEY_SIZE/2);
    PrivKey_ptr->PriveKeyDb.Crt.QSizeInBits = TEST_KEY_SIZE*4;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.dP, DP, TEST_KEY_SIZE/2);
    PrivKey_ptr->PriveKeyDb.Crt.dPSizeInBits = TEST_KEY_SIZE*4;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.dQ, DQ, TEST_KEY_SIZE/2);
    PrivKey_ptr->PriveKeyDb.Crt.dQSizeInBits = TEST_KEY_SIZE*4;
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.qInv, QP, TEST_KEY_SIZE/2);
    PrivKey_ptr->PriveKeyDb.Crt.qInvSizeInBits = TEST_KEY_SIZE*4;
    err = CRYS_RSA_PRIM_Decrypt(&UserPrivKey_ptr, &PrimeData_ptr, Output_ptr, TEST_KEY_SIZE, Output_ptr);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Decrypt failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("CRYS_RSA_PRIM_Encrypt-DEC", Output_ptr, TEST_KEY_SIZE);
    if (memcmp(Output_ptr, DataIn_ptr, TEST_KEY_SIZE) != 0)
    {
		HI_ERR_CIPHER ("CRYS_RSA_OAEP_Decrypt failed\n");	
        return;
	}
}
void rsa_prim_test(void)
{
    rsa_prim_test1();
    rsa_prim_test2();
}
#endif

#endif /*!defined(_INTERNAL_CRYS_NO_RSA_DECRYPT_SUPPORT) && !defined(_INTERNAL_CRYS_NO_RSA_SIGN_SUPPORT)*/


