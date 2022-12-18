/*
 * Copyright (C) 2011 xuyangpo/x54178
*/
#include <android/log.h>
#include "decoder_audio.h"
//#include "output.h"
#include "ahplayerdef.h"
#define TAG "FFMpegMediaPlayer"
extern AVPacket flushPkt;
extern int flushAD;

#if PERFORMANCETEST
#include "ClientLog.h"
double totaladecTime = 0;
extern double totalaFrames;
double totaladec_disTime = 0;
#endif
static double getTime()
{
    timeval pTime;
    gettimeofday(&pTime, NULL);
    return (pTime.tv_sec + (pTime.tv_usec / 1000000.0));
}

DecoderAudio::DecoderAudio(AVStream* stream) : IDecoder(stream)
{
}

DecoderAudio::~DecoderAudio()
{
}

void DecoderAudio::stop()
{
    __android_log_print(ANDROID_LOG_INFO, TAG, "DecoderAudio stop!");
    mRunning = false;
    IDecoder::stop();
}

bool DecoderAudio::prepare()
{
    mSamplesSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
    mSamples = (int16_t *) av_malloc(mSamplesSize);
    if(mSamples == NULL) {
        return false;
    }
    return true;
}

bool DecoderAudio::process(AVPacket *packet)
{
       if(packet->data == flushPkt.data)//flushAD)
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "flush audio codec");
            avcodec_flush_buffers(mStream->codec);
//            Output::AudioDriver_stop();
//            Output::AudioDriver_flush();
//            Output::AudioDriver_start();
//            flushAD = 0;
        bWaitingFlushCodec = false;
            return true;
        }
     else
     {
     #if PERFORMANCETEST
         double startTime = getTime();
     #endif
        int size = mSamplesSize;
        int len = avcodec_decode_audio3(mStream->codec, mSamples, &size, packet);
        long long pts;
        if (packet->dts != AV_NOPTS_VALUE)
        {
            int ret = 0;
            pts = packet->dts;
//            ret = av_rescale(pts, AV_TIME_BASE * (int64_t)mStream->time_base.num, mStream->time_base.den);
            mPTS = pts*av_q2d(mStream->time_base);
//            __android_log_print(ANDROID_LOG_INFO, TAG, "audio pts:%f",mPTS);
        }
#if PERFORMANCETEST
        double interval = (getTime() - startTime);
        ClientLog::logOut("audioDEC:\t%f",interval);
        totaladecTime += interval;
        totalaFrames += 1;
#endif
        //call handler for posting buffer to os audio driver
        onDecode(mSamples, size,mPTS);
#if PERFORMANCETEST
        interval = (getTime() - startTime);
        totaladec_disTime += interval;
        ClientLog::logOut("audioDec+Display:\t%f",interval);
#endif
        return true;
     }
}

bool DecoderAudio::decode(void* ptr)
{
    AVPacket        pPacket;
    int    bGet = 0;
    bool ret = true;

    __android_log_print(ANDROID_LOG_INFO, TAG, "decoding audio");
#if PERFORMANCETEST
    totaladecTime = 0;
    totalaFrames = 0;
    totaladec_disTime = 0;
    double startTime = getTime();
#endif
    while(mRunning)
    {
//        __android_log_print(ANDROID_LOG_INFO, TAG, "get pkt from audio queue");
        bGet = mQueue->get(&pPacket, bBlockGet);
//              __android_log_print(ANDROID_LOG_INFO, TAG, "decoding audio get over");
        if(bGet <= 0)
        {
            mRunning = false;
            ret = false;
            break;
        }

        if(!process(&pPacket))
        {
            mRunning = false;
            ret = false;
            break;
        }
//        __android_log_print(ANDROID_LOG_INFO, TAG, "decoding audio process over");
        // Free the packet that was allocated by av_read_frame
        av_free_packet(&pPacket);
    }
#if PERFORMANCETEST
    ClientLog::logOut("average audio decoding time: \t%f",(totalaFrames>1)?(totaladecTime/totalaFrames):(0));
    ClientLog::logOut("average audio display   time: \t%f",(totalaFrames>1)?((totaladec_disTime - totaladecTime)/totalaFrames):(0));
    ClientLog::logOut("average audio            fps: \t%f",(totalaFrames>1)?(totalaFrames/(getTime() - startTime)):(0));
    __android_log_print(ANDROID_LOG_ERROR, TAG, "average audio decoding time: \t%f",(totalaFrames>1)?(totaladecTime/totalaFrames):(0));
    __android_log_print(ANDROID_LOG_ERROR, TAG, "average audio display   time: \t%f",(totalaFrames>1)?((totaladec_disTime - totaladecTime)/totalaFrames):(0));
    __android_log_print(ANDROID_LOG_ERROR, TAG, "average audio            fps: \t%f",(totalaFrames>1)?(totalaFrames/(getTime() - startTime)):(0));
#endif
    __android_log_print(ANDROID_LOG_INFO, TAG, "decoding audio onDecode NULL");
    onDecode(NULL, -1,-1);
    __android_log_print(ANDROID_LOG_INFO, TAG, "decoding audio ended");

    // Free audio samples buffer
    av_free(mSamples);
    __android_log_print(ANDROID_LOG_INFO, TAG, "decoding audio ended success");
    return ret;
}
