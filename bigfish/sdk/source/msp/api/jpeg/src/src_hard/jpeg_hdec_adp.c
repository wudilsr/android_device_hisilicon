/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_adp.c
Version		    : Initial Draft
Author		    : 
Created		    : 2014/06/20
Description	    : the adp realize in this file
                  CNcomment: �����ʵ�ֶ�������ļ��� CNend\n
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2014/06/20		    y00181162  		    Created file      	
******************************************************************************/

/*********************************add include here******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>

#include "hi_jpeg_config.h"
#include "jpeg_hdec_adp.h"
#include "jpeg_hdec_api.h"
#include "jpeg_hdec_mem.h"

/***************************** Macro Definition ******************************/


/** calculate the size according to the scale */
/** CNcomment:�������ű��������С */
#define JPEG_ALIGNED_SCALE(x, i)  (((x) + (1 << (i)) - 1) >> (i))

/** calculate the size according to the scale */
/** CNcomment:�������ű��������С */
#define JPEG_ROUND_UP(a,b)          ( ((a) + (b) - (1L)) / (b) )


/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/


/******************************* API forward declarations *******************/


/******************************* API realization *****************************/


/*****************************************************************************
* func          : JPEG_HDEC_GetOutSize
* description	: get the out size
                  CNcomment:  ��ȡ�����С CNend\n
* param[in]  	: s32Ration      CNcomment: ���ű��� CNend\n
* param[in]  	: u32InWidth     CNcomment: ������ CNend\n
* param[in]  	: u32InHeight    CNcomment: ����߶� CNend\n
* param[out] 	: pu32OutWidth   CNcomment: ������ CNend\n
* param[out]	: pu32OutHeight  CNcomment: ����߶� CNend\n
* retval     	: NA
* others:	 	: NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_GetOutSize(const HI_U32 u32Ration,    \
                                                   const HI_U32 u32InWidth,   \
                                                   const HI_U32 u32InHeight,  \
                                                   HI_U32 *pu32OutWidth,      \
                                                   HI_U32 *pu32OutHeight)
{

       switch(u32Ration){
		     case 0:
		         *pu32OutWidth  = u32InWidth;
		         *pu32OutHeight = u32InHeight;
				 break;
			 case 1:
		         *pu32OutWidth  = (JDIMENSION)JPEG_ROUND_UP((long) u32InWidth, 2L);
		         *pu32OutHeight = (JDIMENSION)JPEG_ROUND_UP((long) u32InHeight, 2L);
				  break;
			 case 2:
				*pu32OutWidth = (JDIMENSION)JPEG_ROUND_UP((long) u32InWidth, 4L);
		         *pu32OutHeight = (JDIMENSION)JPEG_ROUND_UP((long) u32InHeight, 4L);
				 break;
	         case 3:
			 	  *pu32OutWidth = (JDIMENSION)JPEG_ROUND_UP((long) u32InWidth, 8L);
		          *pu32OutHeight = (JDIMENSION)JPEG_ROUND_UP((long) u32InHeight, 8L);  
				  break;
			 default:
			 	  break;

       }

}


/*****************************************************************************
* func			: JPEG_HDEC_GetScale
* description	: get the jpeg decode scale
				  CNcomment:  ��ȡjpeg����Ҫ���ŵı��� CNend\n
* param[in] 	: cinfo 	  CNcomment: �������	CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_GetScale(j_decompress_ptr cinfo)
{


		HI_U32 u32Ration      = 0;
		HI_U32 u32Scale       = 0;
		HI_U32 u32TmpScale    = 0;
		HI_U32 u32TmpWidth    = 0;
		HI_U32 u32TmpHeight   = 0;
		HI_U32 u32TdeInWidth  = 0;
		HI_U32 u32TdeInHeight = 0;
		HI_U32 u32YWidth      = 0;
		HI_U32 u32YHeight     = 0;

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		u32TmpWidth  = cinfo->image_width;
		u32TmpHeight = cinfo->image_height;

		/**
		 ** the user set scale
		 ** CNcomment: �û�������Ҫ�����ű��� CNend\n
		 **/
		if(cinfo->scale_num * 8 <= cinfo->scale_denom){
		    u32Ration = JPEG_SCALEDOWN_8;
		}else if(cinfo->scale_num * 4 <= cinfo->scale_denom){
		    u32Ration = JPEG_SCALEDOWN_4;
		}else if(cinfo->scale_num * 2 <= cinfo->scale_denom){
			u32Ration = JPEG_SCALEDOWN_2;
		}else if(cinfo->scale_num == cinfo->scale_denom){
		     u32Ration = JPEG_SCALEDOWN_1;
		}else{
		     u32Ration = JPEG_SCALEDOWN_BUTT;
		}


		JPEG_HDEC_GetOutSize(u32Ration,u32TmpWidth,u32TmpHeight,&u32TdeInWidth,&u32TdeInHeight);
		/**
		** if the picture size is 1*height or width*1,the scale is the same as no scale
		** CNcomment: Ҫ��ͼƬ��Ȼ�߶�Ϊ1����������벻������һ���� CNend\n
		**/
		u32YWidth   = u32TdeInWidth;
		u32YHeight  = u32TdeInHeight;
		for(u32Scale = JPEG_SCALEDOWN_1; u32Scale <= JPEG_SCALEDOWN_8; u32Scale++ ){
		    if(JPEG_ALIGNED_SCALE(cinfo->image_width, u32Scale) == u32YWidth){
		        break;
		    }
		}

		/*������С��8��������ϵ���п����ظ�,��ʱҪ���߶�*/
		if(JPEG_ALIGNED_SCALE(cinfo->image_width, (u32Scale+1)) == u32YWidth){
			for(u32Scale = JPEG_SCALEDOWN_1; u32Scale <= JPEG_SCALEDOWN_8; u32Scale++){
				if(JPEG_ALIGNED_SCALE(cinfo->image_height, u32Scale) == u32YHeight){
				    break;
				}
			}
		}

		if(u32Scale < u32Ration){
		    u32TmpScale = u32Scale;
		}else{
		    u32TmpScale = u32Ration;
		}


		/**
		** check if the jpeg hard support decode to argb8888 or abgr8888
		** CNcomment: �ж�jpegӲ���Ƿ�֧�ֽ������argb8888����abgr8888 CNend\n
		**/
#ifdef CONFIG_JPEG_HARDDEC2ARGB
    #ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
		if(   (0 == u32TmpScale)\
			   &&(   JCS_ARGB_8888 == cinfo->out_color_space \
			      || JCS_RGBA_8888 == cinfo->out_color_space \
			      || JCS_ABGR_8888 == cinfo->out_color_space \
			      || JCS_ARGB_1555 == cinfo->out_color_space \
			      || JCS_ABGR_1555 == cinfo->out_color_space \
			      || JCS_RGB_565   == cinfo->out_color_space \
			      || JCS_BGR_565   == cinfo->out_color_space \
			      || JCS_RGB       == cinfo->out_color_space \
			      || JCS_BGR       == cinfo->out_color_space))
	#else
        if(   (0 == u32TmpScale)\
			   &&(   JCS_ARGB_8888 == cinfo->out_color_space \
			      || JCS_ABGR_8888 == cinfo->out_color_space \
			      || JCS_ARGB_1555 == cinfo->out_color_space \
			      || JCS_ABGR_1555 == cinfo->out_color_space \
			      || JCS_RGB_565   == cinfo->out_color_space \
			      || JCS_BGR_565   == cinfo->out_color_space \
			      || JCS_RGB       == cinfo->out_color_space \
			      || JCS_BGR       == cinfo->out_color_space))
    #endif
		{
		    pJpegHandle->bDecARGB	=  HI_TRUE;
		}
#endif


		/**
		** the tde limit��the size must contain in (4095 4095)
		** CNcomment: tde������ƣ�ת����С������(4095 4095)��Χ֮�� CNend\n
		** TDEʹ��2�ε���������ߺ����߼�֧��4K���ϣ�����������������
		**/
#if 0//def CHIP_TYPE_X5HD_hi3716m
#ifdef CONFIG_JPEG_HARDDEC2ARGB
		while( ((u32TdeInWidth > 4095) || ( u32TdeInHeight > 4095 )) && (HI_FALSE == pJpegHandle->bDecARGB) && (HI_FALSE == pJpegHandle->bOutYCbCrSP) )
#else
		while( ((u32TdeInWidth > 4095) || ( u32TdeInHeight > 4095 )) && (HI_FALSE == pJpegHandle->bOutYCbCrSP))
#endif
		{
			u32TmpScale++;
			if(u32TmpScale > 3)
			{
				u32TmpScale--;
				break;
			}
			JPEG_HDEC_GetOutSize(u32TmpScale,u32TmpWidth,u32TmpHeight,&u32TdeInWidth,&u32TdeInHeight);
		}
#else
		JPEG_HDEC_GetOutSize(u32TmpScale,u32TmpWidth,u32TmpHeight,&u32TdeInWidth,&u32TdeInHeight);
#endif


#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(0 != u32TmpScale){
			pJpegHandle->bDecARGB	=  HI_FALSE;
		}
#endif

		/**
		** the output size
		** CNcomment: �����С CNend\n
		**/
		cinfo->output_width  = u32TdeInWidth;
		cinfo->output_height = u32TdeInHeight;


		/**
		** set to hard register scale value
		** CNcomment: ���Ӳ�������ű�����С CNend\n
		**/
		pJpegHandle->u32ScalRation = u32TmpScale;
				
}



/*****************************************************************************
* func			: JPEG_HDEC_GetImagInfo
* description	: get jpeg picture information
				  CNcomment:  ��ȡͼƬ��Ϣ CNend\n
* param[in] 	: cinfo 	  CNcomment: �������	CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_GetImagInfo(j_decompress_ptr cinfo)
{


		HI_U32 YInWidth        = 0;
	    HI_U32 YInHeight       = 0;
		HI_U32 YWidthTmp       = 0;
	    HI_U32 YHeightTmp      = 0;
	    HI_U32 CHeightTmp      = 0;
        HI_U32 u32YStride      = 0;
		HI_U32 u32UVStride     = 0;
	    HI_U32 u32YWidth       = 0;
	    HI_U32 u32YHeight      = 0;
		HI_U32 u32UVWidth      = 0;
	    HI_U32 u32UVHeight     = 0;
		#ifdef CONFIG_JPEG_HARDDEC2ARGB
        HI_U32 u32McuWidth     = 0;
		#endif
		#if defined(CONFIG_JPEG_OUTPUT_CROP) && defined(CONFIG_JPEG_HARDDEC2ARGB)
		HI_U32 u32DecSize      = 0;
		#endif
		HI_U32 u32YSize        = 0;
		HI_U32 u32CSize        = 0;
		HI_U32 u32DecWidth     = 0;
		HI_U32 u32DecHeight    = 0;
		
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		#if defined(CONFIG_JPEG_OUTPUT_CROP) && defined(CONFIG_JPEG_HARDDEC2ARGB)
		if(HI_TRUE == pJpegHandle->stOutDesc.bCrop && HI_TRUE == pJpegHandle->bDecARGB){
		 /**
		  **  if set HI_JPEG_SetOutDesc,the crop is change
		  **  CNcomment: ����������ü���ʱ������Ҫ�Ĵ�С�����仯�ˣ��������¼���һ�� CNend\n
		  **/
		    u32DecSize = (HI_U32)(pJpegHandle->stJpegSofInfo.u32DisplayStride * pJpegHandle->stOutDesc.stCropRect.h);
			pJpegHandle->stJpegSofInfo.u32YSize  =  u32DecSize;
		    pJpegHandle->stJpegSofInfo.u32CSize  =  0;
		}
        #endif

		if(HI_TRUE == pJpegHandle->stJpegSofInfo.bCalcSize){
		    return;
		}
		/**
		 **  if out yuvsp,the output mem has two types,one from user, the other from inner. 
		 **  if out others, we should alloc the yuvsp mem.
		 ** CNcomment: Ҫ�����yuvsp �� Ӳ���������ARGB���Ƿ���Ҫ����Ӳ��������м�buffer�����������
		 ** 		   Ҫ�����������ʽ����Ҫ�����м�buffer  CNend\n
		 **/
		if(  (JCS_YUV400_SP	   == cinfo->out_color_space)
		   ||(JCS_YUV420_SP    == cinfo->out_color_space)
		   ||(JCS_YUV422_SP_12 == cinfo->out_color_space)
		   ||(JCS_YUV422_SP_21 == cinfo->out_color_space)
		   ||(JCS_YUV444_SP	   == cinfo->out_color_space)){
			pJpegHandle->bOutYCbCrSP   = HI_TRUE;
		}else{
			pJpegHandle->bOutYCbCrSP    = HI_FALSE;
		}

	    /**
		 ** this function call should after check the bOutYCbCrSP
		 ** CNcomment:���Ҫ������bOutYCbCrSP�ж�֮����� CNend\n
		 **/
		JPEG_HDEC_GetScale(cinfo);

		/**
		 ** the y stride should 128 bytes align
		 ** CNcomment:�����м�������128�ֽڶ��� CNend\n
		 **/
		HI_GFX_GetStride(cinfo->output_width,&u32YStride,JPGD_HDEC_MMZ_YUVSP_STRIDE_ALIGN);
		
		/** this to save data used
		 ** CNcomment:�����Ǳ���ʵ������ʹ�� CNend\n
		 **/
        u32YWidth   = cinfo->output_width;
		u32YHeight  = cinfo->output_height;
		if(u32YWidth  <= 1) u32YWidth  = 2;
	    if(u32YHeight <= 1) u32YHeight = 2;

		YInWidth   = (1 == pJpegHandle->u8Fac[0][0])?((cinfo->image_width   + JPEG_MCU_8ALIGN - 1)>>3) : ((cinfo->image_width  + JPEG_MCU_16ALIGN - 1)>>4);
		YInHeight  = (1 == pJpegHandle->u8Fac[0][1])?((cinfo->image_height  + JPEG_MCU_8ALIGN - 1)>>3) : ((cinfo->image_height + JPEG_MCU_16ALIGN - 1)>>4);
		YWidthTmp  = (1 == pJpegHandle->u8Fac[0][0])?((cinfo->output_width  + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1)))  : ((cinfo->output_width  + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1)));
		YHeightTmp = (1 == pJpegHandle->u8Fac[0][1])?((cinfo->output_height + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1)))  : ((cinfo->output_height + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1)));
		u32DecWidth  = (1 == pJpegHandle->u8Fac[0][0])?((cinfo->image_width  + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1))) : ((cinfo->image_width   + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1)));
		u32DecHeight = (1 == pJpegHandle->u8Fac[0][1])?((cinfo->image_height + JPEG_MCU_8ALIGN - 1) & (~(JPEG_MCU_8ALIGN - 1))) : ((cinfo->image_height  + JPEG_MCU_16ALIGN - 1) & (~(JPEG_MCU_16ALIGN - 1)));
		#ifdef CONFIG_JPEG_HARDDEC2ARGB
		u32McuWidth	= (1 == pJpegHandle->u8Fac[0][0])? (YInWidth / JPEG_MCU_8ALIGN) : (YInWidth / JPEG_MCU_16ALIGN);
		#endif
		switch(pJpegHandle->enImageFmt){

	        case JPEG_FMT_YUV400:
	        {
	            CHeightTmp  = 0;
				u32UVStride = 0;
				#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
				if(HI_TRUE == pJpegHandle->bOutYUV420SP)
				{
					CHeightTmp  = 0;
					u32UVStride = 0;
				}
				#endif
				u32UVWidth   = 0;
				u32UVHeight  = 0;
                break;
				
			}
	        case JPEG_FMT_YUV420:
	        {
	            CHeightTmp  = YHeightTmp >> 1;
                u32UVStride = u32YStride;
				#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
				if(HI_TRUE == pJpegHandle->bOutYUV420SP)
				{
					CHeightTmp  = CHeightTmp;
					u32UVStride = u32UVStride;
				}
				#endif
				u32YWidth   = (u32YWidth  >> 1) << 1;
		        u32YHeight  = (u32YHeight >> 1) << 1;
		        u32UVWidth  = u32YWidth  >> 1;
		        u32UVHeight = u32YHeight >> 1;
				break;
	        }
	        case JPEG_FMT_YUV422_21:
	        {
				/**
				 ** the horizontal sample
				 ** CNcomment:ˮƽ���� CNend\n
				 **/
	            CHeightTmp  = YHeightTmp;
				u32UVStride = u32YStride;
				#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
				if(HI_TRUE == pJpegHandle->bOutYUV420SP)
				{
					CHeightTmp  = CHeightTmp >> 1;
					u32UVStride = u32UVStride;
				}
				#endif
				u32YWidth    = (u32YWidth  >> 1) << 1;
		        u32UVWidth   = u32YWidth >> 1;
		        u32UVHeight  = u32YHeight;
				break;
				
	        }
	        case JPEG_FMT_YUV422_12:
	        {
				/**
				 ** the vertical sample
				 ** CNcomment:��ֱ���� CNend\n
				 **/
	            CHeightTmp  = YHeightTmp>>1;
				u32UVStride = u32YStride<<1;
				#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
				if(HI_TRUE == pJpegHandle->bOutYUV420SP)
				{
					CHeightTmp  = CHeightTmp;
					u32UVStride = u32UVStride >> 1;
				}
				#endif
				u32YHeight   = (u32YHeight >> 1) << 1;
		        u32UVWidth   = u32YWidth;
		        u32UVHeight  = u32YHeight >> 1;
				break;
	        }        
	        default:
	        {
	            CHeightTmp  = YHeightTmp;
				u32UVStride = u32YStride << 1;
				#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
				if(HI_TRUE == pJpegHandle->bOutYUV420SP)
				{
					CHeightTmp  = CHeightTmp  >> 1;
					u32UVStride = u32UVStride >> 1;
				}
				#endif
				u32UVWidth   = u32YWidth;
		        u32UVHeight  = u32YHeight;
				break;
				
	        }
	    }
		u32DecWidth  = u32DecWidth  >> pJpegHandle->u32ScalRation;
		u32DecHeight = u32DecHeight >> pJpegHandle->u32ScalRation;
		
#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
		if(HI_TRUE == pJpegHandle->bOutYUV420SP && JPEG_FMT_YUV400 != pJpegHandle->enImageFmt){
			u32YWidth	= (0 == u32YWidth  % 2)? u32YWidth  : (u32YWidth  - 1);
			u32YHeight	= (0 == u32YHeight % 2)? u32YHeight : (u32YHeight - 1);
			u32UVWidth	= u32YWidth >> 1;
			u32UVHeight = u32YHeight >> 1;
		}
#endif

		/** the decode size, argb output
		 ** CNcomment:����ֱ��ʴ�С��ARGB����� CNend\n
		 **/
		if(HI_FALSE == pJpegHandle->stOutDesc.bCrop){	
			/**
			 ** is dec width and height,if not set crop message,use this
			 ** CNcomment:����ֱ���,���û�����òü��ֱ�����ô��ʹ��Ĭ�ϵ������С CNend\n
			 **/
			 pJpegHandle->stOutDesc.stCropRect.x = 0;
			 pJpegHandle->stOutDesc.stCropRect.y = 0;
			 pJpegHandle->stOutDesc.stCropRect.w = (HI_S32)cinfo->output_width;
			 pJpegHandle->stOutDesc.stCropRect.h = (HI_S32)cinfo->output_height;
		}
		/** revise by y00181162,for iphone test,the components is not right **/
        switch(cinfo->out_color_space){
			case JCS_RGB:
			case JCS_BGR:
			case JCS_CrCbY:
			case JCS_YCbCr:
				 HI_GFX_GetStride((HI_U32)pJpegHandle->stOutDesc.stCropRect.w * 3,&(pJpegHandle->stJpegSofInfo.u32DisplayStride),pJpegHandle->u32StrideAlign);
                 pJpegHandle->stJpegSofInfo.u32DecStride  =  YWidthTmp * 3;
				 cinfo->out_color_components = 3;
				 break;
			case JCS_CMYK:
			case JCS_ARGB_8888:
			case JCS_ABGR_8888:
			#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
			case JCS_RGBA_8888:
			#endif
				 HI_GFX_GetStride((HI_U32)pJpegHandle->stOutDesc.stCropRect.w * 4,&(pJpegHandle->stJpegSofInfo.u32DisplayStride),pJpegHandle->u32StrideAlign);
                 pJpegHandle->stJpegSofInfo.u32DecStride  =  YWidthTmp * 4;
				 cinfo->out_color_components = 4;
				 break;
			case JCS_ARGB_1555:
			case JCS_ABGR_1555:
				 HI_GFX_GetStride((HI_U32)pJpegHandle->stOutDesc.stCropRect.w * 2,&(pJpegHandle->stJpegSofInfo.u32DisplayStride),pJpegHandle->u32StrideAlign);
                 pJpegHandle->stJpegSofInfo.u32DecStride  =  YWidthTmp * 2;
				 cinfo->out_color_components = 2;
				 break;
			case JCS_RGB_565:
			case JCS_BGR_565:
				 HI_GFX_GetStride((HI_U32)pJpegHandle->stOutDesc.stCropRect.w * 2,&(pJpegHandle->stJpegSofInfo.u32DisplayStride),pJpegHandle->u32StrideAlign);
                 pJpegHandle->stJpegSofInfo.u32DecStride  =  YWidthTmp * 2;
				 cinfo->out_color_components = 3;
				 break;
			default:
				 /**JCS_GRAYSCALE**/
				 HI_GFX_GetStride((HI_U32)pJpegHandle->stOutDesc.stCropRect.w * 2,&(pJpegHandle->stJpegSofInfo.u32DisplayStride),pJpegHandle->u32StrideAlign);
				 pJpegHandle->stJpegSofInfo.u32DecStride  =  u32YStride;
				 cinfo->out_color_components = 1;
				 break;
		}
		/** if user use this output_components after start decompress not zero **/
		cinfo->output_components = cinfo->out_color_components;
		
#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bDecARGB){
		    u32YSize  = pJpegHandle->stJpegSofInfo.u32DisplayStride * pJpegHandle->stOutDesc.stCropRect.h;
			u32CSize  = 0;
		}else
#endif
		{
		    u32YSize = YHeightTmp * u32YStride;
			u32CSize = CHeightTmp * u32UVStride;
		}

		/**
		 ** the jpeg size info has calculated
		 ** CNcomment:jpeg��С�Ѿ��������ˣ�����Ҫ���¼����� CNend\n
		 **/
        pJpegHandle->stJpegSofInfo.bCalcSize       =  HI_TRUE;
		pJpegHandle->stJpegSofInfo.u32YWidth       =  u32YWidth;
		pJpegHandle->stJpegSofInfo.u32YHeight      =  u32YHeight;
		pJpegHandle->stJpegSofInfo.u32YSize        =  u32YSize;
		pJpegHandle->stJpegSofInfo.u32CWidth       =  u32UVWidth;
		pJpegHandle->stJpegSofInfo.u32CHeight      =  u32UVHeight;
        pJpegHandle->stJpegSofInfo.u32CSize        =  u32CSize;
        pJpegHandle->stJpegSofInfo.u32YStride      =  u32YStride;
        pJpegHandle->stJpegSofInfo.u32CbCrStride   =  u32UVStride;
        pJpegHandle->stJpegSofInfo.u32DisplayW     =  cinfo->output_width;
        pJpegHandle->stJpegSofInfo.u32DisplayH     =  cinfo->output_height;
        pJpegHandle->stJpegSofInfo.u32DecW         =  u32DecWidth;
        pJpegHandle->stJpegSofInfo.u32DecH         =  u32DecHeight;
		pJpegHandle->stJpegSofInfo.u32InWandH      =  (YInWidth| (YInHeight << 16));
		#ifdef CONFIG_JPEG_HARDDEC2ARGB
		pJpegHandle->stJpegSofInfo.u32McuWidth     =  u32McuWidth;
		/**
		 ** need 128 bytes align
		 ** CNcomment:128�ֽڶ��� CNend\n
		 **/
		pJpegHandle->stJpegSofInfo.u32MINSize      =  u32McuWidth * 128;
		pJpegHandle->stJpegSofInfo.u32MIN1Size     =  pJpegHandle->stJpegSofInfo.u32MINSize;
		pJpegHandle->stJpegSofInfo.u32RGBSizeReg   =  2 * pJpegHandle->stJpegSofInfo.u32MINSize;
		#endif
		
}
