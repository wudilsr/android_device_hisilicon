/*
 * Copyright (C) 2011 xuyangpo/x54178
*/
#include <android/log.h>
#include "decoder_video.h"
#include "libsf/libsf.h"
#include "ahplayerdef.h"
#define TAG "FFMpegMediaPlayer1"
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t global_video_pkt_pts = AV_NOPTS_VALUE;
extern AVPacket flushPkt;

int totalFrames = 0;
#if PERFORMANCETEST
#include "ClientLog.h"
double totalvdecTime = 0;
double totalvdec_disTime = 0;
double maxFrameDecTime = 0;
#endif
#define SYNCWITHPTS 1
static double getTime()
{
    timeval pTime;
    gettimeofday(&pTime, NULL);
    return (pTime.tv_sec + (pTime.tv_usec / 1000000.0));
}

DecoderVideo::DecoderVideo(AVStream* stream) : IDecoder(stream)
{
    mStream->codec->get_buffer = getBuffer;
    mStream->codec->release_buffer = releaseBuffer;
    mVideoClock = 0;
    mFps = 0;
    mFrameDuration = 0;
    mPlayedDuration = 0;
}

DecoderVideo::~DecoderVideo()
{
}
void    DecoderVideo::SetVideoFPS(int fps)
{
    mFps = fps;
    mFrameDuration = 1.0/fps;
    mPlayedDuration = 0;
}
bool DecoderVideo::prepare()
{
    mFrame = avcodec_alloc_frame();
    if (mFrame == NULL) {
        return false;
    }
    return true;
}

double DecoderVideo::synchronize(AVFrame *src_frame, double pts) {

    double frame_delay;
    if(mFps != 0)
    {
        static int frameNum = 0;
        frameNum++;
        if(frameNum == mFps)
        {
            frameNum = 0;
            mPlayedDuration += 1;
            mVideoClock = mPlayedDuration;
        }
        pts = mVideoClock;
        mVideoClock += mFrameDuration;
        return pts;
    }
    if (pts > 0.001) {
        /* if we have pts, set video clock to it */
        mVideoClock = pts;
    } else {
        /* if we aren't given a pts, set it to the clock */
        pts = mVideoClock;
    }
    /* update the video clock */
    frame_delay = av_q2d(mStream->codec->time_base);
    /* if we are repeating a frame, adjust clock accordingly */
    frame_delay += src_frame->repeat_pict * (frame_delay * 0.5);
    mVideoClock += frame_delay;
    return pts;
}

bool DecoderVideo::process(AVPacket *packet)
{
    if(packet->data == flushPkt.data)
    {
        __android_log_print(ANDROID_LOG_INFO, TAG, "flush video codec");
        avcodec_flush_buffers(mStream->codec);
        bNeedFirstFrame = true;
        bWaitingFlushCodec = false;
        return true;
    }
    else
    {
        int    completed = 0;
        double pts = 0;
        int64_t llpts = 0;
#if PERFORMANCETEST
        double startTime = getTime();
        // Decode video frame
        __android_log_print(ANDROID_LOG_INFO, TAG, "avcodec_decode_video2 start");
#endif
        unsigned char* pData = packet->data;
        int decRet  = 0;
#if CHANGEASR
        if((*(unsigned int*)pData) == 0xffffffff)
        {//需要更新extradata
            __android_log_print(ANDROID_LOG_INFO, TAG,"*************New ExtraData***********");
            avcodec_close(mStream->codec);
            __android_log_print(ANDROID_LOG_INFO, TAG,"*************avcodec_close***********");
            if(mStream->codec->thread_count > 1)
            {
                avcodec_thread_init(mStream->codec, mStream->codec->thread_count );
            }
            if(mStream->codec->extradata)
            {
                av_free(mStream->codec->extradata);
            }
            mStream->codec->extradata_size = *(unsigned int*)(pData+4);
               mStream->codec->extradata = (unsigned char*)av_mallocz(mStream->codec->extradata_size + FF_INPUT_BUFFER_PADDING_SIZE);
               memcpy(mStream->codec->extradata, pData+8, mStream->codec->extradata_size);
            __android_log_print(ANDROID_LOG_INFO, TAG,"*************avcodec_open***********");
            avcodec_open(mStream->codec,avcodec_find_decoder(CODEC_ID_H264));
            packet->data = pData+8+mStream->codec->extradata_size;
            packet->size = packet->size - 8 - mStream->codec->extradata_size;
            __android_log_print(ANDROID_LOG_INFO, TAG,"*************avcodec_decode_video2***********");
               decRet = avcodec_decode_video2(mStream->codec,
                             mFrame,
                             &completed,
                             packet);
            packet->data = pData;
            packet->size = packet->size + 8 + mStream->codec->extradata_size;
            __android_log_print(ANDROID_LOG_INFO, TAG,"*************onASRChange***********");
            onASRChange(mStream->codec);
        }
        else
        {
            decRet = avcodec_decode_video2(mStream->codec,
                             mFrame,
                             &completed,
                             packet);
            if((decRet == -2 &&mStream->codec->codec_id == CODEC_ID_H264))
            {//分辨率发生了变化
                avcodec_close(mStream->codec);
                if(mStream->codec->thread_count > 1)
                {
                    avcodec_thread_init(mStream->codec, mStream->codec->thread_count);
                }
                avcodec_open(mStream->codec,avcodec_find_decoder(CODEC_ID_H264));
                   decRet = avcodec_decode_video2(mStream->codec,
                             mFrame,
                             &completed,
                             packet);
            }
        }
#else
        decRet = avcodec_decode_video2(mStream->codec,
                                     mFrame,
                                     &completed,
                                     packet);
#endif
#if PERFORMANCETEST
        __android_log_print(ANDROID_LOG_INFO, TAG, "avcodec_decode_video2 end");
        double interval = (getTime() - startTime);
        totalvdecTime += interval;
        if(interval > maxFrameDecTime)
        {
            maxFrameDecTime = interval;
        }
        ClientLog::logOut("VideoDEC: \t%f",interval);
#endif
#if SYNCWITHPTS
        if(mFrame->pkt_pts != AV_NOPTS_VALUE)
        {
            llpts = mFrame->pkt_pts;
        }
        else if (packet->dts == AV_NOPTS_VALUE && mFrame->opaque
                && *(uint64_t*) mFrame->opaque != AV_NOPTS_VALUE) {
#else
        if (packet->dts == AV_NOPTS_VALUE && mFrame->opaque
                && *(uint64_t*) mFrame->opaque != AV_NOPTS_VALUE) {
#endif
            llpts = *(uint64_t *) mFrame->opaque;
        } else if (packet->dts != AV_NOPTS_VALUE) {
            llpts = packet->dts;
        } else {
            llpts = 0;
        }
        pts = llpts*av_q2d(mStream->time_base);

        if (completed)
        {
#if PERFORMANCETEST
            __android_log_print(ANDROID_LOG_INFO, TAG, "synchronize start");
#endif
            pts = synchronize(mFrame, pts);
#if !RENDERINDECODER
#if PERFORMANCETEST
            __android_log_print(ANDROID_LOG_INFO, TAG, "onDecode start");
#endif
            onDecode(mFrame, pts);
#if PERFORMANCETEST
            __android_log_print(ANDROID_LOG_INFO, TAG, "onDecode end");
#endif
#endif
            totalFrames += 1;
#if PERFORMANCETEST
            interval = (getTime() - startTime);
            totalvdec_disTime += interval;
            ClientLog::logOut("VideoDEC+Display: \t%f",interval);
               __android_log_print(ANDROID_LOG_ERROR, TAG, "avcodec_decode_video2+onDecode %f",interval);
#endif
            return true;
        }
        return false;
    }
}
bool DecoderVideo::getLostFrameStatus()
{
    double nowTime = getTime();
    if(nowTime - mCheckSourceTime < 1)
    {
        return false;
    }
    mCheckSourceTime = nowTime;
    FILE* myfile = NULL;
    unsigned int d1,d2,d3,d4;
    unsigned int total2,busy2;
    static unsigned int total1 = 0;
    static unsigned int busy1 = 0;
    myfile = fopen("/proc/stat","r");
    if(myfile)
    {
        fscanf(myfile, "cpu  %u %u %u %u\n",&d1,&d2,&d3,&d4);
        fclose(myfile);
        total2 = d1 + d2 + d3 + d4;
        busy2 = d1 + d2 + d3;
        __android_log_print(ANDROID_LOG_ERROR,TAG,"CPU: Busy %u,Total %u\t",
            (busy2 - busy1),(total2-total1));
                  /*up to %80 will lost frame*/
        if(((busy2 - busy1)/5 +(busy2 - busy1))  > (total2-total1))
        {
            total1 = total2;
            busy1 = busy2;
            __android_log_print(ANDROID_LOG_ERROR,TAG,"video decoder begin lost frame!!");
            return true;
        }
        total1 = total2;
        busy1 = busy2;
        return false;
    }else
    {
        __android_log_print(ANDROID_LOG_ERROR,TAG,"not open cpu stat");
        return false;
    }

}

void DecoderVideo::stop()
{
    mRunning = false;
    __android_log_print(ANDROID_LOG_INFO, TAG, "DecoderVideo stop!");
    IDecoder::stop();
}


bool DecoderVideo::decode(void* ptr)
{
    AVPacket        pPacket;
    timeval pTime;
    static double t1 = -1;
    static double t2 = -1;
         int i = 0;

        bool LfirstFlag = true;
    __android_log_print(ANDROID_LOG_INFO, TAG, "decoding video");
    totalFrames = 0;
#if PERFORMANCETEST
    totalvdecTime = 0;
    totalvdec_disTime = 0;
    double startTime = getTime();
#endif
    while(mRunning)
    {
        if(0 == mQueue->size())
        {
            usleep(1000);
            continue;
        }
        if(mQueue->get(&pPacket, bBlockGet) <= 0)
        {
            mRunning = false;
            continue;
        }
#if 1
        /*lost 20 frames*/
        if(i<= 20)
        {
            i++;
            if(pPacket.flags != AV_PKT_FLAG_KEY)
            {
                av_free_packet(&pPacket);
                usleep(2000);
                __android_log_print(ANDROID_LOG_INFO, TAG, "drop 20 frame");
                continue;
            }
        }
        else
        {
            if(LfirstFlag && pPacket.flags != AV_PKT_FLAG_KEY)
            {
                av_free_packet(&pPacket);
                usleep(2000);
                __android_log_print(ANDROID_LOG_INFO, TAG, "there no key frame, drop again");
                continue;
            }
            else
            {
                LfirstFlag = false;
            }
        }


         if(true == getLostFrameStatus())
         {
            mCheckLostFlag = true;
            av_free_packet(&pPacket);
            usleep(2000);
            __android_log_print(ANDROID_LOG_INFO, TAG, "11 decoding free video");
            continue;
        }
        if(pPacket.flags == AV_PKT_FLAG_KEY)
        {
            mCheckLostFlag = false;
        }
        if(true == mCheckLostFlag)
        {
            av_free_packet(&pPacket);
            usleep(2000);
            __android_log_print(ANDROID_LOG_INFO, TAG, "22 decoding free video");
            continue;
        }
#endif
     if(!process(&pPacket))
        {
//            mRunning = false;
//            return false;
        }
        // Free the packet that was allocated by av_read_frame
        av_free_packet(&pPacket);
    }
    onDecode(NULL,-1);
    __android_log_print(ANDROID_LOG_INFO, TAG, "decoding video ended");
#if PERFORMANCETEST
    ClientLog::logOut("Total frames : \t%d \t%f",totalFrames, getTime() - startTime);
    ClientLog::logOut("average video           fps: \t%f",(totalFrames>1)?(totalFrames/(getTime() - startTime)):(0));
    ClientLog::logOut("average video decoding time: \t%f",(totalFrames>1)?(totalvdecTime/totalFrames):(0));
    ClientLog::logOut("average video display   time: \t%f",(totalFrames>1)?((totalvdec_disTime - totalvdecTime)/totalFrames):(0));
    __android_log_print(ANDROID_LOG_ERROR, TAG, "Total frames & time: \t%d \t%f",totalFrames, getTime() - startTime);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "average video           fps: \t%f",(totalFrames>1)?(totalFrames/(getTime() - startTime)):(0));
    __android_log_print(ANDROID_LOG_ERROR, TAG, "average video decoding time: \t%f",(totalFrames>1)?(totalvdecTime/totalFrames):(0));
    __android_log_print(ANDROID_LOG_ERROR, TAG, "average video display   time: \t%f",(totalFrames>1)?((totalvdec_disTime - totalvdecTime)/totalFrames):(0));
    __android_log_print(ANDROID_LOG_ERROR, TAG, "max Frame Decoding    time: \t%f",maxFrameDecTime);
#endif
    // Free the RGB image
    av_free(mFrame);

    return true;
}

/* These are called whenever we allocate a frame
 * buffer. We use this to store the global_pts in
 * a frame at the time it is allocated.
 */
int DecoderVideo::getBuffer(struct AVCodecContext *c, AVFrame *pic) {
    int ret = avcodec_default_get_buffer(c, pic);
    uint64_t *pts = (uint64_t *)av_malloc(sizeof(uint64_t));
    *pts = global_video_pkt_pts;
    pic->opaque = pts;
    return ret;
}
void DecoderVideo::releaseBuffer(struct AVCodecContext *c, AVFrame *pic) {
    if (pic)
        av_freep(&pic->opaque);
    avcodec_default_release_buffer(c, pic);
}
