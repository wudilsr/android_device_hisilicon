#define LOG_NDEBUG 0

#include "utils/Log.h"

#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <utils/threads.h>
#include <cutils/properties.h>
#include "jni.h"
#include <utils/Log.h>
#include "JNIHelp.h"
#include "HiAoServiceClient.h"
#include <android_runtime/AndroidRuntime.h>
#include "utils/Errors.h"  // for status_t
#include "utils/KeyedVector.h"
#include "utils/String8.h"
#include <binder/Parcel.h>

// ----------------------------------------------------------------------------

using namespace android;

// ----------------------------------------------------------------------------
struct fields_t {
    jfieldID    context;
};
static fields_t fields;
/*
*port: 1: HDMI  2:SPDIF
*mode: 0: close 1:lpcm 2: 5.1 3: 7.1
*return: 0: failed  1:success
*/
static jint com_hisilicon_android_hiaoservice_setAudioOutput(JNIEnv *env, jobject clazz, jint port, jint mode)
{
    sp<IBinder> binder = defaultServiceManager()->getService(String16("hiaoservice"));
    sp<IHiAoService> service = interface_cast<IHiAoService>(binder);
    if (service.get() == NULL) {
        ALOGE("Cannot connect to the HiAoService.");
        return -1;
    }
  ALOGI("jni set port");
    return service->setUnfAudioPort(port,mode);
}
/*
* input : port
* return : mode
*/
static jint com_hisilicon_android_hiaoservice_getAudioOutput(JNIEnv *env, jobject clazz, jint port)
{
    sp<IBinder> binder = defaultServiceManager()->getService(String16("hiaoservice"));
    sp<IHiAoService> service = interface_cast<IHiAoService>(binder);
    if (service.get() == NULL) {
        ALOGE("Cannot connect to the AOService.");
        return -1;
    }
    return service->getUnfAudioPort(port);
}

static jint com_hisilicon_android_hiaoservice_setBluerayHbr(JNIEnv *env, jobject clazz, jint mode)
{
    sp<IBinder> binder = defaultServiceManager()->getService(String16("hiaoservice"));
    sp<IHiAoService> service = interface_cast<IHiAoService>(binder);
    if (service.get() == NULL) {
       ALOGE("Cannot connect to the AOService.");
    return -1;
    }
    return service->setBluerayHbr(mode);
}

static jint com_hisilicon_android_hiaoservice_setEnterSmartSuspend(JNIEnv *env, jobject clazz, jint status)
{
    sp<IBinder> binder = defaultServiceManager()->getService(String16("hiaoservice"));
    sp<IHiAoService> service = interface_cast<IHiAoService>(binder);
    if (service.get() == NULL) {
       ALOGE("Cannot connect to the AOService.");
    return -1;
    }
    return service->setEnterSmartSuspend(status);
}


static JNINativeMethod gMethods[] = {
    {"setAudioOutput", "(II)I", (void *)com_hisilicon_android_hiaoservice_setAudioOutput},
    {"getAudioOutput", "(I)I", (void *)com_hisilicon_android_hiaoservice_getAudioOutput},
    {"setBluerayHbr", "(I)I", (void *)com_hisilicon_android_hiaoservice_setBluerayHbr},
    {"setEnterSmartSuspend", "(I)I", (void *)com_hisilicon_android_hiaoservice_setEnterSmartSuspend},
};

static int register_com_hisilicon_android_hiaoservice(JNIEnv *env)
{
    return AndroidRuntime::registerNativeMethods(env, "com/hisilicon/android/HiAoService", gMethods, NELEM(gMethods));
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

    ALOGD("JNI_OnLoad");
  if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
      ALOGE("ERROR: GetEnv failed\n");
      return result;
  }

  if(register_com_hisilicon_android_hiaoservice(env) < 0) {
    ALOGE("ERROR: aoservice native registration failed\n");
    return result;
  }

  /* success -- return valid version number */
  result = JNI_VERSION_1_4;
  ALOGD("return");
  return result;
}
