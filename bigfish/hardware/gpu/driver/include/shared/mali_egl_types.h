/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2010, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * Contains EGL internal types that needs to be shared between APIs.
 */

#ifndef _MALI_EGL_TYPES_H_
#define _MALI_EGL_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * an enum for tagging the surfaces by type
 */
typedef enum
{
	MALI_EGL_WINDOW_SURFACE,
	MALI_EGL_PBUFFER_SURFACE,
	MALI_EGL_PIXMAP_SURFACE,
	MALI_EGL_INVALID_SURFACE /* Used as a dummy argument for setting no surfaces current */
} mali_egl_surface_type;

typedef void (*egl_blob_cache_set_cb)(const void *key, s32 key_size, const void *value, s32 value_size);
typedef s32(*egl_blob_cache_get_cb)(const void *key, s32 key_size, void *value, s32 value_size);

#ifdef __cplusplus
}
#endif

#endif /* _MALI_EGL_TYPES_H_ */
