#ifndef __YUV2RGB_NEON__
#define __YUV2RGB_NEON__
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
void __attribute((noinline)) yv12_to_rgb565_neon(uint16_t *dst, const uint8_t *y, const uint8_t *u, const uint8_t *v, int n, int oddflag);
void *memcpy_neon(void *dest, void *src, unsigned int count);
void *memset_neon(void *s,int c,size_t n);
void yuv422_2_rgba_neon(uint8_t *dst_ptr,
                               const uint8_t *y_ptr,
                               const uint8_t *u_ptr,
                               const uint8_t *v_ptr,
                               int      width,
                               int      height,
                               int y_pitch,
                               int uv_pitch,
                               int rgb_pitch);

    void yuv420_2_rgba_neon(uint8_t *dst_ptr,
                               const uint8_t *y_ptr,
                               const uint8_t *u_ptr,
                               const uint8_t *v_ptr,
                               int      width,
                               int      height,
                               int y_pitch,
                               int uv_pitch,
                               int rgb_pitch);
#ifdef __cplusplus
}
#endif
#endif
