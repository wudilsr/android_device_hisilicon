#ifndef __HI_MEDIA_SOURCE_H__
#define __HI_MEDIA_SOURCE_H__

#include <media/stagefright/MediaBuffer.h>

namespace android{
class HiMediaSource:public RefBase{
public:
    HiMediaSource(){};
    virtual int start(){};
    virtual int stop(){};
    virtual int read(MediaBuffer* pbuffer){};
    virtual ~HiMediaSource(){};
};
}
#endif
