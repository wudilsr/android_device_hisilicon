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
#include "crys_aes.h"
#include "crys_aes_error.h"
#include "dx_error.h"

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

#define AES_MMZ_BUFF_SIZE  (0x2000)

typedef struct hiAESUserContext_t
{
    HI_HANDLE hCipher;
    HI_BOOL   bIsDecrypt;
    CRYS_AES_OperationMode_t OperationMode;
    HI_U8    auLastBlock[CRYS_AES_BLOCK_SIZE_IN_BYTES];
    HI_U32   u32BloctCnt;
    MMZ_BUFFER_S stMMzIn;
    MMZ_BUFFER_S stMMzOut;
}AESUserContext_t;

/*!
 * Converts Symmetric Adaptor return code to CRYS error code.
 * 
 * \param symRetCode Symmetric Adaptor return error.
 * \param errorInfo Ignored.
 *  
 * \return CRYSError_t one of CRYS_* error codes defined in crys_error.h
 */
static CRYSError_t SymAdaptor2CrysAesErr(int symRetCode, DxUint32_t errorInfo)
{
    CRYSError_t err;
    
	switch (symRetCode) {
	case HI_ERR_CIPHER_NOT_INIT:
		err = CRYS_AES_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_FAILED_INIT:
        err = CRYS_AES_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_INVALID_POINT:
		err =  CRYS_AES_WRAP_ILLEGAL_DATA_PTR_ERROR;
        break;
	case HI_ERR_CIPHER_INVALID_PARA:
        err = CRYS_AES_ILLEGAL_PARAMS_ERROR;
        break;
	case HI_ERR_CIPHER_FAILED_GETHANDLE:
		err =  CRYS_OUT_OF_RESOURCE_ERROR;
        break;
	case HI_ERR_CIPHER_FAILED_CONFIGAES:
		err = CRYS_AES_ILLEGAL_PARAMS_ERROR;
        break;
	case HI_ERR_CIPHER_FAILED_CONFIGDES:
		err = CRYS_AES_ILLEGAL_PARAMS_ERROR;
        break;
	case HI_ERR_CIPHER_BUSY:
	case HI_ERR_CIPHER_NO_AVAILABLE_RNG:
        err = CRYS_AES_IS_NOT_SUPPORTED;
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

static HI_UNF_CIPHER_WORK_MODE_E MakeSepAesMode(CRYS_AES_OperationMode_t OperationMode)
{
	HI_UNF_CIPHER_WORK_MODE_E result;

	switch(OperationMode) {
	case CRYS_AES_ECB_mode:
		result = HI_UNF_CIPHER_WORK_MODE_ECB;
		break;
	case CRYS_AES_CBC_mode:
		result = HI_UNF_CIPHER_WORK_MODE_CBC;
		break;
	case CRYS_AES_CTR_mode:
		result = HI_UNF_CIPHER_WORK_MODE_CTR;
		break;
	case CRYS_AES_CMAC_mode:
		result = HI_UNF_CIPHER_WORK_MODE_CBC;
		break;
	case CRYS_AES_OFB_mode:
		result = HI_UNF_CIPHER_WORK_MODE_OFB;
		break;
	case CRYS_AES_CBC_CTS_mode:
		result = HI_UNF_CIPHER_WORK_MODE_CBC_CTS;
		break;
	default:
		result = HI_UNF_CIPHER_WORK_MODE_BUTT;
	}

	return result;
}

/* For CMAC Calculation */
static HI_U8 const_Rb[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
};

/* Basic Functions */
static HI_VOID xor_128(HI_U8 *a, HI_U8 *b, HI_U8 *out)
{
    HI_U32 i;

    if(a == NULL || b == NULL || out == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return;
    }
    
    for (i = 0; i < 16; i++)
    {
        out[i] = a[i] ^ b[i];
    }
}

/* AES-CMAC Generation Function */
static HI_VOID leftshift_onebit(HI_U8 *input, HI_U8 *output)
{
    HI_S32 i;
    HI_U8 overflow = 0;

    if(input == NULL || output == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return;
    }
    
    for ( i = 15; i >= 0; i-- )
    {
        output[i] = input[i] << 1;
        output[i] |= overflow;
        overflow = (input[i] & 0x80) ? 1 : 0;
    }
    return;
}

static HI_VOID padding ( HI_U8 *lastb, HI_U8 *pad, HI_U32 length )
{
    HI_U32 j;

    if(lastb == NULL || pad == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return;
    }
    
    /* original last block */
    for ( j = 0; j < 16; j++ )
    {
        if ( j < length )
        {
            pad[j] = lastb[j];
        }
        else if ( j == length )
        {
            pad[j] = 0x80;
        }
        else
        {
            pad[j] = 0x00;
        }
    }
}

static CRYSError_t cmac_generate_subkey(CRYS_AESUserContext_t *ContextID_ptr, HI_U8 *K1, HI_U8 *K2)
{
    HI_U8 L[16];
    HI_U8 Z[16];
    HI_U8 tmp[16];
    HI_U32 u32DataLen = 16;
    CRYSError_t err;

    if(K1 == NULL || K2 == NULL)
    {
        HI_ERR_CIPHER("Invalid parameter!\n");
        return HI_FAILURE;
    }

    memset(tmp, 0x0, sizeof(tmp));
    memset(L, 0x0, sizeof(L));
    memset(Z, 0x0, sizeof(Z));

    err = CRYS_AES_SetIv(ContextID_ptr, tmp);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER("CRYS_AES_SetIv failed.\n");
        return err;
    }
    
    err = CRYS_AES_Block(ContextID_ptr, Z, u32DataLen, L);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER("CRYS_AES_Block.\n");
        return err;
    }
    
    if ( (L[0] & 0x80) == 0 ) /* If MSB(L) = 0, then K1 = L << 1 */
    {
        leftshift_onebit(L, K1);
    }
    else  /* Else K1 = ( L << 1 ) (+) Rb */
    {
        leftshift_onebit(L, tmp);
        xor_128(tmp, const_Rb, K1);
    }
    
    if ( (K1[0] & 0x80) == 0 )
    {
        leftshift_onebit(K1,K2);
    }
    else
    {
        leftshift_onebit(K1, tmp);
        xor_128(tmp, const_Rb, K2);
    }

//    HI_PRINT_HEX ("K1", K1, 16);
//    HI_PRINT_HEX ("K2", K2, 16);
    
    return CRYS_OK;
}
             
/****************************************************************************************************/
/** 
 * @brief This function is used to initialize the AES machine or SW structures.
 *        To perform the AES operations this should be the first function called.
 *
 *        The actual macros, that will be used by the user for calling this function, are described 
 *        in crys_aes.h file.
 *
 * @param[in] ContextID_ptr - A pointer to the AES context buffer that is allocated by the user 
 *                            and is used for the AES machine operation.
 * @param[in] IVCounter_ptr - A buffer containing an initial value: IV, Counter or Tweak according 
 *                            to operation mode:
 *                            - on ECB, XCBC, CMAC mode this parameter is not used and may be NULL,
 *                            - on CBC and MAC modes it contains the IV value,
 *                            - on CTR and OFB modes it contains the init counter,
 *                            - on XTS mode it contains the initial tweak value - 128-bit consecutive number 
 *                              of data unit (in little endian).
 * @param[in] Key_ptr  -  A pointer to the user's key buffer.
 * @param[in] KeySize  -  An enum parameter, defines size of used key (128, 192, 256, 512 bits):
 *                        On XCBC mode allowed 128 bit size only, on XTS - 256 or 512 bit, on other modes <= 256 bit.
 * @param[in] EncryptDecryptFlag - A flag specifying whether the AES should perform an Encrypt operation (0) 
 *                                 or a Decrypt operation (1). In XCBC, MAC and CMAC modes it must be Encrypt.
 * @param[in] OperationMode - The operation mode: ECB, CBC, MAC, CTR, OFB, XCBC (PRF and 96), CMAC.
 *
 * @return CRYSError_t - On success the value CRYS_OK is returned, and on failure - a value from crys_aes_error.h
 */
CIMPORT_C CRYSError_t  CRYS_AES_Init(  
	CRYS_AESUserContext_t    *ContextID_ptr,
	CRYS_AES_IvCounter_t     IVCounter_ptr,
	CRYS_AES_Key_t           Key_ptr,
	CRYS_AES_KeySize_t       KeySizeID,
	CRYS_AES_EncryptMode_t   EncryptDecryptFlag,
	CRYS_AES_OperationMode_t OperationMode )
{
	HI_S32 s32Ret;
    AESUserContext_t *pstAESUserContext;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_S stCtrl;
	/* FUNCTION LOGIC */

	/* ............... local initializations .............................. */
	/* -------------------------------------------------------------------- */

	/* ............... checking the parameters validity ................... */
	/* -------------------------------------------------------------------- */

	/* if the users context ID pointer is DX_NULL return an error */
	if( ContextID_ptr == DX_NULL ) 
    {
		return CRYS_AES_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

	/* check if the operation mode is legal */
	if( OperationMode >= CRYS_AES_NumOfModes || OperationMode == CRYS_AES_CCM_mode) 
    {
		return  CRYS_AES_ILLEGAL_OPERATION_MODE_ERROR;
	}

    pstAESUserContext = (AESUserContext_t *)ContextID_ptr;
    memset(pstAESUserContext, 0, sizeof(AESUserContext_t));

	/* check if the mode is supported */
	if((OperationMode != CRYS_AES_ECB_mode) 
        && (OperationMode != CRYS_AES_CBC_mode)
        && (OperationMode != CRYS_AES_OFB_mode)
        && (OperationMode != CRYS_AES_CTR_mode)
        && (OperationMode != CRYS_AES_CMAC_mode))
    {
		return  CRYS_AES_ILLEGAL_OPERATION_MODE_ERROR;
	}

	/* if the operation mode selected is CBC,CTS, MAC, CTR, XTS or OFB then check the validity of
	the IV counter pointer (note: on XTS mode it is the Tweak pointer) */    
	if( ((OperationMode == CRYS_AES_CBC_mode)  ||
	     (OperationMode == CRYS_AES_CTR_mode)  ||
	     (OperationMode == CRYS_AES_MAC_mode)  ||
	     (OperationMode == CRYS_AES_XTS_mode)  ||
	     (OperationMode == CRYS_AES_CBC_CTS_mode)  ||
	     (OperationMode == CRYS_AES_OFB_mode)) &&
	     (IVCounter_ptr == DX_NULL) ) {
		return  CRYS_AES_INVALID_IV_OR_TWEAK_PTR_ERROR;     
	}
	/* in XCBC mode enable only key size = 128 bit */
	if( (OperationMode == CRYS_AES_XCBC_MAC_mode) &&
	   (KeySizeID != CRYS_AES_Key128BitSize) ) {
		return  CRYS_AES_ILLEGAL_KEY_SIZE_ERROR;
	}

	/* check the Encrypt / Decrypt flag validity */
	if ( EncryptDecryptFlag >= CRYS_AES_EncryptNumOfOptions ) {
		return  CRYS_AES_INVALID_ENCRYPT_MODE_ERROR;
	}
	/* in MAC,XCBC,CMAC modes enable only encrypt mode  */
	if( ((OperationMode == CRYS_AES_XCBC_MAC_mode) || 
	     (OperationMode == CRYS_AES_CMAC_mode) || 
	     (OperationMode == CRYS_AES_MAC_mode)) &&  
	   (EncryptDecryptFlag != CRYS_AES_Encrypt) ) {
		return  CRYS_AES_DECRYPTION_NOT_ALLOWED_ON_THIS_MODE;
	}


	/*  check the validity of the key pointer */  
	if ( Key_ptr == DX_NULL ) {
		return  CRYS_AES_INVALID_KEY_POINTER_ERROR;
	}

    memset(&stCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    stCtrl.bKeyByCA = HI_FALSE;
    stCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
    stCtrl.enWorkMode = MakeSepAesMode(OperationMode);
    if (stCtrl.enWorkMode >= HI_UNF_CIPHER_WORK_MODE_BUTT)
    {
        return CRYS_AES_ILLEGAL_OPERATION_MODE_ERROR;
    }
    stCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
    if((stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_ECB) && (IVCounter_ptr != HI_NULL))
    {
        stCtrl.stChangeFlags.bit1IV = 1;  //must set for CBC , CFB mode
        memcpy(stCtrl.u32IV, IVCounter_ptr, CRYS_AES_IV_COUNTER_SIZE_IN_BYTES);
    }
    memcpy(stCtrl.u32Key, Key_ptr, 32);

    if (OperationMode == CRYS_AES_CMAC_mode)
    {
        memset(stCtrl.u32IV, 0, CRYS_AES_IV_COUNTER_SIZE_IN_BYTES);
        stCtrl.stChangeFlags.bit1IV = 1; 
    }
           
	/* check key size in XTS mode  */
	if ( OperationMode == CRYS_AES_XTS_mode ) {
		if( (KeySizeID != CRYS_AES_Key256BitSize) && 
		    (KeySizeID != CRYS_AES_Key512BitSize) ) {
			return  CRYS_AES_ILLEGAL_KEY_SIZE_ERROR;
		}
	} else if ( KeySizeID > CRYS_AES_Key256BitSize ) {
		/* check the max key size for all modes besides XTS */
		return  CRYS_AES_ILLEGAL_KEY_SIZE_ERROR;
	}
		
	/* get AES_Key size in bytes */
	switch( KeySizeID ) {
	case CRYS_AES_Key128BitSize:
		stCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
		break;
		
	case CRYS_AES_Key192BitSize:
		stCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_192BIT; 
		break;
	
	case CRYS_AES_Key256BitSize:
		stCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_256BIT;   
		break;       
	
	default:
		return CRYS_AES_ILLEGAL_KEY_SIZE_ERROR; /*for preventing compiler warnings*/
	}

    pstAESUserContext->OperationMode = OperationMode;
    pstAESUserContext->bIsDecrypt = (EncryptDecryptFlag == CRYS_AES_Decrypt) ? 1 : 0;

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    s32Ret = Cipher_CreateHandle(&pstAESUserContext->hCipher, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
	{   
		return CRYS_FATAL_ERROR;	
	}
    
    s32Ret = Cipher_ConfigHandle(pstAESUserContext->hCipher, &stCtrl);
    if(HI_SUCCESS != s32Ret)
	{
		return SymAdaptor2CrysAesErr(s32Ret, 0);	
	}

    pstAESUserContext->stMMzIn.u32Size = AES_MMZ_BUFF_SIZE;
    pstAESUserContext->stMMzIn.u32StartPhyAddr = new_mmb("AES_DRV", AES_MMZ_BUFF_SIZE, SECURE_MEM, "SEC-MMZ");
    if(pstAESUserContext->stMMzIn.u32StartPhyAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_NEW() for cipher failed\n");
        return CRYS_FATAL_ERROR;
    }
    pstAESUserContext->stMMzIn.u32StartVirAddr = (unsigned int)remap_mmb(pstAESUserContext->stMMzIn.u32StartPhyAddr);
    if(pstAESUserContext->stMMzIn.u32StartVirAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_MAP() for cipher failed, PhyAddr=0x%x\n", pstAESUserContext->stMMzIn.u32StartPhyAddr);
        (HI_VOID)delete_mmb(pstAESUserContext->stMMzIn.u32StartPhyAddr);
        return HI_ERR_CIPHER_FAILED_INIT;
    }
    memset((void*)(pstAESUserContext->stMMzIn.u32StartVirAddr), 0, AES_MMZ_BUFF_SIZE);

    pstAESUserContext->stMMzOut.u32Size = AES_MMZ_BUFF_SIZE;
    pstAESUserContext->stMMzOut.u32StartPhyAddr = new_mmb("AES_DRV", AES_MMZ_BUFF_SIZE, SECURE_MEM, "SEC-MMZ");
    if(pstAESUserContext->stMMzOut.u32StartPhyAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_NEW() for cipher failed\n");
        return CRYS_FATAL_ERROR;
    }
    pstAESUserContext->stMMzOut.u32StartVirAddr = (unsigned int)remap_mmb(pstAESUserContext->stMMzOut.u32StartPhyAddr);
    if(pstAESUserContext->stMMzOut.u32StartVirAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_MAP() for cipher failed, PhyAddr=0x%x\n", pstAESUserContext->stMMzOut.u32StartPhyAddr);
        (HI_VOID)delete_mmb(pstAESUserContext->stMMzOut.u32StartPhyAddr);
        return HI_ERR_CIPHER_FAILED_INIT;
    }
    memset((void*)(pstAESUserContext->stMMzOut.u32StartVirAddr), 0, AES_MMZ_BUFF_SIZE);
	return DX_CRYS_RETURN_ERROR(s32Ret, 0, SymAdaptor2CrysAesErr);
}

/****************************************************************************************************/
/** 
 * @brief This function is used to operate a block of data on the SW or on AES machine.
 *        This function should be called after the appropriate CRYS AES init function 
 *        (according to used AES operation mode).
 *
 * @param[in] ContextID_ptr - A pointer to the AES context buffer allocated by the user that
 *                            is used for the AES machine operation. This should be the same context that was
 *                            used on the previous call of this session.
 *
 * @param[in] DataIn_ptr - A pointer to the buffer of the input data to the AES. The pointer does 
 *                         not need to be aligned. On CSI input mode the pointer must be equal to
 *                         value (0xFFFFFFFC | DataInAlignment). 
 *
 * @param[in] DataInSize - A size of the input data must be multiple of 16 bytes and not 0, 
 *                         on all modes. Note last chunk (block) of data must be processed by 
 *                         CRYS_AES_Finish function but not by CRYS_AES_Block function;  
 *
 * @param[out] DataOut_ptr - A pointer to the buffer of the output data from the AES. The pointer  does not 
 *                             need to be aligned. On CSI output mode the pointer must be equal to
 *                             value (0xFFFFFFFC | DataOutAlignment). On all MAC modes (MAC,XCBC, CMAC) CSI 
 *                             output is not allowed.
 *
 * @return CRYSError_t - On success CRYS_OK is returned, on failure a
 *                       value MODULE_* CRYS_DES_error.h
 *
 *     NOTES: 1. Temporarily it is not allowed, that both the Input and the Output simultaneously 
 *               were on CSI mode.
 *            2. Temporarily the CSI input or output are not allowed on XCBC, CMAC and XTS modes.    
 */
CIMPORT_C CRYSError_t  CRYS_AES_Block( CRYS_AESUserContext_t   *ContextID_ptr,   
                                       DxUint8_t               *DataIn_ptr,     
                                       DxUint32_t              DataInSize,     
                                       DxUint8_t               *DataOut_ptr )
{
	HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32CopySize = 0;
    HI_U32 u32TotalCopySize = 0;
    AESUserContext_t *pstAESUserContext;
    
	/* if the users context ID pointer is DX_NULL return an error */
	if ( ContextID_ptr == DX_NULL ) 
    {
		 return CRYS_AES_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

	/* if the users Data In pointer is illegal return an error */
	if ( (DataIn_ptr == DX_NULL) || (DataOut_ptr == DX_NULL)) 
    {
		return CRYS_AES_DATA_IN_POINTER_INVALID_ERROR;
	}

    pstAESUserContext = (AESUserContext_t *)ContextID_ptr;

	if( ((pstAESUserContext->OperationMode == CRYS_AES_ECB_mode)  ||
	     (pstAESUserContext->OperationMode == CRYS_AES_CBC_mode) ) &&
	     (DataInSize % CRYS_AES_BLOCK_SIZE_IN_BYTES) != 0) {
		return  CRYS_AES_DATA_IN_SIZE_ILLEGAL;     
	}

    if (DataInSize > 0)
    {
        pstAESUserContext->u32BloctCnt++;
    }
    while(u32TotalCopySize < DataInSize)
    {
        if ((DataInSize - u32TotalCopySize) > AES_MMZ_BUFF_SIZE)
        {
            u32CopySize = AES_MMZ_BUFF_SIZE;
        }
        else
        {
            u32CopySize = DataInSize - u32TotalCopySize; 
            memset((HI_U8*)pstAESUserContext->stMMzIn.u32StartVirAddr, 0, AES_MMZ_BUFF_SIZE);
        }
        memcpy((HI_U8*)pstAESUserContext->stMMzIn.u32StartVirAddr, DataIn_ptr+u32TotalCopySize, u32CopySize);
		
        if (pstAESUserContext->bIsDecrypt)
        {
            s32Ret = Cipher_Decrypt(pstAESUserContext->hCipher, pstAESUserContext->stMMzIn.u32StartPhyAddr, 
                pstAESUserContext->stMMzOut.u32StartPhyAddr, (u32CopySize+15)&(~0x0F));
            if(HI_SUCCESS != s32Ret)
        	{
        		HI_ERR_CIPHER("Cipher encrypt failed.\n");
            }
        }
        else
        {
            s32Ret = Cipher_Encrypt(pstAESUserContext->hCipher, pstAESUserContext->stMMzIn.u32StartPhyAddr, 
                pstAESUserContext->stMMzOut.u32StartPhyAddr, (u32CopySize+15)&(~0x0F));
            if(HI_SUCCESS != s32Ret)
        	{
        		HI_ERR_CIPHER("Cipher encrypt failed.\n");
            }
        }

        if(pstAESUserContext->OperationMode == CRYS_AES_CMAC_mode)
        {
             memcpy(DataOut_ptr, (HI_U8*)pstAESUserContext->stMMzOut.u32StartVirAddr + (u32CopySize - CRYS_AES_BLOCK_SIZE_IN_BYTES), 
                CRYS_AES_BLOCK_SIZE_IN_BYTES); 
        }
        else
        {
            memcpy(DataOut_ptr+u32TotalCopySize, (HI_U8*)pstAESUserContext->stMMzOut.u32StartVirAddr, u32CopySize);
        }
        memcpy(pstAESUserContext->auLastBlock, (HI_U8*)pstAESUserContext->stMMzOut.u32StartVirAddr + (((u32CopySize+15)&(~0x0F)) - CRYS_AES_BLOCK_SIZE_IN_BYTES), 
                CRYS_AES_BLOCK_SIZE_IN_BYTES);
        u32TotalCopySize+=u32CopySize;
    }

//    HI_PRINT_HEX("IN", DataIn_ptr, DataInSize);
//    HI_PRINT_HEX("OUT", DataOut_ptr, 16);

	return DX_CRYS_RETURN_ERROR(s32Ret, 0, SymAdaptor2CrysAesErr);
}
                 
/****************************************************************************************************/
/** 
 * @brief This function is used as finish operation on all AES modes.
 *
 *        The function must be called after AES_Block operations (or instead) for last chunck 
 *        of data with size > 0. 
 *
 *        The function performs all operations, including specific operations for last blocks of 
 *        data on some modes (XCBC, CMAC, MAC) and puts out the result. After all operations 
 *        the function cleans the secure sensitive data from context.  
 *        
 *        1. Checks the validation of all of the inputs of the function.
 *           If one of the received parameters is not valid it shall return an error.
 *        2. Decrypts the received context to the working context  by calling the 
 *           CRYS_CCM_GetContext function.
 *        3. Calls the LLF_AES_Finish function.
 *        4. Outputs the result and cleans working context.
 *        5. Exits   
 *      
 *
 * @param[in] ContextID_ptr - A pointer to the AES context buffer allocated by the user that
 *                            should be the same context that was used on the previous call
 *                            of this session.
 * @param[in] DataIn_ptr    - A pointer to the buffer of the input data to the AES. The pointer does 
 *                            not need to be aligned. On CSI input mode the pointer must be equal to
 *                            value (0xFFFFFFFC | DataInAlignment). 
 * @param[in] DataInSize    - A size of the input data must be:  DataInSize >= minimalSize, where: 
 *                            minimalSize =
 *                                  -  1 byte for CTR, OFB, XCBC, CMAC mode;
 *                                  - 16 bytes for other modes. 
 * @param[out] DataOut_ptr  - A pointer to the output buffer. The pointer  does not need to be aligned. 
 *                            On CSI output mode the pointer must be equal to value 
 *                            (0xFFFFFFFC | DataOutAlignment). On some modes (MAC,XCBC,CMAC,XTS) 
 *                            CSI output is not allowed. Temporarily is not allowed, that both the 
 *                            Input and the output are on CSI mode simultaneously. 
 *                            The size of the output buffer must be not less than:  
 *                                - 16 bytes for MAC, XCBC, CMAC modes;
 *                                - DataInSize for ECB,CBC,CTR,XTS,OFB modes. 
 *
 * @return CRYSError_t    - On success CRYS_OK is returned, on failure - a value defined in crys_aes_error.h.
 *
 */
CIMPORT_C CRYSError_t  CRYS_AES_Finish( CRYS_AESUserContext_t   *ContextID_ptr,  
                                        DxUint8_t               *DataIn_ptr,     
                                        DxUint32_t               DataInSize,     
                                        DxUint8_t               *DataOut_ptr )
{
	HI_S32 s32Ret;
    CRYSError_t err;
    AESUserContext_t *pstAESUserContext;
    HI_U8 u8LastBlock[CRYS_AES_BLOCK_SIZE_IN_BYTES];
    HI_U8 u8Y[CRYS_AES_BLOCK_SIZE_IN_BYTES];
    HI_U8 u8CmacK1[CRYS_AES_BLOCK_SIZE_IN_BYTES], u8CmacK2[CRYS_AES_BLOCK_SIZE_IN_BYTES];
    HI_U32 u32LastBlockSize = 0;
	/* if the users context ID pointer is DX_NULL return an error */
	if ( ContextID_ptr == DX_NULL ) 
    {
		 return CRYS_AES_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

	/* if the users Data In pointer is illegal return an error */
	if ( DataIn_ptr == DX_NULL ) 
    {
		return CRYS_AES_DATA_IN_POINTER_INVALID_ERROR;
	}
    
    pstAESUserContext = (AESUserContext_t *)ContextID_ptr;
    
	if ((DataInSize % CRYS_AES_BLOCK_SIZE_IN_BYTES != 0) &&
	    ((pstAESUserContext->OperationMode == CRYS_AES_ECB_mode) || 
	     (pstAESUserContext->OperationMode == CRYS_AES_CBC_mode) )) {
		return CRYS_AES_DATA_IN_SIZE_ILLEGAL; 
	}
    
    /*Check, that in case of CTS mode data size is not less than CRYS_AES_BLOCK_SIZE_IN_BYTES */
	if ((DataInSize < CRYS_AES_BLOCK_SIZE_IN_BYTES)&&
	    (pstAESUserContext->OperationMode == CRYS_AES_CBC_CTS_mode)) {
		return CRYS_AES_DATA_IN_SIZE_ILLEGAL; 
	}

	if(pstAESUserContext->OperationMode == CRYS_AES_CMAC_mode)
	{
	    memset(u8LastBlock, 0, CRYS_AES_BLOCK_SIZE_IN_BYTES);
        u32LastBlockSize = DataInSize % CRYS_AES_BLOCK_SIZE_IN_BYTES;
        if (DataInSize > 0)
        {
            if (u32LastBlockSize == 0)
            {
                u32LastBlockSize = 16; 
            }
            memcpy(u8LastBlock, DataIn_ptr + (DataInSize - u32LastBlockSize), u32LastBlockSize);
            DataInSize -= u32LastBlockSize;
        }
    }

    if (DataInSize > 0)
    {
        err = CRYS_AES_Block(ContextID_ptr, DataIn_ptr, DataInSize, DataOut_ptr);
        if(CRYS_OK != err)
    	{
    		HI_ERR_CIPHER("CRYS_AES_Block.\n");
            return err;
        }
    }

//    HI_PRINT_HEX ("LAST_BLOCK", pstAESUserContext->auLastBlock, CRYS_AES_BLOCK_SIZE_IN_BYTES);

    if(pstAESUserContext->OperationMode == CRYS_AES_CMAC_mode)
	{           
	    memcpy(u8Y, pstAESUserContext->auLastBlock, CRYS_AES_BLOCK_SIZE_IN_BYTES);
        err = cmac_generate_subkey(ContextID_ptr, u8CmacK1, u8CmacK2);
        if(CRYS_OK != err)
    	{
    		HI_ERR_CIPHER("CRYS_AES_Block.\n");
            return err;
        } 
        if ( u32LastBlockSize == 16 )  /* last block is complete block */
        {
            xor_128(u8LastBlock, u8CmacK1, u8LastBlock);
        }
        else
        {
            padding(u8LastBlock, u8LastBlock, u32LastBlockSize);
            xor_128(u8LastBlock, u8CmacK2, u8LastBlock);
        }
 //       HI_PRINT_HEX ("IV", u8Y, 16);
        err = CRYS_AES_SetIv(ContextID_ptr, u8Y);
        if(CRYS_OK != err)
    	{
    		HI_ERR_CIPHER("CRYS_AES_SetIv failed.\n");
            return err;
        }
        
        err = CRYS_AES_Block(ContextID_ptr, u8LastBlock, CRYS_AES_BLOCK_SIZE_IN_BYTES, DataOut_ptr);
        if(CRYS_OK != err)
    	{
    		HI_ERR_CIPHER("CRYS_AES_Block.\n");
            return err;
        }
    }
    
    s32Ret = Cipher_DestroyHandle(pstAESUserContext->hCipher);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
    }

    if(pstAESUserContext->stMMzIn.u32StartVirAddr != 0)
    {
        (void)unmap_mmb((void*)pstAESUserContext->stMMzIn.u32StartVirAddr);
    }
    if(pstAESUserContext->stMMzIn.u32StartPhyAddr != 0)
    {
        (void)delete_mmb(pstAESUserContext->stMMzIn.u32StartPhyAddr);
    }

    if(pstAESUserContext->stMMzOut.u32StartVirAddr != 0)
    {
        (void)unmap_mmb((void*)pstAESUserContext->stMMzOut.u32StartVirAddr);
    }
    if(pstAESUserContext->stMMzOut.u32StartPhyAddr != 0)
    {
        (void)delete_mmb(pstAESUserContext->stMMzOut.u32StartPhyAddr);
    }

	return DX_CRYS_RETURN_ERROR(s32Ret, 0, SymAdaptor2CrysAesErr);
}

/****************************************************************************************************/
/**
 * @brief This function is used to perform the AES operation in one integrated process.
 *
 *        The input-output parameters of the function are the following:
 *
 * @param[in] IVCounter_ptr - A buffer containing an initial value: IV, Counter or Tweak according 
 *                            to operation mode:
 *                            - on ECB, XCBC, CMAC mode this parameter is not used and may be NULL,
 *                            - on CBC and MAC modes it contains the IV value,
 *                            - on CTR and OFB modes it contains the init counter,
 *                            - on XTS mode it contains the initial tweak value - 128-bit consecutive number 
 *                              of data unit (in little endian).
 * @param[in] Key_ptr  -  A pointer to the user's key buffer.
 * @param[in] KeySize  -  An enum parameter, defines size of used key (128, 192, 256 bits).
 * @param[in] EncryptDecryptFlag - A flag specifying whether the AES should perform an Encrypt operation (0) 
 *                                 or a Decrypt operation (1). In XCBC and CMAC modes it must be 0.
 * @param[in] OperationMode - The operation mode: ECB, CBC, MAC, CTR, XCBC (PRF and 96), CMAC, XTS, OFB.
 * @param[in] DataIn_ptr - A pointer to the buffer of the input data to the AES.
 *
 * @param[in] DataInSize - The size of the input data, it must be:
 *                         - on ECB,CBC,MAC modes must be a multiple of 16 bytes
 *                         - on CTR, XCBC, CMAC and OFB modes any value
 *      		   - on XTS mode: If input or output pointers are in the D-Cache range,
 *      		     only the following data sizes are supported: 64B, 512B, 520B, 521B. Otherwise,
 *      		     1024B and 4096B are also supported.
 * @param[out] DataOut_ptr - A pointer to the buffer of the output data from the AES
 *
 * @return CRYSError_t - On success CRYS_OK is returned, on failure a value defined in crys_aes_error.h
 *
 */
CIMPORT_C CRYSError_t  CRYS_AES(CRYS_AES_IvCounter_t       IVCounter_ptr,       
				CRYS_AES_Key_t             Key_ptr,								
				CRYS_AES_KeySize_t         KeySize,            
				CRYS_AES_EncryptMode_t     EncryptDecryptFlag, 
				CRYS_AES_OperationMode_t   OperationMode,
				DxUint8_t                  *DataIn_ptr,        
				DxUint32_t                 DataInSize,         
				DxUint8_t                  *DataOut_ptr)
{
	CRYS_AESUserContext_t UserContext;
	CRYSError_t Error = CRYS_OK;

	/* check, that data size is multiple of 16 bytes on relevant modes */
	if (((DataInSize % CRYS_AES_BLOCK_SIZE_IN_BYTES) != 0) &&
	    ((OperationMode == CRYS_AES_ECB_mode) ||
	     (OperationMode == CRYS_AES_CBC_mode) ||
	     (OperationMode == CRYS_AES_MAC_mode))) {
		return CRYS_AES_DATA_IN_SIZE_ILLEGAL;
	}

	
	/* check the minimum data size according to mode */
	if ((OperationMode == CRYS_AES_XTS_mode) && (DataInSize < 2*CRYS_AES_BLOCK_SIZE_IN_BYTES)) {
			return CRYS_AES_DATA_IN_SIZE_ILLEGAL;
	}
	/* in CMAC mode it may be applet key and we want to build it*/
	if (OperationMode == CRYS_AES_CMAC_mode)
    {

			
	}
    
	Error = CRYS_AES_Init(&UserContext, IVCounter_ptr, Key_ptr, KeySize, EncryptDecryptFlag, OperationMode);
	if(Error != CRYS_OK) {
		goto end;
	}

		Error = CRYS_AES_Finish(&UserContext, DataIn_ptr, DataInSize, DataOut_ptr);

end:
	return Error;
}

/**************************************************************************
 *	              CRYS_AES_SetIv function                                *
 **************************************************************************/
/**
   @brief  The CRYS_AES_SetIv function puts a new initial vector into
   an existing context.

   Inputs:  New IV vector
  
   Outputs: Result
   
   @param[in/out] ContextID_ptr - A pointer to the AES context buffer that is allocated by the user 
                                  and is used for the AES machine operation.
			   
   @return CRYSError_t - CRYS_OK, or error message 
			 CRYS_AES_INVALID_USER_CONTEXT_POINTER_ERROR          
			 
*/                               
CIMPORT_C  CRYSError_t CRYS_AES_SetIv(CRYS_AESUserContext_t   *ContextID_ptr,  
		                       DxUint8_t *iv_ptr)
{
    HI_S32 s32Ret;
    AESUserContext_t *pstAESUserContext;
    HI_UNF_CIPHER_CTRL_S stCtrl;

   /* if the users context ID pointer is DX_NULL return an error */
	if ( ContextID_ptr == DX_NULL ) 
    {
		 return CRYS_AES_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

    pstAESUserContext = (AESUserContext_t *)ContextID_ptr;
    s32Ret = Cipher_GetHandleConfig(pstAESUserContext->hCipher, &stCtrl);
    if(HI_SUCCESS != s32Ret)
	{
		HI_ERR_CIPHER("Cipher Get Handle Config failed.\n");
        return SymAdaptor2CrysAesErr(s32Ret, 0);
    }
/*
    HI_PRINT("CRYS_AES_SetIv() - enWorkMode: 0x%x\n", stCtrl.enWorkMode);    
    HI_PRINT("CRYS_AES_SetIv() - enAlg     : 0x%x\n", stCtrl.enAlg);    
    HI_PRINT("CRYS_AES_SetIv() - enKeyLen  : 0x%x\n", stCtrl.enKeyLen);    
    HI_PRINT("CRYS_AES_SetIv() - enBitWidth: 0x%x\n", stCtrl.enBitWidth);    
    HI_PRINT("CRYS_AES_SetIv() - enCaType  : 0x%x\n", stCtrl.enCaType);
*/	
	if ((stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CBC) &&
	(stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CTR) &&
	(stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CBC_CTS) &&
	(stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_OFB) ) {
		return CRYS_AES_ILLEGAL_OPERATION_MODE_ERROR;
	}
	
	if (iv_ptr == DX_NULL)
    {
		return CRYS_AES_INVALID_IV_OR_TWEAK_PTR_ERROR;
	}

    stCtrl.stChangeFlags.bit1IV = 1;  //must set for CBC , CFB mode
    memcpy(stCtrl.u32IV, iv_ptr, CRYS_AES_IV_COUNTER_SIZE_IN_BYTES);

    s32Ret = Cipher_ConfigHandle(pstAESUserContext->hCipher, &stCtrl);
    if(HI_SUCCESS != s32Ret)
	{
		return SymAdaptor2CrysAesErr(s32Ret, 0);	
	}
	
	return CRYS_OK;
}


/**************************************************************************
 *	              CRYS_AES_GetIv function                                *
 **************************************************************************/
/**
   @brief  The CRYS_AES_GetIv function retrieves the initial vector from
   the context.

   Inputs:  IV vector buffer
  
   Outputs: Result
   
   @param[in/out] ContextID_ptr - A pointer to the AES context buffer that is allocated by the user 
                                  and is used for the AES machine operation.
			   
   @return CRYSError_t - CRYS_OK, or error message 
			 CRYS_AES_INVALID_USER_CONTEXT_POINTER_ERROR          
			 
*/                               
CIMPORT_C CRYSError_t CRYS_AES_GetIv(CRYS_AESUserContext_t   *ContextID_ptr,  
		                       DxUint8_t *iv_ptr)
{
    HI_S32 s32Ret;
    AESUserContext_t *pstAESUserContext;
    HI_UNF_CIPHER_CTRL_S stCtrl;

   /* if the users context ID pointer is DX_NULL return an error */
	if ( ContextID_ptr == DX_NULL ) 
    {
		 return CRYS_AES_INVALID_USER_CONTEXT_POINTER_ERROR;
	}

    pstAESUserContext = (AESUserContext_t *)ContextID_ptr;
    s32Ret = Cipher_GetHandleConfig(pstAESUserContext->hCipher, &stCtrl);
    if(HI_SUCCESS != s32Ret)
	{
		HI_ERR_CIPHER("Cipher Get Handle Config failed.\n");
        return SymAdaptor2CrysAesErr(s32Ret, 0);
    }
	
	if ((stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CBC) &&
	(stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CTR) &&
	(stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_CBC_CTS) &&
	(stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_OFB) ) {
		return CRYS_AES_ILLEGAL_OPERATION_MODE_ERROR;
	}

	if (iv_ptr == DX_NULL)
    {
		return CRYS_AES_INVALID_IV_OR_TWEAK_PTR_ERROR;
	}

    s32Ret = Cipher_GetIVOut(pstAESUserContext->hCipher, iv_ptr);

	return SymAdaptor2CrysAesErr(s32Ret, 0);
}

#ifdef HI_CIPHER_TEST
//Only for test
void aes_test1(void)
{
    CRYSError_t  err;
    CRYS_AESUserContext_t    ContextID_ptr;
    DxUint8_t     au8Data[16] = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
    CRYS_AES_Key_t au8Key     = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    DxUint8_t        au8T[16] = {0x07, 0x0a, 0x16, 0xb4, 0x6b, 0x4d, 0x41, 0x44, 0xf7, 0x9b, 0xdd, 0x9d, 0xd0, 0x4a, 0x28, 0x7c};
    DxUint8_t       au8OT[16] = {0};

    err = CRYS_AES_Init(&ContextID_ptr, HI_NULL, au8Key, CRYS_AES_Key128BitSize, CRYS_AES_Encrypt, CRYS_AES_CMAC_mode);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    err = CRYS_AES_Finish(&ContextID_ptr, au8Data, sizeof(au8Data), au8OT);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("CBC-MAC", au8OT, 16);
    if (memcmp(au8OT, au8T, 16) != 0)
    {
		HI_ERR_CIPHER ("CBC-MAC failed\n");	
        return;
	}
}

void aes_test2(void)
{
    CRYSError_t  err;
    CRYS_AESUserContext_t    ContextID_ptr;
    DxUint8_t     au8Data[1] = {0x00};
    CRYS_AES_Key_t au8Key     = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    DxUint8_t        au8T[16] = {0xbb, 0x1d, 0x69, 0x29, 0xe9, 0x59, 0x37, 0x28, 0x7f, 0xa3, 0x7d, 0x12, 0x9b, 0x75, 0x67, 0x46};
    DxUint8_t       au8OT[16] = {0};

    err = CRYS_AES_Init(&ContextID_ptr, HI_NULL, au8Key, CRYS_AES_Key128BitSize, CRYS_AES_Encrypt, CRYS_AES_CMAC_mode);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    err = CRYS_AES_Finish(&ContextID_ptr, au8Data, 0, au8OT);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("CBC-MAC", au8OT, 16);
    if (memcmp(au8OT, au8T, 16) != 0)
    {
		HI_ERR_CIPHER ("CBC-MAC failed\n");	
        return;
	}
}

void aes_test3(void)
{
    CRYSError_t  err;
    CRYS_AESUserContext_t    ContextID_ptr;
    DxUint8_t     au8Data[40] = 
    {
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a, 
        0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51, 
        0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11
    };
    CRYS_AES_Key_t au8Key     = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    DxUint8_t        au8T[16] = {0xdf, 0xa6, 0x67, 0x47, 0xde, 0x9a, 0xe6, 0x30, 0x30, 0xca, 0x32, 0x61, 0x14, 0x97, 0xc8, 0x27};
    DxUint8_t       au8OT[16] = {0};

    err = CRYS_AES_Init(&ContextID_ptr, HI_NULL, au8Key, CRYS_AES_Key128BitSize, CRYS_AES_Encrypt, CRYS_AES_CMAC_mode);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    err = CRYS_AES_Block(&ContextID_ptr, au8Data, 32, au8OT);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    err = CRYS_AES_Finish(&ContextID_ptr, &au8Data[32], 8, au8OT);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("CBC-MAC", au8OT, 16);
    if (memcmp(au8OT, au8T, 16) != 0)
    {
		HI_ERR_CIPHER ("CBC-MAC failed\n");	
        return;
	}
}

void aes_test4(void)
{
    CRYSError_t  err;
    DxUint8_t        auIV[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
    DxUint8_t     au8Data[16] = {0x6B,0xC1,0xBE,0xE2,0x2E,0x40,0x9F,0x96,0xE9,0x3D,0x7E,0x11,0x73,0x93,0x17,0x2A};
    CRYS_AES_Key_t au8Key     = {0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C};
    DxUint8_t     au8Dest[16] = {0x76,0x49,0xAB,0xAC,0x81,0x19,0xB2,0x46,0xCE,0xE9,0x8E,0x9B,0x12,0xE9,0x19,0x7D};
    DxUint8_t       au8OT[16] = {0};

    err = CRYS_AES(auIV, au8Key, CRYS_AES_Key128BitSize, CRYS_AES_Encrypt, CRYS_AES_CBC_mode, au8Data, sizeof(au8Data), au8OT);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("CBC-ENC", au8OT, 16);
    if (memcmp(au8OT, au8Dest, 16) != 0)
    {
		HI_ERR_CIPHER ("CBC-MAC failed\n");	
        return;
	}
    err = CRYS_AES(auIV, au8Key, CRYS_AES_Key128BitSize, CRYS_AES_Decrypt, CRYS_AES_CBC_mode, au8OT, sizeof(au8Data), au8OT);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_AES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("CBC-DEC", au8OT, 16);
    if (memcmp(au8OT, au8Data, 16) != 0)
    {
		HI_ERR_CIPHER ("CBC-MAC failed\n");	
        return;
	}
}

void aes_test(void)
{
    aes_test1();
    aes_test2();
    aes_test3();
    aes_test4();
}
#endif
