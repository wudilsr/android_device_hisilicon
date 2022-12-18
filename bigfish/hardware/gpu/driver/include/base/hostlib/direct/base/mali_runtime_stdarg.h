/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013-2014 ARM Limited
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

MALI_STATIC_FORCE_INLINE int _mali_sys_vsnprintf(char *str, u32 size, const char *format, va_list ap)
{
	return vsnprintf(str, size, format, ap);
}

MALI_STATIC_FORCE_INLINE int _mali_sys_vfprintf(mali_file *file, const char *format, va_list ap)
{
	return vfprintf(MALI_REINTERPRET_CAST(FILE *)file, format, ap);
}

#ifdef __cplusplus
}
#endif

#endif /* _MALI_RUNTIME_STDARG_H_ */

