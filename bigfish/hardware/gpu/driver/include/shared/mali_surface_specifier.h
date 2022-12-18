/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef MALI_SURFACE_SPECIFIER_H
#define MALI_SURFACE_SPECIFIER_H

#include <mali_system.h>
#include <shared/mali_pixel_format.h>
#include <shared/mali_texel_format.h>

typedef enum
{
	MALI_SURFACE_COLORSPACE_lRGB = 0,
	MALI_SURFACE_COLORSPACE_sRGB = 1
} mali_surface_colorspace;

typedef enum
{
	MALI_SURFACE_ALPHAFORMAT_NONPRE = 0,
	MALI_SURFACE_ALPHAFORMAT_PRE = 1
} mali_surface_alphaformat;

typedef enum
{
	MALI_ENDIANESS_NEEDS_CONVERSION = 0,
	MALI_ENDIANESS_INVARIANT = 1
} mali_surface_endianess;

typedef struct mali_surface_specifier
{
	u16 width;                                /* The width of the surface in pixels. */
	u16 height;                               /* The height of the surface in pixels. */
	u16 pitch;                                /* The size of one pixel row in bytes, or 0 to compute from the width and format. Must be 0 for non-linear layouts*/
	mali_pixel_format pixel_format;           /* The pixel format of this surface. If MALI_PIXEL_FORMAT_NONE, not writable */
	m200_texel_format texel_format;           /* The texel format of this surface. If M200_TEXEL_FORMAT_NO_TEXTURE, not readable */
	mali_pixel_layout pixel_layout;           /* The pixel layout for this surface. Should always be specified */
	m200_texture_addressing_mode texel_layout;/* The texel layout for this surface. Should always be specified */
	mali_bool red_blue_swap;                  /* Whether the red and blue componets are swapped. RGBA -> BGRA */
	mali_bool reverse_order;                  /* Whether the components have reverse order. RGBA -> ABGR */
	mali_bool premultiplied_alpha;            /* Whether alpha component is premultiplied in color components or not */
	mali_surface_colorspace colorspace;       /* Which color space the surface color components resides */
	mali_bool alpha_to_one;                   /* Whether alpha component is to be expanded to ones */
	mali_surface_endianess big_endian_surf;   /* The surface is BE if it's allocated as one of pixmap, windowsurface and CPU memory,
                                                 it's LE for pbuffer or internal texture. */
} mali_surface_specifier;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Fills out a surface format structure
 * @param output The struct to fill out. This is a pure output parameter.
 * @param width  The width of the surface in pixels.
 * @param height The height of the surface in pixels.
 * @param pitch  The size of one pixel row in bytes, or 0 to compute from the width and format. Must be 0 for non-linear layouts
 * @param pformat The required pixel format
 * @param tformat The required texel format
 * @param playoutThe required pixel layout
 * @param tlayout The required texel layout
 * @param rbswap The red/blue swap flag for this format
 * @param revorder The reverse order flag for this format
 * @param alpha_to_one Indicates whether to expand alpha component to one.
 * @param be_surf Indicates whether the surface is BE or LE
 * NOTE: This function will always specify all fields in the surface format struct given.
 */
MALI_STATIC_INLINE void _mali_surface_specifier_ex(mali_surface_specifier *output,
        u16 width, u16 height, u16 pitch,
        mali_pixel_format pformat, m200_texel_format tformat,
        mali_pixel_layout playout, m200_texture_addressing_mode tlayout,
        mali_bool rbswap, mali_bool revorder,
        mali_surface_colorspace colorspace, mali_surface_alphaformat alpha_format,
        mali_bool alpha_to_one, mali_surface_endianess be_surf)
{
#if !MALI_BIG_ENDIAN
	MALI_IGNORE(be_surf);
#endif
	output->width = width;
	output->height = height;
	output->pitch = pitch;
	output->pixel_format = pformat;
	output->texel_format = tformat;
	output->pixel_layout = playout;
	output->texel_layout = tlayout;
	output->red_blue_swap = rbswap;
	output->reverse_order = revorder;
	output->colorspace = colorspace;
	output->premultiplied_alpha = alpha_format;
	output->alpha_to_one = alpha_to_one;
#if MALI_BIG_ENDIAN
	output->big_endian_surf = be_surf;
#else
	output->big_endian_surf = MALI_ENDIANESS_INVARIANT;
#endif
}

/**
 * Also fills out a format structure, but makes a guess on texel format, based on pixel format. Usually, this is good enough
 * @param output The struct to fill out. This is a pure output parameter.
 * @param width  The width of the surface in pixels.
 * @param height The height of the surface in pixels.
 * @param pitch  The size of one pixel row in bytes, or 0 to compute from the width and format. Must be 0 for non-linear layouts
 * @param pformat The required pixel format
 * @param playout The required pixel layout
 * @param rbswap The red/blue swap flag for this format
 * @param revorder The reverse order flag for this format
 * @param be_surf Indicates whether the surface is BE or LE
 * NOTE: This function will always specify all fields in the surface format struct given.
 */
MALI_STATIC_INLINE void _mali_surface_specifier(mali_surface_specifier *output,
        u16 width, u16 height, u16 pitch,
        mali_pixel_format pformat, mali_pixel_layout playout,
        mali_bool rbswap, mali_bool revorder, mali_surface_endianess be_surf)
{
	_mali_surface_specifier_ex(output, width, height, pitch,
	                           pformat, _mali_pixel_to_texel_format(pformat),
	                           playout, _mali_pixel_layout_to_texel_layout(playout), rbswap, revorder,
	                           MALI_SURFACE_COLORSPACE_sRGB, MALI_SURFACE_ALPHAFORMAT_NONPRE, MALI_FALSE, be_surf);
}

/**
 * Clones a mali_surface_specifier
 * @param output The struct to fill out. This is a pure output parameter.
 * @param input  The struct to be copied.
 * NOTE: This function will always specify all fields in the surface format struct given.
 */

MALI_STATIC_INLINE void _mali_surface_specifier_clone(mali_surface_specifier *output, const mali_surface_specifier *input)
{
	MALI_DEBUG_ASSERT_POINTER(output);
	MALI_DEBUG_ASSERT_POINTER(input);
	_mali_surface_specifier_ex(output,
	                           input->width, input->height, input->pitch,
	                           input->pixel_format, input->texel_format,
	                           input->pixel_layout, input->texel_layout,
	                           input->red_blue_swap, input->reverse_order,
	                           input->colorspace, input->premultiplied_alpha ? MALI_SURFACE_ALPHAFORMAT_PRE : MALI_SURFACE_ALPHAFORMAT_NONPRE,
	                           input->alpha_to_one, input->big_endian_surf);
}

/**
 * returns the amount of bits per pixel available in the given surface format
 * @param format The surface format struct on which to calculate bpp size
 * @returns the number of bits per pixel.
 */
MALI_IMPORT u32 _mali_surface_specifier_bpp(const mali_surface_specifier *format);

/**
 * return the minimum pitch of a given linear specifier
 * @param format - the input specifier
 * @return The minimum pitch of the specifier that adheres to Mali requirements
 */
MALI_IMPORT u32 _mali_surface_specifier_calculate_minimum_pitch(const mali_surface_specifier *format);

/**
 * return the datasize of a given specifier
 * @param format - The input specifier
 * @return The datasize (in bytes) of the data area the GPU will access based
 *         on this specifier.
 */
MALI_IMPORT u32 _mali_surface_specifier_datasize(const mali_surface_specifier *format);

/**
 * compares two formats for format and layout only
 * @param format_l The left input for compare
 * @param format_r The right input for compare
 * @returns 0 if the formats are equal. 1 if r > l. -1 if l > r.
 */
MALI_STATIC_INLINE int _mali_surface_specifier_cmp_format_layout(const mali_surface_specifier *format_l, const mali_surface_specifier *format_r)
{
	MALI_DEBUG_ASSERT_POINTER(format_l);
	MALI_DEBUG_ASSERT_POINTER(format_r);

	if (format_l->pixel_format != format_r->pixel_format)
	{
		return format_l->pixel_format - format_r->pixel_format;
	}

	if (format_l->texel_format != format_r->texel_format)
	{
		return format_l->texel_format - format_r->texel_format;
	}

	if (format_l->pixel_layout != format_r->pixel_layout)
	{
		return format_l->pixel_layout - format_r->pixel_layout;
	}

	if (format_l->texel_layout != format_r->texel_layout)
	{
		return format_l->texel_layout - format_r->texel_layout;
	}

	if (format_l->red_blue_swap != format_r->red_blue_swap)
	{
		return format_l->red_blue_swap - format_r->red_blue_swap;
	}

	if (format_l->reverse_order != format_r->reverse_order)
	{
		return format_l->reverse_order - format_r->reverse_order;
	}

	if (format_l->premultiplied_alpha != format_r->premultiplied_alpha)
	{
		return format_l->premultiplied_alpha - format_r->premultiplied_alpha;
	}

	if (format_l->colorspace != format_r->colorspace)
	{
		return format_l->colorspace - format_r->colorspace;
	}

	return 0;
}

/**
 * compares two formats
 * @param format_l The left input for compare
 * @param format_r The right input for compare
 * @returns 0 if the formats are equal. 1 if r > l. -1 if l > r. D
 */
MALI_STATIC_INLINE mali_bool _mali_surface_specifier_cmp(const mali_surface_specifier *format_l, const mali_surface_specifier *format_r)
{
	int format_equal;
	MALI_DEBUG_ASSERT_POINTER(format_l);
	MALI_DEBUG_ASSERT_POINTER(format_r);

	format_equal = _mali_surface_specifier_cmp_format_layout(format_l, format_r);

	if (format_equal != 0)
	{
		return format_equal;
	}

	if (format_l->width != format_r->width)
	{
		return format_l->width - format_r->width;
	}

	if (format_l->height != format_r->height)
	{
		return format_l->height - format_r->height;
	}

	if (format_l->pitch != format_r->pitch)
	{
		return format_l->pitch - format_r->pitch;
	}

	return 0;
}

/**
 * Creates a mipmap-reduced specifier matching the input in all ways, except for dimensions.
 * The dimensions are divided by 2, but will never be smaller than 1. This follows the
 * HW requirements of Mali. Pitch remains unchanged.
 *
 * @param out - Will be filled out with a new surface specifier. This is the reduced mipmap level.
 * @param in - Input data forming the base of the output specifier. This is the previous mipmap level.
 */
MALI_STATIC_INLINE void _mali_surface_specifier_mipmap_reduce(mali_surface_specifier *out, const mali_surface_specifier *in)
{
	MALI_DEBUG_ASSERT_POINTER(out);
	MALI_DEBUG_ASSERT_POINTER(in);

	*out = *in; /* struct copy. Should be faster than calling memcpy.  */
	out->width = MAX(out->width / 2, 1);
	out->height = MAX(out->height / 2, 1);
}

#ifdef __cplusplus
}
#endif

#endif /* MALI_SURFACE_SPECIFIER_H */
