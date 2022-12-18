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


#ifndef __tutorial1_h_
#define __tutorial1_h_

#include <GLES/gl.h>
#include <EGL/egl.h>

#define FixedFromInt(n)	(GLfixed) ((n) << 16)
#define ZERO			FixedFromInt(0)
#define ONE				FixedFromInt(1)

#define bool int 
#define true 1
#define false 0

void ParseCommandLine(int argc, char * argv[]);
bool InitGLES();
void Render();
void CleanGLES();


#endif /* __tutorial1_h_ */
