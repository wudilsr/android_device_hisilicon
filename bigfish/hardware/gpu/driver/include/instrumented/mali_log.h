/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_LOG_H_
#define _MALI_LOG_H_

#include "mali_system.h"

#include "mali_instrumented_context_types.h"
#include "mali_instrumented_log_types.h"

/* MALI_INSTRUMENTED wrappers for instrumented and non-instrumented expansion */
/**
 * @def     MALI_INSTRUMENTED_LOG((args))
 * @brief   Logging function for instrumented drivers with severity level.
 * @param  Parantheses with the contents to be sent to _MALI_INSTRUMENTED_LOG (_instrumented_log)
 * @note  MALI_INSTRUMENTED_LOG could NOT defined as follows since this is ISO C 99 specific:
 *      MALI_INSTRUMENTED_LOG( ctx, level, format, ... ) _instrumented_log( ctx, level, format ## __VA_ARGS_ )
 *      To maintain ISO C 90 compliance args must parenthesesed and passed to MALI_INSTRUMENTED_LOG.
 */
#define _MALI_INSTRUMENTED_LOG _instrumented_log
#define MALI_INSTRUMENTED_LOG( args ) _MALI_INSTRUMENTED_LOG args
#define MALI_INSTRUMENTED_SET_LOG_LEVEL( ctx, level ) _instrumented_set_log_level( ctx, level )
#define MALI_INSTRUMENTED_OPEN_LOG_FILE( ctx,  filename ) _instrumented_open_log_file( ctx,  filename )
#define MALI_INSTRUMENTED_CLOSE_LOG_FILE( ctx ) _instrumented_close_log_file( ctx )
#define MALI_INSTRUMENTED_REGISTER_LOG_CALLBACK( ctx, callback ) _instrumented_register_log_callback( ctx, callback )
#define MALI_INSTRUMENTED_WRITE_TO_LOG_FILE( ctx, message ) _instrumented_write_to_log_file( ctx, message )

/**
 * Log a message
 *
 * @param level              log level of message (severity)
 * @param message            the message to log. Format the message so that it doesn't have a
 *                           newline at the end
 */
MALI_IMPORT
void _instrumented_log(mali_instrumented_context *ctx, mali_log_level level, char *format, ...);

/**
 * Set debug driver log level
 *
 * @param level              new log level
 */
MALI_IMPORT
void _instrumented_set_log_level(mali_instrumented_context *ctx, mali_log_level level);

/**
 * Open a log file in the given context
 *
 * @param ctx               The context to use
 * @param filename          The log file to open
 */
MALI_IMPORT
mali_err_code _instrumented_open_log_file(mali_instrumented_context *ctx, const char *filename) MALI_CHECK_RESULT;

/**
 * Open a close file in the given context
 *
 * @param ctx               The context to use
 */
MALI_IMPORT
void _instrumented_close_log_file(mali_instrumented_context *ctx);

/**
 * Register a callback that receives log messages. The format of the
 * callback function is defined in mali_instrumented_log_types.h
 *
 * @param ctx               The context to register the callback in
 * @param callback          The callback to register
 * @return                  MALI_ERR_NO_ERROR if success,
 *                          MALI_ERR_OUT_OF_MEMORY if allocation fails
 */
MALI_IMPORT
mali_err_code _instrumented_register_log_callback(mali_instrumented_context *ctx, mali_log_callback callback);

/**
 * Write a message to the currently opened log file. Note, the file must
 * be opened before calling this function.
 *
 * @param ctx               The context whose log file will be written to
 * @param message           The log entry to write
 */
MALI_IMPORT
void _instrumented_write_to_log_file(mali_instrumented_context *ctx, char *message);

#endif /* _MALI_LOG_H_ */

