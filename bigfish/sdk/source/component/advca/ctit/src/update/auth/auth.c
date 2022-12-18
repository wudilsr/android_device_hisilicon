#include <stdio.h>
#include <stdlib.h>
#include <cutils/log.h>

#include "rsa.h"
#include "sha2.h"
#include "crc32.h"
#include "authdefine.h"

#include "hi_flash.h"
#include "hi_common.h"
#include "hi_unf_cipher.h"

#define TMPFILE     "/mnt/sdcard/tmpupdate.zip"

int CA_Android_getExternRsaKey(rsa_context *rsa)
{
    int i, ret = 0;
	HI_HANDLE handle = INVALID_FD;
    char buffer[RSA_2048_LEN * 2] = {0};
    HI_SYS_VERSION_S enChipVersion;
    HI_Flash_InterInfo_S enFlashInfo;

    memset(&enChipVersion, 0, sizeof(HI_SYS_VERSION_S));
    memset(&enFlashInfo, 0, sizeof(HI_Flash_InterInfo_S));
    
    ret = HI_SYS_GetVersion(&enChipVersion);
    if (HI_FAILURE == ret)
    {
        SLOGE("Can't get chip info!");
        return AUTH_FAIL;
    }
    
    handle = HI_Flash_OpenByName("fastboot");
    if (HI_INVALID_HANDLE == handle)
    {
        SLOGE("Can't open fastboot partition");
        return AUTH_FAIL;
    }
    ret = HI_Flash_GetInfo(handle, &enFlashInfo);
    if (HI_FAILURE == ret)
    {
        SLOGE("Can't get chip info!");
        HI_Flash_Close(handle);
        return AUTH_FAIL;
    }
    
    if (HI_FLASH_TYPE_EMMC_0 == enFlashInfo.FlashType)
    {
        if ((HI_CHIP_TYPE_HI3719M == enChipVersion.enChipTypeHardWare) && (HI_CHIP_VERSION_V100 == enChipVersion.enChipVersion))
        {
            ret = HI_Flash_Read(handle, 0, (HI_U8 *)buffer, 512, HI_FLASH_RW_FLAG_RAW);
        }
        else
        {
            ret = HI_Flash_Read(handle, 512, (HI_U8 *)buffer, 512, HI_FLASH_RW_FLAG_RAW);
        }
    }
    else
    {
        ret = HI_Flash_Read(handle, 0, (HI_U8 *)buffer, 512, HI_FLASH_RW_FLAG_RAW);
    }
    
    if (ret == HI_FAILURE || ret == HI_FLASH_END_DUETO_BADBLOCK)
    {
        SLOGE("Read fastboot partition failed");
        HI_Flash_Close(handle);
        return AUTH_FAIL;
    }

    HI_Flash_Close(handle);
    rsa_init( rsa, RSA_PKCS_V15, 0 );    /* get rsa N and E */  
    CA_ASSERT( mpi_read_binary( (mpi *)&rsa->N, (const unsigned char *)buffer, RSA_2048_LEN), ret);
    CA_ASSERT( mpi_read_binary( (mpi *)&rsa->E, (const unsigned char *)(buffer+ RSA_2048_LEN), RSA_2048_LEN),ret);
    rsa->len = ( mpi_msb( &rsa->N ) + 7 ) >> 3;     

    return AUTH_OK;
}

int CA_Android_getSignHead(const char *inputfilepath, HI_CASignImageTail_S *CAimgHead)
{
    //unsigned int index = 0;
    unsigned long ucrc32 = 0;
    FILE *fp = NULL;
    
    fp = fopen(inputfilepath, "rb");
    CA_CheckPointer(fp);

    fseek(fp, -CAIMG_HEAD_BLOCK_SIZE, SEEK_END);
    fread((unsigned char *)CAimgHead, 1, sizeof(HI_CASignImageTail_S), fp);
    fseek(fp, 0, SEEK_SET);
    fclose(fp);
    
    if (!memcmp(CAimgHead, CAIMGHEAD_MAGICNUMBER, 32))
    {
        ucrc32 = CRC32((unsigned char *)CAimgHead, sizeof(HI_CASignImageTail_S) - 4);
        if (ucrc32 != CAimgHead->CRC32)
        {
            SLOGE("get invalid CA Sign Head\n");
            return AUTH_FAIL;
        }
    }
    else
    {
        SLOGE("get CA Sign Head failed\n");
        return AUTH_FAIL;
    }
    //SLOGE("u8Version:%s\n", CAimgHead->u8Version);
    SLOGE("u32CreateDay:0x%x\n", CAimgHead->u32CreateDay);
    SLOGE("u32CreateTime:0x%x\n", CAimgHead->u32CreateTime);
    SLOGE("u32HeadLength:0x%x\n", CAimgHead->u32HeadLength);
    SLOGE("u32SignedDataLength:%d:0x%x\n", CAimgHead->u32SignedDataLength, CAimgHead->u32SignedDataLength);
    SLOGE("u32IsYaffsImage:%d\n", CAimgHead->u32IsYaffsImage);
    SLOGE("u32IsConfigNandBlock:%d\n", CAimgHead->u32IsConfigNandBlock);
    SLOGE("u32NandBlockType:%d\n", CAimgHead->u32NandBlockType);
    SLOGE("u32IsNeedEncrypt:%d\n", CAimgHead->u32IsNeedEncrypt);
    SLOGE("u32IsEncrypted:%d\n", CAimgHead->u32IsEncrypted);
    SLOGE("u32HashType:%d\n", CAimgHead->u32HashType);
    /*for(index = 0; index < HASH256_LEN; index ++)
    {   
        SLOGE("%02x ", CAimgHead->u8Sha[index]); 
    } 
    SLOGE("u32SignatureLen:%d\n", CAimgHead->u32SignatureLen);
    for(index = 0; index < CAimgHead->u32SignatureLen; index ++)   
    {
        SLOGE("%02x ", CAimgHead->u8Signature[index]);   
    }*/
    //SLOGE("OrignalImagePath:%s\n", CAimgHead->OrignalImagePath);  
    //SLOGE("RSAPrivateKeyPath:%s\n", CAimgHead->RSAPrivateKeyPath);
    SLOGE("u32CurrentsectionID:%d\n", CAimgHead->u32CurrentsectionID);
    SLOGE("u32SectionSize:%d\n", CAimgHead->u32SectionSize);
    SLOGE("u32TotalsectionID:%d\n", CAimgHead->u32TotalsectionID);
    SLOGE("CRC32:%x\n", CAimgHead->CRC32);

    return AUTH_OK;
}


int auth(rsa_context *rsa, unsigned char *hash,unsigned char *sign)
{
    int ret = -1;

    ret = rsa_pkcs1_verify( rsa, RSA_PUBLIC, SIG_RSA_SHA256, 32, hash, sign);
    if (0 == ret)
        return AUTH_OK;
    else
        return AUTH_FAIL;
}

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

static int CA_Android_FileSha256(const char *inputfilepath, HI_CASignImageTail_S *head, char *hash)
{    
    unsigned int index = 0;   
    unsigned int remainder = 0; 
    unsigned int multiple = 0;   
    char *buffer = NULL;  
    FILE *fp = NULL;  
    HI_HANDLE hHandle = -1;   
    char u8Hash[HASH256_LEN];   
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;  
    
    buffer = (char *)malloc(SIGN_BLOCK_SIZE);
    if (buffer == NULL)  
    {      
        SLOGE("malloc memory failed");   
        return AUTH_FAIL; 
    }  
    memset(buffer, 0, SIGN_BLOCK_SIZE);  
    
    fp = fopen(inputfilepath, "rb"); 
    if (fp == NULL)  
    {    
        SLOGE("open file %s faild!", inputfilepath);  
        return AUTH_FAIL;   
    }  
    fseek(fp, 0, SEEK_SET);  
    
    multiple = head->u32SignedDataLength / SIGN_BLOCK_SIZE; 
    remainder = head->u32SignedDataLength % SIGN_BLOCK_SIZE;   
    
    HI_UNF_CIPHER_Init(); 
    
    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S)); 
    
    stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;  
    HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle); 
    
    for(index = 0; index < multiple; index++)  
    {       
        fread(buffer, 1, SIGN_BLOCK_SIZE, fp);  
        HI_UNF_CIPHER_HashUpdate(hHandle, buffer, SIGN_BLOCK_SIZE);  
    } 
    
    if (remainder != 0)   
    {      
        fread(buffer, 1, remainder, fp);     
        HI_UNF_CIPHER_HashUpdate(hHandle, buffer, remainder);   
    } 
    
    HI_UNF_CIPHER_HashFinal(hHandle, u8Hash);  
    HI_UNF_CIPHER_DeInit(); 
    
    memcpy(hash, u8Hash, HASH256_LEN); 
    
    return AUTH_OK;
}


int CA_Android_FileAuth(const char *inputfilepath, HI_CASignImageTail_S *head, rsa_context *rsa)
{
    int ret = -1;
    unsigned int index = 0;
    unsigned char hash[HASH256_LEN] = {0};
    
    CA_Android_FileSha256(inputfilepath, head, hash);
    for (index = 0; index < HASH256_LEN; index++)
    {
        SLOGE("%02x", hash[index]);
        if (hash[index] != head->u8Sha[index])
        {
            SLOGE("error in index: %d, sha2: %x != %x!", index, hash[index], head->u8Sha[index]);
            return AUTH_FAIL;
        }
    }
    ret = auth(rsa, hash, head->u8Signature);

    return ret;
}

int CA_Android_departUpdateFile(const char *inputfilepath, unsigned int length, char *outputfilepath)
{
    unsigned int index;
    unsigned int remainder = 0;
    unsigned int multiple = 0;
    FILE *in = NULL;
    FILE *out = NULL;
    char *buf = NULL;

    multiple = length / SIGN_BLOCK_SIZE;
    remainder = length % SIGN_BLOCK_SIZE;
      
    in = fopen(inputfilepath, "rb");
    out = fopen(TMPFILE, "wb");

    CA_CheckPointer(in);
    CA_CheckPointer(out);
    
    fseek(in, 0, SEEK_SET);

    buf = (char *)malloc(SIGN_BLOCK_SIZE);
    if (NULL == buf)
    {
        SLOGE("malloc memory failed, get orginal update.zip failed!");
        return AUTH_FAIL;
    }

    for (index = 0; index < multiple; index++)
    {
        fread(buf, 1, SIGN_BLOCK_SIZE, in);
        fwrite(buf, SIGN_BLOCK_SIZE, 1, out);
    }

    if (0 != remainder)
    {
        fread(buf, 1, remainder, in);
        fwrite(buf, remainder, 1, out);
    }
    fclose(out);
    fclose(in);

    if (-1 == remove(inputfilepath))
    {
        SLOGE("rm old update.zip faild");
        return AUTH_FAIL;
    }

    if (-1 == rename(TMPFILE, outputfilepath))
    {
        SLOGE("rename original update.zip faild");
        return AUTH_FAIL;
    }
    free(buf);
   
    SLOGE("get original update.zip!");
    
    return AUTH_OK;
}


int CA_Android_authUpdateFile(const char *inputfilepath,  char *outputfilepath)
{
    int ret = 0;
    HI_CASignImageTail_S head;
    rsa_context customer_key;

    memset(&customer_key, 0, sizeof(customer_key));
    memset(&head, 0, sizeof(head));

    ret = CA_Android_getSignHead(inputfilepath, &head);
    if (AUTH_FAIL == ret)
    {
        SLOGE("Fail to get Sign Head!\n");
        return AUTH_FAIL;
    }
    
    ret = CA_Android_getExternRsaKey(&customer_key);
    if (AUTH_FAIL == ret)
    {
        SLOGE("Fail to get extern rsa key!\n");
        return AUTH_FAIL;
    }
    
    ret =  CA_Android_FileAuth(inputfilepath, &head, &customer_key);
    if (AUTH_FAIL == ret)
    {
        SLOGE("Fail to get input file: %s sha!\n", inputfilepath);
        return AUTH_FAIL;
    }
    
    ret = CA_Android_departUpdateFile(inputfilepath, head.u32SignedDataLength, outputfilepath);

    return ret;
}
