#include "Setting.h"
#include <android/log.h>
extern JNIEnv* jniEnv;
jclass SettingJava = NULL;
jobject mSettingJava = NULL;
jmethodID m_setIpMode = NULL;
jmethodID m_getIpMode = NULL;
jmethodID m_setAudioMode = NULL;
jmethodID m_getAudioMode = NULL;
jmethodID m_getSaveMode = NULL;
jmethodID m_setOutputFormat = NULL;
jmethodID m_getOutputFormat = NULL;
jmethodID m_getPosition = NULL;
jmethodID m_setPosition = NULL;
jmethodID m_restoreFactorySettings = NULL;
jmethodID m_setDate = NULL;
jmethodID m_setTime = NULL;
jmethodID m_setTimeFormat = NULL;
jmethodID m_getTimeFormat = NULL;
jmethodID m_setDateFormat = NULL;
jmethodID m_getDateFormat = NULL;
jmethodID m_setAutotime = NULL;
jmethodID m_getAutotime = NULL;
jmethodID m_setAutoTimeZone = NULL;
jmethodID m_getAutoTimeZone = NULL;
jmethodID m_setTimeZone = NULL;
jmethodID m_getTimeZone = NULL;
jmethodID m_setResolution = NULL;
jmethodID m_getResolution = NULL;
jmethodID m_saveSetting = NULL;
jmethodID m_getSetting = NULL;
jmethodID construction_id = NULL;
int GetmSettingJavaJavaInstance(jclass obj_class);
void deleteRef(JNIEnv* env);

int InitCCallJava() {
    if(jniEnv == NULL) {
        return 0;
    }
    if(SettingJava == NULL) {
        SettingJava = (*jniEnv)->FindClass(jniEnv,"com/SyMedia/SyIptv/Utils/SettingProvide");
        if(SettingJava == NULL){
        return -1;
        }
    }
    if (mSettingJava == NULL) {
        if (GetmSettingJavaJavaInstance(SettingJava) != 1) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        return -1;
        }
    }
    return 1;

}

int GetmSettingJavaJavaInstance(jclass obj_class) {
    if(obj_class == NULL) {
        return 0;
    }
    if(construction_id==NULL){
        construction_id = (*jniEnv)->GetMethodID(jniEnv, obj_class,"<init>", "()V");
    }
    if (construction_id == 0) {
        return -1;
    }
    if(jniEnv==NULL||obj_class==NULL){
    }
    mSettingJava = (*jniEnv)->NewObject(jniEnv, obj_class,construction_id);
    if (mSettingJava == NULL) {
        return -2;
    }
    return 1;
}
int setIpMode(int flag) {
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setIpMode == NULL) {
        m_setIpMode = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setIpMode","(I)I");
        if (m_setIpMode == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setIpMode,flag);
    deleteRef(jniEnv);
    return ret;
}

int getIpMode() {
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_getIpMode == NULL) {
        m_getIpMode = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "getIpMode","()I");
        if (m_getIpMode == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_getIpMode);
    deleteRef(jniEnv);
    return ret;
}
int setAudioMode(int index){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setAudioMode == NULL) {
        m_setAudioMode = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setAudioMode","(I)I");
        if (m_setAudioMode == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setAudioMode,index);
    deleteRef(jniEnv);
    return ret;
}
int getAudioMode(){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_getAudioMode == NULL) {
        m_getAudioMode = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "getAudioMode","()I");
        if (m_getAudioMode == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_getAudioMode);
    deleteRef(jniEnv);
    return ret;
}
int getSaveMode(){
    int ret = -1;
    if(mSettingJava==NULL){
        int result = InitCCallJava();
        if(result != 1){
        return ret;
        }else{
        if(m_getSaveMode == NULL){
        m_getSaveMode = (*jniEnv)->GetMethodID(jniEnv,SettingJava,"getSaveMode","()I");
        if(m_getSaveMode == NULL){
        (*jniEnv)->DeleteLocalRef(jniEnv,SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_getSaveMode);
    deleteRef(jniEnv);
    return ret;
}
int setOutputFormat(int flag){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setOutputFormat == NULL) {
        m_setOutputFormat = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setOutputFormat","(I)I");
        if (m_setOutputFormat == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setOutputFormat,flag);
    deleteRef(jniEnv);
    return ret;
}
int getOutputFormat(){
    int ret = -1;
    if(mSettingJava==NULL){
        int result = InitCCallJava();
        if(result != 1){
        return ret;
        }else{
        if(m_getOutputFormat == NULL){
        m_getOutputFormat = (*jniEnv)->GetMethodID(jniEnv,SettingJava,"getOutputFormat","()I");
        if(m_getOutputFormat == NULL){
        (*jniEnv)->DeleteLocalRef(jniEnv,SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_getOutputFormat);
    deleteRef(jniEnv);
    return ret;
}
int setPosition(int l, int t, int w, int h ,int mode){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setPosition == NULL) {
        m_setPosition = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setPosition","(IIIII)I");
        if (m_setPosition == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setPosition,l,t,w,h,mode);
    deleteRef(jniEnv);
    return ret;
}
jintArray getPosition(){
    jintArray ret = NULL;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_getPosition == NULL) {
        m_getPosition = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "getPosition","()[I");
        if (m_getPosition == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallObjectMethod(jniEnv, mSettingJava, m_getPosition);
    deleteRef(jniEnv);
    return ret;
}
int restoreFactorySettings(){
    int ret = -1;
    if(mSettingJava==NULL){
        int result = InitCCallJava();
        if(result != 1){
        return ret;
        }else{
        if(m_restoreFactorySettings == NULL){
        m_restoreFactorySettings = (*jniEnv)->GetMethodID(jniEnv,SettingJava,"restoreFactorySettings","()I");
        if(m_restoreFactorySettings == NULL){
        (*jniEnv)->DeleteLocalRef(jniEnv,SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_restoreFactorySettings);
    deleteRef(jniEnv);
    return ret;
}
int setDate(int year, int month, int day){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setDate == NULL) {
        m_setDate = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setDate","(III)I");
        if (m_setDate == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setDate,year,month,day);
    deleteRef(jniEnv);
    return ret;
}
int setTime(int hourOfDay, int minute){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setTime == NULL) {
        m_setTime = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setTime","(II)I");
        if (m_setTime == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setTime,hourOfDay,minute);
    deleteRef(jniEnv);
    return ret;
}
int setTimeFormat(int timeFormat ){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setTimeFormat == NULL) {
        m_setTimeFormat = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setTimeFormat","(I)I");
        if (m_setTimeFormat == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setTimeFormat,timeFormat);
    deleteRef(jniEnv);
    return ret;
}
int getTimeFormat(){
    int ret = -1;
    if(mSettingJava==NULL){
        int result = InitCCallJava();
        if(result != 1){
        return ret;
        }else{
        if(m_getTimeFormat == NULL){
        m_getTimeFormat = (*jniEnv)->GetMethodID(jniEnv,SettingJava,"getTimeFormat","()I");
        if(m_getTimeFormat == NULL){
        (*jniEnv)->DeleteLocalRef(jniEnv,SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_getTimeFormat);
    deleteRef(jniEnv);
    return ret;
}
int setDateFormat(jstring dateFormat){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setDateFormat == NULL) {
        m_setDateFormat = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setDateFormat","(Ljava/lang/String;)I");
        if (m_setDateFormat == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setDateFormat,dateFormat);
    deleteRef(jniEnv);
    return ret;
}
jstring getDateFormat(){
    jstring ret = NULL;
    if(mSettingJava==NULL){
        int result = InitCCallJava();
        if(result != 1){
        return ret;
        }else{
        if(m_getDateFormat == NULL){
        m_getDateFormat = (*jniEnv)->GetMethodID(jniEnv,SettingJava,"getDateFormat","()Ljava/lang/String;");
        if(m_getDateFormat == NULL){
        (*jniEnv)->DeleteLocalRef(jniEnv,SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallObjectMethod(jniEnv, mSettingJava, m_getDateFormat);
    deleteRef(jniEnv);
    return ret;
}
int setAutotime(int Autotime){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setAutotime == NULL) {
        m_setAutotime = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setAutotime","(I)I");
        if (m_setAutotime == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setAutotime,Autotime);
    deleteRef(jniEnv);
    return ret;
}
int getAutotime(){
    int ret = -1;
    if(mSettingJava==NULL){
        int result = InitCCallJava();
        if(result != 1){
        return ret;
        }else{
        if(m_getAutotime == NULL){
        m_getAutotime = (*jniEnv)->GetMethodID(jniEnv,SettingJava,"getAutotime","()I");
        if(m_getAutotime == NULL){
        (*jniEnv)->DeleteLocalRef(jniEnv,SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_getAutotime);
    deleteRef(jniEnv);
    return ret;
}
int setAutoTimeZone(int autoTimeZone){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setAutoTimeZone == NULL) {
        m_setAutoTimeZone = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setAutoTimeZone","(I)I");
        if (m_setAutoTimeZone == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setAutoTimeZone,autoTimeZone);
    deleteRef(jniEnv);
    return ret;
}
int getAutoTimeZone(){
    int ret = -1;
    if(mSettingJava==NULL){
        int result = InitCCallJava();
        if(result != 1){
        return ret;
        }else{
        if(m_getAutoTimeZone == NULL){
        m_getAutoTimeZone = (*jniEnv)->GetMethodID(jniEnv,SettingJava,"getAutoTimeZone","()I");
        if(m_getAutoTimeZone == NULL){
        (*jniEnv)->DeleteLocalRef(jniEnv,SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_getAutoTimeZone);
    deleteRef(jniEnv);
    return ret;
}
int setTimeZone(jstring timeZone){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setTimeZone == NULL) {
        m_setTimeZone = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setTimeZone","(Ljava/lang/String;)I");
        if (m_setTimeZone == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setTimeZone,timeZone);
    deleteRef(jniEnv);
    return ret;
}
jstring getTimeZone(){
    jstring ret = NULL;
    if(mSettingJava==NULL){
        int result = InitCCallJava();
        if(result != 1){
        return ret;
        }else{
        if(m_getTimeZone == NULL){
        m_getTimeZone = (*jniEnv)->GetMethodID(jniEnv,SettingJava,"getTimeZone","()Ljava/lang/String;");
        if(m_getTimeZone == NULL){
        (*jniEnv)->DeleteLocalRef(jniEnv,SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallObjectMethod(jniEnv, mSettingJava, m_getTimeZone);
    deleteRef(jniEnv);
    return ret;
}
int setResolution(int index){
    int ret = -1;
    if(mSettingJava == NULL) {
        int result = InitCCallJava();
        if (result != 1) {
        return ret;
        }else{
        if (m_setResolution == NULL) {
        m_setResolution = (*jniEnv)->GetMethodID(jniEnv, SettingJava, "setResolution","(I)I");
        if (m_setResolution == NULL) {
        (*jniEnv)->DeleteLocalRef(jniEnv, SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_setResolution,index);
    deleteRef(jniEnv);
    return ret;
}
int getResolution(){
    int ret = -1;
    if(mSettingJava==NULL){
        int result = InitCCallJava();
        if(result != 1){
        return ret;
        }else{
        if(m_getResolution == NULL){
        m_getResolution = (*jniEnv)->GetMethodID(jniEnv,SettingJava,"getResolution","()I");
        if(m_getResolution == NULL){
        (*jniEnv)->DeleteLocalRef(jniEnv,SettingJava);
        (*jniEnv)->DeleteLocalRef(jniEnv, mSettingJava);
        return ret;
        }
        }
        }
    }
    ret = (*jniEnv)->CallIntMethod(jniEnv, mSettingJava, m_getResolution);
    deleteRef(jniEnv);
    return ret;
}
void deleteRef(JNIEnv* env){
    if(env!=NULL){
        (*env)->DeleteLocalRef(env, mSettingJava);
        (*env)->DeleteLocalRef(env, SettingJava);
        mSettingJava = NULL;
        SettingJava = NULL;
    }
}
