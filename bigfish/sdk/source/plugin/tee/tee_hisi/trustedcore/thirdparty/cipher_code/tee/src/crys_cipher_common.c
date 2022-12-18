#include "drv_cipher.h"
#include "drv_cipher_intf.h"
#include "drv_cipher_define.h"
#include "crys_cipher_common.h"
#include "crys_rsa_error.h"
#include <boot.h>

HI_U32 CRYS_GetBitNum(HI_U8 *pu8BigNum, HI_U32 u32NumLen)
{
	static const HI_S8 u8Bits[16] = {0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4};
	HI_U32 i;
	HI_U32 u32Num;

	for(i=0; i<u32NumLen; i++)
	{
		u32Num = u8Bits[(pu8BigNum[i] & 0xF0) >> 4] ;
		if(u32Num > 0)
		{
			return (u32NumLen - i - 1) * 8 + u32Num + 4;
		}
		u32Num = u8Bits[pu8BigNum[i] & 0xF] ;
		if(u32Num > 0)
		{
			return (u32NumLen - i - 1) * 8 + u32Num;
		}
	}
	return  0;
}

#define ciL    ((int) sizeof(int))    /* chars in limb  */

HI_U32 CRYS_Bn2Bin( HI_U32 *pu32bn, HI_U8 *pbin, HI_S32 u32Len)
{
#if 1
    HI_S32 i, j, n;

    n = u32Len;

    memset( pbin, 0, u32Len);

    for( i = u32Len - 1, j = 0; n > 0; i--, j++, n-- )
        pbin[i] = (unsigned char)( pu32bn[j / ciL] >> ((j % ciL) << 3) );
#else
    memcpy(pbin, pu32bn, u32Len);
#endif
    return( 0 );
}

HI_U32 CRYS_Bin2Bn(DxUint32_t *pu32bn, HI_U8 *pbin, HI_S32 u32Len)
{
#if 1
    HI_S32 i, j, n;

    memset(pu32bn, 0, u32Len);

    for( n = 0; n < u32Len; n++ )
        if( pbin[n] != 0 )
            break;

    for( i = u32Len - 1, j = 0; i >= n; i--, j++ )
        pu32bn[j / ciL] |= ((int) pbin[i]) << ((j % ciL) << 3);
#else
    memcpy(pu32bn, pbin, u32Len);
#endif

    return( 0 );
}

HI_S32 CRYS_GetRandomNumber(HI_U8 *pu8Rand, HI_U32 u32Size)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i;
    HI_U32 u32Rand;

    memset(pu8Rand, 0, u32Size); 
    for(i=0; i<u32Size; i+=4)
    {
        ret = Cipher_GetRandomNumber(&u32Rand);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_CIPHER("Get random number failed, ret = %x\n", ret);
            return HI_FAILURE;
        }
        pu8Rand[i+3]   = (HI_U8)(u32Rand >> 24)& 0xFF;
        pu8Rand[i+2] = (HI_U8)(u32Rand >> 16)& 0xFF;
        pu8Rand[i+1] = (HI_U8)(u32Rand >> 8)& 0xFF;
        pu8Rand[i+0] = (HI_U8)(u32Rand) & 0xFF;
    }

    /*non-zero random octet string*/
    for(i=0; i<u32Size; i++)
    {
        if (pu8Rand[i] == 0x00)
        {
            ret = Cipher_GetRandomNumber(&u32Rand);
            if (ret != HI_SUCCESS)
            {
                HI_ERR_CIPHER("Get random number failed, ret = %x\n", ret);
                return HI_FAILURE;
            }
            pu8Rand[i] = (HI_U8)(u32Rand) & 0xFF;
            i = 0;
        }
    }

    return HI_SUCCESS;
}

CEXPORT_C CRYSError_t CRYS_RSA_Private(HI_U8 *UserContext_ptr, CRYSRSAPrivKey_t *PrivKey_ptr,				  				  			      
                   HI_U8 *DataIn_ptr, HI_U8 *Output_ptr, HI_U32 DataSize)
{
    HI_U32 ret;
    CIPHER_RSA_DATA_S stRsaData;
   if( UserContext_ptr == DX_NULL )
      return CRYS_RSA_INVALID_USER_CONTEXT_POINTER_ERROR;

   if (PrivKey_ptr == DX_NULL)
   	  return CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR;

    memset(&stRsaData, 0, sizeof(CIPHER_RSA_DATA_S));
    if (PrivKey_ptr->OperationMode == CRYS_RSA_NoCrt)
    {
		stRsaData.pu8N = (HI_U8*)UserContext_ptr;
		stRsaData.pu8K = stRsaData.pu8N + RSA_MAX_RSA_KEY_LEN;
        stRsaData.u16NLen = (PrivKey_ptr->nSizeInBits+7)/8;
        stRsaData.u16KLen = (PrivKey_ptr->PriveKeyDb.NonCrt.dSizeInBits+7)/8;
        CRYS_Bn2Bin((HI_U32*)PrivKey_ptr->n, stRsaData.pu8N, stRsaData.u16NLen);
        CRYS_Bn2Bin((HI_U32*)PrivKey_ptr->PriveKeyDb.NonCrt.d, stRsaData.pu8K, stRsaData.u16KLen);
    }
    else if (PrivKey_ptr->OperationMode == CRYS_RSA_Crt)
    {
		stRsaData.pu8N = (HI_U8*)UserContext_ptr;
		stRsaData.pu8K = HI_NULL;
		stRsaData.pu8P = stRsaData.pu8N + RSA_MAX_RSA_KEY_LEN;
		stRsaData.pu8Q = stRsaData.pu8P + RSA_MAX_RSA_KEY_LEN/2;
		stRsaData.pu8DP = stRsaData.pu8Q + RSA_MAX_RSA_KEY_LEN/2;
		stRsaData.pu8DQ = stRsaData.pu8DP + RSA_MAX_RSA_KEY_LEN/2;
		stRsaData.pu8QP = stRsaData.pu8DQ + RSA_MAX_RSA_KEY_LEN/2;
		stRsaData.u16NLen = (PrivKey_ptr->nSizeInBits+7)/8;
        stRsaData.u16KLen = 0;
        stRsaData.u16PLen = (PrivKey_ptr->PriveKeyDb.Crt.PSizeInBits+7)/8;
        stRsaData.u16QLen = (PrivKey_ptr->PriveKeyDb.Crt.QSizeInBits+7)/8;
        stRsaData.u16DPLen = (PrivKey_ptr->PriveKeyDb.Crt.dPSizeInBits+7)/8;
        stRsaData.u16DQLen = (PrivKey_ptr->PriveKeyDb.Crt.dQSizeInBits+7)/8;
        stRsaData.u16QPLen = (PrivKey_ptr->PriveKeyDb.Crt.qInvSizeInBits+7)/8;
        CRYS_Bn2Bin((HI_U32*)PrivKey_ptr->n, stRsaData.pu8N, stRsaData.u16NLen);
        CRYS_Bn2Bin((HI_U32*)PrivKey_ptr->PriveKeyDb.Crt.P, stRsaData.pu8P, stRsaData.u16PLen);
        CRYS_Bn2Bin((HI_U32*)PrivKey_ptr->PriveKeyDb.Crt.Q, stRsaData.pu8Q, stRsaData.u16QLen);
        CRYS_Bn2Bin((HI_U32*)PrivKey_ptr->PriveKeyDb.Crt.dP, stRsaData.pu8DP, stRsaData.u16DPLen);
        CRYS_Bn2Bin((HI_U32*)PrivKey_ptr->PriveKeyDb.Crt.dQ, stRsaData.pu8DQ, stRsaData.u16DQLen);
        CRYS_Bn2Bin((HI_U32*)PrivKey_ptr->PriveKeyDb.Crt.qInv, stRsaData.pu8QP, stRsaData.u16QPLen);
    }
    else
    {
        return CRYS_RSA_WRONG_PRIVATE_KEY_TYPE;   
    }
    stRsaData.pu8Input = DataIn_ptr;
    stRsaData.pu8Output = Output_ptr;
    stRsaData.u32DataLen = DataSize;
    ret = DRV_CIPHER_CalcRsa_SW(&stRsaData);
    return ret == HI_SUCCESS ? CRYS_OK :CRYS_FATAL_ERROR;
}
CEXPORT_C CRYSError_t CRYS_RSA_Public(HI_U8 *UserContext_ptr, CRYSRSAPubKey_t *PubKey_ptr,				  				  			      
                   HI_U8 *DataIn_ptr, HI_U8 *Output_ptr, HI_U32 DataSize)
{
    HI_U32 ret;
    CIPHER_RSA_DATA_S stRsaData;
   if( UserContext_ptr == DX_NULL )
      return CRYS_RSA_INVALID_USER_CONTEXT_POINTER_ERROR;
   if (PubKey_ptr == DX_NULL)
   	  return CRYS_RSA_INVALID_PRIV_KEY_STRUCT_POINTER_ERROR;
    memset(&stRsaData, 0, sizeof(CIPHER_RSA_DATA_S));
    stRsaData.pu8N = (HI_U8*)UserContext_ptr;
    stRsaData.pu8K = stRsaData.pu8N + RSA_MAX_RSA_KEY_LEN;
    stRsaData.u16NLen = (PubKey_ptr->nSizeInBits+7)/8;
    stRsaData.u16KLen = (PubKey_ptr->eSizeInBits+7)/8;
    CRYS_Bn2Bin((HI_U32*)PubKey_ptr->n, stRsaData.pu8N, stRsaData.u16NLen);
    CRYS_Bn2Bin((HI_U32*)PubKey_ptr->e, stRsaData.pu8K, stRsaData.u16KLen);
    stRsaData.pu8Input = DataIn_ptr;
    stRsaData.pu8Output = Output_ptr;
    stRsaData.u32DataLen = DataSize;
    ret = DRV_CIPHER_CalcRsa_SW(&stRsaData);
    return ret == HI_SUCCESS ? CRYS_OK :CRYS_FATAL_ERROR;
}
