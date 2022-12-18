/*
 **************************************************************************************
 *       Filename:  SkJpegEncoder.cpp
 *    Description:  RGB565 to JPEG source file
 *
 *        Version:  1.0
 *        Created:  2012-06-06 15:29:39
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
//#define LOG_NDEBUG 0
#define LOG_TAG "SkJpegEncoder"
#include <utils/Log.h>

#include "CameraUtils.h"
#include "SkJpegUtility.h"
#include "SkJpegEncoder.h"
#include "SkColorPriv.h"

extern "C" {
    #include "jpeglib.h"
    #include "jerror.h"
}

// this enables timing code to report milliseconds for an encode
//#define TIME_ENCODE

// this enables our rgb->yuv code, which is faster than libjpeg on ARM
// disable for the moment, as we have some glitches when width != multiple of 4
#define WE_CONVERT_TO_YUV

// taken from jcolor.c in libjpeg
#if 0   // 16bit - precise but slow
    #define CYR     19595   // 0.299
    #define CYG     38470   // 0.587
    #define CYB     7471    // 0.114

    #define CUR     -11059  // -0.16874
    #define CUG     -21709  // -0.33126
    #define CUB     32768   // 0.5

    #define CVR     32768   // 0.5
    #define CVG     -27439  // -0.41869
    #define CVB     -5329   // -0.08131

    #define CSHIFT  16
#else      // 8bit - fast, slightly less precise
    #define CYR     77      // 0.299
    #define CYG     150     // 0.587
    #define CYB     29      // 0.114

    #define CUR     -43     // -0.16874
    #define CUG     -85     // -0.33126
    #define CUB     128     // 0.5

    #define CVR     128     // 0.5
    #define CVG     -107    // -0.41869
    #define CVB     -21     // -0.08131

    #define CSHIFT  8
#endif

/*
 **************************************************************************
 * FunctionName: rgb2yuv_32;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void rgb2yuv_32(uint8_t dst[], SkPMColor c)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    int r = SkGetPackedR32(c);
    int g = SkGetPackedG32(c);
    int b = SkGetPackedB32(c);

    int  y = ( CYR*r + CYG*g + CYB*b ) >> CSHIFT;
    int  u = ( CUR*r + CUG*g + CUB*b ) >> CSHIFT;
    int  v = ( CVR*r + CVG*g + CVB*b ) >> CSHIFT;

    dst[0] = SkToU8(y);
    dst[1] = SkToU8(u + 128);
    dst[2] = SkToU8(v + 128);
}

/*
 **************************************************************************
 * FunctionName: rgb2yuv_4444;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void rgb2yuv_4444(uint8_t dst[], U16CPU c)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    int r = SkGetPackedR4444(c);
    int g = SkGetPackedG4444(c);
    int b = SkGetPackedB4444(c);

    int  y = ( CYR*r + CYG*g + CYB*b ) >> (CSHIFT - 4);
    int  u = ( CUR*r + CUG*g + CUB*b ) >> (CSHIFT - 4);
    int  v = ( CVR*r + CVG*g + CVB*b ) >> (CSHIFT - 4);

    dst[0] = SkToU8(y);
    dst[1] = SkToU8(u + 128);
    dst[2] = SkToU8(v + 128);
}

/*
 **************************************************************************
 * FunctionName: rgb2yuv_16;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void rgb2yuv_16(uint8_t dst[], U16CPU c)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    int r = SkGetPackedR16(c);
    int g = SkGetPackedG16(c);
    int b = SkGetPackedB16(c);

    int y = ( 2*CYR*r + CYG*g + 2*CYB*b ) >> (CSHIFT - 2);
    int u = ( 2*CUR*r + CUG*g + 2*CUB*b ) >> (CSHIFT - 2);
    int v = ( 2*CVR*r + CVG*g + 2*CVB*b ) >> (CSHIFT - 2);

    dst[0] = SkToU8(y);
    dst[1] = SkToU8(u + 128);
    dst[2] = SkToU8(v + 128);
}


typedef void (*WriteScanline)(uint8_t* SK_RESTRICT dst,
                  const void* SK_RESTRICT src, int width,
                  const SkPMColor* SK_RESTRICT ctable);

/*
 **************************************************************************
 * FunctionName: Write_32_YUV;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void Write_32_YUV(uint8_t* SK_RESTRICT dst,
             const void* SK_RESTRICT srcRow, int width,
             const SkPMColor*)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    const uint32_t* SK_RESTRICT src = (const uint32_t*)srcRow;
    while (--width >= 0)
    {
#ifdef WE_CONVERT_TO_YUV
        rgb2yuv_32(dst, *src++);
#else
        uint32_t c = *src++;
        dst[0] = SkGetPackedR32(c);
        dst[1] = SkGetPackedG32(c);
        dst[2] = SkGetPackedB32(c);
#endif
        dst += 3;
    }
}

/*
 **************************************************************************
 * FunctionName: Write_4444_YUV;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void Write_4444_YUV(uint8_t* SK_RESTRICT dst,
               const void* SK_RESTRICT srcRow, int width,
               const SkPMColor*)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    const SkPMColor16* SK_RESTRICT src = (const SkPMColor16*)srcRow;
    while (--width >= 0)
    {
#ifdef WE_CONVERT_TO_YUV
        rgb2yuv_4444(dst, *src++);
#else
        SkPMColor16 c = *src++;
        dst[0] = SkPacked4444ToR32(c);
        dst[1] = SkPacked4444ToG32(c);
        dst[2] = SkPacked4444ToB32(c);
#endif
        dst += 3;
    }
}

/*
 **************************************************************************
 * FunctionName: Write_16_YUV;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void Write_16_YUV(uint8_t* SK_RESTRICT dst,
             const void* SK_RESTRICT srcRow, int width,
             const SkPMColor*)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    const uint16_t* SK_RESTRICT src = (const uint16_t*)srcRow;
    while (--width >= 0)
    {
#ifdef WE_CONVERT_TO_YUV
        rgb2yuv_16(dst, *src++);
#else
        uint16_t c = *src++;
        dst[0] = SkPacked16ToR32(c);
        dst[1] = SkPacked16ToG32(c);
        dst[2] = SkPacked16ToB32(c);
#endif
        dst += 3;
    }
}

/*
 **************************************************************************
 * FunctionName: Write_Index_YUV;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static void Write_Index_YUV(uint8_t* SK_RESTRICT dst,
                const void* SK_RESTRICT srcRow, int width,
                const SkPMColor* SK_RESTRICT ctable)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    const uint8_t* SK_RESTRICT src = (const uint8_t*)srcRow;
    while (--width >= 0)
    {
#ifdef WE_CONVERT_TO_YUV
        rgb2yuv_32(dst, ctable[*src++]);
#else
        uint32_t c = ctable[*src++];
        dst[0] = SkGetPackedR32(c);
        dst[1] = SkGetPackedG32(c);
        dst[2] = SkGetPackedB32(c);
#endif
        dst += 3;
    }
}

/*
 **************************************************************************
 * FunctionName: ChooseWriter;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static WriteScanline ChooseWriter(const SkBitmap& bm)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    switch (bm.config())
    {
        case SkBitmap::kARGB_8888_Config:
            return Write_32_YUV;
        case SkBitmap::kRGB_565_Config:
            return Write_16_YUV;
        case SkBitmap::kARGB_4444_Config:
            return Write_4444_YUV;
        case SkBitmap::kIndex8_Config:
            return Write_Index_YUV;
        default:
            return NULL;
    }
}

/*
 **************************************************************************
 * FunctionName: SkJpegImageEncoder::onEncode;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
bool SkJpegImageEncoder::onEncode(SkWStream* stream, const SkBitmap& bm, int quality)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

#ifdef TIME_ENCODE
    AutoTimeMillis atm("JPEG Encode");
#endif

    const WriteScanline writer = ChooseWriter(bm);
    if (NULL == writer)
    {
        return false;
    }

    SkAutoLockPixels alp(bm);
    if (NULL == bm.getPixels())
    {
        return false;
    }

    jpeg_compress_struct    cinfo;
    skjpeg_error_mgr        sk_err;
    skjpeg_destination_mgr  sk_wstream(stream);

    // allocate these before set call setjmp
    SkAutoMalloc     oneRow;
    SkAutoLockColors ctLocker;

    cinfo.err           = jpeg_std_error(&sk_err);
    sk_err.error_exit   = skjpeg_error_exit;
    if (setjmp(sk_err.fJmpBuf))
    {
        return false;
    }
    jpeg_create_compress(&cinfo);

    cinfo.dest              = &sk_wstream;
    cinfo.image_width       = bm.width();
    cinfo.image_height      = bm.height();
    cinfo.input_components  = 3;
#ifdef WE_CONVERT_TO_YUV
    cinfo.in_color_space    = JCS_YCbCr;
#else
    cinfo.in_color_space    = JCS_RGB;
#endif
    cinfo.input_gamma       = 1;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);
    cinfo.dct_method = JDCT_IFAST;

    jpeg_start_compress(&cinfo, TRUE);

    const int       width   = bm.width();
        uint8_t*        oneRowP = (uint8_t*)oneRow.reset(width * 3);

    const SkPMColor* colors = ctLocker.lockColors(bm);
    const void*      srcRow = bm.getPixels();

    while (cinfo.next_scanline < cinfo.image_height)
    {
        JSAMPROW row_pointer[1];    /* pointer to JSAMPLE row[s] */

        writer(oneRowP, srcRow, width, colors);
        row_pointer[0] = oneRowP;
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
        srcRow = (const void*)((const char*)srcRow + bm.rowBytes());
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    return true;
}

/********************************** END **********************************************/
