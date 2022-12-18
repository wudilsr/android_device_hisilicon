/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : cmd_authenticate.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 204-09-19
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef HI_ADVCA_FUNCTION_RELEASE

#ifndef HI_MINIBOOT_SUPPORT
#include "ca_authenticate.h"
#include "hi_unf_cipher.h"
#include "hi_unf_otp.h"
#include "hi_unf_advca.h"
#include "ca_common.h"

extern HI_U32 g_EnvFlashAddr;
extern HI_U32 g_EnvFlashPartionSize;
extern HI_U32 g_EnvFlashPartionSize;
extern HI_U8  g_customer_blpk[16];
extern HI_U8  g_customer_rsa_public_key_N[256];
extern HI_U32  g_customer_rsa_public_key_E;

#define MAX_DATA_LEN (1024*1024 - 16) //the max data length for encryption / decryption

#ifndef HI_ADVCA_TYPE_VERIMATRIX
U_BOOT_CMD(CXSecSystemBoot, 1, 1, HI_CA_AuthenticateEntry, "Conax CA security system booting", "eg: CX_SecSystemBoot");

/* special signing test */
#ifdef CA_CMD_SIGN_TYPE_SPECIAL_TEST
static HI_S32 CA_Special_BurnFlashName(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;
    HI_U32 addr = 0;

    if (argc != 3)
    {
        HI_SIMPLEINFO_CA( "ca_special_burnflashname  - burn DDR image to  flash_patition_name, for example: ca_special_burnflashname  DDRAddress FlashPartition (eg: ca_special_burnflashname 1000000 kernel)\n\n");
        return 0;
    }

    addr = simple_strtoul(argv[1], NULL, 16);
    HI_DEBUG_CA("burn DDR address 0x%x  to flash area %s\n",addr,argv[2]);

    CA_ASSERT(HI_CA_EncryptDDRImageAndBurnFlashName((HI_U8*)addr,(HI_U8*)argv[2]),ret);
    HI_DEBUG_CA("ca_special_burnflashname success\n");

    return ret;
}
U_BOOT_CMD(ca_special_burnflashname,3,1,CA_Special_BurnFlashName,\
"Encrypt DDR image with R2R Key-ladder and burn DDR image into flash", "ca_special_burnflashname  DDRAddress FlashPartition (eg: ca_special_burnflashname 1000000 kernel)");

HI_S32 CA_Special_BurnFlashNameByLen(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;
    HI_U32 addr = 0;
    HI_U32 len = 0;
    HI_U32 FlashWriteSize = 0;
    HI_U8* pImageDDRAddress = NULL;
    if (argc != 4)
    {
        HI_SIMPLEINFO_CA( "ca_special_burnflashnamebylen  - burn DDR image to  flash_patition_name, for example: ca_special_burnflashnamebylen  DDRAddress ImageLen FlashPartition (eg: ca_special_burnflashnamebylen 1000000 80000 logo)\n");
        return 0;
    }
    addr = simple_strtoul(argv[1], NULL, 16);
    pImageDDRAddress = (HI_U8*)addr;
    len =   simple_strtoul(argv[2], NULL, 16);
    len =  (len + NAND_PAGE_SIZE - 1)& (~(NAND_PAGE_SIZE -1) );
    HI_DEBUG_CA("burn DDR address 0x%x  with len = 0x%x to flash area %s\n",addr,len ,argv[3]);

    CA_ASSERT(HI_CA_EncryptDDRImageAndBurnFlashNameByLen(pImageDDRAddress,len,argv[3]),ret);
    HI_DEBUG_CA("ca_special_burnflashnamebylen success\n");
    return ret;
}
U_BOOT_CMD(ca_special_burnflashnamebylen,4,1,CA_Special_BurnFlashNameByLen,\
"Encrypt DDR image with R2R Key-ladder and burn DDR image into flash", "ca_special_burnflashnamebylen  DDRAddress ImageLen FlashPartition (eg: ca_special_burnflashnamebylen 1000000 80000 logo)");



HI_S32 CA_DecryptFlashImage2DDRTest(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;

    if (argc != 2)
    {
        HI_SIMPLEINFO_CA( "ca_decryptflashpartition  - decrypt flash_patition_name to DDR, for example: DecryptFlashPartition kernel\n");
        return 0;
    }

    HI_DEBUG_CA("HI_CA_DecryptFlashImage2DDR %s\n",argv[1]);
    CA_ASSERT(HI_CA_DecryptFlashImage2DDR((HI_U8*)argv[1]),ret);
    HI_DEBUG_CA("HI_CA_DecryptFlashImage2DDR success\n");

    return ret;
}
U_BOOT_CMD(ca_decryptflashpartition,2,1,CA_DecryptFlashImage2DDRTest,"decrypt flash_patition_name to DDR", "eg:ca_decryptflashpartition kernel");



HI_S32 CA_Special_FlashAuthenticateDebug(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;

    if (argc != 2)
    {
        HI_SIMPLEINFO_CA( "ca_special_verify  - ca_special_verify flash_patition_name, for example: ca_special_verify bootpara\n");
        return 0;
    }

    HI_DEBUG_CA("CA_FlashAuthenticate %s\n",argv[1]);
    CA_ASSERT(HI_CA_FlashAuthenticateByName((HI_U8*)argv[1], NULL), ret);
    HI_DEBUG_CA("ca_special_verify success\n");
    return ret;
}
U_BOOT_CMD(ca_special_verify, 2, 1, CA_Special_FlashAuthenticateDebug, \
"ca_special_verify flash_patition_name", "eg: ca_special_verify bootpara");



HI_S32 CA_Special_FlashAuthenticateAddrDebug(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;
    HI_U32 addr = 0;
    HI_U32 ImgInDDRAddress = 0;

    if (argc != 2)
    {
        HI_SIMPLEINFO_CA("ca_special_verifyaddr- ca_special_verifyaddr flash_patition_Addr, for example: ca_special_verifyaddr 0x100000\n");
        return 0;
    }

    addr = simple_strtoul(argv[1], NULL, 16);
    HI_DEBUG_CA("HI_CA_FlashAuthenticateByAddr 0x%X\n",addr);

    CA_ASSERT(HI_CA_FlashAuthenticateByAddr(addr,HI_FALSE,&ImgInDDRAddress),ret);
    HI_DEBUG_CA("ca_special_verifyaddr success\n");

    return ret;
}
U_BOOT_CMD(ca_special_verifyaddr,2,1,CA_Special_FlashAuthenticateAddrDebug,"ca_special_verifyaddr flash_patition_Addr", "eg: ca_special_verifyaddr 0x100000");



HI_S32 CA_Special_AuthenticateBootParaDebug(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;

    if (argc != 1)
    {
        HI_SIMPLEINFO_CA("ca_special_verifybootargs- verify bootargs, for example: ca_special_verifybootargs\n");
        return 0;
    }

    ret = HI_CA_AuthenticateBootPara();
    HI_DEBUG_CA("ca_special_verifybootargs success\n");
    return ret;
}
U_BOOT_CMD(ca_special_verifybootargs,1,1,CA_Special_AuthenticateBootParaDebug,"verify bootargs", "eg: ca_special_verifybootargs");
#endif /* endif CA_CMD_SIGN_TYPE_SPECIAL_TEST */

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

HI_VOID compare_hex(char *title, HI_U8 *pu8Src, HI_U8 *pu8Dst, HI_U32 u32Length)
{
    HI_U32 i;

    for(i = 0; i < u32Length; i++)
    {
        if(pu8Src[i] != pu8Dst[i])
        {
           HI_SIMPLEINFO_CA("\033[0;31m" "%s failed!\n" "\033[0m", title);
           return;
        }
    }
    HI_SIMPLEINFO_CA("%s success!\n", title);
    return;
}

//test for AES CBC MAC
HI_U8 g_M[64] = {
0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,
0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11,
0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17,
0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10
};

HI_U8 g_K[16] = {
0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
};

HI_U8 AEC_CBC_MAC_0[16] = {
0xBB, 0x1D, 0x69, 0x29, 0xE9, 0x59, 0x37, 0x28,
0x7F, 0xA3, 0x7D, 0x12, 0x9B, 0x75, 0x67, 0x46
};

HI_U8 AEC_CBC_MAC_16[16] = {
0x07, 0x0A, 0x16, 0xB4, 0x6B, 0x4D, 0x41, 0x44,
0xF7, 0x9B, 0xDD, 0x9D, 0xD0, 0x4A, 0x28, 0x7C
};

HI_U8 AEC_CBC_MAC_40[16] = {
0xDF, 0xA6, 0x67, 0x47, 0xDE, 0x9A, 0xE6, 0x30,
0x30, 0xCA, 0x32, 0x61, 0x14, 0x97, 0xC8, 0x27
};

HI_U8 AEC_CBC_MAC_64[16] = {
0x51, 0xF0, 0xBE, 0xBF, 0x7E, 0x3B, 0x9D, 0x92,
0xFC, 0x49, 0x74, 0x17, 0x79, 0x36, 0x3C, 0xFE
};


HI_S32 cipher_cbc_mac_test(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{

    HI_U8 u8EncryptKey[16];
    HI_U8 T[16];
    HI_U8 M[64] = {
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
        0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
        0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c,
        0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
        0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11,
        0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
        0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17,
        0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10
    };
    HI_U8 key[16] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
    };

    HI_UNF_ADVCA_Init();

    //encrypt the key first, the swpk keyladder should use the encrypted key
    generate_encrypt_key(key, u8EncryptKey);

    HI_SIMPLEINFO_CA("\nExample 1: len = 0\n");
    HI_SIMPLEINFO_CA("M "); HI_SIMPLEINFO_CA("<empty string>\n");
    HI_CA_CalcMAC(u8EncryptKey, M, 0, T, HI_TRUE);
    HI_SIMPLEINFO_CA("AES_CMAC "); printf_hex(T, 16); HI_SIMPLEINFO_CA("\n");
    compare_hex("M_0", AEC_CBC_MAC_0, T, 16);

    HI_SIMPLEINFO_CA("\nExample 2: len = 16\n");
    HI_SIMPLEINFO_CA("M "); printf_hex(M, 16);
    HI_CA_CalcMAC(u8EncryptKey, M, 16, T, HI_TRUE);
    HI_SIMPLEINFO_CA("AES_CMAC "); printf_hex(T, 16); HI_SIMPLEINFO_CA("\n");
    compare_hex("M_16", AEC_CBC_MAC_16, T, 16);

    HI_SIMPLEINFO_CA("\nExample 3: len = 40\n");
    HI_SIMPLEINFO_CA("M "); printf_hex(M, 40);

    HI_CA_CalcMAC(u8EncryptKey,M, 16, T, HI_FALSE);
    HI_CA_CalcMAC(u8EncryptKey,M + 16, 16, T, HI_FALSE);
    HI_CA_CalcMAC(u8EncryptKey,M + 32, 8, T, HI_TRUE);

    HI_SIMPLEINFO_CA("AES_CMAC "); printf_hex(T, 16); HI_SIMPLEINFO_CA("\n");
    compare_hex("M_40", AEC_CBC_MAC_40, T, 16);

    HI_SIMPLEINFO_CA("\nExample 4: len = 64\n");
    HI_CA_CalcMAC(u8EncryptKey, M, 64, T, HI_TRUE);
    HI_SIMPLEINFO_CA("AES_CMAC "); printf_hex(T, 16); HI_SIMPLEINFO_CA("\n");
    compare_hex("M_64", AEC_CBC_MAC_64, T, 16);

    HI_U32 timeuse = 0;
    HI_U32 newtime, oldtime;
    HI_U32 i;

    oldtime = get_timer(0);

    HI_SIMPLEINFO_CA("start 300M data test......\r\n");

    for(i = 0; i < 299; i++)
    {
        HI_CA_CalcMAC(u8EncryptKey, IMG_VERIFY_ADDRESS, 0x100000, T, HI_FALSE);
    }
    HI_CA_CalcMAC(u8EncryptKey, IMG_VERIFY_ADDRESS, 0x100000, T, HI_TRUE);

    newtime = get_timer(0);
    timeuse= (newtime - oldtime)/get_tbclk();
    HI_SIMPLEINFO_CA("time use: %d s\r\n", timeuse);

    HI_SIMPLEINFO_CA("--------------------------------------------------\n");

    return 0;
}
U_BOOT_CMD(cipher_cbc_mac_test, 2, 1, cipher_cbc_mac_test, "", "");

/* normal signing test */
#ifdef CA_CMD_SIGN_TYPE_COMMON_TEST
HI_S32 CA_Common_VerifyImageSignature(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;

    if(argc >= 4)
    {
        HI_U32 offset = 0;

        offset = (HI_U32)simple_strtoul((const char *)argv[3], NULL, 16);
        CA_ASSERT(HI_CA_CommonVerify_Signature((HI_U8*)argv[1], (HI_U8*)argv[2], offset),ret);
    }
    else if(argc >= 3)
    {
        CA_ASSERT(HI_CA_CommonVerify_Signature((HI_U8*)argv[1], (HI_U8*)argv[2], 0),ret);
    }
    else if(argc >= 2)
    {
        CA_ASSERT(HI_CA_CommonVerify_Signature((HI_U8*)argv[1], (HI_U8*)argv[1], 0),ret);
    }
    else
    {
        HI_ERR_CA("Error Input, for example: ca_common_verify_image_signature imgepartionname signpartionname signoffsetinpartion\n");
    }

    return ret;
}

U_BOOT_CMD(ca_common_verify_image_signature,4,1,CA_Common_VerifyImageSignature, \
"verify pariton-image signature with tail mode","for example: ca_common_verify_image_signature imgepartionname signpartionname signoffsetinpartion");
#endif

#ifdef HI_ADVCA_TYPE_VERIMATRIX
extern HI_S32 VMX_CommonVerify_Signature_Test(HI_U8 *PartitionImagenName, HI_U8 *PartitionSignName, HI_U32 offset);
HI_S32 CA_Common_VerifyImageSignature_VMX(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;

    if(argc >= 4)
    {
        HI_U32 offset = 0;

        offset = (HI_U32)simple_strtoul((const char *)argv[3], NULL, 16);
        CA_ASSERT(VMX_CommonVerify_Signature_Test((HI_U8*)argv[1], (HI_U8*)argv[2], offset),ret);
    }
    else if(argc >= 3)
    {
        CA_ASSERT(VMX_CommonVerify_Signature_Test((HI_U8*)argv[1], (HI_U8*)argv[2], 0),ret);
    }
    else if(argc >= 2)
    {
        CA_ASSERT(VMX_CommonVerify_Signature_Test((HI_U8*)argv[1], (HI_U8*)argv[1], 0),ret);
    }
    else
    {
        HI_ERR_CA("Error Input, for example: ca_common_verify_image_signature_vmx_test imgepartionname signpartionname signoffsetinpartion\n");

    }

    return ret;
}

U_BOOT_CMD(ca_common_verify_image_signature_vmx_test,4,1,CA_Common_VerifyImageSignature_VMX, \
"verify pariton-image signature with tail mode","for example: ca_common_verify_image_signature_vmx_test imgepartionname signpartionname signoffsetinpartion");
#endif

HI_S32 CA_Common_VerifySystemSignature(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;

    if(argc >= 4)
    {
        HI_U32 offset = 0;

        offset = (HI_U32)simple_strtoul((const char *)argv[3], NULL, 16);
        CA_ASSERT(HI_CA_CommonVerify_Section_Signature((HI_U8*)argv[1], (HI_U8*)argv[2], offset),ret);
    }
    else if(argc >= 3)
    {
        CA_ASSERT(HI_CA_CommonVerify_Section_Signature((HI_U8*)argv[1], (HI_U8*)argv[2], 0),ret);
    }
    else if(argc >= 2)
    {
        CA_ASSERT(HI_CA_CommonVerify_Section_Signature((HI_U8*)argv[1], (HI_U8*)argv[1], 0),ret);
    }
    else
    {
        HI_ERR_CA("Error Input\n");
    }

    return ret;
}

U_BOOT_CMD(ca_common_verify_system_signature,4,1,CA_Common_VerifySystemSignature, \
"verify pariton-image signature with tail mode","for example: ca_common_verify_system_signature imgepartionname signpartionname signoffsetinpartion");



HI_S32 CA_Common_VerifyParseSignCommand(void)
{
    HI_S32 ret = 0;
    unsigned char  *str = NULL;        /* used to set string properties */
    int strlength = 0, offset = 0;
    unsigned char head[] = "sign:";
    unsigned char *pParamoffset, *pImageoffset;

    HI_U8 ImageName[50] = {0};
    HI_U8 SignName[50] = {0};
    HI_U32 SignLocationOffset = 0;

    str = getenv("signature_check");
    if (str == NULL)
    {
        HI_ERR_CA("can not find boot argures:signature_check\n");
        return HI_FAILURE;
    }
    strlength = strlen(str);
    if(strlength > 256)
    {
        HI_ERR_CA("signature_check is too long > 256,error\n");
        return -1;
    }

    //parse as: setenv signature_check 'sign:kernel,kernel,0x280000 sign:fs,fs,0x600000 sign:subfs,subfs,0x400000'
    offset = 0;
    while(offset <= strlength)
    {
        HI_U8  ImageName[50] = {0};
        HI_U8  SignName[50] = {0};
        HI_U32 SignOffset = 0;

        pParamoffset = (HI_U8 *)strstr((const char *)(str + offset), (const char *)head);
        if(pParamoffset == HI_NULL)
        {
            break;
        }

        //To get the Image,Image_Signature,SignatureOffset
        pImageoffset = pParamoffset + strlen(head);

        offset = pImageoffset - str;//change offset
        ret = CA_CommonParse_SubCommand(pImageoffset, strlen(pImageoffset), ImageName, SignName, &SignOffset);
        if (ret != 0)
        {
            HI_ERR_CA("Error to parse data\n");
            return -1;
        }
        HI_INFO_CA("verify image:%s, sign:%s, offset:0x%x\n", ImageName, SignName, SignOffset);
        ret = HI_CA_CommonVerify_Signature(ImageName, SignName, SignOffset);
        if (ret != 0)
        {
            HI_ERR_CA("Verify image %s failed!\n", ImageName);
            return -1;
        }
    }
    HI_INFO_CA("Finish\n");

    return 0;
}

U_BOOT_CMD(ca_common_verify_signature_check,2,1,CA_Common_VerifyParseSignCommand, \
"verify BootArgs signature_check","for example: ca_common_verify_signature_check, please set signature_check 'Image,Image_Signature,SignatureOffset'");


HI_S32 CA_Common_VerifyEncryptCommand(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;

    if(argc >= 3)
    {
        CA_ASSERT(HI_CA_CommonVerify_EncryptImage((HI_U8*)argv[1], (HI_U8*)argv[2], 0),ret);
    }
    else
    {
        HI_ERR_CA("Error Input\n");
    }

    return ret;
}

U_BOOT_CMD(ca_common_verify_encryptimage,3,1,CA_Common_VerifyEncryptCommand, \
"Encrypt image for Digital Signature","for example: ca_common_verify_encryptimage Image Image_Signature");


HI_S32 CA_Common_VerifyBootParaDebug(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;

    HI_SIMPLEINFO_CA("g_EnvFlashAddr:0x%x, g_EnvFlashPartionSize:0x%x\n", g_EnvFlashAddr, g_EnvFlashPartionSize);

    ret = HI_CA_CommonVerify_BootPara(g_EnvFlashAddr, g_EnvFlashPartionSize);
    if(HI_FAILURE != ret)
    {
        HI_DEBUG_CA("verify success\n");
    }
    else
    {
        HI_DEBUG_CA("verify failed\n");
    }

    return ret;
}
U_BOOT_CMD(ca_common_verify_bootargs,2,1,CA_Common_VerifyBootParaDebug, \
"ca_common_verify_bootargs ","for example: ca_common_verify_bootargs ");


extern HI_FLASH_TYPE_E CA_get_env_flash_type(HI_VOID);
HI_S32 CA_Common_VerifyBootParaByPartitionDebug(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;
    HI_FLASH_TYPE_E EnvFlashType = CA_get_env_flash_type();

    if(argc == 2)
    {
        CA_ASSERT(CA_flash_GetSize(argv[1], &g_EnvFlashPartionSize), ret);
        CA_ASSERT(CA_flash_GetFlashAddressFromParitonName(EnvFlashType, argv[1], &g_EnvFlashAddr), ret);

        HI_SIMPLEINFO_CA("g_EnvFlashAddr:0x%x, g_EnvFlashPartionSize:0x%x\n", g_EnvFlashAddr, g_EnvFlashPartionSize);

        CA_ASSERT(HI_CA_CommonVerify_BootPara(g_EnvFlashAddr, g_EnvFlashPartionSize), ret);
        HI_DEBUG_CA("verify success\n");
    }
    else
    {
        HI_ERR_CA("Error Input\n");
        HI_ERR_CA("usage: common_verify_bootargs  bootargs_partition_name\n");
        ret = HI_FAILURE;
    }

    return ret;
}
U_BOOT_CMD(ca_common_verify_bootargs_partition,2,1,CA_Common_VerifyBootParaByPartitionDebug, \
"ca_common_verify_bootargs_partition ","for example: ca_common_verify_bootargs_partition  bootargs_partition_name");

#endif /* endif CA_CMD_SIGN_TYPE_COMMON_TEST */

#ifndef HI_ADVCA_TYPE_VERIMATRIX
#define BLPK_SPACE_V300_OFFSET  0x1800
#define BLPK_SPACE_V200_OFFSET  0x800
#define BLPK_PARAM_OFFSET       0x304
#define BLPK_LEN                0x10
#define BOOT_IMG_LEN            0x100000
#define BLOAD_MODE_SEL_ADDR     0x03

static HI_U8 g_BootImg[BOOT_IMG_LEN] = {0};

HI_S32 CA_EncryptBoot_Test(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32                  ret = 0;
    HI_U8                   *pBlpk;
    HI_U8                   *pBootImage;
    HI_U8                   EncryptBlpk[BLPK_LEN];
    HI_U8                   BlpkClear;
    HI_UNF_CIPHER_CTRL_S    CipherCtrl;
    HI_HANDLE               blpkHandle = 0;
    HI_U8                   u8CheckedAreaOffset[4] = {0};
    HI_U8                   u8CheckedAreaLen[4] = {0};
    HI_U32                  u32CheckedAreaOffset = 0;
    HI_U32                  u32CheckedAreaLen = 0;
    HI_U32                  i = 0;
    CA_V300_BLOAD_MODE_U    bloadMode;
    static HI_U32           u32MmzPhyAddr = 0;
    HI_BOOL                 bIsV300 = HI_FALSE;
    HI_U32                  u32BlpkSpaceOffset = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAtts;

    u32BlpkSpaceOffset= BLPK_SPACE_V300_OFFSET;
    bIsV300 = HI_TRUE;

    /* read all valid data of boot partition  */
    CA_ASSERT(CA_flash_read(BOOT_BASIC,0ULL,BOOT_IMG_LEN,(HI_U8*)g_BootImg, HI_NULL),ret);

    /*read the offset and length of the param area*/
    memcpy(u8CheckedAreaOffset, g_BootImg + BLPK_PARAM_OFFSET, 4);
    memcpy(u8CheckedAreaLen, g_BootImg + BLPK_PARAM_OFFSET + 8, 4);

    u32CheckedAreaOffset = u8CheckedAreaOffset[0];
    u32CheckedAreaOffset += u8CheckedAreaOffset[1] << 8;
    u32CheckedAreaOffset += u8CheckedAreaOffset[2] << 16;
    u32CheckedAreaOffset += u8CheckedAreaOffset[3] << 24;

    u32CheckedAreaLen = u8CheckedAreaLen[0];
    u32CheckedAreaLen += u8CheckedAreaLen[1] << 8;
    u32CheckedAreaLen += u8CheckedAreaLen[2] << 16;
    u32CheckedAreaLen += u8CheckedAreaLen[3] << 24;

    HI_SIMPLEINFO_CA("u32CheckedAreaOffset = %x, u32CheckedAreaLen = %x\n", u32CheckedAreaOffset, u32CheckedAreaLen);

    if (0 != (u32CheckedAreaLen % 0x100))
    {
        HI_ERR_CA("checked area length invalid!\n");
        return HI_FAILURE;
    }

    /* read blpk and its clear flag */
    pBlpk = g_BootImg + u32BlpkSpaceOffset;
    pBootImage = g_BootImg + u32BlpkSpaceOffset + u32CheckedAreaOffset;
    BlpkClear = pBlpk[BLPK_LEN];
    if (bIsV300)
    {
        if (0x48 == BlpkClear)
        {
            HI_ERR_CA("blpk is already encrypted\n");
            return HI_SUCCESS;
        }

        HI_SIMPLEINFO_CA("clear key:");
        for (i = 0; i < BLPK_LEN; i++)
        {
            HI_SIMPLEINFO_CA("%02x ", g_customer_blpk[i]);
        }
        HI_SIMPLEINFO_CA("\n");

        ret = HI_UNF_CIPHER_Init();
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("HI_UNF_CIPHER_Init failed:%#x\n",ret);
            return HI_FAILURE;
        }

        memset(&stCipherAtts, 0, sizeof(HI_UNF_CIPHER_ATTS_S));
        stCipherAtts.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
        ret = HI_UNF_CIPHER_CreateHandle(&blpkHandle, &stCipherAtts);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("HI_UNF_CIPHER_CreateHandle failed:%#x\n",ret);
            goto _CIPHER_CLOSE;
        }

        CipherCtrl.bKeyByCA = HI_FALSE;
        CipherCtrl.enAlg = HI_UNF_CIPHER_ALG_AES;
        CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_CBC;
        CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;

        memcpy(CipherCtrl.u32Key, g_customer_blpk, BLPK_LEN);
        memset(CipherCtrl.u32IV, 0, 16);

        ret = HI_UNF_CIPHER_ConfigHandle(blpkHandle, &CipherCtrl);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("HI_UNF_CIPHER_ConfigHandle failed:%#x\n",ret);
            goto _CIPHER_DESTROY;
        }

        /*************************************************************/
        ret = HI_MEM_Alloc(&u32MmzPhyAddr, MAX_DATA_LEN);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_CA("malloc input memory failed!\n");
            goto _CIPHER_DESTROY;
        }
        memset((void *)u32MmzPhyAddr, 0, BOOT_IMG_LEN);

        /*************************************************************/
        memcpy((void *)u32MmzPhyAddr, pBootImage, u32CheckedAreaLen);

        ret = HI_UNF_CIPHER_Encrypt(blpkHandle, u32MmzPhyAddr, u32MmzPhyAddr, u32CheckedAreaLen);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("HI_UNF_CIPHER_Encrypt failed:%#x\n",ret);
            goto _CIPHER_DESTROY;
        }
        memcpy(pBootImage, (HI_U8 *)u32MmzPhyAddr, u32CheckedAreaLen);

        /* encrypt blpk */
        HI_UNF_ADVCA_Init();

        ret = CA_EncryptSwpk(g_customer_blpk,EncryptBlpk);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("CA_EncryptSwpk failed:%#x\n",ret);
            goto _CIPHER_DESTROY;
        }

        HI_SIMPLEINFO_CA("encrypted key:");
        for (i = 0; i < BLPK_LEN; i++)
        {
            HI_SIMPLEINFO_CA("%02x ", EncryptBlpk[i]);
        }
        HI_SIMPLEINFO_CA("\n");

        /* write encrypted blpk and set flag*/
        memcpy(pBlpk,EncryptBlpk,BLPK_LEN);
        pBlpk[BLPK_LEN] = BlpkClear = 0X48;

        /* write all valid data of boot partition  */
        ret = CA_flash_write(BOOT_BASIC,0ULL,BOOT_IMG_LEN,(HI_U8*)g_BootImg);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("CA_flash_write failed:%#x\n",ret);
            goto _CIPHER_DESTROY;
        }

        HI_UNF_OTP_Init();

        /*Set bload mode sel flag*/
        bloadMode.u8 = 0;
        bloadMode.bits.bload_mode_sel = 1;
        ret = HI_OTP_WriteByte(BLOAD_MODE_SEL_ADDR, bloadMode.u8);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("Set bload_mod_sel failed:%#x\n",ret);
            goto _OTP_DEINIT;
        }

        HI_UNF_OTP_DeInit();

        ret = HI_SUCCESS;

_OTP_DEINIT:
        HI_UNF_OTP_DeInit();

_CIPHER_DESTROY:
        HI_UNF_CIPHER_DestroyHandle(blpkHandle);

_CIPHER_CLOSE:
        HI_UNF_CIPHER_DeInit();
    }
    else
    {
        if (0x0 == BlpkClear)
        {
            HI_ERR_CA("blpk is already encrypted\n");
            return HI_SUCCESS;
        }

        HI_SIMPLEINFO_CA("clear key:");
        for (i = 0; i < BLPK_LEN; i++)
        {
            HI_SIMPLEINFO_CA("%02x ", pBlpk[i]);
        }
        HI_SIMPLEINFO_CA("\n");

        /* encrypt blpk */
        HI_UNF_ADVCA_Init();

        ret = CA_EncryptSwpk(pBlpk, EncryptBlpk);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("CA_EncryptSwpk failed:%#x\n",ret);
            goto _END_PROCESS;
        }

        HI_SIMPLEINFO_CA("encrypted key:");
        for (i = 0; i < BLPK_LEN; i++)
        {
            HI_SIMPLEINFO_CA("%02x ", EncryptBlpk[i]);
        }
        HI_SIMPLEINFO_CA("\n");

        /* write encrypted blpk and set flag*/
        memcpy(pBlpk,EncryptBlpk,BLPK_LEN);
        pBlpk[BLPK_LEN] = BlpkClear = 0X0;

        /* write all valid data of boot partition  */
        ret = CA_flash_write(BOOT_BASIC,0ULL,BOOT_IMG_LEN,(HI_U8*)g_BootImg);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("CA_flash_write failed:%#x\n",ret);
            goto _END_PROCESS;
        }

        ret = HI_SUCCESS;
    }

_END_PROCESS:
    if (HI_SUCCESS == ret)
    {
        HI_ERR_CA("ca_encryptboot blpk SUCCESS!\n");
    }
    else
    {
        HI_ERR_CA("ca_encryptboot blpk FAIL!\n");
    }

    return ret;
}
U_BOOT_CMD(ca_encryptboot, 1, 1, CA_EncryptBoot_Test, "CA Encrypt Boot ", "eg: ca_encryptboot");


HI_S32 CA_GetExternRsaKey(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_S32 ret = 0;
    HI_S32 index = 0;
    HI_U8 buffer[512] = {0};
    HI_U8 command[512] = {0};
    HI_CHIP_TYPE_E enChipType;
    HI_CHIP_VERSION_E u32ChipVersion = 0;
    HI_FLASH_TYPE_E EnvFlashType;

    if (argc != 2)
    {
       HI_ERR_CA("Error Input\n");
       HI_ERR_CA("usage: ca_get_extern_rsa_key  fastboot_partition_name\n");
       return HI_FAILURE;
    }

    HI_DRV_SYS_GetChipVersion( &enChipType, &u32ChipVersion );

    EnvFlashType = CA_get_env_flash_type();
    if (EnvFlashType == HI_FLASH_TYPE_SPI_0 || EnvFlashType == HI_FLASH_TYPE_NAND_0)
    {
        CA_ASSERT(CA_flash_read(argv[1], 0ULL, 512, buffer, HI_NULL), ret);
    }
    else if (EnvFlashType == HI_FLASH_TYPE_EMMC_0 || EnvFlashType == HI_FLASH_TYPE_SD)
    {
       memset(command, 0, 256);
#if defined(CHIP_TYPE_hi3719mv100)
       if ((HI_CHIP_TYPE_HI3719M == enChipType) && (HI_CHIP_VERSION_V100 == u32ChipVersion))
       {
           snprintf((char *)command, sizeof(command), "mmc read 0 0x%x 0x0 0x1 ", buffer);
       }
       else
#endif
       {
           snprintf((char *)command, sizeof(command), "mmc read 0 0x%x 0x1 0x1 ", buffer);
       }
       run_command((const char *)command, 0);
    }
    else
    {
        HI_ERR_CA("\nget extern rsa key fail!\n");
        return HI_FAILURE;
    }

    for (; index < 256; index++)
    {
       g_customer_rsa_public_key_N[index] = buffer[index];
    }
    g_customer_rsa_public_key_E = (buffer[508] << 24) + (buffer[509] << 16) + (buffer[510] << 8) + buffer[511];

//z00213260, for test
    printf("RSA Module:\n");
    printf_hex(g_customer_rsa_public_key_N, sizeof(g_customer_rsa_public_key_N));

    printf("RSA Exponent:\n");
    printf_hex((HI_U8 *)&g_customer_rsa_public_key_E, sizeof(g_customer_rsa_public_key_E));

    HI_SIMPLEINFO_CA("\nget extern rsa key success!\n");

    return 0;
}
U_BOOT_CMD(ca_get_extern_rsa_key,2,1,CA_GetExternRsaKey, "get external rsa key","for example: get_extern_rsa_key fastboot");

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
HI_S32 HI_Android_Authenticate(HI_VOID)
{
    HI_S32 ret = 0;
    HI_BOOL CAFlag = HI_FALSE;
    HI_UNF_ADVCA_FLASH_TYPE_E enCAFlashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;
    HI_U32 recoveryAuthMode = COMMON_MODE;
    HI_U32 kernelAuthMode = COMMON_MODE;

    CA_ASSERT(HI_UNF_ADVCA_Init(), ret);
    CA_ASSERT(HI_UNF_ADVCA_GetSecBootStat(&CAFlag, &enCAFlashType), ret);
    if (CAFlag == HI_TRUE)
    {
        ret = run_command("ca_get_extern_rsa_key fastboot", 0);
        if (ret == -1)
        {
            HI_ERR_CA("Get extern rsa key failed!\n");
            return -1;
        }

        ret = run_command("ca_common_verify_bootargs_partition bootargs", 0);
        if (ret == -1)
        {
            HI_ERR_CA("Verify bootargs failed!\n");
            return -1;
        }

        recoveryAuthMode = HI_CA_GetAuthMode("recovery");
        kernelAuthMode = HI_CA_GetAuthMode("kernel");

        if (recoveryAuthMode == SPECIAL_MODE && kernelAuthMode == SPECIAL_MODE)
        {
            ret = run_command("ca_special_verify recovery", 0);
            if (ret == -1)
            {
                HI_ERR_CA("Special verify recovery failed!\n");
                return -1;
            }
            ret = run_command("ca_special_verify kernel", 0);
            if (ret == -1)
            {
                HI_ERR_CA("Special verify kernel failed!\n");
                return -1;
            }
        }
        else if (recoveryAuthMode == COMMON_MODE && kernelAuthMode == COMMON_MODE)
        {
            ret = run_command("ca_common_verify_signature_check", 0);
            if (ret == -1)
            {
                HI_ERR_CA("Common verify recovery or kernel failed!\n");
                return -1;
            }
        }
        else
        {
            HI_ERR_CA("AuthMode Not support!\n");
            return -1;
        }
    }
    else
    {
        HI_SIMPLEINFO_CA("enter write OTP mode!\n");
    }

    return 0;
}
#else
HI_S32 HI_Android_Authenticate(HI_VOID)
{
    HI_S32 ret = 0;
    HI_BOOL CAFlag = HI_FALSE;
    HI_FLASH_TYPE_E EnvFlashType;
	HI_UNF_ADVCA_FLASH_TYPE_E enCAFlashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;	//not used!!

    EnvFlashType = CA_get_env_flash_type();

	CA_ASSERT(HI_UNF_ADVCA_Init(), ret);
	CA_ASSERT(HI_UNF_ADVCA_GetSecBootStat(&CAFlag, &enCAFlashType), ret);	/* parameter enCAFlashType is not used in this case */

    if (CAFlag == HI_TRUE)
    {
        ret = run_command("ca_get_extern_rsa_key fastboot", 0);
        if (ret == -1)
        {
            HI_ERR_CA("Get extern rsa key failed!\n");
            return -1;
        }

        ret = run_command("ca_common_verify_bootargs_partition bootargs", 0);
        if (ret == -1)
        {
            HI_ERR_CA("Verify bootargs failed!\n");
            return -1;
        }

        ret = run_command("ca_common_verify_image_signature recovery", 0);
        if (ret == -1)
        {
            HI_ERR_CA("Verify recovery failed!\n");
            return -1;
        }

        ret = run_command("ca_common_verify_image_signature kernel", 0);
        if (ret == -1)
        {
            HI_ERR_CA("Verify kernel failed!\n");
            return -1;
        }

        if (EnvFlashType == HI_FLASH_TYPE_EMMC_0)
        {
            ret = run_command("ca_common_verify_image_signature systemsign systemsign 0x3E8000", 0);
        }
        else
        {
            HI_U8 CAImageInfo[NAND_PAGE_SIZE] = {0};
            HI_CASignImageTail_S stSignImage = {0};
            CA_ASSERT(CA_flash_read("systemsign", 0UL, NAND_PAGE_SIZE,(HI_U8 *)CAImageInfo, HI_NULL),ret);
            memcpy(&stSignImage, CAImageInfo, sizeof(HI_CASignImageTail_S));
            CA_ASSERT(HI_CA_CommonVerify_Signature("systemsign", "systemsign", stSignImage.u32TotalsectionID * NAND_PAGE_SIZE), ret);
        }

        if (ret == -1)
        {
            HI_ERR_CA("Verify systemsign failed!\n");
            return -1;
        }

        ret = run_command("ca_common_verify_system_signature system systemsign 0x0", 0);
        if (ret == -1)
        {
            HI_ERR_CA("Verify system failed!\n");
            return -1;
        }
    }
    else
    {
        HI_SIMPLEINFO_CA("enter write OTP mode!\n");
    }

    return 0;
}
#endif

U_BOOT_CMD(ca_auth, 2, 1, HI_Android_Authenticate, \
"verify android system: bootargs, recovory, kernel, system...", "for example: ca_auth");


/*************************************************************************
 *
 * The test below is for Irdeto MSR2.2 chipset AES CBC-MAC.
 *
 *************************************************************************/
HI_S32 CA_CbcMacTest(cmd_tbl_t *cmdtp, HI_S32 flag, HI_S32 argc, char *argv[])
{
    HI_U8 u8TestData[16];
    HI_U8 u8CbcMac[16];
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_ADVCA_CA_VENDOR_OPT_S stCaVendorOpt;

    HI_UNF_ADVCA_Init();
    CA_ASSERT(HI_UNF_CIPHER_Init(), Ret);

    HI_SIMPLEINFO_CA("Test case 1: Calculate the AES CBC MAC\n");

    memset(u8TestData, 0xA5, sizeof(u8TestData));
    stCaVendorOpt.enCaVendorOpt = HI_ADVCA_CAVENDOR_ATTR_IRDETO_CBCMAC_CALC;
    stCaVendorOpt.unCaVendorOpt.stIrdetoCbcMac.pu8InputData = u8TestData;
    stCaVendorOpt.unCaVendorOpt.stIrdetoCbcMac.u32InputDataLen = sizeof(u8TestData);
    Ret = HI_UNF_ADVCA_CaVendorOperation(HI_ADVCA_IRDETO, &stCaVendorOpt);
    if(Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Calcualte the AES CBC MAC failed! Ret = 0x%08x\n", Ret);
        return HI_FAILURE;
    }
    memcpy(u8CbcMac, stCaVendorOpt.unCaVendorOpt.stIrdetoCbcMac.u8OutputCbcMac, 16);
    HI_SIMPLEINFO_CA("The AES CBC-MAC is:\n");
    printf_hex(u8CbcMac, 16);

    HI_SIMPLEINFO_CA("Test case 2: Authenticate the AES CBC MAC\n");

    //If the authentication failed, the chipset will reset automatically
    memset(u8TestData, 0xA5, sizeof(u8TestData));
    stCaVendorOpt.enCaVendorOpt = HI_ADVCA_CAVENDOR_ATTR_IRDETO_CBCMAC_AUTH;
    stCaVendorOpt.unCaVendorOpt.stIrdetoCbcMac.pu8InputData = u8TestData;
    stCaVendorOpt.unCaVendorOpt.stIrdetoCbcMac.u32InputDataLen = sizeof(u8TestData);
    stCaVendorOpt.unCaVendorOpt.stIrdetoCbcMac.u32AppLen = sizeof(u8TestData);

    //Use the last AES CBC-MAC for test
    memcpy(stCaVendorOpt.unCaVendorOpt.stIrdetoCbcMac.u8RefCbcMAC, u8CbcMac, 16);
    Ret = HI_UNF_ADVCA_CaVendorOperation(HI_ADVCA_IRDETO, &stCaVendorOpt);
    if(Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Authenticate the AES CBC MAC failed! Ret = 0x%08x\n", Ret);
        return HI_FAILURE;
    }
    HI_SIMPLEINFO_CA("Authenticate the AES CBC MAC successfully\n");

    return HI_SUCCESS;
}
U_BOOT_CMD(ca_cbcmac_test, 2, 1, CA_CbcMacTest, "", "");

HI_S32 OTP_GetChipIDEx(HI_U8 *pu8ChipId, HI_U32 len)
{
    HI_U32 index = 0;

    if(NULL == pu8ChipId || 8 != len)
    {
        HI_ERR_OTP("Invalid parameters when read chipid!\n");
        return HI_FAILURE;
    }

    for(index = 0; index < len; index++)
    {
        pu8ChipId[index] = HAL_OTP_V200_ReadByte(OTP_CHIP_ID_ADDR + index);
    }

    return HI_SUCCESS;
}

HI_S32 OTP_GetChipID_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_U8 au8ChipId[8] = {0};

    HI_UNF_OTP_Init();
    OTP_GetChipIDEx(au8ChipId, 8);

    HI_SIMPLEINFO_CA("Chipid:\n");
    printf_hex(au8ChipId, 8);

    HI_SIMPLEINFO_CA("otp_getchipid success\n");

    return HI_SUCCESS;
}
U_BOOT_CMD(otp_getchipid,2,1,OTP_GetChipID_test,"otp_getchipid ","");

HI_S32 OTP_GetStbSN_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 i = 0;
    HI_U8 u8SN[4];

    memset(u8SN,0,sizeof(u8SN));

	ret = HI_UNF_ADVCA_Init();
    ret |= HI_UNF_ADVCA_GetStbSn(u8SN);
	if(HI_SUCCESS != ret)
	{
		HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetStbSn failed\n");
	    return HI_FAILURE;
	}

    HI_SIMPLEINFO_CA("STBSN = ");
    for(i = 0;i<4;i++)
    {
        HI_SIMPLEINFO_CA("0x%x ",u8SN[i]);
    }
    HI_SIMPLEINFO_CA("\n");
    HI_SIMPLEINFO_CA("otp_getstbsn success\n");
    return HI_SUCCESS;
}
U_BOOT_CMD(otp_getstbsn,2,1,OTP_GetStbSN_test,"otp_getstbsn ","");

HI_S32 OTP_GetMarketID_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_U8 i = 0;
    HI_U8 u8SN[4];

    HI_UNF_OTP_Init();

    memset(u8SN,0,sizeof(u8SN));
    OTP_GetMarketID(u8SN);

    HI_SIMPLEINFO_CA("MarketID = \n");
    for(i = 0;i<4;i++)
    {
        HI_SIMPLEINFO_CA("0x%x ",u8SN[i]);
    }
    HI_SIMPLEINFO_CA("\n");
    HI_SIMPLEINFO_CA("otp_getmsid success\n");
    return HI_SUCCESS;
}
U_BOOT_CMD(otp_getmsid,2,1,OTP_GetMarketID_test,"otp_getmsid ","for example: getMarketID");


HI_S32 OTP_GetSecureBootEn_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bSecBootEn = HI_FALSE;
	HI_UNF_ADVCA_FLASH_TYPE_E enFlashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;

	s32Ret = HI_UNF_ADVCA_Init();
    s32Ret |= HI_UNF_ADVCA_GetSecBootStat(&bSecBootEn, &enFlashType);
    if(HI_SUCCESS != s32Ret)
    {
        HI_SIMPLEINFO_CA("Get Secure boot en failed!\n");
        return HI_FAILURE;
    }

    HI_SIMPLEINFO_CA("SecBootEn = %d\n", bSecBootEn);
    HI_SIMPLEINFO_CA("otp_getsecurebooten success\n");

    return HI_SUCCESS;
}
U_BOOT_CMD(otp_getsecurebooten,2,1,OTP_GetSecureBootEn_test,"otp_getsecurebooten ","");

HI_S32 CA_GetSecBootStat_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_BOOL bEnable = HI_FALSE;
    HI_UNF_ADVCA_FLASH_TYPE_E enFlashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;

    ret = HI_UNF_ADVCA_Init();
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_Init failed!\n");
        return HI_FAILURE;
    }

    ret = HI_UNF_ADVCA_GetSecBootStat(&bEnable, &enFlashType);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetSecBootStat failed!\n");
        return HI_FAILURE;
    }

    if(HI_TRUE == bEnable)
    {
        HI_SIMPLEINFO_CA("Secure boot is enabled\n");
    }
    else
    {
        HI_SIMPLEINFO_CA("Secure boot is not enabled\n");
        return HI_SUCCESS;
    }

    switch(enFlashType)
    {
        case HI_UNF_ADVCA_FLASH_TYPE_SPI:
        {
            HI_SIMPLEINFO_CA("Secure boot from SPI flash(enFlashType:%d).\n", enFlashType);
            break;
        }
        case HI_UNF_ADVCA_FLASH_TYPE_NAND:
        {
            HI_SIMPLEINFO_CA("Secure boot from NAND flash(enFlashType:%d).\n", enFlashType);
            break;
        }
        case HI_UNF_ADVCA_FLASH_TYPE_NOR:
        {
            HI_SIMPLEINFO_CA("Secure boot from NOR flash(enFlashType:%d).\n", enFlashType);
            break;
        }
        case HI_UNF_ADVCA_FLASH_TYPE_EMMC:
        {
            HI_SIMPLEINFO_CA("Secure boot from EMMC flash(enFlashType:%d).\n", enFlashType);
            break;
        }
        case HI_UNF_ADVCA_FLASH_TYPE_SPI_NAND:
        {
            HI_SIMPLEINFO_CA("Secure boot from SPI_NAND flash(enFlashType:%d).\n", enFlashType);
            break;
        }
        case HI_UNF_ADVCA_FLASH_TYPE_SD:
        {
            HI_SIMPLEINFO_CA("Secure boot from SD flash(enFlashType:%d).\n", enFlashType);
            break;
        }
        default:
        {
            HI_SIMPLEINFO_CA("Invalid enFlashType:%d.\n", enFlashType);
            break;
        }
    }

    return HI_SUCCESS;
}
U_BOOT_CMD(ca_getsecbootstatus,2,1,CA_GetSecBootStat_test,"ca_getsecbootstatus ","");

HI_S32 CA_EnableSecBoot_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_ADVCA_FLASH_TYPE_E enFlashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;

    if(2 != argc)
    {
        HI_SIMPLEINFO_CA("Invalid argument, argc:%d!\n", argc);
        return HI_FAILURE;
    }

    ret = HI_UNF_ADVCA_Init();
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_Init failed!\n");
        return HI_FAILURE;
    }

    if(0 == strcmp(argv[1], "spi"))
    {
        HI_SIMPLEINFO_CA("Flash type: spi(%s)\n", argv[1]);
        enFlashType = HI_UNF_ADVCA_FLASH_TYPE_SPI;
    }
    else if(0 == strcmp(argv[1], "nand"))
    {
        HI_SIMPLEINFO_CA("Flash type: nand(%s)\n", argv[1]);
        enFlashType = HI_UNF_ADVCA_FLASH_TYPE_NAND;
    }
    else if(0 == strcmp(argv[1], "nor"))
    {
        HI_SIMPLEINFO_CA("Flash type: nor(%s)\n", argv[1]);
        enFlashType = HI_UNF_ADVCA_FLASH_TYPE_NOR;
    }
    else if(0 == strcmp(argv[1], "emmc"))
    {
        HI_SIMPLEINFO_CA("Flash type: emmc(%s)\n", argv[1]);
        enFlashType = HI_UNF_ADVCA_FLASH_TYPE_EMMC;
    }
    else if(0 == strcmp(argv[1], "sd"))
    {
        HI_SIMPLEINFO_CA("Flash type: sd(%s)\n", argv[1]);
        enFlashType = HI_UNF_ADVCA_FLASH_TYPE_SD;
    }
    else if(0 == strcmp(argv[1], "spi_nand"))
    {
        HI_SIMPLEINFO_CA("Flash type: spi_nand(%s)\n", argv[1]);
        enFlashType = HI_UNF_ADVCA_FLASH_TYPE_SPI_NAND;
    }
    else
    {
        HI_SIMPLEINFO_CA("Invalid flash type: %s\n", argv[1]);
        return HI_FAILURE;
    }

    ret = HI_UNF_ADVCA_EnableSecBoot(enFlashType);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_EnableSecBoot failed!\n");
        return HI_FAILURE;
    }

    HI_SIMPLEINFO_CA("Enable secure boot success!\n");

    return HI_SUCCESS;
}
U_BOOT_CMD(ca_enablesecboot,2,1,CA_EnableSecBoot_test,"ca_enablesecboot flash_type(spi|nand|sd|emmc)","");

static HI_VOID printbuffer(HI_CHAR *str, HI_U8 *pu8Buf, HI_U32 u32Length)
{
    HI_U32 i = 0;

    if(NULL != str)
    {
        printf("%s\n", str);
    }

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

HI_S32 CA_SetRSAKey_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_ADVCA_OTP_ATTR_S stOtpFuseAttr;
    /* This rsa key is only for test */
    HI_U8 au8Key[512] =
    {
        0xa3, 0x1f, 0x12, 0xf8, 0xa6, 0xbf, 0xb5, 0x19, 0xad, 0xa3, 0xef, 0x18, 0x68, 0x37, 0x2b, 0xd1,
        0xa5, 0x7d, 0x1c, 0x2f, 0x83, 0x88, 0x56, 0xe5, 0xfb, 0xe6, 0xa0, 0xac, 0xa4, 0xd7, 0xb9, 0xd8,
        0xb7, 0xca, 0x37, 0x5a, 0xda, 0xd7, 0x6d, 0xb7, 0x76, 0x59, 0x96, 0x44, 0x9f, 0x79, 0xab, 0xd8,
        0x18, 0xe2, 0x00, 0xb7, 0x67, 0xa0, 0x0f, 0x59, 0x9b, 0x9f, 0x8b, 0xb0, 0x5d, 0x6f, 0x9f, 0xa6,
        0x74, 0xe0, 0xfd, 0x14, 0x4d, 0xae, 0x23, 0x9b, 0x5d, 0x18, 0x7f, 0x37, 0x82, 0x03, 0x44, 0xac,
        0xca, 0x6d, 0x88, 0xc3, 0x2c, 0x5b, 0x47, 0x8c, 0xb5, 0x07, 0x6b, 0x9c, 0xd7, 0x6b, 0x64, 0x1e,
        0x82, 0x6e, 0xb8, 0x7e, 0xd0, 0xc2, 0xf4, 0x26, 0x17, 0xe1, 0xdc, 0x2f, 0x81, 0x3b, 0xa6, 0x9e,
        0x1f, 0xbe, 0xc6, 0x89, 0xc4, 0x1d, 0xa3, 0xe1, 0x2f, 0x88, 0x5f, 0x53, 0xd8, 0xae, 0xe6, 0xef,
        0xb2, 0x5c, 0x6a, 0xba, 0xba, 0xfd, 0x29, 0xfe, 0x99, 0x1a, 0x89, 0x73, 0xf7, 0xc0, 0x6e, 0xb7,
        0x13, 0x58, 0xc8, 0x9a, 0x29, 0x17, 0xba, 0xf2, 0x6c, 0xd7, 0x16, 0xc4, 0x9e, 0x3b, 0xe8, 0x90,
        0x72, 0x40, 0xa6, 0x4f, 0xee, 0x45, 0x9d, 0xe9, 0xae, 0xa0, 0x41, 0xfc, 0xc6, 0x01, 0x9b, 0x26,
        0x38, 0xf6, 0x5d, 0x11, 0xa1, 0x18, 0x54, 0x2d, 0x15, 0x60, 0x7a, 0xac, 0xc7, 0x7a, 0x18, 0x1d,
        0xeb, 0xcf, 0x15, 0x4c, 0xdd, 0x88, 0xa4, 0x41, 0xbe, 0x6b, 0x1a, 0x5a, 0x4f, 0xf7, 0x8e, 0xbe,
        0x5b, 0xc9, 0x6a, 0x2f, 0x6a, 0x74, 0xb0, 0xfc, 0x8b, 0xe8, 0xae, 0x68, 0xd7, 0x86, 0xad, 0x60,
        0x5b, 0xf0, 0x8a, 0x2c, 0xe1, 0xb2, 0xf9, 0x3f, 0x35, 0x5d, 0xa3, 0xd6, 0x5e, 0xfd, 0x12, 0xb6,
        0x21, 0xca, 0x72, 0xa9, 0xba, 0xf2, 0x97, 0xbc, 0x2d, 0x79, 0xba, 0xd6, 0x48, 0x53, 0x97, 0x5d,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01
    };

    ret = HI_UNF_ADVCA_Init();
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_Init failed!\n");
        return HI_FAILURE;
    }

    memset(&stOtpFuseAttr, 0, sizeof(HI_UNF_ADVCA_OTP_ATTR_S));
    stOtpFuseAttr.unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked = HI_FALSE;
    ret = HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_RSA_KEY_LOCK_FLAG, &stOtpFuseAttr);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetSecBootStat failed!\n");
        return HI_FAILURE;
    }

    if(HI_TRUE == stOtpFuseAttr.unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked)
    {
        HI_SIMPLEINFO_CA("Failed, rsa key has already been locked before!\n");
        return HI_FAILURE;
    }

    ret = HI_UNF_ADVCA_SetRSAKey(au8Key);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetSecBootStat failed!\n");
        return HI_FAILURE;
    }

    memset(au8Key, 0, sizeof(au8Key));
    ret = HI_UNF_ADVCA_GetRSAKey(au8Key);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetSecBootStat failed!\n");
        return HI_FAILURE;
    }

    printbuffer("set rsa key success:", au8Key, sizeof(au8Key));

    return HI_SUCCESS;
}
U_BOOT_CMD(ca_setotprsakey,2,1,CA_SetRSAKey_test,"ca_setotprsakey ","");

HI_S32 CA_GetRSAKey_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_ADVCA_OTP_ATTR_S stOtpFuseAttr;
    HI_U8 au8Key[512] = {0};

    ret = HI_UNF_ADVCA_Init();
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_Init failed!\n");
        return HI_FAILURE;
    }

    memset(&stOtpFuseAttr, 0, sizeof(HI_UNF_ADVCA_OTP_ATTR_S));
    stOtpFuseAttr.unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked = HI_FALSE;
    ret = HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_RSA_KEY_LOCK_FLAG, &stOtpFuseAttr);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetSecBootStat failed!\n");
        return HI_FAILURE;
    }

    if(HI_TRUE == stOtpFuseAttr.unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked)
    {
        HI_SIMPLEINFO_CA("Failed, rsa key can not be read out, it has already been locked before!\n");
        return HI_FAILURE;
    }

    memset(au8Key, 0, sizeof(au8Key));
    ret = HI_UNF_ADVCA_GetRSAKey(au8Key);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetRSAKey failed! ret:0x%x\n", ret);
        return HI_FAILURE;
    }

    printbuffer("rsa key:", au8Key, sizeof(au8Key));

    return HI_SUCCESS;
}
U_BOOT_CMD(ca_getotprsakey,2,1,CA_GetRSAKey_test,"ca_getotprsakey ","");

HI_S32 CA_GetRSAKeyLockFlag_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_ADVCA_OTP_ATTR_S stOtpFuseAttr;

    ret = HI_UNF_ADVCA_Init();
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_Init failed!\n");
        return HI_FAILURE;
    }

    memset(&stOtpFuseAttr, 0, sizeof(HI_UNF_ADVCA_OTP_ATTR_S));
    stOtpFuseAttr.unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked = HI_FALSE;
    ret = HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_RSA_KEY_LOCK_FLAG, &stOtpFuseAttr);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetOtpFuse failed!\n");
        return HI_FAILURE;
    }

    HI_SIMPLEINFO_CA("get rsa key lock flag: %d\n", stOtpFuseAttr.unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked);

    return HI_SUCCESS;
}
U_BOOT_CMD(ca_getrsakeylockflag,2,1,CA_GetRSAKeyLockFlag_test,"ca_getrsakeylockflag ","");

HI_S32 CA_LockRSAKey_test(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    HI_UNF_ADVCA_OTP_ATTR_S stOtpFuseAttr;
    HI_U8 au8Key[512] = {0};

    ret = HI_UNF_ADVCA_Init();
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_Init failed!\n");
        return HI_FAILURE;
    }

    memset(&stOtpFuseAttr, 0, sizeof(HI_UNF_ADVCA_OTP_ATTR_S));
    stOtpFuseAttr.unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked = HI_FALSE;
    ret = HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_RSA_KEY_LOCK_FLAG, &stOtpFuseAttr);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetOtpFuse failed!\n");
        return HI_FAILURE;
    }

    if(HI_TRUE == stOtpFuseAttr.unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked)
    {
        HI_SIMPLEINFO_CA("Failed, rsa key can not be locked anymore, it has already been locked before!\n");
        return HI_FAILURE;
    }

    memset(&stOtpFuseAttr, 0, sizeof(HI_UNF_ADVCA_OTP_ATTR_S));
    stOtpFuseAttr.unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked = HI_TRUE;
    ret = HI_UNF_ADVCA_SetOtpFuse(HI_UNF_ADVCA_OTP_RSA_KEY_LOCK_FLAG, &stOtpFuseAttr);
    if(HI_SUCCESS != ret)
    {
        HI_SIMPLEINFO_CA("HI_UNF_ADVCA_GetOtpFuse failed!\n");
        return HI_FAILURE;
    }

    HI_SIMPLEINFO_CA("lock rsa key success!\n");

    return HI_SUCCESS;
}
U_BOOT_CMD(ca_lockrsakey,2,1,CA_LockRSAKey_test,"ca_lockrsakey ","");
#endif

#endif /* #ifndef HI_MINIBOOT_SUPPORT */

#endif /* #ifndef HI_ADVCA_FUNCTION_RELEASE */

