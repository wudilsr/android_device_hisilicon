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

/* .............. CRYS level includes ................. */
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
#include "crys_common_math.h"
#include "crys_rsa_kg.h"
#include "crys_rnd.h"
#include "crys_cipher_common.h"


/************************ Defines ******************************/

/* canceling the lint warning:
   Use of goto is deprecated */
/*lint --e{801} */

/************************ Enums ************************************/

/************************ Typedefs *********************************/

/************************ Global Data ******************************/



/************* Private function prototype **************************/


/************************ Public Functions ******************************/


/***********************************************************************************************/
#ifndef _INTERNAL_CRYS_NO_RSA_KG_SUPPORT


    


/**
   @brief CRYS_RSA_KG_GenerateKeyPair generates a Pair of public and private keys on non CRT mode.
 
   @param[in] PubExp_ptr - The pointer to the public exponent (public key)
   @param[in] PubExpSizeInBytes - The public exponent size in bytes.
   @param[in] KeySize  - The size of the key, in bits. Supported sizes are:
                            - for PKI without PKA HW: all 256 bit multiples between 512 - 2048;
                            - for PKI with PKA: HW all 32 bit multiples between 512 - 2112;
   @param[out] UserPrivKey_ptr - A pointer to the private key structure. 
                           This structure is used as input to the CRYS_RSA_PRIM_Decrypt API.
   @param[out] UserPubKey_ptr - A pointer to the public key structure. 
                           This structure is used as input to the CRYS_RSA_PRIM_Encrypt API.
   @param[in] KeyGenData_ptr - a pointer to a structure required for the KeyGen operation.                       

   @return CRYSError_t - CRYS_OK,
                         CRYS_RSA_INVALID_EXPONENT_POINTER_ERROR,
                         CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR,
                         CRYS_RSA_INVALID_PUB_KEY_STRUCT_POINTER_ERROR,
                         CRYS_RSA_KEY_GEN_DATA_STRUCT_POINTER_INVALID,
                         CRYS_RSA_INVALID_MODULUS_SIZE,
                         CRYS_RSA_INVALID_EXPONENT_SIZE
*/
CEXPORT_C CRYSError_t CRYS_RSA_KG_GenerateKeyPair(
				DxUint8_t             *PubExp_ptr,
				DxUint16_t             PubExpSizeInBytes, 
				DxUint32_t             KeySize,
				CRYS_RSAUserPrivKey_t *UserPrivKey_ptr,
				CRYS_RSAUserPubKey_t  *UserPubKey_ptr,
				CRYS_RSAKGData_t      *KeyGenData_ptr )
{
	/* LOCAL INITIALIZATIONS AND DECLERATIONS */
	HI_S32 ret = HI_SUCCESS;
	
	/* the pointers to the key structures */
	CRYSRSAPubKey_t  *PubKey_ptr;  
	CRYSRSAPrivKey_t *PrivKey_ptr; 
	CIPHER_RSA_KEY_S stRsaKey;
    HI_U8* pu8Key;
    HI_U32 i;
                                      

	/* ................ initializaions and local declarations ............ */
	/* ------------------------------------------------------------------- */
	
	
	/* ................. checking the validity of the pointer arguments ....... */
	/* ------------------------------------------------------------------------ */
	
	/* ...... checking the key database handle pointer .................... */
	if( PubExp_ptr == DX_NULL )
		return CRYS_RSA_INVALID_EXPONENT_POINTER_ERROR;
	
	/* ...... checking the validity of the exponent pointer ............... */
	if( UserPrivKey_ptr == DX_NULL )
		return CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR;
	
	/* ...... checking the validity of the modulus pointer .............. */
	if( UserPubKey_ptr == DX_NULL )
		return CRYS_RSA_INVALID_PUB_KEY_STRUCT_POINTER_ERROR;
	
	/* ...... checking the validity of the keygen data .................. */
	if( KeyGenData_ptr == DX_NULL )
		return CRYS_RSA_KEY_GEN_DATA_STRUCT_POINTER_INVALID;
	
	/* ...... checking the exponent size .................. */
	if( PubExpSizeInBytes > CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BYTES )
		return CRYS_RSA_INVALID_EXPONENT_SIZE;
		
	/* ...... checking the required key size ............................ */
	if( ( KeySize < CRYS_RSA_MIN_VALID_KEY_SIZE_VALUE_IN_BITS ) ||
	( KeySize > CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS ) ||
	( KeySize % CRYS_RSA_VALID_KEY_SIZE_MULTIPLE_VALUE_IN_BITS ) )
	
		return CRYS_RSA_INVALID_MODULUS_SIZE;
	
	/* set the public and private key structure pointers */
	PubKey_ptr  = ( CRYSRSAPubKey_t *)UserPubKey_ptr->PublicKeyDbBuff;
	PrivKey_ptr = ( CRYSRSAPrivKey_t *)UserPrivKey_ptr->PrivateKeyDbBuff;
	
	
	/* ................ clear all input structures ............................. */
	/* ------------------------------------------------------------------------- */
	memset(	PubKey_ptr, 0, sizeof(CRYSRSAPubKey_t));
    memset(	PrivKey_ptr, 0, sizeof(CRYSRSAPrivKey_t));
    memset(	KeyGenData_ptr, 0, sizeof(CRYS_RSAKGData_t));
	/* ................ loading the public exponent to the structure .......... */
	/* ------------------------------------------------------------------------- */

    if (PubExpSizeInBytes > 4)
   	{
   	    return CRYS_RSA_INVALID_EXPONENT_SIZE;
	} 
    PubKey_ptr->e[0]= 0;
    for(i=0; i<PubExpSizeInBytes; i++)
    {
        PubKey_ptr->e[0] <<= 8;
        PubKey_ptr->e[0] |= PubExp_ptr[i];
    }
    PubKey_ptr->eSizeInBits = CRYS_GetBitNum(PubExp_ptr, PubExpSizeInBytes);
	PrivKey_ptr->PriveKeyDb.NonCrt.e[0] = PubKey_ptr->e[0];
    PrivKey_ptr->PriveKeyDb.NonCrt.eSizeInBits = PubKey_ptr->eSizeInBits;
    
	/* .......... initializing the effective counters size in bits .......... */
	
	/* if the size in bits is 0 - return error */
	if(PubKey_ptr->eSizeInBits == 0 || PubKey_ptr->eSizeInBits > 17)
    {
		return CRYS_RSA_INVALID_EXPONENT_SIZE;
	}
	
	/* verifying the exponent has legal value (currently only 0x3,0x11 and 0x10001) */
	if(PubKey_ptr->e[0] != CRYS_RSA_KG_PUB_EXP_ALLOW_VAL_1  &&
	   PubKey_ptr->e[0] != CRYS_RSA_KG_PUB_EXP_ALLOW_VAL_2  &&
	   PubKey_ptr->e[0] != CRYS_RSA_KG_PUB_EXP_ALLOW_VAL_3){
		return CRYS_RSA_INVALID_EXPONENT_VAL;
	}
	
	/* .......... initializing the key size in bits ......................... */
	
	/* this initialization is required for the low level function (LLF) - indicates the required
	size of the key to be found */
	PubKey_ptr->nSizeInBits  = KeySize;
	PrivKey_ptr->nSizeInBits = KeySize;
    pu8Key = (HI_U8*)KeyGenData_ptr;
    
    stRsaKey.u32Exponent = PubKey_ptr->e[0];
    stRsaKey.u32NumBits = KeySize;
    stRsaKey.stPriKey.pu8N = pu8Key;
    stRsaKey.stPriKey.pu8E = stRsaKey.stPriKey.pu8N + RSA_MAX_RSA_KEY_LEN;
    stRsaKey.stPriKey.pu8D = stRsaKey.stPriKey.pu8E + 4;
    stRsaKey.stPriKey.pu8P = stRsaKey.stPriKey.pu8D + RSA_MAX_RSA_KEY_LEN/2;
	stRsaKey.stPriKey.pu8Q = stRsaKey.stPriKey.pu8P + RSA_MAX_RSA_KEY_LEN/2;
	stRsaKey.stPriKey.pu8DP = stRsaKey.stPriKey.pu8Q + RSA_MAX_RSA_KEY_LEN/2;
	stRsaKey.stPriKey.pu8DQ = stRsaKey.stPriKey.pu8DP + RSA_MAX_RSA_KEY_LEN/2;
	stRsaKey.stPriKey.pu8QP = stRsaKey.stPriKey.pu8DQ + RSA_MAX_RSA_KEY_LEN/2;
    ret = DRV_CIPHER_GenRsaKey_SW(&stRsaKey);
    if (ret != HI_SUCCESS)  
    {
       HI_ERR_CIPHER("DRV_CIPHER_GenRsaKey_SW, err = 0x%x\n", ret);
       return CRYS_FATAL_ERROR; 
    }
//    HI_PRINT_HEX ("N", stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
//    HI_PRINT_HEX ("E", stRsaKey.stPriKey.pu8E, stRsaKey.stPriKey.u16ELen);
//    HI_PRINT_HEX ("D", stRsaKey.stPriKey.pu8D, stRsaKey.stPriKey.u16DLen);

	CRYS_Bin2Bn(PubKey_ptr->n, stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
    CRYS_Bin2Bn(PrivKey_ptr->n, stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.NonCrt.d, stRsaKey.stPriKey.pu8D, stRsaKey.stPriKey.u16DLen);
    PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits = CRYS_GetBitNum(stRsaKey.stPriKey.pu8D, stRsaKey.stPriKey.u16DLen);
	/* .......... set the private mode to non CRT .............................. */   
	/* ------------------------------------------------------------------------- */
	
	/* set the mode to non CRT */
	PrivKey_ptr->OperationMode = CRYS_RSA_NoCrt;
	
	/* set the key source as internal */
	PrivKey_ptr->KeySource = CRYS_RSA_InternalKey;
	
	/* ................ executing the key generation ........................... */
	/* ------------------------------------------------------------------------- */

	/* ................ set the key valid tags ................................. */
	/* ------------------------------------------------------------------------- */
	UserPrivKey_ptr->valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG; 
	UserPubKey_ptr->valid_tag  = CRYS_RSA_PUB_KEY_VALIDATION_TAG; 

    memset(KeyGenData_ptr, 0, sizeof(CRYS_RSAKGData_t));  

    return CRYS_OK;

}/* END OF CRYS_RSA_KG_GenerateKeyPair */ 

                                      
/***********************************************************************************************/
/**
   @brief CRYS_RSA_KG_GenerateKeyPairCRT generates a Pair of public and private keys on CRT mode.

   @param[in] PubExp_ptr - The pointer to the public exponent (public key)
   @param[in] PubExpSizeInBytes - The public exponent size in bits. 
   @param[in] KeySize  - The size of the key, in bits. Supported sizes are:
                            - for PKI without PKA HW: all 256 bit multiples between 512 - 2048;
                            - for PKI with PKA: HW all 32 bit multiples between 512 - 2112;
   @param[out] UserPrivKey_ptr - A pointer to the private key structure. 
                           This structure is used as input to the CRYS_RSA_PRIM_Decrypt API.
   @param[out] UserPubKey_ptr - A pointer to the public key structure. 
                           This structure is used as input to the CRYS_RSA_PRIM_Encryped API.
   @param[in] KeyGenData_ptr - a pointer to a structure required for the KeyGen operation.                       

   @return CRYSError_t - CRYS_OK,
                         CRYS_RSA_INVALID_EXPONENT_POINTER_ERROR,
                         CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR,
                         CRYS_RSA_INVALID_PUB_KEY_STRUCT_POINTER_ERROR,
                         CRYS_RSA_KEY_GEN_DATA_STRUCT_POINTER_INVALID,
                         CRYS_RSA_INVALID_MODULUS_SIZE,
                         CRYS_RSA_INVALID_EXPONENT_SIZE
*/

CEXPORT_C CRYSError_t CRYS_RSA_KG_GenerateKeyPairCRT(DxUint8_t               *PubExp_ptr,
                                           DxUint16_t               PubExpSizeInBytes, 
                                           DxUint32_t               KeySize,
                                           CRYS_RSAUserPrivKey_t *UserPrivKey_ptr,
                                           CRYS_RSAUserPubKey_t  *UserPubKey_ptr,
                                           CRYS_RSAKGData_t      *KeyGenData_ptr )
{
   /* LOCAL INITIALIZATIONS AND DECLERATIONS */
   
   /* the error identifier */
   HI_S32 ret = HI_SUCCESS;
      
   /* the pointers to the key structures */
   CRYSRSAPubKey_t  *PubKey_ptr;  
   CRYSRSAPrivKey_t *PrivKey_ptr; 
   CIPHER_RSA_KEY_S stRsaKey;
   HI_U8* pu8Key;
   HI_U32 i;
 
   /* FUNCTION LOGIC */

   /* ............... if not supported exit .............................. */
   /* -------------------------------------------------------------------- */                                      

   /* ............... initializations and local declarations ............ */
   /* ------------------------------------------------------------------- */

   /* ........... checking the validity of the pointer arguments ....... */
   /* ------------------------------------------------------------------ */
   
   /* ...... checking the key database handle pointer .................. */
   if( PubExp_ptr == DX_NULL )
      return CRYS_RSA_INVALID_EXPONENT_POINTER_ERROR;
      
   /* ...... checking the validity of the exponent pointer ............. */
   if( UserPrivKey_ptr == DX_NULL )
      return CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR;
      
   /* ...... checking the validity of the modulus pointer .............. */
   if( UserPubKey_ptr == DX_NULL )
      return CRYS_RSA_INVALID_PUB_KEY_STRUCT_POINTER_ERROR;
      
   /* ...... checking the validity of the keygen data .................. */
   if( KeyGenData_ptr == DX_NULL )
      return CRYS_RSA_KEY_GEN_DATA_STRUCT_POINTER_INVALID;
      
   /* ...... checking the required key size ............................ */
   if( ( KeySize < CRYS_RSA_MIN_VALID_KEY_SIZE_VALUE_IN_BITS ) ||
       ( KeySize > CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS ) ||
       ( KeySize % CRYS_RSA_VALID_KEY_SIZE_MULTIPLE_VALUE_IN_BITS ) ){
	   return CRYS_RSA_INVALID_MODULUS_SIZE;
   }

   /* set the public and private key structure pointers */
   PubKey_ptr  = (CRYSRSAPubKey_t*)UserPubKey_ptr->PublicKeyDbBuff;
   PrivKey_ptr = (CRYSRSAPrivKey_t*)UserPrivKey_ptr->PrivateKeyDbBuff;
   
   /* ................ clear all input structures ............................. */
   /* ------------------------------------------------------------------------- */
   
   memset(UserPrivKey_ptr, 0, sizeof(CRYS_RSAUserPrivKey_t)); 
   memset(UserPubKey_ptr, 0, sizeof(CRYS_RSAUserPubKey_t)); 
   memset(KeyGenData_ptr, 0, sizeof(CRYS_RSAKGData_t));
     
   /* ................ loading the public exponent to the structure .......... */
   /* ------------------------------------------------------------------------- */
   
    if (PubExpSizeInBytes > 4)
   	{
   	    return CRYS_RSA_INVALID_EXPONENT_SIZE;
	} 
    PubKey_ptr->e[0]= 0;
    for(i=0; i<PubExpSizeInBytes; i++)
    {
        PubKey_ptr->e[0] <<= 8;
        PubKey_ptr->e[0] |= PubExp_ptr[i];
    }
    PubKey_ptr->eSizeInBits = CRYS_GetBitNum(PubExp_ptr, PubExpSizeInBytes);
	/* .......... initializing the effective counters size in bits .......... */
	
	/* if the size in bits is 0 - return error */
	if(PubKey_ptr->eSizeInBits == 0 || PubKey_ptr->eSizeInBits > 17)
    {
		return CRYS_RSA_INVALID_EXPONENT_SIZE;
	}
  	/* verifying the exponent has legal value (currently only 0x3,0x11 and 0x10001) */
	if(PubKey_ptr->e[0] != CRYS_RSA_KG_PUB_EXP_ALLOW_VAL_1  &&
	   PubKey_ptr->e[0] != CRYS_RSA_KG_PUB_EXP_ALLOW_VAL_2  &&
	   PubKey_ptr->e[0] != CRYS_RSA_KG_PUB_EXP_ALLOW_VAL_3){
		return CRYS_RSA_INVALID_EXPONENT_VAL;
	}
	
	/* .......... initializing the key size in bits ......................... */
	
	/* this initialization is required for the low level function (LLF) - indicates the required
	size of the key to be found */
	PubKey_ptr->nSizeInBits  = KeySize;
	PrivKey_ptr->nSizeInBits = KeySize;
    pu8Key = (HI_U8*)KeyGenData_ptr;
    
    stRsaKey.u32Exponent = PubKey_ptr->e[0];
    stRsaKey.u32NumBits = KeySize;
    stRsaKey.stPriKey.pu8N = pu8Key;
    stRsaKey.stPriKey.pu8E = stRsaKey.stPriKey.pu8N + RSA_MAX_RSA_KEY_LEN;
    stRsaKey.stPriKey.pu8D = stRsaKey.stPriKey.pu8E + 4;
    stRsaKey.stPriKey.pu8P = stRsaKey.stPriKey.pu8D + RSA_MAX_RSA_KEY_LEN/2;
	stRsaKey.stPriKey.pu8Q = stRsaKey.stPriKey.pu8P + RSA_MAX_RSA_KEY_LEN/2;
	stRsaKey.stPriKey.pu8DP = stRsaKey.stPriKey.pu8Q + RSA_MAX_RSA_KEY_LEN/2;
	stRsaKey.stPriKey.pu8DQ = stRsaKey.stPriKey.pu8DP + RSA_MAX_RSA_KEY_LEN/2;
	stRsaKey.stPriKey.pu8QP = stRsaKey.stPriKey.pu8DQ + RSA_MAX_RSA_KEY_LEN/2;
    ret = DRV_CIPHER_GenRsaKey_SW(&stRsaKey);
    if (ret != HI_SUCCESS)  
    {
       HI_ERR_CIPHER("DRV_CIPHER_GenRsaKey_SW, err = 0x%x\n", ret);
       return CRYS_FATAL_ERROR; 
    }
        
//    HI_PRINT_HEX ("N", stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
//    HI_PRINT_HEX ("E", stRsaKey.stPriKey.pu8E, stRsaKey.stPriKey.u16ELen);
//    HI_PRINT_HEX ("D", stRsaKey.stPriKey.pu8D, stRsaKey.stPriKey.u16DLen);

	CRYS_Bin2Bn(PubKey_ptr->n, stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
    CRYS_Bin2Bn(PrivKey_ptr->n, stRsaKey.stPriKey.pu8N, stRsaKey.stPriKey.u16NLen);
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.P, stRsaKey.stPriKey.pu8P, stRsaKey.stPriKey.u16PLen);
    PrivKey_ptr->PriveKeyDb.Crt.PSizeInBits = CRYS_GetBitNum(stRsaKey.stPriKey.pu8P, stRsaKey.stPriKey.u16PLen);
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.Q, stRsaKey.stPriKey.pu8Q, stRsaKey.stPriKey.u16QLen);
    PrivKey_ptr->PriveKeyDb.Crt.QSizeInBits = CRYS_GetBitNum(stRsaKey.stPriKey.pu8Q, stRsaKey.stPriKey.u16QLen);
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.dP, stRsaKey.stPriKey.pu8DP, stRsaKey.stPriKey.u16DPLen);
    PrivKey_ptr->PriveKeyDb.Crt.dPSizeInBits = CRYS_GetBitNum(stRsaKey.stPriKey.pu8DP, stRsaKey.stPriKey.u16DPLen);
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.dQ, stRsaKey.stPriKey.pu8DQ, stRsaKey.stPriKey.u16DQLen);
    PrivKey_ptr->PriveKeyDb.Crt.dQSizeInBits = CRYS_GetBitNum(stRsaKey.stPriKey.pu8DQ, stRsaKey.stPriKey.u16DQLen);
    CRYS_Bin2Bn(PrivKey_ptr->PriveKeyDb.Crt.qInv, stRsaKey.stPriKey.pu8QP, stRsaKey.stPriKey.u16QPLen);
    PrivKey_ptr->PriveKeyDb.Crt.qInvSizeInBits = CRYS_GetBitNum(stRsaKey.stPriKey.pu8QP, stRsaKey.stPriKey.u16QPLen);

   /* .......... set the private mode to CRT .................................. */   
   /* ------------------------------------------------------------------------- */
   
   /* set the mode to CRT */
   PrivKey_ptr->OperationMode = CRYS_RSA_Crt;
   
   /* set the key source as internal */
   PrivKey_ptr->KeySource = CRYS_RSA_InternalKey;
   
   UserPrivKey_ptr->valid_tag = CRYS_RSA_PRIV_KEY_VALIDATION_TAG; 
   UserPubKey_ptr->valid_tag  = CRYS_RSA_PUB_KEY_VALIDATION_TAG; 
    
   
   /* clear the KG data structure */
   memset(KeyGenData_ptr, 0, sizeof(CRYS_RSAKGData_t));  
   
   return CRYS_OK;                                 

}/* END OF CRYS_RSA_KG_GenerateKeyPairCRT */



/**********************************************************************************************************/
/** 
 * @brief The CRYS_RSA_GenerateVectorInRangeX931 function generates a random vector in range:
 *            MinVect < RandVect < MaxVect, where:
 *            MinVect = sqwRoot(2) * 2^(RndSizeInBits-1),  MaxVect = 2^RndSizeInBits. 
 *
 *            Note: 1. MSBit of RandVect must be set to 1.
 *                  2. Words order of output vector is set from LS word to MS
 *      	       word. 
 *            
 *        This function is used in PKI RSA for random generation according to ANS X9.31 standard.
 *        If PKI_RSA is not supported, the function does nothing.
 *
 *        Functions algorithm:: 
 *
 *        1.  Calls the CRYS_RND_GenerateVector() function for generating random vector 
 *            RndVect of size RndSizeInWords, rounded up to bytes. Set index i
 *            to high word i = SizeInWords-1.
 *        2.  Check and adust candidate for msWord inside the random vector
 *            starting from msWord himselv, if msWord > high word of MinVect,
 *            goto step 3, else try next word i--; if no words to try, then goto
 *            step 1.
 *        3.  Set the found msWord to high position in array and generate new
 *            random words instead all checked and rejected words.
 *
 * @rndSizeWords[in]  - The size of random vectore that is required.
 * @rnd_ptr[out]      - The output buffer of size not less, than rndSizeWords.
 *
 * @return CRYSError_t - On success CRYS_OK is returned, on failure a
 *                       value MODULE_* as defined in ...
 */
CRYSError_t CRYS_RSA_GenerateVectorInRangeX931(DxUint32_t   rndSizeWords, 
                                               DxUint32_t  *rnd_ptr)
{
	/* MIN_WORD = rounded up MS word of (2^(32*rndSizeWords-1))*sqwRoot(2)*/
	#define  MIN_VAL 0xB504F334

	/* FUNCTION DECLARATIONS */
	
	CRYSError_t error = CRYS_OK;
	DxUint32_t  msWord;
	DxInt32_t   i;
	DxBool_t    isFound = DX_FALSE;
	
#ifdef CRYS_NO_PKI_SUPPORT  
	/* prevent compiler warnings */
	rndSizeWords = rndSizeWords; rnd_ptr = rnd_ptr; 
#else
	
	/* FUNCTION LOGIC */
	

	/* .........         Rnd generation       .............. */
	/* ----------------------------------------------------- */
	
	while(1) 
	{
		/* Genrate random vector candidate */
		error = CRYS_RND_GenerateVector(
			(DxUint16_t)rndSizeWords*sizeof(DxUint32_t), 
			(DxUint8_t*)rnd_ptr); 
		if(error)    
			goto End;

		/* Find and adust candidate for msWord inside the random *  
		*  vector starting from msWord himselv  		 */

		for(i = rndSizeWords-1; i >= 0; i--) {
			/* Set MSBit to 1 */
			msWord = rnd_ptr[i] | 0x80000000;
			
			if(msWord > MIN_VAL){
				rnd_ptr[rndSizeWords-1] = msWord;
				isFound = 1;
			}
			
			/* Generate new random words instead checked yet for  * 
			*  sequrity goals       			      */
			if((isFound == 1) && (i < (DxInt32_t)rndSizeWords - 1)) {
				error = CRYS_RND_GenerateVector(
					(DxUint16_t)(rndSizeWords - 1 - i)*sizeof(DxUint32_t), 
					(DxUint8_t*)&rnd_ptr[i]); 

				if(error)    
					goto End;
			}

			if(isFound == 1)
				break;
		}

		if(isFound){
			rnd_ptr[0] |= 1UL; /* ensure odd result */
			break;
		}
	}
#endif
	
End:
	return error;	
	
} /* End of CRYS_RSA_GenerateVectorInRangeX931 */

#ifdef HI_CIPHER_TEST
void rsa_kg_test1(void)
{
    CRYSError_t err;
    CRYSRSAPubKey_t  *PubKey_ptr;  
    CRYSRSAPrivKey_t *PrivKey_ptr; 
    DxUint8_t             PubExp_ptr[4] = {0x03, 0x00, 0x00, 0x00};
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAKGData_t      KeyGenData_ptr;

    PubKey_ptr  = (CRYSRSAPubKey_t*)UserPubKey_ptr.PublicKeyDbBuff;
    PrivKey_ptr = (CRYSRSAPrivKey_t*)UserPrivKey_ptr.PrivateKeyDbBuff;

   err = CRYS_RSA_KG_GenerateKeyPair(PubExp_ptr, 1, 2048, 
        &UserPrivKey_ptr, &UserPubKey_ptr, &KeyGenData_ptr);

    if (err != CRYS_OK)
    {
		HI_ERR_CIPHER ("CRYS_RSA_KG_GenerateKeyPair failed, err = 0x%x\n", err);	
        return;
	}
    HI_PRINT("KeyPair:\n");
    HI_PRINT_HEX("N", PubKey_ptr->n, (PubKey_ptr->nSizeInBits+7)/8);
    HI_PRINT_HEX("E", PubKey_ptr->e, (PubKey_ptr->eSizeInBits+7)/8);
    HI_PRINT_HEX("D", PrivKey_ptr->PriveKeyDb.NonCrt.d, (PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits+7)/8);
    
}

void rsa_kg_test2(void)
{
    CRYSError_t err;
    CRYSRSAPubKey_t  *PubKey_ptr;  
    CRYSRSAPrivKey_t *PrivKey_ptr; 
    DxUint8_t             PubExp_ptr[4] = {0x01, 0x00, 0x01, 0x00};
    CRYS_RSAUserPrivKey_t UserPrivKey_ptr;
    CRYS_RSAUserPubKey_t  UserPubKey_ptr;
    CRYS_RSAKGData_t      KeyGenData_ptr;
    
   err = CRYS_RSA_KG_GenerateKeyPairCRT(PubExp_ptr, 3, 2048, 
        &UserPrivKey_ptr, &UserPubKey_ptr, &KeyGenData_ptr);

    if (err != CRYS_OK)
    {
		HI_ERR_CIPHER ("CRYS_RSA_KG_GenerateKeyPair failed, err = 0x%x\n", err);	
        return;
	}

    PubKey_ptr  = (CRYSRSAPubKey_t*)UserPubKey_ptr.PublicKeyDbBuff;
    PrivKey_ptr = (CRYSRSAPrivKey_t*)UserPrivKey_ptr.PrivateKeyDbBuff;

    HI_PRINT("KeyPairCRT:\n");
    HI_PRINT_HEX("N", PubKey_ptr->n, (PubKey_ptr->nSizeInBits+7)/8);
    HI_PRINT_HEX("E", PubKey_ptr->e, (PubKey_ptr->eSizeInBits+7)/8);
    HI_PRINT_HEX("P", PrivKey_ptr->PriveKeyDb.Crt.P, (PrivKey_ptr->PriveKeyDb.Crt.PSizeInBits+7)/8);
    HI_PRINT_HEX("Q", PrivKey_ptr->PriveKeyDb.Crt.Q, (PrivKey_ptr->PriveKeyDb.Crt.QSizeInBits+7)/8);
    HI_PRINT_HEX("dP", PrivKey_ptr->PriveKeyDb.Crt.dP, (PrivKey_ptr->PriveKeyDb.Crt.dPSizeInBits+7)/8);
    HI_PRINT_HEX("dQ", PrivKey_ptr->PriveKeyDb.Crt.dQ, (PrivKey_ptr->PriveKeyDb.Crt.dQSizeInBits+7)/8);
    HI_PRINT_HEX("QP", PrivKey_ptr->PriveKeyDb.Crt.qInv, (PrivKey_ptr->PriveKeyDb.Crt.qInvSizeInBits+7)/8);

}

void rsa_kg_test(void)
{
    rsa_kg_test1();
    rsa_kg_test2();
}
#endif

#endif /*_INTERNAL_CRYS_NO_RSA_KG_SUPPORT*/
