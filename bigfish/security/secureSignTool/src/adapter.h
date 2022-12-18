/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : adapter.h
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2014-03-01
Last Modified :
Description   : Hisilicon CA API definition
Function List :
History       :
******************************************************************************/


#ifndef HEADER_ADAPTER_H
#define HEADER_ADAPTER_H

#include "openssl/rsa.h"
#include "openssl/sha.h"
#include "openssl/des.h"
#include "openssl/aes.h"
#include "openssl/bio.h"
#include "openssl/err.h"
#include "openssl/bn.h"
#include "openssl/evp.h"
#include "openssl/x509.h"

#define RSA_PUBLIC      0
#define RSA_PRIVATE     1

#define RSA_PKCS_V15    0
#define RSA_PKCS_V21    1

#define SIG_RSA_SHA1    5
#define SIG_RSA_SHA256  11

#define RSA_2048_LEN 0x100
#define KEY_SIZE 2048

typedef RSA * rsa_context;

typedef AES_KEY aes_context;

typedef int havege_state;

typedef struct
{
    DES_key_schedule des_ks;
    DES_key_schedule des_ks2;
} des3_context;

void* havege_rand(void);
void* havege_init(havege_state *state);

void rsa_init( rsa_context *ctx,
               int padding,
               int hash_id,
               void *gen,
               void *genlen);

void rsa_free( rsa_context *ctx );

int write_rsa_file( const char *p, const BIGNUM *X, FILE *fout );

int mpi_get_digit( unsigned char *d, int radix, char c );

int get_rsa_from_file( BIGNUM **rsa, FILE *fin );

int write_rsa_to_file( BIGNUM *rsa, FILE *fin );

void sha1( const unsigned char *input, int ilen, unsigned char output[20] );

void sha2( const unsigned char *input, int ilen,
           unsigned char output[32], int is224 );

int mpi_read_file( BIGNUM **X, int radix, FILE *fin );

int mpi_write_file( const char *p, BIGNUM **X, int radix, FILE *fout );

int mpi_write_binary( BIGNUM **X, unsigned char *buf, int buflen );

int mpi_read_binary( BIGNUM **X, const unsigned char *buf, int buflen );

int aes_setkey_enc( aes_context *ctx, const unsigned char *key, int keysize );

int aes_crypt_cbc( aes_context *ctx,
                    int mode,
                    int length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output );

int aes_crypt_ecb( aes_context *ctx,
                    int mode,
                    const unsigned char input[16],
                    unsigned char output[16] );

int aes_setkey_dec( aes_context *ctx, const unsigned char *key, int keysize );

void des3_set2key_enc( des3_context *ctx, const unsigned char key[16] );

void des3_set2key_dec( des3_context *ctx, const unsigned char key[16] );

int des3_crypt_cbc( des3_context *ctx,
                     int mode,
                     int length,
                     unsigned char iv[8],
                     const unsigned char *input,
                     unsigned char *output );

int des3_crypt_ecb( des3_context *ctx,
                     const unsigned char input[8],
                     unsigned char output[8] );

int sha2_file( const char *path, unsigned char output[32], int is224 );

int rsa_pkcs1_sign( rsa_context *ctx,
                    int mode,
                    int hash_id,
                    int hashlen,
                    const unsigned char *hash,
                    unsigned char *sig );

int rsa_pkcs1_verify( rsa_context *ctx,
                      int mode,
                      int hash_id,
                      int hashlen,
                      unsigned char *hash,
                      unsigned char *sig );

int rsa_gen_key( rsa_context *ctx,
                 int nbits, int exponent );

#endif
