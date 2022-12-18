/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */


#ifndef _MALI_GP_PLBU_CONFIG_H_
#define _MALI_GP_PLBU_CONFIG_H_

#include <mali_gp_plbu_cmd.h>

/** The required alignment of memory addresses that are added to PLBU registers */
#define GP_PLBU_CONF_REG_ADDRESS_ALIGNMENT 64

/**
 * @defgroup PLBU_CONF_REG
 * Configuration registers for the PLBU in MaliGP2
*/
#define GP_PLBU_CONF_REG_VERTEX_ARRAY_ADDR   256
#define GP_PLBU_CONF_REG_INDEX_ARRAY_ADDR    257
#define GP_PLBU_CONF_REG_POINT_SIZE_ADDR     258
#define GP_PLBU_CONF_REG_HEAP_START_ADDR     259
#define GP_PLBU_CONF_REG_HEAP_END_ADDR       260
#define GP_PLBU_CONF_REG_SCISSOR_TOP         261
#define GP_PLBU_CONF_REG_SCISSOR_BOTTOM      262
#define GP_PLBU_CONF_REG_SCISSOR_LEFT        263
#define GP_PLBU_CONF_REG_SCISSOR_RIGHT       264
#define GP_PLBU_CONF_REG_VIEWPORT            265
#define GP_PLBU_CONF_REG_OFFSET_VERTEX_ARRAY 266
#define GP_PLBU_CONF_REG_PARAMS              267
#define GP_PLBU_CONF_REG_TILE_SIZE           268
#define GP_PLBU_CONF_REG_POINT_SIZE          269
#define GP_PLBU_CONF_REG_Z_NEAR              270
#define GP_PLBU_CONF_REG_Z_FAR               271

/** }@ defgroup PLBU_CONF_REG */

#ifdef MALI_BIG_ENDIAN

#define GP_PLBU_CONF_REGS_PARAMS(\
                                 rsw_idx, \
                                 list_alloc_size, \
                                 vertex_idx_format,\
                                 point_size_override, \
                                 point_clipping_select, \
                                 line_width_vertex_select,\
                                 polygon_mode, \
                                 backf_cull_ccv, \
                                 backf_cull_cv) \
( \
  ( (u32)GP_PLBU_CMD_BMASK(rsw_idx,                   8)      ) |\
  ( (u32)GP_PLBU_CMD_BMASK(list_alloc_size,           2)   <<8) |\
  (((u32)GP_PLBU_CMD_BMASK(vertex_idx_format,         2)) <<10) |\
  (((u32)GP_PLBU_CMD_BMASK(point_size_override,       1)) <<12) |\
  (((u32)GP_PLBU_CMD_BMASK(point_clipping_select,     1)) <<13) |\
  (((u32)GP_PLBU_CMD_BMASK(line_width_vertex_select,  1)) <<14) |\
  (((u32)GP_PLBU_CMD_BMASK(polygon_mode,              2)) <<15) |\
  (((u32)GP_PLBU_CMD_BMASK(backf_cull_ccv,            1)) <<17) |\
  (((u32)GP_PLBU_CMD_BMASK(backf_cull_cv,             1)) <<18) |\
  (((u32)1) <<19) \
)

#else

#define GP_PLBU_CONF_REGS_PARAMS(\
                                 rsw_idx, \
                                 list_alloc_size, \
                                 vertex_idx_format,\
                                 point_size_override, \
                                 point_clipping_select, \
                                 line_width_vertex_select,\
                                 polygon_mode, \
                                 backf_cull_ccv, \
                                 backf_cull_cv) \
( \
  ( (u32)GP_PLBU_CMD_BMASK(rsw_idx,                   8)      ) |\
  ( (u32)GP_PLBU_CMD_BMASK(list_alloc_size,           2)   <<8) |\
  (((u32)GP_PLBU_CMD_BMASK(vertex_idx_format,         2)) <<10) |\
  (((u32)GP_PLBU_CMD_BMASK(point_size_override,       1)) <<12) |\
  (((u32)GP_PLBU_CMD_BMASK(point_clipping_select,     1)) <<13) |\
  (((u32)GP_PLBU_CMD_BMASK(line_width_vertex_select,  1)) <<14) |\
  (((u32)GP_PLBU_CMD_BMASK(polygon_mode,              2)) <<15) |\
  (((u32)GP_PLBU_CMD_BMASK(backf_cull_ccv,            1)) <<17) |\
  (((u32)GP_PLBU_CMD_BMASK(backf_cull_cv,             1)) <<18) |\
  (((u32)0) <<19) \
)

#endif


#define GP_PLBU_CONF_REGS_TILE_SIZE(xsize, ysize) \
	( \
	  ( (u32)GP_PLBU_CMD_BMASK(xsize,                     6)      ) |\
	  (((u32)GP_PLBU_CMD_BMASK(ysize,                     6)) <<16) \
	)

typedef enum mali_polygon_list_primitive_format
{
	MALI_PLIST_FORMAT_LEGACY_1X1 = 0,       /**< The old Mali200 format */
	MALI_PLIST_FORMAT_SUPER_TILING_2X2 = 1, /**< 2x2 super tiling */
	MALI_PLIST_FORMAT_SUPER_TILING_4X4 = 2  /**< 4x4 super tiling */
} mali_polygon_list_primitive_format;

#define GP_PLBU_CONF_REGS_TILE_SIZE_WITH_FORMAT(xsize, ysize, format) \
	( \
	  ( (u32)GP_PLBU_CMD_BMASK(xsize,                     6)      ) |\
	  (((u32)GP_PLBU_CMD_BMASK(ysize,                     6)) <<16) |\
	  (((u32)GP_PLBU_CMD_BMASK(format,                    2)) <<28)  \
	)

#endif /* _MALI_GP_PLBU_CONFIG_H_ */
