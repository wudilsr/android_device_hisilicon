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


#include "config.h"


/*!
 * \file
 */


#if EXCLUDE_GENA == 0
#ifdef INCLUDE_CLIENT_APIS


#include "gena.h"
#include "httpparser.h"
#include "httpreadwrite.h"
#include "parsetools.h"
#include "statcodes.h"
#include "sysdep.h"
#include "uuid.h"
#include "upnpapi.h"


extern ithread_mutex_t GlobalClientSubscribeMutex;


/*!
 * \brief This is a thread function to send the renewal just before the
 * subscription times out.
 */
static void GenaAutoRenewSubscription(
    /*! [in] Thread data(upnp_timeout *) needed to send the renewal. */
    IN void *input)
{
    upnp_timeout *event = (upnp_timeout *) input;
        struct Upnp_Event_Subscribe *sub_struct = (struct Upnp_Event_Subscribe *)event->Event;
    void *cookie;
    Upnp_FunPtr callback_fun;
    struct Handle_Info *handle_info;
    int send_callback = 0;
    int eventType = 0;
    int timeout = 0;
    int errCode = 0;
    UpnpString *tmpSID = UpnpString_new();

    /*lint -e506*/
    if (AUTO_RENEW_TIME == 0) {
        DLNA_LOGI("[VPPDLNA]:GENA SUB EXPIRED");
        sub_struct->ErrCode = UPNP_E_SUCCESS;
        send_callback = 1;
        eventType = UPNP_EVENT_SUBSCRIPTION_EXPIRED;
    } else {
        DLNA_LOGI("[VPPDLNA]:GENA AUTO RENEW");
        timeout = sub_struct->TimeOut;
        (void)UpnpString_set_String(tmpSID, sub_struct->Sid);
        errCode = genaRenewSubscription(
            event->handle,
            tmpSID,
            &timeout);
        sub_struct->ErrCode = errCode;
        sub_struct->TimeOut = timeout;
        if (errCode != UPNP_E_SUCCESS &&
            errCode != GENA_E_BAD_SID &&
            errCode != GENA_E_BAD_HANDLE) {
            send_callback = 1;
            eventType = UPNP_EVENT_AUTORENEWAL_FAILED;
        }
    }
    /*lint +e506*/

    if (send_callback) {
        HandleReadLock();
        if( GetHandleInfo( event->handle, &handle_info ) != HND_CLIENT ) {
            HandleUnlock();
            DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n", __FUNCTION__,__LINE__,
                event->handle);
            free_upnp_timeout(event);
            goto end_function;
        }
        DLNA_LOGI("[VPPDLNA]:HANDLE IS VALID");

        /* make callback */
        callback_fun = handle_info->Callback;
        cookie = handle_info->Cookie;
        HandleUnlock();
        (void)callback_fun((Upnp_EventType)eventType, event->Event, cookie);
    }

    free_upnp_timeout(event);

end_function:
    UpnpString_delete(tmpSID);
    return;
}


/*!
 * \brief Schedules a job to renew the subscription just before time out.
 *
 * \return GENA_E_SUCCESS if successful, otherwise returns the appropriate
 *  error code.
 */
static int ScheduleGenaAutoRenew(
    /*! [in] Handle that also contains the subscription list. */
    IN int client_handle,
    /*! [in] The time out value of the subscription. */
    IN int TimeOut,
    /*! [in] Subscription being renewed. */
    IN ClientSubscription *sub)
{
    struct Upnp_Event_Subscribe *RenewEventStruct = NULL;
    upnp_timeout *RenewEvent = NULL;
    int return_code = GENA_SUCCESS;
    ThreadPoolJob job;
    const UpnpString *tmpSID = UpnpClientSubscription_get_SID(sub);
    const UpnpString *tmpEventURL = UpnpClientSubscription_get_EventURL(sub);

    if (TimeOut == UPNP_INFINITE) {
        return_code = GENA_SUCCESS;
        goto end_function;
    }

    RenewEventStruct = (struct Upnp_Event_Subscribe *)UPNP_MALLOC(sizeof (struct Upnp_Event_Subscribe));
    if (RenewEventStruct == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][:%d]-:Memory Allocation Failure\r\n",
            __FUNCTION__,__LINE__);
        return_code = UPNP_E_OUTOF_MEMORY;
        goto end_function;
    }

    RenewEvent = (upnp_timeout *) UPNP_MALLOC(sizeof(upnp_timeout));
    if (RenewEvent == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][:%d]-:Memory Allocation Failure\r\n",
            __FUNCTION__,__LINE__);
        UPNP_FREE(RenewEventStruct);
        return_code = UPNP_E_OUTOF_MEMORY;
        goto end_function;
    }

    /* schedule expire event */
    RenewEventStruct->ErrCode = UPNP_E_SUCCESS;
    RenewEventStruct->TimeOut = TimeOut;
    memset(RenewEventStruct->Sid,0,sizeof(RenewEventStruct->Sid));
    strncpy(RenewEventStruct->Sid,UpnpString_get_String(tmpSID),((sizeof(RenewEventStruct->Sid)/sizeof(char))-1));
    memset(RenewEventStruct->PublisherUrl,0,(sizeof(RenewEventStruct->PublisherUrl)/sizeof(char)));
    strncpy(RenewEventStruct->PublisherUrl,
        UpnpString_get_String(tmpEventURL), NAME_SIZE - 1);

    /* RenewEvent->EventType=UPNP_EVENT_SUBSCRIPTION_EXPIRE; */
    RenewEvent->handle = client_handle;
    RenewEvent->Event = RenewEventStruct;

    (void)TPJobInit(&job, (start_routine) GenaAutoRenewSubscription, RenewEvent);
    (void)TPJobSetFreeFunction(&job, (free_routine)free_upnp_timeout);
    (void)TPJobSetPriority(&job, MED_PRIORITY);

    /* Schedule the job */
    return_code = TimerThreadSchedule(
        &gTimerThread,
        (TimeOut - AUTO_RENEW_TIME) * 1000,
        REL_SEC,
        &job, SHORT_TERM,
        &(RenewEvent->eventId));
    if (return_code != UPNP_E_SUCCESS) {
        UPNP_FREE(RenewEvent);
        UPNP_FREE(RenewEventStruct);
        goto end_function;
    }

    UpnpClientSubscription_set_RenewEventId(sub, RenewEvent->eventId);

    return_code = GENA_SUCCESS;

end_function:
    return return_code;
}


/*!
 * \brief Sends the UNSUBCRIBE gena request and recieves the response from the
 *  device and returns it as a parameter.
 *
 * \returns 0 if successful, otherwise returns the appropriate error code.
 */
static int gena_unsubscribe(
    /*! [in] Event URL of the service. */
    IN const UpnpString *url,
    /*! [in] The subcription ID. */
    IN const UpnpString *sid,
    /*! [out] The UNSUBCRIBE response from the device. */
    OUT http_parser_t *response )
{
    int return_code;
    uri_type dest_url;
    membuffer request;

    /* parse url */
    return_code = http_FixStrUrl(
        UpnpString_get_String(url),
        UpnpString_get_Length(url),
        &dest_url);
    if (return_code != 0) {
        return return_code;
    }

    /* make request msg */
    membuffer_init(&request);
    request.size_inc = 30;
    return_code = http_MakeMessage(
        &request, 1, 1,
        "q" "ssc" "C" "Uc",
        HTTPMETHOD_UNSUBSCRIBE, &dest_url,
        "SID: ", UpnpString_get_String(sid));

    /* Not able to make the message so destroy the existing buffer */
    if (return_code != 0) {
        membuffer_destroy(&request);

        return return_code;
    }

    /* send request and get reply */
    return_code = http_RequestAndResponse(
        &dest_url, request.buf, request.length,
        HTTPMETHOD_UNSUBSCRIBE, HTTP_DEFAULT_TIMEOUT, response);
    membuffer_destroy(&request);
    if (return_code != 0) {
        httpmsg_destroy(&response->msg);
    }

    if (return_code == 0 && response->msg.status_code != HTTP_OK) {
        return_code = UPNP_E_UNSUBSCRIBE_UNACCEPTED;
        httpmsg_destroy(&response->msg);
    }

    return return_code;
}


/*!
 * \brief Subscribes or renew subscription.
 *
 * \return 0 if successful, otherwise returns the appropriate error code.
 */
static int gena_subscribe(
    /*! [in] URL of service to subscribe. */
    IN const UpnpString *url,
    /*! [in,out] Subscription time desired (in secs). */
    INOUT int *timeout,
    /*! [in] for renewal, this contains a currently held subscription SID.
     * For first time subscription, this must be NULL. */
    IN const UpnpString *renewal_sid,
    /*! [out] SID returned by the subscription or renew msg. */
    OUT UpnpString *sid,
    struct Handle_Info *handle_info)
{
    int return_code;
    int parse_ret = 0;
    int local_timeout = CP_MINIMUM_SUBSCRIPTION_TIME;
    memptr sid_hdr;
    memptr timeout_hdr;
    char timeout_str[25] = {0};
    membuffer request;
    uri_type dest_url;
    http_parser_t response;

    UpnpString_clear(sid);

    /* request timeout to string */
    if (timeout == NULL) {
        timeout = &local_timeout;
    }
    memset(timeout_str,0,sizeof(timeout_str));
    if (*timeout < 0) {
        HISTRCPY(timeout_str, "infinite");
    } else if(*timeout < CP_MINIMUM_SUBSCRIPTION_TIME) {
        snprintf(timeout_str,sizeof(timeout_str) ,"%d", CP_MINIMUM_SUBSCRIPTION_TIME);
    } else {
        snprintf(timeout_str, sizeof(timeout_str),"%d", *timeout);
    }

    /* parse url */
    return_code = http_FixStrUrl(
        UpnpString_get_String(url),
        UpnpString_get_Length(url),
        &dest_url);
    if (return_code != 0) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Parsing of URL in http_FixStrUrl Failed "
            "error code: %d\n",__FUNCTION__,__LINE__,return_code );
        return return_code;
    }

    /* make request msg */
    membuffer_init(&request);
    request.size_inc = 30;
    if (renewal_sid) {
        /* renew subscription */
        return_code = http_MakeMessage(
            &request, 1, 1,
            "q" "ssc" "sscCcc" ,
            HTTPMETHOD_SUBSCRIBE, &dest_url,
            "SID: ", UpnpString_get_String(renewal_sid),
            "TIMEOUT: Second-", timeout_str );
    } else {
        /* subscribe */
        if (dest_url.hostport.IPaddress.ss_family == AF_INET6) {
            struct sockaddr_in6* DestAddr6 = (struct sockaddr_in6*)&dest_url.hostport.IPaddress;
            return_code = http_MakeMessage(
                &request, 1, 1,
                "q" "sssdsc" "sc" "sscCcc",
                HTTPMETHOD_SUBSCRIBE, &dest_url,
                "CALLBACK: <http://[",
                (IN6_IS_ADDR_LINKLOCAL(&DestAddr6->sin6_addr) || strlen(gIF_IPV6_ULA_GUA) == 0) ?
                    gIF_IPV6 : gIF_IPV6_ULA_GUA,
                "]:", handle_info->listenPortNoIp6, "/>",
                "NT: upnp:event",
                "TIMEOUT: Second-", timeout_str);
        } else {
            return_code = http_MakeMessage(
                &request, 1, 1,
                "q" "sssdsc" "sc" "sscCcc",
                HTTPMETHOD_SUBSCRIBE, &dest_url,
                "CALLBACK: <http://", gIF_IPV4, ":", handle_info->listenPortNoIp4, "/>",
                "NT: upnp:event",
                "TIMEOUT: Second-", timeout_str);
        }
    }
    if (return_code != 0) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:HTTP message Creation for subscription "
            "request failed with error code: %d\n",__FUNCTION__,__LINE__
            ,return_code);
        return return_code;
    }

    /*send request and get reply */
    return_code = http_RequestAndResponse(&dest_url, request.buf,
        request.length,
        HTTPMETHOD_SUBSCRIBE,
        HTTP_DEFAULT_TIMEOUT,
        &response);
    membuffer_destroy(&request);

    if (return_code != 0) {
        httpmsg_destroy(&response.msg);
        DLNA_LOGE("[VPPDLNA][%s][%d]:http_RequestAndResponse failed with "
            "error code: %d\n",__FUNCTION__,__LINE__ ,return_code);
        return return_code;
    }
    if (response.msg.status_code != HTTP_OK) {
        httpmsg_destroy(&response.msg);
        DLNA_LOGE("[VPPDLNA][%s][%d]:Received an Error response from Peer for"
            "the subscription request status code: %d\n",__FUNCTION__,__LINE__
            ,response.msg.status_code);
        return UPNP_E_SUBSCRIBE_UNACCEPTED;
    }

    /* get SID and TIMEOUT */
    if (httpmsg_find_hdr(&response.msg, HDR_SID, &sid_hdr) == NULL ||
        sid_hdr.length == 0 ||
        httpmsg_find_hdr( &response.msg, HDR_TIMEOUT, &timeout_hdr ) == NULL ||
        timeout_hdr.length == 0 ) {
        httpmsg_destroy( &response.msg );
        DLNA_LOGE("[VPPDLNA][%s][%d]:Received Invalid response from Peer for"
            "the subscription request Mandatory header fields SID and Timeout"
            "Are missing \n",__FUNCTION__,__LINE__);
        return UPNP_E_BAD_RESPONSE;
    }

    /* save timeout */
    parse_ret = matchstr(timeout_hdr.buf, timeout_hdr.length, "%iSecond-%d%0", timeout);
    if (parse_ret == PARSE_OK) {
        /* nothing to do */
    } else if (memptr_cmp_nocase(&timeout_hdr, "Second-infinite") == 0) {
        *timeout = -1;
    } else {
        httpmsg_destroy( &response.msg );

        return UPNP_E_BAD_RESPONSE;
    }

    /* save SID */
    (void)UpnpString_set_StringN(sid, sid_hdr.buf, sid_hdr.length);
    if (UpnpString_get_String(sid) == NULL) {
        httpmsg_destroy(&response.msg);
        DLNA_LOGE("[VPPDLNA][%s][%d]:Memory Allocation Failed \n",__FUNCTION__,
            __LINE__);
        return UPNP_E_OUTOF_MEMORY;
    }
    httpmsg_destroy(&response.msg);

    return UPNP_E_SUCCESS;
}


int genaUnregisterClient(UpnpClient_Handle client_handle)
{
    ClientSubscription *sub_copy = UpnpClientSubscription_new();
    int return_code = UPNP_E_SUCCESS;
    struct Handle_Info *handle_info = NULL;
    http_parser_t response;

    while (TRUE) {
        HandleLock();

        if (GetHandleInfo(client_handle, &handle_info) != HND_CLIENT) {
            HandleUnlock();
            DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n", __FUNCTION__,__LINE__,
                client_handle);
            return_code = GENA_E_BAD_HANDLE;
            goto exit_function;
        }
        if (handle_info->ClientSubList == NULL) {
            return_code = UPNP_E_SUCCESS;
            break;
        }
        UpnpClientSubscription_assign(sub_copy, handle_info->ClientSubList);
        RemoveClientSubClientSID(
            &handle_info->ClientSubList,
            UpnpClientSubscription_get_SID(sub_copy));

        HandleUnlock();

        return_code = gena_unsubscribe(
            UpnpClientSubscription_get_EventURL(sub_copy),
            UpnpClientSubscription_get_ActualSID(sub_copy),
            &response);
        if (return_code == 0) {
            httpmsg_destroy(&response.msg);
        }
        free_client_subscription(sub_copy);
    }

    freeClientSubList(handle_info->ClientSubList);
    HandleUnlock();

exit_function:
    UpnpClientSubscription_delete(sub_copy);
    return return_code;
}


#ifdef INCLUDE_CLIENT_APIS
int genaUnSubscribe(
    UpnpClient_Handle client_handle,
    const UpnpString *in_sid)
{
    ClientSubscription *sub = NULL;
    int return_code = GENA_SUCCESS;
    struct Handle_Info *handle_info;
    ClientSubscription *sub_copy = UpnpClientSubscription_new();
    http_parser_t response;

    /* validate handle and sid */
    HandleLock();
    if (GetHandleInfo(client_handle, &handle_info) != HND_CLIENT) {
        HandleUnlock();
        DLNA_LOGV("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n", __FUNCTION__,__LINE__,
                client_handle);
        return_code = GENA_E_BAD_HANDLE;
        goto exit_function;
    }
    sub = GetClientSubClientSID(handle_info->ClientSubList, in_sid);
    if (sub == NULL) {
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to get the subscription object"
                " \n", __FUNCTION__,__LINE__);
        return_code = GENA_E_BAD_SID;
        goto exit_function;
    }
    UpnpClientSubscription_assign(sub_copy, sub);
    HandleUnlock();

    return_code = gena_unsubscribe(
        UpnpClientSubscription_get_EventURL(sub_copy),
        UpnpClientSubscription_get_ActualSID(sub_copy),
        &response);
    if (return_code == 0) {
        httpmsg_destroy(&response.msg);
    }
    free_client_subscription(sub_copy);

    HandleLock();
    if (GetHandleInfo(client_handle, &handle_info) != HND_CLIENT) {
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n", __FUNCTION__,__LINE__,
                client_handle);
        return_code = GENA_E_BAD_HANDLE;
        goto exit_function;
    }
    RemoveClientSubClientSID(&handle_info->ClientSubList, in_sid);
    HandleUnlock();

exit_function:
    UpnpClientSubscription_delete(sub_copy);
    return return_code;
}
#endif /* INCLUDE_CLIENT_APIS */


#ifdef INCLUDE_CLIENT_APIS
int genaSubscribe(
    UpnpClient_Handle client_handle,
    const UpnpString *PublisherURL,
    int *TimeOut,
    UpnpString *out_sid)
{
    int return_code = GENA_SUCCESS;
    ClientSubscription *newSubscription = UpnpClientSubscription_new();
    uuid_upnp uid;
    Upnp_SID temp_sid;
    Upnp_SID temp_sid2;
    UpnpString *ActualSID = UpnpString_new();
    UpnpString *EventURL = UpnpString_new();
    struct Handle_Info *handle_info;

    DLNA_LOGI("[VPPDLNA]:GENA SUBSCRIBE BEGIN");

    UpnpString_clear(out_sid);

    HandleReadLock();
    /* validate handle */
    if (GetHandleInfo(client_handle, &handle_info) != HND_CLIENT) {
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,client_handle);

        UpnpString_delete(ActualSID);
        UpnpString_delete(EventURL);
        UpnpClientSubscription_delete(newSubscription);
        return GENA_E_BAD_HANDLE;
    }
    HandleUnlock();

    /* subscribe */
    SubscribeLock();
    return_code = gena_subscribe(PublisherURL, TimeOut, NULL, ActualSID,
        handle_info);
    HandleLock();
    if (return_code != UPNP_E_SUCCESS) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:SUBSCRIBE FAILED error code:%d returned\n",
            __FUNCTION__,__LINE__,return_code );
        goto error_handler;
    }

    if(GetHandleInfo(client_handle, &handle_info) != HND_CLIENT) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,client_handle);
        return_code = GENA_E_BAD_HANDLE;
        goto error_handler;
    }

    /* generate client SID */
    (void)uuid_create(&uid );
    memset(temp_sid,0,sizeof(temp_sid));
    uuid_unpack(&uid, temp_sid,(sizeof(temp_sid)-1));
    memset(temp_sid2,0,sizeof(temp_sid2));
    snprintf(temp_sid2, sizeof(temp_sid2),"uuid:%s", temp_sid);
    (void)UpnpString_set_String(out_sid, temp_sid2);

    /* create event url */
    UpnpString_assign(EventURL, PublisherURL);

    /* fill subscription */
    if (newSubscription == NULL) {
        return_code = UPNP_E_OUTOF_MEMORY;
        goto error_handler;
    }
    UpnpClientSubscription_set_RenewEventId(newSubscription, -1);
    UpnpClientSubscription_set_SID(newSubscription, out_sid);
    UpnpClientSubscription_set_ActualSID(newSubscription, ActualSID);
    UpnpClientSubscription_set_EventURL(newSubscription, EventURL);
    UpnpClientSubscription_set_Next(newSubscription, handle_info->ClientSubList);
    handle_info->ClientSubList = newSubscription;

    /* schedule expiration event */
    return_code = ScheduleGenaAutoRenew(client_handle, *TimeOut, newSubscription);

error_handler:
    if (return_code != UPNP_E_SUCCESS) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:SUBSCRIBE FAILED error code:%d returned\n",
            __FUNCTION__,__LINE__,return_code );
        UpnpString_delete(ActualSID);
        UpnpString_delete(EventURL);
        UpnpClientSubscription_delete(newSubscription);
    }else{
    /*[r72104] Need to free the memory in success case also */
        UpnpString_delete(ActualSID);
        UpnpString_delete(EventURL);
    }
    HandleUnlock();
    SubscribeUnlock();

    return return_code;
}
#endif /* INCLUDE_CLIENT_APIS */


int genaRenewSubscription(
    UpnpClient_Handle client_handle,
    const UpnpString *in_sid,
    int *TimeOut)
{
    int return_code = GENA_SUCCESS;
    ClientSubscription *sub = NULL;
    ClientSubscription *sub_copy = UpnpClientSubscription_new();
    struct Handle_Info *handle_info;
    UpnpString *ActualSID = UpnpString_new();
    ThreadPoolJob tempJob;

    HandleLock();

    /* validate handle and sid */
    if (GetHandleInfo(client_handle, &handle_info) != HND_CLIENT) {
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,client_handle);
        return_code = GENA_E_BAD_HANDLE;
        goto exit_function;
    }

    sub = GetClientSubClientSID(handle_info->ClientSubList, in_sid);
    if (sub == NULL) {
        HandleUnlock();
         DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to get the subscription object"
                " \n", __FUNCTION__,__LINE__);
        return_code = GENA_E_BAD_SID;
        goto exit_function;
    }

    /* remove old events */
    if (TimerThreadRemove(
        &gTimerThread,
        UpnpClientSubscription_get_RenewEventId(sub),
        &tempJob) == 0 ) {
        free_upnp_timeout((upnp_timeout *)tempJob.arg);
    }

    DLNA_LOGI("[VPPDLNA][%s][%d]:REMOVED AUTO RENEW  EVENT",__FUNCTION__,
        __LINE__);

    UpnpClientSubscription_set_RenewEventId(sub, -1);
    UpnpClientSubscription_assign(sub_copy, sub);

    HandleUnlock();

    return_code = gena_subscribe(
        UpnpClientSubscription_get_EventURL(sub_copy),
        TimeOut,
        UpnpClientSubscription_get_ActualSID(sub_copy),
        ActualSID, handle_info);

    HandleLock();

    if (GetHandleInfo(client_handle, &handle_info) != HND_CLIENT) {
        HandleUnlock();
        DLNA_LOGE("[VPPDLNA][%s][%d]-:No device Found for the"
                " UpnpDevice_Handle-%d \n",__FUNCTION__,__LINE__,client_handle);
        return_code = GENA_E_BAD_HANDLE;
        goto exit_function;
    }

    /* we just called GetHandleInfo, so we don't check for return value */
    /*GetHandleInfo(client_handle, &handle_info); */
    if (return_code != UPNP_E_SUCCESS) {
        /* network failure (remove client sub) */
        RemoveClientSubClientSID(&handle_info->ClientSubList, in_sid);
        free_client_subscription(sub_copy);
        HandleUnlock();
         DLNA_LOGE("[VPPDLNA][%s][%d]-:gena_subscribe failed with return code-"
                "%d \n", __FUNCTION__,__LINE__,return_code);
        goto exit_function;
    }

    /* get subscription */
    sub = GetClientSubClientSID(handle_info->ClientSubList, in_sid);
    if (sub == NULL) {
        free_client_subscription(sub_copy);
        HandleUnlock();
         DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to get the subscription object"
                " \n", __FUNCTION__,__LINE__);
        return_code = GENA_E_BAD_SID;
        goto exit_function;
    }

    /* store actual sid */
    UpnpClientSubscription_set_ActualSID(sub, ActualSID);

    /* start renew subscription timer */
    return_code = ScheduleGenaAutoRenew(client_handle, *TimeOut, sub);
    if (return_code != GENA_SUCCESS) {
        RemoveClientSubClientSID(
            &handle_info->ClientSubList,
            UpnpClientSubscription_get_SID(sub));
         DLNA_LOGE("[VPPDLNA][%s][%d]-:Starting of New subscription timer "
                " Failed with an error code-%d \n", __FUNCTION__,__LINE__,
                                                                return_code);
    }
    free_client_subscription(sub_copy);
    HandleUnlock();

exit_function:
    UpnpString_delete(ActualSID);
    UpnpClientSubscription_delete(sub_copy);
    return return_code;
}


void gena_process_notification_event(
    SOCKINFO *info,
    http_message_t *event)
{
    struct Upnp_Event event_struct;
    IXML_Document *ChangedVars = NULL;
    int eventKey;
    token sid;
    ClientSubscription *clnt_subscription = NULL;
    struct Handle_Info *handle_info;
    void *cookie;
    Upnp_FunPtr callback;
    UpnpClient_Handle client_handle;
    const UpnpString *tmpSID = NULL;

    memptr sid_hdr;
    memptr nt_hdr,
    nts_hdr;
    memptr seq_hdr;

    /* get SID */
    if (httpmsg_find_hdr(event, HDR_SID, &sid_hdr) == NULL) {
        error_respond(info, HTTP_PRECONDITION_FAILED, event);
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed To get the Mandatory Header "
                " SID in the received notify message\n",__FUNCTION__,__LINE__);
        goto exit_function;
    }

    sid.buff = sid_hdr.buf;
    sid.size = sid_hdr.length;

    /* get event key */
    if (httpmsg_find_hdr(event, HDR_SEQ, &seq_hdr) == NULL ||
        matchstr(seq_hdr.buf, seq_hdr.length, "%d%0", &eventKey) != PARSE_OK) {
        error_respond( info, HTTP_BAD_REQUEST, event );
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed To get the Mandatory Header "
                " SEQ in the received notify message\n",__FUNCTION__,__LINE__);
        goto exit_function;
    }

    /* get NT and NTS headers */
    if (httpmsg_find_hdr(event, HDR_NT, &nt_hdr) == NULL ||
        httpmsg_find_hdr(event, HDR_NTS, &nts_hdr) == NULL) {
        error_respond( info, HTTP_BAD_REQUEST, event );
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed To get the Mandatory Header "
                " NT or NTS in the received notify message\n",__FUNCTION__,
                __LINE__);
        goto exit_function;
    }

    /* verify NT and NTS headers */
    if (memptr_cmp(&nt_hdr, "upnp:event") != 0 ||
        memptr_cmp(&nts_hdr, "upnp:propchange") != 0) {
        error_respond(info, HTTP_PRECONDITION_FAILED, event);
        DLNA_LOGE("[VPPDLNA][%s][%d]-:Verification of values of NT and NTS "
            "header failed. excpected values upnp:event and upnp:propchange "
            "respectively" ,__FUNCTION__, __LINE__);
        goto exit_function;
    }

    /* parse the content (should be XML) */
    if (!has_xml_content_type(event) ||
        event->msg.length == 0 ||
        ixmlParseBufferEx(event->entity.buf, &ChangedVars) != IXML_SUCCESS) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-:The content is either not XML or the "
            "parsing of the message failed\n",__FUNCTION__,__LINE__);
        error_respond(info, HTTP_BAD_REQUEST, event);
        goto exit_function;
    }

    HandleLock();

    /* get client info */
    if (GetClientHandleInfoExt(info->listenSocket,&client_handle, &handle_info)
        != HND_CLIENT) {
        DLNA_LOGE("[VPPDLNA][%s][%d]-: Failed To get The Client "
                "Handle Info\r\n",__FUNCTION__,__LINE__);
        error_respond(info, HTTP_PRECONDITION_FAILED, event);
        HandleUnlock();
        goto exit_function;
    }

    /* get subscription based on SID */
    clnt_subscription = GetClientSubActualSID(handle_info->ClientSubList, &sid);
    if (clnt_subscription == NULL) {
        if (eventKey == 0) {
            /* wait until we've finished processing a subscription  */
            /*   (if we are in the middle) */
            /* this is to avoid mistakenly rejecting the first event if we  */
            /*   receive it before the subscription response */
            HandleUnlock();

            /* try and get Subscription Lock  */
            /*   (in case we are in the process of subscribing) */
            SubscribeLock();

            /* get HandleLock again */
            HandleLock();

            if (GetClientHandleInfoExt(info->listenSocket, &client_handle,
                    &handle_info) != HND_CLIENT) {
                DLNA_LOGE("[VPPDLNA][%s][%d]-: Failed To get The Client "
                    "Handle Info\r\n",__FUNCTION__,__LINE__);
                error_respond(info, HTTP_PRECONDITION_FAILED, event);
                SubscribeUnlock();
                HandleUnlock();
                goto exit_function;
            }

            clnt_subscription = GetClientSubActualSID(handle_info->ClientSubList, &sid);
            if (clnt_subscription == NULL) {
                error_respond( info, HTTP_PRECONDITION_FAILED, event );
                SubscribeUnlock();
                HandleUnlock();
                DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to get the subscription "
                    "object \n", __FUNCTION__,__LINE__);
                goto exit_function;
            }

            SubscribeUnlock();
        } else {
            error_respond( info, HTTP_PRECONDITION_FAILED, event );
            DLNA_LOGE("[VPPDLNA][%s][%d]-:Failed to get the subscription "
                    "object and the received a %d th Notify Event\n",
                    __FUNCTION__,__LINE__, eventKey);
            HandleUnlock();
            goto exit_function;
        }
    }

    /* success */
    error_respond(info, HTTP_OK, event);

    /* fill event struct */
    tmpSID = UpnpClientSubscription_get_SID(clnt_subscription);

    memset(event_struct.Sid,0,sizeof(event_struct.Sid));
    strncpy(event_struct.Sid,UpnpString_get_String(tmpSID),(sizeof(event_struct.Sid)-1));
    event_struct.EventKey = eventKey;
    event_struct.ChangedVariables = ChangedVars;

    /* copy callback */
    callback = handle_info->Callback;
    cookie = handle_info->Cookie;

    HandleUnlock();

    /* make callback with event struct */
    /* In future, should find a way of mainting */
    /* that the handle is not unregistered in the middle of a */
    /* callback */
    (void)callback(UPNP_EVENT_RECEIVED, &event_struct, cookie);

exit_function:
    ixmlDocument_free(ChangedVars);
}


#endif /* INCLUDE_CLIENT_APIS */
#endif /* EXCLUDE_GENA */
