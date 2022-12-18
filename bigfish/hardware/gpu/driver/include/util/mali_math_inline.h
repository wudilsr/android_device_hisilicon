/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2005, 2007-2010, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_MATH_INLINE_H_
#define _MALI_MATH_INLINE_H_

MALI_STATIC_INLINE s32 _mali_iabs(s32 x)
{
	if (x >= 0)
	{
		return x;
	}

	return -x;
}

#if defined(ARM) && !defined(THUMB)

#if defined(__ARMCC_VERSION)
#if __TARGET_ARCH_ARM > 5
/* ARMcc variant. Test this first, as armcc with the --gnu option enabled also defines __GNUC__ */
MALI_STATIC_INLINE u32 _mali_clz(u32 input)
{
	u32 zeros;
	__asm
	{
		clz zeros, input
	}
	return zeros;
}

MALI_STATIC_INLINE s32 _mali_smlabb(s32 a16, s32 b16, s32 c32)
{
	s32 res;
	__asm
	{
		smlabb res, a16, b16, c32
	}
	return res;
}

MALI_STATIC_INLINE s32 _mali_smulbb(s32 a16, s32 b16)
{
	s32 res;
	__asm
	{
		smulbb res, a16, b16
	}
	return res;
}
#else /* __TARGET_ARCH_ARM > 5 */
#define CLZ_FALLBACK_NEEDED
#define SMLA_FALLBACK_NEEDED
#endif /* __TARGET_ARCH_ARM > 5 */
#elif defined(__GNUC__)

/* GCC inline assembly versions */
MALI_STATIC_INLINE u32 _mali_clz(u32 input)
{
	u32 zeros;
	__asm__("clz %0, %0" : "=&r"(zeros) : "0"(input));
	return zeros;
}

MALI_STATIC_INLINE s32 _mali_smlabb(s32 a16, s32 b16, s32 c32)
{
	s32 res;
	__asm__("smlabb %0, %1, %2, %3" : "=&r"(res) : "r"(a16), "r"(b16), "r"(c32));
	return res;
}

MALI_STATIC_INLINE s32 _mali_smulbb(s32 a16, s32 b16)
{
	s32 res;
	__asm__("smulbb %0, %1, %2" : "=&r"(res) : "r"(a16), "r"(b16));
	return res;
}
#elif defined(_MSC_VER)
#include <cmnintrin.h>
#if _INTRINSIC_IS_SUPPORTED(_CountLeadingZeros)
MALI_STATIC_INLINE u32 _mali_clz(u32 input)
{
	return _CountLeadingZeros(input);
}
#else
#define CLZ_FALLBACK_NEEDED
#endif
#define SMLA_FALLBACK_NEEDED
#else
/*# warning "Unknown ARM compiler, not assembling CLZ or SMLA instructions"*/
/* Cannot use #warning in MSVC */
#define CLZ_FALLBACK_NEEDED
#define SMLA_FALLBACK_NEEDED

# endif /* ARM platform compilers */

#elif defined(ARM) && defined(THUMB)
/* # warning "ARM thumb code, not assembling CLZ or SMLA instructions" */
#define CLZ_FALLBACK_NEEDED
#define SMLA_FALLBACK_NEEDED

#else
/*# warning "Non-ARM platform, not assembling CLZ or SMLA instructions"*/
#define CLZ_FALLBACK_NEEDED
#define SMLA_FALLBACK_NEEDED

#endif


#if defined(CLZ_FALLBACK_NEEDED)
/* ANSI C versions */

extern const u8 _mali_clz_lut[256];

MALI_STATIC_INLINE u32 _mali_clz(u32 input)
{
	/* 2 iterations of binary search */
	u32 c = 0;

	if (input & 0xFFFF0000)
	{
		input >>= 16;
	}
	else
	{
		c = 16;
	}

	if (input & 0xFF00)
	{
		input >>= 8;
	}
	else
	{
		c += 8;
	}

	/* a 256 bytes lut for the last 8 bits */
	return _mali_clz_lut[input] + c;
}
#endif

#if defined(SMLA_FALLBACK_NEEDED)
/* ANSI C versions */

MALI_STATIC_INLINE s32 _mali_smlabb(s32 a16, s32 b16, s32 c32)
{
	s32 s = (a16 << 16) >> 16; /* 16bit sign-extend */
	s32 t = (b16 << 16) >> 16; /* 16bit sign-extend */
	return c32 + s * t;
}

MALI_STATIC_INLINE s32 _mali_smulbb(s32 a16, s32 b16)
{
	s32 s = (a16 << 16) >> 16; /* 16bit sign-extend */
	s32 t = (b16 << 16) >> 16; /* 16bit sign-extend */
	return s * t;
}

#endif

/** helper for doing a rshift on a u64, where the shift is no more than 32,
 * and the result expected to fit in a u32
 * @param val input u64
 * @param shift shift involved
 * @param shift_rsb32 32-shift, which may be available already
 * @result val >> shift
 */
MALI_STATIC_INLINE u32 _mali_u64rshift_max32(u64 val, u32 shift, u32 shift_rsb32)
{
	u32 result;

	MALI_DEBUG_ASSERT(32 - shift == shift_rsb32, ("Incorrect shift, shift_rsb32"));
	MALI_DEBUG_ASSERT(shift <= 32, ("Incorrect shift, must be no more than 32"));
	MALI_DEBUG_ASSERT((val >> (shift + 32)) == 0, ("shift would not yield a u32: val = %llx, shift=%d", val, shift));

	result = ((u32)(val & 0xFFFFFFFFu)) >> shift;
	result |= ((u32)(val >> 32)) << shift_rsb32;

	return result;
}

/**
 * @brief Count trailing zeros
 *
 * This obeys _mali_count_trailing_zeros((u32)x<<n) == n, for unsigned x even and n < 32
 *
 * @note Count trailing ones/find first zero bit can be implemented by working
 * on the inverted value.
 * @param value input value to count the number of least significant trailing zeros
 * @result the number of trailing zeros.
 */
MALI_STATIC_INLINE u32 _mali_count_trailing_zeros(u32 value)
{
	u32 negated;
	u32 isolated;
	u32 leading_zeros;

	/* Catch zero value */
	if (0 == value)
	{
		return 32;
	}

	/*
	 * Begin with zzz...z1000...0
	 * See ARM System Developers Guide for details of count_trailing_zeros
	 */

	/* Isolate the zero: it is preceeded by a run of 1s, so add 1 to it
	 *
	 * ~value = xxx...x0111...1
	 * ~value + 1 = xxx...x1000...0
	 */
	negated = (u32)0 - value ; /* -a == ~a + 1 (mod 2^n) for n-bit numbers */

	isolated = negated & value ; /* xxx...x1000...0 & zzz...z1000...0, zs are ~xs */
	/* We have isolated the first set bit.
	 * Note that isolated is 0 when value is 0 */

	leading_zeros = _mali_clz(isolated);

	/* isolated obeys Trailing zeros + leading zeros + 1 = 32, when isolated != 0 */

	return 31 - leading_zeros;
}

#endif /* _MALI_MATH_INLINE_H_ */
