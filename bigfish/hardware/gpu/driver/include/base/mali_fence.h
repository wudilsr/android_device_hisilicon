/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_fence.h
 * The Mali fence.
 *
 * Mali fences represent some condition we might want to wait on (e.g. pp job done or a Linux sync
 * fence being signaled).  When the condition is fulfilled the fence will be signaled which means
 * anything waiting on the fence will be able to continue.
 */

#ifndef _MALI_FENCE_H_
#define _MALI_FENCE_H_

#include <base/mali_fence_types.h>
#include <base/arch/mali_arch_fence.h>

#ifdef __cplusplus
extern "C" {
#endif /* _cplusplus */

/**
 * Create a new fence.  The fence will initially be in a signaled state.
 *
 * @return Handle to new fence if successful, else MALI_NO_HANDLE.
 */
mali_fence_handle _mali_fence_create(void);

/**
 * Destroy a fence.
 *
 * @param fence_handle Handle to fence we want to destroy.
 */
void _mali_fence_destroy(mali_fence_handle fence_handle);

/**
 * Reset a fence back to a signaled state.  Any resources held by the fence (e.g. Linux sync fence)
 * will be properly released.
 *
 * @param fence_handle Handle to fence we want to reset.
 */
void _mali_fence_reset(mali_fence_handle fence_handle);

/**
 * Merge two fences, storing the result in the first fence.
 *
 * If anything fails while merging the fences a blocking wait might be performed on parts of the
 * second fence in order to guarantee that the result of the merger can be safely used.
 *
 * @param fence_handle Handle to first fence.
 * @param other_fence_handle Handle to second fence that will be merged into first fence.
 */
void _mali_fence_merge(mali_fence_handle fence_handle, mali_fence_handle other_fence_handle);

/**
 * Wait on a fence until it is signaled or timeout is reached.
 *
 * @param fence_handle Handle for fence to wait on.
 * @param timeout Timeout in ms.  If MALI_FENCE_WAIT_TIMEOUT_IMMEDIATELY return immediately.  If
 * MALI_FENCE_WAIT_TIMEOUT_NEVER wait forever.
 * @return MALI_TRUE if fence was signaled or MALI_FALSE if timeout was reached.
 */
MALI_STATIC_FORCE_INLINE mali_bool _mali_fence_wait(mali_fence_handle fence_handle, u32 timeout)
{
	return _mali_arch_fence_wait(fence_handle, timeout);
}

/**
 * Check if a fence is signaled.
 *
 * @param fence_handle Handle for fence to check.
 * @return MALI_TRUE if fence is signaled or MALI_FALSE if not.
 */
MALI_STATIC_FORCE_INLINE mali_bool _mali_fence_signaled(mali_fence_handle fence_handle)
{
	return _mali_arch_fence_wait(fence_handle, 0);
}

#if MALI_LINUX_SYNC

/**
 * Merge Linux sync fence into Mali fence.  The Mali fence takes ownership of the sync fence and
 * will release it when no longer needed.
 *
 * If the merge fails a blocking wait is performed on the sync fence fd in order to guarantee that
 * the result of the merger can be safely used.
 *
 * @param fence_handle Handle to Mali fence.
 * @param fd File descriptor for Linux sync fence that will be merged into Mali fence.
 */
void _mali_fence_merge_sync_fence(mali_fence_handle fence_handle, int fd);

/**
 * Create a Linux sync fence representing a Mali fence.  The caller gets ownership of the sync fence
 * and must release it.
 *
 * @param fence_handle Handle to Mali fence.
 * @return File descriptor for new Linux sync fence.
 */
MALI_STATIC_FORCE_INLINE int _mali_fence_create_sync_fence(mali_fence_handle fence_handle)
{
	return _mali_arch_fence_create_sync_fence(fence_handle);
}

#endif /* MALI_LINUX_SYNC */

#ifdef __cplusplus
}
#endif /* _cplusplus */

#endif /* _MALI_FENCE_H_ */
