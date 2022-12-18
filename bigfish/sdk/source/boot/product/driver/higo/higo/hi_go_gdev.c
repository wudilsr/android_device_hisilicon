
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


static HI_S32 HIGO_GetLayerSize(HI_HANDLE pLayer, HI_S32* pWidth, HI_S32* pHeight)
{

    HIGO_LAYER_REC_S* pLayerInstance = (HIGO_LAYER_REC_S*)pLayer;
    
    HIGO_ASSERT (pWidth  != NULL);
    HIGO_ASSERT (pHeight != NULL);
    
    if (pLayerInstance->hLayerSurface){
        Surface_GetSurfaceSize(pLayerInstance->hLayerSurface, pWidth, pHeight);
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
    HI_S32 s32Ret = HI_SUCCESS;    
    CHECK_GDEVINIT();
    CHECK_GDEV_NULLPTR(pLayerInfo);

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
    if (HI_SUCCESS != s32Ret){
        HIGO_ERROR(s32Ret);        
        return s32Ret;
    }
    
    HIGO_MemCopy(&ActRect, &FullRect, sizeof(HI_RECT));

    s32Ret = s_pGdevDevice->SetLayerSurface(Layer, (HIGO_SURFACE_S*)pLayerRec->hLayerSurface, &ActRect);
    if (HI_SUCCESS != s32Ret){
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }    
  
    return HI_SUCCESS;
}
