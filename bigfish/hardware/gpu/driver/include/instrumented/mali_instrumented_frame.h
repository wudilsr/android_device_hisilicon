/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2011, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_INSTRUMENTED_FRAME_H_
#define _MALI_INSTRUMENTED_FRAME_H_

#include "mali_system.h"
#include "base/mali_memory.h"
#include "mali_instrumented_context_types.h"
#include "shared/mali_surface.h"


/**
 * Allocate and initialize a new mali_instrumented_frame and set ctx->current_frame to that
 * frame.
 *
 * @param old_frame The frame which was replaced is returned here
 */
MALI_IMPORT
mali_err_code _instrumented_begin_new_frame(mali_instrumented_frame **old_frame);

/**
 * Writes out the counters and dumps the frame buffer if these features are turned on.
 * Reads remote commands from MRI if MRI is enabled.
 *
 * @param frame The instrumented frame to be finished. This frame contains the counters
 *              to be dumped to a file.
 */
MALI_IMPORT
void _instrumented_finish_frame(mali_instrumented_frame *frame);

/**
 * Destroys the given instrumented frame.  That includes freeing the frame's counter values table
 * and unmapping the frame buffer if instrumentation code has been using that.
 *
 * @param frame An instrumented frame to be destroyed
 */
MALI_STATIC_INLINE void _destroy_instrumented_frame(mali_instrumented_frame *frame)
{
	if (frame->counter_values)
	{
		_mali_sys_free(frame->counter_values);
	}

	_mali_sys_memset(frame, 0xCD, sizeof(mali_instrumented_frame));
	_mali_sys_free(frame);
}

MALI_IMPORT
void _instrumented_addref_frame(mali_instrumented_frame *frame);

MALI_IMPORT
void _instrumented_release_frame(mali_instrumented_frame *frame);

MALI_IMPORT
void _instrumented_frame_completed(mali_instrumented_frame *frame, mali_surface *draw_surface);

MALI_STATIC_INLINE mali_bool _instrumented_frame_is_completed(mali_instrumented_frame *frame)
{
	return (_mali_sys_atomic_get(&frame->ref_count) == 0);
}

/**
 * Set the instrumented frame's "profiling buffer has been realloced" flag.
 */
MALI_IMPORT
void _instrumented_frame_set_realloced(mali_instrumented_frame *frame);

/**
 * Get the instrumetned frame's "profiling buffer has been realloced" flag.
 */
MALI_IMPORT
mali_bool _instrumented_frame_get_realloced(mali_instrumented_frame *frame);

#endif /* _MALI_INSTRUMENTED_FRAME_H_ */

