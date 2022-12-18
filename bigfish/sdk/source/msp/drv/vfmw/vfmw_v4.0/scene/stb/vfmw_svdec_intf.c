/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rYgDnWEYHdqiWpPUq+8h0NJ5vAPu/oxljuTsvJQOTqM/rc+aZJCW69Jife4y
0B+Jv71vOXtyZsEgOrQiuF1rPDbxgpOtpiFTlZH24nVaam7ClOrDrTsJLxGDBcveUje+9Pka
vn22/xZIrjCo/B/z9gIBR3klrneqgaeJFP1BEMaj1gJm4kTVunMLJR1KL6TzXw==#*/
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

