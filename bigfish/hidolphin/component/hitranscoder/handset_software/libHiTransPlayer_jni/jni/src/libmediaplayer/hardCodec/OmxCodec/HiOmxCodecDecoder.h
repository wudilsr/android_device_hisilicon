
#ifndef HI_OMXCODEC_DECODER_H
#define HI_OMXCODEC_DECODER_H

#include <jni.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/MediaSource.h>
#include <media/stagefright/MediaBufferGroup.h>
#include "mediaPlayerListener.h"
#include "HiMLoger.h"
#include <media/stagefright/OMXClient.h>
#include "HiMediaSource.h"

namespace android{

class HiOmxCodecDecoder:public RefBase{
public:
    HiOmxCodecDecoder(
        sp<ANativeWindow>& nativeWin,
        sp<MetaData>& format,
        HiMediaSource* source);

    void deinit_OmxCodec();
    int init_OmxCodec();
    int read_omx_data(MediaBuffer ** mVideoBuffer);
    int open();
    void close();
    virtual ~HiOmxCodecDecoder();

private:
    sp<ANativeWindow> mANativeWindow;
    sp<MediaSource> mVideoSource;
    sp<MediaSource> mVideoTrack;
    sp<MetaData> mformat;
    OMXClient mClient;
    HiMediaSource* mSource;
    bool mRunning;
};
}
#endif
