#include "HiOmxCodecDecoder.h"
#include "HiMLoger.h"
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <media/IMediaPlayerService.h>
#include <android_runtime/android_view_Surface.h>
#include <media/stagefright/OMXCodec.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/MediaBuffer.h>
#include "HisiVideoSource.h"


namespace android{
#define TAG "HiOmxCodecDecoder"

HiOmxCodecDecoder::HiOmxCodecDecoder(
    sp<ANativeWindow>& nativeWin,
    sp<MetaData>& format,
    HiMediaSource* source)
    :mANativeWindow(nativeWin),
    mformat(format),
    mSource(source)
{
    mVideoSource = NULL;
    mVideoTrack = NULL;
    mRunning = false;
    mClient.connect();
}

HiOmxCodecDecoder::~HiOmxCodecDecoder()
{
    mClient.disconnect();
}

int HiOmxCodecDecoder::open()
{
    int ret  = 0;
    if(!mRunning)
    {
        MMLOGI(TAG, "HiOmxCodecDecoder::open\n");
        ret = init_OmxCodec();
        if(ret >= OK)
            mRunning = true;
    }
    else
    {
        MMLOGI(TAG, "HiOmxCodecDecoder already opened\n");
    }
    return ret;
}

void HiOmxCodecDecoder::close()
{
    MMLOGI(TAG, "HiOmxCodecDecoder::close\n");
    if(mRunning)
    {
        MMLOGI(TAG, "deinit_OmxCodec\n");
        deinit_OmxCodec();
        mRunning= false;
    }
}

void HiOmxCodecDecoder::deinit_OmxCodec()
{
    if(mVideoSource!=NULL)
    {
        MMLOGI(TAG, "mVideoSource stop\n");
        mVideoSource->stop();

        // The following hack is necessary to ensure that the OMX
        // component is completely released by the time we may try
        // to instantiate it again.
        wp<MediaSource> tmp = mVideoSource;
        mVideoSource.clear();
        while (tmp.promote() != NULL) {
            usleep(1000);
        }
    }
}

int HiOmxCodecDecoder::init_OmxCodec()
{
    unsigned char avcC_data[256] = {0};
    int avcC_size = 256;
    uint32_t flags = 0;

    const char *mime = NULL;
    bool success = false;
    success = mformat->findCString(kKeyMIMEType, &mime);
    if(!success)
    {
        MMLOGI(TAG, "there no kKeyMIMEType error\n");
        return INVALID_OPERATION;
    }
    MMLOGI(TAG, "mime type: %s\n", mime);
    int64_t duration = 0;
    success = mformat->findInt64(kKeyDuration, &duration);
    if(!success)
    {
        MMLOGI(TAG, "there no kKeyDuration error\n");
        return INVALID_OPERATION;
    }
    MMLOGI(TAG, "duration: %d\n", duration);
    int32_t maxInputSize = 0;
    success = mformat->findInt32(kKeyMaxInputSize, &maxInputSize);
    if(!success)
    {
        MMLOGI(TAG, "there no kKeyMaxInputSize error\n");
        return INVALID_OPERATION;
    }
    MMLOGI(TAG, "maxInputSize: %d\n", maxInputSize);
    int32_t width = 0;
    success = mformat->findInt32(kKeyWidth, &width);
    if(!success)
    {
        MMLOGI(TAG, "there no kKeyWidth error\n");
        return INVALID_OPERATION;
    }
    MMLOGI(TAG, "width: %d\n", width);
    int32_t height = 0;
    success = mformat->findInt32(kKeyHeight, &height);
    if(!success)
    {
        MMLOGI(TAG, "there no kKeyHeight error\n");
        return INVALID_OPERATION;
    }
    MMLOGI(TAG, "height: %d\n", height);
    MMLOGI(TAG,  "init_OmxCodec");
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder = sm->getService(String16("media.player"));
    sp<IMediaPlayerService> service =
        interface_cast<IMediaPlayerService>(binder);
    sp<IOMX> omx = service->getOMX();
    Vector<CodecCapabilities> results;
    QueryCodecs(omx, MEDIA_MIMETYPE_VIDEO_AVC, true, &results);
    for (size_t i = 0; i < results.size(); ++i)
    {
        MMLOGI(TAG, "decoder '%s' supports ",results[i].mComponentName.string());
        if (results[i].mColorFormats.size() > 0)
        {
            for (size_t j = 0; j < results[i].mColorFormats.size() ; ++j)
            {
                MMLOGI(TAG, "mColorFormats supports %d ",results[i].mColorFormats[j]);
            }
        }
    }

    mVideoTrack = new HisiVideoSource(mformat, mSource);
    flags |= OMXCodec::kOnlySubmitOneInputBufferAtOneTime;
    mVideoSource = OMXCodec::Create(
            mClient.interface(), mVideoTrack->getFormat(),
            false, // createEncoder
            mVideoTrack,
            NULL, flags, mANativeWindow);
    if (mVideoSource != NULL)
    {
        status_t err = mVideoSource->start();

        if (err != OK) {
            mVideoSource.clear();
            return err;
        }
    }
    else
    {
        MMLOGI(TAG, "OMXCodec::Create failed ");
        return INVALID_OPERATION;
    }

    if (mVideoSource != NULL)
    {
        const char *componentName;
        int32_t colorFormat = 0;
        mVideoSource->getFormat()->findCString(kKeyDecoderComponent, &componentName);
        MMLOGI(TAG, "componentName: %s", componentName);
        mVideoSource->getFormat()->findInt32(kKeyColorFormat, &colorFormat);
        MMLOGI(TAG, "colorFormat: %d", colorFormat);
    }
    return NO_ERROR;
}


int HiOmxCodecDecoder::read_omx_data(MediaBuffer ** mVideoBuffer)
{
    MediaSource::ReadOptions options;

    if(!mRunning)
    {
        MMLOGI(TAG, "HiOmxCodecDecoder have not been started  %d");
        return -1;
    }
    status_t err = mVideoSource->read(mVideoBuffer, &options);
    if (err != OK)
    {
        MMLOGI(TAG, "read_omx_data error  %d", err);
    }

    return err;
}
}
