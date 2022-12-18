/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _VG_INSTRUMENTED_H_
#define _VG_INSTRUMENTED_H_

/* This header contains all the includes needed by the VG driver to do instrumentation,
 * so we don't have to include them all in every VG file.
 */

#include "mali_system.h"
#include "mali_instrumented_context.h"
#include "mali_log.h"
#include "mali_counters.h"
#include "mali_vg_instrumented_types.h"

/**
 * Initialize VG instrumentation.
 *
 * This function registers VG software counters and does other VG-related initialization
 * on the current instrumentation context.
 *
 * @param ctx The instrumented context that's linked to the VG context.
 */
MALI_IMPORT
mali_err_code MALI_CHECK_RESULT _vg_instrumentation_init(mali_instrumented_context *ctx);

/**
 * Update total bytes heap memory allocated by VG driver.
 */
MALI_IMPORT
void _vg_update_total_allocated(u32 allocated_memory);

#endif /* _VG_INSTRUMENTED_H_ */

