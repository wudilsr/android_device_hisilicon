#ifndef _HIKARAOKEAUDIORECORD_H_
#define _HIKARAOKEAUDIORECORD_H_

#include "IHiKaraokeRecord.h"
#include "IHiKaraokeService.h"
#include "HiCircleBuf.h"

#include <utils/Mutex.h>

namespace android
{
    typedef void (*callback_t)(int event, void* user, void* info);

    class HiKaraokeAudioRecord : virtual public RefBase
    {
    public:
        HiKaraokeAudioRecord();

        virtual ~HiKaraokeAudioRecord();
        static status_t getMinFrameCount(int* frameCount,
                                         uint32_t sampleRate,
                                         audio_format_t format,
                                         audio_channel_mask_t channelMask);


        status_t    set(audio_source_t inputSource = AUDIO_SOURCE_DEFAULT,
                        uint32_t sampleRate = 0,
                        audio_format_t format = AUDIO_FORMAT_DEFAULT,
                        audio_channel_mask_t channelMask = AUDIO_CHANNEL_IN_MONO,
                        int frameCount      = 0,
                        callback_t cbf = NULL,
                        void* user = NULL,
                        int notificationFrames = 0,
                        bool threadCanCallJava = false,
                        int sessionId = 0);

        status_t    initCheck() const;

        uint32_t    latency() const;

        audio_format_t format() const;

        int         channelCount() const;

        uint32_t    frameCount() const;

        size_t      frameSize() const;

        audio_source_t inputSource() const;

        status_t    start();

        void        stop();

        bool        stopped() const;

        uint32_t    getSampleRate() const;

        /*unimplement  start*/
        status_t    setMarkerPosition(uint32_t marker);

        status_t    getMarkerPosition(uint32_t* marker) const;

        status_t    setPositionUpdatePeriod(uint32_t updatePeriod);

        status_t    getPositionUpdatePeriod(uint32_t* updatePeriod) const;

        status_t    getPosition(uint32_t* position) const;

        audio_io_handle_t    getInput() const;

        int    getSessionId() const;
        /*unimplement  end*/

        //       status_t    obtainBuffer(Buffer* audioBuffer, int32_t waitCount);

        //       void        releaseBuffer(Buffer* audioBuffer);

        ssize_t     read(void* buffer, size_t size);

        /*unimplement  start*/
        unsigned int  getInputFramesLost() const;
        /*unimplement  end*/
    private:
        uint32_t                mFrameCount;
        audio_format_t          mFormat;
        uint8_t                 mChannelCount;
        audio_source_t          mInputSource;
        status_t                mStatus;
        uint32_t                mLatency;
        uint32_t                mSampleRate;
        audio_channel_mask_t    mChannelMask;
        audio_io_handle_t       mInput;
        int                     mSessionId;

        sp<IHiKaraokeService>   mKaraokeService;
        sp<IHiKaraokeRecord>    mHiKaraokeRecord;
        sp<IMemory>             mMemory;
        sp<HiCircleBufExeCutor> mHiCircleBufExeCutor;

        mutable Mutex           mLock;
        bool                    mActive;



    };
};

#endif
