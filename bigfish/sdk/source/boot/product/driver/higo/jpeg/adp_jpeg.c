/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : adp_jpeg.c
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


#define HIGO_JPEG_SUPPORT

#ifdef HIGO_JPEG_SUPPORT

#include "adp_jpeg.h"
#include "hi_go_decoder.h"
#include "hi_jpg_errcode.h"
#include "hi_jpg_type.h"
#include "jpg_decctrl.h"
#include "hi_go_comm.h"
#include "higo_surface.h"
#include "higo_adp_sys.h"
#include "higo_io.h"
#include "higo_common.h"

/***************************** Macro Definition ******************************/

/**
 ** to check is the bitstream has over the position we needed 
 **/
#define JPGSTREAMISOVER(CurIndex, CurState, DstIndex, Result) \
    do {\
        if (((0 == CurIndex) && (0 == DstIndex) && (JPG_STATE_PARSED < CurState)) \
            || ((0 == CurIndex) && (0 != DstIndex)) \
            || ((0 != CurIndex) && (DstIndex != 0) && (CurIndex > DstIndex)) \
            || ((0 != CurIndex) && (DstIndex != 0) \
                && ((JPG_STATE_PARTPARSED == CurState) \
                    || (JPG_STATE_THUMBPARSED == CurState) \
                    || (JPG_STATE_PARSED < CurState)))) \
        { \
            Result = HI_TRUE; \
        } \
    } while (0)


/**
 ** get the scaling rate
 **/
#define ADP_JPEGCALSCALE(num, dem, result) \
do { \
    HI_U32 ScaleTmp; \
    ScaleTmp = (HI_U32)((2*num  + dem)/(dem *2)); \
    if (8 <= ScaleTmp) \
    { \
        result = 3; \
    } \
    else if (4 <= ScaleTmp) \
    { \
        result = 2; \
    } \
    else if (2 <= ScaleTmp) \
    { \
        result = 1; \
    } \
    else \
    { \
        result = 0; \
    } \
}while(0)


/*************************** Structure Definition ****************************/

/** a instance about jpeg decode*/
typedef struct _DEC_JPEGINSTANCE_S
{
	IO_INSTANCE_S stStream; 
	DEC_HANDLE FirmWare;          /**< firmware handle */
	HI_CHAR *  pStreamBuf;        /**  a pointer for the stream data buffer */
} DEC_JPEGINSTANCE_S;
	

/********************** Global Variable declaration **************************/


/******************************* API declaration *****************************/

/*****************************************************************************
* func			   ADP_ConverFMTJPG2HIGO
* description	:  
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HIGO_PF_E ADP_ConverFMTJPG2HIGO(JPG_SOURCEFMT_E JpgFmt)
{
   switch (JpgFmt)
    {
      case JPG_SOURCE_COLOR_FMT_YCBCR400:
            return HIGO_PF_YUV400;                
        case JPG_SOURCE_COLOR_FMT_YCBCR420:
            return HIGO_PF_YUV420;
        case JPG_SOURCE_COLOR_FMT_YCBCR422BHP:
            return HIGO_PF_YUV422;
        case JPG_SOURCE_COLOR_FMT_YCBCR422BVP:
            return HIGO_PF_YUV422_V;
        case JPG_SOURCE_COLOR_FMT_YCBCR444:
            return HIGO_PF_YUV444;
        default:
        	return (HIGO_PF_E)0;
    }
}

/*****************************************************************************
* func			   ADP_JPGSendStream
* description	:  
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HI_VOID ADP_JPGSendStream(const DEC_JPEGINSTANCE_S *pDecJpegInstance)
{
    JPGDEC_WRITESTREAM_S StreamInfo;
    HI_U32 CopyLen;
    HI_U32 FreeSize = 0;
    HI_BOOL EndFlag = HI_FALSE;
    HI_VOID *pAddr = HI_NULL_PTR;
    HI_S32 Ret;
    
	while (HI_SUCCESS == JPG_IsNeedStream(pDecJpegInstance->FirmWare, &pAddr, &FreeSize))
    {
        /** if return value is 0, it means there is enouch bitstream data, and go into sleep */
        if (0 == FreeSize)
        {           
           (HI_VOID)udelay(5*1000);
            continue;
        }
        /** get the bitstream data, if file read fail, return*/
        Ret = HIGO_ADP_IORead((IO_INSTANCE_S* const)(&(pDecJpegInstance->stStream)), pAddr, FreeSize, &CopyLen, &EndFlag);
        if (HI_SUCCESS != Ret)
        {
            return;
        }

        /** send bitstream to decode */
        StreamInfo.pStreamAddr  = pAddr;
        StreamInfo.StreamLen    = CopyLen;
        StreamInfo.CopyLen      = 0;
        StreamInfo.NeedCopyFlag = HI_FALSE;
        StreamInfo.EndFlag      = EndFlag;

        (HI_VOID)JPG_SendStream(pDecJpegInstance->FirmWare, &StreamInfo);
        if (StreamInfo.CopyLen != StreamInfo.StreamLen)
        {
            (HI_VOID)HIGO_ADP_IOSeek((IO_INSTANCE_S* const)(&(pDecJpegInstance->stStream)), \
                                     IO_POS_CUR,                                            \
                                     StreamInfo.CopyLen - StreamInfo.StreamLen);
        }

        /** if to the file end, stop read data, and send the remain data  */
        if ((HI_TRUE == EndFlag) && (StreamInfo.CopyLen == StreamInfo.StreamLen))
        {   
            return;
        }
    }

    return;
	
} /*lint !e818 */

/*****************************************************************************
* func			   HIGO_ADP_JPGCreateDecoder
* description	:  create decoder
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HI_S32 HIGO_ADP_JPGCreateDecoder(DEC_HANDLE *pJpegDec, const HIGO_DEC_ATTR_S *pSrcDesc)
{
    DEC_JPEGINSTANCE_S *pDecJpegInstance;
    HI_S32 Ret;
    HI_U32 Length = 0;
    
    /** check parameter*/
    if (HI_NULL_PTR == pSrcDesc)
    {
        HIGO_ERROR(HIGO_ERR_NULLPTR);
        return HIGO_ERR_NULLPTR;
    }
    /** create decode instance*/
    pDecJpegInstance = (DEC_JPEGINSTANCE_S *)HIGO_Malloc(sizeof(DEC_JPEGINSTANCE_S));
    if (HI_NULL_PTR == pDecJpegInstance)
    {
        HIGO_ERROR(HIGO_ERR_NOMEM);
        return HIGO_ERR_NOMEM;
    }

    HIGO_MemSet((HI_VOID *)pDecJpegInstance, 0x0, sizeof(DEC_JPEGINSTANCE_S));
    pDecJpegInstance->pStreamBuf = HI_NULL_PTR;

    Ret = HIGO_ADP_IOCreate(&(pDecJpegInstance->stStream),pSrcDesc->SrcInfo.MemInfo.pAddr,pSrcDesc->SrcInfo.MemInfo.Length);
    if (HI_SUCCESS != Ret)
    {
        HIGO_ERROR(HI_FAILURE);
        Ret = HI_FAILURE;
        goto creatiofailed;
    }
    /** start firmware*/
    (HI_VOID)HIGO_ADP_IOGetLength(pDecJpegInstance->stStream, &Length);

    Ret = JPG_CreateDecoder(&(pDecJpegInstance->FirmWare), JPG_IMGTYPE_NORMAL, Length);
    if (HI_SUCCESS != Ret)
    {
        HIGO_ERROR(Ret);
        goto memfailue;
    }

    /** allocate decode handle **/

    *pJpegDec = (DEC_HANDLE)pDecJpegInstance;

    return HI_SUCCESS;

memfailue:
	
	HIGO_ADP_IODestroy(&(pDecJpegInstance->stStream));
	
creatiofailed:
	if(NULL != pDecJpegInstance)
	{
   		 HIGO_Free(pDecJpegInstance);
	}
	
    return Ret;
	
} /*lint !e818 */

/*****************************************************************************
* func			   HIGO_ADP_JPGDestroyDecoder
* description	:  destory decoder
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HI_S32 HIGO_ADP_JPGDestroyDecoder(DEC_HANDLE JpegDec)
{
    DEC_JPEGINSTANCE_S *pDecJpegInstance;

    /** paramter check */
    pDecJpegInstance = (DEC_JPEGINSTANCE_S *)JpegDec;

    if (NULL == pDecJpegInstance)
	return HI_SUCCESS;

    /** destroy virtual file system*/
    HIGO_ADP_IODestroy(&(pDecJpegInstance->stStream));

    /** clsoe firmware*/
    (HI_VOID)JPG_DestroyDecoder(pDecJpegInstance->FirmWare);

    /** destroy decode instance*/
    HIGO_Free(pDecJpegInstance);
    
    return HI_SUCCESS;	
}

/*****************************************************************************
* func			   HIGO_ADP_JPGDecCommInfo
* description	:  
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HI_S32 HIGO_ADP_JPGDecCommInfo(DEC_HANDLE JpegDec, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo)
{

    if (HI_NULL_PTR == pPrimaryInfo)
    {
        HIGO_ERROR((HI_U32)HI_NULL_PTR);
        return HI_NULL_PTR;
    }
	pPrimaryInfo->Count         = 1;
    pPrimaryInfo->ImgType       = HIGO_DEC_IMGTYPE_JPEG;
    pPrimaryInfo->IsHaveBGColor = HI_FALSE;
    pPrimaryInfo->ScrHeight     = 0;
    pPrimaryInfo->ScrWidth      = 0;
    pPrimaryInfo->BGColor       = 0;

	return HI_SUCCESS;
	
}


/*****************************************************************************
* func			   HIGO_ADP_JPGDecImgInfo
* description	:  
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HI_S32 HIGO_ADP_JPGDecImgInfo(DEC_HANDLE JpegDec, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo)
{
    HI_S32 Ret;
    DEC_JPEGINSTANCE_S *pDecJpegInstance;
    JPG_PICINFO_S PicInfo;

    /** check parameter*/
    if (HI_NULL_PTR == pImgInfo)
    {
        HIGO_ERROR((HI_U32)HI_NULL_PTR);
        return HI_NULL_PTR;
    }

    /** get current decode instance*/
    pDecJpegInstance = (DEC_JPEGINSTANCE_S *)JpegDec;


    /** query system info*/
    Ret = JPG_GetPicInfo(pDecJpegInstance->FirmWare, &PicInfo, Index);
    if (HI_SUCCESS == Ret)
    {
        /** return picture info*/
        pImgInfo->Width   = PicInfo.Width;
        pImgInfo->Height  = PicInfo.Height;
        pImgInfo->Format  = ADP_ConverFMTJPG2HIGO(PicInfo.EncodeFormat);
        return HI_SUCCESS;
    }
    else if (Ret != HI_ERR_JPG_WANT_STREAM)
    {
        Ret = HIGO_ERR_INVIMGDATA;
        HIGO_ERROR(Ret);
        return Ret;
    }



    ADP_JPGSendStream(pDecJpegInstance);


    /** query system status*/
    Ret = JPG_GetPicInfo(pDecJpegInstance->FirmWare, &PicInfo, Index);
    if (HI_SUCCESS == Ret)
    {
        /** return picture info */
        pImgInfo->Width  = PicInfo.Width;
        pImgInfo->Height = PicInfo.Height;
        pImgInfo->Format = ADP_ConverFMTJPG2HIGO(PicInfo.EncodeFormat);     
        return HI_SUCCESS;
    }
    
    HIGO_ERROR(HIGO_ERR_INVIMGDATA);

    return HIGO_ERR_INVIMGDATA;
}

/*****************************************************************************
* func			   HIGO_ADP_JPGDecImgData
* description	:  
* retval		:  NA
* others:		:  NA
*****************************************************************************/
HI_S32 HIGO_ADP_JPGDecImgData(DEC_HANDLE JpegDec, HI_U32 Index, HIGO_SURFACE_S * pSurface)
{
    HI_S32 Ret = 0;
    DEC_JPEGINSTANCE_S *pDecJpegInstance;
    JPG_PICINFO_S PicInfo = {0}; /*lint !e64 */
    JPG_STATE_E DecState;
    HI_U32 CurIndex;
    JPG_SURFACE_S JpegSurface;
    HI_PIXELDATA pData;

	HI_U32 FreeSize;
    HI_VOID *pAddr = HI_NULL_PTR;
		
    /**check parameter*/
    if (HI_NULL_PTR == pSurface)
    {
        HIGO_ERROR((HI_U32)HI_NULL_PTR);
        return HI_NULL_PTR;
    }

    /** get current decode instance*/
    pDecJpegInstance = (DEC_JPEGINSTANCE_S *)JpegDec;

    /** query systeam status*/
    (HI_VOID)JPG_GetStatus(pDecJpegInstance->FirmWare, &DecState, &CurIndex);

    /** query if needed to send bitstream*/
    Ret = JPG_GetPicInfo(pDecJpegInstance->FirmWare, &PicInfo, Index);
    if ((HI_SUCCESS != Ret) && (HI_ERR_JPG_WANT_STREAM != Ret))
    {
        HIGO_ERROR(HI_FAILURE);
        return HI_FAILURE;
    }
    
    /** send bitstream*/
    if (HI_ERR_JPG_WANT_STREAM == Ret)
    {

        ADP_JPGSendStream(pDecJpegInstance);

        /** check is reach the position which decode needed*/
        Ret = JPG_GetPicInfo(pDecJpegInstance->FirmWare, &PicInfo, Index);
        if ((HI_SUCCESS != Ret) && (HI_ERR_JPG_WANT_STREAM != Ret))
        {
            HIGO_ERROR(HI_FAILURE);
            return HI_FAILURE;
        }
    }

    /** get  info decode needed*/
    Ret = JPG_GetPicInfo(pDecJpegInstance->FirmWare, &PicInfo, Index);
    if(HI_SUCCESS != Ret){
		 HIGO_ERROR(HI_FAILURE);
         return HI_FAILURE;
    }
   
    JpegSurface.OutType = JPG_OUTTYPE_MACROBLOCK;
    (HI_VOID)Surface_LockSurface((HIGO_HANDLE)pSurface, pData);
    Surface_GetSurfaceSize((HIGO_HANDLE)pSurface, (HI_S32*)&JpegSurface.SurfaceInfo.MbSurface.YWidth, (HI_S32*)&JpegSurface.SurfaceInfo.MbSurface.YHeight);
    if (PicInfo.EncodeFormat == JPG_SOURCE_COLOR_FMT_YCBCR422BHP)
    {
        JpegSurface.SurfaceInfo.MbSurface.MbFmt = JPG_MBCOLOR_FMT_JPG_YCbCr422MBHP;
    }
    else if (PicInfo.EncodeFormat == JPG_SOURCE_COLOR_FMT_YCBCR420)
    {
        JpegSurface.SurfaceInfo.MbSurface.MbFmt  = JPG_MBCOLOR_FMT_JPG_YCbCr420MBP;
    }
    else
    {
        JpegSurface.SurfaceInfo.MbSurface.MbFmt = JPG_MBCOLOR_FMT_JPG_YCbCr400MBP;
    }
    
    JpegSurface.SurfaceInfo.MbSurface.YPhyAddr     = (HI_U32)pData[0].pPhyData;
    JpegSurface.SurfaceInfo.MbSurface.YVirtAddr    = pData[0].pData;
    JpegSurface.SurfaceInfo.MbSurface.YStride      = pData[0].Pitch;
    JpegSurface.SurfaceInfo.MbSurface.CbCrPhyAddr  = (HI_U32)pData[1].pPhyData;
    JpegSurface.SurfaceInfo.MbSurface.CbCrVirtAddr =  pData[1].pData;
    JpegSurface.SurfaceInfo.MbSurface.CbCrStride   = pData[1].Pitch;

    /** start decode*/
    Ret = JPG_Decode(pDecJpegInstance->FirmWare, &JpegSurface, Index);
    if (Ret != HI_SUCCESS)
    {
        HIGO_ADP_SetError(Ret);
        if (Ret == HI_ERR_JPG_NO_MEM)
        {
            HIGO_ERROR(HIGO_ERR_NOMEM);
            return HIGO_ERR_NOMEM;
        }
        else
        {
            HIGO_ERROR(HIGO_ERR_INTERNAL);
            return HIGO_ERR_INTERNAL;
        }
    }
	
    /** send bitstream*/
    ADP_JPGSendStream(pDecJpegInstance);

    /** wait for decode fininsh */

    (HI_VOID)JPG_GetStatus(pDecJpegInstance->FirmWare, &DecState, &CurIndex);
    {
        while((JPG_STATE_DECODED != DecState)&&(JPG_STATE_DECODEERR != DecState)&&(JPG_STATE_PARSEERR != DecState))
        {
            JPG_IsNeedStream(pDecJpegInstance->FirmWare, &pAddr, &FreeSize);
            JPG_GetStatus(pDecJpegInstance->FirmWare, &DecState, &CurIndex);
    	}
    }

    if ((JPG_STATE_DECODED == DecState) && (CurIndex == Index))
    {
        return HI_SUCCESS;
    }

    HIGO_ERROR(HIGO_ERR_INVIMGDATA);
	return HIGO_ERR_INVIMGDATA;
    
}
#endif
