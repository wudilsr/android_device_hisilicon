
/**
 \file
 \brief bliter module
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2012 - 2012
 \version  draft
 \author h180450
 \date 2012-11-2
 */
 
#include "hi_go_gdev.h"
#include "higo_gdev.h"
#include "adp_gfx.h"
#include "adp_layer.h"
#include "higo_surface.h"
#include "hi_tde_api.h"


static HIGO_LAYER_ADP_S s_struGdevDevice;

/** 图层操作函数集全局指针 */
static HIGO_LAYER_ADP_S* s_pGdevDevice = HI_NULL_PTR;

#define CHECK_GDEVINIT() \
do \
{  \
    if (UN_INIT_STATE == s_InitLayerCount) \
    { \
        HIGO_ERROR(HIGO_ERR_NOTINIT); \
        return HIGO_ERR_NOTINIT; \
    } \
} \
while(0)

#define CHECK_GDEV_NULLPTR(ptr) \
do\
{\
    if (NULL == ptr)\
    {\
        HIGO_ERROR(HIGO_ERR_NULLPTR);\
        return HIGO_ERR_NULLPTR;\
    }\
}\
while (0)

//static HIFB_DRV_OPS_S s_stDrvOps;
static HI_S32 s_InitLayerCount = 0;
//static HI_S32 s_InitDisplayCount = 0;
/** 图层数据数组 */
static HIGO_LAYER_REC_S s_LayerRec[HIGO_LAYER_MAXCOUNT]; 

#ifndef HIGO_CODE_CUT
static HI_S32 HIGO_CheckCanvas(const HIGO_LAYER_INFO_S *pLayerInfo,const HIGO_LAYER_CAP_S* pstruLayerCap)
{
    /** 如果非0，并且不在范围内无效*/
    if (pLayerInfo->CanvasWidth * pLayerInfo->CanvasHeight == 0)
        return HI_SUCCESS;
        
    if ((pLayerInfo->CanvasWidth < pstruLayerCap->MinWidth) || (pLayerInfo->CanvasHeight < pstruLayerCap->MinHeight) || \
        (pLayerInfo->CanvasWidth > pstruLayerCap->MaxWidth) || (pLayerInfo->CanvasHeight > pstruLayerCap->MaxHeight))
    {
        HIGO_ERROR(HIGO_ERR_INVSIZE);
        return HIGO_ERR_INVSIZE;
    }
    return HI_SUCCESS;
}

static HI_S32 HIGO_CheckDisplay(const HIGO_LAYER_INFO_S *pLayerInfo, const HIGO_LAYER_CAP_S* pstruLayerCap)
{
    if (pLayerInfo->LayerFlushType == HIGO_LAYER_BUFFER_SINGLE)
    {
        return HI_SUCCESS;
    }
    
    if ((pLayerInfo->DisplayWidth < pstruLayerCap->MinWidth) || (pLayerInfo->DisplayHeight < pstruLayerCap->MinHeight) ||\
    (pLayerInfo->DisplayWidth > pstruLayerCap->MaxWidth) || (pLayerInfo->DisplayHeight > pstruLayerCap->MaxHeight))
    {
        HIGO_ERROR(HIGO_ERR_INVSIZE);
        return HIGO_ERR_INVSIZE;
    }
    return HI_SUCCESS;
}


static HI_S32 HIGO_CheckScreen(HIGO_LAYER_INFO_S *pLayerInfo, const HIGO_LAYER_CAP_S* pstruLayerCap)
{
    if ((pLayerInfo->ScreenWidth < pstruLayerCap->MinWidth) || (pLayerInfo->ScreenHeight < pstruLayerCap->MinHeight) ||\
    (pLayerInfo->ScreenWidth > pstruLayerCap->MaxWidth) || (pLayerInfo->ScreenHeight > pstruLayerCap->MaxHeight))
    {
        HIGO_ERROR(HIGO_ERR_INVSIZE);
        return HIGO_ERR_INVSIZE;
    }

    /** 如果不支持缩放，必须保证screen size is same with display size
     for x5v200 vo only support vertical scale, so we should check screen width and display width*/
    if (pstruLayerCap->bVoScale !=  HI_TRUE)            
    {
        if (pLayerInfo->LayerFlushType != HIGO_LAYER_BUFFER_SINGLE)
        {
            /** 多buffer模式下与display buffer相同*/
            pLayerInfo->ScreenHeight = pLayerInfo->DisplayHeight;
            pLayerInfo->ScreenWidth  = pLayerInfo->DisplayWidth;
        }
        //HIGO_TRACE("vo unsupport scale, the display size will be the sampe with display size\n");
    }
    return HI_SUCCESS;
}

static HI_S32 HIGO_CheckFlushType(HIGO_LAYER_INFO_S *pLayerInfo)
{
    if ((pLayerInfo->LayerFlushType & HIGO_LAYER_BUFFER_OVER ) == HIGO_LAYER_BUFFER_OVER)
    {
        pLayerInfo->LayerFlushType = (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_OVER;	
    }
    else if ((pLayerInfo->LayerFlushType & HIGO_LAYER_BUFFER_TRIPLE ) == HIGO_LAYER_BUFFER_TRIPLE)
    {
        pLayerInfo->LayerFlushType = (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_TRIPLE;
    }
    else if((pLayerInfo->LayerFlushType & HIGO_LAYER_BUFFER_DOUBLE) == HIGO_LAYER_BUFFER_DOUBLE)
    {
        pLayerInfo->LayerFlushType = (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_DOUBLE;
    }
    else if((pLayerInfo->LayerFlushType & HIGO_LAYER_BUFFER_SINGLE) == HIGO_LAYER_BUFFER_SINGLE)
    {
        pLayerInfo->LayerFlushType = (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_SINGLE;
    }
    else
    {
        HIGO_ERROR(HIGO_ERR_INVFLUSHTYPE);
        return HIGO_ERR_INVFLUSHTYPE;
    }
    
    return  HI_SUCCESS;
}

static HI_BOOL LAYER_CheckFmt(HI_U32 LayerID, HIGO_PF_E enFmt)
{
    HI_S32 i;
    HIGO_LAYER_CAP_S* pstruLayerCap = HI_NULL_PTR;

    s_pGdevDevice->CapabilityInquire(LayerID, &pstruLayerCap);
    for (i = 0; i < pstruLayerCap->u8FmtCount; i++)
    {
        if (enFmt == *(pstruLayerCap->enPixelFmt + i))
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}

static HI_S32 HIGO_CheckParam(HIGO_LAYER_INFO_S *pLayerInfo)
{
    HIGO_LAYER_CAP_S* pstruLayerCap = HI_NULL_PTR;
    HI_S32 s32Ret;
    
    if (pLayerInfo->AntiLevel >= HIGO_LAYER_DEFLICKER_BUTT)
    {
        HIGO_ERROR(HIGO_ERR_INVANILEVEL);
        return HIGO_ERR_INVANILEVEL;
    }

    if (pLayerInfo->PixelFormat >= HIGO_PF_BUTT)
    {
        HIGO_ERROR(HIGO_ERR_INVPIXELFMT);
        return HIGO_ERR_INVPIXELFMT;
    }

    if (pLayerInfo->LayerID >= HIGO_LAYER_ID_BUTT)
    {
        HIGO_ERROR(HIGO_ERR_INVLAYERID);
        return HIGO_ERR_INVLAYERID;
    }
    
    if (HI_TRUE != LAYER_CheckFmt(pLayerInfo->LayerID, pLayerInfo->PixelFormat))
    {
        HIGO_ERROR(HIGO_ERR_INVPIXELFMT);
        return HIGO_ERR_INVPIXELFMT;
    }

    s_pGdevDevice->CapabilityInquire(pLayerInfo->LayerID, &pstruLayerCap);

    s32Ret = HIGO_CheckFlushType(pLayerInfo);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }

    /** 非单buffer模式下，display buffer could not be 0*/
    s32Ret = HIGO_CheckCanvas(pLayerInfo, pstruLayerCap);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
    
    s32Ret = HIGO_CheckDisplay(pLayerInfo, pstruLayerCap);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }

    s32Ret = HIGO_CheckScreen(pLayerInfo, pstruLayerCap);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;
}

#endif
static HI_S32 HIGO_GetLayerSize(HI_HANDLE pLayer, HI_S32* pWidth, HI_S32* pHeight)
{
    /** canvas */
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerInstance = (HIGO_LAYER_REC_S*)pLayer;

    HIGO_ASSERT (pWidth != NULL);
    HIGO_ASSERT (pHeight != NULL);
    if (pLayerInstance->hLayerSurface)
    {
        s32Ret = Surface_GetSurfaceSize(pLayerInstance->hLayerSurface, pWidth, pHeight);
        if (HI_SUCCESS != s32Ret)
        {
            HIGO_ERROR(s32Ret);
            return HIGO_ERR_INVLAYERSURFACE;
        }
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}


HI_S32 HIGO_InitDisplay(HI_VOID)
{
    HI_S32 s32Ret;

    /** re initial  just remember the times*/
    if (UN_INIT_STATE != s_InitLayerCount)
    {
        /** */
        s_InitLayerCount++;
        return HI_SUCCESS;
    }
      
     /** 初始化图层适配层 */
    s32Ret = HIGO_ADP_CreateVideoDevice(&s_struGdevDevice);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
    
    s_pGdevDevice = &s_struGdevDevice;   
    s32Ret = s_pGdevDevice->InitDisplay();
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(HIGO_ERR_INITFAILED);
        return s32Ret;
    }
    
    s_InitLayerCount++;
    return HI_SUCCESS;    
}

HI_S32 HIGO_DinitDisplay(HI_VOID)
{
    //HI_S32 s32Ret;
    
    /** 去初始化图层适配层 */
    s_pGdevDevice->DeinitDisplay();

    /** re initial  just remember the times*/
    if (UN_INIT_STATE != s_InitLayerCount)
    {
        /** */
        s_InitLayerCount--;
        return HI_SUCCESS;
    }

    return HI_SUCCESS;
}

HI_S32 HI_GO_GetLayerDefaultParam (HIGO_LAYER_E LayerID, HIGO_LAYER_INFO_S *pLayerInfo)
{
    HI_S32 s32Ret;    
    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pLayerInfo);

    if (LayerID >= HIGO_LAYER_ID_BUTT)
    {
        HIGO_ERROR(HIGO_ERR_INVLAYERID);
        return HIGO_ERR_INVLAYERID;
    }
    s32Ret = s_pGdevDevice->GetDefautParam(LayerID, pLayerInfo);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
    
    return HI_SUCCESS;
    
}

HI_S32 HI_GO_DestroyLayer(HI_HANDLE Layer)
{
    HIGO_LAYER_REC_S* pLayerRec;

    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
    pLayerRec->bCreated = HI_FALSE;

    /** destroy adp layer*/
    s_pGdevDevice->DestroyLayer(pLayerRec->LayerID);  
    return HI_SUCCESS;
   // HIGO_DestroyLayerSuface();
    //HIGO_FreeDisplayBuffer();
}

HI_S32 HI_GO_CreateLayer (const HIGO_LAYER_INFO_S *pLayerInfo, HI_HANDLE* pLayer)
{
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    HI_U32 LayerId;
    HIGO_LAYER_INFO_S stLayerInfo = {0};

    CHECK_GDEVINIT();

    /** check the param*/
    CHECK_NULLPTR(pLayerInfo);
    CHECK_NULLPTR(pLayer);

    HIGO_MemCopy(&stLayerInfo, pLayerInfo, sizeof(HIGO_LAYER_INFO_S));
#ifndef HIGO_CODE_CUT  
    s32Ret = HIGO_CheckParam(&stLayerInfo);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    } 
#endif   
    LayerId = pLayerInfo->LayerID;
    pLayerRec = s_LayerRec + LayerId;
    HIGO_MemSet(pLayerRec, 0, sizeof(HIGO_LAYER_REC_S) );
    /** if create twice failed*/
    if (pLayerRec->bCreated == HI_TRUE)
    {
        *pLayer = pLayerRec->hLayer;
        return HI_SUCCESS;
    }

    pLayerRec->LayerID =  LayerId;
    HIGO_MemCopy (&(pLayerRec->LayerInfo), &stLayerInfo, sizeof(HIGO_LAYER_INFO_S ));
    
    /** create the layer*/
    s32Ret = s_pGdevDevice->CreateLayer(LayerId, &pLayerRec->LayerInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        goto err;
    }  
    
    *pLayer = (HI_HANDLE)pLayerRec;
    pLayerRec->bCreated = HI_TRUE;
    pLayerRec->hLayer = *pLayer;
    return HI_SUCCESS;
    
 err:   
    s_pGdevDevice->DestroyLayer(LayerId);
    return HI_FAILURE;
}

HI_S32 HI_GO_GetLayerSurface(HI_HANDLE Layer, HI_HANDLE *pSurface)
{
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;

    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pSurface);

    pLayerRec = (HIGO_LAYER_REC_S*)Layer;

    s32Ret = s_pGdevDevice->GetCanvasSurface(pLayerRec->LayerID, &pLayerRec->LayerInfo, pSurface);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }     

    pLayerRec->hLayerSurface = *pSurface;
    return HI_SUCCESS;
}

HI_S32 HI_GO_RefreshLayer(HI_HANDLE Layer, const HI_RECT* pRect)
{
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    HI_RECT ActRect = {0};
    HI_RECT FullRect = {0};
   
    CHECK_GDEVINIT();

    pLayerRec = (HIGO_LAYER_REC_S*)Layer;

    s32Ret = HIGO_GetLayerSize(Layer, &FullRect.w, &FullRect.h);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);        
        return s32Ret;
    }
    
    if (pRect == NULL)
    {
        HIGO_MemCopy(&ActRect, &FullRect, sizeof(HI_RECT));
    }
    else
    {
        s32Ret = HIGO_GetRealRect(&FullRect, pRect, &ActRect);
        if (HI_SUCCESS != s32Ret)
        {
            HIGO_ERROR(s32Ret);
             return s32Ret;
        }
    }   

    /**  attention : the rect is no clipped*/
    s32Ret = s_pGdevDevice->SetLayerSurface(Layer, (HIGO_SURFACE_S*)pLayerRec->hLayerSurface, &ActRect);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }    
  
    return HI_SUCCESS;
}

HI_S32 HI_GO_SetLayerPos(HI_HANDLE Layer, HI_U32 u32StartX, HI_U32 u32StartY)
{
#ifndef HIGO_CODE_CUT
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    
    CHECK_GDEVINIT();

    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
        /** 不可以为负数*/
    if((((HI_S32)u32StartX) < 0) || (((HI_S32)u32StartY) < 0))
    {   
        return HIGO_ERR_INVLAYERPOS;
    }

    /** 设置屏幕位置 */
    s32Ret = s_pGdevDevice->SetPos(pLayerRec->LayerID, u32StartX, u32StartY);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
#endif
    return HI_SUCCESS;
}

HI_S32 HI_GO_GetLayerPos(HI_HANDLE Layer, HI_U32 *pStartX, HI_U32 *pStartY)
{
#ifndef HIGO_CODE_CUT
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;

    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pStartX);
    CHECK_GDEV_NULLPTR(pStartY);

    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
    /** 获取屏幕位置 */
    s32Ret = s_pGdevDevice->GetPos(pLayerRec->LayerID, pStartX, pStartY);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
#endif
    return HI_SUCCESS;
}

HI_S32 HI_GO_SetDisplaySize(HI_HANDLE Layer, HI_U32 u32DWidth, HI_U32 u32DHeight)
{
#ifndef HIGO_CODE_CUT
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    HIGO_LAYER_CAP_S * pLayerCap;
    CHECK_GDEVINIT();

    pLayerRec = (HIGO_LAYER_REC_S*)Layer;

    if ((u32DWidth == 0) || (u32DHeight == 0))
    {
        HIGO_ERROR(HIGO_ERR_INVSIZE);
        return HIGO_ERR_INVSIZE;
    }
    
    /** 如果不支持后端缩放就直接返回失败*/
    s_pGdevDevice->CapabilityInquire(pLayerRec->LayerID, &pLayerCap);
    if ((u32DWidth > (HI_U32)pLayerCap->MaxDisplayWidth) || (u32DHeight > (HI_U32)pLayerCap->MaxDisplayHeight))
    {
        HIGO_ERROR(HIGO_ERR_INVSIZE);
        return HIGO_ERR_INVSIZE;
    }

    if ((u32DWidth  >(HI_U32)pLayerCap->MaxWidth) || (u32DWidth < (HI_U32)pLayerCap->MinWidth)||
        (u32DHeight > (HI_U32)pLayerCap->MaxHeight) || (u32DHeight <(HI_U32)pLayerCap->MinHeight))
    {
        HIGO_ERROR(HIGO_ERR_INVSIZE);
        return HIGO_ERR_INVSIZE;
    }
    
    s32Ret = s_pGdevDevice->SetDisplaySize(pLayerRec->LayerID, u32DWidth, u32DHeight);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }

    pLayerRec->LayerInfo.DisplayWidth = u32DWidth;
    pLayerRec->LayerInfo.DisplayHeight = u32DHeight;    
#endif
    return HI_SUCCESS;
    
}

HI_S32 HI_GO_GetDisplaySize(HI_HANDLE Layer, HI_U32 *pDWidth, HI_U32 *pDHeight)
{
#ifndef HIGO_CODE_CUT
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;

    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pDWidth);
    CHECK_GDEV_NULLPTR(pDHeight);    
    
    pLayerRec = (HIGO_LAYER_REC_S*)Layer;

    s32Ret = s_pGdevDevice->GetDisplaySize(pLayerRec->LayerID, pDWidth, pDHeight);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
#endif    
    return HI_SUCCESS;
}

HI_S32 HI_GO_SetScreenSize(HI_HANDLE Layer, HI_U32 u32SWidth, HI_U32 u32SHeight)
{
#ifndef HIGO_CODE_CUT
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    HIGO_LAYER_CAP_S* pstruLayerCap = HI_NULL_PTR;

    CHECK_GDEVINIT();
    
    if ((u32SWidth == 0)||(u32SHeight == 0))
    {
        HIGO_ERROR(HIGO_ERR_INVSIZE);
        return HIGO_ERR_INVSIZE;
    }
    pLayerRec = (HIGO_LAYER_REC_S*)Layer;

    s_pGdevDevice->CapabilityInquire(pLayerRec->LayerID, &pstruLayerCap);
    if ((u32SWidth  >(HI_U32) pstruLayerCap->MaxWidth) || (u32SWidth < (HI_U32)pstruLayerCap->MinWidth)||
        (u32SHeight > (HI_U32)pstruLayerCap->MaxHeight) || (u32SHeight < (HI_U32)pstruLayerCap->MinHeight))
    {
        HIGO_ERROR(HIGO_ERR_INVSIZE);
        return HIGO_ERR_INVSIZE;
    }

    pLayerRec->LayerInfo.ScreenWidth = u32SWidth;
    pLayerRec->LayerInfo.ScreenHeight = u32SHeight;
    
    s32Ret = s_pGdevDevice->SetScreenSize(pLayerRec->LayerID, u32SWidth, u32SHeight);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
#endif
    return HI_SUCCESS;
}

HI_S32 HI_GO_GetScreenSize(HI_HANDLE Layer, HI_U32 *pSWidth, HI_U32 *pSHeight)
{
#ifndef HIGO_CODE_CUT
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    
    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pSWidth);
    CHECK_GDEV_NULLPTR(pSHeight);  

    pLayerRec = (HIGO_LAYER_REC_S*)Layer;

    s32Ret = s_pGdevDevice->GetScreenSize(pLayerRec->LayerID, pSWidth, pSHeight);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
 #endif
    return HI_SUCCESS;
}

HI_S32 HI_GO_SetLayerAlpha(HI_HANDLE Layer, HI_U8 Alpha)
{
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    HIGO_LAYER_ALPHA_S LayerALpha;
    
    CHECK_GDEVINIT();

    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
   
   	HIGO_MemSet(&LayerALpha, 0, sizeof(HIGO_LAYER_ALPHA_S));
	s32Ret = s_pGdevDevice->GetLayerAlpha(pLayerRec->LayerID, &LayerALpha);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }

	LayerALpha.bAlphaEnable = HI_TRUE;
	LayerALpha.bAlphaChannel = HI_TRUE;
	LayerALpha.GlobalAlpha  =  Alpha;

    /** 在直接设置硬件ALPHA */    
    s32Ret = s_pGdevDevice->SetLayerAlpha(pLayerRec->LayerID, &LayerALpha);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }    
 
    return HI_SUCCESS;

}

HI_S32 HI_GO_GetLayerAlpha(HI_HANDLE Layer, HI_U8* pAlpha)
{
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    HIGO_LAYER_ALPHA_S LayerALpha;    

    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pAlpha);

    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
    s32Ret = s_pGdevDevice->GetLayerAlpha(pLayerRec->LayerID, &LayerALpha);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
    
    *pAlpha = LayerALpha.GlobalAlpha;
    return HI_SUCCESS;
}

HI_S32 HI_GO_SetLayerColorkey(HI_HANDLE Layer, const HIGO_LAYER_KEY_S *pKey)
{
#ifndef HIGO_CODE_CUT
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    
    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pKey);
        
    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
    
    s32Ret = s_pGdevDevice->SetLayerColorKey(pLayerRec->LayerID, pKey->bEnableCK, pKey->ColorKey);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
#endif    
    return HI_SUCCESS;
}

HI_S32 HI_GO_GetLayerColorkey(HI_HANDLE Layer, HIGO_LAYER_KEY_S *pKey)
{
#ifndef HIGO_CODE_CUT
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;
    
    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pKey);
        
    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
    
    s32Ret = s_pGdevDevice->GetLayerColorKey(pLayerRec->LayerID, &(pKey->bEnableCK), &(pKey->ColorKey));
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
 #endif   
    return HI_SUCCESS;
}

#if 0
HI_S32 HI_GO_SetLayerBGColor(HI_HANDLE Layer, HI_COLOR Color)
{
    return HI_SUCCESS;
}


HI_S32 HI_GO_SetLayerAlphaEx(HI_HANDLE Layer,  HIGO_LAYER_ALPHA_S *pAlphaInfo)
{
    HIGO_LAYER_REC_S* pLayerRec;
    HIGO_DISPLAY_INFO_S *DisplayInfo;
    GRC_ALPHA_S pAlpha;
    
    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pAlphaInfo);
    
    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
    DisplayInfo = s_DisplayInfo + pLayerRec->LayerID;

    memcpy(&DisplayInfo->stAlpha, pAlphaInfo, sizeof(HIGO_LAYER_ALPHA_S));    

    pAlpha.bAlphaChannel = DisplayInfo->stAlpha.bAlphaChannel;
    pAlpha.bAlphaEnable = DisplayInfo->stAlpha.bAlphaEnable;
    pAlpha.u8Alpha0 = DisplayInfo->stAlpha.Alpha0;
    pAlpha.u8Alpha1 = DisplayInfo->stAlpha.Alpha1;
    pAlpha.u8GlobalAlpha = DisplayInfo->stAlpha.GlobalAlpha; 
    //update Alpha register
    Grc_DRV_SetLayerAlpha(pLayerRec->LayerID, &pAlpha);   
    Grc_DRV_UpdataLayerReg(pLayerRec->LayerID);    
    return HI_SUCCESS;	
}
HI_S32 HI_GO_GetLayerAlphaEx(HI_HANDLE Layer,  HIGO_LAYER_ALPHA_S *pAlphaInfo)
{
    HIGO_LAYER_REC_S* pLayerRec;
    HIGO_DISPLAY_INFO_S *DisplayInfo;
    
    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pAlphaInfo);
    
    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
    DisplayInfo = s_DisplayInfo + pLayerRec->LayerID;

    memcpy(pAlphaInfo, &DisplayInfo->stAlpha, sizeof(HIGO_LAYER_ALPHA_S));
        
    return HI_SUCCESS;	
} 
#endif
HI_S32 HI_GO_ShowLayer(HI_HANDLE Layer, HI_BOOL bVisbile)
{
    HI_S32 s32Ret;
    HIGO_LAYER_REC_S* pLayerRec;

    CHECK_GDEVINIT();
    
    pLayerRec = (HIGO_LAYER_REC_S*)Layer;

    /** 显示或隐藏图层 */
    s32Ret = s_pGdevDevice->ShowLayer(pLayerRec->LayerID, bVisbile);
    if (HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }

    return HI_SUCCESS;	
} 
