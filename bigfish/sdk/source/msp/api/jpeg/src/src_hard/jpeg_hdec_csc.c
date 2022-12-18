/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_csc.h
Version		    : Initial Draft
Author		    : 
Created		    : 2014/06/20
Description	    : the mem mangage
                  CNcomment: 颜色空间转换 CNend\n
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
#include <fcntl.h>
#include <unistd.h>

#include "hi_jpeg_config.h"

#ifndef CONFIG_JPEG_CSC_DISABLE
#include  "jpeg_hdec_csc.h"

#if   defined(CHIP_TYPE_hi3712)      \
   || defined(CHIP_TYPE_hi3716m)     \
   || defined(CHIP_TYPE_hi3716mv310) \
   || defined(CHIP_TYPE_hi3110ev500) \
   || defined(CHIP_TYPE_hi3716mv320)
#include  "hi_tde_ioctl.h"
#else
#include  "hi_drv_tde.h"
#endif

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/

/******************************* API forward declarations *******************/

/******************************* API realization *****************************/
/*****************************************************************************
* func			: JPEG_HDEC_CSC_Open
* description	: Open the csc device
				  CNcomment: CSC转换设备打开 CNend\n
* retval		: HI_SUCCESS	CNcomment: 成功 	  CNend\n
* retval		: HI_FAILURE	CNcomment: 失败 	  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_CSC_Open()
{

	HI_S32 s32CscDev = -1;
	s32CscDev = open(CSC_DEV, O_RDWR, 0);
	if (s32CscDev < 0){
		return HI_ERR_TDE_DEV_OPEN_FAILED;
	}
	return s32CscDev;
}

/*****************************************************************************
* func			: JPEG_HDEC_CSC_Close
* description	: close the csc device
				  CNcomment: CSC转换设备关闭 CNend\n
* param[in]	    : s32CscDev     CNcomment: CSC 设备   CNend\n
* retval		: HI_SUCCESS	CNcomment: 成功 	  CNend\n
* retval		: HI_FAILURE	CNcomment: 失败 	  CNend\n
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_CSC_Close(HI_S32 s32CscDev)
{
	close(s32CscDev);
}

/*****************************************************************************
* func			: JPEG_HDEC_CSC_BeginJob
* description	: create csc task
				  CNcomment: 创建CSC任务 CNend\n
* param[in]	    : s32CscDev     CNcomment: CSC 设备   CNend\n
* retval		: HI_SUCCESS	CNcomment: 成功 	  CNend\n
* retval		: HI_FAILURE	CNcomment: 失败 	  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_CSC_BeginJob(HI_S32 s32CscDev)
{
	TDE_HANDLE s32Handle;
	if(s32CscDev < 0){
		return HI_FAILURE;
	}
	if (ioctl(s32CscDev, TDE_BEGIN_JOB, &s32Handle) < 0){
		return HI_ERR_TDE_INVALID_HANDLE;
	}
	return s32Handle;
}

/*****************************************************************************
* func			: JPEG_HDEC_CSC_MbBlit
* description	: run csc task
				  CNcomment: 执行任务 CNend\n
* param[in]	    : s32CscDev     CNcomment: CSC 设备   CNend\n
* retval		: HI_SUCCESS	CNcomment: 成功 	  CNend\n
* retval		: HI_FAILURE	CNcomment: 失败 	  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_CSC_MbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, TDE2_SURFACE_S* pstDst,TDE2_RECT_S  *pstDstRect,TDE2_MBOPT_S* pstMbOpt,HI_S32 s32CscDev,HI_BOOL bYCbCrMemMMUType,HI_BOOL bKRGBMemMMUType)
{


	TDE_MBBITBLT_CMD_S stMbBlit = {0};

	if(s32CscDev < 0){
		return HI_FAILURE;
	}
	if ((NULL == pstMB) || (NULL == pstDst) || (NULL == pstMbOpt)){
		return HI_ERR_TDE_NULL_PTR;
	}

	stMbBlit.s32Handle = s32Handle;
	memcpy(&stMbBlit.stMB, pstMB, sizeof(TDE2_MB_S));
	memcpy(&stMbBlit.stMbRect, pstMbRect, sizeof(TDE2_RECT_S));
	memcpy(&stMbBlit.stDstRect, pstDstRect, sizeof(TDE2_RECT_S));
	memcpy(&stMbBlit.stMbOpt, pstMbOpt, sizeof(TDE2_MBOPT_S));
	/** Support 64bit,don't use memcpy **/
	#if 0
    memcpy(&stMbBlit.stDst, pstDst, sizeof(TDE2_SURFACE_S));
	#else
    stMbBlit.stDst.bAlphaExt1555  = pstDst->bAlphaExt1555;
    stMbBlit.stDst.bAlphaMax255   = pstDst->bAlphaMax255;
    stMbBlit.stDst.bYCbCrClut     = pstDst->bYCbCrClut;
    stMbBlit.stDst.enColorFmt     = pstDst->enColorFmt;
    stMbBlit.stDst.pu8ClutPhyAddr = 0;
    stMbBlit.stDst.u32CbCrPhyAddr = pstDst->u32CbCrPhyAddr;
    stMbBlit.stDst.u32CbCrStride  = pstDst->u32CbCrStride;
    stMbBlit.stDst.u32Height      = pstDst->u32Height;
    stMbBlit.stDst.u32PhyAddr     = pstDst->u32PhyAddr;
    stMbBlit.stDst.u32Stride      = pstDst->u32Stride;
    stMbBlit.stDst.u32Width       = pstDst->u32Width;
    stMbBlit.stDst.u8Alpha0       = pstDst->u8Alpha0;
    stMbBlit.stDst.u8Alpha1       = pstDst->u8Alpha1;
	#endif

	if(HI_TRUE == bYCbCrMemMMUType){
		;
	}else{
		;
	}
	if(HI_TRUE == bKRGBMemMMUType){
		;
	}else{
		;
	}

	return ioctl(s32CscDev, TDE_MB_BITBLT, &stMbBlit);

}


/*****************************************************************************
* func			: JPEG_HDEC_CSC_EndJob
* description	: submit csc task
				  CNcomment: 提交任务 CNend\n
* param[in]	    : s32CscDev     CNcomment: CSC 设备   CNend\n
* retval		: HI_SUCCESS	CNcomment: 成功 	  CNend\n
* retval		: HI_FAILURE	CNcomment: 失败 	  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_CSC_EndJob(TDE_HANDLE s32Handle, HI_BOOL bSync, HI_BOOL bBlock, HI_U32 u32TimeOut,HI_S32 s32CscDev)
{

	TDE_ENDJOB_CMD_S stEndJob;

	if(s32CscDev < 0){
		return HI_FAILURE;
	}
	/* Disable sync function */
	bSync = HI_FALSE;
	
	stEndJob.s32Handle  = s32Handle;
	stEndJob.bSync	    = bSync;
	stEndJob.bBlock     = bBlock;
	stEndJob.u32TimeOut = u32TimeOut;

	return ioctl(s32CscDev, TDE_END_JOB, &stEndJob);

}
#endif
