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

#ifndef _COMMONMATH_H_
#define _COMMONMATH_H_

#include <GLES2/gl2.h>

#ifndef M_PI
 #define M_PI 3.14159265f
#endif

#define D3DX_PI 3.14159265f

typedef float FLOAT;

typedef unsigned long ULONG;

struct D3DXVECTOR3
{
    float x, y, z;
};

struct D3DXVECTOR4
{
    float x, y, z, w;
};

typedef struct _D3DMATRIX
{
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
} D3DXMATRIX;

struct State
{
    D3DXVECTOR3 m_Eye,
                m_Lookat,
                m_UpVec,
                m_EyeVector;

    float m_Time,
          m_TimeStep,
          m_StepsPerCircle;

    D3DXMATRIX m_ViewMatrix,
               m_ProjMatrix,
               m_ScaleMatrix,
               m_RotateMatrix,
               m_MoveMatrix,
               m_WorldMatrix;

    int FRAME_BUFFER_WIDTH,
        FRAME_BUFFER_HEIGHT;
};

// Setup matrices.
void SetupMatrices(State* renderState);

// Setup transformation maxtrix.
void SetupTransform(State*      renderState,
                    D3DXMATRIX* matrix);

void GetFrustum(GLfloat *matrix,
                GLfloat  left,
                GLfloat  right,
                GLfloat  bottom,
                GLfloat  top,
                GLfloat  zNear,
                GLfloat  zFar);

void MatMult(GLfloat* Result,
             GLfloat* Mat1,
             GLfloat  Mat2[16]);

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
            int*       numVertices);

// Set eye position.
void SetEye(State* state,
            float  X,
            float  Y,
            float  Z);

// Set object scale in each direction.
void SetScale(State* state,
              float  X,
              float  Y,
              float  Z);

// Set object rotation in each direction.
void SetRotation(State* state,
                 float  X,
                 float  Y,
                 float  Z);

// Set object 3D position in each direction.
void SetMove(State* state,
             float  X,
             float  Y,
             float  Z);

// Set time step.
void SetTimeStep(State* state,
                 ULONG  TimeStep);

void InitializeRenderState(State* state,
                           int    width,
                           int    height);

#endif
