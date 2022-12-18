/******************************************************************************

  Copyright (C), 2014-2024, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : OsdManager.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2014/02/18
  Description   :
  History       :
  1.Date        : 2014/02/18
    Author      : h00183514
    Modification: Created file

******************************************************************************/

#include "OsdManager.h"

namespace android {

static HI_VOID InitDispSurface(OSD_DISP_SURFACE_S *pstSurface)
{
#ifdef ANDROID44
    pstSurface->hSurface = HI_INVALID_HANDLE;
    pstSurface->stAttr.Width = SURFACE_DEFAULT_WIDTH;
    pstSurface->stAttr.Height = SURFACE_DEFAULT_HEIGHT;
    pstSurface->stAttr.PixelFormat = PIXEL_FORMAT_RGBA_8888;
    pstSurface->stAttr.Stride = SURFACE_DEFAULT_WIDTH * 4;    
#endif
}

static TDE2_COLOR_FMT_E FORMAT_TO_TDE(int aformat)
{
    TDE2_COLOR_FMT_E tdeformat = TDE2_COLOR_FMT_ARGB8888;
#ifdef ANDROID44
    switch(aformat)
    {
        case PIXEL_FORMAT_RGBA_8888:
            tdeformat = TDE2_COLOR_FMT_ARGB8888;
            break;
        case PIXEL_FORMAT_RGB_565:
            tdeformat = TDE2_COLOR_FMT_RGB565;
            break;
        case PIXEL_FORMAT_RGBA_5551:
            tdeformat = TDE2_COLOR_FMT_ARGB1555;
            break;
        case PIXEL_FORMAT_RGBA_4444:
            tdeformat = TDE2_COLOR_FMT_ARGB4444;
            break;
        default:
            tdeformat = TDE2_COLOR_FMT_ARGB8888;
    }

#endif
    return tdeformat;
}

static int tde_bytepp(int fmt)
{
#ifdef ANDROID44
    switch(fmt)
    {
        case TDE2_COLOR_FMT_ARGB8888:
        return 4;

        case TDE2_COLOR_FMT_ABGR8888:
        return 4;

        case TDE2_COLOR_FMT_RGB888:
        return 3;

        case TDE2_COLOR_FMT_RGB565:
        case TDE2_COLOR_FMT_ARGB1555:
        case TDE2_COLOR_FMT_ARGB4444:
        return 2;
    }

#endif
    return 4;
}


OsdManager::OsdManager()
{
#ifdef ANDROID44
    HI_U32  i;

    for (i = 0; i < MAX_SURFACE_NUM; i++)
    {
        // display surface source
        memset(&m_DispSurface[i], 0x0, sizeof(OSD_DISP_SURFACE_S));
        
        InitDispSurface(&m_DispSurface[i]);
    }

    HI_TDE2_Open();

    pPixels = HI_NULL;
#endif
}

OsdManager::~OsdManager()
{
#ifdef ANDROID44
    HI_TDE2_Close();

    if(HI_NULL !=pPixels)
    {
        free(pPixels);
    }
    
#endif
}

OSD_DISP_SURFACE_S *OsdManager::GetSurfaceInst(HI_HANDLE hSurface)
{
#ifdef ANDROID44
    HI_U32          i;
    
    for (i = 0; i < MAX_SURFACE_NUM; i++)
    {
        if (m_DispSurface[i].hSurface == hSurface)
        {
            return &(m_DispSurface[i]);            
        }
    }

#endif
    return HI_NULL;
}

HI_S32 OsdManager::CreateSurface(SURFACE_ATTR_S *pstAttr, HI_HANDLE *phSurface)
{
#ifdef ANDROID44
    HI_U32      i;
    
    for (i = 0; i < MAX_SURFACE_NUM; i++)
    {
        if (m_DispSurface[i].hSurface == HI_INVALID_HANDLE)
        {
            break;
        }
    }

    if (i == MAX_SURFACE_NUM)
    {
        ALOGE("there is no free display surface!\n");
        return HI_FAILURE;
    }

    // create new display surface
    m_DispSurface[i].Client = new SurfaceComposerClient();

    m_DispSurface[i].surfaceControl = (m_DispSurface[i].Client)->createSurface(String8("hisiSurfaceDemo"), pstAttr->Width, pstAttr->Height, pstAttr->PixelFormat, 0);

    m_DispSurface[i].surface = (m_DispSurface[i].surfaceControl)->getSurface();

    SurfaceComposerClient::openGlobalTransaction();
    (m_DispSurface[i].surfaceControl)->setLayer(300000 + i);
    (m_DispSurface[i].surfaceControl)->setPosition(0,0);

    (m_DispSurface[i].surfaceControl)->setFlags(0x20,0x20);
    
    SurfaceComposerClient::closeGlobalTransaction();    

    m_DispSurface[i].Window = m_DispSurface[i].surface.get();

    m_DispSurface[i].WindowBuffer = HI_NULL;

    memcpy(&(m_DispSurface[i].stAttr), pstAttr, sizeof(SURFACE_ATTR_S));

    m_DispSurface[i].hSurface = SURFACE_HANDLE_INDEX | i;
    
    *phSurface = m_DispSurface[i].hSurface;

#endif
    return HI_SUCCESS;
}

HI_S32 OsdManager::DestroySurface(HI_HANDLE hSurface)
{
#ifdef ANDROID44
    OSD_DISP_SURFACE_S      *pSurface = HI_NULL;

    pSurface = GetSurfaceInst(hSurface);
    if (pSurface == HI_NULL)
    {
        ALOGE("hSurface is invalid!\n");
        return HI_FAILURE;
    }

    InitDispSurface(pSurface);

#endif
    return HI_SUCCESS;
}

HI_S32 OsdManager::ClearSurface(HI_HANDLE hSurface)
{
#ifdef ANDROID44
    OSD_DISP_SURFACE_S      *pSurface = HI_NULL;

    pSurface = GetSurfaceInst(hSurface);
    if (pSurface == HI_NULL)
    {
        ALOGE("hSurface is invalid!\n");
        return HI_FAILURE;
    }
    
    if (pSurface->WindowBuffer == HI_NULL)
    {
        lock(hSurface);
    }

    memset(pSurface->VirtualAddr, 0x0, pSurface->stAttr.Stride*pSurface->stAttr.Height);

#endif
    return HI_SUCCESS;
}

HI_S32 OsdManager::lock(HI_HANDLE hSurface)
{
#ifdef ANDROID44
    OSD_DISP_SURFACE_S      *pSurface = HI_NULL;

    pSurface = GetSurfaceInst(hSurface);
    if (pSurface == HI_NULL)
    {
        ALOGE("hSurface is invalid!\n");
        return HI_FAILURE;
    }

    native_window_dequeue_buffer_and_wait(pSurface->Window, &(pSurface->WindowBuffer));

    GraphicBufferMapper &mapper = GraphicBufferMapper::get();

    Rect bounds(pSurface->stAttr.Width, pSurface->stAttr.Height);

    private_handle_t* priv_hnd = (private_handle_t*)((pSurface->WindowBuffer)->handle); 

    if (HI_NULL != priv_hnd)
    {
        pSurface->PhyAddr = priv_hnd->ion_phy_addr; 
    }
    else
    {
        ALOGE("disp surface, priv_hnd is null!\n");
        return HI_FAILURE;            
    }

    mapper.lock((pSurface->WindowBuffer)->handle, GRALLOC_USAGE_SW_WRITE_OFTEN, bounds, &(pSurface->VirtualAddr));        

#endif
    return HI_SUCCESS;
}

HI_S32 OsdManager::unLock(HI_HANDLE hSurface)
{
#ifdef ANDROID44
    OSD_DISP_SURFACE_S      *pSurface = HI_NULL;

    pSurface = GetSurfaceInst(hSurface);
    if (pSurface == HI_NULL)
    {
        ALOGE("hSurface is invalid!\n");
        return HI_FAILURE;
    }

    GraphicBufferMapper &mapper = GraphicBufferMapper::get();

    mapper.unlock((pSurface->WindowBuffer)->handle);

#endif
    return HI_SUCCESS;
}

HI_S32 OsdManager::FillRect(HI_HANDLE hSurface, HI_RECT_S *pstRect, HI_U32 u32Color)
{
#ifdef ANDROID44
    TDE_HANDLE          s32Handle = 0;
    HI_S32              s32Ret = 0;
    TDE2_SURFACE_S      stDst;
    OSD_DISP_SURFACE_S  *pSurface = HI_NULL;

    pSurface = GetSurfaceInst(hSurface);
    if (pSurface == HI_NULL)
    {
        ALOGE("hSurface is invalid!\n");
        return HI_FAILURE;
    }

    if (pSurface->WindowBuffer == HI_NULL)
    {
        lock(hSurface);
    }
    
    memset(&stDst, 0, sizeof(TDE2_SURFACE_S));

    stDst.u32Width  = pSurface->stAttr.Width;
    stDst.u32Height = pSurface->stAttr.Height;
    stDst.u32Stride = pSurface->stAttr.Stride;
    stDst.enColorFmt = FORMAT_TO_TDE(pSurface->stAttr.PixelFormat);;
    stDst.u32PhyAddr = pSurface->PhyAddr;
        
    stDst.bAlphaMax255 = HI_TRUE;

    s32Handle = HI_TDE2_BeginJob();
    if(HI_ERR_TDE_INVALID_HANDLE == s32Handle)
    {
        ALOGE("Fail to create Job.\n");
        return HI_FAILURE;
    }

    TDE2_RECT_S TdeRect;
    TdeRect.s32Xpos = pstRect->s32X;
    TdeRect.s32Ypos = pstRect->s32Y;
    TdeRect.u32Width = pstRect->s32Width;
    TdeRect.u32Height = pstRect->s32Height;
    
    s32Ret = HI_TDE2_QuickFill(s32Handle, &stDst, &TdeRect, u32Color);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("HI_TDE2_QuickFill failed!\n");
		HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 1000);
		return HI_FAILURE;
    }
    
    s32Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 1000);
    if(HI_SUCCESS != s32Ret)
    {
        ALOGE("Fail to End Job. ret=%p\n", (void*)s32Ret);
        return HI_FAILURE;
    }
    
    s32Ret = HI_TDE2_WaitForDone(s32Handle);
    if (HI_ERR_TDE_QUERY_TIMEOUT == s32Ret)
    {  
        ALOGE("wait for done time out");
        return HI_FAILURE;
    }

#endif
    return HI_SUCCESS;
}

HI_S32 OsdManager::Refresh(HI_HANDLE hSurface)
{
#ifdef ANDROID44
    OSD_DISP_SURFACE_S  *pSurface = HI_NULL;

    pSurface = GetSurfaceInst(hSurface);
    if (pSurface == HI_NULL)
    {
        ALOGE("hSurface is invalid!\n");
        return HI_FAILURE;
    }

    if (HI_NULL != pSurface->WindowBuffer)
    {
        unLock(hSurface);
        
        // show
        (pSurface->Window)->queueBuffer(pSurface->Window, pSurface->WindowBuffer, -1);
    }

    pSurface->WindowBuffer = HI_NULL;

#endif
    return HI_SUCCESS;
}

HI_S32 OsdManager::Blit(HI_HANDLE hSrcSurface, HI_RECT_S *pstSrcRect, HI_HANDLE hDstSurface, HI_RECT_S *pstDstRect)
{
#ifdef ANDROID44
    HI_S32              Ret;
    OSD_DISP_SURFACE_S  *pSrcSurface, *pDstSurface;

    TDE2_SURFACE_S      stSrc;
    TDE2_SURFACE_S      stDst;
    TDE_HANDLE          s32Handle = 0;
    TDE2_OPT_S          stOpt;

    TDE2_RECT_S         srcRect = {0,0,0,0};
    TDE2_RECT_S         dstRect = {0,0,0,0};

    pSrcSurface = GetSurfaceInst(hSrcSurface);

    pDstSurface = GetSurfaceInst(hDstSurface);

    if (pSrcSurface == HI_NULL || pDstSurface == HI_NULL)
    {
        ALOGE("hSrcSurface or hDstSurface is invalid!\n");
        return HI_FAILURE;
    }

    if (HI_NULL == pstSrcRect || HI_NULL == pstDstRect)  
    {
        ALOGE("pstSrcRect or pstDstRect is invalid!\n");
        return HI_FAILURE;    
    }

    if (HI_NULL == pSrcSurface->WindowBuffer)
    {
        lock(hSrcSurface);
    }

    if (HI_NULL == pDstSurface->WindowBuffer)
    {
        lock(hDstSurface);
    }

    memset(&stSrc, 0, sizeof(TDE2_SURFACE_S));
    memset(&stDst, 0, sizeof(TDE2_SURFACE_S));
    memset(&stOpt, 0, sizeof(TDE2_OPT_S));

    stSrc.u32Width  = pSrcSurface->stAttr.Width;
    stSrc.u32Height = pSrcSurface->stAttr.Height;
    stSrc.enColorFmt = FORMAT_TO_TDE(pSrcSurface->stAttr.PixelFormat);
    stSrc.u32PhyAddr = pSrcSurface->PhyAddr;
    stSrc.u32Stride = stSrc.u32Width * tde_bytepp(stSrc.enColorFmt);
    stSrc.bAlphaMax255 = HI_TRUE;

    stDst.u32Width  = pDstSurface->stAttr.Width;
    stDst.u32Height = pDstSurface->stAttr.Height;
    stDst.enColorFmt = FORMAT_TO_TDE(pDstSurface->stAttr.PixelFormat);
    stDst.u32PhyAddr = pDstSurface->PhyAddr;
    stDst.u32Stride = stDst.u32Width * tde_bytepp(stDst.enColorFmt);
    stDst.bAlphaMax255 = HI_TRUE;  

    srcRect.s32Xpos = pstSrcRect->s32X;
    srcRect.s32Ypos = pstSrcRect->s32Y;
    srcRect.u32Width = pstSrcRect->s32Width;
    srcRect.u32Height = pstSrcRect->s32Height;
    
    dstRect.s32Xpos = pstDstRect->s32X;
    dstRect.s32Ypos = pstDstRect->s32Y;
    dstRect.u32Width = pstDstRect->s32Width;
    dstRect.u32Height = pstDstRect->s32Height;

#if 0
    stOpt.enAluCmd = TDE2_ALUCMD_BLEND;
    stOpt.u8GlobalAlpha = 0x40;
    stOpt.stBlendOpt.bGlobalAlphaEnable = HI_TRUE;
    stOpt.stBlendOpt.bPixelAlphaEnable = HI_TRUE;
    stOpt.stBlendOpt.eBlendCmd = TDE2_BLENDCMD_SRCOVER;
    stOpt.stBlendOpt.bSrc2AlphaPremulti = HI_TRUE;
    stOpt.bResize = HI_TRUE;
#else
    stOpt.enAluCmd = TDE2_ALUCMD_NONE;
    //stOpt.u8GlobalAlpha = 0x40;
    stOpt.stBlendOpt.bGlobalAlphaEnable = HI_FALSE;
    stOpt.stBlendOpt.bPixelAlphaEnable = HI_FALSE;
    stOpt.stBlendOpt.eBlendCmd = TDE2_BLENDCMD_NONE;
    stOpt.stBlendOpt.bSrc2AlphaPremulti = HI_FALSE;
    stOpt.bResize = HI_TRUE;
#endif
        
    s32Handle = HI_TDE_BeginJob();
    if(HI_ERR_TDE_INVALID_HANDLE == s32Handle) 
    {
        ALOGE("Fail to create Job.\n");
        return HI_FAILURE;
    }

    Ret = HI_TDE2_Bitblit(s32Handle,
                         &stDst, &dstRect,
                         &stSrc, &srcRect,
                         &stDst, &dstRect,
                         &stOpt);

    if(HI_SUCCESS != Ret) 
    {
        ALOGE(" TDE blit failed ,error code %x" ,Ret);
        HI_TDE2_CancelJob(s32Handle);
        return HI_FAILURE;
    }

    Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 100);
    if(HI_SUCCESS != Ret) 
    {
        ALOGE(" TDE blit end job failed");
        return HI_FAILURE;
    }

     Ret = HI_TDE2_WaitForDone(s32Handle); 
     if (HI_ERR_TDE_QUERY_TIMEOUT == Ret)
     {  
         ALOGE("wait for done time out");
         return HI_FAILURE;
     }

#endif
    return HI_SUCCESS;
}

HI_S32 OsdManager::BlitFrameToSurface(HI_UNF_VIDEO_FRAME_INFO_S *pstFrame, HI_HANDLE hDstSurface, HI_RECT_S *pstDstRect)
{
#ifdef ANDROID44
    HI_S32              s32Ret;
    TDE2_SURFACE_S      TDEDstSurface;
    TDE2_MBOPT_S        stMbOpt;
    TDE2_MB_S           TDEMBSurface;
    TDE_HANDLE          s32Handle;
    OSD_DISP_SURFACE_S  *pDstSurface;

    pDstSurface = GetSurfaceInst(hDstSurface);

    if (pDstSurface == HI_NULL)
    {
        ALOGE("hDstSurface is invalid!\n");
        return HI_FAILURE;
    }

    if (HI_NULL == pDstSurface->WindowBuffer)
    {
        lock(hDstSurface);
    }

    TDE2_RECT_S SrcRect = {0, 0, pstFrame->u32Width, pstFrame->u32Height};
    
    TDE2_RECT_S DstRect;    

    if (HI_NULL != pstDstRect)
    {
        DstRect.s32Xpos = pstDstRect->s32X;
        DstRect.s32Ypos = pstDstRect->s32Y;
        DstRect.u32Width = pstDstRect->s32Width;
        DstRect.u32Height = pstDstRect->s32Height;
    }
    else
    {
        DstRect.s32Xpos = 0;
        DstRect.s32Ypos = 0;
        DstRect.u32Width =  pDstSurface->stAttr.Width;
        DstRect.u32Height = pDstSurface->stAttr.Height;
    }
   
    memset(&TDEDstSurface,0,sizeof(TDEDstSurface));
    memset(&stMbOpt,0,sizeof(stMbOpt));
    memset(&TDEMBSurface,0,sizeof(TDEMBSurface));

    // set the src surface
    TDEMBSurface.enMbFmt = TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP;

    TDEMBSurface.u32YPhyAddr = pstFrame->stVideoFrameAddr[0].u32YAddr;
    TDEMBSurface.u32CbCrPhyAddr = pstFrame->stVideoFrameAddr[0].u32CAddr;
    TDEMBSurface.u32YStride = pstFrame->stVideoFrameAddr[0].u32YStride;
    TDEMBSurface.u32CbCrStride = pstFrame->stVideoFrameAddr[0].u32CStride;
    TDEMBSurface.u32YWidth  = pstFrame->u32Width;
    TDEMBSurface.u32YHeight = pstFrame->u32Height;

    // set the dst surface
    TDEDstSurface.u32PhyAddr = pDstSurface->PhyAddr;
    TDEDstSurface.enColorFmt = TDE2_COLOR_FMT_ABGR8888;		// need fix

    TDEDstSurface.u32Height = pDstSurface->stAttr.Height;
    TDEDstSurface.u32Width  = pDstSurface->stAttr.Width;
    TDEDstSurface.u32Stride = pDstSurface->stAttr.Stride; 
    
    TDEDstSurface.pu8ClutPhyAddr = NULL;
    TDEDstSurface.bYCbCrClut = HI_FALSE;


    TDEDstSurface.u32CbCrPhyAddr = 0;
    TDEDstSurface.u32CbCrStride  = 0;
        
    TDEDstSurface.bAlphaMax255  = HI_TRUE;
    TDEDstSurface.bAlphaExt1555 = HI_FALSE;
    TDEDstSurface.u8Alpha0 = 0;
    TDEDstSurface.u8Alpha1 = 255;

    s32Handle = HI_TDE2_BeginJob();
    if (s32Handle == HI_ERR_TDE_INVALID_HANDLE)
    {
        ALOGE("begin jop failed\n");
        return HI_FALSE;
    }

    stMbOpt.enResize = TDE2_MBRESIZE_QUALITY_LOW;   //enable scale

    s32Ret = HI_TDE2_MbBlit(s32Handle, &TDEMBSurface, &SrcRect, &TDEDstSurface, &DstRect, &stMbOpt);
    if (HI_SUCCESS != s32Ret)
    {
        ALOGE("Mbblit failed: %x\n",s32Ret);
        (HI_VOID)HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 100);
        return HI_FALSE;
    }

    s32Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 100);
    if ((HI_SUCCESS != s32Ret) && (HI_ERR_TDE_JOB_TIMEOUT != s32Ret))
    {
        ALOGE("end job failed\n");
        return HI_FALSE;
    }

    s32Ret = HI_TDE2_WaitForDone(s32Handle); 
    if (HI_ERR_TDE_QUERY_TIMEOUT == s32Ret)
    {  
        ALOGE("wait for done time out");
        return HI_FAILURE;
    }

#endif
    return HI_SUCCESS;      
}

HI_S32 OsdManager::DecodeImage(HI_HANDLE hSurface, const HI_VOID *pImageMem, HI_U32 MemSize, HI_RECT_S *pstRect)
{
#ifdef ANDROID44
    OSD_DISP_SURFACE_S      *pSurface, *pTmpSurface;
    SkImageDecoder::Format  format;
    SkBitmap                *bitmap;
    HI_HANDLE               hTmpSurface;
    SURFACE_ATTR_S          stAttr;
    HI_RECT_S               stSrcRect, stDstRect;

    pSurface = GetSurfaceInst(hSurface);
    if (pSurface == HI_NULL)
    {
        ALOGE("hSurface is invalid!\n");
        return HI_FAILURE;
    }

    bitmap = new SkBitmap;

    if(0 == SkImageDecoder::DecodeMemory(pImageMem, MemSize, bitmap,
                                        SkBitmap::kARGB_8888_Config, 
                                        SkImageDecoder::kDecodePixels_Mode, &format))
    {
            ALOGE("decode picture failed");
            return HI_FAILURE;
    }

    stAttr.Width = bitmap->width();
    stAttr.Height = bitmap->height();
    stAttr.Stride = bitmap->width() * 4;
    stAttr.PixelFormat = PIXEL_FORMAT_RGBA_8888;
    CreateSurface(&stAttr, &hTmpSurface);

    pTmpSurface = GetSurfaceInst(hTmpSurface);
    if (pSurface == HI_NULL)
    {
        ALOGE("create tmp surface failed!\n");
        delete bitmap;
        return HI_FAILURE;
    }

    lock(hTmpSurface);

    memcpy(pTmpSurface->VirtualAddr, bitmap->getAddr(0,0), bitmap->width()*bitmap->height()*4);

    if (pSurface->WindowBuffer == HI_NULL)
    {
        lock(hSurface);
    }

    stSrcRect.s32X = 0;
    stSrcRect.s32Y = 0;
    stSrcRect.s32Width = stAttr.Width;
    stSrcRect.s32Height = stAttr.Height;

    if ( ((HI_U32)(pstRect->s32X+pstRect->s32Width) > pSurface->stAttr.Width)
        || ((HI_U32)(pstRect->s32Y+pstRect->s32Height) > pSurface->stAttr.Height)
        )
    {
        stDstRect.s32X = 0;
        stDstRect.s32Y = 0;
        stDstRect.s32Width = pSurface->stAttr.Width;
        stDstRect.s32Height = pSurface->stAttr.Height;
    }
    else
    {
        stDstRect = *pstRect;
    }
    
    Blit(hTmpSurface, &stSrcRect, hSurface, &stDstRect);

    DestroySurface(hTmpSurface);

    delete bitmap;
    
#endif
    return HI_SUCCESS;
}

/*
EncodeType = 1: JPEG
EncodeType = 2: PNG
EncodeType = other: JPEG
*/
HI_S32 OsdManager::EncodeFrame(HI_UNF_VIDEO_FRAME_INFO_S *pstFrame, HI_S32 EncodeType, HI_CHAR *DstFile)
{
#ifdef ANDROID44
    HI_HANDLE               hTmpSurface;
    OSD_DISP_SURFACE_S      *pTmpSurface;
    SURFACE_ATTR_S          stAttr;
    SkBitmap                *bitmap;
    HI_VOID                 *pBitmapAddr;

    stAttr.Width = pstFrame->u32Width;
    stAttr.Height = pstFrame->u32Height;
    stAttr.Stride = pstFrame->u32Width * 4;
    stAttr.PixelFormat = PIXEL_FORMAT_RGBA_8888;
    CreateSurface(&stAttr, &hTmpSurface);

    pTmpSurface = GetSurfaceInst(hTmpSurface);

    BlitFrameToSurface(pstFrame, hTmpSurface, HI_NULL);

    bitmap = new SkBitmap;

    bitmap->setConfig(SkBitmap::kARGB_8888_Config, stAttr.Width, stAttr.Height, 0);

    bitmap->allocPixels(NULL);

    pBitmapAddr = bitmap->getAddr(0, 0);

    memcpy(pBitmapAddr, pTmpSurface->VirtualAddr, stAttr.Stride * stAttr.Height);

    DestroySurface(hTmpSurface);

    if (EncodeType == 2)
    {
        SkImageEncoder::EncodeFile(DstFile, *bitmap, SkImageEncoder::kPNG_Type, 80);
    }
    else
    {
        SkImageEncoder::EncodeFile(DstFile, *bitmap, SkImageEncoder::kJPEG_Type, 80);
    }

    delete bitmap;

#endif
    return 0;
}

 HI_S32 OsdManager::DrawCCText(HI_HANDLE hSurface, SURFACE_ATTR_S * pstSurfaceAttr,HI_RECT_S* pstRect, HI_CHAR* pTest,CCTEXT_ATTR_S * pstAttr)
{
#ifdef ANDROID44
        OSD_DISP_SURFACE_S*  pSurface = HI_NULL;
        SkBitmap   bitmap;
        SkBitmap   tempBitmap;
        ANativeWindow_Buffer Buffer;

        pSurface = GetSurfaceInst(hSurface);
        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

        if((HI_NULL == pPixels )||(captionSurfaceW!= pstSurfaceAttr->Width )||(captionSurfaceH!=pstSurfaceAttr->Height)) 
        {         
             captionSurfaceW = pstSurfaceAttr->Width;
             captionSurfaceH  = pstSurfaceAttr->Height;
             if(HI_NULL != pPixels )
             {
                    free(pPixels);
             }
             pPixels = (HI_U8 *)malloc(captionSurfaceW*captionSurfaceH*4);
             memset(pPixels,0,captionSurfaceW*captionSurfaceH*4);
        }

        bitmap.setConfig(SkBitmap::kARGB_8888_Config, captionSurfaceW, captionSurfaceH);
        bitmap.setPixels(pPixels);
        tempBitmap.setConfig(SkBitmap::kARGB_8888_Config, pSurface->stAttr.Width, pSurface->stAttr.Height);
        tempBitmap.allocPixels(NULL);

        SkPaint paint;
        SkCanvas canvas(bitmap);
        SkColor color;
        SkRect rect;

        //draw text background on the bitmap
        color = pstAttr->u32bgColor;
        //color = 0xffff0000;
        paint.setColor(color);
        rect.set(pstRect->s32X, pstRect->s32Y, pstRect->s32Width+pstRect->s32X, pstRect->s32Height+pstRect->s32Y);
        
        canvas.save();
        canvas.clipRect(rect, SkRegion::kReplace_Op);
        paint.setColor(color);
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
        canvas.drawPaint(paint);

        //draw text  on the bitmap
        color = pstAttr->u32fgColor;
        paint.setColor(color);//color        
        size_t byteLength=strlen(pTest);
        paint.setUnderlineText(pstAttr->underline);//underline
        if(HI_TRUE ==pstAttr->italic)//italic
        {
            SkSafeUnref(paint.setTypeface(SkTypeface::CreateFromName("monospace", SkTypeface::kItalic)));
        }
        else
        {
            SkSafeUnref(paint.setTypeface(SkTypeface::CreateFromName("monospace", SkTypeface::kNormal)));
        }
        
         //fontsize
        SkScalar ts;
        if( 1 == pstAttr->u8fontSize)//HI_UNF_CC_FONTSIZE_SMALL
        {
             ts = SkIntToScalar(15);
        }
        else if(3 == pstAttr->u8fontSize)//HI_UNF_CC_FONTSIZE_LARGE
        {
            ts = SkIntToScalar(27);
        }
        else//HI_UNF_CC_FONTSIZE_STANDARD
        {
            ts = SkIntToScalar(21);
        }
        paint.setTextSize(ts);

         //align
        SkScalar x;
        if(1 == pstAttr->u8justify)//HI_UNF_CC_JUSTIFY_RIGHT
        {
            paint.setTextAlign(SkPaint::kRight_Align);
            x=pstRect->s32X+pstRect->s32Width;

        }
        else if(2 == pstAttr->u8justify)//HI_UNF_CC_JUSTIFY_CENTER
        {
            paint.setTextAlign(SkPaint::kCenter_Align);
            x=(pstRect->s32X+pstRect->s32Width)/2;
        }
        else//HI_UNF_CC_JUSTIFY_LEFT
        {
            paint.setTextAlign(SkPaint::kLeft_Align);
            x=pstRect->s32X;
        }

        canvas.drawText((HI_CHAR *)pTest,byteLength,  x,  pstRect->s32Y+ts, paint);
        canvas.restore();

        //scale
        SkCanvas canvas_(tempBitmap);
        SkPaint paint_;
        
        SkScalar sx = (float)pSurface->stAttr.Width/captionSurfaceW;
        SkScalar sy = (float)pSurface->stAttr.Height/captionSurfaceH;
        paint_.setXfermodeMode(SkXfermode::kSrc_Mode);

        canvas_.save();
        canvas_.scale(sx, sy);
        canvas_.drawBitmap(bitmap, 0, 0, &paint_);
        canvas_.restore();
        
        HI_S32 s32Ret;
        SurfaceComposerClient::openGlobalTransaction();
        s32Ret=pSurface->surface->lock(&Buffer, NULL);

        if(HI_SUCCESS != s32Ret)
        {
            ALOGE("lock surface failed!\n");
            return HI_FAILURE;
        }

        //copy the bitmap to surface
        memset(Buffer.bits,0,Buffer.width*Buffer.height*4);
        memcpy(Buffer.bits,tempBitmap.getPixels(),Buffer.width*Buffer.height*4);

        pSurface->surface->unlockAndPost();
        SurfaceComposerClient::closeGlobalTransaction();

#endif
        return HI_SUCCESS;

 }

HI_S32 OsdManager::FillCCRect(HI_HANDLE hSurface,SURFACE_ATTR_S * pstSurfaceAttr, HI_RECT_S *pstRect, HI_U32 u32Color)
{
#ifdef ANDROID44
       OSD_DISP_SURFACE_S*  pSurface = HI_NULL;
        SkBitmap   bitmap;
        SkBitmap   tempBitmap;
        ANativeWindow_Buffer Buffer;

        pSurface = GetSurfaceInst(hSurface);
        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

         if((HI_NULL == pPixels )||(captionSurfaceW!= pstSurfaceAttr->Width )||(captionSurfaceH!=pstSurfaceAttr->Height)) 
        {         
             captionSurfaceW = pstSurfaceAttr->Width;
             captionSurfaceH  = pstSurfaceAttr->Height;
             if(HI_NULL != pPixels )
             {
                    free(pPixels);
             }
             pPixels = (HI_U8 *)malloc(captionSurfaceW*captionSurfaceH*4);
             memset(pPixels,0,captionSurfaceW*captionSurfaceH*4);
        }

        bitmap.setConfig(SkBitmap::kARGB_8888_Config, captionSurfaceW, captionSurfaceH);
        bitmap.setPixels(pPixels);
        tempBitmap.setConfig(SkBitmap::kARGB_8888_Config, pSurface->stAttr.Width, pSurface->stAttr.Height);
        tempBitmap.allocPixels(NULL);

        SkCanvas canvas(bitmap);
        SkPaint paint;
        SkColor color;
        SkRect rect;

        //draw rect on the bitmap
        color = u32Color;
        //color = 0xff0000ff;
        paint.setColor(color);
        rect.set(pstRect->s32X, pstRect->s32Y, pstRect->s32Width+pstRect->s32X, pstRect->s32Height+pstRect->s32Y);
        
        canvas.save();
        canvas.clipRect(rect, SkRegion::kReplace_Op);
        paint.setColor(color);
        paint.setXfermodeMode(SkXfermode::kSrc_Mode);
        canvas.drawPaint(paint);
        canvas.restore();

        //scale
        SkCanvas canvas_(tempBitmap);
        SkPaint paint_;
        
        SkScalar sx = (float)pSurface->stAttr.Width/captionSurfaceW;
        SkScalar sy = (float)pSurface->stAttr.Height/captionSurfaceH;
        paint_.setXfermodeMode(SkXfermode::kSrc_Mode);

        canvas_.save();
        canvas_.scale(sx, sy);
        canvas_.drawBitmap(bitmap, 0, 0, &paint_);
        canvas_.restore();
        
        HI_S32 s32Ret;
        SurfaceComposerClient::openGlobalTransaction();
        s32Ret=pSurface->surface->lock(&Buffer, NULL);

        if(HI_SUCCESS != s32Ret)
        {
            ALOGE("lock surface failed!\n");
            return HI_FAILURE;
        }
        
        //copy the bitmap to surface
        memset(Buffer.bits,0,Buffer.width*Buffer.height*4);
        memcpy(Buffer.bits,tempBitmap.getPixels(),Buffer.width*Buffer.height*4);

        pSurface->surface->unlockAndPost();
        SurfaceComposerClient::closeGlobalTransaction();

#endif
        return HI_SUCCESS;
}

HI_S32 OsdManager::GetCCTextSize(HI_CHAR* pTest,HI_S32 *pWidth, HI_S32 *pHeigh )
{
#ifdef ANDROID44

    if(HI_NULL == pTest)
    {
        * pWidth = 0;
        * pHeigh = 0;
        return HI_SUCCESS;
    }

    SkPaint paint;
    SkScalar ts = SkIntToScalar(21); //normal
    paint.setTextSize(ts);
    SkSafeUnref(paint.setTypeface(SkTypeface::CreateFromName("monospace", SkTypeface::kNormal)));
    size_t byteLength=strlen(pTest);
    SkScalar width=paint.measureText(pTest, byteLength);

    *pWidth = (HI_S32)width;
        
    *pHeigh = 21;

#endif
    return HI_SUCCESS;
    
}

HI_S32 OsdManager::CCBlit(HI_HANDLE hSurface, SURFACE_ATTR_S * pstSurfaceAttr,HI_RECT_S *pstSrcRect, HI_RECT_S *pstDstRect)
{
#ifdef ANDROID44
        OSD_DISP_SURFACE_S*  pSurface = HI_NULL;
        SkBitmap   bitmap;
        SkBitmap   tempBitmap;
        ANativeWindow_Buffer Buffer;

        pSurface = GetSurfaceInst(hSurface);
        if (pSurface == HI_NULL)
        {
            ALOGE("hSurface is invalid!\n");
            return HI_FAILURE;
        }

         if((HI_NULL == pPixels )||(captionSurfaceW!= pstSurfaceAttr->Width )||(captionSurfaceH!=pstSurfaceAttr->Height)) 
        {         
             captionSurfaceW = pstSurfaceAttr->Width;
             captionSurfaceH  = pstSurfaceAttr->Height;
             if(HI_NULL != pPixels )
             {
                    free(pPixels);
             }
             pPixels = (HI_U8 *)malloc(captionSurfaceW*captionSurfaceH*4);
             memset(pPixels,0,captionSurfaceW*captionSurfaceH*4);
        }

        bitmap.setConfig(SkBitmap::kARGB_8888_Config, captionSurfaceW, captionSurfaceH);
        bitmap.setPixels(pPixels);
        tempBitmap.setConfig(SkBitmap::kARGB_8888_Config, pSurface->stAttr.Width, pSurface->stAttr.Height);
        tempBitmap.allocPixels(NULL);

        SkCanvas canvas(bitmap);
        SkPaint paint;
        SkRect src;
        SkRect dst;
        
        src.set(pstSrcRect->s32X, pstSrcRect->s32Y, pstSrcRect->s32X+pstSrcRect->s32Width, pstSrcRect->s32Y+pstSrcRect->s32Height);
        dst.set(pstDstRect->s32X, pstDstRect->s32Y, pstDstRect->s32X+pstDstRect->s32Width, pstDstRect->s32Y+pstDstRect->s32Height);

        paint.setXfermodeMode(SkXfermode::kSrc_Mode);

        canvas.save();
        canvas.drawBitmapRectToRect(bitmap, &src, dst, &paint);
        canvas.restore();

        //scale
        SkCanvas canvas_(tempBitmap);
        SkPaint paint_;
        
        SkScalar sx = (float)pSurface->stAttr.Width/captionSurfaceW;
        SkScalar sy = (float)pSurface->stAttr.Height/captionSurfaceH;
        paint_.setXfermodeMode(SkXfermode::kSrc_Mode);

        canvas_.save();
        canvas_.scale(sx, sy);
        canvas_.drawBitmap(bitmap, 0, 0, &paint_);
        canvas_.restore();

        HI_S32 s32Ret;
        SurfaceComposerClient::openGlobalTransaction();
        s32Ret=pSurface->surface->lock(&Buffer, NULL);

        if(HI_SUCCESS != s32Ret)
        {
            ALOGE("lock surface failed!\n");
            return HI_FAILURE;
        }

        //copy the bitmap to surface
        memset(Buffer.bits,0,Buffer.width*Buffer.height*4);
        memcpy(Buffer.bits,tempBitmap.getPixels(),Buffer.width*Buffer.height*4);

        pSurface->surface->unlockAndPost();
        SurfaceComposerClient::closeGlobalTransaction();
#endif
        return HI_SUCCESS;
        
}

//translate and scale
HI_S32 OsdManager::TeletextDrawBitmap(HI_HANDLE hSurface, HI_U8 *bitmapBuffer,HI_RECT_S *pstSrcRect,HI_RECT_S *pstDstRect)
{
#ifdef ANDROID44
    OSD_DISP_SURFACE_S*  pSurface = HI_NULL;
    SkBitmap   bitmap;
    SkBitmap   tempBitmap;
    ANativeWindow_Buffer Buffer;

    pSurface = GetSurfaceInst(hSurface);
    if (pSurface == HI_NULL)
    {
           ALOGE("hSurface is invalid!\n");
           return HI_FAILURE;
     }

     tempBitmap.setConfig(SkBitmap::kARGB_8888_Config, pstSrcRect->s32Width, pstSrcRect->s32Height);
     tempBitmap.setPixels(bitmapBuffer);
     bitmap.setConfig(SkBitmap::kARGB_8888_Config, pSurface->stAttr.Width, pSurface->stAttr.Height);
     bitmap.allocPixels(NULL);

     HI_S32 s32Ret;
     SurfaceComposerClient::openGlobalTransaction();
     s32Ret=pSurface->surface->lock(&Buffer, NULL);

      if(HI_SUCCESS != s32Ret)
      {
            ALOGE("lock surface failed!\n");
            return HI_FAILURE;
      }

     SkCanvas canvas(bitmap);
     SkPaint paint;

     paint.setXfermodeMode(SkXfermode::kSrc_Mode);
     SkScalar sx = (float)pstDstRect->s32Width/pstSrcRect->s32Width;
     SkScalar sy = (float)pstDstRect->s32Height/pstSrcRect->s32Height;

     canvas.save();
     canvas.scale(sx, sy);
     canvas.drawBitmap(tempBitmap, pstDstRect->s32X/sx, pstDstRect->s32Y/sy, &paint);
     canvas.restore();

     //copy the bitmap to surface
     memset(Buffer.bits,0,Buffer.width*Buffer.height*4);
     memcpy(Buffer.bits,bitmap.getPixels(),Buffer.width*Buffer.height*4);

     pSurface->surface->unlockAndPost();
     SurfaceComposerClient::closeGlobalTransaction();

#endif
     return HI_SUCCESS;

}

//translate and scale
HI_S32 OsdManager::SubDrawBitmap(HI_HANDLE hSurface, HI_U8 *bitmapBuffer,SURFACE_ATTR_S * pstSurfaceAttr ,HI_RECT_S *pstSrcRect)
{
#ifdef ANDROID44
    OSD_DISP_SURFACE_S*  pSurface = HI_NULL;
    SkBitmap   bitmap;
    SkBitmap   tempBitmap;
    ANativeWindow_Buffer Buffer;

    pSurface = GetSurfaceInst(hSurface);
    if (pSurface == HI_NULL)
    {
           ALOGE("hSurface is invalid!\n");
           return HI_FAILURE;
     }

     if(HI_NULL == pPixels)
     {         
             pPixels = (HI_U8 *)malloc(pSurface->stAttr.Width*pSurface->stAttr.Height*4);
             memset(pPixels,0,pSurface->stAttr.Width*pSurface->stAttr.Height*4);
     }
     
     tempBitmap.setConfig(SkBitmap::kARGB_8888_Config, pstSurfaceAttr->Width, pstSurfaceAttr->Height);
     tempBitmap.setPixels(bitmapBuffer);
     bitmap.setConfig(SkBitmap::kARGB_8888_Config, pSurface->stAttr.Width, pSurface->stAttr.Height);
     bitmap.setPixels(pPixels);

     HI_S32 s32Ret;
     SurfaceComposerClient::openGlobalTransaction();
     s32Ret=pSurface->surface->lock(&Buffer, NULL);

      if(HI_SUCCESS != s32Ret)
      {
            ALOGE("lock surface failed!\n");
            return HI_FAILURE;
      }

     SkCanvas canvas(bitmap);
     SkPaint paint;

     paint.setXfermodeMode(SkXfermode::kSrc_Mode);
     SkScalar sx = (float)pSurface->stAttr.Width/pstSurfaceAttr->Width;
     SkScalar sy = (float)pSurface->stAttr.Height/pstSurfaceAttr->Height;

     canvas.save();
     canvas.scale(sx, sy);
     canvas.drawBitmap(tempBitmap, pstSrcRect->s32X, pstSrcRect->s32Y, &paint);
     canvas.restore();

     //copy the bitmap to surface
     memset(Buffer.bits,0,Buffer.width*Buffer.height*4);
     memcpy(Buffer.bits,pPixels,Buffer.width*Buffer.height*4);

     pSurface->surface->unlockAndPost();
     SurfaceComposerClient::closeGlobalTransaction();

#endif
     return HI_SUCCESS;

}



} // end of namespace
