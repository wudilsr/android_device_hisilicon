#ifndef FFMPEG_DECODER_AUDIO_H
#define FFMPEG_DECODER_AUDIO_H
/*
 * Copyright (C) 2011 xuyangpo/x54178
*/
#include "decoder.h"

typedef void (*AudioDecodingHandler) (int16_t*,int,double pts);

class DecoderAudio : public IDecoder
{
public:
    DecoderAudio(AVStream* stream);

    ~DecoderAudio();

    AudioDecodingHandler        onDecode;
    void                        stop();
private:
    int16_t*                    mSamples;
    int                         mSamplesSize;
    double                mPTS;
    bool                        prepare();
    bool                        decode(void* ptr);
    bool                        process(AVPacket *packet);
};

#endif //FFMPEG_DECODER_AUDIO_H
