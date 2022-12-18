/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mplayer.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
  History       :
  1.Date        : 2010/01/26
    Author      : w58735
    Modification: Created file

******************************************************************************/
#include <pthread.h>
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
#include "hi_unf_hdmi.h"
#include "hi_unf_ecs.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "hi_adp.h"
#include "hi_adp_audio.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_boardcfg.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"
#include "hi_transcoder.h"
#include "hi_protocol.h"
#include "hi_muxer.h"
//#include "hi_rtsp_wfd.h"

HI_U32 g_TunerFreq = 0;
HI_U32 g_TunerSrate = 6875;
HI_U32 g_TunerQam = 64;
HI_S32 g_TranOuts32X;                    /*转码的起始位置 X 坐标*/
HI_S32 g_TranOuts32Y;                    /*转码的起始位置 Y 坐标*/
HI_S32 g_TranOuts32Width = 720;                /*视频分辨率--高*/
HI_S32 g_TranOuts32Height = 576;               /*视频分辨率--宽*/
HI_U32 g_TranOutu32VideoBitRate = 1024 * 1024;             /*视频比特率*/
HI_S32 g_TranOuts32VideoFrameRate = 30;           /*视频帧率*/
HI_S32 g_TranOuts32AudioSampleRate = 48000;          /*音频采样率*/
HI_S32 g_TranOuts32AudioBandWidth = 16;           /*音频采样宽度*/
HI_S32 g_TranOuts32AudioChannels = 2;            /*音频采样的声道数量*/
HI_S32 g_TranOuts32Gop = 10;                    /*I帧间隔*/
Transcoder_ProtocolType g_TranProtocolType = TRANSCODER_PROTOCOL_SAMPLE;


static HI_UNF_ENC_FMT_E   g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;

PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;

#ifndef DEFAULT_DVB_PORT
#define DEFAULT_DVB_PORT 0
#endif

static HI_S32 ParseCmd(char* pCommandStr)
{
    HI_U32 u32BitRateX = 0,u32BitRateY = 0,u32BitRateZ = 0;
    const char* pWidth = "w=";
    const char* pHeight = "h=";
    const char* pVideoBitRate = "b=";
    const char* pVideoFrameRate = "f=";
    const char* pAudioSampleRate = "s=";
    const char* pAudioChannel = "c=";
    const char* pfreq = "freq=";
    const char* psrate = "srate=";
    const char* pqam = "qam=";
    const char* protocol = "pro=";
    const char* mulFlag = "*";
    const char* pband = "band=";
    const char* pgop = "gop=";
    char* pTmpPoint = HI_NULL;

    if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pWidth)))
    {
        pTmpPoint += strlen((char*)pWidth);
        g_TranOuts32Width = atoi(pTmpPoint);
        printf("tran width : %d\n",g_TranOuts32Width);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pHeight)))
    {
        pTmpPoint += strlen((char*)pHeight);
        g_TranOuts32Height = atoi(pTmpPoint);
        printf("tran height : %d\n",g_TranOuts32Height);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pVideoBitRate)))
    {
        pTmpPoint += strlen((char*)pVideoBitRate);
        u32BitRateX = atoi(pTmpPoint);
        if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)mulFlag)))
        {
            pTmpPoint += strlen((char*)mulFlag);
            u32BitRateY = atoi(pTmpPoint);
            printf("pTmpPoint : %s\n",pTmpPoint);
            if(HI_NULL != (pTmpPoint = strstr(pTmpPoint,(char*)mulFlag)))
            {
                printf("~~pTmpPoint : %s\n",pTmpPoint);
                pTmpPoint += strlen((char*)mulFlag);
                u32BitRateZ = atoi(pTmpPoint);
                g_TranOutu32VideoBitRate = u32BitRateX * u32BitRateY * u32BitRateZ;
            }else
            {
                g_TranOutu32VideoBitRate = u32BitRateX * u32BitRateY;
            }
        }else
        {
            g_TranOutu32VideoBitRate = u32BitRateX;
        }
        printf("tran video bitrate : %d\n",g_TranOutu32VideoBitRate);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pVideoFrameRate)))
    {
        pTmpPoint += strlen((char*)pVideoFrameRate);
        g_TranOuts32VideoFrameRate = atoi(pTmpPoint);
        printf("tran video framerate : %d\n",g_TranOuts32VideoFrameRate);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pAudioSampleRate)))
    {
        pTmpPoint += strlen((char*)pAudioSampleRate);
        g_TranOuts32AudioSampleRate = atoi(pTmpPoint);
        printf("tran audio samplerate : %d\n",g_TranOuts32AudioSampleRate);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pAudioChannel)))
    {
        pTmpPoint += strlen((char*)pAudioChannel);
        g_TranOuts32AudioChannels = atoi(pTmpPoint);
        printf("tran audio samplerate : %d\n",g_TranOuts32AudioChannels);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pfreq)))
    {
        pTmpPoint += strlen((char*)pfreq);
        g_TunerFreq = atoi(pTmpPoint);
        printf("tuner freq : %d\n",g_TunerFreq);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)psrate)))
    {
        pTmpPoint += strlen((char*)psrate);
        g_TunerSrate = atoi(pTmpPoint);
        printf("tuner sample rate : %d\n",g_TunerSrate);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pqam)))
    {
        pTmpPoint += strlen((char*)pqam);
        g_TunerQam = atoi(pTmpPoint);
        printf("tuner  qam : %d\n",g_TunerQam);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)protocol)))
    {
        pTmpPoint += strlen((char*)protocol);
        if(HI_NULL != strstr(pTmpPoint,(char*)"http"))
        {
            g_TranProtocolType = TRANSCODER_PROTOCOL_HTTP;
        }
        else if(HI_NULL != strstr(pTmpPoint,(char*)"rtsp"))
        {
            g_TranProtocolType = TRANSCODER_PROTOCOL_RTSP;
        }
        else if(HI_NULL != strstr(pTmpPoint,(char*)"local"))
        {
            g_TranProtocolType = TRANSCODER_PROTOCOL_SAMPLE;
        }
        printf("tuner  qam : %d\n",g_TunerQam);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pband)))
    {
        pTmpPoint += strlen((char*)pband);
        printf("pTmpPoint  pband : %s\n",pTmpPoint);
        g_TranOuts32AudioBandWidth = atoi(pTmpPoint);
        printf("audio  pband : %d\n",g_TranOuts32AudioBandWidth);
    }
    else if(HI_NULL != (pTmpPoint = strstr(pCommandStr,(char*)pgop)))
    {
        pTmpPoint += strlen((char*)pgop);
        g_TranOuts32Gop = atoi(pTmpPoint);
        printf("tran video pgop : %d\n",g_TranOuts32Gop);
    }
    else
    {
        printf("parse error!!!\n");
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}


HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                  Ret,index;
    HI_HANDLE               hWin = 0;
    HI_HANDLE               hAvplay = 0;
    HI_HANDLE               hTranscoderHandle = 0;
    HI_HANDLE               hProtocolHandle = 0;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_CHAR                 InputCmd[32];
    HI_U32                  ProgNum;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;
    HI_HANDLE hTrack = 0;
    Transcoder_HandleAttr stTranHandleAttr;
    ProtocolAttr protoAttr;
    HI_U32 value;
    HI_CHAR    InputValue[32];

    memset(&stTranHandleAttr,0,sizeof(Transcoder_HandleAttr));

    for(index = 1;index < argc;index++)
    {
        ParseCmd(argv[index]);
    }
    if (0 != g_TunerFreq)
    {

    }
    else
    {
        printf("Usage: sample_transcoder_dvbplayer freq=307 [srate=6875] [qam=64] [w=1280] [h=720] [f=25] [b=4*1024*1024] [pro=http]\n"
                  "srate:samplerate:6875\n"
                  "qam:qamtype:16|32|64|128|256|512\n"
                  "pro:protocol:rtsp|http|local\n"
                  "w:width:320|640|720|1280|1920\n"
                  "h:height:240|480|576|720|1080\n"
                  "f:framerate:10|15|20|25|30\n"
                  "b:videorbitrate:256*1024|512*1024|1024*1024|2*1024*1024|4*1024*1024|8*1024*1024\n"
               );
        printf("Example:./sample_transcoder_dvbplayer  freq=610 srate=6875 qam=64 f=25 w=1280 h=720 pro=rtsp b=4*1024*1024\n");
        return HI_FAILURE;
    }

    HI_SYS_Init();
    HIADP_MCE_Exit();
    Ret = HI_Transcoder_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_Transcoder_Init failed.\n");
        goto SYS_DEINIT;
    }
    Ret = HI_Protocol_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_Protocol_Init failed.\n");
        HI_Transcoder_DeInit();
        goto SYS_DEINIT;
    }
    Ret = HI_Muxer_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_Muxer_Init failed.\n");
        HI_Protocol_DeInit();
        HI_Transcoder_DeInit();
        goto SYS_DEINIT;
    }
    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Snd_Init failed.\n");
        goto SYS_DEINIT;
    }
    //HI_SYS_GetPlayTime(& u32Playtime);
    //sample_printf("u32Playtime = %d\n",u32Playtime);
    Ret = HIADP_Disp_Init(g_enDefaultFmt);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Disp_DeInit failed.\n");
        goto SND_DEINIT;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    Ret |= HIADP_VO_CreatWin(HI_NULL,&hWin);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_VO_Init failed.\n");
        HIADP_VO_DeInit();
        goto DISP_DEINIT;
    }

    Ret = HI_UNF_DMX_Init();
    Ret |= HI_UNF_DMX_AttachTSPort(0,DEFAULT_DVB_PORT);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Demux_Init failed.\n");
        goto VO_DEINIT;
    }

    Ret = HIADP_Tuner_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Demux_Init failed.\n");
        goto DMX_DEINIT;
    }

    Ret = HIADP_Tuner_Connect(TUNER_USE,g_TunerFreq,g_TunerSrate,g_TunerQam);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Tuner_Connect failed.\n");
        goto TUNER_DEINIT;
    }

    HIADP_Search_Init();
    Ret = HIADP_Search_GetAllPmt(0,&g_pProgTbl);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Search_GetAllPmt failed\n");
        goto PSISI_FREE;
    }

    Ret = HIADP_AVPlay_RegADecLib();
    Ret |= HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto PSISI_FREE;
    }

    Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.stStreamAttr.u32VidBufSize = 0x300000;
    Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    Ret |= HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto CHN_CLOSE;
    }

    Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_VO_AttachWindow failed.\n");
        goto CHN_CLOSE;
    }
    Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (HI_SUCCESS != Ret)
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
        printf("call HI_SND_Attach failed.\n");
        goto WIN_DETACH;
    }

    Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    SyncAttr.stSyncStartRegion.s32VidPlusTime = 60;
    SyncAttr.stSyncStartRegion.s32VidNegativeTime = -20;
    SyncAttr.bQuickOutput = HI_FALSE;
    Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    Transcoder_getDefaultAttr(&stTranHandleAttr);
    stTranHandleAttr.s32Width = g_TranOuts32Width ;
    stTranHandleAttr.s32Height = g_TranOuts32Height ;
    stTranHandleAttr.u32VideoBitRate = g_TranOutu32VideoBitRate ;
    stTranHandleAttr.s32VideoFrameRate =  g_TranOuts32VideoFrameRate;
    stTranHandleAttr.s32AudioSampleRate = g_TranOuts32AudioSampleRate;
    stTranHandleAttr.s32AudioBandWidth = g_TranOuts32AudioBandWidth;
    stTranHandleAttr.s32AudioChannels = g_TranOuts32AudioChannels;
    stTranHandleAttr.s32Gop = g_TranOuts32Gop;
    stTranHandleAttr.hSrc = hAvplay;
    stTranHandleAttr.bCycle = HI_FALSE;
    printf("~!@#$~!@~!@~! u32VideoBitRate : %d\n",stTranHandleAttr.u32VideoBitRate);
    Ret = HI_Transcoder_Create(&hTranscoderHandle,&stTranHandleAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_Transcoder_Create failed.\n");
        goto AVPLAY_STOP;
    }
    protoAttr.s32Port = 4098;
    protoAttr.s32UserNum = 8;
    protoAttr.SourceHandle = hAvplay;
    protoAttr.u32ProtocolType = g_TranProtocolType;
    if(g_TranProtocolType == TRANSCODER_PROTOCOL_SAMPLE)
    {
        Ret = HI_Protocol_RegistProtocol("libprotocol_local.so");
        if(HI_SUCCESS != Ret)
        {
           printf("HI_Protocol_RegistProtocol error!\n");
        }
    }
    Ret = HI_Protocol_Create(&hProtocolHandle,&protoAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_Protocol_Create failed.\n");
        HI_Transcoder_Destroy(hTranscoderHandle);
        goto AVPLAY_STOP;
    }
    ProgNum = 6;
    Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum,HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        printf("call SwitchProg failed.\n");
        goto AVPLAY_STOP;
    }
    Ret = HI_Protocol_RegistHandle(hProtocolHandle,hTranscoderHandle);
    if(HI_SUCCESS != Ret)
    {
        printf("HI_Protocol_RegistHandle error\n");
        HI_Transcoder_Destroy(hTranscoderHandle);
        HI_Protocol_destory(hProtocolHandle);
        return Ret;
    }

    while(1)
    {
        printf("please input the 'q' to quit,'r' to set resolution ratio 'f' to set frameRate,'b'to set biteRate,'g'to set gop!\n");
        fgets(InputCmd, 30, stdin);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
        switch(InputCmd[0])
        {
            case 'b':
                printf("please input the biteRate value,eg:350000,4000000,10000000\n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 32*1024)||(value > 42*1024*1024))
                {
                    printf("input the wrong biteRate value\n");
                }
                else
                {
                    Ret = HI_Transcoder_GetAttr((HI_HANDLE)hTranscoderHandle,TRANSCODER_ALL_ATTR, &stTranHandleAttr);
                    if(HI_SUCCESS != Ret)
                    {
                        printf("HI_Transcoder_GetAttr failed\n");
                        continue;
                    }
                    stTranHandleAttr.u32VideoBitRate = value;
                    Ret = HI_Transcoder_SetAttr( (HI_HANDLE)hTranscoderHandle,TRANSCODER_ALL_ATTR,&stTranHandleAttr);
                    if(HI_SUCCESS != Ret)
                    {
                        printf("HI_Transcoder_SetAttr failed\n");
                    }
                }
                continue;
            case 'f':
                printf("please input the frameRate value,eg:15,20,25\n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 1)||(value > 60))
                {
                    printf("input the wrong frameRate value\n");
                }
                else
                {
                    Ret = HI_Transcoder_GetAttr((HI_HANDLE)hTranscoderHandle,TRANSCODER_ALL_ATTR, &stTranHandleAttr);
                    if(HI_SUCCESS != Ret)
                    {
                        printf("HI_Transcoder_GetAttr failed\n");
                        continue;
                    }
                    stTranHandleAttr.s32VideoFrameRate = value;
                    printf("hejinghai..HI_Transcoder_setAttr\n");
                    Ret = HI_Transcoder_SetAttr( (HI_HANDLE)hTranscoderHandle,TRANSCODER_ALL_ATTR,&stTranHandleAttr);
                    if(HI_SUCCESS != Ret)
                    {
                        printf("HI_Transcoder_SetAttr failed\n");
                    }
                }
                continue;
            case 'r':
                printf("Usage:suggest resolution ratio is :\n"
                "QCIF:176*144,CIF:352*288,QVGA:320*240,VGA:640*480,D1:720*576,720P:1280*720,1080P:1920*1080\n"
                "please input the width value first\n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 176)||(value > 1920))
                {
                    printf("input the wrong width value\n");
                    continue;
                }
                else
                {
                    Ret = HI_Transcoder_GetAttr((HI_HANDLE)hTranscoderHandle,TRANSCODER_ALL_ATTR, &stTranHandleAttr);
                    if(HI_SUCCESS != Ret)
                    {
                        printf("HI_Transcoder_GetAttr failed\n");
                        continue;
                    }
                    stTranHandleAttr.s32Width = value;
                }
                printf("then please input the height value \n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 144)||(value > 1088))
                {
                    printf("input the wrong height value\n");
                }
                else
                {
                    stTranHandleAttr.s32Height = value;
                    Ret = HI_Transcoder_SetAttr( (HI_HANDLE)hTranscoderHandle,TRANSCODER_ALL_ATTR,&stTranHandleAttr);
                    if(HI_SUCCESS != Ret)
                    {
                        printf("HI_Transcoder_SetAttr failed\n");
                    }

                }
                continue;
            case 'g':
                printf("please input the GOP value\n");
                fgets(InputValue, 30, stdin);
                value = atoi(InputValue);
                if((value < 1)||(value > 65535))
                {
                    printf("input the wrong gop value\n");
                }
                else
                {
                    Ret = HI_Transcoder_GetAttr((HI_HANDLE)hTranscoderHandle,TRANSCODER_ALL_ATTR, &stTranHandleAttr);
                    if(HI_SUCCESS != Ret)
                    {
                        printf("HI_Transcoder_GetAttr failed\n");
                        continue;
                    }
                    stTranHandleAttr.s32Gop= value;
                    Ret = HI_Transcoder_SetAttr( (HI_HANDLE)hTranscoderHandle,TRANSCODER_ALL_ATTR,&stTranHandleAttr);
                    if(HI_SUCCESS != Ret)
                    {
                        printf("HI_Transcoder_SetAttr failed\n");
                    }
                }
                continue;
        }

        ProgNum = atoi(InputCmd);

        if(ProgNum == 0)
        {
            ProgNum = 2;
       }
        Ret = HI_Protocol_WFD_SetClientCommand(hProtocolHandle, WFD_SOURCE_METHOD_RESET,HI_FALSE);
        if(HI_SUCCESS != Ret)
        {
            printf("call HI_Protocol_WFD_SetClientCommand failed!\n");
        }
        Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum-1,HI_TRUE);
        if (Ret != HI_SUCCESS)
        {
            printf("call SwitchProgfailed!\n");
            break;
        }
    }
    Ret = HI_Protocol_UnRegistHandle(hProtocolHandle,hTranscoderHandle);
    if(HI_SUCCESS != Ret)
    {
        printf("HI_Protocol_UnRegistHandle error\n");
    }

    Ret = HI_Protocol_destory(hProtocolHandle);
    if(HI_SUCCESS != Ret)
    {
        printf("HI_Protocol_destory error\n");
    }

    Ret = HI_Transcoder_Destroy(hTranscoderHandle);
    if(HI_SUCCESS != Ret)
    {
        printf("HI_Transcoder_Destroy error\n");
    }
    Ret = HI_Muxer_DeInit();
    if(HI_SUCCESS != Ret)
    {
        printf("HI_Muxer_DeInit error\n");
    }
    Ret = HI_Protocol_DeInit();
    if(HI_SUCCESS != Ret)
    {
        printf("HI_Protocol_DeInit error\n");
    }
    Ret = HI_Transcoder_DeInit();
    if(HI_SUCCESS != Ret)
    {
        printf("HI_Transcoder_DeInit error\n");
    }

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

SND_DETACH:
    HI_UNF_SND_Detach(hTrack, hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(hWin,HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, hAvplay);

CHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

    HI_UNF_AVPLAY_Destroy(hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

PSISI_FREE:
    HIADP_Search_FreeAllPmt(g_pProgTbl);
    HIADP_Search_DeInit();

TUNER_DEINIT:
    HIADP_Tuner_DeInit();

DMX_DEINIT:
    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();

VO_DEINIT:
    HI_UNF_VO_DestroyWindow(hWin);
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

SND_DEINIT:
    HIADP_Snd_DeInit();

SYS_DEINIT:
    HI_SYS_DeInit();

    return Ret;
}
