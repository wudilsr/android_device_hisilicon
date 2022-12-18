#ifndef __HI_DRM_UTIL_H__
#define __HI_DRM_UTIL_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"  {
#endif
#endif

int HI_DRM_UtilInit();
int HI_DRM_UtilCA2TA(const unsigned char* inputaddr, unsigned int TAAddr,int len);
int HI_DRM_UtilDeInit();
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
