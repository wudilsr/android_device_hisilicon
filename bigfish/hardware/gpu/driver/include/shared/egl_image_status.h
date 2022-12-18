/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2010, 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


#ifndef _EGL_IMAGE_STATUS_H_
#define _EGL_IMAGE_STATUS_H_

/**
 * GLES return values for EGLImage
 */
enum egl_image_from_gles_surface_status
{
	GLES_SURFACE_TO_EGL_IMAGE_STATUS_NO_ERROR = 0,            /* no error */
	GLES_SURFACE_TO_EGL_IMAGE_STATUS_INVALID_MIPLVL = 1,      /* requested miplevel was invalid */
	GLES_SURFACE_TO_EGL_IMAGE_STATUS_OBJECT_INCOMPLETE = 2,   /* texture/renderbuffer object not complete. */
	GLES_SURFACE_TO_EGL_IMAGE_STATUS_OBJECT_UNAVAILABLE = 3,  /* Chose a texture/renderbuffer object which didn't exist */
	GLES_SURFACE_TO_EGL_IMAGE_STATUS_OBJECT_RESERVED = 4,     /* Chose a texture/renderbufefr object which was reserved from this usage (ie, object #0)  */
	GLES_SURFACE_TO_EGL_IMAGE_STATUS_ALREADY_SIBLING = 5,     /* This object is already a egl image sibling */
	GLES_SURFACE_TO_EGL_IMAGE_STATUS_OOM = 6                  /* Out of memory */
};

/**
 * VG return values for EGLImage
 */
enum egl_image_from_vg_image_status
{
	VG_IMAGE_TO_EGL_IMAGE_STATUS_NO_ERROR        = 0,      /* no error */
	VG_IMAGE_TO_EGL_IMAGE_STATUS_INVALID_HANDLE  = 1,      /* invalid image handle */
	VG_IMAGE_TO_EGL_IMAGE_STATUS_CHILD_IMAGE     = 2,      /* image is a child image */
	VG_IMAGE_TO_EGL_IMAGE_STATUS_ALREADY_SIBLING = 3,      /* the image is already a egl image sibling */
	VG_IMAGE_TO_EGL_IMAGE_STATUS_ERROR           = 4       /* general error */
};

/**
 * GLES targets
 *
 */
enum egl_image_gles_target
{
	GLES_TARGET_UNKNOWN                     = 0,
	GLES_TARGET_TEXTURE_2D                  = 1,
	GLES_TARGET_TEXTURE_CUBE_MAP_POSITIVE_X = 2,
	GLES_TARGET_TEXTURE_CUBE_MAP_NEGATIVE_X = 3,
	GLES_TARGET_TEXTURE_CUBE_MAP_POSITIVE_Y = 4,
	GLES_TARGET_TEXTURE_CUBE_MAP_NEGATIVE_Y = 5,
	GLES_TARGET_TEXTURE_CUBE_MAP_POSITIVE_Z = 6,
	GLES_TARGET_TEXTURE_CUBE_MAP_NEGATIVE_Z = 7,
	GLES_TARGET_RENDERBUFFER                = 8
};


#endif /* _EGL_IMAGE_STATUS_H_ */
