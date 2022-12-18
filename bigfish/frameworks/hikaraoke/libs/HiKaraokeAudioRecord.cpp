#define LOG_NDEBUG 0
#define LOG_TAG "HiKaraoeAudioRecord"

#include <sys/resource.h>
#include <sys/types.h>
#include <binder/IServiceManager.h>
#include <system/audio.h>
#include <utils/Log.h>

#include "IHiKaraokeRecord.h"
#include "HiKaraokeAudioRecord.h"


namespace android
{
    HiKaraokeAudioRecord::HiKaraokeAudioRecord()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        sp<IBinder> binder = defaultServiceManager()->getService(String16("hikaraokeservice"));
        mKaraokeService = interface_cast<IHiKaraokeService>(binder);

        if (mKaraokeService.get() == NULL)
        {
            ALOGE("Cannot connect to the hikaraoke Service.");
        }
    }

    HiKaraokeAudioRecord::~HiKaraokeAudioRecord()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
    }

    status_t HiKaraokeAudioRecord::getMinFrameCount(int* frameCount,
            uint32_t sampleRate,
            audio_format_t format,
            audio_channel_mask_t channelMask)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeAudioRecord::set(audio_source_t inputSource,
                                       uint32_t sampleRate,
                                       audio_format_t format,
                                       audio_channel_mask_t channelMask,
                                       int frameCount,
                                       callback_t cbf,
                                       void* user,
                                       int notificationFrames,
                                       bool threadCanCallJava,
                                       int sessionId)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        AutoMutex lock(mLock);

        /*  if(inputSource != 1000)
          {
              ALOGE("not karaoke audio source");
              return BAD_VALUE;
          }*/

        if (sessionId == 0 )
        {
            mSessionId = 0;
        }
        else
        {
            mSessionId = sessionId;
        }

        int channelCount = popcount(channelMask);

        int minFrameCount = 0;
        status_t status = getMinFrameCount(&minFrameCount, sampleRate, format, channelMask);
        if (status != NO_ERROR)
        {
            return status;
        }
        ALOGV("HiKaraokeAudioRecord::set() minFrameCount = %d", minFrameCount);

        if (frameCount == 0)
        {
            frameCount = minFrameCount;
        }
        else if (frameCount < minFrameCount)
        {
            return BAD_VALUE;
        }
        mHiKaraokeRecord = mKaraokeService->openKaraokeRecord(sampleRate, channelCount, frameCount);
        mMemory = mHiKaraokeRecord->getCblk();
        HiCircleBufCtrl* pCtrl = static_cast<HiCircleBufCtrl*>(mMemory->pointer());
        ALOGD("readPos = %d writePos = %d length = %d  addr = 0x%p", pCtrl->mReadPos,
              pCtrl->mWritePos, pCtrl->mBufLenght, mMemory->pointer());
        int8_t* pDataBuf = (int8_t*)(mMemory->pointer()) + sizeof(HiCircleBufCtrl);
        mHiCircleBufExeCutor = new HiCircleBufExeCutor(pCtrl, pDataBuf);

        mSampleRate = sampleRate;
        mFrameCount = frameCount;
        mStatus = NO_ERROR;
        mFormat = format;
        mChannelCount = (uint8_t)channelCount;
        mChannelMask = channelMask;
        mLatency = pCtrl->mBufLenght / sampleRate;
        mInputSource = inputSource;
        mInput = 1;
        mActive = false;

        return NO_ERROR;
    }

    status_t HiKaraokeAudioRecord::initCheck() const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return mStatus;
    }

    uint32_t HiKaraokeAudioRecord::latency() const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return mLatency;
    }

    audio_format_t HiKaraokeAudioRecord::format() const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return mFormat;
    }

    int HiKaraokeAudioRecord::channelCount() const
    {
        //   ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return mChannelCount;
    }

    uint32_t HiKaraokeAudioRecord::frameCount() const
    {
        //  ALOGD(" %s %d frameCount = %d", __FUNCTION__, __LINE__, mFrameCount);
        return mFrameCount;
    }

    size_t HiKaraokeAudioRecord::frameSize() const
    {
        //  ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        if (audio_is_linear_pcm(mFormat))
        {
            return channelCount() * audio_bytes_per_sample(mFormat);
        }
        else
        {
            return sizeof(uint8_t);
        }
    }

    audio_source_t HiKaraokeAudioRecord::inputSource() const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return mInputSource;
    }

    status_t HiKaraokeAudioRecord::start()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        status_t ret = NO_ERROR;

        AutoMutex lock(mLock);
        if (!mActive)
        {
            mActive = true;
            ret = mHiKaraokeRecord->start();
            if (ret != NO_ERROR)
            {
                mActive = false;
            }
        }
        return ret;
    }

    void HiKaraokeAudioRecord::stop()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        AutoMutex lock(mLock);
        if (mActive)
        {
            mActive = false;
            mHiKaraokeRecord->stop();
        }
    }

    bool HiKaraokeAudioRecord::stopped() const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        AutoMutex lock(mLock);
        return mActive;
    }

    uint32_t HiKaraokeAudioRecord::getSampleRate() const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return mSampleRate;
    }

    status_t HiKaraokeAudioRecord::setMarkerPosition(uint32_t marker)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeAudioRecord::getMarkerPosition(uint32_t* marker) const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeAudioRecord::setPositionUpdatePeriod(uint32_t updatePeriod)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeAudioRecord::getPositionUpdatePeriod(uint32_t* updatePeriod) const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeAudioRecord::getPosition(uint32_t* position) const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    audio_io_handle_t HiKaraokeAudioRecord::getInput() const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return mInput;
    }

    int HiKaraokeAudioRecord::getSessionId() const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return mSessionId;
    }

    /*   status_t HiKaraokeAudioRecord::obtainBuffer(Buffer* audioBuffer, int32_t waitCount)
       {
           ALOGD(" %s %d ", __FUNCTION__, __LINE__);
           return NO_ERROR;
       }

       void HiKaraokeAudioRecord::releaseBuffer(Buffer* audioBuffer)
       {
           ALOGD(" %s %d ", __FUNCTION__, __LINE__);
       }*/

    ssize_t HiKaraokeAudioRecord::read(void* buffer, size_t size)
    {
        if(mActive){
        return mHiCircleBufExeCutor->circleBufRead((int8_t*)buffer, size);
        }
        return 0;
    }

    unsigned int HiKaraokeAudioRecord::getInputFramesLost() const
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return 0;
    }


};
