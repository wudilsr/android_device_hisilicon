#ifndef FFMPEG_MEDIAPLAYER_H
#define FFMPEG_MEDIAPLAYER_H
/*
 * Copyright (C) 2011 xuyangpo/x54178
*/
#include <pthread.h>

#include <jni.h>

#include <utils/Vector.h>
#include <utils/Errors.h>

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "mediaPlayerListener.h"
#include "HiRtspClient.h"
#include "HiMediaHandlr.h"

using namespace android;


// Info and warning codes for the media player framework.  These are non fatal,
// the playback is going on but there might be some user visible issues.
//
// Info and warning messages are communicated back to the client using the
// MediaPlayerListener::notify method defined below.  In this situation,
// 'notify' is invoked with the following:
//   'msg' is set to MEDIA_INFO.
//   'ext1' should be a value from the enum media_info_type.
//   'ext2' contains an implementation dependant info code to provide
//          more details. Should default to 0 when not used.
//
// The codes are distributed as follow:
//   0xx: Reserved
//   7xx: Android Player info/warning (e.g player lagging behind.)
//   8xx: Media info/warning (e.g media badly interleaved.)
//
enum media_info_type {
    // 0xx
    MEDIA_INFO_UNKNOWN = 1,
    // 7xx
    // The video is too complex for the decoder: it can't decode frames fast
    // enough. Possibly only the audio plays fine at this stage.
    MEDIA_INFO_VIDEO_TRACK_LAGGING = 700,
    // 8xx
    // Bad interleaving means that a media has been improperly interleaved or not
    // interleaved at all, e.g has all the video samples first then all the audio
    // ones. Video is playing but a lot of disk seek may be happening.
    MEDIA_INFO_BAD_INTERLEAVING = 800,
    // The media is not seekable (e.g live stream).
    MEDIA_INFO_NOT_SEEKABLE = 801,
    // New media metadata is available.
    MEDIA_INFO_METADATA_UPDATE = 802,

    MEDIA_INFO_FRAMERATE_VIDEO = 900,
    MEDIA_INFO_FRAMERATE_AUDIO,
};



enum media_player_states {
    MEDIA_PLAYER_IDLE               = 1 << 0,
    MEDIA_PLAYER_INITIALIZED        = 1 << 1,
    MEDIA_PLAYER_PREPARED           = 1 << 2,
    MEDIA_PLAYER_RUNNING            = 1 << 3,
    MEDIA_PLAYER_ERROR             = 1 << 4,
    MEDIA_PLAYER_STOPPING            = 1 << 5,
    MEDIA_PLAYER_STOPPED            = 1 << 5
};

class MediaPlayer
{
public:
    MediaPlayer();
    ~MediaPlayer();
    status_t        setDataSource(const char *url);
    status_t        setVideoSurface(JNIEnv* env, jobject jsurface,int apiVersion);
    status_t        setListener(MediaPlayerListener *listener);
    status_t        setPCMWriter(MediaPlayerPCMWriter *writer);
    status_t        start();
    status_t        stop();
    status_t        pause();
    bool            isPlaying();
    status_t        getVideoWidth(int *w);
    status_t        getVideoHeight(int *h);
    status_t        seekTo(int msec);
    status_t        getCurrentPosition(int *msec);
    status_t        getDuration(int *msec);
    status_t        reset();
    status_t        setAudioStreamType(int type);
    status_t        prepare();
    void            notify(int msg, int ext1, int ext2);
    status_t        suspend();
    status_t        resume();
    status_t setVideoDisplayMode(int mode);
    status_t setPlayerConfig(const char* configPath);
    int getAPIVersion();
    void setAPIVersion(int version);

private:
    double                         mTime;
    pthread_mutex_t             mLock;
    MediaPlayerPCMWriter*        mPCMWriter;
    AVFrame*                    mFrame;
    bool mbAlreadyStart;

    media_player_states         mCurrentState;
    int                         mVideoWidth;
    int                         mVideoHeight;
    int mAudioLatency;
    static double getTime();
    static double getMsTime();
    void* pANWindow;
    int mAPIVersion;
    jobject mjsurface;
    JNIEnv* mjenv;
    HiRtspClient* mClient;
    HiMediaHandlr* mMediaHandlr;
    MediaPlayerListener*     mListener;
};

#endif // FFMPEG_MEDIAPLAYER_H
