/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2013-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * API to add function / value systrace events.
 * To use it, call the macros
 * MALI_SYSTRACE_BEGIN(cat,str)
 * MALI_SYSTRACE_END(cat)
 * MALI_SYSTRACE_ASYNC_BEGIN(cat,str,cookie)
 * MALI_SYSTRACE_ASYNC_END(cat,str,cookie)
 * MALI_SYSTRACE_VALUE(cat, str,val)
 */
#ifndef _MALI_SYSTRACE_H_
#define _MALI_SYSTRACE_H_


/* set to any of the below categories to enable function or value tracing */
#define MALI_SYSTRACE_PROPERTY_CATEGORY    "mali.debug.systrace.category"

/* set to 1 or true to enable memory usage tracking */
#define MALI_SYSTRACE_PROPERTY_MEMORY      "mali.debug.systrace.memory"

/* set to 1 or true to enable fps tracking (requires MALI_SYSTRACE_API_EGL_INTERNAL) */
#define MALI_SYSTRACE_PROPERTY_FPS         "mali.debug.systrace.fps"

/* set to any value [1..30] to indicate the moving average fps window */
#define MALI_SYSTRACE_PROPERTY_FPS_WINDOW  "mali.debug.systrace.fps_window"

/* set to 1 or true to enable surface tracking */
#define MALI_SYSTRACE_PROPERTY_SURFACE_TRACKING "mali.debug.systrace.tracking"


/* maximum size of systrace string */
#define MALI_SYSTRACE_MAX_SIZE       1024

/* maximum window of timestamps tracked for fps */
#define MALI_SYSTRACE_FPS_TIMESTAMPS   30

/* default setting of fps window */
#define MALI_SYSTRACE_FPS_WINDOW       10


#ifdef __cplusplus
extern "C" {
#endif

enum mali_systrace_category
{
	MALI_SYSTRACE_API_EGL           = (1 << 0), /*  1 */
	MALI_SYSTRACE_API_GLES          = (1 << 1), /*  2 */
	MALI_SYSTRACE_API_BASE          = (1 << 2), /*  4 */
	MALI_SYSTRACE_API_SHARED        = (1 << 3), /*  8 */
	MALI_SYSTRACE_API_EGL_INTERNAL  = (1 << 4), /* 16 */
	MALI_SYSTRACE_API_GLES_INTERNAL = (1 << 5), /* 32 */
	MALI_SYSTRACE_API_BASE_INTERNAL = (1 << 6), /* 64 */
};

enum mali_mem_systrace_category
{
	/**
	 * The memory systace level decides which mali memory usge will be tracked by systrace.
	 * MALI_MEM_SYSTRACE_LEVEL_1, only track total memory,free memory,allocated memory.
	 * The systrace level for sub memory usages, please refer to mali_mem_systrace_get_level.
	 */

	MALI_MEM_SYSTRACE_LEVEL_1    = 1,
	MALI_MEM_SYSTRACE_LEVEL_2,
	MALI_MEM_SYSTRACE_LEVEL_3,
	MALI_MEM_SYSTRACE_LEVEL_4,
};

/**
 * @brief Starts a function systrace
 * @param cat The category this function belongs to (see @mali_systrace_category)
 * @param str The function name, or any other string to indicate the scope you want to trace.
 */
void mali_systrace_begin(int cat, const char *str);

/**
 * @brief Ends a function systrace
 * @param cat The category that this function belongs to (see @mali_systrace_category)
 */
void mali_systrace_end(int cat);

/**
 * @brief Starts an asynchronous function systrace
 * @param cat The category that this function belongs to (see @mali_systrace_category)
 * @param str The function name, or any other string to indicate the scope you want to trace.
 * @param cookie A unique cookie used to differentiate between concurrent traces with same function name
 */
void mali_systrace_begin_async(int cat, const char *str, int cookie);

/**
 * @brief Stops an asynchronous function systrace
 * @param cat The category that this function blongs to (see @mali_systrace_category)
 * @param str The function name, or any other string to indicate the scope you want to trace.
 * @param cookie A unique cookie used to differentiate between concurrent traces with same function name
 */
void mali_systrace_end_async(int cat, const char *str, int cookie);

/**
 * @brief Traces an integer value
 * @param cat The category that this value belongs to (see @mali_systrace_category)
 * @param str The value name, or any other string to indicate the value you are tracing.
 * @param value The integer value
 */
void mali_systrace_value(int cat, const char *str, int value);

/**
 * @brief Check if mali memory systrace is enabled.
 * @param cat The category that need to check (see @mali_mem_systrace_category)
 * @Return enabled when > 0, disabled otherwise.
 */
int mali_systrace_memory_enabled(int cat);

/**
 * @brief Starts a memory_alloc systrace
 * @param cat The category this alloc belongs to (see @mali_mem_systrace_category)
 * @param str Any other string to indicate the scope you want to trace.
 */
void mali_systrace_memory_begin(int cat, const char *str);

/**
 * @brief Ends a memory_alloc systrace
 * @param cat The category that this alloc belongs to (see @mali_mem_systrace_category)
 */
void mali_systrace_memory_end(int cat);

/**
 * @brief Traces an memory usage integer value
 * @param cat The category that this value belongs to (see @mali_mem_systrace_category)
 * @param str The value name, or any other string to indicate the value you are tracing.
 * @param value The memory usage integer value
 */
void mali_systrace_memory_value(int cat, const char *str, int value);


#ifdef MALI_SYSTRACE_ENABLE

#define MALI_SYSTRACE_BEGIN(cat,str)               mali_systrace_begin(cat,str)
#define MALI_SYSTRACE_END(cat)                     mali_systrace_end(cat)
#define MALI_SYSTRACE_ASYNC_BEGIN(cat,str,cookie)  mali_systrace_begin_async(cat,str,cookie)
#define MALI_SYSTRACE_ASYNC_END(cat,str,cookie)    mali_systrace_end_async(cat,str,cookie)
#define MALI_SYSTRACE_VALUE(cat, str,val)          mali_systrace_value(cat,str,val)
#define MALI_SYSTRACE_MEMORY_ENABLED(cat)      mali_systrace_memory_enabled(cat)
#define MALI_SYSTRACE_MEMORY_BEGIN(cat,str)    mali_systrace_memory_begin(cat,str)
#define MALI_SYSTRACE_MEMORY_END(cat)              mali_systrace_memory_end(cat)
#define MALI_SYSTRACE_MEMORY_VALUE(cat,str,value)  mali_systrace_memory_value(cat,str,value)


#else /* MALI_SYSTRACE_ENABLE */

#define MALI_SYSTRACE_BEGIN(cat,str)
#define MALI_SYSTRACE_END(cat)
#define MALI_SYSTRACE_ASYNC_BEGIN(cat,str,cookie)
#define MALI_SYSTRACE_ASYNC_END(cat,str,cookie)
#define MALI_SYSTRACE_VALUE(cat,str,val)
#define MALI_SYSTRACE_MEMORY_ENABLED(cat)   NULL
#define MALI_SYSTRACE_MEMORY_BEGIN(cat,str)
#define MALI_SYSTRACE_MEMORY_END(cat)
#define MALI_SYSTRACE_MEMORY_VALUE(cat,str,value)


#endif

#ifdef __cplusplus
}
#endif

#endif /* _MALI_SYSTRACE_H_ */

