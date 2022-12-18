/******************************************************************************
Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_debug.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2005/4/23
Last Modified :
Description   : Common debugging macro definition
Function List :
History       :
******************************************************************************/
#ifndef __HI_DEBUG_H__
#define __HI_DEBUG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"

//#undef HI_DEBUG
#define HI_DEBUG

#ifdef __OS_LINUX__
#ifdef __KERNEL__
    #define HI_PRINT printk
#else
#include <stdio.h>
    #define HI_PRINT printf
#endif /* end of __KERNEL__ */
#else  /* __OS_ECOS__ */
#define HI_PRINT printf
#endif /* end of __OS_LINUX__ */

/*************************** Structure Definition ****************************/
/** \addtogroup      related to debugging */
/** @{ */  /** <!-- 【Data structures related to debugging. CNcomment: 与调试相关的数据结构】 */

#ifdef __KERNEL__
#include <linux/module.h>
#include <linux/init.h>


    #define HI_PANIC printk
#else
    #define HI_PANIC printf
#endif

/**Default level of the output debugging information*/
/**CNcomment: 默认的调试信息输出级别*/
#define HI_LOG_LEVEL_DEFAULT HI_LOG_LEVEL_ERROR

/**Level of the output debugging information*/
/**CNcomment: 调试信息输出级别*/
typedef enum hiLOG_LEVEL_E
{
    HI_LOG_LEVEL_FATAL   = 0,     /**Fatal error. It indicates that a critical problem occurs in the system. Therefore, you must pay attention to it.*/
                                  /**<CNcomment: 致命错误, 此类错误需要特别关注，一般出现此类错误代表系统出现了重大问题 */
    HI_LOG_LEVEL_ERROR   = 1,     /**Major error. It indicates that a major problem occurs in the system and the system cannot run.*/
                                  /**<CNcomment: 一般错误, 一般出现此类错误代表系统出现了比较大的问题，不能再正常运行 */
    HI_LOG_LEVEL_WARNING = 2,     /**Warning. It indicates that a minor problem occurs in the system, but the system still can run properly.*/
                                  /**<CNcomment: 告警信息, 一般出现此类信息代表系统可能出现问题，但是还能继续运行 */
    HI_LOG_LEVEL_INFO    = 3,     /**Message. It is used to prompt users. Users can open the message when locating problems. It is recommended to disable this message in general.*/
                                  /**<CNcomment: 提示信息, 一般是为提醒用户而输出，在定位问题的时候可以打开，一般情况下建议关闭 */
    HI_LOG_LEVEL_BUTT
} HI_LOG_LEVEL_E;

/**ID of the module to be debugged*/
/**CNcomment: 调试模块ID*/
typedef enum hiDEBUG_MOD_ID_E
{
    HI_DEBUG_ID_COMMON  = 0,
    HI_DEBUG_ID_DEMUX   = 1,
    HI_DEBUG_ID_ADEC    = 2,
    HI_DEBUG_ID_AENC    = 3,
    HI_DEBUG_ID_AO      = 4,
    HI_DEBUG_ID_AI      = 5,
    HI_DEBUG_ID_VDEC    = 6,
    HI_DEBUG_ID_VENC    = 7,
    HI_DEBUG_ID_VO      = 8,
    HI_DEBUG_ID_VI      = 9,
    HI_DEBUG_ID_DISP    = 10,
    HI_DEBUG_ID_PNG     = 11,
    HI_DEBUG_ID_FB      = 12,
    HI_DEBUG_ID_FIRMWARE= 13,
    HI_DEBUG_ID_VP      = 14,
    HI_DEBUG_ID_AVPLAY  = 15,
    HI_DEBUG_ID_PVR     = 16,
    HI_DEBUG_ID_SYNC    = 17,
    HI_DEBUG_ID_VSYNC   = 18,
    HI_DEBUG_ID_ASYNC   = 19,
	HI_DEBUG_ID_SIO     = 20,
	HI_DEBUG_ID_SIO_AI  = 21,
	HI_DEBUG_ID_SIO_AO  = 22,
		HI_DEBUG_ID_HDMI    = 23,

    /*  ECS     */
    HI_DEBUG_ID_ECS     = 24,
    HI_DEBUG_ID_TUNER   = 25,
	HI_DEBUG_ID_CA   	= 26,
	HI_DEBUG_ID_C51   	= 27,

    HME_LOG_API         = 28,
    HME_LOG_ENGINE      = 29,

    HI_DEBUG_ID_DEBUG   = 30,  /* !!! MAX num of debug ID, don't change */
    HI_DEBUG_ID_USR     = 31,

    HI_DEBUG_ID_SUBT    = 32,
    HI_DEBUG_ID_TTX     = 33,

    HI_DEBUG_ID_BUTT
} HI_DEBUG_MOD_ID_E;

/** Used for HI_TRACE */
extern HI_VOID HI_LogOut(HI_U32 u32Level, HI_DEBUG_MOD_ID_E enModId,
            HI_U8 *pFuncName, HI_U32 u32LineNum, const char *format, ...);

#define PRINT_FMT ("[%d %s-%s]:%s[%d]:%s", TimeMs, DebugLevelName[u32Level],\
                g_pLogConfigInfo[enModId].ModName,\
                pFuncName, u32LineNum, log_str)

#ifdef HI_DEBUG
#define HI_TRACE(level, module_id, fmt...)                      \
    do{                                                         \
        HI_LogOut(level,module_id,(HI_U8*)__FUNCTION__,__LINE__,fmt);  \
    }while(0)

#define HI_ASSERT(expr)                                     \
    do{                                                     \
        if (!(expr)) {                                      \
            HI_PANIC("\nASSERT failed at:\n  >File name: %s\n  >Function : %s\n  >Line No. : %d\n  >Condition: %s\n", \
		__FILE__,__FUNCTION__, __LINE__, #expr);    \
        }                                                   \
    }while(0)


#define HI_ASSERT_RET(expr)                                     \
    do{                                                         \
        if (!(expr)) {                                          \
            HI_PRINT("\n<%s %d>: ASSERT Failure{" #expr "}\n",  \
                          __FUNCTION__, __LINE__);              \
            return HI_FAILURE;                                  \
        }                                                       \
    }while(0)

#define HI_DEBUG_LOG(fmt...) \
            HI_TRACE(HI_LOG_LEVEL_INFO, HI_DEBUG_ID_DEBUG, fmt)

/** @} */  /** <!-- ==== Structure Definition End ==== */

#else
#define HI_TRACE(level, module_id, fmt...)
#define HI_ASSERT(expr)
#define HI_ASSERT_RET(expr)
#define HI_DEBUG_LOG(fmt...)
#endif

#define MKSTR(exp) # exp
#define MKMARCOTOSTR(exp) MKSTR(exp)
#define VERSION_STRING ("SDK_VERSION:["MKMARCOTOSTR(SDK_VERSION)"] Build Time:["__DATE__", "__TIME__"]")

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_DEBUG_H__ */
