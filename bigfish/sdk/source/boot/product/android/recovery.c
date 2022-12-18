#ifdef HI_MINIBOOT_SUPPORT
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <flash.h>
#include <malloc.h>
#include <run.h>
#else
#include <uboot.h>
#include <linux/string.h>
#include <malloc.h>
#include <spiflash_logif.h>
#include <nand_logif.h>
#include <emmc_logif.h>
#include <asm/io.h>
#include <asm/sizes.h>
#include <asm/arch/platform.h>
#include <net.h>
#include <linux/mtd/mtd.h>
#endif

#include "hi_type.h"
#include "hi_flash.h"
#include "recovery.h"
/* #include "hi_keyled.h" */

#ifdef HI_REMOTE_RECOVERY
#include "hi_unf_ir.h"
#define REMOTE_BTN_RECOVER 0x639cff00
int gpio_recovery = 0 ;
#endif


#define KEY_PRESS             (0x0)	/* press */
#define KEY_HOLD              (0x01)	/* hold */
#define KEY_RELEASE           (0x02)	/* release */

#define FASTBOOT_RECOVERY_NAME "recovery"
#define FASTBOOT_RECOVERY_OFFSET 0

#define FASTBOOT_MISC_NAME "misc"
#define FASTBOOT_MISC_OFFSET 0

#define KERNEL_LOAD_ADDR 0x1000000

#define REG_VAL(RegAddr) (*((volatile HI_U32 *)(RegAddr)))
/* #define HI_OTTGPIO_SUPPORT */
static int check_gpio_recovery(void)
{
	int t;
	int count = 2;
	long long chipid;
	chipid = get_chipid();
	printf("get chipid =%llx\n", chipid);
	switch (chipid) {
	case _HI3716C_V200:
		printf("get chipType (HI3716C_V200)\n");
#ifdef HI_OTTGPIO_SUPPORT
		/* get gpio5_1 buttom */
		while ((((REG_VAL(0xF80043FC) & 0x02) >> 1) == 0)
		       && (count > 0)) {
			udelay(1000 * 1000);
			count--;
		}
#endif
		break;
#if defined(CHIP_TYPE_hi3798cv100) || defined(CHIP_TYPE_hi3798cv100_a)
	case _HI3798CV100:
	case _HI3798CV100A:
		printf("get chipType (HI3798C_V100)\n");
		/* get GPIO_STB1 buttom */
		REG_VAL(0xF8008038) = 0x1;
		while (((REG_VAL(0xF80093FC) & 0x1) == 0) && (count > 0)) {
			udelay(1000 * 1000);
			count--;
		}
		break;
#endif
        case _HI3798M_V100:
        case _HI3798M_V100_A:
            printf("get chipType (HI3798MV100)\n");
            /* get gpio2_0 buttom */
            /* fix    0xF8A21064 [2:0] = 101 */
            /* input: 0xF8B22400 [0] = 0*/
            /* read : 0xF8B22004 [0] = 1: release , 0 :button*/
            while(((REG_VAL(0xF8B22004)) == 0) && (count > 0)){
                udelay(1000*1000);
                count--;
            }
            break;
    }
    printf("count=%x\n",count);
	if (count > 0)
		return HI_FAILURE;
	else
		return HI_SUCCESS;
}
static int check_buttom_recovery(HI_S32 *keyvalue)
{

	HI_S32 Ret = -1;
	HI_U32 u32PressStatus = KEY_RELEASE;
	HI_U32 u32KeyValue = 0;
	HI_S32 s32Cnt = 0;

	Ret = HI_UNF_KEYLED_Init();
	if (HI_SUCCESS != Ret) {
		printf("init failed\n");
		return Ret;
	}

	Ret = HI_UNF_KEYLED_SelectType(0);

	Ret |= HI_UNF_LED_Open();
	if (HI_SUCCESS != Ret) {
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_Open();
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_IsKeyUp(0);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_IsRepKey(0);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_SetBlockTime(200);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEYLED_Init();
	if (HI_SUCCESS != Ret) {
		printf("init failed\n");
		return Ret;
	}

	Ret = HI_UNF_KEYLED_SelectType(0);

	Ret |= HI_UNF_LED_Open();
	if (HI_SUCCESS != Ret) {
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_Open();
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_IsKeyUp(0);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_KEY_IsRepKey(0);
	if (HI_SUCCESS != Ret) {
		HI_UNF_LED_Close();
		HI_UNF_KEY_Close();
		HI_UNF_KEYLED_DeInit();
		return HI_FAILURE;
	}

	Ret = HI_UNF_LED_Display(0xffffffff);
	if (HI_SUCCESS != Ret) {
		printf("display failed\n");
		return Ret;
	}

	printf("press the key!!\n");

	udelay(50000);

	Ret = HI_UNF_KEY_GetValue(&u32PressStatus, &u32KeyValue);
	printf("get key %d %d\n", u32KeyValue, u32PressStatus);

	while (u32KeyValue == RECOVERY_KEY && u32PressStatus == KEY_PRESS) {

		udelay(1000);
		*keyvalue = u32KeyValue;
		Ret = HI_UNF_KEY_GetValue(&u32PressStatus, &u32KeyValue);
		if (s32Cnt >= MAX_KEY_PRESS_COUNT)
			break;
		else if (u32PressStatus == KEY_RELEASE) {
			*keyvalue = -1;
			u32KeyValue = 0;
			s32Cnt = 0;
			break;
		} else {
			s32Cnt++;
		}
	}

	Ret = HI_UNF_LED_Close();
	if (HI_SUCCESS != Ret) {
		printf("LED close failed\n");
		return Ret;
	}

	Ret = HI_UNF_KEY_Close();
	if (HI_SUCCESS != Ret) {
		printf("key close failed\n");
		return Ret;
	}

	Ret = HI_UNF_KEYLED_DeInit();
	if (HI_SUCCESS != Ret) {
		printf("DeInit close failed\n");
		return Ret;
	}

	return HI_SUCCESS;

}
#ifdef HI_REMOTE_RECOVERY
#define MAX_KEY_COUNT 30
int check_remote_recovery(void)
{
    HI_S32 ret = HI_FAILURE;
	HI_U32 cnt = 0;
    enum KEY_STATUS PressStatus = KEY_STAT_BUTT;
    HI_U64 KeyId = 0;

    printf("check remote recovery button begin\n");

    ret = HI_UNF_IR_Init();
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_IR_Init failed\n");
        return ret;
    }

    ret = HI_UNF_IR_Enable(HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_IR_Enable failed\n");
        ret = HI_FAILURE;
        goto OUT;
    }
	ret = HI_UNF_IR_GetValue(&PressStatus, &KeyId, 400);
    if (HI_SUCCESS != ret)
    {
		printf("HI_UNF_IR_GetValue failed\n");
		ret = HI_FAILURE;
		goto OUT;
    }
	printf("remote button KeyId is %lld,status:%d\n", KeyId,PressStatus);

	while( KeyId  == REMOTE_BTN_RECOVER ){
		KeyId = 0;
        ret = HI_UNF_IR_GetValue(&PressStatus, &KeyId, 400);
        if (HI_SUCCESS != ret)
        {
			printf("HI_UNF_IR_GetValue failed\n");
            break;
        }
		cnt++;
		if(cnt > MAX_KEY_COUNT)
		{
			printf("remote button to recovery success!\n");
			ret = HI_SUCCESS;
			goto OUT;
		}
		printf("remote button KeyId is %lld,status:%d\n", KeyId,PressStatus);
		udelay(2000);
	}
    ret = HI_FAILURE;
OUT:

    if (HI_SUCCESS != HI_UNF_IR_DeInit())
    {
        printf("HI_UNF_IR_DeInit failed\n");
    }

    return ret;
}
#endif

const char *boot_select(void)
{
	int ret;
	int count = 0;
	unsigned int len = 0;
	unsigned char *buf;
	unsigned char *buf1;
	int keycode = -1;

	HI_HANDLE flashhandle;

	HI_Flash_InterInfo_S pFlashInfo;

	unsigned int pagesize;
	unsigned int erasesize;
#ifdef HI_REMOTE_RECOVERY
	if(HI_SUCCESS == check_remote_recovery())
	{
		printf("enter the remote button recovery\n");
		gpio_recovery = 1;
	}
#endif
	flashhandle = HI_Flash_OpenByName(FASTBOOT_MISC_NAME);
	if ((0 == flashhandle) || (HI_INVALID_HANDLE == flashhandle)) {
		printf("HI_Flash_Open partion %s error\n", FASTBOOT_MISC_NAME);
	} else {
		ret = HI_Flash_GetInfo(flashhandle, &pFlashInfo);
		if (ret) {
			printf("HI_Flash_GetInfo %s error\n",
			       FASTBOOT_MISC_NAME);
		}
		switch (pFlashInfo.FlashType) {
		case HI_FLASH_TYPE_SPI_0:
			printf("misc partition can not in spi ERROR!\n");
			HI_Flash_Close(flashhandle);
			break;
		case HI_FLASH_TYPE_NAND_0:
			pagesize = pFlashInfo.PageSize;
			erasesize = pFlashInfo.BlockSize;
			len = MISC_PAGES * pagesize;
			buf =
			    (unsigned char *)malloc(len *
						    sizeof(unsigned char));
			if (buf == NULL) {
				printf("malloc buf failed\n");
				HI_Flash_Close(flashhandle);
				break;
			}

			buf1 =
			    (unsigned char *)malloc(len *
						    sizeof(unsigned char));
			if (buf1 == NULL) {
				printf("malloc buf1 failed\n");
				free(buf);
				buf = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}

			ret =
			    HI_Flash_Read(flashhandle, FASTBOOT_MISC_OFFSET,
					  buf, len, HI_FLASH_RW_FLAG_RAW);
			if (ret == HI_FAILURE) {
				printf("HI_Flash_Read partion %s error\n",
				       FASTBOOT_MISC_NAME);
				free(buf);
				free(buf1);
				buf = NULL;
				buf1 = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}

			ret =
			    HI_Flash_Read(flashhandle, erasesize, buf1, len,
					  HI_FLASH_RW_FLAG_RAW);
			if (ret == HI_FAILURE) {
				printf("HI_Flash_Read partion %s error\n",
				       FASTBOOT_MISC_NAME);
				free(buf);
				free(buf1);
				buf = NULL;
				buf1 = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}
			/*check magic number */
			len = MISC_COMMAND_PAGE * pagesize;
			if ((0 == (memcmp(&buf[len], "boot-recovery", 13))) ||
			    (0 == (memcmp(&buf1[len], "boot-setlable", 13)))) {
				free(buf);
				free(buf1);
				buf = NULL;
				buf1 = NULL;
				HI_Flash_Close(flashhandle);
				return "recovery";
			}
#ifdef HI_REMOTE_RECOVERY
			else if (gpio_recovery){
                memcpy(&buf[len], "boot-recovery", 14);
				memcpy(&buf[len+64],"recovery\n--send_intent=update_ui\n",33);
				ret = HI_Flash_Erase(flashhandle,FASTBOOT_MISC_OFFSET,len);
			    if (ret == HI_FAILURE) {
				    free(buf);
				    free(buf1);
				    buf = NULL;
				    buf1 = NULL;
				    HI_Flash_Close(flashhandle);
				    break;
                }
				ret = HI_Flash_Write(flashhandle, FASTBOOT_MISC_OFFSET,
					  buf, len, HI_FLASH_RW_FLAG_RAW);
		        if (ret == HI_FAILURE) {
				    free(buf);
				    free(buf1);
				    buf = NULL;
				    buf1 = NULL;
				    HI_Flash_Close(flashhandle);
				    break;
                }
				return "recovery";
			}
#endif
			else{
				free(buf);
				free(buf1);
				buf = NULL;
				buf1 = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}
		case HI_FLASH_TYPE_EMMC_0:
			len = 6 * SZ_1KB;
			buf =
			    (unsigned char *)malloc(len *
						    sizeof(unsigned char));
			if (!buf) {
				printf("malloc buf failed\n");
				HI_Flash_Close(flashhandle);
				break;
			}

			ret =
			    HI_Flash_Read(flashhandle, FASTBOOT_MISC_OFFSET,
					  buf, len, HI_FLASH_RW_FLAG_RAW);
			if (ret == HI_FAILURE) {
				printf("HI_Flash_Read partion %s error\n",
				       FASTBOOT_MISC_NAME);
				free(buf);
				buf = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}

			int len1 = MISC_EMMC_COMMAND_PAGE * SZ_1KB;
			int len2 = MISC_EMMC_WRITE_LABEL_COMMAND_PAGE * SZ_1KB;
			if (0 == (memcmp(&buf[len1], "boot-recovery", 13)) ||
			    0 == (memcmp(&buf[len2], "boot-setlable", 13))) {
				free(buf);
				buf = NULL;
				HI_Flash_Close(flashhandle);
				return "recovery";
			}
#ifdef HI_REMOTE_RECOVERY
			else if (gpio_recovery){
                memcpy(&buf[len1], "boot-recovery", 14);
				memcpy(&buf[len1+64],"recovery\n--send_intent=update_ui\n",33);
				ret = HI_Flash_Erase(flashhandle,FASTBOOT_MISC_OFFSET,len);
			    if (ret == HI_FAILURE) {
				    free(buf);
				    free(buf1);
				    buf = NULL;
				    buf1 = NULL;
				    HI_Flash_Close(flashhandle);
				    break;
                }
				ret = HI_Flash_Write(flashhandle, FASTBOOT_MISC_OFFSET,
					  buf, len, HI_FLASH_RW_FLAG_RAW);
		        if (ret == HI_FAILURE) {
				    free(buf);
				    free(buf1);
				    buf = NULL;
				    buf1 = NULL;
				    HI_Flash_Close(flashhandle);
				    break;
                }
				printf("bigfish __recovery__ok");
				return "recovery";
			}
#endif
			 else {
				free(buf);
				buf = NULL;
				HI_Flash_Close(flashhandle);
				break;
			}

		default:
			HI_Flash_Close(flashhandle);
			break;
		}
	}




	if (check_gpio_recovery() == HI_SUCCESS) {
		printf("enter the gpio press revocery\n");
		return "recovery";
	}
    ret = check_buttom_recovery(&keycode);
	if (keycode == RECOVERY_KEY && ret == HI_SUCCESS) {
		printf("enter the keypress revocery,keycode=%d\n", keycode);
	    return "recovery";
	}
	return "kernel";
}

int load_recovery_image(void)
{
	int ret;
	size_t cnt;
	const HI_CHAR *addr = KERNEL_LOAD_ADDR;
	HI_HANDLE flashhandle;
	HI_Flash_InterInfo_S pFlashInfo;

	flashhandle = HI_Flash_OpenByName(FASTBOOT_RECOVERY_NAME);
	if ((0 == flashhandle) || (HI_INVALID_HANDLE == flashhandle)) {
		printf("HI_Flash_Open partion %s error\n",
		       FASTBOOT_RECOVERY_NAME);
		return HI_FAILURE;
	}

	ret = HI_Flash_GetInfo(flashhandle, &pFlashInfo);
	if (ret == HI_FAILURE) {
		printf("HI_Flash_GetInfo partion %s error\n",
		       FASTBOOT_RECOVERY_NAME);
		HI_Flash_Close(flashhandle);
		return HI_FAILURE;
	}
	ret =
	    HI_Flash_Read(flashhandle, FASTBOOT_RECOVERY_OFFSET, addr,
			  pFlashInfo.PartSize, HI_FLASH_RW_FLAG_RAW);
	if (ret == HI_FAILURE) {
		printf("HI_Flash_Read partion %s error\n",
		       FASTBOOT_RECOVERY_NAME);
		HI_Flash_Close(flashhandle);
		return HI_FAILURE;
	}
	HI_Flash_Close(flashhandle);

	printf("Automatic boot of image at addr 0x%08lx ...\n", addr);
	ret = kern_load(addr);
	if (ret < 0) {
		printf("recovery bootm failed!\n");
		return -1;
	}

	return 0;
}

void load_recovery(void)
{
	if (!strcmp(boot_select(), "kernel"))
		return;
	char *recovery_boot_args = NULL;
	char *boot_args = NULL;

#ifdef HI_ADVCA_SUPPORT
	if (-1 == HI_Android_Auth_Recovery())
	{
		run_command("reset", 0);
	}
#endif
	boot_args = (char *)malloc(strlen(getenv("bootargs")) + 1);
	if (!boot_args) {
		printf("malloc fail ! recovery !\n");
		return;
	}
	strcpy(boot_args, getenv("bootargs"));

	printf("bootargs:%s\n", boot_args);

	if (getenv("recoverybootargs")) {
		recovery_boot_args =
		    (char *)malloc(strlen(getenv("recoverybootargs")) + 1);
		if (!recovery_boot_args) {
			free(boot_args);
			printf("please setenv bootargs! exit!\n");
			return;
		}
		strcpy(recovery_boot_args, getenv("recoverybootargs"));
		setenv("bootargs", recovery_boot_args);
	}

	printf("==Enter recovery!\n");
	printf("recoverybootargs:%s\n", getenv("bootargs"));

	free(recovery_boot_args);
	recovery_boot_args = NULL;

	if (load_recovery_image() != 0) {
		printf("enter recovery fail!!\n");
		setenv("bootargs", boot_args);
		free(boot_args);
		boot_args = NULL;
	}
}
