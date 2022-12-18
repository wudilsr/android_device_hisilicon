/****************************************************************************
 *
 *    Copyright (c) 2005 - 2010 by Vivante Corp.  All rights reserved.
 *
 *    The material in this file is confidential and contains trade secrets
 *    of Vivante Corporation. This is proprietary information owned by
 *    Vivante Corporation. No part of this work may be disclosed,
 *    reproduced, copied, transmitted, or used in any way for any purpose,
 *    without the express written permission of Vivante Corporation.
 *
 *****************************************************************************
 *
 *    Auto-generated file on 4/13/2010. Do not edit!!!
 *
 *****************************************************************************/

#include "commonMath.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static D3DXMATRIX* _D3DXMatrixRotationX(D3DXMATRIX* pOut,
                                        float       angle)
{
    float _sin = (float)sin(angle);
    float _cos = (float)cos(angle);

    pOut->_11 = 1.0f;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;
    pOut->_21 = 0.0f;
    pOut->_22 = _cos;
    pOut->_23 = _sin;
    pOut->_24 = 0.0f;
    pOut->_31 = 0.0f;
    pOut->_32 = -_sin;
    pOut->_33 = _cos;
    pOut->_34 = 0.0f;
    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = 0.0f;
    pOut->_44 = 1.0f;

    return pOut;
}

static D3DXMATRIX* _D3DXMatrixRotationY(D3DXMATRIX* pOut,
                                        float       angle)
{
    float _sin = (float)sin(angle);
    float _cos = (float)cos(angle);

    pOut->_11 = _cos;
    pOut->_12 = 0.0f;
    pOut->_13 = -_sin;
    pOut->_14 = 0.0f;
    pOut->_21 = 0.0f;
    pOut->_22 = 1.0f;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;
    pOut->_31 = _sin;
    pOut->_32 = 0.0f;
    pOut->_33 = _cos;
    pOut->_34 = 0.0f;
    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = 0.0f;
    pOut->_44 = 1.0f;

    return pOut;
}

static D3DXMATRIX* _D3DXMatrixRotationZ(D3DXMATRIX* pOut,
                                        float       angle)
{
    float _sin = (float)sin(angle);
    float _cos = (float)cos(angle);

    pOut->_11 = _cos;
    pOut->_12 = _sin;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;
    pOut->_21 = -_sin;
    pOut->_22 = _cos;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;
    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = 1.0f;
    pOut->_34 = 0.0f;
    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = 0.0f;
    pOut->_44 = 1.0f;

    return pOut;
}

#if 0
static void _D3DXMatrixRotationZ(GLfloat* mat,
                                 float    angle)
{
    // Set up rotation matrix rotating by angle around Z axis.
    FLOAT _sin = (float)sin(angle);
    FLOAT _cos = (float)cos(angle);

    mat[0]  = _cos;
    mat[1]  = _sin;
    mat[2]  = 0.0f;
    mat[3]  = 0.0f;
    mat[4]  = -_sin;
    mat[5]  = _cos;
    mat[6]  = 0.0f;
    mat[7]  = 0.0f;
    mat[8]  = 0.0f;
    mat[9]  = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;
    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

#endif

static D3DXVECTOR4* _D3DXVec3Transform(D3DXVECTOR4* pOut,
                                       D3DXVECTOR3* pV,
                                       D3DXMATRIX*  pM)
{
    pOut->x = pV->x * pM->_11 + pV->y * pM->_21 + pV->z * pM->_31 + pM->_41;
    pOut->y = pV->x * pM->_12 + pV->y * pM->_22 + pV->z * pM->_32 + pM->_42;
    pOut->z = pV->x * pM->_13 + pV->y * pM->_23 + pV->z * pM->_33 + pM->_43;
    pOut->w = pV->x * pM->_14 + pV->y * pM->_24 + pV->z * pM->_34 + pM->_44;

    return pOut;
}

static D3DXVECTOR3* _D3DXVec3Cross(D3DXVECTOR3* pOut,
                                   D3DXVECTOR3* pV1,
                                   D3DXVECTOR3* pV2)
{
    D3DXVECTOR3 v;

    v.x = pV1->y * pV2->z - pV1->z * pV2->y;
    v.y = pV1->z * pV2->x - pV1->x * pV2->z;
    v.z = pV1->x * pV2->y - pV1->y * pV2->x;

    *pOut = v;
    return pOut;
}

static D3DXVECTOR3* _D3DXVec3Subtract(D3DXVECTOR3* pOut,
                                      D3DXVECTOR3* pV1,
                                      D3DXVECTOR3* pV2)
{
    pOut->x = pV1->x - pV2->x;
    pOut->y = pV1->y - pV2->y;
    pOut->z = pV1->z - pV2->z;

    return pOut;
}

static float _D3DXVec3Dot(D3DXVECTOR3* pV1,
                          D3DXVECTOR3* pV2)
{
    return (pV1->x * pV2->x + pV1->y * pV2->y + pV1->z * pV2->z);
}

static D3DXVECTOR3* _D3DXVec3Normalize(D3DXVECTOR3* pOut,
                                       D3DXVECTOR3* pV)
{
    float x2  = pV->x * pV->x;
    float y2  = pV->y * pV->y;
    float z2  = pV->z * pV->z;
    float len = sqrtf(x2 + y2 + z2);

    pOut->x = pV->x / len;
    pOut->y = pV->y / len;
    pOut->z = pV->z / len;

    return pOut;
}

static D3DXMATRIX* _D3DXMatrixLookAtLH(D3DXMATRIX*  pOut,
                                       D3DXVECTOR3* pEye,
                                       D3DXVECTOR3* pAt,
                                       D3DXVECTOR3* pUp)
{
    D3DXVECTOR3 xaxis, yaxis, zaxis, tmp;

    _D3DXVec3Subtract(&tmp, pAt, pEye);
    _D3DXVec3Normalize(&zaxis, &tmp);       // 	zaxis = normal(At - Eye)

    _D3DXVec3Cross(&tmp, pUp, &zaxis);
    _D3DXVec3Normalize(&xaxis, &tmp);       //   xaxis = normal(cross(Up, zaxis))

    _D3DXVec3Cross(&yaxis, &zaxis, &xaxis);  //   yaxis = cross(zaxis, xaxis)

    pOut->_11 = xaxis.x;
    pOut->_12 = yaxis.x;
    pOut->_13 = zaxis.x;
    pOut->_14 = 0.0f;
    pOut->_21 = xaxis.y;
    pOut->_22 = yaxis.y;
    pOut->_23 = zaxis.y;
    pOut->_24 = 0.0f;
    pOut->_31 = xaxis.z;
    pOut->_32 = yaxis.z;
    pOut->_33 = zaxis.z;
    pOut->_34 = 0.0f;

    pOut->_41 = _D3DXVec3Dot(&xaxis, pEye) * -1.0f;
    pOut->_42 = _D3DXVec3Dot(&yaxis, pEye) * -1.0f;
    pOut->_43 = _D3DXVec3Dot(&zaxis, pEye) * -1.0f;
    pOut->_44 = 1.0f;           //	-dot(xaxis, eye)  -dot(yaxis, eye)  -dot(zaxis, eye)  1

    return pOut;
}

static D3DXMATRIX* _D3DXMatrixPerspectiveFovLH(D3DXMATRIX *pOut,
                                               FLOAT       fovy,
                                               FLOAT       Aspect,
                                               FLOAT       zn,
                                               FLOAT       zf)
{
    FLOAT yScale = 1.0f / (float)tan(fovy / 2);
    FLOAT xScale = yScale / Aspect;

    pOut->_11 = xScale;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;
    pOut->_21 = 0.0f;
    pOut->_22 = yScale;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;
    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = zf / (zf - zn);
    pOut->_34 = 1.0f;
    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = -zn * zf / (zf - zn);
    pOut->_44 = 0.0f;

    return pOut;
}

static D3DXMATRIX* _D3DXMatrixMultiply(D3DXMATRIX* pOut,
                                       D3DXMATRIX* pM1,
                                       D3DXMATRIX* pM2)
{
    D3DXMATRIX tmpOut;

    tmpOut._11 = pM1->_11 * pM2->_11 + pM1->_12 * pM2->_21 + pM1->_13 * pM2->_31 + pM1->_14 * pM2->_41;
    tmpOut._12 = pM1->_11 * pM2->_12 + pM1->_12 * pM2->_22 + pM1->_13 * pM2->_32 + pM1->_14 * pM2->_42;
    tmpOut._13 = pM1->_11 * pM2->_13 + pM1->_12 * pM2->_23 + pM1->_13 * pM2->_33 + pM1->_14 * pM2->_43;
    tmpOut._14 = pM1->_11 * pM2->_14 + pM1->_12 * pM2->_24 + pM1->_13 * pM2->_34 + pM1->_14 * pM2->_44;

    tmpOut._21 = pM1->_21 * pM2->_11 + pM1->_22 * pM2->_21 + pM1->_23 * pM2->_31 + pM1->_24 * pM2->_41;
    tmpOut._22 = pM1->_21 * pM2->_12 + pM1->_22 * pM2->_22 + pM1->_23 * pM2->_32 + pM1->_24 * pM2->_42;
    tmpOut._23 = pM1->_21 * pM2->_13 + pM1->_22 * pM2->_23 + pM1->_23 * pM2->_33 + pM1->_24 * pM2->_43;
    tmpOut._24 = pM1->_21 * pM2->_14 + pM1->_22 * pM2->_24 + pM1->_23 * pM2->_34 + pM1->_24 * pM2->_44;

    tmpOut._31 = pM1->_31 * pM2->_11 + pM1->_32 * pM2->_21 + pM1->_33 * pM2->_31 + pM1->_34 * pM2->_41;
    tmpOut._32 = pM1->_31 * pM2->_12 + pM1->_32 * pM2->_22 + pM1->_33 * pM2->_32 + pM1->_34 * pM2->_42;
    tmpOut._33 = pM1->_31 * pM2->_13 + pM1->_32 * pM2->_23 + pM1->_33 * pM2->_33 + pM1->_34 * pM2->_43;
    tmpOut._34 = pM1->_31 * pM2->_14 + pM1->_32 * pM2->_24 + pM1->_33 * pM2->_34 + pM1->_34 * pM2->_44;

    tmpOut._41 = pM1->_41 * pM2->_11 + pM1->_42 * pM2->_21 + pM1->_43 * pM2->_31 + pM1->_44 * pM2->_41;
    tmpOut._42 = pM1->_41 * pM2->_12 + pM1->_42 * pM2->_22 + pM1->_43 * pM2->_32 + pM1->_44 * pM2->_42;
    tmpOut._43 = pM1->_41 * pM2->_13 + pM1->_42 * pM2->_23 + pM1->_43 * pM2->_33 + pM1->_44 * pM2->_43;
    tmpOut._44 = pM1->_41 * pM2->_14 + pM1->_42 * pM2->_24 + pM1->_43 * pM2->_34 + pM1->_44 * pM2->_44;

    *pOut = tmpOut;
    return pOut;
}

// Setup matrices.
void SetupMatrices(State* renderState)
{
    // Compute the angle and advance the time counter.
    float fAngle = renderState->m_Time * (2.0f * M_PI) / renderState->m_StepsPerCircle;

    renderState->m_Time += renderState->m_TimeStep;

    D3DXMATRIX eyeMatrix;
    _D3DXMatrixRotationY(&eyeMatrix, fAngle);

    // Set eye position.
    D3DXVECTOR4 eyeTransform;
    _D3DXVec3Transform(&eyeTransform, &renderState->m_Eye, &eyeMatrix);
    renderState->m_EyeVector.x = eyeTransform.x;
    renderState->m_EyeVector.y = eyeTransform.y;
    renderState->m_EyeVector.z = eyeTransform.z;

    _D3DXMatrixLookAtLH(&renderState->m_ViewMatrix,
                        &renderState->m_EyeVector,
                        &renderState->m_Lookat,
                        &renderState->m_UpVec);

    float fAspect = float (renderState->FRAME_BUFFER_WIDTH) / float (renderState->FRAME_BUFFER_HEIGHT);

    _D3DXMatrixPerspectiveFovLH(&renderState->m_ProjMatrix,
                                D3DX_PI / 4.0f,
                                fAspect,
                                1.0f,
                                100.0f);
}

// Setup transformation maxtrix.
void SetupTransform(State*      renderState,
                    D3DXMATRIX* matrix)
{
    SetupMatrices(renderState);

    // Compute transformation matrix.
    // Matrix = scale * rotation * translation.
    D3DXMATRIX transform;
    _D3DXMatrixMultiply(&transform,
                        _D3DXMatrixMultiply(&transform,
                                            &renderState->m_ScaleMatrix,
                                            &renderState->m_RotateMatrix),
                        &renderState->m_MoveMatrix);

    // Transform view matrix with object transform matrices.
    D3DXMATRIX view;
    _D3DXMatrixMultiply(&view, &transform, &renderState->m_ViewMatrix);

    // Transform view matrix with the world matrix.
    D3DXMATRIX worldView;
    _D3DXMatrixMultiply(&worldView, &renderState->m_WorldMatrix, &view);

    // Transform view matrix with the projection matrix.
    _D3DXMatrixMultiply(matrix, &worldView, &renderState->m_ProjMatrix);
}

void GetFrustum(GLfloat *matrix,
                GLfloat  left,
                GLfloat  right,
                GLfloat  bottom,
                GLfloat  top,
                GLfloat  zNear,
                GLfloat  zFar)
{
    if ((left == right)
       || (bottom == top)
       || (zNear == zFar)
       || (zNear <= 0.0f)
       || (zFar <= 0.0f))
    {
        // Invalid value.
        return;
    }

    // Fill in frustum matrix.
    matrix[0]  = (2.0f * zNear) / (right - left);
    matrix[2]  = (right + left) / (right - left);
    matrix[5]  = (2.0f * zNear) / (top - bottom);
    matrix[6]  = (top + bottom) / (top - bottom);
    matrix[10] = -(zFar + zNear) / (zFar - zNear);
    matrix[11] = -(2.0f * zFar * zNear) / (zFar - zNear);
    matrix[14] = -1;
    matrix[1]  = 0;
    matrix[3]  = 0;
    matrix[4]  = 0;
    matrix[7]  = 0;
    matrix[8]  = 0;
    matrix[9]  = 0;
    matrix[12] = 0;
    matrix[13] = 0;
}

void MatMult(GLfloat* Result,
             GLfloat* Mat1,
             GLfloat  Mat2[16])
{
    int r, c;

    for (r = 0; r < 4; r++)
    {
        for (c = 0; c < 4; c++)
        {
            Result[r * 4 + c] = Mat1[r * 4 + 0] * Mat2[0 + c]
                                + Mat1[r * 4 + 1] * Mat2[4 + c]
                                + Mat1[r * 4 + 2] * Mat2[8 + c]
                                + Mat1[r * 4 + 3] * Mat2[12 + c];
        }
    }
}

void Sphere(GLfloat**  VertexArray,
            int        Width,
            int        Height,
            int        Colors,
            GLfloat**  ColorArray,
            int        Textures,
            GLfloat**  TextureArray,
            GLushort** IndexArray,
            int *      numPrimitives,
            int*       numIndices,
            int*       numVertices)
{
    int x, y, vcnt = 0, icnt = 0, ccnt = 0, tcnt = 0;
    GLushort offset;

    GLfloat* vertexArray = (GLfloat*)malloc(3 * Width * Height * sizeof(GLfloat));
    GLfloat* colorArray   = NULL;
    GLfloat* textureArray = NULL;
    GLushort* indexArray  = NULL;

    for (y = 0; y < Height; ++y)
    {
        float normY = (float) y / (float) (Height - 1);
        float polar = M_PI * normY;
        float polarSin = (float)sin(polar);
        float polarCos = (float)cos(polar);

        for (x = 0; x < Width; ++x)
        {
            float normX = (float) x / (float) (Width - 1);
            float azim = 2.0f * M_PI * normX;
            float azimSin = (float)sin(azim);
            float azimCos = (float)cos(azim);
            vertexArray[vcnt++] = polarSin * azimCos;
            vertexArray[vcnt++] = polarSin * azimSin;
            vertexArray[vcnt++] = polarCos;

            if (Colors)
            {
                colorArray = (GLfloat*)malloc(4 * Width * Height * sizeof(GLfloat));
                colorArray[ccnt++] = 1.0f;
                colorArray[ccnt++] = 0.0f;
                colorArray[ccnt++] = 0.0f;
                colorArray[ccnt++] = 1.0f;
            }

            if (Textures > 1)
            {
                textureArray = (GLfloat*)malloc(4 * Width * Height * sizeof(GLfloat));
            }
            else if (Textures)
            {
                textureArray = (GLfloat*)malloc(2 * Width * Height * sizeof(GLfloat));
            }

            if (Textures)
            {
                float u = 1.0f - normX;
                float v = normY;
                textureArray[tcnt++] = u;
                textureArray[tcnt++] = v;
            }

            if (Textures > 1)
            {
                float u = 4.0f * (1.0f - normX);
                float v = 2.0f * normY;
                textureArray[tcnt++] = u;
                textureArray[tcnt++] = v;
            }
        }
    }

    offset = 0;
    *numPrimitives = (Width - 1) * (Height - 1) * 2;
    indexArray = (GLushort*) malloc((*numPrimitives) * 3 * sizeof(GLushort));

    for (y = 0; y < Height - 1; ++y)
    {
        for (x = 1; x < Width; ++x)
        {
            indexArray[icnt++] = GLushort(offset + x - 1);
            indexArray[icnt++] = GLushort(offset + x - 1 + Width);
            indexArray[icnt++] = GLushort(offset + x);
            indexArray[icnt++] = GLushort(offset + x - 1 + Width);
            indexArray[icnt++] = GLushort(offset + x + Width);
            indexArray[icnt++] = GLushort(offset + x);
        }

        offset += Width;
    }

    *VertexArray = vertexArray;
    if (Colors)
    {
        *ColorArray = colorArray;
    }

    if (Textures)
    {
        *TextureArray = textureArray;
    }

    *IndexArray  = indexArray;
    *numIndices  = icnt;
    *numVertices = vcnt;
}

static D3DXMATRIX* _D3DXMatrixTranslation(D3DXMATRIX* pOut,
                                          float       x,
                                          float       y,
                                          float       z)
{
    pOut->_11 = 1.0f;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;
    pOut->_21 = 0.0f;
    pOut->_22 = 1.0f;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;
    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = 1.0f;
    pOut->_34 = 0.0f;
    pOut->_41 = x;
    pOut->_42 = y;
    pOut->_43 = z;
    pOut->_44 = 1.0f;

    return pOut;
}

static D3DXMATRIX* _D3DXMatrixScaling(D3DXMATRIX* pOut,
                                      float       x,
                                      float       y,
                                      float       z)
{
    pOut->_11 = x;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;
    pOut->_21 = 0.0f;
    pOut->_22 = y;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;
    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = z;
    pOut->_34 = 0.0f;
    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = 0.0f;
    pOut->_44 = 1.0f;

    return pOut;
}

static D3DXMATRIX* _D3DXMatrixIdentity(D3DXMATRIX* pOut)
{
    pOut->_11 = 1.0f;
    pOut->_12 = 0.0f;
    pOut->_13 = 0.0f;
    pOut->_14 = 0.0f;
    pOut->_21 = 0.0f;
    pOut->_22 = 1.0f;
    pOut->_23 = 0.0f;
    pOut->_24 = 0.0f;
    pOut->_31 = 0.0f;
    pOut->_32 = 0.0f;
    pOut->_33 = 1.0f;
    pOut->_34 = 0.0f;
    pOut->_41 = 0.0f;
    pOut->_42 = 0.0f;
    pOut->_43 = 0.0f;
    pOut->_44 = 1.0f;

    return pOut;
}

static D3DXMATRIX*  _D3DXMatrixRotationYawPitchRoll(D3DXMATRIX* pOut,
                                                    float       Yaw,
                                                    float       Pitch,
                                                    float       Roll)
{
    D3DXMATRIX yaw, pitch, roll;

    _D3DXMatrixRotationY(&yaw, Yaw);
    _D3DXMatrixRotationX(&pitch, Pitch);
    _D3DXMatrixRotationZ(&roll, Roll);

    return _D3DXMatrixMultiply(pOut, _D3DXMatrixMultiply(pOut, &yaw, &pitch), &roll);
}

// Set eye position.
void SetEye(State* state,
            float  X,
            float  Y,
            float  Z)
{
    state->m_Eye.x = X;
    state->m_Eye.y = Y;
    state->m_Eye.z = Z;
}

// Set object scale in each direction.
void SetScale(State* state,
              float  X,
              float  Y,
              float  Z)
{
    _D3DXMatrixScaling(&state->m_ScaleMatrix, X, Y, Z);
}

// Set object rotation in each direction.
void SetRotation(State* state,
                 float  X,
                 float  Y,
                 float  Z)
{
    _D3DXMatrixRotationYawPitchRoll(&state->m_RotateMatrix, Y, X, Z);
}

// Set object 3D position in each direction.
void SetMove(State* state,
             float  X,
             float  Y,
             float  Z)
{
    _D3DXMatrixTranslation(&state->m_MoveMatrix, X, Y, Z);
}

// Set time step.
void SetTimeStep(State* state,
                 ULONG  TimeStep)
{
    state->m_TimeStep = (float)TimeStep;
}

void InitializeRenderState(State* state,
                           int    width,
                           int    height)
{
    _D3DXMatrixIdentity(&state->m_ProjMatrix);
    _D3DXMatrixIdentity(&state->m_WorldMatrix);
    _D3DXMatrixIdentity(&state->m_ViewMatrix);

    SetScale(state, 1, 1, 1);
    SetRotation(state, 0, 0, 0);
    SetMove(state, 0, 0, 0);

    state->m_Eye.x = 0;
    state->m_Eye.y = 0;
    state->m_Eye.z = -1;

    state->m_EyeVector.x = 0;
    state->m_EyeVector.y = 0;
    state->m_EyeVector.z = -1;

    state->m_Lookat.x = 0;
    state->m_Lookat.y = 0;
    state->m_Lookat.z = 0;

    state->m_UpVec.x = 0;
    state->m_UpVec.y = 1;
    state->m_UpVec.z = 0;

    state->m_Time = 0;
    state->m_TimeStep = 4;
    state->m_StepsPerCircle    = 360;
    state->FRAME_BUFFER_WIDTH  = width;
    state->FRAME_BUFFER_HEIGHT = height;
}
