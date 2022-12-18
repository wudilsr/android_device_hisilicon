#ifndef _HI_OMXAL_DECODER_H_
#define _HI_OMXAL_DECODER_H_

#include <jni.h>
#include <media/stagefright/MediaSource.h>
#include <media/stagefright/MediaBufferGroup.h>
#include <android/native_window_jni.h>
#include "HiMediaSource.h"

namespace android{

class HiOmxALDecoder{
public:
    HiOmxALDecoder(jobject jsurface, JNIEnv* env, HiMediaSource* source);
    int open();
    int close();
    int start();
    int stop();
    int read(void* ptr, size_t* dataSize);

protected:
    virtual ~HiOmxALDecoder();

private:
    ANativeWindow* mANativeWindow;
    HiMediaSource* mSource;
    MediaBuffer* mbuffer;
    int mbAlreadyStart;
    int mReadThread;
    int mRunning;
};
}
#endif
