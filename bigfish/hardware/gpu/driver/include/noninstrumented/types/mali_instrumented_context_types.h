/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_INSTRUMENTED_CONTEXT_TYPES_H_
#define _MALI_INSTRUMENTED_CONTEXT_TYPES_H_

#include "mali_system.h"
#include "shared/mali_named_list.h"
#include "mali_instrumented_log_types.h"
#include "shared/mali_linked_list.h"
#include "sw_profiling_types.h"

/* Forward declarations */
struct mali_counter;
struct mali_counter_group;
struct mali_instrumented_frame;


/** A mask of Bools telling what kinds of instrumentation output to produce.
 * To be OR-ed together into an options mask: values are powers of 2.
 */
typedef enum mali_instrument_option
{
	INSTRUMENT_DUMP_COUNTERS = 1,     /* do produce a PAT dump file with counter values */
	INSTRUMENT_IS_PAT_DUMPING = 2,    /* is currently producing a PAT dump file */
	INSTRUMENT_DUMP_FRAMEBUFFER = 4,  /* dump frame buffers for PAT */
	INSTRUMENT_PRINT_COUNTERS = 8,    /* print counter values */
	INSTRUMENT_WAIT_FOR_MRI = 16,     /* unconditionally wait for MRI commands */
	INSTRUMENT_LOOK_FOR_MRI = 32,     /* stop if there is an MRI command, handle it */
	INSTRUMENT_IS_MRI_ACTIVE = 64,    /* has a MRI connection to a client */
	INSTRUMENT_DUMP_FRAMEBUFFER_HEX = 128   /* dump frame buffers for debug features */
} mali_instrument_option;


/**
 * Instrumented context.
 *
 * There should be one instrumented context per EGL context.
 */
typedef struct mali_instrumented_context
{
	mali_lock_handle lock;           /**< For thread safe access to this object */
	mali_linked_list tls_structures; /**< Linked list containing all the dynamically
                                          allocated structures in the thread local
                                          storages of the various threads */

	struct mali_counter *counters;    /**< An array of mali_counters */
	u32 num_counters;                 /**< The size of the counter array */
	mali_named_list *counter_map;     /**< Maps unique counter id to an index in the counter array */

	struct mali_counter_group *header_root;    /**< Counter header tree root */
	struct mali_counter_group *current_header; /**< A pointer to the current header block while
                                                 we are constructing the header tree */
	mali_bool sampling;
	mali_bool inited;                /**< whether the context has been properly initialized,
                                         i.e. _instrumented_finish_init has been called */
	mali_file *dump_file;
	int options_mask;                /**< A set of Bools identified by mali_instrument_option */

	u32 current_frame_no;
	struct mali_instrumented_frame *current_frame; /**< Current active instrumented frame, contains counters for frame and unique frame_no. */
	mali_linked_list working_frames; /**< List of frames which are swapped out, but not yet finalized by instrumented */

	void *mrp_context;               /**< The MRPPeer object used for MRI communications */

	/* Logging */
	mali_log_level log_level;        /**< "global" log level for this context */
	mali_file *log_file;             /**< the logging file */
	mali_log_callback *callbacks;    /**< an array of callbacks registered */
	u32 numcallbacks;                /**< the number of callbacks in the callbacks array */

#if !defined(USING_MALI200)
	u32 prev_l2_perf_counters_count;           /**< Temporary hold the number of counters for the last completed frame */
	u32 prev_l2_perf_counter_id[2];            /**< Temporary hold the Ids from the last completed PP frame */
	u32 prev_l2_perf_values_raw[2];            /**< Temporary hold the values from the last completed frame */
#endif

	u32 egl_start_index;              /**< index into counters where the EGL counters exported to the plug-in begin */
	u32 egl_num_counters;             /**< the number of EGL counters exported to the plug-in, starting at egl_start_index */

	u32 gles_start_index;             /**< index into counters where the GLES counters exported to the plug-in begin */
	u32 gles_num_counters;            /**< the number of GLES counters exported to the plug-in, starting at gles_start_index */

	u32 vg_start_index;               /**< index into counters where the VG counters exported to the plug-in begin */
	u32 vg_num_counters;              /**< the number of VG counters exported to the plug-in, starting at vg_start_index */

	u32 gp_start_index;               /**< index into counters where the GP counters exported to the plug-in begin */
	u32 gp_num_counters;              /**< the number of GP counters exported to the plug-in, starting at gp_start_index */

	u32 pp_start_index[MALI_MAX_PP_SPLIT_COUNT];    /**< index into counters where the PP counters exported to the plug-in begin, index 0 for PP0, and so on */
	u32 pp_num_counters[MALI_MAX_PP_SPLIT_COUNT];   /**< the number of PP0 counters exported to the plug-in, starting at pp0_start_index, index 0 for PP0 and so on */
} mali_instrumented_context;


/**
 * Instrumented frame.
 *
 * There is one of these per actual frame that's rendered to a screen or whatever.
 * It contains a set of counter values for the frame.
 */
typedef struct mali_instrumented_frame
{
	mali_atomic_int ref_count;            /**< Reference count this object in order to know when we can finish it */

	u32 frame_no;
	mali_instrumented_context *instrumented_ctx;
	s64 *counter_values;                  /**< An array to be used with the same indices as
                                               counters  in mali_instrumented_context */
	mali_bool profiling_buffer_realloced; /**< MALI_TRUE if the profiling buffer has been realloced
                                               this frame. */
#if !defined(USING_MALI200)
	u32 l2_perf_counters_count;           /**< Temporary hold the number of counters for the last completed PP job for this frame */
	u32 l2_perf_counter_id[2];            /**< Temporary hold the Ids from the last completed PP job for this frame */
	u32 l2_perf_values_raw[2];            /**< Temporary hold the values from the last completed PP job for this frame */
#endif
} mali_instrumented_frame;


/**
 * Thread local storage used by the instrumented drivers.
 *
 * Used to store buffers and caches that we don't want to allocate all the time or on stack.
 *
 * It is allocated and returned by _instrumented_get_tls. Currently this is
 * allocated on demand in _instrumented_get_tls, and freed by destroy_instrumented_context.
 *
 * Again, note that the data is not stored per context, but per thread running.
 * */
typedef struct mali_instrumented_tls_struct
{
	char log_message[INSTRUMENTED_LOG_BUFFER_SIZE];  /**< The incoming message, with useful debug information prepended */
	profiling_buffer _mali_profiling_buffer;  /**< Buffer for profiling data recorded in this thread */
	u32 realloc_count;                        /**< Number of times the _mali_profiling_buffer has been reallocated (since last analyze) */
} mali_instrumented_tls_struct;

#endif /* _MALI_INSTRUMENTED_CONTEXT_TYPES_H_ */


