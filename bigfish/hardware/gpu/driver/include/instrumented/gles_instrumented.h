/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2012-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _GLES_INSTRUMENTED_H_
#define _GLES_INSTRUMENTED_H_

#include "mali_instrumented_context.h"
#include "mali_log.h"
#include "mali_counters.h"
#include "mali_gles_instrumented_types.h"
#include "sw_profiling.h"
#include <gles_context.h>

/**
 * @brief Initializes the OpenGL ES software counters and groups.
 * @param ctx The instrumented context to add the OpenGL ES software counters and groups to
 * @param api_version The OpenGL ES API version (For example 1.x or 2.x)
 * @return An error if the initialization of the OpenGL ES software counter tree failed
 */
MALI_IMPORT
mali_err_code _gles_instrumentation_init(mali_instrumented_context *ctx) MALI_CHECK_RESULT;

/**
 * @brief Adds instrumented info about drawcalls
 * @param inst_ctx The instrumented context
 * @param mode the drawmode (LINES, POINTS, TRIANGLES, TRIANGLE_STRIP etc) of this drawcall
 */
MALI_STATIC_INLINE void _gles_add_instrumented_drawcall_info(mali_instrumented_context *instr_ctx, GLenum mode, GLint count)
{
	MALI_IGNORE(instr_ctx);

	switch (mode)
	{
		case GL_POINTS:
			_profiling_count(INST_GL_DRAW_POINTS, 1);
			_profiling_count(INST_GL_POINTS_COUNT, count);
			break;

		case GL_LINES:
			_profiling_count(INST_GL_DRAW_LINES, 1);
			_profiling_count(INST_GL_LINES_COUNT, count / 2);
			_profiling_count(INST_GL_INDEPENDENT_LINES_COUNT, count / 2);
			break;

		case GL_LINE_LOOP:
			_profiling_count(INST_GL_DRAW_LINE_LOOP, 1);
			_profiling_count(INST_GL_LINES_COUNT, count);
			_profiling_count(INST_GL_LOOP_LINES_COUNT, count);
			break;

		case GL_LINE_STRIP:
			_profiling_count(INST_GL_DRAW_LINE_STRIP, 1);
			_profiling_count(INST_GL_LINES_COUNT, count - 1);
			_profiling_count(INST_GL_STRIP_LINES_COUNT, count - 1);
			break;

		case GL_TRIANGLES:
			_profiling_count(INST_GL_DRAW_TRIANGLES, 1);
			_profiling_count(INST_GL_TRIANGLES_COUNT, count / 3);
			_profiling_count(INST_GL_INDEPENDENT_TRIANGLES_COUNT, count / 3);
			break;

		case GL_TRIANGLE_STRIP:
			_profiling_count(INST_GL_DRAW_TRIANGLE_STRIP, 1);
			_profiling_count(INST_GL_TRIANGLES_COUNT, count - 2);
			_profiling_count(INST_GL_STRIP_TRIANGLES_COUNT, count - 2);
			break;

		case GL_TRIANGLE_FAN:
			_profiling_count(INST_GL_DRAW_TRIANGLE_FAN, 1);
			_profiling_count(INST_GL_TRIANGLES_COUNT, count - 2);
			_profiling_count(INST_GL_FAN_TRIANGLES_COUNT, count - 2);
			break;
	}
}

#endif /* _GLES_INSTRUMENTED_H_ */

