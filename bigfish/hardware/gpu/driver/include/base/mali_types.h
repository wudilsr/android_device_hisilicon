/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_types.h
 * Defines standard integral and boolean types used throughout the driver
 */

#ifndef _MALI_TYPES_H_
#define _MALI_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifdef MALI_ARCH_HAS_DATATYPES
#include <mali_arch_datatypes.h>
#else
/* define INLINE, STATIC_INLINE and STATIC_FORCE_INLINE */
#ifndef _MSC_VER
#define MALI_STATIC_INLINE static __inline__
#define MALI_INLINE __inline__
#define INLINE_AVAILABLE 1

#ifdef NDEBUG
#if defined(__ARMCC_VERSION)
#define MALI_STATIC_FORCE_INLINE static __forceinline
#elif defined(__GNUC__)
#define MALI_STATIC_FORCE_INLINE static __inline__ __attribute__ ((always_inline))
#else
#define MALI_STATIC_FORCE_INLINE MALI_STATIC_INLINE
#endif
#else /* not NDEBUG */
#define MALI_STATIC_FORCE_INLINE MALI_STATIC_INLINE
#endif /* NDEBUG */

#else /* _MSC_VER */
#define MALI_STATIC_INLINE static __inline
#define MALI_INLINE __inline
#define INLINE_AVAILABLE 1
#define MALI_STATIC_FORCE_INLINE static __forceinline
#endif /* _MSC_VER */

#define VALUE_IN_REGS

/* define RESTRICT and PURE */
#ifdef _MSC_VER
#define MALI_RESTRICT __restrict
#define MALI_PURE __declspec(noalias)
#elif defined(__GNUC__)
#define MALI_RESTRICT __restrict
#define MALI_PURE __attribute__((pure))
#else
#define MALI_RESTRICT
#define MALI_PURE
#endif

typedef unsigned long   mali_bool;
typedef unsigned char   u8;
typedef signed char     s8;
typedef unsigned short  u16;
typedef signed short    s16;
typedef unsigned int    u32;
typedef signed int  s32;
#ifdef _MSC_VER
typedef unsigned __int64    u64;
typedef signed   __int64    s64;
#else
typedef unsigned long long  u64;
typedef signed long long    s64;
#endif

typedef u32 PidType;

#endif

/**
 * @defgroup MaxValues Maximum values the basic integer types
 * @{
 */
#define MALI_U8_MAX     0xFFu
#define MALI_S8_MAX     0x7F

#define MALI_U16_MAX    0xFFFFu
#define MALI_S16_MAX    0x7FFF

#define MALI_U32_MAX    0xFFFFFFFFu
#define MALI_S32_MAX    0x7FFFFFFF

#define MALI_U64_MAX    0xFFFFFFFFFFFFFFFFuLL
#define MALI_S64_MAX    0x7FFFFFFFFFFFFFFFLL
/** @}*/

#define MALI_NAN_POS 0x7fc00000
#define MALI_NAN_NEG 0xffc00000

#ifdef MALI_TEST_API
#define MALI_STATIC
#define MALI_EXTERN     extern
#define MALI_CONST      const
#define MALI_VOID       void
#else
/* NOTE: Could set this to MALI_ARCH_STATIC to make it possible to define this in the arch-layer*/
#define MALI_STATIC          static

#define MALI_EXTERN     extern
#define MALI_CONST      const
#define MALI_VOID       void
#endif

typedef enum mali_err_code
{
	MALI_ERR_NO_ERROR           =  0,
	MALI_ERR_OUT_OF_MEMORY      = -1,
	MALI_ERR_FUNCTION_FAILED    = -2,
	MALI_ERR_EARLY_OUT          = -3,
#if MALI_TEST_API
	MALI_ERR_CHECK_ERROR        = -4,
#endif
	MALI_ERR_TIMEOUT            = -5
} mali_err_code;

/**
 * Type definition for frame_id. All gp-jobs from the same frame builder
 * should have the same frame_id. If two succeeding jobs have the same
 * frame_id, the plbu does not need to flush the pointer cache between
 * these jobs, and the vs or plbu cmd processor can skip some cmds
 * in the start.
 */
typedef u32 mali_base_frame_id;

/**
 * Type definitions needed for Frame Builder identification.
 */
typedef u32 mali_base_frame_builder_id;
typedef u32 mali_base_flush_id;
typedef struct mali_base_render_id
{
	u32 mali_base_frame_builder_id;
	u32 mali_base_flush_id;
} mali_base_render_id;


/**
 * Invalid frame ID constant. Used to signal a bad frame_id.
 */
enum { MALI_BAD_FRAME_ID = 0 };
enum { MALI_BAD_FRAME_BUILDER_ID = 0 };

/**
 * Definition of the job priority type.
 * Jobs with a higher priority will be executed before jobs with lower,
 * even if the low ones are added first.
 */
typedef enum mali_job_priority
{
	MALI_JOB_PRI_HIGH,
	MALI_JOB_PRI_NORMAL,
	MALI_JOB_PRI_LOW,
	MALI_JOB_PRI_COUNT
} mali_job_priority;

/**
 * Job completion status codes
 */
typedef enum mali_job_completion_status
{
	/* MALI_JOB_STATUS_FINISHED */
	MALI_JOB_STATUS_END_SUCCESS         = 1 << (16 + 0),
	MALI_JOB_STATUS_END_OOM             = 1 << (16 + 1),
	MALI_JOB_STATUS_END_ABORT           = 1 << (16 + 2),
	MALI_JOB_STATUS_END_TIMEOUT_SW      = 1 << (16 + 3),
	MALI_JOB_STATUS_END_HANG            = 1 << (16 + 4),
	MALI_JOB_STATUS_END_SEG_FAULT       = 1 << (16 + 5),
	MALI_JOB_STATUS_END_ILLEGAL_JOB     = 1 << (16 + 6),
	MALI_JOB_STATUS_END_UNKNOWN_ERR     = 1 << (16 + 7),
	MALI_JOB_STATUS_END_SHUTDOWN        = 1 << (16 + 8),
	MALI_JOB_STATUS_END_SYSTEM_UNUSABLE = 1 << (16 + 9)
} mali_job_completion_status;

/**
 *  Minimum values for these types
 */
#define MALI_U8_MIN     0x0
#define MALI_S8_MIN     ((-MALI_S8_MAX)-1)

#define MALI_U16_MIN    0x0
#define MALI_S16_MIN    ((-MALI_S16_MAX)-1)

#define MALI_U32_MIN    0x0
#define MALI_S32_MIN    ((-MALI_S32_MAX)-1)

#define MALI_U64_MIN    0x0
#define MALI_S64_MIN    ((-MALI_S64_MAX)-1L)


/**
 *  Other common values
 */
#define MALI_PI 3.14159265358979323


/**
 * Type definition for a base wait handle.
 * Used to wait on objects supporting wait logic
 */
typedef struct mali_base_wait_type *mali_base_wait_handle;

/**
 * Type definition for a reentrant mutex handle.
 * Used by _mali_sys_mutex_reentrant_* functions.
 */
typedef struct mali_mutex_reentrant_type *mali_mutex_reentrant_handle;

/**
 * Type definition for a lock handle.
 * Must be used instead of mutexes if the lock is to be released by a different thread than the one which did the locking.
 * Nested locking is not supported.
 */
typedef struct mali_lock_type *mali_lock_handle;


/** @brief Public type of atomic counters
 *
 * This is public for allocation on stack. On systems that support it, this is just a single 32-bit value.
 * On others, it could be encapsulating an object stored elsewhere.
 *
 * Even though the structure has space for a u32, the counters will only
 * represent signed 24-bit integers.
 *
 * Regardless of implementation, the _mali_base_sys_atomic_ functions \b must be used
 * for all accesses to the variable's value, even if atomicity is not requried.
 * Do not access u.val or u.obj directly.
 */
typedef struct mali_atomic_int
{
	volatile union
	{
		u32 val;
		void *obj;
	} u;
} mali_atomic_int;

/** @brief User space definition of VSYNC events
 *
 * @note This must be kept in sync with _mali_uk_vsync_event
 */
typedef enum mali_vsync_event
{
	MALI_VSYNC_EVENT_BEGIN_WAIT,
	MALI_VSYNC_EVENT_END_WAIT
} mali_vsync_event;


#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef MALI_TRUE
#define MALI_TRUE ((mali_bool)1)
#endif

#ifndef MALI_FALSE
#define MALI_FALSE ((mali_bool)0)
#endif

/** NOTE: THESE EVALUTE BOTH ARGUMENTS EXACTLY TWICE */
#ifndef MAX
#define MAX(x,y) (((x)>(y))?(x):(y))
#endif

#ifndef MIN
#define MIN(x,y) (((x)<(y))?(x):(y))
#endif

#ifndef MALI_NO_HANDLE
#define MALI_NO_HANDLE NULL
#endif

#ifdef __cplusplus
}
#endif
#endif /* _MALI_TYPES_H_ */
