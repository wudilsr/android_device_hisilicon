/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2007, 2009-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_GP_VS_CMD_H_
#define _MALI_GP_VS_CMD_H_

#include <mali_system.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef u64 mali_gp_vs_cmd;
#define GP_VS_CMD_BIT_LOW 60

/* Bit two in a shade vertices command will disable paralell shading on Mali-450. */
#if defined(USING_MALI450)
#define GP_VS_CMD_SHADE_VERTICES_NO_PARALLEL 0x2
#else
#define GP_VS_CMD_SHADE_VERTICES_NO_PARALLEL 0x0
#endif

/** A bitmask macro used for each field that is merged to a VS Commando.
 *  It might not be needed, but can make the system a little more stable.
 *  In most of the cases where it is not needed it will automagically be
 *  optimized away by the compiler.
 */
#define GP_VS_CMD_BMASK( A, X ) ( (mali_gp_vs_cmd)(A) & ((1<<(X))-1) )


/** @defgroup vertex_shader_commands
 *  The Vertex Shader Command List is a list of commands intended
 *  for the Vertex Shader to perform. The GP_VS_CMD_ list below
 *  declares the command part of the command, and must be ored
 *  with the payload part of the command.
 *  @{ */
#define GP_VS_CMD_SHADE_VERTICES               0
#define GP_VS_CMD_WRITE_CONF_REG               1
#define GP_VS_CMD_WRITE_INPUT_OUTPUT_CONF_REGS 2
#define GP_VS_CMD_LOAD_CONST_REGS              3
#define GP_VS_CMD_LOAD_SHADER                  4
#define GP_VS_CMD_LOAD_WAIT_INC_SEM            5
#define GP_VS_CMD_FLUSH_WRITEBACK_BUF          6
#define GP_VS_CMD_LIST_CALL                    7
#define GP_VS_CMD_LIST_RETURN                  8
/* commands 9-14 are reserved */
#define GP_VS_CMD_COMMAND_LIST_JUMP            15

#include <base/mali_byteorder.h>
/* #define GP_VS_COMMAND(vs_cmd,payload) (vs_cmd |(payload)) */
#define GP_VS_COMMAND(vs_cmd,payload) (_SWAP_ENDIAN_U64_U8((((mali_gp_vs_cmd)(vs_cmd))<<GP_VS_CMD_BIT_LOW) |(payload)))


/** CMD 0:
 *  This command instructs the Vertex Shader to process a
 *  number of vertices from a vertex array; the actual
 *  parameters for the vertex array are expected to be
 *  programmed before this command is issued.
 *
 *  On Mali-450 this command will activate both shader cores.
 */
#define GP_VS_COMMAND_SHADE_VERTICES(opmod, vertex_count)         \
	GP_VS_COMMAND(                                                  \
	        GP_VS_CMD_SHADE_VERTICES,                                   \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK(opmod, 1)         <<  0) | \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK(vertex_count, 24) << 24)   \
	             )


/** CMD 0 no parallel:
 *  This command instructs the Vertex Shader to process a
 *  number of vertices from a vertex array; the actual
 *  parameters for the vertex array are expected to be
 *  programmed before this command is issued.
 *
 *  On Mali-450 this will only activate a single core.
 *  Use only when there are dependencies among the vertices.
 */
#define GP_VS_COMMAND_SHADE_VERTICES_NO_PARALLEL(opmod, vertex_count)   \
	GP_VS_COMMAND(                                                  \
	        GP_VS_CMD_SHADE_VERTICES,                                   \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK(opmod, 1)         <<  0) | \
	        ((mali_gp_vs_cmd)(GP_VS_CMD_SHADE_VERTICES_NO_PARALLEL)) |      \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK(vertex_count, 24) << 24)   \
	             )

/** CMD 1:
 *  This command will write one 32-bit value to a single
 *  Configuration Register in the vertex shader. See
 *  Section [sec:The-Configuration-Registers] for a listing of
 *  the Configuration Registers.
 */
#define GP_VS_COMMAND_WRITE_CONF_REG(data, reg_index)            \
	GP_VS_COMMAND(                                               \
	        GP_VS_CMD_WRITE_CONF_REG,                                \
	        ((mali_gp_vs_cmd)(data)                         <<  0) | \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK(reg_index, 16) << 32)   \
	             )



/** CMD 2:
 *  This command will fetch from memory a sequence of 32-bit
 *  values, and write then to a contiguous sequence of Configuration
 *  Registers. See Section [sec:The-Configuration-Registers] for a
 *  listing of the Configuration Registers.*/
#define GP_VS_COMMAND_WRITE_INPUT_OUTPUT_CONF_REGS(addr,idx,nr) \
	GP_VS_COMMAND(                                              \
	        GP_VS_CMD_WRITE_INPUT_OUTPUT_CONF_REGS,                 \
	        ((mali_gp_vs_cmd)(addr)                   <<  0)      | \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK(idx,  1) << 35)      | \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK(nr,  11) << 49)        \
	             )

/** CMD 3:
 *  This command will fetch from memory a sequence of
 *  values, and store them to a contiguous sequence of
 *  vertex shader Constant Registers. Each value consists
 *  of 4 values in FP32 floating-point format; they are
 *  stored in the order XYZW, with X first in memory; they
 *  are converted down to FP24 as they are written to the
 *  Constant Register File.
 */
#define GP_VS_COMMAND_LOAD_CONST_REGS(addr, idx, nr)         \
	GP_VS_COMMAND(                                           \
	        GP_VS_CMD_LOAD_CONST_REGS,                           \
	        ((mali_gp_vs_cmd)(addr)                     <<  0) | \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK((idx), 16) << 32) | \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK((nr),  12) << 48)   \
	             )


/** CMD 4:
 *  This command will fetch from memory a sequence of
 *  Vertex Shader instruction words, and store them to a
 *  contiguous sequence of instruction words in the
 *  instruction memory. Each instruction word is 128 bits
 *  wide and contains the shader instructions to execute
 *  for 1 instruction.
 */
#define GP_VS_COMMAND_LOAD_SHADER(addr, idx, nr)             \
	GP_VS_COMMAND(                                           \
	        GP_VS_CMD_LOAD_SHADER,                               \
	        ((mali_gp_vs_cmd)(addr)                     <<  0) | \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK((idx), 16) << 32) | \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK((nr),  12) << 48)   \
	             )



/** CMD 5:
 *  This command will wait until the value of the Semaphore
 *  Register is equal to or below the specified value, then
 *  increment the value of the Semaphore Register by the
 *  specified value.
 */
#define GP_VS_COMMAND_WAIT_INC_SEM(valwait, valinc, irqenbl)     \
	GP_VS_COMMAND(                                               \
	        GP_VS_CMD_LOAD_WAIT_INC_SEM,                             \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK((valwait), 16) <<  0) | \
	        ((mali_gp_vs_cmd)GP_VS_CMD_BMASK((valinc),  16) << 16) | \
	        ((mali_gp_vs_cmd)((irqenbl) & 1)    << 32)               \
	             )

/** CMD 6:
 */
#define GP_VS_COMMAND_FLUSH_WRITEBACK_BUF() \
	GP_VS_COMMAND(                          \
	                                        GP_VS_CMD_FLUSH_WRITEBACK_BUF,      \
	                                        0                                   \
	             )

/** CMD 7:
 */
#define GP_VS_COMMAND_LIST_CALL(addr) \
	GP_VS_COMMAND(                    \
	                                  GP_VS_CMD_LIST_CALL,          \
	                                  (mali_gp_vs_cmd)(addr)        \
	             )

/** CMD 8:
 */
#define GP_VS_COMMAND_LIST_RETURN() \
	GP_VS_COMMAND(                  \
	                                GP_VS_CMD_LIST_RETURN,      \
	                                0                           \
	             )


/** CMD 15:
 *  This command performs a command list Jump; the
 *  execution of the command list is then resumed at the
 *  address that is jumped to.
 */
#define GP_VS_COMMAND_LIST_JUMP(addr) \
	GP_VS_COMMAND(                    \
	                                  GP_VS_CMD_COMMAND_LIST_JUMP,  \
	                                  (mali_gp_vs_cmd)(addr)        \
	             )

/** }@ */


/* Utility macros for working with PLBU command lists  */
/**
 * Check whether the command is a command of type "Command 0: Shade vertices"
 * (GP_VS_CMD_SHADE_VERTICES). This commands starts the shading of vertices
 */
#define IS_VS_SHADE_VERTICES_COMMAND(command) \
	(GP_VS_CMD_BMASK(command >> GP_PLBU_CMD_BIT_LOW, 4) == 0)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MALI_GP_VS_CMD_H_ */
