/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_INCREMENTAL_RENDERING_H_
#define _MALI_INCREMENTAL_RENDERING_H_

#include <mali_system.h>
#include "mali_frame_builder.h"

/**
 * Performs incremental rendering and a readback on the given frame builder.
 *
 * The act of performing an incremental render will end the current frame, and
 * flush out the frame to all output attachments, including the virtual ones.
 * A new frame with conditional readbacks will be set up to read back any framebuffer
 * information flushed out. Any information not caught by an output buffer will be lost.
 *
 * @note Calling this function will reset the frame_builder, including calling all callbacks that
 *       have been added to it
 * @note After calilng this function, the framebuilder is in state "UNDEFINED". No
 *       more rendering is required.
 * @note If a failure occurs then the framebuffer results are undefined
 *
 * @param frame_builder          - The frame builder to perform incremental rendering on, thereby
 *                                 resolving all previously registered draw calls/geometry
 * @return An error code if something went wrong
 */
MALI_IMPORT MALI_CHECK_RESULT mali_err_code _mali_incremental_render(mali_frame_builder *frame_builder);

#endif /* _MALI_INCREMENTAL_RENDERING_H_ */

