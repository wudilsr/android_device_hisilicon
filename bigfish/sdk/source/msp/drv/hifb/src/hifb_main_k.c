/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

******************************************************************************
  File Name     : hifb_main_k.c
  Version       : Initial Draft
  Author        : h180450
  Created       : 2013/6/9
  Last Modified :
  Description   : framebuffer export function for mce
  History       :
 
******************************************************************************/

#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/delay.h>

#include <linux/slab.h>
#include <linux/mm.h>

#include <linux/fb.h>
#include <asm/uaccess.h>

#include <asm/types.h>
#include <asm/stat.h>
#include <asm/fcntl.h>

#include <linux/interrupt.h>
#include "hi_module.h"
#include "hi_drv_module.h"

#include "drv_hifb_ext.h"
#include "drv_pdm_ext.h"
#include "hifb_p.h"
#include "optm_define.h"

/**
 **寄存器相关配置
 **/
#include "hifb_config.h"




#define HIFB_NAME "HI_FB"


#ifndef HI_ADVCA_FUNCTION_RELEASE
#define HIFB_PRINT_INFO  printk
#else
#define HIFB_PRINT_INFO(x...)
#endif

HI_VOID HifbSetLogoLayerEnable(HI_BOOL bEnable);
HI_S32 HifbUpdatePqData(HI_U32 u32UpdateType, PQ_PARAM_S* pstPqParam);

static volatile HI_U32 *g_u32HDLogoCtrlReg = HI_NULL;
static volatile HI_U32 *g_u32SDLogoCtrlReg = HI_NULL;
static volatile HI_U32 *g_u32SDCtrlReg   = HI_NULL;
static volatile HI_U32 *g_u32WBCCtrlReg  = HI_NULL;

static HIFB_EXPORT_FUNC_S s_HifbExportFuncs =
{
    .pfnHifbSetLogoLayerEnable             = HifbSetLogoLayerEnable,
    .pfnHifbUpdatePqData                   = HifbUpdatePqData,    
};

static HI_BOOL gs_bLogoOff = HI_FALSE;

HI_VOID HifbSetLogoLayerEnable(HI_BOOL bEnable)
{
    PDM_EXPORT_FUNC_S *ps_PdmExportFuncs = HI_NULL;
	
    if (bEnable) 
    {
        *g_u32HDLogoCtrlReg |= (0x1 << 31);
		*g_u32SDLogoCtrlReg |= (0x1 << 31);
        *g_u32SDCtrlReg   |= (0x1 << 31);
        *g_u32WBCCtrlReg  |= (0x1 << 31);

        *(g_u32HDLogoCtrlReg + 1) = 0x1;
		*(g_u32SDLogoCtrlReg + 1) = 0x1;
        *(g_u32SDCtrlReg + 1)   = 0x1;
        *(g_u32WBCCtrlReg + 1)  = 0x1;

    }
    else
    {
    	if (gs_bLogoOff)
		{
			return;
		}
		
        *g_u32HDLogoCtrlReg &= ~(0x1 << 31);
		*g_u32SDLogoCtrlReg &= ~(0x1 << 31);
        *g_u32SDCtrlReg   &= ~(0x1 << 31);
        *g_u32WBCCtrlReg  &= ~(0x1 << 31);

        *(g_u32HDLogoCtrlReg + 1) = 0x1;
		*(g_u32SDLogoCtrlReg + 1) = 0x1;
        *(g_u32SDCtrlReg + 1)   = 0x1;
        *(g_u32WBCCtrlReg + 1)  = 0x1;

		gs_bLogoOff = HI_TRUE;
	
        msleep(40);

        /* free the reserve memory*/
        if (HI_SUCCESS != HI_DRV_MODULE_GetFunction(HI_ID_PDM, (HI_VOID**)&ps_PdmExportFuncs))
        {
        	return;
        }
		
        if(HI_NULL != ps_PdmExportFuncs)
        {
            ps_PdmExportFuncs->pfnPDM_ReleaseReserveMem(DISPLAY_BUFFER_HD);
			ps_PdmExportFuncs->pfnPDM_ReleaseReserveMem(DISPLAY_BUFFER_SD);
            ps_PdmExportFuncs->pfnPDM_ReleaseReserveMem(OPTM_GFX_WBC2_BUFFER);
            ps_PdmExportFuncs->pfnPDM_ReleaseReserveMem(HIFB_ZME_COEF_BUFFER);
        }
    }

    return;
}


/***************************************************************************************
* func          : hifb_init_module_k
* description   : CNcomment: 加载KO的初始化 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 hifb_init_module_k(HI_VOID)
{
    HI_S32 ret;
	/** 高清层logo地址映射,只映射32位 **/
    g_u32HDLogoCtrlReg  = (HI_U32*)ioremap_nocache(CONFIG_HIFB_HD_LOGO_REG_BASEADDR, 8);
	g_u32SDLogoCtrlReg  = (HI_U32*)ioremap_nocache(CONFIG_HIFB_SD_LOGO_REG_BASEADDR, 8);
	g_u32SDCtrlReg       = (HI_U32*)ioremap_nocache(CONFIG_HIFB_WBC_SLAYER_REG_BASEADDR, 8);
	g_u32WBCCtrlReg      = (HI_U32*)ioremap_nocache(CONFIG_HIFB_WBC_GP0_REG_BASEADDR, 8);
	/** 函数导出 **/
    ret = HI_GFX_MODULE_Register(HIGFX_FB_ID, HIFB_NAME, &s_HifbExportFuncs); 
    if (HI_SUCCESS != ret)
    {
        HIFB_PRINT_INFO("HI_DRV_MODULE_Register failed\n");
        hifb_cleanup_module_k();
        return ret;
    }
    return HI_SUCCESS;
}

HI_VOID hifb_cleanup_module_k(HI_VOID)
{
    HI_GFX_MODULE_UnRegister(HIGFX_FB_ID);
    iounmap(g_u32HDLogoCtrlReg);
	iounmap(g_u32SDLogoCtrlReg);
	iounmap(g_u32SDCtrlReg);
	iounmap(g_u32WBCCtrlReg);
}

extern HIFB_DRV_OPS_S s_stDrvOps;
#define HIFB_DISPCHN_HD 1
#define HIFB_DISPCHN_SD 0
HI_S32 HifbUpdatePqData(HI_U32 u32UpdateType, PQ_PARAM_S* pstPqParam)
{/** 98M/hifone should no set defliker,pq set by self**/
#ifdef HI_PQ_V1_0
    switch (u32UpdateType)
    {
        case PQ_CMD_VIRTUAL_GFX_DEFLICKER:
        {
            if(pstPqParam->stPQCoef.stGfxCoef.u32HdCtrlEn)
            {
                s_stDrvOps.HIFB_DRV_SetGpDeflicker(HIFB_DISPCHN_HD, HI_TRUE);
            }
            else
            {
                s_stDrvOps.HIFB_DRV_SetGpDeflicker(HIFB_DISPCHN_HD, HI_FALSE);
            }
            
            if(pstPqParam->stPQCoef.stGfxCoef.u32SdCtrlEn)
            {
                s_stDrvOps.HIFB_DRV_SetGpDeflicker(HIFB_DISPCHN_SD, HI_TRUE);
            }
            else
            {
                s_stDrvOps.HIFB_DRV_SetGpDeflicker(HIFB_DISPCHN_SD, HI_FALSE);
            }
            break;
        }
        default:
            break;
     }
#endif

    return HI_SUCCESS;
} 
