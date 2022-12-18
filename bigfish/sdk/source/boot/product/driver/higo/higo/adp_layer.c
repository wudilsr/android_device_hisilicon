
/**
\file
\brief LAYER适配层
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author h180450
\date 2012-11-2
*/
#include "adp_layer.h"
#include "hi_go_gdev.h"
#include "higo_adp_sys.h"
#include "higo_gdev.h"
#include "hi_common.h"
#include "hi_drv_pdm.h"
#include "optm_hifb.h"
#include "hifb_debug.h"
#include "hi_tde_api.h"
#include "adp_gfx.h"
#include "hi_drv_disp.h"
#include "drv_display.h"

#define IS_SD_LAYER(LayerID) ((LayerID >= HIGO_LAYER_SD_0)&&(LayerID <= HIGO_LAYER_SD_3))
#define IS_HD_LAYER(LayerID) (LayerID <= HIGO_LAYER_HD_3)
#define IS_AD_LAYER(LayerID) ((LayerID >= HIGO_LAYER_AD_0)&&(LayerID <= HIGO_LAYER_AD_3))
#define SD_INDEX 0
#define HD_INDEX 1
#define AD_INDEX 2
#define LAYER_TYPE_NUM 3

#ifndef HIGO_CODE_CUT
#define HIGO_LAYER_PFCOUNT 9
#define HIGO_LAYER_COUNT 10
#else
#define HIGO_LAYER_COUNT 4
#endif
typedef struct
{
    HI_U32       u32LayerID;
    HI_U32       u32LayerAddr;   
    HIFB_RECT     stInRect;  
    HIFB_RECT     stOutRect;   
    HI_U32       u32Stride;         
}HIFB_LAYER_REFRESH_S;

typedef struct _HIGO_DISPLAY_INFO_S
{
    HI_U32 u32ScreenAddr;	  
    //HIFB_POINT_S stScreenPos;
    HIFB_RECT stInRect;
    HIFB_RECT stOutRect;
    HIFB_ALPHA_S stAlpha;
#ifndef HIGO_CODE_CUT
   HIFB_COLORKEYEX_S stColorKey;
#endif
}HIGO_DISPLAY_INFO_S;

static HIGO_DISPLAY_INFO_S s_DisplayInfo[HIGO_LAYER_MAXCOUNT];

/** 图层私有信息结构 */
typedef struct _HIGO_LAYER_PRIVATE_S
{
    HI_S32            fd;            /**< 文件操作符 */
    HI_CHAR*          pszLayerName;  /**< 图层路径名称 */
    HIGO_LAYER_CAP_S  struLayerCap;  /**< 图层能力集 */
} HIGO_LAYER_PRIVATE_S;

#ifndef HIGO_CODE_CUT
/** 各像素格式对应的位域信息数组 */
const HIGO_BITFIELD_S s_BitField[9] =
{
    {
        .red    ={     8, 4, 0}, /**< RGB4444 */
        .green  ={     4, 4, 0},
        .blue   ={     0, 4, 0},
        .transp ={    12, 4, 0},
    },
    {
        .red    ={     8, 4, 0}, /**< RGB0444 */
        .green  ={     4, 4, 0},
        .blue   ={     0, 4, 0},
        .transp ={     0, 0, 0},
    },
    {
        .red    ={    10, 5, 0}, /**< RGB1555 */
        .green  ={     5, 5, 0},
        .blue   ={     0, 5, 0},
        .transp ={    15, 1, 0},
    },
    {
        .red    ={    10, 5, 0}, /**< RGB0555 */
        .green  ={     5, 5, 0},
        .blue   ={     0, 5, 0},
        .transp ={     0, 0, 0},
    },
    {
        .red    ={    11, 5, 0}, /**< RGB565 */
        .green  ={     5, 6, 0},
        .blue   ={     0, 5, 0},
        .transp ={     0, 0, 0},
    },
    {
        .red    ={    16, 8, 0}, /**< RGB8888 */
        .green  ={     8, 8, 0},
        .blue   ={     0, 8, 0},
        .transp ={    24, 8, 0},
    },
    {
        .red    ={    16, 8, 0}, /**< RGB0888 */
        .green  ={     8, 8, 0},
        .blue   ={     0, 8, 0},
        .transp ={     0, 0, 0},
    },
    {
        .red    ={     0, 8, 0}, /**< CLUT8 */
        .green  ={     0, 8, 0},
        .blue   ={     0, 8, 0},
        .transp ={     0, 0, 0},
    },
    {
        .red    = {    11, 5, 0}, /**< RGB8565 */
        .green  = {    5, 6, 0},
        .blue   = {    0, 5, 0},
        .transp = {   16, 8, 0},
    }  
};
#endif
static HIGO_LAYER_INFO_S s_HiGoLayerDefInfo[LAYER_TYPE_NUM] = 
{{720 , 576, 720 , 576, 720 , 576, (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_DOUBLE, HIGO_LAYER_DEFLICKER_AUTO, HIGO_PF_1555, HIGO_LAYER_SD_0},
 //{1920, 1080, 1920, 1080, 1920, 1080, (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_TRIPLE, HIGO_LAYER_DEFLICKER_AUTO, HIGO_PF_1555, HIGO_LAYER_HD_0},
 {1280, 720, 1280, 720, 1280, 720, (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_DOUBLE, HIGO_LAYER_DEFLICKER_AUTO, HIGO_PF_8888, HIGO_LAYER_HD_0}, 
 {1280, 80, 1280, 80, 1280, 80, (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_DOUBLE, HIGO_LAYER_DEFLICKER_AUTO, HIGO_PF_1555, HIGO_LAYER_AD_0}};
#if 0
static HIGO_LAYER_INFO_S s_HiGoLayerDefInfo[1] = 
{
 //{1920, 1080, 1920, 1080, 1920, 1080, (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_TRIPLE, HIGO_LAYER_DEFLICKER_AUTO, HIGO_PF_1555, HIGO_LAYER_HD_0},
 {1280, 720, 1280, 720, 1280, 720, (HIGO_LAYER_FLUSHTYPE_E)HIGO_LAYER_BUFFER_DOUBLE, HIGO_LAYER_DEFLICKER_AUTO, HIGO_PF_8888, HIGO_LAYER_HD_0}, 
 };
#endif
//#endif
#ifndef HIGO_CODE_CUT
/** 图层信息数组，数组下标为硬件层的ID */
static HIGO_LAYER_PRIVATE_S s_LayerInfo[HIGO_LAYER_COUNT];

/** 图形叠加层支持的像素格式 */
static HIGO_PF_E s_LayerFmt[HIGO_LAYER_PFCOUNT] = {/*HIGO_PF_CLUT8,*/ HIGO_PF_4444, HIGO_PF_0444, HIGO_PF_1555,
                                  HIGO_PF_0555,  HIGO_PF_565,  HIGO_PF_0888, HIGO_PF_8888, HIGO_PF_8565};

static HIGO_PF_E s_PfMem[HIGO_LAYER_PFCOUNT*HIGO_LAYER_COUNT];
#endif
/******************************************************************************
    internal function
******************************************************************************/
static HI_U32 WinParamAlignUp(HI_U32 x, HI_U32 a)
{
    if (!a)
    {
        return x;
    }
    else
    {
        return ( (( x + (a-1) ) / a ) * a);
    }
}

/*this func is for both graphics and video  virtual screen deal, it's a common function.*/
HI_S32 Win_ReviseOutRect(const HI_RECT_S *tmp_virtscreen, 
                         const HI_DRV_DISP_OFFSET_S *stOffsetInfo,
                         const HI_RECT_S *stFmtResolution,
                         const HI_RECT_S *stPixelFmtResolution,
                         HI_RECT_S *stToBeRevisedRect, 
                         HI_RECT_S *stRevisedRect)
{    
    HI_U32 width_ratio = 0,  height_ratio = 0;
    HI_U32 zmeDestWidth = 0, zmeDestHeight = 0;
    HI_DRV_DISP_OFFSET_S tmp_offsetInfo;

    tmp_offsetInfo = *stOffsetInfo;


    if ( (stFmtResolution->s32Width * 2) == stPixelFmtResolution->s32Width)
    {
        tmp_offsetInfo.u32Left  *= 2;
        tmp_offsetInfo.u32Right *= 2;        
    }

    zmeDestWidth = (stPixelFmtResolution->s32Width - tmp_offsetInfo.u32Left - tmp_offsetInfo.u32Right);
    zmeDestHeight = (stPixelFmtResolution->s32Height - tmp_offsetInfo.u32Top - tmp_offsetInfo.u32Bottom);

    
    /*pay attention ,we must care about that  u32 overflow.....*/
    width_ratio  = zmeDestWidth  * 100 /(tmp_virtscreen->s32Width);
    height_ratio = zmeDestHeight * 100 /(tmp_virtscreen->s32Height);    

    if (tmp_virtscreen->s32Width != stToBeRevisedRect->s32Width)
    {
        stRevisedRect->s32Width = (stToBeRevisedRect->s32Width * width_ratio) / 100;         
    } else {
        stRevisedRect->s32Width = zmeDestWidth;
    }
    
    if (tmp_virtscreen->s32Height != stToBeRevisedRect->s32Height)
    {
        stRevisedRect->s32Height = (stToBeRevisedRect->s32Height * height_ratio) / 100;      
    } else {
        stRevisedRect->s32Height = zmeDestHeight;
    }
    
        
    stRevisedRect->s32X = (stToBeRevisedRect->s32X * width_ratio) /100 + tmp_offsetInfo.u32Left;
    stRevisedRect->s32Y= (stToBeRevisedRect->s32Y * height_ratio) /100 + tmp_offsetInfo.u32Top;
    
    stRevisedRect->s32X = WinParamAlignUp(stRevisedRect->s32X, 2);
    stRevisedRect->s32Y = WinParamAlignUp(stRevisedRect->s32Y, 2);
    stRevisedRect->s32Width  = WinParamAlignUp(stRevisedRect->s32Width, 2);
    stRevisedRect->s32Height = WinParamAlignUp(stRevisedRect->s32Height, 2);



    return HI_SUCCESS;
}
static OPTM_GFX_GP_E OPTM_GetGfxGpId(HIFB_LAYER_ID_E enLayerId)
{
	if(HIFB_LAYER_HD_3 >= enLayerId)
	{
		return OPTM_GFX_GP_0;
	}
	else if (enLayerId >= HIFB_LAYER_SD_0
			&& HIFB_LAYER_SD_1 >= enLayerId)
	{
		return OPTM_GFX_GP_1;
	}

	return OPTM_GFX_GP_BUTT;
}

HI_VOID ADP_Layer_ConvertFieldInfo(HIGO_PF_E enType, HIGO_BITFIELD_S *pstFieldInfo)
{
#ifndef HIGO_CODE_CUT
    switch (enType)
    {
    case HIGO_PF_4444:
        HIGO_MemCopy(pstFieldInfo, &s_BitField[0], sizeof(HIGO_BITFIELD_S));
        break;
    case HIGO_PF_0444:
        HIGO_MemCopy(pstFieldInfo, &s_BitField[1], sizeof(HIGO_BITFIELD_S));
        break;
    case HIGO_PF_1555:
        HIGO_MemCopy(pstFieldInfo, &s_BitField[2], sizeof(HIGO_BITFIELD_S));
        break;
    case HIGO_PF_0555:
        HIGO_MemCopy(pstFieldInfo, &s_BitField[3], sizeof(HIGO_BITFIELD_S));
        break;
    case HIGO_PF_565:
        HIGO_MemCopy(pstFieldInfo, &s_BitField[4], sizeof(HIGO_BITFIELD_S));
        break;
    case HIGO_PF_8888:
        HIGO_MemCopy(pstFieldInfo, &s_BitField[5], sizeof(HIGO_BITFIELD_S));
        break;
    case HIGO_PF_0888:
        HIGO_MemCopy(pstFieldInfo, &s_BitField[6], sizeof(HIGO_BITFIELD_S));
        break;
  /*  case HIGO_PF_CLUT8:
        HIGO_MemCopy(pstFieldInfo, &s_BitField[7], sizeof(HIGO_BITFIELD_S));*/
        break;
    case HIGO_PF_8565:
        HIGO_MemCopy(pstFieldInfo, &s_BitField[8], sizeof(HIGO_BITFIELD_S));
        break;
    default:
        break;
    }
#endif
    return;
}

static HI_S32 ADP_Layer_RefreshLayer(HIFB_LAYER_REFRESH_S *pstLayerAttr)
{
    OPTM_GFX_GP_E enGpId = OPTM_GetGfxGpId(pstLayerAttr->u32LayerID);
    if (enGpId >= OPTM_GFX_GP_BUTT)
        return HI_FAILURE;
    
    OPTM_GfxSetLayerAddr(pstLayerAttr->u32LayerID, pstLayerAttr->u32LayerAddr);
   // Debug("Set Layer Addr: 0x%x\n",pstLayerAttr->u32LayerAddr);
 
    OPTM_GfxSetLayerStride(pstLayerAttr->u32LayerID, pstLayerAttr->u32Stride);
    //Debug("Set Layer Stride: 0x%x\n",pstLayerAttr->u32Stride);

    OPTM_GfxSetLayerRect(pstLayerAttr->u32LayerID, &(pstLayerAttr->stInRect));

    OPTM_GfxSetGpRect(enGpId, &(pstLayerAttr->stInRect));

    OPTM_GfxSetDispFMTSize(enGpId, (HI_RECT_S *)(&(pstLayerAttr->stOutRect)));
    OPTM_GfxSetEnable(pstLayerAttr->u32LayerID, HI_TRUE);
    
    if (OPTM_Get_GfxWorkMode() == HIFB_GFX_MODE_HD_WBC)
    {
        OPTM_GFX_GP_E   enGfxGpId = OPTM_GFX_GP_1;
        OPTM_Wbc2Isr(&enGfxGpId, NULL);
        OPTM_GfxUpLayerReg(HIGO_LAYER_SD_0);
    }
    
    OPTM_GfxUpLayerReg(pstLayerAttr->u32LayerID);

    return HI_SUCCESS;
}
#ifndef HIGO_CODE_CUT
static HI_S32 ADP_Layer_Init(HI_VOID** pInitData)
{
    HI_U32 i, j;
    HIGO_PF_E* pPixelFmt;

    /** 分配支持的像素格式数据所占的内存 */
    pPixelFmt = (HIGO_PF_E*)s_PfMem;

    /** 初始化图层私有结构数组 */
    for (i = 0; i < HIGO_LAYER_COUNT; i++)
    {
        //s_LayerInfo[i].pszLayerName = s_LayerName[i];
        s_LayerInfo[i].struLayerCap.bPremultiply = HI_TRUE;        
        s_LayerInfo[i].struLayerCap.bNonPremultiply = HI_FALSE;
        
        /** 初始化各图层支持的像素格式 */
        s_LayerInfo[i].struLayerCap.u8FmtCount = HIGO_LAYER_PFCOUNT;
        for (j = 0; j < HIGO_LAYER_PFCOUNT; j++)
        {
            *(pPixelFmt + HIGO_LAYER_PFCOUNT * i + j) = s_LayerFmt[j];
        }

        s_LayerInfo[i].struLayerCap.enPixelFmt = pPixelFmt + HIGO_LAYER_PFCOUNT * i;
        if (IS_SD_LAYER(i))
        {
            s_LayerInfo[i].struLayerCap.MaxWidth = HIGO_SD_MAXWIDTH;
            s_LayerInfo[i].struLayerCap.MaxHeight= HIGO_SD_MAXHEIGHT;            
            s_LayerInfo[i].struLayerCap.MinWidth = HIGO_SD_MINWIDTH;
            s_LayerInfo[i].struLayerCap.MinHeight= HIGO_SD_MINHEIGHT;       
            s_LayerInfo[i].struLayerCap.bVoScale = HI_TRUE; //TO be modify in pilot
            
        }
        else if (IS_HD_LAYER(i) /*|| IS_AD_LAYER(i)*/)
        {
            s_LayerInfo[i].struLayerCap.MaxWidth = HIGO_HD_MAXWIDTH;
            s_LayerInfo[i].struLayerCap.MaxHeight= HIGO_HD_MAXHEIGHT;            
            s_LayerInfo[i].struLayerCap.MinWidth = HIGO_HD_MINWIDTH;
            s_LayerInfo[i].struLayerCap.MinHeight= HIGO_HD_MINHEIGHT;              
            s_LayerInfo[i].struLayerCap.bVoScale = HI_TRUE;
        }
    }


    return HI_SUCCESS;
}
#endif
HI_S32 HIGO_ADP_InitDisplay(HI_VOID)
{
#ifndef HIGO_CODE_CUT
    HI_S32 s32Ret;
    HI_VOID* pInitData;
    s32Ret = ADP_Layer_Init(&pInitData);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }
#endif    
	OPTM_GfxInit();
    return HI_SUCCESS;
}

HI_VOID HIGO_ADP_DeinitDisplay(HI_VOID)
{
    /** 释放初始化时分配的内存 */
    return ;
}

HI_VOID HIGO_ADP_CapabilityInquire(HI_U32 LayerID,  HIGO_LAYER_CAP_S** pstruCap)
{
#ifndef HIGO_CODE_CUT
    /** 参数检查 */
    HIGO_ASSERT(HI_NULL_PTR != pstruCap);

    /** 获取图层能力集 */
    *pstruCap = &(s_LayerInfo[LayerID].struLayerCap);
#endif    
    return ;
}

HI_S32 HIGO_ADP_GetDefaultParam(HI_U32  LayerID, HIGO_LAYER_INFO_S *pLayerInfo)
{
//#ifndef HIGO_CODE_CUT
    if (IS_SD_LAYER(LayerID))
    {   
        HIGO_MemCopy(pLayerInfo, &s_HiGoLayerDefInfo[SD_INDEX], sizeof(HIGO_LAYER_INFO_S));
    }
    else if (IS_HD_LAYER(LayerID))
    {  
        HIGO_MemCopy(pLayerInfo, &s_HiGoLayerDefInfo[HD_INDEX], sizeof(HIGO_LAYER_INFO_S));
    }
    else if (IS_AD_LAYER(LayerID))
    {   
        HIGO_MemCopy(pLayerInfo, &s_HiGoLayerDefInfo[AD_INDEX], sizeof(HIGO_LAYER_INFO_S));        
    }
    else
    {
        HIGO_ERROR(HIGO_ERR_INVPARAM);
        return HIGO_ERR_INVPARAM;
    }
//#else
//    HIGO_MemCopy(pLayerInfo, &s_HiGoLayerDefInfo[0], sizeof(HIGO_LAYER_INFO_S));
//#endif
    pLayerInfo->LayerID = (HIGO_LAYER_E)LayerID;
    return HI_SUCCESS;
}

static HI_VOID ADP_Layer_HigoFmtToHifbFmt(HIGO_PF_E SrcFmt, HIFB_COLOR_FMT_E *DstFmt)
{
    switch (SrcFmt)
    {
        case HIGO_PF_4444:
            *DstFmt = HIFB_FMT_ARGB4444;
            break;
        case HIGO_PF_0444:
            *DstFmt = HIFB_FMT_KRGB444;
            break;            
        case HIGO_PF_1555:
            *DstFmt = HIFB_FMT_ARGB1555;
            break;
        case HIGO_PF_0555:
            *DstFmt = HIFB_FMT_KRGB555;
            break; 
        case HIGO_PF_565:
            *DstFmt = HIFB_FMT_RGB565;
            break;
        case HIGO_PF_8565:
            *DstFmt = HIFB_FMT_ARGB8565;
            break;            
        case HIGO_PF_8888:
            *DstFmt = HIFB_FMT_ARGB8888;
            break;
        case HIGO_PF_0888:
            *DstFmt = HIFB_FMT_RGB888;
            break;     
        default:
            *DstFmt = HIFB_FMT_ARGB8888;
            break;
    }

}

static HI_S32 ADP_Layer_AllocateDisplayBuffer(HIGO_LAYER_INFO_S *pLayerInfo, HIGO_DISPLAY_INFO_S *pDisplayInfo)
{
    HI_S32 s32Ret;
    HI_U32 u32BPP;
    HI_U32 u32BufferSize;
    MMZ_BUFFER_S         stDisplayBuf;    
    
    Surface_CalculateBpp0(pLayerInfo->PixelFormat, &u32BPP);

    //u32BufferSize = u32BPP *pLayerInfo->DisplayWidth * pLayerInfo->DisplayHeight;
    u32BufferSize = (u32BPP *pLayerInfo->DisplayWidth + 0xf)&0xfffffff0;
	u32BufferSize *= pLayerInfo->DisplayHeight;

	if (pLayerInfo->LayerID == HIFB_HD_LOGO_ID)
	{
		s32Ret = HI_DRV_PDM_AllocReserveMem(DISPLAY_BUFFER_HD, u32BufferSize, &stDisplayBuf.u32StartPhyAddr);
	}
	else
	{
		s32Ret = HI_DRV_PDM_AllocReserveMem(DISPLAY_BUFFER_SD, u32BufferSize, &stDisplayBuf.u32StartPhyAddr); 
	}
    
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return HI_FAILURE;
    }
    
    //memset((HI_VOID*)stDisplayBuf.u32StartPhyAddr,0x0, u32BufferSize);
    Debug("Display Buffer Address: 0x%x\n",stDisplayBuf.u32StartPhyAddr);
 
    pDisplayInfo->u32ScreenAddr = stDisplayBuf.u32StartPhyAddr;

    return HI_SUCCESS;   
}

static HI_S32 ADP_Layer_DisplayInfoInit(HIGO_LAYER_INFO_S *LayerInfo, HIGO_DISPLAY_INFO_S * DisplayInfo)
{
    HI_S32 s32Ret;
    
    HI_DISP_DISPLAY_INFO_S pstInfo = {0};
    
    memset(DisplayInfo, 0, sizeof(HIGO_DISPLAY_INFO_S));    
#ifndef HIGO_CODE_CUT
    HIGO_BITFIELD_S pstFieldInfo;
    ADP_Layer_ConvertFieldInfo(LayerInfo->PixelFormat, &pstFieldInfo);
  
    DisplayInfo->stColorKey.u8BlueMask = 0Xff >> pstFieldInfo.blue.length;
    DisplayInfo->stColorKey.u8RedMask = 0Xff >> pstFieldInfo.red.length;
    DisplayInfo->stColorKey.u8GreenMask= 0Xff >> pstFieldInfo.green.length;
#endif    
    DisplayInfo->stAlpha.bAlphaEnable = HI_TRUE;
    DisplayInfo->stAlpha.bAlphaChannel = HI_FALSE;
    DisplayInfo->stAlpha.u8Alpha0 = 0x00;
    DisplayInfo->stAlpha.u8Alpha1 = 0xff;
    DisplayInfo->stAlpha.u8GlobalAlpha = 0xff;

	if (LayerInfo->LayerID <= HIGO_LAYER_HD_3)
	{
		DISP_GetDisplayInfo(HI_DRV_DISPLAY_1, &pstInfo);  
	}
	else
	{
		DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &pstInfo);
	}    

    DisplayInfo->stInRect.x = pstInfo.stVirtaulScreen.s32X;
    DisplayInfo->stInRect.y = pstInfo.stVirtaulScreen.s32Y;
    DisplayInfo->stInRect.w = pstInfo.stVirtaulScreen.s32Width;
    DisplayInfo->stInRect.h = pstInfo.stVirtaulScreen.s32Height;

    LayerInfo->DisplayWidth = DisplayInfo->stInRect.w;
    LayerInfo->DisplayHeight = DisplayInfo->stInRect.h;
    LayerInfo->CanvasWidth = DisplayInfo->stInRect.w;
    LayerInfo->CanvasHeight = DisplayInfo->stInRect.h;
    //memcpy(&DisplayInfo->stOutRect,&DisplayInfo->stInRect,sizeof(DisplayInfo->stInRect));
    Debug("DisplayInfo->stInRect[%d,%d,%d,%d]\n",DisplayInfo->stInRect.x,DisplayInfo->stInRect.y,DisplayInfo->stInRect.w,DisplayInfo->stInRect.h);
    Win_ReviseOutRect(&pstInfo.stVirtaulScreen, &pstInfo.stOffsetInfo, 
                      &pstInfo.stFmtResolution, &pstInfo.stPixelFmtResolution,
                      &pstInfo.stVirtaulScreen, (HI_RECT_S*)&DisplayInfo->stOutRect);
    Debug("DisplayInfo->stOutRect[%d,%d,%d,%d]\n",DisplayInfo->stOutRect.x,DisplayInfo->stOutRect.y,DisplayInfo->stOutRect.w,DisplayInfo->stOutRect.h);

	if (LayerInfo->LayerID == HIFB_SD_LOGO_ID)
	{
		LayerInfo->DisplayWidth = DisplayInfo->stOutRect.w;
		LayerInfo->DisplayHeight= DisplayInfo->stOutRect.h;
	}
	
    s32Ret = ADP_Layer_AllocateDisplayBuffer(LayerInfo, DisplayInfo);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    } 
   //printf("ADP_Layer_AllocateDisplayBuffer %d us\n",(get_timer(0)-start)*10);
    return HI_SUCCESS;
}

#define OPTM_TC_WIDTH 720
HI_S32 HIGO_ADP_CreateLayer(HI_U32  LayerID, HIGO_LAYER_INFO_S *pLayerInfo)
{
    HI_S32 s32Ret;
    HIFB_COLOR_FMT_E LayerFmt;
    HIFB_ALPHA_S pstAlpha = {0};  
    HIGO_DISPLAY_INFO_S *DisplayInfo;
	OPTM_GFX_GP_E enGpId;
	//HIFB_RECT stDefRect;
    /** 参数检查 */
    HIGO_ASSERT(HI_NULL_PTR != pLayerInfo);

    DisplayInfo = s_DisplayInfo + LayerID;
    s32Ret = OPTM_GfxOpenLayer(LayerID);
	if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }  

    s32Ret = ADP_Layer_DisplayInfoInit(pLayerInfo, DisplayInfo);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }    

	if (LayerID <= HIFB_LAYER_HD_3)
	{
		enGpId = OPTM_GFX_GP_0;
	}
	else
	{
		enGpId = OPTM_GFX_GP_1;
	}
	/*set layer in rect*/
	OPTM_GfxSetLayerRect(LayerID, &DisplayInfo->stInRect);
	OPTM_GfxSetGpRect(enGpId, &DisplayInfo->stInRect);
    OPTM_GfxSetDispFMTSize(enGpId, (HI_RECT_S *)(&DisplayInfo->stOutRect));

    s32Ret = OPTM_GpInitFromDisp(enGpId);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }

	/**if work in wbc mode, open slv layer, then init slv gp*/
	if (HIFB_GFX_MODE_HD_WBC == OPTM_Get_GfxWorkMode())
	{
		HI_DISP_DISPLAY_INFO_S stInfo;
		
		DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &stInfo);
		if (stInfo.stFmtResolution.s32Width > OPTM_TC_WIDTH)
		{
			OPTM_GFX_SetTCFlag(HI_TRUE);
		}
		
		OPTM_GfxOpenSlvLayer(HIFB_LAYER_SD_0);
		OPTM_GpInitFromDisp(OPTM_GFX_GP_1);
	}

    pstAlpha.bAlphaEnable  = HI_TRUE;
    pstAlpha.bAlphaChannel = HI_FALSE;
    pstAlpha.u8Alpha0      = 0;
    pstAlpha.u8Alpha1      = 255;
    pstAlpha.u8GlobalAlpha = 255;   
    OPTM_GfxSetLayerAlpha(LayerID,&pstAlpha);
    if (OPTM_Get_GfxWorkMode() == HIFB_GFX_MODE_HD_WBC)
    {
        OPTM_GFX_GP_E   enGfxGpId = OPTM_GFX_GP_1;
        OPTM_Wbc2Isr(&enGfxGpId, NULL);
        OPTM_GfxUpLayerReg(HIGO_LAYER_SD_0);
    }   
    
    ADP_Layer_HigoFmtToHifbFmt(pLayerInfo->PixelFormat, &LayerFmt);
    OPTM_GfxSetLayerDataFmt(LayerID, LayerFmt);

    return HI_SUCCESS;
}

HI_VOID HIGO_ADP_DestroyLayer(HI_U32 LayerID)
{
    /** 关闭图层设备 */
    OPTM_GfxCloseLayer(LayerID);
    return ;   
}



HI_S32 HIGO_ADP_GetCanvasSurface(HI_U32 LayerID, const HIGO_LAYER_INFO_S *pLayerInfo, HI_HANDLE *pSurface)
{
    HI_S32 s32Ret;
    HIGO_SURINFO_S       SurInfo;
    MMZ_BUFFER_S         stSurfaceBuf;
    HI_U32 u32BPP;
    HI_HANDLE hSurface;
    
    Surface_CalculateBpp0(pLayerInfo->PixelFormat, &u32BPP);
    SurInfo.PixelFormat = pLayerInfo->PixelFormat;
    SurInfo.Width = pLayerInfo->CanvasWidth;
    SurInfo.Pitch[0] = SurInfo.Width * u32BPP;
    SurInfo.Height = pLayerInfo->CanvasHeight;
  
    s32Ret = HI_MEM_Alloc(&stSurfaceBuf.u32StartPhyAddr, SurInfo.Pitch[0] * SurInfo.Height);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return HI_FAILURE;
    }

    stSurfaceBuf.u32StartVirAddr = stSurfaceBuf.u32StartPhyAddr;
    SurInfo.pPhyAddr[0] = (HI_CHAR*)stSurfaceBuf.u32StartPhyAddr;
    SurInfo.pVirAddr[0]  =(HI_CHAR*)stSurfaceBuf.u32StartVirAddr;
    //memset((HI_VOID*)SurInfo.pPhyAddr[0],0,SurInfo.Pitch[0] * SurInfo.Height);
    Debug("Layer Surface Address: 0x%x\n",stSurfaceBuf.u32StartVirAddr);

    s32Ret = HI_GO_CreateSurfaceFromMem(&SurInfo , &hSurface);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }

    *pSurface = hSurface;
    return HI_SUCCESS;  
}

HI_S32 HIGO_ADP_SetPos( HI_U32 LayerID, HI_U32 u32XStart, HI_U32 u32YStart)
{
#if 0
    HIFB_RECT InputRect;
    HIGO_DISPLAY_INFO_S *DisplayInfo;
    HI_DISP_DISPLAY_INFO_S pstInfo;
    
    DisplayInfo = s_DisplayInfo + LayerID;  

    DISP_GetDisplayInfo(HI_DRV_DISPLAY_1, &pstInfo);

    /** 设置屏幕起始位置 */
    DisplayInfo->stScreenPos.s32XPos = u32XStart;
    DisplayInfo->stScreenPos.s32YPos = u32YStart;
    DisplayInfo->stInRect.x = DisplayInfo->stOutRect.w * u32XStart / pstInfo.stOrgRect.s32Width;
    DisplayInfo->stInRect.y = DisplayInfo->stOutRect.h * u32YStart / pstInfo.stOrgRect.s32Height;
    memcpy(&InputRect, &DisplayInfo->stInRect, sizeof(InputRect));
    OPTM_GfxSetLayerRect(LayerID, &InputRect);  
    OPTM_GfxUpLayerReg(LayerID);
#endif    
    return HI_SUCCESS;
}

HI_S32 HIGO_ADP_GetPos(HI_U32 LayerID, HI_U32* pXStart, HI_U32* pYStart)
{
#if 0
    HIGO_DISPLAY_INFO_S *DisplayInfo;

    HIGO_ASSERT((HI_NULL_PTR != pXStart) && (HI_NULL_PTR != pYStart));
    
    DisplayInfo = s_DisplayInfo + LayerID;  

    /** 获取屏幕起始位置 */
    *pXStart = (HI_U32)DisplayInfo->stScreenPos.s32XPos;
    *pYStart = (HI_U32)DisplayInfo->stScreenPos.s32YPos;
#endif    
    return HI_SUCCESS;
}

HI_S32 HIGO_ADP_SetDisplaySize(HI_U32 LayerID, HI_U32 u32Width, HI_U32 u32Height)
{
#if 0
    HIGO_DISPLAY_INFO_S *DisplayInfo;
    
    DisplayInfo = s_DisplayInfo + LayerID;
    DisplayInfo->stOutRect.w = u32Width;
    DisplayInfo->stOutRect.h = u32Height;
  //  ADP_Layer_DefScreenSize(u32Width, u32Height, &DisplayInfo->stOutRect);
    OPTM_GfxSetGpRect(OPTM_GetGfxGpId(LayerID), &DisplayInfo->stOutRect);
    if (OPTM_Get_GfxWorkMode() == HIFB_GFX_MODE_HD_WBC)
    {
        OPTM_GFX_GP_E   enGfxGpId = OPTM_GFX_GP_1;
        OPTM_Wbc2Isr(&enGfxGpId, NULL);
        OPTM_GfxUpLayerReg(HIGO_LAYER_SD_0);
    }
    OPTM_GfxUpLayerReg(LayerID);   
#endif
    return HI_SUCCESS;
}

HI_S32 HIGO_ADP_GetDisplaySize(HI_U32 LayerID, HI_U32 *pWidth, HI_U32 *pHeight)
{
#if 0
    HIGO_DISPLAY_INFO_S *DisplayInfo;

    DisplayInfo = s_DisplayInfo + LayerID;

    HIGO_ASSERT(pWidth != NULL);
    HIGO_ASSERT(pHeight != NULL);

    *pWidth = DisplayInfo->stOutRect.w;
    *pHeight = DisplayInfo->stOutRect.h;
#endif
     return  HI_SUCCESS;
}

HI_S32 HIGO_ADP_SetScreenSize(HI_U32 LayerID, HI_U32 u32Width, HI_U32 u32Height)
{
#if 0
    HIGO_DISPLAY_INFO_S *DisplayInfo;
 //   HIFB_RECT OutRect;
//    HIFB_RECT InputRect;

    DisplayInfo = s_DisplayInfo + LayerID;

    DisplayInfo->stOutRect.w = u32Width;
    DisplayInfo->stOutRect.h = u32Height;

  // memcpy(&InputRect, &DisplayInfo->stInRect, sizeof(InputRect));
   // memcpy(&OutRect, &DisplayInfo->stOutRect, sizeof(OutRect));
  //  ADP_Layer_DefScreenSize(u32Width, u32Height, &DisplayInfo->stOutRect);
   // s_stDrvOps.HIFB_DRV_SetLayerInRect(pLayerRec->LayerID, &InputRect);
    OPTM_GfxSetGpRect(OPTM_GetGfxGpId(LayerID), &DisplayInfo->stOutRect);
    if (OPTM_Get_GfxWorkMode() == HIFB_GFX_MODE_HD_WBC)
    {
        OPTM_GFX_GP_E   enGfxGpId = OPTM_GFX_GP_1;
        OPTM_Wbc2Isr(&enGfxGpId, NULL);
        OPTM_GfxUpLayerReg(HIGO_LAYER_SD_0);
    }
   
    OPTM_GfxUpLayerReg(LayerID);   
#endif
    return HI_SUCCESS;

}

HI_S32 HIGO_ADP_GetScreenSize(HI_U32 LayerID, HI_U32 *pWidth, HI_U32 *pHeight)
{
#if 0
    //HI_S32 s32Ret;
    HIGO_DISPLAY_INFO_S *DisplayInfo;

    DisplayInfo = s_DisplayInfo + LayerID;
    HIGO_ASSERT(pWidth != NULL);
    HIGO_ASSERT(pHeight != NULL);

    *pWidth = DisplayInfo->stOutRect.w;
    *pHeight = DisplayInfo->stOutRect.h;
#endif    
    return HI_SUCCESS;
}

HI_S32 HIGO_ADP_SetLayerAlpha(HI_U32 LayerID, const HIGO_LAYER_ALPHA_S *pAlphaInfo)
{
    HIGO_DISPLAY_INFO_S *DisplayInfo;
    
    DisplayInfo = s_DisplayInfo + LayerID;
    
    /** 设置全局ALPHA */
    DisplayInfo->stAlpha.bAlphaEnable = pAlphaInfo->bAlphaEnable;
    DisplayInfo->stAlpha.bAlphaChannel = pAlphaInfo->bAlphaChannel;
    DisplayInfo->stAlpha.u8GlobalAlpha = pAlphaInfo->GlobalAlpha;
    DisplayInfo->stAlpha.u8Alpha0 = pAlphaInfo->Alpha0;
    DisplayInfo->stAlpha.u8Alpha1 = pAlphaInfo->Alpha1; 
    OPTM_GfxSetLayerAlpha(LayerID, &DisplayInfo->stAlpha);
    if (OPTM_Get_GfxWorkMode() == HIFB_GFX_MODE_HD_WBC)
    {
        OPTM_GFX_GP_E   enGfxGpId = OPTM_GFX_GP_1;
        OPTM_Wbc2Isr(&enGfxGpId, NULL);
        OPTM_GfxUpLayerReg(HIGO_LAYER_SD_0);
    }    
    OPTM_GfxUpLayerReg(LayerID); 

    return HI_SUCCESS;
}

HI_S32 HIGO_ADP_GetLayerAlpha(HI_U32 LayerID, HIGO_LAYER_ALPHA_S *pAlphaInfo)
{
    HIGO_DISPLAY_INFO_S *DisplayInfo;
    
    HIGO_ASSERT(pAlphaInfo != NULL);

    DisplayInfo = s_DisplayInfo + LayerID;

    pAlphaInfo->bAlphaEnable = DisplayInfo->stAlpha.bAlphaEnable;
    pAlphaInfo->bAlphaChannel = DisplayInfo->stAlpha.bAlphaChannel;
    pAlphaInfo->GlobalAlpha = DisplayInfo->stAlpha.u8GlobalAlpha;
    pAlphaInfo->Alpha0 = DisplayInfo->stAlpha.u8Alpha0;
    pAlphaInfo->Alpha1 = DisplayInfo->stAlpha.u8Alpha1;    
    return HI_SUCCESS;
}

HI_S32 HIGO_ADP_SetLayerColorkey(HI_U32 LayerID, HI_BOOL bEnable, HI_U32 Key)
{
#ifndef HIGO_CODE_CUT
    HIGO_DISPLAY_INFO_S *DisplayInfo;
    
    DisplayInfo = s_DisplayInfo + LayerID;

    /** 设置COLORKEY */
    DisplayInfo->stColorKey.u32Key = Key;
    DisplayInfo->stColorKey.bKeyEnable = bEnable;
 
    OPTM_GfxSetLayKeyMask(LayerID, &DisplayInfo->stColorKey);
    OPTM_GfxUpLayerReg(LayerID); 
#endif    
    return HI_SUCCESS;
}

HI_S32 HIGO_ADP_GetLayerColorKey(HI_U32 LayerID, HI_BOOL *pbEnable, HI_U32 *pKey)
{
#ifndef HIGO_CODE_CUT
    HIGO_DISPLAY_INFO_S *DisplayInfo;
    
    DisplayInfo = s_DisplayInfo + LayerID;

    *pKey = DisplayInfo->stColorKey.u32Key;
    *pbEnable = DisplayInfo->stColorKey.bKeyEnable;
#endif    
    return HI_SUCCESS;
}

HI_S32 HIGO_ADP_ShowLayer(HI_U32 LayerID, HI_BOOL bVisbile)
{
    /** 显示或隐藏图层 */
    OPTM_GfxSetEnable(LayerID, bVisbile);
    if (OPTM_Get_GfxWorkMode() == HIFB_GFX_MODE_HD_WBC)
    {
        OPTM_GFX_GP_E   enGfxGpId = OPTM_GFX_GP_1;
        OPTM_Wbc2Isr(&enGfxGpId, NULL);
        OPTM_GfxUpLayerReg(HIGO_LAYER_SD_0);
    }
    return HI_SUCCESS;
    
}

HI_S32 HIGO_ADP_SetLayerSurface(HI_HANDLE Layer, const HIGO_SURFACE_S *pSurface, HI_RECT *pRect)
{    
    HI_S32 s32Ret;
    TDE_HANDLE       s32Handle;
    TDE2_SURFACE_S   stSrcSur = {0};
    TDE2_SURFACE_S   stDstSur = {0};
    TDE2_RECT_S      stSrcRect = {0};
    TDE2_RECT_S      stDstRect = {0};
    TDE2_OPT_S       stOpt = {0};
    HIGO_DISPLAY_INFO_S *DisplayInfo;
    HIGO_LAYER_REC_S* pLayerRec;
    HIGO_SURFACE_S *LayerSurface;
    HIFB_LAYER_REFRESH_S pstLayerAttr;
    
    LayerSurface = (HIGO_SURFACE_S*)pSurface;
    
    pLayerRec = (HIGO_LAYER_REC_S*)Layer;
    DisplayInfo = s_DisplayInfo + pLayerRec->LayerID;

    if (pRect->x + pRect->w > pLayerRec->LayerInfo.CanvasWidth)
    {
        pRect->w = pLayerRec->LayerInfo.CanvasWidth - pRect->x;
    }
    if (pRect->y + pRect->h > pLayerRec->LayerInfo.CanvasHeight)
    {
        pRect->h = pLayerRec->LayerInfo.CanvasHeight - pRect->y;
    }
       
    stSrcRect.s32Xpos = pRect->x;
    stSrcRect.s32Ypos = pRect->y;
    stSrcRect.u32Width = pRect->w;
    stSrcRect.u32Height = pRect->h;
    
    stSrcSur.u32PhyAddr = (HI_U32)LayerSurface->Data[0].pPhyData;
    stSrcSur.u32Stride = (pLayerRec->LayerInfo.CanvasWidth * LayerSurface->Data[0].Bpp + 0xf) &0xfffffff0;
    stSrcSur.u32Width = pLayerRec->LayerInfo.CanvasWidth;
    stSrcSur.u32Height = pLayerRec->LayerInfo.CanvasHeight;

    stSrcSur.bAlphaMax255 = HI_TRUE;
    stSrcSur.u8Alpha0 = 0;
    stSrcSur.u8Alpha1 = 0xff;

    s32Ret = ADP_ConvertFormat(LayerSurface->PixelFormat, &stSrcSur.enColorFmt);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }    
    
    if (pLayerRec->LayerInfo.CanvasWidth != pLayerRec->LayerInfo.DisplayWidth ||
        pLayerRec->LayerInfo.CanvasHeight!= pLayerRec->LayerInfo.DisplayHeight)
    {
        stDstRect.s32Xpos = 0;
        stDstRect.s32Ypos = 0;
        stDstRect.u32Width = pLayerRec->LayerInfo.DisplayWidth;
        stDstRect.u32Height = pLayerRec->LayerInfo.DisplayHeight;
        stOpt.bResize = HI_TRUE;
    }
    else 
    {
        stDstRect = stSrcRect;
    }
    
    memcpy((HI_VOID*)&stDstSur, (HI_VOID*)&stSrcSur, sizeof(TDE2_SURFACE_S));
    
    stDstSur.u32PhyAddr = DisplayInfo->u32ScreenAddr;
    stDstSur.u32Stride = (pLayerRec->LayerInfo.DisplayWidth * LayerSurface->Data[0].Bpp +0xf)&0xfffffff0;
    stDstSur.u32Width = pLayerRec->LayerInfo.DisplayWidth;
    stDstSur.u32Height = pLayerRec->LayerInfo.DisplayHeight;

    stOpt.enFilterMode = TDE2_FILTER_MODE_COLOR;
    stOpt.enDeflickerMode = TDE2_DEFLICKER_MODE_RGB;   

   // stOpt.bResize = HI_TRUE;
    s32Handle = HI_TDE2_BeginJob();
    if (s32Handle < 0)
    {
        HIGO_ERROR(s32Handle);
        return s32Handle;
    }
    
    Debug("stSrcRect.x=%d,stSrcRect.y=%d,stSrcRect.w=%d,stSrcRect.h=%d\n",stSrcRect.s32Xpos,stSrcRect.s32Ypos,stSrcRect.u32Width,stSrcRect.u32Height);
    Debug("stDstRect.x=%d,stDstRect.y=%d,stDstRect.w=%d,stDstRect.h=%d\n",stDstRect.s32Xpos,stDstRect.s32Ypos,stDstRect.u32Width,stDstRect.u32Height);
    Debug("stSrcSur.enColorFmt:%d,stSrcSur.u32Stride:%d,stSrcSur.u32Width:%d,stSrcSur.u32Height:%d\n",stSrcSur.enColorFmt,stSrcSur.u32Stride,stSrcSur.u32Width,stSrcSur.u32Height);
    Debug("stDstSur.enColorFmt:%d,stDstSur.u32Stride:%d,stDstSur.u32Width:%d,stDstSur.u32Height:%d\n",stDstSur.enColorFmt,stDstSur.u32Stride,stDstSur.u32Width,stDstSur.u32Height);
    
    s32Ret = HI_TDE2_Bitblit(s32Handle, &stDstSur, &stDstRect, &stSrcSur, &stSrcRect, &stDstSur,  &stDstRect, &stOpt);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }  
    
    s32Ret = HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 100);
    if (s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(s32Ret);
        return s32Ret;
    }  

   pstLayerAttr.u32LayerID = pLayerRec->LayerID;
   pstLayerAttr.u32LayerAddr = DisplayInfo->u32ScreenAddr;
 
   pstLayerAttr.u32Stride = (LayerSurface->Data[0].Bpp * pLayerRec->LayerInfo.DisplayWidth +0xf)&0xfffffff0;
   memcpy(&pstLayerAttr.stInRect, &DisplayInfo->stInRect, sizeof(pstLayerAttr.stInRect));
   memcpy(&pstLayerAttr.stOutRect, &DisplayInfo->stOutRect, sizeof(pstLayerAttr.stOutRect));
 
   //update register
   ADP_Layer_RefreshLayer(&pstLayerAttr);
   
   return HI_SUCCESS;
}

HI_S32 HIGO_ADP_CreateVideoDevice(HIGO_LAYER_ADP_S *thiz)
{
    /** 参数检查 */
    if (HI_NULL_PTR == thiz)
    {
        HIGO_ADP_SetError(HI_FAILURE);
        return HI_FAILURE;
    }
    /** 为图层操作函数集结构赋值 */
    thiz->InitDisplay   =    HIGO_ADP_InitDisplay;
    thiz->DeinitDisplay =    HIGO_ADP_DeinitDisplay;
    thiz->GetDefautParam =   HIGO_ADP_GetDefaultParam;
    thiz->CreateLayer  =     HIGO_ADP_CreateLayer;
    thiz->DestroyLayer =     HIGO_ADP_DestroyLayer;
    thiz->SetLayerSurface =  HIGO_ADP_SetLayerSurface;
    thiz->GetCanvasSurface = HIGO_ADP_GetCanvasSurface;
   // thiz->SetLayerZorder =   HIGO_ADP_SetLayerZorder;
   // thiz->GetLayerZorder =   HIGO_ADP_GetLayerZorder;
    thiz->ShowLayer  =       HIGO_ADP_ShowLayer;  
   // thiz->GetLayerShowState= HIGO_ADP_GetLayerStatus;
    thiz->SetLayerAlpha =    HIGO_ADP_SetLayerAlpha;
    thiz->GetLayerAlpha =    HIGO_ADP_GetLayerAlpha;
#ifndef HIGO_CODE_CUT
    thiz->SetLayerColorKey = HIGO_ADP_SetLayerColorkey;
    thiz->GetLayerColorKey = HIGO_ADP_GetLayerColorKey;
    thiz->SetPos =           HIGO_ADP_SetPos;
    thiz->GetPos =           HIGO_ADP_GetPos;
	thiz->SetScreenSize =    HIGO_ADP_SetScreenSize;
	thiz->GetScreenSize =    HIGO_ADP_GetScreenSize;
	thiz->SetDisplaySize =   HIGO_ADP_SetDisplaySize;
	thiz->GetDisplaySize =   HIGO_ADP_GetDisplaySize;	
    thiz->CapabilityInquire= HIGO_ADP_CapabilityInquire;
    thiz->LayerCount =       HIGO_LAYER_COUNT;
#endif
    return HI_SUCCESS;
}
