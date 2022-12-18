/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : hi_jpge_henc_api.h
Version		    : Initial Draft
Author		    : 
Created		    : 2014/05/14
Description	    : The user will use this api to realize some function
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2014/05/14		    y00181162  		    Created file      	
******************************************************************************/

#ifndef __HI_JPGE_HENC_API_H__
#define __HI_JPGE_HENC_API_H__


/*********************************add include here******************************/

#include "jpeglib.h"
#include "hi_type.h"

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" 
{
#endif
#endif /* __cplusplus */


     /***************************** Macro Definition ******************************/
	 /** \addtogroup	  JPGE */
	 /** @{ */	/** <!--[JPGE]*/

     /** Maximum number of data components */
	 /** CNcomment:������ݷ����� CNend */
     #define MAX_IN_PIXEL_COMPONENT_NUM            3
	 
     /** @} */  /** <!-- ==== Macro Definition end ==== */

	 /*************************** Enum Definition ****************************/
    /****************************************************************************/
	/*							   jpge enum    					            */
	/****************************************************************************/
	
	/** \addtogroup	  JPGE */
	/** @{ */	/** <!--[JPGE]*/

    /** @} */  /** <!-- ==== enum Definition end ==== */
	
	/*************************** Structure Definition ****************************/
    /****************************************************************************/
	/*							   jpeg api structure    					    */
	/****************************************************************************/
	
	/** \addtogroup	  JPGE */
	/** @{ */	/** <!--[JPGE]*/

	/** Structure of the stream message */
	/** CNcomment:�������������Ļ�����Ϣ CNend */
	typedef struct hiJPEG_STREAM_INFO_S
	{
		 HI_CHAR* pInPhy[MAX_IN_PIXEL_COMPONENT_NUM + 1];/**�������buffer**/
		 HI_CHAR* pInVir[MAX_IN_PIXEL_COMPONENT_NUM + 1];/**�������buffer**/
		 HI_U32   u32InStride[MAX_IN_PIXEL_COMPONENT_NUM];
		 HI_U32   u32InSize[MAX_IN_PIXEL_COMPONENT_NUM];
         HI_BOOL  bUserPhyMem;
	}HI_JPEG_STREAM_INFO_S;

	/** @} */  /** <!-- ==== Structure Definition End ==== */
	
    /********************** Global Variable declaration **************************/
 
    /******************************* API declaration *****************************/
	/** \addtogroup	  JPGE */
	/** @{ */	/** <!--[JPGE]*/

	/** 
	\brief set stream message. CNcomment:����������Ϣ CNend
	\attention \n
	if want to use this function,should call before jpeg_write_raw_data or jpeg_write_scanlines.
	if not call this we should check\n
	CNcomment:���Ҫ���ã�������jpeg_write_raw_data����jpeg_write_scanlines֮ǰ����CNend\n
	
	\param[in]	cinfo. CNcomment:������� CNend
	\param[in]	pstStreamInfo. CNcomment:�������������Ϣ CNend
	
	\retval ::HI_SUCCESS 
	\retval ::HI_FAILURE
	
	\see \n
	::HI_JPGE_SetStreamInfo
	*/
	 HI_S32 HI_JPGE_SetStreamInfo(const struct jpeg_compress_struct *cinfo, const HI_JPEG_STREAM_INFO_S *pstStreamInfo);


	/** 
	\brief get jpeg enc inflexion. CNcomment:��ȡ�����Ӳ������Ĺյ� CNend
	\attention \n
	HI_JPEG_GetInflexion should have called jpeg_create_compress.\n
	CNcomment:�ڵ���HI_JPGE_GetInflexion֮ǰ�����Ѿ��������˱����� CNend\n

	\param[in]	cinfo. CNcomment:������� CNend
	\param[out]	pu32flexionSize. CNcomment:����յ��С CNend
	
	\retval ::HI_SUCCESS 
	\retval ::HI_FAILURE
	
	\see \n
	::HI_JPGE_GetInflexion
	*/
	HI_S32 HI_JPGE_GetInflexion(const struct jpeg_compress_struct *cinfo, HI_U32 *pu32flexionSize);
	

	/** 
	\brief set jpeg enc inflexion. CNcomment:��Ӳ������֧�ֵ�����£����ñ���Ĺյ� CNend
	\attention \n
	HI_JPGE_SetInflexion should have called jpeg_create_compress.if no call this \n
	function,use the default flexion \n
	CNcomment:�����ڴ����������֮����øú�����Ҫ��û�����ùյ㣬ʹ��Ĭ�ϵĹյ��С CNend\n

	\param[in]	cinfo. CNcomment:������� CNend
	\param[in]	u32flexionSize. CNcomment:Ҫ���õı���յ��С CNend
	
	\retval ::HI_SUCCESS 
	\retval ::HI_FAILURE
	
	\see \n
	::HI_JPGE_SetInflexion
	*/
	HI_S32 HI_JPGE_SetInflexion(const struct jpeg_compress_struct *cinfo, const HI_U32 u32flexionSize);
	

	/** @} */  /** <!-- ==== API Declaration End ==== */

    /****************************************************************************/



#ifdef __cplusplus
    
#if __cplusplus
   
}
#endif
#endif /* __cplusplus */

#endif /* __HI_JPGE_HENC_API_H__*/
