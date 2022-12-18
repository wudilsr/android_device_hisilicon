/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_BASE_ARCH_MEM_INLINE_H_
#define _MALI_BASE_ARCH_MEM_INLINE_H_

#include <base/mali_memory_types.h>
#include <base/mali_byteorder.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Definition of the arch memory descriptor type
 * Each memory allocation used by the base driver
 * is actually embedded in this struct.
 * Contains the info we need to give to the device driver and
 * locally cached data from the device driver.
 */
typedef struct arch_mem
{
	mali_mem embedded_mali_mem; /**< The mali memory descriptor*/
	mali_bool is_head_of_block; /**< Flag telling if this block is first inside a big block */
	mali_bool is_tail_of_block; /**< Flag telling if this block is last inside a big block */
	uintptr_t cookie; /**< Cookie received from the device driver identifying the allocation, used in DD calls */
	u32 cookie_backend; /**< Cookie set by the MMU/non-MMU specific backend, if needed */
	void *mapping;  /**< Mapping inside the process for this memory */
	u32 mapping_size; /**< Size of process (CPU) mapping */
	u32 flags; /**< The capabilties of this memory */
} arch_mem;

/**
 * Get arch memory pointer for a base descriptor
 * Each base descriptor is embedded in an arch descriptor, so just perform an offset
 * @note The given pointer is never checked against NULL
 * @param mem Pointer to a base descriptor
 * @return Pointer to an arch descriptor
 */
MALI_STATIC_INLINE arch_mem *arch_mem_from_mali_mem(mali_mem *mem)
{
	return (arch_mem *)(((u8 *)mem) - offsetof(arch_mem, embedded_mali_mem));
}

MALI_STATIC_INLINE void _mali_base_arch_mem_read(void *to, mali_mem *from_mali, u32 from_offset, u32 size)
{
	/* implemented in user space since all memory is currently mappable */
	arch_mem *mem;

	mem = arch_mem_from_mali_mem(from_mali);

	MALI_DEBUG_ASSERT_POINTER(to);
	MALI_DEBUG_ASSERT_POINTER(from_mali);
	MALI_DEBUG_ASSERT(MALI_TRUE == from_mali->is_allocated, ("Operation on free memory block 0x%X detected", from_mali));
	MALI_DEBUG_ASSERT(from_offset <= from_mali->size, ("Offset outside memory block during read"));
	MALI_DEBUG_ASSERT((from_offset + size) <= from_mali->size, ("Would read outside memory block"));
	MALI_DEBUG_ASSERT_POINTER(mem->mapping);
	MALI_DEBUG_PRINT(6, ("Reading from Mali memory\n"));
	_mali_sys_memcpy(to, (void *)(((uintptr_t)mem->mapping) + from_offset), size);
}

MALI_STATIC_INLINE void _mali_base_arch_mem_read_mali_to_cpu(void *to, mali_mem *from_mali, u32 from_offset, u32 size, u32 typesize)
{
	/* implemented in user space since all memory is currently mappable */
	arch_mem *mem;

	mem = arch_mem_from_mali_mem(from_mali);

	MALI_DEBUG_ASSERT_POINTER(to);
	MALI_DEBUG_ASSERT_POINTER(from_mali);
	MALI_DEBUG_ASSERT(MALI_TRUE == from_mali->is_allocated, ("Operation on free memory block 0x%X detected", from_mali));
	MALI_DEBUG_ASSERT(from_offset <= from_mali->size, ("Offset outside memory block during read"));
	MALI_DEBUG_ASSERT((from_offset + size) <= from_mali->size, ("Would read outside memory block"));
	MALI_DEBUG_ASSERT_POINTER(mem->mapping);
	MALI_DEBUG_PRINT(6, ("Reading from Mali memory, endian safe routine\n"));

	MALI_IGNORE(typesize);

	_mali_byteorder_copy_mali_to_cpu(to, (void *)(((uintptr_t)mem->mapping) + from_offset), size, typesize);
}

MALI_STATIC_INLINE void _mali_base_arch_mem_write(mali_mem *to_mali, u32 to_offset, const void *from, u32 size)
{
	arch_mem *mem;

	mem = arch_mem_from_mali_mem(to_mali);

	MALI_DEBUG_ASSERT_POINTER(to_mali);
	MALI_DEBUG_ASSERT_POINTER(from);
	MALI_DEBUG_ASSERT(MALI_TRUE == to_mali->is_allocated, ("Operation on free memory block 0x%X detected", to_mali));
	MALI_DEBUG_ASSERT(to_offset <= to_mali->size, ("Attempt to write outside mali memory write detected"));
	MALI_DEBUG_ASSERT((to_offset + size) <= to_mali->size, ("Attempt to write outside mali memory write detected"));
	MALI_DEBUG_ASSERT_POINTER(mem->mapping);
	MALI_DEBUG_PRINT(4, ("Writing to Mali memory @ 0x%X\n", (void *)(((uintptr_t)mem->mapping) + to_offset)));

	_mali_sys_memcpy((void *)(((uintptr_t)mem->mapping) + to_offset), from, size);
}

MALI_STATIC_INLINE void _mali_base_arch_mem_write_cpu_to_mali(mali_mem *to_mali, u32 to_offset, const void *from, u32 size, u32 typesize)
{
	arch_mem *mem;

	mem = arch_mem_from_mali_mem(to_mali);

	MALI_IGNORE(typesize);

	MALI_DEBUG_ASSERT_POINTER(to_mali);
	MALI_DEBUG_ASSERT_POINTER(from);
	MALI_DEBUG_ASSERT(MALI_TRUE == to_mali->is_allocated, ("Operation on free memory block 0x%X detected", to_mali));
	MALI_DEBUG_ASSERT(to_offset <= to_mali->size, ("Attempt to write outside mali memory write detected"));
	MALI_DEBUG_ASSERT((to_offset + size) <= to_mali->size, ("Attempt to write outside mali memory write detected"));
	MALI_DEBUG_ASSERT_POINTER(mem->mapping);
	MALI_DEBUG_PRINT(6, ("Writing to Mali memory @ 0x%X, endian safe routine\n", (void *)(((uintptr_t)mem->mapping) + to_offset)));
	MALI_DEBUG_PRINT(3, ("----- write %d bytes @ 0x%08x, endian safe routine\n", size, mem->embedded_mali_mem.mali_addr + to_offset));

	_mali_byteorder_copy_cpu_to_mali((void *)(((uintptr_t)mem->mapping) + to_offset), from, size, typesize);
}
MALI_STATIC_INLINE void _mali_base_arch_mem_copy(mali_mem *to_mali, u32 to_offset, mali_mem *from_mali, u32 from_offset, u32 size)
{
	arch_mem *mem_source, * mem_destination;

	mem_destination = arch_mem_from_mali_mem(to_mali);
	mem_source = arch_mem_from_mali_mem(from_mali);

	MALI_DEBUG_ASSERT_POINTER(to_mali);
	MALI_DEBUG_ASSERT(MALI_TRUE == to_mali->is_allocated, ("Operation on free memory block 0x%X detected", to_mali));
	MALI_DEBUG_ASSERT(to_offset <= to_mali->size, ("Write outside copy destination"));
	MALI_DEBUG_ASSERT((to_offset + size) <= to_mali->size, ("Write outside copy destination"));
	MALI_DEBUG_ASSERT_POINTER(mem_destination->mapping);
	MALI_DEBUG_ASSERT_POINTER(from_mali);
	MALI_DEBUG_ASSERT(MALI_TRUE == from_mali->is_allocated, ("Operation on free memory block 0x%X detected", from_mali));
	MALI_DEBUG_ASSERT(from_offset <= from_mali->size, ("Read from outside copy source buffer"));
	MALI_DEBUG_ASSERT((from_offset + size) <= from_mali->size, ("Read from outside copy source buffer"));
	MALI_DEBUG_ASSERT_POINTER(mem_source->mapping);

	_mali_sys_memcpy((void *)(((uintptr_t)mem_destination->mapping) + to_offset),
	                 (void *)(((uintptr_t)mem_source->mapping) + from_offset), size);
}

MALI_STATIC_INLINE void _mali_base_arch_mem_write_cpu_to_mali_32(mali_mem *to_mali, u32 to_offset, const void *from, u32 size, u32 typesize)
{
	arch_mem *mem;
	const u32 *src32;
	u32 *dst32;

	MALI_IGNORE(typesize);

	mem = arch_mem_from_mali_mem(to_mali);

	dst32 = (u32 *)(((uintptr_t)mem->mapping) + to_offset);
	src32 = (u32 *)from;

	MALI_DEBUG_ASSERT_POINTER(to_mali);
	MALI_DEBUG_ASSERT_POINTER(from);
	MALI_DEBUG_ASSERT(MALI_TRUE == to_mali->is_allocated, ("Operation on free memory block 0x%X detected", to_mali));
	MALI_DEBUG_ASSERT(to_offset <= to_mali->size, ("Attempt to write outside mali memory write detected"));
	MALI_DEBUG_ASSERT((to_offset + size) <= to_mali->size, ("Attempt to write outside mali memory write detected"));
	MALI_DEBUG_ASSERT_POINTER(mem->mapping);
	MALI_DEBUG_PRINT(6, ("Writing to Mali memory @ 0x%X, endian safe routine\n", (void *)(((uintptr_t)mem->mapping) + to_offset)));
	MALI_DEBUG_PRINT(3, ("----- write %d bytes @ 0x%08x, endian safe routine\n", size, mem->embedded_mali_mem.mali_addr + to_offset));
	MALI_DEBUG_ASSERT_ALIGNMENT(dst32, 4);
	MALI_DEBUG_ASSERT_ALIGNMENT(src32, 4);

	_mali_byteorder_copy_cpu_to_mali(dst32, src32, size, typesize);
}

MALI_STATIC_INLINE u32 _mali_base_arch_mem_get_cookie(mali_mem *memh)
{
	arch_mem *mem;
	mem = arch_mem_from_mali_mem(memh);

	return mem->cookie_backend;
}

#ifdef __cplusplus
}
#endif

#endif /* _MALI_BASE_ARCH_MEM_INLINE_H_ */

