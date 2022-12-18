#define LOG_NDEBUG 0
#define LOG_TAG "HiBDInfo"

#include <utils/Log.h>
#include <utils/Errors.h>
#include <sys/times.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <binder/Parcel.h>
#include "android_os_Parcel.h"
#include "android_util_Binder.h"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"
#include "bluray.h"
#include "HiBDInfo.h"
#include "HiBDInvoke.h"

#define LOGE ALOGE
#define LOGV ALOGV
#define LOGW ALOGW
#define LOGI ALOGI
#define LOGD ALOGD

using namespace android;

struct fields_t {
    jclass      javaHiBDInfo_BDCommand;
    jfieldID    BD_CMD_OPEN_BLURAY_INJAVA;
    jfieldID    BD_CMD_CLOSE_BLURAY_INJAVA;
    jfieldID    BD_CMD_CHECK_DISC_INFO_INJAVA;
    jfieldID    BD_CMD_GET_TITLE_NUMBER_INJAVA;
    jfieldID    BD_CMD_GET_CHAPTER_NUMBER_INJAVA;
    jfieldID    BD_CMD_GET_PLAYLIST_INJAVA;
    jfieldID    BD_CMD_GET_DEFAULT_PLAYLIST_INJAVA;
    jfieldID    BD_CMD_GET_CHAPTER_POSITION_INJAVA;
    jfieldID    BD_CMD_GET_DEFAULT_TITLE_INJAVA;
    jfieldID    BD_CMD_GET_TITLE_INJAVA;
    jfieldID    BD_CMD_GET_SUBTITLE_LANGUAGE_INJAVA;
    jfieldID    BD_CMD_GET_AUDIO_TRACK_LANGUAGE_INJAVA;
    jfieldID    BD_CMD_GET_CUR_CHAPTER_INJAVA;
    jfieldID    BD_CMD_GET_DURATION_INJAVA;
    jfieldID    BD_CMD_CHECK_3D_INJAVA;
    jfieldID    BD_CMD_GET_POSTER_INJAVA;
};

static const char * kClassPathName = "com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand";
static fields_t javaHiBDInfoFields;
static HiBDInfo sHiBDInfo;

static jint
com_hisilicon_hibdplayer_invoke(JNIEnv *env, jobject thiz, jobject java_request, jobject java_reply)
{
    Parcel * request = parcelForJavaObject(env, java_request);
    Parcel * reply = parcelForJavaObject(env, java_reply);

    return sHiBDInfo.invoke(*request, reply);
}

static JNINativeMethod gMethods[] = {
    {"native_invoke",       "(Landroid/os/Parcel;Landroid/os/Parcel;)I", (void *)com_hisilicon_hibdplayer_invoke},
};

static int
register_com_hisilicon_hibdplayer_HiBDInfo(JNIEnv *env) {
    javaHiBDInfoFields.javaHiBDInfo_BDCommand = env->FindClass(kClassPathName);

    if (javaHiBDInfoFields.javaHiBDInfo_BDCommand == NULL)
    {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand");
        return -1;
    }

    javaHiBDInfoFields.BD_CMD_OPEN_BLURAY_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_OPEN_BLURAY", "I");
    if (javaHiBDInfoFields.BD_CMD_OPEN_BLURAY_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_OPEN_BLURAY");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_OPEN_BLURAY_INJAVA, BD_CMD_OPEN_BLURAY);

    javaHiBDInfoFields.BD_CMD_CLOSE_BLURAY_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_CLOSE_BLURAY", "I");
    if (javaHiBDInfoFields.BD_CMD_CLOSE_BLURAY_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_CLOSE_BLURAY");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_CLOSE_BLURAY_INJAVA, BD_CMD_CLOSE_BLURAY);

    javaHiBDInfoFields.BD_CMD_CHECK_DISC_INFO_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_CHECK_DISC_INFO", "I");
    if (javaHiBDInfoFields.BD_CMD_CHECK_DISC_INFO_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_CHECK_DISC_INFO");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_CHECK_DISC_INFO_INJAVA, BD_CMD_CHECK_DISC_INFO);

    javaHiBDInfoFields.BD_CMD_GET_TITLE_NUMBER_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_TITLE_NUMBER", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_TITLE_NUMBER_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_TITLE_NUMBER");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_TITLE_NUMBER_INJAVA, BD_CMD_GET_TITLE_NUMBER);

    javaHiBDInfoFields.BD_CMD_GET_CHAPTER_NUMBER_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_CHAPTER_NUMBER", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_CHAPTER_NUMBER_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_CHAPTER_NUMBER");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_CHAPTER_NUMBER_INJAVA, BD_CMD_GET_CHAPTER_NUMBER);

    javaHiBDInfoFields.BD_CMD_GET_PLAYLIST_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_PLAYLIST", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_PLAYLIST_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_PLAYLIST");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_PLAYLIST_INJAVA, BD_CMD_GET_PLAYLIST);

    javaHiBDInfoFields.BD_CMD_GET_DEFAULT_PLAYLIST_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_DEFAULT_PLAYLIST", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_DEFAULT_PLAYLIST_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_DEFAULT_PLAYLIST");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_DEFAULT_PLAYLIST_INJAVA, BD_CMD_GET_DEFAULT_PLAYLIST);

    javaHiBDInfoFields.BD_CMD_GET_CHAPTER_POSITION_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_CHAPTER_POSITION", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_CHAPTER_POSITION_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_CHAPTER_POSITION");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_CHAPTER_POSITION_INJAVA, BD_CMD_GET_CHAPTER_POSITION);

    javaHiBDInfoFields.BD_CMD_GET_DEFAULT_TITLE_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_DEFAULT_TITLE", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_DEFAULT_TITLE_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_DEFAULT_TITLE");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_DEFAULT_TITLE_INJAVA, BD_CMD_GET_DEFAULT_TITLE);

    javaHiBDInfoFields.BD_CMD_GET_TITLE_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_TITLE", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_TITLE_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_TITLE");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_TITLE_INJAVA, BD_CMD_GET_TITLE);

    javaHiBDInfoFields.BD_CMD_GET_SUBTITLE_LANGUAGE_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_SUBTITLE_LANGUAGE", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_SUBTITLE_LANGUAGE_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_SUBTITLE_LANGUAGE");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_SUBTITLE_LANGUAGE_INJAVA, BD_CMD_GET_SUBTITLE_LANGUAGE);

    javaHiBDInfoFields.BD_CMD_GET_AUDIO_TRACK_LANGUAGE_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_AUDIO_TRACK_LANGUAGE", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_AUDIO_TRACK_LANGUAGE_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_AUDIO_TRACK_LANGUAGE");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_AUDIO_TRACK_LANGUAGE_INJAVA, BD_CMD_GET_AUDIO_TRACK_LANGUAGE);

    javaHiBDInfoFields.BD_CMD_GET_CUR_CHAPTER_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_CUR_CHAPTER", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_CUR_CHAPTER_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_CUR_CHAPTER");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_CUR_CHAPTER_INJAVA, BD_CMD_GET_CUR_CHAPTER);

    javaHiBDInfoFields.BD_CMD_GET_DURATION_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_DURATION", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_DURATION_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_DURATION");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_DURATION_INJAVA, BD_CMD_GET_DURATION);

    javaHiBDInfoFields.BD_CMD_CHECK_3D_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_CHECK_3D", "I");
    if (javaHiBDInfoFields.BD_CMD_CHECK_3D_INJAVA == NULL) {
	jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_CHECK_3D");
	return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_CHECK_3D_INJAVA, BD_CMD_CHECK_3D);

    javaHiBDInfoFields.BD_CMD_GET_POSTER_INJAVA = env->GetStaticFieldID(javaHiBDInfoFields.javaHiBDInfo_BDCommand, "BD_CMD_GET_POSTER", "I");
    if (javaHiBDInfoFields.BD_CMD_GET_POSTER_INJAVA == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/hisilicon/android/hibdinfo/HiBDInfo$BDCommand/BD_CMD_GET_POSTER");
        return -1;
    }
    env->SetStaticIntField(javaHiBDInfoFields.javaHiBDInfo_BDCommand, javaHiBDInfoFields.BD_CMD_GET_POSTER_INJAVA, BD_CMD_GET_POSTER);

    return AndroidRuntime::registerNativeMethods(env, "com/hisilicon/android/hibdinfo/HiBDInfo", gMethods, NELEM(gMethods));
}

jint
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;
    LOGE("begin load\n");

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        LOGE("ERROR: GetEnv failed\n");
        goto bail;
    }
    assert(env != NULL);

    if (register_com_hisilicon_hibdplayer_HiBDInfo(env) < 0) {
        LOGE("ERROR: HiBDInfo native registraction failed\n");
        goto bail;
    }
    result = JNI_VERSION_1_4;

bail:
    return result;
}
