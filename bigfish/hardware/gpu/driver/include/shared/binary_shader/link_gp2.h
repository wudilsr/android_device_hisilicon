/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef LINK_GP2_H
#define LINK_GP2_H

#include <mali_system.h>
#include <shared/binary_shader/bs_object.h>
#include <shared/mali_linked_list.h>


/**
 * @brief Relinks a binary gp2 program, moving around attributes according to the remap table.
 * @param po A linked program object containing a vertex shader program
 * @param attrib_remap An array of 16 elemets containing remapping instructions.
 *        Example: If attrib_array[9] = 3, then attribute 9 should be remapped to attribute 3.
 * @param rewrite_symbols If true, the function will also rewrite the symbol table and stream table.
 *        Setting this field to TRUE is what you want, but some rare workarounds (like 4326) might require you not to.
 * @note
 *        The attribute remap table must contain legal values (0..15), or the function will assertcrash
 *        The program can technically be relinked multiple times, but every time you alias two attributes,
 *        you can never un-alias them. It is therefore advisable to keep a copy of the original program
 *        if you want to do this process more than once.
 */
MALI_IMPORT MALI_CHECK_RESULT mali_err_code _mali_gp2_link_attribs(bs_program *po, int attrib_remap[], mali_bool rewrite_symbols);


/**
 * @brief Rewrites a binary gp2 program, moving varying streams in the gp2 program to match those in the
 *        mali200 program. All streams (position, pointsize and generic varyings) are handled.
 * @param po The linked program object to rewrite the shader for.
 * @note You should call this only once per link.
 */
MALI_IMPORT MALI_CHECK_RESULT mali_err_code __mali_gp2_rewrite_vertex_shader_varying_locations(bs_program *po) MALI_CHECK_RESULT;

#endif /* LINK_GP2_H */
