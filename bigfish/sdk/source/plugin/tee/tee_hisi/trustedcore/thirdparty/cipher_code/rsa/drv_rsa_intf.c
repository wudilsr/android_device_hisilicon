/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_rsa.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include <boot.h>
#include "sre_debug.h"
#include "hi_mmz.h"
#include "../mmz/list.h"
#include "sre_securemmu.h"
#include "hi_type.h"
#include "drv_cipher_define.h"
#include "drv_cipher_intf.h"
#include "drv_rsa.h"

#define sw_memcpy memcpy
#define sw_memset memset
#define sw_memcmp memcmp

HI_S32 DRV_CIPHER_CalcRsa_SW(CIPHER_RSA_DATA_S *pCipherRsaData)
{
    HI_S32 ret = HI_SUCCESS;
    rsa_context rsa;

    rsa_init(&rsa, RSA_PKCS_V15, 0);
    
    /* get N and E */
    if (pCipherRsaData->pu8N == HI_NULL)
    {
        HI_ERR_CIPHER("key error, N is null!\n");
        ret = HI_FAILURE;
    } 
    ret = mpi_read_binary( &rsa.N, pCipherRsaData->pu8N, pCipherRsaData->u16NLen);
    if( 0 != ret )
    {
        HI_ERR_CIPHER("mpi_read_binary error!\n");
        ret = HI_FAILURE;
    }
    rsa.len = ( mpi_msb( &rsa.N ) + 7 ) >> 3;
    if ((pCipherRsaData->pu8K != HI_NULL) && (pCipherRsaData->u16KLen > 0))
    {
    ret = mpi_read_binary( &rsa.E, pCipherRsaData->pu8K, pCipherRsaData->u16KLen);
    if( 0 != ret )
    {
        HI_ERR_CIPHER("mpi_read_binary error!\n");
        ret = HI_FAILURE;
    }

    ret = rsa_public(&rsa, pCipherRsaData->pu8Input, pCipherRsaData->pu8Output);
    if( 0 != ret )
        {
            HI_ERR_CIPHER("RSA public error!\n");
            ret = HI_FAILURE;
        }
    }
    else if ((pCipherRsaData->pu8P != HI_NULL)
        && (pCipherRsaData->pu8P != HI_NULL)
        && (pCipherRsaData->pu8Q != HI_NULL)
        && (pCipherRsaData->pu8DP != HI_NULL)
        && (pCipherRsaData->pu8DQ != HI_NULL)
        && (pCipherRsaData->pu8QP != HI_NULL)
        && (pCipherRsaData->pu8P != HI_NULL))
    {
        ret = mpi_read_binary( &rsa.P, pCipherRsaData->pu8P, pCipherRsaData->u16PLen);
        if( 0 != ret )
        {
            HI_ERR_CIPHER("mpi read P error!\n");
            ret = HI_FAILURE;
        }
        ret = mpi_read_binary( &rsa.Q, pCipherRsaData->pu8Q, pCipherRsaData->u16QLen);
        if( 0 != ret )
        {
            HI_ERR_CIPHER("mpi read Q error!\n");
            ret = HI_FAILURE;
        }
        ret = mpi_read_binary( &rsa.DP, pCipherRsaData->pu8DP, pCipherRsaData->u16DPLen);
        if( 0 != ret )
        {
            HI_ERR_CIPHER("mpi read DP error!\n");
            ret = HI_FAILURE;
        }
        ret = mpi_read_binary( &rsa.DQ, pCipherRsaData->pu8DQ, pCipherRsaData->u16DQLen);
        if( 0 != ret )
        {
            HI_ERR_CIPHER("mpi read DQ error!\n");
            ret = HI_FAILURE;
        }
        ret = mpi_read_binary( &rsa.QP, pCipherRsaData->pu8QP, pCipherRsaData->u16QPLen);
        if( 0 != ret )
        {
            HI_ERR_CIPHER("mpi read QP error!\n");
            ret = HI_FAILURE;
        }
        ret = rsa_private(&rsa, pCipherRsaData->pu8Input, pCipherRsaData->pu8Output);
        if( 0 != ret )
        {
            HI_ERR_CIPHER("RSA public error!\n");
        ret = HI_FAILURE;
        }
    }
    else
    {
        HI_ERR_CIPHER("invalid rsa key!\n");
        ret =  HI_FAILURE;
    }
    
    rsa_free(&rsa);

#if 0
    HI_PRINT_HEX ("N", pCipherRsaData->pu8N, pCipherRsaData->u16NLen);
    HI_PRINT_HEX ("K", pCipherRsaData->pu8K, pCipherRsaData->u16KLen);
    HI_PRINT_HEX ("P", pCipherRsaData->pu8P, pCipherRsaData->u16PLen);
    HI_PRINT_HEX ("Q", pCipherRsaData->pu8Q, pCipherRsaData->u16QLen);
    HI_PRINT_HEX ("DP", pCipherRsaData->pu8DP, pCipherRsaData->u16DPLen);
    HI_PRINT_HEX ("DQ", pCipherRsaData->pu8DQ, pCipherRsaData->u16DQLen);
    HI_PRINT_HEX ("QP", pCipherRsaData->pu8QP, pCipherRsaData->u16QPLen);
    HI_PRINT_HEX ("M", pCipherRsaData->pu8Input, pCipherRsaData->u32DataLen);
    HI_PRINT_HEX ("C", pCipherRsaData->pu8Output, (HI_U32)rsa.len);
#endif

    return ret; 

}
HI_S32 DRV_CIPHER_RSA_CallRMul(HI_U8*X, HI_U8* A, HI_U8* B, HI_U32 Xsize, HI_U32 Asize, HI_U32 Bsize)
{
	mpi x,a,b;
    HI_S32 ret;
    mpi_init (&x, &a, &b,NULL);
    ret = mpi_read_binary(&a, A, Asize);
    if( 0 != ret )
    {
        HI_ERR_CIPHER("mpi read P error, ret = 0x%x\n", ret);
        ret = HI_FAILURE;
    }
    ret = mpi_read_binary(&b, B, Bsize);
    if( 0 != ret )
    {
        HI_ERR_CIPHER("mpi read P error, ret = 0x%x\n", ret);
        ret = HI_FAILURE;
    }
    ret = mpi_mul_mpi(&x, &a, &b);
    if( 0 != ret )
    {
        HI_ERR_CIPHER("mpi mul error!, ret = 0x%x\n", ret);
        ret = HI_FAILURE;
    }
    ret = mpi_write_binary(&x, X, Xsize);
    if( 0 != ret )
    {
        HI_ERR_CIPHER("mpi write, ret = 0x%x\n", ret);
        ret = HI_FAILURE;
    }
    mpi_free(&x, &a, &b,NULL);
    return ret;
}

static HI_S32 DRV_CIPHER_RsaRandomNumber(HI_VOID *param)
{       
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32Rand;

    ret = Cipher_GetRandomNumber(&u32Rand);
    if( HI_SUCCESS != ret )
    {
        return 0x165e9fb5;
    }

    return u32Rand;
}

static HI_VOID DRV_CIPHER_CopyKey(mpi *X, HI_U8 *buf)
{
    HI_S32 ret = 0;
    HI_U8  u8Buf[CIPHER_MAX_RSA_KEY_LEN];
     
    memset(u8Buf, 0, sizeof(u8Buf));
    
    ret = mpi_write_binary(X, u8Buf, mpi_size(X));
    if( 0 != ret )
    {
        HI_ERR_CIPHER("mpi_write_binary error!\n");
    }
    sw_memcpy(buf, u8Buf, mpi_size(X));
}

HI_S32 DRV_CIPHER_GenRsaKey_SW(CIPHER_RSA_KEY_S *pstRsaKey)
{
    HI_S32 ret = 0;
    rsa_context rsa;

    rsa_init(&rsa, RSA_PKCS_V15, 0);
    ret = rsa_gen_key(&rsa, DRV_CIPHER_RsaRandomNumber, HI_NULL, pstRsaKey->u32NumBits, (HI_S32)pstRsaKey->u32Exponent);
    if( 0 == ret )
    {
        pstRsaKey->stPriKey.u16NLen = mpi_size(&rsa.N);
        pstRsaKey->stPriKey.u16ELen = mpi_size(&rsa.E);
        pstRsaKey->stPriKey.u16DLen = mpi_size(&rsa.D);
        pstRsaKey->stPriKey.u16PLen = mpi_size(&rsa.P);
        pstRsaKey->stPriKey.u16QLen = mpi_size(&rsa.Q);
        pstRsaKey->stPriKey.u16DPLen = mpi_size(&rsa.DP);
        pstRsaKey->stPriKey.u16DQLen = mpi_size(&rsa.DQ);
        pstRsaKey->stPriKey.u16QPLen = mpi_size(&rsa.QP);
        DRV_CIPHER_CopyKey(&rsa.N, pstRsaKey->stPriKey.pu8N);
        DRV_CIPHER_CopyKey(&rsa.E, pstRsaKey->stPriKey.pu8E);
        DRV_CIPHER_CopyKey(&rsa.D, pstRsaKey->stPriKey.pu8D);
        DRV_CIPHER_CopyKey(&rsa.P, pstRsaKey->stPriKey.pu8P);
        DRV_CIPHER_CopyKey(&rsa.Q, pstRsaKey->stPriKey.pu8Q);
        DRV_CIPHER_CopyKey(&rsa.DP, pstRsaKey->stPriKey.pu8DP);
        DRV_CIPHER_CopyKey(&rsa.DQ, pstRsaKey->stPriKey.pu8DQ);
        DRV_CIPHER_CopyKey(&rsa.QP, pstRsaKey->stPriKey.pu8QP);
    }
    else
    {
        HI_ERR_CIPHER("RSA public error!\n");
        ret = HI_FAILURE;
    }
    rsa_free(&rsa);

    
    return ret; 

}


