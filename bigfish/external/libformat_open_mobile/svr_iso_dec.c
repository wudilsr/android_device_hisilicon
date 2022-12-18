/*
 * svr_iso_dec.c
 *
 *  Created on: 2014Äê6ÔÂ17ÈÕ
 *      Author: z00187490
 */

#include <libavformat/avformat.h>
#include "libudf.h"

#define TRACE() av_log(s, AV_LOG_ERROR, "[%s,%d]", __FUNCTION__, __LINE__)
struct iso
{
    struct udf_api api;
    libudf_t*   udf;
    AVFormatContext* ctx;
};


static void iso_copy_stream(AVStream *to, AVStream *from)
{
    to->r_frame_rate    = from->r_frame_rate;
    to->time_base       = from->time_base;
    to->id              = from->id;
    to->metadata        = from->metadata;
    to->duration        = from->duration;
    to->need_parsing    = AVSTREAM_PARSE_NONE;
    to->request_probe   = 0;
    to->start_time      = 0;//make sure all streams start from 0
    to->discard = from->discard;

    from->metadata = NULL;
    avcodec_copy_context(to->codec, from->codec);
}

static int iso_probe(AVProbeData *p)
{
    int i;
    if (p->buf_size > 32768)
    {
        for (i = 32768; i < p->buf_size - 2; i++)
        {
            if (p->buf[i] == 'B' && p->buf[i+1] == 'E' && p->buf[i+2] =='A')
            {
                return 100;
            }
            else if (p->buf[i] == 'N' && p->buf[i+1] == 'S' && p->buf[i+2] =='R')
            {
                return 100;
            }
            else if (p->buf[i] == 'T' && p->buf[i+1] == 'E' && p->buf[i+2] =='A')
            {
                return 100;
            }
        }
    }
    return 0;
}

static int iso_read_header(AVFormatContext *s, AVFormatParameters *ap)
{
    TRACE();
    int ret;
    struct iso* iso = s->priv_data;
    const char* template = NULL;
    char* tmp_url = NULL;
    size_t size = 0;

    if (udf_api_load(&iso->api) < 0)
    {
        av_log(s, AV_LOG_ERROR, "load libudf failed");
        return -1;
    }
    //concat bluray url
    template = "bluray:udf://$(filename)?int_handle=0xffffffff&use_cache=1&udf_handle=0xffffffff#?playlist=-1";
    size = strlen(s->filename) + strlen(template);
    tmp_url = av_mallocz(size + 1);
    if (!tmp_url)
    {
        av_log(s, AV_LOG_ERROR, "malloc bluray string failed");
        goto failed;
    }
    snprintf(tmp_url, size, "%s?int_handle=%p&use_cache=1",
            s->filename, &s->interrupt_callback);
    iso->udf = iso->api.open(tmp_url);
    if (!iso->udf)
    {
        av_log(s, AV_LOG_ERROR, "udf open failed");
        goto failed;
    }

    snprintf(tmp_url, size, "bluray:udf://%s?int_handle=%p&udf_handle=0x%08x#?playlist=-1",
            s->filename, &s->interrupt_callback, iso->udf);

    av_log(s, AV_LOG_DEBUG, "open bluray: %s", tmp_url);
    AVInputFormat* fmt = av_find_input_format("blurayplay");
    ret = avformat_open_input(&iso->ctx, tmp_url, fmt, NULL);
    if (ret < 0)
    {
        av_log(s, AV_LOG_ERROR, "open format %s failed", fmt->long_name);
        goto failed;
    }
    av_freep(&tmp_url);
    int i;
    for (i = 0; i < iso->ctx->nb_streams; i++)
    {
        AVStream* st = avformat_new_stream(s, NULL);
        AVStream *ist = iso->ctx->streams[i];
        iso_copy_stream(st, ist);
    }
    s->duration = iso->ctx->duration;
    s->start_time = 0;
    TRACE();
    return 0;
failed:
    if (tmp_url)
    {
        free(tmp_url);
    }
    if (iso->udf)
    {
        iso->api.close(iso->udf);
        iso->udf = NULL;
    }
    return -1;
}

static int iso_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    struct iso* iso = s->priv_data;
    int ret = av_read_packet(iso->ctx, pkt);

    return ret;
}

static int iso_read_close(AVFormatContext *s)
{
    TRACE();
    struct iso* iso = s->priv_data;
    avformat_close_input(&iso->ctx);
    iso->api.close(iso->udf);
    udf_api_close(&iso->api);
    return 0;
}

static int iso_read_seek(AVFormatContext *s, int stream_index,
                         int64_t timestamp, int flags)
{
    TRACE();
    struct iso* iso = s->priv_data;
    ff_read_frame_flush(iso->ctx);
    return iso->ctx->iformat->read_seek(iso->ctx, stream_index, timestamp, flags);
}

AVInputFormat svr_iso_demuxer = {
    .name           = "iso",
    .long_name      = "ISO(UDF)",
    .priv_data_size = sizeof(struct iso),
    .read_probe     = iso_probe,
    .read_header    = iso_read_header,
    .read_packet    = iso_read_packet,
    .read_close     = iso_read_close,
    .read_seek      = iso_read_seek,
    .read_timestamp = NULL,
    .extensions     = "iso",
    .flags          = AVFMT_FLAG_NOPARSE,
};
