/*
 * jdapistd.c
 *
 * Copyright (C) 1994-1996, Thomas G. Lane.
 * Modified 2002-2013 by Guido Vollbeding.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains application interface code for the decompression half
 * of the JPEG library.  These are the "standard" API routines that are
 * used in the normal full-decompression case.  They are not used by a
 * transcoding-only application.  Note that if an application links in
 * jpeg_start_decompress, it will end up linking in the entire decompressor.
 * We thus must separate this file from jdapimin.c to avoid linking the
 * whole decompression library into a transcoder.
 */

#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"


#include "jdatasrc.h"
#include "hi_jpeg_config.h"
#include "hi_jpeg_api.h"
/**
 ** add the include file about the functions that hard decode needed
 ** CNcomment: ����Ӳ��������Ҫ��ͷ�ļ� CNend\n
 **/
#include "jpeg_hdec_api.h"

#if defined(CONFIG_JPEG_ANDROID_DEBUG_ENABLE) && defined(CONFIG_JPEG_DEBUG_INFO)
	#define LOG_TAG "libjpeg"
#endif




/* Forward declarations */
LOCAL(boolean) output_pass_setup JPP((j_decompress_ptr cinfo));


/**
 ** the soft decode move from jpeg_start_decompress,now jpeg_start_decompress
 ** have two decode type, hard decode and soft decode
 ** CNcomment: ԭ��jpeg_start_decompress������������̣����ڽ�������
 **            ����һ������ʵ�� CNend\n
 **/
#ifndef CONFIG_JPEG_ADD_SRC_FUNCTION
static HI_BOOL jpeg_seek_input_data(j_decompress_ptr cinfo, long byte_offset)
{

	 int ret = 0;
	 my_src_ptr src = (my_src_ptr) cinfo->src;
	 
	 ret = fseek(src->infile,byte_offset,SEEK_SET);
	 if(0 != ret)
	 {
		 ERREXIT(cinfo, JERR_STREAM_BACK_FAILURE);
	 }
	 
	 src->pub.next_input_byte = src->buffer;
	 src->pub.bytes_in_buffer = 0;
	   
	 return HI_TRUE;
	
}
#endif

static HI_BOOL jpeg_start_hard_decompress(j_decompress_ptr cinfo)
{

		HI_S32 s32RetVal = HI_SUCCESS;
		/**
		 ** check the hard decode whether support
		 ** CNcomment:�ж�Ӳ�������Ƿ�֧�� CNend\n
		 **/
		s32RetVal =  JPEG_HDEC_IfSupport(cinfo);
		if(HI_SUCCESS != s32RetVal)
		{
			return HI_FALSE;
		}
		/**
		 ** open some device that decode need
		 ** CNcomment:�򿪽�����Ҫ��һЩ�豸 CNend\n
		 **/
		s32RetVal = JPEG_HDEC_OpenDev(cinfo);
		if(HI_SUCCESS != s32RetVal)
		{
			return HI_FALSE;
		}
#if 0
		/** ����ʹ���������ˣ����ԾͲ���ʹ�õ������ַ�ʽ�� **/
		s32RetVal = JPEG_HDEC_DuplicateStreamInfo(cinfo);
		if(HI_SUCCESS != s32RetVal)
		{
			return HI_FALSE;
		}
#endif

		s32RetVal = JPEG_HDEC_Start(cinfo);
		if(HI_SUCCESS != s32RetVal)
		{
			#if 0
		    JPEG_HDEC_ResumeStreamInfo(cinfo);
			#endif
			return HI_FALSE;
		}

		return HI_TRUE;
		
		
}


/*
 * Decompression initialization.
 * jpeg_read_header must be completed before calling this.
 *
 * If a multipass operating mode was selected, this will do all but the
 * last pass, and thus may take a great deal of time.
 *
 * Returns FALSE if suspended.  The return value need be inspected only if
 * a suspending data source is used.
 */
static HI_BOOL jpeg_start_soft_decompress(j_decompress_ptr cinfo)
{
  if (cinfo->global_state == DSTATE_READY) {
    /* First call: initialize master control, select active modules */
    jinit_master_decompress(cinfo);
    if (cinfo->buffered_image) {
      /* No more work here; expecting jpeg_start_output next */
      cinfo->global_state = DSTATE_BUFIMAGE;
      return TRUE;
    }
    cinfo->global_state = DSTATE_PRELOAD;
  }
  if (cinfo->global_state == DSTATE_PRELOAD) {
    /* If file has multiple scans, absorb them all into the coef buffer */
    if (cinfo->inputctl->has_multiple_scans) {
#ifdef D_MULTISCAN_FILES_SUPPORTED
      for (;;) {
	int retcode;
	/* Call progress monitor hook if present */
	if (cinfo->progress != NULL)
	  (*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
	/* Absorb some more input */
	retcode = (*cinfo->inputctl->consume_input) (cinfo);
	if (retcode == JPEG_SUSPENDED)
	  return FALSE;
	if (retcode == JPEG_REACHED_EOI)
	  break;
	/* Advance progress counter if appropriate */
	if (cinfo->progress != NULL &&
	    (retcode == JPEG_ROW_COMPLETED || retcode == JPEG_REACHED_SOS)) {
	  if (++cinfo->progress->pass_counter >= cinfo->progress->pass_limit) {
	    /* jdmaster underestimated number of scans; ratchet up one scan */
	    cinfo->progress->pass_limit += (long) cinfo->total_iMCU_rows;
	  }
	}
      }
#else
      ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif /* D_MULTISCAN_FILES_SUPPORTED */
    }
    cinfo->output_scan_number = cinfo->input_scan_number;
  } else if (cinfo->global_state != DSTATE_PRESCAN)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  /* Perform any dummy output passes, and set up for the final pass */
  return output_pass_setup(cinfo);
}


GLOBAL(boolean)
jpeg_start_decompress (j_decompress_ptr cinfo)
{

        HI_BOOL bRet = HI_FALSE;
        
		HI_S32 s32BeforeStartHardDecState = 0;

        JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		s32BeforeStartHardDecState = cinfo->global_state;


        if(HI_TRUE == pJpegHandle->bFirstDec)
        {
			if(DSTATE_READY == s32BeforeStartHardDecState)
			{
			    bRet = jpeg_start_hard_decompress(cinfo);
			}
			if(HI_TRUE == bRet)
			{ 
				#ifdef CONFIG_JPEG_OUTPUT_NEED_OS_MEMSIZE
				JPEG_TRACE("the need os memory size is %lfM\n",(pJpegHandle->u32NeedMemSize/1024.0)/1024.0);
				#endif
	            return TRUE;
			}
		   /** 
		    ** if hard decode failure, to beging soft decode and the golbal_state 
	        ** should return the state that before hard decode,because the start_decompress
	        ** should use the golbal state.
	        **/
	        cinfo->global_state = s32BeforeStartHardDecState;

		    #ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
				if( (HI_TRUE == pJpegHandle->bInHardDec) && (NULL != cinfo->src->seek_input_data) )
				{/** ����ǽ���Ӳ�����룬��Ӳ��Ӳ������ʧ�ܣ��������������½���������� **/
				   	cinfo->src->seek_input_data(cinfo, pJpegHandle->u32CurrentOffset);
				}
				else if((HI_FALSE == pJpegHandle->stHDecDataBuf.bUseInsideData)&&(HI_TRUE == pJpegHandle->bInHardDec))
				{
					 pJpegHandle->bFirstDec = HI_FALSE;
					 return HI_FALSE;
				}
				else if((HI_TRUE == pJpegHandle->stHDecDataBuf.bUseFileData) && (HI_TRUE == pJpegHandle->bInHardDec))
				{/** ֻ�ж��ļ�����Ҫ�������� **/
				 	jpeg_seek_input_data(cinfo, pJpegHandle->u32CurrentOffset);
				}
				else
				{
					/**nothing to do**/
				}
			#else
				if((HI_FALSE == pJpegHandle->stHDecDataBuf.bUseInsideData)&&(HI_TRUE == pJpegHandle->bInHardDec))
				{/**
		   		  ** when use external stream,if hard decode failure,user should resume the stream,and call this function again
		          ** CNcomment: �����ʹ���ⲿ������������ֱ�ӷ���ʧ�ܣ�Ȼ���û���������֮�����µ��øýӿڽ������ CNend\n
		          **/
		            pJpegHandle->bFirstDec = HI_FALSE;
		            return HI_FALSE;
				}
				#ifdef CONFIG_JPEG_ADD_SRC_FUNCTION
					if((HI_TRUE == pJpegHandle->stHDecDataBuf.bUseFileData) && (NULL != cinfo->src->seek_input_data) && (HI_TRUE == pJpegHandle->bInHardDec))
					{/** ֻ�ж��ļ�����Ҫ�������� **/
					 	cinfo->src->seek_input_data(cinfo, pJpegHandle->u32CurrentOffset);
					}
				#else
                    if((HI_TRUE == pJpegHandle->stHDecDataBuf.bUseFileData) && (HI_TRUE == pJpegHandle->bInHardDec))
					{/** ֻ�ж��ļ�����Ҫ�������� **/
					 	jpeg_seek_input_data(cinfo, pJpegHandle->u32CurrentOffset);
					}
				#endif
			#endif
			
        }

#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_TEST_CHIP_RANDOM_RESET)
		if(HI_FALSE == pJpegHandle->bHdecEnd)
		{
			JPEG_TRACE("===============================================================\n");
			JPEG_TRACE("test random reset, hard dec failure!\n");
			JPEG_TRACE("===============================================================\n");
			ERREXIT(cinfo, JERR_HDEC_INIT_FAILURE);
		}
#endif
		/**as follows is soft decode dispose
		 **CNcomment: ������������̴��� CNend\n
		 **/
        bRet = jpeg_start_soft_decompress(cinfo);

#ifdef CONFIG_JPEG_OUTPUT_NEED_OS_MEMSIZE
		JPEG_TRACE("the need os memory size is %lfM\n",(pJpegHandle->u32NeedMemSize/1024.0)/1024.0);
#endif		
        return bRet;
	
}

/*
 * Set up for an output pass, and perform any dummy pass(es) needed.
 * Common subroutine for jpeg_start_decompress and jpeg_start_output.
 * Entry: global_state = DSTATE_PRESCAN only if previously suspended.
 * Exit: If done, returns TRUE and sets global_state for proper output mode.
 *       If suspended, returns FALSE and sets global_state = DSTATE_PRESCAN.
 */

LOCAL(boolean)
output_pass_setup (j_decompress_ptr cinfo)
{
  if (cinfo->global_state != DSTATE_PRESCAN) {
    /* First call: do pass setup */
    (*cinfo->master->prepare_for_output_pass) (cinfo);
    cinfo->output_scanline = 0;
    cinfo->global_state = DSTATE_PRESCAN;
  }
  /* Loop over any required dummy passes */
  while (cinfo->master->is_dummy_pass) {
#ifdef QUANT_2PASS_SUPPORTED
    /* Crank through the dummy pass */
    while (cinfo->output_scanline < cinfo->output_height) {
      JDIMENSION last_scanline;
      /* Call progress monitor hook if present */
      if (cinfo->progress != NULL) {
	cinfo->progress->pass_counter = (long) cinfo->output_scanline;
	cinfo->progress->pass_limit = (long) cinfo->output_height;
	(*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
      }
      /* Process some data */
      last_scanline = cinfo->output_scanline;
      (*cinfo->main->process_data) (cinfo, (JSAMPARRAY) NULL,
				    &cinfo->output_scanline, (JDIMENSION) 0);
      if (cinfo->output_scanline == last_scanline)
	return FALSE;		/* No progress made, must suspend */
    }
    /* Finish up dummy pass, and set up for another one */
    (*cinfo->master->finish_output_pass) (cinfo);
    (*cinfo->master->prepare_for_output_pass) (cinfo);
    cinfo->output_scanline = 0;
#else
    ERREXIT(cinfo, JERR_NOT_COMPILED);
#endif /* QUANT_2PASS_SUPPORTED */
  }
  /* Ready for application to drive output pass through
   * jpeg_read_scanlines or jpeg_read_raw_data.
   */
  cinfo->global_state = cinfo->raw_data_out ? DSTATE_RAW_OK : DSTATE_SCANNING;
  return TRUE;
}


/*
 * Read some scanlines of data from the JPEG decompressor.
 *
 * The return value will be the number of lines actually read.
 * This may be less than the number requested in several cases,
 * including bottom of image, data source suspension, and operating
 * modes that emit multiple scanlines at a time.
 *
 * Note: we warn about excess calls to jpeg_read_scanlines() since
 * this likely signals an application programmer error.  However,
 * an oversize buffer (max_lines > scanlines remaining) is not an error.
 */

static HI_U32 jpeg_soft_read_scanlines(j_decompress_ptr cinfo, 
                                                   JSAMPARRAY scanlines,
		                                           JDIMENSION max_lines)
{
  JDIMENSION row_ctr;

  if (cinfo->global_state != DSTATE_SCANNING)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  if (cinfo->output_scanline >= cinfo->output_height) {
    WARNMS(cinfo, JWRN_TOO_MUCH_DATA);
    return 0;
  }

  /* Call progress monitor hook if present */
  if (cinfo->progress != NULL) {
    cinfo->progress->pass_counter = (long) cinfo->output_scanline;
    cinfo->progress->pass_limit = (long) cinfo->output_height;
    (*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
  }

  /* Process some data */
  row_ctr = 0;
  (*cinfo->main->process_data) (cinfo, scanlines, &row_ctr, max_lines);
  cinfo->output_scanline += row_ctr;
  return row_ctr;
}


static HI_U32 jpeg_hard_read_scanlines(j_decompress_ptr cinfo, 
                                                   JSAMPARRAY scanlines,
		                                           JDIMENSION max_lines)
{
       HI_S32 row_ctr = 0;
	   row_ctr = JPEG_HDEC_HardCSC(cinfo);
	   if(HI_SUCCESS != row_ctr)
	   {/**
		 ** because the jpeg hard dec success,so the csc must success
		 ** CNcomment:Ӳ������ɹ�������Ӳ��ת��Ҳ����ɹ� CNend\n
		 **/
          ERREXIT(cinfo, JERR_HARD_CSC_FAILURE);
	   }
       if(NULL != scanlines)
       {
	      row_ctr = JPEG_HDEC_OutUserBuf(cinfo, max_lines,(HI_CHAR*)scanlines[0]);
       }
       else
       {
          row_ctr = JPEG_HDEC_OutUserBuf(cinfo, max_lines,NULL);
       }
	   return (HI_U32)row_ctr;

}


GLOBAL(JDIMENSION)
jpeg_read_scanlines (j_decompress_ptr cinfo, JSAMPARRAY scanlines,
		     JDIMENSION max_lines)
{

	HI_U32 row_ctr = 0;
	JPEG_HDEC_HANDLE_S_PTR	 pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	if(HI_TRUE == pJpegHandle->bHdecEnd)
	{
	   row_ctr = jpeg_hard_read_scanlines(cinfo,scanlines,max_lines);
	}
	else
	{
		row_ctr = jpeg_soft_read_scanlines(cinfo,scanlines,max_lines);
	}

	return row_ctr;

}


/*
 * Alternate entry point to read raw data.
 * Processes exactly one iMCU row per call, unless suspended.
 */

GLOBAL(JDIMENSION)
jpeg_read_raw_data (j_decompress_ptr cinfo, JSAMPIMAGE data,
		    JDIMENSION max_lines)
{
  JDIMENSION lines_per_iMCU_row;

  if (cinfo->global_state != DSTATE_RAW_OK)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  if (cinfo->output_scanline >= cinfo->output_height) {
    WARNMS(cinfo, JWRN_TOO_MUCH_DATA);
    return 0;
  }

  /* Call progress monitor hook if present */
  if (cinfo->progress != NULL) {
    cinfo->progress->pass_counter = (long) cinfo->output_scanline;
    cinfo->progress->pass_limit = (long) cinfo->output_height;
    (*cinfo->progress->progress_monitor) ((j_common_ptr) cinfo);
  }

  /* Verify that at least one iMCU row can be returned. */
  lines_per_iMCU_row = cinfo->max_v_samp_factor * cinfo->min_DCT_v_scaled_size;
  if (max_lines < lines_per_iMCU_row)
    ERREXIT(cinfo, JERR_BUFFER_SIZE);

  /* Decompress directly into user's buffer. */
  if (! (*cinfo->coef->decompress_data) (cinfo, data))
    return 0;			/* suspension forced, can do nothing more */

  /* OK, we processed one iMCU row. */
  cinfo->output_scanline += lines_per_iMCU_row;
  return lines_per_iMCU_row;
}


/* Additional entry points for buffered-image mode. */

#ifdef D_MULTISCAN_FILES_SUPPORTED

/*
 * Initialize for an output pass in buffered-image mode.
 */

GLOBAL(boolean)
jpeg_start_output (j_decompress_ptr cinfo, int scan_number)
{
  if (cinfo->global_state != DSTATE_BUFIMAGE &&
      cinfo->global_state != DSTATE_PRESCAN)
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  /* Limit scan number to valid range */
  if (scan_number <= 0)
    scan_number = 1;
  if (cinfo->inputctl->eoi_reached &&
      scan_number > cinfo->input_scan_number)
    scan_number = cinfo->input_scan_number;
  cinfo->output_scan_number = scan_number;
  /* Perform any dummy output passes, and set up for the real pass */
  return output_pass_setup(cinfo);
}


/*
 * Finish up after an output pass in buffered-image mode.
 *
 * Returns FALSE if suspended.  The return value need be inspected only if
 * a suspending data source is used.
 */

GLOBAL(boolean)
jpeg_finish_output (j_decompress_ptr cinfo)
{
  if ((cinfo->global_state == DSTATE_SCANNING ||
       cinfo->global_state == DSTATE_RAW_OK) && cinfo->buffered_image) {
    /* Terminate this pass. */
    /* We do not require the whole pass to have been completed. */
    (*cinfo->master->finish_output_pass) (cinfo);
    cinfo->global_state = DSTATE_BUFPOST;
  } else if (cinfo->global_state != DSTATE_BUFPOST) {
    /* BUFPOST = repeat call after a suspension, anything else is error */
    ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
  }
  /* Read markers looking for SOS or EOI */
  while (cinfo->input_scan_number <= cinfo->output_scan_number &&
	 ! cinfo->inputctl->eoi_reached) {
    if ((*cinfo->inputctl->consume_input) (cinfo) == JPEG_SUSPENDED)
      return FALSE;		/* Suspend, come back later */
  }
  cinfo->global_state = DSTATE_BUFIMAGE;
  return TRUE;
}

#endif /* D_MULTISCAN_FILES_SUPPORTED */
