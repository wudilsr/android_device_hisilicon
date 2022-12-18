/**
* @file tee_log.h
*
* Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
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

//#define TA_DEBUG
#ifdef TA_DEBUG
#define DEBUG_TAG "[debug]"
#define ta_debug(fmt, args...) uart_printf_func("%s %s: " fmt "", DEBUG_TAG, __FUNCTION__, ## args)
#else
#define ta_debug(fmt, args...)
#endif

#define ERROR_TAG "[error]"
#define ta_error(fmt, args...) uart_printf_func("%s %s: " fmt "", ERROR_TAG, __FUNCTION__, ## args)

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
            #exp, __FILE__, __LINE__, __FUNCTION__);    \
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

#endif
