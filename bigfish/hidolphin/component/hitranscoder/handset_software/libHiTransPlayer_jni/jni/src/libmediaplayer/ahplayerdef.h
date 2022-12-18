#ifndef __AHPLAYERDEF__
#define __AHPLAYERDEF__

#define REALDEVICE 1
//can't stat fps in emulator now
#if REALDEVICE
#define FPS_DEBUGGING 0
#else
#define FPS_DEBUGGING 0
#endif

#define ANDROIDVERSION23 0
//whether using libsf
#define USINGLIBSF 0

/////for decoding capacity test
#define NODISPLAY 0
#define NOAUDIO 0
#define NOSYNC 0

/////Set sync mode
#define SYNCTOAUDIO 1

#define MAXPOSITIVEPTSERROR 30
#define MINNEGATIVEPTSERROR -1000

#define PERFORMANCETEST 0

//#define  PROFILING /*printf profiling info*/
#define BMPRENDER 0

#define RENDERINDECODER 0

#define SKIARENDER 0
//允许改变分辨率
#define CHANGEASR 0
#if CHANGEASR
#define VDTHREADCOUNT 1
#else
#define VDTHREADCOUNT 4
#endif
#define OMX_QCOM_COLOR_FormatYVU420SemiPlanar  0x7FA30C00
#define OMX_QOMX_COLOR_FormatYVU420PackedSemiPlanar32m4ka  0x7FA30C01
#define OMX_QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka  0x7FA30C03
#define OMX_TI_COLOR_FormatYUV420PackedSemiPlanar 0x7f000100
#endif
