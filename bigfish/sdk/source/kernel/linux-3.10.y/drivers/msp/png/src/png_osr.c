/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	: hi_png_api.c
Version		: Initial Draft
Author		: z00141204
Created		: 2010/10/11
Description	: implemention of PNG ioctl
Function List 	: 
			  	  
History       	:
Date				Author        		Modification
2010/10/11		z00141204		Created file      	

******************************************************************************/
#include <linux/version.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include "hi_drv_dev.h"
#include "hi_drv_sys.h"
#include "hi_drv_struct.h"
#include "hi_drv_png.h"
#include "png_hal.h"
#include "png_osires.h"
#include "png_osi.h"
#include "png_proc.h"
#include "png_define.h"
#include "hi_gfx_comm_k.h"
#include "hi_png_config.h"
#include "drv_png_ext.h"

#define MKSTR(exp) # exp
#define MKMARCOTOSTR(exp) MKSTR(exp)

#define PNGNAME "HI_PNG"
extern HI_S32 PngOsiInit(HI_VOID);
extern HI_S32 PngOsiDeinit(HI_VOID);
extern HI_VOID PngOsiIntHandle(HI_U32 u32Int);
extern HI_VOID PngOsiDelTimer(HI_VOID);
extern HI_S32 PngOsiSuspend(HI_VOID);
extern HI_S32 pngOsiResume(HI_VOID);

static long png_ioctl(struct file  *ffile,unsigned int  cmd,unsigned long arg);

static int png_open(struct inode *finode, struct file  *ffile);
static int png_close(struct inode *finode, struct file  *ffile);
static int png_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state);
static int png_pm_resume(PM_BASEDEV_S *pdev);
DECLARE_GFX_NODE("hi_png",png_open, png_close, NULL, png_ioctl, png_pm_suspend, png_pm_resume);

static PNG_EXPORT_FUNC_S s_PngExportFuncs =
{
    .pfnPngSuspend			= png_pm_suspend,
    .pfnPngResume			= png_pm_resume,
};


/* interrutp function */
static int png_isr(int irq, void *dev_id)
{
    HI_U32 u32IntValue;

    /* read register and clear the int*/
    u32IntValue = PngHalGetIntStatus();

    PngOsiIntHandle(u32IntValue);

    return IRQ_HANDLED;
}

void PNG_DRV_ModExit(void);

static HI_VOID HI_GFX_ShowVersionK(HIGFX_MODE_ID_E ModID)
{
	#if !defined(CONFIG_GFX_COMM_VERSION_DISABLE) && !defined(CONFIG_GFX_COMM_DEBUG_DISABLE)
	
    	HI_CHAR MouleName[7][10] = {"tde","jpegdec","jpegenc","fb","png", "higo", "gfx2d"};
        HI_CHAR Version[160] ="SDK_VERSION:["MKMARCOTOSTR(SDK_VERSION)"] Build Time:["\
		__DATE__", "__TIME__"]";

    	if (ModID >= HIGFX_BUTT_ID)
    		return;
	
	//if ((HIGFX_JPGDEC_ID == ModID) || (HIGFX_JPGENC_ID == ModID))	
		//GFX_Printk("Load hi_%s.ko success.\t(%s)\n", MouleName[ModID],Version);
	//else
		GFX_Printk("Load hi_%s.ko success.\t\t(%s)\n", MouleName[ModID],Version);		

	return;
		
	#endif
}

/* module init */

int PNG_DRV_ModInit(void)
{

    HI_S32 Ret;


    /* Hal init*/
    if (0 != PngHalInit())
    {
    	return -1;
    }

    /* Osires init*/
    if (0 != PngOsiResInitHandle())
    {
    	goto ERR5;
    }

#if 0
    if (0 != PngOsiResInitMem())
    {
    	goto ERR4;
    }
    if (0 != PngOsiResInitBuf())
    {
        goto ERR3;
    }
#endif
    if (0 != PngOsiInit())
    {
        goto ERR2;
    }

    /* register interrupt function*/
    if (0 != request_irq(PngHalGetIrqNum(), (irq_handler_t)png_isr, IRQF_PROBE_SHARED, "hi_png_irq", NULL))
    {
    	goto ERR1;
    }

    /* register device*/
    HI_GFX_PM_Register();
    /* proc init*/
#ifndef  CONFIG_PNG_PROC_DISABLE 
    PNG_ProcInit();
#endif
    /*Version info*/
    /*CNcomment:�汾��Ϣ*/
#ifndef CONFIG_PNG_VERSION_DISABLE
    HI_GFX_ShowVersionK(HIGFX_PNG_ID);
#endif
    Ret = HI_GFX_MODULE_Register(HIGFX_PNG_ID, PNGNAME, &s_PngExportFuncs);

    if (HI_SUCCESS != Ret)
    {
	   PNG_ERROR("HI_DRV_MODULE_Register PNG failed\n");
	   PNG_DRV_ModExit();
	   goto ERR1;
    }
	
    return 0;

ERR1:
    PngOsiDeinit();
ERR2:
    PngOsiResDeinitBuf();
#if 0    
ERR3:    
    PngOsiResDeinitMem();
ERR4:
    PngOsiResDeinitHandle();
#endif    
ERR5:
    PngHalDeinit();

    return -1;	
}

/* module deinit */

void PNG_DRV_ModExit(void)
{
    /* proc deinit*/
#ifndef CONFIG_PNG_PROC_DISABLE 
    PNG_ProcCleanup();
#endif
    /* logoout device */
    HI_GFX_PM_UnRegister();
    HI_GFX_MODULE_UnRegister(HIGFX_PNG_ID);
    /* release interrupt num*/
    free_irq(PngHalGetIrqNum(), NULL);

    PngOsiDeinit();
    PngOsiResDeinitBuf();
    PngOsiResDeinitMem();
    PngOsiResDeinitHandle();
    PngHalDeinit();
	
    return;
}

/* open  device*/
static int png_open(struct inode *finode, struct file  *ffile)
{
    return PngOsiOpen();
}

/* close device */
static int png_close(struct inode *finode, struct file  *ffile)
{
    PngOsiClose();
    
    return 0;
}

/* ioctl function */
static long png_ioctl(struct file  *ffile,unsigned int  cmd,unsigned long arg)
{
    void __user *argp = (void __user *)arg;

    if (NULL == argp)
    {
        PNG_ERROR("NULL param!\n");
    	return -EFAULT;
    }

    switch(cmd)
    {
    	case PNG_CREATE_DECODER:
    	{
            HI_S32 s32Ret = 0;
            HI_PNG_HANDLE s32Handle;

            s32Ret = PngOsiCreateDecoder(&s32Handle);
            if (s32Ret < 0)
            {
                return s32Ret;
            }

            if (copy_to_user(argp, &s32Handle, sizeof(HI_S32)))
            {
            	return -EFAULT;
            }

            return 0;
    	}
        case PNG_DESTROY_DECODER:
        {
            HI_PNG_HANDLE s32Handle = -1;

            if (copy_from_user(&s32Handle, argp, sizeof(HI_PNG_HANDLE)))
            {
    	        return -EFAULT;
            }

            return PngOsiDestroyDecoder(s32Handle);
        }
        case PNG_ALLOC_BUF:
        {
            HI_S32 s32Ret = HI_SUCCESS;
            PNG_GETBUF_CMD_S stCmd = {0};

            //PNG_ERROR("kernel sizeof(PNG_GETBUF_CMD_S):%d\n", sizeof(PNG_GETBUF_CMD_S));
            if (copy_from_user(&stCmd, argp, sizeof(PNG_GETBUF_CMD_S)))
            {
                return -EFAULT;
            }

            s32Ret = PngOsiAllocBuf(stCmd.s32Handle, &stCmd.stBuf);
            if (s32Ret < 0)
            {
                return s32Ret;
            }

            if (copy_to_user(argp, &stCmd, sizeof(PNG_GETBUF_CMD_S)))
            {
                return -EFAULT;
            }

            return 0;
        }
        case PNG_RELEASE_BUF:
        {
            HI_S32 s32Ret = HI_SUCCESS;
            HI_PNG_HANDLE s32Handle = 0;

            if (copy_from_user(&s32Handle, argp, sizeof(HI_PNG_HANDLE)))
            {
                return -EFAULT;
            }

            s32Ret = PngOsiReleaseBuf(s32Handle);
            if (s32Ret < 0)
            {
                return s32Ret;
            }

            return 0;
        }
        case PNG_SET_STREAMLEN:
        {
            PNG_SETSTREAM_CMD_S stCmd = {0};

            //PNG_ERROR("kernel sizeof(PNG_SETSTREAM_CMD_S):%d\n", sizeof(PNG_SETSTREAM_CMD_S));

            if (copy_from_user(&stCmd, argp, sizeof(PNG_SETSTREAM_CMD_S)))
            {
                return -EFAULT;
            }

            return PngOsiSetStreamLen(stCmd.s32Handle, stCmd.u32Phyaddr, stCmd.u32Len);
        }
        case PNG_GET_STREAMLEN:
        {
            HI_S32 s32Ret = HI_SUCCESS;
            PNG_SETSTREAM_CMD_S stCmd = {0};

            //PNG_ERROR("kernel sizeof(PNG_SETSTREAM_CMD_S):%d\n", sizeof(PNG_SETSTREAM_CMD_S));

            if (copy_from_user(&stCmd, argp, sizeof(PNG_SETSTREAM_CMD_S)))
            {
                return -EFAULT;
            }

            s32Ret = PngOsiGetStreamLen(stCmd.s32Handle, stCmd.u32Phyaddr, &stCmd.u32Len);
            if (s32Ret < 0)
            {
                return s32Ret;
            }

            if (copy_to_user(argp, &stCmd, sizeof(PNG_SETSTREAM_CMD_S)))
            {
                return -EFAULT;
            }

            return 0;
        }
        case PNG_DECODE:
        {
            PNG_DECODE_CMD_S stCmd = {0};

            //PNG_ERROR("kernel sizeof(PNG_DECODE_CMD_S):%d\n", sizeof(PNG_DECODE_CMD_S));
            if (copy_from_user(&stCmd, argp, sizeof(PNG_DECODE_CMD_S)))
            {
                return -EFAULT;
            }

            return PngOsiDecode(stCmd.s32Handle, &stCmd.stDecInfo);
        }
        case PNG_GET_DECRESULT:
        {
            HI_S32 s32Ret = HI_SUCCESS;
            PNG_DECRESULT_CMD_S stCmd = {0};

            //PNG_ERROR("kernel sizeof(PNG_DECODE_CMD_S):%d\n", sizeof(PNG_DECODE_CMD_S));

            if (copy_from_user(&stCmd, argp, sizeof(PNG_DECRESULT_CMD_S)))
            {
    	        return -EFAULT;
            }

            s32Ret = PngOsiGetResult(stCmd.s32Handle, stCmd.bBlock, &stCmd.eDecResult);
            if (s32Ret < 0)
            {
    	        return s32Ret;
            }

            if (copy_to_user(argp, &stCmd, sizeof(PNG_DECRESULT_CMD_S)))
            {
    	        return -EFAULT;
            }

            return 0;
        }
        case PNG_GET_GETBUFPARAM:
        {
            HI_S32 s32Ret = 0;
            PNG_GETBUFPARAM_CMD_S stCmd = {0};

            //PNG_ERROR("kernel sizeof(PNG_GETBUFPARAM_CMD_S):%d\n", sizeof(PNG_GETBUFPARAM_CMD_S));

            if (copy_from_user(&stCmd, argp, sizeof(PNG_GETBUFPARAM_CMD_S)))
            {
                return -EFAULT;
            }

            s32Ret = PngOsiGetBufParam(stCmd.s32Handle, &stCmd.u32PhyAddr, &stCmd.u32Size);
            if (s32Ret < 0)
            {
                return s32Ret;
            }

            if (copy_to_user(argp, &stCmd, sizeof(PNG_GETBUFPARAM_CMD_S)))
            {
                return -EFAULT;
            }

            return 0;
        }
        default:
        {
    	    return -EFAULT;
        }
    }
}

/* suspend */
static int png_pm_suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    return PngOsiSuspend();
}

/* resume */
static int png_pm_resume(PM_BASEDEV_S *pdev)
{
    return pngOsiResume();
}

/** ����������Ҫ�������� **/
#ifdef MODULE
module_init(PNG_DRV_ModInit);
module_exit(PNG_DRV_ModExit);
#endif

#ifndef HI_ADVCA_FUNCTION_RELEASE
MODULE_DESCRIPTION("driver for the all png");
MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");
MODULE_VERSION("V1.0.0.0");
#else
MODULE_DESCRIPTION("");
MODULE_AUTHOR("");
MODULE_LICENSE("GPL");
MODULE_VERSION("");
#endif
