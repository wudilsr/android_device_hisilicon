#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "hi_unf_advca.h"
#include "hi_unf_ecs.h"
#include "hi_flash.h"

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

static char scsdata[1140] ={0};
static char sn[40] ={0};
static char insn[40] ={0};
static char chipID[40] ={0};
static char timex[40] ={0};
static char randomx[40] ={0};
static char aes[40] ={0};
static unsigned char hash[40] ={0};

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

HI_S32 burn_secure_data(HI_U8 *s8Data)
{
   	HI_HANDLE flashhandle = HI_INVALID_HANDLE;
    HI_S32 Ret = HI_SUCCESS;
    HI_U8 PlainSwpk[16];   
    HI_U8 EncryptedSwpk[16];
    HI_U8 u8DataBuf[512];
	HI_U32 i = 0;
    HI_U8 FlashType;
    HI_Flash_InterInfo_S pFlashInfo;

	if (s8Data == NULL)
	{
		printf("Invalid parameter!\n");
		return HI_ERR_CA_INVALID_PARA;
	}
	
	Ret = HI_UNF_ADVCA_Init();
	if (HI_SUCCESS != Ret)
	{
		printf("HI_UNF_ADVCA_Init failed\n");
		return HI_ERR_CA_OPEN_ERR;
	}
	
	Ret = HI_UNF_OTP_Open();
	if (Ret != HI_SUCCESS)
	{
		printf("Open OTP failed!\n");
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
	Ret = HI_UNF_ADVCA_SetRSAKey(u8DataBuf);
	if(Ret != HI_SUCCESS)
	{
		printf("Burn RSA key failed!\n");
		goto ERR1;
	}

	printf("Root RSA key:\n");
	for(i = 0; i < 256; i++)
	{
		if(i != 0 && i % 16 == 0) 	printf("\n");
		printf("0x%02x,", u8DataBuf[i]);
	}
	printf("\n");

	//第一次安全启动0x12345678
	Ret = HI_UNF_OTP_SetStbPrivData(12, 0x12);
	Ret |= HI_UNF_OTP_SetStbPrivData(13, 0x34);
	Ret |= HI_UNF_OTP_SetStbPrivData(14, 0x56);
	Ret |= HI_UNF_OTP_SetStbPrivData(15, 0x78);
	if(Ret != HI_SUCCESS)
	{
		printf("Burn first start up flag failed!\n");
		goto ERR1;
	}
	printf("set android start up flag");
	//安全启动校验标志
    flashhandle = HI_Flash_OpenByName("fastboot");
    if (((HI_HANDLE)INVALID_FD == flashhandle) || (HI_INVALID_HANDLE == flashhandle))
    {
        printf("HI_Flash_Open error\n");
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
		printf("Burn secure boot check flag failed!\n");
		goto ERR1;
	}

    Ret = HI_UNF_ADVCA_ConfigLockFlag(HI_UNF_ADVCA_LOCK_RSA_KEY, HI_NULL, 0);
	if (Ret != HI_SUCCESS)
	{
		printf("Lock RSA Key failed!\n");
	}
	printf("Lock RSA Key\n");

ERR1:
    HI_UNF_OTP_Close();
    HI_UNF_ADVCA_DeInit();
    if (Ret == HI_SUCCESS)
    {
    	printf("write SCS data success!\n");
    }
    else
    {
    	printf("write SCS data failed!\n");		
    }

    return Ret;
}


extern int parse_file(unsigned char *pbuf, unsigned char *aes, unsigned char *sn, unsigned char *in, unsigned char *hash);
extern int verify_file(unsigned char *chipID, unsigned char *time, unsigned char *random, unsigned char *sn, unsigned char *in, unsigned char *hash);

HI_S32 main(HI_S32 argc, HI_CHAR** argv)
{
    HI_S32 Ret = HI_SUCCESS;
    FILE *fp = NULL;
    HI_U32 u32ReadLen = 0;
    HI_U32 u32TmpValue;
    HI_U8 u8TmpBuf[256];
    HI_U8 tmpbuf[512];
    HI_U8 pbuf[200];

    if (argc != 2)
    {
        printf("Error: please input the file name!\n");
        return HI_FAILURE;
    }

    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("Open key for verify file failed\n");
        return HI_FAILURE;
    }

	fgets(scsdata, 1140, fp);
	fgets((char *)tmpbuf, 512, fp);
	fgets((char *)tmpbuf, 512, fp);
	fgets((char *)tmpbuf, 512, fp);
	fgets(chipID, 40, fp);
	fgets(timex, 40, fp);
	fgets(randomx, 40, fp);
	fgets(aes, 40, fp);
	fgets((char *)pbuf, 200, fp);

	//此处是解析key文件。这个步骤是必须的，解析正确后才会写otp。
	if(parse_file(pbuf, (unsigned char *)aes, (unsigned char *)sn, (unsigned char *)insn, hash))
	{
		printf("parse file failed!\n");
		return -1;		
	}
	if(verify_file((unsigned char *)chipID, (unsigned char *)timex, (unsigned char *)randomx, (unsigned char *)sn, (unsigned char *)insn, hash))
	{
		printf("verify file failed!\n");
		return -1;		
	}		

    Ret = burn_secure_data((HI_U8 *)scsdata);
    if (Ret == HI_SUCCESS)
    {
        printf("OK!!!!!");
    }
    else 
    {
        printf("no OK!!!!!");
    }
    
    if(fp != NULL)
    {
        fclose(fp);
    }
    return Ret;
}


