/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name	    : hi_gfx_comm_k.h
Version		    : version 1.0
Author		    : 
Created		    : 2015/03/01
Description	    : Describes adp file. CNcomment:驱动跨平台适配 CNend\n
Function List 	: 

History       	:
Date				Author        		Modification
2015/03/01		    y00181162  		    
******************************************************************************/


#ifndef  _HI_GFX_COMM_K_H_
#define  _HI_GFX_COMM_K_H_


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */


/***************************** SDK Version Macro Definition *********************/

/** \addtogroup 	GFX COMM */
/** @{ */  /** <!-- 【GFX COMM】 */


/** @} */	/*! <!-- Macro Definition end */


/*********************************add include here******************************/

#include "hi_type.h"

#include <linux/version.h>
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36))
#include <linux/smp_lock.h>
#endif
#if defined(CONFIG_GFX_STB_SDK) || defined(CONFIG_GFX_ANDROID_SDK) || defined(CONFIG_GFX_TV_SDK)
#include "hi_debug.h"
#include "hi_module.h"
#include "hi_drv_module.h"
	#if   defined(CHIP_TYPE_hi3712)       \
	   || defined(CHIP_TYPE_hi3716m)      \
	   || defined(CHIP_TYPE_hi3716mv310)  \
	   || defined(CHIP_TYPE_hi3110ev500)  \
       || defined(CHIP_TYPE_hi3716mv320)
		#include "drv_dev_ext.h"
	#else
		#include "hi_drv_dev.h"
	#endif
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"
#include "drv_disp_ext.h"
#include "hi_drv_proc.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_sys.h"
#include "hi_reg_common.h"
#elif defined(CONFIG_GFX_BVT_SDK)
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include "proc_ext.h"
#include "hi_debug.h"
#include "mm_ext.h"
#include "media-mem.h"
#endif



/***************************** Macro Definition ******************************/

/** \addtogroup 	GFX COMM */
/** @{ */  /** <!-- 【GFX COMM】 */

/** this macro define at CFG_HI_KMOD_CFLAGS,so Makefile should include CFG_HI_KMOD_CFLAGS **/
#ifdef HI_ADVCA_FUNCTION_RELEASE
#define  CONFIG_GFX_ADVCA_RELEASE
#endif


#ifdef CONFIG_GFX_ADVCA_RELEASE
/** char disable */
/** CNcomment:char使能 CNend */
#define  CONFIG_GFX_COMM_STR_DISABLE
/** PROC disable */
/** CNcomment:proc使能 CNend */
#define  CONFIG_GFX_COMM_PROC_DISABLE
/** version info disable */
/** CNcomment:版本信息使能 CNend */
#define  CONFIG_GFX_COMM_VERSION_DISABLE
#endif

#ifdef CONFIG_GFX_BVT_SDK
#define  CONFIG_GFX_COMM_PROC_DISABLE
#endif
/** close the string function */
/** CNcomment:关闭字符串功能,DEBUG必须关闭 CNend */
#ifdef   CONFIG_GFX_COMM_STR_DISABLE
/** LOG disable */
/** CNcomment:log使能 CNend */
#define  CONFIG_GFX_COMM_DEBUG_DISABLE
#endif

/** pm disable */
/** CNcomment:pm使能 CNend */
//#define  CONFIG_GFX_COMM_PM_DISABLE


/** register mammap operate */
/** CNcomment:寄存器映射操作 CNend */
#define HI_GFX_REG_MAP(base, size)                    ioremap_nocache((base), (size))
/** register unmap operate */
/** CNcomment:寄存器逆映射操作 CNend */
#define HI_GFX_REG_UNMAP(base) 	                    iounmap((HI_VOID*)(base))


#ifdef CONFIG_GFX_256BYTE_ALIGN   /** 定义到Makefile和Android Makefile中 **/
#define GFX_MMZ_ALIGN_BYTES     256
#else
#define GFX_MMZ_ALIGN_BYTES     16
#endif


#ifdef CONFIG_GFX_COMM_STR_DISABLE
	#define SEQ_Printf(fmt...)                        {do{}while(0);}
	#define GFX_Printk(fmt...)                        {do{}while(0);}
#else 
	#define SEQ_Printf                                  PROC_PRINT
	#ifndef CONFIG_GFX_BVT_SDK
	  #define GFX_Printk                                  HI_PRINT
	#else
	  #define GFX_Printk                                  printk
	#endif
#endif 


/** the mutex init */
/** CNcomment:信号量初始化 CNend */
#define HI_GFX_INIT_MUTEX(x)                           sema_init(x, 1)

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36))
    #define HI_GFX_DECLARE_MUTEX(x)                        DECLARE_MUTEX(x)
#else
    #define HI_GFX_DECLARE_MUTEX(x)                        DEFINE_SEMAPHORE(x)
#endif


#if defined(CONFIG_GFX_STB_SDK) || defined(CONFIG_GFX_ANDROID_SDK) || defined(CONFIG_GFX_TV_SDK)
	/** kmalloc mem */
	/** CNcomment:内核分配内存 CNend */
	#define HI_GFX_KMALLOC(module_id, size, flags)      HI_KMALLOC(ConvertID(module_id), size, flags)
	/** kfree mem */
	/** CNcomment:内核释放内存 */
	#define HI_GFX_KFREE(module_id, addr)                HI_KFREE(ConvertID(module_id), addr)
	#define HI_GFX_VMALLOC(module_id, size)              HI_VMALLOC(ConvertID(module_id), size)
	#define HI_GFX_VFREE(module_id, addr)                HI_VFREE(ConvertID(module_id), addr)
    #define ConvertID(module_id) (module_id + HI_ID_TDE - HIGFX_TDE_ID)
    
	#ifdef CONFIG_GFX_COMM_DEBUG_DISABLE
	    #define HI_GFX_COMM_LOG_FATAL(module_id,fmt...)    
	    #define HI_GFX_COMM_LOG_ERROR(module_id,fmt...)    
	    #define HI_GFX_COMM_LOG_WARNING(module_id,fmt...)  
	    #define HI_GFX_COMM_LOG_INFO(module_id,fmt...)     
	#else 
	    #define HI_GFX_COMM_LOG_FATAL(module_id, fmt...)   HI_FATAL_PRINT(ConvertID(module_id), fmt)
	    #define HI_GFX_COMM_LOG_ERROR(module_id,fmt...)    HI_ERR_PRINT(ConvertID(module_id), fmt)
	    #define HI_GFX_COMM_LOG_WARNING(module_id,fmt...)  HI_WARN_PRINT(ConvertID(module_id), fmt)
	    #define HI_GFX_COMM_LOG_INFO(module_id,fmt...)     HI_INFO_PRINT(ConvertID(module_id), fmt)
	#endif 

	#ifndef CONFIG_GFX_COMM_PM_DISABLE
	#ifdef CONFIG_COMPAT
    	#define DECLARE_GFX_NODE(gfx_name,gfx_open, gfx_release, gfx_mmap, gfx_ioctl, gfx_suspend, gfx_resume) \
        static struct file_operations gfx_fops =\
        {\
            .owner   = THIS_MODULE,      \
            .unlocked_ioctl = gfx_ioctl,\
            .compat_ioctl = gfx_ioctl,\
            .open    = gfx_open,        \
            .release = gfx_release,     \
            .mmap	 = gfx_mmap         \
        };\
        static PM_BASEOPS_S gfx_drvops = \
        {\
            .suspend      = gfx_suspend,\
            .resume       = gfx_resume  \
        };\
        static PM_DEVICE_S gfx_dev = \
        {\
            .name  = gfx_name,            \
            .minor = HIMEDIA_DYNAMIC_MINOR,\
            .owner = THIS_MODULE,          \
            .app_ops = &gfx_fops,          \
            .base_ops = &gfx_drvops        \
        }
	#else
		#define DECLARE_GFX_NODE(gfx_name,gfx_open, gfx_release, gfx_mmap, gfx_ioctl, gfx_suspend, gfx_resume) \
        static struct file_operations gfx_fops =\
        {\
            .owner   = THIS_MODULE,      \
            .unlocked_ioctl = gfx_ioctl,\
            .open    = gfx_open,        \
            .release = gfx_release,     \
            .mmap	 = gfx_mmap         \
        };\
        static PM_BASEOPS_S gfx_drvops = \
        {\
            .suspend      = gfx_suspend,\
            .resume       = gfx_resume  \
        };\
        static PM_DEVICE_S gfx_dev = \
        {\
            .name  = gfx_name,            \
            .minor = HIMEDIA_DYNAMIC_MINOR,\
            .owner = THIS_MODULE,          \
            .app_ops = &gfx_fops,          \
            .base_ops = &gfx_drvops        \
        }
	#endif	/*CONFIG_COMPAT*/
    #else
        #define DECLARE_GFX_NODE(gfx_name, gfx_open, gfx_release, gfx_mmap, gfx_ioctl, gfx_suspend, gfx_resume)  \
        static struct file_operations gfx_fops =\
        {\
            .owner   = THIS_MODULE,       \
            .unlocked_ioctl = gfx_ioctl, \
            .open    = gfx_open,         \
            .release = gfx_release,      \
            .mmap	 = gfx_mmap          \
        };\
        static PM_BASEOPS_S gfx_drvops = \
        {\
            .suspend      = gfx_suspend,\
            .resume       = gfx_resume  \
        };\
        static PM_DEVICE_S gfx_dev = \
        {\
            .name  = gfx_name,            \
            .minor = HIMEDIA_DYNAMIC_MINOR,\
            .owner = THIS_MODULE,          \
            .app_ops = &gfx_fops           \
        }
 	#endif  /*CONFIG_GFX_COMM_PM_DISABLE*/

	#define GFX_MMZ_BUFFER_S     MMZ_BUFFER_S
	
#elif defined(CONFIG_GFX_BVT_SDK)
	/** kmalloc mem */
	/** CNcomment:内核分配内存 CNend */
   	#define HI_GFX_KMALLOC(module_id, size, flags)       kmalloc(size, flags)
    #define HI_GFX_KFREE(module_id, addr)                 kfree(addr)
    #define HI_GFX_VMALLOC(module_id, size)               vmalloc(size)
    #define HI_GFX_VFREE(module_id, addr)                 vfree(addr)
    #define MMB_ADDR_INVALID (~0)
    #define PROC_PRINT(arg...) seq_printf(arg)

	/** kfree mem */
	/** CNcomment:内核释放内存 CNend */
	#define ConvertID(module_id) (module_id + HI_ID_TDE - HIGFX_TDE_ID)
	
	#ifdef CONFIG_GFX_COMM_DEBUG_DISABLE
	    #define HI_GFX_COMM_LOG_FATAL(module_id,fmt...)    
	    #define HI_GFX_COMM_LOG_ERROR(module_id,fmt...)    
	    #define HI_GFX_COMM_LOG_WARNING(module_id,fmt...)  
	    #define HI_GFX_COMM_LOG_INFO(module_id,fmt...)     

	#else 
	    #define HI_GFX_COMM_LOG_FATAL(module_id, fmt...)   HI_TRACE(HI_DBG_ERR,    ConvertID(module_id), fmt)
	    #define HI_GFX_COMM_LOG_ERROR(module_id,fmt...)    HI_TRACE(HI_DBG_WARN,    ConvertID(module_id), fmt)
	    #define HI_GFX_COMM_LOG_WARNING(module_id,fmt...)  HI_TRACE(HI_DBG_NOTICE,  ConvertID(module_id), fmt)
	    #define HI_GFX_COMM_LOG_INFO(module_id,fmt...)     HI_TRACE(HI_DBG_INFO,     ConvertID(module_id), fmt)
        #endif

	#define DECLARE_GFX_NODE(gfx_name,gfx_open, gfx_release, gfx_mmap, gfx_ioctl, gfx_suspend, gfx_resume) \
    struct file_operations gfx_fops =\
    {\
        .owner   = THIS_MODULE,      \
        .unlocked_ioctl = gfx_ioctl,\
        .open    = gfx_open,        \
        .release = gfx_release,     \
        .mmap	 = gfx_mmap         \
    };\
     struct miscdevice gfx_dev =\
    {\
        MISC_DYNAMIC_MINOR,\
        gfx_name,         \
        &gfx_fops          \
    }
	#define MKSTR(exp) # exp
	#define MKMARCOTOSTR(exp) MKSTR(exp)
#else

#endif


/** @} */	/*! <!-- Macro Definition end */


/*************************** Enum Definition ****************************/

/** \addtogroup 	 GFX COMM */
/** @{ */  /** <!-- 【GFX COMM】 */


/** enum of the chip type */
/** CNcomment:芯片类型枚举 CNend */
typedef enum tagHIGFX_CHIP_TYPE_E
{
    HIGFX_CHIP_TYPE_HI3716MV100 = 0,   /**< HI3716MV100 */
    HIGFX_CHIP_TYPE_HI3716MV200,       /**< HI3716MV200 */
    HIGFX_CHIP_TYPE_HI3716MV300,       /**< HI3716MV300 */
    HIGFX_CHIP_TYPE_HI3716H,           /**< HI3716H     */
    HIGFX_CHIP_TYPE_HI3716CV100,       /**< HI3716C     */

    HIGFX_CHIP_TYPE_HI3720,            /**< HI3720       */
    HIGFX_CHIP_TYPE_HI3712V300,        /**< X6V300       */
    HIGFX_CHIP_TYPE_HI3715,            /**< HI3715       */

    HIGFX_CHIP_TYPE_HI3716CV200ES,     /**< S40V200      */
    HIGFX_CHIP_TYPE_HI3716CV200,       /**< HI3716CV200  */    
    HIGFX_CHIP_TYPE_HI3719MV100,       /**< HI3719MV100  */
    HIGFX_CHIP_TYPE_HI3718CV100,        /**<HI3718CV100 */
    HIGFX_CHIP_TYPE_HI3719CV100,        /**<HI3719CV100 */
    HIGFX_CHIP_TYPE_HI3719MV100_A,      /**<HI3719MV100_A */
    HIGFX_CHIP_TYPE_HI3716MV400, 	/*< HI3716MV400*/

    HIGFX_CHIP_TYPE_HI3531      = 100, /**< HI3531       */
    HIGFX_CHIP_TYPE_HI3521,            /**< HI3521       */
    HIGFX_CHIP_TYPE_HI3518,            /**< HI3518       */
    HIGFX_CHIP_TYPE_HI3520A,           /**< HI3520A      */
    HIGFX_CHIP_TYPE_HI3520D,           /**< HI3520D      */
    HIGFX_CHIP_TYPE_HI3535,            /**< HI3535       */

    HIGFX_CHIP_TYPE_BUTT        = 400  /**< Invalid Chip */
    
}HIGFX_CHIP_TYPE_E;


/** enum of the module ID */
/** CNcomment:每个模块的ID号 CNend */
typedef enum tagHIGFX_MODE_ID_E
{

	HIGFX_TDE_ID      = 0,    /**< TDE ID         */
	HIGFX_JPGDEC_ID,          /**< JPEG DECODE ID */
	HIGFX_JPGENC_ID,          /**< JPEG_ENCODE ID */
	HIGFX_FB_ID,              /**<  FRAMEBUFFER ID */
	HIGFX_PNG_ID,             /**< PNG ID          */
	HIGFX_HIGO_ID,
	HIGFX_GFX2D_ID,
	HIGFX_BUTT_ID,
	
}HIGFX_MODE_ID_E;


/** @} */  /*! <!-- enum Definition end */

/*************************** Structure Definition ****************************/


/** \addtogroup 	 GFX COMM */
/** @{ */  /** <!-- 【GFX COMM】 */


/** Structure of proc item */
/** CNcomment:proc相关函数操作 CNend */
typedef struct struGFX_PROC_ITEM
{
	HI_S32 (*fnRead)(struct seq_file *, HI_VOID *);
	HI_S32 (*fnWrite)(struct file * file,  const char __user * buf, size_t count, loff_t *ppos);
	HI_S32 (*fnIoctl)(struct seq_file *, HI_U32 cmd, HI_U32 arg);
}GFX_PROC_ITEM_S;


/** @} */  /*! <!-- Structure Definition end */


/********************** Global Variable declaration **************************/

extern unsigned long long sched_clock(void);

/******************************* API declaration *****************************/

/** \addtogroup 	 GFX COMM */
/** @{ */  /** <!-- 【GFX COMM】 */

/** 
\brief get time function. CNcomment:获取时间函数 CNend\n
\attention \n

\param[in]	ModID. CNcomment:模块ID CNend\n

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_GFX_GetTimeStamp
*/
static inline HI_S32 HI_GFX_GetTimeStamp(HI_U32 *pu32TimeMs, HI_U32 *pu32TimeUs)
{
	HI_U64 u64TimeNow;
    HI_U64 ns;

    if(HI_NULL == pu32TimeMs)
	{
		return HI_FAILURE;
	}

	u64TimeNow = sched_clock();

	*pu32TimeMs = (HI_U32)iter_div_u64_rem(u64TimeNow,1000000,&ns);
	
	return HI_SUCCESS;
}


#if defined(CONFIG_GFX_STB_SDK) || defined(CONFIG_GFX_ANDROID_SDK) || defined(CONFIG_GFX_TV_SDK)
    
/** 
\brief free the mem that has alloced. CNcomment:释放分配过的内存 CNend
\attention \n

\param[in]	u32Phyaddr. CNcomment:物理地址 CNend\n

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_GFX_FreeMem
*/
static inline HI_VOID HI_GFX_FreeMem(HI_U32 u32Phyaddr)
{
        MMZ_BUFFER_S stBuffer;                             
        stBuffer.u32StartPhyAddr = u32Phyaddr;               
        HI_DRV_MMZ_Release(&stBuffer);                    
}


/** 
\brief alloc the mem that need. CNcomment:分配需要的内存 CNend\n
\attention \n

\param[in]	pName.        CNcomment:模块名   CNend\n
\param[in]	pZoneName.
\param[in]	u32LayerSize. CNcomment:内存大小 CNend\n

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_GFX_AllocMem
*/
static inline HI_U32 HI_GFX_AllocMem(HI_CHAR *pName, HI_CHAR* pZoneName, HI_U32 u32LayerSize)
{

	    int addr;
	    MMZ_BUFFER_S stBuffer; 
	    
	    if ((u32LayerSize == 0) || (u32LayerSize > 0x40000000))
	    {
	        return 0;
	    }
	    /* three time mem mangent*/
	    if(HI_SUCCESS == HI_DRV_MMZ_Alloc(pName, pZoneName, u32LayerSize, GFX_MMZ_ALIGN_BYTES, &stBuffer))   
	    {            
	        addr = stBuffer.u32StartPhyAddr;                   
	    }                                                          
	    else if(HI_SUCCESS == HI_DRV_MMZ_Alloc(pName, "graphics", u32LayerSize, GFX_MMZ_ALIGN_BYTES, &stBuffer))   
	    {          
	        addr = stBuffer.u32StartPhyAddr;                                          
	    }  
	    else if(HI_SUCCESS == HI_DRV_MMZ_Alloc(pName, NULL, u32LayerSize, GFX_MMZ_ALIGN_BYTES, &stBuffer))   
	    {
	        addr = stBuffer.u32StartPhyAddr;                                          
	    }
	    else
		{
	        addr = 0;   
		}
		return addr;
	
}


static inline HI_VOID *HI_GFX_Map(HI_U32 u32PhyAddr,HI_U32 size)
{    

	    MMZ_BUFFER_S stBuffer;

	    stBuffer.u32StartPhyAddr = u32PhyAddr;
	    if(HI_SUCCESS == HI_DRV_MMZ_Map(&stBuffer))        
	     {                                                   
	         return ((unsigned char *)stBuffer.u32StartVirAddr);            
	     }                                                   
	     else                                                
	     {                                                   
	         return HI_NULL;
	     } 
}

static inline HI_VOID *HI_GFX_MapCached(HI_U32 u32PhyAddr,HI_U32 size)
{   

	    GFX_MMZ_BUFFER_S stBuffer;
	    stBuffer.u32StartPhyAddr = u32PhyAddr;
	    if(HI_SUCCESS == HI_DRV_MMZ_MapCache(&stBuffer))
	    {                                                   
	        return ((unsigned char *)stBuffer.u32StartVirAddr);            
	    }                                                   
	    else                                                
	    {                                                   
	        return HI_NULL;
	    }  
}

static inline HI_VOID HI_GFX_Flush(GFX_MMZ_BUFFER_S *stFlushBuf)
{   
    HI_DRV_MMZ_Flush(stFlushBuf);
}

static inline HI_S32 HI_GFX_Unmap(HI_VOID *pViraddr)
{

    GFX_MMZ_BUFFER_S stBuffer;                             
    stBuffer.u32StartVirAddr = (unsigned long)pViraddr;              
    HI_DRV_MMZ_Unmap(&stBuffer);                  

    return HI_SUCCESS;
	
}


static inline HI_S32 HI_GFX_PROC_AddModule(HI_CHAR * pEntry_name, GFX_PROC_ITEM_S* pProcItem, HI_VOID *pData)
{
    #ifndef  CONFIG_GFX_COMM_PROC_DISABLE
		DRV_PROC_EX_S stProcItem;
		stProcItem.fnIoctl =  pProcItem->fnIoctl;
		stProcItem.fnRead = pProcItem->fnRead;
		stProcItem.fnWrite= pProcItem->fnWrite;
		HI_DRV_PROC_AddModule(pEntry_name, &stProcItem, pData);
    #endif
	return 0;
	
}

static inline HI_VOID HI_GFX_PROC_RemoveModule(HI_CHAR *pEntry_name)
{
    #ifndef  CONFIG_GFX_COMM_PROC_DISABLE
	  HI_DRV_PROC_RemoveModule(pEntry_name);
    #endif
}

static inline HI_S32 HI_GFX_MODULE_Register(HI_U32 u32ModuleID, const HI_CHAR * pszModuleName, HI_VOID *pData)
{
	return HI_DRV_MODULE_Register(ConvertID(u32ModuleID), pszModuleName, pData);
}

static inline HI_S32 HI_GFX_MODULE_UnRegister(HI_U32 u32ModuleID)
{
	return HI_DRV_MODULE_UnRegister(ConvertID(u32ModuleID));
}

#define HI_GFX_PM_Register()  HI_DRV_PM_Register(&gfx_dev);

#define HI_GFX_PM_UnRegister()  HI_DRV_PM_UnRegister(&gfx_dev);

static inline HI_VOID HI_GFX_SYS_GetChipVersion(HIGFX_CHIP_TYPE_E *penChipType)
{
#if !defined(CHIP_TYPE_hi3712)     \
 && !defined(CHIP_TYPE_hi3716m)    \
 && !defined(CHIP_TYPE_hi3716mv310)\
 && !defined(CHIP_TYPE_hi3110ev500)\
 && !defined(CHIP_TYPE_hi3716mv320)
    HI_CHIP_TYPE_E    ChipType = HI_CHIP_TYPE_BUTT;
    HI_CHIP_VERSION_E ChipVersion = HI_CHIP_VERSION_BUTT;

    HI_DRV_SYS_GetChipVersion(&ChipType, &ChipVersion);
    
    if ((HI_CHIP_TYPE_HI3716M == ChipType) && (ChipVersion == HI_CHIP_VERSION_V100))
    {
        *penChipType = HIGFX_CHIP_TYPE_HI3716MV100;
		return;
    }
    if ((HI_CHIP_TYPE_HI3716M == ChipType) && (ChipVersion == HI_CHIP_VERSION_V200))
	{
        *penChipType = HIGFX_CHIP_TYPE_HI3716MV200;
		return;
    }
    if ((HI_CHIP_TYPE_HI3716M == ChipType) && (ChipVersion == HI_CHIP_VERSION_V300))
	{
        *penChipType = HIGFX_CHIP_TYPE_HI3716MV300;
		return;
    }
    if (HI_CHIP_TYPE_HI3716H == ChipType)
	{
        *penChipType = HIGFX_CHIP_TYPE_HI3716H;
		return;
    }
    if ((HI_CHIP_TYPE_HI3716C == ChipType) && (ChipVersion == HI_CHIP_VERSION_V100))
    {
        *penChipType = HIGFX_CHIP_TYPE_HI3716CV100;
		return;
    }
   if (HI_CHIP_TYPE_HI3720 == ChipType)
   {
        *penChipType = HIGFX_CHIP_TYPE_HI3720;
		return;
   	}
   if ((HI_CHIP_TYPE_HI3712 == ChipType) && (ChipVersion == HI_CHIP_VERSION_V300))
   {
        *penChipType = HIGFX_CHIP_TYPE_HI3712V300;
		return;
   }
   if (HI_CHIP_TYPE_HI3715 == ChipType)
   {
        *penChipType = HIGFX_CHIP_TYPE_HI3715;
		return;
   }
   if ((HI_CHIP_TYPE_HI3716CES == ChipType) && (HI_CHIP_VERSION_V200 == ChipVersion))
   {
        *penChipType = HIGFX_CHIP_TYPE_HI3716CV200ES;
		return;
   }
   if ((HI_CHIP_TYPE_HI3716C == ChipType) && (ChipVersion == HI_CHIP_VERSION_V200))
   {
        *penChipType = HIGFX_CHIP_TYPE_HI3716CV200;
		return;
   	}
    if ((HI_CHIP_TYPE_HI3718C == ChipType) && (ChipVersion == HI_CHIP_VERSION_V100))
    {
        *penChipType = HIGFX_CHIP_TYPE_HI3718CV100;
        return;
    }
    if ((HI_CHIP_TYPE_HI3719C == ChipType) && (ChipVersion == HI_CHIP_VERSION_V100))
    {
        *penChipType = HIGFX_CHIP_TYPE_HI3719CV100;
        return;
    }
    if ((HI_CHIP_TYPE_HI3719M_A == ChipType) && (ChipVersion == HI_CHIP_VERSION_V100))
    {
        *penChipType = HIGFX_CHIP_TYPE_HI3719MV100_A;
        return;
    }
    if ((HI_CHIP_TYPE_HI3716M == ChipType) && (ChipVersion == HI_CHIP_VERSION_V400))
    {
 		*penChipType = HIGFX_CHIP_TYPE_HI3716MV400;
        return;
    }
#endif
}


#elif defined(CONFIG_GFX_BVT_SDK) 


typedef struct struGFX_MMZ_BUFFER
{
    HI_U32 u32StartVirAddr;
    HI_U32 u32StartPhyAddr;
    HI_U32 u32Size;
}GFX_MMZ_BUFFER_S;


/** 
\brief free the mem that has alloced. CNcomment:释放分配过的内存 CNend\n
\attention \n

\param[in]	u32Phyaddr. CNcomment:物理地址 CNend\n

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_GFX_FreeMem
*/
static inline HI_VOID HI_GFX_FreeMem(HI_U32 u32Phyaddr)
{
    if(MMB_ADDR_INVALID != u32Phyaddr)
    {
        CMPI_MmzFree(u32Phyaddr);
    }
}

/** 
\brief alloc the mem that need. CNcomment:分配需要的内存 CNend\n
\attention \n

\param[in]	pName.        CNcomment:模块名   CNend\n
\param[in]	pZoneName.
\param[in]	u32LayerSize. CNcomment:内存大小 CNend\n

\retval ::HI_SUCCESS
\retval ::HI_FAILURE

\see \n
::HI_GFX_AllocMem
*/
static inline HI_U32 HI_GFX_AllocMem(HI_CHAR *pName, HI_CHAR* pZoneName, HI_U32 u32LayerSize)
{
    HI_U32 phyaddr = 0;
    phyaddr = CMPI_MmzMalloc(pZoneName,pName, u32LayerSize);
    if (MMB_ADDR_INVALID == phyaddr && NULL != pZoneName)
    {
        phyaddr = CMPI_MmzMalloc(NULL,pName, u32LayerSize);
    }
    if(MMB_ADDR_INVALID == phyaddr)
    {
        phyaddr = 0; 
    }
    if(0==phyaddr)
    {
        printk("MMZ malloc failed!!\n");
    }
     return phyaddr;
}

static inline HI_VOID *HI_GFX_Map(HI_U32 u32PhyAddr,HI_U32 size)
{  
    HI_VOID* virtaddr;
    virtaddr = CMPI_Remap_Nocache(u32PhyAddr,size);
    if(0 == virtaddr)
    {
        HI_GFX_FreeMem(u32PhyAddr); 
        return NULL;
    }
    return virtaddr;
}

static inline HI_VOID *HI_GFX_MapCached(HI_U32 u32PhyAddr,HI_U32 size)
{   
    HI_VOID* virtaddr;
    virtaddr = CMPI_Remap_Cached(u32PhyAddr,size);
    if(0 == virtaddr)
    {
        HI_GFX_FreeMem(u32PhyAddr); 
        return NULL;
    }
    return virtaddr;
}

static inline HI_VOID HI_GFX_Flush(GFX_MMZ_BUFFER_S *stFlushBuf)
{
    HI_VOID *virtaddr;
    HI_U32 phyaddr;
    HI_U32 len;
    virtaddr = (HI_VOID *)stFlushBuf->u32StartVirAddr;
    phyaddr = stFlushBuf->u32StartPhyAddr;
    len = stFlushBuf->u32Size;
    hil_mmb_flush_dcache_byaddr(virtaddr,phyaddr,len);
}

static inline HI_S32 HI_GFX_Unmap(HI_VOID *pViraddr)
{
    iounmap(pViraddr);
    return HI_SUCCESS;
}

static inline HI_S32 HI_GFX_PROC_AddModule(HI_CHAR * pEntry_name, GFX_PROC_ITEM_S* pProcItem, HI_VOID *pData)
{
    #ifndef  CONFIG_GFX_COMM_PROC_DISABLE
	    CMPI_PROC_ITEM_S stProcItem;
	    CMPI_PROC_ITEM_S* pstProcItem;
	    stProcItem.entry = NULL;
	    stProcItem.pData = NULL;
	    stProcItem.read = pProcItem->fnRead;
	    stProcItem.write = pProcItem->fnWrite;
	    pstProcItem = CMPI_CreateProc(pEntry_name,stProcItem.read, NULL);
    #endif
	
    return HI_SUCCESS;
	
}

static inline HI_VOID HI_GFX_PROC_RemoveModule(HI_CHAR *pEntry_name)
{
    #ifndef  CONFIG_GFX_COMM_PROC_DISABLE
	  CMPI_RemoveProc(pEntry_name);
    #endif
}

#define HI_GFX_MODULE_Register(u32ModuleID,pszModuleName,pData) misc_register(&gfx_dev);


#define HI_GFX_MODULE_UnRegister(u32ModuleID) misc_deregister(&gfx_dev);

#define HI_GFX_PM_Register()    misc_register(&gfx_dev);
#define HI_GFX_PM_UnRegister()  misc_deregister(&gfx_dev);

static inline HI_VOID HI_GFX_SYS_GetChipVersion(HIGFX_CHIP_TYPE_E *penChipType)
{
    *penChipType = HIGFX_CHIP_TYPE_HI3535;
}
#else


#endif

/** @} */  /*! <!-- API declaration end */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */
#endif /*_HI_GFX_COMM_K_H_ */
