/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_COUNTERS_H_
#define _MALI_COUNTERS_H_

#include "mali_system.h"
#include "mali_instrumented_counter_types.h"
#include "mali_instrumented_context_types.h"
#include "mali_instrumented_frame.h"

/*
 * NOP-implementation of mali_counters.h
 *
 * See ../instrumented/mali_counters.h for function documentation
 */

MALI_STATIC_INLINE const mali_counter_group *MALI_CHECK_RESULT _instrumented_get_counter_headers(mali_instrumented_context *ctx)
{
	MALI_IGNORE(ctx);
	return NULL;
}

MALI_STATIC_INLINE const mali_counter_info *MALI_CHECK_RESULT _instrumented_get_counter_information(
    mali_instrumented_context *ctx, u32 counter_index)
{
	MALI_IGNORE(ctx);
	MALI_IGNORE(counter_index);
	return NULL;
}

MALI_STATIC_INLINE int MALI_CHECK_RESULT _instrumented_get_number_of_counters(mali_instrumented_context *ctx)
{
	MALI_IGNORE(ctx);
	return 0;
}

MALI_STATIC_INLINE mali_err_code MALI_CHECK_RESULT _instrumented_activate_counters(
    mali_instrumented_context *ctx,
    const unsigned int *counter_indices, unsigned int counter_amount)
{
	MALI_IGNORE(ctx);
	MALI_IGNORE(counter_indices);
	MALI_IGNORE(counter_amount);
	return MALI_ERR_NO_ERROR;
}

MALI_STATIC_INLINE mali_err_code MALI_CHECK_RESULT _instrumented_deactivate_counters(
    mali_instrumented_context *ctx,
    const unsigned int *counter_indices, int counter_amount)
{
	MALI_IGNORE(ctx);
	MALI_IGNORE(counter_indices);
	MALI_IGNORE(counter_amount);
	return MALI_ERR_NO_ERROR;
}

MALI_STATIC_INLINE mali_bool MALI_CHECK_RESULT _instrumented_is_sampling_enabled(mali_instrumented_context *ctx)
{
	MALI_IGNORE(ctx);
	return MALI_FALSE;
}

MALI_STATIC_INLINE mali_err_code MALI_CHECK_RESULT _instrumented_register_counter(
    mali_instrumented_context *ctx, u32 id, const char *name,
    const char *description, const char *unit, mali_frequency_scale scale_to_hz)
{
	MALI_IGNORE(ctx);
	MALI_IGNORE(id);
	MALI_IGNORE(name);
	MALI_IGNORE(description);
	MALI_IGNORE(unit);
	MALI_IGNORE(scale_to_hz);
	return MALI_ERR_NO_ERROR;
}

MALI_STATIC_INLINE mali_err_code _instrumented_start_group(mali_instrumented_context *ctx,
        const char *name, const char *description, u32 frequency)
{
	MALI_IGNORE(ctx);
	MALI_IGNORE(name);
	MALI_IGNORE(description);
	MALI_IGNORE(frequency);
	return MALI_ERR_NO_ERROR;
}

MALI_STATIC_INLINE void _instrumented_end_group(mali_instrumented_context *ctx)
{
	MALI_IGNORE(ctx);
}

MALI_STATIC_INLINE void _instrumented_set_counter(u32 id, mali_instrumented_frame *frame, s64 value)
{
	MALI_IGNORE(id);
	MALI_IGNORE(frame);
	MALI_IGNORE(value);
}

MALI_STATIC_INLINE void _instrumented_add_to_counter(u32 id, mali_instrumented_frame *frame, s64 value)
{
	MALI_IGNORE(id);
	MALI_IGNORE(frame);
	MALI_IGNORE(value);
}

MALI_STATIC_INLINE s64 _instrumented_get_counter(u32 id, mali_instrumented_frame *frame)
{
	MALI_IGNORE(id);
	MALI_IGNORE(frame);
	return 0;
}

MALI_STATIC_INLINE mali_bool MALI_CHECK_RESULT _instrumented_is_counter_active(
    mali_instrumented_context *ctx, u32 id)
{
	MALI_IGNORE(ctx);
	MALI_IGNORE(id);
	return MALI_FALSE;
}

#endif /* _MALI_COUNTERS_H_ */

