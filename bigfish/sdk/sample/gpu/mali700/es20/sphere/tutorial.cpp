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

/*
 * OpenGL ES 2.0 Tutorial 4
 *
 * Draws a glass sphere inside a big sphere (enviroment mapping).
 * The glass sphere shows both reflection and refraction effects.
 */

#include <GLES2/gl2.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "common.h"
#include "commonMath.h"
#include "hi_egl.h"
#include "hi_texture.h"
#define TUTORIAL_NAME "OpenGL ES 2.0 Tutorial 4"

int width    = 1280;
int height   = 720;
int frames   = 2000;
int sampling = 0;

// Global Variables
GLuint programHandleGlass;
GLuint programHandleBgrnd;

// Generic used buffer
GLuint bufs[5];

// hold sphere data
int numVertices, numFaces, numIndices;
GLfloat* sphereVertices = NULL;
GLushort* indices = NULL;

// attribute and uniform handle.
GLint locVertices[2], locColors[2],
      locTransformMat[2], locRadius[2],
      locEyePos[2], locTexCoords[2], locSamplerCb[2];

// render state
State renderState;

D3DXMATRIX transformMatrix;

/***************************************************************************************
***************************************************************************************/

void RenderInit()
{
    Sphere(&sphereVertices, 40, 60, 0, NULL, 0, NULL, &indices, &numFaces, &numIndices, &numVertices);

    // Grab location of shader attributes.
    locVertices[0] = glGetAttribLocation(programHandleGlass, "my_Vertex");
    locVertices[1] = glGetAttribLocation(programHandleBgrnd, "my_Vertex");

    locRadius[0] = glGetUniformLocation(programHandleGlass, "my_Radius");
    locRadius[1] = glGetUniformLocation(programHandleBgrnd, "my_Radius");

    locEyePos[0] = glGetUniformLocation(programHandleGlass, "my_EyePos");
    locEyePos[1] = glGetUniformLocation(programHandleBgrnd, "my_EyePos");

    // Transform Matrix is uniform for all vertices here.
    locTransformMat[0] = glGetUniformLocation(programHandleGlass, "my_TransformMatrix");
    locTransformMat[1] = glGetUniformLocation(programHandleBgrnd, "my_TransformMatrix");

    glEnableVertexAttribArray(locVertices[0]);
    glEnableVertexAttribArray(locVertices[1]);

    glGenBuffers(2, bufs);
    if (glGetError() != GL_NO_ERROR)
    {
        // can not handle this error
        HI3D_TRACE("GL Error.\n");
        return;
    }

    // Vertices
    glBindBuffer(GL_ARRAY_BUFFER, bufs[0]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), sphereVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(locVertices[0], 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(locVertices[1], 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLushort), indices, GL_STATIC_DRAW);

    if (glGetError() != GL_NO_ERROR)
    {
        // can not handle this error
        HI3D_TRACE("GL Error.\n");
        return;
    }

    // Textures
    // Set s0 for samplerCube location.
    locSamplerCb[0] = glGetUniformLocation(programHandleGlass, "samplerCb");
    locSamplerCb[1] = glGetUniformLocation(programHandleBgrnd, "samplerCb");

    GLuint textureHandle;
    glGenTextures(1, &textureHandle);

#ifdef ADVCA_SUPPORT
    CubeTexture* cubeTexData = LoadCubeDDS("/home/stb/bin/3d/exe/es20/sphere_res/stpeters_cross_mipmap_256.dds");
#else
    CubeTexture* cubeTexData = LoadCubeDDS("./sphere_res/stpeters_cross_mipmap_256.dds");
#endif

    if ((glGetError() != GL_NO_ERROR) || (cubeTexData == NULL))
    {
        // can not handle this error
        HI3D_TRACE("GL Error.\n");
        return;
    }

    int texSize = cubeTexData->img_size;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureHandle);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->posx);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->negx);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->posy);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->negy);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->posz);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, texSize, texSize, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                 cubeTexData->negz);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    if (glGetError() != GL_NO_ERROR)
    {
        // can not handle this error
        HI3D_TRACE("GL Error.\n");
        return;
    }

    // Deletes the texture data, it's now in OpenGL memory.
    DeleteCubeTexture(cubeTexData);

    InitializeRenderState(&renderState, width, height);

    // Set eye position.
    SetEye(&renderState, 0, 0, -3.8f);

    // Enable needed states.
    glEnable(GL_CULL_FACE);
}

// Actual rendering here.
void Render()
{
    //static float angle = 0;
    // Clear background.
    //glClear(GL_DEPTH_BUFFER_BIT);

    SetupTransform(&renderState, &transformMatrix);

    // Render background sphere.
    glCullFace(GL_BACK);
    glUseProgram(programHandleBgrnd);
    glUniform1i(locSamplerCb[1], 0);
    glUniform1f(locRadius[1], 10.0f);
    glUniform3fv(locEyePos[1], 1, (GLfloat*)&renderState.m_EyeVector);
    glUniformMatrix4fv(locTransformMat[1], 1, GL_FALSE, (GLfloat*)&transformMatrix);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

    // Render glass ball.
    glCullFace(GL_FRONT);
    glUseProgram(programHandleGlass);
    glUniform1i(locSamplerCb[0], 0);
    glUniform1f(locRadius[0], 1.0f);
    glUniform3fv(locEyePos[0], 1, (GLfloat*)&renderState.m_EyeVector);
    glUniformMatrix4fv(locTransformMat[0], 1, GL_FALSE, (GLfloat*)&transformMatrix);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

    // swap display with drawn surface.
    hi_egl_swap();
}

void RenderCleanup()
{
    // cleanup
    glDisableVertexAttribArray(locVertices[0]);
    glDisableVertexAttribArray(locVertices[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(2, bufs);

    if (sphereVertices != NULL)
    {
        free(sphereVertices);
    }

    if (indices != NULL)
    {
        free(indices);
    }
}

/***************************************************************************************
***************************************************************************************/
#if 0
void ParseCommandLine(int argc, char * argv[])
{
    if (argc <= 1)
    {
        HI3D_TRACE
        ("\n\n========================================================\n");
        HI3D_TRACE ("Usage:\n");
        HI3D_TRACE ("\t\t./tutorial w[value] h[value] f[value] s[value]\n\n");
        HI3D_TRACE ("w:\tthe display width, default value is %d\n", width);
        HI3D_TRACE ("h:\tthe display height, default value is %d\n", height);
        HI3D_TRACE ("f:\tthe number of frames, default value is %d\n", frames);
        HI3D_TRACE ("s:\tthe sampling, default value is %d\n\n", sampling);
        HI3D_TRACE ("For example:\n\t./tutorial w1280 h720 f2000 s4\n");
        HI3D_TRACE ("========================================================\n\n");
    }

    for (int i = 1; i < argc; i++)
    {
        switch (argv[i][0])
        {
        case 'w':
            width = atoi (&argv[i][1]);
            break;
        case 'h':
            height = atoi (&argv[i][1]);
            break;
        case 'f':

            // f<frames> for number of frames (defaults to 0, infinite).
            frames = atoi (&argv[i][1]);
            break;
        case 's':
            sampling = atoi (&argv[i][1]);
            break;
        }
    }
}

#endif

/***************************************************************************************
***************************************************************************************/
unsigned long long hi_egl_get_time_ns( void )
{
    struct timeval tv;
    unsigned long long time_ns;

    gettimeofday(&tv, NULL);

    time_ns  = ((unsigned long long) tv.tv_sec) * 1000000000;
    time_ns += ((unsigned long long) tv.tv_usec) * 1000;
    return time_ns;
}

// Program entry.
int main(int argc, char** argv)
{
    //ParseCommandLine(argc, argv);
    unsigned long long time_save, time_record;
    int framescnt = 0;

    hi_egl_setup(0, 0, width, height, sampling, 1);

    // load and compile vertex/fragment shaders.
    GLuint vertShaderNum, pixelShaderNum, pixelShaderNum2;

    vertShaderNum   = glCreateShader(GL_VERTEX_SHADER);
    pixelShaderNum  = glCreateShader(GL_FRAGMENT_SHADER);
    pixelShaderNum2 = glCreateShader(GL_FRAGMENT_SHADER);

    do
    {
#ifdef ADVCA_SUPPORT
        if (CompileShader("/home/stb/bin/3d/exe/es20/sphere_res/vs_es20t4.vert", vertShaderNum) == 0)
        {
            break;
        }

        if (CompileShader("/home/stb/bin/3d/exe/es20/sphere_res/ps_es20t4_glass.frag", pixelShaderNum) == 0)
        {
            break;
        }

        if (CompileShader("/home/stb/bin/3d/exe/es20/sphere_res/ps_es20t4_bgrnd.frag", pixelShaderNum2) == 0)
        {
            break;
        }

#else
        if (CompileShader("./sphere_res/vs_es20t4.vert", vertShaderNum) == 0)
        {
            break;
        }

        if (CompileShader("./sphere_res/ps_es20t4_glass.frag", pixelShaderNum) == 0)
        {
            break;
        }

        if (CompileShader("./sphere_res/ps_es20t4_bgrnd.frag", pixelShaderNum2) == 0)
        {
            break;
        }
#endif


        programHandleGlass = glCreateProgram();
        glAttachShader(programHandleGlass, vertShaderNum);
        glAttachShader(programHandleGlass, pixelShaderNum);
        glLinkProgram(programHandleGlass);

        programHandleBgrnd = glCreateProgram();
        glAttachShader(programHandleBgrnd, vertShaderNum);
        glAttachShader(programHandleBgrnd, pixelShaderNum2);
        glLinkProgram(programHandleBgrnd);

        if ((programHandleGlass == 0) || (programHandleBgrnd == 0))
        {
            break;
        }

        RenderInit();

        time_save = hi_egl_get_time_ns();
        do
        {
            Render();
            if (++framescnt == 100)
            {
                time_record = hi_egl_get_time_ns();
#ifdef FPS_RECORD
                fprintf(stderr, "fps is %f...\n", 1000.0 * 1000.0 * 1000.0 * 100 / (time_record - time_save));
#endif
                framescnt = 0;
                time_save = time_record;
            }
        } while (frames--);

        glFinish();

        RenderCleanup();

        // cleanup
        glDeleteShader(vertShaderNum);
        glDeleteShader(pixelShaderNum);
        glDeleteShader(pixelShaderNum2);
        glDeleteProgram(programHandleGlass);
        glDeleteProgram(programHandleBgrnd);
        glUseProgram(0);
    } while (false);

    hi_egl_destroy();

    return 0;
}
