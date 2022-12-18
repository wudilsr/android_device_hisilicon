/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2014-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_gbm.h
 * @brief A window type for the gbm platform (used by egl and tests)
 */

#ifndef _MALI_GBM_H_
#define _MALI_GBM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GBM_MAX_NUM_BO
#define GBM_MAX_NUM_BO 3
#endif

typedef struct gbm_device
{
	struct gbm_device *(*is_gbm_device)(int);
	int32_t fd;
	int32_t refcnt;
	void *mutex;
} gbm_device;

typedef struct gbm_bo
{
	struct gbm_device *device;
	uint32_t width;
	uint32_t height;
	uint32_t bpp;
	uint32_t pitch;
	uint32_t format;
	uint32_t flags;
	uint32_t status;
	uintptr_t handle;
	int32_t fd;
	uint32_t name;
	int32_t refcnt;
	void *mutex;
	void *lock;
	void *user_data;
	void (*destroy_user_data)(struct gbm_bo *, void *);
} gbm_bo;

typedef struct gbm_surface
{
	struct gbm_device *device;
	uint32_t width;
	uint32_t height;
	uint32_t gbm_format;
	uint32_t gbm_flags;
	struct gbm_bo *bo[GBM_MAX_NUM_BO];
	uint32_t current;
	int32_t refcnt;
	void *mutex;
} gbm_surface;

#ifdef __cplusplus
}
#endif

#endif

