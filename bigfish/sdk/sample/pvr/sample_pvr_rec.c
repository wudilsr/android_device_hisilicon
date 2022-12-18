/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : pvr_rec.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
  History       :
  1.Date        : 2010/01/26
    Author      : q46153
    Modification: Created file

******************************************************************************/
#include "hi_adp.h"
#include "hi_adp_audio.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_boardcfg.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"
#include "hi_adp_pvr.h"

/* when recording, playing the live program */
//#define PVR_WITH_LIVE

#ifndef PVR_WITH_LIVE
#define ENABLE_IR_PRG
#else
#undef ENABLE_IR_PRG
#endif

#ifdef ENABLE_IR_PRG
#include "hi_unf_ir.h"
#endif


#define MAX_REC_FILE_SIZE       (10*1024*1024*1024LLU)
//#define MAX_REC_FILE_SIZE       (100*1024*1024LLU)

HI_BOOL bRewind = HI_TRUE;
HI_BOOL bDoCipher = HI_FALSE;

HI_U32 g_TunerFreq;
HI_U32 g_TunerSrate;
HI_U32 g_ThirdParam;
static HI_UNF_ENC_FMT_E   g_enDefaultFmt = HI_UNF_ENC_FMT_1080P_60;

PMT_COMPACT_TBL   *g_pProgTbl = HI_NULL;

extern HI_BOOL g_bIsRecStop;
//static pthread_t   g_CmdThd = 0;
HI_U32 g_uRec2Chn = 0xffffffff;
HI_HANDLE g_hTrack;
HI_U32              g_TunerId = 0;


#ifdef ENABLE_IR_PRG

pthread_t g_IrThread = 0;
HI_BOOL g_IrTaskRunning = HI_FALSE;
HI_HANDLE g_hAvplay = 0;


HI_S32  IRProcess(HI_S32 nProgNum);
HI_S32 StartRecSecondProgram(HI_U32 uPrgNum);
#endif



HI_S32 DMXInitAndSearch(HI_S32 nRecDmxID, HI_S32 sPlayDmxID, HI_U32 tunerId)
{
    HI_S32   Ret;

    Ret = HI_UNF_DMX_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_DMX_Init failed.\n");
        return Ret;
    }

    if(sPlayDmxID != -1)
    {
        Ret = HIADP_DMX_AttachTSPort(PVR_DMX_ID_LIVE, tunerId);
        if (Ret != HI_SUCCESS)
        {
            sample_common_printf("call HIADP_DMX_AttachTSPort failed.\n");
            HI_UNF_DMX_DeInit();
            return Ret;
        }
    }

    Ret = HIADP_DMX_AttachTSPort(nRecDmxID, tunerId);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HIADP_DMX_AttachTSPort for REC failed.\n");
        HI_UNF_DMX_DeInit();
        return Ret;
    }

    HIADP_Search_Init();
    if ( g_pProgTbl != HI_NULL)
    {
        HIADP_Search_FreeAllPmt(g_pProgTbl);
        g_pProgTbl = HI_NULL;
    }
    Ret = HIADP_Search_GetAllPmt(nRecDmxID,&g_pProgTbl);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HIADP_Search_GetAllPmt failed\n");
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 DmxDeInit(HI_VOID)
{
    HI_S32 Ret;

    HIADP_Search_FreeAllPmt(g_pProgTbl);
    g_pProgTbl = HI_NULL;

    Ret = HI_UNF_DMX_DetachTSPort(PVR_DMX_ID_LIVE);
    Ret |= HI_UNF_DMX_DetachTSPort(PVR_DMX_ID_REC);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_DMX_DetachTSPort failed.\n");
        return Ret;
    }

    Ret = HI_UNF_DMX_DeInit();
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_DMX_DeInit failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

HI_S32 AvplayInit(HI_HANDLE hWin, HI_HANDLE *phAvplay)
{
    HI_S32                  Ret;
    HI_HANDLE               hAvplay;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;

    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;

    Ret = HIADP_AVPlay_RegADecLib();
    Ret |= HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_Init failed.\n");
        return Ret;
    }

    Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_GetDefaultConfig failed.\n");
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    AvplayAttr.u32DemuxId = PVR_DMX_ID_LIVE;
    AvplayAttr.stStreamAttr.u32VidBufSize = 0x300000;
    Ret = HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_Create failed.\n");
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        return Ret;
    }

    Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_VO_AttachWindow failed.\n");
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_VO_SetWindowEnable failed.\n");
        HI_UNF_VO_DetachWindow(hWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        return Ret;
    }
    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&g_hTrack);
    if (Ret != HI_SUCCESS)
    {
        HI_UNF_VO_DetachWindow(hWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    Ret = HI_UNF_SND_Attach(g_hTrack, hAvplay);
    if (Ret != HI_SUCCESS)
    {
        HI_UNF_SND_DestroyTrack(g_hTrack);
        sample_common_printf("call HI_SND_Attach failed.\n");
        HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
        HI_UNF_VO_DetachWindow(hWin, hAvplay);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_AVPLAY_Destroy(hAvplay);
        HI_UNF_AVPLAY_DeInit();
        return Ret;
    }

    *phAvplay = hAvplay;
    return HI_SUCCESS;
}

HI_S32 AvplayDeInit(HI_HANDLE hAvplay, HI_HANDLE hWin)
{
    HI_S32                      Ret;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;

    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;

    Ret = HI_UNF_AVPLAY_Stop(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_Stop failed.\n");
    }

    Ret = HI_UNF_SND_Detach(g_hTrack, hAvplay);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_SND_Detach failed.\n");
    }

    HI_UNF_SND_DestroyTrack(g_hTrack);

    Ret = HI_UNF_VO_DetachWindow(hWin, hAvplay);
    {
        sample_common_printf("call HI_UNF_VO_DetachWindow failed.\n");
    }

    Ret = HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_ChnClose failed.\n");
    }

    Ret = HI_UNF_AVPLAY_ChnClose(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_ChnClose failed.\n");
    }

    Ret = HI_UNF_AVPLAY_Destroy(hAvplay);
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_Destroy failed.\n");
    }

    Ret = HI_UNF_AVPLAY_DeInit();
    if (Ret != HI_SUCCESS )
    {
        sample_common_printf("call HI_UNF_AVPLAY_DeInit failed.\n");
    }

    return HI_SUCCESS;
}

HI_VOID * CmdThread(HI_VOID *args)
{
    HI_CHAR                 InputCmd[32];

    while (HI_FALSE == g_bIsRecStop)
    {
        printf("please input the 'q' to quit. \n");

#ifndef ANDROID
        if (!SAMPLE_GET_INPUTCMD(InputCmd))
        {
            sleep(1);
            continue;
        }
#else
        SAMPLE_GET_INPUTCMD(InputCmd);
#endif
        
        if ('q' == InputCmd[0])
        {
            printf("now exit!\n");
            g_bIsRecStop = HI_TRUE;
        }
        else
        {
            sleep(1);
            continue;
        }
    }

    return NULL;
}

#include "hi_go_comm.h"
#include "hi_go_gdev.h"
#include "hi_go_bliter.h"
#include "hi_go_text.h"
HI_HANDLE hLayer_pvr = HI_INVALID_HANDLE;
HI_HANDLE hLayerSurface_pvr;
HI_HANDLE hFont_pvr = HI_INVALID_HANDLE;
HI_RECT rc_Str = {160, 200, 300, 80};
HI_BOOL             g_bIsPlayStop = HI_FALSE;

HI_U32              g_u32RecChn = 0xffffffff;


//static pthread_t   g_TimeThread;


HI_S32 OsdInit(HI_VOID)
{
#ifndef ANDROID
    HI_S32   s32Ret;
    HIGO_LAYER_INFO_S stLayerInfo = {0};
    HIGO_TEXT_INFO_S stTextInfo;

    s32Ret = HI_GO_Init();
    if (HI_SUCCESS != s32Ret)
    {
        sample_common_printf("failed to init higo! ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    HI_GO_GetLayerDefaultParam(HIGO_LAYER_HD_0, &stLayerInfo);

    s32Ret = HI_GO_CreateLayer(&stLayerInfo, &hLayer_pvr);
    if (HI_SUCCESS != s32Ret)
    {
        sample_common_printf("failed to create the layer sd 0, ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    s32Ret =  HI_GO_GetLayerSurface(hLayer_pvr, &hLayerSurface_pvr);
    if  (HI_SUCCESS != s32Ret)
    {
        sample_common_printf("failed to get layer surface! s32Ret = 0x%x \n", s32Ret);
        return HI_FAILURE;
    }

    HI_GO_FillRect(hLayerSurface_pvr, NULL, 0x00000000, HIGO_COMPOPT_NONE);

    stTextInfo.pMbcFontFile = NULL;
    stTextInfo.pSbcFontFile = "./res/DroidSansFallbackLegacy.ttf";
    stTextInfo.u32Size = 40;

    s32Ret = HI_GO_CreateTextEx(&stTextInfo, &hFont_pvr);
    if (HI_SUCCESS != s32Ret)
    {
        sample_common_printf("failed to create the font:./res/DroidSansFallbackLegacy.ttf !\n");
        return HI_FAILURE;
    }
    HI_GO_RefreshLayer(hLayer_pvr, NULL);
#endif
    return HI_SUCCESS;
}

HI_S32 DrawTimeSring(HI_CHAR *szText)
{
#ifndef ANDROID
    HI_S32   s32Ret;

    HI_GO_FillRect(hLayerSurface_pvr, &rc_Str, 0x80000000, HIGO_COMPOPT_NONE);
    HI_GO_DrawRect(hLayerSurface_pvr, &rc_Str, 0xffffffff);

    HI_GO_SetTextColor(hFont_pvr, 0xff00ffff);
    HI_GO_SetTextStyle(hFont_pvr, HIGO_TEXT_STYLE_BOLD);

    s32Ret = HI_GO_TextOutEx(hFont_pvr, hLayerSurface_pvr, szText, &rc_Str, HIGO_LAYOUT_HCENTER);
    if (HI_SUCCESS != s32Ret)
    {
        sample_common_printf("failed to text out char!\n");
        return HI_FAILURE;
    }

    HI_GO_RefreshLayer(hLayer_pvr, NULL);
#else
    sample_common_printf("current time:%s\n", szText);
#endif
    return HI_SUCCESS;
}

HI_VOID ConverTimeString(HI_CHAR* pBuf, HI_U32 u32BufLen, HI_U32 u32TimeInMs)
{
    HI_U32 u32Hour = 0;
    HI_U32 u32Minute = 0;
    HI_U32 u32Second = 0;
    HI_U32 u32MSecond = 0;

    u32Hour = u32TimeInMs/(60*60*1000);

    u32Minute = (u32TimeInMs - u32Hour*60*60*1000)/(60*1000);
    u32Second = (u32TimeInMs - u32Hour*60*60*1000 - u32Minute*60*1000)/1000;

    u32MSecond = (u32TimeInMs - u32Hour*60*60*1000 - u32Minute*60*1000 - u32Second*1000);

    snprintf(pBuf, u32BufLen, "%d:%02d:%02d:%04d", u32Hour, u32Minute, u32Second, u32MSecond);

    return;
}

HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                  Ret;
    HI_HANDLE               hWin;
    HI_CHAR                 InputCmd[32];
    HI_U32                  u32ProgNum;
    HI_U32                  RecChn;
//    HI_U32                  uRec2Chn = 0;
    PMT_COMPACT_PROG        *pstCurrentProgInfo;
    HI_U32 i = 0;
    HI_UNF_PVR_REC_STATUS_S stRecStatus;

    HI_HANDLE               hAvplay;
    HI_U32                  Tuner;

    if (7 == argc)
    {
        g_TunerFreq  = strtol(argv[2],NULL,0);
        g_TunerSrate = strtol(argv[3],NULL,0);
        g_ThirdParam = strtol(argv[4],NULL,0);
        g_enDefaultFmt = HIADP_Disp_StrToFmt(argv[5]);
        Tuner = strtol(argv[6],NULL,0);
    }
    else if (6 == argc)
    {
        g_TunerFreq  = strtol(argv[2],NULL,0);
        g_TunerSrate = strtol(argv[3],NULL,0);
        g_ThirdParam = strtol(argv[4],NULL,0);
        g_enDefaultFmt = HIADP_Disp_StrToFmt(argv[5]);
        Tuner = 0;
    }
    else if (5 == argc)
    {
        g_TunerFreq  = strtol(argv[2],NULL,0);
        g_TunerSrate = strtol(argv[3],NULL,0);
        g_ThirdParam = strtol(argv[4],NULL,0);
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
        Tuner = 0;
    }
    else if(4 == argc)
    {
        g_TunerFreq  = strtol(argv[2],NULL,0);
        g_TunerSrate = strtol(argv[3],NULL,0);
        g_ThirdParam = (g_TunerFreq>1000) ? 0 : 64;
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
        Tuner = 0;
    }
    else if(3 == argc)
    {
        g_TunerFreq  = strtol(argv[2],NULL,0);
        g_TunerSrate = (g_TunerFreq>1000) ? 27500 : 6875;
        g_ThirdParam = (g_TunerFreq>1000) ? 0 : 64;
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
        Tuner = 0;        
    }
    else
    {
        printf("Usage: %s file_path freq [srate] [qamtype or polarization] [vo_format] [Tuner]\n"
                "       qamtype or polarization: \n"
                "           For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64] \n"
                "           For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0] \n"
                "       vo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50\n"
                "       Tuner: value can be 0, 1, 2, 3\n",
                argv[0]);

        printf("Example: %s ./ 618 6875 64 1080i_50 0 0\n", argv[0]);
        printf("  Board HI3796CDMO1B support 3 tuners: \n");
        printf("    Satellite : %s ./ 3840 27500 0 1080i_50 0 0\n", argv[0]);
        printf("    Cable     : %s ./ 618 6875 64 1080i_50 1 0\n", argv[0]);
        printf("    Terestrial: %s ./ 474 8000 64 1080i_50 2 0\n", argv[0]);
        return HI_FAILURE;
    }

    g_TunerId = Tuner;
    HI_SYS_Init();

    HIADP_MCE_Exit();
    //HI_SYS_PreAV(NULL);
    Ret = HIADP_Tuner_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HIADP_Demux_Init failed.\n");
        return Ret;
    }

    Ret = HIADP_Tuner_Connect(Tuner,g_TunerFreq,g_TunerSrate,g_ThirdParam);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HIADP_Tuner_Connect failed.\n");
        return Ret;
    }

    Ret = DMXInitAndSearch(PVR_DMX_ID_REC, PVR_DMX_ID_LIVE, Tuner);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call VoInit failed.\n");
        return Ret;
    }

    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HIADP_Snd_Init failed.\n");
        return Ret;
    }

    Ret = HIADP_Disp_Init(g_enDefaultFmt);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HIADP_Disp_DeInit failed.\n");
        return Ret;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    Ret |= HIADP_VO_CreatWin(HI_NULL,&hWin);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HIADP_VO_Init failed.\n");
        HIADP_VO_DeInit();
        return Ret;
    }

    Ret = AvplayInit(hWin, &hAvplay);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call VoInit failed.\n");
        return Ret;
    }

    HI_UNF_PVR_PlayInit();

#ifdef ENABLE_IR_PRG
    g_hAvplay = hAvplay;
#endif

    //OsdInit();

    Ret = HI_UNF_PVR_RecInit();
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_PVR_RecInit failed.\n");
        return Ret;
    }

    Ret = PVR_RegisterCallBacks();
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call PVR_RegisterCallBacks failed.\n");
        return Ret;
    }

    printf("\nPlease input the number of program to record:: ");

    u32ProgNum = 0;
    while (0 == u32ProgNum)
    {
#ifndef ANDROID
        if (!SAMPLE_GET_INPUTCMD(InputCmd))
        {
            sleep(1);
            continue;
        }
#else
        SAMPLE_GET_INPUTCMD(InputCmd);
#endif
        if ('q' == InputCmd[0])
        {
            return 0;
        }

        u32ProgNum = atoi(InputCmd);
    }

    if (u32ProgNum == 0)
    {
        u32ProgNum = 1;
    }

    printf(" To record program %d.\n", u32ProgNum);

    pstCurrentProgInfo = g_pProgTbl->proginfo + ((u32ProgNum-1) % g_pProgTbl->prog_num);
    PVR_RecStart(argv[1], pstCurrentProgInfo, 1, bRewind, HI_FALSE, MAX_REC_FILE_SIZE, &RecChn);

#ifdef ENABLE_IR_PRG

    u32ProgNum += 1;
    u32ProgNum %= g_pProgTbl->prog_num;

    u32ProgNum |= (RecChn<<16);

    IRProcess(u32ProgNum);

    u32ProgNum -= 1;
#endif

#if 0
    u32ProgNum+=1;

    //DMXInitAndSearch(HI_UNF_DMX_ID_2_REC, -1);
    pstCurrentProgInfo = g_pProgTblRec2->proginfo + ((u32ProgNum-1) % g_pProgTblRec2->prog_num);
    PVR_RecStart(argv[1], pstCurrentProgInfo,HI_UNF_DMX_ID_2_REC, bRewind, HI_TRUE, MAX_REC_FILE_SIZE, &g_uRec2Chn);
#endif

#ifdef PVR_WITH_LIVE
    Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,u32ProgNum-1,HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call SwitchProgfailed!\n");
        return 0;
    }
#endif

   // pthread_create(&g_CmdThd, HI_NULL, CmdThread, HI_NULL);

    while (HI_FALSE == g_bIsRecStop)
    {
        usleep(10000);

        //if (0 == i%5)
        {
            Ret = HI_UNF_PVR_RecGetStatus(RecChn, &stRecStatus);
            if (Ret != HI_SUCCESS)
            {
                sample_common_printf("call HI_UNF_PVR_RecGetStatus failed.\n");
                continue;
            }

            //ConverTimeString(timestr, sizeof(timestr), stRecStatus.u32CurTimeInMs);
            //DrawTimeSring(timestr);

            //printf("== record status: \n");
            if (stRecStatus.u64CurWritePos < 1024*1024)
            {
               // sample_common_printf("      size:%lld K\n", stRecStatus.u64CurWritePos/1024);
            }
            else
            {
                //sample_common_printf("      size:%lld M\n", stRecStatus.u64CurWritePos/1024/1024);
            }
           // sample_common_printf("      time:from %d to %d, length:%d s\n", stRecStatus.u32StartTimeInMs/1000, stRecStatus.u32EndTimeInMs/1000, stRecStatus.u32CurTimeInMs/1000);
           // sample_common_printf("      record buff:%d/%d \n", stRecStatus.stRecBufStatus.u32UsedSize, stRecStatus.stRecBufStatus.u32BufSize);
        }
        i++;
    }

    //pthread_join(g_CmdThd, HI_NULL);

    PVR_RecStop(RecChn);

#ifdef ENABLE_IR_PRG
    if(g_uRec2Chn != 0xffffffff)
    {
        PVR_RecStop(g_uRec2Chn);
    }

    g_IrTaskRunning = HI_FALSE;

    pthread_join(g_IrThread, HI_NULL);

    HI_UNF_IR_DeInit();
#endif

    HI_UNF_PVR_RecDeInit();

//#ifdef PVR_WITH_LIVE
    HI_UNF_PVR_PlayDeInit();
    AvplayDeInit(hAvplay, hWin);
//#endif

    Ret = DmxDeInit();
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call DmxDeInit failed.\n");
        return Ret;
    }

    HI_UNF_VO_DestroyWindow(hWin);
    HIADP_VO_DeInit();
    HIADP_Disp_DeInit();
    HIADP_Snd_DeInit();
    HI_SYS_DeInit();

    return 0;
}


#ifdef ENABLE_IR_PRG
HI_S32 StartRecSecondProgram(HI_U32 uPrgNum)
{
    HI_S32              nRet = 0;
    PMT_COMPACT_PROG    *pstCurrentProgInfo = NULL;

    printf(" To record program %d.\n", uPrgNum);

    nRet = DMXInitAndSearch(2, -1, g_TunerId);
    if (nRet != HI_SUCCESS)
    {
        sample_common_printf("call VoInit failed.\n");
        return nRet;
    }

    pstCurrentProgInfo = g_pProgTbl->proginfo + ((uPrgNum-1) % g_pProgTbl->prog_num);
    PVR_RecStart("./", pstCurrentProgInfo, 2, bRewind, HI_FALSE, MAX_REC_FILE_SIZE, &g_uRec2Chn);

    return 0;
}

const HI_CHAR IR_Stuts_Str[3][10] =
{
    "DOWN",
    "HOLD",
    "UP",
};
typedef enum tagKEY{
    KEY_FF = 0x29d6ff00,
    KEY_RW = 0x25daff00,
    KEY_STOP = 0x2fd0ff00,
    KEY_PLAY = 0x3cc3ff00,
    KEY_F1 = 0x7b84ff00,
    KEY_F2 = 0x8689ff00,
    KEY_F3 = 0x26d9ff00,
    KEY_F4 = 0x6996ff00,
    KEY_SEEK = 0x7d82ff00
}KEY_PAD;
void * IR_ReceiveTask(void *args)
{
    HI_S32 Ret = 0;
    HI_U64 u64KeyId = 0;
    HI_UNF_KEY_STATUS_E PressStatus = HI_UNF_KEY_STATUS_DOWN;
    HI_UNF_IR_PROTOCOL_E Protocol = HI_UNF_IR_NEC;
    HI_S32 nProgNum = (HI_S32)args&0xffff;
    HI_U32 nRecChn = ((HI_S32)args>>16)&0xffff;
    HI_U32 PlayChn = 0;

    HI_U32 uRate = 0;
    HI_U32 uPauseFlag = 0xffffffff;
    HI_U32 uSeekFlag = 0xffffffff;

    printf("current playing program is %d\n", nProgNum);


    while (g_IrTaskRunning)
    {
        /*get ir press codevalue & press status*/
        Ret = HI_UNF_IR_GetValue(&PressStatus, &u64KeyId, 200);
        if (HI_SUCCESS == Ret)
        {
            Ret = HI_UNF_IR_GetProtocol(&Protocol);
            if (PressStatus == 0)
            {
                switch(u64KeyId)
                {
                    case KEY_PLAY:
                    {
                        uRate = 0;

                        if(uPauseFlag == 0xffffffff)
                        {
                            printf("PVR pause now.\n");
                            Ret = HI_UNF_PVR_PlayPauseChn(PlayChn);
                            if (Ret != HI_SUCCESS)
                            {
                                sample_common_printf("call HI_UNF_PVR_PlayPauseChn failed.\n");
                            }
                            uPauseFlag = 0;
                        }
                        else
                        {
                            printf("PVR resume now.\n");
                            Ret = HI_UNF_PVR_PlayResumeChn(PlayChn);
                            if (Ret != HI_SUCCESS)
                            {
                                sample_common_printf("call HI_UNF_PVR_PlayResumeChn failed.\n");
                            }

                            uPauseFlag = 0xffffffff;
                        }
                    }
                    break;
                    case KEY_FF:
                    case KEY_RW:
                    {
                        HI_UNF_PVR_PLAY_MODE_S stTrickMode;

                        uRate = uRate%5;
                        stTrickMode.enSpeed = (0x1 << (uRate+1)) * HI_UNF_PVR_PLAY_SPEED_NORMAL;

                        if(u64KeyId == KEY_RW)
                        {
                            stTrickMode.enSpeed *= -1;
                        }

                        printf("trick mod:%d\n", stTrickMode.enSpeed);
                        Ret = HI_UNF_PVR_PlayTPlay(PlayChn, &stTrickMode);
                        if (Ret != HI_SUCCESS)
                        {
                            sample_common_printf("call HI_UNF_PVR_PlayTPlay failed.\n");
                        }

                        uRate++;
                        uPauseFlag = 0;
                    }
                    break;
                    case KEY_STOP:
                        printf("====To stop player channel is %d\n", PlayChn);
                        PVR_StopPlayBack(PlayChn);
                        uPauseFlag = 0;
                    break;
                    case KEY_F1:
                    case KEY_F2:
                    case KEY_F3:
                    case KEY_F4:
                    {
                        HI_UNF_PVR_REC_ATTR_S stRecAttr;

                        uPauseFlag = 0xffffffff;

                        if(PlayChn != 0xffffffff)
                        {
                            PVR_StopPlayBack(PlayChn);
                        }

                        HI_UNF_PVR_RecGetChn(nRecChn,&stRecAttr);
                        PVR_StartPlayBack(stRecAttr.szFileName, &PlayChn, g_hAvplay);
                        printf("====Created Player channel is %d\n", PlayChn);
                    }
                    break;
                    case KEY_SEEK:
                    {
                        HI_UNF_PVR_PLAY_POSITION_S stPos;
                        uRate = 0;

                        uPauseFlag = 0xffffffff;

                        stPos.enPositionType = HI_UNF_PVR_PLAY_POS_TYPE_TIME;
                        stPos.s64Offset = 0;
                        if(uSeekFlag == 0xffffffff)
                        {
                            stPos.s32Whence = SEEK_SET;
                            uSeekFlag = 0;
                            printf("\033[5;31mseek to start\n\033[0m");
                        }
                        else
                        {
                            printf("\033[5;31mseek to end\n\033[0m");
                            stPos.s32Whence = SEEK_END;
                            uSeekFlag = 0xffffffff;
                        }

                        Ret = HI_UNF_PVR_PlaySeek(PlayChn, &stPos);
                        if (Ret != HI_SUCCESS)
                        {
                            sample_common_printf("call HI_UNF_PVR_PlayStep failed.\n");
                        }
                    }
                    break;
                    default:
                        printf(" IR   KeyId : 0x%llx   PressStatus :%d[%s]\n", u64KeyId, PressStatus, IR_Stuts_Str[PressStatus]);
                    break;
                }
            }
        }
        usleep(10*1000);
    }
    return 0;
}

HI_S32  IRProcess(HI_S32 nProgNum)
{
    HI_S32 Ret;

    /*open ir device*/
    Ret = HI_UNF_IR_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
        return Ret;
    }

    Ret = HI_UNF_IR_EnableKeyUp(HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
        HI_UNF_IR_DeInit();
        return Ret;
    }

    Ret = HI_UNF_IR_SetRepKeyTimeoutAttr(108);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
        HI_UNF_IR_DeInit();
        return Ret;
    }

    Ret = HI_UNF_IR_EnableRepKey(HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
        HI_UNF_IR_DeInit();
        return Ret;
    }

    Ret = HI_UNF_IR_Enable(HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
        HI_UNF_IR_DeInit();
        return Ret;
    }

    g_IrTaskRunning = HI_TRUE;

    /*create a thread for ir receive*/
    Ret = pthread_create(&g_IrThread, NULL, IR_ReceiveTask, (void*)nProgNum);
    if (0 != Ret)
    {
        sample_common_printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
        perror("pthread_create");
    }

    return HI_SUCCESS;
}
#endif

