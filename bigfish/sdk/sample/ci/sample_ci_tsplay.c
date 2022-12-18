/******************************************************************************

  Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sample_ci_tsplay.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/01/26
  Description   :
  History       :
  1.Date        : 2010/01/26
    Author      : w58735
    Modification: Created file

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#include "hi_unf_common.h"
#include "hi_unf_ecs.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_adp_audio.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_mpi.h"

#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "hi_unf_ci.h"
#include "stack/ci_stack.h"

/*********************TS route typical case*************************************
case 0: local_ts->demux_port_ram->tso0->CAM->tsi0->demux_port_tsi1->demux,  
        parallel, hi3751v100/hi3796cv100
        
case 1: local_ts->usb->cimax->CAM_A->tsi0->demux_port_tsi0->demux
        usb2parallel, hi3716cv200+ciamx
        
case 2: local_ts->usb->cimax->CAM_B->tsi2->demux_port_tsi2->demux
        usb2serial, hi3716cv200+ciamx
        
case 3: local_ts->tso1->CAM_B->tsi2->demux_port_tsi2->demux
        serial, hi3716cv200+ciamx
        
*******************************************************************************/
#define  PLAY_DMX_ID                1

#define  CA_DESCRIPTOR_TAG          0x09
#define  SIZE_ONE_TIME              188 * 50
#define  STREAM_TYPE_13818_VIDEO    0x02
#define  STREAM_TYPE_13818_AUDIO    0x04 
#define  HI_UNF_PORT_INVALID        0xFFFF

typedef enum hiTS_ROUTE_CASE_S
{
    TS_ROUTE_CASE_0,
    TS_ROUTE_CASE_1,
    TS_ROUTE_CASE_2,
    TS_ROUTE_CASE_3,
    TS_ROUTE_CASE_BUTT
}TS_ROUTE_CASE;

typedef struct hiTS_ROUTE_S
{
    HI_UNF_CI_TS_MODE_E enTSMode;
    HI_UNF_DMX_PORT_E enTSIPort;
    HI_UNF_DMX_TSO_PORT_E enTSOPort;
    HI_UNF_CI_PCCD_E enCISlot;
    HI_UNF_CI_TSI_SERIAL_PORT_E enMaxSI;
}TS_ROUTE_S;

static TS_ROUTE_S s_TsRouteConfig[TS_ROUTE_CASE_BUTT] =
{
    /* TS_ROUTE_CASE_0 */
    {
        HI_UNF_CI_TS_PARALLEL, 
        HI_UNF_DMX_PORT_TSI_1, 
        HI_UNF_DMX_PORT_TSO_0, 
        HI_UNF_CI_PCCD_A, 
        HI_UNF_PORT_INVALID
     },
    /* TS_ROUTE_CASE_1 */
    {
        HI_UNF_CI_TS_USB2PARALLEL, 
        HI_UNF_DMX_PORT_TSI_0, 
        HI_UNF_PORT_INVALID,
        HI_UNF_CI_PCCD_A, 
        HI_UNF_CI_TSI_SERIAL1 
    },
    /* TS_ROUTE_CASE_2 */
    {
        HI_UNF_CI_TS_USB2SERIAL, 
        HI_UNF_DMX_PORT_TSI_2, 
        HI_UNF_PORT_INVALID,
        HI_UNF_CI_PCCD_B, 
        HI_UNF_CI_TSI_SERIAL2
    },
    /* TS_ROUTE_CASE_3 */
    {
        HI_UNF_CI_TS_SERIAL, 
        HI_UNF_DMX_PORT_TSI_2, 
        HI_UNF_DMX_PORT_TSO_1, 
        HI_UNF_CI_PCCD_B,
        HI_UNF_CI_TSI_SERIAL2
    }
};

static TS_ROUTE_CASE s_enRouteCase =  TS_ROUTE_CASE_0;

#define  TSMODE     s_TsRouteConfig[s_enRouteCase].enTSMode
#define  TSIPORT    s_TsRouteConfig[s_enRouteCase].enTSIPort
#define  TSOPORT    s_TsRouteConfig[s_enRouteCase].enTSOPort
#define  CISLOT     s_TsRouteConfig[s_enRouteCase].enCISlot
#define  MAXSI      s_TsRouteConfig[s_enRouteCase].enMaxSI

FILE               *g_pTsFile = HI_NULL;
static pthread_t   g_TsThd;
static pthread_mutex_t g_TsMutex;
static HI_BOOL     g_bStopTsThread = HI_FALSE;
static HI_HANDLE   s_hAvplay = HI_NULL;
PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;
HI_HANDLE          g_TsBuf;

static HI_U32 UpdatePMT(HI_U32 ProgNum)
{
    HI_PRINT("Update PMT to CAM\n");
    return HI_CI_UpdatePMT(CISLOT, g_pProgTbl->proginfo[ProgNum].u8PmtData);  
}

static HI_U32 CalculatePercent(HI_U32 u32Elememt, HI_U32 u32Denominator)
{
    HI_U64 u64Percent = 0;
        
    if (u32Denominator > 0)
    {
        u64Percent = u32Elememt * 100 / u32Denominator;
    }
    return (HI_U32)u64Percent;
}

static HI_VOID TsTthread(HI_VOID *args)
{
    HI_U32 Readlen = 0;
    HI_U32 u32SleepTime = 100;
    HI_S32 Ret;
    HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfo;
    HI_UNF_STREAM_BUF_S   StreamBuf;
    HI_UNF_CI_PCCD_TSCTRL_PARAM_U unTSParam;
    HI_U8 au8Buffer[SIZE_ONE_TIME];
    HI_U32 AudBufPercent = 0;
    HI_U32 VidBufPercent = 0;
    HI_U32 BufPercent = 0;

    while (!g_bStopTsThread)
    {  
        if (TSMODE == HI_UNF_CI_TS_PARALLEL || TSMODE == HI_UNF_CI_TS_SERIAL)
        {
            pthread_mutex_lock(&g_TsMutex);
            Ret = HI_UNF_DMX_GetTSBuffer(g_TsBuf, SIZE_ONE_TIME, &StreamBuf, 1000);
            if (Ret != HI_SUCCESS )
            {   
                pthread_mutex_unlock(&g_TsMutex);
                continue;
            }

            Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), SIZE_ONE_TIME, g_pTsFile);
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
        else if (TSMODE == HI_UNF_CI_TS_USB2PARALLEL || TSMODE == HI_UNF_CI_TS_USB2SERIAL)
        {
            if (s_hAvplay != HI_NULL && g_pProgTbl != HI_NULL)
            {
                Ret = HI_UNF_AVPLAY_GetStatusInfo(s_hAvplay, &stStatusInfo);
                if (Ret != HI_SUCCESS)
                {
                    printf("call HI_UNF_AVPLAY_GetStatusInfo failed, ret =0x%x.\n", Ret);
                    continue;
                }
                VidBufPercent=CalculatePercent(stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_VID].u32UsedSize, stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_VID].u32BufSize);
                AudBufPercent=CalculatePercent(stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_AUD].u32UsedSize, stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_AUD].u32BufSize);
                BufPercent=CalculatePercent((stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_VID].u32UsedSize + stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_AUD].u32UsedSize), 
                    (stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_VID].u32BufSize + stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_AUD].u32BufSize));
                if(AudBufPercent > 40 || VidBufPercent > 40 || BufPercent > 40)
                {
               //   printf("Percent: audio(%d), video(%d), all(%d), long sleep.\n", AudBufPercent, VidBufPercent, BufPercent);
                    usleep(u32SleepTime * 10);
                    continue;
                }
                u32SleepTime = 1000;
            }
            Readlen = fread(au8Buffer, sizeof(HI_S8), SIZE_ONE_TIME, g_pTsFile);
            if(Readlen < SIZE_ONE_TIME)
            {
                printf("read ts file end and rewind!\n");
                rewind(g_pTsFile);
                continue;
            }
            unTSParam.stWrite.pu8Data = au8Buffer;
            unTSParam.stWrite.u32Size = Readlen;
            Ret = HI_UNF_CI_PCCD_TSCtrl(HI_UNF_CI_PORT_0, CISLOT, HI_UNF_CI_PCCD_TSCTRL_WRITETS, &unTSParam);
            if (Ret != HI_SUCCESS )
            {
                printf("call HI_UNF_CI_PCCD_TSCtrl failed.\n");
            }
            usleep(u32SleepTime);
        }
    }
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32                      Ret;
    HI_HANDLE                   hWin;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_CHAR                     InputCmd[32];
    HI_UNF_ENC_FMT_E            enFormat = HI_UNF_ENC_FMT_1080i_50;
    HI_U32                      ProgNum;
    HI_HANDLE                   hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S    stTrackAttr;
    HI_UNF_DMX_TSO_PORT_ATTR_S  stTSOAttr;
    HI_UNF_DMX_PORT_ATTR_S      pstAttr;
    HI_UNF_DMX_TSI_ATTACH_TSO_S stTSITSO;
    HI_U32  u32Nb;  
    HI_UNF_CI_TS_MODE_E enTSMode[HI_UNF_CI_PCCD_BUTT] = {HI_UNF_CI_TS_PARALLEL, HI_UNF_CI_TS_SERIAL};
    HI_UNF_CI_TSI_SERIAL_PORT_E enTsiSerialPort[HI_UNF_CI_PCCD_BUTT] = {HI_UNF_CI_TSI_SERIAL1, HI_UNF_CI_TSI_SERIAL1};
    HI_U16 u16CaIds[16];
    HI_U8 u8NumCaIds;
    
    if (4 == argc)
    {
        enFormat = stringToUnfFmt(argv[3]);
        s_enRouteCase = atoi(argv[2]);
    }
    if (3 == argc)
    {
        enFormat = HI_UNF_ENC_FMT_1080i_50;
        s_enRouteCase = atoi(argv[2]);
    }
    else if (2 == argc)
    {
        enFormat = HI_UNF_ENC_FMT_1080i_50;
        s_enRouteCase = TS_ROUTE_CASE_0;
    }
    else
    {
        printf("Usage: sample_tsplay file [ts_route_case][vo_format]\n"
               "       vo_format:1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50\n"
               "       ts_route_case:\n"
               "            0: local_ts->tso0->CAM->tsi0->demux\n"
               "            1: local_ts->usb->cimax->CAM_A->tsi0->->demux\n"    
               "            2: local_ts->usb->cimax->CAM_B->tsi2->demux\n" 
               "            3: local_ts->tso1->CAM_B->tsi2->demux\n");
        printf("Example:./sample_tsplay ./test.ts 0\n");
        printf("Example:./sample_tsplay ./test.ts 3 1080i_50\n");
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

    enTSMode[CISLOT] = TSMODE;
    enTsiSerialPort[CISLOT] = MAXSI;
    Ret = HI_CI_Init(enTSMode, enTsiSerialPort);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_CI_Init failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Snd_Init failed.\n");
        goto CI_DEINIT;
    }

    Ret = HIADP_Disp_Init(enFormat);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Disp_Init failed.\n");
        goto SND_DEINIT;
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
    if (TSMODE == HI_UNF_CI_TS_PARALLEL || TSMODE == HI_UNF_CI_TS_SERIAL)
    {
        Ret = HI_UNF_DMX_AttachTSPort(0,HI_UNF_DMX_PORT_RAM_0);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_DMX_AttachTSPort failed.\n");
            goto DMX_DEINIT;
        }

        Ret = HI_UNF_DMX_GetTSOPortAttr(TSOPORT, &stTSOAttr);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_DMX_GetTSOPortAttr failed.\n");
            goto DMX_DEINIT;
        }
        stTSOAttr.bEnable = HI_TRUE;
        stTSOAttr.enTSSource = HI_UNF_DMX_PORT_RAM_0;
        stTSOAttr.bClkReverse = HI_TRUE;
        stTSOAttr.enClkMode = HI_UNF_DMX_TSO_CLK_MODE_NORMAL;
        stTSOAttr.bBitSync =  HI_FALSE;
        stTSOAttr.bSerial = (TSMODE == HI_UNF_CI_TS_SERIAL);
        stTSOAttr.enBitSelector = HI_UNF_DMX_TSO_SERIAL_BIT_7;
        stTSOAttr.bLSB = HI_FALSE;
        stTSOAttr.enClk = HI_UNF_DMX_TSO_CLK_150M;
        stTSOAttr.u32ClkDiv = (TSMODE == HI_UNF_CI_TS_SERIAL ? 2 : 16);
        Ret = HI_UNF_DMX_SetTSOPortAttr(TSOPORT, &stTSOAttr);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_DMX_SetTSOPortAttr failed.\n");
            goto DMX_DEINIT;
        }  
        stTSITSO.enTSI = TSIPORT;
        stTSITSO.enTSO = TSOPORT;
        Ret = HI_UNF_DMX_Invoke(HI_UNF_DMX_INVOKE_TYPE_TSI_ATTACH_TSO,(HI_VOID*)&stTSITSO);/*TS·´Ñ¹*/
        if (Ret != HI_SUCCESS)
        {
            printf("call HI_UNF_DMX_Invoke failed.\n");
            goto DMX_DEINIT;
        }
        Ret = HI_UNF_DMX_CreateTSBuffer(HI_UNF_DMX_PORT_RAM_0, 0x200000, &g_TsBuf);
        if (Ret != HI_SUCCESS)
        {
            printf("call HI_UNF_DMX_CreateTSBuffer failed.\n");
            goto DMX_DEINIT;
        }
    }
  
    Ret = HI_UNF_DMX_AttachTSPort(PLAY_DMX_ID, TSIPORT);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_AttachTSPort failed.\n");
        goto DMX_DEINIT;
    }
    
    Ret = HI_UNF_DMX_GetTSPortAttr(TSIPORT, &pstAttr);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_GetTSPortAttr failed.\n");
        goto DMX_DEINIT;
    } 
    if (TSMODE == HI_UNF_CI_TS_PARALLEL || TSMODE == HI_UNF_CI_TS_USB2PARALLEL)
    {
        pstAttr.enPortType = HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_188;
        pstAttr.u32SerialBitSelector = 0;
    }
    else
    {
        pstAttr.enPortType = HI_UNF_DMX_PORT_TYPE_SERIAL_NOSYNC;
        pstAttr.u32SerialBitSelector = 0;
    }
    Ret = HI_UNF_DMX_SetTSPortAttr(TSIPORT, &pstAttr);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_SetTSPortAttr failed.\n");
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
    AvplayAttr.stStreamAttr.u32VidBufSize = 3 * 1024 * 1024;/* size*15% < 480*1024 */
    AvplayAttr.stStreamAttr.u32AudBufSize = 256 * 1024;
    Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &s_hAvplay);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(s_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto AVPLAY_DESTROY;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(s_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto VCHN_CLOSE;
    }

    Ret = HI_UNF_VO_AttachWindow(hWin, s_hAvplay);
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

    Ret = HI_UNF_SND_Attach(hTrack, s_hAvplay);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_DESTROY;
    }

    Ret = HI_UNF_AVPLAY_GetAttr(s_hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    Ret |= HI_UNF_AVPLAY_SetAttr(s_hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }
    
    pthread_mutex_init(&g_TsMutex,NULL);
    g_bStopTsThread = HI_FALSE;
    pthread_create(&g_TsThd, HI_NULL, (HI_VOID *)TsTthread, HI_NULL);

    while(HI_CI_GetCaSystemID(CISLOT, u16CaIds, &u8NumCaIds) != HI_SUCCESS)
    {
        sleep(1);
    }
        
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
    if (TSMODE == HI_UNF_CI_TS_PARALLEL || TSMODE == HI_UNF_CI_TS_SERIAL)
    {
        HI_UNF_DMX_ResetTSBuffer(g_TsBuf);
    }
    Ret = HIADP_AVPlay_PlayProg(s_hAvplay, g_pProgTbl, ProgNum, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        printf("call HIADP_AVPlay_PlayProg failed.\n");
        goto AVPLAY_STOP;
    }
    UpdatePMT(ProgNum);

    pthread_mutex_unlock(&g_TsMutex);

    while (1)
    {
        static HI_U32 u32TplaySpeed = 2;
        printf("please input your command:\n");
        printf("t : play forward\n");
        printf("r : resume\n");
        printf("g : show time\n");
        printf("m : enter ca menu\n");
        printf("c : mmi input pin code\n");
        printf("s : mmi input choice\n");        
        printf("x : 1-9 play program\n");
        printf("q : quit\n");
        
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }

        if ('t' == InputCmd[0])
        {
            HI_UNF_AVPLAY_TPLAY_OPT_S stTplayOpt;
            printf("%dx tplay\n",u32TplaySpeed);

            stTplayOpt.enTplayDirect = HI_UNF_AVPLAY_TPLAY_DIRECT_FORWARD;
            stTplayOpt.u32SpeedInteger = u32TplaySpeed;
            stTplayOpt.u32SpeedDecimal = 0;

            HI_UNF_AVPLAY_SetDecodeMode(s_hAvplay, HI_UNF_VCODEC_MODE_I);
            HI_UNF_AVPLAY_Tplay(s_hAvplay,&stTplayOpt);
            u32TplaySpeed = (32 == u32TplaySpeed * 2) ? (2) : (u32TplaySpeed * 2) ;
            continue;
        }

        if ('r' == InputCmd[0])
        {
            printf("resume\n");
            HI_UNF_AVPLAY_SetDecodeMode(s_hAvplay, HI_UNF_VCODEC_MODE_NORMAL);
            HI_UNF_AVPLAY_Resume(s_hAvplay,HI_NULL);
            u32TplaySpeed = 2;
            continue;
        }

        if ('g' == InputCmd[0])
        {
            HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfo;
            HI_UNF_AVPLAY_GetStatusInfo(s_hAvplay,&stStatusInfo);
            printf("localtime %u playtime %u\n",stStatusInfo.stSyncStatus.u32LocalTime,stStatusInfo.stSyncStatus.u32PlayTime);
            continue;
        }
        
        if ('m' == InputCmd[0])
        {
            Ret = HI_CI_MMIEnterMenu(CISLOT);
            if (Ret != HI_SUCCESS)
            {
                printf("call HI_CI_MMIEnterMenu failed.\n");
            }
        }
        
        if ('c' == InputCmd[0])
        {       
            if (strlen(&InputCmd[1]) < 2)
            {
                printf("Please input pin code:\n");
                SAMPLE_GET_INPUTCMD(&InputCmd[1]);
            }
            Ret = HI_CI_MMIAnsw(CISLOT, &InputCmd[1], strlen(&InputCmd[1]) - 1);
            if (Ret != HI_SUCCESS)
            {
                printf("call HI_CI_MMIAnsw failed.\n");
            }
        }
        
        if ('s' == InputCmd[0])
        {      
            if (strlen(&InputCmd[1]) < 2)
            {
                printf("Please choice a item:\n");
                SAMPLE_GET_INPUTCMD(&InputCmd[1]);
            }
            u32Nb = atoi(&InputCmd[1]);
            Ret = HI_CI_MMIMenuAnsw(CISLOT, u32Nb);
            if (Ret != HI_SUCCESS)
            {
                printf("call HI_CI_MMIMenuAnsw failed.\n");
            }
        }
        
        ProgNum = atoi(InputCmd);
        if(ProgNum > 0 && ProgNum<= g_pProgTbl->prog_num)
        {        
            pthread_mutex_lock(&g_TsMutex);
            rewind(g_pTsFile);
            HI_UNF_DMX_ResetTSBuffer(g_TsBuf);

            Ret = HIADP_AVPlay_PlayProg(s_hAvplay, g_pProgTbl, ProgNum - 1, HI_TRUE);
            if (Ret != HI_SUCCESS)
            {
                printf("call HIADP_AVPlay_PlayProg failed!\n");
                break;
            }
        	UpdatePMT(ProgNum-1);        
            pthread_mutex_unlock(&g_TsMutex);
        }
    }
    

AVPLAY_STOP:
    Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    Stop.u32TimeoutMs = 0;
    HI_UNF_AVPLAY_Stop(s_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);

PSISI_FREE:
    HIADP_Search_FreeAllPmt(g_pProgTbl);
    g_pProgTbl = HI_NULL;
    HIADP_Search_DeInit();
    g_bStopTsThread = HI_TRUE;
    usleep(100000);
    pthread_join(g_TsThd, HI_NULL);
    pthread_mutex_destroy(&g_TsMutex);
SND_DETACH:
    HI_UNF_SND_Detach(hTrack, s_hAvplay);

TRACK_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrack);

WIN_DETACH:
    HI_UNF_VO_SetWindowEnable(hWin, HI_FALSE);
    HI_UNF_VO_DetachWindow(hWin, s_hAvplay);

ACHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(s_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

VCHN_CLOSE:
    HI_UNF_AVPLAY_ChnClose(s_hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

AVPLAY_DESTROY:
    HI_UNF_AVPLAY_Destroy(s_hAvplay);

AVPLAY_DEINIT:
    HI_UNF_AVPLAY_DeInit();

    
TSBUF_FREE:
    if (TSMODE == HI_UNF_CI_TS_PARALLEL || TSMODE == HI_UNF_CI_TS_SERIAL)
    {
        HI_UNF_DMX_DestroyTSBuffer(g_TsBuf);
    }

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
    
CI_DEINIT:
    HI_CI_DeInit();
    
SYS_DEINIT:
    HI_SYS_DeInit();

    fclose(g_pTsFile);
    g_pTsFile = HI_NULL;

    return Ret;
}


