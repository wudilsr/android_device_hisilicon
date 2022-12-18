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

#ifndef AVFORMAT_HLS_KEY_DECRYPT_H
#define AVFORMAT_HLS_KEY_DECRYPT_H

#include "avformat.h"
#include "libavutil/aes.h"
#include "libavutil/avstring.h"
#include "internal.h"

int hls_decrypt_open(Hls_CryptoContext *h, const char *url, AVDictionary **options, const char *headers,
        const uint8_t *key, int keylen, const uint8_t *iv, int ivlen);

int hls_decrypt_read(Hls_CryptoContext *h, uint8_t *buf, int size);

int hls_decrypt_close(Hls_CryptoContext *h);

#endif /* AVFORMAT_HLS_KEY_DECRYPT_H */
