/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _SW_PROFILING_H_
#define _SW_PROFILING_H_

#include "mali_system.h"
#include "sw_profiling_types.h"

MALI_STATIC_INLINE void _mali_profiling_analyze(mali_instrumented_frame *frame)
{
	MALI_IGNORE(frame);
}

MALI_STATIC_INLINE void _profiling_enter(u32 counter_id)
{
	MALI_IGNORE(counter_id);
}

MALI_STATIC_INLINE void _profiling_leave(u32 counter_id)
{
	MALI_IGNORE(counter_id);
}

MALI_STATIC_INLINE void _profiling_count(u32 counter_id, u32 increment)
{
	MALI_IGNORE(counter_id);
	MALI_IGNORE(increment);
}

#endif /* _SW_PROFILING_H_ */

