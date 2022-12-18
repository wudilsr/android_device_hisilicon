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
#include "omx_dbg.h"

#ifdef HI_TVP_SUPPORT
#define OMXVDEC_SEC_ZONE                "SEC-MMZ"

OMX_S32 alloc_contigous_buffer_secure(OMX_U32 buf_num, OMX_U32 buf_size, OMX_U32 align, OMXVDEC_BUF_DESC *pvdec_buf);
void free_contigous_buffer_secure(OMXVDEC_BUF_DESC *puser_buf);
#ifdef DEBUG_SAVE_YUV 
OMX_S32 yuv_secure_mem_exchange(OMX_U32 pSrcPhyAddr, HI_MMZ_BUF_S *pBuffer);
HI_VOID yuv_exchange_mem_free(HI_MMZ_BUF_S *pBuffer);
#endif
#else
OMX_S32 alloc_contigous_buffer(OMX_U32 buf_num, OMX_U32 buf_size, OMX_U32 align, OMXVDEC_BUF_DESC *pvdec_buf);
void free_contigous_buffer(OMXVDEC_BUF_DESC *puser_buf);
#endif 

#endif
