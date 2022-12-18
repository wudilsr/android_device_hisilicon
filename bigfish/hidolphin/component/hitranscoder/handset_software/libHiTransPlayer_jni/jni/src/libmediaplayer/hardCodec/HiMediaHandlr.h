#ifndef _HI_MEIDIA_HANDLR_H_
#define _HI_MEIDIA_HANDLR_H_
#include <jni.h>
#include "mediaPlayerListener.h"
#include "HiMLoger.h"
#include "HiProtocol.h"
#include <utils/RefBase.h>


using namespace android;

#define STREAM_MUSIC 3
#define CHANNEL_CONFIGURATION_MONO 2
#define CHANNEL_CONFIGURATION_STEREO 3
#define ENCODING_PCM_8BIT 3
#define ENCODING_PCM_16BIT 2
#define MODE_STREAM 1

class HiMediaHandlr:public RefBase{
public:
    HiMediaHandlr(jobject jsurface, int apiVer, HiProtocol* protocol)
        :mjsurface(jsurface),
        mApiVersion(apiVer),
        mProto(protocol){};
    virtual int open(){};
    virtual int close(){};
    virtual int start(){};
    virtual int stop(){};
    virtual void setListener(MediaPlayerListener* listener){mListener = listener;}
    virtual int getWidth(int * width){};
    virtual int getHeight(int* height){};
    ~HiMediaHandlr(){};

    MediaPlayerListener* mListener;
    jobject mjsurface;
    int mApiVersion;
    HiProtocol* mProto;
};
#endif
