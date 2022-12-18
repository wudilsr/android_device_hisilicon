// IPlayer.h: interface for the IPlayer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _ANDROID_IPLAYER_H_
#define _ANDROID_IPLAYER_H_


#include "HiMediaDefine.h"
#include <EGL/egl.h>

extern "C"{

#include "hi_svr_player.h"


 typedef void (* IPlay_notify_callback_f)(void* cookie,
        int msg, int ext1, int ext2, const void *obj);

enum IPlay_media_event_type {
    IPlay_MEDIA_NOP               = 0, // interface test message
    IPlay_MEDIA_PREPARED          = 1,
    IPlay_MEDIA_PLAYBACK_COMPLETE = 2,
    IPlay_MEDIA_BUFFERING_UPDATE  = 3,
    IPlay_MEDIA_SEEK_COMPLETE     = 4,
    IPlay_MEDIA_SET_VIDEO_SIZE    = 5,
    IPlay_MEDIA_ERROR             = 100,
    IPlay_MEDIA_INFO              = 200,
};


enum IPlay_media_info_type {
    // 0xx
    IPlay_MEDIA_INFO_UNKNOWN = 1,
    // 7xx
    // The video is too complex for the decoder: it can't decode frames fast
    // enough. Possibly only the audio plays fine at this stage.
    IPlay_MEDIA_INFO_VIDEO_TRACK_LAGGING = 700,
    // 8xx
    // Bad interleaving means that a media has been improperly interleaved or not
    // interleaved at all, e.g has all the video samples first then all the audio
    // ones. Video is playing but a lot of disk seek may be happening.
    IPlay_MEDIA_INFO_BAD_INTERLEAVING = 800,
    // The media is not seekable (e.g live stream).
    IPlay_MEDIA_INFO_NOT_SEEKABLE = 801,
    // New media metadata is available.
    IPlay_MEDIA_INFO_METADATA_UPDATE = 802,


    IPlay_MEDIA_FAST_FORWORD_COMPLETE = android::MEDIA_FAST_FORWORD_COMPLETE,
    IPlay_MEDIA_FAST_BACKWORD_COMPLETE = android::MEDIA_FAST_BACKWORD_COMPLETE,
    IPlay_MEDIA_INFO_PREPARE_PROGRESS = android::MEDIA_INFO_PREPARE_PROGRESS,
        // Audio play fail
    IPlay_MEDIA_INFO_AUDIO_FAIL = android::MEDIA_INFO_AUDIO_FAIL,
        // Video play fail
    IPlay_MEDIA_INFO_VIDEO_FAIL = android::MEDIA_INFO_VIDEO_FAIL,
        // network erro/unknown
    IPlay_MEDIA_INFO_NETWORK  = android::MEDIA_INFO_NETWORK,
        // time out
    IPlay_MEDIA_INFO_TIMEOUT  =  android::MEDIA_INFO_TIMEOUT,
        // media not support
    IPlay_MEDIA_INFO_NOT_SUPPORT  =  android::MEDIA_INFO_NOT_SUPPORT,
        //net-player buffer is empty
    IPlay_MEDIA_INFO_BUFFER_EMPTY  = android::MEDIA_INFO_BUFFER_EMPTY,
        //net-player buffer is starting
    IPlay_MEDIA_INFO_BUFFER_START  =  android::MEDIA_INFO_BUFFER_START,
        // net-player buffer is enough
    IPlay_MEDIA_INFO_BUFFER_ENOUGH  =  android::MEDIA_INFO_BUFFER_ENOUGH,
        // net-player buffer is full
    IPlay_MEDIA_INFO_BUFFER_FULL  =  android::MEDIA_INFO_BUFFER_FULL,
        // net-player buffer download finish
    IPlay_MEDIA_INFO_BUFFER_DOWNLOAD_FIN  = android::MEDIA_INFO_BUFFER_DOWNLOAD_FIN,
        // The Fist frame time
    IPlay_MEDIA_INFO_FIRST_FRAME_TIME = android::MEDIA_INFO_FIRST_FRAME_TIME,
        // stream 3D mode
    IPlay_MEDIA_INFO_STREM_3D_MODE = android::MEDIA_INFO_STREM_3D_MODE,
        // I frame error
    IPlay_MEDIA_INFO_STREM_IFRAME_ERROR = android::MEDIA_INFO_STREM_IFRAME_ERROR,
        // stream norm switch
    IPlay_MEDIA_INFO_STREM_NORM_SWITCH = android::MEDIA_INFO_STREM_NORM_SWITCH,

        //hiplayer Video INFO string,set only
    IPlay_KEY_PARAMETER_VIDEO_POSITION_INFO = android::KEY_PARAMETER_VIDEO_POSITION_INFO,
};


struct IPlay_URL_S
{
  char * uri;
  char * hostName;
  int port;
  char * userName;
  char * password;
  char * dir;
  char * isofile;
  char * fileName;
  char * protocol;
  char * fileType;
};


 bool IPlay_init(IPlay_URL_S *urls, void * p_cookie);
 void IPlay_release();
 int IPlay_setDataSource(const char *sHeader);
 int IPlay_prepare();
 int IPlay_start();
 int IPlay_stop();
 int IPlay_pause();
 bool IPlay_isPlaying();
 int IPlay_seekTo(int p_msec);
 int IPlay_getCurrentPosition(int *p_msec);
 int IPlay_getFileInfo(HI_FORMAT_FILE_INFO_S **ppstFileInfo);
 int IPlay_getStreamID(HI_SVR_PLAYER_STREAMID_S *streamID);
 int IPlay_reset();
 int IPlay_suspend();
 int IPlay_resume();
 void  IPlay_setNotifyCallback(void* p_cookie, IPlay_notify_callback_f p_notifyFunc);

 int IPlay_setLooping(int p_loop);
 int IPlay_setVolume(float p_leftVolume, float p_rightVolume);
 int IPlay_setOutRange(int p_left, int p_top, int p_width, int p_height);
 int IPlay_setSurfaceXY(int x,int y);
 int IPlay_setSurfaceWH(int w,int h);
 int IPlay_resetOutRange();
 int IPlay_setVideoRatio(int p_ratio);
 int IPlay_setVideoCvrs(int crvs);
 int IPlay_setMute(bool bOnOff);
 int IPlay_tplay(int speed);

 void IPlay_getSubString(unsigned char* pSubString);
 void IPlay_SetAudioStream(int iStream);
 int  IPlay_GetAudioStream();
 void IPlay_SetSubTitleDelay(float fValue);
 float IPlay_GetSubTitleDelay();
 int  IPlay_GetSubtitleCount();
 int  IPlay_GetSubtitle();
 void IPlay_GetSubtitleName(int iStream, char* pStrSubName);
 void IPlay_SetSubtitle(int iStream);
 bool IPlay_GetSubtitleVisible();
 void IPlay_SetSubtitleVisible(bool bVisible, ANativeWindow* pNativeWindow);
 bool IPlay_GetSubtitleExtension(char* pStrSubtitleExtension) { return false; }
 int  IPlay_AddSubtitle(const char* strSubPath);
 }
#endif // !defined(_ANDROID_IPLAYER_H_)
