/**
 \file
 \brief system initial 
 \copyright Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author s37678
 \date 2008-7-28
 */

//lint -wlib(0)
#include "hi_go.h"
#include "higo_common.h"
#include "higo_adp_sys.h"
#include "higo_surface.h"
#include "higo_blit.h"
#include "higo_gdev.h"

/***************************** Macro Definition ******************************/
#define HIGO_VER_MAJOR 2
#define HIGO_VER_MINOR 0
#define HIGO_VER_Z 1
#define HIGO_VER_P 2
#define HIGO_VER_A "a34"  /* for  release version £¬please use the words"final" */

#define MAKE_VER_BIT(x) # x
#define MAKE_MACRO2STR(exp) MAKE_VER_BIT(exp)
#define MAKE_VERSION \
    MAKE_MACRO2STR(HIGO_VER_MAJOR) "." \
    MAKE_MACRO2STR(HIGO_VER_MINOR) "." \
    MAKE_MACRO2STR(HIGO_VER_Z) "." \
    MAKE_MACRO2STR(HIGO_VER_P) " " HIGO_VER_A
/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/
const HI_CHAR* g_pszBuildTime = "This version is building at " __DATE__ " " __TIME__;

/******************************* API declaration *****************************/
extern HI_S32 HIGO_InitDecoder(HI_VOID);
extern HI_S32 HIGO_DeinitDecoder(HI_VOID);

HI_S32 HI_GO_Init()
{
    HI_S32 s32Ret = HI_SUCCESS;

    HIGO_InitSurface();

    s32Ret = HIGO_InitBliter();
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        goto fail0;
    }

    s32Ret = HIGO_InitDecoder();
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        goto fail4;
    }
    
    s32Ret = HIGO_InitDisplay();
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        goto fail4;
    }
    
    return HI_SUCCESS;
fail4:
    (HI_VOID)HIGO_DeinitBliter();
fail0:
    (HI_VOID)HIGO_DeinitSurface();
    return s32Ret;
}


HI_S32 HI_GO_Deinit()
{
    HI_S32 ret = HI_SUCCESS;
    ret = HIGO_DinitDisplay();
    ret |= HIGO_DeinitDecoder();
    ret |= HIGO_DeinitBliter();
    ret |= HIGO_DeinitSurface();
    if (ret != HI_SUCCESS)
    {
        HIGO_ERROR(ret);
        return ret;
    }
    return ret;
}

HI_S32 HIGO_GetRealRect(const HI_RECT* pSrcRect, const HI_RECT* pRect, HI_RECT* pRealRect)
{
    HI_REGION Src1Region, Src2Region, RealRegion;

    /** check is the input rectangle is valid */
    RECT2REGION(*pSrcRect, RealRegion);

    if (HI_NULL != pRect)
    {
        if ((0 >= pRect->w) || (0 >= pRect->h))
        {
            HIGO_ERROR(HIGO_ERR_EMPTYRECT);
            return HIGO_ERR_EMPTYRECT;
        }

        RECT2REGION (*pRect, Src1Region);
        Src2Region = RealRegion;

        RealRegion.l = HIGO_MAX(Src1Region.l, Src2Region.l);
        RealRegion.t = HIGO_MAX(Src1Region.t, Src2Region.t);

        RealRegion.r = HIGO_MIN(Src1Region.r, Src2Region.r);
        RealRegion.b = HIGO_MIN(Src1Region.b, Src2Region.b);

        if ((RealRegion.r < RealRegion.l) || (RealRegion.b < RealRegion.t))
        {
            HIGO_ERROR(HIGO_ERR_OUTOFBOUNDS);
            return HIGO_ERR_OUTOFBOUNDS;
        }
    }

    REGION2RECT (*pRealRect, RealRegion);
    return HI_SUCCESS;
}
