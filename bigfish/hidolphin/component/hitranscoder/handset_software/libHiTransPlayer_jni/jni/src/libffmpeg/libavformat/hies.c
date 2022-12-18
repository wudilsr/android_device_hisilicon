#include "libavutil/avstring.h"
#include "libavcodec/bytestream.h"
#include "libavcodec/mpeg4audio.h"
#include "avformat.h"
#include "flv.h"

#define QUIT_TIMES 1024 * 128

typedef struct
{
    double pos;
    double time;
} FLVIndexEntry;

typedef struct {
    int wrong_dts; ///< wrong dts due to negative cts
    int pos_index;
    int time_index;
    int index_num;
    int has_index;
    FLVIndexEntry * index_entry;
    int iHasFramesArray;         /*CNcomment: onMetaData中是否含有关键帧数组*/ /* having the i frame index in the MetaData */
    int64_t filesizeInMeta;       /* CNcomment: onMetaData中是否含有filesize字段*/ /* having the field of filesize in the MetaData */
} FLVContext;


//w00136937
#define HIES_AVSTREAM_INDEX_AUDIO (1)
#define HIES_AVSTREAM_INDEX_VIDEO (0)


typedef struct tagHIESContext
{
    int audioSampleRate;
    int audioChannel;
    int audioBand;
    int VideoIndex;
    int AudioIndex;
    #if 0
    char SpsBuffer[64];
    int  spsFlag;
    int  ppsFlag;
    int  spsBufferLen;
    int extraChangeFlag;
    #endif
}HIESContext;


static int HIES_probe(AVProbeData *p)
{
    #if 0
    const uint8_t *d;

    d = p->buf;
    if (d[0] == 'F' && d[1] == 'L' && d[2] == 'V' && d[3] < 5 && d[5]==0 && AV_RB32(d+5)>8) {
        return AVPROBE_SCORE_MAX;
    }
    #endif
    //av_log(s, AV_LOG_WARNING,"[%s:%d] file : %s\n", __FILE__, __LINE__,p->filename);
    if(0 != strstr(p->filename,"hisi") || 0 != strstr(p->filename,"HISI"))
    {
        return AVPROBE_SCORE_MAX;
    }
    return 0;
}

static AVStream *create_stream(AVFormatContext *s, int is_audio){
    AVStream *st = av_new_stream(s, is_audio);
    if (!st)
        return NULL;
    st->codec->codec_type = is_audio ? AVMEDIA_TYPE_AUDIO : AVMEDIA_TYPE_VIDEO;
    av_set_pts_info(st, 32, 1, 1000); /* 32 bit pts in ms */
    return st;
}

static int HIES_read_header(AVFormatContext *s,
                           AVFormatParameters *ap)
{
#if 0
    int offset, flags;
    url_fskip(s->pb, 4);
    flags = get_byte(s->pb);
    /* old flvtool cleared this field */
    /* FIXME: better fix needed */
    if (!flags) {
        flags = FLV_HEADER_FLAG_HASVIDEO | FLV_HEADER_FLAG_HASAUDIO;
        av_log(s, AV_LOG_WARNING, "Broken FLV file, which says no streams present, this might fail\n");
    }

    if((flags & (FLV_HEADER_FLAG_HASVIDEO|FLV_HEADER_FLAG_HASAUDIO))
             != (FLV_HEADER_FLAG_HASVIDEO|FLV_HEADER_FLAG_HASAUDIO))
        s->ctx_flags |= AVFMTCTX_NOHEADER;

    if(flags & FLV_HEADER_FLAG_HASVIDEO){
        if(!create_stream(s, 0))
            return AVERROR(ENOMEM);
    }
    if(flags & FLV_HEADER_FLAG_HASAUDIO){
        if(!create_stream(s, 1))
            return AVERROR(ENOMEM);
    }
    #endif
    HIESContext *hiEsContext = s->priv_data;
    if(!create_stream(s, HIES_AVSTREAM_INDEX_VIDEO))
        return AVERROR(ENOMEM);
    #if 1
    if(!create_stream(s, HIES_AVSTREAM_INDEX_AUDIO))
        return AVERROR(ENOMEM);
    #endif
    url_fseek(s->pb, 0, SEEK_SET);

    s->start_time = 0;

//    hiEsContext->extraChangeFlag = 1;
    return 0;
}

static int HIES_get_extradata(AVFormatContext *s, AVStream *st, int size)
{
    av_free(st->codec->extradata);
    st->codec->extradata = av_mallocz(size + FF_INPUT_BUFFER_PADDING_SIZE);
    if (!st->codec->extradata)
        return AVERROR(ENOMEM);
    st->codec->extradata_size = size;
    get_buffer(s->pb, st->codec->extradata, st->codec->extradata_size);
    return 0;
}


static int HIES_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    HIESContext *hiEsContext = s->priv_data;
    int ret, i, type, size, flags, is_audio;
    int64_t next, pos;
    int64_t dts, pts = AV_NOPTS_VALUE;
    AVStream *st = NULL;
    int nTime = 0;
    unsigned u32Pts;

    type = get_le32(s->pb);
    u32Pts = get_le32(s->pb);
    dts = u32Pts;
    pts = u32Pts;
    size = get_le32(s->pb);
    //av_log(s, AV_LOG_WARNING," hies packet: type %d, size %d, u32Pts %d\n", type, size, u32Pts);
    pos = url_ftell(s->pb);

    next= size + url_ftell(s->pb) + 12;
    if(type != 1 && type != 5 &&
            type != 7 && type != 8 && type != 10)
    {
        ret = AVERROR(EAGAIN);
    }
    if(size == 0)
    {
        ret = AVERROR(EAGAIN);
    }

    if (url_feof(s->pb))
    {
        av_log(s, AV_LOG_WARNING,"url_feof : error\n");
        av_log(s, AV_LOG_WARNING," error no : %d\n", AVERROR(EAGAIN));
        return AVERROR(EAGAIN);
    }

    if(type == 10)
    {
        //av_log(s, AV_LOG_WARNING,"audio current position : %lld\n",pts * 1000);
        is_audio=1;
    }else
    {
        is_audio = 0;
    }
    flags = type;
    for(i=0;i<s->nb_streams;i++) {
        st = s->streams[i];
        if (st->id == is_audio)
            break;
    }
    if(i == s->nb_streams){
        av_dlog( s,"nb_streams invalid stream\n");
        st= create_stream(s, is_audio);
        s->ctx_flags &= ~AVFMTCTX_NOHEADER;
    }
    if(  (st->discard >= AVDISCARD_NONKEY && !((flags & FLV_VIDEO_FRAMETYPE_MASK) == FLV_FRAME_KEY ||         is_audio))
       ||(st->discard >= AVDISCARD_BIDIR  &&  ((flags & FLV_VIDEO_FRAMETYPE_MASK) == FLV_FRAME_DISP_INTER && !is_audio))
       || st->discard >= AVDISCARD_ALL
       ){
        ret = AVERROR(EAGAIN);
    }
    if (flags == 10 && s->nb_streams == 1)
    {
        av_add_index_entry(st, pos, dts, size, 0, AVINDEX_KEYFRAME);
    }

    if (flags == 5)
    {

        av_add_index_entry(st, pos, dts, size, 0, AVINDEX_KEYFRAME);
    }

    s->duration = AV_NOPTS_VALUE;

    /*音频参数应该通过header的read来设置,此处写死先*/
    if(is_audio){
        if(!st->codec->channels || !st->codec->sample_rate || !st->codec->bits_per_coded_sample) {
            st->codec->channels = 2;
            st->codec->sample_rate = 48000;
            st->codec->bits_per_coded_sample = 16;
        }
        if(!st->codec->codec_id){
            st->codec->codec_id = CODEC_ID_AAC;
        }
    }else{
        st->codec->codec_id = CODEC_ID_H264;

    }
    ret= av_get_packet(s->pb, pkt, size);
    if (ret < 0) {
        av_log(s, AV_LOG_WARNING," av_get_packet size error\n");
        return AVERROR(EIO);
    }else if(ret == 0)
    {
        av_log(s, AV_LOG_WARNING," hies size %d\n", ret);
    }
    /* note: we need to modify the packet size here to handle the last
       packet */
    pkt->size = ret;
    pkt->dts = pts;
    pkt->pts = pts;
    pkt->stream_index = st->index;

    if (is_audio || flags  == 5)
        pkt->flags |= AV_PKT_FLAG_KEY;
    leave:
        return ret;
}

static int HIES_read_seek(AVFormatContext *s, int stream_index,
    int64_t ts, int flags)
{
    av_dlog( s,"~~~~~~~~~@@@@@@@@@@@@!!!!!!!!!! hies seek\n");
    /* resolving the problem of can not playing from the head of the file when replaying */
    /* CNcomment: changed:增加seek 0处理，循环不能从头开始播放 */
    #if 0
    int offset = 0, ret = 0;
    int index = 0;
    AVStream * vst = NULL;
    FLVContext *flv_context = NULL;
    int64_t pts = 0;

    if (stream_index >= s->nb_streams
        || NULL == s->priv_data)
        return -1;

    vst = s->streams[stream_index];
    flv_context = s->priv_data;

    if (0 == ts)
    {
        url_fseek(s->pb, 0, SEEK_SET);
        url_fskip(s->pb, 4);
        get_byte(s->pb);

        offset = get_be32(s->pb);
        url_fseek(s->pb, offset, SEEK_SET);
        url_fskip(s->pb, 4);
        s->start_time = 0;

        return 0;
    }
    else if (flv_context->has_index)
    {
        pts = ts * (1000 * vst->time_base.num) / vst->time_base.den; /* CNcomment: 转换成ms单位 */      /* converted into ms */
        index = av_index_search_timestamp( vst, ts, flags);

        if (index < 0)
            return av_url_read_fseek(s->pb, stream_index, pts, flags);

        url_fseek(s->pb, vst->index_entries[index].pos, SEEK_SET);

        return 0;
    }

    return av_url_read_fseek(s->pb, stream_index, ts, flags);
    #endif
    return 0;
}

static int HIES_read_close(AVFormatContext *s)
{
    av_dlog( s,"~~~~~~~~~@@@@@@@@@@@@!!!!!!!!!! hies close\n");
    return 0;
}

#if 0 /* don't know enough to implement this */
static int flv_read_seek2(AVFormatContext *s, int stream_index,
    int64_t min_ts, int64_t ts, int64_t max_ts, int flags)
{
    int ret = AVERROR(ENOSYS);

    if (ts - min_ts > (uint64_t)(max_ts - ts)) flags |= AVSEEK_FLAG_BACKWARD;

    if (url_is_streamed(s->pb)) {
        if (stream_index < 0) {
            stream_index = av_find_default_stream_index(s);
            if (stream_index < 0)
                return -1;

            /* timestamp for default must be expressed in AV_TIME_BASE units */
            ts = av_rescale_rnd(ts, 1000, AV_TIME_BASE,
                flags & AVSEEK_FLAG_BACKWARD ? AV_ROUND_DOWN : AV_ROUND_UP);
        }
        ret = av_url_read_fseek(s->pb, stream_index, ts, flags);
    }

    if (ret == AVERROR(ENOSYS))
        ret = av_seek_frame(s, stream_index, ts, flags);
    return ret;
}
#endif

AVInputFormat ff_hies_demuxer = {
    "hisi",
    NULL_IF_CONFIG_SMALL("HIES format"),
    sizeof(HIESContext),
    HIES_probe,
    HIES_read_header,
    HIES_read_packet,
    .read_seek = HIES_read_seek,
    .read_close = HIES_read_close,
#if 0
    .read_seek2 = flv_read_seek2,
#endif
    .extensions = "hisi",
    .value = CODEC_ID_HISI,
};
