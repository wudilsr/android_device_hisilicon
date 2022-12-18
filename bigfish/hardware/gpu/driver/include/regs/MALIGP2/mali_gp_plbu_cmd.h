/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_GP_PLBU_CMD_H_
#define _MALI_GP_PLBU_CMD_H_

/** Data type containing a Polygon List Builder command */
typedef u64 mali_gp_plbu_cmd;

/** Lowest bit in Command-specifying */
#define GP_PLBU_CMD_BIT_LOW 60

/**
 * A bitmask macro used for each field that is merged to a VS Commando.
 *  It might not be needed, but can make the system a little more stable.
 *  In most of the cases where it is not needed it will automagically be
 *  optimized away by the compiler.
 */
#define GP_PLBU_CMD_BMASK( A, X ) ( (mali_gp_plbu_cmd)(A) & ((1U<<(X))-1) )


/**
 * @defgroup polygon_list_builder_commands
 *  The Polygon List Builder Command List is a list of
 *  commands intended for the Polygon List Builder to
 *  perform. This List has a similar format to the Vertex
 *  Shader Command List, with 64-bit entries, and a 4-bit
 *  command + 60-bit payload field. The supported commands
 *  are as follows:
 *  @{ */
#define GP_PLBU_CMD_PROCESS_SHADED_VERTICES (((u64)0)<<GP_PLBU_CMD_BIT_LOW)
#define GP_PLBU_CMD_WRITE_CONF_REG          (((u64)1)<<GP_PLBU_CMD_BIT_LOW)
#define GP_PLBU_CMD_POINTER_ARRAY_BASE_ADDR (((u64)2)<<GP_PLBU_CMD_BIT_LOW)
#define GP_PLBU_CMD_PREPARE_FRAME           (((u64)3)<<GP_PLBU_CMD_BIT_LOW)
/* 4 reserved */
#define GP_PLBU_CMD_END_FRAME               (((u64)5)<<GP_PLBU_CMD_BIT_LOW)
#define GP_PLBU_CMD_WAIT_DEC_SEM            (((u64)6)<<GP_PLBU_CMD_BIT_LOW)
#define GP_PLBU_CMD_SET_SCISSOR             (((u64)7)<<GP_PLBU_CMD_BIT_LOW)
#define GP_PLBU_CMD_RSW_VERTEX_ADDR         (((u64)8)<<GP_PLBU_CMD_BIT_LOW)
#define GP_PLBU_CMD_LOAD_CONF_REG           (((u64)9)<<GP_PLBU_CMD_BIT_LOW)
#define GP_PLBU_CMD_STORE_CONF_REG          (((u64)10)<<GP_PLBU_CMD_BIT_LOW)
/* [11 - 12] reserved */
#define GP_PLBU_CMD_FLUSH_POINTER_CACHE     (((u64)13)<<GP_PLBU_CMD_BIT_LOW)
/* 14 reserved */
#define GP_PLBU_CMD_COMMAND_LIST_JUMP       (((u64)15)<<GP_PLBU_CMD_BIT_LOW)


/**
 * The PLBU command "Process shaded vertices" has two opmods.
 *  @see GP_PLBU_COMMAND_PROCESS_SHADED
 */
#define GP_PLBU_OPMODE_DRAW_ARRAYS 0
#define GP_PLBU_OPMODE_DRAW_ELEMENTS 1

/**
 * In DrawElements mode, the index in bits 23:0 is an
 *  index into an array of vertex indices.
 *  The Primitive type is one of the following.
 *  @see MP_PLBU_COMMAND_PROCESS_SHADED
*/
#define GP_PLBU_PRIM_TYPE_POINTS_AND_POINT_SPRITES (0)
#define GP_PLBU_PRIM_TYPE_INDIVIDUAL_LINES         (1)
#define GP_PLBU_PRIM_TYPE_LINE_LOOP                (2)
#define GP_PLBU_PRIM_TYPE_LINE_STRIP               (3)
#define GP_PLBU_PRIM_TYPE_INDIVIDUAL_TRIANGLES     (4)
#define GP_PLBU_PRIM_TYPE_TRIANGLE_STRIP           (5)
#define GP_PLBU_PRIM_TYPE_TRIANGLE_FAN             (6)
#define GP_PLBU_PRIM_TYPE_INDIVIDUAL_QUADS         (7)
#define GP_PLBU_PRIM_TYPE_QUAD_STRIP               (8)
#define GP_PLBU_PRIM_TYPE_POLYGON                  (9)
/* [10 - 14] reserved */
#define GP_PLBU_PRIM_TYPE_PIXEL_RECTANGLES         (15)
/* [16 - 31] reserved */

/**
 * You can make a PLBU Command whith this macro if you already
 *  got the payload. If not it is simpler with one of the
 *  specified macros below.
 *  Usage: see P0081_media_proc_data_struct.h
 */
#define GP_PLBU_COMMAND(vs_cmd,payload) _SWAP_ENDIAN_U64_U8((vs_cmd |(payload)))
#include <base/mali_byteorder.h>
/** Command 0: Process Shaded Vertices */
#define GP_PLBU_COMMAND_PROCESS_SHADED_VERTICES(idx,nr,ptype, opmod)     \
	(_SWAP_ENDIAN_U64_U8(                                                        \
	        ((mali_gp_plbu_cmd)                                          \
	         (GP_PLBU_CMD_PROCESS_SHADED_VERTICES                       | \
	          ( GP_PLBU_CMD_BMASK( idx, 24) )                            | \
	          ( ((mali_gp_plbu_cmd) GP_PLBU_CMD_BMASK( nr, 24))   << 24) | \
	          ( ((mali_gp_plbu_cmd) GP_PLBU_CMD_BMASK( ptype, 5)) << 48) | \
	          ( ((mali_gp_plbu_cmd) GP_PLBU_CMD_BMASK( opmod, 7)) << 53)   \
	         ))                                                           \
	                    ))


/** Command 1: Write to a configuration register */
#define GP_PLBU_COMMAND_WRITE_CONF_REG(data,idx)                        \
	(_SWAP_ENDIAN_U64_U8(                                                       \
	        ((mali_gp_plbu_cmd)                                         \
	         (GP_PLBU_CMD_WRITE_CONF_REG                               | \
	          ( data )                                                  | \
	          ( ((mali_gp_plbu_cmd) GP_PLBU_CMD_BMASK( idx, 16)) << 32)   \
	         )) \
	                    ))


/** Command 2: set pointer array address and number of tiles */
/**
 * Note:
 * Mali200 defines 0 bits for the number of tiles; assuming always 300 tiles.
 *   But due to bus bursting, it is possible to read 304 tiles.
 *   No matter what you set in no_tiles, up to 304 tiles will be read.
 * Mali300/400/450 defines 12 bits for the number of tiles, must be an even number.
 *
 * If more bits than supported are set, the excess bits are simply ignored.
 */
#define GP_PLBU_COMMAND_POINTER_ARRAY_BASE_ADDR_TILE_COUNT(addr, no_tiles)   \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)                                              \
	         (GP_PLBU_CMD_POINTER_ARRAY_BASE_ADDR                           | \
	          ( ((mali_gp_plbu_cmd)GP_PLBU_CMD_BMASK( 1, 1))          << 59) | \
	          ( ((mali_gp_plbu_cmd)GP_PLBU_CMD_BMASK( no_tiles-1, 12)) << 32) | \
	          ( ((mali_gp_plbu_cmd)GP_PLBU_CMD_BMASK( addr>>4, 28))   << 4)    \
	         )) \
	                    ))


/** Command 3: Prepare for Begin Frame */
#define GP_PLBU_COMMAND_PREPARE_FRAME( tiles_x)                       \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)                                       \
	         (GP_PLBU_CMD_PREPARE_FRAME                              | \
	          ( ((mali_gp_plbu_cmd) GP_PLBU_CMD_BMASK( tiles_x, 8)) )   \
	         )) \
	                    ))

/** Command 5: End Frame */
#define GP_PLBU_COMMAND_END_FRAME() \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)     \
	         (GP_PLBU_CMD_END_FRAME  \
	         )) \
	                    ))

/** Command 6: Wait and Decrement Semaphore */
#define GP_PLBU_COMMAND_WAIT_DEC_SEM(val_wait, val_dec, irq_enbl)  \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)                                    \
	         (GP_PLBU_CMD_WAIT_DEC_SEM                            | \
	          ( GP_PLBU_CMD_BMASK( val_wait, 16)       )           | \
	          ( GP_PLBU_CMD_BMASK( val_dec,  16)   << 16)          | \
	          (( (mali_gp_plbu_cmd)(irq_enbl)  &1) << 32)            \
	         )) \
	                    ))

/** Command 7: Set Scissor Parameters */
#define GP_PLBU_COMMAND_SET_SCISSOR(ty, by, lx,rx)                      \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)                                         \
	         (GP_PLBU_CMD_SET_SCISSOR                                  | \
	          ( GP_PLBU_CMD_BMASK( ty, 15) )                            | \
	          ( GP_PLBU_CMD_BMASK( by, 15)                      << 15)  | \
	          ( ((mali_gp_plbu_cmd) GP_PLBU_CMD_BMASK( lx, 15)) << 30 ) | \
	          ( ((mali_gp_plbu_cmd) GP_PLBU_CMD_BMASK( rx, 15)) << 45 )   \
	         )) \
	                    ))

/** Command 8: Set RSW/Vertex Data Bundle Base Address */
#define GP_PLBU_COMMAND_RSW_VERTEX_ADDR(rsw_addr, vertex_addr)                       \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)                                                      \
	         (GP_PLBU_CMD_RSW_VERTEX_ADDR                                           | \
	          ( ((mali_gp_plbu_cmd)GP_PLBU_CMD_BMASK( (rsw_addr)>>6, 26) )    << 6)  | \
	          ( ((mali_gp_plbu_cmd)GP_PLBU_CMD_BMASK( (vertex_addr)>>6, 26) ) << 34)   \
	         )) \
	                    ))

/** Command 9: Load config reg value from memory */
#define GP_PLBU_COMMAND_LOAD_CONF_REG( address , idx)                  \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)                                        \
	         (GP_PLBU_CMD_LOAD_CONF_REG                               | \
	          (address)                                                | \
	          ( ((mali_gp_plbu_cmd) GP_PLBU_CMD_BMASK( idx, 16)) << 32)  \
	         )) \
	                    ))

/** Command 10: Store config reg value to memory */
#define GP_PLBU_COMMAND_STORE_CONF_REG( address , idx)                 \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)                                        \
	         (GP_PLBU_CMD_STORE_CONF_REG                              | \
	          ( (address) )                                            | \
	          ( ((mali_gp_plbu_cmd) GP_PLBU_CMD_BMASK( idx, 16)) << 32)  \
	         )) \
	                    ))

/** Command 13: Flush pointer array */
#define GP_PLBU_COMMAND_FLUSH_POINTER_CACHE() \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)               \
	         (GP_PLBU_CMD_FLUSH_POINTER_CACHE  \
	         )) \
	                    ))

/** Command 15: Command List Jump */
#define GP_PLBU_COMMAND_LIST_JUMP(addr)      \
	(_SWAP_ENDIAN_U64_U8(                                              \
	        ((mali_gp_plbu_cmd)              \
	         (GP_PLBU_CMD_COMMAND_LIST_JUMP | \
	          (addr)                           \
	         )) \
	                    ))
/** }@ */

/* Utility macros for working with PLBU command lists  */

/**
 * Check whether the PLBU command is a command of type "Command 1: Set single configuration
 * register" (GP_PLB_CMD_WRITE_CONF_REG)
 */
#define IS_PLBU_WRITE_REG_COMMAND(command)                      \
	(GP_PLBU_CMD_BMASK(command >> GP_PLBU_CMD_BIT_LOW, 4) == 1)

/**
 * Check whether the command is a command to write a value to the tile size register
 * (GP_PLB_CONF_REG_TILE_SIZE)
 */
#define IS_PLBU_WRITE_TILE_SIZE_REG_COMMAND(command)                      \
	(IS_PLBU_WRITE_REG_COMMAND(command) &&                                \
	 (GP_PLBU_CMD_BMASK(command >> 32, 16) == GP_PLBU_CONF_REG_TILE_SIZE))

/**
 * Check whether the command is a command to write a value to the PLBU configuration register
 * (GP_PLB_CONF_REG_PARAMS). This register contains, among other things, the list_alloc_size
 * (tile_list_block_scale)
 */
#define IS_PLBU_WRITE_CONF_REG_COMMAND(command)                        \
	(IS_PLBU_WRITE_REG_COMMAND(command) &&                             \
	 (GP_PLBU_CMD_BMASK(command >> 32, 16) == GP_PLBU_CONF_REG_PARAMS))

/**
 * Check whether the command is a command of type "Command 3: Prepare for begin frame address"
 * (GP_PLB_CMD_PREPARE_TO_BEGIN_FRAME). This commands sets the tile iterator
 */
#define IS_PLBU_PREPARE_COMMAND(command)                        \
	(GP_PLBU_CMD_BMASK(command >> GP_PLBU_CMD_BIT_LOW, 4) == 3)

/**
 * Check whether the command is a command of type "Command 0: Process shaded vertices"
 * (GP_PLB_CMD_SHADED_VERTICES). This commands starts the processing of shaded vertices
 */
#define IS_PLBU_PROCESS_SHADED_VERTICES_COMMAND(command) \
	(GP_PLBU_CMD_BMASK(command >> GP_PLBU_CMD_BIT_LOW, 4) == 0)


#endif /* _MALI_GP_PLBU_CMD_H_ */
