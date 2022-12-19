/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hifb_main.c
  Version       : Initial Draft
  Author        : W00198192
  Created       : 2011/12/07
  Last Modified :
  Description   : framebuffer common function
  History       :
  1.Date        : 2011/12/07
    Author      : W00198192
    Modification: Created file

******************************************************************************/

#include "hifb_comm.h"
#include "hi_drv_mmz.h"

static HI_VOID HI_GFX_ShowVersionK(HIGFX_MODE_ID_E ModID)
{
	#if !defined(CONFIG_GFX_COMM_VERSION_DISABLE) && !defined(CONFIG_GFX_COMM_DEBUG_DISABLE)
    	HI_CHAR MouleName[7][10] = {"tde","jpegdec","jpegenc","fb","png", "higo", "gfx2d"};
        HI_CHAR Version[160] ="SDK_VERSION:["MKMARCOTOSTR(SDK_VERSION)"] Build Time:["\
		__DATE__", "__TIME__"]";

    	if (ModID >= HIGFX_BUTT_ID)
    		return;
		GFX_Printk("Load hi_%s.ko success.\t(%s)\n", MouleName[ModID],Version);
		
		return;
		
	#endif
}
/***************************************************************************************
* func          : hifb_version
* description   : CNcomment: ��ӡ�汾�� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID hifb_version(HI_VOID) 
{
	HI_GFX_ShowVersionK(HIGFX_FB_ID);
}
/***************************************************************************************
* func          : hifb_buf_map
* description   : CNcomment: �ڴ�ӳ�� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID *hifb_buf_map(HI_U32 u32PhyAddr)
{
	return HI_GFX_Map(u32PhyAddr,0);
}

/***************************************************************************************
* func          : hifb_buf_ummap
* description   : CNcomment: �ڴ���ӳ�� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 hifb_buf_ummap(HI_VOID *pViraddr)
{
	return HI_GFX_Unmap(pViraddr);
}
/***************************************************************************************
* func          : hifb_buf_freemem
* description   : CNcomment: �ͷ��ڴ� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_VOID hifb_buf_freemem(HI_U32 u32Phyaddr)
{
	HI_GFX_FreeMem(u32Phyaddr);
}
/***************************************************************************************
* func          : hifb_buf_allocmem
* description   : CNcomment: �����ڴ� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_U32 hifb_buf_allocmem(HI_CHAR *pName, HI_U32 u32LayerSize)
{
	return HI_GFX_AllocMem(pName, "hifb", u32LayerSize);
}


inline HI_S32 HIFB_RectToRegion(const HIFB_RECT* pRect, HIFB_REGION* pRegion)
{
    pRegion->l = pRect->x;
    pRegion->t = pRect->y;
    pRegion->r = pRect->x + pRect->w;
    pRegion->b = pRect->y + pRect->h;
    if (pRegion->r < 0)
    {
        pRegion->r = 0;
    }

    if (pRegion->b < 0)
    {
        pRegion->b = 0;
    }

    return HI_SUCCESS;
}

inline HI_BOOL HIFB_IntersectRgn (const HIFB_REGION* psrc1, const HIFB_REGION* psrc2)
{
    HI_S32 left, top, right, bottom;

    top    = (psrc1->t > psrc2->t) ? psrc1->t : psrc2->t;
    left = (psrc1->l > psrc2->l) ? psrc1->l : psrc2->l;
    right  = (psrc1->r < psrc2->r) ? psrc1->r : psrc2->r;
    bottom = (psrc1->b < psrc2->b)
             ? psrc1->b : psrc2->b;

    if ((left >= right) || (top >= bottom))
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

inline HI_S32 HIFB_RegionToRect(const HIFB_REGION* pRegion, HIFB_RECT* pRect)
{
    pRect->x = pRegion->l;
    pRect->y = pRegion->t;
    pRect->w = pRegion->r - pRegion->l;
    pRect->h = pRegion->b - pRegion->t;
    return HI_SUCCESS;
}



inline HI_BOOL HIFB_IsIntersectRect(const HIFB_RECT* pRect1, const HIFB_RECT* pRect2)
{
    HIFB_REGION rc1;
    HIFB_REGION rc2;

    (HI_VOID)HIFB_RectToRegion(pRect1, &rc1);
    (HI_VOID)HIFB_RectToRegion(pRect2, &rc2);
    return HIFB_IntersectRgn(&rc1, &rc2);
}




/** Add rectangles, merge them if they can,  if the total counts of the rectangles more than max count and also can't merge,
we can merge them to the last rectangle*/
HI_VOID hifb_addrect(HIFB_RECT *pRectHead, HI_U32 TotalNum, HI_U32 *pValidNum, HIFB_RECT *pRect)
{
	HI_S32 Index;

    /** return, if the rectangle 's high or width is 0 */
	if ((0 == pRect->h) || (0 == pRect->w))
	{
		return;
	}

	/** scan all the rectangle and check if they can merge, if they can, just merge them and return */	
    for (Index = 0; Index < *pValidNum; Index++)
	{
        /** check if they cover each other */
		if (((pRect->x <= pRectHead[Index].x) 
			 && (pRect->x + pRect->w >= pRectHead[Index].x + pRectHead[Index].w)
			 && (pRect->y <= pRectHead[Index].y) 
			 && (pRect->y + pRect->h >= pRectHead[Index].y + pRectHead[Index].h))
			|| ((pRect->x >= pRectHead[Index].x) 
			 && (pRect->x + pRect->w <= pRectHead[Index].x + pRectHead[Index].w)
			 && (pRect->y >= pRectHead[Index].y) 
			 && (pRect->y + pRect->h <= pRectHead[Index].y + pRectHead[Index].h)))
		{
            HIFB_UNITE_RECT(pRectHead[Index], (*pRect)); 
			return;
		}


		/** check if they can merge by left and right */
        if ((pRect->y == pRectHead[Index].y)
			&& (((pRect->x <= pRectHead[Index].x) &&  (pRect->x + pRect->w >= pRectHead[Index].x))
			    || ((pRectHead[Index].x <= pRect->x) && (pRectHead[Index].x + pRectHead[Index].w >= pRect->x))))
		{
            HIFB_UNITE_RECT(pRectHead[Index], (*pRect)); 
			return;
		}


		/**  check if they can merge by up and down * */
		if ((pRect->x == pRectHead[Index].x)
			&& (((pRect->y <= pRectHead[Index].y) && (pRect->y + pRect->h >= pRectHead[Index].y)) 
			    || ((pRectHead[Index].y <= pRect->y) && (pRectHead[Index].y + pRectHead[Index].h >= pRect->y))))
		{
            HIFB_UNITE_RECT(pRectHead[Index], (*pRect)); 
			return;
		}
	}

	/** check if there is emputy rectangle to use, if yes, add , if no, merge it to the last rectangle */	
	if (*pValidNum < TotalNum)
	{
        pRectHead[*pValidNum] = *pRect;
		(*pValidNum)++;
	}
	else
	{
        HIFB_UNITE_RECT(pRectHead[*pValidNum - 1], (*pRect)); 
	}

	return;
}

/*check these two rectangle cover each other*/
HI_BOOL hifb_iscontain(HIFB_RECT *pstParentRect, HIFB_RECT *pstChildRect)
{
    HIFB_POINT_S stPoint;
    stPoint.s32XPos = pstChildRect->x;
    stPoint.s32YPos = pstChildRect->y;
    if ((stPoint.s32XPos < pstParentRect->x) || (stPoint.s32XPos > (pstParentRect->x + pstParentRect->w))
        || (stPoint.s32YPos < pstParentRect->y) || (stPoint.s32YPos > (pstParentRect->y + pstParentRect->h)))
    {
        return HI_FALSE;
    }
    stPoint.s32XPos = pstChildRect->x + pstChildRect->w;
    stPoint.s32YPos = pstChildRect->y + pstChildRect->h;
    if ((stPoint.s32XPos < pstParentRect->x) || (stPoint.s32XPos > (pstParentRect->x + pstParentRect->w))
        || (stPoint.s32YPos < pstParentRect->y) || (stPoint.s32YPos > (pstParentRect->y + pstParentRect->h)))
    {
        return HI_FALSE;
    }
    return HI_TRUE;
}

/***************************************************************************************
* func			: hifb_isoverlay
* description	: check these two rectangle overlay each other
* param[in] 	:
* retval		: NA
* others:		: NA
***************************************************************************************/
HI_BOOL hifb_isoverlay(HIFB_RECT *pstSrcRect, HIFB_RECT *pstDstRect)
{
    if (   pstSrcRect->x >= (pstDstRect->x + pstDstRect->w)
		|| pstDstRect->x >= (pstSrcRect->x + pstSrcRect->w))
    {
        return HI_FALSE;
    }

	if(    pstSrcRect->y >= (pstDstRect->y+pstDstRect->h)
		|| pstDstRect->y >= (pstSrcRect->y+pstSrcRect->h))
    {
        return HI_FALSE;
    }

	return HI_TRUE;	
}


/***************************************************************************************
* func          : hifb_getbppbyfmt
* description   : CNcomment:  CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_U32 hifb_getbppbyfmt(HIFB_COLOR_FMT_E enColorFmt)
{
    switch(enColorFmt)
    {
        case HIFB_FMT_RGB565:
        case HIFB_FMT_KRGB444: 
        case HIFB_FMT_KRGB555:
        case HIFB_FMT_ARGB4444:
        case HIFB_FMT_ARGB1555:
        case HIFB_FMT_RGBA4444:
        case HIFB_FMT_RGBA5551:
        case HIFB_FMT_ACLUT88:
        case HIFB_FMT_BGR565:
        case HIFB_FMT_ABGR1555:
        case HIFB_FMT_ABGR4444:
        case HIFB_FMT_KBGR444:
        case HIFB_FMT_KBGR555:
        {
            return 16;
        }
        case HIFB_FMT_RGB888:
        case HIFB_FMT_ARGB8565: 
        case HIFB_FMT_RGBA5658:
        case HIFB_FMT_ABGR8565:
        case HIFB_FMT_BGR888:              
        {
            return 24;
        }
        case HIFB_FMT_KRGB888:
        case HIFB_FMT_ARGB8888:
        case HIFB_FMT_RGBA8888:
        case HIFB_FMT_ABGR8888:
        case HIFB_FMT_KBGR888:            
        {
            return 32;
        }
        case HIFB_FMT_1BPP:
        {
            return 1;
        }
        case HIFB_FMT_2BPP:
        {
            return 2;
        }
        case HIFB_FMT_4BPP:
        {
            return 4;
        }
        case HIFB_FMT_8BPP:
        case HIFB_FMT_ACLUT44:
        {
            return 8;
        }
        default:
            return 0;   
    }
}


/***************************************************************************************
* func          : hifb_bitfieldcmp
* description   : CNcomment: �ж��������ظ�ʽ�Ƿ���� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
 HI_S32 hifb_bitfieldcmp(struct fb_bitfield x, struct fb_bitfield y)
{
    if (   (x.offset == y.offset)
        && (x.length == y.length)
        && (x.msb_right == y.msb_right))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
