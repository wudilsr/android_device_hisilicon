/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_henc_api.c
Version		    : Initial Draft
Author		    : y00181162
Created		    : 2014/05/14
Description	    :
Function List 	:

			  		  
History       	:
Date				Author        		Modification
2014/05/14		    y00181162		    Created file      	
******************************************************************************/

/*********************************add include here******************************/

#ifdef CONFIG_GFX_JPGE_ENC_ENABLE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/types.h>


#include "jpeglib.h"
#include "jdatadst.h"
#include "jerror.h"

#include "hi_jpeg_config.h"
#include "jpeg_hdec_csc.h"
#include "jpeg_hdec_mem.h"
#include "jpge_henc_api.h"
#include "jpge_henc_err.h"

#include "drv_jpge_ioctl.h"


/***************************** Macro Definition ******************************/
#define JPGE_DEV 			              "/dev/hi_jpge"

//#define CONFIG_JPGE_SAVE_SRCDATA

#ifdef CONFIG_JPGE_SAVE_SRCDATA
#define SRCDATA_DIR                      "./../res/save-src/"
#endif
/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

/******************************* API forward declarations *******************/


/******************************* API realization *****************************/


/*****************************************************************************
* func			: JPGE_HENC_SetEncColorSpace
* description	: ���ñ���������ɫ�ռ��ʽ
				  CNcomment:    CNend\n
* param[in] 	: cinfo 	      CNcomment: �������	CNend\n
* param[in] 	: s32ColorType 	  CNcomment: ����������ɫ�ռ�	CNend\n
* others:		: NA
*****************************************************************************/
static HI_VOID JPGE_HENC_SetEncColorSpace(j_compress_ptr cinfo,HI_S32 s32ColorType)
{
	JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);
	switch(s32ColorType)
	{
		case JPGE_YUV444:
			pJpgeHandle->EncCfg.YuvSampleType = JPGE_YUV444;
			pJpgeHandle->EncCfg.YuvStoreType  = JPGE_PACKAGE;
			pJpgeHandle->bCanUserPhyMem       = HI_FALSE;/** ��Ϊ������Ҫ���ţ����Բ���ֱ��ʹ���û������ڴ� **/
			if(HI_FALSE == pJpgeHandle->bHasSetStreamInfo)
			{
				pJpgeHandle->stStreamInfo.u32InStride[0] = (cinfo->image_width * 3 + 16 - 1) & (~(16 - 1));
				pJpgeHandle->stStreamInfo.u32InSize[0]   = pJpgeHandle->stStreamInfo.u32InStride[0] * cinfo->image_height;
			}
			pJpgeHandle->stStreamInfo.u32InStride[1] = 0;
			pJpgeHandle->stStreamInfo.u32InSize[1]   = 0;
			pJpgeHandle->stStreamInfo.u32InStride[2] = 0;
			pJpgeHandle->stStreamInfo.u32InSize[2]   = 0;
			break;
		case JPGE_YUV422:
			pJpgeHandle->EncCfg.YuvSampleType = JPGE_YUV422;
			pJpgeHandle->EncCfg.YuvStoreType  = JPGE_PACKAGE;
			pJpgeHandle->bCanUserPhyMem       = HI_TRUE;
			if(HI_FALSE == pJpgeHandle->bHasSetStreamInfo)
			{
				pJpgeHandle->stStreamInfo.u32InStride[0] = (cinfo->image_width * 2 + 16 - 1) & (~(16 - 1));
				pJpgeHandle->stStreamInfo.u32InSize[0]   = pJpgeHandle->stStreamInfo.u32InStride[0] * cinfo->image_height;
			}
			pJpgeHandle->stStreamInfo.u32InStride[1] = 0;
			pJpgeHandle->stStreamInfo.u32InSize[1]   = 0;
			pJpgeHandle->stStreamInfo.u32InStride[2] = 0;
			pJpgeHandle->stStreamInfo.u32InSize[2]   = 0;
			break;
		case JPGE_YUV420:
			if(HI_FALSE == pJpgeHandle->bHasSetStreamInfo && HI_FALSE == pJpgeHandle->bEncMCU)
			{
			    pJpgeHandle->bEncSupport      = HI_FALSE;
			}
			else if(HI_FALSE == pJpgeHandle->bHasSetStreamInfo)
			{
				pJpgeHandle->stStreamInfo.u32InStride[0] = (cinfo->image_width + 16 - 1) & (~(16 - 1));
				pJpgeHandle->stStreamInfo.u32InSize[0]   = pJpgeHandle->stStreamInfo.u32InStride[0] * cinfo->image_height;
				pJpgeHandle->stStreamInfo.u32InStride[1] = pJpgeHandle->stStreamInfo.u32InStride[0];
				pJpgeHandle->stStreamInfo.u32InSize[1]   = pJpgeHandle->stStreamInfo.u32InStride[1] * (cinfo->image_height / 2);
			}
			else
			{
			}
			pJpgeHandle->stStreamInfo.u32InStride[2] = 0;
			pJpgeHandle->stStreamInfo.u32InSize[2]   = 0;
			pJpgeHandle->EncCfg.YuvSampleType = JPGE_YUV420;
			pJpgeHandle->EncCfg.YuvStoreType  = JPGE_SEMIPLANNAR;
			pJpgeHandle->bCanUserPhyMem       = HI_TRUE;
			break;
		default:
			break;
			
	}

}

/*****************************************************************************
* func			: JPGE_HENC_IfSupport
* description	: if the hard encode support
				  CNcomment: Ӳ�������Ƿ�֧��       CNend\n
* param[in] 	: cinfo 	  CNcomment: �������	CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�       CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��       CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPGE_HENC_IfSupport(j_compress_ptr cinfo)
{

	HI_S32 s32Ret = HI_SUCCESS;
	
#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
	HI_CHAR ProcName[25];
	HI_CHAR Name[25];
	HI_S32 s32Pid = 0;
	HI_CHAR ProcessStatusPath[256] ;
	FILE* pProcessStatus = NULL;
#endif

	JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);
	if (NULL == pJpgeHandle)
	{
		pJpgeHandle->bEncSupport = HI_FALSE;
		return HI_FAILURE;
	}
	if( (cinfo->image_width * cinfo->image_height) < pJpgeHandle->u32FlexionSize)
	{
		pJpgeHandle->bEncSupport = HI_FALSE;
		return HI_FAILURE;
	}
	if(cinfo->next_scanline > 0)
	{
		if(HI_TRUE == pJpgeHandle->bEncSupport)
		{
			return HI_SUCCESS;
		}
		else
		{
			pJpgeHandle->bEncSupport = HI_FALSE;
			return HI_FAILURE;
		}
	}
	
#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
	s32Pid = getpid();
	memset(ProcessStatusPath, 0, 256);
	snprintf(ProcessStatusPath,256,"%s%d%s","/proc/",s32Pid,"/status");
	pProcessStatus = fopen(ProcessStatusPath, "r");
	if(NULL != pProcessStatus)
	{
		memset(ProcName, 0, 25);
		fscanf(pProcessStatus,"%s %s",Name,ProcName);
		fclose(pProcessStatus);
	}
	if(0 == strncmp("ndroid.cts.stub", ProcName, strlen("ndroid.cts.stub")>strlen(ProcName)?strlen("ndroid.cts.stub"):strlen(ProcName)))
	{
		pJpgeHandle->bEncSupport = HI_FALSE;
		return HI_FAILURE;
	}
#endif

	/** CFG **/
	pJpgeHandle->EncCfg.FrameWidth	 = cinfo->image_width;
	pJpgeHandle->EncCfg.FrameHeight	 = cinfo->image_height;
	
	if(HI_TRUE == pJpgeHandle->bEncMCU)
	{/** ����MCU�������ʱӲ��ֻ֧��yuv420sp and yuv422package���� **/
		if(  (cinfo->comp_info[0].h_samp_factor == (cinfo->comp_info[1].h_samp_factor << 1))
		   &&(cinfo->comp_info[0].v_samp_factor == cinfo->comp_info[1].v_samp_factor))
		{
			JPGE_HENC_SetEncColorSpace(cinfo,JPGE_YUV422);
		}
		else if(  (cinfo->comp_info[0].h_samp_factor == (cinfo->comp_info[1].h_samp_factor << 1))
		   		 &&(cinfo->comp_info[0].v_samp_factor == (cinfo->comp_info[1].v_samp_factor << 1)))
		{
			JPGE_HENC_SetEncColorSpace(cinfo,JPGE_YUV420);
		}
		else
		{/** ��ʱӲ��ֻ֧��yuv420sp and yuv422package���� **/
			pJpgeHandle->bEncSupport = HI_FALSE;
			//JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
			return HI_FAILURE;
		}
	}
	else
	{
		if(JCS_YCbCr == cinfo->in_color_space)
		{
			JPGE_HENC_SetEncColorSpace(cinfo,JPGE_YUV444);
		}
		else if(JCS_YUV422_PACKAGE == cinfo->in_color_space)
		{
			JPGE_HENC_SetEncColorSpace(cinfo,JPGE_YUV422);
		}
		else if(JCS_YUV420_SP == cinfo->in_color_space)
		{
			JPGE_HENC_SetEncColorSpace(cinfo,JPGE_YUV420);
		}
		else
		{
			pJpgeHandle->bEncSupport = HI_FALSE;
			//JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
			return HI_FAILURE;
		}
	}
	pJpgeHandle->EncCfg.RotationAngle = 0;
	pJpgeHandle->EncCfg.SlcSplitEn	  = 0;
	pJpgeHandle->EncCfg.SplitSize	  = 0;
	if(0 == pJpgeHandle->s32Quality || 100 == pJpgeHandle->s32Quality)
	{
		pJpgeHandle->EncCfg.Qlevel    = 70;
	}
	else
	{
		pJpgeHandle->EncCfg.Qlevel		  = pJpgeHandle->s32Quality;
	}
	
	/**========================================================================**/
	/** IN Message **/
	pJpgeHandle->EncIn.OutBufSize  = pJpgeHandle->stStreamInfo.u32InStride[0] * cinfo->image_height;
	s32Ret = JPGE_HENC_GetEncMem(pJpgeHandle);
	if(HI_FAILURE == s32Ret)
	{
		pJpgeHandle->bEncSupport = HI_FALSE;
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}
	pJpgeHandle->EncIn.BusViY      = (HI_U32)pJpgeHandle->stMiddleBuf.pInPhy[0];
	pJpgeHandle->EncIn.BusViC	   = (HI_U32)pJpgeHandle->stMiddleBuf.pInPhy[1];
	pJpgeHandle->EncIn.BusViV	   = (HI_U32)pJpgeHandle->stMiddleBuf.pInPhy[2];
	pJpgeHandle->EncIn.ViYStride   = pJpgeHandle->stStreamInfo.u32InStride[0];
	pJpgeHandle->EncIn.ViCStride   = pJpgeHandle->stStreamInfo.u32InStride[1];
	pJpgeHandle->EncIn.BusOutBuf   = (HI_U32)pJpgeHandle->stMiddleBuf.pInPhy[3];
	pJpgeHandle->EncIn.pOutBuf	   = (HI_U8*)pJpgeHandle->stMiddleBuf.pInVir[3];
	if(   (HI_TRUE == pJpgeHandle->bHasSetStreamInfo)
		&&(HI_FALSE == pJpgeHandle->stStreamInfo.bUserPhyMem))
	{
		if(JPGE_SEMIPLANNAR == pJpgeHandle->EncCfg.YuvStoreType)
		{
			memcpy(pJpgeHandle->stMiddleBuf.pInVir[0],pJpgeHandle->stStreamInfo.pInVir[0],pJpgeHandle->stStreamInfo.u32InSize[0]);
			memcpy(pJpgeHandle->stMiddleBuf.pInVir[1],pJpgeHandle->stStreamInfo.pInVir[1],pJpgeHandle->stStreamInfo.u32InSize[1]);
		}
		else if(JPGE_PACKAGE == pJpgeHandle->EncCfg.YuvStoreType)
		{
			memcpy(pJpgeHandle->stMiddleBuf.pInVir[0],pJpgeHandle->stStreamInfo.pInVir[0],pJpgeHandle->stStreamInfo.u32InSize[0]);
		}
		else if(JPGE_PLANNAR == pJpgeHandle->EncCfg.YuvStoreType)
		{
			memcpy(pJpgeHandle->stMiddleBuf.pInVir[0],pJpgeHandle->stStreamInfo.pInVir[0],pJpgeHandle->stStreamInfo.u32InSize[0]);
			memcpy(pJpgeHandle->stMiddleBuf.pInVir[1],pJpgeHandle->stStreamInfo.pInVir[1],pJpgeHandle->stStreamInfo.u32InSize[1]);
			memcpy(pJpgeHandle->stMiddleBuf.pInVir[2],pJpgeHandle->stStreamInfo.pInVir[2],pJpgeHandle->stStreamInfo.u32InSize[2]);
		}
	}
    
	pJpgeHandle->bEncSupport = HI_TRUE;
	
	return HI_SUCCESS;
	
}
/*****************************************************************************
* func			: JPEG_HENC_Create
* description	: create jpge handle
				  CNcomment: ����������   	CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�  CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��  CNend\n
* others:		: NA
*****************************************************************************/
static HI_S32	JPEG_HENC_Create(HI_U32 *pEncHandle, const JPGE_ENCCFG_S *pEncCfg,HI_S32 s32JpgeDev)
{

    HI_S32 s32Ret = HI_SUCCESS;
    JPGE_ENCCFGINFO_S stEncCgf = {0};
	
    if ((NULL == pEncHandle) || (NULL == pEncCfg))
    {
    	JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
        return JPGE_NULL_PTR;
    }
    stEncCgf.pEncHandle = (HI_S32*)pEncHandle;
    memcpy(&stEncCgf.EncCfg , pEncCfg,sizeof(JPGE_ENCCFG_S));
    s32Ret = ioctl(s32JpgeDev, JPGE_CREATE_CMD, &stEncCgf);
    *pEncHandle = (HI_U32)*stEncCgf.pEncHandle;
	
    return s32Ret;

}


/*****************************************************************************
* func			: JPGE_HENC_Destroy
* description	: close encode handle
				  CNcomment: ���ٱ�����     	CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�  CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��  CNend\n
* others:		: NA
*****************************************************************************/
static HI_S32 JPGE_HENC_Destroy(HI_U32 EncHandle,HI_S32 s32JpgeDev)
{
   return ioctl(s32JpgeDev, JPGE_DESTROY_CMD, &EncHandle);
}


/*****************************************************************************
* func			: JPEG_HENC_Start
* description	: jpeg encode
				  CNcomment: ��ʼ����   	CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�  CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��  CNend\n
* others:		: NA
*****************************************************************************/
static HI_S32	JPEG_HENC_Start(HI_U32 EncHandle, const JPGE_ENCIN_S *pEncIn, JPGE_ENCOUT_S *pEncOut,HI_S32 s32JpgeDev)
{
    HI_S32 s32Ret = HI_SUCCESS;
    JPGE_ENCINFO_S stEncInfo = {0};

    if ((NULL == pEncIn) || (NULL == pEncOut))
    {
    	JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
        return JPGE_NULL_PTR;
    }
    stEncInfo.EncHandle = (HI_S32)EncHandle;
    
    memcpy(&stEncInfo.EncIn , pEncIn,sizeof(JPGE_ENCIN_S));
    
    s32Ret = ioctl(s32JpgeDev, JPGE_ENCODE_CMD, &stEncInfo);
    memcpy( pEncOut,&stEncInfo.EncOut ,sizeof(JPGE_ENCOUT_S));
	
    return s32Ret;
	
}

/*****************************************************************************
* func			: JPEG_HENC_Encode
* description	: jpeg encode
				  CNcomment: ��ʼ����   	CNend\n
* in            : cinfo       �������
* retval		: HI_SUCCESS  CNcomment: �ɹ�  CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32	JPEG_HENC_Encode(const struct jpeg_compress_struct *cinfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
	HI_S32 s32JpgeDev = -1;
	HI_U32 u32EncHandle = 0;
	
	JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);

#ifdef CONFIG_JPGE_SAVE_SRCDATA
	HI_CHAR *pFile = "src-data";
	HI_CHAR pFileName[256];
	FILE *pSrcFile = NULL;
	static HI_U32 u32Count = 0;
	snprintf(pFileName,256,"%s%s%d.data",SRCDATA_DIR,pFile,u32Count);
	u32Count++;
	pSrcFile = fopen(pFileName,"wb+");
	if(NULL == pSrcFile)
	{
		JPEG_TRACE("open %s failure\n",pFileName);
	}
	switch(pJpgeHandle->EncCfg.YuvStoreType)
	{
		case JPGE_PACKAGE:
			  fwrite(pJpgeHandle->stMiddleBuf.pInVir[0],1,pJpgeHandle->stStreamInfo.u32InSize[0],pSrcFile);
			  break;
		case JPGE_SEMIPLANNAR:
			  fwrite(pJpgeHandle->stMiddleBuf.pInVir[0],1,pJpgeHandle->stStreamInfo.u32InSize[0],pSrcFile);
			  fwrite(pJpgeHandle->stMiddleBuf.pInVir[1],1,pJpgeHandle->stStreamInfo.u32InSize[1],pSrcFile);
			  break;
		case JPGE_PLANNAR:
			  break;
		default:
			  break;
	}
	fclose(pSrcFile);
#endif


	/** open device **/
	s32JpgeDev = open(JPGE_DEV,O_RDWR | O_SYNC);
    if (-1 == s32JpgeDev)
    {/**
      ** should revise the device competence same as jpeg
      ** vi out/..../root/ueventd.bigfish.rc and make kernel
      **/
      	JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
        return HI_FAILURE;
    }
    /** encode **/
	s32Ret = JPEG_HENC_Create(&u32EncHandle,&pJpgeHandle->EncCfg,s32JpgeDev);
	if( HI_SUCCESS != s32Ret )
	{
		close(s32JpgeDev);
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}

	s32Ret = JPEG_HENC_Start(u32EncHandle, &pJpgeHandle->EncIn, &pJpgeHandle->EncOut,s32JpgeDev);
	if (HI_SUCCESS != s32Ret)
	{
		close(s32JpgeDev);
		JPGE_HENC_Destroy(u32EncHandle,s32JpgeDev);
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}
		
	s32Ret = JPGE_HENC_Destroy(u32EncHandle,s32JpgeDev);
	if (HI_SUCCESS != s32Ret)
	{   
		close(s32JpgeDev);
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}
	
	/** close device **/
	if(-1 != s32JpgeDev)
	{
	   close(s32JpgeDev);
	}
	s32JpgeDev = -1;
	
	pJpgeHandle->bEncodeSuccess  = HI_TRUE;
	
    return HI_SUCCESS;
	
}

/*****************************************************************************
* func			: JPEG_HENC_WriteData
* description	: write data to dest
				  CNcomment: ������������д��Ŀ��λ��  CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�            CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��            CNend\n
* others:		: NA
*****************************************************************************/
HI_S32	JPEG_HENC_WriteData(j_compress_ptr cinfo)
{

		HI_S32 s32LeaveSize = 0;
		HI_S32 s32WriteSize = 0;

#if 0
		/** linux debug **/
		my_dest_ptr dest = (my_dest_ptr) cinfo->dest;
#endif
		JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);

#if 0
		/** linux debug **/
		if(HI_TRUE == pJpgeHandle->bWriteFile)
		{
			fwrite(pJpgeHandle->EncOut.pStream,1,pJpgeHandle->EncOut.StrmSize,dest->outfile);
			return HI_SUCCESS;
		}
#endif
		s32WriteSize = pJpgeHandle->s32FreeBufSize - cinfo->dest->free_in_buffer;
		s32LeaveSize = pJpgeHandle->EncOut.StrmSize - s32WriteSize;

		if(0 != s32WriteSize)
		{
			memcpy(cinfo->dest->next_output_byte,(pJpgeHandle->EncOut.pStream + s32WriteSize),cinfo->dest->free_in_buffer);			
           (cinfo->dest->empty_output_buffer)(cinfo);
			s32WriteSize = pJpgeHandle->s32FreeBufSize;
			s32LeaveSize = pJpgeHandle->EncOut.StrmSize - s32WriteSize;
		}
		while(s32LeaveSize >= pJpgeHandle->s32FreeBufSize)
		{
			memcpy(cinfo->dest->next_output_byte,(pJpgeHandle->EncOut.pStream + s32WriteSize),cinfo->dest->free_in_buffer);
			(cinfo->dest->empty_output_buffer)(cinfo);
			s32WriteSize = s32WriteSize + cinfo->dest->free_in_buffer;
			s32LeaveSize = pJpgeHandle->EncOut.StrmSize - s32WriteSize;
		}
		if(s32LeaveSize > 0)
		{
			cinfo->dest->free_in_buffer = pJpgeHandle->s32FreeBufSize - s32LeaveSize;
			memcpy(cinfo->dest->next_output_byte,(pJpgeHandle->EncOut.pStream + s32WriteSize),s32LeaveSize);
			(cinfo->dest->term_destination)(cinfo);
		}
		
		return HI_SUCCESS;
		
		
}


/*****************************************************************************
* func			: JPGE_HENC_Init
* description	: init the private structure para
				  CNcomment: ��ʼ��˽�нṹ�����	CNend\n
* param[in] 	: cinfo 	  CNcomment: �������	CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�  CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPGE_HENC_Init(j_common_ptr cinfo)
{

	JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = NULL;
	pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)calloc(1, SIZEOF(JPGE_HENC_HANDLE_S));
	if(NULL == pJpgeHandle)
	{
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}
	
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
	pJpgeHandle->s32MMZDev   =	-1;
#endif

#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
	pJpgeHandle->s32MMZDev = gfx_mem_open();
	if(pJpgeHandle->s32MMZDev < 0)
	{
		free(pJpgeHandle);
		pJpgeHandle = NULL;
		pJpgeHandle->s32MMZDev = -1;
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}
#endif

	cinfo->client_data = (void *)pJpgeHandle;
	
	return HI_SUCCESS;
	
}
/*****************************************************************************
* func			: JPEG_HENC_CloseDev
* description	: closxe some device that encode need
				  CNcomment: �رձ���򿪵�����豸 	   CNend\n
* param[in] 	: cinfo 		CNcomment: �������    CNend\n
* retval		: HI_SUCCESS	CNcomment: �ɹ� 	   CNend\n
* retval		: HI_FAILURE	CNcomment: ʧ�� 	   CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HENC_CloseDev(const struct jpeg_common_struct *cinfo)
{

		JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);

        if (NULL == pJpgeHandle)
		{
			return HI_SUCCESS;
		}

		return HI_SUCCESS;
}

/*****************************************************************************
* func			: JPEG_HENC_Abort
* description	: when want use the encode again,call this
				  CNcomment:  ��������ʹ�ñ����������øýӿ� CNend\n
* param[in] 	: cinfo 	  CNcomment: �������	           CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�  CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HENC_Abort(const struct jpeg_common_struct *cinfo)
{

		JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);
		if (NULL == pJpgeHandle)
		{
			return HI_SUCCESS;
		}
	   /**
		** if memory leak, take out this check
		** CNcomment: Ҫ�����ڴ��ͷ����⣬ȥ�����ж� CNend\n
		**/
		JPGE_HENC_FreeEncMem(pJpgeHandle);

#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		if(pJpgeHandle->s32MMZDev >= 0)
		{
			gfx_mem_close(pJpgeHandle->s32MMZDev);
		}
		pJpgeHandle->s32MMZDev = -1;
#endif

		/**
		** dinit the para, these are the same as init para value
		** CNcomment: ȥ��ʼ��������ֵ����֤�ͳ�ʼ��������ֵ����һ�� CNend\n
		**/		
		memset(pJpgeHandle,0,sizeof(JPGE_HENC_HANDLE_S));
		
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pJpgeHandle->s32MMZDev  =  -1;
#endif

		return HI_SUCCESS;
		 
}

/*****************************************************************************
* func			: JPGE_HENC_DInit
* description	: dinit the hard compress
				  CNcomment: ����Ӳ��������         CNend\n
* param[in] 	: cinfo 	  CNcomment: �������	CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�       CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��       CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPGE_HENC_DInit(const struct jpeg_common_struct *cinfo)
{

		JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);
		if (NULL == pJpgeHandle)
		{
			return HI_SUCCESS;
		}
		JPGE_HENC_FreeEncMem(pJpgeHandle);

#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		if(pJpgeHandle->s32MMZDev >= 0)
		{
			gfx_mem_close(pJpgeHandle->s32MMZDev);
		}
		pJpgeHandle->s32MMZDev = -1;
#endif

		free(pJpgeHandle);
		pJpgeHandle = NULL;
		
		return HI_SUCCESS;

}
/*****************************************************************************
* func			: HI_JPGE_SetStreamInfo
* description	: set stream info
				  CNcomment: ���ñ���������Ϣ      CNend\n
* param[in] 	: cinfo 	  CNcomment: �������	CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�       CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��       CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 HI_JPGE_SetStreamInfo(const struct jpeg_compress_struct *cinfo, const HI_JPEG_STREAM_INFO_S *pstStreamInfo)
{

	JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);
	HI_S32 s32Cnt = 0;
	if (NULL == pJpgeHandle)
	{
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}
	if (NULL == pstStreamInfo)
	{
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}

	for(s32Cnt = 0; s32Cnt < MAX_IN_PIXEL_COMPONENT_NUM; s32Cnt++)
	{
		pJpgeHandle->stStreamInfo.pInPhy[s32Cnt]      = pstStreamInfo->pInPhy[s32Cnt];
		pJpgeHandle->stStreamInfo.pInVir[s32Cnt]      = pstStreamInfo->pInVir[s32Cnt];
		pJpgeHandle->stStreamInfo.u32InStride[s32Cnt] = pstStreamInfo->u32InStride[s32Cnt];
		pJpgeHandle->stStreamInfo.u32InSize[s32Cnt]   = pstStreamInfo->u32InSize[s32Cnt];
	}
	pJpgeHandle->stStreamInfo.bUserPhyMem = pstStreamInfo->bUserPhyMem;
	
	pJpgeHandle->bHasSetStreamInfo = HI_TRUE;

	return HI_SUCCESS;
	
}

/*****************************************************************************
* func			: HI_JPGE_GetInflexion
* description	: get hard enc inflexion
				  CNcomment: ��ȡ����յ�     CNend\n
* param[in] 	: cinfo 	  CNcomment: ����������	CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�       CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��       CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 HI_JPGE_GetInflexion(const struct jpeg_compress_struct *cinfo, HI_U32 *pu32flexionSize)
{
	JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);
	if (NULL == pJpgeHandle)
	{
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}

	*pu32flexionSize = pJpgeHandle->u32FlexionSize;

	return HI_SUCCESS;
}
/*****************************************************************************
* func			: HI_JPGE_SetInflexion
* description	: set hard enc inflexion
				  CNcomment: ���ñ���յ�	  CNend\n
* param[in] 	: cinfo 	  CNcomment: ����������	CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�		CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��		CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 HI_JPGE_SetInflexion(const struct jpeg_compress_struct *cinfo, const HI_U32 u32flexionSize)
{
	JPGE_HENC_HANDLE_S_PTR  pJpgeHandle = (JPGE_HENC_HANDLE_S_PTR)(cinfo->client_data);
	if (NULL == pJpgeHandle)
	{
		JPEG_TRACE("====%s %s %d\n",__FILE__,__FUNCTION__,__LINE__);
		return HI_FAILURE;
	}

	pJpgeHandle->u32FlexionSize = u32flexionSize;

	return HI_SUCCESS;
}
#endif
