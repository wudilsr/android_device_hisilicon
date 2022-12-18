#include <utils/Log.h>
#include <utils/Trace.h>
#include "HiASink.h"

#define LOG_TAG "ASINK"

namespace android {

HiASink::HiASink(const sp<MediaPlayerBase::AudioSink> &audioSink): mAudioSink(audioSink)
{
    ALOGV("HiASink Construct");
    HI_SVR_ASINK_S::open      = hook_open;
    HI_SVR_ASINK_S::close     = hook_close;
    HI_SVR_ASINK_S::start     = hook_start;
    HI_SVR_ASINK_S::stop      = hook_stop;
    HI_SVR_ASINK_S::pause     = hook_pause;
    HI_SVR_ASINK_S::flush     = hook_flush;
}

HiASink::~HiASink()
{
    ALOGV("HiASink Desctruct");
}

static HiASink* getSelf(HI_SVR_ASINK_S* asink)
{
    return static_cast<HiASink*>(asink);
}

// static
size_t HiASink::HiASinkCallback(
        MediaPlayerBase::AudioSink *audioSink,
        void *buffer, size_t size, void *cookie,
        MediaPlayerBase::AudioSink::cb_event_t event) {
    HiASink *me = (HiASink *)cookie;
    HI_SVR_ASINK_S *asink = reinterpret_cast<HI_SVR_ASINK_S *>(
            dynamic_cast<HI_SVR_ASINK_S*>(me));

   // ALOGD("HiASinkCallback event %d", event);

    switch(event) {
    case MediaPlayerBase::AudioSink::CB_EVENT_FILL_BUFFER:
        return me->mCallback(asink, buffer, size, me->mCookie, HI_SVR_ASINK_EVENT_FILL_BUFFER);

    case MediaPlayerBase::AudioSink::CB_EVENT_STREAM_END:
        ALOGD("HiASinkCallback: stream end");
        return me->mCallback(asink, buffer, size, me->mCookie, HI_SVR_ASINK_EVENT_STREAM_END);
        break;

    case MediaPlayerBase::AudioSink::CB_EVENT_TEAR_DOWN:
        ALOGV("HiASinkCallback: Tear down event");
        break;
    }

    return 0;
}

int HiASink::hook_open(HI_SVR_ASINK_S* asink, HI_SVR_ASINK_OPEN_PARAM* param,HI_SVR_ASINK_Callback cb, HI_VOID *cookie)
{
    HiASink* s = getSelf(asink);

    ALOGD("HiASink hook_open");
    return s->open(param, cb, cookie);
}

int HiASink::hook_close(HI_SVR_ASINK_S* asink)
{
    HiASink* s = getSelf(asink);

    ALOGD("HiASink hook_close");
    return s->close();
}

int HiASink::hook_start(HI_SVR_ASINK_S* asink)
{
    HiASink* s = getSelf(asink);

    ALOGD("HiASink hook_start");
    return s->start();
}

int HiASink::hook_stop(HI_SVR_ASINK_S* asink)
{
    HiASink* s = getSelf(asink);

    ALOGD("HiASink hook_stop");
    return s->stop();
}

int HiASink::hook_pause(HI_SVR_ASINK_S* asink)
{
    HiASink* s = getSelf(asink);

    ALOGD("HiASink hook_pause");
    return s->pause();
}

int HiASink::hook_flush(HI_SVR_ASINK_S* asink)
{
    HiASink* s = getSelf(asink);

    ALOGD("HiASink hook_flush");
    return s->flush();
}

int HiASink::open(HI_SVR_ASINK_OPEN_PARAM *param, HI_SVR_ASINK_Callback cb, HI_VOID *cookie)
{
    audio_format_t format;
    audio_channel_mask_t channelMask = CHANNEL_MASK_USE_CHANNEL_ORDER;
    audio_output_flags_t flags = AUDIO_OUTPUT_FLAG_NONE;

    ALOGD("HiASink hook_open");

    if (mAudioSink.get() == NULL)
    {
        return NO_INIT;
    }

    mCallback = cb;
    mCookie = cookie;
    switch(param->u16BitPerSample)
    {
        case 8:
            format = AUDIO_FORMAT_PCM_8_BIT;
        case 16:
            format = AUDIO_FORMAT_PCM_16_BIT;
            break;
        case 24:
            format = AUDIO_FORMAT_PCM_8_24_BIT;// TODO::what's this
            break;
        case 32:
            format = AUDIO_FORMAT_PCM_32_BIT;
            break;
        default:
             format = AUDIO_FORMAT_PCM_16_BIT;
    }

    ALOGD("HiASink hook_open with u32SampleRate:%u, channels:%hu, format:%d, flags:%d",
        param->u32SampleRate,  param->u16Channels, format, flags);

    return mAudioSink->open(param->u32SampleRate, param->u16Channels, channelMask, format,//
        DEFAULT_AUDIOSINK_BUFFERCOUNT, &HiASink::HiASinkCallback, this, flags, NULL);
}

int HiASink::close()
{
    if (mAudioSink.get() == NULL)
    {
        return NO_INIT;
    }

    mAudioSink->close();

    return NO_ERROR;
}

int HiASink::start()
{
    if (mAudioSink.get() == NULL)
    {
        return NO_INIT;
    }

    return mAudioSink->start();;
}

int HiASink::stop()
{
    if (mAudioSink.get() == NULL)
    {
        return NO_INIT;
    }

    mAudioSink->stop();

    return NO_ERROR;
}

int HiASink::pause()
{
    if (mAudioSink.get() == NULL)
    {
        return NO_INIT;
    }

    mAudioSink->pause();

    return NO_ERROR;
}

int HiASink::flush()
{
    if (mAudioSink.get() == NULL)
    {
        return NO_INIT;
    }

    mAudioSink->flush();

    return NO_ERROR;
}

int HiASink::control(HI_U32 cmd, va_list)
{
    return NO_ERROR;
}

}

