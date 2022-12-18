#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <asm/io.h>
#include <asm/memory.h>
#include <linux/linkage.h>
#include <linux/fs.h>
#include <linux/timer.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/errno.h>
#include <linux/reboot.h>
#include "hi_common.h"
#include "hi_drv_pmoc.h"
#include "drv_pmoc_ioctl.h"
#include "hi_osal.h"

#include "hi_reg_common.h"
#include "hi_kernel_adapt.h"

#include "hi_drv_module.h"
#include "hi_drv_proc.h"
#include "hi_drv_reg.h"
#include "hi_drv_dev.h"
#include "hi_drv_sys.h"
#include "clock.h"
#include "drv_pmoc_priv.h"
#include "drv_gpio_ext.h"
#include <linux/kthread.h>
#include "hi_dvfs.h"

extern unsigned int mpu_get_volt(void);
extern void mpu_init_volt(void);
//extern void hi_cpufreq_hotplug_exit(void);
extern void hi_cpufreq_exit(void);
extern void mpu_exit_clocks(void);
extern void core_init_volt(void);
extern void core_init_hpm(void);
extern void mpu_deinit_volt(void);

//extern int  hi_cpufreq_hotplug_init(void);
extern int  cpufreq_gov_debug_init(void);
extern int  cpufreq_gov_dbs_init(void);
extern int  hi_cpufreq_init(void);
extern int  regulator_pwm_voltage_init(void);
extern int  cpu_volt_scale(unsigned int volt);
extern int  core_volt_scale(unsigned int volt);

/*clk_set_rate(mpu_ck, new_freq)*/
extern struct clk mpu_ck;
extern unsigned long cur_cpu_volt;
extern unsigned long cur_core_volt;
extern unsigned long init_core_volt;

#ifdef HI_DVFS_CPU_SUPPORT
extern unsigned int cpu_dvfs_enable;
extern struct mutex hi_dvfs_lock;
extern int pm_cpufreq_boost(void);
#ifdef HI_TEMP_CTRL_CONFIG
#define TEMP_DOWN HI_TEMP_CTRL_DOWN_THRESHOLD
#define TEMP_UP HI_TEMP_CTRL_UP_THRESHOLD
#define TEMP_REBOOT HI_TEMP_CTRL_REBOOT_THRESHOLD
static HI_S16 g_s16TempUp;
static HI_S16 g_s16TempDown;
static HI_S16 g_s16TempReboot;
static HI_U8 g_u8TempCtrlEnable;
static struct task_struct *pstTempCtrlThread = HI_NULL;
#endif
#endif

#ifdef HI_AVS_SUPPORT
extern HI_U8 g_u8CpuHpmOffset;
extern void         CPU_AVS_Enable(unsigned int enable);
extern unsigned int CPU_AVS_GetStatus(void);
#endif

#define MCU_START_REG 0xf840f000
#define REG_CA_ID_WORD 0xf8ab0128
#define LPC_LOCK_REG 0xf8ab0184
#define SC_GEN_BASE 0xf8000000
#define REG_CA_VENDOR_ID   0xf8ab012c //CA vendor id

#define HI_CHIP_NON_ADVCA 0x2a13c812
#define HI_CHIP_ADVCA 0x6edbe953

#ifdef HI_GPIO_LIGHT_SUPPORT
static GPIO_EXT_FUNC_S *s_pGpioFunc = HI_NULL;
#define GPIO_LIGHT HI_GPIO_LIGHT_SET
#endif

#define ENTER_FLAG_ADD 0xf8407520


static HI_U32 wdgon = 0x0;
static HI_U32 dbgmask   = 0x1;
static HI_U32 keyVal    = 0;
static HI_U32 kltype    = 0;
static HI_U32 timeVal   = 0xffffffff;
static HI_U32 dispMode  = 2;
static HI_U32 irtype    = 0;
static HI_U32 irpmocnum = 1;
static HI_U32 dispvalue = 0x00093a00;
static HI_U8 g_u8UsbWakeUpMask = 0;
static HI_U8 g_u8EthWakeUpEnable = 0;
static HI_U8 g_u8FwEnable = 0;
static HI_U32 irValhigh[PMOC_WKUP_IRKEY_MAXNUM] = {
    0, 0, 0, 0, 0, 0
};
static HI_U32 irVallow[PMOC_WKUP_IRKEY_MAXNUM] = {
    0x639cff00, 0, 0, 0, 0, 0
};
static C51_PMOC_WAKEUP_E wakeupMode;

static HI_U32 g_u32StandbyPeriod = 0;

static UMAP_DEVICE_S g_stPmDev;

static HI_U32 GpioValArray[2] = {
    0, 0
};

static HI_U32 g_u32GpioPortVal = 0xff;

static HI_U32 lu32vC51Code[MCU_CODE_MAXSIZE/4] = {
#include "output.txt"
};

static HI_U8 *ltvVirAddr = NULL;

static struct semaphore c51Sem;
static PM_CMD_DATA_S g_astProcCmd[PM_CMD_MAX_NUM];

extern HI_VOID HI_DRV_SYS_GetChipVersion(HI_CHIP_TYPE_E *penChipType, HI_CHIP_VERSION_E *penChipVersion);

#define C51_GetVIRAddr(addr) (ltvVirAddr + ((addr) - C51_BASE))

static HI_BOOL get_Advca_Support(void)
{
    HI_U32 AdvcaFlag;
    HI_U32 * pCaIdWord = HI_NULL_PTR;

    pCaIdWord = ioremap_nocache(REG_CA_ID_WORD, 0x4);
    if (HI_NULL == pCaIdWord)
    {
        HI_ERR_PM("ioremap_nocache CA ID WORD err! \n");
        return HI_FALSE;
    }

    HI_REG_READ(pCaIdWord, AdvcaFlag);

    iounmap(pCaIdWord);

    if (HI_CHIP_ADVCA == AdvcaFlag)
    {
        return HI_TRUE;
    }
    else if (HI_CHIP_NON_ADVCA == AdvcaFlag)
    {
        return HI_FALSE;
    }
    else
    {
        HI_ERR_PM("invalid advca flag\n");
        return HI_FALSE;
    }
}

static HI_S32  c51_loadCode(HI_VOID)
{
    HI_U32 i = 0;
    HI_U32 size = 0;
    HI_U32 *dwPtr = NULL;
    HI_U32 * pMcuStart = HI_NULL_PTR;
    HI_CHIP_TYPE_E enChipType;
    HI_CHIP_VERSION_E enChipID;
    U_SC_CLKGATE_SRST_CTRL unTmpValue;

    HI_U32 u32CaVendor = 0;

    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipID);
    HI_INFO_PM("\n HI_DRV_SYS_GetChipVersion   enChipType = %d, enChipID = 0x%x \n", enChipType, enChipID);

    unTmpValue.u32 = g_pstRegSysCtrl->SC_CLKGATE_SRST_CTRL.u32;
    unTmpValue.bits.mce_srst_req = 0;
    g_pstRegSysCtrl->SC_CLKGATE_SRST_CTRL.u32 = unTmpValue.u32;

    if (g_u8UsbWakeUpMask != 0)
    {
#if defined(CHIP_TYPE_hi3719mv100) || defined(CHIP_TYPE_hi3718mv100)
        U_PERI_USB_SUSPEND_INT_MASK unTmpValueUSBMask;
        unTmpValueUSBMask.u32 = g_pstRegPeri->PERI_USB_SUSPEND_INT_MASK.u32;
#else
        U_PERI_USB_RESUME_INT_MASK unTmpValueUSBMask;
        unTmpValueUSBMask.u32 = g_pstRegPeri->PERI_USB_RESUME_INT_MASK.u32;
#endif

#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
        unTmpValueUSBMask.bits.peri_usb_suspend_int_mask = g_u8UsbWakeUpMask;
#else
        if (g_u8UsbWakeUpMask & 0x01)
        {
            unTmpValueUSBMask.bits.usb_phy0_suspend_int_mask = 1;
        }
#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3798cv200_a)
        if (g_u8UsbWakeUpMask & 0x02)
        {
            unTmpValueUSBMask.bits.usb3_utmi_suspend_n = 1;
        }
#endif

#if !(defined(CHIP_TYPE_hi3719mv100) || defined(CHIP_TYPE_hi3718mv100)|| defined(CHIP_TYPE_hi3716mv410)|| defined(CHIP_TYPE_hi3716mv420))
        if (g_u8UsbWakeUpMask & 0x04)
        {
            unTmpValueUSBMask.bits.usb_phy2_suspend_int_mask = 1;
        }
#endif

        if (g_u8UsbWakeUpMask & 0x08)
        {
#if defined(CHIP_TYPE_hi3798cv200_a)
            unTmpValueUSBMask.bits.usb_phy3_suspend_int_mask = 1;
#else
            unTmpValueUSBMask.bits.usb_phy1_suspend_int_mask = 1;
#endif
        }
#endif

#if defined(CHIP_TYPE_hi3719mv100) || defined(CHIP_TYPE_hi3718mv100)
        g_pstRegPeri->PERI_USB_SUSPEND_INT_MASK.u32 = unTmpValueUSBMask.u32;
#else
        g_pstRegPeri->PERI_USB_RESUME_INT_MASK.u32 = unTmpValueUSBMask.u32;
#endif

        HI_INFO_PM("\n set  g_u8UsbWakeUpMask to PERI_USB_RESUME_INT_MASK = %d 0x%x \n",
                   g_u8UsbWakeUpMask, unTmpValueUSBMask.u32);
    }

    ltvVirAddr = (HI_U8 *)ioremap_nocache(C51_BASE, C51_SIZE);
    if (ltvVirAddr == NULL)
    {
        HI_WARN_PM("ioremap_nocache err! \n");
        return HI_FAILURE;
    }

    dwPtr = (HI_U32 *)C51_GetVIRAddr(C51_BASE);
    HI_INFO_PM("\n dwPtr BASE = %p\n", dwPtr);

    size = sizeof(lu32vC51Code);
    HI_INFO_PM("\n c51_loadCodetoRam  size = %d \n", size);

#ifndef HI_PM_POWERUP_MODE1_SUPPORT
    pMcuStart = ioremap_nocache(MCU_START_REG, 0x4);
    HI_REG_READ32(pMcuStart, i);
    iounmap(pMcuStart);
    if (0 == i)
    {
        for (i = 0; i < (size >> 2); i++)
        {
            HI_REG_WRITE32((dwPtr + i), lu32vC51Code[i]);
        }
    }
#endif

    dwPtr = (HI_U32 *)C51_GetVIRAddr(C51_BASE + C51_DATA);

    if (g_u8FwEnable || g_u8EthWakeUpEnable)
    {
        HI_REG_WRITE32((dwPtr + 0), (enChipType | (2 << 8)) | (enChipID << 16));
    }
    else if (g_u8UsbWakeUpMask)
    {
        HI_REG_WRITE32((dwPtr + 0), (enChipType | (1 << 8)) | (enChipID << 16));
    }
    else
    {
        HI_REG_WRITE32((dwPtr + 0), (enChipType | (enChipID << 16)));
    }

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
    if (get_Advca_Support())
    {
        HI_REG_READ32(IO_ADDRESS(REG_CA_VENDOR_ID), u32CaVendor);
        u32CaVendor &= 0xff;
        HI_REG_WRITE32((dwPtr + 12 + 2 * irpmocnum), u32CaVendor);
    }

    HI_REG_WRITE32((dwPtr + 13 + 2 * irpmocnum), g_u32GpioPortVal);

    iounmap(ltvVirAddr);

    return HI_SUCCESS;
}

static HI_S32 c51_suspend (PM_BASEDEV_S *pdev, pm_message_t state)
{
    HI_S32 ret = 0;

#ifdef HI_GPIO_LIGHT_SUPPORT
    HI_CHIP_PACKAGE_TYPE_E enPackageType = HI_CHIP_PACKAGE_TYPE_BUTT;
    HI_CHIP_TYPE_E enChipType;
    HI_CHIP_VERSION_E enChipID;

    HI_DRV_SYS_GetChipPackageType(&enPackageType);
    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipID);

    if ((HI_CHIP_TYPE_HI3798M == enChipType) && (HI_CHIP_PACKAGE_TYPE_QFP_216 == enPackageType))
    {
        if (0xff != HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP)
        {
            s_pGpioFunc->pfnGpioDirSetBit(HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP, 0);  //output
            s_pGpioFunc->pfnGpioWriteBit(HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP, 0);
        }
    }
    else
    {
        if (0xff != HI_NEGATIVE_GPIO_LIGHT_NUMBER)
        {
            s_pGpioFunc->pfnGpioDirSetBit(HI_NEGATIVE_GPIO_LIGHT_NUMBER, 0);  //output
            s_pGpioFunc->pfnGpioWriteBit(HI_NEGATIVE_GPIO_LIGHT_NUMBER, 1);
        }

        if (0xff != HI_POSITIVE_GPIO_LIGHT_NUMBER)
        {
            s_pGpioFunc->pfnGpioDirSetBit(HI_POSITIVE_GPIO_LIGHT_NUMBER, 0);  //output
            s_pGpioFunc->pfnGpioWriteBit(HI_POSITIVE_GPIO_LIGHT_NUMBER, 0);
        }
    }
#endif

    ret = c51_loadCode();
    if (ret)
    {
        HI_ERR_PM("c51_loadCode err! \n");
        return HI_FAILURE;
    }

    HI_INFO_PM("c51_loadCode ok! \n");
   


    wakeupMode = C51_PMOC_WAKEUP_BUTT;

    g_u32StandbyPeriod = 0;

#ifdef HI_DVFS_CPU_SUPPORT
    if (HI_TRUE == cpu_dvfs_enable)
    {
        cpu_dvfs_enable = HI_FALSE;

 #ifdef HI_AVS_SUPPORT
        CPU_AVS_Enable(HI_FALSE);
 #endif
    }
#endif

    HI_PRINT("PM suspend OK\n");
    return HI_SUCCESS;
}

extern void mpu_resume_clocks(void);
static HI_S32 c51_resume(PM_BASEDEV_S *pdev)
{
    HI_S32 ret;
    HI_U32 v;
    HI_U32 * pWakeup   = HI_NULL_PTR;
    HI_U32 * pMcuStart = HI_NULL_PTR;

#ifdef HI_GPIO_LIGHT_SUPPORT
    HI_CHIP_PACKAGE_TYPE_E enPackageType = HI_CHIP_PACKAGE_TYPE_BUTT;
    HI_CHIP_TYPE_E enChipType;
    HI_CHIP_VERSION_E enChipID;

    HI_DRV_SYS_GetChipPackageType(&enPackageType);
    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipID);

    if ((HI_CHIP_TYPE_HI3798M == enChipType) && (HI_CHIP_PACKAGE_TYPE_QFP_216 == enPackageType))
    {
        if (0xff != HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP)
        {
            s_pGpioFunc->pfnGpioDirSetBit(HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP, 0);  //output
            s_pGpioFunc->pfnGpioWriteBit(HI_POSITIVE_GPIO_LIGHT_NUMBER_QFP, 1);
        }
    }
    else
    {
        if (0xff != HI_NEGATIVE_GPIO_LIGHT_NUMBER)
        {
            s_pGpioFunc->pfnGpioDirSetBit(HI_NEGATIVE_GPIO_LIGHT_NUMBER, 0);  //output
            s_pGpioFunc->pfnGpioWriteBit(HI_NEGATIVE_GPIO_LIGHT_NUMBER, 0);
        }

        if (0xff != HI_POSITIVE_GPIO_LIGHT_NUMBER)
        {
            s_pGpioFunc->pfnGpioDirSetBit(HI_POSITIVE_GPIO_LIGHT_NUMBER, 0);  //output
            s_pGpioFunc->pfnGpioWriteBit(HI_POSITIVE_GPIO_LIGHT_NUMBER, 1);
        }
    }
#endif


    pWakeup = ioremap_nocache(C51_BASE + C51_DATA + 0xff8, 0x8);
    HI_REG_READ32(pWakeup, ret);
    if (ret < C51_PMOC_WAKEUP_BUTT)
    {
        wakeupMode = (C51_PMOC_WAKEUP_E)ret;
    }
    else
    {
        HI_WARN_PM(" wakeup mode err! \n");
    }

    HI_REG_READ32(pWakeup + 1, g_u32StandbyPeriod);
    iounmap(pWakeup);

#ifdef HI_DVFS_CPU_SUPPORT
    v = mpu_get_volt();
    if (v > cur_cpu_volt)
    {
        mpu_resume_clocks();
        mdelay(15);
        cpu_volt_scale(cur_cpu_volt);
    }
    else
    {
        cpu_volt_scale(cur_cpu_volt);
        mdelay(15);
        mpu_resume_clocks();
    }

    cpu_dvfs_enable = HI_TRUE;
#endif

    pMcuStart = ioremap_nocache(MCU_START_REG, 0x4);
    if (get_Advca_Support())
    {
        HI_REG_WRITE32(pMcuStart, 0x1); //start MCU
 #ifdef HI_AVS_SUPPORT
        core_volt_scale(cur_core_volt);
 #endif
    }
#if defined (HI_PM_POWERUP_MODE1_SUPPORT) || defined (HI_TEMP_CTRL_CONFIG)
    c51_loadCode();
    HI_REG_WRITE32(pMcuStart, 0x1); //start MCU
#endif

    iounmap(pMcuStart);

    HI_PRINT("PM resume OK\n");

    return HI_SUCCESS;
}

static PM_BASEOPS_S c51_baseOps = {
    .probe  = NULL,
    .remove = NULL,
    .shutdown = NULL,
    .prepare  = NULL,
    .complete = NULL,
    .suspend  = c51_suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = c51_resume
};

static HI_VOID C51_SetScene(HI_UNF_PMOC_SCENE_E sence)
{
    if (sence == HI_UNF_PMOC_SCENE_ETH)
    {
        g_u8FwEnable = 1;
    }
    else
    {
        g_u8FwEnable = 0;
    }

    return;
}

static long c51_Ioctl(struct file *file, HI_U32 cmd, HI_SIZE_T arg)
{
    long ret;

    HI_VOID __user *argp = (HI_VOID __user*)arg;

    ret = down_interruptible(&c51Sem);
    if (ret)
    {
        HI_ERR_PM(" down_interruptible err ! \n");
        return ret;
    }

    switch (cmd)
    {
    case HI_PMOC_STANDBY_CMD:
    {
        C51_PMOC_DISP_S dispInfo;

        if (copy_from_user(&dispInfo, argp, sizeof(C51_PMOC_DISP_S)))
        {
            HI_WARN_PM("copy data from user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;
            break;
        }

        dispMode  = dispInfo.mode;
        dispvalue = dispInfo.value;

        HI_INFO_PM("dispMode = %d \n", dispMode);
        HI_INFO_PM("dispvalue = 0x%08x \n", dispvalue);

        ret = HI_SUCCESS;

        break;
    }
    case HI_PMOC_SET_WAKEUP_CMD:
    {
        HI_U32 i;
        C51_PMOC_VAL_S pmocVal;

        if (copy_from_user(&pmocVal, argp, sizeof(C51_PMOC_VAL_S)))
        {
            HI_WARN_PM("copy data from user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;
            break;
        }

        if (pmocVal.irnum > PMOC_WKUP_IRKEY_MAXNUM)
        {
            HI_WARN_PM("Out of the max ir number !\n");
            ret = HI_ERR_PM_INVALID_PARAM;
            break;
        }

        if ((irtype != 4) && (pmocVal.irnum > 1))
        {
            HI_WARN_PM("only ir raw type support several power keys, others support only one power key !\n");
            ret = HI_ERR_PM_INVALID_PARAM;
            break;
        }

        irpmocnum = pmocVal.irnum;

        for (i = 0; i < irpmocnum; i++)
        {
            irVallow[i]  = pmocVal.irlVal[i];
            irValhigh[i] = pmocVal.irhVal[i];
        }

#ifdef HI_KEYLED_SUPPORT
        keyVal = pmocVal.keyVal;
#else
        keyVal = 0xffffffff;
#endif
        timeVal = pmocVal.timeVal;

        g_u8UsbWakeUpMask = pmocVal.usbWakeupMask;
        g_u8EthWakeUpEnable = pmocVal.ethWakeupFlag;

        /* use this param 'wdgon' to control resume reset in C51*/
        wdgon = pmocVal.resumeResetFlag;

        g_u32GpioPortVal = pmocVal.gpioPort;
        
        /* add for quick standby */
        c51_loadCode();

        ret = HI_SUCCESS;

        break;
    }
    case HI_PMOC_GET_WAKEUP_CMD:
    {
        HI_U32 i;
        C51_PMOC_VAL_S pmocVal;

        memset(&pmocVal, 0, sizeof(pmocVal));

        pmocVal.irnum = irpmocnum;

        for (i = 0; i < irpmocnum; i++)
        {
            pmocVal.irlVal[i] = irVallow[i];
            pmocVal.irhVal[i] = irValhigh[i];
        }

#ifdef HI_KEYLED_SUPPORT
        pmocVal.keyVal = keyVal;
#else
        pmocVal.keyVal = 0xffffffff;
#endif
        pmocVal.timeVal = timeVal;
        pmocVal.usbWakeupMask = g_u8UsbWakeUpMask;
        pmocVal.ethWakeupFlag = g_u8EthWakeUpEnable;

        /* use this param 'wdgon' to control resume reset in C51*/
        pmocVal.resumeResetFlag = wdgon;

        pmocVal.gpioPort = g_u32GpioPortVal;

        if (copy_to_user(argp, &pmocVal, sizeof(C51_PMOC_VAL_S)))
        {
            HI_WARN_PM(" copy data to user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;
            break;
        }

        ret = HI_SUCCESS;

        break;
    }
    case HI_PMOC_WAKEUP_READY_CMD:
    {
#ifdef HI_DVFS_CPU_SUPPORT
        cpu_dvfs_enable = HI_FALSE;
#endif

#ifdef HI_AVS_SUPPORT
        CPU_AVS_Enable(HI_FALSE);
#endif
        ret = HI_SUCCESS;

        break;
    }
    case HI_PMOC_WAKEUP_FINISH_CMD:
    {
        if (copy_to_user(argp, &wakeupMode, sizeof(C51_PMOC_WAKEUP_E)))
        {
            HI_WARN_PM(" copy data to user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;
            break;
        }

#ifdef HI_DVFS_CPU_SUPPORT
        cpu_dvfs_enable = HI_TRUE;
#endif

        ret = HI_SUCCESS;

        break;
    }
    case HI_PMOC_GET_PERIOD_CMD:
    {
        if (copy_to_user(argp, &g_u32StandbyPeriod, sizeof(HI_U32)))
        {
            HI_WARN_PM(" copy data to user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;
            break;
        }

        ret = HI_SUCCESS;

        break;
    }
    case HI_PMOC_WAKEUP_SETDEV_CMD:
    {
        C51_PMOC_DEV_S dev;

        if (copy_from_user(&dev, argp, sizeof(C51_PMOC_DEV_S)))
        {
            HI_WARN_PM(" copy data from user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;
            break;
        }

#ifdef HI_KEYLED_SUPPORT
        kltype = dev.kltype;
#endif
        irtype = dev.irtype;

        ret = HI_SUCCESS;

        break;
    }

    case HI_PMOC_LOAD_MCUCODE_CMD:
    {
        if (copy_from_user(lu32vC51Code, argp, sizeof(lu32vC51Code)))
        {
            HI_WARN_PM(" copy data from user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;

            break;
        }

        ret = HI_SUCCESS;

        break;
    }

    case HI_PMOC_SET_SCENE_CMD:
    {
        HI_UNF_PMOC_SCENE_E enPmocSence;

        if (copy_from_user(&enPmocSence, argp, sizeof(HI_UNF_PMOC_SCENE_E)))
        {
            HI_WARN_PM(" copy data from user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;
            break;
        }

        C51_SetScene(enPmocSence);

        ret = HI_SUCCESS;

        break;
    }

    case HI_PMOC_SET_PWROFFGPIO_CMD:
    {
        if (copy_from_user(GpioValArray, argp, sizeof(GpioValArray)))
        {
            HI_WARN_PM(" copy data from user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;
            break;
        }

        ret = HI_SUCCESS;

        break;
    }

    case HI_PMOC_ENTER_SMARTSTANDBY_CMD:
    {
        HI_U32 u32HoldModules;
        if (copy_from_user(&u32HoldModules, argp, sizeof(u32HoldModules)))
        {
            HI_WARN_PM("copy data from user fail!\n");
            ret = HI_ERR_PM_COPY_DATA_ERR;
            break;
        }

        ret = PMEnterSmartStandby(u32HoldModules);
        break;
    }

    case HI_PMOC_QUIT_SMARTSTANDBY_CMD:
    {
        ret = PMQuitSmartStandby();
        break;
    }
    case HI_PMOC_BOOST_CPU:
    {
#ifdef HI_DVFS_CPU_SUPPORT
        ret = pm_cpufreq_boost();
#endif
        break;
    }
    default:
    {
        ret = -ENOIOCTLCMD;
        break;
    }
    }

    up(&c51Sem);

    return ret;
}

static HI_S32 c51_Open(struct inode *inode, struct file *filp)
{
    return HI_SUCCESS;
}

static HI_S32 c51_Release(struct inode *inode, struct file *filp)
{
    return HI_SUCCESS;
}

static struct file_operations stC51fopts = {
    .owner = THIS_MODULE,
    .open  = c51_Open,
    .release        = c51_Release,
    .unlocked_ioctl = c51_Ioctl,
};

HI_S32 PMParseCmd(HI_U8* pu8Cmd, HI_U32 u32Len, PM_CMD_DATA_S** pstCmd, HI_U32* pu32Num)
{
    HI_U32 u32Pos = 0;
    HI_U32 u32SavePos = 0;
    HI_U32 u32CmdNum  = 0;
    HI_BOOL bIsCmd = HI_TRUE;
    HI_U8 u8LastChar = ' ';

    if ((HI_NULL == pu8Cmd) || (0 == u32Len) || (HI_NULL == pstCmd) || (HI_NULL == pu32Num))
    {
        HI_ERR_PM("Invalid.\n");
        return HI_FAILURE;
    }

    u32CmdNum = 0;
    memset(g_astProcCmd, 0, sizeof(g_astProcCmd));

    while ((u32Pos < u32Len) && (pu8Cmd[u32Pos]))
    {
        switch (pu8Cmd[u32Pos])
        {
        case '\0':
        case '\n':
        case '\t':
            break;

        case '=':
            if (bIsCmd)
            {
                bIsCmd = HI_FALSE;
                u32SavePos = 0;
            }

            break;
        case ' ':
            if (!((' ' == u8LastChar) || ('=' == u8LastChar)))
            {
                bIsCmd = !bIsCmd;
                u32SavePos = 0;
                if (bIsCmd)
                {
                    if (u32CmdNum < PM_CMD_MAX_NUM - 1)
                    {
                        u32CmdNum++;
                    }
                    else
                    {
                        goto out;
                    }
                }
            }

            break;
        default:
            if (bIsCmd)
            {
                if (u32SavePos < PM_CMD_MAX_CMD_LEN)
                {
                    g_astProcCmd[u32CmdNum].aszCmd[u32SavePos++] = pu8Cmd[u32Pos];
                }
            }
            else
            {
                if (u32SavePos < PM_CMD_MAX_VLAUE_LEN)
                {
                    g_astProcCmd[u32CmdNum].aszValue[u32SavePos++] = pu8Cmd[u32Pos];
                }
            }

            break;
        }

        u8LastChar = pu8Cmd[u32Pos];
        u32Pos++;
    }

out:
    if (strlen(g_astProcCmd[u32CmdNum].aszCmd) > 0)
    {
        u32CmdNum += 1;
    }

    *pstCmd  = g_astProcCmd;
    *pu32Num = u32CmdNum;
    return HI_SUCCESS;
}

HI_U32 PMParseValue(HI_U8* pu8Value)
{
    if (strlen(pu8Value) < 2)
    {
        return (HI_U32)simple_strtoul(pu8Value, HI_NULL, 10);
    }
    else
    {
        if ((pu8Value[0] == '0') && ((pu8Value[1] == 'x') || (pu8Value[1] == 'X')))
        {
            return (HI_U32)simple_strtoul(pu8Value, HI_NULL, 16);
        }
        else
        {
            return (HI_U32)simple_strtoul(pu8Value, HI_NULL, 10);
        }
    }
}

/***********************************************************************/
/*entrance of function controled by the proc file system*/
/*CNcomment:ͨ��proc�ļ�ϵͳ���п��Ƶĺ������*/
static HI_S8 g_s8KeyLedType[5][16] = {
    "74HC164", "PT6961", "CT1642", "PT6964", "FD650"
};
static HI_S8 g_s8IRType[5][16] = {
    "NEC Simple", "TC9012", "NEC Full", "SONY", "RAW"
};
static HI_S8 g_s8DebugType[5][32] = {
    "No debug info",          "Save debug info to ram",
    "Show debug info to LED", "Save to ram & Show to LED",
    "Show debug info in serial port"
};

static HI_S32 PMProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U8 i;

    PROC_PRINT(p, "---------Hisilicon PM Info---------\n");
    PROC_PRINT(p,
               "Scene                   \t :%s\n"
               "Ethernet WakeUp         \t :%s\n"
               "USB WakeUp              \t :%s\n"
               "Display Mode            \t :%s\n"
               "Display Value           \t :0x%08x\n"
               "WakeUp TimeOut          \t :%u(ms)\n"
               "KeyLed Type             \t :%s\n"
               "KeyLed WakeUp Key       \t :%d\n"
               "IR Type                 \t :%s\n"
               "IR WakeUp Key Number    \t :%d\n",

               (g_u8FwEnable == 1) ? "Eth Forward" : "Standard",
               (g_u8EthWakeUpEnable == 1) ? "Enable" : "Disable",
               (g_u8UsbWakeUpMask == 1) ? "Enable" : "Disable",
               (dispMode == 0) ? "No Display" : ((dispMode == 1) ? "Display Number" : "Display Time"),
               dispvalue,
               timeVal,
               g_s8KeyLedType[kltype],
               keyVal,
               g_s8IRType[irtype],
               irpmocnum);

    for (i = 0; i < irpmocnum; i++)
    {
        PROC_PRINT(p, "IR WakeUp Key:          \t :High 32-bit(0x%x), Low 32-bit(0x%x)\n",
                   irValhigh[i], irVallow[i]);
    }

    PROC_PRINT(p,
               "Wake Up Reset             \t :%s \n"
               "Debug Mode                \t :%s \n"
               "Gpio wake up port         \t :%d \n"
               "Power off GPIO Number     \t :%d \n"
               "Power off GPIO Direction  \t :%d \n",

               (wdgon == 1) ? "Enable" : "Disable",
               g_s8DebugType[dbgmask],
               g_u32GpioPortVal,
               GpioValArray[0],
               GpioValArray[1]);

    return HI_SUCCESS;
}

static HI_S32 MCUDebugCtrl(HI_U32 u32Para1, HI_U32 u32Para2)
{
    if ((u32Para1 == 0) || (u32Para1 == 1))
    {
        wdgon = u32Para1;
    }
    else
    {
        HI_ERR_PM("plese set the value of Watchdog Status : 0x0(CLOSE) or 0x1(ON)\n");
    }

    if (u32Para2 <= 7)
    {
        dbgmask = u32Para2;
    }
    else
    {
        HI_ERR_PM("plese set the value of Debug Mode : between 0x0 and 0x7\n");
    }

    return HI_SUCCESS;
}

static HI_VOID MCUProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo reset=0/1 > /proc/hisi/msp/pm, wake up reset or not.\n"
        "echo debug=0/1/2/4> /proc/hisi/msp/pm, set debug level:\n"
        "\t0: %s;\n"
        "\t1: %s;\n"
        "\t2: %s;\n"
        "\t4: %s.\n",
        g_s8DebugType[0], g_s8DebugType[1], g_s8DebugType[2], g_s8DebugType[3]
        );

    return;
}

static HI_S32 PMProcWrite(struct file * file,
                          const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {
        0
    };
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    PM_CMD_DATA_S* pstCmd = HI_NULL;

    if (copy_from_user(ProcPara, buf, count))
    {
        return -EFAULT;
    }

    s32Ret = PMParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if (HI_SUCCESS != s32Ret)
    {
        goto err;
    }

    if (1 == u32CmdNum)
    {
        /* Only set reset mode */
        if (0 == HI_OSAL_Strncasecmp(PM_CMD_WAKEUPRESET, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            MCUDebugCtrl(PMParseValue(pstCmd[0].aszValue), dbgmask);
        }
        /* Only set debug level */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_FREQ, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            MCUDebugCtrl(wdgon, PMParseValue(pstCmd[0].aszValue));
        }
        /* Help */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_HELP, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            MCUProcHelper();
        }
        /* Enter smart stanby */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_ENTERSMARTSTANDBY, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            PMEnterSmartStandby(PMParseValue(pstCmd[0].aszValue));
        }
        /* Quit smart stanby */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_QUITSMARTSTANDBY, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            PMQuitSmartStandby();
        }
        /* Support 0xXXX 0xXXX command */
        else
        {
            MCUDebugCtrl(PMParseValue(pstCmd[0].aszCmd), PMParseValue(pstCmd[0].aszValue));
        }
    }
    else
    {
        goto err;
    }

    return count;

err:
    HI_DRV_PROC_EchoHelper("Invaid parameter.\n");
    MCUProcHelper();
    return count;
}

#ifdef HI_DVFS_CPU_SUPPORT
HI_S32 CPUDebugCtrl(HI_U32 u32Para1, HI_U32 u32Para2)
{
    HI_U32 u32CpuCurFreq = 0;

    HI_INFO_PM("\n xx u32Para1 = 0x%x, u32Para2 = 0x%x \n", u32Para1, u32Para2);

    if ((0 == u32Para1) && (0 == u32Para2))
    {
        HI_ERR_PM("plese set the valid value \n");
        return HI_SUCCESS;
    }

#ifdef HI_AVS_SUPPORT
    CPU_AVS_Enable(HI_FALSE);
 #endif

    if (0 == u32Para2)
    {
        hi_clk_set_rate(&mpu_ck, u32Para1);

        HI_INFO_PM("\n set rate2 = 0x%x finish \n", u32Para1);

        return HI_SUCCESS;
    }
    else if (0 == u32Para1)
    {
        cpu_volt_scale(u32Para2);

        HI_INFO_PM("\n set volt = 0x%x finish \n", u32Para2);

        return HI_SUCCESS;
    }

    u32CpuCurFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);

    if (u32Para1 > u32CpuCurFreq)
    {
        HI_INFO_PM("\n set volt = 0x%x finish \n", u32Para2);

        cpu_volt_scale(u32Para2);

        msleep(10);

        hi_clk_set_rate(&mpu_ck, u32Para1);

        HI_INFO_PM("\n set rate = 0x%x finish \n", u32Para1);
    }
    else
    {
        HI_INFO_PM("\n set rate = 0x%x before \n", u32Para1);
        hi_clk_set_rate(&mpu_ck, u32Para1);

        msleep(10);

        cpu_volt_scale(u32Para2);

        HI_INFO_PM("\n set volt = 0x%x finish \n", u32Para2);
    }

    return HI_SUCCESS;
}

static HI_VOID CPUProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo volt=1180 > /proc/hisi/msp/pm_cpu, set cpu volt in mv.\n"
        "echo freq=1000000 > /proc/hisi/msp/pm_cpu, set cpu freq in kHz.\n"
        "echo avs on/off > /proc/hisi/msp/pm_cpu, open/close cpu avs.\n"
        "echo freq=1000000 volt=1180 > /proc/hisi/msp/pm_cpu, set cpu volt and freq simultaneity.\n"
        );

    return;
}

static HI_S32 CPUProcWrite(struct file * file,
                           const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {
        0
    };
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    PM_CMD_DATA_S* pstCmd = HI_NULL;

    if (copy_from_user(ProcPara, buf, count))
    {
        return -EFAULT;
    }

    s32Ret = PMParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if (HI_SUCCESS != s32Ret)
    {
        goto err;
    }

    if (1 == u32CmdNum)
    {
        /* Only set CPU volt */
        if (0 == HI_OSAL_Strncasecmp(PM_CMD_VOLT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            CPUDebugCtrl(0, PMParseValue(pstCmd[0].aszValue));
        }
        /* Only set CPU freq */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_FREQ, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            CPUDebugCtrl(PMParseValue(pstCmd[0].aszValue), 0);
        }

#ifdef HI_AVS_SUPPORT
    else if (0 == HI_OSAL_Strncasecmp(PM_CMD_HPMOFFSET, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_u8CpuHpmOffset = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_AVS, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            /* CPU AVS ON */
            if (0 == HI_OSAL_Strncasecmp(PM_CMD_ON, pstCmd[0].aszValue, strlen(pstCmd[0].aszCmd)))
            {
                CPU_AVS_Enable(HI_TRUE);
            }
            /* CPU AVS OFF */
            else if (0 == HI_OSAL_Strncasecmp(PM_CMD_OFF, pstCmd[0].aszValue, strlen(pstCmd[0].aszCmd)))
            {
                CPU_AVS_Enable(HI_FALSE);
            }
        }
#endif

        /* Help */
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_HELP, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            CPUProcHelper();
        }
        /* Support 0xXXX 0xXXX command */
        else /*if (('0' == pstCmd[0].aszCmd[0]) && ('0' == pstCmd[0].aszValue[0]))*/
        {
            CPUDebugCtrl(PMParseValue(pstCmd[0].aszCmd), PMParseValue(pstCmd[0].aszValue));
        }
    }
    else if (2 == u32CmdNum)
    {
        if ((0 == HI_OSAL_Strncasecmp(PM_CMD_VOLT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
            && (0 == HI_OSAL_Strncasecmp(PM_CMD_FREQ, pstCmd[1].aszCmd, strlen(pstCmd[1].aszCmd))))
        {
            CPUDebugCtrl(PMParseValue(pstCmd[1].aszValue), PMParseValue(pstCmd[0].aszValue));
        }
        else if ((0 == HI_OSAL_Strncasecmp(PM_CMD_FREQ, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
                 && (0 == HI_OSAL_Strncasecmp(PM_CMD_VOLT, pstCmd[1].aszCmd, strlen(pstCmd[1].aszCmd))))
        {
            CPUDebugCtrl(PMParseValue(pstCmd[0].aszValue), PMParseValue(pstCmd[1].aszValue));
        }
        else
        {
            goto err;
        }
    }
    else
    {
        goto err;
    }

    return count;

err:
    HI_DRV_PROC_EchoHelper("Invaid parameter.\n");
    CPUProcHelper();
    return count;
}

void mpu_get_temperature(HI_S16 * ps16Temp)
{
    HI_U32 u32RegVal;
    HI_U8 i, j;
    HI_U32 u32TsensorAverage = 0;

#if defined(CHIP_TYPE_hi3798cv200_a)
    HI_REG_WRITE32(PERI_PMC10, 0x72);

    for (j = 0; j < 4; j++)
    {
        HI_REG_READ32(PERI_PMC12 + 0x4 * j, u32RegVal);
        for (i = 0; i < 2; i++)
        {
            u32TsensorAverage += ((u32RegVal >> (16 * i)) & 0x3ff);
        }
    }
#else
    HI_REG_WRITE32(PERI_PMC10, 0x07200000);

    for (j = 0; j < 2; j++)
    {
        HI_REG_READ32(PERI_PMC12 + 0x4 * j, u32RegVal);
        for (i = 0; i < 4; i++)
        {
            u32TsensorAverage += ((u32RegVal >> (8 * i)) & 0xff);
        }
    }
#endif

    u32TsensorAverage = (u32TsensorAverage / 8);

#if defined(CHIP_TYPE_hi3798cv200_a)
    *ps16Temp = ((u32TsensorAverage - 125) * 165 / 806) - 40;
#else
    *ps16Temp = (u32TsensorAverage * 180) / 255 - 40;
#endif

    return;
}

static HI_S32 CPUProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_U32 u32CpuVolt, u32CpuFreq;

    HI_U32 u32CpuAVSStatus = 0xff;
    HI_S16 s16Temperature;
    HI_U8 u8CpuHpmOffset = 0x0;

#ifdef HI_AVS_SUPPORT
    u32CpuAVSStatus = CPU_AVS_GetStatus();
    u8CpuHpmOffset = g_u8CpuHpmOffset;
#endif
    mutex_lock(&hi_dvfs_lock);
    u32CpuVolt = cur_cpu_volt;
    u32CpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);
    mutex_unlock(&hi_dvfs_lock);
	
    mpu_get_temperature(&s16Temperature);

	
#if defined(CHIP_TYPE_hi3716mv410)
	PROC_PRINT(p, "CPU: freq = %d(kHz)\n", u32CpuFreq);
#else
    PROC_PRINT(p, "CPU: freq = %d(kHz) volt = %d(mv)\n", u32CpuFreq, u32CpuVolt);
#endif
    PROC_PRINT(p, "CPU: AVS = %s, hpm offset = %d \n",
               (u32CpuAVSStatus != 0xff) ? ((u32CpuAVSStatus == 1) ? "On" : "Off") : "None", u8CpuHpmOffset);
    PROC_PRINT(p, "Tsensor: temperature = %d degree \n", s16Temperature);
    PROC_PRINT(p, "CPU: DVFS driver is %s \n", (cpu_dvfs_enable == HI_TRUE) ? "On" : "Off");

    return HI_SUCCESS;
}

#ifdef HI_TEMP_CTRL_CONFIG
static HI_VOID TempProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo tempctrl=1 > /proc/hisi/msp/pm_temp, enable temperature control\n"
        "echo tempdown=220 > /proc/hisi/msp/pm_temp, set down threshold temperature.\n"
        "echo tempup=200 > /proc/hisi/msp/pm_temp, set up threshold temperature.\n"
        "echo tempreboot=234 > /proc/hisi/msp/pm_temp, set reboot threshold temperature.\n"
        );

    return;
}

static HI_S32 TempProcRead(struct seq_file *p, HI_VOID *v)
{
    PROC_PRINT(p, "Temperature control is %s \n", (g_u8TempCtrlEnable == HI_TRUE) ? "On" : "Off");
    PROC_PRINT(p, "Temperature down threshold:  %d degree\n", g_s16TempDown);
    PROC_PRINT(p, "Temperature up threshold:  %d degree\n", g_s16TempUp);
    PROC_PRINT(p, "Temperature reboot threshold:  %d degree\n", g_s16TempReboot);

    return HI_SUCCESS;
}

static HI_S32 TempProcWrite(struct file * file,
                            const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {
        0
    };
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    PM_CMD_DATA_S* pstCmd = HI_NULL;

    if (copy_from_user(ProcPara, buf, count))
    {
        return -EFAULT;
    }

    s32Ret = PMParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if (HI_SUCCESS != s32Ret)
    {
        return count;
    }

    if (1 == u32CmdNum)
    {
        if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPCTRL, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_u8TempCtrlEnable = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPDOWN, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_s16TempDown = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPUP, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_s16TempUp = PMParseValue(pstCmd[0].aszValue);
        }
        else if (0 == HI_OSAL_Strncasecmp(PM_CMD_TEMPREBOOT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            g_s16TempReboot = PMParseValue(pstCmd[0].aszValue);
        }
        else
        {
            HI_DRV_PROC_EchoHelper("Invaid parameter.\n");
            TempProcHelper();
            return count;
        }
    }

    return count;
}

HI_S32 temperature_control_thread(void *Arg)
{
    HI_S16 s16Temperature;
    HI_U32 u32CpuFreq;
    HI_U32 u32OriCpuFreq = DEFAULT_INIT_FREQ;
    HI_U8 u8TimeInterval = 100;
    HI_U8 i;
    HI_BOOL bNeedReboot = HI_TRUE;
    HI_U32 u32RegVal;
    HI_U32 * pMcuStart = HI_NULL_PTR;

    printk("enter temperature_control_thread\n");

    /* Init tsensor */
  #if defined (CHIP_TYPE_hi3798cv200_a)
    HI_REG_WRITE32(PERI_PMC10, 0x72);
  #else
    HI_REG_WRITE32(PERI_PMC10, 0x07200000);
  #endif

    pMcuStart = ioremap_nocache(MCU_START_REG, 0x4);
    HI_REG_READ32(pMcuStart, u32RegVal);
    if (0 == u32RegVal)
    {
        c51_loadCode();
        HI_REG_WRITE32(pMcuStart, 0x1); //start MCU
    }

    iounmap(pMcuStart);

    g_s16TempUp = TEMP_UP;
    g_s16TempDown = TEMP_DOWN;
    g_s16TempReboot = TEMP_REBOOT;
    g_u8TempCtrlEnable = HI_TRUE;

    while (!kthread_should_stop())
    {
        msleep(u8TimeInterval);

        if (HI_FALSE == g_u8TempCtrlEnable)
        {
            continue;
        }

        mpu_get_temperature(&s16Temperature);

        if (s16Temperature < g_s16TempUp)
        {
            if (HI_FALSE == cpu_dvfs_enable)
            {
                for (i = 0; i < MAX_FREQ_NUM; i++)
                {
                    if (u32OriCpuFreq == cpu_freq_hpm_table[i].freq)
                    {
                        break;
                    }
                }

                if (i >= MAX_FREQ_NUM)
                {
                    continue;
                }

                u32CpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);
                if (u32CpuFreq > u32OriCpuFreq)
                {
                    hi_clk_set_rate(&mpu_ck, u32OriCpuFreq);
                    msleep(10);
                    cpu_volt_scale(cpu_freq_hpm_table[i].vsetting);
                }
                else
                {
                    cpu_volt_scale(cpu_freq_hpm_table[i].vsetting);
                    msleep(10);
                    hi_clk_set_rate(&mpu_ck, u32OriCpuFreq);
                }

                cpu_dvfs_enable = HI_TRUE;
            }

            bNeedReboot = HI_TRUE;
            u8TimeInterval = 100;
            continue;
        }
        else if ((g_s16TempDown <= s16Temperature) && (s16Temperature < g_s16TempReboot))
        {
            /* stop dvfs */
            if (HI_TRUE == cpu_dvfs_enable)
            {
                cpu_dvfs_enable = HI_FALSE;

                u32OriCpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);
                HI_INFO_PM("u32OriCpuFreq = %d \n", u32OriCpuFreq);
            }

            u32CpuFreq = (HI_U32)hi_clk_get_rate(&mpu_ck);

            if (u32CpuFreq == cpu_freq_hpm_table[0].freq)
            {
                continue;
            }
            else
            {
                /* set freq to low */
                hi_clk_set_rate(&mpu_ck, cpu_freq_hpm_table[0].freq);
                msleep(10);
                cpu_volt_scale(cpu_freq_hpm_table[0].vsetting);
            }
            
            bNeedReboot = HI_TRUE;
            u8TimeInterval = 20;
        }
        else if (s16Temperature >= g_s16TempReboot)
        {
            if (HI_TRUE == cpu_dvfs_enable)
            {
                /* stop dvfs */
                cpu_dvfs_enable = HI_FALSE;

                /* set freq to low */
                hi_clk_set_rate(&mpu_ck, cpu_freq_hpm_table[0].freq);
                msleep(10);
                cpu_volt_scale(cpu_freq_hpm_table[0].vsetting);

                /* in the process of start system, do not reboot system  */
                bNeedReboot = HI_FALSE;
            }
            else
            {
                if (HI_TRUE == bNeedReboot)
                {
                    HI_ERR_PM("Tsensor is extremly high, suspend system!!\n");
                    pMcuStart = ioremap_nocache(ENTER_FLAG_ADD, 0x4);
                    HI_REG_WRITE32(pMcuStart, 0x11111111);
                    iounmap(pMcuStart);
                }
            }
        }
    }

    return HI_SUCCESS;
}
#endif

HI_S32 COREDebugCtrl(HI_U32 u32Para1, HI_U32 u32Para2)
{
    if ((0 == u32Para1) && (0 == u32Para2))
    {
#if defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3798mv100)
        core_volt_scale(init_core_volt);
#else
        HI_ERR_PM("plese set the valid value \n");
#endif
        return HI_SUCCESS;
    }

    core_volt_scale(u32Para2);
    return HI_SUCCESS;
}

static HI_VOID COREProcHelper(HI_VOID)
{
    HI_DRV_PROC_EchoHelper(
        "echo volt=1180 > /proc/hisi/msp/pm_core, set core volt in mv.\n"
        );

    return;
}

static HI_S32 COREProcWrite(struct file * file,
                            const char __user * buf, size_t count, loff_t *ppos)
{
    HI_CHAR ProcPara[64] = {
        0
    };
    HI_S32 s32Ret;
    HI_U32 u32CmdNum = 0;
    PM_CMD_DATA_S* pstCmd = HI_NULL;

    if (copy_from_user(ProcPara, buf, count))
    {
        return -EFAULT;
    }

    s32Ret = PMParseCmd(ProcPara, count, &pstCmd, &u32CmdNum);
    if ((HI_SUCCESS == s32Ret) && (1 == u32CmdNum))
    {
        /* Set core volt */
        if (0 == HI_OSAL_Strncasecmp(PM_CMD_VOLT, pstCmd[0].aszCmd, strlen(pstCmd[0].aszCmd)))
        {
            COREDebugCtrl(0, PMParseValue(pstCmd[0].aszValue));
        }
        else
        {
            COREDebugCtrl(PMParseValue(pstCmd[0].aszCmd), PMParseValue(pstCmd[0].aszValue));
        }
    }
    else
    {
        HI_DRV_PROC_EchoHelper("Invaid parameter.\n");
        COREProcHelper();
    }

    return count;
}

static HI_S32 COREProcRead(struct seq_file *p, HI_VOID *v)
{
#if defined(CHIP_TYPE_hi3716mv410)
	 PROC_PRINT(p, "No Support!\n");
#else
    HI_U32 u32CpuVolt;

    u32CpuVolt = cur_core_volt;

    PROC_PRINT(p, "CORE: volt = %d(mv)\n", u32CpuVolt);
#endif
    return HI_SUCCESS;
}
#endif

/***********************************************************************/
HI_S32 PMOC_DRV_ModInit(HI_VOID)
{
    HI_S32 ret;
    DRV_PROC_ITEM_S *item;

    HI_INIT_MUTEX(&c51Sem);

    ret = HI_DRV_MODULE_Register(HI_ID_PM, "HI_PM", HI_NULL);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PM("c51 init fail ret = 0x%x!\n", ret);
        return ret;
    }

#ifdef HI_GPIO_LIGHT_SUPPORT
    ret = HI_DRV_MODULE_GetFunction(HI_ID_GPIO, (HI_VOID**)&s_pGpioFunc);
    if ((HI_SUCCESS != ret) || (s_pGpioFunc == HI_NULL))
    {
        HI_ERR_PM("Get GPIO function failed! \n");
        return HI_FAILURE;
    }
#endif

    item = HI_DRV_PROC_AddModule("pm", NULL, NULL);
    if (!item)
    {
        HI_ERR_PM("add proc module failed\n");
        return HI_FAILURE;
    }

    item->read  = PMProcRead;
    item->write = PMProcWrite;

#ifdef HI_DVFS_CPU_SUPPORT
    item = HI_DRV_PROC_AddModule("pm_cpu", NULL, NULL);
    if (!item)
    {
        HI_ERR_PM("add proc module failed\n");
        return HI_FAILURE;
    }

    item->read  = CPUProcRead;
    item->write = CPUProcWrite;

    item = HI_DRV_PROC_AddModule("pm_core", NULL, NULL);
    if (!item)
    {
        HI_ERR_PM("add proc module failed\n");
        return HI_FAILURE;
    }

    item->read  = COREProcRead;
    item->write = COREProcWrite;

    core_init_volt();

#ifdef HI_TEMP_CTRL_CONFIG
    item = HI_DRV_PROC_AddModule("pm_temp", NULL, NULL);
    if (!item)
    {
        HI_ERR_PM("add proc module failed\n");
        return HI_FAILURE;
    }

    item->read  = TempProcRead;
    item->write = TempProcWrite;
#endif

    mpu_init_volt();
    mpu_init_clocks();
    hi_cpufreq_init();

#ifdef HI_TEMP_CTRL_CONFIG
    pstTempCtrlThread = kthread_create(temperature_control_thread, NULL, "temperature_control");
    if (IS_ERR(pstTempCtrlThread))
    {
        HI_ERR_PM("create mcu watchdog thread failed.\n");
        return HI_FAILURE;
    }
    wake_up_process(pstTempCtrlThread);
#endif
#endif

    HI_OSAL_Snprintf(g_stPmDev.devfs_name, sizeof(g_stPmDev.devfs_name), UMAP_DEVNAME_PM);
    g_stPmDev.fops   = &stC51fopts;
    g_stPmDev.minor  = UMAP_MIN_MINOR_PM;
    g_stPmDev.owner  = THIS_MODULE;
    g_stPmDev.drvops = &c51_baseOps;
    if (HI_DRV_DEV_Register(&g_stPmDev) < 0)
    {
        HI_FATAL_PM("Unable to register pm dev\n");
        return HI_FAILURE;
    }

#ifdef MODULE
    HI_PRINT("Load hi_pmoc.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;
}

HI_VOID PMOC_DRV_ModExit(HI_VOID)
{
    HI_DRV_PROC_RemoveModule("pm");

#ifdef HI_DVFS_CPU_SUPPORT
    HI_DRV_PROC_RemoveModule("pm_cpu");
    HI_DRV_PROC_RemoveModule("pm_temp");
    HI_DRV_PROC_RemoveModule("pm_core");

    hi_cpufreq_exit();
    mpu_exit_clocks();
    mpu_deinit_volt();

#ifdef HI_TEMP_CTRL_CONFIG
    if (pstTempCtrlThread)
    {
        kthread_stop(pstTempCtrlThread);
        pstTempCtrlThread = HI_NULL;
    }
#endif
#endif

    HI_DRV_DEV_UnRegister(&g_stPmDev);

    (HI_VOID)HI_DRV_MODULE_UnRegister(HI_ID_PM);

    HI_INFO_PM(" PMOC_DRV_ModExit ok! \n");

    return;
}

#ifdef MODULE
module_init(PMOC_DRV_ModInit);
module_exit(PMOC_DRV_ModExit);
#endif

MODULE_LICENSE("GPL");
