#include <linux/version.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/miscdevice.h>

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>        /* everything... */
#include <linux/errno.h> /* error codes */
#include <linux/types.h> /* size_t */
#include <linux/fcntl.h> /* O_ACCMODE */
#include <linux/cdev.h>
#include <asm/uaccess.h> /* copy_*_user */

#include <linux/interrupt.h>
#include <linux/poll.h>
#include <linux/workqueue.h>
#include <asm/io.h>

#include "hi_jpge_type.h"
#include "drv_jpge_ioctl.h"
//#include "jpge_ext.h"
#include "drv_jpge_ext.h"
#include "jpge_hal.h"

#include "hi_drv_dev.h"

#include "hi_drv_mem.h"
#include "hi_drv_module.h"
#include "hi_gfx_comm_k.h"
static int jpge_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state);
static int jpge_pm_resume(PM_BASEDEV_S *pdev);

static atomic_t g_JPGECount = ATOMIC_INIT(0);

static HI_BOOL gs_bClockOpen = HI_FALSE;


static JPGE_EXPORT_FUNC_S s_JpgeExportFuncs =
{
	.pfnJpgeInit                = Jpge_Init,
	.pfnJpgeDeInit             = Jpge_DInit,
      .pfnJpgeCreateChn        = Jpge_Create_toVenc,
	.pfnJpgeDestroyChn       = Jpge_Destroy,
	.pfnJpgeEncodeFrame    = Jpge_Encode_toVenc,
	.pfnJpgeSuspend		= jpge_pm_suspend,
	.pfnJpgeResume		= jpge_pm_resume,
};

static int jpge_open(struct inode *finode, struct file  *ffile)
{
    if (1 == atomic_inc_return(&g_JPGECount))
    {
    	Jpge_SetClock();;
    }

    return 0;
}

int JpgeOsiOpen(HI_VOID)
{
    return jpge_open(NULL, NULL);
}

static int jpge_release(struct inode *finode, struct file  *ffile)
{

    if (atomic_dec_and_test(&g_JPGECount))
    {
    	Jpge_CloseClock();
    }

    if ( atomic_read(&g_JPGECount) < 0 )
    {
        atomic_set(&g_JPGECount, 0);
    }

    return 0;
}

int JpgeOsiClose(HI_VOID)
{
      return jpge_release(NULL, NULL);
}

HI_VOID Jpge_Init(HI_VOID)
{
	 jpge_open(NULL, NULL);
}
HI_VOID Jpge_DInit(HI_VOID)
{
	jpge_release(NULL, NULL);
}

static long jpge_ioctl(struct file  *ffile, unsigned int  cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    long ret;

    if (NULL == argp)
    {
       return -EFAULT;
    }

    switch (cmd)
    {
    case JPGE_CREATE_CMD:
    {
        Jpge_EncCfgInfo_S EncCfgInfo;
        memset(&EncCfgInfo,0x0,sizeof(Jpge_EncCfgInfo_S));
        
        if ((ret = copy_from_user(&EncCfgInfo, argp, sizeof(Jpge_EncCfgInfo_S))) < 0)
        {
            return -EFAULT;
        }
        ret =  Jpge_Create ( EncCfgInfo.pEncHandle, &EncCfgInfo.EncCfg);
        if(0 != ret)
        {
	        return ret;
	    }
        if((ret = copy_to_user(argp, &EncCfgInfo, sizeof(Jpge_EncCfgInfo_S))) < 0)
        {
            return -EFAULT;
        }
        return 0;
    }
    case JPGE_ENCODE_CMD:
    {
        Jpge_EncInfo_S EncInfo;
        memset(&EncInfo,0x0,sizeof(Jpge_EncInfo_S));
        
        if ((ret = copy_from_user(&EncInfo, argp, sizeof(Jpge_EncInfo_S))) < 0)
        {
            return -EFAULT;
        }
        ret =  Jpge_Encode ( (HI_U32)EncInfo.EncHandle, &EncInfo.EncIn, &EncInfo.EncOut);
        if(0 != ret)
        {
            return ret;
        }
        if((ret = copy_to_user(argp, &EncInfo, sizeof(Jpge_EncInfo_S))) < 0)
        {
            return -EFAULT;
        }
        return 0;
    }
    case JPGE_DESTROY_CMD:
    {
         HI_U32  u32Handle = 0;
        if ((ret = copy_from_user(&u32Handle, argp, sizeof(HI_U32))) < 0)
        {
            return -EFAULT;
        }
        return Jpge_Destroy(u32Handle);
    }
    default:
        return -ENOIOCTLCMD;
    }
}


DECLARE_GFX_NODE("hi_jpge", jpge_open, jpge_release, NULL, jpge_ioctl, jpge_pm_suspend, jpge_pm_resume);


static HI_VOID HI_GFX_ShowVersionK(HIGFX_MODE_ID_E ModID)
{
	#if !defined(CONFIG_GFX_COMM_VERSION_DISABLE) && !defined(CONFIG_GFX_COMM_DEBUG_DISABLE)

    	HI_CHAR MouleName[7][10] = {"tde","jpegdec","jpegenc","fb","png", "higo", "gfx2d"};
        HI_CHAR Version[160] ="SDK_VERSION:["MKMARCOTOSTR(SDK_VERSION)"] Build Time:["\
		__DATE__", "__TIME__"]";

    	if (ModID >= HIGFX_BUTT_ID)
    		return;

	//if ((HIGFX_JPGDEC_ID == ModID) || (HIGFX_JPGENC_ID == ModID))
		GFX_Printk("Load hi_%s.ko success.\t(%s)\n", MouleName[ModID],Version);
	//else
	//	GFX_Printk("Load hi_%s.ko success.\t\t(%s)\n", MouleName[ModID],Version);

	return;

	#endif
}


typedef unsigned long       HI_UL;


void JPGE_DRV_ModExit(void);

#define JPGENAME "HI_JPGE"

int JPGE_DRV_ModInit(void)
{
    int ret;

    ret = Jpge_Open();
    if(0 != ret)
    {
        HI_PRINT("request_irq for JPGE failure!\n");
        return -1;
    }

    ret = HI_GFX_PM_Register();
    if (0 != ret)
    {
	HI_PRINT("register dev failed!\n");
	Jpge_Close();
	return -1;
    }

    ret = HI_GFX_MODULE_Register(HIGFX_JPGENC_ID, JPGENAME, &s_JpgeExportFuncs);
    if (HI_SUCCESS != ret)
    {
        HI_PRINT("HI_DRV_MODULE_Register JPGE failed\n");
        JPGE_DRV_ModExit();
        return -1;
    }

    HI_GFX_ShowVersionK(HIGFX_JPGENC_ID);

    return 0;
}

void JPGE_DRV_ModExit(void)
{
    HI_GFX_MODULE_UnRegister(HIGFX_JPGENC_ID);
    Jpge_Close();
    /* cleanup_module is never called if registering failed */
    HI_GFX_PM_UnRegister();
}

static int jpge_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{

	U_PERI_CRG36 unTempValue;

	unTempValue.u32 = g_pstRegCrg->PERI_CRG36.u32;

	if(0x1 == unTempValue.bits.jpge_cken)
	{
		gs_bClockOpen = HI_TRUE;
	}
	else
	{
		gs_bClockOpen = HI_FALSE;
	}


	HI_PRINT("JPGE suspend OK\n");

    return 0;
}

/* wait for resume */
static int jpge_pm_resume(PM_BASEDEV_S *pdev)
{

	if(HI_TRUE == gs_bClockOpen)
    {
    	Jpge_SetClock();
	}
    HI_PRINT("JPGE resume OK\n");
    return 0;
}

#ifdef MODULE
module_init(JPGE_DRV_ModInit);
module_exit(JPGE_DRV_ModExit);
#else
//late_initcall_sync(JPGE_DRV_ModInit);
#endif

#ifndef HI_ADVCA_FUNCTION_RELEASE
MODULE_DESCRIPTION("driver for the all jpge");
MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0.0.0");
#else
MODULE_DESCRIPTION("");
MODULE_AUTHOR("");
MODULE_LICENSE("GPL");
MODULE_VERSION("");
#endif

EXPORT_SYMBOL(JpgeOsiOpen);
EXPORT_SYMBOL(JpgeOsiClose);
