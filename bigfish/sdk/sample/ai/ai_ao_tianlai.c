/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : cast.c
  Version       : Initial Draft
  Author        : Hisilicon audio 
  Created       : 2010/01/26
  Description   :
  History       :
  1.Date        : 2013/06/1
    Author      : audio
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
#include "hi_unf_ai.h"
#include "hi_unf_sound.h"
#include "hi_adp_mpi.h"


#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

#define CAST_FILE_SAVE_MAX_SIZE  500*1024*1024     //MB

HI_U32 g_u32FileSaveLimitSize;
FILE *g_pAIFile = HI_NULL;
static pthread_t g_VirThd;
static HI_BOOL g_StopThread = HI_FALSE;

#if 1

HI_VOID VirTthread(HI_VOID *args)
{
    HI_S32 Ret;
    HI_UNF_AO_FRAMEINFO_S  stAiFrame;
    HI_UNF_AO_FRAMEINFO_S *pstAiFrame = &stAiFrame;
    HI_U32 FrameSize = 0;
    HI_U32 u32TotalCounter=0;
    HI_HANDLE hVirTra = *(HI_HANDLE *)args; 
#if 0
    pstAiFrame->ps32PcmBuffer = malloc(4000);
 
    if(NULL == pstAiFrame->ps32PcmBuffer)
    {
        printf("malloc PcmBuffer error\n");
        return;
    }
#endif   
    while (!g_StopThread)
    {
        Ret = HI_UNF_SND_AcquireTrackFrame(hVirTra, pstAiFrame, 0);
        if(HI_SUCCESS != Ret)
        {
            //printf("-----%s----%d----\n",__FUNCTION__,__LINE__);
            usleep(5*1000);
            continue;
        }
        FrameSize = pstAiFrame->u32PcmSamplesPerFrame*pstAiFrame->u32Channels*pstAiFrame->s32BitPerSample /8;
        u32TotalCounter += FrameSize;
        if(u32TotalCounter <= g_u32FileSaveLimitSize*1024*1024)
        {
            
            //printf("-----%s----%d----\n",__FUNCTION__,__LINE__);
            //printf("----%s----%d------,*pstAiFrame->ps32PcmBuffer = 0x%x,FrameSize = %d\n",__FUNCTION__,__LINE__,*pstAiFrame->ps32PcmBuffer,FrameSize);
            fwrite(pstAiFrame->ps32PcmBuffer, 1, FrameSize, g_pAIFile);
        }

        HI_UNF_SND_ReleaseTrackFrame(hVirTra, pstAiFrame);
    }
    
    if(g_pAIFile)
    {
        fclose(g_pAIFile);  
        g_pAIFile = HI_NULL;
    }

    return;
}
#endif

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 Ret;
    HI_HANDLE hAi;
    HI_UNF_AI_ATTR_S stAitAttr;
    HI_HANDLE hTrackSlave;
    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;
    HI_HANDLE hTrackVir;
    
    HI_CHAR InputCmd[32];
/************************
  HI_UNF_AI_ADC0 :MIC_In
  HI_UNF_AI_ADC1:VGA_In
  HI_UNF_AI_ADC2:AV0
  HI_UNF_AI_ADC3:YPbPr
  HI_UNF_AI_ADC4:AV1
*************************/  

    if (argc < 2)
    {
#if 1
        printf(" usage: sample_ai source(0(MIC)/1(VGA)/2(AV0)/3(YPbPr))/4(AV1)\n");
        printf(" examples: \n");
        printf(" sample_ai 0 \n");
#endif
        return 0;
    }

    g_u32FileSaveLimitSize = 100;

    g_pAIFile = fopen("./ai.pcm", "wb");
    if (!g_pAIFile)
    {
        sample_printf("open the file ./ai.pcm failed!\n");
        return -1;
    }

    HI_SYS_Init();
	
    Ret = HI_UNF_AI_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call AiInit failed.\n");
        goto SYS_DEINIT;
    }

    /************************
      HI_UNF_AI_ADC0 :MIC_In
      HI_UNF_AI_ADC1:VGA_In
      HI_UNF_AI_ADC2:AV0
      HI_UNF_AI_ADC3:YPbPr
      HI_UNF_AI_ADC4:AV1
    *************************/    

    if ('0' == argv[1][0])
    {
        Ret = HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC0,&stAitAttr);
        stAitAttr.u32PcmFrameMaxNum = 8;
        if(HI_SUCCESS != Ret)
        {
            printf("Get Default Ai Attr Failed \n");
            goto AI_DEINIT;
        }
        
        Ret = HI_UNF_AI_Create(HI_UNF_AI_ADC0, &stAitAttr, &hAi);
        if(HI_SUCCESS != Ret)
        {
            printf("Ai Create Failed \n");
            goto AI_DEINIT;
        }
    }


    if ('1' == argv[1][0])
    {
        Ret = HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC1,&stAitAttr);
        stAitAttr.u32PcmFrameMaxNum = 8;
        if(HI_SUCCESS != Ret)
        {
            printf("Get Default Ai Attr Failed \n");
            goto AI_DEINIT;
        }
        
        Ret = HI_UNF_AI_Create(HI_UNF_AI_ADC1, &stAitAttr, &hAi);
        if(HI_SUCCESS != Ret)
        {
            printf("Ai Create Failed \n");
            goto AI_DEINIT;
        }
    }    


    if ('2' == argv[1][0])
    {
        Ret = HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC2,&stAitAttr);
        if(HI_SUCCESS != Ret)
        {
            printf("Get Default Ai Attr Failed \n");
            goto AI_DEINIT;
        }
        
        Ret = HI_UNF_AI_Create(HI_UNF_AI_ADC2, &stAitAttr, &hAi);
        if(HI_SUCCESS != Ret)
        {
            printf("Ai Create Failed \n");
            goto AI_DEINIT;
        }
    }   

    if ('3' == argv[1][0])
    {
        Ret = HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC3,&stAitAttr);
        if(HI_SUCCESS != Ret)
        {
            printf("Get Default Ai Attr Failed \n");
            goto AI_DEINIT;
        }
        
        Ret = HI_UNF_AI_Create(HI_UNF_AI_ADC3, &stAitAttr, &hAi);
        if(HI_SUCCESS != Ret)
        {
            printf("Ai Create Failed \n");
            goto AI_DEINIT;
        }
    }    


    if ('4' == argv[1][0])
    {
        Ret = HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC4,&stAitAttr);
        if(HI_SUCCESS != Ret)
        {
            printf("Get Default Ai Attr Failed \n");
            goto AI_DEINIT;
        }
        
        Ret = HI_UNF_AI_Create(HI_UNF_AI_ADC4, &stAitAttr, &hAi);
        if(HI_SUCCESS != Ret)
        {
            printf("Ai Create Failed \n");
            goto AI_DEINIT;
        }
    }    

    Ret = HIADP_Snd_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call SndInit failed.\n");
        goto AI_DESTROY;
    }

    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_SLAVE, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto SND_DEINIT;
    }
    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&hTrackSlave);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto SND_DEINIT;
    }

    Ret = HI_UNF_SND_Attach(hTrackSlave, hAi);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_SLAVE_DESTROY;
    }

    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_VIRTUAL, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto TRACK_SLAVE_DETACH;
    }

    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0,&stTrackAttr,&hTrackVir);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto TRACK_SLAVE_DESTROY;
    }

    Ret = HI_UNF_SND_Attach(hTrackVir, hAi);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_VIR_DESTROY;
    }

    Ret = HI_UNF_AI_SetEnable(hAi, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_Attach failed.\n");
        goto TRACK_VIR_DETACH;
    }

    g_StopThread = HI_FALSE;
    pthread_create(&g_VirThd, HI_NULL, (HI_VOID *)VirTthread, &hTrackVir);
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

    g_StopThread = HI_TRUE;
    pthread_join(g_VirThd, HI_NULL);
	
    
    HI_UNF_AI_SetEnable(hAi, HI_FALSE);
    
TRACK_VIR_DETACH:
    HI_UNF_SND_Detach(hTrackVir, hAi);
TRACK_VIR_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrackVir);
TRACK_SLAVE_DETACH:
    HI_UNF_SND_Detach(hTrackSlave, hAi);
TRACK_SLAVE_DESTROY:
    HI_UNF_SND_DestroyTrack(hTrackSlave);
SND_DEINIT:
    HIADP_Snd_DeInit();
AI_DESTROY:
    HI_UNF_AI_Destroy(hAi);
AI_DEINIT:
    HI_UNF_AI_DeInit();
SYS_DEINIT:
    HI_SYS_DeInit();

    if(g_pAIFile)
    {
        fclose(g_pAIFile);  
        g_pAIFile = HI_NULL;
    }

    return 0;
}

