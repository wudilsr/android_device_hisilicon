#ifndef __VERIFYTOOL_H__
#define __VERIFYTOOL_H__

#include "hi_unf_cipher.h"

#ifdef __cplusplus
extern "C"{
#endif

int verifySignRSA(unsigned char* hash, unsigned char* sign, unsigned char* rsaKey);

void SHA256( const unsigned char *input, int len, unsigned char* output);

void SHA1( const unsigned char *input, int len, unsigned char* output);

int CipherSha1(unsigned char *input, int len, unsigned char* output);

int CipherSha256(unsigned char *input, int len, unsigned char* output);

#ifdef __cplusplus
}
#endif

#endif