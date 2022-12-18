/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2011, 2013-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_FIXED_VECTOR4_H_
#define _MALI_FIXED_VECTOR4_H_

#include <mali_system.h>
#include "mali_fixed.h"

typedef struct
{
	mali_fixed x, y, z, w;
} mali_fixed_vector4;

MALI_STATIC_INLINE mali_fixed_vector4 __mali_fixed_vector4_add(mali_fixed_vector4 v0, mali_fixed_vector4 v1)
{
	mali_fixed_vector4 temp;
	temp.x = v0.x + v1.x;
	temp.y = v0.y + v1.y;
	temp.z = v0.z + v1.z;
	temp.w = v0.w + v1.w;
	return temp;
}

MALI_STATIC_INLINE mali_fixed_vector4 __mali_fixed_vector4_sub(mali_fixed_vector4 v0, mali_fixed_vector4 v1)
{
	mali_fixed_vector4 temp;
	temp.x = v0.x - v1.x;
	temp.y = v0.y - v1.y;
	temp.z = v0.z - v1.z;
	temp.w = v0.w - v1.w;
	return temp;
}

MALI_STATIC_INLINE mali_fixed_vector4 __mali_fixed_vector4_scale(mali_fixed_vector4 v, mali_fixed scalar)
{
	mali_fixed_vector4 temp;
	temp.x = ((s64)v.x * scalar) >> 16;
	temp.y = ((s64)v.y * scalar) >> 16;
	temp.z = ((s64)v.z * scalar) >> 16;
	temp.w = ((s64)v.w * scalar) >> 16;
	return temp;
}

MALI_STATIC_INLINE mali_fixed __mali_fixed_vector4_dot2(mali_fixed_vector4 v0, mali_fixed_vector4 v1)
{
	return (
	           (MALI_STATIC_CAST(s64)v0.x * v1.x)
	           + (MALI_STATIC_CAST(s64)v0.y * v1.y)
	       ) >> 16;
}

MALI_STATIC_INLINE mali_fixed __mali_fixed_vector4_dot3(mali_fixed_vector4 v0, mali_fixed_vector4 v1)
{
	return (
	           (MALI_STATIC_CAST(s64)v0.x * v1.x)
	           + (MALI_STATIC_CAST(s64)v0.y * v1.y)
	           + (MALI_STATIC_CAST(s64)v0.z * v1.z)
	       ) >> 16;
}

MALI_STATIC_INLINE mali_fixed __mali_fixed_vector4_dot4(mali_fixed_vector4 v0, mali_fixed_vector4 v1)
{
	return (
	           (MALI_STATIC_CAST(s64)v0.x * v1.x)
	           + (MALI_STATIC_CAST(s64)v0.y * v1.y)
	           + (MALI_STATIC_CAST(s64)v0.z * v1.z)
	           + (MALI_STATIC_CAST(s64)v0.w * v1.w)
	       ) >> 16;
}

#endif /* _MALI_FIXED_VECTOR4_H_ */
