/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2008-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _SW_PROFILING_TYPES_H_
#define _SW_PROFILING_TYPES_H_

#include "mali_system.h"

typedef enum profiling_event_type
{
	PROFILING_EVENT_ENTER = 0,
	PROFILING_EVENT_LEAVE,
	PROFILING_EVENT_COUNT,
	PROFILING_EVENT_NONE
} profiling_event_type;

typedef struct profiling_event
{
	unsigned int type : 2;
	unsigned int counter_id : 30;
	u32 value;
} profiling_event;

typedef struct profiling_buffer
{
	profiling_event *buffer;
	profiling_event *current;
	u32 size;
} profiling_buffer;

#endif /* _SW_PROFILING_TYPES_H_ */

