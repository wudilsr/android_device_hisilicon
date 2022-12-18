
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <float.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <errno.h>
#include "pthread.h"
#include "libavcodec/avcodec.h"
#include "Hies_client.h"
#include "HiMLoger.h"

#define true            1
#define false            0
#define TAG "Hies_client"


static AVCodecContext* m_pVedioCtx;
static AVCodecContext* m_pAudCtx;
//extern AVCodec ff_h264_decoder;
//extern AVCodec ff_aac_decoder;

/*初始化 音频解码器*/
/*init audio decoder*/
int HI_HIES_Init_Audio_Codec(AVCodecContext** pAudCtx)
{
    struct AVCodec* i_pcodec;
    int ret = 0;
    /*音频解码器Context*/
    /*audio decoder context*/
    m_pAudCtx = avcodec_alloc_context();
    if(!m_pAudCtx)
    {
        MMLOGI(TAG, "malloc error \n");
        goto err_ret;
    }
    i_pcodec = avcodec_find_decoder(CODEC_ID_AAC);

    if (avcodec_open(m_pAudCtx, i_pcodec) < 0)
    {
       goto open_fail;
    }

    #if 0
    i_pcodec = &ff_aac_decoder;
    m_pAudCtx->codec = &ff_aac_decoder;
    if (i_pcodec->priv_data_size > 0)
    {
        if(!m_pAudCtx->priv_data)
        {
            m_pAudCtx->priv_data = av_mallocz(i_pcodec->priv_data_size);
            if (!m_pAudCtx->priv_data)
            {
                MMLOGI(TAG, "malloc error \n");
                return -1;
            }
        }
    }
    ret = i_pcodec->init(m_pAudCtx);
    if(ret < 0)
    {
        MMLOGI(TAG, "AAC codec init failed \n");
        av_freep(m_pAudCtx->priv_data);
        return -1;
    }
    #endif

    *pAudCtx= m_pAudCtx;
    return 0;
proto_fail:
    avcodec_close(m_pAudCtx);
open_fail:
    av_free(m_pAudCtx);
err_ret:
    return -1;
}
/*初始化 视频解码器*/
/*init video decoder*/
int HI_HIES_Init_Video_Codec(AVCodecContext** pVideoCtx)
{
    struct AVCodec* i_pcodec;
    int ret = 0;

    i_pcodec = avcodec_find_decoder(CODEC_ID_H264);
    if (!i_pcodec) {
        MMLOGI(TAG, "avcodec_find_decoder error \n");
        goto err_ret;
    }

    m_pVedioCtx = avcodec_alloc_context();
    if(!m_pVedioCtx)
    {
        MMLOGI(TAG, "malloc error \n");
        goto err_ret;
    }
    if(i_pcodec->capabilities&CODEC_CAP_TRUNCATED)
        m_pVedioCtx->flags|= CODEC_FLAG_TRUNCATED; /* we do not send complete frames */
    /* open it */
    //m_pVedioCtx->thread_count =4;
    if (avcodec_open(m_pVedioCtx, i_pcodec) < 0) {
        MMLOGI(TAG, "avcodec_open error \n");
        goto open_fail;
    }
    #if 0
    if (i_pcodec->priv_data_size > 0)
    {
        if(!m_pVedioCtx->priv_data)
        {
            m_pVedioCtx->priv_data = av_mallocz(i_pcodec->priv_data_size);
            MMLOGI(TAG, "video malloc codec priv_data ptr : 0x%08x \n",m_pVedioCtx->priv_data );
            if (!m_pVedioCtx->priv_data)
            {
                MMLOGI(TAG, "malloc error \n");
                return -1;
            }
        }
    }
    ret = avcodec_thread_init(m_pVedioCtx,4);
    if(ret < 0)
    {
        MMLOGI(TAG, "h264 avcodec_thread_init failed \n");
        return -1;
    }
#endif
    MMLOGI(TAG, "h264 codec init pthread num : %d \n",m_pVedioCtx->thread_count);
    #if 0
    ret = i_pcodec->init(m_pVedioCtx);

    if(ret < 0)
    {
        av_free((m_pVedioCtx->priv_data));
        m_pVedioCtx->priv_data = NULL;
        MMLOGI(TAG, "h264 codec init failed \n");
        return -1;
    }
    ret = avcodec_thread_init(m_pVedioCtx,8);
    if(ret < 0)
    {
        av_free((m_pVedioCtx->priv_data));
        m_pVedioCtx->priv_data = NULL;
        MMLOGI(TAG, "h264 avcodec_thread_init failed \n");
        return -1;
    }
#endif
    *pVideoCtx = m_pVedioCtx;
    return 0;

proto_fail:
    avcodec_close(m_pVedioCtx);
open_fail:
    av_free(m_pVedioCtx);
err_ret:
    return -1;
}

int HI_HIES_Init_Codec(AVCodecContext** pVideoCtx, AVCodecContext** pAudioCtx)
{
    AVCodecContext* pVdCtx = NULL;
    AVCodecContext* pAudCtx = NULL;

    /* must be called before using avcodec lib */
    avcodec_init();

    /* register all the codecs */
    avcodec_register_all();
    if(HI_HIES_Init_Video_Codec(&pVdCtx) < 0)
    {
        MMLOGI(TAG, "HI_HIES_Init_Video_Codec error \n");
        return -1;
    }
    *pVideoCtx = pVdCtx;
    if(HI_HIES_Init_Audio_Codec(&pAudCtx) < 0)
    {
        MMLOGI(TAG, "HI_HIES_Init_Audio_Codec error \n");
        return -1;
    }
    *pAudioCtx = pAudCtx;
    return 0;
}
/*去初始化 解码器*/
/*deinit  decoder*/
int HI_HIES_DeInit_Codec(AVCodecContext* pVdoCtx, AVCodecContext* pAudCtx)
{
    if(pVdoCtx != m_pVedioCtx)
    {
        MMLOGI(TAG, "HI_HIES_DeInit_Codec video ctx is not corresponding \n");
    }
    if(m_pVedioCtx)
    {
        avcodec_close(m_pVedioCtx);
        MMLOGI(TAG, "avcodec_close  video  ok \n");
        av_free(m_pVedioCtx);
        m_pVedioCtx = NULL;
    }
    MMLOGI(TAG, "HI_HIES_DeInit_Codec close video ctx ok \n");
    #if 0
    if(pVdoCtx->codec->close)
        pVdoCtx->codec->close(pVdoCtx);
    if(m_pVedioCtx->priv_data)
    {
        av_free((m_pVedioCtx->priv_data));
        m_pVedioCtx->priv_data = NULL;
    }
    #endif
    if(pAudCtx != m_pAudCtx)
    {
        MMLOGI(TAG, "HI_HIES_DeInit_Codec audio ctx is not corresponding \n");
    }
    if(m_pAudCtx)
    {
        avcodec_close(m_pAudCtx);
        MMLOGI(TAG, "avcodec_close  audio  ok \n");
        av_free(m_pAudCtx);
        m_pAudCtx = NULL;
    }
    MMLOGI(TAG, "HI_HIES_DeInit_Codec close audio ctx ok \n");

}


void HI_HIES_init_packet(AVPacket *pkt)
{
    pkt->pts   = NOPTS_VALUE;
    pkt->dts   = NOPTS_VALUE;
    pkt->pos   = -1;
    pkt->duration = 0;
    pkt->convergence_duration = 0;
    pkt->flags = 0;
    pkt->stream_index = 0;
    pkt->destruct= NULL;
    pkt->side_data       = NULL;
    pkt->side_data_elems = 0;

}

void* HI_HIES_av_malloc(int size)
{
    void * outbuf = av_mallocz(size);
    return outbuf;
}

void HI_HIES_av_free(void* ptr)
{
    av_free(ptr);
}
/*视频解码函数*/
/*video decoder*/
 int HI_HIES_decodeVideo(AVCodecContext *pCtx, void *outdata, int *outdata_size, AVPacket *avpkt)
{
    struct AVCodec* i_pcodec = pCtx->codec;
    int ret = 0;
    //ret = ff_thread_decode_frame(pCtx, outdata, outdata_size, avpkt);
    ret = avcodec_decode_video2(pCtx, outdata, outdata_size, avpkt);
    //ret = i_pcodec->decode(pCtx, outdata, outdata_size, avpkt);
    if(ret < 0)
    {
        MMLOGI(TAG, "decode failed  \n");
        return -1;
    }
    return ret;
}

/*音频解码函数*/
/*audio decoder*/
int HI_HIES_decodeAudio(AVCodecContext *pCtx, void *outdata, int *outdata_size, AVPacket *avpkt)
{
    struct AVCodec* i_pcodec = pCtx->codec;
    int ret = 0;
    //ret = ff_thread_decode_frame(pCtx, outdata, outdata_size, avpkt);
    //ret = avcodec_decode_video2(pCtx, outdata, outdata_size, avpkt);
    ret = avcodec_decode_audio3(pCtx, outdata, outdata_size, avpkt);
    if(ret < 0)
    {
        MMLOGI(TAG, "decode failed  \n");
        return -1;
    }
    return ret;
}

/*解一帧音频*/
/*decoder one audio frame*/
int HI_HIES_try_decode_audio_stream(void)
{
    MMLOGI(TAG, "HI_HIES_try_decode_audio_stream enter\n");
    AVPacket pkt;
    AVFrame* i_frame;
    memset(&pkt, 0x00, sizeof(AVPacket));
    if(HI_HIES_read_audio_stream(&pkt) < 0)
    {
        MMLOGI(TAG, "HI_HIES_read_audio_stream error\n");
         return -1;
    }
    void* outbuf = av_mallocz(AVCODEC_MAX_AUDIO_FRAME_SIZE);
    if(!outbuf)
    {
        MMLOGI(TAG, "audio decoder outbuf malloc error\n");
        return -1;
    }
    int i_outSize = AVCODEC_MAX_AUDIO_FRAME_SIZE;
    if(HI_HIES_decodeAudio(m_pAudCtx, (void*)outbuf, &i_outSize, &pkt) < 0)
    {
        MMLOGI(TAG, "HI_HIES_decode_stream error\n");
        av_free(outbuf);
        return -1;
    }
    av_free(outbuf);
    return 0;
}
/*解一帧视频*/
/*decoder one video frame*/
int HI_HIES_try_decode_Video_stream(void)
{
    AVPacket pkt;
    AVFrame* i_frame;

    av_init_packet(&pkt);
//    memset(&pkt, 0x00, sizeof(AVPacket));
    while(!pkt.flags&AV_PKT_FLAG_KEY)
    {
        if(HI_HIES_read_video_stream(&pkt) < 0)
        {
            MMLOGI(TAG, "HI_HIES_read_video_stream error\n");
             return -1;
        }

        MMLOGI(TAG, "read pkt  pts: %lld, len: %d \n",  pkt.pts, pkt.size);
    }
    i_frame = avcodec_alloc_frame();
    if (i_frame == NULL) {
        MMLOGI(TAG, "avcodec_alloc_frame error\n");
        return -1;
    }
    int got_pic;
    if(HI_HIES_decodeVideo(m_pVedioCtx, (void*)i_frame, &got_pic, &pkt) < 0)
    {
        MMLOGI(TAG, "HI_HIES_decode_stream error\n");
        av_free(i_frame);
        return -1;
    }
    av_free(i_frame);
    return 0;
}

/*从码流中获取解码的一些必要信息，比如视频分辨率，
    颜色空间，音频采样率，音频通道数等
    get the arbitary info need by decoder from the net stream, eg: video resolution, color space, audio samplerate
    audio channel and so on...*/
int HI_HIES_try_decode_stream(void)
{
    MMLOGI(TAG, "HI_HIES_try_decode_stream enter\n");
    if(HI_HIES_try_decode_Video_stream() < 0)
    {
        MMLOGI(TAG, "HI_HIES_try_decode_Video_stream error\n");
        return -1;
    }
    MMLOGI(TAG, "HI_HIES_try_decode_Video_stream success\n");
    if(HI_HIES_try_decode_audio_stream() < 0)
    {
        MMLOGI(TAG, "HI_HIES_try_decode_Video_stream error\n");
        return -1;
    }
    return 0;
}
