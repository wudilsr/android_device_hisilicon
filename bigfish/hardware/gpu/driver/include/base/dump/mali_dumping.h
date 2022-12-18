/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2010, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_BASE_DUMP_
#define _MALI_BASE_DUMP_

#ifdef MALI_DUMP_ENABLE

#include "mali_system.h"
#include "base/mali_context.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



typedef struct mali_dump_job_info
{
	mali_bool             is_pp_job;
	u32                   frame_nr;
	u32                   job_nr;
	mali_base_wait_handle inline_waiter;
	mali_sync_handle      dump_sync;

	mali_bool           disable_dump;
	mali_bool           crash_dump_enable;
	mali_bool           pre_run_dump_enable;
	mali_bool           post_run_dump_enable;
	mali_bool           pre_run_dump_done;
	mali_bool           post_run_dump_done;
	char                last_mem_dump_file_name[512];
} mali_dump_job_info ;

typedef struct mali_dump_job_info_gp
{
	mali_dump_job_info  gp;
	mali_mem_handle     pointer_array_user;
	u32                 pointer_array_first_elements[4];
	void               *pointer_array_patch_backup;
} mali_dump_job_info_gp ;

/**
 * Increase the global current frame number by one.
 * The dumping system can be set up to dump spesific frames.
 * It uses the counter controlled by this variable.
 * \param ctx The base context
 */
MALI_IMPORT void _mali_base_common_dump_frame_counter_increment(mali_base_ctx_handle ctx);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MALI_DUMP_ENABLE  - Compiletime toggle*/
#endif /* _MALI_BASE_DUMP_  - Include guard */
