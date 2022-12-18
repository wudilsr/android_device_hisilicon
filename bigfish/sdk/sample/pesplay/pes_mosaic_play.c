/******************************************************************************

  Copyright (C), 2001-2020, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pes_mosaic_play.c
  Version       : Initial Draft
  Author        : l00168554
  Created       : 2011/07/06
  Description   :
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "HA.AUDIO.TRUEHDPASSTHROUGH.decode.h"
#include "HA.AUDIO.DTSHD.decode.h"

#include "hi_adp_audio.h"
#include "hi_adp_mpi.h"
#include "hi_adp_hdmi.h"
#include "hi_unf_pes.h"
#include "hi_unf_avplay.h"
#if defined(DOLBYPLUS_HACODEC_SUPPORT)
#include "HA.AUDIO.DOLBYPLUS.decode.h"
#endif

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

#define AVPLAY_AUDIO_BUFF_SIZE    (2 * 1024 * 1024)
#define AVPLAY_VIDEO_BUFF_SIZE    (9 * 1024 * 1024)

#define __MAX_PES_INPUT_NUM__ 4

static FILE       *g_pPEsFile[__MAX_PES_INPUT_NUM__];
static pthread_t   g_EsThd[__MAX_PES_INPUT_NUM__];
static HI_BOOL     g_StopThread[__MAX_PES_INPUT_NUM__];
static HI_HANDLE   g_PEShandle[__MAX_PES_INPUT_NUM__];

static HI_VOID PESTthread(HI_VOID *arg)
{
    HI_U32            Readlen;
    HI_S32            Ret, index;
    HI_HANDLE         PESHandle;
    HI_BOOL           bPESBufAvailable = HI_FALSE;
    HI_U32            RequireSize = 0;
    HI_U32            RewindFlag  = HI_FALSE;
    HI_UNF_STREAM_BUF_S stPESData;
    HI_U32            current_index = 0xff;

    PESHandle = *((HI_HANDLE *)arg);
    //printf("args:0x%x, PESHandle:0x%x\n", (HI_U32)arg, (HI_U32)PESHandle);

    for(index = 0; index < __MAX_PES_INPUT_NUM__; index ++)
    {
        if(PESHandle == g_PEShandle[index])
        {
            current_index = index;
        }
    }

    if(current_index >= __MAX_PES_INPUT_NUM__)
    {
        sample_printf("Do not know this PES Handle:0x%x\n", PESHandle);
        return;
    }

    RequireSize = 20*1024;

    while (!(g_StopThread[current_index]))
    {
        Ret = HI_UNF_PES_GetBuffer(PESHandle, RequireSize, &stPESData);
        if (HI_SUCCESS == Ret)
        {
            bPESBufAvailable = HI_TRUE;

            if(RewindFlag == HI_TRUE)
            {
                //Just input a empty data to avoid rewind effect!
                Readlen = RequireSize;
                memset(stPESData.pu8Data, 0, RequireSize);
                RewindFlag = HI_FALSE;
            }
            else
            {
                Readlen = fread(stPESData.pu8Data, sizeof(HI_S8), RequireSize, g_pPEsFile[current_index]);
                //printf("PsBuf:0x%x, pu8Data[0,1,2,3]:0x%02x%02x%02x%02x\n", stPESData.pu8Data, stPESData.pu8Data[0], stPESData.pu8Data[1], stPESData.pu8Data[2], stPESData.pu8Data[3]);
            }

            //Judge and inject PES Data
            if (Readlen > 0)
            {
                if(Readlen != RequireSize)
                {
                    sample_printf("infor: Maybe come to end to Read PES file 0x%x, 0x%x\n", Readlen, RequireSize);
                }
                //sample_printf("PES Input PESHandle:0x%x\n", PESHandle);
                Ret = HI_UNF_PES_PutBuffer(PESHandle, Readlen);
                if (Ret != HI_SUCCESS )
                {
                    sample_printf("call HI_UNF_PES_PutPESBuffer failed.\n");
                }
            }
            else if(Readlen <= 0)
            {
                sample_printf("read file error!\n");
                RewindFlag = HI_TRUE;
                rewind(g_pPEsFile[current_index]);
                continue;
            }
        }
        else
        {
            bPESBufAvailable = HI_FALSE;
        }

        /* wait for buffer */
        if (HI_FALSE == bPESBufAvailable)
        {
            //printf("****Full*****\n");
            usleep(1000 * 10);
        }
    }
    return;
}

static HI_S32 Pes_Mosaic_Open(HI_U32 index, HI_U32 enVideoCodec, HI_U32 u32AdecTypeCodec, HI_HANDLE *ohAVHandle, HI_HANDLE *ohWin, HI_HANDLE *phTrack)
{
    HI_S32                      ret = HI_SUCCESS;
    HI_UNF_AVPLAY_ATTR_S        stAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_RECT_S                   stWinRect;
    HI_HANDLE                   AVPlayHandle;
    HI_HANDLE                   hWin;
    HI_UNF_AVPLAY_OPEN_OPT_S    stVidOpenOpt;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;

    // 2. Create AVPlayer
    ret = HI_UNF_AVPLAY_GetDefaultConfig(&stAttr, HI_UNF_AVPLAY_STREAM_TYPE_ES);
    if(ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_GetDefaultConfig failed.\n");
        return HI_FAILURE;
    }
    //Get Param from Hiplayer
    stAttr.stStreamAttr.u32AudBufSize = AVPLAY_AUDIO_BUFF_SIZE;
    stAttr.stStreamAttr.u32VidBufSize = AVPLAY_VIDEO_BUFF_SIZE;

    ret  = HI_UNF_AVPLAY_Create(&stAttr, &AVPlayHandle);
    if(ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_Create failed.\n");
        return HI_FAILURE;
    }

    // 4. Set Sync mode
    ret = HI_UNF_AVPLAY_GetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if(ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_GetAttr failed.\n");
        return HI_FAILURE;
    }
    if(index == 0)
    {
        SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    }
    else
    {
        SyncAttr.enSyncRef = HI_UNF_SYNC_REF_NONE;
    }
    ret = HI_UNF_AVPLAY_SetAttr(AVPlayHandle, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if(ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        return HI_FAILURE;
    }

    if((index == 0) && (u32AdecTypeCodec != 0))
    {
        // 5. Start Audio Play
        ret = HI_UNF_AVPLAY_ChnOpen(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL);
        if(ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_AVPLAY_ChnOpen (AUD) failed.\n");
            return HI_FAILURE;
        }

        ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
        if (ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
            return HI_FAILURE;
        }        
        ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, phTrack);
        if (ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_SND_CreateTrack failed.\n");
            return HI_FAILURE;
        }

        ret = HI_UNF_SND_Attach(*phTrack, AVPlayHandle);
        if (ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_SND_Attach failed.\n");
            return HI_FAILURE;
        }

        ret = HI_UNF_SND_SetTrackMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL,HI_UNF_TRACK_MODE_DOUBLE_MONO);
        if (ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_SND_SetTrackMode failed.\n");
            return HI_FAILURE;
        }

        ret = HIADP_AVPlay_SetAdecAttr(AVPlayHandle, u32AdecTypeCodec, HD_DEC_MODE_RAWPCM, 0);
        if (ret != HI_SUCCESS)
        {
            sample_printf("call HIADP_AVPlay_SetAdecAttr failed.\n");
            return HI_FAILURE;
        }
        ret = HI_UNF_AVPLAY_Start(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL);
        if(ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_AVPLAY_Start failed.\n");
            return HI_FAILURE;
        }
    }

    // 6. VO window create
    stWinRect.s32Width = 1280 / (__MAX_PES_INPUT_NUM__ / 2);
    stWinRect.s32Height = 720 / 2;
    stWinRect.s32X = (index % (__MAX_PES_INPUT_NUM__ / 2)) * stWinRect.s32Width;
    stWinRect.s32Y = (index / (__MAX_PES_INPUT_NUM__ / 2)) * stWinRect.s32Height;

    ret |= HIADP_VO_CreatWin(&stWinRect,&hWin);

    // 8. Start Video Play
    stVidOpenOpt.enDecType = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
    stVidOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_D1;
    stVidOpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_MPEG;
    ret = HI_UNF_AVPLAY_ChnOpen(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, NULL);
    if(ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_ChnOpen (VID) failed.\n");
        return HI_FAILURE;
    }

    ret = HI_UNF_VO_AttachWindow(hWin, AVPlayHandle);
    if (ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_VO_AttachWindow failed.\n");
        return HI_FAILURE;
    }

    ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        return HI_FAILURE;
    }

    ret = HIADP_AVPlay_SetVdecAttr(AVPlayHandle,enVideoCodec,HI_UNF_VCODEC_MODE_NORMAL);
    if (ret != HI_SUCCESS)
    {
        sample_printf("call HIADP_AVPlay_SetVdecAttr failed.\n");
        return HI_FAILURE;
    }

    ret = HI_UNF_AVPLAY_Start(AVPlayHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID, NULL);
    if(ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_Start failed.\n");
        return HI_FAILURE;
    }

    *ohAVHandle = AVPlayHandle;
    *ohWin      = hWin;
    return HI_SUCCESS;
}

static HI_S32 Pes_Close(HI_HANDLE hAVHandle, HI_HANDLE hWin, HI_HANDLE hTrack)
{
    HI_S32                    ret = HI_SUCCESS;
    HI_UNF_AVPLAY_STOP_OPT_S  Stop;

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    ret |= HI_UNF_AVPLAY_Stop(hAVHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD|HI_UNF_AVPLAY_MEDIA_CHAN_VID, &Stop);

    ret |= HI_UNF_SND_Detach(hTrack, hAVHandle);
    ret |= HI_UNF_SND_DestroyTrack(hTrack);
    ret |= HI_UNF_AVPLAY_ChnClose(hAVHandle, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

    ret |= HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
    ret |= HI_UNF_VO_DetachWindow(hWin, hAVHandle);
    ret |= HI_UNF_AVPLAY_ChnClose(hAVHandle, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    HI_UNF_VO_DestroyWindow(hWin);

    ret |= HI_UNF_AVPLAY_Destroy(hAVHandle);

    return HI_SUCCESS;
}

HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                      Ret, index, u32Pesfilenum;
    HI_UNF_VCODEC_TYPE_E        VdecType[__MAX_PES_INPUT_NUM__];
    HI_U32                      AdecType[__MAX_PES_INPUT_NUM__];
    HI_CHAR                     InputCmd[32];
    HI_UNF_ENC_FMT_E            enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_UNF_PES_OPEN_S           stOpenParam = {0};
    HI_HANDLE                   hAVPlay[__MAX_PES_INPUT_NUM__];
    HI_HANDLE                   hWin[__MAX_PES_INPUT_NUM__];
    HI_UNF_DISP_BG_COLOR_S      BgColor;

    HI_U32                      u32PESVideoType[__MAX_PES_INPUT_NUM__];
    HI_U32                      u32PES_AudioType[__MAX_PES_INPUT_NUM__];

    HI_HANDLE                   hTrack;

    if (argc < 5)
    {
        printf(" usage: sample_pes_mosaic_play filenum pes0file v0type a0type pes1file v1type pes2file v2type ... [vo_format] \n");
        printf(" filenum: input file number, Maximun number is 4\n");
        printf(" v0type, v1type, v2type, ...: mpeg2/mpeg4/h263/h264/null\n");
        printf(" a0type: aac/mp3/pcm/ddp(ac3/eac3)/null\n");
        printf(" vo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50\n");

        return 0;
    }
    //Get pes file number
    u32Pesfilenum  = strtol(argv[1],NULL,0);
    if(u32Pesfilenum > __MAX_PES_INPUT_NUM__)
    {
        printf("too much input file number u32Pesfilenum:%d > %d\n", u32Pesfilenum, __MAX_PES_INPUT_NUM__);
        return 0;
    }
    if(argc < (3 + u32Pesfilenum * 2))
    {
        printf("too few input arg for multistream input argc:%d\n", argc);
        return 0;
    }

    for(index = 0; index < u32Pesfilenum; index ++)
    {
        HI_U8 tmpinputindexoffset;
        //Init parameter
        VdecType[index]        = HI_UNF_VCODEC_TYPE_BUTT;
        AdecType[index]        = 0x00;
        g_PEShandle[index]     = 0;
        hAVPlay[index]         = 0;
        hWin[index]            = 0;
        u32PESVideoType[index] = HI_UNF_PES_STREAM_TYPE_VIDEO_UNKNOW;
        u32PES_AudioType[index] = HI_UNF_PES_STREAM_TYPE_AUDIO_UNKNOW;

        if(index == 0)
        {
            tmpinputindexoffset = 2;
        }
        else
        {
            tmpinputindexoffset = 5 + (index - 1) * 2;
        }

        g_pPEsFile[index] = fopen(argv[tmpinputindexoffset], "rb");
        if (!g_pPEsFile[index])
        {
            sample_printf("open file %s error!\n", argv[tmpinputindexoffset]);
            return -1;
        }

        //Get Video Type
        if (!strcasecmp("mpeg2", argv[tmpinputindexoffset + 1]))
        {
            VdecType[index] = HI_UNF_VCODEC_TYPE_MPEG2;
            u32PESVideoType[index] = HI_UNF_PES_STREAM_TYPE_VIDEO_MPEG2;
        }
        else if (!strcasecmp("mpeg4", argv[tmpinputindexoffset + 1]))
        {
            VdecType[index] = HI_UNF_VCODEC_TYPE_MPEG4;
            u32PESVideoType[index] = HI_UNF_PES_STREAM_TYPE_VIDEO_MPEG4;
        }
        else if (!strcasecmp("h264", argv[tmpinputindexoffset + 1]))
        {
            VdecType[index] = HI_UNF_VCODEC_TYPE_H264;
            u32PESVideoType[index] = HI_UNF_PES_STREAM_TYPE_VIDEO_H264;
        }
        else if (!strcasecmp("h263", argv[tmpinputindexoffset + 1]))
        {
            VdecType[index] = HI_UNF_VCODEC_TYPE_H263;
            u32PESVideoType[index] = HI_UNF_PES_STREAM_TYPE_VIDEO_H263;
        }
        else
        {
            VdecType[index] = HI_UNF_VCODEC_TYPE_BUTT;
        }

        if(index == 0)
        {
            //Get Audio type
            if (!strcasecmp("aac", argv[tmpinputindexoffset + 2]))
            {
                AdecType[index] = HA_AUDIO_ID_AAC;
                u32PES_AudioType[index] = HI_UNF_PES_STREAM_TYPE_AUDIO_AAC;
            }
            else if (!strcasecmp("mp3", argv[tmpinputindexoffset + 2]))
            {
                AdecType[index] = HA_AUDIO_ID_MP3;
                u32PES_AudioType[index] = HI_UNF_PES_STREAM_TYPE_AUDIO_MP3;
            }
            else if (!strcasecmp("pcm", argv[tmpinputindexoffset + 2]))
            {
                AdecType[index] = HA_AUDIO_ID_PCM;
                u32PES_AudioType[index] = HI_UNF_PES_STREAM_TYPE_AUDIO_PCM;
            }
#if defined (DOLBYPLUS_HACODEC_SUPPORT)
            else if (!strcasecmp("ddp", argv[tmpinputindexoffset + 2]))
            {
                AdecType[index] = HA_AUDIO_ID_DOLBY_PLUS;
                u32PES_AudioType[index] = HI_UNF_PES_STREAM_TYPE_AUDIO_DDPLUS;
            }
#endif
            else
            {
                AdecType[index] = 0x00;
            }

        }
    }

    enFormat = HIADP_Disp_StrToFmt(argv[(3 + u32Pesfilenum * 2)]);

    HI_SYS_Init();

    HIADP_MCE_Exit();

    Ret = HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto SYS_DEINIT;
    }

    if(VdecType[0] != HI_UNF_VCODEC_TYPE_BUTT)
    {
        Ret = HIADP_Disp_Init(enFormat);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call DispInit failed.\n");
            goto DISP_DEINIT;
        }

        BgColor.u8Red   = 0;
        BgColor.u8Green = 200;
        BgColor.u8Blue  = 200;
        HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY1, &BgColor);

        Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_MOSAIC);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HIADP_VO_Init failed.\n");
            goto DISP_DEINIT;
        }
    }

    if (AdecType[0] != 0x00)
    {
        Ret = HIADP_Snd_Init();
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call SndInit failed.\n");
            goto SND_DEINIT;
        }

        Ret = HIADP_AVPlay_RegADecLib();
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_AVPLAY_RegisterAcodecLib failed.\n");
            goto SND_DEINIT;
        }
    }

    for(index = 0; index < u32Pesfilenum; index ++)
    {
        Pes_Mosaic_Open(index, VdecType[index], AdecType[index], &(hAVPlay[index]), &(hWin[index]), &hTrack);

        /* Open PES handle */
        stOpenParam.hAVPlay           = hAVPlay[index];
        stOpenParam.u32VdecType       = u32PESVideoType[index];
        stOpenParam.u32AudioType      = u32PES_AudioType[index];
        stOpenParam.u32PESBufferSize  = 2 * 1024 * 1024; // Allocate 2MBytes
        stOpenParam.enPESParseType  = HI_UNF_PES_PARSE_TYPE_REGULAR;
        //stOpenParam.enPESParseType  = HI_UNF_PES_PARSE_TYPE_ADJUST;
        stOpenParam.bIsDVD = HI_FALSE;
        Ret = HI_UNF_PES_Open(&stOpenParam, &(g_PEShandle[index]));
        sample_printf("index:%d, PEShandle:0x%x\n", index, g_PEShandle[index]);

        g_StopThread[index] = HI_FALSE;
        pthread_create(&(g_EsThd[index]), HI_NULL, (HI_VOID *)PESTthread, (HI_VOID *)&(g_PEShandle[index]));
    }

    while(1)
    {
        printf("please input the q to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
    }

    for(index = 0; index < u32Pesfilenum; index ++)
    {
        g_StopThread[index] = HI_TRUE;
        pthread_join(g_EsThd[index], HI_NULL);

        sample_printf("come to pes close\n");
        HI_UNF_PES_Close(g_PEShandle[index]);
        Pes_Close(hAVPlay[index], hWin[index], hTrack);

    }

    HI_UNF_AVPLAY_DeInit();

SND_DEINIT:
    HIADP_Snd_DeInit();

DISP_DEINIT:
    HIADP_VO_DeInit();
    HIADP_Disp_DeInit();

SYS_DEINIT:
    HI_SYS_DeInit();
    for(index = 0; index < u32Pesfilenum; index ++)
    {
        fclose(g_pPEsFile[index]);
        g_pPEsFile[index] = HI_NULL;
    }

    return 0;
}

/*------------------------------------END---------------------------------------------*/
