#include <stdlib.h>
#include <stdarg.h>
#include "HiffmpegDecoder.h"
#include "HiMLoger.h"

#define TAG "HiffmpegDecoder"

namespace android{
HiffmpegDecoder::HiffmpegDecoder()
{
    mVdoCodecCtx = NULL;
    mAudCodecCtx = NULL;
    mFirstAudioFlag = 0;
    mFirstVideoFlag = 0;
    mRunning = 0;
}

HiffmpegDecoder::~HiffmpegDecoder()
{

}

int HiffmpegDecoder::openVideoDecoder()
{
    struct AVCodec* i_pcodec;
    int ret = 0;

    i_pcodec = avcodec_find_decoder(CODEC_ID_H264);
    if (!i_pcodec) {
        MMLOGE(TAG, "avcodec_find_decoder error \n");
        goto err_ret;
    }

    mVdoCodecCtx = avcodec_alloc_context();
    if(!mVdoCodecCtx)
    {
        MMLOGE(TAG, "malloc error \n");
        goto err_ret;
    }
    if(i_pcodec->capabilities&CODEC_CAP_TRUNCATED)
        mVdoCodecCtx->flags|= CODEC_FLAG_TRUNCATED; /* we do not send complete frames */
    /* open it */
    if (avcodec_open(mVdoCodecCtx, i_pcodec) < 0) {
        MMLOGE(TAG, "avcodec_open error \n");
        goto open_fail;
    }
    MMLOGE(TAG, "h264 codec init pthread num : %d \n",mVdoCodecCtx->thread_count);
    return 0;

open_fail:
    av_free(mVdoCodecCtx);
err_ret:
    return -1;
}

int HiffmpegDecoder::openAudioDecoder()
{
    struct AVCodec* i_pcodec;
    int ret = 0;
    /*音频解码器Context*/
    /*audio decoder context*/
    mAudCodecCtx = avcodec_alloc_context();
    if(!mAudCodecCtx)
    {
        MMLOGE(TAG, "malloc error \n");
        goto err_ret;
    }
    i_pcodec = avcodec_find_decoder(CODEC_ID_AAC);

    if (avcodec_open(mAudCodecCtx, i_pcodec) < 0)
    {
        MMLOGE(TAG, "avcodec_open error \n");
       goto open_fail;
    }
    return 0;

open_fail:
    av_free(mAudCodecCtx);
err_ret:
    return -1;
}

int HiffmpegDecoder::open()
{
    if(!mRunning)
    {
        /*设置ffmpeg callback函数
            set the callback of ffmpeg to display the log of ff*/
        av_log_set_callback(ffmpegNotify);
        /* must be called before using avcodec lib */
        avcodec_init();

        /* register all the codecs */
        avcodec_register_all();
        if(openVideoDecoder() < 0)
        {
            MMLOGE(TAG, "openVideoDecoder error \n");
            return -1;
        }
        if(openAudioDecoder() < 0)
        {
            MMLOGE(TAG,  "openAudioDecoder error \n");
            close();
            return -1;
        }
        mRunning = 1;
    }
    else
    {
        MMLOGE(TAG,  "HiffmpegDecoder already opened \n");
    }
    return 0;
}

int HiffmpegDecoder::close()
{
    if(mVdoCodecCtx)
    {
        avcodec_close(mVdoCodecCtx);
        MMLOGE(TAG, "avcodec_close  video  ok \n");
        av_free(mVdoCodecCtx);
        mVdoCodecCtx = NULL;
    }
    MMLOGI(TAG, "HiffmpegDecoder close video ctx ok \n");
    if(mAudCodecCtx)
    {
        avcodec_close(mAudCodecCtx);
        MMLOGE(TAG, "avcodec_close  audio  ok \n");
        av_free(mAudCodecCtx);
        mAudCodecCtx = NULL;
    }
    mRunning = 0;
    mFirstAudioFlag = 0;
    mFirstVideoFlag = 0;
}

/*循环获取音频数据，并送入decoder解码，获得PCM数据，回调java AudioTrack 播放*/
/*get the audio data , the input to decoder and get pcm output, then input pcm to audio track*/
int HiffmpegDecoder::decodeAudio(void *outdata, int *outdata_size, AVPacket *avpkt)
{
    int ret = 0;
    ret = avcodec_decode_audio3(mAudCodecCtx, (int16_t*)outdata, outdata_size, avpkt);
    if(ret < 0)
    {
        MMLOGE(TAG, "decodeAudio failed  \n");
        return -1;
    }
    if(!mFirstAudioFlag)
        mFirstAudioFlag = true;
    return ret;
}

/*循环获取视频数据，并送入decoder解码，获得YUV数据，转换为
    RGB, 送入NativeWindow 更新显示*/
/*get the video frame ,  input to decoder and get YUV output, convert YUV to RGB ,then input RGB to NativeWindow for display update*/
int HiffmpegDecoder::decodeVideo(AVFrame *outdata, int *outdata_size, AVPacket *avpkt)
{
    int ret = 0;
    ret = avcodec_decode_video2(mVdoCodecCtx, outdata, outdata_size, avpkt);
    if(ret < 0)
    {
        MMLOGE(TAG, "decode failed  \n");
        return -1;
    }
    if(!mFirstVideoFlag)
        mFirstVideoFlag = true;
    return ret;
}

int HiffmpegDecoder::getVideoAttr(int* width, int* height, int* pixFormat)
{
    if(mFirstVideoFlag)
    {
        *width = mVdoCodecCtx->width;
        *height = mVdoCodecCtx->height;
        *pixFormat = mVdoCodecCtx->pix_fmt;
        return 0;
    }
    else
    {
        MMLOGI(TAG, "there no video frame are decoded\n");
        return -1;
    }
}

int HiffmpegDecoder::getAudioAttr(int* chnlCnt, int* sampleRate, int* sample_fmt)
{
    if(mFirstAudioFlag)
    {
        *chnlCnt = mAudCodecCtx->channels;
        *sampleRate = mAudCodecCtx->sample_rate;
        *sample_fmt = mAudCodecCtx->sample_fmt;
        return 0;
    }
    else
    {
        MMLOGI(TAG, "there no audio frame are decoded\n");
        return -1;
    }
}

void HiffmpegDecoder::ffmpegNotify(void* ptr, int level, const char* fmt, va_list vl)
{
    char tmpBuffer[1024];
//    __android_log_print(ANDROID_LOG_ERROR, TAG, "AV_LOG_ERROR: %s", tmpBuffer);
    vsnprintf(tmpBuffer,1024,fmt,vl);

    switch(level) {
            /**
             * Something went really wrong and we will crash now.
             */
        case AV_LOG_PANIC:
            MMLOGE(TAG, "AV_LOG_PANIC: %s", tmpBuffer);
            //sPlayer->mCurrentState = MEDIA_PLAYER_STATE_ERROR;
            break;

            /**
             * Something went wrong and recovery is not possible.
             * For example, no header was found for a format which depends
             * on headers or an illegal combination of parameters is used.
             */
        case AV_LOG_FATAL:
            MMLOGE(TAG, "AV_LOG_FATAL: %s", tmpBuffer);
            //sPlayer->mCurrentState = MEDIA_PLAYER_STATE_ERROR;
            break;

            /**
             * Something went wrong and cannot losslessly be recovered.
             * However, not all future data is affected.
             */
        case AV_LOG_ERROR:
            MMLOGE(TAG, "AV_LOG_ERROR: %s", tmpBuffer);
            //sPlayer->mCurrentState = MEDIA_PLAYER_STATE_ERROR;
            break;

            /**
             * Something somehow does not look correct. This may or may not
             * lead to problems. An example would be the use of '-vstrict -2'.
             */
        case AV_LOG_WARNING:
            MMLOGI("AV_LOG_WARNING: %s", tmpBuffer);
            break;

        case AV_LOG_INFO:
            MMLOGI(TAG, "%s", tmpBuffer);
            break;

        case AV_LOG_DEBUG:
            MMLOGI(TAG, "%s", tmpBuffer);
            break;

    }
}
}
