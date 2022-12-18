/**
\file
\brief surface manage module
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author a
\date 2009-12-26
*/
//lint -wlib(0)
#include "hi_go_surface.h"
#include "higo_surface.h"
/***************************** Macro Definition ******************************/
HI_BOOL g_bEnAutoSync = HI_TRUE;

/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/

HI_S32 HI_GO_CreateSurface(HI_S32 Width, HI_S32 Height, HIGO_PF_E PixelFormat, HI_HANDLE* pSurface)
{
    HI_S32 ret;
    HIGO_HANDLE Surface;
    HIGO_SURINFO_S SurInfo;
    HI_U32 u32PartNum = 0;
    /*config color key YUV and CLUT8 format memory */

    /** check parameters */
    if (HI_NULL == pSurface)
    {
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HIGO_ERR_NULLPTR;
    }

    /** width and heighe should >0 */
    if ((0 >= Width) || (0 >= Height))
    {
        HIGO_ERROR(HIGO_ERR_INVSURFACESIZE);
        return HIGO_ERR_INVSURFACESIZE;
    }
    if ((!IS_RGB_FORMAT(PixelFormat)) && (!IS_CLUT_FORMAT(PixelFormat)) && (!IS_ALPHA_FORMAT(PixelFormat)))
    {
        HIGO_ERROR(HIGO_ERR_INVSURFACEPF);
        return HIGO_ERR_INVSURFACEPF;
    }
    HIGO_MemSet(&SurInfo, 0, sizeof (HIGO_SURINFO_S));
    SurInfo.Width  = Width;
    SurInfo.Height = Height;
    SurInfo.PixelFormat = PixelFormat;

    ret = HIGO_CreateSurface(&SurInfo, HIGO_MOD_MEMSURFACE, &Surface, u32PartNum);
    if (ret != HI_SUCCESS)
    {
        HIGO_ERROR(ret);
        return ret;
    }

    *pSurface = Surface; 
    return HI_SUCCESS;
}

HI_S32 HI_GO_FreeSurface(HI_HANDLE Surface)
{
    HIGO_FreeSurface(Surface);
    return HI_SUCCESS;
}

HI_S32 HI_GO_CreateSurfaceFromMem(const HIGO_SURINFO_S *pSurInfo, HI_HANDLE * pSurface)
{
    HI_S32 ret;
    HIGO_HANDLE Surface;
#ifndef HIGO_CODE_CUT
    /** check parameters */
    if ((HI_NULL == pSurface) || (HI_NULL == pSurInfo))
    {
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HIGO_ERR_NULLPTR;
    }

    /** width and heighe should >0 */
    if ((0 >= pSurInfo->Width) || (0 >= pSurInfo->Height))
    {
        HIGO_ERROR(HIGO_ERR_INVSURFACESIZE);
        return HIGO_ERR_INVSURFACESIZE;
    }

    if ((!(IS_YUV_FORMAT(pSurInfo->PixelFormat))) && (!(IS_CLUT_FORMAT(pSurInfo->PixelFormat))) && (!(IS_RGB_FORMAT(pSurInfo->PixelFormat))))
    {
        HIGO_ERROR(HIGO_ERR_INVSURFACEPF);
        return HIGO_ERR_INVSURFACEPF;
    }

    if (!pSurInfo->Pitch[0] || !pSurInfo->pVirAddr[0] || !pSurInfo->pPhyAddr[0])
    {
        HIGO_ERROR(HIGO_ERR_INVPARAM);
        return HIGO_ERR_INVPARAM;
    }

    if (IS_YUV_FORMAT(pSurInfo->PixelFormat))
    {
        if (!pSurInfo->Pitch[1] || !pSurInfo->pVirAddr[1] || !pSurInfo->pPhyAddr[1])
        {
            HIGO_ERROR(HIGO_ERR_INVPARAM);
            return HIGO_ERR_INVPARAM;
        }
    }
#endif    
    ret = HIGO_CreateSurfaceFromMem(pSurInfo, HIGO_MOD_MEMSURFACE, &Surface);
    if (ret != HI_SUCCESS)
    {
        HIGO_ERROR(ret);
    	return ret;
    }
    
    *pSurface = Surface;
    return HI_SUCCESS;
}

HI_S32 HI_GO_LockSurface(HI_HANDLE Surface, HI_PIXELDATA pData,HI_BOOL bSync)
{
    return Surface_LockSurface(Surface, pData);
}

HI_S32 HI_GO_UnlockSurface(HI_HANDLE Surface)
{

    return Surface_UnlockSurface (Surface);
}

HI_S32 HI_GO_GetSurfaceSize(HI_HANDLE Surface, HI_S32* pWidth, HI_S32* pHeight)
{
    if ((HI_NULL == pWidth) && (HI_NULL == pHeight))
    {
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HIGO_ERR_NULLPTR;
    }

    return Surface_GetSurfaceSize (Surface, pWidth, pHeight);
}

HI_S32 HI_GO_GetSurfacePixelFormat(HI_HANDLE Surface, HIGO_PF_E* pPixelFormat)
{
    if (HI_NULL == pPixelFormat)
    {
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HIGO_ERR_NULLPTR;
    }

    return Surface_GetSurfacePixelFormat (Surface, pPixelFormat, HI_NULL);
}
