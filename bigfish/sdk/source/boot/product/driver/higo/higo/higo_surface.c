/**
 \file
 \brief surface core implement 
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author s37678
 \date 2008-5-19
 */

//lint -wlib(0)
#include "hi_type.h"

#include "hi_go_comm.h"
#include "hi_go_surface.h"
#include "higo_common.h"
#include "higo_surface.h"
#include "higo_adp_sys.h"
#include "higo_memory.h"

/***************************** Macro Definition ******************************/
#define MAKERGB(r, g, b) (0xff000000 | ((r) << 16) | ((g) << 8) | (b))


#define SURFACE_ALIGN_0  0
//#define SURFACE_ALIGN_1  1 
#define SURFACE_ALIGN_4  4
#define SURFACE_ALIGN_8  8
#define SURFACE_ALIGN_16 16
//#define SURFACE_ALIGN_64 64 
#define SURFACE_ALIGN_128 128

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

#ifndef HIGO_CODE_CUT
static HI_VOID CreateDefaultPalette(HI_PALETTE Palette)
{

    HI_U32 i = 0;
    HI_U32 offset[] = {
        0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF
    };
    HI_U8 r, g, b;

    HIGO_ASSERT(Palette != HI_NULL);

    Palette[i++] = MAKERGB(0, 0, 0);
    Palette[i++] = MAKERGB(128, 0, 0);
    Palette[i++] = MAKERGB(0, 128, 0);
    Palette[i++] = MAKERGB(128, 128, 0);
    Palette[i++] = MAKERGB(0, 0, 128);
    Palette[i++] = MAKERGB(128, 0, 128);
    Palette[i++] = MAKERGB(0, 128, 128);
    Palette[i++] = MAKERGB(128, 128, 128);
    Palette[i++] = MAKERGB(192, 192, 192);
    Palette[i++] = MAKERGB(255, 0, 0);
    Palette[i++] = MAKERGB(0, 255, 0);
    Palette[i++] = MAKERGB(255, 255, 0);
    Palette[i++] = MAKERGB(0, 0, 255);
    Palette[i++] = MAKERGB(255, 0, 255);
    Palette[i++] = MAKERGB(0, 255, 255);
    Palette[i++] = MAKERGB(255, 255, 255);

    for (; i < 40; i++)
    {
        Palette[i] = MAKERGB(0, 0, 0);
    }

    for (r = 0; r < 6; r++)
    {
        for (g = 0; g < 6; g++)
        {
            for (b = 0; b < 6; b++)
            {
                Palette[i++] = MAKERGB(offset[r], offset[g], offset[b]);
            }
        }
    }

    return;
} 
#endif


HI_VOID Surface_CalculateBpp0(HIGO_PF_E PixelFormat, HI_U32* pBpp)
{
    switch (PixelFormat)
    {
   /* case HIGO_PF_CLUT1:
    case HIGO_PF_CLUT4:
        *pBpp = 0;
        break;
    case HIGO_PF_CLUT8:
    case HIGO_PF_A8:
        *pBpp = 1;
        break;
*/
#ifndef HIGO_CODE_CUT
    case HIGO_PF_0444:
    case HIGO_PF_4444:
	case HIGO_PF_0555:
#endif
    case HIGO_PF_1555:
    //case HIGO_PF_0555:
    case HIGO_PF_565:
        *pBpp = 2;
        break;
    case HIGO_PF_8565:
        *pBpp = 3;
        break;        
    case HIGO_PF_8888:
        *pBpp = 4;
        break;
    case HIGO_PF_0888:
#ifndef RGB24
        *pBpp = 4;
#else
        *pBpp = 3;
#endif
        break;
    case HIGO_PF_YUV400:
    case HIGO_PF_YUV420:
    case HIGO_PF_YUV422:
    case HIGO_PF_YUV422_V:
    case HIGO_PF_YUV444:    
        *pBpp = 1;    
        break;       
    default:
        *pBpp = 0;
        return;
    }

    return;
}

HI_VOID Surface_CalculateBpp1(HIGO_PF_E PixelFormat, HI_U32* pBpp)
{
    switch (PixelFormat)
    {
   /* case HIGO_PF_CLUT1:
    case HIGO_PF_CLUT4:
    case HIGO_PF_CLUT8:
    case HIGO_PF_A8:
*/
    case HIGO_PF_0444:
    case HIGO_PF_4444:
    case HIGO_PF_1555:
    case HIGO_PF_0555:
    case HIGO_PF_565:
    case HIGO_PF_8565:
    case HIGO_PF_8888:
    case HIGO_PF_0888:
        *pBpp = 0;
        break;
    case HIGO_PF_YUV400:
        *pBpp = 1;
        break;
    case HIGO_PF_YUV420:
        *pBpp = 1;
        break;
    case HIGO_PF_YUV422:
        *pBpp = 1;
        break;    
    case HIGO_PF_YUV422_V:
        *pBpp = 2;    
        break;    
    case HIGO_PF_YUV444:    
        *pBpp = 2;    
        break;    
        
    default:
        *pBpp = 0;
        return;
    }

    return;
}
#ifndef HIGO_CODE_CUT
HI_VOID Surface_CalculateBitsPerPixel1(HIGO_PF_E PixelFormat, HI_U32* pBits)
{
    switch (PixelFormat)
    {
 /*   case HIGO_PF_CLUT1:
    case HIGO_PF_A1:
    case HIGO_PF_CLUT4:
    case HIGO_PF_CLUT8:
    case HIGO_PF_A8:
    
    case HIGO_PF_0444:
    case HIGO_PF_4444:*/
    case HIGO_PF_1555:
    case HIGO_PF_0555:
    case HIGO_PF_565:
    case HIGO_PF_8565:
    case HIGO_PF_8888:
    case HIGO_PF_0888:
        *pBits = 0;
        break;
    case HIGO_PF_YUV400:
        *pBits = 0;
        break;
    case HIGO_PF_YUV420:
        *pBits = 4;
        break;        
    case HIGO_PF_YUV422:
        *pBits = 8;
        break;        
    case HIGO_PF_YUV422_V:
        *pBits = 8;
        break;
    case HIGO_PF_YUV444:    
        *pBits = 16;    
        break;    
       
    default:
        *pBits = 0;
        return;
    }

    return;
}

#endif
HI_VOID Surface_CalculateBitsPerPixel0(HIGO_PF_E PixelFormat, HI_U32* pBits)
{
    switch (PixelFormat)
    {
 /*   case HIGO_PF_CLUT1:
    case HIGO_PF_A1:
        *pBits = 1;
        break;
    case HIGO_PF_CLUT4:
        *pBits = 4;
        break;
    case HIGO_PF_CLUT8:
    case HIGO_PF_A8:
        *pBits = 8;
        break;
        */
    case HIGO_PF_0444:
    case HIGO_PF_4444:
    case HIGO_PF_1555:
    case HIGO_PF_0555:
    case HIGO_PF_565:
        *pBits = 16;
        break;
    case HIGO_PF_8888:
        *pBits = 32;
        break;
    case HIGO_PF_0888:
#ifdef RGB24
        *pBits = 24;
#else
        *pBits = 32;
#endif
        break;
    case HIGO_PF_8565:
        *pBits = 24;    
        break;
   case HIGO_PF_YUV400:
    case HIGO_PF_YUV420:
    case HIGO_PF_YUV422:
    case HIGO_PF_YUV422_V:
    case HIGO_PF_YUV444:    
        *pBits = 8;    
        break; 
        
    default:
        *pBits = 0;
        return;
    }

    return;
}


HI_VOID Surface_CalculateStride0(HIGO_PF_E PixelFormat, HI_U32 Width, HI_U32 Height, HI_U32* pWStride, HI_U32* pHStride)
{
    HI_U32 BitPerPixel = 0;
    HI_U32 WAlign = SURFACE_ALIGN_0;
    HI_U32 HAlign = SURFACE_ALIGN_0;

    Surface_CalculateBitsPerPixel0(PixelFormat, &BitPerPixel);

    switch (PixelFormat)
    {
	    case HIGO_PF_0444:
	    case HIGO_PF_4444:
	    case HIGO_PF_1555:
	    case HIGO_PF_0555:
	    case HIGO_PF_565:
	    case HIGO_PF_8565:
	    case HIGO_PF_8888:
	    case HIGO_PF_0888:
	        WAlign = SURFACE_ALIGN_4;
	        HAlign = SURFACE_ALIGN_0;
	        break;
	    case HIGO_PF_YUV400:
	        WAlign = SURFACE_ALIGN_128;
	        HAlign = SURFACE_ALIGN_8;
	        break;
	    case HIGO_PF_YUV420:
	        WAlign = SURFACE_ALIGN_128;
	        HAlign = SURFACE_ALIGN_16;
	        break;
	    case HIGO_PF_YUV422:
	        WAlign = SURFACE_ALIGN_128;
	        HAlign = SURFACE_ALIGN_8;
	        break;
	    case HIGO_PF_YUV422_V:
	        WAlign = SURFACE_ALIGN_128;
	        HAlign = SURFACE_ALIGN_16;
	        break;
	    case HIGO_PF_YUV444:    
	        WAlign = SURFACE_ALIGN_128;
	        HAlign = SURFACE_ALIGN_8;
	        break;
	    default:
	        return;
    }
    
    *pWStride = (((Width * BitPerPixel + 7 )>>3) + (WAlign - 1))&(~(WAlign - 1));

    if (HAlign != 0)
    {
        *pHStride = (Height + HAlign - 1)&(~(HAlign - 1));
    }
    else
    {
        *pHStride = Height;
    }
    return;    

}

HI_VOID Surface_CalculateStride1(HIGO_PF_E PixelFormat, HI_U32 Width, HI_U32 Height, HI_U32* pWStride, HI_U32* pHStride)
{

    HI_U32 WStride, HStride;
    
    Surface_CalculateStride0(PixelFormat, Width, Height, &WStride, &HStride);
    
    switch (PixelFormat)
    {
   /* case HIGO_PF_CLUT1:
    case HIGO_PF_A1:
    case HIGO_PF_CLUT4:
    case HIGO_PF_CLUT8:
    case HIGO_PF_A8:*/
    case HIGO_PF_0444:
    case HIGO_PF_4444:
    case HIGO_PF_1555:
    case HIGO_PF_0555:
    case HIGO_PF_565:
    case HIGO_PF_8565:
    case HIGO_PF_8888:
    case HIGO_PF_0888:
        *pWStride = 0;
        *pHStride = 0;
        return;
    case HIGO_PF_YUV400:
        *pWStride = 0;
        *pHStride = 0;
        break;
    case HIGO_PF_YUV420:
        *pWStride = WStride;
        *pHStride = HStride>>1;
        break;
    case HIGO_PF_YUV422:
        *pWStride = WStride;
        *pHStride = HStride;
        break;
    case HIGO_PF_YUV422_V:
        *pWStride = WStride<<1;
        *pHStride = HStride>>1;
        break;
    case HIGO_PF_YUV444:    
        *pWStride = WStride<<1;
        *pHStride = HStride;
        break;
    default:
        return;
    }

    return;    

}


HI_VOID Surface_SetSurfaceType(HIGO_HANDLE Surface, HIGO_SUR_TYPE_E Type)
{
    HIGO_SURFACE_S* pSurfaceInstance = (HIGO_SURFACE_S*) Surface;
    pSurfaceInstance->Type = Type;
}

HI_S32 Surface_CreateSurface(HIGO_HANDLE* pSurface, HI_S32 Width, HI_S32 Height, HIGO_PF_E PixelFormat)
{
    HIGO_SURFACE_S* pSurfaceInstance;

    /** ·ÖÅäÊµÀýÄÚ´æ */
    pSurfaceInstance = (HIGO_SURFACE_S*)HIGO_Malloc(sizeof(HIGO_SURFACE_S));
    if (HI_NULL == pSurfaceInstance)
    {
        HIGO_ERROR(HIGO_ERR_NOMEM);
        return HIGO_ERR_NOMEM;
    }

    HIGO_MemSet(pSurfaceInstance, 0, sizeof (HIGO_SURFACE_S));

    pSurfaceInstance->Model  = HIGO_MOD_BUTT;
    pSurfaceInstance->PixelFormat = PixelFormat;
    pSurfaceInstance->Alpha = 0xff;
    pSurfaceInstance->Width  = Width;
    pSurfaceInstance->Height = Height;
    pSurfaceInstance->ClipRect.w = Width;
    pSurfaceInstance->ClipRect.h = Height;
#ifndef HIGO_CODE_CUT
    if (/*(PixelFormat == HIGO_PF_CLUT8)||
        (PixelFormat == HIGO_PF_CLUT4)||
        (PixelFormat == HIGO_PF_CLUT1)*/0)
    {
        /** the address must be phyaddress, for TDE to use(adp_gfx.c ADP_MEMSurfaceToTDESurface)*/
 
        pSurfaceInstance->Palette = (HI_COLOR *)HIGO_MMZ_Malloc(sizeof(HI_PALETTE));
        pSurfaceInstance->pPhyPalette =  pSurfaceInstance->Palette;

        if (HI_NULL == pSurfaceInstance->Palette)
		{
            HIGO_ERROR(HIGO_ERR_NOMEM);
            HIGO_Free(pSurfaceInstance);
            return HIGO_ERR_NOMEM;
		}
        //printf("length:%d\n", sizeof(HI_PALETTE));
        CreateDefaultPalette(pSurfaceInstance->Palette);
	}
#endif
    *pSurface = (HIGO_HANDLE) pSurfaceInstance;

    return HI_SUCCESS;
}


HI_VOID Surface_SetSurfacePrivateData(HIGO_HANDLE Surface, HIGO_MOD_E Model, const HI_PIXELDATA pData)
{
    HIGO_SURFACE_S* pSurfaceInstance = (HIGO_SURFACE_S*) Surface;
    pSurfaceInstance->Model = Model;
    HIGO_MemCopy(pSurfaceInstance->Data, pData, sizeof(HI_PIXELDATA));
}

HI_VOID Surface_FreeSurfacePrivateData(HIGO_HANDLE Surface)
{
    HIGO_SURFACE_S* pSurfaceInstance = (HIGO_SURFACE_S*) Surface;

    /** sub surface no needed free */
    if (pSurfaceInstance->Type == HIGO_SUR_MEM_E)
    {
        /** free Surface privad data  */
        HIGO_MMZ_Free(pSurfaceInstance->Data[0].pData);

    }
    
    return;    
}

HI_VOID Surface_FreeSurface(HIGO_HANDLE Surface)
{
    HIGO_SURFACE_S* pSurfaceInstance;

    pSurfaceInstance = (HIGO_SURFACE_S*) Surface;

    if (HI_NULL != pSurfaceInstance)
    {
   		if (/*(pSurfaceInstance->PixelFormat == HIGO_PF_CLUT8)||
		    (pSurfaceInstance->PixelFormat == HIGO_PF_CLUT4)||
		    (pSurfaceInstance->PixelFormat == HIGO_PF_CLUT1)*/0)
		{
		    HIGO_MMZ_Free(pSurfaceInstance->Palette);

		}
        HIGO_Free (pSurfaceInstance);
    }

    return ;
}

HI_S32 Surface_SetSurfacePalette(HIGO_HANDLE Surface, const HI_PALETTE Palette)
{
    HIGO_SURFACE_S* p = (HIGO_SURFACE_S*) Surface;

    HIGO_ASSERT (HI_NULL != p);
    HIGO_ASSERT(HI_NULL != Palette);

    /* color paletten only be used in the case of 1/2/4/8bit  */
    if (!IS_CLUT_FORMAT(p->PixelFormat))
    {
        HIGO_ERROR(HIGO_ERR_INVSURFACEPF);
        return HIGO_ERR_INVSURFACEPF;
    }

    /* copy collor palette to surface */
    HIGO_MemCopy(p->Palette, Palette, sizeof(HI_PALETTE));

    return HI_SUCCESS;
}

HI_S32 Surface_SetSurfaceColorKey(HIGO_HANDLE Surface, HI_COLOR ColorKey)
{
    HIGO_SURFACE_S* p = (HIGO_SURFACE_S*) Surface;

    HIGO_ASSERT (HI_NULL != p);

    /** remember color key */
    p->HasColorKey = HI_TRUE;
    p->ColorKey = ColorKey;
    return HI_SUCCESS;
}

HI_S32 Surface_GetSurfaceColorKey(HIGO_HANDLE Surface, HI_COLOR* pColorKey)
{
    HIGO_SURFACE_S* p = (HIGO_SURFACE_S*) Surface;

    /** check parameter */
    HIGO_ASSERT (HI_NULL != pColorKey);
    HIGO_ASSERT (HI_NULL != p);

    if (HI_TRUE != p->HasColorKey)
    {
        HIGO_ERROR(HIGO_ERR_NOCOLORKEY);
        return HIGO_ERR_NOCOLORKEY;
    }

    *pColorKey = p->ColorKey;

    return HI_SUCCESS;
}

HI_S32 Surface_SetSurfaceAlpha(HIGO_HANDLE Surface, HI_U8 Alpha)
{
    HIGO_SURFACE_S* p = (HIGO_SURFACE_S*) Surface;

    HIGO_ASSERT (HI_NULL != p);

    /** record alpha channel value */
    p->Alpha = Alpha;
    return HI_SUCCESS;
}

HI_VOID Surface_GetSurfaceAlpha(HIGO_HANDLE Surface, HI_U8* pAlpha)
{
    HIGO_SURFACE_S* p = (HIGO_SURFACE_S*) Surface;

    HIGO_ASSERT (HI_NULL != p);
    HIGO_ASSERT (HI_NULL != pAlpha);

    /** return alpha channel */
    *pAlpha = p->Alpha;
    return;
}

HI_S32 Surface_LockSurface(HIGO_HANDLE Surface, HI_PIXELDATA pData)
{
    HIGO_SURFACE_S* p = (HIGO_SURFACE_S*) Surface;

    /** check parameter */
    HIGO_ASSERT (HI_NULL != pData);

    /**  copy pixel data  */
    HIGO_MemCopy(pData, p->Data, sizeof(HI_PIXELDATA));

    /** record lock status */
    p->Locked = HI_TRUE;
    return HI_SUCCESS;
}

HI_S32 Surface_UnlockSurface(HIGO_HANDLE Surface)
{
    HIGO_SURFACE_S* p = (HIGO_SURFACE_S*) Surface;

    if (!p->Locked)
    {
        HIGO_ERROR(HIGO_ERR_NOTLOCKED);
        return HIGO_ERR_NOTLOCKED;
    }

    /** record lock status */
    p->Locked = HI_FALSE;
    return HI_SUCCESS;
}

HI_VOID Surface_GetSurfaceSize(HIGO_HANDLE Surface, HI_S32* pWidth, HI_S32* pHeight)
{
    HIGO_SURFACE_S* p = (HIGO_SURFACE_S*) Surface;
    if (HI_NULL != pWidth){
        *pWidth = p->Width;
    }

    if (HI_NULL != pHeight){
        *pHeight = p->Height;
    }
}
HI_S32 Surface_GetSurfacePixelFormat(HIGO_HANDLE Surface, HIGO_PF_E* pPixelFormat, HI_U32* pBpp)
{
    HIGO_SURFACE_S* p = (HIGO_SURFACE_S*) Surface;

    HIGO_ASSERT (HI_NULL != pPixelFormat);

    *pPixelFormat = p->PixelFormat;

#ifndef HIGO_CODE_CUT
	/** deal with codecc **/
    if (pBpp)
    {
        Surface_CalculateBpp0(p->PixelFormat, pBpp);
    }
#endif

    return HI_SUCCESS;
}
