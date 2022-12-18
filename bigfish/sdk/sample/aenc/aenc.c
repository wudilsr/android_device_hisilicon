/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : aenc.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2008/03/15
  Description   :
  History       :
  1.Date        : 2008/03/15
    Author      : Hi3560MPP
    Modification: Created file
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>

#include "hi_type.h"
#include "hi_debug.h"

#include "hi_error_mpi.h"

#include "hi_unf_common.h"
#include "hi_adp_mpi.h"
#include "hi_unf_aenc.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.AAC.encode.h"

typedef struct
{
    pthread_t pthreadSendES;
    HI_BOOL   bStopSendStream;

    HI_CHAR * infileName;
    HI_CHAR * outfileName;

    HI_HANDLE hAenc;
    HI_U32    u32AencCodecID;
    HI_UNF_AENC_ATTR_S stAencAttr;
} AudAenc_S;


#define AENC_IN_PACKET_SIZE  (1024 * 3)

static HI_CHAR* g_HA_EncoderDllName = {"libHA.AUDIO.AAC.encode.so"};
static AudAenc_S g_stAudAenc;
static HI_U32 g_u32SampleRateIn;
static HI_U32 g_u32ChannelsIn;
static HI_U32 g_u32SampleRateOut;
static HI_U32 nFrame;


#define CHECK_RET(Ret) \
    do                                                  \
    {                                                   \
        if (HI_SUCCESS != Ret)             \
        {                                           \
            printf("err=0x%x: %s[%d] !\n", Ret, __FUNCTION__, __LINE__); \
            return Ret;           \
        }                                           \
    } while (0)

#define CHECK_AO_OUT_SAMPLERATE(outrate) \
    do                                     \
    {                                      \
        switch (outrate)                   \
        {                                  \
        case  HI_UNF_SAMPLE_RATE_16K:          \
        case  HI_UNF_SAMPLE_RATE_22K:          \
        case  HI_UNF_SAMPLE_RATE_24K:          \
        case  HI_UNF_SAMPLE_RATE_32K:          \
        case  HI_UNF_SAMPLE_RATE_44K:          \
        case  HI_UNF_SAMPLE_RATE_48K:          \
            break;                          \
        default:                            \
            printf("invalid sample rate: %d\n", outrate);  \
            return -1; \
        }                                                 \
    } while (0)

void AencFrameInfoConfig(HI_UNF_AO_FRAMEINFO_S *pFrameinfo)
{
    pFrameinfo->ps32PcmBuffer = NULL;
    pFrameinfo->u32SampleRate = g_u32SampleRateIn;
    pFrameinfo->s32BitPerSample = 16;
    pFrameinfo->u32Channels = g_u32ChannelsIn;

    if (16 == pFrameinfo->s32BitPerSample)
    {
        pFrameinfo->u32PcmSamplesPerFrame = AENC_IN_PACKET_SIZE / (pFrameinfo->u32Channels * 2);
    }
    else
    {
        pFrameinfo->u32PcmSamplesPerFrame = AENC_IN_PACKET_SIZE / (pFrameinfo->u32Channels * 4);
    }
    //pFrameinfo->u32PcmSamplesPerFrame = 0x300;
    //printf("pFrameinfo->u32PcmSamplesPerFrame=%#x, =%d\n", pFrameinfo->u32PcmSamplesPerFrame, pFrameinfo->u32Channels);

    pFrameinfo->bInterleaved = HI_TRUE;

    pFrameinfo->u32FrameIndex = 0;
    pFrameinfo->ps32BitsBuffer = 0x0;
    pFrameinfo->u32BitsBytesPerFrame = 0x0;
    pFrameinfo->u32PtsMs = 0;
}

static HI_S32 AencWriteFile(FILE* outfile)
{
    HI_UNF_ES_BUF_S sAencFrame;
    HI_UNF_ES_BUF_S *pstAencFrame = &sAencFrame;
    HI_S32 Ret;

    Ret = HI_UNF_AENC_AcquireStream(g_stAudAenc.hAenc, pstAencFrame, 0);
    if (HI_SUCCESS == Ret)
    {
        if (outfile)
        {
            fwrite(pstAencFrame->pu8Buf, 1, pstAencFrame->u32BufLen, outfile);
        }

        nFrame++;
        if ((nFrame % 256 == 0))
        {
            printf("%s Sent Stream times =%d \n", __FUNCTION__, nFrame);
        }

        Ret = HI_UNF_AENC_ReleaseStream(g_stAudAenc.hAenc, pstAencFrame);
    }
    return Ret;
}

HI_S32 AencThread(AudAenc_S* pAud)
{
    FILE *infile, *outfile;
    HI_UNF_STREAM_BUF_S sStream;
    HI_UNF_AO_FRAMEINFO_S  sAoFrame;
    HI_UNF_AO_FRAMEINFO_S *pFrameinfo = &sAoFrame;
    HI_U32 FileLen = 0;
    HI_U32 ReadSum = 0;
    HI_S32 nRead = 0;
    HI_S32 Ret = 0;
    HI_BOOL bSendOK = HI_TRUE;
    HI_U32 u32EncodeFrame = 0;

    g_stAudAenc.bStopSendStream = HI_FALSE;

    /* open input file */
    infile = fopen(pAud->infileName, "rb");
    if (!infile)
    {
        printf(" *** Error opening input file %s ***\n", pAud->infileName);
        return -1;
    }
    Ret = fseek(infile, 0, SEEK_END);
    FileLen = ftell(infile);
    Ret += fseek(infile, 0, SEEK_SET);
    if (Ret || !FileLen)
    {
        printf(" *** Error ftell input file length: 0x%x ***\n", FileLen);
        fclose(infile);
        return -1;
    }
    //printf("FileLen=0x%x\n", FileLen);

    /* open output file */
    outfile = fopen(pAud->outfileName, "wb");
    if (!outfile)
    {
        printf(" *** Error opening output file %s ***\n", pAud->outfileName);
        fclose(infile);
        return -1;
    }

    sStream.pu8Data = malloc(AENC_IN_PACKET_SIZE);
    AencFrameInfoConfig(pFrameinfo);

    while (!(pAud->bStopSendStream))
    {
        if (ReadSum >= FileLen)
        {
            Ret = AencWriteFile(outfile);
            if (HI_ERR_AENC_OUT_BUF_EMPTY == Ret)
            {
                break;
            }
            else
            {
                usleep(10000);
                continue;
            }
        }

        if (bSendOK)
        {
            memset(sStream.pu8Data, '\0', AENC_IN_PACKET_SIZE);
            nRead = fread(sStream.pu8Data, sizeof(HI_U8), AENC_IN_PACKET_SIZE, infile);
            if (nRead != AENC_IN_PACKET_SIZE && (nRead + ReadSum) < FileLen)
            {
                printf(" *** Error fread input file: Ret= 0x%x ***\n", nRead);
                fclose(infile);
                infile = fopen(pAud->infileName, "rb");
                Ret = fseek(infile, ReadSum, SEEK_SET);
                if (Ret)
                {
                    printf(" *** Error fseek input file: Ret= 0x%x ***\n", Ret);
                }
                usleep(10000);
                continue;
            }
            ReadSum += nRead;
        }

        AencWriteFile(outfile);

        pFrameinfo->ps32PcmBuffer = (HI_S32 *)sStream.pu8Data;
        pFrameinfo->u32FrameIndex = u32EncodeFrame;
        Ret = HI_UNF_AENC_SendFrame(g_stAudAenc.hAenc, pFrameinfo);
        if (HI_SUCCESS == Ret)
        {
            bSendOK = HI_TRUE;
            u32EncodeFrame++;
        }
        else
        {
            bSendOK = HI_FALSE;
        }
        usleep(10000);
    }

    free(sStream.pu8Data);

    if (infile)
    {
        fclose(infile);
    }
    if (outfile)
    {
        fclose(outfile);
    }

    printf(" *** Aenc Send Stream Stop ***\n\n");
    return Ret;
}


HI_S32 main(int argc, char *argv[])
{
    HI_U32 AencType;
    HI_S32 Ret;

    if (7 != argc)
    {
        printf("Usage:   ./sample_aenc infileName inChannel insamplerate outfileName aac outsamplerate\n"
               "         insamplerate:8000~192000\n"
               "         inChannle:1, 2\n"
               "         outsamplerate:16000~48000\n");
        printf("Example: ./sample_aenc ./test.wav 2 44100 ./test.aac aac 48000\n");

        return -1;
    }

    g_stAudAenc.infileName = argv[1];
    g_stAudAenc.outfileName = argv[4];

    if (!strcasecmp("aac", argv[5]))
    {
        AencType = HA_AUDIO_ID_AAC;
    }
    else
    {
        printf("unsupport aud encode type!\n");
        return -1;
    }

    g_u32SampleRateIn = atoi(argv[3]);
    g_u32ChannelsIn = atoi(argv[2]);
    g_u32SampleRateOut = atoi(argv[6]);
    HI_SYS_Init();

    /*Initial HIAO*/
    Ret = HIADP_Snd_Init();
    CHECK_RET(Ret);

    Ret = HI_UNF_AENC_Init();
    CHECK_RET(Ret);

    Ret = HI_UNF_AENC_RegisterEncoder(g_HA_EncoderDllName);
    CHECK_RET(Ret);

    g_stAudAenc.stAencAttr.enAencType = AencType;

    HI_UNF_AO_FRAMEINFO_S sAoFrame;
    AencFrameInfoConfig(&sAoFrame);

    AAC_ENC_CONFIG stPrivateConfig;
    HA_AAC_GetDefaultConfig(&stPrivateConfig);
    stPrivateConfig.sampleRate = g_u32SampleRateOut;

    if (HA_AUDIO_ID_AAC == g_stAudAenc.stAencAttr.enAencType)
    {
        HA_AAC_GetEncDefaultOpenParam(&g_stAudAenc.stAencAttr.sOpenParam, (HI_VOID*)&stPrivateConfig);
        printf("DesiredSampleRate=%d\n", g_stAudAenc.stAencAttr.sOpenParam.u32DesiredSampleRate);
    }

    Ret = HI_UNF_AENC_Create(&(g_stAudAenc.stAencAttr), &(g_stAudAenc.hAenc));
    CHECK_RET(Ret);

    Ret = HI_UNF_AENC_Start(g_stAudAenc.hAenc);
    CHECK_RET(Ret);
    pthread_create(&(g_stAudAenc.pthreadSendES), HI_NULL, (HI_VOID *)AencThread, (HI_VOID *)&(g_stAudAenc));

    printf("\nPress any key to exit\n");
    getchar();

    Ret = HI_UNF_AENC_Stop(g_stAudAenc.hAenc);
    CHECK_RET(Ret);
    g_stAudAenc.bStopSendStream = HI_TRUE;
    usleep(10000);
    pthread_join(g_stAudAenc.pthreadSendES, HI_NULL);

    HI_UNF_AENC_Destroy(g_stAudAenc.hAenc);
    HI_UNF_AENC_DeInit();

    return 0;
}
