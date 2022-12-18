/******************************************************************************

  Copyright (C), 2001-2013, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : audioplayer.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2012/05/22
  Description   :
  History       :
  1.Date        : 2012/05/22
    Author      : w00196555
    Modification: Created file

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
//#include "hi_snd_effect.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "HA.AUDIO.AMRWB.codec.h"
#include "HA.AUDIO.TRUEHDPASSTHROUGH.decode.h"
#include "HA.AUDIO.DTSHD.decode.h"
#include "HA.AUDIO.AC3PASSTHROUGH.decode.h"
#include "HA.AUDIO.DTSPASSTHROUGH.decode.h"
#include "hi_adp_audio.h"
#include "hi_adp_mpi.h"
#include "hi_adp_hdmi.h"
#include "hi_aef_srs.h"

//#define MULTI_AEF

#if defined (DOLBYPLUS_HACODEC_SUPPORT)
 #include "HA.AUDIO.DOLBYPLUS.decode.h"
#endif

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif
FILE   *g_pAudEsFile;

static pthread_t g_EsThd;
static HI_HANDLE hAvplay;
HI_S32 g_AudEsFileOffest;

static HI_BOOL g_StopThread = HI_FALSE;


HI_VOID AudioTthread(HI_VOID *args)
{
    HI_UNF_STREAM_BUF_S StreamBuf;
    HI_U32 Readlen;
    HI_S32 Ret;
    HI_BOOL bAudBufAvail = HI_TRUE;
    
    bAudBufAvail = HI_FALSE;

    while (!g_StopThread)
    {
        Ret = HI_UNF_AVPLAY_GetBuf(hAvplay, HI_UNF_AVPLAY_BUF_ID_ES_AUD, 0x1000, &StreamBuf, 0);
        if (HI_SUCCESS == Ret)
        {
            bAudBufAvail = HI_TRUE;
            Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), 0x1000, g_pAudEsFile);
            if (Readlen > 0)
            {
                Ret = HI_UNF_AVPLAY_PutBuf(hAvplay, HI_UNF_AVPLAY_BUF_ID_ES_AUD, Readlen, 0);
                if (Ret != HI_SUCCESS)
                {
                    sample_printf("call HI_UNF_AVPLAY_PutBuf failed.\n");
                }
            }
            else if (Readlen <= 0)
            {
                sample_printf("read aud file error!\n");
                rewind(g_pAudEsFile);
                if (g_AudEsFileOffest)
                {
                    fseek(g_pAudEsFile, g_AudEsFileOffest, SEEK_SET);
                }
            }
        }
        else if (Ret != HI_SUCCESS)
        {
            bAudBufAvail = HI_FALSE;
        }

        /* wait for buffer */
        if (HI_FALSE == bAudBufAvail)
        {
            usleep(1000 * 10);
        }
    }

    return;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 Ret;
    HI_HANDLE hTrack;
    HI_HANDLE hAef;
#ifdef MULTI_AEF    
    HI_HANDLE hAef1;
#endif
	HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;
    HI_UNF_SND_ATTR_S stAttr;
    
    HI_U32 AdecType;
    HI_UNF_AVPLAY_ATTR_S AvplayAttr;
    HI_UNF_SYNC_ATTR_S AvSyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S Stop;
    HI_CHAR InputCmd[32];
    HI_HA_DECODEMODE_E enAudioDecMode = HD_DEC_MODE_RAWPCM;
    HI_S32 s32DtsDtsCoreOnly = 0;
    HI_AEF_SRS_OPENPARAM_S stOpenDfAttr;
    
    if (argc < 3)
    {
        sample_printf(" usage: ./sample_srsaudioplay afile1 atype1\n"
                      "        ./sample_srsaudioplay afile1 atype1 afile2 atype2\n"
                      "        ./sample_srsaudioplay afile1 atype1 afile2 atype2 afile3 atype3\n");
        sample_printf(" atype: aac/mp3/dts/dra/mlp/pcm/ddp(ac3/eac3)\n");
        sample_printf(" examples: \n");
        sample_printf("        ./sample_srsaudioplay father.mp3 mp3 \n");
        return -1;
    }

    g_pAudEsFile = fopen(argv[1], "rb");
    if (!g_pAudEsFile)
    {
        sample_printf("open file %s error!\n", argv[1]);
        return -1;
    }

    if (!strcasecmp("aac", argv[2]))
    {
        AdecType = HA_AUDIO_ID_AAC;
    }
    else if (!strcasecmp("mp3", argv[2]))
    {
        AdecType = HA_AUDIO_ID_MP3;
    }

    else if (!strcasecmp("ac3raw", argv[2]))
    {
        AdecType = HA_AUDIO_ID_AC3PASSTHROUGH;
    }
    else if (!strcasecmp("dtsraw", argv[2]))
    {
        AdecType = HA_AUDIO_ID_DTSPASSTHROUGH;
    }
#if defined (DOLBYPLUS_HACODEC_SUPPORT)
    else if (!strcasecmp("ddp", argv[2]))
    {
        AdecType = HA_AUDIO_ID_DOLBY_PLUS;
    }
#endif
    else if (!strcasecmp("dts", argv[2]))
    {
        AdecType = HA_AUDIO_ID_DTSHD;
    }
    else if (!strcasecmp("dra", argv[2]))
    {
        AdecType = HA_AUDIO_ID_DRA;
    }
    else if (!strcasecmp("pcm", argv[2]))
    {
        AdecType = HA_AUDIO_ID_PCM;
    }
    else if (!strcasecmp("mlp", argv[2]))
    {
        AdecType = HA_AUDIO_ID_TRUEHD;
    }
    else if (!strcasecmp("amr", argv[2]))
    {
        AdecType = HA_AUDIO_ID_AMRNB;
    }
    else if (!strcasecmp("amrwb", argv[2]))
    {
        AdecType = HA_AUDIO_ID_AMRWB;
#if 1
        /*read header of file for MIME file format */
        extern HI_U8 u8DecOpenBuf[1024];
        AMRWB_DECODE_OPENCONFIG_S *pstConfig = (AMRWB_DECODE_OPENCONFIG_S *)u8DecOpenBuf;
        if (pstConfig->enFormat == AMRWB_FORMAT_MIME)
        {
            HI_U8 u8MagicBuf[8];

            fread(u8MagicBuf, sizeof(HI_S8), strlen(AMRWB_MAGIC_NUMBER), g_pAudEsFile);/* just need by amr file storage format (xxx.amr) */
            if (strncmp((const char *)u8MagicBuf, AMRWB_MAGIC_NUMBER, strlen(AMRWB_MAGIC_NUMBER)))
            {
                sample_printf( "%s Invalid amr wb file magic number ", u8MagicBuf);
                return HI_FAILURE;
            }
        }
        g_AudEsFileOffest = strlen(AMRWB_MAGIC_NUMBER);
#endif
    }
    else
    {
        sample_printf("unsupport aud codec type!\n");
        return -1;
    }

    HI_SYS_Init();
    Ret = HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HI_UNF_SND_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_Init failed.\n");
        goto AVPLAY_DEINIT;
    }
    
    HI_UNF_SND_GetDefaultOpenAttr(HI_UNF_SND_0, &stAttr);
    Ret = HI_UNF_SND_Open(HI_UNF_SND_0, &stAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_Open failed.\n");
        goto SND_CLOSE;
    }
 
    Ret = HIADP_Snd_RegAefAuthLib();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_RegisterAefAuthLib failed.\n");
        goto SND_CLOSE;
    }

    Ret = HIADP_AVPlay_RegADecLib();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_RegisterAcodecLib failed.\n");
        goto SND_CLOSE;
    }

    Ret  = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_ES);
    
    Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DESTROY;
    }
    Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &AvSyncAttr);
    AvSyncAttr.enSyncRef = HI_UNF_SYNC_REF_NONE;
    Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &AvSyncAttr);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto AVPLAY_DESTROY;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
      sample_printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
      goto ACHN_CLOSE;
    }
        
    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);

    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&hTrack);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto TRACK_DESTROY;
    }
    
    HI_AEF_SRS_OPENPARAM_S stSRSParams;
    HI_AEF_SRS_PARAM_S     stParams;
    HI_AEF_SRS_CONFIG_S    stSRSConfig;
    stSRSParams.pstSRSParam = &stParams;
    stSRSParams.pstSRSConfig = &stSRSConfig;
    HI_AEF_SRS_GetDefaultOpenParam(&stSRSParams);
    stSRSConfig.stMainConfig.bEnable =HI_TRUE;

    Ret = HI_UNF_SND_CreateAef(HI_UNF_SND_0, HI_UNF_SND_AEF_TYPE_SRS3D, (HI_VOID *)(&stOpenDfAttr), &hAef);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_CreateAef failed.\n");
        goto AEF_DESTROY;
    }

    HI_UNF_SND_SetAefParams(hAef, 0, stSRSParams.pstSRSParam);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_SetAefParams failed.\n");
        goto AEF_DESTROY;
    }    
    HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_All, stSRSParams.pstSRSConfig);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_SetAefConfig failed.\n");
        goto AEF_DESTROY;
    }
    
    Ret = HI_UNF_SND_SetAefEnable(hAef, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_SetAefEnable failed.\n");
        goto AEF_DISABLE;
    }    

        Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_SND_Attach failed.\n");
            goto SND_DETACH;
        }
        Ret = HIADP_AVPlay_SetAdecAttr(hAvplay, AdecType, enAudioDecMode, s32DtsDtsCoreOnly);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HIADP_AVPlay_SetAdecAttr failed.\n");
            goto SND_DETACH;
        }
        Ret = HI_UNF_AVPLAY_Start(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_AVPLAY_Start failed.\n");
        }

#if 0
    Ret = HIADP_Disp_Init(g_enDefaultFmt);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call DispInit failed.\n");
        goto SND_DETACH;
    }
#endif
    g_StopThread = HI_FALSE;
    pthread_create(&g_EsThd, HI_NULL, (HI_VOID *)AudioTthread, (HI_VOID *)HI_UNF_SND_0);

    while (1)
    {
        sample_printf("\nplease input the q to quit!, s to toggle spdif pass-through, h to toggle hdmi mode\n"
                      "mh/s/a/l to toggle hdmi/spdif/adac/all mute, uh/s/a/l to toggle hdmi/spdif/adac/all unmute\n"
                      "please input the tn to toggle trackMode, v to decrease volume, e to increase volume\n"
                      "p to toggle pause, o to toggle stop/start, r to toggle reset\n\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        stSRSParams.pstSRSConfig->stMainConfig.bEnable = !(stSRSParams.pstSRSConfig->stMainConfig.bEnable);
        sample_printf("f32MainTech Enable:%d \n",stSRSParams.pstSRSConfig->stMainConfig.bEnable);
        HI_UNF_SND_SetMute((HI_UNF_SND_E)HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, HI_TRUE);
        HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_All, stSRSParams.pstSRSConfig);
        usleep(1000 * 200);
        HI_UNF_SND_SetMute((HI_UNF_SND_E)HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, HI_FALSE);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_SND_SetAefConfig failed.\n");
            goto SND_DETACH;
        }
        
        if ('q' == InputCmd[0])
        {
            sample_printf("prepare to quit!\n");
            break;
        }

        if (('m' == InputCmd[0]) || ('u' == InputCmd[0]))
        {
            static HI_UNF_SND_OUTPUTPORT_E enPort;
            if('a' == InputCmd[1])
            {
                enPort = HI_UNF_SND_OUTPUTPORT_DAC0;
            }
            else if('s' == InputCmd[1])
            {
                enPort = HI_UNF_SND_OUTPUTPORT_SPDIF0;
            }
            else if('h' == InputCmd[1])
            {
                enPort = HI_UNF_SND_OUTPUTPORT_HDMI0;
            }
            else if('l' == InputCmd[1])
            {
                enPort = HI_UNF_SND_OUTPUTPORT_ALL;
            }
            else
            {
                sample_printf("Invalid port!\n");
                continue;
            }
            
            if ('m' == InputCmd[0])
            {
                HI_UNF_SND_SetMute((HI_UNF_SND_E)HI_UNF_SND_0, enPort, HI_TRUE);
                sample_printf("Snd %d Mute on!\n", HI_UNF_SND_0);
            }
            else if('u' == InputCmd[0])
            {
                HI_UNF_SND_SetMute((HI_UNF_SND_E)HI_UNF_SND_0, enPort, HI_FALSE);
                sample_printf("Snd %d Mute off!\n", HI_UNF_SND_0);
            }
        }

        static HI_UNF_SND_GAIN_ATTR_S volume_toggle = {HI_TRUE, 100};
        
        if ('v' == InputCmd[0])
        {
            volume_toggle.s32Gain -= 10;
            if(volume_toggle.s32Gain < 0)
            {
                volume_toggle.s32Gain = 0;
            }
            HI_UNF_SND_SetVolume((HI_UNF_SND_E)HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, &volume_toggle);
            sample_printf("Snd %d volume[%d]!\n", 0, volume_toggle.s32Gain);
        }

        if ('V' == InputCmd[0])
        {
            volume_toggle.s32Gain = 0;
            HI_UNF_SND_SetVolume((HI_UNF_SND_E)HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, &volume_toggle);
            sample_printf("Snd %d volume[%d]!\n", 0, volume_toggle.s32Gain);
        }


        if ('e' == InputCmd[0])
        {
            volume_toggle.s32Gain += 10;
            if(volume_toggle.s32Gain > 100)
            {
                volume_toggle.s32Gain = 100;
            }
            HI_UNF_SND_SetVolume((HI_UNF_SND_E)HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, &volume_toggle);
            sample_printf("Snd %d volume[%d]!\n", HI_UNF_SND_0, volume_toggle.s32Gain);
        }

        if ('E' == InputCmd[0])
        {
            volume_toggle.s32Gain = 100;
            HI_UNF_SND_SetVolume((HI_UNF_SND_E)HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, &volume_toggle);
            sample_printf("Snd %d volume[%d]!\n", HI_UNF_SND_0, volume_toggle.s32Gain);
        }
     
        if (('p' == InputCmd[0]) || ('P' == InputCmd[0]))
        {
            static HI_U32 pause_toggle = {0};
            pause_toggle++;
            if (pause_toggle & 1)
            {
                HI_UNF_AVPLAY_Pause(hAvplay, HI_NULL);
                sample_printf("Track of snd %d pause on!\n", HI_UNF_SND_0);
            }
            else
            {
                HI_UNF_AVPLAY_Resume(hAvplay, HI_NULL);
                sample_printf("Track of snd %d pause off!\n", HI_UNF_SND_0);
            }
        }

        if (('o' == InputCmd[0]) || ('O' == InputCmd[0]))
        {
            static HI_U32 stop_toggle = {0};

            stop_toggle++;
            if (stop_toggle & 1)
            {
                HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
                //HI_MPI_AO_Track_Stop(hTrack[u32InVal]);
                sample_printf("Track of snd %d stop!\n", HI_UNF_SND_0);
            }
            else
            {
                HI_UNF_AVPLAY_Start(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
                //HI_MPI_AO_Track_Start(hTrack[u32InVal]);
                sample_printf("Track of snd %d start!\n", HI_UNF_SND_0);
            }
        }
        if (('b' == InputCmd[0]) || ('B' == InputCmd[0]))
        {            
            static HI_U32 bypass_toggle = {0};
            bypass_toggle++;
            if(bypass_toggle & 1)
            {
                HI_UNF_SND_SetAefBypass(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, HI_TRUE);
                sample_printf("enport %d aef bypass\n", HI_UNF_SND_OUTPUTPORT_ALL);
            }
            else
            {
                HI_UNF_SND_SetAefBypass(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, HI_FALSE);
                sample_printf("enport %d aef not bypass\n", HI_UNF_SND_OUTPUTPORT_ALL);
            }    
        }
    }

    g_StopThread = HI_TRUE;
    pthread_join(g_EsThd, HI_NULL);

    Stop.u32TimeoutMs = 0;
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

AEF_DISABLE:
    HI_UNF_SND_SetAefEnable(hAef, HI_FALSE);    
    
AEF_DESTROY:
    HI_UNF_SND_DestroyAef(hAef);    
    
TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);    

ACHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);    
    
AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(hAvplay);    
    
SND_CLOSE:
    HI_UNF_SND_Close(HI_UNF_SND_0);      
    
AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();      

SYS_DEINIT:
    HI_SYS_DeInit();    

    fclose(g_pAudEsFile);
    g_pAudEsFile = HI_NULL;

    return 0;
}
