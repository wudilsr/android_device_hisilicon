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
#include "tutorial.h"
#include <hi_egl.h>
#include <EGL/egl.h>


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

	configAttribs[1] = sampling;
	hi_egl_setup(x, y, width, height, 1, 0);

	// Initialize the GLES.
	if (InitGLES())
	{
		int frames = 0;
        	bool done;

		// Main loop.
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

	// Success.
	return true;
}

/*******************************************************************************
*******************************************************************************/

void Render()
{
	static int rotation = 0;

	// Clear the screen.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	// Translate and rotate the triangle.
	glLoadIdentity();  
	glTranslatex(ZERO, ZERO, FixedFromInt(-10));
	glRotatex(FixedFromInt(rotation++), ZERO, ONE, ZERO);

	// Enable the vertex array.
	glEnableClientState(GL_VERTEX_ARRAY);
	static GLshort vertexArray[] = { -25, -25, 0,
									  25, -25, 0,
									   0,  25, 0 };
	glVertexPointer(3, GL_SHORT, 0, vertexArray);

	// Enable the color array.
	glEnableClientState(GL_COLOR_ARRAY);
	static GLubyte colorArray[] = { 255,   0,   0, 0,
									  0, 255,   0, 0,
									  0,   0, 255, 0 };
	glColorPointer(4,GL_UNSIGNED_BYTE, 0, colorArray);

	// Draw 1 triangle (it consists of 3 vertices).
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Disable the client states (we are good citizens).
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}

/*******************************************************************************
*******************************************************************************/

void CleanGLES()
{
	glFinish();
}

/*******************************************************************************
*******************************************************************************/
