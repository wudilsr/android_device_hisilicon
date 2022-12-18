/*
 * Copyright (C) 2011 xuyangpo/x54178
*/
#include "nativeWindow.h"
#include <stdlib.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/log.h>
#include <surfaceflinger/Surface.h>
#include <dlfcn.h>
#define TAG "AndroidNativeWindow"
#define ANDROID_V22_ANW_LOCK "_ZN7android7Surface4lockEPNS0_11SurfaceInfoEb"
#define ANDROID_V22_ANW_UNLOCK "_ZN7android7Surface13unlockAndPostEv"
#define ANDROID_V23_ANW_LOCK "ANativeWindow_lock"
#define ANDROID_V23_ANW_UNLOCK "ANativeWindow_unlockAndPost"
#define ANDROID_V23_ANW_RELEASE "ANativeWindow_release"
#define ANDROID_V23_ANW_GET "ANativeWindow_fromSurface"
#define ANDROID_V23_ANW_SETBUFFERSGEOMETRY "ANativeWindow_setBuffersGeometry"
using namespace android;
static void* AndroidNativeWindow_register23(void* pHandle,JNIEnv* env, jobject jsurface);
static int AndroidNativeWindow_getPixels23(void* pHandle,int width, int height, void** pixels,int format);
static int AndroidNativeWindow_update23(void* pHandle,void* pPixels,int width,int height,int format);
static int AndroidNativeWindow_unregister23(void* pHandle);
static void* AndroidNativeWindow_register22(void* pHandle,JNIEnv* env, jobject jsurface);
static int AndroidNativeWindow_getPixels22(void* pHandle,int width, int height, void** pixels,int format);
static int AndroidNativeWindow_update22(void* pHandle,void* pPixels,int width,int height,int format);
static int AndroidNativeWindow_unregister22(void* pHandle);
//////////////////////////////////////////////////////////////////////////////////////////
//开始函数定义
//////////////////////////////////////////////////////////////////////////////////////////
static inline void *LoadLibrary22(const char *psz_lib,ANWindow* pANWindow)
{
    void *p_library = dlopen(psz_lib, RTLD_NOW);
    if (p_library)
    {
        pANWindow->pf_lock = (PF_ANWindow_lock*)(dlsym(p_library, ANDROID_V22_ANW_LOCK));
        pANWindow->pf_unlockAndPost = (PF_ANWindow_unlockAndPost*)(dlsym(p_library, ANDROID_V22_ANW_UNLOCK));
        if (pANWindow->pf_lock && pANWindow->pf_unlockAndPost)
        {
            return p_library;
        }
    }
    return NULL;
}
static inline void *LoadLibrary23(const char *psz_lib,ANWindow* pANWindow)
{
    void *p_library = dlopen(psz_lib, RTLD_NOW);
    if (p_library)
    {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "dlopen libandroid.so success");
        pANWindow->pf_lock = (PF_ANWindow_lock*)(dlsym(p_library, ANDROID_V23_ANW_LOCK));
        pANWindow->pf_unlockAndPost = (PF_ANWindow_unlockAndPost*)(dlsym(p_library, ANDROID_V23_ANW_UNLOCK));
        pANWindow->pf_release = (PF_ANWindow_release*)(dlsym(p_library, ANDROID_V23_ANW_RELEASE));
        pANWindow->pf_get = (PF_ANWindow_get*)(dlsym(p_library, ANDROID_V23_ANW_GET));
        pANWindow->pf_setBuffersGeometry= (PF_ANWindow_setBuffersGeometry*)(dlsym(p_library, ANDROID_V23_ANW_SETBUFFERSGEOMETRY));

        if (pANWindow->pf_lock && pANWindow->pf_unlockAndPost
            &&pANWindow->pf_release&&pANWindow->pf_get
            &&pANWindow->pf_setBuffersGeometry)
        {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "dlsym success");
            return p_library;
        }
    }
    return NULL;
}
void* AndroidNativeWindow_register(JNIEnv* env, jobject jsurface,int apiVersion,
    PF_ANWindow_setBuffersGeometry* pf_setBuffersGeometry,void* pPlayer)
{
    ANWindow* pANWindow = (ANWindow*)malloc(sizeof(ANWindow));
    if(!pANWindow)
    {
        return NULL;
    }
    memset(pANWindow,0,sizeof(ANWindow));
    pANWindow->mAndroidAPIVersion = apiVersion;
    if(pANWindow->mAndroidAPIVersion < 9)
    {
        pANWindow->pf_register = AndroidNativeWindow_register22;
        pANWindow->pf_getPixels= AndroidNativeWindow_getPixels22;
        pANWindow->pf_update= AndroidNativeWindow_update22;
        pANWindow->pf_unregister = AndroidNativeWindow_unregister22;
        assert(pf_setBuffersGeometry!=NULL);
        assert(pPlayer!=NULL);
        pANWindow->pf_setBuffersGeometry = pf_setBuffersGeometry;
        pANWindow->pPlayer = pPlayer;
        if((pANWindow->pLibHandle = LoadLibrary22("libsurfaceflinger_client.so", pANWindow)) == NULL)
        {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "AndroidNativeWindow_register load libsurfaceflinger_client.so failed");
            if((pANWindow->pLibHandle = LoadLibrary22("libui.so", pANWindow)) == NULL)
            {
                __android_log_print(ANDROID_LOG_ERROR, TAG, "AndroidNativeWindow_register load libui.so failed");
                return NULL;
            }
        }
    }
    else
    {
        pANWindow->pf_register = AndroidNativeWindow_register23;
        pANWindow->pf_getPixels= AndroidNativeWindow_getPixels23;
        pANWindow->pf_update= AndroidNativeWindow_update23;
        pANWindow->pf_unregister = AndroidNativeWindow_unregister23;
        __android_log_print(ANDROID_LOG_ERROR, TAG, "LoadLibrary23 libandroid.so start");
        if((pANWindow->pLibHandle =LoadLibrary23("libandroid.so", pANWindow)) == NULL)
        {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "AndroidNativeWindow_register load libandroid.so failed");
             return NULL;
        }
    }
    pANWindow->pWindow = pANWindow->pf_register(pANWindow,env,jsurface);
    return pANWindow;
}

int AndroidNativeWindow_getPixels(void* pHandle,int width, int height, void** pixels,int format)
{
    ANWindow* pANWindow = (ANWindow*)pHandle;
    return pANWindow->pf_getPixels(pHandle,width,height,pixels,format);
}

int AndroidNativeWindow_update(void* pHandle,void* pPixels,int width,int height,int format)
{
    ANWindow* pANWindow = (ANWindow*)pHandle;
    return pANWindow->pf_update(pHandle,pPixels,width,height,format);
}

int AndroidNativeWindow_unregister(void* pHandle)
{
    ANWindow* pANWindow = (ANWindow*)pHandle;
    return pANWindow->pf_unregister(pHandle);
}

static void* AndroidNativeWindow_register23(void* pHandle,JNIEnv* env, jobject jsurface)
{
    ANWindow* pANWindow = (ANWindow*)pHandle;
    void* pWindow = pANWindow->pf_get(env, jsurface);
    return pWindow;
}

static int AndroidNativeWindow_getPixels23(void* pHandle,int width, int height, void** pixels,int format)
{
    ANWindow* pANWindow = (ANWindow*)pHandle;
    pANWindow->mWindowWidth = width/32*32;
    pANWindow->mWindowHeight = height;
    pANWindow->mVideoWidth = width;
    pANWindow->mVideoHeight = height;
    pANWindow->mPixelFormat = format;
    int ret = pANWindow->pf_setBuffersGeometry((ANativeWindow*)(pANWindow->pWindow),
        pANWindow->mWindowWidth, pANWindow->mWindowHeight, pANWindow->mPixelFormat);
    if(ret < 0)
    {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "AndroidNativeWindow_getPixels23 failed");
        return ret;
    }
    else
    {
        if(format == WINDOW_FORMAT_RGBA_8888)
        {
            *pixels = malloc(width*height*4);
            pANWindow->mBytesPerPixels = 4;
            pANWindow->pPixelCache = *pixels;
        }
        else if(format == WINDOW_FORMAT_RGB_565)
        {
            *pixels = malloc(width*height*2);
            pANWindow->mBytesPerPixels = 2;
            pANWindow->pPixelCache = *pixels;
        }
        pANWindow->mWindowLineSize = pANWindow->mWindowWidth*pANWindow->mBytesPerPixels;
        pANWindow->mVideoLineSize = pANWindow->mVideoWidth*pANWindow->mBytesPerPixels;
        if(*pixels)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
}
static int AndroidNativeWindow_update23(void* pHandle,void* pPixels,int width,int height,int format)
{
    ANWindow* pANWindow = (ANWindow*)pHandle;
    ANativeWindow_Buffer buffer;
//    __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_lock start");
         if(pANWindow->pf_lock((pANWindow->pWindow), &buffer, NULL) < 0)
         {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_lock failed");
             return -1;
        }
        int i = 0;
        char* pSrc = (char*)pPixels;
        char* pDst = (char*)(buffer.bits);
/*    while((buffer.width != pANWindow->mWindowWidth) ||(buffer.height != pANWindow->mWindowHeight))
    {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Warning ANativeWindow fill Mismatch, pf_setBuffersGeometry");
        int ret = pANWindow->pf_setBuffersGeometry((ANativeWindow*)(pANWindow->pWindow),
        pANWindow->mWindowWidth, pANWindow->mWindowHeight, pANWindow->mPixelFormat);
        if((buffer.width != pANWindow->mWindowWidth) ||(buffer.height != pANWindow->mWindowHeight))
        {
            __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_setBuffersGeometry failed");
            int ret = pANWindow->pf_unlockAndPost(pANWindow->pWindow);
            return ret;
        }
    }*/
    {
#if PERFORMANCETEST
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow fill:%d,%d,%d,%d",
        buffer.width,buffer.height,buffer.stride,buffer.format);
#endif
            if(pANWindow->mWindowLineSize == pANWindow->mVideoLineSize)
            {
                memcpy(pDst,pSrc,pANWindow->mWindowLineSize*height);
            }
            else
            {
                for(i = 0;i<height;i++)
                {
                    memcpy(pDst,pSrc,pANWindow->mWindowLineSize);
                    pDst += pANWindow->mWindowLineSize;
                    pSrc += pANWindow->mVideoLineSize;
                }
        }
    }
#if PERFORMANCETEST
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_unlockAndPost start");
#endif
    int ret = pANWindow->pf_unlockAndPost(pANWindow->pWindow);
    if(ret < 0)
    {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_unlockAndPost Failed");
    }
#if PERFORMANCETEST
    __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_unlockAndPost End");
#endif
        return ret;
}
static int AndroidNativeWindow_unregister23(void* pHandle)
{
    __android_log_print(ANDROID_LOG_ERROR, TAG, "AndroidNativeWindow_unregister start");
    ANWindow* pANWindow = (ANWindow*)pHandle;
    pANWindow->pf_release(pANWindow->pWindow);
    if(pANWindow->pLibHandle)
    {
        dlclose(pANWindow->pLibHandle);
    }
    free(pANWindow);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "AndroidNativeWindow_unregister end");
    return 0;
}

static void* AndroidNativeWindow_register22(void* pHandle,JNIEnv* env, jobject jsurface)
{
    jclass clazz = env->FindClass("android/view/Surface");
    jfieldID field_surface = env->GetFieldID(clazz, "mSurface", "I");
    if(field_surface == NULL) {
        return NULL;
    }
    return (void*)env->GetIntField(jsurface, field_surface);
}

static int AndroidNativeWindow_getPixels22(void* pHandle,int width, int height, void** pixels,int format)
{
    ANWindow* pANWindow = (ANWindow*)pHandle;
    pANWindow->mWindowWidth = width/32*32;
    pANWindow->mWindowHeight = height;
    pANWindow->mVideoWidth = width;
    pANWindow->mVideoHeight = height;
    pANWindow->mPixelFormat = format;
    /*int ret = pANWindow->pf_setBuffersGeometry(pANWindow->pPlayer,
        pANWindow->mWindowWidth, pANWindow->mWindowHeight, pANWindow->mPixelFormat);
    if(ret < 0)
    {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "AndroidNativeWindow_getPixels22 failed");
        return ret;
    }
    else*/
    {
        if(format == WINDOW_FORMAT_RGBA_8888)
        {
            *pixels = malloc(width*height*4);
            pANWindow->mBytesPerPixels = 4;
            pANWindow->pPixelCache = *pixels;
        }
        else if(format == WINDOW_FORMAT_RGB_565)
        {
            *pixels = malloc(width*height*2);
            pANWindow->mBytesPerPixels = 2;
            pANWindow->pPixelCache = *pixels;
        }
        pANWindow->mWindowLineSize = pANWindow->mWindowWidth*pANWindow->mBytesPerPixels;
        pANWindow->mVideoLineSize = pANWindow->mVideoWidth*pANWindow->mBytesPerPixels;
        if(*pixels)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
}
static int AndroidNativeWindow_update22(void* pHandle,void* pPixels,int width,int height,int format)
{
    ANWindow* pANWindow = (ANWindow*)pHandle;
    Surface* pSurface = (Surface*)pANWindow->pWindow;
    Surface::SurfaceInfo surfaceInfo;
    int bASR = 0;
//    __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_lock start");
         if (pANWindow->pf_lock(pANWindow->pWindow,&surfaceInfo,1) < 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_lock Failed");
        return -1;
    }
        int i = 0;
        char* pSrc = (char*)pPixels;
        char* pDst = (char*)(surfaceInfo.bits);
//    __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow fill:%d,%d,%d,%d",
//    surfaceInfo.w,surfaceInfo.h,surfaceInfo.s,surfaceInfo.format);
    if((surfaceInfo.w != pANWindow->mWindowWidth) ||(surfaceInfo.h != pANWindow->mWindowHeight))
    {
//        __android_log_print(ANDROID_LOG_ERROR, TAG, "Warning ANativeWindow fill Mismatch, pf_setBuffersGeometry");
        int ret = pANWindow->pf_setBuffersGeometry(pANWindow->pPlayer,
        pANWindow->mWindowWidth, pANWindow->mWindowHeight, pANWindow->mPixelFormat);
        if((surfaceInfo.w != pANWindow->mWindowWidth) ||(surfaceInfo.h != pANWindow->mWindowHeight))
        {
//            __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_setBuffersGeometry failed");
            int ret = pANWindow->pf_unlockAndPost(pANWindow->pWindow);
            return ret;
        }
        bASR = 1;
    }
    {
        if(pANWindow->mWindowLineSize == pANWindow->mVideoLineSize)
        {
            memcpy(pDst,pSrc,pANWindow->mWindowLineSize*height);
        }
        else
        {
//            __android_log_print(ANDROID_LOG_ERROR, TAG, "mWindowLineSize  : %d !=  mVideoLineSize : %d",
//                        pANWindow->mWindowLineSize,pANWindow->mVideoLineSize);
            for(i = 0;i<height;i++)
            {
                memcpy(pDst,pSrc,pANWindow->mWindowLineSize);
                pDst += pANWindow->mWindowLineSize;
                pSrc += pANWindow->mVideoLineSize;
            }
        }
    }
//    __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_unlockAndPost start");
    int ret = pANWindow->pf_unlockAndPost(pANWindow->pWindow);
    if(ret < 0)
    {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_unlockAndPost Failed");
    }
//    __android_log_print(ANDROID_LOG_ERROR, TAG, "ANativeWindow_unlockAndPost End");
    if(bASR)
    {
        usleep(3000000);
    }
        return ret;
}
static int AndroidNativeWindow_unregister22(void* pHandle)
{
    ANWindow* pANWindow = (ANWindow*)pHandle;
    if(pANWindow->pLibHandle)
    {
        dlclose(pANWindow->pLibHandle);
    }
    __android_log_print(ANDROID_LOG_ERROR, TAG, "AndroidNativeWindow_unregister start");
    free(pANWindow);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "AndroidNativeWindow_unregister end");
    return 0;
}
