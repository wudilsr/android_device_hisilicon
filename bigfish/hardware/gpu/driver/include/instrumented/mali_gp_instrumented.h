/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2012-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_GP_INSTRUMENTED_H_
#define _MALI_GP_INSTRUMENTED_H_

#include "mali_instrumented_context_types.h"
#include <base/gp/mali_gp_job_types.h>

/**
 * Register GP performance counters.
 *
 * This function registers GP performance counters in the mali_counters system. It
 * is run by _mali_instrumented_create_context()
 *
 * @param ctx      the instrumented context.
 */
MALI_IMPORT
mali_err_code MALI_CHECK_RESULT _mali_gp_instrumented_init(mali_instrumented_context *ctx);

/**
 * Calculate derived counters for the GP.
 *
 * Derived counters are for instance bandwith,
 * which is not directly calculated by the hardware performance counters, but can be
 * calculated from them.
 *
 * @param ctx      the instrumented context.
 */
MALI_IMPORT
mali_err_code _mali_gp_derive_counts(mali_instrumented_context *ctx, mali_instrumented_frame *frame);


/** Activate all hw counters needed for computing the derived counters concerning the gp.
 */
MALI_IMPORT
void _mali_gp_activate_derived(mali_instrumented_context *ctx);


/**
 * Prepare the instrumented gp job
 *
 * @param frame              instrumented frame that we write values to
 * @param job_handle         handle to the pixel processor job that we prepare
 */
MALI_IMPORT
void _instrumented_gp_setup(mali_instrumented_context *context, mali_gp_job_handle job_handle);


/**
 * Collect performance values from the geometry processor
 *
 * @param frame              instrumented frame that we write values to
 * @param job_handle         handle to the geometry processor job that we read values from
 */
MALI_IMPORT
void _instrumented_gp_done(mali_instrumented_frame *frame, mali_gp_job_handle job_handle);

/**
 * Abort instrumentation of specified job (cleanup allocated memory)
 *
 * @param job_handle         handle to the geometry processor job that we should abandon instrumentation for.
 */
MALI_IMPORT
void _instrumented_gp_abort(mali_gp_job_handle job_handle);

#endif /* _MALI_GP_INSTRUMENTED_H_ */
