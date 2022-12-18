/**************************************************************************
 *
 * Copyright (c) 2000-2003 Intel Corporation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * - Neither name of Intel Corporation nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **************************************************************************/



/*!
 * \file
 *
 * \brief Implements the functionality and utility functions
 * used by the Miniserver module.
 *
 * The miniserver is a central point for processing all network requests.
 * It is made of:
 *   - The SSDP sockets for discovery.
 *   - The HTTP listeners for description / control / eventing.
 *
 */

/*lint -save -e* */
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
/*lint -restore * */

#include "config.h"

#include "miniserver.h"

#include "httpreadwrite.h"
#include "ithread.h"
#include "ssdplib.h"
#include "statcodes.h"
#include "ThreadPool.h"
#include "unixutil.h" /* for socklen_t, EAFNOSUPPORT */
#include "upnpapi.h"
#include "upnputil.h"


/*! . */
#define APPLICATION_LISTENING_PORT 49152

struct mserv_request_t {
    /*! Connection handle. */
    SOCKET connfd;
    /*! . */
    struct sockaddr_storage foreign_sockaddr;

       /*l57071/r72104 To store the device handle
                               to which the request belongs
       */

       SOCKET listenSocket;
};

/*! . */
typedef enum {
    /*! . */
    MSERV_IDLE,
    /*! . */
    MSERV_RUNNING,
    /*! . */
    MSERV_STOPPING
} MiniServerState;

/*! . */
uint16_t miniStopSockPort;

MiniServerSockArray gstMiniServerSockArray;

/*!
 * module vars
 */
static MiniServerCallback gGetCallback = NULL;
static MiniServerCallback gSoapCallback = NULL;
static MiniServerCallback gGenaCallback = NULL;
static MiniServerState gMServState = MSERV_IDLE;

void SetHTTPGetCallback(MiniServerCallback callback)
{
    gGetCallback = callback;
}

#ifdef INCLUDE_DEVICE_APIS
void SetSoapCallback(MiniServerCallback callback)
{
    gSoapCallback = callback;
}
#endif /* INCLUDE_DEVICE_APIS */

void SetGenaCallback(MiniServerCallback callback)
{
    gGenaCallback = callback;
}

#ifdef INTERNAL_WEB_SERVER
/*!
 * \brief Based on the type pf message, appropriate callback is issued.
 *
 * \return 0 on Success or HTTP_INTERNAL_SERVER_ERROR if Callback is NULL.
 */
static int dispatch_request(
    /*! [in] Socket Information object. */
    IN SOCKINFO *info,
    /*! [in] HTTP parser object. */
    http_parser_t *hparser)
{
    MiniServerCallback callback;

    switch (hparser->msg.method) {
    /* Soap Call */
    case SOAPMETHOD_POST:
    case HTTPMETHOD_MPOST:
        DLNA_LOGI("[VPPDLNA][%s][%d]:Received a SOAP Action Request From Peer\n"
                ,__FUNCTION__,__LINE__);
        callback = gSoapCallback;
        break;
    /* Gena Call */
    case HTTPMETHOD_NOTIFY:
    case HTTPMETHOD_SUBSCRIBE:
    case HTTPMETHOD_UNSUBSCRIBE:
            DLNA_LOGI("[VPPDLNA][%s][%d]:Received a GENA Request From Peer\n"
                ,__FUNCTION__,__LINE__);
            callback = gGenaCallback;
        break;
    /* HTTP server call */
    case HTTPMETHOD_GET:
    case HTTPMETHOD_POST:
    case HTTPMETHOD_HEAD:
    case HTTPMETHOD_SIMPLEGET:
        DLNA_LOGI("[VPPDLNA][%s][%d]:Received a HTTP Request From Peer\n"
                ,__FUNCTION__,__LINE__);
        callback = gGetCallback;
        break;
    default:
        callback = NULL;
    }
    if (callback == NULL) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    callback(hparser, &hparser->msg, info);

    return 0;
}

/*!
 * \brief Send Error Message.
 */
static UPNP_INLINE void handle_error(
    /*! [in] Socket Information object. */
    SOCKINFO *info,
    /*! [in] HTTP Error Code. */
    int http_error_code,
    /*! [in] Major Version Number. */
    int m_major,
    /*! [in] Minor Version Number. */
    int m_minor)
{
    (void)http_SendStatusResponse(info, http_error_code, m_major, m_minor);
}

/*!
 * \brief Free memory assigned for handling request and unitialize socket
 * functionality.
 */
static void free_handle_request_arg(
    /*! [in] Request Message to be freed. */
    void *args)
{
    struct mserv_request_t *request = (struct mserv_request_t *)args;

    (void)sock_close(request->connfd);
    UPNP_FREE(request);
}

/*!
 * \brief Receive the request and dispatch it for handling.
 */
static void handle_request(
    /*! [in] Request Message to be handled. */
    void *args)
{
    SOCKINFO info;
    int http_error_code = 0;
    int ret_code;
    http_parser_t parser;
    http_message_t *hmsg = NULL;
    int timeout = 30;
    struct mserv_request_t *request = (struct mserv_request_t *)args;
    SOCKET connfd = request->connfd;
    http_header_t *pstHdr;
    memptr value;
    /* Used in case of a keep-alive connection to check if the connection is
    closed properly */
    int bIsMsgRecvComplete = UPNP_FALSE;

    DLNA_LOGI("[VPPDLNA][%s][%d]: Received a Request from Peer on miniserver "
            "socket %d: READING\n",__FUNCTION__,
        __LINE__, connfd );
    /* parser_request_init( &parser ); */ /* LEAK_FIX_MK */
    hmsg = &parser.msg;
    ret_code = sock_init_with_ip(
        &info, connfd, (struct sockaddr *)&request->foreign_sockaddr);
    if (ret_code != UPNP_E_SUCCESS) {
        UPNP_FREE(request);
        httpmsg_destroy(hmsg);
        return;
    }

    do
    {
        /* read */
        hmsg = &parser.msg;
        ret_code = http_RecvMessage(
            &info, &parser, HTTPMETHOD_UNKNOWN, &timeout, &http_error_code, &bIsMsgRecvComplete);

        if (ret_code != 0)
        {
            /* below flag is set only in case of a Keep-Alive connection and
            when the previous message is completely received and handled. */
            if (UPNP_TRUE == bIsMsgRecvComplete)
            {
                /* Connection was idle for longer than 30sec. */
                if (HTTP_BAD_REQUEST == http_error_code)
                {
                    DLNA_LOGV("[VPPDLNA][%s][%d]:Keep-Alive connection timed-out. Closing the connection.\n",
                        __FUNCTION__,__LINE__);
                    http_error_code = 0;
                }
                /* Received a socket close indication while waiting for
                a new message on the connection. */
                else if (0 == http_error_code)
                {
                    DLNA_LOGV("[VPPDLNA][%s][%d]:Connection is closed by peer.\n",
                        __FUNCTION__,__LINE__);
                }
            }
            else if (http_error_code != 0)
            {
                DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To receive the request"
                " HTTP Error Code-%d...\n",__FUNCTION__,__LINE__,http_error_code);
            }
            else
            {
                DLNA_LOGV("[VPPDLNA][%s][%d]: ret_code : %d",__FUNCTION__,__LINE__,ret_code);
            }

            break;
        }

        DLNA_LOGI("[VPPDLNA][%s][%d]:Message Received Successfully. Processing the"
            " Request Now...\n",__FUNCTION__,__LINE__);

        info.listenSocket = request->listenSocket;

        /* If host header is not present in HTTP request, send 400 */
        pstHdr = httpmsg_find_hdr_str(&parser.msg, "Host");
        if (!pstHdr)
        {
            http_error_code = HTTP_BAD_REQUEST;
            break;
        }

        /* dispatch */
        http_error_code = dispatch_request(&info, &parser);
        if (http_error_code != 0) {
            DLNA_LOGE("[VPPDLNA][%s][%d]:dispatch_request Failed with error code-%d"
                " \n",__FUNCTION__,__LINE__,http_error_code);
            break;
        }

        pstHdr = httpmsg_find_hdr_str(&parser.msg, "Connection");

        if (parser.msg.minor_version == HTTP11_MINOR_VERSION)
        {
            if (pstHdr)
            {
                value.buf = pstHdr->value.buf;
                value.length = pstHdr->value.length;

                if ((value.length == strlen("close"))
                    && (0 == strncasecmp(value.buf, "close", value.length)))
                {
                    break;
                }else if(value.length == strlen("Keep-Alive")
                && (0 == strncasecmp(value.buf, "Keep-Alive", value.length)))
                {
                    DLNA_LOGV("[VPPDLNA][%s][%d]: keep Alive",__FUNCTION__,__LINE__);
                }
            }
        }
        else
        {
            /* Always maintain short connections with 1.0 peers */

            break;
        }

        httpmsg_destroy(hmsg);
        bIsMsgRecvComplete = UPNP_TRUE;
    }while(1);

error_handler:
    if (http_error_code > 0) {
        handle_error(&info, http_error_code, HTTP11_MAJOR_VERSION,
            HTTP11_MINOR_VERSION);
    }

    (void)sock_destroy(&info, SD_BOTH);
    httpmsg_destroy(hmsg);
    UPNP_FREE(request);

    DLNA_LOGI("[VPPDLNA][%s][%d]: Processing of Received HTTP Request From Peer"
        "on socket:%d Finished\n",__FUNCTION__,__LINE__,connfd);
}

/*!
 * \brief Initilize the thread pool to handle a request, sets priority for the
 * job and adds the job to the thread pool.
 */
static UPNP_INLINE void schedule_request_job(
    /*! [in] Socket Descriptor on which connection is accepted. */
    SOCKET connfd,
    /*! [in] Clients Address information. */
    struct sockaddr *clientAddr,
    SOCKET listenSocket)
{
    struct mserv_request_t *request;
    ThreadPoolJob job;

    request = (struct mserv_request_t *)UPNP_MALLOC(
        sizeof (struct mserv_request_t));
    if (request == NULL) {
        DLNA_LOGE("[VPPDLNA]:mserv %d: out of memory\n", connfd);
        (void)sock_close(connfd);
        return;
    }

    request->connfd = connfd;
    memcpy(&request->foreign_sockaddr, clientAddr,
        sizeof(request->foreign_sockaddr));
       request->listenSocket = listenSocket;

    /*  ADDED by s00902670 & k00900440
    DLNA_LOGI("[VPPDLNA]:schedule_request_job accept addr:%x port:%x\r\n",
        request->foreign_ip_addr.s_addr,
        request->foreign_ip_port); */

    (void)TPJobInit(&job, (start_routine)handle_request, (void *)request);
    (void)TPJobSetFreeFunction(&job, free_handle_request_arg);
    (void)TPJobSetPriority(&job, MED_PRIORITY);
    if (ThreadPoolAdd(&gMiniServerThreadPool, &job, NULL) != 0) {
        DLNA_LOGE("[VPPDLNA]:mserv %d: cannot schedule request\n", connfd);
        UPNP_FREE(request);
        (void)sock_close(connfd);
        return;
    }
}
#endif

static UPNP_INLINE void fdset_if_valid(SOCKET sock, fd_set *set)
{
    if (sock != INVALID_SOCKET) {
        FD_SET(sock, set);
    }
}

static void web_server_accept(SOCKET lsock, fd_set *set)
{
#ifdef INTERNAL_WEB_SERVER
    SOCKET asock;
    socklen_t clientLen;
    struct sockaddr_storage clientAddr;
    char errorBuffer[ERROR_BUFFER_LEN];

    if (lsock != INVALID_SOCKET && FD_ISSET(lsock, set)) {
        clientLen = sizeof(clientAddr);
        asock = accept(lsock, (struct sockaddr *)&clientAddr,
            &clientLen);
        if (asock == INVALID_SOCKET) {
            strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
            DLNA_LOGE("[VPPDLNA]:miniserver: Error in accept(): %s\n",
                errorBuffer);
        } else {
            /*
               We need to pass the listening socket
               information to the worker thread
               so that the received request
               can be redirected to proper device
            */
            schedule_request_job(asock,
            (struct sockaddr *)&clientAddr, lsock);

            /*End */
        }
    }
#endif /* INTERNAL_WEB_SERVER */
}

static void ssdp_read(SOCKET rsock, fd_set *set)
{
    if (rsock != INVALID_SOCKET && FD_ISSET(rsock, set)) {
        readFromSSDPSocket(rsock);
    }
}

static int receive_from_stopSock(SOCKET ssock, fd_set *set)
{
    ssize_t byteReceived;
    socklen_t clientLen;
    struct sockaddr_storage clientAddr;
    char requestBuf[256];
    char buf_ntop[64];

    if (FD_ISSET(ssock, set)) {
        clientLen = sizeof(clientAddr);
        memset((char *)&clientAddr, 0, sizeof(clientAddr));
        byteReceived = recvfrom(ssock, requestBuf,
            25, 0, (struct sockaddr *)&clientAddr, &clientLen);
        if (byteReceived > 0) {
            requestBuf[byteReceived] = '\0';
            (void)inet_ntop(AF_INET,
                &((struct sockaddr_in*)&clientAddr)->sin_addr,
                buf_ntop, sizeof(buf_ntop));
            DLNA_LOGI("[VPPDLNA]:Received response: %s From host %s \n",
                requestBuf, buf_ntop );
            DLNA_LOGI("[VPPDLNA]:Received multicast packet: \n %s\n",
                requestBuf);
            if (NULL != strstr(requestBuf, "ShutDown")) {
                return 1;
            }
        }
    }

    return 0;
}

/*!
 * \brief Run the miniserver.
 *
 * The MiniServer accepts a new request and schedules a thread to handle the
 * new request. Checks for socket state and invokes appropriate read and
 * shutdown actions for the Miniserver and SSDP sockets.
 */
static void RunMiniServer(
    /*! [in] Socket Array. */
    MiniServerSockArray *miniSock)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    fd_set expSet;
    fd_set rdSet;
    SOCKET maxMiniSock;
    int ret = 0;
    SOCKET stopSock = 0;
    unsigned int uiLoop;

    maxMiniSock = 0;

    /*
        l57071/r72104 Changes Made to support multiple device.
        Begin
    */
    for (uiLoop = 0; uiLoop < DLNA_MAX_DEVICE_MINISERVER; uiLoop++)
    {
        maxMiniSock = Max(maxMiniSock, miniSock->miniServerSock4[uiLoop]);
        maxMiniSock = Max(maxMiniSock, miniSock->miniServerSock6[uiLoop]);
    }
    maxMiniSock = Max(maxMiniSock, miniSock->miniServerStopSock);
    maxMiniSock = Max(maxMiniSock, miniSock->ssdpSock4);
    maxMiniSock = Max(maxMiniSock, miniSock->ssdpSock6);
    maxMiniSock = Max(maxMiniSock, miniSock->ssdpSock6UlaGua);
    for (uiLoop = 0; uiLoop < DLNA_MAX_CTRLPOINT_CLIENT ; uiLoop++)
    {
        maxMiniSock = Max(maxMiniSock, miniSock->ssdpReqSock4[uiLoop]);
        maxMiniSock = Max(maxMiniSock, miniSock->ssdpReqSock6[uiLoop]);
    }

    ++maxMiniSock;

    gMServState = MSERV_RUNNING;

    while (!stopSock) {
        FD_ZERO(&rdSet);
        FD_ZERO(&expSet);
        /* FD_SET()'s */
        FD_SET(miniSock->miniServerStopSock, &expSet);
        FD_SET(miniSock->miniServerStopSock, &rdSet);
        for (uiLoop = 0; uiLoop < DLNA_MAX_DEVICE_MINISERVER; uiLoop++)
        {
            fdset_if_valid(miniSock->miniServerSock4[uiLoop], &rdSet);
            fdset_if_valid(miniSock->miniServerSock6[uiLoop], &rdSet);
        }

        fdset_if_valid(miniSock->ssdpSock4, &rdSet);
        fdset_if_valid(miniSock->ssdpSock6, &rdSet);
        fdset_if_valid(miniSock->ssdpSock6UlaGua, &rdSet);
        for (uiLoop = 0; uiLoop < DLNA_MAX_CTRLPOINT_CLIENT ; uiLoop++)
        {
            fdset_if_valid(miniSock->ssdpReqSock4[uiLoop], &rdSet);
            fdset_if_valid(miniSock->ssdpReqSock6[uiLoop], &rdSet);
        }

        /* select() */
        ret = select((int) (maxMiniSock+1), &rdSet, NULL, &expSet, NULL);
        if (ret == SOCKET_ERROR && errno == EINTR) {
            continue;
        }
        if (ret == SOCKET_ERROR) {
            strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
            #ifndef HI_ADVCA_FUNCTION_RELEASE
            printf("%s,%d,[VPPDLNA]:Error in select(): %s\n",__FILE__,__LINE__,errorBuffer);
            #endif
            DLNA_LOGE("[VPPDLNA]:Error in select(): %s\n", errorBuffer);
            continue;
        }
        else
        {
            for (uiLoop = 0; uiLoop < DLNA_MAX_DEVICE_MINISERVER; uiLoop++)
            {
                web_server_accept(miniSock->miniServerSock4[uiLoop], &rdSet);
                web_server_accept(miniSock->miniServerSock6[uiLoop], &rdSet);
            }
#ifdef INCLUDE_CLIENT_APIS
            for (uiLoop = 0; uiLoop < DLNA_MAX_CTRLPOINT_CLIENT ; uiLoop++)
            {
                ssdp_read(miniSock->ssdpReqSock4[uiLoop], &rdSet);
                ssdp_read(miniSock->ssdpReqSock6[uiLoop], &rdSet);
            }
#endif /* INCLUDE_CLIENT_APIS */
            ssdp_read(miniSock->ssdpSock4, &rdSet);
            ssdp_read(miniSock->ssdpSock6, &rdSet);
            ssdp_read(miniSock->ssdpSock6UlaGua, &rdSet);
            stopSock = receive_from_stopSock(
                miniSock->miniServerStopSock, &rdSet);
        }
    }

    /* Close all sockets. */
    for (uiLoop = 0; uiLoop < DLNA_MAX_DEVICE_MINISERVER; uiLoop++)
    {
      (void)sock_close(miniSock->miniServerSock4[uiLoop]);
      (void)sock_close(miniSock->miniServerSock6[uiLoop]);
    }

    (void)sock_close(miniSock->miniServerStopSock);
    (void)sock_close(miniSock->ssdpSock4);
    (void)sock_close(miniSock->ssdpSock6);
    (void)sock_close(miniSock->ssdpSock6UlaGua);
    for (uiLoop = 0; uiLoop < DLNA_MAX_CTRLPOINT_CLIENT; uiLoop++)
    {
        (void)sock_close(miniSock->ssdpReqSock4[uiLoop]);
        (void)sock_close(miniSock->ssdpReqSock6[uiLoop]);
    }

    gMServState = MSERV_IDLE;
 //  printf("%s,%d out of StopMiniServer\n",__FILE__,__LINE__);
    return;
}

/* End */
/*!
 * \brief Returns port to which socket, sockfd, is bound.
 *
 * \return -1 on error; check errno. 0 if successfull.
 */
int get_port(
    /*! [in] Socket descriptor. */
    SOCKET sockfd,
    /*! [out] The port value if successful, otherwise, untouched. */
    uint16_t *port)
{
    struct sockaddr_storage sockinfo;
    socklen_t len;
    int code;

    len = sizeof(sockinfo);
    code = getsockname(sockfd, (struct sockaddr *)&sockinfo, &len);
    if (code == -1) {
        return -1;
    }
    if (sockinfo.ss_family == AF_INET) {
        *port = ntohs(((struct sockaddr_in*)&sockinfo)->sin_port);
    } else if(sockinfo.ss_family == AF_INET6) {
        *port = ntohs(((struct sockaddr_in6*)&sockinfo)->sin6_port);
    }
    DLNA_LOGI("[VPPDLNA]:sockfd = %d, .... port = %u\n", sockfd, *port);

    return 0;
}

#ifdef INTERNAL_WEB_SERVER
/*!
 * \brief Creates a STREAM socket, binds to INADDR_ANY and listens for
 * incoming connecttions. Returns the actual port which the sockets
 * sub-system returned.
 *
 * Also creates a DGRAM socket, binds to the loop back address and
 * returns the port allocated by the socket sub-system.
 *
 * \return
 *  \li UPNP_E_OUTOF_SOCKET: Failed to create a socket.
 *  \li UPNP_E_SOCKET_BIND: Bind() failed.
 *  \li UPNP_E_LISTEN: Listen() failed.
 *  \li UPNP_E_INTERNAL_ERROR: Port returned by the socket layer is < 0.
 *  \li UPNP_E_SUCCESS: Success.
 */
 /* l57071: testmark: should test this function */
static int get_miniserver_sockets(
    uint16_t listen_port4,
    uint16_t listen_port6,
    OUT uint16_t *actual_listen_port4,  /* as the port maybe change */
    OUT uint16_t *actual_listen_port6,
    OUT SOCKET *pListenfd4,
    OUT SOCKET *pListenfd6)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    struct sockaddr_storage __ss_v4;
    struct sockaddr_in* serverAddr4 = (struct sockaddr_in*)&__ss_v4;
    SOCKET listenfd4;
    uint16_t actual_port4;
#ifdef UPNP_ENABLE_IPV6
    struct sockaddr_storage __ss_v6;
    struct sockaddr_in6* serverAddr6 = (struct sockaddr_in6*)&__ss_v6;
    SOCKET listenfd6;
    uint16_t actual_port6;
#endif
    int ret_code;
    int reuseaddr_on = 0;
    int sockError = UPNP_E_SUCCESS;
    int errCode = 0;

    /* Create listen socket for IPv4/IPv6. An error here may indicate
     * that we don't have an IPv4/IPv6 stack. */

    /* l57071: initial the output parameter */
    *actual_listen_port4 = listen_port4;
    *actual_listen_port6 = listen_port6;
    *pListenfd4 = INVALID_SOCKET;
    *pListenfd6 = INVALID_SOCKET;

    listenfd4 = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd4 == INVALID_SOCKET) {
        return UPNP_E_OUTOF_SOCKET;
    }
#ifdef UPNP_ENABLE_IPV6
    listenfd6 = socket(AF_INET6, SOCK_STREAM, 0);
    if (listenfd6 == INVALID_SOCKET) {
        DLNA_LOGE("[VPPDLNA][%s][:%d]-:socket call failure \r\n",
            __FUNCTION__,__LINE__);
        return UPNP_E_OUTOF_SOCKET;
    }
#endif
    /* As per the IANA specifications for the use of ports by applications
     * override the listen port passed in with the first available. */
    if (listen_port4 < APPLICATION_LISTENING_PORT) {
        listen_port4 = APPLICATION_LISTENING_PORT;
    }
#ifdef UPNP_ENABLE_IPV6
    if (listen_port6 < APPLICATION_LISTENING_PORT) {
        listen_port6 = APPLICATION_LISTENING_PORT;
    }
#endif
    memset(&__ss_v4, 0, sizeof (__ss_v4));
    serverAddr4->sin_family = AF_INET;
    serverAddr4->sin_addr.s_addr = htonl(INADDR_ANY);
#ifdef UPNP_ENABLE_IPV6
    memset(&__ss_v6, 0, sizeof (__ss_v6));
    serverAddr6->sin6_family = AF_INET6;
    serverAddr6->sin6_addr = in6addr_any;
#endif
    /* Getting away with implementation of re-using address:port and
     * instead choosing to increment port numbers.
     * Keeping the re-use address code as an optional behaviour that
     * can be turned on if necessary.
     * TURN ON the reuseaddr_on option to use the option. */
    if (reuseaddr_on) {
        /* THIS IS ALLOWS US TO BIND AGAIN IMMEDIATELY
         * AFTER OUR SERVER HAS BEEN CLOSED
         * THIS MAY CAUSE TCP TO BECOME LESS RELIABLE
         * HOWEVER IT HAS BEEN SUGESTED FOR TCP SERVERS. */
        DLNA_LOGI("[VPPDLNA]:get_miniserver_sockets: resuseaddr is set.\n");
        if (listenfd4 != INVALID_SOCKET) {
            sockError = setsockopt(listenfd4, SOL_SOCKET,
                SO_REUSEADDR,
                (const char *)&reuseaddr_on, sizeof (int));
            if (sockError == SOCKET_ERROR) {
                DLNA_LOGE("[VPPDLNA][%s][:%d]-:setsockopt call failure \r\n",
                    __FUNCTION__,__LINE__);
                (void)sock_close(listenfd4);
#ifdef UPNP_ENABLE_IPV6
                (void)sock_close(listenfd6);
#endif
                return UPNP_E_SOCKET_BIND;
            }
            serverAddr4->sin_port = htons(listen_port4);
            sockError = bind(listenfd4,
                (struct sockaddr *)&__ss_v4,
                sizeof (__ss_v4));
            if (sockError == SOCKET_ERROR) {
                strerror_r(errno, errorBuffer,
                    ERROR_BUFFER_LEN);
                DLNA_LOGE("[VPPDLNA]:get_miniserver_sockets: "
                    "Error in IPv4 bind(): %s\n",
                    errorBuffer);
                (void)sock_close(listenfd4);
#ifdef UPNP_ENABLE_IPV6
                (void)sock_close(listenfd6);
#endif
                /* Bind failed */
                return UPNP_E_SOCKET_BIND;
            }
        }
#ifdef UPNP_ENABLE_IPV6
        if (listenfd6 != INVALID_SOCKET) {
            sockError = setsockopt(listenfd6, SOL_SOCKET,
                SO_REUSEADDR,
            (const char *)&reuseaddr_on, sizeof (int));
            if (sockError == SOCKET_ERROR) {
                DLNA_LOGE("[VPPDLNA][%s][:%d]-:setsockopt call failure \r\n",
                    __FUNCTION__,__LINE__);
                (void)sock_close(listenfd4);
                (void)sock_close(listenfd6);
                return UPNP_E_SOCKET_BIND;
            }
            serverAddr6->sin6_port = htons(listen_port6);
            sockError = bind(listenfd6,
                (struct sockaddr *)&__ss_v6,
                sizeof (__ss_v6));
            if (sockError == SOCKET_ERROR) {
                strerror_r(errno, errorBuffer,
                    ERROR_BUFFER_LEN);
                DLNA_LOGE("[VPPDLNA]:get_miniserver_sockets: "
                    "Error in IPv6 bind(): %s\n",
                    errorBuffer);
                (void)sock_close(listenfd4);
                (void)sock_close(listenfd6);
                /* Bind failed */
                return UPNP_E_SOCKET_BIND;
            }
        }
#endif  /* IPv6 */
    } else {        /* l57071: go into this case */
        if (listenfd4 != INVALID_SOCKET) {
            uint16_t orig_listen_port4 = listen_port4;
            do {
                serverAddr4->sin_port = htons(listen_port4++);
                sockError = bind(listenfd4,
                    (struct sockaddr *)serverAddr4,
                    sizeof(*serverAddr4));
                if (sockError == SOCKET_ERROR) {
#ifdef WIN32
                    errCode = WSAGetLastError();
#else
                    errCode = errno;
#endif
                    if (errno == EADDRINUSE) {
                        errCode = 1;
                    }
                } else {
                    errCode = 0;
                }
            } while (errCode != 0 &&
                 listen_port4 >= orig_listen_port4);   /* reverse */

            if (sockError == SOCKET_ERROR) {
                strerror_r(errno, errorBuffer,
                    ERROR_BUFFER_LEN);
                DLNA_LOGE("[VPPDLNA]:get_miniserver_sockets: "
                    "Error in IPv4 bind(): %s\n",
                    errorBuffer);
                (void)sock_close(listenfd4);
#ifdef UPNP_ENABLE_IPV6
                (void)sock_close(listenfd6);
#endif
                /* Bind failied. */
                return UPNP_E_SOCKET_BIND;
            }
        }
#ifdef UPNP_ENABLE_IPV6
        if (listenfd6 != INVALID_SOCKET) {
            uint16_t orig_listen_port6 = listen_port6;
            do {
                serverAddr6->sin6_port = htons(listen_port6++);
                sockError = bind(listenfd6,
                    (struct sockaddr *)serverAddr6,
                    sizeof(*serverAddr6));
                if (sockError == SOCKET_ERROR) {
#ifdef WIN32
                    errCode = WSAGetLastError();
#else
                    errCode = errno;
#endif
                    if (errno == EADDRINUSE) {
                        errCode = 1;
                    }
                } else {
                    errCode = 0;
                }
            } while (errCode != 0 &&
                 listen_port6 >= orig_listen_port6);
            if (sockError == SOCKET_ERROR) {
                strerror_r(errno, errorBuffer,
                    ERROR_BUFFER_LEN);
                DLNA_LOGE("[VPPDLNA]:get_miniserver_sockets: "
                    "Error in IPv6 bind(): %s\n",
                    errorBuffer);
                (void)sock_close(listenfd4);
                (void)sock_close(listenfd6);
                /* Bind failied. */
                return UPNP_E_SOCKET_BIND;
            }
        }
#endif
    }
    DLNA_LOGI("[VPPDLNA]:get_miniserver_sockets: bind successful\n");

    if (listenfd4 != INVALID_SOCKET) {
        ret_code = listen(listenfd4, SOMAXCONN);
        if (ret_code == SOCKET_ERROR) {
            strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
            DLNA_LOGE("[VPPDLNA]:mserv start: Error in IPv4 listen(): %s\n",
                errorBuffer);
            (void)sock_close(listenfd4);
#ifdef UPNP_ENABLE_IPV6
            (void)sock_close(listenfd6);
#endif
            return UPNP_E_LISTEN;
        }

        ret_code = get_port(listenfd4, &actual_port4);
        if (ret_code < 0) {
            (void)sock_close(listenfd4);
#ifdef UPNP_ENABLE_IPV6
            (void)sock_close(listenfd6);
#endif
            return UPNP_E_INTERNAL_ERROR;
        }

        *actual_listen_port4 = actual_port4;   /* l57071 */
        DLNA_LOGI("[VPPDLNA]:The Actual Listen Port is %d\n", actual_port4); /* k00900440 */
    }
#ifdef UPNP_ENABLE_IPV6
    if (listenfd6 != INVALID_SOCKET) {
        ret_code = listen(listenfd6, SOMAXCONN);
        if (ret_code == SOCKET_ERROR) {
            strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
            DLNA_LOGE("[VPPDLNA]:mserv start: Error in IPv6 listen(): %s\n",
                errorBuffer);
            (void)sock_close(listenfd4);
            (void)sock_close(listenfd6);
            return UPNP_E_LISTEN;
        }
        ret_code = get_port(listenfd6, &actual_port6);
        if (ret_code < 0) {
            (void)sock_close(listenfd4);
            (void)sock_close(listenfd6);
            return UPNP_E_INTERNAL_ERROR;
        }
        *actual_listen_port6 = actual_port6;   /* l57071 */
    }
#endif

    *pListenfd4 = listenfd4;    /* l57071 */
#ifdef UPNP_ENABLE_IPV6
    *pListenfd6 = listenfd6;    /* l57071 */
#endif
    return UPNP_E_SUCCESS;
}

static int get_miniserver_fixed_sockets( IN uint16_t start_port,
    OUT uint16_t *expect_listen_port4,  OUT uint16_t *expect_listen_port6,
    OUT uint16_t *actual_listen_port4,  OUT uint16_t *actual_listen_port6,
    OUT SOCKET *pListenfd4, OUT SOCKET *pListenfd6)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    struct sockaddr_storage __ss_v4;
    struct sockaddr_in* serverAddr4 = (struct sockaddr_in*)&__ss_v4;
    SOCKET listenfd4;

    int lpCount;
    //uint16_t start_port = APPLICATION_LISTENING_PORT;
    int reuseaddr_on = 1;
    int ret_code;
    int sockError = UPNP_E_SUCCESS;
    int errCode = 0;
    int bind_counts = 0;

    //APPLICATION_LISTENING_PORT;
    for (lpCount = 0; lpCount < DLNA_MAX_DEVICE_MINISERVER; lpCount++)
    {
        if(expect_listen_port4[lpCount] == 0)
        {
            actual_listen_port4[lpCount] = start_port;
            expect_listen_port4[lpCount] = start_port;
            start_port ++;
        }
        else
            actual_listen_port4[lpCount] = expect_listen_port4[lpCount];

        listenfd4 = socket(AF_INET, SOCK_STREAM, 0);
        if (listenfd4 == INVALID_SOCKET) {
            return UPNP_E_OUTOF_SOCKET;
        }
        memset(&__ss_v4, 0, sizeof (__ss_v4));
        serverAddr4->sin_family = AF_INET;
        serverAddr4->sin_addr.s_addr = htonl(INADDR_ANY);

        sockError = setsockopt(listenfd4, SOL_SOCKET,SO_REUSEADDR,
            &reuseaddr_on, sizeof (reuseaddr_on));
        if (sockError == SOCKET_ERROR) {
            DLNA_LOGE("[VPPDLNA][%s][:%d]-:setsockopt call failure \r\n",
                __FUNCTION__,__LINE__);
            (void)sock_close(listenfd4);
            return UPNP_E_SOCKET_BIND;
        }


        serverAddr4->sin_port = htons(actual_listen_port4[lpCount]);
        sockError = bind(listenfd4,(struct sockaddr *)&__ss_v4,sizeof (__ss_v4));


        if (sockError == SOCKET_ERROR) {
            strerror_r(errno, errorBuffer,ERROR_BUFFER_LEN);
            DLNA_LOGE("[VPPDLNA]:get_miniserver_fixed_sockets: "
                "Error in IPv4 bind(): %s port:%d ,try next port\n",errorBuffer,actual_listen_port4[lpCount]);
            (void)sock_close(listenfd4);
        /* Bind failed  choose next port*/
            if(expect_listen_port4[lpCount] != 0)
                expect_listen_port4[lpCount] = expect_listen_port4[lpCount] + 1;
            lpCount = lpCount - 1;
            bind_counts ++;
            if(bind_counts >= 50)
            {
                break;
            }
            else
            {
                continue;
            }
            //return UPNP_E_SOCKET_BIND;
        }

        ret_code = listen(listenfd4, SOMAXCONN);
        if (ret_code == SOCKET_ERROR) {
            strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
            DLNA_LOGE("[VPPDLNA]:mserv start: Error in IPv4 listen(): %s\n",
            errorBuffer);
            (void)sock_close(listenfd4);
            return UPNP_E_LISTEN;
        }

        pListenfd4[lpCount] = listenfd4;
        bind_counts = 0;
        DLNA_LOGI("[VPPDLNA]:The Actual Listen Port is %d\n", actual_listen_port4[lpCount]); /* k00900440 */
    }

    return UPNP_E_SUCCESS;
}

#endif /* INTERNAL_WEB_SERVER */

/*!
 * \brief Creates the miniserver STOP socket. This socket is created and
 *  listened on to know when it is time to stop the Miniserver.
 *
 * \return
 * \li \c UPNP_E_OUTOF_SOCKET: Failed to create a socket.
 * \li \c UPNP_E_SOCKET_BIND: Bind() failed.
 * \li \c UPNP_E_INTERNAL_ERROR: Port returned by the socket layer is < 0.
 * \li \c UPNP_E_SUCCESS: Success.
 */
static int get_miniserver_stopsock(
    /*! [in] Miniserver Socket Array. */
    MiniServerSockArray *out)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    struct sockaddr_in stop_sockaddr;
    SOCKET miniServerStopSock = 0;
    int ret = 0;

    miniServerStopSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (miniServerStopSock == INVALID_SOCKET) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in socket(): %s\n", errorBuffer);
        return UPNP_E_OUTOF_SOCKET;
    }
    /* Bind to local socket. */
    memset(&stop_sockaddr, 0, sizeof (stop_sockaddr));
    stop_sockaddr.sin_family = AF_INET;
    stop_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ret = bind(miniServerStopSock, (struct sockaddr *)&stop_sockaddr,
        sizeof(stop_sockaddr));
    if (ret == SOCKET_ERROR) {
        DLNA_LOGE("[VPPDLNA]:Error in binding localhost!!!\n");
        (void)sock_close(miniServerStopSock);
        return UPNP_E_SOCKET_BIND;
    }
    ret = get_port(miniServerStopSock, &miniStopSockPort);
    if (ret < 0) {
        DLNA_LOGE("[VPPDLNA][%s][:%d]-:getsockname call failure \r\n",
            __FUNCTION__,__LINE__);
        (void)sock_close(miniServerStopSock);
        return UPNP_E_INTERNAL_ERROR;
    }
    out->miniServerStopSock = miniServerStopSock;
    out->stopPort = miniStopSockPort;

    return UPNP_E_SUCCESS;
}

static UPNP_INLINE void InitMiniServerSockArray(MiniServerSockArray *miniSocket)
{
    unsigned int uiLoop = 0;
    for (uiLoop = 0; uiLoop < DLNA_MAX_DEVICE_MINISERVER; uiLoop++)
    {
        miniSocket->miniServerSock4[uiLoop] = INVALID_SOCKET;
        miniSocket->miniServerSock6[uiLoop] = INVALID_SOCKET;
        miniSocket->miniServerPort4[uiLoop] = 0;
        miniSocket->miniServerPort6[uiLoop] = 0;
        miniSocket->deviveOccupyFlag[uiLoop] = 0;
    }

    miniSocket->miniServerStopSock = INVALID_SOCKET;
    miniSocket->ssdpSock4 = INVALID_SOCKET;
    miniSocket->ssdpSock6 = INVALID_SOCKET;
    miniSocket->ssdpSock6UlaGua = INVALID_SOCKET;
    miniSocket->stopPort = 0;
    miniSocket->miniServerPort4[0] = 0;
    for (uiLoop = 0; uiLoop < DLNA_MAX_CTRLPOINT_CLIENT ; uiLoop++)
    {
        miniSocket->ssdpReqSock4[uiLoop] = INVALID_SOCKET;
        miniSocket->ssdpReqSock6[uiLoop] = INVALID_SOCKET;
        miniSocket->ctrlpntOccupyFlag[uiLoop] = 0;
    }
}

static UPNP_INLINE void closeAllMiniServerSocket(MiniServerSockArray *miniSocket)
{
    unsigned int uiLoop;

    /* L57071: checkmark: whether need to use INTERNAL_WEB_SERVER to control,
        can discuss, suggest don't use as it is free resource */
    for (uiLoop = 0; uiLoop < DLNA_MAX_DEVICE_MINISERVER; uiLoop++)
    {
        (void)sock_close(miniSocket->miniServerSock4[uiLoop]);
        (void)sock_close(miniSocket->miniServerSock6[uiLoop]);
    }

    (void)sock_close(miniSocket->miniServerStopSock);
    (void)sock_close(miniSocket->ssdpSock4);
    (void)sock_close(miniSocket->ssdpSock6);
    (void)sock_close(miniSocket->ssdpSock6UlaGua);
    for (uiLoop = 0; uiLoop < DLNA_MAX_CTRLPOINT_CLIENT ; uiLoop++)
    {
        (void)sock_close(miniSocket->ssdpReqSock4[uiLoop]);
        (void)sock_close(miniSocket->ssdpReqSock6[uiLoop]);
    }

    /* after close, initial the miniSocket */
    InitMiniServerSockArray(miniSocket);
    return;
}

int StartMiniServer(
    uint16_t *listen_port4,
    uint16_t *listen_port6,
    uint16_t startport
    )
{
    int ret_code;
    int count;
    int lpCount;
    int itmpLoop = 0;
    int max_count = 10000;
    ThreadPoolJob job;
    unsigned int iDcount = 0;
    struct Handle_Info *HInfo = NULL;

    HInfo = HInfo;
    itmpLoop = itmpLoop;
    iDcount = iDcount;

    if (gMServState != MSERV_IDLE) {
        /* miniserver running. */
        return UPNP_E_INTERNAL_ERROR;
    }

    /*
       l57071/r72104
       To support Multiple Device We need to store the
       listen port and socket information globaly
       Begin
    */
    InitMiniServerSockArray(&gstMiniServerSockArray);
#ifdef INTERNAL_WEB_SERVER
    /* V4 and V6 http listeners. */
#if 0
    for (lpCount = 0; lpCount < DLNA_MAX_DEVICE_MINISERVER; lpCount++)
    {
        ret_code = get_miniserver_sockets(
                        listen_port4[lpCount],
                        listen_port6[lpCount],
                        &(gstMiniServerSockArray.miniServerPort4[lpCount]),
                        &(gstMiniServerSockArray.miniServerPort6[lpCount]),
                        &(gstMiniServerSockArray.miniServerSock4[lpCount]),
                        &(gstMiniServerSockArray.miniServerSock6[lpCount]));
        /* L57071: if return failure, should close all the socket */
        if (ret_code != UPNP_E_SUCCESS)
        {
            /* L57071: close socket */
            closeAllMiniServerSocket(&gstMiniServerSockArray);
            return ret_code;
        }

        listen_port4[lpCount] = gstMiniServerSockArray.miniServerPort4[lpCount];
        listen_port6[lpCount] = gstMiniServerSockArray.miniServerPort6[lpCount];
    }
#endif
    //get sockets
    get_miniserver_fixed_sockets(startport,listen_port4,listen_port6,
        gstMiniServerSockArray.miniServerPort4, gstMiniServerSockArray.miniServerPort6,
        gstMiniServerSockArray.miniServerSock4, gstMiniServerSockArray.miniServerSock6);


    /* End */
#endif
    /* Stop socket (To end miniserver processing). */
    /* l57071: it is not useful for stopsock, reserve */
    ret_code = get_miniserver_stopsock(&gstMiniServerSockArray);
    if (ret_code != UPNP_E_SUCCESS)
    {
        closeAllMiniServerSocket(&gstMiniServerSockArray);
        return ret_code;
    }

    /* SSDP socket for discovery/advertising. */
    ret_code = get_ssdp_sockets(&gstMiniServerSockArray);
    if (ret_code != UPNP_E_SUCCESS)
    {
        closeAllMiniServerSocket(&gstMiniServerSockArray);
        return ret_code;
    }
    (void)TPJobInit(&job, (start_routine)RunMiniServer, (void *)&gstMiniServerSockArray);
    (void)TPJobSetPriority(&job, MED_PRIORITY);
    (void)TPJobSetFreeFunction(&job, (free_routine)free);
    ret_code = ThreadPoolAddPersistent(&gMiniServerThreadPool, &job, NULL);
    if (ret_code < 0) {
        closeAllMiniServerSocket(&gstMiniServerSockArray);
        return UPNP_E_OUTOF_MEMORY;
    }
    /* Wait for miniserver to start. */
    count = 0;
    while (gMServState != MSERV_RUNNING && count < max_count) {
        /* 0.05s */
        (void)usleep(50 * 1000); //comment out by l00138489 20120313
        count++;
    }
    if (count >= max_count)
    {
        closeAllMiniServerSocket(&gstMiniServerSockArray);
        return UPNP_E_INTERNAL_ERROR;
    }

    return UPNP_E_SUCCESS;
}

int StopMiniServer()
{
    char errorBuffer[ERROR_BUFFER_LEN];
    socklen_t socklen = sizeof (struct sockaddr_in);
    SOCKET sock;
    struct sockaddr_in ssdpAddr;
    char buf[256] = "ShutDown";
    size_t bufLen = strlen(buf);
/*l00138489 20120308*/
//DTS2012121001927
#if 1
    if(gMServState == MSERV_RUNNING) {
        gMServState = MSERV_STOPPING;
    }

    else {
        return 0;
    }

#else
    gMServState = MSERV_STOPPING;
#endif
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:SSDP_SERVER: StopSSDPServer: Error in socket() %s\n",
            errorBuffer);
        return 0;
    }
    while(gMServState != MSERV_IDLE) {
        ssdpAddr.sin_family = AF_INET;
        ssdpAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        ssdpAddr.sin_port = htons(miniStopSockPort);
        (void)sendto(sock, buf, bufLen, 0,
            (struct sockaddr *)&ssdpAddr, socklen);
       // (void)usleep(1000); //comment out by l00138489 20120313
        if (gMServState == MSERV_IDLE) {
            break;
        }
        //(void)isleep(1); //comment out by l00138489 20120313
    }
    (void)sock_close(sock);
  // printf("%s,%d out of StopMiniServer\n",__FILE__,__LINE__);
    return 0;
}
