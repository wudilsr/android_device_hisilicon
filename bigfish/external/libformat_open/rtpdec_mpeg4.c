/**
 * Common code for the RTP depacketization of MPEG-4 formats.
 * Copyright (c) 2010 Fabrice Bellard
 *                    Romain Degez
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file
 * @brief MPEG4 / RTP Code
 * @author Fabrice Bellard
 * @author Romain Degez
 */

#include "rtpdec_formats.h"
#include "libavformat/internal.h"
#include "libavutil/avstring.h"
#include "libavcodec/get_bits.h"

#define AAC_PROFILE_LC      1
/** Structure listing useful vars to parse RTP packet payload*/
struct PayloadContext
{
    int sizelength;
    int indexlength;
    int indexdeltalength;
    int profile_level_id;
    int streamtype;
    int objecttype;
    char *mode;

    /** mpeg 4 AU headers */
    struct AUHeaders {
        int size;
        int index;
        int cts_flag;
        int cts;
        int dts_flag;
        int dts;
        int rap_flag;
        int streamstate;
    } *au_headers;
    int au_headers_allocated;
    int nb_au_headers;
    int au_headers_length_bytes;
    int cur_au_index;
};

typedef struct {
    const char *str;
    uint16_t    type;
    uint32_t    offset;
} AttrNameMap;
/**add for bug2012062701d00198887**/
typedef struct tagADTSHeader
{
    /* fixed */
    int32_t  sync;                           /* syncword */
    uint8_t   id;                             /* MPEG bit - should be 1 */
    uint8_t   layer;                          /* MPEG layer - should be 0 */
    uint8_t   protectBit;                     /* 0 = CRC word follows, 1 = no CRC word */
    uint8_t   profile;                        /* 0 = main, 1 = LC, 2 = SSR, 3 = reserved */
    uint8_t   sampRateIdx;                    /* sample rate index range = [0, 11] */
    uint8_t   privateBit;                     /* ignore */
    uint8_t   channelConfig;                  /* 0 = implicit, >0 = use default table */
    uint8_t   origCopy;                       /* 0 = copy, 1 = original */
    uint8_t   home;                           /* ignore */

    /* variable */
    uint8_t   copyBit;                        /* 1 bit of the 72-bit copyright ID (transmitted as 1 bit per frame) */
    uint8_t   copyStart;                      /* 1 = this bit starts the 72-bit ID, 0 = it does not */
    int32_t   frameLength;                    /* length of frame */
    int32_t   bufferFull;                     /* number of 32-bit words left in enc buffer, 0x7FF = VBR */
    uint8_t   numRawDataBlocks;               /* number of raw data blocks in frame */

    /* CRC */
    int32_t   crcCheckWord;                   /* 16-bit CRC check word (present if protectBit == 0) */
} ADTSHeader;

/* All known fmtp parameters and the corresponding RTPAttrTypeEnum */
#define ATTR_NAME_TYPE_INT 0
#define ATTR_NAME_TYPE_STR 1
static const AttrNameMap attr_names[]=
{
    { "SizeLength",       ATTR_NAME_TYPE_INT,
      offsetof(PayloadContext, sizelength) },
    { "IndexLength",      ATTR_NAME_TYPE_INT,
      offsetof(PayloadContext, indexlength) },
    { "IndexDeltaLength", ATTR_NAME_TYPE_INT,
      offsetof(PayloadContext, indexdeltalength) },
    { "profile-level-id", ATTR_NAME_TYPE_INT,
      offsetof(PayloadContext, profile_level_id) },
    { "StreamType",       ATTR_NAME_TYPE_INT,
      offsetof(PayloadContext, streamtype) },
    { "mode",             ATTR_NAME_TYPE_STR,
      offsetof(PayloadContext, mode) },
    { NULL, -1, -1 },
};

static PayloadContext *new_context(void)
{
    return av_mallocz(sizeof(PayloadContext));
}

static void free_context(PayloadContext * data)
{
    int i;
    for (i = 0; i < data->nb_au_headers; i++) {
         /* according to rtp_parse_mp4_au, we treat multiple
          * au headers as one, so nb_au_headers is always 1.
          * loop anyway in case this changes.
          * (note: changes done carelessly might lead to a double free)
          */
       //av_free(&data->au_headers[i]);
    }
    av_free(data->au_headers);
    av_free(data->mode);
    av_free(data);
}

static int parse_fmtp_config(AVCodecContext * codec, char *value)
{
    /* decode the hexa encoded parameter */
    int len = ff_hex_to_data(NULL, value);
    av_free(codec->extradata);
    codec->extradata = av_mallocz(len + FF_INPUT_BUFFER_PADDING_SIZE);
    if (!codec->extradata)
        return AVERROR(ENOMEM);
    codec->extradata_size = len;
    ff_hex_to_data(codec->extradata, value);
    return 0;
}
/**add for bug2012062701d00198887**/
static int get_bits_func(const uint8_t *pBuf, uint32_t u32ByteOffset, uint32_t u32Startbit, uint32_t u32Bitlen)
{
    uint8_t   *b = NULL;
    int   v = -1;
    uint32_t   mask = 0;
    uint32_t   tmp_long = 0;
    uint32_t   bitHigh = 0;
    uint32_t   offset = 0;

    if (u32Bitlen > 32)
    {
        return -1;
    }

    if (pBuf == NULL)
    {
        return -1;
    }

    b = (uint8_t*)&pBuf[u32ByteOffset + (u32Startbit >> 3)];

    u32Startbit %= 8;

    if ((uint32_t)0  == u32Bitlen )
    {
        return -1;
    }

    offset = (u32Bitlen-1) >> 3;

    switch (offset)
    {
    case 0:             /*-- 1..8 bit*/
        tmp_long = (uint32_t)((*(b)<< 8) + *(b+1));
        bitHigh = 16;
        break;

    case 1:             /* -- 9..16 bit*/
        tmp_long = (uint32_t)((*(b)<<16) + (*(b+1)<< 8) + *(b+2));
        bitHigh = 24;
        break;

    case 2:             /*-- 17..24 bit*/
        tmp_long = (uint32_t)((*(b)<<24) + (*(b+1)<<16) + (*(b+2)<< 8) + *(b+3));
        bitHigh = 32;
        break;

    case 3:             /* -- 25..32 bit*/
        tmp_long = (uint32_t)(((uint32_t)(*(b))<<32)+((uint32_t)(*(b+1 ))<<24) + ((uint32_t)(*(b+2))<<16)
            + ((uint32_t)(*(b+3))<<8) + (uint32_t)(*(b+4)));
        bitHigh = 40;
        break;

    default:    /* -- 33.. bits: fail, deliver constant fail value*/
        return -1;
    }

    u32Startbit = bitHigh - (u32Startbit + u32Bitlen);
    tmp_long = tmp_long >> u32Startbit;

    if (u32Bitlen == 32 )
    {
        mask = 0xFFFFFFFF;
    }
    else
    {
        mask = (((uint32_t)0x00000001) << u32Bitlen) - 1;
    }

    v= tmp_long & mask;

    return v;
}

static void aac_get_adts_header(int32_t sampleRateidx,             /*!< aacPlus sampling frequency (incl. SBR) */
                            int32_t     frameLength,            /*!< raw data length */
                            int32_t     profile,                /* 0 = main, 1 = LC, 2 = SSR, 3 = reserved */
                            int32_t     ch,
                            uint8_t     *pADTSHeadBuf)
{
    int32_t  head0 = 0, head1 = 0;
    ADTSHeader fhADTS;

    frameLength += 7;  /* 7 bytes ADTS */

    /* fixed fields - should not change from frame to frame */

    fhADTS.sync =             0x0fff;          /* 12bit: */
    fhADTS.id =               0;               /* 1bit: MPEG bit - should be 1 */
    fhADTS.layer =            0;               /* 2bit: MPEG layer - should be 0 */
    fhADTS.protectBit =       1;               /* 1bit: */
    fhADTS.profile =          profile;         /* 2bit: */
    fhADTS.sampRateIdx =      sampleRateidx;     /* 4bit: */
    fhADTS.privateBit =       0;               /* 1bit: */
    fhADTS.channelConfig =    ch;              /* 3bit: */
    fhADTS.origCopy =         0;               /* 1bit: */
    fhADTS.home =             0;               /* 1bit: */

    /* variable fields - can change from frame to frame */

    fhADTS.copyBit =          0;              /* 1bit: */
    fhADTS.copyStart =        0;              /* 1bit: */
    fhADTS.frameLength =      frameLength;    /* 13bit: */
    fhADTS.bufferFull =       0x07ff;         /* 11bit: */
    fhADTS.numRawDataBlocks = 0;              /* 2bit: */

    head0  = fhADTS.sync       <<(32-12);
    head0 |= fhADTS.id         <<(32-12-1);
    head0 |= fhADTS.layer      <<(32-12-1-2);
    head0 |= fhADTS.protectBit <<(32-12-1-2-1);

    head0 |= fhADTS.profile       <<(32-12-1-2-1 -2);
    head0 |= fhADTS.sampRateIdx   <<(32-12-1-2-1 -2 -4);
    head0 |= fhADTS.privateBit    <<(32-12-1-2-1 -2 -4 -1);
    head0 |= fhADTS.channelConfig <<(32-12-1-2-1 -2 -4 -1 - 3);
    head0 |= fhADTS.origCopy      <<(32-12-1-2-1 -2 -4 -1 - 3 - 1);
    head0 |= fhADTS.home          <<(32-12-1-2-1 -2 -4 -1 - 3 - 1- 1);
    head0 |= fhADTS.copyBit       <<(32-12-1-2-1 -2 -4 -1 - 3 - 1- 1- 1);
    head0 |= fhADTS.copyStart     <<(32-12-1-2-1 -2 -4 -1 - 3 - 1- 1- 1- 1);
    head0 |= ((fhADTS.frameLength>>(13-2)) & 0x3);

    head1  = fhADTS.frameLength      <<(32-13+2);
    head1 |= fhADTS.bufferFull       <<(32-13+2-11);
    head1 |= fhADTS.numRawDataBlocks <<(32-13+2-11-2);

    pADTSHeadBuf[0] = (unsigned char)(head0>>24)&0xff;
    pADTSHeadBuf[1] = (unsigned char)(head0>>16)&0xff;
    pADTSHeadBuf[2] = (unsigned char)(head0>>8)&0xff;
    pADTSHeadBuf[3] = (unsigned char)(head0>>0)&0xff;

    pADTSHeadBuf[4] = (unsigned char)(head1>>24)&0xff;
    pADTSHeadBuf[5] = (unsigned char)(head1>>16)&0xff;
    pADTSHeadBuf[6] = (unsigned char)(head1>>8)&0xff;
    return;
}

static int aac_dec_adts_extradata(uint8_t *pu8Buf, uint32_t u32Size, uint32_t *pu32SampleRateIdx,
    uint32_t *pu32Profile, uint32_t *pu32Channel)
{
    uint32_t u32SampleRateIdx = 0, u32Profile = 0, u32Channel = 0;

    if (NULL == pu8Buf || u32Size < 2)
    {
        return -1;
    }

    u32Profile = get_bits_func(pu8Buf, 0, 0, 5) - 1;
    u32SampleRateIdx = get_bits_func(pu8Buf, 0, 5, 4);
    u32Channel = get_bits_func(pu8Buf, 0, 9, 4);

    *pu32SampleRateIdx = u32SampleRateIdx;
    *pu32Profile = u32Profile;
    *pu32Channel = u32Channel;

    return 0;
}

static int rtp_parse_mp4_au(PayloadContext *data, const uint8_t *buf, int *audio_es_size)
{
    int au_headers_length, au_header_size, i;
    GetBitContext getbitcontext;

    /* decode the first 2 bytes where the AUHeader sections are stored
       length in bits */
    au_headers_length = AV_RB16(buf);

    if (au_headers_length > RTP_MAX_PACKET_LENGTH)
      return -1;

    data->au_headers_length_bytes = (au_headers_length + 7) / 8;

    /* skip AU headers length section (2 bytes) */
    buf += 2;

    init_get_bits(&getbitcontext, buf, data->au_headers_length_bytes * 8);

    /* XXX: Wrong if optionnal additional sections are present (cts, dts etc...) */
    au_header_size = data->sizelength + data->indexlength;
    if (au_header_size <= 0 || (au_headers_length % au_header_size != 0))
        return -1;

    data->nb_au_headers = au_headers_length / au_header_size;
    if (!data->au_headers || data->au_headers_allocated < data->nb_au_headers) {
        av_free(data->au_headers);
        data->au_headers = av_malloc(sizeof(struct AUHeaders) * data->nb_au_headers);
        data->au_headers_allocated = data->nb_au_headers;
    }

    /* XXX: We handle multiple AU Section as only one (need to fix this for interleaving)
       In my test, the FAAD decoder does not behave correctly when sending each AU one by one
       but does when sending the whole as one big packet...  */
    data->au_headers[0].size = 0;
    data->au_headers[0].index = 0;
    /**begin modify for bug2012062701d00198887**/
    for (i = 0; i < data->nb_au_headers; ++i) {
        data->au_headers[i].size = get_bits_long(&getbitcontext, data->sizelength);
        data->au_headers[i].index = get_bits_long(&getbitcontext, data->indexlength);
        *audio_es_size += data->au_headers[i].size;
    }
    //data->nb_au_headers = 1;
    /**end bug2012062701d00198887**/
    return 0;
}


/* Follows RFC 3640 */
static int aac_parse_packet(AVFormatContext *ctx,
                            PayloadContext *data,
                            AVStream *st,
                            AVPacket *pkt,
                            uint32_t *timestamp,
                            const uint8_t *buf, int len, int flags)
{
    int audio_es_size = 0;
    if (rtp_parse_mp4_au(data, buf, &audio_es_size))
        return -1;
    buf += data->au_headers_length_bytes + 2;
    len -= data->au_headers_length_bytes + 2;

    /**begin solve the problem playing aac is not fluent/add by duanqingpeng00198887 bug2012062701d00198887**/
    //add adts info to every aac es stream
    const int ADTS_LEN = 7;
    int codec_extra_size = st->codec->extradata_size;
    uint8_t* codec_extra_data = st->codec->extradata;
    int au_frame_count = data->nb_au_headers;
    uint32_t u32_sampleRateIdx = 3, u32_channel = 2, u32_profile = AAC_PROFILE_LC;
    int packet_data_size = au_frame_count * ADTS_LEN + audio_es_size;
    av_new_packet(pkt, packet_data_size);
    if (NULL == pkt->data) {
        return -1;
    }
    if (0 == aac_dec_adts_extradata(codec_extra_data, codec_extra_size, &u32_sampleRateIdx, &u32_profile, &u32_channel)) {
        int offset = 0;
        int buf_offset=  0;
        int i = 0;
        for(; i < au_frame_count; i++) {
            int au_frame_size =  data->au_headers[i].size;
            aac_get_adts_header(u32_sampleRateIdx, au_frame_size, u32_profile, u32_channel, pkt->data + offset);
            offset += 7;
            memcpy(pkt->data + offset, buf + buf_offset, au_frame_size);
            offset += au_frame_size;
            buf_offset += au_frame_size;
        }
     } else {
        av_free_packet(pkt);
        return -1;
     }
     /**end bug2012062701d00198887**/
    /* XXX: Fixme we only handle the case where rtp_parse_mp4_au define
                    one au_header */

    //memcpy(pkt->data, buf, data->au_headers[0].size);
    pkt->stream_index = st->index;
    return 0;
}

static int parse_fmtp(AVStream *stream, PayloadContext *data,
                      char *attr, char *value)
{
    AVCodecContext *codec = stream->codec;
    int res, i;

    if (!av_strcmp(attr, "config")) {
        res = parse_fmtp_config(codec, value);

        if (res < 0)
            return res;
    }

    if (codec->codec_id == CODEC_ID_AAC) {
        /* Looking for a known attribute */
        for (i = 0; attr_names[i].str; ++i) {
            if (!av_strcasecmp(attr, attr_names[i].str)) {
                if (attr_names[i].type == ATTR_NAME_TYPE_INT) {
                    *(int *)((char *)data+
                        attr_names[i].offset) = atoi(value);
                } else if (attr_names[i].type == ATTR_NAME_TYPE_STR)
                    *(char **)((char *)data+
                        attr_names[i].offset) = av_strdup(value);
            }
        }
    }
    return 0;
}

static int parse_sdp_line(AVFormatContext *s, int st_index,
                          PayloadContext *data, const char *line)
{
    const char *p;

    if (av_strstart(line, "fmtp:", &p))
        return ff_parse_fmtp(s->streams[st_index], data, p, parse_fmtp);

    return 0;
}

RTPDynamicProtocolHandler ff_mp4v_es_dynamic_handler = {
    .enc_name           = "MP4V-ES",
    .codec_type         = AVMEDIA_TYPE_VIDEO,
    .codec_id           = CODEC_ID_MPEG4,
    .parse_sdp_a_line   = parse_sdp_line,
};

RTPDynamicProtocolHandler ff_mpeg4_generic_dynamic_handler = {
    .enc_name           = "mpeg4-generic",
    .codec_type         = AVMEDIA_TYPE_AUDIO,
    .codec_id           = CODEC_ID_AAC,
    .parse_sdp_a_line   = parse_sdp_line,
    .alloc              = new_context,
    .free               = free_context,
    .parse_packet       = aac_parse_packet
};
