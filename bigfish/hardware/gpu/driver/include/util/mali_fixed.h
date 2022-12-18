/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2005, 2007-2010, 2012-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_FIXED_H_
#define _MALI_FIXED_H_

#include <mali_system.h>

#include "mali_math.h"

typedef s32 mali_fixed;

extern const u32 _mali_rcp_table[512];

/* Routine for doing common part of reciprocal of 16.16 fixed point numbers
 * @param f value to convert
 * @param right_shift pointer to location to store right-shift required to convert result to 16.16
 * @param is_neg pointer to location to store negative flag of the result
 * @return 1/f * 1<<right_shift in 16.16 format, sign determined by *is_neg
 * @note this has worst case precision of about 14 bits. Use Newton-Raphson for better precision and memory constraints.
 */

MALI_STATIC_INLINE u32 _mali_fixed_rcp_unshifted(mali_fixed f, u32 *right_shift, u32 *is_neg)
{
	u32 v, v1, v2, v3;
	u32 zero_bits;

	/*
	    This routine utilize the mathematical symmetries of reciprocals:
	        1 / x = (1 / (x * n)) * n

	    This is utilized by having a  LUT of 1/x in the range 1..2, and adjusting n to always fit x * n between 1 and 2.
	*/

	/* store away sign for later */
	s32 neg = f < 0;

	/* This avoids us having a negative right_shift */
	MALI_DEBUG_ASSERT(f != 0, ("reciprocal of zero attempted"));

	/* take absolute value */
	if (neg)
	{
		f = -f;
	}

	/* find magnitude of the number */
	zero_bits = _mali_clz(MALI_STATIC_CAST(u32)f);

	/* normalize number to 1..2 range (2.30 fixed point) */
	v = f << zero_bits;

	/* Look up. The LUT contains linear curve coefficients for 1/x in the 0..2 range.
	   However, only the 1..2 range should be used for non-zero numbers.
	*/
	v1 = _mali_rcp_table[v >> 23];

	/* linear interpolation */
	v2 = (v >> 14) & 511;
	v3 = _mali_smlabb(v1, v2, v1);

	/* write out the sign */
	*is_neg = (neg) ? 1 : 0;

	/* write out the shift required */
	*right_shift = 31 - zero_bits;

	return v3;
}

#if defined(_GNUC_) && defined(ARM) && !defined(THUMB)

/* GCC inline assembly versions */

MALI_STATIC_INLINE mali_fixed _mali_fixed_rcp(mali_fixed input)
{
	s32 tmp, res;
	MALI_DEBUG_ASSERT(input != 0, ("reciprocal of zero attempted"));

	__asm__ __volatile__(
	    "cmp %3, #0					\n\r"
	    "rsblt %2, %3, #0			\n\r"
	    "clz %0, %2					\n\r"
	    "mov %1, %2, lsl %0			\n\r"
	    "mov %2, %1, lsr #23		\n\r"
	    "ldr %2, [%4, %2, lsl #2]	\n\r"
	    "and %1, %5, %1, lsr #14	\n\r"
	    "smlabb %1, %2, %1, %2		\n\r"
	    "rsb %0, %0, #31			\n\r"
	    "mov %1, %1, lsr %0			\n\r"
	    "rsblt %1, %1, #0			\n\r"
	    : "=&r"(tmp), "=&r"(res)
	    : "r"(input), "r"(input), "r"(_mali_rcp_table), "r"(511)
	    : "2");
	return (mali_fixed)res;
}

#else

/* ANSI C versions */

/* 16.16 fixed point reciprocal routine */
MALI_STATIC_INLINE mali_fixed _mali_fixed_rcp(mali_fixed f)
{
	u32 right_shift;
	u32 is_neg;
	u32 v;
	s32 result;

	v = _mali_fixed_rcp_unshifted(f, &right_shift, &is_neg);

	/* NOTE: input of f==0x1 (1/65536) is unrepresentable here */
	result = v >> right_shift;

	if (is_neg)
	{
		result = -result;
	}

	return result;
}

#endif

#endif /* _MALI_FIXED_H_ */
