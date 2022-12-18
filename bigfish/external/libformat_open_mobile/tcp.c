/*
 * TCP protocol
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
#include "avformat.h"
#include "libavutil/parseutils.h"
#include <unistd.h>
#include "internal.h"
#include "network.h"
#include "os_support.h"
#include "url.h"
#if HAVE_POLL_H
#include <poll.h>
#endif
#include <sys/time.h>

#include <pthread.h>
#include <netinet/tcp.h>
#include <asm/socket.h>
#include <sys/select.h>
#include "libavutil/avstring.h"

#ifndef SOL_TCP   //wkf34645 for linux compile
#define SOL_TCP 6
#endif

#define TCP_ZERO_TIME_OUT (2500000) // 2.5 second
#define __FILE_NAME__     av_filename(__FILE__)

typedef struct TCPContext {
    int fd;
    int quit_flag;  //z00180556 quit immediately, while seeking
} TCPContext;

typedef struct TCPThread_DATA_S {
    pthread_t         thid;
    int               fdmain[2],fdthread[2];
    char              hostname[1024];
    char              portstr[10];
    struct addrinfo*  ai;
    int               errcode;
} TCPThread_S;

static int ipv6_works()
{
    static int ipv6_works = -1;

    if (-1 == ipv6_works) {
        /* probe to see if we have a working IPv6 stack */
        int fd = socket(AF_INET6, SOCK_DGRAM, 0);
        if (fd < 0) {
            /* an ipv6 address was requested but we can't get/use one */
            ipv6_works = 0;
        } else {
            ipv6_works = 1;
            closesocket(fd);
        }
    }

    return (ipv6_works>0)?1:0;
}

//wkf34645 get DNS use thread
static void tcp_getAddrInfo(void *arg)
{
    if (arg == NULL)
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] thread, Args is null\n",__FILE_NAME__,__LINE__);
        return;
    }

    TCPThread_S *pstThread = (TCPThread_S*)arg;
    struct addrinfo hints, *ai = NULL;
    char hostname[1024];
    char portstr[10];
    char cmsg;
    int ret = 0, errcode,addr;
    int fd1[2],fd2[2];
    struct timeval tv;
    fd_set rfds;

    memcpy(hostname,pstThread->hostname, sizeof(hostname));
    memcpy(portstr,pstThread->portstr, sizeof(portstr));
    hostname[1023] = 0;
    portstr[9] = 0;
    errcode = 0;
    fd1[0] = pstThread->fdmain[0];
    fd1[1] = pstThread->fdmain[1];
    fd2[0] = pstThread->fdthread[0];
    fd2[1] = pstThread->fdthread[1];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    av_log(NULL, AV_LOG_ERROR, "[%s:%d] thread, hostname:%s,port:%s\n",__FILE_NAME__,__LINE__,hostname,portstr);

    cmsg = 1;
    ret = write(fd1[1],&cmsg,1);
    if(ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] write msg failed:%s\n",__FILE_NAME__,__LINE__,strerror(errno));
    }

    hints.ai_family = AF_INET;
    #if 0
    if ((hints.ai_family != AF_INET) && !IPv6_Works())
    {
        hints.ai_family = AF_INET;
    }
    #endif

    ret = getaddrinfo(hostname, portstr,&hints,&ai);

    if (ret)
    {
        errcode = ff_neterrno();
        cmsg = 0;
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret=%d,errcode:%d\n",__FILE_NAME__,__LINE__,ret,errcode);
    }

    ret = write(fd1[1],&cmsg,1);
    if(ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] write msg failed:%s\n",__FILE_NAME__,__LINE__,strerror(errno));
    }

    ret = 0;
    cmsg = 0;

    while (1)
    {
        FD_ZERO(&rfds);
        FD_SET(fd2[0], &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 200 * 1000;
        ret = select(fd2[0] + 1, &rfds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(fd2[0], &rfds))
        {
            ret = read(fd2[0],&cmsg,1);
            ret = (ret <0)? 0 : cmsg;
            break;
        }

        usleep(20*1000);
    }

    if (ret > 0)
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d]\n",__FILE_NAME__,__LINE__);
        if (NULL != ai && errcode == 0)
        {
            freeaddrinfo(ai);
        }
    }
    else
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] errcode:%d,ai:0x%x\n",__FILE_NAME__,__LINE__,errcode,ai);
        pstThread->ai = ai;
        pstThread->errcode = errcode;
    }

    cmsg = 1;
    ret = write(fd1[1],&cmsg,1);
    if(ret < 0)
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] write msg failed:%s\n",__FILE_NAME__,__LINE__,strerror(errno));
    }

    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    av_log(NULL, AV_LOG_ERROR, "[%s:%d] thread exit!\n",__FILE_NAME__,__LINE__);
    pthread_detach(pthread_self()); //thread quit
}

//wkf34645 send sync packet for connection detection
//return user defined error code
static int tcp_set_keepAlive(int fd, int start, int interval, int count)
{
    int keepAlive = 1;
    if (fd < 0 || start < 0 || interval < 0 || count < 0) return -1;
    //use sync packect, set keepAlive=0 to disable it
    if(setsockopt(fd,SOL_SOCKET,SO_KEEPALIVE,(void*)&keepAlive,sizeof(keepAlive)) == -1)
    {
        return -2;
    }
    //set timeout value, then send 1st sync packet
    if(setsockopt(fd,SOL_TCP,TCP_KEEPIDLE,(void *)&start,sizeof(start)) == -1)
    {
        return -3;
    }
    //time interval of next sync packet
    if(setsockopt(fd,SOL_TCP,TCP_KEEPINTVL,(void *)&interval,sizeof(interval)) == -1)
    {
        return -4;
    }
    //sync packet counts for TCP disconnection
    if(setsockopt(fd,SOL_TCP,TCP_KEEPCNT,(void *)&count,sizeof(count)) == -1)
    {
        return -5;
    }
    return 0;
}

/* return non zero if error */
static int tcp_open(URLContext *h, const char *uri, int flags)
{
    struct addrinfo hints, *ai, *cur_ai;
    struct sockaddr_in *soketaddr = NULL;
    int port, fd = -1;
    TCPContext *s = h->priv_data;
    fd_set rfds;
    int listen_socket = 0;
    const char *p;
    char buf[256];
    int ret = 0;
    socklen_t optlen;
    int timeout = 10;
    char hostname[1024],proto[1024],path[1024];
    char portstr[10];
    int64_t time_start = av_gettime();
    TCPThread_S stThread;
    int ret_getinfo;
    pthread_attr_t attr;
    int fd1[2],fd2[2];
    char cmsg;
    struct timeval tv;
    int is_thread;
    int retry_in_progress = 0;
    char errbuf[128];

    //h00186041, add thread to get AddrInfo to avoid ANR
    memset(&stThread, 0, sizeof(TCPThread_S));
    av_url_split(proto, sizeof(proto), NULL, 0, stThread.hostname, sizeof(stThread.hostname),
        &port, path, sizeof(path), uri);
    if (av_strcmp(proto,"tcp") || port <= 0 || port >= 65536)
        return AVERROR(EINVAL);

    snprintf(stThread.portstr, sizeof(stThread.portstr), "%d", port);
    if (ff_check_interrupt(&h->interrupt_callback))
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] exit\n",__FILE_NAME__,__LINE__);
        return AVERROR_EXIT;
    }

    is_thread = 1;
    ret = pthread_attr_init(&attr);
    ret |= pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (ret)
    {
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret_cond=%d\n",__FILE_NAME__,__LINE__,ret);
        is_thread = 0;
        pthread_attr_destroy(&attr);
    }

    if (is_thread)
    {
        ret = pipe(fd1);
        ret |= pipe(fd2);
        if (ret < 0)
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret_cond=%d, errno = %d\n",__FILE_NAME__,__LINE__,ret, errno);
            is_thread = 0;
            pthread_attr_destroy(&attr);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);
            return AVERROR(EIO); //h00212929 add, only use asyn thread way.
                                 //sync will cause ANR[haimeidi]
        }
    }

    if (is_thread)
    {
        stThread.fdmain[0] = fd1[0];
        stThread.fdmain[1] = fd1[1];
        stThread.fdthread[0] = fd2[0];
        stThread.fdthread[1] = fd2[1];

        ret = pthread_create(&stThread.thid, &attr, (void *)tcp_getAddrInfo, &stThread);
        if (ret != 0)
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] pthread_create failed\n",__FILE_NAME__,__LINE__);
            is_thread = 0;
            pthread_attr_destroy(&attr);
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            close(fd2[1]);
        }
    }

    if (is_thread)
    {
        read(stThread.fdmain[0],&cmsg,1);
        cmsg = 0;
        ret_getinfo = -1;

        while (1)
        {
            FD_ZERO(&rfds);
            FD_SET(stThread.fdmain[0], &rfds);
            tv.tv_sec = 0;
            tv.tv_usec = 200 * 1000;
            ret = select(stThread.fdmain[0] + 1, &rfds, NULL, NULL, &tv);
            if (ret > 0 && FD_ISSET(stThread.fdmain[0], &rfds))
            {
                ret = read(stThread.fdmain[0],&cmsg,1);
                if (ret <= 0)
                {
                    av_log(NULL, AV_LOG_ERROR, "[%s:%d]\n",__FILE_NAME__,__LINE__);
                    cmsg = 0;
                }
                ret_getinfo = cmsg;
                break;
            }

            if (ff_check_interrupt(&h->interrupt_callback))
            {
                break;
            }

            usleep(10*1000);
        }

        cmsg = (ret_getinfo < 0) ? 1 : 0;
        ret = write(stThread.fdthread[1],&cmsg,1);

        if(ret < 0)
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] write msg failed:%s\n",__FILE_NAME__,__LINE__,strerror(errno));
        }

        pthread_attr_destroy(&attr);

        if (ret_getinfo != -1)
        {
            read(stThread.fdmain[0],&cmsg,1);
        }

        if (ret_getinfo <= 0)
        {
            ret = (ret_getinfo == 0)? stThread.errcode : AVERROR(EIO);
            return ret;
        }
    }
    else
    {
        if (getaddrinfo(stThread.hostname, stThread.portstr, &hints, &stThread.ai))
        {
            ret = ff_neterrno();
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret=%d\n",__FILE_NAME__,__LINE__,ret);
            return ret;
        }
    }

    av_log(NULL, AV_LOG_ERROR, "[%s:%d] get addrinfo ok,ret=%d\n",__FILE_NAME__,__LINE__,ret);

    cur_ai = stThread.ai;
    ai = stThread.ai;

    p = strchr(uri, '?');
    if (p) {
        if (av_find_info_tag(buf, sizeof(buf), "listen", p))
            listen_socket = 1;
        if (av_find_info_tag(buf, sizeof(buf), "timeout", p)) {
            timeout = strtol(buf, NULL, 10);
        }
    }

 restart:
    ret = AVERROR(EIO);
    fd = socket(cur_ai->ai_family, cur_ai->ai_socktype, cur_ai->ai_protocol);
    if (fd < 0)
    {
        ret = ff_neterrno();
        av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret=%d\n",__FILE_NAME__,__LINE__,ret);
        goto fail;
    }

    if (listen_socket) {
        int fd1;
        ret = bind(fd, cur_ai->ai_addr, cur_ai->ai_addrlen);
        listen(fd, 1);
        fd1 = accept(fd, NULL, NULL);
        closesocket(fd);
        fd = fd1;
        ff_socket_nonblock(fd, 1);
    } else {
 redo:
        ff_socket_nonblock(fd, 1);
        ret = tcp_set_keepAlive(fd, 45, 5, 3);//z00180556 user set timeout value
        if (ret != 0)
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] set_tcp_keepAlive failed,ret=%d\n",__FILE_NAME__,__LINE__,ret);
        }
        ret = connect(fd, cur_ai->ai_addr, cur_ai->ai_addrlen);
    }

    if (ret < 0) {
        struct pollfd p = {fd, POLLOUT, 0};
        ret = ff_neterrno();
        if (ret == AVERROR(EINTR)) {
            if (ff_check_interrupt(&h->interrupt_callback)) {
                ret = AVERROR_EXIT;
                goto fail1;
            }
            goto redo;
        }
        if (ret != AVERROR(EINPROGRESS) &&
            ret != AVERROR(EAGAIN))
        {
            ret = ff_neterrno();
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] connect ret=%d, not EAGAIN and not EINPROGRESS,go to fail!\n",__FILE_NAME__,__LINE__,ret);
            goto fail;
        }

        /* wait until we are connected or until abort */
        while (timeout--) {
            if (ff_check_interrupt(&h->interrupt_callback)) {
                ret = AVERROR_EXIT;
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret=%d\n",__FILE_NAME__,__LINE__,ret);
                goto fail1;
            }
            ret = poll(&p, 1, 300);
            if (ret > 0)
                break;

            usleep(10*1000);
        }
        if (ret <= 0) {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] wait for connectting time out,ret=%d\n",
                    __FILE_NAME__, __LINE__, ret);
            //ret = AVERROR(ETIMEDOUT);
            ret = AVERROR(EAGAIN);
            goto fail;
        }
        /* test error */
        optlen = sizeof(ret);
        getsockopt (fd, SOL_SOCKET, SO_ERROR, &ret, &optlen);
        if (ret != 0) {
            av_log(h, AV_LOG_ERROR,
                   "TCP connection to %s:%d failed: %s, ret:%d\n",
                   hostname, port, strerror(ret), ret);
            /**
             * The C function getsockopt lets you get the error codes with the
             * option SO_ERROR. The possible error numbers are defined in the
             * global errno.h. The relevant values are as flow:
             */
            ret = AVERROR(ret);
            switch (ret) {
            case AVERROR(ECONNREFUSED): /* Connection refused */
            case AVERROR(EHOSTDOWN):    /* Host is down */
            case AVERROR(EHOSTUNREACH): /* No route to host */
            case AVERROR(ETIMEDOUT):    /* Connection timed out */
                break;
            case AVERROR(EALREADY):     /* Operation already in progress */
            case AVERROR(EINPROGRESS):  /* Operation now in progress */
                if (retry_in_progress++ < 3)
                {
                    av_log(h, AV_LOG_ERROR, "Connection in progress, try again:%d", retry_in_progress);
                    goto redo;
                }
                break;
            default:
                break;
            }

            errbuf[0] = 0;
            av_strerror(ret, errbuf, sizeof(errbuf));
            ret = ff_neterrno();
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] tcp connect fail,ret=%d, err=%s\n",__FILE_NAME__,__LINE__,ret, errbuf);
            goto fail;
        }
    }
    h->is_streamed = 1;
    s->fd = fd;
    s->quit_flag = 0;

    /* Get ip address */
    soketaddr = (struct sockaddr_in *)cur_ai->ai_addr;
    av_strlcpy(&h->ipaddr, inet_ntoa(soketaddr->sin_addr), sizeof(h->ipaddr));

    freeaddrinfo(ai);
    return 0;

 fail:
    if (cur_ai->ai_next) {
        /* Retry with the next sockaddr */
        cur_ai = cur_ai->ai_next;
        if (fd >= 0)
            closesocket(fd);
        goto restart;
    }
 fail1:
    if (fd >= 0)
        closesocket(fd);
    freeaddrinfo(ai);
    av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret=%d\n",__FILE_NAME__,__LINE__,ret);
    return ret;
}

static int tcp_read(URLContext *h, uint8_t *buf, int size)
{
    TCPContext *s = h->priv_data;
    int len, fd_max, ret,count = 0, count_timeout = 0;
    fd_set rfds;
    struct timeval tv;
    int64_t start_time = 0;

    while(1)
    {
        if (ff_check_interrupt(&(h->interrupt_callback)))
        {
            av_log(NULL, AV_LOG_ERROR, "tcp_read check interrupt, exit read! \n");
            return AVERROR_EXIT; //z00180556 re-connect
        }

        if (NULL != s && 1 == s->quit_flag)
        {
            return -1;
        }

        fd_max = s->fd;
        FD_ZERO(&rfds);
        FD_SET(s->fd, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 50 * 1000;
        ret = select(fd_max + 1, &rfds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(s->fd, &rfds))
        {
            len = recv(s->fd, buf, size, 0);
            if (len < 0) {
                if (ff_neterrno() != AVERROR(EINTR) &&
                    ff_neterrno() != AVERROR(EAGAIN))
                    return ff_neterrno();
            } else {
                // h00186041, add timeout while read data is 0.
                if (len == 0)
                {
                    if (count == 0)
                        start_time = av_gettime();
                    if (count > 0 && llabs(av_gettime() - start_time) > TCP_ZERO_TIME_OUT)
                    {
                        av_log(NULL, AV_LOG_ERROR, "%s,%d, tcp read return 0 \n", __FILE__, __LINE__);
                        return len;
                    }
                    count++;
                    usleep(10*1000);
                }
                else
                    return len;
            }
        }
        else if (ret < 0)
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret:%d\n",__FILE_NAME__,__LINE__,ret);
            if (ff_neterrno() == AVERROR(EINTR))
            {
                usleep(10*1000);
                continue;
            }
            return -1;
        }
        else
        {
            //modify for cts, chunked, skyplay time out too short cause quit play bug.
            if(count_timeout++ >= 300)   // 15s for experience
            //if (count_timeout++ >= 30)
            {
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] Tcp_read timeout, ret:%d, count = %d\n",
                    __FILE_NAME__, __LINE__, ret, count_timeout);
                return 0;
            }
        }
    }//end while(1)
}

static int tcp_write(URLContext *h, uint8_t *buf, int size)
{
    TCPContext *s = h->priv_data;
    int ret, size1, fd_max, len;
    fd_set wfds;
    struct timeval tv;
    size1 = size;

    while (size > 0)
    {
        if (NULL != s && 1 == s->quit_flag)
            return AVERROR(EINTR);

        if (ff_check_interrupt(&(h->interrupt_callback)))
            return AVERROR_EXIT; //h00212929 modfy for rtsp exit,will cause dead-loop

        fd_max = s->fd;
        FD_ZERO(&wfds);
        FD_SET(s->fd, &wfds);
        tv.tv_sec = 0;
        tv.tv_usec = 100 * 1000;
        ret = select(fd_max + 1, NULL, &wfds, NULL, &tv);

        if (ret > 0 && FD_ISSET(s->fd, &wfds))
        {
            len = send(s->fd, buf, size, 0);
            if (len < 0) {
                av_log(NULL, AV_LOG_ERROR, "[%s:%d] send:%d,errno:%d\n",__FILE_NAME__,__LINE__,len,ff_neterrno());
                if (ff_neterrno() != AVERROR(EINTR) &&
                    ff_neterrno() != AVERROR(EAGAIN))
                    return ff_neterrno();
                continue;
            }
            size -= len;
            buf += len;
        }
        else if (ret < 0)
        {
            ret = ff_neterrno();
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] ret:%d\n",__FILE_NAME__,__LINE__,ret);
            if (ff_neterrno() == AVERROR(EINTR))
            {
                usleep(20*1000);
                continue;
            }
            return -1;
        }
        else
        {
            usleep(10*1000);
        }
    }//end while

    return (size1 - size);
}

static int tcp_close(URLContext *h)
{
    TCPContext *s = h->priv_data;
    closesocket(s->fd);
    return 0;
}

static int tcp_get_file_handle(URLContext *h)
{
    TCPContext *s = h->priv_data;
    return s->fd;
}

static int64_t tcp_read_pause(URLContext *h, int pause)
{
    TCPContext *s = h->priv_data;

    if (NULL != s) {
        s->quit_flag = (1 == pause) ? 1 : 0;
    }

    return -1;
}

URLProtocol ff_tcp_protocol = {
    .name                = "tcp",
    .url_open            = tcp_open,
    .url_read            = tcp_read,
    .url_write           = tcp_write,
    .url_close           = tcp_close,
    .url_read_pause      = tcp_read_pause,
    .url_get_file_handle = tcp_get_file_handle,
    .priv_data_size      = sizeof(TCPContext),
    .flags               = URL_PROTOCOL_FLAG_NETWORK,
};
