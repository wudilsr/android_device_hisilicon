/**
* @file tee_log.h
*
* Copyright(C), 2008-2013, Hisilicon Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：安全服务调试log函数定义\n
*/

/** @defgroup grp_log_api 安全服务调试
* @ingroup TEE_API
*/
#ifndef __TEE_LOG_H
#define __TEE_LOG_H

#include "tee_internal_api.h"

extern void uart_printf_func(const char *fmt, ...);

#define DEBUG_TAG "[debug]"
#define WARNING_TAG "[warning]"
#define ERROR_TAG "[error]"
#define INFO_TAG "[info]"

#define LEVEL_DEBUG   2
#define LEVEL_WARNING   1
#define LEVEL_ERROR    0


/* in debug version users can dynamically modify the loglevel ,in release version, users have to modify the level by compile */
#ifndef DEBUG_VERSION

//#define TA_DEBUG
#ifdef TA_DEBUG
#define ta_debug(fmt, args...) uart_printf_func("%s %s: " fmt "", DEBUG_TAG,__FUNCTION__, ## args)
#else
#define ta_debug(fmt, args...)
#endif

#else

#define ta_debug(fmt, args...) \
    do {\
        uint32_t level;\
        level = get_value();\
        if(level>=LEVEL_DEBUG){\
           uart_printf_func("%s %s: " fmt "", DEBUG_TAG,__FUNCTION__, ## args); \
        }\
    } while (0)

#define ta_warning(fmt, args...)\
    do {\
        uint32_t level;\
        level = get_value();\
        if(level>=LEVEL_WARNING){\
            uart_printf_func("%s %s: " fmt "", DEBUG_TAG,__FUNCTION__, ## args); \
        }\
    } while (0)

#endif

#define ta_info(fmt, args...) uart_printf_func("%s %s: " fmt "", INFO_TAG,__FUNCTION__, ## args)
#define ta_error(fmt, args...) uart_printf_func("%s %s: " fmt " ", ERROR_TAG,__FUNCTION__, ## args)
#define TA_LOG
#ifdef TA_LOG
/**
 * @ingroup grp_log_api
 * 日志的级别Trace
 */
#define TRACE "[Trace]"
/**
 * @ingroup grp_log_api
 * 日志的级别Warning
 */
#define WARNING "[Warning]"
/**
 * @ingroup grp_log_api
 * 日志的级别Error
 */
#define ERROR "[Error]"

/**
 * @ingroup grp_log_api
 * 打印Trace日志的接口
 */
#define SLogTrace(fmt, args...) SLog("%s %s: " fmt "\n", TRACE, __FUNCTION__, ## args)
/**
 * @ingroup grp_log_api
 * 打印Warning日志的接口
 */
#define SLogWarning(fmt, args...) SLog("%s %s: " fmt "\n", WARNING, __FUNCTION__, ## args)
/**
 * @ingroup grp_log_api
 * 打印Error日志的接口
 */
#define SLogError(fmt, args...) SLog("%s %s: " fmt "\n", ERROR, __FUNCTION__, ## args)

//TODO: SHOULD call Panic to deal, here just return
/**
 * @ingroup grp_log_api
 * 断言接口
 */
#define SAssert(exp) \
    do {    \
        if (!(exp)) {   \
            SLog("Assertion [ %s ] Failed: File %s, Line %d, Function %s\n",   \
            #exp, "__FILE__", __LINE__, __FUNCTION__);    \
            return 0xFFFF0001;    \
        }   \
    } while(0);
#else
#define SLogTrace(fmt, args...) ((void)0)
#define SLogWarning(fmt, args...) ((void)0)
#define SLogError(fmt, args...) ((void)0)
#define SAssert(exp)  ((void)0)
#endif

/**
* @ingroup  grp_log_api
* @brief 将日志输出至文件
*
* @par 描述:
* 无
*
* @attention 无
* @param fmt [IN] 日志的格式化内容
*
* @retval #无
*
* @par 依赖:
* @li tee_internal_api.h：内部数据类型定义
**/
void SLog(const char *fmt, ...);
uint32_t get_value();

/**
* @ingroup  grp_log_api
* @brief 打印函数调用栈的接口
*
* @par 描述:
* 目前调用栈打印的函数地址为绝对地址，需要经过计算对应到代码行，
* 计算方式参见开发文档
*
* @attention 无
* @param fmt [IN] 无
*
* @retval #无
*
* @par 依赖: 无
**/
void __dump_backtraces(void);

#endif
