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
#include "hi_drv_ao.h"
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

#if defined (DOLBYPLUS_HACODEC_SUPPORT)
 #include "HA.AUDIO.DOLBYPLUS.decode.h"
#endif

extern HI_AEF_COMPONENT_S srs_effect_entry;
HI_AEF_COMPONENT_S *pstEntry = &srs_effect_entry;

#define BYTES_PERFRAME (256*2*sizeof(HI_S16)*8)

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif
FILE   *g_pAudEsFile;
FILE *g_pAefFile = HI_NULL;

static pthread_t g_EsThd;
static pthread_t g_EsThd1;

HI_S32 g_AudEsFileOffest;


static HI_BOOL g_StopThread = HI_FALSE;

HI_U8 *pu8InBufAddr;
HI_U8 *pu8OutBufAddr;

HI_VOID AudioRecFrmTthread(HI_VOID *args)
{
    HI_HANDLE hAef;
    HI_AEF_OUTPUT_S stAOut;
    HI_S32 Ret;
    HI_BOOL bAudBufAvail = HI_TRUE;
    HI_U32 u32FrameIndex;
    HI_U32 u32WriteLgth;
    
    bAudBufAvail = HI_FALSE;

    hAef = *(HI_HANDLE*)args;

    while (!g_StopThread)
    {       
        usleep(1000 * 3);
        Ret = pstEntry->AefReceiveFrame(hAef, &stAOut);
        if(Ret == HI_SUCCESS)
        {
            //printf("stAOut.u32PcmOutbytesPerFrame[%d]\n",stAOut.u32PcmOutbytesPerFrame);
            u32WriteLgth = fwrite((pu8OutBufAddr+(HI_U32)stAOut.u32PcmOutBuf), 1, stAOut.u32PcmOutbytesPerFrame, g_pAefFile);
            u32FrameIndex = stAOut.u32FrameIndex;
            pstEntry->AefReleaseFrame(hAef, u32FrameIndex);
        }
        
    }
    return;
}

HI_VOID AudioTthread(HI_VOID *args)
{
    HI_HANDLE hAef;
    HI_AFE_INBUF_PROCESS_S stGetBuf;
    HI_UNF_STREAM_BUF_S StreamBuf;
    HI_U32 Readlen;
    HI_S32 Ret;
    HI_BOOL bAudBufAvail = HI_TRUE;
    
    bAudBufAvail = HI_FALSE;

    hAef = *(HI_HANDLE*)args;

    StreamBuf.pu8Data = (HI_U8*)malloc(BYTES_PERFRAME+4);
    while (!g_StopThread)
    {
        stGetBuf.u32RequestSize = BYTES_PERFRAME;
        Ret = pstEntry->AefGetBuf(hAef, &stGetBuf);

        if (HI_SUCCESS == Ret)
        {
            bAudBufAvail = HI_TRUE;
            Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), BYTES_PERFRAME, g_pAudEsFile);
            if (BYTES_PERFRAME == Readlen)
            {
                if (stGetBuf.u32BufRequestSize2 > 0)
                {
                    memcpy(pu8InBufAddr+stGetBuf.u32BufOffsetAddr1, (HI_VOID*)StreamBuf.pu8Data, stGetBuf.u32BufRequestSize1);
                    memcpy(pu8InBufAddr+stGetBuf.u32BufOffsetAddr2, (HI_VOID*)(StreamBuf.pu8Data+stGetBuf.u32BufRequestSize1), stGetBuf.u32BufRequestSize2);
                }
                else
                {
                    memcpy(pu8InBufAddr+stGetBuf.u32BufOffsetAddr1, (HI_VOID*)StreamBuf.pu8Data, stGetBuf.u32BufRequestSize1);
                }
                Ret = pstEntry->AefPutBuf(hAef, &stGetBuf);
                if (Ret != HI_SUCCESS)
                {
                    sample_printf("call AefPutBuf failed.\n");
                }
            }
            else
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
    free(StreamBuf.pu8Data);
    return;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 Ret;
    HI_HANDLE hAef;    
    HI_U32 AdecType;
    HI_CHAR InputCmd[32];
    HI_AEF_INPUTBUF_S stInBufAttr;
    HI_AEF_OUTPUTBUF_S stOutBufAttr;

    if (argc < 3)
    {
        sample_printf(" usage: ./sample_audioplay InFile OutFile\n");
        sample_printf(" examples: \n");
        sample_printf("        ./sample_audioplay /mnt/In.pcm /mnt/Out.pcm\n");
        return -1;
    }

        g_pAudEsFile = fopen(argv[1], "rb");
        if (!g_pAudEsFile)
        {
            sample_printf("open file %s error!\n", argv[1]);
            return -1;
        }

        if (strcasecmp("null", argv[2]))
        {
            g_pAefFile = fopen(argv[2], "wb");
            if (!g_pAefFile)
            {
                sample_printf("open file %s error!\n", argv[2]);
                return -1;
            }
        }
        
        AdecType = HA_AUDIO_ID_PCM;
        
    HI_SYS_Init();
    
    Ret = HIADP_Snd_RegAefAuthLib();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_RegisterAefAuthLib failed.\n");
        goto SYS_DEINIT;
    }
#if 1 //Create
    HI_AEF_SRS_OPENPARAM_S stSRSParams;
    HI_AEF_SRS_PARAM_S     stParams;
    HI_AEF_SRS_CONFIG_S    stSRSConfig;
    stSRSParams.pstSRSParam = &stParams;
    stSRSParams.pstSRSConfig = &stSRSConfig;
    HI_AEF_SRS_GetDefaultOpenParam(&stSRSParams);
    stSRSParams.pstSRSConfig->stMainConfig.bEnable = HI_TRUE;    
    stSRSParams.bMaster = HI_TRUE;

	HI_AEF_AUTHORIZE_S stAuthEntry;
    Ret = pstEntry->AefCreate(&stAuthEntry,(HI_VOID *)(&stSRSParams), &hAef);
    if(HI_SUCCESS != Ret)
    {
        sample_printf(" SRS create failed\n");
            goto SYS_DEINIT;
    }
#endif    

#if 1 // Init buf
    stInBufAttr.u32BufSize = 128*1024;

    Ret = pstEntry->AefInbufInit(hAef, &stInBufAttr);
    if(HI_SUCCESS != Ret)
    {
        sample_printf(" SRS InbufInit failed\n");
            goto AEF_DESTROY;
    }

    pu8InBufAddr = (HI_U8 *)HI_MEM_Map(stInBufAttr.u32BufAddr, stInBufAttr.u32BufSize);

    stOutBufAttr.u32MaxBufSizePerFrame = 1024;
    stOutBufAttr.u32OutFrameNum = 8;
    Ret = pstEntry->AefOutbufInit(hAef, &stOutBufAttr);
    if(HI_SUCCESS != Ret)
    {
        sample_printf(" SRS OutbufInit failed\n");
            goto AEF_DEINIT_INBUF;
    }
    
    pu8OutBufAddr = (HI_U8 *)HI_MEM_Map(stOutBufAttr.u32BufAddr, stOutBufAttr.u32BufSize);

#endif 

#if 1
    Ret = pstEntry->AefSetParameter(hAef, 0, stSRSParams.pstSRSParam);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call AefSetParameter failed.\n");
        goto AEF_DEINIT_OUTBUF;
    }
#endif    

#if 1
    
    Ret = pstEntry->AefSetConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_All, stSRSParams.pstSRSConfig);
    if (Ret != HI_SUCCESS)
    {
        printf("call AefSetConfig failed.\n");
        goto AEF_DEINIT_OUTBUF;
    }    
    
    Ret = pstEntry->AefGetConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_All, stSRSParams.pstSRSConfig);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call AefGetConfig failed.\n");
        goto AEF_DEINIT_OUTBUF;
    }    

#endif    

    Ret = pstEntry->AefSetEnable(hAef, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call AefSetEnable failed.\n");
        goto AEF_DEINIT_OUTBUF;
    }

    g_StopThread = HI_FALSE;
    pthread_create(&g_EsThd, HI_NULL, (HI_VOID *)AudioTthread, (HI_VOID*)&hAef);
    pthread_create(&g_EsThd1, HI_NULL, (HI_VOID *)AudioRecFrmTthread, (HI_VOID*)&hAef);
    
    while (1)
    {
        printf("please input the q to quit!\n");
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
        if ('c' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
    }

    g_StopThread = HI_TRUE;
    pthread_join(g_EsThd, HI_NULL);
    pthread_join(g_EsThd1, HI_NULL);
    
    pstEntry->AefSetEnable(hAef, HI_FALSE);

AEF_DEINIT_OUTBUF:
    HI_MEM_Unmap((HI_VOID *)pu8OutBufAddr);
    pstEntry->AefOutBufDeInit(hAef);
AEF_DEINIT_INBUF:
    HI_MEM_Unmap((HI_VOID *)pu8InBufAddr);
    pstEntry->AefInBufDeInit(hAef);
AEF_DESTROY:
    pstEntry->AefDestroy(hAef);
SYS_DEINIT:
    HI_SYS_DeInit();

    fclose(g_pAudEsFile);
    g_pAudEsFile = HI_NULL;

    if(g_pAefFile)
    {
        fclose(g_pAefFile);  
        g_pAefFile = HI_NULL;
    }

    return 0;
}
