/*******************************************************************************
 *
 * Copyright (c) 2000-2003 Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * - Neither name of Intel Corporation nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/

/*!
 * \file
 */

#include "config.h"

#include "ithread.h"
#include "ixml.h"
#include "upnp.h"
#include "upnpdebug.h"

/*lint -save -e* */
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*lint -restore * */

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define HIPRINTF printf
#else
#define HIPRINTF(fmt...)  do{}while((void)0,0)
#endif /*HI_ADVCA_FUNCTION_RELEASE*/


int gulUpnpLogLevel = DLNA_UPNP_LOG_LEVEL_ERROR;

unsigned long long  GetNowmTime()
{
    struct timeval now;
    unsigned long long   u64NowmTime;

    gettimeofday(&now,(struct timezone*) 0);
    u64NowmTime = now.tv_sec * 1000 + now.tv_usec /1000;
    return u64NowmTime;
}

void DlnaUpnpSetLogLevel
(
    int enLevel
)
{
    gulUpnpLogLevel = (int)enLevel;
    return;
}


void DlnaUpnpLogE
(
    char *format, ...
)
{

    va_list va;
    char *PathFromEnv = getenv("DLNA_LOGFILE_PATH");
    char *pcFileName = PathFromEnv!=NULL ? PathFromEnv : "./DlnaLogError.txt";
    FILE *Fd = NULL;

    if (gulUpnpLogLevel  < DLNA_UPNP_LOG_LEVEL_ERROR)
    {
        return;
    }

    if (NULL == format)
    {
        HIPRINTF("\r\n NULL format string");
        return;
    }

    Fd = fopen(pcFileName, "a+");
    if (NULL == Fd)
    {
        HIPRINTF("\r\n DlnaLogError.txt Open Failed!!!!, errno = %d", errno);
        return;
    }

    va_start(va, format);
    fprintf(Fd, "\r\n VPP_DLNA_ERROR:");
    (void)vfprintf(Fd, format, va);

    (void)fclose(Fd);
    va_end (va);
    return;
}

void DlnaUpnpLogI
(
    char *format, ...
)
{

    va_list va;
    char *PathFromEnv = getenv("DLNA_LOGFILE_PATH");
    char *pcFileName = PathFromEnv!=NULL ? PathFromEnv : "./DlnaLogInfo.txt";
    FILE *Fd = NULL;

    if (gulUpnpLogLevel < DLNA_UPNP_LOG_LEVEL_INFO)
    {
        return;
    }

    if (NULL == format)
    {
        HIPRINTF("\r\n NULL format string");
        return;
    }

    Fd = fopen(pcFileName, "a+");
    if (NULL == Fd)
    {
        HIPRINTF("\r\n DlnaLogInfo.txt Open Failed!!!!, errno = %d", errno);
        return;
    }

    va_start(va, format);
    fprintf(Fd, "\r\n VPP_DLNA_INFO:");
    (void)vfprintf(Fd, format, va);

    (void)fclose(Fd);
    va_end (va);
    return;
}

void DlnaUpnpLogV
(
   char *format, ...
)
{

    va_list va;
    char *PathFromEnv = getenv("DLNA_LOGFILE_PATH");
    char *pcFileName = PathFromEnv!=NULL ? PathFromEnv : "./DlnaLogTrace.txt";
    FILE *Fd = NULL;

    if (gulUpnpLogLevel < DLNA_UPNP_LOG_LEVEL_TRACE)
    {
        return;
    }

    if (NULL == format)
    {
        HIPRINTF("\r\n NULL format string");
        return;
    }

    Fd = fopen(pcFileName, "a+");
    if (NULL == Fd)
    {
        HIPRINTF("\r\n DlnaLogTrace.txt Open Failed!!!!, errno = %d", errno);
        return;
    }

    va_start(va, format);
    fprintf(Fd, "\r\n VPP_DLNA_TRACE:");
    (void)vfprintf(Fd, format, va);

    (void)fclose(Fd);
    va_end (va);
    return;
}


#ifdef DLNA_SFT

#define DLNA_INVALID_PTR(_PTR) (NULL == (_PTR))

UPNP_MSG_CALLBACK_FUNC_ST   gUpnpMemCallBackFunc    =
{
    SFT_malloc,
    SFT_free,
    SFT_realloc,
    SFT_strdup
};

void *SFT_malloc(size_t size)
{
    return malloc(size);
}

void *SFT_realloc(void *ptr, size_t size)
{
    return realloc(ptr,size);
}

void   SFT_free(void *ptr)
{
    if (ptr != NULL)
    {
        free((void *)ptr);
        ptr = NULL;
    }
}

char * SFT_strdup(const char *s)
{
        return strdup(s);
}



int  UpnpApiRegMemFunc
(
    const UPNP_MSG_CALLBACK_FUNC_ST *pstMsgFunc
)
{

    if (DLNA_INVALID_PTR(pstMsgFunc))
    {
        return 1;
    }

    if (DLNA_INVALID_PTR(pstMsgFunc->pfMallocMsg))
    {
        return 1;
    }

    if (DLNA_INVALID_PTR(pstMsgFunc->pfFreeMsg))
    {
        return 1;
    }

    if (DLNA_INVALID_PTR(pstMsgFunc->pfReAllocMsg))
    {
       return 1;
    }


    if (DLNA_INVALID_PTR(pstMsgFunc->pfStrdup))
    {
        return 1;
    }

    gUpnpMemCallBackFunc = *pstMsgFunc;

    return 0;
}

#endif


#ifdef DEBUG_PRINT     //earlier #ifdef DEBUG

/*! Mutex to synchronize all the log file opeartions in the debug mode */
static ithread_mutex_t GlobalDebugMutex;

/*! Global log level */
static Upnp_LogLevel g_log_level = UPNP_DEFAULT_LOG_LEVEL;

/*! File handle for the error log file */
static FILE *ErrFileHnd = NULL;

/*! File handle for the information log file */
static FILE *InfoFileHnd = NULL;

/*! Name of the error file */
/*  modified by s00902670 & k00900440
static const char *errFileName = "IUpnpErrFile.txt";*/
static const char *errFileName = "IUpnpErrFile.txt";


/*! Name of the info file */
/*  modified by s00902670 & k00900440
static const char *infoFileName = "IUpnpInfoFile.txt"; */
static const char *infoFileName = "IUpnpInfoFile.txt";

/*  ADDED by s00902670 & k00900440 */
int   g_debug_level = 0;


int UpnpInitLog(void)
{
    ithread_mutex_init(&GlobalDebugMutex, NULL);
    if (DEBUG_TARGET == 1) {
        if ((ErrFileHnd = fopen(errFileName, "a")) == NULL) {
            /*  ADDED by s00902670 & k00900440 */
            DLNA_LOGE("[VPPDLNA]:%s fopen %s failed\r\n", __FUNCTION__, errFileName);
            return -1;
        }
        if ((InfoFileHnd = fopen(infoFileName, "a")) == NULL) {
            /*  ADDED by s00902670 & k00900440 */
            DLNA_LOGE("[VPPDLNA]:%s fopen %s failed\r\n", __FUNCTION__, infoFileName);
            return -1;
        }
    }
    return UPNP_E_SUCCESS;
}

void UpnpSetLogLevel(Upnp_LogLevel log_level)
{
    g_log_level = log_level;
}

void UpnpCloseLog(void)
{
    if (DEBUG_TARGET == 1) {
        fflush(ErrFileHnd);
        fflush(InfoFileHnd);
        fclose(ErrFileHnd);
        fclose(InfoFileHnd);
    }
    (void)ithread_mutex_destroy(&GlobalDebugMutex);
}

void UpnpSetLogFileNames(const char *ErrFileName, const char *InfoFileName)
{
    if (ErrFileName) {
        errFileName = ErrFileName;
    }
    if (InfoFileName) {
        infoFileName = InfoFileName;
    }
}

int DebugAtThisLevel(Upnp_LogLevel DLevel, Dbg_Module Module)
{
    int ret = DLevel <= g_log_level;
    ret &=
        DEBUG_ALL ||
        (Module == SSDP && DEBUG_SSDP) ||
        (Module == SOAP && DEBUG_SOAP) ||
        (Module == GENA && DEBUG_GENA) ||
        (Module == TPOOL && DEBUG_TPOOL) ||
        (Module == MSERV && DEBUG_MSERV) ||
        (Module == DOM && DEBUG_DOM) || (Module == HTTP && DEBUG_HTTP);

    return ret;
}

void UpnpPrintf(Upnp_LogLevel DLevel,
        Dbg_Module Module,
        const char *DbgFileName, int DbgLineNo, const char *FmtStr, ...)
{
    va_list ArgList;

    /*  ADDED by s00902670 & k00900440 */
    if (g_debug_level  <  (int)DLevel)
    {
        //log_debug("the g_debug_level %d \r\n", g_debug_level);
        return;
    }

    if (!DebugAtThisLevel(DLevel, Module))
        return;
    ithread_mutex_lock(&GlobalDebugMutex);
    va_start(ArgList, FmtStr);
    if (!DEBUG_TARGET) {
        if (DbgFileName)
            UpnpDisplayFileAndLine(stdout, DbgFileName, DbgLineNo);
        vfprintf(stdout, FmtStr, ArgList);
        fflush(stdout);
    } else if (DLevel == 0) {
        if (DbgFileName)
            UpnpDisplayFileAndLine(ErrFileHnd, DbgFileName,
                           DbgLineNo);
        vfprintf(ErrFileHnd, FmtStr, ArgList);
        fflush(ErrFileHnd);
    } else {
        if (DbgFileName)
            UpnpDisplayFileAndLine(InfoFileHnd, DbgFileName,
                           DbgLineNo);
        vfprintf(InfoFileHnd, FmtStr, ArgList);
        fflush(InfoFileHnd);
    }
    va_end(ArgList);
    (void)ithread_mutex_unlock(&GlobalDebugMutex);
}

FILE *GetDebugFile(Upnp_LogLevel DLevel, Dbg_Module Module)
{
    FILE *ret;

    if (!DebugAtThisLevel(DLevel, Module))
        ret = NULL;
    if (!DEBUG_TARGET)
        ret = stdout;
    else if (DLevel == 0)
        ret = ErrFileHnd;
    else
        ret = InfoFileHnd;

    return ret;
}

void UpnpDisplayFileAndLine(FILE *fd, const char *DbgFileName, int DbgLineNo)
{
#define NLINES 2
#define MAX_LINE_SIZE 512
#define NUMBER_OF_STARS 80
    const char *lines[NLINES];
    char buf[NLINES][MAX_LINE_SIZE];
    int i;

    /* Initialize the pointer array */
    for (i = 0; i < NLINES; i++)
        lines[i] = buf[i];
    /* Put the debug lines in the buffer */
    snprintf(buf[0], sizeof(buf[0])/sizeof(char),"DEBUG - THREAD ID: 0x%lX",
#ifdef WIN32
        (unsigned long int)ithread_self().p
#else
        (unsigned long int)ithread_self()
#endif
        );
    if (DbgFileName)
        snprintf(buf[1],sizeof(buf[1])/sizeof(char), "FILE: %s, LINE: %d", DbgFileName, DbgLineNo);
    /* Show the lines centered */
    UpnpDisplayBanner(fd, lines, NLINES, NUMBER_OF_STARS);
    fflush(fd);
}

void UpnpDisplayBanner(FILE * fd,
               const char **lines, size_t size, size_t starLength)
{
    size_t leftMarginLength = starLength / 2 + 1;
    size_t rightMarginLength = starLength / 2 + 1;
    size_t i = 0;
    size_t LineSize = 0;
    size_t starLengthMinus2 = starLength - 2;

    char *leftMargin = UPNP_MALLOC(leftMarginLength);
    char *rightMargin = UPNP_MALLOC(rightMarginLength);
    char *stars = UPNP_MALLOC(starLength + 1);
    char *currentLine = UPNP_MALLOC(starLength + 1);
    const char *line = NULL;

    memset(stars, '*', starLength);
    stars[starLength] = 0;
    memset(leftMargin, 0, leftMarginLength);
    memset(rightMargin, 0, rightMarginLength);
    fprintf(fd, "\n%s\n", stars);
    for (i = 0; i < size; i++) {
        LineSize = strlen(lines[i]);
        line = lines[i];
        while (LineSize > starLengthMinus2) {
            memcpy(currentLine, line, starLengthMinus2);
            currentLine[starLengthMinus2] = 0;
            fprintf(fd, "*%s*\n", currentLine);
            LineSize -= starLengthMinus2;
            line += starLengthMinus2;
        }
        leftMarginLength = (starLengthMinus2 - LineSize) / 2;
        if (LineSize % 2 == 0)
            rightMarginLength = leftMarginLength;
        else
            rightMarginLength = leftMarginLength + 1;
        memset(leftMargin, ' ', leftMarginLength);
        memset(rightMargin, ' ', rightMarginLength);
        leftMargin[leftMarginLength] = 0;
        rightMargin[rightMarginLength] = 0;
        fprintf(fd, "*%s%s%s*\n", leftMargin, line, rightMargin);
    }
    fprintf(fd, "%s\n\n", stars);

    UPNP_FREE(currentLine);
    UPNP_FREE(stars);
    UPNP_FREE(rightMargin);
    UPNP_FREE(leftMargin);
}

#endif /* DEBUG */
