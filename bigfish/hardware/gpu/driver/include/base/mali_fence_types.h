/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_fence_types.h
 * Timeline and fence types.
 */

#ifndef _MALI_FENCE_TYPES_H_
#define _MALI_FENCE_TYPES_H_

#include <base/mali_types.h>
#include "mali_utgard_uk_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* _cplusplus */

/**
 * Handle for a Mali fence.
 */
typedef void *mali_fence_handle;

/**
 * Type representing a point on a timeline.
 */
typedef u32 mali_timeline_point;

/**
 * This enum is used to specify a timeline.  GP, PP and soft jobs have separate timelines.
 */
typedef enum mali_timeline
{
	MALI_TIMELINE_GP   = MALI_UK_TIMELINE_GP,
	MALI_TIMELINE_PP   = MALI_UK_TIMELINE_PP,
	MALI_TIMELINE_SOFT = MALI_UK_TIMELINE_SOFT,
	MALI_TIMELINE_MAX  = MALI_UK_TIMELINE_MAX
} mali_timeline;

/**
 * Constant used to represent no point on a timeline.
 */
#define MALI_TIMELINE_NO_POINT ((mali_timeline_point) 0)

/**
 * If used as the timeout argument in @ref mali_fence_wait, the function will never time out.
 */
#define MALI_FENCE_WAIT_TIMEOUT_NEVER ((u32) -1)

/**
 * If used as the timeout argument in @ref mali_fence_wait, the function will return
 * immediately with the current state of the fence.
 */
#define MALI_FENCE_WAIT_TIMEOUT_IMMEDIATELY 0

/**
 * The Mali fence structure.
 */
typedef struct mali_fence
{
	mali_timeline_point points[MALI_TIMELINE_MAX];
	int sync_fd;
} mali_fence;

/* The following functions are used internally by the base layer. */

/**
 * Initialize a fence.  The fence will initially be in a signaled state.
 *
 * @param fence Fence we want to initialize.
 */
void _mali_fence_init(struct mali_fence *fence);

/**
 * Initialize a fence to the same state as another fence.
 *
 * @param dst_fence Fence we want to initialize.
 * @param src_fence Fence used to initialize fence.
 */
void _mali_fence_init_from(struct mali_fence *dst_fence, struct mali_fence *src_fence);

/**
 * Terminate a fence.
 *
 * @param fence Fence we want to terminate.
 */
void _mali_fence_term(struct mali_fence *fence);

/**
 * Merge a timeline point into fence.
 *
 * @param fence_handle Handle to fence point will be merged into.
 * @param timeline Timeline points belongs on.
 * @param point The point that will be merged into the fence.
 */
void _mali_fence_merge_point(mali_fence_handle fence, enum mali_timeline timeline, mali_timeline_point point);

#ifdef __cplusplus
}
#endif /* _cplusplus */
#endif /* _MALI_FENCE_TYPES_H_ */
