
#define LOG_TAG "SVR_EXTRATOR_ADP"
#define ANDROID_VER(major, minor)   ((major)*100 + (minor)*10)

#include <utils/Log.h>
#include <utils/String8.h>
#include <string.h>

#include <media/stagefright/foundation/AMessage.h>
#include <media/stagefright/DataSource.h>
#include <media/stagefright/FileSource.h>
#include <media/stagefright/MediaExtractor.h>
#include <media/stagefright/MetaData.h>
#include <media/stagefright/MediaDefs.h>
#include <media/stagefright/MediaBuffer.h>
#include <media/stagefright/MediaSource.h>
#include <media/stagefright/foundation/ABitReader.h>
#if (PLATFORM_SDK_VERSION >= 21)
#include <media/IMediaHTTPService.h>
#include <media/IMediaHTTPConnection.h>
#include <media/stagefright/MediaHTTP.h>
#endif

#include "include/NuCachedSource2.h"
#include <include/DRMExtractor.h>
#include <include/WVMExtractor.h>

#include "include/ESDS.h"
#if defined (ANDROID_VERSION)
#include "cutils/properties.h"
#endif

//#include <include/AwesomePlayer.h>

#include "svr_extrator_adp.h"
#include "svr_extrator_intf.h"

#ifdef HISMOOTHSTREAMINGPLAYER_DRM_ENABLE
#include "hi_svr_smoothstreaming.h"
#include <include/SSExtractor.h>
#endif

#define EX_PRINTF    ALOGE

#define FORMAT_CASE(ffmpeg_code_id, hisi_codec_id) \
do { \
    switch ((ffmpeg_code_id)) \
    { \
    case CODEC_ID_WMAVOICE: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_WMAVOICE; \
        break; \
    case CODEC_ID_AAC: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_AAC; \
        break; \
    case CODEC_ID_WMALOSSLESS: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_WMALOSSLESS; \
        break; \
    case CODEC_ID_WMAPRO: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_WMAPRO; \
        break; \
    case CODEC_ID_AMR_WB: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_AMR_WB; \
        break; \
    case CODEC_ID_FLAC: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_FLAC; \
        break; \
    case CODEC_ID_ATRAC3: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_ATRAC3; \
        break; \
    case CODEC_ID_COOK: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_COOK; \
        break; \
    case CODEC_ID_SIPR: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_SIPR; \
        break; \
    case CODEC_ID_APE: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_APE; \
        break; \
    case CODEC_ID_VORBIS: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_VORBIS; \
        break; \
    case CODEC_ID_GSM: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_GSM; \
        break; \
    case CODEC_ID_GSM_MS: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_GSM_MS; \
        break; \
    case CODEC_ID_TTA: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_TTA; \
        break; \
    case CODEC_ID_WAVPACK: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_WAVPACK; \
        break; \
    case CODEC_ID_ADPCM_IMA_QT: \
    case CODEC_ID_ADPCM_IMA_WAV: \
    case CODEC_ID_ADPCM_IMA_DK3: \
    case CODEC_ID_ADPCM_IMA_DK4: \
    case CODEC_ID_ADPCM_IMA_WS: \
    case CODEC_ID_ADPCM_IMA_SMJPEG: \
    case CODEC_ID_ADPCM_MS: \
    case CODEC_ID_ADPCM_4XM: \
    case CODEC_ID_ADPCM_XA: \
    case CODEC_ID_ADPCM_ADX: \
    case CODEC_ID_ADPCM_EA: \
    case CODEC_ID_ADPCM_G726: \
    case CODEC_ID_ADPCM_CT: \
    case CODEC_ID_ADPCM_SWF: \
    case CODEC_ID_ADPCM_YAMAHA: \
    case CODEC_ID_ADPCM_SBPRO_4: \
    case CODEC_ID_ADPCM_SBPRO_3: \
    case CODEC_ID_ADPCM_SBPRO_2: \
    case CODEC_ID_ADPCM_THP: \
    case CODEC_ID_ADPCM_IMA_AMV: \
    case CODEC_ID_ADPCM_EA_R1: \
    case CODEC_ID_ADPCM_EA_R3: \
    case CODEC_ID_ADPCM_EA_R2: \
    case CODEC_ID_ADPCM_IMA_EA_SEAD: \
    case CODEC_ID_ADPCM_IMA_EA_EACS: \
    case CODEC_ID_ADPCM_EA_XAS: \
    case CODEC_ID_ADPCM_EA_MAXIS_XA: \
    case CODEC_ID_ADPCM_IMA_ISS: \
        (hisi_codec_id) = HI_FORMAT_AUDIO_ADPCM; \
        break; \
    default: \
        break; \
    } \
}while (0)


#define EXTRATOR_REALLOC_1MORE_PROGRAM(stFileInfo) \
    do{ \
            HI_U32 u32AllocSize = 0; \
            HI_U32 u32OldSize = 0; \
            HI_U32 index = 0; \
            HI_FORMAT_PROGRAM_INFO_S *pastProgramInfo; \
            s32AddResult = HI_FAILURE; \
            u32OldSize   =  stFileInfo.u32ProgramNum * sizeof(HI_FORMAT_PROGRAM_INFO_S); \
            u32AllocSize =  u32OldSize + sizeof(HI_FORMAT_PROGRAM_INFO_S); \
            pastProgramInfo = (HI_FORMAT_PROGRAM_INFO_S*)SVR_EXTRACTOR_Realloc(stFileInfo.pastProgramInfo, u32OldSize, u32AllocSize); \
            if (pastProgramInfo != NULL) \
            { \
                index = stFileInfo.u32ProgramNum; \
                memset(&pastProgramInfo[index], 0 ,sizeof(HI_FORMAT_PROGRAM_INFO_S)); \
                stFileInfo.u32ProgramNum += 1; \
                stFileInfo.pastProgramInfo = pastProgramInfo; \
                s32AddResult = HI_SUCCESS; \
            } \
            else \
            { \
                ALOGE("ffmpeg Alloc program error");\
            } \
        }while(0)

/* CNcomment:需要自己增加stProgramInfo.u32StreamNum */
#define EXTRATOR_REALLOC_NMORE_STREAM(stProgramInfo, TYPE, Type, n) \
    do{ \
        HI_FORMAT_##TYPE##_INFO_S *pstStream = NULL; \
        HI_U32 u32AllocSize = 0; \
        HI_U32 u32OldSize = 0; \
        HI_U32 index = 0; \
        s32AddResult = HI_FAILURE;\
        u32OldSize   = stProgramInfo.u32##Type##StreamNum * sizeof(*pstStream); \
        u32AllocSize = (stProgramInfo.u32##Type##StreamNum + n) * sizeof(*pstStream); \
        pstStream =  (HI_FORMAT_##TYPE##_INFO_S *)SVR_EXTRACTOR_Realloc(stProgramInfo.past##Type##Stream, u32OldSize, u32AllocSize); \
        if (pstStream != NULL) \
        { \
            index = stProgramInfo.u32##Type##StreamNum; \
            memset(&pstStream[index], 0 ,sizeof(HI_FORMAT_##TYPE##_INFO_S) * n); \
            stProgramInfo.past##Type##Stream = pstStream; \
            stProgramInfo.past##Type##Stream[stProgramInfo.u32##Type##StreamNum].s32StreamIndex = HI_FORMAT_INVALID_STREAM_ID; \
            s32AddResult = HI_SUCCESS;\
        } \
        else \
        { \
            ALOGE("ffmpeg Alloc stream error");\
        } \
    }while(0)

#define EXTRATOR_FREE_ALL_PROGRAMS(stFileInfo) \
    do{ \
        uint32_t i = 0; \
        if (stFileInfo.pastProgramInfo != NULL) \
        { \
            for (i = 0; i < stFileInfo.u32ProgramNum; i++)\
            { \
                free(stFileInfo.pastProgramInfo[i].pastVidStream); \
                free(stFileInfo.pastProgramInfo[i].pastAudStream); \
                free(stFileInfo.pastProgramInfo[i].pastSubStream); \
            } \
            free(stFileInfo.pastProgramInfo); \
            stFileInfo.pastProgramInfo = NULL; \
            stFileInfo.u32ProgramNum = 0; \
        } \
    }while(0)

#define EXTRATOR_FREE_LAST_PROGRAM(stFileInfo) \
    do{ \
        HI_U32 i = 0; \
        HI_FORMAT_PROGRAM_INFO_S *pastProgramInfo; \
        HI_U32 u32AllocSize = 0; \
        HI_U32 u32OldSize = 0; \
        if (stFileInfo.pastProgramInfo != NULL) \
        { \
            i = stFileInfo.u32ProgramNum - 1; \
            if (i == 0) \
            { \
                free(stFileInfo.pastProgramInfo); \
                stFileInfo.pastProgramInfo = NULL; \
            } \
            else \
            { \
                u32AllocSize =  (stFileInfo.u32ProgramNum - 1) * sizeof(HI_FORMAT_PROGRAM_INFO_S); \
                u32OldSize   =  u32AllocSize + sizeof(HI_FORMAT_PROGRAM_INFO_S); \
                pastProgramInfo = (HI_FORMAT_PROGRAM_INFO_S *)SVR_EXTRACTOR_Realloc(stFileInfo.pastProgramInfo, u32OldSize, u32AllocSize); \
                if (pastProgramInfo != NULL) \
                { \
                    stFileInfo.pastProgramInfo = pastProgramInfo; \
                } \
                else \
                { \
                    ALOGE("Fatal error, relloc less size failed?\n"); \
                } \
            } \
            stFileInfo.u32ProgramNum --; \
        } \
    }while(0)

#define MAX_READ_TIMES   (10)
#define SEPARATE_SYMBOL_OFFSET "::offset="
#define SEPARATE_SYMBOL_LENGTH "::length="
#define FMT_MAX_URL_LEN  (1024)
#define LICENSE_DATA_MAX_LEN (2048)

#define INT_MAX  (0x7fffffff)
#define DEMUX_BUFFER_SIZE_LIMIT           (2*1024*1024)

#define FILEINFO_UPDATE_DOING               (1)
#define FILEINFO_UPDATE_DONE                (2)
#define FILEINFO_UPDATE_NONE                (0)
#define FILEINFO_UPDATE_WAIT_MAX            (50) //unit:ms

#ifndef min
#define min(a,b) ( a < b ? a : b)
#endif

typedef struct tagADTSHeader
{
    /* fixed */
    uint32_t  sync;                           /* syncword */
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

HI_VOID *SVR_EXTRACTOR_Realloc(HI_VOID *ptr, HI_U32 oldsize, HI_U32 newsize)
{
    /* do not use realloc for ICSL */
    HI_VOID *ptrNew = malloc(newsize);
    if (ptrNew == NULL)
    {
        return NULL;
    }
    if (ptr != NULL)
    {
        if (oldsize > 0  && newsize > 0)
        {
            memcpy(ptrNew, ptr, (newsize > oldsize?oldsize:newsize));
        }
        free(ptr);
    }

    return ptrNew;
}

static int32_t _getH264SpsPps(uint8_t *pu8ExtraData, uint32_t u32ExtraDataLen,
    uint8_t *pu8InBuff, uint32_t u32InBufLen, uint32_t*pu32OutLen)
{
    uint32_t startcode_len = 0, unit_size = 0;
    uint8_t num_unit = 0, sps_done = 0;
    static const uint8_t nalu_header3[3] = {0, 0, 1};
    static const uint8_t nalu_header4[4] = {0, 0, 0, 1};
    const uint8_t *extradata = NULL;
    const uint8_t *nalu_header = NULL;

    if (NULL == pu8ExtraData  || NULL == pu8InBuff || u32ExtraDataLen < 5)
    {
        return HI_FAILURE;
    }

    startcode_len = (pu8ExtraData[4] & 0x3) + 1;

    /* extra data is sps and pps data, not need parse, copy it to inbuff and return */

    if (((0x00 == pu8ExtraData[0] && 0x00 == pu8ExtraData[1] && 0x00 == pu8ExtraData[2] && 0x01 == pu8ExtraData[3]))
        || (((0x00 == pu8ExtraData[0] && 0x00 == pu8ExtraData[1] && 0x01 == pu8ExtraData[2])
            || (0x00 == pu8ExtraData[0] && 0x00 == pu8ExtraData[1] && 0x00 == pu8ExtraData[2] && 0x01 == pu8ExtraData[3]))))
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

static int32_t _getH264StartCodeLen(uint8_t *pu8ExtraData,
    uint32_t u32ExtraDataLen, uint32_t *pu32StartCodeLen)
{
    if (NULL == pu8ExtraData || u32ExtraDataLen < 5 || NULL == pu32StartCodeLen)
    {
        return HI_FAILURE;
    }

    *pu32StartCodeLen = (pu8ExtraData[4] & 0x3) + 1;

    if (*pu32StartCodeLen < 2)
    {
        //FORMAT_PRINT("start code len erro, start code len = %d \n", *pu32StartCodeLen);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static int32_t _getBe321(uint8_t *pu8Data, uint32_t *value, uint32_t u32StartCodeLen)
{
    uint32_t val = 0;

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

static int32_t _parseNalInplace(uint8_t *pu8Data, uint32_t u32InDataLen, uint32_t u32StartCodeLen,
    uint8_t *pu8InBuff, uint32_t u32InBufLen, uint32_t *pu32OutDataLen)
{
    int32_t nal_num = 0;
    int32_t ReadLen = 0;
    uint8_t* pos = pu8Data;
    uint8_t* buf = pu8InBuff;

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

    uint32_t u32RealOutLen = 0;

    while (u32InDataLen > u32StartCodeLen && pos < (pu8Data + u32InDataLen - u32StartCodeLen))
    {
        _getBe321(pos,(uint32_t*)&ReadLen, u32StartCodeLen);

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

static void _getADTSHeader(int32_t sampleRateidx,             /*!< aacPlus sampling frequency (incl. SBR) */
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

static HI_U32 getCurrentTime()
{
    struct timeval tv;

    if (0 == gettimeofday(&tv, NULL))
    {
        return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    }

    return -1;
}

namespace android {

SVRExtratorAdp::SVRExtratorAdp()
{
    EX_PRINTF("[%s:%d] Enter StagefrightMetadataRetriever()\n", __FUNCTION__, __LINE__);

    mParseFileInfo = false;
    mVideoBuffer   = NULL;
    mAudioBuffer   = NULL;
    mDecryptHandle = NULL;
    mVideoTrackIndex = -1;
    mAudioTrackIndex = -1;
    mLastVideoFramePts = -1;
    mLastAudioFramePts = -1;
    mVideoReadTimes  = 0;
    mAudioReadTimes  = 0;
    mbVideoEndOfStream   = true;
    mbAudioEndOfStream   = true;
    misWidevineStreaming = false;
    mSeeking = false;
    s64BufferMaxSize = 0;
    aszHeaders = NULL;
    mDrmManagerClient = NULL;

    memset(&mFileInfo, 0, sizeof(mFileInfo));
    memset(&stBufConfig, 0, sizeof(stBufConfig));
    options.clearSeekTo();

    DataSource::RegisterDefaultSniffers();
}

SVRExtratorAdp::~SVRExtratorAdp()
{
    EX_PRINTF("[%s:%d] Enter ~SVRExtratorAdp()\n", __FUNCTION__, __LINE__);

    #if 0
    if (NULL != mVideoBuffer)
        mVideoBuffer->release();

    if (NULL != mAudioBuffer)
        mAudioBuffer->release();
    #endif

    reset();
}

void SVRExtratorAdp::checkDrmStatus(const sp<DataSource>& dataSource)
{
    dataSource->getDrmInfo(mDecryptHandle, &mDrmManagerClient);
    if (mDecryptHandle != NULL)
    {
        //CHECK(mDrmManagerClient);
        if (RightsStatus::RIGHTS_VALID != mDecryptHandle->status)
        {
            // TODO: notify listener
            //notifyListener_l(MEDIA_ERROR, MEDIA_ERROR_UNKNOWN, ERROR_DRM_NO_LICENSE);
        }
    }
}

#ifdef HISMOOTHSTREAMINGPLAYER_DRM_ENABLE
status_t SVRExtratorAdp::setInitBps()
{
    HI_CHAR *aszKey = NULL;
    HI_CHAR szTemp[64] = {};
    HI_PTR hissplayer = NULL;
    HI_U32 u32InitialBps, u32Len;

    sp<MetaData> FileMeta = mExtractor->getMetaData();

    if (NULL != aszHeaders)
    {
        aszKey = strstr(aszHeaders, "mss_bitrate: ");
        if (NULL != aszKey && (FileMeta->findPointer(kKeyHiSShandle, &hissplayer)) && NULL != hissplayer)
        {
            aszKey = (HI_CHAR *)((uint32_t)aszKey + strlen("mss_bitrate: "));
            u32Len = min(((uint32_t)(strstr(aszKey, "\r\n")) - (uint32_t)aszKey), 64);
            memcpy(szTemp, aszKey, u32Len);
            EX_PRINTF("[%s:%d] mss_bitrate:%s\n", __FUNCTION__, __LINE__, szTemp);

            if (atoi(szTemp) < 0)
            {
                EX_PRINTF("[%s:%d] set initial bps failed, invalid mss_bitrate:%d kbps", __FUNCTION__, __LINE__, atoi(szTemp));
                return HI_FAILURE;
            }

            u32InitialBps = atoi(szTemp) * 1000;
            if (u32InitialBps > INT_MAX)
            {
                EX_PRINTF("[%s:%d] set initial bps failed, invalid mss_bitrate:%d bps", __FUNCTION__, __LINE__, u32InitialBps);
                return HI_FAILURE;
            }

            EX_PRINTF("[%s:%d] begin to set initial bitrate:%d bps\n", __FUNCTION__, __LINE__, u32InitialBps);
            uint32_t s32Ret = HI_SVR_SMOOTHSTREAMING_SetParam(hissplayer,
                                                            HI_SVR_SMOOTHSTREAMING_ATTR_INITIAL_BPS,
                                                            &u32InitialBps);
            if (HI_SUCCESS != s32Ret)
            {
                EX_PRINTF("[%s:%d] set initial bps failed, HI_SVR_SMOOTHSTREAMING_SetParam return:0x%x", __FUNCTION__, __LINE__, s32Ret);
                return HI_FAILURE;
            }
            EX_PRINTF("[%s:%d] set initial bps success\n", __FUNCTION__, __LINE__);
        }
    }
    return HI_SUCCESS;
}

status_t SVRExtratorAdp::acquireDrmInfo()
{
    String8 mimeType;
    float confidence;
    bool success;

    //sp<MetaData> FileMeta = mExtractor->getMetaData();

    success = SniffSS(mSource, &mimeType, &confidence, NULL);
    if ((mExtractor->getDrmFlag()) && success && (!strcasecmp(mimeType.string(), MEDIA_MIMETYPE_CONTAINER_SS)))
    {
        DrmManagerClient *drmClient_header;
        DrmInfoRequest *request_header;
        DrmInfo *response;
        DrmBuffer ipmpBox;
        int i = 0;

        ipmpBox.data = mExtractor->getDrmTrackInfo(NULL, &(ipmpBox.length));
        if ((ipmpBox.length) && (ipmpBox.data))
        {
            EX_PRINTF("[%s:%d] acquire drm header start.\n", __FUNCTION__, __LINE__);

            /* save drm header to local and move the black space */
            HI_CHAR *drm_header = (HI_CHAR *)malloc(ipmpBox.length);
            if (!drm_header)
            {
                EX_PRINTF("[%s:%d] memory alloc failed\n", __FUNCTION__, __LINE__);
                return ERROR_UNSUPPORTED;
            }
            memcpy(drm_header, ipmpBox.data, ipmpBox.length);
            for (i = 0; i < ipmpBox.length - 2; i++)
            {
                if (drm_header[i] == '\0')
                {
                    memcpy((HI_CHAR *)&drm_header[i], (HI_CHAR *)&drm_header[i+1], (ipmpBox.length - i - 1));
                    ipmpBox.length--;
                    i--;
                }
            }
            HI_CHAR *header_str = strstr(drm_header, "<");
            if (!header_str)
            {
                free(drm_header);
                EX_PRINTF("[%s:%d] drm header is unvalid\n", __FUNCTION__, __LINE__);
                return ERROR_UNSUPPORTED;
            }

            drmClient_header = new DrmManagerClient();
            request_header = new DrmInfoRequest(DrmInfoRequest::TYPE_RIGHTS_ACQUISITION_INFO, String8("video/ismv"));
            request_header->put(String8("Action"), String8("AcquireLicenseFull"));

            EX_PRINTF("[%s:%d] Header:%s\n", __FUNCTION__, __LINE__, (char *)(header_str));
            request_header->put(String8("Header"), String8(header_str));

            if (aszHeaders)
            {
                HI_CHAR *aszKey = NULL;
                HI_CHAR *szTemp = (HI_CHAR *)malloc(LICENSE_DATA_MAX_LEN);
                if (!szTemp)
                {
                    EX_PRINTF("[%s:%d] memory alloc failed\n", __FUNCTION__, __LINE__);
                    return ERROR_UNSUPPORTED;
                }

                aszKey = strstr(aszHeaders, "custom_data: ");
                if (aszKey)
                {
                    aszKey = (HI_CHAR *)((uint32_t)aszKey + strlen("custom_data: "));
                    memset(szTemp, 0, LICENSE_DATA_MAX_LEN);
                    memcpy(szTemp, aszKey, ((uint32_t)(strstr(aszKey, "\r\n")) - (uint32_t)aszKey));
                    EX_PRINTF("[%s:%d] CustomData:%s\n", __FUNCTION__, __LINE__, szTemp);
                    request_header->put(String8("CustomData"), String8(szTemp));
                }

                aszKey = strstr(aszHeaders, "la_url: ");
                if (aszKey)
                {
                    aszKey = (HI_CHAR *)((uint32_t)aszKey + strlen("la_url: "));
                    memset(szTemp, 0, LICENSE_DATA_MAX_LEN);
                    memcpy(szTemp, aszKey, ((uint32_t)(strstr(aszKey, "\r\n")) - (uint32_t)aszKey));
                    EX_PRINTF("[%s:%d] LA_URL:%s\n", __FUNCTION__, __LINE__, szTemp);
                    request_header->put(String8("LA_URL"), String8(szTemp));
                }
            }

            response = drmClient_header->acquireDrmInfo(request_header);
            free(drm_header);
            delete drmClient_header;
            delete request_header;

            if (!response || strcasecmp(response->get(String8("Status")).string(), "ok"))
            {

                EX_PRINTF("[%s:%d] acquireDrmInfo failed\n", __FUNCTION__, __LINE__);
                return ERROR_UNSUPPORTED;
            }
            EX_PRINTF("[%s:%d] acquire drm header success.\n", __FUNCTION__, __LINE__);
        }
    }
    return HI_SUCCESS;
}

void SVRExtratorAdp::setInitBufConfig()
{
    HI_PTR handle = NULL;
    sp<MetaData> FileMeta = mExtractor->getMetaData();
    if ((FileMeta->findPointer(kKeyStreamBufInfo, &handle)) && handle)
    {
        DEMUX_BUFFER_MGR_S *pstDemuxBufInfo = (DEMUX_BUFFER_MGR_S *)handle;
        if (HI_FORMAT_BUFFER_CONFIG_SIZE == stBufConfig.eType)
        {
            pstDemuxBufInfo->stConfigSize.eType          = HI_FORMAT_BUFFER_CONFIG_SIZE;
            pstDemuxBufInfo->stConfigSize.s64EventEnough = stBufConfig.s64EventEnough;
            pstDemuxBufInfo->stConfigSize.s64EventStart  = stBufConfig.s64EventStart;
            pstDemuxBufInfo->stConfigSize.s64TimeOut     = stBufConfig.s64TimeOut;
            pstDemuxBufInfo->stConfigSize.s64Total       = stBufConfig.s64Total;
            pstDemuxBufInfo->eConfigUser = HI_FORMAT_BUFFER_CONFIG_SIZE;
            EX_PRINTF("HI_FORMAT_INVOKE_SET_BUFFER_CONFIG Args is HI_FORMAT_BUFFER_CONFIG_SIZE\n");
        }
        else if(HI_FORMAT_BUFFER_CONFIG_TIME == stBufConfig.eType)
        {
            pstDemuxBufInfo->stConfigTime.eType          = HI_FORMAT_BUFFER_CONFIG_TIME;
            pstDemuxBufInfo->stConfigTime.s64EventEnough = stBufConfig.s64EventEnough;
            pstDemuxBufInfo->stConfigTime.s64EventStart  = stBufConfig.s64EventStart;
            pstDemuxBufInfo->stConfigTime.s64TimeOut     = stBufConfig.s64TimeOut;
            pstDemuxBufInfo->stConfigTime.s64Total       = stBufConfig.s64Total;
            pstDemuxBufInfo->eConfigUser = HI_FORMAT_BUFFER_CONFIG_TIME;
            EX_PRINTF("HI_FORMAT_INVOKE_SET_BUFFER_CONFIG Args is HI_FORMAT_BUFFER_CONFIG_TIME\n");
        }

        if (s64BufferMaxSize)
        {
            pstDemuxBufInfo->s64BufferMaxSize = s64BufferMaxSize;
        }
    }
}
#endif

status_t SVRExtratorAdp::createDataSource(const char *uri,
    const KeyedVector<String8, String8> *headers, void *parg)
{
    String8 newURI(uri);
    String8 mimeType("");
    EX_PRINTF("[%s:%d] Enter SVRExtratorAdp::createDataSource\n", __FUNCTION__, __LINE__);
    misWidevineStreaming = false;

    if (!strncasecmp("widevine://", uri, 11) || strstr(uri, ".wvm"))
    {
        misWidevineStreaming = true;

        if (!strncasecmp("widevine://", uri, 11)) {
            newURI = String8("http://");
            newURI.append(uri + 11);
            EX_PRINTF("[%s:%d] newURI =  %s\n", __FUNCTION__, __LINE__, newURI.string());
        }
    }

#if (PLATFORM_SDK_VERSION >= 21)
    sp<IMediaHTTPService>httpService = static_cast<IMediaHTTPService *>(parg);
#endif
    //local file url
    if (strncasecmp("http", uri, 4)
            && strncasecmp("widevine://", uri, 11)
            && (strstr(uri, ".wvm") || strstr(uri, ".pyv") || strstr(uri, ".pya"))) {
        const char* localUri = strstr(uri, "::offset=");
        int fd = -1;
        uint64_t offset = -1;
        uint64_t length = -1;
        if (NULL != localUri && 3 == sscanf(localUri, "::offset=%lld::length=%lld::fd=%d", &offset, &length, &fd))
        {
            mSource = new FileSource(dup(fd), offset, length);
        } else {
            localUri = strdup(uri);
            char* tmp = localUri ? strstr(localUri, "::offset=") : NULL;
            if (tmp) {
                *tmp = 0;
            }
            mSource = new FileSource(localUri);
            ALOGE("open local wvm file:%s", localUri);
            free((void*)localUri);
        }
        if (mSource == NULL) {
            ALOGE("create wvm source failed");
            return ERROR_UNSUPPORTED;
        }
        if (misWidevineStreaming)
        {
            float confidence;
            bool success;
            success = SniffWVM(mSource, &mimeType, &confidence, NULL);
            if (!success || strcasecmp(mimeType.string(), MEDIA_MIMETYPE_CONTAINER_WVM))
            {
                mSource.clear();
                EX_PRINTF("[%s:%d] Widevine datasource create fail \n", __FUNCTION__, __LINE__);
                return ERROR_UNSUPPORTED;
            }

            mMimeType = mimeType;
            mWVMExtractor = new WVMExtractor(mSource);
            mWVMExtractor->setCryptoPluginMode(true);
            mExtractor = mWVMExtractor;

            if (mExtractor->getDrmFlag())
            {
                checkDrmStatus(mSource);
            }
        }
        else
        {
            const char *mime = NULL;
            sp<AMessage> meta;
            if (mime == NULL) {
                float confidence;
                if (!mSource->sniff(&mimeType, &confidence, &meta)) {
                    EX_PRINTF("FAILED to autodetect media content.");

                    return NULL;
                }

                mime = mimeType.string();
            }

            // DRM MIME type syntax is "drm+type+original" where
            // type is "es_based" or "container_based" and
            // original is the content's cleartext MIME type
            if (!strncmp(mime, "drm+", 4)) {
                const char *originalMime = strchr(mime+4, '+');
                if (originalMime == NULL) {
                    // second + not found
                    return NULL;
                }
                ++originalMime;
                if (!strncmp(mime, "drm+es_based+", 13)) {
                    // DRMExtractor sets container metadata kKeyIsDRM to 1
                    mime = originalMime;
                } else if (!strncmp(mime, "drm+container_based+", 20)) {
                    mime = originalMime;
                } else {
                    return NULL;
                }
            }

            mExtractor = MediaExtractor::Create(mSource, mime);
            if (mExtractor == NULL)
            {
                EX_PRINTF("[%s:%d] Unable to instantiate an extractor for '%s'.\n", __FUNCTION__, __LINE__, uri);
                mSource.clear();
                return ERROR_UNSUPPORTED;
            }
            else
            {
                mMimeType = String8(mime);
                EX_PRINTF("[%s:%d] Create extractor success \n", __FUNCTION__, __LINE__);
            }
        }
    }
    else if (false == misWidevineStreaming)
    {
    #if (PLATFORM_SDK_VERSION >= 21)
        mSource = DataSource::CreateFromURI(httpService, uri, headers);
    #else
        mSource = DataSource::CreateFromURI(uri, headers);
    #endif

        if (mSource == NULL)
        {
            EX_PRINTF("[%s:%d] Unable to create data source for '%s'.\n", __FUNCTION__, __LINE__, uri);
            return ERROR_UNSUPPORTED;
        }
        else
        {
            EX_PRINTF("[%s:%d] Create data source success \n", __FUNCTION__, __LINE__);
        }

        String8 tmp;
        const char *mime = NULL;
        sp<AMessage> meta;
        if (mime == NULL) {
            float confidence;
            if (!mSource->sniff(&tmp, &confidence, &meta)) {
                EX_PRINTF("FAILED to autodetect media content.");

                return NULL;
            }

            mime = tmp.string();
            EX_PRINTF("Autodetected media content as '%s' with confidence %.2f",
                 mime, confidence);
        }

        // DRM MIME type syntax is "drm+type+original" where
        // type is "es_based" or "container_based" and
        // original is the content's cleartext MIME type
        if (!strncmp(mime, "drm+", 4)) {
            const char *originalMime = strchr(mime+4, '+');
            if (originalMime == NULL) {
                // second + not found
                return NULL;
            }
            ++originalMime;
            if (!strncmp(mime, "drm+es_based+", 13)) {
                // DRMExtractor sets container metadata kKeyIsDRM to 1
                mime = originalMime;
            } else if (!strncmp(mime, "drm+container_based+", 20)) {
                mime = originalMime;
            } else {
                return NULL;
            }
        }

        //specify the original mimetype to avoid create DRMExtractor
        mExtractor = MediaExtractor::Create(mSource, mime);
        if (mExtractor == NULL)
        {
            EX_PRINTF("[%s:%d] Unable to instantiate an extractor for '%s'.\n", __FUNCTION__, __LINE__, uri);
            mSource.clear();
            return ERROR_UNSUPPORTED;
        }
        else if (!strcasecmp(mime, MEDIA_MIMETYPE_CONTAINER_SS))
        {
            mMimeType = String8(MEDIA_MIMETYPE_CONTAINER_SS);
            EX_PRINTF("[%s:%d] Create extractor success mime:%s\n", __FUNCTION__, __LINE__, mime);
        }

        sp<MetaData> FileMeta = mExtractor->getMetaData();

#ifdef HISMOOTHSTREAMINGPLAYER_DRM_ENABLE
#if defined (ANDROID_VERSION)
        {
            bool bAcqLicense_disable = 0;
            HI_CHAR value[PROPERTY_VALUE_MAX] = {0};
            if (property_get("media.ss.LicenseAcq.disabled", value, NULL) > 0)
            {
                if (!strncmp(value, "true", 4))
                {
                    bAcqLicense_disable = 1;
                    EX_PRINTF("[%s:%d] media.ss.LicenseAcq.disabled prop is set\n", __FUNCTION__, __LINE__);
                }
            }
            if (!bAcqLicense_disable)
            {
                EX_PRINTF("[%s:%d] media.ss.LicenseAcq.disabled prop is not set\n", __FUNCTION__, __LINE__);
                if (acquireDrmInfo())
                {
                    return ERROR_UNSUPPORTED;
                }
            }
        }
#endif
        (void)setInitBps();
        setInitBufConfig();
#endif
    }
    else
    {
        EX_PRINTF("[%s:%d] Create extractor \n", __FUNCTION__, __LINE__);

    #if (PLATFORM_SDK_VERSION >= 21)
        /* for android 5.0 modification*/
        if (httpService == NULL)
        {
             EX_PRINTF("Invalid http service!");
             return ERROR_UNSUPPORTED;
        }
        sp<IMediaHTTPConnection> conn = httpService->makeHTTPConnection();
        mConnectingDataSource = new MediaHTTP(conn);
    #else
        mConnectingDataSource = HTTPBase::Create(0);
    #endif
        #if 0
        if (mUIDValid) {
            mConnectingDataSource->setUID(mUID);
        }
        #endif
        EX_PRINTF("[%s:%d] Create extractor \n", __FUNCTION__, __LINE__);

        String8 cacheConfig;
        bool disconnectAtHighwatermark;
        NuCachedSource2::RemoveCacheSpecificHeaders(
                &mUriHeaders, &cacheConfig, &disconnectAtHighwatermark);

        //mLock.unlock();
        status_t err = mConnectingDataSource->connect(newURI.string(), &mUriHeaders);
        //mLock.lock();
        EX_PRINTF("[%s:%d] Create extractor \n", __FUNCTION__, __LINE__);

        if (err != OK)
        {
            mConnectingDataSource.clear();
            EX_PRINTF("[%s:%d] mConnectingDataSource->connect() returned %d", __FUNCTION__, __LINE__, err);
            return err;
        }

        EX_PRINTF("[%s:%d] Open %s ", __FUNCTION__, __LINE__, newURI.string());
        mSource = mConnectingDataSource;//DataSource::CreateFromURI(newURI.string(), headers);
        mConnectingDataSource.clear();
        EX_PRINTF("[%s:%d] Create extractor \n", __FUNCTION__, __LINE__);

        if (mSource == NULL)
        {
            EX_PRINTF("[%s:%d] Unable to create data source for '%s'.", __FUNCTION__, __LINE__, newURI.string());
            return ERROR_UNSUPPORTED;
        }
        else
        {
            EX_PRINTF("[%s:%d] Create data source success \n", __FUNCTION__, __LINE__);
        }

        /* widevine stream */
        float confidence;
        bool success;

        // SniffWVM is potentially blocking since it may require network access.
        // Do not call it with mLock held.
        //mLock.unlock();
        success = SniffWVM(mSource, &mimeType, &confidence, NULL);
        mMimeType = mimeType;
        //mLock.lock();
        EX_PRINTF("[%s:%d] Create extractor \n", __FUNCTION__, __LINE__);

        if (!success || strcasecmp(mimeType.string(), MEDIA_MIMETYPE_CONTAINER_WVM))
        {
            mSource.clear();
            EX_PRINTF("[%s:%d] Widevine datasource create fail \n", __FUNCTION__, __LINE__);
            return ERROR_UNSUPPORTED;
        }

        mWVMExtractor = new WVMExtractor(mSource);
        mWVMExtractor->setCryptoPluginMode(true);
        mWVMExtractor->setAdaptiveStreamingMode(true);
        mExtractor = mWVMExtractor;

        if (mExtractor->getDrmFlag())
        {
            EX_PRINTF("[%s:%d] Create extractor \n", __FUNCTION__, __LINE__);
            checkDrmStatus(mSource);
        }
        mFileInfo.eSourceType = HI_FORMAT_SOURCE_NET_VOD;//default set to VOD type
        EX_PRINTF("[%s:%d] Widevine extractor create success \n", __FUNCTION__, __LINE__);
    }

    mParseFileInfo = false;

    return OK;
}

status_t SVRExtratorAdp::reset()
{
    stop();

    if (NULL != mWVMExtractor.get())
        mWVMExtractor.clear();

    if (NULL != mSource.get())
        mSource.clear();
    if (NULL != mAudioTrack.get())
        mAudioTrack.clear();
    if (NULL != mVideoTrack.get())
        mVideoTrack.clear();
    if (NULL != mExtractor.get())
        mExtractor.clear();

    mParseFileInfo = false;
    EXTRATOR_FREE_ALL_PROGRAMS(mFileInfo);
    mLastVideoFramePts = -1;
    mLastAudioFramePts = -1;

    return OK;
}

status_t SVRExtratorAdp::openFile(HI_FORMAT_FILE_INFO_S **fileinfo)
{
    size_t numTracks = 0;

    uint32_t videoNum = 0, audioNum = 0;
    int32_t videoWidth = 0, videoHeig = 0;
    int32_t value = 0, rotationAngle = 0;

    int32_t s32AddResult = HI_SUCCESS;

    EX_PRINTF("Enter [%s:%d] \n", __FUNCTION__, __LINE__);

    if (NULL == mExtractor.get())
    {
        EX_PRINTF("mExtractor is null \n");
        return UNKNOWN_ERROR;
    }

    mFileInfo.bIsDrmFile = (HI_BOOL)mExtractor->getDrmFlag();

    numTracks = mExtractor->countTracks();

    if (0 == numTracks)
    {
        EX_PRINTF("Track number is zero \n");
        return UNKNOWN_ERROR;
    }

    if (false != mParseFileInfo)
    {
        EX_PRINTF("[%s:%d], file already parse ", __FUNCTION__, __LINE__);
        *fileinfo = &mFileInfo;
        return OK;
    }

    sp<MetaData> FileMeta = mExtractor->getMetaData();
    int32_t bIsLive = -1;
    if ((FileMeta->findInt32(kKeyFileSourceType, &bIsLive))
        && (-1 != bIsLive))
    {
        if (bIsLive)
        {
            mFileInfo.eSourceType = HI_FORMAT_SOURCE_NET_LIVE;
        }
        else
        {
            mFileInfo.eSourceType = HI_FORMAT_SOURCE_NET_VOD;
        }
    }

    EXTRATOR_REALLOC_1MORE_PROGRAM(mFileInfo);

    EX_PRINTF("Enter [%s:%d], track number = %d \n", __FUNCTION__, __LINE__, numTracks);

    for (size_t i = 0; i < numTracks; ++i)
    {
        sp<MetaData> trackMeta = mExtractor->getTrackMetaData(i);

        int64_t durationUs = 0;

        if (trackMeta->findInt64(kKeyDuration, &durationUs))
        {
            if (durationUs > mFileInfo.s64Duration)
                mFileInfo.s64Duration = durationUs / 1000;

            EX_PRINTF("Enter [%s:%d], duration = %lld \n", __FUNCTION__, __LINE__, durationUs);
        }

        const char *mime = NULL;
        int cdcversion = 0;
        uint32_t type;
        const void *data = NULL;
        size_t size;

        if (trackMeta->findCString(kKeyMIMEType, &mime))
        {
            if (!strncasecmp("audio/", mime, 6))
            {
                EXTRATOR_REALLOC_NMORE_STREAM(mFileInfo.pastProgramInfo[0], AUD, Aud, 1);
                audioNum = mFileInfo.pastProgramInfo[0].u32AudStreamNum;

                EX_PRINTF("Audio stream number = %d \n", audioNum);

                if (trackMeta->findInt32(kKeyBitRate, &value))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Bitrate = value;
                    EX_PRINTF("Audio kKeyBitRate = %d \n", value);
                }

                if (trackMeta->findInt32(kKeySampleRate, &value))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32SampleRate = value;
                    EX_PRINTF("Audio kKeySampleRate = %d \n", value);
                }

                if (trackMeta->findInt32(kKeyChannelCount, &value))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u16Channels = value;
                    EX_PRINTF("Audio kKeyChannelCount = %d \n", value);
                }
                if (trackMeta->findInt32(kKeyBlockAlign, &value))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32BlockAlign = value;
                    EX_PRINTF("Audio kKeyBlockAlign = %d \n", value);
                }

                if (trackMeta->findInt32(kKeyTrackID, &value))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].s32StreamIndex = value;
                    EX_PRINTF("Audio kKeyTrackID = %d \n", value);
                }

                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].s64Duration = durationUs / 1000;

                if (NULL == mAudioTrack.get())
                {
                    int data_len = 0;
                    int32_t trackID = 0;
                    (HI_VOID)trackMeta->findInt32(kKeyTrackID, &trackID);
                    HI_CHAR* data = (HI_CHAR*)mExtractor->getDrmTrackInfo(trackID, &data_len);
                    if (data && data_len > 0)
                    {
                        mFileInfo.bIsDrmFile = HI_TRUE;
                    }
                    mAudioTrack = mExtractor->getTrack(i);
                    mAudioTrackIndex = value;
                    EX_PRINTF("Enter [%s:%d], audio track, mime = %s, track index = %d bIsDrmFile = %d \n",
                        __FUNCTION__, __LINE__, mime, mAudioTrackIndex, mFileInfo.bIsDrmFile);

                    // To be fixed. The mime variable is modified abnormally somewhere, get it again.
                    trackMeta->findCString(kKeyMIMEType, &mime);
                }

                if (!strncasecmp(mime, MEDIA_MIMETYPE_AUDIO_AMR_WB, strlen(MEDIA_MIMETYPE_AUDIO_AMR_WB)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_AMR_NB;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_AUDIO_MPEG, strlen(MEDIA_MIMETYPE_AUDIO_MPEG)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_MP3;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_I, strlen(MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_I)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_MP2;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_II, strlen(MEDIA_MIMETYPE_AUDIO_MPEG_LAYER_II)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_MP2;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_AUDIO_AAC, strlen(MEDIA_MIMETYPE_AUDIO_AAC)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_AAC;
                    if (trackMeta->findInt32(kKeyAACProfile, &value))
                        mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Profile = value;

                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_AUDIO_VORBIS, strlen(MEDIA_MIMETYPE_AUDIO_VORBIS)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_VORBIS;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_AUDIO_FLAC, strlen(MEDIA_MIMETYPE_AUDIO_FLAC)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_FLAC;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_AUDIO_AAC_ADTS, strlen(MEDIA_MIMETYPE_AUDIO_AAC_ADTS)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_AAC;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_AUDIO_WMAPRO, strlen(MEDIA_MIMETYPE_AUDIO_WMAPRO)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_WMAPRO;
                }
                else if (!strncasecmp(mime,MEDIA_MIMETYPE_AUDIO_WMA, strlen(MEDIA_MIMETYPE_AUDIO_WMA)))
                {
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_WMAV2;
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Profile = 0x161;
                    if (trackMeta->findInt32(kKeyCodecVersion, &cdcversion))
                    {
                        switch (cdcversion)
                        {
                            case 1:
                            {
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_WMAV1;
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Profile = 0x160;
                                break;
                            }
                            case 2:
                            {
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_WMAV2;
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Profile = 0x161;
                                break;
                            }
                            default:
                                EX_PRINTF("mime: %s error version!!!\n", mime);
                                break;
                        }
                    }
                }
                else if (!strncasecmp(mime,MEDIA_MIMETYPE_AUDIO_FFMPEG, strlen(MEDIA_MIMETYPE_AUDIO_FFMPEG)))
                {
                    if (trackMeta->findInt32(kKeyFFmpegCodecID, &value))
                    {
                        switch (value)
                        {
                            case CODEC_ID_PCM_S16BE:
                            case CODEC_ID_PCM_U16BE:
                            case CODEC_ID_PCM_S32BE:
                            case CODEC_ID_PCM_U32BE:
                            case CODEC_ID_PCM_S24BE:
                            case CODEC_ID_PCM_U24BE:
                            case CODEC_ID_PCM_F32BE:
                            case CODEC_ID_PCM_F64BE:   /* big-endian */
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].bBigEndian = HI_TRUE;
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_PCM;
                                EX_PRINTF("     bBigEndian:   %d \n", \
                                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].bBigEndian);
                                break;

                            case CODEC_ID_PCM_S16LE:
                            case CODEC_ID_PCM_U16LE:
                            case CODEC_ID_PCM_S32LE:
                            case CODEC_ID_PCM_U32LE:
                            case CODEC_ID_PCM_S24LE:
                            case CODEC_ID_PCM_U24LE:
                            case CODEC_ID_PCM_F32LE:
                            case CODEC_ID_PCM_F64LE:
                            case CODEC_ID_PCM_S16LE_PLANAR:
                            case CODEC_ID_PCM_S8:
                            case CODEC_ID_PCM_U8:
                            case CODEC_ID_PCM_MULAW:
                            case CODEC_ID_PCM_ALAW:
                            case CODEC_ID_PCM_S24DAUD:
                            case CODEC_ID_PCM_ZORK:
                            case CODEC_ID_PCM_DVD:
                            case CODEC_ID_PCM_BLURAY:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].bBigEndian = HI_FALSE;
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_PCM;

                                EX_PRINTF("     bBigEndian:   %d \n", \
                                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].bBigEndian);
                                break;

                            case CODEC_ID_MP1:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_MP1;
                                break;

                            case CODEC_ID_MP2:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_MP2;
                                break;

                            case CODEC_ID_MP3:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_MP3;
                                break;

                            case CODEC_ID_AAC:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_AAC;
                                #if 0
                                _SVR_FORMAT_DecAdtsExtradata(enc->extradata, enc->extradata_size, &u32SampleRateIdx, \
                                &u32Profile, &u32Channel);
                                EX_PRINTF("     samplerateidx:     %d \n", u32SampleRateIdx);
                                EX_PRINTF("     samplerate in tab: %d \n", s_au32SampRateTab[u32SampleRateIdx]);
                                EX_PRINTF("     profile:           %d \n", u32Profile);
                                EX_PRINTF("     channels:          %d \n", u32Channel);
                                #endif
                                break;

                            case CODEC_ID_AC3:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_AC3;
                                break;

                            case CODEC_ID_EAC3:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_EAC3;
                                break;

                            case CODEC_ID_DTS:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_DTS;
                                break;

                            case CODEC_ID_TRUEHD:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_TRUEHD;
                                break;

                            case CODEC_ID_DXA:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_DRA;
                                break;

                            case CODEC_ID_AMR_NB:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_AMR_NB;
                                break;

                            case CODEC_ID_AMR_WB:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_AMR_WB;
                                break;

                            case CODEC_ID_COOK:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_COOK;
                                break;

                            case CODEC_ID_WMAVOICE:
                            case CODEC_ID_WMALOSSLESS:
                            case CODEC_ID_WMAPRO:
                            case CODEC_ID_FLAC:
                            case CODEC_ID_ATRAC3:
                            case CODEC_ID_SIPR:
                            case CODEC_ID_APE:
                            case CODEC_ID_VORBIS:
                            case CODEC_ID_GSM:
                            case CODEC_ID_GSM_MS:
                            case CODEC_ID_ADPCM_IMA_QT:
                            case CODEC_ID_ADPCM_IMA_WAV:
                            case CODEC_ID_ADPCM_IMA_DK3:
                            case CODEC_ID_ADPCM_IMA_DK4:
                            case CODEC_ID_ADPCM_IMA_WS:
                            case CODEC_ID_ADPCM_IMA_SMJPEG:
                            case CODEC_ID_ADPCM_MS:
                            case CODEC_ID_ADPCM_4XM:
                            case CODEC_ID_ADPCM_XA:
                            case CODEC_ID_ADPCM_ADX:
                            case CODEC_ID_ADPCM_EA:
                            case CODEC_ID_ADPCM_G726:
                            case CODEC_ID_ADPCM_CT:
                            case CODEC_ID_ADPCM_SWF:
                            case CODEC_ID_ADPCM_YAMAHA:
                            case CODEC_ID_ADPCM_SBPRO_4:
                            case CODEC_ID_ADPCM_SBPRO_3:
                            case CODEC_ID_ADPCM_SBPRO_2:
                            case CODEC_ID_ADPCM_THP:
                            case CODEC_ID_ADPCM_IMA_AMV:
                            case CODEC_ID_ADPCM_EA_R1:
                            case CODEC_ID_ADPCM_EA_R3:
                            case CODEC_ID_ADPCM_EA_R2:
                            case CODEC_ID_ADPCM_IMA_EA_SEAD:
                            case CODEC_ID_ADPCM_IMA_EA_EACS:
                            case CODEC_ID_ADPCM_EA_XAS:
                            case CODEC_ID_ADPCM_EA_MAXIS_XA:
                            case CODEC_ID_ADPCM_IMA_ISS:
                            case CODEC_ID_TTA:
                            case CODEC_ID_WAVPACK:
                                FORMAT_CASE(value, mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format);
                                break;

                            default:
                                mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Format = HI_FORMAT_AUDIO_BUTT;
                                EX_PRINTF("not support audio format, code id = 0x%x \n", value);
                                break;
                        }
                    }
                }
                else
                {
                    EX_PRINTF("[%s:%d] not support audio type %s", __FUNCTION__, __LINE__,mime);
                }

                if (trackMeta->findData(kKeyCodecPriData, &type, &data, &size))
                {
                    EX_PRINTF("[%s:%d][kKeyCodecPriData]type=%d, size=%d  ", __FUNCTION__, __LINE__,type,size);
                    mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32ExtradataSize = size;

                    if (size > 0)
                    {
                        mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].pu8Extradata =
                            (HI_U8*)malloc(sizeof(HI_U8) * size + 16);
                        memset(mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].pu8Extradata, 0, size + 16);
                        memcpy(mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].pu8Extradata, data, size);
                    }
                    HI_U8 *pstdata = mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].pu8Extradata;
                    EX_PRINTF("     profile:      0x%x \n", mFileInfo.pastProgramInfo[0].pastAudStream[audioNum].u32Profile);
                    EX_PRINTF("     CbData:");
                    for (i = 0; i < (HI_U32)size; i++)
                    {
                        EX_PRINTF("%02x ", pstdata[i]);
                    }
                    EX_PRINTF("\n");
                }

                mFileInfo.pastProgramInfo[0].u32AudStreamNum++;
            }
            else if (!strncasecmp("video/", mime, 6))
            {
                if (trackMeta->findInt32(kKeyRotation, &rotationAngle))
                {
                    rotationAngle = 0;
                }

                EXTRATOR_REALLOC_NMORE_STREAM(mFileInfo.pastProgramInfo[0], VID, Vid, 1);
                videoNum = mFileInfo.pastProgramInfo[0].u32VidStreamNum;

                EX_PRINTF("Video stream number = %d \n", videoNum);

                if (trackMeta->findInt32(kKeyFrameRate, &value))
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u16FpsInteger = value;
                if (trackMeta->findInt32(kKeyTrackID, &value))
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].s32StreamIndex = value;

                mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].s64Duration = durationUs / 1000;

                if (NULL == mVideoTrack.get())
                {
                    int data_len = 0;
                    int32_t trackID = 0;
                    (HI_VOID)trackMeta->findInt32(kKeyTrackID, &trackID);
                    HI_CHAR* data = (HI_CHAR*)mExtractor->getDrmTrackInfo(trackID, &data_len);
                    if (data && data_len > 0)
                    {
                        mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].bEnableTVP = HI_TRUE;
                        mFileInfo.bIsDrmFile = HI_TRUE;
                    }
                    mVideoTrack = mExtractor->getTrack(i);
                    mVideoTrackIndex = value;
                    EX_PRINTF("Enter [%s:%d], video track, mime = %s, track index = %d, bIsDrmFile = %d \n",
                        __FUNCTION__, __LINE__, mime, mVideoTrackIndex, mFileInfo.bIsDrmFile);

                    // To be fixed. The mime variable is modified abnormally somewhere, get it again.
                    trackMeta->findCString(kKeyMIMEType, &mime);
                }

                if (trackMeta->findInt32(kKeyWidth, &value))
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u16Width = value;
                if (trackMeta->findInt32(kKeyHeight, &value))
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u16Height = value;

                if (!strncasecmp(mime, MEDIA_MIMETYPE_VIDEO_VP8, strlen(MEDIA_MIMETYPE_VIDEO_VP8)))
                {
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32Format = HI_FORMAT_VIDEO_VP8;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_VIDEO_MPEG4, strlen(MEDIA_MIMETYPE_VIDEO_MPEG4)))
                {
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32Format = HI_FORMAT_VIDEO_MPEG4;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_VIDEO_AVC, strlen(MEDIA_MIMETYPE_VIDEO_AVC)))
                {
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32Format = HI_FORMAT_VIDEO_H264;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_VIDEO_MPEG2, strlen(MEDIA_MIMETYPE_VIDEO_MPEG2)))
                {
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32Format = HI_FORMAT_VIDEO_MPEG2;
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_VIDEO_WMV, strlen(MEDIA_MIMETYPE_VIDEO_WMV)))
                {
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32Format  = HI_FORMAT_VIDEO_WMV2;
                    if (trackMeta->findInt32(kKeyCodecVersion, &cdcversion))
                    {
                        switch (cdcversion)
                        {
                            case 1:
                            {
                                mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32Format  = HI_FORMAT_VIDEO_WMV1;
                                break;
                            }
                            case 2:
                            {
                                mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32Format  = HI_FORMAT_VIDEO_WMV2;
                                break;
                            }
                            case 3:
                            {
                                mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32Format  = HI_FORMAT_VIDEO_VC1;
                                mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u16Profile = 0;
                                mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32CodecVersion = 5;
                                mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].pu8Extradata = NULL;
                                mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32ExtradataSize = 0;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                    EX_PRINTF("[%s:%d], video codec type is WMV3 ", __FUNCTION__, __LINE__);
                }
                else if (!strncasecmp(mime, MEDIA_MIMETYPE_VIDEO_VC1, strlen(MEDIA_MIMETYPE_VIDEO_VC1)))
                {
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32Format  = HI_FORMAT_VIDEO_VC1;
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u16Profile = 1;
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32CodecVersion = 8;
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].pu8Extradata = NULL;
                    mFileInfo.pastProgramInfo[0].pastVidStream[videoNum].u32ExtradataSize = 0;

                    EX_PRINTF("[%s:%d], video codec type is VC1 ", __FUNCTION__, __LINE__);
                }
                else
                {
                    EX_PRINTF("[%s:%d], video codec type mime:%s ", __FUNCTION__, __LINE__, mime);
                }
                mFileInfo.pastProgramInfo[0].u32VidStreamNum++;
            }
            else
            {
                /* current only support audio and video */
                EX_PRINTF("[%s:%d] not support video & audio type ", __FUNCTION__, __LINE__);
            }
        }
    }

    *fileinfo = &mFileInfo;
    mParseFileInfo = true;
    EX_PRINTF("[%s:%d] mFileInfo.bIsDrmFile:%d", __FUNCTION__, __LINE__, mFileInfo.bIsDrmFile);

    return OK;
}

status_t SVRExtratorAdp::getFileInfo(HI_FORMAT_FILE_INFO_S **fileinfo)
{
    if (false != mParseFileInfo)
    {
        *fileinfo = &mFileInfo;
        return OK;
    }
    else
    {
        return UNKNOWN_ERROR;
    }
}

status_t SVRExtratorAdp::start()
{
    status_t err = OK;

    if (NULL == mVideoTrack.get() && NULL == mAudioTrack.get())
        return UNKNOWN_ERROR;

    if (NULL != mVideoTrack.get())
    {
        err = mVideoTrack->start();
        if (OK != err)
            EX_PRINTF("[%s:%d], video track start fail ", __FUNCTION__, __LINE__);
        mbVideoEndOfStream   = false;
    }

    if (NULL != mAudioTrack.get())
    {
        err = mAudioTrack->start();
        if (OK != err)
            EX_PRINTF("[%s:%d], audio track start fail ", __FUNCTION__, __LINE__);
        mbAudioEndOfStream   = false;
    }

    if (mDecryptHandle != NULL)
    {
        mDrmManagerClient->setPlaybackStatus(mDecryptHandle, Playback::START, 0);
    }

    return OK;
}

status_t SVRExtratorAdp::getTrackExtraData(HI_FORMAT_FRAME_S *frame)
{
    size_t numTracks = mExtractor->countTracks();
    uint8_t *ptr  = NULL;
    uint32_t size = 0;
    uint32_t keytype = 0;
    int32_t value = 0;
    int32_t ret = 0;
    int32_t isADTS;

    for (size_t i = 0; i < numTracks; ++i)
    {
        sp<MetaData> trackMeta = mExtractor->getTrackMetaData(i);
        (HI_VOID)trackMeta->findInt32(kKeyTrackID, &value);

        if (HI_FORMAT_DATA_VID == frame->eType && value == mVideoTrackIndex)
        {
            if (trackMeta->findData(kKeyAVCC, &keytype, (void const**)&ptr, &size))
            {
                if (keytype == kTypeAVCC)
                {
                    frame->pu8FrameHeader = (uint8_t*)malloc(size * 2);

                    if (NULL == frame->pu8FrameHeader)
                        return UNKNOWN_ERROR;

                    memset(frame->pu8FrameHeader, 0, size);
                    ret = _getH264SpsPps(ptr, size, frame->pu8FrameHeader, size * 2, &frame->u32FrameHeaderLen);

                    if (HI_SUCCESS != ret)
                    {
                        free(frame->pu8FrameHeader);
                        frame->pu8FrameHeader = NULL;
                        frame->u32FrameHeaderLen = 0;

                        return UNKNOWN_ERROR;
                    }

                    #if 0
                    uint32_t i = 0;

                    for (i = 0; i < frame->u32FrameHeaderLen; i++)
                    {
                        EX_PRINTF("%02x ", frame->pu8FrameHeader[i]);
                    }

                    EX_PRINTF("\n");
                    #endif
                }
            }
            else
            {
                frame->pu8FrameHeader = NULL;
                frame->u32FrameHeaderLen = 0;
            }
        }
        else if (HI_FORMAT_DATA_AUD == frame->eType && value == mAudioTrackIndex)
        {
            int32_t objectType, freqIndex, numChannels;

            if (misWidevineStreaming == false &&
                trackMeta->findData(kKeyESDS, &keytype, (void const**)&ptr, &size))
            {
                if (keytype == kTypeESDS)
                {
                    ESDS esds(ptr, size);

                    uint8_t objectTypeIndication;

                    if (esds.getObjectTypeIndication(&objectTypeIndication) != OK)
                    {
                        EX_PRINTF("getObjectTypeIndication fail\n");
                        return ERROR_MALFORMED;
                    }

                    const uint8_t *csd;
                    size_t csd_size;

                    if (esds.getCodecSpecificInfo((const void **)&csd, &csd_size) != OK)
                    {
                        EX_PRINTF("getCodecSpecificInfo fail\n");
                        return ERROR_MALFORMED;
                    }

                    ABitReader br(csd, csd_size);
                    objectType = br.getBits(5);

                    if (objectType == 31)
                    {
                        // AAC-ELD => additional 6 bits
                        objectType = 32 + br.getBits(6);
                    }

                    freqIndex = br.getBits(4);
                    numChannels = br.getBits(4);

                    //EX_PRINTF("[%s:%d] object type = %d, freqindex = %d, channel = %d ",
                    //    __FUNCTION__, __LINE__, objectType, freqIndex, numChannels);

                    frame->pu8FrameHeader = (uint8_t*)malloc(8);

                    if (NULL == frame->pu8FrameHeader)
                        return UNKNOWN_ERROR;

                    memset(frame->pu8FrameHeader, 0, 8);

                    _getADTSHeader(freqIndex, frame->u32Len, objectType, numChannels, frame->pu8FrameHeader);
                    frame->u32FrameHeaderLen = 7;
                }
            }
            else
            {
                frame->pu8FrameHeader = NULL;
                frame->u32FrameHeaderLen = 0;
            }
        }
    }

    return HI_SUCCESS;
}

status_t SVRExtratorAdp::getFrameMetadata(HI_FORMAT_FRAME_S *pFrame, MediaBuffer *pFrameRead)
{
    const void *pData = NULL;
    size_t size = 0;
    uint32_t type = 0;
    HI_S32 s32MetaValue = 0;
    HI_S32 IsKeyFrame = 0;

    if (pFrameRead->meta_data()->findInt32(kKeyIsSyncFrame, &IsKeyFrame))
    {
        pFrame->bKeyFrame = IsKeyFrame == 0 ? HI_FALSE : HI_TRUE;
    }

    if (pFrameRead->meta_data()->findData(kKeyCryptoIV, &type, &pData, &size))
    {
        if (size > 0)
        {
            pFrame->pu8IVBuffer = (HI_U8*)malloc(size);
            pFrame->u32IVSize = size;
            memcpy(pFrame->pu8IVBuffer, pData, size);
        }

        ALOGD("copy replicated data size:%d", size);
    } else {
        pFrame->pu8IVBuffer = NULL;
        pFrame->u32IVSize = 0;
        ALOGE("get replicated data faield, size:%d", size);
    }

    // get decryptsize
    if (pFrameRead->meta_data()->findData(kKeyEncryptedSizes, &type, &pData, &size))
    {
        if (size > 0)
        {
            pFrame->ps32Encryptsize = (HI_S32*)malloc(size);
            memset(pFrame->ps32Encryptsize, 0, size);
            memcpy(pFrame->ps32Encryptsize, pData, size);
            pFrame->s32Encryptsize = size;
        }

        ALOGD("copy decryptsize data size:%d", size);
    } else {
        pFrame->ps32Encryptsize = NULL;
        pFrame->ps32Encryptsize = 0;
        ALOGE("get decryptsize data faield, size:%d", size);
    }

    if (pFrameRead->meta_data()->findInt32(kKeyCryptoMode, &s32MetaValue))
    {
        pFrame->s32Cryptomode = s32MetaValue;
        ALOGD("s32Cryptomode is :%d", s32MetaValue);
    } else {
        pFrame->s32Cryptomode = 0;
        ALOGE("get s32Cryptomode faield");
    }

    if (pFrameRead->meta_data()->findData(kKeyCryptoKey, &type, &pData, &size))
    {
        if (size > 0)
        {
            pFrame->pu8KeyID = (HI_U8*)malloc(size);
            memset(pFrame->pu8KeyID, 0, size);
            memcpy(pFrame->pu8KeyID, pData, size);
            pFrame->u32KeyIDSize = size;
        }

        ALOGD("copy cryptokey data size:%d", size);
    } else {
        pFrame->pu8KeyID = NULL;
        pFrame->u32KeyIDSize = 0;
        ALOGE("get cryptokey data faield, size:%d", size);
    }
    return HI_SUCCESS;
}
status_t SVRExtratorAdp::readFrame(HI_FORMAT_FRAME_S *frame)
{
    status_t err = OK;
    int64_t timestamp = -1;
    int32_t IsKeyFrame = -1;
    //copy DRM IV Buffer for player using
    const void *pData = NULL;
    size_t size = 0;
    uint32_t type = 0;
    HI_S32 s32MetaValue = 0;

    if (NULL == frame){
        EX_PRINTF("%s,%d\n",__FILE__,__LINE__);
        return UNKNOWN_ERROR;
    }

#ifdef HISMOOTHSTREAMINGPLAYER_DRM_ENABLE
        HI_S32 handle = 0;
        HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
        sp<MetaData> FileMeta = mExtractor->getMetaData();
        if ((FileMeta->findInt32(kKeyStreamBufInfo, &handle)) && handle)
        {
            // check the stream is changed or not
            DEMUX_BUFFER_MGR_S *pstDemuxBufInfo = (DEMUX_BUFFER_MGR_S *)handle;
            HI_U32 u32StartTime = getCurrentTime();

            while (FILEINFO_UPDATE_DOING == pstDemuxBufInfo->u32FileUpdateFlag)// while file info is updating, wait it
            {
                //if exceed the max wait time, return fail,let player read again
                if ((getCurrentTime() - u32StartTime) > FILEINFO_UPDATE_WAIT_MAX)
                {
                    return HI_FAILURE;
                }
                usleep(100);
            }

            // when stream is changed, flush it and reset the read state
            if (FILEINFO_UPDATE_DONE == pstDemuxBufInfo->u32FileUpdateFlag)
            {
                mParseFileInfo = false;
                EXTRATOR_FREE_ALL_PROGRAMS(mFileInfo);
                (void)openFile(&pstFileInfo);

                mVideoReadTimes  = 0;
                mAudioReadTimes  = 0;
                mbVideoEndOfStream = true;
                mbAudioEndOfStream =  true;
                if (NULL != mVideoTrack.get())
                {
                    mbVideoEndOfStream   = false;
                }

                if (NULL != mAudioTrack.get())
                {
                    mbAudioEndOfStream   = false;
                }

                mLastVideoFramePts = -1;
                mLastAudioFramePts = -1;

                pthread_mutex_lock(&pstDemuxBufInfo->stMutex);
                pstDemuxBufInfo->u32FileUpdateFlag = FILEINFO_UPDATE_NONE;
                pthread_mutex_unlock(&pstDemuxBufInfo->stMutex);
            }
        }
#endif

    if (true == mbAudioEndOfStream && true == mbVideoEndOfStream)
    {
        EX_PRINTF("File is end of stream");
        return HI_FORMAT_ERRO_ENDOFFILE;
    }

    /*if (NULL != mVideoTrack.get()
        && ((mLastVideoFramePts < mLastAudioFramePts && false == mbVideoEndOfStream)
        || (mVideoReadTimes < MAX_READ_TIMES && false == mbVideoEndOfStream)
        || true == mbAudioEndOfStream))*/
    if (NULL != mVideoTrack.get()
        && ((mLastVideoFramePts <= mLastAudioFramePts && false == mbVideoEndOfStream)
        || (true == mbAudioEndOfStream) || (true == misWidevineStreaming && true == mSeeking)))
    {
        if (mSeeking)
        {
            err = mVideoTrack->read(&mVideoBuffer, &options);
            options.clearSeekTo();
            mSeeking = false;
        }
        else
        {
            err = mVideoTrack->read(&mVideoBuffer, NULL);
        }

        if (ERROR_END_OF_STREAM == err)
        {
            mbVideoEndOfStream = true;

            if (true == mbAudioEndOfStream)
            {
                EX_PRINTF("Video and audio is end of stream");
                return HI_FORMAT_ERRO_ENDOFFILE;
            }
            else
            {
                EX_PRINTF("Set mbVideoEndOfStream = true");
            }
        }

        if (OK != err)
        {
            EX_PRINTF("[%s:%d], read video frame fail", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }

        frame->s32StreamIndex = mVideoTrackIndex;
        frame->eType = HI_FORMAT_DATA_VID;
        frame->pu8Addr = (unsigned char*)mVideoBuffer->data() + mVideoBuffer->range_offset();
        frame->u32Len = mVideoBuffer->range_length();
        frame->s64Pts = HI_FORMAT_NO_PTS;
        frame->s64Pos = HI_FORMAT_NO_POS;
        if ( mVideoBuffer->meta_data()->findInt64(kKeyTime, &timestamp))
        {
            frame->s64Pts  = timestamp / 1000;
            mLastVideoFramePts = frame->s64Pts;
        }
        if ( mVideoBuffer->meta_data()->findInt32(kKeyIsSyncFrame, &IsKeyFrame))
        {
            frame->bKeyFrame  = (HI_BOOL)IsKeyFrame;
        }

        getFrameMetadata(frame, mVideoBuffer);

        getTrackExtraData(frame);
        /*separate extradata from original frame,
         *if video is AVC, frame should not contain another codec private data,
         *otherwise encrypt data offset is invalid */
        if (!frame->pu8FrameHeader && mVideoBuffer->meta_data()->findData(kKeyCodecPriData, &type, &pData, &size)) {
            if (size < frame->u32Len) {
                frame->pu8FrameHeader = (HI_U8*)malloc(size);
                memcpy(frame->pu8FrameHeader, pData, size);
                frame->pu8Addr += size;//change frame offset
                frame->u32FrameHeaderLen = size;
                frame->u32Len -= size;
                ALOGD("video codec private data contained in frame buffer, size:%d", size);
            } else {
                ALOGE("video Media buffer's extra data(%d Bytes) too large, buffer size(%d Bytes)", size, frame->u32Len);
            }
        }

        mVideoReadTimes++;
#if 0
        EX_PRINTF("[%s:%d], read frame", __FUNCTION__, __LINE__);

        static HI_MMZ_BUF_S caBuffer;
        static FILE *pfile = NULL;
        HI_S32 s32Ret;

        EX_PRINTF("[%s:%d], read frame", __FUNCTION__, __LINE__);

        if (NULL == pfile)
        {
            pfile = fopen("/data/audio/vid_es.es", "w+b");
            EX_PRINTF("[%s:%d], xxxxxxxx2", __FUNCTION__, __LINE__);
            memset(&caBuffer, 0, sizeof(HI_MMZ_BUF_S));
            strncpy(caBuffer.bufname, "ssss", sizeof(caBuffer.bufname));
            caBuffer.bufsize = 1*1024*1024;
            s32Ret = HI_MMZ_Malloc(&caBuffer);
        }

        EX_PRINTF("[%s:%d], read video frame", __FUNCTION__, __LINE__);

        if (NULL != frame->pu8Addr && NULL != pfile)
        {
            if (NULL != frame->pu8FrameHeader)
            {
                EX_PRINTF("[%s:%d], read video frame fail", __FUNCTION__, __LINE__);
                memcpy(caBuffer.user_viraddr, frame->pu8FrameHeader, frame->u32FrameHeaderLen);
            }
            else
            {
                frame->u32FrameHeaderLen = 0;
            }
            EX_PRINTF("[%s:%d], read video frame fail", __FUNCTION__, __LINE__);
            HI_SEC_MMZ_TA2CA((unsigned long)(mVideoBuffer->data()), caBuffer.phyaddr + frame->u32FrameHeaderLen, frame->u32Len);
            EX_PRINTF("[%s:%d], read video frame fail", __FUNCTION__, __LINE__);
            fwrite(caBuffer.user_viraddr, 1, frame->u32Len + frame->u32FrameHeaderLen, pfile);
        }
#endif

        //EX_PRINTF("======READ VID Frame: index = %d, data len = %d, frame header len = %d, timestampl = %lld ",
        //    frame->s32StreamIndex, frame->u32Len, frame->u32FrameHeaderLen, frame->s64Pts);

        if (MAX_READ_TIMES == mVideoReadTimes)
            mAudioReadTimes = 0;

        return OK;
    }
    //else if (NULL != mAudioTrack.get()
    //    && (mAudioReadTimes < MAX_READ_TIMES && false == mbAudioEndOfStream) || true == mbVideoEndOfStream)
    else if (NULL != mAudioTrack.get()
        && ((false == mbAudioEndOfStream)
        || true == mbVideoEndOfStream))
    {
        if (mSeeking)
        {
            if (true == misWidevineStreaming)
            {
                if (NULL == mVideoTrack.get())
                {
                    err = mAudioTrack->read(&mAudioBuffer, NULL);
                    options.clearSeekTo();
                    mSeeking = false;
                }
                else
                {
                    return HI_FAILURE;
                }
            }
            else
            {
                err = mAudioTrack->read(&mAudioBuffer, &options);
                options.clearSeekTo();
                mSeeking = false;
            }

        }
        else
        {
            err = mAudioTrack->read(&mAudioBuffer, NULL);
        }

        if (ERROR_END_OF_STREAM == err)
        {
            mbAudioEndOfStream = true;
            if (true == mbVideoEndOfStream)
            {
                EX_PRINTF("Audio and video is end of stream");
                return HI_FORMAT_ERRO_ENDOFFILE;
            }
            else
            {
                EX_PRINTF("Set mbAudioEndOfStream = true");
            }
        }

        if (OK != err)
        {
            EX_PRINTF("[%s:%d], read audio frame fail", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }

        frame->s32StreamIndex = mAudioTrackIndex;
        frame->eType = HI_FORMAT_DATA_AUD;
        if (true == misWidevineStreaming)
        {
            frame->pu8Addr = (unsigned char*)mAudioBuffer->data() + mAudioBuffer->range_offset();
            frame->u32Len = mAudioBuffer->range_length();
        }
        else
        {
            frame->pu8Addr = (unsigned char*)mAudioBuffer->data();
            frame->u32Len  = mAudioBuffer->size();
        }
        frame->s64Pts = HI_FORMAT_NO_PTS;
        frame->s64Pos = HI_FORMAT_NO_POS;

        if ( mAudioBuffer->meta_data()->findInt64(kKeyTime, &timestamp))
        {
            frame->s64Pts  = timestamp / 1000;
            mLastAudioFramePts = frame->s64Pts;
        }
        getFrameMetadata(frame, mAudioBuffer);

        getTrackExtraData(frame);
        mAudioReadTimes++;

        if (NULL != frame->pu8FrameHeader)
        {
            uint8_t *pframe = (uint8_t*)malloc(frame->u32FrameHeaderLen + frame->u32Len + 1);

            if (NULL != pframe)
            {
                if (true == misWidevineStreaming)
                {
                    memcpy(pframe, frame->pu8FrameHeader, frame->u32FrameHeaderLen);
                    memcpy(pframe + frame->u32FrameHeaderLen, frame->pu8Addr, frame->u32Len);
                }
                else
                {
                     memcpy(pframe, frame->pu8Addr, frame->u32Len);
                     memcpy(pframe + frame->u32Len, frame->pu8FrameHeader, frame->u32FrameHeaderLen);
                }
                frame->pu8Addr = pframe;
                frame->u32Len  += frame->u32FrameHeaderLen;
            }
        }
        else if (mAudioBuffer->meta_data()->findData(kKeyCodecPriData, &type, &pData, &size)) {
            if (size < frame->u32Len) {
                frame->pu8FrameHeader = (HI_U8*)malloc(size);
                memcpy(frame->pu8FrameHeader, pData, size);
                frame->u32FrameHeaderLen = size;
                ALOGD("aduio codec private data contained in frame buffer, size:%d", size);
            } else {
                ALOGE("audio Media buffer's extra data(%d Bytes) too large, buffer size(%d Bytes)", size, frame->u32Len);
            }
        }

        //EX_PRINTF("======READ AUD Frame: index = %d, data len = %d, frame header len = %d, timestampl = %lld ",
        //    frame->s32StreamIndex, frame->u32Len, frame->u32FrameHeaderLen, frame->s64Pts);

#if 0
        static FILE *pfile = NULL;

        if (NULL == pfile)
            pfile = fopen("/data/audio/aud_es.aac", "w+b");

        if (NULL != frame->pu8Addr && NULL != pfile)
            fwrite(frame->pu8Addr, 1, frame->u32Len, pfile);
#endif

        if (2 * MAX_READ_TIMES == mAudioReadTimes)
            mVideoReadTimes = 0;

        return OK;
    }

    EX_PRINTF("%s,%d,mVideoReadTimes=%d,mAudioReadTimes=%d\n",__FILE__,__LINE__,mVideoReadTimes,mAudioReadTimes);
    mVideoReadTimes = 0;
    mAudioReadTimes = 0;

    return UNKNOWN_ERROR;
}

status_t SVRExtratorAdp::freeFrame(HI_FORMAT_FRAME_S *frame)
{
    HI_S32 s32IsSecureBuffer = 0;
    if (NULL == frame)
    {
        return OK;
    }

    if (frame->eType == HI_FORMAT_DATA_VID)
    {
        if (NULL != mVideoBuffer)
        {
            mVideoBuffer->release();
        }
    }
    else if (frame->eType == HI_FORMAT_DATA_AUD)
    {
        if (mAudioBuffer->data() != frame->pu8Addr && NULL != frame->pu8FrameHeader)
        {
            free(frame->pu8Addr);
            frame->pu8Addr = NULL;
        }

        if (NULL != mAudioBuffer)
            mAudioBuffer->release();
    }

    if (NULL != frame->pu8FrameHeader)
    {
        free(frame->pu8FrameHeader);
        frame->pu8FrameHeader = NULL;
    }
    if (NULL != frame->pu8IVBuffer)
    {
        free(frame->pu8IVBuffer);
        frame->pu8IVBuffer = NULL;
    }
    if (NULL != frame->pu8KeyID)
    {
        free(frame->pu8KeyID);
        frame->pu8KeyID = NULL;
    }

    if (NULL != frame->ps32Encryptsize)
    {
        free(frame->ps32Encryptsize);
        frame->ps32Encryptsize = NULL;
    }

    return OK;
}

status_t SVRExtratorAdp::invoke (HI_U32 u32InvokeId, HI_VOID *pArg)
{
    const char *mime = NULL;

    if (HI_FORMAT_INVOKE_SET_COOKIE == u32InvokeId)
    {
        EX_PRINTF("[%s:%d], HI_FORMAT_INVOKE_SET_COOKIE", __FUNCTION__, __LINE__);

        aszHeaders = (HI_CHAR*)(*((HI_U32 *) pArg));

        EX_PRINTF("[%s:%d]: headers='%s'\n", __FUNCTION__, __LINE__, aszHeaders);
        return HI_SUCCESS;
    }
#ifdef HISMOOTHSTREAMINGPLAYER_DRM_ENABLE
    else if (HI_FORMAT_INVOKE_SET_BUFFER_CONFIG == u32InvokeId)
    {
        EX_PRINTF("SVRExtratorAdp::invoke HI_FORMAT_INVOKE_SET_BUFFER_CONFIG\n");

        memcpy(&stBufConfig, pArg, sizeof(HI_FORMAT_BUFFER_CONFIG_S));
        if (mExtractor != NULL)
        {
            HI_S32 handle;
            DEMUX_BUFFER_MGR_S *pstDemuxBufInfo = NULL;
            sp<MetaData> FileMeta = mExtractor->getMetaData();

            if ((FileMeta->findInt32(kKeyStreamBufInfo, &handle)) && handle)
            {
                pstDemuxBufInfo = (DEMUX_BUFFER_MGR_S *)handle;
            }

            if (NULL == pstDemuxBufInfo)
            {
                EX_PRINTF("pstDemuxBufInfo is NULL\n");
                return HI_FAILURE;
            }

            HI_FORMAT_BUFFER_CONFIG_S *pstConfig = (HI_FORMAT_BUFFER_CONFIG_S *)pArg;
            if (pstConfig->s64EventEnough > pstConfig->s64Total
                || pstConfig->s64EventStart > pstConfig->s64Total
                || pstConfig->s64EventStart < 0 || pstConfig->s64TimeOut < 0
                || pstConfig->s64EventEnough < 0 || pstConfig->s64Total < 0)
            {
                EX_PRINTF("HI_FORMAT_INVOKE_SET_BUFFER_CONFIG Args is not right\n");
                return HI_FAILURE;
            }
            if (HI_FORMAT_BUFFER_CONFIG_SIZE == pstConfig->eType)
            {
                if ((s64BufferMaxSize) && (pstConfig->s64Total > s64BufferMaxSize))
                {
                    EX_PRINTF("s64Total(%lld) can not larger than s64BufferMaxSize(%lld)\n", pstConfig->s64Total, s64BufferMaxSize);
                    return HI_FAILURE;
                }
                pstDemuxBufInfo->stConfigSize.eType          = pstConfig->eType;
                pstDemuxBufInfo->stConfigSize.s64EventEnough = pstConfig->s64EventEnough;
                pstDemuxBufInfo->stConfigSize.s64EventStart  = pstConfig->s64EventStart;
                pstDemuxBufInfo->stConfigSize.s64TimeOut     = pstConfig->s64TimeOut;
                pstDemuxBufInfo->stConfigSize.s64Total       = pstConfig->s64Total;
                pstDemuxBufInfo->eConfigUser = HI_FORMAT_BUFFER_CONFIG_SIZE;
                EX_PRINTF("HI_FORMAT_INVOKE_SET_BUFFER_CONFIG Args is HI_FORMAT_BUFFER_CONFIG_SIZE\n");
            }
            else if(HI_FORMAT_BUFFER_CONFIG_TIME == pstConfig->eType)
            {
                pstDemuxBufInfo->stConfigTime.eType          = pstConfig->eType;
                pstDemuxBufInfo->stConfigTime.s64EventEnough = pstConfig->s64EventEnough;
                pstDemuxBufInfo->stConfigTime.s64EventStart  = pstConfig->s64EventStart;
                pstDemuxBufInfo->stConfigTime.s64TimeOut     = pstConfig->s64TimeOut;
                pstDemuxBufInfo->stConfigTime.s64Total       = pstConfig->s64Total;
                pstDemuxBufInfo->eConfigUser = HI_FORMAT_BUFFER_CONFIG_TIME;
                EX_PRINTF("HI_FORMAT_INVOKE_SET_BUFFER_CONFIG Args is HI_FORMAT_BUFFER_CONFIG_TIME\n");
            }
            else
            {
                EX_PRINTF("HI_FORMAT_INVOKE_SET_BUFFER_CONFIG ,unknow config type\n");
                return HI_FAILURE;
            }
            return HI_SUCCESS;
        }
        return HI_SUCCESS;
    }
    else if (HI_FORMAT_INVOKE_SET_BUFFER_MAX_SIZE == u32InvokeId)
    {
        EX_PRINTF("SVRExtratorAdp::invoke HI_FORMAT_INVOKE_SET_BUFFER_MAX_SIZE\n");
        if (NULL == pArg)
        {
            return HI_FAILURE;
        }
        HI_S64 maxsize = *(HI_S64*)pArg;
        if (maxsize < DEMUX_BUFFER_SIZE_LIMIT)
        {
            EX_PRINTF("[%s:%d], SVRExtratorAdp::invoke, buffer max size is less than 2MB!!\n", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }

        s64BufferMaxSize = maxsize;

        if (mExtractor != NULL)
        {
            HI_S32 handle;
            DEMUX_BUFFER_MGR_S *pstDemuxBufInfo = NULL;
            sp<MetaData> FileMeta = mExtractor->getMetaData();

            if ((FileMeta->findInt32(kKeyStreamBufInfo, &handle)) && handle)
            {
                pstDemuxBufInfo = (DEMUX_BUFFER_MGR_S *)handle;
            }
            if (pstDemuxBufInfo)
            {
                pstDemuxBufInfo->s64BufferMaxSize = maxsize;
                EX_PRINTF("SVRExtratorAdp::invoke HI_FORMAT_INVOKE_SET_BUFFER_MAX_SIZE success\n");
            }
        }
        return HI_SUCCESS;
    }
    sp<MetaData> FileMeta = mExtractor->getMetaData();
    HI_S32 handle;
    DEMUX_BUFFER_MGR_S *pstDemuxBufInfo = NULL;
    if ((FileMeta->findInt32(kKeyStreamBufInfo, &handle)) && handle)
    {
        pstDemuxBufInfo = (DEMUX_BUFFER_MGR_S *)handle;
    }

    if (HI_FORMAT_INVOKE_PRE_CLOSE_FILE == u32InvokeId)
    {
        HI_PTR hissplayer;
        if ((FileMeta->findPointer(kKeyHiSShandle, &hissplayer))
            && hissplayer)
        {
            uint32_t s32Ret = HI_SVR_SMOOTHSTREAMING_Invoke(hissplayer, u32InvokeId, pArg);
            if (HI_SUCCESS != s32Ret)
            {
                EX_PRINTF("[%s:%d], HI_SVR_SMOOTHSTREAMING_Invoke failed:0x%x", __FUNCTION__, __LINE__, s32Ret);
                return HI_FAILURE;
            }
        }
    }
    else if (HI_FORMAT_INVOKE_GET_BUFFER_CONFIG == u32InvokeId)
    {
        //EX_PRINTF("SVRExtratorAdp::invoke HI_FORMAT_INVOKE_GET_BUFFER_CONFIG\n");
        if (NULL == pArg)
        {
            EX_PRINTF("HI_FORMAT_INVOKE_BUFFER_CONFIG Args is NULL\n");
            return HI_FAILURE;
        }

        HI_FORMAT_BUFFER_CONFIG_S *pstConfig = (HI_FORMAT_BUFFER_CONFIG_S *)pArg;
        HI_S32 s32Type = pstConfig->eType;

        memset(pstConfig, 0, sizeof(HI_FORMAT_BUFFER_CONFIG_S));

        if (NULL != pstDemuxBufInfo && HI_FORMAT_BUFFER_CONFIG_SIZE == s32Type)
        {
            pstConfig->eType          = HI_FORMAT_BUFFER_CONFIG_SIZE;
            pstConfig->s64EventEnough = pstDemuxBufInfo->stConfigSize.s64EventEnough;
            pstConfig->s64EventStart  = pstDemuxBufInfo->stConfigSize.s64EventStart;
            pstConfig->s64TimeOut     = 0; // TODO: 暂不支持，后续补充与smoothstreaming内部超时对接
            pstConfig->s64Total       = pstDemuxBufInfo->stConfigSize.s64Total;
            EX_PRINTF("SVRExtratorAdp::invoke HI_FORMAT_INVOKE_GET_BUFFER_CONFIG success\n");
        }
        else
        {
            EX_PRINTF("HI_FORMAT_INVOKE_BUFFER_CONFIG ,only support the size format\n");
            return HI_FAILURE;
        }
    }
    else if ((HI_FORMAT_INVOKE_GET_BUFFER_STATUS == u32InvokeId)
        || (HI_FORMAT_INVOKE_GET_VIDEO_FORMAT_BUFFER == u32InvokeId)
        || (HI_FORMAT_INVOKE_GET_AUDIO_FORMAT_BUFFER == u32InvokeId))
    {
        if (NULL == pArg)
        {
            EX_PRINTF("HI_FORMAT_INVOKE_BUFFER_STATUS Args is NULL\n");
            return HI_FAILURE;
        }
        HI_FORMAT_BUFFER_STATUS_S *pstStat = (HI_FORMAT_BUFFER_STATUS_S*)pArg;
        memset(pstStat, 0x0, sizeof(HI_FORMAT_BUFFER_STATUS_S));
        if (pstDemuxBufInfo)
        {
            pstStat->s64BufferSize = pstDemuxBufInfo->s64Size;
            pstStat->s64Duration   = pstDemuxBufInfo->s64RearPts - pstDemuxBufInfo->s64FrontPts;
        }
    }
    else if ((HI_FORMAT_INVOKE_GET_BUFFER_LAST_PTS == u32InvokeId)
        || (HI_FORMAT_INVOKE_GET_LAST_AUDBUF_PTS == u32InvokeId)
        || (HI_FORMAT_INVOKE_GET_LAST_VIDBUF_PTS == u32InvokeId))
    {
        if (NULL == pArg)
        {
            EX_PRINTF("HI_FORMAT_INVOKE_GET_BUFFER_LAST_PTS Args is null\n");
            return HI_FAILURE;
        }

        if (pstDemuxBufInfo)
        {
            *(HI_S64*)pArg = pstDemuxBufInfo->s64RearPts;
        }
    }
    else if (HI_FORMAT_INVOKE_GET_BANDWIDTH == u32InvokeId)
    {
        HI_PTR hissplayer;
        HI_SVR_SMOOTHSTREAMING_RUNNING_INFO_S stPlayerRunningInfo;

        if (NULL == pArg)
        {
            EX_PRINTF("HI_FORMAT_INVOKE_GET_BANDWIDTH Args is NULL\n");
            return HI_FAILURE;
        }

        if ((FileMeta->findPointer(kKeyHiSShandle, &hissplayer))
            && hissplayer)
        {
            uint32_t s32Ret = HI_SVR_SMOOTHSTREAMING_GetPlayerInfo(hissplayer, &stPlayerRunningInfo);
            if (HI_SUCCESS != s32Ret)
            {
                EX_PRINTF("[%s:%d], HI_SVR_SMOOTHSTREAMING_GetPlayerInfo failed:0x%x", __FUNCTION__, __LINE__, s32Ret);
                return HI_FAILURE;
            }
            *((HI_S64 *)pArg) = stPlayerRunningInfo.s32CurBitrate;
        }
    }
    else if (HI_FORMAT_INVOKE_SET_STREAM_INFO == u32InvokeId)
    {
         HI_FORMAT_STREAM_INFO_S* info = (HI_FORMAT_STREAM_INFO_S*)pArg;
         HI_FORMAT_PROGRAM_INFO_S* prog = &mFileInfo.pastProgramInfo[info->s32ProgID];
         HI_S64 stream_index = 0;
         int32_t value = 0, audioNum = 0;
         size_t numTracks = mExtractor->countTracks();

        EX_PRINTF("[%s:%d], SVRExtratorAdp::invoke HI_FORMAT_INVOKE_SET_STREAM_INFO", __FUNCTION__, __LINE__);
        if (info->s32VidID < prog->u32VidStreamNum)
        {
            mVideoTrackIndex = prog->pastVidStream[info->s32VidID].s32StreamIndex;
        }

        if (info->s32AudID < prog->u32AudStreamNum)
        {
            mAudioTrackIndex = prog->pastAudStream[info->s32AudID].s32StreamIndex;
        }

        if (info->s32SubID < prog->u32SubStreamNum)
        {
            stream_index = prog->pastSubStream[info->s32SubID].s32StreamIndex;
            uint32_t s32Ret = HI_SUCCESS;
            HI_PTR hissplayer;
            HI_SVR_SMOOTHSTREAMING_STREAMID_S stStreamID;
            HI_SVR_SMOOTHSTREAMING_RUNNING_INFO_S stPlayerRunningInfo;
            if ((FileMeta->findPointer(kKeyHiSShandle, &hissplayer))
                && hissplayer)
            {
                s32Ret = HI_SVR_SMOOTHSTREAMING_GetPlayerInfo(hissplayer, &stPlayerRunningInfo);
                if (HI_SUCCESS != s32Ret)
                {
                    EX_PRINTF("[%s:%d], HI_SVR_SMOOTHSTREAMING_GetPlayerInfo failed:0x%x", __FUNCTION__, __LINE__, s32Ret);
                    return HI_FAILURE;
                }

                stStreamID.u16SubStreamId = stream_index;
                stStreamID.u16VidStreamId = stPlayerRunningInfo.s32CurVidStreamIdx;
                stStreamID.u16AudStreamId = stPlayerRunningInfo.s32CurAudStreamIdx;
                s32Ret = HI_SVR_SMOOTHSTREAMING_SetParam(hissplayer,
                                                         HI_SVR_SMOOTHSTREAMING_ATTR_STREAM_ID,
                                                         &stStreamID);
                if (HI_SUCCESS != s32Ret)
                {
                    EX_PRINTF("[%s:%d], HI_SVR_SMOOTHSTREAMING_SetParam failed:0x%x", __FUNCTION__, __LINE__, s32Ret);
                    return HI_FAILURE;
                }
            }
        }

        for (size_t i = 0; i < numTracks; ++i)
        {
            sp<MetaData> trackMeta = mExtractor->getTrackMetaData(i);

            if ((trackMeta->findCString(kKeyMIMEType, &mime)) && (!strncasecmp("audio/", mime, 6)))
            {
                audioNum = mFileInfo.pastProgramInfo[0].u32AudStreamNum;
                if (trackMeta->findInt32(kKeyTrackID, &value) && (value == mAudioTrackIndex))
                {
                    mAudioTrack = mExtractor->getTrack(i);
                }
            }

            if ((trackMeta->findCString(kKeyMIMEType, &mime)) && (!strncasecmp("video/", mime, 6)))
            {
                audioNum = mFileInfo.pastProgramInfo[0].u32VidStreamNum;
                if (trackMeta->findInt32(kKeyTrackID, &value) && (value == mVideoTrackIndex))
                {
                    mVideoTrack = mExtractor->getTrack(i);
                }
            }
        }
    }
#endif
    else if (HI_FORMAT_INVOKE_GET_DRM_INFO == u32InvokeId)
    {
        //TODO:to support widevine & ASF
        HI_FORMAT_DRM_INFO_S* drm_info = (HI_FORMAT_DRM_INFO_S*)pArg;
        memset(drm_info, 0, sizeof(*drm_info));
        int mime_str_len = 0;
        int data_len = 0;
        int32_t trackID = 0;
        size_t numTracks = mExtractor->countTracks();

        if (strcasecmp(mMimeType.string(), MEDIA_MIMETYPE_CONTAINER_WVM))
        {
            for (size_t i = 0; i < numTracks; ++i)
            {
                sp<MetaData> trackMeta = mExtractor->getTrackMetaData(i);
                (HI_VOID)trackMeta->findInt32(kKeyTrackID, &trackID);

                HI_CHAR* data = (HI_CHAR*)mExtractor->getDrmTrackInfo(trackID, &data_len);
                if (data)
                {
                    drm_info->headers[drm_info->u32HeaderNum].pu8Data = (HI_U8*)data;
                    drm_info->headers[drm_info->u32HeaderNum].s32Size = data_len;
                    drm_info->headers[drm_info->u32HeaderNum].s32ID = trackID;
                    drm_info->u32HeaderNum++;
                    ALOGE("Get SmoothStreaming DRM info succeed, track id:%d, ipmp size:%d, val:%p",
                            trackID, data_len, data);
                }
            }
        }

        mime_str_len = strlen(mMimeType.string());
        mime_str_len = (mime_str_len <= HI_FORMAT_MIMETYPE_LEN) ? mime_str_len:HI_FORMAT_MIMETYPE_LEN;
        memcpy(drm_info->szMimeType, mMimeType.string(), mime_str_len);
        ALOGE("mMimeType is %s",mMimeType.string());
        return HI_SUCCESS;
    }

    return HI_SUCCESS;
}

status_t SVRExtratorAdp::seekTo(int64_t time_us)
{
    mSeeking = true;

    options.setSeekTo(time_us);
    EX_PRINTF("[%s:%d], SVRExtratorAdp::seekTo %lldus", __FUNCTION__, __LINE__, time_us);
    //mark it for tplay error
    //mVideoTrackIndex = -1;
    //mAudioTrackIndex = -1;
    mVideoReadTimes  = 0;
    mAudioReadTimes  = 0;
    if (NULL != mVideoTrack.get())
    {
        mbVideoEndOfStream   = false;
    }

    if (NULL != mAudioTrack.get())
    {
        mbAudioEndOfStream   = false;
    }

    //misWidevineStreaming = false;
    mLastVideoFramePts = -1;
    mLastAudioFramePts = -1;

    return OK;
}

status_t SVRExtratorAdp::stop()
{
    status_t err = OK;

    if (mDecryptHandle != NULL)
    {
        mDrmManagerClient->setPlaybackStatus(mDecryptHandle, Playback::STOP, 0);
        mDecryptHandle = NULL;
        mDrmManagerClient = NULL;
    }

    if (NULL != mVideoTrack.get())
    {
        err = mVideoTrack->stop();
        if (OK != err)
            EX_PRINTF("[%s:%d], video track stop fail ", __FUNCTION__, __LINE__);
    }

    if (NULL != mAudioTrack.get())
    {
        err = mAudioTrack->stop();
        if (OK != err)
            EX_PRINTF("[%s:%d], audio track stop fail ", __FUNCTION__, __LINE__);
    }

    mVideoTrackIndex = -1;
    mAudioTrackIndex = -1;
    mVideoReadTimes  = 0;
    mAudioReadTimes  = 0;
    mbVideoEndOfStream   = true;
    mbAudioEndOfStream   = true;
    //misWidevineStreaming = false;

    return OK;
}

typedef struct tagEXTRACTOR_MEMBER_S
{
    HI_CHAR filename[MAX_URI_NAME_LEN];
    SVRExtratorAdp *extractor;
}EXTRACTOR_MEMBER_S;

extern "C" HI_S32 SVR_EXTRACTOR_Create(HI_HANDLE *phandle)
{
    EXTRACTOR_MEMBER_S *handle = NULL;
    HI_FORMAT_FILE_INFO_S *pstFileInfo;

    EX_PRINTF("[%s:%d] Enter SVR_EXTRACTOR_Create\n", __FUNCTION__, __LINE__);

    if (NULL == phandle)
        return HI_FAILURE;

    handle = (EXTRACTOR_MEMBER_S*)malloc(sizeof(EXTRACTOR_MEMBER_S));

    if (NULL == handle)
        return HI_FAILURE;

    memset(handle, 0, sizeof(EXTRACTOR_MEMBER_S));
    handle->extractor = new SVRExtratorAdp();

    if (NULL == handle->extractor)
    {
        EX_PRINTF("[%s:%d] extractor create fail, exit", __FUNCTION__, __LINE__);
        goto err;
    }
    else
    {
        EX_PRINTF("[%s:%d] Create extractor adp handle success \n", __FUNCTION__, __LINE__);
    }

    *phandle = (HI_U32)handle;
    return HI_SUCCESS;

err:
    if (NULL != handle->extractor)
    {
        delete handle->extractor;
        handle->extractor = NULL;
    }

    free(handle);

    return HI_FAILURE;
}

extern "C" HI_S32 SVR_EXTRACTOR_SetDataSource(HI_HANDLE handle, HI_CHAR *uri, HI_CHAR *headers,
                                                            HI_VOID *pArg)
{
    status_t ret;
    EXTRACTOR_MEMBER_S *phandle = (EXTRACTOR_MEMBER_S*)handle;
    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
    char *pszFileOffset = NULL;
    char *pszFileLength = NULL;
    char *pszFileUrl = uri;
    char aszTmpFileUrl[FMT_MAX_URL_LEN];

    if (NULL == phandle || NULL == uri)
    {
        EX_PRINTF("[%s:%d] invalid param, return", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    if (NULL == phandle->extractor)
    {
        EX_PRINTF("[%s:%d] Extractor is not create, return fail", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    if (strlen(uri) < MAX_URI_NAME_LEN)
    {
        memcpy(phandle->filename, uri, strlen(uri));
    }
    else
    {
        EX_PRINTF("[%s:%d] uri size is large than MAX_URL_LEN, err", __FUNCTION__, __LINE__);
        goto err;
    }
#if 0
    pszFileOffset = strstr(uri, SEPARATE_SYMBOL_OFFSET);

    if (NULL != pszFileOffset)
    {
        if ((pszFileOffset - uri) > (FMT_MAX_URL_LEN - 1))
        {
            goto err;
        }

        memset(aszTmpFileUrl, 0, FMT_MAX_URL_LEN);
        memcpy(aszTmpFileUrl, uri, pszFileOffset - uri);
        pszFileUrl = aszTmpFileUrl;
    }
#endif
    EX_PRINTF("[%s:%d] New url = %s ", __FUNCTION__, __LINE__, pszFileUrl);
    EX_PRINTF("[%s:%d] HI_FORMAT_INVOKE_SET_COOKIE headers:%s ", __FUNCTION__, __LINE__, headers);

    (void)phandle->extractor->invoke(HI_FORMAT_INVOKE_SET_COOKIE, (void *)&headers);

    // TODO: send headers by createDataSource function
    ret = phandle->extractor->createDataSource(pszFileUrl, NULL, pArg);
    if (OK != ret)
    {
        EX_PRINTF("[%s:%d] Create data source fail, exit", __FUNCTION__, __LINE__);
        goto err;
    }

    ret = phandle->extractor->openFile(&pstFileInfo);
    if (OK != ret)
    {
        EX_PRINTF("[%s:%d] Get file information fail", __FUNCTION__, __LINE__);
        goto err;
    }

    ret = phandle->extractor->start();
    if (OK != ret)
    {
        EX_PRINTF("[%s:%d] Extractor start fail", __FUNCTION__, __LINE__);
        goto err;
    }

    return HI_SUCCESS;

err:
    if (NULL != phandle->extractor)
        phandle->extractor->reset();

    return HI_FAILURE;
}

extern "C" HI_S32 SVR_EXTRACTOR_GetFileInfo(HI_HANDLE handle, HI_FORMAT_FILE_INFO_S **pstFileInfo)
{
    status_t ret;
    EXTRACTOR_MEMBER_S *phandle = (EXTRACTOR_MEMBER_S*)handle;

    if (NULL == phandle || NULL == phandle->extractor)
    {
        //EX_PRINTF("handle invalid \n");
        return HI_FAILURE;
    }

    ret = phandle->extractor->getFileInfo(pstFileInfo);

    if (OK != ret)
    {
        EX_PRINTF("Get file information fail \n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

extern "C" HI_S32 SVR_EXTRACTOR_ReadFrame(HI_HANDLE handle, HI_FORMAT_FRAME_S *frame)
{
    status_t ret;
    EXTRACTOR_MEMBER_S *phandle = (EXTRACTOR_MEMBER_S*)handle;

    if (NULL == phandle || NULL == phandle->extractor)
    {
        return HI_FAILURE;
    }

    ret = phandle->extractor->readFrame(frame);
    if (HI_FORMAT_ERRO_ENDOFFILE == ret)
    {
        EX_PRINTF("[%s:%d] End of file \n", __FUNCTION__, __LINE__);
        return HI_FORMAT_ERRO_ENDOFFILE;
    }
    else
    {
        //EX_PRINTF("[%s:%d] Read frame fail ret=%d\n", __FUNCTION__, __LINE__, ret);
        return ret;
    }

    return HI_SUCCESS;
}

extern "C" HI_S32 SVR_EXTRACTOR_Invoke(HI_HANDLE handle, HI_U32 u32InvokeId, void *pArg)
{
    status_t ret;
    EXTRACTOR_MEMBER_S *phandle = (EXTRACTOR_MEMBER_S*)handle;

    if (NULL == phandle || NULL == phandle->extractor)
    {
        return HI_FAILURE;
    }

    ret = phandle->extractor->invoke(u32InvokeId, pArg);

    if (OK != ret)
    {
        EX_PRINTF("[%s:%d] SVR_EXTRACTOR_Invoke fail \n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

extern "C" HI_S32 SVR_EXTRACTOR_Free(HI_HANDLE handle, HI_FORMAT_FRAME_S *frame)
{
    status_t ret;
    EXTRACTOR_MEMBER_S *phandle = (EXTRACTOR_MEMBER_S*)handle;

    if (NULL == phandle || NULL == phandle->extractor)
    {
        return HI_FAILURE;
    }

    ret = phandle->extractor->freeFrame(frame);

    if (OK != ret)
    {
        EX_PRINTF("[%s:%d] Free frame fail \n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

extern "C" HI_S32 SVR_EXTRACTOR_Seek(HI_HANDLE handle, HI_S64 timeMs)
{
    status_t ret;
    EXTRACTOR_MEMBER_S *phandle = (EXTRACTOR_MEMBER_S*)handle;

    if (NULL == phandle || NULL == phandle->extractor)
    {
        return HI_FAILURE;
    }

    ret = phandle->extractor->seekTo(timeMs * 1000);

    if (OK != ret)
    {
        EX_PRINTF("[%s:%d] Seek frame fail \n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

extern "C" HI_S32 SVR_EXTRACTOR_Delete(HI_HANDLE handle)
{
    EXTRACTOR_MEMBER_S *phandle = (EXTRACTOR_MEMBER_S*)handle;

    if (NULL == phandle)
    {
        EX_PRINTF("[%s:%d] invalid param, return", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    if (NULL != phandle->extractor)
    {
        phandle->extractor->reset();
        delete phandle->extractor;
        phandle->extractor = NULL;
    }

    free(phandle);
    phandle = NULL;

    return HI_SUCCESS;
}

}  // namespace android
