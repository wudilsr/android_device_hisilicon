/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_adp.h
Version		    : Initial Draft
Author		    : 
Created		    : 2014/06/20
Description	    : the adp realize in this file
                  CNcomment: �����ʵ�ֶ�������ļ��� CNend\n
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2014/06/20		    y00181162  		    Created file      	
******************************************************************************/

#ifndef __JPEG_HDEC_ADP_H__
#define __JPEG_HDEC_ADP_H__


/*********************************add include here******************************/

#include  "jpeglib.h"
#include  "hi_type.h"


/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" 
{
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ******************************/
    /** \addtogroup 	 JPEG ADP MACRO */
    /** @{ */  /** <!-- ��JPEG ADP MACRO�� */


	 /** @} */	/*! <!-- Macro Definition end */


	 /*************************** Enum Definition ****************************/

	/** \addtogroup      JPEG ADP ENUM */
    /** @{ */  /** <!-- ��JPEG ADP ENUM�� */


	
    /** @} */  /*! <!-- enum Definition end */

	/*************************** Structure Definition ****************************/

	/** \addtogroup      JPEG ADP STRUCTURE */
    /** @{ */  /** <!-- ��JPEG ADP STRUCTURE�� */

	/** @} */  /*! <!-- Structure Definition end */

	
    /********************** Global Variable declaration **************************/
 
    /******************************* API declaration *****************************/

	/** \addtogroup      JPEG ADP API */
    /** @{ */  /** <!-- ��JPEG ADP API�� */
	

	/*****************************************************************************
	* func			: JPEG_HDEC_GetImagInfo
	* description	: get jpeg picture information
					  CNcomment:  ��ȡͼƬ��Ϣ CNend\n
	* param[in] 	: cinfo 	  CNcomment: �������	CNend\n
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID JPEG_HDEC_GetImagInfo(j_decompress_ptr cinfo);
		
		 
	 /*****************************************************************************
	 * func 		 : JPEG_HDEC_SetPara
	 * description	 : set the parameter that hard decode need
	                   CNcomment: ����Ӳ��������Ҫ�Ĳ�����Ϣ        CNend\n
	 * param[in]	 : cinfo         CNcomment: �������    CNend\n
	 * retval		 : HI_SUCCESS    CNcomment: �ɹ�        CNend\n
	 * retval		 : HI_FAILURE    CNcomment: ʧ��        CNend\n
	 * others:		 : NA
	 *****************************************************************************/
	 HI_S32 JPEG_HDEC_SetPara(const struct jpeg_decompress_struct *cinfo);
	 
	/*****************************************************************************
	* func			: JPEG_HDEC_SetStreamBuf
	* description	: set stream buffer message
					  CNcomment: ��������buffer�Ĵ��� 	   CNend\n
	* param[in] 	: cinfo 		CNcomment: �������    CNend\n
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID JPEG_HDEC_SetStreamBuf(const struct jpeg_decompress_struct *cinfo);

	/*****************************************************************************
	* func			: JPEG_HDEC_SendStreamFromPhyMem
	* description	: get the stream from physics memory
	                  CNcomment:  ������Դ�����������ڴ�Ĵ���ʽ   CNend\n
	* param[in]     : cinfo       CNcomment:  �������     CNend\n
	* retval	    : HI_SUCCESS  CNcomment:  �ɹ�         CNend\n
	* retval	    : HI_FAILURE  CNcomment:  ʧ��         CNend\n
	* others:	    : NA
	*****************************************************************************/
	HI_S32 JPEG_HDEC_SendStreamFromPhyMem(j_decompress_ptr cinfo);

	
	/*****************************************************************************
	* func			: JPEG_HDEC_SendStreamFromReturnPhyMem
	* description	: get the stream from physics memory
	                  CNcomment:  ������Դ�����������ڴ�Ĵ���ʽ�������������ƵĴ���   CNend\n
	* param[in]     : cinfo       CNcomment:  �������     CNend\n
	* retval	    : HI_SUCCESS  CNcomment:  �ɹ�         CNend\n
	* retval	    : HI_FAILURE  CNcomment:  ʧ��         CNend\n
	* others:	    : NA
	*****************************************************************************/
	HI_S32 JPEG_HDEC_SendStreamFromReturnPhyMem(j_decompress_ptr cinfo);
	
	/*****************************************************************************
	* func			: JPEG_HDEC_SendStreamFromVirMem
	* description	: get the stream from virtual memory
	                  CNcomment:  ������Դ�����ڴ�Ĵ���ʽ   CNend\n
	* param[in]     : cinfo       CNcomment:  �������     CNend\n
	* retval	    : HI_SUCCESS  CNcomment:  �ɹ�         CNend\n
	* retval	    : HI_FAILURE  CNcomment:  ʧ��         CNend\n
	* others:	    : NA
	*****************************************************************************/
	HI_S32 JPEG_HDEC_SendStreamFromVirMem(j_decompress_ptr cinfo);
	
	/*****************************************************************************
	* func			: JPEG_HDEC_SendStreamFromFile
	* description	: get the stream from file
	                  CNcomment:  ������Դ�ļ��Ĵ���ʽ
	* param[in]     : cinfo       CNcomment:  �������
	* param[in]     : NA
	* retval	    : HI_SUCCESS  CNcomment:  �ɹ�
	* retval	    : HI_FAILURE  CNcomment:  ʧ��
	* others:	    : NA
	*****************************************************************************/
	HI_S32 JPEG_HDEC_SendStreamFromFile(j_decompress_ptr cinfo);

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
	HI_S32 JPEG_HDEC_SendStreamFromFileWithConDDRChange(j_decompress_ptr cinfo);

	/*****************************************************************************
	* func			: JPEG_HDEC_SendStreamFromCallBack
	* description	: CNcomment:  ������Դ�ⲿ����
	* param[in] 	: cinfo 	  CNcomment:  �������
	* param[in] 	: NA
	* retval		: HI_SUCCESS  CNcomment:  �ɹ�
	* retval		: HI_FAILURE  CNcomment:  ʧ��
	* others:		: NA
	*****************************************************************************/
	HI_S32 JPEG_HDEC_SendStreamFromCallBack(j_decompress_ptr cinfo);


	/** @} */  /*! <!-- API declaration end */
	
    /****************************************************************************/



#ifdef __cplusplus
    
#if __cplusplus
   
}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_HDEC_ADP_H__*/
