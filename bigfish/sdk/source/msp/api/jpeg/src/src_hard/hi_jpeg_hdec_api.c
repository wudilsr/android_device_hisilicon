/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : hi_jpeg_hdec_api.c
Version		    : Initial Draft
Author		    :
Created		    : 2014/06/20
Description	    : The user will use this api to realize some function
Function List 	:


History       	:
Date				Author        		Modification
2014/06/20		    y00181162  		    Created file
******************************************************************************/

/****************************  add include here     ***************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "hi_jpeg_config.h"
#include "jpeg_hdec_api.h"
#include "jpeg_hdec_adp.h"
#include "hi_jpeg_api.h"

/***************************** Macro Definition     ***************************/

#define JPEG_CHECK_FD() \
    do {                                 \
        if(-1 == gs_s32JpegFd){          \
            return HI_FAILURE;          \
        }                                \
    } while (0)

/***************************** Structure Definition ***************************/

/********************** Global Variable declaration **************************/

#ifdef CONFIG_JPEG_OMX_FUNCTION

static HI_S32 gs_s32JpegFd  = -1;
static HI_S32 gs_s32JpegRef = 0;

#endif

/********************** API forward declarations    **************************/

/**********************       API realization       **************************/

/**
 \brief Sets dec output message. CNcomment:���ý����������Ϣ������ CNend
 \attention \n
HI_JPEG_SetOutDesc should have called create jpeg decoder.set the output address \n
and output stride,set whether crop, set crop rect \n
CNcomment:�����ڴ���������֮����������֮ǰ���øýӿڣ���Ҫ���ý��������ַ����� \n
          �м�࣬�����Ƿ�ü��Լ���Ӧ�Ĳü����� CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[in]	*pstSurfaceDesc. CNcomment:�������������Ϣ CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetOutDesc
 */

HI_S32  HI_JPEG_SetOutDesc(const struct jpeg_decompress_struct *cinfo,
                           const HI_JPEG_SURFACE_DESCRIPTION_S *pstSurfaceDesc)
{
	HI_S32 s32Cnt = 0;
	JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	if (NULL == pstSurfaceDesc){
		return HI_FAILURE;
	}

	for (s32Cnt = 0; s32Cnt < MAX_PIXEL_COMPONENT_NUM; s32Cnt++){
		pJpegHandle->stOutDesc.stOutSurface.pOutPhy[s32Cnt] = pstSurfaceDesc->stOutSurface.pOutPhy[s32Cnt];
		pJpegHandle->stOutDesc.stOutSurface.pOutVir[s32Cnt] = pstSurfaceDesc->stOutSurface.pOutVir[s32Cnt];
		pJpegHandle->stOutDesc.stOutSurface.u32OutStride[s32Cnt] = pstSurfaceDesc->stOutSurface.u32OutStride[s32Cnt];
	}

	pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem = pstSurfaceDesc->stOutSurface.bUserPhyMem;

	if (HI_TRUE == pstSurfaceDesc->bCrop){
		if( (pstSurfaceDesc->stCropRect.w <= 0)||(pstSurfaceDesc->stCropRect.h <= 0)){
			return HI_FAILURE;
		}
		pJpegHandle->stOutDesc.stCropRect.x = pstSurfaceDesc->stCropRect.x;
		pJpegHandle->stOutDesc.stCropRect.y = pstSurfaceDesc->stCropRect.y;
		pJpegHandle->stOutDesc.stCropRect.w = pstSurfaceDesc->stCropRect.w;
		pJpegHandle->stOutDesc.stCropRect.h = pstSurfaceDesc->stCropRect.h;
	}

	pJpegHandle->stOutDesc.bCrop = pstSurfaceDesc->bCrop;

	return HI_SUCCESS;
	
}

/**
 \brief Get Jpeg information. CNcomment:��ȡjpegͼƬ��Ϣ CNend
 \attention \n
if you want to get input format and input width and input height,you should set bOutInfo false.\n
others you can get the information as follows: output rgb widht/height/stride/size or output \n
yuvsp lu width/height/stride/size and ch width/height/stride/size.\n
you call this function should after read header and set the ouput parameter.\n
CNcomment:��bOutInfo���ó�FALSE��ʱ�򣬿��Ի�ȡ��ͼƬ����Ŀ�Ⱥ͸߶��Լ����ظ�ʽ�������ó�TRUE�� \n
          ʱ������Ի�ȡ��������Ϣ��Ҫ�ǽ���RGB���ȡ�����/�߶�/�м��/��С,Ҫ�ǽ������yuvsp��\n
          ����Ի�ȡ�����Ⱥ�ɫ�ȵĿ��/�߶�/�м��/��С����Ϣ�� CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[out] pJpegInfo.	CNcomment:����jpeg�������Ϣ  CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_GetJpegInfo
 */
HI_S32  HI_JPEG_GetJpegInfo(j_decompress_ptr cinfo, HI_JPEG_INFO_S *pJpegInfo)
{
		JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		if (NULL == pJpegInfo){
			return HI_FAILURE;
		}

		if (HI_FALSE == pJpegInfo->bOutInfo){
			memset(pJpegInfo, 0, sizeof(HI_JPEG_INFO_S));
			pJpegInfo->u32Width[0]  = cinfo->image_width;
			pJpegInfo->u32Height[0] = cinfo->image_height;
			pJpegInfo->enFmt = pJpegHandle->enImageFmt;
			return HI_SUCCESS;
		}

		JPEG_HDEC_GetImagInfo(cinfo);

		/**
		** output message,the output stride should 16byte align by tde request
		** CNcomment: �����Ϣ CNend\n
		**/
		switch (cinfo->out_color_space){
			case JCS_YUV400_SP:
			case JCS_YUV444_SP:
			case JCS_YUV420_SP:
			case JCS_YUV422_SP_12:
			case JCS_YUV422_SP_21:
				pJpegInfo->u32Width[0]  = pJpegHandle->stJpegSofInfo.u32YWidth;
				pJpegInfo->u32Width[1]  = pJpegHandle->stJpegSofInfo.u32CWidth;
				pJpegInfo->u32Height[0] = pJpegHandle->stJpegSofInfo.u32YHeight;
				pJpegInfo->u32Height[1] = pJpegHandle->stJpegSofInfo.u32CHeight;
				pJpegInfo->u32OutStride[0] = pJpegHandle->stJpegSofInfo.u32YStride;
				pJpegInfo->u32OutStride[1] = pJpegHandle->stJpegSofInfo.u32CbCrStride;
				pJpegInfo->u32OutSize[0] = pJpegHandle->stJpegSofInfo.u32YSize;
				pJpegInfo->u32OutSize[1] = pJpegHandle->stJpegSofInfo.u32CSize;
				break;
			case JCS_ARGB_8888:
			case JCS_ABGR_8888:
			case JCS_CMYK:
			#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
			case JCS_RGBA_8888:
			#endif
			case JCS_RGB:
			case JCS_BGR:
			case JCS_RGB_565:
			case JCS_BGR_565:
			case JCS_ARGB_1555:
			case JCS_ABGR_1555:
			case JCS_CrCbY:
			case JCS_YCbCr:
			case JCS_GRAYSCALE:
				pJpegInfo->u32Width[0]  = cinfo->output_width;
				pJpegInfo->u32Height[0] = cinfo->output_height;
				pJpegInfo->u32OutStride[0] = pJpegHandle->stJpegSofInfo.u32DisplayStride;
				pJpegInfo->u32OutSize[0] = pJpegInfo->u32OutStride[0] * pJpegInfo->u32Height[0];
				break;
			default:
				break;
		}

		/**
		** now use save dec width and height and stride and size.
		** CNcomment: ��ʱ��Ϊ����ֱ����� CNend\n
		**/
		pJpegInfo->u32Width[2]     = pJpegHandle->stJpegSofInfo.u32DecW;
		pJpegInfo->u32Height[2]    = pJpegHandle->stJpegSofInfo.u32DecH;
		pJpegInfo->u32OutStride[2] = pJpegHandle->stJpegSofInfo.u32DecStride;
		pJpegInfo->u32OutSize[2]   = pJpegInfo->u32OutStride[2] * pJpegInfo->u32Height[2];

		return HI_SUCCESS;
	
}

/**
 \brief set jpeg dec inflexion. CNcomment:��Ӳ������֧�ֵ�����£���������Ӳ��Ĺյ� CNend
 \attention \n
HI_JPEG_SetInflexion should have called jpeg_create_decompress.if no call this \n
function,use the default flexion \n
CNcomment:�����ڴ����������֮����øú�����Ҫ��û�����ùյ㣬ʹ��Ĭ�ϵĹյ��С CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[in]	u32flexionSize. CNcomment:Ҫ���õĽ���յ��С CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetInflexion
 */
HI_S32 HI_JPEG_SetInflexion(const struct jpeg_decompress_struct *cinfo, const HI_U32 u32flexionSize)
{
	JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	pJpegHandle->u32Inflexion = u32flexionSize;

	return HI_SUCCESS;
}

/**
 \brief get jpeg dec inflexion. CNcomment:��ȡ�����Ӳ������Ĺյ� CNend
 \attention \n
HI_JPEG_GetInflexion should have called jpeg_create_decompress.\n
CNcomment:�ڵ���HI_JPEG_GetInflexion֮ǰ�����Ѿ��������˽����� CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[out] pu32flexionSize. CNcomment:����յ��С CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetInflexion
 */
HI_S32 HI_JPEG_GetInflexion(const struct jpeg_decompress_struct *cinfo, HI_U32 *pu32flexionSize)
{
	JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	if (NULL == pu32flexionSize){
		return HI_FAILURE;
	}

	*pu32flexionSize = pJpegHandle->u32Inflexion;

	return HI_SUCCESS;
}

/**
 \brief set jpeg dec coef when output argb. CNcomment:�ڽ������ARGB��������������ϵ�� CNend
 \attention \n
HI_JPEG_SetDecCoef should have called jpeg_create_decompress.set whether horizontal \n
and vertical fliter,whether set horizontal and ver sample, whether set csc coefficient, \n
and set there coefficient.if no call this function, use the default parameter. \n
CNcomment:�����ڴ����������֮����øú�������Ҫ�����Ƿ�ֱ��ˮƽ�˲����Ƿ����ô�ֱ��ˮƽ \n
          ����ϵ�����Ƿ�����CSSϵ�������������Ӧ��ϵ����Ҫ��û�е��øú�����ʹ��Ĭ��ֵ CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[in]	*pstDecCoef. CNcomment:����ϵ�� CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetDecCoef
 */
HI_S32 HI_JPEG_SetDecCoef(const struct jpeg_decompress_struct *cinfo, const HI_JPEG_DEC_COEF_S *pstDecCoef)
{
#ifdef CONFIG_JPEG_HARDDEC2ARGB
	HI_S32 s32Cnt1 = 0;
	HI_S32 s32Cnt2 = 0;
	
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (NULL == pstDecCoef){
        return HI_FAILURE;
    }

    pJpegHandle->stDecCoef.bEnHorMedian = pstDecCoef->bEnHorMedian;
    pJpegHandle->stDecCoef.bEnVerMedian = pstDecCoef->bEnVerMedian;
    pJpegHandle->stDecCoef.bSetHorSampleCoef = pstDecCoef->bSetHorSampleCoef;
    pJpegHandle->stDecCoef.bSetVerSampleCoef = pstDecCoef->bSetVerSampleCoef;
    pJpegHandle->stDecCoef.bSetCSCCoef = pstDecCoef->bSetCSCCoef;

	for(s32Cnt1 = 0; s32Cnt1 < MAX_HORCOEF_ROW; s32Cnt1++){
		for(s32Cnt2 = 0; s32Cnt2 < MAX_HORCOEF_COL; s32Cnt2++){
           pJpegHandle->stDecCoef.s16HorCoef[s32Cnt1][s32Cnt2] = pstDecCoef->s16HorCoef[s32Cnt1][s32Cnt2];
		}
	}
	for(s32Cnt1 = 0; s32Cnt1 < MAX_VERCOEF_ROW; s32Cnt1++){
		for(s32Cnt2 = 0; s32Cnt2 < MAX_VERCOEF_COL; s32Cnt2++){
           pJpegHandle->stDecCoef.s16VerCoef[s32Cnt1][s32Cnt2] = pstDecCoef->s16VerCoef[s32Cnt1][s32Cnt2];
		}
	}
	for(s32Cnt1 = 0; s32Cnt1 < MAX_CSCCOEF_ROW; s32Cnt1++){
		for(s32Cnt2 = 0; s32Cnt2 < MAX_CSCCOEF_COL; s32Cnt2++){
           pJpegHandle->stDecCoef.s16CSCCoef[s32Cnt1][s32Cnt2] = pstDecCoef->s16CSCCoef[s32Cnt1][s32Cnt2];
		}
	}
	
    return HI_SUCCESS;

#else
	if(NULL == cinfo || NULL == pstDecCoef)/** deal with warning **/
			return HI_FAILURE;
	else
    		return HI_FAILURE;
#endif

}

/**
 \brief get jpeg dec coef when output argb. CNcomment:�ڽ������ARGB������»�ȡ���õ����ϵ�� CNend
 \attention \n
HI_JPEG_GetDecCoef should have called HI_JPEG_SetDecCoef.\n
CNcomment:�ڵ���HI_JPEG_GetDecCoef֮ǰ�����Ѿ�HI_JPEG_SetDecCoef CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[out]	pstOutDecCoef. CNcomment:�������ϵ�� CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_GetDecCoef
 */
#ifdef CONFIG_JPEG_HARDDEC2ARGB
HI_S32 HI_JPEG_GetDecCoef(const struct jpeg_decompress_struct *cinfo, HI_JPEG_DEC_COEF_S *pstOutDecCoef)
{
	HI_S32 s32Cnt1 = 0;
	HI_S32 s32Cnt2 = 0;
	
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (NULL == pstOutDecCoef){
        return HI_FAILURE;
    }

    pstOutDecCoef->bEnHorMedian = pJpegHandle->stDecCoef.bEnHorMedian;
    pstOutDecCoef->bEnVerMedian = pJpegHandle->stDecCoef.bEnVerMedian;
    pstOutDecCoef->bSetHorSampleCoef = pJpegHandle->stDecCoef.bSetHorSampleCoef;
    pstOutDecCoef->bSetVerSampleCoef = pJpegHandle->stDecCoef.bSetVerSampleCoef;
    pstOutDecCoef->bSetCSCCoef = pJpegHandle->stDecCoef.bSetCSCCoef;

	for(s32Cnt1 = 0; s32Cnt1 < MAX_HORCOEF_ROW; s32Cnt1++){
		for(s32Cnt2 = 0; s32Cnt2 < MAX_HORCOEF_COL; s32Cnt2++){
		   pstOutDecCoef->s16HorCoef[s32Cnt1][s32Cnt2] = pJpegHandle->stDecCoef.s16HorCoef[s32Cnt1][s32Cnt2];
		}
	}
	for(s32Cnt1 = 0; s32Cnt1 < MAX_VERCOEF_ROW; s32Cnt1++){
		for(s32Cnt2 = 0; s32Cnt2 < MAX_VERCOEF_COL; s32Cnt2++){
		   pstOutDecCoef->s16VerCoef[s32Cnt1][s32Cnt2] = pJpegHandle->stDecCoef.s16VerCoef[s32Cnt1][s32Cnt2];
		}
	}
	for(s32Cnt1 = 0; s32Cnt1 < MAX_CSCCOEF_ROW; s32Cnt1++){
		for(s32Cnt2 = 0; s32Cnt2 < MAX_CSCCOEF_COL; s32Cnt2++){
		   pstOutDecCoef->s16CSCCoef[s32Cnt1][s32Cnt2] = pJpegHandle->stDecCoef.s16CSCCoef[s32Cnt1][s32Cnt2];
		}
	}
    return HI_SUCCESS;

}
#else
HI_S32 HI_JPEG_GetDecCoef(const struct jpeg_decompress_struct *cinfo, HI_JPEG_DEC_COEF_S *pstOutDecCoef)
{
	if (NULL != pstOutDecCoef && NULL != cinfo){/** deal with warning **/
		memset(pstOutDecCoef,0,sizeof(HI_JPEG_DEC_COEF_S));
	}
	return HI_FAILURE;
}
#endif

/**
 \brief set alpha value. CNcomment:����alpha��ֵ CNend
 \attention \n
HI_JPEG_SetAlpha should have called jpeg_create_decompress.when decode output \n
argb8888 and argb8888,we can call this function,if no call it,use the default value. \n
CNcomment:�����ڴ����������֮����øú��������������ΪARGB8888��ABGR8888��ʱ����� \n
���øú�����Ҫ��û�е��øú�������ʹ��Ĭ�ϵ�ֵ CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[in]	s32Alpha. CNcomment:����alphaֵ CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetAlpha
 */
HI_S32 HI_JPEG_SetAlpha(const struct jpeg_decompress_struct *cinfo, const HI_U32 u32Alpha)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    pJpegHandle->u32Alpha = u32Alpha;

    return HI_SUCCESS;
}

/**
 \brief set stream from flag of use phy mem	or virtual mem. CNcomment:���������������������ڴ���Ϣ CNend
 \attention \n
if want to use this function,should call between create decompress and
jpeg_stdio_src or jpeg_mem_src.if not call this we should check\n
CNcomment:���Ҫ���ã������ڴ������������������֮ǰ���ã����û�е��øýӿ�Ҳ�п������������ڴ� CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[in]	pStreamPhyAddr. CNcomment:���������ַ CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetStreamPhyMem
 */
HI_S32 HI_JPEG_SetStreamPhyMem(const struct jpeg_decompress_struct *cinfo, HI_CHAR* pStreamPhyAddr)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    if (NULL == pStreamPhyAddr){
        return HI_FAILURE;
    }

    pJpegHandle->stHDecDataBuf.pDataPhyBuf = pStreamPhyAddr;
    pJpegHandle->stHDecDataBuf.bUserPhyMem = HI_TRUE;

    return HI_SUCCESS;
}

/** 
 \brief set stream mem information. CNcomment:���������ڴ���Ϣ CNend
 \attention \n
 if want to use this function,should call between create decompress and 
 jpeg_stdio_src or jpeg_mem_src.if not call this we should check\n
 CNcomment:���Ҫ���ã������ڴ������������������֮ǰ���� CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[in]	pPhyStremBuf.         CNcomment:����buffer��ʼ�����ַ CNend
 \param[in]	u32StremBufLen.       CNcomment:����buffer��С         CNend
 \param[in]	pVirSaveReturnBuf.    CNcomment:����buffer������ʼ��ַ CNend
 \param[in]	s32StrmReturnSize.    CNcomment:����������С           CNend
 \param[in]	bStreamBufNeedReturn. CNcomment:����buffer�Ƿ����     CNend

 \retval ::HI_SUCCESS 
 \retval ::HI_FAILURE

 \see \n
 ::HI_JPEG_SetBufInfo
 */
HI_S32 HI_JPEG_SetBufInfo(const struct jpeg_decompress_struct *cinfo,HI_CHAR* pPhyStremBuf,HI_U32 u32StremBufLen, HI_CHAR* pVirSaveReturnBuf,HI_S32 s32StrmReturnSize,HI_BOOL bStreamBufNeedReturn)
{

	JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	if(NULL == pPhyStremBuf){
		/** Ҫ�����������Ʊ���������Դ�������ַ **/
		return HI_FAILURE;
	}

#ifdef CONFIG_JPEG_STREAMBUF_4ALIGN
	if(0 != (HI_S32)pPhyStremBuf % 4){/**���ǰ���4�ֽڶ��룬��֧�� **/
		return HI_FAILURE;
	}
#endif
	pJpegHandle->stHDecDataBuf.pStartBufPhy = pPhyStremBuf;
	pJpegHandle->stHDecDataBuf.s32BufLen    = u32StremBufLen;
    pJpegHandle->stHDecDataBuf.pDataVirBufReturn  = pVirSaveReturnBuf;
	pJpegHandle->stHDecDataBuf.s32StreamReturnLen = s32StrmReturnSize;
	pJpegHandle->stHDecDataBuf.bNeedStreamReturn  = bStreamBufNeedReturn;
	
	return HI_SUCCESS;
	
}


/**
 \brief set if dec output yuv420sp. CNcomment:�����Ƿ�ͳһ���yuv420sp��ʶ CNend
 \attention \n
HI_JPEG_SetYCbCr420spFlag should have called jpeg_create_decompress.\n
CNcomment:�ڵ���HI_JPEG_SetYCbCr420spFlag֮ǰ�����Ѿ��������˽����� CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[in]	bOutYCbCr420sp. CNcomment:�Ƿ�ͳһ�������yuv420sp��ʽ CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetYCbCr420spFlag
 */
HI_S32 HI_JPEG_SetYCbCr420spFlag(const struct jpeg_decompress_struct *cinfo, const HI_BOOL bOutYCbCr420sp)
{
#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    pJpegHandle->bOutYUV420SP = bOutYCbCr420sp;

    return HI_SUCCESS;

#else
    return HI_FAILURE;
#endif

}

/**
 \brief set if output lu pixle sum value. CNcomment:�����Ƿ�ͳ������ֵ��ʶ CNend
 \attention \n
HI_JPEG_SetLuPixSumFlag should have called jpeg_create_decompress.\n
CNcomment:�ڵ���HI_JPEG_SetLuPixSumFlag֮ǰ�����Ѿ��������˽����� CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[in]	bLuPixSum. CNcomment:�����Ƿ�ͳ������ֵ��ʶ CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_SetLuPixSumFlag
 */
HI_S32 HI_JPEG_SetLuPixSumFlag(const struct jpeg_decompress_struct *cinfo, const HI_BOOL bLuPixSum)
{
#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

    pJpegHandle->bLuPixSum = bLuPixSum;

    return HI_SUCCESS;

#else
    return HI_FAILURE;
#endif

}

/**
 \brief get lu pixle sum value. CNcomment:��ȡ����ֵ CNend
 \attention \n
If you want to get the luminance value, you can call this function, \n
but you should call it after jpeg_start_decompress and have call HI_JPEG_SetLuPixSumFlag.\n
CNcomment:Ҫ����õ�����ֵ�����Ե��øú�������������jpeg_start_decompress֮����ö��ҽ��� \n
          ֮ǰҪ����HI_JPEG_SetLuPixSumFlag CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[out] u64LuPixSum. CNcomment:�������ֵ CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_GetLuPixSum
 */
HI_S32 HI_JPEG_GetLuPixSum(const struct jpeg_decompress_struct *cinfo, HI_U64 *u64LuPixSum)

{
	if (NULL == u64LuPixSum){
		return HI_FAILURE;
	}

#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
	JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	if(HI_TRUE == pJpegHandle->bLuPixSum){
		*u64LuPixSum = pJpegHandle->u64LuPixValue;
	}
	return HI_SUCCESS;

#else
	*u64LuPixSum = 0;
	return HI_FAILURE;
#endif

}

/**
 \brief get jpeg dec time. CNcomment:��ȡjpeg����ʱ�� CNend
 \attention \n
If you want to know how much the decode cost time ,you can call HI_JPEG_GetDecTime, \n
but should have called it after jpeg_finish_decompress.\n
CNcomment:Ҫ���뿴���뻨���˶���ʱ����Ե��øú������������ڽ������֮����� CNend\n

 \param[in]	cinfo. CNcomment:������� CNend
 \param[out] pu32DecTime. CNcomment:�����������ʱ�� CNend

 \retval ::HI_SUCCESS
 \retval ::HI_FAILURE

 \see \n
::HI_JPEG_GetDecTime
 */
HI_S32 HI_JPEG_GetDecTime(const struct jpeg_decompress_struct *cinfo, HI_U32 *pu32DecTime)
{
#ifdef CONFIG_JPEG_GETDECTIME

	JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	if (NULL == pu32DecTime){
		return HI_FAILURE;
	}

	*pu32DecTime = pJpegHandle->u32DecTime;

	return HI_SUCCESS;

#else

	return HI_FAILURE;

#endif
}


/** 
\brief set the leave memory size. CNcomment:����ʣ���ڴ��С���Թ�����ʹ�� CNend
\attention \n
should have called it after  create jpeg decoder.\n
CNcomment:�����ڴ���������֮����� CNend\n

\param[in]	cinfo. CNcomment:������� CNend
\param[int] sMemSizeInfo. CNcomment:�ڴ���Ϣ CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_SetLeaveMemSize
*/
HI_S32 HI_JPEG_SetLeaveMemSize(const struct jpeg_decompress_struct *cinfo, HI_JPEG_MEMSIZE_INFO_S sMemSizeInfo)
{

	HI_U32 u32MemSize = 0;
	JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	if(NULL == pJpegHandle){
		return HI_FAILURE;
	}

	switch(sMemSizeInfo.eCheckType){
		case JPEG_MEMCHECK_MEMSIZE:
			u32MemSize = sMemSizeInfo.u32MemSize;
			break;
		case JPEG_MEMCHECK_RESOLUTION:
			u32MemSize = sMemSizeInfo.u32Width * sMemSizeInfo.u32Height * 4;
			break;
		default:
			break;
	}
	
	pJpegHandle->u32LeaveMemSize = u32MemSize;
		
	return HI_SUCCESS;
	
}


 /** 
\brief set the mem type. CNcomment:�����ڴ����� CNend
\attention \n
HI_JPEG_SetMemType should have called before start decompress.\n
CNcomment:�ڵ���HI_JPEG_SetMemType֮ǰ�����Ѿ��������˽����� CNend\n

\param[in]	cinfo. CNcomment:������� CNend
\param[in]	u32MemTypeMask. CNcomment:�ڴ�ʹ������ CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_SetMemType
*/
#ifdef CONFIG_JPEG_MMU_SUPPORT
HI_S32 HI_JPEG_SetMemType(const struct jpeg_decompress_struct *cinfo,const HI_U32 u32MemTypeMask)
{
	JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	if(NULL == pJpegHandle){
		return HI_FAILURE;
	}
	pJpegHandle->u32MemTypeMask |= u32MemTypeMask;

	return HI_SUCCESS;
}
#endif


/** 
\brief open jpeg device. CNcomment:��jpeg�豸 CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  NULL. CNcomment:û��������� CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_Open
*/
HI_S32 HI_JPEG_Open(HI_VOID)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION

    if (-1 != gs_s32JpegFd){
        gs_s32JpegRef++;
        return HI_SUCCESS;
    }

    gs_s32JpegFd = open(JPG_DEV, O_RDWR | O_SYNC);
    if (gs_s32JpegFd < 0){
        return HI_FAILURE;
    }
    gs_s32JpegRef++;
    
    return HI_SUCCESS;
#else
    return HI_FAILURE;
#endif
}

/** 
\brief close jpeg device. CNcomment:�ر�jpeg�豸 CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  NULL. CNcomment:û��������� CNend

\retval ::NA 
\retval ::NA

\see \n
::HI_JPEG_Close
*/
HI_VOID HI_JPEG_Close(HI_VOID)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION
   if (-1 == gs_s32JpegFd){
        return;
    }
    gs_s32JpegRef--;
    
    if(gs_s32JpegRef > 0){
        return ;
    }else{
        gs_s32JpegRef = 0;
    }
    
    close(gs_s32JpegFd);

    gs_s32JpegFd = -1;

#endif

    return;
}
/** 
\brief create decode. CNcomment:���������� CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  *pu32Handle.  CNcomment:���ؽ�������� CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_CreateDec
*/
HI_S32 HI_JPEG_CreateDec(HI_U32 *pu32Handle)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION

    HI_S32 u32DecHandle = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    JPEG_CHECK_FD();
    
    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_CREATEDEC, &u32DecHandle);
    if(HI_SUCCESS != s32Ret){
        return HI_FAILURE;
    }
    
    *pu32Handle = u32DecHandle;

    return HI_SUCCESS;

#else
    return HI_FAILURE;
#endif

}

/** 
\brief set dec memory type. CNcomment: ���ý�����Ҫ���ڴ����� CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  u32Handle.         CNcomment:��������� CNend
\param[in]  u32MemTypeMask.    CNcomment:�ڴ�����   CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_SetDecMemType
*/
#ifdef CONFIG_JPEG_MMU_SUPPORT
HI_S32 HI_JPEG_SetDecMemType(HI_U32 u32Handle,HI_U32 u32MemTypeMask)
{
	HI_DRV_JPEG_INMSG_S stImgInfo;
    HI_S32 s32Ret = HI_SUCCESS;

    JPEG_CHECK_FD();

    memset(&stImgInfo,0,sizeof(HI_JPEG_INMSG_S));

    stImgInfo.u32MemMask     = u32MemTypeMask;
    stImgInfo.u32DecHandle   = u32Handle;

	s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_SETMEMTYPE, &stImgInfo);
    if(HI_SUCCESS != s32Ret){
        return HI_FAILURE;
    }

	return HI_SUCCESS;
}
#endif

/** 
\brief get jpeg input information. CNcomment:��ȡͼƬ������Ϣ CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  u32Handle.  CNcomment:��������� CNend
\param[in]  stInMsg.    CNcomment:������Ϣ   CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_DecInfo
*/
HI_S32 HI_JPEG_DecInfo(HI_U32 u32Handle,HI_JPEG_INMSG_S *stInMsg)
{

#ifdef CONFIG_JPEG_OMX_FUNCTION

    HI_DRV_JPEG_INMSG_S stImgInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    
    JPEG_CHECK_FD();
    
    if(NULL == stInMsg){
        return HI_FAILURE;
    }

    memset(&stImgInfo,0,sizeof(HI_JPEG_INMSG_S));

    /** ͨ������buffer����ͼ��������� **/
    stImgInfo.pAllPhy        = stInMsg->pAllPhy;
    stImgInfo.pSavePhy       = stInMsg->pSavePhy;
    stImgInfo.pSaveVir[0]    = stInMsg->pSaveVir[0];
    stImgInfo.pSaveVir[1]    = stInMsg->pSaveVir[1];
    stImgInfo.u32AllLen      = stInMsg->u32AllLen;
    stImgInfo.u32SaveLen[0]  = stInMsg->u32SaveLen[0];
    stImgInfo.u32SaveLen[1]  = stInMsg->u32SaveLen[1];
    stImgInfo.s32InWidth     = stInMsg->s32InWidth;
    stImgInfo.s32InHeight    = stInMsg->s32InHeight;
    stImgInfo.bUserPhyMem    = stInMsg->bUserPhyMem;
    stImgInfo.enInFmt        = stInMsg->enInFmt;
    stImgInfo.u32DecHandle   = u32Handle;
        
    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_DECINFO, &stImgInfo);
    if(HI_SUCCESS != s32Ret){
        return HI_FAILURE;
    }
    stInMsg->s32InWidth  = stImgInfo.s32InWidth;
    stInMsg->s32InHeight = stImgInfo.s32InHeight;
    stInMsg->enInFmt     = stImgInfo.enInFmt;
    
    return HI_SUCCESS;
#else
    return HI_FAILURE;
#endif
}
/** 
\brief get jpeg output information. CNcomment:��ȡͼƬ�������Ϣ CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  u32Handle.  CNcomment:��������� CNend
\param[in]  stOutMsg.   CNcomment:������Ϣ   CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_DecOutInfo
*/
HI_S32 HI_JPEG_DecOutInfo(HI_U32 u32Handle,HI_JPEG_OUTMSG_S *stOutMsg)
{

#ifdef CONFIG_JPEG_OMX_FUNCTION

    HI_DRV_JPEG_OUTMSG_S stOutInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32Cnt = 0;
    
    JPEG_CHECK_FD();
    
    if(NULL == stOutMsg){
        return HI_FAILURE;
    }
    
    memset(&stOutInfo,0,sizeof(HI_JPEG_OUTMSG_S));

    /** �����Ƿ����ź��Ƿ�ͳһ���yuv420�������������Լ�stride **/
    for(s32Cnt = 0; s32Cnt < MAX_PIXEL_COMPONENT_NUM; s32Cnt++){
        stOutInfo.pOutPhy[s32Cnt]       = stOutMsg->pOutPhy[s32Cnt];
        stOutInfo.u32OutWidth[s32Cnt]   = stOutMsg->u32OutWidth[s32Cnt];
        stOutInfo.u32OutHeight[s32Cnt]  = stOutMsg->u32OutHeight[s32Cnt];
        stOutInfo.u32OutStride[s32Cnt]  = stOutMsg->u32OutStride[s32Cnt];
        stOutInfo.u32OutSize[s32Cnt]    = stOutMsg->u32OutSize[s32Cnt];
    }
    stOutInfo.s32Scale      = stOutMsg->s32Scale;
    stOutInfo.bOutYuvSp420  = stOutMsg->bOutYuvSp420;
    stOutInfo.bLuPixSum     = stOutMsg->bLuPixSum;
    stOutInfo.enOutFmt      = stOutMsg->enOutFmt;
    stOutInfo.u32DecHandle  = u32Handle;
     
    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_DECOUTINFO, &stOutInfo);
    if(HI_SUCCESS != s32Ret){
        return HI_FAILURE;
    }
    for(s32Cnt = 0; s32Cnt < MAX_PIXEL_COMPONENT_NUM; s32Cnt++){
        stOutMsg->u32OutWidth[s32Cnt]  = stOutInfo.u32OutWidth[s32Cnt];
        stOutMsg->u32OutHeight[s32Cnt] = stOutInfo.u32OutHeight[s32Cnt];
        stOutMsg->u32OutStride[s32Cnt] = stOutInfo.u32OutStride[s32Cnt];
        stOutMsg->u32OutSize[s32Cnt]   = stOutInfo.u32OutSize[s32Cnt];
    }
    stOutMsg->enOutFmt = stOutInfo.enOutFmt;
    
    return HI_SUCCESS;

#else
    return HI_FAILURE;
#endif  
}

/** 
\brief start jpeg hard decode. CNcomment:����jpegӲ������ CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  u32Handle.  CNcomment:��������� CNend
\param[in]  stInMsg.    CNcomment:������Ϣ   CNend
\param[in]  stOutMsg.   CNcomment:�����Ϣ   CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_Decode
*/
HI_S32 HI_JPEG_Decode(HI_U32 u32Handle,HI_JPEG_INMSG_S *stInMsg,HI_JPEG_OUTMSG_S *stOutMsg)
{

#ifdef CONFIG_JPEG_OMX_FUNCTION

    HI_JPEG_DECINFO_S stDecInfo;
    HI_S32 s32Cnt = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    
    JPEG_CHECK_FD();
    
    if ((NULL == stInMsg) || (NULL == stOutMsg)){
        return HI_FAILURE;
    }

    memset(&stDecInfo,0,sizeof(HI_JPEG_DECINFO_S));

    stDecInfo.stInMsg.pAllPhy        = stInMsg->pAllPhy;
    stDecInfo.stInMsg.pSavePhy       = stInMsg->pSavePhy;
    stDecInfo.stInMsg.pSaveVir[0]    = stInMsg->pSaveVir[0];
    stDecInfo.stInMsg.pSaveVir[1]    = stInMsg->pSaveVir[1];
    stDecInfo.stInMsg.u32AllLen      = stInMsg->u32AllLen;
    stDecInfo.stInMsg.u32SaveLen[0]  = stInMsg->u32SaveLen[0];
    stDecInfo.stInMsg.u32SaveLen[1]  = stInMsg->u32SaveLen[1];
    stDecInfo.stInMsg.s32InWidth     = stInMsg->s32InWidth;
    stDecInfo.stInMsg.s32InHeight    = stInMsg->s32InHeight;
    stDecInfo.stInMsg.bUserPhyMem    = stInMsg->bUserPhyMem;
    stDecInfo.stInMsg.enInFmt        = stInMsg->enInFmt;
    stDecInfo.stInMsg.u32DecHandle   = u32Handle;
    


    for(s32Cnt = 0; s32Cnt < MAX_PIXEL_COMPONENT_NUM; s32Cnt++){
        stDecInfo.stOutMsg.pOutPhy[s32Cnt]       = stOutMsg->pOutPhy[s32Cnt];
        stDecInfo.stOutMsg.u32OutWidth[s32Cnt]   = stOutMsg->u32OutWidth[s32Cnt];
        stDecInfo.stOutMsg.u32OutHeight[s32Cnt]  = stOutMsg->u32OutHeight[s32Cnt];
        stDecInfo.stOutMsg.u32OutStride[s32Cnt]  = stOutMsg->u32OutStride[s32Cnt];
        stDecInfo.stOutMsg.u32OutSize[s32Cnt]    = stOutMsg->u32OutSize[s32Cnt];
    }
    stDecInfo.stOutMsg.s32Scale      = stOutMsg->s32Scale;
    stDecInfo.stOutMsg.bOutYuvSp420  = stOutMsg->bOutYuvSp420;
    stDecInfo.stOutMsg.bLuPixSum     = stOutMsg->bLuPixSum;
    stDecInfo.stOutMsg.enOutFmt      = stOutMsg->enOutFmt;
    stDecInfo.stOutMsg.u32DecHandle  = u32Handle;

    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_DECODE, &stDecInfo);
    if(HI_SUCCESS != s32Ret){
        return HI_FAILURE;
    }
    
	return HI_SUCCESS;
#else
    return HI_FAILURE;
#endif

}

/** 
\brief get lu pixle sum value from omx decode. CNcomment:���������ȡ����ֵ CNend
\attention \n
If you want to get the luminance value, you can call this function, \n
but you should call it after HI_JPEG_Decode.\n
CNcomment:Ҫ����õ�����ֵ�����Ե��øú�������������HI_JPEG_Decode֮����ö��ҽ��� CNend\n

\param[in]	u32Handle. CNcomment:������ CNend
\param[out]	u64LuPixSum. CNcomment:�������ֵ CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_GetOmxLuPixSum
*/
HI_S32 HI_JPEG_GetOmxLuPixSum(HI_U32 u32Handle,HI_U64 *u64LuPixSum)
{

#ifdef CONFIG_JPEG_OMX_FUNCTION

    HI_DRV_JPEG_OUTMSG_S stOutInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    
    JPEG_CHECK_FD();
 	
    memset(&stOutInfo,0,sizeof(HI_DRV_JPEG_OUTMSG_S));

    stOutInfo.u32DecHandle = u32Handle;
    
    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_GETLUPIXSUM, &stOutInfo);
    if(HI_SUCCESS != s32Ret){
        return HI_FAILURE;
    }
    *u64LuPixSum  = stOutInfo.u64LuPixValue;

    return HI_SUCCESS;
#else
    return HI_FAILURE;
#endif
}


/** 
\brief destory all decode. CNcomment:�������н����� CNend
\attention \n
NA.\n
CNcomment:CNend\n

\param[in]  u32Handle.  CNcomment:��������� CNend

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE

\see \n
::HI_JPEG_DestoryDec
*/
HI_S32 HI_JPEG_DestoryDec(HI_U32 u32Handle)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION

    HI_S32 s32Ret = HI_SUCCESS;

    JPEG_CHECK_FD();
    
    s32Ret = ioctl(gs_s32JpegFd, CMD_JPG_DESTORYDEC,&u32Handle);
    if(HI_SUCCESS != s32Ret){
        return HI_FAILURE;
    }
    return HI_SUCCESS;

#else
    return HI_FAILURE;
#endif

}
