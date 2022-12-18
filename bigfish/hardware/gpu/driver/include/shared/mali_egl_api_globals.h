/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2011, 2013-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef MALI_EGL_API_GLOBALS_H
#define MALI_EGL_API_GLOBALS_H

#include <mali_system.h>

#ifndef MALI_INTER_MODULE_API
#define MALI_INTER_MODULE_API
#endif

struct gles_context;

/**
 * @brief Global data used by the GLES library but held by EGL.
 */
typedef struct egl_gles_global_data
{
	/** Protects access to num_contexts, multi_context, and current_context */
	mali_mutex_handle context_mutex;
	/** Number of current GLES contexts */
	u32 num_contexts;
	/** Whether to fall back to TLS to get the context pointer */
	mali_bool multi_context;
	/** The current context, if multi_context is false.
	 * @note Only valid if the current thread has a current context.
	 */
	struct gles_context *current_context;
} egl_gles_global_data;

/**
* @brief Global data used by the VG library but held by EGL.
*/
typedef struct egl_vg_global_data
{
	/** Protects access to num_contexts, multi_context, and current_context */
	mali_mutex_handle context_mutex;
	/** Number of current GLES contexts */
	u32 num_contexts;
	/** Whether to fall back to TLS to get the context pointer */
	mali_bool multi_context;
	/** The current context, if multi_context is false.
	* @note Only valid if the current thread has a current context.
	*/
	struct vg_context *current_context;
} egl_vg_global_data;

#endif /* MALI_EGL_API_GLOBALS_H */

