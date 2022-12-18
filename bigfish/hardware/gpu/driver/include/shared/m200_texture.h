/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2010, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


#ifndef _M200_TEXTURE_H_
#define _M200_TEXTURE_H_


#include "m200_td.h"


#define TEX2D_MIPMAP_SIZE_ABOVE_LEVEL9 1024

/**
 * convert a texture from one addressing mode to another.
 * @param dest A pointer to the destination texture.
 * @param dest_mode The addressing mode of the destination.
 * @param src A pointer to the source texture.
 * @param src_mode The addressing mode of the source texture.
 * @param width The width of the texture.
 * @param height The height of the texture.
 * @param depth The depth of the texture.
 * @param format The texture format
 * @param dst_pitch The pitch of the destination texture.
 * @param src_pitch The pitch of the source texture.
 * @return The error code or MALI_ERR_NO_ERROR if there was no error.
 */
MALI_IMPORT MALI_CHECK_RESULT mali_err_code _m200_texture_swizzle(
    void                        *dest,
    m200_texture_addressing_mode dest_mode,
    const void                  *src,
    m200_texture_addressing_mode src_mode,
    s32                          width,
    s32                          height,
    m200_texel_format            format,
    int dst_pitch,
    int src_pitch);

/**
 * convert from linear to 2d interleaved texture
 * @note this does not work for 2d interleaved to linear :)
 */
MALI_IMPORT void _m200_texture_interleave_2d(
    void             *dest,
    const void       *src,
    s32               width,
    s32               height,
    int               src_pitch,
    m200_texel_format texel_format,
    s32               texels_per_block
);

/**
 * convert from linear to 16x16 block interleaved texture
 * @note this does not work for 16x16 block interleaved to linear :)
 */
MALI_IMPORT void _m200_texture_interleave_16x16_blocked(
    void             *dest,
    const void       *src,
    s32               width,
    s32               height,
    int               src_pitch,
    m200_texel_format texel_format
);

/**
 * convert ETC from linear to 16x16 block interleaved texture
 * @note this does not work for 16x16 block interleaved to linear :)
 */
MALI_IMPORT void _m200_texture_interleave_16x16_blocked_etc(
    void             *dest,
    const void       *src,
    s32               width,
    s32               height,
    int               src_pitch,
    m200_texel_format texel_format
);

#endif /* _M200_TEXTURE_H_ */

