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
#include "hi_aef_srs.h"


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

    HI_AEF_SRS_OPENPARAM_S stSRSParams;
    HI_AEF_SRS_PARAM_S     stParams;
    HI_AEF_SRS_CONFIG_S    stSRSConfig;
    stSRSParams.pstSRSParam = &stParams;
    stSRSParams.pstSRSConfig = &stSRSConfig;
    HI_AEF_SRS_GetDefaultOpenParam(&stSRSParams);

    Ret = HI_UNF_SND_CreateAef(HI_UNF_SND_0, HI_UNF_SND_AEF_TYPE_SRS3D, (HI_VOID *)(&stSRSParams), &hAef);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_CreateAef failed.\n");
        goto TRACK_SLAVE_DESTROY;
    }

    HI_UNF_SND_SetAefParams(hAef, 0, stSRSParams.pstSRSParam);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_SetAefParams failed.\n");
        goto TRACK_SLAVE_DESTROY;
    }    
    HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_All, stSRSParams.pstSRSConfig);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_SetAefConfig failed.\n");
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
			case 'M':	
			{
				static HI_AEF_SRS_MAINTECH_E tech = HI_AEF_SRS_MAINTECH_NONE;
				tech = tech%6;
				stSRSParams.pstSRSConfig->stMainConfig.enMainTech = (HI_AEF_SRS_MAINTECH_E)tech;				
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_Main, &(stSRSParams.pstSRSConfig->stMainConfig));
			    if (Ret != HI_SUCCESS)
			    {
			        sample_printf("call HI_UNF_SND_SetAefConfig failed.\n");
			        goto TRACK_SLAVE_DESTROY;
			    }
				sample_printf("enMainTech:%d\n",tech);
				tech++;
				break;
			}
			
			case 'v':
			case 'V':				
			{
				stSRSParams.pstSRSConfig->stTVolHDConfig.bEnable = !stSRSParams.pstSRSConfig->stTVolHDConfig.bEnable ;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_TVolHD, &(stSRSParams.pstSRSConfig->stTVolHDConfig));
				sample_printf("stTVolHDConfig enable:%d\n",stSRSParams.pstSRSConfig->stTVolHDConfig.bEnable);
				break;
			}
			
			case 'D':
			case 'd':				
			{
				stSRSParams.pstSRSConfig->stTruDiagConfig.bEnable = !stSRSParams.pstSRSConfig->stTruDiagConfig.bEnable;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_TruDiag, &(stSRSParams.pstSRSConfig->stTruDiagConfig));
				sample_printf("stTruDiagConfig enable:%d\n",stSRSParams.pstSRSConfig->stTruDiagConfig.bEnable);
				break;
			}	

			case 'B':
			case 'b':				
			{
				stSRSParams.pstSRSConfig->stCommonConfig.bTBHDEnable= !stSRSParams.pstSRSConfig->stCommonConfig.bTBHDEnable;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_Comm, &(stSRSParams.pstSRSConfig->stCommonConfig));
				sample_printf("stTBHD enable:%d\n",stSRSParams.pstSRSConfig->stCommonConfig.bTBHDEnable);
				break;
			}	

			case 'H':
			case 'h':	
			{
				if (stSRSParams.pstSRSConfig->stCommonConfig.f32TBHDLevel > 1) stSRSParams.pstSRSConfig->stCommonConfig.f32TBHDLevel = 0;
				stSRSParams.pstSRSConfig->stCommonConfig.f32TBHDLevel +=0.1;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_Comm, &(stSRSParams.pstSRSConfig->stCommonConfig));
				sample_printf("f32TBHDLevel :%f\n",stSRSParams.pstSRSConfig->stCommonConfig.f32TBHDLevel);
				break;
			}
		
			case 'T':
			case 't':				
			{				
				if (stSRSParams.pstSRSConfig->stCC3DConfig.f32TruSurLevel > 1) stSRSParams.pstSRSConfig->stCC3DConfig.f32TruSurLevel = 0;
				stSRSParams.pstSRSConfig->stCC3DConfig.f32TruSurLevel += 0.1;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_CC3D, &(stSRSParams.pstSRSConfig->stCC3DConfig));
				sample_printf("f32TruSurLevel:%f\n",stSRSParams.pstSRSConfig->stCC3DConfig.f32TruSurLevel);
				break;
			}

			case 'E':
			case 'e':				
			{				
				stSRSParams.pstSRSConfig->stGEQConfig.bEnable = !stSRSParams.pstSRSConfig->stGEQConfig.bEnable;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_GEQ, &(stSRSParams.pstSRSConfig->stGEQConfig));
				sample_printf("EQ enable:%d\n",stSRSParams.pstSRSConfig->stGEQConfig.bEnable);
				break;
			}

			case 'f':
			case 'F':				
			{		
				int i;
				for (i = 0;i < 5; i++)
				{
					stSRSParams.pstSRSConfig->stGEQConfig.f32bgain[i] += 1; 
					if (stSRSParams.pstSRSConfig->stGEQConfig.f32bgain[i]>15)
						stSRSParams.pstSRSConfig->stGEQConfig.f32bgain[i] = -15;
				}
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_GEQ, &(stSRSParams.pstSRSConfig->stGEQConfig));
				for (i = 0;i < 5; i++)
				{
					sample_printf("EQ band[%d], value:%f\n",i,stSRSParams.pstSRSConfig->stGEQConfig.f32bgain[i]);
				}
				
				break;
			}

			case 'p':
			case 'P':				
			{		
				stSRSParams.pstSRSConfig->stHPFConfig.bEnable = !stSRSParams.pstSRSConfig->stHPFConfig.bEnable;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_HPF, &(stSRSParams.pstSRSConfig->stHPFConfig));
				sample_printf("HPF Enable:%d\n",stSRSParams.pstSRSConfig->stHPFConfig.bEnable);
				break;
			}

			case 'L':
			case 'l':				
			{		
				stSRSParams.pstSRSConfig->stHdLmtConfig.bEnable = !stSRSParams.pstSRSConfig->stHdLmtConfig.bEnable;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_HPF, &(stSRSParams.pstSRSConfig->stHdLmtConfig));
				sample_printf("HDLmt Enable:%d\n",stSRSParams.pstSRSConfig->stHdLmtConfig.bEnable);
				break;
			}			

			case 'A':
			case 'a':				
			{		
				stSRSParams.pstSRSConfig->stAEQConfig.bEnable = !stSRSParams.pstSRSConfig->stAEQConfig.bEnable;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_AEQ, &(stSRSParams.pstSRSConfig->stAEQConfig));
				sample_printf("AEQ Enable:%d\n",stSRSParams.pstSRSConfig->stAEQConfig.bEnable);
				break;
			}	

			case 'S':
			case 's':				
			{		
				stSRSParams.pstSRSConfig->stMvolConfig.bEnable = HI_TRUE;
				stSRSParams.pstSRSConfig->stMvolConfig.bMute = !stSRSParams.pstSRSConfig->stMvolConfig.bMute; 
				if (stSRSParams.pstSRSConfig->stMvolConfig.u32VolStep < 100)
					stSRSParams.pstSRSConfig->stMvolConfig.u32VolStep += 5; 
				else
					stSRSParams.pstSRSConfig->stMvolConfig.u32VolStep = 0;
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_Mvol, &(stSRSParams.pstSRSConfig->stMvolConfig));
				sample_printf("MVOL mute:%d, u32VolStep:%d\n",
					stSRSParams.pstSRSConfig->stMvolConfig.bMute,
					stSRSParams.pstSRSConfig->stMvolConfig.u32VolStep);
				break;
			}

			case 'n':
			case 'N':				
			{		
				//*SRS Mute ?TD¡ì*
				stSRSParams.pstSRSConfig->stMvolConfig.u32VolStep = 100;
				stSRSParams.pstSRSConfig->stMvolConfig.bEnable = HI_TRUE;
				sample_printf("be,MVOL balance:%d, u32VolStep:%d\n",
					stSRSParams.pstSRSConfig->stMvolConfig.s32LRBalance,
					stSRSParams.pstSRSConfig->stMvolConfig.u32VolStep);
				
				#if 1
				if (stSRSParams.pstSRSConfig->stMvolConfig.s32LRBalance < 11)
					stSRSParams.pstSRSConfig->stMvolConfig.s32LRBalance += 1; 
				else
					stSRSParams.pstSRSConfig->stMvolConfig.s32LRBalance = -10;
				#endif
				stSRSParams.pstSRSConfig->stMvolConfig.bMute = !stSRSParams.pstSRSConfig->stMvolConfig.bMute;
				
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_Mvol, &(stSRSParams.pstSRSConfig->stMvolConfig));

				sample_printf("af,MVOL balance:%d, mute:%d\n",
					stSRSParams.pstSRSConfig->stMvolConfig.s32LRBalance,
					stSRSParams.pstSRSConfig->stMvolConfig.bMute);
				break;
			}

			case 'C':
			case 'c':				
			{				
				stSRSParams.pstSRSConfig->stToneConfig.bEnable = HI_TRUE;

				if (stSRSParams.pstSRSConfig->stToneConfig.s32BassGain < 12)
				{
					stSRSParams.pstSRSConfig->stToneConfig.s32BassGain += 1; 
					stSRSParams.pstSRSConfig->stToneConfig.s32TrebleGain+= 1; 
				}
				else
				{
					stSRSParams.pstSRSConfig->stToneConfig.s32BassGain = -12;
					stSRSParams.pstSRSConfig->stToneConfig.s32TrebleGain = -12;
				}
				
				HI_UNF_SND_SetAefConfig(hAef, HI_AEF_SRS_CONFIG_TYPE_Tone, &(stSRSParams.pstSRSConfig->stToneConfig));
				
				sample_printf("af,Tone  :%d, Treble:%d\n",
					stSRSParams.pstSRSConfig->stToneConfig.s32BassGain,
					stSRSParams.pstSRSConfig->stToneConfig.s32TrebleGain);
			}
			break;

			default:
			{
				sample_printf("default\n");
				break;
			}
		}
        
    }

    g_StopThread = HI_TRUE;
    pthread_join(g_VirThd, HI_NULL);
    
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

