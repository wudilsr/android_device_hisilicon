/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jdcolor_userbuf.c
Version		    : Initial Draft
Author		    : 
Created		    : 2014/06/20
Description	    : add the color convert to user buffer,the reason add this file is
                  because call these function should check how to output everytime.
                  cost much time
                  CNcomment: �����bufferΪ�û�buffer��ʱ��ʹ�ø��ļ�����ʵ�֡�
                             ��д��ԭ�����ڲ�����ת���Ĺ�����ÿ�ζ����ж�Ҫ�����
                             �ĸ�buffer��,�����ܺ�ʱ��,����ͳһ�ڳ�ʼ����ʱ������жϡ�
                             �ü��ͷǲü�����������rect�Ĵ�С������ȫ���ü������� CNend\n
Function List 	: 
History       	:
Date				Author        		Modification
2014/06/20		    y00181162  		    Created file      	
******************************************************************************/


/*********************************add include here******************************/

#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"

/**
 ** add the include file about the init function
 ** CNcomment: ����Ӳ��������Ҫ��ͷ�ļ� CNend\n
 **/
#include "jpeg_hdec_api.h"
#include "hi_jpeg_config.h"

/***************************** Macro Definition ******************************/

/* Declarations for ordered dithering.
 * 
 * We use 4x4 ordered dither array packed into 32 bits. This array is
 * sufficent for dithering RGB_888 to RGB_565.
 ** CNcomment:��ɫ�ռ�ת����RGB���ӵĲ��� CNend\n
 **/
#define DITHER_MASK         0x3
#define DITHER_ROTATE(x)    (((x)<<24) | (((x)>>8)&0x00FFFFFF))


#define SCALEBITS	16	/* speediest right-shift on some machines */
#define ONE_HALF	((INT32) 1 << (SCALEBITS-1))
#define FIX(x)		((INT32) ((x) * (1L<<SCALEBITS) + 0.5))

#define CONFIG_CONVERT_CMYK_RGB

/*************************** Structure Definition ****************************/

/* Private subobject */

typedef struct {
  struct jpeg_color_deconverter pub; /* public fields */

  /* Private state for YCC->RGB conversion */
  int * Cr_r_tab;		/* => table for Cr to R conversion */
  int * Cb_b_tab;		/* => table for Cb to B conversion */
  INT32 * Cr_g_tab;		/* => table for Cr to G conversion */
  INT32 * Cb_g_tab;		/* => table for Cb to G conversion */
} my_color_deconverter;

typedef my_color_deconverter * my_cconvert_ptr;


/********************** Global Variable declaration **************************/

static const INT32 dither_matrix[4] = 
{
  0x0008020A,
  0x0C040E06,
  0x030B0109,
  0x0F070D05
};


/******************************* API declaration *****************************/


/**************** YCbCr -> RGB conversion: most common case **************/

/*
 * YCbCr is defined per CCIR 601-1, except that Cb and Cr are
 * normalized to the range 0..MAXJSAMPLE rather than -0.5 .. 0.5.
 * The conversion equations to be implemented are therefore
 *	R = Y                + 1.40200 * Cr
 *	G = Y - 0.34414 * Cb - 0.71414 * Cr
 *	B = Y + 1.77200 * Cb
 * where Cb and Cr represent the incoming values less CENTERJSAMPLE.
 * (These numbers are derived from TIFF 6.0 section 21, dated 3-June-92.)
 *
 * To avoid floating-point arithmetic, we represent the fractional constants
 * as integers scaled up by 2^16 (about 4 digits precision); we have to divide
 * the products by 2^16, with appropriate rounding, to get the correct answer.
 * Notice that Y, being an integral input, does not contribute any fraction
 * so it need not participate in the rounding.
 *
 * For even more speed, we avoid doing any multiplications in the inner loop
 * by precalculating the constants times Cb and Cr for all possible values.
 * For 8-bit JSAMPLEs this is very reasonable (only 256 entries per table);
 * for 12-bit samples it is still acceptable.  It's not very reasonable for
 * 16-bit samples, but if you want lossless storage you shouldn't be changing
 * colorspace anyway.
 * The Cr=>R and Cb=>B values can be rounded to integers in advance; the
 * values for the G calculation are left scaled up, since we must add them
 * together before rounding.
 */


/*
 * Initialize tables for YCC->RGB colorspace conversion.
 */

#ifndef CONFIG_JPEG_CODE_CUT_RGB
LOCAL(void)
build_ycc_rgb_table (j_decompress_ptr cinfo)
{

	my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
	int i;
	INT32 x;
	SHIFT_TEMPS
	
	cconvert->Cr_r_tab = (int *)
	  (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  (MAXJSAMPLE+1) * SIZEOF(int));
	
	cconvert->Cb_b_tab = (int *)
	  (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  (MAXJSAMPLE+1) * SIZEOF(int));
	
	cconvert->Cr_g_tab = (INT32 *)
	  (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  (MAXJSAMPLE+1) * SIZEOF(INT32));
	
	cconvert->Cb_g_tab = (INT32 *)
	  (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  (MAXJSAMPLE+1) * SIZEOF(INT32));
	
	
	for (i = 0, x = -CENTERJSAMPLE; i <= MAXJSAMPLE; i++, x++) 
	{
	
		  /* i is the actual input pixel value, in the range 0..MAXJSAMPLE */
		  /* The Cb or Cr value we are thinking of is x = i - CENTERJSAMPLE */
		  /* Cr=>R value is nearest int to 1.40200 * x */
		  cconvert->Cr_r_tab[i] = (int)
				  RIGHT_SHIFT(FIX(1.40200) * x + ONE_HALF, SCALEBITS);
		  /* Cb=>B value is nearest int to 1.77200 * x */
		  cconvert->Cb_b_tab[i] = (int)
				  RIGHT_SHIFT(FIX(1.77200) * x + ONE_HALF, SCALEBITS);
		  /* Cr=>G value is scaled-up -0.71414 * x */
		  cconvert->Cr_g_tab[i] = (- FIX(0.71414)) * x;
		  /* Cb=>G value is scaled-up -0.34414 * x */
		  /* We also add in ONE_HALF so that need not do it in inner loop */
		  cconvert->Cb_g_tab[i] = (- FIX(0.34414)) * x + ONE_HALF;
	  
	}

}


/*
 * Convert some rows of samples to the output colorspace.
 *
 * Note that we change from noninterleaved, one-plane-per-component format
 * to interleaved-pixel format.  The output buffer is therefore three times
 * as wide as the input buffer.
 * A starting row offset is provided only for the input buffer.  The caller
 * can easily adjust the passed output_buf value to accommodate any row
 * offset required on that side.
 */

METHODDEF(void)
ycc_rgb_convert (j_decompress_ptr cinfo,
		 JSAMPIMAGE input_buf, JDIMENSION input_row,
		 JSAMPARRAY output_buf, int num_rows)
{


	    JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	
		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		register int y, cb, cr;
		register JSAMPROW inptr0, inptr1, inptr2;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;
		register JSAMPLE * range_limit = cinfo->sample_range_limit;
		register int * Crrtab = cconvert->Cr_r_tab;
		register int * Cbbtab = cconvert->Cb_b_tab;
		register INT32 * Crgtab = cconvert->Cr_g_tab;
		register INT32 * Cbgtab = cconvert->Cb_g_tab;
		SHIFT_TEMPS

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;

		unsigned int  r = 0;
		unsigned int  g = 1;
		unsigned int  b = 2;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		if(JCS_BGR == cinfo->out_color_space)
		{
			r = 2;
			b = 0;
		}
		
		while (--num_rows >= 0)
		{
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{
				 if(  (col >= pJpegHandle->stOutDesc.stCropRect.x)
					&&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				  {
						y  = GETJSAMPLE(inptr0[col]);
						cb = GETJSAMPLE(inptr1[col]);
						cr = GETJSAMPLE(inptr2[col]);
						
						retYBuf[s32RowYNum+3*u32Count+r] =	range_limit[y + Crrtab[cr]];
						retYBuf[s32RowYNum+3*u32Count+g] =	range_limit[y +
												   ((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr],
													SCALEBITS))];
						retYBuf[s32RowYNum+3*u32Count+b] =	range_limit[y + Cbbtab[cb]];

						u32Count++;
				  }
				    
			}
			
		}

}

METHODDEF(void)
ycc_argb_8888_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{

		  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
			  
		  my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		  register int y, cb, cr;
		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;
		  /* copy these pointers into registers if possible */
		  register JSAMPLE * range_limit = cinfo->sample_range_limit;
		  register int * Crrtab = cconvert->Cr_r_tab;
		  register int * Cbbtab = cconvert->Cb_b_tab;
		  register INT32 * Crgtab = cconvert->Cr_g_tab;
		  register INT32 * Cbgtab = cconvert->Cb_g_tab;
		  SHIFT_TEMPS

		  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_S32 s32RowYNum  = 0;
		  HI_U32 u32Count = 0;

		  unsigned int  r = 0;
		  unsigned int  g = 1;
		  unsigned int  b = 2;

		  retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  
		  if(JCS_ABGR_8888 == cinfo->out_color_space)
		  {
			 r = 2;
			 b = 0;
		  }
		
		  while (--num_rows >= 0) 
		  {

			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{
				 if(  (col >= pJpegHandle->stOutDesc.stCropRect.x)
					 &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				   {
					      y  = GETJSAMPLE(inptr0[col]);
					      cb = GETJSAMPLE(inptr1[col]);
					      cr = GETJSAMPLE(inptr2[col]);
						  retYBuf[s32RowYNum+4*u32Count+r] =  range_limit[y + Crrtab[cr]];
						  retYBuf[s32RowYNum+4*u32Count+g] =  range_limit[y +
				                      ((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr],
				                                         SCALEBITS))];
						  retYBuf[s32RowYNum+4*u32Count+b] =  range_limit[y + Cbbtab[cb]];
						  retYBuf[s32RowYNum+4*u32Count+3] = 0xFF;

						  u32Count++;
				    }
			   
			}
			
				 
	   }
		
}
METHODDEF(void)
ycc_rgb_565_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;
		
		/** �޿����� **/
		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		register int y, cb, cr;
		register JSAMPROW inptr0, inptr1, inptr2;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;
		/* copy these pointers into registers if possible */
		register JSAMPLE * range_limit = cinfo->sample_range_limit;
		register int * Crrtab = cconvert->Cr_r_tab;
		register int * Cbbtab = cconvert->Cb_b_tab;
		register INT32 * Crgtab = cconvert->Cr_g_tab;
		register INT32 * Cbgtab = cconvert->Cb_g_tab;
		SHIFT_TEMPS

		unsigned int r, g, b;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		while (--num_rows >= 0) 
		{
			
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
			s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

			   if(	(col >= pJpegHandle->stOutDesc.stCropRect.x)
				   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				 {

						y  = GETJSAMPLE(inptr0[col]);
						cb = GETJSAMPLE(inptr1[col]);
						cr = GETJSAMPLE(inptr2[col]);

						/** argb1555 **/
						r = range_limit[y + Cbbtab[cb]];
						g = range_limit[y + ((int)RIGHT_SHIFT(Cbgtab[cb]+Crgtab[cr], SCALEBITS))];
						b = range_limit[y + Crrtab[cr]];
						
						(*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,g,b);

						u32Count++;
						
				  }
				   
			}
		  
		}

}

METHODDEF(void)
ycc_bgr_565_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);


		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;

		 
		 /** �޿����� **/
		 my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		 register int y, cb, cr;
		 register JSAMPROW inptr0, inptr1, inptr2;
		 register HI_S32 col;
		 JDIMENSION num_cols = cinfo->output_width;
		 /* copy these pointers into registers if possible */
		 register JSAMPLE * range_limit = cinfo->sample_range_limit;
		 register int * Crrtab = cconvert->Cr_r_tab;
		 register int * Cbbtab = cconvert->Cb_b_tab;
		 register INT32 * Crgtab = cconvert->Cr_g_tab;
		 register INT32 * Cbgtab = cconvert->Cb_g_tab;
		 SHIFT_TEMPS
		
		 unsigned int r, g, b;

		 retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		 
		 while (--num_rows >= 0) 
		 {
			 
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				if(  (col >= pJpegHandle->stOutDesc.stCropRect.x)
					&&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				  {

						 y	= GETJSAMPLE(inptr0[col]);
						 cb = GETJSAMPLE(inptr1[col]);
						 cr = GETJSAMPLE(inptr2[col]);

						 /** argb1555 **/
						 r = range_limit[y + Crrtab[cr]];
						 g = range_limit[y + ((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr], SCALEBITS))];
						 b = range_limit[y + Cbbtab[cb]];
						 
						 (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,g,b);

						 u32Count++;
						 
				   }
					
			}
						
		 }
}


METHODDEF(void)
ycc_rgb_565D_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;


		/** ������ **/
		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		register int y, cb, cr;
		register JSAMPROW inptr0, inptr1, inptr2;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;
		/* copy these pointers into registers if possible */
		register JSAMPLE * range_limit = cinfo->sample_range_limit;
		register int * Crrtab = cconvert->Cr_r_tab;
		register int * Cbbtab = cconvert->Cb_b_tab;
		register INT32 * Crgtab = cconvert->Cr_g_tab;
		register INT32 * Cbgtab = cconvert->Cb_g_tab;
		INT32 d0 = dither_matrix[cinfo->output_scanline & DITHER_MASK];
		SHIFT_TEMPS

		unsigned int r, g, b;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		while (--num_rows >= 0) 
		{
			
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
			s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				if(	(col >= pJpegHandle->stOutDesc.stCropRect.x)
				   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				 {

						y  = GETJSAMPLE(inptr0[col]);
						cb = GETJSAMPLE(inptr1[col]);
						cr = GETJSAMPLE(inptr2[col]);

						d0 = DITHER_ROTATE(d0);
						r = range_limit[DITHER_565_B(y + Cbbtab[cb], d0)];
						g = range_limit[DITHER_565_G(y + ((int)RIGHT_SHIFT(Cbgtab[cb]+Crgtab[cr], SCALEBITS)), d0)];
						b = range_limit[DITHER_565_R(y + Crrtab[cr], d0)];
						
						(*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,g,b);

						u32Count++;
						
				  }
				
			}
			 
		}
	  
}

METHODDEF(void)
ycc_bgr_565D_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{


		 JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		 HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		 HI_S32 s32RowYNum	= 0;
		 HI_U32 u32Count = 0;

		 my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		 register int y, cb, cr;
		 register JSAMPROW inptr0, inptr1, inptr2;
		 register HI_S32 col;
		 JDIMENSION num_cols = cinfo->output_width;
		 /* copy these pointers into registers if possible */
		 register JSAMPLE * range_limit = cinfo->sample_range_limit;
		 register int * Crrtab = cconvert->Cr_r_tab;
		 register int * Cbbtab = cconvert->Cb_b_tab;
		 register INT32 * Crgtab = cconvert->Cr_g_tab;
		 register INT32 * Cbgtab = cconvert->Cb_g_tab;
		 INT32 d0 = dither_matrix[cinfo->output_scanline & DITHER_MASK];
		 SHIFT_TEMPS

		unsigned int r, g, b;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		 while (--num_rows >= 0) 
		 {

			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				if(  (col >= pJpegHandle->stOutDesc.stCropRect.x)
					&&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				  {

						 y	= GETJSAMPLE(inptr0[col]);
						 cb = GETJSAMPLE(inptr1[col]);
						 cr = GETJSAMPLE(inptr2[col]);

						 d0 = DITHER_ROTATE(d0);
						 
						 b = range_limit[DITHER_565_B(y + Cbbtab[cb], d0)];
						 g = range_limit[DITHER_565_G(y + ((int)RIGHT_SHIFT(Cbgtab[cb]+Crgtab[cr], SCALEBITS)), d0)];
						 r = range_limit[DITHER_565_R(y + Crrtab[cr], d0)];

						 (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,g,b);

						 u32Count++;
						 
				   }
				  
			}
							
		}
	  
}


METHODDEF(void)
ycc_abgr_1555_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{

 
		 /**
		   **Ҫ������alph0ֵ�� A = 0;	A8λ = 0
		   **Ҫ������alph1ֵ�� A = 1;	A8λ = 255
		   **/
		   my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		   register int y, cb, cr;
		   register JSAMPROW inptr0, inptr1, inptr2;
		   register HI_S32 col;
		   JDIMENSION num_cols = cinfo->output_width;
		 
		   register JSAMPLE * range_limit = cinfo->sample_range_limit;
		   
		   register int * Crrtab	 = cconvert->Cr_r_tab;
		   register int * Cbbtab	 = cconvert->Cb_b_tab;
		   register INT32 * Crgtab	 = cconvert->Cr_g_tab;
		   register INT32 * Cbgtab	 = cconvert->Cb_g_tab;
		   SHIFT_TEMPS
		 
		   JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		   HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		   HI_S32 s32RowYNum  = 0;
		   HI_U32 u32Count = 0;

		 
		   unsigned int r, g, b;
		   HI_U8 a;

		   retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		   
		   while (--num_rows >= 0) 
		   {
			   
				inptr0 = input_buf[0][input_row];
				inptr1 = input_buf[1][input_row];
				inptr2 = input_buf[2][input_row];
				input_row++;

				if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   		||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
				{
					continue;
				}
                s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
				for (col = 0; col < (HI_S32)num_cols; col++)
				{

					if(  (col >= pJpegHandle->stOutDesc.stCropRect.x)
					    &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				     {
						   y  = GETJSAMPLE(inptr0[col]);
						   cb = GETJSAMPLE(inptr1[col]);
						   cr = GETJSAMPLE(inptr2[col]);

						   /** abgr1555 **/
						   b =	range_limit[y + Crrtab[cr]];
						   g =  range_limit[y + ((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr], SCALEBITS))];
						   r =	range_limit[y + Cbbtab[cb]];
						   a =	0x0;
					  
					      (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT_1555(a,r,g,b);

					       u32Count++;
					 }
						   
				}
												  
		   }
  
}

METHODDEF(void)
ycc_argb_1555_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{

	     /**
	      **Ҫ������alph0ֵ�� A = 0;   A8λ = 0
	      **Ҫ������alph1ֵ�� A = 1;   A8λ = 255
	      **/
		  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
		
		  my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		  register int y, cb, cr;
		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  register JSAMPLE * range_limit = cinfo->sample_range_limit;
		  
		  register int * Crrtab 	= cconvert->Cr_r_tab;
		  register int * Cbbtab 	= cconvert->Cb_b_tab;
		  register INT32 * Crgtab	= cconvert->Cr_g_tab;
		  register INT32 * Cbgtab	= cconvert->Cb_g_tab;
		  SHIFT_TEMPS

		  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_S32 s32RowYNum = 0;
		  HI_U32 u32Count = 0;


		  unsigned int r, g, b;
		  HI_U8 a;

		  retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  
		  while (--num_rows >= 0) 
		  {
			  
				inptr0 = input_buf[0][input_row];
				inptr1 = input_buf[1][input_row];
				inptr2 = input_buf[2][input_row];
				input_row++;

				if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
				{
					continue;
				}
                s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
				for (col = 0; col < (HI_S32)num_cols; col++)
				{

					 if(  (col >= pJpegHandle->stOutDesc.stCropRect.x)
						 &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
					  {

						  y  = GETJSAMPLE(inptr0[col]);
						  cb = GETJSAMPLE(inptr1[col]);
						  cr = GETJSAMPLE(inptr2[col]);

						  /** argb1555 **/
						  r = range_limit[y + Crrtab[cr]];
						  g = range_limit[y + ((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr], SCALEBITS))];
						  b = range_limit[y + Cbbtab[cb]];
						  a = 0x0;

						  (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT_1555(a,r,g,b);

						  u32Count++;
						  
					}
					 
				}
			
		  }
  
}
METHODDEF(void)
rgb_rgb_888_convert (j_decompress_ptr cinfo,
	      JSAMPIMAGE input_buf, JDIMENSION input_row,
	      JSAMPARRAY output_buf, int num_rows)
{/**CMYKʹ�ã���4�����ص� **/

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;

		register JSAMPROW inptr0, inptr1, inptr2;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		while (--num_rows >= 0) 
		{
		
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

			    if(	  (col >= pJpegHandle->stOutDesc.stCropRect.x)
					 &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				 {
						retYBuf[s32RowYNum+3*u32Count]	 =	GETJSAMPLE(inptr0[col]);
						retYBuf[s32RowYNum+3*u32Count+1] =	GETJSAMPLE(inptr1[col]);
						retYBuf[s32RowYNum+3*u32Count+2] =	GETJSAMPLE(inptr2[col]);
						u32Count++;
				  }
			}

	  }

	  
}
METHODDEF(void)
rgb_abgr_8888_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{


		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
		
		register JSAMPROW inptr0, inptr1, inptr2;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;
		SHIFT_TEMPS

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		while (--num_rows >= 0)
		{
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

			     if(   (col >= pJpegHandle->stOutDesc.stCropRect.x)
				     &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
			     {

						retYBuf[s32RowYNum+4*u32Count]	 =	inptr2[col];
						retYBuf[s32RowYNum+4*u32Count+1] =	inptr0[col];
						retYBuf[s32RowYNum+4*u32Count+2] =	inptr1[col];
						retYBuf[s32RowYNum+4*u32Count+3] = 0xFF;
						u32Count++;
				  }
			}
			  
		}

}

METHODDEF(void)
rgb_rgb_565_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{


        JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		 HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		 HI_S32 s32RowYNum	= 0;
		 HI_U32 u32Count = 0;


		 register JSAMPROW inptr0, inptr1, inptr2;
		 register HI_S32 col;
		 JDIMENSION num_cols = cinfo->output_width;
		 SHIFT_TEMPS

		 unsigned int r, g, b;

		 retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		 
		 while (--num_rows >= 0) 
		 {
			 
				inptr0 = input_buf[0][input_row];
				inptr1 = input_buf[1][input_row];
				inptr2 = input_buf[2][input_row];
				input_row++;

				if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
				{
					continue;
				}
                s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
				for (col = 0; col < (HI_S32)num_cols; col++)
				{

					if(   (col >= pJpegHandle->stOutDesc.stCropRect.x)
					     &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				     {
							 r = inptr0[col];
							 g = inptr1[col];
							 b = inptr2[col];
							 
							 (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,g,b);

							 u32Count++;
							 
					   }
					  
				}
							
		 }
  
}


METHODDEF(void)
rgb_bgr_565_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{


		 JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		 HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		 HI_S32 s32RowYNum	= 0;
		 HI_U32 u32Count = 0;


		register JSAMPROW inptr0, inptr1, inptr2;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;
		SHIFT_TEMPS

		unsigned int r, g, b;

		retYBuf	= pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		while (--num_rows >= 0) 
		{
			
				inptr0 = input_buf[0][input_row];
				inptr1 = input_buf[1][input_row];
				inptr2 = input_buf[2][input_row];
				input_row++;

				if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
				{
					continue;
				}
				s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
				for (col = 0; col < (HI_S32)num_cols; col++)
				{

				   if(	 (col >= pJpegHandle->stOutDesc.stCropRect.x)
						&&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
					{

							r = inptr0[col];
							g = inptr1[col];
							b = inptr2[col];
							
							(*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,g,b);

							u32Count++;
							
					  }

				}
		  
		}
  
}


METHODDEF(void)
rgb_rgb_565D_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{

	  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
	  HI_S32 s32RowYNum  = 0;
	  HI_U32 u32Count = 0;

	  
	  register JSAMPROW inptr0, inptr1, inptr2;
	  register HI_S32 col;
	  register JSAMPLE * range_limit = cinfo->sample_range_limit;
	  JDIMENSION num_cols = cinfo->output_width;
	  INT32 d0 = dither_matrix[cinfo->output_scanline & DITHER_MASK];
	  SHIFT_TEMPS

	  unsigned int r, g, b;

	  retYBuf	  = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
	  
	  while (--num_rows >= 0) 
	  {
		  
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				  if(  (col >= pJpegHandle->stOutDesc.stCropRect.x)
					  &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				  {

						 d0 = DITHER_ROTATE(d0);
					     r = range_limit[DITHER_565_R(GETJSAMPLE(inptr0[col]), d0)];
					     g = range_limit[DITHER_565_G(GETJSAMPLE(inptr1[col]), d0)];
					     b = range_limit[DITHER_565_B(GETJSAMPLE(inptr2[col]), d0)];

						 (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,g,b);

						 u32Count++;
						  
				    }							
			}
		
	  }
	  
}


METHODDEF(void)
rgb_argb_1555_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{

 
	 /**
		**Ҫ������alph0ֵ�� A = 0;	 A8λ = 0
		**Ҫ������alph1ֵ�� A = 1;	 A8λ = 255
		**/
		register JSAMPROW inptr0, inptr1, inptr2;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;
		SHIFT_TEMPS
	 
		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;

		
		unsigned int r,g,b;
		HI_U8 a;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		while (--num_rows >= 0)
		{
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				 if(	(col >= pJpegHandle->stOutDesc.stCropRect.x)
					   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				  {

						r = *inptr0++;
						g = *inptr1++;
						b = *inptr2++;
					    a =  0x0;
						(*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT_1555(a,r,g,b);

						u32Count++;
						
				  }
				   
			}
						   
		}
  
}


METHODDEF(void)
rgb_abgr_1555_convert (j_decompress_ptr cinfo,
         JSAMPIMAGE input_buf, JDIMENSION input_row,
         JSAMPARRAY output_buf, int num_rows)
{


	
         /**
	      **Ҫ������alph0ֵ�� A = 0;   A8λ = 0
	      **Ҫ������alph1ֵ�� A = 1;   A8λ = 255
	      **/
		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;
		  SHIFT_TEMPS

		  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_S32 s32RowYNum  = 0;
		  HI_U32 u32Count = 0;
	  
		  unsigned int r,g,b;
		  HI_U8 a;

		  retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  
		  while (--num_rows >= 0)
		  {
				inptr0 = input_buf[0][input_row];
				inptr1 = input_buf[1][input_row];
				inptr2 = input_buf[2][input_row];
				input_row++;

				if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
				{
					continue;
				}
                s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
				for (col = 0; col < (HI_S32)num_cols; col++)
				{

					 if(  (col >= pJpegHandle->stOutDesc.stCropRect.x)
						 &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
					  {
						      b = *inptr0++;
						      g = *inptr1++;
						      r = *inptr2++;
					          a =  0x0;

							  (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT_1555(a,r,g,b);

							  u32Count++;
							  
					    }
					 
				}

		  }
		  
}


/**************** Cases other than YCbCr -> RGB **************/


/*
 * Color conversion for no colorspace change: just copy the data,
 * converting from separate-planes to interleaved representation.
 */
METHODDEF(void)
null_convert (j_decompress_ptr cinfo,
	      JSAMPIMAGE input_buf, JDIMENSION input_row,
	      JSAMPARRAY output_buf, int num_rows)
{/**CMYKʹ�ã���4�����ص� **/

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;

		register JSAMPROW inptr0, inptr1, inptr2,inptr3;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;

	  	retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
	  	
		while (--num_rows >= 0) 
		{
		
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			inptr3 = input_buf[3][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

			    if(	  (col >= pJpegHandle->stOutDesc.stCropRect.x)
					 &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				 {
						retYBuf[s32RowYNum+4*u32Count]	 =	GETJSAMPLE(inptr0[col]);
						retYBuf[s32RowYNum+4*u32Count+1] =	GETJSAMPLE(inptr1[col]);
						retYBuf[s32RowYNum+4*u32Count+2] =	GETJSAMPLE(inptr2[col]);
						retYBuf[s32RowYNum+4*u32Count+3] =  GETJSAMPLE(inptr3[col]);
						u32Count++;
				  }
			}

	  }

	  
}

/*
 * Color conversion for grayscale: just copy the data.
 * This also works for YCbCr -> grayscale conversion, in which
 * we just copy the Y (luminance) component and ignore chrominance.
 */

METHODDEF(void)
grayscale_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{

	  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);


	  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
	  HI_S32 s32RowYNum  = 0;
      HI_U32 u32Count = 0;
	  
	  register JSAMPROW inptr;
	  register HI_S32 col;
	  JDIMENSION num_cols = cinfo->output_width;

	  retYBuf	  = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
	  
	  while (--num_rows >= 0)
	  {
	  
		  inptr = input_buf[0][input_row++];
		  
		  if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			 ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
		  {
			  continue;
		  }
		  s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);

		  for (col = 0; col < (HI_S32)num_cols; col++)
		  {
		  
			   if(	 (col >= pJpegHandle->stOutDesc.stCropRect.x)
					&&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				{
						retYBuf[s32RowYNum+u32Count] =	inptr[col];
						u32Count++;
				  }   
			   
		  }

	  }
	  
}


/*
 * Convert grayscale to RGB: just duplicate the graylevel three times.
 * This is provided to support applications that don't want to cope
 * with grayscale as a separate case.
 */

METHODDEF(void)
gray_rgb_convert (j_decompress_ptr cinfo,
		  JSAMPIMAGE input_buf, JDIMENSION input_row,
		  JSAMPARRAY output_buf, int num_rows)
{


	  register JSAMPROW inptr;
	  register HI_S32 col;
	  JDIMENSION num_cols = cinfo->output_width;

	  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
	  HI_S32 s32RowYNum  = 0;
	  HI_U32 u32Count = 0;

	  unsigned int  r = 0;
	  unsigned int  g = 1;
	  unsigned int  b = 2;

	  retYBuf	  = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
	  
	  while (--num_rows >= 0)
	  {
	 
			inptr = input_buf[0][input_row++];

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
			s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				 if(   (col >= pJpegHandle->stOutDesc.stCropRect.x)
					  &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				  {
						  retYBuf[s32RowYNum+3*u32Count+r] =  inptr[col];
						  retYBuf[s32RowYNum+3*u32Count+g] =  inptr[col];
						  retYBuf[s32RowYNum+3*u32Count+b] =  inptr[col];

						  u32Count++;
					}	
				 
			}
						 
	  }


}


METHODDEF(void)
gray_argb_8888_convert (j_decompress_ptr cinfo,
          JSAMPIMAGE input_buf, JDIMENSION input_row,
          JSAMPARRAY output_buf, int num_rows)
{


		  register JSAMPROW inptr;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_S32 s32RowYNum = 0;
		  HI_U32 u32Count = 0;

		  unsigned int  r = 0;
	      unsigned int  g = 1;
	      unsigned int  b = 2;

		  retYBuf	 = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  
		  while (--num_rows >= 0) 
		  {
			    inptr = input_buf[0][input_row++];
				
				if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
				{
					continue;
				}
				s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
				for (col = 0; col < (HI_S32)num_cols; col++)
				{

					if(   (col >= pJpegHandle->stOutDesc.stCropRect.x)
				         &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				    {
						  retYBuf[s32RowYNum+4*u32Count+r] =  inptr[col];
						  retYBuf[s32RowYNum+4*u32Count+g] =  inptr[col];
						  retYBuf[s32RowYNum+4*u32Count+b] =  inptr[col];
						  retYBuf[s32RowYNum+4*u32Count+3] = 0xFF;
						  u32Count++;
				    }
					
				}
			
		  }
	
}

METHODDEF(void)
gray_rgb_565_convert (j_decompress_ptr cinfo,
          JSAMPIMAGE input_buf, JDIMENSION input_row,
          JSAMPARRAY output_buf, int num_rows)
{

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;

		 register JSAMPROW inptr;
		 register HI_S32 col;
		 JDIMENSION num_cols = cinfo->output_width;

		 unsigned int r;

		 retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		 
		 while (--num_rows >= 0) 
		 {
			 
				inptr = input_buf[0][input_row++];
				if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
				{
					continue;
				}
				s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
				for (col = 0; col < (HI_S32)num_cols; col++)
				{

					if(   (col >= pJpegHandle->stOutDesc.stCropRect.x)
						&&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
					   {
							 r = inptr[col];
							 (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,r,r);
							 u32Count++;
							 
					   }
					  
				}
		   
		 }
  
}

METHODDEF(void)
gray_rgb_565D_convert (j_decompress_ptr cinfo,
          JSAMPIMAGE input_buf, JDIMENSION input_row,
          JSAMPARRAY output_buf, int num_rows)
{

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;


	   register JSAMPROW inptr;
	   register HI_S32 col;
	   register JSAMPLE * range_limit = cinfo->sample_range_limit;
	   JDIMENSION num_cols = cinfo->output_width;
	   INT32 d0 = dither_matrix[cinfo->output_scanline & DITHER_MASK];


	   unsigned int r;

	   retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
	   
	   while (--num_rows >= 0) 
	   {
		   
			 inptr = input_buf[0][input_row++];

			 if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

			  if(	(col >= pJpegHandle->stOutDesc.stCropRect.x)
				  &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				 {
					   d0 = DITHER_ROTATE(d0);
					   r = range_limit[DITHER_565_R(inptr[col], d0)];
					   (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,r,r);
					   u32Count++;
					   
				 }

			}
		 
	   }
		
}

METHODDEF(void)
gray_argb_1555_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{

	     /**
	      **Ҫ������alph0ֵ�� A = 0;   A8λ = 0
	      **Ҫ������alph1ֵ�� A = 1;   A8λ = 255
	      **/
		  register JSAMPROW inptr;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;
		  
		  
		  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_S32 s32RowYNum = 0;
		  HI_U32 u32Count = 0;

		  
		  unsigned int r;
		  HI_U8 a;

		  retYBuf	 = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  
		  while (--num_rows >= 0) 
		  {
			  
				inptr = input_buf[0][input_row];
				input_row++;

				if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
				{
					continue;
				}
				s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
				for (col = 0; col < (HI_S32)num_cols; col++)
				{

				    if(   (col >= pJpegHandle->stOutDesc.stCropRect.x)
					    &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
					{
				          r = *inptr++;
				          a =  0x0;
						  
						  (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT_1555(a,r,r,r);

						  u32Count++;
						  
				    }
				}
			
		  }
  
}

/*
 * Adobe-style YCCK->CMYK conversion.
 * We convert YCbCr to R=1-C, G=1-M, and B=1-Y using the same
 * conversion as above, while passing K (black) unchanged.
 * We assume build_ycc_rgb_table has been called.
 */

METHODDEF(void)
ycck_cmyk_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{



		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;


		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		register int y, cb, cr;
		register JSAMPROW inptr0, inptr1, inptr2, inptr3;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;
		/* copy these pointers into registers if possible */
		register JSAMPLE * range_limit = cinfo->sample_range_limit;
		register int * Crrtab = cconvert->Cr_r_tab;
		register int * Cbbtab = cconvert->Cb_b_tab;
		register INT32 * Crgtab = cconvert->Cr_g_tab;
		register INT32 * Cbgtab = cconvert->Cb_g_tab;
		SHIFT_TEMPS

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		while (--num_rows >= 0)
		{


			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			inptr3 = input_buf[3][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				   if(	 (col >= pJpegHandle->stOutDesc.stCropRect.x)
					   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				   {
						y  = GETJSAMPLE(inptr0[col]);
						cb = GETJSAMPLE(inptr1[col]);
						cr = GETJSAMPLE(inptr2[col]);

						retYBuf[s32RowYNum+4*u32Count]	 = range_limit[MAXJSAMPLE - (y + Crrtab[cr])];
						retYBuf[s32RowYNum+4*u32Count+1] = range_limit[MAXJSAMPLE - (y +
								((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr],
									   SCALEBITS)))];
						retYBuf[s32RowYNum+4*u32Count+2] = range_limit[MAXJSAMPLE - (y + Cbbtab[cb])];
						/* K passes through unchanged */
						retYBuf[s32RowYNum+4*u32Count+3] = inptr3[col];
						u32Count++;
				  }

			}

		}

}

#ifdef CONFIG_CONVERT_CMYK_RGB
/** revise by y00181162,set the output_color_space is JCS_CMYK **/
/**
 **   CMYK -> CMY
 **   C = ( C * (1 - K) + K )	   // for each CMY component
 **   CMY -> RGB
 **   R = ( 1 - C ) * 255		   // for each RGB component
 **   Unfortunately we are seeing inverted CMYK so all the original terms are 1-. This yields:
 **   CMYK -> CMY
 **   C = ( (1-C) * (1 - (1-K) + (1-K) ) -> C = 1 - C*K
 **   The conversion from CMY->RGB remains the same
**/
#define SkMulS16(x, y)  ((x) * (y))

static inline HI_U8 MulDiv255Round(HI_U16 a, HI_U16 b) 
{
	if(a > 32767 || b > 32767)
	{
		return 0;
	}
	unsigned prod = SkMulS16(a, b) + 128;
	return (prod + (prod >> 8)) >> 8;
	
}

METHODDEF(void)
 cmyk_argb_8888_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{

    	  JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_S32 s32RowYNum  = 0;
		  HI_U32 u32Count = 0;
		
		  register JSAMPROW inptr0, inptr1, inptr2,inptr3;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  unsigned int  r = 0;
		  unsigned int  g = 1;
		  unsigned int  b = 2;

		  retYBuf	 = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  
		  if(JCS_ABGR_8888 == cinfo->out_color_space)
		  {
			  r = 2;
			  b = 0;
		  }
		  while (--num_rows >= 0) 
		  {
		  
			  inptr0 = input_buf[0][input_row];
			  inptr1 = input_buf[1][input_row];
			  inptr2 = input_buf[2][input_row];
			  inptr3 = input_buf[3][input_row];
			  input_row++;
		
			  if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				 ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			  {
				  continue;
			  }
			  s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			  for (col = 0; col < (HI_S32)num_cols; col++)
			  {
		
				  if(	(col >= pJpegHandle->stOutDesc.stCropRect.x)
					   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				   {
						  retYBuf[s32RowYNum+4*u32Count+r] =  GETJSAMPLE(inptr0[col]);
						  retYBuf[s32RowYNum+4*u32Count+g] =  GETJSAMPLE(inptr1[col]);
						  retYBuf[s32RowYNum+4*u32Count+b] =  GETJSAMPLE(inptr2[col]);
						  retYBuf[s32RowYNum+4*u32Count+3] =  GETJSAMPLE(inptr3[col]);

						  u32Count++;
					}
			  }
		
		}

}

METHODDEF(void)
 cmyk_rgb_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{

	
	  JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);


	  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
	  HI_S32 s32RowYNum  = 0;
	  HI_U32 u32Count = 0;
	
	  register JSAMPROW inptr0, inptr1, inptr2,inptr3;
	  register HI_S32 col;
	  JDIMENSION num_cols = cinfo->output_width;

	  unsigned int  r = 0;
	  unsigned int  g = 1;
	  unsigned int  b = 2;
	  
	  unsigned int  Red,Green,Blue;
	  unsigned char Alpha;

	  retYBuf	 = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
	  
	  if(JCS_BGR == cinfo->out_color_space)
	  {
		 r = 2;
		 b = 0;
	  }
	  while (--num_rows >= 0) 
	  {
	  
		  inptr0 = input_buf[0][input_row];
		  inptr1 = input_buf[1][input_row];
		  inptr2 = input_buf[2][input_row];
		  inptr3 = input_buf[3][input_row];
		  input_row++;
	
		  if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			 ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
		  {
			  continue;
		  }
		  s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
		  for (col = 0; col < (HI_S32)num_cols; col++)
		  {
	
			  if(	(col >= pJpegHandle->stOutDesc.stCropRect.x)
				   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
			   {
					  Red   = GETJSAMPLE(inptr0[col]);
					  Green = GETJSAMPLE(inptr1[col]);
					  Blue  = GETJSAMPLE(inptr2[col]);
					  Alpha = GETJSAMPLE(inptr3[col]);
					  retYBuf[s32RowYNum+3*u32Count+r]   =  MulDiv255Round(Red,Alpha);
					  retYBuf[s32RowYNum+3*u32Count+g]   =  MulDiv255Round(Green,Alpha);
					  retYBuf[s32RowYNum+3*u32Count+b]   =  MulDiv255Round(Blue,Alpha);
					  u32Count++;
				}
		  }
	
	}
	
}
METHODDEF(void)
 cmyk_argb_1555_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{

		  JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);


		  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_S32 s32RowYNum  = 0;
		  HI_U32 u32Count = 0;
		
		  register JSAMPROW inptr0, inptr1, inptr2,inptr3;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  unsigned int  r,g,b;
	      unsigned char a;

		  unsigned int  Red,Green,Blue;
	  	  unsigned char Alpha;

	  	  retYBuf	 = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  
		  while (--num_rows >= 0) 
		  {
		  
			  inptr0 = input_buf[0][input_row];
			  inptr1 = input_buf[1][input_row];
			  inptr2 = input_buf[2][input_row];
			  inptr3 = input_buf[3][input_row];
			  input_row++;
		
			  if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				 ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			  {
				  continue;
			  }
			  s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			  for (col = 0; col < (HI_S32)num_cols; col++)
			  {
		
				  if(	(col >= pJpegHandle->stOutDesc.stCropRect.x)
					   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				   {
						  r  =   GETJSAMPLE(inptr0[col]);
						  g  =   GETJSAMPLE(inptr1[col]);
					      b  =   GETJSAMPLE(inptr2[col]);
					      a  =   GETJSAMPLE(inptr3[col]);

						  Red    =  MulDiv255Round(r,a);
					      Green  =  MulDiv255Round(g,a);
					      Blue   =  MulDiv255Round(b,a);
					  	  Alpha  = 0XFF;
						  
                          if(JCS_ABGR_1555 == cinfo->out_color_space)
                          {
						    (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT_1555(Alpha,Red,Green,Blue);
                          }
						  else
						  {
                             (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT_1555(Alpha,Blue,Green,Red);
						  }
						  u32Count++;
					}
			  }
		
		}

}
METHODDEF(void)
 cmyk_rgb_565_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{

	
	  JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
	  HI_S32 s32RowYNum  = 0;
	  HI_U32 u32Count = 0;
	
	  register JSAMPROW inptr0, inptr1, inptr2,inptr3;
	  register HI_S32 col;
	  JDIMENSION num_cols = cinfo->output_width;

	  unsigned int r, g, b;
	  unsigned char a;
	  
	  unsigned int  Red,Green,Blue;

	  retYBuf	 = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
	  
	  while (--num_rows >= 0) 
	  {
	  
		  inptr0 = input_buf[0][input_row];
		  inptr1 = input_buf[1][input_row];
		  inptr2 = input_buf[2][input_row];
		  inptr3 = input_buf[3][input_row];
		  input_row++;
	
		  if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			 ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
		  {
			  continue;
		  }
		  s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
		  for (col = 0; col < (HI_S32)num_cols; col++)
		  {
	
			  if(	(col >= pJpegHandle->stOutDesc.stCropRect.x)
				   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
			   {
					  r  =   GETJSAMPLE(inptr0[col]);
					  g  =   GETJSAMPLE(inptr1[col]);
					  b  =   GETJSAMPLE(inptr2[col]); 
                      a  =   GETJSAMPLE(inptr3[col]);

					  Red    =  MulDiv255Round(r,a);
					  Green  =  MulDiv255Round(g,a);
					  Blue   =  MulDiv255Round(b,a);
						  
					  if(JCS_BGR_565 == cinfo->out_color_space)
					  {
					     (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(Red,Green,Blue);
					  }
					  else
					  {
					     (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(Blue,Green,Red);
					  }
					  u32Count++;
				}
		  }
	
	}
	
}

/**
 **R = 255*(100-C)*(100-K)/10000
 **G = 255*(100-M)*(100-K)/10000
 **B = 255*(100-Y)*(100-K)/10000
 **/

/**
 ** R = Y + 1.402*Cr - 179.456
 ** G = Y - 0.34414*Cb - 0.71414*Cr + 135.45984
 ** B = Y + 1.772*Cb - 226.816
 ** After that, conversion to CMYK image is performed as follows:
 ** C = 255 �C R
 ** M = 255 �C G
 ** Y = 255 �C B
 **/
 METHODDEF(void)
 ycck_argb_8888_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		register int y, cb, cr;
		register JSAMPROW inptr0, inptr1, inptr2, inptr3;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;

		register JSAMPLE * range_limit = cinfo->sample_range_limit;
		register int * Crrtab = cconvert->Cr_r_tab;
		register int * Cbbtab = cconvert->Cb_b_tab;
		register INT32 * Crgtab = cconvert->Cr_g_tab;
		register INT32 * Cbgtab = cconvert->Cb_g_tab;
		SHIFT_TEMPS

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;


		HI_U8 u8YCCK[4];
		HI_U8 u8MaxVal = 0;
		int C = 0;	/** cyan	**/
		int M = 1;	/** magenta **/
		int Y = 2;	/** yellow	**/
		int K = 3;	/** black	**/

		unsigned int  r = 0;
	    unsigned int  g = 1;
	    unsigned int  b = 2;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
	    if(JCS_ABGR_8888 == cinfo->out_color_space)
	    {
		  r = 2;
		  b = 0;
	    }
		while (--num_rows >= 0)
		{

			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			inptr3 = input_buf[3][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
			s32RowYNum	= pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				   if(	 (col >= pJpegHandle->stOutDesc.stCropRect.x)
					   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				   {	
						y  = GETJSAMPLE(inptr0[col]);
						cb = GETJSAMPLE(inptr1[col]);
						cr = GETJSAMPLE(inptr2[col]);
			  
						u8YCCK[C]  = range_limit[MAXJSAMPLE - (y + Crrtab[cr])];
						u8YCCK[M]  = range_limit[MAXJSAMPLE - (y +
									((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr],SCALEBITS)))];
						u8YCCK[Y]  = range_limit[MAXJSAMPLE - (y + Cbbtab[cb])];
						u8YCCK[K]  = inptr3[col];

						u8MaxVal = u8YCCK[C]>u8YCCK[M]? u8YCCK[C]:u8YCCK[M];
						u8MaxVal = u8MaxVal>u8YCCK[Y]? u8MaxVal:u8YCCK[Y];
						u8MaxVal = u8MaxVal>u8YCCK[K]? u8MaxVal:u8YCCK[K];
						
						retYBuf[s32RowYNum+4*u32Count+r] =	(u8YCCK[K]*u8YCCK[C])/u8MaxVal;
						retYBuf[s32RowYNum+4*u32Count+g] =	(u8YCCK[K]*u8YCCK[M])/u8MaxVal; 
						retYBuf[s32RowYNum+4*u32Count+b] =	(u8YCCK[K]*u8YCCK[Y])/u8MaxVal;
                        retYBuf[s32RowYNum+4*u32Count+3] = 0xFF;
						
						u32Count++;
						
				  }
				   
			}
			
		}


}

METHODDEF(void)
ycck_rgb_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{


		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
		
		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		register int y, cb, cr;
		register JSAMPROW inptr0, inptr1, inptr2, inptr3;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;
	
		register JSAMPLE * range_limit = cinfo->sample_range_limit;
		register int * Crrtab = cconvert->Cr_r_tab;
		register int * Cbbtab = cconvert->Cb_b_tab;
		register INT32 * Crgtab = cconvert->Cr_g_tab;
		register INT32 * Cbgtab = cconvert->Cb_g_tab;
		SHIFT_TEMPS

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;


		HI_U8 u8YCCK[4];
		HI_U8 u8MaxVal = 0;
		int C = 0;	/** cyan	**/
		int M = 1;	/** magenta **/
		int Y = 2;	/** yellow	**/
		int K = 3;	/** black	**/

		unsigned int  r = 0;
		unsigned int  g = 1;
		unsigned int  b = 2;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		if(JCS_BGR == cinfo->out_color_space)
		{
			r = 2;
			b = 0;
		}
		while (--num_rows >= 0)
		{
		
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			inptr3 = input_buf[3][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				   if(	 (col >= pJpegHandle->stOutDesc.stCropRect.x)
					   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				   {	
						y  = GETJSAMPLE(inptr0[col]);
						cb = GETJSAMPLE(inptr1[col]);
						cr = GETJSAMPLE(inptr2[col]);
			  
						u8YCCK[C]  = range_limit[MAXJSAMPLE - (y + Crrtab[cr])];
						u8YCCK[M]  = range_limit[MAXJSAMPLE - (y +
									((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr],SCALEBITS)))];
						u8YCCK[Y]  = range_limit[MAXJSAMPLE - (y + Cbbtab[cb])];
						u8YCCK[K]  = inptr3[col];

						u8MaxVal = u8YCCK[C]>u8YCCK[M]? u8YCCK[C]:u8YCCK[M];
						u8MaxVal = u8MaxVal>u8YCCK[Y]? u8MaxVal:u8YCCK[Y];
						u8MaxVal = u8MaxVal>u8YCCK[K]? u8MaxVal:u8YCCK[K];
						
						retYBuf[s32RowYNum+3*u32Count+r] =	(u8YCCK[K]*u8YCCK[C])/u8MaxVal;
						retYBuf[s32RowYNum+3*u32Count+g] =	(u8YCCK[K]*u8YCCK[M])/u8MaxVal; 
						retYBuf[s32RowYNum+3*u32Count+b] =	(u8YCCK[K]*u8YCCK[Y])/u8MaxVal;

						u32Count++;
						
				  }
				   
			}
			
		}

}


 METHODDEF(void)
 ycck_argb_1555_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		register int y, cb, cr;
		register JSAMPROW inptr0, inptr1, inptr2, inptr3;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;

		register JSAMPLE * range_limit = cinfo->sample_range_limit;
		register int * Crrtab = cconvert->Cr_r_tab;
		register int * Cbbtab = cconvert->Cb_b_tab;
		register INT32 * Crgtab = cconvert->Cr_g_tab;
		register INT32 * Cbgtab = cconvert->Cb_g_tab;
		SHIFT_TEMPS

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;


		HI_U8 u8YCCK[4];
		HI_U8 u8MaxVal = 0;
		int C = 0;	/** cyan	**/
		int M = 1;	/** magenta **/
		int Y = 2;	/** yellow	**/
		int K = 3;	/** black	**/

		unsigned int  r,g,b;
	    unsigned char a;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		while (--num_rows >= 0)
		{

			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			inptr3 = input_buf[3][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
			s32RowYNum	= pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				   if(	 (col >= pJpegHandle->stOutDesc.stCropRect.x)
					   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				   {	
						y  = GETJSAMPLE(inptr0[col]);
						cb = GETJSAMPLE(inptr1[col]);
						cr = GETJSAMPLE(inptr2[col]);
			  
						u8YCCK[C]  = range_limit[MAXJSAMPLE - (y + Crrtab[cr])];
						u8YCCK[M]  = range_limit[MAXJSAMPLE - (y +
									((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr],SCALEBITS)))];
						u8YCCK[Y]  = range_limit[MAXJSAMPLE - (y + Cbbtab[cb])];
						u8YCCK[K]  = inptr3[col];

						u8MaxVal = u8YCCK[C]>u8YCCK[M]? u8YCCK[C]:u8YCCK[M];
						u8MaxVal = u8MaxVal>u8YCCK[Y]? u8MaxVal:u8YCCK[Y];
						u8MaxVal = u8MaxVal>u8YCCK[K]? u8MaxVal:u8YCCK[K];
						
						r =	(u8YCCK[K]*u8YCCK[C])/u8MaxVal;
						g =	(u8YCCK[K]*u8YCCK[M])/u8MaxVal; 
						b =	(u8YCCK[K]*u8YCCK[Y])/u8MaxVal;
                        a = 0x0;

						if(JCS_ABGR_1555 == cinfo->out_color_space)
                        {
						    (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT_1555(a,r,g,b);
                        }
						else
						{
                            (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT_1555(a,b,g,r);
						}
						u32Count++;
						
				  }
				   
			}
			
		}


}

METHODDEF(void)
ycck_rgb_565_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{


		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
		
		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		register int y, cb, cr;
		register JSAMPROW inptr0, inptr1, inptr2, inptr3;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;
	
		register JSAMPLE * range_limit = cinfo->sample_range_limit;
		register int * Crrtab = cconvert->Cr_r_tab;
		register int * Cbbtab = cconvert->Cb_b_tab;
		register INT32 * Crgtab = cconvert->Cr_g_tab;
		register INT32 * Cbgtab = cconvert->Cb_g_tab;
		SHIFT_TEMPS

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;


		HI_U8 u8YCCK[4];
		HI_U8 u8MaxVal = 0;
		int C = 0;	/** cyan	**/
		int M = 1;	/** magenta **/
		int Y = 2;	/** yellow	**/
		int K = 3;	/** black	**/

		unsigned int r, g, b;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
		while (--num_rows >= 0)
		{
		
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			inptr3 = input_buf[3][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				   if(	 (col >= pJpegHandle->stOutDesc.stCropRect.x)
					   &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				   {	
						y  = GETJSAMPLE(inptr0[col]);
						cb = GETJSAMPLE(inptr1[col]);
						cr = GETJSAMPLE(inptr2[col]);
			  
						u8YCCK[C]  = range_limit[MAXJSAMPLE - (y + Crrtab[cr])];
						u8YCCK[M]  = range_limit[MAXJSAMPLE - (y +
									((int) RIGHT_SHIFT(Cbgtab[cb] + Crgtab[cr],SCALEBITS)))];
						u8YCCK[Y]  = range_limit[MAXJSAMPLE - (y + Cbbtab[cb])];
						u8YCCK[K]  = inptr3[col];

						u8MaxVal = u8YCCK[C]>u8YCCK[M]? u8YCCK[C]:u8YCCK[M];
						u8MaxVal = u8MaxVal>u8YCCK[Y]? u8MaxVal:u8YCCK[Y];
						u8MaxVal = u8MaxVal>u8YCCK[K]? u8MaxVal:u8YCCK[K];
						
						r =	(u8YCCK[K]*u8YCCK[C])/u8MaxVal;
						g =	(u8YCCK[K]*u8YCCK[M])/u8MaxVal; 
						b =	(u8YCCK[K]*u8YCCK[Y])/u8MaxVal;

						if(JCS_BGR_565 == cinfo->out_color_space)
					    {
					       (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(r,g,b);
					    }
					    else
					    {
					       (*(INT16*)(retYBuf+s32RowYNum+2*u32Count)) = PACK_SHORT2_565(b,g,r);
					    }
					    u32Count++;
				  }
				   
			}
			
		}

}
#endif

METHODDEF(void)
output_ycbcr_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{


		  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_S32 s32RowYNum  = 0;
		  HI_U32 u32Count = 0;

		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  retYBuf = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  
		  while (--num_rows >= 0) 
		  {
		  
				inptr0 = input_buf[0][input_row];
				inptr1 = input_buf[1][input_row];
				inptr2 = input_buf[2][input_row];
				input_row++;

				if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
				   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
				{
					continue;
				}
                s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
				for (col = 0; col < (HI_S32)num_cols; col++)
				{
					 if(   (col >= pJpegHandle->stOutDesc.stCropRect.x)
						 &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
					 {
							  retYBuf[s32RowYNum+3*u32Count]   = GETJSAMPLE(inptr0[col]);
					          retYBuf[s32RowYNum+3*u32Count+1] = GETJSAMPLE(inptr1[col]);
					          retYBuf[s32RowYNum+3*u32Count+2] = GETJSAMPLE(inptr2[col]);
							  u32Count++;
					    }
				   
				}
			
		}
			  
}


METHODDEF(void)
output_crcby_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{

	
		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		HI_CHAR* retYBuf   = (HI_CHAR*)output_buf;/** deal with warning **/
		HI_S32 s32RowYNum  = 0;
		HI_U32 u32Count = 0;

		register JSAMPROW inptr0, inptr1, inptr2;
		register HI_S32 col;
		JDIMENSION num_cols = cinfo->output_width;

		retYBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		
	    while (--num_rows >= 0) 
	    {
	  
			inptr0 = input_buf[0][input_row];
			inptr1 = input_buf[1][input_row];
			inptr2 = input_buf[2][input_row];
			input_row++;

			if(  ((cinfo->output_scanline) < (HI_U32)pJpegHandle->stOutDesc.stCropRect.y) 
			   ||((cinfo->output_scanline+1) > (HI_U32)(pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))
			{
				continue;
			}
            s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * (cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y);
			for (col = 0; col < (HI_S32)num_cols; col++)
			{

				if(   (col >= pJpegHandle->stOutDesc.stCropRect.x)
					 &&(col < (pJpegHandle->stOutDesc.stCropRect.w + pJpegHandle->stOutDesc.stCropRect.x)))
				{
					  retYBuf[s32RowYNum+3*u32Count]   = GETJSAMPLE(inptr2[col]);
					  retYBuf[s32RowYNum+3*u32Count+1] = GETJSAMPLE(inptr1[col]);
					  retYBuf[s32RowYNum+3*u32Count+2] = GETJSAMPLE(inptr0[col]);
					  u32Count++;
				}
			   
			}

	   }
		
}
#endif


/**
 ** csc output yuv semi-planer
 ** CNcomment: �������yuv semi-planer CNend\n
 **/
METHODDEF(void)
yuv400_sp_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{


		  JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf    = (HI_CHAR*)output_buf;/** deal with warning **/
          HI_S32 s32RowYNum;

		  retYBuf      = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  s32RowYNum   = (pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0]) * cinfo->output_scanline;

		  register JSAMPROW inptr;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  while (--num_rows >= 0)
		  {
		 
			    inptr = input_buf[0][input_row];
				input_row++;
			    for (col = 0; col < (HI_S32)num_cols; col++) 
				{
				  retYBuf[s32RowYNum+col] = GETJSAMPLE(inptr[col]);
				  #ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
				  if(HI_TRUE == pJpegHandle->bLuPixSum)
				  {
					 pJpegHandle->u64LuPixValue += retYBuf[s32RowYNum+col];
				  }
				  #endif
			    }
				
		  }
		  
		
}

#ifdef CONFIG_JPEG_OUTPUT_YUV420SP

METHODDEF(void)
yuv444_to_yuv420_sp_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)

{



	      JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf    = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_CHAR* retCbCrBuf = pJpegHandle->stOutDesc.stOutSurface.pOutVir[1];

          HI_S32 s32RowYNum,s32RowCbCrNum;
          HI_S32 s32Cnt = 0;

		  retYBuf       = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  s32RowYNum    = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * cinfo->output_scanline;
		  s32RowCbCrNum = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[1] * (cinfo->output_scanline/2);

		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  while (--num_rows >= 0)
		  {
		  
			    inptr0 = input_buf[0][input_row];
			    inptr1 = input_buf[1][input_row];
			    inptr2 = input_buf[2][input_row];
			    input_row++;
				
			    for (col = 0; col < (HI_S32)num_cols; col++) 
				{
					retYBuf[s32RowYNum+col] = GETJSAMPLE(inptr0[col]);
                    #ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
					if(HI_TRUE == pJpegHandle->bLuPixSum)
					{
					   pJpegHandle->u64LuPixValue += retYBuf[s32RowYNum+col];
					}
                    #endif
		        }

				if(0 != cinfo->output_scanline % 2)
				{
                     continue;
				}
				for (col = 0; col < (HI_S32)num_cols; col++) 
				{
				    if(0 == col % 2)
				    {
						retCbCrBuf[s32RowCbCrNum+2*s32Cnt]   = GETJSAMPLE(inptr2[col]);
						retCbCrBuf[s32RowCbCrNum+2*s32Cnt+1] = GETJSAMPLE(inptr1[col]);
						s32Cnt++;
				    }
		        }

		}
		
}
#endif


METHODDEF(void)
yuv444_sp_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{



	      JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf    = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_CHAR* retCbCrBuf = pJpegHandle->stOutDesc.stOutSurface.pOutVir[1];
          HI_S32 s32RowYNum,s32RowCbCrNum;

		  retYBuf       = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  s32RowYNum    = (pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0]) * cinfo->output_scanline;
		  s32RowCbCrNum = (pJpegHandle->stOutDesc.stOutSurface.u32OutStride[1]) * cinfo->output_scanline;

		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  while (--num_rows >= 0)
		  {
		  
			    inptr0 = input_buf[0][input_row];
			    inptr1 = input_buf[1][input_row];
			    inptr2 = input_buf[2][input_row];
			    input_row++;
				
			    for (col = 0; col < (HI_S32)num_cols; col++) 
				{
					retYBuf[s32RowYNum+col] = GETJSAMPLE(inptr0[col]);
					retCbCrBuf[s32RowCbCrNum+2*col]   = GETJSAMPLE(inptr2[col]);
					retCbCrBuf[s32RowCbCrNum+2*col+1] = GETJSAMPLE(inptr1[col]);
                    #ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
					if(HI_TRUE == pJpegHandle->bLuPixSum)
					{
					   pJpegHandle->u64LuPixValue += retYBuf[s32RowYNum+col];
					}
                    #endif
		        }
		}
		
}


METHODDEF(void)
yuv420_sp_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{


          HI_S32 s32RowYNum,s32RowCbCrNum;
		  HI_S32 s32Tmp = 0;
		  
	      JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf    = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_CHAR* retCbCrBuf = pJpegHandle->stOutDesc.stOutSurface.pOutVir[1];

		  retYBuf     = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  s32RowYNum  = (pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0]) * cinfo->output_scanline;
		 
		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;
		  
		  while (--num_rows >= 0)
		  {
		  
			    inptr0 = input_buf[0][input_row];
			    inptr1 = input_buf[1][input_row];
			    inptr2 = input_buf[2][input_row];
			    input_row++;
				
			    for (col = 0; col < (HI_S32)num_cols; col++) 
				{
					retYBuf[s32RowYNum+col] = GETJSAMPLE(inptr0[col]);
					#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
				    if(HI_TRUE == pJpegHandle->bLuPixSum)
				    {
					   pJpegHandle->u64LuPixValue += retYBuf[s32RowYNum+col];
				    }
				    #endif
		        }

				if(0 !=cinfo->output_scanline%2)
				{
				   continue;
				}
				/**
				** ������YUV422 21 �� YUV422 12���ص�
				**/
				s32RowCbCrNum = (pJpegHandle->stOutDesc.stOutSurface.u32OutStride[1]) * cinfo->output_scanline/2;
				for (col = 0; col < (HI_S32)num_cols; col++) 
				{
				    if(0 == s32Tmp)
				    {
				         retCbCrBuf[s32RowCbCrNum+col] = GETJSAMPLE(inptr2[col]);
						 s32Tmp = 1;
				    }
					else
					{
					     retCbCrBuf[s32RowCbCrNum+col] = GETJSAMPLE(inptr1[col]);
						 s32Tmp = 0;
					}
				}
				
		}
		
}


#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
METHODDEF(void)
yuv422_12_to_yuv420_sp_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{


          HI_S32 s32RowYNum,s32RowCbCrNum;
		  HI_S32 s32Cnt = 0;

	      JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf    = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_CHAR* retCbCrBuf = pJpegHandle->stOutDesc.stOutSurface.pOutVir[1];

          retYBuf     = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  s32RowYNum  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * cinfo->output_scanline;
		 
		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  while (--num_rows >= 0)
		  {
		  
			    inptr0 = input_buf[0][input_row];
			    inptr1 = input_buf[1][input_row];
			    inptr2 = input_buf[2][input_row];
			    input_row++;
				
			    for (col = 0; col < (HI_S32)num_cols; col++) 
				{
					retYBuf[s32RowYNum+col] = GETJSAMPLE(inptr0[col]);	
                    #ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
				    if(HI_TRUE == pJpegHandle->bLuPixSum)
				    {
					   pJpegHandle->u64LuPixValue += retYBuf[s32RowYNum+col];
				    }
                    #endif
		        }

				if(0 != cinfo->output_scanline%2)
				{
				   continue;
				}
				
			    s32RowCbCrNum = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[1] * cinfo->output_scanline/2;
				for (col = 0; col < (HI_S32)num_cols; col++) 
				{
				    if(0 == col % 2)
				    {
					    retCbCrBuf[s32RowCbCrNum+2*s32Cnt]   = GETJSAMPLE(inptr2[col]);
						retCbCrBuf[s32RowCbCrNum+2*s32Cnt+1] = GETJSAMPLE(inptr1[col]);
						s32Cnt++;
				    }
		        }
				
		}
		
}


#endif

METHODDEF(void)
yuv422_12_sp_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{


          HI_S32 s32RowYNum,s32RowCbCrNum;
		  
	      JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf    = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_CHAR* retCbCrBuf = pJpegHandle->stOutDesc.stOutSurface.pOutVir[1];

          retYBuf     = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  s32RowYNum  = (pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0]) * cinfo->output_scanline;
		 
		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  
		  while (--num_rows >= 0)
		  {
		  
			    inptr0 = input_buf[0][input_row];
			    inptr1 = input_buf[1][input_row];
			    inptr2 = input_buf[2][input_row];
			    input_row++;
				
			    for (col = 0; col < (HI_S32)num_cols; col++) 
				{
					retYBuf[s32RowYNum+col] = GETJSAMPLE(inptr0[col]);
					#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
				    if(HI_TRUE == pJpegHandle->bLuPixSum)
				    {
					   pJpegHandle->u64LuPixValue += retYBuf[s32RowYNum+col];
				    }
				    #endif
		        }

				if(0 != cinfo->output_scanline%2)
				{
				    continue;
				}
				
				/**
				 ** �߶���Y��һ��
				 ** ȡһ�ж�һ�� 
				 **/
				s32RowCbCrNum = (pJpegHandle->stOutDesc.stOutSurface.u32OutStride[1]) * cinfo->output_scanline/2;
				for (col = 0; col < (HI_S32)num_cols; col++) 
				{
				    retCbCrBuf[s32RowCbCrNum+2*col]   = GETJSAMPLE(inptr2[col]);
					retCbCrBuf[s32RowCbCrNum+2*col+1] = GETJSAMPLE(inptr1[col]);
				}										

		}
		
}

#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
METHODDEF(void)
yuv422_21_to_yuv420_sp_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)

{


          HI_S32 s32RowYNum,s32RowCbCrNum;
		  HI_S32 s32Tmp = 0;
		  
	      JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf    = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_CHAR* retCbCrBuf = pJpegHandle->stOutDesc.stOutSurface.pOutVir[1];

          retYBuf       = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  s32RowYNum    = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0] * cinfo->output_scanline;
		  s32RowCbCrNum = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[1] * (cinfo->output_scanline/2);
		  	
		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;
		  
		  while (--num_rows >= 0)
		  {
		  
			    inptr0 = input_buf[0][input_row];
			    inptr1 = input_buf[1][input_row];
			    inptr2 = input_buf[2][input_row];
			    input_row++;
				
			    for (col = 0; col < (HI_S32)num_cols; col++) 
				{
					retYBuf[s32RowYNum+col] = GETJSAMPLE(inptr0[col]);
                    #ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
				    if(HI_TRUE == pJpegHandle->bLuPixSum)
				    {
					   pJpegHandle->u64LuPixValue += retYBuf[s32RowYNum+col];
				    }
                    #endif
		        }
				if(0 != cinfo->output_scanline%2)
				{
				   continue;
				}
				
				for (col = 0; col < (HI_S32)num_cols; col++) 
				{			
					if(0==s32Tmp)
					{/**
					  ** �����Y��һ��
					  ** UV������ȡ
					  **/
					   retCbCrBuf[s32RowCbCrNum+col] = GETJSAMPLE(inptr2[col]);
					   s32Tmp = 1;
					}
					else
					{
					   retCbCrBuf[s32RowCbCrNum+col]  = GETJSAMPLE(inptr1[col]);
					   s32Tmp = 0;
					}
					
		        }

		}


}


#endif

METHODDEF(void)
yuv422_21_sp_convert (j_decompress_ptr cinfo,
		   JSAMPIMAGE input_buf, JDIMENSION input_row,
		   JSAMPARRAY output_buf, int num_rows)
{


          HI_S32 s32RowYNum,s32RowCbCrNum;
		  HI_S32 s32Tmp = 0;
		  
	      JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		  HI_CHAR* retYBuf    = (HI_CHAR*)output_buf;/** deal with warning **/
		  HI_CHAR* retCbCrBuf = pJpegHandle->stOutDesc.stOutSurface.pOutVir[1];

		  retYBuf       = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		  s32RowYNum    = (pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0]) * cinfo->output_scanline;
		  s32RowCbCrNum = (pJpegHandle->stOutDesc.stOutSurface.u32OutStride[1]) * cinfo->output_scanline;
		  	
		  register JSAMPROW inptr0, inptr1, inptr2;
		  register HI_S32 col;
		  JDIMENSION num_cols = cinfo->output_width;

		  
		  while (--num_rows >= 0)
		  {
		  
			    inptr0 = input_buf[0][input_row];
			    inptr1 = input_buf[1][input_row];
			    inptr2 = input_buf[2][input_row];
			    input_row++;
				
			    for (col = 0; col < (HI_S32)num_cols; col++) 
				{
					retYBuf[s32RowYNum+col] = GETJSAMPLE(inptr0[col]);
					#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
				    if(HI_TRUE == pJpegHandle->bLuPixSum)
				    {
					   pJpegHandle->u64LuPixValue += retYBuf[s32RowYNum+col];
				    }
				    #endif
					if(0==s32Tmp)
					{/**
					  ** �����Y��һ��
					  ** UV������ȡ
					  **/
					   retCbCrBuf[s32RowCbCrNum+col] = GETJSAMPLE(inptr2[col]);
					   s32Tmp = 1;
					}
					else
					{
					   retCbCrBuf[s32RowCbCrNum+col]  = GETJSAMPLE(inptr1[col]);
					   s32Tmp = 0;
					}
					
		        }
				
		}


}




/*
 * Empty method for start_pass.
 */
/** deal with warning **/
METHODDEF(void)
start_pass_dcolor (j_decompress_ptr cinfo)
{
  /* no work needed */
  /** deal with warning **/
  if(JCS_UNKNOWN == cinfo->out_color_space)
  {
  	return;
  }
}

/*
 * Module initialization routine for output colorspace conversion.
 */

GLOBAL(void)
jinit_color_deconverter_userbuf (j_decompress_ptr cinfo)
{

		 my_cconvert_ptr cconvert;
#ifndef CONFIG_JPEG_CODE_CUT_RGB
		 int ci;
#endif/** CONFIG_JPEG_CODE_CUT_RGB **/
		 cconvert = (my_cconvert_ptr)
		   (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
					   SIZEOF(my_color_deconverter));
		 
		 cinfo->cconvert = (struct jpeg_color_deconverter *) cconvert;
		 cconvert->pub.start_pass = start_pass_dcolor;
		 
#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
		 JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
#endif
		 /* Make sure num_components agrees with jpeg_color_space */
		 switch (cinfo->jpeg_color_space) 
		 {
		 
			 case JCS_GRAYSCALE:
				   if (cinfo->num_components != 1)
				   {
					  ERREXIT(cinfo, JERR_BAD_J_COLORSPACE);
				   }
				   break;
			 case JCS_RGB:
			 case JCS_YCbCr:
				   if (cinfo->num_components != 3)
				   {
					 ERREXIT(cinfo, JERR_BAD_J_COLORSPACE);
				   }
				   break;
			 case JCS_CMYK:
			 case JCS_YCCK:
				   if (cinfo->num_components != 4)
				   {
					 ERREXIT(cinfo, JERR_BAD_J_COLORSPACE);
				   }
				   break;
			 default:		   /* JCS_UNKNOWN can be anything */
				   if (cinfo->num_components < 1)
				   {
					 ERREXIT(cinfo, JERR_BAD_J_COLORSPACE);
				   }
				   break;
		 }

#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
	     if(HI_TRUE == pJpegHandle->bOutYUV420SP)
		 {
		     switch(pJpegHandle->enImageFmt)
		     {
			 	case JPEG_FMT_YUV400:
					   if(JCS_GRAYSCALE == cinfo->jpeg_color_space)
					   {
						  cinfo->out_color_components = cinfo->num_components;
						  cconvert->pub.color_convert = yuv400_sp_convert;
					   }
					   else
					   {/* unsupported non-null conversion */
						   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
					   }
					   break;
				 case JPEG_FMT_YUV444:
					   if(JCS_YCbCr == cinfo->jpeg_color_space)
					   {
						  cinfo->out_color_components = cinfo->num_components;
						  cconvert->pub.color_convert = yuv444_to_yuv420_sp_convert;
					   }
					   else
					   {/* unsupported non-null conversion */
						   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
					   }
					   break;
				 case JPEG_FMT_YUV420:
					   if(JCS_YCbCr == cinfo->jpeg_color_space)
					   {
						  cinfo->out_color_components = cinfo->num_components;
						  cconvert->pub.color_convert = yuv420_sp_convert;
					   }
					   else
					   {/* unsupported non-null conversion */
						   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
					   }
					   break;
				 case JPEG_FMT_YUV422_21:
					   if(JCS_YCbCr == cinfo->jpeg_color_space)
					   {
						  cinfo->out_color_components = cinfo->num_components;
						  cconvert->pub.color_convert = yuv422_21_to_yuv420_sp_convert;
					   }
					   else
					   {/* unsupported non-null conversion */
						   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
					   }
					   break;
				 case JPEG_FMT_YUV422_12:
					   if(JCS_YCbCr == cinfo->jpeg_color_space)
					   {
						  cinfo->out_color_components = cinfo->num_components;
						  cconvert->pub.color_convert = yuv422_12_to_yuv420_sp_convert;
					   }
					   else
					   {
						   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
					   }
					   break;
				 default:
				 	   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				 	   break;
				 	   
		     }
		     if (cinfo->quantize_colors)
			 {
			   cinfo->output_components = 1;
			 }
			 else
			 {
			   cinfo->output_components = cinfo->out_color_components;
			 }
			 return;
				   
		 }
#endif/** CONFIG_JPEG_OUTPUT_YUV420SP **/

		 
		 switch (cinfo->out_color_space)
		 {
		 #ifndef CONFIG_JPEG_CODE_CUT_RGB 
			 case JCS_GRAYSCALE:
				   cinfo->out_color_components = 1;
				   if ( (cinfo->jpeg_color_space == JCS_GRAYSCALE) 
					   ||(cinfo->jpeg_color_space == JCS_YCbCr))
				   {
				   
						 cconvert->pub.color_convert = grayscale_convert;
						 /* For color->grayscale conversion, only the Y (0) component is needed */
						 for (ci = 1; ci < cinfo->num_components; ci++)
							  cinfo->comp_info[ci].component_needed = FALSE;
					 
				   } 
				   else
				   {
						 ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			  case JCS_RGB:
			  case JCS_BGR:
				   cinfo->out_color_components = RGB_PIXELSIZE;
				   if (cinfo->jpeg_color_space == JCS_YCbCr)
				   {
					   cconvert->pub.color_convert = ycc_rgb_convert;
					   build_ycc_rgb_table(cinfo);
				   } 
				   else if (cinfo->jpeg_color_space == JCS_GRAYSCALE) 
				   {
					   cconvert->pub.color_convert = gray_rgb_convert;
				   } 
				   else if (cinfo->jpeg_color_space == JCS_RGB && RGB_PIXELSIZE == 3) 
				   {
					   cconvert->pub.color_convert = rgb_rgb_888_convert;
					   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   #ifdef CONFIG_CONVERT_CMYK_RGB
				   	   /** revise by y00181162,set the output_color_space is JCS_CMYK **/
					   else if (cinfo->jpeg_color_space == JCS_YCCK) 
					   {
						   cconvert->pub.color_convert = ycck_rgb_convert;
						   build_ycc_rgb_table(cinfo);
					   }
					   else if (cinfo->jpeg_color_space == JCS_CMYK) 
					   {
						   cconvert->pub.color_convert = cmyk_rgb_convert;
					   }
				   #endif
				   else
				   {
					   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			  case JCS_ABGR_8888:
			  case JCS_ARGB_8888:
			  #ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
			  case JCS_RGBA_8888:
			  #endif
				   cinfo->out_color_components = 4;
				   if (cinfo->jpeg_color_space == JCS_YCbCr) 
				   {
					 cconvert->pub.color_convert = ycc_argb_8888_convert;
					 build_ycc_rgb_table(cinfo);
					 
				   } 
				   else if (cinfo->jpeg_color_space == JCS_GRAYSCALE)
				   {
					 cconvert->pub.color_convert = gray_argb_8888_convert;
				   }
				   else if (cinfo->jpeg_color_space == JCS_RGB)
				   {
					 cconvert->pub.color_convert = rgb_abgr_8888_convert;
				   }
				   #ifdef CONFIG_CONVERT_CMYK_RGB
					   /** revise by y00181162,set the output_color_space is JCS_CMYK **/
					   else if (cinfo->jpeg_color_space == JCS_YCCK) 
					   {
						   cconvert->pub.color_convert = ycck_argb_8888_convert;
						   build_ycc_rgb_table(cinfo);
					   }
					   else if (cinfo->jpeg_color_space == JCS_CMYK) 
					   {
						   cconvert->pub.color_convert = cmyk_argb_8888_convert;
					   }
				   #endif
				   else
				   {
					  ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			  case JCS_ARGB_1555:
				   cinfo->out_color_components = 2;
				   if (cinfo->jpeg_color_space == JCS_YCbCr) 
				   {
					  cconvert->pub.color_convert = ycc_abgr_1555_convert;
					  build_ycc_rgb_table(cinfo);
					 
				   } 
				   else if (cinfo->jpeg_color_space == JCS_GRAYSCALE)
				   {
					  cconvert->pub.color_convert = gray_argb_1555_convert;
				   }
				   else if (cinfo->jpeg_color_space == JCS_RGB)
				   {
					  cconvert->pub.color_convert = rgb_abgr_1555_convert;
				   }
				   #ifdef CONFIG_CONVERT_CMYK_RGB
				   	   /** revise by y00181162,set the output_color_space is JCS_CMYK **/
					   else if (cinfo->jpeg_color_space == JCS_YCCK) 
					   {
						   cconvert->pub.color_convert = ycck_argb_1555_convert;
						   build_ycc_rgb_table(cinfo);
					   }
					   else if (cinfo->jpeg_color_space == JCS_CMYK) 
					   {
						   cconvert->pub.color_convert = cmyk_argb_1555_convert;
					   }
				   #endif
				   else
				   {
					  ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			  case JCS_ABGR_1555:
				   cinfo->out_color_components = 2;
				   if (cinfo->jpeg_color_space == JCS_YCbCr) 
				   {
					  cconvert->pub.color_convert = ycc_argb_1555_convert;
					  build_ycc_rgb_table(cinfo);
					 
				   } 
				   else if (cinfo->jpeg_color_space == JCS_GRAYSCALE)
				   {
					  cconvert->pub.color_convert = gray_argb_1555_convert;
				   }
				   else if (cinfo->jpeg_color_space == JCS_RGB)
				   {
					  cconvert->pub.color_convert = rgb_argb_1555_convert;
				   }
				   #ifdef CONFIG_CONVERT_CMYK_RGB
				   	   /** revise by y00181162,set the output_color_space is JCS_CMYK **/
					   else if (cinfo->jpeg_color_space == JCS_YCCK) 
					   {
						   cconvert->pub.color_convert = ycck_argb_1555_convert;
						   build_ycc_rgb_table(cinfo);
					   }
					   else if (cinfo->jpeg_color_space == JCS_CMYK) 
					   {
						   cconvert->pub.color_convert = cmyk_argb_1555_convert;
					   }
				   #endif
				   else
				   {
					  ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;		   
			  case JCS_RGB_565:
				   cinfo->out_color_components = RGB_PIXELSIZE;
				   if (cinfo->dither_mode == JDITHER_NONE)
				   {
				   
						 if (cinfo->jpeg_color_space == JCS_YCbCr)
						 {
						   cconvert->pub.color_convert = ycc_rgb_565_convert;
						   build_ycc_rgb_table(cinfo);
						 } 
						 else if (cinfo->jpeg_color_space == JCS_GRAYSCALE) 
						 {
						   cconvert->pub.color_convert = gray_rgb_565_convert;
						 } 
						 else if (cinfo->jpeg_color_space == JCS_RGB) 
						 {
						   cconvert->pub.color_convert = rgb_rgb_565_convert;
						 }
						 #ifdef CONFIG_CONVERT_CMYK_RGB
						 	 /** revise by y00181162,set the output_color_space is JCS_CMYK **/
							 else if (cinfo->jpeg_color_space == JCS_YCCK) 
						     {
							   cconvert->pub.color_convert = ycck_rgb_565_convert;
							   build_ycc_rgb_table(cinfo);
						     }
						     else if (cinfo->jpeg_color_space == JCS_CMYK) 
						     {
							   cconvert->pub.color_convert = cmyk_rgb_565_convert;
						     }
						 #endif
						 else
						 {
						   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
						 }
					 
				   }
				   else
				   {
				   
						 /* only ordered dither is supported */
						 if (cinfo->jpeg_color_space == JCS_YCbCr) 
						 {
						   cconvert->pub.color_convert = ycc_rgb_565D_convert;
						   build_ycc_rgb_table(cinfo);
						 } 
						 else if (cinfo->jpeg_color_space == JCS_GRAYSCALE)
						 {
						   cconvert->pub.color_convert = gray_rgb_565D_convert;
						 } 
						 else if (cinfo->jpeg_color_space == JCS_RGB) 
						 {
						   cconvert->pub.color_convert = rgb_rgb_565D_convert;
						 }
						 #ifdef CONFIG_CONVERT_CMYK_RGB
						     /** revise by y00181162,set the output_color_space is JCS_CMYK **/
							 else if (cinfo->jpeg_color_space == JCS_YCCK) 
						     {
							   cconvert->pub.color_convert = ycck_rgb_565_convert;
							   build_ycc_rgb_table(cinfo);
						     }
						     else if (cinfo->jpeg_color_space == JCS_CMYK) 
						     {
							   cconvert->pub.color_convert = cmyk_rgb_565_convert;
						     }
						 #endif
						 else
						 {
						   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
						 }
					 
				   }
				   break;
			  case JCS_BGR_565:
				   cinfo->out_color_components = RGB_PIXELSIZE;
				   if (cinfo->dither_mode == JDITHER_NONE)
				   {
						 if (cinfo->jpeg_color_space == JCS_YCbCr)
						 {
						   cconvert->pub.color_convert = ycc_bgr_565_convert;
						   build_ycc_rgb_table(cinfo);
						 } 
						 else if (cinfo->jpeg_color_space == JCS_GRAYSCALE) 
						 {
						   cconvert->pub.color_convert = gray_rgb_565_convert;
						 } 
						 else if (cinfo->jpeg_color_space == JCS_RGB) 
						 {
						   cconvert->pub.color_convert = rgb_bgr_565_convert;
						 }
						 #ifdef CONFIG_CONVERT_CMYK_RGB
						     /** revise by y00181162,set the output_color_space is JCS_CMYK **/
							 else if (cinfo->jpeg_color_space == JCS_YCCK) 
						     {
							   cconvert->pub.color_convert = ycck_rgb_565_convert;
							   build_ycc_rgb_table(cinfo);
						     }
						     else if (cinfo->jpeg_color_space == JCS_CMYK) 
						     {
							   cconvert->pub.color_convert = cmyk_rgb_565_convert;
						     }
						 #endif
						 else
						 {
						   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
						 }
				   }
				   else
				   {
				   
						 /* only ordered dither is supported */
						 if (cinfo->jpeg_color_space == JCS_YCbCr) 
						 {
						   cconvert->pub.color_convert = ycc_bgr_565D_convert;
						   build_ycc_rgb_table(cinfo);
						 } 
						 else if (cinfo->jpeg_color_space == JCS_GRAYSCALE)
						 {
						   cconvert->pub.color_convert = gray_rgb_565D_convert;
						 } 
						 else if (cinfo->jpeg_color_space == JCS_RGB) 
						 {
						   cconvert->pub.color_convert = rgb_rgb_565D_convert;
						 }
						 #ifdef CONFIG_CONVERT_CMYK_RGB
							 else if (cinfo->jpeg_color_space == JCS_YCCK) 
						     {
							   cconvert->pub.color_convert = ycck_rgb_565_convert;
							   build_ycc_rgb_table(cinfo);
						     }
						     else if (cinfo->jpeg_color_space == JCS_CMYK) 
						     {
							   cconvert->pub.color_convert = cmyk_rgb_565_convert;
						     }
						 #endif
						 else
						 {
						   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
						 }
					 
				   }
				   break;
			 case JCS_CMYK:
				   cinfo->out_color_components = 4;
				   if (cinfo->jpeg_color_space == JCS_YCCK) 
				   {
					   cconvert->pub.color_convert = ycck_cmyk_convert;
					   build_ycc_rgb_table(cinfo);
				   }
				   else if (cinfo->jpeg_color_space == JCS_CMYK)
				   {
					  cconvert->pub.color_convert = null_convert;
				   }
				   else
				   {
					   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
		   #endif/** CONFIG_JPEG_CODE_CUT_RGB **/
			 case JCS_YUV400_SP:
				   if(JCS_GRAYSCALE == cinfo->jpeg_color_space)
				   {
					  cinfo->out_color_components = cinfo->num_components;
					  cconvert->pub.color_convert = yuv400_sp_convert;
				   }
				   else
				   {/* unsupported non-null conversion */
					   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			 case JCS_YUV444_SP:
				   if(JCS_YCbCr == cinfo->jpeg_color_space)
				   {
					  cinfo->out_color_components = cinfo->num_components;
					  cconvert->pub.color_convert = yuv444_sp_convert;
				   }
				   else
				   {/* unsupported non-null conversion */
					   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			 case JCS_YUV420_SP:
				   if(JCS_YCbCr == cinfo->jpeg_color_space)
				   {
					  cinfo->out_color_components = cinfo->num_components;
					  cconvert->pub.color_convert = yuv420_sp_convert;
				   }
				   else
				   {/* unsupported non-null conversion */
					   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			 case JCS_YUV422_SP_21:
				   if(JCS_YCbCr == cinfo->jpeg_color_space)
				   {
					  cinfo->out_color_components = cinfo->num_components;
					  cconvert->pub.color_convert = yuv422_21_sp_convert;
				   }
				   else
				   {/* unsupported non-null conversion */
					   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			 case JCS_YUV422_SP_12:
				   if(JCS_YCbCr == cinfo->jpeg_color_space)
				   {
					  cinfo->out_color_components = cinfo->num_components;
					  cconvert->pub.color_convert = yuv422_12_sp_convert;
				   }
				   else
				   {
					   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			 default:
			 #ifndef CONFIG_JPEG_CODE_CUT_RGB
				   /* Permit null conversion to same output space */
				   if (cinfo->out_color_space == cinfo->jpeg_color_space)
				   {
						cinfo->out_color_components = cinfo->num_components;
						cconvert->pub.color_convert = output_ycbcr_convert;
				   }
				   else if(  (JCS_CrCbY == cinfo->out_color_space)
						   &&(JCS_YCbCr == cinfo->jpeg_color_space))
				   {
					   cinfo->out_color_components = cinfo->num_components;
					   cconvert->pub.color_convert = output_crcby_convert;
				   }
				   else
				   {/* unsupported non-null conversion */
						ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
				   }
				   break;
			#else
				   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
			#endif/** CONFIG_JPEG_CODE_CUT_RGB **/
				   
			   
		 }

		 if (cinfo->quantize_colors)
		 {
		   cinfo->output_components = 1;
		 }
		 else
		 {
		   cinfo->output_components = cinfo->out_color_components;
		 }
	
}
