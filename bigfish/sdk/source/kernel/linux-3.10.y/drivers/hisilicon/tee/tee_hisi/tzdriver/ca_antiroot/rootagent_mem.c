/*
 * FileName:      rootagent_mem.c
 * Author:        z00321956
 * Description:   rootagent memory initial
 * Version:       0.0.1
 * Date:          2016-04-01
 */
#include <linux/mm.h>
#include "teek_client_type.h"
#include "rootagent_mem.h"
#include "rootagent_common.h"

static void *g_rw_mem_pre_allocated = NULL;
static void *g_swap_mem_pre_allocated = NULL;
static int g_mem_flag = 0;
#define RM_PRE_ALLOCATE_SIZE 4096
#define ROUND_UP(N, S) ((((N) + (S) - 1) / (S)) * (S))

int rm_mem_init(void){

    if(!g_mem_flag){
        g_rw_mem_pre_allocated = (void*) __get_free_pages(GFP_KERNEL,
            get_order(ROUND_UP(RM_PRE_ALLOCATE_SIZE, SZ_4K)));
        if(!g_rw_mem_pre_allocated){
            antiroot_error("mem allocated failed\n");
            return -1;
        }

        g_swap_mem_pre_allocated = (void*) __get_free_pages(GFP_KERNEL,
            get_order(ROUND_UP(RM_PRE_ALLOCATE_SIZE, SZ_4K)));
        if(!g_swap_mem_pre_allocated){
            antiroot_error("Swap mem allocated failed\n");
            free_pages((unsigned long)g_rw_mem_pre_allocated,
                get_order(ROUND_UP(RM_PRE_ALLOCATE_SIZE, SZ_4K)));
            g_rw_mem_pre_allocated = NULL;
            return -1;
        }
        g_mem_flag = 1;
    }

	antiroot_debug(ROOTAGENT_DEBUG_MEM, "rm_mem_init successful!\n");
	return 0;
}

void rm_mem_destroy(void)
{
	if(g_rw_mem_pre_allocated){
		free_pages((unsigned long)g_rw_mem_pre_allocated,
			   get_order(ROUND_UP(RM_PRE_ALLOCATE_SIZE, SZ_4K)));
        g_rw_mem_pre_allocated = NULL;
    }
	if(g_swap_mem_pre_allocated){
		free_pages((unsigned long)g_swap_mem_pre_allocated,
			   get_order(ROUND_UP(RM_PRE_ALLOCATE_SIZE, SZ_4K)));
        g_swap_mem_pre_allocated = NULL;
    }
}

int initial_rm_shared_mem(TEEC_TempMemoryReference* rwMem, TEEC_TempMemoryReference* swapMem){

    if(!swapMem || ! rwMem){
        antiroot_error("Bad param!\n");
        return -1;
    }

    if(g_swap_mem_pre_allocated){
        swapMem->buffer = g_swap_mem_pre_allocated;
        swapMem->size = SZ_4K;
    }else{
        antiroot_error("initial_rm_shared_mem failed!\n");
        return -1;
    }

    if(g_rw_mem_pre_allocated){
        rwMem->buffer = g_rw_mem_pre_allocated;
        rwMem->size = SZ_4K;
    }else{
        antiroot_error("initial_rm_shared_mem failed!\n");
        return -1;
    }
    antiroot_debug(ROOTAGENT_DEBUG_MEM, "initial_rm_shared_mem successful!\n");
    return 0;
}
