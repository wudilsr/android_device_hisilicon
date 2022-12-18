/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : 
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
  History       :
  1.Date        : 2010/01/26
    Author      : 
    Modification: Created file

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "hi_adp_mpi.h"
#include "hi_karaoke.h"
#include "hi_unf_common.h"
#include "hi_unf_ecs.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_adp_audio.h"
#include "hi_adp_hdmi.h"


#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"



#define  BUFEMPTY 0x2
#define MICFILE "/mnt/mic.pcm"
#define MIXFILE "/mnt/mixer.aac"

static FILE *g_pMicFile = HI_NULL;
static FILE* g_pMixFile = HI_NULL;

static HI_BOOL bSaveMicData = HI_FALSE;
static HI_BOOL bSaveMixData = HI_FALSE;
static HI_BOOL g_StopMicThread = HI_FALSE; 
static HI_BOOL g_StopMixThread = HI_FALSE;
static pthread_t   g_MicThd;
static pthread_t   g_MixThd;

FILE               *g_pTsFile = HI_NULL;
static pthread_t   g_TsThd;
static pthread_mutex_t g_TsMutex;
static HI_BOOL     g_bStopTsThread = HI_FALSE;
HI_HANDLE          g_TsBuf;
PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;

#define  PLAY_DMX_ID  0

HI_VOID TsTthread(HI_VOID *args)
{
    HI_UNF_STREAM_BUF_S   StreamBuf;
    HI_U32                Readlen;
    HI_S32                Ret;

    while (!g_bStopTsThread)
    {
        pthread_mutex_lock(&g_TsMutex);
        Ret = HI_UNF_DMX_GetTSBuffer(g_TsBuf, 188*50, &StreamBuf, 1000);
        if (Ret != HI_SUCCESS )
        {
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), 188*50, g_pTsFile);
        if(Readlen <= 0)
        {
            printf("read ts file end and rewind!\n");
            rewind(g_pTsFile);
            pthread_mutex_unlock(&g_TsMutex);
            continue;
        }

        Ret = HI_UNF_DMX_PutTSBuffer(g_TsBuf, Readlen);
        if (Ret != HI_SUCCESS )
        {
            printf("call HI_UNF_DMX_PutTSBuffer failed.\n");
        }
        pthread_mutex_unlock(&g_TsMutex);
    }

    Ret = HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    if (Ret != HI_SUCCESS )
    {
        printf("call HI_UNF_DMX_ResetTSBuffer failed.\n");
    }

    return;
}




HI_S32 PullMicDataThread(HI_VOID* args)
{
    int s32Ret = 0;
    unsigned int framesize = 0;
    HI_UNF_AO_FRAMEINFO_S  stMicFrame;
    HI_HANDLE  hKaraoke = (HI_HANDLE)args;

    printf("PullMicDataThread Enter!\n");
    stMicFrame.s32BitPerSample = 16;
    stMicFrame.u32Channels = 1;
    stMicFrame.u32SampleRate = HI_UNF_SAMPLE_RATE_44K;
    stMicFrame.bInterleaved = HI_TRUE;
    stMicFrame.u32PtsMs = 0xffffffff;
    stMicFrame.ps32BitsBuffer = HI_NULL;
    stMicFrame.u32FrameIndex = 0;
    stMicFrame.u32PcmSamplesPerFrame = 1024;
    stMicFrame.ps32PcmBuffer = HI_NULL;
    while (HI_TRUE != g_StopMicThread)
    {
        if (HI_TRUE == bSaveMicData)
        {
            stMicFrame.u32PcmSamplesPerFrame = 1024;
            s32Ret = HI_KARAOKE_AcquireMicFrame(hKaraoke, &stMicFrame, 0);
            if (HI_SUCCESS == s32Ret)
            {
                //printf("Acquire MicFrame  success!\n");
                //framesize = sMicFrame.u32PcmSamplesPerFrame*sMicFrame.u32Channels*sMicFrame.s32BitPerSample /8;
                framesize = stMicFrame.u32PcmSamplesPerFrame * stMicFrame.u32Channels * sizeof(HI_S16);
                fwrite(stMicFrame.ps32PcmBuffer, 1, framesize, g_pMicFile);
#if 0
                s32Ret = HI_UNF_KARAOKE_ReleaseMicFrame(hKaraoke, &stMicFrame);
                if (HI_SUCCESS != s32Ret)
                {
                    printf("Release MicFrame Failed!\n");
                    break;
                }
#endif
                usleep(2000);
            }
            else if ((HI_S32)HI_ERR_KARAOKE_BUFFER_EMPTY == s32Ret)
            {
                //printf("Acquire MicFrame  empty!\n");
                usleep(5000);
            }
            else
            {
                printf("Acquire MicFrame  Failed!\n");
                usleep(10 * 1000);
            }
        }
        else
        {
                usleep(500 * 1000);
        }
    }

    printf("PullMicDataThread Exit!\n");	
    return HI_SUCCESS;
}

HI_S32 PullMixDataThread(HI_VOID* args)
{
    int ret = 0;
    unsigned int framesize = 0;
    HI_KARAOKE_MIXDATAFRAME_S  stMixFrame;
    HI_HANDLE  hKaraoke = (HI_HANDLE)args;

    printf("PullMixDataThread Enter!\n");
    while (HI_TRUE != g_StopMixThread)
    {
        if (HI_TRUE == bSaveMixData)
        {
            ret = HI_KARAOKE_AcquireMixFrame(hKaraoke, &stMixFrame, 0);
            if(0 == ret)
            {
#if 0
                framesize = stMixFrame.unAttr.stMixFrame.u32PcmSamplesPerFrame *
                            stMixFrame.unAttr.stMixFrame.u32Channels *
                            stMixFrame.unAttr.stMixFrame.s32BitPerSample / 8;
                
                fwrite(sMixFrame.unAttr.stMixFrame.ps32PcmBuffer, 1, framesize, g_pMixFile);
#endif
                framesize = stMixFrame.stMixBufStream.u32BufLen;
                fwrite(stMixFrame.stMixBufStream.pu8Buf, 1, framesize, g_pMixFile);
                ret = HI_KARAOKE_ReleaseMixFrame(hKaraoke, &stMixFrame);
                if(0 != ret)
                {
                    printf("Release MixFrame Failed!\n");
                    break;
                }
                usleep(10 * 1000);
            }
            else if((HI_S32)HI_ERR_KARAOKE_BUFFER_EMPTY  == ret)
            {
                //printf("Acquire MixFrame  empty!\n");
                usleep(10 * 1000);
            }
            else
            {
                printf("Acquire MixFrame Failed!\n");
                usleep(10 * 1000);
            }
        }
        else
        {
                usleep(500 * 1000);
        }
    }

    printf("PullMixDataThread Exit!\n");	
    return HI_SUCCESS;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32                      Ret;
    HI_CHAR                     InputCmd[32];
    HI_KARAOKE_ATTR_S  stAttr;
    HI_HANDLE  hKaraoke = HI_NULL;

    HI_UNF_SND_ABSGAIN_ATTR_S stAbsWeightGain;
    HI_HANDLE                   hWin;
    HI_HANDLE                   hAvplay;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_UNF_ENC_FMT_E            enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_U32                      ProgNum;
    HI_HANDLE                   hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;

    HI_BOOL bHpfEnable = HI_TRUE;
    HI_BOOL bHowlEnable = HI_TRUE;
    HI_BOOL bRnrEnable = HI_TRUE;
    HI_BOOL bGainEnable = HI_TRUE;
    HI_BOOL bPeqEnable = HI_TRUE;
    HI_BOOL bHarmEnable = HI_TRUE;
    HI_BOOL bReverbEnable = HI_TRUE;
	
    if (3 == argc)
       {
           enFormat = HIADP_Disp_StrToFmt(argv[2]);
       }
       else if (2 == argc)
       {
           enFormat = HI_UNF_ENC_FMT_1080i_50;
       }
       else
       {
           printf("Usage: sample_tsplay file [vo_format]\n"
                  "       vo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50\n");
           printf("Example:./sample_tsplay ./test.ts 1080i_50\n");
           return 0;
       }
    
       g_pTsFile = fopen(argv[1], "rb");
       if (!g_pTsFile)
       {
           printf("open file %s error!\n", argv[1]);
           return -1;
       }
    
       HI_SYS_Init();
    
       HIADP_MCE_Exit();
    
       Ret = HIADP_Snd_Init();
       if (HI_SUCCESS != Ret)
       {
           printf("call HIADP_Snd_Init failed.\n");
           goto SYS_DEINIT;
       }
    
       Ret = HIADP_Disp_Init(enFormat);
       if (HI_SUCCESS != Ret)
       {
           printf("call HIADP_Disp_Init failed.\n");
         //  goto SND_DEINIT;
       }
    
       Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
       Ret |= HIADP_VO_CreatWin(HI_NULL, &hWin);
       if (HI_SUCCESS != Ret)
       {
           printf("call HIADP_VO_Init failed.\n");
           HIADP_VO_DeInit();
           goto DISP_DEINIT;
       }
    
       Ret = HI_UNF_DMX_Init();
       if (HI_SUCCESS != Ret)
       {
           printf("call HI_UNF_DMX_Init failed.\n");
           goto VO_DEINIT;
       }
    
       Ret = HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID,HI_UNF_DMX_PORT_RAM_0);
       if (HI_SUCCESS != Ret)
       {
           printf("call HI_UNF_DMX_AttachTSPort failed.\n");
           goto DMX_DEINIT;
       }
    
       Ret = HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_RAM_0, 0x200000, &g_TsBuf);
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_DMX_CreateTSBuffer failed.\n");
           goto DMX_DEINIT;
       }
    
       Ret = HIADP_AVPlay_RegADecLib();
       if (HI_SUCCESS != Ret)
       {
           printf("call RegADecLib failed.\n");
           goto TSBUF_FREE;
       }
    
       Ret = HI_UNF_AVPLAY_Init();
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_AVPLAY_Init failed.\n");
           goto DMX_DEINIT;
       }
    
       Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
       AvplayAttr.u32DemuxId = PLAY_DMX_ID;
       Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_AVPLAY_Create failed.\n");
           goto AVPLAY_DEINIT;
       }
    
       Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
           goto AVPLAY_DESTROY;
       }
    
       Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
           goto VCHN_CLOSE;
       }
    
       Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
       if (HI_SUCCESS != Ret)
       {
           printf("call HI_UNF_VO_AttachWindow failed:%#x.\n",Ret);
           goto ACHN_CLOSE;
       }
    
       Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_VO_SetWindowEnable failed.\n");
           goto WIN_DETACH;
       }
    
       Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
           goto WIN_DETACH;
       }
       Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_SND_CreateTrack failed.\n");
           goto WIN_DETACH;
       }
    
       Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_SND_Attach failed.\n");
           goto TRACK_DESTROY;
       }
    
       Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
       SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
       Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
       if (Ret != HI_SUCCESS)
       {
           printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
           goto SND_DETACH;
       }
    
       pthread_mutex_init(&g_TsMutex,NULL);
       g_bStopTsThread = HI_FALSE;
       pthread_create(&g_TsThd, HI_NULL, (HI_VOID *)TsTthread, HI_NULL);
    
       HIADP_Search_Init();
       Ret = HIADP_Search_GetAllPmt(PLAY_DMX_ID, &g_pProgTbl);
       if (Ret != HI_SUCCESS)
       {
           printf("call HIADP_Search_GetAllPmt failed.\n");
           goto PSISI_FREE;
       }
    
       ProgNum = 0;
    
       pthread_mutex_lock(&g_TsMutex);
       rewind(g_pTsFile);
       HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    
       Ret = HIADP_AVPlay_PlayProg(hAvplay, g_pProgTbl, ProgNum, HI_TRUE);
       if (Ret != HI_SUCCESS)
       {
           printf("call HIADP_AVPlay_PlayProg failed.\n");
           goto AVPLAY_STOP;
       }
    
       pthread_mutex_unlock(&g_TsMutex);



    g_pMicFile = fopen(MICFILE, "wb");
    if (!g_pMicFile)
    {
        printf("open file %s error!\n", argv[2]);
        return -1;
    }
    g_pMixFile = fopen(MIXFILE, "wb");
    if (!g_pMixFile)
    {
        printf("open file %s error!\n", argv[3]);
        return -1;
    }
    Ret = HI_KARAOKE_Init(&hKaraoke);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_KARAOKE_Init failed.\n");
        return -1;
    }

    Ret = HI_KARAOKE_GetDefaultKaraokeAttr(&stAttr);
    if (HI_SUCCESS != Ret)
    {
        printf("GetDefaultTrackAttr failed.\n");
        return -1;
    }

    Ret = HI_KARAOKE_Create(HI_UNF_SND_0, &stAttr, hKaraoke);
    if (HI_SUCCESS != Ret)
    {
        printf("Create failed.\n");
        return -1;
    }

    stAbsWeightGain.bLinearMode = HI_TRUE;
    stAbsWeightGain.s32GainL = 5;
    stAbsWeightGain.s32GainR = 5;

    Ret = HI_KARAOKE_SetMicWeight(hKaraoke, &stAbsWeightGain);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_KARAOKE_SetMicWeight failed.\n");
        goto KARAOKE_ENABLE;
        return -1;
    }

    Ret = HI_KARAOKE_SetEnable(hKaraoke, HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        printf("Enable KARAOKE failed.\n");
        goto KARAOKE_ENABLE;
        return -1;
    }

#if 1
    g_StopMicThread = HI_FALSE;
    Ret = pthread_create(&g_MicThd, HI_NULL, (HI_VOID*)PullMicDataThread, (HI_VOID*)hKaraoke);

    g_StopMixThread = HI_FALSE;
    Ret = pthread_create(&g_MixThd, HI_NULL, (HI_VOID*)PullMixDataThread, (HI_VOID*)hKaraoke);
#endif

    while (1)
    {
        printf("please input 'q' to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);
        //ALOGD("FUNC:%s Line:%d\n", __func__, __LINE__);
        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        if('r' == InputCmd[0] || 'R' == InputCmd[0])
        {
            if('0' == InputCmd[1] )
            {
                printf("Disable Revervb \n");
                //TODO
                Ret = HI_KARAOKE_SetREVERBConfig(hKaraoke, HI_KARAOKE_REVERB_TYPE_NULL);
                if (HI_SUCCESS != Ret)
                {
                    printf("SetREVERBConfig failed.\n");
                }
            }
            else if('1' == InputCmd[1] )
            {
                printf("Enable Revervb KTV\n");
                //TODO
                Ret = HI_KARAOKE_SetREVERBConfig(hKaraoke, HI_KARAOKE_REVERB_TYPE_KTV);
                if (HI_SUCCESS != Ret)
                {
                    printf("SetREVERBConfig failed.\n");
                }
            }
            else if('2' == InputCmd[1] )
            {
                printf("Enable Revervb THEATRE\n");
                //TODO
                Ret = HI_KARAOKE_SetREVERBConfig(hKaraoke, HI_KARAOKE_REVERB_TYPE_THEATRE);
                if (HI_SUCCESS != Ret)
                {
                    printf("SetREVERBConfig failed.\n");
                }
                
            }
            else if('3' == InputCmd[1] )
            {
                printf("Enable Revervb CONCERT\n");
                //TODO
                 Ret = HI_KARAOKE_SetREVERBConfig(hKaraoke, HI_KARAOKE_REVERB_TYPE_HALL);
                if (HI_SUCCESS != Ret)
                {
                    printf("SetREVERBConfig failed.\n");
                }
            }
            else if('4' == InputCmd[1] )
            {
                printf("Enable Revervb CONCERT\n");
                //TODO
                 Ret = HI_KARAOKE_SetREVERBConfig(hKaraoke, HI_KARAOKE_REVERB_TYPE_CONCERT);
                if (HI_SUCCESS != Ret)
                {
                    printf("SetREVERBConfig failed.\n");
                }
            }
            else if('5' == InputCmd[1] )
            {
                printf("Enable Revervb CONCERT\n");
                //TODO
                 Ret = HI_KARAOKE_SetREVERBConfig(hKaraoke, HI_KARAOKE_REVERB_TYPE_VALLEY);
                if (HI_SUCCESS != Ret)
                {
                    printf("SetREVERBConfig failed.\n");
                }
           }
        }

        if('m' == InputCmd[0] || 'M' == InputCmd[0])
        {
            static int pullmic_toggle = 0;
            pullmic_toggle++;
            if (pullmic_toggle & 1)
            {
                printf("Enable pull Mic Data\n");
                Ret = HI_KARAOKE_SetAcquireMicFrameEnable(hKaraoke, HI_TRUE);
                if (HI_SUCCESS != Ret)
                {
                    printf("KARAOKE_SetAttr failed.\n");
                }
                bSaveMicData = HI_TRUE;
            }
            else
            {
                printf("Disable pull Mic Data\n");
                Ret = HI_KARAOKE_SetAcquireMicFrameEnable(hKaraoke, HI_FALSE);
                if (HI_SUCCESS != Ret)
                {
                    printf("KARAOKE_SetAttr failed.\n");
                }
                usleep(500 * 1000);
                bSaveMicData = HI_FALSE;
            }

        }

        if('o' == InputCmd[0] || 'O' == InputCmd[0])
        {
            static int pullmix_toggle = 0;
            pullmix_toggle++;
            if (pullmix_toggle & 1)
            {
                printf("Enable pull Mix Data\n");
                HI_KARAOKE_MIX_ATTR_S stAencAttr;
                stAencAttr.s16ChannelsIn = 2;
                stAencAttr.s16ChannelsOut = 2;
                stAencAttr.s32BitRate = 64000;
                stAencAttr.s32SampleRate = 48000;
                HI_KARAOKE_SetMixFrameAttr(hKaraoke, &stAencAttr);
                Ret = HI_KARAOKE_SetAcquireMixFrameEnable(hKaraoke, HI_TRUE);
                if (HI_SUCCESS != Ret)
                {
                    printf("KARAOKE_SetAttr failed.\n");
                }
                bSaveMixData = HI_TRUE;
            }
            else
            {
                printf("Disable pull Mix Data\n");
                Ret = HI_KARAOKE_SetAcquireMixFrameEnable(hKaraoke, HI_FALSE);
                if (HI_SUCCESS != Ret)
                {
                    printf("KARAOKE_SetAttr failed.\n");
                }
                bSaveMixData = HI_FALSE;
            }
        }


        if('s' == InputCmd[0] || 'S' == InputCmd[0])
        {
            static int enable_toggle = 0;
            enable_toggle++;
            if (enable_toggle & 1)
            {
                printf("Enable KARAOKE\n");
                Ret = HI_KARAOKE_SetEnable(hKaraoke, HI_TRUE);
                if (HI_SUCCESS != Ret)
                {
                    printf("Enable KARAOKE failed.\n");
                }
            }
            else
            {
                printf("Disable KARAOKE\n");
                Ret = HI_KARAOKE_SetEnable(hKaraoke, HI_FALSE);
                if (HI_SUCCESS != Ret)
                {
                    printf("Enable KARAOKE failed.\n");
                }
            }
        }
        if ('u' == InputCmd[0] || 'U' == InputCmd[0])
        {
            printf("Mic volume up!\n");
            HI_KARAOKE_GetMicWeight(hKaraoke, &stAbsWeightGain);
            stAbsWeightGain.s32GainL += 5;
            if (stAbsWeightGain.s32GainL > 100)
            {
                stAbsWeightGain.s32GainL = 100;
            }
            stAbsWeightGain.s32GainR = stAbsWeightGain.s32GainL;
            HI_KARAOKE_SetMicWeight(hKaraoke, &stAbsWeightGain);
            printf("Mic Volum : %d\n", stAbsWeightGain.s32GainL);
        }
        if ('d' == InputCmd[0] || 'D' == InputCmd[0])
        {
            printf("Mic volume down!\n");
            HI_KARAOKE_GetMicWeight(hKaraoke, &stAbsWeightGain);
            stAbsWeightGain.s32GainL -= 5;
            if (stAbsWeightGain.s32GainL < 0)
            {
                stAbsWeightGain.s32GainL = 0;
            }
            stAbsWeightGain.s32GainR = stAbsWeightGain.s32GainL;
            HI_KARAOKE_SetMicWeight(hKaraoke, &stAbsWeightGain);
            printf("Mic Volum : %d\n", stAbsWeightGain.s32GainL);
        }
        if ('h' == InputCmd[0])
        {
            if (HI_TRUE == bHpfEnable)
            {
                bHpfEnable = HI_FALSE;
            }
            else
            {
                bHpfEnable = HI_TRUE;
            }
            HI_KARAOKE_SetEnableKde(hKaraoke, 0, bHpfEnable);
        }

        if ('H' == InputCmd[0])
        {
            if (HI_TRUE == bHowlEnable)
            {
                bHowlEnable = HI_FALSE;
            }
            else
            {
                bHowlEnable = HI_TRUE;
            }
            HI_KARAOKE_SetEnableKde(hKaraoke, 0, bHowlEnable);
        }

        if ('n' == InputCmd[0] || 'N' == InputCmd[0])
        {
            if (HI_TRUE == bRnrEnable)
            {
                bRnrEnable = HI_FALSE;
            }
            else
            {
                bRnrEnable = HI_TRUE;
            }
            HI_KARAOKE_SetEnableKde(hKaraoke, 0, bRnrEnable);
        }

        if ('g' == InputCmd[0])
        {
            if (HI_TRUE == bGainEnable)
            {
                bGainEnable = HI_FALSE;
            }
            else
            {
                bGainEnable = HI_TRUE;
            }
            HI_KARAOKE_SetEnableKde(hKaraoke, 0, bGainEnable);
        }

        if ('p' == InputCmd[0])
        {
            if (HI_TRUE == bPeqEnable)
            {
                bPeqEnable = HI_FALSE;
            }
            else
            {
                bPeqEnable = HI_TRUE;
            }
            HI_KARAOKE_SetEnableKde(hKaraoke, 0, bPeqEnable);
        }

        if ('a' == InputCmd[0])
        {
            if (HI_TRUE == bHarmEnable)
            {
                bHarmEnable = HI_FALSE;
            }
            else
            {
                bHarmEnable = HI_TRUE;
            }
            HI_KARAOKE_SetEnableKde(hKaraoke, 0, bHarmEnable);
        }

        if ('v' == InputCmd[0])
        {
            if (HI_TRUE == bReverbEnable)
            {
                bReverbEnable = HI_FALSE;
            }
            else
            {
                bReverbEnable = HI_TRUE;
            }
            HI_KARAOKE_SetEnableKde(hKaraoke, 0, bReverbEnable);
        }
    }
AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

PSISI_FREE:
    HIADP_Search_FreeAllPmt(g_pProgTbl);
    g_pProgTbl = HI_NULL;
    HIADP_Search_DeInit();

    g_bStopTsThread = HI_TRUE;
    pthread_join(g_TsThd, HI_NULL);
    pthread_mutex_destroy(&g_TsMutex);

SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, hAvplay);

ACHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

VCHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

TSBUF_FREE:
    HI_UNF_DMX_DestroyTSBuffer(g_TsBuf);

DMX_DEINIT:
    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();

VO_DEINIT:
    HI_UNF_VO_DestroyWindow(hWin);
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

//SND_DEINIT:
//    HIADP_Snd_DeInit();
SYS_DEINIT:
    HI_SYS_DeInit();
    fclose(g_pTsFile);
    g_pTsFile = HI_NULL;
    g_StopMixThread = HI_TRUE;
    pthread_join(g_MixThd, HI_NULL);

    g_StopMicThread = HI_TRUE;
    pthread_join(g_MicThd, HI_NULL);
KARAOKE_ENABLE:
    
    HI_KARAOKE_Destroy(hKaraoke);
    HI_KARAOKE_DeInit(hKaraoke);
    fclose(g_pMicFile);
    g_pMicFile = HI_NULL;

    fclose(g_pMixFile);
    g_pMixFile = HI_NULL;

    return Ret;
}


