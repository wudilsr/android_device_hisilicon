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


#include <directfb.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

/* macro for a safe call to DirectFB functions */
#define DFBCHECK(x...)                                                    \
     {                                                                    \
          err = x;                                                        \
          if (err != DFB_OK) {                                            \
               fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ );     \
               DirectFBErrorFatal( #x, err );                             \
          }                                                               \
     }

/* DirectFB interfaces */
IDirectFB               *dfb;
IDirectFBSurface        *primary;
IDirectFBDisplayLayer   *layer;
IDirectFBEventBuffer    *keybuffer;
IDirectFBImageProvider  *provider;
IDirectFBFont           *font;

/* DirectFB surfaces */
IDirectFBSurface *gridimage;
IDirectFBSurface *testimage;
IDirectFBSurface *testimage2;

/* values on which placement of various elements may depend */
int xres;
int yres;
int fontheight;

void init_resources( int argc, char *argv[] )
{
     DFBResult err;
     DFBSurfaceDescription dsc;

     srand((long)time(0));

     DFBCHECK(DirectFBInit( &argc, &argv ));

     /* create the super interface */
     DFBCHECK(DirectFBCreate( &dfb ));

     /* create an input buffer for key events */
     DFBCHECK(dfb->CreateInputEventBuffer( dfb, DICAPS_KEYS,
                                           DFB_FALSE, &keybuffer ));

     /* set our cooperative level to DFSCL_FULLSCREEN for exclusive access to
        the primary layer */
     err = dfb->SetCooperativeLevel( dfb, DFSCL_FULLSCREEN );
     if (err)
       DirectFBError( "Failed to get exclusive access", err );

     DFBCHECK(dfb->GetDisplayLayer( dfb, DLID_PRIMARY, &layer ));

     /* get the primary surface, i.e. the surface of the primary layer we have
        exclusive access to */
     dsc.flags = DSDESC_CAPS;
     dsc.caps = DSCAPS_PRIMARY;

     DFBCHECK(dfb->CreateSurface( dfb, &dsc, &primary ));
     DFBCHECK(primary->GetSize( primary, &xres, &yres ));

     /* load font */
     {
          DFBFontDescription desc;

          desc.flags = DFDESC_HEIGHT;
          desc.height = 24;

          DFBCHECK(dfb->CreateFont( dfb, FONT, &desc, &font ));
          DFBCHECK(font->GetHeight( font, &fontheight ));
          DFBCHECK(primary->SetFont( primary, font ));
     }

     DFBCHECK(dfb->CreateImageProvider( dfb, DATADIR"/grid.gif",
                                        &provider ));

     DFBCHECK(provider->GetSurfaceDescription (provider, &dsc));
     DFBCHECK(dfb->CreateSurface( dfb, &dsc, &gridimage ));

     DFBCHECK(provider->RenderTo( provider, gridimage, NULL ));
     provider->Release( provider );

     /* load the penguin destination mask */
     DFBCHECK(dfb->CreateImageProvider( dfb, DATADIR
                                        "/pngtest.png",
                                        &provider ));

     DFBCHECK(provider->GetSurfaceDescription( provider, &dsc ));

     dsc.width  = 128;
     dsc.height = 256;

     DFBCHECK(dfb->CreateSurface( dfb, &dsc, &testimage ));

     DFBCHECK(provider->RenderTo( provider, testimage, NULL ));
     
     dsc.width  = 192;
     dsc.height = 96;

     DFBCHECK(dfb->CreateSurface( dfb, &dsc, &testimage2 ));

     DFBCHECK(provider->RenderTo( provider, testimage2, NULL ));
     
     
     provider->Release( provider );
}

/*
 * deinitializes resources and DirectFB
 */
void deinit_resources()
{
     gridimage->Release( gridimage );
     testimage->Release( testimage );
     testimage2->Release( testimage2 );
     primary->Release( primary );
     keybuffer->Release( keybuffer );
     layer->Release( layer );
     dfb->Release( dfb );

}

int main( int argc, char *argv[] )
{
     DFBResult err;
     int quit = 0;
     DFBRegion clipreg = { 128, 128, 384+128-1, 256+128-1 };
     int clip_enabled = 0;
     DFBSurfaceBlittingFlags blittingflags = DSBLIT_NOFX;

     init_resources( argc, argv );

     primary->Clear( primary, 0x00, 0x00, 0x00, 0xFF );
     primary->Blit( primary, gridimage, NULL, 128, 128 );
     /* flip display */
     DFBCHECK(primary->Flip( primary, NULL, DSFLIP_WAITFORSYNC ));

     /* main loop */
     while (!quit) {
          DFBInputEvent evt;

          /* process keybuffer */
          while (keybuffer->GetEvent( keybuffer, DFB_EVENT(&evt)) == DFB_OK) {
               if (evt.type == DIET_KEYPRESS) {
                    switch (DFB_LOWER_CASE(evt.key_symbol)) {
                         case DIKS_ESCAPE:
                         case DIKS_SMALL_Q:
                         case DIKS_BACK:
                         case DIKS_STOP:
                              /* quit main loop */
                              quit = 1;
                              break;
                         /* test blitting */
                         case DIKS_SMALL_B:
                              primary->SetClip( primary, NULL );
                              primary->Clear( primary, 0x00, 0x00, 0x00, 0xFF );
                              if (clip_enabled)
                                   primary->SetClip( primary, &clipreg );
                              else
                                   primary->SetClip( primary, NULL );
                              
                              primary->SetBlittingFlags( primary, DSBLIT_NOFX );
                              primary->Blit( primary, gridimage, NULL,  128, 128 );
                              
                              primary->SetBlittingFlags( primary, blittingflags );
                              primary->Blit( primary, testimage2, NULL,   64,  96 );
                              primary->Blit( primary, testimage2, NULL, 384,  96 );
                              primary->Blit( primary, testimage2, NULL, 64  , 320 );
                              primary->Blit( primary, testimage2, NULL, 384, 320 );
                              primary->Flip( primary, NULL, DSFLIP_WAITFORSYNC );
                              break;
                         /* test strechblitting */
                         case DIKS_SMALL_S: {
                              DFBRectangle drect;
                              primary->SetClip( primary, NULL );
                              primary->Clear( primary, 0x00, 0x00, 0x00, 0xFF );
                              if (clip_enabled)
                                   primary->SetClip( primary, &clipreg );
                              else
                                   primary->SetClip( primary, NULL );

                              primary->SetBlittingFlags( primary, DSBLIT_NOFX );
                              primary->Blit( primary, gridimage, NULL,  128, 128 );

                              primary->SetBlittingFlags( primary, blittingflags );
                              drect.x = 96;
                              drect.y = 32;
                              drect.w = 2.5*64;
                              drect.h = 2.5*64;
                              primary->StretchBlit( primary, testimage2, NULL, &drect );
                              drect.x = 384;
                              primary->StretchBlit( primary, testimage2, NULL, &drect );
                              drect.y = 320;
                              primary->StretchBlit( primary, testimage2, NULL, &drect );
                              drect.x = 96;
                              primary->StretchBlit( primary, testimage2, NULL, &drect );
                              primary->Flip( primary, NULL, DSFLIP_WAITFORSYNC );
                              break;
                         }
                         /* toggle clipping */
                         case DIKS_SMALL_C:
                              clip_enabled = !clip_enabled;
                              break;
                         /* toggle horizontal flipping */
                         case DIKS_SMALL_H:
                              blittingflags ^= DSBLIT_FLIP_HORIZONTAL;
                              break;
                         /* toggle vertical clipping */
                         case DIKS_SMALL_V:
                              blittingflags ^= DSBLIT_FLIP_VERTICAL;
                              break;
                         /* toggle rotate 90 */
                         case DIKS_SMALL_R:
                         case DIKS_9:
                              blittingflags ^= DSBLIT_ROTATE90;
                              break;
                         /* toggle rotate 180 */
                         case DIKS_1:
                              blittingflags ^= DSBLIT_ROTATE180;
                              break;
                         /* toggle rotate 270 */
                         case DIKS_2:
                              blittingflags ^= DSBLIT_ROTATE270;
                              break;
                         default:
                              break;
                    }
               }
          }
     }

     deinit_resources();
     return 42;
}
