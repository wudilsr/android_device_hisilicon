/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * API for modifying EGLImage data
 *
 */

#ifndef _MALI_EGL_IMAGE_H_
#define _MALI_EGL_IMAGE_H_

/**
 * @addtogroup eglcore_image EGL core EGLImageKHR API
 *
 * @{
 */

/**
 * @defgroup eglcore_image_mali mali_egl_image API
 *
 * @note mali_egl_image API
 *
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <base/mali_macros.h>
#include <EGL/mali_egl.h>
#include <EGL/mali_eglext.h>

/**
 * An opaque handle to the EGLImage structure
 */
typedef void *mali_egl_image;
#define MALI_EGL_IMAGE_NONE 0x0

/** Versioning */
typedef enum
{
	MALI_EGL_IMAGE_VERSION_1_0 = 1,
	MALI_EGL_IMAGE_VERSION_HEAD = MALI_EGL_IMAGE_VERSION_1_0
} mali_egl_image_version;

/**
 * The miplevel attribute
 * Legal values : [0, 12]
 * Default value: 0
 */
#define MALI_EGL_IMAGE_MIPLEVEL 0x00FA

/**
 * The image plane attribute
 * Legal values : @see ImagePlaneValues
 * Default value: MALI_EGL_IMAGE_PLANE_Y
 */
#define MALI_EGL_IMAGE_PLANE 0x00FB

/**
 * @defgroup MaliEGLImagePlaneValues Mali EGLImage Plane Values
 * @{
 */
#define MALI_EGL_IMAGE_PLANE_Y   0x0100
#define MALI_EGL_IMAGE_PLANE_U   0x0101
#define MALI_EGL_IMAGE_PLANE_V   0x0102
#define MALI_EGL_IMAGE_PLANE_UV  0x0103
#define MALI_EGL_IMAGE_PLANE_YUV 0x0104
#define MALI_EGL_IMAGE_PLANE_RGB MALI_EGL_IMAGE_PLANE_Y
/** @} */

#define MALI_EGL_IMAGE_LAYOUT    0x00F3
/**
 * @defgroup MaliEGLImageLayoutValues Mali EGLImage Layout Values
 * @{
 */
#define MALI_EGL_IMAGE_LAYOUT_LINEAR                0x0110
#define MALI_EGL_IMAGE_LAYOUT_BLOCKINTERLEAVED      0x0112
/** @} */


#define MALI_EGL_IMAGE_COLORSPACE                   0x00F4
/**
 * @defgroup MaliEGLImageColorspaceValues Mali EGLImage Colorspace Values
 * @{
 */
#define MALI_EGL_IMAGE_COLORSPACE_LINEAR            0x1
#define MALI_EGL_IMAGE_COLORSPACE_SRGB              0x2
#define MALI_EGL_IMAGE_COLORSPACE_BT_601            EGL_COLORSPACE_BT_601
#define MALI_EGL_IMAGE_COLORSPACE_BT_709            EGL_COLORSPACE_BT_709
/** @} */


#define MALI_EGL_IMAGE_RANGE                        0x00F5
/**
 * @defgroup MaliEGLImageColorrangeValues Mali EGLImage Colorrange Values
 * @{
 */
#define MALI_EGL_IMAGE_RANGE_FULL                   0x1
#define MALI_EGL_IMAGE_RANGE_REDUCED                0x2
/** @} */


#define MALI_EGL_IMAGE_FORMAT                       0x00F6
/**
 * @defgroup MaliEGLImageFormatValues Mali EGLImage Format Values
 * @{
 */
#define MALI_EGL_IMAGE_FORMAT_YUV420_PLANAR         0x1
/** @} */


#define MALI_EGL_IMAGE_ALPHA_FORMAT                 0x00F7
/**
 * @defgroup MaliEGLImageAlphaFormatValues Mali EGLImage Alpha Format Values
 * @{
 */
#define MALI_EGL_IMAGE_ALPHA_PRE                    0x1
#define MALI_EGL_IMAGE_ALPHA_NONPRE                 0x2
/** @} */


#define MALI_EGL_IMAGE_WIDTH                        0x00F8
#define MALI_EGL_IMAGE_HEIGHT                       0x00F9

#define MALI_EGL_IMAGE_ALLOCATE_IMAGE_DATA          0x00FA

/**
 * @defgroup MaliEGLImageColorDepthAttributes Mali EGLImage Color Depth Attributes
 * @{
 */
#define MALI_EGL_IMAGE_BITS_R                       0x1000
#define MALI_EGL_IMAGE_BITS_G                       0x1001
#define MALI_EGL_IMAGE_BITS_B                       0x1002
#define MALI_EGL_IMAGE_BITS_A                       0x1003
/** @} */



/**
 * @defgroup MaliEGLImageErrorCodes Mali EGLImage Error Codes
 * @{
 */
#define MALI_EGL_IMAGE_SUCCESS        0x4001
#define MALI_EGL_IMAGE_BAD_IMAGE      0x4002
#define MALI_EGL_IMAGE_BAD_LOCK       0x4003
#define MALI_EGL_IMAGE_BAD_MAP        0x4004
#define MALI_EGL_IMAGE_BAD_ACCESS     0x4005
#define MALI_EGL_IMAGE_BAD_ATTRIBUTE  0x4006
#define MALI_EGL_IMAGE_IN_USE         0x4007
#define MALI_EGL_IMAGE_BAD_PARAMETER  0x4008
#define MALI_EGL_IMAGE_BAD_POINTER    0x4009
#define MALI_EGL_IMAGE_SYNC_TIMEOUT   0x4010
#define MALI_EGL_IMAGE_BAD_VERSION    0x4011
#define MALI_EGL_IMAGE_OUT_OF_MEMORY  0x4012
/** @} */

/**
 * The access mode attribute
 * Legal values : @see MaliEGLImageAccessModes
 * Default value: MALI_EGL_IMAGE_ACCESS_READ_WRITE
 */
#define MALI_EGL_IMAGE_ACCESS_MODE           0x00FC

/**
 * @defgroup MaliEGLImageAccessModes Mali EGLImage Access Modes
 * @{
 */
#define MALI_EGL_IMAGE_ACCESS_READ_ONLY      0x1
#define MALI_EGL_IMAGE_ACCESS_WRITE_ONLY     0x2
#define MALI_EGL_IMAGE_ACCESS_READ_WRITE     0x4
/** @} */

/**
 * @defgroup MaliEGLImageSync Mali EGLImage Sync
 * @{
 */
#define MALI_EGL_IMAGE_WAIT_FOREVER 0x0
/** @} */


/**
 * Initializes mali_egl_image
 *
 * @param version the version of mali_egl_image to use
 * @note the head version is used by default
 */
MALI_IMPORT EGLBoolean mali_egl_image_init(mali_egl_image_version version);

/**
 * Retrieves the error code set by the most recent API function called.
 *
 * @see MaliEGLImageErrorCodes for a list of possible error values.
 *
 * @return an error code
 */
MALI_IMPORT EGLint mali_egl_image_get_error(void);

/**
 * Retrieves an mali_egl_image pointer from an EGLImageKHR handle, and locks it for
 * external access.
 *
 * This must be matched by a later call to mali_egl_image_unlock_ptr.
 *
 * If the function fails, a NULL pointer will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_IMAGE if <image> is not valid
 * MALI_EGL_IMAGE_BAD_LOCK if <image> is already locked
 *
 * @param image - an EGLImageKHR handle
 * @return an opaque pointer to a mali_egl_image structure
 */
MALI_IMPORT mali_egl_image *mali_egl_image_lock_ptr(EGLImageKHR image);

/**
 * Signals that external access is complete.
 *
 * When this function returns, the pointer returned by mali_egl_image_lock_ptr
 * becomes invalid.
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_IMAGE if <image> is not valid
 * MALI_EGL_IMAGE_BAD_LOCK if <image> is not locked
 *
 * @note If the image is mapped (after a successful call to mali_egl_image_map_buffer), then
 * the image will be unmapped automatically.
 *
 * @param image - an EGLImageKHR handle
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_unlock_ptr(EGLImageKHR image);

/**
 * Replaces the color buffer data specified in the attribs list with a custom data pointer
 * The given pointer has to be allocated through UMP, and will need to be of same dimensions
 * as the specified buffer.
 *
 * @note This must be done prior to any use of the EGLImageKHR handle
 * @note This is to be used with the new EGLImageKHR extension, where you initially
 * do not have any data allocated
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_ATTRIBUTE if <attribs> contain invalid attributes
 * MALI_EGL_IMAGE_BAD_ACCESS if <attribs> specifies a buffer that is not present in <image>
 * MALI_EGL_IMAGE_BAD_ACCESS if the specified buffer is currently mapped
 * MALI_EGL_IMAGE_BAD_PARAMETER if <data> is NULL, or a non-UMP compatible pointer
 * MALI_EGL_IMAGE_IN_USE if <image> is in use by any other API
 *
 * @param image - an opaque pointer to an EGLImage
 * @param attribs - specifies which buffer to access
 * @param data - the buffer data
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_set_data(mali_egl_image *image, EGLint *attribs, void *data);

/**
 * Retrieves the width of an EGLImage.
 *
 * This function requires that the EGLImageKHR handle is locked
 * (using mali_egl_image_lock_ptr), but does not require
 * the buffer to be mapped.
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_LOCK if <image> is not locked
 * MALI_EGL_IMAGE_BAD_PARAMETER if <width> is NULL.
 *
 * @param image - an opaque pointer to an EGLImage
 * @param width - a pointer to an integer where the width will be written
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_get_width(mali_egl_image *image, EGLint *width);

/**
 * @see mali_egl_image_get_width
 */
MALI_IMPORT EGLBoolean mali_egl_image_get_height(mali_egl_image *image, EGLint *height);

/**
 * Retrieves the format of an EGLImage.
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_LOCK if <image> is not locked
 * MALI_EGL_IMAGE_BAD_PARAMETER if <format> is NULL.
 *
 * @param image - an opaque pointer to an EGLImage
 * @param format - a pointer to an integer that will store the format
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_get_format(mali_egl_image *image, EGLint *format);

/**
 * Maps a specific buffer for read/write access.
 *
 * This must be matched by a later call to mali_egl_image_unmap_buffer.
 *
 * If the function fails, a NULL-pointer will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_ACCESS if <attribs> specifies a buffer that is not present in <image>
 * MALI_EGL_IMAGE_BAD_MAP if <image> is already mapped
 * MALI_EGL_IMAGE_IN_USE if <image> is in use by any other API
 *
 * @param image - an opaque pointer to an EGLImage
 * @param attribs - specifies which buffer to access
 * @return a pointer to the data for the specific buffer, or NULL on failure
 */
MALI_IMPORT void *mali_egl_image_map_buffer(mali_egl_image *image, EGLint *attribs);

/**
 * Unmaps a specific buffer.
 *
 * When this function returns the pointer returned by mali_egl_image_map_buffer
 * becomes invalid.
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_ACCESS if <attribs> specifies a buffer that is not present in <image>
 * MALI_EGL_IMAGE_BAD_MAP if <image> is not mapped
 *
 * @param image - an opaque pointer to an EGLImage
 * @param attribs - specifies which buffer to access
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_unmap_buffer(mali_egl_image *image, EGLint *attribs);

/**
 * Retrieves the width of a buffer in an EGLImage.
 *
 * This function requires that the EGLImage handle is locked
 * (@see mali_egl_image_lock_ptr), but does not require
 * the buffer to be mapped.
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_PARAMETER if <width> is NULL
 * MALI_EGL_IMAGE_BAD_ACCESS if <attribs> specifies a buffer that is not present in <image>
 *
 * @note If no attributes are given (attribs is NULL) the size of a
 * 'default' buffer will be returned (miplevel 0 of the first plane (RGBA, or Y))
 *
 * @param image - an opaque pointer to an EGLImage
 * @param attribs - attributes used to select a given buffer
 * @param width - a pointer to an integer that will store the width
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_get_buffer_width(mali_egl_image *image, EGLint *attribs, EGLint *width);

/**
 * @see mali_egl_image_get_buffer_width
 */
MALI_IMPORT EGLBoolean mali_egl_image_get_buffer_height(mali_egl_image *image, EGLint *attribs, EGLint *height);

/**
 * Retrieves the UMP secure ID in an EGLImage.
 *
 * This function requires that the EGLImage handle is locked
 * (@see mali_egl_image_lock_ptr), but does not require
 * the buffer to be mapped.
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_PARAMETER if <secure_id> is NULL, or if given EGLImage is not allocated through UMP
 * MALI_EGL_IMAGE_BAD_ACCESS if <attribs> specifies a buffer that is not present in <image>
 * MALI_EGL_IMAGE_BAD_MAP if there are no support for UMP in client API
 *
 * @note If no attributes are given (attribs is NULL) the UMP secure ID of a
 * 'default' buffer will be returned (miplevel 0 of the first plane (RGBA, or Y))
 *
 * @param image - an opaque pointer to an EGLImage
 * @param attribs - attributes used to select a given buffer
 * @param secure_id - a pointer to an integer that will store the UMP secure ID
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_get_buffer_secure_id(mali_egl_image *image, EGLint *attribs, EGLint *secure_id);

/**
 * Retrieves the layout of a buffer in an EGLImage.
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_PARAMETER if <layout> is NULL
 * MALI_EGL_IMAGE_BAD_ACCESS if <attribs> specifies a buffer that is not present in <image>
 *
 * @param image - an opaque pointer to an EGLImage
 * @param attribs - specifies which buffer to access
 * @param layout - a pointer to an integer that will store the layout
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_get_buffer_layout(mali_egl_image *image, EGLint *attribs, EGLint *layout);

/**
 * Retrieves the number of mipmap levels in an EGLImage.
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_PARAMETER if <layout> is NULL
 *
 * @param image - an opaque pointer to an EGLImage
 * @param miplevels - a pointer to an integer that will store the layout
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_get_miplevels(mali_egl_image *image, EGLint *miplevels);

/**
 * Creates a synchronization lock for a given EGLImage
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_ACCESS if synchronization lock could not be created
 *
 * @param image - an opaque pointer to an EGLImage
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_create_sync(mali_egl_image *image);

/**
 * Sets a synchronization lock active for a given EGLImage
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_LOCK if synchronization lock could not be locked
 *
 * @param image - an opaque pointer to an EGLImage
 * @return EGL_TRUE if synchronization handle was locked, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_set_sync(mali_egl_image *image);

/**
 * Sets a synchronization lock not active for a given EGLImage
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_BAD_LOCK if synchronization lock could not be unlocked
 *
 * @param image - an opaque pointer to an EGLImage
 * @return EGL_TRUE on success, EGL_FALSE on failure
 */
MALI_IMPORT EGLBoolean mali_egl_image_unset_sync(mali_egl_image *image);

/**
 * Waits for a given synchronization lock to become inactive
 *
 * If the function fails, EGL_FALSE will be returned, and an
 * error code will be set as follows:
 * MALI_EGL_IMAGE_BAD_POINTER if <image> is not a valid pointer
 * MALI_EGL_IMAGE_SYNC_TIMEOUT if <timeout> expires
 *
 * @param image - an opaque pointer to an EGLImage
 * @param timeout timeout to wait for lock (microseconds) or MALI_EGL_IMAGE_WAIT_FOREVER
 * @return EGL_TRUE if lock became inactive, EGL_FALSE in case of a timeout
 */
MALI_IMPORT EGLBoolean mali_egl_image_wait_sync(mali_egl_image *image, EGLint timeout);

/**
* Creates an EGLImage matching the specified attributes.
*
* The created image will have no siblings.
*
* Attribute Default Value Legal Values
* -----------------------------------------------------------------------------------------------------
*
* MALI_EGL_IMAGE_WIDTH 0 [0-4096]
* MALI_EGL_IMAGE_HEIGHT 0 [0-4096]
* MALI_EGL_IMAGE_ALLOCATE_IMAGE_DATA EGL_TRUE EGL_TRUE/EGL_FALSE
* MALI_EGL_IMAGE_FORMAT MALI_EGL_IMAGE_PLANE_RGB MALI_EGL_IMAGE_PLANE_RGB |
* MALI_EGL_IMAGE_FORMAT_YUV422_INTERLEAVED MALI_EGL_IMAGE_FORMAT_YUV420_PLANAR MALI_EGL_IMAGE_FORMAT_YUV420_SEMIPLANAR
* MALI_EGL_IMAGE_LAYOUT MALI_EGL_IMAGE_LAYOUT_LINEAR MALI_EGL_IMAGE_LAYOUT_LINEAR|MALI_EGL_IMAGE_LAYOUT_INTERLEAVED|MALI_EGL_IMAGE_LAYOUT_BLOCKINTERLEAVED
* MALI_EGL_IMAGE_RANGE MALI_EGL_IMAGE_RANGE_REDUCED MALI_EGL_IMAGE_RANGE_FULL|MALI_EGL_IMAGE_RANGE_REDUCED
* MALI_EGL_IMAGE_COLORSPACE MALI_EGL_IMAGE_COLORSPACE_SRGB MALI_EGL_IMAGE_COLORSPACE_LINEAR|MALI_EGL_IMAGE_COLORSPACE_SRGB|MALI_EGL_IMAGE_COLORSPACE_BT_601|MALI_EGL_IMAGE_COLORSPACE_BT_709
* MALI_EGL_IMAGE_ALPHA_FORMAT MALI_EGL_IMAGE_ALPHA_PRE MALI_EGL_IMAGE_ALPHA_PRE|MALI_EGL_IMAGE_ALPHA_NONPRE
* MALI_EGL_IMAGE_BITS_R 0 [0-8]
* MALI_EGL_IMAGE_BITS_G 0 [0-8]
* MALI_EGL_IMAGE_BITS_B 0 [0-8]
* MALI_EGL_IMAGE_BITS_A 0 [0-8]
*
* MALI_EGL_IMAGE_BITS_[R,G,B,A] is ignored unless MALI_EGL_IMAGE_FORMAT is MALI_EGL_IMAGE_PLANE_RGB.
* MALI_EGL_IMAGE_RANGE will be ignored if MALI_EGL_IMAGE_FORMAT is MALI_EGL_IMAGE_PLANE_RGB.
*
* If the value of MALI_EGL_IMAGE_ALLOCATE_IMAGE_DATA is EGL_FALSE, no memory will be
* allocated for the image data when the EGLImage is created. The image data must be
* specified by calling mali_egl_image_set_data prior to using the EGLImage.
*
* If the function fails, EGL_FALSE will be returned, and an
* error code will be set as follows:
*
* MALI_EGL_IMAGE_BAD_ATTRIBUTE if <attribs> contain invalid attributes
* MALI_EGL_IMAGE_BAD_PARAMETER if any attribute in <attrib> has an illegal value
* MALI_EGL_IMAGE_OUT_OF_MEMORY if there was not enough memory to allocate the image
*
* @note EGLImages created by this function can only be destroyed by mali_egl_image_destroy.
*
* @param display - handle to EGLDisplay
* @param attribs - a set of attributes that specify the format of the image
* @return A valid EGLImageKHR handle on success, EGL_NO_IMAGE_KHR on failure.
*/
MALI_IMPORT EGLImageKHR mali_egl_image_create(EGLDisplay display, EGLint *attribs);

/**
* Destroys an EGLImage previously created by mali_egl_image_create.
* Siblings of the EGLImage will still be valid after this call, but <image>
* will no longer be a valid EGLImage handle.
*
* If the function fails, EGL_FALSE will be returned, and an
* error code will be set as follows:
* MALI_EGL_IMAGE_BAD_IMAGE if <image> is not a valid EGLImageKHR returned by mali_egl_image_create.
* MALI_EGL_IMAGE_BAD_LOCK if <image> is currently locked by mali_egl_image_lock_ptr
*
* @param image - a handle to an EGLImage
* @return EGL_TRUE if the EGLImage was successfully deleted, EGL_FALSE if not.
*/
MALI_IMPORT EGLBoolean mali_egl_image_destroy(EGLImageKHR image);

#ifdef __cplusplus
}
#endif

/** @} */ /* end group eglcore_image */
/** @} */ /* end group eglcore_image_mali */

#endif /* _MALI_EGL_IMAGE_H_ */
