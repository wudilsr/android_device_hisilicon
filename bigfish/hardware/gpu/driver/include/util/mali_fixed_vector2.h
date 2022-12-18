/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2010, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_FIXED_VECTOR2_H_
#define _MALI_FIXED_VECTOR2_H_

#include <mali_system.h>
#include "mali_fixed.h"

typedef struct
{
	mali_fixed x, y;
} mali_fixed_vector2;

MALI_STATIC_INLINE mali_fixed_vector2 __mali_fixed_vector2_add(mali_fixed_vector2 v0, mali_fixed_vector2 v1)
{
	mali_fixed_vector2 temp;
	temp.x = v0.x + v1.x;
	temp.y = v0.y + v1.y;
	return temp;
}

MALI_STATIC_INLINE mali_fixed_vector2 __mali_fixed_vector2_sub(mali_fixed_vector2 v0, mali_fixed_vector2 v1)
{
	mali_fixed_vector2 temp;
	temp.x = v0.x - v1.x;
	temp.y = v0.y - v1.y;
	return temp;
}

MALI_STATIC_INLINE mali_fixed_vector2 __mali_fixed_vector2_scale(mali_fixed_vector2 v, mali_fixed scalar)
{
	mali_fixed_vector2 temp;
	temp.x = (MALI_STATIC_CAST(s64)v.x * scalar) >> 16;
	temp.y = (MALI_STATIC_CAST(s64)v.y * scalar) >> 16;
	return temp;
}

MALI_STATIC_INLINE mali_fixed __mali_fixed_vector2_dot2(mali_fixed_vector2 v0, mali_fixed_vector2 v1)
{
	return ((MALI_STATIC_CAST(s64)v0.x * v1.x) + (MALI_STATIC_CAST(s64)v0.y * v1.y)) >> 16;
}

MALI_STATIC_INLINE mali_fixed __mali_fixed_vector2_magnitude(mali_fixed_vector2 v)
{
	return _mali_fixed_rcp(_mali_fixed_rsq(__mali_fixed_vector2_dot2(v, v)));
}

MALI_STATIC_INLINE mali_fixed_vector2 __mali_fixed_vector2_normalize(mali_fixed_vector2 v)
{
	return __mali_fixed_vector2_scale(v, _mali_fixed_rsq(__mali_fixed_vector2_dot2(v, v)));
}

#endif /* _MALI_FIXED_VECTOR2_H_ */
