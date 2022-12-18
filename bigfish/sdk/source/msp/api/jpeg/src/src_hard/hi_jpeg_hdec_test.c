/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : hi_jpeg_hdec_test.c
Version		    : Initial Draft
Author		    : y00181162
Created		    : 2014/06/20
Description	    : the test need some function
                  CNcomment: ����������Ҫ��һЩ���⺯�� CNend\n
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
#include <unistd.h>

#include "jpeglib.h"

#include "jpeg_hdec_rwreg.h"
#include "jpeg_hdec_api.h"
#include "hi_jpeg_hdec_test.h"
#include "hi_jpeg_reg.h"


#if defined(CONFIG_JPEG_TEST_SAVE_BMP_PIC) || defined(CONFIG_JPEG_TEST_SAVE_YUVSP_DATA)
#include <linux/types.h>
#include <linux/stat.h>
#include <linux/unistd.h>
#endif

#if 0
#include <utils/Log.h>
#define LOG_TAG           "libjpeg"
#endif

/***************************** Macro Definition ******************************/

#ifdef CONFIG_JPEG_TEST_CHIP_RANDOM_RESET
static volatile HI_CHAR *g_pJpegRegVirAddr  = NULL; /** �Ĵ�������ַ **/
static HI_BOOL sg_bDecFinish                = HI_FALSE;
static HI_S32  sg_s32JpegDev                = -1;
#endif

#ifdef CONFIG_JPEG_FPGA_TEST_CONTINUE_STREAM_DDR_CHANGE
static HI_BOOL gs_bConStreamDDRChange = HI_FALSE;
#endif

#ifdef CONFIG_JPEG_FPGA_TEST_SET_DIFFERENT_OUTSTANDING_VALUE
static HI_S32 gs_s32OutstandingValue = 0xffffff3f;
static HI_BOOL gs_bOutstandingFlag   = HI_FALSE;
#endif

/******************** to see which include file we want to use***************/



/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/




/******************************* API forward declarations *******************/
#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE

/*****************************************************************************
* func			: HI_JPEG_OpenScenFile
* description	: open the scen file
				  CNcomment: �򿪵��ֳ����ļ� CNend\n
* param[in]	    : cinfo.       CNcomment:�������     CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_S32 HI_JPEG_OpenScenFile(const struct jpeg_decompress_struct *cinfo)
{
	 JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	 char pFileName[256];
	 char pNum[20];
     static HI_S32 s32Cnt = 0;
	 
	 snprintf(pNum,sizeof(pNum), "%d", s32Cnt);
	 strncpy(pFileName, SCEN_FILE_NAME,strlen(SCEN_FILE_NAME));
	 pFileName[strlen(SCEN_FILE_NAME)] = '\0';
	 strncat(pFileName,pNum,strlen(pNum));
	 
	 pJpegHandle->pScenFile = fopen(pFileName,"wb+");
	 if(NULL == pJpegHandle->pScenFile)
	 {
	 	JPEG_TRACE("open scen file failure\n");
		return HI_FAILURE;
	 }
	 s32Cnt++;

	 SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");
	 SCEN_PRINT(pJpegHandle->pScenFile,"the dec file name is %s\n",pJpegHandle->pScenFileName);
	 SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");

	 return HI_SUCCESS;
	 
}

/*****************************************************************************
* func			: HI_JPEG_CloseScenFile
* description	: close the scen file
				  CNcomment: �رյ��ֳ����ļ� CNend\n
* param[in]	    : cinfo.       CNcomment:�������     CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_CloseScenFile(const struct jpeg_decompress_struct *cinfo)
{
	 JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	 
	 if(NULL != pJpegHandle->pScenFile)
	 {
	 	fclose(pJpegHandle->pScenFile);
	 }
	 pJpegHandle->pScenFile = NULL;
}


/*****************************************************************************
* func			: HI_JPEG_GetScenData
* description	: get scen data.
				  CNcomment: ��ȡ�ֳ����� CNend\n
* param[in]	    : cinfo.       CNcomment:�������     CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
static HI_VOID HI_JPEG_GetScenData(const struct jpeg_decompress_struct *cinfo)
{

		HI_S32 offset      = 0;
		HI_S32 cnt         = 0;

	    JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	
		/* �Ĵ���(����) */
		for (offset = 0xc; offset <= 0x6bc; offset+=4)
		{

			if(JPGD_REG_STADD == offset)
			{
				cnt++;
			}
			else if(JPGD_REG_ENDADD == offset)
			{
				cnt++;
			}
			else
			{   
				pJpegHandle->s32RegData[cnt] = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,offset);
				cnt++;
			}
		}

}

/*****************************************************************************
* func			: HI_JPEG_PrintScenData
* description	: export the scen data.
				  CNcomment: �����ֳ����� CNend\n
* param[in]	    : cinfo.                 CNcomment:�������         CNend\n
* param[in]	    : pStreamStartBuf.       CNcomment:������ʼ��ַ     CNend\n
* param[in]	    : pStreamEndBuf.         CNcomment:����������ַ     CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
static HI_VOID HI_JPEG_PrintScenData(const struct jpeg_decompress_struct *cinfo,HI_CHAR* pStreamStartBuf,HI_CHAR* pStreamEndBuf)
{

		HI_S32 offset      = 0;
		HI_S32 cnt        = 0;

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		if(NULL != pJpegHandle->pScenFile)
		{

			SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");
			SCEN_PRINT(pJpegHandle->pScenFile,"   the register data \n");
			SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");
			/* �Ĵ���(����)����VAHB_STRIDE��ʼ */
			for (offset = 0xc; offset <= 0x6bc; offset+=4)
			{

				if(JPGD_REG_STADD == offset)
				{
					PRN_SCENE(pJpegHandle->pScenFile,CV200_JPEG_BASE + offset, (HI_U32)pStreamStartBuf);
					cnt++;
				}
				else if(JPGD_REG_ENDADD == offset)
				{/**
				  **���������buffer,һֱ�ڷ����ı䣬����������ݲ�׼ȷ
				  **/
					PRN_SCENE(pJpegHandle->pScenFile,CV200_JPEG_BASE + offset, (HI_U32)pStreamEndBuf);
					cnt++;
				}
				else
				{
					PRN_SCENE(pJpegHandle->pScenFile,CV200_JPEG_BASE + offset, pJpegHandle->s32RegData[cnt]);
					cnt++;
				}
			}
		}


}

/*****************************************************************************
* func			: HI_JPEG_OutScenData
* description	: get the scen data
				  CNcomment: ��ȡ�ֳ����� CNend\n
* param[in]	    : cinfo.                 CNcomment:�������         CNend\n
* param[in]	    : pStreamStartBuf.       CNcomment:������ʼ��ַ     CNend\n
* param[in]	    : pStreamEndBuf.         CNcomment:����������ַ     CNend\n
* param[in]	    : pData.                 CNcomment:���ݵ�ַ         CNend\n
* param[in]	    : s32DataSize.           CNcomment:���ݴ�С         CNend\n
* param[in]     : bStartFirst            CNcomment:��һ����������   CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_OutScenData(const struct jpeg_decompress_struct *cinfo, \
                                         HI_CHAR* pStreamStartBuf,                    \
                                         HI_CHAR* pStreamEndBuf,                      \
                                         HI_CHAR* pData,                              \
                                         HI_U64  u64DataSize,                         \
                                         HI_BOOL bStartFirst)
{

		 HI_U32 data 	   = 0;
		 HI_S32 offset	   = 0;
		
		 JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		 /**
		  ** output the scen message to file
		  ** CNcomment:�������ֳ� CNend\n
		  **/
		  HI_JPEG_GetScenData(cinfo);
		  HI_JPEG_PrintScenData(cinfo,pStreamStartBuf,pStreamEndBuf);
		  SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");
		  SCEN_PRINT(pJpegHandle->pScenFile,"	the dec data \n");
		  SCEN_PRINT(pJpegHandle->pScenFile,"=====================================================\n");
		  SCEN_PRINT(pJpegHandle->pScenFile,"======================= data begin ==================\n\n");
		  for(offset = 0; offset < u64DataSize; offset+=4)
		  {
		  
			   data =	(pData[offset+3] << 24)
					  | (pData[offset+2] << 16)
					  | (pData[offset+1] << 8)
					  | (pData[offset]);
			   
			   PRN_SCENE(pJpegHandle->pScenFile,(HI_U32)(pStreamStartBuf+offset),data);
			   /**
				**�ֳ��������Ҷ���������ܱ�ʵ�ʶ�1��2��3���ֽ�
				**/
		  
		  }
		  if(HI_TRUE == bStartFirst)
		  {
			  PRN_SCENE(pJpegHandle->pScenFile,CV200_JPEG_BASE,0x00000001);
		  }
		  else
		  {
			  PRN_SCENE(pJpegHandle->pScenFile,CV200_JPEG_BASE+4,0x00000001);
		  }
		  SCEN_PRINT(pJpegHandle->pScenFile,"\n======================= data end ==================\n");


}

/*****************************************************************************
* func			: HI_JPEG_SetSaveScen
* description	: if the decode failure, we want to debug should need the decode\n
                  scen,and use eda simulation.
				  CNcomment: �������ʧ������ϣ����EDA������ж�λ����Ҫ���������\n
				             ����������ʹ�� CNend\n
* param[in]	    :cinfo.       CNcomment:�������     CNend\n
* param[in]	    :bSaveScen.   CNcomment:�Ƿ񱣴��ֳ� CNend\n
* param[in]     :pFileName    CNcomment:�����ļ�     CNend\n
* retval		: HI_SUCCESS  CNcomment: �ɹ�	     CNend\n
* retval		: HI_FAILURE  CNcomment: ʧ��	     CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 HI_JPEG_SetSaveScen(const struct jpeg_decompress_struct *cinfo,HI_BOOL bSaveScen,HI_CHAR* pFileName)
{

	JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	pJpegHandle->bSaveScen = bSaveScen;
	pJpegHandle->pScenFileName = pFileName;

	return HI_SUCCESS;
	
}
#endif


#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE)
/*****************************************************************************
* func			: HI_JPEG_Suspend
* description	: test suspend.
				  CNcomment: �������� CNend\n
* param[in]	    : s32JpegDev
* param[ou]	    : *bSendSuspendSignal
* retval		: HI_SUCCESS
* retval		: HI_FAILURE
* others:		: NA
*****************************************************************************/
HI_S32 HI_JPEG_Suspend(HI_S32 s32JpegDev,HI_BOOL *bSendSuspendSignal)
{
	*bSendSuspendSignal = HI_TRUE;
	return ioctl(s32JpegDev, CMD_JPG_SUSPEND);
}

/*****************************************************************************
* func			: HI_JPEG_Resume
* description	: test resume.
				  CNcomment: �������Ѵ��� CNend\n
* param[in]	    : s32JpegDev
* param[ou]	    : *bSendSuspendSignal
* retval		: HI_SUCCESS
* retval		: HI_FAILURE
* others:		: NA
*****************************************************************************/
HI_S32 HI_JPEG_Resume(HI_S32 s32JpegDev,HI_BOOL *bSendSuspendSignal)
{
	*bSendSuspendSignal = HI_FALSE;
	return ioctl(s32JpegDev, CMD_JPG_RESUME);
}
#endif


/*****************************************************************************
* func			: HI_JPEG_GetDev
* description	: get the jpeg device.
			      CNcomment: ��ȡjpeg�豸 CNend\n
* param[in] 	: s32JpegDev CNcomment: �򿪵�jpeg�ڵ� CNend\n
* retval		: HI_SUCCESS
* retval		: HI_FAILURE
* others:		: NA
*****************************************************************************/
HI_S32 HI_JPEG_GetDev(HI_S32 s32JpegDev)
{
    return ioctl(s32JpegDev, CMD_JPG_GETDEVICE);
}


/*****************************************************************************
* func			: HI_JPEG_SaveBmp
* description	: save the phy data to bmp picture.
				  CNcomment: ������������ݵ�bmpͼƬ
				             RGB565,ARGB4444,ARGB1555,RGB888 and ARGB8888 CNend\n
* param[in]	    : u32DataPhy
* param[in]	    : u32Width
* param[in]	    : u32Height
* param[in]	    : u32Stride
* param[in]	    : cinfo
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_SaveBmp(HI_U32 u32DataPhy,HI_U32 u32Width,HI_U32 u32Height,HI_U32 u32Stride,const struct jpeg_decompress_struct *cinfo)
{
#ifdef CONFIG_JPEG_TEST_SAVE_BMP_PIC
     HI_CHAR exec[256];
	 HI_CHAR pColorSpace[256];
	 HI_CHAR *pFile = "data";
	 HI_CHAR pFileName[256];
	 static HI_U32 u32Cnt = 0;

	 switch(cinfo->out_color_space)
	 {
         case JCS_ARGB_8888:
         	strncpy(pColorSpace,"ABGR8888",strlen("ABGR8888"));
			pColorSpace[strlen("ABGR8888")] = '\0';
			break;
		 case JCS_ABGR_8888:
		 case JCS_RGBA_8888:
		 	strncpy(pColorSpace,"ARGB8888",strlen("ARGB8888"));
			pColorSpace[strlen("ARGB8888")] = '\0';
			break;
		 case JCS_ARGB_1555:
		 	strncpy(pColorSpace,"ABGR1555",strlen("ABGR1555"));
			pColorSpace[strlen("ABGR1555")] = '\0';
			break;
		 case JCS_ABGR_1555:
		 	strncpy(pColorSpace,"ARGB1555",strlen("ARGB1555"));
			pColorSpace[strlen("ARGB1555")] = '\0';
			break;
		  case JCS_RGB:
		  case JCS_YCbCr:
		  	strncpy(pColorSpace,"BGR888",strlen("BGR888"));
			pColorSpace[strlen("BGR888")] = '\0';
		  	break;
		  case JCS_BGR:
		  case JCS_CrCbY:
		  	strncpy(pColorSpace,"RGB888",strlen("RGB888"));
			pColorSpace[strlen("RGB888")] = '\0';
		  	break;
		  case JCS_RGB_565:
		  	strncpy(pColorSpace,"BGR565",strlen("BGR565"));
			pColorSpace[strlen("BGR565")] = '\0';
		  	break;
		  case JCS_BGR_565:
		  	strncpy(pColorSpace,"RGB565",strlen("RGB565"));
			pColorSpace[strlen("RGB565")] = '\0';
		  	break;
		  default:
		  	break;
	 }
	 /**
	  **android���Է��õ�·��Ϊ cd /data
	  **�� /data/./bmpGen, /data/.bmp
	  **/
#ifdef CONFIG_JPEG_ANDROID_SAVE
	 snprintf(exec, 256, "/data/./bmpGen 0x%x %d %d %d %s  %s/%s%d.bmp", 
              u32DataPhy,u32Width,u32Height,u32Stride,pColorSpace,BMP_DATA_FILE_DIR,pFile,u32Cnt);
#else
	 snprintf(exec, 256, "./bmpGen 0x%x %d %d %d %s  %s/%s%d.bmp", 
              u32DataPhy,u32Width,u32Height,u32Stride,pColorSpace,BMP_DATA_FILE_DIR,pFile,u32Cnt);
#endif

	 snprintf(pFileName,256,"%s/%s%d.bmp",BMP_DATA_FILE_DIR,pFile,u32Cnt);
	 	
     system(exec);
	 
	 u32Cnt++;

     #if 0
	 JPEG_TRACE("\n==================================================================================================\n");
	 JPEG_TRACE("has save the data to bmp picture,please press enter to save next picture!\n");
	 JPEG_TRACE("==================================================================================================\n");
	 getchar();
     #endif

	 #if 0
	 JPEG_TRACE("\n==================================================================================================\n");
	 JPEG_TRACE("has save the data to bmp picture,please press enter to save next picture!\n");
	 JPEG_TRACE("exec = %s\n",exec);
	 JPEG_TRACE("==================================================================================================\n");
	 #endif
	 
	 //mkdir("./../res/test_save_data_bmp/", 0775 )
	 //chmod(pFileName, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
     //chown("./../res/test_save_data_bmp/", 0, 0);
#else
	 /** deal with warning **/
    if(cinfo->is_decompressor || 0 == u32DataPhy || 0 == u32Width || 0 == u32Height || 0 == u32Stride)
		return;
#endif
}

/*****************************************************************************
* func			: HI_JPEG_SaveYUVSP
* description	: save the yuv semi-planer data
		  		  CNcomment: ���������yuvsp���� CNend\n
* param[in] 	: cinfo
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_SaveYUVSP(const struct jpeg_decompress_struct *cinfo)
{
#ifdef CONFIG_JPEG_TEST_SAVE_YUVSP_DATA
		HI_CHAR pFileName[256];
		HI_CHAR pHdrName[256];
		HI_CHAR *pFile = "yuvsp";
		static HI_U32 u32Count = 0;

		FILE* pOutFile = NULL;
		FILE* pHdrFile = NULL;
		HI_S32 s32Cnt     = 0;
		HI_S32 s32Cnt1    = 0;
		HI_CHAR *pTmp     = NULL;

		HI_CHAR pTmpCbCr[10000];   /** > 8192 **/

		HI_U32 u32YWidth  = 0;
		HI_U32 u32YHeight = 0;
		HI_U32 u32YStride = 0;
		HI_U32 u32CWidth  = 0;
		HI_U32 u32CHeight = 0;
		HI_U32 u32CStride = 0;
		HI_CHAR* pYAddr    = NULL;
		HI_CHAR* pUVAddr   = NULL;
		HI_JPEG_FMT_E eFmt = JPEG_FMT_BUTT;

		JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		if( 0 != access(CAPTURE_YUVSP_START, 0)) 
		{
			JPEG_TRACE("\n===============================================================================\n");
			JPEG_TRACE("���ȴ��� %s �ļ�\n",CAPTURE_YUVSP_START);
			JPEG_TRACE("touch %s\n",CAPTURE_YUVSP_START);
			JPEG_TRACE("===============================================================================\n");
			return;
		}
		
		snprintf(pFileName,256,"%s/%s%d.yuv",YUVSP_DATA_FILE_DIR,pFile,u32Count);
		snprintf(pHdrName,256,"%s/%s%d.hdr",YUVSP_DATA_FILE_DIR,pFile,u32Count);
		JPEG_TRACE("\n===============================================================================\n");
		JPEG_TRACE("the yuvsp file name is %s\n",pFileName);
		JPEG_TRACE("the hdr file name is %s\n",pHdrName);
		JPEG_TRACE("===============================================================================\n");

		pOutFile = fopen(pFileName,"wb+");
		if(NULL == pOutFile)
		{
			JPEG_TRACE("open %s failure\n",pFileName);
		}
		u32YWidth  = pJpegHandle->stJpegSofInfo.u32YWidth;
		u32YHeight = pJpegHandle->stJpegSofInfo.u32YHeight;
		u32YStride = pJpegHandle->stJpegSofInfo.u32YStride;
		u32CWidth  = pJpegHandle->stJpegSofInfo.u32CWidth;
		u32CHeight = pJpegHandle->stJpegSofInfo.u32CHeight;
		u32CStride = pJpegHandle->stJpegSofInfo.u32CbCrStride;
		pYAddr     = pJpegHandle->stMiddleSurface.pMiddleVir[0];
		pUVAddr    = pJpegHandle->stMiddleSurface.pMiddleVir[1];
		eFmt       = pJpegHandle->enImageFmt;

		/**===============================================================
		����Y��������
		===============================================================**/
		if(0 != u32YWidth)
		{
			pTmp = pYAddr;
			for(s32Cnt = 0; s32Cnt < (HI_S32)u32YHeight; s32Cnt++)
			{
				fwrite(pTmp, u32YWidth, 1, pOutFile);
				pTmp += u32YStride;
			}
		}
		if(0 != u32CWidth)
		{
			pTmp = pUVAddr;
			for( s32Cnt = 0; s32Cnt < (HI_S32)u32CHeight; s32Cnt ++ )
			{

				for(s32Cnt1=0; s32Cnt1 < (HI_S32)u32CWidth; s32Cnt1++ )
				{
					pTmpCbCr[s32Cnt1] = pTmp[2*s32Cnt1 + 1];
				}

				fwrite(pTmpCbCr, u32CWidth, 1, pOutFile );

				pTmp += u32CStride;
			}
			pTmp = pUVAddr;
			for( s32Cnt = 0; s32Cnt < (HI_S32)u32CHeight; s32Cnt ++ )
			{

				for(s32Cnt1=0; s32Cnt1 < (HI_S32)u32CWidth; s32Cnt1++ )
				{
					pTmpCbCr[s32Cnt1] = pTmp[2*s32Cnt1 + 0];
				}

				fwrite(pTmpCbCr, u32CWidth, 1, pOutFile);

				pTmp += u32CStride;
			}


		}

		fclose(pOutFile);


		pHdrFile = fopen(pHdrName,"wb+");
		if(NULL == pHdrFile)
		{
			JPEG_TRACE("open %s failure\n",pHdrName);
		}
		switch(eFmt)
		{
			case JPEG_FMT_YUV400:
				DADA_WRITE(pHdrFile, "format = \"Y\" ;\n");
				break;
			case JPEG_FMT_YUV420:
				DADA_WRITE(pHdrFile, "format = \"YUV420\" ;\n");
				break;
			case JPEG_FMT_YUV422_12:
				DADA_WRITE(pHdrFile, "format = \"YUV422\" ;\n");
				break;
			case JPEG_FMT_YUV422_21:
				DADA_WRITE(pHdrFile, "format = \"YUV422\" ;\n");
				break;
			case JPEG_FMT_YUV444:
				DADA_WRITE(pHdrFile, "format = \"YUV444\" ;\n");
				break;
			default:
				JPEG_TRACE("format is unknow ;\n");
				break;
		}

		DADA_WRITE(pHdrFile, "offset = 0 ;\n");
		DADA_WRITE(pHdrFile, "width = %d ;\n", u32YWidth);
		DADA_WRITE(pHdrFile, "height = %d ;\n", u32YHeight);
		DADA_WRITE(pHdrFile, "framerate = 50 ;\n");
		DADA_WRITE(pHdrFile, "loop = 1 ;\n");

		fclose(pHdrFile);

		u32Count++;
		//chmod(pFileName, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		//chmod(pHdrName, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
#else
		/** deal with warning **/
	    if(cinfo->is_decompressor)
    		return;
#endif
}


/*****************************************************************************
* func			: HI_JPEG_GetIfHardDec2ARGB8888
* description	: get if use jpeg hard decode to ARGB888,is not tde csc to ARGB8888
				  CNcomment: ��ȡ�Ƿ�ʹ��JPEGӲ��������ARGB8888�����ʱ�����ý���ֱ��ʵ�
							 ��������������ʾ�ֱ��ʣ�����JPEG����Ҫ�ü�����ʾ�ֱ��ʴ�С�ģ�
							 ����������ݾ���ȷ�ˡ��������òü����ж������ݵ� CNend\n
* param[in] 	: cinfo 				   �������
* param[in] 	: pbJpegHardDecARGB8888    �Ƿ�ΪJPEGӲ���������ARGB8888
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_GetIfHardDec2ARGB8888(const struct jpeg_decompress_struct *cinfo,HI_BOOL *pbJpegHardDecARGB8888)
{
	/** �Ƿ�ʹ��JPEGӲ������ **/
	#ifdef CONFIG_JPEG_HARDDEC2ARGB
	JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	*pbJpegHardDecARGB8888 = pJpegHandle->bDecARGB;
	#else
		if(cinfo->progressive_mode)/** deal with warning **/
    		*pbJpegHardDecARGB8888 = HI_FALSE;
		else
			*pbJpegHardDecARGB8888 = HI_FALSE;
	#endif
}


/*****************************************************************************
* func			: HI_JPEG_IfHardDec
* description	: whether is hard decode or soft decode
				  CNcomment: ��Ӳ�����뻹��������� CNend\n
* param[in]	    : cinfo       �������
* param[in]	    : pHardDec    �Ƿ�ΪӲ������
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_IfHardDec(const struct jpeg_decompress_struct *cinfo,HI_BOOL *pHardDec)
{

    JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    if(HI_TRUE == pJpegHandle->bHdecEnd)
    {
       *pHardDec  = HI_TRUE;
    }
	else
	{
	   *pHardDec  = HI_FALSE;
	}

}


#ifdef CONFIG_JPEG_TEST_CHIP_RANDOM_RESET
/** �����λ���� **/
/*****************************************************************************
* func			: HI_JPEG_HardDecNow
* description	: whether has hard decode now
		  		  CNcomment: �˿��Ƿ�������Ӳ������ CNend\n
* retval		: HI_SUCCESS;
* retval		: HI_FAILURE;
* others:		: NA
*****************************************************************************/
HI_S32 HI_JPEG_HardDecNow()
{


		HI_S32 s32CapabilityReg = 0;

		if( (NULL != g_pJpegRegVirAddr) && (FALSE == sg_bDecFinish) && (sg_s32JpegDev >= 0))
		{
			s32CapabilityReg  = JPEG_HDEC_ReadReg(g_pJpegRegVirAddr, JPGD_REG_TIME);
		}
		if(0 == s32CapabilityReg)
		{
			return HI_FAILURE;
		}
		else
		{
			JPEG_TRACE("==========================================================\n");
			JPEG_TRACE("s32CapabilityReg = %d\n",s32CapabilityReg);
			JPEG_TRACE("==========================================================\n");
		}

		return HI_SUCCESS;
		
}

/*****************************************************************************
* func			: HI_JPEG_RandomReset
* description	: reset the hard decode register
		  CNcomment: ��λӲ������Ĵ��� CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_RandomReset()
{
	 if(sg_s32JpegDev >= 0)
	 {
	 	 JPEG_TRACE("================================================================\n");
		 JPEG_TRACE("��ʼ��λ\n");
		 JPEG_TRACE("================================================================\n");
         ioctl(sg_s32JpegDev, CMD_JPG_RESET);
		 sleep(5);
	 }
}
/*****************************************************************************
* func			: HI_JPEG_SetDecState
* description	: set hard decode state
				  CNcomment: ���ý���״̬ CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_SetDecState(HI_BOOL bDecState)
{
	sg_bDecFinish = bDecState;
}

/*****************************************************************************
* func			: HI_JPEG_SetJpegDev
* description	: set Jpeg Dev
				  CNcomment: ���ý����豸ֵ CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_SetJpegDev(HI_S32 s32JpegDev)
{
	sg_s32JpegDev = s32JpegDev;
}

 /*****************************************************************************
* func			: HI_JPEG_SetJpegVir
* description	: set Jpeg map virtual value
				  CNcomment: ����ӳ�������ַ CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_SetJpegVir(volatile HI_CHAR *pRegisterVir)
{
	 g_pJpegRegVirAddr = pRegisterVir;
}

/*****************************************************************************
* func			: HI_JPEG_RandomResetInit
* description	: init the random reset valure
			      CNcomment: ��ʼ�������λ���Ե���ز���ֵ CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_RandomResetInit()
{
	sg_bDecFinish     = HI_FALSE;
	sg_s32JpegDev     = -1;
	g_pJpegRegVirAddr = NULL;
}

#endif


/*****************************************************************************
* func			: HI_JPEG_GetRegTime
* description	: get the jpeg hard register time value
				  CNcomment: ��ȡӲ������Ĵ���������ֵ CNend\n
* param[in]	    : cinfo         �������
* param[in]	    : u32DecTime    �Ĵ�������ʱ��
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_GetRegTime(const struct jpeg_decompress_struct *cinfo,HI_U32 *u32DecTime)
{
	JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
	*u32DecTime  = JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr, JPGD_REG_TIME);
}


#ifdef CONFIG_JPEG_FPGA_TEST_CONTINUE_STREAM_DDR_CHANGE
/*****************************************************************************
* func			: HI_JPEG_SetConStreamDDRChangeFlag
* description	: if the continue stream ddr change
	 			  CNcomment: ��������ַ�Ƿ����仯 CNend\n
* param[in] 	: bConDDRChange 		���÷����仯��־
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_SetConStreamDDRChangeFlag(HI_BOOL bConDDRChange)
{
	gs_bConStreamDDRChange = bConDDRChange;
}
/*****************************************************************************
* func			: HI_JPEG_GetConStreamDDRChangeFlag
* description	: get the whether the continue stream ddr change
	 			  CNcomment: ��ȡ��������ַ�Ƿ����仯��־ CNend\n
* param[in] 	: *pbConDDRChange 		��ȡ���״̬
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_GetConStreamDDRChangeFlag(HI_BOOL *pbConDDRChange)
{
	*pbConDDRChange = gs_bConStreamDDRChange;
}

#endif

#ifdef CONFIG_JPEG_FPGA_TEST_SET_DIFFERENT_OUTSTANDING_VALUE
/*****************************************************************************
* func			: HI_JPEG_SetOutstandingValue
* description	: set the outstanding value
				  CNcomment: ����outstanding��ֵ CNend\n
* param[in] 	: s32OutstandingValue	Ҫ���õ�ֵ��С
* param[in] 	: bSetFlag				Ҫ���ñ�־
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_SetOutstandingValue(HI_S32 s32OutstandingValue,HI_BOOL bSetFlag)
{
	gs_s32OutstandingValue = s32OutstandingValue;
	gs_bOutstandingFlag    = bSetFlag;
}
/*****************************************************************************
* func			: HI_JPEG_GetOutstandingValue
* description	: get the outstanding value
				  CNcomment: ��ȡoutstanding ��ֵ��С CNend\n
* param[in] 	: *ps32OutstandingValue 		Ҫ��ȡ��ֵ
* param[in] 	: *pbSetFlag					Ҫ�����õı�־
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID HI_JPEG_GetOutstandingValue(HI_S32 *ps32OutstandingValue,HI_BOOL *pbSetFlag)	

{
	*ps32OutstandingValue = gs_s32OutstandingValue;
	*pbSetFlag = gs_bOutstandingFlag;
}
#endif
