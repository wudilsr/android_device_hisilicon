
#ifndef DECODE_SOURCE_H_

#define DECODE_SOURCE_H_

#include <media/stagefright/MediaSource.h>
#include <media/stagefright/MediaBufferGroup.h>
#include "HiMediaSource.h"

namespace android{

class HisiVideoSource : public MediaSource {
public:
    HisiVideoSource(const sp<MetaData> &format,
        HiMediaSource* source);

    virtual status_t start(MetaData *params = NULL);
    virtual status_t stop();

    virtual sp<MetaData> getFormat();

    virtual status_t read(
            MediaBuffer **buffer, const ReadOptions *options = NULL);

protected:
    virtual ~HisiVideoSource();

private:
    sp<MetaData> mFormat;

    HiMediaSource* mSource;

    bool mStarted;

    MediaBufferGroup *mGroup;

    MediaBuffer* mBuffer;

};

}
#endif
