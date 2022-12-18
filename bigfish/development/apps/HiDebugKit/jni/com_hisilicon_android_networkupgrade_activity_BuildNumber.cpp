#include "com_hisilicon_android_networkupgrade_activity_BuildNumber.h"

#define LOG_TAG "BuildNumber"

#include <utils/Log.h>
#include <jni.h>
#include <JNIHelp.h>

#include "get_sdk_version.h"

using namespace android;

jstring StrToJstring(JNIEnv* env, const char* pat)
{
    jclass strClass = env->FindClass("Ljava/lang/String;");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

JNIEXPORT jstring JNICALL Java_com_hisilicon_android_networkupgrade_activity_BuildNumber_GetSDKVersion(JNIEnv *env, jclass clazz)
{
    ALOGE("Java_com_hisilicon_android_networkupgrade_activity_BuildNumber_GetSDKVersion\n");
    char str[80];
    HisiGetSDKVersion(str);
    return NULL;//strToJstring(env,str);
}
