#ifndef __QCOM_COLORCVT__
#define __QCOM_COLORCVT__
#ifdef __cplusplus

void convertNV12Tile(size_t width, size_t height, const void *srcBits, size_t srcSkip, void *dstBits, size_t dstSkip);
void cvtNV12BlockLine2YV12BlockLine(uint8_t* u_dst,uint8_t* v_dst,const uint8_t* src,int blockWidth_half) ;
#endif
#endif
