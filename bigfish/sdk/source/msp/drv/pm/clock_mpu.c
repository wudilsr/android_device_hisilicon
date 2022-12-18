/*
 * hisilicon mpu clock management Routines
 *
 * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <mach/platform.h>
#include <linux/clkdev.h>
#include <asm/clkdev.h>
#include <mach/clock.h>
#include <mach/early-debug.h>
#include <linux/device.h>

#include "hi_reg_common.h"
#include "hi_drv_reg.h"
#include "hi_drv_pmoc.h"
#include "hi_dvfs.h"
#include "hi_drv_sys.h"

struct device *mpu_dev;

static DEFINE_SPINLOCK(mpu_clock_lock);

#if defined(HI_DONGLE_MODE_CRITICAL)
#define MAX_FREQ 800000
#elif defined(HI_DONGLE_MODE_LOW)
#define MAX_FREQ 1000000
#elif  defined(CHIP_TYPE_hi3798cv100) \
    || defined(CHIP_TYPE_hi3796cv100)
#define MAX_FREQ 1500000
#elif  defined(CHIP_TYPE_hi3716mv410)
#define MAX_FREQ 1000000
#elif  defined(CHIP_TYPE_hi3798cv200_a)
#define MAX_FREQ 1600000
#else
#define MAX_FREQ 1200000
#endif // end of defined(HI_DONGLE_MODE_CRITICAL)

#if defined(CHIP_TYPE_hi3719mv100) || defined(CHIP_TYPE_hi3718mv100)
#define CPU_HPM_F 0x1d4
#else
#define CPU_HPM_F 0x1b6
#endif //end of defined(CHIP_TYPE_hi3719mv100) || defined(CHIP_TYPE_hi3718mv100)

#if  defined(CHIP_TYPE_hi3716mv410) \
	|| defined(CHIP_TYPE_hi3716mv420)
#define MIN_FREQ 200000
#else
#define MIN_FREQ 400000
#endif
#define MEM_DELAY_PIN 0xf8a22180
#define MEM_DELAY_LOW_FREQ_VALUE 0x9aaaaf

#define CLOCK_24M (24 * 1000) //KHz

CPU_VF_S cpu_freq_hpm_table[MAX_FREQ_NUM] =
{
#if	   defined(CHIP_TYPE_hi3716mv410) \
		|| defined(CHIP_TYPE_hi3716mv420)
	{ 200000, HI_VDD_MPU_OPP11_HPM, HI_VDD_MPU_OPP11_VMIN, HI_VDD_MPU_OPP11_UV},
	{ 300000, HI_VDD_MPU_OPP12_HPM, HI_VDD_MPU_OPP12_VMIN, HI_VDD_MPU_OPP12_UV},
#endif
#if    defined (CHIP_TYPE_hi3716cv200)   \
        || defined (CHIP_TYPE_hi3716mv400)   \
        || defined (CHIP_TYPE_hi3718cv100)   \
        || defined (CHIP_TYPE_hi3719cv100)   \
        || defined (CHIP_TYPE_hi3718mv100)   \
        || defined (CHIP_TYPE_hi3719mv100)   \
        || defined (CHIP_TYPE_hi3798cv100)   \
        || defined (CHIP_TYPE_hi3796cv100)   \
        || defined(CHIP_TYPE_hi3716mv410) 	 \
		|| defined(CHIP_TYPE_hi3716mv420)	 \
        || defined(CHIP_TYPE_hi3798cv200_a)
    { 400000, HI_VDD_MPU_OPP1_HPM, HI_VDD_MPU_OPP1_VMIN, HI_VDD_MPU_OPP1_UV},
#endif
    { 600000, HI_VDD_MPU_OPP2_HPM, HI_VDD_MPU_OPP2_VMIN, HI_VDD_MPU_OPP2_UV},
#if    defined (CHIP_TYPE_hi3716cv200)   \
        || defined (CHIP_TYPE_hi3716mv400)   \
        || defined (CHIP_TYPE_hi3718cv100)   \
        || defined (CHIP_TYPE_hi3719cv100)   \
        || defined (CHIP_TYPE_hi3718mv100)   \
        || defined (CHIP_TYPE_hi3719mv100)   \
        || defined (CHIP_TYPE_hi3798cv100)   \
        || defined (CHIP_TYPE_hi3796cv100)   \
        || defined(CHIP_TYPE_hi3716mv410) 	 \
		|| defined(CHIP_TYPE_hi3716mv420)	 \
        || defined(CHIP_TYPE_hi3798cv200_a)
    { 800000, HI_VDD_MPU_OPP3_HPM, HI_VDD_MPU_OPP3_VMIN, HI_VDD_MPU_OPP3_UV},
#endif
    {1000000, HI_VDD_MPU_OPP4_HPM, HI_VDD_MPU_OPP4_VMIN, HI_VDD_MPU_OPP4_UV},
#if	   !defined(CHIP_TYPE_hi3716mv410)
    {1200000, HI_VDD_MPU_OPP5_HPM, HI_VDD_MPU_OPP5_VMIN, HI_VDD_MPU_OPP5_UV},
#endif
#if    defined(CHIP_TYPE_hi3798cv100) \
    || defined(CHIP_TYPE_hi3796cv100) \
    || defined(CHIP_TYPE_hi3798mv100) \
    || defined(CHIP_TYPE_hi3796mv100) \
    || defined(CHIP_TYPE_hi3798cv200_a)
    {1500000, HI_VDD_MPU_OPP6_HPM, HI_VDD_MPU_OPP6_VMIN, HI_VDD_MPU_OPP6_UV},
#endif
#if   defined(CHIP_TYPE_hi3798cv200_a)
    {1600000, HI_VDD_MPU_OPP7_HPM, HI_VDD_MPU_OPP7_VMIN, HI_VDD_MPU_OPP7_UV},
#endif
};


#ifdef HI_AVS_SUPPORT
unsigned int cur_cpu_hpm;
unsigned int cur_cpu_vmin;
HI_U8 g_u8CpuHpmOffset = 0;
#endif

static int cpu_init_hpm(unsigned long rate, unsigned int offset)
{
    unsigned int regval, div;

#ifdef HI_AVS_SUPPORT
    unsigned int i;
#endif

    div = (rate / 50000) - 1;

    if (div > 31)
    {
        HI_ERR_PM("\n Rate value is out of range \n");
        return -1;
    }

    /* hpm 2             */
    /* set time division */
    HI_REG_READ32(PERI_PMC30, regval);
    regval &= 0xffffffc0;
    regval |= div;
    HI_REG_WRITE32(PERI_PMC30, regval);

    /* set monitor period to 2ms */
    HI_REG_READ32(PERI_PMC33, regval);
    regval &= 0x00ffffff;
    regval |= (1 << 24);
    HI_REG_WRITE32(PERI_PMC33, regval);

    /* hpm enable */
    HI_REG_READ32(PERI_PMC30, regval);
    regval |= (1 << 24);
    HI_REG_WRITE32(PERI_PMC30, regval);

    /* hpm monitor enable */
    HI_REG_READ32(PERI_PMC30, regval);
    regval |= (1 << 26);
    HI_REG_WRITE32(PERI_PMC30, regval);

#ifdef HI_AVS_SUPPORT
    /* get default hpm record */
    for (i = 0; i < MAX_FREQ_NUM; i++)
    {
        if (rate == cpu_freq_hpm_table[i].freq)
        {
	        if (g_u8CpuHpmOffset != 0xff)
            {
                cur_cpu_hpm  = cpu_freq_hpm_table[i].hpmrecord + g_u8CpuHpmOffset + offset;
            }
	        else
	        {
 	    	    cur_cpu_hpm  = cpu_freq_hpm_table[i].hpmrecord + offset + 0x10;
	        }
            cur_cpu_vmin = cpu_freq_hpm_table[i].vmin;
            break;
        }
    }
#endif
    return 0;
}

#ifdef HI_AVS_SUPPORT
void core_init_hpm(void)
{
    unsigned int regval;
    unsigned int hpm_cfg, hpm_time_cfg;

    /* hpm 0 */
    hpm_cfg = PERI_PMC22;
    hpm_time_cfg = PERI_PMC25;

    /* clock is 200M, set time division to (200/50 - 1) */
    HI_REG_READ32(hpm_cfg, regval);
    regval &= 0xffffffc0;
    regval |= 3;
    HI_REG_WRITE32(hpm_cfg, regval);

    /* set monitor period to 2ms */
    HI_REG_READ32(hpm_time_cfg, regval);
    regval &= 0x00ffffff;
    regval |= (1 << 24);
    HI_REG_WRITE32(hpm_time_cfg, regval);

    /* hpm enable */
    HI_REG_READ32(hpm_cfg, regval);
    regval |= (1 << 24);
    HI_REG_WRITE32(hpm_cfg, regval);

    /* hpm monitor enable */
    HI_REG_READ32(hpm_cfg, regval);
    regval |= (1 << 26);
    HI_REG_WRITE32(hpm_cfg, regval);
}
#endif //end of HI_AVS_SUPPORT

static unsigned int crg96_ori = 0xffffffff;
struct clk mpu_ck = {
    .name   = "mpu_ck",
    .parent = NULL,
};

#if defined(CHIP_TYPE_hi3798cv200_a)
static unsigned int g_postdiv1;
static unsigned int g_postdiv2;
static unsigned int g_refdiv;
static int mpu_clk_set_rate(struct clk *clk, unsigned rate)
{
    unsigned int fbdiv;
    unsigned long flag;
    unsigned int offset = 0;

    U_PERI_CRG_PLL0 unTmpValuePLL0;
    U_PERI_CRG_PLL1 unTmpValuePLL1;
    U_PERI_CRG155 unTmpValueCRG155;
    U_PERI_CRG125 unTmpValueCRG125;
    U_PERI_CRG126 unTmpValueCRG126;
    U_PERI_CRG127 unTmpValueCRG127;
    U_PERI_CRG128 unTmpValueCRG128;
    U_PERI_CRG129 unTmpValueCRG129;

    unTmpValuePLL0.u32 = g_pstRegCrg->PERI_CRG_PLL0.u32;
    g_postdiv1 = (unTmpValuePLL0.bits.cpu_pll_cfg0_apb >> 24) & 0x7; //bit[26:24]
    g_postdiv2 = (unTmpValuePLL0.bits.cpu_pll_cfg0_apb >> 28) & 0x7; //bit[30:28]

    unTmpValuePLL1.u32 = g_pstRegCrg->PERI_CRG_PLL1.u32;
    g_refdiv = (unTmpValuePLL1.bits.cpu_pll_cfg1_apb >> 12) & 0x3f; //bit[17:12]

    /* do not set frac */
    fbdiv = (rate * g_postdiv1 * g_postdiv2 * g_refdiv) / CLOCK_24M;

    unTmpValueCRG155.u32 = g_pstRegCrg->PERI_CRG155.u32;
    /*TODO set ssmod param, should do it in boot register */
    unTmpValueCRG155.bits.cpll_ssmod_ctrl |= 0x1; //bit[0] to 1;enable clock
    unTmpValueCRG155.bits.cpll_ssmod_ctrl &= 0xffb; //bit[2] to 0;enable ssmod
    g_pstRegCrg->PERI_CRG155.u32 = unTmpValueCRG155.u32;

    /* set fbdiv of target cpll */
    unTmpValueCRG125.u32 = g_pstRegCrg->PERI_CRG125.u32;
    unTmpValueCRG125.bits.cpll_tune_int_cfg = fbdiv;
    g_pstRegCrg->PERI_CRG125.u32 = unTmpValueCRG125.u32;

    /* set frac of target cpll to 0 */
    unTmpValueCRG126.u32 = g_pstRegCrg->PERI_CRG126.u32;
    unTmpValueCRG126.bits.cpll_tune_frac_cfg = 0;
    g_pstRegCrg->PERI_CRG126.u32 = unTmpValueCRG126.u32;

    /* set integer of tune step */
    unTmpValueCRG127.u32 = g_pstRegCrg->PERI_CRG127.u32;
    unTmpValueCRG127.bits.cpll_tune_step_int = 1;
    g_pstRegCrg->PERI_CRG127.u32 = unTmpValueCRG127.u32;

    /* set fraction of tune setp */
    unTmpValueCRG128.u32 = g_pstRegCrg->PERI_CRG128.u32;
    unTmpValueCRG128.bits.cpll_tune_step_frac = 0;
    g_pstRegCrg->PERI_CRG128.u32 = unTmpValueCRG128.u32;

    /* enter ssmod */
    unTmpValueCRG129.u32 = g_pstRegCrg->PERI_CRG129.u32;
    unTmpValueCRG129.bits.cpll_tune_mode = 0x1;
    g_pstRegCrg->PERI_CRG129.u32 = unTmpValueCRG129.u32;

    /* begin one tune process */
    unTmpValueCRG129.u32 = g_pstRegCrg->PERI_CRG129.u32;
    unTmpValueCRG129.bits.cpll_tune_en = 0x0;
    g_pstRegCrg->PERI_CRG129.u32 = unTmpValueCRG129.u32;

    unTmpValueCRG129.u32 = g_pstRegCrg->PERI_CRG129.u32;
    unTmpValueCRG129.bits.cpll_tune_en = 0x1;
    g_pstRegCrg->PERI_CRG129.u32 = unTmpValueCRG129.u32;

    /* check whether pll switch is over */
    while (1)
    {
        if (0x0 == g_pstRegCrg->PERI_CRG173.bits.cpll_tune_busy)
        {
            break;
        }
        udelay(10);
    }

    /* After change clock, we need to reinitialize hpm */
    cpu_init_hpm(rate, offset);

    spin_lock_irqsave(&mpu_ck.spinlock, flag);
    clk->rate = rate;
    g_pstRegSysCtrl->SC_GEN26 = rate;
    spin_unlock_irqrestore(&mpu_ck.spinlock, flag);

    return 0;
}

static unsigned int mpu_clk_get_rate(void)
{
    unsigned int rate, fbdiv, reg_clk;

    reg_clk = g_pstRegCrg->PERI_CRG18.bits.cpu_freq_sel_cfg_crg;

    switch (reg_clk)
    {
    case 0:
    {
        g_postdiv1 = (g_pstRegCrg->PERI_CRG_PLL0.bits.cpu_pll_cfg0_apb >> 24) & 0x7;     //bit[26:24]
        g_postdiv2 = (g_pstRegCrg->PERI_CRG_PLL0.bits.cpu_pll_cfg0_apb >> 28) & 0x7;     //bit[30:28]
        g_refdiv = (g_pstRegCrg->PERI_CRG_PLL1.bits.cpu_pll_cfg1_apb >> 12) & 0x3f;     //bit[17:12]

        if (g_pstRegCrg->PERI_CRG173.bits.cpll_tune_int)
        {
            fbdiv = g_pstRegCrg->PERI_CRG173.bits.cpll_tune_int;
        }
        else
        {
            fbdiv = g_pstRegCrg->PERI_CRG_PLL1.bits.cpu_pll_cfg1_apb & 0xfff;
        }

        rate = (fbdiv * CLOCK_24M) / (g_postdiv1 * g_postdiv2 * g_refdiv);
        break;
    }
    case 1:
        rate = 600000;
        break;
    case 3:
        rate = 1500000;
        break;
    case 4:
        rate = 24000;
        break;
    case 5:
        rate = 1200000;
        break;
    case 6:
        rate = 400000;
        break;
    case 7:
        rate = 600000;
        break;
    default:
        HI_ERR_PM("mpu_clk_get_rate %dk not support\n", reg_clk);
        return 0;
    }

    return rate;
}

#else
static int mpu_clk_set_sel(unsigned long sel)
{
    U_PERI_CRG18 unTmpValue;

    HI_INFO_PM("enter %s\n", __FUNCTION__);

    unTmpValue.u32 = g_pstRegCrg->PERI_CRG18.u32;
    unTmpValue.bits.cpu_sw_begin_cfg = 0;
    g_pstRegCrg->PERI_CRG18.u32 = unTmpValue.u32;

    unTmpValue.bits.cpu_freq_sel_cfg_crg = sel;
    g_pstRegCrg->PERI_CRG18.u32 = unTmpValue.u32;

    unTmpValue.bits.cpu_sw_begin_cfg = 1;
    g_pstRegCrg->PERI_CRG18.u32 = unTmpValue.u32;

    return 0;
}

/*
 * mpu_clksel_set_rate() - program clock rate in hardware
 * @clk: struct clk * to program rate
 * @rate: target rate to program
 */
#define CHIP_TYPE_FF 1
#define CHIP_TYPE_TT 2
#define CHIP_TYPE_SS 3
static int mpu_clk_set_rate(struct clk *clk, unsigned rate)
{
    unsigned int sel, corner_type;
    unsigned int offset = 0;
    unsigned int rate_change_flag = 0;
    unsigned long flag;
    HI_CHIP_PACKAGE_TYPE_E enPackageType = HI_CHIP_PACKAGE_TYPE_BUTT;

    HI_INFO_PM("mpu_clk_set_rate %dk\n", rate);

    HI_DRV_SYS_GetChipPackageType(&enPackageType);
    corner_type = (g_pstRegSysCtrl->SC_GEN17 >> 24) & 0xff;

    if (1200000 == rate)
    {
        if (g_u8CpuHpmOffset != 0xff)
        {
	        if ((CHIP_TYPE_FF == corner_type) || (CHIP_TYPE_SS == corner_type)
            || (HI_CHIP_PACKAGE_TYPE_QFP_216 == enPackageType))
            {	
            	rate = 1000000;
	    	    rate_change_flag = 1;
            }
        }
        else
        {
            if (CHIP_TYPE_SS == corner_type)
            {
		        offset += 0x10;
	        }
        }
    }

    if (HI_CHIP_PACKAGE_TYPE_QFP_216 == enPackageType)
    {
        if ((600000 == rate) || (1200000 == rate))
        {
            offset += 0x10;
        }
        else
        {
            offset += 0x25;
        }
    }

    switch (rate)
    {
#if	   defined(CHIP_TYPE_hi3716mv410) \
		|| defined(CHIP_TYPE_hi3716mv420)
	case 1000000:
        sel = 0; // APLL
        break;
    case 800000:
        sel = 1;
        break;
    case 600000:
        sel = 2;
        break;
	case 1200000:
        sel = 3;
		break;
    case 24000:
        sel = 4;
        break;
    case 400000:
        sel = 5;
        break;
    case 300000:
        sel = 6;
        break;
    case 200000:
        sel = 7;
        break;
#else
    case 1000000:
        sel = 0; // APLL
        break;
    case 800000:
        sel = 1;
        break;
    case 1500000:
        sel = 3;
        break;
    case 24000:
        sel = 4;
        break;
    case 1200000:
        sel = 5;
        break;
    case 400000:
        sel = 6;
        break;
    case 600000:
        sel = 7;
        break;
#endif
    default:
        HI_ERR_PM("mpu_clk_set_rate %dk not support\n", rate);
        return -1;
    }

    HI_INFO_PM("mpu_clk_set_rate sel=%u\n", sel);

/* set mem delay pin */
#if  defined(CHIP_TYPE_hi3716cv200)   \
                || defined(CHIP_TYPE_hi3716mv400)   \
                || defined(CHIP_TYPE_hi3718cv100)   \
                || defined(CHIP_TYPE_hi3719cv100)   \
                || defined(CHIP_TYPE_hi3798cv100)   \
                || defined(CHIP_TYPE_hi3798cv100_a) \
                || defined(CHIP_TYPE_hi3796cv100)   \
                || defined(CHIP_TYPE_hi3796cv100_a) \
                || defined(CHIP_TYPE_hi3718mv100)   \
                || defined(CHIP_TYPE_hi3719mv100)   \
                || defined(CHIP_TYPE_hi3719mv100_a)
    if (rate <= 800000)
    {
        HI_REG_WRITE32(IO_ADDRESS(MEM_DELAY_PIN), MEM_DELAY_LOW_FREQ_VALUE);
    }
    else
    {
        if (0xffffffff != crg96_ori)
        {
            HI_REG_WRITE32(IO_ADDRESS(MEM_DELAY_PIN), crg96_ori);
        }
    }
#endif


    /* After change clock, we need to reinitialize hpm */
    cpu_init_hpm(rate, offset);

    if (1 == rate_change_flag)
    {
        rate = 1200000;
    }

    mpu_clk_set_sel(sel);

    spin_lock_irqsave(&mpu_ck.spinlock, flag);
    clk->rate = rate;
    g_pstRegSysCtrl->SC_GEN26 = rate;
    spin_unlock_irqrestore(&mpu_ck.spinlock, flag);

    return 0;
}

static unsigned int mpu_clk_get_rate(void)
{
    unsigned int reg_clk, val_clk;

    reg_clk = g_pstRegCrg->PERI_CRG18.bits.cpu_freq_sel_cfg_crg;

    switch (reg_clk)
        {
#if	   defined(CHIP_TYPE_hi3716mv410) \
		|| defined(CHIP_TYPE_hi3716mv420)
		case 0:
            val_clk = 1000000; // APLL
            break;
        case 1:
            val_clk = 800000;
            break;
        case 2:
            val_clk = 600000;
            break;
		case 3:
            val_clk = 1200000;
            break;
        case 4:
            val_clk = 24000;
            break;
        case 5:
            val_clk = 400000;
            break;
        case 6:
            val_clk = 300000;
            break;
        case 7:
            val_clk = 200000;
            break;
#else
        case 0:
            val_clk = 1000000; // APLL
            break;
        case 1:
            val_clk = 800000;
            break;
        case 3:
            val_clk = 1500000;
            break;
        case 4:
            val_clk = 24000;
            break;
        case 5:
            val_clk = 1200000;
            break;
        case 6:
            val_clk = 400000;
            break;
        case 7:
            val_clk = 600000;
            break;
#endif
        default:
            HI_ERR_PM("mpu_clk_get_rate %dk not support\n", reg_clk);
            return 0;
        }

    return val_clk;
}
#endif

static void mpu_clk_init(struct clk *clk)
{
    U_PERI_CRG18 unTmpValue;

    /* set cpu switch by software register */
    unTmpValue.u32 = g_pstRegCrg->PERI_CRG18.u32;
#if  defined(CHIP_TYPE_hi3716cv200)   \
    || defined(CHIP_TYPE_hi3716mv400)   \
    || defined(CHIP_TYPE_hi3718cv100)   \
    || defined(CHIP_TYPE_hi3719cv100)   \
    || defined(CHIP_TYPE_hi3798cv100)   \
    || defined(CHIP_TYPE_hi3798cv100_a) \
    || defined(CHIP_TYPE_hi3796cv100)   \
    || defined(CHIP_TYPE_hi3796cv100_a) \
    || defined(CHIP_TYPE_hi3718mv100)   \
    || defined(CHIP_TYPE_hi3719mv100)   \
    || defined(CHIP_TYPE_hi3719mv100_a)
    unTmpValue.bits.cpu_div_cfg_bypass = 0x1;
#endif
    unTmpValue.bits.cpu_begin_cfg_bypass = 0x1;
    g_pstRegCrg->PERI_CRG18.u32 = unTmpValue.u32;

    return;
}

static struct clk_ops mpu_clock_ops = {
    .set_rate = mpu_clk_set_rate,
    .init     = mpu_clk_init,
};

void set_mem_delay_pin(void)
{
    HI_U32 u32RegVal;
    HI_U16 u16HpmCode, u16HpmCodeAverage;

    HI_REG_READ32(PERI_PMC31, u32RegVal);
    u16HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
    u16HpmCodeAverage = u16HpmCode;
    u16HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
    u16HpmCodeAverage += u16HpmCode;

    HI_REG_READ32(PERI_PMC32, u32RegVal);
    u16HpmCode = (u32RegVal & HPM_PC_RECORED_MASK);
    u16HpmCodeAverage += u16HpmCode;
    u16HpmCode = ((u32RegVal >> 12) & HPM_PC_RECORED_MASK);
    u16HpmCodeAverage += u16HpmCode;

    u16HpmCodeAverage = (u16HpmCodeAverage / 4);
    HI_INFO_PM("\n ###################cpu u16HpmCodeAverage  = 0x%x \n", u16HpmCodeAverage);

    /* if this chip is fff, then change mem delay pin in high freq. */
    if (u16HpmCodeAverage > CPU_HPM_F)
    {
        crg96_ori = MEM_DELAY_LOW_FREQ_VALUE;
    }
    else
    {
        HI_REG_READ32(IO_ADDRESS(MEM_DELAY_PIN), crg96_ori);
    }
}

void  mpu_init_clocks(void)
{
    HI_INFO_PM("Enter %s\n", __FUNCTION__);
    mpu_ck.rate = mpu_clk_get_rate();
    if (0 == mpu_ck.rate)
    {
        mpu_ck.rate = DEFAULT_INIT_FREQ;
    }

    mpu_ck.ops  = &mpu_clock_ops;
    mpu_ck.max_rate = MAX_FREQ;
    mpu_ck.min_rate = MIN_FREQ;

    mpu_ck.spinlock = mpu_clock_lock;
    clk_init(&mpu_ck);

    mpu_clk_set_rate(&mpu_ck, mpu_ck.rate);

    /* delay 8 ms to wait hpm ok */
    msleep(8);
    set_mem_delay_pin();

    return;
}

void  mpu_resume_clocks(void)
{
    mpu_clk_set_rate(&mpu_ck, mpu_ck.rate);

    return;
}

void  mpu_exit_clocks(void)
{
    clk_exit(&mpu_ck);
}
