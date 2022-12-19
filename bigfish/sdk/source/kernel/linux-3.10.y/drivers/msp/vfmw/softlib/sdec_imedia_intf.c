/*-----------------------------------------------------------------------*/
/*!!Warning: Hisilicon key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rYgDnWEYHdqiWpPUq+8h0NIQe0+PABsdaVBvBywkVW5G8adGW4T782mUyetR
ku9RbDwGY35I2hs4ecx0R510w0Qwnph/RJu5GUhSdlBnGwycsC08YPJtrz1+vy8/HKryoPt/
PJA74ixjl8UfmYuZA+aDf1Io/t5f1mUkO/lPnfAxG7dxstIQXzpbVAYGwEB9fg==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/
























/***********************************************************************
*
* Copyright (c) 2007 Hisilicon - All Rights Reserved
*
* File     : $sdec_imedia_ko.c$
* Date     : $2011/03/14$
* Revision : $v1.1$
* Purpose  : give a ko interface to the soft-dec-lib
*
* Change History:
*
* Date                       Author                          Change
* ====                       ======                          ====== 
* 2011/03/14                 z56361                          Original.
*
* Dependencies:
* Linux OS
*
************************************************************************/

//#include "vfmw_type.h"
#include "sdec_imedia.h"

#include "hi_drv_dev.h"

//#include "common_dev.h"
//#include "common_proc.h"
#include "hi_drv_proc.h"
#include "hi_common.h"
#include "hi_drv_module.h"
#include "vfmw_ctrl.h"
#include "vfmw_svdec_ext.h"

VFMW_SVDEC_EXPORT_FUNC_S* pVfmwToSvdecFun;

static UMAP_DEVICE_S g_SvdecRegisterData;

static struct file_operations SVDEC_FOPS =
{
    owner   : THIS_MODULE,
    open    : NULL,
    unlocked_ioctl :NULL,
    release : NULL,
};

//static struct himedia_baseops  SVDEC_drvops = {
static struct tagPM_BASEOPS_S SVDEC_drvops = {
	.probe        = NULL,
	.remove       = NULL,
	.shutdown     = NULL,
	.prepare      = NULL,
	.complete     = NULL,
	.suspend      = NULL,
	.suspend_late = NULL,
	.resume_early = NULL,
	.resume       = NULL,
};


HI_S32 SVDEC_ModeInit(HI_VOID)
{
	HI_S32 s32Ret;
    iMediaSDEC_FUNC_S  stSdecFunc;

    /* ÏòVFMW×¢²áÈí½âÂë¿â */
    stSdecFunc.pfun_iMediaSoftDEC_Create = iMediaSoftDEC_Create;
    stSdecFunc.pfun_iMediaSoftDEC_Destroy = iMediaSoftDEC_Destroy;
    stSdecFunc.pfun_iMediaSoftDEC_Init = iMediaSoftDEC_Init;
    stSdecFunc.pfun_iMediaSoftDEC_Decode = iMediaSoftDEC_Decode;
    stSdecFunc.pfun_iMediaSoftDEC_RecycleImage = iMediaSoftDEC_RecycleImage;
    stSdecFunc.pfun_iMediaSoftDEC_GetRemainImg = iMediaSoftDEC_GetRemainImg;
    stSdecFunc.pfun_iMediaSoftDEC_GetImageBuffer = iMediaSoftDEC_GetImageBuffer;

	/* get vfmw export functions for svdec */
    pVfmwToSvdecFun = HI_NULL;

    /* Get vfmw functions */
    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_SVDEC, (HI_VOID**)&(pVfmwToSvdecFun));
    if (HI_SUCCESS != s32Ret)
    {
#ifndef HI_ADVCA_FUNCTION_RELEASE
        printk("Get vfmw function err:%#x!\n", s32Ret);
#endif
        return HI_FAILURE;
    }

//    if (VDEC_OK != VCTRL_RegisterSoftDecoder( &stSdecFunc ))
	if(VDEC_OK != (pVfmwToSvdecFun->pfnVfmwRegisterSoftDecoder)(&stSdecFunc))
    {
#ifndef HI_ADVCA_FUNCTION_RELEASE
        printk("register soft vdec failed!\n");
#endif
        return HI_FAILURE;
    }

    /* ×¢²ávsdecÉè±¸ */
    sprintf(g_SvdecRegisterData.devfs_name, UMAP_DEVNAME_SVDEC);
	g_SvdecRegisterData.minor  = UMAP_MIN_MINOR_SVDEC;
	g_SvdecRegisterData.owner  = THIS_MODULE;
    g_SvdecRegisterData.fops   = &SVDEC_FOPS;
    g_SvdecRegisterData.drvops = &SVDEC_drvops;
    //if (CMPI_RegisterDevice(&g_SvdecRegisterData) < 0)
    if (HI_DRV_DEV_Register(&g_SvdecRegisterData) < 0)
    {
#ifndef HI_ADVCA_FUNCTION_RELEASE
        printk("register hi_vsdec failed!\n");
#endif
        return HI_FAILURE;
    }

#ifdef MODULE
#ifndef HI_ADVCA_FUNCTION_RELEASE
    HI_PRINT("Load hi_svdec.ko success.\t(%s)\n", VERSION_STRING);
#endif
#endif

    return 0;
}

HI_VOID SVDEC_ModeExit(HI_VOID)
{
    HI_S32 s32Ret;
    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_SVDEC, (HI_VOID**)&(pVfmwToSvdecFun));
    if (HI_SUCCESS != s32Ret)
    {
        return;
    }

	(pVfmwToSvdecFun->pfnVfmwUnRegisterSoftDecoder)();
//    VCTRL_UnRegisterSoftDecoder();
    //CMPI_UnRegisterDevice(&g_SvdecRegisterData);
    HI_DRV_DEV_UnRegister(&g_SvdecRegisterData);

    return;
}


#ifdef MODULE
module_init(SVDEC_ModeInit);
module_exit(SVDEC_ModeExit);
#else
EXPORT_SYMBOL(SVDEC_ModeInit);
EXPORT_SYMBOL(SVDEC_ModeExit);
#endif
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HISILICON");







