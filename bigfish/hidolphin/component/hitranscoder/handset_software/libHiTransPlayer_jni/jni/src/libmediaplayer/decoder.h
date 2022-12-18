#ifndef FFMPEG_DECODER_H
#define FFMPEG_DECODER_H
/*
 * Copyright (C) 2011 xuyangpo/x54178
*/
extern "C" {

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

}

#include "thread.h"
#include "packetqueue.h"

class IDecoder : public Thread
{
public:
    IDecoder(AVStream* stream);
    ~IDecoder();

    void                        stop();
    void                        enqueue(AVPacket* packet);
    int                            packets();
    //add by x54178 for flush queue
    int flushQueue();
    //add by x54178 for Block Get
    bool bBlockGet;
    //add by x54178 for Signal the first frame after the flushPkt or start
    //用于视频，音频单独同步的场景
    bool bNeedFirstFrame;
    //是否等待ｃｏｄｅｃ清空，如果等待清空，则解码后的数据将被丢弃
    //否则，正常显示
    bool bWaitingFlushCodec;
protected:
    PacketQueue*                mQueue;
    AVStream*                     mStream;

    virtual bool                prepare();
    virtual bool                decode(void* ptr);
    virtual bool                process(AVPacket *packet);
    void                        handleRun(void* ptr);
};

#endif //FFMPEG_DECODER_H
