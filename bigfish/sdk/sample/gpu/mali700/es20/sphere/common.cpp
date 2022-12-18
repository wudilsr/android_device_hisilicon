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

#ifdef _WIN32
 #define WIN32_LEAN_AND_MEAN 1
#endif

#include "common.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef LINUX
 #include <sys/time.h>
#else
 #include <windows.h>
#endif

#include "hi_3d_config.h"

/***************************************************************************************
***************************************************************************************/

// Computes file length.
static int flength(FILE * Fptr)
{
    int length;

    fseek(Fptr, 0, SEEK_END);
    length = ftell(Fptr);
    fseek(Fptr, 0, SEEK_SET);
    return length;
}

// Compile a vertex or pixel shader.
// returns 0: fail
//         1: success
int CompileShader(const char * FName, GLuint ShaderNum)
{
    FILE * fptr = NULL;

#ifdef UNDER_CE
    static wchar_t buffer[MAX_PATH + 1];
    int i = GetModuleFileName(NULL, buffer, MAX_PATH);
    while (buffer[i - 1] != L'\\')
    {
        i--;
    }

    while (*FName != '\0')
    {
        buffer[i++] = (wchar_t)(*FName++);
    }

    buffer[i] = L'\0';
    fptr = _wfopen(buffer, L"rb");
#else
    fptr = fopen(FName, "rb");
#endif
    if (fptr == NULL)
    {
        HI3D_TRACE("Can not open file: %s\n", FName);
        return 0;
    }

    int length = flength(fptr);

    char * shaderSource = (char*)malloc(sizeof (char) * length);
    if (shaderSource == NULL)
    {
        HI3D_TRACE("Out of memory.\n");
        return 0;
    }

    fread(shaderSource, length, 1, fptr);

    glShaderSource(ShaderNum, 1, (const char**)&shaderSource, &length);
    glCompileShader(ShaderNum);

    free(shaderSource);
    fclose(fptr);

    GLint compiled = 0;
    glGetShaderiv(ShaderNum, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        // Retrieve error buffer size.
        GLint errorBufSize, errorLength;
        glGetShaderiv(ShaderNum, GL_INFO_LOG_LENGTH, &errorBufSize);

        char * infoLog = (char*)malloc(errorBufSize * sizeof(char) + 1);
        if (!infoLog)
        {
            // Retrieve error.
            glGetShaderInfoLog(ShaderNum, errorBufSize, &errorLength, infoLog);
            infoLog[errorBufSize + 1] = '\0';
            HI3D_TRACE("%s\n", infoLog);

            free(infoLog);
        }

        return 0;
    }

    return 1;
}

/***************************************************************************************
***************************************************************************************/

static void ConvertARGBtoABGR(unsigned int * data, int size)
{
    for (int i = 0; i < size * size; i++, data++)
    {
        register unsigned int temp = *data;

        // Swap R and B.
        *data = (temp & 0xFF00FF00) | ((temp & 0xFF) << 16) | ((temp & 0xFF0000) >> 16);
    }
}

// loads a 256x256 ARGB (32bit) format cube map texture dds file.
CubeTexture* LoadCubeDDS(const char * filename)
{
    FILE * fptr = NULL;

#ifdef UNDER_CE
    static wchar_t buffer[MAX_PATH + 1];
    int i = GetModuleFileName(NULL, buffer, MAX_PATH);
    while (buffer[i - 1] != L'\\')
    {
        i--;
    }

    while (*filename != '\0')
    {
        buffer[i++] = (wchar_t)(*filename++);
    }

    buffer[i] = L'\0';
    fptr = _wfopen(buffer, L"rb");
#else
    fptr = fopen(filename, "rb");
#endif
    if (fptr == NULL)
    {
        HI3D_TRACE("Can not open file: %s\n", filename);
        return NULL;
    }

    // read dds file routine.
    CubeTexture * cbTexture = NULL;
    do
    {
        unsigned long dummy, size, offset, width;

        // read first 4 bytes, magic number.
        if (!fread(&dummy, sizeof (unsigned long), 1, fptr))
        {
            break;
        }

        // check magic number, should be "DDS ": 0x20534444.
        if (dummy != 0x20534444UL)
        {
            HI3D_TRACE("File format incorrect.\n");
            break;
        }

        // second 4 bytes: texture offset in file.
        if (!fread(&dummy, sizeof (unsigned long), 1, fptr))
        {
            break;
        }

        offset = dummy + 4;

        // no care.
        if (!fread(&dummy, sizeof (unsigned long), 1, fptr))
        {
            break;
        }

        // no care.
        if (!fread(&dummy, sizeof (unsigned long), 1, fptr))
        {
            break;
        }

        // texture width
        if (!fread(&width, sizeof (unsigned long), 1, fptr))
        {
            break;
        }

        size = width * width;

        if (fseek(fptr, offset, SEEK_SET))
        {
            break;
        }

        if ((cbTexture = (CubeTexture*)malloc(sizeof (CubeTexture))) == NULL)
        {
            break;
        }

        // read faces
        // positive x
        if ((cbTexture->posx = (unsigned int*)malloc(sizeof (unsigned int) * size)) == NULL)
        {
            break;
        }

        if (fread(cbTexture->posx, sizeof (unsigned int), size, fptr) != size)
        {
            break;
        }

        ConvertARGBtoABGR(cbTexture->posx, width);

        // negative x
        if (fseek(fptr, 87380, SEEK_CUR))
        {
            // FIXME, assuming size is 256 and mipmaps included
            break;
        }

        if ((cbTexture->negx = (unsigned int*)malloc(sizeof (unsigned int) * size)) == NULL)
        {
            break;
        }

        if (fread(cbTexture->negx, sizeof (unsigned int), size, fptr) != size)
        {
            break;
        }

        ConvertARGBtoABGR(cbTexture->negx, width);

        // positive y
        if (fseek(fptr, 87380, SEEK_CUR))
        {
            // FIXME, assuming size is 256 and mipmaps included
            break;
        }

        if ((cbTexture->posy = (unsigned int*)malloc(sizeof (unsigned int) * size)) == NULL)
        {
            break;
        }

        if (fread(cbTexture->posy, sizeof (unsigned int), size, fptr) != size)
        {
            break;
        }

        ConvertARGBtoABGR(cbTexture->posy, width);

        // negative y
        if (fseek(fptr, 87380, SEEK_CUR))
        {
            // FIXME, assuming size is 256 and mipmaps included
            break;
        }

        if ((cbTexture->negy = (unsigned int*)malloc(sizeof (unsigned int) * size)) == NULL)
        {
            break;
        }

        if (fread(cbTexture->negy, sizeof (unsigned int), size, fptr) != size)
        {
            break;
        }

        ConvertARGBtoABGR(cbTexture->negy, width);

        // positive z
        if (fseek(fptr, 87380, SEEK_CUR))
        {
            // FIXME, assuming size is 256 and mipmaps included
            break;
        }

        if ((cbTexture->posz = (unsigned int*)malloc(sizeof (unsigned int) * size)) == NULL)
        {
            break;
        }

        if (fread(cbTexture->posz, sizeof (unsigned int), size, fptr) != size)
        {
            break;
        }

        ConvertARGBtoABGR(cbTexture->posz, width);

        // negative z
        if (fseek(fptr, 87380, SEEK_CUR))
        {
            // FIXME, assuming size is 256 and mipmaps included
            break;
        }

        if ((cbTexture->negz = (unsigned int*)malloc(sizeof (unsigned int) * size)) == NULL)
        {
            break;
        }

        if (fread(cbTexture->negz, sizeof (unsigned int), size, fptr) != size)
        {
            break;
        }

        ConvertARGBtoABGR(cbTexture->negz, width);

        cbTexture->img_size = width;

        fclose(fptr);
        return cbTexture;
    } while (false);

    // error handle
    HI3D_TRACE("Error while read DDS file.\n");

    fclose(fptr);
    DeleteCubeTexture(cbTexture);

    return NULL;
}

/***************************************************************************************
***************************************************************************************/

void DeleteCubeTexture(CubeTexture * cube)
{
    if (cube != NULL)
    {
        void * pointers[] = {
            (void*)cube->posx,
            (void*)cube->posy,
            (void*)cube->posz,
            (void*)cube->negx,
            (void*)cube->negy,
            (void*)cube->negz,
            (void*)cube
        };

        for (unsigned int i = 0; i < (sizeof (pointers) / sizeof (pointers[0])); i++)
        {
            if (pointers[i] != NULL)
            {
                free(pointers[i]);
            }
        }
    }
}

unsigned long GetTimeMillis()
{
#ifdef LINUX
    static struct timeval start = {0, 0};
    struct timeval now;
    if ((start.tv_sec == 0) && (start.tv_usec == 0))
    {
        gettimeofday(&start, NULL);
    }

    gettimeofday(&now, NULL);

    return (unsigned long)(((unsigned long)(now.tv_sec - start.tv_sec)) * 1000
                           + (now.tv_usec - start.tv_usec) / 1000);
#else
    static long start = 0;
    if (start == 0)
    {
        start = GetTickCount();
    }

    return (unsigned long)(GetTickCount() - start);
#endif
}
