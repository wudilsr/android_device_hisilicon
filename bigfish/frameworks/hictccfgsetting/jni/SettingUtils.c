#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "Setting.h"
JNIEnv* jniEnv;
jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setIpMode(JNIEnv* env, jobject thiz,jint flag){
    jint ret = -1;
    if(jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setIpMode(flag);
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_getIpMode(JNIEnv* env, jobject thiz){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getIpMode();
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setAudioMode(JNIEnv* env, jobject thiz,jint index){
    jint ret = -1;
    if(jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setAudioMode(index);
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_getAudioMode(JNIEnv* env, jobject thiz){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getAudioMode();
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_getSaveMode(JNIEnv* env, jobject thiz){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getSaveMode();
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setOutputFormat(JNIEnv* env, jobject thiz,jint flag){
    jint ret = -1;
    if(jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setOutputFormat(flag);
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_getOutputFormat(JNIEnv* env, jobject thiz){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getOutputFormat();
    return ret;
}
jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setPosition(JNIEnv* env, jobject thiz,jint l,jint t,jint w,jint h,jint mode){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setPosition(l,t,w,h,mode);
    return ret;
}

jintArray Java_com_SyMedia_SyIptv_Utils_SettingUtils_getPosition(JNIEnv* env, jobject thiz){
    jintArray ret = NULL;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getPosition();
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_restoreFactorySettings(JNIEnv* env, jobject thiz){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = restoreFactorySettings();
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setDate(JNIEnv* env, jobject thiz,jint year,jint month,jint day){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setDate(year,month,day);
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setTime(JNIEnv* env, jobject thiz,jint hourOfDay,jint minute){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setTime(hourOfDay,minute);
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setTimeFormat(JNIEnv* env, jobject thiz,jint timeFormat){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setTimeFormat(timeFormat);
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_getTimeFormat(JNIEnv* env, jobject thiz){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getTimeFormat();
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setDateFormat(JNIEnv* env, jobject thiz,jstring dateFormat){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setDateFormat(dateFormat);
    return ret;
}

jstring Java_com_SyMedia_SyIptv_Utils_SettingUtils_getDateFormat(JNIEnv* env, jobject thiz){
    jstring ret = NULL;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getDateFormat();
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setAutotime(JNIEnv* env, jobject thiz,jint Autotime){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setAutotime(Autotime);
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_getAutotime(JNIEnv* env, jobject thiz){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getAutotime();
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setAutoTimeZone(JNIEnv* env, jobject thiz,jint autoTimeZone){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setAutoTimeZone(autoTimeZone);
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_getAutoTimeZone(JNIEnv* env, jobject thiz){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getAutoTimeZone();
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setTimeZone(JNIEnv* env, jobject thiz,jstring timeZone){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setTimeZone(timeZone);
    return ret;
}

jstring Java_com_SyMedia_SyIptv_Utils_SettingUtils_getTimeZone(JNIEnv* env, jobject thiz){
    jstring str = NULL;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    str = getTimeZone();
    return str;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_setResolution(JNIEnv* env, jobject thiz,jint index){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = setResolution(index);
    return ret;
}

jint Java_com_SyMedia_SyIptv_Utils_SettingUtils_getResolution(JNIEnv* env, jobject thiz){
    jint ret = -1;
    if (jniEnv == NULL) {
        jniEnv = env;
    }
    ret = getResolution();
    return ret;
}
