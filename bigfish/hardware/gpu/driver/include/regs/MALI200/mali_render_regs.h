/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2010, 2012-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/* previously found in mali_pp_regs.h in basedriver and m200_regs.h in shared */

#ifndef _MALI_200_REGS_H_
#define _MALI_200_REGS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef u32 mali_reg_value;

typedef enum mali_reg_id
{
	M200_FRAME_REG_REND_LIST_ADDR                   = 0x000,
	M200_FRAME_REG_REND_RSW_BASE                    = 0x001,
	M200_FRAME_REG_REND_VERTEX_BASE                 = 0x002,
	M200_FRAME_REG_FEATURE_ENABLE                   = 0x003,
	M200_FRAME_REG_Z_CLEAR_VALUE                    = 0x004,
	M200_FRAME_REG_STENCIL_CLEAR_VALUE              = 0x005,
	M200_FRAME_REG_ABGR_CLEAR_VALUE_0               = 0x006,
	M200_FRAME_REG_ABGR_CLEAR_VALUE_1               = 0x007,
	M200_FRAME_REG_ABGR_CLEAR_VALUE_2               = 0x008,
	M200_FRAME_REG_ABGR_CLEAR_VALUE_3               = 0x009,
	M200_FRAME_REG_BOUNDING_BOX_LEFT_RIGHT          = 0x00A,
	M200_FRAME_REG_BOUNDING_BOX_BOTTOM              = 0x00B,
	M200_FRAME_REG_FS_STACK_ADDR                    = 0x00C,
	M200_FRAME_REG_FS_STACK_SIZE_AND_INIT_VAL       = 0x00D,
	M200_FRAME_REG_REND_CLIP_VERTEX_BASE            = 0x00E,
	M200_FRAME_REG_REND_FIRST_CLIP_VERTEX           = 0x00F,
	M200_FRAME_REG_ORIGIN_OFFSET_X                  = 0x010,
	M200_FRAME_REG_ORIGIN_OFFSET_Y                  = 0x011,
	M200_FRAME_REG_SUBPIXEL_SPECIFIER               = 0x012,
	M200_FRAME_REG_TIEBREAK_MODE                    = 0x013,
	M400_FRAME_REG_PLIST_CONFIG                     = 0x014,
	M400_FRAME_REG_SCALING_CONFIG                   = 0x015,
	M400_FRAME_REG_TILEBUFFER_BITS                  = 0x016,
	M200_WB0_REG_SOURCE_SELECT                      = 0x040,
	M200_WB0_REG_TARGET_ADDR                        = 0x041,
	M200_WB0_REG_TARGET_PIXEL_FORMAT                = 0x042,
	M200_WB0_REG_TARGET_AA_FORMAT                   = 0x043,
	M200_WB0_REG_TARGET_LAYOUT                      = 0x044,
	M200_WB0_REG_TARGET_SCANLINE_LENGTH             = 0x045,
	M200_WB0_REG_TARGET_FLAGS                       = 0x046,
	M200_WB0_REG_MRT_ENABLE                         = 0x047,
	M200_WB0_REG_MRT_OFFSET                         = 0x048,
	M200_WB0_REG_GLOBAL_TEST_ENABLE                 = 0x049,
	M200_WB0_REG_GLOBAL_TEST_REF_VALUE              = 0x04A,
	M200_WB0_REG_GLOBAL_TEST_CMP_FUNC               = 0x04B,

	M200_WB1_REG_SOURCE_SELECT                      = 0x080,
	M200_WB1_REG_TARGET_ADDR                        = 0x081,
	M200_WB1_REG_TARGET_PIXEL_FORMAT                = 0x082,
	M200_WB1_REG_TARGET_AA_FORMAT                   = 0x083,
	M200_WB1_REG_TARGET_LAYOUT                      = 0x084,
	M200_WB1_REG_TARGET_SCANLINE_LENGTH             = 0x085,
	M200_WB1_REG_TARGET_FLAGS                       = 0x086,
	M200_WB1_REG_MRT_ENABLE                         = 0x087,
	M200_WB1_REG_MRT_OFFSET                         = 0x088,
	M200_WB1_REG_GLOBAL_TEST_ENABLE                 = 0x089,
	M200_WB1_REG_GLOBAL_TEST_REF_VALUE              = 0x08A,
	M200_WB1_REG_GLOBAL_TEST_CMP_FUNC               = 0x08B,

	M200_WB2_REG_SOURCE_SELECT                      = 0x0C0,
	M200_WB2_REG_TARGET_ADDR                        = 0x0C1,
	M200_WB2_REG_TARGET_PIXEL_FORMAT                = 0x0C2,
	M200_WB2_REG_TARGET_AA_FORMAT                   = 0x0C3,
	M200_WB2_REG_TARGET_LAYOUT                      = 0x0C4,
	M200_WB2_REG_TARGET_SCANLINE_LENGTH             = 0x0C5,
	M200_WB2_REG_TARGET_FLAGS                       = 0x0C6,
	M200_WB2_REG_MRT_ENABLE                         = 0x0C7,
	M200_WB2_REG_MRT_OFFSET                         = 0x0C8,
	M200_WB2_REG_GLOBAL_TEST_ENABLE                 = 0x0C9,
	M200_WB2_REG_GLOBAL_TEST_REF_VALUE              = 0x0CA,
	M200_WB2_REG_GLOBAL_TEST_CMP_FUNC               = 0x0CB
} mali_reg_id;


enum m200_feature
{
	M200_FEATURE_FP_TILEBUF_ENABLE = (1 << 0),
	M200_FEATURE_EARLYZ_ENABLE     = (1 << 1),
	M200_FEATURE_IGNORE_CLEAR_BITS = (1 << 2),
	M200_FEATURE_EARLYZ_DISABLE1   = (1 << 3),
	M200_FEATURE_EARLYZ_DISABLE2   = (1 << 4),
	M200_FEATURE_ORIGIN_LOWER_LEFT = (1 << 5)
};

enum m400_scaling_config
{
	M400_SCALING_CONFIG_POINT_AND_LINE_SCALE_ENABLE = (1 << 0),
	M400_SCALING_CONFIG_DITHERING_SCALE_ENABLE      = (1 << 1),
	M400_SCALING_CONFIG_FRAGCOORD_SCALE_ENABLE      = (1 << 2),
	M400_SCALING_CONFIG_DERIVATIVE_SCALE_ENABLE     = (1 << 3),
	M400_SCALING_CONFIG_FLIP_POINT_SPRITES          = (1 << 8),
	M400_SCALING_CONFIG_FLIP_DITHERING_MATRIX       = (1 << 9),
	M400_SCALING_CONFIG_FLIP_FRAGCOORD              = (1 << 10),
	M400_SCALING_CONFIG_FLIP_DERIVATIVE_Y           = (1 << 11)
};

/**
 * This enum is used when writing to a m200_reg typed array of writeback registers.
 * They are offsets in 32-bit units from the base address of a writeback unit,
 * not the actual hardware addresses. Use m200_wb_unit + m200_wbx_reg_offset
 * to calculate the complete address offset for a certain unit.
 */
enum m200_wbx_reg_offset
{
	/* Same names and order as in P00086 7.2 Writeback registers prefixed with
	   M200_WB_REG */
	M200_WBx_REG_SOURCE_SELECT         = 0x000,
	M200_WBx_REG_TARGET_ADDR           = 0x004,
	M200_WBx_REG_TARGET_PIXEL_FORMAT   = 0x008,
	M200_WBx_REG_TARGET_AA_FORMAT      = 0x00c,
	M200_WBx_REG_TARGET_LAYOUT         = 0x010,
	M200_WBx_REG_TARGET_SCANLINE_LENGTH = 0x014,
	M200_WBx_REG_TARGET_FLAGS          = 0x018,
	M200_WBx_REG_MRT_ENABLE            = 0x01c,
	M200_WBx_REG_MRT_OFFSET            = 0x020,
	M200_WBx_REG_GLOBAL_TEST_ENABLE    = 0x024,
	M200_WBx_REG_GLOBAL_TEST_REF_VALUE = 0x028,
	M200_WBx_REG_GLOBAL_TEST_CMP_FUNC  = 0x02c
};

/** The number of registers in one single writeback unit */
#define M200_NUM_REGS_WBx 12

enum m200_wbx_source_select
{
	M200_WBx_SOURCE_NONE      = 0,
	M200_WBx_SOURCE_Z_STENCIL = 1,
	M200_WBx_SOURCE_ARGB      = 2
	                            /* 3 - undefined */
};

enum  m200_wbx_target_flags
{
	M200_WBx_TARGET_FLAGS_DIRTY_BIT_ENABLE             = (1 << 0),
	M200_WBx_TARGET_FLAGS_BOUNDING_BOX_ENABLE          = (1 << 1),
	M200_WBx_TARGET_FLAGS_SWAP_RED_BLUE_ENABLE         = (1 << 2),
	M200_WBx_TARGET_FLAGS_INV_COMPONENT_ORDER_ENABLE   = (1 << 3),
	M200_WBx_TARGET_FLAGS_DITHER_ENABLE                = (1 << 4),
	M200_WBx_TARGET_FLAGS_BIG_ENDIAN                   = (1 << 5)
};

enum m200_wbx_mrt_enable
{
	M200_WBx_MRT_ENABLE0 = (1 << 0),
	M200_WBx_MRT_ENABLE1 = (1 << 1),
	M200_WBx_MRT_ENABLE2 = (1 << 2),
	M200_WBx_MRT_ENABLE3 = (1 << 3)
};

enum m200_wbx_aa_format
{
	M200_WBx_AA_FORMAT_0X = 0,
	M200_WBx_AA_FORMAT_2X = 1,
	M200_WBx_AA_FORMAT_4X = 2,
	M200_WBx_AA_FORMAT_8X = 3,
	M200_WBx_AA_FORMAT_16X = 4,
	M200_WBx_AA_FORMAT_32X = 5,
	M200_WBx_AA_FORMAT_64X = 6,
	M200_WBx_AA_FORMAT_128X = 7
};

#if defined(USING_MALI450)
enum m450_dlbu_registers
{
	M450_DLBU_REG_TILE_LIST_VIRTUAL_BASE_ADDRESS = 0,
	M450_DLBU_REG_FRAME_BUFFER_DIMENSION = 1,
	M450_DLBU_REG_TILE_LIST_CONFIGURATION = 2,
	M450_DLBU_REG_START_TILE_POSITIONS = 3,
	M450_DLBU_NUM_REGS
};
#endif /* #if defined(USING_MALI450) */

#ifdef __cplusplus
}
#endif

#endif /* _MALI_200_REGS_H_ */
