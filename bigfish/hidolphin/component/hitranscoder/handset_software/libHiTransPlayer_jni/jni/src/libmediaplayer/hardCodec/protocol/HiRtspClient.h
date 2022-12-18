#ifndef  _HI_RTSP_CLIENT_H_
#define _HI_RTSP_CLIENT_H_

#include "HiProtocol.h"

class HiRtspClient:public HiProtocol{
public:
    HiRtspClient(const char* url);
    int getSPSPPS(void* sps, int *spsSize, void* pps, int* ppsSize);
    int getVideoWidth();
    int getVideoHeight();
    int readVideoStream(void* ptr, int& dataSize, int64_t& pts, int& ptype);
    int readAudioStream(void* ptr, int& dataSize, int64_t& pts);
    virtual int connect();
    virtual int disconnect();
    virtual ~HiRtspClient();
};

#endif
