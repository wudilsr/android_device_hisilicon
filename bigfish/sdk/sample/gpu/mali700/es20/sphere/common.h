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

#ifndef _COMMON_H_
#define _COMMON_H_

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <stdio.h>
#include <stdlib.h>

// Compile a vertex or pixel shader.
int CompileShader(const char * FName, GLuint ShaderNum);

struct CubeTexture
{
    unsigned int * posx;
    unsigned int * negx;
    unsigned int * posy;
    unsigned int * negy;
    unsigned int * posz;
    unsigned int * negz;
    int            img_size;
};

// loads a 256x256 ARGB (32bit) format cube map texture dds file.
CubeTexture*  LoadCubeDDS(const char * filename);

void          DeleteCubeTexture(CubeTexture * cube);

unsigned long GetTimeMillis();

#endif
