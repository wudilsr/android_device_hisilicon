/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_pp_job.h
 * PP job system.
 * All access to the mali hardware goes through a job system. Jobs are created by the user and queued for execution.
 *
 */

#ifndef _MALI_PP_JOB_H_
#define _MALI_PP_JOB_H_

#include <base/pp/mali_pp_job_types.h>
#include <mali_arch_pp_job.h>
#include <base/common/base_common_context.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the PP job system. Returns a base context handle.
 * Each _mali_pp_open call must be matched with a call to _mali_pp_close.
 * It's safe to call this function multiple times.
 * @see _mali_pp_close()
 * @param ctx The base context to scope the PP usage to
 * @return A standard Mali error code
 */
MALI_CHECK_RESULT mali_err_code _mali_pp_open(mali_base_ctx_handle ctx);

/**
 * Close a reference to the PP job system. Match each call to _mali_pp_open with a call to this function.
 * @see _mali_pp_open()
 * @param ctx The mali base context handle used in the open call
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_close(mali_base_ctx_handle ctx)
{
	return _mali_arch_pp_close(ctx);
}

/**
 * Get a new PP job struct.
 * Returns a pointer to a new mali_pp_job.
 * When you are finished with the job it needs to be released.
 * This can either be done with setting the auto_free member variable or
 * calling the _mali_pp_job_free function.
 * @param ctx The mali base context handle obtained in a open call earlier
 * @param num_cores Number of cores in a multi-core system, values in the range 1 through 4 supported
 * @return Handle to a job on success, NULL on failure
 */
mali_pp_job_handle _mali_pp_job_new(mali_base_ctx_handle ctx, u32 num_cores);

mali_pp_job_handle _mali_pp_job_dup(mali_pp_job_handle job_handle);

/**
 * Release a PP job struct.
 * Returns the PP job struct to the base system and frees up any resources used by it.
 * Any attached resources will also be freed like upon a normal job completion.
 * @param job The job to release
 */
void _mali_pp_job_free(mali_pp_job_handle job);

/**
 * Add a mali_mem_handle to a job's free-on-termination list
 * @param job Handle to the job to update
 * @param mem Handle to add to list
 * @return void
 */
void _mali_pp_job_add_mem_to_free_list(mali_pp_job_handle job, mali_mem_handle mem);
/**
 * Set callback for a pp job
 * @param job Handle to the job to update
 * @param func Function to set as callback func
 * @param cp_param Argument passed to callback
 * @return void
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_job_set_callback(mali_pp_job_handle job_handle, mali_cb_pp func, void *cb_param)
{
	mali_pp_job *job = MALI_REINTERPRET_CAST(mali_pp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(MALI_PP_JOB_BUILDING == job->state || MALI_PP_JOB_CALLBACK == job->state || MALI_PP_JOB_SYNCING == job->state,
	                  ("Setting a callback on a job which is not in the BUILDING, CALLBACK or SYNCING state is not supported"));

	job->callback = func;
	job->callback_argument = cb_param;
}

/**
 * Get the address of a render attachment from the write back unit of a pp job
 * @param job Handle to the job
 * @param wb_unit the Write Back unit
 * @return the memory address of the render attachment
 */
u32 _mali_pp_job_get_render_attachment_address(mali_pp_job_handle job, u32 wb_unit);

/**
 * Set a render register value in a job definition
 * @param job Handle to the job to update
 * @param regid ID of register to set
 * @param value value to assign to register
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_job_set_common_render_reg(mali_pp_job_handle job_handle, mali_reg_id regid, mali_reg_value value)
{
	u32 bank = (regid >> 6) & 0x03FF;
	u32 internal_register_number = regid & 0x003F;
	mali_pp_job *job = MALI_REINTERPRET_CAST(mali_pp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(MALI_PP_JOB_BUILDING == job->state ||
	                  MALI_PP_JOB_CALLBACK == job->state ||
	                  MALI_PP_JOB_RUNNING == job->state ||
	                  MALI_PP_JOB_SYNCING == job->state,
	                  ("Changing a render register on a job which is not in the BUILDING, CALLBACK or SYNCING state is not supported"));

	switch (bank)
	{
		case 0:
			_mali_arch_pp_job_set_common_frame_register(job, internal_register_number, value);
			break;

		case 1:
			_mali_arch_pp_job_set_wb0_register(job, internal_register_number, value);
			break;

		case 2:
			_mali_arch_pp_job_set_wb1_register(job, internal_register_number, value);
			break;

		case 3:
			_mali_arch_pp_job_set_wb2_register(job, internal_register_number, value);
			break;

		default:
			MALI_DEBUG_ASSERT(MALI_FALSE, ("Invalid register id %d", regid));
			break;
	}
}

MALI_STATIC_FORCE_INLINE void _mali_pp_job_set_specific_render_reg_list_addr(mali_pp_job_handle job_handle, u32 core_no, mali_reg_value value)
{
	mali_pp_job *job = MALI_REINTERPRET_CAST(mali_pp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(core_no < _MALI_PP_MAX_SUB_JOBS, ("Setting register for invalid core number %d", core_no));
	MALI_DEBUG_ASSERT(MALI_PP_JOB_BUILDING == job->state || MALI_PP_JOB_CALLBACK == job->state || MALI_PP_JOB_SYNCING == job->state,
	                  ("Changing a render register on a job which is not in the BUILDING, CALLBACK or SYNCING state is not supported"));

	_mali_arch_pp_job_set_specific_render_reg_list_addr(job, core_no, value);
}

MALI_STATIC_FORCE_INLINE void _mali_pp_job_set_specific_render_reg_stack_addr(mali_pp_job_handle job_handle, u32 core_no, mali_reg_value value)
{
	mali_pp_job *job = MALI_REINTERPRET_CAST(mali_pp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(core_no < _MALI_PP_MAX_SUB_JOBS, ("Setting register for invalid core number %d", core_no));
	MALI_DEBUG_ASSERT(MALI_PP_JOB_BUILDING == job->state || MALI_PP_JOB_CALLBACK == job->state || MALI_PP_JOB_SYNCING == job->state,
	                  ("Changing a render register on a job which is not in the BUILDING, CALLBACK or SYNCING state is not supported"));

	_mali_arch_pp_job_set_specific_render_reg_stack_addr(job, core_no, value);
}

/**
 * Return true if it is possible to update a register of the pp job
 * @param job Handle to the job to check
 * @return true if it is possible to update a job register, false otherwise
 */
MALI_STATIC_FORCE_INLINE mali_bool _mali_pp_job_is_updateable(mali_pp_job_handle job_handle)
{
	mali_pp_job *job = MALI_REINTERPRET_CAST(mali_pp_job *)job_handle;
	MALI_DEBUG_ASSERT_POINTER(job);
	return (MALI_PP_JOB_BUILDING == job->state ||
	        MALI_PP_JOB_CALLBACK == job->state ||
	        MALI_PP_JOB_RUNNING == job->state ||
	        MALI_PP_JOB_SYNCING == job->state);
}

/**
 * Get a wait handle which is trigged when the pp job has finished processing
 * Returns a handle to a wait object usable for waiting on this pp job to finish processing
 * @note This must be called before @see _mali_pp_job_start if you want to be able wait on this pp job
 * @param handle Handle to a pp job
 * @return Handle which can be used with @see _mali_wait_on_handle
 */
mali_base_wait_handle _mali_pp_job_get_wait_handle(mali_pp_job_handle job);

/**
 * Queue a PP job for execution by the system.
 *
 * Submits the job to the Timeline system where it will eventually be scheduled to run when it no
 * longer has anything to wait on.
 *
 * The job's priority will decide where in the queue it will be put.
 *
 * A fence is created for this job which can be used to wait for the job to finish.  The fence will
 * be merged into @ref fence_handle, if it is not MALI_NO_HANDLE.
 *
 * @param job Pointer to the job to put on the execution queue.
 * @param priority Priority of the job
 * @param fence_handle If not MALI_NO_HANDLE, the fence created for this job will be merged into this fence
 */
void _mali_pp_job_start(mali_pp_job_handle job, mali_job_priority priority, mali_fence_handle fence_handle);

/** called by arch layer when PP job has completed */
void _mali_pp_job_run_postprocessing(mali_pp_job *job, mali_job_completion_status completion_status);

/**
 * Attach a PP job to a sync object
 * Attaches the job to the list of jobs the sync object should wait for before firing the callback
 * @note The two objects must be from the same context
 * @param sync Handle to the sync object to attach this job to
 * @param job Pointer to the job to put on the sync list
 */
void _mali_pp_job_add_to_sync_handle(mali_sync_handle sync, mali_pp_job_handle job);

/**
 * Function to return number of PP cores totally available
 * @return The total number of PP cores on the system
 */
MALI_STATIC_FORCE_INLINE u32 _mali_pp_get_num_total_cores(void)
{
	return _mali_base_arch_pp_get_num_total_cores();
}

/**
 * Function to return number of PP cores which are currently enabled
 * @return The number of currently enabled PP cores on the system
 */
MALI_STATIC_FORCE_INLINE u32 _mali_pp_get_num_enabled_cores(void)
{
	return _mali_base_arch_pp_get_num_enabled_cores();
}

/**
 * Function to return version number of MaliPP. To be used if we have several different versions
 * of MaliPP, and some may have bugfixes.
 * @return The core version
 */
MALI_STATIC_FORCE_INLINE u32 _mali_pp_get_core_product_id(void)
{
	return (_mali_arch_pp_get_core_version() >> 16);
}

/**
 * Function to return the Major and Minor fields (version) reported for the cores on the system.
 * @return The version number read from the cores
 */
MALI_STATIC_FORCE_INLINE u32 _mali_pp_get_core_version(void)
{
	return _mali_arch_pp_get_core_version();
}

/**
 * Get a fence for the latest PP job started.
 *
 * The fence will be merged (@ref _mali_fence_merge) into @ref fence_handle.
 *
 * @param fence_handle Handle to a fence we will merge the latest pp fence into.
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_get_latest_fence(mali_fence_handle fence_handle)
{
	_mali_arch_pp_get_latest_fence(fence_handle);
}

/**
 * Mark this job as a window surface job
 * @param job_handle Job to mark as window surface job
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_job_set_window_surface_type(mali_pp_job_handle job_handle)
{
	mali_pp_job *job = (mali_pp_job *)job_handle;
	MALI_DEBUG_ASSERT_POINTER(job);
	job->is_window_surface = MALI_TRUE;
}

/**
 * Set a frame_nr on the job. It can be used for aborting jobs. The frame_nr
 * can be given to the job_abort function, and it will abort all jobs in the
 * context with this frame_id.
 * @param job_handle Set frame_id on this job
 * @param frame_id   The frame_id we want to set.
 * @see _mali_base_frame_id_get_new()
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_job_set_frame_id(mali_pp_job_handle job_handle, mali_base_frame_id frame_id)
{
	mali_pp_job *job = (mali_pp_job *)job_handle;
	MALI_DEBUG_ASSERT_POINTER(job);
	job->frame_id = frame_id;
}

/**
 *  Set job identity, which is defined by unique frame builder id and flush id. Called from Frame Builder's
 *  @c _pp_jobs_create.
 *
 *  @param job_handle   Job handle
 *  @param fb_id        Frame Builder ID
 *  @param flush_id     Flush ID
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_job_set_identity(mali_pp_job_handle job_handle, mali_base_frame_id fb_id, mali_base_flush_id flush_id)
{
	mali_pp_job *job = (mali_pp_job *) job_handle;
	MALI_DEBUG_ASSERT_POINTER(job_handle);
	_mali_arch_pp_job_set_identity(job, fb_id, flush_id);
}

/**
 * Disable Write-back unit(s) on the job with the specified frame builder and flush IDs, and where the memory
 * matches the memory block given.
 *
 *  @param fb_id        Frame Builder ID
 *  @param wb0_memory   Memory block assumed bound to writeback unit #0
 *  @param wb1_memory   Memory block assumed bound to writeback unit #1
 *  @param wb2_memory   Memory block assumed bound to writeback unit #2
 *
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_job_disable_wb(u32 fb_id, mali_addr wb0_memory, mali_addr wb1_memory, mali_addr wb2_memory)
{
	_mali_arch_pp_job_disable_wb(fb_id, (u32) wb0_memory, (u32) wb1_memory, (u32) wb2_memory);
}

#if defined(USING_MALI450)
void _mali_pp_job_450_set_frame_info(mali_pp_job_handle job_handle, m450_pp_job_frame_info *info);
#endif

#if MALI_INSTRUMENTED
/**
 * Setting the array that tells which counters to read for a job and
 * where to put the result.
 *
 * @param job_handle            PP job handle
 * @param perf_counters         an array with the counter indices to read
 * @param perf_counters_count   the number of counters in the perf_counters array
 * @param res                   an array where the extracted counters should be put
 */
void _mali_pp_job_setup(mali_pp_job_handle job_handle, u32 *perf_counters, u32 perf_counters_count, u32 **res);

/**
 * Get the array that tells which counters to read / has been read for a job,
 * and the resulting values
 *
 * The perf_counters array tells which counters on mali we will readout after
 * the job has run.
 *
 * @param job_handle            PP job handle
 * @param num_cores             number of PP cores used in the job i.e. number of PP subjobs
 * @param perf_counters         returns the array with the counter indices to read
 * @param perf_counters_count   returns the number of counters in the perf_counters array
 * @param res                   pointer to location where counter results/values is stored
 */
void _mali_pp_job_get_data(mali_pp_job_handle job_handle, u32 *num_cores, u32 **perf_counters, u32 *perf_counters_count, u32 **res);


void _mali_pp_job_set_wbx_mem(mali_pp_job_handle job_handle, u32 wb_unit, mali_mem_handle mem);

#endif

#if MALI_HEATMAPS_ENABLED

MALI_STATIC_FORCE_INLINE void _mali_pp_job_get_perf_counters(mali_pp_job_handle job_handle, u32 *src0, u32 *src1)
{
	_mali_arch_pp_job_get_perf_counters(job_handle, src0, src1);
}

MALI_STATIC_FORCE_INLINE void _mali_pp_job_set_heatmap_mem(mali_pp_job_handle job_handle, u32 tilesx, u32 tilesy, mali_mem_handle mem)
{
	_mali_arch_pp_job_set_heatmap_mem(job_handle, tilesx, tilesy, mem);
}

#endif /* MALI_HEATMAPS_ENABLED */

#if defined(MALI_USE_DMA_BUF) && defined(DMA_BUF_ON_DEMAND)
/**
 * Attach a list of memory to job.
 *
 * The list will be used by the kernel driver to map or do cache maintenance on the memory before
 * job start.  This function takes ownership of the list and will free the memory once it's done
 * with it.
 *
 * @param job_handle Handle of job
 * @param num_cookies Number of cookies in list \a cookies
 * @param cookies List of cookies referencing memory
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_job_attach_mem(mali_pp_job_handle job_handle, u32 num_cookies, u32 *cookies)
{
	mali_pp_job *job = (mali_pp_job *)job_handle;

	MALI_DEBUG_ASSERT(0 == job->num_memory_cookies, ("No memories to attach"));
	MALI_DEBUG_ASSERT(NULL == job->memory_cookies, ("Attaching NULL"));

	job->num_memory_cookies = num_cookies;
	job->memory_cookies = cookies;
}
#endif /* defined(MALI_USE_DMA_BUF) && defined(DMA_BUF_ON_DEMAND) */

/**
 * Add a fence to this job.
 *
 * The fence will be merged (@ref _mali_fence_merge) with any fences previously added to the job.
 *
 * @param job_handle Handle to job.
 * @param fence_handle Handle to fence that will be added to the job fence.
 */
void _mali_pp_job_add_fence(mali_pp_job_handle job_handle, mali_fence_handle fence_handle);

/**
 * Add a fence to the global PP fence.
 *
 * The global PP fence is added to all PP jobs started.
 *
 * The fence will be merged (@ref _mali_fence_merge) with any fences previously added to the global
 * PP fence.
 *
 * @note The global mem fence mutex must be locked before calling this function (@ref
 * _mali_mem_fence_lock).
 *
 * @param fence_handle Handle to the fence that will be added to the global PP fence.
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_add_global_fence(mali_fence_handle fence_handle)
{
	_mali_base_common_context_add_global_pp_fence(fence_handle);
}

/**
 * Get global PP fence.
 *
 * The global PP fence will be merged (@ref _mali_fence_merge) into @ref fence_handle.
 *
 * @note The global mem fence mutex must be locked before calling this function (@ref
 * _mali_mem_fence_lock).
 *
 * @param fence_handle Handle to the fence that the global PP fence will be merged into.
 */
MALI_STATIC_FORCE_INLINE void _mali_pp_get_global_fence(mali_fence_handle fence_handle)
{
	_mali_base_common_context_get_global_pp_fence(fence_handle);
}

#ifdef __cplusplus
}
#endif

#endif /* _MALI_PP_JOB_H_ */
