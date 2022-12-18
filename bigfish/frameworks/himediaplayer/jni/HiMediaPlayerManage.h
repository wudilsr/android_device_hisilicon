/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_HIMEDIAPLAYER_MANAGE_H
#define ANDROID_HIMEDIAPLAYER_MANAGE_H

#include <utils/KeyedVector.h>
#include <utils/String8.h>
#include <utils/RefBase.h>

#include "mediaplayer.h"
#include "HiMediaDefine.h"

#include "HiMediaPlayerBase.h"

class ANativeWindow;

namespace android
{
    class Surface;

    class HiMediaPlayerListener : virtual public RefBase
    {
public:
        virtual void  notify(int msg, int ext1, int ext2, const Parcel *obj) = 0;
    };

    class HiMediaPlayerManage : virtual public RefBase
    {
public:

        HiMediaPlayerManage();
        ~HiMediaPlayerManage();

        status_t    setDataSource(const char *url,
                                      const KeyedVector <String8, String8> *headers);

        status_t    setDataSource(int fd, int64_t offset, int64_t length);

        status_t    setListener(const sp <HiMediaPlayerListener>& listener);

        //z00180556 add begin
        //add for surface position adjust, subsurface
        status_t    setSubSurface(const sp <Surface>& surface);
        status_t    updateVideoPosition(int x, int y, int width, int height);
        status_t    prepare();
        status_t    prepareAsync();
        status_t    start();
        status_t    stop();
        status_t    pause();
        bool      isPlaying();
        status_t    getVideoWidth(int *w);
        status_t    getVideoHeight(int *h);
        status_t    seekTo(int msec);
        status_t    getCurrentPosition(int *msec);
        status_t    getDuration(int *msec);
        status_t    reset();
        status_t    setAudioStreamType(int type);
        status_t    setLooping(int loop);
        bool      isLooping();
        status_t    setVolume(float leftVolume, float rightVolume);
        static void   notify(void* cookie, int msg, int ext1, int ext2, const Parcel *obj = NULL);
        void      notifyFunc(int msg, int ext1, int ext2, const Parcel *obj = NULL);
        status_t    invoke(const Parcel& request, Parcel *reply);
        status_t    setMetadataFilter(const Parcel& filter);
        status_t    getMetadata(bool update_only, bool apply_filter, Parcel *metadata);
        status_t    setParameter(int key, const Parcel& request);
        status_t    getParameter(int key, Parcel* reply);
    status_t  SetStereoVideoFmt(int VideoFmt);
    void      SetStereoStrategy(int strategy);
        status_t    setSubFramePack(int type);
private:
        void PrintErrorInfo(int ext1,int ext2);
        status_t    attachNewPlayer(const sp <HiMediaPlayerBase>& player);
        sp <HiMediaPlayerBase> getPlayer(const char* url);
        Hi_PLAYER_TYPE  getPlayerType(const char* url);
        Hi_PLAYER_TYPE  getPlayerType(int fd, int64_t offset, int64_t length);
        sp <HiMediaPlayerBase> createPlayer(Hi_PLAYER_TYPE PlayerType, notify_callback_f notifyFunc);
        void      clear_l();
        status_t    seekTo_l(int msec);
        status_t    prepareAsync_l();
        status_t    getDuration_l(int *msec);
        status_t    reset_l();

        sp <HiMediaPlayerBase>         mPlayer;

        thread_id_t mLockThreadId;
        int mIsSeeking;
        int mIsStarting;
        Mutex mLock;
        Mutex mNotifyLock;
        Condition mSignal;
        sp <HiMediaPlayerListener>   mListener;
        void*                       mCookie;
        media_player_states mCurrentState;
        int mDuration;
        int mCurrentPosition;
        int mSeekPosition;
        bool mPrepareSync;
        status_t mPrepareStatus;
        int mStreamType;
        bool mLoop;
        float mLeftVolume;
        float mRightVolume;
        int mVideoWidth;
        int mVideoHeight;
        int mAudioSessionId;
        float mSendLevel;

        int mVideoSurfaceX;
        int mVideoSurfaceY;
        int mVideoSurfaceWidth;
        int mVideoSurfaceHeight;
    };
}; // namespace android

#endif // ANDROID_MEDIAPLAYER_H
