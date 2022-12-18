/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2011, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


#ifndef _MALI_VSYNC_H
#define _MALI_VSYNC_H

#include <mali_system.h>
#include <base/arch/base_arch_vsync.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Add/register a VSYNC event.
 *
 * @param event type to register.
 */
MALI_STATIC_INLINE void _mali_base_vsync_event_report(mali_vsync_event event)
{
#if MALI_VSYNC_EVENT_REPORT_ENABLE
	_mali_base_arch_vsync_event_report(event);
#else
	MALI_IGNORE(event);
#endif
}


#ifdef __cplusplus
}
#endif

#endif /*_MALI_VSYNC_H */
