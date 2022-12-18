
#include "HiRtspVideoSource.h"
#include "HiMLoger.h"
#include <media/stagefright/MetaData.h>

#define TAG "HiRtspVideoSource"
namespace android{
HiRtspVideoSource::HiRtspVideoSource(HiRtspClient* protocol)
:mProto(protocol)
{

}

HiRtspVideoSource::~HiRtspVideoSource()
{

}

int HiRtspVideoSource::start()
{

}

int HiRtspVideoSource::stop()
{

}

int HiRtspVideoSource::read(MediaBuffer* pbuffer)
{
    MediaBuffer* buffer = pbuffer;
    int dataSize = buffer->size();
    void *ptr = (void *)buffer->data();
    int64_t pts = 0;
    int payloadType = 0;

    int ret =0;
    ret = mProto->readVideoStream(ptr, dataSize, pts, payloadType);
    if(ret != 0)
    {
        MMLOGI(TAG, "readVideoStream failed\n");
        return -1;
    }
    buffer->meta_data().clear();
    if(payloadType == 5)
    {
        buffer->meta_data()->setInt32(
                kKeyIsSyncFrame,  1);
    }
    buffer->meta_data()->setInt64(
            kKeyTime,  pts*1000);

    buffer->set_range(0, dataSize);
    return OK;
}
}
