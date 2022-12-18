/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2005-2010, 2012-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
#ifndef _MALI_FLOAT_MATRIX4X4_H_
#define _MALI_FLOAT_MATRIX4X4_H_

#include "mali_system.h"
#include "mali_float_vector3.h"
#include "mali_float_vector4.h"

typedef mali_float mali_float_matrix4x4[4][4];

/* build matrices */

void __mali_float_matrix4x4_make_identity(mali_float_matrix4x4 dst);

void __mali_float_matrix4x4_make_frustum(mali_float_matrix4x4 dst, float left, float right, float bottom, float top, float near, float far);
void __mali_float_matrix4x4_make_ortho(mali_float_matrix4x4 dst, float left, float right, float bottom, float top, float near, float far);

/* modify matrices */

void __mali_float_matrix4x4_copy(mali_float_matrix4x4 dst, mali_float_matrix4x4 src);
void __mali_float_matrix4x4_multiply(mali_float_matrix4x4 dst, mali_float_matrix4x4 src1, const mali_float_matrix4x4 src2);
mali_err_code __mali_float_matrix4x4_invert(mali_float_matrix4x4 dst, mali_float_matrix4x4 src) MALI_CHECK_RESULT;
void __mali_float_matrix4x4_transpose(mali_float_matrix4x4 dst, mali_float_matrix4x4 src);


MALI_STATIC_INLINE mali_float_vector3 __mali_float_matrix4x4_rotate_vector3(mali_float_matrix4x4 m, mali_float_vector3 v)
{
	mali_float_vector3 dst;
	MALI_DEBUG_ASSERT_POINTER(m);
	dst.x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z;
	dst.y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z;
	dst.z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z;
	return dst;
}

MALI_STATIC_INLINE mali_float_vector4 __mali_float_matrix4x4_transform_vector4(mali_float_matrix4x4 m, mali_float_vector4 v)
{
	mali_float_vector4 dst;
	MALI_DEBUG_ASSERT_POINTER(m);
	dst.x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w;
	dst.y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w;
	dst.z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w;
	dst.w = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w;
	return dst;
}

static MALI_INLINE void __mali_float_matrix4x4_rotate_array3(mali_float dst[3], mali_float_matrix4x4 m, mali_float v[4])
{
	MALI_DEBUG_ASSERT_POINTER(m);
	dst[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2];
	dst[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2];
	dst[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2];
}

static MALI_INLINE void __mali_float_matrix4x4_transform_array4(mali_float dst[4], mali_float_matrix4x4 m, mali_float v[4])
{
	MALI_DEBUG_ASSERT_POINTER(m);
	dst[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3];
	dst[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3];
	dst[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3];
	dst[3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3];
}

#endif /* _MALI_FLOAT_MATRIX4X4_H_ */
