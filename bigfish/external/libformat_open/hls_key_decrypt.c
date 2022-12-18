/*
 * Decryption protocol handler
 * Copyright (c) 2011 Martin Storsjo
 *
 * This file is part of Libav.
 *
 * Libav is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * Libav is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "avformat.h"
#include "libavutil/aes.h"
#include "libavutil/avstring.h"
#include "libavcodec/opt.h"
#include "internal.h"
#include "url.h"
#include "hls_read.h"

#include "hls_key_decrypt.h"

#define __FILE_NAME__     av_filename(__FILE__)

int hls_decrypt_open(Hls_CryptoContext *h, const char *url,  AVDictionary **options,
        const uint8_t *key, int keylen, const uint8_t *iv, int ivlen)
{
    int ret;

    h->keylen = keylen;
    h->ivlen  = ivlen;

    av_log(NULL, AV_LOG_ERROR, "[%s:%d] %s IN\n", __FILE_NAME__, __LINE__, __FUNCTION__);

    if (h->keylen < HLS_DECRYPT_BLOCKSIZE || h->ivlen < HLS_DECRYPT_BLOCKSIZE) {
        av_log(h, AV_LOG_ERROR, "Key or IV not set\n");
        return AVERROR(EINVAL);
    }

    h->key = av_mallocz(keylen);
    h->iv  = av_mallocz(ivlen);
    if (!h->key || !h->iv)
        return AVERROR(ENOMEM);

    memcpy(h->key, key, keylen);
    memcpy(h->iv, iv, ivlen);

    ret = hls_open_h(&h->hd, url, URL_RDONLY, &(h->interrupt_callback), options);
    h->offset = 0;

    if (ret < 0) {
        av_log(h, AV_LOG_ERROR, "Unable to open input url='%s'\n", url);
        return ret;
    }

    h->aes = av_mallocz(av_aes_size);
    if (!h->aes) return AVERROR(ENOMEM);

    av_aes_init(h->aes, h->key, 128, 1);

    return 0;
}

int hls_decrypt_read(Hls_CryptoContext *h, uint8_t *buf, int size)
{
    int blocks;

    if (!h) return AVERROR(EINVAL);

retry:

    if (h->outdata > 0) {
        size = FFMIN(size, h->outdata);
        memcpy(buf, h->outptr, size);
        h->outptr  += size;
        h->outdata -= size;
        return size;
    }

    // We avoid using the last block until we've found EOF,
    // since we'll remove PKCS7 padding at the end. So make
    // sure we've got at least 2 blocks, so we can decrypt
    // at least one.
    while (h->indata - h->indata_used < 2*HLS_DECRYPT_BLOCKSIZE) {
        int n = hls_read(h->hd, h->offset, h->inbuffer + h->indata,
                         sizeof(h->inbuffer) - h->indata);
        if (n <= 0) {
            h->eof = 1;
            break;
        }

        h->offset += n;
        h->indata += n;
    }

    blocks = (h->indata - h->indata_used) / HLS_DECRYPT_BLOCKSIZE;
    if (!blocks)
        return AVERROR_EOF;
    if (!h->eof)
        blocks--;

    av_aes_crypt(h->aes, h->outbuffer, h->inbuffer + h->indata_used, blocks,
                 h->iv, 1);

    h->outdata      = HLS_DECRYPT_BLOCKSIZE * blocks;
    h->outptr       = h->outbuffer;
    h->indata_used += HLS_DECRYPT_BLOCKSIZE * blocks;

    if (h->indata_used >= sizeof(h->inbuffer)/2) {
        memmove(h->inbuffer, h->inbuffer + h->indata_used,
                h->indata - h->indata_used);
        h->indata     -= h->indata_used;
        h->indata_used = 0;
    }

    if (h->eof) {
        // Remove PKCS7 padding at the end
        int padding = h->outbuffer[h->outdata - 1];
        h->outdata -= padding;
    }

    goto retry;
}

int hls_decrypt_close(Hls_CryptoContext *h)
{
    if (!h) return 0;

    if (h->hd) { hls_close(h->hd); h->hd = NULL;}
    if (h->iv) { av_freep(&h->iv); h->iv = NULL;}
    if (h->key) { av_freep(&h->key); h->key = NULL;}
    if (h->aes) { av_freep(&h->aes); h->aes = NULL;}
    h->offset = 0;
    return 0;
}
