/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2010, 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_RUNTIME_TIMER_H_
#define _MALI_RUNTIME_TIMER_H_

#include <base/mali_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

MALI_STATIC_INLINE u32 _mali_sys_get_timestamp(void)
{
	return (u32)_mali_sys_get_time_usec();
}

MALI_STATIC_INLINE float _mali_sys_get_timestamp_scaling_factor(void)
{
	return (float)(1.0 / 1000000.0);
}
#ifdef __cplusplus
}
#endif

#endif /* _MALI_RUNTIME_STDARG_H_ */

