/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_runtime.h
 * Wraps compiler specific stdarg functions. This file will have to
 * include the C library's stdarg.h, and will "polute" the namespace
 * of the including modules. It should be included with care so that
 * any ports to platforms without stdarg.h will have a manageable job.
 */

#ifndef _MALI_RUNTIME_STDARG_H_
#define _MALI_RUNTIME_STDARG_H_

#include <base/mali_runtime.h>

#include <stdarg.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * vsnprintf wrapper.
 *
 * A failsafe vsnprintf wrapper. The function is like a printf that prints
 * its contents to a text string with a given maximum length.
 * We guarantee that the last byte written will be a Zero byte, which
 * terminates the text string, and that the total number of bytes written
 * will never exceed size bytes. This guarantee also implies that the
 * maximum letters written to the string is (size-1), before the
 * Zero-termination.
 * The function does not call the va_end macro on ap, so ap is undefined
 * after the call. The caller should call va_end(ap) itself afterwards.
 *
 * @param str The string that this function writes to.
 * @param size Number of bytes in the buffer.
 * @param format The input text string that formats the output string.
 * @param ap Variable argument list
 */
MALI_IMPORT
int _mali_sys_vsnprintf(char *str, u32 size, const char *format, va_list ap);

/**
 * Print to file. Same semantics as libc's vfprintf().
 *
 * The function does not call the va_end macro on ap, so ap is undefined
 * after the call. The caller should call va_end(ap) itself afterwards.
 *
 * @param file File to write to - opened by _mali_fopen().
 * @param format The input string that formats the output string.
 * @param ap Variable argument list
 */
MALI_IMPORT
int _mali_sys_vfprintf(mali_file *file, const char *format, va_list ap);

#ifdef __cplusplus
}
#endif

#endif /* _MALI_RUNTIME_STDARG_H_ */

