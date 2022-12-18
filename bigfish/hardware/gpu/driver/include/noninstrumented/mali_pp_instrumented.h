/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2012-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_PP_INSTRUMENTED_H_
#define _MALI_PP_INSTRUMENTED_H_

#include "mali_system.h"
#include "mali_instrumented_context_types.h"
#include <base/pp/mali_pp_job_types.h>

MALI_STATIC_INLINE mali_err_code MALI_CHECK_RESULT _mali_pp_instrumented_init(mali_instrumented_context *ctx)
{
	MALI_IGNORE(ctx);
	MALI_SUCCESS;
}

MALI_STATIC_INLINE mali_err_code _mali_pp_derive_counts(
    mali_instrumented_context *ctx, mali_instrumented_frame *frame)
{
	MALI_IGNORE(ctx);
	MALI_IGNORE(frame);
	MALI_SUCCESS;
}

MALI_STATIC_INLINE void _mali_pp_activate_derived(mali_instrumented_context *ctx)
{
	MALI_IGNORE(ctx);
}

MALI_STATIC_INLINE void _instrumented_pp_setup(mali_instrumented_context *frame, mali_pp_job_handle job_handle, u32 frame_split_nr)
{
	MALI_IGNORE(frame);
	MALI_IGNORE(job_handle);
	MALI_IGNORE(frame_split_nr);
}

MALI_STATIC_INLINE void _instrumented_pp_done(mali_instrumented_frame *frame, mali_pp_job_handle job_handle)
{
	MALI_IGNORE(frame);
	MALI_IGNORE(job_handle);
}

MALI_STATIC_INLINE void _instrumented_pp_abort(mali_pp_job_handle job_handle)
{
	MALI_IGNORE(job_handle);
}

#endif /* _MALI_PP_INSTRUMENTED_H_ */
