#ifndef __HI_BOOT_LOGO_H__
#define __HI_BOOT_LOGO_H__

#include "hi_common.h"
#include "hi_flash.h"
#include "hi_unf_disp.h"
//#include "hi_unf_hdmi.h"
#include "hi_go_gdev.h"
#include "hi_go_decoder.h"
#include "hi_go_bliter.h"
#include "hi_drv_pdm.h"


#ifdef __cplusplus
extern "C" {
#endif

#define HI_ERR_MCE(format...)     HI_ERR_PRINT(HI_ID_FASTPLAY, format)
#define HI_INFO_MCE(format...)    HI_INFO_PRINT(HI_ID_FASTPLAY, format)

HI_S32 HI_LOGO_DecImg(HI_LOGO_PARAM_S stLogoParam, HI_U32 u32LogoDataAddr, HI_HANDLE *hSurface);

#ifdef __cplusplus
}
#endif

#endif


