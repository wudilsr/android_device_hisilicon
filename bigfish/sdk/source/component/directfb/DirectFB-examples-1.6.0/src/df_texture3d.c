/*
   (c) Copyright 2000-2002  convergence integrated media GmbH.
   (c) Copyright 2002-2004  convergence GmbH.

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Hundt <andi@fischlustig.de>,
              Sven Neumann <neo@directfb.org> and
              Ville Syrjälä <syrjala@sci.fi>.

   This file is subject to the terms and conditions of the MIT License:

   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation
   files (the "Software"), to deal in the Software without restriction,
   including without limitation the rights to use, copy, modify, merge,
   publish, distribute, sublicense, and/or sell copies of the Software,
   and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
   CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
   TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <direct/clock.h>
#include <direct/debug.h>
#include <direct/util.h>

#include <directfb.h>

#include "ve.h"

#include "util.h"

/* the super interface */
static IDirectFB              *dfb;

/* the primary surface (surface of primary layer) */
static IDirectFBSurface       *primary;

/* Input interfaces: device and its buffer */
static IDirectFBEventBuffer   *events;

/* Font used for FPS etc. */
static IDirectFBFont          *font;

/* The texture surface. */
static IDirectFBSurface       *texture;

static IDirectFBVideoProvider *provider = NULL;

static int screen_width, screen_height;


/* macro for a safe call to DirectFB functions */
#define DFBCHECK(x...) \
        {                                                                      \
           DFBResult err = x;                                                  \
           if (err != DFB_OK) {                                                \
              fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ );           \
              DirectFBErrorFatal( #x, err );                                   \
           }                                                                   \
        }

#define SET_VECTOR(vec, x, y, z, S, T)  \
                                        (vec).v[0] = x, \
                                        (vec).v[1] = y, \
                                        (vec).v[2] = z, \
                                        (vec).v[3] = 1, \
                                        (vec).s = S,    \
                                        (vec).t = T

/*
static inline void
generate_mesh( VeVertexBuffer *buffer, int n, float c, float r )
{
     int   i;
     int   m = n - 1;
     float M = m * m * m * m;
     float t = c * M_PI * 2.0f / m;

     D_ASSERT( buffer != NULL );
     D_ASSERT( n > 2 );

     vbClear( buffer );

     for (i=m; i>=0; i--) {
          float T   = i * t;

          float I   = i * i * i * i;
          float IoM = I / M;

          float R   = r - i * r / (float) m;

          vbAdd( buffer,
                 sin( T ) * R,
                 cos( T ) * R,
                 4.0f - IoM * 9.6f,
                 i / (float) m,
                 (i == m) ? 1.0f : 0.0f );
     }
}
*/

static inline void
generate_flag( VeVertexBuffer *buffer, int num, float cycles, float amplitude, float phase )
{
     int   i;
     int   n = num >> 1;
     float m = n - 1;
     float t = cycles * M_PI * 2.0f / m;
     float P = phase  * M_PI * 2.0f;

     D_ASSERT( buffer != NULL );
     D_ASSERT( num > 3 );

     vbClear( buffer );

     for (i=0; i<n; i++) {
          float T = i * t + P;
          float R = i * amplitude / m;

          float x = -5.0f + i * 10.0f / m;
          float y = sin( T ) * R  +  sin( 0.27f * T ) * R  +  sin( 0.37f * T ) * R;

          float s = i / m;

          vbAdd( buffer, x, y, -5.0f, s, 0.0f );
          vbAdd( buffer, x, y,  5.0f, s, 1.0f );
     }
}

static bool
handle_input()
{
     DFBInputEvent evt;

     while (events->GetEvent( events, DFB_EVENT(&evt) ) == DFB_OK) {
          switch (evt.type) {
               case DIET_KEYPRESS:
                    switch (evt.key_symbol) {
                         case DIKS_ESCAPE:
                              return true;

                         default:
                              break;
                    }
                    break;

               case DIET_AXISMOTION:
                    if (evt.flags & DIEF_AXISREL) {
                         switch (evt.axis) {
                              case DIAI_X:
                                   if (evt.buttons & DIBM_LEFT)
                                        veTranslate( evt.axisrel * 0.01, 0.0f, 0.0f );

                                   if (evt.buttons & DIBM_MIDDLE)
                                        veRotate( evt.axisrel * 0.01, 0.0f, 1.0f, 0.0f );

                                   if (evt.buttons & DIBM_RIGHT)
                                        veScale( 1.0f + evt.axisrel * 0.01, 1.0f, 1.0f );

                                   break;

                              case DIAI_Y:
                                   if (evt.buttons & DIBM_LEFT)
                                        veTranslate( 0.0f, 0.0f, evt.axisrel * 0.01 );

                                   if (evt.buttons & DIBM_MIDDLE)
                                        veRotate( -evt.axisrel * 0.01, 1.0f, 0.0f, 0.0f );

                                   if (evt.buttons & DIBM_RIGHT)
                                        veScale( 1.0f, 1.0f + evt.axisrel * 0.01, 1.0f );

                                   break;

                              default:
                                   break;
                         }
                    }
                    break;

               default:
                    break;
          }
     }

     return false;
}

int
main( int argc, char *argv[] )
{
     int                     num;
     long long               start;
     DFBFontDescription      fdsc;
     DFBSurfaceDescription   sdsc;
     FPSData                 fps;
     VeVertexBuffer         *buffer;
     IDirectFBScreen        *screen = NULL;
     DFBScreenEncoderConfig  encoder_config;

     /* Initialize DirectFB. */
     DFBCHECK(DirectFBInit( &argc, &argv ));

     /* Create the super interface. */
     DFBCHECK(DirectFBCreate( &dfb ));

     /* Setup screen. */
     DFBCHECK(dfb->GetScreen( dfb, DSCID_PRIMARY, &screen ));

     encoder_config.flags          = DSECONF_TV_STANDARD | DSECONF_SCANMODE   | DSECONF_FREQUENCY | 
                                     DSECONF_CONNECTORS  | DSECONF_RESOLUTION | DSECONF_FRAMING;
     encoder_config.tv_standard    = DSETV_DIGITAL;
     encoder_config.out_connectors = DSOC_COMPONENT | DSOC_HDMI;
     encoder_config.scanmode       = DSESM_PROGRESSIVE;
     encoder_config.frequency      = DSEF_24HZ;
     encoder_config.framing        = DSEPF_STEREO_FRAME_PACKING;
     encoder_config.resolution     = DSOR_1920_1080;

     DFBCHECK(screen->SetEncoderConfiguration( screen, 0, &encoder_config ));

     /* 
      * Create fullscreen primary surface
      */
     dfb->SetCooperativeLevel( dfb, DFSCL_FULLSCREEN );

     sdsc.flags = DSDESC_CAPS;
     sdsc.caps  = DSCAPS_PRIMARY | DSCAPS_FLIPPING | DSCAPS_STEREO;

     DFBCHECK(dfb->CreateSurface( dfb, &sdsc, &primary ));


     /* Query the size of the primary surface. */
     primary->GetSize( primary, &screen_width, &screen_height );

     /* Calculate number of vertices used. */
     num = MAX( screen_width, screen_height ) / 16 + 16;

     /* Allocate vertex buffer. */
     buffer = vbNew( VE_QUAD_STRIP, num );
     if (!buffer) {
          primary->Release( primary );
          dfb->Release( dfb );
          return -1;
     }

     /* Create an event buffer for all devices. */
     DFBCHECK(dfb->CreateInputEventBuffer( dfb, DICAPS_ALL, DFB_FALSE, &events ));

     /* Load the font. */
     fdsc.flags  = DFDESC_HEIGHT;
     fdsc.height = 20;

     DFBCHECK(dfb->CreateFont( dfb, FONT, &fdsc, &font ));

     /*
      * Load the texture.
      */
     if (argc > 1) {
          DFBWindowID id = atoi(argv[1]);

          if (id > 0) {
               IDirectFBDisplayLayer *layer;
               IDirectFBWindow       *window;
               DFBSurfacePixelFormat  format;

               DFBCHECK(dfb->GetDisplayLayer( dfb, DLID_PRIMARY, &layer ));

               DFBCHECK(layer->SetCooperativeLevel( layer, DLSCL_ADMINISTRATIVE ));

               DFBCHECK(layer->GetWindow( layer, id, &window ));

               layer->Release( layer );

               DFBCHECK(window->GetSurface( window, &texture ));

               window->Release( window );

               DFBCHECK(texture->GetPixelFormat( texture, &format ));

               if (DFB_PIXELFORMAT_HAS_ALPHA( format ))
                    primary->SetBlittingFlags( primary, DSBLIT_BLEND_ALPHACHANNEL );
          }
          else {
               DFBCHECK(dfb->CreateVideoProvider( dfb, argv[1], &provider ));

               DFBCHECK(provider->GetSurfaceDescription( provider, &sdsc ));

               primary->GetPixelFormat( primary, &sdsc.pixelformat );

               DFBCHECK(dfb->CreateSurface( dfb, &sdsc, &texture ));

               DFBCHECK(provider->PlayTo( provider, texture, NULL, NULL, NULL ));
          }
     }
     else {
          DFBCHECK(util_load_image( dfb, DATADIR"/texture.png", DSPF_UNKNOWN,
                                    &texture, NULL, NULL, NULL ));
     }

     /* Setup viewport transformation. */
     veViewport( 0, 0, screen_width, screen_height );

     /* Setup perspective transformation. */
     vePerspective( 80, screen_width / (float) screen_height, 1.0f, 20.0f );

     /* Move model into clipping volume. */
     veTranslate( 0, 0, -8 );

     /* Rotate a bit around the X axis. */
     veRotate( -0.4f, 1.0f, 0.0f, 0.0f );

     /* Set font and color for text. */
     primary->SetFont( primary, font );
     primary->SetColor( primary, 0xff, 0xff, 0xff, 0xff );

     /* Initialize time base. */
     start = direct_clock_get_millis();

     /* Initialize FPS stuff. */
     fps_init( &fps );

     veTranslate( 0.3, 0, 0 );

     /* Main loop. */
     while (true) {
          long long now = direct_clock_get_millis();
          float     T   = (now - start) / 1000.0f;

          /* Fill the vertex buffer. */
          //generate_mesh( buffer, num, sin( 1.7f * T ) + 2.5f, sin( 3.7f * T ) * 2.0f + 3.0f );
          generate_flag( buffer, num, 2.5f, 1.0f, -T );


          primary->SetStereoEye( primary, DSSE_LEFT );

          /* Clear the color buffer and depth buffer. */
          primary->Clear( primary, 0, 0, 0, 0 );

          /* Draw the FPS string. */
          primary->DrawString( primary, fps.fps_string, -1, 30, 30, DSTF_TOPLEFT );

          /* Render vertex buffer content. */
          vbExec( buffer, primary, texture );


          veTranslate( -0.6, 0, 0 );

          primary->SetStereoEye( primary, DSSE_RIGHT );

          /* Clear the color buffer and depth buffer. */
          primary->Clear( primary, 0, 0, 0, 0 );

          /* Draw the FPS string. */
          primary->DrawString( primary, fps.fps_string, -1, 30, 30, DSTF_TOPLEFT );

          /* Render vertex buffer content. */
          vbExec( buffer, primary, texture );

          veTranslate( 0.6, 0, 0 );


          /* Flip the surface. */
          DFBCHECK(primary->FlipStereo( primary, NULL, NULL, 0 ));

          /* Do FPS calculations. */
          fps_count( &fps, 1000 );

          /* Abort if result is true. */
          if (handle_input())
               break;
     }

     /* Free buffer memory. */
     vbDestroy( buffer );

     /* Release video provider. */
     if (provider)
          provider->Release( provider );

     /* Release other interfaces to shutdown DirectFB. */ 
     font->Release( font );
     texture->Release( texture );
     primary->Release( primary );
     screen->Release( screen );
     events->Release( events );
     dfb->Release( dfb );

     return 0;
}

