#include "avformat.h"
#include "internal.h"
#include "avio.h"
#include "hls_read.h"
#include "network.h"
#include "url.h"

int hls_open_h(URLContext **puc, const char *filename, int flags, const AVIOInterruptCB *int_cb, AVDictionary **options)
{
    int retry = 3;
    int ret = -1;

    while ((ret < 0) && (retry > 0))
    {
        if (ff_check_interrupt(int_cb))
            return -1;
        /**
         * make a tmp copy for options, because options will
         * will be freed inner av_opt_set_dict.
         */
        AVDictionary *tmp_opts = NULL;
        av_dict_copy(&tmp_opts, *options, 0);
        ret = ffurl_open_h(puc, filename, flags, int_cb, &tmp_opts);
        av_dict_free(&tmp_opts);
        if(ret < 0)
        {
            av_log(NULL, AV_LOG_ERROR, "ffurl_open_h failed, try again");
            retry--;
        }
    }
    return ret;
}

int hls_read_complete(URLContext *h, int64_t offset, unsigned char *buf, int size)
{
    int64_t new_off = offset;
    int ret = -1;
    int read_size = size;
    int retry = 1;

    while(retry > 0)
    {
        if (ff_check_interrupt(&(h->interrupt_callback)) > 0)
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] force quit \n", __FILE__, __LINE__);
            ret = -1;
            break;
        }

        ret = ffurl_read_complete(h, buf, read_size);
        if(ret >= 0)
        {
            if(new_off == offset || offset < 0)
            {
                return ret;
            }else if(new_off > offset){
                return -1;
            }
            new_off += ret;
            if(new_off == offset)
            {
                read_size = size;
            }else if(offset > new_off){
                if(offset - new_off > size)
                {
                    read_size = size;
                }else{
                    read_size = offset - new_off;
                }
            }
            continue;
        }else{
            if(ret == AVERROR(ECONNRESET))
            {
                if(offset > 0)
                {
                    new_off = 0;
                    if(offset - new_off > size)
                    {
                        read_size = size;
                    }else{
                        read_size = offset - new_off;
                    }
                }
                //fixbug: when retry is 1,ret is AVERROR(ECONNRESET),will quit the while cycle, lead to EOF.
                retry = 3;
            }
        }
        retry--;
    }
    return ret;

}

int hls_read(URLContext *h, int64_t offset, unsigned char *buf, int size)
{
    int64_t new_off = offset;
    int ret = -1;
    int read_size = size;
    int retry = 1;

    while(retry > 0)
    {
        if (ff_check_interrupt(&(h->interrupt_callback)) > 0)
        {
            av_log(NULL, AV_LOG_ERROR, "[%s:%d] force quit \n", __FILE__, __LINE__);
            ret = -1;
            break;
        }

        ret = ffurl_read(h, buf, read_size);
        if(ret >= 0)
        {
            if(new_off == offset || offset < 0)
            {
                return ret;
            }else if(new_off > offset){
                return ret;
            }
            new_off += ret;
            if(new_off == offset)
            {
                read_size = size;
            }else if(offset > new_off){
                if(offset - new_off > size)
                {
                    read_size = size;
                }else{
                    read_size = offset - new_off;
                }
            }
            continue;
        }else{
            if(ret == AVERROR(ECONNRESET))
            {
                if(offset > 0)
                {
                    new_off = 0;
                    if(offset - new_off > size)
                    {
                        read_size = size;
                    }else{
                        read_size = offset - new_off;
                    }
                }

                retry = 3;
            }
        }
        retry--;
    }
    return ret;
}

int hls_close(URLContext *h)
{
    return ffurl_close(h);
}
