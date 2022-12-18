
#include "hi_common.h"
#include "hi_reg_common.h"

HI_VOID HI_DRV_SYS_GetChipVersion(HI_CHIP_TYPE_E *penChipType, HI_CHIP_VERSION_E *penChipVersion)
{
    HI_CHIP_TYPE_E      ChipType    = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E   ChipVersion = HI_CHIP_VERSION_BUTT;

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

