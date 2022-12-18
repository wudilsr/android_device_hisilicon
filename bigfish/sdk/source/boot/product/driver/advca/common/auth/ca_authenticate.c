/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : ca_authenticate.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "ca_authenticate.h"
#include "drv_cipher_intf.h"
#include "ca_common.h"

#ifndef HI_ADVCA_TYPE_VERIMATRIX
#include "alg.h"
#endif

#ifdef HI_MINIBOOT_SUPPORT
#include "run.h"
#include "config.h"
#include "platform.h"
#else
#include "exports.h"
#endif

#include "loaderdb_info.h"
#include "hi_unf_advca.h"
#include "hi_unf_cipher.h"
#include "hi_unf_otp.h"
#include "malloc.h"
#include "ca_flash.h"

/* for printf: */
#undef printf
#include "ca_authdefine.h"
#include "ca_flash.h"
/* for printf end */

#ifndef HI_ADVCA_TYPE_VERIMATRIX

#define SPARSE_EXT4

#ifdef SPARSE_EXT4
#include "sparse.h"
#define SYSTEM_SIGN_PARTITION  "systemsign"
#define SYSTEM_IMG_PARTITION  "system"

HI_U32 IsSparseFlag = 0xFF;  /* 0->init, 1->sparse, 2->not sparse */
HI_U32 *pSignChunkInfo = HI_NULL;
sparse_header_t *pSparseHead = HI_NULL;
sign_chunk_header_t *pChunkHead = HI_NULL;
#endif


#define MAX_STRLEN(a, b) ((strlen(a) > strlen(b)) ? strlen(a) : strlen(b))
#define CFG_TIMERBASE23         REG_BASE_TIMER23
#define CFG_TIMER2_CTRL         0xC2
#define READ_TIMER2         \
     (*(volatile unsigned long *)(CFG_TIMERBASE23 + REG_TIMER_VALUE))

static HI_VOID printf_hex(HI_U8 *pu8Buf, HI_U32 u32Length)
{
    HI_U32 i;

    for(i = 0; i < u32Length; i++)
    {
        if(i % 16 == 0 && i != 0)
        {
            HI_SIMPLEINFO_CA("\n");
        }
        HI_SIMPLEINFO_CA("0x%02X, ", pu8Buf[i]);
    }
    HI_SIMPLEINFO_CA("\n");

    return;
}

/* trivial congruential random generators. from glibc. */
static unsigned long rstate = 1;
static void ca_srandom(unsigned long seed)
{
    rstate = seed ? seed : 1;  /* dont allow a 0 seed */
}

static unsigned long ca_random(void)
{
    unsigned int next = rstate;
    int result;

    next *= 1103515245;
    next += 12345;
    result = (unsigned int) (next / 65536) % 2048;

    next *= 1103515245;
    next += 12345;
    result <<= 10;
    result ^= (unsigned int) (next / 65536) % 1024;

    next *= 1103515245;
    next += 12345;
    result <<= 10;
    result ^= (unsigned int) (next / 65536) % 1024;

    rstate = next;

    return result;
}

#ifndef HI_MINIBOOT_SUPPORT
extern int do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
#endif

extern HI_S32  c51_loadCode(void);
extern void sha1( const unsigned char *input, int ilen, unsigned char output[20] );

extern HI_S32 Logo_Main(HI_VOID);

static HI_U32 CipherBlockSize = 1024*1024-16;   //cipher block must < 1M BYTE and be times of 16BYTE
#if 0
static HI_U8 G1_CIPHERKEY[16] = "Hisilicon_cipher";
static HI_U8 G2_CIPHERKEY[16] = "Hisilicon_second";
static HI_U8 G1_KEYLADDER_KEY1[16] = "auth1_keyladder1";
static HI_U8 G1_KEYLADDER_KEY2[16] = "auth1_keyladder2";
static HI_U8 G2_KEYLADDER_KEY1[16] = "auth2_keyladder1";
static HI_U8 G2_KEYLADDER_KEY2[16] = "auth2_keyladder2";
static HI_U8 CAIMGHEAD_MAGICNUMBER[32]  =  "Hisilicon_ADVCA_ImgHead_MagicNum";
#else
static HI_U8 G1_CIPHERKEY[16]      = {0x5b,0x45,0x14,0x37,0x6d,0xed,0x1d,0x08,0x64,0x97,0xbc,0xba,0xe6,0x7f,0x90,0x78};
static HI_U8 G2_CIPHERKEY[16]      = {0xd6,0xbc,0x9e,0xe2,0x3a,0x61,0x50,0x10,0xb4,0x64,0x2e,0xaa,0xe8,0xf0,0x53,0xa6};
static HI_U8 G1_KEYLADDER_KEY1[16] = {0x1c,0x21,0x42,0xa2,0x9e,0x31,0x57,0x8d,0xff,0xa4,0xe1,0xdf,0x2e,0x36,0xa0,0x6e};
static HI_U8 G1_KEYLADDER_KEY2[16] = {0x7c,0x76,0x1a,0x38,0xc1,0x46,0x4e,0x53,0x8c,0xa3,0xd7,0xae,0x56,0xee,0x27,0xb7};
static HI_U8 G2_KEYLADDER_KEY1[16] = {0x41,0x98,0x30,0x77,0x14,0xed,0x9d,0xc3,0x60,0x55,0x49,0xcf,0x5e,0x75,0x13,0xa2};
static HI_U8 G2_KEYLADDER_KEY2[16] = {0x5c,0x98,0xbe,0x7c,0x52,0x24,0x35,0xb8,0x30,0xa5,0x10,0x54,0x33,0xc3,0x21,0xf8};
static HI_U8 CAIMGHEAD_MAGICNUMBER[32]  =  {0};
#endif
static HI_U8 CAIMGHEAD_VERSION[8] = "v1.0.0.3";
static HI_U32 u32ConfigEnvSize = CONFIG_ENV_SIZE;   //CFG_ENV_SIZE;
static HI_HANDLE  g_hCipher = -1;

extern HI_U8 CA_VENDOR[];
extern HI_U32 g_MaxBlockSize;
extern HI_U8 *env_ptr;
extern HI_U32 g_EnvFlashPartionSize;
extern HI_U32 g_EnvBakFlashAddr;
extern HI_U32 g_MaxBlockSize;
extern HI_BOOL isCipherkeyByCA;
extern HI_UNF_CIPHER_ALG_E g_CipherAlg;
extern HI_U8  g_customer_rsa_public_key_N[256];
extern HI_U32  g_customer_rsa_public_key_E;
extern HI_U32 g_DDRSize ;
extern AUTHALG_E g_AuthAlg ;
extern HI_U8  g_customer_blpk[16];
extern HI_U32 g_EnvFlashAddr;
HI_U8  g_partition_hash[96] = {0};

unsigned long DVB_CRC32(unsigned char *buf, int length);

HI_VOID CA_Reset(HI_VOID)
{
    HI_INFO_CA(" \n");
    do_reset (NULL, 0, 0, NULL);
    do_reset (NULL, 0, 0, NULL);
    do_reset (NULL, 0, 0, NULL);
    while(1) { };
}

void showtime(HI_U32 n,HI_U32*  oldtime,HI_U32* newtime)
{
    HI_U32 timeuse = 0;
    *newtime = get_timer(0);
    timeuse= (*newtime - *oldtime)/get_tbclk();
    HI_DEBUG_CA("%d\n", n);
    HI_DEBUG_CA(" Time use :%d s\n",timeuse);
    *oldtime = *newtime;
}
HI_VOID DumpImgHead(HI_CAImgHead_S* ImgInfo)
{
    HI_DEBUG_CA("ImgInfo->u8MagicNumber = %s\n",ImgInfo->u8MagicNumber);
    HI_DEBUG_CA("ImgInfo->u32TotalLen = 0x%x\n",ImgInfo->u32TotalLen);
}

HI_VOID GenerateMagicNum(HI_VOID)
{
    CAIMGHEAD_MAGICNUMBER[0] = 'H';
    CAIMGHEAD_MAGICNUMBER[1] = 'i';
    CAIMGHEAD_MAGICNUMBER[2] = 's';
    CAIMGHEAD_MAGICNUMBER[3] = 'i';
    CAIMGHEAD_MAGICNUMBER[4] = 'l';
    CAIMGHEAD_MAGICNUMBER[5] = 'i';
    CAIMGHEAD_MAGICNUMBER[6] = 'c';
    CAIMGHEAD_MAGICNUMBER[7] = 'o';
    CAIMGHEAD_MAGICNUMBER[8] = 'n';
    CAIMGHEAD_MAGICNUMBER[9] = '_';
    CAIMGHEAD_MAGICNUMBER[10] = 'A';
    CAIMGHEAD_MAGICNUMBER[11] = 'D';
    CAIMGHEAD_MAGICNUMBER[12] = 'V';
    CAIMGHEAD_MAGICNUMBER[13] = 'C';
    CAIMGHEAD_MAGICNUMBER[14] = 'A';
    CAIMGHEAD_MAGICNUMBER[15] = '_';
    CAIMGHEAD_MAGICNUMBER[16] = 'I';
    CAIMGHEAD_MAGICNUMBER[17] = 'm';
    CAIMGHEAD_MAGICNUMBER[18] = 'g';
    CAIMGHEAD_MAGICNUMBER[19] = 'H';
    CAIMGHEAD_MAGICNUMBER[20] = 'e';
    CAIMGHEAD_MAGICNUMBER[21] = 'a';
    CAIMGHEAD_MAGICNUMBER[22] = 'd';
    CAIMGHEAD_MAGICNUMBER[23] = '_';
    CAIMGHEAD_MAGICNUMBER[24] = 'M';
    CAIMGHEAD_MAGICNUMBER[25] = 'a';
    CAIMGHEAD_MAGICNUMBER[26] = 'g';
    CAIMGHEAD_MAGICNUMBER[27] = 'i';
    CAIMGHEAD_MAGICNUMBER[28] = 'c';
    CAIMGHEAD_MAGICNUMBER[29] = 'N';
    CAIMGHEAD_MAGICNUMBER[30] = 'u';
    CAIMGHEAD_MAGICNUMBER[31] = 'm';
}

HI_S32 CA_AuthenticateInit(HI_CA_KEY_GROUP_E enKeyGroup)
{
    HI_S32 ret = 0;
    HI_U8  SessionKey1[16];
    HI_U8  SessionKey2[16];
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_UNF_CIPHER_ATTS_S stCipherAtts;

    /*Generate the magic number*/
    GenerateMagicNum();

    memset(SessionKey1,0,sizeof(SessionKey1));
    memset(SessionKey2,0,sizeof(SessionKey2));
    memset(&CipherCtrl,0,sizeof(HI_UNF_CIPHER_CTRL_S));

    /*open and config keyladder*/
    CA_ASSERT(HI_UNF_CIPHER_Init(),ret);

    HI_UNF_ADVCA_Init();

    CA_ASSERT(CA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_AES),ret);
    CA_ASSERT(CA_GetR2RLadder(&enStage),ret);

    if (HI_CA_KEY_GROUP_1 == enKeyGroup)
    {
        memcpy(SessionKey1, G1_KEYLADDER_KEY1, sizeof(SessionKey1));
        memcpy(SessionKey2, G1_KEYLADDER_KEY2, sizeof(SessionKey2));
        memcpy(CipherCtrl.u32Key,G1_CIPHERKEY,16);
    }
    else
    {
        memcpy(SessionKey1, G2_KEYLADDER_KEY1, sizeof(SessionKey1));
        memcpy(SessionKey2, G2_KEYLADDER_KEY2, sizeof(SessionKey2));
        memcpy(CipherCtrl.u32Key,G2_CIPHERKEY,16);
    }

    CA_ASSERT(HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV1,SessionKey1),ret);
    if(enStage == HI_UNF_ADVCA_KEYLADDER_LEV3)
    {
        CA_ASSERT(HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV2,SessionKey2),ret);
    }

    /*config cipher*/
    memset(&stCipherAtts, 0, sizeof(HI_UNF_CIPHER_ATTS_S));
    stCipherAtts.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    CA_ASSERT(HI_UNF_CIPHER_CreateHandle(&g_hCipher, &stCipherAtts),ret);

    if(HI_TRUE == isCipherkeyByCA)
    {
        CipherCtrl.bKeyByCA = isCipherkeyByCA;
    }
    else
    {
        CipherCtrl.bKeyByCA = HI_FALSE;
    }

    if(HI_UNF_CIPHER_ALG_3DES == g_CipherAlg)
    {
        CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_3DES;
        CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
    }
    else if(HI_UNF_CIPHER_ALG_DES == g_CipherAlg)
    {
        CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_DES;
        CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_64BIT;
        CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
    }
    else if(HI_UNF_CIPHER_ALG_AES == g_CipherAlg)
    {
        CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
        CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    }
    else
    {
        HI_ERR_CA("Cipher Algorithem error\n");
        return -1;
    }

    CA_ASSERT(HI_UNF_CIPHER_ConfigHandle(g_hCipher,&CipherCtrl),ret);
    return ret;
}

HI_VOID CA_AuthenticateDeInit(HI_VOID)
{
    HI_UNF_CIPHER_DestroyHandle(g_hCipher);
    HI_UNF_CIPHER_DeInit();
}

HI_S32 CA_DataEncrypt(HI_U8 *pPlainText, HI_U32 TextLen, HI_U8 *pCipherText)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 CipherBlockNum = 0;
    HI_U32 index = 0;

    CA_CheckPointer(pPlainText);
    CA_CheckPointer(pCipherText);

    if(-1 == g_hCipher)
    {
        HI_ERR_CA("call CA_AuthenticateInit first\n");
        return ret;
    }
    if((TextLen < 16) || (TextLen%16 != 0))
    {
        HI_ERR_CA("Data length must be times of 16BYTE\n");
        return ret;
    }
    CipherBlockNum = TextLen/CipherBlockSize;
    if(CipherBlockNum > 0)
    {
        for(index = 0;index <CipherBlockNum;index++)
        {
            CA_ASSERT(HI_UNF_CIPHER_Encrypt(g_hCipher,((HI_U32)pPlainText+index*CipherBlockSize),((HI_U32)pCipherText+index*CipherBlockSize),CipherBlockSize),ret);
        }
        if(TextLen > index*CipherBlockSize)
        {
            CA_ASSERT(HI_UNF_CIPHER_Encrypt(g_hCipher,((HI_U32)pPlainText+index*CipherBlockSize),((HI_U32)pCipherText+index*CipherBlockSize),(TextLen-index*CipherBlockSize)),ret);
        }
    }
    else
    {
        CA_ASSERT(HI_UNF_CIPHER_Encrypt(g_hCipher,(HI_U32)pPlainText,(HI_U32)pCipherText,TextLen),ret);
    }
    return ret;
}
HI_S32 CA_DataDecrypt(HI_U8 *pCipherText, HI_U32 TextLen, HI_U8 *pPlainText)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 CipherBlockNum = 0;
    HI_U32 index = 0;

    CA_CheckPointer(pPlainText);
    CA_CheckPointer(pCipherText);
    if(-1 == g_hCipher)
    {
        HI_ERR_CA("call CA_AuthenticateInit first\n");
        return ret;
    }
    if((TextLen < 16) || (TextLen%16 != 0))
    {
        HI_ERR_CA("Data length must be times of 16BYTE\n");
        return ret;
    }
    CipherBlockNum = TextLen/CipherBlockSize;
    if(CipherBlockNum > 0)
    {
        for(index = 0;index <CipherBlockNum;index++)
        {
            CA_ASSERT(HI_UNF_CIPHER_Decrypt(g_hCipher,((HI_U32)pCipherText+index*CipherBlockSize),((HI_U32)pPlainText+index*CipherBlockSize),CipherBlockSize),ret);
        }
        if(TextLen > index*CipherBlockSize)
        {
            CA_ASSERT(HI_UNF_CIPHER_Decrypt(g_hCipher,((HI_U32)pCipherText+index*CipherBlockSize),((HI_U32)pPlainText+index*CipherBlockSize),(TextLen-index*CipherBlockSize)),ret);
        }
    }
    else
    {
        CA_ASSERT(HI_UNF_CIPHER_Decrypt(g_hCipher,(HI_U32)pCipherText,(HI_U32)pPlainText,TextLen),ret);
    }
    return ret;
}
HI_S32 auth(rsa_context *rsa, HI_U8* BlockStartAddr, HI_S32 Blocklength, HI_U8* sign)
{
    HI_S32 ret;
    CA_CheckPointer(rsa);
    CA_CheckPointer(BlockStartAddr);
    CA_CheckPointer(sign);

    HI_U8 hash[32];
    memset(hash,0,sizeof(hash));

    if(AUTH_SHA2 == g_AuthAlg)
    {
        sha2(BlockStartAddr, Blocklength, hash,0);
        ret = rsa_pkcs1_verify( rsa, RSA_PUBLIC, SIG_RSA_SHA256, 32, hash, sign);
    }
    else
    {
        sha1( BlockStartAddr, Blocklength, hash);
        ret = rsa_pkcs1_verify( rsa, RSA_PUBLIC, SIG_RSA_SHA1, 20, hash, sign);
    }
    return ret;
}
HI_S32 Getkey(rsa_context *rsa, HI_U8* base)
{
    HI_S32 ret;

    rsa_init( rsa, RSA_PKCS_V15, 0 );
    /* get N and E */
    CA_ASSERT( mpi_read_binary( &rsa->N, base, RSA_2048_LEN),ret);
    CA_ASSERT( mpi_read_binary( &rsa->E, base + RSA_2048_LEN, RSA_2048_LEN),ret);
    rsa->len = ( mpi_msb( &rsa->N ) + 7 ) >> 3;
    return ret;
}
HI_S32 CA_Getkey(rsa_context *rsa,HI_U8 *N,HI_U32 E)
{
    HI_U8   base[512];
    memset(base,0,sizeof(base));
    HI_U8 customer_rsa_public_key_E_100001[256] = {
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x01
            };

    HI_U8 customer_rsa_public_key_E_10001[256] = {
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01
            };

    HI_U8 customer_rsa_public_key_E_3[256] = {
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03
            };

    if(NULL == N)
    {
        return -1;
    }
    memcpy(base,N,256);
    if(0x100001 == E)
    {
        memcpy(base + 256,customer_rsa_public_key_E_100001,256);
    }
    else if(0x10001 == E)
    {
        memcpy(base + 256,customer_rsa_public_key_E_10001,256);
    }
    else if(0x3 == E)
    {
        memcpy(base + 256,customer_rsa_public_key_E_3,256);
    }
    else
    {
        return -1;
    }
    return Getkey(rsa, base);
}

HI_U8* CA_GetEnvPtr(HI_VOID)
{
    return (HI_U8*)env_ptr;/*UBOOT use this address as env addr */
}

HI_VOID CA_SetEnv(HI_CHAR* args)
{
    HI_CHAR* s;
    HI_CHAR buf[4096];
    memset(buf,0,sizeof(buf));
    if((s = getenv(args)) != NULL)
    {
        HI_DEBUG_CA("%s = %s\n",args,s);
        snprintf(buf, sizeof(buf), "%s", s);
        setenv(args,buf);
    }
}

HI_S32 CA_ReadUpgrdFlag(HI_BOOL *pbNeedUpgrd)
{
    HI_S32 ret = HI_SUCCESS;
    UPGRD_PARA_HEAD_S *pstParamHead;
    UPGRD_TAG_PARA_S  pstUpgrdParam;
    HI_HANDLE hFlash = HI_INVALID_HANDLE;
    HI_Flash_InterInfo_S stFlashInfo;
    HI_U32 u32CRC32Value = 0;

    CA_CheckPointer(pbNeedUpgrd);

    /*Read loaderdb partition*/
    hFlash = HI_Flash_Open(HI_FLASH_TYPE_BUTT, LOADER_INFOBASIC, 0, 0);
    if(HI_INVALID_HANDLE == hFlash)
    {
        HI_ERR_CA("HI_Flash_Open() %s error, result %x!\n",LOADER_INFOBASIC,ret);
        return HI_FAILURE;
    }

    ret = HI_Flash_GetInfo(hFlash, &stFlashInfo);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("HI_Flash_GetInfo() error, result %x!\n",ret);
        (HI_VOID)HI_Flash_Close(hFlash);
        return ret;
    }

    ret = HI_Flash_Read(hFlash, 0ULL, (HI_U8*)IMG_VERIFY_ADDRESS, stFlashInfo.BlockSize, HI_FLASH_RW_FLAG_RAW);
    if (ret <= 0)
    {
        HI_ERR_CA("HI_Flash_Read partion %s error\n", LOADER_INFOBASIC);
        HI_Flash_Close(hFlash);
        return HI_FAILURE;
    }
    HI_Flash_Close(hFlash);

    /*loaderdb should use G2 to decrypt*/
    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_2),ret);
    CA_ASSERT(CA_DataDecrypt((HI_U8 *)IMG_VERIFY_ADDRESS,stFlashInfo.BlockSize,(HI_U8 *)IMG_VERIFY_ADDRESS),ret);

    pstParamHead = (UPGRD_PARA_HEAD_S *)IMG_VERIFY_ADDRESS;

    /* Verify Magic Number */
    if ( LOADER_MAGIC_NUMBER == pstParamHead->u32MagicNumber)
    {
        if( pstParamHead->u32Length < stFlashInfo.BlockSize )
        {
            /* Veriry CRC value */
            u32CRC32Value = crc32(0, (HI_U8 *)(IMG_VERIFY_ADDRESS + sizeof(HI_U32) * 2),
                           (pstParamHead->u32Length + sizeof(HI_U32)));
            if (u32CRC32Value == pstParamHead->u32Crc)
            {
                HI_INFO_CA("Get upgrade tag info from loderdb successfully.\n");
                memcpy(&pstUpgrdParam, (void *)(IMG_VERIFY_ADDRESS + sizeof(UPGRD_PARA_HEAD_S)),
                       sizeof(UPGRD_TAG_PARA_S));
                *pbNeedUpgrd = pstUpgrdParam.bTagNeedUpgrd;
                return HI_SUCCESS;
            }
            else
            {
                HI_ERR_CA("Check CRC for loaderdb failed u32CRC32Value %x != pstParamHead->u32Crc %x!\n", u32CRC32Value, pstParamHead->u32Crc);
            }
        }
        else
        {
            HI_ERR_CA("Read loaderdb value failed!\n");
        }
    }
    else
    {
        HI_ERR_CA("Check Magic Number for loaderdb failed!\n");
    }

    CA_AuthenticateDeInit();
    return HI_FAILURE;
}

HI_S32 CA_nand_env_relocate_spec(HI_U8 *u8EnvAddr)
{
    HI_U8* pGlobalEnvPtr = NULL;
    CA_CheckPointer(u8EnvAddr);

    pGlobalEnvPtr = CA_GetEnvPtr();

    memset(pGlobalEnvPtr, 0, u32ConfigEnvSize);
    memcpy(pGlobalEnvPtr, u8EnvAddr, u32ConfigEnvSize);

    CA_SetEnv("bootargs");
    CA_SetEnv("loaderargs");

#ifndef  HI_ADVCA_FUNCTION_RELEASE
//    CA_SetEnv("bootcmd");
    CA_SetEnv("ipaddr");
    CA_SetEnv("serverip");
    CA_SetEnv("gatewayip");
    CA_SetEnv("netmask");
    CA_SetEnv("ethaddr");
#endif

    return 0;
}

HI_U32 HI_CA_ImgAuthenticate(HI_U32 StartAddr,HI_U32 length,HI_U8 u8Signature[RSA_2048_LEN])
{
    HI_S32 ret = 0;
    rsa_context customer_key;

    memset(&customer_key,0,sizeof(customer_key));
    CA_ASSERT(CA_Getkey(&customer_key,g_customer_rsa_public_key_N,g_customer_rsa_public_key_E),ret);

    dcache_enable(g_DDRSize);
    ret = auth(&customer_key,(HI_U8 *)StartAddr,length,u8Signature);
    dcache_disable();

    rsa_free(&customer_key);

    return ret;
}

HI_S32 HI_CA_EncryptDDRImageAndBurnFlashAddr(HI_U8* pImageDDRAddress, HI_U32 PartionAddr)
{
    HI_S32 ret = 0;
    HI_U32 FlashWriteSize = 0 ;
    HI_CAImgHead_S ImgInfo;

    memset(&ImgInfo, 0, sizeof(HI_CAImgHead_S));
    memcpy(&ImgInfo, pImageDDRAddress, sizeof(HI_CAImgHead_S));

    if(memcmp(ImgInfo.u8MagicNumber,CAIMGHEAD_MAGICNUMBER,sizeof(ImgInfo.u8MagicNumber)))
    {
        HI_ERR_CA("Img format error\n");
        return -1;
    }

    CA_ASSERT(CA_DataEncrypt(pImageDDRAddress,ImgInfo.u32TotalLen,pImageDDRAddress),ret);

    FlashWriteSize = (ImgInfo.u32TotalLen + g_MaxBlockSize - 1)& (~(g_MaxBlockSize -1) );
    memset(pImageDDRAddress + ImgInfo.u32TotalLen, 0xff, FlashWriteSize - ImgInfo.u32TotalLen);

    CA_ASSERT(CA_flash_write_addr(PartionAddr, FlashWriteSize, pImageDDRAddress),ret);
    HI_INFO_CA("Img has been encrypted by SBP img encrypt process and write back to flash address = 0x%x\n",PartionAddr);

    CA_ASSERT(CA_DataDecrypt(pImageDDRAddress,ImgInfo.u32TotalLen,pImageDDRAddress),ret);

    return 0;

}

HI_S32 HI_CA_EncryptDDRImageAndBurnFlashName(HI_U8* pImageDDRAddress, HI_CHAR* pPartionName)
{
    HI_S32 ret = 0;
    HI_U32 FlashWriteSize = 0 ;
    HI_CAImgHead_S ImgInfo;

    memset(&ImgInfo, 0, sizeof(HI_CAImgHead_S));

    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);

    memcpy(&ImgInfo, pImageDDRAddress, sizeof(HI_CAImgHead_S));
     if(memcmp(ImgInfo.u8MagicNumber,CAIMGHEAD_MAGICNUMBER,sizeof(ImgInfo.u8MagicNumber)))
    {
        HI_ERR_CA("Img format error\n");

        HI_INFO_CA("ImgInfo.u8MagicNumber:\n", ImgInfo.u8MagicNumber);
        printf_hex(ImgInfo.u8MagicNumber, sizeof(ImgInfo.u8MagicNumber));

        HI_INFO_CA("CAIMGHEAD_MAGICNUMBER:\n", CAIMGHEAD_MAGICNUMBER);
        printf_hex(CAIMGHEAD_MAGICNUMBER, sizeof(CAIMGHEAD_MAGICNUMBER));

        return -1;
    }

    CA_ASSERT(CA_DataEncrypt(pImageDDRAddress, ImgInfo.u32TotalLen, pImageDDRAddress),ret);

    FlashWriteSize = (ImgInfo.u32TotalLen + g_MaxBlockSize - 1)& (~(g_MaxBlockSize -1) );
    memset(pImageDDRAddress + ImgInfo.u32TotalLen ,0xff,FlashWriteSize - ImgInfo.u32TotalLen);

    CA_ASSERT(CA_flash_write(pPartionName, 0ULL, FlashWriteSize,pImageDDRAddress),ret);
    HI_INFO_CA("Img has been encrypted by SBP img encrypt process and write back to flash\n");

    CA_ASSERT(CA_DataDecrypt(pImageDDRAddress,ImgInfo.u32TotalLen,pImageDDRAddress),ret);

    CA_AuthenticateDeInit();
    return 0;

}

HI_S32 HI_CA_EncryptDDRImageAndBurnFlashNameByLen(HI_U8* pImageDDRAddress, HI_U32 u32Len, HI_CHAR* pPartionName)
{
    HI_S32 ret = 0;
    HI_U32 FlashWriteSize = 0 ;

    u32Len = (u32Len + NAND_PAGE_SIZE - 1)& (~(NAND_PAGE_SIZE -1) );
    /*loaderdb should use G2 to encrypt*/
    if (0 == strncmp(pPartionName, (HI_CHAR *)LOADER_INFOBASIC, MAX_STRLEN(pPartionName, LOADER_INFOBASIC)))
    {
        HI_INFO_CA("Img has been encrypted using G2 key\n");
        CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_2),ret);
    }
    else
    {
        HI_INFO_CA("Img has been encrypted using G1 key\n");
        CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);
    }

    CA_ASSERT(CA_DataEncrypt(pImageDDRAddress,u32Len,pImageDDRAddress),ret);

    FlashWriteSize = (u32Len + g_MaxBlockSize - 1)& (~(g_MaxBlockSize -1) );
    memset(pImageDDRAddress + u32Len ,0xff,FlashWriteSize - u32Len);

    CA_ASSERT(CA_flash_write(pPartionName, 0ULL, FlashWriteSize,pImageDDRAddress),ret);
    HI_INFO_CA("Img has been encrypted by SBP img encrypt process and write back to flash\n");

    CA_ASSERT(CA_DataDecrypt(pImageDDRAddress,u32Len,pImageDDRAddress),ret);

    CA_AuthenticateDeInit();
    return 0;

}

HI_S32 HI_CA_GetFlashImgInfoByName(HI_U8* pPartionName, HI_CAImgHead_S* pstImgInfo, HI_BOOL *pIsEncrypt)
{
    HI_S32 ret = 0;
    HI_U8 CAImageArea[CAImgHeadAreaLen] = {0};
    HI_U32 u32CRC32Value = 0;
    HI_Flash_InterInfo_S flashInfo;

    CA_CheckPointer(pPartionName);
    CA_ASSERT(CA_flash_read((HI_CHAR*)pPartionName, 0ULL, NAND_PAGE_SIZE,(HI_U8*)CAImageArea, &flashInfo),ret);
    memcpy(pstImgInfo,CAImageArea,sizeof(HI_CAImgHead_S));
    if(!memcmp(pstImgInfo->u8MagicNumber,CAIMGHEAD_MAGICNUMBER,sizeof(pstImgInfo->u8MagicNumber)))
    {
        HI_INFO_CA("Img has not be encrypted\n");
        *pIsEncrypt = HI_FALSE;
    }
    else
    {
        CA_ASSERT(CA_DataDecrypt(CAImageArea,CAImgHeadAreaLen,CAImageArea),ret);
        udelay(100000);//wait fo decrypt end,this code is essential
        memcpy(pstImgInfo,CAImageArea,sizeof(HI_CAImgHead_S));
        if(!memcmp(pstImgInfo->u8MagicNumber,CAIMGHEAD_MAGICNUMBER,sizeof(pstImgInfo->u8MagicNumber)))
        {
            HI_INFO_CA("Img has be encrypted\n");
            *pIsEncrypt = HI_TRUE;
        }
        else
        {
            HI_INFO_CA("Magic number err, get Img information failed\n");
            return -1;
        }
    }

    HI_INFO_CA("ImgInfo.u8MagicNumber:\n", pstImgInfo->u8MagicNumber);
    printf_hex(pstImgInfo->u8MagicNumber, sizeof(pstImgInfo->u8MagicNumber));

    HI_INFO_CA("Magic number check success\n");

    /*Check if the total length is valid*/
    if ((pstImgInfo->u32TotalLen > (HI_U32)flashInfo.PartSize) || (pstImgInfo->u32TotalLen < NAND_PAGE_SIZE))
    {
        HI_ERR_CA("The total length of image %d invalid!\n", pPartionName);
        return -1;
    }

    /*Check if the other lengthes of the header are valid*/
    if ((pstImgInfo->u32CodeOffset != NAND_PAGE_SIZE) || (pstImgInfo->u32SignedImageLen == 0) || (pstImgInfo->u32SignedImageLen > pstImgInfo->u32TotalLen) ||
            (pstImgInfo->u32SignatureOffset == 0) || (pstImgInfo->u32SignatureOffset > pstImgInfo->u32TotalLen))
    {
        HI_ERR_CA("The header data of image %d invalid!\n", pPartionName);
        return -1;
    }

    //Clacluate CRC32!
    u32CRC32Value = DVB_CRC32((HI_U8 *)pstImgInfo, (sizeof(HI_CAImgHead_S) - 4));
    if(u32CRC32Value == pstImgInfo->u32CRC32)
    {
        HI_INFO_CA("CRC32 check ok\n");
    }
    else
    {
        HI_ERR_CA("CRC32Value:%x != pstImgInfo->CRC32:%x\n", u32CRC32Value, pstImgInfo->u32CRC32);
        return -1;
    }

    return 0;
}

HI_S32 HI_CA_DecryptFlashImage2DDR(HI_CHAR* pPartionName)
{
    HI_S32 ret = 0;
    HI_CAImgHead_S ImgInfo;
    HI_BOOL IsEncrypt = HI_TRUE;

    CA_CheckPointer(pPartionName);

    memset(&ImgInfo, 0, sizeof(HI_CAImgHead_S));

    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);

    CA_ASSERT(HI_CA_GetFlashImgInfoByName((HI_U8 *)pPartionName, &ImgInfo, &IsEncrypt),ret);

    CA_ASSERT(CA_flash_read((HI_CHAR*)pPartionName,0ULL, ImgInfo.u32TotalLen, (HI_U8*)IMG_VERIFY_ADDRESS, HI_NULL),ret);
    if (HI_TRUE == IsEncrypt)
    {
        CA_ASSERT(CA_DataDecrypt((HI_U8 *)IMG_VERIFY_ADDRESS, ImgInfo.u32TotalLen, (HI_U8 *)IMG_VERIFY_ADDRESS),ret);
    }
    
    if(memcmp(ImgInfo.u8MagicNumber,CAIMGHEAD_MAGICNUMBER,sizeof(ImgInfo.u8MagicNumber)))
    {
        HI_ERR_CA("Img format error\n");
        return -1;
    }

    CA_AuthenticateDeInit();

    return ret;
}

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
HI_U32 HI_CA_GetAuthMode(HI_U8* pPartionName)
{
    HI_S32 ret = 0;
    HI_U8 CAImageArea[CAImgHeadAreaLen] = {0};
    HI_Flash_InterInfo_S flashInfo;
    HI_CAImgHead_S stImgInfo;

    CA_CheckPointer(pPartionName);
    GenerateMagicNum();
    CA_ASSERT(CA_flash_read((HI_CHAR*)pPartionName, 0ULL, NAND_PAGE_SIZE,(HI_U8*)CAImageArea, &flashInfo),ret);
    memcpy(&stImgInfo,CAImageArea,sizeof(HI_CAImgHead_S));

    if(!memcmp(stImgInfo.u8MagicNumber,CAIMGHEAD_MAGICNUMBER,sizeof(stImgInfo.u8MagicNumber)))
    {
        HI_INFO_CA("Special Signature!\n");
        return SPECIAL_MODE;
    }
    else
    {
        HI_INFO_CA("Common Signature!\n");
        return COMMON_MODE;
    }
}
#endif


HI_S32 HI_CA_FlashAuthenticateByName(HI_U8* pPartionName,HI_U32 *ImgInDDRAddress)
{
    HI_S32 ret = 0;
    HI_CAImgHead_S ImgInfo;
    HI_U8 u8Signature[SIGNATURE_LEN] = {0};
    HI_U8* pImageSignature = NULL;
    HI_BOOL bEncrypt = HI_TRUE;
    HI_U8 u8Hash[32] = {0};

    memset(&ImgInfo,0,sizeof(ImgInfo));
    CA_CheckPointer(pPartionName);

    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);

    CA_ASSERT(HI_CA_GetFlashImgInfoByName(pPartionName,&ImgInfo, &bEncrypt),ret);   
    CA_ASSERT(CA_flash_read((HI_CHAR*)pPartionName,0ULL,ImgInfo.u32TotalLen,(HI_U8*)IMG_VERIFY_ADDRESS, HI_NULL),ret);

    if (HI_TRUE == bEncrypt)
    {
        CA_ASSERT(CA_DataDecrypt((HI_U8 *)IMG_VERIFY_ADDRESS,ImgInfo.u32TotalLen,(HI_U8 *)IMG_VERIFY_ADDRESS),ret);
    }

    pImageSignature = (HI_U8*)(IMG_VERIFY_ADDRESS + ImgInfo.u32SignatureOffset );
    memcpy(u8Signature,pImageSignature,SIGNATURE_LEN);

    CA_ASSERT(HI_CA_ImgAuthenticate(IMG_VERIFY_ADDRESS,ImgInfo.u32SignedImageLen,u8Signature),ret);
    if(ImgInDDRAddress)
    {
        *ImgInDDRAddress = IMG_VERIFY_ADDRESS + ImgInfo.u32CodeOffset ;
    }

    HI_INFO_CA("HI_CA_FlashAuthenticateByName %s successed\n",pPartionName);

    sha2(u8Signature, SIGNATURE_LEN, u8Hash, 0);
    if (!memcmp(pPartionName, "recovery", sizeof(pPartionName)))
    {
        memcpy(&g_partition_hash[32], u8Hash, 32);
    }
    if (!memcmp(pPartionName, "kernel", sizeof(pPartionName)))
    {
        memcpy(&g_partition_hash[64], u8Hash, 32);
    }
    HI_SIMPLEINFO_CA("g_partition_hash:\n");
    printf_hex(g_partition_hash, 96);
    CA_AuthenticateDeInit();

    return ret;
}


HI_S32 HI_CA_GetFlashImgInfoByAddr(HI_U32 PartionAddr,HI_CAImgHead_S* pstImgInfo, HI_BOOL *pIsEncrypt)
{
    HI_S32 ret = 0;
    HI_U8 CAImageArea[CAImgHeadAreaLen] = {0};
    HI_U32 u32CRC32Value = 0;
    HI_Flash_InterInfo_S flashInfo;

    CA_CheckPointer(pstImgInfo);
    CA_ASSERT(CA_flash_read_addr(PartionAddr,NAND_PAGE_SIZE,(HI_U8*)CAImageArea, &flashInfo),ret);
    memcpy(pstImgInfo,CAImageArea,sizeof(HI_CAImgHead_S));
    if(!memcmp(pstImgInfo->u8MagicNumber,CAIMGHEAD_MAGICNUMBER,sizeof(pstImgInfo->u8MagicNumber)))
    {
        HI_INFO_CA("Img has not be encrypted\n");
        *pIsEncrypt = HI_FALSE;
    }
    else
    {
        CA_ASSERT(CA_DataDecrypt(CAImageArea,CAImgHeadAreaLen,CAImageArea),ret);
        udelay(100000);//wait fo decrypt end,this code is essential
        memcpy(pstImgInfo,CAImageArea,sizeof(HI_CAImgHead_S));
        if(!memcmp(pstImgInfo->u8MagicNumber,CAIMGHEAD_MAGICNUMBER,sizeof(pstImgInfo->u8MagicNumber)))
        {
            HI_INFO_CA("Img has be encrypted\n");
            *pIsEncrypt = HI_TRUE;
        }
        else
        {
            HI_INFO_CA("Magic number err, get Img information failed\n");
            return -1;
        }
    }

    HI_INFO_CA("ImgInfo.u8MagicNumber:\n", pstImgInfo->u8MagicNumber);
    printf_hex(pstImgInfo->u8MagicNumber, sizeof(pstImgInfo->u8MagicNumber));

    HI_INFO_CA("Magic number check success\n");

    /*Check if the total length is valid*/
    if ((pstImgInfo->u32TotalLen > (HI_U32)flashInfo.PartSize) || (pstImgInfo->u32TotalLen < NAND_PAGE_SIZE))
    {
        HI_ERR_CA("The total length of image invalid!\n");
        return -1;
    }

    /*Check if the other lengthes of the header are valid*/
    if ((pstImgInfo->u32CodeOffset != NAND_PAGE_SIZE) || (pstImgInfo->u32SignedImageLen == 0) || (pstImgInfo->u32SignedImageLen > pstImgInfo->u32TotalLen) ||
            (pstImgInfo->u32SignatureOffset == 0) || (pstImgInfo->u32SignatureOffset > pstImgInfo->u32TotalLen))
    {
        HI_ERR_CA("The header data of image invalid!\n");
        return -1;
    }

    //Clacluate CRC32!
    u32CRC32Value = DVB_CRC32((HI_U8 *)pstImgInfo, (sizeof(HI_CAImgHead_S) - 4));
    if(u32CRC32Value == pstImgInfo->u32CRC32)
    {
        HI_INFO_CA("CRC32 check ok\n");
    }
    else
    {
        HI_ERR_CA("CRC32Value:%x != pstImgInfo->CRC32:%x\n", u32CRC32Value, pstImgInfo->u32CRC32);
        return -1;
    }
    return 0;

}

HI_S32 HI_CA_FlashAuthenticateByAddr(HI_U32 PartionAddr,HI_BOOL bisBootargsArea,HI_U32 *ImgInDDRAddress)
{
    HI_S32 ret = 0;
    HI_CAImgHead_S ImgInfo;
    HI_U8 u8Signature[SIGNATURE_LEN] = {0};
    HI_U8* pImageSignature = NULL;
    HI_BOOL bEncrypt = HI_TRUE;


    memset(&ImgInfo,0,sizeof(ImgInfo));
    CA_CheckPointer(ImgInDDRAddress);

    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);

    CA_ASSERT(HI_CA_GetFlashImgInfoByAddr(PartionAddr, &ImgInfo, &bEncrypt),ret);
    CA_ASSERT(CA_flash_read_addr(PartionAddr,ImgInfo.u32TotalLen,(HI_U8*)IMG_VERIFY_ADDRESS, HI_NULL),ret);

    if (HI_TRUE == bEncrypt)
    {
        CA_ASSERT(CA_DataDecrypt((HI_U8 *)IMG_VERIFY_ADDRESS,ImgInfo.u32TotalLen,(HI_U8 *)IMG_VERIFY_ADDRESS),ret);
    }

    pImageSignature = (HI_U8*)(IMG_VERIFY_ADDRESS + ImgInfo.u32SignatureOffset );
    memcpy(u8Signature,pImageSignature,SIGNATURE_LEN);

    CA_ASSERT(HI_CA_ImgAuthenticate(IMG_VERIFY_ADDRESS,ImgInfo.u32SignedImageLen,u8Signature),ret);
    if(ImgInDDRAddress)
    {
        *ImgInDDRAddress = IMG_VERIFY_ADDRESS + ImgInfo.u32CodeOffset ;
    }

    HI_INFO_CA("HI_CA_FlashAuthenticateByAddr   0x%x  successed\n",PartionAddr);
    if (HI_TRUE == bisBootargsArea)
    {
        HI_SIMPLEINFO_CA("re-set bootargs, offset:0x%x, realaddr:0x%x\n", IMG_VERIFY_ADDRESS+ImgInfo.u32CodeOffset, ImgInfo.u32CodeOffset);
        CA_nand_env_relocate_spec((HI_U8*)(IMG_VERIFY_ADDRESS+ImgInfo.u32CodeOffset));
    }

    CA_AuthenticateDeInit();

    return ret;
}

HI_S32 HI_CA_AuthenticateBootPara(HI_VOID)
{
    HI_S32 ret;
    HI_U32 ImgInDDRAddress = 0;

    HI_SIMPLEINFO_CA("HI_CA_AuthenticateBootPara g_EnvFlashAddr:0x%x\n", g_EnvFlashAddr);

    ret = HI_CA_FlashAuthenticateByAddr(g_EnvFlashAddr, HI_TRUE, &ImgInDDRAddress);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("Authenticate bootargs failed\n");
        CA_Reset();
    }

    return HI_SUCCESS;
}

HI_S32 HI_CA_AuthenticateBootParaBak(HI_VOID)
{
    HI_U32 ImgInDDRAddress = 0;
    return HI_CA_FlashAuthenticateByAddr(g_EnvBakFlashAddr,HI_TRUE,&ImgInDDRAddress);
}

#if 0
HI_S32 CA_AuthenticateLogoData(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32LogoSize = 0;
    HI_U32 u32BaseSize = 0;
    HI_HANDLE hFlash = HI_INVALID_HANDLE;
    HI_Flash_InterInfo_S stLogoInfo;
    HI_Flash_InterInfo_S stBaseInfo;
    HI_FASTPLAY_MEM_INFO_S FastPlayMemInfo;
    HI_U32 u32LogoRamAddress = 0;
    HI_U32 u32BaseRamAddress = 0;
    struct mmz_Info_t stFastplayInfo;

    stFastplayInfo = get_fastplay_mmzInfo();

    /*Read logo partition*/
    hFlash = HI_Flash_Open(HI_FLASH_TYPE_BUTT, LOGO_BASIC, 0, 0);
    if(HI_INVALID_HANDLE == hFlash)
    {
        HI_ERR_CA("HI_Flash_Open() %s error, result %x!\n",LOGO_BASIC,ret);
        return HI_FAILURE;
    }

    ret = HI_Flash_GetInfo(hFlash, &stLogoInfo);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("HI_Flash_GetInfo() error, result %x!\n",ret);
        (HI_VOID)HI_Flash_Close(hFlash);
        return ret;
    }

    u32LogoSize = (HI_U32)stLogoInfo.PartSize;

    /*mmz tail - 8K - Logo size = 0x8FEFE000*/
    u32LogoRamAddress = stFastplayInfo.startAddr + stFastplayInfo.size - 0x2000 - u32LogoSize;
    HI_ERR_CA("logo part size = %llx, logo ram address = %x\n", stLogoInfo.PartSize, u32LogoRamAddress);

    ret = HI_Flash_Read(hFlash, 0ULL, (HI_U8*)u32LogoRamAddress, u32LogoSize, HI_FLASH_RW_FLAG_RAW);
    if (ret)
    {
        HI_ERR_CA("HI_Flash_Read partion %s error\n", LOGO_BASIC);
        HI_Flash_Close(hFlash);
        return HI_FAILURE;
    }
    HI_Flash_Close(hFlash);

    /*Read base partition*/
    hFlash = HI_Flash_Open(HI_FLASH_TYPE_BUTT, BASE_BASIC, 0, 0);
    if(HI_INVALID_HANDLE == hFlash)
    {
        HI_ERR_CA("HI_Flash_Open() %s error, result %x!\n",BASE_BASIC,ret);
        return HI_FAILURE;
    }

    ret = HI_Flash_GetInfo(hFlash, &stBaseInfo);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("HI_Flash_GetInfo() error, result %x!\n",ret);
        (HI_VOID)HI_Flash_Close(hFlash);
        return HI_FAILURE;
    }

    u32BaseSize = (HI_U32)stBaseInfo.PartSize;
    /*LOGO_DATA_ADDR - baseparam size = 0x8FDFE000*/
    u32BaseRamAddress = u32LogoRamAddress - u32BaseSize;

    HI_ERR_CA("base block size = %llx, base ram address = %x\n", stBaseInfo.PartSize, u32BaseRamAddress);
    ret = HI_Flash_Read(hFlash, 0ULL, (HI_U8*)u32BaseRamAddress, u32BaseSize, HI_FLASH_RW_FLAG_RAW);
    if (ret)
    {
        HI_ERR_CA("HI_Flash_Read partion %s error\n", BASE_BASIC);
        (HI_VOID)HI_Flash_Close(hFlash);
        return HI_FAILURE;
    }
    HI_Flash_Close(hFlash);

#ifndef HI_CA_NOT_AUTHENTICATE
    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);
    CA_ASSERT(CA_DataDecrypt((HI_U8 *)u32LogoRamAddress,u32LogoSize,(HI_U8 *)u32LogoRamAddress),ret);
    CA_ASSERT(CA_DataDecrypt((HI_U8 *)u32BaseRamAddress,u32BaseSize,(HI_U8 *)u32BaseRamAddress),ret);
#endif

    memset(&FastPlayMemInfo,0,sizeof(HI_FASTPLAY_MEM_INFO_S));
    FastPlayMemInfo.pu8BaseParaAddr = (HI_U8 *)u32BaseRamAddress;
    FastPlayMemInfo.u32BasePartitionSize = u32BaseSize;
    FastPlayMemInfo.pu8LogoParaAddr = (HI_U8 *)u32LogoRamAddress;
    FastPlayMemInfo.u32LogoPartitionSize = u32LogoSize;

    /* show logo */
    fast_play(&FastPlayMemInfo);

    return HI_SUCCESS;
}
#endif

HI_S32 HI_CA_AuthenticateEntry(HI_VOID)
{
    HI_S32 ret;
    HI_BOOL bNeedUpgrd = HI_FALSE;
    HI_CHAR chBootCmd[64] = {0};
    HI_U32 u32LaunchAddr = 0;

    HI_CA_AuthenticateBootPara();

    CA_AuthenticateInit(HI_CA_KEY_GROUP_1);
    Logo_Main();
    CA_AuthenticateDeInit();

    c51_loadCode();

    ret = CA_ReadUpgrdFlag(&bNeedUpgrd);
    if ((HI_SUCCESS == ret) && (0x01 == bNeedUpgrd))
    {
        HI_INFO_CA("Need Upgrade!!!!!!!!!!!!!!\n");
        ret = HI_CA_FlashAuthenticateByName((HI_U8 *)STBID_BASIC,NULL);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("Authenticate stbid failed\n");
            CA_Reset();
        }
        ret = HI_CA_FlashAuthenticateByName((HI_U8 *)SYSTEM_BASIC,NULL);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("Authenticate system failed\n");
            CA_Reset();
        }
        ret = HI_CA_FlashAuthenticateByName((HI_U8 *)LOADER_BASIC,&u32LaunchAddr);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("Authenticate loader failed\n");
            CA_Reset();
        }
    }
    else
    {
        HI_INFO_CA("Do not Need Upgrade!!!!!!!!!!!!!!\n");
        ret = HI_CA_FlashAuthenticateByName((HI_U8 *)STBID_BASIC,NULL);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("Authenticate stbid failed\n");
            CA_Reset();
        }
        ret = HI_CA_FlashAuthenticateByName((HI_U8 *)LOADER_BASIC,NULL);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("Authenticate loader failed\n");
            CA_Reset();
        }
        ret = HI_CA_FlashAuthenticateByName((HI_U8 *)SYSTEM_BASIC,&u32LaunchAddr);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("Authenticate system failed\n");
            CA_Reset();
        }
    }

    snprintf(chBootCmd, sizeof(chBootCmd), "bootm 0x%x", u32LaunchAddr);

    run_command(chBootCmd, 0);

    return ret;
}


/*************************************************************************
 *
 * The function below is added for AES CBC-MAC, for Irdeto MSR1.9 chipset.
 *
 *************************************************************************/

/* For CMAC Calculation */
static HI_U8 const_Rb[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
};

/* Basic Functions */
static HI_VOID xor_128(HI_U8 *a, HI_U8 *b, HI_U8 *out)
{
    HI_U32 i;

    if(a == NULL || b == NULL || out == NULL)
    {
        HI_ERR_CA("Invalid parameter!\n");
        return;
    }

    for (i = 0; i < 16; i++)
    {
        out[i] = a[i] ^ b[i];
    }
}

/* AES-CMAC Generation Function */
static HI_VOID leftshift_onebit(HI_U8 *input, HI_U8 *output)
{
    HI_S32 i;
    HI_U8 overflow = 0;

    if(input == NULL || output == NULL)
    {
        HI_ERR_CA("Invalid parameter!\n");
        return;
    }

    for ( i = 15; i >= 0; i-- )
    {
        output[i] = input[i] << 1;
        output[i] |= overflow;
        overflow = (input[i] & 0x80) ? 1 : 0;
    }
    return;
}

static HI_S32 generate_subkey(HI_HANDLE hCipherHandle, HI_U8 *K1, HI_U8 *K2)
{
    HI_U8 L[16];
    HI_U8 Z[16];
    HI_U8 tmp[16];
    HI_U32 u32DataLen = 16;
    HI_S32 Ret = HI_SUCCESS;

    if(K1 == NULL || K2 == NULL)
    {
        HI_ERR_CA("Invalid parameter!\n");
        return HI_FAILURE;
    }

    memset(Z, 0x0, sizeof(Z));
    Ret = HI_CIPHER_EncryptEx(hCipherHandle, Z, u32DataLen, L);
    if(Ret != HI_SUCCESS)
    {
        return Ret;
    }

    if ( (L[0] & 0x80) == 0 ) /* If MSB(L) = 0, then K1 = L << 1 */
    {
        leftshift_onebit(L, K1);
    }
    else  /* Else K1 = ( L << 1 ) (+) Rb */
    {
        leftshift_onebit(L, tmp);
        xor_128(tmp, const_Rb, K1);
    }

    if ( (K1[0] & 0x80) == 0 )
    {
        leftshift_onebit(K1,K2);
    }
    else
    {
        leftshift_onebit(K1, tmp);
        xor_128(tmp, const_Rb, K2);
    }

    return HI_SUCCESS;
}

static HI_VOID padding ( HI_U8 *lastb, HI_U8 *pad, HI_U32 length )
{
    HI_U32 j;

    if(lastb == NULL || pad == NULL)
    {
        HI_ERR_CA("Invalid parameter!\n");
        return;
    }

    /* original last block */
    for ( j = 0; j < 16; j++ )
    {
        if ( j < length )
        {
            pad[j] = lastb[j];
        }
        else if ( j == length )
        {
            pad[j] = 0x80;
        }
        else
        {
            pad[j] = 0x00;
        }
    }
}

HI_S32 HI_CA_CalcMAC(HI_U8 *pu8Key, HI_U8 *pInputData, HI_U32 u32InputDataLen,
                                        HI_U8 *pOutputMAC, HI_BOOL bIsLastBlock)
{
    HI_U8 X[16], M_last[16], padded[16];
    static HI_U8 K1[16], K2[16];
    HI_U32 n, i, flag;
    HI_U8 u8TmpBuf[16];
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S stCipherCtrl;
    static HI_BOOL bIsFirstBlock = HI_TRUE;
    HI_S32 ret = HI_SUCCESS;
    static HI_HANDLE hCipherHandle;
    HI_UNF_CIPHER_ATTS_S stCipherAtts;
    static HI_U32 u32MmzPhyAddr = 0;
    static HI_BOOL bIsDstMmzInit = HI_FALSE;

     if(pu8Key == NULL || pInputData == NULL || pOutputMAC == NULL)
    {
        HI_ERR_CA("Invalid parameter!\n");
        return -1;
    }

    if(bIsFirstBlock)
    {
        CA_ASSERT(HI_UNF_CIPHER_Init(), ret);
        HI_UNF_ADVCA_Init();

        memset(&stCipherAtts, 0, sizeof(HI_UNF_CIPHER_ATTS_S));
        stCipherAtts.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
        CA_ASSERT(HI_UNF_CIPHER_CreateHandle(&hCipherHandle, &stCipherAtts),ret);
        memcpy(stCipherCtrl.u32Key, pu8Key, 16);
        memset(stCipherCtrl.u32IV, 0, sizeof(stCipherCtrl.u32IV));
        stCipherCtrl.bKeyByCA = HI_TRUE;
        stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
        stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
        stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
        stCipherCtrl.stChangeFlags.bit1IV = 1;
        stCipherCtrl.enCaType = HI_UNF_CIPHER_CA_TYPE_BLPK;
        CA_ASSERT(HI_UNF_CIPHER_ConfigHandle(hCipherHandle, &stCipherCtrl), ret);

        Ret = generate_subkey(hCipherHandle, K1, K2);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }

        //After genreate the subkey, reset the configure handle
        memcpy(stCipherCtrl.u32Key, pu8Key, 16);
        memset(stCipherCtrl.u32IV, 0, sizeof(stCipherCtrl.u32IV));
        stCipherCtrl.bKeyByCA = HI_TRUE;
        stCipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
        stCipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        stCipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
        stCipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
        stCipherCtrl.stChangeFlags.bit1IV = 1;
        stCipherCtrl.enCaType = HI_UNF_CIPHER_CA_TYPE_BLPK;
        CA_ASSERT(HI_UNF_CIPHER_ConfigHandle(hCipherHandle, &stCipherCtrl), ret);
        bIsFirstBlock = HI_FALSE;
    }

    if(!bIsDstMmzInit)
    {
        Ret = HI_MEM_Alloc(&u32MmzPhyAddr, MAX_DATA_LEN);
        if (Ret != HI_SUCCESS)
        {
            HI_ERR_CA("malloc input memory failed!\n");
            return HI_FAILURE;
        }
        memset((void *)u32MmzPhyAddr, 0, MAX_DATA_LEN);

        bIsDstMmzInit = HI_TRUE;
    }

    if(!bIsLastBlock)
    {
       Ret = HI_CIPHER_EncryptEx(hCipherHandle, pInputData, u32InputDataLen, (HI_U8 *)u32MmzPhyAddr); /* X := AES-128(KEY, Y); */
       memcpy(u8TmpBuf, (HI_U8 *)(u32MmzPhyAddr + u32InputDataLen - 16), 16);
       if(Ret != HI_SUCCESS)
       {
            return Ret;
       }
    }
    else
    {
        bIsFirstBlock = HI_TRUE;

        n = (u32InputDataLen + 15) / 16; /* n is number of rounds */
        if ( n == 0 )
        {
            n = 1;
            flag = 0;
        }
        else
        {
            if ( (u32InputDataLen % 16) == 0 ) /* last block is a complete block */
            {
                flag = 1;
            }
            else /* last block is not complete block */
            {
                flag = 0;
            }
        }

        if ( flag )  /* last block is complete block */
        {
            xor_128(&pInputData[16 * (n - 1)], K1, M_last);
        }
        else
        {
            padding(&pInputData[16 * (n - 1)], padded, u32InputDataLen % 16);
            xor_128(padded, K2, M_last);
        }

        if(n > 1)
        {
           Ret = HI_CIPHER_EncryptEx(hCipherHandle, pInputData, 16 * (n - 1), (HI_U8 *)u32MmzPhyAddr); /* X := AES-128(KEY, Y); */
           memcpy(u8TmpBuf, (HI_U8 *)(u32MmzPhyAddr + 16 * (n - 1) - 16), 16);
           if(Ret != HI_SUCCESS)
           {
                return Ret;
           }
        }

        HI_CIPHER_EncryptEx(hCipherHandle, M_last, 16, X);
        if(Ret != HI_SUCCESS)
        {
            return Ret;
        }

        for ( i = 0; i < 16; i++ )
        {
            pOutputMAC[i] = X[i];
        }

        CA_ASSERT(HI_UNF_CIPHER_DestroyHandle(hCipherHandle), ret);
    }

    return HI_SUCCESS;
}
/****************/

/****************************************************/
HI_S32 generate_encrypt_key(HI_U8 *clear_key, HI_U8 *encrypt_key)
{
    CA_EncryptSwpk((HI_U32 *)clear_key, (HI_U32 *)encrypt_key);
    return HI_SUCCESS;
}

typedef enum
{
    Algoritm_Hash1,
    Algoritm_Hash2
}HI_Algorithm_EN;

typedef struct
{
    HI_U8 *pImageData;
    HI_U32 ImageDataLength;
    HI_CASignImageTail_S *pCASignTail;
} HI_CA_NEW_SignParam_S;

/*
** CRC32 Arithmetic
*/
#define     POLYNOMIAL 0x04c11db7L
static short _First = 1;                       /*Init _CrcTable[256] Flag, Only init once time*/
static unsigned long  _CrcTable[256];                  /*Calculate CRC32*/

static void GenCrcTable(void)
{
     int    i, j;
    unsigned long crc_accum;
    for( i = 0;  i < 256;  i++ )
    {
        crc_accum =  ( i << 24 );
        for( j = 0;  j < 8;  j++ )
        {
            if( crc_accum & 0x80000000L )
                crc_accum = ( crc_accum << 1 ) ^ POLYNOMIAL;
            else
                crc_accum = ( crc_accum << 1 );
        }
        _CrcTable[i] = crc_accum;
    }
    return;
}


unsigned long DVB_CRC32(unsigned char *buf, int length)
{
    unsigned long crc = 0xffffffff;

    if(_First)
    {
        GenCrcTable();
        _First = 0;
    }
    while( length-- )
    {
        crc = (crc << 8) ^ _CrcTable[((crc >> 24) ^ *buf++) & 0xff];
    }

    return crc;
}

typedef struct hash_atts
{
    HI_HANDLE *sha_context;
    HI_Algorithm_EN hashType;
}HASH_ATTS_S;

HI_S32 CA_Common_InitHASH(HI_U8 HashType, HI_HANDLE **handle)
{
    void *ctx = NULL;
    HASH_ATTS_S *atts = NULL;

    atts = (HASH_ATTS_S *)malloc(sizeof(HASH_ATTS_S));
    if (NULL == atts)
    {
        HI_SIMPLEINFO_CA("err [%s:%d]\n", __FUNCTION__, __LINE__);
        return -1;
    }

    if (HashType == Algoritm_Hash1)
    {
        ctx = (sha1_context *)malloc(sizeof(sha1_context));
        if (NULL == ctx)
        {
            HI_SIMPLEINFO_CA("err [%s:%d]\n", __FUNCTION__, __LINE__);
            free(atts);
            return -1;
        }
        memset(ctx, 0, sizeof(sha1_context));

        sha1_starts(ctx);
    }
    else if (HashType == Algoritm_Hash2)
    {
        ctx = (sha2_context *)malloc(sizeof(sha2_context));
        if (NULL == ctx)
        {
            HI_SIMPLEINFO_CA("err [%s:%d]\n", __FUNCTION__, __LINE__);
            free(atts);
            return -1;
        }
        memset(ctx, 0, sizeof(sha2_context));

        sha2_starts(ctx, 0);
    }
    else
    {
        HI_SIMPLEINFO_CA("Invalid hash type!\n");
        free(atts);
        return -1;
    }
    atts->sha_context= (HI_HANDLE *)ctx;
    atts->hashType = HashType;
    *handle = (HI_HANDLE *)atts;

    return 0;
}

HI_VOID CA_Common_UpdateHASH(HI_HANDLE *handle, HI_U8 *StartAddr, HI_U32 length)
{
    if (((HASH_ATTS_S *)handle)->hashType == Algoritm_Hash1)
    {
        sha2_update((sha2_context *)(((HASH_ATTS_S *)handle)->sha_context), (const unsigned char *)StartAddr, length);
    }
    else
    {
        sha1_update((sha1_context *)(((HASH_ATTS_S *)handle)->sha_context), (const unsigned char *)StartAddr, length);
    }
}

HI_VOID CA_Common_FinishHASH(HI_HANDLE *handle, HI_U8 *Hash)
{
    if (((HASH_ATTS_S *)handle)->hashType == Algoritm_Hash2)
    {
        sha2_finish((sha2_context *)(((HASH_ATTS_S *)handle)->sha_context), Hash);
        free((sha2_context *)(((HASH_ATTS_S *)handle)->sha_context));
    }
    else
    {
        sha1_finish((sha1_context *)(((HASH_ATTS_S *)handle)->sha_context), Hash);
        free((sha1_context *)(((HASH_ATTS_S *)handle)->sha_context));
    }
    free((HASH_ATTS_S *)handle);
}
HI_S32 Debug_CASignImageTail_Value(HI_CASignImageTail_S *pCASignTail)
{
    int index;
    unsigned char Data[256];

    memset(Data, 0, 256);
    memcpy(Data, pCASignTail->u8MagicNumber, 32);
    HI_SIMPLEINFO_CA("\nu8MagicNumber:%s\n", Data);
    memset(Data, 0, 256);
    if(memcmp(pCASignTail->u8Version, CAIMGHEAD_VERSION, sizeof(pCASignTail->u8Version)))
    {
        HI_ERR_CA("Version num has been changed from v0000002 to v0000003\n");
        return -1;
    }
    memcpy(Data, pCASignTail->u8Version, 8);

    HI_SIMPLEINFO_CA("u8Version:%s\n", Data);
    HI_SIMPLEINFO_CA("u32CreateDay:0x%x\n", pCASignTail->u32CreateDay);
    HI_SIMPLEINFO_CA("u32CreateTime:0x%x\n", pCASignTail->u32CreateTime);
    HI_SIMPLEINFO_CA("u32HeadLength:0x%x\n", pCASignTail->u32HeadLength);
    HI_SIMPLEINFO_CA("u32SignedDataLength:%d:0x%x\n", pCASignTail->u32SignedDataLength, pCASignTail->u32SignedDataLength);
    HI_SIMPLEINFO_CA("u32IsYaffsImage:%d\n", pCASignTail->u32IsYaffsImage);
    HI_SIMPLEINFO_CA("u32IsConfigNandBlock:%d\n", pCASignTail->u32IsConfigNandBlock);
    HI_SIMPLEINFO_CA("u32NandBlockType:%d\n", pCASignTail->u32NandBlockType);
    HI_SIMPLEINFO_CA("u32IsNeedEncrypt:%d\n", pCASignTail->u32IsNeedEncrypt);
    HI_SIMPLEINFO_CA("u32IsEncrypted:%d\n", pCASignTail->u32IsEncrypted);
    HI_SIMPLEINFO_CA("u32HashType:%d\n", pCASignTail->u32HashType);
    HI_SIMPLEINFO_CA("u32CurrentsectionID:%d\n", pCASignTail->u32CurrentsectionID);
    HI_SIMPLEINFO_CA("u32TotalsectionID:%d\n", pCASignTail->u32TotalsectionID);
    HI_SIMPLEINFO_CA("u32SectionSize:%d\n", pCASignTail->u32SectionSize);
    if(pCASignTail->u32HashType == Algoritm_Hash2)
    {
        for(index = 0; index < 32; index ++)
        {
            HI_SIMPLEINFO_CA("%02x ", pCASignTail->u8Sha[index]);
        }
    }
    else
    {
        for(index = 0; index < 5; index ++)
        {
            HI_SIMPLEINFO_CA("%02x ", pCASignTail->u8Sha[index]);
        }
    }
    HI_SIMPLEINFO_CA("\n");
    HI_SIMPLEINFO_CA("u32SignatureLen:%d\n", pCASignTail->u32SignatureLen);
    for(index = 0; index < pCASignTail->u32SignatureLen; index ++)
    {
        HI_SIMPLEINFO_CA("%02x ", pCASignTail->u8Signature[index]);
    }
    HI_SIMPLEINFO_CA("\n");
    HI_SIMPLEINFO_CA("OrignalImagePath:%s\n", pCASignTail->OrignalImagePath);
    HI_SIMPLEINFO_CA("RSAPrivateKeyPath:%s\n", pCASignTail->RSAPrivateKeyPath);
    HI_SIMPLEINFO_CA("CRC32:%x\n", pCASignTail->CRC32);

    return 0;
}

HI_S32 CA_CommonParse_SubCommand(HI_U8 *string, HI_U32 length, HI_U8 *ImageName, HI_U8 *SignName, HI_U32 *SignOffset)
{
    int ret = 0;
    HI_U8 *pImageoffset, *pSignimageoffset, *pSignloacationoffset;
    HI_U8 deliver[] = ",";

    pImageoffset = string;

    pSignimageoffset = (HI_U8 *)strstr((const char *)string, (const char *)deliver);
    if(pSignimageoffset == HI_NULL)
    {
        HI_ERR_CA("Can not find , in string:%s\n", string);
        return -1;
    }
    //Get ImageName
    memcpy(ImageName, pImageoffset, (pSignimageoffset - pImageoffset));

    pSignimageoffset ++; //jump ;
    pSignloacationoffset = (HI_U8 *)strstr((const char *)pSignimageoffset, (const char *)deliver);
    if(pSignloacationoffset == HI_NULL)
    {
        HI_ERR_CA("Can not find , in pSignimageoffset:%s\n", pSignimageoffset);
        return -1;
    }
    //Get SiagnName
    memcpy(SignName, pSignimageoffset, (pSignloacationoffset - pSignimageoffset));

    //Get Siagn loaction offset
    pSignloacationoffset ++; //jump ;
    *SignOffset = (HI_U32)simple_strtoul((const char *)pSignloacationoffset, NULL, 16);

    return ret;
}

HI_S32 CA_Common_Search_SignHeader(HI_U8 *PartitionSignName, HI_CASignImageTail_S *pSignImageInfo, HI_U32 *pOffset)
{
    HI_S32 ret = 0, index = 0, i = 0;
    HI_U32 PartitionSize = 0;
    HI_U8 *CAImageArea = HI_NULL;
    HI_U32 offset;
    HI_U32 PageSize = 0;

    CA_CheckPointer(pOffset);
    offset = *pOffset;

    CA_CheckPointer(PartitionSignName);
    HI_INFO_CA("PartitionSignName:%s\n", PartitionSignName);
    CA_ASSERT(CA_flash_GetSize((HI_CHAR *)PartitionSignName, &PartitionSize),ret);
    CA_ASSERT(CA_flash_GetPageSize((HI_CHAR *)PartitionSignName, &PageSize), ret);

    if (PageSize <= NAND_PAGE_SIZE)
    {
        PageSize = NAND_PAGE_SIZE;
		if(NAND_PAGE_SIZE % PageSize != 0)
		{
		    HI_ERR_CA("NAND_PAGE_SIZE(%d) % PageSize(%d) != 0\n", NAND_PAGE_SIZE, PageSize);
		    return HI_FAILURE;
		}
    }

    CAImageArea = (HI_U8 *)malloc(PageSize);
    if (NULL == CAImageArea)
    {
        HI_ERR_CA("malloc CAImageArea Fail\n");
        return HI_FAILURE;
    }
    
    for(index = offset / PageSize; index < PartitionSize / PageSize; index ++)
    {
        CA_ASSERT(CA_flash_read((HI_CHAR*)PartitionSignName, PageSize * index, PageSize,(HI_U8*)CAImageArea, HI_NULL),ret);
        for (i = 0; i < PageSize / NAND_PAGE_SIZE; i++)  //PageSize must >= NAND_PAGE_SIZE
        {
            memcpy(pSignImageInfo, CAImageArea + i * NAND_PAGE_SIZE, sizeof(HI_CASignImageTail_S));
            if(!memcmp(pSignImageInfo->u8MagicNumber, CAIMGHEAD_MAGICNUMBER, sizeof(pSignImageInfo->u8MagicNumber)))
            {
                unsigned int CRC32Value;
                HI_INFO_CA("Sign Header found!\n");
                //Clacluate CRC32!
                CRC32Value = DVB_CRC32((HI_U8 *)pSignImageInfo, (sizeof(HI_CASignImageTail_S) - 4));
                if(CRC32Value == pSignImageInfo->CRC32)
                {                    
                    *pOffset = index * PageSize + i * NAND_PAGE_SIZE;
                    HI_INFO_CA("CRC32 check ok\n");
#ifdef SPARSE_EXT4
                    if (0 == IsSparseFlag && !memcmp(PartitionSignName, SYSTEM_SIGN_PARTITION, strlen(SYSTEM_SIGN_PARTITION)))
                    {
                        HI_U32 pTmp = 0;
                        ret = HI_MEM_Alloc(&pTmp, PartitionSize - PageSize * index);
                        if (HI_SUCCESS != ret)
                        {
                            free (CAImageArea);
                            return HI_FAILURE;
                        }
                        CA_CheckPointer((HI_VOID *)pTmp);
                        CA_ASSERT(CA_flash_read((HI_CHAR*)PartitionSignName, PageSize * index, PartitionSize - PageSize * index, pTmp, HI_NULL), ret);
                        pSparseHead = (sparse_header_t *)(pTmp + i * NAND_PAGE_SIZE + pSignImageInfo->u32TotalsectionID * NAND_PAGE_SIZE);
                        if (IS_SPARSE(pSparseHead))  /* sparse ext4 */
                        {
                            IsSparseFlag = 1;
                            pChunkHead = (sign_chunk_header_t *)(pTmp + i * NAND_PAGE_SIZE + pSignImageInfo->u32TotalsectionID * NAND_PAGE_SIZE + pSparseHead->file_hdr_sz);
                            pSignChunkInfo = (HI_U32 *)(pTmp + i * NAND_PAGE_SIZE + pSignImageInfo->u32TotalsectionID * NAND_PAGE_SIZE + pSparseHead->file_hdr_sz + pSparseHead->chunk_hdr_sz * pSparseHead->total_chunks);
                        }
                        else  /* not sparse ext4 */
                        {
                            IsSparseFlag = 2;
                        }
                    }
#endif
    				free (CAImageArea);
                    return HI_SUCCESS;
                }
                else
                {
                    HI_ERR_CA("CRC32Value:%x != pSignImageInfo->CRC32:%x\n", CRC32Value, pSignImageInfo->CRC32);
                    free (CAImageArea);
                    return HI_FAILURE; 
                }
            }
        }
    }
 
    free(CAImageArea);
    return HI_FAILURE;
}

static HI_S32 CA_GetYAFFSFlashData(HI_U8 * PartitionImagenName, HI_U8 *DDRAddress, HI_U32 Length)
{
    HI_S32 ret = 0, index;
    HI_U8 *pCAImageArea;
    HI_U32 Address;
    HI_U32 PartionSize;
    HI_U32 PageSize;
    HI_U32 BlockSize;
    HI_U32 OobSize;

    char argv[5][20];
    char command[256];

    CA_ASSERT(CA_flash_getinfo((HI_CHAR *)PartitionImagenName, &PartionSize, &BlockSize, &PageSize, &OobSize),ret);
    if(Length == 0)
    {
        Length = PartionSize;
    }

    pCAImageArea = (HI_U8 *)DDRAddress;
    if(pCAImageArea == NULL)
    {
        HI_ERR_CA("can not allocate data\n");
        return HI_FAILURE;
    }


    CA_flash_GetFlashAddressFromParitonName(HI_FLASH_TYPE_NAND_0, (HI_CHAR*)PartitionImagenName, &Address);

    memset(argv, 0, 5*20);
    strncpy(argv[0], "nand", sizeof(argv[0]));
    strncpy(argv[1], "read.yaffs", sizeof(argv[1]));
    snprintf(argv[2], sizeof(argv[2]), "%x ", pCAImageArea);
    snprintf(argv[3], sizeof(argv[3]), "%x ", Address);
    snprintf(argv[4], sizeof(argv[4]), "%x ", Length);

    for(index = 0; index < 5; index ++)
    {
        HI_SIMPLEINFO_CA("%s ", argv[index]);
    }

#if 1
    memset(command, 0, 256);
    snprintf(command, sizeof(command), "nand read.yaffs 0x%x 0x%x 0x%x ", pCAImageArea, Address, Length);
    run_command(command, 0);
#else
    do_get_nand_read(&(argv[1]), &(argv[2]), &(argv[3]), &(argv[4]));
#endif

    HI_SIMPLEINFO_CA("Get %s to %x, length:0x%x\n", PartitionImagenName, (int)DDRAddress, Length);

    return ret;
}

HI_S32 CA_Common_GetImageData(HI_U8 *PartitionImageName, HI_CASignImageTail_S *pSignImageInfo, HI_CA_NEW_SignParam_S *pSignParam)
{
    HI_S32 ret = 0, index = 0;
    HI_S32 PartitionImagSize = 0;
    HI_U64 PartitionImageOffset = 0;
    HI_U8 *pCAImageArea = NULL;
    HI_U8 TmpSha[32];
#ifdef SPARSE_EXT4
    HI_U32 u32CurChunkNum = 0;
    HI_U32 u32NextChunkNum = 0;
    HI_U32 u32ChunkNum = 0;
    HI_U32 u32MergeDataLen = 0;
    HI_U32 u32MergeDataOffset = 0;
    sign_chunk_header_t * tmpChunkHead = HI_NULL;
#endif

    CA_CheckPointer(PartitionImageName);

    HI_INFO_CA("PartitionImageName:%s, pSignImageInfo->u32SignedDataLength:%d\n", PartitionImageName, pSignImageInfo->u32SignedDataLength);
    PartitionImagSize = (pSignImageInfo->u32SignedDataLength + NAND_PAGE_SIZE - 1) / NAND_PAGE_SIZE * NAND_PAGE_SIZE;
    PartitionImageOffset = pSignImageInfo->u32CurrentsectionID * pSignImageInfo->u32SectionSize;

    pCAImageArea = (HI_U8 *)IMG_VERIFY_ADDRESS;
    if(pCAImageArea == NULL)
    {
        HI_ERR_CA("can not allocate data\n");
        return HI_FAILURE;
    }
    memset(pCAImageArea, 0x00, PartitionImagSize);
    if(pSignImageInfo->u32IsYaffsImage)
    {
        HI_INFO_CA("Yaffs FileSystem, We will check sign of the whole yaffs-image:%s\n", PartitionImageName);
        CA_ASSERT(CA_GetYAFFSFlashData((HI_U8*)PartitionImageName, pCAImageArea, pSignImageInfo->u32SignedDataLength),ret);
    }
    else
    {
        CA_ASSERT(CA_flash_read((HI_CHAR*)PartitionImageName, PartitionImageOffset, PartitionImagSize,(HI_U8*)pCAImageArea, HI_NULL),ret);
    }

#ifdef SPARSE_EXT4
    if (1 == IsSparseFlag)
    {
        /* Get authenticate data begin in which sparse chunk */
        u32CurChunkNum = *(pSignChunkInfo + pSignImageInfo->u32CurrentsectionID);
        u32NextChunkNum = *(pSignChunkInfo + pSignImageInfo->u32CurrentsectionID + 1);
        u32ChunkNum = u32NextChunkNum - u32CurChunkNum;

        tmpChunkHead = (sign_chunk_header_t *)(pChunkHead + u32CurChunkNum);
        if (tmpChunkHead->num != u32CurChunkNum)
        {
            HI_ERR_CA("Get sparse ext4 info error!\n");
            return HI_FAILURE;
        }

        /* set the data of CHUNK_TYPE_DONT_CARE to zero */
        if (0 == u32ChunkNum)
        {
            if (tmpChunkHead->chunk_type == CHUNK_TYPE_DONT_CARE)
            {
                memset(pCAImageArea, 0, pSignImageInfo->u32SignedDataLength);
            }
        }
        else
        {
            if (tmpChunkHead->chunk_type == CHUNK_TYPE_DONT_CARE)
                u32MergeDataOffset = 0;
            else
                u32MergeDataOffset = tmpChunkHead->offset + tmpChunkHead->chunk_sz * pSparseHead->blk_sz - pSignImageInfo->u32CurrentsectionID * pSignImageInfo->u32SignedDataLength;
            u32MergeDataLen = 0;
            for (index = 0; index <= u32ChunkNum; index++)
            {
                if (tmpChunkHead->chunk_type == CHUNK_TYPE_DONT_CARE)
                {
                    if (0 == index)
                        u32MergeDataLen = tmpChunkHead->offset + tmpChunkHead->chunk_sz * pSparseHead->blk_sz - pSignImageInfo->u32CurrentsectionID * pSignImageInfo->u32SignedDataLength;
                    else if (u32ChunkNum == index)
                        u32MergeDataLen = pSignImageInfo->u32SignedDataLength - u32MergeDataOffset;
                    else
                        u32MergeDataLen = tmpChunkHead->offset + tmpChunkHead->chunk_sz * pSparseHead->blk_sz - pSignImageInfo->u32CurrentsectionID * pSignImageInfo->u32SignedDataLength - u32MergeDataOffset;
                    memset((HI_U8 *)(pCAImageArea + u32MergeDataOffset), 0, u32MergeDataLen);
                    u32MergeDataOffset += u32MergeDataLen;
                }
                else
                {
                    if (0 != index)
                        u32MergeDataOffset +=  tmpChunkHead->chunk_sz * pSparseHead->blk_sz;
                }
                tmpChunkHead++;
            }
        }
    }
#endif

    if(pSignImageInfo->u32IsEncrypted == HI_TRUE)
    {
        HI_INFO_CA("Need to Decrypt image \n");
        CA_DataDecrypt(pCAImageArea, PartitionImagSize, pCAImageArea);
    }
    //We can check SHA value!
    if(pSignImageInfo->u32HashType == Algoritm_Hash1)
    {
        dcache_enable(g_DDRSize);
        sha1((HI_U8 *)pCAImageArea, pSignImageInfo->u32SignedDataLength, TmpSha);
        dcache_disable();
        for(index = 0; index < 5; index ++)
        {
            if(TmpSha[index] != pSignImageInfo->u8Sha[index])
            {
                HI_ERR_CA("error index:%d sha:0x%2x != 0x%2x\n", TmpSha[index], pSignImageInfo->u8Sha[index]);
                return HI_FAILURE;
            }
        }
    }
    else
    {
        HI_INFO_CA("begin sha2, length:%d\n", pSignImageInfo->u32SignedDataLength);

        g_DDRSize = 512*1024*1024;
        dcache_enable(g_DDRSize);
        sha2((HI_U8 *)pCAImageArea, pSignImageInfo->u32SignedDataLength, TmpSha, 0);
        dcache_disable();

        for(index = 0; index < 32; index ++)
        {
            if(TmpSha[index] != pSignImageInfo->u8Sha[index])
            {
                HI_ERR_CA("error index:%d sha:0x%2x != 0x%2x\n", index, TmpSha[index], pSignImageInfo->u8Sha[index]);
                return HI_FAILURE;
            }
        }
    }
    HI_INFO_CA("Sha check ok\n");
    //Now, We got clean image data!
    pSignParam->pImageData = pCAImageArea;
    pSignParam->ImageDataLength = pSignImageInfo->u32SignedDataLength;
    pSignParam->pCASignTail = pSignImageInfo;

    return 0;
}

HI_S32 HI_CA_CommonVerify_Signature(HI_U8 *PartitionImagenName, HI_U8 *PartitionSignName, HI_U32 offset)
{
    HI_S32 ret = 0, index = 0;
    HI_U32 u32TotalSection = 0;
    HI_CASignImageTail_S SignImageInfo;
    HI_CA_NEW_SignParam_S SignParam;

    //Verify Partition
    CA_CheckPointer(PartitionImagenName);
    CA_CheckPointer(PartitionSignName);

    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);

    CA_ASSERT(CA_Common_Search_SignHeader(PartitionSignName, &SignImageInfo, &offset),ret);
    CA_ASSERT(Debug_CASignImageTail_Value(&SignImageInfo),ret);

    u32TotalSection = SignImageInfo.u32TotalsectionID;
    if(u32TotalSection >= 1)
    {
        for(index = 0; index < u32TotalSection; index++)
        {
            CA_ASSERT(CA_Common_Search_SignHeader(PartitionSignName, &SignImageInfo, &offset),ret);
            CA_ASSERT(Debug_CASignImageTail_Value(&SignImageInfo),ret);

            //Get image data
            CA_ASSERT(CA_Common_GetImageData(PartitionImagenName, &SignImageInfo, &SignParam),ret);
            //Verify image signature
            CA_ASSERT(HI_CA_ImgAuthenticate((HI_U32)(SignParam.pImageData), SignParam.ImageDataLength, SignParam.pCASignTail->u8Signature),ret);

            offset += NAND_PAGE_SIZE;
        }
    }
    else
    {
        HI_ERR_CA("Err u32TotalsectionID = %d\n", u32TotalSection);
    }

    HI_INFO_CA("Check Authenitication is ok\n");

    HI_SIMPLEINFO_CA("u8Hash1:\n");
    printf_hex(SignImageInfo.u8Sha, 32);
    if (!memcmp(PartitionImagenName, "recovery", sizeof(PartitionImagenName)))
    {
        memcpy(&g_partition_hash[32], SignImageInfo.u8Sha, 32);
    }
    if (!memcmp(PartitionImagenName, "kernel", sizeof(PartitionImagenName)))
    {
        memcpy(&g_partition_hash[64], SignImageInfo.u8Sha, 32);
    }

    CA_AuthenticateDeInit();

    return 0;
}

HI_S32 HI_CA_CommonVerify_Section_Signature(HI_U8 *PartitionImagenName, HI_U8 *PartitionSignName, HI_U32 offset)
{
    HI_S32 ret = 0, index = 0;
    HI_U32 u32TotalSection = 0;
    HI_U32 u32random;
    HI_CASignImageTail_S SignImageInfo;
    HI_CA_NEW_SignParam_S SignParam;

    //Verify Partition
    CA_CheckPointer(PartitionImagenName);
    CA_CheckPointer(PartitionSignName);

    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);

    if ((0xFF == IsSparseFlag) &&
        (!memcmp(PartitionSignName, SYSTEM_SIGN_PARTITION, strlen(SYSTEM_SIGN_PARTITION))) &&
        (!memcmp(PartitionSignName, SYSTEM_IMG_PARTITION, strlen(SYSTEM_IMG_PARTITION)))
        )
    {
        IsSparseFlag = 0;
    }
    CA_ASSERT(CA_Common_Search_SignHeader(PartitionSignName, &SignImageInfo, &offset),ret);
    CA_ASSERT(Debug_CASignImageTail_Value(&SignImageInfo),ret);

    u32TotalSection = SignImageInfo.u32TotalsectionID;
    ca_srandom(READ_TIMER2 & 0xFFFFFFFF);
    u32random = ca_random() % 10 + 1;

    if(u32TotalSection >= 1)
    {
        for(index = 0; index < u32TotalSection;)
        {
            CA_ASSERT(CA_Common_Search_SignHeader(PartitionSignName, &SignImageInfo, &offset),ret);
            CA_ASSERT(Debug_CASignImageTail_Value(&SignImageInfo),ret);

            //Get image data
            CA_ASSERT(CA_Common_GetImageData(PartitionImagenName, &SignImageInfo, &SignParam),ret);
            //Verify image signature
            CA_ASSERT(HI_CA_ImgAuthenticate((HI_U32)(SignParam.pImageData), SignParam.ImageDataLength, SignParam.pCASignTail->u8Signature),ret);
            if (0 == index)
            {
                index = u32random;
            }
            else
            {
                index = index + 10;
            }
            offset = NAND_PAGE_SIZE * index;
        }
    }
    else
    {
        HI_ERR_CA("Err u32TotalsectionID = %d\n", u32TotalSection);
    }

    HI_INFO_CA("Check Authenitication is ok\n");
    CA_AuthenticateDeInit();
    return 0;
}


HI_S32 HI_CA_CommonVerify_EncryptImage(HI_U8 *PartitionImagenName, HI_U8 *PartitionSignName, HI_U32 offset)
{
    HI_S32 ret = 0;
    HI_U32 EncryptLength = 0;
    HI_CASignImageTail_S SignImageInfo;
    HI_CA_NEW_SignParam_S SignParam;
    HI_U32 PartionSize;
    HI_U32 PageSize;
    HI_U32 BlockSize;
    HI_U32 OobSize;

    //Verify Partition
    CA_CheckPointer(PartitionImagenName);
    CA_CheckPointer(PartitionSignName);

    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);

    CA_ASSERT(CA_Common_Search_SignHeader(PartitionSignName, &SignImageInfo, &offset),ret);
    Debug_CASignImageTail_Value(&SignImageInfo);
    //Get image data
    CA_ASSERT(CA_Common_GetImageData(PartitionImagenName, &SignImageInfo, &SignParam),ret);
    //Verify image signature
    CA_ASSERT(HI_CA_ImgAuthenticate(SignParam.pImageData, SignParam.ImageDataLength, SignParam.pCASignTail->u8Signature),ret);
    HI_INFO_CA("Check Authenitication is ok\n");

    if(SignImageInfo.u32IsNeedEncrypt == 0)
    {
        HI_ERR_CA("Do not need to encrypt image\n");
        return 0;
    }
    else if(SignImageInfo.u32IsEncrypted == 1)
    {
        HI_ERR_CA("Image pariton is already encrypted\n");
        return 0;
    }

    if(strncmp(PartitionImagenName, PartitionSignName, MAX_STRLEN(PartitionImagenName, PartitionSignName)) == 0)
    {
        HI_ERR_CA("Error Image Partition and SignImagePartion are the same(%s)\n", PartitionSignName);
        return -1;
    }
    if(SignImageInfo.u32IsYaffsImage != 0)
    {
        HI_ERR_CA("Error Yaffs Image can not be encrypted\n");
        return -1;
    }

    //User R2R to encrypt Image Data Partition
    CA_ASSERT(CA_flash_getinfo(PartitionImagenName, &PartionSize, &BlockSize, &PageSize, &OobSize),ret);
    HI_INFO_CA("NAND BlockSize:0x%x, PageSize:0x%x, OobSize:0x%x\n", BlockSize, PageSize, OobSize);
    EncryptLength = (SignParam.ImageDataLength + BlockSize - 1) & (~(BlockSize -1));

    CA_ASSERT(CA_DataEncrypt((HI_U8*)SignParam.pImageData, EncryptLength, (HI_U8*)SignParam.pImageData),ret);

    //write data back to flash
    CA_ASSERT(CA_flash_write(PartitionImagenName, 0x00, EncryptLength, (HI_U8*)SignParam.pImageData),ret);
    //Set SignHead Encrypt flag to true
    SignImageInfo.u32IsEncrypted = 1;
    SignImageInfo.CRC32 = DVB_CRC32((HI_U8*)(&SignImageInfo), (sizeof(HI_CASignImageTail_S) - 4));
    HI_INFO_CA("new crc32:%x\n", SignImageInfo.CRC32);
    //write data back to flash
    CA_ASSERT(CA_flash_write(PartitionSignName, 0x00, BlockSize, (HI_U8*)(&SignImageInfo)),ret);

    CA_AuthenticateDeInit();
    return 0;
}


HI_S32 HI_CA_CommonVerify_BootPara(HI_U32 u32ParaPartionAddr, HI_U32 u32ParaParitonSize)
{
    HI_S32 ret = 0, index;
    HI_CASignImageTail_S SignImageInfo;
    HI_U8 *ParaBase, *CAImageArea;
    HI_U32 IsFoundFlag = HI_FALSE;
    HI_U8 TmpSha[32];

    CA_ASSERT(CA_AuthenticateInit(HI_CA_KEY_GROUP_1),ret);

    ParaBase = (HI_U8*)IMG_VERIFY_ADDRESS;

    //Read out flash data
    CA_ASSERT(CA_flash_read_addr(u32ParaPartionAddr, u32ParaParitonSize, ParaBase, HI_NULL),ret);
    //Get Signature of bottargrs pariton!
    for(index = 0; index < u32ParaParitonSize/NAND_PAGE_SIZE; index ++)
    {
        CAImageArea = ParaBase + index * NAND_PAGE_SIZE;
        memcpy(&SignImageInfo, CAImageArea, sizeof(HI_CASignImageTail_S));
        if(!memcmp(SignImageInfo.u8MagicNumber, CAIMGHEAD_MAGICNUMBER, sizeof(SignImageInfo.u8MagicNumber)))
        {
            unsigned int CRC32Value;
            HI_INFO_CA("Sign Header found!\n");
            IsFoundFlag = HI_TRUE;
            //Clacluate CRC32!
            CRC32Value = DVB_CRC32((HI_U32 *)&SignImageInfo, (sizeof(HI_CASignImageTail_S) - 4));
            if(CRC32Value == SignImageInfo.CRC32)
            {
                HI_INFO_CA("CRC32 check ok\n");
            }
            else
            {
                HI_ERR_CA("CRC32Value:%x != SignImageInfo.CRC32:%x\n", CRC32Value, SignImageInfo.CRC32);
                return HI_FAILURE;
            }
            break;
        }
        else
        {
            continue;
        }
    }
    if(IsFoundFlag != HI_TRUE)
    {
        HI_INFO_CA("Sign Header is not correct!\n");
        return HI_FAILURE;
    }
    //We can check SHA value!
    if(SignImageInfo.u32HashType == Algoritm_Hash1)
    {
        dcache_enable(g_DDRSize);
        sha1((HI_U8 *)ParaBase, SignImageInfo.u32SignedDataLength, TmpSha);
        dcache_disable();
        for(index = 0; index < 5; index ++)
        {
            if(TmpSha[index] != SignImageInfo.u8Sha[index])
            {
                HI_ERR_CA("error index:%d sha:0x%2x != 0x%2x\n", TmpSha[index], SignImageInfo.u8Sha[index]);
                return HI_FAILURE;
            }
        }
    }
    else
    {
        HI_INFO_CA("begin sha2, length:%d\n", SignImageInfo.u32SignedDataLength);

        dcache_enable(g_DDRSize);
        sha2((HI_U8 *)ParaBase, SignImageInfo.u32SignedDataLength, TmpSha, 0);
        dcache_disable();

        for(index = 0; index < 32; index ++)
        {
            if(TmpSha[index] != SignImageInfo.u8Sha[index])
            {
                HI_ERR_CA("error index:%d sha:0x%2x != 0x%2x\n", index, TmpSha[index], SignImageInfo.u8Sha[index]);
                return HI_FAILURE;
            }
        }
    }
    HI_INFO_CA("Sha check ok\n");
    CA_ASSERT(Debug_CASignImageTail_Value(&SignImageInfo),ret);

    //Verify image signature
    CA_ASSERT(HI_CA_ImgAuthenticate((HI_U8 *)ParaBase, SignImageInfo.u32SignedDataLength, SignImageInfo.u8Signature),ret);

    HI_INFO_CA("Check Authenitication is ok\n");

    memcpy(g_partition_hash, SignImageInfo.u8Sha, 32);
    CA_AuthenticateDeInit();
    return ret;
}
#else //#ifndef HI_ADVCA_TYPE_VERIMATRIX

#ifdef HI_MINIBOOT_SUPPORT
extern int reboot();
#endif

HI_VOID CA_Reset(HI_VOID)
{
#ifndef HI_MINIBOOT_SUPPORT
    HI_INFO_CA(" \n");
    do_reset (NULL, 0, 0, NULL);
    do_reset (NULL, 0, 0, NULL);
    do_reset (NULL, 0, 0, NULL);
    while(1) { };
#else
    reboot();
#endif
}

extern char* getenv(char *);

HI_VOID CA_SetEnv(HI_CHAR* args)
{
    HI_CHAR *s = NULL;
    HI_CHAR buf[4096] = {0};

    memset(buf,0,sizeof(buf));

    if((s = getenv(args)) != NULL)
    {
        HI_DEBUG_CA("%s = %s\n",args,s);
        snprintf(buf, sizeof(buf), "%s", s);
        setenv(args,buf);
    }
}

HI_S32 CA_nand_env_relocate_spec(HI_U8 *u8EnvAddr)
{
    CA_SetEnv("bootargs");
    CA_SetEnv("loaderargs");

#ifndef  HI_ADVCA_FUNCTION_RELEASE
//    CA_SetEnv("bootcmd");
    CA_SetEnv("ipaddr");
    CA_SetEnv("serverip");
    CA_SetEnv("gatewayip");
    CA_SetEnv("netmask");
    CA_SetEnv("ethaddr");
#endif

    return 0;
}

extern HI_U32 g_EnvFlashAddr;
extern HI_U32 g_EnvFlashPartionSize;

#ifdef HI_ADVCA_TYPE_VERIMATRIX
static HI_S32 VMX_PrintBuffer(const HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{

    HI_U32 i = 0;

    if ( NULL != string )
    {
        printf("%s\n", string);
    }

    for ( i = 0 ; i < u32Length; i++ )
    {
        if( (i % 16 == 0) && (i != 0)) printf("\n");
        printf("%02x ", pu8Input[i]);
    }
    printf("\n");

    return HI_SUCCESS;
}

#define VMX_SIG_OFFSET  (16)
#define VMX_SIG_LENGTH  (256)
#define VMX_IMG_OFFSET  (VMX_SIG_OFFSET + VMX_SIG_LENGTH)
#define VMX_HEAD_LENGTH (VMX_IMG_OFFSET)

static HI_VOID printbuffer(HI_U8 *pu8Buf, HI_U32 u32Length)
{
    HI_U32 i;

    for(i = 0; i < u32Length; i++)
    {
        if(i % 16 == 0 && i != 0)
        {
            printf("\n");
        }
        printf("0x%02X, ", pu8Buf[i]);
    }
    printf("\n");

    return;
}

static VMX_Auth_Partition_Image(HI_CHAR *partition_name, HI_U8 *ptr)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 image_len = 0;
    HI_U8 errorCode = 0;
    HI_U32 tmp_len = 0;
    HI_U8 *pu8Tmp = NULL;

    if(NULL == partition_name)
    {
        printf("%s %d, failed, NULL pointer!\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    image_len = *((HI_U32 *)ptr);
    printf("%s image_len: 0x%08x\n", partition_name, image_len);

    if(0 != (image_len & 0xF))
    {
        printf("%s %d, failed, Invalid image_len:0x%x!\n", __FUNCTION__, __LINE__, image_len);
        return HI_FAILURE;
    }

    pu8Tmp = (HI_U8 *)reserve_mem_alloc(image_len, &tmp_len);
    if((NULL == pu8Tmp) || (tmp_len < image_len))
    {
        printf("VMX_Auth_Partition_Image: reserve_mem_alloc:0x%08x failed\n", image_len);
        return HI_FAILURE;
    }
    else
    {
        printf("VMX_Auth_Partition_Image: reserve_mem_alloc:0x%08x success\n", image_len);
    }

    /*
        errorCode is a pointer to a value that tells the reason for not having a valid image
            1 means no valid signature found - reboot
            2 means store src part to flash and reboot after it
        return value
            0 indicates do not start the application
            1 indicates the application can be started

        There are three situations: ret=1; ret=0 and errorCode=1;  ret=0 and errorCode=2;
    */
    ret = verifySignature((ptr + VMX_SIG_OFFSET),
                        (ptr + VMX_IMG_OFFSET),
                        pu8Tmp,
                        image_len,
                        image_len,
                        0,
                        &errorCode);
    if(1 == ret)
    {
        printf("verify success! ret:0x%x, Continue ...\n", ret);
        return HI_SUCCESS;
    }
    else if((1 == errorCode) && (0 == ret))         /* Invalid signature, maybe */
    {
        printf("do not start the application, reset! errorCode: 0x%x, ret: 0x%x, Resetting ...\n", errorCode, ret);
        CA_Reset();
    }
    else if((2 == errorCode) && (0 == ret))         /* Src is re-encrypted inside BL library, burn to flash */
    {
        printf("verify success! burn src to flash, errorCode:0x%x\n", errorCode);

        HI_U32 PartionSize = 0;
        HI_U32 BlockSize = 0;
        HI_U32 PageSize = 0;
        HI_U32 OobSize = 0;
        HI_U32 write_length = 0;

        ret = CA_flash_getinfo(partition_name, &PartionSize, &BlockSize, &PageSize, &OobSize);
        if(HI_SUCCESS != ret)
        {
            printf("CA_flash_getinfo failed! ret:0x%x\n", ret);
            return HI_FAILURE;
        }

        write_length = ((VMX_HEAD_LENGTH + image_len) + BlockSize - 1) & (~(BlockSize -1));

        printf("before write(32 bytes):\n");
        printbuffer(ptr, 32);

        printf("write info: partition_name:%s\, BlockSize:0x%x, PageSize:0x%x, OobSize:0x%x, write_length:0x%x\n", partition_name, BlockSize, PageSize, OobSize, write_length);
        ret = CA_flash_write(partition_name, (HI_U64)0, write_length, ptr);
        if(HI_SUCCESS != ret)
        {
            printf("Burn image to flash failed! ret:0x%x, Resetting ...\n", ret);
            CA_Reset();
        }
        else
        {
            printf("\nWrite src to flash success, ret:0x%x! Resetting ...\n", ret);
            CA_Reset();
        }
    }
    else
    {
        //not supported;
    }

    return HI_SUCCESS;
}



#define VMX_VERIFY_MEM_ALLOC_SIZE  (0x4000000)
HI_S32 HI_CA_AuthenticateEntry_VMX(HI_VOID)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 *ParaBase = (HI_U8*)IMG_VERIFY_ADDRESS;
    HI_U32 u32KernelSize = 0;
    HI_U32 u32FsSize = 0;
    HI_U8 *ptr = NULL;
    HI_U8 *ptr_trace = NULL;
    HI_Flash_InterInfo_S flashInfo;

    HI_U32 KernelPartionSize = 0;
    HI_U32 LoaderPartionSize = 0;
    HI_U32 BlockSize = 0;
    HI_U32 PageSize = 0;
    HI_U32 OobSize = 0;
    HI_U32 u32FSReadSize = 0;
    HI_U32 u32TotalBufLen = 0;
    HI_CHAR *loader_name = "loader";
    HI_CHAR *kernel_name = "kernel";
    HI_CHAR *rootfs_name = "rootfs";

    printf("HI_CA_AuthenticateEntry_VMX start --->\n");

    /* Read and setenv bootargs data first */
    ret = CA_flash_read_addr(g_EnvFlashAddr, g_EnvFlashPartionSize, ParaBase, HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("CA_flash_read_addr: env_addr:0x%x, size:0x%x failed\n", g_EnvFlashAddr, g_EnvFlashPartionSize);
        return HI_FAILURE;
    }
    (HI_VOID)CA_nand_env_relocate_spec(ParaBase);

#if 0
    ptr = (HI_U8 *)reserve_mem_alloc(VMX_VERIFY_MEM_ALLOC_SIZE, &u32TotalBufLen);
    if((NULL == ptr) || (u32TotalBufLen < VMX_VERIFY_MEM_ALLOC_SIZE))
    {
        printf("HI_CA_AuthenticateEntry_VMX: reserve_mem_alloc:0x%08x failed\n", VMX_VERIFY_MEM_ALLOC_SIZE);
        return HI_FAILURE;
    }
    else
    {
        printf("HI_CA_AuthenticateEntry_VMX: reserve_mem_alloc:0x%08x success\n", VMX_VERIFY_MEM_ALLOC_SIZE);
        ptr_trace = ptr;
    }
#else
    ptr = (HI_U8 *)IMG_VERIFY_ADDRESS;
    ptr_trace = ptr;
#endif

    /* prepare the loader image data to ddr */
    ret = CA_flash_getinfo(loader_name, &LoaderPartionSize, &BlockSize, &PageSize, &OobSize);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("%s %d, failed, ret!\n", __FUNCTION__, __LINE__, ret);
        return HI_FAILURE;
    }

    ret = CA_flash_read(loader_name, 0, LoaderPartionSize, ptr_trace, &flashInfo);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("%s %d, failed, ret!\n", __FUNCTION__, __LINE__, ret);
        return HI_FAILURE;
    }
    printf("%s partition size is: 0x%x\n", loader_name, LoaderPartionSize);
    ptr_trace += LoaderPartionSize;

    /* prepare kernel image data to ddr */
    ret = CA_flash_getinfo(kernel_name, &KernelPartionSize, &BlockSize, &PageSize, &OobSize);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("%s %d, failed, ret!\n", __FUNCTION__, __LINE__, ret);
        return HI_FAILURE;
    }

    ret = CA_flash_read(kernel_name, 0, KernelPartionSize, ptr_trace, &flashInfo);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("%s %d, failed, ret!\n", __FUNCTION__, __LINE__, ret);
        return HI_FAILURE;
    }
    printf("%s partition size is: 0x%x\n", kernel_name, KernelPartionSize);
    ptr_trace += KernelPartionSize;

    /* prepare fs image data to ddr */
    ret = CA_flash_read(rootfs_name, 0, PageSize, ptr_trace, &flashInfo);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("%s %d, failed, ret!\n", __FUNCTION__, __LINE__, ret);
        return HI_FAILURE;
    }
    u32FsSize = *(HI_U32 *)ptr_trace;
    u32FSReadSize = PageSize * ((VMX_SIG_OFFSET + VMX_SIG_LENGTH + u32FsSize + PageSize -1)/PageSize);
    printf("%s partition size is: 0x%x, u32FSReadSize:0x%x\n", rootfs_name, u32FsSize, u32FSReadSize);

    ret = CA_flash_read(rootfs_name, 0, u32FSReadSize, ptr_trace, &flashInfo);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("%s %d, failed, ret!\n", __FUNCTION__, __LINE__, ret);
        return HI_FAILURE;
    }

    /* verify images now */
    ret = VMX_Auth_Partition_Image(loader_name, ptr);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("VMX_Auth_Partition_Image:%s failed\n", loader_name);
        CA_Reset();
    }
    printf("Authenticate %s success.\n\n\n", loader_name);

    ret = VMX_Auth_Partition_Image(kernel_name, ptr + LoaderPartionSize);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("VMX_Auth_Partition_Image:%s failed\n", kernel_name);
        CA_Reset();
    }
    printf("Authenticate %s success.\n\n\n", kernel_name);

    ret = VMX_Auth_Partition_Image(rootfs_name, ptr + LoaderPartionSize + KernelPartionSize);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("VMX_Auth_Partition_Image:%s failed\n", rootfs_name);
        CA_Reset();
    }
    printf("Authenticate %s success.\n\n\n", rootfs_name);

    /* start the kernel */
#ifdef HI_MINIBOOT_SUPPORT
    //HI_U32 addr = ptr + VMX_SIG_OFFSET + VMX_SIG_LENGTH;
    //kern_load((char *)addr);
#else
    run_command("bootm 0x4000110", 0);
#endif

    return HI_SUCCESS;
}
#endif

#endif //#ifndef HI_ADVCA_TYPE_VERIMATRIX

