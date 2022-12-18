/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : hi_go_decoder.c
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
#include "hi_go_decoder.h"
#include "higo_surface.h"
#include "higo_blit.h"
#include "higo_adp_sys.h"
#include "hi_api_mmz.h"
#include "hi_common.h"

#if !defined(HIGO_BMP_SUPPORT)
#define HIGO_BMP_SUPPORT
#endif
#if !defined(HIGO_JPEG_SUPPORT)
#define HIGO_JPEG_SUPPORT
#endif


#ifdef HIGO_BMP_SUPPORT
#include "bmp_dec.h"
#endif

#ifdef HIGO_JPEG_SUPPORT
#include "adp_jpeg.h"
#endif 

/***************************** Macro Definition ******************************/
#define HEAD_MAX_LENGTH      10
#define INVALID_HANDLE       0x0         
#define JPEG_MEM_SIZE        0x100000
/*************************** Structure Definition ****************************/


typedef struct _HIGO_DEC_INSTANCE_S
{
    HIGO_DEC_IMGTYPE_E ImgType;
    HI_HANDLE          Decoder;
    HI_S32 (*CreateDecoder) (HI_HANDLE *pDecoder, const HIGO_DEC_ATTR_S *pSrcDesc);
    HI_S32 (*DestroyDecoder)(HI_HANDLE Decoder);
    HI_S32 (*DecCommInfo)   (HI_HANDLE Decoder, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo);
    HI_S32 (*DecImgInfo)    (HI_HANDLE Decoder, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo);
    HI_S32 (*DecImgData)    (HI_HANDLE Decoder, HI_U32 Index, HIGO_SURFACE_S *pSurface);
} HIGO_DEC_INSTANCE_S;  

static HI_S32  s_InitDecCount = 0;

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

HI_S32 HIGO_DeinitDecoder(HI_VOID)
{
     /** avoid has not do initial */
    if (UN_INIT_STATE == s_InitDecCount)
    {
        HIGO_ERROR(HIGO_ERR_NOTINIT);
        return HIGO_ERR_NOTINIT;
    }

    /** exit if has do initial */
    if (s_InitDecCount != CLEAR_INIT_STATE)
    {   
        s_InitDecCount--;
        return HI_SUCCESS;
    }

    s_InitDecCount--;
    
    return HI_SUCCESS;
}

HI_S32 HIGO_InitDecoder(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    MMZ_BUFFER_S stJpegBuf;
    
    /** re initial and just remember the times  */
    if (UN_INIT_STATE != s_InitDecCount)
    {
        s_InitDecCount++;
        return HI_SUCCESS;
    }

    s32Ret = HI_MEM_Alloc(&stJpegBuf.u32StartPhyAddr, JPEG_MEM_SIZE);
    if(s32Ret != HI_SUCCESS)
    {
        HIGO_ERROR(-1);
        return HI_FAILURE;
    }     
    /* allocate memory for jpeg decode*/
    HI_MMB_Init(stJpegBuf.u32StartPhyAddr,JPEG_MEM_SIZE);    
    
    s_InitDecCount++;

    return HI_SUCCESS;
}

/*****************************************************************************
* func			   DEC_GetSrcType
* description	:  get src type,here only use from mem data
* retval		:  NA
* others:		:  NA
*****************************************************************************/
static HI_S32 DEC_GetSrcType(const HIGO_DEC_ATTR_S *pSrcDesc, HIGO_DEC_IMGTYPE_E * pImgType)
{
    HI_CHAR HeadInfo[HEAD_MAX_LENGTH] = {0};

    if (HI_NULL_PTR == pSrcDesc->SrcInfo.MemInfo.pAddr){
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HIGO_ERR_NULLPTR;
    }
    HIGO_MemCopy(HeadInfo, pSrcDesc->SrcInfo.MemInfo.pAddr, HEAD_MAX_LENGTH);

	#ifdef HIGO_JPEG_SUPPORT
	    if ((0xff == *((HI_U8*)HeadInfo)) && (0xD8 == *((HI_U8*)(HeadInfo + 1))))
	    {
	        *pImgType = HIGO_DEC_IMGTYPE_JPEG;
	        return HI_SUCCESS;
	    }
	#endif
    
	#ifdef HIGO_BMP_SUPPORT
	    if ((0x42 == *((HI_U8*)HeadInfo)) && (0x4d == *((HI_U8*)(HeadInfo + 1))))
	    {
	        *pImgType = HIGO_DEC_IMGTYPE_BMP;
	        return HI_SUCCESS;
	    }
	#endif

    HIGO_ERROR(HIGO_ERR_INVIMAGETYPE);

    return HIGO_ERR_INVIMAGETYPE;
	
};

static HI_S32 HIGO_DecImgData(const HIGO_DEC_INSTANCE_S *pDecInstance, HI_U32 Index, HIGO_HANDLE InSurface, 
                               const HIGO_DEC_IMGATTR_S *pImgAttr,  HIGO_HANDLE *pOutSurface, HIGO_DEC_IMGTYPE_E ImgType)
{
    HIGO_HANDLE DstSurface = 0;
    HIGO_SURINFO_S SurInfo;
    HIGO_DEC_IMGINFO_S ImgInfo;
    HI_S32 ret;


    HIGO_MemSet(&SurInfo, 0 , sizeof(HIGO_SURINFO_S));
    SurInfo.Width =  (HI_S32)pImgAttr->Width;
    SurInfo.Height = (HI_S32)pImgAttr->Height;
    SurInfo.PixelFormat = pImgAttr->Format;
    ret = HIGO_CreateSurface(&SurInfo, HIGO_MOD_DEC, &DstSurface, 0);
    if (ret != HI_SUCCESS)
    {
        HIGO_ERROR(ret);
        return ret;
    }            

    ret = pDecInstance->DecImgData(pDecInstance->Decoder, Index, (HIGO_SURFACE_S *)DstSurface);
    if (ret != HI_SUCCESS)
    {
        HIGO_ERROR(ret);
        goto err0;
    } 
 
    /** get index decoding image info*/
    ret = pDecInstance->DecImgInfo(pDecInstance->Decoder, Index, &ImgInfo);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(ret);
        goto err0;        
    }

    /** set alpha value  */
    (HI_VOID)Surface_SetSurfaceAlpha(DstSurface, ImgInfo.Alpha);

    /** set colorkey attribute */
    if (HI_TRUE == ImgInfo.IsHaveKey)
    {
        (HI_VOID)Surface_SetSurfaceColorKey(DstSurface, ImgInfo.Key);
    }

    if (INVALID_HANDLE == InSurface){
        *pOutSurface = DstSurface;
    }else{
		goto err0;
    }
    
    return HI_SUCCESS;
err0:

    if (INVALID_HANDLE != DstSurface)
    {
        HIGO_FreeSurface(DstSurface);
    }
    return ret;
}



/*****************************************************************************
* func			   HI_GO_CreateDecoder
* description	:  创建解码器
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HI_S32 HI_GO_CreateDecoder(const HIGO_DEC_ATTR_S *pSrcDesc, HI_HANDLE *pDecoder)
{
    HIGO_DEC_INSTANCE_S *pDecInstance = HI_NULL_PTR;
    HIGO_DEC_IMGTYPE_E ImgType = HIGO_DEC_IMGTPYE_BUTT;
    HI_S32 Ret = HI_SUCCESS;

    if ((HI_NULL_PTR == pSrcDesc) || (HI_NULL_PTR == pDecoder)){
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HIGO_ERR_NULLPTR;
    }
    if (UN_INIT_STATE == s_InitDecCount ){
        HIGO_ERROR(HIGO_ERR_NOTINIT);
        return HIGO_ERR_NOTINIT;
    }

    Ret = DEC_GetSrcType(pSrcDesc, &ImgType);
    if (Ret != HI_SUCCESS){
        HIGO_ERROR(Ret);
        return Ret;
    }
    
    pDecInstance = (HIGO_DEC_INSTANCE_S*)HIGO_Malloc(sizeof (HIGO_DEC_INSTANCE_S));
    if(HI_NULL_PTR == pDecInstance){
        HIGO_ERROR(HIGO_ERR_NOMEM);
        return HIGO_ERR_NOMEM;
    }
    *pDecoder =  (HI_HANDLE)pDecInstance;
    HIGO_MemSet(pDecInstance, 0, sizeof (HIGO_DEC_INSTANCE_S));
	
    if(HIGO_DEC_IMGTYPE_JPEG == ImgType){
		pDecInstance->ImgType = HIGO_DEC_IMGTYPE_JPEG;
        pDecInstance->CreateDecoder  = HIGO_ADP_JPGCreateDecoder;
        pDecInstance->DestroyDecoder = HIGO_ADP_JPGDestroyDecoder;
        pDecInstance->DecCommInfo    = HIGO_ADP_JPGDecCommInfo;
        pDecInstance->DecImgInfo     = HIGO_ADP_JPGDecImgInfo;
        pDecInstance->DecImgData     = HIGO_ADP_JPGDecImgData;
    }else if(HIGO_DEC_IMGTYPE_BMP == ImgType){
		pDecInstance->ImgType = HIGO_DEC_IMGTYPE_BMP;
        pDecInstance->CreateDecoder  = BMP_CreateDecoder;
        pDecInstance->DestroyDecoder = BMP_DestroyDecoder;
        pDecInstance->DecCommInfo    = BMP_DecCommInfo;
        pDecInstance->DecImgInfo     = BMP_DecImgInfo;
        pDecInstance->DecImgData     = BMP_DecImgData;
    }else{
    	HIGO_ERROR(HIGO_ERR_INVIMGDATA);
		goto adpfailed;
    }
	
    Ret = pDecInstance->CreateDecoder(&(pDecInstance->Decoder), pSrcDesc);
    if(HI_SUCCESS != Ret){
        goto adpfailed;
    }
    return HI_SUCCESS;
 
adpfailed:

	if(NULL != pDecInstance){
    	HIGO_Free(pDecInstance);
	}
    pDecInstance = HI_NULL_PTR;
    
    return Ret;
}


/*****************************************************************************
* func			   HI_GO_DecImgData
* description	:  解码
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HI_S32 HI_GO_DecImgData(HI_HANDLE Decoder, HI_U32 Index, const HIGO_DEC_IMGATTR_S *pImgAttr, HI_HANDLE *pSurface)
{
    HI_S32 ret = 0;
    HIGO_DEC_INSTANCE_S *pDecInstance = HI_NULL_PTR;
    HIGO_DEC_IMGINFO_S DecInfo;
    HIGO_HANDLE pOutSurface;
    HIGO_DEC_PRIMARYINFO_S PrimaryInfo = {0};
    HIGO_DEC_IMGATTR_S ExpImgAttr;
    
    if (HI_NULL_PTR == pSurface){
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HIGO_ERR_NULLPTR;
    }

    pDecInstance = (HIGO_DEC_INSTANCE_S *)Decoder;
    if(NULL == pDecInstance){
		return HIGO_ERR_NULLPTR;
    }
    
    ret = pDecInstance->DecCommInfo(pDecInstance->Decoder, &PrimaryInfo);
    if (HI_SUCCESS != ret){
        HIGO_ERROR(ret);
        return ret;
    }

    if (Index >= PrimaryInfo.Count){
        HIGO_ERROR(HIGO_ERR_INVINDEX);
        return HIGO_ERR_INVINDEX;
    }
    
    ret = pDecInstance->DecImgInfo(pDecInstance->Decoder, Index, &DecInfo);
    if (HI_SUCCESS != ret){
        HIGO_ERROR(ret);
        return ret;
    }

    ExpImgAttr.Width  = DecInfo.Width;
    ExpImgAttr.Height = DecInfo.Height;
    ExpImgAttr.Format = DecInfo.Format;

    ret = HIGO_DecImgData(pDecInstance, Index, (HIGO_HANDLE)NULL, &ExpImgAttr , &pOutSurface, PrimaryInfo.ImgType);
    if (ret != HI_SUCCESS){
        HIGO_ERROR(ret);
        return ret;
    }
    *pSurface = (HI_HANDLE)pOutSurface;
    
    return HI_SUCCESS;

}
/*****************************************************************************
* func			   HI_GO_DestroyDecoder
* description	:  销毁解码器
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HI_S32 HI_GO_DestroyDecoder(HI_HANDLE Decoder)
{
    HIGO_DEC_INSTANCE_S *pDecInstance = (HIGO_DEC_INSTANCE_S*)Decoder;

    if(NULL != pDecInstance){
    	(HI_VOID)pDecInstance->DestroyDecoder(pDecInstance->Decoder);
    	HIGO_Free(pDecInstance);
    	pDecInstance = NULL;
    }
    
    HI_MMB_DeInit();
    
    return HI_SUCCESS;
};
