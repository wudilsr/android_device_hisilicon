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
#include <dirent.h>

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
#include "hi_go.h"
#include "hi_go_decoder.h"
#include "sample_displayInit.h"

/***************************** Macro Definition ******************************/
#define PIC_DIRNAME "./res/jpg"
#define PIC_SUFFIX "jpg"
#define MAX_FILENAME_LEN 256
#define FLIP_COUNT 2

HI_U32 g_TunerFreq;
HI_U32 g_TunerSrate;
HI_U32 g_ThirdParam;
static HI_UNF_ENC_FMT_E g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
PMT_COMPACT_TBL    *g_pProgTbl = HI_NULL;

#ifndef DEFAULT_DVB_PORT
#define DEFAULT_DVB_PORT 0
#endif

static HI_S32 filter_doublevo(const struct dirent *pentry)
{
    HI_CHAR *pos = NULL;

    pos = strrchr(pentry->d_name, '.');
    if (NULL == pos)
    {
        return 0;
    }

    pos++;
    if (strcasecmp(pos, "jpg") != 0)
    {
        return 0;
    }

    return 1;
}

static HI_S32 file_dec_doublevo(HI_CHAR *pszFileName, HI_HANDLE *pSurface)
{
    HI_S32 Ret;
    HI_HANDLE hDecoder;
    HIGO_DEC_ATTR_S stSrcDesc;

    /** create decode*/
    stSrcDesc.SrcType = HIGO_DEC_SRCTYPE_FILE;
    stSrcDesc.SrcInfo.pFileName = pszFileName;
    Ret = HI_GO_CreateDecoder(&stSrcDesc, &hDecoder);
    if (HI_SUCCESS != Ret)
    {
        return Ret;
    }

    /** decode it to Surface */
    Ret  = HI_GO_DecImgData(hDecoder, 0, NULL, pSurface);
    Ret |= HI_GO_DestroyDecoder(hDecoder);

    return Ret;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32                          Ret, i;
    HI_HANDLE                       hWin[2];
    HI_HANDLE                       hAvplay[2];
    HI_UNF_AVPLAY_ATTR_S            AvplayAttr;
    HI_UNF_SYNC_ATTR_S              SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S        Stop;
    HI_CHAR                         InputCmd[32];
    HI_U32                          StartX_HD, StartY_HD, StartX_SD, StartY_SD;
    HI_S32                          s32FileNum;
    HI_HANDLE                       hDecSurface, hLayer_HD, hLayer_SD, hLayer_Surface_HD, hLayer_Surface_SD;
    HI_CHAR                         aszFileName[MAX_FILENAME_LEN + 1];
    HIGO_LAYER_INFO_S               stLayerInfo_HD, stLayerInfo_SD;
    HIGO_BLTOPT_S                   stBltOpt   = {0};
    struct                          dirent **filelist = NULL;
    HIGO_LAYER_E                    eLayerID_HD = HIGO_LAYER_HD_0;
    HIGO_LAYER_E                    eLayerID_SD = HIGO_LAYER_SD_0;
    HI_UNF_DISP_BG_COLOR_S          BgColor;
    HI_UNF_DISP_INTF_S              stDispIntf[2];
    HI_UNF_WINDOW_ATTR_S            WinAttr_HD, WinAttr_SD;
    HI_HANDLE                       hTrack[2];
    HI_UNF_AUDIOTRACK_ATTR_S        stTrackAttr;
    
    if (5 == argc)
    {
        g_TunerFreq  = strtol(argv[1], NULL, 0);
        g_TunerSrate = strtol(argv[2], NULL, 0);
        g_ThirdParam = strtol(argv[3], NULL, 0);
        g_enDefaultFmt = HIADP_Disp_StrToFmt(argv[4]);
    }
    else if (4 == argc)
    {
        g_TunerFreq  = strtol(argv[1], NULL, 0);
        g_TunerSrate = strtol(argv[2], NULL, 0);
        g_ThirdParam = strtol(argv[3], NULL, 0);
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
    }
    else if (3 == argc)
    {
        g_TunerFreq  = strtol(argv[1], NULL, 0);
        g_TunerSrate = strtol(argv[2], NULL, 0);
        g_ThirdParam = (g_TunerFreq>1000) ? 0 : 64;
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
    }
    else if (2 == argc)
    {
        g_TunerFreq  = strtol(argv[1], NULL, 0);
        g_TunerSrate = (g_TunerFreq>1000) ? 27500 : 6875;
        g_ThirdParam = (g_TunerFreq>1000) ? 0 : 64;
        g_enDefaultFmt = HI_UNF_ENC_FMT_1080i_50;
    }
    else
    {
        printf("Usage: %s freq [srate] [qamtype or polarization] [hd_vo_format] \n"
                "       qamtype or polarization: \n"
                "           For cable, used as qamtype, value can be 16|32|[64]|128|256|512 defaut[64] \n"
                "           For satellite, used as polarization, value can be [0] horizontal | 1 vertical defaut[0] \n"
                "       hd_vo_format:2160P_30|2160P_24|1080P_60|1080P_50|1080i_60|[1080i_50]|720P_60|720P_50\n",
                argv[0]);
        printf("Example: %s 610 6875 64 1080i_50 \n", argv[0]);
        return HI_FAILURE;
    }

    HI_SYS_Init();
    HIADP_MCE_Exit();
    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Snd_Init failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HI_UNF_DISP_Init();
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DISP_Init failed.\n");
        goto SND_DEINIT;
    }

    Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DISP_Open failed.\n");
        goto DISP_DEINIT;
    }

    Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY0);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_DISP_Open SD failed.\n");
        HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
        goto DISP1_CLOSE;
    }
    Ret = HIADP_HDMI_Init(HI_UNF_HDMI_ID_0, g_enDefaultFmt);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DISP_Open SD failed.\n");
        goto DISP0_CLOSE;
    }

    BgColor.u8Red   = 0;
    BgColor.u8Green = 0;
    BgColor.u8Blue  = 0;
    Ret = HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY1, &BgColor);
    Ret |= HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY0, &BgColor);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DISP_SetBgColor failed!\n");
        goto HDMI_DEINIT;
    }
    
    Ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, g_enDefaultFmt);
    
    if ((HI_UNF_ENC_FMT_1080P_60 == g_enDefaultFmt)
        || (HI_UNF_ENC_FMT_1080i_60 == g_enDefaultFmt)
        || (HI_UNF_ENC_FMT_720P_60 == g_enDefaultFmt)
        || (HI_UNF_ENC_FMT_480P_60 == g_enDefaultFmt))
    {
        Ret |= HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, HI_UNF_ENC_FMT_NTSC);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_DISP_SetFormat failed.\n");
            goto HDMI_DEINIT;
        }
    }

    if ((HI_UNF_ENC_FMT_1080P_50 == g_enDefaultFmt)
        || (HI_UNF_ENC_FMT_1080i_50 == g_enDefaultFmt)
        || (HI_UNF_ENC_FMT_720P_50 == g_enDefaultFmt)
        || (HI_UNF_ENC_FMT_576P_50 == g_enDefaultFmt))
    {
        Ret |= HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, HI_UNF_ENC_FMT_PAL);
        if (HI_SUCCESS != Ret)
        {
            printf("call HI_UNF_DISP_SetFormat failed.\n");
            goto HDMI_DEINIT;
        }
    }

    stDispIntf[0].enIntfType = HI_UNF_DISP_INTF_TYPE_CVBS;
    stDispIntf[0].unIntf.stCVBS.u8Dac = DAC_CVBS;
    Ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY0, &stDispIntf[0], 1);

    stDispIntf[0].enIntfType               = HI_UNF_DISP_INTF_TYPE_YPBPR;
    stDispIntf[0].unIntf.stYPbPr.u8DacY    = DAC_YPBPR_Y;
    stDispIntf[0].unIntf.stYPbPr.u8DacPb   = DAC_YPBPR_PB;
    stDispIntf[0].unIntf.stYPbPr.u8DacPr   = DAC_YPBPR_PR;
    stDispIntf[1].enIntfType            = HI_UNF_DISP_INTF_TYPE_HDMI;
    stDispIntf[1].unIntf.enHdmi         = HI_UNF_HDMI_ID_0;    
    Ret |= HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY1, &stDispIntf[0], 2);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_DISP_AttachIntf failed.\n");
        goto HDMI_DEINIT;
    }    

    Ret = HI_UNF_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_Init failed.\n");
        goto HDMI_DEINIT;
    }

    WinAttr_SD.enDisp = HI_UNF_DISPLAY0;
    WinAttr_SD.bVirtual = HI_FALSE;
    WinAttr_SD.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    WinAttr_SD.stWinAspectAttr.enAspectCvrs = HI_UNF_VO_ASPECT_CVRS_IGNORE;
    WinAttr_SD.stInputRect.s32X = 0;
    WinAttr_SD.stInputRect.s32Y = 0;
    WinAttr_SD.stInputRect.s32Width  = 720;
    WinAttr_SD.stInputRect.s32Height = 576;
    WinAttr_SD.bUseCropRect = HI_FALSE;
    memset(&WinAttr_SD.stOutputRect, 0x0, sizeof(HI_RECT_S));
    Ret = HI_UNF_VO_CreateWindow(&WinAttr_SD, &hWin[0]);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_CreateWindow failed.\n");
        goto VO_DEINIT;
    }

    WinAttr_HD.enDisp = HI_UNF_DISPLAY1;
    WinAttr_HD.bVirtual = HI_FALSE;
    WinAttr_HD.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    WinAttr_HD.stWinAspectAttr.enAspectCvrs = HI_UNF_VO_ASPECT_CVRS_IGNORE;
    WinAttr_HD.stInputRect.s32X = 0;
    WinAttr_HD.stInputRect.s32Y = 0;
    WinAttr_HD.stInputRect.s32Width  = 1920;
    WinAttr_HD.stInputRect.s32Height = 1080;
    WinAttr_HD.bUseCropRect = HI_FALSE;
    memset(&WinAttr_HD.stOutputRect, 0x0, sizeof(HI_RECT_S));
    Ret = HI_UNF_VO_CreateWindow(&WinAttr_HD, &hWin[1]);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_CreateWindow failed.\n");
        goto WIN0_DESTROY;
    }
    
    Ret  = HI_UNF_DMX_Init();
    Ret |= HI_UNF_DMX_AttachTSPort(0, DEFAULT_DVB_PORT);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Demux_Init failed.\n");
        goto WIN1_DESTROY;
    }

    Ret = HIADP_Tuner_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Demux_Init failed.\n");
        goto DMX_DEINIT;
    }

    Ret = HIADP_Tuner_Connect(TUNER_USE, g_TunerFreq, g_TunerSrate, g_ThirdParam);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Tuner_Connect failed.\n");
        goto TUNER_DEINIT;
    }

    HIADP_Search_Init();
    Ret = HIADP_Search_GetAllPmt(0, &g_pProgTbl);
    if (HI_SUCCESS != Ret)
    {
        printf("call HIADP_Search_GetAllPmt failed\n");
        goto SEARCH_DEINIT;
    }

    Ret  = HIADP_AVPlay_RegADecLib();
    Ret |= HI_UNF_AVPLAY_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_AVPLAY_Init failed\n");
        goto PSISI_FREE;
    }

    for (i = 0; i < 2; i++)
    {
        printf("===============avplay[%d]===============\n", i);
        HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
        AvplayAttr.stStreamAttr.u32VidBufSize = 0x200000;
        Ret = HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay[i]);
        Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
        if (0 == i)
        {
            Ret |= HI_UNF_AVPLAY_ChnOpen(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
            Ret |= HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
            if (Ret != HI_SUCCESS)
            {
                printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
            }
            Ret |= HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack[i]);               
            Ret |= HI_UNF_SND_Attach(hTrack[i], hAvplay[i]);
        }

        if(1 == i)
        {
            Ret |= HI_UNF_AVPLAY_ChnOpen(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
            Ret |= HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_SLAVE, &stTrackAttr);
            if (Ret != HI_SUCCESS)
            {
                printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
            }
            Ret |= HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack[i]);  
            Ret |= HI_UNF_SND_Attach(hTrack[i], hAvplay[i]);
        }

        Ret |= HI_UNF_VO_AttachWindow(hWin[i], hAvplay[i]);
        Ret |= HI_UNF_VO_SetWindowEnable(hWin[i], HI_TRUE);
        if (Ret != HI_SUCCESS)
        {
            printf("call HI_UNF_VO_SetWindowEnable failed.\n");
            goto AVPLAY_STOP;
        }

        Ret = HI_UNF_AVPLAY_GetAttr(hAvplay[i], HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
        SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
        Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay[i], HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
        Ret |= HIADP_AVPlay_PlayProg(hAvplay[i], g_pProgTbl, i, HI_TRUE);
        if (HI_SUCCESS != Ret)
        {
            printf("call HIADP_AVPlay_PlayProg failed\n");
        }
    }

    Ret  = HI_GO_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_GO_Init failed\n");
        goto AVPLAY_STOP;
    }
    
    Ret = HI_GO_GetLayerDefaultParam(eLayerID_HD, &stLayerInfo_HD);
    stLayerInfo_HD.ScreenWidth  = 1280 / 2;
    stLayerInfo_HD.ScreenHeight = 720 / 2;
    stLayerInfo_HD.PixelFormat = HIGO_PF_8888;

    /**create the graphic layer and get the handler */
    Ret |= HI_GO_CreateLayer(&stLayerInfo_HD, &hLayer_HD);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_GO_CreateLayer failed\n");
        goto HIGO_DEINIT;
    }

    StartX_HD = 600;
    StartY_HD = 300;
    Ret = HI_GO_SetLayerPos(hLayer_HD, StartX_HD, StartY_HD);
    Ret |= HI_GO_GetLayerSurface(hLayer_HD, &hLayer_Surface_HD);
    Ret |= HI_GO_SetLayerAlpha(hLayer_HD, 200);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_GO_SetLayerAlpha failed\n");
        goto DESTROY_HD;
    }

    Ret = HI_GO_GetLayerDefaultParam(eLayerID_SD, &stLayerInfo_SD);
    stLayerInfo_SD.PixelFormat  = HIGO_PF_8888;
    stLayerInfo_SD.ScreenWidth  = 720 / 2;
    stLayerInfo_SD.ScreenHeight = 576 / 2;
    StartX_SD = 300;
    StartY_SD = 100;

    /**create the graphic layer and get the handler */
    Ret |= HI_GO_CreateLayer(&stLayerInfo_SD, &hLayer_SD);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_GO_CreateLayer failed\n");
        goto DESTROY_HD;
    }

    Ret = HI_GO_SetLayerPos(hLayer_SD, StartX_SD, StartY_SD);
    Ret |= HI_GO_GetLayerSurface(hLayer_SD, &hLayer_Surface_SD);
    Ret |= HI_GO_SetLayerAlpha(hLayer_SD, 200);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_GO_CreateLayer failed\n");
        goto DESTROY_SD;
    }

    /**get the jpeg file from the path */
    s32FileNum = scandir(PIC_DIRNAME, &filelist, filter_doublevo, alphasort);
    if (s32FileNum < 2)
    {
        printf("no enough file!\n");
        goto DESTROY_SD;
    }

    stBltOpt.EnableScale = HI_TRUE;

    sprintf(aszFileName, "%s/%s", PIC_DIRNAME, filelist[0]->d_name);

    /**decoding*/
    Ret = file_dec_doublevo(aszFileName, &hDecSurface);
    if (HI_SUCCESS == Ret)
    {
        /** Blit it to graphic layer Surface */
        HI_GO_Blit(hDecSurface, NULL, hLayer_Surface_HD, NULL, &stBltOpt);
        HI_GO_RefreshLayer(hLayer_HD, NULL);
        HI_GO_FreeSurface(hDecSurface);
    }

    sprintf(aszFileName, "%s/%s", PIC_DIRNAME, filelist[1]->d_name);

    /**decoding*/
    Ret = file_dec_doublevo(aszFileName, &hDecSurface);
    if (HI_SUCCESS == Ret)
    {
        /** Blit it to graphic layer Surface */
        HI_GO_Blit(hDecSurface, NULL, hLayer_Surface_SD, NULL, &stBltOpt);
        HI_GO_RefreshLayer(hLayer_SD, NULL);
        HI_GO_FreeSurface(hDecSurface);
    }

    /** free the memory which saving the file name */
    while (s32FileNum--)
    {
        free(filelist[s32FileNum]);
    }

    while (1)
    {
        printf("please input the q to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
    }

DESTROY_SD:
    HI_GO_DestroyLayer(hLayer_SD);
DESTROY_HD:
    HI_GO_DestroyLayer(hLayer_HD);
HIGO_DEINIT:
    HI_GO_Deinit();

AVPLAY_STOP:
    for (i = 0; i < 2; i++)
    {
        Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
        Stop.u32TimeoutMs = 0;

        HI_UNF_AVPLAY_Stop(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
        HI_UNF_SND_Detach(hTrack[i], hAvplay[i]);

        HI_UNF_VO_SetWindowEnable(hWin[i], HI_FALSE);
        HI_UNF_VO_DetachWindow(hWin[i], hAvplay[i]);

        HI_UNF_AVPLAY_ChnClose(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
   
        HI_UNF_AVPLAY_Destroy(hAvplay[i]);

        HI_UNF_SND_DestroyTrack(hTrack[i]);
    }

    HI_UNF_AVPLAY_DeInit();
    
PSISI_FREE:
    HIADP_Search_FreeAllPmt(g_pProgTbl);
SEARCH_DEINIT:    
    HIADP_Search_DeInit();
TUNER_DEINIT:
    HIADP_Tuner_DeInit();
DMX_DEINIT:
    HI_UNF_DMX_DetachTSPort(0);
    HI_UNF_DMX_DeInit();
WIN1_DESTROY:    
    HI_UNF_VO_DestroyWindow(hWin[1]);    
WIN0_DESTROY:    
    HI_UNF_VO_DestroyWindow(hWin[0]);    
VO_DEINIT:
    HI_UNF_VO_DeInit();
HDMI_DEINIT:
    HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_0);
DISP0_CLOSE:    
    HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
DISP1_CLOSE:
    HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
DISP_DEINIT:
    HI_UNF_DISP_DeInit();
SND_DEINIT:
    HIADP_Snd_DeInit();
SYS_DEINIT:
    HI_SYS_DeInit();
    return Ret;
}

