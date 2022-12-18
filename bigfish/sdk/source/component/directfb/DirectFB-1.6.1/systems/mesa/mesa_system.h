/*
   (c) Copyright 2001-2009  The world wide DirectFB Open Source Community (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Hundt <andi@fischlustig.de>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrjälä <syrjala@sci.fi> and
              Claudio Ciccani <klan@users.sf.net>.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#ifndef __MESA_MESA_H__
#define __MESA_MESA_H__


#define EGL_EGLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES

#include <gbm.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#ifndef GLAPIENTRY
#define GLAPIENTRY
#endif
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <xf86drmMode.h>
#include <xf86drm.h>

#include <fusion/shmalloc.h>

#include <core/surface_pool.h>

#include <core/layers.h>
#include <core/screens.h>

#include "vt.h"

extern const SurfacePoolFuncs mesaSurfacePoolFuncs;

extern const ScreenFuncs       *mesaScreenFuncs;
extern const DisplayLayerFuncs *mesaLayerFuncs;


typedef struct {
     FusionSHMPoolShared *shmpool;

     CoreSurfacePool     *pool;
} MesaDataShared;

typedef struct {
     MesaDataShared      *shared;

     CoreDFB             *core;
     CoreScreen          *screen;
     CoreLayer           *layer;

     int                  fd;      /* DRM file descriptor */
     struct gbm_device   *gbm;
     EGLDisplay           dpy;
     EGLContext           ctx;


     drmModeConnector    *connector;
     drmModeEncoder      *encoder;
     drmModeModeInfo      mode;
     drmModeRes          *resources;
     drmModeCrtcPtr       saved_crtc;

     drmEventContext      drmeventcontext;

     VirtualTerminal     *vt;

     bool                 flip_pending;
     CoreSurfaceBuffer   *buffer;

     DirectThread        *thread;
     DirectMutex          lock;
     DirectWaitQueue      wq_event;
     DirectWaitQueue      wq_flip;
} MesaData;


#endif
