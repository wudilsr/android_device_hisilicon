
#ifndef _HI_OMXCODEC_H_
#define _HI_OMXCODEC_H_
#include <jni.h>
#include "mediaPlayerListener.h"
#include "HiMediaSource.h"
#include <android/native_window_jni.h>
#include "HiOmxCodecDecoder.h"
#include "HiMediaHandlr.h"

namespace android{

class HiOmxCodecHandlr:public HiMediaHandlr{
public:
    HiOmxCodecHandlr(jobject jsurface,
        JNIEnv* env,
        MediaPlayerPCMWriter* PCMWriter,
        int apiVer,
        HiProtocol* protocol);
    int open();
    int close();
    int start();
    int stop();
    int getWidth(int * width);
    int getHeight(int* height);
    virtual ~HiOmxCodecHandlr();

protected:
    void configAudioRender(int chnlCnt, int sampleRate, int sample_fmt);
    int MakeAVCCodecSpecData(void* outbuf, int* outsize);
    void decodeMovie(void* ptr);
    void decodeAudio(void* ptr);
    static void* startPlayVideo(void* ptr);
    static void* startPlayAudio(void* ptr);

private:
    sp<MetaData> mformat;
    MediaBuffer *mVideoBuffer;
    MediaPlayerPCMWriter* mPCMWriter;
    ANativeWindow* mANativeWindow;
    sp<ANativeWindow> spWindow;
    HiMediaSource* mVideoSource;
    HiOmxCodecDecoder* mVideoDecoder;
    pthread_t mAudThread;
    pthread_t mVidThread;
    int mRunning;
    int mOpened;
    int mWidth;
    int mHeight;
};
}
#endif
