extern "C" {
#include "libavcodec/avcodec.h"
#include "libavutil/samplefmt.h"
#include "Hies_proto.h"
}

#include "HiOmxCodecHandlr.h"
#include "HiMLoger.h"
#include "HiRtspClient.h"
#include <media/stagefright/MediaDefs.h>
#include "HiffmpegDecoder.h"
#include "HiRtspVideoSource.h"

#define TAG "HiOmxCodecHandlr"

namespace android{

static double getTime()
{
    timeval pTime;
    gettimeofday(&pTime, NULL);
    return (pTime.tv_sec + (pTime.tv_usec / 1000000.0));
}

class MediaPlayerRender:public RefBase
{
public:
    MediaPlayerRender(sp<ANativeWindow>& nativeWin) {
        mNativeWindow = nativeWin;
        native_window_set_scaling_mode(mNativeWindow.get(),NATIVE_WINDOW_SCALING_MODE_SCALE_TO_WINDOW);
    }
    void render(MediaBuffer *buffer) {
        int64_t timeUs;
        buffer->meta_data()->findInt64(kKeyTime, &timeUs);
        native_window_set_buffers_timestamp(mNativeWindow.get(), timeUs * 1000);
        status_t err = mNativeWindow->queueBuffer(
                mNativeWindow.get(), buffer->graphicBuffer().get());
        if (err != 0) {
            LOGE("queueBuffer failed with error %s (%d)", strerror(-err),
                    -err);
            return;
        }

        sp<MetaData> metaData = buffer->meta_data();
        metaData->setInt32(kKeyRendered, 1);
    }
private:
    sp<ANativeWindow> mNativeWindow;
};

HiOmxCodecHandlr::HiOmxCodecHandlr(jobject jsurface,
    JNIEnv* env,
    MediaPlayerPCMWriter* PCMWriter,
    int apiVer,
    HiProtocol* protocol)
    :HiMediaHandlr(jsurface, apiVer, protocol),
    mPCMWriter(PCMWriter)
{
    mVideoBuffer = NULL;
    mANativeWindow = ANativeWindow_fromSurface(env, jsurface);
    spWindow = mANativeWindow;
    mRunning = 0;
    mVideoDecoder = NULL;
    mVideoSource = NULL;
    mOpened = 0;
}

HiOmxCodecHandlr::~HiOmxCodecHandlr()
{
    mOpened = 0;
    mRunning= 0;
    MMLOGI(TAG, "~HiOmxCodecHandlr\n");
}

void HiOmxCodecHandlr::configAudioRender(int chnlCnt, int sampleRate, int sample_fmt)
{
    int AudioLatency= 0;
        /*配置AudioTrack 参数*/
        /*config the paras of AudioTrack*/
    AudioLatency = mPCMWriter->configAudioTrack(STREAM_MUSIC,
                        sampleRate,
                        ((chnlCnt == 2) ? CHANNEL_CONFIGURATION_STEREO: CHANNEL_CONFIGURATION_MONO),
                        ((sample_fmt == AV_SAMPLE_FMT_S16)?(ENCODING_PCM_16BIT):(ENCODING_PCM_8BIT)),
                        MODE_STREAM);
}

int HiOmxCodecHandlr::MakeAVCCodecSpecData(void* outbuf, int* outsize)
{
    unsigned char sps_set[128] = {0};
    unsigned char pps_set[128] = {0};
    int sps_size = 0;
    int pps_size =0;
    int ret = 0;

    HiRtspClient* rtspClient = static_cast<HiRtspClient*>(mProto);
    ret = rtspClient->getSPSPPS(sps_set,&sps_size,pps_set,&pps_size);
    if(ret != 0)
    {
        MMLOGI(TAG, "getSPS PPS failed\n");
        return ret;
    }
    int csdSize =
        1 + 3 + 1 + 1
        + 2 * 1 + sps_size
        + 1 + 2 * 1 + pps_size;

    uint8_t *out = (uint8_t*)outbuf;
    *outsize = csdSize;
    *out++ = 0x01;  // configurationVersion
    memcpy(out, &sps_set[1], 3);  // profile/level...

    uint8_t profile = out[0];
    uint8_t level = out[2];

    out += 3;
    *out++ = (0x3f << 2) | 1;  // lengthSize == 2 bytes
    *out++ = 0xe0 | 1;

    *out++ = sps_size >> 8;
    *out++ = sps_size & 0xff;
    memcpy(out, &sps_set[0], sps_size);
    out += sps_size;

    *out++ = 1;

    *out++ = pps_size >> 8;
    *out++ = pps_size & 0xff;
    memcpy(out, &pps_set[0], pps_size);
    return 0;
}

int HiOmxCodecHandlr::open()
{
    int ret = 0;
    if(!mOpened)
    {
        HiRtspClient* rtspClient = static_cast<HiRtspClient*>(mProto);
        unsigned char avcC_data[256] = {0};
        int avcC_size = 256;
        ret = MakeAVCCodecSpecData(&avcC_data[0], &avcC_size);
        if(ret != 0)
        {
            MMLOGI(TAG, "MakeAVCCodecSpecData error \n");
            return -1;
        }
        MMLOGI(TAG, "avcsd size: %d\n", avcC_size);
        int width = rtspClient->getVideoWidth();
        int height = rtspClient->getVideoHeight();

        mformat = new MetaData;
        mformat->setCString(kKeyMIMEType, MEDIA_MIMETYPE_VIDEO_AVC);
        mformat->setInt64(kKeyDuration, 9999999);
        mformat->setInt32(kKeyMaxInputSize, MAX_VIDEO_FRAME_SIZE);
        mformat->setInt32(kKeyWidth, width);
        mformat->setInt32(kKeyHeight, height);
        mformat->setData(kKeyAVCC, kTypeAVCC, &avcC_data[0], avcC_size);

        mVideoSource = new HiRtspVideoSource(rtspClient);
        mVideoDecoder = new HiOmxCodecDecoder(spWindow, mformat, mVideoSource);
        mVideoDecoder->open();
        mOpened = 1;
        mWidth = width;
        mHeight = height;
    }
    else
    {
        MMLOGI(TAG, "already opened \n");
    }
    return ret;
}

int HiOmxCodecHandlr::close()
{
    MMLOGI(TAG, "HiOmxCodecHandlr::close \n");
    if(mOpened)
    {
        stop();
        if (mVideoBuffer)
        {
            mVideoBuffer->release();
            mVideoBuffer = NULL;
        }
        if(mVideoDecoder)
        {
            mVideoDecoder->close();
            delete mVideoDecoder;
            mVideoDecoder = NULL;
        }
        if(mVideoSource)
        {
            mVideoSource->stop();
            delete mVideoSource;
            mVideoSource = NULL;
        }
        mOpened = 0;
        if(mANativeWindow)
        {
            MMLOGI(TAG, "ANativeWindow_release\n");
            ANativeWindow_release(mANativeWindow);
            //mANativeWindow = NULL;
        }
    }
    mOpened = 0;
    mRunning= 0;
    return 0;
}

int HiOmxCodecHandlr::getWidth(int * width)
{
    *width = mWidth;
    return 0;
}

int HiOmxCodecHandlr::getHeight(int * height)
{
    *height = mHeight;
    return 0;
}

void* HiOmxCodecHandlr::startPlayVideo(void* ptr)
{
    HiOmxCodecHandlr* pHandlr = static_cast<HiOmxCodecHandlr*>(ptr);
    pHandlr->decodeMovie(ptr);
}

void* HiOmxCodecHandlr::startPlayAudio(void* ptr)
{
    HiOmxCodecHandlr* pHandlr = static_cast<HiOmxCodecHandlr*>(ptr);
    pHandlr->decodeAudio(ptr);
}

void HiOmxCodecHandlr::decodeMovie(void* ptr)
{
    int got_pic = 0;
    double last_time = 0;
    int diff = 0;
    int ret = 0;
    int errFlag = 0;

    double Vidbegin = getTime();
    double VidTime = Vidbegin;
    MediaPlayerRender*  mediaRender = new MediaPlayerRender(spWindow);
    while(mRunning)
    {
        if(getTime()-VidTime >=60)
        {
            VidTime = getTime();
            diff = getTime()-Vidbegin;
            MMLOGE(TAG, "display video last  time: %d (s)!!!!", diff);
        }
        mVideoBuffer = NULL;
        ret= mVideoDecoder->read_omx_data(&mVideoBuffer);
        if(ret != 0)
        {
            if(ret == -1012 ||ret == -38 || ret == -110)
            {
                if (mVideoBuffer) {
                    mVideoBuffer->release();
                    mVideoBuffer = NULL;
                }
                continue;
            }
            errFlag = 1;
            break;
        }
        //MMLOGE(TAG, "read_omx_data  OK");
        mediaRender->render(mVideoBuffer);
        mVideoBuffer->release();
        mVideoBuffer = NULL;
    }
    MMLOGI(TAG, "start Notify Detaching decodeMovie");
    if(errFlag)
    {
        /*回调error给java层，告知java层player 发生错误*/
        /*tell the player error to java*/
        mListener->notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        MMLOGE(TAG, "playing err");
    }
    delete mediaRender;
    mListener->notify(DETACHING, -1, -1);
}

void HiOmxCodecHandlr::decodeAudio(void* ptr)
{
    AVPacket pkt;
    int i_outSize = 0;
    int diff = 0;
    int ret =0;
    int errHappened = 0;
    int audConfigFlag = 0;
    int mChnCnt, mSampleRate, mSampleFmt = 0;
    HiffmpegDecoder* iDecoder = new HiffmpegDecoder();
    ret = iDecoder->open();
    if(ret < 0)
    {
        MMLOGE(TAG, "HiffmpegDecoder open error \n");
        mListener->notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        return;
    }
    void * outbuf = av_malloc(AVCODEC_MAX_AUDIO_FRAME_SIZE);
    if(!outbuf)
    {
        MMLOGE(TAG, "HI_HIES_av_malloc failed");
        mListener->notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        return;
    }
    void* pInBuffer = av_malloc(MAX_AUDIO_FRAME_SIZE);
    if(!pInBuffer)
    {
        MMLOGE(TAG, "malloc error \n");
        mListener->notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        return;
    }
    double Audbegin = getTime();
    double AudTime = Audbegin;
    HiRtspClient* iprotocol = static_cast<HiRtspClient*>(mProto);
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
        //__android_log_print(ANDROID_LOG_INFO, TAG, "audio read pkt  pts: %lld, len: %d \n",  pkt.pts, pkt.size);
        i_outSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
        if((iDecoder->decodeAudio(outbuf, &i_outSize, &pkt)) < 0)
        {
            MMLOGE(TAG, "HI_HIES_decodeAudio failed");
            errHappened = 1;
            break;
        }
        if(!audConfigFlag)
        {
            int ret = 0;
            ret = iDecoder->getAudioAttr(&mChnCnt, &mSampleRate, &mSampleFmt);
            if(ret < 0)
            {
                MMLOGE(TAG, "there some error happened, could not get the attr \n");
                errHappened = 1;
                break;
            }
            MMLOGE(TAG, "Audio Attr chnl: %d sampleRate: %d sampleFmt: %d\n", mChnCnt, mSampleRate, mSampleFmt);
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
        mListener->notify(MEDIA_ERROR, MEDIA_ERROR_SERVER_DIED, -1);
        MMLOGE(TAG, "playing err");
    }
    MMLOGI(TAG, "start Notify Detaching decodeAudio");
    iDecoder->close();
    delete iDecoder;
    iDecoder = NULL;
    mListener->notify(DETACHING, -1, -1);
}

int HiOmxCodecHandlr::start()
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
    return 0;
}

int HiOmxCodecHandlr::stop()
{
    if(mRunning)
    {
        mRunning = 0;
        if(mAudThread)
        {
            if(pthread_join(mAudThread, 0) < 0)
            {
                 MMLOGE(TAG,"pthread_join failed");
            }
            mAudThread = 0;
        }
        if(mVidThread)
        {
            if(pthread_join(mVidThread, 0) < 0)
            {
                 MMLOGE(TAG,"pthread_join failed");
            }
            mVidThread = 0;
        }
        MMLOGE(TAG,"decode thread have been closed!!");
    }

    if (mVideoBuffer) {
        mVideoBuffer->release();
        mVideoBuffer = NULL;
    }
    mRunning = 0;
}
}
