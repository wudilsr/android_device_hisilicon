/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file mali_memory_types.h
 * File contains functions memory-related type definitions
 *
 */
#ifndef _MALI_MEMORY_TYPES_H_
#define _MALI_MEMORY_TYPES_H_

#include <base/mali_types.h>
#include <base/mali_macros.h>
#include <base/mali_context.h>
#include <base/mali_fence.h>
#include <mali_system.h>
#include <base/common/tools/base_common_tools_circular_linked_list.h>

#define MEM_HIST_SIZE 8

#if MALI_USE_UNIFIED_MEMORY_PROVIDER != 0
#include <ump/ump.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Type definition of mali_addr to u32
 */
typedef u32 mali_addr;

/** Mali Page Order, as log to base 2 of the Page size. @see MALI_PAGE_SIZE */
#define MALI_PAGE_ORDER ((u32)12)
/** Mali Page Size, in bytes. */
#define MALI_PAGE_SIZE (((u32)1) << (MALI_PAGE_ORDER))
/** Mali Page Mask, which masks off the offset within a page */
#define MALI_PAGE_MASK (~((((u32)1) << (MALI_PAGE_ORDER)) - ((u32)1)))

/**
 * Properties for the LOCK_AREA function below
 */
typedef enum mali_mem_ptr_flag
{
	MALI_MEM_PTR_READABLE          = (1 << 0), /* CPU can read from ptr */
	MALI_MEM_PTR_WRITABLE          = (1 << 1), /* CPU can write to ptr */
	MALI_MEM_PTR_NO_PRE_UPDATE     = (1 << 16) /* mem is updated from mali_mem */
} mali_mem_ptr_flag;



typedef enum mali_mem_rights
{
	MALI_MEM_RIGHT_PP_READ              = (1 << 0),
	MALI_MEM_RIGHT_PP_WRITE             = (1 << 1),
	MALI_MEM_RIGHT_GP_READ              = (1 << 2),
	MALI_MEM_RIGHT_GP_WRITE             = (1 << 3),
	MALI_MEM_RIGHT_CPU_READ             = (1 << 4),
	MALI_MEM_RIGHT_CPU_WRITE            = (1 << 5),
	MALI_MEM_RIGHT_GP_L2_ALLOCATE       = (1 << 6),
} mali_mem_rights;

typedef struct mali_mem_type
{
	mali_addr mali_address; /**< The Mali seen address of this block. Valid if cpu_address is set*/
	void *cpu_address;      /**< The CPU  seen address of this block */
} mali_mem_type, *mali_mem_handle;

/**
 * Architecture bank descriptor
 * This type is used by the architecture to describe a memory bank
 */
typedef struct mali_mem_bank_info
{
	u32 capabilities; /**< The possible rights of this bank */
	u32 cache_settings; /**< mali_memory_cache_settings cache_settings;  */
	u32 maximum_order_supported; /**< Order of largest allocation possible */
} mali_mem_bank_info;

/* forward decl of mali_mem */
struct mali_mem;

/**
 * The mali memory bank type.
 * Represents the various types of memory banks available on the system.
 * Each bank has info abouts
 */
typedef struct mali_mem_bank
{
	/* placed first so the compiler can optimize away pointer correction when walking the linked list */
	mali_embedded_list_link link; /**< Used to Link multiple banks together */

	mali_mutex_handle mutex /**< Mutex protecting manipulation of this bank */;
	u32 rights; /**< The rights of the memory this bank represent */
	u32 cache_settings; /**< Cache settings of type mali_memory_cache_settings */

	mali_embedded_list_link *free_list_exact;  /**< Free list of exact pow2 sizes */
	mali_embedded_list_link *free_list_bigger;  /**< Free list of non pow2 sizes */
	mali_embedded_list_link all_memory; /**< All memory which exists in this bank */
	mali_embedded_list_link full_blocks; /**< List of free full blocks */

	u8 order_minimum; /**< Order of minimum allocation size */
	u8 order_maximum; /**< Order of maximum allocation size */

	u32 size_allocated; /**< Total size of all current allocations */
	u32 past_size_allocated[MEM_HIST_SIZE];     /**< Total size of previous allocations */
	u32 holdback_size; /**< How much memory we should hold back in any period */

	u32 allocated_elements; /**< The number of allocated blocks */
	u32 free_list_elements; /**< The number of blocks on the free list */
	u32 free_list_size;     /**< Number of free bytes */
} mali_mem_bank;

/**
* Enum used to indicate the subtype of memory the mali_mem struct represents
*/
typedef enum mali_mem_subtype
{
	MALI_MEM_TYPE_INVALID, /**< Blank memory descriptor */
	MALI_MEM_TYPE_NORMAL, /**< A Normal allocation */
	MALI_MEM_TYPE_HEAP, /**< Heap object */
	MALI_MEM_TYPE_EXTERNAL_MEMORY, /**< External memory reference, not managed by the Base driver */
	MALI_MEM_TYPE_UMP_EXTERNAL_MEMORY, /**< External memory reference, not managed by the Base driver, special cased as it's UMP */
	MALI_MEM_TYPE_DMA_BUF_EXTERNAL_MEMORY /**< External memory reference, not managed by the Base driver, special cased as it's dma_buf */
} mali_mem_subtype;

typedef struct mali_mem
{
	/* must be placed first */
	mali_mem_type cached_addr_info;

	mali_embedded_list_link memlink; /**< Used to link memory blocks on the all_memory list */
	u32 mali_addr; /**< The Mali seen address of this block */
	u32 size; /**< The size of this block */
	u32 order; /**< The order of this block */
	u32 alignment; /**< Alignment requested for this block */

	mali_mem_subtype memory_subtype; /**< The memory subtype */

	u32 memory_usage;	/** < The usage of GLES */

	mali_bool is_pow2; /**< Is pow2? */
	mali_bool is_allocated; /**< Current allocation status */

	u32 effective_rights; /**< Rights requested when this block was allocated */

	mali_atomic_int cpu_map_ref_count; /**< Reference count of users of the CPU mapping */

#ifdef MALI_TEST_API
	u32 size_used_to_alloc_call; /**< Stores the requested size, the real size might be larger */
#endif

	/**
	 * Union of circular linked list used internally when free
	 * and pointers used by the user while allocated
	 */
	union
	{
		struct
		{
			struct mali_mem *next;  /**< Used when allocated and put on a user defined linked list */
			struct mali_mem *prev;  /**< Used when allocated and put on a user defined linked list */
		} user;
		mali_embedded_list_link link; /**< Used when on a free list */
	} custom;

	mali_embedded_list_link full_block_link; /**< Used when this is a full free memory block */
	u32 frame_counter;                       /**< The "timestamp" when this was added to the full_blocks free list */

	/**
	 * Union of bank parent or heap object
	 * The is_heap variable determines which of these two fields are valid
	 */
	union
	{
		mali_mem_bank *parent;  /**< Pointer to the memory bank this block belongs to */
		void *heap;  /**< Pointer to heap data when describing a heap */
		mali_base_ctx_handle ctx; /**< Base context the external memory was scoped to */
#if MALI_USE_DMA_BUF
		int dma_buf_fd; /**< File descriptor representing the shared memory */
#endif
#if MALI_USE_UNIFIED_MEMORY_PROVIDER != 0
		ump_handle ump_mem;
#endif
	} relationship;
#ifdef MALI_MEMORY_PROFILING
	/* When this define is enabled, all functions that allocate mali memory
	    are routed through macros that store additional information about where the
	    allocation was made in the data to the returned memory_handle */
	const char *function_name;  /**< The name of the function that allocated this memory.*/
	const char *file_name;      /**< The name of the file that allocated this memory. */
	u32 line_nr;                /**< The line number in the file where the allocation took place */
	u32 alloc_nr;               /**< How many allocation the system have had before this one */
	u64 alloc_time;             /**< The time in msecs between this and the first allocation */
	u32 frame_nr;               /**< Frame number of the allocation */
#endif /* #ifdef MALI_MEMORY_PROFILING */
#if MALI_MEM_STATUS
	mali_bool just_allocated_from_kernel;
	u32 frame_nr_touched;
#endif
	mali_atomic_int ref_count; /**< Reference count of users of the memory */
	mali_atomic_int read_counter; /**< Read counter. Used to decide when COW is needed */
	struct mali_fence writer_fence; /**< Fence for waiting on jobs that are writing to this memory */
} mali_mem;


/**
 * Definition of the heap object struct
 * Used for heaps on non-MMU systems
 */
typedef struct heap_extended_data
{
	mali_mem_handle first; /**< The first handle allocated to this heap */
	mali_mem_handle last; /**< The last handle allocated to this heap */
	u32 block_size; /**< The size to use for allocations when extening the heap */
	u32 maximum_size; /**< The maximum size the heap is allowed to grow to */
	u32 current_phys_addr; /**< Mali address of first available address */
	mali_base_ctx_handle ctx; /**< The base context this heap was created in */
} heap_extended_data;

#ifdef __cplusplus
}
#endif

#endif /* _MALI_MEMORY_TYPES_H_ */

