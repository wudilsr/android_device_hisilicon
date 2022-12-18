/*
 * HTTP protocol for ffmpeg client
 * Copyright (c) 2000, 2001 Fabrice Bellard
 *
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

/**
 * @file    hls.c
 * @brief   Apple HTTP Live Streaming demuxer
 *          http://tools.ietf.org/html/draft-pantos-http-live-streaming
 */
#if defined (ANDROID_VERSION)
#include "cutils/properties.h"
#endif
#include "libavutil/avstring.h"
#include "libavutil/intreadwrite.h"
#include "avformat.h"
#include "internal.h"
#include <unistd.h>
#include "avio.h"
#include "url.h"
#include "hls_read.h"
#include "libavutil/opt.h"

#if defined (ANDROID_VERSION)
#include "libclientadp.h"
#endif

#include <sys/time.h>
#include "hls_key_decrypt.h"

#define DISCONTINUE_MAX_US      (3000000)
#define IFRAME_ONLY_DISCONTINUE_MAX_US (60000000)

#define DEFAULT_PTS_ADDON       (1)         // 1 sec

#define INITIAL_BUFFER_SIZE     (32768 * 16) //512K
#define HLS_MAX_WAITE_TIME      (5 * AV_TIME_BASE)  // 3s
#define __FILE_NAME__           av_filename(__FILE__)

#define MAX_CHARACTERISTICS_LEN 512

#define DEC AV_OPT_FLAG_DECODING_PARAM
#define ENC AV_OPT_FLAG_ENCODING_PARAM
#define OFFSET(x) offsetof(HLSContext, x)

#define HLS_TIME_SHIFT_SEGMENT_NUM_MIN (30)

#ifndef HI_ADVCA_FUNCTION_RELEASE
const AVOption ff_hls_options[] = {
    { "download_speed_collect_freq_ms",  "download speed collect freq", OFFSET(download_speed_collect_freq_ms), AV_OPT_TYPE_INT, {.i64 = 0}, 0, INT_MAX, DEC|ENC},
    {"headers", "",  OFFSET(headers), AV_OPT_TYPE_STRING, { 0 }, 0, 0, DEC|ENC},
    {"uuid", "",  OFFSET(uuid), AV_OPT_TYPE_STRING, { 0 }, 0, 0, DEC|ENC},
    { NULL },
};
#else
const AVOption ff_hls_options[] = {
    { "download_speed_collect_freq_ms", "",  OFFSET(download_speed_collect_freq_ms), AV_OPT_TYPE_INT, {.i64 = 0}, 0, INT_MAX, DEC|ENC},
    {"headers", "",  OFFSET(headers), AV_OPT_TYPE_STRING, { 0 }, 0, 0, DEC|ENC},
    {"uuid", "",  OFFSET(uuid), AV_OPT_TYPE_STRING, { 0 }, 0, 0, DEC|ENC},
    { NULL },
};
#endif

/*******************************************************************************
 * Local prototypes
 ******************************************************************************/
enum HLS_KEY_TYPE {
    KEY_NONE,
    KEY_AES_128,
};

typedef struct hls_info_s {
    char bandwidth[20];
    char program_id[10];
    char codecs[30];
    char resolution[20];
    char audio[MAX_FIELD_LEN];
    char video[MAX_FIELD_LEN];
    char subtitles[MAX_FIELD_LEN];
} hls_info_t;

typedef struct hls_redition_info_s {
    char type[16];
    char uri[MAX_URL_SIZE];
    char group_id[MAX_FIELD_LEN];
    char language[MAX_FIELD_LEN];
    char assoc_language[MAX_FIELD_LEN];
    char name[MAX_FIELD_LEN];
    char defaultr[4];
    char forced[4];
    char characteristics[MAX_CHARACTERISTICS_LEN];
} hls_redition_info_t;

typedef struct hls_iframe_info_s {
    char video[MAX_FIELD_LEN];
    char codecs[30];
    char bandwidth[20];
    char uri[INITIAL_URL_SIZE];
} hls_iframe_info_t;

typedef struct hls_key_info_s {
    char    uri[INITIAL_URL_SIZE];
    char    method[10];
    char    iv[35];
} hls_key_info_t;

typedef enum HLS_START_MODE
{
    HLS_MODE_NORMAL,
    HLS_MODE_FAST,
    HLS_MODE_BUTT
} HLS_START_MODE_E;
#define LOG_TAG "hls"

static int hlsReditionReadDataCb(void *opaque, uint8_t *buf, int buf_size);
static int hlsReadDataCb(void *opaque, uint8_t *buf, int buf_size);

/*******************************************************************************
 * Local protofunctions
 ******************************************************************************/

static int hlsGetPtsScale(int64_t *discontinue_pts, int num, int idx, int64_t *scale_val)
{
    int i = 0;
    int64_t pts_min = AV_NOPTS_VALUE;

    for (i = 0; i < num; i++)
    {
        //av_log(NULL, AV_LOG_ERROR, "discontinue_pts[%d]=%lld \n", i, discontinue_pts[i]);
        if (discontinue_pts[i] != AV_NOPTS_VALUE
            && (discontinue_pts[i] < pts_min
            || pts_min == AV_NOPTS_VALUE))
        {
            pts_min = discontinue_pts[i];
        }
    }

    if (discontinue_pts[idx] > pts_min
        && discontinue_pts[idx] != AV_NOPTS_VALUE
        && pts_min != AV_NOPTS_VALUE)
    {
        *scale_val = discontinue_pts[idx] - pts_min;
    }
    else
    {
        *scale_val = 0;
    }

    return 0;
}

static int hlsGetLine(ByteIOContext *s, char *buf, int maxlen, AVIOInterruptCB *interrupt_callback)
{
    char c;
    int i = 0;

    do {
        if (s->eof_reached) // Stream eof
            return 0;

        c = url_fgetc(s);
        if ((char)URL_EOF != c && i < maxlen-1)
            buf[i++] = c;
        //if(url_interrupt_cb(userdata))
        if (ff_check_interrupt(interrupt_callback)) {
            return AVERROR_EOF;
        }
    } while (c != '\r' && c != '\n' && (char)URL_EOF != c);

    buf[i] = 0;
    return i;
}

static int hlsReadLine(ByteIOContext *s, char *buf, int maxlen, AVIOInterruptCB *interrupt_callback)
{
    memset(buf, 0, maxlen);
    int len = hlsGetLine(s, buf, maxlen, interrupt_callback);
    while (len > 0 && isspace(buf[len - 1]))
        buf[--len] = '\0';

    return len;
}

static void hlsMakeAbsoluteUrl(char *buf, int size, const char *base,
        const char *rel)
{
    char *sep;

    /* Absolute path, relative to the current server */
    if (base && strstr(base, "://") && rel[0] == '/') {
        if (base != buf)
            av_strlcpy(buf, base, size);
        sep = strstr(buf, "://");
        if (sep) {
            sep += 3;
            sep = strchr(sep, '/');
            if (sep)
                *sep = '\0';
        }
        av_strlcat(buf, rel, size);
        return;
    }

    /* If rel actually is an absolute url, just copy it */
    if (!base || strstr(rel, "://") || rel[0] == '/') {
        av_strlcpy(buf, rel, size);
        return;
    }

    if (base != buf) av_strlcpy(buf, base, size);

    /* Remove the para from the base url */
    sep = strstr(buf, "?");
    if (sep)
        *sep = '\0';

    /* Remove the file name from the base url */
    sep = strrchr(buf, '/');
    if (sep)
        sep[1] = '\0';
    else
        buf[0] = '\0';

    while (av_strstart(rel, "../", NULL) && sep) {
        /* Remove the path delimiter at the end */
        sep[0] = '\0';
        sep = strrchr(buf, '/');
        /* If the next directory name to pop off is "..", break here */
        if (!av_strcmp(sep ? &sep[1] : buf, "..")) {
            /* Readd the slash we just removed */
            av_strlcat(buf, "/", size);
            break;
        }
        /* Cut off the directory name */
        if (sep)
            sep[1] = '\0';
        else
            buf[0] = '\0';
        rel += 3;
    }

    av_strlcat(buf, rel, size);
}

typedef void (*hlsParseKeyValCb)(void *context, const char *key,
                                 int key_len, char **dest, int *dest_len);
static void hlsParseKeyValue(const char *str, hlsParseKeyValCb callback_get_buf, void *context)
{
    const char *ptr = str;

    /* Parse key=value pairs. */
    for (;;) {
        const char *key;
        char *dest = NULL, *dest_end;
        int key_len, dest_len = 0;

        /* Skip whitespace and potential commas. */
        while (*ptr && (isspace(*ptr) || *ptr == ','))
            ptr++;
        if (!*ptr)
            break;

        key = ptr;

        if (!(ptr = strchr(key, '=')))
            break;
        ptr++;
        key_len = ptr - key;

        callback_get_buf(context, key, key_len, &dest, &dest_len);
        dest_end = dest + dest_len - 1;

        if (*ptr == '\"') {
            ptr++;
            while (*ptr && *ptr != '\"') {
                if (*ptr == '\\') {
                    if (!ptr[1])
                        break;
                    if (dest && dest < dest_end)
                        *dest++ = ptr[1];
                    ptr += 2;
                } else {
                    if (dest && dest < dest_end)
                        *dest++ = *ptr;
                    ptr++;
                }
            }
            if (*ptr == '\"')
                ptr++;
        } else {
            for (; *ptr && !(isspace(*ptr) || *ptr == ','); ptr++)
                if (dest && dest < dest_end)
                    *dest++ = *ptr;
        }
        if (dest)
            *dest = 0;
    }
}

static void hlsResetPacket(AVPacket *pkt)
{
    av_init_packet(pkt);
    pkt->data = NULL;
}

/* Free all segments context of hls_stream */
static void hlsFreeSegmentList(hls_stream_info_t *hls)
{
    int i;
    for (i = 0; i < hls->seg_list.hls_segment_nb; i++) {
        av_free(hls->seg_list.segments[i]);
    }

    hls->seg_list.hls_segment_nb = 0;
    av_freep(&hls->seg_list.segments);
}

static void hlsCloseInput(hls_stream_info_t *hls)
{
    /* WARN: close IO_decrypt first ! */
    if (hls->seg_key.IO_decrypt) {
        hls_decrypt_close(hls->seg_key.IO_decrypt);
        av_freep(&hls->seg_key.IO_decrypt);
        hls->seg_key.IO_decrypt = NULL;
        hls->seg_stream.input = NULL; // already freed in hls_decrypt_close
        hls->seg_stream.offset = 0;
    }
    if (hls->seg_stream.input) {
        hls_close(hls->seg_stream.input);
        hls->seg_stream.input = NULL;
        hls->seg_stream.offset = 0;
    }
}

static void hlsCloseStream(hls_stream_info_t *hls)
{
    av_free_packet(&hls->seg_demux.pkt);
    hlsResetPacket(&hls->seg_demux.pkt);
    hlsCloseInput(hls);
    av_freep(&hls->seg_stream.IO_pb.buffer);
    if (hls->seg_demux.ctx) {
        hls->seg_demux.ctx->pb = NULL;
        av_close_input_file(hls->seg_demux.ctx);
        hls->seg_demux.ctx = NULL;
    }
}

static void hlsFreeHlsStream(hls_stream_info_t *hls)
{
    hlsFreeSegmentList(hls);
    av_free_packet(&hls->seg_demux.pkt);
    if (hls->seg_stream.headers) {
        av_free(hls->seg_stream.headers);
        hls->seg_stream.headers = NULL;
    }
    hlsCloseStream(hls);
    if (!hls->is_redition_stream &&
        hls->attr.v.reditions) {
        av_freep(&hls->attr.v.reditions);
        hls->attr.v.nb_reditions = 0;
    }
}

/* Free all hls_stream context of hls_context */
static void hlsFreeHlsList(HLSContext *c)
{
    int i;

    for (i = 0; i < c->hls_stream_nb; i++) {
        hls_stream_info_t *hls = c->hls_stream[i];
        hlsFreeHlsStream(hls);
        av_free(hls);
    }
    av_freep(&c->hls_stream);
    c->hls_stream_nb = 0;

    for (i = 0; i < c->nb_reditions; i++) {
        hls_stream_info_t *rend = c->reditions[i];
        hlsFreeHlsStream(rend);
        av_free(rend);
    }
    if (c->reditions) {
        av_freep(&c->reditions);
    }
    c->nb_reditions = 0;
}

static inline void hls_init_stream(hls_stream_info_t *hls,  int bandwidth,
        const char *url, const char *base, const char *headers)
{
    hls->bandwidth = bandwidth;

    if (headers)
        hls->seg_stream.headers = av_strdup(headers);

    hlsMakeAbsoluteUrl(hls->url, sizeof(hls->url), base, url);
}

static hls_stream_info_t *hls_new_stream(HLSContext *c, int bandwidth,
        const char *url, const char *base, const char *headers)
{
    hls_stream_info_t *hls = av_mallocz(sizeof(hls_stream_info_t));

    if (!hls) return NULL;

    av_log(c->parent, AV_LOG_INFO, "[%s:%d]: NEW HLS stream info ==> bandwidth=%d url=%s base=%s headers=%s\n",
            __FUNCTION__, __LINE__,
            bandwidth, url, base, headers);
    hls_init_stream(hls, bandwidth, url, base, headers);
    hlsResetPacket(&hls->seg_demux.pkt);
    return hls;
}

static void hls_del_stream(hls_stream_info_t *hls)
{
    int i;
    if (hls) {
        av_freep(&hls->seg_stream.headers);
        av_free(hls);
    }
}

static hls_stream_info_t *hlsNewHlsStream(HLSContext *c, int bandwidth,
        const char *url, const char *base, const char *headers)
{
    int add_ret;
    hls_stream_info_t *hls = hls_new_stream(c, bandwidth, url, base, headers);
    if (!hls)
        return NULL;

    dynarray_add_noverify(&c->hls_stream, &c->hls_stream_nb, hls, &add_ret);
    if (add_ret < 0){
        hls_del_stream(hls);
        hls = NULL;
    }
    return hls;
}

static void hlsHandleArgs(hls_info_t *info, const char *key, int key_len, char **dest, int *dest_len)
{
    if (!strncmp(key, "BANDWIDTH=", key_len)) {
        *dest     =        info->bandwidth;
        *dest_len = sizeof(info->bandwidth);
    } else if (!strncmp(key, "PROGRAM-ID=", key_len)) {
        *dest     =        info->program_id;
        *dest_len = sizeof(info->program_id);
    } else if (!strncmp(key, "CODECS=", key_len)) {
        *dest     =        info->codecs;
        *dest_len = sizeof(info->codecs);
    } else if (!strncmp(key, "RESOLUTION=", key_len)) {
        *dest     =        info->resolution;
        *dest_len = sizeof(info->resolution);
    } else if (!strncmp(key, "AUDIO=", key_len)) {
        *dest     =        info->audio;
        *dest_len = sizeof(info->audio);
    } else if (!strncmp(key, "VIDEO=", key_len)) {
        *dest     =        info->video;
        *dest_len = sizeof(info->video);
    } else if (!strncmp(key, "SUBTITLES=", key_len)) {
        *dest     =        info->subtitles;
        *dest_len = sizeof(info->subtitles);
    }
}

static void hlsHandleRenditionArgs(struct hls_redition_info_s *info, const char *key,
                                  int key_len, char **dest, int *dest_len)
{
    if (!strncmp(key, "TYPE=", key_len)) {
        *dest     =        info->type;
        *dest_len = sizeof(info->type);
    } else if (!strncmp(key, "URI=", key_len)) {
        *dest     =        info->uri;
        *dest_len = sizeof(info->uri);
    } else if (!strncmp(key, "GROUP-ID=", key_len)) {
        *dest     =        info->group_id;
        *dest_len = sizeof(info->group_id);
    } else if (!strncmp(key, "LANGUAGE=", key_len)) {
        *dest     =        info->language;
        *dest_len = sizeof(info->language);
    } else if (!strncmp(key, "ASSOC-LANGUAGE=", key_len)) {
        *dest     =        info->assoc_language;
        *dest_len = sizeof(info->assoc_language);
    } else if (!strncmp(key, "NAME=", key_len)) {
        *dest     =        info->name;
        *dest_len = sizeof(info->name);
    } else if (!strncmp(key, "DEFAULT=", key_len)) {
        *dest     =        info->defaultr;
        *dest_len = sizeof(info->defaultr);
    } else if (!strncmp(key, "FORCED=", key_len)) {
        *dest     =        info->forced;
        *dest_len = sizeof(info->forced);
    } else if (!strncmp(key, "CHARACTERISTICS=", key_len)) {
        *dest     =        info->characteristics;
        *dest_len = sizeof(info->characteristics);
    }
    /*
     * ignored:
     * - AUTOSELECT: client may autoselect based on e.g. system language
     * - INSTREAM-ID: EIA-608 closed caption number ("CC1".."CC4")
     */
}

static void hlsHandleIframeVariantArgs(struct hls_iframe_info_s *info, const char *key,
                                int key_len, char **dest, int *dest_len)
{
    if (!strncmp(key, "BANDWIDTH=", key_len)) {
        *dest     =        info->bandwidth;
        *dest_len = sizeof(info->bandwidth);
    } else if (!strncmp(key, "VIDEO=", key_len)) {
        *dest     =        info->video;
        *dest_len = sizeof(info->video);
    } else if (!strncmp(key, "CODECS=", key_len)) {
        *dest     =        info->codecs;
        *dest_len = sizeof(info->codecs);
    } else if (!strncmp(key, "URI=", key_len)) {
        *dest     =        info->uri;
        *dest_len = sizeof(info->uri);
    }
}

static void hlsHandleKeyArgs(hls_key_info_t *info, const char *key,
        int key_len, char **dest, int *dest_len)
{
    if (!strncmp(key, "METHOD=", key_len)) {
        *dest     =        info->method;
        *dest_len = sizeof(info->method);
    } else if (!strncmp(key, "URI=", key_len)) {
        *dest     =        info->uri;
        *dest_len = sizeof(info->uri);
    } else if (!strncmp(key, "IV=", key_len)) {
        *dest     =        info->iv;
        *dest_len = sizeof(info->iv);
    }
}

static int hlsSetReditionAttr(hls_redition_info_t *info, hls_redition_attr_s *attr)
{
    int ret = 0;

    if (!info || !attr) {
        return -1;
    }
    snprintf(attr->group_id, sizeof(attr->group_id), "%s", info->group_id);
    snprintf(attr->name, sizeof(attr->name), "%s", info->name);
    snprintf(attr->language, sizeof(attr->language), "%s", info->language);
    if (!strncasecmp(info->type, "AUDIO", sizeof(info->type))) {
        attr->type = HLSMEDIA_AUDIO;
    } else if (!strncasecmp(info->type, "VIDEO", sizeof(info->type))){
        attr->type = HLSMEDIA_VIDEO;
    } else if (!strncasecmp(info->type, "SUBTITLES", sizeof(info->type))) {
        attr->type = HLSMEDIA_SUBTITLE;
    } else if (!strncasecmp(info->type, "CLOSED-CAPTIONS", sizeof(info->type))) {
        attr->type = HLSMEDIA_CLOSED_CAPTIONS;
    } else {
        ret = -1;
        attr->type = HLSMEDIA_BUTT;
        av_log(0, AV_LOG_ERROR, "[%s,%d] unknown media type %s\n",
            __FILE_NAME__, __LINE__, info->type);
    }
    attr->defaulti = 0;
    if (strlen(info->defaultr) > 0 &&
        !strncasecmp(info->defaultr, "YES", sizeof(info->defaultr))) {
        attr->defaulti = 1;
    }
    attr->forced = 0;
    if (strlen(info->forced) > 0 &&
        !strncasecmp(info->forced, "YES", sizeof(info->forced))) {
        attr->forced= 1;
    }
    attr->autoselect = 0;

    return ret;
}

static int hlsAddReditionToVariant(HLSContext *c, hls_stream_info_t *variant,
    enum hls_media_type type, const char *group_id)
{
    int i, add_ret = 0;

    if (c->nb_reditions <= 0) {
        return 0;
    }

    for (i = 0; i < c->nb_reditions; i++) {
        hls_stream_info_t *rend = c->reditions[i];
        /* ignore the reditions those are already in variant */
        if (rend->seg_list.hls_segment_nb <= 0) {
            continue;
        }
        if (rend->attr.r.type == type &&
            !strncmp(rend->attr.r.group_id, group_id, FFMAX(strlen(group_id), strlen(rend->attr.r.group_id)))) {
            dynarray_add_noverify(&variant->attr.v.reditions, &variant->attr.v.nb_reditions, rend, &add_ret);
            if (add_ret < 0){
                return AVERROR(ENOMEM);
            }
        }
    }

    return 0;
}

static int hlsParseM3U8(HLSContext *c, char *url,
        hls_stream_info_t *hls, ByteIOContext *in)
{
    hls_info_t variant_info;
    int ret = 0, duration = 0, is_segment = 0, is_hls = 0, bandwidth = 0, video_codec = 0, audio_codec = 0, start_time = 0;
    char line[1024];
    const char *ptr;
    int close_in = 0;

    enum HLS_KEY_TYPE key_type = KEY_NONE;
    uint8_t iv[16] = "";
    int has_iv = 0;
    char key[INITIAL_URL_SIZE];
    AVDictionary *opts = NULL;
    int  hls_finished = 0;
    time_t  timeSec = 0;
    int save_hls=0;
    int64_t seg_size = -1, seg_offset = 0;

    /**make resolution change available from 3716c-0.6.3 r41002 changed by duanqingpeng**/
    /*HLSContext *hls_c = NULL;

    if (NULL != hls && NULL != hls->seg_demux.parent)
        hls_c = hls->seg_demux.parent->priv_data;
    */
    if (!in) {
        close_in = 1;

        if (c->user_agent && strlen(c->user_agent) > 0)
            av_dict_set(&opts, "user-agent", c->user_agent, 0);

        if (c->referer && strlen(c->referer) > 0)
            av_dict_set(&opts, "referer", c->referer, 0);

        if (c->cookies && strlen(c->cookies) > 0)
            av_dict_set(&opts, "cookies", c->cookies, 0);

        if (c->headers && strlen(c->headers) > 0)
            av_dict_set(&opts, "headers", c->headers, 0);

        ret = avio_open_h(&in, url, URL_RDONLY, &c->interrupt_callback, &opts);
        av_dict_free(&opts);

        if (0 > ret) {
            if (hls && 0 < strlen(hls->org_url) && av_strscmp(hls->org_url, url)
                && (AVERROR_HTTP_FORBIDDEN == ret
                    || AVERROR_HTTP_NOT_FOUND == ret
                    || AVERROR_HTTP_OTHER_4XX == ret
                    || AVERROR_HTTP_SERVER_ERROR == ret
                    || CHECK_NET_INTERRUPT(ret))) {
                /* if server error, use original url next time */
                av_strlcpy(url, hls->org_url, INITIAL_URL_SIZE);
                av_log(0, AV_LOG_ERROR, "server error use original url:%s\n", url);
            }
            return ret;
        }

        /* Set url to http location url. */
        URLContext *uc = in->opaque;
        if (uc && uc->moved_url) {
            memset(url, 0, INITIAL_URL_SIZE);
            snprintf(url, INITIAL_URL_SIZE, "%s", uc->moved_url);
        }
    }

    if ( c->ready_to_record_ts == 1)
    {
        save_hls =1;
    }

    if (save_hls)
    {
        uint32_t time = 0;
        char buf[INITIAL_URL_SIZE];

        memset(buf, 0, sizeof(buf));
        time = av_getsystemtime();
        snprintf(buf, sizeof(buf)-1, "download m3u8 at time[%u ms]\n\n", time);

        if (c->mufp)
        {
            fwrite(buf, 1, strlen(buf), c->mufp);
            fflush(c->mufp);
        }
    }

    hlsReadLine(in, line, sizeof(line), &c->interrupt_callback);

    if (save_hls && c->mufp)
    {
        fwrite(line, 1, strlen(line), c->mufp);
        fwrite("\n", 1, 1, c->mufp);
        fflush(c->mufp);
    }

    if (av_strcmp(line, "#EXTM3U")) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    if (hls) {
        hlsFreeSegmentList(hls);
        hls->seg_list.hls_finished = 0;
    }

    while (!url_feof(in)) {
        hlsReadLine(in, line, sizeof(line), &c->interrupt_callback);
        if (save_hls && c->mufp)
        {
            fwrite(line, 1, strlen(line), c->mufp);
            fwrite("\n", 1, 1, c->mufp);
            fflush(c->mufp);
        }

        if (ff_check_interrupt(&c->interrupt_callback)) {
            ret = AVERROR_EOF;
            goto fail;
        }

        if (av_strstart(line, "#EXTM3U", &ptr)) { // Allow only one m3u8 playlist
            break;
        } if (av_strstart(line, "#EXT-X-STREAM-INF:", &ptr)) {
            is_hls = 1;
            memset(&variant_info, 0, sizeof(variant_info));
            hlsParseKeyValue(ptr, (hlsParseKeyValCb) hlsHandleArgs, &variant_info);
            bandwidth = atoi(variant_info.bandwidth);

            /*audiocodecs description:
                        // generic for MPEG-2 Part 7 & MPEG-4 Part 2 AAC
                        "mp4a",
                        // MPEG-2 Part 7 & MPEG-4 Part 2 AAC, Low-Complexity Profile
                        "mp4a.40.2",
                        "mp4a.40.5",
                        "mp4a.40.34"
                    */
            if(strstr(variant_info.codecs, "mp4a."))
            {
                audio_codec = 1;
            }
            /* videocodecs description:
                        // generic for MPEG-4 Part 10 H.264/AVC
                        "avc1",
                        // MPEG-4 Part 10 H.264/AVC, Baseline Profile
                        "avc1.42e00a", // level 1.0
                        "avc1.42e00b", // level 1.1
                        "avc1.42e00c", // level 1.2
                        "avc1.42e00d", // level 1.3
                        "avc1.42e014", // level 2.0
                        "avc1.42e015", // level 2.1
                        "avc1.42e016", // level 2.2
                        "avc1.42e01e", // level 3.0
                        "avc1.42e01f", // level 3.1
                        "avc1.42e020", // level 3.2
                        "avc1.42e028", // level 4.0
                        // MPEG-4 Part 10 H.264/AVC, Main Profile
                        "avc1.4d400a", // level 1.0
                        "avc1.4d400b", // level 1.1
                        "avc1.4d400c", // level 1.2
                        "avc1.4d400d", // level 1.3
                        "avc1.4d4014", // level 2.0
                        "avc1.4d4015", // level 2.1
                        "avc1.4d4016", // level 2.2
                        "avc1.4d401e", // level 3.0
                        "avc1.4d401f", // level 3.1
                        "avc1.4d4020", // level 3.2
                        "avc1.4d4028", // level 4.0
                        // MPEG-4 Part 10 H.264/AVC, High Profile
                        "avc1.64000a", // level 1.0
                        "avc1.64000b", // level 1.1
                        "avc1.64000c", // level 1.2
                        "avc1.64000d", // level 1.3
                        "avc1.640014", // level 2.0
                        "avc1.640015", // level 2.1
                        "avc1.640016", // level 2.2
                        "avc1.64001e", // level 3.0
                        "avc1.64001f", // level 3.1
                        "avc1.640020", // level 3.2
                        "avc1.640028", // level 4.0
                        // MPEG-4 Part 2 Visual Simple Profile
                        "mp4v.20.9", // level 0
                        // MPEG-4 Part 2 Visual Advanced Simple Profile
                        "mp4v.20.240"  // level 0
                  */
            if(strstr(variant_info.codecs, "avc1.") || strstr(variant_info.codecs, "mp4v."))
            {
                video_codec = 1;
            }
        }
        else if (av_strstart(line, "#EXT-X-I-FRAME-STREAM-INF:", &ptr)) {
            hls_stream_info_t *iframe_hls = NULL;
            hls_iframe_info_t iframe_hls_info;
            memset(&iframe_hls_info, 0, sizeof(iframe_hls_info));
            ff_parse_key_value(ptr, (ff_parse_key_val_cb) hlsHandleIframeVariantArgs,
                               &iframe_hls_info);
            iframe_hls = hlsNewHlsStream(c, atoi(iframe_hls_info.bandwidth), iframe_hls_info.uri, url, c->headers);
            if (!iframe_hls) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            snprintf(iframe_hls->attr.v.video_group, sizeof(iframe_hls->attr.v.video_group), "%s", iframe_hls_info.video);
            iframe_hls->iframe_only = 1;
            iframe_hls->video_codec = 1;
            av_log(0, AV_LOG_INFO, "[%s,%d] iframe only variant, url='%s'\n",
                __FUNCTION__, __LINE__, iframe_hls_info.uri);
        }
        else if (av_strstart(line, "#EXT-X-I-FRAMES-ONLY:", &ptr)) {
            if (!hls) {
                hls = hlsNewHlsStream(c, 0, url, NULL, c->headers);
                if (!hls) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }
            hls->iframe_only = 1;
            hls->video_codec = 1;
            av_log(0, AV_LOG_INFO, "[%s,%d] iframe only variant, url='%s'\n",
                __FUNCTION__, __LINE__, url?url:"null");
        }
        else if (av_strstart(line, "#EXT-X-MEDIA:", &ptr)) {
            hls_redition_info_t rend_info;
            memset(&rend_info, 0, sizeof(rend_info));
            hlsParseKeyValue(ptr, (hlsParseKeyValCb) hlsHandleRenditionArgs, &rend_info);
            if (strlen(rend_info.uri) > 0) {
                hls_stream_info_t *rend  = hls_new_stream(c, 0, rend_info.uri, url, NULL);

                if (!rend) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
                dynarray_add_noverify(&c->reditions, &c->nb_reditions, rend, &ret);
                if (ret < 0) {
                    av_free(rend);
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
                rend->is_redition_stream = 1;
                hlsSetReditionAttr(&rend_info, &rend->attr.r);
                av_log(c->parent, AV_LOG_INFO, "[%s,%d] new redition type=%s\n",
                    __FILE_NAME__, __LINE__, rend_info.type);
            }
        }
        else if (av_strstart(line, "#EXT-X-BYTERANGE:", &ptr)) {
            seg_size = atoi(ptr);
            ptr = strchr(ptr, '@');
            if (ptr)
                seg_offset = atoi(ptr+1);
        }
        else if (av_strstart(line, "#EXT-X-KEY:", &ptr)) {
            hls_key_info_t info = {{0}};
            hlsParseKeyValue(ptr, (hlsParseKeyValCb) hlsHandleKeyArgs, &info);

            key_type = KEY_NONE;
            has_iv = 0;

            if (!av_strcmp(info.method, "AES-128"))
                key_type = KEY_AES_128;
            if (!strncmp(info.iv, "0x", 2) || !strncmp(info.iv, "0X", 2)) {
                ff_hex_to_data(iv, info.iv + 2);
                has_iv = 1;
            }
            av_strlcpy(key, info.uri, sizeof(key));
        } else if (av_strstart(line, "#EXT-X-TARGETDURATION:", &ptr)) {
            if (!hls) {
                hls = hlsNewHlsStream(c, 0, url, NULL, c->headers);
                if (!hls) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }

            hls->seg_list.hls_target_duration = atoi(ptr);
        } else if (av_strstart(line, "#EXT-X-MEDIA-SEQUENCE:", &ptr)) {
            if (!hls) {
                hls = hlsNewHlsStream(c, 0, url, NULL, c->headers);
                if (!hls) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
            }

            hls->seg_list.hls_seg_start = atoi(ptr);
            av_log(NULL, AV_LOG_ERROR, "[%s:%d], hls_seg_start = %d \n",
                __FUNCTION__, __LINE__, hls->seg_list.hls_seg_start);
        } else if (av_strstart(line, "#EXT-X-ENDLIST", &ptr)) {
            if (hls)
                hls->seg_list.hls_finished = 1;
            hls_finished = 1;
            av_log(NULL, AV_LOG_ERROR, "[%s:%d], find endlist tag \n", __FUNCTION__, __LINE__);
            break;
        } else if (av_strstart(line, "#EXTINF:", &ptr)) {
            is_segment = 1;
            duration   = atof(ptr) * 1000;
            if (duration > 0 && duration < hls->seg_list.hls_target_duration)
                hls->seg_list.hls_target_duration = duration;
            else if (duration == 0)
                hls->seg_list.hls_target_duration = hls->seg_list.hls_target_duration;

            //av_log(NULL, AV_LOG_ERROR, "#EXTINF:%d ,fresh target duraion = %d \n",
            //    duration, hls->seg_list.hls_target_duration);
        } else if (av_strstart(line, "#EXT-X-PROGRAM-DATE-TIME:", &ptr)) {
            int tm_year = 0, tm_mon = 0, tm_day = 0, tm_hour = 0, tm_min = 0, tm_sec = 0;

            sscanf(ptr, "%d-%d-%dT%d:%d:%dZ",
                &tm_year, &tm_mon, &tm_day, &tm_hour, &tm_min, &tm_sec);

            struct tm ptm[1];
            memset(ptm, 0, sizeof(ptm));
            ptm[0].tm_sec  = tm_sec;
            ptm[0].tm_min  = tm_min;
            ptm[0].tm_hour = tm_hour;
            ptm[0].tm_mday = tm_day;
            ptm[0].tm_mon  = tm_mon;
            ptm[0].tm_year = tm_year - 1900;

            timeSec = mktime(ptm);
            //av_log(NULL, AV_LOG_ERROR, "prgram timesec = %d \n", timeSec);
        } else if (av_strstart(line, "#", NULL)) {
            continue;
        } else if (line[0]) {
            if (is_hls) {
                // Select hls stream with max bandwidth

                /* //z00180556 parse all list
                   if (c->hls_stream_nb > 0) {
                   if (bandwidth > c->hls_stream[0]->bandwidth) {
                // Release last hls stream
                hlsFreeHlsList(c);
                } else {
                // Keep last hls stream
                is_hls     = 0;
                bandwidth  = 0;
                continue;
                }
                }
                */
                hls_stream_info_t *hls = hlsNewHlsStream(c, bandwidth, line, url, c->headers);

                if (!hls) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }

                snprintf(hls->attr.v.audio_group, sizeof(hls->attr.v.audio_group), "%s", variant_info.audio);
                snprintf(hls->attr.v.video_group, sizeof(hls->attr.v.video_group), "%s", variant_info.video);
                snprintf(hls->attr.v.subtitles_group, sizeof(hls->attr.v.subtitles_group), "%s", variant_info.subtitles);

                if (audio_codec || video_codec) {
                    hls->audio_codec = audio_codec;
                    hls->video_codec = video_codec;
                }

                if (!audio_codec && !video_codec) {
                    hls->audio_codec = 1;
                    hls->video_codec = 1;
                }

                if (!c->has_video_stream && hls->video_codec) {
                    c->has_video_stream = 1;
                }
                is_hls = 0;
                bandwidth  = 0;
                audio_codec = 0;
                video_codec = 0;

                if (0 >= strlen(hls->org_url))
                {
                    av_strlcpy(hls->org_url, hls->url, sizeof(hls->org_url));
                    av_log(0, AV_LOG_INFO, "org_url:%s\n", hls->org_url);
                }
            }

            if (is_segment) {
                int seq;
                int add_ret;
                hls_segment_t *seg;
                if (!hls) {
                    hls = hlsNewHlsStream(c, 0, url, NULL, c->headers);
                    if (!hls) {
                        ret = AVERROR(ENOMEM);
                        goto fail;
                    }
                }

                seg = av_mallocz(sizeof(hls_segment_t));
                if (!seg) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }

                seg->total_time = duration;
                seg->start_time = start_time;
                seg->program_time = timeSec;
                start_time += duration;
                seg->key_type   = key_type;

                if (has_iv) {
                    memcpy(seg->iv, iv, sizeof(iv));
                } else {
                    seq = hls->seg_list.hls_seg_start + hls->seg_list.hls_segment_nb;
                    memset(seg->iv, 0, sizeof(seg->iv));
                    AV_WB32(seg->iv + 12, seq);
                }

                hlsMakeAbsoluteUrl(seg->key, sizeof(seg->key), url, key);
                hlsMakeAbsoluteUrl(seg->url, sizeof(seg->url), url, line);
                dynarray_add_noverify(&hls->seg_list.segments, &hls->seg_list.hls_segment_nb, seg, &add_ret);
                is_segment = 0;
                if (add_ret < 0) {
                    av_free(seg);
                    seg = NULL;
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
                seg->size = seg_size;
                if (seg_size >= 0) {
                    seg->url_offset = seg_offset;
                    seg_offset += seg_size;
                    seg_size = -1;
                } else {
                    seg->url_offset = 0;
                    seg_offset = 0;
                }
            }
        }
    }

    if (hls)
        hls->seg_list.hls_last_load_time = av_gettime();

fail:
    if (close_in) url_fclose(in);
    if (hls) {
        /*
        //z00180556 set default playback HLS and segment
        c->cur_seg=c->hls_stream[0]->seg_list.segments[0];
        c->cur_hls=c->hls_stream[0];
        c->cur_stream_seq = 0;
        c->cur_seq_num = 0;
        */
    }
    if (hls && ret >= 0) {
        hls->is_parsed = 1;
    }
    return ret;
}

static int hlsGetDefaultIndex(HLSContext *c, HLS_START_MODE_E mode)
{
    int default_video_bw_stream_nb = -1, i = 0;
    // d00198887 select the lowest or maxvideo bitrate stream to play
    // accord the mode
    for (i = 0; i < c->hls_stream_nb; i++)
    {
        if (0 != c->hls_stream[i]->video_codec && !c->hls_stream[i]->iframe_only)
        {
            if (-1 == default_video_bw_stream_nb)
            {
               default_video_bw_stream_nb = i;
               continue;
            }
            if (HLS_MODE_FAST == mode)
            {
                if ((c->hls_stream[i]->seg_list.hls_segment_nb || !c->hls_stream[i]->is_parsed) &&
                    (c->hls_stream[i]->bandwidth < c->hls_stream[default_video_bw_stream_nb]->bandwidth))
                {
                    default_video_bw_stream_nb = i;
                }
            }
            else
            {
                if ((c->hls_stream[i]->seg_list.hls_segment_nb || !c->hls_stream[i]->is_parsed) &&
                    (c->hls_stream[i]->bandwidth > c->hls_stream[default_video_bw_stream_nb]->bandwidth))
                {
                    default_video_bw_stream_nb = i;
                }
            }

        }
    }
    // d0198887 all is audio stream
    if (-1 == default_video_bw_stream_nb)
    {
        av_log(NULL, AV_LOG_INFO, "all stream is audio stream\n");
        default_video_bw_stream_nb = 0;
    }
    av_log(NULL, AV_LOG_INFO, "default hls stream is %d\n", default_video_bw_stream_nb);
    return default_video_bw_stream_nb;
}

static int hlsSetDownLoadSpeed(HLSContext *c, unsigned int read_size, unsigned int read_time
    , int64_t starttime, int64_t endtime)
{
    int64_t download_interval = 0;
    if (NULL == c)
    {
        return -1;
    }

    DownSpeed *downspeed = &(c->downspeed);
    DownNode *node = (DownNode *)av_malloc(sizeof(DownNode));
    if (NULL == node)
    {
        return -1;
    }

    node->down_size = read_size;
    node->down_time = read_time;
    node->down_starttime = starttime;
    node->down_endtime = endtime;
    node->next = NULL;

    if (NULL == downspeed->head)
    {
        downspeed->head = node;
        downspeed->tail = node;
        downspeed->down_size += node->down_size;
        downspeed->down_time += node->down_time;
        node = NULL;
    }
    else
    {
        downspeed->tail->next = node;
        downspeed->tail = node;
        downspeed->down_size += node->down_size;
        downspeed->down_time += node->down_time;
        node = NULL;
    }

    while (SPEED_SIZE < downspeed->down_size && downspeed->head != downspeed->tail)
    {
        node = downspeed->head;
        downspeed->head = downspeed->head->next;
        downspeed->down_size -= node->down_size;
        downspeed->down_time -= node->down_time;
        av_free(node);
        node = NULL;
    }

    if (c->download_speed_collect_freq_ms > 0)
    {
        if (0 == c->last_get_speed_time)
        {
            c->last_get_speed_time = av_gettime();
        }

        if (c->download_speed_collect_freq_ms * 1000 > (av_gettime() - c->last_get_speed_time))
        {
            return 0;
        }
    }


    if (downspeed->down_time != 0)
    {
        if (NULL == downspeed->tail || NULL == downspeed->head)
            return -1;
        download_interval = downspeed->tail->down_endtime - downspeed->head->down_starttime;
        if (0 == download_interval)
            return -1;
        downspeed->speed = (downspeed->down_size * 1000000 * 8) / download_interval;
        c->real_bw = downspeed->speed;
        c->netdata_read_speed = (downspeed->down_size * 1000000 * 8) / downspeed->down_time;
        c->last_get_speed_time = av_gettime();
    }

    return 0;
}

/*z00180556
 * function:    Get HLS Index by average band width
 * in:     HLS Context
 * out:    HLS index for next playback
 */
static int hlsGetIndex(HLSContext *c)
{
    uint64_t net_bw = c->netdata_read_speed;
    int    cur_bw=c->cur_hls->bandwidth;
    int    target_index = -1;
    int    target_bw = 0;
    int    cur_index = 0;
    int    i = 0;
    unsigned int bw_diff = 0xFFFFFFFF;
    int    adjust_smooth = 1;
    int    select_iframe_var = 0;

    if (c->cur_play_speed != 1.0) {
        select_iframe_var = 1;
    }

    if ((c->appoint_id >= 0) && (c->appoint_id < c->hls_stream_nb) &&
        (c->hls_stream[c->appoint_id]->iframe_only == select_iframe_var) &&
        (c->hls_stream[c->appoint_id]->seg_list.hls_segment_nb > 0 || !c->hls_stream[c->appoint_id]->is_parsed)) {
        return c->appoint_id;
    }

    for (i = 0; i < c->hls_stream_nb; i++) {
        if (c->hls_stream[i]->bandwidth == cur_bw) {
            cur_index=i;
        }
    }

    for (i = 0; i < c->hls_stream_nb; i++) {
        if ((select_iframe_var == c->hls_stream[i]->iframe_only) &&
            (c->hls_stream[i]->bandwidth < net_bw) &&
            (net_bw - c->hls_stream[i]->bandwidth < bw_diff) &&
            (c->hls_stream[i]->seg_list.hls_segment_nb > 0 || !c->hls_stream[i]->is_parsed)) {
            bw_diff = net_bw - c->hls_stream[i]->bandwidth;
            target_index = i;
        }
    }

    if (-1 == target_index) {
        bw_diff = 0xFFFFFFFF;
        for (i = 0; i < c->hls_stream_nb; i++) {
            if ((select_iframe_var == c->hls_stream[i]->iframe_only) &&
                (c->hls_stream[i]->bandwidth < bw_diff) &&
                (c->hls_stream[i]->seg_list.hls_segment_nb > 0 || !c->hls_stream[i]->is_parsed)) {
                bw_diff = c->hls_stream[i]->bandwidth;
                target_index = i;
            }
        }
    }

    if (target_index < 0) {
        target_index = 0;
        av_log(0, AV_LOG_ERROR, "[%s,%d] unknow error, no stream selected, "
            "default to 0!select_iframe_var=%d\n", __FUNCTION__, __LINE__, select_iframe_var);
    }

    target_bw = c->hls_stream[target_index]->bandwidth;
    bw_diff = 0xFFFFFFFF;

#if defined (ANDROID_VERSION)
    /* We can set hls bandwidth adjust mode by setprop media.hiplayer.hls.adjustbw *
     * setprop media.hiplayer.hls.adjustbw quick      --- means adjust by quick *
     * setprop media.hiplayer.hls.adjustbw smooth --- means adjust by smooth*/

    char value[PROPERTY_VALUE_MAX] = {0};
    if (property_get("media.hiplayer.hls.adjustbw", value, "smooth") > 0) {
        if (!strncmp(value, "quick", 5)) {
            adjust_smooth = 0;
        }
    }
#endif

    if (adjust_smooth && cur_index != target_index) {
        if (target_bw < cur_bw) {
            for (i = 0; i < c->hls_stream_nb; i++) {
                if ((select_iframe_var == c->hls_stream[i]->iframe_only) &&
                    (c->hls_stream[i]->bandwidth < cur_bw) &&
                    (cur_bw - c->hls_stream[i]->bandwidth < bw_diff) &&
                    (c->hls_stream[i]->seg_list.hls_segment_nb > 0)) {
                    bw_diff = cur_bw - c->hls_stream[i]->bandwidth;
                    target_index = i;
                }
            }
        } else if (target_bw > cur_bw) {
            for (i = 0; i < c->hls_stream_nb; i++) {
                if ((select_iframe_var == c->hls_stream[i]->iframe_only) &&
                    (c->hls_stream[i]->bandwidth > cur_bw) &&
                    (c->hls_stream[i]->bandwidth - cur_bw < bw_diff) &&
                    (c->hls_stream[i]->seg_list.hls_segment_nb > 0 || !c->hls_stream[i]->is_parsed)) {
                    bw_diff = c->hls_stream[i]->bandwidth - cur_bw;
                    target_index = i;
                }
            }
        }
    }

    av_log(NULL, AV_LOG_ERROR, "[%s:%d] net_bw =%llu  current: %d %d  target: %d %d, adjust smooth: %d \n",
        __FILE_NAME__, __LINE__, net_bw, cur_index, cur_bw, target_index,c->hls_stream[target_index]->bandwidth, adjust_smooth);
    return target_index;
}

static int hlsUpdateUrlInfo(HLSContext *c, URLContext *uc, hls_segment_t *seg)
{
    memset(&c->stHlsUrlInfo, 0, sizeof(HLS_URL_INFO_S));
    if (uc) {
        c->stHlsUrlInfo.port = uc->port;
        av_strlcpy(c->stHlsUrlInfo.ipaddr, uc->ipaddr, sizeof(c->stHlsUrlInfo.ipaddr));
    }
    if (uc && uc->moved_url) {
        av_strlcpy(c->stHlsUrlInfo.url, uc->moved_url, sizeof(c->stHlsUrlInfo.url));
        c->stHlsUrlInfo.enable = 1;
    } else if (seg) {
        av_strlcpy(c->stHlsUrlInfo.url, seg->url, sizeof(c->stHlsUrlInfo.url));
        c->stHlsUrlInfo.enable = 1;
    }
    return 0;
}

static void hlsAppendSegOpts(hls_segment_t *seg, AVDictionary **opts)
{
    if (seg && opts && seg->size >= 0) {
        char off[64], end_off[64];
        /* try to restrict the HTTP request to the part we want
         * (if this is in fact a HTTP request) */
        snprintf(off, sizeof(off), "%lld", seg->url_offset);
        snprintf(end_off, sizeof(end_off), "%lld", seg->url_offset + seg->size - 1);
        av_dict_set(opts, "offset", off, 0);
        av_dict_set(opts, "end_offset", end_off, 0);
    }
}

static int hlsOpenSegment(hls_stream_info_t *hls)
{
    int pos;
    int cur = hls->seg_list.hls_seg_cur;
    int start = hls->seg_list.hls_seg_start;
    HLSContext *c = hls->seg_demux.parent->priv_data;
    int ret = 0;
    AVDictionary *opts = NULL;
    hls_segment_t *seg = NULL;
    int save_hls =0;

    if (hls->sof) {
        av_log(c->parent, AV_LOG_WARNING, "[%s %d] backward download to sof!hls[%d](iframe_only:%d)\n",
            __FUNCTION__, __LINE__, hls->seg_list.hls_index, hls->iframe_only);
        return AVERROR_EOF;
    }

    if (cur == 0) {
        c->seg_position = 0;
        c->ts_first_btime = 0;
        c->seg_count = 1000;
    }
    pos = cur - start;
    if (!hls->is_redition_stream) {
        seg=c->cur_seg;
    } else {
        seg = hls->seg_list.segments[pos];
    }

    if (c->user_agent && strlen(c->user_agent) > 0)
        av_dict_set(&opts, "user-agent", c->user_agent, 0);

    if (c->referer && strlen(c->referer) > 0)
        av_dict_set(&opts, "referer", c->referer, 0);

    if (c->cookies && strlen(c->cookies) > 0)
        av_dict_set(&opts, "cookies", c->cookies, 0);

    if (c->headers && strlen(c->headers) > 0)
        av_dict_set(&opts, "headers", c->headers, 0);

    if (!hls->is_redition_stream) {
        av_log(NULL, AV_LOG_ERROR, "[%s %d] c->uuid:%xh, seg_position=%d cur=%d",__FUNCTION__, __LINE__, c->uuid,c->seg_position,cur);
        if(c->uuid && c->seg_position != cur){
            if (NULL != c->uuid) {
                c->ts_send_time = av_gettime();
            }
            c->ts_first_btime = 0;
            c->seg_count++;
            if (c->seg_count > 9000) {
                c->seg_count = 1001;
            }
        }
        if (c->uuid && strlen(c->uuid) > 0){
            struct timeval tv;

            if (0 == gettimeofday(&tv, NULL)) {
                snprintf(c->ts_traceid, sizeof(c->ts_traceid),"%s%013u%04d",c->uuid, tv.tv_sec*1000 + tv.tv_usec/1000, c->seg_count);
            }

            av_dict_set(&opts, "traceId", c->ts_traceid, 0);
            av_log(NULL, AV_LOG_ERROR, "[%s %d] time=[%013u] c->uuid=[%s] ts_traceid:%s",
                __FUNCTION__, __LINE__,tv.tv_sec*1000 + tv.tv_usec/1000,c->uuid, c->ts_traceid);
        }
    }

    if (seg->key_type == KEY_NONE) {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] redition?(%d),open segment noKey url=%s pos=%d hls->bandwidth=%d \n",
            __FILE_NAME__, __LINE__, hls->is_redition_stream, seg->url, pos, hls->is_redition_stream?0:c->cur_hls->bandwidth);
        hlsAppendSegOpts(seg, &opts);
        ret = hls_open_h(&hls->seg_stream.input, seg->url, URL_RDONLY, &(c->interrupt_callback), &opts);
        if (0 == ret) {
            hlsUpdateUrlInfo(c, hls->seg_stream.input, seg);
        } else {
            hlsUpdateUrlInfo(c, NULL, seg);
        }
        hls->seg_stream.offset = 0;
        av_dict_free(&opts);
    } else if (seg->key_type == KEY_AES_128) {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] redition?(%d),open segment with Keyurl=%s \n url=%s\n",
            __FILE_NAME__, __LINE__, hls->is_redition_stream, seg->key, seg->url);

        int ret, use_customer_client = 1;

        /* Read key context */
        if (av_strcmp(seg->key, hls->seg_key.key_url)) {
            #if defined (ANDROID_VERSION)
            if (use_customer_client) {
                // call customer client get key info
                unsigned int client_handle = 0;

                av_log(NULL, AV_LOG_ERROR, "[CLIENT] %s:%d, call CLIENT_Init \n", __FILE_NAME__, __LINE__);

                ret = CLIENT_Init(&client_handle);

                if (CLIENT_SUCCESS != ret) {
                    av_log(NULL, AV_LOG_ERROR, "[CLIENT] %s:%d, client init fail \n", __FILE_NAME__, __LINE__);
                    use_customer_client = 0;
                } else {
                    av_log(NULL, AV_LOG_ERROR, "[CLIENT] %s:%d, call CLIENT_GetKey \n", __FILE_NAME__, __LINE__);
                    ret = CLIENT_GetKey(client_handle, seg->key, hls->seg_key.key, sizeof(hls->seg_key.key), NULL);

                    if (CLIENT_SUCCESS != ret) {
                        av_log(NULL, AV_LOG_ERROR, "[CLIENT] %s:%d, call get key fail \n", __FILE_NAME__, __LINE__);
                        use_customer_client = 0;
                    }
                }

                av_log(NULL, AV_LOG_ERROR, "[CLIENT] %s:%d, call CLIENT_Deinit \n", __FILE_NAME__, __LINE__);
                CLIENT_Deinit(client_handle);
                client_handle = 0;
            }
            #else
            use_customer_client = 0;
            #endif

            if (!use_customer_client) {
                URLContext *uc;
                int64_t offset;

                /* Open key url to get key context */
                ret = hls_open_h(&uc, seg->key, URL_RDONLY, &(c->interrupt_callback), &opts);
                offset = 0;
                if (0 == ret) {
                    hlsUpdateUrlInfo(c, uc, seg);
                } else {
                    hlsUpdateUrlInfo(c, NULL, seg);
                }
                if (ret == 0) {
                    ret = hls_read_complete(uc, offset, hls->seg_key.key, sizeof(hls->seg_key.key));
                    if (ret != sizeof(hls->seg_key.key)) {
                        av_log(NULL, AV_LOG_ERROR, "[%s:%d] Unable to read key file %s\n", __FILE_NAME__, __LINE__, seg->key);
                    }

                    if(ret > 0) {
                        offset += ret;
                    }
                    hls_close(uc);
                } else {
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] Unable to open key file %s\n", __FILE_NAME__, __LINE__, seg->key);
                }
            }

            av_strlcpy(hls->seg_key.key_url, seg->key, sizeof(hls->seg_key.key_url));
        }

        if (hls->seg_key.IO_decrypt) {
            hls_decrypt_close(hls->seg_key.IO_decrypt);
            av_freep(&hls->seg_key.IO_decrypt);
            hls->seg_key.IO_decrypt = NULL;
        }

        hls->seg_key.IO_decrypt = av_mallocz(sizeof(Hls_CryptoContext));
        if (!hls->seg_key.IO_decrypt) {
            av_dict_free(&opts);
            return AVERROR(ENOMEM);
        }

        hlsAppendSegOpts(seg, &opts);
        //hls->seg_key.IO_decrypt->userdata = userdata;
        hls->seg_key.IO_decrypt->interrupt_callback.callback = c->interrupt_callback.callback;
        hls->seg_key.IO_decrypt->interrupt_callback.opaque = c->interrupt_callback.opaque;
        hls->seg_key.IO_decrypt->file_name = c->file_name;
        hls->seg_key.IO_decrypt->cur_segment = cur;
        ret = hls_decrypt_open(hls->seg_key.IO_decrypt,
                               seg->url,
                               seg->size,
                               &opts,
                               hls->seg_key.key,
                               sizeof(hls->seg_key.key),
                               seg->iv,
                               sizeof(seg->iv));
        av_dict_free(&opts);
    } else {
        /* If reached here, invalid type */
        return AVERROR(EINVAL);
    }

    if (0 == ret && !hls->is_redition_stream)  {
        if (c->ready_to_record_ts == 1) {
            save_hls =1;
        }
        /* close last segment's logfile handle */
        if (c->tsfp) {
            fclose(c->tsfp);
            c->tsfp = NULL;
        }
        if (save_hls) {
            char name[INITIAL_URL_SIZE];

            memset(name, 0, sizeof(name));
            snprintf(name, sizeof(name) - 1, "%s/%d_%d.ts", c->save_hls_path, start, pos);
            av_log(NULL,AV_LOG_ERROR,"#[%s:%d] save ts:%s#\n",__FUNCTION__,__LINE__,name);

            c->tsfp = fopen(name, "w+b");
            if (NULL == c->tsfp) {
                av_log(NULL,AV_LOG_ERROR,"#[%s:%d] fopen %s failed#\n",__FUNCTION__,__LINE__,name);
            }
        }
    }

    return ret;
}

#undef time

static int hlsFreshUrl(hls_stream_info_t *v)
{
    char    *pTmp = NULL;
    char    *pDate = NULL;
    char    *pTime = NULL;
    char    *pEnd  = NULL;
    unsigned int duration = 0, i = 0;
    unsigned int date_old = 0, time_old = 0, time_new = 0, date_new = 0;
    int tm_sec = 0, tm_min = 0, tm_hour = 0, tm_mday = 0, tm_mon = 0, tm_year = 0;

    time_t timeSec, timeSystem;
    struct tm ptm[1];
    struct tm *tmp = NULL;
    char startTime[128];

    //char *url_temp ="http://10.67.225.126/0_0_3736680_0.m3u8?id=3736680&scId=&isChannel=true&time=300&serviceRegionIds
    //=&codec=ALL&quality=100&vSiteCode=&offset=0&livemode=2&starttime=20130906T134439Z";
    av_log(NULL, AV_LOG_ERROR, "%s,%d, ### last URL:%s \n",__FILE__,__LINE__, v->url);

    if (pTmp = strstr(v->url, "starttime=")) {
        pDate = pTmp + strlen("starttime=");
        date_old = atoi(pDate);
        tm_year = date_old / 10000 - 1900;
        tm_mon  = (date_old % 10000) / 100 - 1;
        tm_mday = date_old % 100;

        pTmp = strstr(pDate, "T");

        if (!pTmp) {
            av_log(NULL, AV_LOG_ERROR, "%s,%d,\n",__FILE__,__LINE__);
            return 0;
        }

        pTime    = pTmp + 1;
        time_old = atoi(pTime);
        tm_hour  = time_old / 10000;
        tm_min   = (time_old % 10000) / 100;
        tm_sec   = time_old % 100;

        for (i = 0; i < v->seg_list.hls_segment_nb; i++) {
            duration += v->seg_list.segments[i]->total_time;
        }

        memset(ptm, 0, sizeof(ptm));
        ptm[0].tm_sec  = tm_sec;
        ptm[0].tm_min  = tm_min;
        ptm[0].tm_hour = tm_hour;
        ptm[0].tm_mday = tm_mday;
        ptm[0].tm_mon  = tm_mon;
        ptm[0].tm_year = tm_year;

        #if 0
        timeSec = mktime(ptm);
        timeSec += duration;
        tmp = localtime(&timeSec);
        #else
        timeSec = mktime(ptm);
        timeSec += duration / 1000;
        timeSystem = time(0);

        av_log(NULL, AV_LOG_ERROR, "INFO: timeSec = %ld, timeSystem = %ld, duration = %u \n", timeSec, timeSystem, duration);

        if (timeSystem <= timeSec)
            timeSec = timeSystem - 1;
        timeSec -= 20;
        av_log(NULL, AV_LOG_ERROR, "INFO1: timeSec = %ld, timeSystem = %ld, duration = %u \n", timeSec, timeSystem, duration);
        tmp = localtime(&timeSec);
        #endif

        //time_new = tmp->tm_hour * 10000 + tmp->tm_min * 100 + tmp->tm_sec;
        //date_new = (1900 + tmp->tm_year) * 10000 + (1 + tmp->tm_mon) * 100 + tmp->tm_mday;

        memset(startTime, 0, 128);
        strftime(startTime, 100, "%Y%m%dT%H%M%S.00Z", tmp);
        //snprintf(startTime, 100, "%04d%02d%02dT%02d%02d%02d.00Z",
        //        (1900 + tmp->tm_year), (1 + tmp->tm_mon), tmp->tm_mday,
        //        tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
        av_log(NULL, AV_LOG_ERROR, "#:%d-%d-%d %d:%d:%d\n",(1900 + tmp->tm_year), (1 + tmp->tm_mon), tmp->tm_mday,
                tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
        av_log(NULL, AV_LOG_ERROR, "caculate time = %s \n", startTime);

        pEnd = strstr(pDate, ".00Z");

        if (pEnd > pDate && pEnd + strlen(".00Z") < v->url + strlen(v->url))
        {
            av_log(NULL, AV_LOG_ERROR, "%s,%d, ### EndStr:%s \n",__FILE__,__LINE__, pEnd);
            snprintf(pDate, INITIAL_URL_SIZE - (pDate - v->url), "%s%s", startTime, pEnd + strlen(".00Z"));
        }
        else
        {
            //TimeSample:20140423T110600.00Z
            //memset(pDate, 0, INITIAL_URL_SIZE - (pDate - v->url));
            //snprintf(pDate, INITIAL_URL_SIZE - (pDate - v->url), "%08dT%06d.00Z", date_new, time_new);
            snprintf(pDate, INITIAL_URL_SIZE - (pDate - v->url), "%s", startTime);
        }

        av_log(NULL, AV_LOG_ERROR, "%s,%d, ### New URL:%s \n",__FILE__,__LINE__, v->url);
    }
    else
    {
        return -1;
    }

    return 0;
}

/* WARN: the iframe stream's segment number may be not the same as main stream,
   refer to http://10.157.186.83/4KTest/17M/04_m3u8/iframe/entire.m3u8 */
static int hlsGetCurSeqNoByTime(HLSContext *c, hls_stream_info_t *hls, int64_t start_time, int duration)
{
    int j, seq_no = -1;

    if (hls->seg_list.hls_segment_nb <= 0)
        return 0;

    /* if current segment not complete, skip it*/
    if (c->cur_play_speed >= 0 && c->hls_stream[0]->seg_stream.input) {
        start_time += duration;
    }

    for (j = 0; j < hls->seg_list.hls_segment_nb; j++) {
        if (c->cur_play_speed >= 0) {
            if (hls->seg_list.segments[j]->start_time >= start_time) {
                av_log(0, AV_LOG_WARNING, "[%s,%d] hls[%d] iframe_only=%d, seq_no=%d got for start_time=%lld\n",
                        __FUNCTION__, __LINE__, hls->seg_list.hls_index, hls->iframe_only, j, start_time);
                seq_no = j;
                break;
            }
        } else {
            if (hls->seg_list.segments[j]->start_time <= start_time) {
                seq_no = j;
            } else {
                break;
            }
        }
    }

    if (seq_no < 0) {
        if (c->cur_play_speed >= 0) {
            seq_no = hls->seg_list.hls_segment_nb - 1;
        } else {
            seq_no = 0;
        }
    }

    av_log(0, AV_LOG_WARNING, "[%s,%d] hls[%d] iframe_only=%d, seq_no=%d got for start_time=%lld, cur_play_speed=%f\n",
            __FUNCTION__, __LINE__, hls->seg_list.hls_index, hls->iframe_only, seq_no, start_time, c->cur_play_speed);

    return seq_no;
}

static int hlsCheckSwitchVariant(HLSContext *c)
{
    int ret = 0, pos = 0;
    int next_stream_num = 0, old_stream_num = 0;
    int select_iframe_var = 0;
    hls_stream_info_t *cur_hls = NULL;
    hls_stream_info_t *hls = c->hls_stream[0];
    hls_stream_info_t *hls_next = NULL;
    hls_segment_t   *seg = NULL;

    if (c->cur_play_speed != 1.0) {
        select_iframe_var = 1;
    }
    old_stream_num = c->cur_stream_seq;
    cur_hls = c->hls_stream[old_stream_num];
    next_stream_num = hlsGetIndex(c);
    hls_next = c->hls_stream[next_stream_num];
    if (hls_next->seg_list.hls_segment_nb <= 0 && !hls_next->is_parsed) {
        ret = hlsParseM3U8(c, hls_next->url, hls_next, NULL);
        if (0 > ret){
            av_log(c->parent, AV_LOG_ERROR, "[%s,%d] parse hls[%d] error, do not switch variant\n",
                __FUNCTION__, __LINE__, next_stream_num);
            hls_next = c->hls_stream[old_stream_num];
        }
    }

    pos = hls_next->seg_list.hls_seg_start + (hls->seg_list.hls_seg_cur - hls->seg_list.hls_seg_start);
    av_log(c->parent, AV_LOG_ERROR, "[%s:%d] hls_next[%d].seg_start=%d, .seg_nb=%d, .seg_cur=%d, "
        "hls[%d].seg_start=%d, .seg_nb=%d, pos=%d\n", __FUNCTION__, __LINE__, hls_next->seg_list.hls_index,
        hls_next->seg_list.hls_seg_start, hls_next->seg_list.hls_segment_nb, hls->seg_list.hls_seg_cur,
        hls->seg_list.hls_index, hls->seg_list.hls_seg_start, hls->seg_list.hls_segment_nb, pos);

    if (hls_next->seg_list.hls_segment_nb > 0) {
        if (hls->seg_list.hls_finished) {
            if (pos < hls_next->seg_list.hls_segment_nb + hls_next->seg_list.hls_seg_start ||
                (select_iframe_var != c->hls_stream[c->cur_stream_seq]->iframe_only &&
                 select_iframe_var == hls_next->iframe_only)) {
                if (select_iframe_var != c->hls_stream[c->cur_stream_seq]->iframe_only &&
                    select_iframe_var == hls_next->iframe_only) {
                    if (hls->seg_list.hls_seg_cur - hls->seg_list.hls_seg_start < cur_hls->seg_list.hls_segment_nb) {
                        seg = cur_hls->seg_list.segments[hls->seg_list.hls_seg_cur - hls->seg_list.hls_seg_start];
                    } else {
                        seg = cur_hls->seg_list.segments[cur_hls->seg_list.hls_segment_nb - 1];
                    }
                    pos = hlsGetCurSeqNoByTime(c, hls_next, seg->start_time, seg->total_time) + hls_next->seg_list.hls_seg_start;
                }
                if (pos < hls_next->seg_list.hls_segment_nb + hls_next->seg_list.hls_seg_start) {
                    c->cur_seg = hls_next->seg_list.segments[pos - hls_next->seg_list.hls_seg_start];
                } else {
                    c->cur_seg = hls_next->seg_list.segments[hls_next->seg_list.hls_segment_nb - 1];
                }
                c->cur_hls = hls_next;
                c->cur_stream_seq = next_stream_num;
                c->cur_seq_num = pos-hls_next->seg_list.hls_seg_start;
            } else if (c->cur_stream_seq != next_stream_num) {
                hls_next = c->hls_stream[c->cur_stream_seq];
                c->cur_seg = hls_next->seg_list.segments[pos-hls_next->seg_list.hls_seg_start];
                c->cur_hls = hls_next;
                c->cur_seq_num = pos-hls_next->seg_list.hls_seg_start;
            }
        } else {
            c->cur_hls = hls_next;
            c->cur_stream_seq = next_stream_num;
            if (pos < hls_next->seg_list.hls_segment_nb + hls_next->seg_list.hls_seg_start) {
                c->cur_hls->seg_list.hls_seg_cur = pos;
                av_log(c->parent, AV_LOG_ERROR, "[%s:%d] set cur_hls.seg_cur = %d \n", __FUNCTION__, __LINE__, pos);
            }
        }
    }

    if (old_stream_num != c->cur_stream_seq) {
        av_log(c->parent, AV_LOG_ERROR, "[%s:%d] variant changed, Adjust bit rate(%d->%d) \n",
            __FUNCTION__, __LINE__, old_stream_num, c->cur_stream_seq);
        return 1;
    } else {
        return 0;
    }
}

static int hlsStepSegCur(HLSContext *c, hls_stream_info_t *v)
{
    if (c->cur_play_speed >= 0) {
        v->seg_list.hls_seg_cur += 1;
    } else {
        if (v->seg_list.hls_seg_cur > v->seg_list.hls_seg_start) {
            v->seg_list.hls_seg_cur --;
        } else {
            v->sof = 1;
            return AVERROR_EOF;
        }
    }

    return 0;
}

static int hlsReadDataCb(void *opaque, uint8_t *buf, int buf_size)
{
    hls_stream_info_t *v = opaque;
    HLSContext *c = v->seg_demux.parent->priv_data;
    int ret, i;
    int need_reload = 0;
    int64_t time_diff;
    int64_t time_wait;
    int has_reload = 0;
    int open_fail = 0;
    int end_pos;
    AVFormatContext *s = v->seg_demux.parent;

restart:
    if (!v->seg_stream.input) {
reload:
        if (ff_check_interrupt(&c->interrupt_callback))
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] force quit \n", __FILE__, __LINE__);
            return AVERROR_EOF;
        }

        time_diff = av_gettime() - v->seg_list.hls_last_load_time;
        time_wait = v->seg_list.hls_target_duration * AV_TIME_BASE;

        if (time_wait > HLS_MAX_WAITE_TIME)
            time_wait = HLS_MAX_WAITE_TIME;

        /* If this is a live stream and target_duration has elapsed since
         * the last playlist reload, reload the variant playlists now. */
        if (!v->seg_list.hls_finished && ((llabs(time_diff) >= time_wait) || need_reload)) {
reparse:
            //ret = hlsFreshUrl(v); //only for yueme version
            ret = hlsParseM3U8(c, v->url, v, NULL);
            if (ret < 0) {
                if (ff_check_interrupt(&c->interrupt_callback))
                    return ret;

                /* fix seek operation blocked */
                if (s->is_time_shift)
                {
                    return AVERROR(EAGAIN);
                }

                usleep(1000*1000);
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] redo hlsParseM3U8\n",
                        __FILE_NAME__, __LINE__);
                goto reparse;
            }

            need_reload = 0;
            has_reload = 1;
        }

        if (v->seg_list.hls_seg_cur < v->seg_list.hls_seg_start) {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] skipping %d segments ahead, expired from playlists",
                    __FILE_NAME__, __LINE__,
                    v->seg_list.hls_seg_start - v->seg_list.hls_seg_cur);
            v->seg_list.hls_seg_cur = v->seg_list.hls_seg_start;
        }

        end_pos = v->seg_list.hls_seg_start + v->seg_list.hls_segment_nb;
        if (c->cur_hls && c->cur_hls->iframe_only) {
            end_pos = c->cur_hls->seg_list.hls_seg_start + c->cur_hls->seg_list.hls_segment_nb;
        }
        if (v->seg_list.hls_seg_cur >= end_pos) {
            if (v->seg_list.hls_finished)
                return AVERROR_EOF;

            #if defined (ANDROID_VERSION)
            /* add for fresh url */
            /* setprop media.hiplayer.hls.freshurl true or false
                   the project may need set true:
                   1. iptv.china.mobile
                   2. iptv.china.telecom (yue me)
                   */
            char value[PROPERTY_VALUE_MAX] = {0};
            if (property_get("media.hiplayer.hls.freshurl", value, NULL) && !strncmp(value, "true", 4)) {
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] need fresh url\n", __FILE_NAME__, __LINE__);

                if (0 == hlsFreshUrl(v)) {
                    need_reload = 1;
                    goto reload;
                }
            }
            /* end: add for fresh url*/
            #endif

            time_diff = av_gettime() - v->seg_list.hls_last_load_time;
            time_wait = v->seg_list.hls_target_duration * AV_TIME_BASE;

            if (time_wait > HLS_MAX_WAITE_TIME)
                time_wait = HLS_MAX_WAITE_TIME;

            while (llabs(time_diff) < time_wait) {
                if (ff_check_interrupt(&c->interrupt_callback))
                    return AVERROR_EOF;

                usleep(100*1000);

                time_diff = av_gettime() - v->seg_list.hls_last_load_time;
                time_wait = v->seg_list.hls_target_duration * AV_TIME_BASE;

                if (time_wait > HLS_MAX_WAITE_TIME)
                    time_wait = HLS_MAX_WAITE_TIME;
            }

            /* Enough time has elapsed since the last reload */
            if (ff_check_interrupt(&c->interrupt_callback))
                return AVERROR_EOF;
            goto reload;
        }

        if (!v->seg_list.hls_finished) {
            if (has_reload && (c->cur_stream_seq != v->seg_list.hls_index)) {
reparse2:
                //ret = hlsFreshUrl(c->cur_hls); //only for yueme version
                ret = hlsParseM3U8(c, c->cur_hls->url, c->cur_hls, NULL);
                if (ret < 0) {
                    if (ff_check_interrupt(&c->interrupt_callback))
                        return ret;

                    /* fix seek operation blocked */
                    if (s->is_time_shift)
                    {
                        return AVERROR(EAGAIN);
                    }

                    usleep(1000*1000);
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] redo hlsParseM3U8\n", __FILE_NAME__, __LINE__);
                    goto reparse2;
                }
            }

            has_reload = 0;
#if 0
            if (c->cur_hls->seg_list.hls_seg_start+ c->cur_hls->seg_list.hls_segment_nb - 1 < v->seg_list.hls_seg_cur) {
                goto reparse2;
            }
#else
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] Sequence ReCount, v.seg_start:%d, v.seg_cur:%d, cur_hls.seg_start:%d, cur_hls.seg_cur:%d, cur_hls.segment_nb:%d",
                __FUNCTION__, __LINE__, v->seg_list.hls_seg_start, v->seg_list.hls_seg_cur,
                c->cur_hls->seg_list.hls_seg_start, c->cur_hls->seg_list.hls_seg_cur, c->cur_hls->seg_list.hls_segment_nb);

            if (c->use_offset_seq) {
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] v->first_seg_number:%d, cur_hls->first_seg_number:%d",
                    __FUNCTION__, __LINE__, v->first_seg_number, c->cur_hls->first_seg_number);

                if (v->seg_list.hls_seg_cur - v->first_seg_number + c->cur_hls->first_seg_number
                    <= c->cur_hls->seg_list.hls_seg_start + c->cur_hls->seg_list.hls_segment_nb - 1) {
                    c->cur_hls->seg_list.hls_seg_cur
                        = v->seg_list.hls_seg_cur - v->first_seg_number + c->cur_hls->first_seg_number;
                } else {
                    c->cur_hls->seg_list.hls_seg_cur
                        = v->seg_list.hls_seg_cur - v->seg_list.hls_seg_start + c->cur_hls->seg_list.hls_seg_start;
                }
            } else {
                if (c->cur_hls->seg_list.hls_seg_start + c->cur_hls->seg_list.hls_segment_nb - 1 < v->seg_list.hls_seg_cur) {
                    goto reparse2;
                }
            }
            #if 0
            else {
                if ((c->cur_hls->seg_list.hls_seg_start + c->cur_hls->seg_list.hls_segment_nb - 1) < v->seg_list.hls_seg_cur) {
                    v->seg_list.hls_seg_cur = v->seg_list.hls_seg_cur - v->seg_list.hls_seg_start
                        + c->cur_hls->seg_list.hls_seg_start;
                } else if (c->cur_hls->seg_list.hls_seg_start > v->seg_list.hls_seg_start + v->seg_list.hls_segment_nb - 1) {
                    v->seg_list.hls_seg_cur = v->seg_list.hls_seg_cur - v->seg_list.hls_seg_start
                        + c->cur_hls->seg_list.hls_seg_start;
                }
            }
            #endif
#endif
            //c->cur_seg = c->cur_hls->seg_list.segments[v->seg_list.hls_seg_cur - v->seg_list.hls_seg_start];
            //c->cur_seq_num = v->seg_list.hls_seg_cur - v->seg_list.hls_seg_start;
            #if 0  /* yll:cur_hls.hls_seg_cur is wrong, because the new m3u8 not fresh when caculate the hls_seg_cur value at the function end */
            if (c->cur_hls->seg_list.hls_seg_cur >= c->cur_hls->seg_list.hls_seg_start) {
                c->cur_seg = c->cur_hls->seg_list.segments[c->cur_hls->seg_list.hls_seg_cur - c->cur_hls->seg_list.hls_seg_start];
                c->cur_seq_num = c->cur_hls->seg_list.hls_seg_cur - c->cur_hls->seg_list.hls_seg_start;
                av_log(NULL, AV_LOG_ERROR, "[%s:%d], cur_seq_num = %d ", __FUNCTION__, __LINE__, c->cur_seq_num);
            } else {
                c->cur_seg = c->cur_hls->seg_list.segments[0];
                c->cur_seq_num = 0;
                av_log(NULL, AV_LOG_ERROR, "[%s:%d], cur_seq_num = %d ", __FUNCTION__, __LINE__, c->cur_seq_num);
            }
            #else
            if (v->seg_list.hls_seg_cur >= c->cur_hls->seg_list.hls_seg_start) {
                c->cur_seg = c->cur_hls->seg_list.segments[v->seg_list.hls_seg_cur - c->cur_hls->seg_list.hls_seg_start];
                c->cur_seq_num = v->seg_list.hls_seg_cur - c->cur_hls->seg_list.hls_seg_start;
                av_log(NULL, AV_LOG_ERROR, "[%s:%d], cur_seq_num = %d ", __FUNCTION__, __LINE__, c->cur_seq_num);
            } else {
                c->cur_seg = c->cur_hls->seg_list.segments[0];
                c->cur_seq_num = 0;
                av_log(NULL, AV_LOG_ERROR, "[%s:%d], cur_seq_num = %d ", __FUNCTION__, __LINE__, c->cur_seq_num);
            }
            #endif
        }

        //c->read_time = 500*1000;
        int64_t open_start = av_gettime();
reopen:
        ret = hlsOpenSegment(v);
        int64_t open_end = av_gettime();
        if (ret < 0) {
            open_fail = 1;
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret = %d \n", __FILE_NAME__, __LINE__, ret);
            if (ff_check_interrupt(&c->interrupt_callback) || ret == AVERROR(ENOMEM) || ret == AVERROR_EOF) {
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] return EOF, hlsOpenSegment = %d \n",__FILE_NAME__, __LINE__, ret);
                return AVERROR_EOF;
            }
            if (v->seg_list.hls_finished) { // Reload item for metadata stream
                if (ret == AVERROR(EAGAIN)) {
                    usleep(100*1000);
                    goto reopen;
                }

                if (c->hls_stream_nb > 1) {
                    c->cur_hls->has_read = 1;
                    unsigned int min_bw_diff = 0xffffffff;
                    int temp_stream_num = 0;
                    int select_iframe_var = 0;
                    hls_stream_info_t *temp_stream = NULL;
                    if (c->cur_play_speed != 1.0) {
                        select_iframe_var = 1;
                    }
                    for (i = 0; i < c->hls_stream_nb; i++) {
                        if (select_iframe_var == c->hls_stream[i]->iframe_only &&
                            (FFABS((c->hls_stream[i]->bandwidth - c->cur_hls->bandwidth)) < min_bw_diff) &&
                             c->hls_stream[i]->has_read == 0 && (c->hls_stream[i]->seg_list.hls_segment_nb > 0)) {
                            temp_stream = c->hls_stream[i];
                            temp_stream_num = i;
                            min_bw_diff = FFABS(c->hls_stream[i]->bandwidth - c->cur_hls->bandwidth);
                        }
                    }
                    if (NULL == temp_stream) {
                        goto load_next;
                    } else {
                        c->cur_hls = temp_stream;
                        c->cur_seg = c->cur_hls->seg_list.segments[c->cur_seq_num];
                        c->cur_stream_seq = temp_stream_num;
                    }
                } else {
                    goto load_next;
                }

                //usleep(500*1000);
                goto reload;
            } else { // Reload playlist for live stream
                v->seg_list.hls_seg_cur++;
                need_reload = 1;
                goto reload;
            }
        } else {
            AVFormatContext *s = c->parent;
            if (v->seg_stream.input) {
                v->seg_stream.input->parent = s->pb;
                if (open_fail && !strncmp(v->seg_stream.input->filename, "http://", strlen("http://"))) {
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] network normal\n",__FILE_NAME__,__LINE__);
                    url_errorcode_cb(c->interrupt_callback.opaque, NETWORK_NORMAL, "http");
                    open_fail = 0;
                }
            }
            if (v->seg_key.IO_decrypt && v->seg_key.IO_decrypt->hd) {
                v->seg_key.IO_decrypt->hd->parent = s->pb;
                if (open_fail && !strncmp(v->seg_key.IO_decrypt->hd->filename, "http://", strlen("http://"))) {
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] network normal\n",__FILE_NAME__,__LINE__);
                    url_errorcode_cb(c->interrupt_callback.opaque, NETWORK_NORMAL, "http");
                    open_fail = 0;
                }
            }
        }
    }

    int64_t  start = av_gettime();
    if (v->seg_key.IO_decrypt) {  // Encrypted stream
        if (!v->seg_stream.input)
            v->seg_stream.input = v->seg_key.IO_decrypt->hd;
        ret = hls_decrypt_read(v->seg_key.IO_decrypt, buf, buf_size);
    } else {  // Normal stream
        int64_t left_size = 1;
        if (c->cur_seg->size > 0) {
            left_size = c->cur_seg->size - v->seg_stream.offset;
        }
        if (left_size > 0) {
            ret = hls_read(v->seg_stream.input, v->seg_stream.offset, buf, buf_size);
            if(ret > 0) {
                v->seg_stream.offset += ret;
                URLContext *uc = (URLContext *) v->seg_stream.input;
                if(NULL != c->uuid) {
                    if(0 == c->ts_first_btime && v->seg_list.hls_seg_cur != c->seg_position)
                    {
                        c->ts_first_btime = av_gettime();
                    }
                    c->seg_position = v->seg_list.hls_seg_cur;
                    c->ts_length = ffurl_size(uc);
                    c->ts_last_btime = av_gettime();
                    c->http_res = uc->http_res;
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d]  c->http_res=%xh ,uc->http_res=%xh\n",__FUNCTION__,__LINE__, c->http_res, uc->http_res);
                }
            }
        } else {
            ret = AVERROR_EOF;
        }
    }
    int64_t  end = av_gettime();
    if (ret > 0) {
        unsigned int read_size = ret;
        unsigned int read_time = end - start;
        hlsSetDownLoadSpeed(c, read_size, read_time, start, end);
        if (c->tsfp)
        {
            fwrite(buf, 1, ret, c->tsfp);
            fflush(c->mufp);
        }

        return ret;
    }

    if (ret < 0 && ret != AVERROR_EOF)
        return ret;

    if (ff_check_interrupt(&c->interrupt_callback))
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] force quit \n", __FILE__, __LINE__);
        return AVERROR_EOF;
    }

    hlsCloseInput(v);

load_next:
    for (i = 0; i < c->hls_stream_nb; i++) {
        c->hls_stream[i]->has_read = 0;
    }

    if (NULL != c->uuid) {
        c->ts_last_btime = av_gettime();
        av_log(c->parent, AV_LOG_ERROR, "[%s:%d] NETWORK_TS_SEGMENT_COMPLETE load_next urlcontext=%xh, hls_seg_cur=%d,ts_send_time=%lld,"
            "ts_first_btime=%lld,ts_last_btime=%lld, ts_length=%d \n", __FUNCTION__, __LINE__,
             v->seg_stream.input, v->seg_list.hls_seg_cur, c->ts_send_time, c->ts_first_btime, c->ts_last_btime, c->ts_length);
        url_errorcode_cb(c->interrupt_callback.opaque, NETWORK_TS_SEGMENT_COMPLETE, "http");
    }

    if (AVERROR_EOF == hlsStepSegCur(c, v)) {
        av_log(c->parent, AV_LOG_WARNING, "[%s %d] backward download to sof!hls[%d](iframe_only:%d)\n",
            __FUNCTION__, __LINE__, v->seg_list.hls_index, v->iframe_only);
        return AVERROR_EOF;
    }

    if (hlsCheckSwitchVariant(c)) {
        if (!v->seg_list.hls_finished) {
            need_reload = 1;
        }
        url_errorcode_cb(c->interrupt_callback.opaque, NETWORK_ADJUST_BITRATE, "http");
    }

    c->segment_stream_eof = 1;
    c->hls_stream_cur = v->seg_list.hls_seg_cur;

    if (v->seg_demux.ctx) {
        v->seg_list.needed = 0;
        if (v->seg_demux.ctx->nb_streams > v->seg_demux.nb_streams) {
            int j = 0;
            av_log(c->parent, AV_LOG_ERROR, "[%s:%d] number of streams changed, offset %d nb %d p_nb %d \n",
                __FILE_NAME__, __LINE__, v->seg_list.hls_stream_offset, v->seg_demux.ctx->nb_streams, v->seg_demux.nb_streams);
            for (j = v->seg_demux.nb_streams; j < v->seg_demux.ctx->nb_streams; j++) {
                AVStream *st = av_new_stream(v->seg_demux.parent, 0);
                if (!st) {
                    ret = AVERROR(ENOMEM);
                    return ret;
                }
                v->seg_demux.nb_streams ++;
                avcodec_copy_context(st->codec, v->seg_demux.ctx->streams[j]->codec);
                av_log(c->parent, AV_LOG_INFO, "%s:%d, av_new_stream, id: %d\n", __FILE_NAME__, __LINE__, st->id);
            }
        }

        for (i = v->seg_list.hls_stream_offset; i < v->seg_list.hls_stream_offset + v->seg_demux.ctx->nb_streams; i++) {
            if (v->seg_demux.parent->streams[i]->discard < AVDISCARD_ALL)
                v->seg_list.needed = 1;
        }
    }

    if (!v->seg_list.needed) {
        av_log(v->seg_demux.parent, AV_LOG_INFO, "No longer receiving variant %d\n",v->seg_list.hls_index);
        return AVERROR_EOF;
    }

    goto restart;
}

static int hlsReditionReadDataCb(void *opaque, uint8_t *buf, int buf_size)
{
    hls_stream_info_t *v = opaque;
    HLSContext *c = v->seg_demux.parent->priv_data;
    int ret, i;
    int need_reload = 0;
    int64_t time_diff;
    int64_t time_wait;
    int open_fail = 0;
    AVFormatContext *s = v->seg_demux.parent;

restart:
    if (!v->seg_stream.input) {
reload:
        if (ff_check_interrupt(&c->interrupt_callback))
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition force quit \n", __FILE__, __LINE__);
            return AVERROR_EOF;
        }

        time_diff = av_gettime() - v->seg_list.hls_last_load_time;
        time_wait = v->seg_list.hls_target_duration * AV_TIME_BASE;

        if (time_wait > HLS_MAX_WAITE_TIME)
            time_wait = HLS_MAX_WAITE_TIME;

        /* If this is a live stream and target_duration has elapsed since
         * the last playlist reload, reload the variant playlists now. */
        if (!v->seg_list.hls_finished && ((llabs(time_diff) >= time_wait) || need_reload)) {
reparse:
            //ret = hlsFreshUrl(v); //only for yueme version
            ret = hlsParseM3U8(c, v->url, v, NULL);
            if (ret < 0) {
                if (ff_check_interrupt(&c->interrupt_callback))
                    return ret;

                /* fix seek operation blocked */
                if (s->is_time_shift)
                {
                    return AVERROR(EAGAIN);
                }

                usleep(1000*1000);
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition redo hlsParseM3U8\n",
                        __FILE_NAME__, __LINE__);
                goto reparse;
            }

            need_reload = 0;
        }

        if (v->seg_list.hls_seg_cur < v->seg_list.hls_seg_start) {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition skipping %d segments ahead, expired from playlists",
                    __FILE_NAME__, __LINE__,
                    v->seg_list.hls_seg_start - v->seg_list.hls_seg_cur);
            v->seg_list.hls_seg_cur = v->seg_list.hls_seg_start;
        }

        if (v->seg_list.hls_seg_cur >= v->seg_list.hls_seg_start + v->seg_list.hls_segment_nb) {
            if (v->seg_list.hls_finished)
                return AVERROR_EOF;

            #if defined (ANDROID_VERSION)
            /* add for fresh url */
            /* setprop media.hiplayer.hls.freshurl true or false
                   the project may need set true:
                   1. iptv.china.mobile
                   2. iptv.china.telecom (yue me)
                   */
            char value[PROPERTY_VALUE_MAX] = {0};
            if (property_get("media.hiplayer.hls.freshurl", value, NULL) && !strncmp(value, "true", 4)) {
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition need fresh url\n", __FILE_NAME__, __LINE__);

                if (0 == hlsFreshUrl(v)) {
                    need_reload = 1;
                    goto reload;
                }
            }
            /* end: add for fresh url*/
            #endif

            time_diff = av_gettime() - v->seg_list.hls_last_load_time;
            time_wait = v->seg_list.hls_target_duration * AV_TIME_BASE;

            if (time_wait > HLS_MAX_WAITE_TIME)
                time_wait = HLS_MAX_WAITE_TIME;

            while (llabs(time_diff) < time_wait) {
                if (ff_check_interrupt(&c->interrupt_callback))
                    return AVERROR_EOF;

                usleep(100*1000);

                time_diff = av_gettime() - v->seg_list.hls_last_load_time;
                time_wait = v->seg_list.hls_target_duration * AV_TIME_BASE;

                if (time_wait > HLS_MAX_WAITE_TIME)
                    time_wait = HLS_MAX_WAITE_TIME;
            }

            /* Enough time has elapsed since the last reload */
            if (ff_check_interrupt(&c->interrupt_callback))
                return AVERROR_EOF;
            goto reload;
        }

        if (!v->seg_list.hls_finished) {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition Sequence ReCount, v.seg_start:%d, v.seg_cur:%d, v.seg_nb:%d, cur_hls.seg_start:%d, cur_hls.seg_cur:%d, cur_hls.segment_nb:%d",
                __FUNCTION__, __LINE__, v->seg_list.hls_seg_start, v->seg_list.hls_seg_cur, v->seg_list.hls_segment_nb,
                c->cur_hls->seg_list.hls_seg_start, c->cur_hls->seg_list.hls_seg_cur, c->cur_hls->seg_list.hls_segment_nb);

            while (v->seg_list.hls_seg_start + \
                v->seg_list.hls_segment_nb <= v->seg_list.hls_seg_cur) {
                ret = hlsParseM3U8(c, v->url,v, NULL);
                if (ret < 0) {
                    if (ff_check_interrupt(&c->interrupt_callback))
                        return ret;

                    /* fix seek operation blocked */
                    if (s->is_time_shift)
                    {
                        return AVERROR(EAGAIN);
                    }

                    usleep(1000*1000);
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition redo hlsParseM3U8\n", __FILE_NAME__, __LINE__);
                }
            }
        }

reopen:
        ret = hlsOpenSegment(v);
        if (ret < 0) {
            open_fail = 1;
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition open segment ret error= %d \n", __FILE_NAME__, __LINE__, ret);
            if (ff_check_interrupt(&c->interrupt_callback) || ret == AVERROR(ENOMEM) ||  ret == AVERROR_EOF) {
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition return EOF, hlsOpenSegment = %d \n",__FILE_NAME__, __LINE__, ret);
                return AVERROR_EOF;
            }
            if (v->seg_list.hls_finished) { // Reload item for metadata stream
                if (ret == AVERROR(EAGAIN)) {
                    usleep(100*1000);
                    goto reopen;
                } else {
                    goto load_next;
                }
            } else { // Reload playlist for live stream
                v->seg_list.hls_seg_cur++;
                need_reload = 1;
                goto reload;
            }
        } else {
            AVFormatContext *s = c->parent;
            if (v->seg_stream.input) {
                v->seg_stream.input->parent = s->pb;
                if (open_fail && !strncmp(v->seg_stream.input->filename, "http://", strlen("http://"))) {
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition network normal\n",__FILE_NAME__,__LINE__);
                    url_errorcode_cb(c->interrupt_callback.opaque, NETWORK_NORMAL, "http");
                    open_fail = 0;
                }
            }
            if (v->seg_key.IO_decrypt && v->seg_key.IO_decrypt->hd) {
                v->seg_key.IO_decrypt->hd->parent = s->pb;
                if (open_fail && !strncmp(v->seg_key.IO_decrypt->hd->filename, "http://", strlen("http://"))) {
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition network normal\n",__FILE_NAME__,__LINE__);
                    url_errorcode_cb(c->interrupt_callback.opaque, NETWORK_NORMAL, "http");
                    open_fail = 0;
                }
            }
        }
    }

    int64_t  start = av_gettime();
    if (v->seg_key.IO_decrypt) {  // Encrypted stream
        if (!v->seg_stream.input)
            v->seg_stream.input = v->seg_key.IO_decrypt->hd;
        ret = hls_decrypt_read(v->seg_key.IO_decrypt, buf, buf_size);
    } else {  // Normal stream
        int64_t left_size = 1;
        if (c->cur_seg->size > 0) {
            left_size = c->cur_seg->size - v->seg_stream.offset;
        }
        if (left_size > 0) {
            ret = hls_read(v->seg_stream.input, v->seg_stream.offset, buf, buf_size);
            if(ret > 0) {
                v->seg_stream.offset += ret;
            }
        } else {
            ret = AVERROR_EOF;
        }
    }
    int64_t  end = av_gettime();
    if (ret > 0) {
        unsigned int read_size = ret;
        unsigned int read_time = end - start;
        hlsSetDownLoadSpeed(c, read_size, read_time, start, end);
        return ret;
    }

    if (ret < 0 && ret != AVERROR_EOF)
        return ret;

    if (ff_check_interrupt(&c->interrupt_callback))
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition force quit \n", __FILE_NAME__, __LINE__);
        return AVERROR_EOF;
    }

    hlsCloseInput(v);

load_next:
    if (AVERROR_EOF == hlsStepSegCur(c, v)) {
        av_log(c->parent, AV_LOG_WARNING, "[%s %d] backward download to sof!hls[%d](iframe_only:%d)\n",
            __FUNCTION__, __LINE__, v->seg_list.hls_index, v->iframe_only);
        return AVERROR_EOF;
    }
    av_log(NULL, AV_LOG_ERROR, "[%s:%d] hlsRedition hls.seg_start = %d, hls.seg_cur = %d, hls.seg_nb = %d\n",
        __FUNCTION__, __LINE__,  v->seg_list.hls_seg_start, v->seg_list.hls_seg_cur, v->seg_list.hls_segment_nb);

    if (v->seg_demux.ctx) {
        v->seg_list.needed = 0;
        for (i = v->seg_list.hls_stream_offset; i < v->seg_list.hls_stream_offset + v->seg_demux.ctx->nb_streams; i++) {
            if (v->seg_demux.parent->streams[i]->discard < AVDISCARD_ALL)
                v->seg_list.needed = 1;
        }
    }
    if (!v->seg_list.needed) {
        av_log(v->seg_demux.parent, AV_LOG_INFO, "hlsRedition No longer receiving redition %d\n",v->seg_list.hls_index);
        return AVERROR_EOF;
    }

    goto restart;
}

static int hlsRecheckDiscardFlags(AVFormatContext *s, int first)
{
    HLSContext *c = s->priv_data;
    int i, changed = 0;
#if 0
    /* Check if any new streams are needed */
    for (i = 0; i < c->hls_stream_nb; i++)
        c->hls_stream[i]->seg_list.cur_needed = 0;

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        hls_stream_info_t *hls = c->hls_stream[s->streams[i]->id];
        if (st->discard < AVDISCARD_ALL)
            hls->seg_list.cur_needed = 1;
    }

    for (i = 0; i < c->hls_stream_nb; i++) {
        hls_stream_info_t *hls = c->hls_stream[i];
        if (hls->seg_list.cur_needed && !hls->seg_list.needed) {
            hls->seg_list.needed = 1;
            changed = 1;
            hls->seg_list.hls_seg_cur = c->hls_stream_cur;
            hls->seg_stream.IO_pb.eof_reached = 0;
            av_log(s, AV_LOG_INFO, "Now receiving variant %d\n", i);
        } else if (first && !hls->seg_list.cur_needed && hls->seg_list.needed) {
            if (hls->seg_stream.input)
                hls_close(hls->seg_stream.input);
            hls->seg_stream.input = NULL;
            hls->seg_stream.offset = 0;
            hls->seg_list.needed = 0;
            changed = 1;
            av_log(s, AV_LOG_INFO, "No longer receiving variant %d\n", i);
        }
    }
#endif
    return changed;
}

/*******************************************************************************
 * Implementation of HLS demuxer modules
 ******************************************************************************/
static int HLS_probe(AVProbeData *p)
{
    /* Require #EXTM3U at the start, and either one of the ones below
     * somewhere for a proper match. */
    if (strncmp(p->buf, "#EXTM3U", 7))
        return 0;
    if (strstr(p->buf, "#EXT-X-STREAM-INF:")     ||
        strstr(p->buf, "#EXT-X-TARGETDURATION:") ||
        strstr(p->buf, "#EXT-X-MEDIA-SEQUENCE:") ||
        strstr(p->buf, "#EXTINF:"))
        return AVPROBE_SCORE_MAX;

    return 0;
}

static void hlsCalDuration(AVFormatContext *s)
{
    HLSContext *c = NULL;
    hls_stream_info_t *hls = NULL;
    int64_t duration = 0;
    int i = 0, hls_finished = 0;


    if (NULL == s || s->priv_data == NULL)
    {
        av_log(c->parent, AV_LOG_ERROR, "[%s:%d], AVFormatContext ptr is null\n", __FILE_NAME__, __LINE__);
        return;
    }

    c = s->priv_data;
    if (c->hls_stream_nb <= 0) {
        av_log(c->parent, AV_LOG_ERROR, "[%s:%d] no streams\n", __FILE_NAME__, __LINE__);
        return;
    }

    for (i = 0; i < c->hls_stream_nb; i ++) {
        if (c->hls_stream[i]->is_parsed) {
            hls = c->hls_stream[i];
            break;
        }
    }

    if (!hls) {
        int ret;
        hls = c->hls_stream[0];
        ret = hlsParseM3U8(c, hls->url, hls, NULL);
        if (ret < 0) {
            s->is_live_stream = 1;
            s->is_time_shift = 0;
            av_log(c->parent, AV_LOG_ERROR, "[%s:%d] no hls is parsed, parse hls[0] return error=%d, set live stream!\n",
                __FILE_NAME__, __LINE__, ret);
            return;
        }
    }

    for (i = 0; i < hls->seg_list.hls_segment_nb; i++) {
        hls->seg_list.segments[i]->start_time = duration;
        duration += hls->seg_list.segments[i]->total_time;
    }

    if (hls->seg_list.hls_finished) {
        s->duration = duration * (AV_TIME_BASE / 1000);
        s->is_live_stream = 0;
        s->is_time_shift = 0;
    } else {
        s->is_live_stream = 1;
        if (HLS_TIME_SHIFT_SEGMENT_NUM_MIN < hls->seg_list.hls_segment_nb) {
            av_log(c->parent, AV_LOG_ERROR, "[%s:%d] is_time_shift segment num:%d", __FILE_NAME__, __LINE__, c->hls_stream[0]->seg_list.hls_segment_nb);
            s->duration = duration * (AV_TIME_BASE / 1000);
            s->is_time_shift = 1;
        } else {
            s->duration = 10 * AV_TIME_BASE; // If no duration, HiPlayer will continuously seek to 0
            s->is_time_shift = 0;
        }
    }
    av_log(c->parent, AV_LOG_ERROR, "[%s:%d] duration:%lld", __FILE_NAME__, __LINE__,s->duration);

    return;
}

static int hlsUpdateStreamCodecInfo(AVStream *target, AVStream *src)
{
    if (!target || !src || !target->codec || !src->codec) {
        return -1;
    }

    if (src->codec->codec_type == AVMEDIA_TYPE_VIDEO &&
        target->codec->width <= 0 && target->codec->height <= 0 &&
        target->codec->codec_type == AVMEDIA_TYPE_VIDEO &&
        src->codec->width > 0 && src->codec->height > 0) {
        target->codec->width = src->codec->width;
        target->codec->height = src->codec->height;
        av_log(NULL, AV_LOG_WARNING, "[%s,%d], set hls W:%d, H:%d\n", __FILE_NAME__, __LINE__,
            target->codec->width, target->codec->height);
    }

    if (AVMEDIA_TYPE_UNKNOWN == target->codec->codec_type &&
        AVMEDIA_TYPE_UNKNOWN != src->codec->codec_type) {
        target->codec->codec_type = src->codec->codec_type;
        av_log(NULL, AV_LOG_WARNING, "[%s,%d] update hls codec type:%d\n",
            __FILE_NAME__, __LINE__, target->codec->codec_type);
    }

    if (CODEC_ID_NONE == target->codec->codec_id &&
        CODEC_ID_NONE != src->codec->codec_id) {
        target->codec->codec_id = src->codec->codec_id;
        av_log(NULL, AV_LOG_WARNING, "[%s,%d] update hls codec id:%d\n",
            __FILE_NAME__, __LINE__, target->codec->width);
    }

    return 0;
}

static int hlsOpenStream(HLSContext *c, hls_stream_info_t *hls, int *cur_seg_no)
{
    int ret, j;
    hls_segment_t *cur_seg = NULL;
    struct ByteIOContext *pb = NULL;
    AVInputFormat *in_fmt = NULL;

    /**make resolution change available from 3716c-0.6.3 r41002 changed by duanqingpeng**/
    hls->seg_stream.IO_buf = av_mallocz(INITIAL_BUFFER_SIZE);
    if (!hls->is_redition_stream) {
        init_put_byte(&hls->seg_stream.IO_pb, hls->seg_stream.IO_buf,
                INITIAL_BUFFER_SIZE, 0, hls, hlsReadDataCb, NULL, NULL);
    } else {
        init_put_byte(&hls->seg_stream.IO_pb, hls->seg_stream.IO_buf,
                INITIAL_BUFFER_SIZE, 0, hls, hlsReditionReadDataCb, NULL, NULL);
    }
    // d00198887 can not seek in every segment
    hls->seg_stream.IO_pb.seekable = 0;
    pb = &hls->seg_stream.IO_pb;
    cur_seg = hls->seg_list.segments[*cur_seg_no];

    ret = av_probe_input_buffer(pb, &in_fmt, cur_seg->url, NULL, 0, 0, &(c->interrupt_callback));
    if (ret < 0) {
        av_log(c->parent, AV_LOG_ERROR, "[%s:%d] is_redition_stream=%d, av_probe_input_buffer fail=%d, cur_seg->url:%s\n",
            __FILE_NAME__, __LINE__, hls->is_redition_stream, ret, cur_seg->url);
        goto fail;
    }

    hls->seg_demux.ctx->pb = &hls->seg_stream.IO_pb;
    //ret = av_open_input_stream(&hls->seg_demux.ctx, &hls->seg_stream.IO_pb, hls->seg_list.segments[0]->url, in_fmt, NULL);
    for (j = 0; j < hls->seg_list.hls_segment_nb; j++) {
        avio_flush(pb);
        ret = av_open_input_stream(&hls->seg_demux.ctx, &hls->seg_stream.IO_pb, cur_seg->url, in_fmt, NULL);
        if (ret < 0) {
            av_log(c->parent, AV_LOG_ERROR, "[%s:%d] is_redition_stream=%d, av_open_input_stream fail=%d, cur_seg->url:%s\n",
                __FILE_NAME__, __LINE__, hls->is_redition_stream, ret, cur_seg->url);

            if (ff_check_interrupt(&c->interrupt_callback)) {
                break;
            }

            (*cur_seg_no) += 1;
            if (*cur_seg_no < c->cur_hls->seg_list.hls_segment_nb) {
                cur_seg = hls->seg_list.segments[*cur_seg_no];
                continue;
            }
        }
        break;
    }

    if (ret < 0) {
        av_log(c->parent, AV_LOG_ERROR, "[%s:%d] is_redition_stream=%d, av_open_input_stream fail, hls index=%d(is redition:%d), cur_seg->url:%s\n",
            __FILE_NAME__, __LINE__, hls->is_redition_stream, hls->seg_list.hls_index, hls->is_redition_stream, cur_seg->url);
        goto fail;
    }
    //disable wrap dts and pts
    hls->seg_demux.ctx->correct_ts_overflow = 0;

fail:
    return ret;
}

static int hlsOpenStream2(AVFormatContext *s,
    hls_stream_info_t *hls, int hls_index, int *cur_seg_no)
{
    HLSContext *c = s->priv_data;
    char bitrate_str[20];
    int ret = 0,j;

    if (!hls || !cur_seg_no || hls->seg_list.hls_segment_nb <= *cur_seg_no) {
        return -1;
    }

    if (!(hls->seg_demux.ctx = avformat_alloc_context())) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    hls->seg_list.hls_index  = hls_index;
    hls->seg_list.needed = 1;
    hls->seg_demux.parent = s;

    if (!hls->is_redition_stream) {
        /* If this is a live stream with more than 3 segments, start at the third last segment. */
        hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start;
        if (!hls->seg_list.hls_finished && hls->seg_list.hls_segment_nb > 3) {
            if (s->hls_live_start_num >= 1 && s->hls_live_start_num <= hls->seg_list.hls_segment_nb) {
                hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start + s->hls_live_start_num - 1;
            } else {
                hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start + hls->seg_list.hls_segment_nb - 3;
            }
            av_log(c->parent, AV_LOG_INFO,"[%s:%d]: hls live stream first play seg is %d \n", __FILE_NAME__, __LINE__, hls->seg_list.hls_seg_cur);
        }
    } else if (c->hls_stream_nb > 0) {
        hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start + c->hls_stream[0]->seg_list.hls_seg_cur \
            - c->hls_stream[0]->seg_list.hls_seg_start;
    } else {
        hls->seg_list.hls_seg_cur = 0;
    }

    ret = hlsOpenStream(c, hls, cur_seg_no);
    if (ret < 0) {
        goto fail;
    }

    hls->seg_demux.nb_streams = 0;
    hls->seg_list.hls_stream_offset = s->nb_streams;
    snprintf(bitrate_str, sizeof(bitrate_str), "%d", hls->bandwidth);
    /* Create new AVStreams for each stream in this variant */
    for (j = 0; j < hls->seg_demux.ctx->nb_streams; j++) {
        if (NULL != hls->seg_demux.ctx->streams[j]->codec
            && AVMEDIA_TYPE_UNKNOWN == hls->seg_demux.ctx->streams[j]->codec->codec_type) {
            av_log(c->parent, AV_LOG_ERROR, "%s(%d),invalid stream, codec[%d],name:%s, type:%d", __FILE_NAME__, __LINE__,
            j, hls->seg_demux.ctx->streams[j]->codec->av_class->class_name, hls->seg_demux.ctx->streams[j]->codec->codec_type);
        }
        AVStream *st = av_new_stream(s, 0);
        if (!st) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        hls->seg_demux.nb_streams ++;
        avcodec_copy_context(st->codec, hls->seg_demux.ctx->streams[j]->codec);
    }

fail:

    return ret;
}

static int HLS_read_header(AVFormatContext *s, AVFormatParameters *ap)
{
    HLSContext *c = s->priv_data;
    int ret = 0, i, j, stream_offset = 0;
    URLContext *uc = (URLContext *) s->pb->opaque;
    const char *cache_name = "hicache";
    int start_stream_num = 0;

    if(NULL != c)
        c->reset_appoint_id = 0;

    #if 0
    /* Get headers context */
    if (uc && uc->headers) {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] headers=%s\n", __FILE_NAME__, __LINE__, uc->headers);
        if (c->headers) {
            av_free(c->headers);
            c->headers = NULL;
        }

        c->headers = av_strdup(uc->headers);
    }
    #endif

    av_log(NULL, AV_LOG_ERROR, "[%s:%d]%s\n", __FILE_NAME__, __LINE__, __FUNCTION__);

    if (uc && uc->is_streamed)
    {
        if (c->user_agent)
            av_freep(&c->user_agent);

        if (uc && uc->priv_data && (av_opt_get(uc->priv_data, "user-agent", 0, &c->user_agent) >= 0))
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] user-agent: %s\n", __FILE_NAME__, __LINE__, c->user_agent);

        if (c->referer)
            av_freep(&c->referer);

        if (uc && uc->priv_data && (av_opt_get(uc->priv_data, "referer", 0, &c->referer) >= 0))
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] referer: %s\n", __FILE_NAME__, __LINE__, c->referer);

        if (c->cookies)
            av_freep(&c->cookies);

        if (uc && uc->priv_data && (av_opt_get(uc->priv_data, "cookies", 0, &c->cookies) >= 0))
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] cookies: %s\n", __FILE_NAME__, __LINE__, c->cookies);

        if (c->headers)
            av_freep(&c->headers);

        if (uc && uc->priv_data && (av_opt_get(uc->priv_data, "headers", 0, &c->headers) >= 0))
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] headers: %s\n", __FILE_NAME__, __LINE__, c->headers);
    }

    if (uc)
    {
        c->interrupt_callback.callback = uc->interrupt_callback.callback;
        c->interrupt_callback.opaque = uc->interrupt_callback.opaque;
    }

    c->file_name = s->filename;
    c->has_video_stream = 0;

    c->downspeed.down_size = 0;
    c->downspeed.down_time = 0;
    c->downspeed.speed = 0;
    c->downspeed.head = NULL;
    c->downspeed.tail = NULL;
    c->use_offset_seq = 0;
    c->offset_stream_index = -1;
    c->seek_offset_us = -1;
    c->last_timestamp = 0;

    c->tsfp = NULL;
    c->mufp = NULL;
    c->stHlsUrlInfo.enable = 0;
    c->cur_play_speed = 1.0;

    char name[INITIAL_URL_SIZE];

    memset(name, 0, sizeof(name));
    memset(c->save_hls_path,0,sizeof(c->save_hls_path));
    char tmpdest[] ="/sdcard/hiplayer";
    strncpy(c->save_hls_path,tmpdest,strlen(tmpdest));
    snprintf(name, sizeof(name)-1, "%s/log.m3u8", c->save_hls_path);

    c->mufp = fopen(name, "w+b");
    if (NULL == c->mufp)
    {
        av_log(NULL,AV_LOG_ERROR,"[%s:%d] fopen fail \n",__FILE_NAME__,__LINE__);
    }

    /* Get host name string */
    if (uc && uc->moved_url)
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d], moved_url:%s\n", __FILE_NAME__, __LINE__, uc->moved_url);
        ret = hlsParseM3U8(c, uc->moved_url, NULL, s->pb);
    }
    else
    {
        if (!strncmp(c->file_name, cache_name, 7))
            ret = hlsParseM3U8(c, strstr(s->filename, "http"), NULL, s->pb);
        else
            ret = hlsParseM3U8(c, s->filename, NULL, s->pb);
    }

    if (ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d], ret:%d\n", __FILE_NAME__, __LINE__, ret);
        goto fail;
    }

    if (c->hls_stream_nb == 0) {
        av_log(NULL, AV_LOG_WARNING, "Empty playlist\n");
        ret = AVERROR_EOF;
        goto fail;
    }

    /* If the playlist only contained variants, parse each individual
     * variant playlist. */
    if (c->hls_stream_nb > 1 || c->hls_stream[0]->seg_list.hls_segment_nb == 0) {
        int valid_stream_nb = 0;
        int last_seg_start = 0;
        int min_segment_nb = 0;
        c->timeshift_time = s->time_shift_duration;

        if (HLS_MODE_FAST == s->hls_start_mode && 1 < c->hls_stream_nb)
        {
            start_stream_num = hlsGetDefaultIndex(c, HLS_MODE_FAST);
            hls_stream_info_t *hls = c->hls_stream[start_stream_num];
            ret = hlsParseM3U8(c, hls->url, hls, NULL);
            if (0 <= ret)
            {
                valid_stream_nb = 1;
            }
        }
        else
        {
            for (i = 0; i < c->hls_stream_nb; i++) {
                hls_stream_info_t *hls = c->hls_stream[i];

                /* before: add for fresh url */
                /* setprop media.hiplayer.hls.freshurl true or false
                              the project may need set true:
                              1. iptv.china.mobile
                              2. iptv.china.telecom (yue me)
                         */
                char value[PROPERTY_VALUE_MAX] = {0};
                if (property_get("media.hiplayer.hls.freshurl", value, NULL) && !strncmp(value, "true", 4)) {
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] cache time = %d, parse url = %s \n",
                        __FILE__, __LINE__, c->timeshift_time, hls->url);

                    char *servicetype = NULL, *endchar = NULL;
                    servicetype = strstr(s->filename, "servicetype=2");
                    if (NULL == servicetype) {
                        /* '=' need to be transferred from '%3D' */
                        servicetype = strstr(s->filename, "servicetype%3D2");
                    }
                    endchar = strstr(s->filename, "?");

                    if (NULL != servicetype && NULL != endchar) {
                        //calc starttime
                        time_t lt = time(0) - labs(c->timeshift_time) / 1000 - 28800;
                        struct tm *ptr = localtime(&lt);
                        char shift_time[128];

                        memset(shift_time, 0, 128);
                        strftime(shift_time, 128, "%Y%m%d%H%M%S", ptr);

                        //memset(p, 0, hls->url + INITIAL_URL_SIZE - p);
                        snprintf(hls->url + strlen(hls->url), INITIAL_URL_SIZE - strlen(hls->url), "%s%s%s%s",
                            endchar, "&playseek=", shift_time, "-&zoneoffset=480&timezone=UTC");
                    }
                    else
                    {
                        av_log(NULL, AV_LOG_ERROR, "[%s:%d] not shift program \n", __FILE__, __LINE__);
                    }

                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] cache time = %d, parse url = %s \n",
                        __FILE__, __LINE__, c->timeshift_time, hls->url);
                }
                /* end: add for fresh url */

                if ((ret = hlsParseM3U8(c, hls->url, hls, NULL)) < 0) {
                    continue;
                } else {
                    hls->first_seg_number = hls->seg_list.hls_seg_start;
                    /* if the segment start number is not equal, we use offset caculate next segment sequence */
                    valid_stream_nb = 1;

                    if (0 == i || hls->seg_list.hls_segment_nb < min_segment_nb) {
                        min_segment_nb = hls->seg_list.hls_segment_nb;
                    }

                    if (i > 0 && min_segment_nb > 1
                        && abs(last_seg_start - hls->seg_list.hls_seg_start) >= (min_segment_nb - 1)
                        && 0 == hls->seg_list.hls_finished) {
                        c->use_offset_seq = 1;
                        av_log(NULL, AV_LOG_ERROR, "hls live Stream, use offset sequence number refresh list\n");
                    }

                    last_seg_start = hls->seg_list.hls_seg_start;
                    //break;    //zzg continue parse rest list
                }
            }
        }

        if (valid_stream_nb == 0) {
            ret = AVERROR_EOF;
            goto fail;
        }
    }

    /* parse all reditions */
    for (i = 0; i < c->nb_reditions;i++) {
        hls_stream_info_t *rend = c->reditions[i];
        if ((ret = hlsParseM3U8(c, rend->url, rend, NULL)) < 0) {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] parse redition[%d] m3u8 fail=%d\n",
                __FILE_NAME__, __LINE__, i, ret);
            continue;
        }
    }

    int bVodStream = 0;

    for (i = 0; i < c->hls_stream_nb; i++) {
        hls_stream_info_t *hls = c->hls_stream[i];

        if (1 == hls->seg_list.hls_finished) {
            bVodStream = 1;
            if (c->nb_reditions <= 0) {
                break;
            }
        }
        if (c->nb_reditions <= 0) {
            continue;
        }
        if (hls->attr.v.video_group[0]) {
            hlsAddReditionToVariant(c, hls, HLSMEDIA_VIDEO, hls->attr.v.video_group);
        }
        if (hls->attr.v.audio_group[0]) {
            hlsAddReditionToVariant(c, hls, HLSMEDIA_AUDIO, hls->attr.v.audio_group);
        }
        if (hls->attr.v.subtitles_group[0]) {
            hlsAddReditionToVariant(c, hls, HLSMEDIA_SUBTITLE, hls->attr.v.subtitles_group);
        }
    }

    if (c->has_video_stream) {
        int stream_freed = 0;
        for (i = 0; i < c->hls_stream_nb; i++) {
            hls_stream_info_t *hls = c->hls_stream[i];
            if (!hls->video_codec || (0 == hls->seg_list.hls_finished && 1 == bVodStream && hls->is_parsed)) {
                stream_freed = 1;
                hlsFreeSegmentList(hls);

                av_free_packet(&hls->seg_demux.pkt);
                av_free(hls->seg_stream.IO_pb.buffer);

                if (hls->seg_stream.headers) {
                    av_free(hls->seg_stream.headers);
                    hls->seg_stream.headers = NULL;
                }

                if (hls->seg_key.IO_decrypt) {
                    hls_decrypt_close(hls->seg_key.IO_decrypt);
                    av_freep(&hls->seg_key.IO_decrypt);
                    hls->seg_key.IO_decrypt = NULL;
                    hls->seg_stream.input = NULL; // already freed in hls_decrypt_close
                }

                if (hls->seg_stream.input) {
                    hls_close(hls->seg_stream.input);
                    hls->seg_stream.input = NULL;
                    hls->seg_stream.offset = 0;
                }

                if (hls->seg_demux.ctx) {
                    hls->seg_demux.ctx->pb = NULL;
                    av_close_input_file(hls->seg_demux.ctx);
                }

                av_free(hls);

                if (i == c->hls_stream_nb - 1) {
                    c->hls_stream[i] = NULL;
                    c->hls_stream_nb--;
                } else {
                    int j = i;
                    for (j = i; j < c->hls_stream_nb - 1; j++) {
                        c->hls_stream[j] = c->hls_stream[j + 1];
                    }
                    c->hls_stream[c->hls_stream_nb - 1] = NULL;
                    c->hls_stream_nb--;
                }
                i--;
            }
        }

        if (HLS_MODE_FAST == s->hls_start_mode && stream_freed) {
            hls_stream_info_t *def_hls = NULL;
            start_stream_num = hlsGetDefaultIndex(c, s->hls_start_mode);
            def_hls = c->hls_stream[start_stream_num];
            if (!def_hls->is_parsed) {
                ret = hlsParseM3U8(c, def_hls->url, def_hls, NULL);
                if (ret < 0) {
                    for (i = 0; i < c->hls_stream_nb; i++) {
                        def_hls = c->hls_stream[i];
                        if (i == start_stream_num) {
                            continue;
                        }
                        if (!c->hls_stream[i]->is_parsed) {
                            ret = hlsParseM3U8(c, def_hls->url, def_hls, NULL);
                            if (ret >= 0) {
                                start_stream_num = i;
                                break;
                            }
                        } else {
                            start_stream_num = i;
                            break;
                        }
                    }
                    if (!def_hls->is_parsed) {
                        av_log(NULL, AV_LOG_ERROR, "[%s,%d] valid stream not found!\n", __FUNCTION__, __LINE__);
                        ret = AVERROR_EOF;
                        goto fail;
                    }
                }
            }
        }
    }

    if (c->hls_stream[start_stream_num]->seg_list.hls_segment_nb == 0) {
        av_log(NULL, AV_LOG_WARNING, "Empty playlist\n");
        ret = AVERROR_EOF;
        goto fail;
    }

    c->appoint_id = -1;
    c->real_bw = 0;
    c->netdata_read_speed = 0;

    if (c->hls_stream_nb > 1 && c->hls_stream[start_stream_num]->seg_list.hls_finished && HLS_MODE_FAST != s->hls_start_mode) {
        int maxnb = c->hls_stream[0]->seg_list.hls_segment_nb, minnb = c->hls_stream[0]->seg_list.hls_segment_nb;
        int maxband = 0, maxbandidx = 0;

        av_log(NULL,AV_LOG_ERROR,"#[%s:%d] judgement #\n",__FUNCTION__,__LINE__);

        for (i = 0; i < c->hls_stream_nb; i++) {
            maxnb = FFMAX(c->hls_stream[i]->seg_list.hls_segment_nb, maxnb);
            minnb = FFMIN(c->hls_stream[i]->seg_list.hls_segment_nb, minnb);

            if (c->hls_stream[i]->bandwidth > maxband) {
                maxband = c->hls_stream[i]->bandwidth;
                maxbandidx = i;
            }
            av_log(NULL,AV_LOG_ERROR,"#[%s:%d] maxnb:%d minnb:%d maxband:%d maxbandidx:%d#\n",
                    __FUNCTION__,__LINE__,maxnb,minnb,maxband,maxbandidx);
        }

        if ((maxnb - minnb) > 1) {
            hls_stream_info_t *tmp = c->hls_stream[0];
            c->hls_stream[0] = c->hls_stream[maxbandidx];
            c->hls_stream[maxbandidx] = tmp;
            c->appoint_id = 0;
            av_log(NULL,AV_LOG_ERROR,"#[%s:%d] maxnb:%d minnb:%d c->appoint_id:%d stop switch rate.#\n",
                    __FUNCTION__,__LINE__,maxnb,minnb, c->appoint_id);
        }
    }

    hlsCalDuration(s);

    c->parent = s;
    if (c->hls_stream_nb && !strncmp("http", c->hls_stream[start_stream_num]->seg_list.segments[0]->url, 4)) {
        s->pb->downspeedable = 1;
        DownSpeed *downspeed = &(s->pb->downspeed);
        downspeed->down_size = 0;
        downspeed->down_time = 0;
        downspeed->speed = 0;
        downspeed->head = NULL;
        downspeed->tail = NULL;
    } else {
        s->pb->downspeedable = 0;
        DownSpeed *downspeed = &(s->pb->downspeed);
        downspeed->down_size = 0;
        downspeed->down_time = 0;
        downspeed->speed = 0;
        downspeed->head = NULL;
        downspeed->tail = NULL;
    }

    c->appoint_id = -1;
    c->real_bw = 0;
    c->netdata_read_speed = 0;
    if (c->hls_stream_nb > 0) {
        if ((c->appoint_id >= 0) && (c->appoint_id < c->hls_stream_nb) && (c->hls_stream[c->appoint_id]->seg_list.hls_segment_nb > 0)) {
            c->cur_seg = c->hls_stream[c->appoint_id]->seg_list.segments[0];
            c->cur_hls = c->hls_stream[c->appoint_id];
            c->cur_stream_seq = c->appoint_id;
            c->cur_seq_num = 0;
        } else {
            int default_video_bw_stream_nb = 0;

            if (HLS_MODE_FAST != s->hls_start_mode)
            {
                default_video_bw_stream_nb = hlsGetDefaultIndex(c, (HLS_START_MODE_E)s->hls_start_mode);
            }
            else
            {
                default_video_bw_stream_nb = start_stream_num;
            }

            #if 1
            hls_stream_info_t *hls_tmp = c->hls_stream[default_video_bw_stream_nb];
            c->hls_stream[default_video_bw_stream_nb] = c->hls_stream[0];
            c->hls_stream[0] = hls_tmp;

            int64_t duration = 0;
            for (i = 0; i < c->hls_stream[0]->seg_list.hls_segment_nb; i++) {
                c->hls_stream[0]->seg_list.segments[i]->start_time = duration;
                duration += c->hls_stream[0]->seg_list.segments[i]->total_time;
            }
            default_video_bw_stream_nb = 0;
            #endif

            c->cur_seg = c->hls_stream[default_video_bw_stream_nb]->seg_list.segments[0];
            c->cur_hls = c->hls_stream[default_video_bw_stream_nb];
            c->cur_stream_seq = default_video_bw_stream_nb;
            c->cur_seq_num = 0;
        }
    }

    /* Open the demuxer for each variant */
    //for (i = 0; i < c->hls_stream_nb; i++) {
    for (i = 0; i < 1; i++) { //z00180556 only open one demuxer
        hls_stream_info_t *hls = c->hls_stream[i];
        AVInputFormat *in_fmt = NULL;
        struct ByteIOContext *pb = NULL;
        char bitrate_str[20];

        /* Get headers context */
        if (c && c->headers) {
            if (hls->seg_stream.headers) {
                av_freep(&hls->seg_stream.headers);
            }
            hls->seg_stream.headers = av_strdup(c->headers);
        }

        //if (uc)
        //{
        //    hls->seg_stream.userdata = uc->userdata;
        //}

        if (hls->seg_list.hls_segment_nb == 0)
            continue;

        ret = hlsOpenStream2(s, hls, i, &c->cur_seq_num);
        if (ret < 0) {
            goto fail;
        }
        c->cur_seg = c->cur_hls->seg_list.segments[c->cur_seq_num];
        /* sync with demux context */
        s->ctx_flags = hls->seg_demux.ctx->ctx_flags;
        /* if find stream number >= hls_find_stream_max_nb, avformat_find_stream_info could break quickly */
        s->hls_find_stream_max_nb = c->cur_hls->audio_codec + c->cur_hls->video_codec;
        stream_offset += hls->seg_demux.ctx->nb_streams;
    }

    for (i = 0; i < c->hls_stream_nb; i++) {
        c->hls_stream[i]->has_read = 0;
        c->hls_stream[i]->seg_list.hls_index = i;
    }

    /* open reditions after variant */
    for(j = 0; j < c->nb_reditions; j++) {
        hls_stream_info_t *rend = c->reditions[j];
        int cur_seg_no = 0;
        ret = hlsOpenStream2(c->parent, rend, j, &cur_seg_no);
        if (ret == 0) {
            av_log(c->parent, AV_LOG_INFO, "[%s,%d] open rendition[%d] return success!\n",
                __FILE_NAME__, __LINE__, j);
        } else {
            av_log(c->parent, AV_LOG_ERROR, "[%s,%d] open rendition[%d] return error=%d\n",
                __FILE_NAME__, __LINE__, j, ret);
        }
    }

    c->first_packet = 1;
    c->read_size = 0;
    c->read_time = 0;
    return 0;

fail:
    av_log(NULL, AV_LOG_ERROR, "[%s:%d], HLS_read_header fail\n", __FILE_NAME__, __LINE__);

    hlsFreeHlsList(c);

    if (c->headers) {
        av_free(c->headers);
        c->headers = NULL;
    }

    if (c->cookies) {
        av_free(c->cookies);
        c->cookies = NULL;
    }

    if (c->user_agent) {
        av_free(c->user_agent);
        c->user_agent = NULL;
    }

    if (c->referer) {
        av_free(c->referer);
        c->referer = NULL;
    }

    return ret;
}

/* changed: WARN:the stream of pkt must be the s->streams[pkt->stream_index] */
static void hls_make_pts_continous(AVFormatContext *s, AVPacket *pkt)
{
    HLSContext *c = s->priv_data;
    int64_t cur_time_stamp = AV_NOPTS_VALUE;
    int is_avpkt = 0;

    if (s->nb_streams <= 0 || pkt->stream_index >= s->nb_streams)
        return;

    if (s->streams[pkt->stream_index]->codec->codec_type == AVMEDIA_TYPE_AUDIO ||
        s->streams[pkt->stream_index]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
        is_avpkt = 1;
    }
    /*pts first*/
    cur_time_stamp = (pkt->pts != AV_NOPTS_VALUE)?pkt->pts:pkt->dts;
    if (cur_time_stamp != AV_NOPTS_VALUE && is_avpkt &&
        ((c->offset_stream_index >= 0 && pkt->stream_index == c->offset_stream_index) ||
         (c->offset_stream_index < 0))) {
        int64_t diff = 0, last_ts = c->last_timestamp;

        if (c->offset_stream_index >= 0 && c->last_timestamp != AV_NOPTS_VALUE) {
            diff     = c->last_timestamp - (cur_time_stamp + c->timestamp_offset);
            last_ts  = c->last_timestamp;
        } else if (c->seek_offset_us >= 0 &&
            s->streams[pkt->stream_index]->time_base.den > 0 && s->streams[pkt->stream_index]->time_base.num > 0) {
            last_ts = av_rescale_q(c->seek_offset_us, AV_TIME_BASE_Q, s->streams[pkt->stream_index]->time_base);
            diff    = last_ts - (cur_time_stamp + c->timestamp_offset);
        } else if (c->offset_stream_index < 0) {
            diff    = last_ts - (cur_time_stamp + c->timestamp_offset);
        }
        if (s->streams[pkt->stream_index]->time_base.den > 0 && s->streams[pkt->stream_index]->time_base.num > 0) {
            diff = av_rescale_q(diff, s->streams[pkt->stream_index]->time_base, AV_TIME_BASE_Q);
        }
        if ((c->cur_play_speed == 1.0 && llabs(diff) >= DISCONTINUE_MAX_US) ||
            (c->cur_play_speed != 1.0 && llabs(diff) >= IFRAME_ONLY_DISCONTINUE_MAX_US) ||
            (c->offset_stream_index < 0 && llabs(diff) > 0)) {
            if (c->nb_no_timetamp_pkts <= (llabs(diff)/AV_TIME_BASE) * 15) {/* 15 fps */
                c->timestamp_offset = last_ts - cur_time_stamp;
            }
            av_log(s, AV_LOG_ERROR, "[%s,%d] stream[%d] PTS DISCONTINUOUS(nb_no_timetamp_pkts=%d), last_ts:%lld(seek_off:%lld), cur pkt->pts:%lld, pkt->dts:%lld, diff:%lld, NEW PTS OFFSET:%lld\n",
                    __FUNCTION__, __LINE__, pkt->stream_index, c->nb_no_timetamp_pkts, last_ts, c->seek_offset_us, pkt->pts, pkt->dts, diff, c->timestamp_offset);
        }
    }

    if (pkt->dts != AV_NOPTS_VALUE) {
        pkt->dts += c->timestamp_offset;
        if (pkt->dts < 0) {
            pkt->dts = AV_NOPTS_VALUE;
        }
    }

    if (pkt->pts != AV_NOPTS_VALUE) {
        pkt->pts += c->timestamp_offset;
        if (pkt->pts < 0) {
            av_log(s, AV_LOG_ERROR, "[%s:%d]: invalid pts:%lld, timestamp_offset=%lld, seek_offset_us=%lld\n",
                __FUNCTION__,__LINE__, pkt->pts, c->timestamp_offset, c->seek_offset_us);
            pkt->pts = AV_NOPTS_VALUE;
        }
    }

    if ((pkt->stream_index == c->offset_stream_index || (is_avpkt && c->offset_stream_index < 0)) &&
         cur_time_stamp != AV_NOPTS_VALUE) {
        c->last_timestamp      = cur_time_stamp + c->timestamp_offset;
        c->offset_stream_index = pkt->stream_index;
    }

    /* record the number of pkts with invalid timestamp, the pkts must belong to only 1 stream. */
    if (pkt->stream_index == c->offset_stream_index ||
        (c->offset_stream_index < 0 && pkt->stream_index == 0)) {
        if (cur_time_stamp != AV_NOPTS_VALUE) {
            c->nb_no_timetamp_pkts = 0;
        } else {
            c->nb_no_timetamp_pkts ++;
        }
    }
}

static int hlsIsOfVariant(hls_stream_info_t *variant, hls_stream_info_t *rend)
{
    int i;

    if (!variant || !rend) {
        return 0;
    }
    if (variant->is_redition_stream || !rend->is_redition_stream) {
        av_log(0, AV_LOG_ERROR, "[%s,%d] variant or redition stream confused!\n",
            __FUNCTION__, __LINE__);
        return 0;
    }


    for (i = 0; i < variant->attr.v.nb_reditions; i++) {
        if (rend == variant->attr.v.reditions[i]) {
            return 1;
        }
    }

    return 0;
}

static int HLS_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    HLSContext *c = s->priv_data;
    hls_stream_info_t *min_hls = NULL;
    int ret, i;

    if (c->first_packet) {
        hlsRecheckDiscardFlags(s, 1);
        c->first_packet = 0;
    }

    if (c->reset_appoint_id) {
        av_log(s, AV_LOG_INFO, "[%s,%d] try to reset stream num to %d\n",
            __FUNCTION__, __LINE__, c->appoint_id);
        hlsCloseStream(c->hls_stream[0]);
        for (i = 0; i < c->hls_stream_nb; i++) {
            hls_stream_info_t* hls = c->hls_stream[i];
            hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start;
            if (!hls->seg_list.hls_finished && hls->seg_list.hls_segment_nb > 3) {
                //wKF34645 for live stream, if there are more than 3 segments in the list, only read the last 3 segments.
                hls->seg_list.hls_seg_cur =
                    hls->seg_list.hls_seg_start + hls->seg_list.hls_segment_nb - 3;
            }
        }
        if ((c->appoint_id >= 0) && (c->appoint_id < c->hls_stream_nb) &&
            (c->hls_stream[c->appoint_id]->seg_list.hls_segment_nb > 0)) {
            c->cur_seg = c->hls_stream[c->appoint_id]->seg_list.segments[0];
            c->cur_hls = c->hls_stream[c->appoint_id];
            c->cur_stream_seq = c->appoint_id;
            c->cur_seq_num = 0;
            av_log(s, AV_LOG_INFO, "[%s,%d] reset stream num to %d success\n",
                __FUNCTION__, __LINE__, c->appoint_id);
        } else {
            int default_video_bw_stream_nb = 0;

            if (HLS_MODE_FAST != s->hls_start_mode)
            {
                default_video_bw_stream_nb = hlsGetDefaultIndex(c, (HLS_START_MODE_E)s->hls_start_mode);
            }

            c->cur_seg = c->hls_stream[default_video_bw_stream_nb]->seg_list.segments[0];
            c->cur_hls = c->hls_stream[default_video_bw_stream_nb];
            c->cur_stream_seq = default_video_bw_stream_nb;
            c->cur_seq_num = 0;
        }

        if (!(c->hls_stream[0]->seg_demux.ctx = avformat_alloc_context())) {
            return AVERROR(ENOMEM);
        }
        ret = hlsOpenStream(c, c->hls_stream[0], &c->cur_seq_num);
        if (ret < 0) {
            av_log(s, AV_LOG_ERROR, "[%s,%d] hlsOpenStream return %d\n", __FILE_NAME__, __LINE__, ret);
            return ret;
        }
        c->cur_seg = c->cur_hls->seg_list.segments[c->cur_seq_num];
        c->hls_stream[0]->seg_demux.nb_streams = c->hls_stream[0]->seg_demux.ctx->nb_streams;
        c->reset_appoint_id = 0;
    }

start:
    c->segment_stream_eof = 0;
    //for (i = 0; i < c->hls_stream_nb; i++) {
    for (i = 0; i < 1; i++) {    //z00180556 Only use first list for playback
        hls_stream_info_t *hls = c->hls_stream[i];
        /* Make sure we've got one buffered packet from each open variant
         * stream */
        if (hls->seg_list.needed && !hls->seg_demux.pkt.data) {
            ret = av_read_frame(hls->seg_demux.ctx, &hls->seg_demux.pkt);
            if (ret < 0) {
                if (AVERROR(EAGAIN) != ret || !s->is_time_shift)
                {
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d] av_read_frame fail, ret = %d, AVEOF = 0x%x \m",
                        __FILE_NAME__, __LINE__, ret, AVERROR_EOF);
                }
                if (!url_feof(&hls->seg_stream.IO_pb)) {
                    if (AVERROR(EAGAIN) != ret || !s->is_time_shift)
                    {
                        av_log(NULL, AV_LOG_ERROR, "[%s:%d] read packet return fail, ret =%d, eof = 0x%x \n",
                            __FILE_NAME__, __LINE__, ret, AVERROR_EOF);
                    }
                    if (NULL != hls && !hls->seg_list.hls_finished) {
                        return AVERROR(EAGAIN);
                    }

                    return ret;
                }

                if (s->is_time_shift && AVERROR(EAGAIN) == ret)
                {
                    return ret;
                }

                hlsResetPacket(&hls->seg_demux.pkt);
            }

            if (hls->seg_demux.nb_streams < hls->seg_demux.ctx->nb_streams)
            {
                int j = 0;
                for (j = hls->seg_demux.nb_streams; j < hls->seg_demux.ctx->nb_streams; j++) {
                    AVStream *st = av_new_stream(s, i);
                    if (!st) {
                        ret = AVERROR(ENOMEM);
                        av_log(NULL, AV_LOG_ERROR, "[%s:%d] ENOMEM", __FILE_NAME__, __LINE__);
                        return ret;
                    }
                    hls->seg_demux.nb_streams ++;
                    avcodec_copy_context(st->codec, hls->seg_demux.ctx->streams[j]->codec);
                    av_log(NULL, AV_LOG_INFO, "[%s:%d] number of streams changed,add stream:%d codec_type:%d",
                        __FILE_NAME__, __LINE__, j, st->codec->codec_type);
                }
            }
            //notice: st_main->id is invalid, always is 0.
            AVStream *st_seg = NULL, *st_main = NULL;
            st_seg = hls->seg_demux.ctx->streams[hls->seg_demux.pkt.stream_index];
            st_main = s->streams[hls->seg_demux.pkt.stream_index];
            hlsUpdateStreamCodecInfo(st_main, st_seg);
        }

        /* Check if this stream has the packet with the lowest dts */
        if (hls->seg_demux.pkt.data) {
            if (!min_hls ||
                hls->seg_demux.pkt.dts < min_hls->seg_demux.pkt.dts)
                min_hls = hls;
        }
    }

    /* read from reditions */
    for (i = 0; i < c->nb_reditions; i++) {
        hls_stream_info_t *rend = c->reditions[i];
        if (!rend->seg_list.needed || !hlsIsOfVariant(c->cur_hls, rend)) {
            if (rend->seg_demux.pkt.data) {
                av_free_packet(&rend->seg_demux.pkt);
                hlsResetPacket(&rend->seg_demux.pkt);
            }
            continue;
        }

        if (!rend->seg_demux.pkt.data) {
            AVStream *st_seg = NULL, *st_main = NULL;
            while (1) {
                ret = av_read_frame(rend->seg_demux.ctx, &rend->seg_demux.pkt);
                if (ret < 0) {
                    if (!url_feof(&rend->seg_stream.IO_pb) && ret != AVERROR_EOF) {
                        av_log(s, AV_LOG_ERROR, "[%s:%d] rend[%d] av_read_frame fail, ret = %d, AVEOF = 0x%x \n",
                            __FILE_NAME__, __LINE__, i, ret, AVERROR_EOF);
                        return ret;
                    }
                    hlsResetPacket(&rend->seg_demux.pkt);
                } else {
                    st_seg = rend->seg_demux.ctx->streams[rend->seg_demux.pkt.stream_index];
                    st_main = s->streams[rend->seg_demux.pkt.stream_index + rend->seg_list.hls_stream_offset];
                    hlsUpdateStreamCodecInfo(st_main, st_seg);
                }
                break;
            }
        }

        if (rend->seg_demux.pkt.data) {
            if (!min_hls ||
                rend->seg_demux.pkt.dts < min_hls->seg_demux.pkt.dts)
                min_hls = rend;
        }
    }

    if (c->segment_stream_eof) {
        if (hlsRecheckDiscardFlags(s, 0))
            goto start;
    }
    /* If we got a packet, return it */
    if (min_hls) {
        *pkt = min_hls->seg_demux.pkt;
        pkt->stream_index += min_hls->seg_list.hls_stream_offset;
        hls_make_pts_continous(s, pkt);
        hlsResetPacket(&min_hls->seg_demux.pkt);
        //av_log(s, AV_LOG_INFO, "[%s,%d] redition?(%d)[%d] st[%d] pts=%lld, dts=%lld, size=%d\n",
        //    __FUNCTION__, __LINE__, min_hls->is_redition_stream, min_hls->seg_list.hls_index,
         //   pkt->stream_index, pkt->pts, pkt->dts, pkt->size);
        return 0;
    } else {
        hls_stream_info_t *hls = c->hls_stream[0];
        if (NULL != hls && !hls->seg_list.hls_finished) {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] read_frame fail, but is live stream, close current stream, return eagain \n",
                __FILE_NAME__, __LINE__);
            if (hls->seg_stream.input) {
                hls_close(hls->seg_stream.input);
                hls->seg_stream.input  = NULL;
                hls->seg_stream.offset = 0;
            }
            for (i = 0; i < c->nb_reditions; i++) {
                hls_stream_info_t *rend = c->reditions[i];
                if (rend->seg_stream.input) {
                    hls_close(rend->seg_stream.input);
                    rend->seg_stream.input  = NULL;
                    rend->seg_stream.offset = 0;
                }
            }
            return AVERROR(EAGAIN);
        }
    }

    av_log(NULL, AV_LOG_ERROR, "[%s:%d] read packet return eof \n", __FILE_NAME__, __LINE__);

    return AVERROR_EOF;
}

static int HLS_close(AVFormatContext *s)
{
    HLSContext *c = s->priv_data;

    if(s->pb && s->pb->downspeedable)
    {
        s->pb->downspeedable = 0;
        DownSpeed *downspeed = &(s->pb->downspeed);
        downspeed->down_size = 0;
        downspeed->down_time = 0;
        downspeed->speed = 0;
        DownNode *node = NULL;
        while(downspeed->head)
        {
            node = downspeed->head;
            downspeed->head = downspeed->head->next;
            av_free(node);
        }
        downspeed->head = NULL;
        downspeed->tail = NULL;
    }

    hlsFreeHlsList(c);

    if (c->headers) {
        av_free(c->headers);
        c->headers = NULL;
    }

    if (c->cookies) {
        av_free(c->cookies);
        c->cookies = NULL;
    }

    if (c->user_agent) {
        av_free(c->user_agent);
        c->user_agent = NULL;
    }

    if (c->referer) {
        av_free(c->referer);
        c->referer = NULL;
    }

    if (NULL !=c && c->downspeed.head)
    {
        DownNode *node = NULL;
        DownSpeed *downspeed = &(c->downspeed);
        while(downspeed->head)
        {
            node = downspeed->head;
            downspeed->head = downspeed->head->next;
            av_free(node);
        }
        downspeed->head = NULL;
        downspeed->tail = NULL;
    }

    if (c->mufp)
    {
        fclose(c->mufp);
        c->mufp = NULL;
    }

    if (c->tsfp)
    {
        fclose(c->tsfp);
        c->tsfp = NULL;
    }

    return 0;
}

static int HLS_read_seek(AVFormatContext *s, int stream_index,
                               int64_t timestamp, int flags)
{
    HLSContext *c = s->priv_data;
    int i, j, k, ret;
    int variant_seek_seq = 0;
    int seek_beyond_end = 0;

    if ((flags & AVSEEK_FLAG_BYTE)/* || !c->hls_stream[0]->seg_list.hls_finished*/)
        return AVERROR(ENOSYS);

    timestamp = av_rescale_rnd(timestamp, 1000, stream_index >= 0 ?
                               s->streams[stream_index]->time_base.den :
                               AV_TIME_BASE, flags & AVSEEK_FLAG_BACKWARD ?
                               AV_ROUND_DOWN : AV_ROUND_UP);
    ret = AVERROR(EIO);

    char *servicetype = NULL;
    servicetype = strstr(s->filename, "servicetype=2");
    if (NULL == servicetype) {
        /* '=' need to be transferred from '%3D' */
        servicetype = strstr(s->filename, "servicetype%3D2");
    }

    //for (i = 0; i < c->hls_stream_nb; i++) {
    for (i = 0; i < 1; i++) {    //z00180556 Only use first list for playback and seek
        /* Reset reading */
        hls_stream_info_t *hls = c->hls_stream[i];
        int64_t pos = 0;

        hls->sof = 0;
        av_free_packet(&hls->seg_demux.pkt);
        hlsResetPacket(&hls->seg_demux.pkt);
        hlsCloseInput(hls);
        hls->seg_stream.IO_pb.eof_reached = 0;
        hls->seg_stream.IO_pb.pos = 0;
        hls->seg_stream.IO_pb.buf_ptr = hls->seg_stream.IO_pb.buf_end = hls->seg_stream.IO_pb.buffer;
       // timestamp *= 1000;

        c->seek_offset_us      = 0;
        /* Locate the segment that contains the target timestamp */
        if (NULL == servicetype) {
            for (j = 0; j < hls->seg_list.hls_segment_nb; j++) {
                if (timestamp >= pos &&
                    timestamp < pos + hls->seg_list.segments[j]->total_time) {
                    variant_seek_seq = j;
                    hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start + j;
                    c->timestamp_offset    = 0;
                    c->offset_stream_index = -1;
                    c->seek_offset_us      = pos*1000LL;
                    c->last_timestamp      = 0;
                    c->nb_no_timetamp_pkts = 0;
                    av_log(s, AV_LOG_ERROR, "[%s,%d] next pts will start at %lld us(seek_timestamp=%lld) for seeking ,seq_no=%d\n",
                            __FUNCTION__, __LINE__, c->seek_offset_us, timestamp, j);
                    //c->cur_seg=hls->seg_list.segments[j];
                    //c->cur_hls=hls;
                    ret = 0;
                    break;
                }
                pos += hls->seg_list.segments[j]->total_time;
            }
        }
        else
        {
            ret = hlsParseM3U8(c, hls->url, hls, NULL);
            av_log(s, AV_LOG_ERROR, "[%s:%d] end start time = %lld \n", __FUNCTION__, __LINE__,
                hls->seg_list.segments[hls->seg_list.hls_segment_nb - 1]->start_time);

            for (j = hls->seg_list.hls_segment_nb - 1; j >= 0; j--) {
                if (timestamp >= pos &&
                    timestamp < pos + hls->seg_list.segments[j]->total_time) {
                    hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start + j;
                    variant_seek_seq = j;
                    c->timestamp_offset    = 0;
                    c->offset_stream_index = -1;
                    c->seek_offset_us      = 1000000LL * (hls->seg_list.segments[j]->program_time - c->timeshift_start_program_time);
                    c->last_timestamp      = 0;
                    c->nb_no_timetamp_pkts = 0;
                    av_log(s, AV_LOG_ERROR, "[%s:%d] program time = %ld, start program time = %ld, next pts will start"
                        " at %lld us (seek_timestamp=%lld) for seeking, seq_no=%d \n",
                            __FUNCTION__,__LINE__,
                            hls->seg_list.segments[j]->program_time,
                            c->timeshift_start_program_time,
                            c->seek_offset_us, timestamp, j);
                    //c->cur_seg=hls->seg_list.segments[j];
                    //c->cur_hls=hls;
                    ret = 0;
                    break;
                }
                pos += hls->seg_list.segments[j]->total_time;
            }
        }

        if (ret) {
            if (timestamp >= pos && j == hls->seg_list.hls_segment_nb) {
                j = hls->seg_list.hls_segment_nb;
                av_log(s, AV_LOG_INFO, "seek exceed last seg number %d ", j);
                hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start + j;
                c->cur_seg = NULL;
                c->cur_seq_num = j;
                variant_seek_seq = j;
                ff_read_frame_flush(hls->seg_demux.ctx);
                c->timestamp_offset    = 0;
                c->offset_stream_index = -1;
                c->seek_offset_us      = pos*1000LL;
                c->last_timestamp      = 0;
                c->nb_no_timetamp_pkts = 0;
                seek_beyond_end = 1;
                av_log(s, AV_LOG_ERROR, "[%s,%d] next pts will start at %lld us(seek_timestamp=%lld) for seeking ,seq_no=%d\n",
                        __FUNCTION__, __LINE__, c->seek_offset_us, timestamp, j);
               // return 0;// return after seek reditions
            }
        }

        ff_read_frame_flush(hls->seg_demux.ctx);
    }

    /* WARN: the iframe stream's segment number may be not the same as main stream,
       refer to http://10.157.186.83/4KTest/17M/04_m3u8/iframe/entire.m3u8 */
    for (i = 1; i < c->hls_stream_nb; i++) {
        hls_stream_info_t *hls = c->hls_stream[i];
        int64_t pos = 0;
        if (!hls->iframe_only) {
            continue;
        }
        for (j = 0; j < hls->seg_list.hls_segment_nb; j++) {
            if (timestamp >= pos &&
                timestamp < pos + hls->seg_list.segments[j]->total_time) {
                hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start + j;
                if (c->cur_hls == hls && NULL == servicetype) {
                    c->seek_offset_us      = pos*1000LL;
                } else if (c->cur_hls == hls) {
                    c->seek_offset_us      = 1000000LL * (hls->seg_list.segments[j]->program_time - c->timeshift_start_program_time);
                }
                av_log(s, AV_LOG_ERROR, "[%s,%d] hls iframe stream[%d] seek to seq_no=%d for timestamp=%lld\n",
                        __FUNCTION__, __LINE__, i, j, timestamp);
                break;
            }
            pos += hls->seg_list.segments[j]->total_time;
        }
        if (j >= hls->seg_list.hls_segment_nb) {
           hls->seg_list.hls_seg_cur = hls->seg_list.hls_seg_start + hls->seg_list.hls_segment_nb;
           if (c->cur_hls == hls && NULL == servicetype) {
               c->seek_offset_us = pos*1000LL;
           } else if (c->cur_hls == hls) {
               c->seek_offset_us = 1000000LL * (hls->seg_list.segments[j - 1]->program_time \
                + hls->seg_list.segments[j - 1]->total_time/1000 - c->timeshift_start_program_time);
           }
        }
        if (c->cur_hls == hls &&
            c->hls_stream[0]->seg_list.hls_seg_cur != c->cur_hls->seg_list.hls_seg_cur) {
            av_log(s, AV_LOG_WARNING, "[%s,%d] set hls_seg_cur(%d->%d)\n",
                __FUNCTION__, __LINE__, c->hls_stream[0]->seg_list.hls_seg_cur, c->cur_hls->seg_list.hls_seg_cur);
            c->hls_stream[0]->seg_list.hls_seg_cur = c->cur_hls->seg_list.hls_seg_cur;
            if (c->cur_hls->seg_list.hls_seg_cur - c->cur_hls->seg_list.hls_seg_start < \
                c->cur_hls->seg_list.hls_segment_nb) {
                variant_seek_seq = c->cur_hls->seg_list.hls_seg_cur - c->cur_hls->seg_list.hls_seg_start;
            } else {
                variant_seek_seq = c->cur_hls->seg_list.hls_segment_nb - 1;
            }

        }
    }

    /* seek reditions */
    for (i = 0; i < c->nb_reditions; i++) {
        /* Reset reading */
        hls_stream_info_t *rend = c->reditions[i];
        int64_t pos = 0;
        j = 0;
        rend->sof = 0;
        av_free_packet(&rend->seg_demux.pkt);
        hlsResetPacket(&rend->seg_demux.pkt);
        hlsCloseInput(rend);
        rend->seg_stream.IO_pb.eof_reached = 0;
        rend->seg_stream.IO_pb.pos = 0;
        rend->seg_stream.IO_pb.buf_ptr = rend->seg_stream.IO_pb.buf_end = rend->seg_stream.IO_pb.buffer;
        ff_read_frame_flush(rend->seg_demux.ctx);
        if (!servicetype) {
            for (j = 0; j < rend->seg_list.hls_segment_nb; j++) {
                if (timestamp >= pos &&
                    timestamp < pos + rend->seg_list.segments[j]->total_time) {
                    rend->seg_list.hls_seg_cur = rend->seg_list.hls_seg_start + j;
                    av_log(s, AV_LOG_INFO, "[%s:%d] rend[%d] seek to hls_seg_cur=%d(j=%d)\n",
                            __FUNCTION__,__LINE__, i, rend->seg_list.hls_seg_cur, j);
                    break;
                }
                pos += rend->seg_list.segments[j]->total_time;
            }
        } else {
            hlsParseM3U8(c, rend->url, rend, NULL);
            for (j = rend->seg_list.hls_segment_nb - 1; j >= 0; j--) {
                if (timestamp >= pos &&
                    timestamp < pos + rend->seg_list.segments[j]->total_time) {
                    rend->seg_list.hls_seg_cur = rend->seg_list.hls_seg_start + j;
                    av_log(s, AV_LOG_INFO, "[%s:%d] rend[%d] service seek to hls_seg_cur=%d\n",
                            __FUNCTION__,__LINE__, i, rend->seg_list.hls_seg_cur);
                    break;
                }
                pos += rend->seg_list.segments[j]->total_time;
            }
        }
        if (j >= rend->seg_list.hls_segment_nb || j <0) {
            if (timestamp >= pos && j >= rend->seg_list.hls_segment_nb) {
                rend->seg_list.hls_seg_cur = rend->seg_list.hls_seg_start + rend->seg_list.hls_segment_nb;
            } else {
                rend->seg_list.hls_seg_cur = rend->seg_list.hls_seg_start;
            }
            av_log(s, AV_LOG_INFO, "[%s:%d] rend[%d] service seek to timestamp=%lld beyond the end! set hls_seg_cur=%d\n",
                    __FUNCTION__,__LINE__, j, timestamp, rend->seg_list.hls_seg_cur);
        }
    }

    if (seek_beyond_end) {
        return 0;
    }

    /*
    int stream_id = 0;
    if((c->appoint_id >= 0)
            && (c->hls_stream[c->appoint_id]->seg_list.hls_segment_nb > j))
    {
        stream_id = c->appoint_id;
    }
    else
    {
        stream_id = 0;
        for(i = 1; i < c->hls_stream_nb; i++)
        {
            if((c->hls_stream[i]->bandwidth < c->hls_stream[stream_id]->bandwidth)
                    && (c->hls_stream[i]->seg_list.hls_segment_nb > j))
            {
                stream_id = i;
            }
        }
    }
    */

    if(!ret) {
        hls_stream_info_t *hls = c->hls_stream[c->cur_stream_seq];
        c->cur_seg = hls->seg_list.segments[variant_seek_seq];
        c->cur_hls = hls;
        //c->cur_stream_seq = stream_id;
        c->cur_seq_num = variant_seek_seq;
    }

    return ret;
}

static int has_iframe_variant(HLSContext *c)
{
    int i;

    for (i = 0; i < c->hls_stream_nb; i++) {
        if (c->hls_stream[i]->iframe_only) {
            return 1;
        }
    }

    return 0;
}

static int hls_change_play_speed(struct AVFormatContext *s, float speed)
{
    HLSContext *c = s->priv_data;;
    float cur_play_speed = c->cur_play_speed;

    if (!has_iframe_variant(c) || s->is_live_stream) {
        av_log(s, AV_LOG_ERROR, "[%s,%d] user set play speed=%f error, "
            "is_live_stream=%d(or no iframe-only variant)\n",
          __FUNCTION__, __LINE__, speed, s->is_live_stream);
        return -1;
    }

    if (speed == 0.0) {
        speed = 1.0;
    }

    /* ff/bw->play or play->ff/bw */
    if (c->cur_play_speed != speed &&
       (c->cur_play_speed == 1.0 || speed == 1.0)) {
        int i, min_nb, flags = 0, ret;
        int64_t pos = 0, seek_ts;
        hls_stream_info_t *old_hls = NULL;
        if (s->nb_streams <= 0 || !c->cur_hls) {
            av_log(s, AV_LOG_ERROR, "[%s,%d] user set play speed=%f error, invalid cur_hls "
                "or no streams\n", __FUNCTION__, __LINE__, speed);
            return -1;
        }
        if (c->cur_hls->seg_list.hls_segment_nb <= 0) {
            av_log(s, AV_LOG_ERROR, "[%s,%d] user set play speed=%f error, no segment in variant=%d\n",
                __FUNCTION__, __LINE__, speed, c->cur_hls->seg_list.hls_index);
            return -1;
        }
        /* 1, compute current variant's position, used as seek timestamp */
        min_nb = FFMIN(c->cur_hls->seg_list.hls_segment_nb, \
            (c->hls_stream[0]->seg_list.hls_seg_cur - c->hls_stream[0]->seg_list.hls_seg_start + 1));
        for (i = 0; i < min_nb; i++) {
            pos += c->cur_hls->seg_list.segments[i]->total_time;
        }
        flags = (speed < 0?AVSEEK_FLAG_BACKWARD:0);
        seek_ts = av_rescale_rnd((pos*1000LL), s->streams[0]->time_base.den,
            AV_TIME_BASE, (flags & AVSEEK_FLAG_BACKWARD ?AV_ROUND_DOWN : AV_ROUND_UP));

        /* 2, WARN:switch variant:set @cur_play_speed before call select_bandwidth() */
        c->cur_play_speed = speed;
        old_hls = c->cur_hls;
        hlsCheckSwitchVariant(c);
        av_log(s, AV_LOG_INFO, "[%s,%d] play speed changed(%f->%f),variant:%d->%d(iframe_only:%d)\n",
            __FUNCTION__, __LINE__, cur_play_speed, c->cur_play_speed, old_hls?old_hls->seg_list.hls_index:-1,
            c->cur_hls?c->cur_hls->seg_list.hls_index:-1, c->cur_hls?c->cur_hls->iframe_only:-1);
        /* 3, seek at last */
        ret = HLS_read_seek(s, 0, seek_ts, flags);
        if (ret < 0) {
            /* not sure how to process it */
            av_log(s, AV_LOG_ERROR, "[%s,%d] play speed(%f->%f), hls_read_seek(%lld, seq=%d) return error=%d\n",
                __FUNCTION__, __LINE__, cur_play_speed, speed, seek_ts, min_nb - 1, ret);
        } else {
            av_log(s, AV_LOG_INFO, "[%s,%d] play speed(%f->%f), hls_read_seek(%lld, seq=%d) return %d\n",
                __FUNCTION__, __LINE__, cur_play_speed, speed, seek_ts, i, ret);
        }
        return 0;
    }else if (c->cur_play_speed != speed) {
        c->cur_play_speed = speed;
        av_log(s, AV_LOG_INFO, "[%s,%d] play speed(%f->%f)\n",
            __FUNCTION__, __LINE__, cur_play_speed, c->cur_play_speed);
    }

    return 0;
}

static int HLS_invoke(struct AVFormatContext *s, AVFormatInvokeID invoke_id, void *arg)
{
    HLSContext *c;

    if (!s) {
        return -1;
    }

    c = s->priv_data;

    if (invoke_id == AVFORMAT_INVOKE_SET_PLAY_SPEED) {
        if (!arg) {
            return -1;
        }
        return hls_change_play_speed(s, *((float *)arg));
    } else if (invoke_id == AVFORMAT_INVOKE_GET_TPLAY_SUPPORT) {
        int *support = (int *)arg;
        if (!arg) {
            return -1;
        }
        if (has_iframe_variant(c) && !s->is_live_stream) {
            *support = 1;
        } else {
            *support = 0;
        }
        return 0;
    }

    return -1;
}

/*******************************************************************************
 * HLS demuxer module descriptor
 ******************************************************************************/
const AVClass hls_demuxer_class = {
    .class_name     = "hls demuxer",
    .item_name      = av_default_item_name,
    .option         = ff_hls_options,
    .version        = LIBAVUTIL_VERSION_INT,
};

AVInputFormat ff_hls_demuxer = {
    .name = "hls",
    .long_name = NULL, //NULL_IF_CONFIG_SMALL("Apple HTTP Live Streaming format"),
    .priv_data_size = sizeof(HLSContext),
    .read_probe = HLS_probe,
    .read_header = HLS_read_header,
    .read_packet = HLS_read_packet,
    .read_close = HLS_close,
    .read_seek = HLS_read_seek,
    .invoke    = HLS_invoke,
    .priv_class = &hls_demuxer_class,
};
