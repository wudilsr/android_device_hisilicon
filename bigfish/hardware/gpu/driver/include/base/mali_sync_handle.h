/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2010, 2012-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_sync_handle.h
 * The mali_sync_handle represents an object used to synchronize the callback of multiple jobs.
 * It is used to get a callback when multiple jobs has all been completed, independent of their completion order.
 *
 * Typical usage would be:
 *  - allocate sync object @see _mali_sync_handle_get
 *  - register user defined callback with the sync object @see _mali_sync_handle_cb_function_set
 *  - register the jobs to sync using _mali_gp_job_add_to_sync_handle or
 *    _mali_pp_job_add_to_sync_handle(in mali_pp_job.h and mali_gp_job.h)
 *  - start the sync operation @see _mali_sync_handle_flush
 *
 * The ..._start calls on each job still has to be done. Calling _mali_sync_handle_flush only tells the sync object to become active.
 * Once the sync object has become active no other interactions with it is possible.
 * Therefore getting a wait handle, setting the callback or adding jobs has to be done before the call to _mali_sync_handle_flush.
 *
 * Once the sync object has become active the callback will be called when all the registered job has finished, possibly at the point of the _mali_sync_handle_flush call itself.
 * When the callback returns the sync object is automatically deallocated.
 *
 * Another usage scenario would be to abort the sync sequence.
 * Then we have the two situations:
 * - Some jobs where added: Do a normal _mali_sync_handle_flush call.
 *   If the callback should not be called cancel the registration by setting NULL as the callback function before the _mali_sync_handle_flush call.
 *   The sync object will be freed as normal when the started jobs are either explicitly freed or have been run by the hardware.
 * - No jobs where added: Do a normal _mali_sync_handle_flush call.
 *   If the callback should not be called cancel the registration by setting NULL as the callback function before the _mali_sync_handle_flush call.
 *   The sync object will be freed by the start call itself.
 *
 * If a wait handle was obtained the _mali_wait_on_handle function must be called to free it.
 * Never calling wait_on_handle would result in a leak.
 * Remember to call _mali_sync_handle_flush before you call _mali_wait_on_handle, if not you'll have a deadlock.
 * If you have requested a wait handle from an aborted sync object you still have to call _mali_wait_on_handle which would just free the resources, no stalling would occur.
 */

#ifndef _MALI_SYNC_HANDLE_H_
#define _MALI_SYNC_HANDLE_H_

#include <base/mali_types.h>
#include <base/mali_macros.h>
#include <base/common/base_common_sync_handle.h>
#include <base/arch/base_arch_runtime.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get a new synchronization object.
 * @param ctx The mali base contex handle obtained in a open call earlier
 * @return Non-null on success, null on failure
 */
MALI_STATIC_FORCE_INLINE mali_sync_handle _mali_sync_handle_new(mali_base_ctx_handle ctx)
{
	return _mali_base_common_sync_handle_new(ctx);
}

/**
 * Set the callback for a sync object.
 * Set the callback function to be called when all jobs registered on this sync object has completed.
 * Can NOT be set after called @see _mali_sync_handle_flush
 * @param handle Handle to the sync object to set the callback on
 * @param cbfunc The function to be called when sync is complete
 * @param cbarg  Data passed as an argument to the callback function
 */
MALI_STATIC_FORCE_INLINE void _mali_sync_handle_cb_function_set(mali_sync_handle handle, mali_sync_cb cbfunc, void *cbarg)
{
	_mali_base_common_sync_handle_cb_function_set(handle, cbfunc, cbarg);
}

/**
 * Add a mali_mem_handle to a sync object's free-on-termination list
 * This memory will be freed after the callback has been called and the wait handle triggered.
 * @param handle Handle to the sync object to update
 * @param mem Handle to mali memory to add to the list
 */
MALI_STATIC_FORCE_INLINE void _mali_sync_handle_add_mem_to_free_list(mali_sync_handle handle, mali_mem_handle mem)
{
	_mali_base_common_sync_handle_add_mem_to_free_list(handle, mem);
}

/**
 * Get a wait handle which is trigged when the sync object is triggered.
 * Returns a handle to a wait object usable to wait on this sync object to trigger.
 * Returns a NULL value if an error occured, ie. an invalid sync_handle was given.
 * @note This must be called before @see _mali_sync_handle_flush if you want to be able wait on this sync object
 * @param handle Handle to a sync object
 * @return Handle which can be used with @see _mali_wait_on_handle or NULL if no wait handle could be retrieved.
 */
MALI_STATIC_FORCE_INLINE mali_base_wait_handle _mali_sync_handle_get_wait_handle(mali_sync_handle handle)
{
	return _mali_base_common_sync_handle_get_wait_handle(handle);
}

/**
 * Register a reference to the sync handle
 * Called by the monitored systems when they have objects which the sync handle should depend on
 * @param handle Handle to the sync object to update
 */
MALI_STATIC_FORCE_INLINE void _mali_sync_handle_register_reference(mali_sync_handle handle)
{
	_mali_base_common_sync_handle_register_reference(handle);
}

/**
 * Remove a reference to the sync handle
 * Called when the monitored system have objects which have completed their action
 * @param handle Handle to the sync object to update
 */
MALI_STATIC_FORCE_INLINE void _mali_sync_handle_release_reference(mali_sync_handle handle)
{
	_mali_base_common_sync_handle_release_reference(handle);
}

/**
 * Create a dependency between two sync handles
 * Makes one sync object depend on the completion of another sync handle
 * Limitations:
 * - A sync object can monitor multiple sync objects.
 * - A sync object can only be monitored by a single sync object.
 *
 * The completion of monitored will after the call be one of the events sync_object depends on.
 *
 * @param sync_object - Handle to the sync object which should monitor another sync handle's completion
 * @param monitored - Handle to the sync object to monitor
 */
MALI_STATIC_FORCE_INLINE void _mali_sync_handle_add_to_sync_handle(mali_sync_handle sync_object, mali_sync_handle monitored)
{
	_mali_base_common_sync_handle_add_to_sync_handle(sync_object, monitored);
}

/**
 * Start the sync operation. Tells the sync object to become active. The callback will never be called before this function is called.
 * If the jobs have finished before the call the callback will be called at this point, if not it will be called at a later time.
 * Trying to register new jobs after having called this function results in undefined behavior.
 * @param handle Handle to the sync object to start
 */
MALI_STATIC_FORCE_INLINE void _mali_sync_handle_flush(mali_sync_handle handle)
{
	_mali_base_common_sync_handle_flush(handle);
}

/**
 * Wait for a wait handle to trigger.
 * Will block this thread until a wait handle has been triggered.
 * @param handle Handle to a wait object
 */
/* coverity[-alloc] */
MALI_STATIC_FORCE_INLINE void _mali_wait_on_handle(mali_base_wait_handle handle)
{
	_mali_base_arch_sys_wait_handle_wait(handle);
}

/**
 * Wait for a wait handle to trigger with timeout.
 * Will block this thread until a wait handle has been triggered or the time-out interval elapses.
 * @param handle Handle to a wait object
 * @param timeout Relative time in microseconds of the timeout
 * @return MALI_ERR_NO_ERROR if the wait succeeded or MALI_ERR_TIMEOUT if the timeout elapsed
 */
MALI_STATIC_FORCE_INLINE mali_err_code _mali_timed_wait_on_handle(mali_base_wait_handle handle, u64 timeout)
{
	return _mali_base_arch_sys_wait_handle_timed_wait(handle, timeout);
}

/**
 * Abandon a wait handle.
 * Signal that this handle will never be waited on (again).
 * After the call returns the handle has become invalid
 * @param handle The handle to abandon
 */
MALI_STATIC_FORCE_INLINE void _mali_wait_handle_abandon(mali_base_wait_handle handle)
{
	_mali_base_arch_sys_wait_handle_abandon(handle);
}

#ifdef __cplusplus
}
#endif

#endif /*_MALI_SYNC_HANDLE_H_ */
