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
#include <stdlib.h>

#include "hi_adp.h"
#include "hi_adp_audio.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_boardcfg.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"
#include "hi_adp_pvr.h"

#include "hi_go_comm.h"
#include "hi_go_gdev.h"
#include "hi_go_bliter.h"
#include "hi_go_text.h"

static pthread_t   g_StatusThread;
static HI_CHAR *g_pMultiAddr;
static HI_U16   g_UdpPort;
static HI_UNF_ENC_FMT_E   g_enDefaultFmt = HI_UNF_ENC_FMT_1080P_60;
PMT_COMPACT_TBL   *g_pProgTbl = HI_NULL;
HI_HANDLE hLayer_pvr = HI_INVALID_HANDLE;
HI_HANDLE hLayerSurface_pvr;
HI_HANDLE hFont_pvr = HI_INVALID_HANDLE;
HI_BOOL g_bIsPlayStop = HI_FALSE;
HI_U32 g_RecChn;
HI_U32 g_PlayChn = 0xffffffff;
static HI_BOOL     g_StopSocketThread = HI_FALSE;
static HI_HANDLE   g_hIpTsBuf;
static pthread_t   g_SocketThd;



#define MAX_TIMESHIFT_REC_FILE_SIZE       (4000*1024*1024LLU)
#define MODULE_MEM_TEST_INFO  _IOWR(0, 8, int)


static HI_VOID SocketThread(HI_VOID *args)
{
    HI_S32              SocketFd;
    struct sockaddr_in  ServerAddr;
    in_addr_t           IpAddr;
    struct ip_mreq      Mreq;
    HI_U32              AddrLen;

    HI_UNF_STREAM_BUF_S     StreamBuf;
    HI_U32              ReadLen;
    HI_U32              GetBufCount=0;
    HI_U32              ReceiveCount=0;
    HI_S32              Ret;

    SocketFd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if (SocketFd < 0)
    {
        sample_common_printf("create socket error [%d].\n", errno);
        return;
    }

    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    ServerAddr.sin_port = htons(g_UdpPort);

    if (bind(SocketFd,(struct sockaddr *)(&ServerAddr),sizeof(struct sockaddr_in)) < 0)
    {
        sample_common_printf("socket bind error [%d].\n", errno);
        close(SocketFd);
        return;
    }

    IpAddr = inet_addr(g_pMultiAddr);
    if (IpAddr)
    {
        Mreq.imr_multiaddr.s_addr = IpAddr;
        Mreq.imr_interface.s_addr = htonl(INADDR_ANY);
        if (setsockopt(SocketFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &Mreq, sizeof(struct ip_mreq)))
        {
            sample_common_printf("Socket setsockopt ADD_MEMBERSHIP error [%d].\n", errno);
            close(SocketFd);
            return;
        }
    }

    AddrLen = sizeof(ServerAddr);

    while (!g_StopSocketThread)
    {
        Ret = HI_UNF_DMX_GetTSBuffer(g_hIpTsBuf, 188*50, &StreamBuf, 0);
        if (Ret != HI_SUCCESS)
        {
            GetBufCount++;
            if(GetBufCount >= 10)
            {
                sample_common_printf("########## TS come too fast! #########, Ret=%d\n", Ret);
                GetBufCount=0;
            }

            usleep(10000) ;
            continue;
        }
        GetBufCount=0;

        ReadLen = recvfrom(SocketFd, StreamBuf.pu8Data, StreamBuf.u32Size, 0,
                           (struct sockaddr *)&ServerAddr, &AddrLen);
        if (ReadLen <= 0)
        {
            ReceiveCount++;
            if (ReceiveCount >= 50)
            {
                sample_common_printf("########## TS come too slow or net error! #########\n");
                ReceiveCount = 0;
            }
        }
        else
        {
            ReceiveCount = 0;
            Ret = HI_UNF_DMX_PutTSBuffer(g_hIpTsBuf, ReadLen);
            if (Ret != HI_SUCCESS )
            {
                sample_common_printf("call HI_UNF_DMX_PutTSBuffer failed.\n");
            }
        }
    }

    close(SocketFd);
    return;
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


    PVR_SwitchDmxSource(PVR_DMX_ID_LIVE, HI_UNF_DMX_PORT_RAM_0);
    PVR_StartLivePlay(hAvplay, pProgInfo);
    return HI_SUCCESS;
}

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
        sample_common_printf("failed to create the font:./res/DroidSansFallbackLegacy.ttf!\n");
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
    HI_RECT rc_Str[4] = {{100, 200, 150, 30},
                         {100, 230, 180, 30},
                         {100, 260, 180, 30},
                         {100, 290, 180, 30}};

    if (3 < u32TimeType)
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
    HI_UNF_PVR_REC_STATUS_S RecstStatus;
    HI_UNF_PVR_PLAY_STATUS_S PlaystStatus;
    HI_UNF_PVR_FILE_ATTR_S PlayFileStatus;
    HI_CHAR Rectimestr[20];
    HI_CHAR Playtimestr[20];
    HI_CHAR Filetimestr[20];

    while (HI_FALSE == g_bIsPlayStop)
    {
        sleep(1);
#ifdef ANDROID
        printf("----------------------------------\n");
#endif
        Ret = HI_UNF_PVR_RecGetStatus(g_RecChn, &RecstStatus);
        if (HI_SUCCESS == Ret)
        {
            snprintf(Rectimestr, sizeof(Rectimestr),"Rec time:%d", RecstStatus.u32CurTimeInMs/1000);
            DrawString(1, Rectimestr);
        }

        if (0xffffffff != g_PlayChn)
        {
            Ret = HI_UNF_PVR_PlayGetFileAttr(g_PlayChn, &PlayFileStatus);
            if (HI_SUCCESS == Ret)
            {
                snprintf(Filetimestr, sizeof(Filetimestr),"File end time:%d", PlayFileStatus.u32EndTimeInMs/1000);
                DrawString(2, Filetimestr);
            }

            Ret = HI_UNF_PVR_PlayGetStatus(g_PlayChn, &PlaystStatus);
            if (HI_SUCCESS == Ret)
            {
                snprintf(Playtimestr, sizeof(Playtimestr),"Play time:%d", PlaystStatus.u32CurPlayTimeInMs/1000);
                DrawString(3, Playtimestr);
            }
        }
#ifdef ANDROID
        printf("----------------------------------\n\n");
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
    HI_UNF_PVR_REC_ATTR_S   RecAttr;
    PMT_COMPACT_PROG        *pstCurrentProgInfo;
    HI_BOOL                 bLive = HI_TRUE;
    HI_BOOL                 bPause = HI_FALSE;

    HI_ERR_PRINT(HI_ID_PVR, "%s... enter and argc is %d\n", __func__, argc);

    if(5 == argc)
    {
        g_pMultiAddr  = argv[2];
        g_UdpPort = strtol(argv[3],NULL,0);
        g_enDefaultFmt = HIADP_Disp_StrToFmt(argv[4]);
    }
    else if(4 == argc)
    {
        g_pMultiAddr  = argv[2];
        g_UdpPort = strtol(argv[3],NULL,0);
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
    }
    else
    {
        printf("Usage: %s file_path multiaddr portnum [vo_format]\n"
                "       multicast address: \n"
                "           UDP port \n"
                "       vo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50\n", argv[0]);
        return HI_FAILURE;
    }

    HI_SYS_Init();

    HIADP_MCE_Exit();

    Ret = HI_UNF_DMX_Init();
    Ret |= HI_UNF_DMX_AttachTSPort(PVR_DMX_ID_LIVE,PVR_DMX_PORT_ID_IP);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call VoInit failed.\n");
        return HI_FAILURE;
    }

    Ret = HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_RAM_0, 0x200000, &g_hIpTsBuf);
    if (Ret != HI_SUCCESS)
    {
        sample_common_printf("call HI_UNF_DMX_CreateTSBuffer failed.\n");
        return HI_FAILURE;
    }

    Ret = HI_UNF_DMX_AttachTSPort(PVR_DMX_ID_REC, PVR_DMX_PORT_ID_IP);

    g_StopSocketThread = HI_FALSE;
    pthread_create(&g_SocketThd, HI_NULL, (HI_VOID *)SocketThread, HI_NULL);

    HIADP_Search_Init();
    Ret = HIADP_Search_GetAllPmt(PVR_DMX_ID_LIVE,&g_pProgTbl);
    if (HI_SUCCESS != Ret)
    {
        sample_common_printf("call HIADP_Search_GetAllPmt failed\n");
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
        //printf("get:%s\n", InputCmd);
        u32ProgNum = atoi(InputCmd);
    }

    pstCurrentProgInfo = g_pProgTbl->proginfo
                         + ((u32ProgNum-1)% g_pProgTbl->prog_num);

    PVR_RecStart(argv[1], pstCurrentProgInfo,PVR_DMX_ID_REC, 1,0, MAX_TIMESHIFT_REC_FILE_SIZE, &g_RecChn);

    pthread_create(&g_StatusThread, HI_NULL, StatuThread, HI_NULL);

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

        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            g_bIsPlayStop = HI_TRUE;
            g_StopSocketThread = HI_TRUE;
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
                printf("PlayChn ============= %d\n", g_PlayChn);
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

    pthread_join(g_SocketThd, HI_NULL);
    pthread_join(g_StatusThread, HI_NULL);

    PVR_RecStop(g_RecChn);

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


