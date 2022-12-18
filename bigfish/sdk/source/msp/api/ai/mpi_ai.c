/*****************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_aenc.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01      
*
*****************************************************************************/


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <pthread.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_module.h"
#include "hi_mpi_mem.h"
#include "hi_drv_struct.h"
#include "hi_error_mpi.h"

#include "hi_mpi_ai.h"
#include "drv_ai_ioctl.h"

#include "hi_drv_ao.h"
#include "hi_mpi_ao.h"
#include "hi_drv_aenc.h"
#include "hi_mpi_aenc.h"

#define AI_MAX_DST         (4)
#define AI_SLEEP_TIME_MS   (5)
#define AI_CHECK_DELAY_SLEEP_TIME_MS   (1)
#define AO_TRACK_DELAY_FOR_AI_TIME 20
#define U32_MAX_VALUE 0xffffffff

typedef struct hiAI_MPISTATE_S
{ 
    HI_HANDLE           hAi;
    HI_BOOL             bDataFlag; //is data valid or not

    HI_HANDLE           hSlaTrack;   //ai->ao by aip buff
	HI_BOOL				bNeedStart;	//start track
    
    HI_U32              u32DstNum;
    HI_HANDLE           hDst[AI_MAX_DST];
    
    HI_BOOL             AiThreadRun;
    pthread_t           AiDataThdInst;  /* run handle of ai thread */
    pthread_t           AiTrackThdInst;  /* run handle of start track */
    pthread_mutex_t     *pAiThreadMutex;     /*mutex for data safety use*/
}AI_MPISTATE_S;

typedef struct hiAI_MPIRESOURCE_S
{ 
    AI_MPISTATE_S       *pstAI_S[AI_MAX_TOTAL_NUM];
}AI_MPIRESOURCE_S;

static HI_S32 g_s32AIFd = -1;
static const HI_CHAR g_acAIDevName[] = "/dev/" UMAP_DEVNAME_AI;
static AI_MPIRESOURCE_S g_AiRes;

void AI_ThreadMutex_Lock(pthread_mutex_t *ss)
{
    pthread_mutex_lock(ss);
}

void Ai_ThreadMutex_UnLock(pthread_mutex_t *ss)
{
    pthread_mutex_unlock(ss);
}

static HI_S32 AI_ChnAcquireFrame(HI_HANDLE hAI, HI_UNF_AO_FRAMEINFO_S *pstFrame)
{
    HI_S32 s32Ret;
    AI_Frame_Param_S stAiGetFrame;
    AI_Buf_Param_S stAiBufInfo;

    stAiBufInfo.hAi = hAI;
    stAiGetFrame.hAi = hAI;

    s32Ret = ioctl(g_s32AIFd, CMD_AI_GETBUFINFO, &stAiBufInfo);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("\n GET AI BUF_INFO s32Ret=0x%x Failed \n", s32Ret);  
        return s32Ret;
    }
    
    s32Ret = ioctl(g_s32AIFd, CMD_AI_ACQUIREFRAME, &stAiGetFrame);
    if(HI_SUCCESS != s32Ret)
    {
        HI_WARN_AI("AI GetFrame Failed 0x%x \n", s32Ret);
        return s32Ret;
    }

    memcpy(pstFrame, &stAiGetFrame.stAiFrame, sizeof(HI_UNF_AO_FRAMEINFO_S));
    
    pstFrame->ps32PcmBuffer = (HI_S32 *)(stAiBufInfo.stAiBuf.u32UserVirBaseAddr);

    return HI_SUCCESS;
}

static HI_S32 AI_ChnReleaseFrame(HI_HANDLE hAI, HI_UNF_AO_FRAMEINFO_S *pstFrame)
{
    HI_S32 s32Ret;
    AI_Frame_Param_S stAiRleFrame;

    stAiRleFrame.hAi = hAI;
    
    memcpy(&stAiRleFrame.stAiFrame, pstFrame, sizeof(HI_UNF_AO_FRAMEINFO_S));

    s32Ret = ioctl(g_s32AIFd, CMD_AI_RELEASEFRAME, &stAiRleFrame);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("AI ReleaseFrame Failed 0x%x \n", s32Ret);  
    }

    return s32Ret;
}

HI_VOID *AI_TrackThread(HI_VOID *Arg)
{
    HI_S32 s32Ret;
    AI_MPISTATE_S *pstAiState = (AI_MPISTATE_S*)Arg;
    HI_BOOL bEnable;
    HI_U32 DelayMs = 0;
    HI_S32 s32Flag = 0;
    HI_U32 u32StartSysTime = 0;
    HI_U32 u32EndSysTime = 0;
    HI_U32 u32DelayTime = 0;
    HI_UNF_AI_DELAY_S stDelayCompensation;
    memset(&stDelayCompensation, 0, sizeof(HI_UNF_AI_DELAY_S));
    
    while((pstAiState->AiThreadRun))
    {
        AI_ThreadMutex_Lock(pstAiState->pAiThreadMutex);
        if(HI_INVALID_HANDLE != pstAiState->hSlaTrack)
        {
            s32Ret = HI_MPI_AI_GetEnable(pstAiState->hAi, &bEnable);
            if((HI_SUCCESS == s32Ret) && (HI_TRUE == bEnable))
            {
				if(HI_TRUE == pstAiState->bNeedStart)	// SetEnable/Attach called
				{
					if(0 == s32Flag)
                        HI_SYS_GetTimeStampMs(&u32StartSysTime);

					s32Flag = 1;
					
                    HI_SYS_GetTimeStampMs(&u32EndSysTime);
                    if(u32EndSysTime >= u32StartSysTime)
                    {
                        u32DelayTime = u32EndSysTime - u32StartSysTime;
                    }
                    else
                    {
                        u32DelayTime = (U32_MAX_VALUE - u32StartSysTime )+ (u32EndSysTime + 1);
                    }
					s32Ret = HI_MPI_AO_Track_GetDelayMs(pstAiState->hSlaTrack, &DelayMs);
                    s32Ret |= HI_MPI_AI_GetDelay(pstAiState->hAi, &stDelayCompensation);
                    if(((HI_SUCCESS == s32Ret) && (DelayMs + stDelayCompensation.u32DelayMs >= AO_TRACK_DELAY_FOR_AI_TIME)) 
                        || ((DelayMs + stDelayCompensation.u32DelayMs + u32DelayTime) >= AO_TRACK_DELAY_FOR_AI_TIME))
                    {
					
						s32Ret = HI_MPI_AO_Track_Start(pstAiState->hSlaTrack);
						if (s32Ret != HI_SUCCESS)
                        {
                           HI_ERR_AO("call HI_MPI_AO_Track_Start failed.\n");			  
                        }
                        HI_INFO_AO("HI_MPI_AO_Track_Start make bNeedStart HI_FALSE\n");
                        pstAiState->bNeedStart = HI_FALSE;
                    }
                }
				else
					s32Flag = 0;
            }
            else
				s32Flag = 0;
        }
        else
			s32Flag = 0;
			
        Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
        usleep(AI_CHECK_DELAY_SLEEP_TIME_MS*1000);
    }
    
    return HI_NULL;
}

HI_VOID *AI_DataThread(HI_VOID *Arg)
{
    HI_S32 s32Ret;
    HI_U32 i;
    AI_MPISTATE_S *pstAiState = (AI_MPISTATE_S*)Arg;
    HI_UNF_AO_FRAMEINFO_S  stAiFrame;
    HI_UNF_AO_FRAMEINFO_S *pstAiFrame = &stAiFrame;

    while((pstAiState->AiThreadRun))
    {
        AI_ThreadMutex_Lock(pstAiState->pAiThreadMutex);
        if((HI_FALSE == pstAiState->bDataFlag) && (pstAiState->u32DstNum))
        {
            s32Ret = AI_ChnAcquireFrame(pstAiState->hAi, pstAiFrame);
            if(HI_SUCCESS == s32Ret)
            {
                pstAiState->bDataFlag = HI_TRUE;
            }
            else
            {
                HI_WARN_AI("call HI_MPI_AI_AcquireFrame failed!\n");
                Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
                usleep(AI_SLEEP_TIME_MS*1000);
                continue;
            }
        }
        
        if((pstAiState->u32DstNum) && (HI_TRUE == pstAiState->bDataFlag))
        {
            if(HI_ID_AO == (pstAiState->hDst[0])>>16)
            {
                s32Ret = HI_MPI_AO_Track_SendData(pstAiState->hDst[0], pstAiFrame);
            }
            else
            {
                s32Ret = HI_MPI_AENC_SendBuffer(pstAiState->hDst[0], pstAiFrame);
            }
            
            if (HI_SUCCESS == s32Ret)
            {
                pstAiState->bDataFlag = HI_FALSE;
                if(1<pstAiState->u32DstNum)
                {
                    for(i=1; i<pstAiState->u32DstNum; i++)
                    {
                        if(HI_ID_AO == (pstAiState->hDst[i])>>16)
                        {
                            (HI_VOID)HI_MPI_AO_Track_SendData(pstAiState->hDst[i], pstAiFrame);
                        }
                        else
                        {
                            (HI_VOID)HI_MPI_AENC_SendBuffer(pstAiState->hDst[i], pstAiFrame);
                        }
                    }
                }
                
                s32Ret = AI_ChnReleaseFrame(pstAiState->hAi, pstAiFrame);
            }
            else
            {
                pstAiState->bDataFlag = HI_TRUE;
            }
        }
        Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
        usleep(AI_SLEEP_TIME_MS*1000);
    }


    return HI_NULL;
}

HI_S32 AI_Attach(HI_HANDLE hAI, HI_HANDLE hDst)
{
    HI_S32 s32Ret;
    HI_U32 i;
    AI_MPISTATE_S *pstAiState;

    CHECK_AI_ID(hAI);
    if (HI_INVALID_HANDLE == hDst)
    {
        HI_ERR_AI("para hDst is invalid.\n");
        return HI_ERR_AI_INVALID_PARA;
    }

    if((HI_ID_AO != (hDst>>16)) && (HI_ID_AENC != (hDst>>16)))
    {
        HI_ERR_AI("para hDst is invalid, just support attach sound_track or aenc.\n");
        return HI_ERR_AI_INVALID_PARA;
    }

    for(i=0; i<AI_MAX_TOTAL_NUM; i++)
    {
        if((HI_NULL != g_AiRes.pstAI_S[i]) && (hAI == g_AiRes.pstAI_S[i]->hAi))
            break;
    }

    if(AI_MAX_TOTAL_NUM == i)
    {
        HI_ERR_AI("AI chn not open\n");  
        return HI_FAILURE;
    }
    pstAiState = g_AiRes.pstAI_S[i];

    if(( HI_ID_AO == hDst>>16) && (AO_MAX_REAL_TRACK_NUM > (hDst&0xff)))
    {
        if(HI_INVALID_HANDLE != pstAiState->hSlaTrack)
        {
            if(hDst == pstAiState->hSlaTrack)
            {
                return HI_SUCCESS;
            }
            else
            {
                HI_ERR_AI("Ai can not attach more than one slave track!\n");
                return HI_FAILURE;
            }
        }
        
        s32Ret =  HI_MPI_AO_Track_AttachAi(hAI, hDst);
        if (HI_SUCCESS == s32Ret)
        {
            pstAiState->hSlaTrack = hDst;
			HI_INFO_AI("pstAiState->bNeedStart=%d .\n",pstAiState->bNeedStart);
			pstAiState->bNeedStart = HI_TRUE;
        }
        
        return s32Ret;
    }

    AI_ThreadMutex_Lock(pstAiState->pAiThreadMutex);

    for (i=0; i<AI_MAX_DST; i++)
    {
        if (pstAiState->hDst[i] == hDst)
        {
            Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
            
            return HI_SUCCESS;
        }
    }

    for (i=0; i<AI_MAX_DST; i++)
    {
        if (HI_INVALID_HANDLE == pstAiState->hDst[i])
        {
            break;
        }
    }

    if(AI_MAX_DST == i)
    {
        HI_ERR_AI("AI has attached max dst.\n");
        Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
        return HI_FAILURE;        
    }

    pstAiState->hDst[i] = hDst;
    pstAiState->u32DstNum++;

    
    Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
    return HI_SUCCESS;
}


HI_S32 AI_Detach(HI_HANDLE hAI, HI_HANDLE hDst)
{
    HI_U32 i;
    HI_S32 s32Ret;
    AI_MPISTATE_S *pstAiState;

    CHECK_AI_ID(hAI);

    if (HI_INVALID_HANDLE == hDst)
    {
        HI_ERR_AI("para hDst is invalid.\n");
        return HI_ERR_AI_INVALID_PARA;
    }

    if((HI_ID_AO != (hDst>>16)) && (HI_ID_AENC != (hDst>>16)))
    {
        HI_ERR_AI("para hDst is invalid, just support attach sound_track or aenc.\n");
        return HI_ERR_AI_INVALID_PARA;
    }
    
    for(i=0; i<AI_MAX_TOTAL_NUM; i++)
    {
        if((HI_NULL != g_AiRes.pstAI_S[i]) && (hAI == g_AiRes.pstAI_S[i]->hAi))
            break;
    }
    
    if(AI_MAX_TOTAL_NUM == i)
    {
        HI_ERR_AI("AI chn not open\n");  
        return HI_FAILURE;
    }
    
    pstAiState = g_AiRes.pstAI_S[i];
    
    if(( HI_ID_AO == hDst>>16) && (AO_MAX_REAL_TRACK_NUM > (hDst&0xff)))
    {
        if(hDst == pstAiState->hSlaTrack)
        {
            s32Ret = HI_MPI_AO_Track_DetachAi(hAI, hDst);
            if(HI_SUCCESS == s32Ret)
            {
                pstAiState->hSlaTrack = HI_INVALID_HANDLE;
            }
            return s32Ret;
        }
        else
        {
            HI_ERR_AI("This track is not attach Ai,can not detach!\n");
            return HI_FAILURE;
        }
    }
    
    AI_ThreadMutex_Lock(pstAiState->pAiThreadMutex);

    for (i=0; i<pstAiState->u32DstNum; i++)
    {
        if (pstAiState->hDst[i] == hDst)
        {
            break;
        }
    }
    
    if (i == pstAiState->u32DstNum)
    {
        HI_ERR_AI("this track is not attached, can not detach.\n");
        Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
        return HI_FAILURE;
    }
    
    pstAiState->hDst[i] = pstAiState->hDst[pstAiState->u32DstNum - 1];
    pstAiState->hDst[pstAiState->u32DstNum - 1] = HI_INVALID_HANDLE;
    pstAiState->u32DstNum--;

    Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
    return HI_SUCCESS;
}

    
HI_S32 HI_MPI_AI_Init(HI_VOID)
{
    HI_U32 i;
    if (g_s32AIFd < 0)
    {
        g_s32AIFd = open(g_acAIDevName, O_RDWR, 0);
        if (g_s32AIFd < 0)    
        {
            HI_FATAL_AI("OpenAIDevice err\n");
            g_s32AIFd = -1;
            return HI_ERR_AI_NOT_INIT;
        }
        for(i=0; i<AI_MAX_TOTAL_NUM; i++)
        {
            g_AiRes.pstAI_S[i] = NULL;
        }
    }    
    return HI_SUCCESS;
}

HI_S32   HI_MPI_AI_DeInit(HI_VOID)
{
    if(g_s32AIFd > 0)  
    {
        close(g_s32AIFd);
        g_s32AIFd = -1;
    }

    return HI_SUCCESS;
}

HI_S32   HI_MPI_AI_GetDefaultAttr(HI_UNF_AI_E enAiPort, HI_UNF_AI_ATTR_S *pstAttr)
{
    HI_S32 s32Ret;
    AI_GetDfAttr_Param_S stAiGetDfAttr;

    CHECK_AI_CREATE(g_s32AIFd);
    CHECK_AI_NULL_PTR(pstAttr);
	CHECK_AI_PORT(enAiPort);
    stAiGetDfAttr.enAiPort = enAiPort;
    
    s32Ret =  ioctl(g_s32AIFd, CMD_AI_GEtDEFAULTATTR, &stAiGetDfAttr);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("AI GetDfAttr Failed 0x%x \n", s32Ret);
    }
	else
	{
        memcpy(pstAttr, &stAiGetDfAttr.stAttr, sizeof(HI_UNF_AI_ATTR_S));
	}

    return s32Ret;
}

HI_S32 HI_MPI_AI_SetAttr(HI_HANDLE hAI, HI_UNF_AI_ATTR_S *pstAttr)
{
    HI_S32 s32Ret;
    AI_Attr_Param_S stAiSetAttr;
    AI_MPISTATE_S *pstAiState;

    CHECK_AI_ID(hAI);
    CHECK_AI_NULL_PTR(pstAttr);

    stAiSetAttr.hAi = hAI;

    memcpy(&stAiSetAttr.stAttr, pstAttr, sizeof(HI_UNF_AI_ATTR_S));
    
    s32Ret = ioctl(g_s32AIFd, CMD_AI_SETATTR, &stAiSetAttr);
    
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("AI SetAttr Failed 0x%x \n", s32Ret); 
		return s32Ret;
    }

	pstAiState = g_AiRes.pstAI_S[hAI&AI_CHNID_MASK];
	if(HI_NULL != pstAiState && HI_INVALID_HANDLE != pstAiState->hSlaTrack)
	{
		HI_HANDLE hTrack = pstAiState->hSlaTrack;
		//detach track for new ai attr
		HI_INFO_AI("AI_Detach Track\n");
		s32Ret = AI_Detach(hAI, pstAiState->hSlaTrack);
		if(HI_SUCCESS != s32Ret)
		{
			HI_ERR_AI("AI_Detach Failed 0x%x \n", s32Ret); 
		}

        HI_INFO_AI("HI_MPI_AO_Track_Stop called\n");
		s32Ret = HI_MPI_AO_Track_Stop(hTrack);
		if (s32Ret != HI_SUCCESS)
		{
			HI_ERR_AO("call HI_MPI_AO_Track_Stop failed.\n");			 
		}

        HI_INFO_AI("AI_Detach Track\n");
		s32Ret = AI_Attach(hAI, hTrack);
		if(HI_SUCCESS != s32Ret)
		{
			HI_ERR_AI("AI_Attach Failed 0x%x \n", s32Ret); 
		}
	}
    
    return s32Ret;
}

HI_S32 HI_MPI_AI_GetAttr(HI_HANDLE hAI, HI_UNF_AI_ATTR_S *pstAttr)
{
    
    HI_S32 s32Ret;
    AI_Attr_Param_S stAiGetAttr;

    CHECK_AI_ID(hAI);
    CHECK_AI_NULL_PTR(pstAttr);

    stAiGetAttr.hAi = hAI;
    
    s32Ret = ioctl(g_s32AIFd, CMD_AI_GETATTR, &stAiGetAttr);
    
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("AI GetAttr Failed 0x%x \n", s32Ret); 
    }
    
    memcpy(pstAttr, &stAiGetAttr.stAttr, sizeof(HI_UNF_AI_ATTR_S));
    
    return s32Ret;
    
}

HI_S32 HI_MPI_AI_Create(HI_UNF_AI_E enAiPort, HI_UNF_AI_ATTR_S *pstAttr, HI_HANDLE *phandle)
{
    HI_S32 s32Ret;
    HI_U32 i;
    AI_MPISTATE_S *pstAiState;

    AI_Create_Param_S stAiParam;
    AI_Buf_Param_S stAiBufInfo;

    CHECK_AI_PORT(enAiPort);
    CHECK_AI_NULL_PTR(pstAttr);
	CHECK_AI_SAMPLERATE(pstAttr->enSampleRate);
    CHECK_AI_NULL_PTR(phandle);
    
    stAiParam.enAiPort = enAiPort;
    stAiParam.bAlsaUse = HI_FALSE;
    stAiParam.pAlsaPara = NULL;

    memcpy(&stAiParam.stAttr, pstAttr, sizeof(HI_UNF_AI_ATTR_S));
    
    s32Ret = ioctl(g_s32AIFd, CMD_AI_CREATE, &stAiParam);
    
    if(HI_SUCCESS == s32Ret)
    {
        *phandle = stAiParam.hAi;
    }
    else
    {
        return s32Ret;
    }

    stAiBufInfo.hAi = stAiParam.hAi;

    s32Ret = ioctl(g_s32AIFd, CMD_AI_GETBUFINFO, &stAiBufInfo);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("GET AI BUF_INFO s32Ret=0x%x Failed \n", s32Ret);  
        goto ERR_CREAT;
    }   

    stAiBufInfo.stAiBuf.u32UserVirBaseAddr = (HI_S32)HI_MEM_Map(stAiBufInfo.stAiBuf.u32PhyBaseAddr, stAiBufInfo.stAiBuf.u32Size);

    s32Ret = ioctl(g_s32AIFd, CMD_AI_SETBUFINFO, &stAiBufInfo);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("SET AI BUF_INFO Failed 0x%x\n", s32Ret);  
        goto ERR_MMAP;
    }

    for(i=0; i<AI_MAX_TOTAL_NUM; i++)
    {
        if(NULL == g_AiRes.pstAI_S[i])
            break;
    }

    if(AI_MAX_TOTAL_NUM == i)
    {
        HI_ERR_AI("too many Ai chn\n");  
        goto ERR_MMAP;
    }
    
    g_AiRes.pstAI_S[i] = (AI_MPISTATE_S *)HI_MALLOC(HI_ID_AI, sizeof(AI_MPISTATE_S));
    if(HI_NULL == g_AiRes.pstAI_S[i])
    {
        goto ERR_MMAP;
    }
    
    pstAiState = g_AiRes.pstAI_S[i];

    pstAiState->pAiThreadMutex = (pthread_mutex_t *)HI_MALLOC(HI_ID_AI, sizeof(pthread_mutex_t));
    if (HI_NULL == pstAiState->pAiThreadMutex)
    {
        goto ERR_KFREE_STATE;
    }
    (HI_VOID)pthread_mutex_init(pstAiState->pAiThreadMutex, NULL);
    
    pstAiState->hAi= stAiParam.hAi;
    pstAiState->bDataFlag = HI_FALSE;
    pstAiState->u32DstNum = 0;
    pstAiState->AiThreadRun = HI_TRUE;
    pstAiState->hSlaTrack = HI_INVALID_HANDLE;

    for (i=0; i<AI_MAX_DST; i++)
    {
        pstAiState->hDst[i] = HI_INVALID_HANDLE;
    }

    s32Ret = pthread_create(&pstAiState->AiDataThdInst, HI_NULL, AI_DataThread, (HI_VOID *)pstAiState);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("Ai pthread_create failed!\n");  
        goto ERR_KFREE_MUTEX;
    }
    
    s32Ret = pthread_create(&pstAiState->AiTrackThdInst, HI_NULL, AI_TrackThread, (HI_VOID *)pstAiState);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("Ai pthread_create failed!\n");  
        goto ERR_DESTROY_DATATHREAD;
    }
    

    return s32Ret;

ERR_DESTROY_DATATHREAD:
    pstAiState->AiThreadRun = HI_FALSE;
    //AI_ThreadMutex_Lock(pstAiState->pAiThreadMutex);
    (HI_VOID)pthread_join(pstAiState->AiDataThdInst, HI_NULL);
    //Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
ERR_KFREE_MUTEX:
    (HI_VOID)pthread_mutex_destroy(pstAiState->pAiThreadMutex);
    HI_FREE(HI_ID_AI, (HI_VOID*)(pstAiState->pAiThreadMutex));
ERR_KFREE_STATE:
    HI_FREE(HI_ID_AI, (HI_VOID*)(pstAiState));
ERR_MMAP:
    HI_MEM_Unmap((HI_VOID *)stAiBufInfo.stAiBuf.u32PhyBaseAddr);
ERR_CREAT:
    ioctl(g_s32AIFd, CMD_AI_DESTROY, &stAiParam);
    return s32Ret;
}

HI_S32 HI_MPI_AI_Destroy(HI_HANDLE hAI)
{
    HI_S32 s32Ret;
    HI_U32 i;
    AI_Buf_Param_S stAiBufInfo;
    AI_MPISTATE_S *pstAiState;
    
    CHECK_AI_ID(hAI);

    stAiBufInfo.hAi = hAI;

    for(i=0; i<AI_MAX_TOTAL_NUM; i++)
    {
        if((HI_NULL != g_AiRes.pstAI_S[i]) && (hAI == g_AiRes.pstAI_S[i]->hAi))
            break;
    }
    
    if(AI_MAX_TOTAL_NUM == i)
    {
        HI_ERR_AI("This AI chn is not open!\n");  
        return HI_FAILURE;
    }
    
    pstAiState = g_AiRes.pstAI_S[i];

    //AI_ThreadMutex_Lock(pstAiState->pAiThreadMutex);
    
    pstAiState->AiThreadRun = HI_FALSE;
    (HI_VOID)pthread_join(pstAiState->AiTrackThdInst, HI_NULL);    
    (HI_VOID)pthread_join(pstAiState->AiDataThdInst, HI_NULL);
    
    //Ai_ThreadMutex_UnLock(pstAiState->pAiThreadMutex);
    
    (HI_VOID)pthread_mutex_destroy(pstAiState->pAiThreadMutex);
    
    HI_FREE(HI_ID_AI, (HI_VOID*)(pstAiState->pAiThreadMutex));
    HI_FREE(HI_ID_AI, (HI_VOID*)(pstAiState));
    g_AiRes.pstAI_S[i] = HI_NULL;

    s32Ret = ioctl(g_s32AIFd, CMD_AI_GETBUFINFO, &stAiBufInfo);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("\n GET AI BUF_INFO s32Ret=0x%x Failed \n", s32Ret);
        return s32Ret;
    }
    else
    {
        HI_MEM_Unmap((HI_VOID *)stAiBufInfo.stAiBuf.u32UserVirBaseAddr);
    }

    return  ioctl(g_s32AIFd, CMD_AI_DESTROY, &hAI);
}

HI_S32 HI_MPI_AI_SetEnable(HI_HANDLE hAI, HI_BOOL bEnable)
{
    HI_S32 s32Ret;
    AI_MPISTATE_S *pstAiState;
    AI_Enable_Param_S stAiEnable;
    
    CHECK_AI_ID(hAI);
 
    stAiEnable.hAi = hAI;
    stAiEnable.bAiEnable = bEnable;

    s32Ret = ioctl(g_s32AIFd, CMD_AI_SETENABLE, &stAiEnable);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("ENABLE AI Failed 0x%x \n", s32Ret);  
    }   
	else
	{
		if(HI_TRUE == bEnable)
        {
	        HI_INFO_AI("pstAiState->bNeedStart = HI_TRUE\n");  
			pstAiState = g_AiRes.pstAI_S[hAI&AI_CHNID_MASK];
			pstAiState->bNeedStart = HI_TRUE;
        }    
	}
    return s32Ret;
}

HI_S32 HI_MPI_AI_GetEnable(HI_HANDLE hAI, HI_BOOL *pbEnable)
{
    HI_S32 s32Ret;
    AI_Enable_Param_S stAiEnable;
    
    CHECK_AI_ID(hAI);
    CHECK_AI_NULL_PTR(pbEnable);
 
    stAiEnable.hAi = hAI;

    s32Ret = ioctl(g_s32AIFd, CMD_AI_GETENABLE, &stAiEnable);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("Get AI Enable Failed 0x%x \n", s32Ret);  
    }
    else
    {
        *pbEnable = stAiEnable.bAiEnable;
    }
    
    return s32Ret;
}


HI_S32 HI_MPI_AI_AcquireFrame(HI_HANDLE hAI, HI_UNF_AO_FRAMEINFO_S *pstFrame)
{
    HI_U32 i;
    AI_MPISTATE_S *pstAiState;

    CHECK_AI_ID(hAI);
    CHECK_AI_NULL_PTR(pstFrame);

    for(i=0; i<AI_MAX_TOTAL_NUM; i++)
    {
        if((HI_NULL != g_AiRes.pstAI_S[i]) && (hAI == g_AiRes.pstAI_S[i]->hAi))
            break;
    }

    if(AI_MAX_TOTAL_NUM != i)
    {
        pstAiState = g_AiRes.pstAI_S[i];

        if((HI_INVALID_HANDLE != pstAiState->hDst[0]) || (HI_INVALID_HANDLE != pstAiState->hSlaTrack))
        {
            HI_ERR_AI("Aenc or Track attach this Ai chn,can not acquire frame!\n");  
            return  HI_FAILURE;
        }
    }
    
    return AI_ChnAcquireFrame(hAI, pstFrame);
}

HI_S32 HI_MPI_AI_ReleaseFrame(HI_HANDLE hAI, HI_UNF_AO_FRAMEINFO_S *pstFrame)
{
    HI_U32 i;
    AI_MPISTATE_S *pstAiState;

    CHECK_AI_ID(hAI);
    CHECK_AI_NULL_PTR(pstFrame);

    for(i=0; i<AI_MAX_TOTAL_NUM; i++)
    {
        if((HI_NULL != g_AiRes.pstAI_S[i]) && (hAI == g_AiRes.pstAI_S[i]->hAi))
            break;
    }

    if(AI_MAX_TOTAL_NUM != i)
    {
        pstAiState = g_AiRes.pstAI_S[i];

        if((HI_INVALID_HANDLE != pstAiState->hDst[0]) || (HI_INVALID_HANDLE != pstAiState->hSlaTrack))
        {
            HI_WARN_AI("Aenc or Track attach this Ai chn,can not release frame!\n");  
            return  HI_FAILURE;
        }
    }

    return AI_ChnReleaseFrame(hAI, pstFrame);
}

HI_S32 HI_MPI_AI_Attach(HI_HANDLE hAI, HI_HANDLE hDst)
{
	return AI_Attach(hAI, hDst);
}

HI_S32 HI_MPI_AI_Detach(HI_HANDLE hAI, HI_HANDLE hDst)
{
    return AI_Detach(hAI, hDst);    
}

HI_S32 HI_MPI_AI_SetDelay(HI_HANDLE hAI, const HI_UNF_AI_DELAY_S *pstDelay)
{
    HI_S32 s32Ret;
    AI_DelayComps_Param_S stDelayCompsParam;
    
    CHECK_AI_ID(hAI);
    CHECK_AI_NULL_PTR(pstDelay);
 
    stDelayCompsParam.hAi = hAI;
    memcpy(&stDelayCompsParam.stDelayComps, pstDelay, sizeof(HI_UNF_AI_DELAY_S));

    s32Ret = ioctl(g_s32AIFd, CMD_AI_SETDELAYCOMPS, &stDelayCompsParam);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("Set AI Delay Compensation Failed 0x%x \n", s32Ret);  
    }   

    return s32Ret;
}

HI_S32 HI_MPI_AI_GetDelay(HI_HANDLE hAI, HI_UNF_AI_DELAY_S *pstDelay)
{
    HI_S32 s32Ret;
    AI_DelayComps_Param_S stDelayCompsParam;
    
    CHECK_AI_ID(hAI);
    CHECK_AI_NULL_PTR(pstDelay);
 
    stDelayCompsParam.hAi = hAI;

    s32Ret = ioctl(g_s32AIFd, CMD_AI_GETDELAYCOMPS, &stDelayCompsParam);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_AI("Get AI Delay Compensation Failed 0x%x \n", s32Ret);  
    }
    else
    {
        memcpy(pstDelay, &stDelayCompsParam.stDelayComps, sizeof(HI_UNF_AI_DELAY_S));
    }
    
    return s32Ret;
}


#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */
