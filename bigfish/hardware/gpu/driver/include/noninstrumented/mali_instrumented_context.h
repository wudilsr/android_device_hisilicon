/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2012-2013, 2015 ARM Limited
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


MALI_STATIC_INLINE void *MALI_CHECK_RESULT _instrumented_create_context(void)
{
	return NULL;
}

MALI_STATIC_INLINE void _instrumented_destroy_context(void)
{
}

MALI_STATIC_INLINE void _instrumented_finish_init(void)
{
}

MALI_STATIC_INLINE void _instrumented_destroy_tls(void)
{
}

MALI_STATIC_INLINE mali_instrumented_tls_struct *_instrumented_get_tls(void)
{
	return NULL;
}

MALI_STATIC_INLINE mali_instrumented_context *_instrumented_get_context(void)
{
	return NULL;
}

MALI_STATIC_INLINE mali_instrumented_frame *_instrumented_get_current_frame(void)
{
	return NULL;
}

MALI_STATIC_INLINE mali_instrumented_frame *_instrumented_acquire_current_frame(void)
{
	return NULL;
}

#endif /* _MALI_INSTRUMENTED_CONTEXT_H_ */

