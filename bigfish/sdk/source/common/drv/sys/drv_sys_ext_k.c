/******************************************************************************

  Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sys_ext_k.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2006/02/09
  Description   :
******************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <mach/hardware.h>
#include <linux/sched.h>
#include <linux/math64.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_reg_common.h"
#include "hi_drv_sys.h"
#include "hi_drv_reg.h"
#include "hiuapi.h"

#define DIV_NS_TO_MS  1000000
#define HI_OTP_BASE_ADDR  0xf8ab0000

HI_VOID HI_DRV_SYS_GetChipVersion(HI_CHIP_TYPE_E *penChipType, HI_CHIP_VERSION_E *penChipVersion)
{
    HI_CHIP_TYPE_E      ChipType    = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E   ChipVersion = HI_CHIP_VERSION_BUTT;

    /* penChipType or penChipVersion maybe NULL, but not both */
    if (HI_NULL == penChipType && HI_NULL == penChipVersion)
    {
        HI_ERR_SYS("invalid input parameter\n");
        return;
    }

#if    defined(CHIP_TYPE_hi3716cv200)   \
    || defined(CHIP_TYPE_hi3716mv400)   \
    || defined(CHIP_TYPE_hi3718cv100)   \
    || defined(CHIP_TYPE_hi3719cv100)
    if (0x37160200 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE.bits.chip_id)
        {
            case 0x8:
                ChipType    = HI_CHIP_TYPE_HI3719C;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
            case 0x10:
                ChipType    = HI_CHIP_TYPE_HI3718C;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
            case 0x1c:
            case 0x1d:
                ChipType    = HI_CHIP_TYPE_HI3716M;
                ChipVersion = HI_CHIP_VERSION_V400;
                break;
            default:
                ChipType    = HI_CHIP_TYPE_HI3716C;
                ChipVersion = HI_CHIP_VERSION_V200;
                break;
        }
    }
#elif defined(CHIP_TYPE_hi3718mv100) || defined(CHIP_TYPE_hi3719mv100)
    if (0x37190100 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE.bits.chip_id)
        {
            case 0x4:
            case 0x5:
                ChipType    = HI_CHIP_TYPE_HI3718M;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
            default:
                ChipType    = HI_CHIP_TYPE_HI3719M;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
        }
    }
#elif defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
    if (0x19050100 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE.bits.chip_id)
        {
            case 0x18:
                if (g_pstRegSysCtrl->SC_SYS_DBG0.bits.chip_vision)
                {
                    ChipType    = HI_CHIP_TYPE_HI3796C;
                    ChipVersion = HI_CHIP_VERSION_V100;
                }
                break;
            case 0x1C:
                if (g_pstRegSysCtrl->SC_SYS_DBG0.bits.chip_vision)
                {
                    ChipType    = HI_CHIP_TYPE_HI3798C;
                    ChipVersion = HI_CHIP_VERSION_V100;
                }
                break;
            default:
                ChipType    = HI_CHIP_TYPE_HI3796C;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
        }
    }
#elif defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    if (0x37980100 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
        {
            case 0x0:
                ChipType    = HI_CHIP_TYPE_HI3796M;
                ChipVersion = HI_CHIP_VERSION_V100;
                break;
            default:
                ChipType    = HI_CHIP_TYPE_HI3798M;
                ChipVersion = HI_CHIP_VERSION_V100;
        }
    }
#elif defined(CHIP_TYPE_hi3798cv200_a)
    if (0x20281000 == g_pstRegSysCtrl->SC_SYSID)
    {
        ChipType    = HI_CHIP_TYPE_HI3798C_A;
        ChipVersion = HI_CHIP_VERSION_V200;
    }
#endif

    if (penChipType)
    {
        *penChipType = ChipType;
    }

    if (penChipVersion)
    {
        *penChipVersion = ChipVersion;
    }
}

HI_S32 HI_DRV_SYS_GetChipPackageType(HI_CHIP_PACKAGE_TYPE_E *penPackageType)
{
    if (HI_NULL == penPackageType)
    {
        HI_ERR_SYS("invalid input parameter\n");
        return HI_FAILURE;
    }

#if    defined(CHIP_TYPE_hi3716cv200)   \
    || defined(CHIP_TYPE_hi3716mv400)   \
    || defined(CHIP_TYPE_hi3718cv100)   \
    || defined(CHIP_TYPE_hi3719cv100)
    if (0x37160200 == g_pstRegSysCtrl->SC_SYSID)
    {
        *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_23_23;
        return HI_SUCCESS;
    }
#elif defined(CHIP_TYPE_hi3718mv100) || defined(CHIP_TYPE_hi3719mv100)
    if (0x37190100 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE.bits.chip_id)
        {
            case 0x4:
            case 0x5:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_QFP_216;
                return HI_SUCCESS;

            default:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_23_23;
                return HI_SUCCESS;
        }
    }
#elif defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
    if (0x19050100 == g_pstRegSysCtrl->SC_SYSID)
    {
        *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_23_23;
        return HI_SUCCESS;
    }
#elif defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    if (0x37980100 == g_pstRegSysCtrl->SC_SYSID)
    {
        switch (g_pstRegPeri->PERI_SOC_FUSE_0.bits.chip_id)
        {
            case 0x0:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_23_23;
                return HI_SUCCESS;
            case 0x1:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_19_19;
                return HI_SUCCESS;
            case 0x3:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_15_15;
                return HI_SUCCESS;
            case 0x7:
                *penPackageType = HI_CHIP_PACKAGE_TYPE_QFP_216;
                return HI_SUCCESS;
            default:
                HI_ERR_SYS("get package type error!\n");
                return HI_FAILURE;
        }
    }
#elif defined(CHIP_TYPE_hi3798cv200_a)
    if (0x20281000 == g_pstRegSysCtrl->SC_SYSID)
    {
        *penPackageType = HI_CHIP_PACKAGE_TYPE_BGA_31_31;
        return HI_SUCCESS;
    }
#else
    #error "Unkown chip type and package type!"
#endif
    return HI_FAILURE;
}

HI_S32 HI_DRV_SYS_GetTimeStampMs(HI_U32 *pu32TimeMs)
{
    HI_U64 u64TimeNow;

    if (HI_NULL == pu32TimeMs)
    {
        HI_ERR_SYS("null pointer error\n");
        return HI_FAILURE;
    }

    u64TimeNow = sched_clock();

    do_div(u64TimeNow, DIV_NS_TO_MS);

    *pu32TimeMs = (HI_U32)u64TimeNow;

    return HI_SUCCESS;
}

/*
 * from datasheet, the value of dolby_flag meaning: 0: support; 1: not_support .
 * but we change its meaning for return parameter : 0:not support; 1:support.
 */
HI_S32 HI_DRV_SYS_GetDolbySupport(HI_U32 *pu32Support)
{
#if    defined(CHIP_TYPE_hi3716cv200)   \
    || defined(CHIP_TYPE_hi3716mv400)   \
    || defined(CHIP_TYPE_hi3718cv100)   \
    || defined(CHIP_TYPE_hi3719cv100)   \
    || defined(CHIP_TYPE_hi3718mv100)   \
    || defined(CHIP_TYPE_hi3719mv100)   \
    || defined(CHIP_TYPE_hi3796cv100)   \
    || defined(CHIP_TYPE_hi3798cv100)
    *pu32Support = !(g_pstRegPeri->PERI_CHIP_INFO4.bits.dolby_flag);
#elif  defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)    \
    || defined(CHIP_TYPE_hi3798cv200_a)
    *pu32Support = !(g_pstRegPeri->CHIPSET_INFO.bits.dolby_flag);
#else
    *pu32Support = 0;
#endif

    return HI_SUCCESS;
}

/*
 * 1:support; 0:not_support
 */
HI_S32 HI_DRV_SYS_GetDtsSupport(HI_U32 *pu32Support)
{
#if    defined(CHIP_TYPE_hi3716cv200)   \
    || defined(CHIP_TYPE_hi3716mv400)   \
    || defined(CHIP_TYPE_hi3718cv100)   \
    || defined(CHIP_TYPE_hi3719cv100)   \
    || defined(CHIP_TYPE_hi3718mv100)   \
    || defined(CHIP_TYPE_hi3719mv100)   \
    || defined(CHIP_TYPE_hi3796cv100)   \
    || defined(CHIP_TYPE_hi3798cv100)
    *pu32Support = g_pstRegPeri->PERI_CHIP_INFO4.bits.dts_flag;
#elif  defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)    \
    || defined(CHIP_TYPE_hi3798cv200_a)
    *pu32Support = g_pstRegPeri->CHIPSET_INFO.bits.dts_flag;
#else
    *pu32Support = 0;
#endif

    return HI_SUCCESS;
}

/*
 * 1:support; 0:not_support
 */
HI_S32 HI_DRV_SYS_GetRoviSupport(HI_U32 *pu32Support)
{
#if    defined(CHIP_TYPE_hi3716cv200)   \
    || defined(CHIP_TYPE_hi3716mv400)   \
    || defined(CHIP_TYPE_hi3718cv100)   \
    || defined(CHIP_TYPE_hi3719cv100)   \
    || defined(CHIP_TYPE_hi3718mv100)   \
    || defined(CHIP_TYPE_hi3719mv100)   \
    || defined(CHIP_TYPE_hi3796cv100)   \
    || defined(CHIP_TYPE_hi3798cv100)
    *pu32Support = g_pstRegPeri->PERI_SOC_FUSE.bits.mven;
#elif  defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)    \
    || defined(CHIP_TYPE_hi3798cv200_a)
    *pu32Support = g_pstRegPeri->PERI_SOC_FUSE_0.bits.mven;
#else
    *pu32Support = 0;
#endif

    return HI_SUCCESS;
}

/*
 * 0: not_advca_support; 1: advca_support
 */
HI_S32 HI_DRV_SYS_GetAdvcaSupport(HI_U32 *pu32Support)
{
#if    defined(CHIP_TYPE_hi3716cv200)   \
    || defined(CHIP_TYPE_hi3716mv400)   \
    || defined(CHIP_TYPE_hi3718cv100)   \
    || defined(CHIP_TYPE_hi3719cv100)   \
    || defined(CHIP_TYPE_hi3718mv100)   \
    || defined(CHIP_TYPE_hi3719mv100)
#define HI_CHIP_NON_ADVCA   (0x2a13c812)
#define HI_CHIP_ADVCA       (0x6edbe953)

    HI_U32 AdvcaFlag;

    HI_REG_READ(IO_ADDRESS(0xf8ab0128), AdvcaFlag);

    if (HI_CHIP_ADVCA == AdvcaFlag)
    {
        *pu32Support = 1;
    }
    else if (HI_CHIP_NON_ADVCA == AdvcaFlag)
    {
        *pu32Support = 0;
    }
    else
    {
        HI_ERR_SYS("invalid advca flag\n");
        return HI_FAILURE;
    }
#elif  defined(CHIP_TYPE_hi3796cv100) \
    || defined(CHIP_TYPE_hi3798cv100) \
    || defined(CHIP_TYPE_hi3798mv100) \
    || defined(CHIP_TYPE_hi3796mv100) \
    || defined(CHIP_TYPE_hi3798cv200_a)
    *pu32Support = 0;
#endif

    return HI_SUCCESS;
}

HI_S32 HI_DRV_SYS_GetMemConfig(HI_SYS_MEM_CONFIG_S *pstConfig)
{
#if defined(CHIP_TYPE_hi3798mv100) \
 || defined(CHIP_TYPE_hi3796mv100) \
 || defined(CHIP_TYPE_hi3798cv200_a)

    HI_U32      Ret;

    if (HI_NULL != pstConfig)
    {
        Ret = get_mem_size(&(pstConfig->u32TotalSize), HIUAPI_GET_RAM_SIZE);

        Ret |= get_mem_size(&(pstConfig->u32MMZSize), HIUAPI_GET_CMA_SIZE);

        if (Ret != HI_SUCCESS)
        {
            HI_ERR_SYS("get_mem_size ERR, Ret=%#x\n", Ret);
            return HI_FAILURE;
        }
    }
    else
    {
        HI_ERR_SYS("invalid DDR conf ptr\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
#else
    return HI_FAILURE;
#endif
}

HI_S32 HI_DRV_SYS_GetDieID(HI_U64 *pu64dieid)
{
#if defined(CHIP_TYPE_hi3798mv100) \
 || defined(CHIP_TYPE_hi3796mv100) \
 || defined(CHIP_TYPE_hi3798cv200_a)

    HI_U64 id0 = 0;
    HI_U64 id0_0 = 0, id0_1 = 0;
    HI_U64 id1 = 0;
    HI_U64 id2 = 0;
    HI_LENGTH_T timeend = 0;
    HI_S64 timeout = 0;

    if (HI_NULL == pu64dieid)
    {
        HI_ERR_SYS("invalid die ID ptr\n");
        return HI_FAILURE;
    }

    HI_REG_WRITE(IO_ADDRESS(HI_CRG_BASE_ADDR + 0xc0), 0x407);
    HI_REG_WRITE(IO_ADDRESS(HI_CRG_BASE_ADDR + 0xc0), 0x007);
    /** wait state and timeout after 1 second*/
    timeend = jiffies+1*HZ;
    while( !HI_REG_ReadBits(HI_OTP_BASE_ADDR + 0xc, 0x1)  &&  (timeout=time_before(jiffies, timeend)));

    if (HI_NULL == timeout)
    {
        HI_ERR_SYS("get die ID timeout\n");
        return HI_FAILURE;
    }

    id0_0 = HI_REG_ReadBits(HI_OTP_BASE_ADDR + 0x0170, 0xfffffff0)>>4;
    id0_1 = HI_REG_ReadBits(HI_OTP_BASE_ADDR + 0x0174, 0xff);
    id0_1 = id0_1 << 28;
    id0 = id0_0 |id0_1;                                  /**id0 is 36 bit */
    id1 = (HI_REG_ReadBits(HI_OTP_BASE_ADDR + 0x0174, 0x1f00)  >> 8);      /**id1 is 5bit */
    id2  = (HI_REG_ReadBits(HI_OTP_BASE_ADDR + 0x0174, 0x1fffe000)  >> 13);   /**id2 is 16bit*/
    *pu64dieid =  id0 |  (id1 << 36) | (id2<<41);               /** put id0 id1 and id2 together*/
    return HI_SUCCESS;
#else
    *pu64dieid = 0;
    return HI_SUCCESS;
#endif
}


HI_S32 HI_DRV_SYS_KInit(HI_VOID)
{
    return 0;
}

HI_VOID HI_DRV_SYS_KExit(HI_VOID)
{
    return ;
}

EXPORT_SYMBOL(HI_DRV_SYS_GetChipVersion);
EXPORT_SYMBOL(HI_DRV_SYS_GetChipPackageType);
EXPORT_SYMBOL(HI_DRV_SYS_GetTimeStampMs);
EXPORT_SYMBOL(HI_DRV_SYS_GetDolbySupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetDtsSupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetAdvcaSupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetRoviSupport);
EXPORT_SYMBOL(HI_DRV_SYS_GetMemConfig);
EXPORT_SYMBOL(HI_DRV_SYS_GetDieID);

