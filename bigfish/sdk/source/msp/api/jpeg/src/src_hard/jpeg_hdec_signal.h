/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_signal.h
Version		    : Initial Draft
Author		    : 
Created		    : 2015/01/25
Description	    : The user will use this api to realize some function
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2015/01/25		    y00181162  		    Created file      	
******************************************************************************/

#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL


#ifndef __JPEG_HDEC_SIGNAL_H__
#define __JPEG_HDEC_SIGNAL_H__


/*********************************add include here******************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/ioctl.h>


#include "hi_type.h"

/*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
   extern "C" 
{
#endif
#endif /* __cplusplus */


     /***************************** Macro Definition ******************************/
	 /** \addtogroup	  JPEG */
	 /** @{ */	/** <!--[JPEG]*/


     /** @} */  /** <!-- ==== Macro Definition end ==== */

	 /*************************** Enum Definition ****************************/
    /****************************************************************************/
	/*							   jpeg enum    					            */
	/****************************************************************************/
	
	/** \addtogroup	  JPEG */
	/** @{ */	/** <!--[JPEG]*/

    /** @} */  /** <!-- ==== enum Definition end ==== */
	
	/*************************** Structure Definition ****************************/
    /****************************************************************************/
	/*							   jpeg api structure    					    */
	/****************************************************************************/
	
	/** \addtogroup	  JPEG */
	/** @{ */	/** <!--[JPEG]*/

	
	/** @} */  /** <!-- ==== Structure Definition End ==== */
	
    /********************** Global Variable declaration **************************/
 
    /******************************* API declaration *****************************/

	/** \addtogroup	  JPEG */
	/** @{ */	/** <!--[JPEG]*/

	/***************************************************************************************
	* func			: JPEG_HDEC_LockSignal
	* description	: lock multi process or pthread.
					  CNcomment: 锁多进程和多线程 CNend\n
	* param[in] 	: 
	* retval		: HI_SUCCESS 成功
	* retval		: HI_FAILURE 失败
	* others:		: NA
	***************************************************************************************/
	HI_S32 JPEG_HDEC_LockSignal(HI_S32 s32JpegDev,HI_S32 *ps32SignalId);
	/***************************************************************************************
	* func			: JPEG_HDEC_UnLockSignal
	* description	: unlock multi process or pthread.
					  CNcomment: 解锁多进程和多线程 CNend\n
	* param[in] 	: 
	* retval		: HI_SUCCESS 成功
	* retval		: HI_FAILURE 失败
	* others:		: NA
	***************************************************************************************/
	HI_VOID JPEG_HDEC_UnLockSignal(HI_S32 s32SignalID);


	/***************************************************************************************
	* func			: JPEG_HDEC_GetTid
	* description	: get pthread id
					  CNcomment: 获取线程ID CNend\n
	* param[in] 	: 
	* retval		: HI_SUCCESS 成功
	* retval		: HI_FAILURE 失败
	* others:		: NA
	***************************************************************************************/
	HI_U32 JPEG_HDEC_GetTid();
	
	/** @} */  /** <!-- ==== API Declaration End ==== */

    /****************************************************************************/



#ifdef __cplusplus
    
#if __cplusplus
   
}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_HDEC_SIGNAL_H__*/


#endif
