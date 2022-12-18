/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_INSTRUMENTED_FRAME_H_
#define _MALI_INSTRUMENTED_FRAME_H_

#include "mali_system.h"
#include "mali_instrumented_context_types.h"
#include "shared/mali_surface.h"

MALI_STATIC_INLINE mali_err_code _instrumented_begin_new_frame(mali_instrumented_frame **old_frame)
{
	MALI_IGNORE(old_frame);
	MALI_SUCCESS;
}

MALI_STATIC_INLINE void _instrumented_frame_completed(mali_instrumented_frame *frame, mali_surface *draw_surface)
{
	MALI_IGNORE(frame);
	MALI_IGNORE(draw_surface);
}

MALI_STATIC_INLINE void _instrumented_finish_frame(mali_instrumented_frame *frame)
{
	MALI_IGNORE(frame);
}

MALI_STATIC_INLINE void _destroy_instrumented_frame(mali_instrumented_frame *frame)
{
	MALI_IGNORE(frame);
}

#endif /* _MALI_INSTRUMENTED_FRAME_H_ */

