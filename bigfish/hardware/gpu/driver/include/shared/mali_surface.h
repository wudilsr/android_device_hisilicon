/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_SURFACE_H_
#define _MALI_SURFACE_H_


#include <mali_system.h>
#include <base/mali_memory.h>
#include <shared/mali_surface_specifier.h>

/* surface flags enum. Bitwise combinations of these go into the flags field of the various constructors */
enum mali_surface_flags
{
	MALI_SURFACE_FLAGS_NONE                        = 0,     /* No special flags present, this is the default behavior */
	MALI_SURFACE_FLAG_DONT_MOVE                    = 1 << 0, /* The surface memory is referenced externally, and must never be moved. This is a property of pixmaps and window surfaces */
	MALI_SURFACE_FLAG_EGL_IMAGE_SIBLING            = 1 << 1, /* Any mali surface turned into an EGL Image will have this set, to prevent it happening twice */
	MALI_SURFACE_FLAG_TRACK_SURFACE                = 1 << 2, /* The driver needs to track the surface in all framebuilders using it in drawcalls. see m200_surfacetracking.h for details */
	MALI_SURFACE_FLAG_MRT                          = 1 << 3, /* This surface is guaranteed to contain a memory block holding 4x datasize bytes from the given offset */
};

/* surface usecase bits, given to "grab instance" */
#define MALI_SURFACE_READ                        (1<<0)
#define MALI_SURFACE_WRITE                       (1<<1)
#define MALI_SURFACE_INITIALIZE                  (1<<2)
#define MALI_SURFACE_IMMEDIATE                   (1<<3)
#define MALI_SURFACE_DEFERRED                    (1<<4)
#define MALI_SURFACE_DISCARD_ON_COW              (1<<5)
#define MALI_SURFACE_PRESERVE_ON_COW             (1<<6)
#define MALI_SURFACE_MAP                         (1<<7)

enum mali_surface_event
{
	MALI_SURFACE_EVENT_CPU_ACCESS,        /* CPU about to read/write to the surface. Called as a part of the _mali_surface_map function */
	MALI_SURFACE_EVENT_CPU_ACCESS_DONE,   /* CPU done read/writing to the surface. Called as a part of the _mali_surface_unmap function */

	MALI_SURFACE_EVENT_GPU_WRITE,         /* GPU about to write to the surface. Called as a part of the framebuilder flush/swap functions */
	MALI_SURFACE_EVENT_GPU_WRITE_DONE,    /* GPU done writing to the surface. Called as a part of the PP callback function
                                             NB: Currently called on frame complete, not flush complete. We may want to change this.
                                             As a consequence: if glFlush'ing a frame twice, you will end up with 2 GPU write, then 2 GPU write done, in that order.
                                             Also note that the ROTATE_ON_FLUSH property on a framebuilder will likely save us here. Since all flushes are swaps. */
	MALI_SURFACE_EVENT_GPU_READ,          /* GPU about to read from the surface. Called as when calling GPU_WRITE.  */
	MALI_SURFACE_EVENT_GPU_READ_DONE,     /* GPU done reading from the surface. Called as when calling GPU_WRITE_DONE.  */

	MALI_SURFACE_EVENT_UPDATE_TEXTURE,       /* GPU about to upload texture description, trigger the event to update egl_image */

	MALI_SURFACE_EVENT_DESTROY,           /* Used by the mali_image, for reasons unknown. Triggered when the surface is freed */
	MALI_SURFACE_EVENT_COPY_ON_WRITE,     /* Called when triggering a "copy on write". Used by VG to force the texture descriptor into the new copy */

	MALI_SURFACE_EVENT_COUNT              /* The number of events defined. Keep this at the end of the list */
};

/* function pointer definitions for os_lock/unlock  */
struct mali_surface;
typedef void (*mali_surface_eventfunc)(struct mali_surface *surface, enum mali_surface_event event, void *trigger_data, void *data);


typedef struct mali_surface_instance
{
	/* constant */
	struct mali_surface          *surface;        /**< A backward pointer to the surface that spawned this instance */

	/* public members in an interface */
	mali_mem_handle               mem;            /**< memory block of this surface */
	u32                           offset;         /**< offset into the memory block where this surface begins */
	void                         *mapped_cpu_ptr; /**< if grabbed with "mapped", this is a CPU representation of the instance */

	/* This field is private and should not be modified */
	u32                           usecase;        /**< Holds info on how this instance was spawned. Used for release cleanup. */

} mali_surface_instance;

/**
 * This structure contains all metadata regarding a surface in mali memory.
 * A surface can be rendered to and used as a texture.
 */
typedef struct mali_surface
{
	/* The master instance is not legal to access without taking the mali_fence_lock first.
	 * External callers should instead use the "grab_instance" below, which ensures
	 * safe concurrent access to the correct surface instance. */
	struct mali_surface_instance   master_instance;        /**< The current surface instance */

	/* These are constant values and will never change during the life-time of the surface. */
	struct mali_surface_specifier  format;         /**< Contains all required information about the format and layout */
	u32                            datasize;       /**< The bytesize of the mali memory this surface requires. Autocalculated on create */
	mali_base_ctx_handle           base_ctx;       /**< A pointer to the base context used when allocating this surface */
	u32                            flags;          /**< Special behavior flags for this surface. See the flags enum for details */

	/* The following values are atomic and can be modified from anywhere */
	mali_atomic_int                ref_count;      /**< Reference count. Increased per API context using the surface. */

	/* callback pointers (should never be read or written to directly - use the API functions) */
	mali_surface_eventfunc         eventfunc[MALI_SURFACE_EVENT_COUNT];
	void                          *eventdata[MALI_SURFACE_EVENT_COUNT];

} mali_surface;

/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


/**
 * Allocates a new empty surface.
 * @note This constructor will not allocate any mali memory area.
 * @param flags Surface flags modifying the surface behavior. See the flags struct for details.
 * @param format A struct containing the format and layout of this surface.
 * @param base_ctx a pointer to the base context; required to allocate mali memory
 * @return A pointer to the new surface, NULL on error
 */
MALI_IMPORT struct mali_surface *_mali_surface_alloc_empty(enum mali_surface_flags flags, const mali_surface_specifier *format, mali_base_ctx_handle base_ctx);

/**
 * Allocates a new surface and dynamically allocates memory for it.
 * @note This constructor will implicitly allocate a mali memory area matching the specifications.
 * @param flags Surface flags modifying the surface behavior. See the flags struct for details.
 * @param format A struct containing the format and layout of this surface
 * @param mem_offset Size of additional memory allocated in the same chunk, placed before surface data (usually VG's TD)
 * @param base_ctx a pointer to the base context; required to allocate mali memory
 * @param mali_usage to tell what kind of usage of this mem for this surface
 * @return A pointer to the new surface, NULL on error
 * Note: It is a logical error to use MALI_SURFACE_FLAG_DONT_MOVE with this constructor.
 */
MALI_IMPORT struct mali_surface *_mali_surface_alloc(enum mali_surface_flags flags, const mali_surface_specifier *format, u32 mem_offset, mali_base_ctx_handle base_ctx, u32 mem_usage);

/**
 * Allocates a new surface with the same properties as another surface. This is good if you need to clone a surface.
 * @param surface instance to clone
 * @param copy_content if MALI_TRUE, the function will also copy the surface instance data.
 * @return A pointer to the new surface, NULL on error
 * Note: This constructor will clear the MALI_SURFACE_FLAG_DONT_MOVE flag on the copy, if set.
 */
MALI_IMPORT struct mali_surface *_mali_surface_alloc_surface_instance(struct mali_surface_instance *instance, mali_bool copy_content);


/**
 * Allocates a new surface based on the given mali memory area.
 * @note This is a transfer of ownership of the mem handle, which means that the surface will take one of the owner
 *       reference counts of the mem parameter.
 * @param flags Surface flags modifying the surface behavior. See the flags struct for details.
 * @param format A struct containing the format and layout of this surface
 * @param mem The memory handle to take ownership of
 * @param offset Any offset to the given mem handle. Useful for miplevel 10+
 * @param base_ctx a pointer to the base context; required to allocate mali memory
 * @return A pointer to the new buffer, NULL on error
 */
MALI_IMPORT struct mali_surface *_mali_surface_alloc_mem(enum mali_surface_flags flags, const mali_surface_specifier *format, mali_mem_handle mem,
        u32 offset, mali_base_ctx_handle base_ctx);

/**
 * Release the memory previously allocated for a surface.
 * @param buffer A pointer to the surface buffer to be released
 */
MALI_IMPORT void _mali_surface_free(mali_surface *buffer);

/**
 * Increases the ref count
 * @param buffer The surface which get an increased reference counter.
 */
MALI_STATIC_FORCE_INLINE void _mali_surface_addref(mali_surface *buffer)
{
	MALI_DEBUG_ASSERT_POINTER(buffer);
	MALI_DEBUG_ASSERT(0 < _mali_sys_atomic_get(&buffer->ref_count), ("inconsistent ref count (ref_count=%d)", _mali_sys_atomic_get(&buffer->ref_count)));
	_mali_sys_atomic_inc(&buffer->ref_count);

}

/**
 * Decreases the ref count
 * @param buffer The surface which get a decreased reference counter.
 */
MALI_STATIC_FORCE_INLINE void _mali_surface_deref(mali_surface *buffer)
{
	MALI_DEBUG_ASSERT_POINTER(buffer);
	MALI_DEBUG_ASSERT(0 < _mali_sys_atomic_get(&buffer->ref_count), ("inconsistent ref count"));

	if (0 == _mali_sys_atomic_dec_and_return(&buffer->ref_count))
	{
		_mali_surface_free(buffer);
	}
}

/**
 * Retrieves an instance that is safe to use for the given "usecase".
 *
 * @param surface - The Surface to spawn an instance from
 * @param usecase - A bitmask of the following bits
 *
 *                  MALI_SURFACE_READ
 *                  MALI_SURFACE_WRITE
 *                  MALI_SURFACE_INITIALIZE
 *                     One of these bits must be set. It is also legal to specify READ+WRITE.
 *
 *                     By specifying READ only, the caller guarantees that the instance given
 *                     will only be used by READ operations. The instance is safe to read from,
 *                     but attempts to write to it will cause undefined correctness errors.
 *
 *                     Note: Multiple reads can occur at the same time. These will likely share
 *                     the same memory.
 *
 *                     If WRITE is set, the system will return an instance that is not suffering
 *                     from any read dependencies. It does so by performing a COW if needed.
 *
 *                     Note: Grabbing a WRITE instance offer exclusive access mode. All future
 *                     grabs will be blocked until the WRITE grab is released.
 *
 *                     By specifying INITIALIZE, you guarantee that this is the initial
 *                     surface upload operation. No dependencies exist on the surface
 *                     at this point. No dependencies will exist on the surface until
 *                     the matching release operation. This operation will forego any
 *                     locking and potential COWs, allowing access to the surface
 *                     without any mutexes held.
 *
 *                  MALI_SURFACE_IMMEDIATE
 *                  MALI_SURFACE_DEFERRED
 *                     None of these bits must be set if INITIALIZE is set.
 *                     Otherwise, one of these bits must be set.
 *
 *                     By specifying IMMEDIATE; all pending write operations will be
 *                     abolished through a blocking wait. This will cause a GPU pipeline
 *                     bubble. The instance returned will be completely safe to access.
 *                     Generally this bit is used by CPU operations like glReadPixels.
 *
 *                     By specifying DEFERRED; all pending writes will be ignored. The
 *                     caller must deal with these through handling the memory block
 *                     writer fence. Generally this bit is used by GPU operations, like
 *                     when rendering to or from a surface.
 *
*
 *                  MALI_SURFACE_DISCARD_ON_COW
 *                  MALI_SURFACE_PRESERVE_ON_COW
 *                     One of these bits must be set if WRITE+IMMEDIATE is set.
 *                     One of these bits must be set if WRITE+DEFERRED is set.
 *                     These bits are not accepted otherwise.
 *
 *                     This selection decides what should happen to the surface content
 *                     if a copy on write occurs.
 *
 *                     If set to DISCARD, any COW operation caused by this call will discard
 *                     the content in the surface. This is useful if your write will replace
 *                     the entire buffer anyway; as that makes the COW a lot cheaper.
 *
 *                     If set to PRESERVE, any COW operation caused by this call will never
 *                     lose any data. If replacing only a subsection of the buffer, or otherwise
 *                     need the old content to be there, this mode should be used; as it
 *                     guarantees that no data is lost. But it is also slower if a COW
 *                     does happen, as it must both wait for pending writes before copying,
 *                     and also perform the actual copy.
 *
 *                  MALI_SURFACE_MAP
 *                     If set, the surface will be pre-mapped to CPU memory, meaning the
 *                     instance->mapped_ptr is valid on the returned instance. Unless this
 *                     bit is specified, accessing the instance->mapped_ptr is undefined.
 *
 *                     Note that requesting a MAP may cause the operation to fail.
 *
 * @param out_instance [inout] -
 *         Pass in a mali_surface_instance pointer that points to a stack memory block.
 *         The struct will be filled out matching the usecase of this instance.
 *
 * @return For most input parameters, this function call will never fail. Caller
 *         can simply ignore error handling. Memfail situations will be handled by memfail testing.
 *         Asserting that the function returns MALI_ERR_NO_ERROR is a good solution.
 *
 *         If requesting WRITE or MAP, the function may fail with MALI_ERR_OUT_OF_MEMORY.
 *         Error handling should be applied.
 *
 */
mali_err_code _mali_surface_grab_instance(mali_surface *surface, u32 usecase, struct mali_surface_instance *out_instance);

/**
 * Release a previously grabbed instance. All calls to grab must be complemented with a release.
 * Accessing instance members after a release is not legal.
 *
 * There are some rules as to when an instance can be released.
 *
 *  EITHER
 *   - All work on the instance must be done. At this point, releasing the instance is perfectly safe.
 *   - This is generally what happens with a CPU operation, like glTexSubImage2D
 *      -- Instance grabbed
 *      -- Work performed
 *      -- Instance released
 *  OR
 *   - The surface instance memory must be given dependencies.
 *   - This is generally what happens with a deferred GPU setup operation, like glDraw using a texture
 *     -- Instance grabbed
 *     -- ... Either add framebuilder read dependency, ensuring that future grabs will heed this read
 *     -- ... or add a fence to the instance memory, ensuring that future grabs will heed this write
 *     -- Instance released
 *     Despite being released at the time of glDraw, since the instance was given a dependency
 *     (read or write), it may have a lifetime beyond the release operation. It is not a good idea to
 *     add a release_instance as a framebuilder callback, since that may lead to excess locking.
 *     Set up a dependency instead, and release early.
 *
 * @param instance - The instance to release.
 */
void _mali_surface_release_instance(struct mali_surface_instance *instance);

/**
 * Replaces the master instance in a mali_surface with something else.
 * The old master instance is de-referenced.
 *
 * @param surface - The surface which memory should be replaced.
 * @param mem - The new memory block
 * @param offset - The new memory offset
 *
 * @note This function follow the same blocking driving rules as the grab function.
 *
 */
void _mali_surface_replace_instance(struct mali_surface *surface, mali_mem_handle mem, u32 offset);


/**
 * @brief Trigger a given event on this surface. This function is invoked by the driver when an event occurs.
 *        Users of the event system should not call this directly (though you can if you want to simulate events).
 * @param surf - The surface to trigger an event on.
 * @param event - The event to trigger. Check out the ENUM section for details.
 * @note  If the event callback is NULL, no actions will occur.
 **/
MALI_STATIC_INLINE void _mali_surface_trigger_event(mali_surface *surf, void *trigger_data, enum mali_surface_event event)
{
	MALI_DEBUG_ASSERT_POINTER(surf);
	MALI_DEBUG_ASSERT(event < MALI_SURFACE_EVENT_COUNT, ("Event out of range: wanted [0-%d] - found %d", MALI_SURFACE_EVENT_COUNT - 1, event));

	if (surf->eventfunc[event])
	{
		surf->eventfunc[event](surf, event, trigger_data, surf->eventdata[event]);
	}
}

/**
 * @brief Set up a surface event handler
 *        NULL means no callback. Overwriting an existing callback will trigger an assert, as this is not handled.
 * @param surf - The surface to set up callbacks on
 * @param event - The event to listen in to
 * @param callback - The function pointer to call when the event is triggered
 * @param data - A generic handle block passed into the callback functions along with the callback.
 */
MALI_STATIC_INLINE void _mali_surface_set_event_callback(mali_surface *surf, enum mali_surface_event event, mali_surface_eventfunc callback, void *data)
{
	MALI_DEBUG_ASSERT_POINTER(surf);
	MALI_DEBUG_ASSERT(event < MALI_SURFACE_EVENT_COUNT, ("Event out of range: wanted [0-%d] - found %d", MALI_SURFACE_EVENT_COUNT - 1, event));
	MALI_DEBUG_ASSERT(surf->eventfunc[event] == NULL ||  /* no callback set */
	                  callback == NULL ||  /* setting it to NULL right now */
	                  (surf->eventfunc[event] == callback), /* or callback function is the same as it already is */
	                  ("Event %d already had a callback registered. There can only be one at a time right now", event));
	surf->eventfunc[event] = callback;
	surf->eventdata[event] = data;
}


#if MALI_INSTRUMENTED || defined(DEBUG)
/**
 * Writes the content of the surface to a .ppm file in the current directory.
 *
 * @param surface The surface to write to the file
 * @param filename Name of file to write the surface to
 */
void _mali_surface_fprintf(struct mali_surface *surface, const char *filename);

/**
 * Dumps the content of a mali_surface to two files. A .hex file containing the actual image data,
 * and a .hex.metadata file containing the constraints and pointer values of the image.
 * This function is used for debugging purposes only.
 *
 * @param surface The surface to dump
 * @param filename_prefix The name of the file, minus file ending.
 *  Setting this to "foo" will yield one "foo.hex" file and one "foo.metadata" file
 **/
void _mali_surface_dump(struct mali_surface *surface, const char *filename_prefix);

/**
 * Dumps the content of a mali_surface to four files.
 * _RGB.ppm: RGB image
 * _RGB.metadata: the metadata of RGB image
 * _grey.ppm: grey image
   _grey.metadata: the metadata of grey image
 *
 * This function is used for debugging purposes only.
 *
 * @param surface The surface to dump
 * @param filename_prefix The name of the file, minus file ending.
 * @param orientation The rotated degree of surface.
 * @return dump mali_surface is sucessfull or fail
 **/

mali_bool _mali_surface_dump_to_visible_image(struct mali_surface *surface, const char *filename_prefix, const u32 orientation);

#endif

#ifdef __cplusplus
}
#endif

#endif /* _MALI_SURFACE_H_ */
