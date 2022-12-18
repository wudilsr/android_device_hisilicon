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

#ifndef ANDROID_HIMEDIAPLAYER_BASE_H
#define ANDROID_HIMEDIAPLAYER_BASE_H

#ifdef __cplusplus

#include <sys/types.h>
#include <utils/Errors.h>
#include <utils/KeyedVector.h>
#include <utils/String8.h>
#include <utils/RefBase.h>
#include <gui/IGraphicBufferProducer.h>
#include <gui/Surface.h>

#include "MediaPlayerInterface.h"
#include "HiMetadata.h"

namespace android {

class Parcel;
class Surface;
class ISurfaceTexture;

// callback mechanism for passing messages to MediaPlayer object
typedef void (*notify_callback_f)(void* cookie, int msg, int ext1, int ext2, const Parcel *obj);

// abstract base class - use MediaPlayerInterface
class HiMediaPlayerBase : public RefBase
{
public:

                        HiMediaPlayerBase() : mCookie(0), mNotify(0) {}
    virtual             ~HiMediaPlayerBase() {}
    virtual status_t    initCheck() = 0;

    virtual status_t    setUID(uid_t uid) {
        return INVALID_OPERATION;
    }

    virtual status_t    setDataSource(
            const char *url,
            const KeyedVector<String8, String8> *headers = NULL) = 0;

    virtual status_t    setDataSource(int fd, int64_t offset, int64_t length) = 0;

    //add for surface position adjust, subsurface
    //add for VO attribution adjust
    virtual status_t    setSurfaceTexture(const sp<IGraphicBufferProducer> &bufferProducer) {
        ALOGE("HiMediaPlayerBase::setSurfaceTexture not implemented");
        return OK;
    }

    virtual status_t    setSubSurface(const sp<Surface>& surface) {return NO_ERROR;};  // set subtitile surface
    virtual status_t    updateVideoPosition(int x,int y,int w,int h){return 0;};
    virtual status_t    setOutRange(int left, int top, int width, int height){return 0;};
    virtual status_t    setVideoRatio(int width, int height){return 0;};
    virtual status_t    setVideoScaling(int scalingmode){return 0;};
    virtual status_t    setVideoCvrs(int cvrs){return 0;};
    virtual status_t    setVolume(float leftVolume, float rightVolume){return 0;};
    virtual status_t    setAudioStreamType(int streamType)  { mAudioStreamType = streamType; return 0; } // add for hiplayer volume adjust
    virtual int         getAudioStreamType() { return mAudioStreamType; }// add for hiplayer volume adjust
    virtual void        setAudioSink(const sp<MediaPlayerBase::AudioSink> &audioSink) {};//;

    virtual status_t    prepare() = 0;
    virtual status_t    prepareAsync() = 0;
    virtual status_t    start() = 0;
    virtual status_t    stop() = 0;
    virtual status_t    pause() = 0;
    virtual bool        isPlaying() = 0;
    virtual status_t    seekTo(int msec) = 0;
    virtual status_t    getCurrentPosition(int *msec) = 0;
    virtual status_t    getDuration(int *msec) = 0;
    virtual status_t    reset() = 0;
    virtual status_t    setLooping(int loop) = 0;
    virtual Hi_PLAYER_TYPE playerType() = 0;
    virtual status_t    SetStereoVideoFmt(int VideoFmt) = 0;
    virtual void        SetStereoStrategy(int Strategy) = 0;
    virtual status_t    setSubFramePack(int type) = 0;
    virtual status_t    getTrackInfo(Parcel* reply)=0;
    virtual status_t    AddTimedTextSource(const Parcel& request)=0;
    virtual status_t    selectTrack(int trackIndex, bool select)=0;
    virtual int SetOrigAndroidPath(int flag) =0;
    virtual status_t    getParameter(int key, Parcel *reply) = 0;
    virtual status_t    setParameter(int key, const Parcel &request) = 0;
    // Invoke a generic method on the player by using opaque parcels
    // for the request and reply.
    //
    // @param request Parcel that is positioned at the start of the
    //                data sent by the java layer.
    // @param[out] reply Parcel to hold the reply data. Cannot be null.
    // @return OK if the call was successful.
    virtual status_t    invoke(const Parcel& request, Parcel *reply) = 0;

    // The Client in the MetadataPlayerService calls this method on
    // the native player to retrieve all or a subset of metadata.
    //
    // @param ids SortedList of metadata ID to be fetch. If empty, all
    //            the known metadata should be returned.
    // @param[inout] records Parcel where the player appends its metadata.
    // @return OK if the call was successful.
    virtual status_t    getMetadata(const media::HiMetadata::Filter& ids,
                                    Parcel *records) {
        return INVALID_OPERATION;
    };


#ifdef BUILD_BD
    virtual void        setNotifyCallback(
#else
            void        setNotifyCallback(
#endif

            void* cookie, notify_callback_f notifyFunc) {
        Mutex::Autolock autoLock(mNotifyLock);
        mCookie = cookie; mNotify = notifyFunc;
    }

    void        sendEvent(int msg, int ext1=0, int ext2=0,
                          const Parcel *obj=NULL) {
        Mutex::Autolock autoLock(mNotifyLock);
        if (mNotify) mNotify(mCookie, msg, ext1, ext2, obj);
    }

    virtual status_t dump(int fd, const Vector<String16> &args) const {
        return INVALID_OPERATION;
    }

private:
    friend class MediaPlayerService;

    Mutex               mNotifyLock;
    void*               mCookie;
    notify_callback_f   mNotify;
    int                 mAudioStreamType;// add for hiplayer volume adjust
};



}; // namespace android

#endif // __cplusplus


#endif // ANDROID_MEDIAPLAYERINTERFACE_H
