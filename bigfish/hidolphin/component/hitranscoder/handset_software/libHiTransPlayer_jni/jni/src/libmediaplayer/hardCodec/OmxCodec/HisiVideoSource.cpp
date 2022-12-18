
#define TAG "FFMpegMediaPlayer"

#include "HisiVideoSource.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include <media/stagefright/MetaData.h>
#include "Hies_proto.h"
#include "HiMLoger.h"

namespace android{

HisiVideoSource::HisiVideoSource(
        const sp<MetaData> &format,
        HiMediaSource* source)
    : mFormat(format),
    mSource(source){
    const char *mime;
    bool success = mFormat->findCString(kKeyMIMEType, &mime);
    mStarted = false;
    mGroup = NULL;
    mBuffer= NULL;
    if(success == false)
        MMLOGI(TAG, "kKeyMIMEType is null");
}

HisiVideoSource::~HisiVideoSource() {
    if (mStarted) {
        stop();
    }
}

status_t HisiVideoSource::start(MetaData *params) {

    if(mStarted)
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "HisiVideoSource already started !!!!!");
        return OK;
    }
    MMLOGI(TAG, "HisiVideoSource  start !!!!!");
    mGroup = new MediaBufferGroup;

    int32_t max_size;
    if(!(mFormat->findInt32(kKeyMaxInputSize, &max_size))){
        MMLOGI(TAG, "kKeyMaxInputSize  null !!!!!");
        return INVALID_OPERATION;
    }
    mBuffer = new MediaBuffer(max_size);
    mGroup->add_buffer(mBuffer);
    //mGroup->add_buffer(new MediaBuffer(max_size));
    mSource->start();
    mStarted = true;

    return OK;
}

status_t HisiVideoSource::stop() {
    if(!mStarted)
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "HisiVideoSource have not been started !!!!!");
        return OK;
    }
    __android_log_print(ANDROID_LOG_INFO, TAG, "HisiVideoSource  stop !!!!!");
    if(mBuffer)
    {
        int refcnt = mBuffer->refcount();
        __android_log_print(ANDROID_LOG_INFO, TAG, "HisiVideoSource buffer refcnt: %d   !!!!!", refcnt);
        for(;refcnt > 0; --refcnt)
            mBuffer->release();
    }
    if(mGroup)
    {
        delete mGroup;
        mGroup = NULL;
    }

    mStarted = false;

    return OK;
}

sp<MetaData> HisiVideoSource::getFormat() {

    return mFormat;
}

status_t HisiVideoSource::read(
        MediaBuffer **out, const ReadOptions *options) {

    if(!mStarted)
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "HisiVideoSource have not been started !!!!!");
        return INVALID_OPERATION;
    }
    //MMLOGI(TAG, "HisiVideoSource  read !!!!!");
    *out = NULL;
    MediaBuffer *buffer;
    status_t err = mGroup->acquire_buffer(&buffer);

    if (err != OK) {
        return err;
    }

    err= mSource->read(buffer);
    if (err != OK) {
        return err;
    }
    *out = buffer;
}
}
