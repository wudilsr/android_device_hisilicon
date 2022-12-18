/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : jpeg_hdec_api.c
Version		    : Initial Draft
Author		    : y00181162
Created		    : 2014/06/20
Description	    : the jpeg hard decode realize in this function
                  CNcomment: jpeg硬件解码的实现在该函数中,多进程是相互独立的，两个没有
                  			 相关的应用程序 CNend\n
Function List 	:

			  		  
History       	:
Date				Author        		Modification
2014/06/20		    y00181162		    Created file      	
******************************************************************************/

/*********************************add include here******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <assert.h>
#include <unistd.h>


#include "jpeglib.h"
#include "jdatasrc.h"
#include "jerror.h"

#include "hi_jpeg_config.h"
#include "jpeg_hdec_api.h"
#include "jpeg_hdec_error.h"
#include "jpeg_hdec_mem.h"
#include "jpeg_hdec_rwreg.h"
#include "jpeg_hdec_adp.h"
#include "jpeg_hdec_csc.h"
#include "hi_jpeg_drv_api.h"
#include "hi_jpeg_reg.h"

#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL
#include "jpeg_hdec_signal.h"
#endif

#ifdef CONFIG_JPEG_PROC_ENABLE
#include "jpegint.h"
#endif


#if    defined(CONFIG_JPEG_TEST_SAVE_BMP_PIC)     \
	|| defined(CONFIG_JPEG_TEST_SAVE_YUVSP_DATA)  \
	|| defined(CONFIG_JPEG_TEST_CHIP_RANDOM_RESET)\
	|| defined(CONFIG_JPEG_FPGA_TEST_CONTINUE_STREAM_DDR_CHANGE)
#include "hi_jpeg_hdec_test.h"
#endif

#if defined(CONFIG_JPEG_ANDROID_DEBUG_ENABLE) && defined(CONFIG_JPEG_DEBUG_INFO)
#include <cutils/properties.h>
#define LOG_TAG "libjpeg"
#endif


#define ANDROID_BROWER_FUNCTION

/***************************** Macro Definition ******************************/

/** the jpeg structure init pointer */
/** CNcomment:jpeg私有机构体初始化指针 */
#define CLIENT_DATA_MARK				  0x00FFFFFF

/** the hard dec inflexion size */
/** CNcomment:软件和硬件解码的拐点大小 */
#define JPGD_HDEC_FLEXION_SIZE		  0 //100000000

#if 0
#define MEMINFO_FILE                     "/proc/meminfo"
#else
#define MEMINFO_FILE                     ""
#endif

#define MEMLEAVESIZE_DEFAULT            0x20000000     /** 512M **/

/*************************** Structure Definition ****************************/

typedef struct tabJPEGLEAVEMEMINFO
{
  const HI_CHAR *pName;          /**< memory type name      *//**<CNcomment:内存信息名字 */
  HI_U64 *pSize;                 /**< slot in return struct *//**<CNcomment:不缩放   */
}JPEG_LEAVE_MEMINFO;



#ifndef CONFIG_JPEG_CSC_DISABLE
/** Structure of the some function should realize before main function */
/** CNcomment:一些必须在main函数之前实现的功能变量 */
typedef struct tagJPEG_DECOMPRESS_RES 
{
	HI_S32     s32CscDev;         /**< the csc device             *//**<CNcomment:打开csc设备        */
    HI_CHAR*   pStreamPhyBuf;     /**< The stream physics address *//**<CNcomment:码流buffer物理地址 */
    HI_CHAR*   pStreamVirBuf;     /**< The stream virtual address *//**<CNcomment:码流buffer虚拟地址 */
}JPEG_DECOMPRESS_RES;

static JPEG_DECOMPRESS_RES gs_stJpegDecompressRes = {-1, NULL, NULL};
#endif

/********************** Global Variable declaration **************************/

#ifdef CONFIG_JPEG_FPGA_TEST_ENABLE
/**如果是使用FPGA测试，则分配的内存方式是自己封装的，以及其它实现方式也不一样**/
HI_S32 sg_s32MMZDev = -1;
#endif

/******************************* API forward declarations *******************/


/******************************* API realization *****************************/


/***************************************************************************************
* func			: __attribute__ ((constructor))
* description	: this function will realize before main function, so some function will
                  realize in this function.
                  CNcomment: 应用程序起来之后，也就是第一次调用libjpeg库的时候会先调用
                             该函数，然后再调用main函数，直到退出jpeg应用程序 CNend\n
* param[in] 	: NA
* retval		: HI_SUCCESS 成功
* retval		: HI_FAILURE 失败
* others:		: NA
***************************************************************************************/
void __attribute__ ((constructor)) jpeg_lib_creat(void)
{
		/**
		 ** when malloc mem failure at soft decode, pthread will be killed, so
		 ** we want to use MMZ malloc. we should open at creat decompress
		 ** CNcomment: 要是使用malloc分配的内存，在软件解码过程中要是内存不足
		 **            会导致系统直接挂死，所以要使用mmz来分配内存 CNend\n
		 **/
#if 0
		 JPEG_TRACE("\n==========================================================\n");
		 JPEG_TRACE("==== create process_id = %u,pthread_id = %u\n",(unsigned int)getpid(), (unsigned int)syscall(SYS_gettid));
		 JPEG_TRACE("==========================================================\n");
#endif

#ifdef CONFIG_JPEG_FPGA_TEST_ENABLE
		/** only the fpga test used **/
		MMZ_INIT(MMZ_DEV);
#endif

}


/***************************************************************************************
* func			: __attribute__ ((destructor))
* description	: when exit the program, will call this function
                  CNcomment: 当退出可执行程序的时候会调用该函数 CNend\n
* param[in] 	: NA
* retval		: HI_SUCCESS   CNcomment: 成功  CNend\n
* retval		: HI_FAILURE   CNcomment: 失败  CNend\n
* others:		: NA
***************************************************************************************/
void __attribute__ ((destructor)) jpeg_lib_destroy(void)
{
		  /**
		   ** close tde device
		   ** CNcomment:关闭TDE设备  CNend\n
		   **/
#ifndef CONFIG_JPEG_CSC_DISABLE
          if(gs_stJpegDecompressRes.s32CscDev >= 0) {
             JPEG_HDEC_CSC_Close(gs_stJpegDecompressRes.s32CscDev);
          }
          gs_stJpegDecompressRes.s32CscDev = -1;
#endif

#ifdef CONFIG_JPEG_FPGA_TEST_ENABLE
		  MMZ_DINIT();
#endif

#if 0
		 JPEG_TRACE("\n==========================================================\n");
		 JPEG_TRACE("==== destory process_id = %u,pthread_id = %u\n",(unsigned int)getpid(), (unsigned int)syscall(SYS_gettid));
		 JPEG_TRACE("==========================================================\n");
#endif

}


/*****************************************************************************
* func			: JPEG_HDEC_OpenDev
* description	: open some device that decode need
				  CNcomment: 打开解码需要的相关设备 	   CNend\n
* param[in] 	: cinfo 		CNcomment: 解码对象    CNend\n
* retval		: HI_SUCCESS	CNcomment: 成功 	   CNend\n
* retval		: HI_FAILURE	CNcomment: 失败 	   CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_OpenDev(const struct jpeg_decompress_struct *cinfo)
{

		HI_S32 s32Ret = HI_SUCCESS;
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
				
		if(pJpegHandle->s32JpegDev < 0){
			pJpegHandle->s32JpegDev = open(JPG_DEV, O_RDWR | O_SYNC);
			if(pJpegHandle->s32JpegDev < 0){
				return HI_FAILURE; 
			}
		}

#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL
		/**
		 **lock hard register
		 **/
		s32Ret = JPEG_HDEC_LockSignal(pJpegHandle->s32JpegDev,&pJpegHandle->s32SignalId);
		if(HI_SUCCESS != s32Ret){
			close(pJpegHandle->s32JpegDev);
			return HI_FAILURE;
		}
		s32Ret = ioctl(pJpegHandle->s32JpegDev, CMD_JPG_OPEN_RESET_CLOCK);
		if (HI_SUCCESS != s32Ret){
			JPEG_HDEC_UnLockSignal(pJpegHandle->s32JpegDev);
			close(pJpegHandle->s32JpegDev);
			return HI_FAILURE;
		}
#else
		/**
		** get jpeg device, this has signal
		** CNcomment: 获取硬件设备，这里有信号量锁，使之支持多任务 CNend\n
		**/
		s32Ret = ioctl(pJpegHandle->s32JpegDev, CMD_JPG_GETDEVICE);
		if (HI_SUCCESS != s32Ret){
			close(pJpegHandle->s32JpegDev);
			return HI_FAILURE;
		}
#endif
		/**
		** mmap the device virtual
		** CNcomment: 映射jpeg设备虚拟地址 CNend\n
		**/
		pJpegHandle->pJpegRegVirAddr  = (volatile char*  )mmap(NULL, \
															 JPGD_REG_LENGTH, 	       \
															 PROT_READ | PROT_WRITE,   \
															 MAP_SHARED,			   \
															 pJpegHandle->s32JpegDev,  \
															 (off_t)0);
		if(MAP_FAILED == pJpegHandle->pJpegRegVirAddr){
			return HI_FAILURE; 
		}

#ifdef CONFIG_JPEG_TEST_CHIP_RANDOM_RESET
		HI_JPEG_SetJpegDev(pJpegHandle->s32JpegDev);
		HI_JPEG_SetJpegVir(pJpegHandle->pJpegRegVirAddr);
#endif

		/**
		 ** open tde device
		 ** CNcomment: 打开TDE设备  CNend\n
		 **/
#ifndef CONFIG_JPEG_CSC_DISABLE
		if(gs_stJpegDecompressRes.s32CscDev < 0){
			gs_stJpegDecompressRes.s32CscDev = JPEG_HDEC_CSC_Open();
		}
	    if(gs_stJpegDecompressRes.s32CscDev < 0){
			return HI_FAILURE;
	    }
#endif

		return HI_SUCCESS;


}

#ifdef CONFIG_JPEG_PROC_ENABLE

/*****************************************************************************
* func			: JPEG_HDEC_SetProcInfo
* description	: set the proc information
				  CNcomment: 设置proc信息		  CNend\n
* param[in] 	: cinfo 	  CNcomment: 解码对象 CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功	  CNend\n
* retval		: HI_FAILURE  CNcomment: 失败	  CNend\n
* others:		: NA
*****************************************************************************/
static HI_S32 JPEG_HDEC_SetProcInfo(const struct jpeg_decompress_struct *cinfo)
{

     HI_S32 s32Ret = HI_SUCCESS;
     HI_JPEG_PROC_INFO_S stProcInfo;

	 const HI_U32 u32InFmt[10]  = {0,1,2,3,4,5,6,7,8,9};
	 const HI_U32 u32OutFmt[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	 
     JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

     if(NULL == pJpegHandle->pJpegRegVirAddr){
        return HI_FAILURE;
     }
     stProcInfo.u32YWidth        = pJpegHandle->stJpegSofInfo.u32YWidth;
	 stProcInfo.u32YHeight       = pJpegHandle->stJpegSofInfo.u32YHeight;
	 stProcInfo.u32YSize         = pJpegHandle->stJpegSofInfo.u32YSize;
	 stProcInfo.u32CWidth        = pJpegHandle->stJpegSofInfo.u32CWidth;
	 stProcInfo.u32CHeight       = pJpegHandle->stJpegSofInfo.u32CHeight;
	 stProcInfo.u32CSize         = pJpegHandle->stJpegSofInfo.u32CSize;
	 stProcInfo.u32YStride       = pJpegHandle->stJpegSofInfo.u32YStride;
	 stProcInfo.u32CbCrStride    = pJpegHandle->stJpegSofInfo.u32CbCrStride;
	 stProcInfo.u32DisplayW      = pJpegHandle->stJpegSofInfo.u32DisplayW;
	 stProcInfo.u32DisplayH      = pJpegHandle->stJpegSofInfo.u32DisplayH;
	 stProcInfo.u32DisplayStride = pJpegHandle->stJpegSofInfo.u32DisplayStride;
	 stProcInfo.u32DecW          = pJpegHandle->stJpegSofInfo.u32DecW;
	 stProcInfo.u32DecH          = pJpegHandle->stJpegSofInfo.u32DecH;
	 stProcInfo.u32DecStride     = pJpegHandle->stJpegSofInfo.u32DecStride;
	 stProcInfo.u32DataStartAddr = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADDR);
	 stProcInfo.u32DataEndAddr   = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADDR);
	 stProcInfo.u32SaveStartAddr = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_STADD);
	 stProcInfo.u32SaveEndAddr   = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_ENDADD);


	 stProcInfo.u32InWidth       = cinfo->image_width;
	 stProcInfo.u32InHeight      = cinfo->image_height;
	 stProcInfo.u32OutWidth      = cinfo->output_width;
	 stProcInfo.u32OutHeight     = cinfo->output_height;
	 stProcInfo.u32OutStride     = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0];
     stProcInfo.u32InFmt         = u32InFmt[pJpegHandle->enImageFmt];
	 stProcInfo.u32OutFmt        = u32OutFmt[cinfo->out_color_space];
	 stProcInfo.u32OutPhyBuf     = (unsigned long)pJpegHandle->stOutDesc.stOutSurface.pOutPhy[0];
	 if(0 == pJpegHandle->u32ScalRation){
	     stProcInfo.u32Scale     = 1;
	 }else if(1 == pJpegHandle->u32ScalRation){
	     stProcInfo.u32Scale     = 2;
	 }else if(2 == pJpegHandle->u32ScalRation){
	     stProcInfo.u32Scale     = 4;
	 }else{
	      stProcInfo.u32Scale     = 8;
	 }

	 if(DSTATE_START == cinfo->global_state){
	 	/**
		 **create decompress
		 **/
	     pJpegHandle->eDecState = JPEG_DEC_FINISH_CREATE_DECOMPRESS;
	 }else if(DSTATE_INHEADER == cinfo->global_state){ 
	    /**
		 **read header ready
		 **/
	     pJpegHandle->eDecState = JPEG_DEC_FINISH_READ_HEADER;
	 }else if(DSTATE_SCANNING == cinfo->global_state){  
	    /**
		 **start decompress ready
		 **/
	     pJpegHandle->eDecState = JPEG_DEC_FINISH_START_DECOMPRESS;
	 }else if(DSTATE_SCANNING == cinfo->global_state){  
	    /**
		 **read scanlines ready
		 **/
	     pJpegHandle->eDecState = JPEG_DEC_FINISH_READ_SCANLINES;
	 }else if(DSTATE_STOPPING == cinfo->global_state){
	    /**
		 **finish decompress
		 **/
	     pJpegHandle->eDecState = JPEG_DEC_FINISH_FINISH_DECOMPRESS;
	 }else if(0 == cinfo->global_state){  
	    /**
		 **destory decompress
		 **/
	     pJpegHandle->eDecState = JPEG_DEC_FINISH_DESTORY_DECOMPRESS;
	 }
	 
	 stProcInfo.eDecState        = pJpegHandle->eDecState;
	 
	 if(HI_TRUE == pJpegHandle->bHdecEnd){
	    stProcInfo.eDecodeType      = JPEG_DEC_HW;
	 }else{
	    stProcInfo.eDecodeType      = JPEG_DEC_SW;
	 }
	 
	 s32Ret = ioctl(pJpegHandle->s32JpegDev, CMD_JPG_READPROC, &stProcInfo);
     if(HI_SUCCESS != s32Ret){
        return HI_FAILURE;
     }
     return HI_SUCCESS;
	 
}
#endif


/*****************************************************************************
* func			: JPEG_HDEC_CloseDev
* description	: closxe some device that decode need
				  CNcomment: 关闭解码打开的相关设备 	   CNend\n
* param[in] 	: cinfo 		CNcomment: 解码对象    CNend\n
* retval		: HI_SUCCESS	CNcomment: 成功 	   CNend\n
* retval		: HI_FAILURE	CNcomment: 失败 	   CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_CloseDev(const struct jpeg_common_struct *cinfo)
{

		HI_S32 s32Ret = HI_SUCCESS;
#ifdef CONFIG_JPEG_4KDDR_DISABLE_SHOWMSG
		HI_U32 u32AXI4KCNT   = 0;
		HI_U32 u32AXI16MCNT  = 0;
		HI_U32 u32ReadAXI4KCNT   = 0;
		HI_U32 u32WriteAXI4KCNT  = 0;
		HI_U32 u32ReadAXI16MCNT  = 0;
		HI_U32 u32WriteAXI16MCNT = 0;
#endif
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

#ifdef CONFIG_JPEG_PROC_ENABLE
		s32Ret = JPEG_HDEC_SetProcInfo((j_decompress_ptr)cinfo); /*lint !e740 !e826 ignore by y00181162, because this cast is ok */  
#endif

#ifdef CONFIG_JPEG_TEST_CHIP_RANDOM_RESET
		HI_JPEG_RandomResetInit();
#endif

#ifdef CONFIG_JPEG_4KDDR_DISABLE_SHOWMSG
		if (NULL != pJpegHandle->pJpegRegVirAddr){
			u32AXI4KCNT  = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_AXI4KCNT);
			u32AXI16MCNT = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_AXI16MCNT);
		}
		u32ReadAXI4KCNT   = u32AXI4KCNT & 0xffff0000;
		u32WriteAXI4KCNT  = u32AXI4KCNT & 0x0000ffff;
		u32ReadAXI16MCNT  = u32AXI16MCNT & 0xffff0000;
		u32WriteAXI16MCNT = u32AXI16MCNT & 0x0000ffff;
		if(0 != u32AXI4KCNT || 0 != u32AXI16MCNT || 0 != u32ReadAXI4KCNT || 0 != u32WriteAXI4KCNT || 0 != u32ReadAXI16MCNT || 0 != u32WriteAXI16MCNT){
			JPEG_TRACE("\n=====================================================\n");
			JPEG_TRACE("跨4K次数  = %d\n", u32AXI4KCNT);
			JPEG_TRACE("跨16M次数 = %d\n", u32AXI16MCNT);
			JPEG_TRACE("读地址跨4K次数 = %d\n", u32ReadAXI4KCNT);
			JPEG_TRACE("写地址跨4K次数 = %d\n", u32WriteAXI4KCNT);
			JPEG_TRACE("读地址跨16M次数 = %d\n",u32ReadAXI16MCNT);
			JPEG_TRACE("写地址跨16M次数 = %d\n",u32WriteAXI16MCNT);
			JPEG_TRACE("=====================================================\n");
			sleep(2);
		}
		#ifdef CONFIG_JPEG_4KDDR_DISABLE
		if(0 != u32AXI4KCNT || 0 != u32AXI16MCNT){
			JPEG_TRACE("\n=====================================================\n");
			JPEG_TRACE("跨4K开关关掉异常,逻辑有问题\n");
			JPEG_TRACE("按回车键结束\n");
			JPEG_TRACE("=====================================================\n");
			getchar();
		}
		#endif
#endif

		if (NULL != pJpegHandle->pJpegRegVirAddr){
			  s32Ret = munmap((void*)pJpegHandle->pJpegRegVirAddr, JPGD_REG_LENGTH);
			  pJpegHandle->pJpegRegVirAddr = NULL;
		}

		/**
		 **close jpeg device
		 **/
		if(pJpegHandle->s32JpegDev < 0){
		    return HI_SUCCESS;
		}
		
		close(pJpegHandle->s32JpegDev);
		pJpegHandle->s32JpegDev = -1;

#ifdef CONFIG_JPEG_USE_KERNEL_SIGNAL
		/**
		 **unlock hard register
		 **/
		JPEG_HDEC_UnLockSignal(pJpegHandle->s32SignalId);
#endif

		if(HI_SUCCESS != s32Ret){
		    return HI_FAILURE;
		}

		return HI_SUCCESS;
		

}

/*****************************************************************************
* func			: JPEG_HDEC_Init
* description	: init the private structure para
                  CNcomment: 初始化私有结构体变量   CNend\n
* param[in] 	: cinfo       CNcomment: 解码对象   CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功  CNend\n
* retval		: HI_FAILURE  CNcomment: 失败  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_Init(j_common_ptr cinfo)
{

#ifdef CONFIG_JPEG_GETDECTIME
		HI_S32 s32Ret  = HI_SUCCESS;
#endif

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = NULL;

		pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)calloc(1, SIZEOF(JPEG_HDEC_HANDLE_S));
		JPEG_ASSERT((NULL == pJpegHandle), JPEG_ERR_NOMEM);

		/**
		** if use external stream,when dec failure, call start decompress
		** again,do not need call hard decode again
		** CNcomment: 如果使用外部码流，当解码失败的时候会第二次调用解码
		**            就不需要再走硬件了CNend\n
		**/
		pJpegHandle->bFirstDec          =  HI_TRUE;

		/** default the jpeg hard decode is 4bytes align, but tde is need 16bytes align**/
		pJpegHandle->u32StrideAlign     = JPGD_HDEC_MMZ_CSCOUT_STRIDE_ALIGN;

#ifdef CONFIG_JPEG_GETDECTIME
		s32Ret  = HI_GFX_GetTimeStamp(&pJpegHandle->u32CurTime,NULL);
		if(HI_SUCCESS != s32Ret){
			free(pJpegHandle);
			return HI_FAILURE;
		}
#endif

#ifdef CONFIG_JPEG_MMU_SUPPORT
		/** default all is mmz memory **/
		pJpegHandle->u32MemTypeMask     = 0X0;
#endif
		pJpegHandle->s32ClientData      =  CLIENT_DATA_MARK;
		pJpegHandle->s32JpegDev         = -1;
		pJpegHandle->u32Inflexion       =  JPGD_HDEC_FLEXION_SIZE;
		pJpegHandle->u32Alpha           =  0xFF;

#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pJpegHandle->s32MMZDev			=  -1;
#endif

#ifdef CONFIG_JPEG_PROC_ENABLE
		pJpegHandle->eDecState          =  JPEG_DEC_STATE_BUTT;
#endif

		/**
		** the jpeg format
		** CNcomment: 原始jpeg图片格式 CNend\n
		**/
		pJpegHandle->enImageFmt   =  JPEG_FMT_BUTT;

		/**
		** save the jpeg handle pointer
		** CNcomment: 存储jpeg句柄指针 CNend\n
		**/
		cinfo->client_data = (void *)pJpegHandle;


		return HI_SUCCESS;


}

/*****************************************************************************
* func			: JPEG_HDEC_ReleaseRes
* description	: release the resouce
				  CNcomment:  释放资源       CNend\n
* param[in] 	: cinfo 	  CNcomment: 解码对象	CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功  CNend\n
* retval		: HI_FAILURE  CNcomment: 失败  CNend\n
* others:		: NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_ReleaseRes(const struct jpeg_common_struct *cinfo)
{

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
		/**
		** get the stream mem
		** CNcomment: 获取硬件解码的码流buffer CNend\n
		**/	 
		JPEG_HDEC_FreeStreamMem(pJpegHandle);

		JPEG_HDEC_FreeYUVMem(pJpegHandle);

#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bDecARGB){
			JPEG_HDEC_FreeMinMem(pJpegHandle);
		}
#endif

		JPEG_HDEC_FreeOutMem(pJpegHandle);

#if 0
		if(NULL != pJpegHandle->stJpegHtoSInfo.pLeaveBuf)
		{
			free(pJpegHandle->stJpegHtoSInfo.pLeaveBuf);
			pJpegHandle->stJpegHtoSInfo.pLeaveBuf = NULL;
		}
#endif

#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		if(pJpegHandle->s32MMZDev >= 0){
			gfx_mem_close(pJpegHandle->s32MMZDev);
			pJpegHandle->s32MMZDev = -1;
		}
#endif

}

/*****************************************************************************
* func			: JPEG_HDEC_Destroy
* description	: dinit the private structure para
				  CNcomment:  销毁硬件解码器        CNend\n
* param[in] 	: cinfo 	  CNcomment: 解码对象	CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功  CNend\n
* retval		: HI_FAILURE  CNcomment: 失败  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_Destroy(const struct jpeg_common_struct *cinfo)
{


		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
		if (NULL == pJpegHandle){
			return HI_SUCCESS;
		}
		/**
		 ** if memory leak, take out this check
		 ** CNcomment: 要是有内存释放问题，去掉该判断 CNend\n
		 **/
		if(HI_FALSE == pJpegHandle->bReleaseRes){
			JPEG_HDEC_ReleaseRes(cinfo);
		}

		free(pJpegHandle);
		pJpegHandle = NULL;

		return HI_SUCCESS;
		 
}
/*****************************************************************************
* func			: JPEG_HDEC_Abort
* description	: when want use the decompress again,call this
				  CNcomment:  如果想继续使用解码器，调用该接口 CNend\n
* param[in] 	: cinfo 	  CNcomment: 解码对象	           CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功  CNend\n
* retval		: HI_FAILURE  CNcomment: 失败  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_Abort(const struct jpeg_common_struct *cinfo)
{
#ifdef CONFIG_JPEG_GETDECTIME
		HI_S32 s32Ret  = HI_SUCCESS;
		HI_U32 u32PreTime = 0;
#endif

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
		if (NULL == pJpegHandle){
			return HI_SUCCESS;
		}

	   /**
		** if memory leak, take out this check
		** CNcomment: 要是有内存释放问题，去掉该判断 CNend\n
		**/
		if(HI_FALSE == pJpegHandle->bReleaseRes){
			JPEG_HDEC_ReleaseRes(cinfo);
		}

		/**
		** dinit the para, these are the same as init para value
		** CNcomment: 去初始化变量的值，保证和初始化变量的值保持一致 CNend\n
		**/
#ifdef CONFIG_JPEG_GETDECTIME
		u32PreTime = pJpegHandle->u32CurTime;
#endif		
		memset(pJpegHandle,0,sizeof(JPEG_HDEC_HANDLE_S));		
		pJpegHandle->bReleaseRes        =  HI_TRUE;
		

		pJpegHandle->bFirstDec			=  HI_TRUE;
		pJpegHandle->u32StrideAlign 	= JPGD_HDEC_MMZ_CSCOUT_STRIDE_ALIGN;

#ifdef CONFIG_JPEG_GETDECTIME
		s32Ret	= HI_GFX_GetTimeStamp(&pJpegHandle->u32CurTime,NULL);
		if(HI_SUCCESS != s32Ret){
			free(pJpegHandle);
			return HI_FAILURE;
		}
		pJpegHandle->u32DecTime = pJpegHandle->u32CurTime - u32PreTime;
#endif

#ifdef CONFIG_JPEG_MMU_SUPPORT
		/** default all is mmz memory **/
		pJpegHandle->u32MemTypeMask = 0X0;
#endif

		pJpegHandle->s32ClientData	 =  CLIENT_DATA_MARK;
		pJpegHandle->s32JpegDev 	 =  -1;

#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pJpegHandle->s32MMZDev		 =  -1;
#endif

		pJpegHandle->u32Inflexion	 =  JPGD_HDEC_FLEXION_SIZE;
		pJpegHandle->u32Alpha		 =  0xFF;

#ifdef CONFIG_JPEG_PROC_ENABLE
		pJpegHandle->eDecState		 =  JPEG_DEC_STATE_BUTT;
#endif

		pJpegHandle->enImageFmt      =  JPEG_FMT_BUTT;

		return HI_SUCCESS;
		 
}

/*****************************************************************************
* func			: JPEG_HDEC_CheckCropSurface
* description	: check the crop rect whether is reasonable
				  CNcomment: 判断裁剪区域是否合理 CNend\n
* param[in] 	: cinfo 	  CNcomment: 解码对象 CNend\n
* retval		: NA
* others:		: NA
*****************************************************************************/
HI_VOID JPEG_HDEC_CheckCropSurface(const struct jpeg_decompress_struct *cinfo)
{

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
		if(  (pJpegHandle->stOutDesc.stCropRect.w <= 0) || (pJpegHandle->stOutDesc.stCropRect.h <= 0)
		   ||(pJpegHandle->stOutDesc.stCropRect.x < 0)  ||  (pJpegHandle->stOutDesc.stCropRect.y < 0)
		   ||((HI_U32)(pJpegHandle->stOutDesc.stCropRect.x + pJpegHandle->stOutDesc.stCropRect.w) > cinfo->output_width)
		   ||((HI_U32)(pJpegHandle->stOutDesc.stCropRect.y + pJpegHandle->stOutDesc.stCropRect.h) > cinfo->output_height)){
			ERREXIT(cinfo, JERR_CROP_CANNOT_SUPPORT);  /*lint !e740  ignore by y00181162, because this function is macro */ 
		}

}
/*****************************************************************************
* func			: JPEG_HDEC_IfSupport
* description	: check whether the hard decode support
				  CNcomment: 判断是否支持硬件解码 CNend\n
* param[in] 	: cinfo 	  CNcomment: 解码对象 CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功	  CNend\n
* retval		: HI_FAILURE  CNcomment: 失败	  CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_IfSupport(j_decompress_ptr cinfo)
{

		HI_U32 u32ImageSize	    = 0; /**< the jpeg picture size  *//**<CNcomment:图片大小         */
		HI_S32 s32RetVal		= HI_FAILURE;

#ifdef CONFIG_JPEG_DEBUG_INFO
	#ifdef CONFIG_JPEG_ANDROID_DEBUG_ENABLE
		HI_CHAR JpegDecMod[256]   = {0}; /**< select jpeg decode module   *//**<CNcomment:选择解码方式  */
	#else
		HI_CHAR *pJpegDecMod       = NULL;
	#endif
#endif

#if defined(CONFIG_JPEG_ADD_GOOGLEFUNCTION) && defined(ANDROID_BROWER_FUNCTION)
		HI_CHAR ProcName[25];
        HI_CHAR Name[25];
		HI_S32 s32Pid = 0;
		HI_CHAR ProcessStatusPath[256] ;
		FILE* pProcessStatus = NULL;
#endif

#ifndef CONFIG_JPEG_SET_SAMPLEFACTOR/**hifone has revise this bug **/
		/** HSCP201405300013 HSCP201405290010 DTS2014061006717**/
		HI_S32 ci = 0;
		HI_BOOL bY22 = HI_FALSE;
		HI_BOOL bU12 = HI_FALSE;
		HI_BOOL bV12 = HI_FALSE;
		jpeg_component_info *compptr = NULL;
#endif

#ifdef CONFIG_JPEG_STREAMBUF_4ALIGN
		HI_U32 u32ConsumSize  = 0;
		HI_CHAR* pDataPhyAddr = NULL;
#endif

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		/**
		 ** at hard decode, we check this message only once just ok 
		 ** because only one program can operation,and if the message
		 ** is wrong, the hardware can not support, so the followed 
		 ** can not operation
		 ** CNcomment: 硬件解码过程只判断一次，假如这个值被改变了，要么使用内部的退出函数
		 **            退出整个应用，要么使用用户回调的错误管理函数结束该张图片解码 CNend\n
		 **/
		if(CLIENT_DATA_MARK != pJpegHandle->s32ClientData){
			ERREXIT(cinfo, JERR_CLIENT_DATA_ERR); /*lint !e740  ignore by y00181162, because this function is macro */  
		}

#ifdef CONFIG_JPEG_TEST_CHIP_RANDOM_RESET
		HI_JPEG_RandomResetInit();
#endif

		JPEG_HDEC_GetImagInfo(cinfo);
		JPEG_ASSERT((pJpegHandle->u32ScalRation > 3), JPEG_ERR_UNSUPPORT_SCALE);

		if(HI_TRUE == pJpegHandle->stOutDesc.bCrop){
			JPEG_HDEC_CheckCropSurface(cinfo);
		}

		pJpegHandle->bReleaseRes =  HI_FALSE;


		/**===========================================================================
		 ** 目前应用方案中：没有使用频域缩放的功能, 在设置频域缩放的时候可以不丢色度；
		 ** 目前逻辑设计方案是：缩放1/2,1/4与不缩放时丢色度，是复用同一套逻辑
		 ** 但如果要支持1/8缩放丢色度的话，存在诸多限制
		 ** (1) 对输入图片大小有限制；
		 ** (2) 只丢色度的话，输出可能存在亮度与色度数量不匹配的问题；
		 ** (3) 硬件逻辑不能复用，要额外增加控制逻辑，实现比较复杂。
				因此，考虑硬件暂不支持1/8缩放时丢弃色度，在1/8缩放时交由软件处理。
		===========================================================================**/
#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
		if(HI_TRUE == pJpegHandle->bOutYUV420SP && 3 == pJpegHandle->u32ScalRation){
			return HI_FAILURE;
		}
#endif

		
#ifdef CONFIG_JPEG_DEBUG_INFO
	#ifdef CONFIG_JPEG_ANDROID_DEBUG_ENABLE
			/**
			** how to use this, when run android,you can get default value = "hw",
			** so when you not run( setprop JPEGDECMOD soft(or other char valu) ),is all run hard decode
			** CNcomment:android程序运行过程中,首先获取默认的值hw，要是运行
			** 过程中没有setprop JPEGDECMOD soft(除了hw字符) 就一直是hw值了 CNend\n
			**/
			property_get("JPEGDECMOD",JpegDecMod,"hw");
			if(0 != strncmp("hw", JpegDecMod, strlen("hw")>strlen(JpegDecMod)?strlen("hw"):strlen(JpegDecMod))){
				JPEG_TRACE("=== force to soft decode !\n");
				return HI_FAILURE;
			}
	#else
			/**
			**use the export entironment var
			**export JPEGDECMOD=soft 软件解码
			**默认硬件解码支持走硬件解码
			**/
			pJpegDecMod = getenv( "JPEGDECMOD" );
			if(pJpegDecMod && 0 == strncmp("soft", pJpegDecMod, strlen("soft")>strlen(pJpegDecMod)?strlen("soft"):strlen(pJpegDecMod))){ 
				JPEG_TRACE("=== force to soft decode !\n");
				return HI_FAILURE;
			}
	#endif
#endif


#if defined(CONFIG_JPEG_ADD_GOOGLEFUNCTION) && defined(ANDROID_BROWER_FUNCTION)
		s32Pid = getpid();
		memset(ProcessStatusPath, 0, 256);
		snprintf(ProcessStatusPath,256,"%s%d%s","/proc/",s32Pid,"/status");
		pProcessStatus = fopen(ProcessStatusPath, "r");
		if(NULL != pProcessStatus){
			memset(ProcName, 0, 25);
			fscanf(pProcessStatus,"%s %s",Name,ProcName);
			fclose(pProcessStatus);
		}
		#if 0
		/** revise by y0018162,the browser anr because the stream seek pointer is null **/
		if(0 == strncmp("android.browser", ProcName, strlen("android.browser")>strlen(ProcName)?strlen("android.browser"):strlen(ProcName)))
		{
			return HI_FAILURE;
		}
		#endif
		if((0 == strncmp("ndroid.cts.stub", ProcName, strlen("ndroid.cts.stub")>strlen(ProcName) ? strlen("ndroid.cts.stub"):strlen(ProcName))) || (0 == strncmp("id.cts.graphics", ProcName, strlen("id.cts.graphics")>strlen(ProcName) ? strlen("id.cts.graphics"):strlen(ProcName)))){
			return HI_FAILURE;
		}
#endif


#ifndef CONFIG_JPEG_DRI_SUPPORT
        if(    0 != pJpegHandle->s32LuDcLen[0] || 0 != pJpegHandle->s32LuDcLen[1] \
            || 0 != pJpegHandle->s32LuDcLen[2] || 0 != pJpegHandle->s32LuDcLen[3] \
            || 0 != pJpegHandle->s32LuDcLen[4] || 0 != pJpegHandle->s32LuDcLen[5]){
            /** 修改当时dri图片解码花屏问题，要是不符合亮度DC协议规定 **/
            return HI_FAILURE;
        }
#endif

		/**
		** the hard decode support resolution
		** CNcomment: 硬件支持的解码分辨率 CNend\n
		**/
		if (	(cinfo->image_width  < 1)
			|| (cinfo->image_width  > 8096)
			|| (cinfo->image_height < 1)
			|| (cinfo->image_height > 8096)){
			return HI_FAILURE;
		}

		/**
		** Get the image inflexion, use hardwire decode or soft decode
		** CNcomment: 获取软解和硬解的拐点 CNend\n
		**/
		u32ImageSize = cinfo->image_width * cinfo->image_height;
		if(u32ImageSize <= pJpegHandle->u32Inflexion){
			return HI_FAILURE;
		}

		/**
		** the CMYK and YCCK color space,the hard decode can not support
		** JCS_YCbCr TDE not support
		** CNcomment: 这两种图像格式硬件解码不支持，TDE不支持JCS_YCbCr转换 CNend\n
		**/
		/**
		 **JPEG_FMT_YUV422_21 == pJpegHandle->enImageFmt
		 **HSCP201405300013 HSCP201405290010 暂时规避yuv422 21采样因子为(Y:2*2 U:1*2 V:1*2)
		 **图片逻辑解码异常
		 **待逻辑修订该bug之后重新去掉该判断。解码异常图片在16test_user_problem
		 **user_program001.jpg，user_program002.jpg
		 **/
		if(   (JCS_CMYK  == cinfo->jpeg_color_space)
			||(JCS_YCCK  == cinfo->jpeg_color_space)
			||(JCS_YCbCr == cinfo->out_color_space)
			||(JCS_GRAYSCALE == cinfo->out_color_space)){
			return HI_FAILURE;
		}

#ifndef CONFIG_JPEG_SET_SAMPLEFACTOR/**hifone has revise this bug **/
		/** HSCP201405300013 HSCP201405290010 DTS2014061006717**/
		for (ci = 0; ci < cinfo->comps_in_scan; ci++){
			compptr = cinfo->cur_comp_info[ci];
			if( (0 == ci) && (2 == compptr->h_samp_factor) && (2 == compptr->v_samp_factor))
				bY22 = HI_TRUE;
			if( (1 == ci) && (1 == compptr->h_samp_factor) && (2 == compptr->v_samp_factor))
				bU12 = HI_TRUE;
			if( (2 == ci) && (1 == compptr->h_samp_factor) && (2 == compptr->v_samp_factor))
				bV12 = HI_TRUE;
		}
		if( (HI_TRUE == bY22) && (HI_TRUE == bU12) && (HI_TRUE == bV12)){
			return HI_FAILURE;
		}
		if( (JPEG_FMT_YUV444 == pJpegHandle->enImageFmt) && (HI_TRUE == bU12) && (HI_TRUE == bV12)){
			return HI_FAILURE;
		}
#endif

		/**
		** progressive, arith code ,data_prcidion !=8, cann't use hard decode 
		** CNcomment: progressive arith code data_prcidion !=8硬件不支持 CNend\n
		**/
		if(	(FALSE != cinfo->progressive_mode) ||(FALSE != cinfo->arith_code) ||(8 != cinfo->data_precision)){
			return HI_FAILURE;
		}

	   /**
		** the leave stream dispose
		** CNcomment: 剩余码流处理 CNend\n
		**/
#if 0
		if(HI_TRUE == pJpegHandle->stHDecDataBuf.bUseFileData)
		{
			pJpegHandle->stJpegHtoSInfo.pLeaveBuf	= (HI_CHAR*)calloc(1, INPUT_BUF_SIZE);
			if(NULL == pJpegHandle->stJpegHtoSInfo.pLeaveBuf)
			{
				return HI_FAILURE;
			}
		}
#endif

#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
		pJpegHandle->s32MMZDev = gfx_mem_open();
		if(pJpegHandle->s32MMZDev < 0){
			return HI_FAILURE;
		}
#endif

		/**
		** if the jpeg image have not any dqt table,we use standard table
		** CNcomment:要是jpeg文件没有带量化表就使用标准量化表 CNend\n
		**/
#ifndef CONFIG_JPEG_MPG_DEC_ENABLE
		if(NULL == cinfo->quant_tbl_ptrs[0]){
			ERREXIT(cinfo, JERR_NO_QUANT_TABLE); /*lint !e740 ignore by y00181162, because this is needed */
		}
#endif
		/**
		** if the jpeg image have not  huff table,we use standard table
		** CNcomment:要是jpeg文件没有带哈夫曼表就使用标准哈夫曼表 CNend\n
		**/
#ifndef CONFIG_JPEG_MPG_DEC_ENABLE
		if (	(NULL == cinfo->dc_huff_tbl_ptrs[0]) || (NULL != cinfo->dc_huff_tbl_ptrs[2]) 
			 || (NULL == cinfo->ac_huff_tbl_ptrs[0]) || (NULL != cinfo->ac_huff_tbl_ptrs[2]) ){
			ERREXIT(cinfo, JERR_BAD_HUFF_TABLE); /*lint !e740 ignore by y00181162, because this is needed */
		}
#endif

	   /** here all information is hard decode need,so failure should use soft dec,should not exit **/

	   /**
		** get the stream mem, if the stream from the user physics mem,
		** no need alloc this mem.is critical variable,so should consider
		** the many pthread.
		** CNcomment: 获取码流buffer内存，要是码流来源于用户连续的物理内存
		** 		   这里就不需要分配了，只需要给宏开关赋值为0即可。这个
		** 		   地方属于临界资源，所以要考虑到多线程的问题，要是有问题就不使用这种方式了 CNend\n
		**/
		/** if use the user stream phy buffer,should not alloc 1M buffer **/
#ifdef CONFIG_JPEG_STREAMBUF_4ALIGN
		u32ConsumSize = pJpegHandle->stHDecDataBuf.u32ConsumeDataSize - cinfo->src->bytes_in_buffer;
		pDataPhyAddr  = pJpegHandle->stHDecDataBuf.pDataPhyBuf + u32ConsumSize;
		if((HI_FALSE == pJpegHandle->stHDecDataBuf.bUserPhyMem) || (0 != ((HI_S32)pDataPhyAddr % JPGD_HDEC_MMZ_BUG_BUFFER_ALIGN)))
#else
		if(HI_FALSE == pJpegHandle->stHDecDataBuf.bUserPhyMem)
#endif
		{
			s32RetVal = JPEG_HDEC_GetStreamMem(pJpegHandle,JPGD_HARD_BUFFER);
			if(HI_SUCCESS != s32RetVal){/** soft decode, output user buffer **/
				return HI_FAILURE;
			}
		}

		/**
		** get the middle mem
		** CNcomment: 获取硬件解码的中间buffer CNend\n
		**/ 
		s32RetVal = JPEG_HDEC_GetYUVMem(pJpegHandle);
		if(HI_SUCCESS != s32RetVal){/** soft decode, output user buffer **/
			return HI_FAILURE;
		}

#ifdef CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bDecARGB){
			s32RetVal = JPEG_HDEC_GetMinMem(pJpegHandle);
			if(HI_SUCCESS != s32RetVal){/** soft decode, output user buffer **/
				return HI_FAILURE;
			}
		}
#endif

		s32RetVal = JPEG_HDEC_GetOutMem(cinfo);
		if(HI_SUCCESS != s32RetVal){/** soft decode, output user buffer **/
			return HI_FAILURE;
		}

		return HI_SUCCESS;
		 

}

/*****************************************************************************
* func			: JPEG_HDEC_Start
* description	: start jpeg hard decode
				  CNcomment: 开始硬件解码
* param[in] 	: cinfo 	  CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功	   CNend\n
* retval		: HI_FAILURE  CNcomment: 失败	   CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_Start(j_decompress_ptr cinfo)
{

		HI_S32 s32RetVal	=  HI_FAILURE;

#ifdef CONFIG_JPEG_FPGA_TEST_CONTINUE_STREAM_DDR_CHANGE
		HI_BOOL bConStreamChange = HI_FALSE;
#endif

#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
		HI_U32 u32RegistLuaPixSum0 = 0;
		HI_U64 u64RegistLuaPixSum1 = 0;
#endif

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);


		/**
		** set parameter thar hard decode need
		** CNcomment:配置硬件解码需要的参数 CNend\n
		**/
		s32RetVal = JPEG_HDEC_SetPara(cinfo);
		if(HI_SUCCESS != s32RetVal){
			return HI_FAILURE;
		}
	   /**
		** this var only used at use callback stream function
		** CNcomment: 这个变量仅用在使用回调码流函数进行解码的情况 CNend\n
		**/
		pJpegHandle->bInHardDec = HI_TRUE;
		
		/**
		 ** send the stream to hard register to start dec
		 ** CNcomment:将码流送给硬件寄存器开始解码 CNend\n
		 **/
		if(HI_FALSE == pJpegHandle->stHDecDataBuf.bUseInsideData){
			s32RetVal = JPEG_HDEC_SendStreamFromCallBack(cinfo);
		}else{
			#ifdef CONFIG_JPEG_STREAMBUF_4ALIGN
			if(HI_TRUE == pJpegHandle->stHDecDataBuf.bNeedStreamReturn){
				JPEG_HDEC_SendStreamFromReturnPhyMem(cinfo);
			}else if(HI_TRUE == pJpegHandle->stHDecDataBuf.bUserPhyMem)
			#else
			if(HI_TRUE == pJpegHandle->stHDecDataBuf.bUserPhyMem)
			#endif
			{
				s32RetVal = JPEG_HDEC_SendStreamFromPhyMem(cinfo);
			}else if(HI_TRUE == pJpegHandle->stHDecDataBuf.bUseFileData){
				#ifdef CONFIG_JPEG_FPGA_TEST_CONTINUE_STREAM_DDR_CHANGE
					HI_JPEG_GetConStreamDDRChangeFlag(&bConStreamChange);
					if(HI_TRUE == bConStreamChange){
						s32RetVal = JPEG_HDEC_SendStreamFromFileWithConDDRChange(cinfo);
					}else{
						s32RetVal = JPEG_HDEC_SendStreamFromFile(cinfo);
					}
				#else
					s32RetVal = JPEG_HDEC_SendStreamFromFile(cinfo);
				#endif
			}else{
				s32RetVal = JPEG_HDEC_SendStreamFromVirMem(cinfo);
			}
		}

		if(HI_FAILURE == s32RetVal){
			 return HI_FAILURE;
		}


		#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
		/**
		 ** get the lu pixle value
		 ** CNcomment: 获取亮度值大小 CNend\n
		 **/
		if(HI_TRUE == pJpegHandle->bLuPixSum){
		   	u32RegistLuaPixSum0 = (HI_U32)JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_LPIXSUM0);
			u64RegistLuaPixSum1 = (HI_U64)(JPEG_HDEC_ReadReg(pJpegHandle->pJpegRegVirAddr,JPGD_REG_LPIXSUM1) & 0xf);
			pJpegHandle->u64LuPixValue = (HI_U64)((u64RegistLuaPixSum1<<32) | u32RegistLuaPixSum0);
		}
        #endif
		
		/**
		 ** the jpeg hard decode finish
		 ** CNcomment: jpeg硬件解码完成 CNend\n
		 **/	
		pJpegHandle->bHdecEnd  = HI_TRUE;

#ifdef CONFIG_JPEG_TEST_SAVE_YUVSP_DATA
		HI_JPEG_SaveYUVSP(cinfo);
#endif

#ifdef CONFIG_JPEG_TEST_CHIP_RANDOM_RESET
		HI_JPEG_SetDecState(HI_TRUE);
#endif

		return HI_SUCCESS;
		
}


/*****************************************************************************
* func			: JPEG_HDEC_SetComponent
* description	: set components
				  CNcomment: 设置组件数 CNend\n
* param[in] 	: cinfo 	 CNcomment: 解码对象 CNend\n
* retval		: HI_SUCCESS CNcomment: 成功	 CNend\n
* retval		: HI_FAILURE CNcomment: 失败	 CNend\n
* others:		: NA
*****************************************************************************/
#if defined(CONFIG_JPEG_CSC_DISABLE) || defined(CONFIG_JPEG_HARDDEC2ARGB)
static HI_VOID JPEG_HDEC_SetCompoent(j_decompress_ptr cinfo)
{
	
	switch(cinfo->out_color_space){
	    case JCS_CMYK:
		case JCS_ARGB_8888:
		case JCS_ABGR_8888:
		#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
		case JCS_RGBA_8888:
		#endif
			cinfo->output_components = 4;
			break;
		case JCS_RGB:
		case JCS_BGR:
		case JCS_CrCbY:
			cinfo->output_components = 3;
			break;
		case JCS_ARGB_1555:
		case JCS_ABGR_1555:
		case JCS_RGB_565:
		case JCS_BGR_565:
			cinfo->output_components = 2;
			break;
		default:
			break;
	}
	
}
#endif


#ifdef CONFIG_JPEG_SOFTCSC_ENABLE


/*****************************************************************************
* func			: ycc2rgb
* description	: yuv to rgb
                  CNcomment: yuv 转 RGB CNend\n
* param[in] 	: cinfo      CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS CNcomment: 成功      CNend\n
* retval		: HI_FAILURE CNcomment: 失败      CNend\n
* others:		: NA
*****************************************************************************/
static HI_VOID ycc2rgb(HI_U8 y, HI_U8 cb, HI_U8 cr, HI_U8 *r, HI_U8 *g, HI_U8 *b)
{
    *r = y               + 1.40200 * cr;
    *g = y - 0.34414 * cb - 0.71414 * cr;
    *b = y + 1.77200 * cb;
}

/*****************************************************************************
* func			: JPEG_HDEC_YUV400TORGB
* description	: yuv400 to rgb
                  CNcomment: yuv400 转 RGB CNend\n
* param[in] 	: cinfo      CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS CNcomment: 成功      CNend\n
* retval		: HI_FAILURE CNcomment: 失败      CNend\n
* others:		: NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_YUV400TORGB(j_decompress_ptr cinfo)
{
	HI_U8 r  = 0;
	HI_U8 g  = 0;
	HI_U8 b  = 0;
	HI_U8 y  = 0;
	HI_U8 cb = 0;
	HI_U8 cr = 0;
	HI_U32 u32Red   = 0;
	HI_U32 u32Green = 1;
	HI_U32 u32Blue  = 2;
	HI_S32 s32Row   = 0;
	HI_S32 s32Col   = 0;
	HI_U32 u32Count = 0;
	HI_S32 s32YRowStride   = 0;
	HI_S32 s32UVRowStride  = 0;
	HI_S32 s32DstRowStride = 0;
	HI_S32 s32YOffset      = 0;
	HI_S32 s32UVOffset     = 0;
	HI_S32 s32DstOffset    = 0;
	HI_CHAR* pYSrcBuf      = NULL;
	HI_CHAR* pUVSrcBuf     = NULL;
	HI_CHAR* pDtsSrcBuf    = NULL;
    JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
    
	pYSrcBuf    = pJpegHandle->stMiddleSurface.pMiddleVir[0];
	pUVSrcBuf   = pJpegHandle->stMiddleSurface.pMiddleVir[1];
	pDtsSrcBuf  = pJpegHandle->stMiddleSurface.pOutVir;

	s32YRowStride     = pJpegHandle->stJpegSofInfo.u32YStride;
	s32UVRowStride    = pJpegHandle->stJpegSofInfo.u32CbCrStride;
    s32DstRowStride	  = pJpegHandle->stJpegSofInfo.u32DisplayStride;
		
	for(s32Row = 0; s32Row < cinfo->output_height; s32Row++){
		s32YOffset    = s32YRowStride   * s32Row;
		s32UVOffset   = s32UVRowStride  * s32Row;
		s32DstOffset  = s32DstRowStride * s32Row;
		for(s32Col = 0; s32Col < cinfo->output_width; s32Col++){
			y  = pYSrcBuf[s32YOffset + s32Col];
			cb = 0x80;
			cr = 0x80;
			ycc2rgb(y,cb,cr,&r,&g,&b);
			switch(cinfo->out_color_space){
				case JCS_RGB:
					pDtsSrcBuf[s32DstOffset + 3 * u32Count + u32Red]   = r;
					pDtsSrcBuf[s32DstOffset + 3 * u32Count + u32Green] = g;
					pDtsSrcBuf[s32DstOffset + 3 * u32Count + u32Blue]  = b;
					u32Count++;
					break;
				case JCS_BGR:
					pDtsSrcBuf[s32DstOffset + 3 * u32Count + u32Blue]   = r;
					pDtsSrcBuf[s32DstOffset + 3 * u32Count + u32Green]  = g;
					pDtsSrcBuf[s32DstOffset + 3 * u32Count + u32Red]    = b;
					u32Count++;
					break;
				case JCS_ARGB_8888:
					break;
				case JCS_ABGR_8888:
					break;
				case JCS_ARGB_1555:
					break;
				case JCS_ABGR_1555:
					break;
				case JCS_RGB_565:
					break;
				case JCS_BGR_565:
					break;
				default:
					break;
			}
		}
	}
}

/*****************************************************************************
* func			: JPEG_HDEC_YUV420TORGB
* description	: yuv420 to rgb
                  CNcomment: yuv420 转 RGB CNend\n
* param[in] 	: cinfo      CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS CNcomment: 成功      CNend\n
* retval		: HI_FAILURE CNcomment: 失败      CNend\n
* others:		: NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_YUV420TORGB(j_decompress_ptr cinfo)
{


}

/*****************************************************************************
* func			: JPEG_HDEC_YUV444TORGB
* description	: yuv444 to rgb
                  CNcomment: yuv444 转 RGB CNend\n
* param[in] 	: cinfo      CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS CNcomment: 成功      CNend\n
* retval		: HI_FAILURE CNcomment: 失败      CNend\n
* others:		: NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_YUV444TORGB(j_decompress_ptr cinfo)
{


}


/*****************************************************************************
* func			: JPEG_HDEC_YUV42212TORGB
* description	: yuv422 12 to rgb
                  CNcomment: yuv422 12 转 RGB CNend\n
* param[in] 	: cinfo      CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS CNcomment: 成功      CNend\n
* retval		: HI_FAILURE CNcomment: 失败      CNend\n
* others:		: NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_YUV42212TORGB(j_decompress_ptr cinfo)
{


}

/*****************************************************************************
* func			: JPEG_HDEC_YUV42221TORGB
* description	: yuv422 21 to rgb
                  CNcomment: yuv422 21 转 RGB CNend\n
* param[in] 	: cinfo      CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS CNcomment: 成功      CNend\n
* retval		: HI_FAILURE CNcomment: 失败      CNend\n
* others:		: NA
*****************************************************************************/
static HI_VOID JPEG_HDEC_YUV42221TORGB(j_decompress_ptr cinfo)
{


}

/*****************************************************************************
* func			: JPEG_HDEC_SoftCSC
* description	: use soft csc, is use to debug the hard csc
                  CNcomment: 使用软件进行颜色空间转换,用来定位硬件转换的问题 CNend\n
* param[in] 	: cinfo      CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS CNcomment: 成功      CNend\n
* retval		: HI_FAILURE CNcomment: 失败      CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_SoftCSC(j_decompress_ptr cinfo)
{
	JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bDecARGB){
			pJpegHandle->bCSCEnd = HI_TRUE;
			JPEG_HDEC_SetCompoent(cinfo);
			return HI_SUCCESS;
		}
	#endif
	
	if((HI_TRUE == pJpegHandle->bOutYCbCrSP)||(HI_TRUE == pJpegHandle->bCSCEnd)){
			return HI_SUCCESS;
	}

	switch(pJpegHandle->enImageFmt){
		case JPEG_FMT_YUV400:
			JPEG_HDEC_YUV400TORGB(cinfo);
			break;
		case JPEG_FMT_YUV420:
			JPEG_HDEC_YUV420TORGB(cinfo);
			break;
		case JPEG_FMT_YUV444:
			JPEG_HDEC_YUV444TORGB(cinfo);
			break;
		case JPEG_FMT_YUV422_12:
			JPEG_HDEC_YUV42212TORGB(cinfo);
			break;
		case JPEG_FMT_YUV422_21:
			JPEG_HDEC_YUV42221TORGB(cinfo);
			break;
		default:
			return HI_FAILURE;
	}

	switch(cinfo->out_color_space){
		case JCS_RGB:
		case JCS_BGR:
			cinfo->output_components = 3;
			break; 
		case JCS_ARGB_8888:
		case JCS_ABGR_8888:
			cinfo->output_components = 4;
			break;
		case JCS_ARGB_1555:
		case JCS_ABGR_1555:
		case JCS_RGB_565:
		case JCS_BGR_565:
			cinfo->output_components = 2;
			break;
		default:
			return HI_FAILURE;
	}
	
	pJpegHandle->bCSCEnd = HI_TRUE;

	return HI_SUCCESS;
}

#else

/*****************************************************************************
* func			: JPEG_HDEC_HardCSC
* description	: use hard csc
				  CNcomment: 使用硬件进行颜色空间?? CNend\n
* param[in] 	: cinfo 	 CNcomment: 解码对象 CNend\n
* retval		: HI_SUCCESS CNcomment: 成功	 CNend\n
* retval		: HI_FAILURE CNcomment: 失败	 CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_HardCSC(j_decompress_ptr cinfo)
{
#ifndef CONFIG_JPEG_CSC_DISABLE
		/** have set value,so should not init **/
		TDE2_MB_S		SrcSurface;
		TDE2_SURFACE_S	DstSurface;
		TDE2_RECT_S  SrcRect,DstRect;

		TDE2_MBOPT_S  stMbOpt;
		TDE_HANDLE s32Handle;
		HI_S32 s32Ret           =  HI_SUCCESS;
		HI_BOOL bYUVMemMMUType  = HI_TRUE;
		HI_BOOL bXRGBMemMMUType = HI_TRUE;
		
		TDE2_MB_COLOR_FMT_E enMbFmt[6] = {
			TDE2_MB_COLOR_FMT_JPG_YCbCr400MBP,
			TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP,
			TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP,
			TDE2_MB_COLOR_FMT_JPG_YCbCr422MBVP,
			TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP,
			TDE2_MB_COLOR_FMT_BUTT,
		};

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		
		if((pJpegHandle->u32MemTypeMask & JPEG_YOUTPUT_MEM_MMU_TYPE) || (pJpegHandle->u32MemTypeMask & JPEG_UVOUTPUT_MEM_MMU_TYPE)){
			bYUVMemMMUType = HI_TRUE;
		}else{
			bYUVMemMMUType = HI_FALSE;
		}
		if(pJpegHandle->u32MemTypeMask & JPEG_XRGBOUTPUT_MEM_MMU_TYPE){
			bXRGBMemMMUType = HI_TRUE;
		}else{
			bXRGBMemMMUType = HI_FALSE;
		}

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bDecARGB){
			/** 认为TDE转换成功了 **/
			pJpegHandle->bCSCEnd = HI_TRUE;
			JPEG_HDEC_SetCompoent(cinfo);
			return HI_SUCCESS;
		}
#endif

		if( (HI_TRUE == pJpegHandle->bOutYCbCrSP)||(HI_TRUE == pJpegHandle->bCSCEnd)){
		 /**
		  ** no need tde csc,only add the sanlines
		  ** CNcomment: 不需要TDE转换了，只需要增加行数 CNend\n
		  **/
			return HI_SUCCESS;
		}

		/**
		** if has image quality quest,you should change the tde coef
		** CNcomment: 如果有图片质量的需求就要通过make menuconfig来修改TDE系数，默认没有分配好内存 CNend\n
		**/

		/**
		** src data from jpeg hard dec output
		** CNcomment: jpeg 硬件解码的输出数据 CNend\n
		**/
		SrcSurface.u32YPhyAddr	  = (unsigned long)(pJpegHandle->stMiddleSurface.pMiddlePhy[0]);
		SrcSurface.u32CbCrPhyAddr = (unsigned long)(pJpegHandle->stMiddleSurface.pMiddlePhy[1]);
		SrcSurface.enMbFmt	      = enMbFmt[pJpegHandle->enImageFmt];
		SrcSurface.u32YWidth	  = pJpegHandle->stJpegSofInfo.u32DisplayW;
		SrcSurface.u32YHeight     = pJpegHandle->stJpegSofInfo.u32DisplayH;
		SrcSurface.u32YStride     = pJpegHandle->stJpegSofInfo.u32YStride;
		SrcSurface.u32CbCrStride  = pJpegHandle->stJpegSofInfo.u32CbCrStride;

#if 0
		JPEG_TRACE("============================================================================\n");
        /** crop debug **/
		JPEG_TRACE("SrcSurface.u32YWidth      = %d\n",SrcSurface.u32YWidth);
		JPEG_TRACE("SrcSurface.u32YHeight     = %d\n",SrcSurface.u32YHeight);
		JPEG_TRACE("SrcSurface.u32YStride     = %d\n",SrcSurface.u32YStride);
		JPEG_TRACE("SrcSurface.u32CbCrStride  = %d\n",SrcSurface.u32CbCrStride);
		JPEG_TRACE("============================================================================\n");
#endif
		/**
		** tde csc output data,not use memset, because the memset cost many times.
		** CNcomment: tde转换之后的输出数据 CNend\n
		**/
		switch(cinfo->out_color_space){
			case JCS_RGB:
				DstSurface.enColorFmt    = TDE2_COLOR_FMT_BGR888;
				cinfo->output_components = 3;
				break; 
			case JCS_BGR:
				DstSurface.enColorFmt	 = TDE2_COLOR_FMT_RGB888;
				cinfo->output_components = 3;
				break; 
			case JCS_ARGB_8888:
			#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
			case JCS_RGBA_8888:
			#endif
				DstSurface.enColorFmt	 = TDE2_COLOR_FMT_ABGR8888;
				cinfo->output_components = 4;
				break;
			case JCS_ABGR_8888:
				DstSurface.enColorFmt	 = TDE2_COLOR_FMT_ARGB8888;
				cinfo->output_components = 4;
				break;
			case JCS_ARGB_1555:
				DstSurface.enColorFmt	 = TDE2_COLOR_FMT_ABGR1555;
				cinfo->output_components = 2;
				break;
			case JCS_ABGR_1555:
				DstSurface.enColorFmt	 = TDE2_COLOR_FMT_ARGB1555;
				cinfo->output_components = 2;
				break;
			case JCS_RGB_565:
				#ifdef CONFIG_JPEG_LITTLE_TRANSFORM_BIG_ENDIAN
				DstSurface.enColorFmt    = TDE2_COLOR_FMT_RGB565;
				#else
				DstSurface.enColorFmt    = TDE2_COLOR_FMT_BGR565;
				#endif
				cinfo->output_components = 2;
				break;
			case JCS_BGR_565:
				DstSurface.enColorFmt	  = TDE2_COLOR_FMT_RGB565;
				cinfo->output_components = 2;
				break;
			case JCS_CrCbY:
				DstSurface.enColorFmt    = TDE2_COLOR_FMT_YCbCr888;
				cinfo->output_components = 3;
				break; 
			default:
				return HI_FAILURE;
		}

		DstSurface.u32PhyAddr 	  = (unsigned long)pJpegHandle->stMiddleSurface.pOutPhy;
		if(HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem){
			DstSurface.u32Stride	  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0];
		}else{
			DstSurface.u32Stride	  = pJpegHandle->stJpegSofInfo.u32DisplayStride;
		}
		DstSurface.u32Width		  = (HI_U32)pJpegHandle->stOutDesc.stCropRect.w;
		DstSurface.u32Height      = (HI_U32)pJpegHandle->stOutDesc.stCropRect.h;
		DstSurface.pu8ClutPhyAddr = NULL;
		DstSurface.bYCbCrClut 	  = HI_FALSE;
		DstSurface.bAlphaMax255	  = HI_TRUE;
		DstSurface.bAlphaExt1555  = HI_TRUE;
		DstSurface.u8Alpha0		  = 0;
		DstSurface.u8Alpha1		  = 255;
		DstSurface.u32CbCrPhyAddr = 0;
		DstSurface.u32CbCrStride  = 0;

		/**
		 ** if the rect equal with the output size, that has been crop.other has no crop.
		 ** CNcomment:是否有裁剪是看rect大小,要是和输出大小保持一致就没有裁剪 CNend\n
		 **/
		SrcRect.s32Xpos   = pJpegHandle->stOutDesc.stCropRect.x;
		SrcRect.s32Ypos   = pJpegHandle->stOutDesc.stCropRect.y;
		SrcRect.u32Width  = (HI_U32)pJpegHandle->stOutDesc.stCropRect.w;
		SrcRect.u32Height = (HI_U32)pJpegHandle->stOutDesc.stCropRect.h;
		DstRect.s32Xpos   = 0;
		DstRect.s32Ypos   = 0;
		DstRect.u32Width  = (HI_U32)pJpegHandle->stOutDesc.stCropRect.w;
		DstRect.u32Height = (HI_U32)pJpegHandle->stOutDesc.stCropRect.h;

#if 0
		JPEG_TRACE("============================================================================\n");
        /** crop debug **/
		JPEG_TRACE("DstSurface.u32Width  = %d\n",DstSurface.u32Width);
		JPEG_TRACE("DstSurface.u32Height = %d\n",DstSurface.u32Height);
		JPEG_TRACE("DstSurface.u32Stride = %d\n",DstSurface.u32Stride);
		JPEG_TRACE("DstRect.s32Xpos      = %d\n",DstRect.s32Xpos);
		JPEG_TRACE("DstRect.s32Ypos      = %d\n",DstRect.s32Ypos);
		JPEG_TRACE("DstRect.u32Width     = %d\n",DstRect.u32Width);
		JPEG_TRACE("DstRect.u32Height    = %d\n",DstRect.u32Height);
		JPEG_TRACE("============================================================================\n");
#endif
		/**
		**这个操作性能会变差，但是消告警
		**/
		memset(&stMbOpt,0,sizeof(TDE2_MBOPT_S));
		stMbOpt.enResize   = TDE2_MBRESIZE_QUALITY_LOW;
		//stMbOpt.bDeflicker = HI_TRUE;
		
		if ((s32Handle = JPEG_HDEC_CSC_BeginJob(gs_stJpegDecompressRes.s32CscDev)) != HI_ERR_TDE_INVALID_HANDLE){
			s32Ret = JPEG_HDEC_CSC_MbBlit(s32Handle, &SrcSurface, &SrcRect, &DstSurface, &DstRect, &stMbOpt,gs_stJpegDecompressRes.s32CscDev,bYUVMemMMUType,bXRGBMemMMUType);
			if(HI_SUCCESS != s32Ret){
			    JPEG_TRACE("==== JPEG_HDEC_CSC_MbBlit Failure,s32Ret = 0x%x!\n",s32Ret);
				return HI_FAILURE;
			}
			/**
			** if HI_TRUE,is no sync. and HI_FALSE you should call tde wait for done to
			** waite the tde work finish.
			** CNcomment:HI_TRUE 阻塞，要是非阻塞要调用waitfordone等待TDE操作完成 CNend\n
			**/
			s32Ret = JPEG_HDEC_CSC_EndJob(s32Handle, HI_FALSE, HI_TRUE, 10000,gs_stJpegDecompressRes.s32CscDev);
			if(HI_SUCCESS != s32Ret){
			    JPEG_TRACE("==== JPEG_HDEC_CSC_EndJob Failure,s32Ret = 0x%x!\n",s32Ret);
				return HI_FAILURE;
			}
		}

		pJpegHandle->bCSCEnd = HI_TRUE;

#ifdef CONFIG_JPEG_TEST_SAVE_BMP_PIC
		HI_JPEG_SaveBmp(DstSurface.u32PhyAddr, \
						DstRect.u32Width,      \
						DstRect.u32Height,     \
						DstSurface.u32Stride,  \
						cinfo);
#endif


#else
		#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);
		if(HI_TRUE == pJpegHandle->bDecARGB){
			/** 认为TDE转换成功了 **/
			pJpegHandle->bCSCEnd = HI_TRUE;
		}
		#endif
		JPEG_HDEC_SetCompoent(cinfo);
#endif
		return HI_SUCCESS;
		  

}

#endif

/*****************************************************************************
* func			: JPEG_HDEC_CheckCpy
* description	: check whethe should cpy to user buffer
				  CNcomment:  确认是否需要拷贝到用户 buffer中 CNend\n
* param[in] 	: cinfo 	 CNcomment:  解码对象  CNend\n
* param[out] 	: max_lines  CNcomment:  解码行数  CNend\n
* retval		: HI_SUCCESS CNcomment:  成功	   CNend\n
* retval		: HI_FAILURE CNcomment:  失败	   CNend\n
* others:		: NA
*****************************************************************************/
static HI_S32 JPEG_HDEC_CheckCpy(j_decompress_ptr cinfo,JDIMENSION max_lines)
{
	HI_U32 u32Cnt			 = 0;
	JPEG_HDEC_HANDLE_S_PTR	pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

	if(    (HI_FALSE == pJpegHandle->bCSCEnd)
		|| (HI_TRUE == pJpegHandle->stOutDesc.stOutSurface.bUserPhyMem)){  
		/**
		** not use tde convert or use physics buffer,so not output the usr buffer
		** CNcomment: tde转换失败或者使用物理内存，所以不需要输出到用户buffer中 CNend\n
		**/
		for(u32Cnt=0; u32Cnt<max_lines; u32Cnt++){
			(cinfo->output_scanline)++;
		}
		return (HI_S32)max_lines;
	}

	if(   (HI_TRUE == pJpegHandle->stOutDesc.bCrop)
		&&( ((HI_S32)(cinfo->output_scanline) < pJpegHandle->stOutDesc.stCropRect.y)
		   ||((HI_S32)(cinfo->output_scanline+1) > (pJpegHandle->stOutDesc.stCropRect.h + pJpegHandle->stOutDesc.stCropRect.y)))){
		for(u32Cnt=0; u32Cnt<max_lines; u32Cnt++){
			(cinfo->output_scanline)++;
		}
		return (HI_S32)max_lines;
	}

	return HI_FAILURE;

}

/*****************************************************************************
* func			: JPEG_HDEC_OutUserBuf
* description	: output the scanlines buffer
				  CNcomment:  输出到用户行buffer中 CNend\n
* param[in] 	: cinfo 	 CNcomment:  解码对象  CNend\n
* param[out] 	: max_lines  CNcomment:  解码行数  CNend\n
* param[out]	: scanlines  CNcomment:  行buffer  CNend\n
* retval		: HI_SUCCESS CNcomment:  成功	   CNend\n
* retval		: HI_FAILURE CNcomment:  失败	   CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_OutUserBuf(j_decompress_ptr cinfo,JDIMENSION max_lines, HI_CHAR *scanlines)
{


		HI_U32 u32Cnt           = 0;
		HI_U32 u32SrcStride     = 0;
		HI_U32 u32DstStride     = 0;
		HI_S32 s32BufSrcLength  = 0;
		HI_CHAR *pDstBuf         = NULL;
		HI_CHAR *pSrcBuf         = NULL;
		HI_S32 s32Ret            = 0;
		
		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		if ((max_lines+(cinfo->output_scanline)) > (cinfo->output_height)){
			max_lines = (cinfo->output_height) - (cinfo->output_scanline);
		}

		s32Ret = JPEG_HDEC_CheckCpy(cinfo,max_lines);
		if(HI_FAILURE != s32Ret){
			return s32Ret;
		}
		
		/**
		** is not set output description,so is output scanlines buffer
		** CNcomment:说明没有设置解码输出的属性，是输出到行buffer中 CNend\n
		**/
		u32SrcStride  = pJpegHandle->stJpegSofInfo.u32DisplayStride;
		u32DstStride  = pJpegHandle->stOutDesc.stOutSurface.u32OutStride[0];

#ifdef  CONFIG_JPEG_HARDDEC2ARGB
		if(HI_TRUE == pJpegHandle->bDecARGB){
			pSrcBuf   = pJpegHandle->stMiddleSurface.pMiddleVir[0] + ((HI_S32)cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y) * (HI_S32)(u32SrcStride);
		}
		else
#endif
		{
			pSrcBuf   = pJpegHandle->stMiddleSurface.pOutVir + ((HI_S32)cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y) * (HI_S32)(u32SrcStride);
		}

		if(NULL != scanlines){
			pDstBuf   = scanlines;
		}else{
			pDstBuf   = pJpegHandle->stOutDesc.stOutSurface.pOutVir[0] + ((HI_S32)cinfo->output_scanline - pJpegHandle->stOutDesc.stCropRect.y) * (HI_S32)(u32DstStride);
		}
		/**
		** data size in reality
		** CNcomment: 实际的数据大小 CNend\n
		**/
		s32BufSrcLength = (cinfo->output_components) * (pJpegHandle->stOutDesc.stCropRect.w);
		for(u32Cnt = 0; u32Cnt < max_lines; u32Cnt++){
			memcpy(pDstBuf,pSrcBuf,(size_t)s32BufSrcLength);
			(cinfo->output_scanline)++;
		}

#if 0
		if(cinfo->output_scanline == pJpegHandle->stOutDesc.stCropRect.h - 1)
		{
			JPEG_TRACE("============================================================================\n");
			JPEG_TRACE("s32BufSrcLength  = %d\n",s32BufSrcLength);
			JPEG_TRACE("u32Stride        = %d\n",u32Stride);
			JPEG_TRACE("============================================================================\n");
		}
#endif

		return (HI_S32)max_lines;

}
/*****************************************************************************
* func			: JPEG_HDEC_DuplicateStreamInfo
* description	: save the stream information before into hard decode
				  CNcomment: 在进入硬件解码之前保存码流信息，包括码流位置
				  剩余的码流以及剩余码流数。
* param[in] 	: cinfo 	  CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功	   CNend\n
* retval		: HI_FAILURE  CNcomment: 失败	   CNend\n
* others:		: NA
*****************************************************************************/
HI_S32	JPEG_HDEC_DuplicateStreamInfo(const struct jpeg_decompress_struct *cinfo)
{
#if 0
		my_src_ptr src = (my_src_ptr)cinfo->src; /*lint !e740 !e826 ignore by y00181162, because this is needed */  

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		if(HI_TRUE == pJpegHandle->stHDecDataBuf.bUseFileData)
		{  /**
			** only use file stream or use external stream should save the data.
			** because the mem stream decode, the hard has no change the 
			** cinfo->src->next_input_byte buffer and leave data.
			** CNcomment: 使用文件码流才需要回退，因为内存码流硬件解码的时候
			**            没有使用cinfo->src->next_input_byte这块临时buffer以及
			**            没有改变cinfo->src->bytes_in_buffer剩余码流大小 CNend\n
			**/
			pJpegHandle->stJpegHtoSInfo.u32FilePos = (HI_U32)ftell(src->infile);
			memcpy(pJpegHandle->stJpegHtoSInfo.pLeaveBuf,	\
			(char*)cinfo->src->next_input_byte,		\
			cinfo->src->bytes_in_buffer);
			pJpegHandle->stJpegHtoSInfo.u32LeaveByte = cinfo->src->bytes_in_buffer;

		}
#else
		if(cinfo->progressive_mode)
			return HI_SUCCESS;
#endif
		return HI_SUCCESS;

}

/*****************************************************************************
* func			: JPEG_HDEC_ResumeStreamInfo
* description	: resume the stream information when hard decode failure,and
				  then into soft decode
				  CNcomment: 当硬件解码失败的时候恢复原先保存的码流信息，然后
				  继续进行软件解码
* param[in] 	: cinfo 	  CNcomment: 解码对象  CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功	   CNend\n
* retval		: HI_FAILURE  CNcomment: 失败	   CNend\n
* others:		: NA
*****************************************************************************/
HI_S32	JPEG_HDEC_ResumeStreamInfo(j_decompress_ptr cinfo)
{
#if 0

		HI_S32 s32Ret;
		my_src_ptr src = (my_src_ptr) cinfo->src; /*lint !e740 !e826 ignore by y00181162, because this is needed */  

		JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

		if(HI_TRUE == pJpegHandle->stHDecDataBuf.bUseFileData)
		{
			s32Ret = fseek(src->infile,(long)pJpegHandle->stJpegHtoSInfo.u32FilePos,SEEK_SET);
			if(HI_SUCCESS != s32Ret)
			{ /**
			   ** the stream back failure,not soft decode again
			   ** CNcomment: 码流回退错误，不需要在进行软件解码了 CNend\n
			   **/
				ERREXIT(cinfo, JERR_STREAM_BACK_FAILURE); /*lint !e740  ignore by y00181162, because this function is macro */  
			}
			memcpy((char*)cinfo->src->next_input_byte,		   \
				   pJpegHandle->stJpegHtoSInfo.pLeaveBuf,	   \
				   pJpegHandle->stJpegHtoSInfo.u32LeaveByte);
			
			cinfo->src->bytes_in_buffer = pJpegHandle->stJpegHtoSInfo.u32LeaveByte;
			
		}
#else
		if(cinfo->progressive_mode)
			return HI_SUCCESS;
#endif
		return HI_SUCCESS;
		
}
/*****************************************************************************
* func			: JPEG_HDEC_CheckStreamMemType
* description	: check the stream buffer type, if user no call the function
				  of set stream buffer type,call this function
				  CNcomment: 查询码流buffer类型，是连续的物理内存，还是虚拟
				  内存，要是用户没有调用设置码流buffer类型，调用该接口
* param[in] 	: cinfo 	  CNcomment: 解码对象  CNend\n
* param[in] 	: pVirBuf	  CNcomment: 虚拟内存  CNend\n
* retval		: HI_SUCCESS  CNcomment: 成功	   CNend\n
* retval		: HI_FAILURE  CNcomment: 失败	   CNend\n
* others:		: NA
*****************************************************************************/
HI_S32 JPEG_HDEC_CheckStreamMemType(const struct jpeg_decompress_struct *cinfo,HI_UCHAR* pVirBuf)
{
     HI_U32 u32Size     = 0;
	 HI_S32 s32Ret      = HI_SUCCESS;
	 HI_CHAR* pPhyAddr  = NULL;
	 
#ifdef CONFIG_JPEG_MMU_SUPPORT
	 HI_BOOL bMmu;
#endif

	 JPEG_HDEC_HANDLE_S_PTR  pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)(cinfo->client_data);

#ifdef CONFIG_JPEG_USE_PRIVATE_MMZ
     s32Ret = HI_GFX_GetPhyaddr(pJpegHandle->s32MMZDev,(HI_VOID*)pVirBuf, pPhyAddr,&u32Size, NULL);
#else
	#ifdef CONFIG_JPEG_MMU_SUPPORT
	 s32Ret = HI_GFX_GetPhyaddr((HI_VOID*)pVirBuf, pPhyAddr,&u32Size, &bMmu);
	#else
	 s32Ret = HI_GFX_GetPhyaddr((HI_VOID*)pVirBuf, pPhyAddr,&u32Size);
	#endif
#endif
	 if(HI_SUCCESS == s32Ret){
          pJpegHandle->stHDecDataBuf.bUserPhyMem = HI_TRUE;
		  pJpegHandle->stHDecDataBuf.pDataPhyBuf = pPhyAddr;
		  #ifdef CONFIG_JPEG_MMU_SUPPORT
		    if(HI_TRUE == bMmu){
		  		pJpegHandle->u32MemTypeMask |= 0x1;
		    }
		  #endif
		  return HI_SUCCESS;
	 }else{
	     return HI_FAILURE;
	 }
	 
}
/*****************************************************************************
* func			: JPEG_HDEC_GetMemFromMemInfo
* description	: get leave memory from cat /proc/meminfo 
                  CNcomment: 从内存信息中获取剩余内存大小 CNend\n
* param[out]    : pu64MemSize  CNcomment:  内存大小  CNend\n
* retval	    : HI_SUCCESS   CNcomment:  成功      CNend\n
* retval	    : HI_FAILURE   CNcomment:  失败      CNend\n
* others:	    : NA
*****************************************************************************/
static HI_S32 compare_meminfo(const HI_VOID *pSrc, const HI_VOID *pDst)
{
	  HI_U32 u32SrcSize  = (HI_U32)strlen(((const JPEG_LEAVE_MEMINFO*)pSrc)->pName);
	  HI_U32 u32DstSize  = (HI_U32)strlen(((const JPEG_LEAVE_MEMINFO*)pDst)->pName);
	  return strncmp(((const JPEG_LEAVE_MEMINFO*)pSrc)->pName, ((const JPEG_LEAVE_MEMINFO*)pDst)->pName,u32SrcSize > u32DstSize ? u32SrcSize : u32DstSize);
}

HI_S32 JPEG_HDEC_GetMemFromMemInfo(HI_U64 *pu64MemSize)
{

	  HI_U64 MEMINFO_Buffers  = 0L;
	  HI_U64 MEMINFO_Cached   = 0L;
	  HI_U64 MEMINFO_MemFree  = 0L;
	  HI_U64 MEMINFO_MemTotal = 0L;
	  HI_CHAR NameBuf[256]     = {0};
	  
	  HI_CHAR MemInfoBuf[2048] = {0};
	  HI_S32  s32MemInfoFd        = -1;
	  HI_S32  s32ReadMemInfoSize = 0;
	  HI_S32  s32LeekOffset       = -1;
	  JPEG_LEAVE_MEMINFO Findme  ={NameBuf, NULL};
	  JPEG_LEAVE_MEMINFO *pFound = NULL;
	  HI_CHAR *pHead = NULL;
	  HI_CHAR *pTail = NULL;  	  

	  /**
	   **这个赋值要注意顺序，因为是二分查找
	   **/
	  JPEG_LEAVE_MEMINFO MemInfo[] =
							{	
								  {"Buffers",	   &MEMINFO_Buffers},
								  {"Cached",	   &MEMINFO_Cached},
								  {"MemFree",	   &MEMINFO_MemFree},
								  {"MemTotal",	   &MEMINFO_MemTotal}	  
							};
	   
	  const HI_U32 u32MemInfoCount = sizeof(MemInfo) / sizeof(JPEG_LEAVE_MEMINFO);

	  *pu64MemSize = MEMLEAVESIZE_DEFAULT;
	  /**=========================================================================
	                           read meminfo start 
	   ==========================================================================**/
	  
	  s32MemInfoFd = open(MEMINFO_FILE,O_RDONLY);
	  if(s32MemInfoFd < 0){
			JPEG_TRACE("open %s failure\n",MEMINFO_FILE);
	  		return HI_FAILURE;
	  }
	  
	  s32LeekOffset = lseek(s32MemInfoFd, 0L, SEEK_SET);
	  if(s32LeekOffset < 0){
			close(s32MemInfoFd);
			JPEG_TRACE("lseek %s failure\n",MEMINFO_FILE);
	  		return HI_FAILURE;
	  }
	  
	  s32ReadMemInfoSize = read(s32MemInfoFd, MemInfoBuf, (sizeof(MemInfoBuf) - 1));
	  if (s32ReadMemInfoSize <= 0 || s32ReadMemInfoSize > (HI_S32)(sizeof(MemInfoBuf) - 1)){
			close(s32MemInfoFd);
			JPEG_TRACE("read %s failure\n",MEMINFO_FILE);
	  		return HI_FAILURE;
	  }else{
	  		MemInfoBuf[s32ReadMemInfoSize] = '\0';
	  }

	  close(s32MemInfoFd);

	  /**=========================================================================
	          read meminfo end,the proc message in MemInfoBuf
	   ==========================================================================**/
	  pHead = MemInfoBuf;
	  for(;;){
		    pTail = strchr(pHead, ':');
		    if(!pTail) {
				break;
		    }
		    *pTail = '\0';

		    if(strlen(pHead) >= sizeof(NameBuf)){
		       pHead = pTail+1;
		       goto NextFind;
		    }

			strncpy(NameBuf, pHead, sizeof(NameBuf));
			NameBuf[sizeof(NameBuf) - 1] = '\0';

		    pFound = (JPEG_LEAVE_MEMINFO *)bsearch(&Findme,                     \
				                                   MemInfo,                     \
				                                   u32MemInfoCount,             \
				                                   sizeof(JPEG_LEAVE_MEMINFO),  \
				                                   compare_meminfo);
		    pHead = pTail + 1;
		    if(!pFound){
				goto NextFind;
		    }
			/**
			 **转成10进制
			 **/
		    *(pFound->pSize) = strtoul(pHead,&pTail,10);
			
			NextFind:
	    		pTail = strchr(pHead, '\n');
	    		if(!pTail){
					break;
	    		}
	   			pHead = pTail + 1;
		
	 }

	 *pu64MemSize = MEMINFO_MemFree;

#if 0
	 system("cat /proc/meminfo");
	 JPEG_TRACE("\n===================================================\n");
	 JPEG_TRACE("MEMINFO_MemTotal = %lld\n",MEMINFO_MemTotal);
	 JPEG_TRACE("MEMINFO_MemFree  = %lld\n",*pu64MemSize);
	 JPEG_TRACE("MEMINFO_Buffers  = %lld\n",MEMINFO_Buffers);
	 JPEG_TRACE("MEMINFO_Cached   = %lld\n",MEMINFO_Cached);
	 JPEG_TRACE("===================================================\n");
#endif

	 return HI_SUCCESS;
	 	
}
