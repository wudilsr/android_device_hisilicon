/*
   (c) Copyright 2001-2010  The world wide DirectFB Open Source Community (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Hundt <andi@fischlustig.de>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrjälä <syrjala@sci.fi> and
              Claudio Ciccani <klan@users.sf.net>.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

#include <directfb.h>

#include <display/idirectfbsurface.h>

#include <media/idirectfbimageprovider.h>

#include <core/layers.h>

#include <core/CoreSurface.h>

#include <misc/gfx_util.h>
#include <misc/util.h>
#include <direct/interface.h>
#include <direct/mem.h>
#include <direct/memcpy.h>
#include <direct/messages.h>

#include <setjmp.h>
#include <math.h>

#undef HAVE_STDLIB_H
#include <jpeglib.h>
#include <hi_jpeg_api.h>

static DFBResult
Probe( IDirectFBImageProvider_ProbeContext *ctx );

static DFBResult
Construct( IDirectFBImageProvider *thiz,
           ... );

#include <direct/interface_implementation.h>

DIRECT_INTERFACE_IMPLEMENTATION( IDirectFBImageProvider, JPEG )

/*
 * private data struct of IDirectFBImageProvider_JPEG
 */
typedef struct {
     IDirectFBImageProvider_data base;

     int                  width;    /*  width of the JPEG image   */
     int                  height;   /*  height of the JPEG image  */

     u32                 *image;        /*  decoded image data    */
     int                  image_width;  /*  width of image data   */
     int                  image_height; /*  height of image data  */

     DIRenderFlags        flags;        /*  selected idct method  */
} IDirectFBImageProvider_JPEG_data;


static DFBResult
IDirectFBImageProvider_JPEG_RenderTo( IDirectFBImageProvider *thiz,
                                      IDirectFBSurface       *destination,
                                      const DFBRectangle     *destination_rect );

static DFBResult
IDirectFBImageProvider_JPEG_GetSurfaceDescription( IDirectFBImageProvider *thiz,
                                                   DFBSurfaceDescription  *dsc );

static DFBResult
IDirectFBImageProvider_JPEG_GetImageDescription( IDirectFBImageProvider *thiz,
                                                 DFBImageDescription    *dsc );

static DFBResult
IDirectFBImageProvider_JPEG_SetRenderFlags( IDirectFBImageProvider *thiz,
                                            DIRenderFlags flags );

#define JPEG_PROG_BUF_SIZE    0x10000

typedef struct {
     struct jpeg_source_mgr  pub; /* public fields */

     JOCTET                 *data;       /* start of buffer */

     IDirectFBDataBuffer    *buffer;

     int                     peekonly;
     int                     peekoffset;
} buffer_source_mgr;

typedef buffer_source_mgr * buffer_src_ptr;


static HI_CHAR* pLeaveBuf = NULL;
static HI_S32 gs_s32LeaveByte = 0;
static HI_S32 gs_s32Readbytes = 0;

/*****************************************************************************
* func        : duplicate_stream_info
* description : 
* param[in]   : 
* param[in]   :
* param[in]   :
* others:	  : nothing
*****************************************************************************/
static HI_VOID duplicate_stream_info(j_decompress_ptr cinfo)
{

	    buffer_src_ptr       src    = (buffer_src_ptr) cinfo->src;

		if(0==src->peekonly) 
		{
		    memcpy(pLeaveBuf,(char*)src->pub.next_input_byte,src->pub.bytes_in_buffer);
			gs_s32LeaveByte = src->pub.bytes_in_buffer;
		}
}

/*****************************************************************************
* func        : resume_stream
* description : 
* param[in]   : 
* param[in]   :
* param[in]   :
* others:	  : nothing
*****************************************************************************/
static HI_VOID resume_stream(j_decompress_ptr cinfo)
{


	   	buffer_src_ptr       src    = (buffer_src_ptr) cinfo->src;
	    IDirectFBDataBuffer *buffer = src->buffer;
     
		if (0==src->peekonly) 
		{
            memcpy((char*)src->pub.next_input_byte,pLeaveBuf,gs_s32LeaveByte);
			src->pub.bytes_in_buffer = gs_s32LeaveByte;
			buffer->SeekTo( buffer, gs_s32Readbytes);
		}
		gs_s32LeaveByte = 0;
		gs_s32Readbytes = 0;
}

static HI_VOID record_readbytes_before_stardecompress(
	                                       const unsigned int bytes,\
	                                       HI_BOOL read_write,
	                                       HI_BOOL cleanzero)
{     
  
	  if(HI_FALSE == read_write)
	  {
		     if(HI_TRUE==cleanzero)
		     {
		        gs_s32Readbytes = 0;
		     }
			 else
			 {
                gs_s32Readbytes += bytes;
			 }
	  }

}

static void
buffer_init_source (j_decompress_ptr cinfo)
{
     buffer_src_ptr src          = (buffer_src_ptr) cinfo->src;
     IDirectFBDataBuffer *buffer = src->buffer;

     buffer->SeekTo( buffer, 0 ); /* ignore return value */
}

static boolean
buffer_fill_input_buffer (j_decompress_ptr cinfo)
{
     DFBResult            ret;
     unsigned int         nbytes = 0;
     buffer_src_ptr       src    = (buffer_src_ptr) cinfo->src;
     IDirectFBDataBuffer *buffer = src->buffer;

     buffer->WaitForDataWithTimeout( buffer, JPEG_PROG_BUF_SIZE, 1, 0 );

     if (src->peekonly) {
          ret = buffer->PeekData( buffer, JPEG_PROG_BUF_SIZE,src->peekoffset, src->data, &nbytes );
          src->peekoffset += MAX( nbytes, 0 );
		  record_readbytes_before_stardecompress(0,HI_FALSE,HI_TRUE);
     }
     else 
	 {
          ret = buffer->GetData( buffer, JPEG_PROG_BUF_SIZE, src->data, &nbytes );
		  record_readbytes_before_stardecompress(nbytes,HI_FALSE,HI_FALSE);
     }

     if (ret || nbytes <= 0) {
          /* Insert a fake EOI marker */
          src->data[0] = (JOCTET) 0xFF;
          src->data[1] = (JOCTET) JPEG_EOI;
          nbytes = 2;

          if (ret && ret != DFB_EOF)
               DirectFBError( "(DirectFB/ImageProvider_JPEG) GetData failed", ret );
     }

     src->pub.next_input_byte = src->data;
     src->pub.bytes_in_buffer = nbytes;

     return TRUE;
}

static void
buffer_skip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
     buffer_src_ptr src = (buffer_src_ptr) cinfo->src;

     if (num_bytes > 0) {
          while (num_bytes > (long) src->pub.bytes_in_buffer) {
               num_bytes -= (long) src->pub.bytes_in_buffer;
               (void)buffer_fill_input_buffer(cinfo);
          }
          src->pub.next_input_byte += (size_t) num_bytes;
          src->pub.bytes_in_buffer -= (size_t) num_bytes;
     }
}

static void
buffer_term_source (j_decompress_ptr cinfo)
{
     D_UNUSED_P( cinfo );
}

static void
jpeg_buffer_src (j_decompress_ptr cinfo, IDirectFBDataBuffer *buffer, int peekonly)
{
     buffer_src_ptr src;

     cinfo->src = (struct jpeg_source_mgr *)
                  cinfo->mem->alloc_small ((j_common_ptr) cinfo, JPOOL_PERMANENT,
                                           sizeof (buffer_source_mgr));

     src = (buffer_src_ptr) cinfo->src;

     src->data = (JOCTET *)
                  cinfo->mem->alloc_small ((j_common_ptr) cinfo, JPOOL_PERMANENT,
                                           JPEG_PROG_BUF_SIZE * sizeof (JOCTET));

     src->buffer = buffer;
     src->peekonly = peekonly;
     src->peekoffset = 0;

     src->pub.init_source       = buffer_init_source;
     src->pub.fill_input_buffer = buffer_fill_input_buffer;
     src->pub.skip_input_data   = buffer_skip_input_data;
     src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
     src->pub.term_source       = buffer_term_source;
     src->pub.bytes_in_buffer   = 0; /* forces fill_input_buffer on first read */
     src->pub.next_input_byte   = NULL; /* until buffer loaded */
}

struct my_error_mgr {
     struct jpeg_error_mgr pub;     /* "public" fields */
     jmp_buf  setjmp_buffer;          /* for return to caller */
};

static void
jpeglib_panic(j_common_ptr cinfo)
{
     struct my_error_mgr *myerr = (struct my_error_mgr*) cinfo->err;
     longjmp(myerr->setjmp_buffer, 1);
}

static inline void
copy_line_nv16( u16 *yy, u16 *cbcr, const u8 *src_ycbcr, int width )
{
     int x;

     for (x=0; x<width/2; x++) {
#ifdef WORDS_BIGENDIAN
          yy[x] = (src_ycbcr[0] << 8) | src_ycbcr[3];

          cbcr[x] = (((src_ycbcr[1] + src_ycbcr[4]) << 7) & 0xff00) |
                     ((src_ycbcr[2] + src_ycbcr[5]) >> 1);
#else
          yy[x] = (src_ycbcr[3] << 8) | src_ycbcr[0];

          cbcr[x] = (((src_ycbcr[2] + src_ycbcr[5]) << 7) & 0xff00) |
                     ((src_ycbcr[1] + src_ycbcr[4]) >> 1);
#endif

          src_ycbcr += 6;
     }

     if (width & 1) {
          u8 *y = (u8*) yy;

          y[width-1] = src_ycbcr[0];

#ifdef WORDS_BIGENDIAN
          cbcr[x] = (src_ycbcr[1] << 8) | src_ycbcr[2];
#else
          cbcr[x] = (src_ycbcr[2] << 8) | src_ycbcr[1];
#endif
     }
}

static inline void
copy_line_uyvy( u32 *uyvy, const u8 *src_ycbcr, int width )
{
     int x;

     for (x=0; x<width/2; x++) {
#ifdef WORDS_BIGENDIAN
          uyvy[x] = (src_ycbcr[1] << 24) | (src_ycbcr[0] << 16) | (src_ycbcr[5] << 8) | src_ycbcr[3];
#else
          uyvy[x] = (src_ycbcr[3] << 24) | (src_ycbcr[5] << 16) | (src_ycbcr[0] << 8) | src_ycbcr[1];
#endif

          src_ycbcr += 6;
     }

     if (width & 1) {
#ifdef WORDS_BIGENDIAN
          uyvy[x] = (src_ycbcr[1] << 24) | (src_ycbcr[0] << 16) | (src_ycbcr[1] << 8) | src_ycbcr[0];
#else
          uyvy[x] = (src_ycbcr[0] << 24) | (src_ycbcr[1] << 16) | (src_ycbcr[0] << 8) | src_ycbcr[1];
#endif
     }
}


static void
IDirectFBImageProvider_JPEG_Destruct( IDirectFBImageProvider *thiz )
{
     IDirectFBImageProvider_JPEG_data *data =
                              (IDirectFBImageProvider_JPEG_data*)thiz->priv;

     if (data->image)
          D_FREE( data->image );
}

static DFBResult
Probe( IDirectFBImageProvider_ProbeContext *ctx )
{
     /* Look of the Jpeg SOI marker */
     if (ctx->header[0] == 0xff && ctx->header[1] == 0xd8) {
          /* Look for JFIF or Exif strings, also could look at header[3:2] for APP0(0xFFE0),
           * APP1(0xFFE1) or even other APPx markers.
           */
          if (strncmp ((char*) ctx->header + 6, "JFIF", 4) == 0 ||
              strncmp ((char*) ctx->header + 6, "Exif", 4) == 0 ||
              strncmp ((char*) ctx->header + 6, "VVL", 3) == 0 ||
              strncmp ((char*) ctx->header + 6, "WANG", 4) == 0)
               return DFB_OK;

          /* Else look for Quantization table marker or Define Huffman table marker,
           * useful for EXIF thumbnails that have no APPx markers.
           */
          if (ctx->header[2] == 0xff && (ctx->header[3] == 0xdb || ctx->header[3] == 0xc4))
               return DFB_OK;

          if (ctx->filename && strchr (ctx->filename, '.' ) &&
             (strcasecmp ( strchr (ctx->filename, '.' ), ".jpg" ) == 0 ||
              strcasecmp ( strchr (ctx->filename, '.' ), ".jpeg") == 0))
               return DFB_OK;
     }

     return DFB_UNSUPPORTED;
}

static DFBResult
Construct( IDirectFBImageProvider *thiz,
           ... )
{
     struct jpeg_decompress_struct cinfo;
     struct my_error_mgr jerr;

     IDirectFBDataBuffer *buffer;
     CoreDFB             *core;
     va_list              tag;

     DIRECT_ALLOCATE_INTERFACE_DATA(thiz, IDirectFBImageProvider_JPEG)

     va_start( tag, thiz );
     buffer = va_arg( tag, IDirectFBDataBuffer * );
     core = va_arg( tag, CoreDFB * );
     va_end( tag );

     data->base.ref    = 1;
     data->base.buffer = buffer;
     data->base.core   = core;

     buffer->AddRef( buffer );

     cinfo.err = jpeg_std_error(&jerr.pub);
     jerr.pub.error_exit = jpeglib_panic;

     if (setjmp(jerr.setjmp_buffer)) {
          D_ERROR( "ImageProvider/JPEG: Error while reading headers!\n" );

          jpeg_destroy_decompress(&cinfo);
          buffer->Release( buffer );
          DIRECT_DEALLOCATE_INTERFACE( thiz );
          return DFB_FAILURE;
     }

     jpeg_create_decompress(&cinfo);
     jpeg_buffer_src(&cinfo, buffer, 1);
     jpeg_read_header(&cinfo, TRUE);
	 jpeg_calc_output_dimensions(&cinfo);

     data->width = cinfo.output_width;
     data->height = cinfo.output_height;

     data->flags = DIRENDER_NONE;

     jpeg_abort_decompress(&cinfo);
     jpeg_destroy_decompress(&cinfo);

     if ( (cinfo.output_width == 0) || (cinfo.output_height == 0)) {
          buffer->Release( buffer );
          DIRECT_DEALLOCATE_INTERFACE( thiz );
          return DFB_FAILURE;
     }

     data->base.Destruct = IDirectFBImageProvider_JPEG_Destruct;

     thiz->RenderTo = IDirectFBImageProvider_JPEG_RenderTo;
     thiz->GetImageDescription =IDirectFBImageProvider_JPEG_GetImageDescription;
     thiz->SetRenderFlags = IDirectFBImageProvider_JPEG_SetRenderFlags;
     thiz->GetSurfaceDescription =
     IDirectFBImageProvider_JPEG_GetSurfaceDescription;

     return DFB_OK;
}

static int
wrap_setjmp( struct my_error_mgr *jerr )
{
     if (setjmp( jerr->setjmp_buffer ))
          return 1;
     else
          return 0;
}

static DFBResult
IDirectFBImageProvider_JPEG_RenderTo( IDirectFBImageProvider *thiz,
                                      IDirectFBSurface       *destination,
                                      const DFBRectangle     *dest_rect )
{
     DFBResult              ret;
     bool                   direct = false;
     DFBRegion              clip;
     DFBRectangle           rect;
     DFBSurfacePixelFormat  format;
     IDirectFBSurface_data *dst_data;
     CoreSurface           *dst_surface;
     CoreSurfaceBufferLock  lock;
     DIRenderCallbackResult cb_result = DIRCR_OK;
	 
     DIRECT_INTERFACE_GET_DATA(IDirectFBImageProvider_JPEG)

     dst_data = (IDirectFBSurface_data*) destination->priv;
     if (!dst_data)
     {
          return DFB_DEAD;
     }
	 
     dst_surface = dst_data->surface;
     if (!dst_surface)
     {
          return DFB_DESTROYED;
     }
     ret = destination->GetPixelFormat( destination, &format);
     if (ret)
     {
          return ret;
     }
	 
     dfb_region_from_rectangle( &clip, &dst_data->area.current );
     if (dest_rect) 
	 {
          if (dest_rect->w < 1 || dest_rect->h < 1)
          {
               return DFB_INVARG;
          }
          rect = *dest_rect;
          rect.x += dst_data->area.wanted.x;
          rect.y += dst_data->area.wanted.y;
          if (!dfb_rectangle_region_intersects( &rect, &clip ))
          {
               return DFB_OK;
          }
     }
     else 
	 {
          rect = dst_data->area.wanted;
     }

     ret = dfb_surface_lock_buffer( dst_surface, CSBR_BACK, CSAID_CPU, CSAF_WRITE, &lock );
     if (ret)
     {
          return ret;
     }
	 
     if (data->image && (rect.x || rect.y || rect.w != data->image_width || rect.h != data->image_height)) 
     {
           D_FREE( data->image );
           data->image        = NULL;
           data->image_width  = 0;
           data->image_height = 0;
     }

     /* actual loading and rendering */
     if (!data->image) 
	 {

          struct jpeg_decompress_struct cinfo;
          struct my_error_mgr jerr;
          JSAMPARRAY buffer = NULL;      /* Output row buffer */
          int row_stride;         /* physical row width in output buffer */
          u32 *row_ptr = NULL;
          int y = 0;
          int uv_offset = 0;

		  HI_JPEG_SURFACE_DESCRIPTION_S stSurfaceDesc;
		  HI_JPEG_INFO_S stJpegInfo;
		  int s32WScale = 0;
		  int s32HScale = 0;
		  bool bRet = FALSE;
		  
          cinfo.err = jpeg_std_error(&jerr.pub);
          jerr.pub.error_exit = jpeglib_panic;

		  /**
		   **dec failure dispose with
		   **/
          if (wrap_setjmp( &jerr )) 
		  {
		  
               D_ERROR( "ImageProvider/JPEG: Error during decoding!\n" );
			   if(NULL != pLeaveBuf)
			   {
			  	  free(pLeaveBuf);
				  pLeaveBuf = NULL;
				  gs_s32LeaveByte = 0;
				  gs_s32Readbytes = 0;
			   }
               jpeg_destroy_decompress( &cinfo );
               if (data->image) 
			   {
                    dfb_scale_linear_32( data->image, data->image_width, data->image_height,
                                         lock.addr, lock.pitch, &rect, dst_surface, &clip );
                    dfb_surface_unlock_buffer( dst_surface, &lock );
                    if (data->base.render_callback) 
					{
                         DFBRectangle r = { 0, 0, data->image_width, data->image_height };
                         if (data->base.render_callback( &r,data->base.render_callback_context ) != DIRCR_OK)
                         {
                              return DFB_INTERRUPTED;
                         }
                    }
                    return DFB_INCOMPLETE;
               }
               else
               {
                    dfb_surface_unlock_buffer( dst_surface, &lock );
               }
               return DFB_FAILURE;
          }

		  if (setjmp( jerr.setjmp_buffer ))
		  {
		  	 D_ERROR( "ImageProvider/JPEG: Error during decoding!\n" );
			 if(NULL != pLeaveBuf)
			 {
				free(pLeaveBuf);
				pLeaveBuf = NULL;
				gs_s32LeaveByte = 0;
				gs_s32Readbytes = 0;
			 }
			 jpeg_destroy_decompress(&cinfo );
			 return DFB_FAILURE;
		  }

		  
		   memset(&stSurfaceDesc,0,sizeof(HI_JPEG_SURFACE_DESCRIPTION_S));
		   memset(&stJpegInfo,0,sizeof(HI_JPEG_INFO_S));
		   
           jpeg_create_decompress( &cinfo );
           jpeg_buffer_src( &cinfo, data->base.buffer, 0 );
           jpeg_read_header( &cinfo, TRUE );

		   stJpegInfo.bOutInfo = HI_FALSE;
		   HI_JPEG_GetJpegInfo(&cinfo,&stJpegInfo);
		  
		   #if 0// JPEG_LIB_VERSION >= 70
	          cinfo.scale_num   = 8;
	          cinfo.scale_denom = 8;
           #else
	          cinfo.scale_num   = 1;
	          cinfo.scale_denom = 1;
           #endif
          
		  /**
		   **this rect is the app call RenderTo rect size
		   **/
		  jpeg_calc_output_dimensions( &cinfo );
          if (cinfo.output_width == (unsigned)rect.w && cinfo.output_height == (unsigned)rect.h) 
		  {
		  	   direct = true;
          }
          else if (rect.x == 0 && rect.y == 0)
		  {
				#if 0
	               /*  The supported scaling ratios in libjpeg 7 and 8
	                *  are N/8 with all N from 1 to 16.
	                */
	               cinfo.scale_num = 1;
	               jpeg_calc_output_dimensions( &cinfo );
	               while (cinfo.scale_num < 16
	                      && cinfo.output_width < (unsigned)rect.w
	                      && cinfo.output_height < (unsigned)rect.h) 
	               {
	                    ++cinfo.scale_num;
	                    jpeg_calc_output_dimensions( &cinfo );
	               }
			   #else
	               /*  The supported scaling ratios in libjpeg 6
	                *  are 1/1, 1/2, 1/4, and 1/8.
	                */
	               if( (stJpegInfo.u32Width[0] / rect.w ) > 8)
	               {
	               	  s32WScale = 8;
	               }
				   else if( (stJpegInfo.u32Width[0] / rect.w ) > 4)
				   {
				   	   s32WScale = 4;
				   }
				   else if( (stJpegInfo.u32Width[0] / rect.w ) > 2)
				   {
				   	   s32WScale = 2;
				   }
				   else
				   {
				   	    s32WScale = 1;
				   }
	               if( (stJpegInfo.u32Height[0] / rect.h ) > 8)
	               {
	               	  s32HScale = 8;
	               }
				   else if( (stJpegInfo.u32Height[0] / rect.h ) > 4)
				   {
				   	   s32HScale = 4;
				   }
				   else if( (stJpegInfo.u32Height[0] / rect.h ) > 2)
				   {
				   	   s32HScale = 2;
				   }
				   else
				   {
				   	    s32HScale = 1;
				   }
				   cinfo.scale_denom = (s32WScale > s32HScale)? s32WScale : s32HScale;
			   #endif
          }

          switch (dst_surface->config.format) 
		  {
               case DSPF_NV16:
                    uv_offset = dst_surface->config.size.h * lock.pitch;
					cinfo.output_components = 3;
                    if (direct && !rect.x && !rect.y)
					{
                         D_INFO( "JPEG: Using YCbCr color space directly! (%dx%d)\n",cinfo.output_width, cinfo.output_height );
                         cinfo.out_color_space = JCS_YCbCr;
                         break;
                    }
                    D_INFO( "JPEG: Going through RGB color space! (%dx%d -> %dx%d @%d,%d)\n",cinfo.output_width, cinfo.output_height, rect.w, rect.h, rect.x, rect.y );
                    cinfo.out_color_space = JCS_RGB;
                    break;

               case DSPF_UYVY:
			   		cinfo.output_components = 3;
                    if (direct && !rect.x && !rect.y) 
					{
                         cinfo.out_color_space = JCS_YCbCr;
                         break;
                    }
                    D_INFO( "JPEG: Going through RGB color space! (%dx%d -> %dx%d @%d,%d)\n",cinfo.output_width, cinfo.output_height, rect.w, rect.h, rect.x, rect.y );
                    cinfo.out_color_space = JCS_RGB;
                    break;
               default:
			   		cinfo.output_components = 4;
                    cinfo.out_color_space = JCS_ABGR_8888;
                    break;
          }

          if (data->flags & DIRENDER_FAST)
          {
               cinfo.dct_method = JDCT_IFAST;
          }

	   	  stJpegInfo.bOutInfo = HI_TRUE;
		  HI_JPEG_GetJpegInfo(&cinfo,&stJpegInfo);

		  data->image_width  = stJpegInfo.u32Width[0];
          data->image_height = stJpegInfo.u32Height[0];
		  row_stride  = data->image_width * cinfo.output_components;
		  
		  data->image = D_CALLOC(data->image_height, row_stride);
          if (!data->image) 
		  {
               dfb_surface_unlock_buffer( dst_surface, &lock );
               return D_OOM();
          }

		  if(DSPF_NV16 == dst_surface->config.format || DSPF_UYVY == dst_surface->config.format)
		  {
		  		buffer = (*cinfo.mem->alloc_sarray)( (j_common_ptr) &cinfo,JPOOL_IMAGE, row_stride, 1);
		  }
		  else
		  {
		  	 stSurfaceDesc.stOutSurface.pOutVir[0] = (HI_CHAR*)data->image;
			 stSurfaceDesc.stOutSurface.u32OutStride[0] = row_stride;
			 stSurfaceDesc.stOutSurface.bUserPhyMem = HI_FALSE;
			 HI_JPEG_SetOutDesc(&cinfo, &stSurfaceDesc);
		  }
		  row_ptr = data->image;

		  pLeaveBuf = (HI_CHAR*)calloc(1,JPEG_PROG_BUF_SIZE * sizeof (JOCTET));
		  if(NULL==pLeaveBuf)
		  {
			  return DFB_FAILURE;
		  }
		  duplicate_stream_info(&cinfo);
		  record_readbytes_before_stardecompress(0,HI_TRUE,HI_FALSE);
		  bRet = jpeg_start_decompress( &cinfo );
		  if(HI_FALSE==bRet)
		  {
			  resume_stream(&cinfo);
			  bRet = jpeg_start_decompress(&cinfo);
		  }
		  record_readbytes_before_stardecompress(0,HI_FALSE,HI_TRUE);
		  if(NULL != pLeaveBuf)
		  {
	  		 free(pLeaveBuf);
			 pLeaveBuf = NULL;
			 gs_s32LeaveByte = 0;
			 gs_s32Readbytes = 0;
		  }
	      if(HI_FALSE==bRet)
		  {
			 jpeg_destroy_decompress( &cinfo );
			 return DFB_FAILURE;
		  }
		  
		  while (cinfo.output_scanline < cinfo.output_height && cb_result == DIRCR_OK) 
		  {
               switch (dst_surface->config.format) 
			   {
                    case DSPF_NV16:
                    case DSPF_UYVY:
						 jpeg_read_scanlines( &cinfo, buffer, 1 );
                         if (direct) 
						 {
                              switch (dst_surface->config.format) 
							  {
                                   case DSPF_NV16:
                                        copy_line_nv16( lock.addr, (u16*)lock.addr + uv_offset, *buffer, rect.w );
                                        break;
                                   case DSPF_UYVY:
                                        copy_line_uyvy( lock.addr, *buffer, rect.w );
                                        break;
                                   default:
                                        break;
                              }
                              lock.addr = (u8*)lock.addr + lock.pitch;
                              if (data->base.render_callback)
							  {
                                   DFBRectangle r = { 0, y, data->image_width, 1 };
                                   cb_result = data->base.render_callback( &r,data->base.render_callback_context );
                              }
							  y++;
                              break;
                         }
                    default:
						 bRet = jpeg_read_scanlines(&cinfo, NULL, 1);
						 if(HI_FALSE==bRet)
						 {
							 jpeg_destroy_decompress( &cinfo );
							 return DFB_FAILURE;
						  }
                         if(direct) 
						 {
						 	  DFBRectangle r = { rect.x, rect.y+y, rect.w, 1 };
                              dfb_copy_buffer_32(row_ptr, lock.addr, lock.pitch,&r, dst_surface, &clip);
                              if (data->base.render_callback) 
							  {
							  	   r = (DFBRectangle){ 0, y, data->image_width, 1 };
                                   cb_result = data->base.render_callback(&r,data->base.render_callback_context );
                              }
							  row_ptr += data->image_width;
							  y++;
                         }
                         break;
               }
			   
          }

          if (!direct) 
		  {
               dfb_scale_linear_32( data->image, data->image_width, data->image_height,lock.addr, lock.pitch, &rect, dst_surface, &clip );
               if (data->base.render_callback) 
			   {
                    DFBRectangle r = { 0, 0, data->image_width, data->image_height };
                    cb_result = data->base.render_callback( &r,data->base.render_callback_context );
               }
          }

          if (cb_result != DIRCR_OK) 
		  {
               jpeg_abort_decompress( &cinfo );
               D_FREE( data->image );
               data->image = NULL;
          }
          else 
		  {
               jpeg_finish_decompress( &cinfo );
          }
          jpeg_destroy_decompress( &cinfo );
		  
     }
     else 
	 {
          dfb_scale_linear_32( data->image, data->image_width, data->image_height,
                               lock.addr, lock.pitch, &rect, dst_surface, &clip );
          if (data->base.render_callback) 
		  {
               DFBRectangle r = { 0, 0, data->image_width, data->image_height };
               data->base.render_callback( &r,data->base.render_callback_context );
          }
     }

     dfb_surface_unlock_buffer( dst_surface, &lock );

     if (cb_result != DIRCR_OK)
     {
          return DFB_INTERRUPTED;
     }
	 
     return DFB_OK;
	 
}

static DFBResult
IDirectFBImageProvider_JPEG_GetSurfaceDescription( IDirectFBImageProvider *thiz,
                                                   DFBSurfaceDescription  *dsc )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBImageProvider_JPEG)

     if (!dsc)
          return DFB_INVARG;

     dsc->flags  = DSDESC_WIDTH |  DSDESC_HEIGHT | DSDESC_PIXELFORMAT;
     dsc->height = data->height;
     dsc->width  = data->width;
     dsc->pixelformat = dfb_primary_layer_pixelformat();

     return DFB_OK;
}
static DFBResult
IDirectFBImageProvider_JPEG_SetRenderFlags( IDirectFBImageProvider *thiz,
                                                   DIRenderFlags flags )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBImageProvider_JPEG)

     data->flags = flags;

     return DFB_OK;
}

static DFBResult
IDirectFBImageProvider_JPEG_GetImageDescription( IDirectFBImageProvider *thiz,
                                                 DFBImageDescription    *dsc )
{
     DIRECT_INTERFACE_GET_DATA(IDirectFBImageProvider_JPEG)

     if (!dsc)
          return DFB_INVARG;

     dsc->caps = DICAPS_NONE;

     return DFB_OK;
}
