#ifndef _HI_FFMPEG_HANDLR_H_
#define _HI_FFMPEG_HANDLR_H_

#include <media/stagefright/MediaSource.h>
#include <media/stagefright/MediaBufferGroup.h>
#include "HiMediaHandlr.h"
#include "HiffmpegDecoder.h"
#include "HiProtocol.h"


namespace android{

class HiffmpegHandlr:public HiMediaHandlr{
public:
    HiffmpegHandlr(jobject jsurface, JNIEnv* env, MediaPlayerPCMWriter* pcmWriter, int apiVer, HiProtocol* protocol);
    void notify(int msg, int ext1, int ext2);
    int open();
    int close();
    int start();
    int stop();
    virtual int getWidth(int * width);
    virtual int getHeight(int* height);
    static void* startPlayVideo(void* ptr);
    static void* startPlayAudio(void * ptr);
    void* decodeMovie(void* ptr);
    void* decodeAudio(void* ptr);

protected:
    virtual ~HiffmpegHandlr();
    void configAudioRender(int chnlCnt, int sampleRate, int sample_fmt);
    int configNativeWindowRender(int width, int height);

private:
    void* pANWindow;
    JNIEnv* mjenv;
    MediaPlayerPCMWriter* mPCMWriter;
    AVFrame* mFrame;
    HiffmpegDecoder* mDecoder;
    int mWidth;
    int mHeight;
    int mPixFormat;
    int audConfigFlag;
    int vidConfigFlag;
    int mChnCnt;
    int mSampleRate;
    int mSampleFmt;
    int mOpened;
    pthread_t mAudThread;
    pthread_t mVidThread;
    int mRunning;
};
}
#endif
