/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sample_pvr_timeshift.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
  History       :
  1.Date        : 2010/01/26
    Author      : q46153
    Modification: Created file

******************************************************************************/
#include <stdlib.h>

#include "hi_adp.h"
#include "hi_adp_audio.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_boardcfg.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"
#include "hi_adp_pvr.h"

#ifndef ANDROID

#define DISPLAY_JPEG
#ifdef DISPLAY_JPEG
#include "hi_go_gdev.h"
#include "hi_go_bliter.h"
#include "hi_go_decoder.h"
#endif
#include "hi_go_comm.h"
#include "hi_go_gdev.h"
#include "hi_go_bliter.h"
#include "hi_go_text.h"

#endif

static pthread_t   g_TimeThread;
HI_U32 g_TunerFreq;
HI_U32 g_TunerSrate;
HI_U32 g_ThirdParam;
static HI_UNF_ENC_FMT_E   g_enDefaultFmt = HI_UNF_ENC_FMT_1080P_60;
PMT_COMPACT_TBL   *g_pProgTbl = HI_NULL;
HI_HANDLE               g_hTsBufForPvrPlayBack;
HI_HANDLE hLayer_pvr = HI_INVALID_HANDLE;
HI_HANDLE hLayerSurface_pvr;
HI_HANDLE hFont_pvr = HI_INVALID_HANDLE;
HI_BOOL g_bIsPlayStop = HI_FALSE;
HI_U32 g_RecChn;
HI_U32 g_PlayChn = 0xffffffff;
int g_thread_run = 1;
extern HI_S32 g_s32SMemFd;



#define MAX_TIMESHIFT_REC_FILE_SIZE       (4000*1024*1024LLU)
#define MODULE_MEM_TEST_INFO  _IOWR(0, 8, int)


HI_S32 DmxInitAndSearch(HI_U32 tunerId)
{
    HI_S32   Ret;

    Ret = HI_UNF_DMX_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_DMX_Init failed.\n");
        return Ret;
    }
    Ret = HIADP_DMX_AttachTSPort(PVR_DMX_ID_LIVE, tunerId);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        HI_UNF_DMX_DeInit();
        return Ret;
    }

    Ret = HIADP_DMX_AttachTSPort(PVR_DMX_ID_REC, tunerId);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_DMX_AttachTSPort for REC failed.\n");
        HI_UNF_DMX_DeInit();
        return Ret;
    }

    HIADP_Search_Init();
    Ret = HIADP_Search_GetAllPmt(0,&g_pProgTbl);
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


HI_S32 SwitchToShiftPlay(const HI_CHAR *pszFileName, HI_U32 *pu32PlayChn,
             HI_HANDLE hAvplay)
{

    PVR_SwitchDmxSource(PVR_DMX_ID_LIVE, PVR_DMX_PORT_ID_PLAYBACK);
    PVR_StartPlayBack(pszFileName, pu32PlayChn, hAvplay);

    return HI_SUCCESS;
}


HI_S32 SwitchToLivePlay(HI_U32 u32PlayChn, HI_HANDLE hAvplay, const PMT_COMPACT_PROG *pProgInfo)
{
    PVR_StopPlayBack(u32PlayChn);


    PVR_SwitchDmxSource(PVR_DMX_ID_LIVE, PVR_DMX_PORT_ID_DVB);
    PVR_StartLivePlay(hAvplay, pProgInfo);
    return HI_SUCCESS;
}

#ifdef DISPLAY_JPEG
static HI_S32 file_dec_doublevo(HI_CHAR *pszFileName, HI_HANDLE *pSurface)
{
    HI_S32 ret;
    HI_HANDLE hDecoder;
    HIGO_DEC_ATTR_S stSrcDesc;

    /** create decode*/
    stSrcDesc.SrcType = HIGO_DEC_SRCTYPE_FILE;
    stSrcDesc.SrcInfo.pFileName = pszFileName;
    ret = HI_GO_CreateDecoder(&stSrcDesc, &hDecoder);
    if (HI_SUCCESS != ret)
    {
        sample_common_printf("HI_GO_CreateDecoder failed!\n");
        return ret;
    }

    /** decode it to Surface */
    ret  = HI_GO_DecImgData(hDecoder, 0, NULL, pSurface);
    ret |= HI_GO_DestroyDecoder(hDecoder);

    return ret;
}

HI_S32 BlitPic(HI_HANDLE* phLayerHD)
{
    HI_S32 s32Ret = 0;

    HI_U32 StartX_HD, StartY_HD;
    HI_HANDLE hDecSurface, hLayer_HD, hLayer_Surface_HD;
    HI_CHAR aszFileName[256] = {0};
    HIGO_LAYER_INFO_S stLayerInfo_HD;
    HIGO_BLTOPT_S stBltOpt   = {0};
    HIGO_LAYER_E eLayerID_HD = HIGO_LAYER_HD_0;
    HI_RECT stRect;

    s32Ret  = HI_GO_Init();
    s32Ret |= HI_GO_GetLayerDefaultParam(eLayerID_HD, &stLayerInfo_HD);
    if (HI_SUCCESS != s32Ret)
    {
        HI_GO_Deinit();

        sample_common_printf("HI_GO_GetLayerDefaultParam failed: line:%d\n", __LINE__);

        return HI_FAILURE;
    }

    //stLayerInfo_HD.ScreenWidth  = 720;
    //stLayerInfo_HD.ScreenHeight = 576;
    stLayerInfo_HD.PixelFormat = HIGO_PF_8888;
    stLayerInfo_HD.LayerFlushType = HIGO_LAYER_FLUSH_NORMAL;

    /**create the graphic layer and get the handler */
    s32Ret = HI_GO_CreateLayer(&stLayerInfo_HD, &hLayer_HD);
    if (HI_SUCCESS != s32Ret)
    {
        HI_GO_Deinit();

        sample_common_printf("HI_GO_CreateLayer failed: line:%d\n", __LINE__);

        return HI_FAILURE;
    }

    *phLayerHD = hLayer_HD;

    StartX_HD = 0;
    StartY_HD = 0;
    HI_GO_SetLayerPos(hLayer_HD, StartX_HD, StartY_HD);
    s32Ret = HI_GO_GetLayerSurface(hLayer_HD, &hLayer_Surface_HD);
    if (HI_SUCCESS != s32Ret)
    {
        HI_GO_DestroyLayer(hLayer_HD);

        HI_GO_Deinit();

        sample_common_printf("HI_GO_GetLayerSurface failed: line:%d\n", __LINE__);

        return HI_FAILURE;
    }
    HI_GO_FillRect(hLayer_Surface_HD, NULL, 0xff000000, 0);
    HI_GO_RefreshLayer(hLayer_HD, NULL);
    HI_GO_SetLayerAlpha(hLayer_HD, 200);

    stBltOpt.EnableScale = HI_TRUE;

    snprintf(aszFileName, sizeof(aszFileName), "%s/%s", "./res/jpg", "1.jpg");

    stRect.x = stRect.y = 0;
    stRect.w = stLayerInfo_HD.DisplayWidth;
    stRect.h = stLayerInfo_HD.DisplayHeight;

    /**decoding*/
    s32Ret = file_dec_doublevo(aszFileName, &hDecSurface);
    if (s32Ret == -1)
    {
        sample_common_printf("file_dec_doublevo failed, again...\n");
        s32Ret = file_dec_doublevo(aszFileName, &hDecSurface);
    }
    if (HI_SUCCESS == s32Ret)
    {
        /** Blit it to graphic layer Surface */
        s32Ret = HI_GO_Blit(hDecSurface, NULL, hLayer_Surface_HD, &stRect, &stBltOpt);
        sample_common_printf("HI_GO_Blit result is %d:(0x%08x)\n",s32Ret,s32Ret);
        HI_GO_RefreshLayer(hLayer_HD, NULL);
        HI_GO_FreeSurface(hDecSurface);
    }

    return HI_SUCCESS;
}
#endif




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
    stLayerInfo.PixelFormat  = HIGO_PF_1555;
    stLayerInfo.ScreenWidth  = 1920;
    stLayerInfo.ScreenHeight = 1080;
    stLayerInfo.CanvasWidth = 1920;
    stLayerInfo.CanvasHeight = 1080;
    stLayerInfo.DisplayWidth  = 1280;
    stLayerInfo.DisplayHeight = 720;

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
    stTextInfo.u32Size = 20;

    s32Ret = HI_GO_CreateTextEx(&stTextInfo,  &hFont_pvr);
    if (HI_SUCCESS != s32Ret)
    {
        sample_common_printf("failed to create the font:./res/DroidSansFallbackLegacy.ttf !\n");
        return HI_FAILURE;
    }
    HI_GO_RefreshLayer(hLayer_pvr, NULL);

#endif

    return HI_SUCCESS;
}


HI_S32 DrawString(HI_U32 u32TimeType, HI_CHAR *szText)
{

#ifndef ANDROID

    HI_S32   s32Ret;
    HI_RECT rc_Str[6] = {{100, 200, 150, 30},
                         {100, 230, 180, 30},
                         {100, 260, 180, 30},
                         {100, 290, 180, 30},
                         {100, 320, 180, 30},
                         {100, 350, 180, 30}};

    if (5 < u32TimeType)
    {
        sample_common_printf("Out of time type!\n");
        return HI_FAILURE;
    }

    HI_GO_FillRect(hLayerSurface_pvr, &rc_Str[u32TimeType], 0x80000000, HIGO_COMPOPT_NONE);
    HI_GO_DrawRect(hLayerSurface_pvr, &rc_Str[u32TimeType], 0xffffffff);

    HI_GO_SetTextColor(hFont_pvr, 0xff00ff00);

    s32Ret = HI_GO_TextOutEx(hFont_pvr, hLayerSurface_pvr, szText, &rc_Str[u32TimeType], HIGO_LAYOUT_RIGHT);
    if (HI_SUCCESS != s32Ret)
    {
        sample_common_printf("failed to text out char!\n");
        return HI_FAILURE;
    }

    HI_GO_RefreshLayer(hLayer_pvr, NULL);

#else
    sample_common_printf("%s\n", szText);
#endif
    return HI_SUCCESS;
}


HI_VOID * StatuThread(HI_VOID *args)
{
    HI_S32 Ret;
    HI_UNF_PVR_REC_ATTR_S stRecAttr;
    HI_UNF_PVR_REC_STATUS_S RecstStatus;
    HI_UNF_PVR_PLAY_STATUS_S PlaystStatus;
    HI_UNF_PVR_FILE_ATTR_S FileStatus;
    HI_CHAR Rectimestr[20];
    HI_CHAR Playtimestr[20];
    HI_CHAR Filetimestr[20];

    while (HI_FALSE == g_bIsPlayStop)
    {
        sleep(1);
        (void)HI_UNF_PVR_RecGetChn(g_RecChn, &stRecAttr);
#ifdef ANDROID
        sample_common_printf("----------------------------------\n");
#endif
        Ret = HI_UNF_PVR_RecGetStatus(g_RecChn, &RecstStatus);
        if (HI_SUCCESS == Ret)
        {
            snprintf(Rectimestr, sizeof(Rectimestr),"Rec time:%ds", RecstStatus.u32CurTimeInMs/1000);
            DrawString(1, Rectimestr);
            snprintf(Rectimestr, sizeof(Rectimestr),"Rec len:%ds", (RecstStatus.u32EndTimeInMs-RecstStatus.u32StartTimeInMs)/1000);
            DrawString(2, Rectimestr);
        }

        Ret = HI_UNF_PVR_GetFileAttrByFileName(stRecAttr.szFileName, &FileStatus);
        if (HI_SUCCESS == Ret)
        {
            snprintf(Rectimestr, sizeof(Rectimestr),"Rec size:%lld.%lldM",
                     (FileStatus.u64ValidSizeInByte)/0x100000,
                     ((FileStatus.u64ValidSizeInByte)%0x100000)/0x400);
            DrawString(3, Rectimestr);
        }

        if (0xffffffff != g_PlayChn)
        {
            if (HI_SUCCESS == Ret)
            {
                snprintf(Filetimestr, sizeof(Filetimestr),"File end time:%ds", FileStatus.u32EndTimeInMs/1000);
                DrawString(4, Filetimestr);
            }

            Ret = HI_UNF_PVR_PlayGetStatus(g_PlayChn, &PlaystStatus);
            if (HI_SUCCESS == Ret)
            {
                snprintf(Playtimestr, sizeof(Playtimestr),"Play time:%ds", PlaystStatus.u32CurPlayTimeInMs/1000);
                DrawString(5, Playtimestr);
            }
        }
#ifdef ANDROID
        sample_common_printf("----------------------------------\n\n");
#endif
    }

    return NULL;
}

HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                  Ret;
    HI_HANDLE               hWin;
    HI_CHAR                 InputCmd[32];
    HI_U32                  u32ProgNum;

    HI_HANDLE               hAvplay;
    HI_HANDLE               hSoundTrack;
    HI_UNF_PVR_REC_ATTR_S       RecAttr;
    PMT_COMPACT_PROG            *pstCurrentProgInfo;
    HI_BOOL                bLive = HI_TRUE;
    HI_BOOL                bPause = HI_FALSE;
#ifdef DISPLAY_JPEG
    HI_HANDLE hLayer_HD;
    HI_U32                u32Jpeg = 0;
#endif
    HI_U32                      Tuner;


    if (8 == argc)
    {
        g_TunerFreq  = strtol(argv[2],NULL,0);
        g_TunerSrate = strtol(argv[3],NULL,0);
        g_ThirdParam = strtol(argv[4],NULL,0);
        g_enDefaultFmt = HIADP_Disp_StrToFmt(argv[5]);
        Tuner = strtol(argv[6],NULL,0);	
#ifdef DISPLAY_JPEG
        u32Jpeg = strtol(argv[7],NULL,0);
#endif
    }
    else if (7 == argc)
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
        printf("Usage: %s file_path freq [srate] [qamtype or polarization] [vo_format] [tuner] [JPEG]\n"
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

    HI_SYS_Init();

    HIADP_MCE_Exit();
    Ret = HIADP_Tuner_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HIADP_Demux_Init failed.\n");
        return Ret;
    }

    sample_common_printf("HIADP_Tuner_Connect, frequency:%d, Symbol:%d, Qam:%d\n", g_TunerFreq,g_TunerSrate,g_ThirdParam);

    Ret = HIADP_Tuner_Connect(Tuner,g_TunerFreq,g_TunerSrate,g_ThirdParam);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HIADP_Tuner_Connect failed. Ret = 0x%x\n", Ret);

        return Ret;
    }

    Ret = DmxInitAndSearch(Tuner);
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

    Ret = PVR_AvplayInit(hWin, &hAvplay, &hSoundTrack);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call VoInit failed.\n");
        return Ret;
    }


#ifdef DISPLAY_JPEG
    if (u32Jpeg)
    {
        BlitPic(&hLayer_HD);
    }
#endif

    printf("================================\n");

    Ret = HI_UNF_PVR_RecInit();
    Ret |= HI_UNF_PVR_PlayInit();
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

    printf("please input the number of program to timeshift:\n");
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

    pstCurrentProgInfo = g_pProgTbl->proginfo
                         + ((u32ProgNum-1)% g_pProgTbl->prog_num);

    PVR_RecStart(argv[1], pstCurrentProgInfo,PVR_DMX_ID_REC, 1,0, MAX_TIMESHIFT_REC_FILE_SIZE, &g_RecChn);


    pthread_create(&g_TimeThread, HI_NULL, StatuThread, HI_NULL);

    //u32ProgNum = u32ProgNum+1;
    //pstCurrentProgInfo = g_pProgTbl->proginfo
     //                    + ((u32ProgNum-1)% g_pProgTbl->prog_num);
    //PVR_RecStart(argv[1], pstCurrentProgInfo,PVR_DMX_ID_REC+1, 1,0, MAX_TIMESHIFT_REC_FILE_SIZE, &RecChn2);

    bLive = HI_TRUE;
    bPause = HI_FALSE;
    Ret = PVR_StartLivePlay(hAvplay, pstCurrentProgInfo);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call SwitchProg failed.\n");
        return Ret;
    }
    OsdInit();
    DrawString(0, "Live");

    while(1)
    {
        static HI_U32 u32RTimes = 0;
        static HI_U32 u32FTimes = 0;
        static HI_U32 u32STimes = 0;

        printf("please input the q to quit!\n");
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
            g_thread_run = 0;
            g_bIsPlayStop = HI_TRUE;
            printf("prepare to exit!\n");
            break;
        }
        else if ('l' == InputCmd[0])
        {
            u32RTimes = 0;
            u32FTimes = 0;
            u32STimes = 0;
            if (!bLive)
            {
                SwitchToLivePlay(g_PlayChn, hAvplay, pstCurrentProgInfo);
                bLive = HI_TRUE;
                g_PlayChn = 0xffffffff;
            }
        }
        else if ('p' == InputCmd[0])
        {
            u32RTimes = 0;
            u32FTimes = 0;
            u32STimes = 0;
            if (bPause)  /* when pause ,to shift play */
            {
                if (bLive)  /*when live, switch to shift play */
                {
                    printf("switch to timeshift...\n");
                    HI_UNF_PVR_RecGetChn(g_RecChn,&RecAttr);
                    SwitchToShiftPlay(RecAttr.szFileName, &g_PlayChn, hAvplay);
                    bLive = HI_FALSE;
                }
                else  /* when shift, just to resume*/
                {
                    printf("PVR resume now.\n");
                    Ret = HI_UNF_PVR_PlayResumeChn(g_PlayChn);
                    if (Ret != HI_SUCCESS)
                    {
                        sample_common_printf("call HI_UNF_PVR_PlayPauseChn failed.\n");
                        return Ret;
                    }
                }
                bPause = HI_FALSE;
            }
            else  /* to pause */
            {
                if (bLive)  /*when live, stop live still last picture */
                {
                    PVR_StopLivePlay(hAvplay);

                    Ret = HI_UNF_PVR_PlayPauseChn(g_RecChn);
                    if (Ret != HI_SUCCESS)
                    {
                        sample_common_printf("call HI_UNF_PVR_PlayPauseChn failed.\n");
                        return Ret;
                    }
                }
                else  /* when shift, just to pause*/
                {
                    printf("PVR pause now.\n");
                    Ret = HI_UNF_PVR_PlayPauseChn(g_PlayChn);
                    if (Ret != HI_SUCCESS)
                    {
                        sample_common_printf("call HI_UNF_PVR_PlayPauseChn failed.\n");
                        return Ret;
                    }
                }
                bPause = HI_TRUE;
            }
        }
        else if ('f' == InputCmd[0])
        {
            u32RTimes = 0;
            u32STimes = 0;
            if (bLive)  /*when live, can not fast forword */
            {
                printf("now live play, not support fast forword\n");

            }
            else
            {
                HI_UNF_PVR_PLAY_MODE_S stTrickMode;
                DrawString(0, "FF>>>");

                u32FTimes = u32FTimes%6;
                stTrickMode.enSpeed = (0x1 << (u32FTimes+1)) * HI_UNF_PVR_PLAY_SPEED_NORMAL;
                printf("trick mod:%d\n", stTrickMode.enSpeed);
                Ret = HI_UNF_PVR_PlayTPlay(g_PlayChn, &stTrickMode);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayTPlay failed.\n");
                    return Ret;
                }
                bPause = HI_FALSE;
                u32FTimes++;
            }
        }
        else if ('r' == InputCmd[0])
        {
            u32FTimes = 0;
            u32STimes = 0;
            DrawString(0, "<<<FB");
            if (bLive)  /*when live, switch to shift and fast reword play */
            {
                HI_UNF_PVR_PLAY_MODE_S stTrickMode;

                /*now, stop live play*/
                PVR_StopLivePlay(hAvplay);
                Ret = HI_UNF_PVR_PlayPauseChn(g_RecChn);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayPauseChn failed.\n");
                    return Ret;
                }

                /*rewind from pause position */
                HI_UNF_PVR_RecGetChn(g_RecChn,&RecAttr);
                SwitchToShiftPlay(RecAttr.szFileName, &g_PlayChn, hAvplay);
                bLive = HI_FALSE;
                u32RTimes = u32RTimes%6;
                stTrickMode.enSpeed = -(0x1 << (u32RTimes+1)) * HI_UNF_PVR_PLAY_SPEED_NORMAL;
                printf("shift play now, trick mod:%d\n", stTrickMode.enSpeed);
                Ret = HI_UNF_PVR_PlayTPlay(g_PlayChn, &stTrickMode);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayTPlay failed.\n");
                    return Ret;
                }
                bPause = HI_FALSE;
            }
            else
            {
                HI_UNF_PVR_PLAY_MODE_S stTrickMode;

                u32RTimes = u32RTimes%6;
                stTrickMode.enSpeed = -(0x1 << (u32RTimes+1)) * HI_UNF_PVR_PLAY_SPEED_NORMAL;
                printf("trick mod:%d\n", stTrickMode.enSpeed);
                Ret = HI_UNF_PVR_PlayTPlay(g_PlayChn, &stTrickMode);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayTPlay failed.\n");
                    return Ret;
                }
                bPause = HI_FALSE;
            }
            u32RTimes++;
        }
        else if ('n' == InputCmd[0])
        {
            u32RTimes = 0;
            u32FTimes = 0;
            u32STimes = 0;
            DrawString(0, "Timeshift");
            printf("PVR normal play now.\n");
            if (g_PlayChn == 0xffffffff)
            {
                HI_UNF_PVR_RecGetChn(g_RecChn,&RecAttr);
                printf("switch to timeshift:%s\n", RecAttr.szFileName);
                SwitchToShiftPlay(RecAttr.szFileName, &g_PlayChn, hAvplay);
                sample_common_printf("PlayChn ============= %d\n", g_PlayChn);
                bLive = HI_FALSE;
            }
            else
            {
                Ret = HI_UNF_PVR_PlayResumeChn(g_PlayChn);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayResumeChn failed.\n");
                    return Ret;
                }
            }
            bPause = HI_FALSE;
        }
        else if ('s' == InputCmd[0])
        {
            u32RTimes = 0;
            u32FTimes = 0;
            if (bLive)  /*when live, can not slow forword */
            {
                printf("now live play, not support fast forword\n");

            }
            else
            {
                HI_UNF_PVR_PLAY_MODE_S stTrickMode;

                DrawString(0, "SF>>>");

                u32STimes = u32STimes%6;
                stTrickMode.enSpeed = HI_UNF_PVR_PLAY_SPEED_NORMAL/(0x1 << (u32STimes+1));
                printf("trick mod:%d\n", stTrickMode.enSpeed);
                Ret = HI_UNF_PVR_PlayTPlay(g_PlayChn, &stTrickMode);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayTPlay failed.\n");
                    return Ret;
                }
                bPause = HI_FALSE;
                u32STimes++;
            }
        }
        else if ('k' == InputCmd[0])
        {
            HI_UNF_PVR_PLAY_POSITION_S stPos;
            HI_UNF_PVR_FILE_ATTR_S stFAttr;
            u32RTimes = 0;
            u32FTimes = 0;
            u32STimes = 0;
            if (!bLive)
            {
                Ret = HI_UNF_PVR_PlayResumeChn(g_PlayChn);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayResumeChn failed.\n");
                    continue;
                }
                DrawString(0, "Play");

                Ret = HI_UNF_PVR_PlayGetFileAttr(g_PlayChn,&stFAttr);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayStep failed.\n");
                }

                stPos.enPositionType = HI_UNF_PVR_PLAY_POS_TYPE_TIME;
                stPos.s64Offset = stFAttr.u32StartTimeInMs;
                stPos.s32Whence = SEEK_SET;
                printf("seek to start\n");

                Ret = HI_UNF_PVR_PlaySeek(g_PlayChn, &stPos);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayStep failed.\n");
                }
            }
            else
            {
                printf("Now in live mode, can't seek to start!\n");
            }
        }
        else if ('e' == InputCmd[0])
        {
            HI_UNF_PVR_PLAY_POSITION_S stPos;
            u32RTimes = 0;
            u32FTimes = 0;
            u32STimes = 0;
            if (!bLive)
            {
                Ret = HI_UNF_PVR_PlayResumeChn(g_PlayChn);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayResumeChn failed.\n");
                    continue;
                }
                DrawString(0, "Play");

                stPos.enPositionType = HI_UNF_PVR_PLAY_POS_TYPE_TIME;
                stPos.s64Offset = 0;
                stPos.s32Whence = SEEK_END;
                printf("seek end\n");

                Ret = HI_UNF_PVR_PlaySeek(g_PlayChn, &stPos);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayStep failed.\n");
                }
            }
            else
            {
                printf("Now in live mode, can't seek to end!\n");
            }
        }
        else if ('a' == InputCmd[0])
        {
            HI_UNF_PVR_PLAY_POSITION_S stPos;
            u32RTimes = 0;
            u32FTimes = 0;
            u32STimes = 0;
            if (!bLive)
            {
                Ret = HI_UNF_PVR_PlayResumeChn(g_PlayChn);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayResumeChn failed.\n");
                    continue;
                }
                DrawString(0, "Play");

                stPos.enPositionType = HI_UNF_PVR_PLAY_POS_TYPE_TIME;
                stPos.s64Offset = -5000;
                stPos.s32Whence = SEEK_CUR;
                printf("seek reward 5 Second\n");

                Ret = HI_UNF_PVR_PlaySeek(g_PlayChn, &stPos);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayStep failed.\n");
                    continue;
                }
            }
            else
            {
                printf("Now in live mode, can't seek backward!\n");
            }
        }
        else if ('d' == InputCmd[0])
        {
            HI_UNF_PVR_PLAY_POSITION_S stPos;
            u32RTimes = 0;
            u32FTimes = 0;
            u32STimes = 0;

            if (!bLive)
            {
                Ret = HI_UNF_PVR_PlayResumeChn(g_PlayChn);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlayResumeChn failed.\n");
                    continue;
                }
                DrawString(0, "Play");

                stPos.enPositionType = HI_UNF_PVR_PLAY_POS_TYPE_TIME;
                stPos.s64Offset = 5000;
                stPos.s32Whence = SEEK_CUR;
                printf("seek forward 5 Second\n");

                Ret = HI_UNF_PVR_PlaySeek(g_PlayChn, &stPos);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call HI_UNF_PVR_PlaySeek failed.\n");
                }
            }
            else
            {
                printf("Now in live mode, can't seek forward!\n");
            }
        }
        else if ('x' == InputCmd[0])
        {
            u32RTimes = 0;
            u32FTimes = 0;
            u32STimes = 0;
            if (!bLive)
            {
                PVR_StopPlayBack(g_PlayChn);

                Ret = PVR_StartPlayBack(RecAttr.szFileName, &g_PlayChn, hAvplay);
                if (Ret != HI_SUCCESS)
                {
                    sample_common_printf("call PVR_StartPlayBack failed.\n");
                }
            }
            else
            {
                printf("Now in live mode, can't recreate play channel!\n");
            }
        }
        else
        {
            printf("commond:\n");
            printf("    l: live play\n");
            printf("    p: pause/play\n");
            printf("    f: fast foreword\n");
            printf("    r: fast reword\n");
            printf("    n: normal play\n");
            printf("    s: slow play\n");
            printf("    k: seek to start\n");
            printf("    e: seek to end\n");
            printf("    a: seek backward 5s\n");
            printf("    d: seek forward 5s\n");
            printf("    x: destroy play channel and create again\n");
            printf("    h: help\n");
            printf("    q: quit\n");
            continue;
        }
    }
#ifdef DISPLAY_JPEG
    if (u32Jpeg)
    {
        HI_GO_DestroyLayer(hLayer_HD);

        HI_GO_Deinit();
    }
#endif

    pthread_join(g_TimeThread, HI_NULL);

    PVR_RecStop(g_RecChn);
    //PVR_RecStop(RecChn2);
    if (0xffffffff != g_PlayChn)
    {
        PVR_StopPlayBack(g_PlayChn);
    }
    PVR_AvplayDeInit(hAvplay, hWin, hSoundTrack);

    HI_UNF_VO_DestroyWindow(hWin);
    HIADP_VO_DeInit();
    HIADP_Disp_DeInit();
    HIADP_Snd_DeInit();
    HI_SYS_DeInit();

    return 0;
}


