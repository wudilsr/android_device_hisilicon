/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_COUNTERS_DUMP_H_
#define _MALI_COUNTERS_DUMP_H_

#include "mali_instrumented_counter_types.h"
#include "mali_instrumented_context_types.h"

/**
 * Calculate the needed buffer size for retrieving the header tree as XML with
 * the _instrumented_get_xml_tree function.
 *
 * \param ctx                the instrumented context
 * \param group              the counter group to print
 * \return                   the number of bytes requiered (including null-term)
 */
MALI_IMPORT
unsigned long _instrumented_get_xml_tree_size(mali_instrumented_context *ctx, const mali_counter_group *group);

/**
 * Recursively 'write' header tree as XML to a char buffer
 *
 * \param ctx                the instrumented context
 * \param group              the counter group to print
 * \param next               the position in the buffer where the next char should be put
 * \param end                the position after the last in the result buffer,
 * \return                   position in buffer for the next char after this call
 *
 * Output a description of the counter variables in the given 'group'
 * and recursively for its sub-groups.  To produce a dump file, this is called by
 * _instrumented_write_headers  below, with the root group as parameter.
 * It is used similarly in the MRI system, see MRPServer::countGetCounterInfoRemote.
 */
MALI_IMPORT
char *_instrumented_get_xml_tree(mali_instrumented_context *ctx, const mali_counter_group *group, char *next, char *end);

/**
 * Open a dump file for dumping counters
 * - called automatically by _instrumented_finish_init
 *
 * Which file to open is given by the environment variable MALI_DUMP_FILE. The
 * name of the dump is given with MALI_DUMP_NAME. The dump file will be
 * attempted opened. Previously existing files will be overwritten.
 *
 * \param ctx               the instrumented context
 */
MALI_IMPORT
void _instrumented_open_dump(mali_instrumented_context *ctx);

/**
 * Close the dump file
 *
 * This will close the dump file previously opened in the given context.
 *
 * \param ctx               the instrumented context
 */
MALI_IMPORT
void _instrumented_close_dump(mali_instrumented_context *ctx);

/**
 * Writes the whole header tree to the opened dumpfile inside a <countertree> block.
 * - called automatically by _instrumented_finish_init
 *
 *   \param ctx             the instrumented context
 */
MALI_IMPORT
void _instrumented_write_headers(mali_instrumented_context *ctx);

/**
 * Write the counter values from a given frame to the dump file.
 * - called automatically by _instrumented_end_frame
 *
 * If not already started, this function will write the <frames> tag to file.
 * Then, the specified frame will be written inside a <frame> tag.
 *
 * \param ctx               the instrumented context
 * \param frame             pointer to the frame
 */
MALI_IMPORT
void _instrumented_write_frame(mali_instrumented_context *ctx, mali_instrumented_frame *frame);

#endif /* _MALI_COUNTERS_DUMP_H_ */
