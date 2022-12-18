#define LOG_NDEBUG 0
#define LOG_TAG "HiKaraokeMediaRecord"

#include "HiKaraokeMediaRecord.h"
#include <utils/Log.h>
#include <utils/String8.h>
#include <sys/resource.h>
#include <binder/IServiceManager.h>
#include <sys/types.h>
#include <ctype.h>
#include <unistd.h>

namespace android
{
    HiKaraokeMediaRecord::HiKaraokeMediaRecord()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        mIsAudioSourceSet = false;
        mIsVideoSourceSet = false;
        mIsAudioEncoderSet = false;
        mIsVideoEncoderSet = false;
        mIsOutputFileSet = false;

        mSampleRate = 44100;
        mBitRate = 64000;
        mChannels = 2;
    }

    HiKaraokeMediaRecord::~HiKaraokeMediaRecord()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
    }

    void HiKaraokeMediaRecord::died()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
    }

    status_t HiKaraokeMediaRecord::initCheck()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }
    /*
        status_t HiKaraokeMediaRecord::setCamera(const sp<ICamera>& camera, const sp<ICameraRecordingProxy>& proxy)
        {
            ALOGD(" %s %d ", __FUNCTION__, __LINE__);
            return NO_ERROR;
        }

        status_t HiKaraokeMediaRecord::setPreviewSurface(const sp<Surface>& surface)
        {
            ALOGD(" %s %d ", __FUNCTION__, __LINE__);
            return NO_ERROR;
        }*/

    status_t HiKaraokeMediaRecord::setVideoSource(int vs)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        mIsVideoSourceSet = true;
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::setAudioSource(int as)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        mIsAudioSourceSet = true;
        mAudioSource = as;
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::setOutputFormat(int of)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        mOutputFormat = of;
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::setVideoEncoder(int ve)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        mIsVideoEncoderSet = true;
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::setAudioEncoder(int ae)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        mIsAudioEncoderSet = true;
        mAudioEncorder = ae;
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::setOutputFile(const char* path)
    {
        ALOGD(" %s %d  %s", __FUNCTION__, __LINE__, path);
        mIsOutputFileSet = true;
        strcpy(mPath, path);
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::setOutputFile(int fd, int64_t offset, int64_t length)
    {
        ALOGD(" %s %d fd = %d", __FUNCTION__, __LINE__, fd);
        mFd = fd;
        return getHiKaraokeService()->setOutputFile(fd, offset, length);
        // return 0;
    }

    status_t HiKaraokeMediaRecord::setVideoSize(int width, int height)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::setVideoFrameRate(int frames_per_second)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::setParameters(const String8& params)
    {
        ALOGD(" %s %d %s", __FUNCTION__, __LINE__, params.string());
        const char* key_start = params.string();
        const char* equal_pos = strchr(key_start, '=');
        if (equal_pos == NULL)
        {
            ALOGE("Parameters miss a value");
            return BAD_VALUE;
        }

        String8 key(key_start, equal_pos - key_start);

        const char* value_start = equal_pos + 1;
        const char* semicolon_pos = strchr(value_start, ';');
        String8 value;
        if (semicolon_pos == NULL)
        {
            value.setTo(value_start);
        }
        else
        {
            value.setTo(value_start, semicolon_pos - value_start);
        }

        if (key == "audio-param-encoding-bitrate")
        {
            if (safeStrToInt32(value.string(), &mBitRate))
            {
                ALOGD("get parameter bitrate = %d", mBitRate);
            }
        }
        else if (key == "audio-param-sampling-rate")
        {
            if (safeStrToInt32(value.string(), &mSampleRate))
            {
                ALOGD("get parameter sampleRate = %d", mSampleRate);
            }
        }
        else if (key == "audio-param-number-of-channels")
        {
            if (safeStrToInt32(value.string(), &mChannels))
            {
                ALOGD("get parameter Channels = %d", mChannels);
            }
        }
        else
        {
            ALOGE("unknown parameters");
        }


        return NO_ERROR;
    }

    /*    status_t HiKaraokeMediaRecord::setListener(const sp<MediaRecorderListener>& listener)
        {
            ALOGD(" %s %d ", __FUNCTION__, __LINE__);
            return NO_ERROR;
        }*/

    status_t HiKaraokeMediaRecord::prepare()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        if (mIsAudioSourceSet != mIsAudioEncoderSet)
        {
            ALOGE("AudioSource or AudioEncoder is ont set");
            return INVALID_OPERATION;
        }

        if (mIsVideoSourceSet != mIsVideoEncoderSet)
        {
            ALOGE("VideoSource or VideoEncoder is ont set");
            return INVALID_OPERATION;
        }

        getHiKaraokeService()->initHiKaraokeMediaRecord(mOutputFormat,
                mAudioEncorder, mSampleRate, mBitRate, mChannels);
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::getMaxAmplitude(int* max)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }
    status_t HiKaraokeMediaRecord::start()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return getHiKaraokeService()->setHiKaraokeMediaRecordState(RECORD_STATE_START);
    }

    status_t HiKaraokeMediaRecord::stop()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return getHiKaraokeService()->setHiKaraokeMediaRecordState(RECORD_STATE_STOP);
    }

    status_t HiKaraokeMediaRecord::reset()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::init()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::close()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return NO_ERROR;
    }

    status_t HiKaraokeMediaRecord::release()
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
        return getHiKaraokeService()->setHiKaraokeMediaRecordState(RECORD_STATE_RELEASE);
    }

    void HiKaraokeMediaRecord::notify(int msg, int ext1, int ext2)
    {
        ALOGD(" %s %d ", __FUNCTION__, __LINE__);
    }

    sp<IHiKaraokeService>& HiKaraokeMediaRecord::getHiKaraokeService()
    {
        sp<IBinder> binder = defaultServiceManager()->getService(String16("hikaraokeservice"));
        mKaraokeService = interface_cast<IHiKaraokeService>(binder);

        if (mKaraokeService.get() == NULL)
        {
            ALOGE("Cannot connect to the hikaraoke Service.");
        }
        return mKaraokeService;
    }

    bool HiKaraokeMediaRecord::safeStrToInt32(const char* s, int32_t* val)
    {
        int64_t temp;
        if (safeStrToInt64(s, &temp))
        {
            if (temp >= 0 && temp <= 0x007FFFFFFF)
            {
                *val = static_cast<int32_t>(temp);
                return true;
            }
        }
        return false;
    }

    bool HiKaraokeMediaRecord::safeStrToInt64(const char* s, int64_t* val)
    {
        char* end;

        // It is lame, but according to man page, we have to set errno to 0
        // before calling strtoll().
        errno = 0;
        *val = strtoll(s, &end, 10);

        if (end == s || errno == ERANGE)
        {
            return false;
        }

        // Skip trailing whitespace
        while (isspace(*end))
        {
            ++end;
        }

        // For a successful return, the string must contain nothing but a valid
        // int64 literal optionally surrounded by whitespace.

        return *end == '\0';
    }

}
