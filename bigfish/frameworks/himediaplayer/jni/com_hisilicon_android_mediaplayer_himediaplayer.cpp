#define LOG_NDEBUG 0
#define LOG_TAG "HiMediaPlayer-JNI"

#include <utils/Log.h>
#include <jni.h>
#include <JNIHelp.h>

#include <android_runtime/AndroidRuntime.h>
#include "android_runtime/android_view_Surface.h"
#include <gui/Surface.h>
#include <binder/Parcel.h>
#include <android_os_Parcel.h>
#include <android_util_Binder.h>

#include "mediaplayer.h"
#include "HiMediaDefine.h"
#include "HiMediaPlayerManage.h"


using namespace android;

JavaVM *gJVM;
JNIEnv *gEnv;

struct fields_t
{
    jfieldID context;
    jfieldID surface;
    jmethodID post_event;
};
static fields_t fields;

static Mutex sLock;

class JNIMediaPlayerListener : public HiMediaPlayerListener
{
public:
    JNIMediaPlayerListener(JNIEnv* env, jobject thiz, jobject weak_thiz);
    ~JNIMediaPlayerListener();
    void notify(int msg, int ext1, int ext2, const Parcel *obj = NULL);
private:
    JNIMediaPlayerListener();
    jclass mClass;     // Reference to MediaPlayer class
    jobject mObject;    // Weak ref to MediaPlayer Java object to call on
    JNIEnv*     mEnv;
};

JNIMediaPlayerListener::JNIMediaPlayerListener(JNIEnv* env, jobject thiz, jobject weak_thiz)
{
    // Hold onto the HiMediaPlayer class for use in calling the static method
    // that posts events to the application thread.
    jclass clazz = env->GetObjectClass(thiz);

    if (clazz == NULL)
    {
        LOGE("Can't find com/hisilicon/android/mediaplayer/HiMediaPlayer");
        jniThrowException(env, "java/lang/Exception", NULL);
        return;
    }

    mEnv   = env;
    mClass = (jclass)env->NewGlobalRef(clazz);

    // We use a weak reference so the HiMediaPlayer object can be garbage collected.
    // The reference is only used as a proxy for callbacks.
    mObject = env->NewGlobalRef(weak_thiz);
}

JNIMediaPlayerListener::~JNIMediaPlayerListener()
{
    bool IsThreadAttach = false;
    // remove global references

    JNIEnv *env = AndroidRuntime::getJNIEnv();//mEnv; AndroidRuntime::getJNIEnv();
    if (NULL == env)
    {
        LOGV("getJNIEnv IS NULL");
        // sometimes getJNIEnv return NULL,because of current thread has not attached
        // with VM
        gJVM->AttachCurrentThread(&env, NULL);
        IsThreadAttach = true;
        if (NULL == env)
        {
            LOGE("JNIEnv is NULL");
            return;
        }
    }


    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    env->DeleteGlobalRef(mObject);
    env->DeleteGlobalRef(mClass);

    if (IsThreadAttach)
    {
        gJVM->DetachCurrentThread();
        IsThreadAttach = false;
    }

}

void JNIMediaPlayerListener::notify(int msg, int ext1, int ext2, const Parcel *obj)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    JNIEnv *env = AndroidRuntime::getJNIEnv(); //mEnv;AndroidRuntime::getJNIEnv();

    bool IsThreadAttach = false;

    if (NULL == env)
    {
        // sometimes getJNIEnv return NULL,because of current thread has not attached
        // with VM
        gJVM->AttachCurrentThread(&env, NULL);
        IsThreadAttach = true;
        if (NULL == env)
        {
            jniThrowException(env, "java/lang/RuntimeException", "Can not get jni env");
            return;
        }
    }

    if (obj && (obj->dataSize() > 0))
    {
        jbyteArray jArray = env->NewByteArray(obj->dataSize());
        if (jArray != NULL)
        {
            jbyte *nArray = env->GetByteArrayElements(jArray, NULL);
            memcpy(nArray, obj->data(), obj->dataSize());
            env->ReleaseByteArrayElements(jArray, nArray, 0);
            LOGV("msg ext1 ext2 is %d %d %d", msg, ext1, ext2);
            env->CallStaticVoidMethod(mClass, fields.post_event, mObject,
                                      msg, ext1, ext2, jArray);
            env->DeleteLocalRef(jArray);
        }
    }
    else
    {
        LOGV("msg ext1 ext2 is %d %d %d", msg, ext1, ext2);
        env->CallStaticVoidMethod(mClass, fields.post_event, mObject,
                                  msg, ext1, ext2, NULL);
    }

    if (IsThreadAttach)
    {
        gJVM->DetachCurrentThread();
        IsThreadAttach = false;
    }
}

static void com_hisilicon_android_mediaplayer_himediaplayer_native_init(JNIEnv *env, jobject thiz)
{
    jclass clazz;
    clazz = env->FindClass("com/hisilicon/android/mediaplayer/HiMediaPlayer");
    if (clazz == NULL)
    {
        LOGE("jni init1 faile\n");
        return;
    }
    fields.context = env->GetFieldID(clazz, "mNativeContext", "I");
    if (fields.context == NULL)
    {
        return;
    }
    fields.post_event = env->GetStaticMethodID(clazz, "postEventFromNative",
                                               "(Ljava/lang/Object;IIILjava/lang/Object;)V");
    if (fields.post_event == NULL)
    {
        return;
    }
    fields.surface = env->GetFieldID(clazz, "mSurface", "Landroid/view/Surface;");
    if (fields.surface == NULL)
    {
        jniThrowException(env, "java/lang/RuntimeException", "Can't find HiMediaPlayer.mSurface");
        return;
    }
}

static sp <HiMediaPlayerManage> setMediaPlayer(JNIEnv * env, jobject thiz, const sp <HiMediaPlayerManage> &player)
{
    Mutex::Autolock l(sLock);

    sp <HiMediaPlayerManage> old = (HiMediaPlayerManage*)env->GetIntField(thiz, fields.context);
    if (player.get())
    {
        player->incStrong(thiz);
    }

    if (old != 0)
    {
        LOGE("release old->decStrong\n");
        old->decStrong(thiz);
    }

    env->SetIntField(thiz, fields.context, (int)player.get());
    return old;
}

static void com_hisilicon_android_mediaplayer_himediaplayer_native_setup(JNIEnv *env, jobject thiz, jobject weak_this)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = new HiMediaPlayerManage();
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/RuntimeException", "Out of memory");
        return;
    }

    // create new listener and give it to HiMediaPlayerManage
    sp <JNIMediaPlayerListener> listener = new JNIMediaPlayerListener(env, thiz, weak_this);
    mp->setListener(listener);

    // Stow our new C++ HiMediaPlayerManage in an opaque field in the Java object.
    setMediaPlayer(env, thiz, mp);
}

static sp <HiMediaPlayerManage> getMediaPlayer(JNIEnv * env, jobject thiz)
{
    Mutex::Autolock l(sLock);
    HiMediaPlayerManage* const p = (HiMediaPlayerManage*)env->GetIntField(thiz, fields.context);

    return sp <HiMediaPlayerManage>(p);
}

static void com_hisilicon_android_mediaplayer_himediaplayer_release(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = setMediaPlayer(env, thiz, 0);
    if (mp != NULL)
    {
        mp->reset();
        // this prevents native callbacks after the object is released
        mp->setListener(0);
    }
}

static void com_hisilicon_android_mediaplayer_himediaplayer_native_finalize(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp != NULL)
    {
        LOGW("HiMediaPlayerManage finalized without being released");
    }

    com_hisilicon_android_mediaplayer_himediaplayer_release(env, thiz);
}

static void process_media_player_call(JNIEnv *env, jobject thiz, status_t opStatus, const char* exception,
                                      const char *message)
{
    if (exception == NULL)
    {
        // Don't throw exception. Instead, send an event.
        if (opStatus != (status_t) OK)
        {
            sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
            if (mp != 0)
            {
                LOGE("%s Call %s IN JNI Call Fail", LOG_TAG, __FUNCTION__);
                mp->notify(mp.get(), MEDIA_ERROR, opStatus, 0);
            }
        }
    }
    else
    {
        // Throw exception!
        if (opStatus == (status_t) INVALID_OPERATION)
        {
            jniThrowException(env, "java/lang/IllegalStateException", NULL);
        }
        else if (opStatus == (status_t) PERMISSION_DENIED)
        {
            jniThrowException(env, "java/lang/SecurityException", NULL);
        }
        else if (opStatus != (status_t) OK)
        {
            if (strlen(message) > 230)
            {
                // if the message is too long, don't bother displaying the status code
                jniThrowException( env, exception, message);
            }
            else
            {
                char msg[256];
                // append the status code to the message
                sprintf(msg, "%s: status=0x%X", message, opStatus);
                jniThrowException( env, exception, msg);
            }
        }
    }
}

static void com_hisilicon_android_mediaplayer_himediaplayer_prepareAsync(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    process_media_player_call( env, thiz, mp->prepareAsync(), "java/io/IOException", "Prepare Async failed." );
}

static void com_hisilicon_android_mediaplayer_himediaplayer_setSurfaceView(JNIEnv *env, jobject thiz)
{
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    jobject surface = env->GetObjectField(thiz, fields.surface);
    if (surface != NULL)
    {
        // modified for subsurface
        sp <Surface> subSurface(android_view_Surface_getSurface(env, surface));
        LOGV("prepare: subtitile surface=%p (id=%d)",
             subSurface.get());
        mp->setSubSurface(subSurface);
    }
}

static void com_hisilicon_android_mediaplayer_himediaplayer_setVolume(JNIEnv *env, jobject thiz, float leftVolume,
                                                               float rightVolume)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    LOGV("setVolume: left %f  right %f", leftVolume, rightVolume);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    mp->setVolume(leftVolume, rightVolume);
    /* report error will lead to apk stop playing */
    //process_media_player_call( env, thiz, mp->setVolume(leftVolume, rightVolume), NULL, NULL );
}


// Sends the request and reply parcels to the media player via the
// binder interface.
static jint com_hisilicon_android_mediaplayer_himediaplayer_invoke(JNIEnv *env, jobject thiz,
                                                            jobject java_request, jobject java_reply)
{
    sp <HiMediaPlayerManage> media_player = getMediaPlayer(env, thiz);
    if (media_player == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return UNKNOWN_ERROR;
    }

    Parcel *request = parcelForJavaObject(env, java_request);
    request->setDataPosition(0);


    Parcel *reply = parcelForJavaObject(env, java_reply);

    // Don't use process_media_player_call which use the async loop to
    // report errors, instead returns the status.
    jint Re = media_player->invoke(*request, reply);
    reply->setDataPosition(0);
    return Re;
}

static void com_hisilicon_android_mediaplayer_himediaplayer_reset(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    process_media_player_call( env, thiz, mp->reset(), NULL, NULL );
}

static void com_hisilicon_android_mediaplayer_himediaplayer_setAudioStreamType(JNIEnv *env, jobject thiz, int streamtype)
{
    LOGV("setAudioStreamType: %d", streamtype);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    /* report error will lead to apk stop playing */
    mp->setAudioStreamType(streamtype);
   // process_media_player_call( env, thiz, mp->setAudioStreamType(streamtype), NULL, NULL );
}

static void com_hisilicon_android_mediaplayer_himediaplayer_setLooping(JNIEnv *env, jobject thiz, jboolean looping)
{
    LOGV("%s Call %s IN looping %d", LOG_TAG, __FUNCTION__, looping);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    /* report error will lead to apk stop playing */
    mp->setLooping(looping);
    //process_media_player_call( env, thiz, mp->setLooping(looping), NULL, NULL );
}

static jboolean
com_hisilicon_android_mediaplayer_himediaplayer_isLooping(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp<HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL ) {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return false;
    }
    jboolean bIsLooping = mp->isLooping();
    LOGV("bIsLooping is %d", bIsLooping);
    return bIsLooping;
}

static void com_hisilicon_android_mediaplayer_himediaplayer_prepare(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    process_media_player_call( env, thiz, mp->prepare(), "java/io/IOException", "Prepare failed." );
}

static void com_hisilicon_android_mediaplayer_himediaplayer_stop(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    /* report error will lead to apk stop playing */
    mp->stop();
   // process_media_player_call( env, thiz, mp->stop(), NULL, NULL );
}

static void com_hisilicon_android_mediaplayer_himediaplayer_pause(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    /* report error will lead to apk stop playing */
    mp->pause();
    //process_media_player_call( env, thiz, mp->pause(), NULL, NULL );
}

static void com_hisilicon_android_mediaplayer_himediaplayer_seekTo(JNIEnv *env, jobject thiz, int msec)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    LOGV("seekTo: %d(msec)", msec);
    /* report error will lead to apk stop playing */
    mp->seekTo(msec);
    //process_media_player_call( env, thiz, mp->seekTo(msec), NULL, NULL );
}

static jboolean com_hisilicon_android_mediaplayer_himediaplayer_isPlaying(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return false;
    }
    const jboolean is_playing = mp->isPlaying();
    LOGV("isPlaying: %d", is_playing);
    return is_playing;
}

static int com_hisilicon_android_mediaplayer_himediaplayer_getDuration(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return 0;
    }
    int msec = -1;
    process_media_player_call( env, thiz, mp->getDuration(&msec), NULL, NULL );
    LOGV("getDuration: %d (msec)", msec);
    return msec;
}

static int com_hisilicon_android_mediaplayer_himediaplayer_getCurrentPosition(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return 0;
    }

    int msec;
    process_media_player_call( env, thiz, mp->getCurrentPosition(&msec), NULL, NULL );
    LOGV("getCurrentPosition: %d (msec)", msec);
    return msec;
}

static void com_hisilicon_android_mediaplayer_himediaplayer_start(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    /* report error will lead to apk stop playing */
    mp->start();
    //process_media_player_call( env, thiz, mp->start(), NULL, NULL );
}

// Sends the new filter to the client.
static jint com_hisilicon_android_mediaplayer_himediaplayer_setMetadataFilter(JNIEnv *env, jobject thiz, jobject request)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> media_player = getMediaPlayer(env, thiz);
    if (media_player == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return UNKNOWN_ERROR;
    }

    Parcel *filter = parcelForJavaObject(env, request);

    if (filter == NULL)
    {
        jniThrowException(env, "java/lang/RuntimeException", "Filter is null");
        return UNKNOWN_ERROR;
    }

    return media_player->setMetadataFilter(*filter);
}

static jboolean com_hisilicon_android_mediaplayer_himediaplayer_getMetadata(JNIEnv *env, jobject thiz, jboolean update_only,
                                                                     jboolean apply_filter, jobject reply)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> media_player = getMediaPlayer(env, thiz);
    if (media_player == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return false;
    }

    Parcel *metadata = parcelForJavaObject(env, reply);

    if (metadata == NULL)
    {
        jniThrowException(env, "java/lang/RuntimeException", "Reply parcel is null");
        return false;
    }

    metadata->freeData();
    jboolean Re = media_player->getMetadata(update_only, apply_filter, metadata);
    metadata->readInt32();
    return Re == OK;
}

static int com_hisilicon_android_mediaplayer_himediaplayer_getVideoWidth(JNIEnv *env, jobject thiz)
{
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return 0;
    }

    int w;
    if (0 != mp->getVideoWidth(&w))
    {
        LOGE("getVideoWidth failed");
        w = 0;
    }
    LOGV("%s Call %s IN w is %d", LOG_TAG, __FUNCTION__, w);
    return w;
}

static int com_hisilicon_android_mediaplayer_himediaplayer_getVideoHeight(JNIEnv *env, jobject thiz)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return 0;
    }

    int h;
    if (0 != mp->getVideoHeight(&h))
    {
        LOGE("getVideoHeight failed");
        h = 0;
    }
    LOGV("%s Call %s IN h is %d", LOG_TAG, __FUNCTION__, h);
    return h;
}

static bool ConvertKeyValueArraysToKeyedVector(JNIEnv *env, jobjectArray keys, jobjectArray values,
                                               KeyedVector <String8, String8> * keyedVector)
{
    int nKeyValuePairs = 0;
    bool failed = false;

    if ((keys != NULL) && (values != NULL))
    {
        nKeyValuePairs = env->GetArrayLength(keys);
        failed = (nKeyValuePairs != env->GetArrayLength(values));
    }

    if (!failed)
    {
        failed = ((keys != NULL && values == NULL)
           || (keys == NULL && values != NULL));
    }

    if (failed)
    {
        LOGE("keys and values arrays have different length");
        jniThrowException(env, "java/lang/IllegalArgumentException", NULL);
        return false;
    }

    for (int i = 0; i < nKeyValuePairs; ++i)
    {
        // No need to check on the ArrayIndexOutOfBoundsException, since
        // it won't happen here.
        jstring key   = (jstring) env->GetObjectArrayElement(keys, i);
        jstring value = (jstring) env->GetObjectArrayElement(values, i);

        const char* keyStr = env->GetStringUTFChars(key, NULL);
        if (!keyStr)
        {
            // OutOfMemoryError
            return false;
        }

        const char* valueStr = env->GetStringUTFChars(value, NULL);
        if (!valueStr)
        {
            // OutOfMemoryError
            env->ReleaseStringUTFChars(key, keyStr);
            return false;
        }

        keyedVector->add(String8(keyStr), String8(valueStr));

        env->ReleaseStringUTFChars(key, keyStr);
        env->ReleaseStringUTFChars(value, valueStr);
        env->DeleteLocalRef(key);
        env->DeleteLocalRef(value);
    }

    return true;
}

static void com_hisilicon_android_mediaplayer_himediaplayer_setDataSourceAndHeaders(JNIEnv *env, jobject thiz, jstring path,
                                                                             jobjectArray keys, jobjectArray values)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    if (path == NULL)
    {
        jniThrowException(env, "java/lang/IllegalArgumentException", NULL);
        return;
    }

    const char *tmp = env->GetStringUTFChars(path, NULL);
    if (tmp == NULL)
    {
        // Out of memory
        return;
    }

    LOGV("setDataSource: path %s", tmp);

    String8 pathStr(tmp);
    env->ReleaseStringUTFChars(path, tmp);
    tmp = NULL;

    // We build a KeyedVector out of the key and val arrays
    KeyedVector <String8, String8> headersVector;
    if (!ConvertKeyValueArraysToKeyedVector(
            env, keys, values, &headersVector))
    {
        return;
    }

    status_t opStatus =
        mp->setDataSource(
        pathStr,
        headersVector.size() > 0 ? &headersVector : NULL);
    process_media_player_call(
        env, thiz, opStatus, "java/io/IOException",
        "setDataSource failed." );
}

static void com_hisilicon_android_mediaplayer_himediaplayer_setDataSource(JNIEnv *env, jobject thiz, jstring path)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    com_hisilicon_android_mediaplayer_himediaplayer_setDataSourceAndHeaders(env, thiz, path, NULL, NULL);
}

static void com_hisilicon_android_mediaplayer_himediaplayer_setDataSourceFD(JNIEnv *env, jobject thiz, jobject fileDescriptor,
                                                                     jlong offset,
                                                                     jlong length)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    if (fileDescriptor == NULL)
    {
        jniThrowException(env, "java/lang/IllegalArgumentException", NULL);
        return;
    }

    int fd = jniGetFDFromFileDescriptor(env, fileDescriptor);
    LOGV("setDataSourceFD: fd %d", fd);
    process_media_player_call( env, thiz, mp->setDataSource(fd, offset,
                                                            length), "java/io/IOException", "setDataSourceFD failed." );
}

static void com_hisilicon_android_mediaplayer_himediaplayer_setVideoRange(JNIEnv *env, jobject thiz, int x, int y, int w,
                                                                   int h)
{
    LOGV("%s Call %s IN,x y w h is %d %d %d %d", LOG_TAG, __FUNCTION__, x, y, w, h);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }

    mp->updateVideoPosition(x, y, w, h);
}

static int com_hisilicon_android_mediaplayer_himediaplayer_SetStereoVideoFmt(JNIEnv *env, jobject thiz, int VideoFmt)
{
    LOGV("%s Call %s IN,VideoFmt is %d", LOG_TAG, __FUNCTION__, VideoFmt);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return UNKNOWN_ERROR;
    }

    return mp->SetStereoVideoFmt(VideoFmt);
}

static void com_hisilicon_android_mediaplayer_himediaplayer_SetStereoStrategy(JNIEnv *env, jobject thiz, int strategy)
{
    LOGV("%s Call %s IN", LOG_TAG, __FUNCTION__);
    sp <HiMediaPlayerManage> mp = getMediaPlayer(env, thiz);
    if (mp == NULL)
    {
        jniThrowException(env, "java/lang/IllegalStateException", NULL);
        return;
    }
    mp->SetStereoStrategy(strategy);
}

static JNINativeMethod gMethods[] = {
    {"native_init",              "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_native_init    },
    {"native_setup",             "(Ljava/lang/Object;)V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_native_setup   },
    {"setDataSource",            "(Ljava/lang/String;)V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_setDataSource    },
    {
        "_setDataSource",
        "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/String;)V",
        (void *)com_hisilicon_android_mediaplayer_himediaplayer_setDataSourceAndHeaders
    },
    {"setDataSource",            "(Ljava/io/FileDescriptor;JJ)V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_setDataSourceFD  },
    {"native_finalize",          "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_native_finalize  },
    {"prepareAsync",             "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_prepareAsync   },
    {"setVideoRange",           "(IIII)I",
     (void*)com_hisilicon_android_mediaplayer_himediaplayer_setVideoRange   },
    {"getVideoWidth",            "()I",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_getVideoWidth    },
    {"getVideoHeight",           "()I",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_getVideoHeight },
    {"native_setMetadataFilter", "(Landroid/os/Parcel;)I",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_setMetadataFilter },
    {"native_getMetadata",       "(ZZLandroid/os/Parcel;)Z",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_getMetadata    },
    {"_start",                   "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_start        },
    {"getCurrentPosition",       "()I",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_getCurrentPosition},
    {"getDuration",              "()I",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_getDuration    },
    {"isPlaying",                "()Z",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_isPlaying      },
    {"_setSurfaceView",          "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_setSurfaceView },
    {"prepare",                  "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_prepare      },
    {"_stop",                    "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_stop       },
    {"seekTo",                   "(I)V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_seekTo     },
    {"_pause",                   "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_pause        },
    {"_release",                 "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_release      },
    {"_reset",                   "()V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_reset        },

    {"setLooping",          "(Z)V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_setLooping        },
    {"isLooping",           "()Z",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_isLooping         },
    {"setVolume",                "(FF)V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_setVolume      },
    {"native_invoke",            "(Landroid/os/Parcel;Landroid/os/Parcel;)I",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_invoke     },
    {"_SetStereoVideoFmt",             "(I)I",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_SetStereoVideoFmt },
    {"_SetStereoStrategy",             "(I)V",
     (void *)com_hisilicon_android_mediaplayer_himediaplayer_SetStereoStrategy },
};

static int register_com_hisilicon_android_mediaplayer_himediaplayer(JNIEnv *env)
{
    return AndroidRuntime::registerNativeMethods(env, "com/hisilicon/android/mediaplayer/HiMediaPlayer", gMethods,
                                                 NELEM(gMethods));
}

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env = NULL;
    jint result = -1;
    gJVM = vm;
    LOGV("HiMediaPlayer JNI Call\n");
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
    {
        LOGE("ERROR: GetEnv failed\n");
        goto bail;
    }

    assert(env != NULL);

    if (register_com_hisilicon_android_mediaplayer_himediaplayer(env) < 0)
    {
        LOGE("ERROR: AirPlayServerImpl native registraction failed\n");
        goto bail;
    }

    result = JNI_VERSION_1_4;
bail:
    return result;
}
