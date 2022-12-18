/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_error.h
Version		    : Initial Draft
Author		    : 
Created		    : 2014/06/20
Description	    : Describes the error codes of the Jpeg
                  CNcomment: Jpeg�������ļ� CNend\n
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2014/06/20		    y00181162  		    Created file      	
******************************************************************************/
#ifndef __JPEG_HDEC_ERROR_H__
#define __JPEG_HDEC_ERROR_H__


/*********************************add include here******************************/

#include "hi_type.h"

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" 
{
#endif
#endif /* __cplusplus */



	 /*************************** Enum Definition ****************************/
	
	/** \addtogroup      JPEG ERROR ENUM */
    /** @{ */  /** <!-- ��JPEG ERROR ENUM�� */


	/** the error level */
	/** CNcomment:�����𼶱� */
	typedef enum tagJPEG_LOG_ERRLEVEL_E
	{
		JPEG_LOG_LEVEL_DEBUG    = 0,     /**< debug level                      *//**<CNcomment:���Լ���       */
		JPEG_LOG_LEVEL_INFO     = 1,	   /**< informational                    *//**<CNcomment:��Ϣ           */
		JPEG_LOG_LEVEL_NOTICE   = 2,     /**< normal but significant condition *//**<CNcomment:��������Ҫ���� */
		JPEG_LOG_LEVEL_WARNING  = 3,     /**< warning conditions               *//**<CNcomment:�澯����       */
		JPEG_LOG_LEVEL_ERROR    = 4,     /**< error conditions                 *//**<CNcomment:��������       */
		JPEG_LOG_LEVEL_CRIT     = 5,     /**< critical conditions              *//**<CNcomment:��Ҫ����       */
		JPEG_LOG_LEVEL_ALERT    = 6,     /**< action must be taken immediately *//**<CNcomment:�����ж�       */
		JPEG_LOG_LEVEL_FATAL    = 7,     /**< just for compatibility with previous version *//**<CNcomment:��֮ǰ�汾������ */
		JPEG_LOG_LEVEL_BUTT
	} JPEG_LOG_ERRLEVEL_E;


	/**Jpeg Module encoding*/
	/** CNcomment:jpeg ģ����� */
	typedef enum
	{
		JPEG_MOD_COMM      = 0,       /**< comm moduld  *//**<CNcomment:����ģ��      */
		JPEG_MOD_MEM,                 /**< comm moduld  *//**<CNcomment:�ڴ����ģ��  */
		JPEG_MOD_BUTT
	} HIGO_MOD_E;


	/** Common error codes of the Jpeg */
	/** CNcomment:Jpeg ���������� */
	typedef enum tagJPEG_COMM_ERR_E
	{
		ERR_COMM_UNSUPPORT_SCALE   =  0,  /**< the scale can not support *//**<CNcomment:���ű�����֧�� */
        ERR_COMM_NOMEM,
		ERR_COMM_BUTT
	} JPEG_COMM_ERR_E;

    /** @} */  /*! <!-- enum Definition end */


	/***************************** Macro Definition ******************************/
	/** \addtogroup 	 JPEG ERROR MACRO */
	/** @{ */  /** <!-- ��JPEG ERROR MACRO�� */

    /** if some where failure,return */
	/** CNcomment:�ж��Ƿ��˳� */
    #define JPEG_ASSERT(cond,retvalue) \
	do  \
	{   \
	    if(cond)            \
		{  \
		   return retvalue;  \
		}  \
	}   \
	while(0)
		

	/** Error IDs of JPEG projects */
	/** CNcomment:JPEG ��Ŀ����ID = 0xB0000000 */
    #define JPEG_ERR_APPID           (0x80000000L + 0x30000000L)

	/** Macros for defining the error codes of the Jpeg */
	/** CNcomment:Jpeg �����붨��꣬��16λ��ʾJPEG��ĳ��ĳ��ID�� 13-16λ��ʾ����ȼ�������13λ��ʾ������*/
    #define JPEG_DEF_ERR( module, errid) \
		((HI_S32)((JPEG_ERR_APPID) | (((HI_U32)module) << 16) | (((HI_U32)JPEG_LOG_LEVEL_ERROR) << 13) | ((HI_U32)errid)))



	/** the scale can not support (0xB0008000) */
	/** CNcomment:���ű�����֧�� 0xB0008000 */
    #define JPEG_ERR_UNSUPPORT_SCALE      JPEG_DEF_ERR(JPEG_MOD_COMM, ERR_COMM_UNSUPPORT_SCALE)


    #define JPEG_ERR_NOMEM      JPEG_DEF_ERR(JPEG_MOD_COMM, ERR_COMM_NOMEM)

	

	/** @} */	/*! <!-- Macro Definition end */

	/*************************** Structure Definition ****************************/
	
    /********************** Global Variable declaration **************************/
 
    /******************************* API declaration *****************************/
	
    /****************************************************************************/



#ifdef __cplusplus
    
#if __cplusplus
   
}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_HDEC_ERROR_H__*/
