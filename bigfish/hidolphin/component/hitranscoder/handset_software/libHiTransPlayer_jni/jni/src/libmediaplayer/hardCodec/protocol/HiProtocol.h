#ifndef _HI_PROTOCOL_H_
#define _HI_PROTOCOL_H_

//using namespace android;
#include "mediaPlayerListener.h"
#include <stdlib.h>
#include "HiMLoger.h"

#define TAG "HiProtocol"
class HiProtocol{
public:
    HiProtocol(const char* url){memset(mUrl, 0x00, 200);strncpy(mUrl, url, strlen(url));}
    virtual int connect(){MMLOGI(TAG, "HiProtocol::connect \n");};

    virtual int disconnect(){MMLOGI(TAG, "HiProtocol::disconnect \n");};
    virtual void setListener(MediaPlayerListener* listener){mlistener = listener;}
    char mUrl[200];
    MediaPlayerListener* mlistener;
    int bConnected;

protected:
    virtual ~HiProtocol(){};
};

#endif
