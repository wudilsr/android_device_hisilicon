/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_signal.c
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


/*********************************add include here******************************/
#include "jpeg_hdec_signal.h"
#include "hi_jpeg_config.h"
#include "hi_jpeg_hal_api.h"

/***************************** Macro Definition ******************************/

#define SEM_UNDO        0x1000          /* undo the operation on exit */

/*************************** Structure Definition ****************************/

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

struct sembuf
{
  unsigned short int sem_num;   /* semaphore number */
  short int sem_op;             /* semaphore operation */
  short int sem_flg;            /* operation flag */
};


/********************** Global Variable declaration **************************/


/******************************* API forward declarations *******************/
extern int semop (int __semid, struct sembuf *__sops, size_t __nsops);

/******************************* API realization *****************************/

/***************************************************************************************
* func			: JPEG_HDEC_LockSignal
* description	: lock multi process or pthread.
				  CNcomment: 锁多进程和多线程 CNend\n
* param[in] 	: 
* retval		: HI_SUCCESS 成功
* retval		: HI_FAILURE 失败
* others:		: NA
***************************************************************************************/
HI_S32 JPEG_HDEC_LockSignal(HI_S32 s32JpegDev,HI_S32 *ps32SignalId)
{

	HI_S32 s32Ret = HI_SUCCESS;
	HI_S32 semid  = 0;
	struct sembuf sb;

	s32Ret = ioctl(s32JpegDev, CMD_JPG_GETSIGNAL_ID, &semid);
	if(s32Ret == HI_FAILURE) 
	{
		JPEG_TRACE("get id failure\n");
		return HI_FAILURE;
	}
	
	sb.sem_num = 0;        /** 第0个信号量 **/
	sb.sem_op = -1;        /** 信号量减－ **/
	sb.sem_flg = SEM_UNDO; /** 指定undo标志，确保进程被kill时，linux会自动释放此信号量 **/
    if(syscall(SYS_semop, semid, &sb, 1) == -1)
	{
		JPEG_TRACE("lock signal failure\n");
		return HI_FAILURE;
	}

	*ps32SignalId = semid;
	
	return HI_SUCCESS;
	
}
/***************************************************************************************
* func			: JPEG_HDEC_UnLockSignal
* description	: unlock multi process or pthread.
				  CNcomment: 解锁多进程和多线程 CNend\n
* param[in] 	: 
* retval		: HI_SUCCESS 成功
* retval		: HI_FAILURE 失败
* others:		: NA
***************************************************************************************/
HI_VOID JPEG_HDEC_UnLockSignal(HI_S32 s32SignalID)
{
	struct sembuf sb;
	
	sb.sem_num = 0;        /** 第0个信号量 **/
	sb.sem_op  = 1;        /** 信号量加－  **/
	sb.sem_flg = SEM_UNDO; /** 指定undo标志，确保进程被kill时，linux会自动释放此信号量 **/
	if(syscall(SYS_semop, s32SignalID, &sb, 1) == -1)
	{
		JPEG_TRACE("unlock signal failure\n");
		return;
	}
	
}


/***************************************************************************************
* func			: JPEG_HDEC_GetTid
* description	: get pthread id
				  CNcomment: 获取线程ID CNend\n
* param[in] 	: 
* retval		: HI_SUCCESS 成功
* retval		: HI_FAILURE 失败
* others:		: NA
***************************************************************************************/
HI_U32 JPEG_HDEC_GetTid()
{
	return (HI_U32)syscall(SYS_gettid);
}

#endif
