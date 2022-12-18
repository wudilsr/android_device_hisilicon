#include <stdio.h>
#include "hash1.h"
#include "hash256.h"
#include "rsa.h"
#include "verifytool.h"

#define SHA256_LEN    (0x20)

#define LOGI(...)
#define LOGE(...) fprintf(stdout, "E:" __VA_ARGS__)

static int SetRsaKey(rsa_context *rsa, unsigned char* rsaKey)
{
    int ret = 0;
    hi_rsa_init( rsa, RSA_PKCS_V15, 0 );
    /* get N and E */
    ret = hi_mpi_read_binary( &rsa->N, rsaKey, 0x100);
    ret |= hi_mpi_read_binary( &rsa->E, rsaKey + 0x100, 0x100);
    rsa->len = ( hi_mpi_msb( &rsa->N ) + 7 ) >> 3;
    return ret;
}

int verifySignRSA(unsigned char* hash, unsigned char* sign, unsigned char* rsaKey)
{
    int i = 0;
    int ret = -1;
    rsa_context key;
    ret = SetRsaKey(&key, rsaKey);
    if (ret != 0) {
        LOGE("set rsa key fail.\n");
        return -1;
    }
    LOGI("verifySignRSA begin\n");
    ret = hi_rsa_pkcs1_verify( &key, RSA_PUBLIC, SIG_RSA_SHA256, SHA256_LEN, hash, sign);
    if (ret != 0){
        LOGE("hi_rsa_pkcs1_verify fail.\n");
        return -1;
    }
    LOGI("verifySignRSA end, ret = %d\n", ret);
    return ret;
}

void SHA256( const unsigned char *input, int len, unsigned char* output)
{
    hi_sha256(input, len, output, 0);
    return;
}

void SHA1( const unsigned char *input, int len, unsigned char* output)
{
    hi_sha1(input, len, output);
    return;
}

int CipherSha1(unsigned char *input, int len, unsigned char* output)
{
    int ret = -1;
    HI_HANDLE hHandle = -1;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

    ret = HI_UNF_CIPHER_Init();
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA1;

    ret = HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle);
    if ( HI_SUCCESS != ret )
    {
        HI_UNF_CIPHER_DeInit();
        return HI_FAILURE;
    }

    ret = HI_UNF_CIPHER_HashUpdate(hHandle, input, len);
    if ( HI_SUCCESS != ret )
    {
        HI_UNF_CIPHER_DeInit();
        return HI_FAILURE;
    }

    ret = HI_UNF_CIPHER_HashFinal(hHandle, output);
    if ( HI_SUCCESS != ret )
    {
        HI_UNF_CIPHER_DeInit();
        return HI_FAILURE;
    }

    HI_UNF_CIPHER_DeInit();

    return HI_SUCCESS;
}

int CipherSha256(unsigned char *input, int len, unsigned char* output)
{
    int ret = -1;
    HI_HANDLE hHandle = -1;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

    ret = HI_UNF_CIPHER_Init();
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;

    ret = HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle);
    if ( HI_SUCCESS != ret )
    {
        HI_UNF_CIPHER_DeInit();
        return HI_FAILURE;
    }

    ret = HI_UNF_CIPHER_HashUpdate(hHandle, input, len);
    if ( HI_SUCCESS != ret )
    {
        HI_UNF_CIPHER_DeInit();
        return HI_FAILURE;
    }

    ret = HI_UNF_CIPHER_HashFinal(hHandle, output);
    if ( HI_SUCCESS != ret )
    {
        HI_UNF_CIPHER_DeInit();
        return HI_FAILURE;
    }

    HI_UNF_CIPHER_DeInit();

    return HI_SUCCESS;
}