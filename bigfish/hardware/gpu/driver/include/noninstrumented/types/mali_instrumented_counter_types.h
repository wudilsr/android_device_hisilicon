/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2011, 2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_INSTRUMENTED_COUNTER_TYPES_H_
#define _MALI_INSTRUMENTED_COUNTER_TYPES_H_

#include "mali_system.h"

#define MALI_COUNTER_HARDWARE_BIT    1 << 30

#define MALI_GLES_COUNTER_OFFSET    1000
#define MALI_VG_COUNTER_OFFSET      2000
#define MALI_EGL_COUNTER_OFFSET     3000
#define MALI_SHARED_COUNTER_OFFSET  4000
#define MALI_MEMORY_COUNTER_OFFSET  5000

#define MALI_M200_COUNTER_OFFSET    (    0 | MALI_COUNTER_HARDWARE_BIT)
#define MALI_MGP2_COUNTER_OFFSET    (10000 | MALI_COUNTER_HARDWARE_BIT)
#define MALI_55_COUNTER_OFFSET      (20000 | MALI_COUNTER_HARDWARE_BIT)
#define MALI_L2_COUNTER_OFFSET      (30000 | MALI_COUNTER_HARDWARE_BIT)
#define MALI_L2_COUNTER_OFFSET_END  (39999 | MALI_COUNTER_HARDWARE_BIT)

#if defined(USING_MALI200) && (MALI200_HWVER == 0x0001)
#define MALI_CORE_FREQ_KHZ 300000
#define MALI_CORE_FREQ_MHZ_STR "300.0"
#else
#define MALI_CORE_FREQ_KHZ 10000
#define MALI_CORE_FREQ_MHZ_STR "10.0"
#endif /* Mali200 r0p1 */

#define MALI_COUNTER_INFINITE 0x7fffffffffffffffLL

#include "mali200_counters.h"
#include "maligp2_counters.h"
#if !defined(USING_MALI200)
#include "malil2_counters.h"
#endif

typedef enum mali_frequency_scale
{
	MALI_SCALE_NONE,
	MALI_SCALE_NORMAL,
	MALI_SCALE_INVERSE
} mali_frequency_scale;

/**
 * Contains meta data for a counter.
 */
typedef struct mali_counter_info
{
	u32 id;                             /**< Unique identificator for counter */
	char *name;                         /**< Counter name (should be short). */
	char *description;                  /**< Counter description (as detailed as
                                                 possible). */
	char *unit;                         /**< Counter unit (For example f/s) */
	mali_frequency_scale scale_to_hz;   /**< MALI_SCALE_NORMAL if this counter should
                                               be scaled up to compensate for lower FPGA
                                               clock speeds. MALI_SCALE_INVERSE if it should be
                                               scaled inversely */
} mali_counter_info;

/**
 *  A header for a number of counters.
 *
 * Describes a tree of headers, where one header either has an array of counter indices
 * (leaves), or an array of headers (branches).
 *
 * An example, each "·" is a header_block:
 *
 * · Root
 *   · GLES stats
 *     · Entrypoint stats
 *       * 0
 *       * 1typedef struct mali_
 *     · API state
 *       * 5
 *       * 6
 *   · GP2 counters
 *     · Vertex Shader counters
 *       * 2
 *       * 3
 *       * 4
 *     · PLBU counters
 *       * 7
 *       * 8
 */
struct mali_counter_group; /* Forward declaration */
typedef struct mali_counter_group
{
	char *name;
	char *description;
	mali_bool leaf;
	u32 frequency;
	u32 num_children;
	union
	{
		u32 *counter_indices;
		struct mali_counter_group **groups;
	} children;
	struct mali_counter_group *parent;
} mali_counter_group;



typedef enum mali_activate_type
{
	MALI_ACTIVATE_NOT = 0,
	MALI_ACTIVATE_DERIVED,
	MALI_ACTIVATE_EXPLICIT
} mali_activate_type;


/**
 * Defines a performance counter.
 */
typedef struct mali_counter
{
	mali_activate_type activated;
	mali_counter_info *info;
} mali_counter;

#endif /* _MALI_INSTRUMENTED_COUNTER_TYPES_H_ */
