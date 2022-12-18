/*
 * svr_android_log.c
 *
 *  Created on: 2014Äê9ÔÂ22ÈÕ
 *      Author: z00187490
 */

#include <utils/Log.h>
#include "svr_log.h"

#define LOG_NDEBUG 0

static int level2Android[SVR_LOG_BUTT] = {
        [SVR_LOG_QUIET] = ANDROID_LOG_UNKNOWN,
        [SVR_LOG_VERBOSE] = ANDROID_LOG_VERBOSE,
        [SVR_LOG_DEBUG] = ANDROID_LOG_DEBUG,
        [SVR_LOG_INFO] = ANDROID_LOG_INFO,
        [SVR_LOG_WARN] = ANDROID_LOG_WARN,
        [SVR_LOG_ERROR] = ANDROID_LOG_ERROR,
        [SVR_LOG_FATAL] = ANDROID_LOG_FATAL,
};

HI_VOID platform_write(const HI_CHAR* tag, HI_S32 level,
        HI_CHAR* fmt, va_list var)
{
    HI_CHAR buf[MAX_BUFFER_SZ];
    HI_CHAR* p = buf;
    HI_S32 cnt;

    vsnprintf(p, MAX_BUFFER_SZ - (p - buf), fmt, var);
    p = strchr(buf, '\0');

    if ((HI_U32)p > (HI_U32)buf && p[-1] == '\n')
    {
        p[-1] = '\0';//remove last \n
    }

    android_writeLog(level2Android[level], tag, buf);
}

