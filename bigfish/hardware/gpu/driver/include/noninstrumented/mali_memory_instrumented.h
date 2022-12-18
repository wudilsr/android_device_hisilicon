/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2011, 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_MEMORY_INSTRUMENTED_H_
#define _MALI_MEMORY_INSTRUMENTED_H_

#include "mali_instrumented_context_types.h"

MALI_STATIC_INLINE mali_err_code MALI_CHECK_RESULT _mali_memory_instrumented_init(mali_instrumented_context *ctx)
{
	MALI_IGNORE(ctx);
	MALI_SUCCESS;
}

#endif /* _MALI_MEMORY_INSTRUMENTED_H_ */

