/******************************************************************************
Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_rng.c
Version       : Initial Draft
Author        : Hisilicon
Created       : 2012/07/10
Last Modified :
Description   :	sample for hash
Function List :
History       :
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <assert.h> 

#include "hi_type.h"
#include "hi_unf_cipher.h"
#include "hi_common.h"
#include "hi_adp.h"

#ifdef  CONFIG_SUPPORT_CA_RELEASE
#define HI_ERR_CIPHER(format, arg...)
#define HI_INFO_CIPHER(format, arg...)   printf( "%s,%d: " format , __FUNCTION__, __LINE__, ## arg)
#else
#define HI_ERR_CIPHER(format, arg...)    printf( "%s,%d: " format , __FUNCTION__, __LINE__, ## arg)
#define HI_INFO_CIPHER(format, arg...)   printf( "%s,%d: " format , __FUNCTION__, __LINE__, ## arg)
#endif

static void print_time (HI_U32 u32Line)
{
    struct timeval tv;
    struct timeval interval;
    static struct timeval last_tv = {0};
    
    gettimeofday (&tv, NULL);

    if(tv.tv_usec < last_tv.tv_usec)
    {
        interval.tv_sec = tv.tv_sec - 1 - last_tv.tv_sec;
        interval.tv_usec = tv.tv_usec + 1000000 - last_tv.tv_usec;
    }
    else
    {
        interval.tv_sec = tv.tv_sec - last_tv.tv_sec;
        interval.tv_usec = tv.tv_usec - last_tv.tv_usec;
    }
    last_tv.tv_sec = tv.tv_sec;
    last_tv.tv_usec = tv.tv_usec;
    printf("LINE %d: %02d.%02d, interval: %02d.%06d\r\n", u32Line, (HI_U32)tv.tv_sec, 
        (HI_U32)tv.tv_usec, (HI_U32)interval.tv_sec, (HI_U32)interval.tv_usec);
}

static HI_S32 printBuffer(const HI_CHAR *string, const HI_U8 *pu8Input, HI_U32 u32Length)
{
    HI_U32 i = 0;
    
    if ( NULL != string )
    {
        printf("%s\n", string);
    }

    for ( i = 0 ; i < u32Length; i++ )
    {
        if( (i % 16 == 0) && (i != 0)) printf("\n");
        printf("0x%02x ", pu8Input[i]);
    }
    printf("\n");

    return HI_SUCCESS;
}

HI_U8 u8HMACKey[16] = {0xe, 0xd, 0x2, 0x3, 0x2, 0x9, 0xc, 0xd, 0xa, 0xb, 0xc, 0xd, 0xa, 0xb, 0xc, 0xd};

static unsigned char sha1_buf[3][57] = {
    {"abc"},
    {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"},
    {""}
};
static const int sha1_buflen[3] ={3, 56};
static const unsigned char sha1_sum[2][20] ={
    {0xA9, 0x99, 0x3E, 0x36, 0x47, 0x06, 0x81, 0x6A, 0xBA, 0x3E,
     0x25, 0x71, 0x78, 0x50, 0xC2, 0x6C, 0x9C, 0xD0, 0xD8, 0x9D},
    {0x84, 0x98, 0x3E, 0x44, 0x1C, 0x3B, 0xD2, 0x6E, 0xBA, 0xAE,
     0x4A, 0xA1, 0xF9, 0x51, 0x29, 0xE5, 0xE5, 0x46, 0x70, 0xF1},
};


static unsigned char sha2_buf[3][57] = {
    {"abc"},
    {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"},
    {""}
};
static const int sha2_buflen[3] = {3, 56, 1000};
static const unsigned char sha2_sum[6][32] ={
    /** SHA-256 sample vectors*/
    {0xBA, 0x78, 0x16, 0xBF, 0x8F, 0x01, 0xCF, 0xEA, 0x41, 0x41, 0x40, 0xDE, 0x5D, 0xAE, 0x22, 0x23, 0xB0, 0x03, 0x61, 0xA3, 0x96, 0x17, 0x7A, 0x9C, 0xB4, 0x10, 0xFF, 0x61, 0xF2, 0x00, 0x15, 0xAD},
    {0x24, 0x8D, 0x6A, 0x61, 0xD2, 0x06, 0x38, 0xB8, 0xE5, 0xC0, 0x26, 0x93, 0x0C, 0x3E, 0x60, 0x39, 0xA3, 0x3C, 0xE4, 0x59, 0x64, 0xFF, 0x21, 0x67, 0xF6, 0xEC, 0xED, 0xD4, 0x19, 0xDB, 0x06, 0xC1},
    {0xCD, 0xC7, 0x6E, 0x5C, 0x99, 0x14, 0xFB, 0x92, 0x81, 0xA1, 0xC7, 0xE2, 0x84, 0xD7, 0x3E, 0x67, 0xF1, 0x80, 0x9A, 0x48, 0xA4, 0x97, 0x20, 0x0E, 0x04, 0x6D, 0x39, 0xCC, 0xC7, 0x11, 0x2C, 0xD0}
};

#define CAPACITY_TEST_SIZE    (10*1024*1024)
#define CAPACITY_BLOCK_SIZE   (10*1024*1024)
#define CAPACITY_BLOCK_CNT    (CAPACITY_TEST_SIZE/CAPACITY_BLOCK_SIZE)

HI_S32 Capacity(HI_UNF_CIPHER_HASH_TYPE_E enHashType)
{
	HI_S32 ret = HI_SUCCESS;
    HI_U8 u8Hash[32];
    HI_U32 i = 0, j = 0;
    HI_HANDLE hHandle = HI_INVALID_HANDLE;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;
    HI_U8 *pu8Buf = HI_NULL;

	ret = HI_UNF_CIPHER_Init();
	if ( HI_SUCCESS != ret )
	{
		return HI_FAILURE;
	}

    memset(u8Hash, 0, 32);

    pu8Buf = (HI_U8*)malloc(CAPACITY_BLOCK_SIZE);
    if (pu8Buf == HI_NULL)
    {
        HI_ERR_CIPHER("malloc failed\n");
        return HI_FAILURE;
    }
    memset(pu8Buf, 'a', CAPACITY_BLOCK_SIZE);

    for(i = 1; i <= 10; i++)
    {
        printf("--------------type: %d, size: %dM------------------\n", enHashType, i*CAPACITY_BLOCK_SIZE/1024/1024);
        memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
        stHashAttr.eShaType = enHashType;

        print_time(__LINE__);
        ret = HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}

#if 0
        for(j=0; j< i; j++)
        {
            ret = HI_UNF_CIPHER_HashUpdate(hHandle, pu8Buf, CAPACITY_BLOCK_SIZE);
    		if ( HI_SUCCESS != ret )
    		{
    			HI_UNF_CIPHER_DeInit();
    			return HI_FAILURE;
    		}
        }
#else
            ret = HI_UNF_CIPHER_HashUpdate(hHandle, pu8Buf, 1024*1024);
    		if ( HI_SUCCESS != ret )
    		{
    			HI_UNF_CIPHER_DeInit();
    			return HI_FAILURE;
    		}
#endif
        ret = HI_UNF_CIPHER_HashFinal(hHandle, u8Hash);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}
        print_time(__LINE__);
        printBuffer("Sha result:", u8Hash, enHashType == HI_UNF_CIPHER_HASH_TYPE_SHA1 ? 20 : 32);
    }

    HI_ERR_CIPHER("sample SHA1 run successfully!\n");
    HI_UNF_CIPHER_DeInit();
    (HI_VOID)HI_SYS_DeInit();

    return HI_SUCCESS;
}

HI_S32 SHA1()
{
	HI_S32 ret = HI_SUCCESS;
    HI_U8 u8Hash[20];
    HI_U32 i = 0;
    HI_HANDLE hHandle = HI_INVALID_HANDLE;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

	ret = HI_UNF_CIPHER_Init();
	if ( HI_SUCCESS != ret )
	{
		return HI_FAILURE;
	}

    memset(u8Hash, 0, 20);

    for(i = 0; i < 2; i++)
    {
        memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
        stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA1;

        print_time(__LINE__);
        ret = HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}
		
        ret = HI_UNF_CIPHER_HashUpdate(hHandle, sha1_buf[i], sha1_buflen[i]);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}
		
        ret = HI_UNF_CIPHER_HashFinal(hHandle, u8Hash);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}
        print_time(__LINE__);
        if(memcmp(u8Hash, sha1_sum[i], 20) != 0)
        {
            HI_ERR_CIPHER("\033[0;31m" "SHA1 run failed, sample %d!\n" "\033[0m", i);
            printBuffer("golden data:", sha1_sum[i], 20);
            HI_UNF_CIPHER_DeInit();
            return HI_FAILURE;
        }

        printBuffer("Sha1 result:", u8Hash, 20);
    }

    HI_ERR_CIPHER("sample SHA1 run successfully!\n");
    HI_UNF_CIPHER_DeInit();
    (HI_VOID)HI_SYS_DeInit();

    return HI_SUCCESS;
}

HI_S32 SHA256()
{
	HI_S32 ret = HI_SUCCESS;
    HI_U8 u8Hash[32];
    HI_U32 i = 0;
    HI_HANDLE hHandle = HI_INVALID_HANDLE;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

	ret = HI_UNF_CIPHER_Init();
	if ( HI_SUCCESS != ret )
	{
		return HI_FAILURE;
	}

    for(i = 0; i < 2; i++)
    {
        memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
        stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_SHA256;

        ret = HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}

        ret = HI_UNF_CIPHER_HashUpdate(hHandle, sha1_buf[i], sha1_buflen[i]);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}

        ret = HI_UNF_CIPHER_HashFinal(hHandle, u8Hash);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}

        if(memcmp(u8Hash, sha2_sum[i], 32) != 0)
        {
            HI_ERR_CIPHER("\033[0;31m" "SHA256 run failed, sample %d!\n" "\033[0m", i);
			HI_UNF_CIPHER_DeInit();
            return HI_FAILURE;
        }

        printBuffer("Sha256 result:", u8Hash, 32);
    }

    HI_ERR_CIPHER("sample SHA256 run successfully!\n");
    HI_UNF_CIPHER_DeInit();
    return HI_SUCCESS;
}

HI_S32 HMAC_SHA1()
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 u8Hash[20];
    HI_U32 i = 0;
    HI_HANDLE hHandle = HI_INVALID_HANDLE;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

	ret = HI_UNF_CIPHER_Init();
	if ( HI_SUCCESS != ret )
	{
		return HI_FAILURE;
	}

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
	stHashAttr.pu8HMACKey = malloc(16);
	stHashAttr.u32HMACKeyLen = 16;
	if ( NULL == stHashAttr.pu8HMACKey )
	{
	    HI_UNF_CIPHER_DeInit();
		return HI_FAILURE;
	}

    memset(u8Hash, 0, 20);

    for(i = 0; i < 2; i++)
    {
        stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1;
        memcpy(stHashAttr.pu8HMACKey, u8HMACKey, 16);

        ret = HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("hash init failed!\n");
            ret = HI_FAILURE;
            goto __EXIT__;
        }
        
        ret = HI_UNF_CIPHER_HashUpdate(hHandle, sha1_buf[i], sha1_buflen[i]);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("hash update failed!\n");
            ret = HI_FAILURE;
            goto __EXIT__;
        }
        
        ret = HI_UNF_CIPHER_HashFinal(hHandle, u8Hash);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_CIPHER("hash final failed!\n");
            ret = HI_FAILURE;
            goto __EXIT__;
        }

        printBuffer("hmac-Sha1 result:", u8Hash, 20);
    }

    HI_ERR_CIPHER("sample HMAC SHA1 run successfully!\n");

__EXIT__:
	free(stHashAttr.pu8HMACKey);
	stHashAttr.pu8HMACKey = NULL;
    HI_UNF_CIPHER_DeInit();

    return ret;
}


HI_S32 HMAC_SHA256()
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 u8Hash[32];
    HI_U32 i = 0;
    HI_HANDLE hHandle = HI_INVALID_HANDLE;
    HI_UNF_CIPHER_HASH_ATTS_S stHashAttr;

	ret = HI_UNF_CIPHER_Init();
	if ( HI_SUCCESS != ret )
	{
		return HI_FAILURE;
	}

    memset(&stHashAttr, 0, sizeof(HI_UNF_CIPHER_HASH_ATTS_S));
	stHashAttr.pu8HMACKey = malloc(16);
	stHashAttr.u32HMACKeyLen = 16;
	if ( NULL == stHashAttr.pu8HMACKey )
	{
	    HI_UNF_CIPHER_DeInit();
		return HI_FAILURE;
	}
	
    memset(u8Hash, 0, 32);

    for(i = 0; i < 2; i++)
    {
        stHashAttr.eShaType = HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256;
        memcpy(stHashAttr.pu8HMACKey, u8HMACKey, 16);

        ret = HI_UNF_CIPHER_HashInit(&stHashAttr, &hHandle);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}

        ret = HI_UNF_CIPHER_HashUpdate(hHandle, sha1_buf[i], sha1_buflen[i]);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}
		
        ret = HI_UNF_CIPHER_HashFinal(hHandle, u8Hash);
		if ( HI_SUCCESS != ret )
		{
			HI_UNF_CIPHER_DeInit();
			return HI_FAILURE;
		}

        printBuffer("hmac-Sha256 result:", u8Hash, 32);
    }

    HI_ERR_CIPHER("sample HMAC SHA256 run successfully!\n");

__EXIT__:
    free(stHashAttr.pu8HMACKey);
	stHashAttr.pu8HMACKey = NULL;
    HI_UNF_CIPHER_DeInit();

    return HI_SUCCESS;
}


#define MCI_REG_BASE       ((0xF9A00000))
#define CHAN0_CIPHER_DOUT1  (MCI_REG_BASE + 0x00)
#define CHAN0_CIPHER_DOUT2  (MCI_REG_BASE + 0x04)
#define CHAN0_CIPHER_DOUT3  (MCI_REG_BASE + 0x08)
#define CHAN0_CIPHER_DOUT4  (MCI_REG_BASE + 0x0c)
#define HDCP_MODE_CTRL      (MCI_REG_BASE + 0x0820)
#define SEC_CHN_CFG         (MCI_REG_BASE + 0x0824)
#define CHAN0_CIPHER_CTRL   (MCI_REG_BASE + 0x1000)
#define CHAN0_CIPHER_IVIN   (MCI_REG_BASE + 0x1004)
#define CHAN0_CIPHER_DIN1   (MCI_REG_BASE + 0x1014)
#define CHAN0_CIPHER_DIN2   (MCI_REG_BASE + 0x1018)
#define CHAN0_CIPHER_DIN3   (MCI_REG_BASE + 0x101c)
#define CHAN0_CIPHER_DIN4   (MCI_REG_BASE + 0x1020)
#define CHAN0_CFG           (MCI_REG_BASE + 0x1410)

#define  CRG_BASE_ADDR_PHY  ((0xF8A22000))            
#define  MCI_SOFT_RESET_REG (CRG_BASE_ADDR_PHY + 0xC0)

#if 1
#define  WRITE_MCI_REG           HI_SYS_WriteRegister  
#define  READ_MCI_REG            HI_SYS_ReadRegister_tmp

HI_U32 HI_SYS_ReadRegister_tmp(HI_U32 Addr)
{    
      HI_U32 Data;
      HI_SYS_ReadRegister(Addr, &Data);
      return Data;
}


void CipherWriteData(HI_U32 addr, HI_U32 *au32Val)
{
    HI_U32 i;

    for(i=0; i<4; i++)
    {
        WRITE_MCI_REG(addr+i*4,au32Val[i]);
    }
}

void CipherReadData(HI_U32 addr, HI_U32 *au32Val)
{
    HI_U32 i;

    for(i=0; i<4; i++)
    {
        au32Val[i] = READ_MCI_REG(addr+i*4);
    }
}

HI_S32 CipherHdcpKeyInit(HI_U8 *pu8HpcpKey)
{
	HI_S32 ret;
	HI_U32 i,j;
    HI_U32 u32Value;
    HI_U32 u32Key[32][4];

    /*Cipher soft reset*/
    u32Value = READ_MCI_REG(MCI_SOFT_RESET_REG);
    u32Value |= 0x00200;
    WRITE_MCI_REG(MCI_SOFT_RESET_REG,u32Value);
	usleep(20*1000);
    u32Value &= ~0x00200;
	WRITE_MCI_REG(MCI_SOFT_RESET_REG,u32Value);
	usleep(20*1000);

    /*Set mode*/
    u32Value = 0x1;
	WRITE_MCI_REG(HDCP_MODE_CTRL, u32Value);//use otp hdcp root key

    /*Hdcp key encrypt*/
	for(i=0;i<32;i++)
	{

	    /*Set input data*/
    	u32Key[i][0] = (pu8HpcpKey[16*i+3]<<24)|(pu8HpcpKey[16*i+2]<<16)|(pu8HpcpKey[16*i+1]<<8)|((pu8HpcpKey[16*i]<<0));
    	u32Key[i][1] = (pu8HpcpKey[16*i+7]<<24)|(pu8HpcpKey[16*i+6]<<16)|(pu8HpcpKey[16*i+5]<<8)|((pu8HpcpKey[16*i+4]<<0));
    	u32Key[i][2] = (pu8HpcpKey[16*i+11]<<24)|(pu8HpcpKey[16*i+10]<<16)|(pu8HpcpKey[16*i+9]<<8)|((pu8HpcpKey[16*i+8]<<0));
    	u32Key[i][3] = (pu8HpcpKey[16*i+15]<<24)|(pu8HpcpKey[16*i+14]<<16)|(pu8HpcpKey[16*i+13]<<8)|((pu8HpcpKey[16*i+12]<<0));
        CipherWriteData(CHAN0_CIPHER_DIN1, u32Key[i]);

        /*Set ctrl*/
        if(i == 0)
        {
            u32Value = 0x122;
            memset(u32Key[0], 0, 16);
            WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, encrypt
            CipherWriteData(CHAN0_CIPHER_IVIN, u32Key[0]);
        }
        else
        {
            u32Value = 0x22;
            WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, encrypt 
        }

        /*start encrypt*/
        u32Value = 0x01;
        WRITE_MCI_REG(CHAN0_CFG, u32Value);

        /*Wait encrypt end*/
        u32Value = READ_MCI_REG(CHAN0_CFG);
        while(u32Value & 0x02)
        {
            u32Value = READ_MCI_REG(CHAN0_CFG); 
        }

        /*Get result*/
        CipherReadData(CHAN0_CIPHER_DOUT1, u32Key[i]);

        printf("u32Key[%02d]: ", i);
        for(j=0; j<4; j++)
        {
            printf("%08x ", u32Key[i][j]);
        }
        printf("\n");
    }

    u32Value = 0x1;
	WRITE_MCI_REG(HDCP_MODE_CTRL, u32Value);//use otp hdcp root key

    /*Hdcp key decrypt*/
	for(i=0;i<32;i++)
	{
	    /*Set input data*/
    	CipherWriteData(CHAN0_CIPHER_DIN1, u32Key[i]);

        /*Set ctrl*/
        if(i == 0)
        {
            u32Value = 0x123;
            memset(u32Key[0], 0, 16);
            WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, encrypt
            CipherWriteData(CHAN0_CIPHER_IVIN, u32Key[0]);
        }
        else
        {
            u32Value = 0x23;
            WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, encrypt 
        }

        /*start decrypt*/
        u32Value = 0x01;
        WRITE_MCI_REG(CHAN0_CFG, u32Value);//start decrypt

        /*Wait decrypt end*/
        u32Value = READ_MCI_REG(CHAN0_CFG);
        while(u32Value & 0x02)
        {
            u32Value = READ_MCI_REG(CHAN0_CFG); 
        }
    }

    u32Value = 0x2;
	WRITE_MCI_REG(HDCP_MODE_CTRL, u32Value);//use otp hdcp root key

    system("himm 0xF8A2210c 0x433f");
    usleep(20*1000);
    system("himm 0xF8A2210c 0x403f");
    system("himd.l 0xf8ce0028");

	return HI_SUCCESS; 
}
#else

#define  WRITE_MCI_REG_1 HI_SYS_WriteRegister
#define  READ_MCI_REG_1  HI_SYS_ReadRegister_tmp

HI_U32 HI_SYS_ReadRegister_tmp(HI_U32 Addr)
{    
      HI_U32 Data;
      HI_SYS_ReadRegister(Addr, &Data);
      return Data;
}

void WRITE_MCI_REG(HI_U32 addr, HI_U32 val)
{
    HI_U32 u32Value1, u32Value2;
    
    u32Value1 = READ_MCI_REG_1 (addr);
    WRITE_MCI_REG_1(addr, val);
    u32Value2 = READ_MCI_REG_1 (addr);

//    printf("0x%08x: 0x%x - > 0x%x\r\n", addr, u32Value1, u32Value2);
}

HI_U32 READ_MCI_REG(HI_U32 addr)
{
    HI_U32 u32Value;
    u32Value = READ_MCI_REG_1 (addr);

 //   printf("0x%08x: 0x%x\r\n", addr, u32Value);
    
    return u32Value;
}

HI_S32 CipherHdcpKeyInit(HI_U8 *pu8HpcpKey)
{
	HI_S32 ret;
	HI_U32 i;
    HI_U32 u32Value;
    HI_U32 u32KeyResult[32][4];
    HI_U32 u32KeyOrigin[32][4];

    /*Cipher soft reset*/
    u32Value = READ_MCI_REG(MCI_SOFT_RESET_REG);
    u32Value |= 0x00200;
    WRITE_MCI_REG(MCI_SOFT_RESET_REG,u32Value);
    usleep(20*1000);
    u32Value &= ~0x00200;
    WRITE_MCI_REG(MCI_SOFT_RESET_REG,u32Value);
    usleep(20*1000);

    /*channl 0 secure*/    
    u32Value = 0x01;
    WRITE_MCI_REG(SEC_CHN_CFG, u32Value);
    
    /*Set mode*/
    u32Value = 0x1;
    WRITE_MCI_REG(HDCP_MODE_CTRL, u32Value);//use otp hdcp root key

    /*Hdcp key encrypt*/
    for(i=0;i<32;i++)
    {
    /*Set input data*/
    	u32KeyOrigin[i][0] = (pu8HpcpKey[16*i+3]<<24)|(pu8HpcpKey[16*i+2]<<16)|(pu8HpcpKey[16*i+1]<<8)|((pu8HpcpKey[16*i]<<0));
    	u32KeyOrigin[i][1] = (pu8HpcpKey[16*i+7]<<24)|(pu8HpcpKey[16*i+6]<<16)|(pu8HpcpKey[16*i+5]<<8)|((pu8HpcpKey[16*i+4]<<0));
    	u32KeyOrigin[i][2] = (pu8HpcpKey[16*i+11]<<24)|(pu8HpcpKey[16*i+10]<<16)|(pu8HpcpKey[16*i+9]<<8)|((pu8HpcpKey[16*i+8]<<0));
    	u32KeyOrigin[i][3] = (pu8HpcpKey[16*i+15]<<24)|(pu8HpcpKey[16*i+14]<<16)|(pu8HpcpKey[16*i+13]<<8)|((pu8HpcpKey[16*i+12]<<0));
    	WRITE_MCI_REG(CHAN0_CIPHER_DIN1, u32KeyOrigin[i][0]);
        WRITE_MCI_REG(CHAN0_CIPHER_DIN2, u32KeyOrigin[i][1]);
        WRITE_MCI_REG(CHAN0_CIPHER_DIN3, u32KeyOrigin[i][2]);
        WRITE_MCI_REG(CHAN0_CIPHER_DIN4, u32KeyOrigin[i][3]);

        /*Set ctrl*/
        u32Value = 0x22;
        WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, encrypt

        /*start encrypt*/
        u32Value = 0x01;
        WRITE_MCI_REG(CHAN0_CFG, u32Value);

        /*Wait encrypt end*/
        u32Value = READ_MCI_REG(CHAN0_CFG);
        while(u32Value & 0x02)
        {
            u32Value = READ_MCI_REG(CHAN0_CFG); 
        }

        /*Get result*/
    	u32KeyResult[i][0] = READ_MCI_REG(CHAN0_CIPHER_DOUT1);
        u32KeyResult[i][1] = READ_MCI_REG(CHAN0_CIPHER_DOUT2);
        u32KeyResult[i][2] = READ_MCI_REG(CHAN0_CIPHER_DOUT3);
        u32KeyResult[i][3] = READ_MCI_REG(CHAN0_CIPHER_DOUT4);
        
        printf("u32KeyResult[%d][0] 0x%x\r\n", i, u32KeyResult[i][0]);
        printf("u32KeyResult[%d][1] 0x%x\r\n", i, u32KeyResult[i][1]);
        printf("u32KeyResult[%d][2] 0x%x\r\n", i, u32KeyResult[i][2]);
        printf("u32KeyResult[%d][3] 0x%x\r\n", i, u32KeyResult[i][3]);

    }

    /*Hdcp key decrypt*/
    for(i=0;i<32;i++)
    {
        /*Set input data*/
    	u32KeyOrigin[i][0] = u32KeyResult[i][0];
    	u32KeyOrigin[i][1] = u32KeyResult[i][1];
    	u32KeyOrigin[i][2] = u32KeyResult[i][2];
    	u32KeyOrigin[i][3] = u32KeyResult[i][3];
    	WRITE_MCI_REG(CHAN0_CIPHER_DIN1, u32KeyOrigin[i][0]);
        WRITE_MCI_REG(CHAN0_CIPHER_DIN2, u32KeyOrigin[i][1]);
        WRITE_MCI_REG(CHAN0_CIPHER_DIN3, u32KeyOrigin[i][2]);
        WRITE_MCI_REG(CHAN0_CIPHER_DIN4, u32KeyOrigin[i][3]);

        /*Set ctrl*/
        u32Value = 0x23;
        WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, decrypt

        /*start decrypt*/
        u32Value = 0x01;
        WRITE_MCI_REG(CHAN0_CFG, u32Value);//start decrypt

        /*Wait decrypt end*/
        u32Value = READ_MCI_REG(CHAN0_CFG);
        while(u32Value & 0x02)
        {
            u32Value = READ_MCI_REG(CHAN0_CFG); 
        }
    }

    u32Value = 0x02;
    WRITE_MCI_REG(HDCP_MODE_CTRL, u32Value);//tx_read

    /*channl 0 non-secure*/
    u32Value = 0x00;
    WRITE_MCI_REG(SEC_CHN_CFG, u32Value);

        system("himm 0xF8A2210c 0x433f");
    usleep(20*1000);
    system("himm 0xF8A2210c 0x403f");
    system("himd.l 0xf8ce0028");

    return HI_SUCCESS; 
}
#endif


static HI_U8 key[512];

int main(int argc, char* argv[])
{
    
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 funcNumber = 0;
    HI_U32 i = 0;
    HI_U32 total= 0;

    (HI_VOID)HI_SYS_Init();

    if ( 2 != argc )
    {
        HI_INFO_CIPHER("Usage: %s funcNumber\n\n", argv[0]);
        HI_INFO_CIPHER("#########cipher sample##########\n"
                        "[0] SHA1\n"
                        "[1] SHA256\n"
                        "[2] HMAC-SHA1\n"
                        "[3] HMAC-SHA256\n");
	    (HI_VOID)HI_SYS_DeInit();
        return HI_SUCCESS;
    }
    funcNumber = strtol(argv[1],NULL,0);
    
	if ( 0 == funcNumber )
    {
        s32Ret = SHA1();
    }
    else if ( 1 == funcNumber )
    {
        s32Ret = SHA256();
    }
    else if ( 2 == funcNumber )
    {
        s32Ret = HMAC_SHA1();
    }
    else if ( 3 == funcNumber )
    {
        s32Ret = HMAC_SHA256();
    }
    else if( 4 == funcNumber )
    {
        memset(key, 0x00, 512);
        key[511] = 0xFF;
        s32Ret = CipherHdcpKeyInit(key);
    }
    else if( 5 == funcNumber )
    {
        Capacity(HI_UNF_CIPHER_HASH_TYPE_SHA1);
        Capacity(HI_UNF_CIPHER_HASH_TYPE_SHA256);
    }
    else    
    {      
        HI_INFO_CIPHER("funcNumber %d do not exist!\n",funcNumber);
    }

    (HI_VOID)HI_SYS_DeInit();

    if(HI_SUCCESS != s32Ret)
    {        
        HI_INFO_CIPHER("funcNumber %d run failure.\n",funcNumber);        
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

