/******************************************************************************

  Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : sample_ci_dvbplay_.c
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
#include "hi_unf_hdmi.h"
#include "hi_unf_frontend.h"
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
#include "hi_unf_ci.h"
#include "stack/ci_stack.h"

/*********************TS route typical case*************************************
case 0: tuner->demod->tso0->CAM->tsi0->demux_port_tsi1->demux,  
        parallel, internal demod, hi3751v100/hi3796cv100
        
case 1: tuner->demod->cimax->CAM_A->tsi0->demux_port_tsi0->demux
        parallel, external demod, hi3716cv200+ciamx
        
case 2: tuner->demod->cimax->CAM_B->tsi2->demux_port_tsi2->demux
        serial, external demod, hi3716cv200+ciamx
        
case 3: tuner->demod->tsi1->tso1->CAM_B->tsi2->demux_port_tsi2->demux
        serial, external demod, hi3716cv200+ciamx
        
*******************************************************************************/
#define HI_ERR_CI(fmt...) \
    HI_ERR_PRINT(HI_ID_CI, fmt)

#define HI_INFO_CI(fmt...) \
    HI_INFO_PRINT(HI_ID_CI, fmt)
    
#define HI_MALLOC_CI(size)  HI_MEM_Malloc(HI_ID_CI, size)
#define HI_FREE_CI(pAddr)   HI_MEM_Free(HI_ID_CI, pAddr)

#define CA_DESCRIPTOR_TAG           0x09
#define HI_UNF_PORT_INVALID         0xFFFF

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
    HI_UNF_DMX_PORT_E enDvbPort;
    HI_U32 u32Tuner;
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
        HI_DEMUX_PORT,
        0,
        HI_UNF_DMX_PORT_TSO_0, 
        HI_UNF_CI_PCCD_A, 
        HI_UNF_PORT_INVALID
     },
    /* TS_ROUTE_CASE_1 */
    {
        HI_UNF_CI_TS_PARALLEL, 
        HI_UNF_DMX_PORT_TSI_0,
        HI_DEMUX_PORT,   
        0,
        HI_UNF_PORT_INVALID,  
        HI_UNF_CI_PCCD_A, 
        HI_UNF_PORT_INVALID   
    },
    /* TS_ROUTE_CASE_2 */
    {
        HI_UNF_CI_TS_SERIAL, 
        HI_UNF_DMX_PORT_TSI_2, 
        HI_DEMUX1_PORT,   
        1,
        HI_UNF_PORT_INVALID,  
        HI_UNF_CI_PCCD_B, 
        HI_UNF_CI_TSI_SERIAL2
    },
    /* TS_ROUTE_CASE_3 */
    {
        HI_UNF_CI_TS_SERIAL, 
        HI_UNF_DMX_PORT_TSI_2, 
        HI_UNF_DMX_PORT_TSI_1,   
        1,  
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
#define  DVBPORT    s_TsRouteConfig[s_enRouteCase].enDvbPort
#define  TUNER		s_TsRouteConfig[s_enRouteCase].u32Tuner

HI_U32 g_TunerFreq;
HI_U32 g_TunerSrate;
HI_U32 g_ThirdParam;
static HI_UNF_ENC_FMT_E   g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;

PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;

static HI_U32 UpdatePMT(HI_U32 ProgNum)
{
    HI_PRINT("Update PMT to CAM\n");
    return HI_CI_UpdatePMT(CISLOT, g_pProgTbl->proginfo[ProgNum].u8PmtData);  
}
    
HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                  Ret;
    HI_HANDLE               hWin;

    HI_HANDLE               hAvplay;
    HI_UNF_AVPLAY_ATTR_S        AvplayAttr;
    HI_UNF_SYNC_ATTR_S          SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S    Stop;
    HI_CHAR                 InputCmd[32];
    HI_U32                  ProgNum;
    
    HI_HANDLE hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;
    HI_UNF_DMX_TSO_PORT_ATTR_S stTSOAttr;
    HI_UNF_DMX_PORT_ATTR_S      pstAttr;
    HI_U32  u32Nb;
    HI_UNF_CI_TS_MODE_E enTSMode[HI_UNF_CI_PCCD_BUTT] = {HI_UNF_CI_TS_PARALLEL, HI_UNF_CI_TS_SERIAL};
    HI_UNF_CI_TSI_SERIAL_PORT_E enTsiSerialPort[HI_UNF_CI_PCCD_BUTT] = {HI_UNF_CI_TSI_SERIAL1, HI_UNF_CI_TSI_SERIAL2};
    HI_U16 u16CaIds[16];
    HI_U8 u8NumCaIds;
    
    if (6 == argc)
    {
        g_TunerFreq  = strtol(argv[1],NULL,0);
        s_enRouteCase = atoi(argv[2]);
        g_TunerSrate = strtol(argv[3],NULL,0);
        g_ThirdParam = strtol(argv[4],NULL,0);
        g_enDefaultFmt = HIADP_Disp_StrToFmt(argv[5]);
    }
    else if (5 == argc)
    {
        g_TunerFreq  = strtol(argv[1],NULL,0);
        s_enRouteCase = atoi(argv[2]);
        g_TunerSrate = strtol(argv[3],NULL,0);
        g_ThirdParam = strtol(argv[4],NULL,0);
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
    }
    else if (4 == argc)
    {
        g_TunerFreq  = strtol(argv[1],NULL,0);
        s_enRouteCase = atoi(argv[2]);
        g_TunerSrate = strtol(argv[3],NULL,0);
        g_ThirdParam = (g_TunerFreq>1000) ? 0 : 64;
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
    }
    else if(3 == argc)
    {
        g_TunerFreq  = strtol(argv[1],NULL,0);
        s_enRouteCase = atoi(argv[2]);
        g_TunerSrate = (g_TunerFreq>1000) ? 27500 : 6875;
        g_ThirdParam = (g_TunerFreq>1000) ? 0 : 64;
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
    }
    else if(2 == argc)
    {
        g_TunerFreq  = strtol(argv[1],NULL,0);
        s_enRouteCase = TS_ROUTE_CASE_0;
        g_TunerSrate = (g_TunerFreq>1000) ? 27500 : 6875;
        g_ThirdParam = (g_TunerFreq>1000) ? 0 : 64;
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
    }
    else
    {
        printf("Usage: %s freq [ts_route_case] [srate] [qamtype or polarization] [vo_format]\n"
                "       ts_route_case:\n"
                "           0: tuner->tso0->CAM->tsi0->demux\n"        
                "           1: tuner->cimax->CAM_A->tsi0->demux\n"    
                "           2: tuner->cimax->CAM_B->tsi2->demux_port_tsi2->demux\n"   
                "           3: tuner->tsi1->tso1->CAM_B->tsi2->demux\n"   
                "       qamtype or polarization: \n"
                "           For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64] \n"
                "           For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0] \n"
                "       vo_format:1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50  default HI_UNF_ENC_FMT_1080i_50\n",
                argv[0]);
        printf("Example: %s 610 0 \n", argv[0]);
        printf("Example: %s 610 3 6875 64 1080i_50\n", argv[0]);
        return HI_FAILURE;
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
        HI_ERR_CI("call HIADP_Snd_Init failed.\n");
        goto CI_DEINIT;
    }

    Ret = HIADP_Disp_Init(g_enDefaultFmt);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CI("call HIADP_Disp_DeInit failed.\n");
        goto SND_DEINIT;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    Ret |= HIADP_VO_CreatWin(HI_NULL,&hWin);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CI("call HIADP_VO_Init failed.\n");
        HIADP_VO_DeInit();
        goto DISP_DEINIT;
    }

    Ret = HI_UNF_DMX_Init();
    Ret |= HI_UNF_DMX_AttachTSPort(0,TSIPORT);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CI("call HIADP_Demux_Init failed.\n");
        goto VO_DEINIT;
    }

    if (DVBPORT != HI_UNF_PORT_INVALID)
    {
        Ret = HI_UNF_DMX_GetTSPortAttr(DVBPORT, &pstAttr);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_DMX_GetTSPortAttr(%d) failed, ret = 0x%08x.\n", DVBPORT, Ret);
            goto DMX_DEINIT;
        } 
        if (TSMODE == HI_UNF_CI_TS_PARALLEL)
        {
            pstAttr.enPortType = HI_UNF_DMX_PORT_TYPE_PARALLEL_NOSYNC_188;
            pstAttr.u32SerialBitSelector = 0;
        }
        else
        {
            pstAttr.enPortType = HI_UNF_DMX_PORT_TYPE_SERIAL_NOSYNC;
            pstAttr.u32SerialBitSelector = 0;
        }
        Ret = HI_UNF_DMX_SetTSPortAttr(DVBPORT, &pstAttr);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_DMX_SetTSPortAttr failed.\n");
            goto DMX_DEINIT;
        }
    }

    if (TSOPORT != HI_UNF_PORT_INVALID)
    {
        Ret = HI_UNF_DMX_GetTSOPortAttr(TSOPORT, &stTSOAttr);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_DMX_GetTSOPortAttr failed.\n");
            goto DMX_DEINIT;
        }
        stTSOAttr.bEnable = HI_TRUE;
        stTSOAttr.enTSSource = DVBPORT;
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
    }
    Ret = HI_UNF_DMX_GetTSPortAttr(TSIPORT, &pstAttr);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DMX_GetTSPortAttr failed.\n");
        goto DMX_DEINIT;
    } 
    if (TSMODE == HI_UNF_CI_TS_PARALLEL)
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

    Ret = HIADP_Tuner_Init();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CI("call HIADP_Demux_Init failed.\n");
        goto DMX_DEINIT;
    }

    if (TUNER == 0)
    {
#if (HI_TUNER_SIGNAL_TYPE == 2)
        HI_UNF_TUNER_SAT_ATTR_S stSatTunerAttr;

        GET_SAT_TUNER_CONFIG(TUNER,stSatTunerAttr);
        Ret = HI_UNF_TUNER_SetSatAttr(TUNER, &stSatTunerAttr);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_TUNER_SetSatAttr failed, return 0x%08x.\n", Ret);
            goto TUNER_DEINIT;
        }
#endif
    }
    else if (TUNER == 1)
    {
#if (HI_TUNER1_SIGNAL_TYPE == 2)
        HI_UNF_TUNER_SAT_ATTR_S stSatTunerAttr;

        GET_SAT_TUNER1_CONFIG(TUNER,stSatTunerAttr);
        Ret = HI_UNF_TUNER_SetSatAttr(TUNER, &stSatTunerAttr);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_TUNER_SetSatAttr failed, return 0x%08x.\n", Ret);
            goto TUNER_DEINIT;
        }
#endif
    }



    Ret = HIADP_Tuner_Connect(TUNER,g_TunerFreq,g_TunerSrate,g_ThirdParam);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CI("call HIADP_Tuner_Connect failed.\n");
        goto TUNER_DEINIT;
    }
    Ret = HIADP_AVPlay_RegADecLib();
    Ret |= HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CI("call HI_UNF_AVPLAY_Init failed.\n");
        goto PSISI_FREE;
    }

    while(HI_CI_GetCaSystemID(CISLOT, u16CaIds, &u8NumCaIds) != HI_SUCCESS)
    {
        sleep(1);
    }
    
    HIADP_Search_Init();
    Ret = HIADP_Search_GetAllPmt(0,&g_pProgTbl);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CI("call HIADP_Search_GetAllPmt failed\n");
        goto PSISI_FREE;
    }

    Ret = HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
    AvplayAttr.stStreamAttr.u32VidBufSize = 0x300000;
    Ret |= HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CI("call HI_UNF_AVPLAY_Create failed.\n");
        goto AVPLAY_DEINIT;
    }

    Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
    Ret |= HI_UNF_AVPLAY_ChnOpen(hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CI("call HI_UNF_AVPLAY_ChnOpen failed.\n");
        goto CHN_CLOSE;
    }

    Ret = HI_UNF_VO_AttachWindow(hWin, hAvplay);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CI("call HI_UNF_VO_AttachWindow failed.\n");
        goto CHN_CLOSE;
    }
    Ret = HI_UNF_VO_SetWindowEnable(hWin, HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CI("call HI_UNF_VO_SetWindowEnable failed.\n");
        goto WIN_DETACH;
    }
    
    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CI("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto WIN_DETACH;
    }
    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&hTrack);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CI("call HI_UNF_SND_CreateTrack failed.\n");
        goto WIN_DETACH;
    }
   
    Ret = HI_UNF_SND_Attach(hTrack, hAvplay);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CI("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_DESTROY;
    }

    Ret = HI_UNF_AVPLAY_GetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    SyncAttr.stSyncStartRegion.s32VidPlusTime = 60;
    SyncAttr.stSyncStartRegion.s32VidNegativeTime = -20;
    SyncAttr.bQuickOutput = HI_FALSE;
    Ret = HI_UNF_AVPLAY_SetAttr(hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CI("call HI_UNF_AVPLAY_SetAttr failed.\n");
        goto SND_DETACH;
    }

    ProgNum = 0;
    Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum,HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CI("call SwitchProg failed.\n");
        goto AVPLAY_STOP;
    }
    UpdatePMT(ProgNum);

    while(1)
    {
        printf("please input your command:\n");
        printf("m : enter ca menu\n");
        printf("c : mmi input pin code\n");
        printf("s : mmi input choice\n");        
        printf("x : 1-9 play program\n");
        printf("q : quit\n");

        memset(InputCmd, 0, sizeof(InputCmd));
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
        
        if ('m' == InputCmd[0])
        {
            Ret = HI_CI_MMIEnterMenu(CISLOT);
            if (Ret != HI_SUCCESS)
            {
                printf("call HI_CI_MMIEnterMenu failed.\n");
                break;
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
                break;
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
                break;
            }
        }

    	ProgNum = atoi(InputCmd);

    	if(ProgNum > 0 && ProgNum<= g_pProgTbl->prog_num)
    	{   
    		Ret = HIADP_AVPlay_PlayProg(hAvplay,g_pProgTbl,ProgNum-1,HI_TRUE);
    		if (Ret != HI_SUCCESS)
    		{
    			HI_ERR_CI("call SwitchProgfailed!\n");
    			break;
    		}
            UpdatePMT(ProgNum-1);
        }
        
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
    
CI_DEINIT:
    HI_CI_DeInit();
    
SYS_DEINIT:
    HI_SYS_DeInit();

    return Ret;
}

