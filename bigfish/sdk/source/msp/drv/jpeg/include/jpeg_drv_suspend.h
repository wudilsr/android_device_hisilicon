/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_drv_suspend.h
Version		    : Initial Draft
Author		    : 
Created		    : 2015/03/01
Description	    : the suspend dispose
                  CNcomment: �������� CNend\n
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2015/03/01		    y00181162  		    Created file      	
******************************************************************************/
#ifndef __JPEG_DRV_SUSPEND_H__
#define __JPEG_DRV_SUSPEND_H__


/*********************************add include here******************************/

#include "hi_jpeg_config.h"

#ifdef CONFIG_JPEG_SUSPEND

#include "hi_type.h"
#include "hi_jpeg_drv_api.h"

/*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" 
{
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ******************************/

	 /*************************** Enum Definition ****************************/

	/*************************** Structure Definition ****************************/

    /********************** Global Variable declaration **************************/
 
    /******************************* API declaration *****************************/
	/***************************************************************************************
	* func 		 : jpg_osr_suspend
	* description: get the suspend signale.
				   CNcomment: �յ������ź� CNend\n
	* param[in]	 : *pdev
	* param[in]	 : state
	* retval	 : HI_SUCCESS �ɹ�
	* retval	 : HI_FAILURE ʧ��
	* others:	 : NA
	***************************************************************************************/
	HI_S32 jpg_osr_suspend(PM_BASEDEV_S *pdev, pm_message_t state);

	/***************************************************************************************
	* func 		 : jpg_osr_resume
	* description: get the resume signale.
				   CNcomment: �յ����������ź� CNend\n
	* param[in]	 : *pdev
	* retval	 : HI_SUCCESS �ɹ�
	* retval	 : HI_FAILURE ʧ��
	* others:	 : NA
	***************************************************************************************/
	HI_S32 jpg_osr_resume(PM_BASEDEV_S *pdev);
	
	/*****************************************************************************
	* func			: JPG_WaitDecTaskDone
	* description	: waite the jpeg decode task done
					  CNcomment: �ȴ������������  CNend\n
	* param[in] 	: NULL
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID JPG_WaitDecTaskDone(HI_VOID);


	/*****************************************************************************
	* func			: JPG_GetResumeValue
	* description	: get the value that resume need
					  CNcomment: ��ȡ����������Ҫ��ֵ  CNend\n
	* param[in] 	: *pSaveInfo
	* retval		: NA
	* others:		: NA
	*****************************************************************************/
	HI_VOID JPG_GetResumeValue(HI_JPG_SAVEINFO_S *pSaveInfo);

    /****************************************************************************/



#ifdef __cplusplus
    
#if __cplusplus
   
}
#endif
#endif /* __cplusplus */

#endif

#endif /* __JPEG_DRV_SUSPEND_H__*/
