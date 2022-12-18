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
#include "crys_des.h"
#include "crys_des_error.h"
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

#define DES_MMZ_BUFF_SIZE  (0x2000)

typedef struct hiDESUserContext_t
{
    HI_HANDLE hCipher;
    HI_BOOL   bIsDecrypt;
    CRYS_DES_OperationMode_t OperationMode;
    HI_U8    auLastBlock[CRYS_AES_BLOCK_SIZE_IN_BYTES];
    HI_U32   u32BloctCnt;
    MMZ_BUFFER_S stMMzIn;
    MMZ_BUFFER_S stMMzOut;
}DESUserContext_t;

/*!
 * Converts Symmetric Adaptor return code to CRYS error code.
 * 
 * \param symRetCode Symmetric Adaptor return error.
 * \param errorInfo Ignored.
 *  
 * \return CRYSError_t one of CRYS_* error codes defined in crys_error.h
 */
static CRYSError_t SymAdaptor2CrysDesErr(int symRetCode, DxUint32_t errorInfo)
{
    CRYSError_t err;
    
	switch (symRetCode) {
	case HI_ERR_CIPHER_NOT_INIT:
		err = CRYS_DES_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_FAILED_INIT:
        err = CRYS_DES_IS_NOT_SUPPORTED;
        break;
	case HI_ERR_CIPHER_INVALID_POINT:
		err =  CRYS_DES_DATA_IN_POINTER_INVALID_ERROR;
        break;
	case HI_ERR_CIPHER_INVALID_PARA:
        err = CRYS_DES_ILLEGAL_PARAMS_ERROR;
        break;
	case HI_ERR_CIPHER_FAILED_GETHANDLE:
		err =  CRYS_OUT_OF_RESOURCE_ERROR;
        break;
	case HI_ERR_CIPHER_FAILED_CONFIGAES:
		err = CRYS_DES_ILLEGAL_PARAMS_ERROR;
        break;
	case HI_ERR_CIPHER_FAILED_CONFIGDES:
		err = CRYS_DES_ILLEGAL_PARAMS_ERROR;
        break;
	case HI_ERR_CIPHER_BUSY:
	case HI_ERR_CIPHER_NO_AVAILABLE_RNG:
        err = CRYS_DES_IS_NOT_SUPPORTED;
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

static HI_UNF_CIPHER_WORK_MODE_E MakeSepDesMode(CRYS_DES_OperationMode_t OperationMode)
{
	HI_UNF_CIPHER_WORK_MODE_E result;

	switch(OperationMode) {
	case CRYS_DES_ECB_mode:
		result = HI_UNF_CIPHER_WORK_MODE_ECB;
		break;
	case CRYS_DES_CBC_mode:
		result = HI_UNF_CIPHER_WORK_MODE_CBC;
		break;
	default:
		result = HI_UNF_CIPHER_WORK_MODE_BUTT;
	}

	return result;
}


/**
 * @brief This function is used to initialize the DES machine.
 *        To operate the DES machine, this should be the first function called.
 *
 * @param[in] ContextID_ptr  - A pointer to the DES context buffer allocated by the user 
 *                       that is used for the DES machine operation.
 *
 * @param[in,out] IV_ptr - The buffer of the IV.
 *                          In ECB mode this parameter is not used.
 *                          In CBC this parameter should contain the IV values.
 *
 * @param[in] Key_ptr - A pointer to the user's key buffer.
 *
 * @param[in] NumOfKeys - The number of keys used: 1, 2, or 3 (defined in the enum).
 *
 * @param[in] EncryptDecryptFlag - A flag that determines whether the DES should perform 
 *                           an Encrypt operation (0) or a Decrypt operation (1).
 *
 * @param[in] OperationMode - The operation mode: ECB or CBC.
 *
 *
 * @return CRYSError_t - On success the value CRYS_OK is returned, 
 *                        and on failure a value from crys_error.h
 */

CIMPORT_C CRYSError_t  CRYS_DES_Init( CRYS_DESUserContext_t *ContextID_ptr,
				  CRYS_DES_Iv_t            IV_ptr,
				  CRYS_DES_Key_t           *Key_ptr,
				  CRYS_DES_NumOfKeys_t     NumOfKeys,
				  CRYS_DES_EncryptMode_t   EncryptDecryptFlag,
				  CRYS_DES_OperationMode_t OperationMode )
{
	HI_S32 s32Ret;
    DESUserContext_t *pstDESUserContext;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;
    HI_UNF_CIPHER_CTRL_S stCtrl;

	/* ............... checking the parameters validity ................... */
	/* -------------------------------------------------------------------- */
	
	/* if the users context ID pointer is DX_NULL return an error */
	if( ContextID_ptr == DX_NULL ) {
		return CRYS_DES_INVALID_USER_CONTEXT_POINTER_ERROR;
	}
	  
	/* check if the operation mode is legal */
	if( OperationMode >= CRYS_DES_NumOfModes ) {
		return CRYS_DES_ILLEGAL_OPERATION_MODE_ERROR;
	}
	  
	/* if the operation mode selected is CBC then check the validity of
	  the IV counter pointer */    
	if( (OperationMode == CRYS_DES_CBC_mode) && (IV_ptr == DX_NULL) ) {
		return CRYS_DES_INVALID_IV_PTR_ON_NON_ECB_MODE_ERROR;
	}
	  
	/* If the number of keys in invalid return an error */
	if( (NumOfKeys >= CRYS_DES_NumOfKeysOptions) || (NumOfKeys == 0) ) {
		return CRYS_DES_ILLEGAL_NUM_OF_KEYS_ERROR;
	}
	 
	/*check the valisity of the key pointer */
	if( Key_ptr == DX_NULL ) {
		return CRYS_DES_INVALID_KEY_POINTER_ERROR;
	}
	  
	/* Check the Encrypt / Decrypt flag validity */
	if( EncryptDecryptFlag >= CRYS_DES_EncryptNumOfOptions ) {
		return CRYS_DES_INVALID_ENCRYPT_MODE_ERROR;
	}

    pstDESUserContext = (DESUserContext_t *)ContextID_ptr;
    memset(&stCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    stCtrl.bKeyByCA = HI_FALSE;
    if (NumOfKeys == CRYS_DES_1_KeyInUse)
    {
        stCtrl.enAlg = HI_UNF_CIPHER_ALG_DES;
    }
    else if (NumOfKeys == CRYS_DES_2_KeysInUse)
    {
        stCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
        stCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
    }
    else if (NumOfKeys == CRYS_DES_3_KeysInUse)
    {
        stCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
        stCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_3KEY;
    } 
    stCtrl.enWorkMode = MakeSepDesMode(OperationMode);
    if (stCtrl.enWorkMode >= HI_UNF_CIPHER_WORK_MODE_BUTT)
    {
        return CRYS_DES_ILLEGAL_OPERATION_MODE_ERROR;
    }
    stCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
    if((stCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_ECB) && (IV_ptr != HI_NULL))
    {
        stCtrl.stChangeFlags.bit1IV = 1;  //must set for CBC , CFB mode
        memcpy(stCtrl.u32IV, IV_ptr, CRYS_AES_IV_COUNTER_SIZE_IN_BYTES);
    }
    memcpy(stCtrl.u32Key, Key_ptr, 32);

    pstDESUserContext->OperationMode = OperationMode;
    pstDESUserContext->bIsDecrypt = (EncryptDecryptFlag == CRYS_DES_Decrypt) ? 1 : 0;

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    s32Ret = Cipher_CreateHandle(&pstDESUserContext->hCipher, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
	{   
		return CRYS_FATAL_ERROR;	
	}
    
    s32Ret = Cipher_ConfigHandle(pstDESUserContext->hCipher, &stCtrl);
    if(HI_SUCCESS != s32Ret)
	{
		return SymAdaptor2CrysDesErr(s32Ret, 0);	
	}

    pstDESUserContext->stMMzIn.u32Size = DES_MMZ_BUFF_SIZE;
    pstDESUserContext->stMMzIn.u32StartPhyAddr = new_mmb("DES_DRV", DES_MMZ_BUFF_SIZE, SECURE_MEM, "SEC-MMZ");
    if(pstDESUserContext->stMMzIn.u32StartPhyAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_NEW() for cipher failed\n");
        return CRYS_FATAL_ERROR;
    }
    pstDESUserContext->stMMzIn.u32StartVirAddr = (unsigned int)remap_mmb(pstDESUserContext->stMMzIn.u32StartPhyAddr);
    if(pstDESUserContext->stMMzIn.u32StartVirAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_MAP() for cipher failed, PhyAddr=0x%x\n", pstDESUserContext->stMMzIn.u32StartPhyAddr);
        (HI_VOID)delete_mmb(pstDESUserContext->stMMzIn.u32StartPhyAddr);
        return HI_ERR_CIPHER_FAILED_INIT;
    }
    memset((void*)(pstDESUserContext->stMMzIn.u32StartVirAddr), 0, DES_MMZ_BUFF_SIZE);

    pstDESUserContext->stMMzOut.u32Size = DES_MMZ_BUFF_SIZE;
    pstDESUserContext->stMMzOut.u32StartPhyAddr = new_mmb("DES_DRV", DES_MMZ_BUFF_SIZE, SECURE_MEM, "SEC-MMZ");
    if(pstDESUserContext->stMMzOut.u32StartPhyAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_NEW() for cipher failed\n");
        return CRYS_FATAL_ERROR;
    }
    pstDESUserContext->stMMzOut.u32StartVirAddr = (unsigned int)remap_mmb(pstDESUserContext->stMMzOut.u32StartPhyAddr);
    if(pstDESUserContext->stMMzOut.u32StartVirAddr == 0)
    {
        HI_ERR_CIPHER("MMZ_MAP() for cipher failed, PhyAddr=0x%x\n", pstDESUserContext->stMMzOut.u32StartPhyAddr);
        (HI_VOID)delete_mmb(pstDESUserContext->stMMzOut.u32StartPhyAddr);
        return HI_ERR_CIPHER_FAILED_INIT;
    }
    memset((void*)(pstDESUserContext->stMMzOut.u32StartVirAddr), 0, DES_MMZ_BUFF_SIZE);
	return DX_CRYS_RETURN_ERROR(s32Ret, 0, SymAdaptor2CrysDesErr);
}

/**
 * @brief This function is used to process a block on the DES machine.
 *        This function should be called after the CRYS_DES_Init function was called.
 *      
 *
 * @param[in] ContextID_ptr - a pointer to the DES context buffer allocated by the user that
 *                       is used for the DES machine operation. this should be the same context that was
 *                       used on the previous call of this session.
 *
 * @param[in] DataIn_ptr - The pointer to the buffer of the input data to the DES. The pointer does 
 *                         not need to be aligned.
 *
 * @param[in] DataInSize - The size of the input data in bytes: must be not 0 and must be multiple 
 *                         of 8 bytes.
 *
 * @param[in/out] DataOut_ptr - The pointer to the buffer of the output data from the DES. The pointer does not 
 *                              need to be aligned.
 *
 * @return CRYSError_t - On success CRYS_OK is returned, on failure a
 *                        value MODULE_* crys_des_error.h
 */
CIMPORT_C CRYSError_t  CRYS_DES_Block( CRYS_DESUserContext_t	*ContextID_ptr,
				       DxUint8_t 		*DataIn_ptr,
				       DxUint32_t 		DataInSize,
				       DxUint8_t 		*DataOut_ptr )
{
	HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32CopySize = 0;
    HI_U32 u32TotalCopySize = 0;
    DESUserContext_t *pstDESUserContext;
    
	/* if the users context ID pointer is DX_NULL return an error */
	if( ContextID_ptr == DX_NULL ) {
		return CRYS_DES_INVALID_USER_CONTEXT_POINTER_ERROR;
	}
	
	/* if the users Data In pointer is illegal return an error */
	if( DataIn_ptr == DX_NULL ) {
		return CRYS_DES_DATA_IN_POINTER_INVALID_ERROR;
	}
	
	/* if the users Data Out pointer is illegal return an error */
	if( DataOut_ptr == DX_NULL ) {
		return CRYS_DES_DATA_OUT_POINTER_INVALID_ERROR;
	}

	/* data size must be a positive number and a block size mult */
	if (((DataInSize % CRYS_DES_BLOCK_SIZE_IN_BYTES) != 0) || (DataInSize == 0)) {
		return CRYS_DES_DATA_SIZE_ILLEGAL; 
	}

    pstDESUserContext = (DESUserContext_t *)ContextID_ptr;
	
	if ((DataInSize % CRYS_DES_BLOCK_SIZE_IN_BYTES) != 0) 
    {
		/* Only for XTS an intermediate data unit may be non aes block multiple */
		HI_ERR_CIPHER("Invalid data size: %u\n", (unsigned int)DataInSize);
		return CRYS_DES_DATA_SIZE_ILLEGAL; 
	}

    if (DataInSize > 0)
    {
        pstDESUserContext->u32BloctCnt++;
    }

    while(u32TotalCopySize < DataInSize)
    {
        if (DataInSize - u32TotalCopySize > DES_MMZ_BUFF_SIZE)
        {
            u32CopySize = DES_MMZ_BUFF_SIZE;
        }
        else
        {
            u32CopySize = DataInSize - u32TotalCopySize; 
        }
        memcpy((HI_U8*)pstDESUserContext->stMMzIn.u32StartVirAddr, DataIn_ptr+u32TotalCopySize, u32CopySize);

        if (pstDESUserContext->bIsDecrypt)
        {
            s32Ret = Cipher_Decrypt(pstDESUserContext->hCipher, pstDESUserContext->stMMzIn.u32StartPhyAddr, 
                pstDESUserContext->stMMzOut.u32StartPhyAddr, u32CopySize);
            if(HI_SUCCESS != s32Ret)
        	{
        		HI_ERR_CIPHER("Cipher encrypt failed.\n");
            }
        }
        else
        {
            s32Ret = Cipher_Encrypt(pstDESUserContext->hCipher, pstDESUserContext->stMMzIn.u32StartPhyAddr, 
                pstDESUserContext->stMMzOut.u32StartPhyAddr, u32CopySize);
            if(HI_SUCCESS != s32Ret)
        	{
        		HI_ERR_CIPHER("Cipher encrypt failed.\n");
            }
        }

        memcpy(DataOut_ptr+u32TotalCopySize, (HI_U8*)pstDESUserContext->stMMzOut.u32StartVirAddr, u32CopySize);
        memcpy(pstDESUserContext->auLastBlock, (HI_U8*)pstDESUserContext->stMMzOut.u32StartVirAddr + (u32CopySize - CRYS_DES_BLOCK_SIZE_IN_BYTES), 
                CRYS_DES_BLOCK_SIZE_IN_BYTES);
        u32TotalCopySize+=u32CopySize;
    }
    
	return DX_CRYS_RETURN_ERROR(s32Ret, 0, SymAdaptor2CrysDesErr);
}
                              
/**
 * @brief This function is used to end the DES processing session.
 *        It is the last function called for the DES process.
 *      
 *
 * @param[in] ContextID_ptr  - A pointer to the DES context buffer allocated by the user that
 *                       is used for the DES machine operation. this should be the 
 *                       same context that was used on the previous call of this session.
 *
 * @return CRYSError_t - On success the value CRYS_OK is returned, 
 *                        and on failure a value from crys_error.h
 */
CIMPORT_C CRYSError_t  CRYS_DES_Free(CRYS_DESUserContext_t  *ContextID_ptr)
{
	HI_S32 s32Ret;
    DESUserContext_t *pstDESUserContext;

	/* if the users context ID pointer is DX_NULL return an error */
	if ( ContextID_ptr == DX_NULL ) 
    {
		 return CRYS_DES_INVALID_USER_CONTEXT_POINTER_ERROR;
	}
    
    pstDESUserContext = (DESUserContext_t *)ContextID_ptr;
    
    s32Ret = Cipher_DestroyHandle(pstDESUserContext->hCipher);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
    }

    if(pstDESUserContext->stMMzIn.u32StartVirAddr != 0)
    {
        (void)unmap_mmb((void*)pstDESUserContext->stMMzIn.u32StartVirAddr);
    }
    if(pstDESUserContext->stMMzIn.u32StartPhyAddr != 0)
    {
        (void)delete_mmb(pstDESUserContext->stMMzIn.u32StartPhyAddr);
    }

    if(pstDESUserContext->stMMzOut.u32StartVirAddr != 0)
    {
        (void)unmap_mmb((void*)pstDESUserContext->stMMzOut.u32StartVirAddr);
    }
    if(pstDESUserContext->stMMzOut.u32StartPhyAddr != 0)
    {
        (void)delete_mmb(pstDESUserContext->stMMzOut.u32StartPhyAddr);
    }

	memset(ContextID_ptr, 0, sizeof(CRYS_DESUserContext_t));

	return CRYS_OK;
}

/**
 * @brief This function is used to operate the DES machine in one integrated operation.
 *
 *        The actual macros that will be used by the users are:
 *      
 *
 * @param[in,out] IVCounter_ptr - this parameter is the buffer of the IV or counters on mode CTR.
 *                          On ECB mode this parameter has no use.
 *                          On CBC mode this parameter should containe the IV values.
 *
 * @param[in] Key_ptr - a pointer to the users key buffer.
 *
 * @param[in] KeySize - Thenumber of keys used by the DES as defined in the enum.
 *
 * @param[in] EncryptDecryptFlag - This flag determains if the DES shall perform an Encrypt operation [0] or a
 *                           Decrypt operation [1].
 *
 * @param[in] OperationMode - The operation mode : ECB or CBC.
 *
 * @param[in] DataIn_ptr - The pointer to the buffer of the input data to the DES. The pointer does 
 *                         not need to be aligned.
 *
 * @param[in] DataInSize - The size of the input data in bytes: must be not 0 and must be multiple 
 *                         of 8 bytes.
 *
 * @param[in/out] DataOut_ptr - CRYS_DES_BLOCK_SIZE_IN_BYTES The pointer to the 
 *      			buffer of the output data from the DES. The
 *      			pointer does not need to be aligned.
 *
 * @return CRYSError_t - On success CRYS_OK is returned, on failure a
 *                        value MODULE_* crys_des_error.h
 *
 */
 CIMPORT_C CRYSError_t  CRYS_DES(
                CRYS_DES_Iv_t             IV_ptr,
                CRYS_DES_Key_t           *Key_ptr,
                CRYS_DES_NumOfKeys_t      NumOfKeys,
                CRYS_DES_EncryptMode_t    EncryptDecryptFlag,
                CRYS_DES_OperationMode_t  OperationMode,
                DxUint8_t                *DataIn_ptr,
                DxUint32_t                DataInSize,
                DxUint8_t                *DataOut_ptr )
{
	CRYS_DESUserContext_t UserContext;
	CRYSError_t Error = CRYS_OK;

	/* if no data to process -we're done */
	if (DataInSize == 0) {
		goto end;
	}

	Error = CRYS_DES_Init(&UserContext, IV_ptr, Key_ptr, NumOfKeys, EncryptDecryptFlag, OperationMode);
	if(Error != CRYS_OK) {
		goto end;
	}

	Error = CRYS_DES_Block(&UserContext, DataIn_ptr, DataInSize, DataOut_ptr);
	if(Error != CRYS_OK) {
		goto end;
	}

	Error = CRYS_DES_Free(&UserContext);

end:
	return Error;
}

#ifdef HI_CIPHER_TEST
void des_test1(void)
{
    CRYSError_t  err;
    CRYS_DESUserContext_t    ContextID_ptr;
    DxUint8_t     au8Data[8] = {"\x00\x00\x00\x00\x00\x00\x00\x00"};
    CRYS_DES_Key_t au8Key     = {"\x00\x00\x00\x00\x00\x00\x00\x00","",""};
    DxUint8_t        au8T[8] = {"\x8C\xA6\x4D\xE9\xC1\xB1\x23\xA7"};
    DxUint8_t       au8OT[8] = {0};

    err = CRYS_DES_Init(&ContextID_ptr, HI_NULL, &au8Key, CRYS_DES_1_KeyInUse, CRYS_DES_Encrypt, CRYS_DES_ECB_mode);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_DES_Init failed, err= 0x%x\n", err);	
        return;
	}
    err = CRYS_DES_Block(&ContextID_ptr, au8Data, sizeof(au8Data), au8OT);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_DES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("DES_ECB", au8OT, 8);
    if (memcmp(au8OT, au8T, 8) != 0)
    {
		HI_ERR_CIPHER ("DES_ECB failed\n");	
        return;
	}
}

void des_test2(void)
{
    CRYSError_t  err;
    CRYS_DESUserContext_t    ContextID_ptr;
    DxUint8_t     au8Data[32] = {"\x37\x36\x35\x34\x33\x32\x31\x20\x4E\x6F\x77\x20\x69\x73\x20\x74\x68\x65\x20\x74\x69\x6D\x65\x20\x66\x6F\x72\x20\x00\x00\x00\x00"};
    CRYS_DES_Key_t au8Key     = {"\x01\x23\x45\x67\x89\xab\xcd\xef","\xf1\xe0\xd3\xc2\xb5\xa4\x97\x86","\xfe\xdc\xba\x98\x76\x54\x32\x10"};
    DxUint8_t        auIV[8] = {"\xfe\xdc\xba\x98\x76\x54\x32\x10"};
    DxUint8_t        au8T[32] = {"\x3F\xE3\x01\xC9\x62\xAC\x01\xD0\x22\x13\x76\x3C\x1C\xBD\x4C\xDC\x79\x96\x57\xC0\x64\xEC\xF5\xD4\x1C\x67\x38\x12\xCF\xDE\x96\x75"};
    DxUint8_t       au8OT[32] = {0};

    err = CRYS_DES_Init(&ContextID_ptr, auIV, &au8Key, CRYS_DES_3_KeysInUse, CRYS_DES_Encrypt, CRYS_DES_CBC_mode);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_DES_Init failed, err= 0x%x\n", err);	
        return;
	}
    err = CRYS_DES_Block(&ContextID_ptr, au8Data, sizeof(au8Data), au8OT);
    if(CRYS_OK != err)
	{
		HI_ERR_CIPHER ("CRYS_DES_Init failed, err= 0x%x\n", err);	
        return;
	}
    HI_PRINT_HEX("TDES_CBC", au8OT, 32);
    if (memcmp(au8OT, au8T, 32) != 0)
    {
		HI_ERR_CIPHER ("TDES_CBC failed\n");	
        return;
	}
}

void des_test(void)
{
    des_test1();
    des_test2();
}
#endif
