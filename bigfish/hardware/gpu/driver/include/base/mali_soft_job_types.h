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
 * @file mali_soft_job_types.h
 *
 * Types related to soft jobs.  See @file mali_soft_job.h for more information.
 */

#ifndef _MALI_SOFT_JOB_TYPES_H_
#define _MALI_SOFT_JOB_TYPES_H_

#include <base/mali_types.h>
#include <base/mali_fence.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Type representing a handle to a soft job.
 */
typedef void *mali_soft_job_handle;

/**
 * Soft job types.
 *
 * Soft jobs of type MALI_SOFT_JOB_TYPE_USER_SIGNALED will only complete after activation if either
 * they are signaled by user-space (@ref mali_soft_job_system_signaled_job) or if they are timed out
 * by the Timeline system.
 * Soft jobs of type MALI_SOFT_JOB_TYPE_SELF_SIGNALED will release job resource automatically in kernel
 * when the job is actived.
 */
typedef enum
{
	MALI_SOFT_JOB_TYPE_SELF_SIGNALED,
	MALI_SOFT_JOB_TYPE_USER_SIGNALED,
} mali_soft_job_type;

/**
 * Type representing a soft job ID.
 */
typedef u32 mali_soft_job_id;
#define MALI_SOFT_JOB_INVALID_ID ((u32) -1)

/**
 * Activated callback function pointer type.
 */
typedef void (*mali_soft_job_activated_callback_func)(mali_soft_job_handle, void *);

/**
 * Soft job struct.
 */
typedef struct mali_soft_job
{
	mali_soft_job_type type; /**< Type of this soft job */
	mali_soft_job_id job_id; /**< Job ID given by device driver */

	struct mali_fence fence; /**< Fence representing what this job has to wait on before starting */

	mali_soft_job_activated_callback_func activated_callback;
	void *activated_callback_param;
} mali_soft_job;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MALI_SOFT_JOB_TYPES_H_ */
