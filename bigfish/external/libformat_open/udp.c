/*
 * UDP prototype streaming system
 * Copyright (c) 2000, 2001, 2002 Fabrice Bellard
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
 * @file
 * UDP protocol
 */

#define _BSD_SOURCE     /* Needed for using struct ip_mreq with recent glibc */

#include "avformat.h"
#include "avio_internal.h"
#include "libavutil/parseutils.h"
#include "libavutil/fifo.h"
#include "libavutil/intreadwrite.h"
#include "libavutil/avstring.h"
#include <unistd.h>
#include "internal.h"
#include "network.h"
#include "os_support.h"
#include "url.h"

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>

#if defined (ANDROID_VERSION)
#define HAVE_PTHREADS 1
#endif

#if HAVE_PTHREADS
#include <pthread.h>
#endif

#include <sys/time.h>

#ifndef IPV6_ADD_MEMBERSHIP
#define IPV6_ADD_MEMBERSHIP IPV6_JOIN_GROUP
#define IPV6_DROP_MEMBERSHIP IPV6_LEAVE_GROUP
#endif

#define UDP_TX_BUF_SIZE 32768
//#define UDP_MAX_PKT_SIZE 65536
#define UDP_MAX_PKT_SIZE (128*1024)
#define UDP_NETWORK_READ_TIMEOUT (30000000)

#define __FILE_NAME__  av_filename(__FILE__)
#define UDP_TRACE()    av_log(NULL, AV_LOG_INFO, "[%s:%d] at this\n", __FILE_NAME__, __LINE__)

#define UDP_READ_TIME_OUT   (5000000) // 5 second;

typedef struct {
    int udp_fd;
    int ttl;
    int buffer_size;
    int is_multicast;
    int local_port;
    int reuse_socket;
    struct sockaddr_storage dest_addr;
    int dest_addr_len;
    int is_connected;

    /* Circular Buffer variables for use in UDP receive code */
    int circular_buffer_size;
    AVFifoBuffer *fifo;
    int circular_buffer_error;
#if HAVE_PTHREADS
    pthread_t circular_buffer_thread;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int thread_started;
    volatile int exit_thread;
#endif
    uint8_t tmp[UDP_MAX_PKT_SIZE+4];
    int remaining_in_dg;
    int quit_flag;
} UDPContext;

static int udp_set_multicast_ttl(int sockfd, int mcastTTL,
                                 struct sockaddr *addr)
{
#ifdef IP_MULTICAST_TTL
    if (addr->sa_family == AF_INET) {
        if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &mcastTTL, sizeof(mcastTTL)) < 0) {
            av_log(NULL, AV_LOG_ERROR, "setsockopt(IP_MULTICAST_TTL): %s\n", strerror(errno));
            return -1;
        }
    }
#endif
#if defined(IPPROTO_IPV6) && defined(IPV6_MULTICAST_HOPS)
    if (addr->sa_family == AF_INET6) {
        if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &mcastTTL, sizeof(mcastTTL)) < 0) {
            av_log(NULL, AV_LOG_ERROR, "setsockopt(IPV6_MULTICAST_HOPS): %s\n", strerror(errno));
            return -1;
        }
    }
#endif
    return 0;
}

static int udp_join_multicast_group(int sockfd, struct sockaddr *addr)
{
#ifdef IP_ADD_MEMBERSHIP
    if (addr->sa_family == AF_INET) {
        struct ip_mreq mreq;

        UDP_TRACE();
        mreq.imr_multiaddr.s_addr = ((struct sockaddr_in *)addr)->sin_addr.s_addr;
        mreq.imr_interface.s_addr= INADDR_ANY;
        if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const void *)&mreq, sizeof(mreq)) < 0) {
            av_log(NULL, AV_LOG_ERROR, "setsockopt(IP_ADD_MEMBERSHIP): %s\n", strerror(errno));
            return -1;
        }
    }
#endif
#if HAVE_STRUCT_IPV6_MREQ && defined(IPPROTO_IPV6)
    if (addr->sa_family == AF_INET6) {
        struct ipv6_mreq mreq6;

        memcpy(&mreq6.ipv6mr_multiaddr, &(((struct sockaddr_in6 *)addr)->sin6_addr), sizeof(struct in6_addr));
        mreq6.ipv6mr_interface= 0;
        if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, &mreq6, sizeof(mreq6)) < 0) {
            av_log(NULL, AV_LOG_ERROR, "setsockopt(IPV6_ADD_MEMBERSHIP): %s\n", strerror(errno));
            return -1;
        }
    }
#endif
    return 0;
}

static int udp_leave_multicast_group(int sockfd, struct sockaddr *addr)
{
#ifdef IP_DROP_MEMBERSHIP
    if (addr->sa_family == AF_INET) {
        struct ip_mreq mreq;

        UDP_TRACE();
        mreq.imr_multiaddr.s_addr = ((struct sockaddr_in *)addr)->sin_addr.s_addr;
        mreq.imr_interface.s_addr= INADDR_ANY;
        if (setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (const void *)&mreq, sizeof(mreq)) < 0) {
            av_log(NULL, AV_LOG_ERROR, "setsockopt(IP_DROP_MEMBERSHIP): %s\n", strerror(errno));
            return -1;
        }
    }
#endif
#if HAVE_STRUCT_IPV6_MREQ && defined(IPPROTO_IPV6)
    if (addr->sa_family == AF_INET6) {
        struct ipv6_mreq mreq6;

        memcpy(&mreq6.ipv6mr_multiaddr, &(((struct sockaddr_in6 *)addr)->sin6_addr), sizeof(struct in6_addr));
        mreq6.ipv6mr_interface= 0;
        if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_DROP_MEMBERSHIP, &mreq6, sizeof(mreq6)) < 0) {
            av_log(NULL, AV_LOG_ERROR, "setsockopt(IPV6_DROP_MEMBERSHIP): %s\n", strerror(errno));
            return -1;
        }
    }
#endif
    return 0;
}

static struct addrinfo* udp_resolve_host(const char *hostname, int port,
                                         int type, int family, int flags)
{
    struct addrinfo hints, *res = 0;
    int error;
    char sport[16];
    const char *node = 0, *service = "0";

    if (port > 0) {
        snprintf(sport, sizeof(sport), "%d", port);
        service = sport;
    }
    if ((hostname) && (hostname[0] != '\0') && (hostname[0] != '?')) {
        node = hostname;
    }
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = type;
    hints.ai_family   = family;
    hints.ai_flags = flags;
    if ((error = getaddrinfo(node, service, &hints, &res))) {
        res = NULL;
        av_log(NULL, AV_LOG_ERROR, "udp_resolve_host: %s\n", gai_strerror(error));
    }

    return res;
}

static int udp_set_url(struct sockaddr_storage *addr,
                       const char *hostname, int port)
{
    struct addrinfo *res0;
    int addr_len;

    res0 = udp_resolve_host(hostname, port, SOCK_DGRAM, AF_UNSPEC, 0);
    if (res0 == 0) return AVERROR(EIO);
    memcpy(addr, res0->ai_addr, res0->ai_addrlen);
    addr_len = res0->ai_addrlen;
    freeaddrinfo(res0);

    return addr_len;
}

static int udp_socket_create(UDPContext *s, struct sockaddr_storage *addr,
                             int *addr_len, const char *localaddr)
{
    int udp_fd = -1;
    struct addrinfo *res0 = NULL, *res = NULL;
    int family = AF_UNSPEC;

    if (((struct sockaddr *) &s->dest_addr)->sa_family)
        family = ((struct sockaddr *) &s->dest_addr)->sa_family;
    res0 = udp_resolve_host(localaddr[0] ? localaddr : NULL, s->local_port,
                            SOCK_DGRAM, family, AI_PASSIVE);
    if (res0 == 0)
        goto fail;
    for (res = res0; res; res=res->ai_next) {
        udp_fd = socket(res->ai_family, SOCK_DGRAM, 0);
        if (udp_fd > 0) break;
        av_log(NULL, AV_LOG_ERROR, "socket: %s\n", strerror(errno));
    }

    if (udp_fd < 0)
        goto fail;

    memcpy(addr, res->ai_addr, res->ai_addrlen);
    *addr_len = res->ai_addrlen;

    freeaddrinfo(res0);

    return udp_fd;

 fail:
    if (udp_fd >= 0)
        closesocket(udp_fd);
    if(res0)
        freeaddrinfo(res0);
    return -1;
}

static int udp_port(struct sockaddr_storage *addr, int addr_len)
{
    char sbuf[sizeof(int)*3+1];

    if (getnameinfo((struct sockaddr *)addr, addr_len, NULL, 0,  sbuf, sizeof(sbuf), NI_NUMERICSERV) != 0) {
        av_log(NULL, AV_LOG_ERROR, "getnameinfo: %s\n", strerror(errno));
        return -1;
    }

    return strtol(sbuf, NULL, 10);
}


/**
 * If no filename is given to av_open_input_file because you want to
 * get the local port first, then you must call this function to set
 * the remote server address.
 *
 * url syntax: udp://host:port[?option=val...]
 * option: 'ttl=n'       : set the ttl value (for multicast only)
 *         'localport=n' : set the local port
 *         'pkt_size=n'  : set max packet size
 *         'reuse=1'     : enable reusing the socket
 *
 * @param h media file context
 * @param uri of the remote server
 * @return zero if no error.
 */
int ff_udp_set_remote_url(URLContext *h, const char *uri)
{
    UDPContext *s = h->priv_data;
    char hostname[256], buf[10];
    int port;
    const char *p;

    av_url_split(NULL, 0, NULL, 0, hostname, sizeof(hostname), &port, NULL, 0, uri);

    /* set the destination address */
    s->dest_addr_len = udp_set_url(&s->dest_addr, hostname, port);
    if (s->dest_addr_len < 0) {
        return AVERROR(EIO);
    }
    s->is_multicast = ff_is_multicast_address((struct sockaddr*) &s->dest_addr);
    p = strchr(uri, '?');
    if (p) {
        if (av_find_info_tag(buf, sizeof(buf), "connect", p)) {
            int was_connected = s->is_connected;
            s->is_connected = strtol(buf, NULL, 10);
            if (s->is_connected && !was_connected) {
                if (connect(s->udp_fd, (struct sockaddr *) &s->dest_addr,
                            s->dest_addr_len)) {
                    s->is_connected = 0;
                    av_log(h, AV_LOG_ERROR, "connect: %s\n", strerror(errno));
                    return AVERROR(EIO);
                }
            }
        }
    }

    return 0;
}

/**
 * Return the local port used by the UDP connection
 * @param h media file context
 * @return the local port number
 */
int ff_udp_get_local_port(URLContext *h)
{
    UDPContext *s = h->priv_data;
    return s->local_port;
}

/**
 * Return the udp file handle for select() usage to wait for several RTP
 * streams at the same time.
 * @param h media file context
 */
static int udp_get_file_handle(URLContext *h)
{
    UDPContext *s = h->priv_data;
    return s->udp_fd;
}

#if HAVE_PTHREADS
static void *circular_buffer_task( void *_URLContext)
{
    URLContext *h = _URLContext;
    UDPContext *s = h->priv_data;
    fd_set rfds;
    struct timeval tv;
    int network_disconnect = 0;
    int64_t timeout_start_time = av_gettime(), now_time, start_time;
    int64_t last_pkt_recv_time  = -1;

    while(!s->exit_thread) {
        int left;
        int ret;
        int len;

        if (ff_check_interrupt(&h->interrupt_callback)) {
            s->circular_buffer_error = AVERROR(EINTR);
            goto end;
        }

        if (!network_disconnect) {
            now_time   = av_gettime();
            start_time = last_pkt_recv_time > 0?last_pkt_recv_time:timeout_start_time;
            if (start_time > 0 && (llabs(now_time - start_time) > UDP_READ_TIME_OUT)) {
                av_log(NULL, AV_LOG_ERROR, "[%s,%d] udp no data received for %d us, send NETWORK_DISCONNECT && return error!\n",
                   __FUNCTION__, __LINE__, UDP_READ_TIME_OUT);
                url_errorcode_cb(h->interrupt_callback.opaque, NETWORK_DISCONNECT, "udp");
                network_disconnect = 1;
                if (timeout_start_time > 0) {
                    s->circular_buffer_error = AVERROR(EIO);
                    goto end;
                }
            }
        }

        FD_ZERO(&rfds);
        FD_SET(s->udp_fd, &rfds);
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        ret = select(s->udp_fd + 1, &rfds, NULL, NULL, &tv);
        if (ret < 0) {
            if (ff_neterrno() == AVERROR(EINTR))
                continue;
            s->circular_buffer_error = AVERROR(EIO);
            goto end;
        }

        if (!(ret > 0 && FD_ISSET(s->udp_fd, &rfds)))
            continue;

        /* How much do we have left to the end of the buffer */
        /* Whats the minimum we can read so that we dont comletely fill the buffer */
      //  left = av_fifo_space(s->fifo);
#if 0
        /* No Space left, error, what do we do now */
        if(left < UDP_MAX_PKT_SIZE + 4) {
            av_log(h, AV_LOG_ERROR, "circular_buffer: OVERRUN, return EIO(%d)\n", EIO);


            s->circular_buffer_error = AVERROR(EIO);
            goto end;
        }
#endif

      //  left = FFMIN(left, s->fifo->end - s->fifo->wptr);
        len = recv(s->udp_fd, s->tmp+4, sizeof(s->tmp)-4, 0);

        if (len < 0) {
            if (ff_neterrno() != AVERROR(EAGAIN) && ff_neterrno() != AVERROR(EINTR)) {
                s->circular_buffer_error = AVERROR(EIO);
                goto end;
            }
            continue;
        }
        if (timeout_start_time > 0) {
            timeout_start_time = -1;
            av_log(0, AV_LOG_INFO, "[%s,%d] udp first pkt received, disable timeout checking!\n",
                __FUNCTION__, __LINE__);
        }
        last_pkt_recv_time = av_gettime();
        if (network_disconnect) {
            av_log(0, AV_LOG_INFO, "[%s,%d] udp network recovered, send NETWORK_NORMAL\n", __FUNCTION__, __LINE__);
            url_errorcode_cb(h->interrupt_callback.opaque, NETWORK_NORMAL, "udp");
            network_disconnect = 0;
        }

        left = av_fifo_space(s->fifo);
        /* No Space left, error, what do we do now */
        if(left < len + 4) {
            av_log(h, AV_LOG_ERROR, "circular_buffer: OVERRUN, Discard packet, len=%d\n", len);
            continue;
        }
        AV_WL32(s->tmp, len);
        pthread_mutex_lock(&s->mutex);
        av_fifo_generic_write(s->fifo, s->tmp, len+4, NULL);
        pthread_cond_signal(&s->cond);
        pthread_mutex_unlock(&s->mutex);
    }

end:
    pthread_mutex_lock(&s->mutex);
    pthread_cond_signal(&s->cond);
    pthread_mutex_unlock(&s->mutex);

    return NULL;
}
#endif

/* put it in UDP context */
/* return non zero if error */
static int udp_open(URLContext *h, const char *uri, int flags)
{
    char hostname[1024], localaddr[1024] = "";
    int port, udp_fd = -1, tmp, bind_ret = -1;
    UDPContext *s = h->priv_data;
    int is_output;
    const char *p;
    char buf[256];
    struct sockaddr_storage my_addr;
    int len;
    int reuse_specified = 0;

    av_log(NULL, AV_LOG_INFO, "[%s:%d] udp_open(%s, %d)\n", __FILE_NAME__, __LINE__, uri, flags);
    h->is_streamed = 1;
    h->max_packet_size = 1472;

    is_output = !(flags & AVIO_FLAG_READ);

    s->ttl = 16;
    s->buffer_size = is_output ? UDP_TX_BUF_SIZE : UDP_MAX_PKT_SIZE;

    //s->circular_buffer_size = 7*188*4096;
    s->circular_buffer_size = 7*188*4096*4;

    p = strchr(uri, '?');
    if (p) {
        if (av_find_info_tag(buf, sizeof(buf), "reuse", p)) {
            char *endptr = NULL;
            s->reuse_socket = strtol(buf, &endptr, 10);
            /* assume if no digits were found it is a request to enable it */
            if (buf == endptr)
                s->reuse_socket = 1;
            reuse_specified = 1;
        }
        if (av_find_info_tag(buf, sizeof(buf), "ttl", p)) {
            s->ttl = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "localport", p)) {
            s->local_port = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "pkt_size", p)) {
            h->max_packet_size = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "buffer_size", p)) {
            s->buffer_size = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "connect", p)) {
            s->is_connected = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "fifo_size", p)) {
            s->circular_buffer_size = strtol(buf, NULL, 10)*188;
        }
        if (av_find_info_tag(buf, sizeof(buf), "localaddr", p)) {
            av_strlcpy(localaddr, buf, sizeof(localaddr));
        }
    }

    /* fill the dest addr */
    av_url_split(NULL, 0, NULL, 0, hostname, sizeof(hostname), &port, NULL, 0, uri);

    /* XXX: fix av_url_split */
    if (hostname[0] == '\0' || hostname[0] == '?') {
        /* only accepts null hostname if input */
        if (!(flags & AVIO_FLAG_READ))
            goto fail;
    } else {
        if (ff_udp_set_remote_url(h, uri) < 0)
            goto fail;
    }

    if ((s->is_multicast || !s->local_port) && (h->flags & AVIO_FLAG_READ))
        s->local_port = port;

    UDP_TRACE();
    udp_fd = udp_socket_create(s, &my_addr, &len, localaddr);
    if (udp_fd < 0)
        goto fail;

    /* Follow the requested reuse option, unless it's multicast in which
     * case enable reuse unless explicitly disabled.
     */
    if (s->reuse_socket || (s->is_multicast && !reuse_specified)) {
        s->reuse_socket = 1;
        UDP_TRACE();
        if (setsockopt (udp_fd, SOL_SOCKET, SO_REUSEADDR, &(s->reuse_socket), sizeof(s->reuse_socket)) != 0)
            goto fail;
    }

    /* the bind is needed to give a port to the socket now */
    /* if multicast, try the multicast address bind first */
    if (s->is_multicast && (h->flags & AVIO_FLAG_READ)) {
        UDP_TRACE();
        bind_ret = bind(udp_fd,(struct sockaddr *)&s->dest_addr, len);
    }
    /* bind to the local address if not multicast or if the multicast
     * bind failed */
    if (bind_ret < 0 && bind(udp_fd,(struct sockaddr *)&my_addr, len) < 0)
        goto fail;

    UDP_TRACE();
    len = sizeof(my_addr);
    getsockname(udp_fd, (struct sockaddr *)&my_addr, &len);
    s->local_port = udp_port(&my_addr, len);

    if (s->is_multicast) {
        if (!(h->flags & AVIO_FLAG_READ)) {
            /* output */
            if (udp_set_multicast_ttl(udp_fd, s->ttl, (struct sockaddr *)&s->dest_addr) < 0)
                goto fail;
        } else {
            /* input */
            if (udp_join_multicast_group(udp_fd, (struct sockaddr *)&s->dest_addr) < 0)
                goto fail;
        }
    }

    if (is_output) {
        /* limit the tx buf size to limit latency */
        tmp = s->buffer_size;
        if (setsockopt(udp_fd, SOL_SOCKET, SO_SNDBUF, &tmp, sizeof(tmp)) < 0) {
            av_log(h, AV_LOG_ERROR, "setsockopt(SO_SNDBUF): %s\n", strerror(errno));
            goto fail;
        }
    } else {
        /* set udp recv buffer size to the largest possible udp packet size to
         * avoid losing data on OSes that set this too low by default. */
        tmp = s->buffer_size;
        if (setsockopt(udp_fd, SOL_SOCKET, SO_RCVBUF, &tmp, sizeof(tmp)) < 0) {
            av_log(h, AV_LOG_WARNING, "setsockopt(SO_RECVBUF): %s\n", strerror(errno));
        }
        tmp  = 0;
        int tmp_len = sizeof(tmp);
        if (getsockopt(udp_fd, SOL_SOCKET, SO_RCVBUF, &tmp, &tmp_len) < 0) {
            av_log(h, AV_LOG_ERROR, "getsockopt(SO_RECVBUF): %s\n", strerror(errno));
        }
        av_log(h, AV_LOG_INFO, "[UDP] getsockopt(SO_RECVBUF): %d\n", tmp);
        /* make the socket non-blocking */
        ff_socket_nonblock(udp_fd, 1);
    }
    if (s->is_connected) {
        if (connect(udp_fd, (struct sockaddr *) &s->dest_addr, s->dest_addr_len)) {
            av_log(h, AV_LOG_ERROR, "connect: %s\n", strerror(errno));
            goto fail;
        }
    }

    s->udp_fd = udp_fd;

#if HAVE_PTHREADS
    if (!is_output && s->circular_buffer_size) {
        int ret;

        UDP_TRACE();
        /* start the task going */
        s->fifo = av_fifo_alloc(s->circular_buffer_size);
        ret = pthread_mutex_init(&s->mutex, NULL);
        if (ret != 0) {
            av_log(h, AV_LOG_ERROR, "pthread_mutex_init failed : %s\n", strerror(ret));
            goto fail;
        }
        ret = pthread_cond_init(&s->cond, NULL);
        if (ret != 0) {
            av_log(h, AV_LOG_ERROR, "pthread_cond_init failed : %s\n", strerror(ret));
            goto cond_fail;
        }
        ret = pthread_create(&s->circular_buffer_thread, NULL, circular_buffer_task, h);
        if (ret != 0) {
            av_log(h, AV_LOG_ERROR, "pthread_create failed : %s\n", strerror(ret));
            goto thread_fail;
        }
        s->thread_started = 1;
    }
#endif
    UDP_TRACE();
    return 0;
#if HAVE_PTHREADS
 thread_fail:
    pthread_cond_destroy(&s->cond);
 cond_fail:
    pthread_mutex_destroy(&s->mutex);
#endif
 fail:
    UDP_TRACE();
    if (udp_fd >= 0)
        closesocket(udp_fd);
    av_fifo_free(s->fifo);
    return AVERROR(EIO);
}

#if 1
static int udp_read(URLContext *h, uint8_t *buf, int size)
{
    UDPContext *s = h->priv_data;
    int ret;
    int avail;

    av_log(0, AV_LOG_INFO, "local_port=%d, fifo=%p", s->local_port, s->fifo);
#if HAVE_PTHREADS
    if (s->fifo) {
        pthread_mutex_lock(&s->mutex);
        do {
            if (ff_check_interrupt(&h->interrupt_callback)) {
                pthread_mutex_unlock(&s->mutex);
                return AVERROR_EXIT;
            }
            avail = av_fifo_size(s->fifo);
            if (avail) { // >=size) {
                uint8_t tmp[4];
                pthread_mutex_unlock(&s->mutex);

                av_fifo_generic_read(s->fifo, tmp, 4, NULL);
                avail= AV_RL32(tmp);
                if(avail > size){
                    av_log(h, AV_LOG_WARNING, "Part of datagram lost due to insufficient buffer size\n");
                    avail= size;
                }

                av_fifo_generic_read(s->fifo, buf, avail, NULL);
                av_fifo_drain(s->fifo, AV_RL32(tmp) - avail);
                return avail;
            } else if(s->circular_buffer_error){
                av_log(0, AV_LOG_ERROR, "[%s,%d] size:%d return error %d\n", __FUNCTION__, __LINE__, size, s->circular_buffer_error);
                pthread_mutex_unlock(&s->mutex);
                return s->circular_buffer_error;
            } else if(h->flags & AVIO_FLAG_NONBLOCK) {
                pthread_mutex_unlock(&s->mutex);
                return AVERROR(EAGAIN);
            } else {
                pthread_cond_wait(&s->cond, &s->mutex);
            }
        } while( 1);
    }
#endif

    if (!(h->flags & AVIO_FLAG_NONBLOCK)) {
        ret = ff_network_wait_fd(s->udp_fd, 0);
        if (ret < 0)
            return ret;
    }

    ret = recv(s->udp_fd, buf, size, 0);

    return ret < 0 ? ff_neterrno() : ret;
}
#else
static int udp_read(URLContext *h, uint8_t *buf, int size)
{
    UDPContext *s = h->priv_data;
    int len, fd_max, ret;
    fd_set rfds;
    struct timeval tv;
    int64_t time_start = av_gettime();

    for (;;) {
        if (ff_check_interrupt(&(h->interrupt_callback)))
            return AVERROR_EXIT; //z00180556 re-connect

        if (NULL != s && 1 == s->quit_flag)
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d], receive quit info \n", __FILE_NAME__, __LINE__);
            return -1;
        }

        fd_max = s->udp_fd;
        FD_ZERO(&rfds);
        FD_SET(s->udp_fd, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 500*1000;
        ret = select(fd_max + 1, &rfds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(s->udp_fd, &rfds))
        {
            len = recv(s->udp_fd, buf, size, 0);
            if (len < 0) {
                if (ff_neterrno() != AVERROR(EINTR) &&
                    ff_neterrno() != AVERROR(EAGAIN))
                        //return AVERROR(ff_neterrno());
                        av_log(NULL, AV_LOG_ERROR, "[%s:%d], udp recv: 0x%x \n", __FILE_NAME__, __LINE__, ff_neterrno());
                        return ff_neterrno();

            } else {
                return len;
            }
        }
        else if (ret < 0)
        {
            if (ff_neterrno() == AVERROR(EINTR)
                && (UDP_NETWORK_READ_TIMEOUT > llabs(av_gettime() - time_start)))
                continue;

            av_log(NULL, AV_LOG_ERROR, "[%s:%d], udp select: 0x%x \n", __FILE_NAME__, __LINE__, ff_neterrno());
            return -1;
        }

        /* timeout */
        if (UDP_NETWORK_READ_TIMEOUT < llabs(av_gettime() - time_start))
        {
            av_log(NULL, AV_LOG_ERROR, "# [%s:%d]ETIMEDOUT #\n",__FILE__,__LINE__);
            av_log(NULL,AV_LOG_ERROR,"UDP TIME OUT!\n");
            return AVERROR(ETIMEDOUT);
        }
    }
}
#endif

#if 1
static int udp_write(URLContext *h, const uint8_t *buf, int size)
{
    UDPContext *s = h->priv_data;
    int ret;

    if (!(h->flags & AVIO_FLAG_NONBLOCK)) {
        ret = ff_network_wait_fd(s->udp_fd, 1);
        if (ret < 0)
            return ret;
    }

    if (!s->is_connected) {
        ret = sendto (s->udp_fd, buf, size, 0,
                      (struct sockaddr *) &s->dest_addr,
                      s->dest_addr_len);
    } else
        ret = send(s->udp_fd, buf, size, 0);

    return ret < 0 ? ff_neterrno() : ret;
}
#else
static int udp_write(URLContext *h, const uint8_t *buf, int size)
{
    UDPContext *s = h->priv_data;
    int ret, fd_max, len;
    fd_set wfds;
    struct timeval tv;

    for(;;) {
        if (NULL != s && 1 == s->quit_flag)
            return AVERROR(EINTR);

        if (ff_check_interrupt(&(h->interrupt_callback)))
            return AVERROR_EXIT; //h00212929 modfy for rtsp exit,will cause dead-loop
        fd_max = s->udp_fd;
        FD_ZERO(&wfds);
        FD_SET(s->udp_fd, &wfds);
        tv.tv_sec = 0;
        tv.tv_usec = 100 * 1000;
        ret = select(fd_max + 1, NULL, &wfds, NULL, &tv);
        if (ret > 0 && FD_ISSET(s->udp_fd, &wfds)) {

            len = send(s->udp_fd, buf, size, 0);

            if (!s->is_connected) {
                len = sendto (s->udp_fd, buf, size, 0,(struct sockaddr *) &s->dest_addr,
                      s->dest_addr_len);
            } else{
                len = send(s->udp_fd, buf, size, 0);
            }

            if (len < 0) {
                if (ff_neterrno() != AVERROR(EINTR) &&
                    ff_neterrno() != AVERROR(EAGAIN))
                    return AVERROR(ff_neterrno());
                continue;
            }else{
                return len;
            }
        } else if (ret < 0) {
             if (ff_neterrno() == AVERROR(EINTR))
                continue;
            return -1;
        }
    }
}
#endif

static int udp_close(URLContext *h)
{
    UDPContext *s = h->priv_data;

#if HAVE_PTHREADS
    int ret;
    if (s->thread_started) {
        s->exit_thread = 1;
        av_log(NULL, AV_LOG_INFO, "[%s:%d] udp join thread exit \n", __FILE_NAME__, __LINE__);
        ret = pthread_join(s->circular_buffer_thread, NULL);
        if (ret != 0)
            av_log(h, AV_LOG_ERROR, "pthread_join(): %s\n", strerror(ret));

        av_log(NULL, AV_LOG_INFO, "[%s:%d] udp join thread exit end \n", __FILE_NAME__, __LINE__);
    }

    av_fifo_free(s->fifo);
    pthread_mutex_destroy(&s->mutex);
    pthread_cond_destroy(&s->cond);
#endif

    if (s->is_multicast && (h->flags & AVIO_FLAG_READ)) {
        udp_leave_multicast_group(s->udp_fd, (struct sockaddr *)&s->dest_addr);
    }

    closesocket(s->udp_fd);

    return 0;
}

static int64_t udp_read_pause(URLContext *h, int pause)
{
    UDPContext *s = h->priv_data;

    if (NULL != s) {
        s->quit_flag = (1 == pause) ? 1 : 0;
    }

    return -1;
}

URLProtocol ff_udp_protocol = {
    .name                = "udp",
    .url_open            = udp_open,
    .url_read            = udp_read,
    .url_write           = udp_write,
    .url_close           = udp_close,
    .url_read_pause      = udp_read_pause,
    .url_get_file_handle = udp_get_file_handle,
    .priv_data_size      = sizeof(UDPContext),
    .flags               = URL_PROTOCOL_FLAG_NETWORK,
};
