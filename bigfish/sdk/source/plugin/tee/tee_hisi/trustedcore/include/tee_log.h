/**
* @file tee_log.h
*
* Copyright(C), 2008-2013, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* ��������ȫ�������log��������\n
*/

/** @defgroup grp_log_api ��ȫ�������
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
 * ��־�ļ���Trace
 */
#define TRACE "[Trace]"
/**
 * @ingroup grp_log_api
 * ��־�ļ���Warning
 */
#define WARNING "[Warning]"
/**
 * @ingroup grp_log_api
 * ��־�ļ���Error
 */
#define ERROR "[Error]"

/**
 * @ingroup grp_log_api
 * ��ӡTrace��־�Ľӿ�
 */
#define SLogTrace(fmt, args...) SLog("%s %s: " fmt "\n", TRACE, __FUNCTION__, ## args)
/**
 * @ingroup grp_log_api
 * ��ӡWarning��־�Ľӿ�
 */
#define SLogWarning(fmt, args...) SLog("%s %s: " fmt "\n", WARNING, __FUNCTION__, ## args)
/**
 * @ingroup grp_log_api
 * ��ӡError��־�Ľӿ�
 */
#define SLogError(fmt, args...) SLog("%s %s: " fmt "\n", ERROR, __FUNCTION__, ## args)

//TODO: SHOULD call Panic to deal, here just return
/**
 * @ingroup grp_log_api
 * ���Խӿ�
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
* @brief ����־������ļ�
*
* @par ����:
* ��
*
* @attention ��
* @param fmt [IN] ��־�ĸ�ʽ������
*
* @retval #��
*
* @par ����:
* @li tee_internal_api.h���ڲ��������Ͷ���
**/
void SLog(const char *fmt, ...);

#endif
