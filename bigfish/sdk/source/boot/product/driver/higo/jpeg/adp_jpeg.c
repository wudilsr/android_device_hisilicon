/**
 \file
 \brief JPEG file decode
 \copyright Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author wangxilin
 \date 2008-6-3
 */
#include "adp_jpeg.h"
#include "hi_go_decoder.h"

#ifdef HIGO_JPEG_SUPPORT
#include "hi_jpg_errcode.h"
#include "hi_jpg_type.h"
#include "jpg_decctrl.h"
#include "hi_go_comm.h"
#include "higo_surface.h"
#include "higo_adp_sys.h"
#include "higo_io.h"

#if 0
#include "adp_vmem.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif
#include "higo_common.h"
#ifdef __cplusplus
extern "C" {
#endif
/***************************** Macro Definition ******************************/
#define MAXALPHA 255
#if 0
#define JPG_STREAM_LENGTH 4096
#define MINIALPHA 0
#endif
//lint -e754
//lint -e750
//lint -e749
/*to check is the bitstream has over the position we needed */
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

// ScaleTmp = (HI_U32)((HI_FLOAT)num / (HI_FLOAT)dem + 0.5); 

/*get the scaling rate*/
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

#if 0
typedef enum hiJPG_ENCFMT_E
{
    JPGHAL_ENCFMT_400 = 0,
    JPGHAL_ENCFMT_420 = 3,
    JPGHAL_ENCFMT_422_21,
    JPGHAL_ENCFMT_422_12,    
    JPGHAL_ENCFMT_444,
    JPGHAL_ENCFMT_BUTT
}JPG_ENCFMT_E;

#define JPG_SURFACE_ALIGN     128
#define JPG_SURFACE_ALIGN_MASK 0x40

#define JPG_MCU_ALIGN8  8
#define JPG_MCU_ALIGN16 16
#endif
/*************************** Structure Definition ****************************/

/** a instance about jpeg decode*/
typedef struct _DEC_JPEGINSTANCE_S
{
    IO_HANDLE  IoHandle;/**< file (virtal ) handle*/
    DEC_HANDLE FirmWare; /**< firmware handle */
    HI_CHAR *  pStreamBuf;/**  a pointer for the stream data buffer */
} DEC_JPEGINSTANCE_S;
#if 0
/*structure about MemSize*/
typedef struct hiJPGHDEC_MEMINFO_S
{
    JPG_ENCFMT_E     EncFmt;    /*encode format*/
    HI_U32           Height;    /*Height of the orignal picture*/
    HI_U32           Width;     /*width  of the orignal pictur */
    HI_U32           YMemSize;  /*Y data memory size */
    HI_U32           CMemSize;  /*C data memory size*/
    HI_U32           YStride;   /*Stride of Y*/
    HI_U32           CStride;   /*Stride of C*/
    JPG_MBCOLORFMT_E MbFmt;
} JPGHDEC_MEMINFO_S;
#endif
/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

extern HI_S32 HI_JPG_Open(HI_VOID);
extern HI_S32  HI_JPG_Close(HI_VOID);

HIGO_PF_E ADP_ConverFMTMBJPG2HIGO(JPG_MBCOLORFMT_E JpgFmt)
{
        switch (JpgFmt)
        {
            case JPG_MBCOLOR_FMT_JPG_YCbCr400MBP:
                return HIGO_PF_YUV400;                
            case JPG_MBCOLOR_FMT_JPG_YCbCr420MBP:
                return HIGO_PF_YUV420;
            case JPG_MBCOLOR_FMT_JPG_YCbCr422MBHP:
                return HIGO_PF_YUV422;
            case JPG_MBCOLOR_FMT_JPG_YCbCr422MBVP:
                return HIGO_PF_YUV422_V;
            case JPG_MBCOLOR_FMT_JPG_YCbCr444MBP:
                return HIGO_PF_YUV444;
            default:
                return (HIGO_PF_E)0;
        }
}

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

/**
  \continue sending the bitstream data untill the decode sofware flow don't need more data,
 \param[in] const DEC_JPEGINSTANCE_S *pDecJpegInstance
 \param[out] none
 \retval none
 \return none
 */
HI_VOID ADP_JPGSendStream(const DEC_JPEGINSTANCE_S *pDecJpegInstance)
{
    JPGDEC_WRITESTREAM_S StreamInfo;
    HI_U32 CopyLen = 0;
    HI_U32 FreeSize = 0;
    HI_BOOL EndFlag = HI_FALSE;
    HI_VOID *pAddr = HI_NULL_PTR;
    HI_S32 Ret;
    IO_TYPE_E IoType;
    
    (HI_VOID)HIGO_ADP_IOGetType(pDecJpegInstance->IoHandle,  &IoType);
    while (HI_SUCCESS == JPG_IsNeedStream(pDecJpegInstance->FirmWare, &pAddr, &FreeSize))
    {
        /** if return value is 0, it means there is enouch bitstream data, and go into sleep */
        if (0 == FreeSize)
        {           
            
            //(HI_VOID)mdelay(5);
          
            (HI_VOID)udelay(5*1000);
            continue;
        }
  
        /** get the bitstream data, if file read fail, return*/
        Ret = HIGO_ADP_IORead(pDecJpegInstance->IoHandle, pAddr, FreeSize, &CopyLen, &EndFlag);
        if (HI_SUCCESS != Ret)
        {
            return;
        }
        if (IoType == IO_TYPE_STREAM)
        {
            continue;
        }

        /** send bitstream to decode */
        StreamInfo.pStreamAddr = pAddr;
        StreamInfo.StreamLen = CopyLen;
        StreamInfo.CopyLen = 0;
        StreamInfo.NeedCopyFlag = HI_FALSE;
        StreamInfo.EndFlag = EndFlag;
        //BM_TRACE(" +++++index %d pStreamAddr 0x%x Streamlen %d\n",iIndex,pAddr,CopyLen);

        Ret = JPG_SendStream(pDecJpegInstance->FirmWare, &StreamInfo);
        if (StreamInfo.CopyLen != StreamInfo.StreamLen)
        {
            (HI_VOID)HIGO_ADP_IOSeek(pDecJpegInstance->IoHandle,
                                     IO_POS_CUR, (HI_S32)StreamInfo.CopyLen - (HI_S32)StreamInfo.StreamLen);
        }

        if (Ret != HI_SUCCESS)
        {
            //HIGO_Printf((const HI_CHAR *)"send stream failed\n");
        }

        /** if to the file end, stop read data, and send the remain data  */
        if ((HI_TRUE == EndFlag) && (StreamInfo.CopyLen == StreamInfo.StreamLen))
        {   
            return;
        }
    }

    return;
} /*lint !e818 */

HI_VOID ADP_JPGPrintPicInfo(JPG_PICINFO_S* pPicInfo)
{
    HIGO_Printf((HI_CHAR *)"EncodeFormat = ");
    HIGO_Printf((HI_CHAR *)"Profile  = %d\n",pPicInfo->Profile         );
    HIGO_Printf((HI_CHAR *)"Width  = %d\n",pPicInfo->Width           );
    HIGO_Printf((HI_CHAR *)"Height  = %d\n",pPicInfo->Height         );
    HIGO_Printf((HI_CHAR *)"SamplePrecision\t = %d\n",pPicInfo->SamplePrecision );
    HIGO_Printf((HI_CHAR *)"ComponentNum\t = %d\n",pPicInfo->ComponentNum  );
    HIGO_Printf((HI_CHAR *)"EncodeFormat = ");
    switch (pPicInfo->EncodeFormat)
    {
         case JPG_SOURCE_COLOR_FMT_YCBCR400:       HIGO_Printf((HI_CHAR *)"YUV 400\n");break;
         case JPG_SOURCE_COLOR_FMT_YCBCR420:       HIGO_Printf((HI_CHAR *)"YUV 420\n");break;
         case JPG_SOURCE_COLOR_FMT_YCBCR422BHP:    HIGO_Printf((HI_CHAR *)"YUV 422 2x1\n");break;
         case JPG_SOURCE_COLOR_FMT_YCBCR422BVP:    HIGO_Printf((HI_CHAR *)"YUV 422 1x2\n");break;
         case JPG_SOURCE_COLOR_FMT_YCBCR444:       HIGO_Printf((HI_CHAR *)"YUV 444\n");break;
         default:                                  HIGO_Printf((HI_CHAR *)"Err format\n");break;   
    }

    return;
} /*lint !e818 */

HI_S32 HIGO_ADP_JpegInit(HI_VOID)
{

    return HI_JPG_Open();
}

HI_S32 HIGO_ADP_JpegDeInit(HI_VOID)
{

    return HI_JPG_Close();
}

/** return the resolution supported*/

HI_S32 HIGO_ADP_JPGCreateDecoder(DEC_HANDLE *pJpegDec, const HIGO_DEC_ATTR_S *pSrcDesc)
{
    DEC_JPEGINSTANCE_S *pDecJpegInstance;
    IO_DESC_S DecIoDesc;
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

    /** create the virtual file system according the inout parameter*/

    DecIoDesc.IoInfo.MemInfo.pAddr  = pSrcDesc->SrcInfo.MemInfo.pAddr;
    DecIoDesc.IoInfo.MemInfo.Length = pSrcDesc->SrcInfo.MemInfo.Length;
   
    Ret = HIGO_ADP_IOCreate(&(pDecJpegInstance->IoHandle), &DecIoDesc);
    if (HI_SUCCESS != Ret)
    {
        HIGO_ERROR(HI_FAILURE);
        Ret = HI_FAILURE;
        goto creatiofailed;
    }

    /** start firmware*/
    (HI_VOID)HIGO_ADP_IOGetLength(pDecJpegInstance->IoHandle, &Length);

    Ret = JPG_CreateDecoder(&(pDecJpegInstance->FirmWare), JPG_IMGTYPE_NORMAL, Length);
    if (HI_SUCCESS != Ret)
    {        
        //Ret = HIGO_ERR_INTERNAL;
        HIGO_ERROR(Ret);
        goto semfailed;
    }

    /** allocate decode handle*/

    *pJpegDec = (DEC_HANDLE)pDecJpegInstance;

    return HI_SUCCESS;

semfailed:
    HIGO_Free((IO_HANDLE *)pDecJpegInstance->IoHandle);
creatiofailed:
    HIGO_Free(pDecJpegInstance);

    return Ret;
} /*lint !e818 */

HI_S32 HIGO_ADP_JPGDestroyDecoder(DEC_HANDLE JpegDec)
{
    DEC_JPEGINSTANCE_S *pDecJpegInstance;

    /** paramter check */
    pDecJpegInstance = (DEC_JPEGINSTANCE_S *)JpegDec;

    /** destroy virtual file system*/
    (HI_VOID)HIGO_ADP_IODestroy(pDecJpegInstance->IoHandle);

    /** clsoe firmware*/
    (HI_VOID)JPG_DestroyDecoder(pDecJpegInstance->FirmWare);

    /** destroy decode instance*/
    HIGO_Free(pDecJpegInstance);

    return HI_SUCCESS;
}

HI_S32 HIGO_ADP_JPGResetDecoder(DEC_HANDLE JpegDec)
{
    HI_S32 Ret;
    DEC_JPEGINSTANCE_S *pDecJpegInstance;

    /** get current decode instance*/
    pDecJpegInstance = (DEC_JPEGINSTANCE_S *)JpegDec;

    /** start new decoder */
    (HI_VOID)JPG_ResetDecoder(pDecJpegInstance->FirmWare);

    /** reset the position of virtual fs*/
    Ret = HIGO_ADP_IOSeek(pDecJpegInstance->IoHandle, IO_POS_SET, 0);
    if (HI_SUCCESS != Ret)
    {
        HIGO_ERROR(HI_FAILURE);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_S32 HIGO_ADP_JPGDecCommInfo(DEC_HANDLE JpegDec, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo)
{
    HI_S32 Ret;
    DEC_JPEGINSTANCE_S *pDecJpegInstance;
    JPG_PRIMARYINFO_S *pFirmPrimaryInfo;

    /** check parameter*/
    if (HI_NULL_PTR == pPrimaryInfo)
    {
        HIGO_ERROR((HI_U32)HI_NULL_PTR);
        return HI_NULL_PTR;
    }

    /** get decode instance*/
    pDecJpegInstance = (DEC_JPEGINSTANCE_S *)JpegDec;



    /** query system info*/
    Ret = JPG_GetPrimaryInfo(pDecJpegInstance->FirmWare, &pFirmPrimaryInfo);
    if (HI_SUCCESS == Ret)
    {
        pPrimaryInfo->Count   = pFirmPrimaryInfo->Count;
        pPrimaryInfo->ImgType = HIGO_DEC_IMGTYPE_JPEG;
        pPrimaryInfo->IsHaveBGColor = HI_FALSE;
        pPrimaryInfo->ScrHeight = 0;
        pPrimaryInfo->ScrWidth = 0;
        pPrimaryInfo->BGColor = 0;
        (HI_VOID)JPG_ReleasePrimaryInfo(pDecJpegInstance->FirmWare, pFirmPrimaryInfo);
        return HI_SUCCESS;
    }
    else if (Ret != HI_ERR_JPG_WANT_STREAM)
    {
        Ret = HIGO_ERR_INVIMGDATA;
        HIGO_ERROR(Ret);
        return Ret;
    }

    /** sending  bitstream */
    ADP_JPGSendStream(pDecJpegInstance);

    /** query info agian*/
    Ret = JPG_GetPrimaryInfo(pDecJpegInstance->FirmWare, &pFirmPrimaryInfo);
    if (HI_SUCCESS == Ret)
    {
        pPrimaryInfo->Count   = pFirmPrimaryInfo->Count;
        pPrimaryInfo->ImgType = HIGO_DEC_IMGTYPE_JPEG;
        pPrimaryInfo->IsHaveBGColor = HI_FALSE;
        pPrimaryInfo->ScrHeight = 0;
        pPrimaryInfo->ScrWidth = 0;
        pPrimaryInfo->BGColor = 0;
        (HI_VOID)JPG_ReleasePrimaryInfo(pDecJpegInstance->FirmWare, pFirmPrimaryInfo);
        return HI_SUCCESS;
    }
    
    HIGO_ERROR(HIGO_ERR_INVIMGDATA);
    return HIGO_ERR_INVIMGDATA;
}


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
        pImgInfo->OffSetX = 0;
        pImgInfo->OffSetY = 0;
        pImgInfo->Width  = PicInfo.Width;
        pImgInfo->Height = PicInfo.Height;

        pImgInfo->Format = ADP_ConverFMTJPG2HIGO(PicInfo.EncodeFormat);
        pImgInfo->IsHaveKey = HI_FALSE;
        pImgInfo->Key   = 0;
        pImgInfo->Alpha = MAXALPHA;
        pImgInfo->DelayTime = 0;
        pImgInfo->DisposalMethod = 0;        
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
        pImgInfo->OffSetX = 0;
        pImgInfo->OffSetY = 0;
        pImgInfo->Width  = PicInfo.Width;
        pImgInfo->Height = PicInfo.Height;
        pImgInfo->Format = ADP_ConverFMTJPG2HIGO(PicInfo.EncodeFormat);
        pImgInfo->IsHaveKey = HI_FALSE;
        pImgInfo->Key   = 0;
        pImgInfo->Alpha = MAXALPHA;
        pImgInfo->DelayTime = 0;
        pImgInfo->DisposalMethod = 0;        
        return HI_SUCCESS;
    }
    
    HIGO_ERROR(HIGO_ERR_INVIMGDATA);

    return HIGO_ERR_INVIMGDATA;
}


HI_S32 HIGO_ADP_JPGDecImgData(DEC_HANDLE JpegDec, HI_U32 Index, HIGO_SURFACE_S * pSurface)
{
    HI_S32 Ret = 0;
    DEC_JPEGINSTANCE_S *pDecJpegInstance;
    JPG_PICINFO_S PicInfo = {0}; /*lint !e64 */
    JPG_STATE_E DecState = JPG_STATE_STOP;
    HI_U32 CurIndex = 0;
    HI_BOOL OverFlag = HI_FALSE;
    JPG_SURFACE_S JpegSurface;
    HI_U32 DecCount= 0;
    HI_PIXELDATA pData;
    HI_S32 s32Ret;

    /**check parameter*/
    if (HI_NULL_PTR == pSurface)
    {
        HIGO_ERROR((HI_U32)HI_NULL_PTR);
        return HI_NULL_PTR;
    }

    /** get current decode instance*/
    pDecJpegInstance = (DEC_JPEGINSTANCE_S *)JpegDec;

decagain:

    /** query systeam status*/
    (HI_VOID)JPG_GetStatus(pDecJpegInstance->FirmWare, &DecState, &CurIndex);

    /** stustus wrong, restart the decode*/
    JPGSTREAMISOVER(CurIndex, DecState, Index, OverFlag);
    if (HI_TRUE == OverFlag)
    {
        /** restart the decode*/
        (HI_VOID)JPG_ResetDecoder(pDecJpegInstance->FirmWare);

        /** restart virtual fs*/
        Ret = HIGO_ADP_IOSeek(pDecJpegInstance->IoHandle, IO_POS_SET, 0);
        if (HI_SUCCESS != Ret)
        {
            HIGO_ERROR(HI_FAILURE);
            return HI_FAILURE;
        }
    }

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
    HIGO_ADP_ASSERT(HI_SUCCESS == Ret);

    JpegSurface.OutType = JPG_OUTTYPE_MACROBLOCK;
    (HI_VOID)Surface_LockSurface((HIGO_HANDLE)pSurface, pData);
    (HI_VOID)Surface_GetSurfaceSize((HIGO_HANDLE)pSurface, (HI_S32*)&JpegSurface.SurfaceInfo.MbSurface.YWidth, (HI_S32*)&JpegSurface.SurfaceInfo.MbSurface.YHeight);
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
    
    JpegSurface.SurfaceInfo.MbSurface.YPhyAddr = (HI_U32)pData[0].pPhyData;
    JpegSurface.SurfaceInfo.MbSurface.YVirtAddr = pData[0].pData;
    JpegSurface.SurfaceInfo.MbSurface.YStride = pData[0].Pitch;

    JpegSurface.SurfaceInfo.MbSurface.CbCrPhyAddr = (HI_U32)pData[1].pPhyData;
    JpegSurface.SurfaceInfo.MbSurface.CbCrVirtAddr =  pData[1].pData;
    JpegSurface.SurfaceInfo.MbSurface.CbCrStride = pData[1].Pitch;

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
        HI_U32 FreeSize;
        HI_VOID *pAddr = HI_NULL_PTR;
       
        while((JPG_STATE_DECODED != DecState)&&(JPG_STATE_DECODEERR != DecState)&&(JPG_STATE_PARSEERR != DecState))
        {   

            //#define JPEG_HW_ADDRESS 0xf8c40000
            s32Ret = JPG_IsNeedStream(pDecJpegInstance->FirmWare, &pAddr, &FreeSize);
            if(HI_SUCCESS != s32Ret)
            { 
                //printf("JPG_IsNeedStream failed\n");
            }
          
           // printf("jpeg:0x%x,int_mask:0x%x, int_value:0x%x\n",*(HI_U32*)JPEG_HW_ADDRESS,*(HI_U32*)(JPEG_HW_ADDRESS+0x100),*(HI_U32*)(JPEG_HW_ADDRESS+0x104));
            s32Ret = JPG_GetStatus(pDecJpegInstance->FirmWare, &DecState, &CurIndex);
            if(HI_SUCCESS != s32Ret)
            {
                //("JPG_GetStatus failed\n");
            }
        
            //BM_TRACE("+++++++++iIndex %d pAddr 0x%x FreeSize %d  DecState %d CurIndex %d\n",iIndex,pAddr, FreeSize, DecState, CurIndex);
        }
    }

    if ((JPG_STATE_DECODED == DecState) && (CurIndex == Index))
    {
        return HI_SUCCESS;
    }
    
    /** if hw decode fail, switch to software decode*/
    DecCount++;
    if  (DecCount <= 1)
        goto decagain; 

    HIGO_ERROR(HIGO_ERR_INVIMGDATA);
    return HIGO_ERR_INVIMGDATA;
}

HI_S32 HIGO_ADP_JPGGetActualSize(DEC_HANDLE JpegDec, HI_S32 Index, const HI_RECT *pSrcRect, HIGO_SURINFO_S *pSurInfo)
{
#ifndef HIGO_CODE_CUT
    HIGO_DEC_IMGINFO_S ImgInfo;
    HI_U32 XScale, YScale;
    HI_S32 ret;

    
    ret = HIGO_ADP_JPGDecImgInfo(JpegDec, (HI_U32)Index, &ImgInfo);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(ret);
        return ret;
    }
    
    /*scaling rate is the same both  for height and witdh, and the rate can be 2,4,8, send the parameter to decoder*/
    ADP_JPEGCALSCALE(ImgInfo.Width, pSrcRect->w,XScale);
    ADP_JPEGCALSCALE(ImgInfo.Height, pSrcRect->h,YScale);
    if (YScale > XScale)
    {
        XScale = YScale;
    }
    
    pSurInfo->Width = (HI_S32)((ImgInfo.Width  + (1 << XScale) - 1) >> XScale);
    pSurInfo->Height = (HI_S32)((ImgInfo.Height + (1 << XScale) - 1) >> XScale);
    pSurInfo->PixelFormat = ImgInfo.Format;
    pSurInfo->Pitch[0] = 0;
    pSurInfo->Pitch[1] = 0;
    #endif
    return HI_SUCCESS;
}

//lint +e749
//lint +e750
//lint +e754
#ifdef __cplusplus
}
#endif
#endif
