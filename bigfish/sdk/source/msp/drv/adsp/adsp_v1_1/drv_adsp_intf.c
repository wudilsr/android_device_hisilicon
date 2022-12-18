/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv2bO4a86Ra1cP5w/R608AW9MyvBFsCSDo8GzQMC4Jhtu/zShyENpjFzntvB+
qu9VLadm7xpBOGxb9pN9HIkRL02SuAm5SHdaTYzg1ktQWmxJq5GXSQLAfrs2fjTOc4zcR0aZ
d9VMQ0LU5oS/E3BZtrv3kezyoW8Jqqx/TEdNxIaR9BIYspp57ouN50/VVVWOGQ==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/vmalloc.h>
#include <linux/interrupt.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <mach/hardware.h>

/* Unf headers */
#include "hi_error_mpi.h"
#include "hi_drv_mmz.h"
#include "hi_drv_stat.h"
#include "hi_drv_sys.h"
#include "hi_drv_proc.h"

/* Drv headers */
#include "drv_adsp_ext.h"
#include "drv_adsp_private.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */


static struct file_operations s_stDevFileOpts =
{
    .owner = THIS_MODULE,

    //    .open			= ADSP_DRV_Open,
    //    .release		= ADSP_DRV_Release,
};

static PM_BASEOPS_S s_stDrvOps = {
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = ADSP_DRV_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = ADSP_DRV_Resume,
};

static ADSP_REGISTER_PARAM_S s_stProcParam = {
    .pfnReadProc  = ADSP_DRV_ReadProc,
    .pfnWriteProc = ADSP_DRV_WriteProc,
};

/* the attribute struct of video decoder device */
static UMAP_DEVICE_S s_stAdspUmapDev;

static __inline__ int  ADSP_DRV_RegisterDev(void)
{
    /*register aenc chn device*/
 
	snprintf(s_stAdspUmapDev.devfs_name, sizeof(s_stAdspUmapDev.devfs_name), UMAP_DEVNAME_ADSP);
    s_stAdspUmapDev.fops   = &s_stDevFileOpts;
    s_stAdspUmapDev.minor  = UMAP_MIN_MINOR_ADSP;
    s_stAdspUmapDev.owner  = THIS_MODULE;
    s_stAdspUmapDev.drvops = &s_stDrvOps;
    if (HI_DRV_DEV_Register(&s_stAdspUmapDev) < 0)
    {
        HI_FATAL_ADSP("FATAL: vdec register device failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static __inline__ void ADSP_DRV_UnregisterDev(void)
{
    /*unregister aenc chn device*/
    HI_DRV_DEV_UnRegister(&s_stAdspUmapDev);
}

HI_S32 ADSP_DRV_ModInit(HI_VOID)
{
    int ret;

#ifndef HI_MCE_SUPPORT
    ret = ADSP_DRV_Init();
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_ADSP("Init drv fail!\n");
        return HI_FAILURE;
    }
#endif


    ret = ADSP_DRV_RegisterProc(&s_stProcParam);
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_ADSP("Reg proc fail!\n");
        return HI_FAILURE;
    }

    ret = ADSP_DRV_RegisterDev();
    if (HI_SUCCESS != ret)
    {
        ADSP_DRV_UnregisterProc();
        HI_FATAL_ADSP("Reg dev fail!\n");
        return HI_FAILURE;
    }

#ifdef MODULE
    HI_PRINT("Load hi_adsp.ko success.\t(%s)\n", VERSION_STRING);
#endif

    return HI_SUCCESS;
}

HI_VOID ADSP_DRV_ModExit(HI_VOID)
{
    ADSP_DRV_UnregisterDev();
    ADSP_DRV_UnregisterProc();

#ifndef HI_MCE_SUPPORT
    ADSP_DRV_Exit();
#endif

    return;
}

#ifdef MODULE
module_init(ADSP_DRV_ModInit);
module_exit(ADSP_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */
