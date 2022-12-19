/******************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: gfx2d_os.c
* Description: gfx2d os adapter layer
*
* History:
* Version   Date         Author     DefectNum    Description
* main\1    2013-10-23              NULL         Create this file.
*******************************************************************************/

#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#include "hi_drv_dev.h"
#include "hi_gfx2d_type.h"
#include "hi_gfx_comm_k.h"
#include "gfx2d_ctl.h"
#include "drv_gfx2d_ioctl.h"
#include "gfx2d_config.h"
#include "gfx2d_hal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#define GFX2D_MODULENAME "hi_gfx2d"

static HI_U32 mem = 0;

module_param(mem, uint, S_IRUGO);

#ifndef GFX2D_PROC_UNSUPPORT
HI_S32 GFX2D_OS_ReadProc(struct seq_file *p, HI_VOID *v)
{
    if (GFX2D_CONFIG_IsProcOn())
        (HI_VOID)GFX2D_CTL_ReadProc(p, v);

    return HI_SUCCESS;
}

HI_S32 GFX2D_OS_WriteProc(struct file * file, const char __user * buf,
                          size_t count, loff_t *ppos)
{
    (HI_VOID)GFX2D_CONFIG_WriteProc(file, buf, count, ppos);

    (HI_VOID)GFX2D_CTL_WriteProc(file, buf, count, ppos);

    return HI_SUCCESS;
}
#endif

HI_S32 GFX2D_OS_Open(struct inode *finode, struct file *ffile)
{
    return GFX2D_CTL_Open();
}

HI_S32 GFX2D_OS_Release(struct inode *finode, struct file *ffile)
{
    return GFX2D_CTL_Close();
}

long GFX2D_OS_Ioctl(struct file  *ffile, unsigned int  cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;

    if (NULL == argp)
    {
       return -EFAULT;
    }


    if (GFX2D_CTL_CheckOpen() == HI_FALSE)
    {
        return -EFAULT;
    }

    switch(cmd)
    {
        case GFX2D_COMPOSE:
        {
            GFX2D_COMPOSE_CMD_S stCompose;

            if (copy_from_user(&stCompose, argp, sizeof(GFX2D_COMPOSE_CMD_S)))
            {
                return -EFAULT;
            }

            if (stCompose.bSync)
            {
                return GFX2D_CTL_ComposeSync(stCompose.enDevId, stCompose.pstComposeList, stCompose.pstDst, stCompose.u32Timeout);
            }
            else
            {
                return GFX2D_CTL_ComposeAsync(stCompose.enDevId, stCompose.pstComposeList, stCompose.pstDst);
            }
        }
        case GFX2D_WATIALLDONE:
        {
            GFX2D_WAITALLDONE_CMD_S stWaitAllDone;

            if (copy_from_user(&stWaitAllDone, argp, sizeof(GFX2D_WAITALLDONE_CMD_S)))
            {
                return -EFAULT;
            }

            return GFX2D_CTL_WaitAllDone(stWaitAllDone.enDevId, stWaitAllDone.u32Timeout);
        }
        default:
            return -ENOIOCTLCMD;
    }
    return HI_SUCCESS;
}

HI_S32 GFX2D_OS_PmSuspend(PM_BASEDEV_S *pstDev, pm_message_t state)
{
    GFX2D_CTL_WaitAllDone(HI_GFX2D_DEV_ID_0, 0);

    return HI_SUCCESS;
}

HI_S32 GFX2D_OS_PmResume(PM_BASEDEV_S *pstDev)
{
    GFX2D_HAL_Open();
    return HI_SUCCESS;
}

DECLARE_GFX_NODE(GFX2D_MODULENAME,GFX2D_OS_Open, GFX2D_OS_Release, NULL, GFX2D_OS_Ioctl,\
                 GFX2D_OS_PmSuspend, GFX2D_OS_PmResume);

static HI_VOID HI_GFX_ShowVersionK(HIGFX_MODE_ID_E ModID)
{
	#if !defined(CONFIG_GFX_COMM_VERSION_DISABLE) && !defined(CONFIG_GFX_COMM_DEBUG_DISABLE)

    	HI_CHAR MouleName[7][10] = {"tde","jpegdec","jpegenc","fb","png", "higo", "gfx2d"};
        HI_CHAR Version[160] ="SDK_VERSION:["MKMARCOTOSTR(SDK_VERSION)"] Build Time:["\
		__DATE__", "__TIME__"]";

    	if (ModID >= HIGFX_BUTT_ID)
    		return;

	if ((HIGFX_JPGDEC_ID == ModID) || (HIGFX_JPGENC_ID == ModID))
		GFX_Printk("Load hi_%s.ko success.\t(%s)\n", MouleName[ModID],Version);
	else
		GFX_Printk("Load hi_%s.ko success.\t\t(%s)\n", MouleName[ModID],Version);

	return;

	#endif
}


HI_S32 GFX2D_OS_ModInit(HI_VOID)
{
    HI_S32 s32Ret;
#ifndef GFX2D_PROC_UNSUPPORT
    GFX_PROC_ITEM_S stProcItem = {GFX2D_OS_ReadProc,GFX2D_OS_WriteProc,NULL};
#endif

    s32Ret = GFX2D_CONFIG_SetMemSize(mem);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    s32Ret = GFX2D_CTL_Init();
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    s32Ret = HI_GFX_PM_Register();
    if (HI_SUCCESS != s32Ret)
    {
        (HI_VOID)GFX2D_CTL_Deinit();
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "Register module failed!\n");
        return HI_FAILURE;
    }

#ifndef GFX2D_PROC_UNSUPPORT
    s32Ret = HI_GFX_PROC_AddModule(GFX2D_MODULENAME, &stProcItem, NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_GFX_COMM_LOG_WARNING(HIGFX_GFX2D_ID, "Create proc failed!\n");
    }
#endif

    HI_GFX_ShowVersionK(HIGFX_GFX2D_ID);

    return HI_SUCCESS;
}

HI_VOID GFX2D_OS_ModExit(HI_VOID)
{
    HI_GFX_PROC_RemoveModule(GFX2D_MODULENAME);

    (HI_VOID)HI_GFX_PM_UnRegister();

    (HI_VOID)GFX2D_CTL_Deinit();

    return;
}

module_init(GFX2D_OS_ModInit);
module_exit(GFX2D_OS_ModExit);

MODULE_AUTHOR("Digital Media Team, Hisilicon crop.");
MODULE_DESCRIPTION("Hisilicon GFX2D Device driver for 3716CV200");
MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0.0.0");

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/
