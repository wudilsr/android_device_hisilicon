/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2011-2013, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_BYTEORDER_H_
#define _MALI_BYTEORDER_H_

#include <mali_system.h>

#ifdef __cplusplus
extern "C" {
#endif


#include <base/arch/base_arch_byteorder.h>

/*
 *  Endian safe memory copy routines
 */

#if MALI_BIG_ENDIAN
/**
 * Copy a memory region from host memory to Mali memory
 * in an endian safe manner.
 *
 * @param destination Destination address
 * @param source Source address
 * @param num Total number of bytes
 * @param element_size Size of one data item in bytes. Can be 1, 2, 4 or 8
 *
 */
MALI_IMPORT void *_mali_byteorder_copy_cpu_to_mali(void *destination, const void *source, u32 num, u32 element_size);

/**
 * Copy a memory region from Mali memory to host memory
 * in an endian safe manner.
 *
 * @param destination Destination address
 * @param source Source address
 * @param num Total number of bytes
 * @param element_size Size of one data item in bytes. Can be 1, 2, 4 or 8
 *
 */
MALI_IMPORT void *_mali_byteorder_copy_mali_to_cpu(void *destination, const void *source, u32 num, u32 element_size);

/**
 * Copy a memory region from Mali memory to Mali memory in an endian safe manner.
 *
 *
 * @param destination Destination address
 * @param source Source address
 * @param num Total number of bytes
 * @param element_size Size of one data item in bytes. Can be 1, 2, 4 or 8
 *
 */
MALI_IMPORT void *_mali_byteorder_copy_mali_to_mali(void *destination, const void *source, u32 num, u32 element_size);

/**
 * Swap endianess of a memory area.
 *
 * @param buf Address of the buffer to shuffle
   @param num Number of memory elements to swap
   @param element_size Size of a single element in bytes. Can be 1, 2, 4 or 8
 */
MALI_IMPORT void _mali_byteorder_swap_endian(void *buf, u32 num, u32 element_size);

/**
 * Set memory in endian safe manner.
 *
 * @param buf Address of the buffer to clear
 * @param val Clear value, the least significant byte is used
 * @param num Number of bytes to clear
 */
MALI_IMPORT void *_mali_byteorder_memset(void *buf, u32 val, u32 num);

#else /* MALI_BIG_ENDIAN */
/*
 * Little-endian equivalents of copy routines.
 *
 * All void
 *
 */

#define _mali_byteorder_copy_cpu_to_mali_32(destination, source, num)  _mali_sys_memcpy_32(destination, source, num)
#define _mali_byteorder_copy_mali_to_cpu_32(destination, source, num)  _mali_sys_memcpy_32(destination, source, num)
#define _mali_byteorder_copy_mali_to_mali_32(destination, source, num) _mali_sys_memcpy_32(destination, source, num)

#define _mali_byteorder_copy_cpu_to_mali_runtime_32(destination, source, num)  _mali_sys_memcpy_runtime_32(destination, source, num)
#define _mali_byteorder_copy_mali_to_cpu_runtime_32(destination, source, num)  _mali_sys_memcpy_runtime_32(destination, source, num)
#define _mali_byteorder_copy_mali_to_mali_runtime_32(destination, source, num) _mali_sys_memcpy_runtime_32(destination, source, num)

#define _mali_byteorder_copy_cpu_to_mali(destination, source, num, element_size) _mali_sys_memcpy(destination, source, num)
#define _mali_byteorder_copy_mali_to_cpu(destination, source, num, element_size) _mali_sys_memcpy(destination, source, num)
#define _mali_byteorder_copy_mali_to_mali(destination, source, num, element_size) _mali_sys_memcpy(destination, source, num)
#define _mali_byteorder_swap_endian(buf, num, element_size) {;} while (0)
#define _mali_byteorder_memset(buf, val, num) _mali_sys_memset(buf, val, num)

#endif /* MALI_BIG_ENDIAN */


#ifdef __cplusplus
}
#endif


#endif /* _MALI_BYTEORDER_H_ */

