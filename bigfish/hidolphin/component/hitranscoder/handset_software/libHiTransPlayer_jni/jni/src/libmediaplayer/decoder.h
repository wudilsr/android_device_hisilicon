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
    //������Ƶ����Ƶ����ͬ���ĳ���
    bool bNeedFirstFrame;
    //�Ƿ�ȴ���������գ�����ȴ���գ�����������ݽ�������
    //����������ʾ
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
