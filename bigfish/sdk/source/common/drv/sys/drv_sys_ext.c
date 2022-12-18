/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sys_ext.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2006/02/09
  Description   :
  History       :
  1.Date        : 2006/02/09
    Author      : Luo Chuanzao
    Modification: Created file

  2.Date         : 2006/2/9
    Author       : QuYaxin 46153
    Modification : Modified some macro for coherence
                   with mpi_struct.h

  3.Date         : 2010/1/25
    Author       : jianglei
    Modification : Modified for X5HD common module

******************************************************************************/

#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/delay.h>
#include <mach/hardware.h>
#include "hi_type.h"
#include "hi_osal.h"
#include "hi_reg_common.h"
#include "hi_drv_struct.h"
#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_drv_reg.h"
#include "drv_sys_ioctl.h"

static HI_CHAR s_szSdkKoVersion[] __attribute__((used)) = "SDK_VERSION:["\
    MKMARCOTOSTR(SDK_VERSION)"] Build Time:["\
    __DATE__", "__TIME__"]";

typedef struct hiHIxxxx_SOC_S
{
    struct semaphore stSem;
    HI_SYS_CONF_S stChipConf;
}HIxxxx_SOC_S;

static HIxxxx_SOC_S s_stSocData;

extern const char * get_sdkversion(void);

HI_S32 SYS_GetBootVersion(HI_CHAR *pVersion,HI_U32 u32VersionLen)
{
    const HI_U8* pu8BootVer = get_sdkversion();

    if (HI_NULL == pVersion || u32VersionLen == 0)
    {
        HI_WARN_SYS("SYS_GetBootVersion failure line:%d\n", __LINE__);
        return HI_FAILURE;
    }

    if (pu8BootVer != NULL)
    {
        if (u32VersionLen > strlen(pu8BootVer))
        {
            u32VersionLen = strlen(pu8BootVer);
        }

        memcpy(pVersion, pu8BootVer, u32VersionLen);
        pVersion[u32VersionLen] = '\0';

        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 SysSetConfig(HI_SYS_CONF_S *pstConf)
{
    memcpy(&s_stSocData.stChipConf, pstConf, sizeof(*pstConf));
    return 0;
}

HI_S32 SysGetConfig(HI_SYS_CONF_S *pstConf)
{
    memcpy(pstConf, &s_stSocData.stChipConf, sizeof(*pstConf));
    return 0;
}

static HI_S32 SYS_Ioctl(struct inode *pInode, struct file *pFile, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 ret = -ENOIOCTLCMD;
    HI_SYS_VERSION_S* chiptype;

    down(&s_stSocData.stSem);
    switch (cmd)
    {
        case SYS_SET_CONFIG_CTRL :
            ret = SysSetConfig((HI_SYS_CONF_S*)arg);
            break;

        case SYS_GET_CONFIG_CTRL :
            ret = SysGetConfig((HI_SYS_CONF_S*)arg);
            break;

        case SYS_GET_SYS_VERSION :
            chiptype = (HI_SYS_VERSION_S*)arg;
            HI_DRV_SYS_GetChipVersion(&chiptype->enChipTypeHardWare, &chiptype->enChipVersion);
            SYS_GetBootVersion(chiptype->BootVersion, sizeof(chiptype->BootVersion));
            ret = HI_SUCCESS;
            break;

        case SYS_GET_TIMESTAMPMS :
            ret = HI_DRV_SYS_GetTimeStampMs((HI_U32*)arg);
            break;

        case SYS_GET_DOLBYSUPPORT:
            ret = HI_DRV_SYS_GetDolbySupport((HI_U32*)arg);
            break;
        case SYS_GET_DTSSUPPORT:
            ret = HI_DRV_SYS_GetDtsSupport((HI_U32*)arg);
            break;
        case SYS_GET_ADVCASUPPORT:
            ret = HI_DRV_SYS_GetAdvcaSupport((HI_U32*)arg);
            break;
        case SYS_GET_MACROVISIONSUPPORT:
            ret = HI_DRV_SYS_GetRoviSupport((HI_U32*)arg);
            break;
        case SYS_GET_DDRCONFIG:
            ret = HI_DRV_SYS_GetMemConfig((HI_SYS_MEM_CONFIG_S*)arg);
            break;
	 case SYS_GET_DIEID:
            ret = HI_DRV_SYS_GetDieID((HI_U64 *)arg);
            break;

        default :
            HI_WARN_SYS("ioctl cmd %d nonexist!\n", cmd);
    }
    up(&s_stSocData.stSem);
    return ret;
}

static HI_S32 SysProcShow(struct seq_file *s, HI_VOID *pArg)
{
    HI_CHIP_TYPE_E      ChipType    = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E   ChipVersion = 0;
    HI_CHAR            *ChipName;
    HI_U32 u32DolbySupport ;
    HI_U32 u32DtsSupport ;
    HI_U32 u32RoviSupport ;
    HI_U32 u32AdvcaSupport;

    HI_DRV_SYS_GetChipVersion(&ChipType, &ChipVersion);

    PROC_PRINT(s, "%s\n", s_szSdkKoVersion);

    switch (ChipType)
    {
        case HI_CHIP_TYPE_HI3716M :
            ChipName = "Hi3716M";
            break;
        case HI_CHIP_TYPE_HI3716H :
            ChipName = "Hi3716H";
            break;
        case HI_CHIP_TYPE_HI3716C :
            ChipName = "Hi3716C";
            break;
        case HI_CHIP_TYPE_HI3720 :
            ChipName = "Hi3720";
            break;
        case HI_CHIP_TYPE_HI3712 :
            ChipName = "Hi3712";
            break;
        case HI_CHIP_TYPE_HI3715 :
            ChipName = "Hi3715";
            break;
        case HI_CHIP_TYPE_HI3718M :
            ChipName = "Hi3718M";
            break;
        case HI_CHIP_TYPE_HI3718C :
            ChipName = "Hi3718C";
            break;
        case HI_CHIP_TYPE_HI3719M :
            ChipName = "Hi3719M";
            break;
        case HI_CHIP_TYPE_HI3719C :
            ChipName = "Hi3719C";
            break;
        case HI_CHIP_TYPE_HI3796C :
            ChipName = "Hi3796C";
            break;
        case HI_CHIP_TYPE_HI3798C :
            ChipName = "Hi3798C";
            break;
        case HI_CHIP_TYPE_HI3798C_A :
            ChipName = "Hi3798C_A";
            break;
        case HI_CHIP_TYPE_HI3796M :
            ChipName = "Hi3796M";
            break;
        case HI_CHIP_TYPE_HI3798M :
            ChipName = "Hi3798M";
            break;
        default:
            ChipName = "UNKNOWN";
    }

    PROC_PRINT(s, "CHIP_VERSION: %s(0x%x)_v%x\n", ChipName, ChipType, ChipVersion);

    if (HI_SUCCESS == HI_DRV_SYS_GetDolbySupport(&u32DolbySupport))
    {
        PROC_PRINT(s, "DOLBY: %s\n", (u32DolbySupport) ? "YES" : "NO");
    }

    if (HI_SUCCESS == HI_DRV_SYS_GetDtsSupport(&u32DtsSupport))
    {
        PROC_PRINT(s, "DTS: %s\n", (u32DtsSupport) ? "YES" : "NO");
    }

    if (HI_SUCCESS == HI_DRV_SYS_GetAdvcaSupport(&u32AdvcaSupport))
    {
        PROC_PRINT(s, "ADVCA: %s\n", (u32AdvcaSupport) ? "YES" : "NO");
    }

    if (HI_SUCCESS == HI_DRV_SYS_GetRoviSupport(&u32RoviSupport))
    {
        PROC_PRINT(s, "ROVI(Macrovision): %s\n", (u32RoviSupport) ? "YES" : "NO");
    }

    return 0;
}

static long CMPI_SYS_Ioctl(struct file *file, HI_U32 cmd, unsigned long arg)
{
    long ret;
    ret=(long)HI_DRV_UserCopy(file->f_dentry->d_inode, file, cmd, arg, SYS_Ioctl);

    return ret;
}


static HI_S32 CMPI_SYS_Open(struct inode * vinode, struct file * vfile)
{
    return 0;
}

static HI_S32 CMPI_SYS_Close(struct inode * vinode, struct file * vfile)
{
    return 0;
}


static struct file_operations stFileOp =
{
     .owner       = THIS_MODULE,
     .open        = CMPI_SYS_Open,
     .unlocked_ioctl  = CMPI_SYS_Ioctl,
     .release     = CMPI_SYS_Close
};
static UMAP_DEVICE_S s_stDevice;

HI_S32 HI_DRV_SYS_Init(HI_VOID)
{
    DRV_PROC_EX_S stFnOpt =
    {
         .fnRead = SysProcShow,
    };

    sema_init(&s_stSocData.stSem, 1);

    HI_OSAL_Snprintf(s_stDevice.devfs_name, sizeof(s_stDevice.devfs_name), UMAP_DEVNAME_SYS);
    s_stDevice.fops = &stFileOp;
    s_stDevice.minor = UMAP_MIN_MINOR_SYS;
    s_stDevice.owner  = THIS_MODULE;
    s_stDevice.drvops = NULL;

    if (HI_DRV_DEV_Register(&s_stDevice))
    {
        HI_ERR_SYS("Register system device failed!\n");
        goto OUT;
    }

    HI_DRV_PROC_AddModule(HI_MOD_SYS, &stFnOpt, 0);

    return 0;

OUT:
    HI_WARN_SYS("load sys ...FAILED!\n");
    return HI_FAILURE;
}

HI_VOID HI_DRV_SYS_Exit(HI_VOID)
{
    HI_DRV_PROC_RemoveModule(HI_MOD_SYS);
    HI_DRV_DEV_UnRegister(&s_stDevice);
}

