#ifndef __LIBSTAGEFRIGHT_H_
#define __LIBSTAGEFRIGHT_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include "libavcodec/avcodec.h"
#include <pthread.h>
struct TmpStagefrightContext {
    void *avctx;
    void *bsfc;
    void* orig_extradata;
    int orig_extradata_size;
    void *source;
    void *in_queue, *out_queue;
    pthread_mutex_t in_mutex, out_mutex;
    pthread_cond_t condition;
    pthread_t decode_thread_id;

    void *end_frame;
    int source_done;
    volatile sig_atomic_t thread_exited, stop_decode;

    AVFrame ret_frame;

    void *dummy_buf;
    int dummy_bufsize;

    void *client;
    void *decoder;
    const char *decoder_component;
    void* render;
};

int Stagefright_init(AVCodecContext *avctx);
int Stagefright_close(AVCodecContext *avctx);
void Stagefright_flush(AVCodecContext *avctx);
int Stagefright_decode_frame(AVCodecContext *avctx, void *data, int *data_size, AVPacket *avpkt);
int Stagefright_init_render(AVCodecContext *avctx,void* surface);
int Stagefright_render_frame(AVCodecContext *avctx,void* mediaBuffer);
int Stagefright_close_render(AVCodecContext *avctx);
#ifdef __cplusplus
}
#endif
#endif
