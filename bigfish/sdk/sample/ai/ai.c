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
static pthread_t g_AiThd;
static HI_BOOL g_StopThread = HI_FALSE;

HI_VOID AiTthread(HI_VOID *args)
{
    HI_S32 Ret;
    HI_UNF_AO_FRAMEINFO_S  stAiFrame;
    HI_UNF_AO_FRAMEINFO_S *pstAiFrame = &stAiFrame;
    HI_U32 FrameSize = 0;
    HI_U32 u32TotalCounter=0;
    HI_HANDLE hAi = *(HI_HANDLE *)args; 
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
        Ret = HI_UNF_AI_AcquireFrame(hAi, pstAiFrame, 0);
        FrameSize = pstAiFrame->u32PcmSamplesPerFrame*pstAiFrame->u32Channels*pstAiFrame->s32BitPerSample /8;
        u32TotalCounter += FrameSize;
        if(u32TotalCounter <= g_u32FileSaveLimitSize*1024*1024)
        {
            //printf("----%s----%d------,*pstAiFrame->ps32PcmBuffer = 0x%x,FrameSize = %d\n",__FUNCTION__,__LINE__,*pstAiFrame->ps32PcmBuffer,FrameSize);
            fwrite(pstAiFrame->ps32PcmBuffer, 1, FrameSize, g_pAIFile);
        }
        HI_UNF_AI_ReleaseFrame(hAi, pstAiFrame);
    }
    
    if(g_pAIFile)
    {
        fclose(g_pAIFile);  
        g_pAIFile = HI_NULL;
    }

    return;
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 Ret;
    HI_HANDLE hAi;
    HI_UNF_AI_ATTR_S stAitAttr;
    
    HI_CHAR InputCmd[32];

    if (argc < 3)
    {
#if 1
        printf(" usage: sample_ai  size(MB)   File(/**/**.pcm) \n");
        printf(" examples: \n");
        printf(" sample_ai 100 /mnt/ai.pcm \n");
#endif
        return 0;
    }

    g_u32FileSaveLimitSize = strtol(argv[1],NULL,0);
    if((g_u32FileSaveLimitSize <=0)||(g_u32FileSaveLimitSize > 500))
    {
        printf("File Save Length Limit %d is not set or larger than 500MB\n", g_u32FileSaveLimitSize);
        return 0;
    }
    else
    {
        printf("File Save Length Limit %d(MB)\n", g_u32FileSaveLimitSize);
    }
    
    if (strcasecmp("null", argv[2]))
    {
        g_pAIFile = fopen(argv[2], "wb");
        if (!g_pAIFile)
        {
            sample_printf("open file %s error!\n", argv[2]);
            return -1;
        }
    }

    HI_SYS_Init();
    Ret = HI_UNF_AI_Init();
    if (HI_SUCCESS != Ret)
    {
        sample_printf("call AiInit failed.\n");
        goto SYS_DEINIT;
    }
    Ret = HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_I2S0,&stAitAttr);
    
    if(HI_SUCCESS != Ret)
    {
        printf("Get Default Ai Attr Failed \n");
        goto AI_DEINIT;
    }
    Ret = HI_UNF_AI_Create(HI_UNF_AI_I2S0, &stAitAttr, &hAi);
    if(HI_SUCCESS != Ret)
    {
        printf("Ai Create Failed \n");
        goto AI_DEINIT;
    }

#if 1   
    //printf("----%s----%d------\n",__FUNCTION__,__LINE__);
    Ret = HI_UNF_AI_SetEnable(hAi, HI_TRUE);
    
    if(HI_SUCCESS != Ret)
    {
        printf("Ai Enable Failed \n");
        goto AI_DESTROY;
    }
#endif

    g_StopThread = HI_FALSE;
    pthread_create(&g_AiThd, HI_NULL, (HI_VOID *)AiTthread, &hAi);
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
    pthread_join(g_AiThd, HI_NULL);

    Ret = HI_UNF_AI_SetEnable(hAi, HI_FALSE);
    if(HI_SUCCESS != Ret)
    {
        printf("Cast Enable Failed \n");
    }

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
