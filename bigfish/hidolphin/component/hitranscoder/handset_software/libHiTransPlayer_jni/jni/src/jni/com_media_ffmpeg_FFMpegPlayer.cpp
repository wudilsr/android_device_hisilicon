/* //device/libs/android_runtime/com_media_ffmpeg_FFMpegPlayer.cpp
**
** Copyright 2007, The Android Open Source Project
**
/*
 * Copyright (C) 2011 xuyangpo/x54178
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#define TAG "FFMpegPlayer-JNI"

#include <android/log.h>
#include "jniUtils.h"
#include "methods.h"
#include "mediaplayer.h"
#include "ahplayerdef.h"
#include "HiMLoger.h"


struct fields_t {
    jfieldID    context;
    jmethodID   post_event;
    jmethodID   write_pcm;
    jmethodID   config_audioTrack;
    jfieldID sec;
    jfieldID RTBandwidth;
    jfieldID SMBandwidth;
    jfieldID PLVideoBitRate;
    jfieldID DLVideoBitRate;
    jfieldID BufferedTime;
};
static fields_t fields;
static JNIEnv* JniEnv = NULL;
static const char* const kClassPathName = "com/media/libahplayer/libahplayer";
static const char* const kMonitorInfoClassPathName = "com/media/libahplayer/AHSMonitorInfo";

/*Android Audio Track 控制类，包括配置AudioTrack 属性，和写入PCM音频数据*/
/*Android Audio Track control class, include the attribute of AudioTrack Configration, and writting in PCM audio data*/
class JNIWritePCM: public MediaPlayerPCMWriter
{
public:
    JNIWritePCM(JNIEnv* env, jobject thiz, jobject weak_thiz);
    ~JNIWritePCM();
    void writePCM(unsigned char* buf,int bufCount);
    int configAudioTrack(int streamType, int sampleRate, int channelConfig,int bytesPerSample,int trackMode );

private:
    JNIWritePCM();
    jclass      mClass;     // Reference to MediaPlayer class
    jobject     mObject;    // Weak ref to MediaPlayer Java object to call on

};
JNIWritePCM::JNIWritePCM(JNIEnv* env, jobject thiz, jobject weak_thiz)
{
    // Hold onto the MediaPlayer class for use in calling the static method
    // that posts events to the application thread.
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        jniThrowException(env, "java/lang/Exception", kClassPathName);
        return;
    }
    mClass = (jclass)env->NewGlobalRef(clazz);

    // We use a weak reference so the MediaPlayer object can be garbage collected.
    // The reference is only used as a proxy for callbacks.
    mObject  = env->NewGlobalRef(weak_thiz);
}
JNIWritePCM::~JNIWritePCM()
{
    // remove global references
    JNIEnv *env = getJNIEnv();
    env->DeleteGlobalRef(mObject);
    env->DeleteGlobalRef(mClass);
}
int JNIWritePCM::configAudioTrack(int streamType, int sampleRate, int channelConfig,int bytesPerSample,int trackMode )
{
    MMLOGI( TAG,
        "setting audio track:streamType %d,sampleRate %d,channels %d,format %d,trackMode %d",
        streamType, sampleRate, channelConfig, bytesPerSample, trackMode);
    JNIEnv *env = getJNIEnv();
    if(env == NULL)
        env = JniEnv;
       return env->CallStaticIntMethod(mClass, fields.config_audioTrack,streamType, sampleRate, channelConfig, bytesPerSample, trackMode);
}
void JNIWritePCM::writePCM(unsigned char* buf,int bufCount)
{
//    MMLOGI( TAG, "start writePCM");
    JNIEnv *env = getJNIEnv();
    if(env == NULL)
        env = JniEnv;
    if(buf == NULL)
    {
        detachThreadFromJNI();
        MMLOGI( TAG,
            "Detach current thread for thread end!!\n");
        return;
    }
    jbyteArray array = env->NewByteArray( bufCount);
     env->SetByteArrayRegion(array, 0, bufCount, (jbyte *)buf);
    env->CallStaticVoidMethod(mClass, fields.write_pcm,array);
    env->DeleteLocalRef(array);
}
// ----------------------------------------------------------------------------
// ref-counted object for callbacks
/*player事件对java的回调借口*/
/*the interfaces to callback event of player */
class HiMediaPlayerListener: public MediaPlayerListener
{
public:
    HiMediaPlayerListener(JNIEnv* env, jobject thiz, jobject weak_thiz);
    ~HiMediaPlayerListener();
    void notify(int msg, int ext1, int ext2);
private:
    HiMediaPlayerListener();
    jclass      mClass;     // Reference to MediaPlayer class
    jobject     mObject;    // Weak ref to MediaPlayer Java object to call on
};

HiMediaPlayerListener::HiMediaPlayerListener(JNIEnv* env, jobject thiz, jobject weak_thiz)
{
    // Hold onto the MediaPlayer class for use in calling the static method
    // that posts events to the application thread.
    jclass clazz = env->GetObjectClass(thiz);
    if (clazz == NULL) {
        jniThrowException(env, "java/lang/Exception", kClassPathName);
        return;
    }
    mClass = (jclass)env->NewGlobalRef(clazz);

    // We use a weak reference so the MediaPlayer object can be garbage collected.
    // The reference is only used as a proxy for callbacks.
    mObject  = env->NewGlobalRef(weak_thiz);
}

HiMediaPlayerListener::~HiMediaPlayerListener()
{
    // remove global references
    JNIEnv *env = getJNIEnv();
    env->DeleteGlobalRef(mObject);
    env->DeleteGlobalRef(mClass);
}

void HiMediaPlayerListener::notify(int msg, int ext1, int ext2)
{
    MMLOGI( TAG,
                "Start notify\n");
    JNIEnv *env = getJNIEnv();
    if(env == NULL)
        env = JniEnv;
    if((msg == 0)&&(ext1 == -1)&&(ext2 == -1))
    {
        detachThreadFromJNI();
        MMLOGI( TAG,
            "Detach current thread for thread end!!\n");
        return;
    }
    MMLOGI( TAG,
            "start CallStaticVoidMethod!!\n");
    env->CallStaticVoidMethod(mClass, fields.post_event, mObject, msg, ext1, ext2, 0);
}

// ----------------------------------------------------------------------------

static MediaPlayer* getMediaPlayer(JNIEnv* env, jobject thiz)
{
    return (MediaPlayer*)env->GetIntField(thiz, fields.context);
}

static MediaPlayer* setMediaPlayer(JNIEnv* env, jobject thiz, MediaPlayer* player)
{
    MediaPlayer* old = (MediaPlayer*)env->GetIntField(thiz, fields.context);
    if (old != NULL) {
        MMLOGI( TAG, "freeing old mediaplayer object");
        free(old);
    }
    env->SetIntField(thiz, fields.context, (int)player);
    return old;
}

// If exception is NULL and opStatus is not OK, this method sends an error
// event to the client application; otherwise, if exception is not NULL and
// opStatus is not OK, this method throws the given exception to the client
// application.
static void process_media_player_call(JNIEnv *env, jobject thiz, status_t opStatus, const char* exception, const char *message)
{
    if (exception == NULL) {  // Don't throw exception. Instead, send an event.
        /*
        if (opStatus != (status_t) OK) {
            sp<MediaPlayer> mp = getMediaPlayer(env, thiz);
            if (mp != 0) mp->notify(MEDIA_ERROR, opStatus, 0);
        }
        */
    } else {  // Throw exception!
        if ( opStatus == (status_t) INVALID_OPERATION ) {
            jniThrowException(env, "java/lang/IllegalStateException", NULL);
        } else if ( opStatus != (status_t) OK ) {
            if (strlen(message) > 230) {
               // if the message is too long, don't bother displaying the status code
               jniThrowException( env, exception, message);
            } else {
               char msg[256];
                // append the status code to the message
               sprintf(msg, "%s: status=0x%X", message, opStatus);
               jniThrowException( env, exception, msg);
            }
        }
    }
}

//add by x54178
/*当前无用*/
/*current no use*/
static void
com_media_ffmpeg_FFMpegPlayer_setVideoDisplayMode(
    JNIEnv *env, jobject thiz, int jmode)
{/*no use*/
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    MMLOGI( TAG, "setVideoDisplayMode: %d", jmode);
    status_t opStatus = mp->setVideoDisplayMode(jmode);
    process_media_player_call(
            env, thiz, opStatus, "java/io/IOException",
            "setVideoDisplayMode failed." );

}
/*当前无用*/
/*current no use*/
static void
com_media_ffmpeg_FFMpegPlayer_setPlayerConfig(JNIEnv *env, jobject thiz, jstring path)
{/*no use*/
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    if (path == NULL) {
        jniThrowException(env, "java/lang/IllegalArgumentException", NULL);
        return;
    }

    const char *pathStr = env->GetStringUTFChars(path, NULL);
    if (pathStr == NULL) {  // Out of memory
        jniThrowException(env, "java/lang/RuntimeException", "Out of memory");
        return;
    }
    MMLOGI( TAG, "setPlayerConfig: path %s", pathStr);
    status_t opStatus = mp->setPlayerConfig(pathStr);

    // Make sure that local ref is released before a potential exception
    env->ReleaseStringUTFChars(path, pathStr);

    process_media_player_call(
            env, thiz, opStatus, "java/io/IOException",
            "setPlayerConfig failed." );
}

/*设置服务器的URL*/
/* set the server url*/
static void
com_media_ffmpeg_FFMpegPlayer_setDataSourceAndHeaders(
        JNIEnv *env, jobject thiz, jstring path, jobject headers) {
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    if (path == NULL) {
        jniThrowException(env, "java/lang/IllegalArgumentException", NULL);
        return;
    }

    const char *pathStr = env->GetStringUTFChars(path, NULL);
    if (pathStr == NULL) {  // Out of memory
        jniThrowException(env, "java/lang/RuntimeException", "Out of memory");
        return;
    }

    MMLOGI( TAG, "setDataSource: path %s", pathStr);
    status_t opStatus = mp->setDataSource(pathStr);

    // Make sure that local ref is released before a potential exception
    env->ReleaseStringUTFChars(path, pathStr);

    process_media_player_call(
            env, thiz, opStatus, "java/io/IOException",
            "setDataSource failed." );
}

/*设置服务器的URL*/
/* set the server url*/
static void
com_media_ffmpeg_FFMpegPlayer_setDataSource(JNIEnv *env, jobject thiz, jstring path)
{
    com_media_ffmpeg_FFMpegPlayer_setDataSourceAndHeaders(env, thiz, path, 0);
}

/*从java层传递surface 对象到Cpp层，注册该surface, 以显示视频*/
/*deliver from java to cpp through jni, register this surface for video display*/
static void
com_media_ffmpeg_FFMpegPlayer_setVideoSurface(JNIEnv *env, jobject thiz, jobject jsurface,int apiVersion)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    if (jsurface == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    process_media_player_call( env, thiz, mp->setVideoSurface(env, jsurface,apiVersion),
                              "java/io/IOException", "Set video surface failed.");
}

/*配置音视频播放的一些参数*/
/* config some parameters of audio and video*/
static void
com_media_ffmpeg_FFMpegPlayer_prepare(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    process_media_player_call( env, thiz, mp->prepare(), "java/io/IOException", "Prepare failed." );
}

/*开始播放，建立播放线程*/
/*start play, create thread for play*/
static void
com_media_ffmpeg_FFMpegPlayer_start(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    process_media_player_call( env, thiz, mp->start(), NULL, NULL );
}

/*停止播放，移除播放线程*/
/*stop play, destroy thread for play*/
static void
com_media_ffmpeg_FFMpegPlayer_stop(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    process_media_player_call( env, thiz, mp->stop(), NULL, NULL );
}

/*暂停播放*/
/*pause play*/
static void
com_media_ffmpeg_FFMpegPlayer_pause(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    process_media_player_call( env, thiz, mp->pause(), NULL, NULL );
}

static jboolean
com_media_ffmpeg_FFMpegPlayer_isPlaying(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return false;
    }
    const jboolean is_playing = mp->isPlaying();
    return is_playing;
}

/*当前不支持*/
/*no use*/
static void
com_media_ffmpeg_FFMpegPlayer_seekTo(JNIEnv *env, jobject thiz, int msec)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    process_media_player_call( env, thiz, mp->seekTo(msec), NULL, NULL );
}
/*获取视频宽度*/
/*get video width*/
static int
com_media_ffmpeg_FFMpegPlayer_getVideoWidth(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return 0;
    }
    int w;
    if (0 != mp->getVideoWidth(&w)) {
        w = 0;
    }
    return w;
}

/*获取视频高度*/
/*get video height*/
static int
com_media_ffmpeg_FFMpegPlayer_getVideoHeight(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return 0;
    }
    int h;
    if (0 != mp->getVideoHeight(&h)) {
        h = 0;
    }
    return h;
}

/*当前不支持*/
/*no use*/
static int
com_media_ffmpeg_FFMpegPlayer_getCurrentPosition(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return 0;
    }
    int msec;
    process_media_player_call( env, thiz, mp->getCurrentPosition(&msec), NULL, NULL );
    return msec;
}

/*实时流，当前不支持*/
/*real stream, no use*/
static int
com_media_ffmpeg_FFMpegPlayer_getDuration(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return 0;
    }
    int msec;
    process_media_player_call( env, thiz, mp->getDuration(&msec), NULL, NULL );
    return msec;
}

/*当前不支持*/
/*no use*/
static void
com_media_ffmpeg_FFMpegPlayer_reset(JNIEnv *env, jobject thiz)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    process_media_player_call( env, thiz, mp->reset(), NULL, NULL );
}

/*当前不支持*/
/*no use*/
static void
com_media_ffmpeg_FFMpegPlayer_setAudioStreamType(JNIEnv *env, jobject thiz, int streamtype)
{
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    process_media_player_call( env, thiz, mp->setAudioStreamType(streamtype) , NULL, NULL );
}

// ----------------------------------------------------------------------------
/*获取java层静态函数和变量的引用*/
/*get the reference of variables and static methods from java */
static void
com_media_ffmpeg_FFMpegPlayer_native_init(JNIEnv *env)
{
    MMLOGI( TAG, "native_init");
    jclass clazz;
    clazz = env->FindClass(kClassPathName);
    if (clazz == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find android/media/MediaPlayer");
        return;
    }

    fields.context = env->GetFieldID(clazz, "mNativeContext", "I");
    if (fields.context == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find MediaPlayer.mNativeContext");
        return;
    }

    fields.post_event = env->GetStaticMethodID(clazz, "postEventFromNative",
                                                   "(Ljava/lang/Object;IIILjava/lang/Object;)V");
    if (fields.post_event == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find FFMpegMediaPlayer.postEventFromNative");
        return;
    }
    fields.write_pcm = env->GetStaticMethodID(clazz, "writePCM",
                                                   "([B)V");
    fields.config_audioTrack= env->GetStaticMethodID(clazz, "configATrack",
                                                   "(IIIII)I");
    if (fields.write_pcm == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find libahPlayer.writePCM");
        return;
    }
    clazz = env->FindClass(kMonitorInfoClassPathName);
    if(clazz == NULL){
        jniThrowException(env, "java/lang/RuntimeException", "Can't find com/media/libahplayer/libahplayer/AHSMonitorInfo");
        return;
    }
    fields.sec = env->GetFieldID(clazz,"time","I");
    fields.RTBandwidth = ((env)->GetFieldID(clazz,"RTBandwidth","D"));
    fields.SMBandwidth = (env)->GetFieldID(clazz,"SMBandwidth","D");
    fields.PLVideoBitRate = (env)->GetFieldID(clazz,"PLVideoBitRate","D");
    fields.DLVideoBitRate = (env)->GetFieldID(clazz,"DLVideoBitRate","D");
    fields.BufferedTime = (env)->GetFieldID(clazz,"BufferedTime","D");
}

/* 初始化player实例，及一些回写借口*/
/*init instance of player, and some interface for inverse callback*/
static void
com_media_ffmpeg_FFMpegPlayer_native_setup(JNIEnv *env, jobject thiz, jobject weak_this)
{
    MMLOGI( TAG, "native_setup");
    MediaPlayer* mp = new MediaPlayer();
    MMLOGI( TAG, "new MediaPlayer()");
    if (mp == NULL) {
        jniThrowException(env, "java/lang/RuntimeException", "Out of memory");
        return;
    }
    // create new listener and give it to MediaPlayer
    HiMediaPlayerListener* listener = new HiMediaPlayerListener(env, thiz, weak_this);
    mp->setListener(listener);
    JNIWritePCM* PCMWriter = new JNIWritePCM(env, thiz, weak_this);
    mp->setPCMWriter(PCMWriter);
        MMLOGI( TAG, "new JNIWritePCM HiMediaPlayerListener()");
    // Stow our new C++ MediaPlayer in an opaque field in the Java object.
    setMediaPlayer(env, thiz, mp);
        MMLOGI( TAG, "setMediaPlayer");
}

static void
com_media_ffmpeg_FFMpegPlayer_release(JNIEnv *env, jobject thiz)
{

}

static void
com_media_ffmpeg_FFMpegPlayer_native_finalize(JNIEnv *env, jobject thiz)
{
    MMLOGI( TAG, "native_finalize");
    com_media_ffmpeg_FFMpegPlayer_release(env, thiz);
}

/*挂起，恢复播放*/
/*suspend or resume player*/
static jint
com_media_ffmpeg_FFMpegPlayer_native_suspend_resume(
        JNIEnv *env, jobject thiz, jboolean isSuspend) {
    MediaPlayer* mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return UNKNOWN_ERROR;
    }
    mp->suspend();

    delete mp;
    return NO_ERROR;
}

/*当前不支持*/
/*no use*/
static int com_media_ffmpeg_FFMpegPlayer_getAHSData(JNIEnv *env, jobject thiz,jobject info,int lastTimeSec)
{
    return -1;
}

/*当前不支持*/
/*no use*/
static float com_media_ffmpeg_FFMpegPlayer_getVideoAspectRatio(JNIEnv *env, jobject thiz)
{
    return 0;
}
// ----------------------------------------------------------------------------

static JNINativeMethod gMethods[] = {
    {"setDataSource",       "(Ljava/lang/String;)V",            (void *)com_media_ffmpeg_FFMpegPlayer_setDataSource},
    {"_setVideoSurface",    "(Landroid/view/Surface;I)V",        (void *)com_media_ffmpeg_FFMpegPlayer_setVideoSurface},
    {"prepare",             "()V",                              (void *)com_media_ffmpeg_FFMpegPlayer_prepare},
    {"_start",              "()V",                              (void *)com_media_ffmpeg_FFMpegPlayer_start},
    {"_stop",               "()V",                              (void *)com_media_ffmpeg_FFMpegPlayer_stop},
    {"getVideoWidth",       "()I",                              (void *)com_media_ffmpeg_FFMpegPlayer_getVideoWidth},
    {"getVideoHeight",      "()I",                              (void *)com_media_ffmpeg_FFMpegPlayer_getVideoHeight},
    {"seekTo",              "(I)V",                             (void *)com_media_ffmpeg_FFMpegPlayer_seekTo},
    {"_pause",              "()V",                              (void *)com_media_ffmpeg_FFMpegPlayer_pause},
    {"isPlaying",           "()Z",                              (void *)com_media_ffmpeg_FFMpegPlayer_isPlaying},
    {"getCurrentPosition",  "()I",                              (void *)com_media_ffmpeg_FFMpegPlayer_getCurrentPosition},
    {"getDuration",         "()I",                              (void *)com_media_ffmpeg_FFMpegPlayer_getDuration},
    {"_release",            "()V",                              (void *)com_media_ffmpeg_FFMpegPlayer_release},
    {"_reset",              "()V",                              (void *)com_media_ffmpeg_FFMpegPlayer_reset},
    {"setAudioStreamType",  "(I)V",                             (void *)com_media_ffmpeg_FFMpegPlayer_setAudioStreamType},
    {"native_init",         "()V",                              (void *)com_media_ffmpeg_FFMpegPlayer_native_init},
    {"native_setup",        "(Ljava/lang/Object;)V",            (void *)com_media_ffmpeg_FFMpegPlayer_native_setup},
    {"native_finalize",     "()V",                              (void *)com_media_ffmpeg_FFMpegPlayer_native_finalize},
    {"native_suspend_resume", "(Z)I",                           (void *)com_media_ffmpeg_FFMpegPlayer_native_suspend_resume},
    {"setVideoDisplayMode", "(I)V",                             (void *)com_media_ffmpeg_FFMpegPlayer_setVideoDisplayMode},
    {"setPlayerConfig", "(Ljava/lang/String;)V",                             (void *)com_media_ffmpeg_FFMpegPlayer_setPlayerConfig},
    {"native_getAHSData", "(Ljava/lang/Object;I)I",                             (void *)com_media_ffmpeg_FFMpegPlayer_getAHSData},
    {"getVideoAspectRatio", "()F",                             (void *)com_media_ffmpeg_FFMpegPlayer_getVideoAspectRatio},
};
int register_android_media_FFMpegPlayerAndroid(JNIEnv *env) {
    JniEnv = env;
    return jniRegisterNativeMethods(env, kClassPathName, gMethods, sizeof(gMethods) / sizeof(gMethods[0]));
}
