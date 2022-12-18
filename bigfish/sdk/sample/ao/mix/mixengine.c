/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : sample_mixengine.c
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

//#include "hi_unf_sio.h"
#include "hi_unf_sound.h"
#include "hi_adp_audio.h"
#include "hi_adp.h"

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_demux.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "HA.AUDIO.TRUEHDPASSTHROUGH.decode.h"

typedef struct himyMixer_State_S
{
    HI_U32              portIdx;
    pthread_t           MixerThd;
    HI_BOOL             StopThread;
    HI_HANDLE           hTrack;
    FILE               *pAudMixFile;
    HI_U32              SampleRate;
    HI_U32              Channels;
} myMixer_State_S;

#define HI_SND_MIXER_NUMBER 8
static myMixer_State_S stMixer[HI_SND_MIXER_NUMBER];

/*****************************************SOUND common interface************************************/
static HI_S32 MIXENGINE_Snd_Init(HI_VOID)
{
    HI_S32 Ret;
    HI_UNF_SND_ATTR_S stAttr;

    Ret = HI_UNF_SND_Init();
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Init failed.\n");
        return Ret;
    }

    Ret = HI_UNF_SND_GetDefaultOpenAttr(HI_UNF_SND_0, &stAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_GetDefaultOpenAttr failed.\n");
        return Ret;
    }

    stAttr.u32SlaveOutputBufSize = 1024 * 16; /* in order to increase the reaction of stop/start, the buf cannot too big*/

    Ret = HI_UNF_SND_Open(HI_UNF_SND_0, &stAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Open failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 MIXENGINE_Snd_DeInit(HI_VOID)
{
    HI_S32 Ret;

    Ret = HI_UNF_SND_Close(HI_UNF_SND_0);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Close failed.\n");
        return Ret;
    }

    Ret = HI_UNF_SND_DeInit();
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_DeInit failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 MixerThread(HI_VOID *args)
{
    HI_S16 PmcBuf[4096];
    HI_S32 nRet, Readlen, Frame;
    HI_UNF_AO_FRAMEINFO_S stAOFrame;
    HI_BOOL Interleaved = HI_TRUE;
    HI_S32 BitPerSample = 16;
    HI_S32 PcmSamplesPerFrame = 1024;
    myMixer_State_S *pstMixer;
    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;

    pstMixer = (myMixer_State_S*)args;

    {
        if(0 == pstMixer->portIdx)
        {
            HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
        }
        else
        {
            HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_SLAVE, &stTrackAttr);
        }
        nRet = HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&pstMixer->hTrack);
        if (HI_SUCCESS != nRet)
        {
            printf("HI_UNF_SND_CreateTrack err:0x%x\n", nRet);
            return nRet;
        }
    }
    Frame = 0;
    stAOFrame.s32BitPerSample = BitPerSample;
    stAOFrame.u32Channels   = pstMixer->Channels;
    stAOFrame.bInterleaved  = Interleaved;
    stAOFrame.u32SampleRate = (HI_U32)(pstMixer->SampleRate);
    stAOFrame.u32PtsMs = 0xffffffff;
    stAOFrame.ps32BitsBuffer = HI_NULL;
    stAOFrame.u32BitsBytesPerFrame = 0;
    stAOFrame.u32FrameIndex = 0;
    stAOFrame.u32PcmSamplesPerFrame = PcmSamplesPerFrame;
    stAOFrame.ps32PcmBuffer = (HI_S32*)(PmcBuf);

    while (HI_TRUE != pstMixer->StopThread)
    {
        HI_S32 Need, SendPending;
        Need = PcmSamplesPerFrame * pstMixer->Channels * sizeof(HI_S16);

        SendPending = 0;
        //while (1)
        while (HI_TRUE != pstMixer->StopThread)
        {
            if (!SendPending)
            {
                Readlen = fread(PmcBuf, sizeof(HI_U8), Need, pstMixer->pAudMixFile);
                if (Readlen != Need)
                {
                    printf("mixer(%d)reach end of mix file\n", pstMixer->portIdx);
                    rewind(pstMixer->pAudMixFile);
                    continue;
                }
            }

            nRet = HI_UNF_SND_SendTrackData(pstMixer->hTrack, &stAOFrame);
            if (HI_SUCCESS == nRet)
            {
                break;
            }
            else if (HI_FAILURE == nRet)
            {
                printf("HI_UNF_SND_Mixer_SendData err:0x%x\n", nRet);
                return nRet;
            }
            else
            {
                usleep(1000);
                SendPending = 1;
                
                //continue;
            }
        }

#if 0
        Frame++;
        if ((Frame % 1024 == 0))
        {
            printf("frame =%d send Bytes=%d\n", Frame, Need);
        }
#endif

    }

    nRet = HI_UNF_SND_DestroyTrack(pstMixer->hTrack);
    if (HI_SUCCESS != nRet)
    {
        printf("HI_UNF_SND_DestroyTrack err:0x%x\n", nRet);
        return nRet;
    }

    //printf("hTrack(0x%x) exit\n", pstMixer->hTrack);

    return HI_SUCCESS;
}

HI_S32 main(int argc, char *argv[])
{
    HI_U32 portIdx;
    HI_CHAR InputCmd[32];
    HI_S32 MixNumber;
    if (argc < 5)
    {
        printf("Usage:    ./sample_mixengine inputfile0 trackweight0 samplerate0 inchannels0 inputfile1 trackweight1 samplerate1 inchannels1 ...\n");
        printf("examples:\n");
		printf("          ./sample_mixengine inputfile0 100 48000 2 inputfile1 100 44100 1\n");
        return HI_FAILURE;
    }

	HI_SYS_Init();
    //HI_SYS_PreAV(NULL);
    MIXENGINE_Snd_Init();

    MixNumber  = argc - 1;
    MixNumber /= 4;
    for (portIdx = 0; portIdx < MixNumber; portIdx++)
    {
        stMixer[portIdx].pAudMixFile = fopen(argv[4 * portIdx + 0 + 1], "rb");
        stMixer[portIdx].SampleRate = atoi(argv[4 * portIdx + 2 + 1]);
        stMixer[portIdx].Channels = atoi(argv[4 * portIdx + 3 + 1]);
        if (!stMixer[portIdx].pAudMixFile)
        {
            printf("open file %s error!\n", argv[portIdx + 1]);
            return -1;
        }

        stMixer[portIdx].portIdx = portIdx;
        stMixer[portIdx].StopThread = HI_FALSE;
        stMixer[portIdx].MixerThd = (pthread_t)NULL;
        printf("\n create mixer(%d) , sampleRate(%d) ch(%d)\n", portIdx,
               stMixer[portIdx].SampleRate, stMixer[portIdx].Channels);

        pthread_create(&(stMixer[portIdx].MixerThd), (const pthread_attr_t *)HI_NULL, (HI_VOID *)MixerThread,
                       (HI_VOID *)(&stMixer[portIdx]));
    }

    while (1)
    {
        printf("\n please input the q to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);
        portIdx = (HI_U32)((InputCmd[1] - 0x30));
        if (portIdx >= HI_SND_MIXER_NUMBER)
        {
            portIdx = HI_SND_MIXER_NUMBER - 1;
        }

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            for (portIdx = 0; portIdx < MixNumber; portIdx++)
            {
                stMixer[portIdx].StopThread = 0;
            }
            
            break;
        }
    }

    sleep(1);

    for (portIdx = 0; portIdx < MixNumber; portIdx++)
    {
        stMixer[portIdx].StopThread = HI_TRUE;
        pthread_join(stMixer[portIdx].MixerThd, NULL);
        fclose(stMixer[portIdx].pAudMixFile);
    }

    MIXENGINE_Snd_DeInit();

    return 0;
}
