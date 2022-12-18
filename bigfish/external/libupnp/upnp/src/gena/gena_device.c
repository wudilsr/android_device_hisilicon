/*******************************************************************************
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
 ******************************************************************************/

/*!
 * \file
 */

#include "config.h"

#if EXCLUDE_GENA == 0
#ifdef INCLUDE_DEVICE_APIS

#include "gena.h"
#include "httpparser.h"
#include "httpreadwrite.h"
#include "parsetools.h"
#include "ssdplib.h"
#include "statcodes.h"
#include "sysdep.h"
#include "unixutil.h"
#include "upnpapi.h"
#include "uuid.h"

/*!
 * \brief Unregisters a device.
 *
 * \return UPNP_E_SUCCESS on success, GENA_E_BAD_HANDLE on failure.
 */
int genaUnregisterDevice(
    /*! [in] Device handle. */
    UpnpDevice_Handle device_handle)
{
    int ret = 0;
    struct Handle_Info *handle_info;

    HandleLock();
    if (GetHandleInfo(device_handle, &handle_info) != HND_DEVICE) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,device_handle);
        ret = GENA_E_BAD_HANDLE;
    } else {
        freeServiceTable(&handle_info->ServiceTable);
        ret = UPNP_E_SUCCESS;
    }
    HandleUnlock();

    return ret;
}

/*!
 * \brief Generates XML property set for notifications.
 *
 * \return UPNP_E_SUCCESS if successful else returns GENA_E_BAD_HANDLE.
 *
 * \note The XML_VERSION comment is NOT sent due to interoperability issues
 *  with other UPnP vendors.
 */
static int GeneratePropertySet(
    /*! [in] Array of variable names (go in the event notify). */
    char **names,
    /*! [in] Array of variable values (go in the event notify). */
    char **values,
    /*! [in] number of variables. */
    int count,
    /*! [out] PropertySet node in the string format. */
    DOMString *out)
{
    char *buffer;
    int counter = 0;
    size_t size = 0;
    int temp_counter = 0;

    temp_counter = temp_counter;

    /*size += strlen(XML_VERSION);*/
    size += strlen(XML_PROPERTYSET_HEADER);
    size += strlen("</e:propertyset>\n\n");
    for (temp_counter = 0, counter = 0; counter < count; counter++) {
        size += strlen( "<e:property>\n</e:property>\n" );
        size += 2 * strlen(names[counter]) +
            strlen(values[counter]) +
            strlen("<></>\n");
    }

    buffer = (char *)UPNP_MALLOC(size + 1);
    if (buffer == NULL)
    {
        DLNA_LOGE("[VPPDLNA][%s][:%d]-:Memory Allocation Failure\r\n",
            __FUNCTION__,__LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }
    memset(buffer, 0, size + 1);
    /*
    HISTRCPY(buffer,XML_VERSION);
    HISTRCAT(buffer, XML_PROPERTYSET_HEADER);
    */
    HISTRCPY(buffer, XML_PROPERTYSET_HEADER);
    for (counter = 0; counter < count; counter++) {
        HISTRCAT(buffer, "<e:property>\n");
        snprintf(&buffer[strlen(buffer)],(size - strlen(buffer)),
            "<%s>%s</%s>\n</e:property>\n",
            names[counter],
            values[counter],
            names[counter]);
    }
    HISTRCAT(buffer, "</e:propertyset>\n\n");

    /*[r72104][Internal review comments fix] No need to clone
        the buffer we can remove the free and assign it directly
        to the out parameter*/
    *out = buffer;

    return UPNP_E_SUCCESS;
}

/*!
 * \brief Frees memory used in notify_threads if the reference count is 0,
 * otherwise decrements the refrence count.
 */
static void free_notify_struct(
    /*! [in] Notify structure. */
    notify_thread_struct *input)
{
    (*input->reference_count)--;
    if (*input->reference_count == 0) {
        UPNP_FREE(input->headers);
        ixmlFreeDOMString(input->propertySet);
        UPNP_FREE(input->servId);
        UPNP_FREE(input->UDN);
        UPNP_FREE(input->reference_count);
    }
    UPNP_FREE(input);
}

/*!
 * \brief Sends the notify message and returns a reply.
 *
 * \return on success returns UPNP_E_SUCCESS, otherwise returns a UPNP error.
 *
 * \note called by genaNotify
 */
static UPNP_INLINE int notify_send_and_recv(
    /*! [in] subscription callback URL (URL of the control point). */
    uri_type *destination_url,
    /*! [in] Common HTTP headers. */
    membuffer *mid_msg,
    /*! [in] The evented XML. */
    char *propertySet,
    /*! [out] The response from the control point. */
    http_parser_t *response)
{
    uri_type url;
    SOCKET conn_fd;
    membuffer start_msg;
    int ret_code;
    int err_code;
    int timeout;
    SOCKINFO info;
    const char *CRLF = "\r\n";
    char *response_buf = NULL;
    int response_length = 0;
    /* connect */

    conn_fd = http_Connect(destination_url, &url);
    if (conn_fd < 0)
        /* return UPNP error */
        return UPNP_E_SOCKET_CONNECT;
    ret_code = sock_init(&info, conn_fd);
    if (ret_code) {
        (void)sock_destroy(&info, SD_BOTH);
        return ret_code;
    }
    /* make start line and HOST header */
    membuffer_init(&start_msg);
    if (http_MakeMessage(
            &start_msg, 1, 1,
            "q" "C" "s",
            HTTPMETHOD_NOTIFY, &url,
            mid_msg->buf) != 0) {
        membuffer_destroy(&start_msg);
        (void)sock_destroy(&info, SD_BOTH);
        return UPNP_E_OUTOF_MEMORY;
    }
    DLNA_LOGI("[VPPDLNA]:gena notify to: %.*s,time : %lld\n",
        (int)destination_url->hostport.text.size,
        destination_url->hostport.text.buff,GetNowmTime());
    timeout = GENA_NOTIFICATION_SENDING_TIMEOUT;
    /* send msg (note: end of notification will contain "\r\n" twice) */
    response_length = start_msg.length + strlen(propertySet) + strlen(CRLF);
    response_buf = (char *)malloc(response_length);
    if(response_buf != NULL)
    {
       memcpy(response_buf,start_msg.buf,start_msg.length);
       memcpy(response_buf + start_msg.length ,propertySet,strlen(propertySet));
       memcpy(response_buf + start_msg.length + strlen(propertySet),CRLF, strlen(CRLF));

       ret_code = http_SendMessage(&info, &timeout,
        "b",response_buf,response_length);
       free(response_buf);
    }
    else
    {
        ret_code = http_SendMessage(&info, &timeout,
            "bbb",
            start_msg.buf, start_msg.length,
            propertySet, strlen(propertySet),
            CRLF, strlen(CRLF));
    }
    if (ret_code) {
        membuffer_destroy(&start_msg);
        (void)sock_destroy(&info, SD_BOTH);
        return ret_code;
    }
    timeout = GENA_NOTIFICATION_ANSWERING_TIMEOUT;
    ret_code = http_RecvMessage(&info, response,
        HTTPMETHOD_NOTIFY, &timeout, &err_code, NULL);
    if (ret_code) {
        membuffer_destroy(&start_msg);
        (void)sock_destroy(&info, SD_BOTH);
        httpmsg_destroy(&response->msg);
        return ret_code;
    }
    /* should shutdown completely when closing socket */
    (void)sock_destroy(&info, SD_BOTH);
    membuffer_destroy(&start_msg);

    return UPNP_E_SUCCESS;
}

/*!
 * \brief Function to Notify a particular subscription of a particular event.
 *
 * In general the service should NOT be blocked around this call (this may
 * cause deadlock with a client).
 *
 * NOTIFY http request is sent and the reply is processed.
 *
 * \return GENA_SUCCESS if the event was delivered, otherwise returns the
 *  appropriate error code.
 */
static int genaNotify(
    /*! [in] Null terminated, includes all headers (including \\r\\n) except SID and SEQ. */
    char *headers,
    /*! [in] The evented XML. */
    char *propertySet,
    /*! [in] subscription to be Notified, assumes this is valid for life of function. */
    subscription *sub)
{
    size_t i;
    membuffer mid_msg;
    membuffer endmsg;
    uri_type *url;
    http_parser_t response;
    int return_code = -1;

    membuffer_init(&mid_msg);
    /* make 'end' msg (the part that won't vary with the destination) */
    endmsg.size_inc = 30;
    if (http_MakeMessage(&mid_msg, 1, 1,
                 "s" "ssc" "sdcc",
                 headers,
                 "SID: ", sub->sid,
                 "SEQ: ", sub->ToSendEventKey) != 0) {
        membuffer_destroy(&mid_msg);
        DLNA_LOGE("[VPPDLNA][%s][%d]-:http_MakeMessage failed to create the "
                    " Noify Request message for the subscription id-%s\n",
                    __FUNCTION__,__LINE__,sub->sid);
        return UPNP_E_OUTOF_MEMORY;
    }
    /* send a notify to each url until one goes thru */
    for (i = 0; i < sub->DeliveryURLs.size; i++) {
        url = &sub->DeliveryURLs.parsedURLs[i];
        return_code = notify_send_and_recv(
            url, &mid_msg, propertySet, &response);
        if (return_code == UPNP_E_SUCCESS)
            break;
    }

    membuffer_destroy(&mid_msg);
    if (return_code == UPNP_E_SUCCESS) {
        if (response.msg.status_code == HTTP_OK)
            return_code = GENA_SUCCESS;
        else {
            if (response.msg.status_code == HTTP_PRECONDITION_FAILED)
                /*Invalid SID gets removed */
                return_code = GENA_E_NOTIFY_UNACCEPTED_REMOVE_SUB;
            else
                return_code = GENA_E_NOTIFY_UNACCEPTED;
        }
        httpmsg_destroy(&response.msg);
    }

    endmsg = endmsg;
    DLNA_LOGV("[VPPDLNA][%s][%d]:gena Return Code :%d",__FUNCTION__,
                __LINE__, return_code);

    return return_code;
}


/*!
 * \brief Thread job to Notify a control point.
 *
 * It validates the subscription and copies the subscription. Also make sure
 * that events are sent in order.
 *
 * \note calls the genaNotify to do the actual work.
 */
static void genaNotifyThread(
    /*! [in] notify thread structure containing all the headers and property set info. */
    void *input)
{
    subscription *sub;
    service_info *service = NULL;
    subscription sub_copy;
    notify_thread_struct *in = (notify_thread_struct *) input;
    int return_code;
    struct Handle_Info *handle_info;

    /* This should be a HandleLock and not a HandleReadLock otherwise if there
     * is a lot of notifications, then multiple threads will acquire a read
     * lock and the thread which sends the notification will be blocked forever
     * on the HandleLock at the end of this function. */
    /*HandleReadLock(); */
    HandleLock();
    /* validate context */

    if (GetHandleInfo(in->device_handle, &handle_info) != HND_DEVICE) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                    " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,
                    in->device_handle);
        free_notify_struct(in);
        HandleUnlock();
        return;
    }

    if (!(service = FindServiceId(&handle_info->ServiceTable, in->servId, in->UDN)) ||
        !service->active ||
        !(sub = GetSubscriptionSID(in->sid, service)) ||
        copy_subscription(sub, &sub_copy) != HTTP_SUCCESS) {

        DLNA_LOGE("[VPPDLNA][%s][%d]-:No Notify Will be sent as either no "
            "service found with service id-%s or the service is not active"
            " or the service doesn't have any subscription"
            " with subscription ID-%s or the subscription timeout has "
            "happened\n",__FUNCTION__,__LINE__, in->servId, in->sid);
        free_notify_struct(in);
        HandleUnlock();
        return;
    }

/* TBD: reordering of the events is disabled. Will be taken up in iteration2 */
#if 0
//#if UPNP_ENABLE_NOTIFICATION_REORDERING
    /*If the event is out of order push it back to the job queue */
    if (in->eventKey != sub->ToSendEventKey) {
        TPJobInit(&job, (start_routine) genaNotifyThread, input);
        TPJobSetFreeFunction(&job, (free_function) free_notify_struct);
        TPJobSetPriority(&job, MED_PRIORITY);
        /* Sleep a little before creating another thread otherwise if there is
         * a lot of notifications to send, the device will take 100% of the CPU
         * to create threads and push them back to the job queue. */
        imillisleep(1);
        ThreadPoolAdd(&gSendThreadPool, &job, NULL);
        freeSubscription(&sub_copy);
        HandleUnlock();
        return;
    }
#endif

    HandleUnlock();

    /* send the notify */
    return_code = genaNotify(in->headers, in->propertySet, &sub_copy);
    freeSubscription(&sub_copy);
    HandleLock();
    if (GetHandleInfo(in->device_handle, &handle_info) != HND_DEVICE) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                    " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,
                    in->device_handle);
        free_notify_struct(in);
        HandleUnlock();
        return;
    }

    /* validate context */
    if (!(service = FindServiceId(&handle_info->ServiceTable, in->servId, in->UDN)) ||
        !service->active ||
        !(sub = GetSubscriptionSID(in->sid, service))) {

        DLNA_LOGE("[VPPDLNA][%s][%d]:Basic Validation Failed. Either no service"
            "Is there for the Service ID-%s or service is not active or no\n"
            "subscription is there with SID-%s",
            __FUNCTION__,__LINE__,in->servId, in->sid);

        free_notify_struct(in);
        HandleUnlock();
        return;
    }
    sub->ToSendEventKey++;
    if (sub->ToSendEventKey < 0)
        /* wrap to 1 for overflow */
        sub->ToSendEventKey = 1;
    if (return_code == GENA_E_NOTIFY_UNACCEPTED_REMOVE_SUB)
        RemoveSubscriptionSID(in->sid, service);
    free_notify_struct(in);

    HandleUnlock();
}


/*!
 * \brief Allocates the GENA header.
 *
 * \note The header must be destroyed after with a call to free(), otherwise
 * there will be a memory leak.
 *
 * \return The constructed header.
 */
static char *AllocGenaHeaders(
    /*! [in] The property set string. */
    const DOMString propertySet)
{
    static const char *HEADER_LINE_1 =
        "CONTENT-TYPE: text/xml; charset=\"utf-8\"\r\n";
    static const char *HEADER_LINE_2A =
        "CONTENT-LENGTH: ";
    static const char *HEADER_LINE_2B =
        "\r\n";
    static const char *HEADER_LINE_3 =
        "NT: upnp:event\r\n";
    static const char *HEADER_LINE_4 =
        "NTS: upnp:propchange\r\n";
    char *headers = NULL;
    size_t headers_size = 0;

    headers_size =
        strlen(HEADER_LINE_1 ) +
        strlen(HEADER_LINE_2A) + MAX_CONTENT_LENGTH +
        strlen(HEADER_LINE_2B) +
        strlen(HEADER_LINE_3 ) +
        strlen(HEADER_LINE_4 ) + 1;
    headers = (char *)UPNP_MALLOC(headers_size);
    if (headers == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory alloction failed\n", __FUNCTION__,
                        __LINE__);
        goto ExitFunction;
    }
    memset(headers,0,headers_size);
    snprintf(headers,headers_size, "%s%s%"PRIzu"%s%s%s",
        HEADER_LINE_1,
        HEADER_LINE_2A,
        strlen(propertySet),
        HEADER_LINE_2B,
        HEADER_LINE_3,
        HEADER_LINE_4);

ExitFunction:
    if (headers == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][%d]: Error UPNP_E_OUTOF_MEMORY\n",
            __FUNCTION__,__LINE__);
    }
    return headers;
}


int genaInitNotify(
    UpnpDevice_Handle device_handle,
    char *UDN,
    char *servId,
    char **VarNames,
    char **VarValues,
    int var_count,
    const Upnp_SID sid)
{
    int ret = GENA_SUCCESS;

    int *reference_count = NULL;
    char *UDN_copy = NULL;
    char *servId_copy = NULL;
    DOMString propertySet = NULL;
    char *headers = NULL;
    notify_thread_struct *thread_struct = NULL;

    subscription *sub = NULL;
    service_info *service = NULL;
    struct Handle_Info *handle_info;
    ThreadPoolJob job;

    DLNA_LOGV("[VPPDLNA][%s][%d]:GENA BEGIN INITIAL NOTIFY",__FUNCTION__,
                                                    __LINE__);

    reference_count = (int *)UPNP_MALLOC(sizeof (int));
    if (reference_count == NULL) {
        ret = UPNP_E_OUTOF_MEMORY;
        DLNA_LOGE("[VPPDLNA][%s][%d]:Mmeory Allocation Failed",__FUNCTION__,
                                                    __LINE__);
        goto ExitFunction;
    }
    *reference_count = 0;

    UDN_copy = (char *)UPNP_MALLOC(strlen(UDN) + 1);
    if (UDN_copy == NULL) {
        ret = UPNP_E_OUTOF_MEMORY;
        DLNA_LOGE("[VPPDLNA][%s][%d]:Mmeory Allocation Failed",__FUNCTION__,
                                                    __LINE__);
        goto ExitFunction;
    }

    servId_copy = (char *)UPNP_MALLOC(strlen(servId) + 1);
    if (servId_copy == NULL) {
        ret = UPNP_E_OUTOF_MEMORY;
        DLNA_LOGE("[VPPDLNA][%s][%d]:Mmeory Allocation Failed",__FUNCTION__,
                                                    __LINE__);
        goto ExitFunction;
    }

    HISTRCPY(UDN_copy, UDN);
    HISTRCPY(servId_copy, servId);

    HandleLock();

    if (GetHandleInfo(device_handle, &handle_info) != HND_DEVICE) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,device_handle);
        ret = GENA_E_BAD_HANDLE;
        goto ExitFunction;
    }

    service = FindServiceId(&handle_info->ServiceTable, servId, UDN);
    if (service == NULL) {
        ret = GENA_E_BAD_SERVICE;
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No Service Information Found for the "
                " service ID:%s and UDN:%s \n",__FUNCTION__,__LINE__,
                servId,UDN);
        goto ExitFunction;
    }

    sub = GetSubscriptionSID(sid, service);
    if (sub == NULL || sub->active) {
        ret = GENA_E_BAD_SID;
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No Subscription found for the SID:%s"
            "In the Service or subscription is not active\n",__FUNCTION__,
            __LINE__,sid);
        goto ExitFunction;
    }

    sub->active = 1;

    if (var_count <= 0) {
        ret = GENA_SUCCESS;
        goto ExitFunction;
    }

    ret = GeneratePropertySet(VarNames, VarValues, var_count, &propertySet);
    if (ret != XML_SUCCESS) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to generate the property set"
            "For Initial Notify\n",__FUNCTION__,__LINE__);
        goto ExitFunction;
    }

    headers = AllocGenaHeaders(propertySet);
    if (headers == NULL) {
        ret = UPNP_E_OUTOF_MEMORY;
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to Allocate the GENA Headers"
            "For Initial Notify\n",__FUNCTION__,__LINE__);
        goto ExitFunction;
    }

    /* schedule thread for initial notification */

    thread_struct = (notify_thread_struct *)UPNP_MALLOC(sizeof (notify_thread_struct));
    if (thread_struct == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Mmeory Allocation Failed",__FUNCTION__,
                                                    __LINE__);
        ret = UPNP_E_OUTOF_MEMORY;
    } else {
        *reference_count = 1;
        thread_struct->servId = servId_copy;
        thread_struct->UDN = UDN_copy;
        thread_struct->headers = headers;
        thread_struct->propertySet = propertySet;
        HISTRCPY(thread_struct->sid, sid);
        thread_struct->eventKey = sub->eventKey++;
        thread_struct->reference_count = reference_count;
        thread_struct->device_handle = device_handle;

        (void)TPJobInit(&job, (start_routine)genaNotifyThread, thread_struct);
        (void)TPJobSetFreeFunction(&job, (free_routine)free_notify_struct);
        (void)TPJobSetPriority(&job, MED_PRIORITY);

        ret = ThreadPoolAdd(&gSendThreadPool, &job, NULL);
        if (ret != 0) {
            DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to add the job to job pool",
                    __FUNCTION__, __LINE__);
            if (ret == EOUTOFMEM) {
                ret = UPNP_E_OUTOF_MEMORY;
            }
        } else {
            ret = GENA_SUCCESS;
        }
    }

ExitFunction:
    if (ret != GENA_SUCCESS || var_count <= 0) {
        UPNP_FREE(thread_struct);
        UPNP_FREE(headers);
        ixmlFreeDOMString(propertySet);
        UPNP_FREE(servId_copy);
        UPNP_FREE(UDN_copy);
        UPNP_FREE(reference_count);
    }

    HandleUnlock();

    DLNA_LOGV("[VPPDLNA][%s][%d]:GENA END INITIAL NOTIFY, ret = %d",
        __FUNCTION__,__LINE__,ret);

    return ret;
}


int genaInitNotifyExt(
    UpnpDevice_Handle device_handle,
    char *UDN,
    char *servId,
    void *PropSet,
    const Upnp_SID sid,
    int isBuffer)
{
    int ret = GENA_SUCCESS;

    int *reference_count = NULL;
    char *UDN_copy = NULL;
    char *servId_copy = NULL;
    DOMString propertySet = NULL;
    char *headers = NULL;
    notify_thread_struct *thread_struct = NULL;

    subscription *sub = NULL;
    service_info *service = NULL;
    struct Handle_Info *handle_info;
    ThreadPoolJob job;

    DLNA_LOGV("[VPPDLNA][%s][%d]:GENA BEGIN INITIAL NOTIFY EXT",__FUNCTION__,
                 __LINE__);

    reference_count = (int *)UPNP_MALLOC(sizeof (int));
    if (reference_count == NULL) {
        ret = UPNP_E_OUTOF_MEMORY;
        DLNA_LOGE("[VPPDLNA][%s][%d]:Mmeory Allocation Failed",__FUNCTION__,
                                                    __LINE__);
        goto ExitFunction;
    }
    *reference_count = 0;

    UDN_copy = (char *)UPNP_MALLOC(strlen(UDN) + 1);
    if (UDN_copy == NULL) {
        ret = UPNP_E_OUTOF_MEMORY;
        DLNA_LOGE("[VPPDLNA][%s][%d]:Mmeory Allocation Failed",__FUNCTION__,
                                                    __LINE__);
        goto ExitFunction;
    }

    servId_copy = (char *)UPNP_MALLOC(strlen(servId) + 1);
    if( servId_copy == NULL ) {
        ret = UPNP_E_OUTOF_MEMORY;
        DLNA_LOGE("[VPPDLNA][%s][%d]:Mmeory Allocation Failed",__FUNCTION__,
                                                    __LINE__);
        goto ExitFunction;
    }

    HISTRCPY(UDN_copy, UDN);
    HISTRCPY(servId_copy, servId);

    HandleLock();

    if (GetHandleInfo(device_handle, &handle_info) != HND_DEVICE) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,device_handle);
        ret = GENA_E_BAD_HANDLE;
        goto ExitFunction;
    }

    service = FindServiceId(&handle_info->ServiceTable, servId, UDN);
    if (service == NULL) {
        ret = GENA_E_BAD_SERVICE;
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No Service Information Found for the "
                " service ID:%s and UDN:%s \n",__FUNCTION__,__LINE__,
                servId,UDN);
        goto ExitFunction;
    }

    sub = GetSubscriptionSID(sid, service);
    if (sub == NULL || sub->active) {
        ret = GENA_E_BAD_SID;
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No Subscription found for the SID:%s"
            "In the Service or subscription is not active\n",__FUNCTION__,
            __LINE__,sid);
        goto ExitFunction;
    }

    sub->active = 1;

    if (PropSet == 0) {
        ret = GENA_SUCCESS;
        goto ExitFunction;
    }

    if (isBuffer)
    {
        propertySet = (DOMString)UPNP_STRDUP(PropSet);
        if (propertySet == NULL) {
            DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory allocation failure in  "
                "Strdup \n", __FUNCTION__,__LINE__);
            ret = UPNP_E_OUTOF_MEMORY;
            goto ExitFunction;
        }
    }else{
    propertySet = ixmlPrintNode((IXML_Node *)PropSet);
    if (propertySet == NULL) {
        ret = UPNP_E_INVALID_PARAM;
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to generate the property set"
            "For Initial Notify\n",__FUNCTION__,__LINE__);
        goto ExitFunction;
        }
    }

    headers = AllocGenaHeaders(propertySet);
    if (headers == NULL) {
        ret = UPNP_E_OUTOF_MEMORY;
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to Allocate the GENA Headers"
            "For Initial Notify\n",__FUNCTION__,__LINE__);
        goto ExitFunction;
    }

    /* schedule thread for initial notification */

    thread_struct = (notify_thread_struct *)UPNP_MALLOC(sizeof (notify_thread_struct));
    if (thread_struct == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][:%d]-:Memory Allocation Failure\r\n",
            __FUNCTION__,__LINE__);
        ret = UPNP_E_OUTOF_MEMORY;
    } else {
        *reference_count = 1;
        thread_struct->servId = servId_copy;
        thread_struct->UDN = UDN_copy;
        thread_struct->headers = headers;
        thread_struct->propertySet = propertySet;
        HISTRCPY(thread_struct->sid, sid);
        thread_struct->eventKey = sub->eventKey++;
        thread_struct->reference_count = reference_count;
        thread_struct->device_handle = device_handle;

        (void)TPJobInit(&job, (start_routine)genaNotifyThread, thread_struct);
        (void)TPJobSetFreeFunction(&job, (free_routine)free_notify_struct);
        (void)TPJobSetPriority(&job, MED_PRIORITY);

        ret = ThreadPoolAdd(&gSendThreadPool, &job, NULL);
        if (ret != 0) {
            DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to add the job to job pool",
                    __FUNCTION__, __LINE__);
            if (ret == EOUTOFMEM) {
                ret = UPNP_E_OUTOF_MEMORY;
            }
        } else {
            ret = GENA_SUCCESS;
        }
    }

ExitFunction:
    if (ret != GENA_SUCCESS || PropSet == 0) {
        UPNP_FREE(thread_struct);
        UPNP_FREE(headers);
        ixmlFreeDOMString(propertySet);
        UPNP_FREE(servId_copy);
        UPNP_FREE(UDN_copy);
        UPNP_FREE(reference_count);
    }

    HandleUnlock();

    DLNA_LOGV("[VPPDLNA][%s][%d]:GENA END INITIAL NOTIFY EXT, ret = %d",
        __FUNCTION__,__LINE__,ret);

    return ret;
}


int genaNotifyAllExt(
    UpnpDevice_Handle device_handle,
    char *UDN,
    char *servId,
    void *PropSet,
    int isBuff)
{
    int ret = GENA_SUCCESS;

    int *reference_count = NULL;
    char *UDN_copy = NULL;
    char *servId_copy = NULL;
    DOMString propertySet = NULL;
    char *headers = NULL;
    notify_thread_struct *thread_struct = NULL;

    subscription *finger = NULL;
    service_info *service = NULL;
    struct Handle_Info *handle_info;
    ThreadPoolJob job;

    DLNA_LOGV("[VPPDLNA][%s][%d]:GENA BEGIN NOTIFY ALL EXT",__FUNCTION__,
                __LINE__);

    reference_count = (int *)UPNP_MALLOC(sizeof (int));
    if (reference_count == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory alloction failed\n", __FUNCTION__,
                        __LINE__);
        ret = UPNP_E_OUTOF_MEMORY;
        goto ExitFunction;
    }

    *reference_count = 0;
    UDN_copy = (char *)UPNP_MALLOC(strlen(UDN) + 1);
    if (UDN_copy == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory alloction failed\n", __FUNCTION__,
                        __LINE__);
        ret = UPNP_E_OUTOF_MEMORY;
        goto ExitFunction;
    }

    servId_copy = (char *)UPNP_MALLOC(strlen(servId) + 1);
    if( servId_copy == NULL ) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory alloction failed\n", __FUNCTION__,
                        __LINE__);
        ret = UPNP_E_OUTOF_MEMORY;
        goto ExitFunction;
    }

    HISTRCPY(UDN_copy, UDN);
    HISTRCPY(servId_copy, servId);

    if (isBuff){
        propertySet = UPNP_STRDUP((char *)PropSet);
        if (propertySet == NULL) {
            DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory allocation failure in  "
                "Strdup \n", __FUNCTION__,__LINE__);
            ret = UPNP_E_OUTOF_MEMORY;
            goto ExitFunction;
        }
    }else{

        propertySet = ixmlPrintNode((IXML_Node *)PropSet);
        if (propertySet == NULL) {
            DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to Generate the xml "
                "document for the prpoperties \n", __FUNCTION__,__LINE__);
            ret = UPNP_E_INVALID_PARAM;
            goto ExitFunction;
        }
    }

    headers = AllocGenaHeaders(propertySet);
    if (headers == NULL) {
        ret = UPNP_E_OUTOF_MEMORY;
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to Allocate the GENA Headers"
            "For Notify\n",__FUNCTION__,__LINE__);
        goto ExitFunction;
    }

    HandleLock();
    if (GetHandleInfo(device_handle, &handle_info) != HND_DEVICE) {
        DLNA_LOGI("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,device_handle);
        ret = GENA_E_BAD_HANDLE;
    } else {
        service = FindServiceId(&handle_info->ServiceTable, servId, UDN);
        if (service != NULL) {
            finger = GetFirstSubscription(service);
            if(finger == NULL)
            {
                DLNA_LOGI("[VPPDLNA][%s][%d]-:No Subscription Found for the"
                    " Service with ID-%s\n",__FUNCTION__,__LINE__,
                                        servId);
                 ret = GENA_FAILURE;
                 goto ExitFunction;
            }
            while (finger) {
                thread_struct =
                    (notify_thread_struct *)UPNP_MALLOC(sizeof (notify_thread_struct));
                if (thread_struct == NULL) {
                    DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory alloction failed\n",
                        __FUNCTION__, __LINE__);
                    ret = UPNP_E_OUTOF_MEMORY;
                    break;
                }

                (*reference_count)++;
                thread_struct->reference_count = reference_count;
                thread_struct->UDN = UDN_copy;
                thread_struct->servId = servId_copy;
                thread_struct->headers = headers;
                thread_struct->propertySet = propertySet;
                HISTRCPY(thread_struct->sid, finger->sid);
                thread_struct->eventKey = finger->eventKey++;
                thread_struct->device_handle = device_handle;
                /* if overflow, wrap to 1 */
                if (finger->eventKey < 0) {
                    finger->eventKey = 1;
                }

                (void)TPJobInit(&job, (start_routine)genaNotifyThread, thread_struct);
                (void)TPJobSetFreeFunction(&job, (free_routine)free_notify_struct);
                (void)TPJobSetPriority(&job, MED_PRIORITY);
                ret = ThreadPoolAdd(&gSendThreadPool, &job, NULL);
                if (ret != 0) {
                    DLNA_LOGE("[VPPDLNA][%s][%d]-:Adding Job to the thread"
                        " pool failed with return value-%d\n",__FUNCTION__,
                        __LINE__, ret);
                    if (ret == EOUTOFMEM) {
                        ret = UPNP_E_OUTOF_MEMORY;
                    }

                    break;
                }

                finger = GetNextSubscription(service, finger);
            }
        } else {
            DLNA_LOGE("[VPPDLNA][%s][%d]-:No Service Found for the"
                    " Service ID-%s and UDN-%s\n",__FUNCTION__,__LINE__,
                                        servId, UDN);
            ret = GENA_E_BAD_SERVICE;
        }
    }

ExitFunction:
    if (ret != GENA_SUCCESS) { /*Lint Fix - v70917*/
       if (headers != NULL)
        UPNP_FREE(headers);
    if (propertySet != NULL)
            ixmlFreeDOMString(propertySet);
       if (servId_copy != NULL)
           UPNP_FREE(servId_copy);
       if (UDN_copy != NULL)
           UPNP_FREE(UDN_copy);
       if (reference_count != NULL)
           UPNP_FREE(reference_count);
    }

    HandleUnlock();

    DLNA_LOGV("[VPPDLNA][%s][%d]-:GENA END NOTIFY ALL EXT, ret = %d\n",
        __FUNCTION__,__LINE__,ret);

    return ret;
}


int genaNotifyAll(
    UpnpDevice_Handle device_handle,
    char *UDN,
    char *servId,
    char **VarNames,
    char **VarValues,
    int var_count)
{
    int ret = GENA_SUCCESS;

    int *reference_count = NULL;
    char *UDN_copy = NULL;
    char *servId_copy = NULL;
    DOMString propertySet = NULL;
    char *headers = NULL;
    notify_thread_struct *thread_struct = NULL;

    subscription *finger = NULL;
    service_info *service = NULL;
    struct Handle_Info *handle_info;
    ThreadPoolJob job;

    DLNA_LOGV("[VPPDLNA][%s][%d]:GENA BEGIN NOTIFY ALL",__FUNCTION__,__LINE__);

    reference_count = (int *)UPNP_MALLOC(sizeof (int));
    if (reference_count == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][:%d]-:Memory Allocation Failure\r\n",
            __FUNCTION__,__LINE__);
        ret = UPNP_E_OUTOF_MEMORY;
        goto ExitFunction;
    }
    *reference_count = 0;

    UDN_copy = (char *)UPNP_MALLOC(strlen(UDN) + 1);
    if (UDN_copy == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory alloction failed\n", __FUNCTION__,
                        __LINE__);
        ret = UPNP_E_OUTOF_MEMORY;
        goto ExitFunction;
    }

    servId_copy = (char *)UPNP_MALLOC(strlen(servId) + 1);
    if( servId_copy == NULL ) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory alloction failed\n", __FUNCTION__,
                        __LINE__);
        ret = UPNP_E_OUTOF_MEMORY;
        goto ExitFunction;
    }

    HISTRCPY(UDN_copy, UDN);
    HISTRCPY(servId_copy, servId);

    ret = GeneratePropertySet(VarNames, VarValues, var_count, &propertySet);
    if (ret != XML_SUCCESS) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to generate the property set"
            "For Notify\n",__FUNCTION__,__LINE__);
        goto ExitFunction;
    }

    headers = AllocGenaHeaders(propertySet);
    if (headers == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to Allocate the GENA Headers"
            "For Notify\n",__FUNCTION__,__LINE__);
        ret = UPNP_E_OUTOF_MEMORY;
        goto ExitFunction;
    }

    HandleLock();

    if (GetHandleInfo(device_handle, &handle_info) != HND_DEVICE) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,device_handle);
        ret = GENA_E_BAD_HANDLE;
    } else {
        service = FindServiceId(&handle_info->ServiceTable, servId, UDN);
        if (service != NULL) {
            finger = GetFirstSubscription(service);
            while (finger) {
                thread_struct = (notify_thread_struct *)UPNP_MALLOC(sizeof (notify_thread_struct));
                if (thread_struct == NULL) {

                    ret = UPNP_E_OUTOF_MEMORY;
                    break;
                }

                (*reference_count)++;
                thread_struct->reference_count = reference_count;
                thread_struct->UDN = UDN_copy;
                thread_struct->servId = servId_copy;
                thread_struct->headers = headers;
                thread_struct->propertySet = propertySet;
                HISTRCPY(thread_struct->sid, finger->sid);
                thread_struct->eventKey = finger->eventKey++;
                thread_struct->device_handle = device_handle;
                /* if overflow, wrap to 1 */
                if (finger->eventKey < 0) {
                    finger->eventKey = 1;
                }


                (void)TPJobInit(&job, (start_routine)genaNotifyThread, thread_struct);
                (void)TPJobSetFreeFunction(&job, (free_routine)free_notify_struct);
                (void)TPJobSetPriority(&job, MED_PRIORITY);
                ret = ThreadPoolAdd(&gSendThreadPool, &job, NULL);
                if (ret != 0){
                    DLNA_LOGE("[VPPDLNA][%s][%d]-:Adding Job to the thread"
                        " pool failed with return value-%d\n",__FUNCTION__,
                        __LINE__, ret);
                    if (ret == EOUTOFMEM) {

                        ret = UPNP_E_OUTOF_MEMORY;
                    }
                    break;
                }

                finger = GetNextSubscription(service, finger);
            }
        } else {
            DLNA_LOGE("[VPPDLNA][%s][%d]-:No Service Found for the"
                    " Service ID-%s and UDN-%s\n",__FUNCTION__,__LINE__,
                                        servId, UDN);
            ret = GENA_E_BAD_SERVICE;
        }
    }

ExitFunction:
    if (ret != GENA_SUCCESS) { /*Lint fix - v70917*/
     if (headers != NULL)
       {
         UPNP_FREE(headers);
      }
     if (propertySet != NULL)
       {
            ixmlFreeDOMString(propertySet);
     }
     if (servId_copy != NULL)
       {
            UPNP_FREE(servId_copy);
      }
     if (UDN_copy != NULL)
       {
            UPNP_FREE(UDN_copy);
     }
     if (reference_count != NULL)
       {
            UPNP_FREE(reference_count);
     }
    }

    HandleUnlock();

    DLNA_LOGV("[VPPDLNA][%s][%d]:GENA END NOTIFY ALL, ret = %d",
        __FUNCTION__,__LINE__,ret);

    return ret;
}


/*!
 * \brief Returns OK message in the case of a subscription request.
 *
 * \return UPNP_E_SUCCESS if successful, otherwise the appropriate error code.
 */
static int respond_ok(
    /*! [in] Socket connection of request. */
    SOCKINFO *info,
    /*! [in] Accepted duration. */
    int time_out,
    /*! [in] Accepted subscription. */
    subscription *sub,
    /*! [in] Http request. */
    http_message_t *request)
{
    int m_major = HTTP11_MAJOR_VERSION;
    int m_minor = HTTP11_MINOR_VERSION;
    membuffer response;
    int return_code;
    char timeout_str[100];
    int upnpTimeout = UPNP_TIMEOUT;

#if 0
    http_CalcResponseVersion( request->major_version,
                              request->minor_version, &m_major, &m_minor );
#endif

    memset(timeout_str,0,sizeof(timeout_str));
    if( time_out >= 0 ) {
        snprintf( timeout_str, (sizeof(timeout_str)/sizeof(char)),"TIMEOUT: Second-%d", time_out );
    } else {
        HISTRCPY( timeout_str, "TIMEOUT: Second-infinite" );
    }

    membuffer_init( &response );
    response.size_inc = 30;
    if(request->method == HTTPMETHOD_SUBSCRIBE
          && strstr(request->msg.buf,"ConnectionManager"))
    {//slove subscription CTT 7.2.33.2
     return_code = http_MakeMessage(
        &response, m_major, m_minor,
        "R" "D" "S" "N" "Xc" "ssc" "scCcc",
        HTTP_OK,

        /*  MODIFIED by c00190074
        (off_t)0, */
        0LL,
        X_USER_AGENT,
        "SID: ", sub->sid,
        timeout_str ) ;

    }
    else
    {//slove socket close in one seconde CTT 7.2.6.1,2
    return_code = http_MakeMessage(
        &response, m_major, m_minor,
        "R" "D" "S" "N" "Xc" "ssc" "scCc",
        HTTP_OK,

        /*  MODIFIED by c00190074
        (off_t)0, */
        0LL,
        X_USER_AGENT,
        "SID: ", sub->sid,
        timeout_str ) ;

    }
    if(return_code != 0 ){
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to create the HTTP Message"
                    " to respond to the received subscripion message\n",
                    __FUNCTION__,__LINE__);
        membuffer_destroy( &response );
        error_respond( info, HTTP_INTERNAL_SERVER_ERROR, request );
        return UPNP_E_OUTOF_MEMORY;
    }

    return_code = http_SendMessage( info, &upnpTimeout, "b",
                                    response.buf, response.length );

    membuffer_destroy( &response );

    return return_code;
}


/*!
 * \brief Function to parse the Callback header value in subscription requests.
 *
 * Takes in a buffer containing URLS delimited by '<' and '>'. The entire buffer
 * is copied into dynamic memory and stored in the URL_list. Pointers to the
 * individual urls within this buffer are allocated and stored in the URL_list.
 * Only URLs with network addresses are considered (i.e. host:port or domain name).
 *
 * \return The number of URLs parsed if successful, otherwise UPNP_E_OUTOF_MEMORY.
 */
static int create_url_list(
    /*! [in] . */
    memptr *url_list,
    /*! [out] . */
    URL_list *out)
{
    size_t URLcount = 0;
    size_t i;
    int return_code = 0;
    uri_type temp;
    token urls;
    token *URLS;

    urls.buff = url_list->buf;
    urls.size = url_list->length;
    URLS = &urls;

    out->size = 0;
    out->URLs = NULL;
    out->parsedURLs = NULL;

    for( i = 0; i < URLS->size; i++ ) {
        if( ( URLS->buff[i] == '<' ) && ( i + 1 < URLS->size ) ) {
            if( ( ( return_code = parse_uri_for_gena( &URLS->buff[i + 1],
                                             URLS->size - i + 1,
                                             &temp ) ) == HTTP_SUCCESS )
                && ( temp.hostport.text.size != 0 ) ) {
                URLcount++;
            } else {
                if( return_code == UPNP_E_OUTOF_MEMORY ) {
                    DLNA_LOGE("[VPPDLNA][%s][%d]-:parse_uri Failed due to "
                        " Memory allocation Failure\n",__FUNCTION__,__LINE__);
                    return return_code;
                }
            }
        }
    }

    if( URLcount > 0 ) {
        out->URLs = UPNP_MALLOC(URLS->size + 1);
        out->parsedURLs = UPNP_MALLOC(sizeof(uri_type) * URLcount);
        if (!out->URLs || !out->parsedURLs) {
            UPNP_FREE(out->URLs);
            UPNP_FREE(out->parsedURLs);
            out->URLs = NULL;
            out->parsedURLs = NULL;
            DLNA_LOGE("[VPPDLNA][%s][%d]-:Memory Allocation Failed "
                    "\n",__FUNCTION__,__LINE__);
            return UPNP_E_OUTOF_MEMORY;
        }

        memcpy( out->URLs, URLS->buff, URLS->size );
        out->URLs[URLS->size] = 0;
        URLcount = 0;

        for( i = 0; i < URLS->size; i++ ) {
            if( ( URLS->buff[i] == '<' ) && ( i + 1 < URLS->size ) ) {
                if( ( ( return_code =
                        parse_uri_for_gena( &out->URLs[i + 1], URLS->size - i + 1,
                                   &out->parsedURLs[URLcount] ) ) ==
                      HTTP_SUCCESS )
                    && ( out->parsedURLs[URLcount].hostport.text.size !=
                         0 ) ) {
                    URLcount++;
                } else {
                    if( return_code == UPNP_E_OUTOF_MEMORY ) {
                        UPNP_FREE( out->URLs );
                        UPNP_FREE( out->parsedURLs );
                        out->URLs = NULL;
                        out->parsedURLs = NULL;
                        DLNA_LOGE("[VPPDLNA][%s][%d]-:parse_uri Failed due to "
                                    " Memory allocation Failure\n",__FUNCTION__,
                                                __LINE__);
                        return return_code;
                    }
                }
            }
        }
    }

    out->size = URLcount;
    return (int)URLcount;
}


int gena_process_subscription_check_duplicate(
    service_info *service,
    subscription *sub,
    subscription **matchedSub
)
{

    subscription *NextSub;

    NextSub = service->subscriptionList;

    while(NULL != NextSub)
    {
        if (NULL == NextSub->DeliveryURLs.URLs)
        {
            NextSub = NextSub->next;
            continue;
        }

        if(0 == HISTRCMP(NextSub->DeliveryURLs.URLs, sub->DeliveryURLs.URLs))
        {
            *matchedSub = NextSub;
            return UPNP_TRUE;
        }

        NextSub = NextSub->next;
    }

    return UPNP_FALSE;
}



void gena_process_subscription_request(
    SOCKINFO *info,
    http_message_t *request)
{
    struct Upnp_Subscription_Request request_struct;
    Upnp_SID temp_sid;
    int return_code = 1;
    int time_out = 1801;
    service_info *service = NULL;
    subscription *sub;
    uuid_upnp uid;
    struct Handle_Info *handle_info;
    void *cookie;
    Upnp_FunPtr callback_fun;
    UpnpDevice_Handle device_handle;
    memptr nt_hdr;
    char *event_url_path = NULL;
    memptr callback_hdr;
    memptr timeout_hdr;
    subscription *matchedSub = NULL;

    DLNA_LOGI("[VPPDLNA][%s][%d]:Subscription Request Received:\n",__FUNCTION__,
                    __LINE__);

    if (httpmsg_find_hdr(request, HDR_NT, &nt_hdr) == NULL) {
        error_respond(info, HTTP_BAD_REQUEST, request);
        goto exit_function;
    }

    /* check NT header */
    /* Windows Millenium Interoperability: */
    /* we accept either upnp:event, or upnp:propchange for the NT header */
    if (memptr_cmp_nocase(&nt_hdr, "upnp:event") != 0) {
        error_respond(info, HTTP_PRECONDITION_FAILED, request);
        DLNA_LOGE("[VPPDLNA][%s][%d]-:NT header is not received with a value "
            " either upnp:event, or upnp:propchange\n",__FUNCTION__, __LINE__);
        goto exit_function;
    }

    /* if a SID is present then the we have a bad request "incompatible headers" */
    if (httpmsg_find_hdr(request, HDR_SID, NULL) != NULL) {
        error_respond(info, HTTP_BAD_REQUEST, request);
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Subscription ID header MUST not be "
            " present in the Subscription request\n",__FUNCTION__, __LINE__);
        goto exit_function;
    }
    /* look up service by eventURL */
    event_url_path = str_alloc(request->uri.pathquery.buff, request->uri.pathquery.size);
    if (event_url_path == NULL) {
        error_respond(info, HTTP_INTERNAL_SERVER_ERROR, request);
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed To Allocate Memory\n",__FUNCTION__,
                    __LINE__);
        goto exit_function;
    }

    DLNA_LOGV("[VPPDLNA][%s][%d]: Received Subscription Request for event URL "
            "path: %s\n",__FUNCTION__,__LINE__,event_url_path);

    HandleLock();

    /* CURRENTLY, ONLY ONE DEVICE */
    if (GetDeviceHandleInfoExt(info ,
        &device_handle, &handle_info) != HND_DEVICE) {
        UPNP_FREE(event_url_path);
        error_respond(info, HTTP_INTERNAL_SERVER_ERROR, request);
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To Get the Device Handle"
            " Information\n",__FUNCTION__,__LINE__);
        goto exit_function;
    }
    service = FindServiceEventURLPath(&handle_info->ServiceTable, event_url_path);
    if (service == NULL || !service->active) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Either No Service found for the event URL"
            ":%s or the service is not active\n",__FUNCTION__,__LINE__,
                                    event_url_path);
        UPNP_FREE(event_url_path);
        error_respond(info, HTTP_NOT_FOUND, request);
        HandleUnlock();
        goto exit_function;
    }

    UPNP_FREE(event_url_path);

    /* too many subscriptions */
    if (handle_info->MaxSubscriptions != -1 &&
        service->TotalSubscriptions >= handle_info->MaxSubscriptions) {
        error_respond(info, HTTP_INTERNAL_SERVER_ERROR, request);
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]: For the service the total number of "
            "subscription exceeds the maximum nuber of subscription allowed"
            "Number of subscriptions already:%d Max Subscriptions allowed:%d\n",
            __FUNCTION__,__LINE__,service->TotalSubscriptions,
            handle_info->MaxSubscriptions);
        goto exit_function;
    }

    /* generate new subscription */
    sub = (subscription *)UPNP_MALLOC(sizeof (subscription));
    if (sub == NULL) {
        error_respond(info, HTTP_INTERNAL_SERVER_ERROR, request);
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed To Allocate Memory\n",__FUNCTION__,
                    __LINE__);
        goto exit_function;
    }

    sub->eventKey = 0;
    sub->ToSendEventKey = 0;
    sub->active = 0;
    sub->next = NULL;
    sub->DeliveryURLs.size = 0;
    sub->DeliveryURLs.URLs = NULL;
    sub->DeliveryURLs.parsedURLs = NULL;

    /* check for valid callbacks */
    if (httpmsg_find_hdr( request, HDR_CALLBACK, &callback_hdr) == NULL) {
        error_respond(info, HTTP_PRECONDITION_FAILED, request);
        freeSubscriptionList(sub);
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Callback Header is not present in the \n"
            "Received Subscription Request",__FUNCTION__, __LINE__);
        goto exit_function;
    }
    return_code = create_url_list(&callback_hdr, &sub->DeliveryURLs);
    if (return_code == 0) {
        error_respond(info, HTTP_PRECONDITION_FAILED, request);
        freeSubscriptionList(sub);
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to create the delivery URL list \n"
            "From the callback header",__FUNCTION__, __LINE__);
        goto exit_function;
    }
    if (return_code == UPNP_E_OUTOF_MEMORY) {
        error_respond(info, HTTP_INTERNAL_SERVER_ERROR, request);
        freeSubscriptionList(sub);
        HandleUnlock();
        goto exit_function;
    }

    /* set the timeout */
    if (httpmsg_find_hdr(request, HDR_TIMEOUT, &timeout_hdr) != NULL) {
        if (matchstr(timeout_hdr.buf, timeout_hdr.length,
            "%iSecond-%d%0", &time_out) == PARSE_OK) {
            /* nothing */
        } else if(memptr_cmp_nocase(&timeout_hdr, "Second-infinite") == 0) {
            /* infinite timeout */
            time_out = -1;
        } else {
            /* default is > 1800 seconds */
            time_out = DEFAULT_TIMEOUT;
        }
    }

    /* replace infinite timeout with max timeout, if possible */
    if (handle_info->MaxSubscriptionTimeOut != -1) {
        if (time_out == -1 ||
            time_out > handle_info->MaxSubscriptionTimeOut) {
            time_out = handle_info->MaxSubscriptionTimeOut;
        }
    }

    /*
        As Per DLNA_GUIDE Line
        Requirement [7.2.22.1]: UPnP devices must send events to all properly
        subscribed UPnP control points. The device must enforce a subscription
        TIMEOUT value of 5 minutes.The UPnP device behavior of enforcing this 5
        minutes TIMEOUT value is    implemented by specifying "TIMEOUT:
        second-300" as an HTTP header/value pair As a Device we will enforce
        the subscription time out to be 300 Seconds
    */
        /* infinite time */
    if (time_out != 300){
        time_out = 300;
    }

    sub->expireTime = GetNowmTime() + time_out * 1000;

    /* Handling the Duplicate Subscription . If found remove the original
        Subsription*/

    if(gena_process_subscription_check_duplicate(service,sub, &matchedSub)){

        DLNA_LOGI("[VPPDLNA][%s][%d]:Found Duplicate Sub Request  url :%s "
            "SID :%s Subscription is Released !!!\n",__FUNCTION__, __LINE__,
            matchedSub->DeliveryURLs.URLs,matchedSub->sid);
        RemoveSubscriptionSID(matchedSub->sid,service);
    }

    /* generate SID */
    (void)uuid_create(&uid);

    memset(temp_sid,0,sizeof(temp_sid));
    uuid_unpack(&uid, temp_sid,(sizeof(temp_sid)-1));
    memset(sub->sid,0,sizeof(sub->sid));
    snprintf(sub->sid, sizeof(sub->sid),"uuid:%s", temp_sid);

    /* respond OK */
    if (respond_ok(info, time_out, sub, request) != UPNP_E_SUCCESS) {
        freeSubscriptionList(sub);
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Sending 200 OK response to peer for the "
            " Received subscription request failed \n",__FUNCTION__, __LINE__);
        goto exit_function;
    }
    /* add to subscription list */
    sub->next = service->subscriptionList;
    service->subscriptionList = sub;
    service->TotalSubscriptions++;

    /* finally generate callback for init table dump */
    request_struct.ServiceId = service->serviceId;
    request_struct.UDN = service->UDN;
    HISTRCPY((char *)request_struct.Sid, sub->sid);

    /* copy callback */
    callback_fun = handle_info->Callback;
    cookie = handle_info->Cookie;

    HandleUnlock();

    /* make call back with request struct */
    /* in the future should find a way of mainting that the handle */
    /* is not unregistered in the middle of a callback */
    (void)callback_fun(UPNP_EVENT_SUBSCRIPTION_REQUEST, &request_struct, cookie);

exit_function:
    return;
}


void gena_process_subscription_renewal_request(
    SOCKINFO *info,
    http_message_t *request)
{
    Upnp_SID sid;
    subscription *sub;
    int time_out = 1801;
    service_info *service = NULL;
    struct Handle_Info *handle_info;
    UpnpDevice_Handle device_handle;
    memptr temp_hdr;
    membuffer event_url_path;
    memptr timeout_hdr;

    /* if a CALLBACK or NT header is present, then it is an error */
    if( httpmsg_find_hdr( request, HDR_CALLBACK, NULL ) != NULL ||
        httpmsg_find_hdr( request, HDR_NT, NULL ) != NULL ) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed tp Find Callabck and NT Header "
            "in the subscription renewal request received\n",__FUNCTION__,
            __LINE__);
        error_respond( info, HTTP_BAD_REQUEST, request );
        return;
    }
    /* get SID */
    if( httpmsg_find_hdr( request, HDR_SID, &temp_hdr ) == NULL ||
        temp_hdr.length > SID_SIZE ) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed tp Find SID Header in the "
            "subscription renewal request received\n",__FUNCTION__,__LINE__);
        error_respond( info, HTTP_PRECONDITION_FAILED, request );
        return;
    }

    memcpy( sid, temp_hdr.buf, temp_hdr.length );
    sid[temp_hdr.length] = '\0';

    /* lookup service by eventURL */
    membuffer_init( &event_url_path );
    if( membuffer_append( &event_url_path, request->uri.pathquery.buff,
                          request->uri.pathquery.size ) != 0 ) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:membuffer_append failed\n",
                    __FUNCTION__,__LINE__);
        error_respond( info, HTTP_INTERNAL_SERVER_ERROR, request );
        return;
    }

    HandleLock();

    /* CURRENTLY, ONLY SUPPORT ONE DEVICE */
    if( GetDeviceHandleInfoExt( info,
        &device_handle, &handle_info ) != HND_DEVICE ) {
        error_respond( info, HTTP_PRECONDITION_FAILED, request );
        membuffer_destroy( &event_url_path );
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To Get the Device Handle"
            " Information\n",__FUNCTION__,__LINE__);
        return;
    }
    service = FindServiceEventURLPath( &handle_info->ServiceTable,
                                       event_url_path.buf );
    membuffer_destroy( &event_url_path );

    /* get subscription */
    if( service == NULL ||
        !service->active ||
        ( ( sub = GetSubscriptionSID( sid, service ) ) == NULL ) ) {
        error_respond( info, HTTP_PRECONDITION_FAILED, request );
        HandleUnlock();
        DLNA_LOGV("[VPPDLNA][%s][%d]:Basic Validation Failed. Either no service"
            " Is there or service is not active or no"
            " subscription is there with subscription id:%s\n",
            __FUNCTION__,__LINE__,sid);
        return;
    }

    /* too many subscriptions */
    if(handle_info->MaxSubscriptions != -1 &&
            service->TotalSubscriptions > handle_info->MaxSubscriptions) {
        error_respond( info, HTTP_INTERNAL_SERVER_ERROR, request );
        RemoveSubscriptionSID( sub->sid, service );
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]: For the service the total number of "
            "subscription exceeds the maximum nuber of subscription allowed "
            "Number of subscriptions already:%d Max Subscriptions allowed:%d\n",
            __FUNCTION__,__LINE__,service->TotalSubscriptions,
            handle_info->MaxSubscriptions);
        return;
    }

    /* set the timeout */
    if( httpmsg_find_hdr( request, HDR_TIMEOUT, &timeout_hdr ) != NULL ) {
        if( matchstr( timeout_hdr.buf, timeout_hdr.length,
                      "%iSecond-%d%0", &time_out ) == PARSE_OK ) {

            /*nothing */

        } else if( memptr_cmp_nocase( &timeout_hdr, "Second-infinite" ) ==
                   0 ) {

            time_out = -1;      /* inifinite timeout */

        } else {
            time_out = DEFAULT_TIMEOUT; /* default is > 1800 seconds */

        }
    }

    /* replace infinite timeout with max timeout, if possible */
    if( handle_info->MaxSubscriptionTimeOut != -1 ) {
        if( time_out == -1 ||
            time_out > handle_info->MaxSubscriptionTimeOut ) {
            time_out = handle_info->MaxSubscriptionTimeOut;
        }
    }

     /*
        As Per DLNA_GUIDE Line
        Requirement [7.2.22.1]: UPnP devices must send events to all properly
        subscribed UPnP control points. The device must enforce a subscription
        TIMEOUT value of 5 minutes.The UPnP device behavior of enforcing this 5
        minutes TIMEOUT value is    implemented by specifying "TIMEOUT:
        second-300" as an HTTP header/value pair As a Device we will enforce
        the subscription time out to be 300 Seconds
    */

    if (time_out != 300){
        time_out = 300;
    }

    sub->expireTime = GetNowmTime() + time_out * 1000;
    if( respond_ok( info, time_out, sub, request ) != UPNP_E_SUCCESS ) {
        RemoveSubscriptionSID( sub->sid, service );
    }

    HandleUnlock();
}


void gena_process_unsubscribe_request(
    SOCKINFO *info,
    http_message_t *request)
{
    Upnp_SID sid;
    service_info *service = NULL;
    struct Handle_Info *handle_info;
    UpnpDevice_Handle device_handle;

    memptr temp_hdr;
    membuffer event_url_path;

    /* if a CALLBACK or NT header is present, then it is an error */
    if( httpmsg_find_hdr( request, HDR_CALLBACK, NULL ) != NULL ||
        httpmsg_find_hdr( request, HDR_NT, NULL ) != NULL ) {
        error_respond( info, HTTP_BAD_REQUEST, request );
        return;
    }
    /* get SID */
    if( httpmsg_find_hdr( request, HDR_SID, &temp_hdr ) == NULL ||
        temp_hdr.length > SID_SIZE ) {
        error_respond( info, HTTP_PRECONDITION_FAILED, request );
        return;
    }
    memcpy( sid, temp_hdr.buf, temp_hdr.length );
    sid[temp_hdr.length] = '\0';

    /* lookup service by eventURL */
    membuffer_init( &event_url_path );
    if( membuffer_append( &event_url_path, request->uri.pathquery.buff,
                          request->uri.pathquery.size ) != 0 ) {
        error_respond( info, HTTP_INTERNAL_SERVER_ERROR, request );
        return;
    }

    HandleLock();

    /* CURRENTLY, ONLY SUPPORT ONE DEVICE */
    if( GetDeviceHandleInfoExt( info,
        &device_handle, &handle_info ) != HND_DEVICE ) {
        error_respond( info, HTTP_PRECONDITION_FAILED, request );
        membuffer_destroy( &event_url_path );
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To Get the Device Handle"
            " Information\n",__FUNCTION__,__LINE__);
        return;
    }

    service = FindServiceEventURLPath( &handle_info->ServiceTable,
                                       event_url_path.buf );
    /* validate service */
    if( service == NULL ||
        !service->active || GetSubscriptionSID( sid, service ) == NULL )
    {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Basic Validation Failed. Either no service"
            "Is there for the event url-%s or service is not active or no\n"
            "subscription is there with subscription id:%s",
            __FUNCTION__,__LINE__,event_url_path.buf, sid);
        membuffer_destroy( &event_url_path );
        error_respond( info, HTTP_PRECONDITION_FAILED, request );
        HandleUnlock();
        return;
    }

    membuffer_destroy( &event_url_path );

    RemoveSubscriptionSID(sid, service);
    error_respond(info, HTTP_OK, request);    /* success */

    HandleUnlock();
}


#endif /* INCLUDE_DEVICE_APIS */
#endif /* EXCLUDE_GENA */
