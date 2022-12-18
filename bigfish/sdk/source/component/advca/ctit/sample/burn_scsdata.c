#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include "hi_type.h"
#include "hi_unf_advca.h"
#include "hi_unf_ecs.h"
#include "hi_flash.h"

//#define DEBUG

#define HI_PRINT_INFO(format, arg...)       printf(format, ##arg)
#define HI_PRINT_ERR(format, arg...)        printf("%s,%d: " format, __FUNCTION__, __LINE__, ##arg)      
#define HI_CA_LOG_INFO(fmt...)              __android_log_print(ANDROID_LOG_INFO, "HI_CTIT", fmt)
#define HI_CA_LOG_ERR(fmt...)               __android_log_print(ANDROID_LOG_ERROR, "HI_CTIT", fmt)

/*
除了运营商标示为4个字节的字符，其他的数据都必须为2个字节拼凑成一个unsigned char的数据，
因此，大小为实际大小* 2
*/
#define ROOT_RSA_KEY_OFFSET     0
#define ROOT_RSA_KEY_SIZE       512

#define ROOT_RSA_KEY_E_OFFSET   (ROOT_RSA_KEY_OFFSET + ROOT_RSA_KEY_SIZE)
#define ROOT_RSA_KEY_E_SIZE     6

#define BL_ROOT_KEY_OFFSET      (ROOT_RSA_KEY_E_OFFSET + ROOT_RSA_KEY_E_SIZE)
#define BL_ROOT_KEY_SIZE        32

#define KEY_PARTITION_AES_CBC_KEY_OFFSET    (BL_ROOT_KEY_OFFSET + BL_ROOT_KEY_SIZE)
#define KEY_PARTITION_AES_CBC_KEY_SIZE      32

#define EXTERNAL_RSA_PUBLIC_KEY_OFFSET      (KEY_PARTITION_AES_CBC_KEY_OFFSET + KEY_PARTITION_AES_CBC_KEY_SIZE)
#define EXTERNAL_RSA_PUBLIC_KEY_SIZE        512

#define EXTERNAL_RSA_PUBLIC_KEY_E_OFFSET    (EXTERNAL_RSA_PUBLIC_KEY_OFFSET + EXTERNAL_RSA_PUBLIC_KEY_SIZE)
#define EXTERNAL_RSA_PUBLIC_KEY_E_SIZE      6

static HI_U8 g_RSA_E[] = {0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,    
                          0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x01 , 0x00 , 0x01
                    };

HI_U32 Convert2Hex(HI_U8 *pDataBuf)
{
    HI_U8 u8TmpBuf[16];
    HI_U32 u32Value;

    memset(u8TmpBuf, 0, sizeof(u8TmpBuf));
    u8TmpBuf[0] = pDataBuf[0];
    u8TmpBuf[1] = pDataBuf[1];
    u32Value = strtoul((const char *)u8TmpBuf, 0, 16);

    return u32Value;
}

HI_S32 HI_ADVCA_SetSCSData(HI_CHAR s8Data[], HI_U32 u32DataLength)
{
    HI_U8 FlashType;
    HI_HANDLE flashhandle = HI_INVALID_HANDLE;
    HI_S32 Ret = HI_SUCCESS;
    HI_U8 CAFlag[4] = {0x12, 0x34, 0x56, 0x78};
    HI_U8 PlainSwpk[16];   
    HI_U8 EncryptedSwpk[16];
    HI_U8 u8DataBuf[512];
    HI_U32 i = 0;
    HI_Flash_InterInfo_S pFlashInfo;

    if (s8Data == NULL || u32DataLength != 1132)
    {
        HI_PRINT_ERR("Invalid parameter!\n");
        HI_CA_LOG_ERR("Invalid parameter!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = HI_UNF_ADVCA_Init();
    if (HI_SUCCESS != Ret)
    {
        HI_PRINT_ERR("HI_UNF_ADVCA_Init failed\n");
        HI_CA_LOG_ERR("HI_UNF_ADVCA_Init failed\n");
        return HI_ERR_CA_OPEN_ERR;
    }

    Ret = HI_UNF_OTP_Open();
    if (Ret != HI_SUCCESS)
    {
        HI_PRINT_ERR("Open OTP failed!\n");
        HI_CA_LOG_ERR("Open OTP failed!\n");
        HI_UNF_ADVCA_DeInit();
        return HI_FAILURE;
    }

    //Root RSA Public Key    
    memset(u8DataBuf, 0, sizeof(u8DataBuf));
    for (i = 0; i < ROOT_RSA_KEY_SIZE / 2; i++)
    {
        u8DataBuf[i] = Convert2Hex((HI_U8 *)(s8Data + ROOT_RSA_KEY_OFFSET + i * 2));        
    }
    memcpy(u8DataBuf + 256, g_RSA_E, sizeof(g_RSA_E));
#ifndef DEBUG
    Ret = HI_UNF_ADVCA_SetRSAKey(u8DataBuf);
    if(Ret != HI_SUCCESS)
    {
        HI_PRINT_ERR("Burn RSA key failed!\n");
        HI_CA_LOG_ERR("Burn RSA key failed!\n");
        goto ERR1;
    }
#endif
    HI_PRINT_INFO("Root RSA key:\n");
    HI_CA_LOG_INFO("Root RSA key:\n");
    for(i = 0; i < 256; i++)
    {
        if(i != 0 && i % 16 == 0)   HI_PRINT_ERR("\n");
        HI_PRINT_INFO("0x%02x,", u8DataBuf[i]);
        HI_CA_LOG_INFO("0x%02x,", u8DataBuf[i]);
    }
    HI_PRINT_INFO("\n");

#ifndef DEBUG
    //第一次安全启动0x12345678
    Ret = HI_UNF_OTP_SetStbPrivData(12, 0x12);
    Ret |= HI_UNF_OTP_SetStbPrivData(13, 0x34);
    Ret |= HI_UNF_OTP_SetStbPrivData(14, 0x56);
    Ret |= HI_UNF_OTP_SetStbPrivData(15, 0x78);
    if(Ret != HI_SUCCESS)
    {
        HI_PRINT_ERR("Burn first start up flag failed!\n");
        HI_CA_LOG_ERR("Burn first start up flag failed!\n");
        goto ERR1;
    }
    HI_CA_LOG_INFO("set android start up flag");

    //安全启动校验标志
    flashhandle = HI_Flash_OpenByName("fastboot");
    if (((HI_HANDLE)INVALID_FD == flashhandle) || (HI_INVALID_HANDLE == flashhandle))
    {
        HI_PRINT_ERR("HI_Flash_Open error\n");  
        HI_CA_LOG_ERR("HI_Flash_Open error\n"); 
        return HI_FAILURE;
    }

    HI_Flash_GetInfo(flashhandle, &pFlashInfo);
    FlashType = pFlashInfo.FlashType; 
    switch (FlashType) 
    {
        case HI_FLASH_TYPE_NAND_0:
            Ret = HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_NAND);
            break;    
        case HI_FLASH_TYPE_SPI_0:
            Ret = HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_SPI);
            break;
        case HI_FLASH_TYPE_EMMC_0:
            Ret = HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_EMMC);
            break;
        default:            
            Ret = HI_FAILURE;
            break;
    }
    HI_Flash_Close(flashhandle);
    if(Ret != HI_SUCCESS)
    {
        HI_PRINT_ERR("Burn secure boot check flag failed!\n");
        HI_CA_LOG_ERR("Burn secure boot check flag failed!\n");
        goto ERR1;
    }
    HI_CA_LOG_INFO("set secure boot check flag");

    Ret = HI_UNF_ADVCA_ConfigLockFlag(HI_UNF_ADVCA_LOCK_RSA_KEY, HI_NULL, 0);
    if (Ret != HI_SUCCESS)
    {
        HI_PRINT_ERR("Burn SR register 2,4,6 failed!\n");
        HI_CA_LOG_ERR("Burn SR register 2,4,6 failed!\n");
    }
    HI_CA_LOG_INFO("set SR register 2,4,6");
#endif
ERR1:
    HI_UNF_OTP_Close();
    HI_UNF_ADVCA_DeInit();
    if (Ret == HI_SUCCESS)
    {
        HI_PRINT_ERR("write SCS data success!\n");
        HI_CA_LOG_ERR("write SCS data success!\n");
    }
    else
    {
        HI_PRINT_ERR("write SCS data failed!\n");
        HI_CA_LOG_ERR("write SCS data failed!\n");      
    }

    return Ret;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 ret = HI_SUCCESS;
    //SCS_DATA为芯片安全启动数据，正式生产用的数据必须由运营商提供，
    //此处仅供调试参考.
    HI_CHAR SCS_DATA[] = "a31f12f8a6bfb519ada3ef1868372bd1a57d1c2f838856e5fbe6a0aca4d7b9d8b7ca375adad76db7765996449f79abd818e200b767a00f599b9f8bb05d6f9fa674e0fd144dae239b5d187f37820344acca6d88c32c5b478cb5076b9cd76b641e826eb87ed0c2f42617e1dc2f813ba69e1fbec689c41da3e12f885f53d8aee6efb25c6ababafd29fe991a8973f7c06eb71358c89a2917baf26cd716c49e3be8907240a64fee459de9aea041fcc6019b2638f65d11a118542d15607aacc77a181debcf154cdd88a441be6b1a5a4ff78ebe5bc96a2f6a74b0fc8be8ae68d786ad605bf08a2ce1b2f93f355da3d65efd12b621ca72a9baf297bc2d79bad64853975d010001c74df8700fd09e33eb0db8b5330b7e6175ae974f3de68215932636e0c61805c3d40176599dabd2856819a5c270511a2f1d3444a73da772f978ecffa69066293839e4893010174eb337de3b8a354b433852557ca611bd22c36330aa22d41bca4bf1d29847c4a77feb4fbcbcc217380b27fc03dbc9760f9afa692dc24506bb54d0abd7eb3223748946df36e916cc439ffc712118f891feab06f78ba2dd056b6b7126452d23eec19fcb471657e5e5e9861e23e11c85f88c5f6a0e8e63b24814cb2db007b862258f5250c25326883cc87bfbc79b2d806e86709eedf7486626a68fef9daebf1f115b0556f0c0a2a40135ea95d087fe3b6c4378e8b63461025fed0fec85ba64901617c323529dc294b50a859cd3a9ad75bbd24f22a25c441f6f0b209f000003688fc64e9abd33638aa6904539d48ef2";

    ret = HI_ADVCA_SetSCSData(SCS_DATA, strlen(SCS_DATA)); 
    if (ret == HI_SUCCESS)
    {
        HI_PRINT_INFO("OK!!!!!");
    }
    else 
    {
        HI_PRINT_ERR("no OK!!!!!");
        return 0;
    }

    return 0;
}
