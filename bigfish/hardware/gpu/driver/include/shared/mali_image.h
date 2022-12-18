/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_IMAGE_H_
#define _MALI_IMAGE_H_
#include <mali_system.h>
#include <base/mali_memory.h>
#include <shared/mali_surface.h>
#include <shared/mali_egl_image.h>
#include <shared/mali_named_list.h>

#define MALI_IMAGE_MAX_PLANES     5
#define MALI_IMAGE_MAX_MIPLEVELS 12

#define MALI_EGL_IMAGE_SUPPORT_NATIVE_YUV 1

/**
 * @brief The YUV format list
 */
#if MALI_EGL_IMAGE_SUPPORT_NATIVE_YUV

/* EGL_IMAGE_FORMAT_KHR values */
/* YUV formats */
#define EGL_YUV420P_KHR    0x30F1
#define EGL_YUV420SP_KHR   0x30F2
#define EGL_YVU420SP_KHR   0x30F3
#define EGL_YUV422I_KHR    0x30F4
#define EGL_YUV422P_KHR    0x30F5
#define EGL_YUV444P_KHR    0x30F6
#define EGL_YUV444I_KHR    0x30F7
#define EGL_YV12_KHR       0x30F8
#define EGL_UYVY_KHR       0x30FC

#define EGL_DATA_TYPE_KHR                   0x30D1
#define EGL_ELEMENT_TYPE_KHR                0x30D2
#define EGL_COMPONENTS_KHR                  0x30D3
#define EGL_COMPRESSION_TYPE_KHR            0x30D4
#define EGL_IMAGE_FORMAT_KHR                0x30DA
#define EGL_PREMULTIPLICATION_ORDER_KHR     0x30DB
#define EGL_OPENGL_USE_KHR                  0x30DC
#define EGL_COLOR_RANGE_KHR                 0x30E2

/* EGL_ELEMENT_TYPE_KHR values */
#define EGL_COLOR_KHR               0x30E7
#define EGL_DEPTH_KHR               0x30E8
#define EGL_STENCIL_KHR             0x30E9
#define EGL_DEPTH_STENCIL_KHR       0x30EA

/* EGL_COMPRESSION_TYPE_KHR values */
#define EGL_UNCOMPRESSED_KHR        0x30EB

/* EGL_PREMULTIPLICATION_ORDER_KHR values */
#define EGL_BEFORE_COLORSPACE_CONVERSION_KHR  0x30EE
#define EGL_AFTER_COLORSPACE_CONVERSION_KHR   0x30F0

/* EGL_OPENGL_USE_KHR mask bits */
#define EGL_OPENGL_TEXTURE_BIT_KHR       0x0001
#define EGL_OPENGL_RENDERBUFFER_BIT_KHR  0x0002

#endif

/* fix enum names and wrap the defines in an ifdef */
/* EGL_COLORSPACE additional values */
#define EGL_COLORSPACE_BT_601  0x30EC
#define EGL_COLORSPACE_BT_709  0x30ED

/* EGL_COLOR_RANGE_KHR values */
#define EGL_REDUCED_RANGE_KHR 0x30F9
#define EGL_FULL_RANGE_KHR    0x30FA

/** mali_image error codes */
typedef enum
{
	MALI_IMAGE_ERR_NO_ERROR        = 0,
	MALI_IMAGE_ERR_BAD_ACCESS_MODE = 1,
	MALI_IMAGE_ERR_BAD_BUFFER      = 2,
	MALI_IMAGE_ERR_BAD_ALLOC       = 3,
	MALI_IMAGE_ERR_BAD_LOCK        = 4,
	MALI_IMAGE_ERR_IN_USE          = 5,
	MALI_IMAGE_ERR_BAD_PARAMETER   = 6
} mali_image_err_code;

/** mali_image access modes */
typedef enum
{
	MALI_IMAGE_ACCESS_READ_ONLY  = 1,
	MALI_IMAGE_ACCESS_WRITE_ONLY = 2,
	MALI_IMAGE_ACCESS_READ_WRITE = 4
} mali_image_access_mode;

/** mali_image creation modes */
typedef enum
{
	MALI_IMAGE_CREATED_IMPLICIT     = 0,
	MALI_IMAGE_CREATED_FROM_SURFACE = 1,
	MALI_IMAGE_CREATED_FROM_EXTMEM  = 2
} mali_image_creation_mode;

/** mali_image memory types */
typedef enum
{
	MALI_IMAGE_CPU_MEM   = 0,
	MALI_IMAGE_MALI_MEM  = 2,
	MALI_IMAGE_UMP_MEM   = 3,
	MALI_IMAGE_DMA_BUF   = 4,
} mali_image_memory_type;

/** special image plane ID to use for plane_alias value when plane isn't aliased */
#define MALI_IMAGE_PLANE_INVALID    (u32) (0xFFFFFFFF)

/** mali_image lock session data */
typedef struct mali_image_lock_session
{
	mali_image_access_mode access_mode;
	s32 x, y;
	s32 width, height;
	s32 session_id;
	mali_surface_instance surface_instance;
} mali_image_lock_session;

/** plane specific yuv format info */
typedef struct yuv_format_plane_info
{
	mali_bool active;
	float width_scale;
	float height_scale;
	float pitch_scale;
	m200_texel_format texel_format;
	mali_bool reverse_order;
	mali_bool red_blue_swap;
	u32 plane_alias;
} yuv_format_plane_info;

/** yuv format info for all planes */
typedef struct yuv_format_info
{
	u32 format;
	u32 planes_count;
	/* For some formats like UYVY, U channels can't be fetched to channel #2 anyway.
         * So workaround is we swap both UV planes and UV uniforms used by PP. */
	mali_bool uv_plane_swap;
	yuv_format_plane_info plane[MALI_IMAGE_MAX_PLANES];
} yuv_format_info;

/** mali image data */
typedef struct mali_image
{
	u32 width;
	u32 height;
	u32 miplevels;
	struct mali_surface *pixel_buffer[MALI_IMAGE_MAX_PLANES][MALI_IMAGE_MAX_MIPLEVELS];
	void *userdata; /* custom userdata */
	mali_named_list *locklist; /* list of current locks */
	yuv_format_info *yuv_info; /* attached YUV format specifications, always NULL for non-YUV formats */
	mali_image_creation_mode creation_mode; /* what the image was created from */
	mali_base_ctx_handle base_ctx; /* we often need this, so let's cache it */
	mali_atomic_int references;

	/* Mali EGL Image lock tracking
	 * The loc is be default unlocked (set to 0).
	 * The lock is set (to 1) if calling _mali_image_lock_sync_handle.
	 * The lock is released (to 0) if calling _mali_image_unlock_sync_handle.
	 * The lock is NOT released if the number of users reach 0,
	 * but the lock IS released if that happens while waiting.
	 * The lock is also released if the image is freed. */
	mali_atomic_int mei_locked;


} mali_image;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Verifies that a given YUV format is valid and supported
 * @param yuv_format yuv format, as specified by the EGLImage extension
 * @return MALI_TRUE if supported, MALI_FALSE if not
 */
MALI_IMPORT mali_bool mali_image_supported_yuv_format(u32 yuv_format);

/**
 * @brief Create a Mali image from CPU memory.
 *
 * Creates a Mali image that has one surface of the specified format and
 * dimensions (plane 0, mip level 0). Allocates Mali memory for a new
 * surface. If the @a pitch parameter is 0 then a pitch compatible with
 * Mali GPU alignment restrictions will be calculated from the requested
 * @a width and @a sformat.
 *
 * @param[in] flags       Surface flags. See mali_surface.h for details
 * @param[in] sformat     Format and layout of the surface to be created.
 * @param[in] base_ctx    Mali base context handle.
 * @return mali_image pointer on success, NULL on failure
 * @note It is the caller's responsibility to initialise the content of
 *       the surface allocated by this function, if required.
 */
MALI_IMPORT struct mali_image *mali_image_create_from_cpu_memory(
    enum mali_surface_flags flags,
    const mali_surface_specifier *sformat,
    mali_base_ctx_handle base_ctx);

/**
 * @brief Create a Mali image from UMP or Mali memory.
 *
 * Creates a Mali image with one surface of the specified format and
 * dimensions (plane 0, mip level 0). Does not allocate memory for a new
 * surface. Instead, @a ext_mem specifies a UMP or Mali memory handle and
 * @a offset specifies the number of bytes between the start of that memory
 * and the surface data. The @a width, @a height and @a pitch parameters
 * should match the layout of the surface data or else accessing it will
 * have undefined effects.
 *
 * @param[in] flags       Surface flags. See mali_surface.h for details.
 * @param[in] sformat     Format and layout of the surface to be created.
 * @param[in] memory_type Type of memory from which to create the Mali image
 *                        (Mali or UMP - CPU memory isn't supported).
 * @param[in] ext_mem     UMP or Mali memory handle of a surface to be
 *                        wrapped as a Mali image.
 * @param[in] offset      Offset in bytes from the start of allocated memory
 *                        to the surface data.
 * @param[in] base_ctx    Mali base context handle.
 * @return mali_image pointer on success, NULL on failure
 * @warning Asserts that the specified pitch is compatible with Mali GPU
 *          alignment restrictions.
 */
MALI_IMPORT struct mali_image *mali_image_create_from_ump_or_mali_memory(
    enum mali_surface_flags flags,
    const mali_surface_specifier *sformat,
    mali_image_memory_type memory_type,
    void *ext_mem, u32 offset,
    mali_base_ctx_handle base_ctx);

/**
 * @brief Looks up YUV format info
 * @param yuv_format the YUV format to look up
 * @return yuv_format_into pointer on success, NULL else
 */
yuv_format_info *mali_image_get_yuv_info(u32 yuv_format);

/**
 * @brief Creates a mali_image from a given set of parameters
 * @param miplevels number of miplevels to be used in image
 * @param flags surface flags. See mali_surface.h for details.
 * @param sformat the surface format to be used in image (must be specified also for YUV format)
 * @param yuv_format the YUV format to be used in image (can be 0 if not a YUV format)
 * @param base_ctx base context handle
 * @return mali_image pointer on success, NULL on failure
 */
MALI_IMPORT mali_image *mali_image_create(u32 miplevels, enum mali_surface_flags flags,  mali_surface_specifier *sformat, u32 yuv_format, mali_base_ctx_handle base_ctx);

/**
 * @brief Create a Mali image from external memory.
 *
 * Creates a Mali image with one surface of the specified format and
 * dimensions (plane 0, mip level 0). When called with MALI_IMAGE_CPU_MEM
 * as the @a memory_type, it allocates Mali memory for the surface and
 * @a ext_mem must be NULL. Otherwise, the @a ext_mem parameter specifies
 * a UMP or Mali memory handle and the surface data to be wrapped is
 * assumed to be at the start of this memory block.
 *
 * @param[in] width       Width of the image, in pixels.
 * @param[in] height      Height of the image, in pixels.
 * @param[in] flags       Surface flags. See mali_surface.h for details.
 * @param[in] sformat     Format and layout of the surface to be created.
 * @param[in] ext_mem     UMP or Mali memory handle of a surface to be
 *                        wrapped as a Mali image, or NULL if using
 *                        MALI_IMAGE_CPU_MEM.
 * @param[in] memory_type Type of memory from which to create the Mali image
 *                        (CPU, Mali or UMP).
 * @param[in] base_ctx    Mali base context handle.
 * @return mali_image pointer on success, NULL on failure
 * @note    It is the caller's responsibility to initialise the content of
 *          the surface allocated by this function if MALI_IMAGE_CPU_MEM.
 * @warning This function guesses the pitch (bytes per line) of the surface
 *          from the @a width and @a sformat parameters. The result may not
 *          match the surface layout and may cause an assertion failure if
 *          incompatible with Mali GPU alignment restrictions.
 */
MALI_IMPORT mali_image *mali_image_create_from_external_memory(u32 width, u32 height,
        enum mali_surface_flags flags,
        mali_surface_specifier *sformat, void *ext_mem,
        mali_image_memory_type memory_type,
        mali_base_ctx_handle base_ctx);

/**
 * @brief Creates a mali_image from an existing mali_surface
 * @param surface pointer to mali_surface
 * @param base_ctx base context handle
 * @return valid mali_image pointer on success, NULL on failure
 * @ntoe This assumes that plane 0, miplevel 0 is used only
 */
MALI_IMPORT mali_image *mali_image_create_from_surface(mali_surface *surface, mali_base_ctx_handle base_ctx);

/**
 * @brief Sets the data for a given plane and miplevel inside a mali image
 * @param image image to set data for
 * @param plane the plane to set data for
 * @param miplevel the miplevel to set data for
 * @param data pointer to data
 * @note Requires usage of UMP
 */
MALI_IMPORT mali_image_err_code mali_image_set_data(mali_image *image, u32 plane, u32 miplevel, u32 offset, void *data);

/**
 * @brief Releases the mali image resources
 * @param image image to release
 * @note make sure that all references has been removed before calling this
 */
MALI_IMPORT void mali_image_release(mali_image *image);

/**
 * @brief Dereferences mali image resources
 * @param image mali image to dereference
 * @return MALI_TRUE if image has no more references, EGL_FALSE if it still has references
 * @note MALI_FALSE will be returned if any of the internal surfaces are in use
 */
MALI_IMPORT mali_bool mali_image_deref(mali_image *image);

/**
 * @brief Removes references to all contained mali_surfaces
 * @param image The mali_image containing the mali_surfaces
 */
MALI_IMPORT void mali_image_deref_surfaces(mali_image *image);

/**
 * @brief Allocates data, if needed, for a given buffer.
 * @param image image to allocate buffer in
 * @param plane the plane to allocate buffer in
 * @param miplevel the miplevel to allocate buffer in
 * @return MALI_TRUE on success, MALI_FALSE on failure
 * @note failures indicates an OOM situation
 * @note size of buffer allocated will depend on given plane and miplevel
 */
MALI_IMPORT mali_bool mali_image_allocate_buffer(mali_image *image, u32 plane, u32 miplevel);

/**
 * @brief Allocates all active data buffers in an image
 * @param image pointer to image
 * @return MALI_TRUE on success, MALI_FALSE on failure
 */
MALI_IMPORT mali_bool mali_image_allocate_buffers(mali_image *image);

/**
 * @brief Verifies / retrieves a buffer based on given plane and mipmap level
 * @param image image to get buffer from
 * @param plane plane in image to get buffer from
 * @param mipmap mipmap level in image to get buffer from
 * @param exclude_aliased_buffers will exclude buffers which are aliased, and return NULL if such a buffer is requested
 * @return pointer to mali_surface on success, NULL pointer on failure
 */
MALI_IMPORT mali_surface *mali_image_get_buffer(mali_image *image, u32 plane, u32 mipmap, mali_bool exclude_aliased_buffers);

/**
 * @brief Locks a region of an image buffer
 * @param image pointer to mali_image
 * @param access_mode access mode rights
 * @param plane plane in image to lock
 * @param miplevel mipmap level in image to lock
 * @param x x position to acquire lock for
 * @param y y position to acquire lock for
 * @param width the width to acquire lock for
 * @param height the height to acquire lock for
 * @param multiple_write_locks_allowed multiple writelocks will not be allowed if set to true
 * @param multiple_read_locks_allowed multiple readlocks will not be allowed if set to true
 * @param session_id storage for the unique session id representing the lock/map
 * @param data storage for the returned pointer to buffer
 * @note if zero is given for width or height, it is assumed that the whole buffer is to be locked
 */
MALI_IMPORT mali_image_err_code mali_image_lock(mali_image *image,
        mali_image_access_mode access_mode,
        u16 plane, u16 miplevel,
        s32 x, s32 y, s32 width, s32 height,
        mali_bool multiple_write_locks_allowed,
        mali_bool multiple_read_locks_allowed,
        s32 *session_id, void **data);

/**
 * @brief Unlocks a region of an image buffer
 * @param image pointer to mali_image
 * @param plane plane in image to lock
 * @param miplevel mipmap level in image to lock
 * @param x x position to acquire lock for
 * @param y y position to acquire lock for
 * @param width the width to acquire lock for
 * @param height the height to acquire lock for
 * @param session_id the unique session id returned by mali_image_lock
 * @note if zero is given for width or height, it is assumed that the whole buffer is to be unlocked
 * @note giving a rectangle larger than the lock area will give a MALI_IMAGE_ERR_BAD_PARAMETER,
 *       but region is still unlocked
 */
MALI_IMPORT mali_image_err_code mali_image_unlock(mali_image *image,
        u16 plane, u16 miplevel,
        s32 x, s32 y, s32 width, s32 height,
        s32 session_id);

/**
 * @brief Unlocks all sessions in mali_image
 * @param image pointer to mali_image
 */
MALI_IMPORT mali_image_err_code mali_image_unlock_all_sessions(mali_image *image);

/**
 * @brief Checks if surface is mapped (ie. has a locked area)
 * @param image pointer to image
 * @param surface pointer to surface
 * @return MALI_TRUE if mapped, MALI_FALSE else
 */
MALI_IMPORT mali_bool mali_image_surface_is_mapped(mali_image *image, mali_surface *surface);

/**
 * @brief Creates a sync handle
 * @param surface pointer to an image
 * @return MALI_TRUE on success, MALI_FALSE on error
 */
MALI_IMPORT mali_bool _mali_image_create_sync_handle(struct mali_image *surface);

/**
 * @brief Locks a sync handle
 * @param surface pointer to the image to lock
 * @return MALI_TRUE if sync handle was locked successfully, MALI_FALSE else
 */
MALI_IMPORT mali_bool _mali_image_lock_sync_handle(mali_image *surface);

/**
 * @brief Unlocks a sync handle
 * @param surface pointer to the image to unlock
 * @return MALI_TRUE on success, MALI_FALSE else
 */
MALI_IMPORT mali_bool _mali_image_unlock_sync_handle(mali_image *surface);




#ifdef __cplusplus
}
#endif

#endif /* _MALI_IMAGE_H_ */
