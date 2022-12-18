/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_mem.c
Version		    : Initial Draft
Author		    : y00181162
Created		    : 2014/06/20
Description	    : the mem alloc realize in this file
                  CNcomment: jpegӲ��������Ҫ���ڴ�������ļ���ʵ��.
                  MMZ�ڴ�ʹ��ԭ��:
                  (1)ˢ�ֲ�cach������ˢȫ��cach��Ҫ���ڴ�С��cach��С�ֲ���ȫ�ֿ� 
                  (2)Ҫ��û���õ������ڴ治��Ҫӳ���Լ��÷�cach��ʽ��Ҫ��ʹ��cach��ʽ
                     ��ʹ������ڴ�֮ǰҪˢcach����Ȼcach�л������ݲ����Լ�Ҫ��cach����
                     ���������ڴ��д�������ݴ���cachֻ�������ڴ���Ӱ�졣
                  (3)ÿ�η���YUV�ڴ�ᵼ�������½��ܶ࣬TC��Ҫ���ڴ�Ƚ�С�����Լ�ά��
                     ����ڴ棬�̶�����һ���ڴ棬������ʱ�����·��䡣��Ϊ��ʱ�������ٽ�
                     ��Դ����Ӱ�쵽���߳��Լ��û������ڴ����������ǵ�ͨ���Բ���ͳһά���ˡ�
                     �����ÿ����Դ�Ƕ����ģ�������ԴҪ�������ͨ����
                  (4)���������������ڴ沢��ӳ���cach��ʽ�ڴ�֮��Ҫˢһ��cach�����Բ��ó�ʼ����
                     ����cach����ǰ�Ĳ�����Ӱ�쵽�����ʹ��Ч��CNend\n
Function List 	:

			  		  
History       	:
Date				Author        		Modification
2014/06/20		    y00181162		    Created file      	
******************************************************************************/

/*********************************add include here******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include  "hi_jpeg_config.h"
#include  "jpeg_hdec_mem.h"
#include  "jpeg_hdec_api.h"
#include  "jpeg_hdec_error.h"

/***************************** Macro Definition ******************************/

/** the first class is jpeg */
/** CNcomment:��һ���ڴ�Ϊjpeg���� */
#define MMZ_TAG          "jpeg"
/** the second class is jpeg */
/** CNcomment:�ڶ����ڴ�Ϊgraphics���� */
//#define MMZ_TAG_1        "graphics"
/** the last class is jpeg */
/** CNcomment:���һ���ڴ�Ϊ����MMZ���� */
//#define MMZ_TAG_2        ""

/** the module name */
/** CNcomment:�����jpegģ������֣��������ͨ��mmz proc���鿴�����˭�� */
#define MMZ_MODULE       "JPEG_STREAM_OUT_BUF"


#if defined(CONFIG_JPEG_ANDROID_DEBUG_ENABLE) && defined(CONFIG_JPEG_DEBUG_INFO)
#define LOG_TAG    "libjpeg"
#endif

/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/

/******************************* API forward declarations *******************/

/******************************* API realization *****************************/


/*****************************************************************************
* func			: JPEG_HDEC_GetStreamMem
* description	: alloc the stream buffer mem
                  CNcomment: ��������buffer�ڴ� CNend\n
* param[in] 	: u32MemSize   CNcomment: Ҫ������ڴ��С    CNend\n
* param[out]	: pOutPhyAddr  CNcomment: ����õ��������ַ  CNend\n
* param[out]	: pOutVirAddr  CNcomment: ����õ��������ַ  CNend\n
* retval		: HI_SUCCESS   CNcomment: �ɹ�  CNend\n
* retval		: HI_FAILURE   CNcomment: ʧ��   CNend\n
* others:		: NA
*****************************************************************************/
HI_S32	JPEG_HDEC_GetStreamMem(JPEG_HDEC_HANDLE_S_PTR	 pJpegHandle,const HI_U32 u32MemSize)
{


		HI_CHAR *pPhyBuf = NULL;
		HI_CHAR *pVirBuf = NULL;
		HI_U32 u32StreamSize = JPGD_STREAM_BUFFER;

		JPEG_ASSERT((0 == u32MemSize),HI_FAILURE);

		if(u32StreamSize < 4096)/*lint !e774 ignore by y00181162, because this cast is ok */  
		{
			//JPEG_TRACE("the save stream size is small than the input buffer size\n");
			return HI_FAILURE;
		}
		/**
		** use the third class manage to alloc mem,the stream buffer should 64bytes align
		** CNcomment: ʹ��������������������ڴ� CNend\n
		**/
        #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pPhyBuf = (HI_CHAR*)HI_GFX_AllocMem(pJpegHandle->s32MMZDev,u32MemSize, JPGD_HDEC_MMZ_STREAM_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)MMZ_MODULE, &(pJpegHandle->pSaveStreamMemHandle));
        #else
		pPhyBuf = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize, JPGD_HDEC_MMZ_STREAM_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)MMZ_MODULE);
        #endif
		if(NULL == pPhyBuf)
		{
			//JPEG_TRACE("%s %s %d == HI_GFX_AllocMem FAILURE\n",__FILE__,__FUNCTION__,__LINE__);
			return HI_FAILURE;
		}
	    #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pVirBuf = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->s32MMZDev,(unsigned long)pPhyBuf, pJpegHandle->pSaveStreamMemHandle);
        #else
		pVirBuf = (HI_CHAR*)HI_GFX_MapCached((unsigned long)pPhyBuf);
        #endif
		if(NULL == pVirBuf)
		{
			//JPEG_TRACE("HI_GFX_MapCached FAILURE\n");
			return HI_FAILURE;
		}
#if 0
		/**
		** when use this mem, should memset this mem
		** CNcomment: ��ʹ�ø��ڴ�ĵ�ַ��ʼ�����ڴ棬memset��Ҫʱ�䣬ʹ��������� CNend\n
		**/
		memset(pVirAddr,0,u32MemSize);
		HI_GFX_Flush((HI_U32)pPhyBuf);
#endif

		pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf      = pPhyBuf;
		pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf      = pVirBuf;
		/**
		** use the virtual memory, every time should read data size
		** CNcomment: �����ڴ�������ʱ��ÿ����Ҫ��ȡ��������С CNend\n
		**/
		pJpegHandle->stHDecDataBuf.u32ReadDataSize	      = u32StreamSize;


		return HI_SUCCESS;

		
}



/*****************************************************************************
* func			: JPEG_HDEC_FreeStreamMem
* description	: free the stream buffer mem
                  CNcomment: �ͷ�����buffer�ڴ� CNend\n
* param[in] 	: pInPhyAddr    CNcomment: Ҫ�ͷŵ�����buffer�����ַ CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_FreeStreamMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{

      HI_S32 s32Ret = HI_SUCCESS;
	
      if(NULL == pJpegHandle)
      {
           JPEG_TRACE("%s :%s : %d (the pJpegHandle is NULL)\n",__FILE__,__FUNCTION__,__LINE__);
		   return;
      }
	  
	  if( NULL == pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf)
	  {
		   return;
	  }
	  #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
	  s32Ret = HI_GFX_Unmap(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
	  s32Ret = HI_GFX_FreeMem(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf, pJpegHandle->pSaveStreamMemHandle);
	  #else
	  s32Ret = HI_GFX_Unmap((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
	  s32Ret = HI_GFX_FreeMem((unsigned long)pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf);
	  #endif
	  if(HI_SUCCESS != s32Ret)
	  {
	      JPEG_TRACE("HI_GFX_Unmap or  HI_GFX_FreeMem FAILURE\n");
	      return;
	  }
	  pJpegHandle->stHDecDataBuf.pSaveStreamPhyBuf	    = NULL;
	  pJpegHandle->stHDecDataBuf.pSaveStreamVirBuf	    = NULL;
	  
}


/*****************************************************************************
* func			: JPEG_HDEC_GetYUVMem
* description	: get the hard decode output mem
				  CNcomment: ��ȡӲ������������ڴ� CNend\n
* param[in]	    : pJpegHandle   CNcomment: ��������� CNend\n
* retval		: HI_SUCCESS	CNcomment: �ɹ� CNend\n
* retval		: HI_FAILURE	CNcomment: ʧ�� CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_GetYUVMem(JPEG_HDEC_HANDLE_S_PTR	pJpegHandle)
{


		HI_U32 u32MemSize = 0;
		HI_CHAR *pYUVPhy  = NULL;
		HI_CHAR *pYUVVir  = NULL;
		HI_U32 u32Align   = 0;
		HI_S32 s32Ret = HI_SUCCESS;
		/**
		 ** check whether to alloc jpeg hard decode middle mem
		 ** CNcomment: �ж��Ƿ����Ӳ��������м�buffer CNend\n
		 **/
#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(   (HI_TRUE == pJpegHandle->bOutYCbCrSP || HI_TRUE == pJpegHandle->bDecARGB)
			&&(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem))
#else
		if(   (HI_TRUE == pJpegHandle->bOutYCbCrSP)
			&&(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem))	
#endif
		{/**
		  ** use user mem
		  ** CNcomment: ʹ���û��ڴ� CNend\n
		  **/
		      pJpegHandle->stMiddleSurface.pMiddlePhy[0] = pJpegHandle->stOutDesc.stOutSurface.pOutPhy[0];
		      pJpegHandle->stMiddleSurface.pMiddlePhy[1] = pJpegHandle->stOutDesc.stOutSurface.pOutPhy[1];
			  pJpegHandle->stMiddleSurface.pMiddlePhy[2] = pJpegHandle->stOutDesc.stOutSurface.pOutPhy[2];
		      pJpegHandle->stMiddleSurface.pMiddleVir[0] = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
		      pJpegHandle->stMiddleSurface.pMiddleVir[1] = pJpegHandle->stOutDesc.stOutSurface.pOutVir[1];
			  pJpegHandle->stMiddleSurface.pMiddleVir[2] = pJpegHandle->stOutDesc.stOutSurface.pOutVir[2];
		      return HI_SUCCESS;
		}


#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bDecARGB)
		{
		  /**
		   ** 4bytes align just ok
		   ** CNcomment: 4�ֽڶ���Ϳ����� CNend\n
		   **/
		   u32Align   = JPGD_HDEC_MMZ_ARGB_BUFFER_ALIGN;
		   u32MemSize = pJpegHandle->stJpegSofInfo.u32YSize;
		}
		else
#endif
		{
		   u32Align   = JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN;
		   u32MemSize = pJpegHandle->stJpegSofInfo.u32YSize + pJpegHandle->stJpegSofInfo.u32CSize;
		}
		/**
		 ** use the third class manage to alloc mem,the stream buffer should 128bytes align
		 ** CNcomment: ʹ��������������������ڴ�,bufferҪ128�ֽڶ��� CNend\n
		 **/
		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pYUVPhy = (HI_CHAR*)HI_GFX_AllocMem(pJpegHandle->s32MMZDev,u32MemSize,u32Align,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)MMZ_MODULE, &(pJpegHandle->pMiddleMemHandle));
		#else
		pYUVPhy = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize,u32Align,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)MMZ_MODULE);
		#endif
		if(NULL == pYUVPhy)
		{
		     //JPEG_TRACE("%s %s %d == HI_GFX_AllocMem FAILURE\n",__FILE__,__FUNCTION__,__LINE__);
		     return HI_FAILURE;
		}

#ifndef CONFIG_JPEG_TEST_SAVE_YUVSP_DATA
/** if need save yuvsp data,should virtual address **/
		#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if( (HI_TRUE == pJpegHandle->bOutYCbCrSP) || (HI_TRUE == pJpegHandle->bDecARGB))
		#else
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP)
		#endif
#endif
		{
			#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			pYUVVir = (HI_CHAR *)HI_GFX_MapCached(pJpegHandle->s32MMZDev,(unsigned long)pYUVPhy, pJpegHandle->pMiddleMemHandle);
			#else
			pYUVVir = (HI_CHAR *)HI_GFX_MapCached((unsigned long)pYUVPhy);
			#endif
			if (NULL == pYUVVir)
			{
				//JPEG_TRACE("HI_GFX_MapCached FAILURE\n");
				return HI_FAILURE;
			}
			/**
			** when use this mem, should memset this mem
			** CNcomment: ��ʹ�ø��ڴ�ĵ�ַ��ʼ�����ڴ棬memset��Ҫʱ�䣬ʹ��������� CNend\n
			**/
			//memset(pYUVVir,0,u32MemSize);
			#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
			s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(unsigned long)pYUVPhy, pJpegHandle->pMiddleMemHandle);
			#else
			s32Ret = HI_GFX_Flush((unsigned long)pYUVPhy);
			#endif
			if(HI_SUCCESS != s32Ret)
			{
				return HI_FAILURE;
			}
			pJpegHandle->stMiddleSurface.pMiddleVir[0] = pYUVVir;
			pJpegHandle->stMiddleSurface.pMiddleVir[1] = pYUVVir + pJpegHandle->stJpegSofInfo.u32YSize;
			
		}

		pJpegHandle->stMiddleSurface.pMiddlePhy[0] = pYUVPhy;
		pJpegHandle->stMiddleSurface.pMiddlePhy[1] = pYUVPhy + pJpegHandle->stJpegSofInfo.u32YSize;
		 
		return HI_SUCCESS;


}

/*****************************************************************************
* func			: JPEG_HDEC_FreeYUVMem
* description	: free the hard decode output mem
				  CNcomment: �ͷ�Ӳ����������ĵ�ַ  CNend\n
* param[in]	    : pJpegHandle   CNcomment: ��������� CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_FreeYUVMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{

		HI_S32 s32Ret = HI_SUCCESS;


		if(NULL == pJpegHandle)
		{
			JPEG_TRACE("%s :%s : %d (the pJpegHandle is NULL)\n",__FILE__,__FUNCTION__,__LINE__);
			return;
		}

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(   (HI_TRUE == pJpegHandle->bOutYCbCrSP || (HI_TRUE == pJpegHandle->bDecARGB))
			&&(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem))
#else
		if(   (HI_TRUE == pJpegHandle->bOutYCbCrSP)
			&&(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem))

#endif
		{/**
		** use user mem
		** CNcomment: ʹ���û��ڴ� CNend\n
		**/
			return;
		}

		if(NULL == pJpegHandle->stMiddleSurface.pMiddlePhy[0])
		{
			return;
		}

#ifndef CONFIG_JPEG_TEST_SAVE_YUVSP_DATA
		#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if( (HI_TRUE == pJpegHandle->bOutYCbCrSP) || (HI_TRUE == pJpegHandle->bDecARGB))
		#else
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP)
		#endif
#endif
		{
		    #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		    s32Ret = HI_GFX_Unmap(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stMiddleSurface.pMiddlePhy[0], pJpegHandle->pMiddleMemHandle);
			#else
			s32Ret = HI_GFX_Unmap((unsigned long)pJpegHandle->stMiddleSurface.pMiddlePhy[0]);
			#endif
			if(HI_SUCCESS != s32Ret)
			{
				JPEG_TRACE("HI_GFX_Unmap FAILURE\n");
				return;
			}
		}

		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		s32Ret = HI_GFX_FreeMem(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stMiddleSurface.pMiddlePhy[0], pJpegHandle->pMiddleMemHandle);
		#else
		s32Ret = HI_GFX_FreeMem((unsigned long)pJpegHandle->stMiddleSurface.pMiddlePhy[0]);
		#endif
		if(HI_SUCCESS != s32Ret)
		{
			JPEG_TRACE("HI_GFX_FreeMem FAILURE\n");
			return;
		}
		pJpegHandle->stMiddleSurface.pMiddlePhy[0]  = NULL;
		pJpegHandle->stMiddleSurface.pMiddlePhy[1]  = NULL;
		pJpegHandle->stMiddleSurface.pMiddleVir[0]  = NULL;
		pJpegHandle->stMiddleSurface.pMiddleVir[1]  = NULL;
					
}


#ifdef CONFIG_JPEG_HARDDEC2ARGB
/*****************************************************************************
* func			: JPEG_HDEC_GetMinMem
* description	: get dec output argb min memory
				  CNcomment: ��ȡӲ���������ΪARGB����buffer CNend\n
* param[in]	    : pJpegHandle   CNcomment: ��������� CNend\n
* retval		: HI_SUCCESS	CNcomment: �ɹ� CNend\n
* retval		: HI_FAILURE	CNcomment: ʧ�� CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_GetMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{

		HI_U32 u32MemSize = 0;
		HI_CHAR *pMinPhy  = NULL;

   		u32MemSize = pJpegHandle->stJpegSofInfo.u32RGBSizeReg;

		/**
	 	 ** use the third class manage to alloc mem,the min buffer should 128bytes align
	     ** CNcomment: ʹ��������������������ڴ�,argb��bufferҪ128�ֽڶ��� CNend\n
	     **/
	    #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
        pMinPhy = (HI_CHAR*)HI_GFX_AllocMem(pJpegHandle->s32MMZDev,u32MemSize,JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)MMZ_MODULE, &(pJpegHandle->pMinMemHandle));
        #else
		pMinPhy = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize,JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN,(HI_CHAR*)MMZ_TAG,(HI_CHAR*)MMZ_MODULE);
		#endif
		if(NULL == pMinPhy)
		{
		     //JPEG_TRACE("%s %s %d == HI_GFX_AllocMem FAILURE\n",__FILE__,__FUNCTION__,__LINE__);
			 return HI_FAILURE;
		}

		pJpegHandle->pMinPhyBuf   =   pMinPhy;
			
		return HI_SUCCESS;


}

/*****************************************************************************
* func			: JPEG_HDEC_FreeMinMem
* description	: free dec output argb min memory
				  CNcomment: �ͷ�Ӳ���������ΪARGB����buffer  CNend\n
* param[in]	    : pJpegHandle   CNcomment: ��������� CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_FreeMinMem(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{

	    HI_S32 s32Ret = HI_SUCCESS;

		if(NULL == pJpegHandle)
		{
			 JPEG_TRACE("%s :%s : %d (the pJpegHandle is NULL)\n",__FILE__,__FUNCTION__,__LINE__);
			 return;
		}

		if(NULL == pJpegHandle->pMinPhyBuf)
		{
		   return;
		}
        #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		s32Ret = HI_GFX_FreeMem(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->pMinPhyBuf, pJpegHandle->pMinMemHandle);
		#else
        s32Ret = HI_GFX_FreeMem((unsigned long)pJpegHandle->pMinPhyBuf);
		#endif
		if(HI_SUCCESS != s32Ret)
		{
		   JPEG_TRACE("HI_GFX_FreeMem FAILURE\n");
		   return;
		}
				
		pJpegHandle->pMinPhyBuf  = NULL;

}
#endif


/*****************************************************************************
* func			: JPEG_HDEC_GetOutMem
* description	: get the output buffer
				  CNcomment: ��������������ڴ� 	 CNend\n
* param[in]	    : cinfo         CNcomment: �������  CNend\n
* retval		: HI_SUCCESS    CNcomment: �ɹ�		  CNend\n
* retval		: HI_FAILURE    CNcomment: ʧ��		  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_GetOutMem(const struct jpeg_decompress_struct *cinfo)
{


		HI_U32 u32OutStride = 0;
		HI_U32 u32MemSize   = 0;
		HI_CHAR* pOutPhy    = NULL;
		HI_CHAR* pOutVir    = NULL;
        HI_S32 s32Ret = HI_SUCCESS;
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);


#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP || HI_TRUE  == pJpegHandle->bDecARGB)
#else
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP)
#endif
		{
		/**
		** shoule not csc,so not alloc output mem
		** CNcomment: ����Ҫ��ɫ�ռ�ת�������ԾͲ���Ҫ�������buffer CNend\n
		**/
			return HI_SUCCESS;
		}

		if(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem)
		{  
		/**
		** use user mem
		** CNcomment: ʹ���û��ڴ� CNend\n
		**/
			pJpegHandle->stMiddleSurface.pOutPhy = pJpegHandle->stOutDesc.stOutSurface.pOutPhy[0];
			pJpegHandle->stMiddleSurface.pOutVir = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0];
			return HI_SUCCESS;
		}
		u32OutStride = pJpegHandle->stJpegSofInfo.u32DisplayStride;
		u32MemSize   = u32OutStride * ((HI_U32)pJpegHandle->stOutDesc.stCropRect.h);
		
		/**
		** align depend the pixle
		** CNcomment: �������ض��� CNend\n
		**/
		/** 3�ֽڶ�����������ģ���Ϊmap������**/
		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pOutPhy = (HI_CHAR*)HI_GFX_AllocMem(pJpegHandle->s32MMZDev,u32MemSize, JPGD_HDEC_MMZ_CSCOUT_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)MMZ_MODULE, &(pJpegHandle->pOutMemHandle));
        #else
		pOutPhy = (HI_CHAR*)HI_GFX_AllocMem(u32MemSize, JPGD_HDEC_MMZ_CSCOUT_BUFFER_ALIGN, (HI_CHAR*)MMZ_TAG, (HI_CHAR*)MMZ_MODULE);
		#endif
		if(0 == pOutPhy)
		{
			//JPEG_TRACE("%s %s %d == HI_GFX_AllocMem FAILURE\n",__FILE__,__FUNCTION__,__LINE__);
			return HI_FAILURE;
		}
		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pOutVir = (HI_CHAR*)HI_GFX_MapCached(pJpegHandle->s32MMZDev,(unsigned long)pOutPhy, pJpegHandle->pOutMemHandle);
		#else
		pOutVir = (HI_CHAR*)HI_GFX_MapCached((unsigned long)pOutPhy);
		#endif
		if (NULL == pOutVir)
		{
			//JPEG_TRACE("HI_GFX_MapCached FAILURE\n");
			return HI_FAILURE;
		}
		/** memset Ҳ��Ҫ��ʱ�䣬������������Ͳ�Ҫmemset������ **/
		//memset(pOutVir,0,u32MemSize);
		#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		s32Ret = HI_GFX_Flush(pJpegHandle->s32MMZDev,(unsigned long)pOutPhy, pJpegHandle->pOutMemHandle);
        #else
		s32Ret = HI_GFX_Flush((unsigned long)pOutPhy);
		#endif
		if(HI_SUCCESS != s32Ret)
		{
			return HI_FAILURE;
		}
		/**
		** Ҫ���û�û���������ͼ���С���ʹ��Ĭ�ϵ������Ҳ����ֻ��1/2/4/8��������
		**/
		pJpegHandle->stMiddleSurface.pOutPhy   =  pOutPhy;
		pJpegHandle->stMiddleSurface.pOutVir   =  pOutVir;

		return HI_SUCCESS;

		
}

/*****************************************************************************
* func			: JPEG_HDEC_FreeOutMem
* description	: free the output buf
				  CNcomment: �ͷ�����������ڴ� 	   CNend\n
* param[in]	    : pJpegHandle   CNcomment: ���������  CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_FreeOutMem(JPEG_HDEC_HANDLE_S_PTR	 pJpegHandle)
{

		HI_S32 s32Ret = HI_SUCCESS;

		if(NULL == pJpegHandle)
		{
				JPEG_TRACE("%s :%s : %d (the pJpegHandle is NULL)\n",__FILE__,__FUNCTION__,__LINE__);
				return;
		}
#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP || HI_TRUE  == pJpegHandle->bDecARGB)
#else
		if(HI_TRUE == pJpegHandle->bOutYCbCrSP)
#endif
		{
			return;
		}

		if(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem)
		{   
			return;
		}


		if(NULL == pJpegHandle->stMiddleSurface.pOutPhy)
		{
			return;
		}
        #ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		s32Ret = HI_GFX_Unmap(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stMiddleSurface.pOutPhy, pJpegHandle->pOutMemHandle);
		s32Ret = HI_GFX_FreeMem(pJpegHandle->s32MMZDev,(unsigned long)pJpegHandle->stMiddleSurface.pOutPhy, pJpegHandle->pOutMemHandle);
		#else
		s32Ret = HI_GFX_Unmap((unsigned long)pJpegHandle->stMiddleSurface.pOutPhy );
		s32Ret = HI_GFX_FreeMem((unsigned long)pJpegHandle->stMiddleSurface.pOutPhy);
		#endif
		if(HI_SUCCESS != s32Ret)
		{
			JPEG_TRACE("HI_GFX_Unmap or HI_GFX_FreeMem FAILURE\n");
			return;
		}
		pJpegHandle->stMiddleSurface.pOutPhy  = NULL;
		pJpegHandle->stMiddleSurface.pOutVir  = NULL; 

}

#ifdef CONFIG_GFX_JPGE_ENC_ENABLE

/*****************************************************************************
 * func 		 : JPGE_HENC_GetEncMem
 * description	 : get encode need memory
                   CNcomment: ���������Ҫ���ڴ�        CNend\n
 * param[ou]	 : pu32OutPhy   CNcomment: ���������ַ      CNend\n
 * param[ou]	 : pOutVir      CNcomment: ���������ַ      CNend\n
 * retval		 : NA
 * others:		 : NA
 *****************************************************************************/
 HI_S32 JPGE_HENC_GetEncMem(JPGE_HENC_HANDLE_S_PTR pJpgeHandle)
{

		HI_S32 s32Ret = HI_SUCCESS;
		HI_S32 s32MemSize = 0;
		HI_CHAR* pPhy = NULL;
		HI_CHAR* pVir = NULL;
		HI_S32 s32Cnt = 0;
		
		if( (HI_TRUE == pJpgeHandle->stStreamInfo.bUserPhyMem) && (HI_TRUE == pJpgeHandle->bCanUserPhyMem))
		{
			s32MemSize = pJpgeHandle->EncIn.OutBufSize;
		}
		else
		{
			s32MemSize =  pJpgeHandle->stStreamInfo.u32InSize[0] \
				        + pJpgeHandle->stStreamInfo.u32InSize[1] \
				        + pJpgeHandle->stStreamInfo.u32InSize[2] \
				        + pJpgeHandle->EncIn.OutBufSize;
		}
		
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pPhy = (HI_CHAR*)HI_GFX_AllocMem(pJpgeHandle->s32MMZDev,s32MemSize, JPGD_HDEC_MMZ_STREAM_BUFFER_ALIGN, (HI_CHAR*)JPGE_TAG, (HI_CHAR*)JPGE_MODULE, &(pJpgeHandle->pMemHandle));
#else
		pPhy = (HI_CHAR*)HI_GFX_AllocMem(s32MemSize, JPGD_HDEC_MMZ_STREAM_BUFFER_ALIGN, (HI_CHAR*)JPGE_TAG, (HI_CHAR*)JPGE_MODULE);
#endif
		if(NULL == pPhy)
		{
			JPEG_TRACE("=====%s %d failure\n",__FUNCTION__,__LINE__);
			return HI_FAILURE;
		}
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pVir = (HI_CHAR*)HI_GFX_MapCached(pJpgeHandle->s32MMZDev,(unsigned long)pPhy, pJpgeHandle->pMemHandle);
#else
	    pVir = (HI_CHAR*)HI_GFX_Map((unsigned long)pPhy);
#endif
		if(NULL == pVir)
		{
			#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
				HI_GFX_FreeMem(pJpgeHandle->s32MMZDev,(unsigned long)pPhy, pJpgeHandle->pMemHandle);
			#else
				HI_GFX_FreeMem((unsigned long)pPhy);
			#endif
			pPhy = NULL;
			pVir = NULL;
			return HI_FAILURE;
		}
		memset(pVir,0,s32MemSize);
		
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		s32Ret = HI_GFX_Flush(pJpgeHandle->s32MMZDev,(unsigned long)pPhy, pJpgeHandle->pMemHandle);
#else
		s32Ret = HI_GFX_Flush((unsigned long)pPhy);
#endif
		if(HI_SUCCESS != s32Ret)
		{
			#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
				HI_GFX_Unmap(pJpgeHandle->s32MMZDev,(unsigned long)pPhy, pJpgeHandle->pMemHandle);
				HI_GFX_FreeMem(pJpgeHandle->s32MMZDev,(unsigned long)pPhy, pJpgeHandle->pMemHandle);
			#else
				HI_GFX_Unmap((unsigned long)pPhy);
				HI_GFX_FreeMem((unsigned long)pPhy);
			#endif
			JPEG_TRACE("=====%s %d failure\n",__FUNCTION__,__LINE__);
			return HI_FAILURE;
		}

		if( (HI_TRUE == pJpgeHandle->stStreamInfo.bUserPhyMem) && (HI_TRUE == pJpgeHandle->bCanUserPhyMem))
		{
			for(s32Cnt = 0; s32Cnt < MAX_IN_PIXEL_COMPONENT_NUM; s32Cnt++)
			{
				pJpgeHandle->stMiddleBuf.pInPhy[s32Cnt] = pJpgeHandle->stStreamInfo.pInPhy[s32Cnt];
				pJpgeHandle->stMiddleBuf.pInVir[s32Cnt] = pJpgeHandle->stStreamInfo.pInVir[s32Cnt];
			}
			pJpgeHandle->stMiddleBuf.pInPhy[3] = pPhy;
			pJpgeHandle->stMiddleBuf.pInVir[3] = pVir;
			return HI_SUCCESS;
		}

		pJpgeHandle->stMiddleBuf.pInPhy[0] = pPhy;
		pJpgeHandle->stMiddleBuf.pInVir[0] = pVir;
		pJpgeHandle->stMiddleBuf.pInPhy[1] = pPhy + pJpgeHandle->stStreamInfo.u32InSize[0];
		pJpgeHandle->stMiddleBuf.pInVir[1] = pVir + pJpgeHandle->stStreamInfo.u32InSize[0];
		pJpgeHandle->stMiddleBuf.pInPhy[2] = pJpgeHandle->stMiddleBuf.pInPhy[1] + pJpgeHandle->stStreamInfo.u32InSize[1];
		pJpgeHandle->stMiddleBuf.pInVir[2] = pJpgeHandle->stMiddleBuf.pInVir[1] + pJpgeHandle->stStreamInfo.u32InSize[1];
		pJpgeHandle->stMiddleBuf.pInPhy[3] = pJpgeHandle->stMiddleBuf.pInPhy[2] + pJpgeHandle->stStreamInfo.u32InSize[2];
		pJpgeHandle->stMiddleBuf.pInVir[3] = pJpgeHandle->stMiddleBuf.pInVir[2] + pJpgeHandle->stStreamInfo.u32InSize[2];

		return HI_SUCCESS;
		
}


/*****************************************************************************
 * func 		 : JPGE_HENC_FreeEncMem
 * description	 : free encode memory
                   CNcomment: �ͷű����ڴ�                   CNend\n
 * param[in]	 : u32PhyAddr   CNcomment: Ҫ�ͷŵ������ַ  CNend\n
 * retval		 : NA
 * others:		 : NA
 *****************************************************************************/
 HI_S32 JPGE_HENC_FreeEncMem(JPGE_HENC_HANDLE_S_PTR pJpgeHandle)
{

	HI_S32 s32Ret = HI_SUCCESS;
	HI_CHAR *pPhy = NULL;
	HI_S32 s32Cnt = 0;
	
	if( (HI_TRUE == pJpgeHandle->stStreamInfo.bUserPhyMem) && (HI_TRUE == pJpgeHandle->bCanUserPhyMem))
	{
		pPhy = pJpgeHandle->stMiddleBuf.pInPhy[3];
	}
	else
	{
		pPhy = pJpgeHandle->stMiddleBuf.pInPhy[0];
	}
	if(NULL == pPhy)
	{
		return HI_SUCCESS;
	}
	
#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
	s32Ret = HI_GFX_Unmap(pJpgeHandle->s32MMZDev,(unsigned long)pPhy, pJpgeHandle->pMemHandle);
	s32Ret = HI_GFX_FreeMem(pJpgeHandle->s32MMZDev,(unsigned long)pPhy, pJpgeHandle->pMemHandle);
#else
	s32Ret = HI_GFX_Unmap((unsigned long)pPhy);
	s32Ret = HI_GFX_FreeMem((unsigned long)pPhy);
#endif
	if(HI_SUCCESS != s32Ret)
	{
	   JPEG_TRACE("=====%s %d failure\n",__FUNCTION__,__LINE__);
	   return HI_FAILURE;
	}
	for(s32Cnt = 0; s32Cnt < MAX_IN_PIXEL_COMPONENT_NUM + 1; s32Cnt++)
	{
		pJpgeHandle->stMiddleBuf.pInPhy[s32Cnt] = NULL;
	}
	
	return HI_SUCCESS;
	
}
#endif
