#ifndef FFMPEG_DECODER_VIDEO_H
#define FFMPEG_DECODER_VIDEO_H
/*
 * Copyright (C) 2011 xuyangpo/x54178
*/
#include "decoder.h"

typedef void (*VideoDecodingHandler) (AVFrame*,double);
typedef int (*VideoChangeASR) (struct AVCodecContext *c);
class DecoderVideo : public IDecoder
{
public:
    DecoderVideo(AVStream* stream);
    ~DecoderVideo();
void    SetVideoFPS(int fps);
    VideoDecodingHandler        onDecode;
    VideoChangeASR onASRChange;
    int                         lostflag;
    void                        stop();
    bool                        mCheckLostFlag;
private:
    AVFrame*                    mFrame;
    double                        mVideoClock;
    double                        mFrameDuration;
    double                        mPlayedDuration;
    double                      mCheckSourceTime;
    int                            mFps;

    bool                        prepare();
    double                         synchronize(AVFrame *src_frame, double pts);
    bool                        decode(void* ptr);
    bool                        getLostFrameStatus();
    bool                        process(AVPacket *packet);
    static int                    getBuffer(struct AVCodecContext *c, AVFrame *pic);
    static void                    releaseBuffer(struct AVCodecContext *c, AVFrame *pic);
};

#endif //FFMPEG_DECODER_AUDIO_H
