#ifndef __DRV_HIFB_EXT_H__
#define __DRV_HIFB_EXT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"

#include "drv_pq_define.h"


typedef HI_VOID  (*FN_HIFB_SetLogoLayerEnable)(HI_BOOL);
typedef HI_S32 (*FN_HIFB_UpdatePqData)(HI_U32 u32UpdateType,PQ_PARAM_S * pstPqParam);

typedef struct
{
    FN_HIFB_SetLogoLayerEnable             pfnHifbSetLogoLayerEnable;
    FN_HIFB_UpdatePqData                   pfnHifbUpdatePqData; 
} HIFB_EXPORT_FUNC_S;


HI_S32 HIFB_DRV_ModInit(HI_VOID);
HI_VOID HIFB_DRV_ModExit(HI_VOID);

HI_S32 hifb_init_module_k(HI_VOID);
HI_VOID hifb_cleanup_module_k(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__DRV_HIFB_EXT_H__*/
