#ifndef _LOG_H_
#define _LOG_H_
#include <stdarg.h>
#include <stdio.h>

/*
 * Using the same definition in ffmpeg
 * Change the name from AV_LOG_XX into DASH_LOG_XX
 */
#define DASH_LOG_QUIET    -8
#define DASH_LOG_PANIC     0
#define DASH_LOG_FATAL     8
#define DASH_LOG_ERROR    16
#define DASH_LOG_WARNING  24
#define DASH_LOG_INFO     32
#define DASH_LOG_VERBOSE  40
#define DASH_LOG_DEBUG    48

int dash_log_get_level(void);
void dash_log_set_level(int);
void dash_log(int level, const char * fmt,...);
unsigned long long dash_gettime(void);
#endif
