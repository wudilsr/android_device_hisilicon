/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2005, 2007-2010, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_FLOAT_VECTOR3_H_
#define _MALI_FLOAT_VECTOR3_H_

#include "mali_float.h"

typedef struct
{
	mali_float x, y, z;
} mali_float_vector3;


MALI_STATIC_INLINE mali_float_vector3 __mali_float_vector3_add(mali_float_vector3 v0, mali_float_vector3 v1)
{
	mali_float_vector3 temp;
	temp.x = v0.x + v1.x;
	temp.y = v0.y + v1.y;
	temp.z = v0.z + v1.z;
	return temp;
}

MALI_STATIC_INLINE mali_float_vector3 __mali_float_vector3_sub(mali_float_vector3 v0, mali_float_vector3 v1)
{
	mali_float_vector3 temp;
	temp.x = v0.x - v1.x;
	temp.y = v0.y - v1.y;
	temp.z = v0.z - v1.z;
	return temp;
}

MALI_STATIC_INLINE mali_float_vector3 __mali_float_vector3_scale(mali_float_vector3 v, mali_float scalar)
{
	mali_float_vector3 temp;
	temp.x = v.x * scalar;
	temp.y = v.y * scalar;
	temp.z = v.z * scalar;
	return temp;
}

MALI_STATIC_INLINE mali_float __mali_float_vector3_dot2(mali_float_vector3 v0, mali_float_vector3 v1)
{
	return v0.x * v1.x + v0.y * v1.y;
}

MALI_STATIC_INLINE mali_float __mali_float_vector3_dot3(mali_float_vector3 v0, mali_float_vector3 v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

MALI_STATIC_INLINE mali_float __mali_float_vector3_magnitude(mali_float_vector3 v)
{
	return _mali_sys_sqrt(__mali_float_vector3_dot3(v, v));
}

MALI_STATIC_INLINE mali_float_vector3 __mali_float_vector3_normalize(mali_float_vector3 v)
{
	return __mali_float_vector3_scale(v, 1.f / __mali_float_vector3_magnitude(v));
}

#endif /* _MALI_FLOAT_VECTOR3_H_ */
