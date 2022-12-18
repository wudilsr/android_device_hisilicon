/*=================================================

Open MAX   Component: Video Decoder
This module contains the class definition for openMAX decoder component.
File:    omx_allocator.c
Author:  yangyichang 00226912
Date:    16, 03, 2013.

=================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "omx_dbg.h"
#include "omx_allocator.h"

#ifdef HI_TVP_SUPPORT
#include "tee_client_api.h" 
#endif


#ifdef HI_TVP_SUPPORT
OMX_S32 alloc_contigous_buffer_secure(OMX_U32 buf_num, OMX_U32 buf_size, OMX_U32 align, OMXVDEC_BUF_DESC *pvdec_buf)
{ 
	OMX_S16 ret = -1;
    HI_U32  u32SecPhyAddr = 0;
    HI_CHAR SecBufName[20];
    OMXVDEC_BUF_DESC *puser_buf = pvdec_buf;

	if (NULL == puser_buf)
	{
		DEBUG_PRINT_ERROR("%s invalid param\n", __func__);
		return -1;
	}

	buf_size = (buf_size + align - 1) & ~(align - 1);
	buf_size += 0x40;

    if (0 == puser_buf->dir)
    {
        snprintf(SecBufName, sizeof(SecBufName), "SEC_OMXVDEC_IN%ld", buf_num);
    }
    else
    {
        snprintf(SecBufName, sizeof(SecBufName), "SEC_OMXVDEC_OUT%ld", buf_num);
    }

	u32SecPhyAddr = HI_SEC_MMZ_New(buf_size, OMXVDEC_SEC_ZONE, SecBufName);
	if(0 == u32SecPhyAddr)
    {
        DEBUG_PRINT_ERROR("%s mmz alloc secure buffer error!\n", __func__);
        return -1;
	}

    puser_buf->bufferaddr   = (HI_VOID *)u32SecPhyAddr;
    puser_buf->phyaddr      = u32SecPhyAddr;
    puser_buf->buffer_len   = buf_size;
    puser_buf->data_len     = 0;
    puser_buf->data_offset  = 0;
    puser_buf->timestamp    = 0;
    
    DEBUG_PRINT_ALWS("Alloc secure buffer %s, phy 0x%x, size %d success!\n", SecBufName, u32SecPhyAddr, buf_size);

	return 0;
}

void free_contigous_buffer_secure(OMXVDEC_BUF_DESC *puser_buf)
{
    HI_S32 ret;
    
	if (NULL == puser_buf)
	{
		DEBUG_PRINT_ERROR("%s invalid param\n", __func__);
		return;
	}

    ret = HI_SEC_MMZ_Delete(puser_buf->phyaddr); 
    if (ret != HI_SUCCESS)
    {
		DEBUG_PRINT_ERROR("%s free secure buffer 0x%x failed.\n", __func__, puser_buf->phyaddr);
	}

    DEBUG_PRINT_ALWS("Free secure dir %d buffer 0x%x success!\n", puser_buf->dir, puser_buf->phyaddr);

	return;
}

#else

OMX_S32 alloc_contigous_buffer(OMX_U32 buf_num, OMX_U32 buf_size, OMX_U32 align, OMXVDEC_BUF_DESC *pvdec_buf)
{
	OMX_S16 ret = -1;
	HI_MMZ_BUF_S buffer;
    OMXVDEC_BUF_DESC *puser_buf = pvdec_buf;

	if (NULL == puser_buf)
	{
		DEBUG_PRINT_ERROR("%s invalid param\n", __func__);
		return -1;
	}

	buf_size = (buf_size + align - 1) & ~(align - 1);
	buf_size += 0x40;
	buffer.bufsize = buf_size;
    if (0 == puser_buf->dir)
    {
        snprintf(buffer.bufname, sizeof(buffer.bufname), "OMXVDEC_IN%ld", buf_num);
    }
    else
    {
        snprintf(buffer.bufname, sizeof(buffer.bufname), "OMXVDEC_OUT%ld", buf_num);
    }

	ret = HI_MMZ_Malloc(&buffer);
	if(ret < 0)
    {
        DEBUG_PRINT_ERROR("%s mmz alloc error!\n", __func__);
        return -1;
	}

    puser_buf->bufferaddr   = buffer.user_viraddr;
    puser_buf->phyaddr      = buffer.phyaddr;
    puser_buf->buffer_len   = buf_size;
    puser_buf->data_len     = 0;
    puser_buf->data_offset  = 0;
    puser_buf->timestamp    = 0;
    
	return 0;
}

void free_contigous_buffer(OMXVDEC_BUF_DESC *puser_buf)
{
    HI_S32 ret;
	HI_MMZ_BUF_S buffer;
    
	if (NULL == puser_buf)
	{
		DEBUG_PRINT_ERROR("%s invalid param\n", __func__);
		return;
	}

    buffer.phyaddr = puser_buf->phyaddr;
    buffer.user_viraddr = puser_buf->bufferaddr;
    
	ret = HI_MMZ_Free(&buffer);
    if (ret != HI_SUCCESS)
    {
		DEBUG_PRINT_ERROR("%s free 0x%x failed.\n", __func__, puser_buf->phyaddr);
	}

	return;
}
#endif


