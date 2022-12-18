/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef MALI_PIXEL_FORMAT_H
#define MALI_PIXEL_FORMAT_H

#include <mali_system.h>
#include <shared/m200_td.h> /*Needed for mali_pixel enum */

/**
 * The different framebuffer formats for m200
 * The notation is MALI_PIXEL_FORMAT_[Channel Numbits, Channel Numbits...]
 * A = alpha
 * R = red
 * G = green
 * B = blue
 * Z = depth
 * S = Stencil
 * FP16 = 16 bits floating point
 * X = unused bits
 */
typedef enum mali_pixel_format
{
	MALI_PIXEL_FORMAT_NONE = -1,
	MALI_PIXEL_FORMAT_R5G6B5 = 0,
	MALI_PIXEL_FORMAT_A1R5G5B5 = 1,
	MALI_PIXEL_FORMAT_A4R4G4B4 = 2,
	MALI_PIXEL_FORMAT_A8R8G8B8 = 3,
	MALI_PIXEL_FORMAT_B8 = 4,
	MALI_PIXEL_FORMAT_G8B8 = 5,
	MALI_PIXEL_FORMAT_ARGB_FP16 = 6,
	MALI_PIXEL_FORMAT_B_FP16 = 7,
	MALI_PIXEL_FORMAT_GB_FP16 = 8,
	MALI_PIXEL_FORMAT_S8 = 13,
	MALI_PIXEL_FORMAT_Z16 = 14,
	MALI_PIXEL_FORMAT_S8Z24 = 15,
	MALI_PIXEL_FORMAT_COUNT
} mali_pixel_format;

typedef enum mali_pixel_layout
{
	MALI_PIXEL_LAYOUT_INVALID = -1,
	MALI_PIXEL_LAYOUT_LINEAR = 0,
	MALI_PIXEL_LAYOUT_INTERLEAVED = 1,
	MALI_PIXEL_LAYOUT_INTERLEAVED_BLOCKS = 2
} mali_pixel_layout;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets the pixel format's number of bits per pixel.
 * @param pixel_format
 * @return size in bits
 */
MALI_IMPORT s32 __mali_pixel_format_get_bpp(enum mali_pixel_format pixel_format);

/**
 *  Returns the number of bits per component for a given mali pixel format.
 * @param pixel_format
 * @param r Pointer to a u32 in which to return the red component storage depth. Can be NULL.
 * @param g Pointer to a u32 in which to return the green component storage depth. Can be NULL.
 * @param b Pointer to a u32 in which to return the blue component storage depth. Can be NULL.
 * @param a Pointer to a u32 in which to return the alpha component storage depth. Can be NULL.
 * @param d Pointer to a u32 in which to return the depth component storage depth. Can be NULL.
 * @param s Pointer to a u32 in which to return the stencil component storage depth. Can be NULL.
 */
MALI_IMPORT void _mali_pixel_format_get_bpc(enum mali_pixel_format pixel_format,
        u32 *r, u32 *g, u32 *b,
        u32 *a, u32 *d, u32 *s);

/**
 * Returns the texel layout corresponding to the input pixel layout
 * @param pixel_layout The pixel layout to be converted
 */
MALI_IMPORT enum m200_texture_addressing_mode _mali_pixel_layout_to_texel_layout(
    enum mali_pixel_layout pixel_layout);

/**
 * Returns the pixel layout corresponding to the input texel layout
 * @param texel_layout The texel layout to be converted
 */
MALI_IMPORT enum mali_pixel_layout _mali_texel_layout_to_pixel_layout(
    enum m200_texture_addressing_mode);

/**
 * Returns the texel format corresponding to the input pixel format
 * @param pixel_format The pixel format to be converted
 */
MALI_IMPORT enum m200_texel_format _mali_pixel_to_texel_format(
    enum mali_pixel_format pixel_format);

/**
 * Returns the pixel format corresponding to the input texel format
 * @param texel_format The texel format to be converted
 */
MALI_IMPORT enum mali_pixel_format _mali_texel_to_pixel_format(
    enum m200_texel_format texel_format);

#if MALI_BIG_ENDIAN
/**
 * Returns whether the pixel format supports pixel format thunking
 * @param format The pixel format to be checked
 */
MALI_IMPORT mali_bool _support_pixel_format_thunking(mali_pixel_format format);
#endif


#if MALI_INSTRUMENTED || defined(DEBUG)

/** Returns a C-string identifying the pixel format,
 *  used in MRI messages.
 */
MALI_IMPORT const char *_mali_pixel_format_string(enum mali_pixel_format pixel_format);
#endif /* MALI_INSTRUMENTED */

#ifdef __cplusplus
}

#endif /* MALI_INSTRUMENTED || DEBUG */

#endif /* MALI_PIXEL_FORMAT_H */
