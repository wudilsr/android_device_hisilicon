/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2011, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_FRAME_DUMP_H_
#define _MALI_FRAME_DUMP_H_

#include "mali_instrumented_frame.h"

/**
 * Write a framebuffer to a .ppm file.
 *
 * This function writes a framebuffer (or: any mali_surface) to a .ppm image file.
 *
 * \param filename Name of file to write to.
 * \param render_target Spesification of the frame buffer we render to, and its settings
 */
MALI_IMPORT
void _instrumented_write_frame_dump(char *filename, mali_surface *render_target);

/**
 * Write a framebuffer to a .hex + .hex.metadata file.
 *
 * This function writes a framebuffer (or: any mali_surface) to a dumped image file.
 *
 * \param filename Name of file to write to, minus extension.
 * \param render_target Spesification of the frame buffer we render to, and its settings
 */
MALI_IMPORT
void _instrumented_write_frame_dump_hex(char *filename, mali_surface *render_target);

#endif /* _MALI_FRAME_DUMP_H_ */

