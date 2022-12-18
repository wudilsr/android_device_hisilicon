/*
 * RTSP demuxer
 * Copyright (c) 2002 Fabrice Bellard
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

#include "libavutil/avstring.h"
#include "libavutil/intreadwrite.h"
#include "libavutil/mathematics.h"
#include "libavutil/internal.h"
#include "avformat.h"

#include "libavformat/internal.h"
#include "libavformat/network.h"
#include "libavformat/os_support.h"
#include "rtsp.h"
#include "rdt.h"
#include "url.h"
#include <unistd.h>
#include <time.h>
#include <time64.h>
#if defined (ANDROID_VERSION)
#include <cutils/properties.h>
#endif

static void get_downspeed(AVFormatContext *s, int len, int64_t time)
{
    if (len < 0)
    {
        return;
    }
    AVIOContext *pb = s->pb;
    RTSPState *rt = s->priv_data;
    if (NULL == pb)
        return;
    DownSpeed *downspeed = &(pb->downspeed);
    if (NULL == downspeed)
        return;
    if(pb->downspeedable == 0)
    {
        pb->downspeedable = 1;
        downspeed->down_size = 0;
        downspeed->down_time = 0;
        downspeed->speed = 0;
        downspeed->head = NULL;
        downspeed->tail = NULL;
    }

    DownNode *node = av_malloc(sizeof(DownNode));
    if(NULL == node)
        return;

    node->down_size = len;
    node->down_time = time;
    node->next = NULL;
    if(NULL == downspeed->head)
    {
        downspeed->head = node;
        downspeed->tail = node;
        downspeed->down_size = node->down_size;
        downspeed->down_time = node->down_time;
    }
    else
    {
        downspeed->tail->next = node;
        downspeed->tail = node;
        downspeed->down_size += node->down_size;
        downspeed->down_time += node->down_time;
    }

    while(SPEED_SIZE < downspeed->down_size)
    {
        node = downspeed->head;
        downspeed->head = downspeed->head->next;
        downspeed->down_size -= node->down_size;
        downspeed->down_time -= node->down_time;
        av_free(node);
        node = NULL;
    }

    if (rt->download_speed_collect_freq_ms > 0)
    {
        if (0 == rt->last_get_speed_time)
        {
            rt->last_get_speed_time = av_gettime();
        }

        if (rt->download_speed_collect_freq_ms * 1000 > (av_gettime() - rt->last_get_speed_time))
        {
            return;
        }
    }

    if(downspeed->down_time != 0)
    {
        downspeed->speed = (downspeed->down_size *8000000)/downspeed->down_time;
        downspeed->speed = downspeed->speed*8/10;
        rt->last_get_speed_time = av_gettime();
    }
}

static void reset_downspeed(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    if (NULL == pb)
        return;
    DownSpeed *downspeed = &(pb->downspeed);

    if (NULL == downspeed)
        return;
    downspeed->down_size = 0;
    downspeed->down_time = 0;
    downspeed->speed = 0;
    DownNode *node = NULL;

    while(NULL != downspeed->head)
    {
        node = downspeed->head;
        downspeed->head = downspeed->head->next;
        av_free(node);
    }
    downspeed->head = NULL;
    downspeed->tail = NULL;
}

static int rtsp_read_play(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;
    RTSPMessageHeader reply1, *reply = &reply1;
    int i;
    char cmd[1024];

    av_log(s, AV_LOG_DEBUG, "hello state=%d\n", rt->state);
    rt->nb_byes = 0;

#if HAVE_UDP_RCV_THREAD
    if (rt->rtp_queue)
        pktq_clear(rt->rtp_queue);
#endif
    if (!(rt->server_type == RTSP_SERVER_REAL && rt->need_subscription)) {
        if (rt->transport == RTSP_TRANSPORT_RTP) {
            for (i = 0; i < rt->nb_rtsp_streams; i++) {
                RTSPStream *rtsp_st = rt->rtsp_streams[i];
                RTPDemuxContext *rtpctx = rtsp_st->transport_priv;
                if (!rtpctx)
                    continue;
                ff_rtp_reset_packet_queue(rtpctx);
                rtpctx->last_rtcp_ntp_time  = AV_NOPTS_VALUE;
                rtpctx->first_rtcp_ntp_time = AV_NOPTS_VALUE;
                rtpctx->base_timestamp      = 0;
                rtpctx->timestamp           = 0;
                rtpctx->unwrapped_timestamp = 0;
                rtpctx->rtcp_ts_offset      = 0;
            }
            ff_rtsp_reset_demux(s);
        }

        if (rt->state == RTSP_STATE_PAUSED) {
            cmd[0] = 0;
        } else {
            int len;
            /* Range: clock=19961108T142300Z-19961108T143520Z */
            if (rt->seek_timestamp.type == RTSP_CLOCK_UTC) {
                len = snprintf(cmd, sizeof(cmd), "Range: clock=%04d%02d%02dT%02d%02d%02dZ-",
                    rt->seek_timestamp.time.utc.year, rt->seek_timestamp.time.utc.mon,
                    rt->seek_timestamp.time.utc.day, rt->seek_timestamp.time.utc.hour,
                    rt->seek_timestamp.time.utc.min, rt->seek_timestamp.time.utc.second);
                if (rt->seek_end_timestamp.type == RTSP_CLOCK_UTC) {
                    len += snprintf(cmd + len, sizeof(cmd) - len, "%04d%02d%02dT%02d%02d%02dZ",
                        rt->seek_end_timestamp.time.utc.year, rt->seek_end_timestamp.time.utc.mon,
                        rt->seek_end_timestamp.time.utc.day, rt->seek_end_timestamp.time.utc.hour,
                        rt->seek_end_timestamp.time.utc.min, rt->seek_end_timestamp.time.utc.second);
                }
            } else {
                len = snprintf(cmd, sizeof(cmd), "Range: npt=%0.02lf-", rt->seek_timestamp.time.npt);
                if (rt->seek_end_timestamp.type == RTSP_CLOCK_NPT) {
                    len += snprintf(cmd + len, sizeof(cmd) - len, "%0.02lf", rt->seek_timestamp.time.npt);
                }
            }
            len += snprintf(cmd + len, sizeof(cmd) - len, "\r\n");
            av_log(s, AV_LOG_INFO, "[%s,%d] seek range='%s'\n", __FUNCTION__, __LINE__, cmd);
        }
        ff_rtsp_send_cmd(s, "PLAY", rt->control_uri, cmd, reply, NULL);
        if (reply->status_code != RTSP_STATUS_OK) {
            return -1;
        }
        if (rt->transport == RTSP_TRANSPORT_RTP &&
            reply->range_start != AV_NOPTS_VALUE) {
            for (i = 0; i < rt->nb_rtsp_streams; i++) {
                RTSPStream *rtsp_st = rt->rtsp_streams[i];
                RTPDemuxContext *rtpctx = rtsp_st->transport_priv;
                AVStream *st = NULL;
                if (!rtpctx || rtsp_st->stream_index < 0)
                    continue;
                st = s->streams[rtsp_st->stream_index];
                rtpctx->range_start_offset =
                    av_rescale_q(reply->range_start, AV_TIME_BASE_Q,
                                 st->time_base);
            }
        }
    }
    rt->state = RTSP_STATE_STREAMING;
    return 0;
}

/* pause the stream */
static int rtsp_read_pause(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;
    RTSPMessageHeader reply1, *reply = &reply1;

    if (rt->state != RTSP_STATE_STREAMING)
        return 0;
    else if (!(rt->server_type == RTSP_SERVER_REAL && rt->need_subscription)) {
        ff_rtsp_send_cmd(s, "PAUSE", rt->control_uri, NULL, reply, NULL);
        if (reply->status_code != RTSP_STATUS_OK) {
            return -1;
        }
    }
    rt->state = RTSP_STATE_PAUSED;
    return 0;
}

int ff_rtsp_setup_input_streams(AVFormatContext *s, RTSPMessageHeader *reply)
{
    RTSPState *rt = s->priv_data;
    char cmd[1024];
    unsigned char *content = NULL;
    int ret = -1;

    /* describe the stream */
    snprintf(cmd, sizeof(cmd),
             "Accept: application/sdp\r\n");
    if (rt->server_type == RTSP_SERVER_REAL) {
        /**
         * The Require: attribute is needed for proper streaming from
         * Realmedia servers.
         */
        av_strlcat(cmd,
                   "Require: com.real.retain-entity-for-setup\r\n",
                   sizeof(cmd));
    }
    ff_rtsp_send_cmd(s, "DESCRIBE", rt->control_uri, cmd, reply, &content);
    if (!content)
        return AVERROR_INVALIDDATA;
    if (reply->status_code != RTSP_STATUS_OK) {
        av_freep(&content);
        return AVERROR_INVALIDDATA;
    }

    av_log(s, AV_LOG_VERBOSE, "SDP:\n%s\n", content);
    /* now we got the SDP description, we parse it */
    if (!rt->reconnecting) {
        ret = ff_sdp_parse(s, (const char *)content);
    } else {
        ret = 0;
    }
    av_freep(&content);
    if (ret < 0)
        return ret;

    return 0;
}

static int rtsp_probe(AVProbeData *p)
{
    if (av_strstart(p->filename, "rtsp:", NULL))
        return AVPROBE_SCORE_MAX;
    return 0;
}

#if HAVE_UDP_RCV_THREAD

int create_udp_recv_thread(AVFormatContext *s);
int destroy_udp_recv_thread(AVFormatContext *s);
#endif

static inline const char *skip_space(const char *buf)
{
    while (*buf == ' ' || *buf == '\t')
        buf++;
    return buf;
}

static int parse_utc_range(const char *headers, RTSPUTCTime *start, RTSPUTCTime *end)
{
    const char *p;
    int ret, n = 0;
    int year = -1, month = -1, day = -1, hour = -1, min = -1, second = -1;
    RTSPUTCTime *target = start;

    if (!headers || !start) {
        return -1;
    }

    p = strstr(headers, "Range:");
    if (!p) {
        return -1;
    }
    av_log(NULL, AV_LOG_INFO, "[%s,%d] headers='%s'\n", __FUNCTION__, __LINE__, headers);
    p += strlen("Range:");
    p = skip_space(p);
    if (!av_stristart(p, "clock", &p)) {
        av_log(NULL, AV_LOG_INFO, "[%s,%d] clock not found!\n", __FUNCTION__, __LINE__);
        return -1;
    }
    p = skip_space(p);
    if (*p != '=') {
        av_log(NULL, AV_LOG_INFO, "[%s,%d] '=' not found!\n", __FUNCTION__, __LINE__);
        return -1;
    }
    p ++;
    p = skip_space(p);

NEXT:
    year  = -1;
    month = -1;
    day   = -1;
    hour  = -1;
    min   = -1;
    second = -1;
    ret = sscanf(p, "%4d%2d%2dT%2d%2d%2dZ", &year, &month, &day, &hour, &min, &second);
    av_log(NULL, AV_LOG_INFO, "[%s,%d] ret=%d, year=%d, month=%d, day=%d, hour=%d, min=%d, second=%d\n",
        __FUNCTION__, __LINE__, ret, year, month, day, hour, min, second);
    if (ret < 6) {
        return -1;
    }
    n ++;
    target->year = year;
    target->mon  = month;
    target->day  = day;
    target->hour = hour;
    target->min  = min;
    target->second = second;
    p = strchr(p, '-');
    if (!p) {
        return n;
    }
    p ++;
    p = skip_space(p);
    if (end && target != end && *p != '\r' && *p != '\n') {
        target = end;
        goto NEXT;
    }

    return n;
}

static int rtsp_read_header(AVFormatContext *s,
                            AVFormatParameters *ap)
{
    RTSPState *rt = s->priv_data;
    int ret;
#if defined (ANDROID_VERSION)
    char prefer_tcp_str[PROP_VALUE_MAX];

    if (property_get("persist.sys.hiplayer.rtspusetcp", prefer_tcp_str, "false")) {
        if (!strcmp(prefer_tcp_str, "true")) {
            rt->rtsp_flags |= RTSP_FLAG_PREFER_TCP;
            av_log(s, AV_LOG_INFO, "[%s,%d] perfer_tcp=true\n", __FUNCTION__, __LINE__);
        } else {
            av_log(s, AV_LOG_INFO, "[%s,%d] perfer_tcp=false\n", __FUNCTION__, __LINE__);
        }
    }
#endif

    rt->lower_transport_mask_bak = rt->lower_transport_mask;
    rt->seek_timestamp.type     = RTSP_CLOCK_NPT;
    rt->seek_end_timestamp.type = RTSP_CLOCK_NONE;
    ret = parse_utc_range(rt->headers, &rt->seek_timestamp.time.utc, &rt->seek_end_timestamp.time.utc);
    if (ret >= 1) {
        rt->seek_timestamp.type = RTSP_CLOCK_UTC;
        if (ret >= 2) {
            rt->seek_end_timestamp.type = RTSP_CLOCK_UTC;
        }
    }

    ret = ff_rtsp_connect(s);
    if (ret) {
        if (AVERROR(ENOENT) == ret) {
            url_errorcode_cb(s->interrupt_callback.opaque, 404, "rtsp");
        } else {
            url_errorcode_cb(s->interrupt_callback.opaque, ret, "rtsp");
        }
        return ret;
    }

#if 1
    /* l00192899  modify add seekable info*/
    if(!s->pb)
    {
        s->pb = av_mallocz(sizeof(AVIOContext));
    }

    (s->pb)->protocal_flag = URL_PROTOCOL_FLAG_NETWORK;
    (s->pb)->seekable = (0 == s->bSeekFlag) ? AVIO_SEEKABLE_NORMAL : 0;
#endif

    rt->real_setup_cache = av_mallocz(2 * s->nb_streams * sizeof(*rt->real_setup_cache));
    if (!rt->real_setup_cache)
        return AVERROR(ENOMEM);
    rt->real_setup = rt->real_setup_cache + s->nb_streams;

#if HAVE_UDP_RCV_THREAD
    if (rt->lower_transport == RTSP_LOWER_TRANSPORT_UDP ||
        rt->lower_transport == RTSP_LOWER_TRANSPORT_UDP_MULTICAST) {
        // if fail, will not call read_close();
        if (create_udp_recv_thread(s) < 0) {
            ff_rtsp_send_cmd_async(s, "TEARDOWN", rt->control_uri, NULL);
            ff_rtsp_close_streams(s);
            ff_rtsp_close_connections(s);
            ff_network_close();
            rt->real_setup = NULL;
            av_freep(&rt->real_setup_cache);
            return -1;
        }
    }
#endif

    if (rt->initial_pause) {
         /* do not start immediately */
    } else {
         if (rtsp_read_play(s) < 0) {
            ff_rtsp_close_streams(s);
            ff_rtsp_close_connections(s);
            return AVERROR_INVALIDDATA;
        }
    }

    return 0;
}

int ff_rtsp_tcp_read_packet(AVFormatContext *s, RTSPStream **prtsp_st,
                            uint8_t *buf, int buf_size)
{
    RTSPState *rt = s->priv_data;
    int id, len, i, ret;
    RTSPStream *rtsp_st;

    av_dlog(s, "tcp_read_packet:\n");
redo:
    for (;;) {
        RTSPMessageHeader reply;

        ret = ff_rtsp_read_reply(s, &reply, NULL, 1, NULL);
        if (ret < 0)
            return ret;
        if (ret == 1) /* received '$' */
            break;
        /* XXX: parse message */
        if (rt->state != RTSP_STATE_STREAMING)
            return 0;
    }
    ret = ffurl_read_complete(rt->rtsp_hd, buf, 3);
    if (ret != 3)
        return -1;
    id  = buf[0];
    len = AV_RB16(buf + 1);
    av_dlog(s, "id=%d len=%d\n", id, len);
    if (len > buf_size || len < 8)
        goto redo;
    /* get the data */
    ret = ffurl_read_complete(rt->rtsp_hd, buf, len);
    if (ret != len)
        return -1;
    if (rt->transport == RTSP_TRANSPORT_RDT &&
        ff_rdt_parse_header(buf, len, &id, NULL, NULL, NULL, NULL) < 0)
        return -1;

    /* find the matching stream */
    for (i = 0; i < rt->nb_rtsp_streams; i++) {
        rtsp_st = rt->rtsp_streams[i];
        if (id >= rtsp_st->interleaved_min &&
            id <= rtsp_st->interleaved_max)
            goto found;
    }
    goto redo;
found:
    *prtsp_st = rtsp_st;
    return len;
}

static int resetup_tcp(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;
    char host[1024];
    int port;

    av_url_split(NULL, 0, NULL, 0, host, sizeof(host), &port, NULL, 0,
                 s->filename);
    ff_rtsp_undo_setup(s);
    return ff_rtsp_make_setup_request(s, host, port, RTSP_LOWER_TRANSPORT_TCP,
                                      rt->real_challenge);
}

static int compute_reconnect_timestamp(RTSPState *rt, int64_t downloaded_duration_us)
{
    if (downloaded_duration_us <= 0) {
        return 0;
    }

    if (rt->seek_timestamp.type == RTSP_CLOCK_NPT) {
        double npt = rt->seek_timestamp.time.npt + downloaded_duration_us/(double)AV_TIME_BASE;
        if (rt->seek_end_timestamp.type == RTSP_CLOCK_NPT &&
            rt->seek_timestamp.time.npt >= rt->seek_end_timestamp.time.npt) {
            av_log(NULL, AV_LOG_ERROR, "[%s,%d] current NPT time is beyond of the end of time!\n", __FUNCTION__, __LINE__);
            return -1;
        }
        av_log(NULL, AV_LOG_INFO, "[%s,%d] NPT(%lf) + (%lld us)-> NPT(%lf)!\n",
            __FUNCTION__, __LINE__, rt->seek_timestamp.time.npt, downloaded_duration_us, npt);
        rt->seek_timestamp.time.npt = npt;
        return 0;
    } else if (rt->seek_timestamp.type == RTSP_CLOCK_UTC) {
        struct tm tm_time;
        time64_t time_sec, seek_end_sec;

        if (downloaded_duration_us/AV_TIME_BASE <= 0) {
            return 0;
        }
        memset(&tm_time, 0, sizeof(tm_time));
        tm_time.tm_year = rt->seek_timestamp.time.utc.year;
        tm_time.tm_mon  = rt->seek_timestamp.time.utc.mon;
        tm_time.tm_mday = rt->seek_timestamp.time.utc.day;
        tm_time.tm_hour = rt->seek_timestamp.time.utc.hour;
        tm_time.tm_min  = rt->seek_timestamp.time.utc.min;
        tm_time.tm_sec  = rt->seek_timestamp.time.utc.second;

        time_sec = mktime64(&tm_time);
        time_sec += downloaded_duration_us/AV_TIME_BASE;
        if (rt->seek_end_timestamp.type == RTSP_CLOCK_UTC) {
            memset(&tm_time, 0, sizeof(tm_time));
            tm_time.tm_year = rt->seek_end_timestamp.time.utc.year;
            tm_time.tm_mon  = rt->seek_end_timestamp.time.utc.mon;
            tm_time.tm_mday = rt->seek_end_timestamp.time.utc.day;
            tm_time.tm_hour = rt->seek_end_timestamp.time.utc.hour;
            tm_time.tm_min  = rt->seek_end_timestamp.time.utc.min;
            tm_time.tm_sec  = rt->seek_end_timestamp.time.utc.second;
            seek_end_sec = mktime64(&tm_time);
            if (time_sec >= seek_end_sec) {
                av_log(NULL, AV_LOG_ERROR, "[%s,%d] current UTC time(%lld) is beyond of the end of time(%lld)!\n",
                    __FUNCTION__, __LINE__, time_sec, seek_end_sec);
                return -1;
            }
        }
        memset(&tm_time, 0, sizeof(tm_time));
        if (localtime64_r(&time_sec, &tm_time)) {
            av_log(NULL, AV_LOG_INFO, "[%s,%d] date(%04d%02d%02dT%02d%02d%02d) + duration(%lld us) -> date(%04d%02d%02dT%02d%02d%02d)\n",
                __FUNCTION__, __LINE__,
                rt->seek_timestamp.time.utc.year,
                rt->seek_timestamp.time.utc.mon,
                rt->seek_timestamp.time.utc.day,
                rt->seek_timestamp.time.utc.hour,
                rt->seek_timestamp.time.utc.min,
                rt->seek_timestamp.time.utc.second,
                downloaded_duration_us,
                tm_time.tm_year, tm_time.tm_mon, tm_time.tm_mday,
                tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);

            rt->seek_timestamp.time.utc.year = tm_time.tm_year;
            rt->seek_timestamp.time.utc.mon  = tm_time.tm_mon;
            rt->seek_timestamp.time.utc.day  = tm_time.tm_mday;
            rt->seek_timestamp.time.utc.hour = tm_time.tm_hour;
            rt->seek_timestamp.time.utc.min  = tm_time.tm_min;
            rt->seek_timestamp.time.utc.second = tm_time.tm_sec;

            return 0;
        } else {
            av_log(NULL, AV_LOG_ERROR, "[%s,%d] localtime_r(%lld) error!\n", __FUNCTION__, __LINE__, time_sec);
        }
    }else {
        av_log(NULL, AV_LOG_ERROR, "[%s,%d] clock type(%d) temporarily not supported!\n",
            __FUNCTION__, __LINE__, rt->seek_end_timestamp.type);
    }

    return -1;
}

static int rtsp_reconnect(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;
    int ret, i;
    unsigned last_reconn_time = 0, cur_time;
    int64_t dowloaded_duration = 0, st_downloaded_duration;

    av_log(s, AV_LOG_INFO, "[%s,%d] start do reconnecting...\n", __FUNCTION__, __LINE__);
    url_errorcode_cb(s->interrupt_callback.opaque, NETWORK_DISCONNECT, "rtsp");

    /* compute the duration of data that has been downloaded */
    for (i = 0; i < s->nb_streams; i ++) {
        if (s->streams[i]->cur_dts != AV_NOPTS_VALUE &&
            s->streams[i]->first_dts != AV_NOPTS_VALUE) {
            st_downloaded_duration = s->streams[i]->cur_dts - s->streams[i]->first_dts;
            st_downloaded_duration = av_rescale_q(st_downloaded_duration,
                                       s->streams[i]->time_base, AV_TIME_BASE_Q);
            if (st_downloaded_duration > dowloaded_duration) {
                dowloaded_duration = st_downloaded_duration;
            }
        } else {
            st_downloaded_duration = -1;
        }
        av_log(s, AV_LOG_INFO, "[%s,%d] stream[%d] first_dts=%lld, cur_dts=%lld, downloaded_duration=%lld\n",
            __FUNCTION__, __LINE__, i, s->streams[i]->first_dts, s->streams[i]->cur_dts, st_downloaded_duration);
    }

    /* add the duration to the seek timestamp */
    if (compute_reconnect_timestamp(rt, dowloaded_duration) < 0) {
        av_log(s, AV_LOG_ERROR, "[%s,%d] compute timestamp error, exit reconnect!\n", __FUNCTION__, __LINE__);
        return -1;
    }

    /* now do reconnecting */
    rt->reconnecting = 1;
    rt->state = RTSP_STATE_IDLE;
    rt->lower_transport_mask = rt->lower_transport_mask_bak;
    do {
        if (ff_check_interrupt(&s->interrupt_callback)) {
            av_log(s, AV_LOG_ERROR, "[%s,%d] reconnect interrupted\n", __FUNCTION__, __LINE__);
            ret = AVERROR_EXIT;
            break;
        }
        cur_time = av_getsystemtime();
        if (cur_time - last_reconn_time >= 1000) {
            last_reconn_time = cur_time;
            ff_rtsp_undo_setup(s);
            ff_rtsp_close_connections(s);
            rt->session_id[0] = '\0';
            ret = ff_rtsp_connect(s);
            if (ret == 0) {
                av_log(s, AV_LOG_INFO, "[%s,%d] ff_rtsp_connect ok, send play\n", __FUNCTION__, __LINE__);
                ret = rtsp_read_play(s);
                if (ret != 0) {
                    av_log(s, AV_LOG_ERROR, "[%s,%d] rtsp_read_play return %d\n", __FUNCTION__, __LINE__, ret);
                } else {
                    break;
                }
            } else {
                av_log(s, AV_LOG_ERROR, "[%s,%d] reconnect return error=%d\n",
                    __FUNCTION__, __LINE__, ret);
            }
        }
        usleep(10000);
    } while(1);

    rt->reconnecting = 0;
    if (ret == 0) {
       url_errorcode_cb(s->interrupt_callback.opaque, NETWORK_NORMAL, "rtsp");
    }
    av_log(s, AV_LOG_INFO, "[%s,%d] do reconnecting return %d\n", __FUNCTION__, __LINE__, ret);

    return ret;
}

static int rtsp_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    RTSPState *rt = s->priv_data;
    int ret;
    RTSPMessageHeader reply1, *reply = &reply1;
    char cmd[1024];
    int64_t bandwidth_start = 0;
    int64_t bandwidth_end = 0;

retry:
    if (rt->server_type == RTSP_SERVER_REAL) {
        int i;

        for (i = 0; i < s->nb_streams; i++)
            rt->real_setup[i] = s->streams[i]->discard;

        if (!rt->need_subscription) {
            if (memcmp (rt->real_setup, rt->real_setup_cache,
                        sizeof(enum AVDiscard) * s->nb_streams)) {
                snprintf(cmd, sizeof(cmd),
                         "Unsubscribe: %s\r\n",
                         rt->last_subscription);
                ff_rtsp_send_cmd(s, "SET_PARAMETER", rt->control_uri,
                                 cmd, reply, NULL);
                if (reply->status_code != RTSP_STATUS_OK)
                    return AVERROR_INVALIDDATA;
                rt->need_subscription = 1;
            }
        }

        if (rt->need_subscription) {
            int r, rule_nr, first = 1;

            memcpy(rt->real_setup_cache, rt->real_setup,
                   sizeof(enum AVDiscard) * s->nb_streams);
            rt->last_subscription[0] = 0;

            snprintf(cmd, sizeof(cmd),
                     "Subscribe: ");
            for (i = 0; i < rt->nb_rtsp_streams; i++) {
                rule_nr = 0;
                for (r = 0; r < s->nb_streams; r++) {
                    if (s->streams[r]->id == i) {
                        if (s->streams[r]->discard != AVDISCARD_ALL) {
                            if (!first)
                                av_strlcat(rt->last_subscription, ",",
                                           sizeof(rt->last_subscription));
                            ff_rdt_subscribe_rule(
                                rt->last_subscription,
                                sizeof(rt->last_subscription), i, rule_nr);
                            first = 0;
                        }
                        rule_nr++;
                    }
                }
            }
            av_strlcatf(cmd, sizeof(cmd), "%s\r\n", rt->last_subscription);
            ff_rtsp_send_cmd(s, "SET_PARAMETER", rt->control_uri,
                             cmd, reply, NULL);
            if (reply->status_code != RTSP_STATUS_OK)
                return AVERROR_INVALIDDATA;
            rt->need_subscription = 0;

            if (rt->state == RTSP_STATE_STREAMING)
                rtsp_read_play (s);
        }
    }
    //z00228123 begin add for wms server replay
    if (rt->state == RTSP_STATE_EOF &&
            (rt->server_type == RTSP_SERVER_WMS || rt->server_type == RTSP_SERVER_REAL))
    {
        return AVERROR_EOF;
    }
    //z00228123 end
    bandwidth_start = av_gettime();
    ret = ff_rtsp_fetch_packet(s, pkt);
    bandwidth_end = av_gettime();
    if (ret < 0) {
        av_log(s, AV_LOG_WARNING, "[%s,%d] ff_rtsp_fetch_packet return error=%d, server_type=%d\n",
            __FUNCTION__, __LINE__, ret, rt->server_type);
        if (rt->state != RTSP_STATE_IDLE && rt->packets > 0) {
            if (!rtsp_reconnect(s)) {
                goto retry;
            } else {
                return AVERROR_EOF;
            }
        }
        //z00228123 begin add for wms server replay
        if ((rt->server_type == RTSP_SERVER_WMS || rt->server_type == RTSP_SERVER_REAL) && ret == AVERROR_EOF)
        {
            rt->state = RTSP_STATE_EOF;
            reset_downspeed(s);
            return ret;
        }
        //z00228123 end
        if (ret == AVERROR(ETIMEDOUT) && !rt->packets) {
            if (rt->lower_transport == RTSP_LOWER_TRANSPORT_UDP &&
                rt->lower_transport_mask & (1 << RTSP_LOWER_TRANSPORT_TCP)) {
                RTSPMessageHeader reply1, *reply = &reply1;
                av_log(s, AV_LOG_WARNING, "UDP timeout, retrying with TCP\n");
                if (rtsp_read_pause(s) != 0)
                    return -1;
                // TEARDOWN is required on Real-RTSP, but might make
                // other servers close the connection.
                if (rt->server_type == RTSP_SERVER_REAL || rt->server_type == RTSP_SERVER_RTP)
                    ff_rtsp_send_cmd(s, "TEARDOWN", rt->control_uri, NULL,
                                     reply, NULL);
                /*l00192899 modify,UDP timeout,but session_id is fine,should not make it 0*/
                //rt->session_id[0] = '\0';
                /*modify end*/
                if (resetup_tcp(s) == 0) {
                    rt->state = RTSP_STATE_IDLE;
                    rt->need_subscription = 1;
                    if (rtsp_read_play(s) != 0)
                        return -1;
                    goto retry;
                }
            }
        }
        /*l00192899,if ret is timeout error,return this error back by url_errorcode_cb*/
        if (CHECK_NET_INTERRUPT(ret))
        {
            url_errorcode_cb(rt->rtsp_hd->interrupt_callback.opaque, ret, "rtsp");
            url_errorcode_cb(rt->rtsp_hd->interrupt_callback.opaque, NETWORK_DISCONNECT, "rtsp");
            reset_downspeed(s);

            while(1)
            {
                if (ff_check_interrupt(&((rt->rtsp_hd)->interrupt_callback)))
                {
                    return AVERROR_EXIT;
                }

                usleep(20000);
            }
        }
        /*end*/
        reset_downspeed(s);
        return ret;
    }
    rt->packets++;
    get_downspeed(s, pkt->size, (bandwidth_end - bandwidth_start));

    /* send dummy request to keep TCP connection alive */
    if ((av_gettime() - rt->last_cmd_time) / 1000000 >= rt->timeout / 2) {
        if (rt->server_type == RTSP_SERVER_WMS ||
           (rt->server_type != RTSP_SERVER_REAL &&
            rt->get_parameter_supported)) {
            ff_rtsp_send_cmd_async(s, "GET_PARAMETER", rt->control_uri, NULL);
        } else {
            ff_rtsp_send_cmd_async(s, "OPTIONS", "*", NULL);
        }
    }

    return 0;
}

static int rtsp_read_seek(AVFormatContext *s, int stream_index,
                          int64_t timestamp, int flags)
{
    RTSPState *rt = s->priv_data;
    int ret = 0;
    AVRational seek_ts_r;
    int64_t seek_ts;

    if (rt->seek_timestamp.type != RTSP_CLOCK_NONE &&
        rt->seek_timestamp.type != RTSP_CLOCK_NPT) {
        av_log(s, AV_LOG_ERROR, "[%s,%d] clock type(%d) not support seek!\n",
            __FUNCTION__, __LINE__, rt->seek_timestamp.type);
        return -1;
    }
    seek_ts = av_rescale_q(timestamp,
                s->streams[stream_index]->time_base, AV_TIME_BASE_Q);
    rt->seek_timestamp.type     = RTSP_CLOCK_NPT;
    rt->seek_timestamp.time.npt = seek_ts/(double)AV_TIME_BASE;
    rt->seek_end_timestamp.type = RTSP_CLOCK_NONE;
    av_log(s, AV_LOG_INFO, "[%s,%d] seek timestamp(%lld) to npt is %lf\n",
        __FUNCTION__, __LINE__, seek_ts, rt->seek_timestamp.time.npt);

    switch(rt->state) {
    default:
    case RTSP_STATE_IDLE:
        break;
    case RTSP_STATE_EOF:
        rt->state = RTSP_STATE_SEEKING;
        ret = rtsp_read_play(s);
        if (ret != 0){
            rt->state = RTSP_STATE_EOF;
            return ret;
        }
        break;
    case RTSP_STATE_STREAMING:
        //Warning:must pause first before seek when server is helix
        if (rt->server_type == RTSP_SERVER_REAL) {
            ret = rtsp_read_pause(s);
            if (ret != 0)
                return ret;
        }
        rt->state = RTSP_STATE_SEEKING;
        ret = rtsp_read_play(s);
        if (ret != 0){
            rt->state = RTSP_STATE_STREAMING;
            return ret;
        }
        break;
    case RTSP_STATE_PAUSED:
        rt->state = RTSP_STATE_SEEKING;
        ret = rtsp_read_play(s);
        if (ret != 0){
            rt->state = RTSP_STATE_PAUSED;
            return ret;
        }
        /*recover to pause state*/
        ret = rtsp_read_pause(s);
        if (ret != 0){
            rt->state = RTSP_STATE_STREAMING;
            return ret;
        }
        break;
    }
    return 0;
}

static int rtsp_read_close(AVFormatContext *s)
{
    RTSPState *rt = s->priv_data;

#if HAVE_UDP_RCV_THREAD
    destroy_udp_recv_thread(s);
#endif

    ff_rtsp_send_cmd_async(s, "TEARDOWN", rt->control_uri, NULL);

    ff_rtsp_close_streams(s);
    ff_rtsp_close_connections(s);
    ff_network_close();
    rt->real_setup = NULL;
    av_freep(&rt->real_setup_cache);
    if (rt->headers) {
        av_freep(&rt->headers);
    }
    return 0;
}

const AVClass rtsp_demuxer_class = {
    .class_name     = "RTSP demuxer",
    .item_name      = av_default_item_name,
    .option         = ff_rtsp_options,
    .version        = LIBAVUTIL_VERSION_INT,
};

AVInputFormat ff_rtsp_demuxer = {
    .name           = "rtsp",
    .long_name      = NULL_IF_CONFIG_SMALL("RTSP input format"),
    .priv_data_size = sizeof(RTSPState),
    .read_probe     = rtsp_probe,
    .read_header    = rtsp_read_header,
    .read_packet    = rtsp_read_packet,
    .read_close     = rtsp_read_close,
    .read_seek      = rtsp_read_seek,
    .flags = AVFMT_NOFILE,
    .read_play = rtsp_read_play,
    .read_pause = rtsp_read_pause,
    .priv_class = &rtsp_demuxer_class,
};
