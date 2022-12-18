extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/log.h"
#include "Hies_proto.h"
#include "yuv2rgb_neon.h"
}

#include "HiffmpegHandlr.h"
#include "nativeWindow.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <media/AudioSystem.h>
#include "HiMLoger.h"
#include "HiRtspClient.h"


#define VIDEOPIXELFORMAT PIX_FMT_RGB565

#define TAG "HiffmpegHandlr"

namespace android{

static void yuv420_2_rgb565_neon(uint8_t  *dst_ptr,
               const uint8_t  *y_ptr,
               const uint8_t  *u_ptr,
               const uint8_t  *v_ptr,
                     int32_t   pic_width,
                     int32_t   pic_height,
                     int32_t   y_pitch,
                     int32_t   uv_pitch,
                     int32_t   dst_pitch)
{
    for (int i = 0; i < pic_height; i++)
    {
        yv12_to_rgb565_neon((uint16_t*)(dst_ptr + dst_pitch * i),
                         y_ptr + y_pitch * i,
                         u_ptr + uv_pitch * (i / 2),
                         v_ptr + uv_pitch * (i / 2),
                         pic_width,
                         0);
    }
}
static double getTime()
{
    timeval pTime;
    gettimeofday(&pTime, NULL);
    return (pTime.tv_sec + (pTime.tv_usec / 1000000.0));
}

/*图像surface 分辨率改变时，到java层的回调函数*/
/*when the surface resoultion change, this function will be callback to java*/
static int ANWindow_setBuffersGeometry(void* pHandle, int width, int height, int format)
{
    HiffmpegHandlr* pHandlr = (HiffmpegHandlr*)pHandle;
    pHandlr->notify(MEDIA_ASR_CHANGE, -1, -1);
}

HiffmpegHandlr::HiffmpegHandlr(jobject jsurface,
    JNIEnv* env,
    MediaPlayerPCMWriter* pcmWriter,
    int apiVer,
    HiProtocol* protocol)
    :HiMediaHandlr(jsurface, apiVer, protocol),
    mjenv(env),
    mPCMWriter(pcmWriter)
{
    mFrame = NULL;
    mVidThread = 0;
    mAudThread = 0;
    pANWindow = NULL;
    mDecoder = NULL;
    mOpened = 0;
    mRunning = 0;
    mWidth = 0;
    mHeight = 0;
    vidConfigFlag = 0;
    audConfigFlag= 0;
}

HiffmpegHandlr::~HiffmpegHandlr()
{

}

void HiffmpegHandlr::notify(int msg, int ext1, int ext2)
{
    MMLOGI(TAG, "message received msg=%d, ext1=%d, ext2=%d", msg, ext1, ext2);
    bool send = true;
    bool locked = false;

    if ((mListener != 0) && send) {
       MMLOGI(TAG, "callback application");
       mListener->notify(msg, ext1, ext2);
       MMLOGI(TAG, "back from callback");
    }
}

int HiffmpegHandlr::configNativeWindowRender(int width, int height)
{
    void*        pixels;
    /*获取NativeWindow的显示buffer*/
    /*get the display buffer of Native Window*/
    if (AndroidNativeWindow_getPixels(pANWindow,
        width, height, &pixels, WINDOW_FORMAT_RGB_565)!= 0)
    {
        MMLOGE(TAG, "AndroidNativeWindow_getPixels failed");
        return -1;
    }

    mFrame = avcodec_alloc_frame();
    if (!mFrame)
    {
        MMLOGE(TAG, TAG, "avcodec_alloc_frame failed");
        return -1;
    }
    // Assign appropriate parts of buffer to image planes in pFrameRGB
    // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
    // of AVPicture
        /*关联display buffer到mFrame*/
        /*create connection between mFrame and display buffer*/
    avpicture_fill((AVPicture *) mFrame,
                   (uint8_t *) pixels,
                   PIX_FMT_RGB565,
                   width,
                   height);

    notify(MEDIA_ASR_CHANGE, -1, -1);
}

void HiffmpegHandlr::configAudioRender(int chnlCnt, int sampleRate, int sample_fmt)
{
    int AudioLatency= 0;
    MMLOGI(TAG, "audio  channels:%d, samplerate: %d, sample_fmt: %d ",chnlCnt ,
        sampleRate, sample_fmt);
        /*配置AudioTrack 参数*/
        /*config the paras of AudioTrack*/
    AudioLatency = mPCMWriter->configAudioTrack(STREAM_MUSIC,
                        sampleRate,
                        ((chnlCnt == 2) ? CHANNEL_CONFIGURATION_STEREO: CHANNEL_CONFIGURATION_MONO),
                        ((sample_fmt == AV_SAMPLE_FMT_S16)?(ENCODING_PCM_16BIT):(ENCODING_PCM_8BIT)),
                        MODE_STREAM);
}

int HiffmpegHandlr::open()
{
    int AudioLatency;
    if(!mOpened)
    {
        pANWindow = AndroidNativeWindow_register(mjenv, mjsurface, mApiVersion,&ANWindow_setBuffersGeometry,this);
        if(!pANWindow)
        {
            MMLOGE(TAG, "AndroidNativeWindow_register error \n");
            return -1;
        }

        mDecoder = new HiffmpegDecoder();
        /*初始化音视频编码器
            init the audio and video coder with ffmpeg*/
        mDecoder->open();
        mOpened = 1;
    }
    else
    {
        MMLOGI(TAG, "HiffmpegHandlr already opened!!");
    }
}

int HiffmpegHandlr::close()
{
    if(mRunning)
    {
        stop();
        mRunning = 0;
    }
    if(mOpened)
    {
        if(pANWindow)
        {
            AndroidNativeWindow_unregister(pANWindow);
            pANWindow = NULL;
        }
        MMLOGI(TAG, "before mFrame free!!");
        if(mFrame)
        {
            if(mFrame->data[0])
            {
                av_free(mFrame->data[0]);
                mFrame->data[0] =NULL;
            }
            av_free(mFrame);
            mFrame = NULL;
        }
        mDecoder->close();
        delete mDecoder;
        mDecoder = NULL;
    }
    mOpened = 0;
    mRunning = 0;
}

/*循环获取音频数据，并送入decoder解码，获得PCM数据，回调java AudioTrack 播放*/
/*get the audio data , the input to decoder and get pcm output, then input pcm to audio track*/
void* HiffmpegHandlr::decodeAudio(void* ptr)
{
    AVPacket pkt;
    int i_outSize = 0;
    int diff = 0;
    int errHappened = 0;
    void * outbuf = av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
    if(!outbuf)
    {
        MMLOGI(TAG, "HI_HIES_av_malloc failed");
        notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        return 0;
    }
    void* pInBuffer = av_malloc(MAX_AUDIO_FRAME_SIZE);
    if(!pInBuffer)
    {
        MMLOGE(TAG, "malloc error \n");
        notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        return 0;
    }
    double Audbegin = getTime();
    double AudTime = Audbegin;
    HiRtspClient* iprotocol = (HiRtspClient*)mProto;
    while(mRunning)
    {
        if(getTime()-AudTime >=180)
        {
            AudTime = getTime();
            diff = getTime()-Audbegin;
            MMLOGE(TAG, "display audio last  time: %d (s)!!!!", diff);
        }
        av_init_packet(&pkt);
        pkt.size = MAX_AUDIO_FRAME_SIZE;
        if(iprotocol->readAudioStream(pInBuffer, pkt.size, pkt.pts) < 0)
        {
            MMLOGE(TAG, "readAudioStream failed");
            errHappened = 1;
            break;
        }
        pkt.data = (uint8_t*)pInBuffer;
        pkt.dts = pkt.pts;
        //MMLOGI(TAG, "audio read pkt  pts: %lld, len: %d \n",  pkt.pts, pkt.size);
        i_outSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
        if((mDecoder->decodeAudio(outbuf, &i_outSize, &pkt)) < 0)
        {
            MMLOGE(TAG, "HI_HIES_decodeAudio failed");
            errHappened = 1;
            break;
        }
        if(!audConfigFlag)
        {
            int ret = 0;
            ret = mDecoder->getAudioAttr(&mChnCnt, &mSampleRate, &mSampleFmt);
            if(ret < 0)
            {
                MMLOGE(TAG, "there some error happened, could not get the attr \n");
                errHappened = 1;
                break;
            }
            configAudioRender(mChnCnt, mSampleRate, mSampleFmt);
            audConfigFlag = 1;
        }
        if(mPCMWriter)
        {
            mPCMWriter->writePCM((unsigned char*)outbuf, i_outSize);
        }
    }
    if(outbuf)
        av_free(outbuf);
    if(pInBuffer)
        av_free(pInBuffer);
    if(errHappened)
    {
        notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        MMLOGE(TAG, "playing err");
    }
    MMLOGI(TAG, "start Notify Detaching decodeAudio");
    notify(DETACHING, -1, -1);
    return 0;
}

void* HiffmpegHandlr::startPlayVideo(void* ptr)
{
    HiffmpegHandlr* pHandlr = static_cast<HiffmpegHandlr*>(ptr);
    pHandlr->decodeMovie(ptr);
}

void* HiffmpegHandlr::startPlayAudio(void* ptr)
{
    HiffmpegHandlr* pHandlr = static_cast<HiffmpegHandlr*>(ptr);
    pHandlr->decodeAudio(ptr);
}

/*循环获取视频数据，并送入decoder解码，获得YUV数据，转换为
    RGB, 送入NativeWindow 更新显示*/
/*get the video frame ,  input to decoder and get YUV output, convert YUV to RGB ,then input RGB to NativeWindow for display update*/
void* HiffmpegHandlr::decodeMovie(void* ptr)
{
    AVPacket pkt;
    int got_pic = 0;
    int diff = 0;
    int errHappened = 0;
    int ptype = 0;
    AVFrame* frame = avcodec_alloc_frame();
    if (frame == NULL)
    {
        MMLOGE(TAG, "avcodec_alloc_frame failed");
        notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        return 0;
    }
    double Vidbegin = getTime();
    double VidTime = Vidbegin;
    void* pBuffer = av_malloc(MAX_VIDEO_FRAME_SIZE);
    if(!pBuffer)
    {
        MMLOGE(TAG, "malloc error \n");
        notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        return 0;
    }
    HiRtspClient* iprotocol = (HiRtspClient*)mProto;
    MMLOGE(TAG, "display video begin time: %d !!!!", Vidbegin);
    while(mRunning)
    {
        if(getTime()-VidTime >=60)
        {
            VidTime = getTime();
            diff = getTime()-Vidbegin;
            MMLOGE(TAG, "display video last  time: %d (s)!!!!", diff);
        }
        av_init_packet(&pkt);
        pkt.size = MAX_VIDEO_FRAME_SIZE;
        if(iprotocol->readVideoStream(pBuffer, pkt.size, pkt.pts, ptype) < 0)
        {
            MMLOGE(TAG, "HI_HIES_read_video_stream failed");
            errHappened = 1;
            break;
        }
        pkt.data = (uint8_t*)pBuffer;
        pkt.dts = pkt.pts;
        if(ptype == 5)
            pkt.flags |= AV_PKT_FLAG_KEY;
        //MMLOGI(TAG, "video read pkt  pts: %lld, len: %d data ptr: 0x%08x  got_pic ptr:  0x%08x\n",  pkt.pts, pkt.size, pkt.data, &got_pic);
        if((mDecoder->decodeVideo(frame, &got_pic, &pkt)) < 0)
        {
            MMLOGE(TAG, "HI_HIES_decodeVideo failed");
            continue;
        }
        if(!got_pic)
            continue;
        if(!vidConfigFlag)
        {
            int ret = 0;
            ret = mDecoder->getVideoAttr(&mWidth, &mHeight, &mPixFormat);
            if(ret < 0)
            {
                MMLOGE(TAG, "there some error happened, could not get the attr \n");
                errHappened = 1;
                break;
            }
            ret = configNativeWindowRender(mWidth, mHeight);
            if(ret < 0)
            {
                MMLOGE(TAG, "configNativeWindowRender error\n");
                errHappened = 1;
                break;
            }
            vidConfigFlag = 1;
        }
        if(mPixFormat == PIX_FMT_RGB565)
        {
            memcpy(mFrame->data[0],frame->data[0],avpicture_get_size(VIDEOPIXELFORMAT, mWidth, mHeight));
        }
        else
        {
            if(VIDEOPIXELFORMAT == PIX_FMT_RGB565)
            {
                yuv420_2_rgb565_neon(mFrame->data[0], frame->data[0], frame->data[1],
                                    frame->data[2],
                mWidth, mHeight, frame->linesize[0], frame->linesize[1],
                mWidth<<1);
            }
            else if(VIDEOPIXELFORMAT == PIX_FMT_RGBA)
            {
                yuv420_2_rgba_neon(mFrame->data[0],frame->data[0], frame->data[1],
                frame->data[2],mWidth, mHeight,
                frame->linesize[0], frame->linesize[1],
                mWidth<<2);
            }

        }
        /*更新NativeWindow 当前显示图像*/
        /*update the display buffer to refresh disp image*/
        AndroidNativeWindow_update(pANWindow, mFrame->data[0], mWidth,
            mHeight, WINDOW_FORMAT_RGB_565);
    }
    if(pBuffer)
        av_free(pBuffer);
    if(frame)
        av_free(frame);
    MMLOGE(TAG, "start Notify Detaching decodeMovie");
    if(errHappened)
    {
        /*回调error给java层，告知java层player 发生错误*/
        /*tell the player error to java*/
        notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        MMLOGE(TAG, "playing err");
    }
    notify(DETACHING, -1, -1);
    return 0;
}

int HiffmpegHandlr::start()
{
    if(!mOpened)
    {
        MMLOGE(TAG, "have not been opened \n");
        return -1;
    }
    if(!mRunning)
    {
        mRunning = 1;
        pthread_create(&mVidThread, NULL, startPlayVideo, this);
        MMLOGE(TAG, "pthread_create startVideo id: %d ", mVidThread);
        pthread_create(&mAudThread, NULL, startPlayAudio, this);
        MMLOGE(TAG, "pthread_create startAudio id: %d ", mAudThread);
    }
}

int HiffmpegHandlr::stop()
{
    if(mRunning)
    {
        mRunning = 0;
        if(pthread_join(mAudThread, 0) < 0)
        {
             MMLOGI(TAG,"pthread_join failed");
        }
        if(pthread_join(mVidThread, 0) < 0)
        {
             MMLOGI(TAG,"pthread_join failed");
        }
    }
}

int HiffmpegHandlr::getWidth(int * width)
{
    *width = mWidth;
    return 0;
}

int HiffmpegHandlr::getHeight(int * height)
{
    *height = mHeight;
    return 0;
}
}
