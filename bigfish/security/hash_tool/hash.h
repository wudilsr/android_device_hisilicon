#ifndef __HASH_H__
#define __HASH_H__
typedef enum tagHashAlgorithm
{
    SHA1_ALG,
    SHA256_ALG
}HASH_ALGORITHM;

int CalHash(char* path, HASH_ALGORITHM stALGTHM, unsigned char* hash);

void WriteHashToFile(char* path, unsigned char* hash, int hashLength);

int CalAllFilesHash(char *dirname, HASH_ALGORITHM hashAlgorithm);

#endif