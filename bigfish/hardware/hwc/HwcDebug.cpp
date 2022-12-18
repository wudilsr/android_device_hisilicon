/****************************************************************************
*
*    Copyright (c) 2005 - 2012 by Vivante Corp.  All rights reserved.
*
*    The material in this file is confidential and contains trade secrets
*    of Vivante Corporation. This is proprietary information owned by
*    Vivante Corporation. No part of this work may be disclosed,
*    reproduced, copied, transmitted, or used in any way for any purpose,
*    without the express written permission of Vivante Corporation.
*
*****************************************************************************/

#include <utils/Log.h>
#include <fcntl.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <hardware/hwcomposer_defs.h>
#include "HwcDebug.h"

#define BI_RGB            0L
#define BI_RLE8           1L
#define BI_RLE4           2L
#define BI_BITFIELDS      3L

#define ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
#define ALIGN_DOWN(x, align)  ((x) & ~((align)-1))
#define ALIGN_MASK_W (8)
#define ALIGN_MASK_H (2)

typedef struct _bitmapInfoHeader
{
    uint32_t   biSize;
    uint32_t   biWidth;
    uint32_t   biHeight;
    uint16_t   biPlanes;
    uint16_t   biBitCount;
    uint32_t   biCompression;
    uint32_t   biSizeImage;
    uint32_t   biXPelsPerMeter;
    uint32_t   biYPelsPerMeter;
    uint32_t   biClrUsed;
    uint32_t   biClrImportant;
}
__attribute__((packed)) bitmapInfoHeader;

typedef struct _bitmapFileHeader
{
    uint16_t   bfType;
    uint32_t   bfSize;
    uint16_t   bfReserved1;
    uint16_t   bfReserved2;
    uint32_t   bfOffBits;
}
__attribute__((packed)) bitmapFileHeader;

static int _big_endian = -1;

#ifdef HWC_DEBUG
static void _check_endian()
{
    uint32_t v = 0x01020304;
    _big_endian = ((unsigned char*) &v)[0] == 0x01;
}

static unsigned short _little16(unsigned short data)
{
    if (_big_endian)
    {
        data = ((data & 0x00ff) << 8) | ((data & 0xff00) >> 8);
    }

    return data;
}

static  uint32_t _little32( uint32_t data)
{
    if (_big_endian)
    {
        data = ((data & 0x000000ff) << 24) |
               ((data & 0x0000ff00) << 8)  |
               ((data & 0x00ff0000) >> 8)  |
               ((data & 0xff000000) >> 24);
    }

    return data;
}

int format2dumpformat(int format)
{
	switch(format) {
			case HAL_PIXEL_FORMAT_RGBA_8888:
				return RGBA_8888;
			case HAL_PIXEL_FORMAT_RGBX_8888:
				return RGBX_8888;
			case HAL_PIXEL_FORMAT_BGRA_8888:
				return BGRA_8888;
			case HAL_PIXEL_FORMAT_RGB_888:
				return RGB_888;
			case HAL_PIXEL_FORMAT_RGB_565:
#if PLATFORM_SDK_VERSION < 18
			case HAL_PIXEL_FORMAT_RGBA_5551:
			case HAL_PIXEL_FORMAT_RGBA_4444:
#endif
				return RGB_565;
			default:
				printf("format2dumpformat fail format is %d\n",format);
				return -1;
	}
}

static int _fconv( void* dest, int    destformat,  const void* source,  int  srcformat, int  count)
{
    int i;

    /* Get some shortcuts. */
    const uint8_t*   csource = (const uint8_t*)  source;
    const uint16_t* ssource = (const uint16_t*) source;
    uint8_t*   cdest = (uint8_t*)  dest;
    uint16_t* sdest = (uint16_t*) dest;

    /* Check source input. */
    if (source == NULL)
    {
        return -EINVAL;
    }
    switch (srcformat)
    {
        case RGBA_8888:
        case BGRA_8888:
        case RGBX_8888:
        case BGRX_8888:

        case RGB_888:
        case BGR_888:

        case RGB_565:
        case BGR_565:

        case ARGB_1555:
            break;

        default:
            return -EINVAL;
    }

    /* Check dest input. */
    if (dest == NULL)
    {
        return -EINVAL;
    }
    switch (destformat)
    {
        case RGBA_8888:
        case BGRA_8888:
        case RGBX_8888:
        case BGRX_8888:

        case RGB_888:
        case BGR_888:

        case RGB_565:
        case BGR_565:

        case ARGB_1555:
            break;

        default:
            return -EINVAL;
    }

    /* Special case for src format == dest format. */
    if (srcformat == destformat)
    {
        int bypp;

        switch (srcformat)
        {
            case RGBA_8888:
            case BGRA_8888:
            case RGBX_8888:
            case BGRX_8888:
                bypp = 4;
                break;

            case RGB_888:
            case BGR_888:
                bypp = 3;
                break;

            case RGB_565:
            case BGR_565:
            case ARGB_1555:
            default:
                bypp = 2;
                break;
        }

        memcpy(dest, source, bypp * count);
        return 0;
    }

    for (i = 0; i < count; i++)
    {
        uint32_t rgba;

        /* Convert to rgba8888. */
        switch (srcformat)
        {
            case RGBA_8888:
            case RGBX_8888:
                rgba = ((uint32_t*) source)[i];
                break;

            case BGRA_8888:
            case BGRX_8888:
                ((uint8_t*) &rgba)[0] = csource[i * 4 + 2];
                ((uint8_t*) &rgba)[1] = csource[i * 4 + 1];
                ((uint8_t*) &rgba)[2] = csource[i * 4 + 0];
                ((uint8_t*) &rgba)[3] = csource[i * 4 + 3];
                break;

            case RGB_888:
                ((uint8_t*) &rgba)[0] = csource[i * 3 + 0];
                ((uint8_t*) &rgba)[1] = csource[i * 3 + 1];
                ((uint8_t*) &rgba)[2] = csource[i * 3 + 2];
                ((uint8_t*) &rgba)[3] = 0xFF;
                break;

            case BGR_888:
                ((uint8_t*) &rgba)[0] = csource[i * 3 + 2];
                ((uint8_t*) &rgba)[1] = csource[i * 3 + 1];
                ((uint8_t*) &rgba)[2] = csource[i * 3 + 0];
                ((uint8_t*) &rgba)[3] = 0xFF;
                break;

            case RGB_565:
                /* R: 11111 000000 00000
                 * G: 00000 111111 00000
                 * B: 00000 000000 11111 */
                ((uint8_t*) &rgba)[0] = (ssource[i] & 0xF800) >> 8;
                ((uint8_t*) &rgba)[1] = (ssource[i] & 0x07E0) >> 3;
                ((uint8_t*) &rgba)[2] = (ssource[i] & 0x001F) << 3;
                ((uint8_t*) &rgba)[3] = 0xFF;
                break;

            case BGR_565:
                /* R: 00000 000000 11111
                 * G: 00000 111111 00000
                 * B: 11111 000000 00000 */
                ((uint8_t*) &rgba)[0] = (ssource[i] & 0x001F) << 3;
                ((uint8_t*) &rgba)[1] = (ssource[i] & 0x07E0) >> 3;
                ((uint8_t*) &rgba)[2] = (ssource[i] & 0xF800) >> 8;
                ((uint8_t*) &rgba)[3] = 0xFF;
                break;

            case ARGB_1555:
            default:
                /* R: 0 11111 00000 00000
                 * G: 0 00000 11111 00000
                 * B: 0 00000 00000 11111
                 * A: 1 00000 00000 00000 */
                ((uint8_t*) &rgba)[0] = (ssource[i] & 0x7C00) >> 7;
                ((uint8_t*) &rgba)[1] = (ssource[i] & 0x03E0) >> 2;
                ((uint8_t*) &rgba)[2] = (ssource[i] & 0x001F) << 3;
                ((uint8_t*) &rgba)[3] = (ssource[i] & 0x8000) >> 8;
                break;
        }

        /* Convert to dest format. */
        switch (destformat)
        {
            case RGBA_8888:
            case RGBX_8888:
                ((uint32_t*) dest)[i] = rgba;
                break;

            case BGRA_8888:
            case BGRX_8888:
                cdest[i * 4 + 2] = ((uint8_t*) &rgba)[0];
                cdest[i * 4 + 1] = ((uint8_t*) &rgba)[1];
                cdest[i * 4 + 0] = ((uint8_t*) &rgba)[2];
                cdest[i * 4 + 3] = ((uint8_t*) &rgba)[3];
                break;

            case RGB_888:
                cdest[i * 3 + 0] = ((uint8_t*) &rgba)[0];
                cdest[i * 3 + 1] = ((uint8_t*) &rgba)[1];
                cdest[i * 3 + 2] = ((uint8_t*) &rgba)[2];
                break;

            case BGR_888:
                cdest[i * 3 + 2] = ((uint8_t*) &rgba)[0];
                cdest[i * 3 + 1] = ((uint8_t*) &rgba)[1];
                cdest[i * 3 + 0] = ((uint8_t*) &rgba)[2];
                break;

            case RGB_565:
                /* R: 11111 000000 00000
                 * G: 00000 111111 00000
                 * B: 00000 000000 11111 */
                sdest[i] =
                    ((((uint8_t*) &rgba)[0] & 0xF8) << 8) |
                    ((((uint8_t*) &rgba)[1] & 0xFC) << 3) |
                    ((((uint8_t*) &rgba)[2] & 0xF8) >> 3);
                break;

            case BGR_565:
                /* R: 00000 000000 11111
                 * G: 00000 111111 00000
                 * B: 11111 000000 00000 */
                sdest[i] =
                    ((((uint8_t*) &rgba)[0] & 0xF8) >> 3) |
                    ((((uint8_t*) &rgba)[1] & 0xFC) << 3) |
                    ((((uint8_t*) &rgba)[2] & 0xF8) << 8);
                break;

            case ARGB_1555:
            default:
                /* R: 0 11111 00000 00000
                 * G: 0 00000 11111 00000
                 * B: 0 00000 00000 11111
                 * A: 1 00000 00000 00000 */
                sdest[i] =
                    ((((uint8_t*) &rgba)[0] & 0xF8) << 7) |
                    ((((uint8_t*) &rgba)[1] & 0xF8) << 2) |
                    ((((uint8_t*) &rgba)[2] & 0xF8) >> 3) |
                    ((((uint8_t*) &rgba)[3] & 0x80) << 8);
                break;
        }
    }

    return 0;
}


int _WriteBitmap( const char* filename,  const void* data,  unsigned int width, unsigned int height,  unsigned int stride, int format)
{
    bitmapFileHeader file_header;
    bitmapInfoHeader info_header;


    int fp = -1;
    unsigned int i;
    unsigned short  bypp;
    unsigned char* buff = NULL;  /* Buffer for dest data line. */
    const unsigned char* line;     /* Source data line. */
    unsigned int    dstride;          /* Dest stride. */


    _check_endian();               /* Check endian. */

    if (filename == NULL)
    {
    	printf("file name is err\n");
        return -EINVAL;
    }

    if (data == NULL)
    {
        return -EINVAL;
    }

    if (width == 0 || height == 0)
    {
        return -EINVAL;
    }

    /* Check source format and get bytes per pixel. */
    switch (format)
    {
        case RGBA_8888:
        case BGRA_8888:
        case RGBX_8888:
        case BGRX_8888:
            bypp = 4;
            break;

        case RGB_888:
        case BGR_888:
            bypp = 3;
            break;

        case RGB_565:
        case BGR_565:
        case ARGB_1555:
            bypp = 2;
            break;

        default:
            return -EINVAL;
    }

    if (stride == 0) /* Check source stride. */
    {
        stride = width * bypp;
    }
    else if (stride < width * bypp) /* Source has stride. */
    {
        return -EINVAL;
    }

    /* Compute number of bytes per dstride in bitmap file: align by 4. */
    dstride = ((width * bypp) + 3) & ~3;

    /* Build file header. */
    file_header.bfType       	        = _little16(0x4D42);
    file_header.bfSize                  = _little32(  sizeof (bitmapFileHeader) + sizeof (bitmapInfoHeader) + dstride * height);
    file_header.bfReserved1        = _little32(0);
    file_header.bfReserved2        = _little32(0);
    file_header.bfOffBits              = _little32( sizeof (bitmapFileHeader) + sizeof (bitmapInfoHeader));

    /* Build info_header. */
    memset(&info_header, 0, sizeof (bitmapInfoHeader));
    info_header.biSize                = _little32(sizeof (bitmapInfoHeader));
    info_header.biWidth              = _little32(width);
    info_header.biHeight             = _little32(height);
    info_header.biPlanes             = _little16(1);
    info_header.biBitCount          = _little16(bypp * 8);
    info_header.biCompression   = _little32(BI_RGB);
    info_header.biSizeImage       = _little32(dstride * height);

    fp = open(filename, O_WRONLY | O_CREAT | O_TRUNC , 777);
    if (fp < 0)
    {
    	printf("file[%s] open err\n",filename);
        return -EACCES;
    }

    if (write(fp, &file_header, sizeof (bitmapFileHeader)) != sizeof (bitmapFileHeader))
    {
        return -EACCES;
    }

    if (write(fp, &info_header, sizeof (bitmapInfoHeader)) != sizeof (bitmapInfoHeader))
    {
        return -EACCES;
    }

    /* Malloc memory for single dstride. */
    buff = (unsigned char*) malloc(dstride);
    if (buff == NULL)
    {
        return -ENOMEM;
    }

    /* Go to last line.  Bitmap is bottom-top, our date is top-bottom. */
    line = (const unsigned char*) data + stride * (height - 1);


    for (i = 0; i < height; i++)
    {
        /* Process each line. */
        switch (format)
        {
            case RGBA_8888:
                /* Swap RB to BGRA 8888. */
                _fconv(buff, BGRA_8888, line, RGBA_8888, width);
                break;

            case BGRA_8888:
                /* No conversion BGRA 8888. */
                memcpy(buff, line, width * 4);
                break;

            case RGBX_8888:
                /* Swap RB and skip A to BGR 888. */
                _fconv(buff, BGR_888, line, RGBX_8888, width);
                break;

            case BGRX_8888:
                /* Skip A to BGR 888. */
                _fconv(buff, BGR_888, line, BGRX_8888, width);
                break;

            case RGB_888:
                /* Swap RB to BGR 888. */
                _fconv(buff, BGR_888, line, RGB_888, width);
                break;

            case BGR_888:
                /* No conversion: BGR 888. */
                _fconv(buff, BGR_888, line, BGR_888, width);
                break;

            case RGB_565:
                /* Convert to BGR 888. */
                _fconv(buff, BGR_888, line, RGB_565, width);
                break;

            case BGR_565:
                /* Convert to BGR 888. */
                _fconv(buff, BGR_888, line, BGR_565, width);
                break;

            case ARGB_1555:
                /* No conversion: ARGB 15555. */
                memcpy(buff, line, width * 2);
                break;
        }

        /* Write a line. */
        if (write(fp, buff, dstride) != dstride)
        {
            free(buff);
            close(fp);
            return -EACCES;
        }

        line -= stride;         /* Go to next source line. */
    }

    free(buff);
    close(fp);
    return 0;
}
#endif
