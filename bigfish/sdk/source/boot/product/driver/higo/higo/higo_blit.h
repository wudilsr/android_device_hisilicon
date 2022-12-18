/**
 \file
 \brief blit core interface
 \copyright Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author w66592
 \date 2010-02-01
 */

#ifndef __HIGO_BLIT_H__
#define __HIGO_BLIT_H__

/* add include here */
#include "hi_go_bliter.h"
#include "higo_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/
typedef struct
{
    HI_RECT Rect;
    HI_COLOR Color;
}HIGO_OPRECT_S; 

typedef enum
{
    GFX_OPT_DRAWLINE = 0,  //draw line 
	GFX_OPT_FILLRECT,
    GFX_OPT_DRAWRECT,		
    GFX_OPT_DRAWCIRCLE,    
    GFX_OPT_DRAWELLIPSE, 
    GFX_OPT_BUTT
}GFX_OPT_TYPE_E;
/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

HI_S32 HIGO_InitBliter(HI_VOID);

HI_S32 HIGO_DeinitBliter(HI_VOID);

HI_S32 Bliter_Blit(HIGO_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                   HIGO_HANDLE DstSurface, const HI_RECT* pDstRect,
                   const HIGO_BLTOPT2_S* pBlitOpt);

HI_S32 Bliter_StretchBlit (HIGO_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                   HIGO_HANDLE DstSurface, const HI_RECT* pDstRect,
                   const HIGO_BLTOPT2_S* pBlitOpt);
HI_S32 Bliter_FillRect(HIGO_HANDLE pSurface, const HI_RECT* pRect, HI_COLOR Color, HIGO_COMPOPT_E CompositeOpt);
#ifdef TEST_IN_ROOTBOX
HI_S32 Bliter_GetPalIndex (HI_COLOR Color, HI_U8* pIndex, const HI_PALETTE Palette);
#endif
#ifdef __cplusplus
}
#endif
#endif /* __HIGO_BLIT_H__ */
