/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCDadN5jJKSuVyxmmaCmKFU6eJEbB2fyHF9weu4/jer/hxLHb+S1e
E0zVg4C3NiZh4b+GnwjAHj8JYHgZh/mRmQno22+dG7COxUFa9FUMSEmwiqyHLY6kItjWlyOj
ANaheE74sh4ijCJf/dutKCluJdvahRR8OP7KYpHE+prATDRD0akugQQfGSu8hzN3Vx2kN0xh
0qBt6t917T4eirzzGvPEA6cFZC5tEEKBIwW/fw0JmVal1rDITWCL3LaZG+bkNg==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/










#include "hi_type.h"
#include "hi_common.h"
#include "hi_module.h"
#include "hi_drv_module.h"
#include "hi_debug.h"
#include "syn_cmn.h"
#include "mem_manage.h"
#include "public.h"
//#include "syntax.h"

#include "vfmw.h"
#include "vfmw_svdec_ext.h"
#include "vfmw_debug.h"
#include "vfmw_ctrl.h"
#define SVDEC_NAME       "HI_SVDEC"

/* svdec use interface */
static VFMW_SVDEC_EXPORT_FUNC_S s_VfmwSvdecExportFuncs =
{
    .pfnVfmwKlibFlushCache          = klib_flush_cache,
    .pfnVfmwKernelFlushCache        = KernelFlushCache,
    .pfnVfmwMemMapRegisterAddr      = MEM_MapRegisterAddr,
    .pfnVfmwInsertImgToVoQueue      = InsertImgToVoQueue,
    #ifndef HI_ADVCA_FUNCTION_RELEASE
    .pfnVfmwDprint                  = dprint_vfmw,
    #else
    .pfnVfmwDprint                  = vfmw_dprint_nothing,
    #endif
    .pfnVfmwVctrlGetChanIDByCtx     = VCTRL_GetChanIDByCtx,
    .pfnVfmwMemVir2Phy              = MEM_Vir2Phy,
    .pfnVfmwMemPhy2Vir              = MEM_Phy2Vir,
    .pfnVfmwResetVoQueue            = ResetVoQueue,
    .pfnVfmwRegisterSoftDecoder     = VCTRL_RegisterSoftDecoder,
    .pfnVfmwUnRegisterSoftDecoder   = VCTRL_UnRegisterSoftDecoder,
    .pfnVfmwLastFrameNotify         = VCTRL_SvdecLastFrame,
};


HI_S32 VFMW_SVDE_DRV_Init(HI_VOID)
{
    HI_S32  ret;

    ret = HI_DRV_MODULE_Register(HI_ID_SVDEC, SVDEC_NAME, (HI_VOID*)&s_VfmwSvdecExportFuncs);
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_VFMW("HI_DRV_MODULE_SVDEC_Register failed\n");
        return ret;
    }

    HI_INFO_VFMW("inner vfmw mod init OK\n");
    return HI_SUCCESS;
}

HI_VOID VFMW_SVDEC_DRV_Exit(HI_VOID)
{
    HI_DRV_MODULE_UnRegister(HI_ID_SVDEC);
}

