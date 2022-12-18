/*
   (c) Copyright 2000-2002  convergence integrated media GmbH.
   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Hundt <andi@fischlustig.de> and
              Sven Neumann <neo@directfb.org>.

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
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include <directfb.h>
#include <directfb_util.h>
#include <directfb_version.h>

#include <direct/util.h>

#define DIRECTFB_ROTATE
#if DIRECTFB_MAJOR_VERSION < 1
#undef DIRECTFB_ROTATE
#else
#if DIRECTFB_MAJOR_VERSION == 1
#if DIRECTFB_MINOR_VERSION < 3
#undef DIRECTFB_ROTATE
#endif
#endif
#endif


/* macro for a safe call to DirectFB functions */
#define DFBCHECK(x...) \
     {                                                                \
          err = x;                                                    \
          if (err != DFB_OK) {                                        \
               fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
               DirectFBErrorFatal( #x, err );                         \
          }                                                           \
     }

static int stacking_id = DWSC_MIDDLE;

static void read_command_line( int argc, char *argv[] )
{
     argc--; argv++; /* program name */

     while( argc ) {
          if( strcmp( *argv, "middle" ) == 0 ) {
               stacking_id = DWSC_MIDDLE;
          }
          else if( strcmp( *argv, "upper" ) == 0 ) {
               stacking_id = DWSC_UPPER;
          }
          else if( strcmp( *argv, "lower" ) == 0 ) {
               stacking_id = DWSC_LOWER;
          }
          else {
               printf( "command %s not understood: Must be middle, upper or lower.\n", *argv );
          }
          argv++;
          argc--;
     }
}

static inline long myclock()
{
  struct timeval tv;

  gettimeofday (&tv, NULL);
  return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int main( int argc, char *argv[] )
{
     IDirectFB              *dfb;
     IDirectFBDisplayLayer  *layer;

     IDirectFBImageProvider *provider;
     IDirectFBVideoProvider *video_provider;

     IDirectFBSurface       *bgsurface;

     IDirectFBWindow        *window1;
     IDirectFBWindow        *window2;
     IDirectFBSurface       *window_surface1;
     IDirectFBSurface       *window_surface2;

     IDirectFBEventBuffer   *buffer;

     IDirectFBFont          *font;

     DFBDisplayLayerConfig         layer_config;
     DFBGraphicsDeviceDescription  gdesc;
     IDirectFBWindow*              upper;
     DFBWindowID                   id1;

     int fontheight;
     int rotation;
     int err;
     int quit = 0;

     IDirectFBWindow* active = NULL;
     int grabbed = 0;
     int startx = 0;
     int starty = 0;
     int endx = 0;
     int endy = 0;
     int winupdate = 0, winx = 0, winy = 0;

     DFBCHECK(DirectFBInit( &argc, &argv ));
     DFBCHECK(DirectFBCreate( &dfb ));

     /* command line might be altered by DirectFBInit */
     read_command_line( argc, argv );

     dfb->GetDeviceDescription( dfb, &gdesc );

     DFBCHECK(dfb->GetDisplayLayer( dfb, DLID_PRIMARY, &layer ));

     layer->SetCooperativeLevel( layer, DLSCL_ADMINISTRATIVE );

/*     if (!((gdesc.blitting_flags & DSBLIT_BLEND_ALPHACHANNEL) &&
           (gdesc.blitting_flags & DSBLIT_BLEND_COLORALPHA  )))
     {
          layer_config.flags = DLCONF_BUFFERMODE;
          layer_config.buffermode = DLBM_BACKSYSTEM;

          layer->SetConfiguration( layer, &layer_config );
     }
*/
     layer->GetConfiguration( layer, &layer_config );
#ifdef DIRECTFB_ROTATE
     layer->GetRotation( layer, &rotation );
#endif
     layer->EnableCursor ( layer, 1 );

     {
          DFBFontDescription desc;

          desc.flags = DFDESC_HEIGHT;
          desc.height = layer_config.width/42;

          DFBCHECK(dfb->CreateFont( dfb, FONT, &desc, &font ));
          font->GetHeight( font, &fontheight );
     }

     if (argc < 2 ||
         dfb->CreateVideoProvider( dfb, argv[1], &video_provider ) != DFB_OK)
     {
          video_provider = NULL;
     }

     {
          DFBSurfaceDescription desc;

          DFBCHECK(dfb->CreateImageProvider( dfb,
                                             DATADIR"/desktop.png",
                                             &provider ));

          desc.flags  = DSDESC_WIDTH | DSDESC_HEIGHT | DSDESC_CAPS;
          desc.width  = layer_config.width;
          desc.height = layer_config.height;
          desc.caps   = DSCAPS_SHARED;

#ifdef DIRECTFB_ROTATE
          if (rotation == 90 || rotation == 270)
               D_UTIL_SWAP( desc.width, desc.height );
#endif

          DFBCHECK(dfb->CreateSurface( dfb, &desc, &bgsurface ) );

          provider->RenderTo( provider, bgsurface, NULL );
          provider->Release( provider );

          DFBCHECK(bgsurface->SetFont( bgsurface, font ));

          bgsurface->SetColor( bgsurface, 0xCF, 0xCF, 0xFF, 0xFF );
          bgsurface->DrawString( bgsurface,
                                 "Move the mouse over a window to activate it.",
                                 -1, 0, 0, DSTF_LEFT | DSTF_TOP );

          bgsurface->SetColor( bgsurface, 0xCF, 0xDF, 0xCF, 0xFF );
          bgsurface->DrawString( bgsurface,
                                 "Press left mouse button and drag to move the window.",
                                 -1, 0, fontheight, DSTF_LEFT | DSTF_TOP );

          bgsurface->SetColor( bgsurface, 0xCF, 0xEF, 0x9F, 0xFF );
          bgsurface->DrawString( bgsurface,
                                 "Press middle mouse button to raise/lower the window.",
                                 -1, 0, fontheight * 2, DSTF_LEFT | DSTF_TOP );

          bgsurface->SetColor( bgsurface, 0xCF, 0xFF, 0x6F, 0xFF );
          bgsurface->DrawString( bgsurface,
                                 "Hold right mouse button to fade in/out the window.", -1,
                                 0, fontheight * 3,
                                 DSTF_LEFT | DSTF_TOP );

          layer->SetBackgroundImage( layer, bgsurface );
          layer->SetBackgroundMode( layer, DLBM_IMAGE );
     }

     {
          DFBSurfaceDescription sdsc;
          DFBWindowDescription  desc;

          desc.flags = ( DWDESC_POSX | DWDESC_POSY |
                         DWDESC_WIDTH | DWDESC_HEIGHT | 
                         DWDESC_STACKING );

          if (!video_provider) {
               desc.caps = DWCAPS_ALPHACHANNEL;
               desc.surface_caps = DSCAPS_PREMULTIPLIED;
               desc.flags |= DWDESC_CAPS | DWDESC_SURFACE_CAPS;

               sdsc.width  = 300;
               sdsc.height = 200;
          }
          else {
               video_provider->GetSurfaceDescription( video_provider, &sdsc );

               if (sdsc.flags & DSDESC_CAPS) {
                    desc.flags       |= DWDESC_SURFACE_CAPS;
                    desc.surface_caps = sdsc.caps;
               }
          }

          desc.posx   = 20;
          desc.posy   = 120;
          desc.width  = sdsc.width;
          desc.height = sdsc.height;

          desc.stacking = stacking_id;

          DFBCHECK( layer->CreateWindow( layer, &desc, &window2 ) );
          window2->GetSurface( window2, &window_surface2 );

          window2->CreateEventBuffer( window2, &buffer );

          if (video_provider) {
               video_provider->PlayTo( video_provider, window_surface2,
                                       NULL, NULL, NULL );
          }
          else
          {
               window_surface2->SetDrawingFlags( window_surface2, DSDRAW_SRC_PREMULTIPLY );

               window_surface2->SetColor( window_surface2,
                                          0x00, 0x30, 0x10, 0xc0 );
               window_surface2->DrawRectangle( window_surface2,
                                               0, 0, desc.width, desc.height );
               window_surface2->SetColor( window_surface2,
                                          0x80, 0xa0, 0x00, 0x90 );
               window_surface2->FillRectangle( window_surface2,
                                               1, 1,
                                               desc.width-2, desc.height-2 );
          }

          window_surface2->Flip( window_surface2, NULL, 0 );

          window2->SetOpacity( window2, 0xFF );
     }

     {
          DFBWindowDescription desc;

          desc.flags  = ( DWDESC_POSX | DWDESC_POSY |
                          DWDESC_WIDTH | DWDESC_HEIGHT | 
                          DWDESC_CAPS | DWDESC_STACKING | DWDESC_SURFACE_CAPS );
          desc.posx   = 200;
          desc.posy   = 200;
          desc.width  = 512;
          desc.height = 145;
          desc.caps   = DWCAPS_ALPHACHANNEL;
          desc.surface_caps = DSCAPS_PREMULTIPLIED;

          desc.stacking = stacking_id;

          DFBCHECK(layer->CreateWindow( layer, &desc, &window1 ) );
          window1->GetSurface( window1, &window_surface1 );
          window_surface1->SetFont( window_surface1, font );

          DFBCHECK(dfb->CreateImageProvider( dfb,
                                             DATADIR"/dfblogo.png",
                                             &provider ));
          provider->RenderTo( provider, window_surface1, NULL );

//          window_surface1->Clear( window_surface1, 0xc0, 0xb0, 0x90, 0x90 );

          window_surface1->SetDrawingFlags( window_surface1, DSDRAW_SRC_PREMULTIPLY );
          window_surface1->SetColor( window_surface1, 0xFF, 0x20, 0x20, 0x90 );
          window_surface1->DrawRectangle( window_surface1,
                                          0, 0, desc.width, desc.height );

          window_surface1->Flip( window_surface1, NULL, 0 );

          provider->Release( provider );

          window1->AttachEventBuffer( window1, buffer );

          window1->SetOpacity( window1, 0xFF );

          window1->GetID( window1, &id1 );
     }

     window1->RequestFocus( window1 );
     window1->RaiseToTop( window1 );
     upper = window1;

     rotation = 0;

     while (!quit) {
          DFBWindowEvent evt;

          buffer->WaitForEventWithTimeout( buffer, 0, 10 );

          while (buffer->GetEvent( buffer, DFB_EVENT(&evt) ) == DFB_OK) {
               IDirectFBWindow* window;

               if (evt.window_id == id1)
                    window = window1;
               else
                    window = window2;

               if (evt.type == DWET_GOTFOCUS) {
                    active = window;
               }
               else if (active) {
                    switch (evt.type) {

                    case DWET_BUTTONDOWN:
                         if (!grabbed) {
                              grabbed = evt.buttons;
                              startx  = evt.cx;
                              starty  = evt.cy;
                              window->GrabPointer( window );
                         }
                         break;

                    case DWET_BUTTONUP:
                         switch (evt.button) {
                              case DIBI_LEFT:
                                   if (grabbed && !evt.buttons) {
                                        window->UngrabPointer( window );
                                        grabbed = 0;
                                   }
                                   break;
                              case DIBI_MIDDLE:
                                   upper->LowerToBottom( upper );
                                   upper =
                                     (upper == window1) ? window2 : window1;
                                   break;
                              case DIBI_RIGHT:
                                   quit = DIKS_DOWN;
                                   break;
                              default:
                                   break;
                         }
                         break;

                    case DWET_KEYDOWN:
                         if (grabbed)
                              break;
                         switch (evt.key_id) {
                              case DIKI_RIGHT:
                                   active->Move (active, 1, 0);
                                   break;
                              case DIKI_LEFT:
                                   active->Move (active, -1, 0);
                                   break;
                              case DIKI_UP:
                                   active->Move (active, 0, -1);
                                   break;
                              case DIKI_DOWN:
                                   active->Move (active, 0, 1);
                                   break;
                              default:
                                   break;
                         }
                         break;

                    case DWET_LOSTFOCUS:
                         if (!grabbed && active == window)
                              active = NULL;
                         break;

                    default:
                         break;

                    }
               }

               switch (evt.type) {

               case DWET_MOTION:
                    endx = evt.cx;
                    endy = evt.cy;
                    winx = evt.x;
                    winy = evt.y;
                    winupdate = 1;
                    break;

               case DWET_KEYDOWN:
                    switch (evt.key_symbol) {
                    case DIKS_ESCAPE:
                    case DIKS_SMALL_Q:
                    case DIKS_CAPITAL_Q:
                    case DIKS_BACK:
                    case DIKS_STOP:
                         quit = 1;
                         break;
                    case DIKS_SMALL_R:
                         if (active) {
                              rotation = (rotation + 90) % 360;

#ifdef DIRECTFB_ROTATE
                              active->SetRotation( active, rotation );
#endif
                         }
                         break;
                    default:
                         break;
                    }
                    break;

               default:
                    break;
               }
          }

          if (video_provider)
               window_surface2->Flip( window_surface2, NULL, 0 );

          if (active) {
               if (grabbed == 1) {
                    active->Move( active, endx - startx, endy - starty);
                    startx = endx;
                    starty = endy;
               }
               else if (grabbed == 2) {
                    active->SetOpacity( active,
                                        (sin( myclock()/300.0 ) * 85) + 170 );
               }
               else if (winupdate) {
                    char buf[32];
                    DFBRectangle rect;
                    DFBRegion    region;

                    snprintf( buf, sizeof(buf), "x/y: %4d,%4d", winx, winy );

                    font->GetStringExtents( font, buf, -1, &rect, NULL );

                    rect.x = 1;
                    rect.y = 1;

                    rect.w += rect.w / 3;
                    rect.h += 10;

                    window_surface1->SetColor( window_surface1, 0x10, 0x10, 0x10, 0x77 );
                    window_surface1->FillRectangles( window_surface1, &rect, 1 );

                    window_surface1->SetColor( window_surface1, 0x88, 0xCC, 0xFF, 0xAA );
                    window_surface1->DrawString( window_surface1, buf, -1, rect.h/4, 5, DSTF_TOPLEFT );


                    region = DFB_REGION_INIT_FROM_RECTANGLE( &rect );

                    window_surface1->Flip( window_surface1, &region, 0 );

                    winupdate = 0;
               }
          }
     }

     if (video_provider)
          video_provider->Release( video_provider );

     buffer->Release( buffer );
     font->Release( font );
     window_surface2->Release( window_surface2 );
     window_surface1->Release( window_surface1 );
     window2->Release( window2 );
     window1->Release( window1 );
     layer->Release( layer );
     bgsurface->Release( bgsurface );
     dfb->Release( dfb );

     return 42;
}
