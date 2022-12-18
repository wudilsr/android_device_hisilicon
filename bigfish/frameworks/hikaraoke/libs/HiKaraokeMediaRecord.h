/* * Copyright (C) 2009 The Android Open Source Project *
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at *
*      http://www.apache.org/licenses/LICENSE-2.0 *
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License. */

//this module is only for karaoke
//most of the interface is unimplement

#ifndef _HIKARAOKEMEDIARECORD_H_
#define _HIKARAOKEMEDIARECORD_H_


#include "IHiKaraokeService.h"
#include <utils/String8.h>

#define MAX_FILEPATH_LEN (256)

namespace android
{
    enum RecordState
    {
        RECORD_STATE_START = 0,
        RECORD_STATE_PAUSE,
        RECORD_STATE_RESUME,
        RECORD_STATE_STOP,
        RECORD_STATE_RELEASE,
    };

    class HiKaraokeMediaRecord: virtual public RefBase
    {
    public:
        HiKaraokeMediaRecord();
        virtual ~HiKaraokeMediaRecord();

        /*unimplement  start*/
        void        died();
        status_t    initCheck();
        /*unimplement  end*/
        //  status_t    setCamera(const sp<ICamera>& camera, const sp<ICameraRecordingProxy>& proxy);
        //  status_t    setPreviewSurface(const sp<Surface>& surface);
        status_t    setVideoSource(int vs);
        status_t    setAudioSource(int as);
        status_t    setOutputFormat(int of);
        status_t    setVideoEncoder(int ve);
        status_t    setAudioEncoder(int ae);
        status_t    setOutputFile(const char* path);
        status_t    setOutputFile(int fd, int64_t offset, int64_t length);
        status_t    setVideoSize(int width, int height);
        status_t    setVideoFrameRate(int frames_per_second);
        status_t    setParameters(const String8& params);
        //    status_t    setListener(const sp<MediaRecorderListener>& listener);
        status_t    prepare();
        status_t    getMaxAmplitude(int* max);
        status_t    start();
        status_t    stop();
        status_t    reset();
        status_t    init();
        status_t    close();
        status_t    release();
        void        notify(int msg, int ext1, int ext2);
    private:
        bool        safeStrToInt32(const char* s, int32_t* val);
        bool        safeStrToInt64(const char* s, int64_t* val);


    private:
        sp<IHiKaraokeService>& getHiKaraokeService();
        sp<IHiKaraokeService> mKaraokeService;

        bool        mIsAudioSourceSet;
        bool        mIsVideoSourceSet;
        bool        mIsAudioEncoderSet;
        bool        mIsVideoEncoderSet;
        bool        mIsOutputFileSet;
        uint32_t    mAudioSource;
        uint32_t    mOutputFormat;
        uint32_t    mAudioEncorder;
        char        mPath[MAX_FILEPATH_LEN];
        int32_t     mFd;
        int32_t     mSampleRate;
        int32_t     mBitRate;
        int32_t     mChannels;


    };
}

#endif
