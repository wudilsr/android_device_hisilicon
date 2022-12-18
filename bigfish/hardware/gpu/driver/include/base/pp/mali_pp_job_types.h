/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2014 ARM Limited
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

#ifndef _MALI_PP_JOB_TYPES_H_
#define _MALI_PP_JOB_TYPES_H_

#include <base/mali_types.h>
#include <base/mali_debug.h>
#include <mali_arch_pp_job_types.h>
#include <mali_render_regs.h>
#include <base/common/base_common_sync_handle.h>
#include <base/mali_fence.h>
#include "mali200_core.h"
#if defined(MALI_DUMP_ENABLE)
#include "base/dump/mali_dumping.h"
#endif
#include <base/gp/mali_gp_job_types.h>

/**
 * Definition of the handle type used to represent a pp job
 */
typedef void *mali_pp_job_handle;

/**
 * Flags to indicate write-back units
 */
typedef enum mali_pp_job_wbx_flag
{
	MALI_PP_JOB_WB0 = 1,
	MALI_PP_JOB_WB1 = 2,
	MALI_PP_JOB_WB2 = 4,
} mali_pp_job_wbx_flag;

/**
 * Definition of the pp callback function
 * Called when a job has completed
 * @param ctx A mali base context handle
 * @param cb_param User defined callback parameter
 * @param completion_status Job completion status
 * @param job_handle Handle for job that is completed when this callback is called
 * @return void
 */
typedef void (*mali_cb_pp)(mali_base_ctx_handle ctx, void *cb_param, mali_job_completion_status completion_status, mali_pp_job_handle job_handle);

#if defined(USING_MALI450)

typedef enum m400_tile_block_size
{
	M400_TILE_BLOCK_SIZE_128  = 0,
	M400_TILE_BLOCK_SIZE_256  = 1,
	M400_TILE_BLOCK_SIZE_512  = 2,
	M400_TILE_BLOCK_SIZE_1024 = 3,
} m400_tile_block_size;

typedef struct m450_pp_job_frame_info
{
	u32 slave_tile_list_mali_address;
	u32 master_x_tiles;
	u32 master_y_tiles;
	enum m400_tile_block_size size;
	u32 binning_pow2_x;
	u32 binning_pow2_y;
	u32 stack_size_per_core;
} m450_pp_job_frame_info;

#endif


/**
 * Definition of pp job state type.
 *
 * Used to indicate in which state a pp job is in.
 *
 * We have these states:
 *  Pool: A job descriptor which is not currently in use
 *  Building: A job which the user can modify and start
 *  Running: Currently running on the hw
 *  Postprocessing Pending: Waiting for for post processing after hw run
 *  Callback: Running a user registered callback as part of post processing
 *  Memory cleanup: Cleaning memory registered for auto cleanup during postprocessing.
 *
 * A job retrieved through the new_job interface originates in the Building state.
 * A job can only be modified through our public API if it's in the Building state.
 * When the user calls start on the job it switches to Queued or Running state,
 * blocking any changes to the job afterwards.
 * The other states are used to track a job's status through post processing, to
 * ease debugging / error tracking.
 *
 * Acceptable transitions between states are:
 *  Pool: to Building
 *  Building: to Running
 *  Running: to Postprocessing Pending
 *  Postprocessing Pending: to Callback
 *  In Callback: to Memory Cleanup
 *  Memory Cleanup: To Pool
 *
 * These rules are enforced in the public accessible functions.
 * Therefore, a user can only call i.e. free on a job which
 * is in the building state.
 * If the job has been started, a free will be denied/reported.
 * Starting of a job which has already been started
 * will also be denied/reported.
 */

typedef enum mali_pp_job_state
{
	MALI_PP_JOB_POOL                    = 0x01, /* unused, will be used by the pool system */
	MALI_PP_JOB_BUILDING                = 0x02,
	MALI_PP_JOB_RUNNING                 = 0x04,
	MALI_PP_JOB_POSTPROCESS_PENDING     = 0x05,
	MALI_PP_JOB_CALLBACK                = 0x06,
	MALI_PP_JOB_MEMORY_CLEANUP          = 0x07,
	MALI_PP_JOB_SYNCING                 = 0x08,
	MALI_PP_JOB_WAKEUP                  = 0x09
} mali_pp_job_state;

#if MALI_INSTRUMENTED
typedef struct mali_pp_instrumented_context
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
	 * the number of counters to be read by this job, which is either 1 or 2.*/
	u32             *perf_counters;
	u32              perf_counters_count;
	u32             *perf_values[_MALI_PP_MAX_SUB_JOBS];
	u32              counter_id[2];

	u32              l2_perf_counters_count;
	u32              l2_counter_id[2];
	u32              l2_perf_values[2];
	u32              l2_perf_values_raw[2];

	mali_mem_handle  wbx_mem[MALI200_WRITEBACK_UNIT_COUNT];
} mali_pp_instrumented_context;
#endif


typedef struct mali_pp_job
{
	mali_pp_job_state               state;

	mali_base_ctx_handle            ctx;
	mali_cb_pp                      callback;
	void                           *callback_argument;
	mali_base_wait_handle           wait_handle;
	mali_mem_handle                 freelist;
	mali_sync_handle                sync;
	mali_base_frame_id              frame_id;
	mali_bool                       is_window_surface; /**< MALI_TRUE if this job is for a window surface rendering */

	struct mali_fence               fence;             /**< Fence representing what this job has to wait on before starting */

	mali_arch_pp_job                arch_data;
	mali_gp_job_handle              gp_job_handle;     /**< A handle to a piggybacking GP job, or MALI_NO_HANDLE if none. */

#if defined(USING_MALI450)
	m450_pp_job_frame_info          info;
#endif /* defined(USING_MALI450) */

#if MALI_INSTRUMENTED
	mali_pp_instrumented_context perf_ctx;
#endif /* MALI_INSTRUMENTED */

#if defined(MALI_DUMP_ENABLE)
	mali_dump_job_info              dump_info;
#endif /* MALI_DUMP_ENABLE */

#if defined(MALI_USE_DMA_BUF) && defined(DMA_BUF_ON_DEMAND)
	u32 num_memory_cookies;
	u32 *memory_cookies;
#endif

} mali_pp_job;


#endif
