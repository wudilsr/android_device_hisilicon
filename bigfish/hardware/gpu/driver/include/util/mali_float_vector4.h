/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2005, 2007-2011, 2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_FLOAT_VECTOR4_H_
#define _MALI_FLOAT_VECTOR4_H_

#include "mali_float.h"

typedef struct
{
	mali_float x, y, z, w;
} mali_float_vector4;


MALI_STATIC_INLINE mali_float_vector4 __mali_float_vector4_add(mali_float_vector4 v0, mali_float_vector4 v1)
{
	mali_float_vector4 temp;
	temp.x = v0.x + v1.x;
	temp.y = v0.y + v1.y;
	temp.z = v0.z + v1.z;
	temp.w = v0.w + v1.w;
	return temp;
}

MALI_STATIC_INLINE mali_float_vector4 __mali_float_vector4_sub(mali_float_vector4 v0, mali_float_vector4 v1)
{
	mali_float_vector4 temp;
	temp.x = v0.x - v1.x;
	temp.y = v0.y - v1.y;
	temp.z = v0.z - v1.z;
	temp.w = v0.w - v1.w;
	return temp;
}

MALI_STATIC_INLINE mali_float_vector4 __mali_float_vector4_scale(mali_float_vector4 v, mali_float scalar)
{
	mali_float_vector4 temp;
	temp.x = v.x * scalar;
	temp.y = v.y * scalar;
	temp.z = v.z * scalar;
	temp.w = v.w * scalar;
	return temp;
}

MALI_STATIC_INLINE mali_float __mali_float_vector4_dot2(mali_float_vector4 v0, mali_float_vector4 v1)
{
	return v0.x * v1.x + v0.y * v1.y;
}

MALI_STATIC_INLINE mali_float __mali_float_vector4_dot3(mali_float_vector4 v0, mali_float_vector4 v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
}

MALI_STATIC_INLINE mali_float __mali_float_vector4_dot4(mali_float_vector4 v0, mali_float_vector4 v1)
{
	return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w;
}

#endif /* _MALI_FLOAT_VECTOR4_H_ */
