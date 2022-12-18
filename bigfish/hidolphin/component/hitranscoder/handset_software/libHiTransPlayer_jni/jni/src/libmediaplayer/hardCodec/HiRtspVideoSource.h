#ifndef _HI_RTSP_VIDEO_SOURCE_H_
#define _HI_RTSP_VIDEO_SOURCE_H_

#include "HiMediaSource.h"
#include "HiRtspClient.h"

namespace android{

class HiRtspVideoSource:public HiMediaSource{
public:
    HiRtspVideoSource(HiRtspClient* protocol);

    virtual int start();
    virtual int stop();
    virtual int read(MediaBuffer* pbuffer);
    ~HiRtspVideoSource();

private:
    HiRtspClient* mProto;
};
}
#endif
