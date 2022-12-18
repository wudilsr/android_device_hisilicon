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
 * \addtogroup SSDPlib
 *
 * @{
 *
 * \file
 */

/*lint -save -e* */
#include <assert.h>
#include <stdio.h>
#include <string.h>
/*lint -restore * */


#include "config.h"

#ifdef INCLUDE_DEVICE_APIS
#if EXCLUDE_SSDP == 0

#include "httpparser.h"
#include "httpreadwrite.h"
#include "ssdplib.h"
#include "statcodes.h"
#include "ThreadPool.h"
#include "unixutil.h"
#include "upnpapi.h"
#include "UpnpInet.h"
#include "upnpdebug.h"

#define MSGTYPE_SHUTDOWN    0
#define MSGTYPE_ADVERTISEMENT   1
#define MSGTYPE_REPLY       2
#define TIME_BETWEEN_SSDP_PACKET 30
/* j70578 - for using different ssdp port */
int SSDP_PORT = 1900;

void SetSsdpPort( int port);

void SetSsdpPort( int port)
{
    /* set SSDP port for test purpose only */
    if (port > 0 && port < 65535)
        SSDP_PORT = port;

    return;
}

void *advertiseAndReplyThread(void *data)
{
    SsdpSearchReply *arg = (SsdpSearchReply *) data;

    (void)AdvertiseAndReply(0, arg->handle,
              arg->event.RequestType,
              (struct sockaddr *)&arg->dest_addr,
              arg->event.DeviceType,
              arg->event.UDN, arg->event.ServiceType, arg->MaxAge);
    UPNP_FREE(arg);

    return NULL;
}

#ifdef INCLUDE_DEVICE_APIS
void ssdp_handle_device_request(http_message_t *hmsg, struct sockaddr_storage *dest_addr)
{
#define MX_FUDGE_FACTOR 10
    int handle = 0;
    struct Handle_Info *dev_info = NULL;
    memptr hdr_value;
    int mx = 0;
    char save_char;
    SsdpEvent event;
    int ret_code;
    SsdpSearchReply *threadArg = NULL;
    ThreadPoolJob job;
    int replyTime;
    int maxAge;
    int usn_found = 0;
    http_header_t *hostHdr;
    int isMultiCast = 0;
    UpnpDevice_Handle devcHdlIdx;
    struct Handle_Info *devcHndInfo;
    char ipv4_addr[64] = {0};
    char port[12];
    uint16_t soure_port;

     usn_found = usn_found;
     handle = handle;
     dev_info = dev_info;
     DLNA_LOGV("[VPPDLNA][%s][%d]:\nInside ssdp_handle_device_request to handle "
            "SSDP m-search request sent by the control points\n",__FUNCTION__,
                __LINE__);

    /* We need to validate the source port if its > 1024 and != 1900 */

    if (dest_addr->ss_family == AF_INET) {
        soure_port = ntohs(((struct sockaddr_in*)dest_addr)->sin_port);
    } else if(dest_addr->ss_family == AF_INET6) {
        soure_port = ntohs(((struct sockaddr_in6*)dest_addr)->sin6_port);
    }

    if(soure_port <= 1024 || soure_port == 1900){
         //DLNA_LOGE("[VPPDLNA][%s][%d]-: The M-SEARCH request is received "
         //   "From a source port which is %u (<=1024) or (==1900)"
         //   " so we will ignore this M-SEARCH request\n",
         //   __FUNCTION__,__LINE__, soure_port);
        return;
    }

    DLNA_LOGV("[VPPDLNA][%s][%d]-: The m-search request is being received from "
            "the source port-%u", __FUNCTION__,__LINE__,soure_port);

    /* check man hdr. */
    if (httpmsg_find_hdr(hmsg, HDR_MAN, &hdr_value) == NULL ||
        memptr_cmp(&hdr_value, "\"ssdp:discover\"") != 0){
        /* bad or missing hdr. */
        DLNA_LOGE("[VPPDLNA][%s][%d]:MAN header is either missing in the search"
            " request or it has a value other than ssdp:discover\n",
            __FUNCTION__,__LINE__);
        return;
    }

    /* MX header. */
    if (httpmsg_find_hdr(hmsg, HDR_MX, &hdr_value) == NULL)
    {
        DLNA_LOGE("[VPPDLNA][%s][%d]:MX header is missing in the search"
            " request\n",__FUNCTION__,__LINE__);
        return;
    }
    else if ((mx = raw_to_int(&hdr_value, 10)) < 0)
    {
        DLNA_LOGE("[VPPDLNA][%s][%d]:MX header in the search"
            " request has a invalid value -%d\n",
            __FUNCTION__,__LINE__,mx);
        return;
    }

    /* ST header. */
    if (httpmsg_find_hdr(hmsg, HDR_ST, &hdr_value) == NULL){
        DLNA_LOGE("[VPPDLNA][%s][%d]:ST header is  missing in the search"
            " request\n",__FUNCTION__,__LINE__);
        return;
    }

    save_char = hdr_value.buf[hdr_value.length];
    hdr_value.buf[hdr_value.length] = '\0';
    ret_code = ssdp_request_type(hdr_value.buf, &event);
    /* restore. */
    hdr_value.buf[hdr_value.length] = save_char;
    if (ret_code == -1)
    {
        /* bad ST header. */
        DLNA_LOGE("[VPPDLNA][%s][%d]:Received bad ST header value in the search"
            " request \n", __FUNCTION__,__LINE__);
        return;
    }
      /*
          r72104
          Find the HOST to determine whether its a Multicast
          or unicast m-search. For Multicast m-search
          we have to provide details of the all root devices
          we have as we expose two devices to the network
          DMS and DMR ---Begin
      */

      hostHdr = httpmsg_find_hdr(hmsg, HDR_HOST, &hdr_value);
      if (NULL == hostHdr){
        DLNA_LOGE("[VPPDLNA][%s][%d]:HOST header is  missing in the search"
            " request \n", __FUNCTION__,__LINE__);
        return;
      }

      /* j70578 - For using different SSDP port */
      memset(port,0,sizeof(port));
      snprintf(port, sizeof(port),"%u", SSDP_PORT);

      memcpy (ipv4_addr, "239.255.255.250:", strlen("239.255.255.250:"));
      memcpy (ipv4_addr + strlen(ipv4_addr), port, strlen(port));

      if (!memcmp(hdr_value.buf, ipv4_addr, hdr_value.length)){
            isMultiCast = 1;
            DLNA_LOGI("[VPPDLNA][%s][%d]:Its a Multicast m-search request\n",
                __FUNCTION__,__LINE__);
      }

      if (isMultiCast){

        DLNA_LOGV("[VPPDLNA][%s][%d]:\n Received a Multicast M-SEARCH Request "
                    "\n",__FUNCTION__,__LINE__);

        /* Iterate Through The device List And send 200 OK
            response for each of the device */
        for (devcHdlIdx = 1; devcHdlIdx < NUM_HANDLE ; devcHdlIdx++){
            devcHndInfo = HandleTable[devcHdlIdx];
            if ((devcHndInfo != NULL)
                && (devcHndInfo->HType == HND_DEVICE)){
                threadArg = (SsdpSearchReply *)UPNP_MALLOC(sizeof(SsdpSearchReply));
                if (threadArg == NULL){
                    DLNA_LOGE("[VPPDLNA][%s][%d]:Memory Allocation failed for "
                            " creating threadArg \n", __FUNCTION__,__LINE__);
                    return;
                }

                maxAge = devcHndInfo->MaxAge;
                threadArg->handle = devcHdlIdx;
                memcpy(&threadArg->dest_addr, dest_addr, sizeof(threadArg->dest_addr));
                threadArg->event = event;
                threadArg->MaxAge = maxAge;

                (void)TPJobInit(&job, advertiseAndReplyThread, threadArg);
                (void)TPJobSetFreeFunction(&job, (free_routine) free);

                if (mx >= 2)
                    mx -= MAXVAL(1, mx / MX_FUDGE_FACTOR);
                if (mx < 1)
                    mx = 1;

                replyTime = rand() % mx;
                (void)TimerThreadSchedule(&gTimerThread, replyTime, REL_SEC, &job,
                SHORT_TERM, NULL);
            }
        }

      }else{

            /*
            We Can't Support Unicast m-search for
            Multiple devices presently. Need to find
            a way to idenify the device for which the
            unicast message has been sent

            Else Its a Unicast
            In case Of Unicast the UUID May not come
            in the received m-search request
            */

            DLNA_LOGI("[VPPDLNA][%s][%d]:\nm-search for unicast is not "
                    "supported\n",__FUNCTION__,__LINE__);
#if 0
            HandleLock();
                /* For Multicast m-Search devive info not required
                 We will reply for all device registered */
            /* device info. */
            if (GetDeviceHandleInfoExt1(param.DeviceId,
                        &handle, &dev_info) != HND_DEVICE) {
                HandleUnlock();
                /* no info found. */
                return;
            }

            maxAge = dev_info->MaxAge;
            HandleUnlock();

            DLNA_LOGI("[VPPDLNA]:MAX-AGE     =  %d\n", maxAge);
            DLNA_LOGI("[VPPDLNA]:MX     =  %d\n", event.Mx);
            DLNA_LOGI("[VPPDLNA]:DeviceType   =  %s\n", event.DeviceType);
            DLNA_LOGI("[VPPDLNA]:DeviceUuid   =  %s\n", event.UDN);
            DLNA_LOGI("[VPPDLNA]:ServiceType =  %s\n", event.ServiceType);
            threadArg = (SsdpSearchReply *)malloc(sizeof(SsdpSearchReply));
            if (threadArg == NULL)
                return;
            threadArg->handle = handle;
            memcpy(&threadArg->dest_addr, dest_addr, sizeof(threadArg->dest_addr));
            threadArg->event = event;
            threadArg->MaxAge = maxAge;

            TPJobInit(&job, advertiseAndReplyThread, threadArg);
            TPJobSetFreeFunction(&job, (free_routine) UPNP_FREE);

            /* Subtract a percentage from the mx to allow for network and processing
             * delays (i.e. if search is for 30 seconds, respond
             * within 0 - 27 seconds). */
            if (mx >= 2)
                mx -= MAXVAL(1, mx / MX_FUDGE_FACTOR);
            if (mx < 1)
                mx = 1;
            replyTime = rand() % mx;
            TimerThreadSchedule(&gTimerThread, replyTime, REL_SEC, &job,
                        SHORT_TERM, NULL);
#endif
      }

      /*End */
}
#endif

/*!
 * \brief Works as a request handler which passes the HTTP request string
 * to multicast channel.
 *
 * \return 1 if successful else appropriate error.
 */
static int NewRequestHandler(
    /*! [in] Ip address, to send the reply. */
    struct sockaddr *DestAddr,
    /*! [in] Number of packet to be sent. */
    int NumPacket,
    /*! [in] . */
    char **RqPacket,
    /*! [in] delay time between each packet to be sent. */
    int delay)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    SOCKET ReplySock;
    socklen_t socklen = sizeof(struct sockaddr_storage);
    int Index;
    unsigned long replyAddr = inet_addr(gIF_IPV4);
    /* a/c to UPNP Spec */
    int ttl = 4;
    int hops = 1;
    char buf_ntop[64];
    int ret = UPNP_E_SUCCESS;

    ReplySock = socket(DestAddr->sa_family, SOCK_DGRAM, 0);
    if (ReplySock == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA][%s][%d]:SSDP_LIB: New Request Handler:"
               "Error in socket(): %s\n", __FUNCTION__,__LINE__,errorBuffer);
        return UPNP_E_OUTOF_SOCKET;
    }

    if (DestAddr->sa_family == AF_INET) {
        (void)inet_ntop(AF_INET, &((struct sockaddr_in *)DestAddr)->sin_addr,
              buf_ntop, sizeof(buf_ntop));
        (void)setsockopt(ReplySock, IPPROTO_IP, IP_MULTICAST_IF,
               (char *)&replyAddr, sizeof(replyAddr));
        (void)setsockopt(ReplySock, IPPROTO_IP, IP_MULTICAST_TTL,
               (char *)&ttl, sizeof(int));
        int service_type;

        service_type = 0xe0;
        setsockopt(ReplySock, SOL_IP,IP_TOS, (void *)&service_type, sizeof(service_type));

        socklen = sizeof(struct sockaddr_in);
    } else if (DestAddr->sa_family == AF_INET6) {
        (void)inet_ntop(AF_INET6,
              &((struct sockaddr_in6 *)DestAddr)->sin6_addr,
              buf_ntop, sizeof(buf_ntop));
        (void)setsockopt(ReplySock, IPPROTO_IPV6, IPV6_MULTICAST_IF,
               (char *)&gIF_INDEX, sizeof(gIF_INDEX));
        (void)setsockopt(ReplySock, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
               (char *)&hops, sizeof(hops));
    } else {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Invalid destination address specified.",
            __FUNCTION__,__LINE__);
        ret = UPNP_E_NETWORK_ERROR;
        goto end_NewRequestHandler;
    }

    for (Index = 0; Index < NumPacket; Index++) {
        ssize_t rc;
        if(delay > 0)
            usleep(delay*1000);
        DLNA_LOGV("[VPPDLNA][%s][%d]:>>> SSDP SEND to %s >>>\n%s\n",__FUNCTION__
               ,__LINE__,buf_ntop, *(RqPacket + Index));
        rc = sendto(ReplySock, *(RqPacket + Index),
                strlen(*(RqPacket + Index)), 0, DestAddr, socklen);
        if (rc == -1) {
            strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
            DLNA_LOGE("[VPPDLNA][%s][%d]:SSDP_LIB: New Request Handler:"
                   "Error in socket(): %s\n",__FUNCTION__,__LINE__,errorBuffer);
            ret = UPNP_E_SOCKET_WRITE;
            goto end_NewRequestHandler;
        }
    }

 end_NewRequestHandler:
    (void)shutdown(ReplySock, SD_BOTH);
    UpnpCloseSocket(ReplySock);

    return ret;
}

/*!
 * \brief
 *
 * \return 1 if an inet6 @ has been found.
 */
static int extractIPv6address(char *url, char *address)
{
    int i = 0;
    int j = 0;
    int ret = 0;

    while (url[i] != '[' && url[i] != '\0') {
        i++;
    }
    if (url[i] == '\0') {
        goto exit_function;
    }

    /* bracket has been found, we deal with an IPv6 address */
    i++;
    while (url[i] != '\0' && url[i] != ']') {
        address[j] = url[i];
        i++;
        j++;
    }
    if (url[i] == '\0') {
        goto exit_function;
    }

    if (url[i] == ']') {
        address[j] = '\0';
        ret = 1;
    }

 exit_function:
    return ret;
}

/*!
 * \brief
 *
 * \return 1 if the Url contains an ULA or GUA IPv6 address, 0 otherwise.
 */
static int isUrlV6UlaGua(char *descdocUrl)
{
    char address[INET6_ADDRSTRLEN];
    struct in6_addr v6_addr;

    if (extractIPv6address(descdocUrl, address)) {
        (void)inet_pton(AF_INET6, address, &v6_addr);
        return !IN6_IS_ADDR_LINKLOCAL(&v6_addr);
    }

    return 0;
}

/*!
 * \brief Creates a HTTP request packet. Depending on the input parameter,
 * it either creates a service advertisement request or service shutdown
 * request etc.
 */
static void CreateServicePacket(
    /*! [in] type of the message (Search Reply, Advertisement
     * or Shutdown). */
    int msg_type,
    /*! [in] ssdp type. */
    const char *nt,
    /*! [in] unique service name ( go in the HTTP Header). */
    char *usn,
    /*! [in] Location URL. */
    char *location,
    /*! [in] Service duration in sec. */
    int duration,
    /*! [out] Output buffer filled with HTTP statement. */
    char **packet,
    /*! [in] Address family of the HTTP request. */
    int AddressFamily)
{
    int ret_code;
    const char *nts;
    membuffer buf;

    /* Notf == 0 means service shutdown,
     * Notf == 1 means service advertisement,
     * Notf == 2 means reply */
    membuffer_init(&buf);
    buf.size_inc = 30;
    *packet = NULL;
    if (msg_type == MSGTYPE_REPLY) {
        ret_code = http_MakeMessage(&buf, 1, 1,
                        "R" "sdc" "D" "sc" "ssc" "ssc" "ssc"
                        "S" "Xc" "ssc" "sscc", HTTP_OK,
                        "CACHE-CONTROL: max-age=", duration,
                        "EXT:", "LOCATION: ", location,
                        "OPT: ",
                        "\"http://schemas.upnp.org/upnp/1/0/\"; ns=01",
                        "01-NLS: ", gUpnpSdkNLSuuid,
                        X_USER_AGENT, "ST: ", nt, "USN: ",
                        usn);
        if (ret_code != 0) {
            DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to create a ssdp reply message"
                   "Error returned:%d\n",__FUNCTION__,__LINE__,ret_code);
            return;
        }
    } else if (msg_type == MSGTYPE_ADVERTISEMENT ||
           msg_type == MSGTYPE_SHUTDOWN) {
        const char *host = NULL;

        if (msg_type == MSGTYPE_ADVERTISEMENT)
            nts = "ssdp:alive";
        else
            /* shutdown */
            nts = "ssdp:byebye";
        /* NOTE: The CACHE-CONTROL and LOCATION headers are not present in
         * a shutdown msg, but are present here for MS WinMe interop. */
        if (AddressFamily == AF_INET)
            host = SSDP_IP;
        else {
            if (isUrlV6UlaGua(location))
                host = "[" SSDP_IPV6_SITELOCAL "]";
            else
                host = "[" SSDP_IPV6_LINKLOCAL "]";
        }
        ret_code = http_MakeMessage(&buf, 1, 1,
                        "Q" "sssdc" "sdc" "ssc" "ssc" "ssc"
                        "ssc" "ssc" "S" "Xc" "sscc",
                        HTTPMETHOD_NOTIFY, "*", (size_t) 1,
                        "HOST: ", host, ":", SSDP_PORT,
                        "CACHE-CONTROL: max-age=", duration,
                        "LOCATION: ", location, "OPT: ",
                        "\"http://schemas.upnp.org/upnp/1/0/\"; ns=01",
                        "01-NLS: ", gUpnpSdkNLSuuid, "NT: ",
                        nt, "NTS: ", nts, X_USER_AGENT,
                        "USN: ", usn);
        if (ret_code){
            DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to create a ssdp request "
                "message of type-%s . Error returned:%d\n",__FUNCTION__,
                __LINE__,nts, ret_code);
            return;
        }
    } else
        /* unknown msg */
        /*lint -e506*/
        assert(0);
        /*lint +e506*/
    /* return msg */
    *packet = membuffer_detach(&buf);
    membuffer_destroy(&buf);

    return;
}

int DeviceAdvertisement(char *DevType, int RootDev, char *Udn, char *Location,
            int iDuration, int AddressFamily)
{
    struct sockaddr_storage __ss;
    struct sockaddr_in *DestAddr4 = (struct sockaddr_in *)&__ss;
    struct sockaddr_in6 *DestAddr6 = (struct sockaddr_in6 *)&__ss;
    /* char Mil_Nt[LINE_SIZE] */
    char Mil_Usn[LINE_SIZE];
    char *msgs[3];
    int ret_code = UPNP_E_SUCCESS;

    DLNA_LOGV("[VPPDLNA][%s][%d]:In function DeviceAdvertisement\n",
        __FUNCTION__,__LINE__);
    memset(&__ss, 0, sizeof(__ss));
    memset(Mil_Usn,0,sizeof(Mil_Usn));
    if (AddressFamily == AF_INET) {
        DestAddr4->sin_family = AF_INET;
        (void)inet_pton(AF_INET, SSDP_IP, &DestAddr4->sin_addr);
        DestAddr4->sin_port = htons(SSDP_PORT);
    } else if (AddressFamily == AF_INET6) {
        DestAddr6->sin6_family = AF_INET6;
        (void)inet_pton(AF_INET6,
              (isUrlV6UlaGua(Location)) ? SSDP_IPV6_SITELOCAL :
              SSDP_IPV6_LINKLOCAL, &DestAddr6->sin6_addr);
        DestAddr6->sin6_port = htons(SSDP_PORT);
        DestAddr6->sin6_scope_id = gIF_INDEX;
    } else {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Invalid device address family.\n",
            __FUNCTION__,__LINE__);
    }
    msgs[0] = NULL;
    msgs[1] = NULL;
    msgs[2] = NULL;
    /* If deviceis a root device , here we need to send 3 advertisement
     * or reply */
    if (RootDev) {
        memset(Mil_Usn,0,sizeof(Mil_Usn));
        snprintf(Mil_Usn, LINE_SIZE,"%s::upnp:rootdevice", Udn);
        CreateServicePacket(MSGTYPE_ADVERTISEMENT, "upnp:rootdevice",
                    Mil_Usn, Location, iDuration, &msgs[0],
                    AddressFamily);
    }
    /* both root and sub-devices need to send these two messages */
    CreateServicePacket(MSGTYPE_ADVERTISEMENT, Udn, Udn,
                Location, iDuration, &msgs[1], AddressFamily);
    memset(Mil_Usn,0,sizeof(Mil_Usn));
    snprintf(Mil_Usn, LINE_SIZE,"%s::%s", Udn, DevType);
    CreateServicePacket(MSGTYPE_ADVERTISEMENT, DevType, Mil_Usn,
                Location, iDuration, &msgs[2], AddressFamily);
    /* check error */
    if ((RootDev && msgs[0] == NULL) || msgs[1] == NULL || msgs[2] == NULL) {
        UPNP_FREE(msgs[0]);
        UPNP_FREE(msgs[1]);
        UPNP_FREE(msgs[2]);
        DLNA_LOGE("[VPPDLNA][%s][%d]:Creation Of Service Packet Failed.\n",
            __FUNCTION__,__LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }
    /* send packets */
    if (RootDev) {
        /* send 3 msg types */
        ret_code =
            NewRequestHandler((struct sockaddr *)&__ss, 3, &msgs[0],TIME_BETWEEN_SSDP_PACKET);
    } else {        /* sub-device */

        /* send 2 msg types */
        ret_code =
            NewRequestHandler((struct sockaddr *)&__ss, 2, &msgs[1],TIME_BETWEEN_SSDP_PACKET);
    }
    /* free msgs */
    UPNP_FREE(msgs[0]);
    UPNP_FREE(msgs[1]);
    UPNP_FREE(msgs[2]);

    return ret_code;
}

int SendReply(struct sockaddr *DestAddr, char *DevType, int RootDev,
          char *Udn, char *Location, int iDuration, int ByType)
{
    int ret_code;
    char *msgs[2];
    int num_msgs;
    char Mil_Usn[LINE_SIZE];
    int i;

    msgs[0] = NULL;
    msgs[1] = NULL;
    memset(Mil_Usn,0,sizeof(Mil_Usn));
    if (RootDev) {
        /* one msg for root device */
        num_msgs = 1;

        snprintf(Mil_Usn, LINE_SIZE,"%s::upnp:rootdevice", Udn);
        CreateServicePacket(MSGTYPE_REPLY, "upnp:rootdevice",
                    Mil_Usn, Location, iDuration, &msgs[0],
                    DestAddr->sa_family);
    } else {
        /* two msgs for embedded devices */
        num_msgs = 1;

        /*NK: FIX for extra response when someone searches by udn */
        if (!ByType) {
            CreateServicePacket(MSGTYPE_REPLY, Udn, Udn, Location,
                        iDuration, &msgs[0],
                        DestAddr->sa_family);
        } else {
            snprintf(Mil_Usn, LINE_SIZE,"%s::%s", Udn, DevType);
            CreateServicePacket(MSGTYPE_REPLY, DevType, Mil_Usn,
                        Location, iDuration, &msgs[0],
                        DestAddr->sa_family);
        }
    }
    /* check error */
    for (i = 0; i < num_msgs; i++) {
        if (msgs[i] == NULL) {
            UPNP_FREE(msgs[0]);
            DLNA_LOGE("[VPPDLNA][%s][%d]:Creation of message:msg[%d] failed.\n",
            __FUNCTION__,__LINE__,i);
            return UPNP_E_OUTOF_MEMORY;
        }
    }
    /* send msgs */
    ret_code = NewRequestHandler(DestAddr, num_msgs, msgs,0);
    for (i = 0; i < num_msgs; i++) {
        if (msgs[i] != NULL)
            UPNP_FREE(msgs[i]);
    }

    return ret_code;
}

int DeviceReply(struct sockaddr *DestAddr, char *DevType, int RootDev,
        char *Udn, char *Location, int iDuration)
{
    char *szReq[3], Mil_Nt[LINE_SIZE], Mil_Usn[LINE_SIZE];
    int RetVal;

    szReq[0] = NULL;
    szReq[1] = NULL;
    szReq[2] = NULL;

    memset(Mil_Usn,0,sizeof(Mil_Usn));
    memset(Mil_Nt,0,sizeof(Mil_Nt));
    /* create 2 or 3 msgs */
    if (RootDev) {
        /* 3 replies for root device */
        HISTRCPY(Mil_Nt, "upnp:rootdevice");
        snprintf(Mil_Usn, LINE_SIZE,"%s::upnp:rootdevice", Udn);
        CreateServicePacket(MSGTYPE_REPLY, Mil_Nt, Mil_Usn,
                    Location, iDuration, &szReq[0],
                    DestAddr->sa_family);
    }
    snprintf(Mil_Nt, LINE_SIZE,"%s", Udn);
    snprintf(Mil_Usn,LINE_SIZE, "%s", Udn);
    CreateServicePacket(MSGTYPE_REPLY, Mil_Nt, Mil_Usn,
                Location, iDuration, &szReq[1], DestAddr->sa_family);
    snprintf(Mil_Nt,LINE_SIZE, "%s", DevType);
    snprintf(Mil_Usn, LINE_SIZE,"%s::%s", Udn, DevType);
    CreateServicePacket(MSGTYPE_REPLY, Mil_Nt, Mil_Usn,
                Location, iDuration, &szReq[2], DestAddr->sa_family);
    /* check error */
    if ((RootDev && szReq[0] == NULL) ||
        szReq[1] == NULL || szReq[2] == NULL) {
        UPNP_FREE(szReq[0]);
        UPNP_FREE(szReq[1]);
        UPNP_FREE(szReq[2]);
        DLNA_LOGE("[VPPDLNA][%s][%d]:Creation of Reply Messages failed.\n",
            __FUNCTION__,__LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }
    /* send replies */
    if (RootDev) {
        RetVal = NewRequestHandler(DestAddr, 3, szReq,0);
    } else {
        RetVal = NewRequestHandler(DestAddr, 2, &szReq[1],0);
    }
    /* free */
    UPNP_FREE(szReq[0]);
    UPNP_FREE(szReq[1]);
    UPNP_FREE(szReq[2]);

    return RetVal;
}

int ServiceAdvertisement(char *Udn, char *ServType, char *Location,
             int iDuration, int AddressFamily)
{
    char Mil_Usn[LINE_SIZE];
    char *szReq[1];
    int RetVal = UPNP_E_SUCCESS;
    struct sockaddr_storage __ss;
    struct sockaddr_in *DestAddr4 = (struct sockaddr_in *)&__ss;
    struct sockaddr_in6 *DestAddr6 = (struct sockaddr_in6 *)&__ss;

    memset(&__ss, 0, sizeof(__ss));
    memset(Mil_Usn,0,sizeof(Mil_Usn));
    if (AddressFamily == AF_INET) {
        DestAddr4->sin_family = AF_INET;
        (void)inet_pton(AF_INET, SSDP_IP, &DestAddr4->sin_addr);
        DestAddr4->sin_port = htons(SSDP_PORT);
    } else if (AddressFamily == AF_INET6) {
        DestAddr6->sin6_family = AF_INET6;
        (void)inet_pton(AF_INET6,
              (isUrlV6UlaGua(Location)) ? SSDP_IPV6_SITELOCAL :
              SSDP_IPV6_LINKLOCAL, &DestAddr6->sin6_addr);
        DestAddr6->sin6_port = htons(SSDP_PORT);
        DestAddr6->sin6_scope_id = gIF_INDEX;
    } else {
        DLNA_LOGE("[VPPDLNA]:Invalid device address family.\n");
    }
    snprintf(Mil_Usn, LINE_SIZE,"%s::%s", Udn, ServType);
    /* CreateServiceRequestPacket(1,szReq[0],Mil_Nt,Mil_Usn,
     * Server,Location,iDuration); */
    CreateServicePacket(MSGTYPE_ADVERTISEMENT, ServType, Mil_Usn,
                Location, iDuration, &szReq[0], AddressFamily);
    if (szReq[0] == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Creation of Advertise Messages failed.\n",
            __FUNCTION__,__LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }
    RetVal = NewRequestHandler((struct sockaddr *)&__ss, 1, szReq,TIME_BETWEEN_SSDP_PACKET);
    UPNP_FREE(szReq[0]);

    return RetVal;
}

int ServiceReply(struct sockaddr *DestAddr, char *ServType, char *Udn,
         char *Location, int iDuration)
{
    char Mil_Usn[LINE_SIZE];
    char *szReq[1];
    int RetVal;

    szReq[0] = NULL;
    memset(Mil_Usn,0,sizeof(Mil_Usn));
    snprintf(Mil_Usn,LINE_SIZE, "%s::%s", Udn, ServType);
    CreateServicePacket(MSGTYPE_REPLY, ServType, Mil_Usn,
                Location, iDuration, &szReq[0], DestAddr->sa_family);
    if (szReq[0] == NULL){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Creation of Reply Messages failed.\n",
            __FUNCTION__,__LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }
    RetVal = NewRequestHandler(DestAddr, 1, szReq,0);
    UPNP_FREE(szReq[0]);

    return RetVal;
}

int ServiceShutdown(char *Udn, char *ServType, char *Location, int iDuration,
            int AddressFamily)
{
    char Mil_Usn[LINE_SIZE];
    char *szReq[1];
    struct sockaddr_storage __ss;
    struct sockaddr_in *DestAddr4 = (struct sockaddr_in *)&__ss;
    struct sockaddr_in6 *DestAddr6 = (struct sockaddr_in6 *)&__ss;
    int RetVal = UPNP_E_SUCCESS;

    memset(&__ss, 0, sizeof(__ss));
    memset(Mil_Usn,0,sizeof(Mil_Usn));
    if (AddressFamily == AF_INET) {
        DestAddr4->sin_family = AF_INET;
        (void)inet_pton(AF_INET, SSDP_IP, &DestAddr4->sin_addr);
        DestAddr4->sin_port = htons(SSDP_PORT);
    } else if (AddressFamily == AF_INET6) {
        DestAddr6->sin6_family = AF_INET6;
        (void)inet_pton(AF_INET6,
              (isUrlV6UlaGua(Location)) ? SSDP_IPV6_SITELOCAL :
              SSDP_IPV6_LINKLOCAL, &DestAddr6->sin6_addr);
        DestAddr6->sin6_port = htons(SSDP_PORT);
        DestAddr6->sin6_scope_id = gIF_INDEX;
    } else {
        DLNA_LOGE("[VPPDLNA]:Invalid device address family.\n");
    }
    /* sprintf(Mil_Nt,"%s",ServType); */
    snprintf(Mil_Usn, LINE_SIZE,"%s::%s", Udn, ServType);
    /* CreateServiceRequestPacket(0,szReq[0],Mil_Nt,Mil_Usn,
     * Server,Location,iDuration); */
    CreateServicePacket(MSGTYPE_SHUTDOWN, ServType, Mil_Usn,
                Location, iDuration, &szReq[0], AddressFamily);
    if (szReq[0] == NULL){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Creation of byebye request  Messages "
            "for services failed.\n", __FUNCTION__,__LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }
    RetVal = NewRequestHandler((struct sockaddr *)&__ss, 1, szReq,0);
    UPNP_FREE(szReq[0]);

    return RetVal;
}

int DeviceShutdown(char *DevType, int RootDev, char *Udn, char *_Server,
           char *Location, int iDuration, int AddressFamily)
{
    struct sockaddr_storage __ss;
    struct sockaddr_in *DestAddr4 = (struct sockaddr_in *)&__ss;
    struct sockaddr_in6 *DestAddr6 = (struct sockaddr_in6 *)&__ss;
    char *msgs[3];
    char Mil_Usn[LINE_SIZE];
    int ret_code = UPNP_E_SUCCESS;

    DLNA_LOGV("[VPPDLNA]:enter  Device Shutdown \r\n");

    msgs[0] = NULL;
    msgs[1] = NULL;
    msgs[2] = NULL;
    memset(Mil_Usn,0,sizeof(Mil_Usn));
    memset(&__ss, 0, sizeof(__ss));
    if (AddressFamily == AF_INET) {
        DestAddr4->sin_family = AF_INET;
        (void)inet_pton(AF_INET, SSDP_IP, &DestAddr4->sin_addr);
        DestAddr4->sin_port = htons(SSDP_PORT);
    } else if (AddressFamily == AF_INET6) {
        DestAddr6->sin6_family = AF_INET6;
        (void)inet_pton(AF_INET6,
              (isUrlV6UlaGua(Location)) ? SSDP_IPV6_SITELOCAL :
              SSDP_IPV6_LINKLOCAL, &DestAddr6->sin6_addr);
        DestAddr6->sin6_port = htons(SSDP_PORT);
        DestAddr6->sin6_scope_id = gIF_INDEX;
    } else {
        DLNA_LOGE("[VPPDLNA]:Invalid device address family.\n");
    }
    /* root device has one extra msg */
    if (RootDev) {
        snprintf(Mil_Usn, LINE_SIZE,"%s::upnp:rootdevice", Udn);
        CreateServicePacket(MSGTYPE_SHUTDOWN, "upnp:rootdevice",
                    Mil_Usn, Location, iDuration, &msgs[0],
                    AddressFamily);
    }
    DLNA_LOGI("[VPPDLNA]:In function DeviceShutdown\n");
    /* both root and sub-devices need to send these two messages */
    CreateServicePacket(MSGTYPE_SHUTDOWN, Udn, Udn,
                Location, iDuration, &msgs[1], AddressFamily);
    snprintf(Mil_Usn, LINE_SIZE,"%s::%s", Udn, DevType);
    CreateServicePacket(MSGTYPE_SHUTDOWN, DevType, Mil_Usn,
                Location, iDuration, &msgs[2], AddressFamily);
    /* check error */
    if ((RootDev && msgs[0] == NULL) || msgs[1] == NULL || msgs[2] == NULL) {
        UPNP_FREE(msgs[0]);
        UPNP_FREE(msgs[1]);
        UPNP_FREE(msgs[2]);
         DLNA_LOGE("[VPPDLNA][%s][%d]:Creation of byebye request  Messages "
            "for Devices failed.\n", __FUNCTION__,__LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }
    /* send packets */
    if (RootDev) {
        /* send 3 msg types */
        ret_code =
            NewRequestHandler((struct sockaddr *)&__ss, 3, &msgs[0],0);
    } else {
        /* sub-device */
        /* send 2 msg types */
        ret_code =
            NewRequestHandler((struct sockaddr *)&__ss, 2, &msgs[1],0);
    }
    /* free msgs */
    UPNP_FREE(msgs[0]);
    UPNP_FREE(msgs[1]);
    UPNP_FREE(msgs[2]);

    _Server = _Server;
    return ret_code;
}
#endif /* EXCLUDE_SSDP */
#endif /* INCLUDE_DEVICE_APIS */

/* @} SSDPlib */
