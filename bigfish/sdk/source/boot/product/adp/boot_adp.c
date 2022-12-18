#include <uboot.h>
#include "hi_common.h"
#include "hi_unf_disp.h"
#include "hi_go_gdev.h"
#include "hi_go_decoder.h"
#include "hi_go_bliter.h"
#include "hi_boot_logo.h"
#include "hi_boot_adp.h"
#include "hi_unf_hdmi.h"



HI_S32 HI_ADP_DispInit(HI_VOID)
{
    HI_S32                      Ret;

    Ret = HI_UNF_DISP_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_UNF_DISP_Init err! Ret = %x\n", Ret);
        goto ERR0;
    }
  
    Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY0);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_UNF_DISP_Open err! Ret = %x\n", Ret);
        goto ERR1; 
    }  
    
    Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY1);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_UNF_DISP_Open err! Ret = %x\n", Ret);
        goto ERR2; 
    }
    
    return Ret;

ERR2:
    HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
ERR1:
    HI_UNF_DISP_DeInit();
ERR0:
    return Ret;
}

HI_S32 HI_ADP_GrcCreate(HIGO_PF_E enPixelFormat, HI_HANDLE *phLayer, HI_HANDLE *phSurface, HIGO_LAYER_E eLayerID)
{
    HI_S32                      Ret;
    HIGO_LAYER_INFO_S           stLayerInfo;

    Ret = HI_GO_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_GO_Init err! Ret = %x\n", Ret);
        return Ret;
    }  
    
    Ret = HI_GO_GetLayerDefaultParam(eLayerID, &stLayerInfo);
    stLayerInfo.PixelFormat = enPixelFormat;
    Ret = HI_GO_CreateLayer(&stLayerInfo, phLayer);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_GO_CreateLayer err! Ret = %x\n", Ret);
        HI_GO_Deinit();
        return Ret;
    }

    /*use single buffer, need not blit*/
    Ret = HI_GO_GetLayerSurface(*phLayer, phSurface);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_GO_GetLayerSurface err! Ret = %x\n", Ret);
        HI_GO_DestroyLayer(*phLayer);
        HI_GO_Deinit();
        return Ret;        
    }
    
    Ret = HI_GO_FillRect(*phSurface, NULL, 0xff0000ff, HIGO_COMPOPT_NONE);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_GO_FillRect err! Ret = %x\n", Ret);
        HI_GO_DestroyLayer(*phLayer);
        HI_GO_Deinit();
        return Ret;        
    }   
    
    return Ret;
}

