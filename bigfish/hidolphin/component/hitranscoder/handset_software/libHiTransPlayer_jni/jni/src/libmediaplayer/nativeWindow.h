#ifndef __NATIVE_WINDOW__
#define __NATIVE_WINDOW__
/*
 * Copyright (C) 2011 xuyangpo/x54178
*/
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <jni.h>
typedef void* PF_ANWindow_register(void* pHandle,JNIEnv* env, jobject jsurface);

typedef int PF_ANWindow_getPixels(void* pHandle,int width, int height, void** pixels,int format);

typedef int PF_ANWindow_update(void* pHandle,void* pPixels,int width,int height,int format);

typedef int PF_ANWindow_unregister(void* pHandle);
// _ZN7android7Surface4lockEPNS0_11SurfaceInfoEb
typedef int PF_ANWindow_lock(void *, void *, int);
// _ZN7android7Surface13unlockAndPostEv
typedef int PF_ANWindow_unlockAndPost(void *);
typedef int PF_ANWindow_release(void *);
typedef int PF_ANWindow_setBuffersGeometry(void* pHandle, int width, int height, int format);
typedef void* PF_ANWindow_get(JNIEnv* env, jobject surface);
typedef struct __AndroidNativeWindow
{
    void* pWindow;
    void* pPixelCache;
    int mVideoWidth;
    int mVideoHeight;
    int mPixelFormat;
    int mBytesPerPixels;
    int mWindowWidth;
    int mWindowHeight;
    int mVideoLineSize;
    int mWindowLineSize;
    int mAndroidAPIVersion;//<9的是2.3以下的操作系统，>9的是2.3及以后的操作系统
    PF_ANWindow_register* pf_register;
    PF_ANWindow_getPixels* pf_getPixels;
    PF_ANWindow_update* pf_update;
    PF_ANWindow_unregister* pf_unregister;
    PF_ANWindow_lock* pf_lock;
    PF_ANWindow_unlockAndPost* pf_unlockAndPost;
    PF_ANWindow_release* pf_release;
    PF_ANWindow_get* pf_get;
    PF_ANWindow_setBuffersGeometry* pf_setBuffersGeometry;
    void* pLibHandle;
    void* pPlayer;
}ANWindow;
void* AndroidNativeWindow_register(JNIEnv* env, jobject jsurface,int apiVersion,PF_ANWindow_setBuffersGeometry* pf_setBuffersGeometry,void* pPlayer);

int AndroidNativeWindow_getPixels(void* pHandle,int width, int height, void** pixels,int format);

int AndroidNativeWindow_update(void* pHandle,void* pPixels,int width,int height,int format);

int AndroidNativeWindow_unregister(void* pHandle);

#ifdef __cplusplus
}
#endif
#endif