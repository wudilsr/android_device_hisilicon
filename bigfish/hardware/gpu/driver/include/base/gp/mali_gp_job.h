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
 * @file mali_gp_job.h
 * The GP job system.
 * All access to the mali hardware goes through a job system. Jobs are created
 * by the user and queued for execution. The Vertex Shader (VS) and the Polygon
 * List Builder Unit (PLBU), use a common job definition. A job can contain
 * commmand lists for both the PLBU and the VS. If a VS and a PLBU job depend
 * on each other they must be added to a single GP job handle so they are
 * handled together by the lower systems.
 */

#ifndef _MALI_GP_JOB_H_
#define _MALI_GP_JOB_H_

#include <base/gp/mali_gp_job_types.h>
#include <base/pp/mali_pp_job_types.h>
#include <mali_arch_gp_job.h>

#ifdef __cplusplus
extern "C" {
#endif /* _cplusplus */

/* private call to enable inlined GP cmd list writing */
MALI_IMPORT u64 *_mali_gp_cmdlist_extend(mali_gp_cmd_list_handle handle, u32 min_count);

/**
 * Initialize the GP job system.
 * Each _mali_gp_open call must be matched with a call to _mali_gp_close.
 * It's safe to call this function multiple times. It is necessary to call
 * close equivalent number of times as open on quit.
 * @see _mali_gp_close()
 * @param ctx The base context to scope usage to
 * @return A standard Mali error code
 */
MALI_CHECK_RESULT MALI_STATIC_FORCE_INLINE mali_err_code _mali_gp_open(mali_base_ctx_handle ctx)
{
	return _mali_arch_gp_open(ctx);
}

/**
 * Close a reference to the GP job system. You must call this function equal
 * number of times as you called _mali_gp_open().
 * @see _mali_gp_open()
 * @param ctx The mali base context handle used the open call
 */
MALI_STATIC_FORCE_INLINE void _mali_gp_close(mali_base_ctx_handle ctx)
{
	return _mali_arch_gp_close(ctx);
}

/**
 * Get a handle to a new GP job.
 * The returned job handle is valid until the job is started or it is freed.
 * Do touch the job after it has started or has been freed.
 * @param ctx The mali base context handle used in a open call earlier
 * @return A handle to a GP job.
 */
mali_gp_job_handle _mali_gp_job_new(mali_base_ctx_handle ctx);

/**
 * Release a GP job that has not been started.
 * Returns the GP job to the base system and frees up any resources used by it.
 * Do this only if you allocate a job that you do
 * not start or has had auto free disabled.
 * Do not use the job_handle after it has been freed.
 * Any attached resources will also be freed like upon a normal job completion.
 * @param job Handle to the gp job to release
 */
void _mali_gp_job_free(mali_gp_job_handle job);

/**
 * Reset a GP job
 * Resets the GP job to same the state as when newly allocated.
 * Any attached resources will also be freed like upon a normal job completion.
 * @note The plbu heap will NOT be freed, only detached from the job.
 * @param job_handle Handle for a GP job
 */
void _mali_gp_job_reset(mali_gp_job_handle job_handle);

/**
 * Add a mali_mem_handle to a job's free-on-termination list.
 * After the job has been finished and the callback has been issued, the
 * memory added to this list will be freed.
 * @param job Handle to the job to update
 * @param mem Handle to memory to add to the list
 */
void _mali_gp_job_add_mem_to_free_list(mali_gp_job_handle job, mali_mem_handle mem);

/**
 * Set callback for a gp job
 * Called with the given parameter when the job has finished
 * @param job Handle to the job to set callback for
 * @param func Function to set as callback func
 * @param cp_param Argument passed to callback
 */
void _mali_gp_job_set_callback(mali_gp_job_handle job, mali_cb_gp func, void *cb_param);

/**
 * Get a wait handle which is trigged when the gp job has finished processing
 * Returns a handle to a wait object usable for waiting on this gp job to finish processing
 * @note This must be called before @see _mali_gp_job_start if you want to be able wait on this gp job
 * @param handle Handle to a gp job
 * @return Handle which can be used with @see _mali_wait_on_handle
 */
mali_base_wait_handle _mali_gp_job_get_wait_handle(mali_gp_job_handle job);

/**
 * Set automatic freeing setting of a GP job
 * By default a job is freed after having been run.
 * This auto free logic can be disabled if the job is to be reused.
 * @note All the other postprocessing of the job is also skipped,
 * except sync handle and wait handle usage.
 * Memory will NOT be freed, command lists will be kept, etc.
 * @note The job has to be freed using _mali_gp_job_free if not auto freed
 * @param job The job set automatic free setting for
 * @param autoFree MALI_TRUE to enable auto freeing, MALI_FALSE to disable auto freeing
 */
void _mali_gp_job_set_auto_free_setting(mali_gp_job_handle job, mali_bool autoFree);

/**
 * Get automatic freeing setting of a GP job
 * Returns the current job completion auto freeing setting.
 * @warning Potential race condition if used from multiple threads
 * @param job The job to return the auto free setting of
 * @return MALI_TRUE if auto free is enabled, MALI_FALSE if disabled
 */
mali_bool _mali_gp_job_get_auto_free_setting(mali_gp_job_handle job);

/**
 * Queue a GP job for execution by the system.
 *
 * Submits the job to the Timeline system where it will eventually be scheduled to run when it no
 * longer has anything to wait on.
 *
 * The job's priority will decide where in the queue it will be put.
 *
 * A fence is created for this job which can be used to wait for the job to finish.  The fence will
 * be merged into @ref fence, if it is not MALI_NO_HANDLE.
 *
 * If a callback has been set (@ref _mali_gp_job_set_callback) it will be called at some point after
 * the call to this function was made.  This will always happen, even if we failed to start the GP
 * job.  @note The callback can be called before this function returns.
 *
 * @note This function should not be called if the GP job is piggybacking on a PP job (@ref
 * _mali_gp_job_piggyback).
 *
 * @param job Handle to the gp job to put on the execution queue.
 * @param priority Priority of the job
 * @param fence If not MALI_NO_HANDLE, the fence created for this job will be merged into this fence
 */
void _mali_gp_job_start(mali_gp_job_handle job, mali_job_priority priority, mali_fence_handle fence);

/**
 * Piggyback GP job on PP job.
 *
 * The GP job will be submitted to the device driver at the same time as a PP job when @ref
 * _mali_pp_job_start is called.  The PP job will automatically depend on the GP job, and will only
 * start if the GP job completes successfully.
 *
 * The PP job is responsible for ensuring that any callback set is called and that the GP job is
 * properly freed.
 *
 * @param job_handle Handle to GP job.
 * @param pp_job_handle Handle to PP job.
 */
void _mali_gp_job_piggyback(mali_gp_job_handle job_handle, mali_pp_job_handle pp_job_handle);



/** called by arch layer when GP job has suspended due to OOM */
void _mali_gp_job_suspended_event(mali_gp_job *job, u32 response_cookie);

/** called by arch layer when GP job has completed */
void _mali_gp_job_run_postprocessing(mali_gp_job *job, mali_job_completion_status completion_status);

/**
 * Attach a GP job to a sync object
 * Attaches the job to the list of jobs the sync object should wait for before firing
 * @note The two objects must belong to the same base context
 * @param sync Handle to the sync object to attach this job to
 * @param job Handle to the job to put on the sync list
 */
void _mali_gp_job_add_to_sync_handle(mali_sync_handle sync, mali_gp_job_handle job);

/*
 * Worker for the inlined (vs|plbu) reserve calls.
 * If room already exists it just need to return a pointer.
 * If not the list is extended and the new allocation is linked into the command list.
 * No list state is changed.
 */
MALI_STATIC_FORCE_INLINE u64 *_mali_gp_job_cmds_reserve(mali_gp_cmd_list_handle list_handle, u32 count)
{
	mali_gp_cmd_list *list = (mali_gp_cmd_list *)list_handle;

	MALI_DEBUG_ASSERT_POINTER(list);

	if (list->mapping_left >= count)
	{
		MALI_DEBUG_CODE(

		    list->reserved_mapping = list->mapping;
		    list->reserved_count = count;

		);

		return list->mapping;
	}
	else
	{
		u64 *res = _mali_gp_cmdlist_extend(list, count);
		MALI_DEBUG_CODE(

		    if (res)
	{
		list->reserved_mapping = res;
		list->reserved_count = count;
	}

	);

		return res;
	}
}
/*
 * Worker for the inlined (vs|plbu) confirm calls.
 * Just updates the list state with the confirmed usage count
 */
MALI_STATIC_FORCE_INLINE void _mali_gp_job_cmds_confirm(mali_gp_cmd_list_handle list_handle, u32 count)
{
	mali_gp_cmd_list *list = (mali_gp_cmd_list *)list_handle;

	MALI_DEBUG_ASSERT_POINTER(list);

	MALI_DEBUG_CODE(
	    MALI_DEBUG_ASSERT(list->reserved_mapping == list->mapping, ("Confirming while buffer has changed.\nHas anyone else worked on the command list in between your reserve and confirm calls?"));
	    MALI_DEBUG_ASSERT(list->reserved_count >= count, ("Confirming more than reserved"));
	);

	list->mapping += count;
	list->mapping_left -= count;
}

/**
 * Reserve VS commands.
 * Returns a linear allocation capable of holding count commands.
 * If a new allocation was needed it is linked into the list.
 * No state is changed for the VS cmd list, so it's safe to call this without confirming any use.
 * A new reserve call is allowed without the previous being confirmed.
 *
 * @param job_handle GP job who's VS command list to reserve space in
 * @param count Number of commands to reserve space to
 * @return NULL if memory couldn't be reserved, pointer to the start of a suitable allocation on success
 */
MALI_STATIC_FORCE_INLINE u64 *_mali_gp_job_vs_cmds_reserve(mali_gp_job_handle job_handle, u32 count)
{
	mali_gp_job *job = (mali_gp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(MALI_GP_JOB_STATE_BUILDING == job->state || MALI_GP_JOB_STATE_CALLBACK == job->state || MALI_GP_JOB_STATE_SYNCING == job->state,
	                  ("Changing a job which is not in the BUILDING, CALLBACK or SYNCING state is not supported"));

	return _mali_gp_job_cmds_reserve(&job->vs_cmd_list, count);
}

/**
 * Confirm VS command list usage.
 * Updates the VS command list to track the new instructions added.
 * Count has to be equal or less to a previous reserve call.
 *
 * @param job_handle GP job who's VS command list to confirm the use of
 * @param count Number of commands actually used
 */
MALI_STATIC_FORCE_INLINE void _mali_gp_job_vs_cmds_confirm(mali_gp_job_handle job_handle, u32 count)
{
	mali_gp_job *job = (mali_gp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(MALI_GP_JOB_STATE_BUILDING == job->state || MALI_GP_JOB_STATE_CALLBACK == job->state || MALI_GP_JOB_STATE_SYNCING == job->state,
	                  ("Changing a job which is not in the BUILDING, CALLBACK or SYNCING state is not supported"));

	_mali_gp_job_cmds_confirm(&job->vs_cmd_list, count);
}

/**
 * Reserve PLBU commands.
 * Returns a linear allocation capable of holding count commands.
 * If a new allocation was needed it is linked into the list.
 * No state is changed for the PLBU cmd list, so it's safe to call this without confirming any use.
 * A new reserve call is allowed without the previous being confirmed.
 *
 * @param job_handle GP job who's PLBU command list to reserve space in
 * @param count Number of commands to reserve space to
 * @return NULL if memory couldn't be reserved, pointer to the start of a suitable allocation on success
 */

MALI_STATIC_FORCE_INLINE u64 *_mali_gp_job_plbu_cmds_reserve(mali_gp_job_handle job_handle, u32 count)
{
	mali_gp_job *job = (mali_gp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(MALI_GP_JOB_STATE_BUILDING == job->state || MALI_GP_JOB_STATE_CALLBACK == job->state || MALI_GP_JOB_STATE_SYNCING == job->state,
	                  ("Changing a job which is not in the BUILDING, CALLBACK or SYNCING state is not supported"));

	return _mali_gp_job_cmds_reserve(&job->plbu_cmd_list, count);
}

/**
 * Confirm PLBU command list usage.
 * Updates the PLBU command list to track the new instructions added.
 * Count has to be equal or less to a previous reserve call.
 * Usage: After a call to this function with a count parameter greater than zero,
 *        and while in the BUILDING state, the pointer returned from the reserve()
 *        call may be used again and is expected to point to a fixed location in the command stream.
 *        That is to say that the implementation will not relocate the stream.
 *
 * @param job_handle GP job who's PLBU command list to confirm the use of
 * @param count Number of commands actually used
 */
MALI_STATIC_FORCE_INLINE void _mali_gp_job_plbu_cmds_confirm(mali_gp_job_handle job_handle, u32 count)
{
	mali_gp_job *job = (mali_gp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(MALI_GP_JOB_STATE_BUILDING == job->state || MALI_GP_JOB_STATE_CALLBACK == job->state || MALI_GP_JOB_STATE_SYNCING == job->state,
	                  ("Changing a job which is not in the BUILDING, CALLBACK or SYNCING state is not supported"));

	_mali_gp_job_cmds_confirm(&job->plbu_cmd_list, count);
}

/**
 * Add a PLBU command to this job.
 * Adds a plbu command to this job's plbu cmd list.
 * @param job Handle to the job to add a plbu cmd to
 * @param cmd The command to add to the job
 * @return Standard Mali error code. MALI_ERR_OUT_OF_MEMORY indicates that the
 * command list had to be extended for this command and that no memory was available.
 */
MALI_STATIC_FORCE_INLINE mali_err_code _mali_gp_job_add_plbu_cmd(mali_gp_job_handle job, u64 cmd) MALI_CHECK_RESULT;
MALI_STATIC_FORCE_INLINE mali_err_code _mali_gp_job_add_plbu_cmd(mali_gp_job_handle job, u64 cmd)
{
	u64 *pcmd = _mali_gp_job_plbu_cmds_reserve(job, 1);

	if (pcmd)
	{
		*pcmd = cmd;
		_mali_gp_job_plbu_cmds_confirm(job, 1);
		MALI_SUCCESS;
	}
	else
	{
		MALI_ERROR(MALI_ERR_OUT_OF_MEMORY);
	}
}

/**
 * Add multiple PLBU commands to this job.
 * Adds plbu commands to this job's plbu cmd list.
 * @param ctx The mali base context handle used in a open call earlier
 * @param job Handle to the job to add a plbu cmds to
 * @param cmds Pointer to a buffer of commands to add to the job
 * @param num_cmds Number of commands to add
 * @return Standard Mali error code. MALI_ERR_OUT_OF_MEMORY indicates that the
 * command list had to be extended for this command and that no memory was available.
 */
MALI_STATIC_FORCE_INLINE mali_err_code _mali_gp_job_add_plbu_cmds(mali_gp_job_handle job, u64 *cmds, u32 num_cmds) MALI_CHECK_RESULT;
MALI_STATIC_FORCE_INLINE mali_err_code _mali_gp_job_add_plbu_cmds(mali_gp_job_handle job, u64 *cmds, u32 num_cmds)
{
	u64 *pcmds = _mali_gp_job_plbu_cmds_reserve(job, num_cmds);

	if (pcmds)
	{
		_mali_sys_memcpy_runtime_32(pcmds, cmds, num_cmds * sizeof(*cmds));
		_mali_gp_job_plbu_cmds_confirm(job, num_cmds);
		MALI_SUCCESS;
	}
	else
	{
		MALI_ERROR(MALI_ERR_OUT_OF_MEMORY);
	}
}

MALI_STATIC_FORCE_INLINE void _mali_gp_job_modify_plbu_cmd(mali_gp_job_handle job_handle, u64 cmd, u32 index);
MALI_STATIC_FORCE_INLINE void _mali_gp_job_modify_plbu_cmd(mali_gp_job_handle job_handle, u64 cmd, u32 index)
{
	mali_gp_job *job = (mali_gp_job *)job_handle;
	u64 *plbu_cmds;

	MALI_DEBUG_ASSERT_POINTER(job);

	plbu_cmds = job->plbu_cmd_list.mapping_start;
	MALI_DEBUG_ASSERT_POINTER(plbu_cmds);

	if (plbu_cmds[index] != cmd)
	{
		plbu_cmds[index] = cmd;
	}
}

MALI_STATIC_FORCE_INLINE u64 _mali_gp_job_get_plbu_cmd(mali_gp_job_handle job_handle,  u32 index);
MALI_STATIC_FORCE_INLINE u64 _mali_gp_job_get_plbu_cmd(mali_gp_job_handle job_handle,  u32 index)
{
	mali_gp_job *job = (mali_gp_job *)job_handle;
	u64 *plbu_cmds;

	MALI_DEBUG_ASSERT_POINTER(job);

	plbu_cmds = job->plbu_cmd_list.mapping_start;
	MALI_DEBUG_ASSERT_POINTER(plbu_cmds);

	return plbu_cmds[index];
}



/**
 * Free the VS and PLBU command lists of this job without reseting it.
 * @param job A handle to the job to free the VS and PLBU command lists of
 */
void _mali_gp_job_free_cmdlists(mali_gp_job_handle job);

/**
 * Add a VS command to this job.
 * Adds a vs command to this job's vs cmd list.
 * @param job Handle to the job to add a vs cmd to
 * @param cmd The command to add to the job
 * @return Standard Mali error code. MALI_ERR_OUT_OF_MEMORY indicates that the
 * command list had to be extended for this command and that no memory was available.
 */
MALI_STATIC_FORCE_INLINE mali_err_code _mali_gp_job_add_vs_cmd(mali_gp_job_handle job, u64 cmd)
{
	u64 *pcmd = _mali_gp_job_vs_cmds_reserve(job, 1);

	if (pcmd)
	{
		*pcmd = cmd;
		_mali_gp_job_vs_cmds_confirm(job, 1);
		MALI_SUCCESS;
	}
	else
	{
		MALI_ERROR(MALI_ERR_OUT_OF_MEMORY);
	}
}

/**
 * Add multiple VS command to this job.
 * Adds vs commands to this job's vs cmd list.
 * @param job Handle to the job to add a vs cmd to
 * @param cmds Pointer to a buffer of commands to add to the job
 * @param num_cmds Number of commands to add
 * @return Standard Mali error code. MALI_ERR_OUT_OF_MEMORY indicates that the
 * command list had to be extended for this command and that no memory was available.
 */
MALI_STATIC_FORCE_INLINE mali_err_code _mali_gp_job_add_vs_cmds(mali_gp_job_handle job, u64 *cmds, u32 num_cmds)
{
	u64 *pcmds = _mali_gp_job_vs_cmds_reserve(job, num_cmds);

	if (pcmds)
	{
		_mali_sys_memcpy_runtime_32(pcmds, cmds, num_cmds * sizeof(*pcmds));
		_mali_gp_job_vs_cmds_confirm(job, num_cmds);
		MALI_SUCCESS;
	}
	else
	{
		MALI_ERROR(MALI_ERR_OUT_OF_MEMORY);
	}
}

/**
 * Setting the tile heap for the job.
 * If the job uses a heap which can be extended this function has to be called
 * @param job_handle The GP job to attach the heap to
 * @param heap The heap to attach
 */
MALI_STATIC_FORCE_INLINE void _mali_gp_job_set_tile_heap(mali_gp_job_handle job_handle, mali_mem_handle heap)
{
	mali_gp_job *job = (mali_gp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);

	job->plbu_heap = heap;
}

#if MALI_INSTRUMENTED || MALI_DUMP_ENABLE
/**
 * Setting pointer_array_handle for the plbu-job.
 * This function will not do anything except in Dumping and Instrumented build, and in both
 * cases are the content stored. The plbu job will both read and write to this memory,
 * so it must be taken a backup of, if we intend to run the job several times.
 * Instrumented use it so that the same job can be executed several times.
 * Dumping use it so that we can make a proper dump of the job after it has crashed.
 * @param job_handle The GP job to attach the heap to
 * @param heap The heap to attach
 */
MALI_STATIC_FORCE_INLINE void _mali_gp_job_set_plbu_pointer_array(mali_gp_job_handle job_handle, mali_mem_handle pointer_array_handle)
{
	MALI_DEBUG_ASSERT_POINTER(job_handle);
	MALI_DEBUG_ASSERT_POINTER(pointer_array_handle);

#if MALI_INSTRUMENTED
	{
		/* Need to restore the pointer array between each re-run of a GP job */
		mali_gp_job *job = (mali_gp_job *)job_handle;
		job->perf_ctx.pointer_array = pointer_array_handle;
	}
#endif

#ifdef MALI_DUMP_ENABLE
	{
		/*
		 * Store the memory_handle that contains the pointer_array used by the PLB.
		 * This is necessary to know to be able to patch the memory before dumping when DUMP_CRASHED is enabled.
		 */
		mali_gp_job *job = (mali_gp_job *)job_handle;
		job->dump_info.pointer_array_user = pointer_array_handle;
	}
#endif
}
#endif

/**
 * Set a frame_nr on the job. It can be used for aborting jobs. The frame_nr
 * can be given to the job_abort function, and it will abort all jobs in the
 * context with this frame_id.
 * @param job_handle Set frame_id on this job
 * @param frame_id   The frame_id we want to set.
 * @see _mali_base_frame_id_get_new()
 */
MALI_STATIC_FORCE_INLINE void _mali_gp_job_set_frame_id(mali_gp_job_handle job_handle, mali_base_frame_id frame_id)
{
	mali_gp_job *job = (mali_gp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(MALI_GP_JOB_STATE_BUILDING == job->state, ("Modifying a job which is not in the BUILDING state is not supported"));

	job->frame_id = frame_id;
}

/**
 *  Set job identity, which is defined by unique frame builder id and flush id. Frame builder uses this
 *  to tag all GP jobs sent to HW (See @c _internal_flush).
 *
 *  @param job_handle   Job handle
 *  @param fb_id        Frame Builder ID
 *  @param flush_id     Flush ID
 */
MALI_STATIC_FORCE_INLINE void _mali_gp_job_set_identity(mali_gp_job_handle job_handle, mali_base_frame_id fb_id, mali_base_flush_id flush_id)
{
	mali_gp_job *job = (mali_gp_job *)job_handle;

	MALI_DEBUG_ASSERT_POINTER(job);
	MALI_DEBUG_ASSERT(MALI_GP_JOB_STATE_BUILDING == job->state, ("Modifying a job which is not in the BUILDING state is not supported"));

	_mali_arch_gp_job_set_identity(job, fb_id, flush_id);
}

#if MALI_INSTRUMENTED

/**
 * Set the array that tells which counters to read for a job.
 *
 * The perf_counters array tells which counters on mali we will readout after
 * the job has run.
 *
 * \param job_handle gp job handle
 * \param perf_counters an array with the counter indices to read
 * \param perf_counters_count the number of counters in the perf_counters array
 */
void _mali_gp_job_set_counters(mali_gp_job_handle job_handle, u32 *perf_counters, u32 perf_counters_count);

/**
 * Get the array that tells which counters to read / has been read for a job.
 *
 * The perf_counters array tells which counters on mali we will readout after
 * the job has run.
 *
 * \param job_handle gp job handle
 * \param perf_counters returns the array with the counter indices to read
 * \param perf_counters_count returns the number of counters in the perf_counters array
 */
void _mali_gp_job_get_counters(mali_gp_job_handle job_handle, u32 **perf_counters, u32 *perf_counters_count);

/**
 * Set the instrumented results before the job has been run.
 * @param job_handle job to set results pointer on
 * @param res an array of u32 values that will be filled with results when
 *            the job is run
 */
void _mali_gp_job_set_results_pointer(mali_gp_job_handle job_handle, u32 *res);

/**
 * Get the instrumented results after a job has been run.
 *
 * \param job_handle job to get results from
 * \return an array of u32 values with the results, in the same order as
 *         the counters from _mali_instrumented_gp_job_set_counters.
 */
u32 *_mali_gp_job_get_results_pointer(mali_gp_job_handle job_handle);

/**
 * Set plbu stack on instrumented gp job.
 *
 * The instrumented job keeps a mali_mem_handle reference to the plbu
 * stack allocated by the frame builder, so that it can overwrite it after
 * each run of the job.
 *
 * \param job_handle job to set plbu stack on
 * \param plbu_stack_handle the plbu stack
 */
void _mali_gp_job_set_plbu_stack_handle(mali_gp_job_handle job_handle, mali_mem_handle plbu_stack_handle);

#endif /* MALI_INSTRUMENTED */

/**
 * Add a fence to this job.
 *
 * The fence will be merged (@ref _mali_fence_merge) with any fences previously added to the job.
 *
 * @param job_handle Handle to job.
 * @param fence_handle Handle to fence that will be added to the job fence.
 */
void _mali_gp_job_add_fence(mali_gp_job_handle job_handle, mali_fence_handle fence_handle);


#ifdef __cplusplus
}
#endif /* _cplusplus */

#endif /* _MALI_GP_JOB_H_ */
