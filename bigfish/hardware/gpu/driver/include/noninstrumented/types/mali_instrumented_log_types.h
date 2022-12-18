/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_INSTRUMENTED_LOG_TYPES_H_
#define _MALI_INSTRUMENTED_LOG_TYPES_H_

#define INSTRUMENTED_LOG_BUFFER_SIZE 1024

struct mali_instrumented_context;

typedef enum mali_log_level
{
	MALI_LOG_LEVEL_NONE = 0,    /**< No logging. Not used as log level in any _mali_log() calls. */
	MALI_LOG_LEVEL_ERROR,       /**< Errors. Out of memory or bad input. */
	MALI_LOG_LEVEL_WARNING,     /**< Warnings. API calls give bad performance or accuracy. */
	MALI_LOG_LEVEL_EVERYTHING,  /**< Everything, including all API entrypoints */
	MALI_LOG_LEVEL_DEBUG        /**< Debug. Only used internally in debug builds. */
} mali_log_level;

typedef void (*mali_log_callback)(struct mali_instrumented_context *ctx, char *message);

#endif /* _MALI_INSTRUMENTED_LOG_TYPES_H_ */

