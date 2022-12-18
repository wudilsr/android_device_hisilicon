/*
 * svr_logger.c
 *
 *  Created on: 2014Äê9ÔÂ18ÈÕ
 *      Author: z00187490
 */
#include <stdio.h>
#include <pthread.h>
#include "svr_log.h"

typedef struct tagSVR_LOG_CONTEXT_S
{
    pthread_mutex_t         mutex;
    HI_S32                  s32CurLevel;
    HI_S32                  s32DbgLevel;/*if s32DbgLevel is valid, use s32DbgLevel, else use s32CurLevel*/
    SVR_LOG_WRITER_S*       pstWriter;
} SVR_LOG_CONTEXT_S;

//------------------------------------------------------------------------------
static HI_VOID internal_write(HI_VOID* opaque, const HI_CHAR* tag, HI_S32 level,
        HI_CHAR* fmt, va_list var);
//------------------------------------------------------------------------------
static SVR_LOG_WRITER_S s_defaultWriter = {
        .write      = internal_write,
        .opaque     = &s_defaultWriter,
};

static SVR_LOG_CONTEXT_S s_loggerThreadData = {
        .mutex = PTHREAD_MUTEX_INITIALIZER,
        .pstWriter = &s_defaultWriter,
        .s32CurLevel = SVR_LOG_ERROR,
        .s32DbgLevel = -1,
};

static HI_CHAR s_lastBuf[MAX_BUFFER_SZ + 1];
static HI_S32 s_curRepeatCnt = 0;
static HI_S32 s_lastRepeatCnt = 0;

//------------------------------------------------------------------------------
static HI_VOID internal_write(HI_VOID* opaque, const HI_CHAR* tag, HI_S32 level,
        HI_CHAR* fmt, va_list var)
{
    platform_write(tag, level, fmt, var);
}

HI_VOID SVR_LOG_Write(const HI_CHAR* tag, HI_S32 level, HI_CHAR* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    if (level > s_loggerThreadData.s32CurLevel)
        return;

    pthread_mutex_lock(&s_loggerThreadData.mutex);
    if (s_loggerThreadData.pstWriter && s_loggerThreadData.pstWriter->write)
    {
        s_loggerThreadData.pstWriter->write(s_loggerThreadData.pstWriter->opaque,
                tag, level, fmt, args);
    }
    pthread_mutex_unlock(&s_loggerThreadData.mutex);
}

HI_VOID SVR_LOG_RegisterWriter(SVR_LOG_WRITER_S* writer)
{
    pthread_mutex_lock(&s_loggerThreadData.mutex);
    s_loggerThreadData.pstWriter = writer;
    pthread_mutex_unlock(&s_loggerThreadData.mutex);
}

HI_S32 SVR_LOG_SetLevel(HI_S32 level)
{
    if (level > -1 && level < SVR_LOG_BUTT)
    {
        s_loggerThreadData.s32CurLevel = level;
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

HI_S32 SVR_LOG_GetLevel()
{
    return s_loggerThreadData.s32CurLevel;
}

HI_S32 SVR_LOG_SetDebugLevel(HI_S32 level)
{
    if (level < SVR_LOG_BUTT)
    {
        s_loggerThreadData.s32DbgLevel = level;
        return HI_SUCCESS;
    }
    return HI_FAILURE;
}

HI_S32 SVR_LOG_GetDebugLevel()
{
    return s_loggerThreadData.s32DbgLevel;
}

HI_BOOL check_update_log(const HI_CHAR* log, HI_S32 len)
{
    if (strncmp(log, s_lastBuf, MAX_BUFFER_SZ) == 0)
    {
        s_curRepeatCnt++;
        return HI_TRUE;
    }
    strncpy(s_lastBuf, log, MAX_BUFFER_SZ);
    s_lastRepeatCnt = s_curRepeatCnt;
    s_curRepeatCnt = 0;
    return HI_FALSE;
}

HI_S32 get_last_repeat_cnt()
{
    HI_S32 cnt = s_lastRepeatCnt;
    s_lastRepeatCnt = 0;
    return cnt;
}
