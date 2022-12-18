/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_sentstream.c
Version		    : Initial Draft
Author		    : y00181162
Created		    : 2014/06/20
Description	    : dispose the inside stream
                  CNcomment: �����Ĵ���ʽ CNend\n
Function List 	:

			  		  
History       	:
Date				Author        		Modification
2014/06/20		    y00181162		    Created file      	
******************************************************************************/

/*********************************add include here******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "jpeglib.h"
#include "jpegint.h"
#include "jdatasrc.h"

#include "jpeg_hdec_adp.h"
#include "jpeg_hdec_api.h"
#include "jpeg_hdec_rwreg.h"
#include "hi_jpeg_config.h"
#include "hi_jpeg_drv_api.h"
#include "hi_jpeg_reg.h"
#include "jpeg_hdec_mem.h"

#include "hi_jpeg_hdec_test.h"

#ifdef CONFIG_JPEG_SUSPEND
#include "jpeg_hdec_suspend.h"
#endif

#ifdef CONFIG_JPEG_TEST_HARD_DEC_CAPA
#include <sys/time.h>
#endif

#if defined(CONFIG_JPEG_ANDROID_DEBUG_ENABLE) && defined(CONFIG_JPEG_DEBUG_INFO)
#define LOG_TAG "libjpeg"
#endif

/***************************** Macro Definition ******************************/

#define JPG_RESUME_VALUE           0x01
#define JPG_EOF_VALUE              0x02
#define JPG_INTTYPE_DELAY_TIME    10000 /** 10s **/

#ifdef CONFIG_JPEG_TEST_HARD_DEC_CAPA
#define HARDDEC_TINIT()   struct timeval tv_start, tv_end; unsigned int time_cost,line_start
#define HARDDEC_TSTART()  gettimeofday(&tv_start, NULL);line_start = __LINE__
#define HARDDEC_TEND()     \
gettimeofday(&tv_end, NULL); \
time_cost = ((tv_end.tv_usec - tv_start.tv_usec) + (tv_end.tv_sec - tv_start.tv_sec)*1000000); \
JPEG_TRACE("=============================================================================\n"); \
JPEG_TRACE("FROM LINE: %d TO LINE: %d COST: %d us\n",line_start, __LINE__, time_cost);         \
JPEG_TRACE("=============================================================================\n")
#endif

/******************** to see which include file we want to use***************/



/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
static HI_S32 sg_s32ResetNum = 0;
#endif


/******************************* API forward declarations *******************/

/*****************************************************************************
* func			: JPEG_HDEC_CheckOut
* description	: check whether should memcpy to output buffer
				  CNcomment:  �ж��Ƿ���Ҫ��������buffer��    CNend\n
* param[in]	    : *pJpegHandle   CNcomment: ���������          CNend\n
* retval		: HI_SUCCESS  CNcomment:  �ɹ�		   CNend\n
* retval		: HI_FAILURE  CNcomment:  ʧ��		   CNend\n
* others:		: NA
*****************************************************************************/
static HI_S32 JPEG_HDEC_CheckOut(const JPEG_HDEC_HANDLE_S *pJpegHandle)
{
#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(   (HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem)
		    &&((HI_TRUE == pJpegHandle->bOutYCbCrSP) ||(HI_TRUE == pJpegHandle->bDecARGB)))
#else
		if(  (HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem)
		   &&(HI_TRUE == pJpegHandle->bOutYCbCrSP))
#endif
		{
			return HI_FAILURE;
		}

#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if((HI_TRUE != pJpegHandle->bOutYCbCrSP) && (HI_TRUE != pJpegHandle->bDecARGB))
#else
		if(HI_TRUE != pJpegHandle->bOutYCbCrSP)
#endif
		{
			return HI_FAILURE;
		}

		return HI_SUCCESS;

}

/*****************************************************************************
* func			: JPEG_HDEC_GetIntStatus
* description	: get interrupt status
				  CNcomment:  ��ȡ�ж�״̬             CNend\n
* param[in]	    : *pJpegHandle   CNcomment: ��������� CNend\n
* retval		: HI_SUCCESS  CNcomment:  �ɹ�		   CNend\n
* retval		: HI_FAILURE  CNcomment:  ʧ��		   CNend\n
* others:		: NA
*****************************************************************************/
static HI_S32 JPEG_HDEC_GetIntStatus(const JPEG_HDEC_HANDLE_S *pJpegHandle, JPG_INTTYPE_E *pIntType, HI_U32 u32TimeOut)
{

		HI_S32 s32RetVal;
		JPG_GETINTTYPE_S GetIntType;

		GetIntType.IntType = JPG_INTTYPE_NONE;
		GetIntType.TimeOut = u32TimeOut;

		s32RetVal = ioctl(pJpegHandle->s32JpegDev, CMD_JPG_GETINTSTATUS, &GetIntType);

		if (HI_SUCCESS != s32RetVal)
		{
			return s32RetVal;
		}
		*pIntType = GetIntType.IntType;

		return HI_SUCCESS;
    
}
/*****************************************************************************
* func			: JPEG_HDEC_SuspendDispose
* description	: dispose the suspend
				  CNcomment:  ��������	 CNend\n
* param[in] 	: cinfo 	          CNcomment:  �������	           CNend\n
* param[in] 	: pbResumeOk     	  CNcomment:  �����Ѿ�����         CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_SuspendDispose(const struct jpeg_decompress_struct *cinfo,HI_BOOL *pbResumeOk)
{
#ifdef CONFIG_JPEG_SUSPEND
		HI_BOOL bSuspendSingal   = HI_FALSE;
		HI_BOOL bResumeSingal    =  HI_FALSE;
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		JPEG_HDEC_GetSuspendSignal(pJpegHandle,&bSuspendSingal);
		JPEG_HDEC_GetResumeSignal(pJpegHandle,&bResumeSingal);
		if( (HI_TRUE == bSuspendSingal) ||  (HI_TRUE == bResumeSingal))
		{
			JPEG_HDEC_Resume(cinfo);
			*pbResumeOk = HI_TRUE;
#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
			JPEG_TRACE("===================================================\n");
			JPEG_TRACE("ģ�������Ч\n");
			JPEG_TRACE("===================================================\n");
#endif
		}
#endif
}


/*****************************************************************************
* func			: JPEG_HDEC_SendStreamFromPhyMem
* description	: get the stream from physics memory
				  CNcomment:  ������Դ�����������ڴ�Ĵ���ʽ	 CNend\n
* param[in] 	: cinfo 	  CNcomment:  �������	   CNend\n
* retval		: HI_SUCCESS  CNcomment:  �ɹ�		   CNend\n
* retval		: HI_FAILURE  CNcomment:  ʧ��		   CNend\n
* others:		: NA
*****************************************************************************/

#ifdef CONFIG_JPEG_STREAMBUF_4ALIGN
/**
 ** before 3716CV200 EC,the save buffer should 4bytes align
 ** CNcomment:3716CV200 EC֮ǰ�Ĵ洢����buffer��ʼ��ַ��Ҫ4�ֽڶ��� CNend\n
 **/
HI_S32 JPEG_HDEC_SendStreamFromPhyMem(j_decompress_ptr cinfo)
{

		JPG_INTTYPE_E eIntStatus        = JPG_INTTYPE_NONE;
		HI_S32 s32Cnt                    = 0;
		HI_U32 u32ConsumSize            = 0;
		HI_U64 u64LeaveSize             = 0;
		HI_U32 u32AlignSize             = 0;
		HI_U32 u32DecSize               = 0;
		HI_BOOL bStartDec               = HI_TRUE;
		HI_CHAR* pDataPhyAddr           = NULL;
		HI_CHAR* pDataVirAddr           = NULL;
		HI_CHAR* pSaveStreamPhyAddr     = NULL;
		HI_CHAR* pSaveStreamVirAddr     = NULL;
		HI_CHAR* pSaveStreamEndPhyAddr  = NULL;

		HI_S32 s32Ret = HI_SUCCESS;

		HI_BOOL bReachEOF = HI_FALSE;
		HI_BOOL b4Align   = HI_FALSE;/**< whether 4bytes align *//**<CNcomment:�Ƿ�4�ֽڶ���*/

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);


#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		/**
		** output the scen message to file
		** CNcomment:�������ֳ� CNend\n
		**/
		if(HI_TRUE == pJpegHandle->bSaveScen)
		{
			HI_JPEG_OpenScenFile(cinfo);
		}
#endif

		/**
		** calc the consume stream size
		** CNcomment:����Ӳ��֮ǰ���ĵ�����������ÿ�ζ������ۼ�-4096��ʣ��������� CNend\n
		**/	 
		u32ConsumSize = pJpegHandle->stHDecDataBuf.u32ConsumeDataSize - cinfo->src->bytes_in_buffer;
		u64LeaveSize  = pJpegHandle->stHDecDataBuf.u64DataSize - ((HI_U64)u32ConsumSize);

		pDataPhyAddr          = pJpegHandle->stHDecDataBuf.pDataPhyBuf + u32ConsumSize;
		pDataVirAddr          = pJpegHandle->stHDecDataBuf.pDataVirBuf + u32ConsumSize;
		pSaveStreamPhyAddr    = pJpegHandle->stHDecDataBuf.pDataPhyBuf + u32ConsumSize;
		pSaveStreamVirAddr    = pJpegHandle->stHDecDataBuf.pDataVirBuf + u32ConsumSize;
		pSaveStreamEndPhyAddr = pJpegHandle->stHDecDataBuf.pDataPhyBuf + pJpegHandle->stHDecDataBuf.u64DataSize;
		if(0 == (HI_S32)pDataPhyAddr % JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN)
		{
			b4Align = HI_TRUE;
		}
		else
		{
			/**
			**��һ�ν���JPGD_HDEC_MMZ_ALIGN_16BYTES + 4�ֽڶ���Ҫ���������С����ΪҪ������̫�ٽⲻ��
			**/
			pSaveStreamPhyAddr = (HI_CHAR*)(((unsigned long)pSaveStreamPhyAddr + 16 + JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN - 1) & (~(JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN - 1)));
			pSaveStreamVirAddr = (HI_CHAR*)(((unsigned long)pSaveStreamVirAddr + 16 + JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN - 1) & (~(JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN - 1)));
			u32AlignSize       = (unsigned long)pSaveStreamPhyAddr - (unsigned long)pDataPhyAddr;
		}
		if(u64LeaveSize <= u32AlignSize)
		{
			u32DecSize  = (HI_U32)u64LeaveSize;
			bReachEOF   = HI_TRUE;
		}
		else
		{
			u32DecSize  = u32AlignSize;
			bReachEOF   = HI_FALSE;
		}

		if(HI_FALSE == b4Align)
		{
			memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,pDataVirAddr,u32DecSize);
			/** ˢ�������� **/
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
#else
			s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
#endif
			if(HI_SUCCESS != s32Ret)
			{
				goto FAIL;
			}
		}

#ifdef CONFIG_JPEG_TEST_HARD_DEC_CAPA
		HARDDEC_TINIT();
		HARDDEC_TSTART();
#endif

		do
		{

			if(HI_TRUE == bStartDec && HI_FALSE == b4Align)
			{
#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
				if(HI_TRUE == pJpegHandle->bSaveScen)
				{
				   /**
					** should save scen before start decode
					** CNcomment:Ҫ�ڽ�������ǰ�����ֳ�����������ʧ�� CNend\n
					**/
					HI_JPEG_OutScenData(cinfo,pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf,pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf + u32DecSize,pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,(HI_U64)u32DecSize,HI_TRUE);
				}
#endif
				//JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADDR,(HI_S32 )(pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf - JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN));
		        //JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADDR,(HI_S32)(pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf + u32DecSize + JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN));
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (HI_S32)(pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf));
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(HI_S32)(pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf + u32DecSize));
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? JPG_EOF_VALUE : 0x0));
#ifdef CONFIG_JPEG_4KDDR_DISABLE
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
#else
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
#endif
			}
			else if(HI_TRUE == bStartDec && HI_TRUE == b4Align)
			{
#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
				if(HI_TRUE == pJpegHandle->bSaveScen)
				{  /**
					** should save scen before start decode
					** CNcomment:Ҫ�ڽ�������ǰ�����ֳ�����������ʧ�� CNend\n
					**/
					HI_JPEG_OutScenData(cinfo,pSaveStreamPhyAddr,pSaveStreamEndPhyAddr,pSaveStreamVirAddr,(HI_U64)u32DecSize,HI_TRUE);
				}
#endif
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (HI_S32)pSaveStreamPhyAddr);
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(HI_S32)pSaveStreamEndPhyAddr);
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME, 0x2);
#ifdef CONFIG_JPEG_4KDDR_DISABLE
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
#else
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
#endif
			}
			else
			{
#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
				if(HI_TRUE == pJpegHandle->bSaveScen)
				{  /**
					** should save scen before start decode
					** CNcomment:Ҫ�ڽ�������ǰ�����ֳ�����������ʧ�� CNend\n
					**/
					HI_JPEG_OutScenData(cinfo,pSaveStreamPhyAddr,pSaveStreamEndPhyAddr,pSaveStreamVirAddr,(HI_U64)(pSaveStreamEndPhyAddr - pSaveStreamPhyAddr),HI_FALSE);
				}
#endif
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (HI_S32)pSaveStreamPhyAddr);
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(HI_S32)pSaveStreamEndPhyAddr);
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(JPG_EOF_VALUE|JPG_RESUME_VALUE));
			}

			bStartDec  = HI_FALSE;
			bReachEOF  = HI_TRUE;

			eIntStatus = JPG_INTTYPE_ERROR;
			s32Ret = JPEG_HDEC_GetIntStatus(pJpegHandle, &eIntStatus, JPG_INTTYPE_DELAY_TIME);
			if(HI_SUCCESS != s32Ret)
			{
				goto FAIL;
			}
			if(JPG_INTTYPE_ERROR == eIntStatus) 
			{
				goto FAIL;
			}
			else if(JPG_INTTYPE_FINISH == eIntStatus) 
			{  
				break;
			}
			else if(JPG_INTTYPE_CONTINUE == eIntStatus)
			{
				//JPEG_HDEC_SetStreamBuf(cinfo);
				continue;
			}
			else 
			{
				goto FAIL;
			}

		}while(JPG_INTTYPE_FINISH != eIntStatus);

#ifdef CONFIG_JPEG_TEST_HARD_DEC_CAPA
		HARDDEC_TEND();
		/** himd.l 0xf8c40018 **/
		/** �в��ֵ himd.l 0xf8c40008 **/
#endif

		cinfo->output_scanline        = 0;
		cinfo->global_state           = DSTATE_STOPPING;
		cinfo->inputctl->eoi_reached  = HI_TRUE;
		cinfo->rec_outbuf_height      = 1;
		cinfo->MCUs_per_row           = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)&0xffff;
		cinfo->MCU_rows_in_scan       = ((HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)>>16)&0xffff;
		cinfo->blocks_in_MCU          =  cinfo->num_components;

		for(s32Cnt=0; s32Cnt<cinfo->num_components; s32Cnt++)
		{
			cinfo->MCU_membership[s32Cnt] = s32Cnt;
		}

		s32Ret = JPEG_HDEC_CheckOut(pJpegHandle);
		if(HI_SUCCESS != s32Ret)
		{
#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			HI_JPEG_CloseScenFile(cinfo);
#endif
			return HI_SUCCESS;
		}

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize && HI_TRUE != pJpegHandle->bDecARGB)
#else
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize)
#endif
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[0],pJpegHandle->stMiddleSurface.pMiddleVir[0],pJpegHandle->stJpegSofInfo.u32YSize);
		}
		if(0 != pJpegHandle->stJpegSofInfo.u32CSize)
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[1],pJpegHandle->stMiddleSurface.pMiddleVir[1],pJpegHandle->stJpegSofInfo.u32CSize);
		}

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_JPEG_CloseScenFile(cinfo);
#endif

		return HI_SUCCESS;

		FAIL:

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		if(HI_TRUE == pJpegHandle->bSaveScen)
		{
			HI_JPEG_CloseScenFile(cinfo);
		}
#endif
		return HI_FAILURE;

}

HI_S32 JPEG_HDEC_SendStreamFromReturnPhyMem(j_decompress_ptr cinfo)
{

		JPG_INTTYPE_E eIntStatus        = JPG_INTTYPE_NONE;
		HI_S32 s32Cnt                    = 0;
		HI_U32 u32ConsumSize            = 0;
		HI_U64 u64LeaveSize             = 0;
		HI_U32 u32AlignSize             = 0;
		HI_U32 u32DecSize               = 0;
		HI_BOOL bStartDec               = HI_TRUE;
		HI_BOOL bUseReturn              = HI_FALSE; /** ʹ�������ۻ� **/
		HI_CHAR* pDataPhyAddr           = NULL;
		HI_CHAR* pDataStartPhyAddr      = NULL;
		HI_CHAR* pDataVirAddr           = NULL;
		HI_CHAR* pSaveStreamPhyAddr     = NULL;
		HI_CHAR* pSaveStreamVirAddr     = NULL;
		HI_CHAR* pSaveStreamEndPhyAddr  = NULL;

		HI_S32 s32Ret = HI_SUCCESS;

		HI_BOOL bReachEOF = HI_FALSE;
		HI_BOOL bNeedContinue = HI_FALSE;
		
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		/**
		** calc the consume stream size
		** CNcomment:����Ӳ��֮ǰ���ĵ�����������ÿ�ζ������ۼ�-4096��ʣ��������� CNend\n
		**/
		if(pJpegHandle->stHDecDataBuf.u32ConsumeDataSize <= pJpegHandle->stHDecDataBuf.u64DataSize)
		{/** ʣ��������ȥcopyȻ����� **/
			u32ConsumSize = pJpegHandle->stHDecDataBuf.u32ConsumeDataSize - cinfo->src->bytes_in_buffer;
			pDataVirAddr  = pJpegHandle->stHDecDataBuf.pDataVirBuf + u32ConsumSize;
			pDataPhyAddr  = pJpegHandle->stHDecDataBuf.pDataPhyBuf + u32ConsumSize;
			u32DecSize    = pJpegHandle->stHDecDataBuf.u64DataSize - u32ConsumSize;
			if(u32DecSize > (HI_U32)(JPGD_HARD_BUFFER))
			{
				pDataStartPhyAddr = (HI_CHAR*)(((unsigned long)pDataPhyAddr + JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN + JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN - 1) & (~(JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN - 1)));
				u32DecSize = (unsigned long)pDataStartPhyAddr - (unsigned long)pDataPhyAddr;
				bUseReturn = HI_TRUE;
			}
			memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,pDataVirAddr,u32DecSize);
			#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
			#else
			s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
			#endif
			if(HI_SUCCESS != s32Ret)
			{
				goto FAIL;
			}
			if(HI_FALSE == bUseReturn)
			{
				pSaveStreamPhyAddr    = pJpegHandle->stHDecDataBuf.pStartBufPhy;
			}
			else
			{/** ʹ�������ۻ� **/
				pSaveStreamPhyAddr = pDataStartPhyAddr;
			}
			pSaveStreamEndPhyAddr = pSaveStreamPhyAddr + pJpegHandle->stHDecDataBuf.s32StreamReturnLen;
			bNeedContinue = HI_TRUE;
			bReachEOF   = HI_FALSE;
		}
		else
		{
			u32ConsumSize = pJpegHandle->stHDecDataBuf.u32ConsumeDataSize - pJpegHandle->stHDecDataBuf.u64DataSize - cinfo->src->bytes_in_buffer;
			u64LeaveSize  = pJpegHandle->stHDecDataBuf.s32StreamReturnLen - ((HI_U64)u32ConsumSize);
	
			pDataPhyAddr          = pJpegHandle->stHDecDataBuf.pStartBufPhy + u32ConsumSize;
			pDataVirAddr          = pJpegHandle->stHDecDataBuf.pDataVirBufReturn + u32ConsumSize;
			pSaveStreamPhyAddr    = pJpegHandle->stHDecDataBuf.pStartBufPhy + u32ConsumSize;
			pSaveStreamVirAddr    = pJpegHandle->stHDecDataBuf.pDataVirBufReturn + u32ConsumSize;
			pSaveStreamEndPhyAddr = pJpegHandle->stHDecDataBuf.pStartBufPhy + pJpegHandle->stHDecDataBuf.s32StreamReturnLen;
			if(0 == (HI_S32)pDataPhyAddr % JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN)
			{
				bNeedContinue = HI_FALSE;
			}
			else
			{
				pSaveStreamPhyAddr = (HI_CHAR*)(((unsigned long)pSaveStreamPhyAddr + 16 + JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN - 1) & (~(JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN - 1)));
				pSaveStreamVirAddr = (HI_CHAR*)(((unsigned long)pSaveStreamVirAddr + 16 + JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN - 1) & (~(JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN - 1)));
				u32AlignSize       = (unsigned long)pSaveStreamPhyAddr - (unsigned long)pDataPhyAddr;
				bNeedContinue = HI_TRUE;
			}
			if(u64LeaveSize <= u32AlignSize)
			{
				u32DecSize  = (HI_U32)u64LeaveSize;
				bReachEOF   = HI_TRUE;
			}
			else
			{
				u32DecSize  = u32AlignSize;
				bReachEOF   = HI_FALSE;
			}

			if(HI_TRUE == bNeedContinue)
			{
				memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,pDataVirAddr,u32DecSize);
				/** ˢ�������� **/
				#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
				s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
				#else
				s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
				#endif
				if(HI_SUCCESS != s32Ret)
				{
					goto FAIL;
				}
			}
		}
		do
		{

			if(HI_TRUE == bStartDec && HI_TRUE == bNeedContinue)
			{
				//JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADDR,(HI_S32 )(pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf - JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN));
				//JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADDR,(HI_S32)(pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf + u32DecSize + JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN));
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (HI_S32)(pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf));
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(HI_S32)(pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf + u32DecSize));
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? JPG_EOF_VALUE : 0x0));
#ifdef CONFIG_JPEG_4KDDR_DISABLE
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
#else
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
#endif

			}
			else if(HI_TRUE == bStartDec && HI_FALSE == bNeedContinue)
			{
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (HI_S32)pSaveStreamPhyAddr);
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(HI_S32)pSaveStreamEndPhyAddr);
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME, 0x2);
#ifdef CONFIG_JPEG_4KDDR_DISABLE
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
#else
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
#endif

			}
			else
			{
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (HI_S32)pSaveStreamPhyAddr);
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(HI_S32)pSaveStreamEndPhyAddr);
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(JPG_EOF_VALUE|JPG_RESUME_VALUE));
			}

			bStartDec  = HI_FALSE;
			bReachEOF  = HI_TRUE;

			eIntStatus = JPG_INTTYPE_ERROR;
			s32Ret = JPEG_HDEC_GetIntStatus(pJpegHandle, &eIntStatus, JPG_INTTYPE_DELAY_TIME);
			if(HI_SUCCESS != s32Ret)
			{
				goto FAIL;
			}
			if(JPG_INTTYPE_ERROR == eIntStatus) 
			{
				goto FAIL;
			}
			else if(JPG_INTTYPE_FINISH == eIntStatus) 
			{  
				break;
			}
			else if(JPG_INTTYPE_CONTINUE == eIntStatus)
			{/** ������������buffer��ַ�Ĵ��� **/
				//JPEG_HDEC_SetStreamBuf(cinfo);
				continue;
			}
			else 
			{
				goto FAIL;
			}

		}while(JPG_INTTYPE_FINISH != eIntStatus);
		
		cinfo->output_scanline        = 0;
		cinfo->global_state           = DSTATE_STOPPING;
		cinfo->inputctl->eoi_reached  = HI_TRUE;
		cinfo->rec_outbuf_height      = 1;
		cinfo->MCUs_per_row           = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)&0xffff;
		cinfo->MCU_rows_in_scan       = ((HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)>>16)&0xffff;
		cinfo->blocks_in_MCU          =  cinfo->num_components;

		for(s32Cnt=0; s32Cnt<cinfo->num_components; s32Cnt++)
		{
			cinfo->MCU_membership[s32Cnt] = s32Cnt;
		}

		s32Ret = JPEG_HDEC_CheckOut(pJpegHandle);
		if(HI_SUCCESS != s32Ret)
		{
			return HI_SUCCESS;
		}

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize && HI_TRUE != pJpegHandle->bDecARGB)
#else
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize)
#endif
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[0],pJpegHandle->stMiddleSurface.pMiddleVir[0],pJpegHandle->stJpegSofInfo.u32YSize);
		}
		if(0 != pJpegHandle->stJpegSofInfo.u32CSize)
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[1],pJpegHandle->stMiddleSurface.pMiddleVir[1],pJpegHandle->stJpegSofInfo.u32CSize);
		}

		return HI_SUCCESS;

		FAIL:
			
		return HI_FAILURE;

}

#else

HI_S32 JPEG_HDEC_SendStreamFromPhyMem(j_decompress_ptr cinfo)
{



		JPG_INTTYPE_E eIntStatus         = JPG_INTTYPE_NONE;
		HI_S32 s32Cnt                    = 0;
		HI_U32 u32ConsumSize             = 0;
		HI_CHAR* pSaveStreamPhyAddr     = NULL;
#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_CHAR* pSaveStreamVirAddr     = NULL;
		HI_U64 u64LeaveSize               = 0;
#endif
		HI_CHAR* pSaveStreamEndPhyAddr  = NULL;

		HI_S32 s32Ret = HI_SUCCESS;

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		/**
		** output the scen message to file
		** CNcomment:�������ֳ� CNend\n
		**/
		if(HI_TRUE == pJpegHandle->bSaveScen)
		{
			HI_JPEG_OpenScenFile(cinfo);
		}
#endif

		/**
		** no alloc the stream buffer, we can set in Makefile about JPGD_HARD_BUFFER
		** CNcomment:��ʱ�����Լ���������buffer�ˣ�������Makefile������JPGD_HARD_BUFFER = 0 CNend\n
		**/

		/**
		** calc the consume stream size
		** CNcomment:����Ӳ��֮ǰ���ĵ�����������ÿ�ζ������ۼ�-4096��ʣ��������� CNend\n
		**/
		if(HI_TRUE == pJpegHandle->stHDecDataBuf.bNeedStreamReturn)
		{
			if(pJpegHandle->stHDecDataBuf.u32ConsumeDataSize <= pJpegHandle->stHDecDataBuf.u64DataSize)
			{
				u32ConsumSize = pJpegHandle->stHDecDataBuf.u32ConsumeDataSize - cinfo->src->bytes_in_buffer;
				pSaveStreamPhyAddr     =   pJpegHandle->stHDecDataBuf.pDataPhyBuf + u32ConsumSize;
				pSaveStreamEndPhyAddr  =   pJpegHandle->stHDecDataBuf.pStartBufPhy + pJpegHandle->stHDecDataBuf.s32StreamReturnLen;
			}
			else
			{
				u32ConsumSize = pJpegHandle->stHDecDataBuf.u32ConsumeDataSize - pJpegHandle->stHDecDataBuf.u64DataSize - cinfo->src->bytes_in_buffer;
				pSaveStreamPhyAddr     =   pJpegHandle->stHDecDataBuf.pStartBufPhy + u32ConsumSize;
				pSaveStreamEndPhyAddr  =   pJpegHandle->stHDecDataBuf.pStartBufPhy + pJpegHandle->stHDecDataBuf.s32StreamReturnLen;
			}
		}
		else
		{
			u32ConsumSize = pJpegHandle->stHDecDataBuf.u32ConsumeDataSize - cinfo->src->bytes_in_buffer;
			pSaveStreamPhyAddr     =   pJpegHandle->stHDecDataBuf.pDataPhyBuf + u32ConsumSize;
			pSaveStreamEndPhyAddr  =   pJpegHandle->stHDecDataBuf.pDataPhyBuf + pJpegHandle->stHDecDataBuf.u64DataSize;
		}
#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		u64LeaveSize       = pJpegHandle->stHDecDataBuf.u64DataSize - ((HI_U64)u32ConsumSize);
		pSaveStreamVirAddr =   pJpegHandle->stHDecDataBuf.pDataVirBuf + u32ConsumSize;
		if(HI_TRUE == pJpegHandle->bSaveScen)
		{/**
		  ** should save scen before start decode
		  ** CNcomment:Ҫ�ڽ�������ǰ�����ֳ�����������ʧ�� CNend\n
		  **/
			HI_JPEG_OutScenData(cinfo,pSaveStreamPhyAddr,pSaveStreamEndPhyAddr,pSaveStreamVirAddr,u64LeaveSize,HI_TRUE);
		}
#endif

#ifdef CONFIG_JPEG_DEBUG_INFO
		if(0 != (HI_S32)pSaveStreamPhyAddr % JPGD_HDEC_MMZ_ALIGN_4BYTES)
		{
			JPEG_TRACE("The stream buffer start address is not 4 bytes align!\n");
			JPEG_TRACE("pSaveStreamPhyAddr = 0x%x\n",(unsigned long)pSaveStreamPhyAddr);
		}
#endif

#ifdef CONFIG_JPEG_TEST_HARD_DEC_CAPA
HARDDEC_TINIT();
HARDDEC_TSTART();
#endif
		/**
		** start the decode, no need resume
		** CNcomment:ֱ���������룬����Ҫ������ CNend\n
		**/
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (unsigned long)(pSaveStreamPhyAddr) & 0xffffffff);
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(unsigned long)(pSaveStreamEndPhyAddr) & 0xffffffff);
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME, 0x2);
		#ifdef CONFIG_JPEG_4KDDR_DISABLE
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
		#else
		JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
		#endif

		eIntStatus = JPG_INTTYPE_ERROR;
		s32Ret = JPEG_HDEC_GetIntStatus(pJpegHandle, &eIntStatus, JPG_INTTYPE_DELAY_TIME);
		if(HI_SUCCESS != s32Ret)
		{
			goto FAIL;
		}

		if(JPG_INTTYPE_FINISH == eIntStatus) 
		{
			/** do nothing **/
		}
		else 
		{
			goto FAIL;
		}

#ifdef CONFIG_JPEG_TEST_HARD_DEC_CAPA
HARDDEC_TEND();
#endif
		cinfo->output_scanline        = 0;
		cinfo->global_state           = DSTATE_STOPPING;
		cinfo->inputctl->eoi_reached  = HI_TRUE;
		cinfo->rec_outbuf_height      = 1;
		cinfo->MCUs_per_row           = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)&0xffff;
		cinfo->MCU_rows_in_scan       = ((HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)>>16)&0xffff;
		cinfo->blocks_in_MCU          =  cinfo->num_components;

		for(s32Cnt=0; s32Cnt<cinfo->num_components; s32Cnt++)
		{
			cinfo->MCU_membership[s32Cnt] = s32Cnt;
		}

		s32Ret = JPEG_HDEC_CheckOut(pJpegHandle);
		if(HI_SUCCESS != s32Ret)
		{
			#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			HI_JPEG_CloseScenFile(cinfo);
			#endif
			return HI_SUCCESS;
		}
		
#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize && HI_TRUE != pJpegHandle->bDecARGB)
#else
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize)
#endif
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[0],pJpegHandle->stMiddleSurface.pMiddleVir[0],pJpegHandle->stJpegSofInfo.u32YSize);
		}
		if(0 != pJpegHandle->stJpegSofInfo.u32CSize)
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[1],pJpegHandle->stMiddleSurface.pMiddleVir[1],pJpegHandle->stJpegSofInfo.u32CSize);
		}

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_JPEG_CloseScenFile(cinfo);
#endif

		return HI_SUCCESS;

	FAIL:

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		if(HI_TRUE == pJpegHandle->bSaveScen)
		{
			HI_JPEG_CloseScenFile(cinfo);
		}
#endif
		return HI_FAILURE;

}

#endif  /** CONFIG_JPEG_STREAMBUF_4ALIGN **/


/*****************************************************************************
* func			: JPEG_HDEC_SendStreamFromVirMem
* description	: get the stream from virtual memory
                  CNcomment:  ������Դ�����ڴ�Ĵ���ʽ   CNend\n
* param[in]     : cinfo       CNcomment:  �������     CNend\n
* retval	    : HI_SUCCESS  CNcomment:  �ɹ�         CNend\n
* retval	    : HI_FAILURE  CNcomment:  ʧ��         CNend\n
* others:	    : NA
*****************************************************************************/
HI_S32 JPEG_HDEC_SendStreamFromVirMem(j_decompress_ptr cinfo)
{
         

		JPG_INTTYPE_E eIntStatus = JPG_INTTYPE_NONE;
		HI_BOOL bReachEOF         = HI_FALSE;
		HI_BOOL bStartDec         = HI_FALSE;
		HI_S32  s32Cnt            = 0;

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_BOOL bStartFirst = HI_TRUE;
#endif

		HI_BOOL bResumeOk       =  HI_FALSE;
#ifdef CONFIG_JPEG_SUSPEND
		HI_U32 u32ResumeSize    = 0;
#endif
		HI_U32 u32ReadDataSize  = 0;
		/**
		 ** the continue stream size should big than 16bytes
		 ** CNcomment:ÿһ���������������16���ֽڣ����� CNend\n
		 **/
		HI_U32 u32NeedDecCnt		       = 0;
		HI_U32 u32ConsumSize              = 0;
		HI_U64 u64LeaveSize               = 0;
		HI_U32 u32TotalSize               = 0;
		HI_CHAR* pDataVirAddr             = NULL;
		HI_CHAR* pSaveStreamStartPhyAddr = NULL;
		HI_CHAR* pSaveStreamEndPhyAddr   = NULL;

        HI_S32 s32Ret = HI_SUCCESS;

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
		HI_CHAR pRegister[256] = {0};
#endif

#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
		HI_BOOL bSendSuspendSignal = HI_FALSE;
		HI_BOOL bSuspendStart		= HI_FALSE;
#endif

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

#ifdef CONFIG_JPEG_MMU_SUPPORT
		HI_BOOL bMemMMUType  = HI_FALSE;
#endif

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		/**
		 ** output the scen message to file
		 ** CNcomment:�������ֳ� CNend\n
		 **/
		if(HI_TRUE == pJpegHandle->bSaveScen)
		{
			HI_JPEG_OpenScenFile(cinfo);
		}
#endif

		/**
		** tell the hard the stream is end.
		** CNcomment:����Ǳ���ģ�Ҫ����Ӳ�������Ѿ������ˣ�����Ӳ����һֱ��
		**           Ӳ����ʡ�޷��ж϶��������� CNend\n
		**/
		bReachEOF = HI_FALSE;

		u32ReadDataSize = JPGD_STREAM_BUFFER;
		u32ConsumSize   = pJpegHandle->stHDecDataBuf.u32ConsumeDataSize - cinfo->src->bytes_in_buffer;
        u64LeaveSize    = pJpegHandle->stHDecDataBuf.u64DataSize - ((HI_U64)u32ConsumSize);
		pDataVirAddr    = pJpegHandle->stHDecDataBuf.pDataVirBuf + u32ConsumSize;
		pSaveStreamStartPhyAddr = pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf;

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
		snprintf(pRegister,256,"himd.l 0x%x",JPGD_REG_BASEADDR);
		JPEG_TRACE("00���븴λ\n");
		ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
		usleep(10);
		system(pRegister);
#endif

		do {
			/**
			** the consume stream size
			** CNcomment:���ĵ������� CNend\n
			**/
#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
			if(HI_TRUE == bSendSuspendSignal && HI_FALSE == bSuspendStart)
			{
				JPEG_TRACE("send resume signal\n");
				HI_JPEG_Resume(pJpegHandle->s32JpegDev,&bSendSuspendSignal);
				bSuspendStart = HI_TRUE;
				JPEG_TRACE("send resume signal finish\n");
			}
#endif

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			JPEG_TRACE("11���븴λ\n");
			ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
			usleep(10);
			system(pRegister);
#endif
			JPEG_HDEC_SuspendDispose(cinfo,&bResumeOk);

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			JPEG_TRACE("22���븴λ\n");
			ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
			usleep(10);
			system(pRegister);
#endif

#ifdef CONFIG_JPEG_SUSPEND
			if(HI_TRUE == bResumeOk)
			{
			  /**
			   ** the consume stream size
			   ** CNcomment:���ĵ������� CNend\n
			   **/
			   u32ResumeSize = u32NeedDecCnt - pJpegHandle->u32ResByteConsum;
			   memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,    \
			   	      pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf + pJpegHandle->u32ResByteConsum,\
			   	      u32ResumeSize);
			   
			   u32NeedDecCnt = u32ResumeSize;
			   if(u32ResumeSize < 16 && HI_FALSE == bReachEOF)
			   {
			      /**
			   	   ** the consume stream size
			       ** CNcomment:�������һ֡��������Ӳ����Ҫ���������� CNend\n
			       **/
			       memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf + u32ResumeSize, \
			              (pDataVirAddr + u32TotalSize),                                \
			              (u32ReadDataSize - u32ResumeSize));

				  u32TotalSize += (u32ReadDataSize - u32ResumeSize);
				  u32NeedDecCnt = u32ReadDataSize;
			   }
			   
			}
			else
#endif
			{
				u32NeedDecCnt  = u32ReadDataSize < ((HI_U32)u64LeaveSize - u32TotalSize) ? u32ReadDataSize : ((HI_U32)u64LeaveSize - u32TotalSize);
				memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf, (pDataVirAddr + u32TotalSize),u32NeedDecCnt);
				u32TotalSize  += u32NeedDecCnt;
			}


			if(u32TotalSize >= u64LeaveSize)
			{
				 bReachEOF = HI_TRUE;
			}
			if( (0xFF == (HI_UCHAR)pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf[0]) \
			 && (0xD9 == (HI_UCHAR)pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf[1]))
			{
			   /**
			    ** strengthen the condition check
			    ** CNcomment:��ǿ�����ж� CNend\n
			    **/
			    bReachEOF = HI_TRUE;
			}
						
			/** ˢ�������� **/
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
#else
	#ifdef CONFIG_JPEG_MMU_SUPPORT
			if (pJpegHandle->u32MemTypeMask & JPEG_STREAM_MEM_MMU_TYPE)
				bMemMMUType  = HI_TRUE;
			s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, bMemMMUType);
	#else
			s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
	#endif
#endif
			if(HI_SUCCESS != s32Ret)
			{
			   	goto FAIL;
			}

			pSaveStreamEndPhyAddr   = (HI_CHAR *)((unsigned long)pSaveStreamStartPhyAddr + u32NeedDecCnt);

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			JPEG_TRACE("33���븴λ\n");
			ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
			usleep(10);
			system(pRegister);
#endif


#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			if(HI_TRUE == pJpegHandle->bSaveScen)
			{/**
		  	  ** should save scen before start decode
		      ** CNcomment:Ҫ�ڽ�������ǰ�����ֳ�����������ʧ�� CNend\n
		      **/
				HI_JPEG_OutScenData(cinfo,pSaveStreamStartPhyAddr,pSaveStreamEndPhyAddr,pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,(HI_U64)u32NeedDecCnt,bStartFirst);
				bStartFirst = HI_FALSE;
			}
#endif

			JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (unsigned long)pSaveStreamStartPhyAddr);
			JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(unsigned long)pSaveStreamEndPhyAddr);


#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			JPEG_TRACE("44���븴λ\n");
			ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
			usleep(10);
			system(pRegister);
#endif

#ifdef CONFIG_JPEG_SUSPEND
			if(HI_FALSE == bStartDec || HI_TRUE == bResumeOk)
#else
	        if(HI_FALSE == bStartDec)
#endif
			{ 
				 /**
				  ** strengthen the condition check
				  ** CNcomment:�Ƿ�Ϊ��ǰ֡�����һ�����롣0�����ǣ�1���� CNend\n
				  **/
				  JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? JPG_EOF_VALUE : 0x0));
				  #ifdef CONFIG_JPEG_4KDDR_DISABLE
				  JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
				  #else
				  JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
				  #endif
				  bStartDec  = HI_TRUE;
				  bResumeOk  = HI_FALSE;
			       
			}
			else
			{
			  	JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? (JPG_EOF_VALUE|JPG_RESUME_VALUE) : JPG_RESUME_VALUE));
			}

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			JPEG_TRACE("55���븴λ\n");
			ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
			usleep(10);
			system(pRegister);
#endif

			eIntStatus = JPG_INTTYPE_ERROR;
			s32Ret = JPEG_HDEC_GetIntStatus(pJpegHandle, &eIntStatus, JPG_INTTYPE_DELAY_TIME);
			if(JPG_INTTYPE_ERROR == eIntStatus) 
			{
				goto FAIL;
			}
			else if(JPG_INTTYPE_FINISH == eIntStatus) 
			{
				break;	
			}
			else if(JPG_INTTYPE_CONTINUE == eIntStatus)
			{
				JPEG_HDEC_SuspendDispose(cinfo,&bResumeOk);
#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
				if(HI_FALSE == bSendSuspendSignal && HI_FALSE == bSuspendStart)
				{
					JPEG_TRACE("send suspend signal\n");
					HI_JPEG_Suspend(pJpegHandle->s32JpegDev,&bSendSuspendSignal);
					JPEG_TRACE("send suspend signal finish\n");
				}
#endif
#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
				JPEG_TRACE("66���븴λ\n");
				ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
				usleep(10);
				system(pRegister);
#endif
				continue;
				 
			}
			else 
			{
				goto FAIL;
			}
			

		} while (JPG_INTTYPE_FINISH != eIntStatus);

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
		JPEG_TRACE("77���븴λ\n");
		ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
		usleep(10);
		system(pRegister);
#endif

		cinfo->output_scanline        = 0;
		cinfo->global_state           = DSTATE_STOPPING;
		cinfo->inputctl->eoi_reached  = HI_TRUE;
		cinfo->rec_outbuf_height      = 1;
		cinfo->MCUs_per_row           = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)&0xffff;
		cinfo->MCU_rows_in_scan       = ((HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)>>16)&0xffff;
		cinfo->blocks_in_MCU          =  cinfo->num_components;

		for(s32Cnt=0; s32Cnt<cinfo->num_components; s32Cnt++)
		{
		   cinfo->MCU_membership[s32Cnt] = s32Cnt;
		}

		s32Ret = JPEG_HDEC_CheckOut(pJpegHandle);
		if(HI_SUCCESS != s32Ret)
		{
			#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			HI_JPEG_CloseScenFile(cinfo);
			#endif
			return HI_SUCCESS;
		}

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize && HI_TRUE != pJpegHandle->bDecARGB)
#else
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize)
#endif
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[0],pJpegHandle->stMiddleSurface.pMiddleVir[0],pJpegHandle->stJpegSofInfo.u32YSize);
		}
		if(0 != pJpegHandle->stJpegSofInfo.u32CSize)
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[1],pJpegHandle->stMiddleSurface.pMiddleVir[1],pJpegHandle->stJpegSofInfo.u32CSize);
		}

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
		JPEG_TRACE("88���븴λ\n");
		ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
		usleep(10);
		system(pRegister);
#endif

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_JPEG_CloseScenFile(cinfo);
#endif

		return HI_SUCCESS;

		/** if decode failure jump here **/
		FAIL:

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			HI_JPEG_CloseScenFile(cinfo);
#endif

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			 JPEG_TRACE("99���븴λ\n");
			 ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
			 usleep(10);
			 system(pRegister);
#endif

			 return HI_FAILURE;
		  
}


/*****************************************************************************
* func			: JPEG_HDEC_SendStreamFromFile
* description	: CNcomment:  ������Դ�ļ�
* param[in] 	: cinfo 	  CNcomment:  �������
* param[in] 	: NA
* retval		: HI_SUCCESS  CNcomment:  �ɹ�
* retval		: HI_FAILURE  CNcomment:  ʧ��
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_SendStreamFromFile(j_decompress_ptr cinfo)
{
         

		JPG_INTTYPE_E eIntStatus = JPG_INTTYPE_NONE;
		HI_BOOL bRetVal           = HI_FALSE;
		HI_BOOL bReachEOF         = HI_FALSE;
		HI_BOOL bStartDec         = HI_FALSE;
		HI_S32  s32Cnt            = 0;

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_BOOL bStartFirst = HI_TRUE;
#endif
		HI_BOOL bResumeOk       =  HI_FALSE;
		HI_U32 u32ReadDataSize  = 0;
		HI_U32 u32ResumeSize	= 0;
		/**
		** the continue stream size should big than 16bytes
		** CNcomment:ÿһ���������������16���ֽڣ����� CNend\n
		**/
		HI_U32 u32NeedDecCnt		   = 0;
		HI_CHAR* pStreamStartPhyAddr   = NULL;
		HI_CHAR* pStreamStartVirAddr   = NULL;
		HI_CHAR* pStreamEndPhyAddr     = NULL;

		HI_S32 s32Ret = HI_SUCCESS;

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
		HI_CHAR pRegister[256] = {0};
#endif

#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
		HI_BOOL bSendSuspendSignal = HI_FALSE;
		HI_BOOL bSuspendStart       = HI_FALSE;
#endif

        my_src_ptr src = (my_src_ptr)cinfo->src;
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

#ifdef CONFIG_JPEG_MMU_SUPPORT
		HI_BOOL bMemMMUType  = HI_FALSE;
#endif

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		/**
		** output the scen message to file
		** CNcomment:�������ֳ� CNend\n
		**/
		if(HI_TRUE == pJpegHandle->bSaveScen)
		{
			HI_JPEG_OpenScenFile(cinfo);
		}
#endif

		pJpegHandle->u32CurrentOffset = (HI_U32)ftell(src->infile);
        pJpegHandle->u32CurrentOffset = pJpegHandle->u32CurrentOffset - cinfo->src->bytes_in_buffer;


#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
        snprintf(pRegister,256,"himd.l 0x%x",JPGD_REG_BASEADDR);
		if(0 == sg_s32ResetNum)
		{
			JPEG_TRACE("sg_s32ResetNum = 0 ��λ\n");
			ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
			usleep(10);
			system(pRegister);
		}
#endif
		/**
		** tell the hard the stream is end.
		** CNcomment:����Ǳ���ģ�Ҫ����Ӳ�������Ѿ������ˣ�����Ӳ����һֱ��
		**           Ӳ����ʡ�޷��ж϶��������� CNend\n
		**/
		bReachEOF = HI_FALSE;

		pStreamStartVirAddr = pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf;
		u32ReadDataSize     = pJpegHandle->stHDecDataBuf.u32ReadDataSize;

	   /**
		** if suspend happen before hard decode,here not deal with this instance.
		** because this instance should check whether is suspend and set para again.
		** it cost many times.it can return to soft decode,just ok to see the show.
		** CNcomment:����ǽ���֮ǰ���д���������Ͳ��������ˣ���Ϊ���ʱ�䣬Ӳ������Ҫ��ʧ��
		**           ���Զ��˻�������룬��������������ʾ CNend\n
		**/
	    do {
			/**
			** the consume stream size
			** CNcomment:���ĵ������� CNend\n
			**/
#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
			if(HI_TRUE == bSendSuspendSignal && HI_FALSE == bSuspendStart)
			{
				JPEG_TRACE("send resume signal\n");
				HI_JPEG_Resume(pJpegHandle->s32JpegDev,&bSendSuspendSignal);
				bSuspendStart = HI_TRUE;
				JPEG_TRACE("send resume signal finish\n");
			}
#endif

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			if(1 == sg_s32ResetNum)
			{
				JPEG_TRACE("sg_s32ResetNum = 1 ��λ\n");
				ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
				usleep(10);
				system(pRegister);
			}
#endif

			JPEG_HDEC_SuspendDispose(cinfo,&bResumeOk);

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			if(2 == sg_s32ResetNum)
			{
				JPEG_TRACE("sg_s32ResetNum = 2 ��λ\n");
				ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
				usleep(10);
				system(pRegister);
			}
#endif

#ifdef CONFIG_JPEG_SUSPEND
			if(HI_TRUE == bResumeOk)
			{
				/**
				** the consume stream size
				** CNcomment:���ĵ������� CNend\n
				**/
				u32ResumeSize = u32NeedDecCnt - pJpegHandle->u32ResByteConsum;
				memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,    \
					   pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf + pJpegHandle->u32ResByteConsum,\
					   u32ResumeSize);
			}
#endif
			if(0 != cinfo->src->bytes_in_buffer)
			{
				/**
				** copy the leave stream to save stream buffer and start decode
				** CNcomment:����ʣ������������buffer�У�Ȼ���������� CNend\n
				**/
				u32NeedDecCnt = cinfo->src->bytes_in_buffer;
				memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,   \
				(char*)cinfo->src->next_input_byte,	   \
				u32NeedDecCnt);
				if(	  (0xFF == (*(cinfo->src->next_input_byte + u32NeedDecCnt - 2)))
					&&(0xD9 == (*(cinfo->src->next_input_byte + u32NeedDecCnt - 1))))
				{
					bReachEOF = HI_TRUE;
				}
				else
				{
					pJpegHandle->stHDecDataBuf.bReadToDataBuf  = HI_TRUE;
					pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf = pStreamStartVirAddr + u32NeedDecCnt;

					pJpegHandle->stHDecDataBuf.u32ReadDataSize = \
					pJpegHandle->stHDecDataBuf.u32ReadDataSize - u32NeedDecCnt;

					bRetVal = (*cinfo->src->fill_input_buffer)(cinfo);/*lint !e64 ignore by y00181162, because return value is ok */  
					if(HI_FALSE == bRetVal)
					{
						goto FAIL;
					}

					u32NeedDecCnt = u32NeedDecCnt + cinfo->src->bytes_in_buffer;

					/** ��ԭ�����׵�ַ **/
					pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf     = pStreamStartVirAddr;
					pJpegHandle->stHDecDataBuf.u32ReadDataSize = u32ReadDataSize;
				}

			}

			if(0 == cinfo->src->bytes_in_buffer)
			{
 
				/**
				** there is not stream,should read data to save stream buffer
				** CNcomment:û�������ˣ���Ҫ����������ʱ��ֱ�Ӷ�������С�ֽڵ�����buffer�� CNend\n
				**/
				pJpegHandle->stHDecDataBuf.bReadToDataBuf  = HI_TRUE;
				pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf = pStreamStartVirAddr + u32ResumeSize;
				pJpegHandle->stHDecDataBuf.u32ReadDataSize = pJpegHandle->stHDecDataBuf.u32ReadDataSize - u32ResumeSize;
				bRetVal = (*cinfo->src->fill_input_buffer)(cinfo); /*lint !e64 ignore by y00181162, because return value is ok */  
				if(HI_FALSE == bRetVal)
				{
					goto FAIL;
				}
				u32NeedDecCnt = u32ResumeSize + cinfo->src->bytes_in_buffer;
				pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf  = pStreamStartVirAddr;
				pJpegHandle->stHDecDataBuf.u32ReadDataSize    = u32ReadDataSize;

			}
			if(HI_TRUE == bStartDec && u32NeedDecCnt < pJpegHandle->stHDecDataBuf.u32ReadDataSize)
			{
				bReachEOF = HI_TRUE;
			}

			if(  (0xFF == (HI_UCHAR)pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf[0]) \
			  && (0xD9 == (HI_UCHAR)pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf[1]) \
			  && (2 == cinfo->src->bytes_in_buffer))
			{
				/**
				** strengthen the condition check
				** CNcomment:��ǿ�����ж� CNend\n
				**/
				bReachEOF = HI_TRUE;
			}

			/**
			** dinit the para
			** CNcomment:ȥ��ʼ����ر��� CNend\n
			**/
			u32ResumeSize = 0;
			cinfo->src->bytes_in_buffer = 0;

			/** ˢ�������� **/
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
#else
		#ifdef CONFIG_JPEG_MMU_SUPPORT
			if (pJpegHandle->u32MemTypeMask & JPEG_STREAM_MEM_MMU_TYPE)
				bMemMMUType  = HI_TRUE;
			s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, bMemMMUType);
		#else

			s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
		#endif
#endif
			if(HI_SUCCESS != s32Ret)
			{
				goto FAIL;
			}


			pStreamStartPhyAddr = pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf;
			pStreamEndPhyAddr   = pStreamStartPhyAddr + u32NeedDecCnt;

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			if(HI_TRUE == pJpegHandle->bSaveScen)
			{/**
			** should save scen before start decode
			** CNcomment:Ҫ�ڽ�������ǰ�����ֳ�����������ʧ�� CNend\n
			**/
				HI_JPEG_OutScenData(cinfo,pStreamStartPhyAddr,pStreamEndPhyAddr,pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,(HI_U64)u32NeedDecCnt,bStartFirst);
				bStartFirst = HI_FALSE;
			}
#endif

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			if(3 == sg_s32ResetNum)
			{
				JPEG_TRACE("sg_s32ResetNum = 3 ��λ\n");
				ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
				usleep(10);
				system(pRegister);
			}
#endif

			JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (unsigned long)pStreamStartPhyAddr);
			JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(unsigned long)pStreamEndPhyAddr);

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			if(4 == sg_s32ResetNum)
			{
				JPEG_TRACE("sg_s32ResetNum = 4 ��λ\n");
				ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
				usleep(10);
				system(pRegister);
			}
#endif

#ifdef CONFIG_JPEG_SUSPEND
			if(HI_FALSE == bStartDec || HI_TRUE == bResumeOk)
#else
			if(HI_FALSE == bStartDec)
#endif
			{ 
				/**
				** strengthen the condition check
				** CNcomment:�Ƿ�Ϊ��ǰ֡�����һ�����롣0�����ǣ�1���� CNend\n
				**/
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? JPG_EOF_VALUE : 0x0));
				#ifdef CONFIG_JPEG_4KDDR_DISABLE
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
				#else
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
				#endif
				bStartDec  = HI_TRUE;
				bResumeOk  = HI_FALSE;
			}
			else
			{
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? (JPG_EOF_VALUE|JPG_RESUME_VALUE) : JPG_RESUME_VALUE));
			}

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			if(5 == sg_s32ResetNum)
			{
				JPEG_TRACE("sg_s32ResetNum = 5 ��λ\n");
				ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
				usleep(10);
				system(pRegister);
			}
#endif

			eIntStatus = JPG_INTTYPE_ERROR;

#ifdef CONFIG_JPEG_TEST_CHIP_RANDOM_RESET
			/** ��λ���Գ�ʱ����̫�� **/
			JPEG_TRACE("the waite up time is 1000ms\n");
			s32Ret = JPEG_HDEC_GetIntStatus(pJpegHandle, &eIntStatus, 1000);
			JPEG_TRACE("waite up now\n");
#else
			s32Ret = JPEG_HDEC_GetIntStatus(pJpegHandle, &eIntStatus, JPG_INTTYPE_DELAY_TIME);
#endif
			if(JPG_INTTYPE_ERROR == eIntStatus) 
			{
				goto FAIL;
			}
			else if(JPG_INTTYPE_FINISH == eIntStatus) 
			{
				break;
			}
			else if(JPG_INTTYPE_CONTINUE == eIntStatus)
			{
				JPEG_HDEC_SuspendDispose(cinfo,&bResumeOk);
#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
				if(HI_FALSE == bSendSuspendSignal && HI_FALSE == bSuspendStart)
				{
					JPEG_TRACE("send suspend signal\n");
					HI_JPEG_Suspend(pJpegHandle->s32JpegDev,&bSendSuspendSignal);
					JPEG_TRACE("send suspend signal finish\n");
				}
				/** ע�����﷢��������ʱ��Ҫ�ڿ�ʼ����һ���ж� **/
#endif
#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
				if(6 == sg_s32ResetNum)
				{
					JPEG_TRACE("sg_s32ResetNum = 6 ��λ\n");
					ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
					usleep(10);
					system(pRegister);
				}
#endif
				continue;

			}
			else 
			{
				goto FAIL;
			}


		} while (JPG_INTTYPE_FINISH != eIntStatus);

		cinfo->output_scanline        = 0;
		cinfo->global_state           = DSTATE_STOPPING;
		cinfo->inputctl->eoi_reached  = HI_TRUE;
		cinfo->rec_outbuf_height      = 1;
		cinfo->MCUs_per_row           = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)&0xffff;
		cinfo->MCU_rows_in_scan       = ((HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)>>16)&0xffff;
		cinfo->blocks_in_MCU          =  cinfo->num_components;

		for(s32Cnt=0; s32Cnt<cinfo->num_components; s32Cnt++)
		{
			cinfo->MCU_membership[s32Cnt] = s32Cnt;
		}

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
		if(7 == sg_s32ResetNum)
		{
			JPEG_TRACE("sg_s32ResetNum = 7 ��λ\n");
			ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
			usleep(10);
			system(pRegister);
		}
#endif


#if defined(CONFIG_JPEG_TEST_SAVE_BMP_PIC) && defined(CONFIG_JPEG_HARDDEC2ARGB)
		if(HI_TRUE == pJpegHandle->bDecARGB)
		{
			HI_JPEG_SaveBmp((unsigned long)pJpegHandle->stMiddleSurface.pMiddlePhy[0],  \
			                  (HI_U32)pJpegHandle->stOutDesc.stCropRect.w,         \
			                  (HI_U32)pJpegHandle->stOutDesc.stCropRect.h,         \
			                  pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0], \
			                  cinfo);
		}
#endif

		s32Ret = JPEG_HDEC_CheckOut(pJpegHandle);
		if(HI_SUCCESS != s32Ret)
		{
			#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			HI_JPEG_CloseScenFile(cinfo);
			#endif
			return HI_SUCCESS;
		}

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize && HI_TRUE != pJpegHandle->bDecARGB)
#else
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize)
#endif
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[0],pJpegHandle->stMiddleSurface.pMiddleVir[0],pJpegHandle->stJpegSofInfo.u32YSize);
		}
		if(0 != pJpegHandle->stJpegSofInfo.u32CSize)
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[1],pJpegHandle->stMiddleSurface.pMiddleVir[1],pJpegHandle->stJpegSofInfo.u32CSize);
		}

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
		if(8 == sg_s32ResetNum)
		{
			JPEG_TRACE("sg_s32ResetNum = 8 ��λ\n");
			ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
			usleep(10);
			system(pRegister);
		}
		sg_s32ResetNum++;
		if(sg_s32ResetNum > 10)
		{
			sg_s32ResetNum = 0;
		}
#endif


#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_JPEG_CloseScenFile(cinfo);
#endif


		return HI_SUCCESS;

		/** if decode failure jump here **/
		FAIL:

			 cinfo->src->bytes_in_buffer  = 0;
			 /**
			  ** change the read stream dispose
			  ** CNcomment:Ӳ������ʧ��֮�������������ԭ������·�� CNend\n
			  **/
			 pJpegHandle->stHDecDataBuf.bReadToDataBuf  = HI_FALSE;

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			 HI_JPEG_CloseScenFile(cinfo);
#endif

#ifdef CONFIG_JPEG_TEST_ALL_DEC_RANDOM_RESET
			if(9 == sg_s32ResetNum)
			{
				JPEG_TRACE("sg_s32ResetNum = 9 ��λ\n");
				ioctl(pJpegHandle->s32JpegDev, CMD_JPG_RESET);
				usleep(10);
				system(pRegister);
			}
			sg_s32ResetNum++;
			if(sg_s32ResetNum > 10)
			{
				sg_s32ResetNum = 0;
			}
#endif

			 return HI_FAILURE;
		  
}
/*****************************************************************************
* func			: JPEG_HDEC_SendStreamFromCallBack
* description	: CNcomment:  ������Դ�ⲿ����
* param[in] 	: cinfo 	  CNcomment:  �������
* param[in] 	: NA
* retval		: HI_SUCCESS  CNcomment:  �ɹ�
* retval		: HI_FAILURE  CNcomment:  ʧ��
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_SendStreamFromCallBack(j_decompress_ptr cinfo)
{
         

		JPG_INTTYPE_E eIntStatus = JPG_INTTYPE_NONE;
		HI_BOOL bReachEOF         = HI_FALSE;
		HI_BOOL bStartDec         = HI_FALSE;
		HI_S32  s32Cnt            = 0;
		HI_BOOL bRetVal           = HI_TRUE;
		HI_S32  s32ByteInBuffer   = 0;
#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_BOOL bStartFirst = HI_TRUE;
#endif

		HI_BOOL bResumeOk       =  HI_FALSE;
		HI_U32 u32ReadDataSize  = 0;
		/**
		** the continue stream size should big than 16bytes
		** CNcomment:ÿһ���������������16���ֽڣ����� CNend\n
		**/
		HI_U32 u32ReadSize            = 0; /** every times read data bytes **/
		HI_U32 u32ReadPos             = 0;
		HI_U32 u32NeedDecCnt		   = 0;
		HI_CHAR* pStreamStartPhyAddr = NULL;
		HI_CHAR* pStreamStartVirAddr = NULL;
		HI_CHAR* pStreamEndPhyAddr   = NULL;

		HI_S32 s32Ret = HI_SUCCESS;

#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
		HI_BOOL bSendSuspendSignal = HI_FALSE;
		HI_BOOL bSuspendStart		= HI_FALSE;
#endif

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

#ifdef CONFIG_JPEG_MMU_SUPPORT
		HI_BOOL bMemMMUType  = HI_FALSE;
#endif

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		/**
		** output the scen message to file
		** CNcomment:�������ֳ� CNend\n
		**/
		if(HI_TRUE == pJpegHandle->bSaveScen)
		{
			HI_JPEG_OpenScenFile(cinfo);
		}
#endif

		/**
		** tell the hard the stream is end.
		** CNcomment:����Ǳ���ģ�Ҫ����Ӳ�������Ѿ������ˣ�����Ӳ����һֱ��
		**           Ӳ����ʡ�޷��ж϶��������� CNend\n
		**/
		bReachEOF = HI_FALSE;
        pJpegHandle->bFirstContinueStream = HI_TRUE;/** Ĭ���������� **/
        
		pStreamStartVirAddr = pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf;
		u32ReadDataSize     = pJpegHandle->stHDecDataBuf.u32ReadDataSize;

#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
		pJpegHandle->u32CurrentOffset = cinfo->src->current_offset - cinfo->src->bytes_in_buffer;
#endif

		s32ByteInBuffer = cinfo->src->bytes_in_buffer;
		do 
		{/** decode continue stream **/

			/**
			** the consume stream size
			** CNcomment:���ĵ������� CNend\n
			**/
#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
			if(HI_TRUE == bSendSuspendSignal && HI_FALSE == bSuspendStart)
			{
				JPEG_TRACE("send resume signal\n");
				HI_JPEG_Resume(pJpegHandle->s32JpegDev,&bSendSuspendSignal);
				bSuspendStart = HI_TRUE;
				JPEG_TRACE("send resume signal finish\n");
			}
#endif
			JPEG_HDEC_SuspendDispose(cinfo,&bResumeOk);
			
#ifdef CONFIG_JPEG_SUSPEND
			if(HI_TRUE == bResumeOk)
			{
				/**
				** the consume stream size
				** CNcomment:���ĵ������� CNend\n
				**/
				u32NeedDecCnt = u32ReadDataSize - pJpegHandle->u32ResByteConsum;
				memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,	\
				pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf + pJpegHandle->u32ResByteConsum,\
				u32NeedDecCnt);
			}
#endif
			do
			{/** read stream data till as 1M bytes **/

				u32ReadSize = 0;
				if (0 == cinfo->src->bytes_in_buffer)
				{
					bRetVal = (*cinfo->src->fill_input_buffer)(cinfo);
					if (0==cinfo->src->bytes_in_buffer)
					{
						break;
					}
					u32ReadPos = 0; /** when read stream, is zero **/
				}
				if (cinfo->src->bytes_in_buffer <= (u32ReadDataSize - u32NeedDecCnt))
				{
					u32ReadSize = cinfo->src->bytes_in_buffer;
				}
				else
				{
					u32ReadSize = u32ReadDataSize - u32NeedDecCnt;
				}
				memcpy(pStreamStartVirAddr + u32NeedDecCnt, (char*)cinfo->src->next_input_byte+u32ReadPos, u32ReadSize);

				u32ReadPos    += u32ReadSize;
				u32NeedDecCnt += u32ReadSize;
				cinfo->src->bytes_in_buffer -= u32ReadSize;

			} while (u32NeedDecCnt < u32ReadDataSize);
            
            pJpegHandle->s32ContinueSize = u32NeedDecCnt;

			bReachEOF = HI_TRUE;
			if (cinfo->src->bytes_in_buffer) 
			{
				bReachEOF = HI_FALSE;
			}
			else
			{/** is last stream data **/
				bRetVal = cinfo->src->fill_input_buffer(cinfo);
				if (cinfo->src->bytes_in_buffer)
				{
					bReachEOF = HI_FALSE;
				}

			}
			if(HI_FALSE == bRetVal && 0XFF != pStreamStartVirAddr[u32NeedDecCnt - 2] && 0XD9 != pStreamStartVirAddr[u32NeedDecCnt - 1])
			{/** ���������������������������û��ʵ�����Ĺ��� **/
			    //pJpegHandle->bFillInput  = HI_FALSE;
				//goto FAIL;
			}
			
			/** ˢ�������� **/
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
#else
		#ifdef CONFIG_JPEG_MMU_SUPPORT
			if (pJpegHandle->u32MemTypeMask & JPEG_STREAM_MEM_MMU_TYPE)
				bMemMMUType  = HI_TRUE;
			s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, bMemMMUType);
		#else
			s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
		#endif
#endif
			if(HI_SUCCESS != s32Ret)
			{
				goto FAIL;
			}


			pStreamStartPhyAddr = pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf;
			pStreamEndPhyAddr   = pStreamStartPhyAddr + u32NeedDecCnt;

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			if(HI_TRUE == pJpegHandle->bSaveScen)
			{	/**
				** should save scen before start decode
				** CNcomment:Ҫ�ڽ�������ǰ�����ֳ�����������ʧ�� CNend\n
				**/
				HI_JPEG_OutScenData(cinfo,pStreamStartPhyAddr,pStreamEndPhyAddr,pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,(HI_U64)u32NeedDecCnt,bStartFirst);
				bStartFirst = HI_FALSE;
			}
#endif

			JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (unsigned long)pStreamStartPhyAddr);
			JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(unsigned long)pStreamEndPhyAddr);

			u32NeedDecCnt = 0;

#ifdef CONFIG_JPEG_SUSPEND
			if(HI_FALSE == bStartDec || HI_TRUE == bResumeOk)
#else
			if(HI_FALSE == bStartDec)
#endif
			{ 
				/**
				** strengthen the condition check
				** CNcomment:�Ƿ�Ϊ��ǰ֡�����һ�����롣0�����ǣ�1���� CNend\n
				**/
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? JPG_EOF_VALUE : 0x0));
				#ifdef CONFIG_JPEG_4KDDR_DISABLE
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
				#else
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
				#endif
				bStartDec  = HI_TRUE;
				bResumeOk  = HI_FALSE;
			}
			else
			{
			    pJpegHandle->bFirstContinueStream = HI_FALSE;
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? (JPG_EOF_VALUE|JPG_RESUME_VALUE) : JPG_RESUME_VALUE));
			}

			eIntStatus = JPG_INTTYPE_ERROR;
			s32Ret = JPEG_HDEC_GetIntStatus(pJpegHandle, &eIntStatus, JPG_INTTYPE_DELAY_TIME);
			if(JPG_INTTYPE_ERROR == eIntStatus) 
			{
				goto FAIL;
			}
			else if(JPG_INTTYPE_FINISH == eIntStatus) 
			{
				break;
			}
			else if(JPG_INTTYPE_CONTINUE == eIntStatus)
			{
				JPEG_HDEC_SuspendDispose(cinfo,&bResumeOk);
#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE) && defined(CONFIG_JPEG_SUSPEND)
				if(HI_FALSE == bSendSuspendSignal && HI_FALSE == bSuspendStart)
				{
					JPEG_TRACE("send suspend signal\n");
					HI_JPEG_Suspend(pJpegHandle->s32JpegDev,&bSendSuspendSignal);
					JPEG_TRACE("send suspend signal finish\n");
				}
#endif
				continue;

			}
			else 
			{
				goto FAIL;
			}


		} while (JPG_INTTYPE_FINISH != eIntStatus);


		cinfo->output_scanline        = 0;
		cinfo->global_state           = DSTATE_STOPPING;
		cinfo->inputctl->eoi_reached  = HI_TRUE;
		cinfo->rec_outbuf_height      = 1;
		cinfo->MCUs_per_row           = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)&0xffff;
		cinfo->MCU_rows_in_scan       = ((HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)>>16)&0xffff;
		cinfo->blocks_in_MCU          =  cinfo->num_components;

		for(s32Cnt=0; s32Cnt<cinfo->num_components; s32Cnt++)
		{
			cinfo->MCU_membership[s32Cnt] = s32Cnt;
		}


#if defined(CONFIG_JPEG_TEST_SAVE_BMP_PIC) && defined(CONFIG_JPEG_HARDDEC2ARGB)
		if(HI_TRUE == pJpegHandle->bDecARGB)
		{
			HI_JPEG_SaveBmp((unsigned long)pJpegHandle->stMiddleSurface.pMiddlePhy[0],  \
							(HI_U32)pJpegHandle->stOutDesc.stCropRect.w,         \
							(HI_U32)pJpegHandle->stOutDesc.stCropRect.h,         \
							pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0], \
							cinfo);
		}
#endif

		s32Ret = JPEG_HDEC_CheckOut(pJpegHandle);
		if(HI_SUCCESS != s32Ret)
		{
			#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			HI_JPEG_CloseScenFile(cinfo);
			#endif
			return HI_SUCCESS;
		}

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize && HI_TRUE != pJpegHandle->bDecARGB)
#else
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize)
#endif
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[0],pJpegHandle->stMiddleSurface.pMiddleVir[0],pJpegHandle->stJpegSofInfo.u32YSize);
		}
		if(0 != pJpegHandle->stJpegSofInfo.u32CSize)
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[1],pJpegHandle->stMiddleSurface.pMiddleVir[1],pJpegHandle->stJpegSofInfo.u32CSize);
		}


#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_JPEG_CloseScenFile(cinfo);
#endif


		return HI_SUCCESS;

		/** if decode failure jump here **/
FAIL:
		cinfo->src->bytes_in_buffer = s32ByteInBuffer;
		/**
		** change the read stream dispose
		** CNcomment:Ӳ������ʧ��֮�������������ԭ������·�� CNend\n
		**/
		pJpegHandle->stHDecDataBuf.bReadToDataBuf  = HI_FALSE;

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_JPEG_CloseScenFile(cinfo);
#endif			  
		return HI_FAILURE;
		  
}

/*****************************************************************************
* func			: JPEG_HDEC_SendStreamFromFileWithConDDRChange
* description	: get the stream from file
		  	      CNcomment:  ������Դ�ļ��Ĵ���ʽ,�����ǲ���
		  	  			  ��������ַ�����仯�����
* param[in] 	: cinfo 	  CNcomment:  �������
* param[in] 	: NA
* retval		: HI_SUCCESS  CNcomment:  �ɹ�
* retval		: HI_FAILURE  CNcomment:  ʧ��
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_SendStreamFromFileWithConDDRChange(j_decompress_ptr cinfo)
{
         
#ifdef CONFIG_JPEG_FPGA_TEST_CONTINUE_STREAM_DDR_CHANGE

		JPG_INTTYPE_E eIntStatus = JPG_INTTYPE_NONE;
		HI_BOOL bRetVal           = HI_FALSE;
		HI_BOOL bReachEOF         = HI_FALSE;
		HI_BOOL bStartDec         = HI_FALSE;
		HI_S32  s32Cnt            = 0;
		HI_U32 u32ReadDataSize   = 0;
		HI_U32 u32OffsetValue     = 0;

		HI_U32 u32NeedDecCnt		   = 0;
		HI_CHAR* pStreamStartPhyAddr = NULL;
		HI_CHAR* pStreamStartVirAddr = NULL;
		HI_CHAR* pStreamEndPhyAddr   = NULL;

		HI_S32 s32Ret = HI_SUCCESS;

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_BOOL bStartFirst = HI_TRUE;
#endif

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		/**
		** output the scen message to file
		** CNcomment:�������ֳ� CNend\n
		**/
		if(HI_TRUE == pJpegHandle->bSaveScen)
		{
			HI_JPEG_OpenScenFile(cinfo);
		}
#endif

		bReachEOF = HI_FALSE;

		pStreamStartVirAddr = pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf;
		u32ReadDataSize     = pJpegHandle->stHDecDataBuf.u32ReadDataSize;

		JPEG_TRACE("==================================================================\n");
		JPEG_TRACE("the stream start address is 0x%x\n",(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
		JPEG_TRACE("the stream end   address is 0x%x\n",(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf + u32ReadDataSize);
		JPEG_TRACE("==================================================================\n");

		do 
		{

			if(0 != cinfo->src->bytes_in_buffer)
			{
				u32NeedDecCnt = cinfo->src->bytes_in_buffer;
				memcpy(pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf,(char*)cinfo->src->next_input_byte,	u32NeedDecCnt);
				if(	  (0xFF == (*(cinfo->src->next_input_byte + u32NeedDecCnt - 2)))
					&&(0xD9 == (*(cinfo->src->next_input_byte + u32NeedDecCnt - 1))))
				{
					bReachEOF = HI_TRUE;
				}
				else
				{
					pJpegHandle->stHDecDataBuf.bReadToDataBuf  = HI_TRUE;
					pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf = pStreamStartVirAddr + u32NeedDecCnt;

					pJpegHandle->stHDecDataBuf.u32ReadDataSize = \
				                      pJpegHandle->stHDecDataBuf.u32ReadDataSize - u32NeedDecCnt;

					bRetVal = (*cinfo->src->fill_input_buffer)(cinfo);/*lint !e64 ignore by y00181162, because return value is ok */  
					if(HI_FALSE == bRetVal)
					{
						goto FAIL;
					}

					u32NeedDecCnt = u32NeedDecCnt + cinfo->src->bytes_in_buffer;
					pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf     = pStreamStartVirAddr;
					pJpegHandle->stHDecDataBuf.u32ReadDataSize = u32ReadDataSize;
				}

			}

			if(0 == cinfo->src->bytes_in_buffer)
			{
				u32OffsetValue = rand() % 50 + 1;
				if( (pStreamStartVirAddr + u32OffsetValue) >  (pStreamStartVirAddr + u32ReadDataSize))
				{
					JPEG_TRACE("�Ѿ������˴洢������ַ�ķ�Χ���س�������");
					getchar();
					return HI_FAILURE;
				}
			}

			if(0 == cinfo->src->bytes_in_buffer)
			{
				pJpegHandle->stHDecDataBuf.bReadToDataBuf  = HI_TRUE;
				pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf = pStreamStartVirAddr + u32OffsetValue;
				pJpegHandle->stHDecDataBuf.u32ReadDataSize   = pJpegHandle->stHDecDataBuf.u32ReadDataSize / 2;
				bRetVal = (*cinfo->src->fill_input_buffer)(cinfo); /*lint !e64 ignore by y00181162, because return value is ok */  
				if(HI_FALSE == bRetVal)
				{
					goto FAIL;
				}
				u32NeedDecCnt = cinfo->src->bytes_in_buffer;
				pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf  = pStreamStartVirAddr;
				pJpegHandle->stHDecDataBuf.u32ReadDataSize    = u32ReadDataSize;

			}
			if(HI_TRUE == bStartDec && u32NeedDecCnt < pJpegHandle->stHDecDataBuf.u32ReadDataSize / 2)
			{
				bReachEOF = HI_TRUE;
			}

			if(   (0xFF == (HI_UCHAR)pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf[0]) \
				&& (0xD9 == (HI_UCHAR)pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf[1]) \
			    && (2 == cinfo->src->bytes_in_buffer))
			{
				bReachEOF = HI_TRUE;
			}

			cinfo->src->bytes_in_buffer = 0;

#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
#else
			s32Ret = HI_GFX_Flush((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
#endif
			if(HI_SUCCESS != s32Ret)
			{
				goto FAIL;
			}

			pStreamStartPhyAddr = pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf + u32OffsetValue;
			pStreamEndPhyAddr   = pStreamStartPhyAddr + u32NeedDecCnt;

			JPEG_TRACE("==================================================================\n");
			JPEG_TRACE("the stream start address is 0x%x\n",(unsigned long)pStreamStartPhyAddr);
			JPEG_TRACE("==================================================================\n");

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
			if(HI_TRUE == pJpegHandle->bSaveScen)
			{	/**
				** should save scen before start decode
				** CNcomment:Ҫ�ڽ�������ǰ�����ֳ�����������ʧ�� CNend\n
				**/
				HI_JPEG_OutScenData(cinfo,pStreamStartPhyAddr,pStreamEndPhyAddr,pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf + u32OffsetValue,(HI_U64)u32NeedDecCnt,bStartFirst);
				bStartFirst = HI_FALSE;
			}
#endif
			JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD, (HI_S32)pStreamStartPhyAddr);
			JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD,(HI_S32)pStreamEndPhyAddr);

			if(HI_FALSE == bStartDec)
			{ 
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? JPG_EOF_VALUE : 0x0));
#ifdef CONFIG_JPEG_4KDDR_DISABLE
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x5);
#else
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_START, 0x1);
#endif
				bStartDec  = HI_TRUE;

			}
			else
			{
				JPEG_HDEC_WriteReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_RESUME,(bReachEOF ? (JPG_EOF_VALUE|JPG_RESUME_VALUE) : JPG_RESUME_VALUE));
			}

			eIntStatus = JPG_INTTYPE_ERROR;

			s32Ret = JPEG_HDEC_GetIntStatus(pJpegHandle, &eIntStatus, JPG_INTTYPE_DELAY_TIME);
			if(JPG_INTTYPE_ERROR == eIntStatus) 
			{
				goto FAIL;
			}
			else if(JPG_INTTYPE_FINISH == eIntStatus) 
			{
				break;
			}
			else if(JPG_INTTYPE_CONTINUE == eIntStatus)
			{
				continue;
			}
			else 
			{
				goto FAIL;
			}


		} while (JPG_INTTYPE_FINISH != eIntStatus);

		cinfo->output_scanline        = 0;
		cinfo->global_state           = DSTATE_STOPPING;
		cinfo->inputctl->eoi_reached  = HI_TRUE;
		cinfo->rec_outbuf_height      = 1;
		cinfo->MCUs_per_row           = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)&0xffff;
		cinfo->MCU_rows_in_scan       = ((HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_PICSIZE)>>16)&0xffff;
		cinfo->blocks_in_MCU          =  cinfo->num_components;

		for(s32Cnt=0; s32Cnt<cinfo->num_components; s32Cnt++)
		{
			cinfo->MCU_membership[s32Cnt] = s32Cnt;
		}

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
		HI_JPEG_CloseScenFile(cinfo);
#endif

		s32Ret = JPEG_HDEC_CheckOut(pJpegHandle);
		if(HI_SUCCESS != s32Ret)
		{
			return HI_SUCCESS;
		}

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize && HI_TRUE != pJpegHandle->bDecARGB)
#else
		if(0 != pJpegHandle->stJpegSofInfo.u32YSize)
#endif
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[0],pJpegHandle->stMiddleSurface.pMiddleVir[0],pJpegHandle->stJpegSofInfo.u32YSize);
		}
		if(0 != pJpegHandle->stJpegSofInfo.u32CSize)
		{
			memcpy(pJpegHandle->stOutDesc.stOutSurface.pOutVir[1],pJpegHandle->stMiddleSurface.pMiddleVir[1],pJpegHandle->stJpegSofInfo.u32CSize);
		}

		return HI_SUCCESS;

		FAIL:
			cinfo->src->bytes_in_buffer  = 0;
			pJpegHandle->stHDecDataBuf.bReadToDataBuf  = HI_FALSE;
			return HI_FAILURE;
#else
		/** deal with warning **/
		if(cinfo->is_decompressor)
			return HI_FAILURE;
		return HI_FAILURE;
#endif
}
