/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
/* .../include/shared/mgp2_regs.h */

enum mgp2_mgmt_reg
{
	MGP2_CTRL_REG_PERF_CNT_0_ENABLE                    = 0x003c,
	MGP2_CTRL_REG_PERF_CNT_1_ENABLE                    = 0x0040,
	MGP2_CTRL_REG_PERF_CNT_0_SRC                       = 0x0044,
	MGP2_CTRL_REG_PERF_CNT_1_SRC                       = 0x0048,
	MGP2_CTRL_REG_PERF_CNT_0_VALUE                     = 0x004c,
	MGP2_CTRL_REG_PERF_CNT_1_VALUE                     = 0x0050,
	MGP2_CTRL_REG_PERF_CNT_0_LIMIT                     = 0x0054,
	MGP2_CTRL_REG_PERF_CNT_1_LIMIT                     = 0x0058
};

enum mgp2_ctrl_reg_perf_cnt_src
{
	MGP2_PERF_SRC_CYCLE_COUNTER                                      = 0x00,
	MGP2_PERF_SRC_ACTIVE_CYCLES_MGP2                                 = 0x01,
	MGP2_PERF_SRC_ACTIVE_CYCLES_VERTEX_SHADER                        = 0x02,
	MGP2_PERF_SRC_ACTIVE_CYCLES_VERTEX_STORER                        = 0x03,
	MGP2_PERF_SRC_ACTIVE_CYCLES_VERTEX_LOADER                        = 0x04,
	MGP2_PERF_SRC_CYCLES_VERTEX_LOADER_WAITING_FOR_VERTEX_SHADER     = 0x05,
	MGP2_PERF_SRC_NUMBER_OF_WORDS_READ                               = 0x06,
	MGP2_PERF_SRC_NUMBER_OF_WORDS_WRITTEN                            = 0x07,
	MGP2_PERF_SRC_NUMBER_OF_READ_BURSTS                              = 0x08,
	MGP2_PERF_SRC_NUMBER_OF_WRITE_BURSTS                             = 0x09,
	MGP2_PERF_SRC_NUMBER_OF_VERTICES_PROCESSED                       = 0x0a,
	MGP2_PERF_SRC_NUMBER_OF_VERTICES_FETCHED                         = 0x0b,
	MGP2_PERF_SRC_NUMBER_OF_PRIMITIVES_FETCHED                       = 0x0c,
	/*  MGP2_PERF_SRC_NUMBER_OF_CLIPPINGS_DONE                           = 0x0d, gone */
	MGP2_PERF_SRC_NUMBER_OF_BACKFACE_CULLINGS_DONE                   = 0x0e,
	MGP2_PERF_SRC_NUMBER_OF_COMMANDS_WRITTEN_TO_TILES                = 0x0f,
	MGP2_PERF_SRC_NUMBER_OF_MEMORY_BLOCKS_ALLOCATED                  = 0x10,
	/*  MGP2_PERF_SRC_NUMBER_OF_TILE_BUFFER_WRITEBACKS                   = 0x11, gone */
	/*  MGP2_PERF_SRC_NUMBER_OF_VERTEX_LOADER_CACHE_HITS                 = 0x12, gone */
	MGP2_PERF_SRC_NUMBER_OF_VERTEX_LOADER_CACHE_MISSES               = 0x13,
	/*  MGP2_PERF_SRC_NUMBER_OF_VERTEX_ADDER_CACHE_HITS                  = 0x14, gone */
	/*  MGP2_PERF_SRC_NUMBER_OF_VERTEX_ADDER_CACHE_MISSES                = 0x15, gone */
	MGP2_PERF_SRC_ACTIVE_CYCLES_VERTEX_SHADER_COMMAND_PROCESSOR      = 0x16,
	MGP2_PERF_SRC_ACTIVE_CYCLES_PLBU_COMMAND_PROCESSOR               = 0x17,
	MGP2_PERF_SRC_ACTIVE_CYCLES_PLBU_LIST_WRITER                     = 0x18,
	MGP2_PERF_SRC_ACTIVE_CYCLES_THROUGH_THE_PREPARE_LIST_COMMANDS    = 0x19,
	/*  MGP2_PERF_SRC_ACTIVE_CYCLES_BACK_FACE_CULLER                     = 0x1a, gone */
	MGP2_PERF_SRC_ACTIVE_CYCLES_PRIMITIVE_ASSEMBLY                   = 0x1b,
	MGP2_PERF_SRC_ACTIVE_CYCLES_PLBU_VERTEX_FETCHER                  = 0x1c,
	/*  MGP2_PERF_SRC_ACTIVE_CYCLES_PLBU_APPLY_POLYGON_MODE              = 0x1d, gone */
	MGP2_PERF_SRC_ACTIVE_CYCLES_BOUNDINGBOX_AND_COMMAND_GENERATOR    = 0x1e,
	/*  MGP2_PERF_SRC_ACTIVE_CYCLES_PLBU_CLIPPER                         = 0x1f, gone */
	MGP2_PERF_SRC_ACTIVE_CYCLES_SCISSOR_TILE_ITERATOR                = 0x20,
	MGP2_PERF_SRC_ACTIVE_CYCLES_PLBU_TILE_ITERATOR                   = 0x21  /* had bad name */
};