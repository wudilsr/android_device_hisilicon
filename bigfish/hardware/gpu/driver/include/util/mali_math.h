/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2005, 2007-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_MATH_H_
#define _MALI_MATH_H_

#include <mali_system.h>

/**
 *  Other common values
 */
#define MALI_PI                 3.14159265358979323
#define MALI_DEGREES_TO_RADIANS (MALI_PI / 180.0f)
#define MALI_RADIANS_TO_DEGREES (180.0f / MALI_PI)
#define MALI_SW_EPSILON 1e-10

/******************************************************************************
                                 PUBLIC FUNCTIONS
 ******************************************************************************/

/**
 * Include inlined functions
 */

#ifdef INLINE_AVAILABLE

/* include inline versions */
#include "mali_math_inline.h"

#else


/* extern versions */
extern s32 _mali_iabs(s32 x);
extern s32 _mali_smlabb(s32 a16, s32 b16, s32 c32);

#endif


extern void mali_math_init(void);

typedef union _mali_math_float_int_union
{
	float x;
	s32   i;
} _mali_math_float_int_union;


/**
 * check if a number is a power of two
 * @param n the number to test
 * @return MALI_TRUE if the number is a power of two, MALI_FALSE if not
 */
MALI_STATIC_INLINE mali_bool _mali_is_pow2(s32 n)
{
	if (0 == n)
	{
		return MALI_TRUE;
	}

	return (n & (n - 1)) == 0;
}

/**
 * ceil x to the next power of two number
 * @param x the number to ceil
 * @return the closest power of two number bigger than x
 */
MALI_STATIC_INLINE u32 _mali_ceil_pow2(u32 x)
{
	x -= 1; /* move threshold */
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
}

MALI_STATIC_INLINE u32 _mali_floor_pow2(u32 x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x >>= 1;
	return x + 1;
}

/**
 * get the base 2 log of a power of two integer
 * @param n the number to take the logarithm of
 * @return log2(n), or -1 if n was < 0 or not a power of two
 */
MALI_STATIC_INLINE s32 _mali_log_base2(s32 n)
{
	s32 log2 = 0;

	/* 0 or negative numbers have no logarithm */
	/*if (n < 1) return -1;*/
	MALI_DEBUG_ASSERT(n >= 1, ("0 or negative numbers have no logrithm"));
	/*
	 *  If we test for powers-of-2 first, then we can just narrow in on
	 *  a single set bit using a series of masks. Non-power-of-two values
	 *  have no integer logarithm.
	 *
	 *  This test relies on 2's complement arithmetic - (n&-n) returns
	 *  the value of the lowest set bit. If this is the same as the value
	 *  itself, then it must be the ONLY set bit.
	 */

	/*if (_mali_is_pow2(n) == MALI_FALSE) return -1;*/
	MALI_DEBUG_ASSERT(_mali_is_pow2(n) == MALI_TRUE, ("Non-power-of-two values have no integer logarithm"));

	if (n & 0x7FFF0000)
	{
		log2 |= 16;
	}

	if (n & 0x7F00FF00)
	{
		log2 |= 8;
	}

	if (n & 0x70F0F0F0)
	{
		log2 |= 4;
	}

	if (n & 0x3CCCCCCC)
	{
		log2 |= 2;
	}

	if (n & 0x2AAAAAAA)
	{
		log2 |= 1;
	}

	MALI_DEBUG_ASSERT((1 << log2) == n, ("log2(%d) is not %d", n, log2));
	return log2;
}

/**
 * MALI_MATH_EXPONENT_BITS is a bitmask for the exponent field in an IEEE-754 float.
 * Both Inf and NaN values are encoded using the maximum (all 1s) value for the
 * exponent, while finite values use smaller exponent values.
 *
 * MALI_MATH_MANTISSA_BITS is a bitmask for the mantissa field in an IEEE-754 float.
 * If the above condition is met, a non-zero mantissa means the float is NaN.
 */
#define MALI_MATH_EXPONENT_BITS (0x7f800000)
#define MALI_MATH_MANTISSA_BITS (0x007fffff)

MALI_STATIC_INLINE s32 _mali_math_isfinite(float x)
{
	u32 i;

	_mali_sys_memcpy_32(&i, &x, 4);

	if ((i & MALI_MATH_EXPONENT_BITS) == MALI_MATH_EXPONENT_BITS)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

MALI_STATIC_INLINE s32 _mali_math_isnan(float x)
{
	u32 i;

	_mali_sys_memcpy_32(&i, &x, 4);

	if ((i & MALI_MATH_EXPONENT_BITS) == MALI_MATH_EXPONENT_BITS && (i & MALI_MATH_MANTISSA_BITS) != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#undef MALI_MATH_EXPONENT_BITS
#undef MALI_MATH_MANTISSA_BITS

#endif /* !defined(_MALI_MATH_H_) */
