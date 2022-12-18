/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _GLES_INSTRUMENTED_H_
#define _GLES_INSTRUMENTED_H_

/* This header contains all the includes needed by the GLES driver to do instrumentation,
 * so we don't have to include them all in every GLES file.
 */

#include "mali_instrumented_context.h"
#include "mali_instrumented_context_types.h"
#include "mali_log.h"
#include "mali_counters.h"
#include "mali_gles_instrumented_types.h"
#include "sw_profiling.h"
#include <gles_context.h>

MALI_STATIC_INLINE mali_err_code MALI_CHECK_RESULT _gles_instrumentation_init(mali_instrumented_context *ctx)
{
	MALI_IGNORE(ctx);
	MALI_SUCCESS;
}

MALI_STATIC_INLINE void _gles_add_instrumented_drawcall_info(mali_instrumented_context *instr_ctx, GLenum mode, GLint count)
{
	MALI_IGNORE(instr_ctx);
	MALI_IGNORE(mode);
	MALI_IGNORE(count);
}

#endif /* _GLES_INSTRUMENTED_H_ */

