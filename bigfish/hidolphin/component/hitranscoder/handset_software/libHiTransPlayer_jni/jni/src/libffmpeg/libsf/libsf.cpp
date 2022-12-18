/*
 * Interface to the Android Stagefright library for
 * H/W accelerated H.264 decoding
 *
 * Copyright (C) 2011 Mohamed Naufal
 * Copyright (C) 2011 Martin Storsjö
 * Copyright (C) 2011 xuyangpo/x54178
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
//#include <surface.h>
#include "libsf.h"
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

extern "C"
{
    #include "libavutil/imgutils.h"
    #include "libavutil/internal.h"
    #include "../../arm_neon/yuv2rgb_neon.h"
}
#include "ahplayerdef.h"
#include "QCOM_ColorCvt.h"
#if !USINGLIBSF
int Stagefright_init(AVCodecContext *avctx)
{
    return -1;
}
int Stagefright_close(AVCodecContext *avctx)
{
    return -1;
}
void Stagefright_flush(AVCodecContext *avctx)
{
    return;
}
int Stagefright_decode_frame(AVCodecContext *avctx, void *data, int *data_size, AVPacket *avpkt)
{
    return -1;
}
int Stagefright_init_render(AVCodecContext *avctx,void* surface)
{
    return -1;
}
int Stagefright_render_frame(AVCodecContext *avctx,void* mediaBuffer)
{
    return -1;
}
int Stagefright_close_render(AVCodecContext *avctx)
{
    return -1;
}
#else
#include <surfaceflinger/Surface.h>
#include <binder/ProcessState.h>
#include <binder/IPCThreadState.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/MediaBufferGroup.h>
#include <media/stagefright/MediaDebug.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/OMXClient.h>
#include <media/stagefright/OMXCodec.h>
#include <media/stagefright/MediaErrors.h>
#include <utils/List.h>
#include <new>
#include <dlfcn.h>
using namespace android;
#define NAL_INPUT 0
#define MULTITHREAD 1
#define BITSTREAMFILTER 1
#define MUTEXLOG 1
#if PERFORMANCETEST
double totalcvtTime = 0;
double totalcvtFrame = 0;
#endif
#define ANDROID_V22_OMXCODEC_CREATE "_ZN7android8OMXCodec6CreateERKNS_2spINS_4IOMXEEERKNS1_INS_8MetaDataEEEbRKNS1_INS_11MediaSourceEEEPKcj"
#define ANDROID_V40_OMXCODEC_CREATE "_ZN7android8OMXCodec6CreateERKNS_2spINS_4IOMXEEERKNS1_INS_8MetaDataEEEbRKNS1_INS_11MediaSourceEEEPKcjRKNS1_I13ANativeWindowEE"
static void GenExtradata(unsigned char* pOut,int* pOutLen, unsigned char* pIn, int InLen);
static inline int GetNal(unsigned char* pIn, int InLen);
static void yuv420SemiPlanar2RGBA(uint8_t *dst_ptr,
                               const uint8_t *y_ptr,
                               const uint8_t *uv_ptr,
                               int      width,
                               int      height,
                               int y_pitch,
                               int uv_pitch,
                               int rgb_pitch);
static double getTime()
{
    timeval pTime;
    gettimeofday(&pTime, NULL);
    return (pTime.tv_sec + (pTime.tv_usec / 1000000.0));
}
static int align(int x, int y) {
    // y must be a power of 2.
    return (x + y - 1) & ~(y - 1);
}

struct Frame {
    status_t status;
    size_t size;
    int64_t time;
    int key;
    uint8_t *buffer;
    MediaBuffer* mbuffer;
    int32_t w, h;
};

class CustomSource;

struct StagefrightContext {
    AVCodecContext *avctx;
    AVBitStreamFilterContext *bsfc;
    uint8_t* orig_extradata;
    int orig_extradata_size;
    sp<MediaSource> *source;
    List<Frame*> *in_queue, *out_queue;
    pthread_mutex_t in_mutex, out_mutex;
    pthread_cond_t condition;
    pthread_t decode_thread_id;

    Frame *end_frame;
    bool source_done;
    volatile sig_atomic_t thread_started, thread_exited, stop_decode;

    AVFrame ret_frame;

    uint8_t *dummy_buf;
    int dummy_bufsize;

    OMXClient *client;
    sp<MediaSource> *decoder;
    const char *decoder_component;
    sp<IOMXRenderer> render;

};

class CustomSource : public MediaSource {
public:
    CustomSource(AVCodecContext *avctx, sp<MetaData> meta) {
        s = (StagefrightContext*)avctx->priv_data;
        source_meta = meta;
        frame_size  = (avctx->width * avctx->height * 3) / 2;
        av_log(avctx, AV_LOG_INFO, "=====Init frame_size:%d =====\n",frame_size);
        buf_group.add_buffer(new MediaBuffer(frame_size));
    }

    virtual sp<MetaData> getFormat() {
        return source_meta;
    }

    virtual status_t start(MetaData *params) {
        return OK;
    }

    virtual status_t stop() {
        return OK;
    }

    virtual status_t read(MediaBuffer **buffer,
                          const MediaSource::ReadOptions *options) {
        Frame *frame;
        status_t ret;

        if (s->thread_exited)
            return ERROR_END_OF_STREAM;
        pthread_mutex_lock(&s->in_mutex);

        while (s->in_queue->empty())
            pthread_cond_wait(&s->condition, &s->in_mutex);

        frame = *s->in_queue->begin();
        ret = frame->status;

        if (ret == OK) {
            ret = buf_group.acquire_buffer(buffer);
            if (ret == OK) {
//                av_log(s->avctx, AV_LOG_INFO, "======framebuffer: %d\n",frame->size);
/*                for(int j = 0;j<frame->size;j++)
                {
                    av_log(s->avctx, AV_LOG_INFO, "%x ",frame->buffer[j]);
                }*/

//                av_log(s->avctx, AV_LOG_INFO, "======framebuffer Over=====\n");
                memcpy((*buffer)->data(), frame->buffer, frame->size);
                (*buffer)->set_range(0, frame->size);
                (*buffer)->meta_data()->clear();
                (*buffer)->meta_data()->setInt32(kKeyIsSyncFrame,frame->key);
                (*buffer)->meta_data()->setInt64(kKeyTime, frame->time);
            } else {
                av_log(s->avctx, AV_LOG_ERROR, "Failed to acquire MediaBuffer\n");
            }
            av_freep(&frame->buffer);
        }

        s->in_queue->erase(s->in_queue->begin());
        pthread_mutex_unlock(&s->in_mutex);


        av_freep(&frame);
        return ret;
    }

private:
    MediaBufferGroup buf_group;
    sp<MetaData> source_meta;
    StagefrightContext *s;
    int frame_size;
};

void* decode_thread(void *arg)
{
    AVCodecContext *avctx = (AVCodecContext*)arg;
    StagefrightContext *s = (StagefrightContext*)avctx->priv_data;
    Frame* frame;
    MediaBuffer *buffer;
    int decode_done = 0;
    av_log(avctx, AV_LOG_ERROR, "decode_thread\n");
    do {
        buffer = NULL;
        frame = (Frame*)av_mallocz(sizeof(Frame));
        if (!frame) {
            frame         = s->end_frame;
            frame->status = AVERROR(ENOMEM);
            decode_done   = 1;
            s->end_frame  = NULL;
        } else {
            frame->status = (*s->decoder)->read(&buffer);
            if (frame->status == OK) {
                sp<MetaData> outFormat = (*s->decoder)->getFormat();
                outFormat->findInt32(kKeyWidth , &frame->w);
                outFormat->findInt32(kKeyHeight, &frame->h);
                frame->size    = buffer->range_length();
                frame->mbuffer = buffer;
                buffer->meta_data()->findInt64(kKeyTime, &(frame->time));
//                av_log(avctx, AV_LOG_ERROR, "new frame out:%x %d\n",frame->mbuffer,frame->size);
            } else if (frame->status == INFO_FORMAT_CHANGED) {
                if (buffer)
                    buffer->release();
                av_free(frame);
                continue;
            } else {
                decode_done = 1;
         if (buffer)
                    buffer->release();
                av_log(avctx, AV_LOG_ERROR, "@@@@@@ decode_done == 1,frame status %x\n",frame->status);
            }
        }
        while (true) {
#if MUTEXLOG
            av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_lock 226\n");
#endif
            pthread_mutex_lock(&s->out_mutex);
            if (s->out_queue->size() >= 10) {
                pthread_mutex_unlock(&s->out_mutex);
#if MUTEXLOG
            av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_unlock 232\n");
#endif
                usleep(10000);
                continue;
            }
            break;
        }
        s->out_queue->push_back(frame);
        pthread_mutex_unlock(&s->out_mutex);
#if MUTEXLOG
            av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_unlock 242\n");
#endif
#if MULTITHREAD
    } while (!decode_done && !s->stop_decode);
        s->thread_exited = true;
#else
    } while (0);
#endif

    return 0;
}

extern "C" int Stagefright_init(AVCodecContext *avctx)
{
    StagefrightContext *s = (StagefrightContext*)avctx->priv_data;
    sp<MetaData> meta, outFormat;
    int32_t colorFormat = 0;
    int ret;
#if PERFORMANCETEST
    totalcvtTime = 0;
    totalcvtFrame = 0;
#endif
    av_log(avctx, AV_LOG_ERROR, "Stagefright_init! %x %d\n",
        avctx->extradata,avctx->extradata_size);
    for(int j = 0;j<avctx->extradata_size;j++)
    {
        av_log(avctx, AV_LOG_INFO, "%x ",avctx->extradata[j]);
    }
    memset(s,0,sizeof(StagefrightContext));
    //if ts ,avctx->extradata[0] = 0
    if (!avctx->extradata || !avctx->extradata_size)// || avctx->extradata[0] != 1)
        return -1;
    av_log(avctx, AV_LOG_ERROR, "Stagefright_init 1\n");
    s->avctx = avctx;
    s->bsfc  = av_bitstream_filter_init("h264_mp4toannexb");
    if (!s->bsfc) {
        av_log(avctx, AV_LOG_ERROR, "Cannot open the h264_mp4toannexb BSF!\n");
        return -1;
    }
    av_log(avctx, AV_LOG_ERROR, "Stagefright_init 2\n");
    if(avctx->extradata[0] != 1)
    {//ts?
        if((avctx->extradata[0] == 0)&&(avctx->extradata[3] == 1))
        {//ts??
            av_log(avctx, AV_LOG_ERROR, "TS input??\n");
            s->orig_extradata_size = avctx->extradata_size+16;
            s->orig_extradata = (uint8_t*) av_mallocz(s->orig_extradata_size +
                                                  FF_INPUT_BUFFER_PADDING_SIZE);
            if (!s->orig_extradata)
               {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            GenExtradata(s->orig_extradata, &(s->orig_extradata_size), avctx->extradata, avctx->extradata_size);
            if(s->orig_extradata_size == 0)
            {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            for(int j = 0;j<(s->orig_extradata_size);j++)
            {
                av_log(avctx, AV_LOG_INFO, "%x ",s->orig_extradata[j]);
            }

        }
        else
        {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
    }
    else
    {
        s->orig_extradata_size = avctx->extradata_size;
        s->orig_extradata = (uint8_t*) av_mallocz(avctx->extradata_size +
                                                  FF_INPUT_BUFFER_PADDING_SIZE);
           if (!s->orig_extradata)
           {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        memcpy(s->orig_extradata, avctx->extradata, avctx->extradata_size);
    }

    meta = new MetaData;
    if (meta == NULL) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    meta->setCString(kKeyMIMEType, MEDIA_MIMETYPE_VIDEO_AVC);
    meta->setInt32(kKeyWidth, avctx->width);
    meta->setInt32(kKeyHeight, avctx->height);
//    meta->setData(kKeyAVCC, kTypeAVCC, avctx->extradata, avctx->extradata_size);
    meta->setData(kKeyAVCC, kTypeAVCC, s->orig_extradata, s->orig_extradata_size);
    av_log(avctx, AV_LOG_ERROR, "Stagefright_init 3\n");
    android::ProcessState::self()->startThreadPool();

    s->source    = new sp<MediaSource>();
    *s->source   = new CustomSource(avctx, meta);
    s->in_queue  = new List<Frame*>;
    s->out_queue = new List<Frame*>;
    s->client    = new OMXClient;
    s->end_frame = (Frame*)av_mallocz(sizeof(Frame));
    if (s->source == NULL || !s->in_queue || !s->out_queue || !s->client ||
        !s->end_frame) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    av_log(avctx, AV_LOG_ERROR, "Stagefright_init 4\n");
    if (s->client->connect() !=  OK) {
        av_log(avctx, AV_LOG_ERROR, "Cannot connect OMX client\n");
        ret = -1;
        goto fail;
    }

    s->decoder  = new sp<MediaSource>();
#if 0
    {
        void* pLibHandle = dlopen("libstagefright.so", RTLD_NOW);
        if (pLibHandle)
        {
                av_log(avctx, AV_LOG_ERROR, "dlsym dlopen Successfully\n");
            typedef sp<MediaSource> fn_OMXCodec_Create(const sp<IOMX> &omx, const sp<MetaData> &meta, bool createEncoder,
            const sp<MediaSource> &source, const char *matchComponentName, uint32_t flags,
            const int& nativeWindow);
                av_log(avctx, AV_LOG_ERROR, "dlsym start \n");
            fn_OMXCodec_Create* func = (fn_OMXCodec_Create*)dlsym(pLibHandle, ANDROID_V40_OMXCODEC_CREATE);
            if (func)
            {
                    av_log(avctx, AV_LOG_ERROR, "dlsym fn_OMXCodec_Create Successfully\n");
                const void* nativeWindow = NULL;
                *s->decoder = (*func)(s->client->interface(), meta, false, *s->source, NULL, 4,NULL);
                    av_log(avctx, AV_LOG_ERROR, "fn_OMXCodec_Create Call Successfully\n");
            }
            else
            {
                    av_log(avctx, AV_LOG_ERROR, "dlsym fn_OMXCodec_Create failed\n");
            }
        }
        else
        {
            dlclose(pLibHandle);
            av_log(avctx, AV_LOG_ERROR, "dlopen libstagefright.so failed\n");
        }
    }
#else
    *s->decoder = OMXCodec::Create(s->client->interface(), meta,
                                  false, *s->source, NULL,
                                  4);

#endif
    if ((*s->decoder)->start() !=  OK) {
        av_log(avctx, AV_LOG_ERROR, "Cannot start decoder\n");
        ret = -1;
        s->client->disconnect();
        goto fail;
    }
    av_log(avctx, AV_LOG_ERROR, "Stagefright_init 6\n");
    outFormat = (*s->decoder)->getFormat();
    outFormat->findInt32(kKeyColorFormat, &colorFormat);
    if (colorFormat == OMX_QCOM_COLOR_FormatYVU420SemiPlanar ||
        colorFormat == OMX_COLOR_FormatYUV420SemiPlanar||
        colorFormat == OMX_QOMX_COLOR_FormatYVU420PackedSemiPlanar32m4ka)
        avctx->pix_fmt = PIX_FMT_NV21;
    else if((colorFormat == OMX_QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka)||
        (colorFormat == OMX_TI_COLOR_FormatYUV420PackedSemiPlanar))
         avctx->pix_fmt = VIDEOPIXELFORMAT;
    else
        avctx->pix_fmt = PIX_FMT_YUV420P;
    av_log(avctx, AV_LOG_ERROR, "output colorFormat:0x%x \n",colorFormat);
    av_log(avctx, AV_LOG_ERROR, "avctx->pix_fmt:0x%x \n",avctx->pix_fmt);
    outFormat->findCString(kKeyDecoderComponent, &s->decoder_component);
    if (s->decoder_component)
        s->decoder_component = av_strdup(s->decoder_component);
    av_log(avctx, AV_LOG_ERROR, "Stagefright_init 7\n");
    pthread_mutex_init(&s->in_mutex, NULL);
    pthread_mutex_init(&s->out_mutex, NULL);
    pthread_cond_init(&s->condition, NULL);
#if MULTITHREAD
    pthread_create(&s->decode_thread_id, NULL, &decode_thread, avctx);
    s->thread_started = true;
    av_log(avctx, AV_LOG_ERROR, "Stagefright_init 8\n");
#endif
    return 0;

fail:
    av_bitstream_filter_close(s->bsfc);
    av_freep(&s->orig_extradata);
    av_freep(&s->end_frame);
    delete s->in_queue;
    delete s->out_queue;
    delete s->client;
    return ret;
}

extern "C" int Stagefright_decode_frame(AVCodecContext *avctx, void *data,
                                    int *data_size, AVPacket *avpkt)
{
    StagefrightContext *s = (StagefrightContext*)avctx->priv_data;
    Frame *frame;
    MediaBuffer *mbuffer;
    status_t status;
    size_t size;
    int64_t pts = 0;
    uint8_t *buf;
    const uint8_t *src_data[3];
    int w, h;
    int src_linesize[3];
    int orig_size = avpkt->size;
    AVPacket pkt = *avpkt;
    int ret;
    if (!s->thread_started) {
        pthread_create(&s->decode_thread_id, NULL, &decode_thread, avctx);
        s->thread_started = true;
    }
//    av_log(avctx, AV_LOG_ERROR, "Stagefright_decode_frame :%d\n",s->source_done);
#if BITSTREAMFILTER
    if (avpkt && avpkt->data) {
        av_bitstream_filter_filter(s->bsfc, avctx, NULL, &pkt.data, &pkt.size,
                                   avpkt->data, avpkt->size, avpkt->flags & AV_PKT_FLAG_KEY);
        avpkt = &pkt;
    }
#endif

    if (!s->source_done) {
#if NAL_INPUT

        uint8_t* pNalStart = avpkt->data;
        int nNalSize = pNalStart[0]<<24|pNalStart[1]<<16|pNalStart[2]<<8|pNalStart[3];//avpkt->size;//pNalStart[0]<<24|pNalStart[1]<<16|pNalStart[2]<<8|pNalStart[3];
        if(nNalSize == 1)
        {//00000001
           unsigned char* pTmp = avpkt->data;
        int tmpInLen = avpkt->size;
        //suppose just one sps one pps
        int NalStart = GetNal(pTmp,tmpInLen);
        while(NalStart >= 0)
        {
            {
                pTmp += NalStart;
                tmpInLen -= NalStart;
                pNalStart = pTmp;
                NalStart = GetNal(pTmp,tmpInLen);
                if(NalStart > 0)
                {
                    nNalSize = NalStart -4;
                }
                else
                {
                    nNalSize = tmpInLen;
                }
                    frame = (Frame*)av_mallocz(sizeof(Frame));
                    if (avpkt->data) {
                        frame->status  = OK;
                        frame->size    = nNalSize;
                        // Stagefright can't handle negative timestamps -
                        // if needed, work around this by offsetting them manually?
                        if (avpkt->pts >= 0)
                            frame->time    = avpkt->pts;
                        frame->key     = avpkt->flags & AV_PKT_FLAG_KEY ? 1 : 0;
                        frame->buffer  = (uint8_t*)av_malloc(nNalSize);
                        if (!frame->buffer) {
                            av_freep(&frame);
                            return AVERROR(ENOMEM);
                        }
                        memcpy(frame->buffer, pNalStart, nNalSize);
                    } else {
                        frame->status  = ERROR_END_OF_STREAM;
                        s->source_done = 1;
                        av_log(avctx, AV_LOG_INFO, "@@@@@@@End of frame#######\n");
                    }
                    while (true) {
                        if (s->thread_exited) {
                            s->source_done = 1;
                              av_log(avctx, AV_LOG_INFO, "@@@@@@@decoder Thread exited #######\n");
                            break;
                        }
                        pthread_mutex_lock(&s->in_mutex);
                        if (s->in_queue->size() >= 10) {
                            pthread_mutex_unlock(&s->in_mutex);
                            usleep(10000);
                            continue;
                        }
                        s->in_queue->push_back(frame);
                        pthread_cond_signal(&s->condition);
                        pthread_mutex_unlock(&s->in_mutex);
                        break;
                    }
            }
        }
        }
        else
        {
            pNalStart += 4;
            if(!s->dummy_buf) {
                s->dummy_buf = (uint8_t*)av_malloc(nNalSize);
                if (!s->dummy_buf)
                    return AVERROR(ENOMEM);
                s->dummy_bufsize = nNalSize;
                memcpy(s->dummy_buf, pNalStart, nNalSize);
            }
            while(pNalStart+nNalSize <= avpkt->data + avpkt->size)
            {
//                  av_log(avctx, AV_LOG_INFO, "######new frame size:%d#######\n",nNalSize);
/*               for(int j = 0;j<nNalSize;j++)
            {
                av_log(avctx, AV_LOG_INFO, "%x ",pNalStart[j]);
            }*/
                frame = (Frame*)av_mallocz(sizeof(Frame));
                if (avpkt->data) {
                    frame->status  = OK;
                    frame->size    = nNalSize;
                    // Stagefright can't handle negative timestamps -
                    // if needed, work around this by offsetting them manually?
                    if (avpkt->pts >= 0)
                        frame->time    = avpkt->pts;
                    frame->key     = avpkt->flags & AV_PKT_FLAG_KEY ? 1 : 0;
                    frame->buffer  = (uint8_t*)av_malloc(nNalSize);
                    if (!frame->buffer) {
                        av_freep(&frame);
                        return AVERROR(ENOMEM);
                    }
                    memcpy(frame->buffer, pNalStart, nNalSize);
                } else {
                    frame->status  = ERROR_END_OF_STREAM;
                    s->source_done = 1;
                    av_log(avctx, AV_LOG_INFO, "@@@@@@@End of frame#######\n");
                }
                while (true) {
                    if (s->thread_exited) {
                        s->source_done = 1;
                          av_log(avctx, AV_LOG_INFO, "@@@@@@@decoder Thread exited #######\n");
                        break;
                    }
                    pthread_mutex_lock(&s->in_mutex);
                    if (s->in_queue->size() >= 10) {
                        pthread_mutex_unlock(&s->in_mutex);
                        usleep(10000);
                        continue;
                    }
                    s->in_queue->push_back(frame);
                    pthread_cond_signal(&s->condition);
                    pthread_mutex_unlock(&s->in_mutex);
                    break;
                }
                if(pNalStart+nNalSize == avpkt->data + avpkt->size)
                {
                    break;
                }
                else
                {
                    pNalStart += nNalSize;
                            av_log(avctx, AV_LOG_INFO, "######new frame nNalSize:%x %x %x %x#######\n",
                                pNalStart[0], pNalStart[1], pNalStart[2], pNalStart[3]);
                    nNalSize = pNalStart[0]<<24|pNalStart[1]<<16|pNalStart[2]<<8|pNalStart[3];
                    pNalStart += 4;
                }
         }
            if(pNalStart+nNalSize != avpkt->data + avpkt->size)
            {
                  av_log(avctx, AV_LOG_INFO, "!!!!!!(pNalStart+nNalSize != avpkt->data + avpkt->size):%u,%u\n",pNalStart+nNalSize,avpkt->data + avpkt->size);
            }
        }
#else
        if(!s->dummy_buf) {
            s->dummy_buf = (uint8_t*)av_malloc(avpkt->size);
            if (!s->dummy_buf)
                return AVERROR(ENOMEM);
            s->dummy_bufsize = avpkt->size;
            memcpy(s->dummy_buf, avpkt->data, avpkt->size);
        }
        frame = (Frame*)av_mallocz(sizeof(Frame));
        if (avpkt->data) {
            frame->status  = OK;
            frame->size    = orig_size;
            // Stagefright can't handle negative timestamps -
            // if needed, work around this by offsetting them manually?
            if (avpkt->pts >= 0)
            {
                    frame->time    = avpkt->pts;
            }
            else
            {
                    frame->time    = AV_NOPTS_VALUE;
            }
            frame->key     = avpkt->flags & AV_PKT_FLAG_KEY ? 1 : 0;
            frame->buffer  = (uint8_t*)av_malloc(avpkt->size);
            if (!frame->buffer) {
                av_freep(&frame);
                return AVERROR(ENOMEM);
            }
            uint8_t *ptr = avpkt->data;
            // The OMX.SEC decoder fails without this.
            if (avpkt->size == orig_size + avctx->extradata_size)
                ptr += avctx->extradata_size;
            memcpy(frame->buffer, ptr, orig_size);
        } else {
            frame->status  = ERROR_END_OF_STREAM;
            s->source_done = 1;
        }
        while (true) {
            if (s->thread_exited) {
                s->source_done = 1;
                break;
            }
            pthread_mutex_lock(&s->in_mutex);
            if (s->in_queue->size() >= 10) {
                pthread_mutex_unlock(&s->in_mutex);
                usleep(10000);
                continue;
            }
            s->in_queue->push_back(frame);
            pthread_cond_signal(&s->condition);
            pthread_mutex_unlock(&s->in_mutex);
            break;
        }
#endif
    }
#if MULTITHREAD
#else
    decode_thread(avctx);
#endif
    while (true)
    {
    #if MUTEXLOG
            av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_lock 633\n");
#endif
        pthread_mutex_lock(&s->out_mutex);
        if (!s->out_queue->empty())
        {
              av_log(avctx, AV_LOG_INFO, "######new frame out#######\n");
            break;
        }
        pthread_mutex_unlock(&s->out_mutex);
#if MUTEXLOG
            av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_unlock 643\n");
#endif
        if (s->source_done)
        {
            usleep(10000);
            continue;
        }
        else
        {
            av_log(avctx, AV_LOG_INFO, "######s->source_done == FALSE#######\n");
            return orig_size;
        }
    }

    frame = *s->out_queue->begin();
    s->out_queue->erase(s->out_queue->begin());
    pthread_mutex_unlock(&s->out_mutex);
#if MUTEXLOG
            av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_unlock 661\n");
#endif
    mbuffer = frame->mbuffer;
    status  = frame->status;
    size    = frame->size;
    w       = frame->w;
    h       = frame->h;
    pts = frame->time;
    av_freep(&frame);
    if(size == 0)
    {
        goto end;
    }
    av_log(avctx, AV_LOG_INFO, "######new frame out:w %d h %d size %d#######\n",w,h,size);
    if (status == ERROR_END_OF_STREAM)
    {
    av_log(avctx, AV_LOG_INFO, "######ERROR_END_OF_STREAM#######\n");
        return 0;
    }
    if (status != OK)
    {
     av_log(avctx, AV_LOG_INFO, "######status != OK######\n");
        if (status == AVERROR(ENOMEM))
            return status;
        av_log(avctx, AV_LOG_ERROR, "Decode failed: %x\n", status);
        return -1;
    }

    // The OMX.SEC decoder doesn't signal the modified width/height
    if (s->decoder_component && !strncmp(s->decoder_component, "OMX.SEC", 7) &&
        (w & 15 || h & 15)) {
        if (((w + 15)&~15) * ((h + 15)&~15) * 3/2 == size) {
            w = (w + 15)&~15;
            h = (h + 15)&~15;
        }
    }

    if (!avctx->width || !avctx->height || avctx->width > w || avctx->height > h) {
        avctx->width  = w;
        avctx->height = h;
    }
    ret = avctx->reget_buffer(avctx, &s->ret_frame);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR, "reget buffer() failed\n");
        goto end;
    }

    buf = (uint8_t*)mbuffer->data() + mbuffer->range_offset();
    av_log(avctx, AV_LOG_ERROR, "mbuffer size:%d offset %d rangeLenght %d\n",
        mbuffer->size(),mbuffer->range_offset(),mbuffer->range_length());
    if(avctx->pix_fmt == VIDEOPIXELFORMAT)
    {
        sp<MetaData>  outFormat;
        int32_t colorFormat = 0;
        outFormat = (*s->decoder)->getFormat();
        outFormat->findInt32(kKeyColorFormat, &colorFormat);
#if    ANDROIDVERSION23
        if(colorFormat == OMX_TI_COLOR_FormatYUV420PackedSemiPlanar)
        {
            int mCropLeft, mCropTop, mCropRight, mCropBottom;
            outFormat->findRect(
                    kKeyCropRect,
                    &mCropLeft, &mCropTop, &mCropRight, &mCropBottom);
            if(w&1)
            {
                av_log(avctx, AV_LOG_ERROR, "warning: Stagefright_decode_frame frame width is odd %d\n",
                    w);
            }
//            av_log(avctx, AV_LOG_ERROR, "findRect:%d %d %d %d\n",mCropLeft, mCropTop, mCropRight, mCropBottom);
//            av_log(avctx, AV_LOG_ERROR, "retframe:linesize %d %d %d\n",s->ret_frame.linesize[0], s->ret_frame.linesize[1],
//                s->ret_frame.linesize[2]);
            uint8_t* dst = (uint8_t*)s->ret_frame.data[0];
            int src_height = mCropBottom - mCropTop +1;
            int src_width = mCropRight - mCropLeft +1;
            unsigned char* src_Y = buf;
            unsigned char* src_UV = buf + w*(h-mCropTop/2);
            yuv420SemiPlanar2RGBA(dst,
                               src_Y,
                               src_UV,
                               avctx->width,
                               avctx->height,
                               w,
                               (w+1)/2,
                               avctx->width<<2);
        }
        else if(colorFormat == OMX_QOMX_COLOR_FormatYUV420PackedSemiPlanar64x32Tile2m8ka)
#endif
        {
            void* dst = NULL;
            dst = s->ret_frame.data[0];
#if PERFORMANCETEST
            double startTime = getTime();
                      av_log(avctx, AV_LOG_ERROR, "convertNV12Tile:%f\n",startTime);
            convertNV12Tile(avctx->width, avctx->height, buf, 0, dst, avctx->width*4);
            double cvtTime = getTime() - startTime;
            totalcvtTime += cvtTime;
            totalcvtFrame += 1;

                      av_log(avctx, AV_LOG_ERROR, "convertNV12Tile:%f\n",cvtTime);
#else
            convertNV12Tile(avctx->width, avctx->height, buf, 0,dst, avctx->width*4);
#endif
        }
    }
    else
    {
        src_linesize[0] = w;
        if (avctx->pix_fmt == PIX_FMT_YUV420P)
            src_linesize[1] = src_linesize[2] = w/2;
        else if (avctx->pix_fmt == PIX_FMT_NV21)
            src_linesize[1] = w;

        src_data[0] = buf;
        src_data[1] = buf + src_linesize[0] * h;
        src_data[2] = src_data[1] + src_linesize[1] * h/2;
        av_image_copy(s->ret_frame.data, s->ret_frame.linesize,
                      src_data, src_linesize,
                      avctx->pix_fmt, avctx->width, avctx->height);
    }
    *data_size = sizeof(AVFrame);
    s->ret_frame.pkt_pts = pts;
    av_log(avctx, AV_LOG_ERROR, "######Decoded frame pts: %lld\n",s->ret_frame.pkt_pts);
    *(AVFrame*)data = s->ret_frame;
    ret = orig_size;
end:
    mbuffer->release();
    return ret;
}

extern "C" int Stagefright_close(AVCodecContext *avctx)
{
    StagefrightContext *s = (StagefrightContext*)avctx->priv_data;
    Frame *frame;
        av_log(avctx, AV_LOG_ERROR, "~~~~~~~stagefright_close\n");
#if PERFORMANCETEST
        av_log(avctx, AV_LOG_ERROR, "averagecvttime:\t%f\n",(totalcvtFrame>1)?(totalcvtTime/totalcvtFrame):(0));
#endif
    if (s->thread_started) {
        if (!s->thread_exited) {
            s->stop_decode = 1;
#if MUTEXLOG
            av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_lock 773\n");
#endif
            // Make sure decode_thread() doesn't get stuck
            pthread_mutex_lock(&s->out_mutex);
            while (!s->out_queue->empty()) {
                frame = *s->out_queue->begin();
                s->out_queue->erase(s->out_queue->begin());
                if (frame->size)
                    frame->mbuffer->release();
                av_freep(&frame);
            }
            pthread_mutex_unlock(&s->out_mutex);
#if MUTEXLOG
            av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_unlock 786\n");
#endif
            // Feed a dummy frame prior to signalling EOF.
            // This is required to terminate the decoder(OMX.SEC)
            // when only one frame is read during stream info detection.
                if(s->dummy_buf == NULL)
        {//allocate a buf
                av_log(avctx, AV_LOG_ERROR, "~~~~~~~stagefright_close\n");
                s->dummy_buf = (uint8_t*)av_malloc(s->orig_extradata_size);
                memcpy(s->dummy_buf,s->orig_extradata,s->orig_extradata_size);
                s->dummy_bufsize = s->orig_extradata_size;
        }
            if (s->dummy_buf && (frame = (Frame*)av_mallocz(sizeof(Frame)))) {
                frame->status = OK;
                frame->size   = s->dummy_bufsize;
                frame->key    = 1;
                frame->buffer = s->dummy_buf;
          av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_lock 2\n");
                pthread_mutex_lock(&s->in_mutex);
                s->in_queue->push_back(frame);
                pthread_cond_signal(&s->condition);
                pthread_mutex_unlock(&s->in_mutex);
          av_log(avctx, AV_LOG_ERROR, "~~~pthread_mutex_unlock 2\n");
                s->dummy_buf = NULL;
            }

            pthread_mutex_lock(&s->in_mutex);
            s->end_frame->status = ERROR_END_OF_STREAM;
            s->in_queue->push_back(s->end_frame);
            pthread_cond_signal(&s->condition);
            pthread_mutex_unlock(&s->in_mutex);
            s->end_frame = NULL;
        }

        pthread_join(s->decode_thread_id, NULL);

        if (s->ret_frame.data[0])
            avctx->release_buffer(avctx, &s->ret_frame);

        s->thread_started = false;
    }
        av_log(avctx, AV_LOG_ERROR, "~~~~~~~stagefright_close 1\n");
    while (!s->in_queue->empty()) {
        frame = *s->in_queue->begin();
        s->in_queue->erase(s->in_queue->begin());
        if (frame->size)
            av_freep(&frame->buffer);
        av_freep(&frame);
    }
        av_log(avctx, AV_LOG_ERROR, "~~~~~~~stagefright_close 2\n");
    while (!s->out_queue->empty()) {
        frame = *s->out_queue->begin();
        s->out_queue->erase(s->out_queue->begin());
//        if (frame->size)
            frame->mbuffer->release();
        av_freep(&frame);
    }
        av_log(avctx, AV_LOG_ERROR, "~~~~~~~stagefright_close 3\n");
        {
        (*s->decoder)->stop();
        s->client->disconnect();
        // The following hack is necessary to ensure that the OMX
        // component is completely released by the time we may try
        // to instantiate it again.
        wp<MediaSource> tmp = (*s->decoder);
        (*s->decoder).clear();
        while (tmp.promote() != NULL) {
            usleep(1000);
        }
        IPCThreadState::self()->flushCommands();
    }
    if (s->decoder_component)
        av_freep(&s->decoder_component);
    av_freep(&s->dummy_buf);
    av_freep(&s->end_frame);

    // Reset the extradata back to the original mp4 format, so that
    // the next invocation (both when decoding and when called from
    // av_find_stream_info) get the original mp4 format extradata.
//    av_freep(&avctx->extradata);
    av_freep(&s->orig_extradata);
    delete s->in_queue;
    delete s->out_queue;
    delete s->client;
    delete s->decoder;
    delete s->source;
        av_log(avctx, AV_LOG_ERROR, "~~~~~~~stagefright_close 4\n");
    pthread_mutex_destroy(&s->in_mutex);
    pthread_mutex_destroy(&s->out_mutex);
    pthread_cond_destroy(&s->condition);
    av_bitstream_filter_close(s->bsfc);
        av_log(avctx, AV_LOG_ERROR, "~~~~~~~stagefright_close 5\n");
    return 0;
}

extern "C" void Stagefright_flush(AVCodecContext *avctx)
{
    Stagefright_close(avctx);
    Stagefright_init(avctx);
}
static inline int GetNal(unsigned char* pIn, int InLen)
{
    int i = 0;
    int NalHeader = 0;
    for(i = 0;i< InLen - 5;i++)
    {
        NalHeader = (pIn[i]<<24|pIn[i+1]<<16|pIn[i+2]<<8|pIn[i+3]);
        if(NalHeader == 1)
        {
            return (i+4);
        }
    }
    return -1;
}

static void GenExtradata(unsigned char* pOut,int* pOutLen, unsigned char* pIn, int InLen)
{
    unsigned char* pSPS = NULL;
    unsigned char* pPPS = NULL;
    int SPSLen = 0;
    int PPSLen = 0;
    unsigned char* pTmp = pIn;
    int tmpInLen = InLen;
    //suppose just one sps one pps
    int NalStart = GetNal(pTmp,tmpInLen);
    while(NalStart >= 0)
    {
        //find sps
        if(pTmp[NalStart] == 0x67)
        {
               av_log(NULL, AV_LOG_ERROR, "find sps \n");
            pTmp = pTmp + NalStart;
            tmpInLen = tmpInLen - NalStart;
            pSPS = pTmp;
            NalStart = GetNal(pTmp,tmpInLen);
            if(NalStart > 0)
            {
                SPSLen = NalStart -4;
            }
            else
            {
                SPSLen = tmpInLen;
            }
        }
        else if(pTmp[NalStart] == 0x68)
        {//find pps
               av_log(NULL, AV_LOG_ERROR, "find pps \n");
            pTmp = pTmp + NalStart;
            tmpInLen = tmpInLen - NalStart;
            pPPS = pTmp;
            NalStart = GetNal(pTmp,tmpInLen);
            if(NalStart > 0)
            {
                PPSLen = NalStart -4;
            }
            else
            {
                PPSLen = tmpInLen;
            }
        }
        else
        {
            pTmp += NalStart;
            tmpInLen -= NalStart;
               av_log(NULL, AV_LOG_ERROR, "find other Nal:%x \n",*pTmp);
            NalStart = GetNal(pTmp,tmpInLen);
        }
    }
    if(pSPS&&pPPS)
    {
        pOut[0] = 1; /* version */
        pOut[1] = pSPS[1]; /* profile */
        pOut[2] = pSPS[2];/* profile compat */
        pOut[3] = pSPS[3];/* level */
        pOut[4] = 0xff;/* 6 bits reserved (111111) + 2 bits nal size length - 1 (11) */
        pOut[5] = 0xe1;/* 3 bits reserved (111) + 5 bits number of sps (00001) */
        pOut[6] = SPSLen>>8;
        pOut[7] = SPSLen&0xff;
        memcpy(pOut + 8, pSPS,SPSLen);
        *pOutLen = 8+SPSLen;
        pOut[*pOutLen] = 1;
        (*pOutLen)++;
        pOut[*pOutLen] = PPSLen>>8;
        (*pOutLen)++;
        pOut[*pOutLen] = PPSLen&0xff;
        (*pOutLen)++;
        memcpy(pOut + *pOutLen, pPPS,PPSLen);
        (*pOutLen) +=PPSLen;
    }
    else
    {
        (*pOutLen) = 0;
    }
}

static void yuv420SemiPlanar2RGBA(uint8_t *dst_ptr,
                               const uint8_t *y_ptr,
                               const uint8_t *uv_ptr,
                               int      width,
                               int      height,
                               int y_pitch,
                               int uv_pitch,
                               int rgb_pitch)
{
    unsigned char* u_ptr = (unsigned char*)av_malloc(uv_pitch*((height+1)/2));
    unsigned char* v_ptr = (unsigned char*)av_malloc(uv_pitch*((height+1)/2));
    cvtNV12BlockLine2YV12BlockLine(u_ptr, v_ptr, uv_ptr, uv_pitch*((height+1)/2));
    yuv420_2_rgba_neon(dst_ptr,
                                   y_ptr,
                                   u_ptr,
                                   v_ptr,
                                   width,
                                   height,
                                   y_pitch,
                                   uv_pitch,
                                   rgb_pitch);
    av_free(u_ptr);
    av_free(v_ptr);
}
#endif
