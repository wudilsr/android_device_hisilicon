#ifndef __HI_BOOT_ADP_H__
#define __HI_BOOT_ADP_H__

#include "hi_drv_pdm.h"

#ifdef __cplusplus
extern "C" {
#endif


HI_S32 HI_ADP_DispInit(HI_VOID);
HI_S32 HI_ADP_GrcCreate(HIGO_PF_E enPixelFormat, HI_HANDLE *phLayer, HI_HANDLE *phSurface, HIGO_LAYER_E eLayerID);


#ifdef __cplusplus
}
#endif

#endif

