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

#include "config.h"

#include "upnputil.h"

#ifdef INCLUDE_CLIENT_APIS
#if EXCLUDE_SSDP == 0

#include "httpparser.h"
#include "httpreadwrite.h"
#include "ssdp_ResultData.h"
#include "ssdplib.h"
#include "statcodes.h"
#include "unixutil.h"
#include "upnpapi.h"
#include "UpnpInet.h"
#include "ThreadPool.h"

/*lint -save -e* */
#include <stdio.h>

#ifdef WIN32
#include <string.h>
#endif /* WIN32 */

/*lint -restore * */


typedef struct _SearchExpiredData
{
    int threadID;
    UpnpClient_Handle clientHdl;
}SearchExpiredData;

/*!
 * \brief Sends a callback to the control point application with a SEARCH
 * result.
 */
static void send_search_result(
    /* [in] Search reply from the device. */
    IN void *data)
{
    ResultData *temp = (ResultData *) data;

    temp->ctrlpt_callback(UPNP_DISCOVERY_SEARCH_RESULT, &temp->param,
                  temp->cookie);
    UPNP_FREE(temp);
}

void ssdp_handle_ctrlpt_msg(http_message_t *hmsg,
                    ssdp_thread_data *data, int timeout, void *cookie)
{
    int handle;
    struct Handle_Info *ctrlpt_info = NULL;
    memptr hdr_value;
    /* byebye or alive */
    int is_byebye;
    struct Upnp_Discovery param;
    SsdpEvent event;
    int nt_found;
    int usn_found;
    int st_found;
    char save_char;
    Upnp_EventType event_type;
    Upnp_FunPtr ctrlpt_callback;
    void *ctrlpt_cookie;
    ListNode *node = NULL;
    SsdpSearchArg *searchArg = NULL;
    int matched = 0;
    ResultData *threadData = NULL;
    ThreadPoolJob job;

    DLNA_LOGV("[VPPDLNA][%s][%d]:Inside ssdp_handle_ctrlpt_msg to handle handle"
            " SSDP advertise and bye bye request or response to m-search\n",
            __FUNCTION__,__LINE__);

    /* we are assuming that there can be only one client supported at a time */
    HandleReadLock();

    if (GetClientHandleInfoExt(data->ssdpReadSocket, &handle,
        &ctrlpt_info) != HND_CLIENT) {
        DLNA_LOGI("[VPPDLNA][%s][%d]-: Failed To get The Client "
                "Handle Info\r\n",__FUNCTION__,__LINE__);
        HandleUnlock();
        return;
    }
    /* copy */
    ctrlpt_callback = ctrlpt_info->Callback;
    ctrlpt_cookie = ctrlpt_info->Cookie;
    HandleUnlock();
    /* search timeout */
    if (timeout) {
        (void)ctrlpt_callback(UPNP_DISCOVERY_SEARCH_TIMEOUT, NULL, cookie);
        return;
    }
    param.ErrCode = UPNP_E_SUCCESS;
    /* MAX-AGE, assume error */
    param.Expires = -1;
    if (httpmsg_find_hdr(hmsg, HDR_CACHE_CONTROL, &hdr_value) != NULL) {
        if (matchstr(hdr_value.buf, hdr_value.length,
                 "%imax-age = %d%0", &param.Expires) != PARSE_OK){
            DLNA_LOGE("[VPPDLNA][%s][%d]-: Failed to get the max-age "
                "header\r\n",__FUNCTION__,__LINE__);
            return;
        }
    }
    /* DATE */
    param.Date[0] = '\0';
    if (httpmsg_find_hdr(hmsg, HDR_DATE, &hdr_value) != NULL) {
        linecopylen(param.Date, hdr_value.buf, hdr_value.length);
    }
    /* dest addr */
    memcpy(&param.DestAddr, &(data->dest_addr), sizeof(struct sockaddr_in));
    /* EXT */
    param.Ext[0] = '\0';
    if (httpmsg_find_hdr(hmsg, HDR_EXT, &hdr_value) != NULL) {
        linecopylen(param.Ext, hdr_value.buf, hdr_value.length);
    }
    /* LOCATION */
    param.Location[0] = '\0';
    if (httpmsg_find_hdr(hmsg, HDR_LOCATION, &hdr_value) != NULL) {
        linecopylen(param.Location, hdr_value.buf, hdr_value.length);
    }
    /* SERVER / USER-AGENT */
    param.Os[0] = '\0';
    if (httpmsg_find_hdr(hmsg, HDR_SERVER, &hdr_value) != NULL ||
        httpmsg_find_hdr(hmsg, HDR_USER_AGENT, &hdr_value) != NULL) {
        linecopylen(param.Os, hdr_value.buf, hdr_value.length);
    }
    /* clear everything */
    param.DeviceId[0] = '\0';
    param.DeviceType[0] = '\0';
    param.ServiceType[0] = '\0';
    /* not used; version is in ServiceType */
    param.ServiceVer[0] = '\0';
    event.UDN[0] = '\0';
    event.DeviceType[0] = '\0';
    event.ServiceType[0] = '\0';
    nt_found = FALSE;
    if (httpmsg_find_hdr(hmsg, HDR_NT, &hdr_value) != NULL) {
        save_char = hdr_value.buf[hdr_value.length];
        hdr_value.buf[hdr_value.length] = '\0';
        nt_found = (ssdp_request_type(hdr_value.buf, &event) == 0);
        hdr_value.buf[hdr_value.length] = save_char;
    }
    usn_found = FALSE;
    if (httpmsg_find_hdr(hmsg, HDR_USN, &hdr_value) != NULL) {
        save_char = hdr_value.buf[hdr_value.length];
        hdr_value.buf[hdr_value.length] = '\0';
        usn_found = (unique_service_name(hdr_value.buf, &event) == 0);
        hdr_value.buf[hdr_value.length] = save_char;
    }
    if (nt_found || usn_found) {
        HISTRCPY(param.DeviceId, event.UDN);
        HISTRCPY(param.DeviceType, event.DeviceType);
        HISTRCPY(param.ServiceType, event.ServiceType);
    }
    /* ADVERT. OR BYEBYE */
    if (hmsg->is_request) {
        /* use NTS hdr to determine advert., or byebye */
        if (httpmsg_find_hdr(hmsg, HDR_NTS, &hdr_value) == NULL) {
            DLNA_LOGE("[VPPDLNA][%s][%d]-: NTS header not found in the  "
                "ssdp request\r\n",__FUNCTION__,__LINE__);
            return; /* error; NTS header not found */
        }
        if (memptr_cmp(&hdr_value, "ssdp:alive") == 0) {
            is_byebye = FALSE;
        } else if (memptr_cmp(&hdr_value, "ssdp:byebye") == 0) {
            is_byebye = TRUE;
        } else {
            DLNA_LOGE("[VPPDLNA][%s][%d]-: NTS header Value Must be either"
                " ssdp:alive or ssdp:byebye for ssdp request\n",
                __FUNCTION__,__LINE__);
            return; /* bad value */
        }
        if (is_byebye) {
            /* check device byebye */
            if (!nt_found || !usn_found) {
                DLNA_LOGE("[VPPDLNA][%s][%d]-:Received ssdp byebye request"
                        " don't have either nt header or usn header\n",
                        __FUNCTION__,__LINE__);
                return; /* bad byebye */
            }

            event_type = UPNP_DISCOVERY_ADVERTISEMENT_BYEBYE;
        } else {
            /* check advertisement.
             * Expires is valid if positive. This is for testing
             * only. Expires should be greater than 1800 (30 mins) */
            if (!nt_found ||
                !usn_found ||
                strlen(param.Location) == 0 || param.Expires <= 0) {
                DLNA_LOGE("[VPPDLNA][%s][%d]-:Received ssdp alive request"
                      " don't have either nt header or usn header or have"
                      "Valid location or max-age\n",
                      __FUNCTION__,__LINE__);
                return; /* bad advertisement */
            }
            event_type = UPNP_DISCOVERY_ADVERTISEMENT_ALIVE;
        }
        /* call callback */

        DLNA_LOGI("[VPPUPNP][%s][%d] Giving Event Indication Event-%d\r\n\n",
                __FUNCTION__,__LINE__,event_type);
        (void)ctrlpt_callback(event_type, &param, ctrlpt_cookie);
    } else {
        /* reply (to a SEARCH) */
        /* only checking to see if there is a valid ST header */
        st_found = FALSE;
        if (httpmsg_find_hdr(hmsg, HDR_ST, &hdr_value) != NULL) {
            save_char = hdr_value.buf[hdr_value.length];
            hdr_value.buf[hdr_value.length] = '\0';
            st_found =
                ssdp_request_type(hdr_value.buf, &event) == 0;
            hdr_value.buf[hdr_value.length] = save_char;
        }
        if (hmsg->status_code != HTTP_OK ||
            param.Expires <= 0 ||
            strlen(param.Location) == 0 || !usn_found || !st_found) {
            DLNA_LOGE("[VPPDLNA][%s][%d]-:Received ssdp response"
                      " don't have either nt header or usn header or have"
                      "Valid location or max-age\n",
                      __FUNCTION__,__LINE__);
            return; /* bad reply */
        }
        /* check each current search */
        HandleLock();
        if (GetClientHandleInfoExt(data->ssdpReadSocket, &handle,
                &ctrlpt_info) != HND_CLIENT) {
            DLNA_LOGE("[VPPDLNA][%s][%d]-: Failed To get The Client "
                "Handle Info\r\n",__FUNCTION__,__LINE__);
            HandleUnlock();
            return;
        }
        node = ListHead(&ctrlpt_info->SsdpSearchList);
        /* temporary add null termination */
        /*save_char = hdr_value.buf[ hdr_value.length ]; */
        /*hdr_value.buf[ hdr_value.length ] = '\0'; */
        while (node != NULL) {
            searchArg = node->item;
            matched = 0;
            /* check for match of ST header and search target */
            switch (searchArg->requestType) {
            case SSDP_ALL:
                matched = 1;
                break;
            case SSDP_ROOTDEVICE:
                matched =
                    (event.RequestType == SSDP_ROOTDEVICE);
                break;
            case SSDP_DEVICEUDN:
                matched = !strncmp(searchArg->searchTarget,
                           hdr_value.buf,
                           hdr_value.length);
                break;
            case SSDP_DEVICETYPE:{
                    size_t m = Min(hdr_value.length,
                               strlen
                               (searchArg->searchTarget));
                    matched =
                        !strncmp(searchArg->searchTarget,
                             hdr_value.buf, m);
                    break;
                }
            case SSDP_SERVICE:{
                    size_t m = Min(hdr_value.length,
                               strlen
                               (searchArg->searchTarget));
                    matched =
                        !strncmp(searchArg->searchTarget,
                             hdr_value.buf, m);
                    break;
                }
            default:
                matched = 0;
                break;
            }
            if (matched) {
                /* schedule call back */
                threadData =
                    (ResultData *) UPNP_MALLOC(sizeof(ResultData));
                if (threadData != NULL) {
                    threadData->param = param;
                    threadData->cookie = searchArg->cookie;
                    threadData->ctrlpt_callback =
                        ctrlpt_callback;
                    (void)TPJobInit(&job, (start_routine)
                          send_search_result,
                          threadData);
                    (void)TPJobSetPriority(&job, MED_PRIORITY);
                    (void)TPJobSetFreeFunction(&job,
                                 (free_routine)
                                 free);
                    (void)ThreadPoolAdd(&gRecvThreadPool, &job,
                              NULL);
                }
            }
            node = ListNext(&ctrlpt_info->SsdpSearchList, node);
        }

        HandleUnlock();
    }
}

/*!
 * \brief Creates a HTTP search request packet depending on the input
 * parameter.
 */
static void CreateClientRequestPacket(
    /*! [in] Output string in HTTP format. */
    IN char *RqstBuf,
    /*! [in] Search Target. */
    IN int Mx,
    /*! [in] Number of seconds to wait to collect all the responses. */
    IN char *SearchTarget,
    /*! [in] search address family. */
    IN int AddressFamily)
{
    char TempBuf[COMMAND_LEN] = {0};

    HISTRCPY(RqstBuf, "M-SEARCH * HTTP/1.1\r\n");

    memset(TempBuf,0,sizeof(TempBuf));
    if (AddressFamily == AF_INET) {
        snprintf(TempBuf,COMMAND_LEN,"HOST: %s:%d\r\n", SSDP_IP, SSDP_PORT);
    } else if (AddressFamily == AF_INET6) {
        snprintf(TempBuf, COMMAND_LEN,"HOST: [%s]:%d\r\n", SSDP_IPV6_LINKLOCAL,
            SSDP_PORT);
    }
    HISTRCAT(RqstBuf, TempBuf);
    HISTRCAT(RqstBuf, "MAN: \"ssdp:discover\"\r\n");

    if (Mx > 0) {
        memset(TempBuf,0,sizeof(TempBuf));
        snprintf(TempBuf,COMMAND_LEN, "MX: %d\r\n", Mx);
        HISTRCAT(RqstBuf, TempBuf);
    }

    if (SearchTarget != NULL) {
        memset(TempBuf,0,sizeof(TempBuf));
        snprintf(TempBuf,COMMAND_LEN, "ST: %s\r\n", SearchTarget);
        HISTRCAT(RqstBuf, TempBuf);
    }
    HISTRCAT(RqstBuf, "\r\n");
}

#ifdef UPNP_ENABLE_IPV6

/*!
 * \brief
 */
static void CreateClientRequestPacketUlaGua(
    /*! [in] . */
    char *RqstBuf,
    /*! [in] . */
    int Mx,
    /*! [in] . */
    char *SearchTarget,
    /*! [in] . */
    int AddressFamily)
{
    char TempBuf[COMMAND_LEN] = {0};

    memset(TempBuf,0,sizeof(TempBuf));
    HISTRCPY(RqstBuf, "M-SEARCH * HTTP/1.1\r\n");
    if (AddressFamily == AF_INET) {
        snprintf(TempBuf,COMMAND_LEN, "HOST: %s:%d\r\n", SSDP_IP, SSDP_PORT);
    } else if (AddressFamily == AF_INET6) {
        snprintf(TempBuf, COMMAND_LEN,"HOST: [%s]:%d\r\n", SSDP_IPV6_SITELOCAL,
            SSDP_PORT);
    }
    HISTRCAT(RqstBuf, TempBuf);
    HISTRCAT(RqstBuf, "MAN: \"ssdp:discover\"\r\n");
    if (Mx > 0) {
        memset(TempBuf,0,sizeof(TempBuf));
        snprintf(TempBuf, COMMAND_LEN,"MX: %d\r\n", Mx);
        HISTRCAT(RqstBuf, TempBuf);
    }
    if (SearchTarget) {
        memset(TempBuf,0,sizeof(TempBuf));
        snprintf(TempBuf, COMMAND_LEN,"ST: %s\r\n", SearchTarget);
        HISTRCAT(RqstBuf, TempBuf);
    }
    HISTRCAT(RqstBuf, "\r\n");
}

#endif

/*!
 * \brief
 */
static void searchExpired(
    /* [in] . */
    void *arg)
{

    SearchExpiredData *pstExpData = (SearchExpiredData *)arg;
    int id = pstExpData->threadID;
    struct Handle_Info *ctrlpt_info = NULL;

    /* remove search Target from list and call client back */
    ListNode *node = NULL;
    SsdpSearchArg *item;
    Upnp_FunPtr ctrlpt_callback;
    void *cookie = NULL;
    int found = 0;

    HandleLock();

    /* remove search target from search list */
    /* As we already have the client handle id we will get the
       client handle info from it */
#if 0
    if (GetClientHandleInfo(&handle, &ctrlpt_info) != HND_CLIENT) {
        free(id);
        HandleUnlock();
        return;
    }
#endif

    if (GetHandleInfo(pstExpData->clientHdl, &ctrlpt_info) != HND_CLIENT){
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,
                pstExpData->clientHdl);
        UPNP_FREE(pstExpData);
        return;
    }


    ctrlpt_callback = ctrlpt_info->Callback;
    node = ListHead(&ctrlpt_info->SsdpSearchList);
    while (node != NULL) {
        item = (SsdpSearchArg *) node->item;
        if (item->timeoutEventId == id) {
            UPNP_FREE(item->searchTarget);
            cookie = item->cookie;
            found = 1;
            item->searchTarget = NULL;
            UPNP_FREE(item);
            (void)ListDelNode(&ctrlpt_info->SsdpSearchList, node, 0);
            break;
        }
        node = ListNext(&ctrlpt_info->SsdpSearchList, node);
    }
    HandleUnlock();

    if (found)
        (void)ctrlpt_callback(UPNP_DISCOVERY_SEARCH_TIMEOUT, NULL, cookie);

    UPNP_FREE(pstExpData);
}


int SearchByTarget(int Mx, char *St, void *Cookie,UpnpClient_Handle clHdl)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    int *id = NULL;
    int ret = 0;
    char ReqBufv4[BUFSIZE];
    struct sockaddr_storage __ss_v4;
    struct sockaddr_in *destAddr4 = (struct sockaddr_in *)&__ss_v4;
#ifdef UPNP_ENABLE_IPV6
    struct sockaddr_storage __ss_v6;
    struct sockaddr_in6 *destAddr6 = (struct sockaddr_in6 *)&__ss_v6;
    char ReqBufv6[BUFSIZE];
    char ReqBufv6UlaGua[BUFSIZE];
#endif
    fd_set wrSet;
    SsdpSearchArg *newArg = NULL;
    int timeTillRead = 0;
    int handle;
    struct Handle_Info *ctrlpt_info = NULL;
    enum SsdpSearchType requestType;
    unsigned long addrv4 = inet_addr(gIF_IPV4);
    int max_fd = 0;
    SearchExpiredData *pstExpData = NULL;

    /*ThreadData *ThData; */
    ThreadPoolJob job;

    DLNA_LOGV("[VPPDLNA][%s][%d]:Inside SearchByTarget\n",__FUNCTION__,
                    __LINE__);

    requestType = ssdp_request_type1(St);
    if (requestType == SSDP_SERROR){

        DLNA_LOGE("[VPPDLNA][%s][%d]:Invalid ssdp request type. Valid"
            "\n",__FUNCTION__, __LINE__);
        return UPNP_E_INVALID_PARAM;
    }
    timeTillRead = Mx;
    if (timeTillRead < MIN_SEARCH_TIME)
        timeTillRead = MIN_SEARCH_TIME;
    else if (timeTillRead > MAX_SEARCH_TIME)
        timeTillRead = MAX_SEARCH_TIME;
    CreateClientRequestPacket(ReqBufv4, timeTillRead, St, AF_INET);

#ifdef UPNP_ENABLE_IPV6
    CreateClientRequestPacket(ReqBufv6, timeTillRead, St, AF_INET6);
    CreateClientRequestPacketUlaGua(ReqBufv6UlaGua, timeTillRead, St, AF_INET6);
#endif

    memset(&__ss_v4, 0, sizeof(__ss_v4));
    destAddr4->sin_family = AF_INET;
    (void)inet_pton(AF_INET, SSDP_IP, &destAddr4->sin_addr);
    destAddr4->sin_port = htons(SSDP_PORT);

#ifdef UPNP_ENABLE_IPV6
    memset(&__ss_v6, 0, sizeof(__ss_v6));
    destAddr6->sin6_family = AF_INET6;
    (void)inet_pton(AF_INET6, SSDP_IPV6_SITELOCAL, &destAddr6->sin6_addr);
    destAddr6->sin6_port = htons(SSDP_PORT);
    destAddr6->sin6_scope_id = gIF_INDEX;
#endif


    /* add search criteria to list */
    HandleLock();
#if 0
    if (GetClientHandleInfo(&handle, &ctrlpt_info) != HND_CLIENT) {
        HandleUnlock();
        return UPNP_E_INTERNAL_ERROR;
    }
#endif

    if (GetHandleInfo(clHdl, &ctrlpt_info) != HND_CLIENT){
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,clHdl);
        return UPNP_E_INTERNAL_ERROR;
    }

    newArg = (SsdpSearchArg *) UPNP_MALLOC(sizeof(SsdpSearchArg));
    if (newArg == NULL)  /*Lint fix - v70917*/
    {
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][:%d]-:Memory Allocation Failure\r\n",
            __FUNCTION__,__LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }

    newArg->searchTarget = UPNP_STRDUP(St);
    if (newArg->searchTarget == NULL)  /*Lint fix - v70917*/
    {
        UPNP_FREE(newArg);
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]:Memory allocation failure inside "
            "strdup\n",__FUNCTION__, __LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }

    newArg->cookie = Cookie;
    newArg->requestType = requestType;
    pstExpData = (SearchExpiredData *)UPNP_MALLOC(sizeof(SearchExpiredData));
    if (pstExpData == NULL)  /*Lint fix - v70917*/
    {
        UPNP_FREE(newArg->searchTarget);
        UPNP_FREE(newArg);
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]:Memory allocation failure "
            "\n",__FUNCTION__, __LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }

    pstExpData->clientHdl = clHdl;

    (void)TPJobInit(&job, (start_routine) searchExpired, pstExpData);
    (void)TPJobSetPriority(&job, MED_PRIORITY);
    (void)TPJobSetFreeFunction(&job, (free_routine) free);
    /* Schedule a timeout event to remove search Arg */
    (void)TimerThreadSchedule(&gTimerThread, timeTillRead * 1000,
                REL_SEC, &job, SHORT_TERM, &(pstExpData->threadID));
    newArg->timeoutEventId = pstExpData->threadID;

    (void)ListAddTail(&ctrlpt_info->SsdpSearchList, newArg);
    HandleUnlock();
    /* End of lock */

    FD_ZERO(&wrSet);
    if (ctrlpt_info->ssdpReadSocketIp4 != INVALID_SOCKET) {
        (void)setsockopt(ctrlpt_info->ssdpReadSocketIp4, IPPROTO_IP,
            IP_MULTICAST_IF, (char *)&addrv4, sizeof(addrv4));
        FD_SET(ctrlpt_info->ssdpReadSocketIp4, &wrSet);
        max_fd = Max(max_fd, ctrlpt_info->ssdpReadSocketIp4);
    }
#ifdef UPNP_ENABLE_IPV6
    if (ctrlpt_info->ssdpReadSocketIp6 != INVALID_SOCKET) {
        (void)setsockopt(ctrlpt_info->ssdpReadSocketIp6, IPPROTO_IPV6,
            IPV6_MULTICAST_IF,(char *)&gIF_INDEX, sizeof(gIF_INDEX));
        FD_SET(ctrlpt_info->ssdpReadSocketIp6, &wrSet);
        max_fd = Max(max_fd, ctrlpt_info->ssdpReadSocketIp6);
    }
#endif
    ret = select(max_fd + 1, NULL, &wrSet, NULL, NULL);
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA][%s][%d]:SSDP_LIB: Error in select(): %s\n",
            __FUNCTION__,__LINE__,errorBuffer);
        (void)shutdown(ctrlpt_info->ssdpReadSocketIp4, SD_BOTH);
        UpnpCloseSocket(ctrlpt_info->ssdpReadSocketIp4);
#ifdef UPNP_ENABLE_IPV6
        (void)shutdown(ctrlpt_info->ssdpReadSocketIp6, SD_BOTH);
        UpnpCloseSocket(ctrlpt_info->ssdpReadSocketIp6);
#endif
        return UPNP_E_INTERNAL_ERROR;
    }
#ifdef UPNP_ENABLE_IPV6
    if (ctrlpt_info->ssdpReadSocketIp6 != INVALID_SOCKET &&
        FD_ISSET(ctrlpt_info->ssdpReadSocketIp6, &wrSet)) {
        int NumCopy = 0;

        while (NumCopy < NUM_SSDP_COPY) {
            sendto(ctrlpt_info->ssdpReadSocketIp6,
                   ReqBufv6UlaGua, strlen(ReqBufv6UlaGua), 0,
                   (struct sockaddr *)&__ss_v6,
                   sizeof(struct sockaddr_in));
            NumCopy++;
            imillisleep(SSDP_PAUSE);
        }
        NumCopy = 0;
        (void)inet_pton(AF_INET6, SSDP_IPV6_LINKLOCAL, &destAddr6->sin6_addr);
        while (NumCopy < NUM_SSDP_COPY) {
            DLNA_LOGV("[VPPDLNA]:>>> SSDP SEND M-SEARCH >>>\n%s\n",
                   ReqBufv6);
            sendto(ctrlpt_info->ssdpReadSocketIp6,
                   ReqBufv6, strlen(ReqBufv6), 0,
                   (struct sockaddr *)&__ss_v6,
                   sizeof(struct sockaddr_in6));
            NumCopy++;
            imillisleep(SSDP_PAUSE);
        }
    }
#endif /* IPv6 */
    if (ctrlpt_info->ssdpReadSocketIp4 != INVALID_SOCKET &&
        FD_ISSET(ctrlpt_info->ssdpReadSocketIp4, &wrSet)) {
        int NumCopy = 0;
        while (NumCopy < NUM_SSDP_COPY) {
            DLNA_LOGV("[VPPDLNA]:>>> SSDP SEND M-SEARCH >>>\n%s\n",
                   ReqBufv4);
            (void)sendto(ctrlpt_info->ssdpReadSocketIp4,
                   ReqBufv4, strlen(ReqBufv4), 0,
                   (struct sockaddr *)&__ss_v4,
                   sizeof(struct sockaddr_in));
            NumCopy++;
            imillisleep(SSDP_PAUSE);
        }
    }

    return 1;
}


#endif /* EXCLUDE_SSDP */
#endif /* INCLUDE_CLIENT_APIS */

/* @} SSDPlib */
