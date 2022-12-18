#ifndef _HI_FFMPEG_DECODER_H_
#define _HI_FFMPEG_DECODER_H_

extern "C"
{
#include "libavcodec/avcodec.h"
}

namespace android{

class HiffmpegDecoder{
public:
    HiffmpegDecoder();
    int open();
    int close();
    int decodeVideo(AVFrame *outdata, int *outdata_size, AVPacket *avpkt);
    int decodeAudio(void *outdata, int *outdata_size, AVPacket *avpkt);
    int getVideoAttr(int* width, int* height, int* pixFormat);
    int getAudioAttr(int* chnlCnt, int* sampleRate, int* sample_fmt);

    virtual ~HiffmpegDecoder();
protected:
    int openVideoDecoder();
    int openAudioDecoder();
    static void ffmpegNotify(void* ptr, int level, const char* fmt, va_list vl);

private:
    AVCodecContext*  mVdoCodecCtx;
    AVCodecContext*  mAudCodecCtx;
    bool mFirstVideoFlag;
    bool mFirstAudioFlag;
    bool mRunning;
};
}
#endif
