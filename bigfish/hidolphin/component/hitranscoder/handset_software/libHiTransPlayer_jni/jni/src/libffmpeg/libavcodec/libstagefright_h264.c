/*
 * Interface to the Android Stagefright library for
 * H/W accelerated H.264 decoding
 * Copyright (C) 2011 xuyangpo/x54178
 */
#include "libsf/libsf.h"
#include "avcodec.h"
static int LibStagefright_init(AVCodecContext *avctx)
{
    av_log(avctx, AV_LOG_ERROR, "#################LibStagefright_init!\n");
    return Stagefright_init(avctx);
}

static int LibStagefright_decode_frame(AVCodecContext *avctx, void *data,
                                    int *data_size, AVPacket *avpkt)
{
//    av_log(avctx, AV_LOG_ERROR, "###############LibStagefright_decode_frame!\n");
    return Stagefright_decode_frame(avctx, data,data_size, avpkt);
}

static int LibStagefright_close(AVCodecContext *avctx)
{
    return Stagefright_close(avctx);
}

static void LibStagefright_flush(AVCodecContext *avctx)
{
    av_log(avctx, AV_LOG_ERROR, "###############LibStagefright_flush!\n");
    Stagefright_flush(avctx);
}

AVCodec ff_libstagefright_h264_decoder = {
    "libstagefright_h264",
    AVMEDIA_TYPE_VIDEO,
    CODEC_ID_H264,
    sizeof(struct TmpStagefrightContext),
    LibStagefright_init,
    NULL, //encode
    LibStagefright_close,
    LibStagefright_decode_frame,
    CODEC_CAP_DELAY,
    NULL, //next
    LibStagefright_flush, //flush
    NULL, //supported_framerates
    NULL, //pixel_formats
    NULL_IF_CONFIG_SMALL("libstagefright H.264"),
};
