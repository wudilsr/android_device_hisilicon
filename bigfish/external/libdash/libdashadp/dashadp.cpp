/*
 *
 *
 *
 *
 *
 *
 */
#include "dashadp.h"
#include "MultimediaManager.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "libavformat/avformat.h"
#include "libavformat/avio_internal.h"
#include "libavformat/isom_encryption.h"
#include "libavutil/opt.h"
#include "libavutil/base64.h"
#include "libavutil/avstring.h"
#include "hi_svr_format.h"
#include "hi_svr_subparse.h"
#ifdef PLAYREADY_SUPPORT
#include "hi_playready.h"
#include "hi_playreadyhttp.h"
#endif

using namespace std;
using namespace libdash::framework::adaptation;
using namespace libdash::framework::buffer;
using namespace sampleplayer::managers;
using namespace dash::mpd;

#define DASH_VID_EXTEND_DATA_LEN    (1024 * 1024)
#define DASH_AAC_ADTS_LEN           (7)
#define DASH_RATING_LEN             (128)
#define AV_TIME_DIFF                (1000)
#define DASH_VID_STREAM             (0x01)
#define DASH_AUD_STREAM             (0x02)
#define DASH_SUB_STREAM             (0x04)
#define DASH_ATTR_STR_LEN           (64)
#define AVIO_BUFFER_SIZE             (524288)
#define DASHIO_MAX_SIZE             (32)
#define DASH_BW_CHECK_CYCLE     (5000000)//us

#define CHECK_SUBTITLE_TYPE(VAR, TYPE) ((TYPE) & (VAR))

typedef struct uuid{
    const char* name;
    const char* uuid;
    uint8_t     system_id[16];
}UUID;

static const UUID DRMSystem[] = {
    {"PlayReady", "9a04f079-9840-4286-ab92-e65be0885f95", \
        {0x9a, 0x04, 0xf0, 0x79, 0x98, 0x40, 0x42, 0x86, 0xab, 0x92, 0xe6, 0x5b, 0xe0, 0x88, 0x5f, 0x95}},
    {"PlayReady", "79f0049a-4098-8642-ab92-e65be0885f95", \
        {0x79, 0xf0, 0x04, 0x9a, 0x40, 0x98, 0x86, 0x42, 0xab, 0x92, 0xe6, 0x5b, 0xe0, 0x88, 0x5f, 0x95}}
    /* ... */
};

typedef struct {
    uint8_t     version;
    uint32_t    flag;

    uint32_t    reference_ID;
    uint32_t    timescale;

    uint64_t    earliest_presentation_time;
    uint64_t    first_offset;

    uint16_t    reserved;
    uint16_t    reference_count;
    AVIndexEntry  *index_entries;
    int         entries_nb;
}SidxInfo;

typedef struct {
    int             mpeg_dash_stream;
    int             representation_index;
    int64_t         earliest_pts;
}Option;

typedef struct {
    char     id[DASH_ATTR_STR_LEN];
    char     bandwidth[DASH_ATTR_STR_LEN];
    char     codecs[DASH_ATTR_STR_LEN];
    int        bandwidthBps;
}DASHRepresentation;

typedef struct {
    SidxInfo *pstSidxInfo;
    HI_U8    *pstSidxData;

}DASHRepresentationIndexes;

typedef struct {
    char  lang[DASH_ATTR_STR_LEN];
    DASHRepresentation       curRepresentation;//only changed when play a new presentation
    std::vector<SidxInfo *>  representationsSidxinfo;
}DASHAdaptionSet;

typedef struct {
    char     id[DASH_ATTR_STR_LEN];
    char     start[DASH_ATTR_STR_LEN];
    char     duration[DASH_ATTR_STR_LEN];
    int64_t startMs;/*in ms*/
    int64_t durationMs;
    std::vector<DASHAdaptionSet> videoAdaptionsets;
    std::vector<DASHAdaptionSet> audioAdaptionsets;
    std::vector<DASHAdaptionSet> subtitleAdaptionsets;
}DASHPeriod;

typedef enum tagRepresentationStreamType
{
    SINGLE_MEDIA_SEGMENT,
    SEGMENT_LIST,
    SEGMENT_TEMPLATE,
    UNDEFINED
}REPRESENTATION_STREAM_TYPE;

typedef enum tagCurlStatus
{
    CURL_STATUS_INPROGRESS,
    CURL_STATUS_OK,
    CURL_STATUS_NOK,
    CURL_STATUS_BUTT
}CURL_STATUS;

typedef struct {
    CURL                        *curl_handle;
    CURLM                       *multi_handle;
    long                        httpCode;
    CURL_STATUS                 status;
    const char                               * download_Url;
    unsigned char                  *pData;
    unsigned                           size;
}CurlDataMember;

typedef enum
{
    DASHIO_EOS_NONE                     = 0, //not eos yet,
    DASHIO_EOS_PERIOD_COMPLETE,
    DASHIO_EOS_PRESENTATION_CHANGED,
    DASHIO_EOS_ERROR
}DASHIO_EOF_TYPE;

typedef  struct _DASHMember DASHMember;

typedef struct
{
    AVIOContext *libavdecoder_pb;
    AVMediaType type;
    int               adaptionset_index;
    int               representation_index;
}DASHIOMapParam;

typedef struct
{
    DASHMember *dash_member;
    DASHIO_EOF_TYPE    eos;
    int                          first_read;
    DASHIOMapParam      param;
    int                          used;
}DASHIOMap;

typedef struct
{
    DASHIOMap *maps;
    int   count;
    int   size;
} DASHIO;

#ifdef PLAYREADY_SUPPORT
typedef struct
{
    HI_PLAYREADY_Handle         hPlayReady;
    HI_U8                       *pu8PROData;
    HI_U32                      u32PROSize;
    HI_U8                       u8Kid[16];
    HI_CHAR*                    pLAURL;
    HI_FORMAT_PLAYREADY_EXTRADATA_S stPlayReadyExtraData;
}PlayReadyMember;
#endif

typedef struct _DASHMember{
    HI_VOID*                    manager;
    HI_CHAR                     filename[1024];
    HI_BOOL                     bUpdateMPD;
    AVFormatContext             *ic;
    AVFormatContext             **vid_ic;
    AVFormatContext             **aud_ic;
    AVFormatContext             **sub_ic;
    AVFormatContext             **ttml_ic;

    HI_S32                      s32PeriodNum;//period index from start playing

    HI_U32                      vid_nb;
    HI_U32                      aud_nb;
    HI_U32                      sub_nb;

    HI_S32                      vid_index;
    HI_S32                      aud_index;
    HI_S32                      sub_index;
    HI_S32                      ttml_index;

    HI_S32                      s32VideoRepresentationIndex;
    HI_S32                      s32AudioRepresentationIndex;
    HI_S32                      s32SubtitleRepresentationIndex;

    HI_S32                      s32VideoAdaptationSetIndex;
    HI_S32                      s32AudioAdaptationSetIndex;
    HI_S32                      s32SubtitleAdaptationSetIndex;

    HI_PCHAR                    rating;
    HI_S64                      s64VideoLastPts;
    HI_S64                      s64AudioLastPts;
    HI_S64                      s64SubtitleLastPts;

    //set to 0xffffffff to start play from latest segment if live, from 0 if vod;set to other to start play from the specified position
    HI_U32                      u32VideoPosition;
    HI_U32                      u32AudioPosition;
    HI_U32                      u32SubtitlePosition;

    HI_U32                      u32VideoBandWidth;
    HI_U32                      u32AudioBandWidth;
    HI_U32                      u32SubtitleBandWidth;

    HI_BOOL                     bSetupFinish;
    HI_BOOL                     bIsISOFF;
    REPRESENTATION_STREAM_TYPE  eRepresentationType;

    HI_S64                      s64VideoFirstPts;
    HI_S64                      s64AudioFirstPts;
    HI_S64                      s64SubtitleFirstPts;

    HI_BOOL                     bSeeking;
    HI_BOOL                     bStartWithSAP;

    HI_BOOL                     bVideoEosReached;
    HI_BOOL                     bAudioEosReached;
    HI_BOOL                     bSubtitleEosReached;

    HI_BOOL                     bVideoChangePresenFinish;
    HI_BOOL                     bAudioChangePresenFinish;
    HI_BOOL                     bSubtitleChangePresenFinish;

    HI_S32                      s32SubSegmentIndex;

    HI_S32                      *ps32SubtitleType;
    HI_BOOL                     bHiSubInit;
    HI_BOOL                     bFirstFrame;
    CurlDataMember           curlDataMember;
    DASHPeriod                 stCurPeriod;
    DASHIO                      stIO;
    HI_S64                       s64LastCheckBWTime;//us
    AVMediaType               eLastCheckBWType;

    HI_DASH_STREAM_INFO_S stUserSetStreamInfo;//the adaptionset index setted by user.
    pthread_mutex_t              mUserStreamInfoLock;

    ///for test
    HI_BOOL                     bForcePrint;
    HI_U32                       u32VTryRead;
    HI_U32                       u32ATryRead;
    HI_U32                       u32STryRead;
    HI_U32                       u32VReadOKCount;
    HI_U32                       u32AReadOKCount;
    HI_U32                       u32SReadOKCount;

    HI_CHAR                    *pHttpHeaders;

    HI_BOOL                     bUsingPlayReady;
#ifdef PLAYREADY_SUPPORT
    PlayReadyMember              PRMember;
#endif

}DASHMember;

typedef enum tagAAC_PROFILE_E
{
    AAC_PROFILE_MAIN = 0,
    AAC_PROFILE_LC,
    AAC_PROFILE_SSR,
    AAC_PROFILE_RESERVED,
} AAC_PROFILE_E;

typedef enum tagNALU_TYPE_H264
{
   HI_DASH_NALU_TYPE_SLICE = 1,
   HI_DASH_NALU_TYPE_DPA,
   HI_DASH_NALU_TYPE_DPB,
   HI_DASH_NALU_TYPE_DPC,
   HI_DASH_NALU_TYPE_IDR,
   HI_DASH_NALU_TYPE_SEI,
   HI_DASH_NALU_TYPE_SPS,
   HI_DASH_NALU_TYPE_PPS,
   HI_DASH_NALU_TYPE_AUD,
   HI_DASH_NALU_TYPE_EOSEQ,
   HI_DASH_NALU_TYPE_EOSTREAM,
   HI_DASH_NALU_TYPE_FILL,
   HI_DASH_NALU_TYPE_SPSEXT,
   HI_DASH_NALU_TYPE_AUX,
   HI_DASH_NALU_TYPE_EOPIC,
   HI_DASH_NALU_TYPE_TSTEND
} NALU_TYPE_H264;

typedef struct tagADTSHeader
{
    /* fixed */
    HI_U32  sync;                           /* syncword */
    HI_U8   id;                             /* MPEG bit - should be 1 */
    HI_U8   layer;                          /* MPEG layer - should be 0 */
    HI_U8   protectBit;                     /* 0 = CRC word follows, 1 = no CRC word */
    HI_U8   profile;                        /* 0 = main, 1 = LC, 2 = SSR, 3 = reserved */
    HI_U8   sampRateIdx;                    /* sample rate index range = [0, 11] */
    HI_U8   privateBit;                     /* ignore */
    HI_U8   channelConfig;                  /* 0 = implicit, >0 = use default table */
    HI_U8   origCopy;                       /* 0 = copy, 1 = original */
    HI_U8   home;                           /* ignore */

    /* variable */
    HI_U8   copyBit;                        /* 1 bit of the 72-bit copyright ID (transmitted as 1 bit per frame) */
    HI_U8   copyStart;                      /* 1 = this bit starts the 72-bit ID, 0 = it does not */
    HI_S32  frameLength;                    /* length of frame */
    HI_S32  bufferFull;                     /* number of 32-bit words left in enc buffer, 0x7FF = VBR */
    HI_U8   numRawDataBlocks;               /* number of raw data blocks in frame */

    /* CRC */
    HI_S32   crcCheckWord;                   /* 16-bit CRC check word (present if protectBit == 0) */
} ADTSHeader;


#define STRING_MATCH(str1, str2)  (!strncmp(str1, str2, (strlen(str1) > strlen(str2)?strlen(str1):strlen(str2))))


extern uint8_t* ff_mov_get_sidx_data(AVFormatContext *s);

extern int ff_index_search_timestamp(const AVIndexEntry * entries,int nb_entries,int64_t wanted_timestamp,int flags);
extern int ff_add_index_entry(AVIndexEntry **index_entries,
                       int *nb_index_entries,
                       unsigned int *index_entries_allocated_size,
                       int64_t pos, int64_t timestamp, int size, int distance, int flags);

//extern int ff_read_frame_flush(AVFormatContext * s);
extern AVInputFormat ff_ttml_demuxer;

static URLErrorCodeCB * dash_errorcode_cb = NULL;

static HI_S32 _SVR_DASH_Init(DASHMember *pstMember);
static HI_S32 _SVR_DASH_StartDownload(DASHMember *pstMember, HI_BOOL bResume, HI_BOOL bForceInvokeInit);
static HI_S32 _SVR_DASH_BuildIndex(DASHMember * pstMember, DASHPeriod *pstAttr);
static HI_S32 _SVR_DASH_DetectURL(DASHMember * pstMember, const HI_CHAR * pURL, HI_U32 u32Position);
static HI_S32 _SVR_DASH_CloseFormat(DASHMember *pstMember);
static HI_S32 _SVR_DASH_PlayPeriod(DASHMember *pstMember, IPeriod * period, HI_BOOL bNew);
static HI_S32 _SVR_DASH_PlayNextPeriod(DASHMember *pstMember);
static HI_S32 _SVR_DASH_FindCurrentPeriod(DASHMember * pstMember, IPeriod **ppstPeriod, HI_BOOL *pbChanged);
static HI_S32 _SVR_DASH_FindNextPeriod(DASHMember * pstMember, IPeriod **ppstPeriod);
static HI_BOOL  _SVR_DASH_CheckBandWidthChanged(DASHMember * pstMember, HI_BOOL bForce, AVMediaType eForceType);
static inline HI_S32 _SVR_DASH_UpdatePktPts(DASHMember * pstMember, AVPacket * pkt);
static inline HI_S32 _SVR_DASH_SelectAdaptionset(DASHMember * pstMember, AVMediaType eType);
static inline HI_S32 _SVR_DASH_SelectRepresentation(DASHMember * pstMember,
                                                    AVMediaType eType,
                                                    HI_S32 s32AdaptationSetIndex,
                                                    HI_U32 u32BandWidth);
static inline HI_BOOL _SVR_DASH_CheckSubtitleRepresentationChanged(DASHMember * pstMember,
                                              AVFormatContext **ic, HI_S32 adaptionsetIndex);
static inline  HI_BOOL _SVR_DASH_PresentationIsMatch(IRepresentation *pstRepresentation, DASHRepresentation *pstToBeMatchedAttr);
static inline int _SVR_DASH_DoReadSegment(DASHIOMap *map, uint8_t *buf, int buf_size);
static inline HI_BOOL _SVR_DASH_CheckAdaptationSetChanged(DASHMember * pstMember);
static inline HI_S32 _SVR_DASH_DoBuildIndex(AVFormatContext *ic, CurlDataMember *curlMember, SidxInfo **ppstSidxInfo);
static int _SVR_DASH_SetAllAdaptationsetsEos(DASHMember *pstMember, DASHIO_EOF_TYPE eEosType);

static HI_S32 _SVR_DASH_Get_be321(HI_U8 *pu8Data, HI_U32 *value, HI_U32 u32StartCodeLen)
{
    HI_U32 val = 0;

    if (4 == u32StartCodeLen)
    {
        val = pu8Data[0] << 24;
        val |= pu8Data[1] << 16;
        val |= pu8Data[2] << 8;
        val |= pu8Data[3];
    }
    else if (3 == u32StartCodeLen)
    {
        val = pu8Data[0] << 16;
        val |= pu8Data[1] << 8;
        val |= pu8Data[2];
    }
    else if (2 == u32StartCodeLen)
    {
        val = pu8Data[0] << 8;
        val |= pu8Data[1];
    }
    else
    {
        val = pu8Data[0];
    }

    *value = val;

    return HI_SUCCESS;
}


static HI_S32 _SVR_DASH_ParseNalInplace(HI_U8 *pu8Data, HI_U32 u32InDataLen, HI_U32 u32StartCodeLen,
    HI_U8 *pu8InBuff, HI_U32 u32InBufLen, HI_U32 *pu32OutDataLen)
{
    HI_S32 nal_num = 0;
    HI_S32 ReadLen = 0;
    HI_U8* pos = pu8Data;
    HI_U8* buf = pu8InBuff;

    if (4 == u32StartCodeLen)
    {
        if (0x00 == pu8Data[0] && 0x00 == pu8Data[1] && 0x00 == pu8Data[2] && 0x01 == pu8Data[3])
        {
            /* not need parse nal */
            return HI_SUCCESS;
        }
    }
    else if (3 == u32StartCodeLen || 2 == u32StartCodeLen)
    {
        /* if start code = 0x00000001, the start code len is wrong */

        if ((0x00 == pu8Data[0] && 0x00 == pu8Data[1] && 0x01 == pu8Data[2])
            || (0x00 == pu8Data[0] && 0x00 == pu8Data[1] && 0x00 == pu8Data[2] && 0x01 == pu8Data[3]))
        {
            /* not need parse nal */
            return HI_SUCCESS;
        }
    }

    HI_U32 u32RealOutLen = 0;

    while (u32InDataLen > u32StartCodeLen && pos < (pu8Data + u32InDataLen - u32StartCodeLen))
    {
        _SVR_DASH_Get_be321(pos,(HI_U32*)&ReadLen, u32StartCodeLen);

        if (ReadLen > ((pu8Data + u32InDataLen) - (pos + u32StartCodeLen)) || ReadLen < 0)
            break;

        if (4 == u32StartCodeLen)
        {
            pos[0]= 0x00;
            pos[1]= 0x00;
            pos[2]= 0x00;
            pos[3]= 0x01;
            pos += (ReadLen + 4);
        }
        else if (3 == u32StartCodeLen)
        {
            pos[0]= 0x00;
            pos[1]= 0x00;
            pos[2]= 0x01;
            pos += (ReadLen + 3);
        }
        else
        {
            if (u32RealOutLen + ReadLen + 3 >= u32InBufLen)
            {
                //FORMAT_PRINT("vid frame data erro, len is large than 3m \n");
                break;
            }

            buf[0] = 0x00;
            buf[1] = 0x00;
            buf[2] = 0x01;

            memcpy(buf + 3, pos + u32StartCodeLen, ReadLen);
            u32RealOutLen += (ReadLen + 3);
            buf += (ReadLen + 3);
            pos += (ReadLen + u32StartCodeLen);

            if ((HI_U32)(pu8Data + u32InDataLen - pos) <= u32StartCodeLen
                && (u32InBufLen - u32RealOutLen) > u32StartCodeLen)
            {
                memcpy(buf, pos, (pu8Data + u32InDataLen - pos));
                u32RealOutLen += (pu8Data + u32InDataLen - pos);
                pos = pu8Data + u32InDataLen;
                break;
            }
        }

        nal_num++;
    }

    if ((4 == u32StartCodeLen) || (3 == u32StartCodeLen))
    {
    }
    else
    {
        *pu32OutDataLen = u32RealOutLen;
    }

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_GetH264SpsPps(HI_U8 *pu8ExtraData, HI_U32 u32ExtraDataLen,
    HI_U8 *pu8InBuff, HI_U32 u32InBufLen, HI_U32*pu32OutLen)
{
    HI_U32 startcode_len = 0, unit_size = 0;
    HI_U8 num_unit = 0, sps_done = 0;
    static const HI_U8 nalu_header3[3] = {0, 0, 1};
    static const HI_U8 nalu_header4[4] = {0, 0, 0, 1};
    const HI_U8 *extradata = NULL;
    const HI_U8 *nalu_header = NULL;

    if (NULL == pu8ExtraData  || NULL == pu8InBuff || u32ExtraDataLen < 5)
    {
        return HI_FAILURE;
    }

    startcode_len = (pu8ExtraData[4] & 0x3) + 1;

    /* extra data is sps and pps data, not need parse, copy it to inbuff and return */

    if (((0x00 == pu8ExtraData[0] && 0x00 == pu8ExtraData[1] && 0x00 == pu8ExtraData[2] && 0x01 == pu8ExtraData[3])
            && 4 == startcode_len)
        || (((0x00 == pu8ExtraData[0] && 0x00 == pu8ExtraData[1] && 0x01 == pu8ExtraData[2])
            || (0x00 == pu8ExtraData[0] && 0x00 == pu8ExtraData[1] && 0x00 == pu8ExtraData[2] && 0x01 == pu8ExtraData[3]))
            && (3 == startcode_len || 2 == startcode_len)))
    {
        if (u32InBufLen >= u32ExtraDataLen)
        {
            memcpy(pu8InBuff, pu8ExtraData, u32ExtraDataLen);
            *pu32OutLen = u32ExtraDataLen;

            return HI_SUCCESS;
        }
    }

    if (3 == startcode_len)
    {
        nalu_header = nalu_header3;
    }
    else
    {
        nalu_header = nalu_header4;
        startcode_len = 4;
    }

    *pu32OutLen = 0;
    extradata = pu8ExtraData + 5;
    /* number of sps unit(s) */

    num_unit = *extradata++ & 0x1f;

    if (!num_unit)
    {
        /* number of pps unit(s) */
        num_unit = *extradata++;
        sps_done++;
    }

    while (num_unit--)
    {
        unit_size = (*extradata) << 8 | extradata[1];
        *pu32OutLen += unit_size + startcode_len;

        if ((extradata+2+unit_size > pu8ExtraData + u32ExtraDataLen)
            ||(*pu32OutLen > u32InBufLen))
        {
            return HI_FAILURE;
        }

        memcpy(pu8InBuff + *pu32OutLen - unit_size - startcode_len, nalu_header, startcode_len);
        memcpy(pu8InBuff + *pu32OutLen - unit_size, extradata + 2, unit_size);
        extradata += 2 + unit_size;

        if (!num_unit && !sps_done++)
        {
            /* number of pps unit(s) */
            num_unit = *extradata++;
        }
    }

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_QuickSearchStartCode( HI_U8* pCode, HI_S32 CodeLen)
{
    HI_U8 *ptr,*pEnd,byte;
    HI_S32  ofst;

    if (CodeLen<5)
    {
        /*! if stream data less than 5, do not use this algorithm */
        return -1;
    }

    pEnd = pCode + CodeLen;

    for ( ptr=pCode+2; ptr<pEnd; )
    {
        byte = ptr[0];

        if ( (byte >1) )
        {
            ptr += 3;
            continue;
        }
        else if ( byte==0x00 )
        {
            if ( ptr[-1] == 0x00 )
            {
                ptr += 1;
                continue;
            }
            else if ( ptr[1] == 0x00 )
            {
                ptr += 2;
                continue;
            }
            else
            {
                ptr+=4;
                continue;
            }
        }
        else if ( byte == 0x01 )
        {
            if ( ptr[-2]==0x00 && ptr[-1]==0x00 )
            {
                ofst = (HI_S32)(ptr - pCode - 2);
                return ofst;
            }
            else
            {
                ptr+=3;
                continue;
            }
        }
    }

    return -1;
}

static HI_S32 _SVR_DASH_GetH264StartCodeLen(HI_U8 *pu8ExtraData, HI_U32 u32ExtraDataLen, HI_U32 *pu32StartCodeLen)
{
    if (NULL == pu8ExtraData || u32ExtraDataLen < 5 || NULL == pu32StartCodeLen)
    {
        return HI_FAILURE;
    }

    *pu32StartCodeLen = (pu8ExtraData[4] & 0x3) + 1;

    if (*pu32StartCodeLen < 2)
    {
        //dash_log("start code len erro, start code len = %d \n", *pu32StartCodeLen);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID _SVR_DASH_GetADTSHeader(HI_S32 sampleRateidx,             /*!< aacPlus sampling frequency (incl. SBR) */
                            HI_S32     frameLength,            /*!< raw data length */
                            HI_S32     profile,                /* 0 = main, 1 = LC, 2 = SSR, 3 = reserved */
                            HI_S32     ch,
                            HI_U8      *pADTSHeadBuf)
{
    HI_S32  head0 = 0, head1 = 0;
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

static HI_S32 _SVR_DASH_GetBits(const HI_U8 *pBuf, HI_U32 u32ByteOffset, HI_U32 u32Startbit, HI_U32 u32Bitlen)
{
    HI_U8   *b = NULL;
    HI_U32   v = HI_FAILURE;
    HI_U32   mask = 0;
    HI_U32   tmp_long = 0;
    HI_U32   bitHigh = 0;
    HI_U32   offset = 0;

    if (u32Bitlen > 32)
    {
        return HI_FAILURE;
    }

    if (pBuf == NULL)
    {
        return HI_FAILURE;
    }

    b = (HI_U8*)&pBuf[u32ByteOffset + (u32Startbit >> 3)];

    u32Startbit %= 8;

    if ((HI_U32)0  == u32Bitlen )
    {
        return HI_FAILURE;
    }

    offset = (u32Bitlen-1) >> 3;

    switch (offset)
    {
    case 0:             /*-- 1..8 bit*/
        tmp_long = (HI_U32)((*(b)<< 8) + *(b+1));
        bitHigh = 16;
        break;

    case 1:             /* -- 9..16 bit*/
        tmp_long = (HI_U32)((*(b)<<16) + (*(b+1)<< 8) + *(b+2));
        bitHigh = 24;
        break;

    case 2:             /*-- 17..24 bit*/
        tmp_long = (HI_U32)((*(b)<<24) + (*(b+1)<<16) + (*(b+2)<< 8) + *(b+3));
        bitHigh = 32;
        break;

    case 3:             /* -- 25..32 bit*/
        tmp_long = (HI_U32)(((HI_U32)(*(b))<<32)+((HI_U32)(*(b+1 ))<<24) + ((HI_U32)(*(b+2))<<16)
            + ((HI_U32)(*(b+3))<<8) + (HI_U32)(*(b+4)));
        bitHigh = 40;
        break;

    default:    /* -- 33.. bits: fail, deliver constant fail value*/
        return HI_FAILURE;
    }

    u32Startbit = bitHigh - (u32Startbit + u32Bitlen);
    tmp_long = tmp_long >> u32Startbit;

    if (u32Bitlen == 32 )
    {
        mask = 0xFFFFFFFF;
    }
    else
    {
        mask = (((HI_U32)0x00000001) << u32Bitlen) - 1;
    }

    v= tmp_long & mask;

    return v;
}

static HI_S32 _SVR_DASH_DecAdtsExtradata(HI_U8 *pu8Buf, HI_U32 u32Size, HI_U32 *pu32SampleRateIdx,
    HI_U32 *pu32Profile, HI_U32 *pu32Channel)
{
    HI_U32 u32SampleRateIdx = 0, u32Profile = 0, u32Channel = 0;

    if (NULL == pu8Buf || u32Size < 2)
    {
        return HI_FAILURE;
    }

    u32Profile = _SVR_DASH_GetBits(pu8Buf, 0, 0, 5) - 1;
    u32SampleRateIdx = _SVR_DASH_GetBits(pu8Buf, 0, 5, 4);
    u32Channel = _SVR_DASH_GetBits(pu8Buf, 0, 9, 4);

    if (u32Profile > 3U)
    {
        //av_log(NULL, AV_LOG_ERROR, "MPEG-4 AOT %d is not allowed in ADTS\n", u32Profile + 1);
        //return HI_FAILURE;
    }

    if (u32SampleRateIdx == 15)
    {
        //av_log(NULL, AV_LOG_ERROR, "Escape sample rate index illegal in ADTS\n");
        //return HI_FAILURE;
    }

    if (_SVR_DASH_GetBits(pu8Buf, 0, 13, 1))
    {
        //av_log(NULL, AV_LOG_ERROR, "960/120 MDCT window is not allowed in ADTS\n");
        //return HI_FAILURE;
    }

    if (_SVR_DASH_GetBits(pu8Buf, 0, 14, 1))
    {
        //av_log(NULL, AV_LOG_ERROR, "Scalable configurations are not allowed in ADTS\n");
        //return HI_FAILURE;
    }

    if (_SVR_DASH_GetBits(pu8Buf, 0, 15, 1))
    {
        //av_log(NULL, AV_LOG_ERROR, "Signaled SBR or PS \n");
        //return HI_FAILURE;
    }

    *pu32SampleRateIdx = u32SampleRateIdx;
    *pu32Profile = u32Profile;
    *pu32Channel = u32Channel;

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_AddExtraData(CodecID u32Format, AVStream *st, AVFormatContext *ic, AVPacket* pkt)
{
    HI_U32 u32ExtraDataSize = 0;
    HI_U32 u32StartcodeLen = 0;
    HI_U32 u32Offset = 0, u32TotalOffset = 0;
    HI_U32 u32SpsPpsLen = 0;
    HI_U32 u32SampleRateIdx = 3, u32Channel = 2, u32Profile = AAC_PROFILE_LC;
    HI_U8 *pu8AExtraData = NULL, *pu8Temp = NULL;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 *pu8VidData = NULL;
    HI_U32 u32FrameHeaderLen = 0;
    HI_BOOL bKeyFrame = HI_FALSE;
    HI_BOOL bSPSnotEqual = HI_FALSE;
    HI_U8 *pu8PktData = NULL;

    pu8VidData = (HI_U8 *)av_mallocz(DASH_VID_EXTEND_DATA_LEN);

    if (NULL == pu8VidData)
        return AVERROR(ENOMEM);

    if (CODEC_ID_H264 == u32Format)
    {
        u32ExtraDataSize = st->codec->extradata_size;
        pu8AExtraData = st->codec->extradata;

        s32Ret = _SVR_DASH_GetH264StartCodeLen(pu8AExtraData, u32ExtraDataSize, &u32StartcodeLen);
        bKeyFrame = ((AV_PKT_FLAG_KEY & pkt->flags) == AV_PKT_FLAG_KEY) ? HI_TRUE : HI_FALSE;
        while (HI_TRUE == bKeyFrame)
        {
            u32Offset = _SVR_DASH_QuickSearchStartCode((HI_U8*)(pkt->data + u32TotalOffset),
            pkt->size - u32TotalOffset);

                u32TotalOffset += (u32Offset + 3);

                if ((pkt->size - u32TotalOffset < 5) || (-1 == (HI_S32)u32Offset))
                {
                    break;
                }

                pu8Temp = (HI_U8*)(pkt->data) + u32TotalOffset;

                if ((pu8Temp[0] & 0x1F) == HI_DASH_NALU_TYPE_SPS)
                {
                    bSPSnotEqual = HI_TRUE;
                    break;
                }
        }

        u32SpsPpsLen = 0;

        if (HI_TRUE == bKeyFrame
            && NULL != pu8AExtraData
            && u32ExtraDataSize < DASH_VID_EXTEND_DATA_LEN)
        {
            _SVR_DASH_GetH264SpsPps(pu8AExtraData, u32ExtraDataSize,
                pu8VidData, DASH_VID_EXTEND_DATA_LEN, &u32SpsPpsLen);
        }

        _SVR_DASH_ParseNalInplace(pkt->data, pkt->size,
            u32StartcodeLen, pu8VidData + u32SpsPpsLen,
            DASH_VID_EXTEND_DATA_LEN - u32SpsPpsLen, &u32FrameHeaderLen);

        if (!u32FrameHeaderLen)
        {
            if (u32SpsPpsLen)
            {
                pu8PktData = (HI_U8 *)av_realloc(pkt->data, pkt->size + u32SpsPpsLen);
                if (NULL == pu8PktData)
                {
                    av_free(pu8VidData);
                    pu8VidData = NULL;
                    return AVERROR(ENOMEM);
                }

                pkt->data = pu8PktData;
                memmove(pkt->data + u32SpsPpsLen, pkt->data, pkt->size);
                memcpy(pkt->data, pu8VidData, u32SpsPpsLen);
                pkt->size = pkt->size + u32SpsPpsLen;
            }
        }
        else
        {
            pu8PktData = (HI_U8 *)av_realloc(pkt->data, pkt->size + u32FrameHeaderLen + u32SpsPpsLen);
            if (NULL == pu8PktData)
            {
                av_free(pu8VidData);
                pu8VidData = NULL;
                return AVERROR(ENOMEM);
            }

            pkt->data = pu8PktData;
            memmove(pkt->data +u32FrameHeaderLen + u32SpsPpsLen, pkt->data, pkt->size);
            memcpy(pkt->data, pu8VidData, u32FrameHeaderLen + u32SpsPpsLen);
            pkt->size = pkt->size + u32FrameHeaderLen + u32SpsPpsLen;
        }
    }

    if (CODEC_ID_AAC == u32Format)
    {
        u32ExtraDataSize = st->codec->extradata_size;
        pu8AExtraData = st->codec->extradata;

        if (NULL != pu8AExtraData)
        {
            _SVR_DASH_DecAdtsExtradata(pu8AExtraData, u32ExtraDataSize, &u32SampleRateIdx, &u32Profile, &u32Channel);
            _SVR_DASH_GetADTSHeader(u32SampleRateIdx, pkt->size, u32Profile, u32Channel, pu8VidData);

            HI_U8  u8ADTSHeader[DASH_AAC_ADTS_LEN] = {0};
            HI_U32 u32AssumedProfile = 0x03&((pkt->data[2])>>6);//assume had header
            HI_U32 s32HasADTS = 0;

            _SVR_DASH_GetADTSHeader(u32SampleRateIdx, (pkt->size - DASH_AAC_ADTS_LEN),
                u32AssumedProfile, u32Channel, u8ADTSHeader);

            if (0 == memcmp(u8ADTSHeader,pkt->data, DASH_AAC_ADTS_LEN))
            {
                s32HasADTS = 1;
            }
            else
            {
                HI_U8  u8FirstFrameADTSHeader[DASH_AAC_ADTS_LEN] = {0};

                memcpy(u8FirstFrameADTSHeader, pkt->data, DASH_AAC_ADTS_LEN);

                HI_U16 len_part1 = u8FirstFrameADTSHeader[3] & 0x0003;
                HI_U16 len_part2 = u8FirstFrameADTSHeader[4] & 0x00ff;
                HI_U16 len_part3 = u8FirstFrameADTSHeader[5] & 0x00e0;
                HI_U32 FirstFrameLen = (len_part1 << 11) | (len_part2 << 3) | (len_part3 >> 5);

                memset(u8ADTSHeader, 0, DASH_AAC_ADTS_LEN);
                _SVR_DASH_GetADTSHeader(u32SampleRateIdx, (FirstFrameLen - DASH_AAC_ADTS_LEN),
                    u32AssumedProfile, u32Channel, u8ADTSHeader);

                if (0 == memcmp(u8ADTSHeader, u8FirstFrameADTSHeader, DASH_AAC_ADTS_LEN))
                {
                    s32HasADTS = 1;
                }
            }

            if ( 0 == s32HasADTS ) //if audio data hasn't ADTS header, add it
            {
                if (pkt->size < DASH_VID_EXTEND_DATA_LEN - DASH_AAC_ADTS_LEN)
                {
                    pu8PktData = (HI_U8 *)av_realloc(pkt->data,pkt->size + DASH_AAC_ADTS_LEN);
                    if (NULL == pu8PktData)
                    {
                        av_free(pu8VidData);
                        pu8VidData = NULL;
                        return AVERROR(ENOMEM);
                    }

                    pkt->data = pu8PktData;
                    memmove(pkt->data + DASH_AAC_ADTS_LEN, pkt->data, pkt->size);
                    memcpy(pkt->data, pu8VidData, DASH_AAC_ADTS_LEN);
                }

                pkt->size = pkt->size + DASH_AAC_ADTS_LEN;
            }

        }
    }

    if (NULL != pu8VidData)
    {
        av_free(pu8VidData);
        pu8VidData = NULL;
    }

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_GetStreamCodec(AVFormatContext *ic,
    HI_S32 s32StreamIdx, AVMediaType *peDataType, CodecID *pu32Codec)
{
    HI_U32 i = 0;
    AVStream * st = HI_NULL;

    for (i = 0; i < ic->nb_streams; i ++)
    {
        st = ic->streams[i];
        if (s32StreamIdx == st->index)
        {
            *peDataType = st->codec->codec_type;
            *pu32Codec  = st->codec->codec_id;
        }
    }
    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_GetStreamIndex(AVFormatContext *ic,
    AVMediaType eDataType, HI_S32 *ps32StreamIdx)
{
    HI_U32 i = 0;
    AVStream * st = HI_NULL;

    for (i = 0; i < ic->nb_streams; i ++)
    {
        st = ic->streams[i];
        if (st->codec->codec_type == eDataType)
        {
            *ps32StreamIdx = st->index;
        }
    }
    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_CopyStream(AVStream * to, AVStream * from)
{
    to->r_frame_rate    = from->r_frame_rate;
    to->time_base       = from->time_base;
    to->id              = from->id;
    if (to->metadata != NULL)
    {
        av_dict_free(&to->metadata);
    }
    to->metadata        = from->metadata;
    to->duration        = from->duration;
//  to->start_time      = from->start_time;    //some file starttime is not 0,after cacaulating pts,starttime is larger than current pts. It makes current progress up to 99%.
    to->need_parsing    = AVSTREAM_PARSE_NONE;
    to->request_probe   = 0;
    to->start_time      = 0;//make sure all streams start from 0
    to->discard         = from->discard;

    if (to->parser != NULL)
    {
        av_parser_close(to->parser);
        av_free_packet(&to->cur_pkt);
        to->parser          = NULL;
    }
    if (to->info)   to->info->duration_count = 20;      //Do not need to re-parse
//  to->first_dts    = from->first_dts;                 //Do not need to re-parse

    from->index = to->index;            //re-new stream index
    from->metadata = NULL;
    avcodec_copy_context(to->codec, from->codec);
    to->codec->bit_rate = from->codec->bit_rate;

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_FreeMasterStream(DASHMember * pstMember)
{
    HI_U32 i = 0;
    AVStream * st = NULL;

    if (pstMember->ic == NULL)
        return HI_FAILURE;

    for(i = 0;i < pstMember->ic->nb_streams; i++)
    {
        /* free all data in a stream component */
        st = pstMember->ic->streams[i];
        if (st->parser) {
            av_parser_close(st->parser);
            av_free_packet(&st->cur_pkt);
        }
        av_dict_free(&st->metadata);
        av_freep(&st->index_entries);
        av_freep(&st->codec->extradata);
        av_freep(&st->codec->subtitle_header);
        av_freep(&st->codec);
        av_freep(&st->priv_data);
        av_freep(&st->info);
        av_freep(&st->probe_data.buf);
        av_freep(&st);
    }

    if (pstMember->ic->streams)
        av_freep(&pstMember->ic->streams);
    pstMember->ic->nb_streams = 0;

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASHIO_Add(DASHMember *pstMember, DASHIOMapParam *param, DASHIOMap **map)
{
    DASHIO *io = &pstMember->stIO;
    DASHIOMap *maps = NULL;
    HI_S32        i;

    *map = NULL;

    if (io->size <= 0)
    {
        //can't use realloc to extend the size here, the addr of maps may be changed.
        maps = (DASHIOMap *)av_mallocz(DASHIO_MAX_SIZE * sizeof(DASHIOMap));
        if (maps == NULL)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] fatal error, realloc for maps failed\n", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }
        io->maps = maps;
        io->size   = DASHIO_MAX_SIZE;
        for (i = 0; i < io->size; i++)
        {
            io->maps[i].dash_member = NULL;
            io->maps[i].eos = DASHIO_EOS_NONE;
            io->maps[i].first_read = 1;
            io->maps[i].used = 0;
            //memset((void *)(&io->maps[i].param), 0, sizeof(io->maps[i].param));
        }
    }

    if (io->count >= io->size)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] fatal error, can't find empty map\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    for (i = 0; i < io->size; i++)
    {
        if (io->maps[i].used == 0)
        {
            io->maps[i].used = 1;
            io->maps[i].dash_member = pstMember;
            io->maps[i].eos = DASHIO_EOS_NONE;
            io->maps[i].first_read = 1;
            memcpy((void *)(&io->maps[i].param), param, sizeof(io->maps[i].param));
            io->count ++;
            *map = &(io->maps[i]);
            dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] add map success ,map[%d]=%p, pb=%p, type=%d, adaptionset_index=%d, rep_index=%d, total count:%d\n",
                __FUNCTION__, __LINE__,  i, &(io->maps[i]), param->libavdecoder_pb, param->type, param->adaptionset_index, param->representation_index, io->count);
            return HI_SUCCESS;
        }
    }

    /*never go to below*/
    dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] fatal error, can't find empty map\n", __FUNCTION__, __LINE__);

    return HI_FAILURE;
}

static HI_S32 _SVR_DASHIO_Remove(DASHMember *pstMember, DASHIOMap *map)
{
    DASHIO *io = &pstMember->stIO;
    HI_S32        i;

    if (map != NULL)
    {
        for (i = 0; i < io->size; i++)
        {
            if (&io->maps[i] == map)
            {
                io->count --;
                dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] remove map success ,map[%d]=%p, pb=%p, type=%d, adaptionset_index=%d, total count:%d\n",
                __FUNCTION__, __LINE__,  i, &(io->maps[i]), map->param.libavdecoder_pb, map->param.type, map->param.adaptionset_index, io->count);
                io->maps[i].dash_member = NULL;
                io->maps[i].eos = DASHIO_EOS_NONE;
                io->maps[i].first_read = 1;
                memset((void *)(&io->maps[i].param), 0, sizeof(io->maps[i].param));
                io->maps[i].used = 0;
                return HI_SUCCESS;
            }
        }
    }

    dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] warning, no map matched for %p,maps count:%d\n", __FUNCTION__, __LINE__, map, io->count);

    return HI_FAILURE;
}

static HI_S32 _SVR_DASHIO_Update(DASHMember *pstMember)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    AVIOContext *pb;
    DASHIOMap  *map;
    HI_S32 i;

    dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] start to update avio\n", __FUNCTION__, __LINE__);

    if (pstMember->vid_ic != NULL)
    {
        for (i = 0; i < pstMember->vid_nb; i++)
        {
            pb    = (AVIOContext *)manager->GetVideoAVIOContext(i);
            map = (DASHIOMap *)pstMember->vid_ic[i]->pb->opaque;
            map->param.libavdecoder_pb = pb;
            //dash_log("[%s,%d][DASHIO] video[%d] map=%p, pb=%p, buf=%p\n", __FUNCTION__, __LINE__, i, map, pb, pstMember->vid_ic[i]->pb->buffer);
        }
    }

    if (pstMember->aud_ic != NULL)
    {
        for (i = 0; i < pstMember->aud_nb; i++)
        {
            pb    = (AVIOContext *)manager->GetAudioAVIOContext(i);
            map = (DASHIOMap *)pstMember->aud_ic[i]->pb->opaque;
            map->param.libavdecoder_pb = pb;
            //dash_log("[%s,%d][DASHIO] audio[%d] map=%p, pb=%p, buf=%p\n", __FUNCTION__, __LINE__, i, map, pb, pstMember->aud_ic[i]->pb->buffer);
        }
    }

    if (pstMember->sub_ic != NULL)
    {
        for (i = 0; i < pstMember->sub_nb; i++)
        {
            pb    = (AVIOContext *)manager->GetSubtitleAVIOContext(i);
            map = (DASHIOMap *)pstMember->sub_ic[i]->pb->opaque;
            map->param.libavdecoder_pb = pb;
        }
    }
    dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] update avio done.\n", __FUNCTION__, __LINE__);

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASHIO_FreeAll(DASHMember *pstMember)
{
    DASHIO *io = &pstMember->stIO;

    dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] free all.\n", __FUNCTION__, __LINE__);
    if (io->maps)
    {
        av_free(io->maps);
        io->maps = NULL;
        io->count = 0;
        io->size = 0;
    }

    return HI_SUCCESS;
}

static HI_BOOL _SVR_DASH_DoUpdateMPD(DASHMember *pstMember, HI_BOOL bResume, HI_BOOL bForceUpdate)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    MultimediaManager *manager_new;
    void *breakpoint = NULL;
    int err = 0;
    HI_U32 u32FetchTime = manager->GetFetchTime();
    HI_U32 u32CurrentTime = manager->GetCurrentTime();
    HI_U32 u32CheckTime = manager->GetCheckTime();

    if (HI_FALSE == bForceUpdate &&
        (u32FetchTime >= u32CheckTime || u32CurrentTime < u32CheckTime))
    {
        return HI_FALSE;
    }

    dash_log(DASH_LOG_INFO, "[%s,%d] u32FetchTime:%u, u32CurrentTime:%u, u32CheckTime:%u\n",
        __FUNCTION__, __LINE__, u32FetchTime, u32CurrentTime, u32CheckTime);
    dash_log(DASH_LOG_ERROR, "[%s,%d] start to update MPD...bResume:%d, bForceUpdate:%d\n", __FUNCTION__, __LINE__, bResume, bForceUpdate);

    /*update bw before pause manager*/
    pstMember->u32VideoBandWidth = manager->GetVideoBandWidth();
    pstMember->u32AudioBandWidth = manager->GetAudioBandWidth();
    pstMember->u32SubtitleBandWidth = manager->GetSubtitleBandWidth();

    if (bResume)
    {
        breakpoint = manager->Pause();
        dash_log(DASH_LOG_ERROR, "[%s,%d] get dash download breakpoint done %p\n", __FUNCTION__, __LINE__, breakpoint);
    }

    pstMember->manager = new MultimediaManager(breakpoint);
    if (pstMember->manager == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to malloc new MultimediaManager\n", __FUNCTION__, __LINE__);
        pstMember->manager = manager;
        manager->Resume(breakpoint);
        return HI_FALSE;
    }

    manager_new = (MultimediaManager *)pstMember->manager;
    if (pstMember->pHttpHeaders != NULL)
    {
        manager_new->Invoke(MANAGER_INVOKE_SET_HTTP_HEADERS, (void *) pstMember->pHttpHeaders);
    }
    if (true != manager_new->Init(pstMember->filename, &err))
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] fail to init new MultimediaManager\n", __FUNCTION__, __LINE__);
        pstMember->manager = manager;
        manager->Resume(breakpoint);
        return HI_FALSE;
    }

    if (manager_new->IsLive() &&
        strlen(manager_new->GetMPD()->GetMinimumUpdatePeriod().c_str()) > 0)
    {
        pstMember->bUpdateMPD = HI_TRUE;
    }
    else
    {
        pstMember->bUpdateMPD = HI_FALSE;
    }

    delete manager;

    dash_log(DASH_LOG_ERROR, "[%s,%d] update MPD done, bUpdateMPD:%d\n", __FUNCTION__, __LINE__, pstMember->bUpdateMPD);

    return HI_TRUE;
}

static int _SVR_DASH_UpdateMPD(DASHMember *pstMember, HI_BOOL bResume, HI_BOOL bForceUpdate)
{
    HI_BOOL bPeriodChanged = HI_FALSE, bUpdated = HI_FALSE;
    IPeriod *period = NULL;

    if (pstMember->bUpdateMPD == HI_FALSE ||  pstMember->bSetupFinish == HI_FALSE)
        return HI_SUCCESS;

    bUpdated = _SVR_DASH_DoUpdateMPD(pstMember, bResume, bForceUpdate);
    if (bUpdated == HI_TRUE)
    {
        bPeriodChanged = HI_FALSE;
        _SVR_DASH_FindCurrentPeriod(pstMember, &period, &bPeriodChanged);
        if (period == NULL || bPeriodChanged == HI_TRUE)
        {
            _SVR_DASH_SetAllAdaptationsetsEos(pstMember, DASHIO_EOS_PERIOD_COMPLETE);
            dash_log(DASH_LOG_ERROR, "[%s,%d][MPD] error:fail to find current period @id='%s', @start='%s', @duration='%s'\n",
                __FUNCTION__, __LINE__,  pstMember->stCurPeriod.id, pstMember->stCurPeriod.start, pstMember->stCurPeriod.duration);
            return HI_FAILURE;
        }

        if (_SVR_DASH_PlayPeriod(pstMember, period, bPeriodChanged) != HI_SUCCESS)
        {
            _SVR_DASH_SetAllAdaptationsetsEos(pstMember, DASHIO_EOS_PERIOD_COMPLETE);
            dash_log(DASH_LOG_ERROR, "[%s,%d][MPD] error:fail to play current period @id='%s', @start='%s', @duration='%s'\n",
                __FUNCTION__, __LINE__,  pstMember->stCurPeriod.id, pstMember->stCurPeriod.start, pstMember->stCurPeriod.duration);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

static int _SVR_DASH_HandleEvent(DASHIOMap *map, int event)
{
    int eventType = (event & LOGIC_EVENT_MASK);

    switch(eventType)
    {
        case LOGIC_EVENT_PRE_INITSEGMENT:
            {
                DASHMember *pstMember = map->dash_member;
                MultimediaManager *manager = (MultimediaManager *)(map->dash_member->manager);
                IAdaptationSet *adaptionset = NULL;
                IRepresentation *representation = NULL;
                unsigned bw = 0;
                int toRepresentationIndex = map->param.representation_index;
                int i;
                double maxPlayoutRate = 0;
                PresentationInfo_s eventData;

                if (map->first_read == 0)
                {
                    toRepresentationIndex = (event & LOGIC_EVENT_DATA_MASK);
                }
                if (map->param.type == AVMEDIA_TYPE_VIDEO)
                {
                    adaptionset = manager->GetVideoAdaptionSet(map->param.adaptionset_index);
                }
                else if (map->param.type == AVMEDIA_TYPE_AUDIO)
                {
                    adaptionset = manager->GetAudioAdaptionSet(map->param.adaptionset_index);
                }
                else if (map->param.type == AVMEDIA_TYPE_SUBTITLE)
                {
                    adaptionset = manager->GetSubtitleAdaptionSet(map->param.adaptionset_index);
                }

                if (adaptionset != NULL)
                {
                    if (toRepresentationIndex >= 0 &&
                        toRepresentationIndex < adaptionset->GetRepresentation().size())
                    {
                        representation = adaptionset->GetRepresentation().at(toRepresentationIndex);
                        if (representation != NULL)
                        {
                            maxPlayoutRate = representation->GetMaxPlayoutRate();
                            bw = representation->GetBandwidth();
                        }
                        #if 1//just for HBBTV @maxPlayoutRate testcase temporarily
                         for (i = 0; i <  adaptionset->GetRepresentation().size(); i ++)
                         {
                            representation = adaptionset->GetRepresentation().at(i);
                            if (representation != NULL)
                            {
                                if (maxPlayoutRate < representation->GetMaxPlayoutRate())
                                {
                                    maxPlayoutRate = representation->GetMaxPlayoutRate();
                                }
                            }
                         }
                        #endif
                    }

                    if (maxPlayoutRate < 1.0)//no value in representattion, get from adaptionset
                        maxPlayoutRate = adaptionset->GetMaxPlayoutRate();
                }
                if (maxPlayoutRate < 1.0)
                    maxPlayoutRate = 1;
                dash_log(DASH_LOG_ERROR, "[%s,%d][READ][EVENT] map[%p] type=%d, adaptionset_index=%d, rep_index=%d,  pb=%p, init event recevied, first_read=%d(if 0 return EOS), maxPlayoutRate:%llf\n",
                    __FUNCTION__, __LINE__, map, map->param.type, map->param.adaptionset_index, map->param.representation_index, map->param.libavdecoder_pb, map->first_read, maxPlayoutRate);
                snprintf(eventData.dmx_name, sizeof(eventData.dmx_name), "libdash");
                eventData.stream_index = map->param.adaptionset_index;
                eventData.presentation_type = map->param.type;
                eventData.presentation_index = toRepresentationIndex;
                eventData.bandwidth = bw;
                eventData.maxPlayoutRate = maxPlayoutRate;
                dash_errorcode_cb(map->dash_member->ic->interrupt_callback.opaque, AVEVENT_PRESENTATION_CHANGED, (char *)&eventData);
                if (map->first_read == 0)
                {
                    map->eos = DASHIO_EOS_PRESENTATION_CHANGED;
                    map->param.representation_index = toRepresentationIndex;
                    return AVERROR_EOF;
                }
           }
            break;
        case LOGIC_EVENT_EOS:
            map->eos = DASHIO_EOS_PERIOD_COMPLETE;
            dash_log(DASH_LOG_ERROR, "[%s,%d][READ][EVENT] map[%p] type=%d, adaptionset_index=%d, rep_index=%d,  pb=%p, eos event recevied!\n",
                __FUNCTION__, __LINE__, map, map->param.type, map->param.adaptionset_index, map->param.representation_index, map->param.libavdecoder_pb);
            return AVERROR_EOF;
        case LOGIC_EVENT_ERROR:
            {
                int errType, errCode;

                map->eos = DASHIO_EOS_ERROR;
                errType = ((event & LOGIC_ERROR_TYPE_MASK) >> 16);
                errCode = (event & LOGIC_ERROR_CODE_MASK);
                if ((event & LOGIC_ERROR_TYPE_MASK) == LOGIC_ERROR_TYPE_HTTP)
                {
                    dash_errorcode_cb(map->dash_member->ic->interrupt_callback.opaque, errCode, "http");
                }
                else if ((event & LOGIC_ERROR_TYPE_MASK) == LOGIC_ERROR_TYPE_STREAM_NOTAVAILABLE)
                {
                    dash_errorcode_cb(map->dash_member->ic->interrupt_callback.opaque, AVEVENT_STREAM_NOT_AVAIABLE, "libdash");
                }
                dash_log(DASH_LOG_ERROR, "[%s,%d][READ][EVENT] map[%p] type=%d, adaptionset_index=%d, rep_index=%d,  pb=%p, error(type:%d, code:%d) recevied!\n",
                    __FUNCTION__, __LINE__, map, map->param.type, map->param.adaptionset_index,
                    map->param.representation_index, map->param.libavdecoder_pb, errType, errCode);
            }
            return AVERROR_EOF;
        default:
            dash_log(DASH_LOG_ERROR, "[%s,%d][READ][EVENT] map[%p] type=%d, adaptionset_index=%d, rep_index=%d,  pb=%p, unknow event recevied!\n",
                __FUNCTION__, __LINE__, map, map->param.type, map->param.adaptionset_index, map->param.representation_index, map->param.libavdecoder_pb);
    }

    return 0;
}

static inline int _SVR_DASH_DoReadSegment(DASHIOMap *map, uint8_t *buf, int buf_size)
{
    DASHMember *pstMember = map->dash_member;
    MultimediaManager *manager = (MultimediaManager *)(map->dash_member->manager);
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Position, u32Position1;
    HI_U64 u64SegEndTimeMS = 0;

    switch(map->param.type)
    {
        case AVMEDIA_TYPE_VIDEO:
            u32Position = manager->GetVideoPosition(map->param.adaptionset_index);
            u64SegEndTimeMS = manager->GetVideoSegmentEndTime(map->param.adaptionset_index, u32Position);
            break;
        case AVMEDIA_TYPE_AUDIO:
            u32Position = manager->GetAudioPosition(map->param.adaptionset_index);
            u64SegEndTimeMS = manager->GetAudioSegmentEndTime(map->param.adaptionset_index, u32Position);
            break;
        case AVMEDIA_TYPE_SUBTITLE:
            u32Position = manager->GetSubtitlePosition(map->param.adaptionset_index);
            u64SegEndTimeMS = manager->GetSubtitleSegmentEndTime(map->param.adaptionset_index, u32Position);
        default:
            u32Position = 0;
    }

    s32Ret = map->param.libavdecoder_pb->read_packet(map->param.libavdecoder_pb->opaque, buf, buf_size);

    //must clear all events first
    while ((s32Ret & LOGIC_EVENT_MASK) != 0)
    {
        s32Ret = _SVR_DASH_HandleEvent(map, s32Ret);
        if (s32Ret < 0)
            return s32Ret;

        s32Ret = map->param.libavdecoder_pb->read_packet(map->param.libavdecoder_pb->opaque, buf, buf_size);
    }
    switch(map->param.type)
    {
        case AVMEDIA_TYPE_VIDEO:
            u32Position1 = manager->GetVideoPosition(map->param.adaptionset_index);
            break;
        case AVMEDIA_TYPE_AUDIO:
            u32Position1 = manager->GetAudioPosition(map->param.adaptionset_index);
            break;
        case AVMEDIA_TYPE_SUBTITLE:
            u32Position1 = manager->GetSubtitlePosition(map->param.adaptionset_index);
            break;
        default:
            u32Position1 = 0;
    }

    if (u32Position1 >= 1 + u32Position)//segment read complete
    {
        if ((u64SegEndTimeMS >= pstMember->stCurPeriod.durationMs && pstMember->stCurPeriod.durationMs > 0) ||
            (manager->GetDuration() > 0 && (manager->GetDuration()/1000 -  pstMember->stCurPeriod.startMs <= u64SegEndTimeMS)))
        {
            map->eos = DASHIO_EOS_PERIOD_COMPLETE;
            dash_log(DASH_LOG_ERROR, "[%s,%d][READ] map[%p] type=%d, adaptionset_index=%d, current period complete, set eos. file dur=%lld, period @id='%s', @start='%s', @duration='%s'(%lld), u64SegEndTimeMS=%llu\n",
                __FUNCTION__, __LINE__, map, map->param.type, map->param.adaptionset_index, manager->GetDuration(), pstMember->stCurPeriod.id, pstMember->stCurPeriod.start,
                pstMember->stCurPeriod.duration, pstMember->stCurPeriod.durationMs, u64SegEndTimeMS);
        }
    }

    if (s32Ret < 0)
        s32Ret = 0;

    return s32Ret;
}

static int _SVR_DASH_SetAllAdaptationsetsEos(DASHMember *pstMember, DASHIO_EOF_TYPE eEosType)
{
    int i;
    DASHIOMap *map = NULL;

    if (pstMember->vid_ic != NULL)
    {
        for (i = 0; i < pstMember->vid_nb; i++)
        {
            if (pstMember->vid_ic[i] != NULL  && pstMember->vid_ic[i]->pb != NULL &&
                pstMember->vid_ic[i]->pb->opaque != NULL)
            {
                map = (DASHIOMap *)pstMember->vid_ic[i]->pb->opaque;
                map->eos = eEosType;
            }
        }
    }

    if (pstMember->aud_ic != NULL)
    {
        for (i = 0; i < pstMember->aud_nb; i++)
        {
            if (pstMember->aud_ic[i] != NULL  && pstMember->aud_ic[i]->pb != NULL &&
                pstMember->aud_ic[i]->pb->opaque != NULL)
            {
                map = (DASHIOMap *)pstMember->aud_ic[i]->pb->opaque;
                map->eos = eEosType;
            }
        }
    }

    if (pstMember->sub_ic != NULL)
    {
        for (i = 0; i < pstMember->sub_nb; i++)
        {
            if (pstMember->sub_ic[i] != NULL  && pstMember->sub_ic[i]->pb != NULL &&
                pstMember->sub_ic[i]->pb->opaque != NULL)
            {
                map = (DASHIOMap *)pstMember->sub_ic[i]->pb->opaque;
                map->eos = eEosType;
            }
        }
    }

    return HI_SUCCESS;
}

static int _SVR_DASH_ReadSegment(void *opaque, uint8_t *buf, int buf_size)
{
    DASHIOMap *map = (DASHIOMap *)opaque;
    DASHMember *pstMember = map->dash_member;
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    HI_S32 s32Ret = HI_FAILURE;
    //HI_U32 u32UpdatePeriod;
    //int64_t time_loaded;
    //int64_t time_now;

    if (map == NULL || map->dash_member == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] fatal error, map is invalid\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    if (map->eos != DASHIO_EOS_NONE)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] map [%p], pb:%p, type:%d, adapset:%d reached eos %d!\n",
            __FUNCTION__, __LINE__, map, map->param.libavdecoder_pb, map->param.type, map->param.adaptionset_index, map->eos);
        return AVERROR_EOF;
    }

    if (map->param.libavdecoder_pb && map->param.libavdecoder_pb->read_packet)
    {
        s32Ret = _SVR_DASH_DoReadSegment(map, buf, buf_size);
        if (s32Ret < 0)
            return s32Ret;
        else if (s32Ret > 0)
            map->first_read = 0;
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][DASHIO] map[%p]invalid libavdecoder_pb:%p\n", __FUNCTION__, __LINE__, map->param.libavdecoder_pb);
        return HI_FAILURE;
    }
#if 0

    u32UpdatePeriod = libdash::framework::mpd::TimeResolver::GetDurationInSec(manager->GetMPD()->GetMinimumUpdatePeriod());
    if (u32UpdatePeriod <= 0)
        u32UpdatePeriod = 15;//15 seconds for 16 audio adaptsets testcase//6


    if (pstMember->bUpdateMPD && pstMember->bSetupFinish == HI_TRUE)
    {
        if (HI_SUCCESS != _SVR_DASH_UpdateMPD(pstMember, HI_TRUE, HI_FALSE))
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d][READ] map[%p] type=%d, adaptionset_index=%d, update mpd return error....\n",
                __FUNCTION__, __LINE__, map, map->param.type, map->param.adaptionset_index);
            map->first_read = 0;
            return s32Ret;
        }
        manager = (MultimediaManager *)pstMember->manager;
    }
#endif

    //may be download not finished
    if ( s32Ret <= 0 && map->eos == DASHIO_EOS_NONE)
    {
        //time_loaded = av_gettime();
        s32Ret = _SVR_DASH_DoReadSegment(map, buf, buf_size);

        while(s32Ret == 0)
        {
            if (pstMember->ic->interrupt_callback.callback(pstMember->ic->interrupt_callback.opaque) != 0)
            {
                map->first_read = 0;
                dash_log(DASH_LOG_ERROR, "[%s,%d][READ] map[%p] type=%d, adaptionset_index=%d, user interrupted\n",
                    __FUNCTION__, __LINE__, map, map->param.type, map->param.adaptionset_index);
                return AVERROR_EOF;
            }

            if (pstMember->bUpdateMPD && pstMember->bSetupFinish == HI_TRUE)
            {
                //may be leads to exit blocked for 15s when downloading mpd timeout.
                if (HI_SUCCESS != _SVR_DASH_UpdateMPD(pstMember, HI_TRUE, HI_FALSE))
                {
                    dash_log(DASH_LOG_ERROR, "[%s,%d][READ] map[%p] type=%d, adaptionset_index=%d, update return error!!!!\n",
                        __FUNCTION__, __LINE__, map, map->param.type, map->param.adaptionset_index);
                    map->first_read = 0;
                    return s32Ret;
                }
                manager = (MultimediaManager *)pstMember->manager;
            }
#if 0
            time_now = av_gettime();
            if (time_now >= time_loaded + u32UpdatePeriod*2000000UL)
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d][READ] map[%p] type=%d, adaptionset_index=%d, read timeout!\n",
                    __FUNCTION__, __LINE__, map, map->param.type, map->param.adaptionset_index);
                break;
            }
            else
#endif
            {
                usleep(20000);
                s32Ret = _SVR_DASH_DoReadSegment(map, buf, buf_size);
            }
        }
    }

    if (s32Ret != 0 && map->first_read != 0)
        map->first_read = 0;

    return s32Ret;
}

static int _SVR_DASH_ReadSegmentWrap(void *opaque, uint8_t *buf, int buf_size)
{
    int ret;
    DASHIOMap *map = (DASHIOMap *)opaque;

   // dash_log(DASH_LOG_INFO, "map[%p] type %d adapt[%d], represent[%d] read start\n", map, map->param.type, map->param.adaptionset_index, map->param.representation_index);
    ret = _SVR_DASH_ReadSegment(opaque, buf, buf_size);
  //  dash_log(DASH_LOG_INFO, "map[%p] type %d adapt[%d], represent[%d] read return %d\n",
   //    map, map->param.type, map->param.adaptionset_index, map->param.representation_index, ret);

    return ret;
}

static HI_S32 _SVR_DASH_SetMetaData(MultimediaManager *manager,
    AVFormatContext *ic, AVMediaType eType, HI_S32 s32AdaptionSetIndex, HI_S32 s32RepresentationIndex)
{
    int i, j, count;
    IDescriptor *decriptor;
    IAdaptationSet *adaptionset;
    char str_value[1024];
    HI_U32 value;

    if (manager->IsISOFF() == HI_FALSE)
    {
        //TODO:not complete.
        return HI_FAILURE;
    }

    if (eType == AVMEDIA_TYPE_AUDIO)
    {
        adaptionset = manager->GetAudioAdaptionSet(s32AdaptionSetIndex);
    }
    else if (eType == AVMEDIA_TYPE_VIDEO)
    {
        adaptionset = manager->GetVideoAdaptionSet(s32AdaptionSetIndex);
    }
    else if (eType == AVMEDIA_TYPE_SUBTITLE)
    {
        adaptionset = manager->GetSubtitleAdaptionSet(s32AdaptionSetIndex);
    }
    else
    {
        return HI_FAILURE;
    }

    //set Language
    for (i = 0; i < ic->nb_streams; i++)
    {
        if (adaptionset->GetLang().length() > 0)
        {
            av_dict_set(&(ic->streams[i]->metadata), "language",adaptionset->GetLang().c_str(), 0);
        }
    }

    //set Role
    value = (HI_FORMAT_ROLE_SCHEME_NONE | HI_FORMAT_ROLE_VALUE_NONE);
    count = adaptionset->GetRole().size();
    for (j = 0; j < count; j++)
    {
        decriptor = adaptionset->GetRole().at(j);
        if (0 == av_strcmp(decriptor->GetSchemeIdUri().c_str(), "urn:mpeg:dash:role:2011"))
        {
            value = (value | HI_FORMAT_ROLE_SCHEME_URN_MPEG_DASH_2011);
            if (0 == av_strcmp(decriptor->GetValue().c_str(), "main"))
            {
                value = (value | HI_FORMAT_ROLE_VALUE_MAIN);
            }
            else if (0 == av_strcmp(decriptor->GetValue().c_str(), "alternate"))
            {
                value = (value | HI_FORMAT_ROLE_VALUE_ALTERNATE);
            }
            else if (0 == av_strcmp(decriptor->GetValue().c_str(), "commentary"))
            {
                value = (value | HI_FORMAT_ROLE_VALUE_COMMENTARY);
            }
            else if (0 == av_strcmp(decriptor->GetValue().c_str(), "supplementary"))
            {
                value = (value | HI_FORMAT_ROLE_VALUE_SUPPLEMENTARY);
            }
            else if (0 == av_strcmp(decriptor->GetValue().c_str(), "dub"))
            {
                value = (value | HI_FORMAT_ROLE_VALUE_DUB);
            }
            else if (0 == av_strcmp(decriptor->GetValue().c_str(), "caption"))
            {
                value = (value | HI_FORMAT_ROLE_VALUE_CAPTION);
            }
            else if (0 == av_strcmp(decriptor->GetValue().c_str(), "subtitle"))
            {
                value = (value | HI_FORMAT_ROLE_VALUE_SUBTITLE);
            }
            else
            {
                dash_log(DASH_LOG_WARNING, "[%s,%d][SETUP] unsupported @Role value:%s\n",
                    __FUNCTION__, __LINE__, decriptor->GetValue().c_str());
                continue;
            }
        }
        else
        {
                dash_log(DASH_LOG_WARNING, "[%s,%d][SETUP] unsupported @Role scheme:%s\n",
                    __FUNCTION__, __LINE__, decriptor->GetSchemeIdUri().c_str());
        }
    }

    snprintf(str_value, sizeof(str_value), "%u", value);
    dash_log(DASH_LOG_INFO, "[%s,%d][SETUP] set @Role=%#x \n", __FUNCTION__, __LINE__, value);
    for (i = 0; i < ic->nb_streams; i++)
    {
        av_dict_set(&(ic->streams[i]->metadata), "Role", str_value, 0);
    }


    //set Accessibility
    value = (HI_FORMAT_ACCESSIBILITY_SCHEME_NONE | 0);
    count = adaptionset->GetAccessibility().size();
    for (j = 0; j < count; j++)
    {
        decriptor = adaptionset->GetAccessibility().at(j);
        if (0 == av_strcmp(decriptor->GetSchemeIdUri().c_str(), "urn:tva:metadata:cs:AudioPurposeCS:2007"))
        {
            value |= HI_FORMAT_ACCESSIBILITY_SCHEME_TVA_AUDIO_PURPOSE_CS_2007;
            i = atoi(decriptor->GetValue().c_str());
            i &= HI_FORMAT_DESCRIPTOR_VALUE_MASK;
            value |= i;
        }
        else
        {
                dash_log(DASH_LOG_WARNING, "[%s,%d][SETUP] unsupported @Accessibility scheme:%s\n",
                    __FUNCTION__, __LINE__, decriptor->GetSchemeIdUri().c_str());
        }
    }

    snprintf(str_value, sizeof(str_value), "%u", value);
    dash_log(DASH_LOG_INFO, "[%s,%d][SETUP] set @Accessibility=%#x \n", __FUNCTION__, __LINE__, value);
    for (i = 0; i < ic->nb_streams; i++)
    {
        av_dict_set(&(ic->streams[i]->metadata), "Accessibility", str_value, 0);
    }

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_SetupContext(DASHMember *pstMember, AVFormatContext **sub,
    AVInputFormat * fmt, AVIOContext * pb, Option *pstOption, HI_BOOL bExternDemux,
    AVMediaType type, HI_S32 s32AdaptionSetIndex, HI_S32 s32RepresentationIndex)
{
    AVFormatContext *master = pstMember->ic;
    AVIOContext *adp_pb = NULL;
    HI_BOOL bUpdate = HI_FALSE;
    HI_S32 s32StreamIndex = -1;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i = 0;
    AVStream * st = HI_NULL;
    AVFormatContext * tmp = HI_NULL;
    AVDictionary *dict = HI_NULL;
    std::stringstream ss;
    std::string s;
    DASHIOMap *map = NULL;
    unsigned char *buffer = NULL;
    DASHIOMapParam mapParam;

    if (HI_NULL == pb)
    {
        dash_log(DASH_LOG_ERROR, "Can not get pb from libdash!\n");
        return HI_FAILURE;
    }

    if (HI_NULL != pstOption)
    {
        ss << pstOption->mpeg_dash_stream;
        ss >> s;
        av_dict_set(&dict, "mpeg_dash_stream", s.c_str(), 0);
        ss.clear();
        //ss.str("");


        ss << pstOption->representation_index;
        ss >> s;
        av_dict_set(&dict, "representation_index", s.c_str(), 0);
        ss.clear();
        //ss.str("");

        ss << pstOption->earliest_pts;
        ss >> s;
        av_dict_set(&dict, "earliest_pts", s.c_str(), 0);
        ss.clear();
        //ss.str("");
    }

    //Use this option to avoid searching ADTS header, which generated by dash
    //Some other info can be read from MPD files
    av_dict_set(&dict, "quick_switch", "1", 0);

    dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP]setup %d start with s32AdaptionSetIndex %d representation_index:%d , earliest_pts:%lld\n",
        __FUNCTION__, __LINE__, type, s32AdaptionSetIndex, s32RepresentationIndex, (pstOption != NULL?pstOption->earliest_pts:-1));

    if ((*sub))
    {
        bUpdate = HI_TRUE;
        tmp = (*sub);
    }

    mapParam.adaptionset_index = s32AdaptionSetIndex;
    mapParam.type = type;
    mapParam.libavdecoder_pb = pb;
    mapParam.representation_index = s32RepresentationIndex;
    _SVR_DASHIO_Add(pstMember, &mapParam, &map);
    if (map == NULL)
    {
        av_dict_free(&dict);
        return HI_FAILURE;
    }
  //  dash_log("[%s,%d] map %p, with pb %p \n", __FUNCTION__, __LINE__, map, pb);

    buffer = (unsigned char *)av_malloc(AVIO_BUFFER_SIZE);
    if (buffer == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] malloc fail \n", __FUNCTION__, __LINE__);
        av_dict_free(&dict);
        _SVR_DASHIO_Remove(pstMember, map);
        return HI_FAILURE;
    }
    (*sub) = avformat_alloc_context();
    if (*sub == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] malloc fail \n", __FUNCTION__, __LINE__);
      //  av_dict_free(&dict);
        av_free(buffer);
        _SVR_DASHIO_Remove(pstMember, map);
        s32Ret = HI_FAILURE;
        goto rett;
    }
    (*sub)->pb =  avio_alloc_context(buffer, AVIO_BUFFER_SIZE, 0, map, _SVR_DASH_ReadSegmentWrap, NULL, NULL);
    if ((*sub)->pb == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] malloc fail \n", __FUNCTION__, __LINE__);
       // av_dict_free(&dict);
        av_free(buffer);
        _SVR_DASHIO_Remove(pstMember, map);
        s32Ret = HI_FAILURE;
        goto rett;
    }
    (*sub)->pb->seekable = 0;
    (*sub)->pb->force_seek = 1;
    (*sub)->interrupt_callback.callback = master->interrupt_callback.callback;
    (*sub)->interrupt_callback.opaque = master->interrupt_callback.opaque;


    dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] avformat_open_input start ...\n", __FUNCTION__, __LINE__);
    s32Ret = avformat_open_input(sub ,"", fmt, &dict);
    if (s32Ret < 0)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] avformat_open_input error:%d\n", __FUNCTION__, __LINE__, s32Ret);
        //av_dict_free(&dict);
        _SVR_DASHIO_Remove(pstMember, map);
        goto rett;
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] avformat_open_input success:%d\n", __FUNCTION__, __LINE__, s32Ret);
    }

    dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] avformat_find_stream_info start ...\n", __FUNCTION__, __LINE__);
    s32Ret = avformat_find_stream_info(*sub, &dict);
    if (s32Ret < 0)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] avformat_find_stream_info error\n", __FUNCTION__, __LINE__);
       // av_dict_free(&dict);
        _SVR_DASHIO_Remove(pstMember, map);
        goto rett;
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] avformat_find_stream_info success:%d\n", __FUNCTION__, __LINE__, s32Ret);
    }

    if (HI_TRUE == bExternDemux)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] use external demux \n", __FUNCTION__, __LINE__);
        //av_dict_free(&dict);
        //return HI_SUCCESS;
        s32Ret = HI_SUCCESS;
        goto rett;
    }

    if (!*sub || !(*sub)->nb_streams)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] error, no streams.\n", __FUNCTION__, __LINE__);
       // av_dict_free(&dict);
        _SVR_DASHIO_Remove(pstMember, map);
       // return HI_FAILURE;
        s32Ret = HI_FAILURE;
        goto rett;
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP] %d streams found\n", __FUNCTION__, __LINE__, (*sub)->nb_streams);
    }

    //manager may be updated during _SVR_DASH_ReadPacket, must update it when refer to it.
    _SVR_DASH_SetMetaData((MultimediaManager *)pstMember->manager, (*sub), type, s32AdaptionSetIndex, s32RepresentationIndex);

    for (i = 0; i < (*sub)->nb_streams; i++)
    {
        if (bUpdate)
        {
            s32StreamIndex = tmp->streams[i]->index;
            st = master->streams[s32StreamIndex];
        }
        else
            st = avformat_new_stream(master, NULL);

        _SVR_DASH_CopyStream(st, (*sub)->streams[i]);
    }

    s32Ret = HI_SUCCESS;

rett:
    av_dict_free(&dict);
    if (bUpdate)
    {
        _SVR_DASHIO_Remove(pstMember, (DASHIOMap *)tmp->pb->opaque);
        adp_pb = tmp->pb;
        adp_pb->opaque = NULL;
        avformat_close_input(&tmp);
        avio_close(adp_pb);
    }

    if (HI_SUCCESS == s32Ret)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP]setup %d success with s32AdaptionSetIndex %d representation_index:%d, new ic:%p, bUpdate:%d\n",
            __FUNCTION__, __LINE__, type, s32AdaptionSetIndex, s32RepresentationIndex, (*sub), bUpdate);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SETUP]setup %d error with s32AdaptionSetIndex %d representation_index:%d, new ic:%p, bUpdate:%d\n",
            __FUNCTION__, __LINE__, type, s32AdaptionSetIndex, s32RepresentationIndex, (*sub), bUpdate);
    }

    return s32Ret;
}

static HI_S32 _SVR_DASH_Setup(DASHMember *pstMember)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    AVIOContext *pb = NULL;
    AVInputFormat * fmt = NULL;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 i = 0;
    HI_S32 s32RepresentationIndex = 0;

    if (HI_TRUE != pstMember->bSetupFinish)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] vid_nb:%u, aud_nb:%u, sub_nb:%u \n", __FUNCTION__, __LINE__, pstMember->vid_nb, pstMember->aud_nb, pstMember->sub_nb);
        dash_log(DASH_LOG_ERROR, "[%s,%d] _SVR_DASH_Setup for video.... s64VideoFirstPts:%lld, s64VideoLastPts:%lld\n", __FUNCTION__, __LINE__, pstMember->s64VideoFirstPts, pstMember->s64VideoLastPts);
        if (pstMember->vid_nb > 0)
        {
            HI_S64 s64EarlistPts = ((pstMember->s64VideoLastPts > pstMember->s64VideoFirstPts) && \
                (pstMember->s64VideoFirstPts >= 0))?(pstMember->s64VideoLastPts - pstMember->s64VideoFirstPts):0;
            Option stOption = {1, 0, s64EarlistPts};

            if (NULL == pstMember->vid_ic)
                pstMember->vid_ic = (AVFormatContext **)av_mallocz(pstMember->vid_nb * sizeof(*pstMember->vid_ic));

            for (i = 0; i < pstMember->vid_nb; i++)
            {
                manager = (MultimediaManager *)pstMember->manager;
                pb = (AVIOContext *)manager->GetVideoAVIOContext(i);
                if (i == pstMember->s32VideoAdaptationSetIndex)
                {
                    stOption.representation_index = pstMember->s32VideoRepresentationIndex;
                    s32RepresentationIndex = pstMember->s32VideoRepresentationIndex;
                }
                else
                {
                    s32RepresentationIndex = _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_VIDEO, i, 0);
                }

                s32Ret = _SVR_DASH_SetupContext(pstMember, &(pstMember->vid_ic[i]), NULL,
                    pb, &stOption, HI_FALSE, AVMEDIA_TYPE_VIDEO, i, s32RepresentationIndex);
                if (HI_FAILURE == s32Ret)
                {
                    dash_log(DASH_LOG_ERROR, "[%s,%d] _SVR_DASH_Setup for video fail.\n", __FUNCTION__, __LINE__);
                    return s32Ret;
                }
            }
        }
        dash_log(DASH_LOG_ERROR, "[%s,%d]:_SVR_DASH_Setup for audio.... s64AudioFirstPts:%lld, s64AudioLastPts:%lld\n", __FUNCTION__, __LINE__, pstMember->s64AudioFirstPts, pstMember->s64AudioLastPts);

        if (pstMember->aud_nb > 0)
        {
            HI_S64 s64EarlistPts = ((pstMember->s64AudioLastPts > pstMember->s64AudioFirstPts) && \
                (pstMember->s64AudioFirstPts >= 0))?(pstMember->s64AudioLastPts - pstMember->s64AudioFirstPts):0;
            Option stOption = {1, 0, s64EarlistPts};

            if (NULL == pstMember->aud_ic)
                pstMember->aud_ic = (AVFormatContext **)av_mallocz(pstMember->aud_nb * sizeof(*pstMember->aud_ic));

            for (i = 0; i < pstMember->aud_nb; i++)
            {
                manager = (MultimediaManager *)pstMember->manager;
                pb = (AVIOContext *)manager->GetAudioAVIOContext(i);
                if (i == pstMember->s32AudioAdaptationSetIndex)
                {
                    stOption.representation_index = pstMember->s32AudioRepresentationIndex;
                    s32RepresentationIndex = pstMember->s32AudioRepresentationIndex;
                }
                else
                {
                    s32RepresentationIndex = _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_AUDIO, i, 0);
                }

                s32Ret = _SVR_DASH_SetupContext(pstMember, &(pstMember->aud_ic[i]), NULL,
                    pb, &stOption, HI_FALSE, AVMEDIA_TYPE_AUDIO, i, s32RepresentationIndex);
                if (HI_FAILURE == s32Ret)
                {
                    dash_log(DASH_LOG_ERROR, "[%s,%d] _SVR_DASH_Setup for audio fail.\n", __FUNCTION__, __LINE__);
                    return s32Ret;
                }
            }
        }
        dash_log(DASH_LOG_ERROR, "[%s,%d] _SVR_DASH_Setup for sub.... s64SubtitleFirstPts:%lld, s64SubtitleLastPts:%lld\n", __FUNCTION__, __LINE__, pstMember->s64SubtitleFirstPts, pstMember->s64SubtitleLastPts);

        if (pstMember->sub_nb > 0)
        {
            HI_S64 s64EarlistPts = ((pstMember->s64SubtitleLastPts > pstMember->s64SubtitleFirstPts) && \
                (pstMember->s64SubtitleFirstPts >= 0))?(pstMember->s64SubtitleLastPts - pstMember->s64SubtitleFirstPts):0;
            Option stOption = {0, 0, s64EarlistPts};

            if (NULL == pstMember->sub_ic)
                pstMember->sub_ic = (AVFormatContext **)av_mallocz(pstMember->sub_nb * sizeof(*pstMember->sub_ic));
            if (NULL == pstMember->ttml_ic)
                pstMember->ttml_ic = (AVFormatContext **)av_mallocz(pstMember->sub_nb * sizeof(*pstMember->ttml_ic));
            if (NULL == pstMember->ps32SubtitleType)
                pstMember->ps32SubtitleType = (HI_S32 *)av_mallocz(pstMember->sub_nb * sizeof(HI_S32));

            for (i = 0; i < pstMember->sub_nb; i++)
            {
                manager = (MultimediaManager *)pstMember->manager;
                pb = (AVIOContext *)manager->GetSubtitleAVIOContext(i);
                pstMember->ps32SubtitleType[i] = manager->GetSubtitleType(i);
                HI_BOOL bExternDemux = HI_FALSE;

                if (CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType[i], Subtitle_ISO_Mask))
                {
                    if (i == pstMember->s32SubtitleAdaptationSetIndex)
                    {
                        stOption.representation_index = pstMember->s32SubtitleRepresentationIndex;
                        s32RepresentationIndex =  pstMember->s32SubtitleRepresentationIndex;
                    }
                    else
                    {
                        s32RepresentationIndex = _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_SUBTITLE, i, 0);
                    }

                    s32Ret = _SVR_DASH_SetupContext(pstMember, &(pstMember->sub_ic[i]), NULL, pb,
                        &stOption, HI_FALSE, AVMEDIA_TYPE_SUBTITLE, i, s32RepresentationIndex);
                    if (HI_FAILURE == s32Ret)
                    {
                        dash_log(DASH_LOG_ERROR, "[%s,%d] _SVR_DASH_Setup for subtitle fail.\n", __FUNCTION__, __LINE__);
                        return s32Ret;
                    }

                    bExternDemux = HI_TRUE;
                    pb = NULL;
                }

                #if defined (HISUB_SUPPORT)
                if (CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType[i], Subtitle_TTML) && (HI_TRUE == pstMember->bHiSubInit))
                {
                    fmt = &ff_ttml_demuxer;
                    s32Ret = _SVR_DASH_SetupContext(pstMember, &(pstMember->ttml_ic[i]), fmt,
                        pb, NULL, bExternDemux, AVMEDIA_TYPE_SUBTITLE, i, 0);
                    if (HI_FAILURE == s32Ret)
                        return s32Ret;
                }
                else
                #endif
                if (CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType[i], Subtitle_TX3G))
                {
                    //do nothing
                    s32Ret = HI_SUCCESS;
                }
                /*
                else if (CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType, Subtitle_WEBVTT))
                {
                    //not supprot yet
                    s32Ret = HI_SUCCESS;
                }
                else if (CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType[i], Subtitle_CC))
                {
                    //not supprot yet
                    s32Ret = HI_SUCCESS;
                }
                */
                else
                {
                    dash_log(DASH_LOG_ERROR, "dash unsupproted subtitle!\n");
                    i--;
                    pstMember->sub_nb--;
                    s32Ret = HI_SUCCESS;
                }
            }
        }
    }

    pstMember->u32VideoPosition = ((MultimediaManager *)pstMember->manager)->GetVideoPosition();
    pstMember->u32AudioPosition = ((MultimediaManager *)pstMember->manager)->GetAudioPosition();
    pstMember->u32SubtitlePosition = ((MultimediaManager *)pstMember->manager)->GetSubtitlePosition();

    return HI_SUCCESS;
}

static HI_S32 _SVR_CHECK_StreamType(DASHMember * pstMember)
{
    HI_S32 s32StreamType = 0;
    if (pstMember->vid_nb)
        s32StreamType = DASH_VID_STREAM;

    if (pstMember->aud_nb)
        s32StreamType |= DASH_AUD_STREAM;

    if (pstMember->sub_nb)
        s32StreamType |= DASH_SUB_STREAM;

    return s32StreamType;
}

static HI_S32 _SVR_DASH_CheckIndexChanged(SidxInfo * pSidxInfo, HI_S64 s64NewPts, HI_S64 s64OldPts, HI_S32 * ps32SugSegmentIndex)
{
    HI_U32 i = 0;
    HI_S32 s32NewIndex = -1;
    HI_S32 s32OldIndex = -1;

    if (NULL == pSidxInfo)
        return HI_FAILURE;

    for (i = 0; i < pSidxInfo->entries_nb; i++)
    {
        if (s64NewPts >= pSidxInfo->index_entries[i].timestamp)
            s32NewIndex = i;

        if (s64OldPts >= pSidxInfo->index_entries[i].timestamp)
            s32OldIndex = i;
    }

    if (s32NewIndex > s32OldIndex && s32OldIndex >= 0 && s32NewIndex > *ps32SugSegmentIndex)
    {
        *ps32SugSegmentIndex = s32NewIndex;
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

static inline HI_S32 _SVR_DASH_SelectRepresentation(DASHMember * pstMember,
                                                                                      AVMediaType eType,
                                                                                      HI_S32 s32AdaptationSetIndex,
                                                                                      HI_U32 u32BandWidth)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    IAdaptationSet *adaptionset = NULL;
    HI_S32 s32RepresentationIndex    = 0;

     switch(eType)
    {
        case AVMEDIA_TYPE_VIDEO:
            s32RepresentationIndex = manager->CheckVideoCurrentIndex(u32BandWidth);
            if (s32RepresentationIndex < 0)
            {
                adaptionset = manager->GetVideoAdaptionSet(s32AdaptationSetIndex);
                if (adaptionset != NULL &&
                    adaptionset->GetRepresentation().size() > pstMember->s32VideoRepresentationIndex &&
                    pstMember->s32VideoRepresentationIndex >= 0)
                {
                    s32RepresentationIndex = pstMember->s32VideoRepresentationIndex;
                }
                else
                {
                    s32RepresentationIndex = 0;
                }
            }
            break;
        case AVMEDIA_TYPE_AUDIO:
             s32RepresentationIndex = manager->CheckAudioCurrentIndex(u32BandWidth);
             if (s32RepresentationIndex < 0)
             {
                adaptionset = manager->GetAudioAdaptionSet(s32AdaptationSetIndex);
                if (adaptionset != NULL &&
                    adaptionset->GetRepresentation().size() > pstMember->s32AudioRepresentationIndex &&
                    pstMember->s32AudioRepresentationIndex >= 0)
                {
                    s32RepresentationIndex = pstMember->s32AudioRepresentationIndex;
                }
                else
                {
                    s32RepresentationIndex = 0;
                }
             }
            break;
        case AVMEDIA_TYPE_SUBTITLE:
            s32RepresentationIndex = manager->CheckSubtitleCurrentIndex(u32BandWidth);
             if (s32RepresentationIndex < 0)
             {
                adaptionset = manager->GetSubtitleAdaptionSet(s32AdaptationSetIndex);
                if (adaptionset != NULL &&
                    adaptionset->GetRepresentation().size() > pstMember->s32SubtitleRepresentationIndex &&
                    pstMember->s32SubtitleRepresentationIndex >= 0)
                {
                    s32RepresentationIndex = pstMember->s32SubtitleRepresentationIndex;
                }
                else
                {
                    s32RepresentationIndex = 0;
                }
             }
            break;
    }

    return s32RepresentationIndex;
}

static inline  HI_BOOL _SVR_DASH_PresentationIsMatch(IRepresentation *pstRepresentation, DASHRepresentation *pstToBeMatchedAttr)
{
    HI_BOOL bMatched = HI_FALSE;
    HI_S32   s32Len;
    HI_U32   u32BandWidth;
    char     id[DASH_ATTR_STR_LEN];

    snprintf(id, sizeof(id), "%s", pstRepresentation->GetId().c_str());
    u32BandWidth = pstRepresentation->GetBandwidth();

    if (strlen(id) > 0)
    {
        if (STRING_MATCH(id, pstToBeMatchedAttr->id) &&
            pstToBeMatchedAttr->bandwidthBps == u32BandWidth && u32BandWidth > 0)
        {
            bMatched = HI_TRUE;
        }
    }
    /*
    else
    {
        if (pstToBeMatchedAttr->bandwidthBps == u32BandWidth && u32BandWidth > 0)
        {
            bMatched = HI_TRUE;
        }
    }
*/
    if (bMatched == HI_TRUE)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] matched  presentation   is @id=%s, @u32BandWidth=%u\n",
            __FUNCTION__, __LINE__, id, u32BandWidth);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] new  presentation is @id=%s, @u32BandWidth=%u,old is @id=%s, @u32BandWidth=%u\n",
            __FUNCTION__, __LINE__, id, u32BandWidth, pstToBeMatchedAttr->id, pstToBeMatchedAttr->bandwidthBps);
    }

    return bMatched;
}

//when resentation attribute changed, return HI_TRUE
static HI_BOOL _SVR_DASH_UpdatePresentationAttr(DASHRepresentation *pstPresentationAttr,
                                                                                            IRepresentation *pstRepresentation)
{
    HI_BOOL bAttrChanged = HI_FALSE;

    if (HI_FALSE == _SVR_DASH_PresentationIsMatch(pstRepresentation, pstPresentationAttr))
    {
        bAttrChanged = HI_TRUE;
        snprintf(pstPresentationAttr->id, DASH_ATTR_STR_LEN, "%s", pstRepresentation->GetId().c_str());
        pstPresentationAttr->bandwidthBps = pstRepresentation->GetBandwidth();
    }

    return bAttrChanged;
}

//set representationindex to MultimediaManager, when resentation changed, return HI_TRUE
static HI_BOOL _SVR_DASH_SetRepresentation(DASHMember * pstMember,
                                                                                 AVMediaType eType,
                                                                                 HI_S32 s32AdaptationSetIndex,
                                                                                 HI_S32 s32RepresentationIndex,
                                                                                 HI_BOOL bForceInvokeInit)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    IAdaptationSet *pstAaptionSet;
    IRepresentation *pstRepresentation;
    HI_BOOL bPrepresentationChanged = HI_FALSE;
    bool bInvokeInitSeg = false;

    switch(eType)
    {
        case AVMEDIA_TYPE_VIDEO:
            pstAaptionSet = manager->GetVideoAdaptionSet(s32AdaptationSetIndex);
            if (pstAaptionSet == NULL || pstMember->stCurPeriod.videoAdaptionsets.size() <= s32AdaptationSetIndex)
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] error, adaptionset at %d not exist, max:%lu\n",
                    __FUNCTION__, __LINE__, s32AdaptationSetIndex, pstMember->stCurPeriod.videoAdaptionsets.size());
                return HI_FALSE;
            }
            if (s32RepresentationIndex >= pstAaptionSet->GetRepresentation().size())
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] error, representation at %d of adationset %d not exist, max:%lu\n",
                    __FUNCTION__, __LINE__, s32RepresentationIndex, s32AdaptationSetIndex, pstAaptionSet->GetRepresentation().size());
                return HI_FALSE;
            }
            pstRepresentation = pstAaptionSet->GetRepresentation().at(s32RepresentationIndex);
            bPrepresentationChanged = _SVR_DASH_UpdatePresentationAttr(\
                &(pstMember->stCurPeriod.videoAdaptionsets.at(s32AdaptationSetIndex).curRepresentation),\
                pstRepresentation);
            if (bPrepresentationChanged == HI_TRUE || bForceInvokeInit == HI_TRUE)
            {
                bInvokeInitSeg = true;
            }
            if (s32AdaptationSetIndex == pstMember->s32VideoAdaptationSetIndex)
            {
                manager->SetVideoIndex(s32AdaptationSetIndex, s32RepresentationIndex, bInvokeInitSeg);
            }
            else
            {
                manager->SetVideoRepresentation(s32AdaptationSetIndex, s32RepresentationIndex, bInvokeInitSeg);
            }
            break;
        case AVMEDIA_TYPE_AUDIO:
            pstAaptionSet = manager->GetAudioAdaptionSet(s32AdaptationSetIndex);
            if (pstAaptionSet == NULL || pstMember->stCurPeriod.audioAdaptionsets.size() <= s32AdaptationSetIndex)
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] error, adaptionset at %d not exist, max:%lu\n",
                    __FUNCTION__, __LINE__, s32AdaptationSetIndex, pstMember->stCurPeriod.audioAdaptionsets.size());
                return HI_FALSE;
            }
            if (s32RepresentationIndex >= pstAaptionSet->GetRepresentation().size())
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] error, representation at %d of adationset %d not exist, max:%lu\n",
                    __FUNCTION__, __LINE__, s32RepresentationIndex, s32AdaptationSetIndex, pstAaptionSet->GetRepresentation().size());
                return HI_FALSE;
            }
            pstRepresentation = pstAaptionSet->GetRepresentation().at(s32RepresentationIndex);
            bPrepresentationChanged = _SVR_DASH_UpdatePresentationAttr(\
                &(pstMember->stCurPeriod.audioAdaptionsets.at(s32AdaptationSetIndex).curRepresentation),\
                pstRepresentation);
            if (bPrepresentationChanged == HI_TRUE || bForceInvokeInit == HI_TRUE)
            {
                bInvokeInitSeg = true;
            }
            if (s32AdaptationSetIndex == pstMember->s32AudioAdaptationSetIndex)
            {
                manager->SetAudioIndex(s32AdaptationSetIndex, s32RepresentationIndex, bInvokeInitSeg);
            }
            else
            {
                manager->SetAudioRepresentation(s32AdaptationSetIndex, s32RepresentationIndex, bInvokeInitSeg);
            }
             break;
        case AVMEDIA_TYPE_SUBTITLE:
            pstAaptionSet = manager->GetSubtitleAdaptionSet(s32AdaptationSetIndex);
            if (pstAaptionSet == NULL || pstMember->stCurPeriod.subtitleAdaptionsets.size() <= s32AdaptationSetIndex)
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] error, adaptionset at %d not exist, max:%lu\n",
                    __FUNCTION__, __LINE__, s32AdaptationSetIndex, pstMember->stCurPeriod.subtitleAdaptionsets.size());
                return HI_FALSE;
            }
            if (s32RepresentationIndex >= pstAaptionSet->GetRepresentation().size())
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] error, representation at %d of adationset %d not exist, max:%lu\n",
                    __FUNCTION__, __LINE__, s32RepresentationIndex, s32AdaptationSetIndex, pstAaptionSet->GetRepresentation().size());
                return HI_FALSE;
            }
            pstRepresentation = pstAaptionSet->GetRepresentation().at(s32RepresentationIndex);
            bPrepresentationChanged = _SVR_DASH_UpdatePresentationAttr(\
                &(pstMember->stCurPeriod.subtitleAdaptionsets.at(s32AdaptationSetIndex).curRepresentation),\
                pstRepresentation);
            if (bPrepresentationChanged == HI_TRUE || bForceInvokeInit == HI_TRUE)
            {
                bInvokeInitSeg = true;
            }
            if (s32AdaptationSetIndex == pstMember->s32SubtitleAdaptationSetIndex)
            {
                manager->SetSubtitleIndex(s32AdaptationSetIndex, s32RepresentationIndex, bInvokeInitSeg);
            }
            else
            {
                manager->SetSubtitleRepresentation(s32AdaptationSetIndex, s32RepresentationIndex, bInvokeInitSeg);
            }
             break;


        default:;
    }

    return bPrepresentationChanged;
}

static inline HI_S32 _SVR_DASH_SelectAdaptionset(DASHMember * pstMember, AVMediaType eType)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;

    switch(eType)
    {
        case AVMEDIA_TYPE_VIDEO:
            if (manager->GetVideoAdaptationSetNum() > pstMember->s32VideoAdaptationSetIndex &&
                pstMember->s32VideoAdaptationSetIndex >= 0)
            {
                return pstMember->s32VideoAdaptationSetIndex;
            }
            break;
        case AVMEDIA_TYPE_AUDIO:
            if (manager->GetAudioAdaptationSetNum() > pstMember->s32AudioAdaptationSetIndex &&
                pstMember->s32AudioAdaptationSetIndex >= 0)
            {
                return pstMember->s32AudioAdaptationSetIndex;
            }
             break;
        case AVMEDIA_TYPE_SUBTITLE:
            if (manager->GetSubtitleAdaptationSetNum() > pstMember->s32SubtitleAdaptationSetIndex &&
                pstMember->s32SubtitleAdaptationSetIndex >= 0)
            {
                return pstMember->s32SubtitleAdaptationSetIndex;
            }
        default:;
    }

    return 0;
}

static HI_BOOL _SVR_DASH_CheckRepresentationChanged(DASHMember * pstMember, AVMediaType eType)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    HI_S32 s32VideoRepresentationIndex    = -1;
    HI_S32 s32AudioRepresentationIndex    = -1;
    HI_S32 s32SubtitleRepresentationIndex = -1;
    HI_U32 u32BandWidth = 0;
    HI_BOOL bChanged = HI_FALSE;

    switch(eType)
    {
        case AVMEDIA_TYPE_VIDEO:
            if (pstMember->bVideoChangePresenFinish != HI_TRUE)
            {
                return HI_FALSE;
            }
            u32BandWidth = manager->GetVideoBandWidth();
            if (u32BandWidth == 0)
                return HI_FALSE;
            s32VideoRepresentationIndex = _SVR_DASH_SelectRepresentation(pstMember, eType, pstMember->s32VideoAdaptationSetIndex,u32BandWidth);
            dash_log(DASH_LOG_ERROR, "[%s,%d][BW] representation index %d returned with bw %u,current representation index %d\n",
                __FUNCTION__, __LINE__, s32VideoRepresentationIndex, u32BandWidth, pstMember->s32VideoRepresentationIndex);
            if (s32VideoRepresentationIndex == pstMember->s32VideoRepresentationIndex ||
                s32VideoRepresentationIndex < 0)
                return HI_FALSE;

            if (HI_TRUE == _SVR_DASH_SetRepresentation(pstMember, eType, \
                pstMember->s32VideoAdaptationSetIndex, s32VideoRepresentationIndex, HI_FALSE))
            {
                pstMember->s32VideoRepresentationIndex = s32VideoRepresentationIndex;
                bChanged = HI_TRUE;
                pstMember->bVideoChangePresenFinish = HI_FALSE;
            }
            break;
        case AVMEDIA_TYPE_AUDIO:
            if (pstMember->bAudioChangePresenFinish != HI_TRUE)
            {
                return HI_FALSE;
            }
            u32BandWidth = manager->GetAudioBandWidth();
             if (u32BandWidth == 0)
                return HI_FALSE;
            s32AudioRepresentationIndex = _SVR_DASH_SelectRepresentation(pstMember, eType, \
                pstMember->s32AudioAdaptationSetIndex,u32BandWidth);
            dash_log(DASH_LOG_ERROR, "[%s,%d][BW] representation index %d returned with bw %u,current representation index %d\n",
                __FUNCTION__, __LINE__, s32AudioRepresentationIndex, u32BandWidth, pstMember->s32AudioRepresentationIndex);
            if (s32AudioRepresentationIndex == pstMember->s32AudioRepresentationIndex ||
                s32AudioRepresentationIndex < 0)
                return HI_FALSE;

            if (HI_TRUE == _SVR_DASH_SetRepresentation(pstMember, eType, \
                pstMember->s32AudioAdaptationSetIndex, s32AudioRepresentationIndex, HI_FALSE))
            {
                pstMember->s32AudioRepresentationIndex = s32AudioRepresentationIndex;
                bChanged = HI_TRUE;
                pstMember->bAudioChangePresenFinish = HI_FALSE;
            }

             break;
        case AVMEDIA_TYPE_SUBTITLE:
            if (pstMember->bSubtitleChangePresenFinish != HI_TRUE)
            {
                return HI_FALSE;
            }
            u32BandWidth = manager->GetSubtitleBandWidth();
             if (u32BandWidth == 0)
                return HI_FALSE;
            s32SubtitleRepresentationIndex = _SVR_DASH_SelectRepresentation(pstMember, eType,\
                pstMember->s32SubtitleAdaptationSetIndex,u32BandWidth);
            dash_log(DASH_LOG_ERROR, "[%s,%d][BW] representation index %d returned with bw %u,current representation index %d\n",
                __FUNCTION__, __LINE__, s32SubtitleRepresentationIndex, u32BandWidth, pstMember->s32SubtitleRepresentationIndex);
            if (s32SubtitleRepresentationIndex == pstMember->s32SubtitleRepresentationIndex ||
                s32SubtitleRepresentationIndex < 0)
                return HI_FALSE;

            if (HI_TRUE == _SVR_DASH_SetRepresentation(pstMember, eType, \
                pstMember->s32SubtitleAdaptationSetIndex, s32SubtitleRepresentationIndex, HI_FALSE))
            {
                pstMember->s32SubtitleRepresentationIndex = s32SubtitleRepresentationIndex;
                bChanged = HI_TRUE;
                pstMember->bSubtitleChangePresenFinish = HI_FALSE;
            }
        default:
            return HI_FALSE;
    }

/*
    if (pstMember->eRepresentationType != SINGLE_MEDIA_SEGMENT)
    {
        manager->SetQuality();
    }
*/
    return bChanged;
}

static HI_BOOL _SVR_DASH_CheckEos(DASHMember * pstMember)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    AVIOInterruptCB *cb = &(pstMember->ic->interrupt_callback);

    if (cb && cb->callback && (cb->callback(cb->opaque)))
        return HI_TRUE;

    if (pstMember->vid_nb > 0)
    {
        if ((HI_FALSE == pstMember->bVideoEosReached))// ||!manager->VideoEosReached())
            return HI_FALSE;
    }

    if (pstMember->aud_nb > 0)
    {
        if ((HI_FALSE == pstMember->bAudioEosReached))// || !manager->AudioEosReached())
            return HI_FALSE;
    }

    if (pstMember->sub_nb > 0)
    {
        if ((HI_FALSE == pstMember->bSubtitleEosReached))// || !manager->SubtitleEosReached())
            return HI_FALSE;
    }

    return HI_TRUE;
}

static HI_S32 _SVR_DASH_ReadPacket(DASHMember * pstMember ,AVFormatContext *sub, AVPacket *pkt, HI_S64 *ps64LastPts)
{
    HI_S32 s32Ret = HI_SUCCESS;
    AVFormatContext *master = pstMember->ic;

    s32Ret = av_read_frame(sub ,pkt);

    /*
     * ISOFF video & audio are stored separately
     * MPEG2-TS video & audio are stored together
     * So if there are more than one stream in AVFormatContext, do not renew the stream_index
     */
#if 0
    if (1 == sub->nb_streams)
        pkt->stream_index = sub->streams[0]->index;
#else
    if (pstMember->bIsISOFF || sub->nb_streams == 1)
    {
        pkt->stream_index = sub->streams[pkt->stream_index]->index;
    }
#endif

    if (pkt->stream_index >= master->nb_streams || pkt->stream_index < 0)
    {
        return AVERROR_INVALIDDATA;
    }

    AVStream * st = NULL;
    st = master->streams[pkt->stream_index];
    if (NULL == st)
    {
        return AVERROR_INVALIDDATA;
    }

    if (ps64LastPts && s32Ret == 0)
    {
        if (st->time_base.num != 0 && st->time_base.den != 0)
            *ps64LastPts = (pkt->pts * 1000 * st->time_base.num )/ st->time_base.den;
        else
            *ps64LastPts = pkt->pts;
    }

    _SVR_DASH_UpdatePktPts(pstMember, pkt);

    return (s32Ret < 0) ? HI_FAILURE : HI_SUCCESS;
}

#ifdef PLAYREADY_SUPPORT

static void _SVR_DASH_CheckDRMSystem(DASHMember *pstMember)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    MOVTenc *tenc = NULL;
    MOVPssh *pssh = NULL;
    int index = 0;

    dash_log(DASH_LOG_INFO, "%s %d\n", __FUNCTION__, __LINE__);

    if (pstMember->vid_ic == NULL && pstMember->aud_ic == NULL)
    {
        return;
    }
    if (pstMember->vid_nb &&
        pstMember->vid_ic != NULL &&
        pstMember->vid_ic[0] != NULL)
    {
        tenc = ff_mov_get_tenc(pstMember->vid_ic[0]);
        pssh = ff_mov_get_pssh(pstMember->vid_ic[0]);
    }
    else if (pstMember->aud_nb &&
        pstMember->aud_ic != NULL &&
        pstMember->aud_ic[0] != NULL)
    {
        tenc = ff_mov_get_tenc(pstMember->aud_ic[0]);
        pssh = ff_mov_get_pssh(pstMember->aud_ic[0]);
    }

    for (index = 0; index < (sizeof(DRMSystem)/sizeof(DRMSystem[0])); index++)
    {
        /* Check supportted DRM System ID */
        string uuid(DRMSystem[index].uuid);
        if (manager->CheckUUID(uuid) && STRING_MATCH(DRMSystem[index].name, "PlayReady"))
        {
            dash_log(DASH_LOG_INFO, "Check:Using playready!\n");
            pstMember->bUsingPlayReady = HI_TRUE;
            return;
        }

        if (pssh && !memcmp(DRMSystem[index].system_id, pssh->system_id, sizeof(DRMSystem[index].system_id)) && STRING_MATCH(DRMSystem[index].name, "PlayReady"))
        {
            dash_log(DASH_LOG_INFO, "Check:Using playready!\n");
            pstMember->bUsingPlayReady = HI_TRUE;
            return;
        }
    }

    /* Check if DRMRightsError happened */
    if (tenc && tenc->default_algorithm_id == 0x01)
    {
        dash_log(DASH_LOG_ERROR, "Check:The strem is encrypted, but no DRM System is specified!\n");
        dash_errorcode_cb(pstMember->ic->interrupt_callback.opaque, 0, "DRMRightsError:PlayReady");
    }

    return;
}

static HI_S32 _SVR_DASH_PlayReady_SetSecureClock(DASHMember *pstMember)
{
    HI_PLAYREADY_CHALLENGE_S Challenge;
    HI_PLAYREADY_ASCII_STRING Response;
    HI_PLAYREADY_SECURECLOCK_STATUS_E Status;
    HI_PLAYREADY_DATE_TIME_S Time;
    HI_S32 s32Ret = HI_SUCCESS;
    PlayReadyMember *pstPRMember = &pstMember->PRMember;

    memset(&Challenge, 0, sizeof(HI_PLAYREADY_CHALLENGE_S));
    memset(&Response, 0, sizeof(HI_PLAYREADY_ASCII_STRING));
    memset(&Time, 0, sizeof(HI_PLAYREADY_DATE_TIME_S));

    s32Ret = HI_PLAYREADY_SecureClock_Generate_Challenge(pstPRMember->hPlayReady, &Challenge);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Set:HI_PLAYREADY_SecureClock_Generate_Challenge failed!\n");
        goto playready_set_failed;
    }

    s32Ret = HI_PLAYREADY_HTTP_FetchLicense(&Challenge, &Response, IS_SECURE_CLOCK);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Set:HI_PLAYREADY_HTTP_FetchLicense failed!\n");
        goto playready_set_failed;
    }

    HI_PLAYREADY_Release_Challenge(&Challenge);

    s32Ret = HI_PLAYREADY_SecureClock_ProcessResponse(pstPRMember->hPlayReady, &Response);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "HI_PLAYREADY_SecureClock_ProcessResponse failed!\n");
        goto playready_set_failed;
    }

    HI_PLAYREADY_HTTP_Release_Response(&Response);

    s32Ret = HI_PLAYREADY_GetSecureClock(pstPRMember->hPlayReady, &Status, &Time);
    if (HI_SUCCESS == s32Ret)
    {
        dash_log(DASH_LOG_INFO, "HI_PLAYREADY_GetSecureClock: Status:%d Time:%u-%u-%u %u:%u:%u\n", Status, \
            Time.u16Year, Time.u16Month, Time.u16Day, Time.u16Hour, Time.u16Minute, Time.u16Second);
    }

    return HI_SUCCESS;

playready_set_failed:
    HI_PLAYREADY_Release_Challenge(&Challenge);
    HI_PLAYREADY_HTTP_Release_Response(&Response);
    return HI_FAILURE;
}

static HI_S32 _SVR_DASH_PlayReady_Prepare(DASHMember *pstMember, HI_PLAYREADY_OPENPARAM_S * pstOpenParam)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    string pro = manager->GetPRO();
    MOVPssh *pssh;
    HI_U8 *pu8Data = NULL;
    HI_U32 u32Size = 0;
    HI_U8 *pu8PROData = NULL;
    HI_U32 u32PROSize = 0;
    HI_U8 *pu8EncodedPROData = NULL;
    HI_U32 u32EncodedPROSize = 0;
    HI_U32 u32Pading = 0;
    HI_S32 i = 0;

    if (pro != "")
    {
        dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);
        pu8Data = (HI_U8*)av_mallocz(pro.size());
        pu8EncodedPROData = (HI_U8*)av_mallocz(pro.size());
        strncpy((HI_CHAR*)pu8Data, (HI_CHAR*)pro.c_str(), pro.size());
        u32Size = pro.size();

        for (i = 0; i < u32Size; i++)
        {
            /*Remove extra data: 0x0a 'LF',0x09 'HT',0x20 'SPACE'*/
            if (pu8Data[i] != 0x0a && pu8Data[i] != 0x09 && pu8Data[i] != 0x20)
            {
                pu8EncodedPROData[u32EncodedPROSize] = pu8Data[i];
                printf("0x%x ", pu8EncodedPROData[u32EncodedPROSize]);
                u32EncodedPROSize++;
            }

            /*Count pading '='*/
            if (0x3d == pu8Data[i])
                u32Pading++;
        }

        u32PROSize = u32EncodedPROSize * 6 / 8 - u32Pading;
        pu8PROData = (HI_U8*)av_mallocz(u32PROSize);
        dash_log(DASH_LOG_INFO, "\nPROSize:(en)%u %u data:\n", u32EncodedPROSize, u32PROSize);
        av_base64_decode(pu8PROData, (HI_CHAR*)pu8EncodedPROData, u32PROSize);
        av_free(pu8EncodedPROData);
        av_free(pu8Data);

        for (i = 0; i < u32PROSize; i++)
            dash_log(DASH_LOG_INFO, "0x%x ", pu8PROData[i]);
    }
    else
    {
        if (pstMember->vid_nb)
            pssh = ff_mov_get_pssh(pstMember->vid_ic[0]);
        else if (pstMember->aud_nb)
            pssh = ff_mov_get_pssh(pstMember->aud_ic[0]);

        if (NULL == pssh)
            return HI_FAILURE;

        pu8PROData = (HI_U8*)av_mallocz(pssh->data_size);
        u32PROSize = pssh->data_size;
        memcpy(pu8PROData, pssh->data, u32PROSize);
    }

    dash_log(DASH_LOG_INFO, "\n%s %d\n", __FILE__, __LINE__);
    if (pu8PROData == NULL || u32PROSize <= 0)
    {
        dash_log(DASH_LOG_ERROR, "%s %d\n", __FILE__, __LINE__);
        return HI_FAILURE;
    }

    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);
    pstOpenParam->pCE_Ver1 = NULL;
    pstOpenParam->pCE_Ver2->Valid = HI_TRUE;
    pstOpenParam->pCE_Ver2->Data.pszString = pu8PROData;
    pstOpenParam->pCE_Ver2->Data.length = u32PROSize;
    pstOpenParam->IsHardWareDecrypt = HI_TRUE;
    pstOpenParam->initiatorFlag = HI_FALSE;
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_PlayReady_Record(DASHMember *pstMember, HI_PLAYREADY_OPENPARAM_S * pstOpenParam)
{
    PlayReadyMember * pstPRMember = &pstMember->PRMember;
    MOVTenc *tenc;

    /*Record PRO data*/
    if (pstPRMember->pu8PROData)
    {
        av_free(pstPRMember->pu8PROData);
        pstPRMember->pu8PROData = NULL;
        pstPRMember->u32PROSize = 0;
    }
    pstPRMember->pu8PROData = pstOpenParam->pCE_Ver2->Data.pszString;
    pstPRMember->u32PROSize = pstOpenParam->pCE_Ver2->Data.length;

    if (pstMember->vid_nb)
        tenc = ff_mov_get_tenc(pstMember->vid_ic[0]);
    else if (pstMember->aud_nb)
        tenc = ff_mov_get_tenc(pstMember->aud_ic[0]);

    /*TODO: Record the right KID*/
    if (NULL == tenc)
    {
        dash_log(DASH_LOG_ERROR, "Record:No KID found in media stream!\n");
        return HI_FAILURE;
    }

    memcpy(pstPRMember->u8Kid, tenc->default_kid, sizeof(pstPRMember->u8Kid));

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_PlayReady_CheckKIDChanged(DASHMember *pstMember)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    PlayReadyMember * pstPRMember = &pstMember->PRMember;
    MOVTenc *tenc;

    if (pstMember->vid_nb)
        tenc = ff_mov_get_tenc(pstMember->vid_ic[0]);
    else if (pstMember->aud_nb)
        tenc = ff_mov_get_tenc(pstMember->aud_ic[0]);

    if (tenc && memcmp(pstPRMember->u8Kid, tenc->default_kid, sizeof(pstPRMember->u8Kid)))
    {
        dash_log(DASH_LOG_WARNING, "Check:KID has been changed!\n");
        return HI_SUCCESS;
    }

    dash_log(DASH_LOG_INFO, "Check has not been changed!\n");
    return HI_FAILURE;
}

size_t _SVR_DASH_CurlFetchLicenseCallback(void * contents, size_t size,size_t nmemb,void * userdata)
{
    HI_PLAYREADY_ASCII_STRING *pResponse = (HI_PLAYREADY_ASCII_STRING *)userdata;
    size_t realsize = size * nmemb;

    if (pResponse->pszString)
        pResponse->pszString = (HI_U8*)av_realloc(pResponse->pszString, pResponse->length + realsize);
    else
        pResponse->pszString = (HI_U8*)av_mallocz(realsize);

    memcpy(pResponse->pszString + pResponse->length, contents, realsize);
    pResponse->length += realsize;

    return realsize;
}

static HI_S32 _SVR_DASH_PlayReady_FetchLicense(DASHMember *pstMember, const HI_CHAR *pURL, HI_PLAYREADY_CHALLENGE_S *pChallenge, HI_PLAYREADY_ASCII_STRING *pResponse, HI_IS_WHAT_ENCRYPT IsWhatEncryp)
{
    CurlDataMember * curlDataMember = &pstMember->curlDataMember;
    int is_running = 0;
    char * post_fields = NULL;
    struct curl_slist *headers = NULL;

    curl_global_init(CURL_GLOBAL_ALL);
    curlDataMember->curl_handle = curl_easy_init();
    curlDataMember->multi_handle = curl_multi_init();

    post_fields = (char *)av_mallocz(pChallenge->ChallengeContent.length + 1);
    memcpy(post_fields, pChallenge->ChallengeContent.pszString, pChallenge->ChallengeContent.length);

    dash_log(DASH_LOG_INFO, "content length:%u post_fields:%s\n", pChallenge->ChallengeContent.length, post_fields);
    headers = curl_slist_append(headers, "Content-Type: text/xml; charset=utf-8");
    /* No 'Expect' and 'Accept' header */
    headers = curl_slist_append(headers, "Expect:");
    headers = curl_slist_append(headers, "Accept:");
    switch(IsWhatEncryp)
    {
        case IS_PLAYREADY_ENCRYPT:
            headers = curl_slist_append(headers, "SOAPAction: http://schemas.microsoft.com/DRM/2007/03/protocols/AcquireLicense");
            break;
        case IS_ACK_LIC:
            headers = curl_slist_append(headers, "SOAPAction: http://schemas.microsoft.com/DRM/2007/03/protocols/AcknowledgeLicense");
            break;
        case IS_SECURE_CLOCK:
            /* TODO */
            break;
        default:
            break;
    }

    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_URL, pURL);
    if (strstr(pURL, "https://"))
    {
        dash_log(DASH_LOG_INFO, "SSL do not verify anything!\n");
        curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_SSL_VERIFYHOST, 0L);
    }
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_WRITEFUNCTION, _SVR_DASH_CurlFetchLicenseCallback);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_WRITEDATA, (void *)pResponse);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_POSTFIELDS, post_fields);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_NOSIGNAL, 1L);

    curl_multi_add_handle(curlDataMember->multi_handle, curlDataMember->curl_handle);
    curlDataMember->status = CURL_STATUS_INPROGRESS;

    do
    {
        while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(curlDataMember->multi_handle, &is_running));

        if (curlDataMember->status != CURL_STATUS_INPROGRESS)
        {
            break;
        }

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 1000;

        int max;
        fd_set fd_read;
        fd_set fd_write;
        fd_set fd_except;

        FD_ZERO(&fd_read);
        FD_ZERO(&fd_write);
        FD_ZERO(&fd_except);

        curl_multi_fdset(curlDataMember->multi_handle, &fd_read, &fd_write, &fd_except,&max);
        int code = select(max + 1, &fd_read, &fd_write, &fd_except, &tv);
        if (-1 == code)
           break;

    }while(is_running);

    curl_slist_free_all(headers);
    av_free(post_fields);

    curl_easy_getinfo(curlDataMember->curl_handle, CURLINFO_RESPONSE_CODE ,&curlDataMember->httpCode);
    curl_multi_remove_handle(curlDataMember->multi_handle, curlDataMember->curl_handle);
    curl_easy_cleanup(curlDataMember->curl_handle);
    curl_multi_cleanup(curlDataMember->multi_handle);
    curl_global_cleanup();

    if (curlDataMember->httpCode == 200 || curlDataMember->httpCode == 206)
    {
        curlDataMember->status = CURL_STATUS_OK;
        return HI_SUCCESS;
    }
    else
    {
        curlDataMember->status = CURL_STATUS_NOK;
        return HI_FAILURE;
    }
}

#ifndef USE_PLAYREADY_HTTP
//#define USE_PLAYREADY_HTTP
#endif

#ifndef USE_SECURE_CLOCK
//#define USE_SECURE_CLOCK
#endif

#ifndef USE_CUSTOM_DATA
#define USE_CUSTOM_DATA
#endif
static HI_S32 _SVR_DASH_PlayReady_Open(DASHMember *pstMember)
{
    PlayReadyMember * pstPRMember = &pstMember->PRMember;
    HI_FORMAT_PLAYREADY_EXTRADATA_S *pstPRExtraData = &pstPRMember->stPlayReadyExtraData;
    HI_PLAYREADY_CHALLENGE_S Challenge;
    HI_PLAYREADY_ASCII_STRING Response;
    HI_PLAYREADY_LICENSE_RESPONSE AckResponse;
    HI_PLAYREADY_OPENPARAM_S OpenParam;
    HI_PR_Content_Encryption_Ver2_S ContentEncryption;
    HI_PLAYREADY_STORE_CLEANUP_E eCleanupType = (HI_PLAYREADY_STORE_CLEANUP_E)(HI_PLAYREADY_STORE_CLEANUP_DELETE_EXPIRED_LICENSES | HI_PLAYREADY_STORE_CLEANUP_DELETE_REMOVAL_DATE_LICENSES);
    HI_U8 tempURL[1024] = {0};
    HI_S32 s32Ret = HI_SUCCESS;

    memset(&Challenge, 0, sizeof(HI_PLAYREADY_CHALLENGE_S));
    memset(&Response, 0, sizeof(HI_PLAYREADY_ASCII_STRING));
    memset(&AckResponse, 0, sizeof(HI_PLAYREADY_LICENSE_RESPONSE));
    memset(&OpenParam, 0, sizeof(HI_PLAYREADY_OPENPARAM_S));
    memset(&ContentEncryption, 0, sizeof(HI_PR_Content_Encryption_Ver2_S));

    /*Prepare*/
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);
    OpenParam.pCE_Ver2 = &ContentEncryption;
    s32Ret = _SVR_DASH_PlayReady_Prepare(pstMember, &OpenParam);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:_SVR_DASH_PlayReady_Prepare failed!\n");
        goto playready_open_fail;
    }
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

    s32Ret = HI_PLAYREADY_Open(&OpenParam, &pstPRMember->hPlayReady);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:HI_PLAYREADY_Open failed!\n");
        goto playready_open_fail;
    }
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

    /*Record PRO & KID*/
    s32Ret = _SVR_DASH_PlayReady_Record(pstMember, &OpenParam);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:_SVR_DASH_PlayReady_Store failed!\n");
        //goto playready_open_fail;
    }

#ifdef USE_SECURE_CLOCK
#ifdef USE_PLAYREADY_HTTP
    /*Secure Clock*/
    s32Ret = _SVR_DASH_PlayReady_SetSecureClock(pstMember);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:_SVR_DASH_PlayReady_SetSecureClock failed!\n");
        goto playready_open_fail;
    }
#else
    /*Use Curl*/
#endif
#endif

    s32Ret = HI_PLAYREADY_StoreMgmt_CleanupStore(pstPRMember->hPlayReady, eCleanupType);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:HI_PLAYREADY_StoreMgmt_CleanupStore failed!\n");
        goto playready_open_fail;
    }
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

    if (HI_TRUE == pstPRExtraData->bPlayReadyLicense)
    {
        dash_log(DASH_LOG_INFO, "Open:Already has playready pre-acquisition license!\n");
        s32Ret = HI_PLAYREADY_GetLicenseStatus(pstPRMember->hPlayReady);
        if (s32Ret == HI_SUCCESS)
        {
            s32Ret = HI_PLAYREADY_LoadLicense(pstPRMember->hPlayReady);
            if (s32Ret == HI_SUCCESS)
            {
                dash_log(DASH_LOG_INFO, "Open:HI_PLAYREADY_LoadLicense success!");
                return HI_SUCCESS;
            }
            dash_log(DASH_LOG_ERROR, "Opedn:HI_PLAYREADY_LoadLicense failed! Try to fetch license!\n");
        }

    }
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

#ifdef USE_CUSTOM_DATA
    /* Chex extra Custom Data*/
    HI_PLAYREADY_ASCII_STRING stCustomData;
    memset(&stCustomData, 0, sizeof(HI_PLAYREADY_ASCII_STRING));

    if (pstPRExtraData->stCustomData.pu8Data)
    {
        dash_log(DASH_LOG_INFO, "Open:set Custom Data %s %u!\n", pstPRExtraData->stCustomData.pu8Data, pstPRExtraData->stCustomData.u32Length);
        stCustomData.length = pstPRExtraData->stCustomData.u32Length;
        stCustomData.pszString = (HI_U8*)av_mallocz(stCustomData.length);
        memcpy(stCustomData.pszString, pstPRExtraData->stCustomData.pu8Data, stCustomData.length);
    }

    s32Ret = HI_PLAYREADY_LicAcquisition_Generate_ChallengeEx(pstPRMember->hPlayReady, stCustomData, &Challenge);
    av_free(stCustomData.pszString);
#else
    s32Ret = HI_PLAYREADY_LicAcquisition_Generate_Challenge(pstPRMember->hPlayReady, &Challenge);
#endif
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:HI_PLAYREADY_LicAcquisition_Generate_Challenge failed!\n");
        goto playready_open_fail;
    }

    /* Check extra LA_URL */
    if (pstPRExtraData->stURL.pu8Data)
    {
        dash_log(DASH_LOG_INFO, "Open:extra LA_URL=%s %u\n", pstPRExtraData->stURL.pu8Data, pstPRExtraData->stURL.u32Length);
        av_free(Challenge.URL.pszString);
        Challenge.URL.length = pstPRExtraData->stURL.u32Length;
        Challenge.URL.pszString = (HI_U8*)av_mallocz(Challenge.URL.length);
        memcpy(Challenge.URL.pszString, pstPRExtraData->stURL.pu8Data, Challenge.URL.length);
    }

    memcpy(tempURL, Challenge.URL.pszString, Challenge.URL.length);
    dash_log(DASH_LOG_INFO, "Open:LA_URL=%s\n",tempURL);

#ifdef USE_PLAYREADY_HTTP
    s32Ret = HI_PLAYREADY_HTTP_FetchLicense(&Challenge, &Response, IS_PLAYREADY_ENCRYPT);
#else
    /*Use Curl*/
    s32Ret = _SVR_DASH_PlayReady_FetchLicense(pstMember, (HI_CHAR*)tempURL, &Challenge, &Response, IS_PLAYREADY_ENCRYPT);
#endif
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:FetchLicense(IS_PLAYREADY_ENCRYPT) failed!\n");
        dash_errorcode_cb(pstMember->ic->interrupt_callback.opaque, 0, "DRMRightsError:PlayReady");
        goto playready_open_fail;
    }

    HI_PLAYREADY_Release_Challenge(&Challenge);
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

    HI_PLAYREADY_LicAcquisition_ProcessResponse(pstPRMember->hPlayReady, &Response, &AckResponse);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:HI_PLAYREADY_LicAcquisition_ProcessResponse failed!\n");
        goto playready_open_fail;
    }

#ifdef USE_PLAYREADY_HTTP
    HI_PLAYREADY_HTTP_Release_Response(&Response);
#else
    av_freep(&Response.pszString);
    Response.length = 0;
#endif
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

    /*ACK*/
    s32Ret = HI_PLAYREADY_LicenseAcq_Generate_Ack(pstPRMember->hPlayReady, &AckResponse, &Challenge, tempURL);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:HI_PLAYREADY_LicenseAcq_Generate_Ack failed.ACK is not needed!\n");
        HI_PLAYREADY_Release_Challenge(&Challenge);
        goto playready_load_license;
    }
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

#ifdef USE_PLAYREADY_HTTP
    s32Ret = HI_PLAYREADY_HTTP_FetchLicense(&Challenge, &Response, IS_ACK_LIC);
#else
    /*Use Curl*/
    s32Ret = _SVR_DASH_PlayReady_FetchLicense(pstMember, (HI_CHAR*)tempURL, &Challenge, &Response, IS_ACK_LIC);
#endif
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:FetchLicense(IS_ACK_LIC) failed!\n");
        goto playready_open_fail;
    }


    HI_PLAYREADY_Release_Challenge(&Challenge);
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

    HI_PLAYREADY_LicenseAcq_ProcessAckResponse(pstPRMember->hPlayReady, &Response);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:HI_PLAYREADY_LicenseAcq_ProcessAckResponse failed!\n");
        goto playready_open_fail;
    }

#ifdef USE_PLAYREADY_HTTP
    HI_PLAYREADY_HTTP_Release_Response(&Response);
#else
    av_freep(&Response.pszString);
    Response.length = 0;
#endif
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

playready_load_license:
    /*Check License*/
    s32Ret = HI_PLAYREADY_GetLicenseStatus(pstPRMember->hPlayReady);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:HI_PLAYREADY_GetLicenseStatus failed!\n");
        //goto playready_open_fail;
    }
    dash_log(DASH_LOG_INFO, "%s %d\n", __FILE__, __LINE__);

    /*Load License*/
    s32Ret = HI_PLAYREADY_LoadLicense(pstPRMember->hPlayReady);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Open:HI_PLAYREADY_LoadLicense failed!\n");
        dash_errorcode_cb(pstMember->ic->interrupt_callback.opaque, 1, "DRMRightsError:PlayReady");
        goto playready_open_fail;
    }

    dash_log(DASH_LOG_INFO, "Open:PlayReady open success!\n");

    return HI_SUCCESS;

playready_open_fail:
    HI_PLAYREADY_Release_Challenge(&Challenge);
#ifdef USE_PLAYREADY_HTTP
    HI_PLAYREADY_HTTP_Release_Response(&Response);
#else
    av_freep(&Response.pszString);
    Response.length = 0;
#endif

    HI_PLAYREADY_Close(pstPRMember->hPlayReady);
    return HI_FAILURE;
}

static HI_S32 _SVR_DASH_PlayReady_Close(DASHMember *pstMember)
{
    PlayReadyMember * pstPRMember = &pstMember->PRMember;
    HI_FORMAT_PLAYREADY_EXTRADATA_S *pstPRExtraData = &pstPRMember->stPlayReadyExtraData;
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_PLAYREADY_Close(pstPRMember->hPlayReady);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Close:HI_PLAYREADY_Close failed!\n");
    }

    if (pstPRMember->pu8PROData)
    {
        av_free(pstPRMember->pu8PROData);
        pstPRMember->pu8PROData = NULL;
        pstPRMember->u32PROSize = 0;
    }

    if (pstPRExtraData->stCustomData.pu8Data)
    {
        av_free(pstPRExtraData->stCustomData.pu8Data);
        pstPRExtraData->stCustomData.pu8Data = NULL;
        pstPRExtraData->stCustomData.u32Length = 0;
    }

    if (pstPRExtraData->stURL.pu8Data)
    {
        av_free(pstPRExtraData->stURL.pu8Data);
        pstPRExtraData->stURL.pu8Data = NULL;
        pstPRExtraData->stURL.u32Length = 0;
    }

    memset(pstPRExtraData, 0, sizeof(HI_FORMAT_PLAYREADY_EXTRADATA_S));
    memset(pstPRMember, 0, sizeof(PlayReadyMember));

    return s32Ret;
}

static HI_S32 _SVR_DASH_PlayReady_Reopen(DASHMember *pstMember)
{
    PlayReadyMember * pstPRMember = &pstMember->PRMember;
    HI_FORMAT_PLAYREADY_EXTRADATA_S *pstPRExtraData = &pstPRMember->stPlayReadyExtraData;
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_PLAYREADY_Close(pstPRMember->hPlayReady);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Close:HI_PLAYREADY_Close failed!\n");
    }

    pstPRExtraData->bPlayReadyLicense = HI_TRUE;
    s32Ret = _SVR_DASH_PlayReady_Open(pstMember);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Reopen:_SVR_DASH_PlayReady_Open failed!\n");
    }

    return s32Ret;
}

static HI_U8* _SVR_DASH_PlayReady_Compose_Data(AVPacket *pkt, HI_U32 *pu32DataSize)
{
    HI_U8 *pu8Data = NULL;
    HI_U8 *pu8Temp = NULL;
    HI_U32 u32DataSize = 0;             /* Total encrypted data size */
    HI_U32 u32EncryptedDataSize = 0;    /* Current subsample encrypted data size */
    HI_U32 u32ClearDataSize = 0;        /* Total clear data size */
    HI_U32 i = 0;
    IV *iv;

    iv = (IV*)pkt->side_data->data;

    for (i = 0; i < iv->subsample_count; i++)
    {
        u32ClearDataSize += iv->subsample[i]->clear_data_size;
        u32EncryptedDataSize = iv->subsample[i]->encrypted_data_size;
        if (0 == u32EncryptedDataSize)
            continue;

        if (NULL == pu8Data)
            pu8Data = (HI_U8*)av_mallocz(u32EncryptedDataSize);
        else
        {
            pu8Temp = (HI_U8*)av_realloc(pu8Data, u32DataSize + u32EncryptedDataSize);
            if (NULL == pu8Temp)
                av_freep(&pu8Data);
            else
                pu8Data = pu8Temp;
        }

        if (NULL == pu8Data)
        {
            dash_log(DASH_LOG_ERROR, "Compose:malloc failed!\n");
            return NULL;
        }

        memcpy(pu8Data + u32DataSize, pkt->data + u32ClearDataSize + u32DataSize, u32EncryptedDataSize);
        u32DataSize += u32EncryptedDataSize;
    }

    //dash_log("Compose:totoal=%u clear=%u encrypted=%u pkt_size=%d\n",u32ClearDataSize + u32DataSize, u32ClearDataSize, u32DataSize, pkt->size);

    *pu32DataSize = u32DataSize;
    return pu8Data;
}

static HI_S32 _SVR_DASH_PlayReady_Decompose_Data(AVPacket *pkt, HI_U8 *pu8Data)
{
    HI_U32 u32ClearDataSize = 0;        /* Total clear data size */
    HI_U32 u32EncryptedDataSize = 0;    /* Current subsample encrypted data size */
    HI_U32 u32Offset = 0;               /* offset of encrypted data */
    HI_U32 i = 0;
    IV *iv;

    iv = (IV*)pkt->side_data->data;

    for (i = 0; i < iv->subsample_count; i++)
    {
        u32EncryptedDataSize = iv->subsample[i]->encrypted_data_size;
        u32ClearDataSize += iv->subsample[i]->clear_data_size;
        if (0 == u32EncryptedDataSize)
            continue;

        memcpy(pkt->data + u32ClearDataSize + u32Offset, pu8Data + u32Offset, u32EncryptedDataSize);
        u32Offset += u32EncryptedDataSize;
    }

    //dash_log("Decompose:totoal=%u clear=%u encrypted=%u pkt_size:%d\n",u32ClearDataSize + u32Offset, u32ClearDataSize, u32Offset, pkt->size);

    av_free(pu8Data);
    return 0;
}

static int _SVR_DASH_PlayReady_IV_Convert(uint8_t *data, int size)
{
    int temp = 0;
    int i = 0;

    if (8 == size)
    {
        /* big endian to little endian*/
        for (i = 0; i < 4; i++)
        {
            temp = data[i];
            data[i] = data[size - 1 - i];
            data[size - 1 - i] = temp;
        }
    }
    else if (16 == size)
    {
        //dash_log("Convert:do nothing!\n");
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "Convert:Invalid IV size:%d!\n", size);
        return -1;
    }

    return 0;
}

static HI_S32 _SVR_DASH_PlayReady_Decrypt(DASHMember *pstMember, AVPacket *pkt)
{
    PlayReadyMember *pstPRMember = &pstMember->PRMember;
    HI_PLAYREADY_DECRYPTPARM_S DecryptParam;
    HI_U8 *pu8Data = NULL;
    HI_U32 u32DataSize = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    IV * iv;

    memset(&DecryptParam, 0, sizeof(HI_PLAYREADY_DECRYPTPARM_S));
    if (NULL == pkt->side_data || NULL == pkt->side_data->data || pkt->side_data->size < 0)
    {
        dash_log(DASH_LOG_ERROR, "Decrypt:get IV failed 0x%x %d!\n", pkt->side_data, pkt->side_data_elems);
        goto playready_decrypt_fail;
    }

    iv = (IV*)pkt->side_data->data;
    if (iv->use_subsample)
    {
        pu8Data = _SVR_DASH_PlayReady_Compose_Data(pkt, &u32DataSize);
        if (NULL == pu8Data)
        {
            if (0 != u32DataSize)
            {
                dash_log(DASH_LOG_ERROR, "Decrypt:compose data failed!\n");
                goto playready_decrypt_fail;
            }
            else
            {
                dash_log(DASH_LOG_INFO, "Decyrpt:clear sample!\n");
                return HI_SUCCESS;
            }
        }
        else
        {
            DecryptParam.u8Data = pu8Data;
            DecryptParam.u32Length = u32DataSize;
        }
    }
    else
    {
        DecryptParam.u8Data = pkt->data;
        DecryptParam.u32Length = pkt->size;
    }

#if 1
    _SVR_DASH_PlayReady_IV_Convert(iv->data, iv->size);
#endif
    DecryptParam.u8ReplicatedData = iv->data;
    DecryptParam.u32ReplicatedLength = iv->size;

    dash_log(DASH_LOG_DEBUG, "Decrypt:iv_size=%u encrypted_size=%d\n", \
        DecryptParam.u32ReplicatedLength = iv->size, DecryptParam.u32Length);
    s32Ret = HI_PLAYREADY_Decrypt(pstPRMember->hPlayReady, &DecryptParam);
    if (s32Ret != HI_SUCCESS)
    {
        dash_log(DASH_LOG_ERROR, "Decrypt:HI_PLAYREADY_Decrypt failed!\n");
        goto playready_decrypt_fail;
    }

    if (iv->use_subsample)
    {
        _SVR_DASH_PlayReady_Decompose_Data(pkt, pu8Data);
    }

    return HI_SUCCESS;

playready_decrypt_fail:
    HI_PLAYREADY_Close(pstPRMember->hPlayReady);
    return HI_FAILURE;
}

#endif

static inline  HI_BOOL _SVR_DASH_PeriodIsMatch(IPeriod *period, DASHPeriod *pstToBeMatchedAttr)
{
    HI_BOOL bMatched = HI_FALSE;
    HI_S32   s32Len;
    char     id[DASH_ATTR_STR_LEN];
    char     start[DASH_ATTR_STR_LEN];
    char     duration[DASH_ATTR_STR_LEN];

    snprintf(id, sizeof(id), "%s", period->GetId().c_str());
    snprintf(start, sizeof(start), "%s", period->GetStart().c_str());
    snprintf(duration, sizeof(duration), "%s", period->GetDuration().c_str());

    if (strlen(id) > 0)
    {
        if (STRING_MATCH(id, pstToBeMatchedAttr->id))
        {
            bMatched = HI_TRUE;
        }
    }

    if (bMatched == HI_FALSE)
    {
        if (STRING_MATCH(start, pstToBeMatchedAttr->start) &&
            STRING_MATCH(duration, pstToBeMatchedAttr->duration))
        {
            bMatched = HI_TRUE;
        }
    }

    if (bMatched == HI_TRUE)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] matched  period   is @id=%s, @start=%s, @duration=%s\n",
            __FUNCTION__, __LINE__, period->GetId().c_str(), period->GetStart().c_str(), period->GetDuration().c_str());
    }

    return bMatched;
}

static HI_S32 _SVR_DASH_FindCurrentPeriod(DASHMember * pstMember, IPeriod **ppstPeriod, HI_BOOL *pbChanged)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    IPeriod *period = NULL;
    HI_U32 u32PeriodNum = manager->GetMPD()->GetPeriods().size();
    HI_U32 i;

    *ppstPeriod = NULL;
    *pbChanged = HI_FALSE;

    if (u32PeriodNum <= 0)
    {
        dash_log(DASH_LOG_ERROR, "[%s, %d] no periods found in mpd\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    for (i = 0; i < u32PeriodNum; i ++)
    {
        period = manager->GetMPD()->GetPeriods().at(i);
        if (HI_TRUE == _SVR_DASH_PeriodIsMatch(period, &pstMember->stCurPeriod))
        {
            break;
        }
    }

    if (i == u32PeriodNum)
    {
            dash_log(DASH_LOG_ERROR, "[%s, %d] no periods matched, return period 0\n", __FUNCTION__, __LINE__);
            period = manager->GetMPD()->GetPeriods().at(0);
            *pbChanged = HI_TRUE;
    }

    *ppstPeriod = period;

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_FindNextPeriod(DASHMember * pstMember, IPeriod **ppstPeriod)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    IPeriod *period = NULL;
    HI_U32 u32PeriodNum = manager->GetMPD()->GetPeriods().size();
    HI_U32 i;

    *ppstPeriod = NULL;

    if (u32PeriodNum <= 0)
    {
        dash_log(DASH_LOG_ERROR, "[%s, %d] no periods found in mpd\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    for (i = 0; i < u32PeriodNum; i ++)
    {
        period = manager->GetMPD()->GetPeriods().at(i);
        if (HI_TRUE == _SVR_DASH_PeriodIsMatch(period, &pstMember->stCurPeriod))
        {
            period = NULL;
            break;
        }
    }

    if (i < u32PeriodNum)
    {
        if (i + 1 < u32PeriodNum)
        {
            period = manager->GetMPD()->GetPeriods().at(i + 1);
            dash_log(DASH_LOG_ERROR, "[%s, %d] next period found\n", __FUNCTION__, __LINE__);
        }
    }
    else
    {
            dash_log(DASH_LOG_ERROR, "[%s, %d] no period matched, return the fist period\n", __FUNCTION__, __LINE__);
            period = manager->GetMPD()->GetPeriods().at(0);
    }

    if (period != NULL)
    {
        *ppstPeriod = period;
    }
    else
    {
         dash_log(DASH_LOG_ERROR, "[%s, %d] next period not found\n", __FUNCTION__, __LINE__);
         return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_SetAdaptationset(DASHMember * pstMember, HI_DASH_STREAM_INFO_S * pstStreamInfo)
{
    HI_BOOL bVidSet = HI_FALSE, bAudSet = HI_FALSE, bSubSet = HI_FALSE;

    pthread_mutex_lock(&pstMember->mUserStreamInfoLock);
    if (pstStreamInfo->s32VidIndex >= 0 &&
        pstMember->s32VideoAdaptationSetIndex != pstStreamInfo->s32VidIndex &&
        pstStreamInfo->s32VidIndex < pstMember->vid_nb)
    {
        pstMember->stUserSetStreamInfo.s32VidIndex = pstStreamInfo->s32VidIndex;
    //    pstMember->s32VideoAdaptationSetIndex = pstStreamInfo->s32VidIndex;
        bVidSet = HI_TRUE;
    }
    else if (pstStreamInfo->s32VidIndex < 0 || pstStreamInfo->s32VidIndex >= pstMember->vid_nb)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] user set video adaptionset index invalid %d, correct scope is[0~%u)\n",
            __FUNCTION__, __LINE__, pstStreamInfo->s32VidIndex, pstMember->vid_nb);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] user set video adaptionset index %d is the same with current value, not changed.\n",
            __FUNCTION__, __LINE__, pstStreamInfo->s32VidIndex);
    }

    if (pstStreamInfo->s32AudIndex >= 0 &&
        pstMember->s32AudioAdaptationSetIndex != pstStreamInfo->s32AudIndex &&
        pstStreamInfo->s32AudIndex < pstMember->aud_nb)
    {
        pstMember->stUserSetStreamInfo.s32AudIndex = pstStreamInfo->s32AudIndex;
       // pstMember->s32AudioAdaptationSetIndex = pstStreamInfo->s32AudIndex;
        bAudSet = HI_TRUE;
    }
    else if (pstStreamInfo->s32AudIndex < 0 || pstStreamInfo->s32AudIndex >= pstMember->aud_nb)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] user set audio adaptionset index invalid %d, correct scope is[0~%u)\n",
            __FUNCTION__, __LINE__, pstStreamInfo->s32AudIndex, pstMember->aud_nb);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] user set audio adaptionset index %d is the same with current value, not changed.\n",
            __FUNCTION__, __LINE__, pstStreamInfo->s32AudIndex);
    }

    if (pstStreamInfo->s32SubIndex >= 0 &&
        pstMember->s32SubtitleAdaptationSetIndex != pstStreamInfo->s32SubIndex &&
        pstStreamInfo->s32SubIndex < pstMember->sub_nb)
    {
        pstMember->stUserSetStreamInfo.s32SubIndex = pstStreamInfo->s32SubIndex;
      //  pstMember->s32SubtitleAdaptationSetIndex = pstStreamInfo->s32SubIndex;
        bSubSet = HI_TRUE;
    }
    else if (pstStreamInfo->s32SubIndex < 0 || pstStreamInfo->s32SubIndex >= pstMember->sub_nb)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] user set subtitle adaptionset index invalid %d, correct scope is[0~%u)\n",
            __FUNCTION__, __LINE__, pstStreamInfo->s32SubIndex, pstMember->sub_nb);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] user set subtitle adaptionset index %d is the same with current value, not changed.\n",
            __FUNCTION__, __LINE__, pstStreamInfo->s32SubIndex);
    }

    if (bVidSet == HI_TRUE || bAudSet == HI_TRUE || bSubSet == HI_TRUE)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] user set adaptionset index to (video %d, audio %d, subtitle %d) success.\n",
            __FUNCTION__, __LINE__, pstMember->stUserSetStreamInfo.s32VidIndex,
            pstMember->stUserSetStreamInfo.s32AudIndex, pstMember->stUserSetStreamInfo.s32SubIndex);
        pthread_mutex_unlock(&pstMember->mUserStreamInfoLock);
        return HI_SUCCESS;
    }

    pthread_mutex_unlock(&pstMember->mUserStreamInfoLock);

    return HI_FAILURE;
}

static inline HI_BOOL _SVR_DASH_CheckAdaptationSetChanged(DASHMember * pstMember)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    HI_S32 s32RepresentationIndex;
    HI_BOOL bChanged = HI_FALSE;

    if (manager == NULL || !manager->IsStarted())
        return HI_FALSE;

    pthread_mutex_lock(&pstMember->mUserStreamInfoLock);

    if (pstMember->stUserSetStreamInfo.s32VidIndex >= 0 &&
        pstMember->s32VideoAdaptationSetIndex != pstMember->stUserSetStreamInfo.s32VidIndex)
    {
        //switch to lowest bandwidth representation
        s32RepresentationIndex= _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_VIDEO, pstMember->s32VideoAdaptationSetIndex, 0);
        if (s32RepresentationIndex != pstMember->s32VideoRepresentationIndex && pstMember->bVideoChangePresenFinish == HI_TRUE)
            _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_VIDEO, pstMember->s32VideoAdaptationSetIndex, s32RepresentationIndex, HI_FALSE);

        pstMember->s32VideoAdaptationSetIndex = pstMember->stUserSetStreamInfo.s32VidIndex;
        pstMember->s32VideoRepresentationIndex = manager->GetVideoCurrentPresentationIndex(pstMember->s32VideoAdaptationSetIndex);
        _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_VIDEO, pstMember->s32VideoAdaptationSetIndex, pstMember->s32VideoRepresentationIndex, HI_FALSE);
        bChanged = HI_TRUE;
    }

    if (pstMember->stUserSetStreamInfo.s32AudIndex >= 0 &&
        pstMember->s32AudioAdaptationSetIndex != pstMember->stUserSetStreamInfo.s32AudIndex)
    {
        //switch to lowest bandwidth representation
        s32RepresentationIndex= _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_AUDIO, pstMember->s32AudioAdaptationSetIndex, 0);
        if (s32RepresentationIndex != pstMember->s32AudioRepresentationIndex && pstMember->bAudioChangePresenFinish == HI_TRUE)
            _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_AUDIO, pstMember->s32AudioAdaptationSetIndex, s32RepresentationIndex, HI_FALSE);

        pstMember->s32AudioAdaptationSetIndex = pstMember->stUserSetStreamInfo.s32AudIndex;
        pstMember->s32AudioRepresentationIndex = manager->GetAudioCurrentPresentationIndex(pstMember->s32AudioAdaptationSetIndex);
        _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_AUDIO, pstMember->s32AudioAdaptationSetIndex, pstMember->s32AudioRepresentationIndex, HI_FALSE);
        bChanged = HI_TRUE;
    }

    if (pstMember->stUserSetStreamInfo.s32SubIndex >= 0 &&
        pstMember->s32SubtitleAdaptationSetIndex != pstMember->stUserSetStreamInfo.s32SubIndex)
    {
        //switch to lowest bandwidth representation
        s32RepresentationIndex= _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_SUBTITLE, pstMember->s32SubtitleAdaptationSetIndex, 0);
        if (s32RepresentationIndex != pstMember->s32SubtitleRepresentationIndex && pstMember->bSubtitleChangePresenFinish == HI_TRUE)
            _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_SUBTITLE, pstMember->s32SubtitleAdaptationSetIndex, s32RepresentationIndex, HI_FALSE);

        pstMember->s32SubtitleAdaptationSetIndex = pstMember->stUserSetStreamInfo.s32SubIndex;
        pstMember->s32SubtitleRepresentationIndex = manager->GetSubtitleCurrentPresentationIndex(pstMember->s32SubtitleAdaptationSetIndex);
        _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_SUBTITLE, pstMember->s32SubtitleAdaptationSetIndex, pstMember->s32SubtitleRepresentationIndex, HI_FALSE);
        bChanged = HI_TRUE;
    }

    pstMember->stUserSetStreamInfo.s32VidIndex = -1;
    pstMember->stUserSetStreamInfo.s32AudIndex = -1;
    pstMember->stUserSetStreamInfo.s32SubIndex = -1;

    pthread_mutex_unlock(&pstMember->mUserStreamInfoLock);

    if (bChanged == HI_TRUE)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] adaptionset index changed to (Video=%d, Audio=%d, Subtitle=%d)\n",
            __FUNCTION__, __LINE__, pstMember->s32VideoAdaptationSetIndex,
            pstMember->s32AudioAdaptationSetIndex, pstMember->s32SubtitleAdaptationSetIndex);
    }

    return bChanged;
}

static HI_BOOL _SVR_DASH_CheckSingleSegmentSwitchable(DASHMember * pstMember, AVMediaType type)
{
    HI_S32 i, rep_count;
    HI_S32 s32AdaptionSetIndex;
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;

    if (type == AVMEDIA_TYPE_VIDEO)
    {
        s32AdaptionSetIndex = pstMember->s32VideoAdaptationSetIndex;
        if (pstMember->vid_nb <= 0 || s32AdaptionSetIndex < 0 ||
            s32AdaptionSetIndex >= pstMember->vid_nb)
        {
            return HI_FALSE;
        }
        rep_count = pstMember->stCurPeriod.videoAdaptionsets.at(s32AdaptionSetIndex).representationsSidxinfo.size();
        if (rep_count < 2)
            return HI_FALSE;
        for (i = 0; i < rep_count; i++)
        {
            if (pstMember->stCurPeriod.videoAdaptionsets.at(s32AdaptionSetIndex).representationsSidxinfo.at(i) == NULL)
                return HI_FALSE;
        }

        return HI_TRUE;
    }

    else if (type == AVMEDIA_TYPE_AUDIO)
    {
        s32AdaptionSetIndex = pstMember->s32AudioAdaptationSetIndex;
        if (pstMember->aud_nb <= 0 || s32AdaptionSetIndex < 0 ||
            s32AdaptionSetIndex >= pstMember->aud_nb)
        {
            return HI_FALSE;
        }
        rep_count = pstMember->stCurPeriod.audioAdaptionsets.at(s32AdaptionSetIndex).representationsSidxinfo.size();
        if (rep_count < 2)
            return HI_FALSE;
        for (i = 0; i < rep_count; i++)
        {
            if (pstMember->stCurPeriod.audioAdaptionsets.at(s32AdaptionSetIndex).representationsSidxinfo.at(i) == NULL)
                return HI_FALSE;
        }

        return HI_TRUE;
    }

    else if (type == AVMEDIA_TYPE_SUBTITLE)
    {
        s32AdaptionSetIndex = pstMember->s32SubtitleAdaptationSetIndex;
        if (pstMember->sub_nb <= 0 || s32AdaptionSetIndex < 0 ||
            s32AdaptionSetIndex >= pstMember->sub_nb)
        {
            return HI_FALSE;
        }
        rep_count = pstMember->stCurPeriod.subtitleAdaptionsets.at(s32AdaptionSetIndex).representationsSidxinfo.size();
        if (rep_count < 2)
            return HI_FALSE;
        for (i = 0; i < rep_count; i++)
        {
            if (pstMember->stCurPeriod.subtitleAdaptionsets.at(s32AdaptionSetIndex).representationsSidxinfo.at(i) == NULL)
                return HI_FALSE;
        }

        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL _SVR_DASH_ISOFFBandWidthChg(DASHMember * pstMember, AVMediaType eMediaType)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    HI_U32 u32VideoPosition = 0;
    HI_U32 u32AudioPosition = 0;
    HI_S64 s64FirstPts = 0;
    HI_U32 u32SubtitlePosition  = 0;
    HI_BOOL bChanged = HI_FALSE;
    AVStream * st = NULL;

    if (HI_TRUE != pstMember->bSetupFinish)
        return bChanged;

    if (pstMember->eRepresentationType == SINGLE_MEDIA_SEGMENT &&
        HI_TRUE != _SVR_DASH_CheckSingleSegmentSwitchable(pstMember, eMediaType))
    {
        return HI_FALSE;
    }

    bChanged = _SVR_DASH_CheckRepresentationChanged(pstMember, eMediaType);

    return bChanged;
    #if 0
    else
    {
        switch(eMediaType)
        {
            case AVMEDIA_TYPE_VIDEO:
                u32VideoPosition = pstMember->u32VideoPosition + pkt->size;
                s32Ret = _SVR_DASH_CheckIndexChanged(pstMember->pVideoSidxInfo, u32VideoPosition, pstMember->u32VideoPosition, &pstMember->s32SubSegmentIndex);
                if (HI_FAILURE == s32Ret)
                    pstMember->u32VideoPosition = u32VideoPosition;
                else
                    pstMember->s64VideoFirstPts = pkt->pts;
                break;
            case AVMEDIA_TYPE_AUDIO:
                u32AudioPosition = pstMember->u32AudioPosition + pkt->size;
                s32Ret = _SVR_DASH_CheckIndexChanged(pstMember->pAudioSidxInfo, u32AudioPosition, pstMember->u32AudioPosition, &pstMember->s32SubSegmentIndex);
                if (HI_FAILURE == s32Ret)
                    pstMember->u32AudioPosition = u32AudioPosition;
                else
                    pstMember->s64AudioFirstPts = pkt->pts;
                break;
            case AVMEDIA_TYPE_SUBTITLE:
                u32SubtitlePosition = pstMember->u32SubtitlePosition += pkt->size;
                s32Ret = _SVR_DASH_CheckIndexChanged(pstMember->pSubtitleSidxInfo, u32SubtitlePosition, pstMember->u32SubtitlePosition, &pstMember->s32SubSegmentIndex);
                if (HI_FAILURE == s32Ret)
                    pstMember->u32SubtitlePosition = u32SubtitlePosition;
                else
                    pstMember->s64SubtitleFirstPts = pkt->pts;
                break;
            default:
                s32Ret = HI_FAILURE;
                break;
        }

        if (HI_SUCCESS == s32Ret)
        {
            s32Ret = _SVR_DASH_CheckRepresentationChanged(pstMember ,eMediaType);
            if (HI_SUCCESS == s32Ret)
            {
                if (HI_TRUE == pstMember->bVideoRepresentationChanged)
                {
                    manager->SetVideoPosition(0);
                    manager->SetQuality();
                    _SVR_DASH_Setup(pstMember);

                    _SVR_DASH_BuildIndex(pstMember);
                    u32VideoPosition = (HI_U32)pstMember->pVideoSidxInfo->index_entries[pstMember->s32SubSegmentIndex].pos;

                    manager->SetVideoPosition(u32VideoPosition);
                    manager->SetQuality();

                    ff_read_frame_flush(pstMember->vid_ic[pstMember->s32VideoAdaptationSetIndex]);
                    pstMember->vid_ic[pstMember->s32VideoAdaptationSetIndex]->pb = (AVIOContext *)manager->GetVideoAVIOContext(pstMember->s32VideoAdaptationSetIndex);
                    std::stringstream ss;
                    std::string s;
                    ss << pstMember->s32SubSegmentIndex;
                    ss >> s;
                    av_opt_set(pstMember->vid_ic[pstMember->s32VideoAdaptationSetIndex]->priv_data, "current_sample", s.c_str(), 0);
                    //_SVR_DASH_Setup(pstMember);
                }
                //do the same with audio and subtitle

                if (HI_TRUE == pstMember->bAudioRepresentationChanged)
                {
                    manager->SetAudioPosition(0);
                    manager->SetQuality();
                    _SVR_DASH_Setup(pstMember);

                    _SVR_DASH_BuildIndex(pstMember);
                    u32AudioPosition = (HI_U32)pstMember->pAudioSidxInfo->index_entries[pstMember->s32SubSegmentIndex].pos;

                    manager->SetAudioPosition(u32AudioPosition);
                    manager->SetQuality();

                    ff_read_frame_flush(pstMember->aud_ic[pstMember->s32AudioAdaptationSetIndex]);
                    pstMember->aud_ic[pstMember->s32AudioAdaptationSetIndex]->pb = (AVIOContext *)manager->GetAudioAVIOContext(pstMember->s32AudioAdaptationSetIndex);
                    std::stringstream ss;
                    std::string s;
                    ss << pstMember->s32SubSegmentIndex;
                    ss >> s;
                    av_opt_set(pstMember->aud_ic[pstMember->s32AudioAdaptationSetIndex]->priv_data, "current_sample", s.c_str(), 0);
                    //_SVR_DASH_Setup(pstMember);
                }

                if (HI_TRUE == pstMember->bSubtitleRepresentationChanged)
                {

                }

                av_free_packet(pkt);
                goto retry;
            }
        }

    }
    #endif

    return bChanged;
}

#if 0
static HI_S32 _SVR_DASH_TSBandWidthChg(DASHMember * pstMember, AVPacket * pkt, AVMediaType eMediaType)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    HI_U32 u32VideoPosition = 0;
    HI_U32 u32AudioPosition = 0;
    HI_S64 s64VideoLastPts = 0;
    HI_S64 s64VideoFirstPts = 0;
    HI_U32 u32SubtitlePosition  = 0;
    HI_S32 s32Ret;
    AVStream * st;

    if (HI_TRUE != pstMember->bSetupFinish)
        return HI_FAILURE;

    //MPEG2-TS Format multi segment
    if (pstMember->eRepresentationType == SEGMENT_LIST
        || pstMember->eRepresentationType == SEGMENT_TEMPLATE)
    {
        u32VideoPosition = manager->GetVideoPosition();

        if (pstMember->u32VideoPosition < u32VideoPosition)
        {
            pstMember->u32VideoPosition = u32VideoPosition;
            s32Ret = _SVR_DASH_CheckRepresentationChanged(pstMember, AVMEDIA_TYPE_VIDEO);

            if (HI_SUCCESS == s32Ret)
            {
                s32Ret = _SVR_DASH_Setup(pstMember);
                if (HI_FAILURE == s32Ret)
                    return AVERROR_DEMUXER_NOT_FOUND;

                av_free_packet(pkt);
                return HI_SUCCESS;
            }
        }
    }
    else
    {
        //Use the  Video PTS
        s32Ret = HI_FAILURE;
        st = pstMember->vid_ic[pstMember->s32VideoAdaptationSetIndex]->streams[pkt->stream_index];

        if (st->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            if (st->time_base.den != 0 && st->time_base.num != 0)
            {
                s64VideoFirstPts
                    = pstMember->s64VideoFirstPts * st->time_base.den / (1000 * st->time_base.num);

                if (0 == pstMember->s64VideoLastPts)
                {
                    s64VideoLastPts = s64VideoFirstPts + pkt->duration;
                    pstMember->s64VideoLastPts
                        = s64VideoLastPts * 1000 * st->time_base.num / st->time_base.den;
                }
                else
                {
                    s64VideoLastPts
                        = pstMember->s64VideoLastPts * st->time_base.den / (1000 * st->time_base.num);
                }
            }

            s32Ret = _SVR_DASH_CheckIndexChanged(pstMember->pVideoSidxInfo, s64VideoLastPts,
                s64VideoFirstPts,&pstMember->s32SubSegmentIndex);
            pstMember->s64VideoFirstPts = pstMember->s64VideoLastPts;
        }

        if (HI_SUCCESS == s32Ret)
        {
            s32Ret = _SVR_DASH_CheckRepresentationChanged(pstMember, AVMEDIA_TYPE_VIDEO);
            if (HI_SUCCESS == s32Ret)
            {
                s32Ret = _SVR_DASH_BuildIndex(pstMember);
                if (HI_FAILURE == s32Ret)
                    return s32Ret;

                u32VideoPosition
                    = (HI_U32)pstMember->pVideoSidxInfo->index_entries[pstMember->s32SubSegmentIndex].pos;
                manager->SetVideoPosition(pstMember->s32VideoAdaptationSetIndex, u32VideoPosition);
                manager->SetQuality();

                s32Ret = _SVR_DASH_Setup(pstMember);
                if (HI_FAILURE == s32Ret)
                    return AVERROR_DEMUXER_NOT_FOUND;

                av_free_packet(pkt);
                return HI_SUCCESS;
            }
        }
    }

    return HI_FAILURE;
}
#endif

static HI_BOOL _SVR_DASH_CheckBandWidthChanged(DASHMember * pstMember, HI_BOOL bForce, AVMediaType eForceType)
{
    HI_BOOL bChanged = HI_FALSE;
    HI_S64 s64CurTime = av_gettime();
    HI_BOOL bVidNeedCheck = HI_FALSE;
    HI_BOOL bAudNeedCheck = HI_FALSE;
    HI_BOOL bSubNeedCheck = HI_FALSE;
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;

    if (pstMember->bSetupFinish == HI_FALSE)
        return bChanged;

    if (bForce == HI_FALSE && (av_gettime() - pstMember->s64LastCheckBWTime) < DASH_BW_CHECK_CYCLE)
        return bChanged;

    if (pstMember->vid_nb > 0 &&
        manager->GetVideoAdaptionSet(pstMember->s32VideoAdaptationSetIndex)->GetRepresentation().size() > 1)
    {
        bVidNeedCheck = HI_TRUE;
    }

    if (pstMember->aud_nb > 0 &&
        manager->GetAudioAdaptionSet(pstMember->s32AudioAdaptationSetIndex)->GetRepresentation().size() > 1)
    {
        bAudNeedCheck = HI_TRUE;
    }

    if (pstMember->sub_nb > 0 &&
        manager->GetSubtitleAdaptionSet(pstMember->s32SubtitleAdaptationSetIndex)->GetRepresentation().size() > 1)
    {
        bSubNeedCheck = HI_TRUE;
    }

    if (bVidNeedCheck == HI_FALSE && bAudNeedCheck == HI_FALSE && bSubNeedCheck == HI_FALSE)
    {
        pstMember->s64LastCheckBWTime = av_gettime();
        return HI_FALSE;
    }

    if (bForce == HI_FALSE)
    {
        switch(pstMember->eLastCheckBWType)
        {
            case AVMEDIA_TYPE_VIDEO:
                if (bAudNeedCheck == HI_TRUE)
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_AUDIO;
                else if (bSubNeedCheck == HI_TRUE)
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_SUBTITLE;
                else
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_VIDEO;
                break;
            case AVMEDIA_TYPE_AUDIO:
                if (bSubNeedCheck == HI_TRUE)
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_SUBTITLE;
                else if (bVidNeedCheck == HI_TRUE)
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_VIDEO;
                else
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_AUDIO;
                break;
            case AVMEDIA_TYPE_SUBTITLE:
            case AVMEDIA_TYPE_UNKNOWN:
            default:
                if (bVidNeedCheck == HI_TRUE)
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_VIDEO;
                else if (bAudNeedCheck == HI_TRUE)
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_AUDIO;
                else if (bSubNeedCheck == HI_TRUE)
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_SUBTITLE;
                break;
        }
    }
    else
    {
        switch (eForceType)
        {
            case AVMEDIA_TYPE_VIDEO:
                if (bVidNeedCheck == HI_FALSE)
                    return HI_FALSE;
                else
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_VIDEO;
                break;
            case AVMEDIA_TYPE_AUDIO:
                if (bAudNeedCheck == HI_FALSE)
                    return HI_FALSE;
                else
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_AUDIO;
                break;
            case AVMEDIA_TYPE_SUBTITLE:
                if (bSubNeedCheck == HI_FALSE)
                    return HI_FALSE;
                else
                    pstMember->eLastCheckBWType = AVMEDIA_TYPE_SUBTITLE;
                break;
            default:
                return HI_FALSE;
        }
    }

    if (pstMember->eLastCheckBWType != AVMEDIA_TYPE_VIDEO &&
        pstMember->eLastCheckBWType != AVMEDIA_TYPE_AUDIO &&
        pstMember->eLastCheckBWType != AVMEDIA_TYPE_SUBTITLE)
        return HI_FALSE;

    dash_log(DASH_LOG_ERROR, "[%s,%d][BW] start to check bandwidth, type %d....\n", __FUNCTION__, __LINE__, pstMember->eLastCheckBWType);

    if (pstMember->bIsISOFF)
    {
        bChanged = _SVR_DASH_ISOFFBandWidthChg(pstMember, pstMember->eLastCheckBWType);
    }
    else
    {
       // s32Ret = _SVR_DASH_TSBandWidthChg(pstMember, pkt, eMediaType);
    }

    pstMember->s64LastCheckBWTime = av_gettime();
    if (bChanged != HI_TRUE)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][BW] resentation not changed, type %d.\n", __FUNCTION__, __LINE__, pstMember->eLastCheckBWType);
    }

    return bChanged;
}

static HI_S32 _SVR_DASH_ParseSubPacket(DASHMember * pstMember, AVPacket *pkt, SubtitleType eSubtitleType)
{
    AVPacket *ttml_pkt = NULL;
    AVIOContext *pb = NULL;
    HI_U8 *u8Data = NULL;
    HI_S32 s32DataSize = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    switch(eSubtitleType)
    {
        case Subtitle_TTML:
            if (NULL == pstMember->ttml_ic[pstMember->sub_index] || NULL == pstMember->ttml_ic[pstMember->sub_index]->pb);
                return HI_FAILURE;

            pb = pstMember->ttml_ic[pstMember->sub_index]->pb;

            //Read ttml packet
            ffio_init_context(pb, pkt->data, pkt->size, 0, NULL, NULL, NULL, NULL);
            s32Ret = av_read_packet(pstMember->ttml_ic[pstMember->sub_index], pkt);
            if (s32Ret < 0)
            {
                av_free_packet(ttml_pkt);
            }
            break;
        case Subtitle_TX3G:
            if (pkt->size <= 2 || !pkt->data)
            {
                s32Ret = HI_FAILURE;
                break;
            }

            //The first two bytes of the packet are the length of the text string
            u8Data = (HI_U8 *)av_mallocz(pkt->size - 2);
            s32DataSize = pkt->size - 2;
            if (NULL == u8Data)
            {
                s32Ret = HI_FAILURE;
                break;
            }

            memcpy(u8Data, pkt->data + 2, s32DataSize);
            av_free(pkt->data);

            pkt->data = u8Data;
            pkt->size = s32DataSize;
            break;
        default:
            dash_log(DASH_LOG_ERROR, "DASH Unsupported subtitle type!\n");
            break;
    }
    return s32Ret;
}

static HI_S32 _SVR_DASH_ReadAudFrame(DASHMember * pstMember, AVPacket * pkt)
{
    HI_S64 *ps64LastPts = NULL;
    HI_S64  s64LastPts = 0;
    HI_S32  s32Ret = HI_SUCCESS, i;
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;

    pstMember->u32ATryRead ++;

    if (pstMember->aud_index == pstMember->aud_nb)
        pstMember->aud_index = 0;

    if (pstMember->aud_ic[pstMember->aud_index] == NULL)
    {
        for (i = pstMember->aud_index + 1; i < pstMember->aud_nb; i++)
        {
            if (pstMember->aud_ic[i] != NULL)
            {
                pstMember->aud_index = i;
                break;
            }
        }
        if (pstMember->aud_ic[pstMember->aud_index] == NULL)
        {
            for (i = 0; i < pstMember->aud_index; i++)
            {
                if (pstMember->aud_ic[i] != NULL)
                {
                    pstMember->aud_index = i;
                    break;
                }
            }
        }

        if (pstMember->aud_ic[pstMember->aud_index] == NULL)
        {
            dash_log(DASH_LOG_ERROR, "avformat context is null, set audio eos reached.\n");
            pstMember->bAudioEosReached = HI_TRUE;
            return HI_FAILURE;
        }
    }

    ps64LastPts = (pstMember->aud_index == pstMember->s32AudioAdaptationSetIndex) ? &(pstMember->s64AudioLastPts) : &s64LastPts;
    s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->aud_ic[pstMember->aud_index], pkt, ps64LastPts);

    if (s32Ret < 0)
    {
        //check eos type now
        DASHIOMap *map = (DASHIOMap *)(pstMember->aud_ic[pstMember->aud_index]->pb->opaque);;
        if (map->eos == DASHIO_EOS_PRESENTATION_CHANGED)
        {
            HI_S64 s64EarlistPts = (pstMember->s64AudioLastPts > pstMember->s64AudioFirstPts && \
                (pstMember->s64AudioFirstPts >= 0))?(pstMember->s64VideoLastPts - pstMember->s64AudioFirstPts):0;
            Option stOption = {1, map->param.representation_index, s64EarlistPts};

            dash_log(DASH_LOG_ERROR, "[%s,%d][BW] audio[%d] map[%p] pb=%p adaptionset_index=%d,rep_index changed to %d ,reopen the avformat!\n",
                __FUNCTION__, __LINE__, pstMember->aud_index, map, map->param.libavdecoder_pb, map->param.adaptionset_index, map->param.representation_index);

           // if (pstMember->aud_index == pstMember->s32AudioAdaptationSetIndex)
           //     stOption.representation_index = pstMember->s32AudioRepresentationIndex;

            if (HI_SUCCESS == _SVR_DASH_SetupContext(pstMember, &(pstMember->aud_ic[pstMember->aud_index]),
                 NULL, map->param.libavdecoder_pb, &stOption, HI_FALSE, AVMEDIA_TYPE_AUDIO, pstMember->aud_index, map->param.representation_index))
            {
                s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->aud_ic[pstMember->aud_index], pkt, ps64LastPts);
                pstMember->bAudioChangePresenFinish = HI_TRUE;
            }
            else
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d][BW] audio[%d] setup context return error!\n", __FUNCTION__, __LINE__,  pstMember->aud_index);
            }
            pstMember->bForcePrint = HI_TRUE;
        }
    }

    if ((HI_FAILURE == s32Ret) && (pstMember->aud_index == pstMember->s32AudioAdaptationSetIndex))
    {
        //manager may be updated during _SVR_DASH_ReadPacket, must update it when refer to it.
        manager = (MultimediaManager *)pstMember->manager;
        dash_log(DASH_LOG_ERROR, "audio eos reached, current pos:%u\n", ((manager != NULL)?manager->GetAudioPosition(pstMember->aud_index):0));
        pstMember->bAudioEosReached = HI_TRUE;
        return s32Ret;
    }

    if ((HI_FAILURE == s32Ret) || \
        (s64LastPts >= pstMember->s64AudioLastPts) || \
        (pstMember->aud_index == pstMember->s32AudioAdaptationSetIndex))
    {
        /*
         * 1.We need the EOS from the selected stream, the 'FAILURE' here is not used
         * 2.Read other stream when current stream pts is larger than the selected stream
         * 3.When the stream is the selected one, just read the other
         */
        pstMember->aud_index++;
    }

    if (HI_SUCCESS == s32Ret)
    {
        if (pstMember->s64AudioFirstPts == AV_NOPTS_VALUE)
        {
            pstMember->s64AudioFirstPts = pstMember->s64AudioLastPts;
        }

        if (pstMember->s64AudioFirstPts == AV_NOPTS_VALUE)
        {
            pstMember->s64AudioFirstPts = 0;
        }
    }
    pstMember->u32AReadOKCount ++;

    return s32Ret;
}

static HI_S32 _SVR_DASH_ReadVidFrame(DASHMember * pstMember, AVPacket * pkt)
{
    HI_S64 *ps64LastPts = NULL;
    HI_S32  s32Ret = HI_SUCCESS, i;
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;

    if (pstMember->vid_index == pstMember->vid_nb)
        pstMember->vid_index = 0;

    pstMember->u32VTryRead ++;

    if (pstMember->vid_ic[pstMember->vid_index] == NULL)
    {
        for (i = pstMember->vid_index + 1; i < pstMember->vid_nb; i++)
        {
            if (pstMember->vid_ic[i] != NULL)
            {
                pstMember->vid_index = i;
                break;
            }
        }
        if (pstMember->vid_ic[pstMember->vid_index] == NULL)
        {
            for (i = 0; i < pstMember->vid_index; i++)
            {
                if (pstMember->vid_ic[i] != NULL)
                {
                    pstMember->vid_index = i;
                    break;
                }
            }
        }

        if (pstMember->vid_ic[pstMember->vid_index] == NULL)
        {
            dash_log(DASH_LOG_ERROR, "avformat context is null, set video eos reached.\n");
            pstMember->bVideoEosReached = HI_TRUE;
            return HI_FAILURE;
        }
    }

    ps64LastPts = (pstMember->vid_index == pstMember->s32VideoAdaptationSetIndex)
        ? &(pstMember->s64VideoLastPts) : NULL;
    s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->vid_ic[pstMember->vid_index], pkt, ps64LastPts);

    if (s32Ret < 0)
    {
        //check eos type now
        DASHIOMap *map = (DASHIOMap *)(pstMember->vid_ic[pstMember->vid_index]->pb->opaque);
        if (map->eos == DASHIO_EOS_PRESENTATION_CHANGED)
        {
            HI_S64 s64EarlistPts = (pstMember->s64VideoLastPts > pstMember->s64VideoFirstPts && \
                (pstMember->s64VideoFirstPts >= 0))?(pstMember->s64VideoLastPts - pstMember->s64VideoFirstPts):0;
            Option stOption = {1, map->param.representation_index, s64EarlistPts};

            dash_log(DASH_LOG_ERROR, "[%s,%d][BW] map[%p] video[%d]  pb=%p, adaptionset_index=%d rep_index changed to %d!\n",
                __FUNCTION__, __LINE__, map, pstMember->vid_index, map->param.libavdecoder_pb, map->param.adaptionset_index, map->param.representation_index);

            //if (pstMember->vid_index == pstMember->s32VideoAdaptationSetIndex)
            //    stOption.representation_index = pstMember->s32VideoRepresentationIndex;

            if (HI_SUCCESS == _SVR_DASH_SetupContext(pstMember, &(pstMember->vid_ic[pstMember->vid_index]),
                  NULL, map->param.libavdecoder_pb, &stOption, HI_FALSE, AVMEDIA_TYPE_VIDEO, pstMember->vid_index, map->param.representation_index))
            {
                pstMember->bFirstFrame = HI_TRUE;//:TODO: ,maybe differ for each adaptionset?
                s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->vid_ic[pstMember->vid_index], pkt, ps64LastPts);
                pstMember->bVideoChangePresenFinish = HI_TRUE;
            }
            else
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d][BW] video[%d] setup context return error!\n", __FUNCTION__, __LINE__,  pstMember->vid_index);
            }
            pstMember->bForcePrint = HI_TRUE;
        }
    }

    if ((HI_FAILURE == s32Ret) && (pstMember->vid_index == pstMember->s32VideoAdaptationSetIndex))
    {
        //manager may be updated during _SVR_DASH_ReadPacket, must update it when refer to it.
        manager = (MultimediaManager *)pstMember->manager;
        dash_log(DASH_LOG_ERROR, "video eos reached, current pos:%u\n", ((manager != NULL)?manager->GetVideoPosition(pstMember->vid_index):0));
        pstMember->bVideoEosReached = HI_TRUE;
        return s32Ret;
    }

    if (HI_SUCCESS == s32Ret)
    {
        if (pstMember->bFirstFrame == HI_TRUE)
        {
            pstMember->bFirstFrame == HI_FALSE;
            pkt->flags |= AV_PKT_FLAG_KEY;
        }

        if (pstMember->s64VideoFirstPts == AV_NOPTS_VALUE)
        {
            pstMember->s64VideoFirstPts = pstMember->s64VideoLastPts;
        }

        if (pstMember->s64VideoFirstPts == AV_NOPTS_VALUE)
        {
            pstMember->s64VideoFirstPts = 0;
        }
    }
    pstMember->vid_index++;
    pstMember->u32VReadOKCount ++;

    return s32Ret;
}

static inline HI_BOOL _SVR_DASH_CheckSubtitleRepresentationChanged(DASHMember * pstMember,
                                              AVFormatContext **ic, HI_S32 adaptionsetIndex)
{

    AVFormatContext *sub_ic = *ic;
    //check eos type now
    DASHIOMap *map = (DASHIOMap *)(sub_ic->pb->opaque);
    if (map->eos == DASHIO_EOS_PRESENTATION_CHANGED)
    {
        HI_S64 s64EarlistPts = (pstMember->s64SubtitleLastPts > pstMember->s64SubtitleFirstPts &&  \
                (pstMember->s64SubtitleFirstPts >= 0))?(pstMember->s64SubtitleLastPts - pstMember->s64SubtitleFirstPts):0;
        Option stOption = {1, map->param.representation_index, s64EarlistPts};

        dash_log(DASH_LOG_ERROR, "[%s,%d][BW] subtitle[%d] map[%p] pb=%p adaptionset_index=%d,rep_index changed to %d ,reopen the avformat!\n",
             __FUNCTION__, __LINE__, adaptionsetIndex, map, map->param.libavdecoder_pb, map->param.adaptionset_index, map->param.representation_index);

       // if (adaptionsetIndex == pstMember->s32SubtitleAdaptationSetIndex)
      //      stOption.representation_index = pstMember->s32SubtitleRepresentationIndex;

        pstMember->bForcePrint = HI_TRUE;
        if (HI_SUCCESS == _SVR_DASH_SetupContext(pstMember, ic,  NULL, map->param.libavdecoder_pb,
            &stOption, HI_FALSE, AVMEDIA_TYPE_SUBTITLE, adaptionsetIndex, map->param.representation_index))
        {
            pstMember->bSubtitleChangePresenFinish = HI_TRUE;
            return HI_TRUE;
        }
        else
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d][BW] subtitle[%d] setup context return error!\n", __FUNCTION__, __LINE__,  adaptionsetIndex);
        }
    }

    return HI_FALSE;
}

static HI_S32 _SVR_DASH_ReadSubFrame(DASHMember * pstMember, AVPacket * pkt)
{
    HI_S64 *ps64LastPts = NULL;
    HI_S64  s64LastPts = 0;
    HI_S32  s32Ret = HI_SUCCESS, i;
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;

    if (pstMember->sub_index == pstMember->sub_nb)
        pstMember->sub_index = 0;

    if (pstMember->sub_ic[pstMember->sub_index] == NULL)
    {
        for (i = pstMember->sub_index + 1; i < pstMember->sub_nb; i++)
        {
            if (pstMember->sub_ic[i] != NULL)
            {
                pstMember->sub_index = i;
                break;
            }
        }
        if (pstMember->sub_ic[pstMember->sub_index] == NULL)
        {
            for (i = 0; i < pstMember->sub_index; i++)
            {
                if (pstMember->sub_ic[i] != NULL)
                {
                    pstMember->sub_index = i;
                    break;
                }
            }
        }

        if (pstMember->sub_ic[pstMember->sub_index] == NULL)
        {
            dash_log(DASH_LOG_ERROR, "avformat context is null, set sub eos reached.\n");
            pstMember->bSubtitleEosReached= HI_TRUE;
            return HI_FAILURE;
        }
    }

    if (CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType[pstMember->sub_index], Subtitle_ISO_Mask))
    {
        #if defined (HISUB_SUPPORT)
        retry:
        if (CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType[pstMember->sub_index], Subtitle_TTML))
        {
            HI_S32 *ps32IsLoaded = NULL;
            av_opt_get(pstMember->ttml_ic[pstMember->sub_index], "is_loaded", 0, (HI_U8 **)&ps32IsLoaded);
            if (!(*ps32IsLoaded))
            {
                //if (pstMember->sub_index == pstMember->sub_nb) pstMember->sub_index = 0;
                ps64LastPts = (pstMember->sub_index == pstMember->s32SubtitleAdaptationSetIndex) ? &(pstMember->s64SubtitleLastPts) : &s64LastPts;
                s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->sub_ic[pstMember->sub_index], pkt, ps64LastPts);
                if (s32Ret < 0 && HI_TRUE == _SVR_DASH_CheckSubtitleRepresentationChanged(pstMember, \
                    &(pstMember->sub_ic[pstMember->sub_index]), pstMember->sub_index))
                {
                    s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->sub_ic[pstMember->sub_index], pkt, ps64LastPts);
                }
                if ((HI_FAILURE == s32Ret) && (pstMember->sub_index == pstMember->s32SubtitleAdaptationSetIndex))
                {
                    //manager may be updated during _SVR_DASH_ReadPacket, must update it when refer to it.
                    manager = (MultimediaManager *)pstMember->manager;
                    dash_log(DASH_LOG_ERROR, "subtitle eos reached, current pos:%u\n", ((manager != NULL)?manager->GetSubtitlePosition(pstMember->sub_index):0));
                    pstMember->bSubtitleEosReached = HI_TRUE;
                    return s32Ret;
                }
            }

            s32Ret = _SVR_DASH_ParseSubPacket(pstMember, pkt, Subtitle_TTML);
            if (HI_FAILURE == s32Ret)
            {
                av_opt_set(pstMember->ttml_ic[pstMember->sub_index], "is_loaded", "0", 0);
                av_opt_set(pstMember->ttml_ic[pstMember->sub_index], "is_parsed", "0", 0);
                av_free_packet(pkt);
                goto retry;
            }
        }
        #endif

        if (CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType[pstMember->sub_index], Subtitle_TX3G))
        {
            //if (pstMember->sub_index == pstMember->sub_nb) pstMember->sub_index = 0;
            ps64LastPts = (pstMember->sub_index == pstMember->s32SubtitleAdaptationSetIndex) ? &(pstMember->s64SubtitleLastPts) : &s64LastPts;
            s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->sub_ic[pstMember->sub_index], pkt, ps64LastPts);
            if (s32Ret < 0 && HI_TRUE == _SVR_DASH_CheckSubtitleRepresentationChanged(pstMember, \
                &(pstMember->sub_ic[pstMember->sub_index]), pstMember->sub_index))
            {
                s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->sub_ic[pstMember->sub_index], pkt, ps64LastPts);
            }
            if ((HI_FAILURE == s32Ret) && (pstMember->sub_index == pstMember->s32SubtitleAdaptationSetIndex))
            {
                dash_log(DASH_LOG_ERROR, "subtitle eos reached!\n");
                pstMember->bSubtitleEosReached = HI_TRUE;

                return s32Ret;
            }

            s32Ret = _SVR_DASH_ParseSubPacket(pstMember, pkt, Subtitle_TX3G);
            if (HI_FAILURE == s32Ret)
            {
                dash_log(DASH_LOG_ERROR, "parse tx3g subtitle faild!\n");
            }
        }
    }
    else
    {
        #if defined (HISUB_SUPPORT)
        if (CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType[pstMember->sub_index], Subtitle_TTML))
        {
            //if (pstMember->sub_index == pstMember->sub_nb) pstMember->sub_index = 0;
            ps64LastPts = (pstMember->sub_index == pstMember->s32SubtitleAdaptationSetIndex) ? &(pstMember->s64SubtitleLastPts) : &s64LastPts;
            s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->ttml_ic[pstMember->sub_index], pkt, ps64LastPts);
            if (s32Ret < 0 && HI_TRUE == _SVR_DASH_CheckSubtitleRepresentationChanged(pstMember, \
                &(pstMember->ttml_ic[pstMember->sub_index]), pstMember->sub_index))
            {
                s32Ret = _SVR_DASH_ReadPacket(pstMember, pstMember->ttml_ic[pstMember->sub_index], pkt, ps64LastPts);
            }
            if ((HI_FAILURE == s32Ret) && (pstMember->sub_index == pstMember->s32SubtitleAdaptationSetIndex))
            {
                dash_log(DASH_LOG_ERROR, "subtitle eos reached!\n");
                pstMember->bSubtitleEosReached = HI_TRUE;
                return s32Ret;
            }
        }
        #endif
    }

    if ((HI_FAILURE == s32Ret) || \
        (s64LastPts >= pstMember->s64SubtitleLastPts) || \
        (pstMember->sub_index == pstMember->s32SubtitleAdaptationSetIndex))
    {
        //do the same thing as audio
        pstMember->sub_index++;
    }

    if (HI_SUCCESS == s32Ret)
    {

        if (pstMember->s64SubtitleFirstPts == AV_NOPTS_VALUE)
        {
            pstMember->s64SubtitleFirstPts = pstMember->s64SubtitleLastPts;
        }

        if (pstMember->s64SubtitleFirstPts == AV_NOPTS_VALUE)
        {
            pstMember->s64SubtitleFirstPts = 0;
        }
    }

    return s32Ret;
}

static HI_S32 _SVR_DASH_ReadVidSubFrame(DASHMember* pstMember, AVPacket * pkt)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if ((HI_TRUE == pstMember->bSubtitleEosReached ) ||
        ((pstMember->s64VideoLastPts < pstMember->s64SubtitleLastPts) && (HI_FALSE == pstMember->bVideoEosReached)))
    {
        //Read Video Frame
        s32Ret = _SVR_DASH_ReadVidFrame(pstMember, pkt);
    }
    else
    {
        //Read Subtitle Frame
        s32Ret = _SVR_DASH_ReadSubFrame(pstMember, pkt);
    }

    return s32Ret;
}

static HI_S32 _SVR_DASH_ReadAudSubFrame(DASHMember * pstMember, AVPacket * pkt)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if ((HI_TRUE == pstMember->bSubtitleEosReached) || \
        ((pstMember->s64AudioLastPts < pstMember->s64SubtitleLastPts) && (HI_FALSE == pstMember->bAudioEosReached)))
    {
        //Read Audio Frame
        s32Ret = _SVR_DASH_ReadAudFrame(pstMember, pkt);
    }
    else
    {
        //Read Subtitle Frame
        s32Ret = _SVR_DASH_ReadSubFrame(pstMember, pkt);
    }

    return s32Ret;
}

static HI_S32 _SVR_DASH_ReadVidAudFrame(DASHMember * pstMember, AVPacket * pkt)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if ((HI_TRUE == pstMember->bAudioEosReached) || \
        ((pstMember->s64VideoLastPts < pstMember->s64AudioLastPts) && (HI_FALSE == pstMember->bVideoEosReached)))
    {
        //Read Video Frame
        s32Ret = _SVR_DASH_ReadVidFrame(pstMember, pkt);
    }
    else
    {
        //Read Audio Frame
        s32Ret = _SVR_DASH_ReadAudFrame(pstMember, pkt);
    }

    if (((pstMember->u32VTryRead + pstMember->u32ATryRead) % 50 == 0) ||
        pstMember->bForcePrint == HI_TRUE)
    {
        pstMember->bForcePrint = HI_FALSE;
        dash_log(DASH_LOG_INFO, "[%s,%d] Video(try/ok)  %u/%u, Audio (try/ok)  %u/%u, LastPts(V:%lld, A:%lld, S:%lld), FirstPts(V:%lld, A:%lld, S:%lld)\n",
            __FUNCTION__, __LINE__, pstMember->u32VTryRead, pstMember->u32VReadOKCount,
            pstMember->u32ATryRead, pstMember->u32AReadOKCount,
            pstMember->s64VideoLastPts, pstMember->s64AudioLastPts, pstMember->s64SubtitleLastPts,
            pstMember->s64VideoFirstPts, pstMember->s64AudioFirstPts, pstMember->s64SubtitleFirstPts
            );
    }

    return s32Ret;
}

static HI_S32 _SVR_DASH_ReadVidAudSubFrame(DASHMember * pstMember, AVPacket * pkt)
{
    HI_S32  s32Ret = HI_SUCCESS;

    if (HI_TRUE == pstMember->bVideoEosReached)
    {
        //Read Audio and Subtitle Frame
        s32Ret = _SVR_DASH_ReadAudSubFrame(pstMember, pkt);
    }
    else if (HI_TRUE == pstMember->bAudioEosReached)
    {
        //Read Video and Subtitle Frame
        s32Ret = _SVR_DASH_ReadVidSubFrame(pstMember, pkt);
    }
    else if (HI_TRUE == pstMember->bSubtitleEosReached)
    {
        //Read Video and Audio Frame
        s32Ret = _SVR_DASH_ReadVidAudFrame(pstMember, pkt);
    }
    else
    {
        if ((pstMember->s64VideoLastPts > pstMember->s64AudioLastPts))
        {
            if (pstMember->s64AudioLastPts > pstMember->s64SubtitleLastPts)
            {
                //Read Subtitle Frame
                s32Ret = _SVR_DASH_ReadSubFrame(pstMember, pkt);
            }
            else
            {
                //Read Audio Frame
                s32Ret = _SVR_DASH_ReadAudFrame(pstMember, pkt);
            }
        }
        else
        {
            if (pstMember->s64VideoLastPts > pstMember->s64SubtitleLastPts)
            {
                //Read Subtitle Frame
                s32Ret = _SVR_DASH_ReadSubFrame(pstMember, pkt);
            }
            else
            {
                //Read Video Frame
                s32Ret = _SVR_DASH_ReadVidFrame(pstMember, pkt);
            }
        }
    }

    return s32Ret;
}

static HI_S32 _SVR_DASH_ReadFrame(HI_HANDLE fmtHandle, HI_VOID *pArg)
{
    DASHMember * pstMember = (DASHMember *)fmtHandle;
    AVPacket * pkt = (AVPacket *)pArg;
    HI_S32 s32Ret = HI_FAILURE;
    HI_BOOL bEos = HI_FALSE;
    CodecID u32Format;
    AVMediaType eMediaType;
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;

    if (pstMember->bSetupFinish == HI_FALSE)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] setup not finished ,can't read.\n", __FUNCTION__, __LINE__);
        return AVERROR_EOF;
    }

retry:

    bEos = _SVR_DASH_CheckEos(pstMember);
    if (pstMember->bUpdateMPD && HI_TRUE == pstMember->bSetupFinish && HI_FALSE == bEos)
    {
        if (HI_SUCCESS != _SVR_DASH_UpdateMPD(pstMember, HI_TRUE, HI_FALSE))
        {
            pstMember->bVideoEosReached = HI_TRUE;
            pstMember->bAudioEosReached = HI_TRUE;
            pstMember->bSubtitleEosReached = HI_TRUE;
            bEos = HI_TRUE;
            dash_log(DASH_LOG_ERROR, "[%s,%d] update MPD error, set EOS!!\n", __FUNCTION__, __LINE__);
        }
        manager = (MultimediaManager *)pstMember->manager;
    }

    if (HI_TRUE == bEos)
    {
        HI_S32  s32PlayResult = HI_FAILURE;
        HI_BOOL bFirstTime = HI_TRUE, bUpdated = HI_FALSE;
        dash_log(DASH_LOG_ERROR, "[%s,%d] read frame return EOS!!\n", __FUNCTION__, __LINE__);

        if (pstMember->bUpdateMPD)
        {
            do
            {
                if (pstMember->ic->interrupt_callback.callback(pstMember->ic->interrupt_callback.opaque))
                {
                    dash_log(DASH_LOG_ERROR, "[%s,%d] user interrupted\n", __FUNCTION__, __LINE__);
                    return AVERROR_EOF;
                }
                if (bFirstTime == HI_TRUE || bUpdated == HI_TRUE)
                {
                    s32PlayResult = _SVR_DASH_PlayNextPeriod(pstMember);
                    if (s32PlayResult == HI_SUCCESS)
                        break;
                }
                bUpdated =  _SVR_DASH_DoUpdateMPD(pstMember, HI_FALSE, bFirstTime);
                manager = (MultimediaManager *)pstMember->manager;
                bFirstTime = HI_FALSE;
                if (bUpdated == HI_FALSE)
                    usleep(100000);
            }while(s32PlayResult != HI_SUCCESS);
        }
        else
        {
            s32PlayResult = _SVR_DASH_PlayNextPeriod(pstMember);
        }

        if (HI_SUCCESS == s32PlayResult)
        {
            _SVR_DASH_CloseFormat(pstMember);
            _SVR_DASH_FreeMasterStream(pstMember);
            pstMember->bSetupFinish = HI_FALSE;
            if (HI_SUCCESS == _SVR_DASH_Setup(pstMember))
            {
                pstMember->bSetupFinish = HI_TRUE;
                pstMember->bVideoEosReached = HI_FALSE;
                pstMember->bAudioEosReached = HI_FALSE;
                pstMember->bSubtitleEosReached = HI_FALSE;

                pstMember->bVideoChangePresenFinish = HI_TRUE;
                pstMember->bAudioChangePresenFinish = HI_TRUE;
                pstMember->bSubtitleChangePresenFinish = HI_TRUE;
            #ifdef PLAYREADY_SUPPORT
                if (HI_TRUE == pstMember->bUsingPlayReady && HI_SUCCESS == _SVR_DASH_PlayReady_CheckKIDChanged(pstMember))
                {
                    _SVR_DASH_PlayReady_Reopen(pstMember);
                }
            #endif
            }
            else
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d] failed to setup ,return eof\n", __FUNCTION__, __LINE__);
                return AVERROR_EOF;
            }
        }
        else
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] failed to play next period ,return eof\n", __FUNCTION__, __LINE__);
            return AVERROR_EOF;
        }
    }

    HI_S32 s32StreamType = _SVR_CHECK_StreamType(pstMember);
    //TODO: READ MIN PTS
    switch(s32StreamType)
    {
        case 1:
            //Video Only
            s32Ret = _SVR_DASH_ReadVidFrame(pstMember, pkt);
            if (HI_FAILURE == s32Ret)
                goto retry;
            break;
        case 2:
            //Audio Only
            s32Ret = _SVR_DASH_ReadAudFrame(pstMember, pkt);
            if (HI_FAILURE == s32Ret)
                goto retry;
            break;
        case 3:
            //Video + Audio
            s32Ret = _SVR_DASH_ReadVidAudFrame(pstMember, pkt);
            if (HI_FAILURE == s32Ret)
                goto retry;
            break;
        case 5:
            //Video + Subtitle
            s32Ret = _SVR_DASH_ReadVidSubFrame(pstMember, pkt);
            if (HI_FAILURE == s32Ret)
                goto retry;
            break;
        case 6:
            //Audio + Subtitle
            s32Ret = _SVR_DASH_ReadAudSubFrame(pstMember, pkt);
            if (HI_FAILURE == s32Ret)
                goto retry;
            break;
        case 7:
            //Video + Audio + Subtitle
            s32Ret = _SVR_DASH_ReadVidAudSubFrame(pstMember, pkt);
            if (HI_FAILURE == s32Ret)
                goto retry;
            break;
        case 0:
        case 4:
        default:
            //TODO: error Message
            break;
    }

    _SVR_DASH_GetStreamCodec(pstMember->ic, pkt->stream_index, &eMediaType, &u32Format);

#ifdef PLAYREADY_SUPPORT
    if (HI_TRUE == pstMember->bUsingPlayReady && (AVMEDIA_TYPE_AUDIO == eMediaType || AVMEDIA_TYPE_VIDEO == eMediaType))
    {
        if (_SVR_DASH_PlayReady_Decrypt(pstMember, pkt) != HI_SUCCESS)
        {
            dash_log(DASH_LOG_ERROR, "[%s:%d] _SVR_DASH_PlayReady_Decrypt failed!, eMediaType:%d\n", __FILE__, __LINE__, eMediaType);
            pstMember->bUsingPlayReady = HI_FALSE;
        }
    }
#endif

    if (HI_TRUE == pstMember->bIsISOFF)
    {
        AVStream * st = ((HI_U32)pkt->stream_index < pstMember->ic->nb_streams) ? pstMember->ic->streams[pkt->stream_index] : NULL;
        if (NULL == st)
        {
            return HI_FAILURE;
        }

        s32Ret = _SVR_DASH_AddExtraData(u32Format,st,pstMember->ic,pkt);
        if (HI_SUCCESS != s32Ret)
        {
            dash_log(DASH_LOG_ERROR, "Add extra data failed!\n");
            av_free_packet(pkt);
            return s32Ret;
        }
    }

    _SVR_DASH_CheckAdaptationSetChanged(pstMember);

    //**if need update mpd, we switch representation when we update mpd.
    if (pstMember->bUpdateMPD == HI_FALSE)
        _SVR_DASH_CheckBandWidthChanged(pstMember, HI_FALSE, AVMEDIA_TYPE_UNKNOWN);

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_SearchSidxTag(HI_U8 **ppSidxData, HI_U32 *pSize)
{
    HI_U8 *pSidxData = *ppSidxData;
    HI_U8 * pu8Start = HI_NULL;
    HI_U8 * pu8Data = HI_NULL;
    HI_U8 i = 0;

    if (HI_NULL == pSidxData || *pSize < 3)
        return HI_FAILURE;

    pu8Start = pSidxData;

    for (i = 0; i < (*pSize - 3); i++)
    {
        if (pu8Start[i] == 's' && \
            pu8Start[i + 1] == 'i' && \
            pu8Start[i + 2] == 'd' && \
            pu8Start[i + 3] == 'x')
            break;
    }

    if (0 == i)
        return HI_SUCCESS;

    if ((*pSize - 4) == i)
        return HI_FAILURE;

    *pSize -= (i + 4);
    pu8Data = (HI_U8 *)av_mallocz(*pSize);
    memcpy(pu8Data, pSidxData + i + 4, *pSize);

    av_free(pSidxData);
    *ppSidxData = (HI_U8 *)av_mallocz(*pSize);
    pSidxData = *ppSidxData;
    memcpy(pSidxData, pu8Data, *pSize);

    av_freep(&pu8Data);
    return HI_SUCCESS;
}

size_t  _SVR_DASH_CurlResponseCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    CurlDataMember *curlDataMember = (CurlDataMember *)userp;

    size_t  realsize = size * nmemb;
    curlDataMember->pData = (unsigned char  *)av_realloc(curlDataMember->pData, curlDataMember->size  + realsize);

    memcpy(curlDataMember->pData + curlDataMember->size, contents, realsize);
    curlDataMember->size += realsize;

    return realsize;
}

/*for no Garbleds output when server have response*/
size_t  _SVR_DASH_CurlEmptyCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t  realsize = size * nmemb;

    return  realsize;
}

size_t _SVR_DASH_CurlHeaderCallback(void * headerData, size_t size,size_t nmemb,void * userdata)
{
    DASHMember *pstMember = (DASHMember *)userdata;
    CurlDataMember *curlDataMember = &pstMember->curlDataMember;

    size_t realsize = size * nmemb;
    curl_easy_getinfo(curlDataMember->curl_handle, CURLINFO_RESPONSE_CODE ,&curlDataMember->httpCode);

    if (curlDataMember->httpCode == 200 || curlDataMember->httpCode == 206)
        curlDataMember->status = CURL_STATUS_OK;
    else
        curlDataMember->status = CURL_STATUS_NOK;

    return realsize;
}

static HI_S32 _SVR_DASH_DownloadSidx(CurlDataMember *curlDataMember,const HI_CHAR *pURL)
{
    curl_global_init(CURL_GLOBAL_ALL);
    curlDataMember->curl_handle = curl_easy_init();
    curlDataMember->multi_handle = curl_multi_init();

    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_URL, pURL);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_WRITEFUNCTION, _SVR_DASH_CurlResponseCallback);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_WRITEDATA, (void *)curlDataMember);
    curl_multi_add_handle(curlDataMember->multi_handle, curlDataMember->curl_handle);

    int is_running;
    long http_code = 0;
    curlDataMember->status = CURL_STATUS_INPROGRESS;

    do
    {
        while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(curlDataMember->multi_handle, &is_running));

        if (curlDataMember->status != CURL_STATUS_INPROGRESS)
        {
            break;
        }

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 1000;

        int max;
        fd_set fd_read;
        fd_set fd_write;
        fd_set fd_except;

        FD_ZERO(&fd_read);
        FD_ZERO(&fd_write);
        FD_ZERO(&fd_except);

        curl_multi_fdset(curlDataMember->multi_handle, &fd_read, &fd_write, &fd_except,&max);
        int code = select(max + 1, &fd_read, &fd_write, &fd_except, &tv);
        if (-1 == code)
            break;

    }while(is_running);

    curl_easy_getinfo(curlDataMember->curl_handle, CURLINFO_RESPONSE_CODE , &http_code);

    curl_multi_remove_handle(curlDataMember->multi_handle, curlDataMember->curl_handle);
    curl_easy_cleanup(curlDataMember->curl_handle);
    curl_multi_cleanup(curlDataMember->multi_handle);
    curl_global_cleanup();

    if (http_code != 200)
        return HI_FAILURE;

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_DetectURL(DASHMember *pstMember, const HI_CHAR *pURL, HI_U32 u32Range)
{
    CurlDataMember * curlDataMember = &pstMember->curlDataMember;
    std::stringstream ss;
    std::string s;

    curl_global_init(CURL_GLOBAL_ALL);
    curlDataMember->curl_handle = curl_easy_init();
    curlDataMember->multi_handle = curl_multi_init();

    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_URL, pURL);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_HEADERFUNCTION, _SVR_DASH_CurlHeaderCallback);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_HEADERDATA, (void *)pstMember);
    curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_NOBODY, 1L);
    //curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_WRITEFUNCTION, _SVR_DASH_CurlEmptyCallback);
    //curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_WRITEDATA, (void *)pstMember);

    if (SINGLE_MEDIA_SEGMENT == pstMember->eRepresentationType)
    {
        ss << u32Range;
        ss >> s;
        ss.clear();

        curl_easy_setopt(curlDataMember->curl_handle, CURLOPT_RANGE, (s + "-").c_str());
    }

    curl_multi_add_handle(curlDataMember->multi_handle, curlDataMember->curl_handle);

    int is_running;
    curlDataMember->status = CURL_STATUS_INPROGRESS;

    do
    {
        while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(curlDataMember->multi_handle, &is_running));

        if (curlDataMember->status != CURL_STATUS_INPROGRESS)
        {
            break;
        }

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 1000;

        int max;
        fd_set fd_read;
        fd_set fd_write;
        fd_set fd_except;

        FD_ZERO(&fd_read);
        FD_ZERO(&fd_write);
        FD_ZERO(&fd_except);

        curl_multi_fdset(curlDataMember->multi_handle, &fd_read, &fd_write, &fd_except,&max);
        int code = select(max + 1, &fd_read, &fd_write, &fd_except, &tv);
        if (-1 == code)
           break;

    }while(is_running);

    curl_multi_remove_handle(curlDataMember->multi_handle, curlDataMember->curl_handle);
    curl_easy_cleanup(curlDataMember->curl_handle);
    curl_multi_cleanup(curlDataMember->multi_handle);
    curl_global_cleanup();

    if (curlDataMember->status != CURL_STATUS_OK)
        return HI_FAILURE;

    return HI_SUCCESS;
}

static HI_BOOL _SVR_DASH_IsSingleSegmentSeekable(DASHMember * pstMember)
{
    HI_S32 i, j, rep_count;
    HI_S32 s32AdpIndex = pstMember->s32VideoAdaptationSetIndex;
    HI_S32 s32RepIndex = pstMember->s32VideoRepresentationIndex;
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;

    if (SINGLE_MEDIA_SEGMENT != pstMember->eRepresentationType)
        return HI_TRUE;

    if ( pstMember->stCurPeriod.videoAdaptionsets.size() != pstMember->vid_nb ||
         pstMember->stCurPeriod.audioAdaptionsets.size() != pstMember->aud_nb ||
         pstMember->stCurPeriod.subtitleAdaptionsets.size() != pstMember->sub_nb)
    {
        return HI_FALSE;
    }

    for (i = 0; i < pstMember->vid_nb; i++)
    {
        rep_count = pstMember->stCurPeriod.videoAdaptionsets.at(i).representationsSidxinfo.size();
        if (rep_count  != manager->GetVideoAdaptionSet(i)->GetRepresentation().size())
            return HI_FALSE;
        for (j = 0; j < rep_count; j++)
        {
            if (pstMember->stCurPeriod.videoAdaptionsets.at(i).representationsSidxinfo.at(j) == NULL)
                return HI_FALSE;
        }
    }

    if ((pstMember->vid_nb == 0 && pstMember->bIsISOFF == HI_FALSE)
        || pstMember->bIsISOFF == HI_TRUE)
    {
        for (i = 0; i < pstMember->aud_nb; i++)
        {
            rep_count = pstMember->stCurPeriod.audioAdaptionsets.at(i).representationsSidxinfo.size();
            if (rep_count  != manager->GetAudioAdaptionSet(i)->GetRepresentation().size())
                return HI_FALSE;
            for (j = 0; j < rep_count; j++)
            {
                if (pstMember->stCurPeriod.audioAdaptionsets.at(i).representationsSidxinfo.at(j) == NULL)
                    return HI_FALSE;
            }
        }
    }

    if (pstMember->bIsISOFF == HI_TRUE)
    {
        for (i = 0; i < pstMember->sub_nb; i++)
        {
            rep_count = pstMember->stCurPeriod.subtitleAdaptionsets.at(i).representationsSidxinfo.size();
            if (rep_count  != manager->GetSubtitleAdaptionSet(i)->GetRepresentation().size())
                return HI_FALSE;
            for (j = 0; j < rep_count; j++)
            {
                if (pstMember->stCurPeriod.subtitleAdaptionsets.at(i).representationsSidxinfo.at(j) == NULL)
                    return HI_FALSE;
            }
        }
    }

    return HI_TRUE;
}

static HI_S32 _SVR_DASH_SeekSingleSegment(DASHMember * pstMember, HI_S32 s32StreamIndex, HI_S64 s64Pts)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    HI_U32 u32Position = 0;
    HI_S32 s32Index = 0;
    HI_S64 s64SeekPts = s64Pts;
    HI_U32 i = 0;
    SidxInfo *pSidxInfo = NULL;
    AVStream * st = NULL;
    AVIOContext * pb = NULL;
    HI_S32 s32Ret = HI_FAILURE;
    HI_S32 s32StreamNb;
    HI_S32 s32AdpIndex;
    HI_S32 s32RepIndex;

#if 0
    if (pstMember->bIsISOFF)
    {
      //  dash_log("ISOFF single segment can not seek now!\n");
        if (0 == s64Pts)
        {
            pstMember->s64VideoLastPts = pstMember->s64VideoFirstPts;
            pstMember->s64AudioLastPts = pstMember->s64AudioFirstPts;
            pstMember->s64SubtitleLastPts = pstMember->s64SubtitleFirstPts;

            return HI_SUCCESS;
        }

        return HI_FAILURE;
    }
#endif
    if (0 == s64Pts)
    {
        pstMember->s64VideoLastPts = pstMember->s64VideoFirstPts;
        pstMember->s64AudioLastPts = pstMember->s64AudioFirstPts;
        pstMember->u32VideoPosition = 0;
        pstMember->u32AudioPosition = 0;
        return HI_SUCCESS;
    }

    if (pstMember->vid_nb > 0)
    {
        if (0 == s64Pts)
        {
            u32Position = 0;
            pstMember->s64VideoLastPts = pstMember->s64VideoFirstPts;
        }
        else
        {
            s32AdpIndex = pstMember->s32VideoAdaptationSetIndex;
            s32RepIndex = pstMember->s32VideoRepresentationIndex;
            pSidxInfo = pstMember->stCurPeriod.videoAdaptionsets.at(s32AdpIndex).representationsSidxinfo.at(s32RepIndex);
            if (pSidxInfo == NULL)
                return HI_FAILURE;
            s32StreamNb = pstMember->vid_ic[pstMember->s32VideoAdaptationSetIndex]->nb_streams;
            st = pstMember->vid_ic[pstMember->s32VideoAdaptationSetIndex]->streams[s32StreamNb - 1];
            if (st->time_base.den != 0 && st->time_base.num != 0)
            {
                s64Pts = s64Pts * st->time_base.den /st->time_base.num;
                s64Pts /= 1000;
                dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] video pts update to %lld\n", __FUNCTION__, __LINE__, s64Pts);
            }
            s32Index = ff_index_search_timestamp(pSidxInfo->index_entries, pSidxInfo->entries_nb, s64Pts, AVSEEK_FLAG_ANY);
            if (s32Index < 0)
                return HI_FAILURE;
            //u32Position = (HI_U32)pSidxInfo->index_entries[s32Index].pos;
            s64SeekPts = pSidxInfo->index_entries[s32Index].timestamp;

            //Chcek URL is valid or not before seek
            #if 0
            URL = manager->GetVideoSegmentURL(pstMember->s32VideoAdaptationSetIndex, pstMember->s32VideoRepresentationIndex, 0);
            if (URL == "")
                return HI_FAILURE;

            s32Ret = _SVR_DASH_DetectURL(pstMember, URL.c_str(),u32Position);
            if (HI_FAILURE == s32Ret)
                return s32Ret;
            #endif
             if (st->time_base.den != 0 && st->time_base.num != 0)
                pstMember->s64VideoLastPts = s64SeekPts * 1000 * st->time_base.num / st->time_base.den;
            else
                pstMember->s64VideoLastPts = s64SeekPts;
        }
        pstMember->u32VideoPosition = s32Index;
    }

    if (pstMember->bIsISOFF)
    {
        if (pstMember->aud_nb > 0)
        {
            if (0 == s64Pts)
            {
                u32Position = 0;
                pstMember->s64AudioLastPts = pstMember->s64AudioFirstPts;
            }
            else
            {
                s32AdpIndex = pstMember->s32AudioAdaptationSetIndex;
                s32RepIndex = pstMember->s32AudioRepresentationIndex;
                pSidxInfo = pstMember->stCurPeriod.audioAdaptionsets.at(s32AdpIndex).representationsSidxinfo.at(s32RepIndex);
                if (pSidxInfo == NULL)
                    return HI_FAILURE;
                s32StreamNb = pstMember->aud_ic[pstMember->s32AudioAdaptationSetIndex]->nb_streams;
                st = pstMember->aud_ic[pstMember->s32AudioAdaptationSetIndex]->streams[s32StreamNb - 1];
                if (st->time_base.den != 0 && st->time_base.num != 0)
                {
                    s64Pts = s64Pts * st->time_base.den /st->time_base.num;
                    s64Pts /= 1000;
                    dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] audio pts update to %lld\n", __FUNCTION__, __LINE__, s64Pts);
                }
                s32Index = ff_index_search_timestamp(pSidxInfo->index_entries, pSidxInfo->entries_nb, s64Pts, AVSEEK_FLAG_ANY);
                if (s32Index < 0)
                    return HI_FAILURE;
                //u32Position = (HI_U32)pSidxInfo->index_entries[s32Index].pos;
                s64SeekPts = pSidxInfo->index_entries[s32Index].timestamp;

                //Chcek URL is valid or not before seek
                #if 0
                URL = manager->GetVideoSegmentURL(pstMember->s32VideoAdaptationSetIndex, pstMember->s32VideoRepresentationIndex, 0);
                if (URL == "")
                    return HI_FAILURE;

                s32Ret = _SVR_DASH_DetectURL(pstMember, URL.c_str(),u32Position);
                if (HI_FAILURE == s32Ret)
                    return s32Ret;
                #endif
                 if (st->time_base.den != 0 && st->time_base.num != 0)
                    pstMember->s64AudioLastPts = s64SeekPts * 1000 * st->time_base.num / st->time_base.den;
                else
                    pstMember->s64AudioLastPts = s64SeekPts;
            }
            pstMember->u32AudioPosition = s32Index;
        }
    }

#if 0
    if (pstMember->aud_nb > 0)
    {
        pSidxInfo = pstMember->pAudioSidxInfo;
        s32Index = ff_index_search_timestamp(pSidxInfo->index_entries, pSidxInfo->entries_nb, s64Pts, AVSEEK_FLAG_ANY);
        u32Position = (HI_U32)pSidxInfo->index_entries[s32Index].pos;
        manager->SetAudioPosition(u32Position);
        pstMember->s64AudioFirstPts = pSidxInfo->index_entries[s32Index].timestamp;
        pstMember->s64AudioLastPts = pstMember->s64AudioFirstPts;
    }

    if (pstMember->sub_nb > 0)
    {
        pSidxInfo = pstMember->pSubtitleSidxInfo;
        s32Index = ff_index_search_timestamp(pSidxInfo->index_entries, pSidxInfo->entries_nb, s64Pts, AVSEEK_FLAG_ANY);
        u32Position = (HI_U32)pSidxInfo->index_entries[s32Index].pos;
        manager->SetSubtitlePosition(u32Position);
        pstMember->s64SubtitleFirstPts = pSidxInfo->index_entries[s32Index].timestamp;
        pstMember->s64SubtitleLastPts = pstMember->s64SubtitleFirstPts;
    }
#endif

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_SeekMultiSegment(DASHMember * pstMember, HI_S32 s32StreamIndex, HI_S64 s64Pts, HI_FORMAT_SEEK_FLAG_E eFlag)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    HI_U32 u32SegmentDuration = 0;
    HI_U32 u32Position = 0;
    HI_S32 s32Index = 0;
    HI_S32 s32Direct = 1;
    HI_S64 s64SeekPts = s64Pts;
    SidxInfo *pSidxInfo = NULL;
    AVStream * st = NULL;
    AVIOContext * pb = NULL;

    if (eFlag == HI_FORMAT_AVSEEK_FLAG_BACKWARD)
    {
        s32Direct= -1;
    }

    if (pstMember->vid_nb > 0)
    {
       if (0 == s64Pts)
       {
            u32Position = 0;
            pstMember->s64VideoLastPts = pstMember->s64VideoFirstPts;
       }
       else
       {
            u32Position = manager->GetVideoPositionFromTime(pstMember->s32VideoAdaptationSetIndex, s64SeekPts, s32Direct);
            pstMember->s64VideoLastPts = manager->GetVideoSegmentStartTime(pstMember->s32VideoAdaptationSetIndex, u32Position);
       }

        pstMember->u32VideoPosition = u32Position;
        dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] video adaptationset %d seek to  position %u\n", __FUNCTION__, __LINE__, pstMember->s32VideoAdaptationSetIndex, u32Position);
       // manager->SetVideoPosition(pstMember->s32VideoAdaptationSetIndex, u32Position);
    }

    if (pstMember->aud_nb > 0)
    {
       if (0 == s64Pts)
       {
            u32Position = 0;
            pstMember->s64AudioLastPts = pstMember->s64AudioFirstPts;
       }
       else
       {
            u32Position = manager->GetAudioPositionFromTime(pstMember->s32AudioAdaptationSetIndex, s64SeekPts, s32Direct);
            pstMember->s64AudioLastPts = manager->GetAudioSegmentStartTime(pstMember->s32AudioAdaptationSetIndex, u32Position);
       }
        pstMember->u32AudioPosition = u32Position;
        dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] audio adaptationset %d  seek to position %u\n", __FUNCTION__, __LINE__, pstMember->s32AudioAdaptationSetIndex, u32Position);
      //  manager->SetAudioPosition(pstMember->s32AudioAdaptationSetIndex, u32Position);
    }

    if (pstMember->sub_nb > 0)
    {
       if (0 == s64Pts)
       {
            u32Position = 0;
            pstMember->s64SubtitleLastPts = pstMember->s64SubtitleFirstPts;
       }
       else
       {
            u32Position = manager->GetSubtitlePositionFromTime(pstMember->s32SubtitleAdaptationSetIndex, s64SeekPts, s32Direct);
            pstMember->s64SubtitleLastPts = manager->GetSubtitleSegmentStartTime(pstMember->s32SubtitleAdaptationSetIndex, u32Position);
       }

        pstMember->u32SubtitlePosition = u32Position;
      //  pstMember->s64SubtitleFirstPts = pstMember->s64SubtitleLastPts;
        dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] subtitle adaptationset %d seek to position %u\n", __FUNCTION__, __LINE__, pstMember->s32SubtitleAdaptationSetIndex, u32Position);
           // manager->SetSubtitlePosition(pstMember->s32SubtitleAdaptationSetIndex, u32Position);
    }

    return HI_SUCCESS;
}

static HI_U32 _SVR_DASH_R8(HI_U8 **ppu8Data)
{
    //Do it like avio_r8
    return *(*ppu8Data)++;
}

static HI_U32 _SVR_DASH_RB16(HI_U8 **ppu8Data)
{
    HI_U32 u32Val;
    u32Val = _SVR_DASH_R8(ppu8Data) << 8;
    u32Val |= _SVR_DASH_R8(ppu8Data);
    return u32Val;
}

static HI_U32 _SVR_DASH_RB24(HI_U8 **ppu8Data)
{
    HI_U32 u32Val;
    u32Val = _SVR_DASH_RB16(ppu8Data) << 8;
    u32Val |= _SVR_DASH_R8(ppu8Data);
    return u32Val;
}

static HI_U32 _SVR_DASH_RB32(HI_U8 **ppu8Data)
{
    HI_U32 u32Val;
    u32Val = _SVR_DASH_RB16(ppu8Data) << 16;
    u32Val |= _SVR_DASH_RB16(ppu8Data);
    return u32Val;
}

static HI_U64 _SVR_DASH_RB64(HI_U8 **ppu8Data)
{
    HI_U64 u64Val;
    u64Val = (HI_U64)_SVR_DASH_RB32(ppu8Data) << 32;
    u64Val |= (HI_U64)_SVR_DASH_RB32(ppu8Data);
    return u64Val;
}

static HI_S32 _SVR_DASH_AddIndexEntry(SidxInfo *pSidxInfo, HI_U8 *pu8Data)
{
    HI_U32 i = 0;
    HI_S64 s64Pos = 0;
    HI_S64 s64Pts = 0;
    HI_U32 u32Temp = 0;
    HI_U8  u8RefType = 0;
    HI_U32 u32RefSize = 0;
    HI_U32 u32SubSegDuration = 0;
    HI_U32 u32AllocatedSize = 0;

    pSidxInfo->version = _SVR_DASH_R8(&pu8Data);
    pSidxInfo->flag = _SVR_DASH_RB24(&pu8Data);
    pSidxInfo->reference_ID = _SVR_DASH_RB32(&pu8Data);
    pSidxInfo->timescale = _SVR_DASH_RB32(&pu8Data);

/*
    dash_log("version = %d\n", pSidxInfo->version);
    dash_log("flag = %d\n", pSidxInfo->flag);
    dash_log("ID = %d\n", pSidxInfo->reference_ID);
    dash_log("ts = %d\n", pSidxInfo->timescale);
*/

    if (0 == pSidxInfo->version)
    {
        pSidxInfo->earliest_presentation_time = (HI_U64)_SVR_DASH_RB32(&pu8Data);
        pSidxInfo->first_offset               = (HI_U64)_SVR_DASH_RB32(&pu8Data);
    }
    else
    {
        pSidxInfo->earliest_presentation_time = _SVR_DASH_RB64(&pu8Data);
        pSidxInfo->first_offset               = _SVR_DASH_RB64(&pu8Data);
    }

    pSidxInfo->reserved = _SVR_DASH_RB16(&pu8Data);
    pSidxInfo->reference_count = _SVR_DASH_RB16(&pu8Data);
/*
    dash_log("pts = %lld offset = %lld\n", pSidxInfo->earliest_presentation_time, pSidxInfo->first_offset);
    dash_log("reserved = %d\n", pSidxInfo->reserved);
    dash_log("ref_count = %d\n",pSidxInfo->reference_count);
*/
    if (0 != pSidxInfo->reference_count)
        pSidxInfo->index_entries = (AVIndexEntry *)av_mallocz(pSidxInfo->reference_count * sizeof(AVIndexEntry));
    else
        return HI_FAILURE;

    s64Pts += pSidxInfo->earliest_presentation_time;
    s64Pos += pSidxInfo->first_offset;


    ff_add_index_entry(&pSidxInfo->index_entries, &pSidxInfo->entries_nb, &u32AllocatedSize, \
                s64Pos, s64Pts, 0, 0, AVINDEX_KEYFRAME);

    for (i = 0; i < pSidxInfo->reference_count; i++)
    {

        //reference_type    1bit
        //reference_size    31bit
        u32Temp = _SVR_DASH_RB32(&pu8Data);
        u8RefType = (u32Temp & 0x80000000) >> 24;
        u32RefSize = u32Temp & 0x7fffffff;

        //subsegment_duration   32bit
        u32SubSegDuration = _SVR_DASH_RB32(&pu8Data);

        u32Temp = _SVR_DASH_RB32(&pu8Data);
        if (!(u32Temp & 0x80000000))
            continue;
        //starts_with_SAP   1bit
        //SAP_type          3bit
        //SAP_delta_time    28bit

        s64Pts += u32SubSegDuration;
        s64Pos += u32RefSize;

        u32AllocatedSize = pSidxInfo->entries_nb * sizeof(AVIndexEntry);
        ff_add_index_entry(&pSidxInfo->index_entries, &pSidxInfo->entries_nb, &u32AllocatedSize, \
            s64Pos, s64Pts, 0, 0, AVINDEX_KEYFRAME);

        //dash_log("index: %d pos = %lld pts = %lld\n",(i + 1) ,s64Pos,s64Pts);
    }

    return HI_SUCCESS;
}

static inline HI_S32 _SVR_DASH_DoBuildIndex(AVFormatContext *ic, CurlDataMember *curlMember, SidxInfo **ppstSidxInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;
    SidxInfo *pstSidxInfo = NULL;
    HI_U8    *pSidxData = NULL;
    HI_U32   u32SidxSize = 0;

    pstSidxInfo = (SidxInfo *)av_mallocz(sizeof(SidxInfo));
    if (curlMember == NULL)
    {
        pSidxData = ff_mov_get_sidx_data(ic);
        if (pSidxData == NULL)
            s32Ret = HI_FAILURE;
    }
    else
    {
        s32Ret = _SVR_DASH_DownloadSidx(curlMember, curlMember->download_Url);
        pSidxData = curlMember->pData;
        u32SidxSize= curlMember->size;
        curlMember->pData = NULL;
        curlMember->size = 0;
        s32Ret = _SVR_DASH_SearchSidxTag(&pSidxData, &u32SidxSize);
    }

    if (HI_FAILURE == s32Ret)
    {
        av_free(pstSidxInfo);
        pstSidxInfo = NULL;
    }
    else
    {
        _SVR_DASH_AddIndexEntry(pstSidxInfo, pSidxData);
        *ppstSidxInfo = pstSidxInfo;
    }

    if (curlMember != NULL && pSidxData != NULL)
    {
        u32SidxSize = 0;
        av_freep(&pSidxData);
    }

    if (pstSidxInfo != NULL)
        return HI_SUCCESS;

    return HI_FAILURE;
}

static HI_S32 _SVR_DASH_BuildIndex(DASHMember * pstMember, DASHPeriod *pstAttr)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    HI_S32 s32Ret = HI_FAILURE, i, j, count;
    AVFormatContext *ic = NULL;
    AVIOContext *pb = NULL, *adp_pb = NULL;
    Option stOption = {1, 0, 0};
    SidxInfo *pstSidxInfo = NULL;

    if (SINGLE_MEDIA_SEGMENT != pstMember->eRepresentationType)
        return HI_SUCCESS;

    dash_log(DASH_LOG_ERROR, "[%s,%d] start to build indexes....\n", __FUNCTION__, __LINE__);

    manager->Stop();

    for (i = 0; i< pstMember->vid_nb; i++)
    {
        count = manager->GetVideoAdaptionSet(i)->GetRepresentation().size();
        pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.resize(count);
        for (j = 0; j < count; j++)
        {
            pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.at(j) = NULL;
            pstSidxInfo = NULL;
            ic = NULL;
            manager->SetVideoIndex(i, j, true);
            if (!manager->StartVideo(i))
            {
                continue;
            }
            pb = (AVIOContext *)manager->GetVideoAVIOContext(i);
            stOption.representation_index = j;
            s32Ret = _SVR_DASH_SetupContext(pstMember, &ic, NULL,
                    pb, &stOption, HI_FALSE, AVMEDIA_TYPE_VIDEO, i, j);
            if (s32Ret == HI_SUCCESS)
            {
                if (pstMember->bIsISOFF == HI_TRUE)
                {
                    s32Ret = _SVR_DASH_DoBuildIndex(ic, NULL, &pstSidxInfo);
                }
                else
                {
                    pstMember->curlDataMember.download_Url = manager->GetVideoIndexSegment().c_str();
                    s32Ret = _SVR_DASH_DoBuildIndex(ic, &pstMember->curlDataMember, &pstSidxInfo);
                }
                pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.at(j) = pstSidxInfo;
                _SVR_DASHIO_Remove(pstMember, (DASHIOMap *)(ic->pb->opaque));
                ic->pb->opaque = NULL;
                dash_log(DASH_LOG_ERROR, "[%s,%d] build video[%d][%d] index entries return %d, pstSidxInfo[%p] entries_nb:%d\n",
                    __FUNCTION__, __LINE__, i, j, s32Ret, pstSidxInfo, (pstSidxInfo != NULL?pstSidxInfo->entries_nb:0));
            }
            if (ic != NULL)
            {
                adp_pb = ic->pb;
                avformat_close_input(&ic);
                if (adp_pb != NULL)
                {
                    adp_pb->opaque = NULL;
                    avio_close(adp_pb);
                }
            }
            manager->StopVideo(i);
        }
    }

    for (i = 0; i< pstMember->aud_nb; i++)
    {
        count = manager->GetAudioAdaptionSet(i)->GetRepresentation().size();
        pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.resize(count);
        for (j = 0; j < count; j++)
        {
            pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.at(j) = NULL;
            pstSidxInfo = NULL;
            ic = NULL;
            manager->SetAudioIndex(i, j, true);
            if (!manager->StartAudio(i))
            {
                continue;
            }
            pb = (AVIOContext *)manager->GetAudioAVIOContext(i);
            stOption.representation_index = j;
            s32Ret = _SVR_DASH_SetupContext(pstMember, &ic, NULL,
                    pb, &stOption, HI_FALSE, AVMEDIA_TYPE_AUDIO, i, j);
            if (s32Ret == HI_SUCCESS)
            {
                if (pstMember->bIsISOFF == HI_TRUE)
                {
                    s32Ret = _SVR_DASH_DoBuildIndex(ic, NULL, &pstSidxInfo);
                }
                else
                {
                    pstMember->curlDataMember.download_Url = manager->GetAudioIndexSegment().c_str();
                    s32Ret = _SVR_DASH_DoBuildIndex(ic, &pstMember->curlDataMember, &pstSidxInfo);
                }
                pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.at(j) = pstSidxInfo;
                _SVR_DASHIO_Remove(pstMember, (DASHIOMap *)(ic->pb->opaque));
                ic->pb->opaque = NULL;
                dash_log(DASH_LOG_ERROR, "[%s,%d] build audio[%d][%d] index entries return %d, entries_nb:%d\n",
                    __FUNCTION__, __LINE__, i, j, s32Ret, (pstSidxInfo != NULL?pstSidxInfo->entries_nb:0));
            }
            if(ic != NULL)
            {
                adp_pb = ic->pb;
                avformat_close_input(&ic);
                if (adp_pb != NULL)
                {
                    adp_pb->opaque = NULL;
                    avio_close(adp_pb);
                }
            }
            manager->StopAudio(i);
        }
    }

#if 0
    for (i = 0; i < pstMember->sub_nb; i++)
    {
        //Only subtitle  encapsulated in ISO need Index Info
        if (!CHECK_SUBTITLE_TYPE(pstMember->ps32SubtitleType[i], Subtitle_ISO_Mask))
            continue;
        count = manager->GetSubtitleAdaptionSet(i)->GetRepresentation().size();
        pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.resize(count);
        for (j = 0; j < count; j++)
        {
            pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.at(j) = NULL;
            pstSidxInfo = NULL;
            ic = NULL;
            manager->SetSubtitleIndex(i, j, true);
            if (!manager->StartSubtitle(i))
            {
                continue;
            }
            pb = (AVIOContext *)manager->GetSubtitleAVIOContext(i);
            stOption.representation_index = j;
            s32Ret = _SVR_DASH_SetupContext(pstMember, &ic, NULL,
                    pb, &stOption, HI_FALSE, AVMEDIA_TYPE_SUBTITLE, i, j);
            if (s32Ret == HI_SUCCESS)
            {
                s32Ret = _SVR_DASH_DoBuildIndex(ic, NULL, &pstSidxInfo);
                pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.at(j) = pstSidxInfo;
                _SVR_DASHIO_Remove(pstMember, (DASHIOMap *)(ic->pb->opaque));
                ic->pb->opaque = NULL;
                dash_log(DASH_LOG_ERROR, "[%s,%d] build subtitle[%d][%d] index entries return %d, entries_nb:%d\n",
                    __FUNCTION__, __LINE__, i, j, s32Ret, (pstSidxInfo != NULL?pstSidxInfo->entries_nb:0));
            }
            if (ic != NULL)
            {
                adp_pb = ic->pb;
                avformat_close_input(&ic);
                if (adp_pb != NULL)
                {
                    adp_pb->opaque = NULL;
                    avio_close(adp_pb);
                }
            }
            manager->StopSubtitle(i);
        }
    }
#endif

    _SVR_DASH_FreeMasterStream(pstMember);
    dash_log(DASH_LOG_ERROR, "[%s,%d] build indexes....done\n", __FUNCTION__, __LINE__);

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_Init(DASHMember *pstMember)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    int err;
    bool report = false;
    int64_t last = 0;

    if (pstMember->pHttpHeaders != NULL)
    {
        manager->Invoke(MANAGER_INVOKE_SET_HTTP_HEADERS, (void *) pstMember->pHttpHeaders);
    }

    do
    {
        if (pstMember->ic->interrupt_callback.callback(pstMember->ic->interrupt_callback.opaque))
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d]user interrupted!\n", __FUNCTION__, __LINE__);
            return AVERROR_EOF;
        }

        if (last == 0 || av_gettime() - last >= 3000000)
        {
            dash_log(DASH_LOG_INFO, "[%s,%d] start to download MPD...\n", __FUNCTION__, __LINE__);
            if (manager->Init(pstMember->filename, &err))
            {
                dash_log(DASH_LOG_INFO, "[%s,%d] MPD download complete!\n", __FUNCTION__, __LINE__);
                break;
            }
            else if (err != DashError_EmptyMPD)
            {
                dash_log(DASH_LOG_ERROR, "[%s,%d]manager init error %d!\n", __FUNCTION__, __LINE__, err);
                return HI_FAILURE;
            }
            else if (!report)
            {
                dash_errorcode_cb(pstMember->ic->interrupt_callback.opaque, AVEVENT_WAITING_FOR_STREAMREADY, "libdash");
                report = true;
            }
            last = av_gettime();
        }
        usleep(100000);
    }while(err == DashError_EmptyMPD);

    pstMember->ic->is_live_stream = (HI_S32)manager->IsLive();
    pstMember->bIsISOFF = (HI_BOOL)manager->IsISOFF();
    pstMember->ic->duration = manager->GetDuration();
    pstMember->s64AudioFirstPts = AV_NOPTS_VALUE;
    pstMember->s64VideoFirstPts = AV_NOPTS_VALUE;
    pstMember->s64SubtitleFirstPts = AV_NOPTS_VALUE;//AV_NOPTS_VALUE;
    pstMember->stUserSetStreamInfo.s32VidIndex  = -1;
    pstMember->stUserSetStreamInfo.s32AudIndex = -1;
    pstMember->stUserSetStreamInfo.s32SubIndex = -1;
    pstMember->s64LastCheckBWTime = av_gettime();
    pstMember->eLastCheckBWType = AVMEDIA_TYPE_UNKNOWN;
    pstMember->bForcePrint = HI_TRUE;

    if (pstMember->bIsISOFF == HI_FALSE)
        return HI_FAILURE;

    pthread_mutex_init(&pstMember->mUserStreamInfoLock, NULL);

    if (pstMember->ic->is_live_stream && strlen(manager->GetMPD()->GetMinimumUpdatePeriod().c_str()) > 0)
    {
        pstMember->bUpdateMPD = HI_TRUE;
    }
    else
    {
        pstMember->bUpdateMPD = HI_FALSE;
    }
    pstMember->bUsingPlayReady = HI_FALSE;
    dash_log(DASH_LOG_ERROR, "[%s,%d] mpd downloaded,  is_live_stream %d, duration %lld, IsISOFF:%d, bUpdateMPD needed:%d\n",
        __FUNCTION__, __LINE__, pstMember->ic->is_live_stream, pstMember->ic->duration, pstMember->bIsISOFF, pstMember->bUpdateMPD);

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_StartDownload(DASHMember *pstMember, HI_BOOL bResume, HI_BOOL bForceInvokeInit)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    HI_U32 i = 0;
    HI_S32 s32PresentationIndex = 0;

    for (i = 0; i < pstMember->vid_nb; i++)
    {
        if (bResume == HI_FALSE)
            manager->SetVideoPosition(i, pstMember->u32VideoPosition);
        if (i == pstMember->s32VideoAdaptationSetIndex)
        {
            _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_VIDEO, i, pstMember->s32VideoRepresentationIndex, bForceInvokeInit);
        }
        else
        {
            //select the lowest bandwidth presentation to download
            s32PresentationIndex = _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_VIDEO, i, 0);
            _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_VIDEO, i, s32PresentationIndex, bForceInvokeInit);
        }
    }

    for (i = 0;i < pstMember->aud_nb; i++)
    {
        if (bResume == HI_FALSE)
            manager->SetAudioPosition(i, pstMember->u32AudioPosition);
        if (i == pstMember->s32AudioAdaptationSetIndex)
        {
            _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_AUDIO, i, pstMember->s32AudioRepresentationIndex, bForceInvokeInit);
        }
        else
        {
            //select the lowest bandwidth presentation to download
            s32PresentationIndex = _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_AUDIO, i, 0);
            _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_AUDIO, i, 0, bForceInvokeInit);
        }
    }

    for (i = 0;i < pstMember->sub_nb; i++ )
    {
        if (bResume == HI_FALSE)
            manager->SetSubtitlePosition(i, pstMember->u32SubtitlePosition);
        if (i == pstMember->s32SubtitleAdaptationSetIndex)
        {
            _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_SUBTITLE, i, pstMember->s32SubtitleRepresentationIndex, bForceInvokeInit);
        }
        else
        {
             //select the lowest bandwidth presentation to download
            s32PresentationIndex = _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_SUBTITLE, i, 0);
            _SVR_DASH_SetRepresentation(pstMember, AVMEDIA_TYPE_SUBTITLE, i, 0, bForceInvokeInit);
        }
    }

    manager->Start();

#if defined (HISUB_SUPPORT)
    if (pstMember->bHiSubInit != HI_TRUE)
        pstMember->bHiSubInit = (HI_SUCCESS  == HI_SVR_SUB_Parse_Init()) ? HI_TRUE : HI_FALSE;
#endif

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_CloseFormat(DASHMember *pstMember)
{
    HI_U32 i = 0;
    AVIOContext *pb;

    dash_log(DASH_LOG_INFO, "[%s,%d] \n", __FUNCTION__, __LINE__);

    for (i = 0; i < pstMember->vid_nb; i++)
    {
        if (pstMember->vid_ic != NULL && pstMember->vid_ic[i] != NULL)
        {
            pb = pstMember->vid_ic[i]->pb;
            avformat_close_input(&pstMember->vid_ic[i]);
            if (pb != NULL)
            {
                pb->opaque = NULL;
                avio_close(pb);
            }
        }
    }

    for (i = 0; i < pstMember->aud_nb; i++)
    {
        if (pstMember->aud_ic != NULL && pstMember->aud_ic[i] != NULL)
        {
            pb = pstMember->aud_ic[i]->pb;
            avformat_close_input(&pstMember->aud_ic[i]);
            if (pb != NULL)
            {
                pb->opaque = NULL;
                avio_close(pb);
            }
        }
    }

    for (i = 0; i < pstMember->sub_nb; i++)
    {
        if (pstMember->sub_ic != NULL && pstMember->sub_ic[i] != NULL)
        {
            pb = pstMember->sub_ic[i]->pb;
            avformat_close_input(&pstMember->sub_ic[i]);
            if (pb != NULL)
            {
                pb->opaque = NULL;
                avio_close(pb);
            }
        }
        if (NULL != pstMember->ttml_ic)
        {
            pb = pstMember->ttml_ic[i]->pb;
            avformat_close_input(&pstMember->ttml_ic[i]);
            if (pb != NULL)
            {
                pb->opaque = NULL;
                avio_close(pb);
            }
        }
    }

    if (pstMember->vid_ic != NULL)
        av_free(pstMember->vid_ic);
    if (pstMember->aud_ic != NULL)
        av_free(pstMember->aud_ic);
    if (pstMember->sub_ic != NULL)
        av_free(pstMember->sub_ic);
    if (pstMember->ttml_ic != NULL)
        av_free(pstMember->ttml_ic);

    pstMember->vid_ic = NULL;
    pstMember->aud_ic = NULL;
    pstMember->sub_ic = NULL;
    pstMember->ttml_ic = NULL;

    _SVR_DASHIO_FreeAll(pstMember);

    if (pstMember->ps32SubtitleType != NULL)
        av_free(pstMember->ps32SubtitleType);

    pstMember->ps32SubtitleType = NULL;

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_PT2Seconds(const char *pszPTStr, HI_DOUBLE *pfSeconds)
{
    HI_S32    h = 0,m = 0;
    HI_FLOAT s = 0.0;

    if (strchr(pszPTStr, 'H'))
    {
        sscanf(pszPTStr, "PT%dH%dM%fS", &h, &m, &s);
    }
    else if (strchr(pszPTStr, 'M'))
    {
        sscanf(pszPTStr, "PT%dM%fS" ,&m, &s);
    }
    else
    {
        sscanf(pszPTStr, "PT%fS" ,&s);
    }

    *pfSeconds = h*3600 + m * 60 + s;

    dash_log(DASH_LOG_INFO, "[%s,%d] pszPTStr:%s -> hour:%d,minute:%d, seconds:%f, covert to senconds %f\n", __FUNCTION__, __LINE__, pszPTStr, h, m ,s, *pfSeconds);

    return HI_SUCCESS;
}

/*
@s32StreamIndex:@s64Pts that belong to.
*/
static HI_S64 _SVR_DASH_PTS2Ms(DASHMember *pstMember, HI_S64 s64Pts, HI_S32 s32StreamIndex)
{
        AVStream * st = NULL;
        HI_S32 i;
        HI_S64 s64PtsInMs;

        if (s64Pts <= 0)
            return 0;

        if (pstMember->bSetupFinish == HI_FALSE)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] bSetupFinish is false ,can't covert seek pts to ms!\n", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }

        for (i = 0 ; i < pstMember->ic->nb_streams; i++)
        {
            st = pstMember->ic->streams[i];
            if (st->index == s32StreamIndex)
                break;
        }

        if (i >= pstMember->ic->nb_streams)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] can't find stream of stream_index %d!\n", __FUNCTION__, __LINE__, s32StreamIndex);
            return HI_FAILURE;
        }

        if (st->time_base.den != 0 && st->time_base.num != 0)
            s64PtsInMs = s64Pts * 1000 * st->time_base.num / st->time_base.den;
        else
            s64PtsInMs = s64Pts;

        dash_log(DASH_LOG_INFO, "[%s,%d] stream[%d] pts %lld covert to ms is %lld!\n",
            __FUNCTION__, __LINE__, s32StreamIndex, s64Pts, s64PtsInMs);

        return s64PtsInMs;
}

static inline HI_S32 _SVR_DASH_UpdatePktPts(DASHMember * pstMember, AVPacket * pkt)
{
    HI_S64 s64PeriodBasePts;
    AVStream * st = NULL;

    if (pkt == NULL)
        return HI_FAILURE;

    s64PeriodBasePts = pstMember->stCurPeriod.startMs;

    st = pstMember->ic->streams[pkt->stream_index];
    if (st->time_base.den != 0 && st->time_base.num != 0)
        s64PeriodBasePts = s64PeriodBasePts * st->time_base.den/ st->time_base.num;
    else
        s64PeriodBasePts = 0;

    s64PeriodBasePts /= 1000;

    pkt->pts += s64PeriodBasePts;
    pkt->dts += s64PeriodBasePts;

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_GetPeriodFromPts(DASHMember *pstMember, HI_S64 s64Pts, IPeriod **ppstPeriod)
{
        MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
        IPeriod * period = NULL;
        HI_S32 s32PeriodNum = manager->GetMPD()->GetPeriods().size();
        HI_S32 i;
        HI_DOUBLE fStart, fDuration, fLastStart, fTotal = 0.0;
        HI_S64 s64PtsInSeconds = s64Pts/1000;
        AVStream * st = NULL;

        *ppstPeriod = NULL;

        if (s32PeriodNum <= 0)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] error, no periods\n", __FUNCTION__, __LINE__);
            return -1;
        }

        for (i = 0; i < s32PeriodNum; i ++)
        {
            fStart = 0.0;
            fDuration = 0.0;
            period = manager->GetMPD()->GetPeriods().at(i);
            if (period)
            {
                if (strlen(period->GetStart().c_str()) > 0)
                {
                    _SVR_DASH_PT2Seconds(period->GetStart().c_str(), &fStart);
                    fTotal = fStart;
                }

                if (strlen(period->GetDuration().c_str()) > 0)
                {
                    _SVR_DASH_PT2Seconds(period->GetDuration().c_str(), &fDuration);
                }

                if (s64PtsInSeconds >= fTotal && s64PtsInSeconds <= (fTotal + fDuration))
                {
                    dash_log(DASH_LOG_INFO, "[%s,%d] period %d (Start=%s, Duration=%s) found for pts %lld\n",
                        __FUNCTION__, __LINE__, i, period->GetStart().c_str(), period->GetDuration().c_str(), s64Pts);
                    break;
                }
                if (s64PtsInSeconds >= fLastStart &&  s64PtsInSeconds <= fTotal)
                {
                    i = i - 1;
                    break;
                }
                /*the last period without @duration*/
                if (i == s32PeriodNum - 1 && s64PtsInSeconds >= fTotal && fDuration <= 0.0)
                    break;
                fLastStart = fTotal;
                fTotal += fDuration;
            }
        }

        if (i >= s32PeriodNum)
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] no period found for pts %lld(s64PtsInSeconds:%lld)\n",  __FUNCTION__, __LINE__, s64Pts, s64PtsInSeconds);
            return -1;
        }

        period = manager->GetMPD()->GetPeriods().at(i);
        *ppstPeriod = period;

        return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_GetPeriodAttr(DASHMember *pstMember, IPeriod * pstCurPeriod, DASHPeriod *pstAttr, HI_BOOL bNew)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    HI_S32 s32PeriodNum;
    IPeriod *period;
    HI_DOUBLE fStartSecond, fDuration;
    HI_DOUBLE fNextPeriodStartSec, fNextPeriodDuration;
    HI_DOUBLE fLastPeriodStartSec, fLastPeriodDuration;
    HI_S32 i;
    HI_BOOL bPeriodMatch = HI_FALSE;

    //can't set here
    //memset(pstAttr, 0, sizeof(*pstAttr));
    snprintf(pstAttr->id, sizeof(pstAttr->id), "%s", pstCurPeriod->GetId().c_str());
    snprintf(pstAttr->start, sizeof(pstAttr->start), "%s", pstCurPeriod->GetStart().c_str());
    snprintf(pstAttr->duration, sizeof(pstAttr->duration), "%s", pstCurPeriod->GetDuration().c_str());

    s32PeriodNum = manager->GetMPD()->GetPeriods().size();
    if (s32PeriodNum <= 1 || (strlen(pstAttr->start) > 0 && strlen(pstAttr->duration) > 0))
    {
        _SVR_DASH_PT2Seconds(pstAttr->start, &fStartSecond);
        _SVR_DASH_PT2Seconds(pstAttr->duration, &fDuration);

        pstAttr->startMs = (int64_t)(1000.0*fStartSecond);
        pstAttr->durationMs = (int64_t)(1000.0*fDuration);
    }
    //if @start or @duration is absent
    else
    {
        period = manager->GetMPD()->GetPeriods().at(0);
        _SVR_DASH_PT2Seconds(period->GetStart().c_str(), &fLastPeriodStartSec);
        _SVR_DASH_PT2Seconds(period->GetDuration().c_str(), &fLastPeriodDuration);

        fNextPeriodStartSec = fLastPeriodStartSec + fLastPeriodDuration;
        fNextPeriodDuration = 0.0;
        fStartSecond = -1.0;
        fDuration = -1.0;

        if (period == pstCurPeriod)
            bPeriodMatch = HI_TRUE;

        for (i = 1; i < s32PeriodNum; i++)
        {
            fNextPeriodDuration = 0.0;
            period = manager->GetMPD()->GetPeriods().at(i);
            if (strlen(period->GetStart().c_str()) > 0)
            {
                _SVR_DASH_PT2Seconds(period->GetStart().c_str(), &fNextPeriodStartSec);
                if (period == pstCurPeriod)
                    fStartSecond = fNextPeriodStartSec;
            }
            else
            {
                fNextPeriodStartSec = fLastPeriodStartSec + fLastPeriodDuration;
            }

            if (bPeriodMatch == HI_TRUE)
                break;

            if (strlen(period->GetDuration().c_str()) > 0)
            {
                _SVR_DASH_PT2Seconds(period->GetDuration().c_str(), &fNextPeriodDuration);
                if (period == pstCurPeriod)
                    fDuration = fNextPeriodDuration;
            }

            fLastPeriodStartSec = fNextPeriodStartSec;
            fLastPeriodDuration = fNextPeriodDuration;

            if (period == pstCurPeriod)
            {
                   bPeriodMatch = HI_TRUE;
                   if (i == s32PeriodNum - 1 && manager->GetDuration() > 0)
                       fNextPeriodStartSec = manager->GetDuration()/1000000;
            }
        }

        if (fStartSecond < 0)
            fStartSecond = fLastPeriodStartSec;
        if (fDuration < 0)
            fDuration = fNextPeriodStartSec - fLastPeriodStartSec;

        pstAttr->startMs = (int64_t)(1000.0*fStartSecond);
        pstAttr->durationMs = (int64_t)(1000.0*fDuration);

        if (bPeriodMatch == HI_FALSE)
            dash_log(DASH_LOG_ERROR, "[%s,%d] error, no period matched\n", __FUNCTION__, __LINE__);
    }

    dash_log(DASH_LOG_ERROR, "[%s,%d] period @id=%s, @start=%s(%lld ms), @duration=%s(%lld ms)\n",
        __FUNCTION__, __LINE__, pstAttr->id, pstAttr->start, pstAttr->startMs, pstAttr->duration, pstAttr->durationMs);

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_FreePeriodAttr(DASHPeriod *pstAttr)
{
    HI_S32 i, j, count;

    dash_log(DASH_LOG_INFO, "[%s,%d]\n", __FUNCTION__, __LINE__);

    for (i = 0; i < pstAttr->videoAdaptionsets.size(); i++)
    {
        count = pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.size();
        for (j = 0; j< count; j ++)
        {
            if (pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.at(j) != NULL)
            {
                av_free(pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.at(j)->index_entries);
                av_free(pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.at(j));
                pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.at(j) = NULL;
            }
        }
        pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.clear();
    }
    pstAttr->videoAdaptionsets.clear();

    for (i = 0; i < pstAttr->audioAdaptionsets.size(); i++)
    {
        count = pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.size();
        for (j = 0; j< count; j ++)
        {
            if (pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.at(j) != NULL)
            {
                av_free(pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.at(j)->index_entries);
                av_free(pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.at(j));
                pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.at(j) = NULL;
            }
        }
        pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.clear();
    }
    pstAttr->audioAdaptionsets.clear();

    for (i = 0; i < pstAttr->subtitleAdaptionsets.size(); i++)
    {
        count = pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.size();
        for (j = 0; j< count; j ++)
        {
            if (pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.at(j) != NULL)
            {
                av_free(pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.at(j)->index_entries);
                av_free(pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.at(j));
                pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.at(j) = NULL;
            }
        }
        pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.clear();
    }
    pstAttr->subtitleAdaptionsets.clear();

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_InitPeriodAttr(DASHMember *pstMember, DASHPeriod *pstAttr)
{
    HI_S32 i;
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;

    dash_log(DASH_LOG_INFO, "[%s,%d] vid_nb:%d, aud_nb:%d, sub_nb:%d\n",
        __FUNCTION__, __LINE__, pstMember->vid_nb, pstMember->aud_nb, pstMember->sub_nb);

    pstAttr->videoAdaptionsets.resize(pstMember->vid_nb);
    for (i = 0; i < pstMember->vid_nb; i++)
    {
        snprintf(pstAttr->videoAdaptionsets.at(i).lang, DASH_ATTR_STR_LEN, "%s", manager->GetVideoAdaptionSet(i)->GetLang().c_str());
        pstAttr->videoAdaptionsets.at(i).curRepresentation.id[0] = 0;
        pstAttr->videoAdaptionsets.at(i).curRepresentation.bandwidth[0] = 0;
        pstAttr->videoAdaptionsets.at(i).curRepresentation.codecs[0] = 0;
        pstAttr->videoAdaptionsets.at(i).curRepresentation.bandwidthBps = 0;
        dash_log(DASH_LOG_INFO, "[%s,%d] video adaptionset[%d] @lang=%s\n", __FUNCTION__, __LINE__, i, pstAttr->videoAdaptionsets.at(i).lang);
    }

    pstAttr->audioAdaptionsets.resize(pstMember->aud_nb);
    for (i = 0; i < pstMember->aud_nb; i++)
    {
        snprintf(pstAttr->audioAdaptionsets.at(i).lang, DASH_ATTR_STR_LEN, "%s", manager->GetAudioAdaptionSet(i)->GetLang().c_str());
        pstAttr->audioAdaptionsets.at(i).curRepresentation.id[0] = 0;
        pstAttr->audioAdaptionsets.at(i).curRepresentation.bandwidth[0] = 0;
        pstAttr->audioAdaptionsets.at(i).curRepresentation.codecs[0] = 0;
        pstAttr->audioAdaptionsets.at(i).curRepresentation.bandwidthBps = 0;
        dash_log(DASH_LOG_INFO, "[%s,%d] audio adaptionset[%d] @lang=%s\n", __FUNCTION__, __LINE__, i, pstAttr->audioAdaptionsets.at(i).lang);
    }

    pstAttr->subtitleAdaptionsets.resize(pstMember->sub_nb);
    for (i = 0; i < pstMember->sub_nb; i++)
    {
        snprintf(pstAttr->subtitleAdaptionsets.at(i).lang, DASH_ATTR_STR_LEN, "%s", manager->GetSubtitleAdaptionSet(i)->GetLang().c_str());
        pstAttr->subtitleAdaptionsets.at(i).curRepresentation.id[0] = 0;
        pstAttr->subtitleAdaptionsets.at(i).curRepresentation.bandwidth[0] = 0;
        pstAttr->subtitleAdaptionsets.at(i).curRepresentation.codecs[0] = 0;
        pstAttr->subtitleAdaptionsets.at(i).curRepresentation.bandwidthBps = 0;
        dash_log(DASH_LOG_INFO, "[%s,%d] subtitle adaptionset[%d] @lang=%s\n", __FUNCTION__, __LINE__, i, pstAttr->subtitleAdaptionsets.at(i).lang);
    }

    if (pstMember->ic->is_live_stream == 0)
        _SVR_DASH_BuildIndex(pstMember, pstAttr);

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_SetSAPs(DASHMember *pstMember)
{
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    HI_S32 s32Ret = HI_FAILURE, i, j, entry, count;
    DASHPeriod *pstAttr = &pstMember->stCurPeriod;
    SidxInfo *pstSidxInfo = NULL;
    std::vector<uint64_t> saps;

    if (SINGLE_MEDIA_SEGMENT != pstMember->eRepresentationType)
        return HI_SUCCESS;

    saps.clear();
    for (i = 0; i< pstMember->vid_nb; i++)
    {
        count = pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.size();
        for (j = 0; j < count; j++)
        {
            pstSidxInfo = pstAttr->videoAdaptionsets.at(i).representationsSidxinfo.at(j);
            if (pstSidxInfo != NULL)
            {
                saps.resize(pstSidxInfo->entries_nb);
                for (entry = 0; entry < saps.size(); entry ++)
                {
                     saps.at(entry) = pstSidxInfo->index_entries[entry].pos;
                }
                if (0 == manager->SetVideoRepresentationSAPs(i, j , saps))
                {
                    dash_log(DASH_LOG_INFO, "[%s,%d] set SAPs to video[%d][%d] success!\n", __FUNCTION__, __LINE__, i, j);
                }
                else
                {
                    dash_log(DASH_LOG_ERROR, "[%s,%d] set SAPs to video[%d][%d] error!\n", __FUNCTION__, __LINE__, i, j);
                }
            }
        }
    }

    saps.clear();
    for (i = 0; i< pstMember->aud_nb; i++)
    {
        count = pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.size();
        for (j = 0; j < count; j++)
        {
            pstSidxInfo = pstAttr->audioAdaptionsets.at(i).representationsSidxinfo.at(j);
            if (pstSidxInfo != NULL)
            {
                saps.resize(pstSidxInfo->entries_nb);
                for (entry = 0; entry < saps.size(); entry ++)
                {
                    saps.at(entry) = pstSidxInfo->index_entries[entry].pos;
                }
                if (0 == manager->SetAudioRepresentationSAPs(i, j , saps))
                {
                    dash_log(DASH_LOG_INFO, "[%s,%d] set SAPs to audio[%d][%d] success!\n", __FUNCTION__, __LINE__, i, j);
                }
                else
                {
                    dash_log(DASH_LOG_ERROR, "[%s,%d] set SAPs to audio[%d][%d] error!\n", __FUNCTION__, __LINE__, i, j);
                }
            }
        }
    }

    saps.clear();
    for (i = 0; i< pstMember->sub_nb; i++)
    {
        count = pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.size();
        for (j = 0; j < count; j++)
        {
            pstSidxInfo = pstAttr->subtitleAdaptionsets.at(i).representationsSidxinfo.at(j);
            if (pstSidxInfo != NULL)
            {
                saps.resize(pstSidxInfo->entries_nb);
                for (entry = 0; entry < saps.size(); entry ++)
                {
                    saps.at(entry) = pstSidxInfo->index_entries[entry].pos;
                }
                if (0 == manager->SetSubtitleRepresentationSAPs(i, j , saps))
                {
                    dash_log(DASH_LOG_INFO, "[%s,%d] set SAPs to subtitle[%d][%d] success!\n", __FUNCTION__, __LINE__, i, j);
                }
                else
                {
                    dash_log(DASH_LOG_ERROR, "[%s,%d] set SAPs to subtitle[%d][%d] error!\n", __FUNCTION__, __LINE__, i, j);
                }
            }
        }
    }
    saps.clear();

    return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_PlayPeriod(DASHMember *pstMember, IPeriod * period, HI_BOOL bNew)
{
        MultimediaManager *manager = (MultimediaManager *)pstMember->manager;

        dash_log(DASH_LOG_ERROR, "%s,%d try to stop and play period, @id=%s, @start=%s, @duration=%s, bNew:%d\n",
            __FUNCTION__, __LINE__, period->GetId().c_str(), period->GetStart().c_str(), period->GetDuration().c_str(), bNew);

        manager->Destroy();
        if (true != manager->SetCurrentPeriod(period))
        {
            dash_log(DASH_LOG_ERROR, "%s,%d error, SetCurrentPeriod return false\n", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }

        if (!manager->Create())
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] error, manager create return false\n", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }

        pstMember->vid_nb = manager->GetVideoAdaptationSetNum();
        pstMember->aud_nb = manager->GetAudioAdaptationSetNum();
        //not support subtitle.
        //pstMember->sub_nb = manager->GetSubtitleAdaptationSetNum();
        pstMember->sub_nb = 0;
        pstMember->eRepresentationType = (REPRESENTATION_STREAM_TYPE)manager->GetRepresentationStreamType();

        dash_log(DASH_LOG_ERROR, "[%s,%d] vid_nb:%d, aud_nb:%d, sub_nb:%d\n", __FUNCTION__, __LINE__,
            pstMember->vid_nb, pstMember->aud_nb, pstMember->sub_nb);

        if (pstMember->vid_nb + pstMember->aud_nb <= 0)
        {
            return HI_FAILURE;
        }

        if (bNew == HI_TRUE)
        {
            _SVR_DASH_FreePeriodAttr(&pstMember->stCurPeriod);
            _SVR_DASH_InitPeriodAttr(pstMember, &pstMember->stCurPeriod);
            pstMember->s32VideoAdaptationSetIndex = _SVR_DASH_SelectAdaptionset(pstMember, AVMEDIA_TYPE_VIDEO);
            pstMember->s32AudioAdaptationSetIndex = _SVR_DASH_SelectAdaptionset(pstMember, AVMEDIA_TYPE_AUDIO);
            pstMember->s32SubtitleAdaptationSetIndex = _SVR_DASH_SelectAdaptionset(pstMember, AVMEDIA_TYPE_SUBTITLE);
            //play the first period from the latest segment if live, latter 2nd,3rd...period start from the first segment.
            if (pstMember->s32PeriodNum <= 0)
            {
                pstMember->u32VideoPosition    = 0;//0xffffffff;
                pstMember->u32AudioPosition    = 0;//0xffffffff;
                pstMember->u32SubtitlePosition = 0;//0xffffffff;
            }
            else
            {
                pstMember->u32VideoPosition    = 0;
                pstMember->u32AudioPosition    = 0;
                pstMember->u32SubtitlePosition = 0;
            }

            pstMember->u32VReadOKCount = 0;
            pstMember->u32AReadOKCount = 0;
            pstMember->u32SReadOKCount = 0;
            pstMember->u32VTryRead= 0;
            pstMember->u32ATryRead = 0;
            pstMember->u32STryRead = 0;
            pstMember->s32PeriodNum ++;
        }

        if (SINGLE_MEDIA_SEGMENT == pstMember->eRepresentationType)
            _SVR_DASH_SetSAPs(pstMember);

        _SVR_DASH_GetPeriodAttr(pstMember, period, &pstMember->stCurPeriod, bNew);

        pstMember->s64LastCheckBWTime = av_gettime();
        pstMember->eLastCheckBWType = AVMEDIA_TYPE_UNKNOWN;
        pstMember->s32VideoRepresentationIndex = \
            _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_VIDEO, pstMember->s32VideoAdaptationSetIndex, pstMember->u32VideoBandWidth);
        pstMember->s32AudioRepresentationIndex = \
            _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_AUDIO, pstMember->s32AudioAdaptationSetIndex, pstMember->u32AudioBandWidth);
        pstMember->s32SubtitleRepresentationIndex = \
            _SVR_DASH_SelectRepresentation(pstMember, AVMEDIA_TYPE_SUBTITLE, pstMember->s32SubtitleAdaptationSetIndex, pstMember->u32SubtitleBandWidth);

        pstMember->bFirstFrame = HI_TRUE;

        if (HI_SUCCESS != _SVR_DASH_StartDownload(pstMember, (bNew==HI_TRUE?HI_FALSE:HI_TRUE), HI_FALSE))
        {
            dash_log(DASH_LOG_ERROR, "[%s,%d] _SVR_DASH_StartDownload failed\n", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }

        if (bNew != HI_TRUE)
        {
            _SVR_DASHIO_Update(pstMember);
        }

        pstMember->bForcePrint = HI_TRUE;
        dash_log(DASH_LOG_ERROR, "[%s,%d] play period success, @id=%s, @start=%s, @duration=%s, LastPts(V:%lld, A:%lld, S:%lld)\n",
            __FUNCTION__, __LINE__, period->GetId().c_str(), period->GetStart().c_str(),
            period->GetDuration().c_str(), pstMember->s64VideoLastPts, pstMember->s64AudioLastPts,
            pstMember->s64SubtitleLastPts);

        return HI_SUCCESS;
}

static HI_S32 _SVR_DASH_PlayNextPeriod(DASHMember *pstMember)
{
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    HI_S32 s32PeriodNum = manager->GetMPD()->GetPeriods().size();
    IPeriod *pstNextPeriod = NULL;

    dash_log(DASH_LOG_ERROR, "[%s,%d] find next play period\n", __FUNCTION__, __LINE__);

    _SVR_DASH_FindNextPeriod(pstMember, &pstNextPeriod);
    if (pstNextPeriod == NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] no periods left to play\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    return _SVR_DASH_PlayPeriod(pstMember, pstNextPeriod, HI_TRUE);
}

HI_S32 HI_SVR_DASH_Open(const HI_CHAR *pszFileName, const HI_FORMAT_PROTOCOL_FUN_S *pstProtocol, HI_HANDLE *pFmtHandle)
{
    DASHMember * member = NULL;
    member = (DASHMember *)av_malloc(sizeof(DASHMember));
    if (NULL == member)
    {
        dash_log(DASH_LOG_ERROR, "can not malloc DASH_MEMBER_S!\n");
        return HI_FAILURE;
    }
    memset(member, 0, sizeof(DASHMember));

    MultimediaManager *manager = new MultimediaManager(NULL);
    if (NULL == manager)
    {
        dash_log(DASH_LOG_ERROR, "can not create DASHReceiver!");
        av_free(member);
        return HI_FAILURE;
    }

    member->manager = manager;
    memcpy(member->filename, pszFileName, strlen(pszFileName));

    *pFmtHandle = (HI_HANDLE)member;

    return HI_SUCCESS;
}

HI_S32 HI_SVR_DASH_FindStream(HI_HANDLE fmtHandle, HI_VOID *pArg)
{
    DASHMember * pstMember = (DASHMember *)fmtHandle;
    HI_S32 s32Ret = HI_FAILURE;
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;

    pstMember->ic = (AVFormatContext *)pArg;
    dash_log(DASH_LOG_ERROR, "[%s,%d] pb:%p IN\n", __FUNCTION__, __LINE__, pstMember->ic->pb);

    if (HI_SUCCESS != _SVR_DASH_Init(pstMember))
        return HI_FAILURE;

    if (manager->GetMPD()->GetPeriods().size() <= 0 ||
        HI_SUCCESS != _SVR_DASH_PlayPeriod(pstMember, manager->GetMPD()->GetPeriods().at(0), HI_TRUE))
        return HI_FAILURE;

    pstMember->bSetupFinish = HI_FALSE;
    if (HI_SUCCESS != _SVR_DASH_Setup(pstMember))
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] _SVR_DASH_Setup failed\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

#ifdef PLAYREADY_SUPPORT
    _SVR_DASH_CheckDRMSystem(pstMember);
    if (HI_TRUE == pstMember->bUsingPlayReady)
    {
       (HI_VOID)HI_PLAYREADY_Init();
        if (_SVR_DASH_PlayReady_Open(pstMember) != HI_SUCCESS)
        {
            dash_log(DASH_LOG_ERROR, "[%s:%d] _SVR_DASH_PlayReady_Open failed!\n", __FILE__, __LINE__);
            pstMember->bUsingPlayReady = HI_FALSE;
        }
    }
#endif

    dash_log(DASH_LOG_ERROR, "[%s,%d] OUT\n", __FUNCTION__, __LINE__);

    pstMember->bSetupFinish = HI_TRUE;
    pstMember->bVideoChangePresenFinish = HI_TRUE;
    pstMember->bAudioChangePresenFinish = HI_TRUE;
    pstMember->bSubtitleChangePresenFinish = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 HI_SVR_DASH_SeekPts(HI_HANDLE fmtHandle, HI_S32 s32StreamIndex, HI_S64 s64Pts, HI_FORMAT_SEEK_FLAG_E eFlag)
{
    DASHMember * pstMember = (DASHMember *)fmtHandle;
    MultimediaManager * manager = (MultimediaManager *)pstMember->manager;
    HI_S32 s32Ret = HI_FAILURE;
    IPeriod *period = NULL;
    HI_S64 s64PtsInMs;
    HI_BOOL bNewPeriod = HI_FALSE;
    HI_U32 i = 0;

    if (pstMember->ic->is_live_stream)
        return HI_FAILURE;

    dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] seek to %lld start ...flag %d\n", __FUNCTION__, __LINE__, s64Pts, eFlag);

    if (SINGLE_MEDIA_SEGMENT == pstMember->eRepresentationType &&
        0 != s64Pts &&
        HI_FALSE == _SVR_DASH_IsSingleSegmentSeekable(pstMember))
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] not seekable\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    s64PtsInMs = _SVR_DASH_PTS2Ms(pstMember, s64Pts, s32StreamIndex);
    if (s64PtsInMs >= 0)
    {
        _SVR_DASH_GetPeriodFromPts(pstMember, s64PtsInMs, &period);
        if (period == NULL)
            return HI_FAILURE;
        if (period != manager->GetCurrentPeriod())
        {
            if (HI_SUCCESS != _SVR_DASH_PlayPeriod(pstMember, period, HI_TRUE))
            {
                pstMember->bVideoEosReached = HI_TRUE;
                pstMember->bAudioEosReached = HI_TRUE;
                pstMember->bSubtitleEosReached = HI_TRUE;
                return HI_FAILURE;
            }
            bNewPeriod = HI_TRUE;
        }
        //TODO:update s64Pts
        s64Pts = s64PtsInMs - pstMember->stCurPeriod.startMs;
        dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] seek pts update to %lld\n", __FUNCTION__, __LINE__, s64Pts);
    }

    pstMember->bSeeking = HI_TRUE;
    switch(pstMember->eRepresentationType)
    {
        case SINGLE_MEDIA_SEGMENT:
            //Do I frame seek in this case
            pstMember->bFirstFrame = HI_TRUE;
            s32Ret = _SVR_DASH_SeekSingleSegment(pstMember, s32StreamIndex, s64Pts);
            break;
        case SEGMENT_TEMPLATE:
        case SEGMENT_LIST:
            //Can not do seek accurately in this case
            pstMember->bFirstFrame = HI_TRUE;
            s32Ret = _SVR_DASH_SeekMultiSegment(pstMember, s32StreamIndex, s64Pts, eFlag);
            break;
        default:
            s32Ret = HI_FAILURE;
    }

    if (HI_SUCCESS == s32Ret)
    {
        //TODO : reopen ALL demux?
        dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] MultimediaManager Stop && Start!\n", __FUNCTION__, __LINE__);
        manager->Stop();
        _SVR_DASH_StartDownload(pstMember, HI_FALSE, HI_TRUE);//we'll close format ,so force to invoke init.
    }

    if (bNewPeriod == HI_TRUE || HI_SUCCESS == s32Ret)
    {
        pstMember->bSetupFinish = HI_FALSE;
        //_SVR_DASH_CloseFormat(pstMember);
        //_SVR_DASH_FreeMasterStream(pstMember);
        s32Ret = _SVR_DASH_Setup(pstMember);
        manager = (MultimediaManager *)pstMember->manager;
        if (HI_SUCCESS == s32Ret)
        {
            pstMember->bSetupFinish = HI_TRUE;
            pstMember->bVideoEosReached = HI_FALSE;
            pstMember->bAudioEosReached = HI_FALSE;
            pstMember->bSubtitleEosReached = HI_FALSE;

            pstMember->bVideoChangePresenFinish = HI_TRUE;
            pstMember->bAudioChangePresenFinish = HI_TRUE;
            pstMember->bSubtitleChangePresenFinish = HI_TRUE;
        }
        else
        {
           pstMember->bVideoEosReached = HI_TRUE;
           pstMember->bAudioEosReached = HI_TRUE;
           pstMember->bSubtitleEosReached = HI_TRUE;
        }
    }

    pstMember->bSeeking = HI_FALSE;

    if (HI_SUCCESS == s32Ret)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] seek to %lld finish, LastPts(V:%lld, A:%lld, S:%lld),FirstPts(V:%lld, A:%lld, S:%lld)\n",
            __FUNCTION__, __LINE__, s64Pts, pstMember->s64VideoLastPts, pstMember->s64AudioLastPts,
            pstMember->s64SubtitleLastPts, pstMember->s64VideoFirstPts, pstMember->s64AudioFirstPts, pstMember->s64SubtitleFirstPts);
    }
    else
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d][SEEK] seek to %lld error, LastPts(V:%lld, A:%lld, S:%lld),FirstPts(V:%lld, A:%lld, S:%lld)\n",
            __FUNCTION__, __LINE__, s64Pts, pstMember->s64VideoLastPts, pstMember->s64AudioLastPts,
            pstMember->s64SubtitleLastPts, pstMember->s64VideoFirstPts, pstMember->s64AudioFirstPts, pstMember->s64SubtitleFirstPts);
    }

    return HI_SUCCESS;
}

HI_S32 HI_SVR_DASH_Close(HI_HANDLE fmtHandle)
{
    DASHMember * pstMember = (DASHMember *)fmtHandle;
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    std::vector<DASHAdaptionSet> vct1, vct2, vct3;

    dash_log(DASH_LOG_ERROR, "[%s,%d] start close dash...\n", __FUNCTION__, __LINE__);
    pstMember->bSetupFinish = HI_FALSE;

    if (manager != NULL)
    {
        dash_log(DASH_LOG_ERROR, "[%s,%d] start delete MultimediaManager !\n", __FUNCTION__, __LINE__);
        delete manager;
        dash_log(DASH_LOG_ERROR, "[%s,%d] delete MultimediaManager done.\n", __FUNCTION__, __LINE__);
    }

    _SVR_DASH_FreePeriodAttr(&pstMember->stCurPeriod);
    pstMember->stCurPeriod.videoAdaptionsets.swap(vct1);
    pstMember->stCurPeriod.audioAdaptionsets.swap(vct2);
    pstMember->stCurPeriod.subtitleAdaptionsets.swap(vct3);
    _SVR_DASH_CloseFormat(pstMember);

    if (pstMember->pHttpHeaders!= NULL)
    {
        av_free(pstMember->pHttpHeaders);
        pstMember->pHttpHeaders = NULL;
    }

    pthread_mutex_destroy(&pstMember->mUserStreamInfoLock);

#ifdef PLAYREADY_SUPPORT
    if (HI_TRUE == pstMember->bUsingPlayReady)
    {
        _SVR_DASH_PlayReady_Close(pstMember);
        (HI_VOID)HI_PLAYREADY_DeInit();
        pstMember->bUsingPlayReady = HI_FALSE;
    }
#endif

    memset(pstMember, 0, sizeof(DASHMember));
    av_free(pstMember);

#if defined (HISUB_SUPPORT)
    if (HI_TRUE == pstMember->bHiSubInit)
        (HI_VOID)HI_SVR_SUB_Parse_DeInit();
#endif
    dash_log(DASH_LOG_ERROR, "[%s,%d] close dash OK\n", __FUNCTION__, __LINE__);

    return HI_SUCCESS;
}

HI_S32 HI_SVR_DASH_Invoke(HI_HANDLE fmtHandle, HI_U32 u32InvokeId, HI_VOID *pArg)
{
    DASHMember * pstMember = (DASHMember *)fmtHandle;
    MultimediaManager *manager = (MultimediaManager *)pstMember->manager;
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_DASH_INVOKE_READ == u32InvokeId)
    {
        if (NULL == pArg)
            return HI_FAILURE;

        s32Ret = _SVR_DASH_ReadFrame(fmtHandle, pArg);
        manager = (MultimediaManager *)pstMember->manager;
    }
    else if (HI_DASH_INVOKE_GET_VIDEO_RATING == u32InvokeId)
    {
        if (NULL == pArg)
            return HI_FAILURE;

        *(HI_CHAR **)pArg = av_strdup(manager->GetVideoRating().c_str());
    }
    else if (HI_DASH_INVOKE_GET_AUDIO_RATING == u32InvokeId)
    {
        if (NULL == pArg)
            return HI_FAILURE;

        *(HI_CHAR **)pArg = av_strdup(manager->GetAudioRating().c_str());
    }
    else if (HI_DASH_INVOKE_GET_SUBTITLE_RATING == u32InvokeId)
    {
        if (NULL == pArg)
            return HI_FAILURE;

        *(HI_CHAR **)pArg = av_strdup(manager->GetSubtitleRating().c_str());
    }
    else if (HI_DASH_INVOKE_GET_BANDWIDTH == u32InvokeId)
    {
        if (NULL == pArg)
            return HI_FAILURE;

        //Change it to bit/s
        if (pstMember->vid_nb > 0)
        {
            *(HI_S64 *)pArg = (HI_S64)manager->GetVideoBandWidth();
            return HI_SUCCESS;
        }

        if (pstMember->aud_nb > 0)
        {
            *(HI_S64 *)pArg = (HI_S64)manager->GetAudioBandWidth();
            return HI_SUCCESS;
        }

        *(HI_S64 *)pArg = 0;
    }
    else if (HI_DASH_INVOKE_SET_ID == u32InvokeId)
    {
        if (NULL == pArg)
            return HI_FAILURE;

        HI_DASH_STREAM_INFO_S * pstStreamInfo = (HI_DASH_STREAM_INFO_S *)pArg;
        s32Ret = _SVR_DASH_SetAdaptationset(pstMember, pstStreamInfo);
    }
    else if (HI_DASH_INVOKE_SET_ERRORCODECB == u32InvokeId)
    {
        if (NULL == pArg)
            return HI_FAILURE;

        dash_errorcode_cb = (URLErrorCodeCB *)pArg;
    }
    else if (HI_DASH_INVOKE_SET_LOG_LEVEL == u32InvokeId)
    {
        if (NULL == pArg)
            return HI_FAILURE;

        HI_S32 s32LogLevel = *(HI_S32 *)pArg;
        dash_log_set_level(s32LogLevel);
    }
    else if (HI_DASH_INVOKE_PRE_CLOSE_FILE == u32InvokeId)
    {
        if (NULL == manager)
            return HI_FAILURE;

        dash_log(DASH_LOG_ERROR, "[%s,%d] HI_DASH_INVOKE_PRE_CLOSE_FILE\n", __FUNCTION__, __LINE__);
        manager->Interrupt();
        pstMember->bVideoEosReached = HI_TRUE;
        pstMember->bAudioEosReached = HI_TRUE;
        pstMember->bSubtitleEosReached = HI_TRUE;
    }
    else if (HI_DASH_INVOKE_SET_PLAYREADY_EXTRADATA == u32InvokeId)
    {
        if (NULL == pArg)
            return HI_FAILURE;

#ifdef PLAYREADY_SUPPORT
        HI_FORMAT_PLAYREADY_EXTRADATA_S *pstExternal = (HI_FORMAT_PLAYREADY_EXTRADATA_S *)pArg;
        HI_FORMAT_PLAYREADY_EXTRADATA_S *pstLocal = &pstMember->PRMember.stPlayReadyExtraData;

        dash_log(DASH_LOG_ERROR, "HI_DASH_INVOKE_SET_PLAYREADY_EXTRADATA!\n");

        if (pstExternal->bPlayReadyLicense)
        {
            dash_log(DASH_LOG_INFO, "set playready license!\n");
            pstLocal->bPlayReadyLicense = HI_TRUE;
        }

        if (pstExternal->stCustomData.pu8Data)
        {
            dash_log(DASH_LOG_INFO, "set playready customdata %u!\n", pstExternal->stCustomData.u32Length);
            pstLocal->stCustomData.u32Length = pstExternal->stCustomData.u32Length;
            pstLocal->stCustomData.pu8Data = (HI_U8*)av_mallocz(pstLocal->stCustomData.u32Length);
            memcpy(pstLocal->stCustomData.pu8Data, pstExternal->stCustomData.pu8Data, pstLocal->stCustomData.u32Length);
        }

        if (pstExternal->stURL.pu8Data)
        {
            dash_log(DASH_LOG_INFO, "set playready laurl %u!\n", pstExternal->stURL.u32Length);
            pstLocal->stURL.u32Length = pstExternal->stURL.u32Length;
            pstLocal->stURL.pu8Data = (HI_U8*)av_mallocz(pstLocal->stURL.u32Length);
            memcpy(pstLocal->stURL.pu8Data, pstExternal->stURL.pu8Data, pstLocal->stURL.u32Length);
        }

        return HI_SUCCESS;
#else
        return HI_FAILURE;
#endif
    }
    else if (HI_FORMAT_INVOKE_SET_HEADERS== u32InvokeId)
    {
        if (NULL == pArg)
        {
            return HI_FAILURE;
        }

        if (pstMember->pHttpHeaders != NULL)
        {
            av_free(pstMember->pHttpHeaders);
            pstMember->pHttpHeaders = NULL;
        }

        pstMember->pHttpHeaders = av_strdup((HI_CHAR *)pArg);
        if (NULL == pstMember->pHttpHeaders)
        {
             dash_log(DASH_LOG_ERROR, "[%s,%d] error, httpheaders malloc failed!\n", __FUNCTION__, __LINE__);
        }
        else
        {
             dash_log(DASH_LOG_INFO, "[%s,%d] set httpheaders to \n%s!\n", __FUNCTION__, __LINE__, pstMember->pHttpHeaders);
        }
    }

    return s32Ret;
}

HI_FORMAT_S g_stFormat_entry = {
    g_stFormat_entry.pszDllName                                             = (const HI_PCHAR)"libdashadp.so",
    g_stFormat_entry.pszFormatName                                          = "",
    g_stFormat_entry.pszProtocolName                                        = "",
    const_cast<HI_FORMAT_LIB_VERSION_S &>(g_stFormat_entry.stLibVersion)    = {2,2,0,0},
    g_stFormat_entry.pszFmtDesc                                             = (const HI_PCHAR)"ffmpeg demuxer",
    g_stFormat_entry.u32Merit                                               = 0,
    g_stFormat_entry.stDemuxerFun.fmt_find                                  = NULL,
    g_stFormat_entry.stDemuxerFun.fmt_open                                  = HI_SVR_DASH_Open,
    g_stFormat_entry.stDemuxerFun.fmt_find_stream                           = HI_SVR_DASH_FindStream,
    g_stFormat_entry.stDemuxerFun.fmt_getinfo                               = NULL,
    g_stFormat_entry.stDemuxerFun.fmt_read                                  = NULL,
    g_stFormat_entry.stDemuxerFun.fmt_free                                  = NULL,
    g_stFormat_entry.stDemuxerFun.fmt_invoke                                = HI_SVR_DASH_Invoke,
    g_stFormat_entry.stDemuxerFun.fmt_seek_pts                              = HI_SVR_DASH_SeekPts,
    g_stFormat_entry.stDemuxerFun.fmt_seek_pos                              = NULL,
    g_stFormat_entry.stDemuxerFun.fmt_close                                 = HI_SVR_DASH_Close,

    g_stFormat_entry.stProtocolFun.url_find      = NULL,
    g_stFormat_entry.stProtocolFun.url_open      = NULL,
    g_stFormat_entry.stProtocolFun.url_read      = NULL,
    g_stFormat_entry.stProtocolFun.url_seek      = NULL,
    g_stFormat_entry.stProtocolFun.url_close     = NULL,
    g_stFormat_entry.stProtocolFun.url_read_seek = NULL,
    g_stFormat_entry.stProtocolFun.url_invoke    = NULL,
};

#ifdef __cplusplus
}
#endif
