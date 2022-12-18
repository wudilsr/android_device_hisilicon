/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : hi_go_bliter.c
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

#include "hi_type.h"
#include "hi_go_bliter.h"
#include "hi_go_comm.h"
#include "higo_common.h"
#include "higo_blit.h"
#include "adp_gfx.h"


/***************************** Macro Definition ******************************/


#define CHECK_BLITINIT() \
do \
{\
    if (UN_INIT_STATE == s_InitBlitCount) \
     {   HIGO_ERROR(HIGO_ERR_NOTINIT);\
        return HIGO_ERR_NOTINIT;\
     }\
}  \
while(0) 


#define CHECK_MIRRORTYPE(mirror) \
    if (mirror >= HIGO_MIRROR_BUTT) \
    { \
        HIGO_ERROR(HIGO_ERR_INVMIRRORTYPE);\
        return HIGO_ERR_INVMIRRORTYPE; \
    } 
    
#define CHECK_ROTATETYPE(rotate) \
    if (rotate >= HIGO_ROTATE_BUTT) \
    { \
        HIGO_ERROR(HIGO_ERR_INVROTATETYPE);\
         return HIGO_ERR_INVROTATETYPE;\
    }
    
#define CHECK_PALPHATYPE(palpha) \
    if (palpha >= HIGO_COMPOPT_BUTT) \
    { \
        HIGO_ERROR(HIGO_ERR_INVCOMPTYPE);\
        return HIGO_ERR_INVCOMPTYPE; \
    }

#define CHECK_COLORKEYTYPE(ckey) \
    if (ckey >= HIGO_CKEY_BUTT) \
    { \
        HIGO_ERROR(HIGO_ERR_INVCKEYTYPE);\
         return HIGO_ERR_INVCKEYTYPE;\
    }
#define CHECK_ROPTYPE(rop) \
    if (rop >= HIGO_ROP_BUTT) \
    { \
        HIGO_ERROR(HIGO_ERR_INVROPTYPE);\
         return HIGO_ERR_INVROPTYPE; \
    }

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

static HI_S32 s_InitBlitCount = 0;


/******************************* API declaration *****************************/
HI_S32 HIGO_InitBliter()
{
    HI_S32 s32Ret;

    /** re initial  just remember the times*/
    if (UN_INIT_STATE != s_InitBlitCount)
    {
        /** */
        s_InitBlitCount++;
        return HI_SUCCESS;
    }

    s32Ret = HIGO_ADP_InitBlitter();
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
    s_InitBlitCount++;
    return HI_SUCCESS;
}

HI_S32 HIGO_DeinitBliter()
{
    /** avoid no initial  */
    if (UN_INIT_STATE == s_InitBlitCount)
    {
        HIGO_ERROR(HIGO_ERR_NOTINIT);
        return HIGO_ERR_NOTINIT;
    }

    /** if has done initial,  exit */
    if (s_InitBlitCount != CLEAR_INIT_STATE)
    {   
        s_InitBlitCount--;
        return HI_SUCCESS;
    }
    
    HIGO_ADP_DeinitBlitter();
    s_InitBlitCount--;
    return HI_SUCCESS;
}

HI_S32 HI_GO_FillRect(HI_HANDLE Surface, const HI_RECT* pRect, HI_COLOR Color, HIGO_COMPOPT_E CompositeOpt)
{
    HIGO_HANDLE pSurface;
    HI_RECT OptRect;    
    HI_S32 ret;

    /** check is the module has been initialed  */
    CHECK_BLITINIT();

    /** check input parameters */
    CHECK_PALPHATYPE(CompositeOpt);
    
    pSurface = Surface;
    /** handle rectangle,  */
    HIGO_GetSurfaceRealRect(pSurface, pRect, &OptRect);

    ret = Bliter_FillRect(pSurface, &OptRect, Color, CompositeOpt);
    if (ret != HI_SUCCESS)
    {
        HIGO_ERROR(ret);
        return ret;
    }   
    return HI_SUCCESS;
    
}
static HI_BOOL IsVaildCombOpt(const HIGO_BLTOPT_S* pCompOpt)
{
    HI_U32 Opt = 0, Mirror = 0, Rotate = 0;

    if (pCompOpt->EnableGlobalAlpha || (pCompOpt->PixelAlphaComp != HIGO_COMPOPT_NONE))
    {
        Opt++;
    }
    if (pCompOpt->EnableRop)
    {
        Opt++;
    }
    if (pCompOpt->ColorKeyFrom != HIGO_CKEY_NONE)
    {
        Opt++;
    }
    if (pCompOpt->EnableScale)
    {
        Opt++;
    }
    
    if (pCompOpt->MirrorType != HIGO_MIRROR_NONE)
    {
        Mirror++;
    }

    if (pCompOpt->RotateType != HIGO_ROTATE_NONE)
    {
        Rotate++;
    }
    
    if ((Opt >= 1) && (Mirror >=1))
    {
       return HI_TRUE;
    }
    if ((Opt >= 1) && (Rotate >=1))
    {
       return HI_TRUE;
    }
    if ((Rotate >= 1) && (Mirror >=1))
    {
       return HI_TRUE;
    }
    return HI_FALSE;
        
}

HI_S32 HI_GO_Blit (HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                   HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                   const HIGO_BLTOPT_S* pBlitOpt)
{
    HIGO_HANDLE pSrcSurface, pDstSurface;
    HIGO_BLTOPT2_S BlitOpt2;
    HI_RECT OptSrcRect, OptDstRect;
    HI_S32 ret;
    HIGO_BLTOPT_S BlitOpt;

    
    /** check is the module has been initialed  */
    CHECK_BLITINIT();

    if (NULL != pBlitOpt)
    {
        HIGO_MemCopy(&BlitOpt, pBlitOpt, sizeof(HIGO_BLTOPT_S));
    }
    else
    {
        HIGO_MemSet(&BlitOpt, 0, sizeof(HIGO_BLTOPT_S));
    }

    pSrcSurface = SrcSurface;
    pDstSurface = DstSurface;
    /** check the mix is right */
    if (IsVaildCombOpt(&BlitOpt))
    {
        HIGO_ERROR(HIGO_ERR_UNSUPPORTED);
        ret = HIGO_ERR_UNSUPPORTED;
        goto RET;
    }

     /** handle source rectangle  */
    HIGO_GetSurfaceRealRect(pSrcSurface, pSrcRect, &OptSrcRect);

    /** handle target rectangle  */
    HIGO_GetSurfaceRealRect(pDstSurface, pDstRect, &OptDstRect);
    
    BlitOpt2.EnableGlobalAlpha = BlitOpt.EnableGlobalAlpha;
    BlitOpt2.PixelAlphaComp = BlitOpt.PixelAlphaComp;
    BlitOpt2.ColorKeyFrom = BlitOpt.ColorKeyFrom;
    BlitOpt2.EnableRop = BlitOpt.EnableRop;
    BlitOpt2.Rop =  BlitOpt.Rop;

    if (BlitOpt.EnableScale)
    {
        ret = Bliter_StretchBlit(pSrcSurface, &OptSrcRect, pDstSurface, &OptDstRect, &BlitOpt2);
    }
    else
    {
        ret = Bliter_Blit(pSrcSurface, &OptSrcRect, pDstSurface, &OptDstRect, &BlitOpt2);
        
    }

RET:
    return ret;
	
}
