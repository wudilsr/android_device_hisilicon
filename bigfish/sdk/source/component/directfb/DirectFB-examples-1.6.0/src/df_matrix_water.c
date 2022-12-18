/*
   (c) Copyright 2001-2008  The DirectFB Organization (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Hundt <andi@fischlustig.de>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrjälä <syrjala@sci.fi> and
              Claudio Ciccani <klan@users.sf.net>.
              
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

#include <direct/util.h>

/* Include extended rendering interface (Water) */
#include <directfb_water.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <math.h>

//#define USE_FLOAT

/**********************************************************************************************************************/

static IDirectFB            *dfb     = NULL;
static IDirectFBSurface     *primary = NULL;
static IDirectFBEventBuffer *events  = NULL;
static IWater               *water   = NULL;

/**********************************************************************************************************************/

static void init_application( int *argc, char **argv[] );
static void exit_application( int status );

/**********************************************************************************************************************/

static inline void
matrix_rotate_16_16( IWater *water,
                     int     radians )
{
     WaterAttributeHeader header;
     WaterTransform       transform;

     header.type  = WAT_RENDER_TRANSFORM;
     header.flags = WAF_NONE;

     transform.flags       = WTF_TYPE;
     transform.scalar      = WST_FIXED_16_16;
     transform.type        = WTT_ROTATE_FREE;
     transform.matrix[0].i = radians;

     water->SetAttribute( water, &header, &transform );
}

static inline void
matrix_translate_16_16( IWater *water,
                        int     translate_x,
                        int     translate_y )
{
     WaterAttributeHeader header;
     WaterTransform       transform;

     header.type  = WAT_RENDER_TRANSFORM;
     header.flags = WAF_NONE;

     transform.flags       = WTF_TYPE;
     transform.scalar      = WST_FIXED_16_16;
     transform.type        = WTT_TRANSLATE_X | WTT_TRANSLATE_Y;
     transform.matrix[0].i = translate_x;
     transform.matrix[1].i = translate_y;

     water->SetAttribute( water, &header, &transform );
}

static inline void
matrix_scale_16_16( IWater *water,
                    int     scale_x,
                    int     scale_y )
{
     WaterAttributeHeader header;
     WaterTransform       transform;

     header.type  = WAT_RENDER_TRANSFORM;
     header.flags = WAF_NONE;

     transform.flags       = WTF_TYPE;
     transform.scalar      = WST_FIXED_16_16;
     transform.type        = WTT_SCALE_X | WTT_SCALE_Y;
     transform.matrix[0].i = scale_x;
     transform.matrix[1].i = scale_y;

     water->SetAttribute( water, &header, &transform );
}


static inline void
matrix_rotate_float( IWater *water,
                     float   radians )
{
     WaterAttributeHeader header;
     WaterTransform       transform;

     header.type  = WAT_RENDER_TRANSFORM;
     header.flags = WAF_NONE;

     transform.flags       = WTF_TYPE;
     transform.scalar      = WST_FLOAT;
     transform.type        = WTT_ROTATE_FREE;
     transform.matrix[0].f = radians;

     water->SetAttribute( water, &header, &transform );
}

static inline void
matrix_translate_float( IWater *water,
                        float   translate_x,
                        float   translate_y )
{
     WaterAttributeHeader header;
     WaterTransform       transform;

     header.type  = WAT_RENDER_TRANSFORM;
     header.flags = WAF_NONE;

     transform.flags       = WTF_TYPE;
     transform.scalar      = WST_FLOAT;
     transform.type        = WTT_TRANSLATE_X | WTT_TRANSLATE_Y;
     transform.matrix[0].f = translate_x;
     transform.matrix[1].f = translate_y;

     water->SetAttribute( water, &header, &transform );
}

static inline void
matrix_scale_float( IWater *water,
                    float   scale_x,
                    float   scale_y )
{
     WaterAttributeHeader header;
     WaterTransform       transform;

     header.type  = WAT_RENDER_TRANSFORM;
     header.flags = WAF_NONE;

     transform.flags       = WTF_TYPE;
     transform.scalar      = WST_FLOAT;
     transform.type        = WTT_SCALE_X | WTT_SCALE_Y;
     transform.matrix[0].f = scale_x;
     transform.matrix[1].f = scale_y;

     water->SetAttribute( water, &header, &transform );
}

/**********************************************************************************************************************/

static const WaterColor m_white    = { 0xff, 0xff, 0xff, 0xff };
static const WaterColor m_green    = { 0xff, 0x00, 0xff, 0x00 };
static const WaterColor m_blue     = { 0xff, 0x00, 0x00, 0xff };
static const WaterColor m_red      = { 0xff, 0xff, 0x00, 0x00 };
static const WaterColor m_gray     = { 0xff, 0xcc, 0xcc, 0xcc };
static const WaterColor m_bluish   = { 0xff, 0x12, 0x34, 0x56 };
static const WaterColor m_greenish = { 0xff, 0x80, 0x90, 0x70 };

/* Attributes for four rectangles and two lines */
static const WaterAttribute m_attributes[] = {{
     .header.type   = WAT_FILL_COLOR,   /* [0] white - rect fill */
     .header.flags  = WAF_NONE,
     .header.scalar = WST_INTEGER,
     .value         = &m_white
},{
     .header.type   = WAT_FILL_COLOR,   /* [1] green - rect fill */
     .header.flags  = WAF_NONE,
     .header.scalar = WST_INTEGER,
     .value         = &m_green
},{
     .header.type   = WAT_FILL_COLOR,   /* [2] blue - rect fill */
     .header.flags  = WAF_NONE,
     .header.scalar = WST_INTEGER,
     .value         = &m_blue
},{
     .header.type   = WAT_FILL_COLOR,   /* [3] red - rect fill/draw (including next attribute) */
     .header.flags  = WAF_NONE,
     .header.scalar = WST_INTEGER,
     .value         = &m_red
},{
     .header.type   = WAT_DRAW_COLOR,   /* [4] gray - " */
     .header.flags  = WAF_NONE,
     .header.scalar = WST_INTEGER,
     .value         = &m_gray
},{
     .header.type   = WAT_DRAW_COLOR,   /* [5] bluish - line draw */
     .header.flags  = WAF_NONE,
     .header.scalar = WST_INTEGER,
     .value         = &m_bluish
},{
     .header.type   = WAT_DRAW_COLOR,   /* [6] white - line draw */
     .header.flags  = WAF_NONE,
     .header.scalar = WST_INTEGER,
     .value         = &m_white
},{
     .header.type   = WAT_FILL_COLOR,   /* [7] greenish - triangle fill */
     .header.flags  = WAF_NONE,
     .header.scalar = WST_INTEGER,
     .value         = &m_greenish
}};

/* Values for four rectangles */
static const WaterScalar m_rect_values[] = {
     { .i =   -20 }, { .i =  -20 }, /* [ 0] white rectangle */
     { .i =    40 }, { .i =   40 },

     { .i =  -120 }, { .i =  -20 }, /* [ 4] green rectangle */
     { .i =    40 }, { .i =   40 },

     { .i =   -20 }, { .i = -120 }, /* [ 8] blue rectangle */
     { .i =    40 }, { .i =   40 },

     { .i =   100 }, { .i =  100 }, /* [12] red/gray rectangle (fill/stroke) */
     { .i =   100 }, { .i =  100 },
};

/* Values for two lines */
static const WaterScalar m_line_values[] = {
     { .i =     0 }, { .i =    0 }, /* [0] bluish line */
     { .i =   300 }, { .i =  300 },

     { .i =   -20 }, { .i =  -20 }, /* [4] white line */
     { .i =  -300 }, { .i = -300 },
};

/* Values for a triangle */
static const WaterScalar m_tri_values[] = {
     { .i =     0 }, { .i =    0 }, /* [0] greenish triangle */
     { .i =   200 }, { .i = -210 },
     { .i =  -200 }, { .i =  190 },
};

/* Elements for four rectangles and two lines */
static const WaterElement m_elements[] = {{
     .header.type      = WET_RECTANGLE,
     .header.flags     = WEF_FILL,
     .header.scalar    = WST_INTEGER,
     .values           = &m_rect_values[0],
     .num_values       = 4,
},{
     .header.type      = WET_RECTANGLE,
     .header.flags     = WEF_FILL,
     .header.scalar    = WST_INTEGER,
     .values           = &m_rect_values[4],
     .num_values       = 4,
},{
     .header.type      = WET_RECTANGLE,
     .header.flags     = WEF_FILL,
     .header.scalar    = WST_INTEGER,
     .values           = &m_rect_values[8],
     .num_values       = 4,
},{
     .header.type      = WET_RECTANGLE,
     .header.flags     = WEF_FILL | WEF_DRAW,
     .header.scalar    = WST_INTEGER,
     .values           = &m_rect_values[12],
     .num_values       = 4,
},{
     .header.type      = WET_LINE,
     .header.flags     = WEF_DRAW,
     .header.scalar    = WST_INTEGER,
     .values           = &m_line_values[0],
     .num_values       = 4,
},{
     .header.type      = WET_LINE,
     .header.flags     = WEF_DRAW,
     .header.scalar    = WST_INTEGER,
     .values           = &m_line_values[4],
     .num_values       = 4,
},{
     .header.type      = WET_TRIANGLE,
     .header.flags     = WEF_FILL,
     .header.scalar    = WST_INTEGER,
     .values           = &m_tri_values[0],
     .num_values       = 4,
}};

/* Shapes */
static const WaterShape m_shapes[] = {{
     .header.flags       = WSF_NONE,
     .attributes         = &m_attributes[0],      /* [0] White */
     .num_attributes     = 1,
     .elements           = &m_elements[0],        /* - rect fill [0] */
     .num_elements       = 1,
},{
     .header.flags       = WSF_NONE,
     .attributes         = &m_attributes[1],      /* [1] Green */
     .num_attributes     = 1,
     .elements           = &m_elements[1],        /* - rect fill [1] */
     .num_elements       = 1,
},{
     .header.flags       = WSF_NONE,
     .attributes         = &m_attributes[2],      /* [2] Blue */
     .num_attributes     = 1,
     .elements           = &m_elements[2],        /* - rect fill [2] */
     .num_elements       = 1,
},{
     .header.flags       = WSF_NONE,
     .attributes         = &m_attributes[3],      /* [3] Red / Gray */
     .num_attributes     = 2,
     .elements           = &m_elements[3],        /* - rect draw+fill [3] */
     .num_elements       = 1,
},{
     .header.flags       = WSF_NONE,
     .attributes         = &m_attributes[5],      /* [5] Bluish */
     .num_attributes     = 1,
     .elements           = &m_elements[4],        /* - line draw [4] */
     .num_elements       = 1,
},{
     .header.flags       = WSF_NONE,
     .attributes         = &m_attributes[6],      /* [6] White */
     .num_attributes     = 1,
     .elements           = &m_elements[5],        /* - line draw [5] */
     .num_elements       = 1,
},{
     .header.flags       = WSF_NONE,
     .attributes         = &m_attributes[7],      /* [7] Greenish */
     .num_attributes     = 1,
     .elements           = &m_elements[6],        /* - triangle fill [6] */
     .num_elements       = 1,
}};


int
main( int argc, char *argv[] )
{
     int                  i = 0;
     int                  width, height;
     WaterAttributeHeader header;
     WaterTransform       transform;

     /* Initialize application. */
     init_application( &argc, &argv );

     /* Query size of output surface. */
     primary->GetSize( primary, &width, &height );

     /* Transform coordinates to have 0,0 in the center. */
     header.type  = WAT_RENDER_TRANSFORM;
     header.flags = WAF_NONE;

     transform.flags       = WTF_TYPE | WTF_REPLACE;
     transform.type        = WTT_TRANSLATE_X | WTT_TRANSLATE_Y;
     transform.scalar      = WST_INTEGER;
     transform.matrix[0].i = width  / 2;
     transform.matrix[1].i = height / 2;

     water->SetAttribute( water, &header, &transform );

     /* Main loop. */
     while (1) {
          DFBInputEvent event;

          /* Clear the frame with black. */
          primary->Clear( primary, 0x00, 0x00, 0x00, 0x00 );

          /*
           * Render the whole scene via Shapes.
           *
           * The original version of the demo had 24 calls to IDirectFBSurface for this.
           */
          water->RenderShapes( water, primary, m_shapes, D_ARRAY_SIZE(m_shapes) );


          /* Flip the output surface. */
          primary->Flip( primary, NULL, DSFLIP_WAITFORSYNC );



          /* Rotate and scale scene slightly. */
          matrix_rotate_16_16( water, 0.1 * 0x10000 );
          matrix_scale_16_16( water, 0.99 * 0x10000, 0.99 * 0x10000 );

          /* Reset to initial transform after 500 frames. */
          if (++i == 500) {
               i = 0;

               water->SetAttribute( water, &header, &transform );
          }



          /* Check for new events. */
          while (events->GetEvent( events, DFB_EVENT(&event) ) == DFB_OK) {

               /* Handle key press events. */
               if (event.type == DIET_KEYPRESS) {
                    switch (event.key_symbol) {
                         case DIKS_ESCAPE:
                         case DIKS_POWER:
                         case DIKS_BACK:
                         case DIKS_SMALL_Q:
                         case DIKS_CAPITAL_Q:
                              exit_application( 0 );
                              break;

                         default:
                              break;
                    }
               }
          }
     }

     /* Shouldn't reach this. */
     return 0;
}

/**********************************************************************************************************************/

static void
init_application( int *argc, char **argv[] )
{
     DFBResult             ret;
     DFBSurfaceDescription desc;

     /* Initialize DirectFB including command line parsing. */
     ret = DirectFBInit( argc, argv );
     if (ret) {
          DirectFBError( "DirectFBInit() failed", ret );
          exit_application( 1 );
     }

     /* Create the super interface. */
     ret = DirectFBCreate( &dfb );
     if (ret) {
          DirectFBError( "DirectFBCreate() failed", ret );
          exit_application( 2 );
     }

     /* Request fullscreen mode. */
     dfb->SetCooperativeLevel( dfb, DFSCL_FULLSCREEN );

     /* Fill the surface description. */
     desc.flags       = DSDESC_CAPS | DSDESC_PIXELFORMAT;
     desc.caps        = DSCAPS_PRIMARY | DSCAPS_DOUBLE;
     desc.pixelformat = DSPF_ARGB;
     
     /* Create a primary surface. */
     ret = dfb->CreateSurface( dfb, &desc, &primary );
     if (ret) {
          DirectFBError( "IDirectFB::CreateSurface() failed", ret );
          exit_application( 3 );
     }
     
     /* Create an event buffer with key capable devices attached. */
     ret = dfb->CreateInputEventBuffer( dfb, DICAPS_KEYS, DFB_FALSE, &events );
     if (ret) {
          DirectFBError( "IDirectFB::CreateEventBuffer() failed", ret );
          exit_application( 4 );
     }
     
     /* Clear. */
     primary->Clear( primary, 0x00, 0x00, 0x00, 0x00 );
     primary->Flip( primary, NULL, 0 );

     /* Get the extended rendering interface. */
     ret = dfb->GetInterface( dfb, "IWater", NULL, dfb, (void**) &water );
     if (ret) {
          DirectFBError( "IDirectFB::GetInterface( 'IWater' ) failed", ret );
          exit_application( 5 );
     }
}

static void
exit_application( int status )
{
     /* Release the extended rendering interface. */
     if (water)
          water->Release( water );

     /* Release the event buffer. */
     if (events)
          events->Release( events );

     /* Release the primary surface. */
     if (primary)
          primary->Release( primary );

     /* Release the super interface. */
     if (dfb)
          dfb->Release( dfb );

     /* Terminate application. */
     exit( status );
}

