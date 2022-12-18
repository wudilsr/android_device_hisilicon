/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2007, 2009-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef __M200_TD_HEADER__
#define __M200_TD_HEADER__

#include <mali_system.h>
#include "mali_texel_format.h"

#ifdef __cplusplus
extern "C" {
#endif


/** size of Mali 200 texture descriptor in 32-bit words */
#define M200_TD_SIZE (512/32)
/** Expands the given parameters to the ones needed by _m200_td_set, done like this to be calculated in compile-time and to avoid
 *  too complicated usage of function:
 *    clear_mask The mask used to clear the field we are setting a value for
 *    index Which word we are to change
 *    field The mask (starting from 0), used to assert-check that we are not setting anything that will affect other values in the word
 *    left_index Passing of the left_index
 *    right_index Passing of the right_index
 *    right_index_small How many bits to right-shift in this word
 */
#define MALI_TD_SET_PARAMETER_EXPAND( left_index, right_index ) ~( ( ( 1 << ( left_index - right_index + 1 ) ) - 1 ) << ( right_index - ( ( right_index >> 5 ) << 5  ) ) ), ( left_index >> 5 ), ( ( 1 << ( left_index - right_index + 1 ) ) - 1 ), left_index, right_index, ( right_index - ( ( right_index >> 5 ) << 5  ) )


#if MALI_BIG_ENDIAN

#define MALI_TD_SET_TEXEL_FORMAT(dest, val) do { \
		(dest)[0] = ((dest)[0] & 0xc0ffffff) | ((val) << 24); \
	}while(0);

#define MALI_TD_SET_TEXEL_ORDER_INVERT(dest, val) do { \
		(dest)[0] = ((dest)[0] & 0xbfffffff) | ((val) << 30); \
	} while(0);

#define MALI_TD_SET_TEXEL_RED_BLUE_SWAP(dest, val) do { \
		(dest)[0] = ((dest)[0] & 0x7fffffff) | ((val) << 31); \
	} while(0);

#define MALI_TD_SET_TEXEL_BIAS_SELECT(dest, val) do { \
		(dest)[0] = ((dest)[0] & 0xfffcffff) | ((val) << 16); \
	} while(0);

#define MALI_TD_SET_TEXEL_TOGGLE_MSB(dest, val) do { \
		(dest)[0] = ((dest)[0] & 0xfffbffff) | ((val) << 18); \
	} while(0);

#define MALI_TD_SET_PALETTE_FORMAT(dest, val) do { \
		(dest)[0] = ((dest)[0] & 0xffe7ffff) | ((val) << 19); \
	} while(0);

#define MALI_TD_SET_PALETTE_ADDRESS(dest, val)  do { \
		(dest)[0] = ((dest)[0] & 0xff1f0000) | (((val) & 0x00000007) << 21) | \
					(((val) & 0x000007f8) << 5) | \
					(((val) & 0x0007f800) >> 11); \
		(dest)[1] = ((dest)[1] & 0x80ffffff) | (((val) & 0x0000007f) << 24); \
	} while( 0 );

#define MALI_TD_SET_TEXTURE_FORMAT(dest, val) do { \
		(dest)[1] = ((dest)[1] & 0x7ffcffff) | (((val) & 0x00000001) << 31) | \
					(((val) & 0x00000006) << 15); \
	} while(0);

#define MALI_TD_SET_TEXTURE_DIMENSIONALITY(dest, val) do { \
		(dest)[1] = ((dest)[1] & 0xfff3ffff) | ((val) << 18); \
	} while(0);

#define MALI_TD_SET_LAMBDA_LOW_CLAMP(dest, val) do { \
		(dest)[1] = ((dest)[1] & 0xff0ff0ff) | (((val) & 0x0000000f) << 20) | \
					(((val) & 0x000000f0) << 4); \
	} while(0);

#define MALI_TD_SET_LAMBDA_HIGH_CLAMP(dest, val) do { \
		(dest)[1] = ((dest)[1] & 0xffff0ff0) | (((val) & 0x0000000f) << 12) | \
					(((val) & 0x000000f0) >> 4); \
	} while(0);

#define MALI_TD_SET_LAMBDA_BIAS(dest, val) do { \
		(dest)[1] = ((dest)[1] & 0xffffff0f) | (((val) & 0x0000000f) << 4); \
		(dest)[2] = ((dest)[2] & 0xe0ffffff) | ((((val) >> 4) & 0x0000001f) << 24); \
	} while(0);

#define MALI_TD_SET_ANISOTROPY_LOG2(dest, val) do { \
		(dest)[2] = ((dest)[2] & 0x1fffffff) | ((val) << 29); \
	} while(0);

#define MALI_TD_SET_MIPMAPPING_MODE(dest, val) do { \
		(dest)[2] = ((dest)[2] & 0xfff9ffff) | ((val) << 17); \
	} while(0);

#define MALI_TD_SET_POINT_SAMPLE_MINIFY(dest, val) do { \
		(dest)[2] = ((dest)[2] & 0xfff7ffff) | ((val) << 19); \
	} while(0);

#define MALI_TD_SET_POINT_SAMPLE_MAGNIFY(dest, val) do { \
		(dest)[2] = ((dest)[2] & 0xffefffff) | ((val) << 20); \
	} while(0);

#define MALI_TD_SET_WRAP_MODE_S(dest, val) do { \
		(dest)[2] = ((dest)[2] & 0xff1fffff) | ((val) << 21); \
	} while(0);
#define MALI_TD_SET_WRAP_MODE_T(dest, val) do { \
		(dest)[2] = ((dest)[2] & 0xfffff8ff) | ((val) << 8); \
	} while(0);

#define MALI_TD_SET_WRAP_MODE_R(dest, val) do { \
		(dest)[2] = ((dest)[2] & 0xffffc7ff) | ((val) << 11); \
	} while(0);

#define MALI_TD_SET_TEXTURE_DIMENSION_S(dest, val) do { \
		(dest)[2] = ((dest)[2] & 0xffff3f00) | (((val) & 0x00000003) << 14) | \
		            (((val) & 0x000003fc) >> 2); \
		(dest)[3] = ((dest)[3] & 0xf8ffffff) | (((val) >> 10) << 24); \
	} while(0);

#define MALI_TD_SET_TEXTURE_DIMENSION_T(dest, val) do { \
		(dest)[3] = ((dest)[3] & 0x0700ffff) | (((val) & 0x0000001f) << 27) | \
                    (((val) & 0x00001fe0) << 11); \
	} while(0);

#define MALI_TD_SET_TEXTURE_DIMENSION_R(dest, val) do { \
		(dest)[3] = ((dest)[3] & 0xffff00e0) | (((val) & 0x000000ff) << 8) | \
                    (((val) & 0x00001f00) >> 8); \
	} while(0);
#define MALI_TD_SET_BORDER_COLOR_RED(dest, val) do { \
		(dest)[3] = ((dest)[3] & 0xffffff1f) | (((val) & 0x00000007) << 5); \
		(dest)[4] = ((dest)[4] & 0x00e0ffff) | (((val) & 0x000000ff) << 24) | \
                    (((val) & 0x00001f00) << 8); \
	} while( 0 );

#define MALI_TD_SET_BORDER_COLOR_GREEN(dest, val) do { \
		(dest)[4] = ((dest)[4] & 0xff1f00e0) | (((val) & 0x00000007) << 21) | \
                    (((val) & 0x000007f8) << 5) | \
                    (((val) & 0x0000f800) >> 11);  \
	} while(0);

#define MALI_TD_SET_BORDER_COLOR_BLUE(dest, val) do { \
		(dest)[4] = ((dest)[4] & 0xffffff1f) | (((val) & 0x00000007) << 5); \
		(dest)[5] = ((dest)[5] & 0x00e0ffff) | (((val) & 0x000000ff) << 24) | \
                    (((val) & 0x00001f00) << 8); \
    } while(0);

#define MALI_TD_SET_BORDER_COLOR_ALPHA(dest, val) do { \
		(dest)[5] = ((dest)[5] & 0xff1f00e0) | (((val) & 0x00000007) << 21) | \
                    (((val) & 0x000007f8) << 5) | \
                    (((val) & 0x0000f800) >> 11);  \
	} while(0);
#define MALI_TD_SET_SHADOW_MAPPING_AMBIENT(dest, val) do { \
		(dest)[5] = ((dest)[5] & 0xffffff1f) | (((val) & 0x00000007) << 5); \
		(dest)[6] = ((dest)[6] & 0x00e0ffff) | ((((val) >> 3) & 0x000000ff) << 24) | \
					((((val) >> 3) & 0x00001f00) << 8); \
	} while(0);

#define MALI_TD_SET_TEXTURE_ADDRESSING_MODE(dest, val) do { \
		(dest)[6] = ((dest)[6] & 0xff9fffff) | ((val) << 21); \
	} while(0);

#define MALI_TD_SET_BORDER_TEXEL_ENABLE(dest, val) do { \
		(dest)[6] = ((dest)[6] & 0xff7fffff) | ((val) << 23); \
	} while(0);

#define MALI_TD_SET_SHADOW_MAPPING_CMP_FUNC(dest, val) do { \
		(dest)[6] = ((dest)[6] & 0xfffff8ff) | ((val) << 8); \
	} while(0);

#define MALI_TD_SET_SHADOW_MAPPING_CPY_RGB(dest, val) do { \
		(dest)[6] = ((dest)[6] & 0xfffff7ff) | ((val) << 11); \
	} while(0);

#define MALI_TD_SET_SHADOW_MAPPING_CPY_ALPHA(dest, val) do { \
		(dest)[6] = ((dest)[6] & 0xffffefff) | ((val) << 12); \
	} while(0);

#define MALI_TD_SET_TEXTURE_STACKING_ENABLE(dest, val) do { \
		(dest)[6] = ((dest)[6] & 0xffffdfff) | ((val) << 13); \
	} while(0);

#define MALI_TD_SET_MIPMAP_ADDRESS_0(dest, val) do { \
		(dest)[6] = ((dest)[6] & 0xffffff3f) | (((val) & 0x00000003) << 6); \
		(dest)[7] = ((dest)[7] & 0x000000ff) | ((((val) >> 2) & 0x000000ff) << 24) | \
                    ((((val) >> 2) & 0x0000ff00) << 8) | \
                    ((((val) >> 2) & 0x00ff0000) >> 8); \
	} while(0);

#define MALI_TD_SET_MIPMAP_ADDRESS_1(dest, val) do { \
		(dest)[7] = ((dest)[7] & 0xffffff00) | (((val) & 0x000000ff)); \
		(dest)[8] = ((dest)[8] & 0x0000fcff) | (((val) & 0x0000ff00) << 16) | \
                    (((val) & 0x00ff0000) << 0) | \
                    (((val) & 0x03000000) >> 16); \
	} while(0);

#define MALI_TD_SET_MIPMAP_ADDRESS_2(dest, val) do { \
		(dest)[8] = ((dest)[8] & 0xffff0300) | (((val) & 0x0000003f) << 10) | \
                    (((val) & 0x00003fc0) >> 6); \
		(dest)[9] = ((dest)[9] & 0x00f0ffff) | ((((val) >> 14) & 0x000000ff) << 24) | \
                    ((((val) >> 14) & 0x00000f00) << 8); \
	} while( 0 );

#define MALI_TD_SET_MIPMAP_ADDRESS_3(dest, val) do { \
		(dest)[9] = ((dest)[9] & 0xff0f0000) | (((val) & 0x0000000f) << 20) | \
                    (((val) & 0x00000ff0) << 4) | \
                    (((val) & 0x000ff000) >> 12); \
		(dest)[10] = ((dest)[10] & 0xc0ffffff) | (((val) >> 20) << 24); \
	} while(0);

#define MALI_TD_SET_MIPMAP_ADDRESS_4(dest, val) do { \
		(dest)[10] = ((dest)[10] & 0x3f000000) | (((val) & 0x00000003) << 30) | \
                     (((val) & 0x000003fc) << 14) | \
                     (((val) & 0x0003fc00) >> 2) | \
                     (((val) & 0x03fc0000) >> 18); \
	} while(0);

#define MALI_TD_SET_MIPMAP_ADDRESS_5(dest, val) do { \
		(dest)[11] = ((dest)[11] & 0x000000fc) | (((val) & 0x000000ff) << 24) | \
                     (((val) & 0x0000ff00) << 8) | \
                     (((val) & 0x00ff0000) >> 8) | \
                     (((val) & 0x03000000) >> 24); \
	} while(0);

#define MALI_TD_SET_MIPMAP_ADDRESS_6(dest, val) do { \
		(dest)[11] = ((dest)[11] & 0xffffff03) | (((val) & 0x0000003f) << 2); \
		(dest)[12] = ((dest)[12] & 0xfff00000) | ((((val) >> 6) & 0x000000ff) << 24) | \
                     ((((val) >> 6) & 0x0000ff00) << 8) | \
                     ((((val) >> 6) & 0x000f0000) >> 8);  \
	} while(0);
	
#define MALI_TD_SET_MIPMAP_ADDRESS_7( dest, val ) do { \
		(dest)[12] = ((dest)[12] & 0xffff0f00) | (((val) & 0x0000000f) << 12) | \
                     (((val) & 0x00000ff0) >> 4); \
		(dest)[13] = ((dest)[13] & 0x00c0ffff) | ((((val) >> 12) & 0x000000ff) << 24) | \
                     ((((val) >> 12) & 0x00003f00) << 8); \
	} while(0);


#define MALI_TD_SET_MIPMAP_ADDRESS_8(dest, val) do { \
		(dest)[13] = ((dest)[13] & 0xff3f0000) | (((val) & 0x00000003) << 22) | \
                     (((val) & 0x000003fc) << 6) | \
                     (((val) & 0x0003fc00) >> 10); \
		(dest)[14] = ((dest)[14] & 0x00ffffff) | (((val) >> 18) << 24); \
	} while(0);

#define MALI_TD_SET_MIPMAP_ADDRESS_9( dest, val ) do { \
		(dest)[14] = ((dest)[14] & 0xff000000) | (((val) & 0x000000ff) << 16) | \
                     (((val) & 0x0000ff00)) | \
                     (((val) & 0x00ff0000) >> 16); \
		(dest)[15] = ((dest)[15] & 0xfcffffff) | (((val) & 0x03000000)); \
	} while(0);

#define MALI_TD_SET_MIPMAP_ADDRESS_10(dest, val) do { \
		(dest)[15] = ((dest)[15] & 0x030000f0) | (((val) & 0x0000003f) << 26) | \
                     (((val) & 0x00003fc0) << 10) | \
                     (((val) & 0x003fc000) >> 6) | \
                     (((val) & 0x03c00000) >> 22); \
	} while(0);


/** MALI200 doesn't support texture stride for linear textures
 *  Texture stride will this only be set when target platform is MALI400
 */
#if defined(USING_MALI400) || defined(USING_MALI450)

#define MALI_TD_SET_TEXTURE_TOGGLE_STRIDE(dest, val) do { \
		(dest)[2] = ((dest)[2] & 0xfffeffff) | ((val) << 16); \
	} while( 0 );
#define MALI_TD_SET_TEXTURE_STRIDE(dest, val) do { \
		(dest)[0] = ((dest)[0] & 0xffff0000) | (((val) & 0x000000ff) << 8) | \
					(((val) & 0x0000ff00) >> 8); \
	} while( 0 );

#endif





#define MALI_TD_GET_TEXEL_FORMAT(dest) \
	( \
		(((dest)[0] & 0x3f000000) >> 24) \
	)

#define MALI_TD_GET_TEXEL_ORDER_INVERT(dest) \
	( \
		(((dest)[0] & 0x40000000) >> 30) \
	)

#define MALI_TD_GET_TEXEL_RED_BLUE_SWAP(dest) \
	( \
		(((dest)[0] & 0x80000000) >> 31) \
	)

#define MALI_TD_GET_TEXEL_BIAS_SELECT(dest) \
	( \
		(((dest)[0] & 0x00030000) >> 16) \
	)

#define MALI_TD_GET_TEXEL_TOGGLE_MSB(dest) \
	( \
		(((dest)[0] & 0x00040000) >> 18) \
	)

#define MALI_TD_GET_PALETTE_FORMAT(dest) \
	( \
		(((dest)[0] & 0x00180000) >> 19) \
	)

#define MALI_TD_GET_PALETTE_ADDRESS(dest) \
	( \
		(((dest)[0] & 0x00e00000) >> 21) | \
		(((dest)[0] & 0x0000ff00) >> 5) | \
		(((dest)[0] & 0x000000ff) << 11) | \
        (((dest)[1] & 0x7f000000) >> 5) \
	)

#define MALI_TD_GET_TEXTURE_FORMAT(dest) \
	( \
		(((dest)[1] & 0x80000000) >> 31) | \
        (((dest)[1] & 0x00030000) >> 15) \
	)

#define MALI_TD_GET_TEXTURE_DIMENSIONALITY(dest) \
	( \
		(((dest)[1] & 0x000c0000) >> 18) \
	)

#define MALI_TD_GET_LAMBDA_LOW_CLAMP(dest) \
	( \
		(((dest)[1] & 0x00f00000) >> 20) | \
        (((dest)[1] & 0x00000f00) >> 4) \
	)

#define MALI_TD_GET_LAMBDA_HIGH_CLAMP(dest) \
	( \
		(((dest)[1] & 0x0000f000) >> 12) | \
        (((dest)[1] & 0x0000000f) << 4) \
	)

#define MALI_TD_GET_LAMBDA_BIAS(dest) \
	( \
		(((dest)[1] & 0x000000f0) >> 4) | \
        (((dest)[2] & 0x1f000000) >> 20) \
	)

#define MALI_TD_GET_ANISOTROPY_LOG2(dest) \
	( \
		(((dest)[2] & 0xe0000000) >> 29) \
	)

#define MALI_TD_GET_MIPMAPPING_MODE(dest) \
	( \
		(((dest)[2] & 0x00060000) >> 17) \
	)

#define MALI_TD_GET_POINT_SAMPLE_MINIFY(dest) \
	( \
		(((dest)[2] & 0x00080000) >> 19) \
	)

#define MALI_TD_GET_POINT_SAMPLE_MAGNIFY(dest) \
	( \
		(((dest)[2] & 0x00100000) >> 20) \
	)

#define MALI_TD_GET_WRAP_MODE_S(dest) \
	( \
		(((dest)[2] & 0x00e00000) >> 21) \
	)

#define MALI_TD_GET_WRAP_MODE_T(dest) \
	( \
		(((dest)[2] & 0x00000700) >> 8) \
	)
    
#define MALI_TD_GET_WRAP_MODE_R(dest) \
	( \
		(((dest)[2] & 0x00003800) >> 11) \
	)

#define MALI_TD_GET_TEXTURE_DIMENSION_S(dest) \
	( \
		(((dest)[2] & 0x0000c000) >> 14) | \
		(((dest)[2] & 0x000000ff) << 2) | \
		(((dest)[3] & 0x07000000) >> 14) \
	)

#define MALI_TD_GET_TEXTURE_DIMENSION_T(dest) \
	( \
		(((dest)[3] & 0xf8000000) >> 27) | \
		(((dest)[3] & 0x00ff0000) >> 11) \
	)

#define MALI_TD_GET_TEXTURE_DIMENSION_R(dest) \
	( \
		(((dest)[3] & 0x0000ff00) >> 8) | \
		(((dest)[3] & 0x0000001f) << 8) \
	)

#define MALI_TD_GET_BORDER_COLOR_RED(dest) \
	( \
		(((dest)[3] & 0x000000e0) >> 5) | \
		(((dest)[4] & 0xff000000) >> 21) | \
		(((dest)[4] & 0x001f0000) >> 5) \
	)

#define MALI_TD_GET_BORDER_COLOR_GREEN(dest) \
	( \
		(((dest)[4] & 0x00e00000) >> 21) | \
		(((dest)[4] & 0x0000ff00) >> 5) | \
		(((dest)[4] & 0x0000001f) << 11) \
	)

#define MALI_TD_GET_BORDER_COLOR_BLUE(dest) \
	( \
		(((dest)[4] & 0x000000e0) >> 5) | \
		(((dest)[5] & 0xff000000) >> 21) | \
		(((dest)[5] & 0x001f0000) >> 5) \
	)

#define MALI_TD_GET_BORDER_COLOR_ALPHA(dest) \
	( \
		(((dest)[5] & 0x00e00000) >> 21) | \
		(((dest)[5] & 0x0000ff00) >> 5) | \
		(((dest)[5] & 0x0000001f) << 11) \
	)

#define MALI_TD_GET_SHADOW_MAPPING_AMBIENT(dest) \
	( \
		(((dest)[5] & 0x000000e0) >> 5) | \
		(((dest)[6] & 0xff000000) >> 21) | \
		(((dest)[6] & 0x001f0000) >> 5) \
	)

#define MALI_TD_GET_TEXTURE_ADDRESSING_MODE(dest) \
	( \
		(((dest)[6] & 0x00600000) >> 21) \
    )

#define MALI_TD_GET_BORDER_TEXEL_ENABLE(dest) \
	( \
		(((dest)[6] & 0x00800000) >> 23) \
    )

#define MALI_TD_GET_SHADOW_MAPPING_CMP_FUNC(dest) \
	( \
		(((dest)[6] & 0x00000700) >> 8) \
    )

#define MALI_TD_GET_SHADOW_MAPPING_CPY_RGB(dest) \
	( \
		(((dest)[6] & 0x00000800) >> 11) \
    )

#define MALI_TD_GET_SHADOW_MAPPING_CPY_ALPHA(dest) \
	( \
		(((dest)[6] & 0x00001000) >> 12) \
    )

#define MALI_TD_GET_TEXTURE_STACKING_ENABLE(dest) \
	( \
		(((dest)[6] & 0x00002000) >> 13) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_0(dest) \
	( \
		(((dest)[6] & 0x000000c0) >> 6) | \
		(((dest)[7] & 0xff000000) >> 22) | \
		(((dest)[7] & 0x00ff0000) >> 6) | \
		(((dest)[7] & 0x0000ff00) << 10) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_1(dest) \
	( \
		(((dest)[7] & 0x000000ff)) | \
		(((dest)[8] & 0xff000000) >> 16) | \
		(((dest)[8] & 0x00ff0000)) | \
		(((dest)[8] & 0x00000300) << 16) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_2(dest) \
	( \
		(((dest)[8] & 0x0000fc00) >> 10) | \
		(((dest)[8] & 0x000000ff) << 6) | \
		(((dest)[9] & 0xff000000) >> 10) | \
		(((dest)[9] & 0x000f0000) << 6) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_3(dest) \
	( \
		(((dest)[9] & 0x00f00000) >> 20) | \
		(((dest)[9] & 0x0000ff00) >> 4) | \
		(((dest)[9] & 0x000000ff) << 12) | \
		(((dest)[10] & 0x3f000000) >> 4) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_4(dest) \
	( \
		(((dest)[10] & 0xc0000000) >> 30) | \
		(((dest)[10] & 0x00ff0000) >> 14) | \
		(((dest)[10] & 0x0000ff00) << 2) | \
		(((dest)[10] & 0x000000ff) << 18) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_5(dest) \
    ( \
        (((dest)[11] & 0xff000000) >> 24) | \
        (((dest)[11] & 0x00ff0000) >> 8) | \
        (((dest)[11] & 0x0000ff00) << 8) | \
        (((dest)[11] & 0x00000003) << 24) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_6(dest) \
    ( \
        (((dest)[11] & 0xff000000) >> 24) | \
        (((dest)[11] & 0x00ff0000) >> 8) | \
        (((dest)[11] & 0x0000ff00) << 8) | \
        (((dest)[11] & 0x00000003) << 24) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_7(dest) \
    ( \
        (((dest)[12] & 0x0000f000) >> 12) | \
        (((dest)[12] & 0x000000ff) << 4) | \
        (((dest)[13] & 0xff000000) >> 12) | \
        (((dest)[13] & 0x003f0000) << 4) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_8(dest) \
    ( \
        (((dest)[13] & 0x00c00000) >> 22) | \
        (((dest)[13] & 0x0000ff00) >> 6) | \
        (((dest)[13] & 0x000000ff) << 10) | \
        (((dest)[14] & 0xff000000) >> 6) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_9(dest) \
    ( \
        (((dest)[14] & 0x00ff0000) >> 16) | \
        (((dest)[14] & 0x0000ff00)) | \
        (((dest)[14] & 0x000000ff) << 16) | \
        (((dest)[15] & 0x03000000)) \
    )

#define MALI_TD_GET_MIPMAP_ADDRESS_10(dest) \
    ( \
        (((dest)[15] & 0xfc000000) >> 26) | \
        (((dest)[15] & 0x00ff0000) >> 10) | \
        (((dest)[15] & 0x0000ff00) << 6) | \
        (((dest)[15] & 0x0000000f) << 22) \
    )

#define MALI_TD_GET_TEXTURE_TOGGLE_STRIDE(dest) \
	( \
		(((dest)[2] & 0x00010000) >> 16) \
	)

#define MALI_TD_GET_TEXTURE_STRIDE(dest) \
	( \
		(((dest)[0] & 0x0000ff00) >> 8) | \
		(((dest)[0] & 0x000000ff) << 8) \
	)

#else

/**
 * @brief
These macros have been generated from the functions that are defined at the bottom of this file
 *
 */
#define MALI_TD_SET_TEXEL_FORMAT( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 5 >> 5 ) == ( 0 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 0, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffffffc0 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 0 ] = ( (dest)[ 0 ] & 0xffffffc0 ) | ( (val) << 0 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 5, 0 ) == (val), ( "Value set in MALI_TD_SET_TEXEL_FORMAT is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXEL_ORDER_INVERT( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 6 >> 5 ) == ( 6 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 0, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 0 ] = ( (dest)[ 0 ] & 0xffffffbf ) | ( (val) << 6 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 6, 6 ) == (val), ( "Value set in MALI_TD_SET_TEXEL_ORDER_INVERT is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXEL_RED_BLUE_SWAP( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 7 >> 5 ) == ( 7 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 0, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 0 ] = ( (dest)[ 0 ] & 0xffffff7f ) | ( (val) << 7 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 7, 7 ) == (val), ( "Value set in MALI_TD_SET_TEXEL_RED_BLUE_SWAP is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXEL_BIAS_SELECT( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 9 >> 5 ) == ( 8 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 0, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffc & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 0 ] = ( (dest)[ 0 ] & 0xfffffcff ) | ( (val) << 8 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 9, 8 ) == (val), ( "Value set in MALI_TD_SET_TEXEL_BIAS_SELECT is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXEL_TOGGLE_MSB( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 10 >> 5 ) == ( 10 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 0, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 0 ] = ( (dest)[ 0 ] & 0xfffffbff ) | ( (val) << 10 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 10, 10 ) == (val), ( "Value set in MALI_TD_SET_TEXEL_TOGGLE_MSB is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_PALETTE_FORMAT( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 12 >> 5 ) == ( 11 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 0, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffc & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 0 ] = ( (dest)[ 0 ] & 0xffffe7ff ) | ( (val) << 11 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 12, 11 ) == (val), ( "Value set in MALI_TD_SET_PALETTE_FORMAT is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_PALETTE_ADDRESS( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 38 >> 5 ) - 1 ) == ( 13 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 1, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 0, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 0 ] = ( (dest)[ 0 ] & 0x00001fff ) | ( ( (val) & 0x0007ffff ) << 13 ); \
		(dest)[ 1 ] = ( (dest)[ 1 ] & 0xffffff80 ) | ( (val) >> 19 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 38, 13 ) == (val), ( "Value set in MALI_TD_SET_PALETTE_ADDRESS is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXTURE_FORMAT( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 41 >> 5 ) == ( 39 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 1, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffff8 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 1 ] = ( (dest)[ 1 ] & 0xfffffc7f ) | ( (val) << 7 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 41, 39 ) == (val), ( "Value set in MALI_TD_SET_TEXTURE_FORMAT is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXTURE_DIMENSIONALITY( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 43 >> 5 ) == ( 42 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 1, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffc & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 1 ] = ( (dest)[ 1 ] & 0xfffff3ff ) | ( (val) << 10 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 43, 42 ) == (val), ( "Value set in MALI_TD_SET_TEXTURE_DIMENSIONALITY is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_LAMBDA_LOW_CLAMP( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 51 >> 5 ) == ( 44 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 1, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffffff00 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 1 ] = ( (dest)[ 1 ] & 0xfff00fff ) | ( (val) << 12 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 51, 44 ) == (val), ( "Value set in MALI_TD_SET_LAMBDA_LOW_CLAMP is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_LAMBDA_HIGH_CLAMP( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 59 >> 5 ) == ( 52 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 1, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffffff00 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 1 ] = ( (dest)[ 1 ] & 0xf00fffff ) | ( (val) << 20 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 59, 52 ) == (val), ( "Value set in MALI_TD_SET_LAMBDA_HIGH_CLAMP is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_LAMBDA_BIAS( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 68 >> 5 ) - 1 ) == ( 60 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 1, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffe00 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 1 ] = ( (dest)[ 1 ] & 0x0fffffff ) | ( ( (val) & 0x0000000f ) << 28 ); \
		(dest)[ 2 ] = ( (dest)[ 2 ] & 0xffffffe0 ) | ( (val) >> 4 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 68, 60 ) == (val), ( "Value set in MALI_TD_SET_LAMBDA_BIAS is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_ANISOTROPY_LOG2( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 71 >> 5 ) == ( 69 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffff8 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 2 ] = ( (dest)[ 2 ] & 0xffffff1f ) | ( (val) << 5 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 71, 69 ) == (val), ( "Value set in MALI_TD_SET_ANISOTROPY_LOG2 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAPPING_MODE( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 74 >> 5 ) == ( 73 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffc & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 2 ] = ( (dest)[ 2 ] & 0xfffff9ff ) | ( (val) << 9 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 74, 73 ) == (val), ( "Value set in MALI_TD_SET_MIPMAPPING_MODE is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_POINT_SAMPLE_MINIFY( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 75 >> 5 ) == ( 75 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 2 ] = ( (dest)[ 2 ] & 0xfffff7ff ) | ( (val) << 11 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 75, 75 ) == (val), ( "Value set in MALI_TD_SET_POINT_SAMPLE_MINIFY is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_POINT_SAMPLE_MAGNIFY( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 76 >> 5 ) == ( 76 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 2 ] = ( (dest)[ 2 ] & 0xffffefff ) | ( (val) << 12 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 76, 76 ) == (val), ( "Value set in MALI_TD_SET_POINT_SAMPLE_MAGNIFY is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_WRAP_MODE_S( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 79 >> 5 ) == ( 77 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffff8 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 2 ] = ( (dest)[ 2 ] & 0xffff1fff ) | ( (val) << 13 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 79, 77 ) == (val), ( "Value set in MALI_TD_SET_WRAP_MODE_S is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_WRAP_MODE_T( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 82 >> 5 ) == ( 80 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffff8 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 2 ] = ( (dest)[ 2 ] & 0xfff8ffff ) | ( (val) << 16 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 82, 80 ) == (val), ( "Value set in MALI_TD_SET_WRAP_MODE_T is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_WRAP_MODE_R( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 85 >> 5 ) == ( 83 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffff8 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 2 ] = ( (dest)[ 2 ] & 0xffc7ffff ) | ( (val) << 19 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 85, 83 ) == (val), ( "Value set in MALI_TD_SET_WRAP_MODE_R is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXTURE_DIMENSION_S( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 98 >> 5 ) - 1 ) == ( 86 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 3, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffffe000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 2 ] = ( (dest)[ 2 ] & 0x003fffff ) | ( ( (val) & 0x000003ff ) << 22 ); \
		(dest)[ 3 ] = ( (dest)[ 3 ] & 0xfffffff8 ) | ( (val) >> 10 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 98, 86 ) == (val), ( "Value set in MALI_TD_SET_TEXTURE_DIMENSION_S is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXTURE_DIMENSION_T( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 111 >> 5 ) == ( 99 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 3, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffffe000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 3 ] = ( (dest)[ 3 ] & 0xffff0007 ) | ( (val) << 3 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 111, 99 ) == (val), ( "Value set in MALI_TD_SET_TEXTURE_DIMENSION_T is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXTURE_DIMENSION_R( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 124 >> 5 ) == ( 112 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 3, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffffe000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 3 ] = ( (dest)[ 3 ] & 0xe000ffff ) | ( (val) << 16 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 124, 112 ) == (val), ( "Value set in MALI_TD_SET_TEXTURE_DIMENSION_R is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_BORDER_COLOR_RED( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 140 >> 5 ) - 1 ) == ( 125 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 4, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 3, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffff0000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 3 ] = ( (dest)[ 3 ] & 0x1fffffff ) | ( ( (val) & 0x00000007 ) << 29 ); \
		(dest)[ 4 ] = ( (dest)[ 4 ] & 0xffffe000 ) | ( (val) >> 3 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 140, 125 ) == (val), ( "Value set in MALI_TD_SET_BORDER_COLOR_RED is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_BORDER_COLOR_GREEN( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 156 >> 5 ) == ( 141 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 4, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffff0000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 4 ] = ( (dest)[ 4 ] & 0xe0001fff ) | ( (val) << 13 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 156, 141 ) == (val), ( "Value set in MALI_TD_SET_BORDER_COLOR_GREEN is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_BORDER_COLOR_BLUE( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 172 >> 5 ) - 1 ) == ( 157 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 5, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 4, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffff0000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 4 ] = ( (dest)[ 4 ] & 0x1fffffff ) | ( ( (val) & 0x00000007 ) << 29 ); \
		(dest)[ 5 ] = ( (dest)[ 5 ] & 0xffffe000 ) | ( (val) >> 3 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 172, 157 ) == (val), ( "Value set in MALI_TD_SET_BORDER_COLOR_BLUE is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_BORDER_COLOR_ALPHA( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 188 >> 5 ) == ( 173 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 5, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffff0000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 5 ] = ( (dest)[ 5 ] & 0xe0001fff ) | ( (val) << 13 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 188, 173 ) == (val), ( "Value set in MALI_TD_SET_BORDER_COLOR_ALPHA is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_SHADOW_MAPPING_AMBIENT( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 204 >> 5 ) - 1 ) == ( 189 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 6, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 5, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xffff0000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 5 ] = ( (dest)[ 5 ] & 0x1fffffff ) | ( ( (val) & 0x00000007 ) << 29 ); \
		(dest)[ 6 ] = ( (dest)[ 6 ] & 0xffffe000 ) | ( (val) >> 3 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 204, 189 ) == (val), ( "Value set in MALI_TD_SET_SHADOW_MAPPING_AMBIENT is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXTURE_ADDRESSING_MODE( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 206 >> 5 ) == ( 205 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 6, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffc & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 6 ] = ( (dest)[ 6 ] & 0xffff9fff ) | ( (val) << 13 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 206, 205 ) == (val), ( "Value set in MALI_TD_SET_TEXTURE_ADDRESSING_MODE is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_BORDER_TEXEL_ENABLE( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 207 >> 5 ) == ( 207 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 6, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 6 ] = ( (dest)[ 6 ] & 0xffff7fff ) | ( (val) << 15 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 207, 207 ) == (val), ( "Value set in MALI_TD_SET_BORDER_TEXEL_ENABLE is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_SHADOW_MAPPING_CMP_FUNC( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 210 >> 5 ) == ( 208 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 6, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffff8 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 6 ] = ( (dest)[ 6 ] & 0xfff8ffff ) | ( (val) << 16 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 210, 208 ) == (val), ( "Value set in MALI_TD_SET_SHADOW_MAPPING_CMP_FUNC is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_SHADOW_MAPPING_CPY_RGB( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 211 >> 5 ) == ( 211 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 6, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 6 ] = ( (dest)[ 6 ] & 0xfff7ffff ) | ( (val) << 19 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 211, 211 ) == (val), ( "Value set in MALI_TD_SET_SHADOW_MAPPING_CPY_RGB is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_SHADOW_MAPPING_CPY_ALPHA( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 212 >> 5 ) == ( 212 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 6, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 6 ] = ( (dest)[ 6 ] & 0xffefffff ) | ( (val) << 20 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 212, 212 ) == (val), ( "Value set in MALI_TD_SET_SHADOW_MAPPING_CPY_ALPHA is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_TEXTURE_STACKING_ENABLE( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 213 >> 5 ) == ( 213 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 6, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 6 ] = ( (dest)[ 6 ] & 0xffdfffff ) | ( (val) << 21 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 213, 213 ) == (val), ( "Value set in MALI_TD_SET_TEXTURE_STACKING_ENABLE is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_0( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 247 >> 5 ) - 1 ) == ( 222 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 7, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 6, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 6 ] = ( (dest)[ 6 ] & 0x3fffffff ) | ( ( (val) & 0x00000003 ) << 30 ); \
		(dest)[ 7 ] = ( (dest)[ 7 ] & 0xff000000 ) | ( (val) >> 2 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 247, 222 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_0 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_1( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 273 >> 5 ) - 1 ) == ( 248 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 8, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 7, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 7 ] = ( (dest)[ 7 ] & 0x00ffffff ) | ( ( (val) & 0x000000ff ) << 24 ); \
		(dest)[ 8 ] = ( (dest)[ 8 ] & 0xfffc0000 ) | ( (val) >> 8 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 273, 248 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_1 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_2( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 299 >> 5 ) - 1 ) == ( 274 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 9, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 8, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 8 ] = ( (dest)[ 8 ] & 0x0003ffff ) | ( ( (val) & 0x00003fff ) << 18 ); \
		(dest)[ 9 ] = ( (dest)[ 9 ] & 0xfffff000 ) | ( (val) >> 14 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 299, 274 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_2 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_3( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 325 >> 5 ) - 1 ) == ( 300 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 10, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 9, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 9 ] = ( (dest)[ 9 ] & 0x00000fff ) | ( ( (val) & 0x000fffff ) << 12 ); \
		(dest)[ 10 ] = ( (dest)[ 10 ] & 0xffffffc0 ) | ( (val) >> 20 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 325, 300 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_3 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_4( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 351 >> 5 ) == ( 326 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 10, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 10 ] = ( (dest)[ 10 ] & 0x0000003f ) | ( (val) << 6 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 351, 326 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_4 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_5( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 377 >> 5 ) == ( 352 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 11, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 11 ] = ( (dest)[ 11 ] & 0xfc000000 ) | ( (val) << 0 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 377, 352 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_5 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_6( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 403 >> 5 ) - 1 ) == ( 378 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 12, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 11, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 11 ] = ( (dest)[ 11 ] & 0x03ffffff ) | ( ( (val) & 0x0000003f ) << 26 ); \
		(dest)[ 12 ] = ( (dest)[ 12 ] & 0xfff00000 ) | ( (val) >> 6 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 403, 378 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_6 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_7( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 429 >> 5 ) - 1 ) == ( 404 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 13, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 12, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 12 ] = ( (dest)[ 12 ] & 0x000fffff ) | ( ( (val) & 0x00000fff ) << 20 ); \
		(dest)[ 13 ] = ( (dest)[ 13 ] & 0xffffc000 ) | ( (val) >> 12 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 429, 404 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_7 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_8( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 455 >> 5 ) - 1 ) == ( 430 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 14, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 13, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 13 ] = ( (dest)[ 13 ] & 0x00003fff ) | ( ( (val) & 0x0003ffff ) << 14 ); \
		(dest)[ 14 ] = ( (dest)[ 14 ] & 0xffffff00 ) | ( (val) >> 18 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 455, 430 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_8 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_9( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( ( 481 >> 5 ) - 1 ) == ( 456 >> 5 ), ("Value is split into two words that are not in sequence" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 15, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT_RANGE( 14, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 14 ] = ( (dest)[ 14 ] & 0x000000ff ) | ( ( (val) & 0x00ffffff ) << 8 ); \
		(dest)[ 15 ] = ( (dest)[ 15 ] & 0xfffffffc ) | ( (val) >> 24 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 481, 456 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_9 is different from what was retrieved\n" ) ); \
	} while( 0 );
#define MALI_TD_SET_MIPMAP_ADDRESS_10( dest, val ) do { \
		MALI_DEBUG_ASSERT( ( 507 >> 5 ) == ( 482 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 15, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == ( 0xfc000000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[ 15 ] = ( (dest)[ 15 ] & 0xf0000003 ) | ( (val) << 2 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 507, 482 ) == (val), ( "Value set in MALI_TD_SET_MIPMAP_ADDRESS_10 is different from what was retrieved\n" ) ); \
	} while( 0 );


/** MALI200 doesn't support texture stride for linear textures
 *  Texture stride will this only be set when target platform is MALI400
 */
#if defined(USING_MALI400) || defined(USING_MALI450)

#define MALI_TD_SET_TEXTURE_TOGGLE_STRIDE(dest, val) do { \
		MALI_DEBUG_ASSERT( ( 72 >> 5 ) == ( 72 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 2, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == (0xfffffffe & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[2] = ( (dest)[ 2 ] & ~0x00000100 ) | ( ( val ) << 8 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 72, 72 ) == (val), ( "Valule set in MALI_TD_SET_TEXTURE_TOGGLE_PITCH is different from what was retrieved\n" ) ); \
	} while( 0 );

#define MALI_TD_SET_TEXTURE_STRIDE(dest, val) do { \
		MALI_DEBUG_ASSERT( ( 31 >> 5 ) == ( 16 >> 5 ), ("Value is split into two words, should use split into two functions" ) ); \
		MALI_DEBUG_ASSERT_RANGE( 0, 0, M200_TD_SIZE - 1 ); \
		MALI_DEBUG_ASSERT( 0 == (0xffff0000 & (val) ), ("Bitfield given is too large for the field") ); \
		(dest)[0] = ( (dest)[ 0 ] & 0x0000ffff ) | ( ( val ) << 16 ); \
		MALI_DEBUG_ASSERT( _m200_td_get( (dest), 31, 16 ) == (val), ( "Value set in MALI_TD_SET_TEXTURE_PITCH is different from what was retrieved\n" ) ); \
	} while( 0 );

#endif


#define MALI_TD_GET_TEXEL_FORMAT( dest ) _m200_td_get( dest, 5, 0 )
#define MALI_TD_GET_TEXEL_ORDER_INVERT( dest ) _m200_td_get( dest, 6, 6 )
#define MALI_TD_GET_TEXEL_RED_BLUE_SWAP( dest ) _m200_td_get( dest, 7, 7 )
#define MALI_TD_GET_TEXEL_BIAS_SELECT( dest ) _m200_td_get( dest, 9, 8 )
#define MALI_TD_GET_TEXEL_TOGGLE_MSB( dest ) _m200_td_get( dest, 10, 10 )
#define MALI_TD_GET_PALETTE_FORMAT( dest ) _m200_td_get( dest, 12, 11 )
#define MALI_TD_GET_TEXTURE_STRIDE ( dest ) _m200_td_get( dest, 31, 16 )
#define MALI_TD_GET_PALETTE_ADDRESS( dest ) _m200_td_get( dest, 38, 13 )
#define MALI_TD_GET_TEXTURE_FORMAT( dest ) _m200_td_get( dest, 41, 39 )
#define MALI_TD_GET_TEXTURE_DIMENSIONALITY( dest ) _m200_td_get( dest, 43, 42 )
#define MALI_TD_GET_LAMBDA_LOW_CLAMP( dest ) _m200_td_get( dest, 51, 44 )
#define MALI_TD_GET_LAMBDA_HIGH_CLAMP( dest ) _m200_td_get( dest, 59, 52 )
#define MALI_TD_GET_LAMBDA_BIAS( dest ) _m200_td_get( dest, 68, 60 )
#define MALI_TD_GET_ANISOTROPY_LOG2( dest ) _m200_td_get( dest, 71, 69 )
#define MALI_TD_GET_TEXTURE_TOGGLE_STRIDE ( dest ) _m200_td_get( dest, 72, 72 )
#define MALI_TD_GET_MIPMAPPING_MODE( dest ) _m200_td_get( dest, 74, 73 )
#define MALI_TD_GET_POINT_SAMPLE_MINIFY( dest ) _m200_td_get( dest, 75, 75 )
#define MALI_TD_GET_POINT_SAMPLE_MAGNIFY( dest ) _m200_td_get( dest, 76, 76 )
#define MALI_TD_GET_WRAP_MODE_S( dest ) _m200_td_get( dest, 79, 77 )
#define MALI_TD_GET_WRAP_MODE_T( dest ) _m200_td_get( dest, 82, 80 )
#define MALI_TD_GET_WRAP_MODE_R( dest ) _m200_td_get( dest, 85, 83 )
#define MALI_TD_GET_TEXTURE_DIMENSION_S( dest ) _m200_td_get( dest, 98, 86 )
#define MALI_TD_GET_TEXTURE_DIMENSION_T( dest ) _m200_td_get( dest, 111, 99 )
#define MALI_TD_GET_TEXTURE_DIMENSION_R( dest ) _m200_td_get( dest, 124, 112 )
#define MALI_TD_GET_BORDER_COLOR_RED( dest ) _m200_td_get( dest, 140, 125 )
#define MALI_TD_GET_BORDER_COLOR_GREEN( dest ) _m200_td_get( dest, 156, 141 )
#define MALI_TD_GET_BORDER_COLOR_BLUE( dest ) _m200_td_get( dest, 172, 157 )
#define MALI_TD_GET_BORDER_COLOR_ALPHA( dest ) _m200_td_get( dest, 188, 173 )
#define MALI_TD_GET_SHADOW_MAPPING_AMBIENT( dest ) _m200_td_get( dest, 204, 189 )
#define MALI_TD_GET_TEXTURE_ADDRESSING_MODE( dest ) _m200_td_get( dest, 206, 205 )
#define MALI_TD_GET_BORDER_TEXEL_ENABLE( dest ) _m200_td_get( dest, 207, 207 )
#define MALI_TD_GET_SHADOW_MAPPING_CMP_FUNC( dest ) _m200_td_get( dest, 210, 208 )
#define MALI_TD_GET_SHADOW_MAPPING_CPY_RGB( dest ) _m200_td_get( dest, 211, 211 )
#define MALI_TD_GET_SHADOW_MAPPING_CPY_ALPHA( dest ) _m200_td_get( dest, 212, 212 )
#define MALI_TD_GET_TEXTURE_STACKING_ENABLE( dest ) _m200_td_get( dest, 213, 213 )
#define MALI_TD_GET_MIPMAP_ADDRESS_0( dest ) _m200_td_get( dest, 247, 222 )
#define MALI_TD_GET_MIPMAP_ADDRESS_1( dest ) _m200_td_get( dest, 273, 248 )
#define MALI_TD_GET_MIPMAP_ADDRESS_2( dest ) _m200_td_get( dest, 299, 274 )
#define MALI_TD_GET_MIPMAP_ADDRESS_3( dest ) _m200_td_get( dest, 325, 300 )
#define MALI_TD_GET_MIPMAP_ADDRESS_4( dest ) _m200_td_get( dest, 351, 326 )
#define MALI_TD_GET_MIPMAP_ADDRESS_5( dest ) _m200_td_get( dest, 377, 352 )
#define MALI_TD_GET_MIPMAP_ADDRESS_6( dest ) _m200_td_get( dest, 403, 378 )
#define MALI_TD_GET_MIPMAP_ADDRESS_7( dest ) _m200_td_get( dest, 429, 404 )
#define MALI_TD_GET_MIPMAP_ADDRESS_8( dest ) _m200_td_get( dest, 455, 430 )
#define MALI_TD_GET_MIPMAP_ADDRESS_9( dest ) _m200_td_get( dest, 481, 456 )
#define MALI_TD_GET_MIPMAP_ADDRESS_10( dest ) _m200_td_get( dest, 507, 482 )

#endif

/** Mali 200 texture descriptor data block */
typedef u32 m200_td[M200_TD_SIZE];

/** If all compare enums are the same (like in 110, we can just create a compare enum instead of this */
typedef enum m200_shadow_mapping_compare_func
{
	M200_SHADOW_MAPPING_COMPARE_FUNC_ALWAYS_FAIL = 0,
	M200_SHADOW_MAPPING_COMPARE_FUNC_LESS_THAN = 1,
	M200_SHADOW_MAPPING_COMPARE_FUNC_EQUAL = 2,
	M200_SHADOW_MAPPING_COMPARE_FUNC_LESS_THAN_OR_EQUAL = 3,
	M200_SHADOW_MAPPING_COMPARE_FUNC_GREATER_THAN = 4,
	M200_SHADOW_MAPPING_COMPARE_FUNC_NOT_EQUAL = 5,
	M200_SHADOW_MAPPING_COMPARE_FUNC_GREATER_THAN_OR_EQUAL = 6,
	M200_SHADOW_MAPPING_COMPARE_FUNC_ALWAYS_SUCCEED = 7
} m200_shadow_mapping_compare_function;

/** */
typedef enum m200_texture_format
{
	M200_TEXTURE_FORMAT_NORMALIZED = 0,
	M200_TEXTURE_FORMAT_NON_NORMALIZED = 1,
	M200_TEXTURE_FORMAT_NORMALIZED_SHADOW_MAP = 2,
	M200_TEXTURE_FORMAT_NON_NORMALIZED_SHADOW_MAP = 3,
	M200_TEXTURE_FORMAT_CUBE_MAP = 4
	                               /*Perlin noise not implemented
	                               M200_TEXTURE_FORMAT_PERLIN_NOISE = 5,
	                               enums 6-7 reserved for future expansion */
} m200_texture_format;

/** */
typedef enum m200_texel_bias
{
	M200_TEXEL_BIAS_NONE = 0,
	M200_TEXEL_BIAS_X_MINUS_HALF = 1,
	M200_TEXEL_BIAS_X_MINUS_HALF_X2 = 2,
	M200_TEXEL_BIAS_ONE_MINUS_X = 3
} m200_texel_bias;

/** */
typedef enum m200_palette_format
{
	M200_PALETTE_FORMAT_RGB_565 = 0,
	M200_PALETTE_FORMAT_ARGB_1555 = 1,
	M200_PALETTE_FORMAT_ARGB_4444 = 2
	                                /* Not implemented
	                                M200_PALETTE_FORMAT_ARGB_8888 = 3, */
} m200_palette_format;

/** */
typedef enum m200_texture_addressing_mode
{
	M200_TEXTURE_ADDRESSING_MODE_LINEAR = 0,
	M200_TEXTURE_ADDRESSING_MODE_2D_INTERLEAVED = 1,
	M200_TEXTURE_ADDRESSING_MODE_3D_INTERLEAVED = 2,
	M200_TEXTURE_ADDRESSING_MODE_16X16_BLOCKED = 3,
	M200_TEXTURE_ADDRESSING_MODE_INVALID = 4
} m200_texture_addressing_mode;

/** */
typedef enum m200_mipmap_mode
{
	M200_MIPMAP_MODE_NEAREST = 0,
	M200_MIPMAP_MODE_DITHER = 1,
	M200_MIPMAP_MODE_PERFORMANCE_TRILINEAR = 2,
	M200_MIPMAP_MODE_QUALITY_TRILINEAR = 3
} m200_mipmap_mode;

/** */
typedef enum m200_texture_wrap_mode
{
	M200_TEXTURE_WRAP_MODE_REPEAT = 0,
	M200_TEXTURE_WRAP_MODE_CLAMP_TO_EDGE = 1,
	M200_TEXTURE_WRAP_MODE_CLAMP_TO_ZERO_ONE = 2,
	M200_TEXTURE_WRAP_MODE_CLAMP_TO_BORDER = 3,
	M200_TEXTURE_WRAP_MODE_MIRRORED_REPEAT = 4,
	M200_TEXTURE_WRAP_MODE_MIRRORED_CLAMP_TO_EDGE = 5,
	M200_TEXTURE_WRAP_MODE_MIRRORED_CLAMP_TO_MINUS_1_1 = 6,
	M200_TEXTURE_WRAP_MODE_MIRRORED_CLAMP_TO_BORDER = 7
} m200_texture_wrap_mode;

/** */
typedef enum m200_texture_dimensionality
{
	M200_TEXTURE_DIMENSIONALITY_1D = 0,
	M200_TEXTURE_DIMENSIONALITY_2D = 1,
	M200_TEXTURE_DIMENSIONALITY_3D = 2
	                                 /* **not implemented** supported for Perlin noise only
	                                 M200_TEXTURE_DIMENSIONALITY_4D = 3
	                                 */
} m200_texture_dimensionality;

/**
 * Set default values for all fields in texture descriptor.
 * Fields that are not explicitly listed below defaults to zero.
 *  texel_format = M200_TEXEL_FORMAT_xRGB_8888
 *  bias_select = M200_TEXEL_BIAS_NONE
 *  paletted_format = M200_PALETTE_FORMAT_RGB_565
 *  texture_format = M200_TEXTURE_FORMAT_NORMALIZED
 *  texture_dimensionality = M200_TEXTURE_DIMENSIONALITY_2D
 *  mipmapping_mode = M200_MIPMAP_MODE_NEAREST
 *  wrap_mode_s = M200_TEXTURE_WRAP_MODE_CLAMP_TO_EDGE
 *  wrap_mode_t = M200_TEXTURE_WRAP_MODE_CLAMP_TO_EDGE
 *  wrap_mode_r = M200_TEXTURE_WRAP_MODE_CLAMP_TO_EDGE
 *  texture_dimension_s = 1
 *  texture_dimension_t = 1
 *  texture_dimension_r = 1
 *  addressing_mode = M200_TEXTURE_ADDRESSING_MODE_LINEAR
 *  shadowmap_compare_func = M200_SHADOW_MAPPING_COMPARE_FUNC_ALWAYS_FAIL
 * @param dest
 */
MALI_IMPORT void m200_texture_descriptor_set_defaults(m200_td dest);

MALI_IMPORT u32 _m200_td_get(m200_td dest, u32 left_index, u32 right_index);

#ifdef __cplusplus
}
#endif

#endif /* __M200_TD_HEADER__ */
