/******************************************************************************

  Copyright (C), 2011-2015, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name          : mpi_vir.c
  Version             : Initial Draft
  Author              : Hisilicon multimedia software group
  Created             : 2012/12/12
  Last Modified     :
  Description        :
  Function List      :
  History              :
  1.Date               : 2012/12/12
  Author             : h00213218
  Modification     : Created file

******************************************************************************/
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
#include "mpi_lowlatency.h"
#include "hi_mpi_mem.h"
#include "hi_error_mpi.h"
#include "hi_drv_ao.h"
#include "drv_ao_ioctl.h"
#include "hi_audsp_aoe.h"

extern HI_S32 g_s32AOFd;
static HI_TRACK_MmapAttr_S g_stMMPAttr;
static S_AIP_REGS_TYPE* g_pstAipRegExample = HI_NULL;

static inline HI_U32 TrackMmapBufQueryBusy(HI_TRACK_MmapBufAttr_S* pstTrackMmapBufAttr)
{
    HI_U32  u32ReadPos, u32WritePos, u32BusyLen = 0, u32Lenght = 0;

    /* 先从共享内存中取出头信息，避免使用过程中发生变化 */
    u32ReadPos  = *(pstTrackMmapBufAttr->pu32ReadPtr);
    u32WritePos = *(pstTrackMmapBufAttr->pu32WritePtr);
    u32Lenght   =  pstTrackMmapBufAttr->u32Size;


    if (u32WritePos >= u32ReadPos)
    {
        u32BusyLen = u32WritePos - u32ReadPos;
    }
    else
    {
        u32BusyLen = u32Lenght - (u32ReadPos - u32WritePos);
    }

    return u32BusyLen;
}

static inline HI_U32 TrackMmapBufQueryFree(HI_TRACK_MmapBufAttr_S* pstTrackMmapBufAttr)
{
    HI_U32  u32ReadPos, u32WritePos, u32FreeLen = 0, u32Lenght = 0;

    /* 先从共享内存中取出头信息，避免使用过程中发生变化 */
    u32ReadPos  = *(pstTrackMmapBufAttr->pu32ReadPtr);
    u32WritePos = *(pstTrackMmapBufAttr->pu32WritePtr);
    u32Lenght   =  pstTrackMmapBufAttr->u32Size ;

    if (u32WritePos >= u32ReadPos)
    {
        u32FreeLen = (u32Lenght - (u32WritePos - u32ReadPos));
    }
    else
    {
        u32FreeLen = (u32ReadPos - u32WritePos);
    }

    u32FreeLen = (u32FreeLen <= 32) ? 0 : u32FreeLen - 32;
    /* 循环Buffer避免写满，否则读方向认为Buffer为空 */
    if (u32FreeLen > 0)
    {
        u32FreeLen -= 1;
    }
    return u32FreeLen;
}

static inline HI_U32 TrackMmapBufWrite(HI_TRACK_MmapBufAttr_S* pstTrackMmapBufAttr, HI_U8* pDest, HI_U32 u32Len)
{
    HI_U32*  pVirAddr   = NULL;

    HI_U32  u32WtLen[2] = {0, 0};
    HI_U32  u32WtPos[2] = {0, 0};
    HI_U32  i;
    HI_U32  u32ReadPos, u32WritePos, u32Lenght = 0;

    /* 先从共享内存中取出头信息，避免使用过程中发生变化 */
    u32ReadPos  = *(pstTrackMmapBufAttr->pu32ReadPtr);
    u32WritePos = *(pstTrackMmapBufAttr->pu32WritePtr);
    u32Lenght   =  pstTrackMmapBufAttr->u32Size;

    u32WtPos[0] = u32WritePos;
    if (u32WritePos >= u32ReadPos)
    {
        if (u32Lenght >= (u32WritePos + u32Len))
        {
            u32WtLen[0] = u32Len;
        }
        else
        {
            u32WtLen[0] = u32Lenght - u32WritePos;
            u32WtLen[1] = u32Len - u32WtLen[0];

            u32WtPos[1] = 0;
        }
    }
    else
    {
        u32WtLen[0] = u32Len;
    }

    for (i = 0; ( i < 2 ) && (u32WtLen[i] != 0); i++)
    {
        pVirAddr = (HI_U32*)((HI_U32)pstTrackMmapBufAttr->u32UserAddr+ u32WtPos[i]);
        if (pDest)
        {
            memcpy(pVirAddr, pDest, u32WtLen[i]);
            pDest = pDest + u32WtLen[i];
        }
        else //only passthrouth send 0
        {
            memset(pVirAddr, 0, u32WtLen[i]);
        }
        u32WritePos = u32WtPos[i] + u32WtLen[i];
    }

    /* 将读指针写回Buffer头 */
    if (u32WritePos == u32Lenght)
    {
        u32WritePos = 0;
    }
    *(pstTrackMmapBufAttr->pu32WritePtr) = u32WritePos;

    /* 返回实际读取的长度 */
    return u32WtLen[0] + u32WtLen[1];
}

static HI_S32 TRACKMmapWriteFrame(HI_TRACK_MmapBufAttr_S* pstTrackMmapBufAttr,const HI_UNF_AO_FRAMEINFO_S* pstAoFrame)
{
    HI_U32 u32BusySize;
    HI_U32 u32Latency, u32FrameSize, u32WriteSize;

    //先做水线判断，然后写入数据
    //u32Latency = u32Threshold * pstAoFrame->u32SampleRate * pstAoFrame->u32Channels * sizeof(HI_U16)/ 1000;  // 400ms
    u32Latency = 400 * pstAoFrame->u32SampleRate * pstAoFrame->u32Channels * sizeof(HI_U16)/ 1000;  // todo
    
    u32FrameSize = pstAoFrame->u32PcmSamplesPerFrame * pstAoFrame->u32Channels * sizeof(HI_U16);
    u32BusySize = TrackMmapBufQueryBusy(pstTrackMmapBufAttr);
    if ((u32BusySize + u32FrameSize) < u32Latency)
    {
        u32WriteSize = TrackMmapBufWrite(pstTrackMmapBufAttr, (HI_U8*)pstAoFrame->ps32PcmBuffer, u32FrameSize);
        if (u32WriteSize == u32FrameSize)
        {
            return HI_SUCCESS;
        }
        else
        {
            return HI_FAILURE;
        }
    }
    else
    {
        return HI_ERR_AO_OUT_BUF_FULL;
    }
}

HI_S32 LOWLATENCYTrackMmap(HI_HANDLE hTrack, HI_TRACK_MmapAttr_S* pstTrackMmapAttr)
{
    AO_Track_GetTrackMapInfo_Param_S stTrackMapInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32UserAddr;
    stTrackMapInfo.hTrack = hTrack;
    HI_TRACK_MmapBufAttr_S *pstMmapBuff = &pstTrackMmapAttr->stMmapBuff;
    
    memcpy(&(stTrackMapInfo.stTrackMmapAttr), pstTrackMmapAttr, sizeof(HI_TRACK_MmapAttr_S));
    pstMmapBuff->u32UserAddr = HI_NULL;

    s32Ret = ioctl(g_s32AOFd, CMD_AO_TRACK_MMAPTRACKATTR, &stTrackMapInfo);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_AO("ioctl CMD_AO_TRACK_MMAPTRACKATTR failed.s32Ret %x!\n",s32Ret);
        return s32Ret;
    }
    if (stTrackMapInfo.u32AipRegAddr == HI_NULL)
    {
        HI_ERR_AO("Aip Register address error!\n");
        return HI_FAILURE;
    }
    //HI_ERR_AO("AipRegAddr = %#x\n", stTrackMapInfo.u32AipRegAddr);
    
    g_pstAipRegExample = (S_AIP_REGS_TYPE *)HI_MEM_Map(stTrackMapInfo.u32AipRegAddr, sizeof(S_AIP_REGS_TYPE));
    if (!g_pstAipRegExample)
    {
        HI_ERR_AO("mmap aip register failed!\n");
        return HI_FAILURE;
    }
/*
    HI_ERR_AO("AIP REG INFO :\n");
    HI_ERR_AO("AIP_BUF_ADDR = %#x\n", g_pstAipRegExample->AIP_BUF_ADDR);
    HI_ERR_AO("AIP_BUF_PHY_ADDR = %#x\n", g_pstAipRegExample->AIP_BUF_PHYADDR);
    HI_ERR_AO("AIP_BUF_RPTR = %#x\n", g_pstAipRegExample->AIP_BUF_RPTR);
    HI_ERR_AO("AIP_BUF_WPTR = %#x\n", g_pstAipRegExample->AIP_BUF_WPTR);
    HI_ERR_AO("AIP_BUF_SIZE = %#x\n\n", g_pstAipRegExample->AIP_BUF_SIZE);
*/
    u32UserAddr = (HI_U32)HI_MEM_Map(g_pstAipRegExample->AIP_BUF_PHYADDR, g_pstAipRegExample->AIP_BUF_SIZE.bits.buff_size);
    if (!u32UserAddr)
    {
        HI_ERR_AO("mmap aip buffer failed!\n");
        HI_MEM_Unmap((HI_VOID*)g_pstAipRegExample);
        return HI_FAILURE;
    }

    pstMmapBuff->u32UserAddr  = u32UserAddr;
    pstMmapBuff->pu32ReadPtr  = (HI_U32*)(&(g_pstAipRegExample->AIP_BUF_RPTR));
    pstMmapBuff->pu32WritePtr = (HI_U32*)(&(g_pstAipRegExample->AIP_BUF_WPTR));
    pstMmapBuff->u32Size      =  g_pstAipRegExample->AIP_BUF_SIZE.bits.buff_size;

    return HI_SUCCESS;
}

HI_S32   LOWLATENCYTrackUnmap(HI_HANDLE hTrack, HI_TRACK_MmapBufAttr_S *pstMmapBuff)
{ 
    HI_MEM_Unmap((HI_VOID*)pstMmapBuff->u32UserAddr);
    HI_MEM_Unmap((HI_VOID*)g_pstAipRegExample);
    return HI_SUCCESS;
}

HI_S32   LOWLATENCYTrackSetFifoBypass(HI_HANDLE hTrack, HI_BOOL bEnable)
{
    CHECK_AO_TRACK_ID(hTrack);

    AO_Track_FifoBypass_Param_S  stFifoBypass;
    stFifoBypass.hTrack = hTrack;
    stFifoBypass.bEnable = bEnable;
    
    return ioctl(g_s32AOFd, CMD_AO_TRACK_SETFIFOBYPASS, &stFifoBypass);
}

HI_BOOL LOWLATENCY_CheckIsLowlcyTrack(HI_HANDLE hTrack)
{
   HI_BOOL Ret = HI_FALSE;
   
   if((hTrack & 0xff00) == (HI_ID_LOWLATENCY_TRACK<<8))
   {
       Ret = HI_TRUE;
   }
   return Ret;
}

HI_S32 LOWLATENCY_EnableLowLatencyAttr( HI_HANDLE hTrack,HI_BOOL bEanble)
{
    HI_S32 Ret = HI_SUCCESS;
    
    if(bEanble == HI_TRUE)
    {
        g_stMMPAttr.u32BitPerSample = HI_UNF_BIT_DEPTH_16;
        g_stMMPAttr.u32SampleRate   = HI_UNF_SAMPLE_RATE_48K;
        g_stMMPAttr.u32Channels     = 2;
        
        Ret = LOWLATENCYTrackMmap(hTrack, &g_stMMPAttr);
        if(Ret != HI_SUCCESS)
        {
            HI_ERR_AO("LOWLATENCYTrackMmap failed\n");
            return Ret;
        }
        
        Ret = LOWLATENCYTrackSetFifoBypass(hTrack, HI_TRUE);
        if(Ret != HI_SUCCESS)
        {
            HI_ERR_AO("LOWLATENCYTrackSetFifoBypass failed\n");
            return Ret;
        }
    }
    else
    {
        Ret = LOWLATENCYTrackSetFifoBypass(hTrack, HI_FALSE);
        if(Ret != HI_SUCCESS)
        {
            HI_ERR_AO("LOWLATENCYTrackSetFifoBypass failed\n");
            return Ret;
        }
        Ret = LOWLATENCYTrackUnmap(hTrack, &g_stMMPAttr.stMmapBuff);
        if(Ret != HI_SUCCESS)
        {
            HI_ERR_AO("LOWLATENCYTrackUnmap failed\n");
            return Ret;
        }
    }
    return Ret;
}

HI_S32 LOWLATENCY_SendData(HI_HANDLE hTrack,const HI_UNF_AO_FRAMEINFO_S *pstAOFrame)
{
    if((pstAOFrame->u32Channels != 2) || (pstAOFrame->s32BitPerSample != HI_UNF_BIT_DEPTH_16) || (pstAOFrame->u32SampleRate != HI_UNF_SAMPLE_RATE_48K))
    {
        HI_ERR_AO("pstAOFrame Inavlid para\n");
        return HI_ERR_AO_INVALID_PARA;
    }

    return TRACKMmapWriteFrame(&g_stMMPAttr.stMmapBuff, pstAOFrame);
}

HI_S32 LOWLATENCY_GetAIPDelayMs(HI_HANDLE hTrack,HI_U32 *pDelayMs)
{
    HI_U32 u32BusySize;
    u32BusySize = TrackMmapBufQueryBusy(&g_stMMPAttr.stMmapBuff);
    //u32Latency = 400 * pstAoFrame->u32SampleRate * pstAoFrame->u32Channels * sizeof(HI_U16)/ 1000; 

    *pDelayMs = u32BusySize * 1000 / (48000 * 2 * sizeof(HI_U16));
    return HI_SUCCESS;
}

