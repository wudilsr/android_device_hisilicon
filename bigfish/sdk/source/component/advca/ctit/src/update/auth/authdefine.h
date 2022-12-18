#ifndef __AUTHDEFINE_H__
#define __AUTHDEFINE_H__

#include "hi_type.h"

#define HASH256_LEN				(0x20)			// 256bit, 32Byte
#define CAIMG_HEAD_BLOCK_SIZE   (0x2000)       // 8K
#define RSA_2048_LEN            (0x100)         //256
#define SIGN_BLOCK_SIZE         (0x200000)      //2MB
#define CAIMGHEAD_MAGICNUMBER   "Hisilicon_ADVCA_ImgHead_MagicNum"

#define AUTH_OK                 0
#define AUTH_FAIL               -1

typedef enum
{
    AUTH_SHA1,
    AUTH_SHA2,
    AUTH_BUTT
}AUTHALG_SHA_E;

typedef struct
{
    unsigned char u8MagicNumber[32];             //Magic Number: "Hisilicon_ADVCA_ImgHead_MagicNum"
    unsigned char u8Version[8];                  //version: "V000 0003" 
    unsigned int  u32CreateDay;                  //yyyymmdd
    unsigned int  u32CreateTime;                 //hhmmss
    unsigned int  u32HeadLength;                 //The following data size
    unsigned int  u32SignedDataLength;           //signed data length
    unsigned int  u32IsYaffsImage;               //Yaffsr image need to specail read-out, No use
    unsigned int  u32IsConfigNandBlock;          //Yaffsr image need to specail read-out, No use
    unsigned int  u32NandBlockType;              //Yaffsr image need to specail read-out, No use
    unsigned int  u32IsNeedEncrypt;              //if "1", code need to be encrypted. 
    unsigned int  u32IsEncrypted;                //if "1", code has encrypted. 
    unsigned int  u32HashType;                   //if "0", u8Sha save sha1 of code, if "1",  u8Sha save sha256 of code
    unsigned char u8Sha[32];                     //SHA value
    unsigned int  u32SignatureLen;               //Actural Signature length
    unsigned char u8Signature[256];              //Max length:0x100
    unsigned char OrignalImagePath[256];         //Max length:
    unsigned char RSAPrivateKeyPath[256];        //Max length:0x100
    unsigned int  u32CurrentsectionID;            //begin with 0
	unsigned int  u32SectionSize;                 //section size 
    unsigned int  u32TotalsectionID;              //Max section ID > 1 
    unsigned int  CRC32;                         //CRC32 value
} HI_CASignImageTail_S;
/*
#define CA_printf(p) \
    do { \
        FILE *file = fopen("/dev/ttyAMA0", "w"); \
        fprintf(file, "p");\
        fclose(file);\
    } while(0)  */


//#define CA_printf(p) 	printf(p)
#define CA_CheckPointer(p) \
    do {  \
        if (NULL == p)\
        {\
            printf("pointer parameter is NULL.\n"); \
            return -1; \
        } \
    } while (0)

#define CA_ASSERT(api, ret) \
    do{ \
        HI_S32 l_ret = api; \
        if (l_ret != HI_SUCCESS) \
        { \
            printf("run failed"); \
            return -1;\
        } \
        else\
        {\
        /*printf("sample %s: run %s ok.\n", __FUNCTION__, #api);}*/   \
        }\
        ret = l_ret;\
    } while(0)
    
#endif /*__AUTHDEFINE_H__*/

