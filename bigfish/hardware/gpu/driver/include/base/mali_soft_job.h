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
 * @file mali_soft_job.h
 *
 * Soft jobs are used to represent kernel space CPU work.
 *
 * Soft jobs, like GP and PP jobs, are handled by the Timeline system.  Thus it is possible to add
 * fences on soft jobs to represent dependencies that have to be resolved before they can start, and
 * to get a fence that is signaled when a soft job is completed.
 *
 * Currently the only type of soft job supported is the USER_SIGNALED soft job, which does no work
 * in kernel space, but instead sends a notification message to user space on activation and is then
 * signaled as completed by user space.  This can be used to set up dependencies that prevent a job
 * from starting before user space deems it appropriate.  This is currently used to implement vsync
 * for fbdev, and for the EGL_ANDROID_recordable extension.
 *
 * @note If a USER_SIGNALED soft job is not signaled by user space within reasonable time, it will
 * automatically be signaled as completed by kernel space.
 */

#ifndef _MALI_SOFT_JOB_H_
#define _MALI_SOFT_JOB_H_

#include <base/mali_soft_job_types.h>
#include <base/arch/mali_arch_soft_job.h>
#include <base/mali_debug.h>

#ifdef __cplusplus
extern "C" {
#endif /* _cplusplus */

/**
 * Create a new soft job.
 *
 * @param type Type of soft job.
 * @return Handle to new soft job, or MALI_NO_HANDLE if creation failed.
 */
mali_soft_job_handle _mali_soft_job_new(mali_soft_job_type type);

/**
 * Free soft job.
 *
 * @param soft_job Handle to soft job to free.
 */
void _mali_soft_job_free(mali_soft_job_handle soft_job);

/**
 * Add a fence to this job.
 *
 * The fence will be merged (@ref _mali_fence_merge) with any fences previously added to the job.
 *
 * @param soft_job handle to soft job.
 * @param fence_handle Handle to fence that will be added to job.
 */
void _mali_soft_job_add_fence(mali_soft_job_handle soft_job, mali_fence_handle fence_handle);

/**
 * Start a soft job.  If this function returns MALI_TRUE any callbacks registered for the soft job
 * type will be called.  If MALI_FALSE, no callbacks will be called.
 *
 * @note Callbacks might be called before this function returns.  The function will return MALI_TRUE
 * in this case.
 *
 * @param soft_job Handle to soft job to start.
 * @param fence If not MALI_NO_HANDLE, the fence created for this job will be merged into this fence.
 * @return MALI_TRUE if started successfully, MALI_FALSE if not.
 */
MALI_STATIC_FORCE_INLINE mali_bool _mali_soft_job_start(mali_soft_job_handle soft_job, mali_fence_handle fence)
{
	struct mali_soft_job *job = (struct mali_soft_job *)soft_job;
	MALI_DEBUG_ASSERT_POINTER(job);
	return _mali_arch_soft_job_start(job, fence);
}

/**
 * Signal a soft job.
 *
 * @note This call will block until the soft job is activated.
 * @note The soft job must have type MALI_SOFT_JOB_TYPE_USER_SIGNALED.
 * @note The soft job must have been started.
 *
 * @return MALI_ERR_NO_ERROR if the job completed due to the signal, MALI_ERR_TIMEOUT if the job was
 * timed out or MALI_ERR_FUNCTION_FAILED if an error occured.
 */
MALI_STATIC_FORCE_INLINE mali_err_code _mali_soft_job_signal(mali_soft_job_handle soft_job)
{
	struct mali_soft_job *job = (struct mali_soft_job *)soft_job;
	MALI_DEBUG_ASSERT_POINTER(job);
	return _mali_arch_soft_job_signal(job);
}

/**
 * Set activated callback for soft job.
 *
 * @note The soft job have type MALI_SOFT_JOB_TYPE_USER_SIGNALED and MALI_SOFT_JOB_TYPE_SELF_SIGNALED.
 * @note The soft job must not have been started for this call to have any effect.
 *
 * @param soft_job Handle to soft job to set callback for.
 * @param callback The callback function to set.
 * @param param Optional data that will be sent to callback function.
 */
void _mali_soft_job_set_activated_callback(mali_soft_job_handle soft_job, mali_soft_job_activated_callback_func callback, void *param);

#ifdef __cplusplus
}
#endif /* _cplusplus */

#endif /* _MALI_SOFT_JOB_H_ */
