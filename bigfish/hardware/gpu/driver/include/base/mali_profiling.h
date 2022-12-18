/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2010-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


#ifndef _MALI_PROFILING_H
#define _MALI_PROFILING_H

#include <mali_utgard_profiling_events.h>
#include <mali_arch_profiling.h>

#if MALI_TIMELINE_PROFILING_ENABLED || MALI_SW_COUNTERS_ENABLED

#include <mali_system.h>
#include <cinstr/mali_cinstr_common.h>

#endif /* MALI_TIMELINE_PROFILING_ENABLED */

#ifdef __cplusplus
extern "C" {
#endif

#if MALI_TIMELINE_PROFILING_ENABLED

/**
 * Add/register an profiling event.
 * @param event_id ID of event to register.
 * @param data0 Custom data associated with event
 * @param data1 Custom data associated with event
 * @param data2 Custom data associated with event
 * @param data3 Custom data associated with event
 * @param data4 Custom data associated with event
 */
MALI_NOTRACE MALI_STATIC_INLINE void _mali_base_profiling_add_event(u32 event_id, u32 data0, u32 data1, u32 data2, u32 data3, u32 data4);
MALI_STATIC_INLINE void _mali_base_profiling_add_event(u32 event_id, u32 data0, u32 data1, u32 data2, u32 data3, u32 data4)
{
	/* Don't generate any events if profiling isn't turned on for this application */
	if (_mali_arch_profiling_get_enable_state())
	{
		cinstr_profiling_entry_t evt;
		evt.event_id = event_id;
		evt.data[0] = data0;
		evt.data[1] = data1;
		evt.data[2] = data2;
		evt.data[3] = data3;
		evt.data[4] = data4;

		_mali_arch_profiling_add_event(&evt);
	}
}

/**
 * Check if current user space process should generate events or not.
 * @return MALI_TRUE if profiling events should be turned on, otherwise MALI_FALSE
 */
MALI_STATIC_INLINE mali_bool _mali_base_profiling_get_enable_state(void)
{
	return _mali_arch_profiling_get_enable_state();
}

MALI_STATIC_INLINE u32 _mali_base_profiling_memory_usage_get(void)
{
	return _mali_arch_profiling_memory_usage_get();
}

#endif /* MALI_TIMELINE_PROFILING_ENABLED */

#if MALI_HEATMAPS_ENABLED
MALI_NOTRACE MALI_STATIC_INLINE void _mali_base_profiling_add_heatmap(u32 data0, u32 data1, u32 data2, u32 data3, u32 data4);
MALI_STATIC_INLINE void _mali_base_profiling_add_heatmap(u32 identifier, u32 flush_id, \
        u32 master_tile_width, \
        u32 master_tile_height, u32 heatmap_start)
{
	/* Don't generate any events if profiling isn't turned on for this application */
	if (MALI_INSTRUMENTED_FEATURE_IS_ENABLED(CINSTR_CLIENTAPI_COMMON, CINSTR_FEATURE_TIMELINE_PROFILING))
	{
		cinstr_profiling_entry_t evt;
		/* This event denotes HEATMAP data. We dont want to add another ioctl
		and we can hijack the same kernel call*/
		evt.event_id = 999;

		evt.data[0] = identifier;
		evt.data[1] = flush_id;
		evt.data[2] = master_tile_width;
		evt.data[3] = master_tile_height;
		evt.data[4] = heatmap_start;

		_mali_arch_profiling_add_event(&evt);
	}
}
#endif /* MALI_HEATMAPS_ENABLED */

#if MALI_SW_COUNTERS_ENABLED
/**
 * Send a set of software counters out from the driver.
 * @param counters The list of counter values to report.
 * @param num_counters Number of elements in counters array.
 */
MALI_STATIC_INLINE void _mali_base_profiling_report_sw_counters(u32 *counters, u32 num_counters)
{
	_mali_arch_profiling_report_sw_counters(counters, num_counters);
}

#endif /* MALI_SW_COUNTERS_ENABLED */


#if MALI_FRAMEBUFFER_DUMP_ENABLED
/**
 * Setup a static annotation channel to be used by _mali_base_profiling_annotate_write.
 *
 * @return MALI_TRUE if the channel was available and opened successfully, MALI_FALSE otherwise.
 */
MALI_STATIC_INLINE mali_bool _mali_base_profiling_annotate_setup(void)
{
	return _mali_arch_profiling_annotate_setup();
}

/**
 * Write data to the annotation channel opened by _mali_base_profiling_annotate_setup.
 * If the channel has not been opened this function does nothing.
 *
 * @param data Pointer to the data to be written.
 * @param length Number of bytes to be written.
 */
MALI_STATIC_INLINE void _mali_base_profiling_annotate_write(const void *data, u32 length)
{
	_mali_arch_profiling_annotate_write(data, length);
}

/**
 * Flush data to the annotation channel opened by _mali_base_profiling_annotate_setup.
 * If the channel has not been opened this function does nothing.
 */
MALI_STATIC_INLINE void _mali_base_profiling_annotate_flush(void)
{
	_mali_arch_profiling_annotate_flush();
}

/**
 * Lock annotation channel, protect the annotation channel in multi thread.
 */
MALI_STATIC_INLINE void _mali_base_profiling_annotate_lock(void)
{
	_mali_arch_profiling_annotate_lock();
}


/**
 * UnLock annotation channel, protect the annotation channel in multi thread.
 */
MALI_STATIC_INLINE void _mali_base_profiling_annotate_unlock(void)
{
	_mali_arch_profiling_annotate_unlock();
}

#endif


#ifdef __cplusplus
}
#endif


#if MALI_TIMELINE_PROFILING_FUNC_ENABLED

#include "mali_profiling_func_id.h"

#define MALI_PROFILING_ENTER_FUNC(name) _mali_base_profiling_add_event(MALI_PROFILING_EVENT_TYPE_SINGLE|MALI_PROFILING_EVENT_CHANNEL_SOFTWARE|MALI_PROFILING_EVENT_REASON_SINGLE_SW_ENTER_API_FUNC, 0, 0, TIMELINE_PROFILING_FUNC_ID_##name, 0, 0)
#define MALI_PROFILING_LEAVE_FUNC(name) _mali_base_profiling_add_event(MALI_PROFILING_EVENT_TYPE_SINGLE|MALI_PROFILING_EVENT_CHANNEL_SOFTWARE|MALI_PROFILING_EVENT_REASON_SINGLE_SW_LEAVE_API_FUNC, 0, 0, TIMELINE_PROFILING_FUNC_ID_##name, 0, 0)

#else /* MALI_TIMELINE_PROFILING_FUNC_ENABLED */

#define MALI_PROFILING_ENTER_FUNC(name)
#define MALI_PROFILING_LEAVE_FUNC(name)

#endif /* MALI_TIMELINE_PROFILING_FUNC_ENABLED */

#ifdef MALI_MEMORY_PROFILING
/* Environment variable name,to enable memory profiling. */
#define MALI_MEM_PROFILING_TO_FILE      "MALI_MEM_PROFILING_TO_FILE"

/**
 * @brief Check mali profiling if enable
 */
MALI_STATIC_INLINE mali_bool _mali_mem_profiling_to_file_enabled()
{
	return _mali_sys_config_string_get_bool(MALI_MEM_PROFILING_TO_FILE, MALI_FALSE);
}

/**
 * @brief Starts a function trace
 * @param str The function name you want to trace.
 */
MALI_STATIC_INLINE void _mali_mem_profiling_to_file_begin(const char *str)
{
	if (_mali_mem_profiling_to_file_enabled())
	{
		char buf[256];
		_mali_sys_snprintf(buf, 256, "%d    %s  begin:\n", (u32)_mali_sys_get_time_usec(), str);
		_mali_arch_mem_profiling_fwrite(buf);
	}
	else
	{
		_mali_arch_mem_profiling_fclose();
	}
}

/**
 * @brief Ends a function trace
 * @param str The function name you want to trace.
 */
MALI_STATIC_INLINE void _mali_mem_profiling_to_file_end(const char *str)
{
	if (_mali_mem_profiling_to_file_enabled())
	{
		char buf[256];
		_mali_sys_snprintf(buf, 256, "%d    %s  end.\n", (u32)_mali_sys_get_time_usec(), str);
		_mali_arch_mem_profiling_fwrite(buf);
	}
	else
	{
		_mali_arch_mem_profiling_fclose();
	}
}

/**
 * @brief Traces the memory usage information for func call
 * @param str The memory usage information you are tracing.
 */
MALI_STATIC_INLINE void _mali_mem_profiling_to_file_info(const char *str)
{
	if (_mali_mem_profiling_to_file_enabled())
	{
		char buf[256];
		_mali_sys_snprintf(buf, 256, "%d    %s\n", (u32)_mali_sys_get_time_usec(), str);
		_mali_arch_mem_profiling_fwrite(buf);
	}
	else
	{
		_mali_arch_mem_profiling_fclose();
	}
}

#define MALI_MEM_PROFILING_TO_FILE_BEGIN(name) _mali_mem_profiling_to_file_begin(name)
#define MALI_MEM_PROFILING_TO_FILE_END(name)    _mali_mem_profiling_to_file_end(name)
#define MALI_MEM_PROFILING_TO_FILE_ENABLED()    _mali_mem_profiling_to_file_enabled()
#define MALI_MEM_PROFILING_TO_FILE_INFO(str) _mali_mem_profiling_to_file_info(str)
#else
#define MALI_MEM_PROFILING_TO_FILE_BEGIN(name)
#define MALI_MEM_PROFILING_TO_FILE_END(name)
#define MALI_MEM_PROFILING_TO_FILE_ENABLED()    NULL
#define MALI_MEM_PROFILING_TO_FILE_INFO(str)
#endif /* MALI_MEMORY_PROFILING */

#endif /*_MALI_PROFILING_H */
