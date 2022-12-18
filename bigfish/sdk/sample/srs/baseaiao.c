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
#include "hi_aef_base.h"
#include "hi_amp.h"


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
    HI_HANDLE hAef;
	
//	HI_AMP_Init();
//	sleep(1);
    
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
    stAitAttr.u32PcmFrameMaxNum = 8;
    //stAitAttr.unAttr.stI2sAttr.stAttr.bMaster = HI_FALSE;
    if(HI_SUCCESS != Ret)
    {
        printf("Get Default Ai Attr Failed \n");
        goto AI_DEINIT;
    }
    
    Ret = HIADP_Snd_RegAefAuthLib();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_RegisterAefAuthLib failed.\n");
        goto AI_DEINIT;
    }
	
    Ret = HI_UNF_AI_Create(HI_UNF_AI_ADC1, &stAitAttr, &hAi);
    if(HI_SUCCESS != Ret)
    {
        printf("Ai Create Failed \n");
        goto AI_DEINIT;
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

    HI_AEF_BASE_OPEN_PARAM_S 	stOpenParams;
    HI_AEF_BASE_BALANCE_CONFIG_S		stBalance;
	HI_BOOL enAbleEffect = HI_TRUE;
	stBalance.bEnable  = HI_TRUE;
	stBalance.u32Balance  = 50;
    HI_AEF_BASE_MASTERVOL_CONFIG_S    	stVol;
	stVol.bEnable = HI_TRUE;
	stVol.f32MasterVol = 0;
    HI_AEF_BASE_GetDefaultOpenParams(&stOpenParams);

    Ret = HI_UNF_SND_CreateAef(HI_UNF_SND_0, HI_UNF_SND_AEF_TYPE_BASE, (HI_VOID *)(&stOpenParams), &hAef);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_CreateAef failed.\n");
        goto TRACK_SLAVE_DESTROY;
    }
    
    
	    
    Ret = HI_UNF_SND_SetAefEnable(hAef, HI_TRUE);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_SetAefEnable failed.\n");
        goto TRACK_SLAVE_DESTROY;
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
	//HI_AMP_SetMute(HI_FALSE);

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

		switch (InputCmd[0])
		{
			case 'm':
			{
				stVol.f32MasterVol = stVol.f32MasterVol-0.125;
				
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_BASE_CONFIG_TYPE_MASTERVOL, &stVol);
				if (Ret != HI_SUCCESS)
				{
					sample_printf("call HI_AEF_BASE_CONFIG_TYPE_MASTERVOL failed.\n");
					break;
				}
				sample_printf("stVol.f32MasterVol:%f\n",stVol.f32MasterVol);
				break;
			}				
			case 'M':	
			{
				stVol.f32MasterVol = stVol.f32MasterVol+0.125;
				
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_BASE_CONFIG_TYPE_MASTERVOL, &stVol);
				if (Ret != HI_SUCCESS)
				{
					sample_printf("call HI_AEF_BASE_CONFIG_TYPE_MASTERVOL failed.\n");
					break;
				}
				sample_printf("stVol.f32MasterVol:%f\n",stVol.f32MasterVol);
				break;
			}
			
			case 'B':
			{
				stBalance.u32Balance += 1;				

				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_BASE_CONFIG_TYPE_BALANCE, &stBalance);
				if (Ret != HI_SUCCESS)
				{
					sample_printf("call HI_AEF_BASE_CONFIG_TYPE_BALANCE failed.\n");
					break;
				}
				sample_printf("++stBalance u32Balance:%d\n",stBalance.u32Balance);
				break;
			}
			
			case 'b':				
			{
				stBalance.u32Balance -= 1;

				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_BASE_CONFIG_TYPE_BALANCE, &stBalance);
				if (Ret != HI_SUCCESS)
				{
					sample_printf("call HI_AEF_BASE_CONFIG_TYPE_BALANCE failed.\n");
					break;
				}
				sample_printf("--stBalance u32Balance:%d\n",stBalance.u32Balance);
				break;
			}	
			case 'Y':
			case 'y':	
			{		
				enAbleEffect = !enAbleEffect;
			    Ret = HI_UNF_SND_SetAefEnable(hAef, enAbleEffect);
			    if (Ret != HI_SUCCESS)
			    {
			        sample_printf("call HI_UNF_SND_SetAefEnable failed.\n");
			        goto TRACK_SLAVE_DESTROY;
			    }  
				sample_printf("HI_UNF_SND_SetAefEnable:%d\n",enAbleEffect);
				break;
			}

			default:
			{
				sample_printf("default\n");
				break;
			}
		}
        
    }

    g_StopThread = HI_TRUE;
    pthread_join(g_VirThd, HI_NULL);

END_FUNC:    
    HI_UNF_AI_SetEnable(hAi, HI_FALSE);

	HI_UNF_SND_SetAefEnable(hAef, HI_FALSE);
	HI_UNF_SND_DestroyAef(hAef);
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

