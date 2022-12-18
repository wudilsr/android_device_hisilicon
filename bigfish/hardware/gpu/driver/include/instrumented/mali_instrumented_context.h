/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2012-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_INSTRUMENTED_CONTEXT_H_
#define _MALI_INSTRUMENTED_CONTEXT_H_

#include "mali_system.h"
#include "mali_instrumented_context_types.h"
#include "mali_instrumented_frame.h"

/**
 * Create instrumented context.
 *
 * The instrumented context is used by the instrumented drivers to store data.
 * It is controlled by EGL.
 *
 * @return a pointer to the created instrumented context. May return NULL,
 *         in which case there is no instrumented context available.
 */
MALI_IMPORT
mali_instrumented_context *MALI_CHECK_RESULT _instrumented_create_context(void);

/**
 * Destroy instrumented context by deallocating (freeing) all parts of it.
 * All instrumented frames should be released prior to this.
 */
MALI_IMPORT
void _instrumented_destroy_context(void);

/**
 * Finish initialization of the instrumentation module.
 *
 * This will prevent any further counters to be registered with mali_counters,
 * open dump files, create the first frame of counter values, etc.
 */
MALI_IMPORT
void _instrumented_finish_init(void);

/**
 * Get the thread local storage data. If not already allocated, it will be
 * done.
 *
 * \param ctx Instrumented context that is used for registering cleanup pointers in
 *            if the function has to create a new tls structure.
 * \return NULL if allocation failed
 */
MALI_IMPORT
mali_instrumented_tls_struct *_instrumented_get_tls_with_context(mali_instrumented_context *ctx);

/**
 * Get the thread local storage data. If not already allocated, it will be
 * done.
 *
 * This function requires that an instrumented context is made current.
 *
 * @return NULL if allocation failed
 */
MALI_IMPORT
mali_instrumented_tls_struct *_instrumented_get_tls(void);

/**
 * Destroys all the tls structures registered to destroction list of the given
 * instrumented context.
 *
 * \ctx Instrumented context containing the list of tls structures to destroy.
 */
MALI_IMPORT
void _instrumented_destroy_tls_structures(mali_instrumented_context *ctx);

/**
 * Returns the instrumented context
 */
MALI_IMPORT
mali_instrumented_context *_instrumented_get_context(void);

/**
 * Check if any instrumented frames can be completed.
 * It is important that all instrumented frames are completed in the correct order,
 * so we don't output frame #2 before frame #1 or similar!
 */
MALI_IMPORT
void _instrumented_context_finish_frames(mali_instrumented_context *ctx);

/**
 * Get the current instrumented_frame used by the instrumented driver.
 * This function is not thread safe, so use with care!
 */
MALI_STATIC_INLINE mali_instrumented_frame *_instrumented_get_current_frame(void)
{
	mali_instrumented_context *ctx = _instrumented_get_context();

	if (NULL == ctx)
	{
		return NULL;
	}

	return ctx->current_frame;
}

/**
 * Get the current instrumented_frame used by the instrumented driver, and a
 * reference will be added to the frame, so every pointer acquired must be released by calling _instrumented_release_frame
 */
MALI_STATIC_INLINE mali_instrumented_frame *_instrumented_acquire_current_frame(void)
{
	mali_instrumented_frame *frame;
	mali_instrumented_context *ctx = _instrumented_get_context();

	if (NULL == ctx)
	{
		return NULL;
	}

	_mali_sys_lock_lock(ctx->lock);

	frame = ctx->current_frame;

	if (NULL != frame)
	{
		_mali_sys_atomic_inc(&frame->ref_count);
	}

	_mali_sys_lock_unlock(ctx->lock);

	return frame;
}


#endif /* _MALI_INSTRUMENTED_CONTEXT_H_ */
