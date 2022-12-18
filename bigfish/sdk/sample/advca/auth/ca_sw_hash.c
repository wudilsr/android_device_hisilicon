
/***********************************************************************
*
* Copyright (c) 2006 HUAWEI - All Rights Reserved
*
* File: $ahs_stream_target.h$
* Date: $2011/6/27$
* Revision: $v1.0$
* Purpose: make video stream index info for trick play.
*          support multi video standards
*
* Change History:
*
* Date             Author            Change
* ====             ======            ======
*
* Dependencies:
*
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <cutils/log.h>

#include "alg.h"
#include "authdefine.h"

typedef enum HASH_TYPE
{
	Hash1,
	Hash2
}HASH_TYPE_S;

typedef struct hash_atts
{
    HI_HANDLE *sha_context;
    HASH_TYPE_S hashType;
}HASH_ATTS_S;

const unsigned char rsa_pub_key[512] = {
    0x8b, 0xdd, 0x8b, 0x4a, 0x0c, 0x31, 0x75, 0x1f, 0x2c, 0x7a, 0x73, 0x27, 0xbd, 0xf1, 0xd8, 0x58, 
    0x4d, 0xc7, 0x19, 0x73, 0x81, 0x04, 0x4d, 0xcf, 0x64, 0xe6, 0xbd, 0x55, 0x79, 0x32, 0x7a, 0x78, 
    0x9b, 0xde, 0x3e, 0x1f, 0xf6, 0x5c, 0x6f, 0xdd, 0xd6, 0xd7, 0xb6, 0x0e, 0xe1, 0x00, 0x28, 0x25, 
    0xa4, 0x45, 0xd5, 0xd6, 0x4a, 0x14, 0x20, 0x6f, 0xc6, 0x37, 0x77, 0xb2, 0x11, 0xa2, 0x19, 0x62, 
    0x76, 0x83, 0xf4, 0xe1, 0xec, 0x80, 0x1e, 0x48, 0x23, 0x95, 0x72, 0xde, 0x3d, 0x32, 0x44, 0x1b, 
    0xdc, 0x85, 0x98, 0xb8, 0x97, 0x56, 0x48, 0x71, 0xa5, 0x3f, 0xc4, 0x1c, 0x7b, 0xe2, 0x85, 0x51, 
    0xd2, 0x37, 0x11, 0x0a, 0xd7, 0x18, 0xee, 0x24, 0x84, 0x00, 0x9b, 0x04, 0xff, 0x5e, 0x69, 0x82, 
    0x55, 0xae, 0xd3, 0x1a, 0x50, 0x20, 0xc1, 0xd7, 0x49, 0xcf, 0x70, 0xb7, 0xc1, 0xa6, 0x73, 0x38, 
    0x15, 0x3c, 0x1b, 0x21, 0x13, 0x47, 0xd9, 0xc3, 0x2b, 0xd2, 0xdf, 0xe6, 0x9d, 0x03, 0x7b, 0x7c, 
    0x07, 0xf9, 0x1d, 0xa6, 0xd2, 0xfc, 0xad, 0xf1, 0x83, 0x31, 0x91, 0xf3, 0x7f, 0x35, 0xc4, 0xc4, 
    0xac, 0x1e, 0x7f, 0x2f, 0x2b, 0x76, 0x36, 0x0b, 0xb3, 0x22, 0x7f, 0xb7, 0x93, 0x6b, 0xfa, 0xd8, 
    0xcc, 0xac, 0xcd, 0xcc, 0x0c, 0x30, 0x40, 0x04, 0x27, 0xa8, 0x74, 0xca, 0xb3, 0xd0, 0x7e, 0x96, 
    0x18, 0xa8, 0x9c, 0x2e, 0xcf, 0x53, 0x64, 0xc4, 0x6a, 0x82, 0xc4, 0x26, 0xe0, 0x75, 0xf5, 0xcb, 
    0xf8, 0x20, 0xdc, 0x48, 0x8b, 0xdb, 0x81, 0x51, 0x61, 0x9f, 0x03, 0x30, 0xf3, 0x1a, 0x29, 0xd3, 
    0x02, 0x83, 0x7e, 0x3b, 0x50, 0xcd, 0x2b, 0x65, 0x82, 0x7f, 0x01, 0xaa, 0x88, 0x6d, 0xb7, 0x38, 
    0x99, 0x7d, 0x54, 0x03, 0x31, 0x1d, 0x6c, 0x54, 0xb4, 0x7c, 0xa4, 0x0b, 0x36, 0x74, 0xff, 0x9f, 
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
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03
};

static int CA_common_getRsaKey(rsa_context *rsa)
{
    int ret = 0;

    rsa_init(rsa, RSA_PKCS_V15, 0);    /* get rsa N and E */  
    CA_ASSERT(mpi_read_binary((mpi *)&rsa->N, rsa_pub_key, RSA_2048_LEN), ret);
    CA_ASSERT(mpi_read_binary((mpi *)&rsa->E, rsa_pub_key + RSA_2048_LEN, RSA_2048_LEN), ret);
    rsa->len = ( mpi_msb( &rsa->N ) + 7 ) >> 3;     

    return ret;
}


HI_S32 CA_common_InitHASH(HI_U8 HashType, HI_HANDLE **handle)
{
    void *ctx = NULL;
    HASH_ATTS_S *atts = NULL;

    atts = (HASH_ATTS_S *)malloc(sizeof(HASH_ATTS_S));
    if (NULL == atts)
    {
        printf("err [%s:%d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    if (HashType == Hash1)
    {
        ctx = (sha1_context *)malloc(sizeof(sha1_context));
        if (NULL == ctx)
        {
            printf("err [%s:%d]\n", __FUNCTION__, __LINE__);
            free(atts);
            return -1;
        }
        memset(ctx, 0, sizeof(sha1_context));

        sha1_starts(ctx);
    }
    else if (HashType == Hash2)
    {
        ctx = (sha2_context *)malloc(sizeof(sha2_context));
        if (NULL == ctx)
        {
            printf("err [%s:%d]\n", __FUNCTION__, __LINE__);
            free(atts);
            return -1;
        }
        memset(ctx, 0, sizeof(sha2_context));

        sha2_starts(ctx, 0);
    }
    else
    {
        printf("Invalid hash type!\n");
        free(atts);
        return -1;
    }
    atts->sha_context= (HI_HANDLE *)ctx;
    atts->hashType = HashType;
    *handle = (HI_HANDLE *)atts;

    return 0;
}

HI_VOID CA_common_UpdateHASH(HI_HANDLE *handle, HI_U8 *StartAddr, HI_U32 length)
{
    if (((HASH_ATTS_S *)handle)->hashType == Hash2)
    {
        sha2_update((sha2_context *)(((HASH_ATTS_S *)handle)->sha_context), (const unsigned char *)StartAddr, length);
    }
    else
    {
        sha1_update((sha1_context *)(((HASH_ATTS_S *)handle)->sha_context), (const unsigned char *)StartAddr, length);
    }
}

HI_VOID CA_common_FinishHASH(HI_HANDLE *handle, HI_U8 *Hash)
{
    if (((HASH_ATTS_S *)handle)->hashType == Hash2)
    {
        sha2_finish((sha2_context *)(((HASH_ATTS_S *)handle)->sha_context), Hash);
        free((sha2_context *)(((HASH_ATTS_S *)handle)->sha_context));
    }
    else
    {
        sha1_finish((sha1_context *)(((HASH_ATTS_S *)handle)->sha_context), Hash);
        free((sha1_context *)(((HASH_ATTS_S *)handle)->sha_context));
    }
    free((HASH_ATTS_S *)handle);

}

HI_S32 CA_common_DataAuthenticateEx(HI_U8 HashType, HI_U8 *Hash, HI_CASignImageTail_S *pCASignTail)
{
    int ret = -1;
    rsa_context rsa;

    if (-1 == CA_common_getRsaKey(&rsa))
    {
        printf("get key faild!\n");
        return -1;
    }

    if (Hash1 == HashType)
    {
        ret = rsa_pkcs1_verify(&rsa, RSA_PUBLIC, SIG_RSA_SHA1, 20, Hash, pCASignTail->u8Signature);
    }
    else if (Hash2 == HashType)
    {
        ret = rsa_pkcs1_verify(&rsa, RSA_PUBLIC, SIG_RSA_SHA256, 32, Hash, pCASignTail->u8Signature);
    }
    
    return (ret == 0) ? 0 : -1;    
}

/*
int CA_Android_HWSha256(char *data_buf, int length, unsigned char hash[32])
{    
    unsigned int index;
    unsigned int remainder = 0;
    unsigned int multiple = 0;
    HI_HANDLE hHandle = -1;
    char u8Hash[32];
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

    multiple = length / SIGN_BLOCK_SIZE;
    remainder = length % SIGN_BLOCK_SIZE;
    
    HI_UNF_CIPHER_Init();
    
    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;
    HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle);
    for(index = 0; index < multiple; index++)    
    {        
        HI_UNF_CIPHER_HashUpdate(hHandle, data_buf + index * SIGN_BLOCK_SIZE, SIGN_BLOCK_SIZE);    
    }    
    if (remainder != 0)    
    {        
        HI_UNF_CIPHER_HashUpdate(hHandle, data_buf + index * SIGN_BLOCK_SIZE, remainder);
    }    
    HI_UNF_CIPHER_HashFinal(hHandle, u8Hash);    
    HI_UNF_CIPHER_DeInit();       
    memcpy(hash, u8Hash, 32);   
    
    return AUTH_OK;
}

*/
