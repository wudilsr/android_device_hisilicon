/*-----------------------------------------------------------------------*/
/*!!Warning: Hisilicon key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rYgDnWEYHdqiWpPUq+8h0NJnkUwtwxOoujF8BW8obPKNdmdww7LfnMZl6VC2
5nhx9SzWpegMoUn8SOajFVqz2oG+nf5JHZqhoDy1w3LSCZQCHiAxfLxdyDMMfFJrOj9fAiVV
akV4rzPTF0YHjYFVvrlYDdavIzeylpSMgOxgaILFabk0QjoQcuHIoMEQ61z0Pg==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/
























/*
 * log functions
 * Copyright (c) 2003 Michel Bardiaux
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file libavutil/log.c
 * logging functions
 */

#include "avutil.h"
#include "log.h"

#if defined(_MSC_VER)
#pragma  warning(disable:4996)
#endif

int av_log_level = AV_LOG_INFO;

#ifdef __GNUC__
void av_log_default_callback(const char *file, int lineno, const char *funcname, void* ptr, int level, const char* fmt, va_list vl)
#else
void av_log_default_callback(void* ptr, int level, const char* fmt, va_list vl)
#endif
{
    static int print_prefix=1;
    static int count;
    static char line[1024], prev[1024];
    AVClass* avc= ptr ? *(AVClass**)((int*)ptr) : NULL; 
    if(level>av_log_level)
        return;
#undef fprintf
    if(print_prefix && avc) {
        snprintf(line, 1024, "[%s @ %p]", avc->item_name(ptr), ptr);
    }else
        line[0]=0;

    vsnprintf(line + strlen(line), sizeof(line) - strlen(line), fmt, vl);

    print_prefix= line[strlen(line)-1] == '\n';
    if(print_prefix && !strncmp(line, prev,1024)){
        count++;
        return;
    }

    if(count>0){
#ifndef __KERNEL__
        fprintf(stderr, "    Last message repeated %d times\n", count);
#endif
        count=0;
    }

#ifndef __KERNEL__
    fputs(line, stderr);
#else
 #ifndef HI_ADVCA_FUNCTION_RELEASE
	printk(line);
 #endif
#endif

    strncpy(prev, line,1024);
}

/* 2010/03/30 15:00:00 songxg+00133955 */
/* 修改av_log函数，在linux平台下增加文件名、行号显示 */
#ifdef __GNUC__
static void (*av_log_callback)(const char *, int, const char *, void*, int, const char*, va_list) = av_log_default_callback;

void av_log_set_callback(void (*callback)(const char *, int, const char *, void*, int, const char*, va_list))
{
	av_log_callback = callback;
}

void av_log_hw(const char *file, int line, const char *funcname, void* avcl, int level, const char *fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);

	av_vlog(file, line, funcname, avcl, level, fmt, vl);

	va_end(vl);
}
void av_log_hw_nothing(void)
{
	return;
}
void av_vlog(const char *file, int line, const char *funcname, void* avcl, int level, const char *fmt, va_list vl)
{
	av_log_callback(file, line, funcname, avcl, level, fmt, vl);
}

#else
static void (*av_log_callback)(void*, int, const char*, va_list) = av_log_default_callback;

void av_log_set_callback(void (*callback)(void*, int, const char*, va_list))
{
	av_log_callback = callback;
}

void av_log_private(void* avcl, int level, const char *fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);

	av_vlog(avcl, level, fmt, vl);

	va_end(vl);
}

void av_log_nothing(void)
{
	return;
}


void av_vlog(void* avcl, int level, const char *fmt, va_list vl)
{
	av_log_callback(avcl, level, fmt, vl);
}

#endif

int av_log_get_level(void)
{
    return av_log_level;
}

void av_log_set_level(int level)
{
    av_log_level = level;
}

