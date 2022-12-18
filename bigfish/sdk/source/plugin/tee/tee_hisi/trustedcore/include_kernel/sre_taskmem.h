/*******************************************************************************
 * All rights reserved, Copyright (C) huawei LIMITED 2012
 *------------------------------------------------------------------------------
 * File Name   : sre_taskmem.h
 * Description : task memory allocator.
 * Author      : h00206996
 * Date        : 2013.5.25
 * Notes       :
 *
 *------------------------------------------------------------------------------
 * Modifications:
 *   Date        Author          Modifications
 *******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
 *******************************************************************************/


#ifndef _SRE_TASKMEM_H
#define _SRE_TASKMEM_H

#define TASK_MAX_ORDER 6 //32M
#define TASK_MEMBLOCK_MAX  (1<<(TASK_MAX_ORDER-1)) //32
#define TASK_MEM_DEFAULT_ORDER 0

#define TASK_MEM_SHIFT 20 //1M size
#define TASK_MEM_BLOCK_SIZE (1<<TASK_MEM_SHIFT) //1M

extern void* SRE_TaskMem_Malloc(UINT32 size, UINT32 hint);
extern void SRE_TaskMem_Free(UINT32* addr);
extern void SRE_TaskMem_Init(void);
extern UINT32 SRE_TaskMem_GetOrder(UINT32 size);
extern UINT32 SRE_TaskMem_GetBase(UINT32 *tasknum);
extern VOID SRE_TaskMem_GetInternalTaskInfo(UINT32 *addr, UINT32 start_index, UINT32 num);
#endif//_SRE_TASKMEM_H
