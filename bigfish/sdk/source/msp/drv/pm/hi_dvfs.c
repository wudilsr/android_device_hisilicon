/*
 * hisilicon DVFS Management Routines
 *
 * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
 */

#include <linux/err.h>
#include <linux/spinlock.h>
#include <linux/plist.h>
#include <linux/slab.h>
#include "opp.h"
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/io.h>
#include <mach/platform.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <mach/clock.h>
#include <linux/kthread.h>

#include "hi_reg_common.h"
#include "hi_drv_reg.h"
#include "hi_dvfs.h"
#include "hi_drv_pmoc.h"
#include "drv_i2c_ext.h"
#include "hi_drv_module.h"
#include "hi_kernel_adapt.h"

extern struct clk mpu_ck;

#ifndef HI_PMU_DEVICE_SELECT

#if defined(CHIP_TYPE_hi3719mv100) \
    || defined(CHIP_TYPE_hi3718mv100)
#define CPU_VMAX 1400 /*mv*/
#define CPU_VMIN 900 /*mv*/
#define CORE_VMAX 1205 /*mv*/
#define CORE_VMIN 900 /*mv*/
#elif  defined(CHIP_TYPE_hi3798cv100) \
    || defined(CHIP_TYPE_hi3796cv100) \
    || defined(CHIP_TYPE_hi3798mv100) \
    || defined(CHIP_TYPE_hi3796mv100)
#define CPU_VMAX 1495 /*mv*/
#define CPU_VMIN 920 /*mv*/
#define CORE_VMAX 1315 /*mv*/
#define CORE_VMIN 900 /*mv*/
#elif  defined(CHIP_TYPE_hi3716mv410) \
	 || defined(CHIP_TYPE_hi3716mv420)

#define CPU_VMAX 1400 /*mv*///0.9-1.38
#define CPU_VMIN 900 /*mv*/
#define CORE_VMAX 1315 /*mv*///0.9 1.25
#define CORE_VMIN 900 /*mv*/
#elif  defined(CHIP_TYPE_hi3798cv200_a)
#define CPU_VMAX 1150 /*mv*/
#define CPU_VMIN 750 /*mv*/
#define CORE_VMAX 1150 /*mv*/
#define CORE_VMIN 750 /*mv*/
#else
#define CPU_VMAX 1315 /*mv*/
#define CPU_VMIN 900 /*mv*/
#define CORE_VMAX 1205 /*mv*/
#define CORE_VMIN 900 /*mv*/
#endif

#define PWM_STEP 5 /*mv*/
#define PWM_CLASS 2
#define CPU_DEVICE 0
#define CORE_DEVICE 1
#else
#define MULTI_NUMBER (12)
#define CPU_VMAX 1500 /*mv*/
#define CPU_VMIN 870 /*mv*/
#define PMU_I2cNum 0
#define PMU_DeviceAddress 0x90
#define CORE_Address 0x1
#define GPU_Address 0x2
#define CPU_Address 0x3
static I2C_EXT_FUNC_S *s_pI2CFunc = HI_NULL;
#define PMU_STEP 10 /*mv*/
#define CORE_VMAX 1210 /*mv*/
#define CORE_VMIN 900 /*mv*/
#endif //end of HI_PMU_DEVICE_SELECT

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
#define PWM_CPU PERI_PMC7
#else
#define PWM_CPU PERI_PMC6
#endif

#if defined(CHIP_TYPE_hi3798cv100) || defined(CHIP_TYPE_hi3796cv100)
#define PWM_CORE PERI_PMC8
#elif defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
#define PWM_CORE PERI_PMC6
#else
#define PWM_CORE PERI_PMC7
#endif

#define AVS_STEP 10 /*mv*/
#define AVS_INTERVAL 10 /*ms*/

unsigned long cur_cpu_volt  = 1300;
unsigned long cur_core_volt = 1150;
unsigned long init_core_volt = 1150;

#ifdef HI_AVS_SUPPORT
static struct task_struct *pstAVSThread = HI_NULL;
HI_DECLARE_MUTEX(g_CPUAVSMutex);
static unsigned int cur_cpu_vmax;
static unsigned int cpu_avs_enable = HI_TRUE;
#endif

int core_volt_scale(unsigned int volt);

DEFINE_MUTEX(hi_dvfs_lock);

/**
 * struct hi_dvfs_info - The per vdd dvfs info
 * @user_lock:  spinlock for plist operations
 *
 * This is a fundamental structure used to store all the required
 * DVFS related information for a vdd.
 */
struct hi_dvfs_info
{
    unsigned long volt;
    unsigned long new_freq;
    unsigned long old_freq;
};

#ifndef HI_PMU_DEVICE_SELECT
static void device_volt_scale(unsigned char device, unsigned int volt)
{
    unsigned int pwm_reg;
    unsigned int period, duty, v, tmp;
    unsigned int vmax, vmin, pwc, pws;

    if (CPU_DEVICE == device)
    {
        pwm_reg = PWM_CPU;
        vmax = CPU_VMAX;
        vmin = CPU_VMIN;
    }
    else if (CORE_DEVICE == device)
    {
        pwm_reg = PWM_CORE;
        vmax = CORE_VMAX;
        vmin = CORE_VMIN;
    }
    else
    {
        HI_ERR_PM("Not supprot this device .\n");
        return;
    }

    pwc = PWM_CLASS;
    pws = PWM_STEP;

    period = (((vmax - vmin) * pwc) / pws) + 1;
    duty = (((vmax - volt) * pwc) / pws) + 1;

    HI_REG_READ32(pwm_reg, v);
    tmp = PWM_PERIOD_MASK;
    v &= ~tmp;
    v |= period;

    tmp = PWM_DUTY_MASK;
    v &= ~tmp;
    v |= duty << 16;
    HI_REG_WRITE32(pwm_reg, v);

    return;
}
#else
static void device_volt_scale(unsigned char device_addr,  unsigned char pmu_reg)
{
    HI_S32 s32Ret;
    HI_U8 u8CurReg = 0;
    HI_U8 u8Tmp;

    /* To avoid adjust volt too fast, do it every 48mv once. */
    do
    {
        if (s_pI2CFunc->pfnI2cRead)
        {
            s32Ret = (s_pI2CFunc->pfnI2cRead)(PMU_I2cNum, PMU_DeviceAddress, device_addr, 1, &u8CurReg, 1);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_PM("call HI_I2C_Read failed.\n");
                return;
            }
        }

        u8Tmp = (u8CurReg > pmu_reg) ? (u8CurReg - pmu_reg) : (pmu_reg - u8CurReg);

        HI_INFO_PM("\n u8CurReg = 0x%x, pmu_reg = 0x%x  delta = 0x%x\n", u8CurReg, pmu_reg, u8Tmp);

        if (u8Tmp > 0x10)
        {
            if (u8CurReg > pmu_reg)
            {
                u8CurReg -= 0x10;
            }
            else
            {
                u8CurReg += 0x10;
            }
        }
        else
        {
            u8CurReg = pmu_reg;
        }

        if (s_pI2CFunc->pfnI2cWrite)
        {
            s32Ret = (s_pI2CFunc->pfnI2cWrite)(PMU_I2cNum, PMU_DeviceAddress, device_addr, 1, &u8CurReg, 1);
            if (s32Ret != HI_SUCCESS)
            {
                HI_ERR_PM("call HI_I2C_Write failed.\n");
                return;
            }
        }

        mdelay(1);
    } while (u8CurReg != pmu_reg);

    return;
}
#endif //end of HI_PMU_DEVICE_SELECT


int cpu_volt_scale(unsigned int volt)
{
#if	defined(CHIP_TYPE_hi3716mv410)
	return 0;
#endif
#ifndef HI_PMU_DEVICE_SELECT
    HI_INFO_PM("%s,volt=%d\n", __FUNCTION__, volt);

    if (volt > CPU_VMAX)
    {
        volt = CPU_VMAX;
        HI_ERR_PM("volt is out of range! Force it to vmax\n");
    }
    else if (volt < CPU_VMIN)
    {
        HI_ERR_PM("volt is out of range! Do not change volt \n");
        return 0;
    }

    device_volt_scale(CPU_DEVICE, volt);
#else
    HI_U32 tmp;
    HI_U8 u8VoltReg;

    if (volt > ((CPU_VMAX * MULTI_NUMBER) / PMU_STEP))
    {
        volt = (CPU_VMAX * MULTI_NUMBER) / PMU_STEP;
        HI_ERR_PM("volt is out of range! Force it to vmax\n");
    }
    else if (volt < ((CPU_VMIN * MULTI_NUMBER) / PMU_STEP))
    {
        HI_ERR_PM("volt is out of range! Do not change volt \n");
        return 0;
    }

    /* we change the step from 10 to 12 by changing hardware */
    tmp = ((volt * PMU_STEP) / MULTI_NUMBER) - CPU_VMIN;
    u8VoltReg = (HI_U8)((tmp / PMU_STEP) << 2);

    HI_INFO_PM("_volt_scale,volt=%d, u8VoltReg = 0x%x tmp = %d \n", volt, u8VoltReg, tmp);

    device_volt_scale(CPU_Address, u8VoltReg);
#endif

    cur_cpu_volt = volt;

    return 0;
}

#ifdef HI_AVS_SUPPORT
unsigned int CPU_AVS_GetStatus(void)
{
    return cpu_avs_enable;
}

void CPU_AVS_Enable(unsigned int enable)
{
    cpu_avs_enable = enable;

    HI_INFO_PM("\n CPU_AVS_Enable = %d \n", enable);
}

extern unsigned int cur_cpu_hpm;
extern unsigned int cur_cpu_vmin;

HI_S32 cpu_avs_thread(void *Arg)
{
    HI_U16 u16HpmCode, u16HpmCodeAverage = 0;
    HI_U32 u32RegVal;
    HI_S16 s16HpmDelta;
    HI_U8 i;
    HI_S32 ret;

    while (!kthread_should_stop())
    {
        msleep(AVS_INTERVAL);

        if (HI_FALSE == cpu_avs_enable)
        {
            continue;
        }

        /* read current code */
        u16HpmCodeAverage = 0;
        for (i = 0; i < 2; i++)
        {
            HI_REG_READ32(PERI_PMC31, u32RegVal);
            u16HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
            u16HpmCodeAverage += u16HpmCode;
            u16HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
            u16HpmCodeAverage += u16HpmCode;

            HI_REG_READ32(PERI_PMC32, u32RegVal);
            u16HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
            u16HpmCodeAverage += u16HpmCode;
            u16HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
            u16HpmCodeAverage += u16HpmCode;

            msleep(4);
        }

        u16HpmCodeAverage = u16HpmCodeAverage / (i * 4);

        s16HpmDelta = u16HpmCodeAverage - cur_cpu_hpm;

        HI_INFO_PM("\n show u16HpmCodeMin = 0x%x cur_cpu_hpm = 0x%x \n", u16HpmCodeAverage, cur_cpu_hpm);

        /* compare code value */
        if (s16HpmDelta <= 0x1)
        {
            ret = down_interruptible(&g_CPUAVSMutex);
            if (ret)
            {
                HI_ERR_PM("lock g_CPUAVSMutex error.\n");
                return ret;
            }

            /* up 10mv */
            if (cur_cpu_volt < cur_cpu_vmax)
            {
                cpu_volt_scale(cur_cpu_volt + AVS_STEP);
            }

            up(&g_CPUAVSMutex);
        }
        else if (s16HpmDelta >= 0xa)
        {
            ret = down_interruptible(&g_CPUAVSMutex);
            if (ret)
            {
                HI_ERR_PM("lock g_CPUAVSMutex error.\n");
                return ret;
            }

            /*down 10mv */
            if (cur_cpu_volt > cur_cpu_vmin)
            {
                cpu_volt_scale(cur_cpu_volt - AVS_STEP);
            }

            up(&g_CPUAVSMutex);
        }
        else
        {
            msleep(10 * AVS_INTERVAL);
        }
    }

    return HI_SUCCESS;
}

#endif //end of HI_AVS_SUPPORT

unsigned int mpu_get_volt(void)
{
    unsigned int v;

    HI_REG_READ32(PWM_CPU, v);
    v = (v | 0xffff) >> 16;
    v = CPU_VMAX - ((v - 1) * PWM_STEP) / PWM_CLASS;

    return v;
}

void mpu_init_volt(void)
{
#ifndef HI_PMU_DEVICE_SELECT
    /* get cpu volt set in boot */
    cur_cpu_volt = mpu_get_volt();
#else
    HI_S32 s32Ret;

    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_I2C, (HI_VOID**)&s_pI2CFunc);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PM("Get I2C function err:%#x!\n", s32Ret);
        return;
    }

    if (!s_pI2CFunc || !s_pI2CFunc->pfnI2cWrite || !s_pI2CFunc->pfnI2cRead)
    {
        HI_ERR_PM("I2C not found\n");
        return;
    }
#endif

#ifdef HI_AVS_SUPPORT
    pstAVSThread = kthread_create(cpu_avs_thread, NULL, "cpu_avs");
    if (IS_ERR(pstAVSThread))
    {
        HI_ERR_PM("create avs thread failed.\n");
        return;
    }
    wake_up_process(pstAVSThread);
#endif

    return;
}

void mpu_deinit_volt(void)
{
#ifdef HI_AVS_SUPPORT
    if (pstAVSThread)
    {
        kthread_stop(pstAVSThread);
        pstAVSThread = HI_NULL;
    }
#endif
}

int core_volt_scale(unsigned int volt)
{
#ifndef HI_PMU_DEVICE_SELECT

    HI_INFO_PM("%s,volt=%d\n", __FUNCTION__, volt);

    device_volt_scale(CORE_DEVICE, volt);
 #else
    HI_U8 u8VoltReg;

    /* TODO: check input is in the range */

    /* transfer volt from 1100mv to 1150mv */
    /* step 10mv */
    u8VoltReg = ((((volt * 110) / 115) - CORE_VMIN) / PMU_STEP) << 2;

    HI_INFO_PM("_core_volt_scale,volt=%d, u8VoltReg = 0x%x \n", volt, u8VoltReg);

    device_volt_scale(CORE_Address, u8VoltReg);
 #endif

    cur_core_volt = volt;

    return 0;
}

void core_init_volt(void)
{
#ifndef HI_PMU_DEVICE_SELECT
    unsigned int v;

    /* get core volt set in boot */
    HI_REG_READ32(PWM_CORE, v);
    v = (v | 0xffff) >> 16;
    cur_core_volt = CORE_VMAX - ((v - 1) * PWM_STEP) / PWM_CLASS;
    init_core_volt = cur_core_volt;
#endif

    return;
}

/**
 * _dvfs_scale() : Scale the devices associated with a voltage domain
 *
 * Returns 0 on success else the error value.
 */
static int _dvfs_scale(struct device *target_dev, struct hi_dvfs_info *tdvfs_info)
{
    struct clk * clk;
    int ret;

    HI_INFO_PM("%s rate=%ld\n", __FUNCTION__, tdvfs_info->new_freq);

    clk = &mpu_ck;
    if (tdvfs_info->new_freq == tdvfs_info->old_freq)
    {
        return 0;
    }
    else if (tdvfs_info->new_freq > tdvfs_info->old_freq)
    {
#ifdef HI_AVS_SUPPORT
        CPU_AVS_Enable(HI_FALSE);
        ret = down_interruptible(&g_CPUAVSMutex);
        if (ret)
        {
            HI_ERR_PM("lock g_CPUAVSMutex error.\n");
            return ret;
        }
#endif
        ret = cpu_volt_scale(tdvfs_info->volt);
        if (ret)
        {
            HI_ERR_PM("%s: scale volt to %ld falt\n",
                      __func__, tdvfs_info->volt);
        }

#ifdef HI_AVS_SUPPORT
        up(&g_CPUAVSMutex);
#endif

        msleep(10);
        ret = clk_set_rate(clk, tdvfs_info->new_freq);
        if (ret)
        {
            HI_ERR_PM("%s: scale freq to %ld falt\n",
                      __func__, tdvfs_info->new_freq);
            return ret;
        }
    }
    else
    {
        ret = clk_set_rate(clk, tdvfs_info->new_freq);
        if (ret)
        {
            HI_ERR_PM("%s: scale freq to %ld falt\n",
                      __func__, tdvfs_info->new_freq);
            return ret;
        }

        msleep(10);

#ifdef HI_AVS_SUPPORT
        CPU_AVS_Enable(HI_FALSE);
        ret = down_interruptible(&g_CPUAVSMutex);
        if (ret)
        {
            HI_ERR_PM("lock g_CPUAVSMutex error.\n");
            return ret;
        }
#endif
        ret = cpu_volt_scale(tdvfs_info->volt);
        if (ret)
        {
            HI_ERR_PM("%s: scale volt to %ld falt\n",
                      __func__, tdvfs_info->volt);
        }

#ifdef HI_AVS_SUPPORT
        up(&g_CPUAVSMutex);
#endif
    }

#ifdef HI_AVS_SUPPORT
    if ((tdvfs_info->new_freq > 400000) && (tdvfs_info->new_freq < 1500000))
    {
        /* save basic cpu volt as the max volt of AVS */
        cur_cpu_vmax = tdvfs_info->volt;

        /* wait for hpm test */
        msleep(8);
        CPU_AVS_Enable(HI_TRUE);
    }
#endif

    return ret;
}

/**
 * hi_device_scale() - Set a new rate at which the devices is to operate
 * @rate:   the rnew rate for the device.
 *
 * This API gets the device opp table associated with this device and
 * tries putting the device to the requested rate and the voltage domain
 * associated with the device to the voltage corresponding to the
 * requested rate. Since multiple devices can be assocciated with a
 * voltage domain this API finds out the possible voltage the
 * voltage domain can enter and then decides on the final device
 * rate.
 *
 * Return 0 on success else the error value
 */
int hi_device_scale(struct device *target_dev, unsigned long old_freq, unsigned long new_freq)
{
    struct opp *opp;
    unsigned long volt, freq = new_freq;
    struct hi_dvfs_info dvfs_info;

    int ret = 0;

    HI_INFO_PM("hi_device_scale,oldfreq = %ld,newfreq = %ld\n", old_freq, new_freq);

    /* Lock me to ensure cross domain scaling is secure */
    mutex_lock(&hi_dvfs_lock);
    rcu_read_lock();

    opp = opp_find_freq_ceil(target_dev, &freq);

    /* If we dont find a max, try a floor at least */
    if (IS_ERR(opp))
    {
        opp = opp_find_freq_floor(target_dev, &freq);
    }

    if (IS_ERR(opp))
    {
        rcu_read_unlock();
        HI_ERR_PM("%s: Unable to find OPP for freq%ld\n",
                  __func__, freq);
        ret = -ENODEV;
        goto out;
    }

    volt = opp_get_voltage(opp);

    rcu_read_unlock();

    dvfs_info.old_freq = old_freq;

    dvfs_info.new_freq = freq;

    dvfs_info.volt = volt;

    /* Do the actual scaling */
    ret = _dvfs_scale( target_dev, &dvfs_info);

    if (ret)
    {
        HI_ERR_PM("%s: scale failed %d[f=%ld, v=%ld]\n",
                  __func__, ret, freq, volt);

        /* Fall through */
    }

    /* Fall through */
out:
    mutex_unlock(&hi_dvfs_lock);
    return ret;
}
