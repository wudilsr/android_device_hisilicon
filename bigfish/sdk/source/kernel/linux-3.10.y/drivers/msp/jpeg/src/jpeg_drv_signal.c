/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_drv_signal.c
Version		    : Initial Draft
Author		    : 
Created		    : 2015/03/01
Description	    : The user will use this api to realize some function
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2015/03/01		    y00181162  		    Created file      	
******************************************************************************/

#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL


/*********************************add include here******************************/
#include "jpeg_drv_signal.h"
#include "hi_jpeg_config.h"

/***************************** Macro Definition ******************************/


/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/


/******************************* API forward declarations *******************/
extern long os_semctl(int semid, int semnum, int cmd, unsigned long arg);
extern long os_semget(key_t key, int nsems, int semflg);


/******************************* API realization *****************************/

/***************************************************************************************
* func			: jpeg_create_signal
* description	: create signal.
				  CNcomment: �����ź��� CNend\n
* param[in] 	: 
* retval		: HI_SUCCESS �ɹ�
* retval		: HI_FAILURE ʧ��
* others:		: NA
***************************************************************************************/
HI_S32 jpeg_create_signal(HI_S32 *ps32Semid)
{

	HI_S32 semid  = 0;

	/**
	 ** ��ȡһ���ź�����Ȩ��֧�ֶ���̹�����ź���
	 ** �ڶ����������źŵƵ���Ŀ
	 **/
	if ((semid = os_semget(IPC_PRIVATE, 1, IPC_CREAT | 0666)) == -1) 
	{
		JPEG_TRACE("create signal failure\n");
		return HI_FAILURE;
	}
	/**
	 ** init signal ��ʼ���ź��� 
	 ** SETVAL:����ĳ���������źŵƵ�ֵΪarg.val
	 **/
	if(os_semctl(semid, 0, SETVAL, 1) < 0) 
	{
		JPEG_TRACE("init signal failure\n");
		return HI_FAILURE;
	}

	*ps32Semid = semid;
	
	return HI_SUCCESS;
	
}

/***************************************************************************************
* func			: jpeg_destory_signal
* description	: destory signal.
				  CNcomment: �����ź��� CNend\n
* param[in] 	: 
* retval		: HI_SUCCESS �ɹ�
* retval		: HI_FAILURE ʧ��
* others:		: NA
***************************************************************************************/
HI_S32 jpeg_destory_signal(HI_S32 s32Semid)
{

	HI_S32 s32Ret = HI_SUCCESS;

	s32Ret = os_semctl(s32Semid, 0, IPC_RMID, 1);
	if(s32Ret == HI_FAILURE) 
	{
		JPEG_TRACE("destory id failure\n");
		return HI_FAILURE;
	}
	
	return HI_SUCCESS;
	
}
#endif
