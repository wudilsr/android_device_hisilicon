/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : adapter.c
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2014-03-01
Last Modified :
Description   : Hisilicon CA API definition
Function List :
History       :
******************************************************************************/
#include "adapter.h"
#include "string.h"

int write_rsa_file( const char *p, const BIGNUM *X, FILE *fout )
{
    int ret = 0;
    unsigned char numRsaKey[512] = {0};
    int len = 0;
    int i = 0;

    len = BN_bn2bin(X, numRsaKey);
    ret = fwrite(p, 1, strlen(p), fout);
    if (ret <= 0)
    {
        return ret;
    }

    for (i = 0; i < len; i++)
    {
        ret |= fprintf(fout, "%02x", numRsaKey[i]);
    }
    ret |= fwrite("\r\n", 1, 2, fout);
    if (ret <= 0)
    {
        return ret;
    }

    return 0;
}

/*
 * Convert an ASCII character to digit value
 */
int mpi_get_digit( unsigned char *d, int radix, char c )
{
    *d = 255;

    if( c >= 0x30 && c <= 0x39 ) *d = c - 0x30;
    if( c >= 0x41 && c <= 0x46 ) *d = c - 0x37;
    if( c >= 0x61 && c <= 0x66 ) *d = c - 0x57;

    if( *d >= (unsigned long) radix )
        return( -1 );

    return( 0 );
}

int get_rsa_from_file( BIGNUM **rsa, FILE *fin )
{
    char strRsaKey[1024] = {0};
    unsigned char numRsaKey[1024] = {0};
    int index = 0;
    int i = 0;
    int slen = 0;
    char *p;
    unsigned char d = 0;

    if( fgets( strRsaKey, sizeof( strRsaKey ) - 1, fin ) == NULL )
        return -1;

    slen = strlen( strRsaKey );
    if( strRsaKey[slen - 1] == '\n' ) { slen--; strRsaKey[slen] = '\0'; }
    if( strRsaKey[slen - 1] == '\r' ) { slen--; strRsaKey[slen] = '\0'; }

    p = strRsaKey + 2;
    i = 0;
    index = 0;
    while( p <= (strRsaKey + slen) )
    {
        if( mpi_get_digit( &d, 16, *p ) != 0 )
        {
            p++;
            continue;
        }
        else
        {
            //Jump "0x" or "0X"
            if( ((p[0] == '0') && (p[1] == 'x'))
             || ((p[0] == '0') && (p[1] == 'X'))
             )
            {
                p++;
                continue;
            }
        }

        numRsaKey[index] = numRsaKey[index] << (4 * (i % 2)) | d;
        if (1 == (i++ % 2))
        {
            index++;
        }
        p++;
    }

    *rsa = BN_bin2bn(numRsaKey, index, *rsa);

    return 0;
}

int write_rsa_to_file( BIGNUM *rsa, FILE *fin )
{
    char strRsaKey[1024] = {0};
    unsigned char numRsaKey[1024] = {0};
    int index = 0;
    int i = 0;
    int slen = 0;
    char *p;
    unsigned char d = 0;

    if( fgets( strRsaKey, sizeof( strRsaKey ) - 1, fin ) == NULL )
        return -1;

    slen = strlen( strRsaKey );
    if( strRsaKey[slen - 1] == '\n' ) { slen--; strRsaKey[slen] = '\0'; }
    if( strRsaKey[slen - 1] == '\r' ) { slen--; strRsaKey[slen] = '\0'; }

    p = strRsaKey + 2;
    i = 0;
    index = 0;
    while( p <= (strRsaKey + slen) )
    {
        if( mpi_get_digit( &d, 16, *p ) != 0 )
        {
            p++;
            continue;
        }

        numRsaKey[index] = numRsaKey[index] << (4 * (i % 2)) | d;
        if (1 == (i++ % 2))
        {
            index++;
        }
        p++;
    }

    rsa = BN_bin2bn(numRsaKey, index, rsa);

    return 0;
}

void* havege_rand(void)
{
    return NULL;
}

void* havege_init(havege_state *state)
{
    state = NULL;
    return NULL;
}

void rsa_init( rsa_context *ctx,
               int padding,
               int hash_id,
               void *gen,
               void *genlen)
{
    *ctx = RSA_new();
}

void rsa_free( rsa_context *ctx )
{
    return RSA_free(*ctx);
}

void sha1( const unsigned char *input, int ilen, unsigned char output[20] )
{
    SHA1(input, ilen, output);
}

void sha2( const unsigned char *input, int ilen,
           unsigned char output[32], int is224 )
{
    SHA256(input, ilen, output);
}

int mpi_read_file( BIGNUM **X, int radix, FILE *fin )
{
    return get_rsa_from_file(X, fin);
}

int mpi_write_file( const char *p, BIGNUM **X, int radix, FILE *fout )
{
    return write_rsa_file( p , *X , fout );
}

int mpi_write_binary( BIGNUM **X, unsigned char *buf, int buflen )
{
    int length = 0;
    unsigned char numRsa[512] = {0};

    length = BN_bn2bin(*X, numRsa);
    memcpy(buf + buflen - length, numRsa, length);

    return 0;
}

int mpi_read_binary( BIGNUM **X, const unsigned char *buf, int buflen )
{
    *X = BN_bin2bn(buf, buflen, *X);

    return 0;
}

int aes_setkey_enc( aes_context *ctx, const unsigned char *key, int keysize )
{
    return AES_set_encrypt_key(key, keysize, ctx);
}

int aes_crypt_cbc( aes_context *ctx,
                    int mode,
                    int length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output )
{
    AES_cbc_encrypt(input, output, length, ctx, iv, mode);

    return 0;
}

int aes_crypt_ecb( aes_context *ctx,
                    int mode,
                    const unsigned char input[16],
                    unsigned char output[16] )
{
    AES_ecb_encrypt(input, output, ctx, mode);

    return 0;
}

int aes_setkey_dec( aes_context *ctx, const unsigned char *key, int keysize )
{
    return AES_set_decrypt_key(key, keysize, ctx);
}

int g_desMode = DES_ENCRYPT;

void des3_set2key_enc( des3_context *ctx, const unsigned char key[16] )
{
    g_desMode = DES_ENCRYPT;
    DES_set_key_unchecked((const_DES_cblock *)&key[0], &ctx->des_ks);
    DES_set_key_unchecked((const_DES_cblock *)&key[8], &ctx->des_ks2);
}

void des3_set2key_dec( des3_context *ctx, const unsigned char key[16] )
{
    g_desMode = DES_DECRYPT;
    DES_set_key_unchecked((const_DES_cblock *)&key[0], &ctx->des_ks);
    DES_set_key_unchecked((const_DES_cblock *)&key[8], &ctx->des_ks2);
}

int des3_crypt_cbc( des3_context *ctx,
                     int mode,
                     int length,
                     unsigned char iv[8],
                     const unsigned char *input,
                     unsigned char *output )
{
    DES_ede2_cbc_encrypt(input, output, length, &ctx->des_ks, &ctx->des_ks2, (DES_cblock *)iv, mode);

    return 0;
}

int des3_crypt_ecb( des3_context *ctx,
                     const unsigned char input[8],
                     unsigned char output[8] )
{
    DES_ecb2_encrypt((const_DES_cblock *)input, (DES_cblock *)output, &ctx->des_ks, &ctx->des_ks2, g_desMode);

    return 0;
}

int sha2_file( const char *path, unsigned char output[32], int is224 )
{
    FILE *fp = NULL;
    unsigned char buf[512];
    SHA256_CTX ctx;
    int number = 0;

    if((fp = fopen(path, "rb")) == NULL)
    {
        printf("Failed to open source file!");
        return -1;
    }

    SHA256_Init(&ctx);

    while( ( number = fread( buf, 1, sizeof( buf ), fp ) ) > 0 )
    {
        SHA256_Update(&ctx, buf, number);
    }

    SHA256_Final(output, &ctx);

    fclose(fp);

    return 0;
}

int rsa_pkcs1_sign( rsa_context *ctx,
                    int mode,
                    int hash_id,
                    int hashlen,
                    const unsigned char *hash,
                    unsigned char *sig )
{
    if (hash_id == SIG_RSA_SHA256)
    {
        if (RSA_private_encrypt(hashlen, hash, sig, *ctx, RSA_PKCS1_SHA2_PADDING) != RSA_2048_LEN)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
    else if (hash_id == SIG_RSA_SHA1)
    {
        if (RSA_private_encrypt(hashlen, hash, sig, *ctx, RSA_PKCS1_SHA1_PADDING) != RSA_2048_LEN)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    return -1;
}

int rsa_pkcs1_verify( rsa_context *ctx,
                      int mode,
                      int hash_id,
                      int hashlen,
                      unsigned char *hash,
                      unsigned char *sig )
{
    if (hash_id == SIG_RSA_SHA256)
    {
        if (32 == RSA_public_decrypt(RSA_2048_LEN, sig, hash, *ctx, RSA_PKCS1_SHA2_PADDING))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else if (hash_id == SIG_RSA_SHA1)
    {
        if (32 == RSA_public_decrypt(RSA_2048_LEN, sig, hash, *ctx, RSA_PKCS1_SHA1_PADDING))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    return -1;
}

static int genrsa_cb(int p, int n, BN_GENCB *cb)
{
    char c='*';

    if (p == 0) c='.';
    if (p == 1) c='+';
    if (p == 2) c='*';
    if (p == 3) c='\n';
    BIO_write((BIO *)(cb->arg),&c,1);
    (void)BIO_flush((BIO *)(cb->arg));

    return 1;
}

int rsa_gen_key( rsa_context *ctx,
                 int nbits, int exponent )
{
    BIGNUM *bn = BN_new();
    unsigned long nRsaE=RSA_3;
    BN_GENCB cb;
    unsigned char test_rsa[KEY_SIZE] = {0};
    unsigned char numRsaKeyN[KEY_SIZE] = {0};
    unsigned char numRsaKeyE[KEY_SIZE] = {0};
    int lenRsaN = 0;
    int lenRsaE = 0;

    if(!bn)
    {
        return -1;
    }
    BN_GENCB_set(&cb, genrsa_cb, NULL);

    if(!BN_set_word(bn, exponent) || !RSA_generate_key_ex(*ctx, nbits, bn, &cb))
    {
        return -1;
    }

    BN_free(bn);

    return 0;
}
