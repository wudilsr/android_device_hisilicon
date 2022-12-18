/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef M200_TEXEL_FORMAT_H
#define M200_TEXEL_FORMAT_H


#include <mali_system.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Mapping tokens to Mali-200/Mali-400 texel format values.
 */
typedef enum m200_texel_format
{
	M200_TEXEL_FORMAT_L_1 = 0,
	M200_TEXEL_FORMAT_A_1 = 1,
	M200_TEXEL_FORMAT_I_1 = 2,
	M200_TEXEL_FORMAT_AL_11 = 3,
	M200_TEXEL_FORMAT_L_4 = 4,
	M200_TEXEL_FORMAT_A_4 = 5,
	M200_TEXEL_FORMAT_I_4 = 6,
	M200_TEXEL_FORMAT_ARGB_1111 = 7,
	M200_TEXEL_FORMAT_AL_44 = 8,
	M200_TEXEL_FORMAT_L_8 = 9,
	M200_TEXEL_FORMAT_A_8 = 10,
	M200_TEXEL_FORMAT_I_8 = 11,
	M200_TEXEL_FORMAT_RGB_332 = 12,
	M200_TEXEL_FORMAT_ARGB_2222 = 13,
	M200_TEXEL_FORMAT_RGB_565 = 14,
	M200_TEXEL_FORMAT_ARGB_1555 = 15,
	M200_TEXEL_FORMAT_ARGB_4444 = 16,
	M200_TEXEL_FORMAT_AL_88 = 17,
	M200_TEXEL_FORMAT_L_16 = 18,
	M200_TEXEL_FORMAT_A_16 = 19,
	M200_TEXEL_FORMAT_I_16 = 20,
#if !RGB_IS_XRGB
	M200_TEXEL_FORMAT_RGB_888 = 21,
#endif
	M200_TEXEL_FORMAT_ARGB_8888 = 22,
	M200_TEXEL_FORMAT_xRGB_8888 = 23,
	M200_TEXEL_FORMAT_ARGB_2_10_10_10 = 24,
	M200_TEXEL_FORMAT_RGB_11_11_10 = 25,
	M200_TEXEL_FORMAT_RGB_10_12_10 = 26,
	M200_TEXEL_FORMAT_AL_16_16 = 27,
	M200_TEXEL_FORMAT_ARGB_16_16_16_16 = 28,
	M200_TEXEL_FORMAT_PAL_4 = 29,
	M200_TEXEL_FORMAT_PAL_8 = 30,
	M200_TEXEL_FORMAT_FLXTC = 31,
	M200_TEXEL_FORMAT_ETC = 32,
	/* 33 is Reserved */
	M200_TEXEL_FORMAT_L_FP16 = 34,
	M200_TEXEL_FORMAT_A_FP16 = 35,
	M200_TEXEL_FORMAT_I_FP16 = 36,
	M200_TEXEL_FORMAT_AL_FP16 = 37,
	M200_TEXEL_FORMAT_ARGB_FP16 = 38,
	/* 39 is Reserved */
	/* 40 is Reserved */
	/* 41 is Reserved */
	/* 42 is Reserved */
	/* 43 is Reserved */
	M200_TEXEL_FORMAT_DEPTH_STENCIL_24_8 = 44,
	M200_TEXEL_FORMAT_CONVOLUTION_TEXTURE_64 = 45,
	M200_TEXEL_FORMAT_RGB_16_16_16 = 46,
	M200_TEXEL_FORMAT_RGB_FP16 = 47,
	/* 48 is Reserved */
	/* 49 is Reserved */
	M200_TEXEL_FORMAT_VERBATIM_COPY32 = 50,
	/* 51-62 are Reserved */
	M200_TEXEL_FORMAT_NO_TEXTURE = 63,
	/* Formats below are virtual and cant't be used by the HW*/
	M200_TEXEL_FORMAT_VIRTUAL_DEPTH32            = 64,
	M200_TEXEL_FORMAT_VIRTUAL_DEPTH16            = 65,
	M200_TEXEL_FORMAT_VIRTUAL_STENCIL_DEPTH_8_24 = 66,
	M200_TEXEL_FORMAT_VIRTUAL_RGB888             = 67,
	M200_TEXEL_FORMAT_VIRTUAL_DEPTH_STENCIL_16_0 = 68,
	M200_TEXEL_FORMAT_VIRTUAL_DEPTH_STENCIL_24_0 = 69,
	M200_TEXEL_FORMAT_VIRTUAL_DEPTH_STENCIL_0_4  = 70,
	M200_TEXEL_FORMAT_VIRTUAL_DEPTH_STENCIL_0_8  = 71
} m200_texel_format;

/**
 * Get texel size in bits.
 * @param format texel size
 * @return Number of bits needed to represent texel.
 */
MALI_IMPORT s32 __m200_texel_format_get_bpp(m200_texel_format format);

/**
 * Get size in bytes for each block to be copied into mali memory.
 * Endianess conversions between cpu and mali are made based on the size of
 * the block.
 * @param format texel size
 * @return Number of bytes in each element that is copied into mali memory.
 */
MALI_IMPORT s32 __m200_texel_format_get_bytes_per_copy_element(m200_texel_format format);

/**
 * Get texel size in bytes.
 * @note for 1,2 and 4 bit formats this function returns 1.
 * @param format texel format
 * @return Number of bytes
 */
MALI_STATIC_FORCE_INLINE s32 __m200_texel_format_get_size(m200_texel_format format)
{
	/* round upwards to nearest byte */
	return (__m200_texel_format_get_bpp(format) + 7) / 8;
}

/**
 * Returns whether a format supports rbswap and reverseorder flags or not.
 * @param format texel format to query
 * @param rb [out] MALI_TRUE if this format supports rbswap
 * @param ro [out] MALI_TRUE if this format supports revorder
 */
MALI_IMPORT void __m200_texel_format_flag_support(m200_texel_format format, mali_bool *rb, mali_bool *ro);

/**
 * Returns whether the texel format is alpha only.
 * @param format
 * @return MALI_TRUE if alpha only, MALI_FALSE otherwise.
 */
MALI_IMPORT mali_bool __m200_texel_format_is_alpha(m200_texel_format format);

/**
 * Returns whether format has an alpha component.
 * @param format
 * @return MALI_TRUE if it has an alpha component, MALI_FALSE otherwise
 */
MALI_IMPORT mali_bool __m200_texel_format_has_alpha(m200_texel_format format);

/**
 * @brief Converts a virtual m200_texel_format to a storage m200_texel_format
 * @param virtual_format the virtual m200_texel_format
 * @return The m200_texel_format used for storage
 */
MALI_IMPORT m200_texel_format __m200_texel_format_convert_virtual_to_storage(m200_texel_format virtual_format);

/**
 * Returns whether format has a luminance component.
 * @param format
 * @return MALI_TRUE if it has a luminance component, MALI_FALSE otherwise
 */
MALI_IMPORT mali_bool __m200_texel_format_has_luminance(m200_texel_format format);

/**
 * Returns whether format is luminance only.
 * @param format
 * @return MALI_TRUE if it is luminance only, MALI_FALSE otherwise
 */
MALI_IMPORT mali_bool __m200_texel_format_is_luminance(m200_texel_format format);

/**
 * Returns whether the texel format is intensity only.
 * @param format
 * @return MALI_TRUE if intensity only, MALI_FALSE otherwise.
 */
MALI_IMPORT mali_bool __m200_texel_format_is_intensity(m200_texel_format format);

/**
 * Returns the bit for each color component
 * @param format The input texel format
 * @param r pointer to the red bits
 * @param g pointer to the green bits
 * @param b pointer to the blue bits
 * @param a pointer to the alpha bits
 * @param d pointer to the depth bits
 * @param s pointer to the stencil bits
 */
MALI_IMPORT void __m200_texel_format_get_bpc(m200_texel_format format, u32 *r, u32 *g, u32 *b, u32 *a, u32 *d, u32 *s, u32 *l, u32 *i);

#ifdef __cplusplus
}
#endif

#endif /* M200_TEXEL_FORMAT_H */
