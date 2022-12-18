/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2011, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef MALI_MEM_POOL_H
#define MALI_MEM_POOL_H

#include <mali_system.h>
#include <base/mali_context.h>
#include <base/mali_memory.h>

struct _mali_mmp_superblock;
struct _mali_mmp_block;

/**
 * The main memory pool structure for Mali accessible memory.
 * The members of this struct should not be accessed directly.
 */
typedef struct mali_mem_pool_
{
	mali_base_ctx_handle base_ctx;                /**< The base driver context to make allocations from */
	struct _mali_mmp_superblock *last_superblock; /**< The current superblock (block of blocks) from which allocations are made */
	struct _mali_mmp_block *current_block;        /**< The current memory block from which allocations are made */
	int map_nesting;                              /**< The number of active mappings */
} mali_mem_pool;

/**
 * Initializes the memory pool.
 * Should be done once for each allocated memory pool.
 *
 * @param pool A pointer to the memory pool to initialize
 * @param base_ctx A pointer to the base driver context to allocate mali memory from
 * @return An error code indicating success or failure
 */
MALI_IMPORT MALI_CHECK_RESULT mali_err_code _mali_mem_pool_init(mali_mem_pool *pool, mali_base_ctx_handle base_ctx);

/**
 * Destroys the memory pool.
 * Should be done once for each allocated memory pool, when the memory allocated through the pool
 * is no longer referenced anywhere.
 *
 * @param pool A pointer to the memory pool to destroy
 */
MALI_IMPORT void _mali_mem_pool_destroy(mali_mem_pool *pool);

/**
 * Maps the memory pool.
 * The memory pool must be mapped before any allocations can be made from it. It is
 * legal to map the pool multiple times.
 *
 * Each call to _mali_mem_pool_map should have a corresponding call to _mali_mem_pool_unmap, but
 * it is acceptable to call _mali_mem_pool_destroy on a mapped memory pool.
 *
 * @param pool A pointer to the memory pool to map
 * @return An error code indicating success or failure
 */
MALI_IMPORT MALI_CHECK_RESULT mali_err_code _mali_mem_pool_map(mali_mem_pool *pool);

/**
 * Unmaps the memory pool.
 * Each call to _mali_mem_pool_map should have a corresponding call to _mali_mem_pool_unmap.
 *
 * @param pool A pointer to the memory pool to unmap
 */
MALI_IMPORT void _mali_mem_pool_unmap(mali_mem_pool *pool);

/**
 * Allocates memory from the pool.
 * A CPU read/writeable pointer will be returned, and the Mali address of the memory will
 * be written to the last function parameter.
 *
 * @param pool A pointer to the memory pool to allocate from
 * @param size The number of bytes to allocate
 * @param mali_mem_addr A pointer to where the Mali address of the allocation will be written
 * @param mali_type to mark the mem usage
 * @return A pointer (CPU read/writeable) to the allocated memory, or NULL on failure.
 */
MALI_IMPORT void *_mali_mem_pool_alloc(mali_mem_pool *pool, u32 size, mali_addr *mali_mem_addr, u32 mali_type);

/**
 * Allocates memory from the pool.
 * A CPU read/writeable pointer will be returned, and the Mali address of the memory will
 * be written to the mali_mem_addr parameter. In addition the block handle and offset will be written to the last two parameters
 * The memory handle will be returned to the handle adress and the offset to the offset adress.
 *
 * @param pool A pointer to the memory pool to allocate from
 * @param size The number of bytes to allocate
 * @param mali_mem_addr A pointer to where the Mali address of the allocation will be written
 * @param handle[out] The allocation handle will be written here
 * @param offset[out] The allocation offset will be written here
 * @return A pointer[out] (CPU read/writeable) to the allocated memory, or NULL on failure.
 */
MALI_IMPORT void *_mali_mem_pool_alloc_with_handle_and_offset(mali_mem_pool *pool, u32 size, mali_addr *mali_mem_addr, mali_mem_handle *handle, u32 *offset);

#endif /* MALI_MEM_POOL_H */
