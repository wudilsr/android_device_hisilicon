#include <uboot.h>

#include "hi_type.h"
#include "hi_common.h"
#include "hi_drv_pmoc.h"
#include "hi_reg.h"
//#include "platform_common.h"  //++

#ifdef HI_MINIBOOT_SUPPORT
#include "stdio.h"
#endif

static HI_U32 wdgon     = 0;
static HI_U32 dbgmask   = 0x2;
static HI_U32 keyVal    = 0x8;
static HI_U32 kltype    = 2;
static HI_U32 timeVal   = 0xffffffff;
static HI_U32 dispMode  = 2;
static HI_U32 irtype    = 4;
static HI_U32 irpmocnum = 3;
static HI_U32 dispvalue = 0x00093a00;
static HI_U32 irValhigh[MCU_IRKEY_MAXNUM] = {0, 0, 0, 0, 0, 0};
static HI_U32 irVallow[MCU_IRKEY_MAXNUM]  = {0x639cff00, 0xef101980, 0xf40b5da0, 0, 0, 0};
static HI_U32 GpioValArray[2] = {0, 0};
static HI_U32 g_u32GpioPortVal = 0x2a;

static HI_U32 lu32vC51Code[MCU_CODE_MAXSIZE/4] = {
#ifdef HI_ADVCA_SUPPORT
#include "output_ca.txt"
#else
#include "output.txt"
#endif
};
static HI_U8 *ltvVirAddr = NULL;

#define C51_GetVIRAddr(addr)  (ltvVirAddr + ((addr) - C51_BASE))

#define START_PMOC_ENABLE

HI_S32  c51_loadCode(void)
{
    HI_S32 ret;
    HI_U32 i = 0;
    HI_U32 size = 0;
    HI_U32 *dwPtr = NULL;
    HI_CHIP_TYPE_E enChipType;
    HI_CHIP_VERSION_E enChipID;

    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipID);
    
    /* if s40v2 , set 0xf800_0048 bit1 to 0 */
    HI_REG_READ32((CFG_BASE_ADDR + SRST_REQ_CTRL), ret);
    ret &= ~0x2;
    HI_REG_WRITE32((CFG_BASE_ADDR + SRST_REQ_CTRL), ret);

    ltvVirAddr = (HI_U8 *)C51_BASE;
   
    dwPtr = (HI_U32 *)C51_GetVIRAddr(C51_BASE);
    size = sizeof(lu32vC51Code);

    for (i = 0; i < (size >> 2); i++)
    {
        HI_REG_WRITE32((dwPtr + i), lu32vC51Code[i]);
    }

    dwPtr = (HI_U32 *)C51_GetVIRAddr(C51_BASE + C51_DATA);
 
    HI_REG_WRITE32((dwPtr + 0), (enChipType | (enChipID << 16)));
    HI_REG_WRITE32((dwPtr + 1), wdgon);
    HI_REG_WRITE32((dwPtr + 2), dbgmask);
    HI_REG_WRITE32((dwPtr + 3), GpioValArray[0]);  /*record gpio index, between 40 and 47 */
    HI_REG_WRITE32((dwPtr + 4), GpioValArray[1]);  /*record gpio output, 1 or 0 */

    HI_REG_WRITE32((dwPtr + 5), dispMode);
    HI_REG_WRITE32((dwPtr + 6), dispvalue);
    HI_REG_WRITE32((dwPtr + 7), timeVal);

    HI_REG_WRITE32((dwPtr + 8), kltype);
    HI_REG_WRITE32((dwPtr + 9), keyVal);

    HI_REG_WRITE32((dwPtr + 10), irtype);
    HI_REG_WRITE32((dwPtr + 11), irpmocnum);

    for (i = 0; i < irpmocnum; i++)
    {
        HI_REG_WRITE32((dwPtr + 12 + 2 * i), irVallow[i]);
        HI_REG_WRITE32((dwPtr + 13 + 2 * i), irValhigh[i]);
    }

    /* save ca vendor */
    HI_REG_READ32(REG_CA_VENDOR_ID, ret);
    ret &= 0xff;
    HI_REG_WRITE32((dwPtr + 12 + 2 * irpmocnum), ret);

    HI_REG_WRITE32((dwPtr + 13 + 2 * irpmocnum), g_u32GpioPortVal);
    
    HI_REG_WRITE32(SC_GEN15, C51_CODE_LOAD_FLAG); //indicate the C51 code is loaded

    return HI_SUCCESS;
}

void LightenBlue(void)
{
    HI_U32 data;

#if defined(CHIP_TYPE_hi3798cv100)   \
|| defined(CHIP_TYPE_hi3798cv100_a) \
|| defined(CHIP_TYPE_hi3796cv100)   \
|| defined(CHIP_TYPE_hi3796cv100_a)
    /* Close red light */
    HI_REG_READ32(0xf8009400, data);
    data |= 0x80;
    HI_REG_WRITE32(0xf8009400, data);

    HI_REG_READ32(0xf8009200, data);
    data |= 0x80;
    HI_REG_WRITE32(0xf8009200, data);
    
    /* Open blue light */
    HI_REG_READ32(0xf8004400, data);
    data |= 0x10;
    HI_REG_WRITE32(0xf8004400, data);

    HI_REG_READ32(0xf8004040, data);
    data &= 0xef;
    HI_REG_WRITE32(0xf8004040, data);
#else
    /* set gpio5_5, 5_6  to green light */
    HI_REG_READ32(0xf8004400, data);
    data |= 0x60;
    HI_REG_WRITE32(0xf8004400, data);

    HI_REG_WRITE32(0xf8004180, 0x40);
#endif
}

#ifdef HI_PM_POWERUP_MODE1_SUPPORT
extern unsigned int get_selfboot_type(void);
void boot_suspend(void)
{
    HI_S32 ret;
    HI_U32 data;
    HI_U32 u32Count = 0;

#if defined(CONFIG_BOOTROM_SUPPORT)
    HI_U32 u32SelfbootType ;

    u32SelfbootType = get_selfboot_type();
    if (SELF_BOOT_TYPE_USBHOST == u32SelfbootType)
    {
        HI_PRINT("\nBoot suspend: self boot, jump out.\n");
        LightenBlue();
        c51_loadCode();
	
        /* set bootflag to running status */
        HI_REG_WRITE32(MCU_STATUS_ADDR, KERNEL_RUNNING);
        return;	
    }
#endif    

    /* if press recovery key, jump this MCU code */
    while (1)
    {
#if    defined(CHIP_TYPE_hi3798cv100)   \
    || defined(CHIP_TYPE_hi3798cv100_a) \
    || defined(CHIP_TYPE_hi3796cv100)   \
    || defined(CHIP_TYPE_hi3796cv100_a)
        /* read gpio1_stb0 */
        HI_REG_READ32(0xf8009400, data);
        data &= 0xfe; //set bit0 to input
        HI_REG_WRITE32(0xf8009400, data);

        HI_REG_READ32(0xf8009004, data);
#else
        /* read gpio2_0 */
        HI_REG_READ32(0xf8b22400, data);
        data &= 0xfe; //set bit0 to input
        HI_REG_WRITE32(0xf8b22400, data);

        HI_REG_READ32(0xf8b22004, data);
#endif
        if (0 == (data & 0x01))
        {
            u32Count++;
        }
        else
        {
            u32Count = 0;
            break;
        }

        if (u32Count > 20)
        {
            HI_PRINT("\nBoot suspend: gpio detect, jump out to recovery.\n");
            LightenBlue();
            c51_loadCode();
		
	        /* set bootflag to running status */
            HI_REG_WRITE32(MCU_STATUS_ADDR, KERNEL_RUNNING);
            return;
        }

        udelay (30 * 1000);
    }

    /* If  reset from linux or wake up by watchdog reset, return */ 
    HI_REG_READ32(MCU_STATUS_ADDR, data);
    if (KERNEL_RUNNING != data)
    {
        if (MCU_LOAD_CODE != data)
        {
            /* Load code to mcu in first power up*/
            c51_loadCode();

            /* Need to set in boot reg instead of setting here. Set port to gpio */
            //HI_REG_WRITE32(0xf8008054, 0x1);

#if    defined(CHIP_TYPE_hi3798cv100)   \
    || defined(CHIP_TYPE_hi3798cv100_a) \
    || defined(CHIP_TYPE_hi3796cv100)   \
    || defined(CHIP_TYPE_hi3796cv100_a)
            /* read gpio1_stb1:1 means power to run, 0 means power to standby */
            HI_REG_READ32(0xf8009400, data);
            data &= 0xfd; //set bit1 to input
            HI_REG_WRITE32(0xf8009400, data);

            HI_REG_READ32(0xf8009008, data);
            if (0 == (data & 0x02))
#else
            /* read gpio0_7:1 means power to run, 0 means power to standby */
            HI_REG_READ32(0xf8b20400, data);
            data &= 0x7f; //set bit7 to input
            HI_REG_WRITE32(0xf8b20400, data);

            HI_REG_READ32(0xf8b20200, data);
            if (0 == (data & 0x80))
#endif            
            {
                HI_PRINT("\nBoot suspend: enter standby.\n");
                
                /* indicate the C51 code is loaded, offset 0x51c  */
                HI_REG_WRITE32(MCU_STATUS_ADDR, MCU_LOAD_CODE);

                /* start MCU */
                HI_REG_WRITE32(C51_BASE + C51_START, 0x1);

                /* wait for enter standby */
                while(1);
            }

            HI_PRINT("\nBoot suspend: continue to boot.\n");
        }
        
        /* set bootflag to running status */
        HI_REG_WRITE32(MCU_STATUS_ADDR, KERNEL_RUNNING);
    }
    
    /* start MCU */
    HI_REG_WRITE32(C51_BASE + C51_START, 0x0);
    udelay(1000);
    HI_REG_WRITE32(C51_BASE + C51_START, 0x1);

    LightenBlue();
    
    return;
}
#endif

