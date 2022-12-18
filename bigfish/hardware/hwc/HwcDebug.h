#ifndef HWC_DEBUG_H
#define HWC_DEBUG_H
//#define HWC_DEBUG

enum
{
    /* Bytes: 0 1 2 3 (Low to high)*/
    RGBA_8888 = 306,  /*        R G B A */
    BGRA_8888 = 212,  /*        B G R A */
    RGBX_8888 = 305,  /*        R G B - */
    BGRX_8888 = 211,      /*        B G R - */

    /* Bytes: 0 1 2 (Low to high) */
    RGB_888   = 303,  /*        R G B */
    BGR_888   = 210,  /*        B G R */

    /* Bits: 15 11 5  0 (MSB to LSB) */
    RGB_565   = 209,  /*         R  G  B */
    BGR_565   = 302,  /*         B  G  R */

    /* Bits: 15 14 10 5  0 (MSB to LSB) */
    ARGB_1555 = 208   /*        A   R  G  B */
};

int format2dumpformat(int format);
int _WriteBitmap( const char* filename,  const void* data,  unsigned int width, unsigned int height,  unsigned int stride, int format);


#endif //HWC_DEBUG_H

