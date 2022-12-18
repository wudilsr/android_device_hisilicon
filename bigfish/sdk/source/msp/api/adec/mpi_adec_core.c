/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : mpi_adec.c
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

#include "hi_debug.h"
#include "hi_error_mpi.h"
#include "hi_unf_sound.h"
#include "hi_drv_adec.h"
#include "hi_module.h"
#include "hi_common.h"
#include "hi_mpi_mem.h"
#include "hi_mpi_adec_core.h"
#include "mpi_adec_assembly.h"
#include "mpi_adec_waveform.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

static pthread_mutex_t   g_AdecApiMutex[ADEC_INSTANCE_MAXNUM] = {PTHREAD_MUTEX_INITIALIZER};
static pthread_mutex_t   g_AdecDataMutex[ADEC_INSTANCE_MAXNUM] = {PTHREAD_MUTEX_INITIALIZER};
static pthread_mutex_t   g_AdecIOMutex[ADEC_INSTANCE_MAXNUM] = {PTHREAD_MUTEX_INITIALIZER};


static HI_BOOL g_bAdecInit = HI_FALSE;
static ADEC_CHAN_S* g_pstAdecChan [ADEC_INSTANCE_MAXNUM];
extern HI_S32 ADEC_RegisterDeoderImple(const HI_CHAR *pszCodecDllName, HI_U32 u32Length);
extern HI_S32 ADEC_InitDecoderImple(ADEC_INFO_S* pstAecAttr );
extern HI_S32 ADEC_FindSupportDecoderImple(HA_FORMAT_E enFormat, HI_U32* penDstCodecID);
extern HI_HA_DECODE_S* ADEC_FindHaDecoderImple(HI_U32 enCodecID);

#ifdef HI_ADEC_AUDSPECTRUM_SUPPORT

#define WAVEFORM_CALC_DIFFTIME 300     /* unit:ms */

HI_S16 PcmDataCurrent[2 * 1024];
HI_U32 ChannelsCurrent = 0;
HI_S16 WaveFormPcmDelayLine[2 * 1024];  /* waveform need at least 1024 sample data; frame length defined in mp3 layer1 is 384 */
HI_S32 WaveFormPcmDelayLineSmps = 0;
HI_S32 WaveFormPcmTaltalSample = 0;

#define ADEC_AUD_MAX_CHANNELS 2
#define ADEC_MAX_AO_SRC_FRAC (48000 / 8000)
#define ADEC_AUD_MAX_SMAPLEPERFRAME (2048)
#define ADEC_MAX_AO_OUT_SAMPLE_PERFRAME (((ADEC_AUD_MAX_SMAPLEPERFRAME * ADEC_MAX_AO_SRC_FRAC) * 12) / 10)

static HI_U32* g_pu32Bufffer[ADEC_INSTANCE_MAXNUM];
#endif

#if 0//def HA_AUDIO_STATIC_LINK_MODE
extern HI_HA_DECODE_S g_ha_audio_ac3_decode_entry;
extern HI_HA_DECODE_S g_ha_audio_aac_decode_entry;
extern HI_HA_DECODE_S g_ha_audio_wma_decode_entry;
extern HI_HA_DECODE_S g_ha_audio_pcm_decode_entry;
extern HI_HA_DECODE_S g_ha_audio_mp3_decode_entry;
static HI_HA_DECODE_S* ADECFindHaDecoder(HI_U32 enCodecID)
{
    switch (enCodecID)
    {
        case HA_AUDIO_ID_AAC:
        {
            return &g_ha_audio_aac_decode_entry;
        }
        case HA_AUDIO_ID_MP2:
        case HA_AUDIO_ID_MP3:
        {
            return &g_ha_audio_mp3_decode_entry;
        }
        case HA_AUDIO_ID_PCM:
        {
            return &g_ha_audio_pcm_decode_entry;
        }
        case HA_AUDIO_ID_WMA9STD:
        {
            return &g_ha_audio_wma_decode_entry;
        }
        default:
        {
            return HI_NULL;
        }
    }
}

HI_S32 ADEC_RegisterDeoder(const HI_CHAR* pszDecoderDllName, HI_U32 u32Length)
{
    return HI_SUCCESS;
}

#else
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <dirent.h>
#include "hi_audio_codec.h"

#define MAXNAMESIZE 128
#define MAX_HA_DECODER 64

 HI_HA_DECODE_S* g_hFirstDecoder = HI_NULL;

/** size for the array of allocated components.  Sets the maximum
 * number of components that can be allocated at once */

/* decoder management */







static HI_S32 ADECRegisterHaDeoder(const HI_CHAR* pszDecoderDllName, HI_U32 u32Length)
{
    return ADEC_RegisterDeoderImple(pszDecoderDllName, u32Length);

}

static HI_VOID ADECSetVolume(ADEC_CHAN_S* pstAdecChan, HI_U32 u32Volume)
{
    pstAdecChan->u32Volume = u32Volume;
    pstAdecChan->pstAdecInfo->u32Volume = u32Volume;
    pstAdecChan->s16VolumeFrac = (HI_S16)((u32Volume * 0x7fffL) / ADEC_MAX_VOLUME);
    return;
}

static HI_VOID  ADECCheckScrambler(HI_HANDLE hAdec, HI_S32 s32BsConsumeBytes)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;
    HI_S32 mute = 0;

    pstAdecChan = g_pstAdecChan[hAdec];
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    if (pstAdecInfo->u32LastCorrectFrameNum == pstAdecInfo->u32FramnNm)
    {
        pstAdecInfo->u32FrameConsumedBytes += s32BsConsumeBytes;

        /* mute the adec if the frame comsumed bytes more than ADEC_MAX_FRAME_CONSUME_THD */
        if (pstAdecInfo->u32FrameConsumedBytes > ADEC_MAX_FRAME_CONSUME_THD)
        {
            mute = 1;
        }
    }
    else
    {
        if ((pstAdecInfo->u32LastCorrectFrameNum + 1) == pstAdecInfo->u32FramnNm)
        {
            if ((pstAdecInfo->u32FrameConsumedBytes + s32BsConsumeBytes) > ADEC_MAX_FRAME_CONSUME_THD)
            {
                mute = 1;
            }
            else
            {
                mute = 0;
            }
        }
        else
        {
            mute = 0;
        }

        /* detect angin */
        pstAdecInfo->u32LastCorrectFrameNum = pstAdecInfo->u32FramnNm;
        pstAdecInfo->u32FrameConsumedBytes = 0;
    }

    /* should not invoke ADEC_SetVolume */
    if (mute)
    {
        ADECSetVolume(pstAdecChan, 0);
    }
    else
    {
        ADECSetVolume(pstAdecChan, 100);
    }
}

#if 0
static HI_VOID ADECUnRegisterHaDeoderAll()
{
    HI_HA_DECODE_S* p, *pNext;

    p = g_hFirstDecoder;
    while (p)
    {
        HI_S32 dlok;
        pNext = p->pstNext;
        HI_INFO_ADEC ("\n##### HA_UnRegisterDeoder %s Decoder  #####\n", (HI_CHAR*)(p->szName));
        dlok = dlclose(p->pDllModule);
        if (dlok)
        {
            HI_WARN_ADEC ( "dlclose fali \n");
        }

        p = pNext;
    }

    g_hFirstDecoder = HI_NULL;
}

#endif

HI_S32 ADEC_RegisterDeoder(const HI_CHAR* pszDecoderDllName, HI_U32 u32Length)
{
    CHECK_ADEC_NULL_PTR(pszDecoderDllName);

    return ADECRegisterHaDeoder(pszDecoderDllName, u32Length);
}

HI_S32 ADEC_FoundSupportDeoder(HA_FORMAT_E enFormat, HI_U32* penDstCodecID)
{
    HI_S32 sRet;


    sRet = ADEC_FindSupportDecoderImple(enFormat, penDstCodecID);    
 
    return sRet;


}

HI_S32 ADEC_SetConfigDeoder( const HI_U32 enDstCodecID, HI_VOID* pstConfigStructure)
{
    HI_HA_DECODE_S* pHaDev;
    HI_S32 sRet = HI_SUCCESS;

    CHECK_ADEC_NULL_PTR(pstConfigStructure);

    pHaDev = ADEC_FindHaDecoderImple(enDstCodecID);
    if (pHaDev)
    {
        if (pHaDev->DecSetConfig)
        {
            sRet = (HI_S32)pHaDev->DecSetConfig(NULL, pstConfigStructure);
            if (HA_ErrorNone == sRet)
            {
                return HI_SUCCESS;
            }
            else
            {
                HI_INFO_ADEC ( " DecSetConfig Fail (sRet=0x%x)  \n", sRet);
                return HI_FAILURE;
            }
        }
    }
    else
    {
        HI_ERR_ADEC ( " ADEC_FindHaDecoderImple Fail (u32CodecID=0x%x)  \n", enDstCodecID);
        return HI_FAILURE;
    }

    return sRet;
}

#endif

#ifdef HA_HW_CODEC_SUPPORT
static HI_S32 ADECHwOutbufInit( ADEC_CHAN_S* pstAdecChan, HI_U32 uMaxBufSizePerFrame);
static HI_S32 ADECHwOutbufDeInit(ADEC_CHAN_S* pstAdecChan, ADEC_STREAM_OUTBUF_S*  pstOutBuf);
static HI_S32 ADECHwInbufInit( ADEC_CHAN_S* pstAdecChan);
static HI_S32 ADECHwInbufDeInit(ADEC_CHAN_S* pstAdecChan, ADEC_STREAM_BUFFER_S*  pstInBuf);
static HI_S32 ADECHwGetBuffer( ADEC_CHAN_S* pstAdecChan, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream1,
                               HI_UNF_STREAM_BUF_S* pstStream2);
static HI_S32 ADECHwPutBuffer( ADEC_CHAN_S* pstAdecChan, const HI_UNF_STREAM_BUF_S* pstStream1,
                               const HI_UNF_STREAM_BUF_S* pstStream2);
static HI_S32 ADECHwReceiveFrame( ADEC_CHAN_S* pstAdecChan, HI_UNF_AO_FRAMEINFO_S* pstAOFrame,
                                  ADEC_EXTFRAMEINFO_S* pstExtInfo);

static HI_VOID ADECHwReleaseFrame( ADEC_CHAN_S* pstAdecChan, HI_U32 u32FrameIndex);
static HI_VOID ADECHwDecode( ADEC_CHAN_S* pstAdecChan);
static HI_VOID ADECHwGetStatusInfo( ADEC_CHAN_S* pstAdecChan, HI_HA_STATUS_INFO_S* pstStatusInfo);
static HI_U32 ADECHwGetOutbufFrameNum(ADEC_CHAN_S* pstAdecChan, HI_HA_STATUS_INFO_S* pstStatusInfo);
#endif


static HI_S32 ADECGetDefalutOpenParam(ADEC_ATTR_S* pstDfOpenParam)
{
    HI_S32 i;
    HI_HADECODE_OPENPARAM_S*    pOpenPram;              /* HI_UNF_ACODEC_TYPE_VENDOR_SPECIAL */

    CHECK_ADEC_NULL_PTR(pstDfOpenParam);

    pOpenPram = &(pstDfOpenParam->sOpenPram);
    pstDfOpenParam->bEnable      = HI_FALSE;
    pstDfOpenParam->bEosState    = HI_FALSE;
    pstDfOpenParam->u32CodecID   = 0xFFFFFFFF;
    pstDfOpenParam->u32InBufSize = ADEC_DEFAULT_INPUT_BUFFER_SIZE;

    pstDfOpenParam->u32OutBufNum = ADEC_DEFAULT_WORKINGBUF_NUM;

    pOpenPram->enDecMode = HD_DEC_MODE_RAWPCM;
    pOpenPram->pCodecPrivateData = HI_NULL;
    pOpenPram->u32CodecPrivateDataSize = 0;
    pOpenPram->sPcmformat.u32DesiredOutChannels = 2;
    pOpenPram->sPcmformat.bInterleaved = HI_FALSE;
    pOpenPram->sPcmformat.u32BitPerSample = 16;
    pOpenPram->sPcmformat.u32DesiredSampleRate = 48000;
    for (i = 0; i < HA_AUDIO_MAXCHANNELS; i++)
    {
        pOpenPram->sPcmformat.enChannelMapping[i] = HA_AUDIO_ChannelNone;
    }

    return HI_SUCCESS;
}

static HI_S32 ADECInitInBuf(ADEC_CHAN_S* pstAdecChan, ADEC_STREAM_BUFFER_S*  pstInBuf, HI_U32 u32PaddingSize,
                            HI_U32 u32AdecChID)
{
    CHECK_ADEC_NULL_PTR(pstInBuf);

    if ((pstInBuf->u32BufSize < ADEC_MIN_INPUT_BUFFER_SIZE) || (pstInBuf->u32BufSize > ADEC_MAX_INPUT_BUFFER_SIZE))
    {
        HI_ERR_ADEC(" invalid input buffer size(%d) minsize(%d) maxsize(%d)!\n", pstInBuf->u32BufSize,
                    ADEC_MIN_INPUT_BUFFER_SIZE, ADEC_MAX_INPUT_BUFFER_SIZE);
        return HI_FAILURE;
    }


#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        if (HI_SUCCESS != ADECHwInbufInit(pstAdecChan))
        {
            HI_ERR_ADEC("ADECHwInbufInit fail\n");
            return HI_FAILURE;
        }
    }
    else
#endif
    {
        /* Read buffer size */
        pstInBuf->u32BufFree = pstInBuf->u32BufSize;
        pstInBuf->s32BufReadPos  = 0;
        pstInBuf->u32BufWritePos = 0;
        pstInBuf->u32StreamWritePos = 0;
        pstInBuf->u32Boundary = pstInBuf->u32BufSize;
        while (pstInBuf->u32Boundary * 2 <= (ADEC_PTS_BOUNDARY_SIZE - pstInBuf->u32BufSize))
        {
            pstInBuf->u32Boundary *= 2;
        }

        pstInBuf->u32BufPaddingSize = u32PaddingSize;
#ifdef ADEC_MMZ_INBUF_SUPPORT

        snprintf(pstInBuf->sAdecInMMzBuf.bufname, sizeof(pstInBuf->sAdecInMMzBuf.bufname), "ADEC_InBuf%d", u32AdecChID);

        pstInBuf->sAdecInMMzBuf.bufsize = (pstInBuf->u32BufSize + u32PaddingSize) * sizeof(HI_U8);
        pstInBuf->sAdecInMMzBuf.phyaddr = (HI_U32)HI_MMZ_New(pstInBuf->sAdecInMMzBuf.bufsize, 0x32, HI_NULL,
                                          pstInBuf->sAdecInMMzBuf.bufname);
        if (pstInBuf->sAdecInMMzBuf.phyaddr)
        {
            HI_U32 cache = 1;
            pstInBuf->sAdecInMMzBuf.user_viraddr = (HI_U8*)HI_MMZ_Map(pstInBuf->sAdecInMMzBuf.phyaddr, cache);
            pstInBuf->pu8Data = pstInBuf->sAdecInMMzBuf.user_viraddr;
        }
        else
        {
            pstInBuf->pu8Data = HI_NULL_PTR;
        }

#else
        pstInBuf->pu8Data = (HI_U8*)HI_MALLOC(HI_ID_ADEC, (pstInBuf->u32BufSize + u32PaddingSize) * sizeof(HI_U8));
#endif
        if (HI_NULL_PTR == pstInBuf->pu8Data)
        {
            HI_FATAL_ADEC("adec HI_MALLOC error\n");
            return HI_FAILURE;
        }

        pstInBuf->pu8Data += u32PaddingSize;
    }

    return HI_SUCCESS;
}

static HI_S32 ADECGetBsByteLefts(ADEC_STREAM_BUFFER_S* pstInBuf, HI_U32* pTotalBytes)
{
    HI_S32 s32BsBytes = 0;

    if (pstInBuf->s32BufReadPos <= (HI_S32)pstInBuf->u32BufWritePos)
    {
        s32BsBytes = (pstInBuf->u32BufWritePos - pstInBuf->s32BufReadPos);
    }
    else
    {
        s32BsBytes = (pstInBuf->u32BufSize - pstInBuf->s32BufReadPos) + pstInBuf->u32BufWritePos;
    }

    *pTotalBytes = s32BsBytes;
    return HI_SUCCESS;
}

static HI_VOID ADECUpdateBsReadPos(ADEC_STREAM_BUFFER_S* pstInBuf, HI_U32 u32ConsumeBytes)
{
    pstInBuf->s32BufReadPos += u32ConsumeBytes;
    if (pstInBuf->s32BufReadPos >= (HI_S32)pstInBuf->u32BufSize)
    {
        pstInBuf->s32BufReadPos -= pstInBuf->u32BufSize;
    }

    pstInBuf->u32BufFree += u32ConsumeBytes;

    return;
}

static HI_VOID ADECUpdateBsWrap(ADEC_STREAM_BUFFER_S* pstInBuf)
{
    /*deal with buffer wrap, only at last little data */
    if ((HI_S32)pstInBuf->u32BufWritePos < pstInBuf->s32BufReadPos)
    {
        HI_S32 s32WrapBytes;

        /* deal with loop, (warning: codec can't comsume over s32PaddingSize */
        s32WrapBytes = (HI_S32)(pstInBuf->u32BufSize) - pstInBuf->s32BufReadPos;
        if ((HI_U32)s32WrapBytes <= pstInBuf->u32BufPaddingSize)
        {
            memcpy(pstInBuf->pu8Data - s32WrapBytes, pstInBuf->pu8Data + pstInBuf->s32BufReadPos,
                   (HI_U32)s32WrapBytes);
            pstInBuf->s32BufReadPos = -s32WrapBytes;
        }
    }
}

static HI_VOID ADECDeInitInBuf(ADEC_CHAN_S* pstAdecChan, ADEC_STREAM_BUFFER_S*  pstInBuf )
{
    CHECK_NULL_PTR_NORET(pstInBuf);

    if (HI_NULL_PTR != pstInBuf->pu8Data)
    {
#ifdef HA_HW_CODEC_SUPPORT
        if (HI_TRUE == pstAdecChan->bHwDecoder)
        {
            if (HI_SUCCESS != ADECHwInbufDeInit(pstAdecChan, pstInBuf))
            {
                HI_ERR_ADEC("ADECHwInbufDeInit fail\n");
                return;
            }
        }
        else
#endif
        {
#ifdef ADEC_MMZ_INBUF_SUPPORT
            (HI_VOID) HI_MMZ_Unmap(pstInBuf->sAdecInMMzBuf.phyaddr);
            (HI_VOID)HI_MMZ_Delete(pstInBuf->sAdecInMMzBuf.phyaddr);
#else
            HI_FREE(HI_ID_ADEC, pstInBuf->pu8Data - pstInBuf->u32BufPaddingSize);
#endif
            pstInBuf->pu8Data = HI_NULL_PTR;
        }
    }

    pstInBuf->u32BufFree = 0;
    pstInBuf->s32BufReadPos  = 0;
    pstInBuf->u32BufWritePos = 0;
    pstInBuf->u32StreamWritePos = 0;
    pstInBuf->u32BufPaddingSize = 0;
    return;
}

static HI_VOID ADECResetInBuf(ADEC_STREAM_BUFFER_S*  pstInBuf )
{
    CHECK_NULL_PTR_NORET(pstInBuf);
    CHECK_NULL_PTR_NORET(pstInBuf->pu8Data);

    /* Read buffer size */
    pstInBuf->u32BufFree = pstInBuf->u32BufSize;
    pstInBuf->s32BufReadPos  = 0;
    pstInBuf->u32BufWritePos = 0;
    return;
}

static HI_U32 ADECGetMaxOutBufSize(ADEC_CHAN_S* pstAdecChan)
{
    HI_U32 u32BitSize = 0, u32PcmSize = 0;
    HI_HA_DECODE_S* pHaDev;
    HI_S32 nRet;

    u32PcmSize = 0;
    u32BitSize = 0;
    pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
    if (pHaDev->DecGetMaxPcmOutSize)
    {
        nRet = pHaDev->DecGetMaxPcmOutSize(pstAdecChan->decAttr.hDecoder, &u32PcmSize);
        if (HA_ErrorNone != nRet)    /* Success */
        {
            return 0;
        }
    }

    if (pHaDev->DecGetMaxBitsOutSize)
    {
        nRet = pHaDev->DecGetMaxBitsOutSize(pstAdecChan->decAttr.hDecoder, &u32BitSize);
        if (HA_ErrorNone != nRet)/* Success */
        {
            return 0;
        }
    }

    return (HI_U32)(u32BitSize + u32PcmSize);
}

static HI_S32 ADECInitOutBuf(ADEC_CHAN_S* pstAdecChan, ADEC_STREAM_OUTBUF_S*  pstOutBuf, HI_U32 uMaxBufSizePerFrame,
                             HI_U32 u32AdecChID)
{
    HI_U32 i;
    HI_U32* pu32Buf;

    CHECK_ADEC_NULL_PTR(pstOutBuf);
    CHECK_ADEC_OUTBUF_NUMBER(pstOutBuf->u32OutBufNum);

#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        if (HI_SUCCESS != ADECHwOutbufInit(pstAdecChan, uMaxBufSizePerFrame))
        {
            HI_ERR_ADEC("ADECHwOutbufInit fail\n");
            return HI_FAILURE;
        }
    }
    else
#endif

    {
        /* Allocate OutBuffer */
#ifdef ADEC_MMZ_OUTBUF_SUPPORT

        snprintf(pstOutBuf->sAdecOutMMzBuf.bufname, sizeof(pstOutBuf->sAdecOutMMzBuf.bufname), "ADEC_OutBuf%d", u32AdecChID);

        pstOutBuf->sAdecOutMMzBuf.bufsize = (pstOutBuf->u32OutBufNum * uMaxBufSizePerFrame);
        pstOutBuf->sAdecOutMMzBuf.phyaddr = (HI_U32)HI_MMZ_New(pstOutBuf->sAdecOutMMzBuf.bufsize, 0x32, HI_NULL,
                                            pstOutBuf->sAdecOutMMzBuf.bufname);
        if (pstOutBuf->sAdecOutMMzBuf.phyaddr)
        {
            pu32Buf = (HI_U32*)HI_MMZ_Map(pstOutBuf->sAdecOutMMzBuf.phyaddr, 1);
            pstOutBuf->sAdecOutMMzBuf.user_viraddr = (HI_U8*)pu32Buf;
        }
        else
        {
            pu32Buf = HI_NULL_PTR;
        }

#else
        pu32Buf = (HI_U32*)HI_MALLOC(HI_ID_ADEC, pstOutBuf->u32OutBufNum * uMaxBufSizePerFrame);
#endif

        if (HI_NULL_PTR == pu32Buf)
        {
            HI_FATAL_ADEC("adec HI_MALLOC error\n");
            return HI_FAILURE;
        }
        /* assigning buffer */
        for (i = 0; i < pstOutBuf->u32OutBufNum; i++)
        {
            pstOutBuf->outBuf[i].OutBuf = (HI_U32*)(((HI_U32)pu32Buf) + i * uMaxBufSizePerFrame);    /* only for sw decder */
            pstOutBuf->outBuf[i].bFlag = HI_FALSE;
        }

        /* Reset output buffer pointer */
        pstOutBuf->pu32BaseAddr   = (HI_U32*)pu32Buf;
        pstOutBuf->u32BufReadIdx  = 0;
        pstOutBuf->u32BufWriteIdx = 0;
    }

    return HI_SUCCESS;
}

static HI_VOID ADECDeInitOutBuf(ADEC_CHAN_S* pstAdecChan, ADEC_STREAM_OUTBUF_S*  pstOutBuf )
{
    HI_U32 i;

    CHECK_NULL_PTR_NORET(pstOutBuf);

    if (HI_NULL_PTR != pstOutBuf->pu32BaseAddr)
    {
#ifdef HA_HW_CODEC_SUPPORT
        if (HI_TRUE == pstAdecChan->bHwDecoder)
        {
            if (HI_SUCCESS != ADECHwOutbufDeInit(pstAdecChan, pstOutBuf))
            {
                HI_ERR_ADEC("ADECHwOutbufDeInit fail\n");
                return;
            }
        }
        else
#endif
        {
#ifdef ADEC_MMZ_OUTBUF_SUPPORT
            (HI_VOID) HI_MMZ_Unmap(pstOutBuf->sAdecOutMMzBuf.phyaddr);
            (HI_VOID)HI_MMZ_Delete(pstOutBuf->sAdecOutMMzBuf.phyaddr);
#else
            HI_FREE(HI_ID_ADEC, pstOutBuf->pu32BaseAddr);
#endif
        }

        pstOutBuf->pu32BaseAddr = 0;
    }

    for (i = 0; i < pstOutBuf->u32OutBufNum; i++)
    {
        pstOutBuf->outBuf[i].OutBuf = HI_NULL_PTR;
        pstOutBuf->outBuf[i].bFlag = HI_FALSE;
    }

    pstOutBuf->u32BufReadIdx  = 0;
    pstOutBuf->u32BufWriteIdx = 0;
    return;
}

static HI_VOID ADECResetOutBuf(ADEC_STREAM_OUTBUF_S*  pstOutBuf, HI_U32 uMaxBufSizePerFrame )
{
    HI_U32 i;
    HI_S32* ps32Buf;

    CHECK_NULL_PTR_NORET(pstOutBuf);
    CHECK_ADEC_OUTBUF_NUMBER_NORET(pstOutBuf->u32OutBufNum);
    CHECK_NULL_PTR_NORET(pstOutBuf->pu32BaseAddr);

    // Assigning output buffer
    ps32Buf = (HI_S32*)(pstOutBuf->pu32BaseAddr);
    for (i = 0; i < pstOutBuf->u32OutBufNum; i++)
    {
        pstOutBuf->outBuf[i].OutBuf = (HI_U32*)(ps32Buf + i * (uMaxBufSizePerFrame / sizeof(HI_S32)));
        pstOutBuf->outBuf[i].bFlag = HI_FALSE;
    }

    /* Reset output buffer pointer */
    pstOutBuf->u32BufReadIdx  = 0;
    pstOutBuf->u32BufWriteIdx = 0;
    return;
}

static HI_VOID ADECResetMidState(ADEC_MIDSTATE_S*  pstMidState)
{
    CHECK_NULL_PTR_NORET(pstMidState);

    pstMidState->u32ContinueErrNum = 0;
    pstMidState->u32LastFrameChannels  = 2;
    pstMidState->enLastFrameSmaplerate = HI_UNF_SAMPLE_RATE_48K;

    //memset(pstMidState->lastPkt, 0, sizeof(HI_UNF_STREAM_BUF_S)*2);
}

static HI_VOID ADECRestPTSQuet(ADEC_PTS_QUE_S* pstPTSQue)
{
    CHECK_NULL_PTR_NORET(pstPTSQue);

    memset(pstPTSQue->tPTSArry, 0, sizeof(ADEC_PTS) * ADEC_MAX_STORED_PTS_NUM);
    pstPTSQue->ulPTSread    = 0;
    pstPTSQue->ulPTSwrite   = 0;
    pstPTSQue->u32LastPtsMs = (HI_U32) - 1;
    pstPTSQue->u32LastStorePtsMs    = (HI_U32) - 1;
    pstPTSQue->u32PtsBeforeRevise   = 0;
    pstPTSQue->u32RecycleFirstPtsMs = 0;
    pstPTSQue->u32RecyleStorePtsMs  = 0;
    return;
}

static HI_VOID ADECRestPacketQuet(ADEC_PACKET_QUE_S* pstQue)
{
    if (!pstQue)
    {
        return;
    }

    memset(pstQue->tPacketArry, 0, sizeof(ADEC_PACKET) * ADEC_MAX_STORED_PACKET_NUM);
    pstQue->ulPacketRead  = 0;
    pstQue->ulPacketwrite = 0;
    return;
}

static HI_BOOL ADECIsPTSFull(ADEC_PTS_QUE_S* pstPTSQue)
{
    if (((pstPTSQue->ulPTSwrite + 1) % ADEC_MAX_STORED_PTS_NUM) == pstPTSQue->ulPTSread)
    {
#if 0
        /* pstPTSQue is full , discard oldest pts */
        pstPTSQue->ulPTSread = (pstPTSQue->ulPTSread + 1) % ADEC_MAX_STORED_PTS_NUM;
        return HI_FALSE;
#else
        return HI_TRUE;
#endif
    }

    return HI_FALSE;
}

/* call at sw decoder only */
static HI_U32 ADECGetStreamReadPos(ADEC_STREAM_BUFFER_S* pstInBuf)
{
    HI_U32 u32BsBytes = 0, u32ReadPos = 0;

    ADECGetBsByteLefts(pstInBuf, &u32BsBytes);

    if (pstInBuf->u32StreamWritePos >= u32BsBytes)
    {
        u32ReadPos = pstInBuf->u32StreamWritePos - u32BsBytes;
    }
    else
    {
        u32ReadPos = pstInBuf->u32Boundary + pstInBuf->u32StreamWritePos - u32BsBytes;
    }

    return u32ReadPos;
}

/* call at sw decoder only */
static HI_U32 ADECFixStreamReadPos(ADEC_CHAN_S* pstAdecChan, HI_U32 u32StreamReadPos, HI_U32 u32BackwardBytes)
{
    HI_U32 u32FixStreamReadPos;
    ADEC_STREAM_BUFFER_S*  pstInBuf = &(pstAdecChan->InStreamBuf);

    u32FixStreamReadPos = u32StreamReadPos - u32BackwardBytes;
    if (u32FixStreamReadPos >= pstInBuf->u32Boundary)
    {
        u32FixStreamReadPos -= pstInBuf->u32Boundary;
    }

    return u32FixStreamReadPos;
}

/****************************************************************************
 * Function:    ADECFindPTS
 *
 * Description: try to find current frame u32PtsMs
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
static HI_U32 ADECFindPTS(ADEC_PTS_QUE_S* pstPTSQue, HI_U32 u32Pos, HI_U32 u32PcmOutSamplesPerFrame,
                          HI_U32 u32OutSampleRate, HI_U32* pu32OrgPTS)
{
    HI_U32 u32PtsMs;
    HI_U32 Pos, FoundPtsPos = (HI_U32) - 1;
    HI_U32 rdPos;
    HI_U32 wtPos;
    ADEC_PTS* ptPTS = HI_NULL;

    rdPos = (HI_U32)pstPTSQue->ulPTSread;
    wtPos = (HI_U32)pstPTSQue->ulPTSwrite;
    ptPTS = pstPTSQue->tPTSArry;

    for (Pos = rdPos; Pos != wtPos;  Pos = (Pos + 1) % ADEC_MAX_STORED_PTS_NUM)
    {
        if (ptPTS[Pos].u32BegPos < ptPTS[Pos].u32EndPos)
        {
            if ((ptPTS[Pos].u32BegPos <= u32Pos) && (ptPTS[Pos].u32EndPos > u32Pos))
            {
                FoundPtsPos = ptPTS[Pos].u32PtsMs;
                break;
            }
        }
        else
        {
            if ((ptPTS[Pos].u32BegPos <= u32Pos) || (ptPTS[Pos].u32EndPos > u32Pos))
            {
                FoundPtsPos = ptPTS[Pos].u32PtsMs;
                break;
            }
        }
    }
    if (u32PcmOutSamplesPerFrame & 0xffff0000)
    {
        u32PcmOutSamplesPerFrame = u32PcmOutSamplesPerFrame & 0xffff;
    }
    if (((HI_U32) - 1) == FoundPtsPos)
    {
        /*can not find a valid PTS*/
        HI_U32 u32Delta;
        u32Delta = (u32PcmOutSamplesPerFrame * 1000) / u32OutSampleRate;
        if (((HI_U32) - 1) != pstPTSQue->u32LastPtsMs)
        {
            u32PtsMs = pstPTSQue->u32LastPtsMs + u32Delta;
            if (((HI_U32) - 1) == u32PtsMs)
            {
                u32PtsMs = 0;
            }                      /* avoid loop*/
            pstPTSQue->u32LastPtsMs = u32PtsMs;
        }
        else
        {
            u32PtsMs = (HI_U32) - 1;   /* if the PTS of first Frame isnot valid, dont insert the PTS*/
        }

        if (Pos != wtPos)
        {
            /* Found a invalid PTS */
            pstPTSQue->ulPTSread = (HI_U32)Pos;
        }
    }
    else
    {
        /* Found a valid PTS */
        u32PtsMs = FoundPtsPos;
        ptPTS[Pos].u32PtsMs  = (HI_U32)(-1);
        pstPTSQue->ulPTSread = (HI_U32)Pos;
        pstPTSQue->u32LastPtsMs = u32PtsMs;
    }

    *pu32OrgPTS = FoundPtsPos;
    pstPTSQue->u32LastPtsMs = u32PtsMs;
    return u32PtsMs;
}

static HI_VOID ADECDiscardPTS(ADEC_PTS_QUE_S* pstPTSQue, HI_U32 u32Pos)
{
    HI_U32 Pos;//, FoundPtsPos = (HI_U32)-1;
    HI_U32 rdPos;
    HI_U32 wtPos;
    ADEC_PTS* ptPTS = HI_NULL;

    rdPos = (HI_U32)pstPTSQue->ulPTSread;
    wtPos = (HI_U32)pstPTSQue->ulPTSwrite;
    ptPTS = pstPTSQue->tPTSArry;
    for (Pos = rdPos; Pos != wtPos;  Pos = (Pos + 1) % ADEC_MAX_STORED_PTS_NUM)
    {
        if (ptPTS[Pos].u32BegPos < ptPTS[Pos].u32EndPos)
        {
            if ((ptPTS[Pos].u32BegPos <= u32Pos) && (ptPTS[Pos].u32EndPos > u32Pos))
            {
                break;
            }
        }
        else
        {
            if ((ptPTS[Pos].u32BegPos <= u32Pos) || (ptPTS[Pos].u32EndPos > u32Pos))
            {
                break;
            }
        }
    }

    pstPTSQue->ulPTSread = (HI_U32)Pos;
}
static HI_VOID ADECSetPacketEosFlag (ADEC_CHAN_S* pstAdecChan)
{
    ADEC_PACKET_QUE_S*   pstPacketQue = HI_NULL_PTR;

    pstPacketQue = (pstAdecChan->pstPacketQue);

    pstPacketQue->tPacketArry[pstPacketQue->ulPacketwrite].bPacketEosFlag = HI_TRUE;
}

static HI_BOOL ADECIsPacketFull(ADEC_PACKET_QUE_S*   pstPacketQue)
{
#if 1
    HI_U32 u32Packetwrite = (pstPacketQue->ulPacketwrite + 1) % ADEC_MAX_STORED_PACKET_NUM;

    if (HI_TRUE == pstPacketQue->tPacketArry[u32Packetwrite].bPacketEosFlag)
    {
        return HI_TRUE;
    }
#else
    if (((pstPacketQue->ulPacketwrite + 1) % ADEC_MAX_STORED_PACKET_NUM) == pstPacketQue->ulPacketRead)
    {
        return HI_SUCCESS;
    }
#endif

    return HI_FALSE;
}

static HI_VOID ADECStorePacket (ADEC_CHAN_S* pstAdecChan, HI_U32 u32PtsMs, HI_U32 u32BsSize)
{
    ADEC_STREAM_BUFFER_S*  pstInBuf   = HI_NULL_PTR;
    ADEC_PACKET_QUE_S*   pstPacketQue = HI_NULL_PTR;
    HI_U32 u32PtsEosFlag, u32PtsWrite;

    pstPacketQue = (pstAdecChan->pstPacketQue);
    pstInBuf  = &(pstAdecChan->InStreamBuf);

    if (0xffffffff != u32PtsMs)
    {
        pstPacketQue->tPacketArry[pstPacketQue->ulPacketwrite].bPacketEosFlag =  HI_TRUE;//ulPacketwrite =0 is null
    }


    /* new pactet follow with a valid PTS */
    if (0xffffffff != u32PtsMs)
    {
        u32PtsWrite = (pstPacketQue->ulPacketwrite + 1) % ADEC_MAX_STORED_PACKET_NUM;
        u32PtsEosFlag = pstPacketQue->tPacketArry[u32PtsWrite].bPacketEosFlag;
        if (u32PtsEosFlag ==  HI_FALSE)
        {
            pstPacketQue->ulPacketwrite = (pstPacketQue->ulPacketwrite + 1) % ADEC_MAX_STORED_PACKET_NUM;
            pstPacketQue->tPacketArry[pstPacketQue->ulPacketwrite].bPacketEosFlag =  HI_FALSE;
            pstPacketQue->tPacketArry[pstPacketQue->ulPacketwrite].s32BegPos = (HI_U32)pstInBuf->u32BufWritePos;
            pstPacketQue->tPacketArry[pstPacketQue->ulPacketwrite].u32EndPos = (HI_U32)((HI_U32)pstInBuf->u32BufWritePos
                    + u32BsSize) % pstInBuf->u32BufSize;
        }
    }
    else
    {
        pstPacketQue->tPacketArry[pstPacketQue->ulPacketwrite].u32EndPos += u32BsSize;
        pstPacketQue->tPacketArry[pstPacketQue->ulPacketwrite].u32EndPos %= pstInBuf->u32BufSize;
    }
}

static HI_VOID ADECGetInputBuf(ADEC_CHAN_S* pstAdecChan, HI_HADECODE_INPACKET_S* pAvpkt)
{
    ADEC_STREAM_BUFFER_S*  pstInBuf   = HI_NULL_PTR;
    ADEC_PACKET_QUE_S*   pstPacketQue = HI_NULL_PTR;
    ADEC_PACKET* pstPacket;
    HI_S32 s32BsLeftBytes;

    pstInBuf = &(pstAdecChan->InStreamBuf);
    memset(pAvpkt, 0, sizeof(HI_HADECODE_INPACKET_S));

    if (HI_TRUE == pstAdecChan->bPacketDecoder)
    {
        pstPacketQue = (pstAdecChan->pstPacketQue);
        pstPacket = &pstPacketQue->tPacketArry[pstPacketQue->ulPacketRead];
        if (HI_TRUE == pstPacket->bPacketEosFlag)
        {
            /*deal with buffer wrap before decode at packet mode */
            if (pstPacket->s32BegPos > (HI_S32)pstPacket->u32EndPos)
            {
                ADECUpdateBsWrap(pstInBuf);
                pstPacket->s32BegPos = pstInBuf->s32BufReadPos;
            }

            pAvpkt->pu8Data = pstInBuf->pu8Data + pstInBuf->s32BufReadPos;
            pAvpkt->s32Size = (HI_S32)pstPacket->u32EndPos - pstInBuf->s32BufReadPos;
        }
    }
    else
    {
        /*get linear-buffer unread data length*/
        if ((HI_S32)pstInBuf->u32BufWritePos < pstInBuf->s32BufReadPos)
        {
            s32BsLeftBytes = (HI_S32)(pstInBuf->u32BufSize) - pstInBuf->s32BufReadPos;
        }
        else
        {
            s32BsLeftBytes = (HI_S32)(pstInBuf->u32BufWritePos - pstInBuf->s32BufReadPos);
        }

        pAvpkt->pu8Data = pstInBuf->pu8Data + pstInBuf->s32BufReadPos;
        pAvpkt->s32Size = s32BsLeftBytes;
    }

    return;
}

static HI_VOID ADECUpdateInputBuf(ADEC_CHAN_S* pstAdecChan, HI_U32 u32ConsumeBytes)
{
    ADEC_STREAM_BUFFER_S*  pstInBuf   = HI_NULL_PTR;
    ADEC_PACKET_QUE_S*   pstPacketQue = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;
    ADEC_PACKET* pstPacket;

    pstAdecInfo = pstAdecChan->pstAdecInfo;

    pstPacketQue = (pstAdecChan->pstPacketQue);
    pstInBuf  = &(pstAdecChan->InStreamBuf);
    pstPacket = &pstPacketQue->tPacketArry[pstPacketQue->ulPacketRead];

    if (HI_TRUE == pstAdecChan->bPacketDecoder)
    {
        if (HI_TRUE == pstPacket->bPacketEosFlag)
        {
            ADECUpdateBsReadPos(pstInBuf, u32ConsumeBytes);
            if (pstInBuf->s32BufReadPos == pstPacket->u32EndPos)
            {
                pstPacket->bPacketEosFlag  = HI_FALSE;
                pstPacketQue->ulPacketRead = (pstPacketQue->ulPacketRead + 1) % ADEC_MAX_STORED_PACKET_NUM;
                if (HI_TRUE == pstPacket->bPacketEosFlag)
                {
                    HI_ASSERT(pstInBuf->s32BufReadPos == pstPacket->s32BegPos);
                }
            }
        }
    }
    else
    {
        if (u32ConsumeBytes)
        {
            ADECUpdateBsReadPos(pstInBuf, u32ConsumeBytes);
        }
        else
        {
#ifdef HA_HW_CODEC_SUPPORT
            if (HI_TRUE != pstAdecChan->bHwDecoder)
#endif
            {
                /* only sw decoder need to wrap buffer */
                ADECUpdateBsWrap(pstInBuf);
            }
        }
    }

    //update intpu buf status
    pstAdecInfo->s32BufRead = pstInBuf->s32BufReadPos;
    return;
}


static HI_VOID ADECStorePTS (ADEC_PTS_QUE_S*   pstPTSQue, const ADEC_STREAM_BUFFER_S*  pstInBuf, HI_U32 u32PtsMs,
                             HI_U32 u32BsSize, HI_BOOL enFmt)
{

    ADEC_PTS* ptPTSArrayOpt = pstPTSQue->tPTSArry;

    if (0xffffffff != u32PtsMs)
    {
        if ((u32PtsMs == pstPTSQue->u32LastStorePtsMs))
        {
            u32PtsMs = 0xffffffff;
        }
    }

    /* make sure there are space to store */
    if (((0xffffffff) == u32PtsMs))
    {
        if (pstPTSQue->ulPTSwrite != 0)
        {
            ptPTSArrayOpt[pstPTSQue->ulPTSwrite
                          - 1].u32EndPos = (ptPTSArrayOpt[pstPTSQue->ulPTSwrite
                                            - 1].u32EndPos + u32BsSize) % pstInBuf->u32Boundary;
        }
        else
        {
            ptPTSArrayOpt[ADEC_MAX_STORED_PTS_NUM
                          - 1].u32EndPos = (ptPTSArrayOpt[ADEC_MAX_STORED_PTS_NUM
                                            - 1].u32EndPos + u32BsSize) % pstInBuf->u32Boundary;
        }
    }
    else  if (((pstPTSQue->ulPTSwrite + 1) % ADEC_MAX_STORED_PTS_NUM) != pstPTSQue->ulPTSread)
    {
        if (u32PtsMs < pstPTSQue->u32LastStorePtsMs)
        {
            if (pstPTSQue->u32LastStorePtsMs == 0xffffffff)
            {
                pstPTSQue->u32RecyleStorePtsMs = u32PtsMs;     //first pts
            }
            else
            {
                pstPTSQue->u32RecyleStorePtsMs = pstPTSQue->u32LastStorePtsMs;     //pts re-cycle
            }

            pstPTSQue->u32RecycleFirstPtsMs = u32PtsMs;
        }

        pstPTSQue->u32LastStorePtsMs = u32PtsMs;
        ptPTSArrayOpt[pstPTSQue->ulPTSwrite].u32PtsMs = u32PtsMs;
        ptPTSArrayOpt[pstPTSQue->ulPTSwrite].u32BegPos = (HI_U32)pstInBuf->u32StreamWritePos;
        ptPTSArrayOpt[pstPTSQue->ulPTSwrite].u32EndPos = (HI_U32)((HI_U32)pstInBuf->u32StreamWritePos
                + u32BsSize) % pstInBuf->u32Boundary;
        pstPTSQue->ulPTSwrite = (pstPTSQue->ulPTSwrite + 1) % ADEC_MAX_STORED_PTS_NUM;
    }
    else
    {
        HI_WARN_ADEC("Not enough PTS buffer, discard current PTS(%d)\n", u32PtsMs);
    }
}

static HI_S32 ADECGetStreamPTS(ADEC_CHAN_S* pstAdecChan, HI_S32* s32BufferBps, HI_U32* pInStreamPts)
{
    ADEC_PTS_QUE_S*   pstPTSQue = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf = HI_NULL_PTR;
    HI_U32 u32totalbytes = 0;
    HI_U32 u32PtsMs;

    pstPTSQue = &(pstAdecChan->PTSQue);
    pstInBuf = &(pstAdecChan->InStreamBuf);
    if (pstPTSQue->u32LastStorePtsMs == 0xffffffff)
    {
        u32PtsMs = 0;
        *pInStreamPts = u32PtsMs;
        return HI_SUCCESS;
    }

    if (pstPTSQue->u32LastPtsMs == 0xffffffff)
    {
        pstPTSQue->u32PtsBeforeRevise = pstPTSQue->u32LastStorePtsMs;
    }

    if (pstPTSQue->u32LastPtsMs < pstPTSQue->u32LastStorePtsMs)
    {
        u32PtsMs = (pstPTSQue->u32LastStorePtsMs - pstPTSQue->u32LastPtsMs);

        pstPTSQue->u32RecyleStorePtsMs	= 0;
        pstPTSQue->u32RecycleFirstPtsMs = 0;
        pstPTSQue->u32PtsBeforeRevise = pstPTSQue->u32LastPtsMs;

    }
    else if (pstPTSQue->u32LastStorePtsMs == pstPTSQue->u32LastPtsMs)
    {
        u32PtsMs = 0;
    }
    else
    {
        if ((pstPTSQue->u32RecyleStorePtsMs) && (pstPTSQue->u32LastPtsMs <= pstPTSQue->u32RecyleStorePtsMs))
        {
            u32PtsMs = (pstPTSQue->u32RecyleStorePtsMs
                        - pstPTSQue->u32LastPtsMs) + (pstPTSQue->u32LastStorePtsMs - pstPTSQue->u32RecycleFirstPtsMs); //pts re-cycle
            pstPTSQue->u32RecycleFirstPtsMs = pstPTSQue->u32LastStorePtsMs;
        }
        else if ((pstPTSQue->u32RecyleStorePtsMs) && (pstPTSQue->u32LastPtsMs > pstPTSQue->u32RecyleStorePtsMs))
        {
            u32PtsMs = (pstPTSQue->u32LastStorePtsMs - pstPTSQue->u32RecycleFirstPtsMs); //pts re-cycle and modify
            pstPTSQue->u32RecycleFirstPtsMs = pstPTSQue->u32LastStorePtsMs;

        }
        else
        {
            u32PtsMs = pstPTSQue->u32LastStorePtsMs - pstPTSQue->u32PtsBeforeRevise; //pts modify,currentpts = lastpts + delta
            pstPTSQue->u32PtsBeforeRevise = pstPTSQue->u32LastStorePtsMs;

        }

    }

    ADECGetBsByteLefts(pstInBuf, &u32totalbytes);
    if (u32PtsMs)
    {
        *s32BufferBps = (u32totalbytes * 1000) / (u32PtsMs);
    }
    else
    {
        *s32BufferBps = 0;
    }

    *pInStreamPts = u32PtsMs;
    return HI_SUCCESS;
}

static HI_VOID ADECGetFrameTime(HI_UNF_AO_FRAMEINFO_S* pstAOFrame, HI_U32* u32FrameDurationMs)
{
    if (pstAOFrame->u32SampleRate)
    {
        if (pstAOFrame->u32PcmSamplesPerFrame)
        {
            *u32FrameDurationMs = (pstAOFrame->u32PcmSamplesPerFrame
                                   * 1000) / ((HI_U32)pstAOFrame->u32SampleRate);
        }
        else
        {
            *u32FrameDurationMs = (((pstAOFrame->u32BitsBytesPerFrame
                                     & 0xffff)
                                    / (2 * sizeof(HI_U16))) * 1000) / ((HI_U32)pstAOFrame->u32SampleRate);
        }
    }
    else
    {
        *u32FrameDurationMs = 0;
    }

}

HI_VOID ADECGetOutbufDurationMs (ADEC_CHAN_S* pstAdecChan, HI_U32* pu32DurationMs)
{
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    ADEC_OUTPUTBUF_S* ptOutElem   = HI_NULL_PTR;
    HI_U32 u32BufReadIdx, u32BufWriteIdx;
    HI_U32 u32FrameDurationMs;
    HI_U32 u32OutBufDurationMs = 0;
    HI_U32 u32OutBufNum;
    HI_UNF_AO_FRAMEINFO_S stAOFrame;

    pstOutBuf   = &(pstAdecChan->outStreamBuf);

    *pu32DurationMs = 0;
    u32BufReadIdx = pstOutBuf->u32BufReadIdx;
    u32BufWriteIdx = pstOutBuf->u32BufWriteIdx;
    u32OutBufNum = pstOutBuf->u32OutBufNum;
    /* No data */
    while (u32OutBufNum--)
    {
        if (u32BufReadIdx == u32BufWriteIdx)
        {
            break;
        }
        ptOutElem = &(pstOutBuf->outBuf[u32BufReadIdx++]);
        /* fill frame info */
        stAOFrame.u32FrameIndex = pstOutBuf->u32BufReadIdx;
        stAOFrame.bInterleaved = ptOutElem->bInterleaved;
        stAOFrame.s32BitPerSample = (HI_S32)ptOutElem->u32BitPerSample;
        stAOFrame.u32SampleRate = ptOutElem->u32OutSampleRate;
        stAOFrame.u32Channels = ptOutElem->u32OutChannels;
        stAOFrame.u32PtsMs = ptOutElem->u32PTS;
        stAOFrame.u32PcmSamplesPerFrame = ptOutElem->u32PcmOutSamplesPerFrame;
        stAOFrame.u32BitsBytesPerFrame = ptOutElem->u32BitsOutBytesPerFrame;
        stAOFrame.ps32PcmBuffer  = ptOutElem->ps32PcmOutBuf;
        stAOFrame.ps32BitsBuffer = ptOutElem->ps32BitsOutBuf;
        ADECGetFrameTime(&stAOFrame, &u32FrameDurationMs);
        u32OutBufDurationMs += u32FrameDurationMs;

    }
    *pu32DurationMs = u32OutBufDurationMs;
    return ;
}
HI_S32 ADEC_GetDelayMs(HI_HANDLE hAdec, HI_U32* pDelayMs)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    HI_S32 s32BufferBps = 0;
    HI_S32 s32AvgStreamBps = 0;
    HI_U32 u32InStreamPts;
    HI_S32 S32DelayBps;
    HI_U32 u32TotalAdecTime;
    HI_U32 u32OutBufDurationMs;
#ifdef HA_HW_CODEC_SUPPORT
    HI_HA_STATUS_INFO_S stStatus;
    memset(&stStatus,0,sizeof(HI_HA_STATUS_INFO_S));
#endif
    pstAdecChan = g_pstAdecChan[hAdec];

    ADEC_LOCK(&g_AdecApiMutex[hAdec]);

    CHECK_ADEC_STATE(pstAdecChan->beAssigned, &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATE(pstAdecChan->beWork, &g_AdecApiMutex[hAdec]);

    
#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        ADECHwGetStatusInfo(pstAdecChan, &stStatus);
        pstAdecChan->InStreamBuf.s32BufReadPos = stStatus.u32InBufReadPos;
        pstAdecChan->InStreamBuf.u32BufWritePos = stStatus.u32InBufWritePos;
    }
#endif   

    ADECGetStreamPTS(pstAdecChan, &s32BufferBps, &u32InStreamPts);
    HI_SYS_GetTimeStampMs(&pstAdecChan->u32EndTime);

    u32TotalAdecTime = (pstAdecChan->u32EndTime - pstAdecChan->u32StartTime);
    if (u32TotalAdecTime > 0)
    {
        s32AvgStreamBps = ((( unsigned long long )pstAdecChan->u32TotalAdecInByte) * 1000) / (u32TotalAdecTime); //unit is Bps
    }
    else
    {
        s32AvgStreamBps = 0;
    }

    if (!s32BufferBps || !s32AvgStreamBps)
    {
        *pDelayMs = 0;
        ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
        return HI_SUCCESS;
    }

    S32DelayBps = (s32AvgStreamBps > s32BufferBps) ? (s32AvgStreamBps / s32BufferBps) : (s32BufferBps / s32AvgStreamBps);
    if (S32DelayBps >= ADEC_PTSMS_DIFF)
    {
        *pDelayMs = 0;
    }
    else
    {
        *pDelayMs = u32InStreamPts;
    }

    if (*pDelayMs >= ADEC_MAXPTSTIME)
    {
        *pDelayMs = 0;
    }
 // input buffer more than 1.2s but out buffer less than 40ms make flow control donot work
 //ADEC_GetDelayMs:u32OutBufDurationMs 24,*pDelayMs 1344
#if 1
#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {    
         if(ADECHwGetOutbufFrameNum(pstAdecChan, &stStatus) <= 2)   //if outbuf less than 2 frames, don't control stream
         {
            *pDelayMs = 0;
         }   
    }
    else
#endif
    {
        /* outbuf DurationMs is more critical than inbuf for low delay control */
        ADECGetOutbufDurationMs(pstAdecChan, &u32OutBufDurationMs);
        if (u32OutBufDurationMs < (4 * ADEC_SYS_SLEEP_TIME))  //TODO Judge arecording to frame  num
        {
            *pDelayMs = 0;
        }
    }
#endif
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : ADECOpenDevice
 Description  : ...
 Input        : None
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2006/1/18
    Author       : vicent feng
    Modification : Created function
*****************************************************************************/
static HI_S32 ADECOpenDevice(HI_CHAR*  pathname, const HI_S32 Flags)
{
    HI_S32 AudioDevFd = -1;

#ifndef DISABLE_MKP_ADEC
    struct stat st;
    if (HI_FAILURE == stat (pathname, &st))
    {
        //HI_FATAL_ADEC("Cannot identify '%s': %d, %s\n", pathname, errno, strerror (errno));
        return HI_FAILURE;
    }

    if (!S_ISCHR (st.st_mode))
    {
        HI_FATAL_ADEC("%s is no device\n", pathname);
        return HI_FAILURE;
    }

    AudioDevFd = open(pathname, Flags, 0);
    if (-1 == AudioDevFd)
    {
        //HI_FATAL_ADEC("Cannot open '%s': %d, %s\n", pathname, errno, strerror (errno));
        return HI_FAILURE;
    }
#endif


    return AudioDevFd;
}

/*****************************************************************************
 Prototype    : ADECCloseDevice
 Description  : ...
 Input        : None
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2006/1/18
    Author       : vicent feng
    Modification : Created function
*****************************************************************************/
static HI_S32 ADECCloseDevice(HI_S32 AudioDevFd)
{
#ifndef DISABLE_MKP_ADEC
    HI_S32 nRet = HI_SUCCESS;

    nRet = close(AudioDevFd);
    if (HI_SUCCESS != nRet)
    {
        HI_WARN_ADEC("Adec Close err=0x%x\n", nRet);
        return HI_FAILURE;
    }
#endif


    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype    : ADECInitProcInfo
 Description  : ...
 Input        : None
 Output       : None
 Return Value :
 Calls        :
 Called By    :

  History        :
  1.Date         : 2006/1/18
    Author       : vicent feng
    Modification : Created function
*****************************************************************************/
static HI_VOID ADECInitProcInfo(ADEC_PROC_ITEM_S* pstAdecInfo)
{
    CHECK_NULL_PTR_NORET(pstAdecInfo);

    pstAdecInfo->bAdecWorkEnable = HI_FALSE;
    pstAdecInfo->u32CodecID = (HI_U32) - 1;
    pstAdecInfo->enFmt = HI_FALSE;
    pstAdecInfo->enSampleRate = HI_UNF_SAMPLE_RATE_UNKNOWN;
    pstAdecInfo->enBitWidth = HI_UNF_BIT_DEPTH_UNKNOWN;
    pstAdecInfo->u32OutChannels = 0;
    pstAdecInfo->u32ErrFrameNum = 0;
    pstAdecInfo->u32FramnNm    = 0;
    pstAdecInfo->u32BufSize    = 0;
    pstAdecInfo->s32BufRead    = 0;
    pstAdecInfo->u32BufWrite   = 0;
    pstAdecInfo->u32FrameSize  = 0;
    pstAdecInfo->u32FrameRead  = 0;
    pstAdecInfo->u32FrameWrite = 0;
    pstAdecInfo->u32FrameReadWrap  = 0;
    pstAdecInfo->u32FrameWriteWrap = 0;
    pstAdecInfo->u32BitsOutBytesPerFrame = 0;
    pstAdecInfo->u32PcmSamplesPerFrame = 0;
    pstAdecInfo->u32PtsLost = 0;

    pstAdecInfo->u32DbgGetBufCount_Try = 0;
    pstAdecInfo->u32DbgGetBufCount = 0;
    pstAdecInfo->u32DbgPutBufCount_Try = 0;
    pstAdecInfo->u32DbgPutBufCount = 0;
    pstAdecInfo->u32DbgReceiveFrameCount_Try = 0;
    pstAdecInfo->u32DbgReceiveFrameCount   = 0;
    pstAdecInfo->u32DbgSendStraemCount_Try = 0;
    pstAdecInfo->u32DbgSendStraemCount = 0;
    pstAdecInfo->u32DbgTryDecodeCount = 0;

    pstAdecInfo->u32ThreadId = 0;
    pstAdecInfo->ThreadBeginTime = 0;
    pstAdecInfo->ThreadEndTime = 0;
    pstAdecInfo->ThreadExeTimeOutCnt = 0;
    pstAdecInfo->ThreadScheTimeOutCnt = 0;

    pstAdecInfo->u32AdecSystemSleepTime = 0;

    pstAdecInfo->u32CodecUnsupportNum = 0;
    pstAdecInfo->u32StreamCorruptNum = 0;

    return;
}

static HI_VOID ADECGetHaSzname(ADEC_CHAN_S* pstAdecChan)
{
    HI_HA_DECODE_S* hHaEntry;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;
    ADEC_INFO_S*   ptDecAttr = HI_NULL_PTR;

    ptDecAttr   = &(pstAdecChan->decAttr);
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    hHaEntry = ptDecAttr->pHaDecoderDev;
    if (hHaEntry)
    {
        if (hHaEntry->szName)
        {
            memcpy(pstAdecInfo->szCodecType, hHaEntry->szName, 0x20);
            pstAdecInfo->szCodecType[31] = 0;
        }
        else
        {
            strncpy((HI_CHAR*)pstAdecInfo->szCodecType, "UNKNOWN", sizeof(pstAdecInfo->szCodecType));
        }

        if (hHaEntry->pszDescription)
        {
            memcpy(pstAdecInfo->szCodecDescription, hHaEntry->pszDescription, 0x20);
            pstAdecInfo->szCodecDescription[31] = 0;
        }
        else
        {
            strncpy((HI_CHAR*)pstAdecInfo->szCodecDescription, "UNKNOWN", sizeof(pstAdecInfo->szCodecDescription));
        }
    }

    return;
}

static HI_VOID ADECResetProcInfo2(ADEC_CHAN_S* pstAdecChan)
{
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    CHECK_NULL_PTR_NORET(pstAdecChan);
    CHECK_NULL_PTR_NORET(pstAdecChan->pstAdecInfo);
    pstAdecInfo = pstAdecChan->pstAdecInfo;

    pstAdecInfo->u32CodecID = pstAdecChan->u32CodecID;
    pstAdecInfo->enFmt = pstAdecChan->bPacketDecoder;
    pstAdecInfo->bAdecWorkEnable = pstAdecChan->beWork;/*expedient */
    pstAdecInfo->u32FrameSize = pstAdecChan->outStreamBuf.u32OutBufNum;
    pstAdecInfo->u32BufSize    = pstAdecChan->InStreamBuf.u32BufSize;
    pstAdecInfo->u32FrameRead  = 0;
    pstAdecInfo->u32FrameWrite = 0;
    pstAdecInfo->u32FrameReadWrap  = 0;
    pstAdecInfo->u32FrameWriteWrap = 0;
    pstAdecInfo->u32OutChannels = 0;
    pstAdecInfo->u32BitsOutBytesPerFrame = 0;
    pstAdecInfo->u32PcmSamplesPerFrame = 0;
    pstAdecInfo->s32BufRead  = 0;
    pstAdecInfo->u32BufWrite = 0;
    pstAdecInfo->u32PtsLost = 0;
    pstAdecInfo->u32FramnNm = 0;
    pstAdecInfo->u32ErrFrameNum = 0;
    pstAdecInfo->u32FrameConsumedBytes  = 0;
    pstAdecInfo->u32LastCorrectFrameNum = 0;
    pstAdecInfo->u32CodecUnsupportNum = 0;
    pstAdecInfo->u32StreamCorruptNum = 0;
    ADECGetHaSzname(pstAdecChan);
    return;
}

static HI_S32 ADECFindDecoder( ADEC_CHAN_S* pstAdecChan )
{
    HI_HA_DECODE_S* pHaDev;

    pHaDev = ADEC_FindHaDecoderImple((HI_U32)pstAdecChan->u32CodecID);
    if (pHaDev == HI_NULL)
    {
        HI_ERR_ADEC ( " ADEC_FindHaDecoderImple Fail (u32CodecID=0x%x)  \n", pstAdecChan->u32CodecID);
        return HI_FAILURE;
    }

    pstAdecChan->decAttr.pHaDecoderDev = pHaDev;
    return HI_SUCCESS;
}

static HI_S32 ADECInitDecoder(ADEC_INFO_S*   pstAecAttr )
{
    HI_S32 Ret = HI_FAILURE;
    
    Ret = ADEC_InitDecoderImple(pstAecAttr);

    return Ret;
}

static HI_VOID ADECDeInitDecoder(ADEC_INFO_S*   pstAecAttr )
{
    HI_HA_DECODE_S* pHaDev;

    CHECK_NULL_PTR_NORET(pstAecAttr);

    if (HI_NULL_PTR != (pstAecAttr->hDecoder))
    {
        if (HI_NULL_PTR != (pstAecAttr->pHaDecoderDev))
        {
            pHaDev = pstAecAttr->pHaDecoderDev;
            (HI_VOID)pHaDev->DecDeInit(pstAecAttr->hDecoder);
            pstAecAttr->hDecoder = HI_NULL_PTR;
        }
    }

    return;
}

static HI_S32 ADECResetDecoder(ADEC_INFO_S*   pstAecAttr )
{
    HI_S32 nRet;

    CHECK_ADEC_NULL_PTR(pstAecAttr);

    ADECDeInitDecoder(pstAecAttr );
    nRet = ADECInitDecoder(pstAecAttr );
    if (HI_SUCCESS != nRet)
    {
        HI_ERR_ADEC("ADECResetDecoder err=0x%x\n", nRet);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID  ADEC_Process16bitVolume(HI_S16* pPcmBuf, HI_S32 InSamps, HI_S32 Channels, HI_S16 s16Volume)
{
    HI_S32 sum, n;

    for (n = 0; n < (InSamps * Channels); n++)
    {
        sum = MULF32_16B((HI_S32)pPcmBuf[n], s16Volume);
        pPcmBuf[n] = (HI_S16)sum;
    }
}

static HI_VOID  ADEC_Process32bitVolume(HI_S32* pPcmBuf, HI_S32 InSamps, HI_S32 Channels, HI_S16 s16Volume)
{
    HI_S32 sum, n;

    for (n = 0; n < (InSamps * Channels); n++)
    {
        sum = MULF32_16B((HI_S32)pPcmBuf[n], s16Volume);
        pPcmBuf[n] = (HI_S32)sum;
    }
}

HI_VOID  ADEC_ProcessVolume(HI_S32* ps32PcmBuf, HI_S32 InSamps, HI_S32 BitPerSample, HI_S32 Channels, HI_S16 s16Volume)
{
    if (InSamps & 0xffff0000)
    {
        InSamps = InSamps & 0xffff;
    }
    if (16 == BitPerSample)
    {
        ADEC_Process16bitVolume((HI_S16*)ps32PcmBuf, InSamps, Channels, s16Volume);
    }
    else
    {
        ADEC_Process32bitVolume((HI_S32*)ps32PcmBuf, InSamps, Channels, s16Volume);
    }
}

ADEC_OUTPUTBUF_S* ADECGetOutBuf(ADEC_STREAM_OUTBUF_S*  pstOutBuf)
{
    HI_U32 nextTail;
    ADEC_OUTPUTBUF_S* ptRetBuf = pstOutBuf->outBuf;

    ptRetBuf = pstOutBuf->outBuf;

    /* check availability of output buffer */
    nextTail = ((pstOutBuf->u32BufWriteIdx + 1) % (pstOutBuf->u32OutBufNum));
    if ((nextTail == pstOutBuf->u32BufReadIdx) || (ptRetBuf[pstOutBuf->u32BufWriteIdx].bFlag == HI_TRUE))
    {
        return HI_NULL;
    }

    return &ptRetBuf[pstOutBuf->u32BufWriteIdx];
}

static HI_VOID ADEC_UpdateFrameInfo(ADEC_CHAN_S* pstAdecChan)
{
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    pstAdecInfo = pstAdecChan->pstAdecInfo; 
    
    if((pstAdecChan->stFrameInfo.enSampleRate != (HI_U32)pstAdecInfo->enSampleRate ||
        pstAdecChan->stFrameInfo.u32Channel   != pstAdecInfo->u32OutChannels ||
        pstAdecChan->stFrameInfo.enBitDepth   != pstAdecInfo->enBitWidth) &&
       (pstAdecChan->stFrameInfo.enSampleRate != (HI_U32)HI_UNF_SAMPLE_RATE_UNKNOWN &&
        pstAdecChan->stFrameInfo.u32Channel   != 0 &&
        pstAdecChan->stFrameInfo.enBitDepth   != HI_UNF_BIT_DEPTH_UNKNOWN))
    {
        HI_WARN_ADEC("Frame information change! \n");
        pstAdecChan->stFrameInfo.bFrameInfoChange = HI_TRUE;
    }

    if(pstAdecChan->pstAdecInfo->u32CodecUnsupportNum >= ADEC_MAX_CODECUNSUPPORT_NUM)
    {
        HI_WARN_ADEC("UnSupport Stream Format \n");
        pstAdecChan->stFrameInfo.bUnSupportFormat = HI_TRUE;
    }

    if(pstAdecChan->pstAdecInfo->u32StreamCorruptNum  >= ADEC_MAX_STREAMCORRUPT_NUM)
    {
        HI_WARN_ADEC("Stream Corrupted \n");
        pstAdecChan->stFrameInfo.bStreamCorrupt   = HI_TRUE;
    }
               
    pstAdecChan->stFrameInfo.enSampleRate = (HI_U32)pstAdecInfo->enSampleRate;
    pstAdecChan->stFrameInfo.u32Channel   = pstAdecInfo->u32OutChannels;
    pstAdecChan->stFrameInfo.enBitDepth   = pstAdecInfo->enBitWidth;  

    return;
}



static HI_VOID ADECConvertHaOut2MpiOut(ADEC_CHAN_S* pstAdecChan, ADEC_OUTPUTBUF_S* ptRetBuf,
                                       HI_HADECODE_OUTPUT_S* pstAout,
                                       HI_U32 u32StreamReadPos)
{
    HI_U32 u32OrgPTS;
    HI_U32 u32PcmSamplesPerFrame;
    HI_U32 u32FixStreamReadPos;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    HI_S32* ps32PcmBuf;

    /* look for PTS */
    u32PcmSamplesPerFrame = pstAout->u32PcmOutSamplesPerFrame & 0xffff;//for dolby_truehd,frame_samples stored in 0~15 bit
    if (!pstAout->u32PcmOutSamplesPerFrame)    
    {
        if ((pstAout->u32OutChannels) && (pstAout->u32BitsOutBytesPerFrame & 0xffff))
        {
            u32PcmSamplesPerFrame = (pstAout->u32BitsOutBytesPerFrame & 0xffff) / (pstAout->u32OutChannels * sizeof(HI_U16)); //only passthrough exist
        }
        else
        {
            u32PcmSamplesPerFrame = 0;
        }

    }
#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        u32FixStreamReadPos = pstAout->stPtsInfo.unPts.u32HwDecoderPtsReadPos;
        ptRetBuf->u32FrameIndex = pstAout->u32FrameIndex;
    }
    else
#endif
    {
        u32FixStreamReadPos = ADECFixStreamReadPos(pstAdecChan, u32StreamReadPos,
                              pstAout->stPtsInfo.unPts.u32SwDecoderBytesLeft);
    }
    ptRetBuf->u32PTS = ADECFindPTS(&(pstAdecChan->PTSQue), (HI_U32)u32FixStreamReadPos,
                                   u32PcmSamplesPerFrame,
                                   pstAout->u32OutSampleRate, &u32OrgPTS);

    ptRetBuf->u32OrgPTS = u32OrgPTS;
    ptRetBuf->u32PcmOutSamplesPerFrame = pstAout->u32PcmOutSamplesPerFrame;
    ptRetBuf->u32BitsOutBytesPerFrame = pstAout->u32BitsOutBytesPerFrame;
    ptRetBuf->u32OutChannels   = pstAout->u32OutChannels;
    ptRetBuf->u32OutSampleRate = pstAout->u32OutSampleRate;
    ptRetBuf->bInterleaved = pstAout->bInterleaved;
    ptRetBuf->u32BitPerSample = pstAout->u32BitPerSample;
    ptRetBuf->ps32PcmOutBuf  = pstAout->ps32PcmOutBuf;
    ptRetBuf->ps32BitsOutBuf = pstAout->ps32BitsOutBuf;

    if (ADEC_MAX_VOLUME != pstAdecChan->u32Volume)
    {
#ifdef HA_HW_CODEC_SUPPORT  
        if (HI_TRUE == pstAdecChan->bHwDecoder)
        {
            pstOutBuf = &(pstAdecChan->outStreamBuf);
            ps32PcmBuf = (HI_S32*)((HI_VOID*)pstOutBuf->pu32BaseAddr + (HI_U32)pstAout->ps32PcmOutBuf);
        }
        else
#endif  
        {
            ps32PcmBuf = pstAout->ps32PcmOutBuf;
        }
        ADEC_ProcessVolume(ps32PcmBuf,
                           (HI_S32)pstAout->u32PcmOutSamplesPerFrame,
                           (HI_S32)pstAout->u32BitPerSample,
                           (HI_S32)pstAout->u32OutChannels,
                           pstAdecChan->s16VolumeFrac);
    }
}


static HI_VOID ADECConvertMpiOut2HaOut(HI_HA_DECODE_S* pHaDev, HI_VOID* hDecoder, ADEC_OUTPUTBUF_S* ptRetBuf,
                                       HI_HADECODE_OUTPUT_S* pstAout)
{
    HI_U32 outbufSize;

    /* setup pcm out buffer */
    outbufSize = 0;
    if (pHaDev->DecGetMaxPcmOutSize)
    {
        (HI_VOID)pHaDev->DecGetMaxPcmOutSize(hDecoder, &outbufSize);
    }

    pstAout->ps32PcmOutBuf = (HI_S32*)(ptRetBuf->OutBuf);
    pstAout->u32PcmOutBufSize = (HI_U32)outbufSize;

    /* setup bits out buffer */
    outbufSize = 0;
    if (pHaDev->DecGetMaxBitsOutSize)
    {
        (HI_VOID)pHaDev->DecGetMaxBitsOutSize(hDecoder, &outbufSize);
    }

    pstAout->ps32BitsOutBuf = (HI_S32*)(((HI_U8*)(ptRetBuf->OutBuf)) + pstAout->u32PcmOutBufSize);
    pstAout->u32BitsOutBufSize = (HI_U32)outbufSize;
}

static HI_S32 ADECSwDecode( ADEC_CHAN_S* pstAdecChan)
{
    HI_S32 sRet;
    HI_VOID*  hDecoder = HI_NULL_PTR;
    ADEC_INFO_S*   ptDecAttr         = HI_NULL_PTR;
    ADEC_OUTPUTBUF_S* ptRetBuf       = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo    = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    ADEC_MIDSTATE_S* pstMidState     = HI_NULL_PTR;
    ADEC_PTS_QUE_S* pstPTSQue = HI_NULL_PTR;
    HI_HA_DECODE_S* pHaDev;
    HI_HADECODE_INPACKET_S avpkt;
    HI_HADECODE_OUTPUT_S sOut;
    HI_U32 u32StreamReadPos = 0;
    HI_U32 u32FrameConsumeBytes = 0;
    HI_U32 u32ByteLeftBfDecode = 0;

    CHECK_ADEC_NULL_PTR(pstAdecChan);

    ptDecAttr = &(pstAdecChan->decAttr);
    pstOutBuf   = &(pstAdecChan->outStreamBuf);
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstMidState = &(pstAdecChan->midState);
    pstPTSQue = &(pstAdecChan->PTSQue);
    hDecoder = (HI_VOID*)ptDecAttr->hDecoder;

    CHECK_ADEC_NULL_PTR(ptDecAttr->pHaDecoderDev);

	ADEC_LOCK(&g_AdecIOMutex[pstAdecChan->u32AdecChID]); 
    pHaDev = ptDecAttr->pHaDecoderDev;

    ADECGetInputBuf(pstAdecChan, &avpkt);
    /* Some decoder  may has its own delay buffer, try to pull decoder untill HA_ErrorNotEnoughData  */
    while (1)
    {
        /* check availability of output buffer */
        ptRetBuf = ADECGetOutBuf(pstOutBuf);
        if (HI_NULL == ptRetBuf)
        {
            break;
        }

        /* setup ha pcm out buffer */
        ADECConvertMpiOut2HaOut(pHaDev, hDecoder, ptRetBuf, &sOut);

        /* get pts readpos before decode one frame */
        u32StreamReadPos = ADECGetStreamReadPos(&pstAdecChan->InStreamBuf);

        /* decode one audio frame */
        u32ByteLeftBfDecode = avpkt.s32Size;
        ADEC_UNLOCK(&g_AdecIOMutex[pstAdecChan->u32AdecChID]);
        sRet = pHaDev->DecDecodeFrame(hDecoder, &avpkt, &sOut);
        ADEC_LOCK(&g_AdecIOMutex[pstAdecChan->u32AdecChID]); 
        if ((HI_U32)avpkt.s32Size > u32ByteLeftBfDecode)
        {
            HI_ERR_ADEC("BytesBfDecode=0x%.8x,BytesAfDecode=0x%.8x\n", u32ByteLeftBfDecode, avpkt.s32Size);
            avpkt.s32Size = u32ByteLeftBfDecode;
        }

        u32FrameConsumeBytes = u32ByteLeftBfDecode - avpkt.s32Size;
        pstAdecChan->s32BsConsumeBytes += u32FrameConsumeBytes; //for ADECCheckScrambler

        /* check decode one audio frame */
        if (HA_ErrorNotEnoughData == sRet)
        {
            if (!u32FrameConsumeBytes)
            {
                if (HI_TRUE == pstAdecChan->bPacketDecoder)
                {
                    /* can't decode, Packet audio error*/
                    if (avpkt.s32Size)
                    {
                        HI_WARN_ADEC("FMT_PACKET discard crrupt packet bytes(%d)! \n", sRet, avpkt.s32Size);
                    }

                    u32FrameConsumeBytes = avpkt.s32Size;
                }
            }

            ADECUpdateInputBuf(pstAdecChan, u32FrameConsumeBytes);
            if (((pstPTSQue->ulPTSwrite + 1) % ADEC_MAX_STORED_PTS_NUM) == pstPTSQue->ulPTSread)
            {

                u32StreamReadPos = ADECFixStreamReadPos(pstAdecChan, u32StreamReadPos,
                                                        sOut.stPtsInfo.unPts.u32SwDecoderBytesLeft);
                ADECDiscardPTS(pstPTSQue, u32StreamReadPos);
            }
            /* use for check whether end of decode the input buffer */
            if(HI_TRUE == pstAdecChan->bAdecEosFlag)
            {
                pstAdecChan->u32NotEnoughBufCnt++;
            }
            else
            {
                pstAdecChan->u32NotEnoughBufCnt = 0;
            }

            break;
        }
        else if (HA_ErrorNone == sRet)    /* Success */
        {
            /* when decode audio frame success, clear u32NotEnoughBufCnt */
            pstAdecChan->u32NotEnoughBufCnt = 0;
            
            if ((sOut.u32OutSampleRate == 0) || (sOut.u32OutSampleRate > 192000))
            {
                HI_WARN_ADEC("Invalid SampleRate(%d)! \n", sOut.u32OutSampleRate);
                ADECUpdateInputBuf(pstAdecChan, u32FrameConsumeBytes);
                break;
            }

            ADECConvertHaOut2MpiOut(pstAdecChan, ptRetBuf, &sOut, u32StreamReadPos);

            /* move the tail of output buffer */
            ADECUpdateInputBuf(pstAdecChan, u32FrameConsumeBytes);
            ADECGetInputBuf(pstAdecChan, &avpkt);
            pstOutBuf->u32BufWriteIdx = (pstOutBuf->u32BufWriteIdx + 1) % (pstOutBuf->u32OutBufNum);
            pstMidState->u32ContinueErrNum = 0;
            pstAdecInfo->u32FramnNm++;
            pstAdecInfo->u32FrameWrite = pstOutBuf->u32BufWriteIdx;
            pstAdecInfo->enSampleRate  = (HI_UNF_SAMPLE_RATE_E)sOut.u32OutSampleRate;
            pstAdecInfo->enBitWidth    = (HI_UNF_BIT_DEPTH_E)sOut.u32BitPerSample;
            pstAdecInfo->u32OutChannels= sOut.u32OutChannels;
            pstAdecInfo->u32PcmSamplesPerFrame = (sOut.u32PcmOutSamplesPerFrame & 0xffff);

            pstAdecChan->u32TotalFrameByte += pstAdecInfo->u32PcmSamplesPerFrame;

            if (pstAdecChan->u32TotalFrameByte)
            {
                pstAdecChan->pstAdecInfo->u32bps =(pstAdecChan->s32BsConsumeBytes*8*pstAdecInfo->enSampleRate)/pstAdecChan->u32TotalFrameByte;
            }

            ADEC_UpdateFrameInfo(pstAdecChan);
        }
        else     /* Failure */
        {
            /* when decode audio frame failure, clear u32NotEnoughBufCnt */
            pstAdecChan->u32NotEnoughBufCnt = 0;
            
            HI_INFO_ADEC( "Decode packet HA_ErrorStreamCorrupt \n");
            if (!u32FrameConsumeBytes)
            {
                /*  decode holding,  discard  bytes */
                u32FrameConsumeBytes = avpkt.s32Size;
                if (u32FrameConsumeBytes > ADEC_BYTES_DISCARD_THD)
                {
                    u32FrameConsumeBytes = ADEC_BYTES_DISCARD_THD;  /* discard bytes */
                }
            }

            pstAdecInfo->u32ErrFrameNum++;
            ADECUpdateInputBuf(pstAdecChan, u32FrameConsumeBytes);
            if (((pstPTSQue->ulPTSwrite + 1) % ADEC_MAX_STORED_PTS_NUM) == pstPTSQue->ulPTSread)
            {

                u32StreamReadPos = ADECFixStreamReadPos(pstAdecChan, u32StreamReadPos,
                                                        sOut.stPtsInfo.unPts.u32SwDecoderBytesLeft);
                ADECDiscardPTS(pstPTSQue, u32StreamReadPos);
            }

            if(HA_ErrorNotSupportCodec == sRet)
            {
                pstAdecInfo->u32CodecUnsupportNum++;
            }
            if(HA_ErrorStreamCorrupt == sRet)
            {
                pstAdecInfo->u32StreamCorruptNum++;
            }
            break;
        }
    }//end while 1
    pstAdecInfo->u32DbgTryDecodeCount++;
    ADEC_UNLOCK(&g_AdecIOMutex[pstAdecChan->u32AdecChID]);
    return HI_SUCCESS;
}

static HI_S32 ADECInitChannel( ADEC_CHAN_S* pstAdecChan )
{
    HI_S32 nRet;
    HI_U32 u32PaddingSize;

    CHECK_ADEC_NULL_PTR(pstAdecChan);
    CHECK_ADEC_STATE_NOMUTE(pstAdecChan->beAssigned);
    CHECK_ADEC_STATE_NOMUTE(pstAdecChan->beWork);

    nRet = ADECFindDecoder(pstAdecChan);
    if (nRet != HI_SUCCESS)
    {
        HI_ERR_ADEC("ADECFindHADecoder err=0x%x\n", nRet);
        return HI_FAILURE;
    }

    nRet = ADECInitDecoder(&(pstAdecChan->decAttr));
    if (nRet != HI_SUCCESS)
    {
        HI_ERR_ADEC("Adec_Decoder_Init err=0x%x\n", nRet);
        return HI_FAILURE;
    }

    // 2  Allocate Read Buffer
    pstAdecChan->pstPacketQue = HI_NULL;
    u32PaddingSize = 0;
    if (HI_TRUE != pstAdecChan->bHwDecoder)
    {
        /* only sw decoder support packet audio */
        pstAdecChan->pstPacketQue = (ADEC_PACKET_QUE_S*)HI_MALLOC(HI_ID_ADEC, sizeof(ADEC_PACKET_QUE_S));
        if (HI_NULL == pstAdecChan->pstPacketQue)
        {
            ADECDeInitDecoder(&pstAdecChan->decAttr);
            HI_ERR_ADEC("ADECInitInBuf malloc pstPacketQue err\n");
            return HI_FAILURE;
        }

        if (HI_TRUE == pstAdecChan->bPacketDecoder)
        {
            u32PaddingSize = PACKET_ADEC_INPUTBUF_PADDING_SIZE;
        }
        else
        {
            u32PaddingSize = ADEC_INPUTBUF_PADDING_SIZE;
        }
    }

    nRet = ADECInitInBuf(pstAdecChan, &pstAdecChan->InStreamBuf, u32PaddingSize, pstAdecChan->u32AdecChID);
    if (nRet != HI_SUCCESS)
    {
        ADECDeInitDecoder(&pstAdecChan->decAttr);
        HI_ERR_ADEC("ADECInitInBuf err=0x%x\n", nRet);
        return HI_FAILURE;
    }

    // 3 Allocate OutBuffer
    nRet = ADECInitOutBuf(pstAdecChan, &pstAdecChan->outStreamBuf, ADECGetMaxOutBufSize(pstAdecChan),
                          pstAdecChan->u32AdecChID);
    if (nRet != HI_SUCCESS)
    {
        ADECDeInitInBuf(pstAdecChan, &pstAdecChan->InStreamBuf);
        ADECDeInitDecoder(&pstAdecChan->decAttr);
        HI_ERR_ADEC("ADECInitOutBuf err=0x%x\n", nRet);
        return HI_FAILURE;
    }

#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        HI_VOID*  hDecoder = HI_NULL_PTR;
        HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
        hDecoder = pstAdecChan->decAttr.hDecoder;
        (HI_VOID)pHaDev->HwSetEosFlag(hDecoder, HI_FALSE);
        (HI_VOID)pHaDev->HwSetEnable(hDecoder, HI_TRUE);//PCLINT
    }
#endif

    ADECResetMidState(&pstAdecChan->midState);

    /* reset PTS */
    ADECRestPTSQuet(&pstAdecChan->PTSQue);
    ADECRestPacketQuet(pstAdecChan->pstPacketQue);
    return HI_SUCCESS;
}

static HI_S32 ADECDeInit_Channel( ADEC_CHAN_S* pstAdecChan )
{
    CHECK_ADEC_NULL_PTR(pstAdecChan);
    CHECK_ADEC_STATE_NOMUTE(pstAdecChan->beAssigned);
    CHECK_ADEC_STATE_NOMUTE(pstAdecChan->beWork);
#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        HI_VOID*  hDecoder = pstAdecChan->decAttr.hDecoder;;
        HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
        (HI_VOID)pHaDev->HwSetEosFlag(hDecoder, HI_FALSE);
        (HI_VOID)pHaDev->HwSetEnable(hDecoder, HI_FALSE);//PCLINT
    }
#endif


    ADECDeInitOutBuf(pstAdecChan, &pstAdecChan->outStreamBuf);
    if (pstAdecChan->pstPacketQue)
    {
        HI_FREE(HI_ID_ADEC, pstAdecChan->pstPacketQue);
    }

    ADECDeInitInBuf(pstAdecChan, &pstAdecChan->InStreamBuf);
    ADECDeInitDecoder(&pstAdecChan->decAttr);

    return HI_SUCCESS;
}

/****************************************************************************
 * Function:    ADECOpenChannel
 *
 * Description:
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
static HI_S32  ADECOpenChannel(ADEC_CHAN_S* pstAdecChan)
{
#ifndef DISABLE_MKP_ADEC
    HI_S32 ret;
    HI_CHAR pathname[64];
    HI_U32 phy_adress;
#endif

    CHECK_ADEC_NULL_PTR(pstAdecChan);
#ifndef DISABLE_MKP_ADEC
    /* Check if initialized */

    snprintf((HI_CHAR*)pathname, sizeof(pathname), "/dev/%s", DRV_ADEC_DEVICE_NAME);

    pstAdecChan->AdecDevFd = ADECOpenDevice((HI_CHAR*)pathname, O_RDWR);
    if (pstAdecChan->AdecDevFd < 0)
    {
        HI_ERR_ADEC("ADECOpenDevice err \n");
        return HI_FAILURE;
    }

    ret = ioctl(pstAdecChan->AdecDevFd, DRV_ADEC_PROC_INIT, &phy_adress);
    if (0 != ret)
    {
        (HI_VOID)ADECCloseDevice(pstAdecChan->AdecDevFd);
        pstAdecChan->AdecDevFd = -1;
        HI_ERR_ADEC("ioctl	DRV_ADEC_PROC_INIT err=0x%x \n", ret);
        return HI_FAILURE;
    }

    pstAdecChan->pstAdecInfo = (ADEC_PROC_ITEM_S*)HI_MMAP(phy_adress, sizeof(ADEC_PROC_ITEM_S));
    if (NULL == pstAdecChan->pstAdecInfo)
    {
        (HI_VOID)ADECCloseDevice(pstAdecChan->AdecDevFd);
        pstAdecChan->AdecDevFd = -1;
        HI_ERR_ADEC("HI_MMAP	ADEC_PROC_ITEM_S err\n");
        return HI_FAILURE;
    }

    ADECInitProcInfo(pstAdecChan->pstAdecInfo);
#endif

    return HI_SUCCESS;
}

static HI_VOID  ADECCloseChannel(ADEC_CHAN_S* pstAdecChan)
{
    ADEC_INFO_S*   ptDecAttr = HI_NULL_PTR;

    CHECK_NULL_PTR_NORET(pstAdecChan);
    ptDecAttr = &(pstAdecChan->decAttr);

    /*********************************************/
#ifndef DISABLE_MKP_ADEC
    if (pstAdecChan->AdecDevFd >= 0)
    {
        ioctl(pstAdecChan->AdecDevFd, DRV_ADEC_PROC_EXIT, &pstAdecChan->pstAdecInfo);
        (RET_VOID)ADECCloseDevice(pstAdecChan->AdecDevFd);
        pstAdecChan->AdecDevFd = -1;
    }
#endif


    if (pstAdecChan->pstAdecInfo)
    {
        (HI_VOID)HI_MUNMAP(pstAdecChan->pstAdecInfo);
        pstAdecChan->pstAdecInfo = HI_NULL_PTR;
    }

    if (HI_NULL_PTR != ptDecAttr->pAudPrivDataBak)
    {
        HI_FREE(HI_ID_ADEC, ptDecAttr->pAudPrivDataBak);
        ptDecAttr->pAudPrivDataBak = HI_NULL_PTR;
        ptDecAttr->u32AudPrivDataBakDize = 0;
    }

    return;
}

static HI_S32 ADECCheckHACodecAttr(const ADEC_ATTR_S*  pstAttr)
{
    if ((pstAttr->sOpenPram.enDecMode != HD_DEC_MODE_RAWPCM)
        && (pstAttr->sOpenPram.enDecMode != HD_DEC_MODE_THRU)
        && (pstAttr->sOpenPram.enDecMode != HD_DEC_MODE_SIMUL))
    {
        HI_ERR_ADEC("invalid enDecMode(0x%x)!\n", pstAttr->sOpenPram.enDecMode);
        return HI_FAILURE;
    }

    if ((pstAttr->sOpenPram.enDecMode != HD_DEC_MODE_RAWPCM)
        && (pstAttr->sOpenPram.enDecMode != HD_DEC_MODE_THRU)
        && (pstAttr->sOpenPram.enDecMode != HD_DEC_MODE_SIMUL))
    {
        HI_ERR_ADEC("invalid enDecMode(0x%x)!\n", pstAttr->sOpenPram.enDecMode);
        return HI_FAILURE;
    }

    if (pstAttr->sOpenPram.sPcmformat.u32DesiredOutChannels > ADEC_MAX_CHANNLES)
    {
        HI_ERR_ADEC("invalid u32DesiredOutChannels(0x%x)!\n", pstAttr->sOpenPram.sPcmformat.u32DesiredOutChannels);
        return HI_FAILURE;
    }

    if ((pstAttr->sOpenPram.sPcmformat.u32BitPerSample != 16)
        && (pstAttr->sOpenPram.sPcmformat.u32BitPerSample != 20)
        && (pstAttr->sOpenPram.sPcmformat.u32BitPerSample != 24)
       )
    {
        HI_ERR_ADEC("invalid s32BitPerSample(0x%x)!\n", pstAttr->sOpenPram.sPcmformat.u32BitPerSample);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 ADECCheckInBufAttr(const ADEC_ATTR_S*  pstAttr)
{
    CHECK_ADEC_NULL_PTR(pstAttr);
    CHECK_ADEC_OUTBUF_NUMBER(pstAttr->u32OutBufNum);
    HI_S32 nRet;

    if (pstAttr->u32OutBufNum == 0)
    {
        HI_ERR_ADEC("invalid output buffer framenumber(%d)!\n", pstAttr->u32OutBufNum);
        return HI_FAILURE;
    }

    if ((pstAttr->u32InBufSize < ADEC_MIN_INPUT_BUFFER_SIZE) || (pstAttr->u32InBufSize > ADEC_MAX_INPUT_BUFFER_SIZE))
    {
        HI_ERR_ADEC(" invalid input buffer size(%d)  minsize(%d),maxsize(%d)!\n", pstAttr->u32InBufSize,
                    ADEC_MIN_INPUT_BUFFER_SIZE, ADEC_MAX_INPUT_BUFFER_SIZE);
        return HI_FAILURE;
    }

    nRet = ADECCheckHACodecAttr(pstAttr);

    return nRet;
}

static HI_S32 ADECGetInputAttr(ADEC_CHAN_S* pstAdecChan, const ADEC_ATTR_S*  pstAttr)
{
    ADEC_INFO_S*   ptDecAttr = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf  = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    HI_HADECODE_OPENPARAM_S* pstOpenParams = HI_NULL_PTR;

    CHECK_ADEC_NULL_PTR(pstAttr);
    CHECK_ADEC_NULL_PTR(pstAdecChan);

    ptDecAttr = &(pstAdecChan->decAttr);
    pstInBuf  = &(pstAdecChan->InStreamBuf);
    pstOutBuf = &(pstAdecChan->outStreamBuf);
    pstOpenParams = &(ptDecAttr->decParam);

    memset(pstOpenParams, 0, sizeof(HI_HADECODE_OPENPARAM_S));
    memcpy(pstOpenParams, &(pstAttr->sOpenPram), sizeof(HI_HADECODE_OPENPARAM_S));

    /* HI_MALLOC PrivDataDiz to backup openParams CodecPrivateData  for decoder reset */
    if ((HI_NULL_PTR != pstAttr->sOpenPram.pCodecPrivateData)
        && (0 != pstAttr->sOpenPram.u32CodecPrivateDataSize))
    {
        HI_U32 u32AudPrivDataDize;

        u32AudPrivDataDize = pstAttr->sOpenPram.u32CodecPrivateDataSize;

        if ((HI_NULL_PTR != ptDecAttr->pAudPrivDataBak) && (ptDecAttr->u32AudPrivDataBakDize >= u32AudPrivDataDize))
        {
            /* only update u32AudPrivDataDize, avoid HI_MALLOC again */
            ptDecAttr->u32AudPrivDataBakDize = u32AudPrivDataDize;
        }
        else
        {
            HI_VOID* pSrcAudPrivData;
            if (HI_NULL_PTR != ptDecAttr->pAudPrivDataBak)
            {
                HI_FREE(HI_ID_ADEC, ptDecAttr->pAudPrivDataBak);
                ptDecAttr->pAudPrivDataBak = HI_NULL_PTR;
            }

            /*HI_MALLOC privattr structure*/
            pSrcAudPrivData = (HI_VOID*)HI_MALLOC(HI_ID_ADEC, u32AudPrivDataDize);
            if (HI_NULL_PTR == pSrcAudPrivData)
            {
                HI_ERR_ADEC("  HI_MALLOC AudPrivData fail \n");
                return HI_FAILURE;
            }

            ptDecAttr->pAudPrivDataBak = pSrcAudPrivData;
            ptDecAttr->u32AudPrivDataBakDize = u32AudPrivDataDize;
        }

        memcpy(ptDecAttr->pAudPrivDataBak, (const HI_VOID*)(pstAttr->sOpenPram.pCodecPrivateData), u32AudPrivDataDize);

        /* use pAudPrivDataBak mem */
        pstOpenParams->pCodecPrivateData = ptDecAttr->pAudPrivDataBak;
        pstOpenParams->u32CodecPrivateDataSize = ptDecAttr->u32AudPrivDataBakDize;
        HI_INFO_ADEC("u32CodecID=0x%x u32CodecPrivateDataSize=%d\n", pstAdecChan->u32CodecID,
                     ptDecAttr->u32AudPrivDataBakDize);
    }
    if (0xffffffff != pstAttr->u32CodecID)
    {
        HA_CODEC_PACKETDECODER_QUERY_PARAM_S stPacketDecoder;
        HA_CODEC_HARDWARECODER_QUERY_PARAM_S stHwDecoder;
        memset(&stPacketDecoder, 0, sizeof(HA_CODEC_PACKETDECODER_QUERY_PARAM_S));
        memset(&stHwDecoder, 0, sizeof(HA_CODEC_HARDWARECODER_QUERY_PARAM_S));

        stPacketDecoder.enCmd = HA_CODEC_PACKETDECODER_QUERY_CMD;
        ADEC_SetConfigDeoder(pstAttr->u32CodecID, &stPacketDecoder);
        pstAdecChan->bPacketDecoder = stPacketDecoder.bPacketDecoder;

        stHwDecoder.enCmd = HA_CODEC_HARDWARECODEC_QUERY_CMD;
        pstAdecChan->bHwDecoder = HI_FALSE;
        if (HI_SUCCESS == ADEC_SetConfigDeoder(pstAttr->u32CodecID, &stHwDecoder))
        {
            pstAdecChan->bHwDecoder = stHwDecoder.bHwCodec;
        }
        else
        {
            pstAdecChan->bHwDecoder = HI_FALSE;
        }
    }

    pstInBuf->u32BufSize = pstAttr->u32InBufSize;
    pstOutBuf->u32OutBufNum = pstAttr->u32OutBufNum;
    pstAdecChan->beWork = pstAttr->bEnable;
    pstAdecChan->u32CodecID = pstAttr->u32CodecID;
    pstAdecChan->bAdecEosFlag = pstAttr->bEosState;
    return HI_SUCCESS;
}

static HI_S32 ADECCheckOpenParam(const HI_HADECODE_OPENPARAM_S* ptOldAttr, const HI_HADECODE_OPENPARAM_S*  pstAttr)
{
    HI_S32 isChange = 0;

    if (pstAttr->enDecMode != ptOldAttr->enDecMode)
    {
        isChange = 1;
    }

    if (pstAttr->sPcmformat.u32DesiredOutChannels != ptOldAttr->sPcmformat.u32DesiredOutChannels)
    {
        isChange = 1;
    }

    if (pstAttr->sPcmformat.bInterleaved != ptOldAttr->sPcmformat.bInterleaved)
    {
        isChange = 1;
    }

    if (pstAttr->sPcmformat.u32BitPerSample != ptOldAttr->sPcmformat.u32BitPerSample)
    {
        isChange = 1;
    }

    if (pstAttr->u32CodecPrivateDataSize != ptOldAttr->u32CodecPrivateDataSize)
    {
        isChange = 1;
    }

    if (pstAttr->u32CodecPrivateDataSize == ptOldAttr->u32CodecPrivateDataSize)
    {
        if (pstAttr->pCodecPrivateData && ptOldAttr->pCodecPrivateData)
        {
            HI_U32 n;
            for (n = 0; n < ptOldAttr->u32CodecPrivateDataSize; n++)
            {
                if ((( HI_U8*)pstAttr->pCodecPrivateData)[n] != (( HI_U8*)ptOldAttr->pCodecPrivateData)[n])
                {
                    isChange = 1;
                }
            }
        }
    }

    return isChange;
}

static HI_S32 ADECheckInputAttr(ADEC_CHAN_S* pstAdecChan, ADEC_ATTR_S*  pstAttr)
{
    HI_S32 ret;
    HI_S32 isChange = 0; /* whether need to change attribute */

    ADEC_INFO_S*   ptDecAttr = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf  = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;

    CHECK_ADEC_NULL_PTR(pstAttr);
    CHECK_ADEC_NULL_PTR(pstAdecChan);

    ptDecAttr = &(pstAdecChan->decAttr);
    pstInBuf  = &(pstAdecChan->InStreamBuf);
    pstOutBuf = &(pstAdecChan->outStreamBuf);

    HI_INFO_ADEC("Adec:%d, En:%d, Work:%d, Codec:%#x->%#x, enFmt:%#x.\n",
                 pstAttr->bEnable, pstAdecChan->beWork,
                 pstAdecChan->u32AdecChID, pstAdecChan->u32CodecID, pstAttr->u32CodecID, pstAdecChan->bPacketDecoder);

    if (HI_TRUE == pstAttr->bEnable)
    {
        if (HI_TRUE == pstAdecChan->beWork)
        {
            /* need change when protocal or buffer change */
            if ((pstAttr->u32CodecID != pstAdecChan->u32CodecID) || (pstAttr->u32OutBufNum != pstOutBuf->u32OutBufNum)
                || (pstAttr->u32InBufSize != pstInBuf->u32BufSize))
            {
                isChange = 1;
            }
            else
            {
                isChange = ADECCheckOpenParam((HI_HADECODE_OPENPARAM_S*)(&(ptDecAttr->decParam)), &(pstAttr->sOpenPram));

                /*none*/
            }
        }
        else
        {
            /* Get*/
            isChange = 1;
        }
    }
    else
    {
        if (HI_TRUE == pstAdecChan->beWork)
        {
            (RET_VOID)ADECDeInit_Channel(pstAdecChan);
			pstAdecChan->beWork = HI_FALSE;
            ADECResetProcInfo2(pstAdecChan);
        }

        /* if bEnable==HI_FALSE, only get InputAttr, dont allocate source */
        ret = ADECGetInputAttr(pstAdecChan, pstAttr);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_ADEC("ADECGetInputAttr err=0x%x\n", ret);
            return HI_FAILURE;
        }

        return HI_SUCCESS;
    }

    if (isChange)
    {
        if (HI_TRUE == pstAdecChan->beWork)
        {
            (RET_VOID)ADECDeInit_Channel(pstAdecChan);
        }

        (RET_VOID)ADECGetInputAttr(pstAdecChan, pstAttr);

        HI_INFO_ADEC("Adec:%d, Codec:%#x.\n", pstAdecChan->u32AdecChID, pstAdecChan->u32CodecID);
        ret = ADECInitChannel(pstAdecChan);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_ADEC("ADECInitChannel err=0x%x\n", ret);

            /* if ADECInitChannel failed, pstAdecChan->beWork should be HI_FALSE */
            if (HI_TRUE == pstAdecChan->beWork)
            {
                pstAdecChan->beWork = HI_FALSE;
            }

            return HI_FAILURE;
        }
		ADECResetProcInfo2(pstAdecChan);
    }

    return HI_SUCCESS;
}

HI_S32 ADEC_Init(const HI_CHAR* pszCodecNameTable[])
{
    HI_S32 i;

    for (i = 0; i < ADEC_INSTANCE_MAXNUM; i++)
    {
        g_pstAdecChan[i] = NULL;
    }

    g_bAdecInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 ADEC_deInit(HI_VOID)
{
    g_bAdecInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_VOID* ADEC_DecThread(HI_VOID* arg)
{
    HI_HANDLE hAdec = (HI_HANDLE)arg;
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_INFO_S*   ptDecAttr = HI_NULL_PTR;

    if (hAdec >= ADEC_INSTANCE_MAXNUM)
    {
        return HI_NULL;
    }

    pstAdecChan = g_pstAdecChan[hAdec];

    pstAdecChan->pstAdecInfo->u32ThreadId = syscall(__NR_gettid);

    while (pstAdecChan->AdecThreadRun)
    {
        HI_SYS_GetTimeStampMs(&pstAdecChan->pstAdecInfo->ThreadBeginTime);

        if ((pstAdecChan->pstAdecInfo->ThreadBeginTime - pstAdecChan->pstAdecInfo->ThreadEndTime > ADEC_SCHE_THREADTIME_LIMIT)
            && (0 != pstAdecChan->pstAdecInfo->ThreadEndTime))
        {
            pstAdecChan->pstAdecInfo->ThreadScheTimeOutCnt++;
        }

        ADEC_LOCK(&g_AdecDataMutex[hAdec]);
        ptDecAttr = &(pstAdecChan->decAttr);
        if (ptDecAttr->hDecoder == HI_NULL)
        {
            ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
            (HI_VOID)usleep(ADEC_SYS_SLEEP_TIME * 1000);
            continue;
        }

        if ((pstAdecChan->beAssigned == HI_TRUE) && (pstAdecChan->beWork == HI_TRUE))
        {

#ifdef HA_HW_CODEC_SUPPORT
            if (HI_TRUE == pstAdecChan->bHwDecoder)
            {
                ADECHwDecode(pstAdecChan);
            }
            else
#endif
            {
                (RET_VOID) ADECSwDecode( pstAdecChan );
                if (HI_FALSE == pstAdecChan->bPacketDecoder)
                {
                    // pop sound only in non-Packet sw-decode mode
                    ADECCheckScrambler(hAdec, pstAdecChan->s32BsConsumeBytes);
                    pstAdecChan->s32BsConsumeBytes = 0;
                }
            }

            ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);

            HI_SYS_GetTimeStampMs(&pstAdecChan->pstAdecInfo->ThreadEndTime);

            if (pstAdecChan->pstAdecInfo->ThreadEndTime - pstAdecChan->pstAdecInfo->ThreadBeginTime > ADEC_EXE_THREADTIME_LIMIT)
            {
                pstAdecChan->pstAdecInfo->ThreadExeTimeOutCnt++;
            }

            //dynamically change sleep time
            if((HI_U32)pstAdecChan->pstAdecInfo->enSampleRate)
            {
                if(!pstAdecChan->pstAdecInfo->u32PcmSamplesPerFrame) //only work on passthrough status
                {
                    pstAdecChan->pstAdecInfo->u32AdecSystemSleepTime = ADEC_SYS_SLEEP_TIME;
                }
                else
                {
                    HI_U32 u32FrameDuration = ADEC_SYS_SLEEP_TIME;
                    u32FrameDuration = (HI_U32)(pstAdecChan->pstAdecInfo->u32PcmSamplesPerFrame * 1000 /
                                                (HI_U32)pstAdecChan->pstAdecInfo->enSampleRate);

                    if (u32FrameDuration < ADEC_MIN_SLEEP_TIME)
                    {
                        u32FrameDuration = ADEC_MIN_SLEEP_TIME;
                    }

                    pstAdecChan->pstAdecInfo->u32AdecSystemSleepTime = 
                        (u32FrameDuration > ADEC_SYS_SLEEP_TIME) ? ADEC_SYS_SLEEP_TIME : u32FrameDuration;
                }
            }
            else
            {
                pstAdecChan->pstAdecInfo->u32AdecSystemSleepTime = ADEC_SYS_SLEEP_TIME;
            }
            (HI_VOID)usleep(pstAdecChan->pstAdecInfo->u32AdecSystemSleepTime * 1000);            
           
        }
        else
        {
            ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
            HI_SYS_GetTimeStampMs(&pstAdecChan->pstAdecInfo->ThreadEndTime);

            if (pstAdecChan->pstAdecInfo->ThreadEndTime - pstAdecChan->pstAdecInfo->ThreadBeginTime > ADEC_EXE_THREADTIME_LIMIT)
            {
                pstAdecChan->pstAdecInfo->ThreadExeTimeOutCnt++;
            }
            (HI_VOID)usleep(ADEC_SYS_SLEEP_TIME * 1000);
        }
        
    }

    return HI_NULL;
}

HI_S32 ADEC_Open(HI_HANDLE* phAdec)
{
    HI_S32 i;
    HI_S32 nRet;

    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_ATTR_S sAdecDefaultAttr;

    HI_VOID* pBase;
    HI_U32 chan_id = 0xffffffff;

    if (g_bAdecInit != HI_TRUE)
    {
        HI_ERR_ADEC("adec module is not init t\n");
        return HI_FAILURE;
    }

    //first search source
    for (i = 0; i < ADEC_INSTANCE_MAXNUM; i++)
    {
        if (!g_pstAdecChan[i])
        {
            chan_id = i;
            break;
        }
    }

    if (chan_id == 0xffffffff)
    {
        HI_ERR_ADEC("source is not enough to support so much adec\n");
        return HI_FAILURE;
    }

#ifdef HI_ADEC_AUDSPECTRUM_SUPPORT
    g_pu32Bufffer[chan_id] = (HI_U32*)HI_MALLOC(HI_ID_ADEC, ADEC_MAX_AO_OUT_SAMPLE_PERFRAME
                             * ADEC_AUD_MAX_CHANNELS + 1 );
    if (NULL == g_pu32Bufffer[chan_id])
    {
        HI_ERR_ADEC("malloc AUDSPECTRUM buffer fail\n");
        return HI_FAILURE;
    }
#endif


    pBase = (HI_VOID*)HI_MALLOC(HI_ID_ADEC, sizeof(ADEC_CHAN_S));
    if (NULL == pBase)
    {
#ifdef HI_ADEC_AUDSPECTRUM_SUPPORT
        HI_FREE(HI_ID_ADEC, g_pu32Bufffer[chan_id]);
        g_pu32Bufffer[chan_id] = NULL;
#endif
        HI_ERR_ADEC("malloc ADEC_CHAN_S fail\n");
        return HI_FAILURE;
    }

    memset(pBase, 0, sizeof(ADEC_CHAN_S));

    pstAdecChan = ((ADEC_CHAN_S*)pBase);

    pstAdecChan->beWork = HI_FALSE;
    pstAdecChan->AdecDevFd = -1;
    pstAdecChan->bPacketDecoder = HI_FALSE;

    pstAdecChan->midState.u32LastFrameChannels  = 2;
    pstAdecChan->midState.enLastFrameSmaplerate = HI_UNF_SAMPLE_RATE_48K;

    (RET_VOID)ADECGetDefalutOpenParam(&sAdecDefaultAttr);
    (RET_VOID)ADECGetInputAttr(pstAdecChan, &sAdecDefaultAttr);

    pstAdecChan->u32AdecChID = chan_id;
    pstAdecChan->beAssigned = HI_TRUE;
    pstAdecChan->decAttr.pHaDecoderDev   = HI_NULL;
    pstAdecChan->decAttr.pAudPrivDataBak = HI_NULL;
    pstAdecChan->decAttr.u32AudPrivDataBakDize = 0;

    pstAdecChan->u32NotEnoughBufCnt = 0;
    pstAdecChan->u32TotalAdecInByte = 0;
    pstAdecChan->u32TotalAdecTime = 0;
    pstAdecChan->pfEs = HI_NULL;
    pstAdecChan->pfPcm = HI_NULL;

    memset(&pstAdecChan->stFrameInfo, 0, sizeof(ADEC_FRAME_INFO_S));
    
    g_pstAdecChan[chan_id] = pstAdecChan;

    ADEC_LOCK(&g_AdecApiMutex[chan_id]);
    ADEC_LOCK(&g_AdecDataMutex[chan_id]);

    nRet = ADECOpenChannel(pstAdecChan);

    //HI_MPI_ADEC_RetUserErr(nRet, &pstAdecChan->mutex);
    if (HI_SUCCESS != nRet)
    {
        HI_ERR_ADEC(" DrvErrCode =0x%x\n", nRet);
        ADEC_UNLOCK(&g_AdecDataMutex[chan_id]);
        ADEC_UNLOCK(&g_AdecApiMutex[chan_id]);
#ifdef HI_ADEC_AUDSPECTRUM_SUPPORT
        HI_FREE(HI_ID_ADEC, g_pu32Bufffer[chan_id]);
        g_pu32Bufffer[chan_id] = NULL;
#endif
        HI_FREE(HI_ID_ADEC, (HI_VOID*)(pstAdecChan));
        g_pstAdecChan[chan_id] = NULL;
        return nRet;
    }

    pstAdecChan->u32Volume = ADEC_MAX_VOLUME;
    pstAdecChan->pstAdecInfo->u32Volume = ADEC_MAX_VOLUME;
    pstAdecChan->s16VolumeFrac = 0x7fff;
    ADEC_UNLOCK(&g_AdecDataMutex[chan_id]);
    ADEC_UNLOCK(&g_AdecApiMutex[chan_id]);

    *phAdec = chan_id;
    pstAdecChan->AdecThreadRun = HI_TRUE;
    nRet = pthread_create(&pstAdecChan->AdecThreadInst, HI_NULL, ADEC_DecThread, (HI_VOID*)(*phAdec));
    if (HI_SUCCESS != nRet)
    {
		HI_ERR_ADEC("ADEC Create Thread err \n");
		pstAdecChan->AdecThreadRun = HI_FALSE;
		ADECCloseChannel(pstAdecChan);
#ifdef HI_ADEC_AUDSPECTRUM_SUPPORT
		HI_FREE(HI_ID_ADEC, g_pu32Bufffer[chan_id]);
		g_pu32Bufffer[chan_id] = NULL;
#endif
		HI_FREE(HI_ID_ADEC, (HI_VOID*)(pstAdecChan));
		g_pstAdecChan[chan_id] = NULL;
        return HI_FAILURE;
    }

    HI_SYS_GetTimeStampMs(&pstAdecChan->u32StartTime);

    return HI_SUCCESS;
}

/****************************************************************************
 * Function:    ADEC_Close
 *
 * Description: Close Audio Codec
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
HI_S32 ADEC_Close(HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_ATTR_S sAdecDefaultAttr;

    CHECK_ADEC_HANDLE(hAdec);

    pstAdecChan = g_pstAdecChan[hAdec];

    if (!pstAdecChan)
    {
        return HI_FAILURE;
    }
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    if (HI_FALSE == pstAdecChan->beAssigned)
    {
	    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
        return HI_SUCCESS;
    }

    pstAdecChan->AdecThreadRun = HI_FALSE;
    (HI_VOID)pthread_join(pstAdecChan->AdecThreadInst, HI_NULL);

    ADEC_LOCK(&g_AdecDataMutex[hAdec]);

    if (HI_TRUE == pstAdecChan->beWork)
    {
        (RET_VOID)ADECDeInit_Channel(pstAdecChan );
        pstAdecChan->beWork = HI_FALSE;
    }

    ADECCloseChannel(pstAdecChan);
    pstAdecChan->beAssigned  = HI_FALSE;
    pstAdecChan->u32AdecChID = (HI_U32) - 1;
    (RET_VOID)ADECGetDefalutOpenParam(&sAdecDefaultAttr);
    (RET_VOID)ADECGetInputAttr(pstAdecChan, &sAdecDefaultAttr);
    ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);

    HI_FREE(HI_ID_ADEC, (HI_VOID*)(pstAdecChan));
    g_pstAdecChan[hAdec] = NULL;

#ifdef HI_ADEC_AUDSPECTRUM_SUPPORT
    if (g_pu32Bufffer[hAdec])
    {
        HI_FREE(HI_ID_ADEC, (HI_VOID*)(g_pu32Bufffer[hAdec]));
        g_pu32Bufffer[hAdec] = NULL;
    }
#endif


    return HI_SUCCESS;
}

HI_S32 ADEC_SetAttr(HI_HANDLE hAdec, HI_U32 u32Command, void* pstParam)
{
    HI_S32 nRet = HI_SUCCESS;
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;

    ADEC_ATTR_S stAllAttr;
    memset(&stAllAttr, 0, sizeof(ADEC_ATTR_S));

    /* check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstParam);

    //------------1 . first  get attr -------------------
    nRet = ADEC_GetAttr(hAdec, ADEC_ATTR_ALLATTR, &stAllAttr);
    if (HI_SUCCESS != nRet)
    {
        HI_ERR_ADEC(" ADEC_SetAttr GetAttr ADEC_ALLATTR   fail: nRet =0x%x\n", nRet);
        return nRet;
    }

    //------------2 . update adec attr ----------------
    switch (u32Command)
    {
        case ADEC_ATTR_CODECID:
            HI_INFO_ADEC("ADEC_SetAttr : Set ADEC_CODECID");
            stAllAttr.u32CodecID = *(HI_U32*)pstParam;
            break;

        case  ADEC_ATTR_WORKSTATE:
            HI_INFO_ADEC("ADEC_SetAttr : Set ADEC_WORKSTATE");
            stAllAttr.bEnable = *(HI_BOOL*)pstParam;
            break;

        case ADEC_ATTR_INBUFSIZE:
            HI_INFO_ADEC("ADEC_SetAttr : Set ADEC_INBUFSIZE");
            stAllAttr.u32InBufSize = *(HI_U32*)pstParam;
            break;
        case ADEC_ATTR_EosStateFlag:
            HI_INFO_ADEC("ADEC_SetAttr : Set ADEC_ATTR_EosStateFlag");
            stAllAttr.bEosState = *(HI_BOOL*)pstParam;
            break;
        case ADEC_ATTR_OUTBUFNUM:
            HI_INFO_ADEC("ADEC_SetAttr : Set ADEC_OUTBUFNUM");
            stAllAttr.u32OutBufNum = *(HI_U32*)pstParam;
            break;

        case ADEC_ATTR_DECOPENPARAM:
            HI_INFO_ADEC("ADEC_SetAttr : Set ADEC_DECOPENPARAM");
            memset(&(stAllAttr.sOpenPram), 0, sizeof(HI_HADECODE_OPENPARAM_S));
            memcpy(&(stAllAttr.sOpenPram), (HI_HADECODE_OPENPARAM_S*)pstParam, sizeof(HI_HADECODE_OPENPARAM_S));
            break;

        case ADEC_ATTR_ALLATTR:
            HI_INFO_ADEC("ADEC_SetAttr : Set ADEC_ALLATTR");
            memset(&stAllAttr, 0, sizeof(ADEC_ATTR_S));
            memcpy(&stAllAttr, (ADEC_ATTR_S*)pstParam, sizeof(ADEC_ATTR_S));
            break;

        default:
            HI_ERR_ADEC(" ADEC_SetAttr fail: INVALID PARAM = 0x%x\n", u32Command);
            return HI_FAILURE;
    }

    nRet = ADECCheckInBufAttr(&stAllAttr);
    if (HI_SUCCESS != nRet)
    {
        HI_ERR_ADEC(" ADECCheckInBufAttr fail: nRet =0x%x\n", nRet);
        return nRet;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    ADEC_LOCK(&g_AdecDataMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beAssigned, &g_AdecDataMutex[hAdec], &g_AdecApiMutex[hAdec]);

    /* check if initialized, update attr to global variable*/
    pstAdecChan->bAdecEosFlag = stAllAttr.bEosState;
    nRet = ADECheckInputAttr(pstAdecChan, &stAllAttr);
    HI_MPI_ADEC_RetUserErrARG2(nRet, &g_AdecDataMutex[hAdec], &g_AdecApiMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);

    return HI_SUCCESS;
}

/****************************************************************************
 * Function:    ADEC_GetAttr
 *
 * Description: Get Audio Codec Attribute
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
HI_S32 ADEC_GetAttr(HI_HANDLE hAdec, HI_U32 u32Command, void*  pstAttr)
{
    ADEC_INFO_S*   ptDecAttr = HI_NULL_PTR;
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf  = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;

    /* check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstAttr);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);

    CHECK_ADEC_STATE(pstAdecChan->beAssigned, &g_AdecApiMutex[hAdec]);

    switch (u32Command)
    {
        case ADEC_ATTR_CODECID:
            HI_INFO_ADEC("ADEC_GetAttr : Get ADEC_CODECID");
            *(HI_U32*)pstAttr = pstAdecChan->u32CodecID;
            break;

        case  ADEC_ATTR_WORKSTATE:
            HI_INFO_ADEC("ADEC_GetAttr : Get ADEC_WORKSTATE");
            *(HI_BOOL*)pstAttr = pstAdecChan->beWork;
            break;

        case ADEC_ATTR_INBUFSIZE:
            HI_INFO_ADEC("ADEC_GetAttr : Get ADEC_INBUFSIZE");
            pstInBuf = &(pstAdecChan->InStreamBuf);
            *(HI_U32*)pstAttr = pstInBuf->u32BufSize;
            break;
        case ADEC_ATTR_EosStateFlag:
            HI_INFO_ADEC("ADEC_GetAttr : ADEC_ATTR_EosStateFlag");
            *(HI_BOOL*)pstAttr = pstAdecChan->bAdecEosFlag;
            break;
        case ADEC_ATTR_OUTBUFNUM:
            HI_INFO_ADEC("ADEC_GetAttr : Get ADEC_OUTBUFNUM");
            pstOutBuf = &(pstAdecChan->outStreamBuf);
            *(HI_U32*)pstAttr = pstOutBuf->u32OutBufNum;
            break;

        case ADEC_ATTR_DECOPENPARAM:
            HI_INFO_ADEC("ADEC_GetAttr : Get ADEC_DECOPENPARAM");
            ptDecAttr = &(pstAdecChan->decAttr);
            memset((HI_HADECODE_OPENPARAM_S*)pstAttr, 0, sizeof(HI_HADECODE_OPENPARAM_S));
            memcpy((HI_HADECODE_OPENPARAM_S*)pstAttr, &(ptDecAttr->decParam), sizeof(HI_HADECODE_OPENPARAM_S));
            break;

        case ADEC_ATTR_ALLATTR:
            HI_INFO_ADEC("ADEC_GetAttr : Get ADEC_ALLATTR");
            ptDecAttr = &(pstAdecChan->decAttr);
            pstInBuf  = &(pstAdecChan->InStreamBuf);
            pstOutBuf = &(pstAdecChan->outStreamBuf);
            memset(&(((ADEC_ATTR_S*)pstAttr)->sOpenPram), 0, sizeof(HI_HADECODE_OPENPARAM_S));
            memcpy(&(((ADEC_ATTR_S*)pstAttr)->sOpenPram), &(ptDecAttr->decParam),
                   sizeof(HI_HADECODE_OPENPARAM_S));
            ((ADEC_ATTR_S*)pstAttr)->u32CodecID    = pstAdecChan->u32CodecID;
            ((ADEC_ATTR_S*)pstAttr)->u32InBufSize  = pstInBuf->u32BufSize;
            ((ADEC_ATTR_S*) pstAttr)->u32OutBufNum = pstOutBuf->u32OutBufNum;
            ((ADEC_ATTR_S*)pstAttr)->bEnable   = pstAdecChan->beWork;
            ((ADEC_ATTR_S*)pstAttr)->bEosState = pstAdecChan->bAdecEosFlag;
            break;

        default:
            HI_ERR_ADEC(" ADEC_GetAttr fail: INVALID PARAM = 0x%x\n", u32Command);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return HI_FAILURE;
    }
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}

/****************************************************************************
 * Function:    ADEC_SendStream
 *
 * Description: Send Audio Stream
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
HI_S32 ADEC_SendStream (HI_HANDLE hAdec, const HI_UNF_STREAM_BUF_S* pstStream, HI_U32 u32PtsMs)
{
    HI_S32 sRet = HI_SUCCESS;
    static FILE* fEstream = NULL;

    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PTS_QUE_S*   pstPTSQue     = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo   = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstStream);

    if (pstStream->u32Size == 0)
    {
        HI_WARN_ADEC("stream u32Size is 0 \n" );
        return HI_SUCCESS;
    }

    /* more check, required? */
    if ((pstStream->u32Size > ADEC_MAX_INPUT_BLOCK_SIZE) || (pstStream->pu8Data == HI_NULL_PTR))
    {
        HI_ERR_ADEC("stream u32Bytes(%u) exceed maxsize(%d) or invaid pu8Data(0x%x)!\n",
                    pstStream->u32Size,
                    ADEC_MAX_INPUT_BLOCK_SIZE,
                    pstStream->pu8Data );
        return HI_FAILURE;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    ADEC_LOCK(&g_AdecIOMutex[hAdec]);//IO
    CHECK_ADEC_STATEARG2(pstAdecChan->beAssigned, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beWork, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);

    pstPTSQue = &(pstAdecChan->PTSQue);
    pstInBuf = &(pstAdecChan->InStreamBuf);
    pstAdecInfo = pstAdecChan->pstAdecInfo;

    if (HI_TRUE == ADECIsPTSFull(pstPTSQue))
    {
        ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
        ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
        return HI_ERR_ADEC_IN_PTSBUF_FULL;
    }

    if (HI_TRUE == pstAdecChan->bPacketDecoder)
    {
        if (HI_TRUE == ADECIsPacketFull(pstAdecChan->pstPacketQue))
        {
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return HI_ERR_ADEC_IN_PTSBUF_FULL;
        }
    }
#ifdef HA_HW_CODEC_SUPPORT
    HI_S32 s32Ret;
    HI_UNF_STREAM_BUF_S stStream1;
    HI_UNF_STREAM_BUF_S stStream2;

    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        s32Ret = ADECHwGetBuffer(pstAdecChan, pstStream->u32Size, &stStream1, &stStream2);
        if (HI_SUCCESS != s32Ret)
        {
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return s32Ret;
        }

        ADECStorePTS(pstPTSQue, pstInBuf, u32PtsMs, pstStream->u32Size, pstAdecChan->bPacketDecoder);
        if (HI_TRUE == pstAdecChan->bPacketDecoder)
        {
            ADECStorePacket(pstAdecChan, u32PtsMs, pstStream->u32Size);
        }
        if (stStream2.u32Size > 0)
        {
            memcpy(stStream1.pu8Data, (HI_VOID*)pstStream->pu8Data, stStream1.u32Size);
            memcpy(stStream2.pu8Data, (HI_VOID*)(pstStream->pu8Data + stStream1.u32Size),
                   pstStream->u32Size - stStream1.u32Size);
            stStream2.u32Size = pstStream->u32Size - stStream1.u32Size;
        }
        else
        {
            memcpy(stStream1.pu8Data, (HI_VOID*)pstStream->pu8Data, pstStream->u32Size);
            stStream1.u32Size = pstStream->u32Size;
            stStream2.pu8Data = HI_NULL_PTR;
            stStream2.u32Size = 0;
        }
        s32Ret = ADECHwPutBuffer(pstAdecChan, &stStream1, &stStream2);
        if (s32Ret)
        {
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return HI_ERR_ADEC_IN_BUF_FULL;
        }
        pstInBuf->u32StreamWritePos = (pstInBuf->u32StreamWritePos
                                       + pstStream->u32Size) % (pstInBuf->u32Boundary);
        pstAdecChan->u32TotalAdecInByte += pstStream->u32Size;
    }
    else
#endif
    {
        /* Input Buffer full */
        if (pstInBuf->u32BufFree > pstStream->u32Size)
        {
            ADECStorePTS(pstPTSQue, pstInBuf, u32PtsMs, pstStream->u32Size, pstAdecChan->bPacketDecoder);
            if (HI_TRUE == pstAdecChan->bPacketDecoder)
            {
                ADECStorePacket(pstAdecChan, u32PtsMs, pstStream->u32Size);
            }

            /*Copy data into Input Buffer*/
            if (((HI_U32)pstInBuf->u32BufWritePos + pstStream->u32Size) <= pstInBuf->u32BufSize)
            {
                memcpy((HI_VOID*)(pstInBuf->pu8Data + pstInBuf->u32BufWritePos), (HI_VOID*)pstStream->pu8Data,
                       pstStream->u32Size);
            }
            else
            {
                memcpy((HI_VOID*)(pstInBuf->pu8Data
                                  + pstInBuf->u32BufWritePos), (HI_VOID*)pstStream->pu8Data,
                       (HI_U32)(pstInBuf->u32BufSize
                                - pstInBuf->u32BufWritePos));
                memcpy((HI_VOID*)pstInBuf->pu8Data, (HI_VOID*)(pstStream->pu8Data
                        + (HI_U32)(pstInBuf->u32BufSize
                                   - pstInBuf->u32BufWritePos)),
                       pstStream->u32Size - (HI_U32)(pstInBuf->u32BufSize - pstInBuf->u32BufWritePos));
            }

            /* recaculate free buffer size */
            pstInBuf->u32BufWritePos = (pstInBuf->u32BufWritePos + pstStream->u32Size) % (pstInBuf->u32BufSize);
            pstInBuf->u32StreamWritePos = (pstInBuf->u32StreamWritePos
                                           + pstStream->u32Size) % (pstInBuf->u32Boundary);
            pstInBuf->u32BufFree -= pstStream->u32Size;
            pstAdecChan->u32TotalAdecInByte += pstStream->u32Size;
        }
        else
        {
            /* no space for input buffer, we try to decode */
            sRet = HI_ERR_ADEC_IN_BUF_FULL;
        }
    }

    pstAdecInfo->u32BufWrite = pstInBuf->u32BufWritePos;
    ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);

    if ( pstAdecInfo->enEsCtrlState == ADEC_CMD_CTRL_START )
    {
        if (!fEstream)
        {
            fEstream = fopen(pstAdecInfo->filePath, "wb");
            if (!fEstream)
            {
                HI_ERR_ADEC("can not open file (%s)\n", pstAdecInfo->filePath);
            }
        }
        if (fEstream)
        {
            HI_S32 s32Len = fwrite(pstStream->pu8Data, 1, pstStream->u32Size, fEstream);
            if (pstStream->u32Size != s32Len)
            {
                HI_ERR_ADEC("write (%s) failed\n", pstAdecInfo->filePath);
                fclose(fEstream);
                fEstream = NULL;
                pstAdecInfo->enEsCtrlState = ADEC_CMD_CTRL_STOP;
            }
        }
    }
    if ( pstAdecInfo->enEsCtrlState == ADEC_CMD_CTRL_STOP )
    {
        if (fEstream)
        {
            fclose(fEstream);
            fEstream = NULL;
        }
    }

    return sRet;
}

HI_S32 ADEC_GetBuffer (HI_HANDLE hAdec, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream1,
                       HI_UNF_STREAM_BUF_S* pstStream2)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_MIDSTATE_S* pstMidState = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf = HI_NULL_PTR;
    ADEC_PTS_QUE_S*   pstPTSQue = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstStream1);
    CHECK_ADEC_NULL_PTR(pstStream2);

    if (u32RequestSize == 0)
    {
        HI_WARN_ADEC("u32RequestSize == 0!\n");
        return HI_SUCCESS;
    }

    /* more check, required? */
    if (u32RequestSize > ADEC_MAX_INPUT_BLOCK_SIZE)
    {
        HI_WARN_ADEC("want stream u32Bytes big than %d !\n", ADEC_MAX_INPUT_BLOCK_SIZE );
        return HI_FAILURE;
    }

    if (HI_FALSE == g_pstAdecChan[hAdec]->beWork)
    {
        pstStream1->pu8Data = (HI_U8*)HI_NULL_PTR;
        pstStream1->u32Size = 0;
        pstStream2->pu8Data = (HI_U8*)HI_NULL_PTR;
        pstStream2->u32Size = 0;
        return HI_ERR_ADEC_IN_BUF_FULL;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    ADEC_LOCK(&g_AdecIOMutex[hAdec]);

    CHECK_ADEC_STATEARG2(pstAdecChan->beAssigned, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beWork, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);

    pstInBuf = &(pstAdecChan->InStreamBuf);
    pstMidState = &(pstAdecChan->midState);
    pstPTSQue = &(pstAdecChan->PTSQue);

    if (HI_TRUE == ADECIsPTSFull(pstPTSQue))
    {
        ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
        ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
        return HI_ERR_ADEC_IN_PTSBUF_FULL;
    }

    if (HI_TRUE == pstAdecChan->bPacketDecoder)
    {
        if (HI_TRUE == ADECIsPacketFull(pstAdecChan->pstPacketQue))
        {
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return HI_ERR_ADEC_IN_PTSBUF_FULL;
        }
    }
#ifdef HA_HW_CODEC_SUPPORT
    HI_S32 s32Ret;
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        s32Ret = ADECHwGetBuffer(pstAdecChan, u32RequestSize, pstStream1, pstStream2);
        if (HI_SUCCESS != s32Ret)
        {
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return s32Ret;
        }
    }
    else
#endif
    {
        /* Input Buffer full */
        if (pstInBuf->u32BufFree > u32RequestSize)
        {
            if ((((HI_U32)pstInBuf->u32BufWritePos + u32RequestSize)) <= pstInBuf->u32BufSize)
            {
                pstStream1->pu8Data = (HI_U8*)(pstInBuf->pu8Data + pstInBuf->u32BufWritePos);
                pstStream1->u32Size = u32RequestSize;
                pstStream2->pu8Data = (HI_U8*)HI_NULL_PTR;
                pstStream2->u32Size = 0;
            }
            else
            {
                pstStream1->pu8Data = (HI_U8*)(pstInBuf->pu8Data + pstInBuf->u32BufWritePos);
                pstStream1->u32Size = (pstInBuf->u32BufSize - (HI_U32)pstInBuf->u32BufWritePos);
                pstStream2->pu8Data = (HI_U8*)pstInBuf->pu8Data;
                pstStream2->u32Size = u32RequestSize
                                      - (HI_U32)(pstInBuf->u32BufSize - (HI_U32)pstInBuf->u32BufWritePos);
            }
        }
        else
        {
            /* input buffer is full */
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return HI_ERR_ADEC_IN_BUF_FULL;
        }
    }
    /*recode*/
    memcpy(&pstMidState->lastPkt[0], pstStream1, sizeof(HI_UNF_STREAM_BUF_S));
    memcpy(&pstMidState->lastPkt[1], pstStream2, sizeof(HI_UNF_STREAM_BUF_S));
    ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}

HI_S32 ADEC_PutBuffer (HI_HANDLE hAdec, const HI_UNF_STREAM_BUF_S* pstStream1,
                       const HI_UNF_STREAM_BUF_S* pstStream2,
                       HI_U32 u32PtsMs)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PTS_QUE_S*   pstPTSQue     = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo   = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf = HI_NULL_PTR;
    ADEC_MIDSTATE_S* pstMidState    = HI_NULL_PTR;
    HI_U32 u32BsSize;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstStream1);
    CHECK_ADEC_NULL_PTR(pstStream2);

    /* more check, required */
    if ((pstStream1->u32Size + pstStream2->u32Size) > ADEC_MAX_INPUT_BLOCK_SIZE)
    {
        HI_ERR_ADEC("stream1 u32Size(%d)+ pstStream2 u32Size(%d) exceed maxsize(%d) \n",
                    ADEC_MAX_INPUT_BLOCK_SIZE );
        return HI_FAILURE;
    }

    if ((pstStream1->pu8Data == HI_NULL_PTR)
        || ((pstStream2->u32Size) && (pstStream2->pu8Data == HI_NULL_PTR)))
    {
        HI_ERR_ADEC("invalid pstStream1->pu8Data(0x%x) or pstStream2->pu8Data(0x%x) \n",
                    pstStream1->pu8Data,
                    pstStream2->pu8Data);
        return HI_FAILURE;
    }

    if ((pstStream1->u32Size + pstStream2->u32Size) == 0)
    {
        HI_WARN_ADEC(" (pstStream1->u32Size + pstStream2->u32Size) == 0 \n");
        return HI_SUCCESS;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    ADEC_LOCK(&g_AdecIOMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beAssigned, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beWork, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);

    pstPTSQue = &(pstAdecChan->PTSQue);
    pstInBuf = &(pstAdecChan->InStreamBuf);
    pstAdecInfo = pstAdecChan->pstAdecInfo;

    pstMidState = &(pstAdecChan->midState);
    u32BsSize = pstStream1->u32Size + pstStream2->u32Size;
#ifdef HA_HW_CODEC_SUPPORT
    HI_S32 s32Ret;

    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {

        s32Ret = ADECHwPutBuffer(pstAdecChan, pstStream1, pstStream2);
        if (HI_SUCCESS != s32Ret)
        {
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return HI_ERR_ADEC_IN_BUF_FULL;
        }
        ADECStorePTS(pstPTSQue, pstInBuf, u32PtsMs, u32BsSize, pstAdecChan->bPacketDecoder);
        if (HI_TRUE == pstAdecChan->bPacketDecoder)
        {
            ADECStorePacket(pstAdecChan, u32PtsMs, u32BsSize);
        }
        pstInBuf->u32StreamWritePos = (pstInBuf->u32StreamWritePos + u32BsSize) % (pstInBuf->u32Boundary);
        pstAdecChan->u32TotalAdecInByte += u32BsSize;
    }
    else
#endif
    {

        //check
        if (u32BsSize > pstInBuf->u32BufFree)
        {
            //HI_INFO_ADEC(":u32BsSize%(d) bigger than u32BufFree(%d) \n", u32BsSize,pstInBuf->u32BufFree);
            HI_MPI_ADEC_RetUserErr2ARG2(HI_ERR_ADEC_IN_BUF_FULL, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
        }

        if (pstStream2->u32Size)
        {
            if (pstStream1->u32Size != (pstMidState->lastPkt[0]).u32Size)
            {
                HI_ERR_ADEC("pstStream1 u32Size(%d) != lastPkt[0].u32Size(%d)\n", pstStream1->u32Size,
                            (pstMidState->lastPkt[0]).u32Size);

                HI_MPI_ADEC_RetUserErr2ARG2(HI_FAILURE, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
            }

            if (((pstStream1->pu8Data + pstStream1->u32Size) != (pstInBuf->pu8Data + pstInBuf->u32BufSize))
                || (pstStream2->pu8Data != pstInBuf->pu8Data))
            {
                HI_ERR_ADEC("Stream1 pu8Data(0x%x),Stream1 u32Size(0x%x) \n", pstStream1->pu8Data,
                            pstStream1->u32Size);
                HI_ERR_ADEC("Stream2 pu8Data(0x%x),Stream2 u32Size(0x%x) \n", pstStream2->pu8Data,
                            pstStream2->u32Size);
                HI_ERR_ADEC("pstInBuf->pu8Data(0x%x),pstInBuf->u32BufSize(0x%x) \n", pstInBuf->pu8Data,
                            pstInBuf->u32BufSize);
                HI_MPI_ADEC_RetUserErr2ARG2(HI_FAILURE, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
            }

            if ((pstStream2->u32Size > (pstMidState->lastPkt[1]).u32Size)
                || (pstStream2->pu8Data != (pstMidState->lastPkt[1]).pu8Data))
            {
                HI_ERR_ADEC("Stream2 pu8Data(0x%x),Stream2 u32Size(0x%x) \n", pstStream2->pu8Data,
                            pstStream2->u32Size);
                HI_ERR_ADEC("lastPkt[1].pu8Data(0x%x),lastPkt[1].u32Size(0x%x) \n",
                            (pstMidState->lastPkt[1]).pu8Data,
                            (pstMidState->lastPkt[1]).u32Size);
                HI_MPI_ADEC_RetUserErr2ARG2(HI_FAILURE, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
            }
        }

        if ((pstStream1->u32Size > (pstMidState->lastPkt[0]).u32Size)
            || (pstStream1->pu8Data != (pstMidState->lastPkt[0]).pu8Data))
        {
            HI_ERR_ADEC("pstStream1 pu8Data(0x%x),pstStream1 u32Size(0x%x) \n", pstStream1->pu8Data,
                        pstStream1->u32Size);
            HI_ERR_ADEC("lastPkt[0].pu8Data(0x%x),lastPkt[0].u32Size(0x%x) \n",
                        (pstMidState->lastPkt[0]).pu8Data,
                        (pstMidState->lastPkt[0]).u32Size);

            HI_MPI_ADEC_RetUserErr2ARG2(HI_FAILURE, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);

        }

        ADECStorePTS(pstPTSQue, pstInBuf, u32PtsMs, u32BsSize, pstAdecChan->bPacketDecoder);
        if (HI_TRUE == pstAdecChan->bPacketDecoder)
        {
            ADECStorePacket(pstAdecChan, u32PtsMs, u32BsSize);
        }
        pstInBuf->u32BufWritePos = ((HI_U32)pstInBuf->u32BufWritePos + u32BsSize) % (pstInBuf->u32BufSize);
        pstInBuf->u32StreamWritePos = (pstInBuf->u32StreamWritePos + u32BsSize) % (pstInBuf->u32Boundary);
        pstInBuf->u32BufFree -= u32BsSize;
        pstAdecChan->u32TotalAdecInByte += (pstStream1->u32Size + pstStream2->u32Size);
    }
    pstAdecInfo->u32BufWrite = (HI_U32)pstInBuf->u32BufWritePos;
    ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);

    if ( pstAdecInfo->enEsCtrlState == ADEC_CMD_CTRL_START )
    {
        if (!pstAdecChan->pfEs)
        {
            pstAdecChan->pfEs = fopen(pstAdecInfo->filePath, "wb");
            if (!pstAdecChan->pfEs)
            {
                HI_ERR_ADEC("can not open file (%s)\n", pstAdecInfo->filePath);
            }
        }
        if (pstAdecChan->pfEs)
        {
            HI_S32 s32Len = fwrite(pstStream1->pu8Data, 1, pstStream1->u32Size, pstAdecChan->pfEs);   // discard PTS
            if (pstStream1->u32Size != s32Len)
            {
                HI_ERR_ADEC("write (%s) failed\n", pstAdecInfo->filePath);
                fclose(pstAdecChan->pfEs);
                pstAdecChan->pfEs = HI_NULL;
                pstAdecInfo->enEsCtrlState = ADEC_CMD_CTRL_STOP;
            }
            else
            {
                s32Len = fwrite(pstStream2->pu8Data, 1, pstStream2->u32Size, pstAdecChan->pfEs);   // discard PTS
                if (pstStream2->u32Size != s32Len)
                {
                    HI_ERR_ADEC("write (%s) failed\n", pstAdecInfo->filePath);
                    fclose(pstAdecChan->pfEs);
                    pstAdecChan->pfEs = HI_NULL;
                    pstAdecInfo->enEsCtrlState = ADEC_CMD_CTRL_STOP;
                }
            }
        }
    }
    if ( pstAdecInfo->enEsCtrlState == ADEC_CMD_CTRL_STOP )
    {
        if (pstAdecChan->pfEs)
        {
            fclose(pstAdecChan->pfEs);
            pstAdecChan->pfEs = HI_NULL;
        }
    }
    
    return HI_SUCCESS;
}

HI_S32 ADEC_GetBufferStatus (HI_HANDLE hAdec, ADEC_BUFSTATUS_S* pstBufStatus)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf = HI_NULL_PTR;
    HI_U32 u32DitherWaterline = 5;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstBufStatus);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);

    CHECK_ADEC_STATE(pstAdecChan->beAssigned, &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATE_WARNING(pstAdecChan->beWork, &g_AdecApiMutex[hAdec]);
    pstInBuf = &(pstAdecChan->InStreamBuf);
#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        HI_HA_STATUS_INFO_S stStatus;
        HI_U32 u32BufFree;
        memset(&stStatus,0,sizeof(HI_HA_STATUS_INFO_S));
        
        ADECHwGetStatusInfo(pstAdecChan, &stStatus);
        if (stStatus.u32InBufReadPos <= stStatus.u32InBufWritePos)
        {
            u32BufFree = pstInBuf->u32BufSize - (stStatus.u32InBufWritePos - stStatus.u32InBufReadPos);
        }
        else
        {
            u32BufFree = stStatus.u32InBufReadPos - stStatus.u32InBufWritePos;
        }
        pstBufStatus->u32BufWritePos = stStatus.u32InBufWritePos;
        pstBufStatus->s32BufReadPos = stStatus.u32InBufReadPos;
        pstBufStatus->u32BufferUsed = pstInBuf->u32BufSize - u32BufFree;
        pstBufStatus->u32BufferAvailable = u32BufFree;
    }
    else
#endif
    {
        pstBufStatus->u32BufWritePos = pstInBuf->u32BufWritePos;
        pstBufStatus->s32BufReadPos = pstInBuf->s32BufReadPos;
        pstBufStatus->u32BufferUsed = pstInBuf->u32BufSize - pstInBuf->u32BufFree;
        pstBufStatus->u32BufferAvailable = pstInBuf->u32BufFree;
    }

    pstBufStatus->u32BufferSize = pstInBuf->u32BufSize;
    pstBufStatus->u32TotDecodeFrame = (HI_U32)(pstAdecChan->pstAdecInfo->u32FramnNm);
    pstBufStatus->bEndOfFrame = HI_FALSE;
    if(HI_TRUE == pstAdecChan->bAdecEosFlag)
    {
#ifdef HA_HW_CODEC_SUPPORT
        if(HI_TRUE == pstAdecChan->bHwDecoder)
        {
            HI_HA_STATUS_INFO_S stStatusInfo;
            memset(&stStatusInfo,0,sizeof(HI_HA_STATUS_INFO_S));
            
            ADECHwGetStatusInfo(pstAdecChan, &stStatusInfo);
            pstBufStatus->bEndOfFrame = stStatusInfo.bEndOfFrame;
        }
        else
#endif        
        {
    		if ((pstAdecChan->u32NotEnoughBufCnt >= u32DitherWaterline))
            {
                pstBufStatus->bEndOfFrame = HI_TRUE;
            }
        }
    }

    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}


/****************************************************************************
 * Function:    ADEC_ReceiveFrame
 *
 * Description: Receive Audio Frame
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
HI_S32 ADEC_ReceiveFrame (HI_HANDLE hAdec, HI_UNF_AO_FRAMEINFO_S* pstAOFrame,
                          ADEC_EXTFRAMEINFO_S* pstExtInfo)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    ADEC_OUTPUTBUF_S* ptOutElem   = HI_NULL_PTR;
    ADEC_MIDSTATE_S*  pstMidState = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    if (HI_TRUE != g_pstAdecChan[hAdec]->beWork)
    {
        HI_WARN_ADEC("adec is not work\n");
        return HI_ERR_ADEC_OUT_BUF_EMPTY;
    }

    /* Check parameter */
    CHECK_ADEC_NULL_PTR(pstAOFrame);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    ADEC_LOCK(&g_AdecIOMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beAssigned, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beWork, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
    pstAdecInfo = pstAdecChan->pstAdecInfo;
#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        HI_S32 s32Ret;
        s32Ret = ADECHwReceiveFrame(pstAdecChan, pstAOFrame, pstExtInfo);
        if (HI_SUCCESS != s32Ret)
        {
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return s32Ret;
        }
    }
    else
#endif
    {

        pstOutBuf   = &(pstAdecChan->outStreamBuf);
        pstMidState = &(pstAdecChan->midState);
        /* No data */
        if (pstOutBuf->u32BufReadIdx == pstOutBuf->u32BufWriteIdx)
        {
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);

            return HI_ERR_ADEC_OUT_BUF_EMPTY;
        }
        ptOutElem = &(pstOutBuf->outBuf[pstOutBuf->u32BufReadIdx]);

        /* fill frame info */
        pstAOFrame->u32FrameIndex = pstOutBuf->u32BufReadIdx;
        pstAOFrame->bInterleaved = ptOutElem->bInterleaved;
        pstAOFrame->s32BitPerSample = (HI_S32)ptOutElem->u32BitPerSample;
        pstAOFrame->u32SampleRate = ptOutElem->u32OutSampleRate;
        pstAOFrame->u32Channels = ptOutElem->u32OutChannels;
        pstAOFrame->u32PtsMs = ptOutElem->u32PTS;
        pstAOFrame->u32PcmSamplesPerFrame = (ptOutElem->u32PcmOutSamplesPerFrame & 0xffff);
        pstAOFrame->u32IEC61937DataType = (ptOutElem->u32PcmOutSamplesPerFrame & 0xffff0000) >> 16;
        pstAOFrame->u32BitsBytesPerFrame = ptOutElem->u32BitsOutBytesPerFrame;
        pstAOFrame->ps32PcmBuffer  = ptOutElem->ps32PcmOutBuf;
        pstAOFrame->ps32BitsBuffer = ptOutElem->ps32BitsOutBuf;
        /* add extend adec infomation */
        if (pstExtInfo)
        {
            if (pstOutBuf->u32BufWriteIdx >= pstOutBuf->u32BufReadIdx)
            {
                pstExtInfo->u32FrameLeftNum = pstOutBuf->u32BufWriteIdx - pstOutBuf->u32BufReadIdx;
            }
            else
            {
                pstExtInfo->u32FrameLeftNum = pstOutBuf->u32OutBufNum
                                              - (pstOutBuf->u32BufReadIdx - pstOutBuf->u32BufWriteIdx);
            }

            ADECGetFrameTime(pstAOFrame, &pstExtInfo->u32FrameDurationMs);

            pstExtInfo->u32OrgPtsMs = ptOutElem->u32OrgPTS;
        }

        if ((ptOutElem->u32OutSampleRate > 192000) || (ptOutElem->u32OutSampleRate < 8000)
            || (ptOutElem->u32BitPerSample > 24) || (ptOutElem->u32BitPerSample < 8))
        {
            ptOutElem->bFlag = HI_FALSE;

            /* Move header */
            pstOutBuf->u32BufReadIdx  = (pstOutBuf->u32BufReadIdx + 1) % (pstOutBuf->u32OutBufNum);
            pstAdecInfo->u32FrameRead = pstOutBuf->u32BufReadIdx;

            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            HI_WARN_ADEC("internal error:unsupport sample rate %d or bit depth %d.\n",
                         ptOutElem->u32OutSampleRate,
                         ptOutElem->u32BitPerSample);
            return HI_FAILURE;
        }

        if (pstAOFrame->u32BitsBytesPerFrame == 0)
        {
            pstAOFrame->ps32BitsBuffer = HI_NULL_PTR;
        }

        /* unit of pcm_len is byte! (word??) */
        if (pstMidState->enLastFrameSmaplerate != pstAOFrame->u32SampleRate)
        {
            //SAMPLE_RATE_E tmp;
            //tmp=pstAOFrame->sample_rate;
            //HI_MPI_EVT_Notify(EVENT_MSG_ADEC_NEW_SAMPLE_RATE, (HI_VOID* )(&tmp),sizeof(SAMPLE_RATE_E));
        }

        pstMidState->enLastFrameSmaplerate = (HI_UNF_SAMPLE_RATE_E)pstAOFrame->u32SampleRate;
        if (pstMidState->u32LastFrameChannels != ptOutElem->u32OutChannels)
        {
            //TRACK_MODE_E tmp;
            //(ptOutElem->nchans ==2)?(tmp = TRACK_MODE_STEREO):(tmp=TRACK_MODE_DOUBLE_LEFT);
            //HI_MPI_EVT_Notify(EVENT_MSG_ADEC_NEW_CHMOD, (HI_VOID* )(&tmp),sizeof(TRACK_MODE_E));
        }

        pstMidState->u32LastFrameChannels = ptOutElem->u32OutChannels;

        ptOutElem->bFlag = HI_TRUE;

        /* Move header */
        pstOutBuf->u32BufReadIdx  = (pstOutBuf->u32BufReadIdx + 1) % (pstOutBuf->u32OutBufNum);
        pstAdecInfo->u32FrameRead = pstOutBuf->u32BufReadIdx;
    }

    pstAdecInfo->enSampleRate = (HI_UNF_SAMPLE_RATE_E)pstAOFrame->u32SampleRate;
    pstAdecInfo->enBitWidth = (HI_UNF_BIT_DEPTH_E)pstAOFrame->s32BitPerSample;
    pstAdecInfo->u32PcmSamplesPerFrame = pstAOFrame->u32PcmSamplesPerFrame;
    pstAdecInfo->u32OutChannels = pstAOFrame->u32Channels;
    pstAdecInfo->u32BitsOutBytesPerFrame = pstAOFrame->u32BitsBytesPerFrame;

    ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    if ( pstAdecChan->pstAdecInfo->enPcmCtrlState == ADEC_CMD_CTRL_START )
    {
        if (HI_NULL == pstAdecChan->pfPcm)
        {
            pstAdecChan->pfPcm = fopen(pstAdecChan->pstAdecInfo->filePath, "wb");
            if (!pstAdecChan->pfPcm)
            {
                HI_ERR_ADEC("can not open file (%s)\n", pstAdecChan->pstAdecInfo->filePath);
            }
        }
        if (HI_NULL != pstAdecChan->pfPcm)
        {
            HI_S32 s32Len = fwrite((HI_VOID*)pstAOFrame->ps32PcmBuffer, sizeof(short), pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels, pstAdecChan->pfPcm); // discard PTS
            if (s32Len != pstAOFrame->u32PcmSamplesPerFrame * pstAOFrame->u32Channels)
            {
                HI_ERR_ADEC("write (%s) failed\n", pstAdecChan->pstAdecInfo->filePath);
                fclose(pstAdecChan->pfPcm);
                pstAdecChan->pfPcm = HI_NULL;
                pstAdecChan->pstAdecInfo->enPcmCtrlState = ADEC_CMD_CTRL_STOP;
            }
        }
    }
    if ( pstAdecChan->pstAdecInfo->enPcmCtrlState == ADEC_CMD_CTRL_STOP )
    {
        if (pstAdecChan->pfPcm)
        {
            fclose(pstAdecChan->pfPcm);
            pstAdecChan->pfPcm = HI_NULL;
        }
    }

    return HI_SUCCESS;
}

/****************************************************************************
 * Function:    ADEC_ReleaseFrame
 *
 * Description: Free Audio Frame
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
HI_S32 ADEC_ReleaseFrame(HI_HANDLE hAdec, const HI_UNF_AO_FRAMEINFO_S* pstAOFrame)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstAOFrame);
    CHECK_ADEC_OUTBUF_NUMBER(pstAOFrame->u32FrameIndex);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    ADEC_LOCK(&g_AdecIOMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beAssigned, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beWork, &g_AdecIOMutex[hAdec], &g_AdecApiMutex[hAdec]);
    pstOutBuf = &(pstAdecChan->outStreamBuf);
#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        ADECHwReleaseFrame(pstAdecChan, pstAOFrame->u32FrameIndex);
    }
#endif


    /* free buffer */
    (pstOutBuf->outBuf)[pstAOFrame->u32FrameIndex].bFlag = HI_FALSE;
    ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}

/****************************************************************************
 * Function:    ADEC_GetStatusInfo
 *
 * Description: Free Audio Frame
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
HI_S32 ADEC_GetStatusInfo(HI_HANDLE hAdec, ADEC_STATUSINFO_S* pstStatusinfo)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstStatusinfo);

    pstAdecChan = g_pstAdecChan[hAdec];

    ADEC_LOCK(&g_AdecApiMutex[hAdec]);

    CHECK_ADEC_STATE(pstAdecChan->beAssigned, &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATE(pstAdecChan->beWork, &g_AdecApiMutex[hAdec]);
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstOutBuf = &(pstAdecChan->outStreamBuf);
    pstInBuf = &(pstAdecChan->InStreamBuf);

#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        HI_HA_STATUS_INFO_S stStatus;
        HI_U32 u32BufFree;
        memset(&stStatus,0,sizeof(HI_HA_STATUS_INFO_S));
        
        ADECHwGetStatusInfo(pstAdecChan, &stStatus);
        if (stStatus.u32OutBufReadIdx == stStatus.u32OutBufWriteIdx)
        {
            if (stStatus.u32OutBufReadWrap == stStatus.u32OutBufWriteWrap)
            {
                pstStatusinfo->u32UsedBufNum = 0;
            }
            else
            {
                pstStatusinfo->u32UsedBufNum = pstOutBuf->u32OutBufNum;
            }
        }
        else if (stStatus.u32OutBufReadIdx < stStatus.u32OutBufWriteIdx)
        {
            pstStatusinfo->u32UsedBufNum = stStatus.u32OutBufWriteIdx - stStatus.u32OutBufReadIdx;
        }
        else
        {
            pstStatusinfo->u32UsedBufNum = pstOutBuf->u32OutBufNum
                                           - (stStatus.u32OutBufReadIdx - stStatus.u32OutBufWriteIdx);

        }
        if (stStatus.u32InBufReadPos <= stStatus.u32InBufWritePos)
        {
            u32BufFree = pstInBuf->u32BufSize - (stStatus.u32InBufWritePos - stStatus.u32InBufReadPos);
        }
        else
        {
            u32BufFree = stStatus.u32InBufReadPos - stStatus.u32InBufWritePos;
        }
        pstStatusinfo->u32BufferUsed = pstInBuf->u32BufSize - u32BufFree;
        pstStatusinfo->u32BufferAvailable = u32BufFree;
    }
    else
#endif
    {
        if (pstOutBuf->u32BufWriteIdx >= pstOutBuf->u32BufReadIdx)
        {
            pstStatusinfo->u32UsedBufNum = pstOutBuf->u32BufWriteIdx - pstOutBuf->u32BufReadIdx;
        }
        else
        {
            pstStatusinfo->u32UsedBufNum = pstOutBuf->u32OutBufNum
                                           - (pstOutBuf->u32BufReadIdx - pstOutBuf->u32BufWriteIdx);
        }
        pstStatusinfo->u32BufferUsed = pstInBuf->u32BufSize - pstInBuf->u32BufFree;
        pstStatusinfo->u32BufferAvailable = pstInBuf->u32BufFree;
    }

    pstStatusinfo->bWorking = pstAdecInfo->bAdecWorkEnable;
    pstStatusinfo->u32OutBufNum = pstOutBuf->u32OutBufNum;

    pstStatusinfo->u32BufferSize = pstInBuf->u32BufSize;
    pstStatusinfo->u32TotDecodeFrame = (HI_U32)(pstAdecChan->pstAdecInfo->u32FramnNm);
    if (pstAdecInfo->enSampleRate)
    {
        pstStatusinfo->u32OutBufDurationMs = (pstAdecInfo->u32PcmSamplesPerFrame * 1000
                                              * pstStatusinfo->u32UsedBufNum)
                                             / ((HI_U32)pstAdecInfo->enSampleRate);
        pstStatusinfo->u32FrameDurationMs = (pstAdecInfo->u32PcmSamplesPerFrame
                                             * 1000) / ((HI_U32)pstAdecInfo->enSampleRate);
    }

    pstStatusinfo->u32CodecID = pstAdecInfo->u32CodecID;
    pstStatusinfo->enFmt = pstAdecInfo->enFmt;
    pstStatusinfo->u32Channels  = 2;            /* TODO */
    pstStatusinfo->enSampleRate = pstAdecInfo->enSampleRate;
    pstStatusinfo->enBitDepth = pstAdecInfo->enBitWidth;

    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}

/****************************************************************************
 * Function:    ADEC_GetDebugInfo
 *
 * Description: Free Audio Frame
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
HI_S32 ADEC_GetDebugInfo(HI_HANDLE hAdec, ADEC_DEBUGINFO_S* pstDebuginfo)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstDebuginfo);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);

    CHECK_ADEC_STATE(pstAdecChan->beAssigned, &g_AdecApiMutex[hAdec]);
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstDebuginfo->u32DecFrameNum = (HI_U32)pstAdecInfo->u32FramnNm;
    pstDebuginfo->u32ErrDecFrameNum = (HI_U32)pstAdecInfo->u32ErrFrameNum;

    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}

/****************************************************************************
 * Function:    ADEC_GetStreamInfo
 *
 * Description: Free Audio Frame
 *
 * Inputs:      none
 *
 * Outputs:     none
 *
 * Return:      Success : HI_SUCCESS
 *              Failure : HI_FAILURE
 *****************************************************************************/
HI_S32 ADEC_GetStreamInfo(HI_HANDLE hAdec, ADEC_STREAMINFO_S* pstStreaminfo)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstStreaminfo);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);

    CHECK_ADEC_STATE(pstAdecChan->beAssigned, &g_AdecApiMutex[hAdec]);
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstStreaminfo->u32CodecID   = pstAdecInfo->u32CodecID;
    pstStreaminfo->enSampleRate = pstAdecInfo->enSampleRate;

    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}

HI_S32 ADEC_GetHaSzNameInfo(HI_HANDLE hAdec, ADEC_SzNameINFO_S* pHaSznameInfo)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pHaSznameInfo);

    pstAdecChan = g_pstAdecChan[hAdec];

    ADEC_LOCK(&g_AdecApiMutex[hAdec]);

    CHECK_ADEC_STATE(pstAdecChan->beAssigned, &g_AdecApiMutex[hAdec]);
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    strncpy(pHaSznameInfo->szHaCodecName, pstAdecInfo->szCodecType, sizeof(pHaSznameInfo->szHaCodecName) - 1);
	pHaSznameInfo->szHaCodecName[sizeof(pHaSznameInfo->szHaCodecName) - 1] = '\0';
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}


#ifdef HI_ADEC_AUDSPECTRUM_SUPPORT
HI_S32 ADEC_TryReceiveFrame (HI_HANDLE hAdec, HI_UNF_AO_FRAMEINFO_S* pstAOFrame,
                             ADEC_EXTFRAMEINFO_S* pstExtInfo)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    ADEC_OUTPUTBUF_S* ptOutElem = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    if (HI_TRUE != g_pstAdecChan[hAdec]->beWork)
    {
        HI_WARN_ADEC("adec is not work\n");
        return HI_ERR_ADEC_OUT_BUF_EMPTY;
    }

    /* Check parameter */
    CHECK_ADEC_NULL_PTR(pstAOFrame);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);

    CHECK_ADEC_STATE(pstAdecChan->beAssigned, &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATE(pstAdecChan->beWork, &g_AdecApiMutex[hAdec]);

#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        HI_S32 s32Ret;
        s32Ret = ADECHwReceiveFrame(pstAdecChan, pstAOFrame, pstExtInfo);
        if (HI_SUCCESS != s32Ret)
        {
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return s32Ret;
        }
    }
    else
#endif
    {
        pstOutBuf = &(pstAdecChan->outStreamBuf);

        /* No data */
        if (pstOutBuf->u32BufReadIdx == pstOutBuf->u32BufWriteIdx)
        {
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);

            return HI_ERR_ADEC_OUT_BUF_EMPTY;
        }

        ptOutElem = &(pstOutBuf->outBuf[pstOutBuf->u32BufReadIdx]);

        /* fill frame info */
        pstAOFrame->u32FrameIndex = pstOutBuf->u32BufReadIdx;
        pstAOFrame->bInterleaved = ptOutElem->bInterleaved;
        pstAOFrame->s32BitPerSample = (HI_S32)ptOutElem->u32BitPerSample;
        pstAOFrame->u32SampleRate = ptOutElem->u32OutSampleRate;
        pstAOFrame->u32Channels = ptOutElem->u32OutChannels;
        pstAOFrame->u32PtsMs = ptOutElem->u32PTS;
        pstAOFrame->u32PcmSamplesPerFrame = (ptOutElem->u32PcmOutSamplesPerFrame & 0xffff);
        pstAOFrame->u32IEC61937DataType = (ptOutElem->u32PcmOutSamplesPerFrame & 0xffff0000) >> 16;
        pstAOFrame->u32BitsBytesPerFrame = ptOutElem->u32BitsOutBytesPerFrame;
        pstAOFrame->ps32PcmBuffer  = ptOutElem->ps32PcmOutBuf;
        pstAOFrame->ps32BitsBuffer = ptOutElem->ps32BitsOutBuf;

        /* add extend adec infomation */
        if (pstExtInfo)
        {
            if (pstOutBuf->u32BufWriteIdx >= pstOutBuf->u32BufReadIdx)
            {
                pstExtInfo->u32FrameLeftNum = pstOutBuf->u32BufWriteIdx - pstOutBuf->u32BufReadIdx;
            }
            else
            {
                pstExtInfo->u32FrameLeftNum = pstOutBuf->u32OutBufNum
                                              - (pstOutBuf->u32BufReadIdx - pstOutBuf->u32BufWriteIdx);
            }

            ADECGetFrameTime(pstAOFrame, &pstExtInfo->u32FrameDurationMs);

            pstExtInfo->u32OrgPtsMs = ptOutElem->u32OrgPTS;
        }

        if ((ptOutElem->u32OutSampleRate > 192000) || (ptOutElem->u32OutSampleRate < 8000)
            || (ptOutElem->u32BitPerSample > 24) || (ptOutElem->u32BitPerSample < 8))
        {
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            HI_WARN_ADEC("internal error:unsupport sample rate %d or bit depth %d.\n",
                         ptOutElem->u32OutSampleRate,
                         ptOutElem->u32BitPerSample);
            return HI_FAILURE;
        }

        if (pstAOFrame->u32BitsBytesPerFrame == 0)
        {
            pstAOFrame->ps32BitsBuffer = HI_NULL_PTR;
        }
    }
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}

static HI_VOID ADEC_HIAOUnifyPcmData(HI_HANDLE hAdec, HI_UNF_AO_FRAMEINFO_S* pFrameInfo)
{
    HI_U32 i;
    HI_U32 u32PcmSamplesPerFrame = pFrameInfo->u32PcmSamplesPerFrame;
    HI_U32* pu32UniAoBuf = (HI_U32*)g_pu32Bufffer[hAdec];

    if (HI_TRUE == pFrameInfo->bInterleaved)
    {
        return;
    }

    if (16 == pFrameInfo->s32BitPerSample)
    {
        HI_S16* pSrcL16, *pSrcR16;
        pSrcL16 = (HI_S16*)(pFrameInfo->ps32PcmBuffer);
        HI_U16* pData = (HI_U16*)pu32UniAoBuf;
        if (2 == pFrameInfo->u32Channels)
        {
            pSrcR16 = (HI_S16*)(pFrameInfo->ps32PcmBuffer) + pFrameInfo->u32PcmSamplesPerFrame;
        }
        else
        {
            pSrcR16 = pSrcL16;
        }

        for (i = 0; i < u32PcmSamplesPerFrame; i++)
        {
            *pData++ = (HI_U16)(*pSrcL16++);
            *pData++ = (HI_U16)(*pSrcR16++);
        }
    }
    else
    {
        HI_U32* pSrcL32, *pSrcR32;
        HI_U16* pData = (HI_U16*)pu32UniAoBuf;

        pSrcL32 = (HI_U32*)(pFrameInfo->ps32PcmBuffer);
        if (2 == pFrameInfo->u32Channels)
        {
            pSrcR32 = pSrcL32 + pFrameInfo->u32PcmSamplesPerFrame;
        }
        else
        {
            pSrcR32 = pSrcL32;
        }

        for (i = 0; i < u32PcmSamplesPerFrame; i++)
        {
            *pData++ = (*pSrcL32++) >> 16;
            *pData++ = (*pSrcR32++) >> 16;
        }

        pFrameInfo->s32BitPerSample = 16;
    }

    pFrameInfo->bInterleaved  = HI_TRUE;
    pFrameInfo->ps32PcmBuffer = (HI_S32*)pu32UniAoBuf;

    return;
}

HI_S32 ADEC_GetAnalysisPcmData(HI_HANDLE hAdec)
{
    HI_S32 nRet;
    HI_UNF_AO_FRAMEINFO_S sAoFrame;
    HI_UNF_AO_FRAMEINFO_S* pFrameInfo = &sAoFrame;

    nRet = ADEC_TryReceiveFrame(hAdec, pFrameInfo, NULL);
    if (nRet != HI_SUCCESS)
    {
        HI_WARN_ADEC("Get Frame Failed:%#x!\n", nRet);
        return nRet;
    }

    if (NULL == pFrameInfo->ps32PcmBuffer)
    {
        HI_WARN_ADEC("Get a error Frame!\n");
        return HI_FAILURE;
    }

    /*transform the pcm data to interlace mode in order to simplify post-process*/
    ADEC_HIAOUnifyPcmData(hAdec, pFrameInfo);

    if ((pFrameInfo->u32Channels > 0) && (pFrameInfo->u32PcmSamplesPerFrame > 0))
    {
        WaveFormPcmTaltalSample += pFrameInfo->u32PcmSamplesPerFrame / pFrameInfo->u32Channels;
        if (WaveFormPcmTaltalSample >= ((pFrameInfo->u32PcmSamplesPerFrame * WAVEFORM_CALC_DIFFTIME) / 1000))
        {
            if (pFrameInfo->u32PcmSamplesPerFrame / pFrameInfo->u32Channels >= 1024)
            {
                ChannelsCurrent = pFrameInfo->u32Channels;
                if (ChannelsCurrent > 1)
                {
                    memcpy((HI_U8*)PcmDataCurrent, (HI_U8*)pFrameInfo->ps32PcmBuffer, 2048 * 2);
                }
                else
                {
                    memcpy((HI_U8*)PcmDataCurrent, (HI_U8*)pFrameInfo->ps32PcmBuffer, 1024 * 2);
                }

                WaveFormPcmTaltalSample = 0;
            }
            else
            {
                HI_S32 samples;

                samples = (pFrameInfo->u32PcmSamplesPerFrame <= (2048 - WaveFormPcmDelayLineSmps))
                          ? pFrameInfo->u32PcmSamplesPerFrame : (2048 - WaveFormPcmDelayLineSmps);
                memcpy(&WaveFormPcmDelayLine[WaveFormPcmDelayLineSmps], (HI_U8*)pFrameInfo->ps32PcmBuffer,
                       sizeof(HI_S16) * samples);
                WaveFormPcmDelayLineSmps += samples;
                if ((WaveFormPcmDelayLineSmps / pFrameInfo->u32Channels) >= 1024)
                {
                    ChannelsCurrent = pFrameInfo->u32Channels;
                    if (ChannelsCurrent > 1)
                    {
                        memcpy((HI_U8*)PcmDataCurrent, (HI_U8*)WaveFormPcmDelayLine, 2048 * 2);
                    }
                    else
                    {
                        memcpy((HI_U8*)PcmDataCurrent, (HI_U8*)WaveFormPcmDelayLine, 1024 * 2);
                    }

                    WaveFormPcmTaltalSample  = 0;
                    WaveFormPcmDelayLineSmps = 0;
                }
            }
        }
    }
    else
    {
        HI_FATAL_ADEC("Frame Error!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 ADEC_GetAudSpectrum(HI_U16* pSpectrum, HI_U32 u32BandNum)
{
    HI_U16 EnergyOut[512];

    if (ChannelsCurrent > 0)
    {
        memset(EnergyOut, 0, 512 * sizeof(HI_U16));
        spectrum_do((short*)PcmDataCurrent, (short)ChannelsCurrent, (short*)EnergyOut, (int)u32BandNum);
        memcpy((HI_U8*)pSpectrum, (HI_U8*)EnergyOut, u32BandNum * 2);
    }
    else
    {
        memset((HI_U8*)pSpectrum, 0, u32BandNum * 2);

        /* fix by q46153@20110601: do NOT return HI_FAILURE,
            Channels ==0  means we didn't get the first frame,
            just return HI_SUCCESS, user will try again later and then get the Spectrum. */

        //return HI_FAILURE;
    }

    return HI_SUCCESS;
}

#endif

HI_VOID ADEC_DbgCountTryGetBuffer(HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    if ((HI_S32)(hAdec) >= ADEC_INSTANCE_MAXNUM)
    {
        return;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstAdecInfo->u32DbgGetBufCount_Try++;
}

HI_VOID ADEC_DbgCountGetBuffer (HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    if ((HI_S32)(hAdec) >= ADEC_INSTANCE_MAXNUM)
    {
        return;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstAdecInfo->u32DbgGetBufCount++;
}

HI_VOID ADEC_DbgCountTryPutBuffer(HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    if ((HI_S32)(hAdec) >= ADEC_INSTANCE_MAXNUM)
    {
        return;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstAdecInfo->u32DbgPutBufCount_Try++;
}

HI_VOID ADEC_DbgCountPutBuffer (HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    if ((HI_S32)(hAdec) >= ADEC_INSTANCE_MAXNUM)
    {
        return;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstAdecInfo->u32DbgPutBufCount++;
}

HI_VOID ADEC_DbgCountTryReceiveFrame (HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    if ((HI_S32)(hAdec) >= ADEC_INSTANCE_MAXNUM)
    {
        return;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstAdecInfo->u32DbgReceiveFrameCount_Try++;
}

HI_VOID ADEC_DbgCountReceiveFrame (HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    if ((HI_S32)(hAdec) >= ADEC_INSTANCE_MAXNUM)
    {
        return;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstAdecInfo->u32DbgReceiveFrameCount++;
}

HI_VOID ADEC_DbgCountTrySendStream (HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    if ((HI_S32)(hAdec) >= ADEC_INSTANCE_MAXNUM)
    {
        return;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstAdecInfo->u32DbgSendStraemCount_Try++;
}

HI_VOID ADEC_DbgCountSendStream (HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL_PTR;

    /* Check parameter */
    if ((HI_S32)(hAdec) >= ADEC_INSTANCE_MAXNUM)
    {
        return;
    }

    pstAdecChan = g_pstAdecChan[hAdec];
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstAdecInfo->u32DbgSendStraemCount++;
}

HI_S32  ADEC_SetEosFlag(HI_HANDLE hAdec)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    ADEC_LOCK(&g_AdecDataMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beAssigned, &g_AdecDataMutex[hAdec], &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beWork, &g_AdecDataMutex[hAdec], &g_AdecApiMutex[hAdec]);
#ifdef HA_HW_CODEC_SUPPORT
    if (HI_TRUE == pstAdecChan->bHwDecoder)
    {
        HI_VOID*  hDecoder = HI_NULL_PTR;
        hDecoder = pstAdecChan->decAttr.hDecoder;
        HI_HA_DECODE_S *pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
        (HI_VOID)pHaDev->HwSetEosFlag(hDecoder,HI_TRUE);//PCLINT
    }
    else
#endif
    {
        if (HI_TRUE == pstAdecChan->bPacketDecoder)
        {
            ADECSetPacketEosFlag(pstAdecChan);
        }
    }

    pstAdecChan->bAdecEosFlag = HI_TRUE;
    ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_SUCCESS;
}

HI_S32 ADEC_DropStream(HI_HANDLE hAdec, HI_U32 u32SeekPts)
{
    HI_U32 i, u32LastPts = 0, u32SeekPos;
    HI_U32 u32ConsumeBytes = 0;
    //HI_U32 u32TotalConsumeBytes = 0, u32InRealRdPos = 0;
    HI_U32 u32OutReadPos, u32OutPreBufNum, u32OutWritePos;
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;
    ADEC_PTS_QUE_S* pstPTSQue = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S* pstInBuf = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    ADEC_OUTPUTBUF_S* pstRetBuf = HI_NULL_PTR;
    ADEC_PTS* pstCurrentPTS = HI_NULL_PTR, *pstFirstPts = HI_NULL_PTR;
    ADEC_INFO_S* pstAecAttr = HI_NULL_PTR;

    CHECK_ADEC_HANDLE(hAdec);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    ADEC_LOCK(&g_AdecDataMutex[hAdec]);
    ADEC_LOCK(&g_AdecIOMutex[hAdec]);

    CHECK_ADEC_STATEARG3(pstAdecChan->beAssigned, &g_AdecIOMutex[hAdec], &g_AdecDataMutex[hAdec], &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATEARG3(pstAdecChan->beWork, &g_AdecIOMutex[hAdec], &g_AdecDataMutex[hAdec], &g_AdecApiMutex[hAdec]);

    pstPTSQue = &(pstAdecChan->PTSQue);
    pstInBuf = &(pstAdecChan->InStreamBuf);
    pstOutBuf = &(pstAdecChan->outStreamBuf);
    pstAecAttr = &(pstAdecChan->decAttr);

    u32OutReadPos = pstOutBuf->u32BufReadIdx;
    u32OutWritePos = pstOutBuf->u32BufWriteIdx;

    for (u32SeekPos = u32OutReadPos; u32SeekPos != u32OutWritePos; u32SeekPos = (u32SeekPos + 1) % pstOutBuf->u32OutBufNum)
    {
        pstRetBuf = &(pstOutBuf->outBuf[u32SeekPos]);

        /* find the seek pos in outbuf */
        if ((u32SeekPts <= pstRetBuf->u32PTS) && (u32SeekPts > u32LastPts))
        {
            if (u32SeekPos >= u32OutReadPos)
            {
                for (i = u32OutReadPos; i < u32SeekPos; i++)
                {
                    pstOutBuf->outBuf[i].bFlag = HI_FALSE;
                }
            }
            else
            {
                for (i = u32OutReadPos; i < pstOutBuf->u32OutBufNum; i++)
                {
                    pstOutBuf->outBuf[i].bFlag = HI_FALSE;
                }
                for (i = 0; i < u32SeekPos; i++)
                {
                    pstOutBuf->outBuf[i].bFlag = HI_FALSE;
                }
            }

            pstOutBuf->u32BufReadIdx = u32SeekPos;      //update outbuf readindex

            /* free the frame before the readpos if the frame is being sent to HIAO */
            u32OutPreBufNum = (pstOutBuf->u32OutBufNum + u32OutReadPos - 1) % pstOutBuf->u32OutBufNum;
            if (pstOutBuf->outBuf[u32OutPreBufNum].bFlag == HI_TRUE)
            {
                pstOutBuf->outBuf[u32OutPreBufNum].bFlag = HI_FALSE;
            }

            HI_INFO_ADEC("Find PTS in the outbuffer\n");
            ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
            ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
            return HI_SUCCESS;
        }

        /* continue loop */
        u32LastPts = pstRetBuf->u32PTS;
    }

    if (pstPTSQue->ulPTSread == pstPTSQue->ulPTSwrite)
    {
        HI_WARN_ADEC("Can't find PTS because the inputbuffer is empty\n");
        ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
        ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
        ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
        return HI_FAILURE;
    }

    for (u32SeekPos = pstPTSQue->ulPTSread; u32SeekPos != pstPTSQue->ulPTSwrite; u32SeekPos = (u32SeekPos + 1) % (ADEC_MAX_STORED_PTS_NUM))
    {
        pstCurrentPTS = &(pstPTSQue->tPTSArry[u32SeekPos]);

        if (pstCurrentPTS->u32PtsMs != (HI_U32) - 1)
        {
            /* find the seek pos in inbuf */
            if ((u32SeekPts <= pstCurrentPTS->u32PtsMs) && (u32SeekPts > u32LastPts))
            {
                ADECResetOutBuf(pstOutBuf, ADECGetMaxOutBufSize(pstAdecChan));

                if (u32SeekPos != pstPTSQue->ulPTSread)  //update last pts
                {
                    pstPTSQue->u32LastPtsMs = u32LastPts;
                }

                pstFirstPts = &(pstPTSQue->tPTSArry[pstPTSQue->ulPTSread]);
                //u32InRealRdPos = (pstInBuf->s32BufReadPos + pstInBuf->u32BufSize) % pstInBuf->u32BufSize;
                u32ConsumeBytes = (pstInBuf->u32Boundary + pstCurrentPTS->u32BegPos - pstFirstPts->u32BegPos) % pstInBuf->u32Boundary;
                pstInBuf->u32BufFree += u32ConsumeBytes;
                pstPTSQue->ulPTSread = u32SeekPos;

                if ((u32SeekPos == pstPTSQue->ulPTSread && pstInBuf->s32BufReadPos < 0))
                {
                    /* when the inbuf readpos is in front of the begin pos and the seekpos is equal to ptsque readpos ,
                    don't update the inbuf readpos*/
                }
                else
                {
                    pstInBuf->s32BufReadPos = (HI_S32)(pstCurrentPTS->u32BegPos % pstInBuf->u32BufSize);
                }

                (RET_VOID)ADECResetDecoder(pstAecAttr);       //reset the decoder in case there may be some data left in the codec

                HI_INFO_ADEC("Find PTS in the inbuffer\n");
                ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
                ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
                ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
                return HI_SUCCESS;
            }

            /* continue loop */
            u32LastPts = pstCurrentPTS->u32PtsMs;
        }
    }

    /* reset outbuf/inbuf/codec when the seek pos isn't beyond of 100ms */
    pstCurrentPTS = &(pstPTSQue->tPTSArry[(pstPTSQue->ulPTSwrite + ADEC_MAX_STORED_PTS_NUM - 1) % ADEC_MAX_STORED_PTS_NUM]);
    if (u32SeekPts < pstCurrentPTS->u32PtsMs + ADEC_MAX_PTS_SCOPE)
    {
        ADECResetOutBuf(pstOutBuf, ADECGetMaxOutBufSize(pstAdecChan));
        ADECResetInBuf(pstInBuf);
        (RET_VOID)ADECResetDecoder(pstAecAttr);
        ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
        ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
        ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
        return HI_SUCCESS;
    }

    ADEC_UNLOCK(&g_AdecIOMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return HI_FAILURE;
}
HI_S32 ADEC_SetCodecCmd(HI_HANDLE hAdec, HI_VOID *pstCodecCmd)
{
    HI_S32 sRet = HI_SUCCESS;
    ADEC_CHAN_S* pstAdecChan  = HI_NULL_PTR;
    ADEC_INFO_S*   pstDecAttr = HI_NULL_PTR;
    HI_HA_DECODE_S* pHaDev;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);

    pstAdecChan = g_pstAdecChan[hAdec];
    ADEC_LOCK(&g_AdecApiMutex[hAdec]);
    ADEC_LOCK(&g_AdecDataMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beAssigned, &g_AdecDataMutex[hAdec], &g_AdecApiMutex[hAdec]);
    CHECK_ADEC_STATEARG2(pstAdecChan->beWork, &g_AdecDataMutex[hAdec], &g_AdecApiMutex[hAdec]);
    pstDecAttr = &(pstAdecChan->decAttr);
    if (HI_NULL == pstDecAttr->pHaDecoderDev)
    {
        ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
        ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
        HI_ERR_ADEC("ha_err:invalid NULL poiner,pHaDecoderDev is NULL!\n");
        return HI_FAILURE;
    }

    if (HI_NULL == pstDecAttr->hDecoder)
    {
        ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
        ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
        HI_ERR_ADEC("ha_err:invalid NULL poiner,hDecoder is NULL!\n");
        return HI_FAILURE;
    }

    pHaDev = pstDecAttr->pHaDecoderDev;
    if (pHaDev->DecSetConfig)
    {
        sRet = (HI_S32)pHaDev->DecSetConfig(pstDecAttr->hDecoder, pstCodecCmd);
        if (HA_ErrorNone != sRet)
        {
            HI_ERR_ADEC("ha_err: DecSetConfig fail err=0x%x!\n", sRet);
            sRet = HI_FAILURE;
        }
        else
        {
            sRet = HI_SUCCESS;
        }
    }
    ADEC_UNLOCK(&g_AdecDataMutex[hAdec]);
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    return sRet;
}

HI_S32   ADEC_CheckNewEvent(HI_HANDLE hAdec, ADEC_EVENT_S* pstNewEvent)
{
    ADEC_CHAN_S* pstAdecChan = HI_NULL_PTR;

    /* Check parameter */
    CHECK_ADEC_HANDLE(hAdec);
    CHECK_ADEC_NULL_PTR(pstNewEvent);

    memset(pstNewEvent, 0, sizeof(ADEC_EVENT_S));

    pstAdecChan = g_pstAdecChan[hAdec];

    ADEC_LOCK(&g_AdecApiMutex[hAdec]);

    CHECK_ADEC_STATE(pstAdecChan->beAssigned, &g_AdecApiMutex[hAdec]);

    pstNewEvent->stStreamInfo.enACodecType = pstAdecChan->pstAdecInfo->u32CodecID;

    if(pstAdecChan->stFrameInfo.bFrameInfoChange == HI_TRUE)
    {
        pstNewEvent->bFrameInfoChange = HI_TRUE;
        pstNewEvent->stStreamInfo.enSampleRate = pstAdecChan->stFrameInfo.enSampleRate;
        pstNewEvent->stStreamInfo.u32Channel   = pstAdecChan->stFrameInfo.u32Channel;
        pstNewEvent->stStreamInfo.enBitDepth   = pstAdecChan->stFrameInfo.enBitDepth;
        pstAdecChan->stFrameInfo.bFrameInfoChange = HI_FALSE;
    }

    if(pstAdecChan->stFrameInfo.bUnSupportFormat == HI_TRUE)
    {
        pstAdecChan->pstAdecInfo->u32CodecUnsupportNum = 0;
        pstNewEvent->bUnSupportFormat = HI_TRUE;
        pstAdecChan->stFrameInfo.bUnSupportFormat = HI_FALSE;
    }

    if(pstAdecChan->stFrameInfo.bStreamCorrupt == HI_TRUE)
    {
        pstAdecChan->pstAdecInfo->u32StreamCorruptNum = 0;
        pstNewEvent->bStreamCorrupt   = HI_TRUE;
        pstAdecChan->stFrameInfo.bStreamCorrupt = HI_FALSE;
    }
    
    ADEC_UNLOCK(&g_AdecApiMutex[hAdec]);
    
    return HI_SUCCESS;
}


#ifdef HA_HW_CODEC_SUPPORT
static HI_S32 ADECHwOutbufInit( ADEC_CHAN_S* pstAdecChan, HI_U32 uMaxBufSizePerFrame)
{
    HI_HA_OUTPUTBUF_S stOutbufAttr;
    HA_CODEC_OUTBUFADDR_SET_PARAM_S stOutbufAddr;
    HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    HI_U32  i;

    pstOutBuf = &(pstAdecChan->outStreamBuf);

    stOutbufAttr.u32BufAddr = 0;
    stOutbufAttr.u32MaxBufSizePerFrame = uMaxBufSizePerFrame;
    stOutbufAttr.u32OutFrameNum = pstOutBuf->u32OutBufNum;
    if (HA_ErrorNone != pHaDev->HwOutbufInit(pstAdecChan->decAttr.hDecoder, &stOutbufAttr))
    {
        HI_ERR_ADEC("HwOutbufInit fail\n");
        return HI_FAILURE;
    }

    if (!stOutbufAttr.u32BufAddr)
    {
        return HI_FAILURE;
    }

    pstOutBuf->pu32BaseAddr = (HI_U32*)HI_MEM_Map(stOutbufAttr.u32BufAddr, stOutbufAttr.u32BufSize);
    if (HI_NULL == pstOutBuf->pu32BaseAddr)
    {
        HI_ERR_ADEC("HI_MEM_Map outbuf start addr failed\n");
        (HI_VOID)pHaDev->HwOutBufDeInit(pstAdecChan->decAttr.hDecoder);
        return HI_FAILURE;
    }

    stOutbufAddr.enCmd = HA_CODEC_OUTBUFADDR_SET_CMD;
    stOutbufAddr.u32OutBufAddr = (HI_U32)pstOutBuf->pu32BaseAddr;
    if (HA_ErrorNone != pHaDev->DecSetConfig(pstAdecChan->decAttr.hDecoder, (HI_VOID*)(&stOutbufAddr)))
    {
        HI_ERR_ADEC("DecSetConfig fail\n");
        (HI_VOID)pHaDev->HwOutBufDeInit(pstAdecChan->decAttr.hDecoder);
        (HI_VOID)HI_MEM_Unmap((HI_VOID*)pstOutBuf->pu32BaseAddr);
        return HI_FAILURE;
    }

    /* assigning buffer */
    for (i = 0; i < pstOutBuf->u32OutBufNum; i++)
    {
#if 0
        /* only for sw decder */
        pstOutBuf->outBuf[i].OutBuf = (HI_U32*)(((HI_U32)stOutbufAttr.u32BufVirAddr) + i * uMaxBufSizePerFrame);
#endif
        pstOutBuf->outBuf[i].bFlag = HI_FALSE;
    }

    /* Reset output buffer pointer */
    pstOutBuf->u32BufReadIdx  = 0;
    pstOutBuf->u32BufWriteIdx = 0;

    return HI_SUCCESS;
}

static HI_S32 ADECHwOutbufDeInit(ADEC_CHAN_S* pstAdecChan, ADEC_STREAM_OUTBUF_S*  pstOutBuf)
{
    HA_CODEC_OUTBUFADDR_SET_PARAM_S stOutbufAddr;
    HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;

    if (pstOutBuf->pu32BaseAddr)
    {
        if (HI_SUCCESS != HI_MEM_Unmap((HI_VOID*)pstOutBuf->pu32BaseAddr))
        {
            HI_ERR_ADEC("HI_MEM_Unmap outbuf start addr failed\n");
            return HI_FAILURE;
        }
        pstOutBuf->pu32BaseAddr = HI_NULL_PTR;
    }

    if (HA_ErrorNone != pHaDev->HwOutBufDeInit(pstAdecChan->decAttr.hDecoder))
    {
        HI_ERR_ADEC("HwOutBufDeInit fail\n");
        return HI_FAILURE;
    }

    stOutbufAddr.enCmd = HA_CODEC_OUTBUFADDR_SET_CMD;
    stOutbufAddr.u32OutBufAddr = (HI_U32)pstOutBuf->pu32BaseAddr;
    if (HA_ErrorNone != pHaDev->DecSetConfig(pstAdecChan->decAttr.hDecoder, (HI_VOID*)(&stOutbufAddr)))
    {
        HI_ERR_ADEC("DecSetConfig fail\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 ADECHwInbufInit( ADEC_CHAN_S* pstAdecChan)
{
    HI_HA_INPUTBUF_S stInbufAttr;
    HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
    ADEC_STREAM_BUFFER_S* pstInBuf  = &(pstAdecChan->InStreamBuf);

    /* Read buffer size */
    pstInBuf->u32BufFree = pstInBuf->u32BufSize;
    pstInBuf->s32BufReadPos  = 0;
    pstInBuf->u32BufWritePos = 0;
    pstInBuf->u32StreamWritePos = 0;
    pstInBuf->u32Boundary = pstInBuf->u32BufSize;
    pstInBuf->u32BufPaddingSize = 0;
    pstInBuf->pu8Data = HI_NULL;
    while (pstInBuf->u32Boundary * 2 <= (ADEC_PTS_BOUNDARY_SIZE - pstInBuf->u32BufSize))
    {
        pstInBuf->u32Boundary *= 2;
    }

    stInbufAttr.u32BufAddr = 0;
    stInbufAttr.u32BufSize  = pstInBuf->u32BufSize;
    stInbufAttr.u32PtsBoundary = pstInBuf->u32Boundary;
    if (HA_ErrorNone != pHaDev->HwInbufInit(pstAdecChan->decAttr.hDecoder, &stInbufAttr))
    {
        HI_ERR_ADEC("HwInbufInit fail\n");
        return HI_FAILURE;
    }
    if (!stInbufAttr.u32BufAddr)
    {
        return HI_FAILURE;
    }

    pstInBuf->pu8Data = (HI_U8*)HI_MEM_Map(stInbufAttr.u32BufAddr, stInbufAttr.u32BufSize);
    if (0 == pstInBuf->pu8Data)
    {
        HI_ERR_ADEC(" Map inbuf start addr failed\n");
        (HI_VOID)pHaDev->HwInBufDeInit(pstAdecChan->decAttr.hDecoder);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 ADECHwInbufDeInit(ADEC_CHAN_S* pstAdecChan, ADEC_STREAM_BUFFER_S*  pstInBuf)
{
    HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;

    if (pstInBuf->pu8Data)
    {
        if (HI_SUCCESS != HI_MEM_Unmap((HI_VOID*)pstInBuf->pu8Data))
        {
            HI_ERR_ADEC("HI_MEM_Unmap inbuf start addr failed\n");
            return HI_FAILURE;
        }
        pstInBuf->pu8Data = HI_NULL_PTR;
    }

    if (HA_ErrorNone != pHaDev->HwInBufDeInit(pstAdecChan->decAttr.hDecoder))
    {
        HI_ERR_ADEC("HwInBufDeInit fail\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


static HI_S32 ADECHwGetBuffer( ADEC_CHAN_S* pstAdecChan, HI_U32 u32RequestSize, HI_UNF_STREAM_BUF_S* pstStream1,
                               HI_UNF_STREAM_BUF_S* pstStream2)
{
    HI_S32 s32Ret;
    HI_VOID*  hDecoder = HI_NULL_PTR;
    ADEC_STREAM_BUFFER_S*  pstInBuf = HI_NULL_PTR;
    HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
    HI_HA_INBUF_PROCESS_S stGetInBuf;

    hDecoder = pstAdecChan->decAttr.hDecoder;
    pstInBuf = &(pstAdecChan->InStreamBuf);

    stGetInBuf.u32BufRequestSize1 = 0;
    stGetInBuf.u32BufRequestSize2 = 0;
    stGetInBuf.u32RequestSize = u32RequestSize;

    s32Ret = pHaDev->HwGetBuf(hDecoder, &stGetInBuf);//PCLINT

    //to do:stream get a address!
    if (HA_ErrorNone == s32Ret)
    {
        pstStream1->pu8Data = (HI_VOID*)(pstInBuf->pu8Data + stGetInBuf.u32BufOffsetAddr1);
        pstStream1->u32Size = stGetInBuf.u32BufRequestSize1;
        pstStream2->pu8Data = (HI_VOID*)(pstInBuf->pu8Data + stGetInBuf.u32BufOffsetAddr2);
        pstStream2->u32Size = stGetInBuf.u32BufRequestSize2;
    }
    else if (HA_ErrorInBufFull == s32Ret)
    {
        return HI_ERR_ADEC_IN_BUF_FULL;
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 ADECHwPutBuffer( ADEC_CHAN_S* pstAdecChan, const HI_UNF_STREAM_BUF_S* pstStream1,
                               const HI_UNF_STREAM_BUF_S* pstStream2)
{
    HI_S32 s32Ret;
    HI_VOID*  hDecoder = HI_NULL_PTR;
    HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
    HI_HA_INBUF_PROCESS_S stPutInBuf;

    hDecoder = pstAdecChan->decAttr.hDecoder;
    stPutInBuf.u32BufRequestSize1 = pstStream1->u32Size;
    stPutInBuf.u32BufRequestSize2 = pstStream2->u32Size;

    s32Ret = pHaDev->HwPutBuf(hDecoder, &stPutInBuf);//PCLINT
    if (HA_ErrorNone != s32Ret)
    {
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

static HI_S32 ADECHwReceiveFrame( ADEC_CHAN_S* pstAdecChan, HI_UNF_AO_FRAMEINFO_S* pstAOFrame,
                                  ADEC_EXTFRAMEINFO_S* pstExtInfo)
{
    HI_S32 sRet;
    HI_VOID*  hDecoder = HI_NULL_PTR;
    ADEC_INFO_S*   ptDecAttr         = HI_NULL_PTR;
    ADEC_PROC_ITEM_S* pstAdecInfo    = HI_NULL_PTR;
    ADEC_MIDSTATE_S* pstMidState     = HI_NULL_PTR;
    ADEC_STREAM_OUTBUF_S*  pstOutBuf = HI_NULL_PTR;
    HI_HA_DECODE_S* pHaDev;
    HI_HADECODE_OUTPUT_S sOut;
    ADEC_OUTPUTBUF_S stOutPutBuff;

    ptDecAttr = &(pstAdecChan->decAttr);
    pstAdecInfo = pstAdecChan->pstAdecInfo;
    pstMidState = &(pstAdecChan->midState);
    pstOutBuf = &(pstAdecChan->outStreamBuf);
    hDecoder = (HI_VOID*)ptDecAttr->hDecoder;

    pHaDev = ptDecAttr->pHaDecoderDev;

    sRet = pHaDev->HwReceiveFrame(hDecoder, &sOut);

    if (HA_ErrorNone == sRet)    /* Success */
    {

        ADECConvertHaOut2MpiOut(pstAdecChan, &stOutPutBuff, &sOut, 0);

        if ((stOutPutBuff.u32OutSampleRate > 192000) || (stOutPutBuff.u32OutSampleRate < 8000)
            || (stOutPutBuff.u32BitPerSample > 24) || (stOutPutBuff.u32BitPerSample < 8))
        {
            /* Move header */
            (HI_VOID)ADECHwReleaseFrame(pstAdecChan, stOutPutBuff.u32FrameIndex);

            HI_WARN_ADEC("internal error:unsupport sample rate %d or bit depth %d.\n",
                         stOutPutBuff.u32OutSampleRate,
                         stOutPutBuff.u32BitPerSample);
            return HI_FAILURE;
        }

        /* move the tail of output buffer */
        pstMidState->u32ContinueErrNum = 0;

        /* fill frame info */
        pstAOFrame->u32FrameIndex = stOutPutBuff.u32FrameIndex;
        pstAOFrame->bInterleaved = stOutPutBuff.bInterleaved;
        pstAOFrame->s32BitPerSample = (HI_S32)stOutPutBuff.u32BitPerSample;
        pstAOFrame->u32SampleRate = stOutPutBuff.u32OutSampleRate;
        pstAOFrame->u32Channels = stOutPutBuff.u32OutChannels;
        pstAOFrame->u32PtsMs = stOutPutBuff.u32PTS;
        pstAOFrame->u32PcmSamplesPerFrame = (stOutPutBuff.u32PcmOutSamplesPerFrame & 0xffff);
        pstAOFrame->u32IEC61937DataType = (stOutPutBuff.u32PcmOutSamplesPerFrame & 0xffff0000) >> 16;
        pstAOFrame->u32BitsBytesPerFrame = stOutPutBuff.u32BitsOutBytesPerFrame;
        pstAOFrame->ps32PcmBuffer  = (HI_S32*)((HI_VOID*)pstOutBuf->pu32BaseAddr + (HI_U32)stOutPutBuff.ps32PcmOutBuf);
        pstAOFrame->ps32BitsBuffer = (HI_S32*)((HI_VOID*)pstOutBuf->pu32BaseAddr + (HI_U32)stOutPutBuff.ps32BitsOutBuf);

        if (pstAOFrame->u32BitsBytesPerFrame == 0)
        {
            pstAOFrame->ps32BitsBuffer = HI_NULL_PTR;
        }

        if (pstExtInfo)
        {
            ADECGetFrameTime(pstAOFrame, &pstExtInfo->u32FrameDurationMs);
            pstExtInfo->u32OrgPtsMs = stOutPutBuff.u32OrgPTS;
            pstExtInfo->u32FrameLeftNum = 1;//todo:get left frame num
        }
    }
    else if (HA_ErrorOutBufEmpty == sRet)
    {
        return HI_ERR_ADEC_OUT_BUF_EMPTY;
    }
    else
    {
        //pstAdecInfo->u32ErrFrameNum++;
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID ADECHwReleaseFrame( ADEC_CHAN_S* pstAdecChan, HI_U32 u32FrameIndex)
{
    HI_VOID*  hDecoder = HI_NULL_PTR;
    HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
    hDecoder = pstAdecChan->decAttr.hDecoder;
    (HI_VOID)pHaDev->HwReleaseFrame(hDecoder, u32FrameIndex);//PCLINT
}

static HI_VOID ADECHwGetStatusInfo( ADEC_CHAN_S* pstAdecChan, HI_HA_STATUS_INFO_S* pstStatusInfo)
{
    HI_VOID*  hDecoder = HI_NULL_PTR;
    HI_HA_DECODE_S* pHaDev = pstAdecChan->decAttr.pHaDecoderDev;
    hDecoder = pstAdecChan->decAttr.hDecoder;

    (HI_VOID)pHaDev->HwGetStatusInfo(hDecoder, pstStatusInfo);
}

static HI_VOID ADECHwDecode( ADEC_CHAN_S* pstAdecChan)
{
    HI_HA_STATUS_INFO_S stStatus;
    ADEC_PTS_QUE_S* pstPTSQue = HI_NULL;
    ADEC_PROC_ITEM_S* pstAdecInfo = HI_NULL;
    pstAdecInfo = pstAdecChan->pstAdecInfo;

    pstPTSQue = &(pstAdecChan->PTSQue);
    memset(&stStatus,0,sizeof(HI_HA_STATUS_INFO_S));
    
    ADECHwGetStatusInfo(pstAdecChan, &stStatus);

    pstAdecInfo->u32FramnNm = stStatus.u32FrameNum;
    pstAdecInfo->u32ErrFrameNum = stStatus.u32ErrFrameNum;
    pstAdecInfo->u32DbgTryDecodeCount = stStatus.u32TryExeCnt;
    pstAdecInfo->ThreadScheTimeOutCnt = stStatus.u32ScheTimeOutCnt;
    pstAdecInfo->ThreadExeTimeOutCnt = stStatus.u32ExeTimeOutCnt;

    pstAdecInfo->s32BufRead = (HI_S32)stStatus.u32InBufReadPos;
    pstAdecInfo->u32BufWrite = stStatus.u32InBufWritePos;

    pstAdecInfo->u32FrameWrite = stStatus.u32OutBufWriteIdx;
    pstAdecInfo->u32FrameRead = stStatus.u32OutBufReadIdx;
    pstAdecInfo->u32FrameWriteWrap = (HI_S32)stStatus.u32OutBufWriteWrap;
    pstAdecInfo->u32FrameReadWrap = stStatus.u32OutBufReadWrap;

    if (((pstPTSQue->ulPTSwrite + 1) % ADEC_MAX_STORED_PTS_NUM) == pstPTSQue->ulPTSread)  //pts full
    {
        if ((stStatus.u32OutBufWriteIdx == stStatus.u32OutBufReadIdx) && (stStatus.u32OutBufReadWrap == stStatus.u32OutBufWriteWrap)) //outbuf empty
        {
            ADECDiscardPTS(pstPTSQue, stStatus.u32StreamReadPos); //discard pts
        }
    }
}

static HI_U32 ADECHwGetOutbufFrameNum(ADEC_CHAN_S* pstAdecChan, HI_HA_STATUS_INFO_S* pstStatusInfo)
{
    if(pstStatusInfo->u32OutBufWriteIdx == pstStatusInfo->u32OutBufReadIdx)
    {
        if(pstStatusInfo->u32OutBufWriteWrap == pstStatusInfo->u32OutBufReadWrap)
        {
            return 0;
        }
        else
        {
            return pstAdecChan->outStreamBuf.u32OutBufNum;
        }
    }
    else if(pstStatusInfo->u32OutBufWriteIdx > pstStatusInfo->u32OutBufReadIdx)
    {
        return pstStatusInfo->u32OutBufWriteIdx - pstStatusInfo->u32OutBufReadIdx;
    }
    else
    {
        return pstAdecChan->outStreamBuf.u32OutBufNum - (pstStatusInfo->u32OutBufReadIdx - pstStatusInfo->u32OutBufWriteIdx);
    }
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
