/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef MALI_FRAME_BUILDER_H
#define MALI_FRAME_BUILDER_H

#include <mali_system.h>
#include <base/pp/mali_pp_job.h>
#include <base/gp/mali_gp_job.h>
#include <base/mali_memory.h>
#include <mali_instrumented_context_types.h>
#include <regs/MALI200/mali200_core.h>
#include <regs/MALIGP2/mali_gp_plbu_cmd.h>
#include <shared/mali_mem_pool.h>

/* helpers to calculate the supersample scaling factors */
#define SUPERSAMPLE_SCALE_X( factor ) (1 << ((factor) >> 1))
#define SUPERSAMPLE_SCALE_Y( factor ) (1 << (( (factor) >> 1) + ((factor) & 0x1)))

/* forward declarations */
typedef struct mali_frame_builder mali_frame_builder;
struct mali_surface;

typedef u64 mali_tilelist_cmd; /**< one tile list entry */

/**
 * Framebuilder allocation properties.
 * These can be combined into a bitfield for the framebuilder constructor.
 */
enum mali_frame_builder_properties
{
	/** No flags present. This is the default behavior if no flags are specified. */
	MALI_FRAME_BUILDER_PROPS_NONE                 = 0,
	/**
	 * If set, the framebuilder will allocate a PLBU heap.
	 * If it is known that the framebuilder will only be used to draw very simple geometry,
	 * this flag should not be set.
	 */
	MALI_FRAME_BUILDER_PROPS_NOT_ALLOCATE_HEAP        = (1 << 0),

	/**
	 * If set, a swapbuffer makes all buffer_state_per_plane bits undefined.
	 * If this is not set, a swapbuffer makes all buffer_state_per_plane defined, but unchanged.
	 */
	MALI_FRAME_BUILDER_PROPS_UNDEFINED_AFTER_SWAP = (1 << 1)
};

/**
 *  Framebuilder types available in the driver. Should you add anything to this enum, make
 *  sure you update the timeline profiling tool as well.
 */
enum mali_frame_builder_type
{
	MALI_FRAME_BUILDER_TYPE_UNKNOWN                 = 0,
	MALI_FRAME_BUILDER_TYPE_EGL_SURFACE             = 1,  /* deprecated, replaced by the 3 differentiating WINDOW/PIXMAP/PBUFFER values */
	MALI_FRAME_BUILDER_TYPE_GLES_FRAMEBUFFER_OBJECT = 2,
	MALI_FRAME_BUILDER_TYPE_GLES_TEXTURE_UPLOAD     = 3,
	MALI_FRAME_BUILDER_TYPE_VG_RENDERCHAIN          = 4,
	MALI_FRAME_BUILDER_TYPE_VG_MASKBUFFER           = 5,
	MALI_FRAME_BUILDER_TYPE_EGL_WINDOW              = 6,
	MALI_FRAME_BUILDER_TYPE_EGL_PBUFFER             = 7,
	MALI_FRAME_BUILDER_TYPE_EGL_PIXMAP              = 8,
	MALI_FRAME_BUILDER_TYPE_EGL_COMPOSITOR          = 9,

	/* reserving the topmost bit in the type byte for PILOT JOBs.
	 * Any other type or'ed with the MALI_FRAME_BUILDER_TYPE_PILOT_JOB_BIT
	 * create a new type of frame.
	 *
	 * Example:
	 * type=MALI_FRAME_BUILDER_TYPE_EGL_SURFACE | MALI_FRAME_BUILDER_TYPE_PILOT_JOB_BIT
	 * means a the pilot job for the normal EGL surface with
	 * the same frame/flush ID pair. */
	MALI_FRAME_BUILDER_TYPE_PILOT_JOB_BIT                = 0x80
};

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Allocate and initialize a new frame builder
 * @param type Type of the framebuilder (see #mali_frame_builder_type above)
 * @param base_ctx The base context with which to perform all Mali resource (pp/gp jobs, mali mem) allocations
 * @param frame_count The number of internal frames. Recommended value is 3
 * @param properties A combination of properties for the frame builder. See #mali_frame_builder_properties.
 * @return The new frame_builder or NULL if the allocation failed
 */
MALI_IMPORT mali_frame_builder *_mali_frame_builder_alloc(enum mali_frame_builder_type type,
        mali_base_ctx_handle base_ctx,
        u32 frame_count,
        enum mali_frame_builder_properties properties);
/**
 * Deinitialize and release all frame builder resources
 * @param frame_builder The frame builder to release
 */
MALI_IMPORT void _mali_frame_builder_free(mali_frame_builder *frame_builder);

/**
 * Release the frame builder to its initial state
 * @param frame_builder The frame builder to reset
 */
MALI_IMPORT void _mali_frame_builder_reset(mali_frame_builder *frame_builder);

/**
 * Release the frame builder to a clean state. Same as reset, but will output the clearcolor if flushed.
 * @param frame_builder The frame builder to clean
 */
MALI_IMPORT void _mali_frame_builder_clean(mali_frame_builder *frame_builder);

/**
 * Flush the actual pixel rendering, but make it possible to continue building the frame afterwards
 * @param frame_builder The frame builder defining the current frame and its physical rendertargets
 * @return MALI_ERR_NO_ERROR If the initialization was successful, otherwise an error explaining what went wrong.
 * @note Frame state might be corrupted if the function fails, meaning that the frame builder should be reset in this case.
 */
MALI_IMPORT mali_err_code _mali_frame_builder_flush(mali_frame_builder *frame_builder);

/**
 * Flush the actual pixel rendering and swap out the frame, swapping in the next frame.
 * @param frame_builder The frame builder defining the current frame and its physical rendertargets
 * @return MALI_ERR_NO_ERROR If the initialization was successful, otherwise an error explaining what went wrong.
 */
MALI_IMPORT mali_err_code _mali_frame_builder_swap(mali_frame_builder *frame_builder);

/**
 * Wait until the GPU is no longer rendering to the surface used by the current frame.
 *
 * @param frame_builder The frame builder that owns the frame that is potentially being rendered
 */
MALI_IMPORT void _mali_frame_builder_wait(mali_frame_builder *frame_builder);

/**
 * acquire a new output buffer.
 * Depends on the acquire output buffer callback being set
 * @param frame_builder The framebuilder to acquire a new output buffer into
 */
MALI_IMPORT void _mali_frame_builder_acquire_output(mali_frame_builder *frame_builder);

/**
 * Set the frame builder's color, depth or stencil clear value.
 * @param frame_builder The frame builder to set a clear value of
 * @param buffer_type   The type of buffer to set the clear value for.
 *                      Legal values:
 *                          MALI_OUTPUT_RED
 *                          MALI_OUTPUT_GREEN
 *                          MALI_OUTPUT_BLUE
 *                          MALI_OUTPUT_ALPHA
 *                          MALI_OUTPUT_DEPTH
 *                          MALI_OUTPUT_STENCIL
 * @param clear_value   The clear value to set on the frame builders buffer_type
 *                      buffer.
 *
 *                      For color:
 *                      This value should be given as an U16 integer.
 *                      But if the tilebuffer is FP16 (see _mali_frame_builder_get_fp16_flag)
 *                      the value must be given as an FP16 value (hardcasted).
 *
 *                      For depth:
 *                      This value should eb given as an U24 integer, where 0xFFFFFF is 1.0
 *
 *                      For stencil:
 *                      This value should be given as an U8 integer.
 */
MALI_IMPORT void _mali_frame_builder_set_clear_value(mali_frame_builder *frame_builder, u32 buffer_type, u32 clear_value);

/**
 * Retrieve the frame builders color, depth or stencil clear value
 * @param frame_builder The frame builder to retrieve the clear value of
 * @param buffer_type   The type of the buffer to retrieve the clear value of
 * @return The clear value of the frame builder buffer of type buffer_type
 */
MALI_IMPORT u32 _mali_frame_builder_get_clear_value(mali_frame_builder *frame_builder, u32 buffer_type);

/**
 * Retrieves the error status of the last rendering job that failed since the
 * last call to this function. If no jobs have have failed then
 * MALI_JOB_STATUS_FINISHED is returned.
 *
 * @param frame_builder The frame builder to check for job completion errors
 * @return The error completion status of the last job that failed since this
 *         function was last called or MALI_JOB_STATUS_FINISHED if no jobs
 *         have failed
 */
MALI_IMPORT mali_job_completion_status _mali_frame_builder_get_framebuilder_completion_status(mali_frame_builder *frame_builder);


/* Mali200 frame builder specific functions ---------------------------------------------------------------- */

/**
 * Set the GP2 scissor parameters as described in 3.15.3 (cmd 7) in the M200 TRM
 *
 * If #buffer is @c NULL, then any PLBU commands will be written immediately
 * to the current frame's PLBU command list.
 *
 * If #buffer is not @c NULL, then any PLBU commands will be written to #buffer, and
 * #index will be incremented once per written command. The caller is responsible for
 * committing this to the PLBU command list.
 *
 * @param frame_builder The frame builder defining the frame
 * @param         left   The left coordinate of the scissorbox
 * @param         top    The top coordinate  of the scissorbox
 * @param         right  The right coordinate of the scissorbox
 * @param         bottom The bottom coordinate of the scissorbox
 * @param[in,out] buffer Pointer to an array of PLBU commands. May be @c NULL (see above).
 * @param[in,out] index  Index of first free entry in the array of PLBU commands. May be @c NULL (see above)
 * @param         buffer_len  The total number of elements in #buffer
 *
 * @return MALI_ERR_NO_ERROR if the frame_builders job finalization was successful, otherwise an error explaining the failure.
 */
MALI_IMPORT mali_err_code _mali_frame_builder_scissor(mali_frame_builder *frame_builder,
        u32 left, u32 top, u32 right, u32 bottom,
        mali_gp_plbu_cmd *const buffer, u32 *const index, const u32 buffer_len);

/**
 * Set the GP2 viewport parameters as described in 3.11.6 - .9 in the M200 TRM
 *
 * If #buffer is @c NULL, then any PLBU commands will be written immediately
 * to the current frame's PLBU command list.
 *
 * If #buffer is not @c NULL, then any PLBU commands will be written to #buffer, and
 * #index will be incremented once per written command. The caller is responsible for
 * committing this to the PLBU command list.
 *
 * @param frame_builder       The frame builder defining the frame
 * @param         left        The left coordinate of the viewport
 * @param         top         The top coordinate  of the viewport
 * @param         right       The right coordinate of the viewport
 * @param         bottom      The bottom coordinate of the viewport
 * @param[in,out] buffer      Pointer to an array of PLBU commands. May be @c NULL (see above).
 * @param[in,out] index       Index of first free entry in the array of PLBU commands. May be @c NULL (see above)
 * @param         buffer_len  The total number of elements in #buffer
 *
 * @return MALI_ERR_NO_ERROR if the frame_builders job finalization was successful, otherwise an error explaining the failure.
 */
MALI_IMPORT mali_err_code _mali_frame_builder_viewport(mali_frame_builder *frame_builder,
        float left, float top, float right, float bottom,
        mali_gp_plbu_cmd *const buffer, u32 *const index, const u32 buffer_len);

/**
 * Set the GP2 depth range parameters
 *
 * If #buffer is @c NULL, then any PLBU commands will be written immediately
 * to the current frame's PLBU command list.
 *
 * If #buffer is not @c NULL, then any PLBU commands will be written to #buffer, and
 * #index will be incremented once per written command. The caller is responsible for
 * committing this to the PLBU command list.
 *
 * @param frame_builder       The frame builder defining the frame
 * @param         znear       The nearplane depth value.
 * @param         zfar        The fraplane depth value.
 * @param[in,out] buffer      Pointer to an array of PLBU commands. May be @c NULL (see above).
 * @param[in,out] index       Index of first free entry in the array of PLBU commands. May be @c NULL (see above)
 * @param         buffer_len  The total number of elements in #buffer
 *
 * @return MALI_ERR_NO_ERROR if the frame_builders job finalization was successful, otherwise an error explaining the failure.
 */
MALI_IMPORT mali_err_code _mali_frame_builder_depth_range(mali_frame_builder *frame_builder,
        float znear, float zfar,
        mali_gp_plbu_cmd *const buffer, u32 *const index, const u32 buffer_len);


/**
 * Returns whether incremental rendering is requested or not. Will only return true
 * if all conditions for correct incremental rendering are true.
 * @param frame_builder The frame builder defining the frame
 */
MALI_IMPORT mali_bool _mali_frame_builder_incremental_rendering_requested(mali_frame_builder *frame_builder);

/**
 * @brief Locks all the surfaces of the frame-builder and clears it if all attachments are dirty
 * @param frame_builder The frame-builder to lock the surfaces of
 * @param write_mask. Bitmask (MALI_OUTPUT_*) specifying the buffers modified.
 * @param read_mask. Bitmask (MALI_OUTPUT_*) specifying the buffers read.
 * @return MALI_ERR_NO_ERROR if successful, an error-code if not
 * NOTE: This function will replace mali_frame_builder_use. Currently, VG still use the old version, this will change
 */
MALI_IMPORT MALI_CHECK_RESULT mali_err_code _mali_frame_builder_write_lock(mali_frame_builder *frame_builder, u32 write_mask, u32 read_mask);

/**
 * @brief Unlocks all the surfaces of the frame-builder
 * @param frame_builder The frame-builder to unlock the surfaces of
 */
MALI_IMPORT void _mali_frame_builder_write_unlock(mali_frame_builder *frame_builder);

/**
 * Reset the damage region in framebuilder
 * @param frame_builder The frame builder defining the frame
 */
MALI_EXPORT void _mali_frame_builder_damage_region_reset(mali_frame_builder *frame_builder);

/**
 * Set the damage region of buffer to frame builder in order to do partial update
 * @param frame_builder The frame builder defining the frame
 * @param rects A pointer to a list of values describing the rectangles
 * @param n_rects Specifies the number of rectangles comprising the damage region
 * @return MALI_TRUE if success, MALI_FALSE if not
 */
MALI_EXPORT mali_bool _mali_frame_builder_damage_region_set(mali_frame_builder *frame_builder, int *rects, int n_rects);

#ifdef __cplusplus
}
#endif

#endif /* !defined(MALI_FRAME_BUILDER_H */
