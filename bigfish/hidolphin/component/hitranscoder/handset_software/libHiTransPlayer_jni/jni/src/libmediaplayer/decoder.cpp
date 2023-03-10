/*
 * Copyright (C) 2011 xuyangpo/x54178
*/
#include <android/log.h>
#include "decoder.h"

#define TAG "FFMpegIDecoder"

IDecoder::IDecoder(AVStream* stream)
{
    mQueue = new PacketQueue();
    mStream = stream;
    bBlockGet = true;
    bNeedFirstFrame = true;
    bWaitingFlushCodec = false;
}

IDecoder::~IDecoder()
{
    if(mRunning)
    {
        stop();
    }
    free(mQueue);
    avcodec_close(mStream->codec);
}

void IDecoder::enqueue(AVPacket* packet)
{
    mQueue->put(packet);
}

int IDecoder::flushQueue()
{
    mQueue->flush();
    return 0;
}

int IDecoder::packets()
{
    return mQueue->size();
}

void IDecoder::stop()
{
    mQueue->abort();
    __android_log_print(ANDROID_LOG_INFO, TAG, "waiting on end of decoder thread");
    int ret = -1;
    if((ret = wait()) != 0) {
        __android_log_print(ANDROID_LOG_ERROR, TAG, "Couldn't cancel IDecoder: %i", ret);
        return;
    }
    __android_log_print(ANDROID_LOG_INFO, TAG, "IDecoder::stop exit");
}

void IDecoder::handleRun(void* ptr)
{
    if(!prepare())
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "Couldn't prepare decoder");
        return;
    }
    decode(ptr);
}

bool IDecoder::prepare()
{
    return false;
}

bool IDecoder::process(AVPacket *packet)
{
    return false;
}

bool IDecoder::decode(void* ptr)
{
    return false;
}
