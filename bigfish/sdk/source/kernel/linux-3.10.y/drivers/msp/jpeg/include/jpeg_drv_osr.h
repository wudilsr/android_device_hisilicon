/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_drv_osr.h
Version		    : Initial Draft
Author		    : 
Created		    : 2015/03/01
Description	    : The user will use this api to realize some function
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2015/03/01		    y00181162  		    Created file      	
******************************************************************************/
#ifndef __JPEG_DRV_OSR_H__
#define __JPEG_DRV_OSR_H__


/*********************************add include here******************************/
#include <linux/syscalls.h>
#include <linux/ipc.h>

#include "hi_jpeg_config.h"
#include "hi_jpeg_drv_api.h"
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
	/** \addtogroup	  JPEG */
	/** @{ */	/** <!--[JPEG]*/

    /** @} */  /** <!-- ==== enum Definition end ==== */
	
	/*************************** Structure Definition ****************************/
#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL
	/** jpeg device imformation */
	/** CNcomment:jpeg�豸��Ϣ */
	typedef struct hiJPG_OSRDEV_S
	{
	
		HI_S32	s32SignalId;		   /**< �ź���ID					**/
		HI_BOOL bSuspendSignal; 	   /**< whether get suspend signal   **//**<CNcomment:��ȡ�����ź�	   */
		HI_BOOL bResumeSignal;		   /**< whether get resume signal	 **//**<CNcomment:��ȡ���������ź�	*/
		HI_BOOL bDecTask;			   /**< whether have jpeg dec task	**//**<CNcomment:�Ƿ���jpeg��������  */
		HI_BOOL bClockOpen; 		   /**< ����ʱ���ʱ��״̬		  **/
		HI_BOOL bResetState;		   /**< ����ʱ��ĸ�λ״̬		   **/
		HI_BOOL bMceUse;			   /**< �Ƿ�MCE��jpeg�豸		   **/
		JPG_INTTYPE_E	   IntType;   /**< lately happened halt type  **/
		wait_queue_head_t  QWaitInt;  /**< waite halt queue 		  **/
	
	}JPG_OSRDEV_S;
	
#else
	/** jpeg device imformation */
	/** CNcomment:jpeg�豸��Ϣ */
	typedef struct hiJPG_OSRDEV_S
	{
	
		HI_BOOL bSuspendSignal; 	 /**< whether get suspend signal  *//**<CNcomment:��ȡ�����ź�		 */
		HI_BOOL bResumeSignal;		   /**< whether get resume signal	*//**<CNcomment:��ȡ���������ź�  */
		HI_BOOL bEngageFlag;		  /**< whether be occupied, HI_TRUE if be occupied */
		HI_BOOL bDecTask;			  /**< whether have jpeg dec task	*//**<CNcomment:�Ƿ���jpeg��������	*/
		HI_BOOL bClockOpen; 		  /**< ����ʱ���ʱ��״̬ **/
		HI_BOOL bResetState;		   /**< ����ʱ��ĸ�λ״̬ **/
		HI_BOOL bLock;				   /**< �Ѿ�������״̬	   **/
		HI_BOOL bMceUse;			   /**< �Ƿ�MCE��jpeg�豸		   **/
		HI_U32 SystemAnomalCnt;
        HI_U32 OmxDecHandle;
		struct semaphore   SemGetDev; /**< protect the device to occupy the operation singnal */
		struct file 	   *pFile;
		JPG_INTTYPE_E	   IntType; 	 /**< lately happened halt type  */
		wait_queue_head_t  QWaitInt;	 /**< waite halt queue			 */
		wait_queue_head_t  QWaitMutex;	 /**< �ͷ��ź���				 */
	
	}JPG_OSRDEV_S;

	/** dispose close device */
	/** CNcomment:���豸���� */
	typedef struct hiJPG_DISPOSE_CLOSE_S
	{
	
		 HI_S32 s32SuspendClose;
		 HI_S32 s32DecClose;
		 HI_BOOL bOpenUp;
		 HI_BOOL bSuspendUp;
		 HI_BOOL bRealse;
	
	}JPG_DISPOSE_CLOSE_S;
	
#endif
    
	/** \addtogroup	  JPEG */
	/** @{ */	/** <!--[JPEG]*/

	
	/** @} */  /** <!-- ==== Structure Definition End ==== */
	
    /********************** Global Variable declaration **************************/
 
    /******************************* API declaration *****************************/

	/** \addtogroup	  JPEG */
	/** @{ */	/** <!--[JPEG]*/

	
	/***************************************************************************************
	* func			: jpg_osr_open
	* description	: open jpeg device
					  CNcomment: ��jpeg�豸 CNend\n
	* param[in] 	: *inode
	* param[in] 	: *file
	* retval		: HI_SUCCESS
	* retval		: HI_FAILURE
	* others:		: NA
	***************************************************************************************/
	HI_S32 jpg_osr_open(struct inode *inode, struct file *file);
	/***************************************************************************************
	* func			: jpg_osr_close
	* description	: close jpeg device
					  CNcomment: �ر�jpeg�豸 CNend\n
	* param[in] 	: *inode
	* param[in] 	: *file
	* retval		: HI_SUCCESS
	* retval		: HI_FAILURE
	* others:		: NA
	***************************************************************************************/
	HI_S32 jpg_osr_close( struct inode *inode, struct file *file);
	/***************************************************************************************
	* func			: jpg_osr_mmap
	* description	: mmap register ddr
					  CNcomment: ӳ��Ĵ�����ַ CNend\n
	* param[in] 	: *inode
	* param[in] 	: *file
	* retval		: HI_SUCCESS
	* retval		: HI_FAILURE
	* others:		: NA
	***************************************************************************************/
	HI_S32 jpg_osr_mmap(struct file * filp, struct vm_area_struct *vma);


	/***************************************************************************************
	* func			: jpg_do_cancel_reset
	* description	: cancel reset jpeg register
					  CNcomment: ������λ CNend\n
	* param[in] 	: HI_VOID
	* retval		: NA
	* others:		: NA
	***************************************************************************************/
	HI_VOID jpg_do_cancel_reset(HI_VOID);


	/***************************************************************************************
	* func			: jpg_do_reset
	* description	: reset jpeg register
					  CNcomment: ��λ CNend\n
	* param[in] 	: HI_VOID
	* retval		: NA
	* others:		: NA
	***************************************************************************************/
	HI_VOID jpg_do_reset(HI_VOID);

	/***************************************************************************************
	* func			: jpg_do_clock_off
	* description	: close the jpeg clock
					  CNcomment: �ر�jpegʱ�� CNend\n
	* param[in] 	: HI_VOID
	* retval		: NA
	* others:		: NA
	***************************************************************************************/
	HI_VOID jpg_do_clock_off(HI_VOID);

	
	/***************************************************************************************
	* func			: jpg_do_clock_on
	* description	: open the jpeg clock
					  CNcomment: ��jpegʱ�� CNend\n
	* param[in] 	: HI_VOID
	* retval		: NA
	* others:		: NA
	***************************************************************************************/
	HI_VOID jpg_do_clock_on(HI_VOID);


	 /***************************************************************************************
	 * func 		 : jpg_select_clock_frep
	 * description	 : select the clock frequence
					   CNcomment: jpegʱ��Ƶ��ѡ�� CNend\n
	 * param[in]	 : HI_VOID
	 * retval		 : NA
	 * others:		 : NA
	 ***************************************************************************************/
	 HI_VOID jpg_select_clock_frep(HI_VOID);



    /***************************************************************************************
	* func			: jpg_osr_dec
	* description	: jpeg hard decode
					  CNcomment: jpeg���� CNend\n
	* param[in] 	: *stDecInfo
	* retval		: HI_SUCCESS
	* retval		: HI_FAILURE
	* others:		: NA
	***************************************************************************************/
	HI_S32 jpg_osr_dec(HI_JPEG_DECINFO_S *stDecInfo);

	/***************************************************************************************
	* func			: jpg_osr_getlupixsum
	* description	: get lu pix sum
					  CNcomment: ��ȡ����ֵ�� CNend\n
	* param[in] 	: s32Handle
	* retval		: HI_SUCCESS
	* retval		: HI_FAILURE
	* others:		: NA
	***************************************************************************************/
	HI_VOID jpg_osr_getlupixsum(HI_S32 s32Handle,HI_U64* pu64LuPixValue);


	/***************************************************************************************
	* func			: jpg_osr_setmemtype
	* description	: set memory type.
					  CNcomment: �����ڴ����� CNend\n
	* param[in] 	: s32Handle
	* param[in] 	: u32MemMask
	* retval		: HI_SUCCESS �ɹ�
	* retval		: HI_FAILURE ʧ��
	* others:		: NA
	***************************************************************************************/
	HI_VOID jpg_osr_setmemtype(HI_S32 s32Handle,HI_U32 u32MemMask);
	
	/** @} */  /** <!-- ==== API Declaration End ==== */

    /****************************************************************************/



#ifdef __cplusplus
    
#if __cplusplus
   
}
#endif
#endif /* __cplusplus */

#endif /* __JPEG_DRV_OSR_H__*/
