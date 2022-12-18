/*=================================================

Open MAX   Component: Video Decoder
This module contains the class definition for openMAX decoder component.
File:    omx_allocator.h
Author:  yangyichang 00226912
Date:    16, 03, 2013.

=================================================*/

#ifndef __OMX_ALLOCATOR_H__
#define	__OMX_ALLOCATOR_H__

#include "drv_omxvdec.h"
#include "OMX_Types.h"

#ifdef HI_TVP_SUPPORT
OMX_S32 alloc_contigous_buffer_secure(OMX_U32 buf_num, OMX_U32 buf_size, OMX_U32 align, OMXVDEC_BUF_DESC *pvdec_buf);
void free_contigous_buffer_secure(OMXVDEC_BUF_DESC *puser_buf);
#else
OMX_S32 alloc_contigous_buffer(OMX_U32 buf_num, OMX_U32 buf_size, OMX_U32 align, OMXVDEC_BUF_DESC *pvdec_buf);
void free_contigous_buffer(OMXVDEC_BUF_DESC *puser_buf);
#endif 

#endif
