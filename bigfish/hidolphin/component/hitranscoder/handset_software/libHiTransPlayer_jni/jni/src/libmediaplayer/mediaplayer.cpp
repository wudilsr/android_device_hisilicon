#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/log.h"
#include "../arm_neon/yuv2rgb_neon.h"
#include "Hies_client.h"
#include "Hies_proto.h"

} // end of extern C
#include <android/log.h>
#include "mediaplayer.h"
#include "ahplayerdef.h"
#include "yuv2rgb_neon.h"
#include "HiMLoger.h"
#include "HiffmpegHandlr.h"
#include "HiOmxCodecHandlr.h"
#include "mediaPlayerListener.h"

#define TAG "MediaPlayer"
MediaPlayer::MediaPlayer()
{
    mListener = NULL;
    mPCMWriter = NULL;
    mCurrentState = MEDIA_PLAYER_IDLE;
    mbAlreadyStart = false;
    pthread_mutex_init(&mLock, NULL);
    mVideoWidth = mVideoHeight = 0;
    pANWindow = NULL;
    mFrame = NULL;
    mAPIVersion = -1;
    mClient= NULL;
    mMediaHandlr = NULL;
}


MediaPlayer::~MediaPlayer()
{

}

/*配置音视频播放的一些参数*/
/* config some parameters of audio and video*/
status_t MediaPlayer::prepare()
{
    status_t ret;
    int err = 0;
    int apiVer = -1;
    if(mCurrentState != MEDIA_PLAYER_INITIALIZED)
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "prepare failed, status is not right");
        mCurrentState = MEDIA_PLAYER_ERROR;
        return INVALID_OPERATION;
    }

    if((apiVer= getAPIVersion()) == -1)
    {
        MMLOGE(TAG, "API version not initlized \n");
        mCurrentState = MEDIA_PLAYER_ERROR;
        return INVALID_OPERATION;
    }

    if(apiVer < 14)
    {
        mMediaHandlr = new HiffmpegHandlr(mjsurface, mjenv, mPCMWriter, mAPIVersion, mClient);
    }
    else
    {
        mMediaHandlr = new HiOmxCodecHandlr(mjsurface, mjenv, mPCMWriter, mAPIVersion, mClient);
    }
    if(!mListener)
    {
        MMLOGE(TAG, "setListener have not been execute ", ret);
        mCurrentState = MEDIA_PLAYER_ERROR;
        return INVALID_OPERATION;
    }
    mMediaHandlr->setListener(mListener);
    ret = mMediaHandlr->open();
    if(ret < 0)
    {
        MMLOGE(TAG, "openDecoder failed(%d)", ret);
        mCurrentState = MEDIA_PLAYER_ERROR;
        return INVALID_OPERATION;
    }
    mMediaHandlr->getWidth(&mVideoWidth);
    mMediaHandlr->getHeight(&mVideoHeight);
    MMLOGE(TAG, " video width: %d height: %d \n", mVideoWidth, mVideoHeight);
    notify(MEDIA_PLAYBACK_INFO, MEDIA_PLAYBACK_PREPARED, -1);
    mCurrentState = MEDIA_PLAYER_PREPARED;
    notify(MEDIA_ASR_CHANGE, -1, -1);
    MMLOGI(TAG, "prepare OK");
    return NO_ERROR;
}

/*设定player事件监听回调对象*/
/*set listener object for player event*/
status_t MediaPlayer::setListener(MediaPlayerListener* listener)
{
    MMLOGI(TAG, "setListener");
    mListener = listener;
    return NO_ERROR;
}

status_t  MediaPlayer::setPCMWriter(MediaPlayerPCMWriter *writer)
{
    MMLOGI(TAG, "setPCMWriter");
    mPCMWriter = writer;
    return NO_ERROR;
}

 int MediaPlayer::getAPIVersion()
 {
     return mAPIVersion;
 }
 void MediaPlayer::setAPIVersion(int version)
 {
     mAPIVersion = version;
 }

 /*设置服务器的URL*/
 /* set the server url*/
status_t MediaPlayer::setDataSource(const char *url)
{
    int err = 0;
    char tmpUrl[128] = "\0";

    MMLOGI(TAG, "setDataSource(%s)", url);
    if(mCurrentState != MEDIA_PLAYER_IDLE)
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "setDataSource, status is not right");
        mCurrentState = MEDIA_PLAYER_ERROR;
        return INVALID_OPERATION;
    }
    if(strlen(url) == 0)
    {
        MMLOGI(TAG, "Url is empty\n");
        mCurrentState = MEDIA_PLAYER_ERROR;
        return INVALID_OPERATION;
    }
    /*connect */
    mClient = new HiRtspClient(url);
    if(mListener)
        mClient->setListener(mListener);
    else
    {
        MMLOGI(TAG, "mListener is NULL\n");
        mCurrentState = MEDIA_PLAYER_ERROR;
        return INVALID_OPERATION;
    }
    err = mClient->connect();
    if(err != OK)
    {
        MMLOGI(TAG, "protocol connect failed\n");
        mCurrentState = MEDIA_PLAYER_ERROR;
        return INVALID_OPERATION;
    }
    MMLOGI(TAG, "HI_HIES_Connect OK");

    mCurrentState = MEDIA_PLAYER_INITIALIZED;
    return NO_ERROR;
}

/*player 去初始化借口*/
/*Dinit interface for player*/
status_t MediaPlayer::suspend() {
    MMLOGI(TAG, "suspend");
    //if is paused, decoder thread will be blocked, so we set state = started
    if(mCurrentState == MEDIA_PLAYER_STOPPED
        || mCurrentState == MEDIA_PLAYER_STOPPING)
    {
        MMLOGI(TAG, "already player released or being released  state : %d\n", mCurrentState);
        return NO_ERROR;
    }
    mCurrentState = MEDIA_PLAYER_STOPPING;
    if(mMediaHandlr)
    {
        mMediaHandlr->stop();
        mMediaHandlr->close();
        delete mMediaHandlr;
        mMediaHandlr = NULL;
    }

    if(mClient)
    {
        mClient->disconnect();
        delete mClient;
        mClient = NULL;
    }

    MMLOGI(TAG, "suspended");
    mCurrentState = MEDIA_PLAYER_STOPPED;
    return NO_ERROR;
}

status_t MediaPlayer::resume()
{
    MMLOGI(TAG, "resume no impliment");
    return NO_ERROR;
}

/*从java层传递surface 对象到Cpp层，注册该surface, 以显示视频*/
/*deliver from java to cpp through jni, register this surface for video display*/
status_t MediaPlayer::setVideoSurface(JNIEnv* env, jobject jsurface,int apiVersion)
{
        /*注册surface 到Native Window, 并返回window实例*/
        /*register the surface to Native Window, return instance of window*/
    setAPIVersion(apiVersion);
    mjsurface = jsurface;
    mjenv = env;
    return NO_ERROR;
}

/*启动音视频播放*/
/*start the audio and video play */
status_t MediaPlayer::start()
{
    int ret = 0;
    if (mCurrentState != MEDIA_PLAYER_PREPARED)
    {
        MMLOGI(TAG, "player have not been prepared");
        return INVALID_OPERATION;
    }
    ret = mMediaHandlr->start();
    if(ret != 0)
    {
        MMLOGI(TAG, "mMediaHandlr start failed");
    }
    mCurrentState= MEDIA_PLAYER_RUNNING;
    return NO_ERROR;
}
/*stop player播放*/
/*stop player*/
status_t MediaPlayer::stop()
{
    return suspend();
}

bool MediaPlayer::isPlaying()
{
    return mCurrentState == MEDIA_PLAYER_RUNNING;
}
/*获取视频宽度*/
/*get video width*/
status_t MediaPlayer::getVideoWidth(int *w)
{
    if (mCurrentState < MEDIA_PLAYER_PREPARED) {
        return INVALID_OPERATION;
    }
    *w = mVideoWidth;
    return NO_ERROR;
}
/*获取视频高度*/
/*get video height*/
status_t MediaPlayer::getVideoHeight(int *h)
{
    if (mCurrentState < MEDIA_PLAYER_PREPARED) {
        return INVALID_OPERATION;
    }
    *h = mVideoHeight;
    return NO_ERROR;
}

/*no  use*/
status_t MediaPlayer::reset()
{
    MMLOGI(TAG, "reset no impliment");
    return INVALID_OPERATION;
}

/*到java的事件通知借口*/
/*the event notify interface to java*/
void MediaPlayer::notify(int msg, int ext1, int ext2)
{
    MMLOGI(TAG, "message received msg=%d, ext1=%d, ext2=%d", msg, ext1, ext2);
    bool send = true;
    bool locked = false;

    if ((mListener != 0) && send) {
       mListener->notify(msg, ext1, ext2);
       MMLOGI(TAG, "back from callback");
    }
}

double MediaPlayer::getTime()
{
    timeval pTime;
    gettimeofday(&pTime, NULL);
    return (pTime.tv_sec + (pTime.tv_usec / 1000000.0));
}

double MediaPlayer::getMsTime()
{
    timeval pTime;
    gettimeofday(&pTime, NULL);
    return (pTime.tv_sec * 1000 + (pTime.tv_usec / 1000.0));
}

status_t MediaPlayer::setVideoDisplayMode(int mode)
{
    MMLOGI(TAG, "setVideoDisplayMode no impliment");
    return NO_ERROR;
}

status_t MediaPlayer::setPlayerConfig(const char* configPath)
{
    MMLOGI(TAG, "setPlayerConfig no impliment");
    return NO_ERROR;
}

status_t MediaPlayer::pause()
{
    MMLOGI(TAG, "pause no impliment");
    return NO_ERROR;
}

status_t MediaPlayer::getDuration(int *msec)
{
    MMLOGI(TAG, "getDuration no impliment");
    return NO_ERROR;
}

status_t MediaPlayer::setAudioStreamType(int type)
{
    MMLOGI(TAG, "setAudioStreamType no impliment");
    return NO_ERROR;
}

status_t MediaPlayer::getCurrentPosition(int *msec)
{
    MMLOGI(TAG, "getCurrentPosition no impliment");
    return NO_ERROR;
}

status_t MediaPlayer::seekTo(int msec)
{
    MMLOGI(TAG, "seekTo no impliment");
    return NO_ERROR;
}

