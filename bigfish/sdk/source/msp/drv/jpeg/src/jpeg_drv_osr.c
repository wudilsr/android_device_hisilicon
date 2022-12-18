/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_drv_osr.c
Version		    : Initial Draft
Author		    : 
Created		    : 2015/03/01
Description	    : 
Function List 	: 

			  		  
History       	:
Date				Author        		Modification
2015/03/01		    y00181162  		    Created file      	
******************************************************************************/



/*********************************add include here******************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/ioctl.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/spinlock.h>
#include <linux/mm.h>
#include <linux/stddef.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <asm/atomic.h>
#include <asm/bitops.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/pgtable.h>

#include "hi_gfx_comm_k.h"
#include "hi_jpeg_drv_api.h"
#include "hi_jpeg_reg.h"
#include "jpeg_drv_hal.h"
#include "jpeg_drv_suspend.h"
#include "jpeg_drv_error.h"
#include "jpeg_drv_parse.h"
#include "jpeg_drv_setpara.h"
#include "jpeg_drv_osr.h"
#include "jpeg_drv_mem.h"
#include "hi_type.h"

#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL
#include "jpeg_drv_signal.h"
#endif


#ifdef CONFIG_JPEG_PROC_ENABLE
	#include "jpeg_drv_proc.h"
#endif

#ifdef CONFIG_JPEG_USE_SDK_CRG_ENABLE
#include "hi_reg_common.h"
	#if   defined(CHIP_TYPE_hi3712)      \
	   || defined(CHIP_TYPE_hi3716m)     \
	   || defined(CHIP_TYPE_hi3716mv310) \
	   || defined(CHIP_TYPE_hi3110ev500) \
       || defined(CHIP_TYPE_hi3716mv320) \
	   || defined(CONFIG_GFX_BVT_SDK)
		#include "hi_reg_sys.h"
		#include "hi_reg_peri.h"
		#include "hi_reg_crg.h"
	#else
		#include "hi_drv_reg.h"
	#endif
#endif

#ifndef CONFIG_GFX_BVT_SDK
#include "drv_jpeg_ext.h"
#endif

/***************************** Macro Definition ******************************/


/** module register name */
/** CNcomment:��SDKע��ģ���� */
#define JPEGNAME                  "hi_jpeg_irq"
#define JPEGDEVNAME               "jpeg"


/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/

extern HI_JPEG_PROC_INFO_S s_stJpeg6bProcInfo;

/** read or write register value */
/** CNcomment: ����д�Ĵ�����ֵ  */
#ifndef CONFIG_JPEG_USE_SDK_CRG_ENABLE
static volatile HI_U32  *s_pJpegCRG     = HI_NULL;
#endif
static volatile HI_U32  *s_pJpegRegBase = HI_NULL;
static JPG_OSRDEV_S *s_pstruJpgOsrDev   = HI_NULL;

HI_GFX_DECLARE_MUTEX(s_JpegMutex);      /**< dec muxtex     *//**<CNcomment:������̱߳��� */
HI_GFX_DECLARE_MUTEX(s_SuspendMutex);   /**< suspend muxtex *//**<CNcomment:�������̱߳��� */

/******************************* API forward declarations *******************/
static long jpg_osr_ioctl(struct file *file, HI_U32 Cmd, unsigned long Arg);

/******************************* API realization *****************************/

#ifndef CONFIG_GFX_BVT_SDK
DECLARE_GFX_NODE(JPEGDEVNAME,jpg_osr_open, jpg_osr_close,jpg_osr_mmap,jpg_osr_ioctl,jpg_osr_suspend, jpg_osr_resume);
#else
DECLARE_GFX_NODE(JPEGDEVNAME,jpg_osr_open, jpg_osr_close,jpg_osr_mmap,jpg_osr_ioctl,NULL, NULL);
#endif

/***************************************************************************************
* func			: jpg_do_cancel_reset
* description	: cancel reset jpeg register
				  CNcomment: ������λ CNend\n
* param[in] 	: HI_VOID
* retval		: NA
* others:		: NA
***************************************************************************************/
HI_VOID jpg_do_cancel_reset(HI_VOID)
{
#ifdef CONFIG_JPEG_USE_SDK_CRG_ENABLE
		volatile HI_U32* pBusyAddr = NULL;
		volatile U_PERI_CRG31 unTempValue;
		pBusyAddr	 = s_pJpegRegBase;
		/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		[31:2]	reserve 	   : ����
		[1]		whether reset  : �Ƿ�λ��־
		0: has reset   : �Ѿ���λ
		1: no reset    : û�и�λ
		[0]		start decode   : JPEG���������Ĵ���
		1: startup dec : ����JPEG���н��룬���������󣬴˼Ĵ������Զ���0��
		++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

		/** when reset,should cancle reset */
		/** CNcomment:����Ѿ���λ��������λ,�������ܽ�����һ֡������ */
		while (*pBusyAddr & 0x2)
		{	
			/*nothing to do!*/
        }
		/** the 4 bit write 0 */
		/** CNcomment:��4bitд0����λ,0x10�ǵ�4bit���ĸ�bit�������Ǹ��ط�Ϊ1 */
		unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
		unTempValue.bits.jpgd_srst_req  = 0x0;
		g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;	
#else
		volatile HI_U32* pResetAddr = NULL;
		volatile HI_U32* pBusyAddr = NULL;

		pResetAddr   = s_pJpegCRG;
		pBusyAddr    = s_pJpegRegBase;

		*pResetAddr |= JPGD_RESET_REG_VALUE;

		#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_TEST_CHIP_RANDOM_RESET)
		JPEG_TRACE("\n=====================================\n\n\n");
		JPEG_TRACE("begin reset\n");
		#endif
		while (*pBusyAddr & 0x2)
		{	
			/*nothing to do!*/
		}
		#if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_TEST_CHIP_RANDOM_RESET)
		JPEG_TRACE("end reset\n\n\n");
		JPEG_TRACE("=====================================\n");
		#endif
		*pResetAddr &= JPGD_UNRESET_REG_VALUE;
#endif
}

/***************************************************************************************
* func			: jpg_do_reset
* description	: reset jpeg register
				  CNcomment: ��λ CNend\n
* param[in] 	: HI_VOID
* retval		: NA
* others:		: NA
***************************************************************************************/
HI_VOID jpg_do_reset(HI_VOID)
{
#ifdef CONFIG_JPEG_USE_SDK_CRG_ENABLE
		volatile U_PERI_CRG31 unTempValue;
		unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
		/** when dec finish, should reset to dec next jpeg steam */
		/** CNcomment:���������֮��Ҫ���и�λ,������һ֡����,����bitд1 */
		unTempValue.bits.jpgd_srst_req  = 0x1;
		g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;
#else
		volatile HI_U32* pResetAddr = NULL;

		pResetAddr   = s_pJpegCRG;
		
		*pResetAddr |= JPGD_RESET_REG_VALUE;
#endif
}

/***************************************************************************************
* func			: jpg_do_clock_off
* description	: close the jpeg clock
				  CNcomment: �ر�jpegʱ�� CNend\n
* param[in] 	: HI_VOID
* retval		: NA
* others:		: NA
***************************************************************************************/
HI_VOID jpg_do_clock_off(HI_VOID)
{
#ifdef CONFIG_JPEG_USE_SDK_CRG_ENABLE
		volatile U_PERI_CRG31 unTempValue;
		unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
		/** the 0 bit write 0 */
		/** CNcomment:��0bitд0 ��0x0 & 0x1 = 0 */
		unTempValue.bits.jpgd_cken = 0x0;
		g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;

#else
		volatile HI_U32* pResetAddr = NULL;
		pResetAddr   = s_pJpegCRG;
		*pResetAddr &= JPGD_CLOCK_OFF;
#endif

}

/***************************************************************************************
* func			: jpg_do_clock_on
* description	: open the jpeg clock
				  CNcomment: ��jpegʱ�� CNend\n
* param[in] 	: HI_VOID
* retval		: NA
* others:		: NA
***************************************************************************************/
HI_VOID jpg_do_clock_on(HI_VOID)
{
#ifdef CONFIG_JPEG_USE_SDK_CRG_ENABLE
		volatile U_PERI_CRG31 unTempValue;
		unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
		/** the 0 bit write 1 */
		/** CNcomment:��0bitд1��0x1 & 0x1 = 1 */
		unTempValue.bits.jpgd_cken  = 0x1;
		g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;

#else
		volatile HI_U32* pResetAddr = NULL;
		pResetAddr   = s_pJpegCRG;
		*pResetAddr |= JPGD_CLOCK_ON;
#endif
}

 /***************************************************************************************
 * func 		 : jpg_select_clock_frep
 * description	 : select the clock frequence
				   CNcomment: jpegʱ��Ƶ��ѡ�� CNend\n
 * param[in]	 : HI_VOID
 * retval		 : NA
 * others:		 : NA
 ***************************************************************************************/
HI_VOID jpg_select_clock_frep(HI_VOID)
 {
#ifdef CONFIG_JPEG_USE_SDK_CRG_ENABLE

		volatile U_PERI_CRG31 unTempValue;
		unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
		/** the 8 bit write 0(200M) or 1(150M) **/
		/** CNcomment:��8bitд0���� 1,����Ĵ�������ͨ��himd.l JPGD_CRG_REG_PHYADDR���鿴 **/
		unTempValue.bits.jpgd_clk_sel  = 0x0;
		g_pstRegCrg->PERI_CRG31.u32 = unTempValue.u32;

#else
		volatile HI_U32* pResetAddr = NULL;
		pResetAddr   = s_pJpegCRG;
		*pResetAddr = 0x000;
#endif
 }

 /***************************************************************************************
 * func 		 : jpg_osr_mmap
 * description	 : mmap jpeg device
				   CNcomment: ӳ��jpeg�豸 CNend\n
 * param[in]	 : *filp
 * param[in]	 : *vma
 * retval		 : HI_SUCCESS
 * retval		 : HI_FAILURE
 * others:		 : NA
 ***************************************************************************************/
HI_S32 jpg_osr_mmap(struct file * filp, struct vm_area_struct *vma)
{
      
		/** if api call mmap,will call this function */
		/** CNcomment: �ϲ�map jpeg�豸��ʱ����� */
        HI_U32 Phys;
        HI_U64 u64BaseAddr = JPGD_REG_BASEADDR;
		HI_U32 u32Length   = 0;
		
        /**
         ** set map parameter 
         **/
        /**
         **ҳ����4096����
         **/
        u32Length = (JPGD_REG_LENGTH + 4096 - 1) & (~(4096 - 1));
        if((vma->vm_end - vma->vm_start) > u32Length)
        {/**
          **��ȫ���⣺��������������������±�����Ȩ��ROOT
          **���ﱣ֤�����Ĵ�������
          **/
			return -EINVAL;
 		}
		
		Phys = (u64BaseAddr >> PAGE_SHIFT);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 10, 0))
        vma->vm_flags |= VM_RESERVED | VM_LOCKED | VM_IO;
#else
		vma->vm_flags |= VM_LOCKED | VM_IO;
#endif

        /** cancel map **/
        vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

        if (remap_pfn_range(vma, vma->vm_start, Phys, vma->vm_end - vma->vm_start, 
                            vma->vm_page_prot))
        {
            return -EAGAIN;
        }

        return HI_SUCCESS;

    
}
/***************************************************************************************
* func 		 : jpg_osr_getintstatus
* description: 
			   CNcomment: ��ȡ�ж�״̬ CNend\n
* param[in]	 : *pdev
* retval	 : HI_SUCCESS �ɹ�
* retval	 : HI_FAILURE ʧ��
* others:	 : NA
***************************************************************************************/
static HI_S32 jpg_osr_getintstatus(DRV_JPEG_EXT_GETINTTYPE_S *pstIntType)
{
	JPG_GETINTTYPE_S IntInfo;
	HI_S32 Ret = 0;
	HI_S32 loop = 0;
	HI_U32 FirstCount = 1;
	HI_S32 IRQ_NUM    = JPGD_IRQ_NUM;
	HI_U32 u32StartTimeMs = 0; /** ms **/
	HI_U32 u32EndTimeMs   = 0; /** ms **/
	/**
	 ** checkt parameter
	 **/
	if(NULL == pstIntType)
	{
		return HI_FAILURE;
	}

	IntInfo.IntType = pstIntType->IntType;
	IntInfo.TimeOut = pstIntType->TimeOut;

	
	disable_irq(IRQ_NUM);

   /**
	** get the halt type 
	**/
	if((JPG_INTTYPE_NONE != s_pstruJpgOsrDev->IntType) || (0 == IntInfo.TimeOut))
	{

		
		IntInfo.IntType = s_pstruJpgOsrDev->IntType;
		s_pstruJpgOsrDev->IntType = JPG_INTTYPE_NONE;
		enable_irq(IRQ_NUM);

		pstIntType->IntType = IntInfo.IntType;

		return HI_SUCCESS;
	}
	enable_irq(IRQ_NUM);

	do
	{			
		Ret = wait_event_interruptible_timeout(s_pstruJpgOsrDev->QWaitInt, 
					  JPG_INTTYPE_NONE != s_pstruJpgOsrDev->IntType, 
					  IntInfo.TimeOut * HZ/1000);
		 
		loop = 0;

		if(Ret > 0 || (JPG_INTTYPE_NONE != s_pstruJpgOsrDev->IntType))
		{

			disable_irq(IRQ_NUM);
			IntInfo.IntType = s_pstruJpgOsrDev->IntType;
			s_pstruJpgOsrDev->IntType = JPG_INTTYPE_NONE;
			enable_irq(IRQ_NUM);
			break;
		} 
		else if( -ERESTARTSYS == Ret)
		{

			if(FirstCount)
			{
				HI_GFX_GetTimeStamp(&u32StartTimeMs,NULL);
				FirstCount = 0;
				loop = 1;
			} 
			else
			{
				HI_GFX_GetTimeStamp(&u32EndTimeMs,NULL);
				/** avoid dead lock **/
				loop = ((u32EndTimeMs - u32StartTimeMs) <  IntInfo.TimeOut)?1:0; 
				/** check timeout **/
				if(!loop)
				{
					 return HI_FAILURE;
				}
			}
			
		} 
		else /** == 0(wait timeout) and others **/ 
		{
			return HI_FAILURE;
		}
		
	}while(loop);

	pstIntType->IntType = IntInfo.IntType;

	return HI_SUCCESS;

}


#ifndef CONFIG_GFX_BVT_SDK

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
HI_S32 jpg_osr_suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{

#ifdef CONFIG_JPEG_USE_SDK_CRG_ENABLE
	 volatile U_PERI_CRG31 unTempValue;
#endif

#ifdef CONFIG_JPEG_SUSPEND
 
	 HI_S32 Ret  = 0;
 
	 /** if you continue suspend and resume,this can be protected */
	 /** CNcomment:�����ͣ�Ĵ������ѣ�������𱣻����ã�ʼ��ʹ�����뻽����Բ��� */
	 Ret  = down_interruptible(&s_SuspendMutex);
	 if(HI_TRUE == s_pstruJpgOsrDev->bDecTask)
	 {
		 JPG_WaitDecTaskDone();
		 /** tell the api received suspend signal */
		 /** CNcomment:֪ͨӦ�ò��д����ź��� */
		 s_pstruJpgOsrDev->bSuspendSignal = HI_TRUE;
		 #if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE)
		 JPEG_TRACE("\n======================================\n");
		 JPEG_TRACE("=== %s ���ô����źųɹ�!\n",__FUNCTION__);
		 JPEG_TRACE("======================================\n");
		 #endif
	 }
#endif

#ifdef CONFIG_JPEG_USE_SDK_CRG_ENABLE
	 unTempValue.u32 = g_pstRegCrg->PERI_CRG31.u32;
	 if(0x1 == unTempValue.bits.jpgd_cken)
	 {
		s_pstruJpgOsrDev->bClockOpen = HI_TRUE;/** ʱ�Ӵ򿪵� **/
	 }
	 else
	 {
		s_pstruJpgOsrDev->bClockOpen = HI_FALSE;/** ʱ�ӹرյ� **/
	 }
	 if(0x1 == unTempValue.bits.jpgd_srst_req)
	 {
		s_pstruJpgOsrDev->bResetState = HI_TRUE;/** ��λ״̬ **/
	 }
	 else
	 {
		s_pstruJpgOsrDev->bResetState = HI_FALSE;/** ������λ״̬ **/
	 }
#endif

     jpg_do_reset();
     jpg_do_clock_off();
	 
	 return HI_SUCCESS;
	 
	 
}
 
/***************************************************************************************
* func 		 : jpg_osr_resume
* description: get the resume signale.
			   CNcomment: �յ����������ź� CNend\n
* param[in]	 : *pdev
* retval	 : HI_SUCCESS �ɹ�
* retval	 : HI_FAILURE ʧ��
* others:	 : NA
***************************************************************************************/
HI_S32 jpg_osr_resume(PM_BASEDEV_S *pdev)
{	 
 
#ifdef CONFIG_JPEG_SUSPEND
 
	 /** tell the api received resume signal */
	 /** CNcomment:֪ͨӦ�ò��д��������ź��� */
	 if(HI_TRUE == s_pstruJpgOsrDev->bDecTask)
	 {
		 s_pstruJpgOsrDev->bResumeSignal  = HI_TRUE;
		 #if defined(CONFIG_JPEG_FPGA_TEST_ENABLE) && defined(CONFIG_JPEG_FPGA_TEST_SUSPEND_ENABLE)
		 JPEG_TRACE("\n======================================\n");
		 JPEG_TRACE("=== %s ���ô��������źųɹ�!\n",__FUNCTION__);
		 JPEG_TRACE("======================================\n");
		 #endif
	 }
	 up(&s_SuspendMutex);
#endif

	 /** if suspend resume,the clock should open,if not open **/
	 /** when you read and write register,the system will no work**/
	 /** CNcomment:���ڴ����Ѿ���ʱ�ӹر��ˣ�Ҫ�ǻ��ѵ�ʱ��û�д򿪣���
      **           ϵͳ��������޷��������� **/
     if(HI_TRUE == s_pstruJpgOsrDev->bClockOpen)
     {
		 jpg_do_clock_on();
		 if(HI_FALSE == s_pstruJpgOsrDev->bResetState)
		 {/**����ǰ���ڳ�����λ״̬����������Ҫ������λ **/
		 	 jpg_do_reset();
	     	 jpg_do_cancel_reset();
		 }
     }
	 return HI_SUCCESS;
	 
}

/***************************************************************************************
* func 		 : jpg_osr_getdev
* description: 
			   CNcomment: ��ȡ�豸 CNend\n
* param[in]	 : *pdev
* retval	 : HI_SUCCESS �ɹ�
* retval	 : HI_FAILURE ʧ��
* others:	 : NA
***************************************************************************************/
static HI_S32 jpg_osr_getdev(HI_VOID)
{
#ifdef HI_MCE_SUPPORT
    if(down_interruptible(&s_JpegMutex))
    {
	   return HI_FAILURE;
    }
    /** open the clock          **/
	/** CNcomment: �򿪹���ʱ�� **/
	jpg_do_clock_on();
	/** select clock frequence  **/
	/** CNcomment: ѡ��ʱ��Ƶ�� **/
	jpg_select_clock_frep();
	
	/** reset register                        **/
	/** CNcomment: ��λ�Ĵ���ʹ֮�ܹ����¹��� **/
	jpg_do_reset();
	/** cancle the reset,now can work   **/
	/** CNcomment: ������λʹ֮�ܹ����� **/
	jpg_do_cancel_reset();
	
	/** trun the halt status  **/
	/** CNcomment:            **/
	JpgHalSetIntMask(0x0);

	s_pstruJpgOsrDev->bMceUse = HI_TRUE;
		
#endif
	
 	return HI_SUCCESS;
	
}

/***************************************************************************************
* func 		 : jpg_osr_releasedev
* description: 
			   CNcomment: �ͷ��豸 CNend\n
* param[in]	 : *pdev
* retval	 : HI_SUCCESS �ɹ�
* retval	 : HI_FAILURE ʧ��
* others:	 : NA
***************************************************************************************/
static HI_S32 jpg_osr_releasedev(HI_VOID)
{
	#ifdef HI_MCE_SUPPORT
		up(&s_JpegMutex);
	    jpg_do_reset();
        jpg_do_clock_off();
		s_pstruJpgOsrDev->bMceUse = HI_FALSE;
	#endif
 	return HI_SUCCESS;
}

/***************************************************************************************
* func 		 : jpg_osr_reset
* description: 
			   CNcomment: ��λ CNend\n
* param[in]	 : *pdev
* retval	 : HI_SUCCESS �ɹ�
* retval	 : HI_FAILURE ʧ��
* others:	 : NA
***************************************************************************************/
static HI_VOID jpg_osr_reset(HI_VOID)
{
	#ifdef HI_MCE_SUPPORT
		jpg_do_reset();
		jpg_do_cancel_reset();
	#endif
}

static JPEG_EXPORT_FUNC_S s_JpegExportFuncs =
{ 
	.pfnJpegGetIntStatus = jpg_osr_getintstatus,
	.pfnJpegGetDev		 = jpg_osr_getdev,
	.pfnJpegReleaseDev	 = jpg_osr_releasedev,
	.pfnJpegReset		 = jpg_osr_reset,
	.pfnJpegSuspend 	 = jpg_osr_suspend,
	.pfnJpegResume		 = jpg_osr_resume,
};

#endif



/***************************************************************************************
* func 		 : jpg_osr_showversion
* description: 
			   CNcomment: ��ӡ�汾�� CNend\n
* param[in]	 : *pdev
* retval	 : HI_SUCCESS �ɹ�
* retval	 : HI_FAILURE ʧ��
* others:	 : NA
***************************************************************************************/
static HI_VOID jpg_osr_showversion(HIGFX_MODE_ID_E ModID)
{
#if !defined(CONFIG_GFX_COMM_VERSION_DISABLE) && !defined(CONFIG_GFX_COMM_DEBUG_DISABLE) && defined(MODULE)	
 
	 HI_CHAR MouleName[7][10] = {"tde","jpegdec","jpegenc","fb","png", "higo", "gfx2d"};
	 HI_CHAR Version[160]	  = "SDK_VERSION:["MKMARCOTOSTR(SDK_VERSION)"] Build Time:["__DATE__", "__TIME__"]";
 
	 if (ModID >= HIGFX_BUTT_ID)
		 return;
	 
	 GFX_Printk("Load hi_%s.ko success.\t(%s)\n", MouleName[ModID],Version);
	
	 return;
 
#endif
}


#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL
 /***************************************************************************************
 * func 		 : jpg_osr_open
 * description	 : open jpeg device
				   CNcomment: ��jpeg�豸 CNend\n
 * param[in]	 : *inode
 * param[in]	 : *file
 * retval		 : HI_SUCCESS
 * retval		 : HI_FAILURE
 * others:		 : NA
 ***************************************************************************************/
 HI_S32 jpg_osr_open(struct inode *inode, struct file *file)
 {/**
   **������Է���һ���ṹ������ڴ�Ȼ��ֵ��file->private_data
   **��Ϊfile->private_data�����һֱ���ڵģ��������ʹ���������������
   **�Լ�����Ľṹ��������൱��ȫ�ֱ���
   **/
#ifdef HI_MCE_SUPPORT
	 if(HI_TRUE == s_pstruJpgOsrDev->bMceUse)
	 {/**
	   ** ���п�������������£���ʧ�ܣ��ϲ�ʹ�����
	   ** �����Ͳ����Ӳ�����в����ˣ���MCE������֮����ʹ��Ӳ�����룬����
	   ** �����˲������ĸ����ԣ���ֹ����close����ʧ�����������ⷢ����
	   ** ����һ�����û�����⣬���Ǹպ�mce release�豸��ʱ�������û�̬�Ľ��롣
	   ** �����û�а취����ˣ�ֻ�����û���MCE���֮�����������ˡ�
	   **/
		 return HI_FAILURE;
	 }
#endif
		 
	 return HI_SUCCESS;
 
 }
 
  /***************************************************************************************
  * func		  : jpg_osr_close
  * description   : close jpeg device
					CNcomment: �ر�jpeg�豸 CNend\n
  * param[in]	  : *inode
  * param[in]	  : *file
  * retval		  : HI_SUCCESS
  * retval		  : HI_FAILURE
  * others: 	  : NA
  ***************************************************************************************/
 HI_S32 jpg_osr_close( struct inode *inode, struct file *file)
 {
	 /**
	  **�����������
	  **/
	  s_pstruJpgOsrDev->bDecTask	   = HI_FALSE;
	  s_pstruJpgOsrDev->bSuspendSignal = HI_FALSE;
	  s_pstruJpgOsrDev->bResumeSignal  = HI_FALSE;
	  
	 /**
	  **�ر��豸֮��λ���ر�ʱ�ӣ��ʹ���ʹ��
	  **/
	  jpg_do_reset();
	  jpg_do_clock_off();
 
	  return HI_SUCCESS;
 
 }

#else

 /***************************************************************************************
 * func 		 : jpg_osr_open
 * description	 : open jpeg device
				   CNcomment: ��jpeg�豸 CNend\n
 * param[in]	 : *inode
 * param[in]	 : *file
 * retval		 : HI_SUCCESS
 * retval		 : HI_FAILURE
 * others:		 : NA
 ***************************************************************************************/
 HI_S32 jpg_osr_open(struct inode *inode, struct file *file)
 {	 
 
	 
		 JPG_DISPOSE_CLOSE_S *sDisposeClose = NULL;
		 HI_S32 s32Ret = HI_SUCCESS;
		 
		 sDisposeClose = (JPG_DISPOSE_CLOSE_S *)HI_GFX_KMALLOC(HIGFX_JPGDEC_ID, 		  \
																sizeof(JPG_DISPOSE_CLOSE_S),\
																GFP_KERNEL);
		 if ( HI_NULL == sDisposeClose )
		 {	  
			 return -ENOMEM;
		 }
		 
		 memset(sDisposeClose, 0x0, sizeof(JPG_DISPOSE_CLOSE_S));
		 file->private_data 			= sDisposeClose;
		 sDisposeClose->s32DecClose 	= HI_SUCCESS;
		 sDisposeClose->s32SuspendClose = HI_FAILURE;
		 sDisposeClose->bOpenUp 		= HI_FALSE;
		 sDisposeClose->bSuspendUp		= HI_FALSE;
		 sDisposeClose->bRealse 		= HI_FALSE;
		 
		 s32Ret = wait_event_interruptible_timeout(s_pstruJpgOsrDev->QWaitMutex, 
												   HI_FALSE == s_pstruJpgOsrDev->bLock, 
												   5000 * HZ/1000);/** waite 5s **/
		 if(s32Ret <= 0)
		 {
			 JPEG_TRACE("open dev failure %d\n",__LINE__);
			 up(&s_JpegMutex);
			 s_pstruJpgOsrDev->bLock = HI_FALSE;/** ���ͷ��� **/
			 return HI_FAILURE;
		 }
 
		 return HI_SUCCESS;
	 
 }
 
  /***************************************************************************************
  * func		  : jpg_osr_close
  * description   : close jpeg device
					CNcomment: �ر�jpeg�豸 CNend\n
  * param[in]	  : *inode
  * param[in]	  : *file
  * retval		  : HI_SUCCESS
  * retval		  : HI_FAILURE
  * others: 	  : NA
  ***************************************************************************************/
 HI_S32 jpg_osr_close( struct inode *inode, struct file *file)
 {
		  
 
		 JPG_DISPOSE_CLOSE_S *sDisposeClose = NULL;
 
		 sDisposeClose = file->private_data;
		 if(NULL == sDisposeClose)
		 {	
			return HI_FAILURE;
		 }
 
		 /**
		  **if device has not initial, return failure
		  **/
		 if (HI_NULL == s_pstruJpgOsrDev)
		 {	  
			 up(&s_JpegMutex);
			 wake_up_interruptible(&s_pstruJpgOsrDev->QWaitMutex);/** ���ѣ�����ȳ�ʱ **/
			 return HI_FAILURE;
		 }
 
		 /**
		  **�����������
		  **/
		  s_pstruJpgOsrDev->bDecTask	   = HI_FALSE;
		  s_pstruJpgOsrDev->bSuspendSignal = HI_FALSE;
		  s_pstruJpgOsrDev->bResumeSignal  = HI_FALSE;
		 
		 /** if suspend dispose */
		 /** CNcomment: ����Ǵ����򽫴�����Ҫ���豸�ػص����� */
		 if(HI_SUCCESS==sDisposeClose->s32SuspendClose)
		 {
			  if(HI_TRUE == sDisposeClose->bSuspendUp)
			  {
				 up(&s_JpegMutex);
				 s_pstruJpgOsrDev->bLock = HI_FALSE;/** ���ͷ��� **/
				 wake_up_interruptible(&s_pstruJpgOsrDev->QWaitMutex);/** ���ѣ�����ȳ�ʱ **/
			  }
			  HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID *)sDisposeClose);
			  return HI_SUCCESS;
		 }
 
		 if(HI_SUCCESS==sDisposeClose->s32DecClose)
		 {
			  if(HI_TRUE == sDisposeClose->bOpenUp)
			  {
				 up(&s_JpegMutex);
				 s_pstruJpgOsrDev->bLock = HI_FALSE;/** ���ͷ��� **/
				 wake_up_interruptible(&s_pstruJpgOsrDev->QWaitMutex);/** ���ѣ�����ȳ�ʱ **/
			  }
			  HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID *)sDisposeClose);
			  return HI_SUCCESS;
		 }
 
 
		 /**
		  **  if call realse, should not call this
		  **/
		 if(HI_FALSE == sDisposeClose->bRealse)
		 {
			 /**
			  ** set file private data to HI_NULL 
			  **/
			 HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID *)sDisposeClose);
 
			 /**
			  ** if the file occupy the device, set this device to not occupied,
			  ** wake up waiting halt waiting queue
			  **/
			 if(down_interruptible(&s_pstruJpgOsrDev->SemGetDev))
			 {
			   /*nothing to do!*/
			 }
 
			 if ((HI_TRUE == s_pstruJpgOsrDev->bEngageFlag) && (file == s_pstruJpgOsrDev->pFile))
			 {
			 
				 s_pstruJpgOsrDev->bEngageFlag = HI_FALSE;
				 (HI_VOID)wake_up_interruptible(&s_pstruJpgOsrDev->QWaitInt);				 
			 }
			 /**
			  ** to JPG reset operation, open the clock
			  **/
			 if(s_pstruJpgOsrDev->bEngageFlag != HI_FALSE)
			 {
				 //jpg_do_reset();
				 //jpg_do_clock_off();
				 up(&s_pstruJpgOsrDev->SemGetDev);
				 up(&s_JpegMutex);
				 s_pstruJpgOsrDev->bLock = HI_FALSE;/** ���ͷ��� **/
				 wake_up_interruptible(&s_pstruJpgOsrDev->QWaitMutex);/** ���ѣ�����ȳ�ʱ **/
				 return HI_FAILURE;
			 }
			 if(s_pstruJpgOsrDev->IntType != JPG_INTTYPE_NONE)
			 {
				 jpg_do_reset();
				 jpg_do_clock_off();
				 up(&s_pstruJpgOsrDev->SemGetDev);
				 up(&s_JpegMutex);
				 s_pstruJpgOsrDev->bLock = HI_FALSE;/** ���ͷ��� **/
				 wake_up_interruptible(&s_pstruJpgOsrDev->QWaitMutex);/** ���ѣ�����ȳ�ʱ **/
				 return HI_FAILURE;
			 }
					   
			 jpg_do_reset();
			 jpg_do_clock_off();
#if 0
			 /**
			  **����û�б��ͷŵ����
			  **/
			 static HI_S32 s32MutexCnt = 0;
			 s32MutexCnt++;
			 if(10 == s32MutexCnt)
			 {
				 JPEG_TRACE("=========s32MutexCnt = %d\n",s32MutexCnt);
				 s32MutexCnt = 0;
				 up(&s_pstruJpgOsrDev->SemGetDev);
				 return HI_FAILURE;
			 }
#endif
			 up(&s_JpegMutex);
			 s_pstruJpgOsrDev->bLock = HI_FALSE;/** ���ͷ��� **/
			 wake_up_interruptible(&s_pstruJpgOsrDev->QWaitMutex);/** ���ѣ�����ȳ�ʱ **/
			 
			 up(&s_pstruJpgOsrDev->SemGetDev);
			 
			 return HI_SUCCESS;
			 
			 
		 }
		 jpg_do_reset();
		 jpg_do_clock_off();
		 /**
		  ** set file private data to HI_NULL 
		  **/
		 HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID *)sDisposeClose);
 
		 return HI_SUCCESS;
 
		 
 }
#endif


#ifdef CONFIG_JPEG_OMX_FUNCTION

 /*****************************************************************************
 * func            : jpg_dec_start
 * description     : begin to decode
 * param[in]       : offset
 * param[in]       : value
 * retval          : none
 *****************************************************************************/
 static HI_S32 jpg_dec_start(HI_VOID)
 {

     HI_S32 s32Ret = HI_SUCCESS;
     JPG_GETINTTYPE_S IntInfo = {0};
     jpeg_reg_write(JPGD_REG_RESUME, 0x2);
#ifdef CONFIG_JPEG_4KDDR_DISABLE
     jpeg_reg_write(JPGD_REG_START, 0x5);
#else
     jpeg_reg_write(JPGD_REG_START, 0x1);
#endif

     IntInfo.IntType = JPG_INTTYPE_NONE;
     IntInfo.TimeOut = 10000;/** 10s **/
     s32Ret = jpg_osr_getintstatus((DRV_JPEG_EXT_GETINTTYPE_S*)&IntInfo);
     if(HI_FAILURE == s32Ret)
     {
         return HI_FAILURE;
     }
     if(JPG_INTTYPE_FINISH == IntInfo.IntType)
     {
        //JPEG_TRACE("dec success\n");
        return HI_SUCCESS;
     }
     else if(JPG_INTTYPE_CONTINUE == IntInfo.IntType)
     {
         JPEG_TRACE("dec continue\n");
         return HI_FAILURE;
     }
     else
     {
         JPEG_TRACE("dec failure\n");
         return HI_FAILURE;
     }
     
 }
/*****************************************************************************
 * func            : jpg_dec_continue
 * description     : begin to decode
 * param[in]       : offset
 * param[in]       : value
 * retval          : none
 *****************************************************************************/
 static HI_S32 jpg_dec_continue(HI_S32 s32DecHandle)
 {

     HI_S32 s32Ret = HI_SUCCESS;
     HI_BOOL bStartDec = HI_FALSE;
     HI_BOOL bReachEOF = HI_FALSE;
     HI_S32  s32Offset = 0;
     JPG_GETINTTYPE_S IntInfo = {0};
     IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)s32DecHandle;

     IntInfo.TimeOut = 10000;/** 10s **/
     
     do 
     {
         s32Ret = jpeg_send_stream(s32DecHandle,&s32Offset,&bReachEOF);
         if(HI_SUCCESS != s32Ret)
         {
            return HI_FAILURE;
         }
         /** ����buffer������ַ **/
         jpeg_reg_write(JPGD_REG_ENDADD,(HI_S32)(pstImgInfo->pStreamPhy + s32Offset));
         
         if(HI_FALSE == bStartDec)
	     { 
			jpeg_reg_write(JPGD_REG_RESUME,(bReachEOF ? 0x02 : 0x0));
#ifdef CONFIG_JPEG_4KDDR_DISABLE
			jpeg_reg_write(JPGD_REG_START, 0x5);
#else
			jpeg_reg_write(JPGD_REG_START, 0x1);
#endif
		    bStartDec  = HI_TRUE;
		 }
		 else
		 {
			jpeg_reg_write(JPGD_REG_RESUME,(bReachEOF ? (0x02|0x01) : 0x01));
		 }
            
         IntInfo.IntType = JPG_INTTYPE_NONE;
         s32Ret = jpg_osr_getintstatus((DRV_JPEG_EXT_GETINTTYPE_S*)&IntInfo);
         if(HI_FAILURE == s32Ret)
         {
             return HI_FAILURE;
         }
         if(JPG_INTTYPE_FINISH == IntInfo.IntType)
         {
             break;
         }
         else if(JPG_INTTYPE_CONTINUE == IntInfo.IntType)
         {
             continue;
         }
         else
         {
             JPEG_TRACE("dec failure\n");
             return HI_FAILURE;
         }

      } while(JPG_INTTYPE_FINISH != IntInfo.IntType);

      return HI_SUCCESS;
}

#endif



#ifdef CONFIG_JPEG_MMU_SUPPORT
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
HI_VOID jpg_osr_setmemtype(HI_S32 s32Handle,HI_U32 u32MemMask)
{
	IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)s32Handle;
	pstImgInfo->u32MemTypeMask = u32MemMask;
	return;
}
#endif

 /***************************************************************************************
 * func          : jpg_osr_dec
 * description   : jpeg hard decode
                   CNcomment: jpeg���� CNend\n
 * param[in]     : *stDecInfo
 * retval        : HI_SUCCESS
 * retval        : HI_FAILURE
 * others:       : NA
 ***************************************************************************************/
 HI_S32 jpg_osr_dec(HI_JPEG_DECINFO_S *stDecInfo)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION
    HI_S32 s32Ret = HI_FAILURE;
	#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
		HI_U32 u32RegistLuaPixSum0 = 0;
		HI_U64 u64RegistLuaPixSum1 = 0;
		IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)(stDecInfo->stInMsg.u32DecHandle);
	#endif
	
    if(NULL == stDecInfo)
    {
        JPEG_TRACE("the dec info is null\n");
        return HI_ERR_JPEG_PARA_NULL;
    }
    if(NULL == stDecInfo->stInMsg.pSavePhy)
    {
        JPEG_TRACE("the input ddr is null\n");
        return HI_ERR_JPEG_PARA_NULL;
    }
    if(NULL == stDecInfo->stOutMsg.pOutPhy[0])
    {/** ��֧������ڴ�Ϊ����?ڴ? **/
        JPEG_TRACE("the output ddr is null\n");
        return HI_ERR_JPEG_PARA_NULL;
    }
    
    s32Ret = jpg_dec_setpara(stDecInfo);
    if(HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if(HI_TRUE == stDecInfo->stInMsg.bUserPhyMem)
    {
        s32Ret = jpg_dec_start();
    }
    else
    {
        s32Ret = jpg_dec_continue(stDecInfo->stInMsg.u32DecHandle);
    }
    if(HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

	#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
		/**
		 ** get the lu pixle value
		 ** CNcomment: ��ȡ����ֵ��С,�������֮����Ϣֵ����ֱ�ӻ�ȡ CNend\n
		 **/
		if(HI_TRUE == stDecInfo->stOutMsg.bLuPixSum)
		{
		   	u32RegistLuaPixSum0  = (HI_U32)jpeg_reg_read(JPGD_REG_LPIXSUM0);
			u64RegistLuaPixSum1  = (HI_U64)(jpeg_reg_read(JPGD_REG_LPIXSUM1) & 0xf);
			pstImgInfo->u64LuPixValue = (HI_U64)((u64RegistLuaPixSum1 << 32) | u32RegistLuaPixSum0);
			stDecInfo->stOutMsg.u64LuPixValue = pstImgInfo->u64LuPixValue;
		}
	#endif
    
    return HI_SUCCESS;
#else
    return HI_FAILURE;
#endif

}
/***************************************************************************************
* func			: jpg_osr_getlupixsum
* description	: get lu pix sum
				  CNcomment: ��ȡ����ֵ�� CNend\n
* param[in] 	: s32Handle
* retval		: HI_SUCCESS
* retval		: HI_FAILURE
* others:		: NA
***************************************************************************************/
HI_VOID jpg_osr_getlupixsum(HI_S32 s32Handle,HI_U64* pu64LuPixValue)
{
#ifdef CONFIG_JPEG_OMX_FUNCTION
	IMAG_INFO_S *pstImgInfo = (IMAG_INFO_S*)(s32Handle);
	*pu64LuPixValue = pstImgInfo->u64LuPixValue;
#endif
	return;
}

 /***************************************************************************************
 * func 		 : JpgOsrISR
 * description	 : the halt function
				   CNcomment: �ж���Ӧ���� CNend\n
 * param[in]	 : irq
 * param[in]	 : * devId
 * param[in]	 : * ptrReg
 * retval		 : HI_SUCCESS �ɹ�
 * retval		 : HI_FAILURE ʧ��
 * others:		 : NA
 ***************************************************************************************/
static HI_S32 JpgOsrISR(HI_S32 irq, HI_VOID * devId, struct pt_regs * ptrReg)
{

	HI_U32 IntType = 0;

	/** get and set the halt status  **/
	/** CNcomment:��ȡ��ǰ���ж�״̬ **/
	JpgHalGetIntStatus(&IntType);
	/** get and set the halt status **/
	/** CNcomment:���������ж�״̬  **/
	JpgHalSetIntStatus(IntType);

	if (IntType & 0x1)
	{
	    s_pstruJpgOsrDev->IntType = JPG_INTTYPE_FINISH;	  
	}
	else if (IntType & 0x2)
	{
	    s_pstruJpgOsrDev->IntType = JPG_INTTYPE_ERROR;
	}
	else if (IntType & 0x4)
	{
	    s_pstruJpgOsrDev->IntType = JPG_INTTYPE_CONTINUE;
	}

	/** AI7D02761 wake up the waiting halt **/
	/** CNcomment:�ȴ��жϻ���             **/
	wake_up_interruptible(&s_pstruJpgOsrDev->QWaitInt);

	return IRQ_HANDLED;
        
    
}

/***************************************************************************************
* func			: Jpg_Request_irq
* description	: register the halt function
				  CNcomment: �����жϺ�ע���ж���Ӧ���� CNend\n
* param[in] 	: HI_VOID
* retval		: NA
* others:		: NA
***************************************************************************************/
static HI_VOID Jpg_Request_irq(HI_VOID)
{

	HI_S32 s32Ret = HI_SUCCESS;
	s32Ret = request_irq(JPGD_IRQ_NUM, (irq_handler_t)JpgOsrISR, IRQF_SHARED, JPEGNAME, s_pstruJpgOsrDev);
	if(HI_SUCCESS != s32Ret )
	{   
		HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID *)s_pstruJpgOsrDev);
	    s_pstruJpgOsrDev = HI_NULL;
	}
}
/***************************************************************************************
* func			: Jpg_Free_irq
* description	: free the halt
				  CNcomment: �����ж���Ӧ CNend\n
* param[in] 	: HI_VOID
* retval		: NA
* others:		: NA
***************************************************************************************/
static HI_VOID Jpg_Free_irq(HI_VOID)
{
    free_irq(JPGD_IRQ_NUM, (HI_VOID *)s_pstruJpgOsrDev);
}


/***************************************************************************************
* func			: JpgOsrDeinit
* description	: when remout driver,call this deinit function
				  CNcomment: ж���豸��ʱ��ȥ��ʼ�� CNend\n
* param[in] 	: *pOsrDev
* retval		: NA
* others:		: NA
***************************************************************************************/
static HI_VOID JpgOsrDeinit(JPG_OSRDEV_S *pOsrDev)
{    


	    /** use to initial waitqueue head and mutex */
		/** CNcomment:��ʼ���� */
	    pOsrDev->IntType     = JPG_INTTYPE_NONE;

#ifndef CONFIG_JPEG_USE_KERNEL_SIGNAL
		pOsrDev->bEngageFlag = HI_FALSE;
	    pOsrDev->pFile       = HI_NULL;
		init_waitqueue_head(&pOsrDev->QWaitMutex);
		HI_GFX_INIT_MUTEX(&pOsrDev->SemGetDev);
#endif

	    /** initial the waiting halt waiting queue  */
		/** CNcomment: */
	    init_waitqueue_head(&pOsrDev->QWaitInt);

	    /** initial device occupy operation singnal */
		/** CNcomment: */
	    HI_GFX_INIT_MUTEX(&s_SuspendMutex);

        #ifdef CONFIG_JPEG_PROC_ENABLE
	    JPEG_Proc_Cleanup();
        #endif
		
	    /** unmap the register address and set s_u32JpgRegAddr with zero */
		/** CNcomment: */
	    JpgHalExit();
		
}


 /***************************************************************************************
 * func 		 : JPEG_DRV_ModExit
 * description	 : remount the jpeg driver
				   CNcomment: ж���豸 CNend\n
 * param[in]	 : *pOsrDev
 * retval		 : NA
 * others:		 : NA
 ***************************************************************************************/
HI_VOID JPEG_DRV_ModExit(HI_VOID)
{


	JPG_OSRDEV_S *pDev = s_pstruJpgOsrDev;

#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL
	jpeg_destory_signal(s_pstruJpgOsrDev->s32SignalId);
#endif

	/** unregister the jpeg from sdk   **/
	/** CNcomment: ��jpegģ���SDKȥ�� **/
#ifndef CONFIG_GFX_BVT_SDK
	HI_GFX_MODULE_UnRegister(HIGFX_JPGDEC_ID);
#endif
	/** uninstall the device  **/
	/** CNcomment: ж���豸   **/
	HI_GFX_PM_UnRegister();

	/** free the halt        **/
	/** CNcomment: �ͷ��ж�  **/
	Jpg_Free_irq();

	jpg_do_reset();
	jpg_do_clock_off();

	JpgOsrDeinit(pDev);

	HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID *)pDev);
	s_pstruJpgOsrDev = HI_NULL;

	HI_GFX_REG_UNMAP((HI_VOID*)s_pJpegRegBase);
	s_pJpegRegBase  = NULL;

#ifndef CONFIG_JPEG_USE_SDK_CRG_ENABLE
	HI_GFX_REG_UNMAP((HI_VOID*)s_pJpegCRG);
	s_pJpegCRG      = NULL;
#endif    

	return;

    
}


/***************************************************************************************
* func			: JpgOsrInit
* description	: when insmod the driver call this function
				  CNcomment: �����豸��ʼ�� CNend\n
* param[in] 	: *pOsrDev
* retval		: HI_SUCCESS
* retval		: HI_FAILURE
* others:		: NA
***************************************************************************************/
static HI_VOID JpgOsrInit(JPG_OSRDEV_S *pOsrDev)
{
		
        HI_GFX_INIT_MUTEX(&s_JpegMutex);

        /** request halt  */
		/** CNcomment:   */
         Jpg_Request_irq();
#ifdef CONFIG_JPEG_MMU_SUPPORT
		HI_GFX_RegisterSmmuIrq(JPGD_MMU_IRQ_MMU_NUM, "hi_jpeg_mmu",  JPGD_MMU_REG_BASEADDR);
		HI_GFX_RegisterSmmuIrq(JPGD_MMU_IRQ_SMMU_NUM, "hi_jpeg_smmu", JPGD_MMU_REG_BASEADDR);
#endif

        /** use to initial waitqueue head and mutex */
		/** CNcomment:   */
        pOsrDev->IntType      = JPG_INTTYPE_NONE;

        /** initial the waiting halt waiting queue */
		/** CNcomment:   */
        init_waitqueue_head(&pOsrDev->QWaitInt);
		
        /** initial device occupy operation singnal  */
		/** CNcomment:   */
	    HI_GFX_INIT_MUTEX(&s_SuspendMutex);

#ifndef CONFIG_JPEG_USE_KERNEL_SIGNAL
		pOsrDev->bEngageFlag  = HI_FALSE;
        pOsrDev->pFile        = HI_NULL;
		pOsrDev->bLock        = HI_FALSE;
		init_waitqueue_head(&pOsrDev->QWaitMutex);
		HI_GFX_INIT_MUTEX(&pOsrDev->SemGetDev);
#endif
}
/***************************************************************************************
* func			: JPEG_DRV_K_ModInit
* description	: build into kernel to mce
				  CNcomment: ���뵽�ں��н���MCE���� CNend\n
* param[in] 	: NA
* retval		: HI_SUCCESS
* retval		: HI_FAILURE
* others:		: NA
***************************************************************************************/
HI_S32 JPEG_DRV_K_ModInit(HI_VOID)
{

		HI_S32 Ret = HI_FAILURE;
		HI_U64 u64BaseAddr = JPGD_REG_BASEADDR;
#ifndef CONFIG_JPEG_USE_SDK_CRG_ENABLE
		HI_U64 u64CRGAddr  = JPGD_CRG_REG_PHYADDR;
#endif
        HIGFX_CHIP_TYPE_E enChipType = HIGFX_CHIP_TYPE_BUTT;

        if (HI_NULL != s_pstruJpgOsrDev)
        {   
            return -EBUSY;
        }
		
		 HI_GFX_SYS_GetChipVersion(&enChipType);
		
		 s_pJpegRegBase = (volatile HI_U32*)HI_GFX_REG_MAP(u64BaseAddr, JPGD_REG_LENGTH);

 #ifndef CONFIG_JPEG_USE_SDK_CRG_ENABLE
		 s_pJpegCRG 	= (volatile HI_U32*)HI_GFX_REG_MAP(u64CRGAddr, JPGD_CRG_REG_LENGTH);
 #endif
 
		
        /** malloc and initial the struct that drive needed to s_pstruJpgOsrDev,if malloc failure, return -NOMEM  */
		/** CNcomment:  */
        s_pstruJpgOsrDev = (JPG_OSRDEV_S *)HI_GFX_KMALLOC(HIGFX_JPGDEC_ID,sizeof(JPG_OSRDEV_S),GFP_KERNEL);
        if ( HI_NULL == s_pstruJpgOsrDev )
        {   
            return -ENOMEM;
        }
        memset(s_pstruJpgOsrDev, 0x0, sizeof(JPG_OSRDEV_S));


        JpgHalInit(s_pJpegRegBase);

        jpg_do_reset();
        
       /** call JpgOsrInit to initial OSR modual, if failure should release the
        ** resource and return failure
        **/
        JpgOsrInit(s_pstruJpgOsrDev);

#ifndef CONFIG_GFX_BVT_SDK
		 Ret = HI_GFX_MODULE_Register(HIGFX_JPGDEC_ID, JPEGDEVNAME, &s_JpegExportFuncs);
#endif
		 if(HI_SUCCESS != Ret)
		 {
			 JPEG_DRV_ModExit();
			 return HI_FAILURE;
		 }

#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL
		 Ret = jpeg_create_signal(&s_pstruJpgOsrDev->s32SignalId);
		 if(HI_SUCCESS != Ret)
		 {
			 JPEG_DRV_ModExit();
			 return HI_FAILURE;
		 }
#endif	 
		 return HI_SUCCESS;
		 
}

/***************************************************************************************
* func			: JPEG_DRV_ModInit
* description	: when insmod the driver call this function
				  CNcomment: �����豸��ʼ�� CNend\n
* param[in] 	: NA
* retval		: HI_SUCCESS
* retval		: HI_FAILURE
* others:		: NA
***************************************************************************************/
HI_S32 JPEG_DRV_ModInit(HI_VOID)
{

        HI_S32 Ret = HI_FAILURE;

#ifndef HI_MCE_SUPPORT
		Ret = JPEG_DRV_K_ModInit();
		if (HI_SUCCESS != Ret)
        { 
        	if(NULL != s_pstruJpgOsrDev)
        	{
				HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID *)s_pstruJpgOsrDev);
        	}
			s_pstruJpgOsrDev = HI_NULL;
            return HI_FAILURE;
        }
#endif

        Ret = HI_GFX_PM_Register();
        if (HI_SUCCESS != Ret)
        { 
        	if(NULL != s_pstruJpgOsrDev)
        	{
				HI_GFX_KFREE(HIGFX_JPGDEC_ID, (HI_VOID *)s_pstruJpgOsrDev);
        	}
			s_pstruJpgOsrDev = HI_NULL;
            return HI_FAILURE;
        }

#ifdef CONFIG_JPEG_PROC_ENABLE
		JPEG_Proc_init();
#endif
		/** display the version message  */
		/** CNcomment: ��ʾ�汾��  */
		jpg_osr_showversion(HIGFX_JPGDEC_ID);
    	   
        return HI_SUCCESS;

    
} 
 /*****************************************************************************
* func            : jpg_osr_ioctl
* description     : jpeg device control interface
* param[in]       : inode  
* param[in]       : flip    device file message
* param[in]       : Cmd  
* param[in]       : Arg    
* output          : none
* retval          : HI_SUCCESS
* retval          : HI_ERR_JPG_DEC_BUSY
* retval          : -EINVAL
* retval          : -EAGAIN
* others:	      : nothing
*****************************************************************************/
static long jpg_osr_ioctl(struct file *file, HI_U32 Cmd, unsigned long Arg)
{

    switch(Cmd)
    {
		case CMD_JPG_GETSIGNAL_ID:
		{
			#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL
			if(copy_to_user((HI_VOID *)Arg, (HI_VOID *)&s_pstruJpgOsrDev->s32SignalId, sizeof(int)))
		        { 
                return -EFAULT;  
       	    }
			#endif
			break;
		}
		case CMD_JPG_OPEN_RESET_CLOCK:
		{
			/** open the clock          **/
			/** CNcomment: �򿪹���ʱ�� **/
			jpg_do_clock_on();
			/** select clock frequence  **/
			/** CNcomment: ѡ��ʱ��Ƶ�� **/
			jpg_select_clock_frep();
			
			/** reset register                        **/
			/** CNcomment: ��λ�Ĵ���ʹ֮�ܹ����¹��� **/
			jpg_do_reset();
			/** cancle the reset,now can work   **/
			/** CNcomment: ������λʹ֮�ܹ����� **/
			jpg_do_cancel_reset();
			
			/** trun the halt status  **/
			/** CNcomment:            **/
			JpgHalSetIntMask(0x0);
			
			s_pstruJpgOsrDev->IntType    = JPG_INTTYPE_NONE;
			s_pstruJpgOsrDev->bDecTask   = HI_TRUE; /** ��ʼ�������� **/
			break;
		}
        case CMD_JPG_GETDEVICE:
        {

            JPG_DISPOSE_CLOSE_S *sDisposeClose = NULL;
            sDisposeClose = file->private_data;
			
        	if(down_interruptible(&s_JpegMutex)){
        	      sDisposeClose->bOpenUp = HI_FALSE;
				  return HI_FAILURE;
            }	
            /**
             ** if has not initial device, return failure
             **/
            if (HI_NULL == s_pstruJpgOsrDev)
            {   
                return HI_FAILURE;
            }
            /**
             ** locked the occupied device 
             **/
            if(down_interruptible(&s_pstruJpgOsrDev->SemGetDev))
            {
               /*nothing to do!*/
            }

            s_pstruJpgOsrDev->bEngageFlag = HI_TRUE;
            s_pstruJpgOsrDev->IntType    = JPG_INTTYPE_NONE;
            s_pstruJpgOsrDev->pFile      = file;
            s_pstruJpgOsrDev->bLock      = HI_TRUE;/** �Ѿ�����ס�� **/
			
            sDisposeClose->s32DecClose   = HI_FAILURE;
            sDisposeClose->bOpenUp       = HI_TRUE;
            sDisposeClose->bRealse       = HI_FALSE;

             /** select clock frequence  */
	         /** CNcomment: ѡ��ʱ��Ƶ�� */
	         jpg_select_clock_frep();
	         /** open the clock  */
	         /** CNcomment: �򿪹���ʱ�� */
             jpg_do_clock_on();
             /**
              ** to JPG reset operation, open the clock
              **/
             jpg_do_reset();
	         /** cancle the reset,now can work  */
	         /** CNcomment: ������λʹ֮�ܹ����� */
	         jpg_do_cancel_reset();
             /** trun the halt status  */
	         /** CNcomment:   */
             JpgHalSetIntMask(0x0);
           
			 
             up(&s_pstruJpgOsrDev->SemGetDev);

#ifdef CONFIG_JPEG_MMU_SUPPORT
			 HI_GFX_InitSmmu(JPGD_MMU_REG_BASEADDR);
#endif
             /**
              **��ʼ��������
              **/
			 s_pstruJpgOsrDev->bDecTask = HI_TRUE;
			 
             break;
             
        }
        case CMD_JPG_SUSPEND:
        {    
			 #ifdef CONFIG_JPEG_SUSPEND
            	pm_message_t state = {0};
			 	jpg_osr_suspend(NULL,state);
			 #endif
             break;
        }
        case CMD_JPG_RESUME:
        {    
			 #ifdef CONFIG_JPEG_SUSPEND
             	jpg_osr_resume(NULL);
			 #endif
             break;
        }
        case CMD_JPG_GETINTSTATUS:
        {

			
            JPG_GETINTTYPE_S IntInfo;
            HI_S32 s32Ret = HI_SUCCESS;
            /**
             ** checkt parameter
             **/
            if (0 == Arg)
            {
                return HI_FAILURE;
            }
            /**
             ** copy input parameter
             **/
           if(copy_from_user((HI_VOID *)&IntInfo, (HI_VOID *)Arg, sizeof(JPG_GETINTTYPE_S)))
		   {   
                return -EFAULT;  
           	}
			s32Ret = jpg_osr_getintstatus((DRV_JPEG_EXT_GETINTTYPE_S*)&IntInfo);
			if(HI_FAILURE == s32Ret)
			{
				return HI_FAILURE;
			}
            /** 
             ** get halt status and return
             **/
            if(copy_to_user((HI_VOID *)Arg, (HI_VOID *)&IntInfo,sizeof(JPG_GETINTTYPE_S)))
		    {
                return -EFAULT;  
           	}
            break;
        }
        case CMD_JPG_READPROC:
        {   

             #ifdef CONFIG_JPEG_PROC_ENABLE 
	            HI_BOOL bIsProcOn = HI_FALSE;
				JPEG_Get_Proc_Status(&bIsProcOn);
	            if(HI_TRUE == bIsProcOn)
	            {
		            if (0 == Arg)
		            {
		                return HI_FAILURE;
		            }
		                        
		            if(copy_from_user((HI_VOID *)&s_stJpeg6bProcInfo, (HI_VOID *)Arg, sizeof(HI_JPEG_PROC_INFO_S)))
				    {  
		                return -EFAULT;  
		           	}
	            }
			#endif
			
            break;
			
        }   	
        case CMD_JPG_GETRESUMEVALUE:
        {/** ��ȡ����������Ϣ **/
			#ifdef CONFIG_JPEG_SUSPEND
                HI_JPG_SAVEINFO_S stSaveInfo = {0};
	            if (0 == Arg)
	            {
	                return HI_FAILURE;
	            }
	            JPG_GetResumeValue(&stSaveInfo);
	            if(copy_to_user((HI_VOID *)Arg, (HI_VOID *)&stSaveInfo,sizeof(stSaveInfo)))
			    {
	                return -EFAULT;
	           	}
				s_pstruJpgOsrDev->bSuspendSignal = HI_FALSE;
    			s_pstruJpgOsrDev->bResumeSignal  = HI_FALSE;
			#endif
            break;
			
        }
        case CMD_JPG_GETSUSPEND:
        { /** ��ȡ������Ϣ **/
			
            #ifdef CONFIG_JPEG_SUSPEND
	            if (0 == Arg)
	            {
	                return HI_FAILURE;
	            }
	            if(copy_to_user((HI_VOID *)Arg, (HI_VOID *)&s_pstruJpgOsrDev->bSuspendSignal,sizeof(s_pstruJpgOsrDev->bSuspendSignal)))
			    {  
	                return -EFAULT;
	           	}
			#endif
            break;
			
        }
        case CMD_JPG_GETRESUME:
        {/** ��ȡ����������Ϣ **/  
			#ifdef CONFIG_JPEG_SUSPEND
	            if (0 == Arg)
	            {
	                return HI_FAILURE;
	            }
	                        
	            if(copy_to_user((HI_VOID *)Arg, (HI_VOID *)&s_pstruJpgOsrDev->bResumeSignal,sizeof(s_pstruJpgOsrDev->bResumeSignal)))
			    {
	                return -EFAULT;
	           	}
			#endif
            break;
			
        }
        case CMD_JPG_CANCEL_RESET:
		{
             jpg_do_cancel_reset();
			 break;
        }
        case CMD_JPG_RESET:
		{
             jpg_do_reset();
			 break;
        }
#ifdef CONFIG_JPEG_OMX_FUNCTION
        case CMD_JPG_CREATEDEC:
        {
             HI_U32 u32DecHandle = 0;
             u32DecHandle = (HI_U32)HI_GFX_KMALLOC(HIGFX_JPGDEC_ID,sizeof(IMAG_INFO_S),GFP_KERNEL);
             if(0 == u32DecHandle )
             {
                return HI_FAILURE;
             }
             memset((HI_VOID*)u32DecHandle,0,sizeof(IMAG_INFO_S));
             if(copy_to_user((HI_VOID *)Arg, (HI_VOID *)&u32DecHandle,sizeof(HI_S32)))
		     {
                return -EFAULT;
           	 }
             break;
        }
        case CMD_JPG_SETMEMTYPE:
        {
        #ifdef CONFIG_JPEG_MMU_SUPPORT
             HI_DRV_JPEG_INMSG_S stInMsg;
             if (0 == Arg)
                return HI_FAILURE;
             
             memset(&stInMsg,0,sizeof(HI_DRV_JPEG_INMSG_S));
             if(copy_from_user((HI_VOID *)&stInMsg, (HI_VOID *)Arg, sizeof(HI_DRV_JPEG_INMSG_S))){
                return -EFAULT;
           	 }
             if(0 == stInMsg.u32DecHandle){
                JPEG_TRACE("the dec handle has been destoryed\n");
                return HI_FAILURE;
             }
             jpg_osr_setmemtype(stInMsg.u32DecHandle,stInMsg.u32MemMask);
        #endif
             break;
        }
        case CMD_JPG_DECINFO:
        {
             HI_S32 s32Ret = HI_SUCCESS;
             HI_DRV_JPEG_INMSG_S stInMsg;
             if (0 == Arg)
                return HI_FAILURE;

             memset(&stInMsg,0,sizeof(HI_DRV_JPEG_INMSG_S));
             if(copy_from_user((HI_VOID *)&stInMsg, (HI_VOID *)Arg, sizeof(HI_DRV_JPEG_INMSG_S)))
		     {
                return -EFAULT;
           	 }
             if(0 == stInMsg.u32DecHandle)
             {
                JPEG_TRACE("the dec handle has been destoryed\n");
                return HI_FAILURE;
             }
             s32Ret = jpg_dec_parse(&stInMsg);
             if(HI_SUCCESS != s32Ret)
             {
                JPEG_TRACE("jpg_dec_parse failure s32Ret = 0x%x\n",s32Ret);
                return HI_FAILURE;
             }
             jpeg_get_imginfo(&stInMsg);

             if(copy_to_user((HI_VOID *)Arg, (HI_VOID *)&stInMsg,sizeof(HI_DRV_JPEG_INMSG_S)))
		     {
                return -EFAULT;
           	 }
             
             break;
        }
        case CMD_JPG_DECOUTINFO:
        {
             HI_S32 s32Ret = HI_SUCCESS;
             HI_DRV_JPEG_OUTMSG_S stOutMsg;
             if (0 == Arg)
                return HI_FAILURE;

             memset(&stOutMsg,0,sizeof(HI_DRV_JPEG_OUTMSG_S));
             if(copy_from_user((HI_VOID *)&stOutMsg, (HI_VOID *)Arg, sizeof(HI_DRV_JPEG_OUTMSG_S)))
		     {
                return -EFAULT;
           	 }
             if(0 == stOutMsg.u32DecHandle)
             {
                JPEG_TRACE("the dec handle has been destoryed\n");
                return HI_FAILURE;
             }
             
             s32Ret = jpeg_get_sofn(&stOutMsg);
             if(HI_SUCCESS != s32Ret)
             {
                JPEG_TRACE("jpeg_get_sofn failure\n");
                return HI_FAILURE;
             }

             if(copy_to_user((HI_VOID *)Arg, (HI_VOID *)&stOutMsg,sizeof(HI_DRV_JPEG_OUTMSG_S)))
		     {
                return -EFAULT;
           	 }
             break;
        }
        case CMD_JPG_DECODE:
        {
             HI_S32 s32Ret = HI_SUCCESS;
             HI_JPEG_DECINFO_S stDecInfo;
             JPG_DISPOSE_CLOSE_S *sDisposeClose = NULL;
             sDisposeClose = file->private_data;
             
             if (0 == Arg)
                return HI_FAILURE;
             
             memset(&stDecInfo,0,sizeof(HI_JPEG_DECINFO_S));
             if(copy_from_user((HI_VOID *)&stDecInfo, (HI_VOID *)Arg, sizeof(HI_JPEG_DECINFO_S)))
		     {
                return -EFAULT;
           	 }
             if(0 == stDecInfo.stOutMsg.u32DecHandle || 0 == stDecInfo.stInMsg.u32DecHandle)
             {
                JPEG_TRACE("the dec handle has been destoryed\n");
                return HI_FAILURE;
             }
             
             if(down_interruptible(&s_JpegMutex))
             {
				return HI_FAILURE;
             }
             
             s_pstruJpgOsrDev->bEngageFlag = HI_TRUE;
             s_pstruJpgOsrDev->IntType     = JPG_INTTYPE_NONE;
             s_pstruJpgOsrDev->pFile       = file;
             sDisposeClose->s32DecClose    = HI_FAILURE;
             sDisposeClose->bOpenUp        = HI_TRUE;
             sDisposeClose->bRealse        = HI_TRUE;
            
             /** set clock and reset **/
	         jpg_select_clock_frep();
             jpg_do_clock_on();
             jpg_do_reset();
	         jpg_do_cancel_reset();
             JpgHalSetIntMask(0x0);
             
             s32Ret = jpg_osr_dec(&stDecInfo);
             if(HI_SUCCESS != s32Ret)
             {
                JPEG_TRACE("jpg_osr_dec failure s32Ret = 0x%x\n",s32Ret);
                up(&s_JpegMutex);
                wake_up_interruptible(&s_pstruJpgOsrDev->QWaitMutex);
                return HI_FAILURE;
             }
             
             up(&s_JpegMutex);
             wake_up_interruptible(&s_pstruJpgOsrDev->QWaitMutex);
             
             break;
             
        }
        case CMD_JPG_GETLUPIXSUM:
        {
			 HI_U64 u64LuPixValue = 0;
             HI_DRV_JPEG_OUTMSG_S stOutMsg;
             if (0 == Arg)
                return HI_FAILURE;

             memset(&stOutMsg,0,sizeof(HI_DRV_JPEG_OUTMSG_S));
             if(copy_from_user((HI_VOID *)&stOutMsg, (HI_VOID *)Arg, sizeof(HI_DRV_JPEG_OUTMSG_S)))
		     {
                return -EFAULT;
           	 }

             if(0 == stOutMsg.u32DecHandle)
             {
                JPEG_TRACE("the dec handle has been destoryed\n");
                return HI_FAILURE;
             }

             jpg_osr_getlupixsum(stOutMsg.u32DecHandle,&u64LuPixValue);

             stOutMsg.u64LuPixValue = u64LuPixValue;
             
             if(copy_to_user((HI_VOID *)Arg, (HI_VOID *)&stOutMsg,sizeof(HI_DRV_JPEG_OUTMSG_S)))
		     {
                return -EFAULT;
           	 }
             break;
        }
        case CMD_JPG_DESTORYDEC:
        {
            HI_S32 s32Handle = 0;
            if (0 == Arg)
            {
                return HI_FAILURE;
            }
            if(copy_from_user((HI_VOID *)&s32Handle, (HI_VOID *)Arg, sizeof(HI_S32)))
		    {
                return -EFAULT;
           	}
            
            jpeg_mem_destory(s32Handle);
            
            break;
        }
#endif
        default:
        {
            return -EINVAL;
        }
        
    }
	
    return HI_SUCCESS;


}



/** ����������Ҫ�������� **/
#ifdef MODULE
/** 
 ** this two function is defined at msp/drv/include/drv_jpeg_ext.h
 **/
module_init(JPEG_DRV_ModInit);
module_exit(JPEG_DRV_ModExit);
#endif


EXPORT_SYMBOL(JPEG_DRV_K_ModInit);


#ifndef HI_ADVCA_FUNCTION_RELEASE
MODULE_DESCRIPTION("driver for the all jpeg");
MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");
#else
MODULE_DESCRIPTION("");
MODULE_AUTHOR("");
MODULE_LICENSE("GPL");
#endif
