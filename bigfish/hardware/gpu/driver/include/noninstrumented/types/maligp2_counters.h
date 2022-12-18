/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALIGP2_COUNTERS_H_
#define _MALIGP2_COUNTERS_H_

enum maligp2_counter_ids
{
	CID_MGP2_CYCLE_COUNTER_DEPRECATED = MALI_MGP2_COUNTER_OFFSET  , /*  0 */
	CID_MGP2_ACTIVE_CYCLES_MGP2                                   , /*  1 */
	CID_MGP2_ACTIVE_CYCLES_VERTEX_SHADER                          , /*  2 */
	CID_MGP2_ACTIVE_CYCLES_VERTEX_STORER                          , /*  3 */
	CID_MGP2_ACTIVE_CYCLES_VERTEX_LOADER                          , /*  4 */
	CID_MGP2_CYCLES_VERTEX_LOADER_WAITING_FOR_VERTEX_SHADER       , /*  5 */
	CID_MGP2_NUMBER_OF_WORDS_READ                                 , /*  6 */
	CID_MGP2_NUMBER_OF_WORDS_WRITTEN                              , /*  7 */
	CID_MGP2_NUMBER_OF_READ_BURSTS                                , /*  8 */
	CID_MGP2_NUMBER_OF_WRITE_BURSTS                               , /*  9 */
	CID_MGP2_NUMBER_OF_VERTICES_PROCESSED                         , /* 10 */
	CID_MGP2_NUMBER_OF_VERTICES_FETCHED                           , /* 11 */
	CID_MGP2_NUMBER_OF_PRIMITIVES_FETCHED                         , /* 12 */
	CID_MGP2_RESERVED_13                                          , /* 13 */
	CID_MGP2_NUMBER_OF_BACKFACE_CULLINGS_DONE                     , /* 14 */
	CID_MGP2_NUMBER_OF_COMMANDS_WRITTEN_TO_TILES                  , /* 15 */
	CID_MGP2_NUMBER_OF_MEMORY_BLOCKS_ALLOCATED                    , /* 16 */
	CID_MGP2_RESERVED_17                                          , /* 17 */
	CID_MGP2_RESERVED_18                                          , /* 18 */
	CID_MGP2_NUMBER_OF_VERTEX_LOADER_CACHE_MISSES                 , /* 19 */
	CID_MGP2_RESERVED_20                                          , /* 20 */
	CID_MGP2_RESERVED_21                                          , /* 21 */
	CID_MGP2_ACTIVE_CYCLES_VERTEX_SHADER_COMMAND_PROCESSOR        , /* 22 */
	CID_MGP2_ACTIVE_CYCLES_PLBU_COMMAND_PROCESSOR                 , /* 23 */
	CID_MGP2_ACTIVE_CYCLES_PLBU_LIST_WRITER                       , /* 24 */
	CID_MGP2_ACTIVE_CYCLES_THROUGH_THE_PREPARE_LIST_COMMANDS      , /* 25 */
	CID_MGP2_RESERVED_26                                          , /* 26 */
	CID_MGP2_ACTIVE_CYCLES_PRIMITIVE_ASSEMBLY                     , /* 27 */
	CID_MGP2_ACTIVE_CYCLES_PLBU_VERTEX_FETCHER                    , /* 28 */
	CID_MGP2_RESERVED_29                                          , /* 29 */
	CID_MGP2_ACTIVE_CYCLES_BOUNDINGBOX_AND_COMMAND_GENERATOR      , /* 30 */
	CID_MGP2_RESERVED_31                                          , /* 31 */
	CID_MGP2_ACTIVE_CYCLES_SCISSOR_TILE_ITERATOR                  , /* 32 */
	CID_MGP2_ACTIVE_CYCLES_PLBU_TILE_ITERATOR                     , /* 33 */
	CID_MGP2_COUNTER_ENUM_MAX
};


enum maligp2_performance_ids
{
	CID_MGP2_FPS = CID_MGP2_COUNTER_ENUM_MAX + 1,
	CID_MGP2_FRAME_TIME,
	CID_MGP2_VERTEX_SHADER_TIME,
	CID_MGP2_PLBU_TIME,
	CID_MGP2_READ_BW,
	CID_MGP2_WRITE_BW,
	CID_MGP2_TOTAL_BW,
	CID_MGP2_AVERAGE_BURST_LENGTH,
	CID_MGP2_AVERAGE_BURST_LENGTH_READ,
	CID_MGP2_AVERAGE_BURST_LENGTH_WRITE,
	CID_MGP2_VERTICES_RATE,
	CID_MGP2_BACKFACE_CULLINGS_PER_PRIMITIVES_FETCHED,
	CID_MGP2_PRIMITIVE_RATE,
	CID_MGP2_JOB_COUNT /* this counter is actually added under HW counters */
};

#endif /* _MALIGP2_COUNTERS_H_ */

