/******************************************************************************

  Copyright (C), 2013-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : fbc_mosaic.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/12/23
  Description   : demo for full band capture on board hi3716cdmo2c
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
#include "hi_unf_ecs.h"
#include "hi_adp_mpi.h"
#include "hi_adp_audio.h"
#include "hi_adp_search.h"
#include "hi_adp_tuner.h"

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

#ifndef HI_TUNER_NUMBER
#define HI_TUNER_NUMBER   4
#endif
#define AVPLAY_NUM  HI_TUNER_NUMBER
HI_U32  g_DmxID[4] = {0,1,2,3};
HI_U32  g_TunerID[4] = {0,1,2,3};
HI_UNF_DMX_PORT_E  g_enDmxPort[4] = {HI_DEMUX_PORT, HI_DEMUX1_PORT, HI_DEMUX2_PORT, HI_DEMUX3_PORT};

static PMT_COMPACT_TBL *g_pProgTbl[4];

HI_VOID ConfigTSICLK()
{
   system("himm 0xf8a220fc 0xfffff");    //????????
   //system("himm 0xf8a220fc 0x3fff");    //????????
}

HI_VOID ConfigI2CAndGPIO()
{

    //system("himm 0xf8a21194 2 ");   /*I2C_1 SCL*/
    //system("himm 0xf8a21198 2 ");   /*I2C_1 SDA*/

    //system("himm 0xf8a211f8 0 ");  /*I2C_1 SCL ??*/
    //system("himm 0xf8a21204 0 ");   /*I2C_1 SDA ??*/

   // system("himm 0xf8a21158 0  ");   /*GPIO 11_6  ????? I2C_3 SCL*/
   // system("himm 0xf8a2115c 0 ");    /*GPIO 11_7 ????? I2C_3 SDA*/


   //mxl254_int
    // system("himm 0xf8a21190 0 ");  //GPIO13_4
   // system("himm 0xf8b2d400 0x10 ");  //?
      //system("himm 0xf8b2d040 0xff ");  //?
   //RESET
     system("himm 0xf8a21110 0x6 ");   //gpio9_4
     system("himm 0xf8b29400 0x10 ");  //set dir as output

     /*TODO:should call gpio api in tuner driver*/
     /*RESET TUNER*/
     //system("himm 0xf8b29040 0x00 ");
     sleep(1);
     system("himm 0xf8b29040 0xff ");  //?
}

HI_VOID ConfigTSI0()
{
    //system("himm 0xf8a2111c 0x1");
    //system("himm 0xf8a21120 0x1");
    //system("himm 0xf8a21124 0x1");
    //system("himm 0xf8a21128 0x1");
    system("himm 0xf9c01200 0xa0000715");
    system("himm 0xf9c01208 0x1");
}

HI_VOID ConfigTSI1()
{
    //system("himm 0xf8a21100 0x2");
    //system("himm 0xf8a21104 0x2");
    //system("himm 0xf8a21108 0x2");
    //system("himm 0xf8a2110c 0x2");
    system("himm 0xf9c01300 0xa0000715");
    system("himm 0xf9c01308 0x1");
}

HI_VOID ConfigTSI2()
{
    //system("himm 0xf8a21180 0x4");
    //system("himm 0xf8a21184 0x4");
    //system("himm 0xf8a21188 0x4");
    //system("himm 0xf8a2118c 0x4");
    system("himm 0xf9c01400 0xa0000715");
   system("himm 0xf9c01408 0x1");
}

HI_VOID ConfigTSI3()
{
    //system("himm 0xf8a21168 0x6");
    //system("himm 0xf8a2116c 0x6");
    //system("himm 0xf8a21170 0x6");
    //system("himm 0xf8a21174 0x6");
    system("himm 0xf9c01500 0xa0000715");

    system("himm 0xf9c01508 0x1");
}


HI_S32 main(HI_S32 argc,HI_CHAR *argv[])
{
    HI_S32                   Ret,i;
    HI_HANDLE                hWin[AVPLAY_NUM];
    HI_HANDLE                hAvplay[AVPLAY_NUM];
    HI_UNF_AVPLAY_ATTR_S     AvplayAttr;
    HI_UNF_SYNC_ATTR_S       SyncAttr;
    HI_UNF_AVPLAY_STOP_OPT_S Stop;
    HI_CHAR                  InputCmd[32];
    HI_U32                   ProgNum = 0;
    HI_RECT_S                stWinRect;
    HI_U32                   u32TunerSrate,u32TunerQamType;
    HI_U32                   TunerFreq[4];
    HI_UNF_AVPLAY_OPEN_OPT_S stVidOpenOpt;
    HI_BOOL                  bAudPlay[AVPLAY_NUM];
    HI_HANDLE                hAvplayWithSnd = HI_INVALID_HANDLE;
    HI_HANDLE                hTrack;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;

    if ( argc < HI_TUNER_NUMBER + 1 )
    {
        sample_printf("usage:%s ",argv[0]);
        for ( i = 0 ; i < HI_TUNER_NUMBER ; i++ )
        {
            sample_printf("freq%d ",i);
        }
        sample_printf("\n");
        return HI_FAILURE;
    }

    for ( i = 0 ; i < HI_TUNER_NUMBER ; i++ )
    {
        TunerFreq[i]  = strtol(argv[i + 1],NULL,0);
    }
    u32TunerSrate = 6875;
    u32TunerQamType = 64;

    HI_SYS_Init();

    HIADP_MCE_Exit();

    Ret = HIADP_Snd_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_Snd_Init failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HIADP_Disp_Init(HI_UNF_ENC_FMT_720P_50);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_Disp_DeInit failed.\n");
        goto SND_DEINIT;
    }

    Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_MOSAIC);
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_VO_Init failed.\n");
        goto DISP_DEINIT;
    }

    for (i=0; i<AVPLAY_NUM; i++)
    {
        stWinRect.s32Width = 1280 / AVPLAY_NUM;
        stWinRect.s32Height = 720;
        stWinRect.s32X = i * stWinRect.s32Width;
        stWinRect.s32Y = 0;

        Ret = HIADP_VO_CreatWin(&stWinRect,&hWin[i]);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call WinInit failed.\n");
            goto VO_DEINIT;
        }
    }

    Ret = HI_UNF_DMX_Init();
    Ret |= HIADP_Tuner_Init();
    HIADP_Search_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call HIADP_Demux_Init failed.\n");
        goto DMX_DEINIT;
    }

    for ( i = 0 ; i < HI_TUNER_NUMBER ; i++ )
    {
        HI_UNF_DMX_PORT_ATTR_S stDmxPortAttr;
        Ret = HI_UNF_DMX_GetTSPortAttr(g_enDmxPort[i],&stDmxPortAttr);
        stDmxPortAttr.enPortType = HI_UNF_DMX_PORT_TYPE_SERIAL;
        stDmxPortAttr.u32TunerInClk = 1;
        stDmxPortAttr.u32SerialBitSelector = 0;
        Ret = HI_UNF_DMX_SetTSPortAttr(g_enDmxPort[i],&stDmxPortAttr);
        Ret = HI_UNF_DMX_AttachTSPort(g_DmxID[i],g_enDmxPort[i]);
        Ret = HIADP_Tuner_Connect(g_TunerID[i],TunerFreq[i],u32TunerSrate,u32TunerQamType);
        if ( HI_SUCCESS != Ret )
        {
            sample_printf("call HIADP_Tuner_Connect(%d) failed:%#x\n",i,Ret);
            break;
        }
        Ret |= HIADP_Search_GetAllPmt(g_DmxID[i],&g_pProgTbl[i]);
        if ( HI_SUCCESS != Ret )
        {
            sample_printf("call HIADP_Search_GetAllPmt(%d) failed\n",i);
            break;
        }
    }
    if (HI_SUCCESS != Ret)
    {
        goto PSISI_FREE;
    }

    Ret = HIADP_AVPlay_RegADecLib();
    Ret |= HI_UNF_AVPLAY_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_AVPLAY_Init failed.\n");
        goto PSISI_FREE;
    }

    for(i = 0;i < AVPLAY_NUM;i++)
    {
        sample_printf("===============avplay[%d]===============\n",i);
        HI_UNF_AVPLAY_GetDefaultConfig(&AvplayAttr, HI_UNF_AVPLAY_STREAM_TYPE_TS);
        AvplayAttr.u32DemuxId = g_DmxID[i];
        AvplayAttr.stStreamAttr.u32VidBufSize = 0x200000;
        Ret = HI_UNF_AVPLAY_Create(&AvplayAttr, &hAvplay[i]);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_AVPLAY_Create failed.\n");
            goto AVPLAY_STOP;
        }

        stVidOpenOpt.enDecType = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
        stVidOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_D1;
        stVidOpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;
        Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stVidOpenOpt);
        if (HI_SUCCESS != Ret)
        {
            sample_printf("call HI_UNF_AVPLAY_ChnOpen failed.\n");
            goto AVPLAY_STOP;
        }

        Ret = HI_UNF_VO_AttachWindow(hWin[i], hAvplay[i]);
        if (HI_SUCCESS != Ret)
        {
            sample_printf("call HI_UNF_VO_AttachWindow failed.\n");
            goto AVPLAY_STOP;
        }
        Ret = HI_UNF_VO_SetWindowEnable(hWin[i], HI_TRUE);
        if (HI_SUCCESS != Ret)
        {
            sample_printf("call HI_UNF_VO_SetWindowEnable failed.\n");
            goto AVPLAY_STOP;
        }

        bAudPlay[i] = HI_FALSE;
        if (0 == i)
        {
            bAudPlay[i] = HI_TRUE;
            Ret = HI_UNF_AVPLAY_ChnOpen(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);

            Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
                goto AVPLAY_STOP;
            }
            Ret |= HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&hTrack);
            Ret |= HI_UNF_SND_Attach(hTrack, hAvplay[i]);
            if (Ret != HI_SUCCESS)
            {
                sample_printf("call HI_UNF_SND_Attach failed.\n");
                goto AVPLAY_STOP;
            }
            hAvplayWithSnd = hAvplay[i];
        }

        Ret = HI_UNF_AVPLAY_GetAttr(hAvplay[i], HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
        SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
        Ret |= HI_UNF_AVPLAY_SetAttr(hAvplay[i], HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_AVPLAY_SetAttr failed.\n");
            goto AVPLAY_STOP;
        }

        ProgNum = 0;
        Ret = HIADP_AVPlay_PlayProg(hAvplay[i], g_pProgTbl[i], ProgNum,bAudPlay[i]);
        if (HI_SUCCESS != Ret)
        {
            sample_printf("call HIADP_AVPlay_SwitchProg failed\n");
        }
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
#if 0
        ProgNum = atoi(InputCmd);
        ProgNum = ProgNum % AVPLAY_NUM;
        HI_UNF_AVPLAY_Stop(hAvplayWithSnd, HI_UNF_AVPLAY_MEDIA_CHAN_AUD,HI_NULL);
        HI_UNF_SND_Detach(hTrack,hAvplayWithSnd);
        HI_UNF_SND_DestroyTrack(hTrack);
        HI_UNF_AVPLAY_ChnClose(hAvplayWithSnd, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        hAvplayWithSnd = hAvplay[ProgNum];
        HI_UNF_AVPLAY_ChnOpen(hAvplayWithSnd, HI_UNF_AVPLAY_MEDIA_CHAN_AUD,HI_NULL);

        Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_MASTER, &stTrackAttr);
        if (Ret != HI_SUCCESS)
        {
            sample_printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
            goto AVPLAY_STOP;
        }
        HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&hTrack);
        HI_UNF_SND_Attach(hTrack, hAvplayWithSnd);
        HIADP_AVPlay_PlayAud(hAvplayWithSnd,g_pProgTbl,ProgNum);
#endif
    }

AVPLAY_STOP:
    for(i = 0 ; i < AVPLAY_NUM;i++)
    {
        Stop.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
        Stop.u32TimeoutMs = 0;
        if ( ProgNum == i )
        {
            HI_UNF_AVPLAY_Stop(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD, &Stop);
            HI_UNF_SND_Detach(hTrack, hAvplay[i]);
            HI_UNF_SND_DestroyTrack(hTrack);
        }
        else
        {
            HI_UNF_AVPLAY_Stop(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_VID, &Stop);
        }
        HI_UNF_VO_SetWindowEnable(hWin[i],HI_FALSE);
        HI_UNF_VO_DetachWindow(hWin[i], hAvplay[i]);
        if( ProgNum == i)
        {
            HI_UNF_AVPLAY_ChnClose(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_VID | HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        }
        else
        {
            HI_UNF_AVPLAY_ChnClose(hAvplay[i], HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        }

        HI_UNF_AVPLAY_Destroy(hAvplay[i]);
    }
    HI_UNF_AVPLAY_DeInit();

PSISI_FREE:
    for ( i  = 0 ; i  < HI_TUNER_NUMBER ; i ++ )
    {
        if ( g_pProgTbl[i] )
        {
            HIADP_Search_FreeAllPmt(g_pProgTbl[i]);
            HI_UNF_DMX_DetachTSPort(i);
        }
    }

DMX_DEINIT:
    HIADP_Search_DeInit();
    HIADP_Tuner_DeInit();
    HI_UNF_DMX_DeInit();

VO_DEINIT:
    for ( i = 0 ; i < AVPLAY_NUM ; i++ )
    {
        HI_UNF_VO_DestroyWindow(hWin[i]);
    }
    HIADP_VO_DeInit();

DISP_DEINIT:
    HIADP_Disp_DeInit();

SND_DEINIT:
    HIADP_Snd_DeInit();

SYS_DEINIT:
    HI_SYS_DeInit();

    return Ret;
}

