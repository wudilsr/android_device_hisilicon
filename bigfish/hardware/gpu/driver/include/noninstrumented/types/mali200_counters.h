/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI200_COUNTERS_H_
#define _MALI200_COUNTERS_H_

#define M200_MULTI_CORE_OFFSET 1000 /* 1000 values between each core */

enum mali200_counter_ids                /* NB HW codes below, not the enum values */
{
	CID_M200_ACTIVE_CLOCK_CYCLES_COUNT = MALI_M200_COUNTER_OFFSET ,
	CID_M200_TOTAL_CLOCK_CYCLES_COUNT_REMOVED                     ,
	CID_M200_TOTAL_BUS_READS                                      ,
	CID_M200_TOTAL_BUS_WRITES                                     ,
	CID_M200_BUS_READ_REQUEST_CYCLES_COUNT                        ,
	CID_M200_BUS_WRITE_REQUEST_CYCLES_COUNT                       ,
	CID_M200_BUS_READ_TRANSACTIONS_COUNT                          ,
	CID_M200_BUS_WRITE_TRANSACTIONS_COUNT                         ,
	CID_M200_RESERVED_08                                          ,
	CID_M200_TILE_WRITEBACK_WRITES                                ,
	CID_M200_STORE_UNIT_WRITES                                    , /* HW: 10 */
	CID_M200_RESERVED_11                                          ,
	CID_M200_PALETTE_CACHE_READS_REMOVED                          ,
	CID_M200_TEXTURE_CACHE_UNCOMPRESSED_READS                     ,
	CID_M200_POLYGON_LIST_READS                                   ,
	CID_M200_RSW_READS                                            ,
	CID_M200_VERTEX_CACHE_READS                                   ,
	CID_M200_UNIFORM_REMAPPING_READS                              ,
	CID_M200_PROGRAM_CACHE_READS                                  ,
	CID_M200_VARYING_READS                                        ,
	CID_M200_TEXTURE_DESCRIPTORS_READS                            , /*  HW: 20 */
	CID_M200_TEXTURE_DESCRIPTORS_REMAPPING_READS                  ,
	CID_M200_TEXTURE_CACHE_COMPRESSED_READS_REMOVED               ,
	CID_M200_LOAD_UNIT_READS                                      ,
	CID_M200_POLYGON_COUNT                                        ,
	CID_M200_PIXEL_RECTANGLE_COUNT                                ,
	CID_M200_LINES_COUNT                                          ,
	CID_M200_POINTS_COUNT                                         ,
	CID_M200_STALL_CYCLES_POLYGON_LIST_READER                     ,
	CID_M200_STALL_CYCLES_TRIANGLE_SETUP                          ,
	CID_M200_QUAD_RASTERIZED_COUNT                                , /* HW: 30 */
	CID_M200_FRAGMENT_RASTERIZED_COUNT                            ,
	CID_M200_FRAGMENT_REJECTED_FRAGMENT_KILL_COUNT                ,
	CID_M200_FRAGMENT_REJECTED_FWD_FRAGMENT_KILL_COUNT            ,
	CID_M200_FRAGMENT_PASSED_ZSTENCIL_COUNT                       ,
	CID_M200_PATCHES_REJECTED_EARLY_Z_STENCIL_COUNT               ,
	CID_M200_PATCHES_EVALUATED                                    ,
	CID_M200_INSTRUCTION_COMPLETED_COUNT                          ,
	CID_M200_INSTRUCTION_FAILED_RENDEZVOUS_COUNT                  ,
	CID_M200_INSTRUCTION_FAILED_VARYING_MISS_COUNT                ,
	CID_M200_INSTRUCTION_FAILED_TEXTURE_MISS_COUNT                , /* HW: 40 */
	CID_M200_INSTRUCTION_FAILED_LOAD_MISS_COUNT                   ,
	CID_M200_INSTRUCTION_FAILED_TILE_READ_MISS_COUNT              ,
	CID_M200_INSTRUCTION_FAILED_STORE_MISS_COUNT                  ,
	CID_M200_RENDEZVOUS_BREAKAGE_COUNT                            ,
	CID_M200_PIPELINE_BUBBLES_CYCLE_COUNT                         ,
	CID_M200_TEXTURE_MAPPER_MULTIPASS_COUNT                       ,
	CID_M200_TEXTURE_MAPPER_CYCLE_COUNT                           ,
	CID_M200_VERTEX_CACHE_HIT_COUNT                               ,
	CID_M200_VERTEX_CACHE_MISS_COUNT                              ,
	CID_M200_VARYING_CACHE_HIT_COUNT                              , /* HW: 50 */
	CID_M200_VARYING_CACHE_MISS_COUNT                             ,
	CID_M200_VARYING_CACHE_CONFLICT_MISS_COUNT                    ,
	CID_M200_TEXTURE_CACHE_HIT_COUNT                              ,
	CID_M200_TEXTURE_CACHE_MISS_COUNT                             ,
	CID_M200_TEXTURE_CACHE_CONFLICT_MISS_COUNT                    ,
	CID_M400_COMPRESSED_TEXTURE_CACHE_HIT_COUNT                   ,
	CID_M400_COMPRESSED_TEXTURE_CACHE_MISS_COUNT                  ,
	CID_M200_LOAD_STORE_CACHE_HIT_COUNT                           ,
	CID_M200_LOAD_STORE_CACHE_MISS_COUNT                          ,
	CID_M200_PROGRAM_CACHE_HIT_COUNT                              , /* HW: 60 */
	CID_M200_PROGRAM_CACHE_MISS_COUNT                             ,
	CID_M200_ENUM_MAX
};

enum mali200_performance_ids
{
	CID_M200_FRAME_TIME = CID_M200_ENUM_MAX + 1,
	CID_M200_FPS,
	CID_M200_INSTRUCTION_RATE,
	CID_M200_PRIMITIVE_RATE,
	CID_M200_FILL_RATE,
	CID_M200_TRIANGLE_PROCESSING_BW,
	CID_M200_TEXTURE_BW,
	CID_M200_INPUT_BW,
	CID_M200_INTERNAL_SHADER_BW,
	CID_M200_OUTPUT_BW,
	CID_M200_TOTAL_BW,
	CID_M200_JOB_COUNT_CORE_0, /* These CID_M200_JOB_COUNT_CORE_X counter are actually added under HW counters. */
	CID_M200_JOB_COUNT_CORE_1, /* They are put here so that they can have a fixed ID. */
	CID_M200_JOB_COUNT_CORE_2, /* If I added them to the HW enum above, then I would have to move them if new */
	CID_M200_JOB_COUNT_CORE_3, /* HW counters where added. */
	CID_M200_JOB_COUNT_CORE_4,
	CID_M200_JOB_COUNT_CORE_5,
	CID_M200_JOB_COUNT_CORE_6,
	CID_M200_JOB_COUNT_CORE_7
};

#endif /* _MALI200_COUNTERS_H_ */

