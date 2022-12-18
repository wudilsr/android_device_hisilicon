/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : hi_jpeg_hdec_test.h
Version		    : Initial Draft
Author		    : 
Created		    : 2014/06/20
Description	    : The user will use this api to realize some function
                  �����ר����������ʹ�õ�
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2014/06/20		    y00181162  		    Created file      	
******************************************************************************/

#ifndef __HI_JPEG_HDEC_TEST_H__
#define __HI_JPEG_HDEC_TEST_H__


/*********************************add include here******************************/

#include "jpeglib.h"
#include "hi_type.h"

#include "hi_jpeg_config.h"

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" 
{
#endif
#endif /* __cplusplus */


     /***************************** Macro Definition ******************************/
     /** \addtogroup 	 JPEG */
     /** @{ */  /** <!-- ��JPEG�� */

#ifdef CONFIG_JPEG_FPGA_TEST_SAVE_SCEN_ENABLE
	 #define  CV200_JPEG_BASE    0xf8c40000
	 #define  PRN_SCENE(pFile,addr,data)  fprintf(pFile, "W 0x%08x 0x%08x word single\n",addr,data)
	/**
	 **android���Է��õ�·��Ϊ cd /data/ mkdir register_scen
	 **�� /data/register_scen/.scen
	 **/
	 #define  SCEN_FILE_NAME                "./../res/test_data_dec_log_file/scen_file/output_file.scen"
     #define  SCEN_PRINT                     fprintf
#endif


#ifdef CONFIG_JPEG_TEST_SAVE_YUVSP_DATA
	#define DADA_WRITE( file,fmt, args... )\
		 do { \
				 fprintf(file,fmt, ##args );\
		 } while (0)
	#ifndef CONFIG_JPEG_ANDROID_SAVE
		#define YUVSP_DATA_FILE_DIR            "./../res/test_save_data_yuvsp"
		#define CAPTURE_YUVSP_START            "./../res/test_save_data_yuvsp/capture_start"
	#else/** Android **/
		#define YUVSP_DATA_FILE_DIR 		    "/mnt/sdcard/Movies/test_save_data_yuvsp"
		#define CAPTURE_YUVSP_START 		    "/mnt/sdcard/Movies/capture_start"
	#endif
#endif

#ifdef CONFIG_JPEG_TEST_SAVE_BMP_PIC
	#ifndef CONFIG_JPEG_ANDROID_SAVE
		#define BMP_DATA_FILE_DIR            "./../res/test_save_data_bmp"
	#else/** Android **/
		#define BMP_DATA_FILE_DIR            "/mnt/sdcard/Movies/test_save_data_bmp"
	#endif
#endif

	 /** @} */	/*! <!-- Macro Definition end */


	 /*************************** Enum Definition ****************************/
    /****************************************************************************/
	/*							   jpeg enum    					            */
	/****************************************************************************/
	
	/** \addtogroup      JPEG */
    /** @{ */  /** <!-- ��JPEG�� */

    /** @} */  /*! <!-- enum Definition end */

	/*************************** Structure Definition ****************************/
    /****************************************************************************/
	/*							   jpeg api structure    					    */
	/****************************************************************************/
	
	/** \addtogroup      JPEG */
    /** @{ */  /** <!-- ��JPEG�� */

	/** @} */  /*! <!-- Structure Definition end */

	
    /********************** Global Variable declaration **************************/
 
    /******************************* API declaration *****************************/


	/** \addtogroup      JPEG */
    /** @{ */  /** <!-- ��JPEG�� */

	 /*****************************************************************************
	 * func 		 : HI_JPEG_OpenScenFile
	 * description	 : open the scen file
					   CNcomment: �򿪵��ֳ����ļ� CNend\n
	 * param[in]	 : cinfo.		CNcomment:�������	   CNend\n
	 * retval		 : NA
	 * others:		 : NA
	 *****************************************************************************/
	 HI_S32 HI_JPEG_OpenScenFile(const struct jpeg_decompress_struct *cinfo);


	/*****************************************************************************
	* func			: HI_JPEG_CloseScenFile
	* description	: close the scen file
					  CNcomment: �رյ��ֳ����ļ� CNend\n
	* param[in] 	: cinfo.	   CNcomment:�������	  CNend\n
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_CloseScenFile(const struct jpeg_decompress_struct *cinfo);

	/*****************************************************************************
	* func			: HI_JPEG_OutScenData
	* description	: get the scen data
					  CNcomment: ��ȡ�ֳ����� CNend\n
	* param[in] 	: cinfo.				 CNcomment:������� 		CNend\n
	* param[in] 	: pStreamStartBuf.		 CNcomment:������ʼ��ַ 	CNend\n
	* param[in] 	: pStreamEndBuf.		 CNcomment:����������ַ 	CNend\n
	* param[in] 	: pData.				 CNcomment:���ݵ�ַ 		CNend\n
	* param[in] 	: u64DataSize.			 CNcomment:���ݴ�С 		CNend\n
	* param[in] 	: bStartFirst			 CNcomment:��һ����������	CNend\n
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_OutScenData(const struct jpeg_decompress_struct *cinfo, \
											 HI_CHAR* pStreamStartBuf,					  \
											 HI_CHAR* pStreamEndBuf,					  \
											 HI_CHAR* pData,							  \
											 HI_U64  u64DataSize,						  \
											 HI_BOOL bStartFirst);


	/*****************************************************************************
	* func			: HI_JPEG_SetSaveScen
	* description	: if the decode failure, we want to debug should need the decode\n
					  scen,and use eda simulation.
					  CNcomment: �������ʧ������ϣ����EDA������ж�λ����Ҫ���������\n
								 ����������ʹ�� CNend\n
	* param[in] 	:cinfo. 	  CNcomment:�������	 CNend\n
	* param[in] 	:bSaveScen.   CNcomment:�Ƿ񱣴��ֳ� CNend\n
	* param[in]     :pFileName    CNcomment:�����ļ�     CNend\n
	* retval		: HI_SUCCESS  CNcomment: �ɹ�		 CNend\n
	* retval		: HI_FAILURE  CNcomment: ʧ��		 CNend\n
	* others:		: NA
	*****************************************************************************/
	HI_S32 HI_JPEG_SetSaveScen(const struct jpeg_decompress_struct *cinfo,HI_BOOL bSaveScen,HI_CHAR* pFileName);

	/*****************************************************************************
	* func			: HI_JPEG_GetDev
	* description	: get the jpeg device.
					  CNcomment: ��ȡjpeg�豸 CNend\n
	* param[in] 	: s32JpegDev CNcomment: �򿪵�jpeg�ڵ� CNend\n
	* retval		: HI_SUCCESS
	* retval		: HI_FAILURE
	* others:		: NA
	*****************************************************************************/
	HI_S32 HI_JPEG_GetDev(HI_S32 s32JpegDev);

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
	HI_S32 HI_JPEG_Suspend(HI_S32 s32JpegDev,HI_BOOL *bSendSuspendSignal);

	/*****************************************************************************
	* func			: HI_JPEG_Resume
	* description	: test resume.
					  CNcomment: �������Ѵ��� CNend\n
	* param[in] 	: s32JpegDev
	* param[ou]	    : *bSendSuspendSignal
	* retval		: HI_SUCCESS
	* retval		: HI_FAILURE
	* others:		: NA
	*****************************************************************************/
	HI_S32 HI_JPEG_Resume(HI_S32 s32JpegDev,HI_BOOL *bSendSuspendSignal);


	/*****************************************************************************
	* func			: HI_JPEG_SaveBmp
	* description	: save the phy data to bmp picture.
					  CNcomment: ������������ݵ�bmpͼƬ CNend\n
	* param[in]	    : pDataPhy
	* param[in]	    : u32Width
	* param[in]	    : u32Height
	* param[in]	    : u32Stride
	* param[in]	    : cinfo
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_SaveBmp(HI_U32 u32DataPhy,HI_U32 u32Width,HI_U32 u32Height,HI_U32 u32Stride,const struct jpeg_decompress_struct *cinfo);


	/*****************************************************************************
	* func			: HI_JPEG_SaveYUVSP
	* description	: save the yuv semi-planer data
			  		  CNcomment: ���������yuvsp���� CNend\n
	* param[in] 	: cinfo
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_SaveYUVSP(const struct jpeg_decompress_struct *cinfo);


	/*****************************************************************************
	* func			: HI_JPEG_GetIfHardDec2ARGB8888
	* description	: get if use jpeg hard decode to ARGB888,is not tde csc to ARGB8888
					  CNcomment: ��ȡ�Ƿ�ʹ��JPEGӲ��������ARGB8888�����ʱ�����ý���ֱ��ʵ�
					             ��������������ʾ�ֱ��ʣ�����JPEG����Ҫ�ü�����ʾ�ֱ��ʴ�С�ģ�
					             ����������ݾ���ȷ�ˡ��������òü����ж������ݵ� CNend\n
	* param[in]	    : cinfo                    �������
	* param[in]	    : pbJpegHardDecARGB8888    �Ƿ�ΪJPEGӲ���������ARGB8888
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_GetIfHardDec2ARGB8888(const struct jpeg_decompress_struct *cinfo,HI_BOOL *pbJpegHardDecARGB8888);



	/*****************************************************************************
	* func			: HI_JPEG_IfHardDec
	* description	: whether is hard decode or soft decode
					  CNcomment: ��Ӳ�����뻹��������� CNend\n
	* param[in]	    : cinfo       �������
	* param[in]	    : pHardDec    �Ƿ�ΪӲ������
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_IfHardDec(const struct jpeg_decompress_struct *cinfo,HI_BOOL *pHardDec);
	

#ifdef CONFIG_JPEG_TEST_CHIP_RANDOM_RESET

   /*****************************************************************************
	* func			: HI_JPEG_HardDecNow
	* description	: whether has hard decode now
					  CNcomment: �˿��Ƿ�������Ӳ������ CNend\n
	* retval		: HI_SUCCESS;
	* retval		: HI_FAILURE;
	* others:		: NA
	*****************************************************************************/
	HI_S32 HI_JPEG_HardDecNow();

   /*****************************************************************************
	* func			: HI_JPEG_RandomReset
	* description	: reset the hard decode register
					  CNcomment: ��λӲ������Ĵ��� CNend\n
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_RandomReset();

   /*****************************************************************************
	* func			: HI_JPEG_SetDecState
	* description	: set hard decode state
					  CNcomment: ���ý���״̬ CNend\n
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_SetDecState(HI_BOOL bDecState);

    /*****************************************************************************
	* func			: HI_JPEG_SetJpegDev
	* description	: set Jpeg Dev
					  CNcomment: ���ý����豸ֵ CNend\n
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_SetJpegDev(HI_S32 s32JpegDev);

	/*****************************************************************************
	* func			: HI_JPEG_SetJpegVir
	* description	: set Jpeg map virtual value
					  CNcomment: ����ӳ�������ַ CNend\n
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_SetJpegVir(volatile HI_CHAR *pRegisterVir);
	 
	/*****************************************************************************
	* func			: HI_JPEG_RandomResetInit
	* description	: init the random reset valure
					  CNcomment: ��ʼ�������λ���Ե���ز���ֵ CNend\n
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_RandomResetInit();
	
#endif


	/*****************************************************************************
	* func			: HI_JPEG_GetRegTime
	* description	: get the jpeg hard register time value
					  CNcomment: ��ȡӲ������Ĵ���������ֵ CNend\n
	* param[in] 	: cinfo 		�������
	* param[in] 	: u32DecTime	�Ĵ�������ʱ��
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_GetRegTime(const struct jpeg_decompress_struct *cinfo,HI_U32 *u32DecTime);



#ifdef CONFIG_JPEG_FPGA_TEST_CONTINUE_STREAM_DDR_CHANGE
	/*****************************************************************************
	* func			: HI_JPEG_SetConStreamDDRChangeFlag
	* description	: if the continue stream ddr change
					  CNcomment: ��������ַ�Ƿ����仯 CNend\n
	* param[in] 	: bConDDRChange 		���÷����仯��־
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_SetConStreamDDRChangeFlag(HI_BOOL bConDDRChange);
	/*****************************************************************************
	* func			: HI_JPEG_GetConStreamDDRChangeFlag
	* description	: get the whether the continue stream ddr change
		 			  CNcomment: ��ȡ��������ַ�Ƿ����仯��־ CNend\n
	* param[in] 	: *pbConDDRChange 		��ȡ���״̬
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_GetConStreamDDRChangeFlag(HI_BOOL *pbConDDRChange);

#endif

#ifdef CONFIG_JPEG_FPGA_TEST_SET_DIFFERENT_OUTSTANDING_VALUE
	/*****************************************************************************
	* func			: HI_JPEG_SetOutstandingValue
	* description	: set the outstanding value
					  CNcomment: ����outstanding��ֵ CNend\n
	* param[in] 	: s32OutstandingValue	Ҫ���õ�ֵ��С
	* param[in] 	: bSetFlag	            Ҫ���ñ�־
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_SetOutstandingValue(HI_S32 s32OutstandingValue,HI_BOOL bSetFlag);

	/*****************************************************************************
	* func			: HI_JPEG_GetOutstandingValue
	* description	: get the outstanding value
					  CNcomment: ��ȡoutstanding ��ֵ��С CNend\n
	* param[in] 	: *ps32OutstandingValue 		Ҫ��ȡ��ֵ
	* param[in] 	: *pbSetFlag					Ҫ�����õı�־
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID HI_JPEG_GetOutstandingValue(HI_S32 *ps32OutstandingValue,HI_BOOL *pbSetFlag);
	
#endif

	/** @} */  /*! <!-- API declaration end */
	
    /****************************************************************************/



#ifdef __cplusplus
    
#if __cplusplus
   
}
#endif
#endif /* __cplusplus */

#endif /* __HI_JPEG_HDEC_TEST_H__*/
