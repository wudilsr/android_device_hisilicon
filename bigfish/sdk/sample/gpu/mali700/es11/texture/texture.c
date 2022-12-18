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
*    Auto-generated file on 8/17/2010. Do not edit!!!
*  
*****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "texture.h"
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#define DEBUG_POS printf("debug::func=%s, line=%d\n",__func__, __LINE__);


bool pause   = false;
int sampling =  0;
int x        = 0;
int y        = 0;
int width    =  1280;
int height   =  720;
int count    =  1000;

EGLDisplay g_EglDisplay;
EGLContext g_EglContext;
EGLSurface g_EglSurface;
NativeDisplayType g_NativeDisplay;
NativeWindowType g_NativeWindow;

static GLuint mTextures[4];



// Program entry point.
int main(int argc, char * argv[])
{ 
	// EGL configuration - we use 24-bpp render target and a 16-bit Z buffer.
	EGLint configAttribs[] =
	{
		EGL_SAMPLES,	  0,
		EGL_RED_SIZE,	  8,
		EGL_GREEN_SIZE,	  8,
		EGL_BLUE_SIZE,	  8,
		EGL_ALPHA_SIZE,	  EGL_DONT_CARE,
		EGL_DEPTH_SIZE,	  16,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_NONE,
	};
DEBUG_POS;
	configAttribs[1] = sampling;
	struct timeval render_start;
	struct timeval render_end;
	unsigned long render_delay;
	hi_egl_setup(x, y, width, height, 1, 0);
DEBUG_POS;
	// Initialize the GLES.
	if (InitGLES())
	{	
		int frames = 0;
        	bool done;
DEBUG_POS;
		// Main loop.
		gettimeofday(&render_start, NULL);
		for (done = false; !done;)
		{

				Render();
                		eglSwapBuffers (g_EglDisplay,g_EglSurface );
				frames ++;

				if (count > 0)
				{
					// Check if this is the last frame.
					if (--count == 0)
					{
						gettimeofday(&render_end, NULL);
						render_delay = 1000000 * (render_end.tv_sec-render_start.tv_sec)+ render_end.tv_usec-render_start.tv_usec;
						printf("load 1000 frames cost %ld us\n", render_delay);
						done = true;
						
					}
				}
		}
	}

	// Cleanup the GLES.
	CleanGLES();


	// Clean up the VDK, EGL, and GLES.
    	hi_egl_destroy();


	return 0;
}

/*******************************************************************************
*******************************************************************************/

bool InitGLES()
{
	// Set clear colors.
	glClearColorx(ZERO, ZERO, ZERO, ZERO);

	// Show smoothed colors.
	glShadeModel(GL_SMOOTH);  

	// Set the projection matrix.  We will use an ortho cube centered at the
	// origin with 100 units of edge.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthox(FixedFromInt(-50), FixedFromInt(50),
			 FixedFromInt(-50), FixedFromInt(50),
			 FixedFromInt(-50), FixedFromInt(50));

	// Select modelview matrix.
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	Prepare();

	// Success.
	return true;
}


/*******************************************************************************
Prepare Textures
*******************************************************************************/
void Prepare()
{
	GLint crop[4] = { 0, height, width, -height };
	glGenTextures(4, mTextures);

	uint32_t t32[4][16]= {
		{
			0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
			0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
			0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
			0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
		},
		{
			0xCCFF0000, 0xCCFF0000, 0xCCFF0000, 0xCCFF0000,
			0xCCFF0000, 0xCCFF0000, 0xCCFF0000, 0xCCFF0000,
			0xCCFFFFFF, 0xCCFFFFFF, 0xCCFFFFFF, 0xCCFFFFFF,			
			0xCCFFFFFF, 0xCCFFFFFF, 0xCCFFFFFF, 0xCCFFFFFF
		},
		{
			0x8800FF00, 0x8800FF00, 0x8800FF00, 0x8800FF00,
			0x88FFFFFF, 0x88FFFFFF, 0x88FFFFFF, 0x88FFFFFF,
			0x8800FF00, 0x8800FF00, 0x8800FF00, 0x8800FF00,
			0x88FFFFFF, 0x88FFFFFF, 0x88FFFFFF, 0x88FFFFFF
		},
		{
			0x440000FF, 0x44FFFFFF, 0x440000FF, 0x44FFFFFF,
			0x440000FF, 0x44FFFFFF, 0x440000FF, 0x44FFFFFF,
			0x440000FF, 0x44FFFFFF, 0x440000FF, 0x44FFFFFF,
			0x440000FF, 0x44FFFFFF, 0x440000FF, 0x44FFFFFF
		},			
	};
	
	int i, j;

	struct timeval tv_start;
	struct timeval tv_end;
	unsigned long delay;
	unsigned char *pmem = (unsigned char *)malloc(width * height * 4);
	
	for(j = 0; j  < 4; j++)
	{
		glBindTexture(GL_TEXTURE_2D, mTextures[j]);
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, crop);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexEnvx(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glEnable(GL_TEXTURE_2D);		
		//glColor4f(1,1,1,1);

		for(i = 0; i < width * height * 4/64; i++)
		{
			memcpy(pmem + 64*i, t32[j], 64);
		}
/*
		for(i = 0; i < width * height * 4/4; i++)
		{
			memcpy(pmem + 4*i, &tt32[j], 4);
		}
*/
		gettimeofday(&tv_start, NULL);		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pmem);
		gettimeofday(&tv_end, NULL);
		delay = 1000000 * (tv_end.tv_sec-tv_start.tv_sec)+ tv_end.tv_usec-tv_start.tv_usec;
		printf("load texture cost %ld us\n", delay);	

	}
	free(pmem);


}



void Render()
{	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glBindTexture(GL_TEXTURE_2D, mTextures[0]);
	glDrawTexiOES(0, 0, 0, width, height);

	glBindTexture(GL_TEXTURE_2D, mTextures[1]);	
	glDrawTexiOES(0, 0, 0, width, height);

	glBindTexture(GL_TEXTURE_2D, mTextures[2]);
	glDrawTexiOES(0, 0, 0, width, height);

	glBindTexture(GL_TEXTURE_2D, mTextures[3]);
	glDrawTexiOES(0, 0, 0, width, height);   

}

/*******************************************************************************
*******************************************************************************/

void CleanGLES()
{
	glFinish();
}

/*******************************************************************************
*******************************************************************************/
