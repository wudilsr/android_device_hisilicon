/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007, 2009-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI200_CORE_H_
#define _MALI200_CORE_H_

/**
 * Core specific constants
 */
#define MALI200_MAX_UNIFORM_BLOCKSIZE    32768
#define MALI200_MAX_INPUT_STREAMS        12

#define MALI200_RSW_ADDRESS_ALIGNMENT    64

#define MALI200_TILE_SIZE                16             /* This is the size of one tile in HW. Block-interleaved surfaces need dimensions that are a multiple of this */
#define MALI200_SURFACE_ALIGNMENT        64             /* writeback units need alignment 8, texture descriptors need alignment 64. Using common denominator */

#define MALI200_SURFACE_PITCH_ALIGNMENT_LINEAR_LAYOUT 8

#define MALI200_WRITEBACK_UNIT_COUNT     3
#define MALI200_WRITEBACK_UNIT_MRT_COUNT 4

#define _MALI_PP_MAX_SUB_JOBS 8

/** the maximum dimensions of a texture */
#define MALI200_MAX_TEXTURE_SIZE_LOG2 12
#define MALI200_MAX_TEXTURE_SIZE      (1 << MALI200_MAX_TEXTURE_SIZE_LOG2)

#endif /* _MALI200_CORE_H_*/
