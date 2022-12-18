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

#ifndef WIN32
    #include <sys/param.h>
#endif /* WIN32 */

#include "config.h"

#if EXCLUDE_SSDP == 0

#include "ssdplib.h"

#include "httpparser.h"
#include "httpreadwrite.h"
#include "membuffer.h"
#include "miniserver.h"
#include "sock.h"
#include "ThreadPool.h"
#include "upnpapi.h"

/*lint -save -e* */
#include <stdio.h>
/*lint -restore * */

#define MAX_TIME_TOREAD  45

#ifdef INCLUDE_DEVICE_APIS
static const char SERVICELIST_STR[] = "serviceList";

int AdvertiseAndReply(int AdFlag, UpnpDevice_Handle Hnd,
              enum SsdpSearchType SearchType,
              struct sockaddr *DestAddr, char *DeviceType,
              char *DeviceUDN, char *ServiceType, int Exp)
{
    int retVal = UPNP_E_SUCCESS;
    long unsigned int i;
    long unsigned int j;
    int defaultExp = DEFAULT_MAXAGE;
    struct Handle_Info *SInfo = NULL;
    char UDNstr[100];
    char devType[100];
    char servType[100];
    IXML_NodeList *nodeList = NULL;
    IXML_NodeList *tmpNodeList = NULL;
    IXML_Node *tmpNode = NULL;
    IXML_Node *tmpNode2 = NULL;
    IXML_Node *textNode = NULL;
    const DOMString tmpStr;
    char SERVER[200];
    const DOMString dbgStr;
    int NumCopy = 0;

    DLNA_LOGV("[VPPDLNA][%s][%d]:Inside AdvertiseAndReply with AdFlag=%d "
            " SearchType=%d \r\nDeviceType=%s DeviceUDN:%s ServiceType:%s\n",
            __FUNCTION__,__LINE__,AdFlag, SearchType,  DeviceType,
            DeviceUDN, ServiceType);

    /* Use a read lock */
    HandleReadLock();
    if (GetHandleInfo(Hnd, &SInfo) != HND_DEVICE) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n", __FUNCTION__,__LINE__,Hnd);
        retVal = UPNP_E_INVALID_HANDLE;
        goto end_function;
    }
    defaultExp = SInfo->MaxAge;
    /* get server info */
    get_sdk_info(SERVER,(sizeof(SERVER)-1));
    /* parse the device list and send advertisements/replies */
    while (NumCopy == 0 || (AdFlag && NumCopy < NUM_SSDP_COPY)) {
        if (NumCopy != 0)
            imillisleep(SSDP_PAUSE);
        NumCopy++;
        for (i = 0;; i++) {
            DLNA_LOGV("[VPPDLNA][%s][%d]:Entering new device list "
                "with i = %lu\n\n", __FUNCTION__,__LINE__,i);
            tmpNode = ixmlNodeList_item(SInfo->DeviceList, i);
            if (!tmpNode) {
                DLNA_LOGV("[VPPDLNA][%s][%d]:Exiting new device list "
                    "with i = %lu\n\n", __FUNCTION__,__LINE__,i);
                break;
            }

            dbgStr = ixmlNode_getNodeName(tmpNode);
            DLNA_LOGV("[VPPDLNA][%s][%d]:Extracting device type once for %s\n",
                   __FUNCTION__,__LINE__,dbgStr);
            ixmlNodeList_free(nodeList);
            nodeList =
            ixmlElement_getElementsByTagName((IXML_Element *) tmpNode,
                                                "deviceType");
            if (!nodeList)
                continue;

            dbgStr = ixmlNode_getNodeName(tmpNode);
            tmpNode2 = ixmlNodeList_item(nodeList, 0);
            if (!tmpNode2)
                continue;
            textNode = ixmlNode_getFirstChild(tmpNode2);
            if (!textNode)
                continue;
            tmpStr = ixmlNode_getNodeValue(textNode);
            if (!tmpStr)
                continue;

            HISTRCPY(devType, tmpStr);
            DLNA_LOGV("[VPPDLNA][%s][%d]:Extracted device type = %s\n",
                    __FUNCTION__,__LINE__,devType);

            if (!tmpNode) {
                DLNA_LOGV("[VPPDLNA][%s][%d]:TempNode is NULL\n",__FUNCTION__,
                    __LINE__);
            }

            dbgStr = ixmlNode_getNodeName(tmpNode);

            DLNA_LOGV("[VPPDLNA][%s][%d]:Extracting UDN for %s\n",
                    __FUNCTION__,__LINE__,dbgStr);

            ixmlNodeList_free(nodeList);
            nodeList =
            ixmlElement_getElementsByTagName((IXML_Element *) tmpNode, "UDN");
            if (!nodeList) {
                DLNA_LOGV("[VPPDLNA][%s][%d]:UDN not found!\n",__FUNCTION__,
                    __LINE__);
                continue;
            }

            tmpNode2 = ixmlNodeList_item(nodeList, 0);
            if (!tmpNode2) {
                DLNA_LOGV("[VPPDLNA][%s][%d]:UDN not found!\n",__FUNCTION__,
                    __LINE__);
                continue;
            }

            textNode = ixmlNode_getFirstChild(tmpNode2);
            if (!textNode) {
                DLNA_LOGV("[VPPDLNA][%s][%d]:UDN not found!\n",__FUNCTION__,
                    __LINE__);
                continue;
            }

            tmpStr = ixmlNode_getNodeValue(textNode);
            if (!tmpStr) {
                DLNA_LOGV("[VPPDLNA][%s][%d]:UDN not found!\n",__FUNCTION__,
                    __LINE__);
                continue;
            }

            HISTRCPY(UDNstr, tmpStr);
            DLNA_LOGV("[VPPDLNA][%s][%d]:Sending UDNStr = %s \n", __FUNCTION__,
                        __LINE__,UDNstr);

            if (AdFlag) {
                /* send the device advertisement */
                if (AdFlag == 1) {
                    (void)DeviceAdvertisement(devType, i == 0,
                                UDNstr,
                                SInfo->DescURL, Exp,
                                SInfo->DeviceAf);
                } else {
                    /* AdFlag == -1 */
                    (void)DeviceShutdown(devType, i == 0, UDNstr,
                               SERVER, SInfo->DescURL,
                               Exp, SInfo->DeviceAf);
                }
            } else {
                switch (SearchType) {
                case SSDP_ALL:
                    (void)DeviceReply(DestAddr, devType, i == 0,
                            UDNstr, SInfo->DescURL,
                            defaultExp);
                    break;
                case SSDP_ROOTDEVICE:
                    if (i == 0) {
                        (void)SendReply(DestAddr, devType, 1,
                              UDNstr,
                              SInfo->DescURL,
                              defaultExp, 0);
                    }
                    break;
                case SSDP_DEVICEUDN: {
                    if (DeviceUDN && strlen(DeviceUDN) != 0) {
                        if (strcasecmp(DeviceUDN, UDNstr)) {
                            DLNA_LOGV("[VPPDLNA][%s][%d]:DeviceUDN=%s and"
                                " search UDN=%s Did Not match\n",__FUNCTION__,
                                __LINE__,UDNstr,DeviceUDN);
                            break;
                        } else {
                            DLNA_LOGV("[VPPDLNA][%s][%d]:DeviceUDN=%s and "
                                "search UDN=%s MATCH\n", __FUNCTION__,__LINE__,
                                UDNstr, DeviceUDN);
                            (void)SendReply(DestAddr, devType, 0, UDNstr, SInfo->DescURL, defaultExp, 0);
                            break;
                        }
                    }
                }
                break;
                case SSDP_DEVICETYPE: {
                    if (!strncasecmp(DeviceType, devType, strlen(DeviceType) - 2)) {
                        char *ptr = DeviceType + strlen(DeviceType);
                        while ( *ptr != ':')
                        {
                            ptr--;
                        }

                        ptr++;

                        if (atoi(ptr) <= atoi(&devType[strlen(devType) - 1])) {
                            /* the requested version is lower than the device version
                             * must reply with the lower version number */
                            DLNA_LOGV("[VPPDLNA][%s][%d]: Requested DeviceType=%s and "
                            "search devType=%s MATCH\n",__FUNCTION__,__LINE__,
                                   devType, DeviceType);
                            (void)SendReply(DestAddr, DeviceType, 0, UDNstr, SInfo->DescURL,
                                  defaultExp, 1);
                        } else {
                            DLNA_LOGV("[VPPDLNA][%s][%d]: Requested DeviceType=%s and "
                                "search devType=%s DID NOT MATCH\n",__FUNCTION__
                                   ,__LINE__, devType, DeviceType);
                        }
                    } else {
                        DLNA_LOGV("[VPPDLNA][%s][%d]: Requested DeviceType=%s and "
                            "search devType=%s DID NOT MATCH\n",__FUNCTION__,
                            __LINE__,devType, DeviceType);
                    }
                    break;
                }

                default:
                    break;
                }
            }
            /* send service advertisements for services corresponding
             * to the same device */
            DLNA_LOGV("[VPPDLNA][%s][%d]:Sending service Advertisement\n",
                        __FUNCTION__,__LINE__);
            /* Correct service traversal such that each device's serviceList
             * is directly traversed as a child of its parent device. This
             * ensures that the service's alive message uses the UDN of
             * the parent device. */
            tmpNode = ixmlNode_getFirstChild(tmpNode);
            while (tmpNode) {
                dbgStr = ixmlNode_getNodeName(tmpNode);
                if (!strncmp
                    (dbgStr, SERVICELIST_STR,
                     sizeof SERVICELIST_STR)) {
                    break;
                }
                tmpNode = ixmlNode_getNextSibling(tmpNode);
            }
            ixmlNodeList_free(nodeList);
            if (!tmpNode) {
                nodeList = NULL;
                continue;
            }
            nodeList = ixmlElement_getElementsByTagName((IXML_Element *) tmpNode, "service");
            if (!nodeList) {
                DLNA_LOGE("[VPPDLNA][%s][%d]:Service not found \n",
                    __FUNCTION__,__LINE__);
                continue;
            }
            for (j = 0;; j++) {
                tmpNode = ixmlNodeList_item(nodeList, j);
                if (!tmpNode) {
                    break;
                }

                ixmlNodeList_free(tmpNodeList);
                tmpNodeList = ixmlElement_getElementsByTagName((IXML_Element *) tmpNode, "serviceType");
                if (!tmpNodeList) {
                    DLNA_LOGV("[VPPDLNA][%s][%d]:ServiceType not found \n",
                        __FUNCTION__,__LINE__);
                    continue;
                }
                tmpNode2 = ixmlNodeList_item(tmpNodeList, 0);
                if (!tmpNode2)
                    continue;
                textNode = ixmlNode_getFirstChild(tmpNode2);
                if (!textNode)
                    continue;
                /* servType is of format Servicetype:ServiceVersion */
                tmpStr = ixmlNode_getNodeValue(textNode);
                if (!tmpStr)
                    continue;
                HISTRCPY(servType, tmpStr);
                DLNA_LOGV("[VPPDLNA][%s][%d]:ServiceType = %s\n", __FUNCTION__,
                            __LINE__,servType);
                if (AdFlag) {
                    if (AdFlag == 1) {
                        (void)ServiceAdvertisement(UDNstr,
                            servType, SInfo->DescURL,
                            Exp, SInfo->DeviceAf);
                    } else {
                        /* AdFlag == -1 */
                        (void)ServiceShutdown(UDNstr,
                            servType, SInfo->DescURL,
                            Exp, SInfo->DeviceAf);
                    }
                } else {
                    switch (SearchType) {
                    case SSDP_ALL:
                        (void)ServiceReply(DestAddr, servType,
                                 UDNstr,
                                 SInfo->DescURL,
                                 defaultExp);
                        break;
                    case SSDP_SERVICE:
                        if (ServiceType) {
                            if (!strncasecmp(ServiceType, servType, strlen(ServiceType) - 2)) {
                                char *ptr = ServiceType + strlen(ServiceType);
                                while ( *ptr != ':')
                                {
                                    ptr--;
                                }

                                ptr++;

                                if (atoi(ptr) <= atoi(&servType[strlen(servType) - 1])) {
                                    /* the requested version is lower than the service version
                                     * must reply with the lower version number */
                                    DLNA_LOGV("[VPPDLNA][%s][%d]: Requested ServiceType=%s"
                                            " and search servType=%s MATCH\n",
                                            __FUNCTION__,__LINE__,ServiceType,
                                            servType);
                                    (void)SendReply(DestAddr, ServiceType, 0, UDNstr, SInfo->DescURL,
                                          defaultExp, 1);
                                } else {
                                    DLNA_LOGV("[VPPDLNA][%s][%d]: Requested ServiceType=%s"
                                    " and search servType=%s Requested version"
                                    " is higher than the supported \n",
                                       __FUNCTION__,__LINE__,ServiceType,
                                       servType);
                                }
                            } else {
                                DLNA_LOGV("[VPPDLNA][%s][%d]: Requested ServiceType=%s "
                                    "And search servType=%s DID NOT MATCH\n",
                                    __FUNCTION__,__LINE__,ServiceType, servType);
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
            ixmlNodeList_free(tmpNodeList);
            tmpNodeList = NULL;
            ixmlNodeList_free(nodeList);
            nodeList = NULL;
        }
    }

end_function:
    ixmlNodeList_free(tmpNodeList);
    ixmlNodeList_free(nodeList);
    DLNA_LOGV("[VPPDLNA][%s][%d]:Exiting AdvertiseAndReply.\n",__FUNCTION__,
        __LINE__);
    HandleUnlock();

    return retVal;
}
#endif /* INCLUDE_DEVICE_APIS */

int unique_service_name(char *cmd, SsdpEvent *Evt)
{
    char TempBuf[COMMAND_LEN];
    char *TempPtr = NULL;
    char *Ptr = NULL;
    char *ptr1 = NULL;
    char *ptr2 = NULL;
    char *ptr3 = NULL;
    int CommandFound = 0;
    size_t n = 0;

    if ((TempPtr = strstr(cmd, "uuid:schemas")) != NULL) {
        ptr1 = strstr(cmd, ":device");
        if (ptr1 != NULL)
            ptr2 = strstr(ptr1 + 1, ":");
        else
            return -1;
        if (ptr2 != NULL)
            ptr3 = strstr(ptr2 + 1, ":");
        else
            return -1;
        if (ptr3 != NULL)
            snprintf(Evt->UDN, sizeof(Evt->UDN)/sizeof(char),"uuid:%s", ptr3 + 1);
        else
            return -1;
        ptr1 = strstr(cmd, ":");
        if (ptr1 != NULL) {
            n = (size_t) (ptr3 - ptr1);
            strncpy(TempBuf, ptr1, n);
            TempBuf[n] = '\0';
            snprintf(Evt->DeviceType, sizeof(Evt->DeviceType)/sizeof(char),"urn%s", TempBuf);
        } else
            return -1;
        return 0;
    }
    if ((TempPtr = strstr(cmd, "uuid")) != NULL) {
        if ((Ptr = strstr(cmd, "::")) != NULL) {
            n = (size_t) (Ptr - TempPtr);
            strncpy(Evt->UDN, TempPtr, n);
            Evt->UDN[n] = '\0';
        } else
            HISTRCPY(Evt->UDN, TempPtr);
        CommandFound = 1;
    }
    if (strstr(cmd, "urn:") != NULL && strstr(cmd, ":service:") != NULL) {
        if ((TempPtr = strstr(cmd, "urn")) != NULL) {
            HISTRCPY(Evt->ServiceType, TempPtr);
            CommandFound = 1;
        }
    }
    if (strstr(cmd, "urn:") != NULL && strstr(cmd, ":device:") != NULL) {
        if ((TempPtr = strstr(cmd, "urn")) != NULL) {
            HISTRCPY(Evt->DeviceType, TempPtr);
            CommandFound = 1;
        }
    }
    if ((TempPtr = strstr(cmd, "::upnp:rootdevice")) != NULL) {
        /* Everything before "::upnp::rootdevice" is the UDN. */
        if (TempPtr != cmd) {
            n = (size_t) (TempPtr - cmd);
            strncpy(Evt->UDN, cmd, n);
            Evt->UDN[n] = 0;
            CommandFound = 1;
        }
    }
    if (CommandFound == 0)
        return -1;

    return 0;
}

enum SsdpSearchType ssdp_request_type1(char *cmd)
{
    if (strstr(cmd, ":all"))
        return SSDP_ALL;
    if (strstr(cmd, ":rootdevice"))
        return SSDP_ROOTDEVICE;
    if (strstr(cmd, "uuid:"))
        return SSDP_DEVICEUDN;
    if (strstr(cmd, "urn:") && strstr(cmd, ":device:"))
        return SSDP_DEVICETYPE;
    if (strstr(cmd, "urn:") && strstr(cmd, ":service:"))
        return SSDP_SERVICE;
    return SSDP_SERROR;
}

int ssdp_request_type(char *cmd, SsdpEvent *Evt)
{
    /* clear event */
    memset(Evt, 0, sizeof(SsdpEvent));
    (void)unique_service_name(cmd, Evt);
    Evt->ErrCode = NO_ERROR_FOUND;
    if ((Evt->RequestType = ssdp_request_type1(cmd)) == SSDP_SERROR) {
        Evt->ErrCode = E_HTTP_SYNTEX;
        return -1;
    }
    return 0;
}

/*!
 * \brief Frees the ssdp request.
 */
static void free_ssdp_event_handler_data(
    /*! [in] ssdp_thread_data structure. This structure contains SSDP
     * request message. */
    void *the_data)
{
    ssdp_thread_data *data = (ssdp_thread_data *) the_data;

    if (data != NULL) {
        http_message_t *hmsg = &data->parser.msg;
        /* free data */
        httpmsg_destroy(hmsg);
        UPNP_FREE(data);
    }
}

/*!
 * \brief Does some quick checking of the ssdp msg.
 *
 * \return TRUE if msg is valid, else FALSE.
 */
static UPNP_INLINE int valid_ssdp_msg(
    /*! [in] ssdp_thread_data structure. This structure contains SSDP
     * request message. */
    http_message_t * hmsg)
{
    memptr hdr_value;
    char ipv4_addr[64] = {0};
    char ipv6_addr1[64] = {0};
    char ipv6_addr2[64] = {0};
    char ipv6_addr3[64] = {0};
    char ipv6_addr4[64] = {0};
    char port[12];

    /* check for valid methods - NOTIFY or M-SEARCH */
    if (hmsg->method != HTTPMETHOD_NOTIFY &&
        hmsg->method != HTTPMETHOD_MSEARCH &&
        hmsg->request_method != HTTPMETHOD_MSEARCH) {
        return FALSE;
    }
    if (hmsg->request_method != HTTPMETHOD_MSEARCH) {
        /* check PATH == "*" */
        if (hmsg->uri.type != RELATIVE ||
            strncmp("*", hmsg->uri.pathquery.buff,
                hmsg->uri.pathquery.size) != 0) {
            return FALSE;
        }
        /* check HOST header */

        /* j70578 - for using different SSDP port */
        memset(port,0,sizeof(port));
        snprintf(port, sizeof(port)/sizeof(char),"%u", SSDP_PORT);

        memcpy (ipv4_addr, "239.255.255.250:", strlen("239.255.255.250:"));
        memcpy (ipv4_addr + strlen(ipv4_addr), port, strlen(port));
        memcpy (ipv6_addr1, "[FF02::C]:", strlen("[FF02::C]:"));
        memcpy (ipv6_addr1 + strlen(ipv6_addr1), port, strlen(port));
        memcpy (ipv6_addr2, "[ff02::c]:", strlen("[ff02::c]:"));
        memcpy (ipv6_addr2 + strlen(ipv6_addr2), port, strlen(port));
        memcpy (ipv6_addr3, "[FF05::C]:", strlen("[FF05::C]:"));
        memcpy (ipv6_addr3 + strlen(ipv6_addr3), port, strlen(port));
        memcpy (ipv6_addr4, "[ff05::c]:", strlen("[ff05::c]:"));
        memcpy (ipv6_addr4 + strlen(ipv6_addr4), port, strlen(port));

        if (httpmsg_find_hdr(hmsg, HDR_HOST, &hdr_value) == NULL ||
            (memptr_cmp(&hdr_value, ipv4_addr) != 0 &&
             memptr_cmp(&hdr_value, ipv6_addr1) != 0 &&
             memptr_cmp(&hdr_value, ipv6_addr2) != 0 &&
             memptr_cmp(&hdr_value, ipv6_addr3) != 0 &&
             memptr_cmp(&hdr_value, ipv6_addr4) != 0))
        {
                DLNA_LOGI("[VPPDLNA]:Invalid HOST header from SSDP message\n");

            return FALSE;
        }
    }

    /* passed quick check */
    return TRUE;
}

/*!
 * \brief Parses the message and dispatches it to a handler which handles the
 * ssdp request msg.
 *
 * \return 0 if successful, -1 if error.
 */
static UPNP_INLINE int start_event_handler(
    /*! [in] ssdp_thread_data structure. This structure contains SSDP
     * request message. */
    void *Data)
{
    http_parser_t *parser = NULL;
    parse_status_t status;
    ssdp_thread_data *data = (ssdp_thread_data *) Data;

    parser = &data->parser;
    status = parser_parse(parser);
    if (status == PARSE_FAILURE) {
        if (parser->msg.method != HTTPMETHOD_NOTIFY ||
            !parser->valid_ssdp_notify_hack) {
            DLNA_LOGV("[VPPDLNA]:SSDP recvd bad msg code = %d\n", status);
            /* ignore bad msg, or not enuf mem */
            goto error_handler;
        }
        /* valid notify msg */
    } else if (status != PARSE_SUCCESS) {
        DLNA_LOGV("[VPPDLNA]:SSDP recvd bad msg code = %d\n", status);

        goto error_handler;
    }
    /* check msg */
    if (valid_ssdp_msg(&parser->msg) != TRUE) {
        goto error_handler;
    }
    /* done; thread will free 'data' */
    return 0;

 error_handler:
    free_ssdp_event_handler_data(data);
    return -1;
}

/*!
 * \brief This function is a thread that handles SSDP requests.
 */
static void ssdp_event_handler_thread(
    /*! [] ssdp_thread_data structure. This structure contains SSDP
     * request message. */
    void *the_data)
{
    ssdp_thread_data *data = (ssdp_thread_data *) the_data;
    http_message_t *hmsg = &data->parser.msg;

    DLNA_LOGV("[VPPDLNA]:\nInside ssdp_event_handler_thread to handle handle SSDP\n");

    if (start_event_handler(the_data) != 0)
        return;
    /* send msg to device or ctrlpt */
    if (hmsg->method == HTTPMETHOD_NOTIFY ||
        hmsg->request_method == HTTPMETHOD_MSEARCH) {
#ifdef INCLUDE_CLIENT_APIS
        ssdp_handle_ctrlpt_msg(hmsg,
                       data,
                       FALSE, NULL);
#endif /* INCLUDE_CLIENT_APIS */
    } else {
        ssdp_handle_device_request(hmsg,
                       &data->dest_addr);
    }

    /* free data */
    free_ssdp_event_handler_data(data);
}


bool isSsdpResponseMsg(SOCKET ssdpSocket)
{
    int iLoop;

    for (iLoop = 0; iLoop < DLNA_MAX_CTRLPOINT_CLIENT; iLoop++)
    {
        if ((ssdpSocket == gstMiniServerSockArray.ssdpReqSock4[iLoop])
        #ifdef UPNP_ENABLE_IPV6
            || ((ssdpSocket == gstMiniServerSockArray.ssdpReqSock6[iLoop]))
        #endif
            )
        {
            return TRUE;
        }
    }

    return FALSE;

}

void readFromSSDPSocket(SOCKET ssdpSocket)
{
    char *requestBuf = NULL;
    char staticBuf[BUFSIZE];
    struct sockaddr_storage __ss;
    ThreadPoolJob job;
    ssdp_thread_data *data = NULL;
    socklen_t socklen = sizeof(__ss);
    ssize_t byteReceived = 0;
    char ntop_buf[64];

    memset(ntop_buf,0,sizeof(ntop_buf));
    requestBuf = staticBuf;
    /* in case memory can't be allocated, still drain the socket using a
     * static buffer. */
    data = UPNP_MALLOC(sizeof(ssdp_thread_data));
    if (data) {
        /* initialize parser */
#ifdef INCLUDE_CLIENT_APIS
        if (isSsdpResponseMsg(ssdpSocket))
            parser_response_init(&data->parser, HTTPMETHOD_MSEARCH);
        else
            parser_request_init(&data->parser);
#else /* INCLUDE_CLIENT_APIS */
        parser_request_init(&data->parser);
#endif /* INCLUDE_CLIENT_APIS */
        /* set size of parser buffer */
        if (membuffer_set_size(&data->parser.msg.msg, BUFSIZE) == 0)
            /* use this as the buffer for recv */
            requestBuf = data->parser.msg.msg.buf;
        else {
            UPNP_FREE(data);
            data = NULL;
        }
    }
    byteReceived = recvfrom(ssdpSocket, requestBuf, BUFSIZE - 1, 0,
                (struct sockaddr *)&__ss, &socklen);
    if (byteReceived > 0) {
        requestBuf[byteReceived] = '\0';
        if (__ss.ss_family == AF_INET)
            (void)inet_ntop(AF_INET,
                  &((struct sockaddr_in *)&__ss)->sin_addr,
                  ntop_buf, sizeof(ntop_buf));
#ifdef UPNP_ENABLE_IPV6
        else if (__ss.ss_family == AF_INET6)
            (void)inet_ntop(AF_INET6,
                  &((struct sockaddr_in6 *)&__ss)->sin6_addr,
                  ntop_buf, sizeof(ntop_buf));
#endif /* UPNP_ENABLE_IPV6 */
        else
            strncpy(ntop_buf, "<Invalid address family>",(sizeof(ntop_buf)-1));
        DLNA_LOGV("[VPPDLNA]:Start of received response ----------------------------------------------------\n"
               "%s\n"
               "End of received response ------------------------------------------------------\n"
               "From host %s\n", requestBuf, ntop_buf);
        /* add thread pool job to handle request */
        if (data != NULL) {
            data->parser.msg.msg.length += (size_t) byteReceived;
            /* null-terminate */
            data->parser.msg.msg.buf[byteReceived] = 0;
            data->ssdpReadSocket = ssdpSocket;
            memcpy(&data->dest_addr, &__ss, sizeof(__ss));
            (void)TPJobInit(&job, (start_routine)
                  ssdp_event_handler_thread, data);
            (void)TPJobSetFreeFunction(&job,
                         free_ssdp_event_handler_data);
            (void)TPJobSetPriority(&job, MED_PRIORITY);
            if (ThreadPoolAdd(&gRecvThreadPool, &job, NULL) != 0)
                free_ssdp_event_handler_data(data);
        }
    } else
        free_ssdp_event_handler_data(data);
}

/*!
 * \brief
 */
static int create_ssdp_sock_v4(
    /*! [] SSDP IPv4 socket to be created. */
    SOCKET *ssdpSock)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    int onOff;
    u_char ttl = 4;
    struct ip_mreq ssdpMcastAddr;
    struct sockaddr_storage __ss;
    struct sockaddr_in *ssdpAddr4 = (struct sockaddr_in *)&__ss;
    int ret = 0;
    struct in_addr addr;

    *ssdpSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (*ssdpSock == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in socket(): %s\n", errorBuffer);

        return UPNP_E_OUTOF_SOCKET;
    }
    onOff = 1;
    ret = setsockopt(*ssdpSock, SOL_SOCKET, SO_REUSEADDR,
             (char *)&onOff, sizeof(onOff));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() SO_REUSEADDR: %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_ERROR;
    }
#if defined(BSD) || defined(__OSX__) || defined(__APPLE__)
    onOff = 1;
    ret = setsockopt(*ssdpSock, SOL_SOCKET, SO_REUSEPORT,
             (char *)&onOff, sizeof(onOff));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() SO_REUSEPORT: %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_ERROR;
    }
#endif /* BSD, __OSX__, __APPLE__ */
    memset(&__ss, 0, sizeof(__ss));
    ssdpAddr4->sin_family = AF_INET;
    ssdpAddr4->sin_addr.s_addr = htonl(INADDR_ANY);
    ssdpAddr4->sin_port = htons(SSDP_PORT);
    ret = bind(*ssdpSock, (struct sockaddr *)ssdpAddr4, sizeof(*ssdpAddr4));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in bind(), addr=0x%08X, port=%d: %s\n",
               INADDR_ANY, SSDP_PORT, errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_BIND;
    }
    memset((void *)&ssdpMcastAddr, 0, sizeof(struct ip_mreq));
    ssdpMcastAddr.imr_interface.s_addr = inet_addr(gIF_IPV4);
    ssdpMcastAddr.imr_multiaddr.s_addr = inet_addr(SSDP_IP);
    ret = setsockopt(*ssdpSock, IPPROTO_IP, IP_ADD_MEMBERSHIP,
             (char *)&ssdpMcastAddr, sizeof(struct ip_mreq));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() IP_ADD_MEMBERSHIP (join multicast group): %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_ERROR;
    }
    /* Set multicast interface. */
    memset((void *)&addr, 0, sizeof(struct in_addr));
    addr.s_addr = inet_addr(gIF_IPV4);
    ret = setsockopt(*ssdpSock, IPPROTO_IP, IP_MULTICAST_IF,
             (char *)&addr, sizeof addr);
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() IP_MULTICAST_IF (set multicast interface): %s\n",
               errorBuffer);
        /* This is probably not a critical error, so let's continue. */
    }
    /* result is not checked becuase it will fail in WinMe and Win9x. */
    ret = setsockopt(*ssdpSock, IPPROTO_IP,
             IP_MULTICAST_TTL, &ttl, sizeof(ttl));
    onOff = 1;
    ret = setsockopt(*ssdpSock, SOL_SOCKET, SO_BROADCAST,
             (char *)&onOff, sizeof(onOff));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() SO_BROADCAST (set broadcast): %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_NETWORK_ERROR;
    }

    return UPNP_E_SUCCESS;
}

#if INCLUDE_CLIENT_APIS
/*!
 * \brief Creates the SSDP IPv4 socket to be used by the control point.
 *
 * \return UPNP_E_SUCCESS on successful socket creation.
 */
static int create_ssdp_sock_reqv4(
    /*! [out] SSDP IPv4 request socket to be created. */
    SOCKET *ssdpReqSock)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    u_char ttl = 4;

    *ssdpReqSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (*ssdpReqSock == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in socket(): %s\n", errorBuffer);
        return UPNP_E_OUTOF_SOCKET;
    }

    (void)setsockopt(*ssdpReqSock, IPPROTO_IP, IP_MULTICAST_TTL,
           &ttl, sizeof(ttl));
    /* just do it, regardless if fails or not. */
    (void)sock_make_no_blocking(*ssdpReqSock);

    return UPNP_E_SUCCESS;
}

#ifdef UPNP_ENABLE_IPV6
/*!
 * \brief This function ...
 */
static int create_ssdp_sock_v6(
    /* [] SSDP IPv6 socket to be created. */
    SOCKET *ssdpSock)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    struct ipv6_mreq ssdpMcastAddr;
    struct sockaddr_storage __ss;
    struct sockaddr_in6 *ssdpAddr6 = (struct sockaddr_in6 *)&__ss;
    int onOff;
    int ret = 0;

    *ssdpSock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (*ssdpSock == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in socket(): %s\n", errorBuffer);

        return UPNP_E_OUTOF_SOCKET;
    }
    onOff = 1;
    ret = setsockopt(*ssdpSock, SOL_SOCKET, SO_REUSEADDR,
             (char *)&onOff, sizeof(onOff));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() SO_REUSEADDR: %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_ERROR;
    }
#if defined(BSD) || defined(__OSX__) || defined(__APPLE__)
    onOff = 1;
    ret = setsockopt(*ssdpSock, SOL_SOCKET, SO_REUSEPORT,
             (char *)&onOff, sizeof(onOff));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() SO_REUSEPORT: %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_ERROR;
    }
#endif /* BSD, __OSX__, __APPLE__ */
    memset(&__ss, 0, sizeof(__ss));
    ssdpAddr6->sin6_family = AF_INET6;
    ssdpAddr6->sin6_addr = in6addr_any;
    ssdpAddr6->sin6_scope_id = gIF_INDEX;
    ssdpAddr6->sin6_port = htons(SSDP_PORT);
    ret = bind(*ssdpSock, (struct sockaddr *)ssdpAddr6, sizeof(*ssdpAddr6));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in bind(), addr=0x%032lX, port=%d: %s\n",
               0lu, SSDP_PORT, errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_BIND;
    }
    memset((void *)&ssdpMcastAddr, 0, sizeof(ssdpMcastAddr));
    ssdpMcastAddr.ipv6mr_interface = gIF_INDEX;
    (void)inet_pton(AF_INET6, SSDP_IPV6_LINKLOCAL,
          &ssdpMcastAddr.ipv6mr_multiaddr);
    ret = setsockopt(*ssdpSock, IPPROTO_IPV6, IPV6_JOIN_GROUP,
            (char *)&ssdpMcastAddr, sizeof(ssdpMcastAddr));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() IPV6_JOIN_GROUP (join multicast group): %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_ERROR;
    }
    onOff = 1;
    ret = setsockopt(*ssdpSock, SOL_SOCKET, SO_BROADCAST,
             (char *)&onOff, sizeof(onOff));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() SO_BROADCAST (set broadcast): %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_NETWORK_ERROR;
    }

    return UPNP_E_SUCCESS;
}
#endif /* IPv6 */

#ifdef UPNP_ENABLE_IPV6
/*!
 * \brief This function ...
 */
static int create_ssdp_sock_v6_ula_gua(
    /*! [] SSDP IPv6 socket to be created. */
    SOCKET * ssdpSock)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    struct ipv6_mreq ssdpMcastAddr;
    struct sockaddr_storage __ss;
    struct sockaddr_in6 *ssdpAddr6 = (struct sockaddr_in6 *)&__ss;
    int onOff;
    int ret = 0;

    *ssdpSock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (*ssdpSock == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in socket(): %s\n", errorBuffer);

        return UPNP_E_OUTOF_SOCKET;
    }
    onOff = 1;
    ret = setsockopt(*ssdpSock, SOL_SOCKET, SO_REUSEADDR,
             (char *)&onOff, sizeof(onOff));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() SO_REUSEADDR: %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_ERROR;
    }
#if defined(BSD) || defined(__OSX__) || defined(__APPLE__)
    onOff = 1;
    ret = setsockopt(*ssdpSock, SOL_SOCKET, SO_REUSEPORT,
             (char *)&onOff, sizeof(onOff));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() SO_REUSEPORT: %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_ERROR;
    }
#endif /* BSD, __OSX__, __APPLE__ */
    memset(&__ss, 0, sizeof(__ss));
    ssdpAddr6->sin6_family = AF_INET6;
    ssdpAddr6->sin6_addr = in6addr_any;
    ssdpAddr6->sin6_scope_id = gIF_INDEX;
    ssdpAddr6->sin6_port = htons(SSDP_PORT);
    ret = bind(*ssdpSock, (struct sockaddr *)ssdpAddr6, sizeof(*ssdpAddr6));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in bind(), addr=0x%032lX, port=%d: %s\n",
               0lu, SSDP_PORT, errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_BIND;
    }
    memset((void *)&ssdpMcastAddr, 0, sizeof(ssdpMcastAddr));
    ssdpMcastAddr.ipv6mr_interface = gIF_INDEX;
    /* SITE LOCAL */
    (void)inet_pton(AF_INET6, SSDP_IPV6_SITELOCAL,
          &ssdpMcastAddr.ipv6mr_multiaddr);
    ret = setsockopt(*ssdpSock, IPPROTO_IPV6, IPV6_JOIN_GROUP,
            (char *)&ssdpMcastAddr, sizeof(ssdpMcastAddr));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() IPV6_JOIN_GROUP (join multicast group): %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_SOCKET_ERROR;
    }
    onOff = 1;
    ret = setsockopt(*ssdpSock, SOL_SOCKET, SO_BROADCAST,
             (char *)&onOff, sizeof(onOff));
    if (ret == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in setsockopt() SO_BROADCAST (set broadcast): %s\n",
               errorBuffer);
        (void)shutdown(*ssdpSock, SD_BOTH);
        UpnpCloseSocket(*ssdpSock);

        return UPNP_E_NETWORK_ERROR;
    }

    return UPNP_E_SUCCESS;
}
#endif /* IPv6 */

/*!
 * \brief Creates the SSDP IPv6 socket to be used by the control point.
 */
#ifdef UPNP_ENABLE_IPV6
static int create_ssdp_sock_reqv6(
    /* [out] SSDP IPv6 request socket to be created. */
    SOCKET *ssdpReqSock)
{
    char errorBuffer[ERROR_BUFFER_LEN];
    char hops = 1;

    *ssdpReqSock = socket(AF_INET6, SOCK_DGRAM, 0);
    if (*ssdpReqSock == -1) {
        strerror_r(errno, errorBuffer, ERROR_BUFFER_LEN);
        DLNA_LOGE("[VPPDLNA]:Error in socket(): %s\n", errorBuffer);
        return UPNP_E_OUTOF_SOCKET;
    }
    /* MUST use scoping of IPv6 addresses to control the propagation os SSDP
     * messages instead of relying on the Hop Limit (Equivalent to the TTL
     * limit in IPv4). */
    (void)setsockopt(*ssdpReqSock, IPPROTO_IPV6, IPV6_MULTICAST_HOPS,
           &hops, sizeof(hops));
    /* just do it, regardless if fails or not. */
    sock_make_no_blocking(*ssdpReqSock);

    return UPNP_E_SUCCESS;
}
#endif /* IPv6 */
#endif /* INCLUDE_CLIENT_APIS */

int get_ssdp_sockets(MiniServerSockArray * out)
{
    int retVal;
    int iLoop;

#if INCLUDE_CLIENT_APIS
    /* Create the IPv4 socket for SSDP REQUESTS */
    if (strlen(gIF_IPV4) > 0) {
        for (iLoop = 0; iLoop<DLNA_MAX_CTRLPOINT_CLIENT; iLoop++){
            retVal = create_ssdp_sock_reqv4(&out->ssdpReqSock4[iLoop]);
            if (retVal != UPNP_E_SUCCESS)
                return retVal;
        }
    } else{
        for (iLoop = 0; iLoop<DLNA_MAX_CTRLPOINT_CLIENT; iLoop++)
            out->ssdpReqSock4[iLoop] = INVALID_SOCKET;
    }
    /* Create the IPv6 socket for SSDP REQUESTS */
#ifdef UPNP_ENABLE_IPV6
    if (strlen(gIF_IPV6) > 0) {
        for (iLoop = 0; iLoop<DLNA_MAX_CTRLPOINT_CLIENT; iLoop++){
            retVal = create_ssdp_sock_reqv6(&out->ssdpReqSock6[iLoop]);
            if (retVal != UPNP_E_SUCCESS) {
                for (iLoop = 0; iLoop<DLNA_MAX_CTRLPOINT_CLIENT, iLoop++){
                    (void)shutdown(out->ssdpReqSock4[iLoop], SD_BOTH);
                    UpnpCloseSocket(out->ssdpReqSock4[iLoop]);
                }
                return retVal;
            }
        }
    } else{
        for (iLoop = 0; iLoop<DLNA_MAX_CTRLPOINT_CLIENT; iLoop++)
            out->ssdpReqSock6[iLoop] = INVALID_SOCKET;
    }
#endif /* IPv6 */
#endif /* INCLUDE_CLIENT_APIS */
    /* Create the IPv4 socket for SSDP */
    if (strlen(gIF_IPV4) > 0) {
        retVal = create_ssdp_sock_v4(&out->ssdpSock4);
        if (retVal != UPNP_E_SUCCESS) {
#ifdef INCLUDE_CLIENT_APIS
            for (iLoop = 0; iLoop<DLNA_MAX_CTRLPOINT_CLIENT; iLoop++){
                (void)shutdown(out->ssdpReqSock4[iLoop], SD_BOTH);
                UpnpCloseSocket(out->ssdpReqSock4[iLoop]);
                (void)shutdown(out->ssdpReqSock6[iLoop], SD_BOTH);
                UpnpCloseSocket(out->ssdpReqSock6[iLoop]);
            }

#endif /* INCLUDE_CLIENT_APIS */
            return retVal;
        }
    } else
        out->ssdpSock4 = INVALID_SOCKET;
    /* Create the IPv6 socket for SSDP */
#ifdef UPNP_ENABLE_IPV6
    if (strlen(gIF_IPV6) > 0) {
        retVal = create_ssdp_sock_v6(&out->ssdpSock6);
        if (retVal != UPNP_E_SUCCESS) {
            (void)shutdown(out->ssdpSock4, SD_BOTH);
            UpnpCloseSocket(out->ssdpSock4);
#ifdef INCLUDE_CLIENT_APIS
            for (iLoop = 0; iLoop<DLNA_MAX_CTRLPOINT_CLIENT; iLoop++){
                (void)shutdown(out->ssdpReqSock4[iLoop], SD_BOTH);
                UpnpCloseSocket(out->ssdpReqSock4[iLoop]);
                (void)shutdown(out->ssdpReqSock6[iLoop], SD_BOTH);
                UpnpCloseSocket(out->ssdpReqSock6[iLoop]);
            }
#endif /* INCLUDE_CLIENT_APIS */
            return retVal;
        }
    } else
        out->ssdpSock6 = INVALID_SOCKET;
    if (strlen(gIF_IPV6_ULA_GUA) > 0) {
        retVal = create_ssdp_sock_v6_ula_gua(&out->ssdpSock6UlaGua);
        if (retVal != UPNP_E_SUCCESS) {
            (void)shutdown(out->ssdpSock4, SD_BOTH);
            UpnpCloseSocket(out->ssdpSock4);
            (void)shutdown(out->ssdpSock6, SD_BOTH);
            UpnpCloseSocket(out->ssdpSock6);
#ifdef INCLUDE_CLIENT_APIS
            for (iLoop = 0; iLoop<DLNA_MAX_CTRLPOINT_CLIENT; iLoop++){
                (void)shutdown(out->ssdpReqSock4[iLoop], SD_BOTH);
                UpnpCloseSocket(out->ssdpReqSock4[iLoop]);
                (void)shutdown(out->ssdpReqSock6[iLoop], SD_BOTH);
                UpnpCloseSocket(out->ssdpReqSock6[iLoop]);
            }
#endif /* INCLUDE_CLIENT_APIS */
            return retVal;
        }
    } else
        out->ssdpSock6UlaGua = INVALID_SOCKET;
#endif /* UPNP_ENABLE_IPV6 */

    return UPNP_E_SUCCESS;
}
#endif /* EXCLUDE_SSDP */

/* @} SSDPlib */
