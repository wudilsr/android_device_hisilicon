#ifndef HI_ASINK_H
#define HI_ASINK_H

#include <utils/RefBase.h>
#include <media/MediaPlayerInterface.h>
#include <hi_type.h>
#include <hi_svr_asink.h>

namespace android {
/**
 * An Android implementation of HI_SVR_ASINK_S.
 */
class HiASink
    : public HI_SVR_ASINK_S, public RefBase
{
public:
    HiASink(const sp<MediaPlayerBase::AudioSink> &audioSink);
protected:
    ~HiASink();
private:
    /**
     * hi_svr_sink implementations hooks
     */
    static int hook_open(HI_SVR_ASINK_S* asink, HI_SVR_ASINK_OPEN_PARAM* param,HI_SVR_ASINK_Callback cb, HI_VOID *cookie);
    static int hook_close(HI_SVR_ASINK_S* asink);
    static int hook_start(HI_SVR_ASINK_S* asink);
    static int hook_stop(HI_SVR_ASINK_S* asink);
    static int hook_pause(HI_SVR_ASINK_S* asink);
    static int hook_flush(HI_SVR_ASINK_S* asink);
    static int hook_control(HI_SVR_ASINK_S* asink, HI_U32 cmd, ...);
    static size_t HiASinkCallback(
           MediaPlayerBase::AudioSink *audioSink,
           void *buffer, size_t size, void *cookie,
           MediaPlayerBase::AudioSink::cb_event_t event);

    /**
     * hi_svr_sink implementations
     */
    int open(HI_SVR_ASINK_OPEN_PARAM *param, HI_SVR_ASINK_Callback cb, HI_VOID *cookie);
    int close();
    int start();
    int stop();
    int pause();
    int flush();
    int control(HI_U32 cmd, va_list);

    sp<MediaPlayerBase::AudioSink> mAudioSink;
    HI_SVR_ASINK_Callback mCallback;
    HI_VOID *mCookie;
};

}; // namespace android
#endif

