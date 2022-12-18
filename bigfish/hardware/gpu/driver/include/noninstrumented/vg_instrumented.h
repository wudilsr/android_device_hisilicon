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
#include "sw_profiling.h"

MALI_STATIC_INLINE mali_err_code MALI_CHECK_RESULT _vg_instrumentation_init(mali_instrumented_context *ctx)
{
	MALI_IGNORE(ctx);
	MALI_SUCCESS;
}

MALI_STATIC_INLINE void _vg_update_total_allocated(u32 allocated_memory)
{
	MALI_IGNORE(allocated_memory);
}

#endif /* _VG_INSTRUMENTED_H_ */

