/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2010, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_FIXED_VECTOR3_H_
#define _MALI_FIXED_VECTOR3_H_

#include <mali_system.h>
#include "mali_fixed.h"

typedef struct
{
	mali_fixed x, y, z;
} mali_fixed_vector3;

MALI_STATIC_INLINE mali_fixed_vector3 __mali_fixed_vector3_add(mali_fixed_vector3 v0, mali_fixed_vector3 v1)
{
	mali_fixed_vector3 temp;
	temp.x = v0.x + v1.x;
	temp.y = v0.y + v1.y;
	temp.z = v0.z + v1.z;
	return temp;
}

MALI_STATIC_INLINE mali_fixed_vector3 __mali_fixed_vector3_sub(mali_fixed_vector3 v0, mali_fixed_vector3 v1)
{
	mali_fixed_vector3 temp;
	temp.x = v0.x - v1.x;
	temp.y = v0.y - v1.y;
	temp.z = v0.z - v1.z;
	return temp;
}

MALI_STATIC_INLINE mali_fixed_vector3 __mali_fixed_vector3_scale(mali_fixed_vector3 v, mali_fixed scalar)
{
	mali_fixed_vector3 temp;
	temp.x = (MALI_STATIC_CAST(s64)v.x * scalar) >> 16;
	temp.y = (MALI_STATIC_CAST(s64)v.y * scalar) >> 16;
	temp.z = (MALI_STATIC_CAST(s64)v.z * scalar) >> 16;
	return temp;
}

MALI_STATIC_INLINE mali_fixed __mali_fixed_vector3_dot2(mali_fixed_vector3 v0, mali_fixed_vector3 v1)
{
	return ((MALI_STATIC_CAST(s64)v0.x * v1.x) + (MALI_STATIC_CAST(s64)v0.y * v1.y)) >> 16;
}

MALI_STATIC_INLINE mali_fixed __mali_fixed_vector3_dot3(mali_fixed_vector3 v0, mali_fixed_vector3 v1)
{
	return ((MALI_STATIC_CAST(s64)v0.x * v1.x) + (MALI_STATIC_CAST(s64)v0.y * v1.y) + (MALI_STATIC_CAST(s64)v0.z * v1.z)) >> 16;
}

MALI_STATIC_INLINE mali_fixed __mali_fixed_vector3_magnitude(mali_fixed_vector3 v)
{
	return __mali_fixed_rcp(_mali_fixed_rsq(__mali_fixed_vector3_dot3(v, v)));
}

MALI_STATIC_INLINE mali_fixed_vector3 __mali_fixed_vector3_normalize(mali_fixed_vector3 v)
{
	return __mali_fixed_vector3_scale(v, _mali_fixed_rsq(__mali_fixed_vector3_dot3(v, v)));
}

#endif /* _MALI_FIXED_VECTOR3_H_ */
