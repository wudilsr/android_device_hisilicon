/*
 *
 */
#if defined (ANDROID_VERSION)
#include <utils/Log.h>
#undef  LOG_TAG
#define LOG_TAG "HiDASH"
#endif
#include <sys/time.h>
#include <time.h>
#include "log.h"

static int dash_log_level = DASH_LOG_INFO;

int dash_log_get_level(void)
{
    return dash_log_level;
}

void dash_log_set_level(int level)
{
    dash_log_level = level;
}

void dash_log(int level, const char * fmt,...)
{
    char buf[2048]= {0};

    if (dash_log_level < DASH_LOG_FATAL || level > dash_log_level)
        return;
    int ret;
    struct timeval tv;
    struct tm* ptm;

    va_list vl;
    va_start(vl, fmt);

    gettimeofday(&tv, NULL);
    ptm = localtime (&tv.tv_sec);

    ret= snprintf(buf, sizeof(buf), "[%02d:%02d:%02d.%03d] ", ptm->tm_hour, ptm->tm_min, ptm->tm_sec, tv.tv_usec / 1000);
    vsnprintf(buf + ret , sizeof(buf) - ret, fmt, vl);

#if defined (ANDROID_VERSION)
    ALOGE("%s", buf);
#else
    printf("%s", buf);
#endif

    va_end(vl);
}

unsigned long long dash_gettime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return (unsigned long long)tv.tv_sec * 1000000 + (unsigned long long)tv.tv_usec;
}
