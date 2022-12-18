/**
\file
\brief 2D function adaptive layer
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author a
\date 2009-12-26
*/

#ifndef __ADP_GFX_H__
#define __ADP_GFX_H__

#include "higo_surface.h"
#include "higo_blit.h"
#include "hi_tde_type.h"
/* add include here */


#ifdef __cplusplus
extern "C" {
#endif
/***************************** Macro Definition ******************************/



/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/

/**  a collection about 2D module query function*/
HI_S32  HIGO_ADP_InitBlitter(HI_VOID);

HI_VOID  HIGO_ADP_DeinitBlitter(HI_VOID);

HI_S32 ADP_GFXBlitBility(const HIGO_SURFACE_S* pSrcSurface, const HIGO_SURFACE_S* pDstSurface, const HIGO_BLTOPT2_S* pBlitOpt);

HI_S32 ADP_GFXStretchBlitBility(const HIGO_SURFACE_S* pSrcSurface, const HIGO_SURFACE_S* pDstSurface, const HIGO_BLTOPT2_S* pBlitOpt);

HI_S32 ADP_GFXOperateBility(const HIGO_SURFACE_S* pDstSurface, const GFX_OPT_TYPE_E GfxOpt, const HIGO_BLTOPT2_S* pBlitOpt);
/**  a collection of operations about 2D module */
HI_S32 HIGO_ADP_GFXBlit(const HIGO_SURFACE_S* pSrcSurface, const HI_RECT *pSrcRect, const HIGO_SURFACE_S* pDstSurface, const HI_RECT *pDstRect, const HIGO_BLTOPT2_S* pBlitOpt);

HI_S32 HIGO_ADP_GFXStretchBlit(const HIGO_SURFACE_S* pSrcSurface, const HI_RECT *pSrcRect, const HIGO_SURFACE_S* pDstSurface, const HI_RECT *pDstRect, const  HIGO_BLTOPT2_S* pBlitOpt);

HI_S32 HIGO_ADP_GFXOperate(const HIGO_SURFACE_S* pDstSurface, const GFX_OPT_TYPE_E GfxOpt, const void * pInfo,const  HIGO_BLTOPT2_S* pBlitOpt);

HI_S32 ADP_ConvertFormat(HIGO_PF_E ColorFmt, TDE2_COLOR_FMT_E *pX5ColorFmt);

#ifdef __cplusplus
}
#endif
#endif /* __ADP_GFX_H__ */
