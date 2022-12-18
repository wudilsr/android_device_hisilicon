/*
 * svr_udf_protocol.c
 *
 *  Created on: 2014Äê6ÔÂ18ÈÕ
 *      Author: z00187490
 */
#include <libavformat/avformat.h>
#include "libudf.h"

typedef struct UDFContext
{
    struct udf_api api;
    libudf_file_t* file;
} UDFContext;

static int udf_prot_open(URLContext *h, const char *uri, int flags)
{
    UDFContext* udf = h->priv_data;
    char* tmp = NULL;
    char* udf_str = NULL;

    /* we must use dlopen to avoid recursive library dependence */
    if (udf_api_load(&udf->api) < 0)
    {
        return -1;
    }

    tmp = strdup(uri);
    if (tmp)
    {
        /*remove udf handle while open new file by here*/
        udf_str = av_stristr(tmp, "&udf_handle=");
        if (udf_str) {
            *udf_str = 0;
            udf_str += strlen("&udf_handle=0xffffffff");
            strncat(tmp, udf_str, strlen(udf_str));
        }
        uri = tmp;
    }

    av_log(h, AV_LOG_DEBUG, "udf open:%s", uri);

    udf->file = udf->api.open_file(uri);
    av_freep(&tmp);

    if (!udf->file) {
        av_log(h, AV_LOG_ERROR, "udf open %s failed", uri);
        return -1;
    }
    return 0;
}

static int udf_prot_read(URLContext *h, uint8_t *buf, int size)
{
    UDFContext* udf = h->priv_data;
    return udf->api.read_file(udf->file, buf, size);
}

static int64_t udf_prot_seek(URLContext *h, int64_t off, int whence)
{
    UDFContext* udf = h->priv_data;
    return udf->api.seek_file(udf->file, off, whence);
}

static int udf_prot_close(URLContext *h)
{
    UDFContext* udf = h->priv_data;
    udf->api.close_file(udf->file);
    udf_api_close(&udf->api);
    return 0;
}

URLProtocol svr_udf_protocol = {
    .name                = "udf",
    .url_open            = udf_prot_open,
    .url_read            = udf_prot_read,
    .url_seek            = udf_prot_seek,
    .url_write           = NULL,
    .url_close           = udf_prot_close,
    .url_read_pause      = NULL,
    .url_get_file_handle = NULL,
    .priv_data_size      = sizeof(UDFContext),
//    .flags               = URL_PROTOCOL_FLAG_NETWORK,
};
