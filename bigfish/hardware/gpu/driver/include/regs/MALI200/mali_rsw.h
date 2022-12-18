/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2011, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _M200_RSW_H_
#define _M200_RSW_H_

#include <mali_system.h>
#include <string.h>

typedef u32 m200_rsw[16];


/* offsets for pre-packing blending:
 * All GLES blending factors are encoded into a "source select", "alpha expand" and "1 minus x".
 * As these fields only depend upon the blending factor and are contiguous we can consider
 * them to be a single five bit field which has direct representations for each of the GLES blend
 * factors.
 *
 * The following defines provide the rsw packing arguments for these five bit fields, as well as
 * the offsets within the field to assist with the construction of the Mali blend factors below.
 *
 * As the alpha blending factors are only four bits (having an implicit 1 for alpha expand), the
 * ALPHA_BLEND_MASK is used when packing mali blend factors for alpha blending.
 */
#define M200_RSW_ONE_1_M_X_OFFSET                            3
#define M200_RSW_ALPHA_EXPAND_OFFSET                         4
#define M200_RSW_ALPHA_BLEND_MASK                            (0xF)

/* Mali encodings of GLES blend factors
 */
#define M200_RSW_BLEND_ZERO                     ( 0 << M200_RSW_ALPHA_EXPAND_OFFSET | 0 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_0 )
#define M200_RSW_BLEND_ONE                      ( 0 << M200_RSW_ALPHA_EXPAND_OFFSET | 1 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_0 )
#define M200_RSW_BLEND_SRC_COLOR                ( 0 << M200_RSW_ALPHA_EXPAND_OFFSET | 0 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cs )
#define M200_RSW_BLEND_ONE_MINUS_SRC_COLOR      ( 0 << M200_RSW_ALPHA_EXPAND_OFFSET | 1 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cs )
#define M200_RSW_BLEND_DST_COLOR                ( 0 << M200_RSW_ALPHA_EXPAND_OFFSET | 0 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cd )
#define M200_RSW_BLEND_ONE_MINUS_DST_COLOR      ( 0 << M200_RSW_ALPHA_EXPAND_OFFSET | 1 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cd )
#define M200_RSW_BLEND_SRC_ALPHA                ( 1 << M200_RSW_ALPHA_EXPAND_OFFSET | 0 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cs )
#define M200_RSW_BLEND_ONE_MINUS_SRC_ALPHA      ( 1 << M200_RSW_ALPHA_EXPAND_OFFSET | 1 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cs )
#define M200_RSW_BLEND_DST_ALPHA                ( 1 << M200_RSW_ALPHA_EXPAND_OFFSET | 0 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cd )
#define M200_RSW_BLEND_ONE_MINUS_DST_ALPHA      ( 1 << M200_RSW_ALPHA_EXPAND_OFFSET | 1 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cd )
#define M200_RSW_BLEND_CONSTANT_COLOR           ( 0 << M200_RSW_ALPHA_EXPAND_OFFSET | 0 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cc )
#define M200_RSW_BLEND_ONE_MINUS_CONSTANT_COLOR ( 0 << M200_RSW_ALPHA_EXPAND_OFFSET | 1 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cc )
#define M200_RSW_BLEND_CONSTANT_ALPHA           ( 1 << M200_RSW_ALPHA_EXPAND_OFFSET | 0 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cc )
#define M200_RSW_BLEND_ONE_MINUS_CONSTANT_ALPHA ( 1 << M200_RSW_ALPHA_EXPAND_OFFSET | 1 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_Cc )
#define M200_RSW_BLEND_SRC_ALPHA_SATURATE       ( 0 << M200_RSW_ALPHA_EXPAND_OFFSET | 0 << M200_RSW_ONE_1_M_X_OFFSET | M200_SOURCE_ALPHA_SATURATE )

/** framebuffer blend functions */
#define M200_BLEND_CsS_mCdD                            0
#define M200_BLEND_CdD_mCsS                            1
#define M200_BLEND_CsS_pCdD                            2
#define M200_BLEND_LOGICOP_MODE                        3
#define M200_BLEND_MIN_CsS_pCdD_Cd                     4            /* min( CaA + CsS, Cd ) */
#define M200_BLEND_MAX_CsS_pCdD_Cd                     5            /* max( CaA + CsS, Cd ) */
#define M200_BLEND_MIN_AsSa_pAdDa_Ad                    6           /* AsSa + AdDa < Ad ? CsS : CdD */
#define M200_BLEND_MAX_AsSa_pAdDa_Ad                    7           /* AsSa + AdDa > Ad ? CsS : CdD */

/** S and D source selections */
#define M200_SOURCE_Cs                                   0
#define M200_SOURCE_Cd                                   1
#define M200_SOURCE_Cc                                   2
#define M200_SOURCE_0                                    3
#define M200_SOURCE_ALPHA_SATURATE                       4
#define M200_SOURCE_Cs2                                  5
/* [ 6, 7 ] undefined */

/** Used to mask out the Source part of the blend mode */
#define M200_SOURCE_MASK                               0x7

/** @defgroup logic_op_modes
 *  These are different values for the logic op operations
 *  @{
 */
#define M200_LOGIC_OP_ALWAYS_0      0
#define M200_LOGIC_OP_NOR           1
#define M200_LOGIC_OP_D_NOT_S       2
#define M200_LOGIC_OP_NOT_S         3
#define M200_LOGIC_OP_S_NOT_D       4
#define M200_LOGIC_OP_NOT_D         5
#define M200_LOGIC_OP_XOR           6
#define M200_LOGIC_OP_NAND          7
#define M200_LOGIC_OP_AND           8
#define M200_LOGIC_OP_XNOR          9
#define M200_LOGIC_OP_D             10
#define M200_LOGIC_OP_NOT_NOT_D_S   11
#define M200_LOGIC_OP_S             12
#define M200_LOGIC_OP_NOT_NOT_S_D   13
#define M200_LOGIC_OP_OR            14
#define M200_LOGIC_OP_ALWAYS_1      15
/** @} end of logic_op_modes */


/* z bound operations */
#define M200_Z_BOUND_CLAMP                              0
#define M200_Z_BOUND_DISCARD                            1

/** @defgroup test_funcs
 *  These are different values for the stencil operations
 *  @{
 */
#define M200_TEST_ALWAYS_FAIL                                0
#define M200_TEST_LESS_THAN                                  1
#define M200_TEST_EQUAL                                      2
#define M200_TEST_LESS_THAN_OR_EQUAL                         3
#define M200_TEST_GREATER_THAN                               4
#define M200_TEST_NOT_EQUAL                                  5
#define M200_TEST_GREATER_THAN_OR_EQUAL                      6
#define M200_TEST_ALWAYS_SUCCEED                             7
/** @} end of test_funcs */


#define M200_RSW_Z_BOUND_MAX                                0xffff


/** @defgroup stencil_operations
 *  These are different values for the stencil operations
 *  @{
 */
#define M200_STENCIL_OP_KEEP_CURRENT                         0
#define M200_STENCIL_OP_SET_TO_REFERENCE                     1
#define M200_STENCIL_OP_SET_TO_ZERO                          2
#define M200_STENCIL_OP_BITWISE_INVERT                       3
#define M200_STENCIL_OP_INCREMENT                            4
#define M200_STENCIL_OP_DECREMENT                            5
#define M200_STENCIL_OP_SATURATING_INCREMENT                 6
#define M200_STENCIL_OP_SATURATING_DECREMENT                 7

/** @} end of stencil_operations */


#define M200_RSW_MULTISAMPLE_WRITE_MASK_ALL 0xf


/** @defgroup varying_formats
 *  The different varying formats
 *  @{
 */
#define M200_VARYING_FORMAT_FP32_4C  0
#define M200_VARYING_FORMAT_FP32_2C  1
#define M200_VARYING_FORMAT_FP16_4C  2
#define M200_VARYING_FORMAT_FP16_2C  3
#define M200_VARYING_FORMAT_SFX16_2C 4 /* 1:15 format */
#define M200_VARYING_FORMAT_UFX16_2C 5 /* 0:16 format */
#define M200_VARYING_FORMAT_FX10_3C  6 /* 2:8 per component format */
#define M200_VARYING_FORMAT_FX8_4C   7 /* 2:8 per component format */
/** @} end of varying_formats */



/* the required alignment is 8, but higher alignment suits better */
#define M200_FRAMEBUFFER_ALIGNMENT      32
#define M200_UNIFORM_BLOCK_ALIGNMENT     ( 4 * 2 )           /* 4-component vector of f16 datatypes */
#define M200_UNIFORM_BLOCK_ALIGNMENT_LOG2    3
#define M200_TILE_LIST_ALIGNMENT         32
#define M200_RSW_ALIGNMENT               64
#define M200_SHADER_ALIGNMENT            64
#define M200_TEXTURE_ALIGNMENT           64
#define M200_TD_ALIGNMENT                64
#define M200_VERTEX_ALIGNMENT            64
#define M200_VARYINGS_ALIGNMENT          16
#define M200_REMAP_TABLE_ALIGNMENT       16
#define M200_REMAP_TABLE_ALIGNMENT_LOG2  4

#define M200_POLYGON_ORIENTATION_CLOCKWISE 0
#define M200_POLYGON_ORIENTATION_ANTI_CLOCKWISE 1



/* bitmask for each rsw */
#define M200_RSW_CONSTANT_BLEND_COLOR_BLUE_BITMASK                  0x0000ffff            
#define M200_RSW_CONSTANT_BLEND_COLOR_GREEN_BITMASK                 0x0000ffff            
#define M200_RSW_CONSTANT_BLEND_COLOR_RED_BITMASK                   0x0000ffff            
#define M200_RSW_CONSTANT_BLEND_COLOR_ALPHA_BITMASK                 0x0000ffff            
#define M200_RSW_RGB_BLEND_FUNC_BITMASK                             0x00000007            
#define M200_RSW_ALPHA_BLEND_FUNC_BITMASK                           0x00000007            
#define M200_RSW_RGB_LOGIC_OP_TRUTH_TABLE_BITMASK                   0x0000000f            
#define M200_RSW_RGB_S_SOURCE_SELECT_BITMASK                        0x00000007            
#define M200_RSW_RGB_S_SOURCE_1_M_X_BITMASK                         0x00000001            
#define M200_RSW_RGB_S_SOURCE_ALPHA_EXPAND_BITMASK                  0x00000001            
#define M200_RSW_RGB_D_SOURCE_SELECT_BITMASK                        0x00000007            
#define M200_RSW_RGB_D_SOURCE_1_M_X_BITMASK                         0x00000001            
#define M200_RSW_RGB_D_SOURCE_ALPHA_EXPAND_BITMASK                  0x00000001            
#define M200_RSW_ALPHA_LOGIC_OP_TRUTH_TABLE_BITMASK                 0x0000000f            
#define M200_RSW_ALPHA_S_SOURCE_SELECT_BITMASK                      0x00000007            
#define M200_RSW_ALPHA_S_SOURCE_1_M_X_BITMASK                       0x00000001            
#define M200_RSW_ALPHA_D_SOURCE_SELECT_BITMASK                      0x00000007            
#define M200_RSW_ALPHA_D_SOURCE_1_M_X_BITMASK                       0x00000001            
#define M200_RSW_RGB_INPUT_COLOR_CLAMP_0_1_BITMASK                  0x00000001            
#define M200_RSW_ALPHA_INPUT_COLOR_CLAMP_0_1_BITMASK                0x00000001            
#define M200_RSW_RGB_RESULT_COLOR_CLAMP_0_1_BITMASK                 0x00000001            
#define M200_RSW_ALPHA_RESULT_COLOR_CLAMP_0_1_BITMASK               0x00000001            
#define M200_RSW_R_WRITE_MASK_BITMASK                               0x00000001            
#define M200_RSW_G_WRITE_MASK_BITMASK                               0x00000001            
#define M200_RSW_B_WRITE_MASK_BITMASK                               0x00000001            
#define M200_RSW_A_WRITE_MASK_BITMASK                               0x00000001            
#define M200_RSW_ABGR_WRITE_MASK_BITMASK                            0x0000000f            
#define M200_RSW_RGB_S_SOURCE_COMBINED_BITMASK                      0x0000001f            
#define M200_RSW_RGB_D_SOURCE_COMBINED_BITMASK                      0x0000001f            
#define M200_RSW_ALPHA_S_SOURCE_COMBINED_BITMASK                    0x0000000f            
#define M200_RSW_ALPHA_D_SOURCE_COMBINED_BITMASK                    0x0000000f            
#define M200_RSW_Z_WRITE_MASK_BITMASK                               0x00000001            
#define M200_RSW_Z_COMPARE_FUNC_BITMASK                             0x00000007            
#define M200_RSW_Z_NEAR_DEPTH_BOUND_OP_BITMASK                      0x00000001            
#define M200_RSW_Z_FAR_DEPTH_BOUND_OP_BITMASK                       0x00000001            
#define M200_RSW_Z_STENCIL_VALUE_REGISTER_BITMASK                   0x0000000f            
#define M200_RSW_DST_ENABLE_BITMASK                                 0x00000001            
#define M200_RSW_SHADER_Z_REPLACE_ENABLE_BITMASK                    0x00000001            
#define M200_RSW_SHADER_STENCIL_REPLACE_ENABLE_BITMASK              0x00000001            
#define M200_RSW_POLYGON_Z_OFFSET_FACTOR_BITMASK                    0x000000ff            
#define M200_RSW_POLYGON_Z_OFFSET_OFFSET_BITMASK                    0x000000ff            
#define M200_RSW_Z_NEAR_BOUND_BITMASK                               0x0000ffff            
#define M200_RSW_Z_FAR_BOUND_BITMASK                                0x0000ffff            
#define M200_RSW_STENCIL_FRONT_COMPARE_FUNC_BITMASK                 0x00000007            
#define M200_RSW_STENCIL_FRONT_OP_IF_SFAIL_BITMASK                  0x00000007            
#define M200_RSW_STENCIL_FRONT_OP_IF_ZFAIL_BITMASK                  0x00000007            
#define M200_RSW_STENCIL_FRONT_OP_IF_ZPASS_BITMASK                  0x00000007            
#define M200_RSW_STENCIL_FRONT_REF_VALUE_BITMASK                    0x000000ff            
#define M200_RSW_STENCIL_FRONT_OP_MASK_BITMASK                      0x000000ff            
#define M200_RSW_STENCIL_BACK_COMPARE_FUNC_BITMASK                  0x00000007            
#define M200_RSW_STENCIL_BACK_OP_IF_SFAIL_BITMASK                   0x00000007            
#define M200_RSW_STENCIL_BACK_OP_IF_ZFAIL_BITMASK                   0x00000007            
#define M200_RSW_STENCIL_BACK_OP_IF_ZPASS_BITMASK                   0x00000007            
#define M200_RSW_STENCIL_BACK_REF_VALUE_BITMASK                     0x000000ff            
#define M200_RSW_STENCIL_BACK_OP_MASK_BITMASK                       0x000000ff            
#define M200_RSW_STENCIL_FRONT_WRITE_MASK_BITMASK                   0x000000ff            
#define M200_RSW_STENCIL_BACK_WRITE_MASK_BITMASK                    0x000000ff            
#define M200_RSW_ALPHA_TEST_REF_VALUE_BITMASK                       0x0000ffff            
#define M200_RSW_ALPHA_TEST_FUNC_BITMASK                            0x00000007            
#define M200_RSW_MULTISAMPLE_GRID_ENABLE_BITMASK                    0x00000001            
#define M200_RSW_4X_SUPERSAMPLING_ENABLE_BITMASK                    0x00000001            
#define M200_RSW_MULTISAMPLED_ALPHA_TEST_ENABLE_BITMASK             0x00000001            
#define M200_RSW_MULTISAMPLED_Z_TEST_ENABLE_BITMASK                 0x00000001            
#define M200_RSW_SAMPLE_ALPHA_TO_COVERAGE_BITMASK                   0x00000001            
#define M200_RSW_SAMPLE_ALPHA_TO_ONE_BITMASK                        0x00000001            
#define M200_RSW_SAMPLE_COVERAGE_INVERT_BITMASK                     0x00000001            
#define M200_RSW_FLATSHADING_VERTEX_SELECTOR_BITMASK                0x00000003            
#define M200_RSW_MULTISAMPLE_WRITE_MASK_BITMASK                     0x0000000f            
#define M200_RSW_SAMPLE_0_REGISTER_SELECT_BITMASK                   0x0000000f            
#define M200_RSW_SAMPLE_1_REGISTER_SELECT_BITMASK                   0x0000000f            
#define M200_RSW_SAMPLE_2_REGISTER_SELECT_BITMASK                   0x0000000f            
#define M200_RSW_SAMPLE_3_REGISTER_SELECT_BITMASK                   0x0000000f            
#define M200_RSW_FIRST_SHADER_INSTRUCTION_LENGTH_BITMASK            0x0000001f            
#define M200_RSW_SHADER_ADDRESS_BITMASK                             0xffffffc0            
#define M200_RSW_VARYING0_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING1_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING2_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING3_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING4_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING5_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING6_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING7_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING8_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING9_FORMAT_BITMASK                            0x00000007            
#define M200_RSW_VARYING10_FORMAT_BITS_0_1_BITMASK                  0x00000003            
#define M200_RSW_UNIFORMS_REMAPPING_TABLE_LOG2_SIZE_BITMASK         0x0000000f            
#define M200_RSW_UNIFORMS_REMAPPING_TABLE_ADDRESS_BITMASK           0xfffffff0            
#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_LOG2_SIZE_BITMASK   0x0000000f            
#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_ADDRESS_BITMASK     0xfffffff0            
#define M200_RSW_PER_VERTEX_VARYING_BLOCK_SIZE_BITMASK              0x0000001f            
#define M200_RSW_HINT_FETCH_TEX_DESCRIPTOR_REMAPPING_TABLE_BITMASK  0x00000001            
#define M200_RSW_HINT_NO_SHADER_PRESENT_BITMASK                     0x00000001            
#define M200_RSW_HINT_FETCH_SHADER_UNIFORMS_REMAPPING_TABLE_BITMASK 0x00000001            
#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_TEST_BITMASK             0x00000001            
#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_UPDATE_BITMASK           0x00000001            
#define M200_RSW_HINT_SHADER_CONTAINS_DISCARD_BITMASK               0x00000001            
#define M200_RSW_HINT_SHADER_LACKS_RENDEZVOUS_BITMASK               0x00000001            
#define M200_RSW_FORWARD_PIXEL_KILL_PERMISSIBLE_BITMASK             0x00000001            
#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_SIZE_BITMASK        0x00003fff            
#define M200_RSW_REGISTER_SELECT_FOR_Cs2_BITMASK                    0x0000000f            
#define M200_RSW_STENCIL_TAG_BITS_BITMASK                           0x0000000f            
#define M200_RSW_STENCIL_CLEAR_TAG_BITMASK                          0x000000ff            
#define M200_RSW_POLYGON_ORIENTATION_FLAG_BITMASK                   0x00000001            
#define M200_RSW_DITHERING_ENABLE_BITMASK                           0x00000001            
#define M200_RSW_ROP4_ENABLE_BITMASK                                0x00000001            
#define M200_RSW_UNIFORMS_REMAPPING_TABLE_SIZE_BITMASK              0x0000ffff            
#define M200_RSW_VARYING10_FORMAT_BIT_2_BITMASK                     0x00000001            
#define M200_RSW_VARYING11_FORMAT_BITMASK                           0x00000007            
#define M200_RSW_VARYINGS_BASE_ADDRESS_BITMASK                      0xfffffff0            





/* setter and getter for each rsw */

#if MALI_BIG_ENDIAN

#define M200_RSW_CONSTANT_BLEND_COLOR_BLUE_SET(dest, value) do{ \
		((u32 *)(dest))[0] &= 0x0000ffff; \
		((u32 *)(dest))[0] ^= ((value) & 0x000000ff) << 24 | \
							  ((value) & 0x0000ff00) << 8; \
	}while(0);

#define M200_RSW_CONSTANT_BLEND_COLOR_GREEN_SET(dest, value) do{ \
		((u32 *)(dest))[0] &= 0xffff0000; \
		((u32 *)(dest))[0] ^= ((value) & 0x000000ff) << 8 | \
							  ((value) & 0x0000ff00) >> 8; \
	}while(0);

#define M200_RSW_CONSTANT_BLEND_COLOR_RED_SET(dest, value) do { \
		((u32 *)(dest))[1] &= 0x0000ffff; \
		((u32 *)(dest))[1] ^= ((value) & 0x000000ff) << 24 | \
							  ((value) & 0x0000ff00) << 8; \
	}while(0);

#define M200_RSW_CONSTANT_BLEND_COLOR_ALPHA_SET(dest, value) do { \
		((u32 *)(dest))[1] &= 0xffff0000; \
		((u32 *)(dest))[1] ^= ((value) & 0x000000ff) << 8 | \
							  ((value) & 0x0000ff00) >> 8; \
	}while(0);

#define M200_RSW_RGB_BLEND_FUNC_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xf8ffffff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000007) << 24; \
	}while(0);

#define M200_RSW_ALPHA_BLEND_FUNC_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xc7ffffff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000007) << 27; \
	}while(0);

#define M200_RSW_RGB_LOGIC_OP_TRUTH_TABLE_SET(dest, value) do { \
		((unsigned int *)(dest))[2] &= 0x3ffcffff; \
		((unsigned int *)(dest))[2] ^= ((value) & 0x00000003) << 30 | \
							  ((value) & 0x0000000c) << 14; \
	}while(0);

#define M200_RSW_RGB_S_SOURCE_SELECT_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0x3ffeffff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000003) << 30 | \
							  ((value) & 0x00000004) << 14; \
	}while(0);

#define M200_RSW_RGB_S_SOURCE_1_M_X_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xfffdffff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 17; \
	}while(0);

#define M200_RSW_RGB_S_SOURCE_ALPHA_EXPAND_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xfffbffff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 18; \
	}while(0);


#define M200_RSW_RGB_D_SOURCE_SELECT_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xffc7ffff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000007) << 19; \
	}while(0);

#define M200_RSW_RGB_D_SOURCE_1_M_X_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xffbfffff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 22; \
	}while(0);

#define M200_RSW_RGB_D_SOURCE_ALPHA_EXPAND_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xff7fffff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 23; \
	}while(0);


#define M200_RSW_ALPHA_LOGIC_OP_TRUTH_TABLE_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xfffff0ff; \
		((u32 *)(dest))[2] ^= ((value) & 0x0000000f) << 8; \
	}while(0);

#define M200_RSW_ALPHA_S_SOURCE_SELECT_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xfffff8ff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000007) << 8; \
	}while(0);

#define M200_RSW_ALPHA_S_SOURCE_1_M_X_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xfffff7ff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 11; \
	}while(0);

#define M200_RSW_ALPHA_D_SOURCE_SELECT_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xffff8fff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000007) << 12; \
	}while(0);

#define M200_RSW_ALPHA_D_SOURCE_1_M_X_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xffff7fff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 15; \
	}while(0);



#define M200_RSW_RGB_INPUT_COLOR_CLAMP_0_1_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xfffffffe; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001); \
	}while(0);

#define M200_RSW_ALPHA_INPUT_COLOR_CLAMP_0_1_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xfffffffd; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 1; \
	}while(0);

#define M200_RSW_RGB_RESULT_COLOR_CLAMP_0_1_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xfffffffb; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 2; \
	}while(0);

#define M200_RSW_ALPHA_RESULT_COLOR_CLAMP_0_1_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xfffffff7; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 3; \
	}while(0);

#define M200_RSW_R_WRITE_MASK_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xffffffef; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 4; \
	}while(0);

#define M200_RSW_G_WRITE_MASK_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xffffffdf; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 5; \
	}while(0);

#define M200_RSW_B_WRITE_MASK_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xffffffbf; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 6; \
	}while(0);

#define M200_RSW_A_WRITE_MASK_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xffffff7f; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000001) << 7; \
	}while(0);

#define M200_RSW_ABGR_WRITE_MASK_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0xffffff0f; \
		((u32 *)(dest))[2] ^= ((value) & 0x0000000f) << 4; \
	}while(0);




#define M200_RSW_RGB_S_SOURCE_COMBINED_SET(dest, value) do { \
		((u32 *)(dest))[2] &= 0x3ff8ffff; \
		((u32 *)(dest))[2] ^= ((value) & 0x00000003) << 30 | \
							  ((value) & 0x0000001c) << 14; \
	}while(0);

#define M200_RSW_RGB_D_SOURCE_COMBINED_SET(dest, value) do { \
	((u32 *)(dest))[2] &= 0xff07ffff; \
	((u32 *)(dest))[2] ^= ((value) & 0x0000001f) << 19; \
	}while(0);

#define M200_RSW_ALPHA_S_SOURCE_COMBINED_SET(dest, value) do { \
	((u32 *)(dest))[2] &= 0xfffff0ff; \
	((u32 *)(dest))[2] ^= ((value) & 0x0000000f) << 8; \
	}while(0);

#define M200_RSW_ALPHA_D_SOURCE_COMBINED_SET(dest, value) do { \
	((u32 *)(dest))[2] &= 0xffff0fff; \
	((u32 *)(dest))[2] ^= ((value) & 0x0000000f) << 12; \
	}while(0);


#define M200_RSW_Z_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0xfffffffe; \
	((u32 *)(dest))[3] ^= ((value) & 0x00000001) << 24; \
	}while(0);

#define M200_RSW_Z_COMPARE_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0xf1ffffff; \
	((u32 *)(dest))[3] ^= ((value) & 0x00000007) << 25; \
	}while(0);

#define M200_RSW_Z_NEAR_DEPTH_BOUND_OP_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0xefffffff; \
	((u32 *)(dest))[3] ^= ((value) & 0x00000001) << 28; \
	}while(0);

#define M200_RSW_Z_FAR_DEPTH_BOUND_OP_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0xdfffffff; \
	((u32 *)(dest))[3] ^= ((value) & 0x00000001) << 29; \
	}while(0);

#define M200_RSW_Z_STENCIL_VALUE_REGISTER_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0x3ffcffff; \
	((u32 *)(dest))[3] ^= ((value) & 0x00000003) << 30 | \
						  ((value) & 0x0000000c) << 14; \
	}while(0);

#define M200_RSW_DST_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0xfffbffff; \
	((u32 *)(dest))[3] ^= ((value) & 0x00000001) << 18; \
	}while(0);

#define M200_RSW_SHADER_Z_REPLACE_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0xfff7ffff; \
	((u32 *)(dest))[3] ^= ((value) & 0x00000001) << 19; \
	}while(0);

#define M200_RSW_SHADER_STENCIL_REPLACE_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0xffefffff; \
	((u32 *)(dest))[3] ^= ((value) & 0x00000001) << 20; \
	}while(0);

#define M200_RSW_POLYGON_Z_OFFSET_FACTOR_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0xffff00ff; \
	((u32 *)(dest))[3] ^= ((value) & 0x000000ff) << 8; \
	}while(0);


#define M200_RSW_POLYGON_Z_OFFSET_OFFSET_SET(dest, value) do { \
	((u32 *)(dest))[3] &= 0xffffff00; \
	((u32 *)(dest))[3] ^= ((value) & 0x000000ff); \
	}while(0);


#define M200_RSW_Z_NEAR_BOUND_SET(dest, value) do { \
	((u32 *)(dest))[4] &= 0x0000ffff; \
	((u32 *)(dest))[4] ^= ((value) & 0x000000ff) << 24 | \
						  ((value) & 0x0000ff00) << 8; \
	}while(0);

#define M200_RSW_Z_FAR_BOUND_SET(dest, value) do { \
	((u32 *)(dest))[4] &= 0xffff0000; \
	((u32 *)(dest))[4] ^= ((value) & 0x000000ff) << 8 | \
						  ((value) & 0x0000ff00) >> 8; \
	}while(0);

#define M200_RSW_STENCIL_FRONT_COMPARE_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[5] &= 0xf8ffffff; \
	((u32 *)(dest))[5] ^= ((value) & 0x00000007) << 24;  \
	}while(0);

#define M200_RSW_STENCIL_FRONT_OP_IF_SFAIL_SET(dest, value) do { \
	((u32 *)(dest))[5] &= 0xc7ffffff; \
	((u32 *)(dest))[5] ^= ((value) & 0x00000007) << 27; \
	}while(0);

#define M200_RSW_STENCIL_FRONT_OP_IF_ZFAIL_SET(dest, value) do { \
	((u32 *)(dest))[5] &= 0x3ffeffff; \
	((u32 *)(dest))[5] ^= ((value) & 0x00000003) << 30 | \
						  ((value) & 0x00000004) << 14; \
	}while(0);

#define M200_RSW_STENCIL_FRONT_OP_IF_ZPASS_SET(dest, value) do { \
	((u32 *)(dest))[5] &= 0xfff1ffff; \
	((u32 *)(dest))[5] ^= ((value) & 0x00000007) << 17; \
	}while(0);

#define M200_RSW_STENCIL_FRONT_REF_VALUE_SET(dest, value) do { \
	((u32 *)(dest))[5] &= 0xffff00ff; \
	((u32 *)(dest))[5] ^= ((value) & 0x000000ff) << 8; \
	}while(0);

#define M200_RSW_STENCIL_FRONT_OP_MASK_SET(dest, value) do { \
	((u32 *)(dest))[5] &= 0xffffff00; \
	((u32 *)(dest))[5] ^= ((value) & 0x000000ff); \
	}while(0);


#define M200_RSW_STENCIL_BACK_COMPARE_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[6] &= 0xf8ffffff; \
	((u32 *)(dest))[6] ^= ((value) & 0x00000007) << 24;  \
	}while(0);

#define M200_RSW_STENCIL_BACK_OP_IF_SFAIL_SET(dest, value) do { \
	((u32 *)(dest))[6] &= 0xc7ffffff; \
	((u32 *)(dest))[6] ^= ((value) & 0x00000007) << 27; \
	}while(0);

#define M200_RSW_STENCIL_BACK_OP_IF_ZFAIL_SET(dest, value) do { \
	((u32 *)(dest))[6] &= 0x3ffeffff; \
	((u32 *)(dest))[6] ^= ((value) & 0x00000003) << 30 | \
						  ((value) & 0x00000004) << 14; \
	}while(0);

#define M200_RSW_STENCIL_BACK_OP_IF_ZPASS_SET(dest, value) do { \
	((u32 *)(dest))[6] &= 0xfff1ffff; \
	((u32 *)(dest))[6] ^= ((value) & 0x00000007) << 17; \
	}while(0);

#define M200_RSW_STENCIL_BACK_REF_VALUE_SET(dest, value) do { \
	((u32 *)(dest))[6] &= 0xffff00ff; \
	((u32 *)(dest))[6] ^= ((value) & 0x000000ff) << 8; \
	}while(0);

#define M200_RSW_STENCIL_BACK_OP_MASK_SET(dest, value) do { \
	((u32 *)(dest))[6] &= 0xffffff00; \
	((u32 *)(dest))[6] ^= ((value) & 0x000000ff); \
	}while(0);


#define M200_RSW_STENCIL_FRONT_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[7] &= 0x00ffffff; \
	((u32 *)(dest))[7] ^= ((value) & 0x000000ff) << 24; \
	}while(0);


#define M200_RSW_STENCIL_BACK_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[7] &= 0xff00ffff; \
	((u32 *)(dest))[7] ^= ((value) & 0x000000ff) << 16; \
	}while(0);


#define M200_RSW_ALPHA_TEST_REF_VALUE_SET(dest, value) do { \
	((u32 *)(dest))[7] &= 0xffff0000; \
	((u32 *)(dest))[7] ^= ((value) & 0x0000ff00) >> 8 | \
						  ((value) & 0x000000ff) << 8; \
	}while(0);


#define M200_RSW_ALPHA_TEST_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xf8ffffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x00000007) << 24; \
	}while(0);

#define M200_RSW_MULTISAMPLE_GRID_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xf7ffffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x00000001) << 27; \
	}while(0);

#define M200_RSW_4X_SUPERSAMPLING_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xefffffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x00000001) << 28; \
	}while(0);

#define M200_RSW_MULTISAMPLED_ALPHA_TEST_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xdfffffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x00000001) << 29; \
	}while(0);

#define M200_RSW_MULTISAMPLED_Z_TEST_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xbfffffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x00000001) << 30; \
	}while(0);

#define M200_RSW_SAMPLE_ALPHA_TO_COVERAGE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0x7fffffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x00000001) << 31; \
	}while(0);

#define M200_RSW_SAMPLE_ALPHA_TO_ONE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xfffeffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x00000001) << 16; \
	}while(0);

#define M200_RSW_SAMPLE_COVERAGE_INVERT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xfffdffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x00000001) << 17; \
	}while(0);

#define M200_RSW_FLATSHADING_VERTEX_SELECTOR_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xfff3ffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x00000003) << 18; \
	}while(0);

#define M200_RSW_MULTISAMPLE_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xff0fffff; \
	((u32 *)(dest))[8] ^= ((value) & 0x0000000f) << 20; \
	}while(0);

#define M200_RSW_SAMPLE_0_REGISTER_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xfffff0ff; \
	((u32 *)(dest))[8] ^= ((value) & 0x0000000f) << 8; \
	}while(0);

#define M200_RSW_SAMPLE_1_REGISTER_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xffff0fff; \
	((u32 *)(dest))[8] ^= ((value) & 0x0000000f) << 12; \
	}while(0);

#define M200_RSW_SAMPLE_2_REGISTER_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xfffffff0; \
	((u32 *)(dest))[8] ^= ((value) & 0x0000000f); \
	}while(0);

#define M200_RSW_SAMPLE_3_REGISTER_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= 0xffffff0f; \
	((u32 *)(dest))[8] ^= ((value) & 0x0000000f) << 4; \
	}while(0);


#define M200_RSW_FIRST_SHADER_INSTRUCTION_LENGTH_SET(dest, value) do { \
	((u32 *)(dest))[9] &= 0xe0ffffff; \
	((u32 *)(dest))[9] ^= ((value) & 0x0000001f) << 24; \
	}while(0);

#define M200_RSW_SHADER_ADDRESS_SET(dest, value) do { \
	((u32 *)(dest))[9] &= 0x3f000000; \
	((u32 *)(dest))[9] ^= ((value) & 0x000000c0) << 24 | \
						  ((value) & 0x0000ff00) << 8 | \
						  ((value) & 0x00ff0000) >> 8 | \
						  ((value) & 0xff000000) >> 24; \
	}while(0);


#define M200_RSW_VARYING0_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xf8ffffff; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000007) << 24; \
	}while(0);

#define M200_RSW_VARYING1_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xc7ffffff; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000007) << 27; \
	}while(0);

#define M200_RSW_VARYING2_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0x3ffeffff; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000003) << 30 | \
						   ((value) & 0x00000004) << 14; \
	}while(0);

#define M200_RSW_VARYING3_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xfff1ffff; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000007) << 17; \
	}while(0);

#define M200_RSW_VARYING4_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xff8fffff; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000007) << 20; \
	}while(0);

#define M200_RSW_VARYING5_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xff7ffcff; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000001) << 23 | \
						   ((value) & 0x00000006) << 7; \
	}while(0);

#define M200_RSW_VARYING6_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xffffe3ff; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000007) << 10; \
	}while(0);

#define M200_RSW_VARYING7_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xffff1fff; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000007) << 13; \
	}while(0);

#define M200_RSW_VARYING8_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xfffffff8; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000007); \
	}while(0);

#define M200_RSW_VARYING9_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xffffffc7; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000007) << 3; \
	}while(0);

#define M200_RSW_VARYING10_FORMAT_BITS_0_1_SET(dest, value) do { \
	((u32 *)(dest))[10] &= 0xffffff3f; \
	((u32 *)(dest))[10] ^= ((value) & 0x00000003) << 6; \
	}while(0);

#define M200_RSW_UNIFORMS_REMAPPING_TABLE_LOG2_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[11] &= 0xf0ffffff; \
	((u32 *)(dest))[11] ^= ((value) & 0x0000000f) << 24; \
	}while(0);

#define M200_RSW_UNIFORMS_REMAPPING_TABLE_ADDRESS_SET(dest, value) do { \
	((u32 *)(dest))[11] &= 0x0f000000; \
	((u32 *)(dest))[11] ^= ((value) & 0x000000f0) << 24 | \
						   ((value) & 0x0000ff00) << 8 | \
						   ((value) & 0x00ff0000) >> 8 | \
						   ((value) & 0xff000000) >> 24; \
	}while(0);

#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_LOG2_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[12] &= 0xf0ffffff; \
	((u32 *)(dest))[12] ^= ((value) & 0x0000000f) << 24; \
	}while(0);

#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_ADDRESS_SET(dest, value) do { \
	((u32 *)(dest))[12] &= 0x0f000000; \
	((u32 *)(dest))[12] ^= ((value) & 0x000000f0) << 24 | \
						   ((value) & 0x0000ff00) << 8 | \
						   ((value) & 0x00ff0000) >> 8 | \
						   ((value) & 0xff000000) >> 24; \
	}while(0);

#define M200_RSW_PER_VERTEX_VARYING_BLOCK_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xe0ffffff; \
	((u32 *)(dest))[13] ^= ((value) & 0x0000001f) << 24; \
	}while(0);


#define M200_RSW_HINT_FETCH_TEX_DESCRIPTOR_REMAPPING_TABLE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xdfffffff; \
	((u32 *)(dest))[13] ^= ((value) & 0x00000001) << 29; \
	}while(0);

#define M200_RSW_HINT_NO_SHADER_PRESENT_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xbfffffff; \
	((u32 *)(dest))[13] ^= ((value) & 0x00000001) << 30; \
	}while(0);

#define M200_RSW_HINT_FETCH_SHADER_UNIFORMS_REMAPPING_TABLE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0x7fffffff; \
	((u32 *)(dest))[13] ^= ((value) & 0x00000001) << 31; \
	}while(0);


#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_TEST_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xfffeffff; \
	((u32 *)(dest))[13] ^= ((value) & 0x00000001) << 16; \
	}while(0);


#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_UPDATE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xfffdffff; \
	((u32 *)(dest))[13] ^= ((value) & 0x00000001) << 17; \
	}while(0);


#define M200_RSW_HINT_SHADER_CONTAINS_DISCARD_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xfffdffff; \
	((u32 *)(dest))[13] ^= ((value) & 0x00000001) << 18; \
	}while(0);

#define M200_RSW_HINT_SHADER_LACKS_RENDEZVOUS_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xfff7ffff; \
	((u32 *)(dest))[13] ^= ((value) & 0x00000001) << 19; \
	}while(0);

#define M200_RSW_FORWARD_PIXEL_KILL_PERMISSIBLE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xffefffff; \
	((u32 *)(dest))[13] ^= ((value) & 0x00000001) << 20; \
	}while(0);

#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xff3f00f0; \
	((u32 *)(dest))[13] ^= ((value) & 0x00000003) << 22 | \
						   ((value) & 0x000003fc) << 6 | \
						   ((value) & 0x00003c00) >> 10; \
	}while(0);

#define M200_RSW_REGISTER_SELECT_FOR_Cs2_SET(dest, value) do { \
	((u32 *)(dest))[13] &= 0xffffff0f; \
	((u32 *)(dest))[13] ^= ((value) & 0x0000000f) << 4; \
	}while(0);


#define M200_RSW_STENCIL_TAG_BITS_SET(dest, value) do { \
	((u32 *)(dest))[14] &= 0xf0ffffff; \
	((u32 *)(dest))[14] ^= ((value) & 0x0000000f) << 24; \
	}while(0);

#define M200_RSW_STENCIL_CLEAR_TAG_SET(dest, value) do { \
	((u32 *)(dest))[14] &= 0x0ff0ffff; \
	((u32 *)(dest))[14] ^= ((value) & 0x0000000f) << 28 | \
						   ((value) & 0x000000f0) << 12; \
	}while(0);

#define M200_RSW_POLYGON_ORIENTATION_FLAG_SET(dest, value) do { \
	((u32 *)(dest))[14] &= 0xffefffff; \
	((u32 *)(dest))[14] ^= ((value) & 0x00000001) << 20; \
	}while(0);

#define M200_RSW_DITHERING_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[14] &= 0xffdfffff; \
	((u32 *)(dest))[14] ^= ((value) & 0x00000001) << 21; \
	}while(0);

#define M200_RSW_ROP4_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[14] &= 0xffbfffff; \
	((u32 *)(dest))[14] ^= ((value) & 0x00000001) << 22; \
	}while(0);

#define M200_RSW_UNIFORMS_REMAPPING_TABLE_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[14] &= 0xffff0000; \
	((u32 *)(dest))[14] ^= ((value) & 0x000000ff) << 8 | \
						   ((value) & 0x0000ff00) >> 8; \
	}while(0);

#define M200_RSW_VARYING10_FORMAT_BIT_2_SET(dest, value) do { \
	((u32 *)(dest))[15] &= 0xfeffffff; \
	((u32 *)(dest))[15] ^= ((value) & 0x00000001) << 24; \
	}while(0);

#define M200_RSW_VARYING11_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[15] &= 0xf1ffffff; \
	((u32 *)(dest))[15] ^= ((value) & 0x00000007) << 25; \
	}while(0);

#define M200_RSW_VARYINGS_BASE_ADDRESS_SET(dest, value) do { \
	((u32 *)(dest))[15] &= 0x0f000000; \
	((u32 *)(dest))[15] ^= ((value) & 0x000000f0) << 24 | \
						   ((value) & 0x0000ff00) << 8 | \
						   ((value) & 0x00ff0000) >> 8 | \
						   ((value) & 0xff000000) >> 24; \
	}while(0);






/* getters */
#define M200_RSW_CONSTANT_BLEND_COLOR_BLUE_GET(dest) \
	( \
	(((u32 *)dest)[0] & 0xff000000) >> 24 | \
	(((u32 *)dest)[0] & 0x00ff0000) >> 8 \
	)


#define M200_RSW_CONSTANT_BLEND_COLOR_GREEN_GET(dest) \
	( \
	(((u32 *)(dest))[0] & 0x0000ff00) >> 8 | \
	(((u32 *)(dest))[0] & 0x000000ff) << 8 \
	)

/** subword 1, constant color blending */
#define M200_RSW_CONSTANT_BLEND_COLOR_RED_GET(dest) \
	( \
	(((u32 *)(dest))[1] & 0xff000000) >> 24 | \
	(((u32 *)(dest))[1] & 0x00ff0000) >> 8 \
	)

#define M200_RSW_CONSTANT_BLEND_COLOR_ALPHA_GET(dest) \
	( \
	(((u32 *)(dest))[1] & 0x0000ff00) >> 8 | \
	(((u32 *)(dest))[1] & 0x000000ff) << 8 \
	)

#define M200_RSW_RGB_BLEND_FUNC_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x07000000) >> 24 \
	)

#define M200_RSW_ALPHA_BLEND_FUNC_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x38000000) >> 27 \
	)


#define M200_RSW_RGB_LOGIC_OP_TRUTH_TABLE_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0xc0000000) >> 30 | \
	(((u32 *)(dest))[2] & 0x00030000) >> 14 \
	)

#define M200_RSW_RGB_S_SOURCE_SELECT_GET(dest) \
  	( \
	(((u32 *)(dest))[2] & 0xc0000000) >> 30 | \
	(((u32 *)(dest))[2] & 0x00010000) >> 14 \
	)

#define M200_RSW_RGB_S_SOURCE_1_M_X_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00020000) >> 17 \
	)

#define M200_RSW_RGB_S_SOURCE_ALPHA_EXPAND_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00040000) >> 18 \
	)


#define M200_RSW_RGB_D_SOURCE_SELECT_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00380000) >> 19 \
	)

#define M200_RSW_RGB_D_SOURCE_1_M_X_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00400000) >> 22 \
	)

#define M200_RSW_RGB_D_SOURCE_ALPHA_EXPAND_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00800000) >> 23 \
	)


#define M200_RSW_ALPHA_LOGIC_OP_TRUTH_TABLE_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000f00) >> 8 \
	)

#define M200_RSW_ALPHA_S_SOURCE_SELECT_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000700) >> 8 \
	)

#define M200_RSW_ALPHA_S_SOURCE_1_M_X_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000800) >> 11 \
	)


#define M200_RSW_ALPHA_D_SOURCE_SELECT_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00007000) >> 12 \
	)

#define M200_RSW_ALPHA_D_SOURCE_1_M_X_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00008000) >> 15 \
	)


#define M200_RSW_RGB_INPUT_COLOR_CLAMP_0_1_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000001) \
	)

#define M200_RSW_ALPHA_INPUT_COLOR_CLAMP_0_1_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000002) >> 1 \
	)

#define M200_RSW_RGB_RESULT_COLOR_CLAMP_0_1_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000004) >> 2 \
	)


#define M200_RSW_ALPHA_RESULT_COLOR_CLAMP_0_1_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000008) >> 3 \
	)


#define M200_RSW_R_WRITE_MASK_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000010) >> 4 \
	)


#define M200_RSW_G_WRITE_MASK_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000020) >> 5 \
	)


#define M200_RSW_B_WRITE_MASK_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000040) >> 6 \
	)


#define M200_RSW_A_WRITE_MASK_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000080) >> 7 \
	)

#define M200_RSW_ABGR_WRITE_MASK_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x000000f0) >> 4 \
	)


#define M200_RSW_RGB_S_SOURCE_COMBINED_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0xc0000000) >> 30 | \
	(((u32 *)(dest))[2] & 0x00070000) >> 14 \
	)

#define M200_RSW_RGB_D_SOURCE_COMBINED_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00f80000) >> 19 \
	)

#define M200_RSW_ALPHA_S_SOURCE_COMBINED_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x00000f00) >> 8 \
	)

#define M200_RSW_ALPHA_D_SOURCE_COMBINED_GET(dest) \
	( \
	(((u32 *)(dest))[2] & 0x0000f000) >> 12 \
	)


#define M200_RSW_Z_WRITE_MASK_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0x01000000) >> 24 \
	)

#define M200_RSW_Z_COMPARE_FUNC_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0x0e000000) >> 25 \
	)

#define M200_RSW_Z_NEAR_DEPTH_BOUND_OP_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0x10000000) >> 28 \
	)

#define M200_RSW_Z_FAR_DEPTH_BOUND_OP_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0x20000000) >> 29 \
	)

#define M200_RSW_Z_STENCIL_VALUE_REGISTER_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0xc0000000) >> 30 | \
	(((u32 *)(dest))[3] & 0x00030000) >> 14 \
	)

#define M200_RSW_DST_ENABLE_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0x00040000) >> 18 \
	)

#define M200_RSW_SHADER_Z_REPLACE_ENABLE_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0x00080000) >> 19 \
	)

#define M200_RSW_SHADER_STENCIL_REPLACE_ENABLE_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0x00100000) >> 20 \
	)


#define M200_RSW_POLYGON_Z_OFFSET_FACTOR_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0x0000ff00) >> 8 \
	)


#define M200_RSW_POLYGON_Z_OFFSET_OFFSET_GET(dest) \
	( \
	(((u32 *)(dest))[3] & 0x000000ff) \
	)


#define M200_RSW_Z_NEAR_BOUND_GET(dest) \
	( \
	(((u32 *)(dest))[4] & 0xff000000) >> 24 | \
	(((u32 *)(dest))[4] & 0x00ff0000) >> 8 \
	)

#define M200_RSW_Z_FAR_BOUND_GET(dest) \
	( \
	(((u32 *)(dest))[4] & 0x0000ff00) >> 8 | \
	(((u32 *)(dest))[4] & 0x000000ff) << 8 \
	)

#define M200_RSW_STENCIL_FRONT_COMPARE_FUNC_GET(dest) \
	( \
	(((u32 *)(dest))[5] & 0x07000000) >> 24 \
	)

#define M200_RSW_STENCIL_FRONT_OP_IF_SFAIL_GET(dest) \
	( \
	(((u32 *)(dest))[5] & 0x38000000) >> 27 \
	)

#define M200_RSW_STENCIL_FRONT_OP_IF_ZFAIL_GET(dest) \
	( \
	(((u32 *)(dest))[5] & 0xc0000000) >> 30 | \
	(((u32 *)(dest))[5] & 0x00010000) >> 14 \
	)

#define M200_RSW_STENCIL_FRONT_OP_IF_ZPASS_GET(dest) \
	( \
	(((u32 *)(dest))[5] & 0x000e0000) >> 17 \
	)

#define M200_RSW_STENCIL_FRONT_REF_VALUE_GET(dest) \
	( \
	(((u32 *)(dest))[5] & 0x0000ff00) >> 8 \
	)

#define M200_RSW_STENCIL_FRONT_OP_MASK_GET(dest) \
	( \
	(((u32 *)(dest))[5] & 0x000000ff) \
	)


#define M200_RSW_STENCIL_BACK_COMPARE_FUNC_GET(dest) \
    ( \
    (((u32 *)(dest))[6] & 0x07000000) >> 24 \
    )


#define M200_RSW_STENCIL_BACK_OP_IF_SFAIL_GET(dest) \
    ( \
    (((u32 *)(dest))[6] & 0x38000000) >> 27 \
    )


#define M200_RSW_STENCIL_BACK_OP_IF_ZFAIL_GET(dest) \
	( \
	(((u32 *)(dest))[6] & 0xc0000000) >> 30 | \
	(((u32 *)(dest))[6] & 0x00010000) >> 14 \
	)

#define M200_RSW_STENCIL_BACK_OP_IF_ZPASS_GET(dest) \
    ( \
    (((u32 *)(dest))[6] & 0x000e0000) >> 17 \
    )


#define M200_RSW_STENCIL_BACK_REF_VALUE_GET(dest) \
    ( \
    (((u32 *)(dest))[6] & 0x0000ff00) >> 8 \
    )


#define M200_RSW_STENCIL_BACK_OP_MASK_GET(dest) \
    ( \
    (((u32 *)(dest))[6] & 0x000000ff) \
    )



#define M200_RSW_STENCIL_FRONT_WRITE_MASK_GET(dest) \
    ( \
    (((u32 *)(dest))[7] & 0xff000000) >> 24 \
    )


#define M200_RSW_STENCIL_BACK_WRITE_MASK_GET(dest) \
    ( \
    (((u32 *)(dest))[7] & 0x00ff0000) >> 16 \
    )



#define M200_RSW_ALPHA_TEST_REF_VALUE_GET(dest) \
	( \
	(((u32 *)(dest))[7] & 0x000000ff) << 8 | \
	(((u32 *)(dest))[7] & 0x0000ff00) >> 8 \
	)



#define M200_RSW_ALPHA_TEST_FUNC_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x07000000) >> 24 \
    )


#define M200_RSW_MULTISAMPLE_GRID_ENABLE_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x08000000) >> 27 \
    )


#define M200_RSW_4X_SUPERSAMPLING_ENABLE_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x10000000) >> 28 \
    )


#define M200_RSW_MULTISAMPLED_ALPHA_TEST_ENABLE_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x20000000) >> 29 \
    )


#define M200_RSW_MULTISAMPLED_Z_TEST_ENABLE_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x40000000) >> 30 \
    )


#define M200_RSW_SAMPLE_ALPHA_TO_COVERAGE_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x80000000) >> 31 \
    )


#define M200_RSW_SAMPLE_ALPHA_TO_ONE_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x00010000) >> 16 \
    )


#define M200_RSW_SAMPLE_COVERAGE_INVERT_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x00020000) >> 17 \
    )


#define M200_RSW_FLATSHADING_VERTEX_SELECTOR_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x000c0000) >> 18 \
    )


#define M200_RSW_MULTISAMPLE_WRITE_MASK_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x00f00000) >> 20 \
    )


#define M200_RSW_SAMPLE_0_REGISTER_SELECT_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x00000f00) >> 8 \
    )


#define M200_RSW_SAMPLE_1_REGISTER_SELECT_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x0000f000) >> 12 \
    )


#define M200_RSW_SAMPLE_2_REGISTER_SELECT_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x0000000f) \
    )


#define M200_RSW_SAMPLE_3_REGISTER_SELECT_GET(dest) \
    ( \
    (((u32 *)(dest))[8] & 0x000000f0) >> 4 \
    )



#define M200_RSW_FIRST_SHADER_INSTRUCTION_LENGTH_GET(dest) \
    ( \
    (((u32 *)(dest))[9] & 0x1f000000) >> 24 \
    )


#define M200_RSW_SHADER_ADDRESS_GET(dest) \
	( \
	(((u32 *)(dest))[9] & 0xc0000000) >> 24 | \
	(((u32 *)(dest))[9] & 0x00ff0000) >> 8 | \
	(((u32 *)(dest))[9] & 0x0000ff00) << 8 | \
	(((u32 *)(dest))[9] & 0x000000ff) << 24 \
	)


#define M200_RSW_VARYING0_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x07000000) >> 24 \
    )


#define M200_RSW_VARYING1_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x38000000) >> 27 \
    )


#define M200_RSW_VARYING2_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0xc0000000) >> 30 | \
    (((u32 *)(dest))[10] & 0x00010000) >> 14 \
    )


#define M200_RSW_VARYING3_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x000e0000) >> 17 \
    )


#define M200_RSW_VARYING4_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x00700000) >> 20 \
    )


#define M200_RSW_VARYING5_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x00800000) >> 23 | \
    (((u32 *)(dest))[10] & 0x00000300) >> 7 \
    )


#define M200_RSW_VARYING6_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x00001c00) >> 10 \
    )


#define M200_RSW_VARYING7_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x0000e000) >> 13 \
    )


#define M200_RSW_VARYING8_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x00000007) \
    )


#define M200_RSW_VARYING9_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x00000038) >> 3 \
    )

#define M200_RSW_VARYING10_FORMAT_BITS_0_1_GET(dest) \
    ( \
    (((u32 *)(dest))[10] & 0x000000c0) >> 6 \
    )


#define M200_RSW_UNIFORMS_REMAPPING_TABLE_LOG2_SIZE_GET(dest) \
    ( \
    (((u32 *)(dest))[11] & 0x0f000000) >> 24 \
    )


#define M200_RSW_UNIFORMS_REMAPPING_TABLE_ADDRESS_GET(dest) \
	( \
	(((u32 *)(dest))[11] & 0xf0000000) >> 24 | \
	(((u32 *)(dest))[11] & 0x00ff0000) >> 8 | \
	(((u32 *)(dest))[11] & 0x0000ff00) << 8 | \
	(((u32 *)(dest))[11] & 0x000000ff) << 24 \
	)


#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_LOG2_SIZE_GET(dest) \
    ( \
    (((u32 *)(dest))[12] & 0x0f000000) >> 24 \
    )


#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_ADDRESS_GET(dest) \
	( \
	(((u32 *)(dest))[12] & 0xf0000000) >> 24 | \
	(((u32 *)(dest))[12] & 0x00ff0000) >> 8 | \
	(((u32 *)(dest))[12] & 0x0000ff00) << 8 | \
	(((u32 *)(dest))[12] & 0x000000ff) << 24 \
	)

#define M200_RSW_PER_VERTEX_VARYING_BLOCK_SIZE_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x1f000000) >> 24 \
    )



#define M200_RSW_HINT_FETCH_TEX_DESCRIPTOR_REMAPPING_TABLE_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x20000000) >> 29 \
    )


#define M200_RSW_HINT_NO_SHADER_PRESENT_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x40000000) >> 30 \
    )


#define M200_RSW_HINT_FETCH_SHADER_UNIFORMS_REMAPPING_TABLE_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x80000000) >> 31 \
    )


#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_TEST_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x00010000) >> 16 \
    )



#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_UPDATE_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x00020000) >> 17 \
    )



#define M200_RSW_HINT_SHADER_CONTAINS_DISCARD_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x00040000) >> 18 \
    )


#define M200_RSW_HINT_SHADER_LACKS_RENDEZVOUS_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x00080000) >> 19 \
    )


#define M200_RSW_FORWARD_PIXEL_KILL_PERMISSIBLE_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x00100000) >> 20 \
    )


#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_SIZE_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x00c00000) >> 22 | \
    (((u32 *)(dest))[13] & 0x0000ff00) >> 6 | \
    (((u32 *)(dest))[13] & 0x0000000f) << 10 \
    )


#define M200_RSW_REGISTER_SELECT_FOR_Cs2_GET(dest) \
    ( \
    (((u32 *)(dest))[13] & 0x000000f0) >> 4 \
    )



#define M200_RSW_STENCIL_TAG_BITS_GET(dest) \
    ( \
    (((u32 *)(dest))[14] & 0x0f000000) >> 24 \
    )


#define M200_RSW_STENCIL_CLEAR_TAG_GET(dest) \
    ( \
    (((u32 *)(dest))[14] & 0xf0000000) >> 28 | \
    (((u32 *)(dest))[14] & 0x000f0000) >> 12 \
    )


#define M200_RSW_POLYGON_ORIENTATION_FLAG_GET(dest) \
    ( \
    (((u32 *)(dest))[14] & 0x00100000) >> 20 \
    )


#define M200_RSW_DITHERING_ENABLE_GET(dest) \
    ( \
    (((u32 *)(dest))[14] & 0x00200000) >> 21 \
    )


#define M200_RSW_ROP4_ENABLE_GET(dest) \
    ( \
    (((u32 *)(dest))[14] & 0x00400000) >> 22 \
    )


#define M200_RSW_UNIFORMS_REMAPPING_TABLE_SIZE_GET(dest) \
    ( \
    (((u32 *)(dest))[14] & 0x0000ff00) >> 8 | \
    (((u32 *)(dest))[14] & 0x000000ff) << 8 \
    )


#define M200_RSW_VARYING10_FORMAT_BIT_2_GET(dest) \
    ( \
    (((u32 *)(dest))[15] & 0x01000000) >> 24 \
    )


#define M200_RSW_VARYING11_FORMAT_GET(dest) \
    ( \
    (((u32 *)(dest))[15] & 0x0e000000) >> 25 \
    )


#define M200_RSW_VARYINGS_BASE_ADDRESS_GET(dest) \
	( \
	(((u32 *)(dest))[15] & 0xf0000000) >> 24 | \
	(((u32 *)(dest))[15] & 0x00ff0000) >> 8 | \
	(((u32 *)(dest))[15] & 0x0000ff00) << 8 | \
	(((u32 *)(dest))[15] & 0x000000ff) << 24 \
	)


#else


#define M200_RSW_CONSTANT_BLEND_COLOR_BLUE_SET(dest, value) do { \
	((u32 *)(dest))[0] &= ~(0xffff << 0); \
	((u32 *)(dest))[0] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_CONSTANT_BLEND_COLOR_GREEN_SET(dest, value) do { \
	((u32 *)(dest))[0] &= ~(0xffff << 16); \
	((u32 *)(dest))[0] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_CONSTANT_BLEND_COLOR_RED_SET(dest, value) do { \
	((u32 *)(dest))[1] &= ~(0xffff << 0); \
	((u32 *)(dest))[1] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_CONSTANT_BLEND_COLOR_ALPHA_SET(dest, value) do { \
	((u32 *)(dest))[1] &= ~(0xffff << 16); \
	((u32 *)(dest))[1] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_RGB_BLEND_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x7 << 0); \
	((u32 *)(dest))[2] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_ALPHA_BLEND_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x7 << 3); \
	((u32 *)(dest))[2] ^= ((value) << 3); \
	}while(0);
#define M200_RSW_RGB_LOGIC_OP_TRUTH_TABLE_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0xf << 6); \
	((u32 *)(dest))[2] ^= ((value) << 6); \
	}while(0);
#define M200_RSW_RGB_S_SOURCE_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x7 << 6); \
	((u32 *)(dest))[2] ^= ((value) << 6); \
	}while(0);
#define M200_RSW_RGB_S_SOURCE_1_M_X_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 9); \
	((u32 *)(dest))[2] ^= ((value) << 9); \
	}while(0);
#define M200_RSW_RGB_S_SOURCE_ALPHA_EXPAND_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 10); \
	((u32 *)(dest))[2] ^= ((value) << 10); \
	}while(0);
#define M200_RSW_RGB_D_SOURCE_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x7 << 11); \
	((u32 *)(dest))[2] ^= ((value) << 11); \
	}while(0);
#define M200_RSW_RGB_D_SOURCE_1_M_X_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 14); \
	((u32 *)(dest))[2] ^= ((value) << 14); \
	}while(0);
#define M200_RSW_RGB_D_SOURCE_ALPHA_EXPAND_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 15); \
	((u32 *)(dest))[2] ^= ((value) << 15); \
	}while(0);
#define M200_RSW_ALPHA_LOGIC_OP_TRUTH_TABLE_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0xf << 16); \
	((u32 *)(dest))[2] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_ALPHA_S_SOURCE_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x7 << 16); \
	((u32 *)(dest))[2] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_ALPHA_S_SOURCE_1_M_X_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 19); \
	((u32 *)(dest))[2] ^= ((value) << 19); \
	}while(0);
#define M200_RSW_ALPHA_D_SOURCE_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x7 << 20); \
	((u32 *)(dest))[2] ^= ((value) << 20); \
	}while(0);
#define M200_RSW_ALPHA_D_SOURCE_1_M_X_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 23); \
	((u32 *)(dest))[2] ^= ((value) << 23); \
	}while(0);
#define M200_RSW_RGB_INPUT_COLOR_CLAMP_0_1_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 24); \
	((u32 *)(dest))[2] ^= ((value) << 24); \
	}while(0);
#define M200_RSW_ALPHA_INPUT_COLOR_CLAMP_0_1_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 25); \
	((u32 *)(dest))[2] ^= ((value) << 25); \
	}while(0);
#define M200_RSW_RGB_RESULT_COLOR_CLAMP_0_1_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 26); \
	((u32 *)(dest))[2] ^= ((value) << 26); \
	}while(0);
#define M200_RSW_ALPHA_RESULT_COLOR_CLAMP_0_1_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 27); \
	((u32 *)(dest))[2] ^= ((value) << 27); \
	}while(0);
#define M200_RSW_R_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 28); \
	((u32 *)(dest))[2] ^= ((value) << 28); \
	}while(0);
#define M200_RSW_G_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 29); \
	((u32 *)(dest))[2] ^= ((value) << 29); \
	}while(0);
#define M200_RSW_B_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 30); \
	((u32 *)(dest))[2] ^= ((value) << 30); \
	}while(0);
#define M200_RSW_A_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1 << 31); \
	((u32 *)(dest))[2] ^= ((value) << 31); \
	}while(0);
#define M200_RSW_ABGR_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0xf << 28); \
	((u32 *)(dest))[2] ^= ((value) << 28); \
	}while(0);
#define M200_RSW_RGB_S_SOURCE_COMBINED_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1f << 6); \
	((u32 *)(dest))[2] ^= ((value) << 6); \
	}while(0);
#define M200_RSW_RGB_D_SOURCE_COMBINED_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0x1f << 11); \
	((u32 *)(dest))[2] ^= ((value) << 11); \
	}while(0);
#define M200_RSW_ALPHA_S_SOURCE_COMBINED_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0xf << 16); \
	((u32 *)(dest))[2] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_ALPHA_D_SOURCE_COMBINED_SET(dest, value) do { \
	((u32 *)(dest))[2] &= ~(0xf << 20); \
	((u32 *)(dest))[2] ^= ((value) << 20); \
	}while(0);
#define M200_RSW_Z_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0x1 << 0); \
	((u32 *)(dest))[3] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_Z_COMPARE_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0x7 << 1); \
	((u32 *)(dest))[3] ^= ((value) << 1); \
	}while(0);
#define M200_RSW_Z_NEAR_DEPTH_BOUND_OP_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0x1 << 4); \
	((u32 *)(dest))[3] ^= ((value) << 4); \
	}while(0);
#define M200_RSW_Z_FAR_DEPTH_BOUND_OP_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0x1 << 5); \
	((u32 *)(dest))[3] ^= ((value) << 5); \
	}while(0);
#define M200_RSW_Z_STENCIL_VALUE_REGISTER_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0xf << 6); \
	((u32 *)(dest))[3] ^= ((value) << 6); \
	}while(0);
#define M200_RSW_DST_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0x1 << 10); \
	((u32 *)(dest))[3] ^= ((value) << 10); \
	}while(0);
#define M200_RSW_SHADER_Z_REPLACE_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0x1 << 11); \
	((u32 *)(dest))[3] ^= ((value) << 11); \
	}while(0);
#define M200_RSW_SHADER_STENCIL_REPLACE_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0x1 << 12); \
	((u32 *)(dest))[3] ^= ((value) << 12); \
	}while(0);
#define M200_RSW_POLYGON_Z_OFFSET_FACTOR_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0xff << 16); \
	((u32 *)(dest))[3] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_POLYGON_Z_OFFSET_OFFSET_SET(dest, value) do { \
	((u32 *)(dest))[3] &= ~(0xff << 24); \
	((u32 *)(dest))[3] ^= ((value) << 24); \
	}while(0);
#define M200_RSW_Z_NEAR_BOUND_SET(dest, value) do { \
	((u32 *)(dest))[4] &= ~(0xffff << 0); \
	((u32 *)(dest))[4] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_Z_FAR_BOUND_SET(dest, value) do { \
	((u32 *)(dest))[4] &= ~(0xffff << 16); \
	((u32 *)(dest))[4] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_STENCIL_FRONT_COMPARE_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[5] &= ~(0x7 << 0); \
	((u32 *)(dest))[5] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_STENCIL_FRONT_OP_IF_SFAIL_SET(dest, value) do { \
	((u32 *)(dest))[5] &= ~(0x7 << 3); \
	((u32 *)(dest))[5] ^= ((value) << 3); \
	}while(0);
#define M200_RSW_STENCIL_FRONT_OP_IF_ZFAIL_SET(dest, value) do { \
	((u32 *)(dest))[5] &= ~(0x7 << 6); \
	((u32 *)(dest))[5] ^= ((value) << 6); \
	}while(0);
#define M200_RSW_STENCIL_FRONT_OP_IF_ZPASS_SET(dest, value) do { \
	((u32 *)(dest))[5] &= ~(0x7 << 9); \
	((u32 *)(dest))[5] ^= ((value) << 9); \
	}while(0);
#define M200_RSW_STENCIL_FRONT_REF_VALUE_SET(dest, value) do { \
	((u32 *)(dest))[5] &= ~(0xff << 16); \
	((u32 *)(dest))[5] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_STENCIL_FRONT_OP_MASK_SET(dest, value) do { \
	((u32 *)(dest))[5] &= ~(0xff << 24); \
	((u32 *)(dest))[5] ^= ((value) << 24); \
	}while(0);
#define M200_RSW_STENCIL_BACK_COMPARE_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[6] &= ~(0x7 << 0); \
	((u32 *)(dest))[6] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_STENCIL_BACK_OP_IF_SFAIL_SET(dest, value) do { \
	((u32 *)(dest))[6] &= ~(0x7 << 3); \
	((u32 *)(dest))[6] ^= ((value) << 3); \
	}while(0);
#define M200_RSW_STENCIL_BACK_OP_IF_ZFAIL_SET(dest, value) do { \
	((u32 *)(dest))[6] &= ~(0x7 << 6); \
	((u32 *)(dest))[6] ^= ((value) << 6); \
	}while(0);
#define M200_RSW_STENCIL_BACK_OP_IF_ZPASS_SET(dest, value) do { \
	((u32 *)(dest))[6] &= ~(0x7 << 9); \
	((u32 *)(dest))[6] ^= ((value) << 9); \
	}while(0);
#define M200_RSW_STENCIL_BACK_REF_VALUE_SET(dest, value) do { \
	((u32 *)(dest))[6] &= ~(0xff << 16); \
	((u32 *)(dest))[6] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_STENCIL_BACK_OP_MASK_SET(dest, value) do { \
	((u32 *)(dest))[6] &= ~(0xff << 24); \
	((u32 *)(dest))[6] ^= ((value) << 24); \
	}while(0);
#define M200_RSW_STENCIL_FRONT_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[7] &= ~(0xff << 0); \
	((u32 *)(dest))[7] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_STENCIL_BACK_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[7] &= ~(0xff << 8); \
	((u32 *)(dest))[7] ^= ((value) << 8); \
	}while(0);
#define M200_RSW_ALPHA_TEST_REF_VALUE_SET(dest, value) do { \
	((u32 *)(dest))[7] &= ~(0xffff << 16); \
	((u32 *)(dest))[7] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_ALPHA_TEST_FUNC_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0x7 << 0); \
	((u32 *)(dest))[8] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_MULTISAMPLE_GRID_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0x1 << 3); \
	((u32 *)(dest))[8] ^= ((value) << 3); \
	}while(0);
#define M200_RSW_4X_SUPERSAMPLING_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0x1 << 4); \
	((u32 *)(dest))[8] ^= ((value) << 4); \
	}while(0);
#define M200_RSW_MULTISAMPLED_ALPHA_TEST_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0x1 << 5); \
	((u32 *)(dest))[8] ^= ((value) << 5); \
	}while(0);
#define M200_RSW_MULTISAMPLED_Z_TEST_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0x1 << 6); \
	((u32 *)(dest))[8] ^= ((value) << 6); \
	}while(0);
#define M200_RSW_SAMPLE_ALPHA_TO_COVERAGE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0x1 << 7); \
	((u32 *)(dest))[8] ^= ((value) << 7); \
	}while(0);
#define M200_RSW_SAMPLE_ALPHA_TO_ONE_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0x1 << 8); \
	((u32 *)(dest))[8] ^= ((value) << 8); \
	}while(0);
#define M200_RSW_SAMPLE_COVERAGE_INVERT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0x1 << 9); \
	((u32 *)(dest))[8] ^= ((value) << 9); \
	}while(0);
#define M200_RSW_FLATSHADING_VERTEX_SELECTOR_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0x3 << 10); \
	((u32 *)(dest))[8] ^= ((value) << 10); \
	}while(0);
#define M200_RSW_MULTISAMPLE_WRITE_MASK_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0xf << 12); \
	((u32 *)(dest))[8] ^= ((value) << 12); \
	}while(0);
#define M200_RSW_SAMPLE_0_REGISTER_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0xf << 16); \
	((u32 *)(dest))[8] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_SAMPLE_1_REGISTER_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0xf << 20); \
	((u32 *)(dest))[8] ^= ((value) << 20); \
	}while(0);
#define M200_RSW_SAMPLE_2_REGISTER_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0xf << 24); \
	((u32 *)(dest))[8] ^= ((value) << 24); \
	}while(0);
#define M200_RSW_SAMPLE_3_REGISTER_SELECT_SET(dest, value) do { \
	((u32 *)(dest))[8] &= ~(0xf << 28); \
	((u32 *)(dest))[8] ^= ((value) << 28); \
	}while(0);
#define M200_RSW_FIRST_SHADER_INSTRUCTION_LENGTH_SET(dest, value) do { \
	((u32 *)(dest))[9] &= ~(0x1f << 0); \
	((u32 *)(dest))[9] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_SHADER_ADDRESS_SET(dest, value) do { \
	((u32 *)(dest))[9] &= ~(0xffffffc0 << 0); \
	((u32 *)(dest))[9] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_VARYING0_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 0); \
	((u32 *)(dest))[10] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_VARYING1_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 3); \
	((u32 *)(dest))[10] ^= ((value) << 3); \
	}while(0);
#define M200_RSW_VARYING2_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 6); \
	((u32 *)(dest))[10] ^= ((value) << 6); \
	}while(0);
#define M200_RSW_VARYING3_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 9); \
	((u32 *)(dest))[10] ^= ((value) << 9); \
	}while(0);
#define M200_RSW_VARYING4_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 12); \
	((u32 *)(dest))[10] ^= ((value) << 12); \
	}while(0);
#define M200_RSW_VARYING5_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 15); \
	((u32 *)(dest))[10] ^= ((value) << 15); \
	}while(0);
#define M200_RSW_VARYING6_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 18); \
	((u32 *)(dest))[10] ^= ((value) << 18); \
	}while(0);
#define M200_RSW_VARYING7_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 21); \
	((u32 *)(dest))[10] ^= ((value) << 21); \
	}while(0);
#define M200_RSW_VARYING8_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 24); \
	((u32 *)(dest))[10] ^= ((value) << 24); \
	}while(0);
#define M200_RSW_VARYING9_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x7 << 27); \
	((u32 *)(dest))[10] ^= ((value) << 27); \
	}while(0);
#define M200_RSW_VARYING10_FORMAT_BITS_0_1_SET(dest, value) do { \
	((u32 *)(dest))[10] &= ~(0x3 << 30); \
	((u32 *)(dest))[10] ^= ((value) << 30); \
	}while(0);
#define M200_RSW_UNIFORMS_REMAPPING_TABLE_LOG2_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[11] &= ~(0xf << 0); \
	((u32 *)(dest))[11] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_UNIFORMS_REMAPPING_TABLE_ADDRESS_SET(dest, value) do { \
	((u32 *)(dest))[11] &= ~(0xfffffff0 << 0); \
	((u32 *)(dest))[11] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_LOG2_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[12] &= ~(0xf << 0); \
	((u32 *)(dest))[12] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_ADDRESS_SET(dest, value) do { \
	((u32 *)(dest))[12] &= ~(0xfffffff0 << 0); \
	((u32 *)(dest))[12] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_PER_VERTEX_VARYING_BLOCK_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x1f << 0); \
	((u32 *)(dest))[13] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_HINT_FETCH_TEX_DESCRIPTOR_REMAPPING_TABLE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x1 << 5); \
	((u32 *)(dest))[13] ^= ((value) << 5); \
	}while(0);
#define M200_RSW_HINT_NO_SHADER_PRESENT_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x1 << 6); \
	((u32 *)(dest))[13] ^= ((value) << 6); \
	}while(0);
#define M200_RSW_HINT_FETCH_SHADER_UNIFORMS_REMAPPING_TABLE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x1 << 7); \
	((u32 *)(dest))[13] ^= ((value) << 7); \
	}while(0);
#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_TEST_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x1 << 8); \
	((u32 *)(dest))[13] ^= ((value) << 8); \
	}while(0);
#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_UPDATE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x1 << 9); \
	((u32 *)(dest))[13] ^= ((value) << 9); \
	}while(0);
#define M200_RSW_HINT_SHADER_CONTAINS_DISCARD_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x1 << 10); \
	((u32 *)(dest))[13] ^= ((value) << 10); \
	}while(0);
#define M200_RSW_HINT_SHADER_LACKS_RENDEZVOUS_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x1 << 11); \
	((u32 *)(dest))[13] ^= ((value) << 11); \
	}while(0);
#define M200_RSW_FORWARD_PIXEL_KILL_PERMISSIBLE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x1 << 12); \
	((u32 *)(dest))[13] ^= ((value) << 12); \
	}while(0);
#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0x3fff << 14); \
	((u32 *)(dest))[13] ^= ((value) << 14); \
	}while(0);
#define M200_RSW_REGISTER_SELECT_FOR_Cs2_SET(dest, value) do { \
	((u32 *)(dest))[13] &= ~(0xf << 28); \
	((u32 *)(dest))[13] ^= ((value) << 28); \
	}while(0);
#define M200_RSW_STENCIL_TAG_BITS_SET(dest, value) do { \
	((u32 *)(dest))[14] &= ~(0xf << 0); \
	((u32 *)(dest))[14] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_STENCIL_CLEAR_TAG_SET(dest, value) do { \
	((u32 *)(dest))[14] &= ~(0xff << 4); \
	((u32 *)(dest))[14] ^= ((value) << 4); \
	}while(0);
#define M200_RSW_POLYGON_ORIENTATION_FLAG_SET(dest, value) do { \
	((u32 *)(dest))[14] &= ~(0x1 << 12); \
	((u32 *)(dest))[14] ^= ((value) << 12); \
	}while(0);
#define M200_RSW_DITHERING_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[14] &= ~(0x1 << 13); \
	((u32 *)(dest))[14] ^= ((value) << 13); \
	}while(0);
#define M200_RSW_ROP4_ENABLE_SET(dest, value) do { \
	((u32 *)(dest))[14] &= ~(0x1 << 14); \
	((u32 *)(dest))[14] ^= ((value) << 14); \
	}while(0);
#define M200_RSW_UNIFORMS_REMAPPING_TABLE_SIZE_SET(dest, value) do { \
	((u32 *)(dest))[14] &= ~(0xffff << 16); \
	((u32 *)(dest))[14] ^= ((value) << 16); \
	}while(0);
#define M200_RSW_VARYING10_FORMAT_BIT_2_SET(dest, value) do { \
	((u32 *)(dest))[15] &= ~(0x1 << 0); \
	((u32 *)(dest))[15] ^= ((value) << 0); \
	}while(0);
#define M200_RSW_VARYING11_FORMAT_SET(dest, value) do { \
	((u32 *)(dest))[15] &= ~(0x7 << 1); \
	((u32 *)(dest))[15] ^= ((value) << 1); \
	}while(0);
#define M200_RSW_VARYINGS_BASE_ADDRESS_SET(dest, value) do { \
	((u32 *)(dest))[15] &= ~(0xfffffff0 << 0); \
	((u32 *)(dest))[15] ^= ((value) << 0); \
	}while(0);




/* getters */
#define M200_RSW_CONSTANT_BLEND_COLOR_BLUE_GET(dest) \
	( \
		(((u32 *)(dest))[0] >> 0) & 0xffff \
	)
#define M200_RSW_CONSTANT_BLEND_COLOR_GREEN_GET(dest) \
	( \
		(((u32 *)(dest))[0] >> 16) & 0xffff \
	)
#define M200_RSW_CONSTANT_BLEND_COLOR_RED_GET(dest) \
	( \
		(((u32 *)(dest))[1] >> 0) & 0xffff \
	)
#define M200_RSW_CONSTANT_BLEND_COLOR_ALPHA_GET(dest) \
	( \
		(((u32 *)(dest))[1] >> 16) & 0xffff \
	)
#define M200_RSW_RGB_BLEND_FUNC_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 0) & 0x7 \
	)
#define M200_RSW_ALPHA_BLEND_FUNC_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 3) & 0x7 \
	)
#define M200_RSW_RGB_LOGIC_OP_TRUTH_TABLE_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 6) & 0xf \
	)
#define M200_RSW_RGB_S_SOURCE_SELECT_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 6) & 0x7 \
	)
#define M200_RSW_RGB_S_SOURCE_1_M_X_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 9) & 0x1 \
	)
#define M200_RSW_RGB_S_SOURCE_ALPHA_EXPAND_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 10) & 0x1 \
	)
#define M200_RSW_RGB_D_SOURCE_SELECT_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 11) & 0x7 \
	)
#define M200_RSW_RGB_D_SOURCE_1_M_X_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 14) & 0x1 \
	)
#define M200_RSW_RGB_D_SOURCE_ALPHA_EXPAND_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 15) & 0x1 \
	)
#define M200_RSW_ALPHA_LOGIC_OP_TRUTH_TABLE_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 16) & 0xf \
	)
#define M200_RSW_ALPHA_S_SOURCE_SELECT_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 16) & 0x7 \
	)
#define M200_RSW_ALPHA_S_SOURCE_1_M_X_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 19) & 0x1 \
	)
#define M200_RSW_ALPHA_D_SOURCE_SELECT_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 20) & 0x7 \
	)
#define M200_RSW_ALPHA_D_SOURCE_1_M_X_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 23) & 0x1 \
	)
#define M200_RSW_RGB_INPUT_COLOR_CLAMP_0_1_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 24) & 0x1 \
	)
#define M200_RSW_ALPHA_INPUT_COLOR_CLAMP_0_1_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 25) & 0x1 \
	)
#define M200_RSW_RGB_RESULT_COLOR_CLAMP_0_1_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 26) & 0x1 \
	)
#define M200_RSW_ALPHA_RESULT_COLOR_CLAMP_0_1_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 27) & 0x1 \
	)
#define M200_RSW_R_WRITE_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 28) & 0x1 \
	)
#define M200_RSW_G_WRITE_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 29) & 0x1 \
	)
#define M200_RSW_B_WRITE_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 30) & 0x1 \
	)
#define M200_RSW_A_WRITE_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 31) & 0x1 \
	)
#define M200_RSW_ABGR_WRITE_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 28) & 0xf \
	)
#define M200_RSW_RGB_S_SOURCE_COMBINED_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 6) & 0x1f \
	)
#define M200_RSW_RGB_D_SOURCE_COMBINED_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 11) & 0x1f \
	)
#define M200_RSW_ALPHA_S_SOURCE_COMBINED_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 16) & 0xf \
	)
#define M200_RSW_ALPHA_D_SOURCE_COMBINED_GET(dest) \
	( \
		(((u32 *)(dest))[2] >> 20) & 0xf \
	)
#define M200_RSW_Z_WRITE_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 0) & 0x1 \
	)
#define M200_RSW_Z_COMPARE_FUNC_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 1) & 0x7 \
	)
#define M200_RSW_Z_NEAR_DEPTH_BOUND_OP_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 4) & 0x1 \
	)
#define M200_RSW_Z_FAR_DEPTH_BOUND_OP_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 5) & 0x1 \
	)
#define M200_RSW_Z_STENCIL_VALUE_REGISTER_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 6) & 0xf \
	)
#define M200_RSW_DST_ENABLE_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 10) & 0x1 \
	)
#define M200_RSW_SHADER_Z_REPLACE_ENABLE_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 11) & 0x1 \
	)
#define M200_RSW_SHADER_STENCIL_REPLACE_ENABLE_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 12) & 0x1 \
	)
#define M200_RSW_POLYGON_Z_OFFSET_FACTOR_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 16) & 0xff \
	)
#define M200_RSW_POLYGON_Z_OFFSET_OFFSET_GET(dest) \
	( \
		(((u32 *)(dest))[3] >> 24) & 0xff \
	)
#define M200_RSW_Z_NEAR_BOUND_GET(dest) \
	( \
		(((u32 *)(dest))[4] >> 0) & 0xffff \
	)
#define M200_RSW_Z_FAR_BOUND_GET(dest) \
	( \
		(((u32 *)(dest))[4] >> 16) & 0xffff \
	)
#define M200_RSW_STENCIL_FRONT_COMPARE_FUNC_GET(dest) \
	( \
		(((u32 *)(dest))[5] >> 0) & 0x7 \
	)
#define M200_RSW_STENCIL_FRONT_OP_IF_SFAIL_GET(dest) \
	( \
		(((u32 *)(dest))[5] >> 3) & 0x7 \
	)
#define M200_RSW_STENCIL_FRONT_OP_IF_ZFAIL_GET(dest) \
	( \
		(((u32 *)(dest))[5] >> 6) & 0x7 \
	)
#define M200_RSW_STENCIL_FRONT_OP_IF_ZPASS_GET(dest) \
	( \
		(((u32 *)(dest))[5] >> 9) & 0x7 \
	)
#define M200_RSW_STENCIL_FRONT_REF_VALUE_GET(dest) \
	( \
		(((u32 *)(dest))[5] >> 16) & 0xff \
	)
#define M200_RSW_STENCIL_FRONT_OP_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[5] >> 24) & 0xff \
	)
#define M200_RSW_STENCIL_BACK_COMPARE_FUNC_GET(dest) \
	( \
		(((u32 *)(dest))[6] >> 0) & 0x7 \
	)
#define M200_RSW_STENCIL_BACK_OP_IF_SFAIL_GET(dest) \
	( \
		(((u32 *)(dest))[6] >> 3) & 0x7 \
	)
#define M200_RSW_STENCIL_BACK_OP_IF_ZFAIL_GET(dest) \
	( \
		(((u32 *)(dest))[6] >> 6) & 0x7 \
	)
#define M200_RSW_STENCIL_BACK_OP_IF_ZPASS_GET(dest) \
	( \
		(((u32 *)(dest))[6] >> 9) & 0x7 \
	)
#define M200_RSW_STENCIL_BACK_REF_VALUE_GET(dest) \
	( \
		(((u32 *)(dest))[6] >> 16) & 0xff \
	)
#define M200_RSW_STENCIL_BACK_OP_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[6] >> 24) & 0xff \
	)
#define M200_RSW_STENCIL_FRONT_WRITE_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[7] >> 0) & 0xff \
	)
#define M200_RSW_STENCIL_BACK_WRITE_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[7] >> 8) & 0xff \
	)
#define M200_RSW_ALPHA_TEST_REF_VALUE_GET(dest) \
	( \
		(((u32 *)(dest))[7] >> 16) & 0xffff \
	)
#define M200_RSW_ALPHA_TEST_FUNC_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 0) & 0x7 \
	)
#define M200_RSW_MULTISAMPLE_GRID_ENABLE_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 3) & 0x1 \
	)
#define M200_RSW_4X_SUPERSAMPLING_ENABLE_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 4) & 0x1 \
	)
#define M200_RSW_MULTISAMPLED_ALPHA_TEST_ENABLE_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 5) & 0x1 \
	)
#define M200_RSW_MULTISAMPLED_Z_TEST_ENABLE_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 6) & 0x1 \
	)
#define M200_RSW_SAMPLE_ALPHA_TO_COVERAGE_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 7) & 0x1 \
	)
#define M200_RSW_SAMPLE_ALPHA_TO_ONE_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 8) & 0x1 \
	)
#define M200_RSW_SAMPLE_COVERAGE_INVERT_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 9) & 0x1 \
	)
#define M200_RSW_FLATSHADING_VERTEX_SELECTOR_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 10) & 0x3 \
	)
#define M200_RSW_MULTISAMPLE_WRITE_MASK_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 12) & 0xf \
	)
#define M200_RSW_SAMPLE_0_REGISTER_SELECT_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 16) & 0xf \
	)
#define M200_RSW_SAMPLE_1_REGISTER_SELECT_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 20) & 0xf \
	)
#define M200_RSW_SAMPLE_2_REGISTER_SELECT_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 24) & 0xf \
	)
#define M200_RSW_SAMPLE_3_REGISTER_SELECT_GET(dest) \
	( \
		(((u32 *)(dest))[8] >> 28) & 0xf \
	)
#define M200_RSW_FIRST_SHADER_INSTRUCTION_LENGTH_GET(dest) \
	( \
		(((u32 *)(dest))[9] >> 0) & 0x1f \
	)
#define M200_RSW_SHADER_ADDRESS_GET(dest) \
	( \
		(((u32 *)(dest))[9] >> 0) & 0xffffffc0 \
	)
#define M200_RSW_VARYING0_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 0) & 0x7 \
	)
#define M200_RSW_VARYING1_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 3) & 0x7 \
	)
#define M200_RSW_VARYING2_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 6) & 0x7 \
	)
#define M200_RSW_VARYING3_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 9) & 0x7 \
	)
#define M200_RSW_VARYING4_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 12) & 0x7 \
	)
#define M200_RSW_VARYING5_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 15) & 0x7 \
	)
#define M200_RSW_VARYING6_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 18) & 0x7 \
	)
#define M200_RSW_VARYING7_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 21) & 0x7 \
	)
#define M200_RSW_VARYING8_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 24) & 0x7 \
	)
#define M200_RSW_VARYING9_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 27) & 0x7 \
	)
#define M200_RSW_VARYING10_FORMAT_BITS_0_1_GET(dest) \
	( \
		(((u32 *)(dest))[10] >> 30) & 0x3 \
	)
#define M200_RSW_UNIFORMS_REMAPPING_TABLE_LOG2_SIZE_GET(dest) \
	( \
		(((u32 *)(dest))[11] >> 0) & 0xf \
	)
#define M200_RSW_UNIFORMS_REMAPPING_TABLE_ADDRESS_GET(dest) \
	( \
		(((u32 *)(dest))[11] >> 0) & 0xfffffff0 \
	)
#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_LOG2_SIZE_GET(dest) \
	( \
		(((u32 *)(dest))[12] >> 0) & 0xf \
	)
#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_ADDRESS_GET(dest) \
	( \
		(((u32 *)(dest))[12] >> 0) & 0xfffffff0 \
	)
#define M200_RSW_PER_VERTEX_VARYING_BLOCK_SIZE_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 0) & 0x1f \
	)
#define M200_RSW_HINT_FETCH_TEX_DESCRIPTOR_REMAPPING_TABLE_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 5) & 0x1 \
	)
#define M200_RSW_HINT_NO_SHADER_PRESENT_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 6) & 0x1 \
	)
#define M200_RSW_HINT_FETCH_SHADER_UNIFORMS_REMAPPING_TABLE_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 7) & 0x1 \
	)
#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_TEST_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 8) & 0x1 \
	)
#define M200_RSW_ALLOW_EARLY_Z_AND_STENCIL_UPDATE_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 9) & 0x1 \
	)
#define M200_RSW_HINT_SHADER_CONTAINS_DISCARD_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 10) & 0x1 \
	)
#define M200_RSW_HINT_SHADER_LACKS_RENDEZVOUS_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 11) & 0x1 \
	)
#define M200_RSW_FORWARD_PIXEL_KILL_PERMISSIBLE_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 12) & 0x1 \
	)
#define M200_RSW_TEX_DESCRIPTOR_REMAPPING_TABLE_SIZE_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 14) & 0x3fff \
	)
#define M200_RSW_REGISTER_SELECT_FOR_Cs2_GET(dest) \
	( \
		(((u32 *)(dest))[13] >> 28) & 0xf \
	)
#define M200_RSW_STENCIL_TAG_BITS_GET(dest) \
	( \
		(((u32 *)(dest))[14] >> 0) & 0xf \
	)
#define M200_RSW_STENCIL_CLEAR_TAG_GET(dest) \
	( \
		(((u32 *)(dest))[14] >> 4) & 0xff \
	)
#define M200_RSW_POLYGON_ORIENTATION_FLAG_GET(dest) \
	( \
		(((u32 *)(dest))[14] >> 12) & 0x1 \
	)
#define M200_RSW_DITHERING_ENABLE_GET(dest) \
	( \
		(((u32 *)(dest))[14] >> 13) & 0x1 \
	)
#define M200_RSW_ROP4_ENABLE_GET(dest) \
	( \
		(((u32 *)(dest))[14] >> 14) & 0x1 \
	)
#define M200_RSW_UNIFORMS_REMAPPING_TABLE_SIZE_GET(dest) \
	( \
		(((u32 *)(dest))[14] >> 16) & 0xffff \
	)
#define M200_RSW_VARYING10_FORMAT_BIT_2_GET(dest) \
	( \
		(((u32 *)(dest))[15] >> 0) & 0x1 \
	)
#define M200_RSW_VARYING11_FORMAT_GET(dest) \
	( \
		(((u32 *)(dest))[15] >> 1) & 0x7 \
	)
#define M200_RSW_VARYINGS_BASE_ADDRESS_GET(dest) \
	( \
		(((u32 *)(dest))[15] >> 0) & 0xfffffff0 \
	)


#endif

#endif /* _M200_RSW_H_ */
