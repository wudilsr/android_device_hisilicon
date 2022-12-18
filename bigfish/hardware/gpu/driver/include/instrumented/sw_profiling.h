/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2010, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _SW_PROFILING_H_
#define _SW_PROFILING_H_

#include "mali_system.h"
#include "sw_profiling_types.h"

#include "mali_runtime_timer.h"

#include "mali_instrumented_frame.h"
#include "mali_instrumented_context.h"

/**
 * Initialize profiling.
 */
MALI_IMPORT
mali_err_code _mali_profiling_init(mali_instrumented_context *ctx);

/**
 * Clear/delete the data inside the given profiling_buffer. This function
 * does _not_ delete the profiling_buffer itself.
 *
 * \param prof_buffer The profiling_buffer whose data should be
 *                    cleared/deleted.
 */
MALI_IMPORT
void clear_profiling_buffer(profiling_buffer *prof_buffer);

/**
 * Analyze the contents of the profiling buffer for this thread.
 *
 * This is run at least once per frame, parsing the profiling buffer
 * and adding the values using _instrumented_add_to_counter().
 * It should be called one time for each thread that's working on the
 * current context.
 *
 * @param frame Instrumented frame to add values to.
 */
MALI_IMPORT
void _mali_profiling_analyze(mali_instrumented_frame *frame);

/**
 * Grow the size of the profiling buffer when it's full.
 *
 * @returns MALI_TRUE if successful, MALI_FALSE if not. When it fails,
 * the old buffer will still be available.
 */
MALI_IMPORT
mali_bool _mali_profiling_grow_buffer(void);

/**
 * Enter a section of code which should be timed.
 *
 * Should be followed by a call to @a profiling_leave with the same counter id. The
 * time spent between the call to _profiling_enter and _profiling_leave is added to
 * the counter.
 * @param counter_id id number of the interval timer
 */
MALI_IMPORT
void _profiling_enter(u32 counter_id);

/**
 * Leave a profiling section.
 *
 * Should follow a call to @a profiling_enter with the same counter id.
 * @param counter_id id number of the interval timer
 */
MALI_IMPORT
void _profiling_leave(u32 counter_id);

/**
 * Count a profiling event.
 *
 * Adjusts the counter's value by +increment.
 * @param counter_id id number of the counter
 */
MALI_IMPORT
void _profiling_count(u32 counter_id, u32 increment);

#endif /* _SW_PROFILING_H_ */

