/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_COUNTERS_H_
#define _MALI_COUNTERS_H_

#include "mali_instrumented_counter_types.h"
#include "mali_instrumented_context_types.h"
#include "shared/mali_named_list.h"
#include "mali_instrumented_frame.h"

#include "sw_profiling.h"

/*
 * Counter fetching
 */

/**
 * Return a pointer to the root header.
 *
 * This includes its name, its description and pointers to its children. The
 * header blocks are organized in a tree structure that organizes the counters
 * into logical groups.
 *
 * In this tree, a node can either have other counter_group children, or a list
 * of counter children. Which one is used is stored in the leaf boolean,
 * because counters can only be stored in leaves.
 *
 * @param ctx                the instrumented context
 * @return                   a pointer to the root group
 */
MALI_IMPORT
const mali_counter_group *_instrumented_get_counter_headers(mali_instrumented_context *ctx) MALI_CHECK_RESULT;

/**
 * Retrieve counter information.
 *
 * The counter information describes this counter by itself. Note that because
 * counters are organized in trees, a counter can seldom be completely described
 * by only its own information; much also lies in the context in which it
 * has been registered (not as in mali_instrumented_context, but its place in
 * the tree).
 *
 * @param ctx                the instrumented context
 * @param counter_index      the index of the counter to retrieve info from
 * @return                   a pointer to the _mali_counter_info struct. NULL if
 *                           index out of bounds.
 */
MALI_IMPORT
const mali_counter_info  *_instrumented_get_counter_information(mali_instrumented_context *ctx,
        u32 counter_index) MALI_CHECK_RESULT;

/**
 * Returns the number of counters stored in the given context.
 *
 * @param ctx               the instrumented context
 * @return the number of counters stored in the given context.
 */
MALI_IMPORT
int _instrumented_get_number_of_counters(mali_instrumented_context *ctx) MALI_CHECK_RESULT;

/**
 * Activate an array of counters.
 *
 * @param ctx                the instrumented context
 * @param counter_indices    array containing the indices of the counters
 *                           to be activated. Note: these are array indices, and
 *                           not the counter id's used when registering the
 *                           counter.
 * @param counter_amount     the number of elements in the
 *                           counter_indices array
 * @return                   MALI_ERR_FUNCTION_FAILED if any indices out of
 *                           range, else MALI_ERR_NO_ERROR
 */
MALI_IMPORT
mali_err_code _instrumented_activate_counters(mali_instrumented_context *ctx,
        const unsigned int *counter_indices, unsigned int counter_amount) MALI_CHECK_RESULT;

/**
 * Deactivate an array of counters.
 *
 * @param ctx                he instrumented context
 * @param counter_indices    array containing the indices of the counters
 *                           to be deactivated. Note: these indices are
 *                           relative to the internal array of counters,
 *                           and not the ids given when registering the
 *                           counters.
 * @param counter_amount     the number of elements in the
 *                           counter_indices array
 *
 * @return                   MALI_ERR_FUNCTION_FAILED if any indices out of
 *                           range, else MALI_ERR_NO_ERROR
 */
MALI_IMPORT
mali_err_code _instrumented_deactivate_counters(mali_instrumented_context *ctx,
        const unsigned int *counter_indices, unsigned int counter_amount) MALI_CHECK_RESULT;


/** Activate the counter for use in computing a derived 'counter'.
 * @param ctx       the instrumented context
 * @param id        the counter specified by its enum value
 */
MALI_IMPORT
void _instrumented_activate_counter_derived(mali_instrumented_context *ctx, u32 id);


/**
 * Register a counter.
 *
 * @param ctx                the instrumented context
 * @param id                 unique identifier for the counter.
 * @param name               short name for the counter.
 * @param description        long, detailed description of the counter
 * @param unit               the unit the counter is in. For example f/s.
 * @param scale_to_hz        enum that specifies how the counter should scale to compansate
 *                           for lower clock speeds on FPGA vs. ASIC. Legal values are
 *                           MALI_SCALE_NONE if the counter should not be scaled.
 *                           MALI_SCALE_NORMAL if the counter should be scaled according to
 *                           frequencies and MALI_SCALE_INVERSE if the counter should be
 *                           scaled inversely according to frequencies. Should be
 *                           MALI_SCALE_NONE for most counters.
 * @return                   MALI_ERR_NO_ERROR if all ok
 */
MALI_IMPORT
mali_err_code _instrumented_register_counter(mali_instrumented_context *ctx, u32 id,
        const char *name, const char *description, const char *unit,
        mali_frequency_scale scale_to_hz) MALI_CHECK_RESULT;

/**
 * Register a counter group.
 *
 * Used to make a hierachy of performance counters. Typical usage:
 * @code
 * _instrumented_start_group("Mali200 Performance", "", 20);
 * ...
 * _instrumented_end_group();
 * _instrumented_start_group("VG counters", "OpenVG software counters", 0);
 * _instrumented_start_group("VG calls", "OpenVG API calls", 0);
 * _instrumented_register_counter(VG_DRAW_PATH_COUNTER, "DrawPath", "Calls to DrawPath", ... );
 * _instrumented_register_counter(VG_DRAW_IMAGE_COUNTER, "DrawImage", "Calls to DrawImage", ... );
 * ...
 * _mali_end_counter group();
 * _instrumented_start_group("Timings", "OpenVG timing counters", 0);
 * _instrumented_register_counter(VG_DRAW_PATH_TIMING, ...);
 * ...
 * _instrumented_end_group();
 * _instrumented_end_group();
 * @endcode
 *
 * Make sure to call _instrumented_end_group() after registering counters.
 *
 * @param ctx                the instrumented context
 * @param name               short name for the counter group (e.g. "VG API calls")
 * @param description        long description for the counter group. use "" for no description.
 * @param frequency          the frequency of the child counters for this group in MHz. should
 *                           be used for core-specific groups (e.g. "Mali200"), all children with
 *                           the "scale_to_hz" flag will be scaled with this frequency. set to 0
 *                           if it's not used.
 */
MALI_IMPORT
mali_err_code _instrumented_start_group(mali_instrumented_context *ctx,
                                        const char *name, const char *description, u32 frequency);

/**
 * End a counter group.
 *
 * See @a _instrumented_start_group().
 *
 * @see _instrumented_start_group.
 */
MALI_IMPORT
void _instrumented_end_group(mali_instrumented_context *ctx);


/**
 * Set a counter value.
 *
 * @param id                 unique identifier for the counter
 * @param frame              pointer to the instrumented frame
 * @param value              the new value for the counter
 */
MALI_IMPORT
void _instrumented_set_counter(u32 id, mali_instrumented_frame *frame, s64 value);

/**
 * Add to a counter value.
 *
 * @param id                 unique identifier to the counter
 * @param frame              pointer to the instrumented frame
 * @param value              the value to add to the counter
 */
MALI_IMPORT
void _instrumented_add_to_counter(u32 id, mali_instrumented_frame *frame, s64 value);

/**
 * Get single counter value.
 *
 * @param id                 unique identifier to the counter
 * @param frame              pointer to the instrumented frame
 * @return                   the counter value
 */
MALI_IMPORT
s64 _instrumented_get_counter(u32 id, mali_instrumented_frame *frame);

/**
 * Checks if a counter is active (enabled).
 *
 * @param ctx                the instrumented context
 * @return                   MALI_TRUE if the counter is active, MALI_FALSE if
 *                           it's disabled or does not exist.
 */
MALI_IMPORT
mali_bool _instrumented_is_counter_active(mali_instrumented_context *ctx, u32 id) MALI_CHECK_RESULT;

/**
 * Checks whether sampling (counting) is enabled. This will always
 * return MALI_FALSE on non-instrumented builds, so use it around potentially
 * intrusive counter-setting code.
 *
 * @param ctx                the context to check the samling state on.
 * @return MALI_TRUE if sampling is enabled, MALI_FALSE if not.
 */
MALI_IMPORT
mali_bool MALI_CHECK_RESULT _instrumented_is_sampling_enabled(mali_instrumented_context *ctx);

/**
 * Free the memory used by a counter group.
 *
 * @param group              the counter group to free
 */
MALI_IMPORT
void _instrumented_counter_free_group(mali_counter_group *group);

/**
 * Free the memory used by a counter.
 *
 * @param counter            the counter to free
 */
MALI_IMPORT
void _instrumented_free_counter_info(mali_counter *counter);

/**
 * Print counter stats to stdout.
 *
 * @param frame              frame to print stats from
 */
MALI_IMPORT
void _instrumented_print_counters(mali_instrumented_frame *frame);

/**
 * Mark the beginning of EGL counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 */
MALI_IMPORT void _instrumented_register_counter_egl_begin(mali_instrumented_context *ctx);

/**
 * Mark the end of EGL counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 */
MALI_IMPORT void _instrumented_register_counter_egl_end(mali_instrumented_context *ctx);

/**
 * Mark the beginning of OpenGL ES counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 */
MALI_IMPORT void _instrumented_register_counter_gles_begin(mali_instrumented_context *ctx);

/**
 * Mark the end of OpenGL ES counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 */
MALI_IMPORT void _instrumented_register_counter_gles_end(mali_instrumented_context *ctx);

/**
 * Mark the beginning of OpenVG counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 */
MALI_IMPORT void _instrumented_register_counter_vg_begin(mali_instrumented_context *ctx);

/**
 * Mark the end of OpenVG counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 */
MALI_IMPORT void _instrumented_register_counter_vg_end(mali_instrumented_context *ctx);

/**
 * Mark the beginning of GP counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 */
MALI_IMPORT void _instrumented_register_counter_gp_begin(mali_instrumented_context *ctx);

/**
 * Mark the end of GP counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 */
MALI_IMPORT void _instrumented_register_counter_gp_end(mali_instrumented_context *ctx);

/**
 * Mark the beginning of PP counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 * @param core Which PP core this relates to.
 */
MALI_IMPORT void _instrumented_register_counter_pp_begin(mali_instrumented_context *ctx, u32 core);

/**
 * Mark the end of PP counters exposed to the instrumented plug-in.
 * @param The main instrumented context.
 * @param core Which PP core this relates to.
 */
MALI_IMPORT void _instrumented_register_counter_pp_end(mali_instrumented_context *ctx, u32 core);

#endif /* _MALI_COUNTERS_H_ */


