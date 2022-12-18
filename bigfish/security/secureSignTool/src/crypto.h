#ifndef __SIGN_NON_BOOT_IMAGE_H__
#define __SIGN_NON_BOOT_IMAGE_H__

#include "type.h"
#include "adapter.h"

typedef enum tagAlgorithm
{
    AES = 0x0,
    TDES,
    SHA1_ALG,
    SHA256_ALG,
    CRC16,
#ifdef BOOTROM_CRC16
    BOOTROM_CRC16,
#endif
    RSA_ALG,
}ALGORITHM_EN;

typedef enum tagMode
{
    CBC = 0x0,
    ECB,
}MODE_EN;

typedef enum tagCrypt
{
    ENCRYPT_OP = 0x0,
    DECRYPT_OP,
}CRYPT_EN;

#define BUFFER_SIZE 32
#define PATH_LENGTH 4096

typedef struct crypto_config_parameter_st
{
    unsigned char External_private_key_file[PATH_LENGTH];
    unsigned char Algorithm[BUFFER_SIZE];
    unsigned char Mode[BUFFER_SIZE];
    unsigned char OperationType[BUFFER_SIZE];
    unsigned char Key[BUFFER_SIZE * 2];
    unsigned char IV[BUFFER_SIZE * 2];
    unsigned char ImageNumber[BUFFER_SIZE];
    unsigned char InputFileDir[PATH_LENGTH];
    unsigned char OutputFileDir[PATH_LENGTH];
}CRYPTO_CONFIG_PARAMETER_ST;

typedef struct crypto_image_attribute_st
{
    unsigned char Input[PATH_LENGTH];
    unsigned char Output[PATH_LENGTH];
}CRYPTO_IMG_ATTRIBUTE_ST;

int Sign_NonBOOTImage_Crypto(const char* strConfigFile,const char* inputdir,const char* outputdir,const char* keydir);
extern unsigned long DVB_CRC32(unsigned char *buf, int length);
extern int ParseFile(char *tmp,const char *str, char *srcFile);
extern int GetDirName(char *tmp, char *dir);


#endif
