/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2011, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_GP_JOB_TYPES_H_
#define _MALI_GP_JOB_TYPES_H_

#include <base/mali_types.h>
#include <base/mali_debug.h>
#include <mali_arch_gp_job_types.h>
#include <base/common/base_common_sync_handle.h>
#include <base/mali_fence.h>
#if defined(MALI_DUMP_ENABLE)
#include "base/dump/mali_dumping.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif /* _cplusplus */

typedef void *mali_gp_job_handle;
typedef void *mali_gp_cmd_list_handle;

/**
 * Definition of GP job state type.
 *
 * Used to indicate in which state a GP job is in.
 *
 * We have these states:
 *      Pool: A job descriptor which is not currently in use
 *      Building: A job which the user can modify and start
 *  Separate states for each subqueue a job can be a part of:
 *       Queued: Queued for running on the hw. (VS or PLBU)
 *       Running: Currently running on the hw. (VS or PLBU)
 *      Postprocessing Pending: Waiting for for post processing after hw run (on both cores if requested)
 *      Callback: Running a user registered callback as part of post processing
 *      Memory cleanup: Cleaning memory registered for auto cleanup during postprocessing.
 *
 * A job retrieved through the new_job interface originates in the Building state.
 * A job can only be modified through our public API if it's in the Building state.
 * When the user calls start on the job it switches to Queued or Running state (for each core requested),
 * blocking any changes to the job afterwards.
 * The other states are used to track a job's status through post processing, to
 * ease debugging / error tracking.
 *
 * Acceptable transitions between states are:
 *      Pool: to Building
 *      Building: to Running, to Queued
 *      Queued: to Running (per core)
 *      Running: to Queued, to Postprocessing Pending (per core)
 *      Postprocessing Pending: to Callback
 *      In Callback: to Memory Cleanup
 *      Memory Cleanup: To Pool
 *
 * These rules are enforced in the public accessible functions.
 * Therefore, a user can only call i.e. free on a job which
 * is in the building state.
 * If the job has been started, a free will be denied/reported.
 * Starting of a job which has already been started
 * will also be denied/reported.
 */

/**
 * Enum defintion for job state tracking
 * Used to track the state a job is in to prohibit
 * manipulation of the job after the job has been started
 */
typedef enum mali_gp_job_state
{
	MALI_GP_JOB_STATE_POOL                 = 0x00000001,
	MALI_GP_JOB_STATE_BUILDING             = 0x00000002,
	MALI_GP_JOB_STATE_RUNNING              = 0x00000004,
	MALI_GP_JOB_STATE_POSTPROCESS_PENDING  = 0x00000005,
	MALI_GP_JOB_STATE_CALLBACK             = 0x00000006,
	MALI_GP_JOB_STATE_MEMORY_CLEANUP       = 0x00000007,
	MALI_GP_JOB_STATE_SYNCING              = 0x00000008,
	MALI_GP_JOB_STATE_WAKEUP               = 0x00000009,
	MALI_GP_JOB_STATE_PIGGYBACKING         = 0x0000000a
} mali_gp_job_state;

/**
 * Definition of the gp callback function
 * Called when the job has completed.
 * Registered using _mali_gp_job_set_callback on a job
 * @param ctx The Mali base context handle the job was created in
 * @param cb_param User defined callback parameter
 * @param completion_status Job completion status
 * @param job_handle Handle for job that is completed when this callback is called
 * @return True if the callback successfully completed the job and memory can be reclaimed.
 *         False if the job was not completed and the job should be kept alive
 */
typedef mali_bool(*mali_cb_gp)(mali_base_ctx_handle ctx, void *cb_param, mali_job_completion_status completion_status, mali_gp_job_handle job_handle);

/**
 * Definition of the command list type.
 * A command list is built up of one or more mali memory blocks.
 * If more than one block is needed for the commands a special jump
 * instruction links the blocks together.
 *
 * @note The jump instruction for the PLBU and VS is currently the same. If that changes this code need to know for which unit it's building a command list.
 */
typedef struct mali_gp_cmd_list
{
	u64 *mapping;
	u32 mapping_left;

	MALI_DEBUG_CODE
	(
	    u64 *reserved_mapping;
	    u32   reserved_count;
	)

	mali_mem_handle first;  /**< first mali memory block, this is the start of the command list */
	mali_mem_handle last; /**< last memory block. This is the block we are currently working on */

	u32   skip_count; /**< The first N instructions are usually used to set up the unit.
                       * If linking jobs this setup can be skipped. This field specifies how many instructions we should skip.
                       */

	u32   mapping_default_size; /**< Number of commands to minimum allocate in a new block */
	u32   mapping_size; /**< Number of instructions per memory block / mapping */
	u32   mapping_reserved; /**< We reserve some space for the linking of jobs, this specifies how may instructions we need */

	u64 *mapping_start;  /**< Current cpu mapping of the mali memory block */

	mali_addr end_address; /**< The address of the last command to execute */
} mali_gp_cmd_list;




#if MALI_INSTRUMENTED
typedef struct mali_base_instrumented_gp_context
{
	/* perf_counters contains the activated counters. The values contain
	 * different values, depending on if it's the original job or a duplicated
	 * job:
	 *
	 * on the original job, perf_values stores the actual values of the
	 * counters. perf_counters_count stores the number of counters to be read
	 * in total, [1-u32_max>.
	 *
	 * On the duplicated jobs, perf_values points to the location in
	 * the original job where the results should be stored. counter_id stores
	 * the ids of the hardware registers to be read. perf_counters_count stores
	 * the number of counters to be read by this job, which is either 1 or 2.
	 *
	 * pointer_array contains a pointer to the actual pointer array that
	 * gets used for the job. for the duplicated jobs, this handle points to a
	 * memory block copy of the original pointer array. the original pointer
	 * array is reset before each duplicate run, so that the final outcome will
	 * reflect a single run of the original job.
	 * The same applies for the plbu_stack mem_handle.
	 */
	u32                            *perf_counters;
	u32                             perf_counters_count;
	u32                            *perf_values;

	u32                             counter_id[2];
	u32                             num_counters_to_read;
	u32                            *counter_result[2];

	u32                             l2_perf_counters_count;
	u32                             l2_counter_id[2];
	u32                             l2_perf_values[2];

	mali_job_completion_status      job_result;

	/* PLBU stack and pointer array for copying back */
	mali_mem_handle                 plbu_stack;
	mali_mem_handle                 pointer_array;

} mali_base_instrumented_gp_context;
#endif





/**
 * The GP job struct.
 */
typedef struct mali_gp_job
{
	/* debug only? */
	mali_gp_job_state       state;             /**< The state this job is in */

	mali_gp_cmd_list        vs_cmd_list;       /**< The VS command list */
	mali_gp_cmd_list        plbu_cmd_list;     /**< The PLBU command list */

	mali_base_ctx_handle    ctx;               /**< The base context this job was created in */
	mali_bool               autoFree;          /**< Flag indicating if the job object should be freed during postprocessing */

	mali_cb_gp              callback;          /**< Callback set to run on completion */
	void                   *callback_argument; /**< Argument to give to callback */

	mali_base_wait_handle   wait_handle;       /**< Wait handle attached to this job, when completed this object is notified */
	mali_mem_handle         freelist;          /**< Memory to free after running the job */
	mali_sync_handle        sync;              /**< Sync handle to notify of job completion */

	mali_base_frame_id      frame_id;          /**< Frame id which represents the frame multiple jobs might belong to */
	mali_mem_handle         plbu_heap;         /**< The PLBU heap which is in use for this job */

	struct mali_fence       fence;             /**< Fence representing what this job has to wait on before starting */
	mali_bool               piggybacking;      /**< If MALI_TRUE, this GP job will piggyback on a PP job. */

	mali_arch_gp_job        arch_data;

#if MALI_INSTRUMENTED
	mali_base_instrumented_gp_context   perf_ctx;
#endif

#ifdef MALI_DUMP_ENABLE
	mali_dump_job_info_gp               dump_info;
#endif

} mali_gp_job;

#ifdef __cplusplus
}
#endif /* _cplusplus */

#endif /* _MALI_GP_JOB_TYPES_H_ */
