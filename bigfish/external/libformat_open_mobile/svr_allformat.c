/*
 * svr_allformat.c
 *
 *  Created on: 2014Äê6ÔÂ23ÈÕ
 *      Author: z00187490
 */
#include <pthread.h>
#include <libavformat/avformat.h>

static pthread_once_t  s_once = PTHREAD_ONCE_INIT;
static void init()
{
    av_register_all();
    avformat_network_init();
//#ifndef UDF_NOTSUPPORT
//    extern AVInputFormat svr_iso_demuxer;
//   av_register_input_format(&svr_iso_demuxer);//bluray iso demuxer
//#endif
    extern AVInputFormat ff_hls_demuxer;
    av_register_input_format(&ff_hls_demuxer);//hls demuxer
#ifndef UDF_NOTSUPPORT
    extern URLProtocol svr_udf_protocol;
    av_register_protocol2(&svr_udf_protocol, sizeof(svr_udf_protocol));
#endif

    extern URLProtocol ff_http_protocol;
    av_register_protocol2(&ff_http_protocol, sizeof(ff_http_protocol));
#ifndef HTTPSEX_NOTSUPPORT
    extern URLProtocol ff_httpsex_protocol;
    av_register_protocol2(&ff_httpsex_protocol, sizeof(ff_httpsex_protocol));
#endif

#ifndef HTTPPROXY_NOTSUPPORT
    extern URLProtocol ff_httpproxy_protocol;
    av_register_protocol2(&ff_httpproxy_protocol, sizeof(ff_httpproxy_protocol));
#endif

    extern URLProtocol ff_tcp_protocol;
    av_register_protocol2(&ff_tcp_protocol, sizeof(ff_tcp_protocol));

#ifndef LPCMHTTP_NOTSUPPORT
    extern URLProtocol ff_lpcmhttp_protocol;
    av_register_protocol2(&ff_lpcmhttp_protocol, sizeof(ff_lpcmhttp_protocol));
#endif
    //av_log_set_callback(svr_ffmpeg_callback);
}

void svr_register_allformat()
{
    pthread_once(&s_once, init);
}
