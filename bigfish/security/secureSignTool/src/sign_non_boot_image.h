#ifndef __SIGN_NON_BOOT_IMAGE_H__
#define __SIGN_NON_BOOT_IMAGE_H__

#include "type.h"

//kernel fs
#define KernelSign              "./SignOutput/kernel.sig"
#define RootfsSign              "./SignOutput/rootfs.sig"

#define DEBUG

#ifdef DEBUG
#define log(...)    printf(__VA_ARGS__)
#else
#define log(...)
#endif

//for non-boot
#define PAGE_SIZE   0x2000
#define IMG_MAX_BLOCK_NUM   5
#define SIGNATURE_LEN 256

#define CAIMGHEAD_MAGICNUMBER   "Hisilicon_ADVCA_ImgHead_MagicNum"
#define CAIMGHEAD_VERSION       "v1.0.0.3"

typedef enum hi_Algorithm_E
{
    Hash1,
    Hash2
}HI_Algorithm_EN;

typedef struct hi_CAImgHead_S
{
    unsigned char u8MagicNumber[32];
    unsigned char u8Version[8];
    unsigned int u32TotalLen;
    unsigned int u32CodeOffset;
    unsigned int u32SignedImageLen;
    unsigned int u32SignatureOffset;
    unsigned int u32SignatureLen;
    unsigned int u32BlockNum;
    unsigned int u32BlockOffset[IMG_MAX_BLOCK_NUM];
    unsigned int u32BlockLength[IMG_MAX_BLOCK_NUM];
    unsigned int Reserverd[32];
    unsigned int u32CRC32;
} HI_CAImgHead_S;


typedef struct
{
    unsigned char u8MagicNumber[32];             //Magic Number: "Hisilicon_ADVCA_ImgTail_MagicNum"
    unsigned char u8Version[8];                  //version: "V000 0003" , former version "V000 0002"
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
    unsigned int  CRC32;                         //CRC32 of upper data
} HI_CASignImageTail_S;

BOOL Sign_NonBOOTImage_Common(char* strDestFile, const char *rsaKeyFile, const char* strSrcFile,  unsigned int sectionSize);
BOOL Sign_NonBOOTImage_Special(const char* strConfigFile, const char* inputdir,const char* outputdir,const char* keydir);
extern unsigned long DVB_CRC32(unsigned char *buf, int length);
extern int ParseFile(char *tmp,const char *str, char *srcFile);
extern int GetDirName(char *tmp, char *dir);


#endif
