/*
 * svr_linux_log.c
 *
 *  Created on: 2014Äê9ÔÂ22ÈÕ
 *      Author: z00187490
 */
#include <unistd.h>
#include <sys/syscall.h>
#include "svr_log.h"

static HI_CHAR level2Ch[SVR_LOG_BUTT] = {
        [SVR_LOG_QUIET] = 'N',
        [SVR_LOG_VERBOSE] = 'V',
        [SVR_LOG_DEBUG] = 'D',
        [SVR_LOG_INFO] = 'I',
        [SVR_LOG_WARN] = 'W',
        [SVR_LOG_ERROR] = 'E',
        [SVR_LOG_FATAL] = 'F',
};

HI_VOID platform_write(const HI_CHAR* tag, HI_S32 level,
        HI_CHAR* fmt, va_list var)
{
#ifndef HI_ADVCA_FUNCTION_RELEASE
    HI_CHAR buf[MAX_BUFFER_SZ + 1];
    HI_CHAR* p = buf;
    HI_S32 cnt;

    buf[MAX_BUFFER_SZ] = 0;

    if (tag)
    {
        snprintf(buf, MAX_BUFFER_SZ, "%c/%s (%d,%d):", level2Ch[level], tag,
                getpid(), syscall(SYS_gettid));
        p = buf + strlen(buf);
    }

    vsnprintf(p, MAX_BUFFER_SZ - (p - buf), fmt, var);
    p = strchr(buf, '\0');

    if (p > buf && p[-1] != '\n')
    {
        p[0] = '\n';//add a new line if it does not have
        p[1] = 0;
    }

    printf("%s", buf);
#endif
}

