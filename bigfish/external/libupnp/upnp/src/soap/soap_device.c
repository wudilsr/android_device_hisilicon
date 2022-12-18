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

#ifdef INCLUDE_DEVICE_APIS
#if EXCLUDE_SOAP == 0

#include "httpparser.h"
#include "httpreadwrite.h"
#include "parsetools.h"
#include "soaplib.h"
#include "ssdplib.h"
#include "statcodes.h"
#include "unixutil.h"
#include "upnpapi.h"

#ifdef WIN32
    #define snprintf _snprintf
#endif

/*! timeout duration in secs for transmission/reception */
#define SOAP_TIMEOUT UPNP_TIMEOUT

#define SREQ_HDR_NOT_FOUND     -1
#define SREQ_BAD_HDR_FORMAT     -2

#define SOAP_INVALID_ACTION 401
#define SOAP_INVALID_ARGS    402
#define SOAP_OUT_OF_SYNC    403
#define SOAP_INVALID_VAR    404
#define SOAP_ACTION_FAILED    501

static const char *SOAP_BODY = "Body";
static const char *SOAP_URN = "http:/""/schemas.xmlsoap.org/soap/envelope/";
static const char *QUERY_STATE_VAR_URN = "urn:schemas-upnp-org:control-1-0";

static const char *Soap_Invalid_Action = "Invalid Action";
/*static const char* Soap_Invalid_Args = "Invalid Args"; */
static const char *Soap_Action_Failed = "Action Failed";
static const char *Soap_Invalid_Var = "Invalid Var";
static const char *Soap_Invalid_Service = "Invalid Service";

char *ContentTypeHeader =
    "CONTENT-TYPE: text/xml; charset=\"utf-8\"\r\n";

/*!
 * \brief This function retrives the name of the SOAP action.
 *
 * \return 0 if successful else returns appropriate error.
 */
static UPNP_INLINE int get_request_type(
    /*! [in] HTTP request. */
    http_message_t *request,
    /*! [out] SOAP action name. */
    memptr *action_name)
{
    memptr value;
    memptr ns_value, dummy_quote;
    http_header_t *hdr;
    char save_char;
    char *s;
    membuffer soap_action_name;
    size_t n;

    /* find soapaction header */
    if (request->method == SOAPMETHOD_POST) {
        if (!httpmsg_find_hdr(request, HDR_SOAPACTION, &value))
            return SREQ_HDR_NOT_FOUND;
    } else {
        /* M-POST */
        /* get NS value from MAN header */
        hdr = httpmsg_find_hdr(request, HDR_MAN, &value);
        if (hdr == NULL)
            return SREQ_HDR_NOT_FOUND;
        if (matchstr(value.buf, value.length, "%q%i ; ns = %s",
                 &dummy_quote, &ns_value) != 0)
            return SREQ_BAD_HDR_FORMAT;
        /* create soapaction name header */
        membuffer_init(&soap_action_name);
        if (membuffer_assign(&soap_action_name,
            ns_value.buf, ns_value.length) == UPNP_E_OUTOF_MEMORY ||
                membuffer_append_str(&soap_action_name,
            "-SOAPACTION") == UPNP_E_OUTOF_MEMORY) {
            membuffer_destroy(&soap_action_name);
            return UPNP_E_OUTOF_MEMORY;
        }
        hdr = httpmsg_find_hdr_str(request, soap_action_name.buf);
        membuffer_destroy(&soap_action_name);
        if (!hdr)
            return SREQ_HDR_NOT_FOUND;
        value.buf = hdr->value.buf;
        value.length = hdr->value.length;
    }
    /* determine type */
    save_char = value.buf[value.length];
    value.buf[value.length] = '\0';
    s = strchr(value.buf, '#');
    if (s == NULL) {
        value.buf[value.length] = save_char;
        return SREQ_BAD_HDR_FORMAT;
    }
    /* move to value */
    s++;
    n = value.length - (size_t)(s - value.buf);
    if (matchstr(s, n, "%s", action_name) != PARSE_OK) {
        value.buf[value.length] = save_char;
        return SREQ_BAD_HDR_FORMAT;
    }
    /* action name or variable ? */
    if (memptr_cmp(action_name, "QueryStateVariable") == 0) {
        /* query variable */
        action_name->buf = NULL;
        action_name->length = 0;
    }
    /* restore */
    value.buf[value.length] = save_char;

    return 0;
}

/*!
 * \brief Sends SOAP error response.
 */
static void send_error_response(
    /*! [in] Socket info. */
    IN SOCKINFO *info,
    /*! [in] Error code. */
    IN int error_code,
    /*! [in] Error message. */
    IN const char *err_msg,
    /*! [in] HTTP request. */
    IN http_message_t *hmsg)
{
    /* off_t changed to int - j70578 */
    int content_length;
    int timeout_secs = SOAP_TIMEOUT;
    int m_major;
    int m_minor;
    const char *start_body =
/*        "<?xml version=\"1.0\"?>\n" required?? */
        "<s:Envelope "
        "xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" "
        "s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\n"
        "<s:Body>\n"
        "<s:Fault>\n"
        "<faultcode>s:Client</faultcode>\n"
        "<faultstring>UPnPError</faultstring>\n"
        "<detail>\n"
        "<UPnPError xmlns=\"urn:schemas-upnp-org:control-1-0\">\n"
        "<errorCode>";
    const char *mid_body =
        "</errorCode>\n"
        "<errorDescription>";
    const char *end_body =
        "</errorDescription>\n"
        "</UPnPError>\n"
        "</detail>\n"
        "</s:Fault>\n"
        "</s:Body>\n"
        "</s:Envelope>\n";
    char err_code_str[30];
    membuffer headers;

    memset(err_code_str,0,sizeof(err_code_str));
    snprintf(err_code_str, 30,"%d", error_code);
    /* calc body len */
    /* off_t changed to int - j70578 */
    content_length = (int) (strlen(start_body) + strlen(err_code_str) +
                  strlen(mid_body) + strlen(err_msg) +
                  strlen(end_body));
    http_CalcResponseVersion(hmsg->major_version, hmsg->minor_version,
                 &m_major, &m_minor);

    /*
        As per the DLNA Guideline.
        Requirement [7.2.5.6]: HTTP/1.1 servers of UPnP endpoints (devices and
        control points)should return HTTP version 1.1 in the response header,
        regardless of the version specified in the HTTP client's request.
    */

    DLNA_LOGV("[VPPDLNA][%s][:%d]:SOAP Server Receieve a request with HTTP"
            " Version %d.%d But as per DLNA guideline the response will be sent"
            " using HTTP %d.%d\n",__FUNCTION__,__LINE__,m_major,m_minor,
            HTTP11_MAJOR_VERSION, HTTP11_MINOR_VERSION);

    if (m_minor != HTTP11_MINOR_VERSION){
        m_minor = HTTP11_MINOR_VERSION;
    }

    /* make headers */
    membuffer_init(&headers);
    if (http_MakeMessage(&headers, m_major, m_minor,
            "RNsDsSXcc" "sssss",
            500,
            (off64_t)content_length,
            ContentTypeHeader,
            "EXT:\r\n",
            X_USER_AGENT,
            start_body, err_code_str, mid_body, err_msg,
            end_body) != 0) {
        membuffer_destroy(&headers);
        /* out of mem */
        return;
    }
    /* send err msg */
    (void)http_SendMessage(info, &timeout_secs, "b",
        headers.buf, headers.length);
    membuffer_destroy(&headers);
}

/*!
 * \brief Sends response of get var status.
 */
static UPNP_INLINE void send_var_query_response(
    /*! [in] Socket info. */
    SOCKINFO *info,
    /*! [in] Value of the state variable. */
    const char *var_value,
    /*! [in] HTTP request. */
    http_message_t *hmsg)
{
    /* off_t changed to int - j70578 */
    int content_length;
    int timeout_secs = SOAP_TIMEOUT;
    int m_major;
    int m_minor;
    const char *start_body =
        "<s:Envelope "
        "xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" "
        "s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\n"
        "<s:Body>\n"
        "<u:QueryStateVariableResponse "
        "xmlns:u=\"urn:schemas-upnp-org:control-1-0\">\n" "<return>";
    const char *end_body =
        "</return>\n"
        "</u:QueryStateVariableResponse>\n" "</s:Body>\n" "</s:Envelope>\n";
    membuffer response;

    http_CalcResponseVersion(hmsg->major_version, hmsg->minor_version,
                 &m_major, &m_minor);
    /* off_t changed to int - j70578 */
    content_length = (int) (strlen(start_body) + strlen(var_value) +
                  strlen(end_body));
    /* make headers */
    membuffer_init(&response);
    if (http_MakeMessage(&response, m_major, m_minor,
            "RNsDsSXcc" "sss",
            HTTP_OK,
            (off64_t)content_length,
            ContentTypeHeader,
            "EXT:\r\n",
            X_USER_AGENT,
            start_body, var_value, end_body) != 0) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to Create the HTTP response"
                        " Message\n", __FUNCTION__,__LINE__);
        membuffer_destroy(&response);
        /* out of mem */
        return;
    }
    /* send msg */
    (void)http_SendMessage(info, &timeout_secs, "b",
        response.buf, response.length);
    membuffer_destroy(&response);
}

/*!
 * \brief Separates the action node from the root DOM node.
 *
 * \return 0 if successful, or -1 if fails.
 */
static UPNP_INLINE int get_action_node(
    /*! [in] The root DOM node. */
    IXML_Document *TempDoc,
    /*! [in] IXML_Node name to be searched. */
    char *NodeName,
    /*! [out] Response/Output node. */
    IXML_Document **RespNode)
{
    IXML_Node *EnvpNode = NULL;
    IXML_Node *BodyNode = NULL;
    IXML_Node *ActNode = NULL;
    DOMString ActNodeName = NULL;
    const DOMString nodeName;
    int ret_code = -1;    /* error, by default */
    IXML_NodeList *nl = NULL;

    DLNA_LOGV("[VPPDLNA][%s][%d]:Need to find the node with name =%s\n ",
        __FUNCTION__,__LINE__,NodeName);

    *RespNode = NULL;
    /* Got the Envelope node here */
    EnvpNode = ixmlNode_getFirstChild((IXML_Node *) TempDoc);
    if (!EnvpNode)
        goto error_handler;
    nl = ixmlElement_getElementsByTagNameNS((IXML_Element *)EnvpNode,
                        "*", "Body");
    if (!nl){
        DLNA_LOGE("[VPPDLNA][%s][%d]:No Body Present in the SOAP "
            "Message\n ", __FUNCTION__,__LINE__);
        goto error_handler;
    }
    BodyNode = ixmlNodeList_item(nl, 0);
    if (!BodyNode){
        DLNA_LOGE("[VPPDLNA][%s][%d]: Body Node is not found\n ",
        __FUNCTION__,__LINE__);
        goto error_handler;
    }
    /* Got action node here */
    ActNode = ixmlNode_getFirstChild(BodyNode);
    if (!ActNode){
        DLNA_LOGE("[VPPDLNA][%s][%d]:No Action Present in the SOAP "
            "Message\n ", __FUNCTION__,__LINE__);
        goto error_handler;
    }
    /* Test whether this is the action node */
    nodeName = ixmlNode_getNodeName(ActNode);
    if (!nodeName){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to get the name of the node "
            "(Action Node)\n ", __FUNCTION__,__LINE__);
        goto error_handler;
    }
    if (!strstr(nodeName, NodeName)){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Received Action Node Does Not "
            "Contain the desired action. Action Node Name-%s Required Action-%s"
            " \n ", __FUNCTION__,__LINE__,nodeName,NodeName);
        goto error_handler;
    }
    else {
        ActNodeName = ixmlPrintNode(ActNode);
        if (!ActNodeName){
            DLNA_LOGE("[VPPDLNA][%s][%d]:ixmlPrintNode failed to create "
                "xml buffer\n ", __FUNCTION__,__LINE__);
            goto error_handler;
        }
        ret_code = ixmlParseBufferEx(ActNodeName, RespNode);
        ixmlFreeDOMString(ActNodeName);
        if (ret_code != IXML_SUCCESS) {
            DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to Parse the XML Buffer "
                "\n ", __FUNCTION__,__LINE__);
            ret_code = -1;
            goto error_handler;
        }
    }
    /* success */
    ret_code = 0;

error_handler:
    if (nl)
        ixmlNodeList_free(nl);
    return ret_code;
}

/*!
 * \brief Checks the soap body xml came in the SOAP request.
 *
 * \return UPNP_E_SUCCESS if successful else returns appropriate error.
 */
static int check_soap_body(
    /* [in] soap body xml document. */
    IN IXML_Document *doc,
    /* [in] URN. */
    IN const char *urn,
    /* [in] Name of the requested action. */
    IN const char *actionName)
{
    IXML_NodeList *nl = NULL;
    IXML_Node *bodyNode = NULL;
    IXML_Node *actionNode = NULL;
    const DOMString ns = NULL;
    const DOMString name = NULL;
    int ret_code = UPNP_E_INVALID_ACTION;

    nl = ixmlDocument_getElementsByTagNameNS(doc, SOAP_URN, SOAP_BODY);
    if (nl) {
        bodyNode = ixmlNodeList_item(nl, 0);
        if (bodyNode) {
            actionNode = ixmlNode_getFirstChild(bodyNode);
            if (actionNode) {
                ns = ixmlNode_getNamespaceURI(actionNode);
                name = ixmlNode_getLocalName(actionNode);
                if (name &&
                    ns && actionName &&
                    !HISTRCMP(actionName, name) &&
                    !HISTRCMP(urn, ns))
                    ret_code = UPNP_E_SUCCESS;
            }
        }
        ixmlNodeList_free(nl);
    }
    return ret_code;
}

/*!
 * \brief Checks the HTTP header of the SOAP request coming from the
 * control point.
 *
 * \return UPNP_E_SUCCESS if successful else returns appropriate error.
 */
static int check_soap_action_header(
    /*! [in] HTTP request. */
    http_message_t * request,
    /*! [in] URN. */
    const char *urn,
    /*! [out] Name of the SOAP action. */
    char **actionName)
{
    memptr header_name;
    http_header_t *soap_action_header = NULL;
    char *ns_compare = NULL;
    size_t tempSize = 0;
    int ret_code = UPNP_E_SUCCESS;
    char *temp_header_value = NULL;
    char *temp = NULL;
    char *temp2 = NULL;

    /* check soap action header */
    soap_action_header = httpmsg_find_hdr(request, HDR_SOAPACTION,
                          &header_name);
    if (!soap_action_header) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To Find the Soap"
            " Action Header\n",__FUNCTION__,__LINE__);
        ret_code = UPNP_E_INVALID_ACTION;
        return ret_code;
    }
    if (soap_action_header->value.length <= 0) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Null String is given as Soap"
            " Action Header\n",__FUNCTION__,__LINE__);
        ret_code = UPNP_E_INVALID_ACTION;
        return ret_code;
    }
    temp_header_value = UPNP_MALLOC(soap_action_header->value.length + 1);
    if (!temp_header_value) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to allocate Memory"
            " \n",__FUNCTION__,__LINE__);
        ret_code = UPNP_E_OUTOF_MEMORY;
        UPNP_FREE(temp_header_value);
        return ret_code;
    }
    strncpy(temp_header_value, soap_action_header->value.buf,
        soap_action_header->value.length);
    temp_header_value[soap_action_header->value.length] = 0;
    temp = strchr(temp_header_value, '#');
    if (!temp) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Invalid Soap Action Value. No '#' found. "
            "Action Header Value-%s\n",__FUNCTION__,__LINE__,temp_header_value);
        UPNP_FREE(temp_header_value);
        ret_code = UPNP_E_INVALID_ACTION;
        return ret_code;
    }

    (*temp) = 0;        /* temp make string */

    /* check to see if it is Query State Variable or
     * Service Action */
    tempSize = strlen(urn) + 2;
    ns_compare = UPNP_MALLOC(tempSize);
    if (!ns_compare) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to allocate Memory"
            " \n",__FUNCTION__,__LINE__);
        ret_code = UPNP_E_OUTOF_MEMORY;
        UPNP_FREE(temp_header_value);
        return ret_code;
    }
    memset(ns_compare,0,tempSize);
    (void)snprintf(ns_compare, tempSize, "\"%s", urn);
    if (HISTRCMP(temp_header_value, ns_compare))
        ret_code = UPNP_E_INVALID_ACTION;
    else {
        ret_code = UPNP_E_SUCCESS;
        temp++;
        temp2 = strchr(temp, '\"');
        /* remove ending " if present */
        if (temp2)
            (*temp2) = 0;
        if (*temp)
            (*actionName) = UPNP_STRDUP(temp);
        if (!*actionName)
            ret_code = UPNP_E_OUTOF_MEMORY;
    }

    UPNP_FREE(temp_header_value);
    UPNP_FREE(ns_compare);
    return ret_code;
}

/*!
 * \brief Retrives all the information needed to process the incoming SOAP
 * request. It finds the device and service info and also the callback
 * function to hand-over the request to the device application.
 *
 * \return UPNP_E_SUCCESS if successful else returns appropriate error.
 */
static int get_device_info(
    /*! [in] HTTP request. */
    http_message_t *request,
    /*! [in] flag for a querry. */
    int isQuery,
    /*! [in] Action request document. */
    IXML_Document *actionDoc,
    /*! [in] . */
    SOCKINFO *info,
    /*! [out] Device UDN string. */
    OUT char device_udn[LINE_SIZE],
    /*! [out] Service ID string. */
    char service_id[LINE_SIZE],
    /*! [out] callback function of the device application. */
    Upnp_FunPtr *callback,
    /*! [out] cookie stored by device application. */
    void **cookie)
{
    struct Handle_Info *device_info;
    service_info *serv_info = NULL;
    char save_char;
    /* error by default */
    int ret_code = -1;
    const char *control_url;
    char *actionName = NULL;
    UpnpDevice_Handle device_hnd;

    /* null-terminate pathquery of url */
    control_url = request->uri.pathquery.buff;
    save_char = control_url[request->uri.pathquery.size];
    ((char *)control_url)[request->uri.pathquery.size] = '\0';

    HandleLock();

       /*i57071/r72104
          We already have the corresponding device handle
          inside the received request
       */

    if (GetDeviceHandleInfoExt(info, &device_hnd,
        &device_info) != HND_DEVICE){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To Get the Device Handle"
            " Information\n",__FUNCTION__,__LINE__);
        goto error_handler;
    }

    serv_info = FindServiceControlURLPath(
        &device_info->ServiceTable, control_url);
    if (!serv_info){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To Find the Service"
            " Information for %s\n",__FUNCTION__,__LINE__,control_url);
        goto error_handler;
    }

    if (isQuery) {
        ret_code = check_soap_action_header(request,
            QUERY_STATE_VAR_URN, &actionName);
        if (ret_code != UPNP_E_SUCCESS &&
            ret_code != UPNP_E_OUTOF_MEMORY) {
            ret_code = UPNP_E_INVALID_ACTION;
            goto error_handler;
        }
        /* check soap body */
        ret_code = check_soap_body(actionDoc, QUERY_STATE_VAR_URN,
            actionName);
        UPNP_FREE(actionName);
        if (ret_code != UPNP_E_SUCCESS){
            DLNA_LOGE("[VPPDLNA][%s][%d]:Invalid SOAP Body found in the "
            " Message\n",__FUNCTION__,__LINE__);
            goto error_handler;
        }
    } else {
        ret_code = check_soap_action_header(request,
            serv_info->serviceType, &actionName);
        if (ret_code != UPNP_E_SUCCESS &&
            ret_code != UPNP_E_OUTOF_MEMORY) {
            ret_code = UPNP_E_INVALID_SERVICE;
            goto error_handler;
        }
        /* check soap body */
        ret_code = check_soap_body(actionDoc, serv_info->serviceType,
            actionName);
        UPNP_FREE(actionName);
        if (ret_code != UPNP_E_SUCCESS) {
            DLNA_LOGE("[VPPDLNA][%s][%d]:Invalid Service is being requested "
            " \n",__FUNCTION__,__LINE__);
            ret_code = UPNP_E_INVALID_SERVICE;
            goto error_handler;
        }
    }
    namecopy(service_id, serv_info->serviceId);
    namecopy(device_udn, serv_info->UDN);
    *callback = device_info->Callback;
    *cookie = device_info->Cookie;
    ret_code = 0;

 error_handler:
    /* restore */
    ((char *)control_url)[request->uri.pathquery.size] = save_char;
    HandleUnlock();
    return ret_code;
}

/*!
 * \brief Sends the SOAP action response.
 */
static UPNP_INLINE void send_action_response(
    /*! [in] Socket info. */
    SOCKINFO *info,
    /*! [in] The response document. */
    IXML_Document *action_resp,
    /*! [in] Action request document. */
    http_message_t *request)
{
    char *xml_response = NULL;
    char *response_buf = NULL;
    int response_length = 0;
    membuffer headers;
    int m_major, m_minor;
    int err_code;
    /* off_t changed to int - j70578 */
    int content_length;
    int ret_code;
    int timeout_secs = SOAP_TIMEOUT;
    static const char *start_body =
        /*"<?xml version=\"1.0\"?>" required?? */
        "<s:Envelope xmlns:s=\"http://schemas.xmlsoap."
        "org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap."
        "org/soap/encoding/\"><s:Body>\n";
    static const char *end_body = "</s:Body> </s:Envelope>";

    /* init */
    http_CalcResponseVersion(request->major_version, request->minor_version,
        &m_major, &m_minor);

    /*
        As per the DLNA Guideline.
        Requirement [7.2.5.6]: HTTP/1.1 servers of UPnP endpoints (devices and
        control points)should return HTTP version 1.1 in the response header,
        regardless of the version specified in the HTTP client's request.
    */

    DLNA_LOGV("[VPPDLNA][%s][:%d]:SOAP Server Receieve a request with HTTP"
            " Version %d.%d But as per DLNA guideline the response will be sent"
            " using HTTP %d.%d\n",__FUNCTION__,__LINE__,m_major,m_minor,
            HTTP11_MAJOR_VERSION, HTTP11_MINOR_VERSION);

    if (m_minor != HTTP11_MINOR_VERSION){
        m_minor = HTTP11_MINOR_VERSION;
    }

    membuffer_init(&headers);
    err_code = UPNP_E_OUTOF_MEMORY;    /* one error only */
    /* get xml */
    xml_response = ixmlPrintNode((IXML_Node *) action_resp);
    if (!xml_response){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to Generate the Soap "
            "response message\n", __FUNCTION__,__LINE__);
        goto error_handler;
    }
    /* off_t changed to int - j70578 */
    content_length = (int)(strlen(start_body) + strlen(xml_response) +
        strlen(end_body));
    /* make headers */
    if (http_MakeMessage(&headers, m_major, m_minor,
            "RNsDsSXcc",
            HTTP_OK,    /* status code */
            (off64_t)content_length,
            ContentTypeHeader,
            "EXT:\r\n", X_USER_AGENT) != 0) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to Create the HTTP "
                "response Message\n", __FUNCTION__,__LINE__);
        goto error_handler;
    }
    /* send whole msg */
    response_length = headers.length + strlen(start_body) + strlen(xml_response)+strlen(end_body);
    response_buf = (char *)malloc(response_length);
    if(response_buf != NULL)
    {
       memcpy(response_buf,headers.buf,headers.length);
       memcpy(response_buf + headers.length ,start_body,strlen(start_body));
       memcpy(response_buf + headers.length + strlen(start_body),xml_response, strlen(xml_response));
       memcpy(response_buf + headers.length + strlen(start_body) + strlen(xml_response) ,end_body, strlen(end_body));
       ret_code = http_SendMessage(
            info, &timeout_secs, "b",
            response_buf, response_length);
       free(response_buf);
    }
    else
    {
        ret_code = http_SendMessage(
            info, &timeout_secs, "bbbb",
            headers.buf, headers.length,
            start_body, strlen(start_body),
            xml_response, strlen(xml_response),
            end_body, strlen(end_body));
    }
    if (ret_code != 0) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to send response: "
            "err code = %d\n", __FUNCTION__,__LINE__,ret_code);
    }
    err_code = 0;

error_handler:
    ixmlFreeDOMString(xml_response);
    membuffer_destroy(&headers);
    if (err_code != 0) {
        DLNA_LOGE("[VPPDLNA][%s][%d]: Sending Error response to peer: "
            "err code = %d\n", __FUNCTION__,__LINE__,ret_code);
        /* only one type of error to worry about - out of mem */
        send_error_response(info, SOAP_ACTION_FAILED, "Out of memory",
            request);
    }
}

/*!
 * \brief Finds the name of the state variable asked in the SOAP request.
 *
 * \return 0 if successful else returns -1.
 */
static UPNP_INLINE int get_var_name(
    /*! [in] Document containing variable request. */
    IXML_Document *TempDoc,
    /*! [out] Name of the state varible. */
    char *VarName)
{
    IXML_Node *EnvpNode = NULL;
    IXML_Node *BodyNode = NULL;
    IXML_Node *StNode = NULL;
    IXML_Node *VarNameNode = NULL;
    IXML_Node *VarNode = NULL;
    const DOMString StNodeName = NULL;
    const DOMString Temp = NULL;
    int ret_val = -1;

    /* Got the Envelop node here */
    EnvpNode = ixmlNode_getFirstChild((IXML_Node *) TempDoc);
    if (EnvpNode == NULL)
        goto error_handler;
    /* Got Body here */
    BodyNode = ixmlNode_getFirstChild(EnvpNode);
    if (BodyNode == NULL)
        goto error_handler;
    /* Got action node here */
    StNode = ixmlNode_getFirstChild(BodyNode);
    if (StNode == NULL)
        goto error_handler;
    /* Test whether this is the action node */
    StNodeName = ixmlNode_getNodeName(StNode);
    if (StNodeName == NULL ||
        strstr(StNodeName, "QueryStateVariable") == NULL)
        goto error_handler;
    VarNameNode = ixmlNode_getFirstChild(StNode);
    if (VarNameNode == NULL)
        goto error_handler;
    VarNode = ixmlNode_getFirstChild(VarNameNode);
    Temp = ixmlNode_getNodeValue(VarNode);
    linecopy(VarName, Temp);
    DLNA_LOGI("[VPPDLNA]:Received query for variable  name %s\n", VarName);

    /* success */
    ret_val = 0;

error_handler:
    return ret_val;
}

/*!
 * \brief Handles the SOAP requests to querry the state variables.
 * This functionality has been deprecated in the UPnP V1.0 architecture.
 */
static UPNP_INLINE void handle_query_variable(
    /*! [in] Socket info. */
    SOCKINFO *info,
    /*! [in] HTTP request. */
    http_message_t *request,
    /*! [in] Document containing the variable request SOAP message. */
    IXML_Document *xml_doc)
{
    Upnp_FunPtr soap_event_callback;
    void *cookie;
    char var_name[LINE_SIZE];
    struct Upnp_State_Var_Request variable;
    const char *err_str;
    int err_code;

    /* get var name */
    if (get_var_name(xml_doc, var_name) != 0) {

        DLNA_LOGE("[VPPDLNA][%s][%d]:Sending Error Response To the peer."
            " Failed To get the state var name Error Code-%d\n",
            __FUNCTION__,__LINE__,SOAP_INVALID_VAR);
        send_error_response(info, SOAP_INVALID_VAR,
                    Soap_Invalid_Var, request);
        return;
    }
    /* get info for event */
    err_code = get_device_info(request, 1, xml_doc,
                   info,
                   variable.DevUDN,
                   variable.ServiceID,
                   &soap_event_callback, &cookie);
    if (err_code != 0) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To Get the Device "
            "Information. Sending Error Response to peer\n",
            __FUNCTION__,__LINE__);
        send_error_response(info, SOAP_INVALID_VAR,
                    Soap_Invalid_Var, request);
        return;
    }
    linecopy(variable.ErrStr, "");
    variable.ErrCode = UPNP_E_SUCCESS;
    namecopy(variable.StateVarName, var_name);
    variable.CurrentVal = NULL;
    variable.CtrlPtIPAddr = info->foreign_sockaddr;
    /* send event */
    DLNA_LOGI("[VPPDLNA][%s][d]:Calling Event Indication Callback with "
        "With Event-%d\n", __FUNCTION__,__LINE__,UPNP_CONTROL_GET_VAR_REQUEST);
    soap_event_callback(UPNP_CONTROL_GET_VAR_REQUEST, &variable, cookie);

    /* validate, and handle result */
    if (variable.CurrentVal == NULL) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Device Failed to handle the event"
                " \n", __FUNCTION__,__LINE__);
        err_code = SOAP_ACTION_FAILED;
        err_str = Soap_Action_Failed;
        send_error_response(info, SOAP_INVALID_VAR, Soap_Invalid_Var,
                    request);
        return;
    }
    if (variable.ErrCode != UPNP_E_SUCCESS) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Device Failed to handle the event"
           " Return Value from event callback-%d. Error Response wii be sent\n",
            __FUNCTION__,__LINE__,variable.ErrCode);
        if (strlen(variable.ErrStr) > 0) {
            err_code = SOAP_INVALID_VAR;
            err_str = Soap_Invalid_Var;
        } else {
            err_code = variable.ErrCode;
            err_str = variable.ErrStr;
        }
        send_error_response(info, err_code, err_str, request);
        return;
    }
    /* send response */
    send_var_query_response(info, variable.CurrentVal, request);
    ixmlFreeDOMString(variable.CurrentVal);
}

/*!
 * \brief Handles the SOAP action request. It checks the integrity of the SOAP
 * action request and gives the call back to the device application.
 */
static void handle_invoke_action(
    /*! [in] Socket info. */
    IN SOCKINFO *info,
    /*! [in] HTTP Request. */
    IN http_message_t *request,
    /*! [in] Name of the SOAP Action. */
    IN memptr action_name,
    /*! [in] Document containing the SOAP action request. */
    IN IXML_Document *xml_doc)
{
    char save_char;
    IXML_Document *resp_node = NULL;
    struct Upnp_Action_Request action;
    Upnp_FunPtr soap_event_callback;
    void *cookie = NULL;
    int err_code;
    const char *err_str;

    action.ActionResult = NULL;
    /* null-terminate */
    save_char = action_name.buf[action_name.length];
    action_name.buf[action_name.length] = '\0';
    /* set default error */

    DLNA_LOGV("[VPPDLNA][%s][%d]:\nAction Requested By the Peer --:%s\n",
        __FUNCTION__,__LINE__,action_name);

    err_code = SOAP_INVALID_ACTION;
    err_str = Soap_Invalid_Action;
    /* get action node */
    if (get_action_node(xml_doc, action_name.buf, &resp_node) == -1){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To Get the Action Node From"
            " The request received from the peer\n",__FUNCTION__,__LINE__);
        goto error_handler;
    }
    /* get device info for action event */
    err_code = get_device_info(request,
                   0,
                   xml_doc,
                   info,
                   action.DevUDN,
                   action.ServiceID,
                   &soap_event_callback,&cookie);

    if (err_code != UPNP_E_SUCCESS){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed To Get the Device Information\r\n",
                    __FUNCTION__,__LINE__);
        if (UPNP_E_INVALID_SERVICE == err_code)
        {
            err_str = Soap_Invalid_Service;
        }

        goto error_handler;
    }
    namecopy(action.ActionName, action_name.buf);
    linecopy(action.ErrStr, "");
    action.ActionRequest = resp_node;
    action.ActionResult = NULL;
    action.ErrCode = UPNP_E_SUCCESS;
    action.CtrlPtIPAddr = info->foreign_sockaddr;
    DLNA_LOGI("[VPPDLNA][%s][%d]:Calling Callback\n",__FUNCTION__,__LINE__);
    (void)soap_event_callback(UPNP_CONTROL_ACTION_REQUEST, &action, cookie);
    if (action.ErrCode != UPNP_E_SUCCESS) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:soap_event_callback failed with error"
        "code-%d\n",__FUNCTION__,__LINE__,action.ErrCode);
        if (strlen(action.ErrStr) <= 0) {
            err_code = SOAP_ACTION_FAILED;
            err_str = Soap_Action_Failed;
        } else {
            err_code = action.ErrCode;
            err_str = action.ErrStr;
        }
        goto error_handler;
    }
    /* validate, and handle action error */
    if (action.ActionResult == NULL) {
        err_code = SOAP_ACTION_FAILED;
        err_str = Soap_Action_Failed;
        goto error_handler;
    }
    /* send response */
    send_action_response(info, action.ActionResult, request);
    err_code = 0;

    /* error handling and cleanup */
error_handler:
    ixmlDocument_free(action.ActionResult);
    ixmlDocument_free(resp_node);
    /* restore */
    action_name.buf[action_name.length] = save_char;
    if (err_code != 0){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Handling Of SOAP action failed "
            "Sending Error Response To the Peer Error Codee-%d\n",
            __FUNCTION__,__LINE__,err_code);
        send_error_response(info, err_code, err_str, request);
    }
}

/*!
 * \brief This is a callback called by minisever after receiving the request
 * from the control point. This function will start processing the request.
 * It calls handle_invoke_action to handle the SOAP action.
 */
void soap_device_callback(
    /*! [in] Parsed request received by the device. */
    http_parser_t *parser,
    /*! [in] HTTP request. */
    http_message_t *request,
    /*! [in,out] Socket info. */
    SOCKINFO *info)
{
    int err_code;
    const char *err_str;
    memptr action_name;
    IXML_Document *xml_doc = NULL;

    DLNA_LOGI("[VPPDLNA][%s][%d]:\nIn soap_device_callback\n",__FUNCTION__,
                __LINE__);

    /* set default error */
    err_code = SOAP_INVALID_ACTION;
    err_str = Soap_Invalid_Action;

    /* validate: content-type == text/xml */
    if (!has_xml_content_type(request)){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Invalid Content Type\n",__FUNCTION__,
                __LINE__);
        goto error_handler;
    }
    /* type of request */
    if (get_request_type(request, &action_name) != 0){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Invalid Request Type\n",__FUNCTION__,
                __LINE__);
        goto error_handler;
    }

    /* parse XML */
    err_code = ixmlParseBufferEx(request->entity.buf, &xml_doc);
    if (err_code != IXML_SUCCESS) {
        DLNA_LOGE("[VPPDLNA][%s][%d]:Failed to Parse the Request Message."
            " Error Code-%d\n",__FUNCTION__,__LINE__,err_code);
        if (err_code == IXML_INSUFFICIENT_MEMORY)
            err_code = UPNP_E_OUTOF_MEMORY;
        else
            err_code = SOAP_ACTION_FAILED;
        err_str = "XML error";
        goto error_handler;
    }

    if (action_name.length == 0)
        /* query var */
        handle_query_variable(info, request, xml_doc);   /* checkmark l57071 r72041 */
    else
        /* invoke action */
        handle_invoke_action(info, request, action_name, xml_doc);
    /* no error */
    err_code = 0;

 error_handler:
    ixmlDocument_free(xml_doc);
    if (err_code != 0){
        DLNA_LOGE("[VPPDLNA][%s][%d]:Sending Error Response To the peer."
            " Error Code-%d\n",__FUNCTION__,__LINE__,err_code);
        send_error_response(info, err_code, err_str, request);
    }
    parser = parser;
    return;
}

#endif /* EXCLUDE_SOAP */

#endif /* INCLUDE_DEVICE_APIS */
