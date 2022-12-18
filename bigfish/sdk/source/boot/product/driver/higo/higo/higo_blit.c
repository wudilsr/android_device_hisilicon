/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : higo_blit.c
Version             : Initial Draft
Author              : 
Created             : 2014/08/06
Description         :
Function List       : 
History             :
Date                       Author                   Modification
2014/08/06                 y0081162                 Created file        
******************************************************************************/

/*********************************add include here******************************/

#include "higo_common.h"
#include "higo_blit.h"
#include "adp_gfx.h"
#include "higo_adp_sys.h"


/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

HI_S32 Bliter_Blit(HIGO_HANDLE SrcSurface, const HI_RECT * pSrcRect,
                   HIGO_HANDLE DstSurface, const HI_RECT * pDstRect,
                   const HIGO_BLTOPT2_S * pBlitOpt)
{
    HI_S32 s32Ret;

    s32Ret = HIGO_ADP_GFXBlit((HIGO_SURFACE_S * )SrcSurface, pSrcRect, (HIGO_SURFACE_S * )DstSurface, pDstRect, pBlitOpt);
    if (s32Ret == HI_SUCCESS)
    {
        return HI_SUCCESS;
    }
    
    if (HIGO_ERR_UNSUPPORTED != s32Ret)
    {
        return s32Ret;
    }

    return s32Ret;
}

HI_S32 Bliter_StretchBlit(HIGO_HANDLE SrcSurface, const HI_RECT * pSrcRect,
                   HIGO_HANDLE DstSurface, const HI_RECT * pDstRect,
                   const HIGO_BLTOPT2_S * pBlitOpt)
{
    HI_S32 s32Ret;

    s32Ret = HIGO_ADP_GFXStretchBlit((HIGO_SURFACE_S * )SrcSurface, pSrcRect, (HIGO_SURFACE_S * )DstSurface, pDstRect, pBlitOpt);
    if (s32Ret == HI_SUCCESS)
    {
        return HI_SUCCESS;
    }
    
    if (HIGO_ERR_UNSUPPORTED != s32Ret)
    {
        return s32Ret;
    }
     return s32Ret;
}


HI_S32 Bliter_FillRect(HIGO_HANDLE pSurface, const HI_RECT* pRect, HI_COLOR Color, HIGO_COMPOPT_E CompositeOpt)
{
    HI_S32 s32Ret ;
    HIGO_BLTOPT2_S BlitOpt;
    HIGO_OPRECT_S FillRect;

    HIGO_MemSet (&BlitOpt, 0 , sizeof(HIGO_BLTOPT2_S));
    BlitOpt.PixelAlphaComp = CompositeOpt;
    HIGO_MemCopy(&FillRect.Rect, pRect, sizeof (HI_RECT));
    FillRect.Color = Color;
    s32Ret = HIGO_ADP_GFXOperate((HIGO_SURFACE_S * )pSurface, GFX_OPT_FILLRECT, (const HI_VOID*)&FillRect, &BlitOpt);
    if (s32Ret == HI_SUCCESS)
    {
        return HI_SUCCESS;
    }

    if (HIGO_ERR_UNSUPPORTED != s32Ret)
    {
        return s32Ret;
    }
    return s32Ret;    
}
