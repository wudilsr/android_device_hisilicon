/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : bmp_dec.c
Version             : Initial Draft
Author              : 
Created             : 2015/06/18
Description         : bmp解码
Function List       : 
History             :
Date                       Author                   Modification
2015/06/18                 y00181162                Created file        
******************************************************************************/

/*********************************add include here******************************/
#include "hi_type.h"
#include "hi_go_decoder.h"
#include "higo_adp_sys.h"
#include "higo_io.h"
#include "higo_surface.h"
#include "bmp_dec.h"
/***************************** Macro Definition ******************************/

#define BMP_WORD_LEN                  sizeof(HI_U16)
#define BMP_DWORD_LEN                 sizeof(HI_U32)
#define BMP_FILEHEADER_LEN            0x0E
     
     
/*************************** Structure Definition ****************************/


typedef struct tag_HIGO_BITMAPFILEHEADER
{
    HI_U16 bfType;
    HI_U32 bfSize;
    HI_U16 bfReserved1;
    HI_U16 bfReserved2;
    HI_U32 bfOffBits;
} HIGO_BITMAPFILEHEADER;

typedef struct tag_HIGO_BITMAPINFOHEADER
{
    HI_U32 biSize;
    HI_S32 biWidth;
    HI_S32 biHeight;
    HI_U16 biPlanes;
    HI_U16 biBitCount;       /** 每个像素所需的位数, 1: 双色 4: 16色 8: 256色 24: 真彩色 32: 32位真彩 **/
    HI_U32 biCompression;    /** 位图压缩类型, 0: 不压缩 1: BI_RLE8压缩类型 2: BI_RLE4压缩类型        **/
    HI_U32 biSizeImage;      /** 位图的大小, 以字节为单位, 对于BI_RGB必须设置为0                      **/
    HI_S32 biXPelsPerMeter;
    HI_S32 biYPelsPerMeter;
    HI_U32 biClrUsed;
    HI_U32 biClrImportant;
} HIGO_BITMAPINFOHEADER;

typedef struct BMP_DECODER
{
    IO_INSTANCE_S         stStream; 
    HIGO_BITMAPFILEHEADER FileHeader;
    HIGO_BITMAPINFOHEADER InfoHeader;
} BMP_DECODER_S;

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

/*****************************************************************************
* func       : BMP_NoRle_Decode
* description: boot只支持非压缩类型的bmp图片
* retval     :
* others:	 :
*****************************************************************************/
static HI_S32 BMP_NoRle_Decode(const BMP_DECODER_S *pBmpDec, HI_U8 *pDecData)
{
    HI_S32 ret           = HI_SUCCESS;
    HI_U32 CopyLen       = 0;
    HI_BOOL EndFlag      = 0;
    HI_U32 u32SrcStride  = 0;
    HI_S32 s32Height     = 0;
    HI_S32 s32Size       = 0;

    ret = HIGO_ADP_IOSeek((IO_INSTANCE_S* const)(&(pBmpDec->stStream)), IO_POS_SET, pBmpDec->FileHeader.bfOffBits);
    if(HI_SUCCESS != ret){
        return ret;
    }
    
	u32SrcStride = ((pBmpDec->InfoHeader.biWidth * pBmpDec->InfoHeader.biBitCount + 31) / 32) * 4;
	s32Height    = pBmpDec->InfoHeader.biHeight;
    if(s32Height < 0){
        s32Height = -s32Height;
    }
	s32Size = u32SrcStride * s32Height;
	
    ret = HIGO_ADP_IORead((IO_INSTANCE_S* const)(&(pBmpDec->stStream)), pDecData, s32Size, &CopyLen, &EndFlag);
    if(HI_SUCCESS != ret){
        return ret;
    }

    return HI_SUCCESS;

} /*lint !e818 */


/*****************************************************************************
* func       : BMP_ParseFileHeader
* description: 解析bmp文件
* retval     :
* others:	 :
*****************************************************************************/
static HI_S32 BMP_ParseFileHeader(IO_INSTANCE_S* const pstStream, HIGO_BITMAPFILEHEADER *pFileHeader)
{
    HI_S32 ret;
    HI_U8 Bytes[4] = {0};
    HI_U32 CopyLen = 0, Reserved;
    HI_BOOL EndFlag;

    /** FileType */
    ret = HIGO_ADP_IORead(pstStream, Bytes, 2, &CopyLen, &EndFlag);
    if ((HI_SUCCESS != ret) || (CopyLen < 2))
    {
        HIGO_ERROR(HI_FAILURE);   
        return HI_FAILURE;
    }

    pFileHeader->bfType = Bytes[0] | (Bytes[1] << 8);

    /** FileSize */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if ((HI_SUCCESS != ret) || (CopyLen < BMP_DWORD_LEN))
    {
        HIGO_ERROR(HI_FAILURE);     
        return HI_FAILURE;
    }

    pFileHeader->bfSize = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    /** Reserver Validation */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if ((HI_SUCCESS != ret) || (CopyLen < BMP_DWORD_LEN))
    {
        HIGO_ERROR(HI_FAILURE);      
        return HI_FAILURE;
    }

    Reserved = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);
    if (0 != Reserved)
    {
        HIGO_ERROR(HI_FAILURE);      
        return HI_FAILURE;
    }

    pFileHeader->bfReserved1 = pFileHeader->bfReserved2 = 0;

    /** OffBits */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if ((HI_SUCCESS != ret) || (CopyLen < BMP_DWORD_LEN))
    {
        HIGO_ERROR(HI_FAILURE);      
        return HI_FAILURE;
    }

    pFileHeader->bfOffBits = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    return HI_SUCCESS;
}

HI_S32 BMP_ParseInfoHeader(IO_INSTANCE_S* const pstStream, HIGO_BITMAPINFOHEADER *pInfoHeader)
{
    HI_S32 ret;
    HI_U8 Bytes[4] = {0};
    HI_U32 CopyLen;
    HI_BOOL EndFlag;

    /** We can use the way of check "HeaderSize" to know bmp version  */

    /** 0x0Ch - BMP Version 2(Window2.x OS/2 1.x)
         0x28h - BMP Version 3(Windows3.1, NT)
         0xF0h - OS/2 2.x
         0x6C - BMP Version 4(Windows 95)*/
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);   
        return HI_FAILURE;
    }

    pInfoHeader->biSize = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);
    if (pInfoHeader->biSize != 0x28) /** only support bmp Version 3 */
    {
        HIGO_ERROR(HI_FAILURE);   
        return HI_FAILURE;
    }

    /** ImageWidth */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);      
        return HI_FAILURE;
    }

    pInfoHeader->biWidth = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    /** ImageHeight*/
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);   
        return HI_FAILURE;
    }

    pInfoHeader->biHeight = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    /** Planes always is 1 */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_WORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);       
        return HI_FAILURE;
    }

    pInfoHeader->biPlanes = Bytes[0] | (Bytes[1] << 8);
    if (1 != pInfoHeader->biPlanes)
    {
        HIGO_ERROR(HI_FAILURE);      
        return HI_FAILURE;
    }

    /** BitCount */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_WORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);      
        return HI_FAILURE;
    }

    pInfoHeader->biBitCount = Bytes[0] | (Bytes[1] << 8);

    /** Compression 0-no compress 1- RLE 8  2-RLE 4 3-Bitfields */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);       
        return HI_FAILURE;
    }

    pInfoHeader->biCompression = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    /** ImageSize */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);     
        return HI_FAILURE;
    }

    pInfoHeader->biSizeImage = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    /** HResolution */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);     
        return HI_FAILURE;
    }

    pInfoHeader->biXPelsPerMeter = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    /** VResolution */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);     
        return HI_FAILURE;
    }

    pInfoHeader->biYPelsPerMeter = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    /** Colors */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);      
        return HI_FAILURE;
    }

    pInfoHeader->biClrUsed = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    /** Colors Important */
    ret = HIGO_ADP_IORead(pstStream, Bytes, BMP_DWORD_LEN, &CopyLen, &EndFlag);
    if (HI_SUCCESS != ret)
    {
        HIGO_ERROR(HI_FAILURE);     
        return HI_FAILURE;
    }

    pInfoHeader->biClrImportant = Bytes[0] | (Bytes[1] << 8) | (Bytes[2] << 16) | (Bytes[3] << 24);

    return HI_SUCCESS;
}


/***************************************************************************************
* func          : BMP_ParseFile
* description   : CNcomment: 文件解析 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 BMP_ParseFile(BMP_DECODER_S *pDecoder)
{
    HI_S32 ret = HI_SUCCESS;

    ret = BMP_ParseFileHeader((IO_INSTANCE_S* const)(&(pDecoder->stStream)), &(pDecoder->FileHeader));
    if (HI_SUCCESS != ret){
        HIGO_ERROR(HI_FAILURE);   
        return HI_FAILURE;
    }

    ret = BMP_ParseInfoHeader((IO_INSTANCE_S* const)(&(pDecoder->stStream)), &(pDecoder->InfoHeader));
    if (HI_SUCCESS != ret){
        HIGO_ERROR(HI_FAILURE);   
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : BMP_DecCommInfo
* description   : CNcomment: 获取图片基本信息 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_DecCommInfo(BMP_HANDLE BmpDec, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo)
{

    BMP_DECODER_S *pBmpDec = (BMP_DECODER_S*)BmpDec;

	if(NULL == pPrimaryInfo || NULL == pBmpDec){
		return HI_FAILURE;
	}

    pPrimaryInfo->Count     = 1;
    pPrimaryInfo->ImgType   = HIGO_DEC_IMGTYPE_BMP;
    pPrimaryInfo->ScrWidth  = (HI_U32)(pBmpDec->InfoHeader.biWidth);
    if(pBmpDec->InfoHeader.biHeight < 0)
        pPrimaryInfo->ScrHeight = -pBmpDec->InfoHeader.biHeight;
    else
        pPrimaryInfo->ScrHeight = pBmpDec->InfoHeader.biHeight;

    pPrimaryInfo->IsHaveBGColor = HI_FALSE;

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : BMP_GetPixelFmt
* description   : CNcomment: 获取像素格式 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID BMP_GetPixelFmt(const BMP_DECODER_S *pBmpDec, HIGO_PF_E *pFormat)
{
	if(NULL == pBmpDec || NULL == pFormat){
		return;
	}
    switch (pBmpDec->InfoHeader.biBitCount){
	    case 24:
	    case 32:
	        *pFormat = HIGO_PF_8888;
	        break;
	    default:
	        *pFormat = HIGO_PF_BUTT;
    }
}

/***************************************************************************************
* func          : BMP_DecImgInfo
* description   : CNcomment: 解析图片信息 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_DecImgInfo(BMP_HANDLE BmpDec, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo)
{

    BMP_DECODER_S *pBmpDec = (BMP_DECODER_S*)BmpDec;

	if(NULL == pBmpDec || NULL == pImgInfo){
		return HI_FAILURE;
	}

    pImgInfo->Width  = (HI_U32)pBmpDec->InfoHeader.biWidth;
    pImgInfo->Height = (HI_U32)(pBmpDec->InfoHeader.biHeight);
    
    if(pBmpDec->InfoHeader.biHeight<0){
        pImgInfo->Height = -pBmpDec->InfoHeader.biHeight;
    }else{
        pImgInfo->Height = pBmpDec->InfoHeader.biHeight;
    }
    
    BMP_GetPixelFmt(pBmpDec, &(pImgInfo->Format));
    
	if(HIGO_PF_BUTT == pImgInfo->Format){
		return HI_FAILURE;
	}
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : BMP_CreateDecoder
* description   : CNcomment: 创建bmp解码器 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_CreateDecoder(BMP_HANDLE *pBmpDec, const HIGO_DEC_ATTR_S *pSrcDesc)
{
    HI_S32 ret        = HI_SUCCESS;
    BMP_DECODER_S *pBmpDecoder = NULL;
    
    pBmpDecoder = (BMP_DECODER_S*)HIGO_Malloc(sizeof(BMP_DECODER_S));
    if(HI_NULL == pBmpDecoder){
        HIGO_ERROR(HIGO_ERR_NOMEM);   
        return HIGO_ERR_NOMEM;
    }
    HIGO_MemSet(pBmpDecoder, 0, sizeof(BMP_DECODER_S));

    ret = HIGO_ADP_IOCreate(&(pBmpDecoder->stStream), pSrcDesc->SrcInfo.MemInfo.pAddr,pSrcDesc->SrcInfo.MemInfo.Length);
    if (HI_SUCCESS != ret){
        HIGO_ERROR(ret);  
        goto ERR1;
    }
    
    ret = BMP_ParseFile(pBmpDecoder);
    if (HI_SUCCESS != ret){
        goto ERR2;
    }

    if(0 != pBmpDecoder->InfoHeader.biCompression)
    {/** 只支持非压缩的的bmp文件 **/
    	goto ERR2;
    }

    *pBmpDec = (BMP_HANDLE)pBmpDecoder;
    
    return HI_SUCCESS;
    
ERR2:
    HIGO_ADP_IODestroy(&(pBmpDecoder->stStream));

ERR1:
    if (HI_NULL != pBmpDecoder){
        HIGO_Free(pBmpDecoder);
        pBmpDecoder = HI_NULL;
    }

    return HI_FAILURE;

} /*lint !e818 */

/***************************************************************************************
* func          : BMP_DecImgData
* description   : CNcomment: 解图片数据，只支持0888 8888两种像素格式得
                             要是图片为0888得直接转成8888输出 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_DecImgData(BMP_HANDLE BmpDec, HI_U32 Index, HIGO_SURFACE_S *pSurface)
{
    HI_S32 s32Ret       = HI_SUCCESS;
    HI_U32 DstPitch     = 0;
    HI_U32 i            = 0;
    HI_U32 j            = 0;
    HI_U32 u32SrcStride = 0;
    HI_U32 Width        = 0;
    HI_U32 Height       = 0;
    HI_U8 *pDstData = NULL;
    HI_U8 *pDstPos  = NULL;
    HI_U8 *pSrcData = NULL;
    HI_U8 *pSrcPos  = NULL;
    HIGO_PF_E PixFmt = HIGO_PF_BUTT;
    
	HI_U32 SrcLen      = 0;

    HI_PIXELDATA pData;

	BMP_DECODER_S *pBmpDec = (BMP_DECODER_S*)BmpDec;
	
	if(NULL == pBmpDec){
		return HI_FAILURE;
	}
	if(NULL == pSurface){
		return HI_FAILURE;
	}

    Width  = (HI_U32)(pBmpDec->InfoHeader.biWidth);
    if(pBmpDec->InfoHeader.biHeight < 0){
        Height = -pBmpDec->InfoHeader.biHeight;
    }else{
         Height = pBmpDec->InfoHeader.biHeight;
    }

	if(Width <= 0 || Height <= 0){
		return HI_FAILURE;
	}
	
    BMP_GetPixelFmt(pBmpDec, &PixFmt);
    if(HIGO_PF_BUTT == PixFmt){
        HIGO_ERROR(HI_FAILURE); 
        return HI_FAILURE;
    }

	(HI_VOID)Surface_LockSurface((HIGO_HANDLE)pSurface, pData);
    	DstPitch = pData[0].Pitch;
   		pDstData = (HI_U8*)pData[0].pData;
	(HI_VOID)Surface_UnlockSurface((HIGO_HANDLE)pSurface);

    u32SrcStride = ((Width * pBmpDec->InfoHeader.biBitCount + 31) / 32) * 4;
    SrcLen       = Height * u32SrcStride;
	if(SrcLen < pBmpDec->InfoHeader.biSizeImage){
		HIGO_ERROR(HI_FAILURE); 
        return HI_FAILURE;
	}
    pSrcData = (HI_U8*)HIGO_MMZ_Malloc(SrcLen);
    if(NULL == pSrcData || NULL == pDstData){
        HIGO_ERROR(HIGO_ERR_NOMEM);
        return HIGO_ERR_NOMEM;
    }
    

    s32Ret = BMP_NoRle_Decode(pBmpDec, pSrcData);
    if (HI_SUCCESS != s32Ret){
        HIGO_ERROR(s32Ret);
        goto ERR2;
    }

    for (i = 0; i < Height; i++){
        if(pBmpDec->InfoHeader.biHeight > 0){
        /** 负向图像 */
	         pDstPos = pDstData + ((Height - 1) - i) * DstPitch;
	    }else{
	     /** 正向图像 */
	         pDstPos = pDstData + i * DstPitch;
	    }
        pSrcPos = pSrcData + i * u32SrcStride;

        if(32 == pBmpDec->InfoHeader.biBitCount){
	        for (j = 0; j < Width; j++){
	            HIGO_MemCopy(pDstPos, pSrcPos, 4);
	            pDstPos[3] = 0xff;
	            pDstPos   += 4;
	            pSrcPos   += 4;
	        }
        }else{
			for (j = 0; j < Width; j++){
	            HIGO_MemCopy(pDstPos, pSrcPos, 3);
	            pDstPos[3] = 0xff;
	            pDstPos   += 4;
	            pSrcPos   += 3;
	        }
        }
    }

	if(NULL != pSrcData){
    	HIGO_MMZ_Free(pSrcData);
	}
	
    return HI_SUCCESS;

ERR2:
    if(NULL != pSrcData){
    	HIGO_MMZ_Free(pSrcData);
	}
    
    return HI_FAILURE;
}

/***************************************************************************************
* func          : BMP_DestroyDecoder
* description   : CNcomment: 销毁bmp解码器 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 BMP_DestroyDecoder(BMP_HANDLE BmpDec)
{
    BMP_DECODER_S *pBmpDecoder = (BMP_DECODER_S*)BmpDec;

	if(NULL == pBmpDecoder){
    	return HI_SUCCESS;
	}
	HIGO_ADP_IODestroy(&(pBmpDecoder->stStream));
	
	HIGO_Free(pBmpDecoder);
	
	pBmpDecoder = HI_NULL;

    return HI_SUCCESS;
}
