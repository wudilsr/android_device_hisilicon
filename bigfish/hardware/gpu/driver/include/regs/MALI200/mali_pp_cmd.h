/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2011, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_PP_CMD_H_
#define _MALI_PP_CMD_H_

/** Used to indicate if a list element is a command, not a polygon */
#define MALI_PL_COMMAND                 1



/** @defgrp primitive_types
 *  Different primitive types which can be set in the
 *  MALI_PL_PRIMITIVE_TYPE
 *  @{
 */
#define MALI_PRIMITIVE_TYPE_TRIANGLE    0
#define MALI_PRIMITIVE_TYPE_PIXEL_RECT  1
#define MALI_PRIMITIVE_TYPE_LINE        2
#define MALI_PRIMITIVE_TYPE_POINT       3
/** @} end of primitive_types */



/**************************************************
 * OPCODES AND PARAMETERS
 **************************************************/

/** @defgrp mali_opcodes
 *  Opcodes that can be used in the pixel processor
 *  Located in the MALI_PL_COMMAND_OPCODE
 *  @{
 */
#define MALI_OPCODE_SET_BASE_VB_RSW                 0
#define MALI_OPCODE_SET_SCISSOR_TEST_PARAM          1
#define MALI_OPCODE_SET_ABSOLUTE_SCISSOR_TEST_PARAM 2
#define MALI_OPCODE_SET_CLIP_VERTEX_BASE            3
#define MALI_OPCODE_SET_MV_THRESHOLD                5
#define MALI_OPCODE_TIMER                           6
#define MALI_OPCODE_INTRA_PREDICTION                7
#define MALI_OPCODE_SAD_ARITH                       8
#define MALI_OPCODE_JUMP                           12
#define MALI_OPCODE_BEGIN_NEW_TILE                 14
#define MALI_OPCODE_END_OF_LIST                    15
#define MALI_OPCODE_ALTERNATIVE_POLY               16
/** @} end of mali_opcodes */



/** @defgrp scissor_subcommands
 *  Subcommands for the scissor test command
 *  @{
 */
#define MALI_PL_SCISSOR_SUB_NOP             0
#define MALI_PL_SCISSOR_SUB_PUSH            1
#define MALI_PL_SCISSOR_SUB_POP             2
#define MALI_PL_SCISSOR_SUB_POPPUSH         (MALI_PL_SCISSOR_SUB_PUSH | \
        MALI_PL_SCISSOR_SUB_POP)
/** @} end of scissor_subcommands */



/** @defgrp flow_type
 *  The different flow control commands
 *  @{
 */
#define MALI_PL_FLOW_JUMP               0
#define MALI_PL_FLOW_COND_JUMP          1
#define MALI_PL_FLOW_COND_CALL          2
#define MALI_PL_FLOW_COND_RETURN        3
/** @} end of flow_type */


/** @defgrp jump_conditions
 *  Conditions used to perform control flow operations. Checks how A+const is
 *  related to B, where A, B and const are stored in params
 *  @{
 */
#define MALI_PL_FLOW_TEST_NEVER_PASS                0
#define MALI_PL_FLOW_TEST_LESS_THAN                 1
#define MALI_PL_FLOW_TEST_EQUAL                     2
#define MALI_PL_FLOW_TEST_LESS_THAN_OR_EQUAL        3
#define MALI_PL_FLOW_TEST_GREATER_THAN              4
#define MALI_PL_FLOW_TEST_NOT_EQUAL                 5
#define MALI_PL_FLOW_TEST_GREATER_THAN_OR_EQUAL     6
#define MALI_PL_FLOW_TEST_ALWAYS_PASS               7
/** @} end of jump_conditions */



/** @defgrp jump_params
 *  The parameters that are used to perform the calculation described in
 *  jump_conditions
 *  @see jump_conditions
 *  @{
 */
#define MALI_PL_FLOW_REG0(X)        (u32)(X)
#define MALI_PL_FLOW_REG1(X)        ((u32)(X) << 5)
#define MALI_PL_FLOW_CONSTANT(X)    (((u32)(X) & 0xFFFF) << 10)
/* @} end of jump_params */


#include <base/mali_byteorder.h>
/**************************************************
 * UTILS TO SET UP THE COMMANDS EFFICIENT
 **************************************************/

#define MALI_PL_CMD_SET_BASE_VB_RSW(dest, vb, rsw)  \
	(dest) = _SWAP_ENDIAN_U64_U8(((u64)(((u64)MALI_PL_COMMAND << 31) | \
	                                    ((u64)MALI_OPCODE_SET_BASE_VB_RSW <<26) | \
	                                    ((u64)(vb) >> 6)) << 32) | \
	                             ((u64)(rsw) >> 3))

#define MALI_PL_CMD_SET_SCISSOR_TEST_PARAM(dest, left, top, right, bottom, subcommand) \
	(dest) = _SWAP_ENDIAN_U64_U8(((u64)(((u64)MALI_PL_COMMAND << 31) | \
	                                    ((u64)MALI_OPCODE_SET_SCISSOR_TEST_PARAM <<26)) << 32) | \
	                             (((u64)(subcommand) << 16) | \
	                              ((u64)(top)    << 12) | \
	                              ((u64)(left)   <<  8) | \
	                              ((u64)(bottom) <<  4) | \
	                              (u64)(right)))

#define MALI_PL_CMD_SET_ABSOLUTE_SCISSOR_TEST_PARAM(dest, left, top, right, bottom) \
	(dest) = _SWAP_ENDIAN_U64_U8((((u64)(((u64)MALI_PL_COMMAND << 31) |                                 \
	                                     ((u64)MALI_OPCODE_SET_ABSOLUTE_SCISSOR_TEST_PARAM << 26)) << 32) |    \
	                              ((u64)(top)    <<  36) |                                              \
	                              ((u64)(left)   <<  24) |                                              \
	                              ((u64)(bottom) <<  12) |                                              \
	                              ((u64)(right)  <<   0)))

#define MALI_PL_CMD_JUMP(dest, addr)  \
	(dest) = _SWAP_ENDIAN_U64_U8(((u64)(((u64)MALI_PL_COMMAND << 31) | \
	                                    ((u64)MALI_OPCODE_JUMP <<26)) << 32) | \
	                             ((u64)((addr)) >> 3))

#define MALI_PL_CMD_UNCONDITIONAL_CALL( dest, addr ) \
	(dest) = _SWAP_ENDIAN_U64_U8(((u64)(((u64)MALI_PL_COMMAND << 31)   | \
	                                    ((u64)MALI_OPCODE_JUMP <<26)) << 32) | \
	                             ((u64)0x7 << 29)                     | \
	                             (((u64)((addr)) >> 3) & 0x1FFFFFFC)  | \
	                             2)

#define MALI_PL_CMD_FLOW_CTRL(dest, addr, jump_type, condition, params) \
	(dest) = _SWAP_ENDIAN_U64_U8(((u64)(((u64)MALI_PL_COMMAND << 31) | \
	                                    ((u64)MALI_OPCODE_JUMP <<26) | \
	                                    ((u64)params)) << 32) | \
	                             (((u64)(condition) << 29) | \
	                              ((u64)((addr) & ~0x1F) >> 3) | \
	                              ((u64)(jump_type))))

#define MALI_PL_CMD_BEGIN_NEW_TILE( dest, x_offset, y_offset ) \
	(dest) = _SWAP_ENDIAN_U64_U8((u64) (((u64)MALI_PL_COMMAND << 31) | \
	                                    ((u64)MALI_OPCODE_BEGIN_NEW_TILE << 26) | \
	                                    ((u64)(y_offset) << 8) | \
	                                    ((u64)(x_offset))) << 32)


#define MALI_PL_CMD_END_OF_LIST(dest)  \
	(dest) = _SWAP_ENDIAN_U64_U8((u64)(((u64)MALI_PL_COMMAND << 31) | \
	                                   ((u64)MALI_OPCODE_END_OF_LIST <<26)) << 32)

#define MALI_PL_CMD_ALT_POLY(dest, flags, \
                             scale_factor, s_offset, t_offset, rsw_index, vdb_index, multitexture) \
(dest) = _SWAP_ENDIAN_U64_U8(((u64)(((u64)MALI_PL_COMMAND << 31) | \
                                    ((u64)MALI_OPCODE_ALTERNATIVE_POLY << 26) | \
                                    ((u64)(vdb_index)           << 23) | \
                                    ((u64)(multitexture)        << 22) | \
                                    ((u64)(rsw_index)           << 17) | \
                                    ((u64)(scale_factor) << 8)) << 32) | \
                             (((u64)((t_offset) & 0x7FF)  << 29) | \
                              ((u64)((s_offset) & 0x7FF)  << 18) | \
                              ((u64)(flags))))

#define MALI_PL_CMD_MV_THRESHOLD(dest, \
                                 s_threshold, t_threshold, s_right, t_bot) \
(dest) = _SWAP_ENDIAN_U64_U8(((u64)(((u64)MALI_PL_COMMAND << 31) | \
                                    ((u64)MALI_OPCODE_SET_MV_THRESHOLD << 26) | \
                                    ((u64)4) | /* Threshold enable */ \
                                    ((u64)(t_bot) << 1) | \
                                    ((u64)(s_right))) << 32) | \
                             ((u64)(((u64)((t_threshold) & 0x7FF) << 16) | \
                                    ((u64)((s_threshold) & 0x7FF)))))

#define MALI_PL_CMD_TIMER(dest, opcode, value) \
	(dest) = _SWAP_ENDIAN_U64_U8(((u64)(((u64)MALI_PL_COMMAND << 31) | \
	                                    ((u64)MALI_OPCODE_TIMER << 26) | \
	                                    ((u64)(opcode))) << 32) | \
	                             ((u64)(value)))


#define MALI_PL_CMD_NO_INTRA_PRED(dest, flags) \
	(dest) = _SWAP_ENDIAN_U64_U8(((u64)(((u64)MALI_PL_COMMAND << 31) | \
	                                    ((u64)MALI_OPCODE_INTRA_PREDICTION << 26) | \
	                                    ((u64)(1)                   << 22)) << 32) | \
	                             (((u64)(flags))))


/**************************************************
 * UTILS TO SET UP THE PRIMITIVES EFFICIENT
 **************************************************/

#define MALI_PL_PRIMITIVE(dest, type, rsw_index, vertex0, vertex1, vertex2_or_pointsize_or_linewidth)  \
	(dest) = _SWAP_ENDIAN_U64_U8(((u64)((type << 29) | \
	                                    ((u64)(rsw_index) << 19) | \
	                                    ((u64)(vertex2_or_pointsize_or_linewidth) << 2) | \
	                                    ((u64)(vertex1) >> 15)) << 32) | \
	                             (((u64)(vertex1) << 17) | \
	                              ((u64)(vertex0))))

/**
 * Flags to be used for the alternative poly-command
 * MALI_PL_CMD_ALT_POLY
 */
#define MALI_PL_ALT_FLAG_WRITE_REG(w_reg_add)           ((u32)(w_reg_add & 0x1F))
#define MALI_PL_ALT_FLAG_READ_REG(r_reg_add)            ((u32)(r_reg_add & 0x1F)     << 5)
#define MALI_PL_ALT_FLAG_WRITEBACK_OPERATION(wb_op)     ((u32)(wb_op & 0x7)          << 10)
#define MALI_PL_ALT_FLAG_BEST_SAD_VAL_RESET             ((u32)1                      << 13)
#define MALI_PL_ALT_FLAG_POLYGON_INDEX(pol_index)       ((u32)(pol_index & 0xF)      << 14)
#define MALI_PL_ALT_FLAG_REG_TO_READ_DS_DT(ds_dt_reg)   ((u64)(ds_dt_reg & 0x1F)     << 44)

#endif
