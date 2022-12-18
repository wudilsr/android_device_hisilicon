/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2011, 2013-2014 ARM Limited
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
struct vg_context;

/**
 * @brief Global data used by the GLES library but held by EGL
 * (contained within EGL main context).
 *
 * The global data keeps track of current mode of operation
 * (single-threaded or multi-threaded) and the number of client API
 * contexts created.
 *
 * The mode of operation dictates where the current context pointer
 * is stored and how it is to be retrieved when needed. As long as
 * there's only one thread issuing draw commands, the client API
 * will stay in single-threaded mode. In single-thread mode there
 * might be any number of running threads, but only single thread
 * that is doing any rendering.
 *
 * Whenever API invocations from more than one thread is detected,
 * the client API is switched to multi-threaded mode. The presence
 * of multiple threads is checked by comparing caller thread ID
 * against the main thread ID in the client API global data on each
 * invocation of _(gles|vg)_make_current, _(gles|vg)_get_context and
 * * _(gles|vg)_create_context. The main thread ID is stored in the
 * client API global initialization, which happens during the very
 * first EGL call made from a process.
 *
 * In multi-threaded mode the current context is only stored in TLS
 * and always fetched from there. In single-threaded mode the current
 * context is stored in the current.(vg|gles)_context pointer within
 * the global data block. This is to avoid the performance overhead
 * incurred by accessing TLS.
 *
 * Whenever the client API context count goes back to zero, the
 * API is switched back to single-thread mode.
 */
typedef struct egl_client_api_global_data
{
	/** Protects access to num_contexts, multi_context, and nt_context */
	mali_mutex_handle context_mutex;

	/** Current mode of operation/multi-threaded flag. Set to 1 as soon as we
	 *  detect presence of multiple threads. */
	mali_atomic_int multi_threaded;

	/** Thread ID of the thread that issued the very first call to EGL in
	 *  the process */
	mali_atomic_int main_thread;

	/** Number of contexts client contexts created */
	int num_contexts;

	/** The current context (@note single-threaded mode only) */
	void *current_context;
} egl_client_api_global_data;

typedef egl_client_api_global_data egl_gles_global_data;
typedef egl_client_api_global_data egl_vg_global_data;

/* Below are helper functions for VG and GLES to check/set the current mode
 * of operation and to initialize the global data chunk. */

#define MALI_EGL_CLIENT_HELPER_FUNCTIONS(check_mode, init_global_data) \
	MALI_STATIC void check_mode(egl_client_api_global_data* data, u32* mode) \
	{ \
		u32 caller          = _mali_sys_thread_get_current(); \
		u32 multi_thread    = 0; \
		\
		multi_thread = _mali_sys_atomic_get(&data->multi_threaded); \
		\
		if (0 == multi_thread) \
		{ \
			/* switch to multi-threaded mode if invoked from outside \
			           * the main thread */ \
			if (caller != (u32) _mali_sys_atomic_get(&data->main_thread)) \
			{ \
				_mali_sys_atomic_set(&data->multi_threaded, 1); \
				multi_thread = 1; \
			} \
		} \
		\
		/* return the current mode if requested */ \
		if (mode) \
		{ \
			*mode = multi_thread; \
		} \
	} \
	\
	MALI_STATIC mali_err_code init_global_data(egl_client_api_global_data* data) \
	{ \
		if (MALI_NO_HANDLE == data->context_mutex) \
		{ \
			data->context_mutex = _mali_sys_mutex_create(); \
			\
			if (MALI_NO_HANDLE == data->context_mutex) \
			{ \
				return MALI_ERR_FUNCTION_FAILED; \
			} \
			\
			data->num_contexts = 0; \
			data->current_context = NULL; \
			\
			/* start in single-threaded mode. store the caller thread id \
			           * so we can later detect API invocations from other threads */ \
			_mali_sys_atomic_initialize(&data->multi_threaded, 0); \
			_mali_sys_atomic_initialize(&data->main_thread, _mali_sys_thread_get_current()); \
		} \
		\
		MALI_SUCCESS; \
	}

#endif /* MALI_EGL_API_GLOBALS_H */
