/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_pvr_index.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2008/04/16
  Description   : INDEX module
  History       :
  1.Date        : 2008/04/16
    Author      : q46153
    Modification: Created file

******************************************************************************/
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/times.h>
#include <assert.h>
#include "hi_module.h"
#include "hi_mpi_mem.h"

#include "pvr_debug.h"
#include "hi_pvr_index.h"
#include "hi_pvr_rec_ctrl.h"
#include "hi_pvr_play_ctrl.h"
#include "hi_pvr_fifo.h"


//#include "hi_pvr_stub.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C"
{
#endif
#endif /* End of #ifdef __cplusplus */

#define PVR_INDEX_NUM (PVR_REC_MAX_CHN_NUM + PVR_PLAY_MAX_CHN_NUM)

/**
    only replay, use the first 2,
    only record, use the last 3,
    on timeshift, player use the index struct of record.
    only play, the index channel number is equal the play channel.
    but, the index channel number is not equal the record channel, it should be equal with the index parser channel number
*/
static PVR_INDEX_S g_stPVRIndex[PVR_INDEX_NUM];
static HI_U32 g_u32RecChnStat[PVR_REC_MAX_CHN_NUM] = {PVR_INDEX_REC_CHN_UNUSED};
static HI_U32 g_u32PvrIndexInit = 0; 

#define PVR_DFT_GOP_LEN     60
#define PVR_DIFF_FFLUSH_HEADINFO 1000

#define PVR_GET_HEADER_OFFSET() ((HI_U32) (&((PVR_IDX_HEADER_INFO_S *)0)->stCycInfo))
#define PVR_GET_USR_DATA_OFFSET(headInfo) (sizeof(PVR_IDX_HEADER_INFO_S) + PVR_MAX_CADATA_LEN)
#define PVR_GET_CA_DATA_OFFSET() (sizeof(PVR_IDX_HEADER_INFO_S))
#define PVR_GET_IDX_INFO_OFFSET(headInfo) (sizeof(PVR_IDX_HEADER_INFO_S) + (headInfo.u32CADataInfoLen) - sizeof(PVR_REC_INDEX_INFO_S))

#define PVR_IDX_NEXT_POS_IN_CYC(CurPos, CycLen)           ((CurPos + 1) % CycLen)
#define PVR_IDX_NEXT_N_POS_IN_CYC(CurPos, n, CycLen)      ((CurPos + n) % CycLen)
#define PVR_IDX_PREV_POS_IN_CYC(CurPos, CycLen)           ((CurPos + CycLen - 1) % CycLen)
#define PVR_IDX_PREV_N_POS_IN_CYC(CurPos, n, CycLen)      ((CurPos + CycLen - n) % CycLen)
#define PVR_IDX_DISTANCE_IN_CYC(DstPos, SrcPos, CycLen)   ((DstPos + CycLen - SrcPos) % CycLen)

#define PVR_IDX_ALIGN_DATA(data) (data + (PVR_INDEX_LEAST_COMMON_MULTIPLE - data % PVR_INDEX_LEAST_COMMON_MULTIPLE))

#define PVR_IS_CYC_READFRAME_INVLD(start, end, read) \
(((end) > (start) && ((read) < (start) || (read) > (end)))\
     || ((end) < (start) && ((read) < (start) && (read) > (end))) )

#define PVR_IDX_ENABLE_REWIND(handle) ((handle)->stCycMgr.bIsRewind)

#define PVR_WRITE_INDEX(saveSz, wantSz, buf, fd, offset, handle) \
do{\
saveSz = PVR_WRITE(buf, wantSz, fd, (off_t)(offset + handle->u32IdxStartOffsetLen));\
if (saveSz != (ssize_t)wantSz)\
{\
    if (NULL != &errno)\
    {\
        if (ENOSPC == errno)\
        {\
            HI_ERR_PVR("PVR_WRITE fail:%d, want:%u\n", saveSz, wantSz);\
            PVR_IDX_CACHE_UNLOCK(&(handle->stIdxWriteCache.stCacheMutex));\
            return HI_ERR_PVR_FILE_DISC_FULL;\
        }\
        else\
        {\
            HI_ERR_PVR("PVR_WRITE fail:%d, want:%u\n", saveSz, wantSz);\
            PVR_IDX_CACHE_UNLOCK(&(handle->stIdxWriteCache.stCacheMutex));\
            return HI_ERR_PVR_FILE_CANT_WRITE;\
        }\
    }\
}\
}while(0)

#define PVR_READ_INDEX_DIRECTLY(readSz,buf, size, fd,  offset, handle)\
do{\
if (PVR_Index_IfOffsetInWriteCache(handle,offset,size))\
{\
    PVR_Index_FlushIdxWriteCache(handle);\
}\
readSz = PVR_READALL(buf, size, fd,  (off_t)(offset + handle->u32IdxStartOffsetLen));\
}while(0)

#ifndef HI_PVR_L2_CACHE_SUPPORT
#define PVR_READ_INDEX(readSz, buf, size, fd, offset, handle)\
do{\
readSz = PVRCacheReadIdx(handle,fd,(HI_VOID*)buf,size,(off_t)offset,0);\
}while(0)
#else
#define PVR_READ_INDEX(readSz, buf, size, fd, offset, handle)\
do{\
readSz = PVRIndexReadIndexFromCache(handle,(HI_VOID*)buf, offset/sizeof(PVR_INDEX_ENTRY_S));\
}while(0)
#endif

#define PVR_IDX_CHECK_CYC_SIZE(pstRecAttr) \
    do{\
        if ((pstRecAttr->u64MaxFileSize == 0) && (pstRecAttr->u64MaxTimeInMs == 0))\
        {\
            HI_WARN_PVR("invalidate u64MaxFileSize and u64MaxTimeInMs error!\n");\
        }\
        else if ((pstRecAttr->u64MaxFileSize > 0) && (pstRecAttr->u64MaxTimeInMs > 0))\
        {\
            if ((pstRecAttr->u64MaxFileSize < PVR_MIN_CYC_SIZE) || (pstRecAttr->u64MaxTimeInMs < PVR_MIN_CYC_TIMEMS))\
            {\
                HI_WARN_PVR("invalidate u64MaxFileSize and u64MaxTimeInMs error!\n");\
            }\
        }\
        else if ((pstRecAttr->u64MaxFileSize > 0) && (pstRecAttr->u64MaxFileSize < PVR_MIN_CYC_SIZE))\
        {\
            HI_WARN_PVR("invalidate u64MaxFileSize and u64MaxTimeInMs error!\n");\
        }\
        else if ((pstRecAttr->u64MaxTimeInMs > 0) && (pstRecAttr->u64MaxTimeInMs < PVR_MIN_CYC_TIMEMS))\
        {\
            HI_WARN_PVR("invalidate u64MaxFileSize and u64MaxTimeInMs error!\n");\
        }\
    }while(0)

#define PVR_IDX_CHECK_IDX_LEAD_DATA(IdxOffset, DataOffset)    ((IdxOffset > DataOffset)?HI_TRUE:HI_FALSE)

#define PVR_IDX_CHECK_REWINDTYPE_BYBOTY(pstIdxEntry,pstCycMgr) \
do\
{\
    if(pstIdxEntry->u32DisplayTimeMs > pstCycMgr->u32MaxCycTimeInMs) \
    {\
        pstCycMgr->enRewindType = PVR_INDEX_REWIND_BY_TIME;\
    }\
    if (pstIdxEntry->u64GlobalOffset > pstCycMgr->u64MaxCycSize)\
    {\
        pstCycMgr->enRewindType = PVR_INDEX_REWIND_BY_SIZE;\
    }\
}while(0)

#define PVR_IDX_TRANSFER_FRM_TO_OFFSET(Frm, handle) ((Frm) * sizeof(PVR_INDEX_ENTRY_S) + handle->u32IdxStartOffsetLen)

#ifdef HI_PVR_L2_CACHE_SUPPORT
static HI_BOOL PVRIndexChechBeCached(HI_U32 u32ReadFrm, HI_U32 u32StartNum, HI_U32 u32UsedNum)
{
    if ((u32ReadFrm >= u32StartNum) && (u32ReadFrm < (u32StartNum + u32UsedNum)))
    {
        return HI_TRUE;
    }
    else
    {
        return HI_FALSE;
    }
}

static HI_BOOL PVRIndexCheckReadCacheHeadValid(HI_U32 u32Head, HI_U32 u32ReadFrm, PVR_CYC_HEADER_INFO_S *pstCycHeaderInfo)
{
    //���Ƶ��������ȡ֡����start���֣���֤head��С��start��
    //��ȡ֡����end���֣���headʼ����Ч
    if (pstCycHeaderInfo->u32StartFrame > pstCycHeaderInfo->u32EndFrame)
    {
        if (u32ReadFrm >= pstCycHeaderInfo->u32StartFrame && u32Head >= pstCycHeaderInfo->u32StartFrame)
            return HI_TRUE;

        if (u32ReadFrm <= pstCycHeaderInfo->u32EndFrame)
            return HI_TRUE;
    }
    //�ǻ����������֤head����start����Ч
    else
    {
        if (u32Head >= pstCycHeaderInfo->u32StartFrame)
            return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL PVRIndexCheckReadCacheTailValid(HI_U32 u32Tail, HI_U32 u32ReadFrm, PVR_CYC_HEADER_INFO_S *pstCycHeaderInfo)
{
    if (pstCycHeaderInfo->u32StartFrame > pstCycHeaderInfo->u32EndFrame)
    {
        if (u32ReadFrm <= pstCycHeaderInfo->u32EndFrame && u32Tail <= pstCycHeaderInfo->u32EndFrame)
            return HI_TRUE;
        
        if (u32ReadFrm >= pstCycHeaderInfo->u32StartFrame)
            return HI_TRUE;
    }
    else
    {
        if (u32Tail <=  pstCycHeaderInfo->u32EndFrame)
            return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_BOOL PVRIndexCheckReadFrmIsInCache(PVR_CYC_MGR_S *pstCycMgr,HI_U32 u32ReadFrm, HIPVR_IDX_BUF_S *pstIdxBuf)
{
    HI_U32 u32ReadFrmInWriteCache, u32WriteFrmInWriteCache;

    if (pstIdxBuf->u32UsedNum == 0)
    {
        return HI_FALSE;
    }

    u32WriteFrmInWriteCache = pstCycMgr->u32EndFrame;
    u32ReadFrmInWriteCache = PVR_IDX_PREV_N_POS_IN_CYC(pstCycMgr->u32EndFrame, 
                                PVR_IDX_DISTANCE_IN_CYC(pstIdxBuf->u32Write,pstIdxBuf->u32Read,PVR_INDEX_WRITE_CACHE_NUM),
                                (pstCycMgr->u32LastFrame + 1));

//���Cache  ��û�з������ƣ����ȡ��֡����С�ڵ���endframe
    if (u32WriteFrmInWriteCache > u32ReadFrmInWriteCache)
    {
        if ((u32ReadFrm <= pstCycMgr->u32EndFrame) && (u32ReadFrm >= u32ReadFrmInWriteCache))
        {
            return HI_TRUE;
        }
    }
//���Cache  �з������ƣ����ȡ��֡����С�ڵ���
    else
    {
        if ((u32ReadFrm <= pstCycMgr->u32EndFrame) || (u32ReadFrm >= u32ReadFrmInWriteCache))
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}



static HI_BOOL PVRIndexCheckReadFrmIsInFile(HI_U32 u32ReadFrm,PVR_CYC_HEADER_INFO_S *pstCycHeaderInfo)
{
    HI_U32 u32StartFrame, u32EndFrame, u32LastFrame;

    u32StartFrame = pstCycHeaderInfo->u32StartFrame;
    u32EndFrame   = pstCycHeaderInfo->u32EndFrame;
    u32LastFrame  = pstCycHeaderInfo->u32LastFrame;

    /*just beginning of recording*/
    if (0 == u32LastFrame)
    {
        return HI_FALSE;
    }

    if (u32StartFrame < u32EndFrame)
    {
        if ((u32ReadFrm >= u32StartFrame) && (u32ReadFrm <= u32EndFrame))
        {
            return HI_TRUE;
        }
    }
    else
    {
        /* rewind case */
        if (((u32ReadFrm >= u32StartFrame) && (u32ReadFrm <= u32LastFrame))
            || (u32ReadFrm <= u32EndFrame))
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;    
}

static ssize_t PVRIndexReadIndexFromCache(PVR_INDEX_HANDLE hIndex, HI_VOID *pBuf, HI_U32 u32ReadFrm)
{
    HI_S32 s32Start, s32ReadSize;
    HI_U32 u32CacheEndNum, u32CacheSize;
    HI_BOOL bReadCacheInvalid = HI_FALSE;
    HIPVR_IDX_BUF_S *pstReadCache = HI_NULL;

    if ((-1 == hIndex->stCycMgr.u32EndFrame ) || (-1 == hIndex->stCycMgr.u32LastFrame))
    {
        HI_WARN_PVR("Cache and file has no data!!!\n");
        return -1;
    }

    pstReadCache = &hIndex->stIdxReadCache;

    u32CacheSize = PVR_INDEX_READ_CACHE_NUM * sizeof(PVR_INDEX_ENTRY_S);

    //ʱ�Ƴ������ȼ���Ƿ���writecache��
    if (hIndex->bIsRec)
    {
        PVR_IDX_CACHE_LOCK(&(hIndex->stIdxWriteCache.stCacheMutex));
        if (PVRIndexCheckReadFrmIsInCache(&hIndex->stCycMgr, u32ReadFrm, &hIndex->stIdxWriteCache))
        {
            HI_U32 u32Read;
            u32Read = PVR_IDX_PREV_N_POS_IN_CYC(PVR_IDX_PREV_N_POS_IN_CYC(hIndex->stIdxWriteCache.u32Write, 1, PVR_INDEX_WRITE_CACHE_NUM),
                                                PVR_IDX_DISTANCE_IN_CYC(hIndex->stCycMgr.u32EndFrame, u32ReadFrm, (hIndex->stCycMgr.u32LastFrame + 1)),
                                                PVR_INDEX_WRITE_CACHE_NUM);
            memcpy(pBuf, hIndex->stIdxWriteCache.pu8Addr + u32Read*sizeof(PVR_INDEX_ENTRY_S), 
                   sizeof(PVR_INDEX_ENTRY_S));
            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxWriteCache.stCacheMutex));
            return sizeof(PVR_INDEX_ENTRY_S);
        }
        PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxWriteCache.stCacheMutex));
    }

    //����Ƿ����ļ���
    if (!PVRIndexCheckReadFrmIsInFile(u32ReadFrm, &hIndex->stFileCycInfo))
    {
        HI_WARN_PVR("ReadFrm %d is not in file or cache! s/e/l:%d/%d/%d\n",
                    u32ReadFrm, hIndex->stFileCycInfo.u32StartFrame, hIndex->stFileCycInfo.u32EndFrame,
                    hIndex->stFileCycInfo.u32LastFrame);
        return 0;
    }
    
    //���readcache  ����û���ݣ���start  ��ʼ��ȡ
    PVR_IDX_CACHE_LOCK(&(hIndex->stIdxReadCache.stCacheMutex));

    if (hIndex->stIdxReadCache.u32UsedNum == 0)
    {
        s32Start = hIndex->stFileCycInfo.u32StartFrame;
        if ((s32Start + PVR_INDEX_READ_CACHE_NUM) > hIndex->stFileCycInfo.u32LastFrame)
        {
            u32CacheSize = (hIndex->stFileCycInfo.u32LastFrame - s32Start + 1)*sizeof(PVR_INDEX_ENTRY_S);
        }

        s32ReadSize = PVR_READALL(hIndex->stIdxReadCache.pu8Addr, u32CacheSize, hIndex->s32ReadFd,
                        (off_t)PVR_IDX_TRANSFER_FRM_TO_OFFSET(s32Start, hIndex));

        if ((s32ReadSize <= 0) || (s32ReadSize % sizeof(PVR_INDEX_ENTRY_S)))
        {
            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));
            HI_ERR_PVR("Readcache no data and read failed! start=%d want=%d readed=%d\n", 
                        s32Start, u32CacheSize, s32ReadSize);
            return -1;
        }
        else
        {
            hIndex->stIdxReadCache.u32StartNum = s32Start;
            hIndex->stIdxReadCache.u32UsedNum = s32ReadSize/sizeof(PVR_INDEX_ENTRY_S);
        }
    }

//��readcache���б߽��飬��֤ͷ����β��������Ч������
    if (PVRIndexCheckReadCacheHeadValid(hIndex->stIdxReadCache.u32StartNum, u32ReadFrm, &hIndex->stFileCycInfo) &&
        PVRIndexCheckReadCacheTailValid(hIndex->stIdxReadCache.u32StartNum + hIndex->stIdxReadCache.u32UsedNum - 1, u32ReadFrm, &hIndex->stFileCycInfo))
    {
        bReadCacheInvalid = HI_FALSE;
    }
    else
    {
        bReadCacheInvalid = HI_TRUE;
    }

//���readcacheû�����ǲ���readcache�߽���Ч�������Ƿ�cache�ɹ����ɹ��򷵻أ�ʧ�������¶�ȡ
    if ((pstReadCache->bDirty == HI_FALSE) && (bReadCacheInvalid == HI_FALSE))
    {
        if (PVRIndexChechBeCached(u32ReadFrm, hIndex->stIdxReadCache.u32StartNum, hIndex->stIdxReadCache.u32UsedNum))
        {
            memcpy(pBuf,hIndex->stIdxReadCache.pu8Addr+(u32ReadFrm - hIndex->stIdxReadCache.u32StartNum)*sizeof(PVR_INDEX_ENTRY_S),
                   sizeof(PVR_INDEX_ENTRY_S));

            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));

            return sizeof(PVR_INDEX_ENTRY_S);
        }
    }
//��������ǻ���ûcache  �У����¶�ȡcache

    {
        /* readcache  ���ô��ڻ��ƣ���read  Ϊ���ĵĴ���*/
        s32Start = (HI_S32)(u32ReadFrm - PVR_INDEX_READ_CACHE_NUM/2);
        if (s32Start < 0)
        {
            s32Start = 0;
        }
        //��ͷ�����б߽��飬��֤ͷ��������Ч������
        if (!PVRIndexCheckReadCacheHeadValid((HI_U32)s32Start, u32ReadFrm, &hIndex->stFileCycInfo))
        {
            s32Start = hIndex->stFileCycInfo.u32StartFrame;
        }
        
        u32CacheEndNum = s32Start + PVR_INDEX_READ_CACHE_NUM - 1;
        if (u32CacheEndNum > hIndex->stFileCycInfo.u32LastFrame)
        {
            u32CacheEndNum = hIndex->stFileCycInfo.u32LastFrame;
            u32CacheSize = (u32CacheEndNum - s32Start + 1) * sizeof(PVR_INDEX_ENTRY_S);
        }
        //��β�����б߽��飬��֤β��������Ч������
        if (!PVRIndexCheckReadCacheTailValid(u32CacheEndNum, u32ReadFrm, &hIndex->stFileCycInfo))
        {
            u32CacheEndNum = hIndex->stFileCycInfo.u32EndFrame;
            u32CacheSize = (u32CacheEndNum - s32Start + 1)*sizeof(PVR_INDEX_ENTRY_S);
        }
       
        s32ReadSize = PVR_READALL(hIndex->stIdxReadCache.pu8Addr, u32CacheSize, hIndex->s32ReadFd,
                        (off_t)PVR_IDX_TRANSFER_FRM_TO_OFFSET(s32Start, hIndex));
        if ((s32ReadSize <= 0) || (s32ReadSize % sizeof(PVR_INDEX_ENTRY_S)))
        {
            HI_ERR_PVR("Read file to cache failed! start=%d want=%d readed=%d s/e/l:%d/%d/%d\n", 
                        s32Start, u32CacheSize, s32ReadSize, hIndex->stFileCycInfo.u32StartFrame,
                        hIndex->stFileCycInfo.u32EndFrame, hIndex->stFileCycInfo.u32LastFrame);
            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));
            return -1;
        }

        hIndex->stIdxReadCache.u32StartNum = (HI_U32)s32Start;
        hIndex->stIdxReadCache.u32UsedNum  = (HI_U32)(s32ReadSize)/sizeof(PVR_INDEX_ENTRY_S);

        if (!PVRIndexChechBeCached(u32ReadFrm, hIndex->stIdxReadCache.u32StartNum, hIndex->stIdxReadCache.u32UsedNum))
        {
            HI_ERR_PVR("Readcache is still not cached! readfrm %d end %d last %d cachestart %d usdnum %d cachesize %d readsize %d\n",
                        u32ReadFrm, hIndex->stCycMgr.u32EndFrame, hIndex->stCycMgr.u32LastFrame,hIndex->stIdxReadCache.u32StartNum,
                        hIndex->stIdxReadCache.u32UsedNum,u32CacheSize, s32ReadSize);
            PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));
            return -1;
        }
        
        memcpy(pBuf, hIndex->stIdxReadCache.pu8Addr + (u32ReadFrm - hIndex->stIdxReadCache.u32StartNum)*sizeof(PVR_INDEX_ENTRY_S),
               sizeof(PVR_INDEX_ENTRY_S));
        pstReadCache->bDirty = HI_FALSE;

    }
    
    PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxReadCache.stCacheMutex));

    /*PVR_INDEX_ENTRY_S *ptmp = (PVR_INDEX_ENTRY_S *)pBuf;
    HI_INFO_PVR("read cache index %d startnum %d, cachesize=%d displaytime %d\n", 
             u32ReadFrm,
             hIndex->stIdxReadCache.u32StartNum,
             u32CacheSize,
             ptmp->u32DisplayTimeMs);*/
    return sizeof(PVR_INDEX_ENTRY_S);
}

#endif

/*use cache when read*/
static ssize_t PVRCacheReadIdx(PVR_INDEX_HANDLE  handle,PVR_FILE fd, HI_VOID* pData,size_t size, 
                              HI_U32 offset,HI_U32 u32DirectFlag);
static HI_S32 PVR_Index_IfOffsetReadCache(PVR_INDEX_HANDLE  handle,HI_U32 u32Offset,HI_U32 u32Size);
static HI_S32 PVRIndexGetEntryByNum(const PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pEntry, HI_U32 u32FrameNum);

/*
static HI_U32 PVRIndex_UpdatePreEntryTimeMs(PVR_INDEX_HANDLE pvrIndexHandle, HI_U32 u32TimeMs)
{
    HI_U32 u32MaxCount = sizeof(pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs)/sizeof(pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs[0]);
    HI_U32 u32Index = 0;
    HI_U32 u32AverageRet = 0;
    HI_U64 u64TotalValue = 0;

    for (u32Index=0; u32Index<(u32MaxCount-1); u32Index++)
    {
        pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs[u32Index] = pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs[u32Index+1];

        u64TotalValue += pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs[u32Index];
    }

    pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs[u32MaxCount-1] = u32TimeMs;

    u64TotalValue += pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs[u32MaxCount-1];

    u32AverageRet = u64TotalValue / u32MaxCount;

    pvrIndexHandle->stPreEntryTime.s32Count++;
    pvrIndexHandle->stPreEntryTime.s32Count %= u32MaxCount;

    return u32AverageRet;
}

static HI_U32 PVRIndex_GetPreEntryAverageTimeMs(PVR_INDEX_HANDLE pvrIndexHandle)
{
    HI_U32 u32MaxCount = sizeof(pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs)/sizeof(pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs[0]);
    HI_U32 u32Index = 0;
    HI_U32 u32AverageRet = 0;
    HI_U64 u64TotalValue = 0;

    for (u32Index=0; u32Index<u32MaxCount; u32Index++)
    {
        u64TotalValue += pvrIndexHandle->stPreEntryTime.u32PreEntryTimeMs[u32Index];
    }

    u32AverageRet = u64TotalValue / u32MaxCount;

    return u32AverageRet;
}
*/

/*This api is only for IP record*/
static HI_U32 PVRIndexGetRecTimeStamp(PVR_INDEX_HANDLE handle, const HI_UNF_DMX_REC_INDEX_S *pstRecIdx)
{
    HI_U32 u32DeltaTime = 0;
    HI_U32 u32DeltaFrameNum = 0;
    HI_U32 u32DeltaTimeStamp = 0;
    PVR_REC_TIMESTAMP_S *pstTimeStamp = &handle->stTimeStamp;

    pstTimeStamp->u32FrameNum++;

    /*in first Gop (if less than 20 frames),we using average average delta timestamp of the first 20 frames to adjust the frameTimeMs*/
    /*get the first frame PTS ,as the calc base value to get the first average delta timestamp*/
    if (pstTimeStamp->stLastIFrmPtsInfo.u32PtsMs == PVR_INDEX_INVALID_PTSMS)
    {
        pstTimeStamp->stLastIFrmPtsInfo.u32PtsMs = pstRecIdx->u32PtsMs;
        pstTimeStamp->stLastIFrmPtsInfo.u32FrameNum = pstTimeStamp->u32FrameNum;
    }

    if ((pstTimeStamp->stCurIFrmPtsInfo.u32PtsMs == PVR_INDEX_INVALID_PTSMS) && 
        (pstRecIdx->u32PtsMs > pstTimeStamp->stLastIFrmPtsInfo.u32PtsMs) && 
        (pstTimeStamp->u32FrameNum >= PVR_INDEX_MAX_TIMESTAMP_BASE))
    {
        pstTimeStamp->stCurIFrmPtsInfo.u32PtsMs = pstRecIdx->u32PtsMs;
        pstTimeStamp->stCurIFrmPtsInfo.u32FrameNum = pstTimeStamp->u32FrameNum;
        pstTimeStamp->bShouldUpdateTimeStamp = HI_TRUE;
    } 

    /*After we get I frame ,then ,we only using I fram to calc the average delta timestamp*/
    if ((pstRecIdx->enFrameType == HI_UNF_FRAME_TYPE_I) && (pstTimeStamp->u32FrameNum >= PVR_INDEX_MAX_TIMESTAMP_BASE))
    {
        pstTimeStamp->stCurIFrmPtsInfo.u32PtsMs = pstRecIdx->u32PtsMs ;
        pstTimeStamp->stCurIFrmPtsInfo.u32FrameNum = pstTimeStamp->u32FrameNum;
        /*if PTS rewind or wrapped (32bit overflow),need not update the average timestamp*/
        if (pstTimeStamp->stCurIFrmPtsInfo.u32PtsMs > pstTimeStamp->stLastIFrmPtsInfo.u32PtsMs)
        {
            pstTimeStamp->bShouldUpdateTimeStamp = HI_TRUE;
        }
    }

    if (pstTimeStamp->bShouldUpdateTimeStamp)
    {
        pstTimeStamp->bShouldUpdateTimeStamp = HI_FALSE;
        u32DeltaTime = pstTimeStamp->stCurIFrmPtsInfo.u32PtsMs - pstTimeStamp->stLastIFrmPtsInfo.u32PtsMs;
        u32DeltaFrameNum = pstTimeStamp->stCurIFrmPtsInfo.u32FrameNum - pstTimeStamp->stLastIFrmPtsInfo.u32FrameNum;
        if ((u32DeltaTime !=0) && (u32DeltaFrameNum >= 1))
        {
            u32DeltaTimeStamp = u32DeltaTime/u32DeltaFrameNum;;
            /*liuxingqiang said ,he has meet the frame time gop rang of 15~60 Ms,some net stream is 15fps*/
            if ((u32DeltaTimeStamp < PVR_INDEX_MAX_TIMESTAMP_GOP) && 
                (u32DeltaTimeStamp > PVR_INDEX_MIN_TIMESTAMP_GOP))
            {
                pstTimeStamp->u32DeltaTimeStamp = u32DeltaTimeStamp;
            }               
        }          
        pstTimeStamp->stLastIFrmPtsInfo.u32PtsMs = pstTimeStamp->stCurIFrmPtsInfo.u32PtsMs;
        pstTimeStamp->stLastIFrmPtsInfo.u32FrameNum = pstTimeStamp->stCurIFrmPtsInfo.u32FrameNum;
    }

    if (pstTimeStamp->u32FrameNum <= 1)
    {
        pstTimeStamp->u32CurFrameTimeMs = 0;
    }
    else
    {
        pstTimeStamp->u32CurFrameTimeMs += pstTimeStamp->u32DeltaTimeStamp;
    }

    return pstTimeStamp->u32CurFrameTimeMs;
}


HI_U32 PVRIndexGetCurTimeMs(HI_VOID)
{
    HI_U32    Ticks;
    struct tms buf;
    Ticks = (HI_U32)times(&buf);

    return Ticks * 10;
}

static HI_BOOL PVRIndexCheckEndOffsetCoverStartOffset(HI_U64 u64EndOffset,
                                                      HI_U64 u64EndNextOffset,
                                                      HI_U64 u64Offset,
                                                      HI_U64 u64CycSize)
{
    if (((u64EndOffset < u64Offset) && (u64EndNextOffset >= u64Offset)) ||
         ((u64EndNextOffset > u64CycSize) && (u64EndNextOffset % u64CycSize >= u64Offset)))
    {
        return HI_TRUE;   
    }
    else
        return HI_FALSE;
}

/*****************************************************************************
 Prototype       : PVRIndexIsFileRecording
 Description     : check whether the file is recording or not.
 Input           : pIdxFileName--- to check the file
 Output          : handle------- PVR index handle
 Return Value    : On successfully, return HI_TRUE. otherwise return HI_FALSE;
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2010/06/18
    Author       : j40671
    Modification : Created function

*****************************************************************************/
/**
@brief Check the index file whether is the recording one or not. If HI_TRUE, param handle will save the recording index handle.

@param[in] pIdxFileName : the name of index file
@param[out] handle      : if return HI_TRUE, this param save the recording index handle.

@return HI_BOOL

@retval HI_FALSE The index file does NOT record, yet
@retval HI_TRUE The index file is recording

@author j40671
@date 2010/06/18
@sa PVRIndexIsFilePlaying.
*/
static HI_BOOL PVRIndexIsFileRecording(const HI_CHAR *pIdxFileName, PVR_INDEX_HANDLE *handle)
{
    HI_U32 i;

    if ((NULL == handle) || (NULL == pIdxFileName))
    {
        HI_PRINT("\n<%s %d>: Input pointer parameter is NULL!\n", __FUNCTION__, __LINE__);
        return HI_FALSE;   
    }

    for (i = 0; i < PVR_INDEX_NUM; i++)
    {
        if (g_stPVRIndex[i].bIsRec)
        {
            if  (!strncmp(g_stPVRIndex[i].szIdxFileName, pIdxFileName,strlen(pIdxFileName)))
            {
                *handle = &g_stPVRIndex[i];

                return HI_TRUE;
            }
        }
    }

    return HI_FALSE;
}

/*****************************************************************************
 Prototype       : PVRIndexIsFilePlaying
 Description     : get index handle by file name
 Input           : pFileName  **
 Output          : handle     **
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2010/06/18
    Author       : j40671
    Modification : Created function

*****************************************************************************/
/**
@brief Check the index file whether is the playing one or not. If HI_TRUE, param handle will save the playing index handle.

@param[in] pIdxFileName : the name of index file
@param[out] handle      : if return HI_TRUE, this param save the playing index handle.

@return HI_BOOL

@retval HI_FALSE The index file does NOT play, yet
@retval HI_TRUE The index file is playing

@author j40671
@date 2010/06/18
@sa PVRIndexIsFileRecording.
*/

static HI_BOOL PVRIndexIsFilePlaying(const HI_CHAR *pIdxFileName, PVR_INDEX_HANDLE *handle)
{
    HI_U32 i;
    
    if ((NULL == handle) || (NULL == pIdxFileName))
    {
        HI_PRINT("\n<%s %d>: Input pointer parameter is NULL!\n", __FUNCTION__, __LINE__);
        return HI_FALSE;   
    }

    for (i = 0; i < PVR_INDEX_NUM; i++)
    {
        if (g_stPVRIndex[i].bIsPlay)
        {
            if  (!strncmp(g_stPVRIndex[i].szIdxFileName, pIdxFileName,strlen(pIdxFileName)))
            {
                *handle = &g_stPVRIndex[i];

                return HI_TRUE;
            }
        }
    }

    return HI_FALSE;
}


static HI_BOOL PVRIndexIsFrameValid(HI_U32 u32FrmPos, PVR_CYC_MGR_S *pstCycMgr)
{
    HI_U32 u32StartFrame = 0;
    HI_U32 u32EndFrame = 0;
    HI_U32 u32LastFrame = 0;

    u32StartFrame = pstCycMgr->u32StartFrame;
    u32EndFrame   = (pstCycMgr->u32EndFrame == -1)?0:pstCycMgr->u32EndFrame;
    u32LastFrame  = (pstCycMgr->u32LastFrame == -1)?0:pstCycMgr->u32LastFrame;

    /*
        1. Not rewind case
        =================
        |//////////////////// |
        |//////////////////// |
        =================
        /\                                  /\
         |                                   |
         StartFrame                    EndFrame

         2. Rewind case
         =================
         |////|xxxxx |/////////|
         |////|xxxxx |/////////|
         =================
                /\         /\               /\
                 |          |                |
          EndFrame  StartFrame  LastFrame
        */
    /* Not rewind case */
    if (u32StartFrame < u32EndFrame)
    {
        if ((u32FrmPos >= u32StartFrame) && (u32FrmPos <= u32EndFrame))
        {
            return HI_TRUE;
        }
    }
    else
    {
        /* rewind case */
        if (((u32FrmPos >= u32StartFrame) && (u32FrmPos <= u32LastFrame))
            || (u32FrmPos <= u32EndFrame))
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}


/*! @}*/
#if 0 /* by g00182102 gaoyanfeng */

/* calculate the total frame number, input three valid position. allow rewind or not*/
STATIC INLINE HI_U32 PVRIndexCalcFrameNum(HI_U32 u32StartFrame, HI_U32 u32EndFrame, HI_U32 u32LastFrame)
{
    HI_U32 u32FrameNum = 0;

    if (u32StartFrame < u32EndFrame)
    {
        u32FrameNum = u32EndFrame - u32StartFrame;
    }
    else
    {
        u32FrameNum = u32LastFrame - u32StartFrame + u32EndFrame;
    }

    return u32FrameNum;
}


/*
away from u32FrmPos with s32Offset in the direction of forward or backward.
if s32Offset reach to start, it will be start.
if s32Offset reach to end, it will be end.
the return value is the new position.
*/
STATIC INLINE HI_U32 PVRIndexCalcNewPos(PVR_INDEX_HANDLE handle, HI_U32 u32FrmPos, HI_S32 s32Offset)
{
    HI_U32 u32NewPos = 0;
    HI_U32 u32StartFrame = 0;
    HI_U32 u32EndFrame = 0;
    HI_U32 u32LastFrame = 0;
    HI_U32 u32Pos2Start = 0; /* the frame number from current pos to start pos*/
    HI_U32 u32Pos2End = 0;  /* the frame numbre from current pos to end pos */

    u32StartFrame = handle->stCycMgr.u32StartFrame;
    u32EndFrame = handle->stCycMgr.u32EndFrame;
    u32LastFrame = handle->stCycMgr.u32LastFrame;

    /* check whether the start position is valid or not. invalid, set it to start or end */
    if (!PVRIndexIsFrameValid(handle, u32FrmPos))
    {
        /* direction forward, set it to start */
        if (s32Offset <= 0)
        {
            u32NewPos = u32StartFrame;
        }
        else
        {
            u32NewPos = u32EndFrame;
        }
        return u32NewPos;
    }

    /* direction forward, that is toward the start position, whether it over than the start, if that, set it to start */
    if (s32Offset < 0)
    {
        u32Pos2Start = PVRIndexCalcFrameNum(u32StartFrame, u32FrmPos, u32LastFrame);
        if (abs(s32Offset) > u32Pos2Start)
        {
            u32NewPos = u32StartFrame;
            return u32NewPos;
        }
    }
    else /* direction backward, whether it over than the end, if that, set it to end */
    {
        u32Pos2End = PVRIndexCalcFrameNum(u32FrmPos, u32EndFrame, u32LastFrame);
        if (abs(s32Offset) > u32Pos2End)
        {
            u32NewPos = u32EndFrame;
            return u32NewPos;
        }
    }

    /* for security, make further check it */
    u32NewPos = u32FrmPos + s32Offset;

    if (u32StartFrame < u32EndFrame) /*not rewind*/
    {
        /* check the boundary, the value should be range from u32StartFrame to u32EndFrame. */
        if ((HI_S32)u32NewPos < (HI_S32)u32StartFrame)
        {
            u32NewPos = u32StartFrame;
        }

        if (u32NewPos > u32EndFrame)
        {
            u32NewPos = u32EndFrame;
        }
    }
    else /*be rewind*/
    {
        if ((HI_S32)u32NewPos < 0)
        {
            u32NewPos = u32LastFrame  + (HI_S32)u32NewPos;
        }
        else if (u32NewPos > (u32LastFrame - 1))
        {
            u32NewPos = u32NewPos - u32LastFrame;
        }
        else if ((u32NewPos < u32StartFrame) && (u32NewPos > u32EndFrame))
        {
            /* between start and end, assigned with the most close to it. normally, never incoming here*/
            u32NewPos = ((u32NewPos - u32EndFrame) > (u32StartFrame - u32NewPos)) ? (u32StartFrame) : (u32EndFrame);
        }
    }

    if(abs(s32Offset) > 1)
    {
        HI_WARN_PVR("\033[1;42;34m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! POSITION IS NOT EQUAL Info start !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        HI_WARN_PVR("u32StartFrame = %u, u32EndFrame = %u, u32LastFrame = %u\n",u32StartFrame, u32EndFrame, u32LastFrame);
        HI_WARN_PVR("new position = %u u32FrmPos = %u, s32Offset = %d\n",u32NewPos, u32FrmPos, s32Offset);
        HI_WARN_PVR("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! POSITION IS NOT EQUAL Info end!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\033[0m\n");
    }

    return u32NewPos;
}
#else

//#define DBG_FRAME_POS

#ifdef DBG_FRAME_POS
#define MAX_PRINT_TIMES 10 /* Max print info times. */
static int g_dbgFlag = 0; /* used only by PVRIndexCalcNewPos, just only for debug, enable print times */
static int nPrintTimes = 0;
#endif

STATIC INLINE HI_U32 PVRIndexCalcNewPos(PVR_INDEX_HANDLE handle, HI_U32 u32FrmPos, HI_S32 s32Offset)
{
    HI_U32 u32NewPos = 0;

    HI_U32 u32StartFrame = 0;
    HI_U32 u32EndFrame = 0;
    HI_U32 u32LastFrame = 0;

    HI_U32 u32Boundary = 0;
    HI_U32 u32DiffToStart = 0;
    HI_U32 u32DiffToEnd = 0;

    u32StartFrame = handle->stCycMgr.u32StartFrame;
    u32EndFrame   = (handle->stCycMgr.u32EndFrame == -1)?0:handle->stCycMgr.u32EndFrame;
    u32LastFrame  = (handle->stCycMgr.u32LastFrame == -1)?0:handle->stCycMgr.u32LastFrame;

#ifdef DBG_FRAME_POS
    if(g_dbgFlag >= 0)
    {
        HI_ERR_PVR("\033[1;45;37m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Info start !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        HI_ERR_PVR("u32StartFrame = %u, u32EndFrame = %u, u32LastFrame = %u\n",u32StartFrame, u32EndFrame, u32LastFrame);
        HI_ERR_PVR("u32FrmPos = %u, s32Offset = %d\n",u32FrmPos, s32Offset);
        HI_ERR_PVR("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Info end!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\033[0m\n");
    }
#else
    HI_INFO_PVR("\033[1;45;37m #######%s########\n", __func__);
    HI_INFO_PVR("u32StartFrame = %u, u32EndFrame = %u, u32LastFrame = %u\n",u32StartFrame, u32EndFrame, u32LastFrame);
    HI_INFO_PVR("u32FrmPos = %u, s32Offset = %d\n",u32FrmPos, s32Offset);
    HI_INFO_PVR("##############################################\n\033[0m\n");
#endif

    /* check whether the frame position is valid or not. invalid, set it to start or end */
    if (!PVRIndexIsFrameValid(u32FrmPos, &handle->stCycMgr))
    {
#ifdef DBG_FRAME_POS
        HI_ERR_PVR("\033[1;45;37m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Info start !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        HI_ERR_PVR("u32StartFrame = %u, u32EndFrame = %u, u32LastFrame = %u\n",u32StartFrame, u32EndFrame, u32LastFrame);
        HI_ERR_PVR("u32FrmPos = %u, s32Offset = %d\n",u32FrmPos, s32Offset);
        HI_ERR_PVR("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! Info end!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\033[0m\n");
#endif
        if ( (u32StartFrame > u32EndFrame) && (u32FrmPos > u32EndFrame) && (u32FrmPos < u32StartFrame) )
        {
            u32DiffToStart = u32StartFrame - u32FrmPos;
            u32DiffToEnd = u32FrmPos - u32EndFrame;

            u32NewPos = (u32DiffToStart > u32DiffToEnd ) ? u32EndFrame : u32StartFrame;

            HI_WARN_PVR("Frame %u value invalid, set it to Frame %u, offset to end:%u, offset to start:%u\n",u32FrmPos,u32NewPos,u32DiffToEnd,u32DiffToStart);
        }
        else
        {
            /* more than u32LastFrame */
            u32NewPos = u32LastFrame;

            HI_WARN_PVR("Frame value invalid, set it to Frame %u\n",u32NewPos);
        }

        HI_WARN_PVR("\033[1;37;30mNow u32NewPos is %u in line:%d\n\033[0m", u32NewPos, __LINE__);

        return u32NewPos;
    }

    u32NewPos = u32FrmPos + (HI_U32)s32Offset;

    if(s32Offset >= 0)/* away from the u32FrmPos forward direction toward to u32EndFrame */
    {
        /*
            1. Not rewind (X stands for the sample point)
            --------------------------------------------------
            |                    /     \                     |
            |(offset direction)  ---|--- (offset direction)  |
            |                    \     /                     |
            ------------------------X-------------------------
            /\                      /\                      /\
            ||                      ||                      ||
            u32StartFrame        u32FrmPos     u32LastFrame(u32EndFrame)

            *****************************************************************

            2. Rewind (X1 and X2 stand for the sample point)
            -------------------------------------------
            |              |\    /\  |   u32FrmPos    |
            |              | \  /  \ |     ||         |
            |              |  \/    \|     \/         |
            ---X1--------------------------X2----------
            /\             /\        /\               /\
            ||             ||        ||               ||
            u32FrmPos  u32EndFrame u32StartFrame u32LastFrame

            In the above graphic, the "\    /\" stands for invalid frame position bound.
                                        \  /  \
                                         \/    \

            Notes:(offset forward direction)
            (1) Not rewind, the right boundary should always be u32LastFrame(u32EndFrame).
            (2) Rewind, sample point range from 0 to u32EndFrame, which is similar with Not rewind, the right boudary is u32EndFrame.
            (3) Rewind, sample point range from u32StartFrame to u32LastFrame.The right boundary as following:
                (a). Right boundary -- u32LastFrame, u32NewPos not over u32LastFrame.
                (b). Right boundary -- u32EndFrame, u32NewPos over u32LastFrame, which rewind to u32EndFrame, so it.

        */

        u32Boundary = u32EndFrame; /* not rewind, the boundary should be the u32EndFrame */

        if( (u32StartFrame >= u32EndFrame) && (u32FrmPos >= u32StartFrame) && (u32FrmPos <= u32LastFrame) )
        {
            if(u32NewPos > u32LastFrame)/* rewind, the frame is like X2 */
            {
                HI_WARN_PVR("Frame:%u rewind, offset:%d, LastFrame:%u\n",u32FrmPos, s32Offset, u32LastFrame);

                /* in this case, frame rewind to the u32EndFrame direction, so the right boundary should be the u32EndFrame */
                if (u32NewPos == u32LastFrame + 1)
                    u32NewPos = 0;
                else
                    u32NewPos -= u32LastFrame;
                HI_WARN_PVR("So subtract LastFrame, new frame:%u\n",u32NewPos);
            }
            else
            {
                /* in this case, frame is not real rewind, so the right boundary should be the u32LastFrame */
                u32Boundary = u32LastFrame;
            }
        }

        /* check the right boundary, make sure the value valid */
        u32NewPos = (u32NewPos > u32Boundary) ? u32Boundary : u32NewPos;
#ifdef DBG_FRAME_POS
        if (u32NewPos == 0)
        {
            HI_WARN_PVR("Seek forward, frame position:%u, u32Boundary = %d u32EndFrame = %d u32LastFrame = %d s32Offset = %d\n",u32NewPos,u32Boundary, u32EndFrame,u32LastFrame, s32Offset);
        }
#endif
    }
    else/* away from the u32FrmPos backward direction toward to u32StartFrame */
    {
        /*
           Notes:(offset backward direction)
            (1) Not rewind, the left boundary should always be u32StartFrame(that is ZERO).
            (2) Rewind, sample point range from u32StartFrame to u32LastFrame, which is similar with Not rewind,
                the left boudary is u32StartFrame(NOT ZERO).
            (3) Rewind, sample point range from 0 to u32EndFrame.The left boundary as following:
                (a). left boundary -- ZERO, u32NewPos more than ZERO.
                (b). left boundary -- u32StartFrame, u32NewPos less than ZERO, which rewind to u32StartFrame, so it.

        */
        u32Boundary = u32StartFrame; /* not rewind, the boundary should be the u32StartFrame */

        if( (u32StartFrame >= u32EndFrame) && (u32FrmPos <= u32EndFrame))
        {
            /* rewind*/
            if((HI_S32)u32NewPos < 0)
            {
                HI_WARN_PVR("Frame:%u rewind, offset is %d, LastFrame:%u, line:%d\n",u32FrmPos, s32Offset, u32LastFrame, __LINE__);

                /* frame rewind to the range u32StartFrame to u32LastFrame, like Frame X1 */
                if ((HI_S32)u32NewPos == -1)
                    u32NewPos = u32LastFrame;
                else
                    u32NewPos = u32LastFrame + u32NewPos;
            }
            else
            {
                /* In this case, the left boundary should be zero, NOT u32StartFrame! */
                u32Boundary = 0;
                HI_WARN_PVR("Seek backward, ref frame:%u, u32EndFrame=%d u32LastFrame=%d s32Offset=%d u32NewPos=%d\n",u32FrmPos,u32Boundary, u32EndFrame,u32LastFrame,s32Offset,u32NewPos);
            }
        }

        /* check the left boundary, make sure the value valid.*/
        u32NewPos = ((HI_S32)u32NewPos < (HI_S32)u32Boundary) ? u32Boundary : u32NewPos;
#ifdef DBG_FRAME_POS
        if (u32NewPos == 0)
        {
            HI_WARN_PVR("Seek backward, frame position:%u, u32FrmPos = %d u32Boundary = %d u32EndFrame = %d u32LastFrame = %d s32Offset = %d\n",u32NewPos,u32FrmPos,u32Boundary, u32EndFrame,u32LastFrame,s32Offset);
        }
#endif
    }

#ifdef DBG_FRAME_POS
    if(abs(s32Offset) > 1)
    {
        HI_ERR_PVR("\033[1;42;34m!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! POSITION IS NOT EQUAL Info start !!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        HI_ERR_PVR("u32StartFrame = %u, u32EndFrame = %u, u32LastFrame = %u\n",u32StartFrame, u32EndFrame, u32LastFrame);
        HI_ERR_PVR("new position = %u u32FrmPos = %u, s32Offset = %d\n",u32NewPos, u32FrmPos, s32Offset);
        HI_ERR_PVR("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! POSITION IS NOT EQUAL Info end!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\033[0m\n");
        g_dbgFlag = MAX_PRINT_TIMES;
        nPrintTimes = 0;
    }

    if(g_dbgFlag >= 0)
    {
        HI_ERR_PVR("\033[1;37;30mNow u32NewPos is %u\n\033[0m", u32NewPos);
        g_dbgFlag--;
    }

    if(nPrintTimes == 0)
    {
        HI_ERR_PVR("\033[1;37;30mNow u32NewPos is %u in line:%d\n\033[0m", u32NewPos, __LINE__);
        nPrintTimes = 1;
    }
#endif

    HI_INFO_PVR("\033[1;37;30m%s now u32NewPos is %u in line:%d\n\033[0m", __func__, u32NewPos, __LINE__);

    return u32NewPos;
}
#endif


/* move s32Offset direction forward or backward, over the end or start, set it to the end or start */
STATIC INLINE HI_VOID PVRIndexCycMoveReadFrame(PVR_INDEX_HANDLE handle, HI_S32 s32Offset)
{
    /* in regardless of rewind, calculate the new position for read by the following interface. */
    handle->u32ReadFrame = PVRIndexCalcNewPos(handle, handle->u32ReadFrame, s32Offset);
}


static HI_S32 PVRIndexWriteIndexCycMgr(PVR_INDEX_HANDLE hIndex, PVR_CYC_MGR_S *pstCycMgr)
{
    PVR_CYC_HEADER_INFO_S stHeaderCycInfo = {0};
    
    HI_ASSERT_RET((PVR_INDEX_HANDLE)NULL != hIndex);
    HI_ASSERT_RET((PVR_CYC_MGR_S *)NULL != pstCycMgr);

    stHeaderCycInfo.u32StartFrame = pstCycMgr->u32StartFrame;
    stHeaderCycInfo.u32IsRewind   = pstCycMgr->bIsRewind;
    stHeaderCycInfo.u32LastFrame  = pstCycMgr->u32LastFrame == -1?0:pstCycMgr->u32LastFrame;
    stHeaderCycInfo.u32EndFrame   = pstCycMgr->u32EndFrame == -1?0:pstCycMgr->u32EndFrame;
    
    if (0 > PVR_WRITE((void *)&stHeaderCycInfo, (size_t)sizeof(PVR_CYC_HEADER_INFO_S),
                             hIndex->s32HeaderFd, (off_t)PVR_GET_HEADER_OFFSET()))
    {
        HI_ERR_PVR("Write cyc info err\n");
        return HI_FAILURE;
    }
    /* after rewind case, update u64ValidSize in PVR_IDX_HEADER_INFO_S */
    PVR_WRITE((void *)&(pstCycMgr->u64MaxCycSize), sizeof(HI_U64),
               hIndex->s32HeaderFd, ((off_t)PVR_GET_HEADER_OFFSET() + (off_t)sizeof(PVR_CYC_HEADER_INFO_S)));
    
    return HI_SUCCESS;
}

/* get the header struct info from index file */
STATIC INLINE HI_S32 PVRIndexGetHeaderInfo(HI_S32 s32Fd, PVR_IDX_HEADER_INFO_S* pstHeadInfo)
{
    HI_U32 u32IndexEntryNum;
    HI_S32 s32TmpOffset;
    HI_S32 s32ReadRet = sizeof(PVR_IDX_HEADER_INFO_S);
    HI_S64 s64IndexFileSize;

    s32ReadRet = PVR_READ(pstHeadInfo, sizeof(PVR_IDX_HEADER_INFO_S), s32Fd, 0);
    if (s32ReadRet != (HI_S32)sizeof(PVR_IDX_HEADER_INFO_S))
    {
        HI_ERR_PVR("read Header info err, ret:%d, fd:%d, size:%d\n", s32ReadRet, s32Fd, s32ReadRet);
        memset(pstHeadInfo, 0, sizeof(PVR_IDX_HEADER_INFO_S));
        return HI_FAILURE;
    }

    if (PVR_INDEX_HEADER_CODE != pstHeadInfo->u32StartCode)
    {
        HI_ERR_PVR("Header info StartCode:0x%x, No head at this file, still play.\n", pstHeadInfo->u32StartCode);
        memset(pstHeadInfo, 0, sizeof(PVR_IDX_HEADER_INFO_S));
        return HI_FAILURE;
    }

    s32TmpOffset = (HI_S32)pvr_lseek(s32Fd, 0, SEEK_CUR);
    if (s32TmpOffset < 0)
    {
        HI_ERR_PVR("can't seek to 0.\n");
        memset(pstHeadInfo, 0, sizeof(PVR_IDX_HEADER_INFO_S));
        return HI_FAILURE;
    }

    s64IndexFileSize = (HI_S64)pvr_lseek(s32Fd, 0, SEEK_END);
    (HI_VOID)pvr_lseek(s32Fd, s32TmpOffset, SEEK_SET);

    u32IndexEntryNum = (HI_U32)(((HI_U64)s64IndexFileSize - (HI_U64)pstHeadInfo->u32HeaderLen)/(HI_U64)sizeof(PVR_INDEX_ENTRY_S));

    if (pstHeadInfo->stCycInfo.u32EndFrame > u32IndexEntryNum)
    {
        HI_WARN_PVR("HeadInfo's CycInfo.EndFrame(%u) > indexEntryNum(%u).\n", 
                     pstHeadInfo->stCycInfo.u32EndFrame, u32IndexEntryNum);
        pstHeadInfo->stCycInfo.u32EndFrame = u32IndexEntryNum;
    }

    if (pstHeadInfo->stCycInfo.u32LastFrame > u32IndexEntryNum)
    {
        HI_WARN_PVR("HeadInfo's CycInfo.LastFrame(%u) > indexEntryNum(%u).\n", 
                     pstHeadInfo->stCycInfo.u32LastFrame, u32IndexEntryNum);
        pstHeadInfo->stCycInfo.u32LastFrame = u32IndexEntryNum;
    }

    return HI_SUCCESS;
}

/* read the header info, and allowed without header info */
static HI_S32 PVRIndexReadHeaderInfo(PVR_INDEX_HANDLE handle)
{
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo;

    memset(&stIdxHeaderInfo, 0, sizeof(PVR_IDX_HEADER_INFO_S));

    /* means not found the header info in this index file */
    if (HI_SUCCESS != PVRIndexGetHeaderInfo(handle->s32HeaderFd, &stIdxHeaderInfo))
    {
        return HI_FAILURE;
    }
    else
    {
        handle->u32IdxStartOffsetLen =  stIdxHeaderInfo.u32HeaderLen;
        handle->stCycMgr.bIsRewind = (HI_BOOL)(stIdxHeaderInfo.stCycInfo.u32IsRewind);
        handle->stCycMgr.u32StartFrame = stIdxHeaderInfo.stCycInfo.u32StartFrame;
        handle->stCycMgr.u32EndFrame = stIdxHeaderInfo.stCycInfo.u32EndFrame;
        handle->stCycMgr.u32LastFrame = stIdxHeaderInfo.stCycInfo.u32LastFrame;
        handle->stCycMgr.u64MaxCycSize = stIdxHeaderInfo.u64ValidSize;

#ifdef HI_PVR_L2_CACHE_SUPPORT
        memcpy(&handle->stFileCycInfo, &stIdxHeaderInfo.stCycInfo, sizeof(PVR_CYC_HEADER_INFO_S));
#endif

        handle->u32ReadFrame = handle->stCycMgr.u32StartFrame;
    }

    return HI_SUCCESS;
}


static HI_S32 PVRIndexWriteIndexInfo(PVR_INDEX_HANDLE hIndex, PVR_REC_INDEX_INFO_S *pstIdxInfo)
{
    HI_S32 s32WriteRet;
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo = {0};

    if (HI_SUCCESS != PVRIndexGetHeaderInfo(hIndex->s32HeaderFd, &stIdxHeaderInfo))
    {
        HI_ERR_PVR("Can't get index header info.\n");
        return HI_FAILURE;
    }
    
    s32WriteRet = PVR_WRITE(pstIdxInfo, 
                            sizeof(PVR_REC_INDEX_INFO_S), 
                            hIndex->s32HeaderFd, 
                            PVR_GET_IDX_INFO_OFFSET(stIdxHeaderInfo));

    if (s32WriteRet != sizeof(PVR_REC_INDEX_INFO_S))
    {
        HI_ERR_PVR("Write index info fail ret=0x%x\n", s32WriteRet);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


/* initialize */
STATIC INLINE HI_VOID PVRIndexSetDftAttr(PVR_INDEX_HANDLE handle)
{
    HI_INFO_PVR("index set default attr.\n");

    handle->u64GlobalOffset = 0;
    handle->u64OverflowOffset = 0;
    handle->u64FileSizeGlobal = 0;
    handle->u32PauseFrame  = 0;
    handle->u64PauseOffset = PVR_INDEX_PAUSE_INVALID_OFFSET;
    handle->u32ReadFrame  = 0;
    handle->u32WriteFrame = 0;
    handle->u16RecLastIframe = PVR_INDEX_INVALID_I_FRAME_OFFSET;
    handle->u32RecLastValidPtsMs = PVR_INDEX_INVALID_PTSMS;
    handle->u32RecPicParser = 0xffffffff;
    handle->u32RecFirstFrmTimeMs = 0;

    handle->s32WriteFd = PVR_FILE_INVALID_FILE;
    handle->s32ReadFd = PVR_FILE_INVALID_FILE;
    handle->s32SeekFd = PVR_FILE_INVALID_FILE;
    handle->s32HeaderFd = PVR_FILE_INVALID_FILE;
    handle->u32IdxStartOffsetLen = 0;
    memset(&handle->stCurPlayFrame, 0, sizeof(PVR_INDEX_ENTRY_S) );
    memset(&handle->stCurRecFrame, 0, sizeof(PVR_INDEX_ENTRY_S) );
    memset(&handle->stIndexFileAttr, 0, sizeof(HI_UNF_PVR_FILE_ATTR_S) );
    memset(&handle->stCycMgr, 0, sizeof(PVR_CYC_MGR_S));
    memset(handle->szIdxFileName, 0, PVR_MAX_FILENAME_LEN);
}

static HI_S32 PVRCacheWriteIdx(PVR_INDEX_HANDLE handle, HI_U8* pu8Data, HI_U32 u32Len, HI_U32 u32Offset,
                               HI_BOOL bDirectFlag, HI_BOOL* bWriteFlag)
{
    HI_U32 u32SaveSz;

    PVR_IDX_CACHE_LOCK(&(handle->stIdxWriteCache.stCacheMutex));

    if (handle->stIdxWriteCache.u32BufferLen == 0)/*no cache buffer*/
    {
        PVR_WRITE_INDEX(u32SaveSz, u32Len, pu8Data, handle->s32WriteFd,u32Offset, handle);
        *bWriteFlag = HI_TRUE;
    }
    else if (bDirectFlag)/*Direct write file,not use cache*/
    {
        if (handle->stIdxWriteCache.u32UsedSize)/*have data cache*/
        {
            PVR_WRITE_INDEX(u32SaveSz, handle->stIdxWriteCache.u32UsedSize,handle->stIdxWriteCache.pu8Addr,
                            handle->s32WriteFd, handle->stIdxWriteCache.u32StartOffset, handle);
            PVR_WRITE_INDEX(u32SaveSz, u32Len, pu8Data, handle->s32WriteFd, u32Offset, handle);
            *bWriteFlag = HI_TRUE;
            handle->stIdxWriteCache.u32UsedSize = 0;
            handle->stIdxWriteCache.u32StartOffset = 0;

        }
        else/*no cached data*/
        {
            PVR_WRITE_INDEX(u32SaveSz, u32Len, pu8Data, handle->s32WriteFd, u32Offset, handle);
            *bWriteFlag = HI_TRUE;
        }
    }
    else
    {
        /*  
        1. Data offset jump,may be means idx rewind.
        2. Cache buffer not enough
        should flush cache first(write all cached data to file),the write new data into cache.
        */
        //1.flush cache first(write all cached data to file)
        if ((u32Offset != (handle->stIdxWriteCache.u32StartOffset + handle->stIdxWriteCache.u32UsedSize))
            ||((handle->stIdxWriteCache.u32BufferLen - handle->stIdxWriteCache.u32UsedSize) < u32Len)) 
            
        {
            //lint -e774
            PVR_WRITE_INDEX(u32SaveSz, handle->stIdxWriteCache.u32UsedSize,handle->stIdxWriteCache.pu8Addr, 
                            handle->s32WriteFd,handle->stIdxWriteCache.u32StartOffset, handle);
            *bWriteFlag = HI_TRUE;
            handle->stIdxWriteCache.u32UsedSize = 0;
            handle->stIdxWriteCache.u32StartOffset = 0;
            //lint +e774
        }
        //2. write new data into cache
        memcpy(handle->stIdxWriteCache.pu8Addr + handle->stIdxWriteCache.u32UsedSize,pu8Data,u32Len);
        if(handle->stIdxWriteCache.u32UsedSize == 0)//cache is empty
        {
           handle->stIdxWriteCache.u32StartOffset = u32Offset;
        }
        handle->stIdxWriteCache.u32UsedSize +=  u32Len;
    }
    PVR_IDX_CACHE_UNLOCK(&(handle->stIdxWriteCache.stCacheMutex));

    PVR_IDX_CACHE_LOCK(&(handle->stIdxReadCache.stCacheMutex));
    if (PVR_Index_IfOffsetReadCache(handle,u32Offset,u32Len))//write data been cached or appears in cache
    {
        handle->stIdxReadCache.u32UsedSize = 0;//invalid the read cache buffer
    }
    PVR_IDX_CACHE_UNLOCK(&(handle->stIdxReadCache.stCacheMutex));

    return HI_SUCCESS;
}

HI_S32 PVR_Index_FlushIdxWriteCache(PVR_INDEX_HANDLE    handle)
{
    HI_U32 u32SaveSz;
    if (handle->stIdxWriteCache.u32BufferLen == 0)
    {
        return HI_SUCCESS;
    }
    PVR_IDX_CACHE_LOCK(&(handle->stIdxWriteCache.stCacheMutex));
    if (handle->stIdxWriteCache.u32UsedSize)
    {
        //lint -e774
        PVR_WRITE_INDEX(u32SaveSz, handle->stIdxWriteCache.u32UsedSize,handle->stIdxWriteCache.pu8Addr, 
                            handle->s32WriteFd,handle->stIdxWriteCache.u32StartOffset, handle);
        handle->stIdxWriteCache.u32UsedSize = 0;
        handle->stIdxWriteCache.u32StartOffset = 0;
        memset(handle->stIdxWriteCache.pu8Addr, 0x5a, handle->stIdxWriteCache.u32BufferLen);
        //lint +e774
    }
    PVR_IDX_CACHE_UNLOCK(&(handle->stIdxWriteCache.stCacheMutex));
    return HI_SUCCESS;
}
/*check if the offset in cache:1 in cache,0 not in cache*/
HI_S32 PVR_Index_IfOffsetInWriteCache(PVR_INDEX_HANDLE  handle,HI_U32 u32Offset,HI_U32 u32Size)
{
    if (handle->stIdxWriteCache.u32BufferLen == 0)
    {
        return 0;
    }
    PVR_IDX_CACHE_LOCK(&(handle->stIdxWriteCache.stCacheMutex));
    if (handle->stIdxWriteCache.u32BufferLen != 0 && handle->stIdxWriteCache.u32UsedSize)
    {
        if ((u32Offset >= handle->stIdxWriteCache.u32StartOffset && 
            u32Offset <= (handle->stIdxWriteCache.u32StartOffset + handle->stIdxWriteCache.u32UsedSize)) ||
            (u32Offset < handle->stIdxWriteCache.u32StartOffset && 
            ((u32Offset+u32Size) > handle->stIdxWriteCache.u32StartOffset)))
        {
            PVR_IDX_CACHE_UNLOCK(&(handle->stIdxWriteCache.stCacheMutex));
            return 1;
        }
    }
    PVR_IDX_CACHE_UNLOCK(&(handle->stIdxWriteCache.stCacheMutex));
    return 0;
}

/*check if the offset in read cache:1 all in cache,0 not in cache,2 offset in cache*/
static HI_S32 PVR_Index_IfOffsetReadCache(PVR_INDEX_HANDLE handle, HI_U32 u32Offset, HI_U32 u32Size)
{
    if (handle->stIdxReadCache.u32BufferLen && handle->stIdxReadCache.u32UsedSize)/*have data cached*/
    {
        if ((u32Offset >= handle->stIdxReadCache.u32StartOffset) && 
            ((u32Offset - handle->stIdxReadCache.u32StartOffset) <= handle->stIdxReadCache.u32UsedSize))
        {
            if ((u32Offset - handle->stIdxReadCache.u32StartOffset + u32Size) <= handle->stIdxReadCache.u32UsedSize)
            {
                return 1;
            }
            return 2;
        }
    }
    return 0;
}


static ssize_t PVRCacheReadIdx(PVR_INDEX_HANDLE handle, PVR_FILE fd, HI_VOID* pData, size_t size, 
                               HI_U32 u32Offset, HI_U32 u32DirectFlag)
{
    ssize_t readNum = 0;
    HI_S32 s32CachedFlag;
    HI_S32 s32CacheStartReadOffset;
    HI_U8* pDataAddr;
    static HI_U32 u32CacheNum = 0,NotCacheNum = 0;
    
    PVR_IDX_CACHE_LOCK(&(handle->stIdxReadCache.stCacheMutex));
    if (handle->stIdxReadCache.u32BufferLen == 0 || u32DirectFlag || 
        size > handle->stIdxReadCache.u32BufferLen)/*read directly*/
    {
        PVR_READ_INDEX_DIRECTLY(readNum, pData, size, fd, (off_t)u32Offset, handle);
        NotCacheNum++;
    }
    else
    {
        s32CachedFlag = PVR_Index_IfOffsetReadCache(handle, u32Offset,size);
        if (s32CachedFlag == 1)/*cached*/
        {
            pDataAddr = handle->stIdxReadCache.pu8Addr + u32Offset - handle->stIdxReadCache.u32StartOffset;
            memcpy(pData,pDataAddr,size);
            readNum = size;
            u32CacheNum ++;
        }
        else/*not cached*/
        {
            /*
            flush cache buffer:
            --------------------------------------------------
            |                    /     \                     |
            |       offset in middle of cache buffer         |
            |                    \     /                     |
            ------------------------X-------------------------
            /\                      /\                      /\
            ||                      ||                      ||
            cache start        offset          cache end
            */
            s32CacheStartReadOffset = (HI_S32)(u32Offset - (handle->stIdxReadCache.u32BufferLen / 2));
            if (s32CacheStartReadOffset < 0)
            {
                s32CacheStartReadOffset = 0;
            }

            PVR_READ_INDEX_DIRECTLY(readNum, handle->stIdxReadCache.pu8Addr, handle->stIdxReadCache.u32BufferLen, 
                                    fd, (off_t)s32CacheStartReadOffset, handle);
            handle->stIdxReadCache.u32UsedSize = readNum;
            handle->stIdxReadCache.u32StartOffset = s32CacheStartReadOffset;  
            s32CachedFlag = PVR_Index_IfOffsetReadCache(handle, u32Offset, size);/*check again*/
            if (s32CachedFlag == 1)
            {
                pDataAddr = handle->stIdxReadCache.pu8Addr + u32Offset - handle->stIdxReadCache.u32StartOffset;
                memcpy(pData,pDataAddr,size);
                readNum = size;
                NotCacheNum++;
            }
            else/*try read directly */
            {
                HI_WARN_PVR("idx read cache not works!\n");
                PVR_READ_INDEX_DIRECTLY(readNum, pData, size, fd, (off_t)u32Offset, handle); 
                NotCacheNum++;
            }
        }         
    }
    if ((!(u32CacheNum%5000 ) && u32CacheNum != 0) || (!(NotCacheNum %5000) && NotCacheNum != 0))
    {
        HI_INFO_PVR(">>>> u32CacheNum:%d,NotCacheNum:%d\n",u32CacheNum,NotCacheNum);
    }
    PVR_IDX_CACHE_UNLOCK(&(handle->stIdxReadCache.stCacheMutex));
    return readNum;
}


static HI_S32 PVRIndexGetFBwardIPBFrameNum(PVR_INDEX_HANDLE hIndex,
                                           PVR_CYC_MGR_S *pstCycMgr,
                                           HI_U32 u32Direction, 
                                           HI_U32 u32FrameType, 
                                           HI_U32 u32CurFrameNum, 
                                           HI_U32 *pu32NextFrameNum)
{
    HI_S32 s32NextFrameNum = (HI_S32)u32CurFrameNum;
    HI_S32 ret = HI_SUCCESS;
    PVR_INDEX_ENTRY_S stIdxEntry = {0}; 
    
    HI_ASSERT_RET(hIndex != NULL);
    HI_ASSERT_RET(pstCycMgr != NULL);
    HI_ASSERT_RET(pu32NextFrameNum != NULL);

    if (HI_TRUE != PVRIndexIsFrameValid(u32CurFrameNum, pstCycMgr))
    {
        HI_ERR_PVR("input frame number %d is invalid start=%d end=%d last=%d.\n", 
                    u32CurFrameNum,
                    pstCycMgr->u32StartFrame,
                    pstCycMgr->u32EndFrame,
                    pstCycMgr->u32LastFrame);
        return HI_FAILURE;
    }

    while (1)
    {
        if (0 == u32Direction)
            s32NextFrameNum--;
        else
            s32NextFrameNum++;

        if (pstCycMgr->u32EndFrame <= pstCycMgr->u32StartFrame)
        {
            if (0 == u32Direction)
                s32NextFrameNum = (0 > s32NextFrameNum) ? (HI_S32)pstCycMgr->u32LastFrame : s32NextFrameNum;
            else
                s32NextFrameNum = (pstCycMgr->u32LastFrame < (HI_U32)s32NextFrameNum) ? 0 : s32NextFrameNum;
        }

        if (HI_TRUE != PVRIndexIsFrameValid(s32NextFrameNum, &hIndex->stCycMgr))
        {
            HI_WARN_PVR("next frame number %d is invalid. start=%d end=%d last=%d\n",
                        s32NextFrameNum,
                        pstCycMgr->u32StartFrame,
                        pstCycMgr->u32EndFrame,
                        pstCycMgr->u32LastFrame);
            return PVR_INDEX_ERR_INVALID;
        }

        ret = PVRIndexGetEntryByNum(hIndex, &stIdxEntry, s32NextFrameNum);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("PVRIndexGetEntryByNum fail frame=%d start=%d end=%d last=%d ret=%#x.\n",
                        s32NextFrameNum,
                        pstCycMgr->u32StartFrame,
                        pstCycMgr->u32EndFrame,
                        pstCycMgr->u32LastFrame,
                        ret);
            return HI_FAILURE;
        }

        /* IPB frame, and not found the frame upflow flag*/
        if (u32FrameType == PVR_INDEX_FRAME_I)
        {
            if (PVR_INDEX_is_Iframe(&stIdxEntry))
                break;
        }
        else if (u32FrameType == PVR_INDEX_FRAME_P)
        {
            if (PVR_INDEX_is_Pframe(&stIdxEntry))
                break;
        }
        else if (u32FrameType == PVR_INDEX_FRAME_B)
        {
            if (PVR_INDEX_is_Bframe(&stIdxEntry))
                break;
        }
        else
            return HI_FAILURE;
    }
    
    *pu32NextFrameNum = (HI_U32)s32NextFrameNum;
    return HI_SUCCESS;
}

#if 0
static HI_U32 PVRIndecCalcInvalidIdxLen(PVR_INDEX_HANDLE hIndex, HI_U64 *pu64Len)
{
    HI_U32 u32End, u32NextEnd, u32Start, u32Last;
    ssize_t readNum;
    PVR_INDEX_ENTRY_S stNextEndEntry = {0};
    PVR_INDEX_ENTRY_S stStartEntry = {0};

    u32Start   = hIndex->stCycMgr.u32StartFrame;
    u32End     = hIndex->stCycMgr.u32EndFrame;
    u32Last    = hIndex->stCycMgr.u32LastFrame;
    u32NextEnd = PVR_IDX_NEXT_POS_IN_CYC(u32End,(u32Last + 1));

//ֱ�Ӷ�ȡend����һ��index����index������Ч���䣬����ֱ�Ӵ��ļ��ж�ȡ
    readNum = PVR_READALL(&stNextEndEntry, sizeof(PVR_INDEX_ENTRY_S), hIndex->s32ReadFd,
                          (off_t)PVR_IDX_TRANSFER_FRM_TO_OFFSET(u32NextEnd, hIndex));
    if (readNum != (ssize_t)sizeof(PVR_INDEX_ENTRY_S))
    {
        if (-1 == readNum)
        {
            HI_WARN_PVR("read next end index %d error, end %d\n", u32NextEnd, u32End);
            return HI_ERR_PVR_FILE_CANT_READ;
        }
        else
        {
            HI_INFO_PVR("read nextend failed, cur and next is same: S:%d, E:%d, L:%d N:%d\n", 
                        hIndex->stCycMgr.u32StartFrame, hIndex->stCycMgr.u32EndFrame,
                        hIndex->stCycMgr.u32LastFrame, u32NextEnd);
            return HI_ERR_PVR_FILE_TILL_END;
        }
    }

//��ȡstart��index
    PVR_READ_INDEX(readNum, &stStartEntry, sizeof(PVR_INDEX_ENTRY_S), hIndex->s32ReadFd,
                   (u32Start * sizeof(PVR_INDEX_ENTRY_S)), hIndex);
    if (readNum != (ssize_t)sizeof(PVR_INDEX_ENTRY_S))
    {
        if (-1 == readNum)
        {
            HI_WARN_PVR("read index error: ");
            return HI_ERR_PVR_FILE_CANT_READ;
        }
        else
        {
            HI_INFO_PVR("read to end, cur and next is same: S:%d, E:%d, L:%d N:%d\n", 
                        hIndex->stCycMgr.u32StartFrame, hIndex->stCycMgr.u32EndFrame,
                        hIndex->stCycMgr.u32LastFrame, u32NextEnd);
            return HI_ERR_PVR_FILE_TILL_END;
        }
    }

//��Ч�Լ��
    if (stStartEntry.u64GlobalOffset - stNextEndEntry.u64GlobalOffset <= 0)
    {
        HI_ERR_PVR("Start Goffset %llx small than nextend Goffset %llx\n",
                   stStartEntry.u64GlobalOffset, stNextEndEntry.u64GlobalOffset);
        return HI_FAILURE;
    }

    *pu64Len = stStartEntry.u64GlobalOffset - stNextEndEntry.u64GlobalOffset;
    return HI_SUCCESS;
}
#endif

static HI_VOID PVRIndexCheckReadFrmValidWhenTimeshift(PVR_INDEX_HANDLE hIndex)
{
    if (hIndex->bIsPlay == HI_FALSE)
        return ;

    if (hIndex->bRecReachPlay == HI_TRUE)
    {
        return ;
    }

    if (PVRIndexIsFrameValid(hIndex->u32ReadFrame, &hIndex->stCycMgr) == 0)
    {
        HI_WARN_PVR("Rec cover play!!!! S/E/L/R:%d/%d/%d/%d\n",
                     hIndex->stCycMgr.u32StartFrame, hIndex->stCycMgr.u32EndFrame,
                     hIndex->stCycMgr.u32LastFrame,hIndex->u32ReadFrame);
        hIndex->bRecReachPlay = HI_TRUE;
    }
}


static HI_BOOL PVRIndexCheckRewind(PVR_INDEX_HANDLE hIndex,
                                   PVR_CYC_MGR_S *pstCycMgr,
                                   PVR_INDEX_ENTRY_S *pstIdxEntry)
{
    if (PVR_INDEX_REWIND_BY_TIME == pstCycMgr->enRewindType)
    {
        /*�����ǰ��ʱ����Ʋ���index���ts�����ƴ���ʵ�ʷ�����
          index��globaloffset����TimeRewindMaxSizeʱ�����Է���false*/
        if (hIndex->bTimeRewinding == HI_TRUE)
        {
            return HI_FALSE;
        }
        
        if((pstIdxEntry->u32DisplayTimeMs - (pstCycMgr->u32MaxCycTimeInMs * pstCycMgr->u32CycTimes)) > pstCycMgr->u32MaxCycTimeInMs)
        {
            return HI_TRUE;
        }
    }
    else
    {
        if (pstIdxEntry->u64Offset > pstCycMgr->u64MaxCycSize)
        {
            return HI_TRUE;
        }
    }

    return HI_FALSE;
}


static INLINE HI_VOID PVRIndexAssignIndexEntry(PVR_INDEX_HANDLE hIndex,
                                               const HI_UNF_DMX_REC_INDEX_S *pstDmxIndexInfo,
                                               PVR_INDEX_ENTRY_S *pstIdxEntry)
{
    HI_U32 u32CurFrmTimeMs = 0, u32TimeNow = 0;

    hIndex->u64GlobalOffset = pstDmxIndexInfo->u64GlobalOffset - hIndex->u64DeltaGlobalOffset;
    hIndex->u32DmxClkTimeMs = pstDmxIndexInfo->u32DataTimeMs;

    if (PVR_INDEX_INVALID_I_FRAME_OFFSET != hIndex->u16RecLastIframe)
    {
        hIndex->u16RecLastIframe++;
    }
    else
    {
        hIndex->u16RecLastIframe = 0;
    }

    if (HI_UNF_FRAME_TYPE_I == pstDmxIndexInfo->enFrameType)
    {
        hIndex->u16RecLastIframe = 0;
    }

    if ((PVR_INDEX_INVALID_PTSMS != pstDmxIndexInfo->u32PtsMs) && (0 != pstDmxIndexInfo->u32PtsMs))
    {
        hIndex->u32RecLastValidPtsMs = pstDmxIndexInfo->u32PtsMs;
    }

    if ((0 == hIndex->stCycMgr.u32CycTimes) && (-1 == hIndex->stCycMgr.u32LastFrame))
    {
        hIndex->u32RecFirstFrmTimeMs = hIndex->u32DmxClkTimeMs;
        u32CurFrmTimeMs = 0;
        pstIdxEntry->u32DisplayTimeMs = 0;
    }
    else
    {
        u32TimeNow = hIndex->u32DmxClkTimeMs;
        if (u32TimeNow >= hIndex->stCurRecFrame.u32DisplayTimeMs)
        {
            u32CurFrmTimeMs = u32TimeNow - hIndex->u32RecFirstFrmTimeMs;
        }
        else
        {
            HI_WARN_PVR("The time rewinded firstTimeMs(%u)\n", hIndex->u32RecFirstFrmTimeMs);
            if ((hIndex->u32FRollTime*PVR_INDEX_SCD_WRAP_MS + u32TimeNow) < hIndex->stCurRecFrame.u32DisplayTimeMs)
            {
                hIndex->u32FRollTime++;
            }
            u32CurFrmTimeMs = hIndex->u32FRollTime*PVR_INDEX_SCD_WRAP_MS - hIndex->u32RecFirstFrmTimeMs + u32TimeNow;
            HI_WARN_PVR("Cur indexEntry.u32DisplayTimeMs = %u set the reference time is %u, displayTimeMs increase = %u\n",
                        pstIdxEntry->u32DisplayTimeMs, u32TimeNow,u32CurFrmTimeMs);
        }
    }

    pstIdxEntry->u16FrameTypeAndGop = ((pstDmxIndexInfo->enFrameType) & 0x3) << 14 | (hIndex->u16RecLastIframe & 0x3fff);
    pstIdxEntry->u64GlobalOffset    = pstDmxIndexInfo->u64GlobalOffset - hIndex->u64DeltaGlobalOffset + hIndex->u64OverflowOffset;
    pstIdxEntry->u64Offset          = pstDmxIndexInfo->u64GlobalOffset - hIndex->u64DeltaGlobalOffset + hIndex->u64OverflowOffset;
    pstIdxEntry->u32FrameSize       = pstDmxIndexInfo->u32FrameSize;
    pstIdxEntry->u32PtsMs           = hIndex->u32RecLastValidPtsMs;
    pstIdxEntry->u16IndexType       = (HI_U16)hIndex->enIndexType;
    pstIdxEntry->u161stFrameOfTT    = 0;
    pstIdxEntry->s32CycTimes        = hIndex->stCycMgr.u32CycTimes;

    /* In case the recording data lose, compensate the current time */
    if ((u32CurFrmTimeMs - hIndex->u32LastDispTime) >= 1000)
    {
        hIndex->u32DeltaDispTimeMs += (u32CurFrmTimeMs - hIndex->u32LastDispTime);
    }

    if (!hIndex->stTimeStamp.bNeedAdjustByPts)
    {
        pstIdxEntry->u32DisplayTimeMs = u32CurFrmTimeMs - hIndex->u32DeltaDispTimeMs;
    }
    else
    {
        pstIdxEntry->u32DisplayTimeMs = PVRIndexGetRecTimeStamp(hIndex, pstDmxIndexInfo);
    }
    
    hIndex->u32LastDispTime = u32CurFrmTimeMs;
}


/*����Ҫ��u32PreCurFrmΪI֡�����ⲿ��֤��Ч�� */
static HI_VOID PVRIndexSubGopInfo(PVR_INDEX_HANDLE hIndex,
                                     PVR_REC_INDEX_INFO_S *pstRecIdxInfo, 
                                     HI_U32 u32PreCurFrm)
{
    HI_U32 u32GopSizeSeg;
    PVR_INDEX_ENTRY_S stPreEntryTmp = {0};

    pstRecIdxInfo->stIdxInfo.u32GopTotalNum--;
    if (HI_SUCCESS == PVRIndexGetEntryByNum(hIndex, &stPreEntryTmp, u32PreCurFrm))
    {
        u32GopSizeSeg = ((stPreEntryTmp.u16FrameTypeAndGop & 0x3fff) + 1)/10;
        u32GopSizeSeg = (u32GopSizeSeg > 12) ? 12 : u32GopSizeSeg;
        pstRecIdxInfo->stIdxInfo.u32GopSizeInfo[u32GopSizeSeg]--;
    }

    return;
}

static HI_VOID PVRIndexAddGopInfo(PVR_INDEX_HANDLE hIndex,
                                     PVR_REC_INDEX_INFO_S *pstRecIdxInfo,
                                     PVR_INDEX_ENTRY_S *pstIdxEntry)
{
    HI_U32 u32GopSizeSeg;

    pstRecIdxInfo->stIdxInfo.u32GopTotalNum++;

    if (pstRecIdxInfo->u32LastGopSize > pstRecIdxInfo->stIdxInfo.u32MaxGopSize)
    {
        pstRecIdxInfo->stIdxInfo.u32MaxGopSize = pstRecIdxInfo->u32LastGopSize;
    }

    if (0 != pstRecIdxInfo->u32LastGopSize)
    {
        u32GopSizeSeg = (pstRecIdxInfo->u32LastGopSize/10);
        u32GopSizeSeg = (u32GopSizeSeg > 12) ? 12 : u32GopSizeSeg;
        pstRecIdxInfo->stIdxInfo.u32GopSizeInfo[u32GopSizeSeg]++;
    }

    return;
}


static INLINE HI_VOID PVRIndexUpdateTotalFrmNum(PVR_REC_INDEX_INFO_S *pstRecIdxInfo,
                                                PVR_CYC_MGR_S *pstCycMgr)
{
    pstRecIdxInfo->u32MagicWord = PVR_REC_INDEX_MAGIC_WORD;

    if (0 != pstCycMgr->u32CycTimes)
    {
        pstRecIdxInfo->stIdxInfo.u32FrameTotalNum = pstCycMgr->u32LastFrame -
                                                    (pstCycMgr->u32StartFrame + pstCycMgr->u32LastFrame - pstCycMgr->u32EndFrame)
                                                    %pstCycMgr->u32LastFrame;
    }
    else
    {
        pstRecIdxInfo->stIdxInfo.u32FrameTotalNum = pstCycMgr->u32LastFrame + 1;
    }
}


static HI_VOID PVRIndexPushStartFrame(PVR_INDEX_HANDLE hIndex, 
                                      PVR_CYC_MGR_S *pstCycMgr,
                                      PVR_REC_INDEX_INFO_S *pstIdxInfo,
                                      HI_U64 u64NextEndOffset)
{
    HI_U32 u32NextIFrm;
    HI_S32 s32Ret;
    PVR_INDEX_ENTRY_S stEntryTmp = {0};

    s32Ret = PVRIndexGetFBwardIPBFrameNum(hIndex, pstCycMgr ,1, PVR_INDEX_FRAME_I, pstCycMgr->u32StartFrame, &u32NextIFrm);
    if (HI_SUCCESS == s32Ret)
    {
        PVRIndexSubGopInfo(hIndex, pstIdxInfo, PVR_IDX_PREV_POS_IN_CYC(u32NextIFrm,(pstCycMgr->u32LastFrame + 1)));
        pstCycMgr->u32StartFrame = u32NextIFrm;
        s32Ret = PVRIndexGetEntryByNum(hIndex , &stEntryTmp, pstCycMgr->u32StartFrame);
        if (s32Ret == HI_SUCCESS)
        {
            pstCycMgr->u64StartFrameOffset = stEntryTmp.u64Offset;
        }
        else
        {
            HI_ERR_PVR("!!!Get start idxentry failed ret %x, s/e/l %d/%d/%d\n",
                       s32Ret, pstCycMgr->u32StartFrame, pstCycMgr->u32EndFrame, pstCycMgr->u32LastFrame);
            pstCycMgr->u64StartFrameOffset = u64NextEndOffset;
        }
    }
    else
    {
        HI_ERR_PVR("!!!!Get next I frm failed ret %x, s/e/l %d/%d/%d\n",
                   s32Ret, pstCycMgr->u32StartFrame, pstCycMgr->u32EndFrame, pstCycMgr->u32LastFrame);
        pstCycMgr->u32StartFrame += 1;
        pstCycMgr->u64StartFrameOffset = u64NextEndOffset;
    }
}

static HI_VOID PVRIndexUpdateCycMgrAndRecInfoWhenRewind(PVR_INDEX_HANDLE hIndex, 
                                                        PVR_CYC_MGR_S *pstCycMgr, 
                                                        PVR_REC_INDEX_INFO_S * pstIdxInfo, 
                                                        PVR_INDEX_ENTRY_S *pstEndEntry)
{
    HI_U64 u64NextEndOffset;

    u64NextEndOffset = pstEndEntry->u64Offset + pstEndEntry->u32FrameSize;

    pstCycMgr->u32CycTimes++;
    pstCycMgr->u32LastFrame = pstCycMgr->u32EndFrame;

    if (pstCycMgr->u32CycTimes == 1)
    {
        PVRIndexPushStartFrame(hIndex, pstCycMgr, pstIdxInfo, u64NextEndOffset);
    }
    else
    {
        //�˴��봦�����ʱ�С��endС��start�����º����ж�ʧ�ܣ�startԽ������
        if (pstCycMgr->u32StartFrame >= pstCycMgr->u32LastFrame)
        {
            pstCycMgr->u32StartFrame = 0;
            PVRIndexPushStartFrame(hIndex, pstCycMgr, pstIdxInfo, u64NextEndOffset);
        }

        //we reserve 2 frames for this case:
        //read is equal to start, and we are pushing start at the monent. It will cause  the function of checking read invalide fail
        if ((pstCycMgr->u32StartFrame < 2) ||
            (pstCycMgr->u32StartFrame == PVR_IDX_NEXT_N_POS_IN_CYC(pstCycMgr->u32EndFrame, 2, (pstCycMgr->u32LastFrame + 1))) ||
            (PVRIndexCheckEndOffsetCoverStartOffset(pstEndEntry->u64Offset, u64NextEndOffset, pstCycMgr->u64StartFrameOffset, pstCycMgr->u64MaxCycSize)))
        {
            do
            {
                PVRIndexPushStartFrame(hIndex, pstCycMgr, pstIdxInfo, u64NextEndOffset);
            }while(PVRIndexCheckEndOffsetCoverStartOffset(pstEndEntry->u64Offset,u64NextEndOffset, 
                                                          pstCycMgr->u64StartFrameOffset, pstCycMgr->u64MaxCycSize));
        }
    }

    pstCycMgr->u32EndFrame = 0;
    PVRIndexCheckReadFrmValidWhenTimeshift(hIndex);

    if (PVR_INDEX_is_Iframe(pstEndEntry))
    {
        PVRIndexAddGopInfo(hIndex, pstIdxInfo, pstEndEntry);
    }

    pstIdxInfo->u32LastGopSize = (pstEndEntry->u16FrameTypeAndGop & 0x3fff) + 1;

    PVRIndexUpdateTotalFrmNum(pstIdxInfo, pstCycMgr);

    HI_INFO_PVR("Chn %d update cycmgr cyctimes %3d start %8d end %8d last %8d\n",
                hIndex->u32RecPicParser,
                pstCycMgr->u32CycTimes, 
                pstCycMgr->u32StartFrame, 
                pstCycMgr->u32EndFrame,
                pstCycMgr->u32LastFrame);
}


static HI_VOID PVRIndexUpdateCycMgrAndRecInfoWhenNotRewind(PVR_INDEX_HANDLE hIndex, 
                                                           PVR_CYC_MGR_S *pstCycMgr, 
                                                           PVR_REC_INDEX_INFO_S * pstIdxInfo,
                                                           PVR_INDEX_ENTRY_S *pstEndEntry)
{
    HI_U64 u64NextEndOffset;

    u64NextEndOffset = pstEndEntry->u64Offset + pstEndEntry->u32FrameSize;

    //�ǻ���ʱ��start  ������ֻ�ƶ�end  ��last
    if (pstCycMgr->u32CycTimes == 0)
    {
        if (pstCycMgr->u32EndFrame == -1)
        {
            pstCycMgr->u32EndFrame = 0;
            pstCycMgr->u32LastFrame = 0;
        }
        else
        {
            pstCycMgr->u32EndFrame++;
            pstCycMgr->u32LastFrame++;
        }
    }
    else
    {
        //����������ƶ�start   
        //1. end  ָ���offset  �Ḳ��prestart  ָ���offset
        //2. end  ����prestart
        if ((pstCycMgr->u32StartFrame == PVR_IDX_NEXT_N_POS_IN_CYC(pstCycMgr->u32EndFrame,2,(pstCycMgr->u32LastFrame + 1))) ||
            (PVRIndexCheckEndOffsetCoverStartOffset(pstEndEntry->u64Offset, u64NextEndOffset, 
                                                    pstCycMgr->u64StartFrameOffset, pstCycMgr->u64MaxCycSize)))
        {
            do
            {
                PVRIndexPushStartFrame(hIndex, pstCycMgr, pstIdxInfo, u64NextEndOffset);
            }while(PVRIndexCheckEndOffsetCoverStartOffset(pstEndEntry->u64Offset,u64NextEndOffset, 
                                                          pstCycMgr->u64StartFrameOffset, pstCycMgr->u64MaxCycSize));
        }

        pstCycMgr->u32EndFrame++;
        if (pstCycMgr->u32LastFrame < pstCycMgr->u32EndFrame)
        {
            pstCycMgr->u32LastFrame++;
        }
    }

    PVRIndexCheckReadFrmValidWhenTimeshift(hIndex);

    if (PVR_INDEX_is_Iframe(pstEndEntry))
    {
        PVRIndexAddGopInfo(hIndex, pstIdxInfo, pstEndEntry);
    }

    pstIdxInfo->u32LastGopSize = (pstEndEntry->u16FrameTypeAndGop & 0x3fff) + 1;

    PVRIndexUpdateTotalFrmNum(pstIdxInfo, pstCycMgr);

    HI_INFO_PVR("Chn %d update cycmgr cyctimes %3d start %8d end %8d last %8d\n",
                hIndex->u32RecPicParser,
                pstCycMgr->u32CycTimes, 
                pstCycMgr->u32StartFrame, 
                pstCycMgr->u32EndFrame,
                pstCycMgr->u32LastFrame);
}


static HI_VOID PVRIndexUpdateCycMgrAndRecInfoWhenDisableRewind(PVR_INDEX_HANDLE hIndex, 
                                                               PVR_CYC_MGR_S *pstCycMgr, 
                                                               PVR_REC_INDEX_INFO_S * pstIdxInfo, 
                                                               PVR_INDEX_ENTRY_S *pstEndEntry)
{
    if (pstCycMgr->u32EndFrame == -1)
    {
        pstCycMgr->u32EndFrame = 0;
        pstCycMgr->u32LastFrame = 0;
    }
    else
    {
        pstCycMgr->u32EndFrame++;
        pstCycMgr->u32LastFrame++;
    }

    if (PVR_INDEX_is_Iframe(pstEndEntry))
    {
        PVRIndexAddGopInfo(hIndex, pstIdxInfo, pstEndEntry);
    }

    pstIdxInfo->u32LastGopSize = (pstEndEntry->u16FrameTypeAndGop & 0x3fff) + 1;

    PVRIndexUpdateTotalFrmNum(pstIdxInfo, pstCycMgr);

    HI_INFO_PVR("Chn %d Update cycmgr cyctimes %3d start %8d end %8d last %8d\n",
                hIndex->u32RecPicParser,
                pstCycMgr->u32CycTimes, 
                pstCycMgr->u32StartFrame, 
                pstCycMgr->u32EndFrame,
                pstCycMgr->u32LastFrame);
}


static HI_VOID PVRIndexGetRealOffset(PVR_INDEX_HANDLE hIndex,
                                     PVR_CYC_MGR_S *pstCycMgr,
                                     PVR_INDEX_ENTRY_S *pstIdxEntry)
{
    if(pstCycMgr->enRewindType == PVR_INDEX_REWIND_BY_TIME)
    {
        /*bTimeRewinding������ǰ�Ƿ���ʱ�����ʱindex��󣬴�ʱ��maxsize��TimeRewindMaxSize
                �Ѿ�����Ϊts�ļ��Ĵ�С�����Ƶ���index��globaloffset����ʵ�ʴﵽTimeRewindMaxSize
                ʱ�Ž��л��ƴ���
             */
        if (hIndex->bTimeRewinding == HI_TRUE)
        {
            //index��offsetΪ��ǰglobaloffset��ȥ��һȦ��TimeRewindMaxSize
            pstIdxEntry->u64Offset -= (hIndex->u64TimeRewindMaxSize - pstCycMgr->u64MaxCycSize);
        }
        else
        {
            pstIdxEntry->u64Offset -= hIndex->u64TimeRewindMaxSize;
        }

        /*In the following case, update MaxCycSize to avoid timeshift playing to read wrong position.
                Max1=Latest time rewind file size;  Max2=Current time rewind file size;
                
                |-----------------------------------------------------|-------|
                0                                                                                      Max1      Max2
            */
        if ((0 < pstCycMgr->u32CycTimes) && 
             (pstCycMgr->u64MaxCycSize <= (pstIdxEntry->u64Offset + pstIdxEntry->u32FrameSize)) &&
             ((pstIdxEntry->u32DisplayTimeMs - (pstCycMgr->u32MaxCycTimeInMs * pstCycMgr->u32CycTimes)) <= pstCycMgr->u32MaxCycTimeInMs))
        {
            pstCycMgr->u64MaxCycSize = (pstIdxEntry->u64Offset + pstIdxEntry->u32FrameSize);
        }
    }
    else
    {
        pstIdxEntry->u64Offset -= pstCycMgr->u64MaxCycSize*pstCycMgr->u32CycTimes;
    }
}

static HI_VOID PVRIndexProcRewind(PVR_INDEX_HANDLE hIndex,
                                       PVR_CYC_MGR_S *pstCycMgr,
                                       PVR_REC_INDEX_INFO_S *pstRecInfo,
                                       PVR_INDEX_ENTRY_S *pstIdxEntry)
{
    if (pstCycMgr->enRewindType == PVR_INDEX_REWIND_BY_TIME)
    {
        /*���ֻ��ƴ������
                    1.index��ǰts�����ƴ�СΪindex��GlobalOffset��ֱ�ӽ��л��ƴ���
                      ʱ�Ƴ������ɲ��ſ���ts������indexͬ��
                    2.index���ts�����ƴ�СΪ��ǰ�ļ���С�����ƴ����Ƴٵ�index��
                      GlobalOffset�������ƴ�С��ʱ��
                   */
        if (pstIdxEntry->u64GlobalOffset < hIndex->u64FileSizeGlobal)   //index���
        {
            pstCycMgr->u64MaxCycSize = PVR_IDX_ALIGN_DATA((hIndex->u64FileSizeGlobal - hIndex->u64TimeRewindMaxSize));
            hIndex->bTimeRewinding = HI_TRUE;
            PVRIndexUpdateCycMgrAndRecInfoWhenNotRewind(hIndex, pstCycMgr, pstRecInfo, pstIdxEntry);
        }
        else    //index��ǰ
        {
            pstCycMgr->u64MaxCycSize = PVR_IDX_ALIGN_DATA((pstIdxEntry->u64GlobalOffset - hIndex->u64TimeRewindMaxSize));
            PVRIndexUpdateCycMgrAndRecInfoWhenRewind(hIndex, pstCycMgr, pstRecInfo, pstIdxEntry);
            hIndex->bRewindFlagForIndex = HI_TRUE;

            //˵����ǰcache  ���л��Ƶ㣬��Ҫsavefile  ʱ���д���
            hIndex->stIdxWriteCache.u32RewindCacheWrite = hIndex->stIdxWriteCache.u32Write;

            pstIdxEntry->s32CycTimes = pstCycMgr->u32CycTimes;
            //index��ǰ�ǻ��MaxCycSize�������������ܻᳬ��u64Offset
            if(pstIdxEntry->u64Offset >= pstCycMgr->u64MaxCycSize)
            {
                pstIdxEntry->u64Offset -= pstCycMgr->u64MaxCycSize;
            }
        }
        
        hIndex->u64TimeRewindMaxSize += pstCycMgr->u64MaxCycSize;
        hIndex->bTimeRewindFlagForFile  = HI_TRUE;
    }
    else
    {
        pstIdxEntry->u64Offset -= hIndex->stCycMgr.u64MaxCycSize;
        PVRIndexUpdateCycMgrAndRecInfoWhenRewind(hIndex, pstCycMgr, &hIndex->stRecIdxInfo, pstIdxEntry);
        hIndex->bRewindFlagForIndex = HI_TRUE;
        pstIdxEntry->s32CycTimes = pstCycMgr->u32CycTimes;

        hIndex->stIdxWriteCache.u32RewindCacheWrite = hIndex->stIdxWriteCache.u32Write;
    }
}


static HI_VOID PVRIndexProcNotRewind(PVR_INDEX_HANDLE hIndex,
                                       PVR_CYC_MGR_S *pstCycMgr,
                                       PVR_REC_INDEX_INFO_S *pstRecInfo,
                                       PVR_INDEX_ENTRY_S *pstIdxEntry)
{
//����ʱ�������index�������
    if((pstCycMgr->enRewindType == PVR_INDEX_REWIND_BY_TIME) &&
       (hIndex->bTimeRewinding == HI_TRUE))
    {
        if (pstIdxEntry->u64GlobalOffset <= hIndex->u64TimeRewindMaxSize)
        {
            PVRIndexUpdateCycMgrAndRecInfoWhenNotRewind(hIndex, pstCycMgr, pstRecInfo, pstIdxEntry);
        }
        else
        {
            HI_INFO_PVR("Proc rewind when timerewind and ts lead idx!!!! idx globaloffset %llx timerewindmaxsize %llx\n",
                        pstIdxEntry->u64GlobalOffset, hIndex->u64TimeRewindMaxSize);
            PVRIndexUpdateCycMgrAndRecInfoWhenRewind(hIndex, pstCycMgr, pstRecInfo, pstIdxEntry);
            hIndex->bRewindFlagForIndex = HI_TRUE;
            hIndex->bTimeRewinding   = HI_FALSE;
            pstIdxEntry->s32CycTimes = hIndex->stCycMgr.u32CycTimes;
            pstIdxEntry->u64Offset   = pstIdxEntry->u64GlobalOffset - hIndex->u64TimeRewindMaxSize;
            hIndex->stIdxWriteCache.u32RewindCacheWrite = hIndex->stIdxWriteCache.u32Write;
        }
    }
    //�����������������
    else
    {
        PVRIndexUpdateCycMgrAndRecInfoWhenNotRewind(hIndex, pstCycMgr, pstRecInfo, pstIdxEntry);
    }
}


static HI_S32 PVRIndexProcDisableRewind(PVR_INDEX_HANDLE hIndex,
                                       PVR_CYC_MGR_S *pstCycMgr,
                                       PVR_REC_INDEX_INFO_S *pstRecInfo,
                                       PVR_INDEX_ENTRY_S *pstIdxEntry)
{
    if (hIndex->bRecReachFix)   //����Ѿ�����ָ����С��ʱ�䣬�����д���
    {
        return HI_FAILURE;
    }

    if ((pstCycMgr->u32MaxCycTimeInMs == 0) && (pstCycMgr->u64MaxCycSize == 0))
    {
        PVRIndexUpdateCycMgrAndRecInfoWhenDisableRewind(hIndex, pstCycMgr, pstRecInfo, pstIdxEntry);

        return HI_SUCCESS;
    }

    if (PVR_INDEX_REWIND_BY_TIME == pstCycMgr->enRewindType)
    {            
        if((pstIdxEntry->u32DisplayTimeMs/1000) >= (pstCycMgr->u32MaxCycTimeInMs - 1)/1000)
        {
            pstCycMgr->u64MaxCycSize = PVR_IDX_ALIGN_DATA((pstIdxEntry->u64GlobalOffset + pstIdxEntry->u32FrameSize));
            hIndex->bRecReachFix = HI_TRUE;
            HI_ERR_PVR("reach fix size: u64MaxCycSize =%llu \n\n",hIndex->stCycMgr.u64MaxCycSize);
        }
    }
    else
    {
        if (pstIdxEntry->u64GlobalOffset + pstIdxEntry->u32FrameSize > pstCycMgr->u64MaxCycSize)
        {
            hIndex->bRecReachFix = HI_TRUE;
            return HI_FAILURE;
        }
    }

    PVRIndexUpdateCycMgrAndRecInfoWhenDisableRewind(hIndex, pstCycMgr, pstRecInfo, pstIdxEntry);

    return HI_SUCCESS;
}

#ifdef HI_PVR_L2_CACHE_SUPPORT
//��writeindex���ף������ǻ��Ƶ����
static HI_BOOL PVRIndexWriteWhetherCoverRead(HI_U32 u32Write, HI_U32 u32Num, HIPVR_IDX_BUF_S *pstReadCache)
{
    if (u32Write >= pstReadCache->u32StartNum && u32Write < pstReadCache->u32StartNum + pstReadCache->u32UsedNum)
    {
        return HI_TRUE;
    }

    if (u32Write < pstReadCache->u32StartNum && u32Write + u32Num >= pstReadCache->u32StartNum)
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_S32 PVRIndexWriteIndexEntry(PVR_INDEX_HANDLE hIndex,
                                      HI_U32 u32WriteNum,
                                      HI_U32 u32CacheOffset,
                                      HI_U32 u32FileOffset)
{
    HI_U32 u32SaveSize;

    //���д���index  �Ḳ��readcache  ����ˢ��readcache
    PVR_IDX_CACHE_LOCK(&hIndex->stIdxReadCache.stCacheMutex);
    if (PVRIndexWriteWhetherCoverRead(u32FileOffset,u32WriteNum,&hIndex->stIdxReadCache))
    {
        HI_INFO_PVR("Write frame will cover read frame. read=%d write=%d\n",hIndex->stIdxReadCache.u32Read, u32WriteNum);
        hIndex->stIdxReadCache.bDirty = HI_TRUE;
    }
    PVR_IDX_CACHE_UNLOCK(&hIndex->stIdxReadCache.stCacheMutex);

    PVR_IDX_CACHE_LOCK(&(hIndex->stIdxWriteCache.stCacheMutex));
    if (u32CacheOffset + u32WriteNum >= PVR_INDEX_WRITE_CACHE_NUM)
    {
        PVR_WRITE_INDEX(u32SaveSize, 
                        (PVR_INDEX_WRITE_CACHE_NUM - u32CacheOffset) * sizeof(PVR_INDEX_ENTRY_S),
                        hIndex->stIdxWriteCache.pu8Addr + u32CacheOffset * sizeof(PVR_INDEX_ENTRY_S),
                        hIndex->s32WriteFd, 
                        u32FileOffset * sizeof(PVR_INDEX_ENTRY_S),
                        hIndex);
        
        PVR_WRITE_INDEX(u32SaveSize, 
                        (u32CacheOffset + u32WriteNum - PVR_INDEX_WRITE_CACHE_NUM) * sizeof(PVR_INDEX_ENTRY_S),
                        hIndex->stIdxWriteCache.pu8Addr,
                        hIndex->s32WriteFd, 
                        (u32FileOffset + PVR_INDEX_WRITE_CACHE_NUM - u32CacheOffset) * sizeof(PVR_INDEX_ENTRY_S),
                        hIndex);
    }
    else
    {
        PVR_WRITE_INDEX(u32SaveSize, 
                        u32WriteNum * sizeof(PVR_INDEX_ENTRY_S),
                        hIndex->stIdxWriteCache.pu8Addr + u32CacheOffset * sizeof(PVR_INDEX_ENTRY_S),
                        hIndex->s32WriteFd, 
                        u32FileOffset * sizeof(PVR_INDEX_ENTRY_S),
                        hIndex);
    }
    PVR_IDX_CACHE_UNLOCK(&(hIndex->stIdxWriteCache.stCacheMutex));

    HI_INFO_PVR("Write %d idx Cacheoffset %10d  Fileoffset %10d\n", u32WriteNum, u32CacheOffset,u32FileOffset);

    return HI_SUCCESS;
}

static HI_VOID PVRIndexCopyToCache(HIPVR_IDX_BUF_S *pstIdxBuf, PVR_INDEX_ENTRY_S *pstIdxEntry)
{
    memcpy(pstIdxBuf->pu8Addr + pstIdxBuf->u32Write*sizeof(PVR_INDEX_ENTRY_S), pstIdxEntry, sizeof(PVR_INDEX_ENTRY_S));
    pstIdxBuf->u32Write = PVR_IDX_NEXT_POS_IN_CYC(pstIdxBuf->u32Write, PVR_INDEX_WRITE_CACHE_NUM);
    pstIdxBuf->u32UsedNum++;
}

HI_S32 PVR_Index_SaveToFile(PVR_INDEX_HANDLE hIndex, HI_BOOL bDirectWrite)
{
    HI_S32 s32Ret;
    HI_U32 u32Read, u32Write, u32RewindInCache, u32IdxCount = 0;
    HI_BOOL bRewindInCache = HI_FALSE;
    PVR_CYC_MGR_S        stCycMgr = {0};
    PVR_REC_INDEX_INFO_S stIdxInfo = {0};
    HIPVR_IDX_BUF_S *pstIdxBuf = HI_NULL;

    pstIdxBuf = &hIndex->stIdxWriteCache;

/** we use u32UsedNum to judge whether the writecache is full or empty */
/**  CNcomment:ͳһ�� usednum �ж� writecache �Ƿ�ջ�����*/
    if (pstIdxBuf->u32UsedNum == 0)
    {
        HI_INFO_PVR("There is no data in write cache!\n");
        return HI_SUCCESS;
    }

//�õ����ı����洢����֤���洦������в�����Ϊwritecache  ��
//дָ����¶�������
    PVR_IDX_CACHE_LOCK(&hIndex->stIdxWriteCache.stCacheMutex);
    u32Read  = pstIdxBuf->u32Read;
    u32Write = pstIdxBuf->u32Write;
    PVR_IDX_CACHE_UNLOCK(&hIndex->stIdxWriteCache.stCacheMutex);

    PVR_INDEX_LOCK(&(hIndex->stMutex));
    bRewindInCache = hIndex->bRewindFlagForIndex;
    u32RewindInCache = pstIdxBuf->u32RewindCacheWrite;
    memcpy(&stCycMgr, &hIndex->stCycMgr, sizeof(PVR_CYC_MGR_S));
    memcpy(&stIdxInfo, &hIndex->stRecIdxInfo, sizeof(PVR_REC_INDEX_INFO_S));
    PVR_INDEX_UNLOCK(&(hIndex->stMutex));

    u32IdxCount = pstIdxBuf->u32UsedNum;

    //Ҫд���cache  ���л��Ƶ㣬��ֶ�д��index  �ļ�
    if(bRewindInCache)
    {
        HI_U32 u32IdxCount1,u32IdxCount2;
        u32IdxCount1 = PVR_IDX_DISTANCE_IN_CYC(u32RewindInCache, u32Read, PVR_INDEX_WRITE_CACHE_NUM);
        u32IdxCount2 = PVR_IDX_DISTANCE_IN_CYC(u32Write, u32RewindInCache, PVR_INDEX_WRITE_CACHE_NUM);
        s32Ret = PVRIndexWriteIndexEntry(hIndex, u32IdxCount1, u32Read, hIndex->u32WriteFrame);
        s32Ret |= PVRIndexWriteIndexEntry(hIndex, u32IdxCount2, u32RewindInCache, 0);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_PVR("Write idx failed!! ret %x\n", s32Ret);
            return s32Ret;
        }

        (HI_VOID)PVRIndexWriteIndexCycMgr(hIndex, &stCycMgr);
        (HI_VOID)PVRIndexWriteIndexInfo(hIndex, &stIdxInfo);

        hIndex->u32WriteFrame = u32IdxCount2;
        //fileidxinfo��Ҫ��readcacheʹ�ã�����д���ļ���֡��
        PVR_IDX_CACHE_LOCK(&(pstIdxBuf->stCacheMutex));
        pstIdxBuf->u32RewindCacheWrite = 0;
        pstIdxBuf->u32Read = PVR_IDX_NEXT_N_POS_IN_CYC(u32Read, u32IdxCount, PVR_INDEX_WRITE_CACHE_NUM);
        pstIdxBuf->u32UsedNum -= u32IdxCount;

        HI_ASSERT(pstIdxBuf->u32UsedNum <= PVR_INDEX_WRITE_CACHE_NUM);

        PVR_IDX_CACHE_UNLOCK(&(pstIdxBuf->stCacheMutex));

        PVR_INDEX_LOCK(&(hIndex->stMutex));
        hIndex->stFileCycInfo.u32EndFrame   = stCycMgr.u32EndFrame;
        hIndex->stFileCycInfo.u32LastFrame  = stCycMgr.u32LastFrame;
        hIndex->stFileCycInfo.u32StartFrame = stCycMgr.u32StartFrame;
        hIndex->stFileCycInfo.u32IsRewind   = stCycMgr.bIsRewind;
        hIndex->bRewindFlagForIndex = HI_FALSE;
        PVR_INDEX_UNLOCK(&(hIndex->stMutex));

    }
    //�ﵽд�ļ����޻���ֱ��д�������д�ļ�����
    else if (u32IdxCount > PVR_INDEX_WRITE_FILE_LIMIT || bDirectWrite)
    {
        s32Ret = PVRIndexWriteIndexEntry(hIndex,u32IdxCount,u32Read,hIndex->u32WriteFrame);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_PVR("Write index error %x\n", s32Ret);
            return s32Ret;
        }

        hIndex->u32WriteFrame += u32IdxCount;
        (HI_VOID)PVRIndexWriteIndexCycMgr(hIndex, &stCycMgr);
        (HI_VOID)PVRIndexWriteIndexInfo(hIndex, &stIdxInfo);

        PVR_IDX_CACHE_LOCK(&(pstIdxBuf->stCacheMutex));

        pstIdxBuf->u32Read = PVR_IDX_NEXT_N_POS_IN_CYC(u32Read, u32IdxCount, PVR_INDEX_WRITE_CACHE_NUM);
        pstIdxBuf->u32UsedNum -= u32IdxCount;

        HI_ASSERT(pstIdxBuf->u32UsedNum <= PVR_INDEX_WRITE_CACHE_NUM);
        
        PVR_IDX_CACHE_UNLOCK(&(pstIdxBuf->stCacheMutex));

        PVR_INDEX_LOCK(&(hIndex->stMutex));
        hIndex->stFileCycInfo.u32EndFrame   = stCycMgr.u32EndFrame;
        hIndex->stFileCycInfo.u32LastFrame  = stCycMgr.u32LastFrame;
        hIndex->stFileCycInfo.u32StartFrame = stCycMgr.u32StartFrame;
        hIndex->stFileCycInfo.u32IsRewind   = stCycMgr.bIsRewind;
        PVR_INDEX_UNLOCK(&(hIndex->stMutex));
    }

    return HI_SUCCESS;
}

HI_S32 PVR_Index_SaveToCache(PVR_INDEX_HANDLE hIndex, const HI_UNF_DMX_REC_INDEX_S *pstDmxIndexInfo)
{
    PVR_INDEX_ENTRY_S   stIndexEntry = {0};
    PVR_CYC_MGR_S       *pstCycMgr = HI_NULL;
    PVR_REC_INDEX_INFO_S *pstRecInfo = HI_NULL;
    HIPVR_IDX_BUF_S     *pstIdxBuf = HI_NULL;

    pstCycMgr = &(hIndex->stCycMgr);
    pstRecInfo = &(hIndex->stRecIdxInfo);
    pstIdxBuf = &(hIndex->stIdxWriteCache);

    if ((HI_UNF_FRAME_TYPE_I != pstDmxIndexInfo->enFrameType) &&
        (HI_UNF_FRAME_TYPE_P != pstDmxIndexInfo->enFrameType) &&
        (HI_UNF_FRAME_TYPE_B != pstDmxIndexInfo->enFrameType))
    {
        HI_WARN_PVR("Frame type %d is invalid\n", pstDmxIndexInfo->enFrameType);
        return HI_SUCCESS;
    }

    if (pstIdxBuf->u32UsedNum == PVR_INDEX_WRITE_CACHE_NUM)
    {
        HI_INFO_PVR("There is no space in index write cache\n");
        return HI_FAILURE;
    }

    PVR_INDEX_LOCK(&(hIndex->stMutex));
    PVRIndexAssignIndexEntry(hIndex, pstDmxIndexInfo, &stIndexEntry);

    if (hIndex->stCycMgr.enRewindType == PVR_INDEX_REWIND_BY_BOTH)
        PVR_IDX_CHECK_REWINDTYPE_BYBOTY((&stIndexEntry), pstCycMgr);

    PVRIndexGetRealOffset(hIndex, pstCycMgr, &stIndexEntry);


    if (PVR_IDX_ENABLE_REWIND(hIndex))      //֧�ֻ���
    {
        if (PVRIndexCheckRewind(hIndex, pstCycMgr, &stIndexEntry))      //�����������
        {
            PVRIndexProcRewind(hIndex, pstCycMgr, pstRecInfo, &stIndexEntry);
        }
        else
        {
            PVRIndexProcNotRewind(hIndex, pstCycMgr, pstRecInfo, &stIndexEntry);
        }
    }
    else
    {
        if (HI_SUCCESS != PVRIndexProcDisableRewind(hIndex, pstCycMgr, pstRecInfo, &stIndexEntry))
        {
            PVR_INDEX_UNLOCK(&(hIndex->stMutex));
            return HI_SUCCESS;
        }
    }

    PVR_IDX_CACHE_LOCK(&(pstIdxBuf->stCacheMutex));
    PVRIndexCopyToCache(pstIdxBuf, &stIndexEntry);
    PVR_IDX_CACHE_UNLOCK(&(pstIdxBuf->stCacheMutex));

    memcpy(&(hIndex->stCurRecFrame), &stIndexEntry, sizeof(PVR_INDEX_ENTRY_S));

    PVR_INDEX_UNLOCK(&(hIndex->stMutex));

    HI_INFO_PVR("Chn %d saveidx !bufwrite %d goffset %llx disime %d frmsize %d frmtype %d\n",
                hIndex->u32RecPicParser,pstIdxBuf->u32Write, stIndexEntry.u64GlobalOffset, 
                stIndexEntry.u32DisplayTimeMs, stIndexEntry.u32FrameSize,((pstDmxIndexInfo->enFrameType)&0x3));

    return HI_SUCCESS;
}

/*
Flush the index in the write cache to the disk
*/
HI_S32 PVR_Index_FlushToFile(PVR_INDEX_HANDLE hIndex)
{
    HI_U32 u32IdxTotalNum = 0;
    HI_S32 s32Ret;
    PVR_CYC_MGR_S   *pstCycMgr = HI_NULL;
    HIPVR_IDX_BUF_S *pstIdxBuf = HI_NULL;

    pstCycMgr = &(hIndex->stCycMgr);
    pstIdxBuf = &(hIndex->stIdxWriteCache);
    u32IdxTotalNum = pstIdxBuf->u32UsedNum;

    if (hIndex->bRewindFlagForIndex)
    {
        HI_U32 u32BeforRewindIdxNum;
        u32BeforRewindIdxNum = PVR_IDX_DISTANCE_IN_CYC(pstIdxBuf->u32RewindCacheWrite, 
                                        pstIdxBuf->u32Read, PVR_INDEX_WRITE_CACHE_NUM);
        if (u32IdxTotalNum < u32BeforRewindIdxNum)
        {
            HI_ERR_PVR("Flush idx when rewind errer!!! beforerewind idxnum %d, totalnum %d\n",
                        u32BeforRewindIdxNum, u32IdxTotalNum);
            return HI_FAILURE;
        }

        s32Ret = PVRIndexWriteIndexEntry(hIndex, u32BeforRewindIdxNum, pstIdxBuf->u32Read, hIndex->u32WriteFrame);
        s32Ret |= PVRIndexWriteIndexEntry(hIndex, u32IdxTotalNum - u32BeforRewindIdxNum, pstIdxBuf->u32RewindCacheWrite, 0);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_PVR("Write idx failed!! ret %x\n", s32Ret);
            return s32Ret;
        }

        PVRIndexWriteIndexCycMgr(hIndex, pstCycMgr);
        PVRIndexWriteIndexInfo(hIndex, &hIndex->stRecIdxInfo);                

        hIndex->u32WriteFrame = u32IdxTotalNum - u32BeforRewindIdxNum;
        hIndex->bRewindFlagForIndex = HI_FALSE;
        pstIdxBuf->u32RewindCacheWrite = 0;
    }
    else
    {
        s32Ret = PVRIndexWriteIndexEntry(hIndex, u32IdxTotalNum, pstIdxBuf->u32Read, hIndex->u32WriteFrame);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_PVR("Write index error %x\n", s32Ret);
            return s32Ret;
        }

        (HI_VOID)PVRIndexWriteIndexCycMgr(hIndex, pstCycMgr);
        (HI_VOID)PVRIndexWriteIndexInfo(hIndex, &hIndex->stRecIdxInfo);
        hIndex->u32WriteFrame += u32IdxTotalNum;
    }

    if (hIndex->s32WriteFd && (hIndex->s32WriteFd != PVR_FILE_INVALID_FILE))
    {
        PVR_FSYNC(hIndex->s32WriteFd);
    }

    if (hIndex->s32HeaderFd && (hIndex->s32HeaderFd != PVR_FILE_INVALID_FILE))
    {
        PVR_FSYNC(hIndex->s32HeaderFd);
    }

    hIndex->stFileCycInfo.u32EndFrame   = pstCycMgr->u32EndFrame;
    hIndex->stFileCycInfo.u32LastFrame  = pstCycMgr->u32LastFrame;
    hIndex->stFileCycInfo.u32StartFrame = pstCycMgr->u32StartFrame;
    hIndex->stFileCycInfo.u32IsRewind   = pstCycMgr->bIsRewind;
    pstIdxBuf->u32Read = PVR_IDX_NEXT_N_POS_IN_CYC(pstIdxBuf->u32Read, u32IdxTotalNum, PVR_INDEX_WRITE_CACHE_NUM);
    pstIdxBuf->u32UsedNum = 0;

    return HI_SUCCESS;
}

#else
HI_S32 PVR_Index_SaveFramePosition(PVR_INDEX_HANDLE hIndex, HI_UNF_DMX_REC_INDEX_S *pstDmxIndexInfo,HI_BOOL bDirectWriteFile)
{
    HI_S32              Ret;
    HI_BOOL             bWriteFile = HI_FALSE;
    HI_BOOL             bRewind = HI_FALSE;
    PVR_INDEX_ENTRY_S   stIdxEntry = {0};
    PVR_CYC_MGR_S       *pstCycMgr = HI_NULL;
    PVR_REC_INDEX_INFO_S *pstRecInfo = HI_NULL;

    pstCycMgr = &(hIndex->stCycMgr);
    pstRecInfo = &(hIndex->stRecIdxInfo);

    if ((HI_UNF_FRAME_TYPE_I != pstDmxIndexInfo->enFrameType) &&
        (HI_UNF_FRAME_TYPE_P != pstDmxIndexInfo->enFrameType) &&
        (HI_UNF_FRAME_TYPE_B != pstDmxIndexInfo->enFrameType))
    {
        HI_WARN_PVR("Don't support frame type %d\n", pstDmxIndexInfo->enFrameType);
        return HI_SUCCESS;
    }

    PVR_INDEX_LOCK(&(hIndex->stMutex));
    
    PVRIndexAssignIndexEntry(hIndex, pstDmxIndexInfo, &stIdxEntry);
    
    if (PVR_INDEX_REWIND_BY_BOTH == pstCycMgr->enRewindType)
        PVR_IDX_CHECK_REWINDTYPE_BYBOTY((&stIdxEntry), pstCycMgr);

    PVRIndexGetRealOffset(hIndex, pstCycMgr, &stIdxEntry);

    if (PVR_IDX_ENABLE_REWIND(hIndex))
    {
        bRewind = PVRIndexCheckRewind(hIndex, pstCycMgr, &stIdxEntry);
        if (bRewind)
        {
            PVRIndexProcRewind(hIndex, pstCycMgr, pstRecInfo, &stIdxEntry);
        }
        else
        {
            PVRIndexProcNotRewind(hIndex, pstCycMgr, pstRecInfo, &stIdxEntry);
        }
    }
    else
    {
        if (HI_SUCCESS != PVRIndexProcDisableRewind(hIndex, pstCycMgr, pstRecInfo, &stIdxEntry))
        {
            PVR_INDEX_UNLOCK(&(hIndex->stMutex));
            return HI_SUCCESS;
        } 
    }

    if (hIndex->bRewindFlagForIndex)
    {
        hIndex->u32WriteFrame = 0;
        hIndex->bRewindFlagForIndex = HI_FALSE;
    }

    memcpy(&hIndex->stCurRecFrame, &stIdxEntry, sizeof(PVR_INDEX_ENTRY_S));

    /* if saved stream less than 50M use direct write */
    bDirectWriteFile = (stIdxEntry.u64GlobalOffset < 0x3200000)?HI_TRUE:bDirectWriteFile;

    Ret = PVRCacheWriteIdx(hIndex, (HI_U8*)&stIdxEntry, sizeof(PVR_INDEX_ENTRY_S),
                           hIndex->u32WriteFrame*sizeof(PVR_INDEX_ENTRY_S), 
                           bDirectWriteFile, &bWriteFile);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_PVR("write idx cache failed  ret %x\n", Ret);
        PVR_INDEX_UNLOCK(&(hIndex->stMutex));
        return Ret;
    }

    hIndex->u32WriteFrame++;

    if (bWriteFile)
    {
        (HI_VOID)PVRIndexWriteIndexCycMgr(hIndex, pstCycMgr);
        (HI_VOID)PVRIndexWriteIndexInfo(hIndex, pstRecInfo);
    }

    HI_INFO_PVR("chn %d S:%u, E:%u, L:%u, W:%u\n",
                hIndex->u32RecPicParser,
                pstCycMgr->u32StartFrame,
                pstCycMgr->u32EndFrame,
                pstCycMgr->u32LastFrame,
                hIndex->u32WriteFrame);

    PVR_INDEX_UNLOCK(&(hIndex->stMutex));

    return HI_SUCCESS;
}
#endif


HI_S32 PVR_Index_Init(HI_VOID)
{
    HI_U32 i;

    if (0 == g_u32PvrIndexInit)
    {
        for (i = 0; i < PVR_INDEX_NUM; i++)
        {
            memset(&g_stPVRIndex[i], 0, sizeof(PVR_INDEX_S));
        }
        g_u32PvrIndexInit++;
    }

    return HI_SUCCESS;
}


/*****************************************************************************
 Prototype       : PVR_Index_CreatPlay
 Description     : init index module, get index handle
 Input           : pfileName  **
                    enIndexType: need this just only on recording
 Output          : None
 Return Value    : HI_NULL_PTR:failure, maybe operate file fail, included the wrong index file format
                   handle: success, retruen the handle of index
 Global Variable
    Read Only    :
    Read & Write : pIsNoIdx :index file exist or not
  History
  1.Date         : 2008/4/16
    Author       : q46153
    Modification : Created function
  2.Date         : 2010/06/19
    Author       : Jiang Lei
    Modification : modify for HD
*****************************************************************************/
PVR_INDEX_HANDLE PVR_Index_CreatPlay(HI_U32 chnID,
                                     const HI_UNF_PVR_PLAY_ATTR_S *pstPlayAttr,
                                     HI_BOOL *pIsNoIdx)
{
    HI_S32 ret = HI_SUCCESS;
    PVR_INDEX_HANDLE handle;
    HI_CHAR szIndexName[PVR_MAX_FILENAME_LEN];
    //HI_BOOL bPlayOnly = HI_FALSE;
    //HI_U32 PicParser;

    if (!pstPlayAttr)
    {
        return HI_NULL_PTR;
    }

    //snprintf(szIndexName,sizeof(szIndexName), "%s.%s", pstPlayAttr->szFileName, "idx");
    PVR_Index_GetIdxFileName(szIndexName,  (HI_CHAR *)pstPlayAttr->szFileName);
    /* on recording file, play it, and return the recorded index handle */
    if (PVRIndexIsFileRecording(szIndexName, &handle))
    {
        handle->bIsPlay = HI_TRUE;
        PVR_LOCK(&(handle->stMutex));
        handle->bRecReachPlay = HI_FALSE;
        PVR_UNLOCK(&(handle->stMutex));
        return handle;
    }

    handle = &g_stPVRIndex[chnID];
    HI_ASSERT(HI_FALSE == handle->bIsPlay);

    memset(&handle->stIdxReadCache,0,sizeof(HIPVR_IDX_BUF_S));

#ifndef HI_PVR_L2_CACHE_SUPPORT
    handle->stIdxReadCache.pu8Addr = HI_MALLOC(HI_ID_PVR, PVR_DFT_IDX_READCACHE_SIZE);
    if (handle->stIdxReadCache.pu8Addr)
    {
        handle->stIdxReadCache.u32BufferLen = PVR_DFT_IDX_READCACHE_SIZE;
        handle->stIdxReadCache.u32UsedSize = 0;
        handle->stIdxReadCache.u32StartOffset = 0;
    }
    else
    {
        HI_ERR_PVR("HI_MALLOC read cache buffer failed!\n");
        handle->stIdxReadCache.u32BufferLen = 0;
    }
    if(-1 == pthread_mutex_init(&(handle->stIdxReadCache.stCacheMutex), NULL))
    {
        HI_ERR_PVR("init mutex lock for PVR index failed,check it\n");
        if (handle->stIdxReadCache.pu8Addr != HI_NULL)
            HI_FREE(HI_ID_PVR,handle->stIdxReadCache.pu8Addr);
        return HI_NULL_PTR;
    }
#else
    handle->stIdxReadCache.pu8Addr = HI_MALLOC(HI_ID_PVR, PVR_DFT_IDX_READCACHE_SIZE);
    if (handle->stIdxReadCache.pu8Addr)
    {
        handle->stIdxReadCache.u32BufferLen = 0;
        handle->stIdxReadCache.u32UsedNum = 0;
        handle->stIdxReadCache.u32StartNum = 0;
    }
    else
    {
        HI_ERR_PVR("HI_MALLOC read cache buffer failed!\n");
        handle->stIdxReadCache.u32BufferLen = 0;
    }
    if(-1 == pthread_mutex_init(&(handle->stIdxReadCache.stCacheMutex), NULL))
    {
        HI_ERR_PVR("init mutex lock for PVR index failed,check it\n");
        if (handle->stIdxReadCache.pu8Addr != HI_NULL)
            HI_FREE(HI_ID_PVR,handle->stIdxReadCache.pu8Addr);
        return HI_NULL_PTR;
    }
#endif

    PVRIndexSetDftAttr(handle);

    memset(handle->szIdxFileName, 0, sizeof(handle->szIdxFileName));
    strncpy(handle->szIdxFileName, szIndexName, strlen(szIndexName));

    if (-1 == pthread_mutex_init(&(handle->stMutex), NULL))
    {
        HI_ERR_PVR("init mutex lock for PVR index failed \n");
        goto ErrorExit;
    }

    handle->bIsPlay = HI_TRUE;
    handle->bIsRec = HI_FALSE;

    /* check whether index file exist or not, if not, just  track it and not to open */
    if (PVR_CHECK_FILE_EXIST(szIndexName))
    {
        *pIsNoIdx = HI_FALSE;
        handle->s32ReadFd = PVR_OPEN(szIndexName, PVR_FOPEN_MODE_INDEX_READ);
        if (PVR_FILE_INVALID_FILE == handle->s32ReadFd)
        {
            HI_ERR_PVR("PVR open Index File for read failed !\n");
            goto ErrorExit;
        }

        handle->s32SeekFd = PVR_OPEN(szIndexName, PVR_FOPEN_MODE_INDEX_READ);
        if (PVR_FILE_INVALID_FILE == handle->s32SeekFd)
        {
            HI_ERR_PVR("PVR open Index File for seek failed !\n");
            PVR_CLOSE(handle->s32ReadFd);
            goto ErrorExit;
        }

        handle->s32HeaderFd = PVR_OPEN(szIndexName, PVR_FOPEN_MODE_INDEX_BOTH);
        if (PVR_FILE_INVALID_FILE == handle->s32HeaderFd)
        {
            HI_ERR_PVR("PVR open Index File for Header failed !\n");
            PVR_CLOSE(handle->s32SeekFd);
            PVR_CLOSE(handle->s32ReadFd);
            goto ErrorExit;
        }

        ret = PVRIndexReadHeaderInfo(handle);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("PVR read Index File Header failed !\n");
            PVR_CLOSE(handle->s32ReadFd);
            PVR_CLOSE(handle->s32SeekFd);
            PVR_CLOSE(handle->s32HeaderFd);
            goto ErrorExit;
        }

        ret = PVR_Index_PlayGetFileAttrByFileName(pstPlayAttr->szFileName, HI_NULL, &handle->stIndexFileAttr);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("PVR read Index File Header failed !\n");
            PVR_CLOSE(handle->s32ReadFd);
            PVR_CLOSE(handle->s32SeekFd);
            PVR_CLOSE(handle->s32HeaderFd);
            goto ErrorExit;
        }

        handle->enIndexType = handle->stIndexFileAttr.enIdxType;

        /*alone play, not open write handle */
        handle->s32WriteFd = PVR_FILE_INVALID_FILE;
    }
    else  /* NO index file, no need to process! */
    {
        //*pIsNoIdx = HI_TRUE;
        //handle->enIndexType = HI_UNF_PVR_REC_INDEX_TYPE_NONE;
        HI_ERR_PVR("No index file for '%s' found!.\n", pstPlayAttr->szFileName);
        goto ErrorExit;
    }

    return handle;

ErrorExit:
    if (handle->stIdxReadCache.pu8Addr)
    {
        HI_FREE(HI_ID_PVR, handle->stIdxReadCache.pu8Addr);
    }
    memset(&handle->stIdxReadCache,0,sizeof(HIPVR_IDX_BUF_S));
    handle->bIsPlay = HI_FALSE;
    (HI_VOID)pthread_mutex_destroy(&(handle->stMutex));
    return HI_NULL_PTR;
}

/*****************************************************************************
 Prototype       : PVR_Index_CreatRec
 Description     : create pvr rec channel
 Input           : pfileName  **
                    enIndexType: need this just only on recording
 Output          : None
 Return Value    : HI_NULL_PTR: failure, maybe operate file failure or the file playing, which the need to record.
                   handle: success, retruen the handle of index
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/16
    Author       : q46153
    Modification : Created function
  2.Date         : 2010/06/19
    Author       : Jiang Lei
    Modification : modify for HD
*****************************************************************************/
PVR_INDEX_HANDLE PVR_Index_CreatRec(HI_U32 chnID, HI_UNF_PVR_REC_ATTR_S *pstRecAttr)
{
    HI_S32 ret;
    HI_UNF_DMX_PORT_E enPort;
    PVR_INDEX_HANDLE handle = HI_NULL;
    HI_CHAR szIndexName[PVR_MAX_FILENAME_LEN] = {0};
    HI_U32 i = 0;

    if (!pstRecAttr)
    {
        return HI_NULL_PTR;
    }

    PVR_Index_GetIdxFileName(szIndexName,  pstRecAttr->szFileName);
    //snprintf(szIndexName,sizeof(szIndexName), "%s.ts.%s", pstRecAttr->szFileName, "idx");

    /** if the file has been playing, return HI_NULL_PTR */
    if (PVRIndexIsFilePlaying(szIndexName, &handle))
    {
        HI_ERR_PVR("the file %s is playing, please stop it before recordring the same file.\n", pstRecAttr->szFileName);
        return HI_NULL_PTR;
    }

    for (i = 0; i < sizeof(g_u32RecChnStat)/sizeof(HI_U32); i++)
    {
        if (PVR_INDEX_REC_CHN_UNUSED == g_u32RecChnStat[i])
        {
            g_u32RecChnStat[i] = PVR_INDEX_REC_CHN_USED;
            break;
        }
    }
    if (i >= PVR_REC_MAX_CHN_NUM)
    {
        HI_ERR_PVR("Rec channel %d is out of range.\n", i);
        return HI_NULL_PTR;
    }

    handle = &g_stPVRIndex[i + PVR_PLAY_MAX_CHN_NUM];

    HI_ASSERT(HI_FALSE == handle->bIsRec);

    PVRIndexSetDftAttr(handle);

    memset(handle->szIdxFileName, 0, sizeof(handle->szIdxFileName));
    strncpy(handle->szIdxFileName, szIndexName, strlen(szIndexName));

    if (-1 == pthread_mutex_init(&(handle->stMutex), NULL))
    {
        HI_ERR_PVR("init mutex lock for PVR index failed \n");
        g_u32RecChnStat[i] = PVR_INDEX_REC_CHN_UNUSED;
        return HI_NULL_PTR;
    }

    PVR_IDX_CHECK_CYC_SIZE(pstRecAttr);

    handle->bIsPlay = HI_FALSE;
    handle->bIsRec = HI_TRUE;
    handle->u32RecPicParser = i;
    handle->enIndexType = pstRecAttr->enIndexType;
    handle->u32DavBufSize = pstRecAttr->u32DavBufSize;
    handle->stCycMgr.bIsRewind = pstRecAttr->bRewind;
    handle->stCycMgr.u64MaxCycSize = (pstRecAttr->u64MaxFileSize / PVR_FIFO_WRITE_BLOCK_SIZE) * PVR_FIFO_WRITE_BLOCK_SIZE;
    handle->stCycMgr.u32MaxCycTimeInMs = pstRecAttr->u64MaxTimeInMs ;
    handle->stCycMgr.u32EndFrame = -1;
    handle->stCycMgr.u32LastFrame = -1;

    handle->stCycMgr.enRewindType = PVR_INDEX_REWIND_BY_BOTH;
    
    if ((handle->stCycMgr.u64MaxCycSize == 0) && (handle->stCycMgr.u32MaxCycTimeInMs > 0))
    {
        handle->stCycMgr.enRewindType = PVR_INDEX_REWIND_BY_TIME;
    }
    if ((handle->stCycMgr.u64MaxCycSize > 0) && (handle->stCycMgr.u32MaxCycTimeInMs == 0))
    {
        handle->stCycMgr.enRewindType = PVR_INDEX_REWIND_BY_SIZE;
    }

    handle->s32WriteFd = PVR_OPEN(szIndexName, PVR_FOPEN_MODE_INDEX_WRITE);
    if (PVR_FILE_INVALID_FILE == handle->s32WriteFd)
    {
        HI_ERR_PVR("PVR open Index File for write failed !\n");
        goto ErrorExit;
    }

    handle->s32SeekFd = PVR_OPEN(szIndexName, PVR_FOPEN_MODE_INDEX_READ);
    if (PVR_FILE_INVALID_FILE == handle->s32SeekFd)
    {
        HI_ERR_PVR("PVR open Index File for seek failed !\n");
        PVR_CLOSE(handle->s32WriteFd);
        goto ErrorExit;
    }

    handle->s32HeaderFd = PVR_OPEN(szIndexName, PVR_FOPEN_MODE_INDEX_BOTH);
    if (PVR_FILE_INVALID_FILE == handle->s32HeaderFd)
    {
        HI_ERR_PVR("PVR open Index File for Idx Header failed !\n");
        PVR_CLOSE(handle->s32WriteFd);
        PVR_CLOSE(handle->s32SeekFd);
        goto ErrorExit;
    }

    handle->s32ReadFd = PVR_OPEN(szIndexName, PVR_FOPEN_MODE_INDEX_READ);
    if (PVR_FILE_INVALID_FILE == handle->s32ReadFd)
    {
        PVR_CLOSE(handle->s32WriteFd);
        PVR_CLOSE(handle->s32SeekFd);
        PVR_CLOSE(handle->s32HeaderFd);
        (HI_VOID)remove(szIndexName);
        HI_ERR_PVR("PVR open Index File for read failed !\n");
        goto ErrorExit;
    }
#ifdef HI_PVR_L2_CACHE_SUPPORT
    handle->stIdxWriteCache.pu8Addr = HI_MALLOC(HI_ID_PVR, PVR_INDEX_WRITE_CACHE_NUM * sizeof(PVR_INDEX_ENTRY_S));
    if (handle->stIdxWriteCache.pu8Addr)
    {
        handle->stIdxWriteCache.u32BufferLen = 0;
        handle->stIdxWriteCache.u32Read      = 0;
        handle->stIdxWriteCache.u32Write     = 0;
        handle->stIdxWriteCache.u32UsedNum   = 0;
        handle->stIdxWriteCache.u32StartNum  = 0;
    }
    else
    {
        handle->stIdxWriteCache.u32BufferLen = 0;
        HI_ERR_PVR("HI_MALLOC write cache buffer failed!\n");
    }

    if (-1 == pthread_mutex_init(&(handle->stIdxWriteCache.stCacheMutex), NULL))
    {
        HI_ERR_PVR("init mutex lock for PVR index failed,check it\n");
        if (handle->stIdxWriteCache.pu8Addr != HI_NULL)
        {
            HI_FREE(HI_ID_PVR,handle->stIdxWriteCache.pu8Addr);
        }

        PVR_CLOSE(handle->s32WriteFd);
        PVR_CLOSE(handle->s32SeekFd);
        PVR_CLOSE(handle->s32HeaderFd);
        PVR_CLOSE(handle->s32ReadFd);
        (HI_VOID)remove(szIndexName);
        goto ErrorExit;
    }

    memset(&handle->stIdxReadCache, 0, sizeof(HIPVR_IDX_BUF_S));
    handle->stIdxReadCache.pu8Addr = HI_MALLOC(HI_ID_PVR, PVR_INDEX_READ_CACHE_NUM * sizeof(PVR_INDEX_ENTRY_S));
    if (handle->stIdxReadCache.pu8Addr)
    {
        handle->stIdxReadCache.u32BufferLen = 0;
        handle->stIdxReadCache.u32UsedNum = 0;
        handle->stIdxReadCache.u32StartNum = 0;
        handle->stIdxReadCache.bDirty = HI_FALSE;
    }
    else
    {
        HI_ERR_PVR("HI_MALLOC read cache buffer failed!\n");
        handle->stIdxReadCache.u32BufferLen = 0;
    }
    
    if (-1 == pthread_mutex_init(&(handle->stIdxReadCache.stCacheMutex), NULL))
    {
        HI_ERR_PVR("init mutex lock for PVR index failed,check it\n");
        if (handle->stIdxWriteCache.pu8Addr != HI_NULL)
        {
            HI_FREE(HI_ID_PVR, handle->stIdxWriteCache.pu8Addr);
        }
        if (handle->stIdxReadCache.pu8Addr != HI_NULL)
        {
            HI_FREE(HI_ID_PVR, handle->stIdxReadCache.pu8Addr);
        }

        PVR_CLOSE(handle->s32WriteFd);
        PVR_CLOSE(handle->s32SeekFd);
        PVR_CLOSE(handle->s32HeaderFd);
        PVR_CLOSE(handle->s32ReadFd);
        (HI_VOID)remove(szIndexName);
        goto ErrorExit;
    }
#else
    handle->stIdxWriteCache.pu8Addr = HI_MALLOC(HI_ID_PVR, PVR_DFT_IDX_WRITECACHE_SIZE);
    if (handle->stIdxWriteCache.pu8Addr)
    {
        handle->stIdxWriteCache.u32BufferLen = PVR_DFT_IDX_WRITECACHE_SIZE;
        handle->stIdxWriteCache.u32UsedSize = 0;
        handle->stIdxWriteCache.u32StartOffset = 0;
        if (-1 == pthread_mutex_init(&(handle->stIdxWriteCache.stCacheMutex), NULL))
        {
            HI_ERR_PVR("init mutex lock for PVR index failed,check it\n");
            if (handle->stIdxWriteCache.pu8Addr != HI_NULL)
            {
                HI_FREE(HI_ID_PVR, handle->stIdxWriteCache.pu8Addr);
            }
            PVR_CLOSE(handle->s32WriteFd);
            PVR_CLOSE(handle->s32SeekFd);
            PVR_CLOSE(handle->s32HeaderFd);
            PVR_CLOSE(handle->s32ReadFd);
            (HI_VOID)remove(szIndexName);
            goto ErrorExit;
        }
    }
    else
    {
        handle->stIdxWriteCache.u32BufferLen = 0;
        HI_ERR_PVR("HI_MALLOC write cache buffer failed!\n");
    }

    memset(&handle->stIdxReadCache, 0, sizeof(HIPVR_IDX_BUF_S));
    handle->stIdxReadCache.pu8Addr = HI_MALLOC(HI_ID_PVR, PVR_DFT_IDX_READCACHE_SIZE);
    if (handle->stIdxReadCache.pu8Addr)
    {
        handle->stIdxReadCache.u32BufferLen = PVR_DFT_IDX_READCACHE_SIZE;
        handle->stIdxReadCache.u32UsedSize = 0;
        handle->stIdxReadCache.u32StartOffset = 0;
        if (-1 == pthread_mutex_init(&(handle->stIdxReadCache.stCacheMutex), NULL))
        {
            HI_ERR_PVR("init mutex lock for PVR index failed,check it\n");
            if (handle->stIdxWriteCache.pu8Addr != HI_NULL)
            {
                HI_FREE(HI_ID_PVR, handle->stIdxWriteCache.pu8Addr);
            }
            if (handle->stIdxReadCache.pu8Addr != HI_NULL)
            {
                HI_FREE(HI_ID_PVR, handle->stIdxReadCache.pu8Addr);
            }
            PVR_CLOSE(handle->s32WriteFd);
            PVR_CLOSE(handle->s32SeekFd);
            PVR_CLOSE(handle->s32HeaderFd);
            PVR_CLOSE(handle->s32ReadFd);
            (HI_VOID)remove(szIndexName);
            goto ErrorExit;
        }
    }
    else
    {
        HI_ERR_PVR("HI_MALLOC read cache buffer failed!\n");
        handle->stIdxReadCache.u32BufferLen = 0;
    }
#endif
        
    handle->u32FRollTime = 0;
    handle->u32DeltaDispTimeMs = 0;
    handle->u32LastDispTime = 0;
    handle->u32TimeShiftTillEndTimeMs = 0;
    handle->u32TimeShiftTillEndCnt = 0;
    handle->bRecReachFix = HI_FALSE;
    handle->bTimeRewindFlagForFile = HI_FALSE;
    handle->bTimeRewinding = HI_FALSE;
    handle->bRewindFlagForIndex = HI_FALSE;
    handle->u64TimeRewindMaxSize = 0;
    handle->u64DeltaGlobalOffset = 0;
    memset(&(handle->stRecIdxInfo), 0, sizeof(PVR_REC_INDEX_INFO_S));

    memset(&(handle->stTimeStamp), 0, sizeof(PVR_REC_TIMESTAMP_S));
    ret = HI_UNF_DMX_GetTSPortId(pstRecAttr->u32DemuxID, &enPort);
    if (ret == HI_SUCCESS)
    {
        if (enPort >= HI_UNF_DMX_PORT_RAM_0)
        {
            handle->stTimeStamp.bNeedAdjustByPts = HI_TRUE;
        }
    }
    else
    {
        handle->stTimeStamp.bNeedAdjustByPts = HI_FALSE;
    }

    handle->stTimeStamp.u32DeltaTimeStamp        = PVR_INDEX_DEFAULT_FRAME_TIMESTAMP;
    handle->stTimeStamp.stLastIFrmPtsInfo.u32PtsMs = PVR_INDEX_INVALID_PTSMS;
    handle->stTimeStamp.stCurIFrmPtsInfo.u32PtsMs  = PVR_INDEX_INVALID_PTSMS;

    UNUSED(chnID);

    return handle;

ErrorExit:
    g_u32RecChnStat[i] = PVR_INDEX_REC_CHN_UNUSED;
    (HI_VOID)pthread_mutex_destroy(&(handle->stMutex));
    return HI_NULL_PTR;
}


/*****************************************************************************
 Prototype       : PVR_Index_Destroy
 Description     : de-init index module, release index handle and relative resource
                 may stop either record or play at any time, which are independent
 Input           : handle  **
                   u32PlayOrRec  need to stop record or play
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/16
    Author       : q46153
    Modification : Created function

*****************************************************************************/
HI_S32 PVR_Index_Destroy(PVR_INDEX_HANDLE handle, HI_U32 u32PlayOrRec)
{
    PVR_CHECK_POINTER(handle);

    if (PVR_INDEX_PLAY == u32PlayOrRec)
    {
        handle->bIsPlay = HI_FALSE;
    }
    else
    {
        handle->bIsRec = HI_FALSE;
    }

    if (handle->bIsPlay || handle->bIsRec)
    {
        HI_WARN_PVR("also play or rec was using this index.\n");
        return HI_SUCCESS;
    }

#ifndef HI_PVR_L2_CACHE_SUPPORT
    if (PVR_Index_FlushIdxWriteCache(handle) != HI_SUCCESS)
    {
        HI_ERR_PVR("rec flush cache error!\n");
    }

    (HI_VOID)PVRIndexWriteIndexCycMgr(handle, &handle->stCycMgr);

    if (handle->s32HeaderFd && (handle->s32HeaderFd != PVR_FILE_INVALID_FILE))
    {
        PVR_FSYNC(handle->s32HeaderFd);
    }

    if (handle->s32WriteFd && (handle->s32WriteFd != PVR_FILE_INVALID_FILE))
    {
        PVR_FSYNC(handle->s32WriteFd);
    }
#endif
    (HI_VOID)pthread_mutex_destroy(&(handle->stMutex));

    /* close index file */
    if (handle->s32ReadFd && (handle->s32ReadFd != PVR_FILE_INVALID_FILE))
    {
        PVR_CLOSE(handle->s32ReadFd);
        handle->s32ReadFd = PVR_FILE_INVALID_FILE;
    }

    if (handle->s32WriteFd && (handle->s32WriteFd != PVR_FILE_INVALID_FILE))
    {
        PVR_CLOSE(handle->s32WriteFd);
        handle->s32WriteFd = PVR_FILE_INVALID_FILE;
    }

    if (handle->s32SeekFd && (handle->s32SeekFd != PVR_FILE_INVALID_FILE))
    {
        PVR_CLOSE(handle->s32SeekFd);
        handle->s32SeekFd = PVR_FILE_INVALID_FILE;
    }

    if (handle->s32HeaderFd && (handle->s32HeaderFd != PVR_FILE_INVALID_FILE))
    {
        PVR_CLOSE(handle->s32HeaderFd);
        handle->s32HeaderFd = PVR_FILE_INVALID_FILE;
    }

    /* release index handle */
    if ((handle->u32RecPicParser != 0xffffffff) && (PVR_REC_MAX_CHN_NUM > handle->u32RecPicParser))
    {
        g_u32RecChnStat[handle->u32RecPicParser] = PVR_INDEX_REC_CHN_UNUSED;
        handle->u32RecPicParser = 0xffffffff;
    }

#ifndef HI_PVR_L2_CACHE_SUPPORT    
    if (handle->stIdxWriteCache.pu8Addr)
    {
        HI_FREE(HI_ID_PVR, handle->stIdxWriteCache.pu8Addr);
        handle->stIdxWriteCache.pu8Addr = HI_NULL;
        handle->stIdxWriteCache.u32StartOffset = 0;
        handle->stIdxWriteCache.u32UsedSize = 0;
    }
    (HI_VOID)pthread_mutex_destroy(&(handle->stIdxWriteCache.stCacheMutex));

    if (handle->stIdxReadCache.pu8Addr)
    {
        HI_FREE(HI_ID_PVR, handle->stIdxReadCache.pu8Addr);
        handle->stIdxReadCache.pu8Addr = HI_NULL;
        handle->stIdxReadCache.u32StartOffset = 0;
        handle->stIdxReadCache.u32UsedSize = 0;
    }
#else
    if (handle->stIdxWriteCache.pu8Addr)
    {
        HI_FREE(HI_ID_PVR, handle->stIdxWriteCache.pu8Addr);
        handle->stIdxWriteCache.pu8Addr = HI_NULL;
        handle->stIdxWriteCache.u32StartNum = 0;
        handle->stIdxWriteCache.u32UsedNum = 0;
    }
    (HI_VOID)pthread_mutex_destroy(&(handle->stIdxWriteCache.stCacheMutex));

    if (handle->stIdxReadCache.pu8Addr)
    {
        HI_FREE(HI_ID_PVR, handle->stIdxReadCache.pu8Addr);
        handle->stIdxReadCache.pu8Addr = HI_NULL;
        handle->stIdxReadCache.u32StartNum = 0;
        handle->stIdxReadCache.u32UsedNum = 0;
    }
#endif
    (HI_VOID)pthread_mutex_destroy(&(handle->stIdxReadCache.stCacheMutex));

    return HI_SUCCESS;
}



/*
  |---n * sizeof(PVR_INDEX_ENTRY_S)---|
  +---------+-------------------------+-------...
  | CycInfo | UsrDataInfo             | Idx data
  +---------+-------------------------+---------...
*/
HI_S32 PVR_Index_PrepareHeaderInfo(PVR_INDEX_HANDLE handle, HI_U32 u32UsrDataLen, HI_U32 u32Vtype)
{
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo;
    HI_U32 u32HeadInfoSize = 0;
    HI_S32 s32WriteRet;
    HI_U8* pTmpBuff = NULL;

    memset(&stIdxHeaderInfo, 0x0, sizeof(PVR_IDX_HEADER_INFO_S));

    stIdxHeaderInfo.u32CADataInfoLen = PVR_MAX_CADATA_LEN;

    /* compute HeaderSize, which should be the times of sizeof(PVR_INDEX_ENTRY_S)*/
    u32HeadInfoSize = (sizeof(PVR_IDX_HEADER_INFO_S) + stIdxHeaderInfo.u32CADataInfoLen + u32UsrDataLen + sizeof(PVR_INDEX_ENTRY_S))
                      / sizeof(PVR_INDEX_ENTRY_S) * sizeof(PVR_INDEX_ENTRY_S);

    stIdxHeaderInfo.u32HeaderLen = u32HeadInfoSize;
    stIdxHeaderInfo.u32StartCode = PVR_INDEX_HEADER_CODE;
    stIdxHeaderInfo.u32UsrDataInfoLen = u32UsrDataLen;

    stIdxHeaderInfo.u64ValidSize = handle->stCycMgr.u64MaxCycSize;
    stIdxHeaderInfo.stCycInfo.u32StartFrame = handle->stCycMgr.u32StartFrame;
    stIdxHeaderInfo.stCycInfo.u32EndFrame   = handle->stCycMgr.u32EndFrame;
    stIdxHeaderInfo.stCycInfo.u32LastFrame  = handle->stCycMgr.u32LastFrame;
    stIdxHeaderInfo.stCycInfo.u32IsRewind   = handle->stCycMgr.bIsRewind;
    /* use u32Reserved low 16bits to store HI_UNF_VCODEC_TYPE_E */
    stIdxHeaderInfo.u32Reserved = 0xFFFF & (100 + u32Vtype); 
    if ((HI_S32)stIdxHeaderInfo.u32UsrDataInfoLen < 0)
    {
        HI_ERR_PVR("calc usr data len:%d err\n", stIdxHeaderInfo.u32UsrDataInfoLen);
        return HI_FAILURE;
    }

    pTmpBuff = HI_MALLOC(HI_ID_PVR, u32HeadInfoSize);
    if (NULL == pTmpBuff)
    {
        HI_ERR_PVR("no mem, want=%u\n", u32HeadInfoSize);
        return HI_FAILURE;
    }
    memset(pTmpBuff, 0x0, u32HeadInfoSize);
    memcpy(pTmpBuff, &stIdxHeaderInfo, sizeof(PVR_IDX_HEADER_INFO_S));

    s32WriteRet = (HI_S32)u32HeadInfoSize;
    if (s32WriteRet != PVR_WRITE((HI_VOID*)pTmpBuff, (size_t)u32HeadInfoSize, handle->s32HeaderFd, 0))
    {
        HI_ERR_PVR("write header info err, fd:%d, size:%d\n", handle->s32HeaderFd, u32HeadInfoSize);
        HI_FREE(HI_ID_PVR, pTmpBuff);
        return HI_FAILURE;
    }

    HI_INFO_PVR("write header info ok(%uByte writen), UDLen:%u, MaxSize:%llu\n", 
                 s32WriteRet, stIdxHeaderInfo.u32UsrDataInfoLen, stIdxHeaderInfo.u64ValidSize);
    PVR_FSYNC(handle->s32HeaderFd);

    handle->u32IdxStartOffsetLen = u32HeadInfoSize;

    HI_FREE(HI_ID_PVR, pTmpBuff);

    return HI_SUCCESS;
}

/* reset the player attribute, called when start play*/
HI_VOID PVR_Index_ResetPlayAttr(PVR_INDEX_HANDLE handle)
{
    PVR_INDEX_LOCK(&handle->stMutex);
    handle->u32ReadFrame = handle->stCycMgr.u32StartFrame;
    handle->bRecReachPlay = HI_FALSE;
    memset(&handle->stCurPlayFrame, 0, sizeof(PVR_INDEX_ENTRY_S));
    PVR_INDEX_UNLOCK(&handle->stMutex);
}

/* reset the player attribute, called when start record */
HI_VOID PVR_Index_ResetRecAttr(PVR_INDEX_HANDLE handle)
{
    handle->u64GlobalOffset = 0;
    handle->u64OverflowOffset = 0;
    handle->u32PauseFrame  = 0;
    handle->u64PauseOffset = PVR_INDEX_PAUSE_INVALID_OFFSET;
    handle->u32WriteFrame = 0;
    handle->u16RecLastIframe = PVR_INDEX_INVALID_I_FRAME_OFFSET;
    handle->u32RecLastValidPtsMs = PVR_INDEX_INVALID_PTSMS;
    handle->u32RecFirstFrmTimeMs = 0;
    handle->stCycMgr.u32StartFrame = 0;
    handle->stCycMgr.u32EndFrame = -1;
    handle->stCycMgr.u32LastFrame = -1;
    handle->stCycMgr.u32CycTimes = 0;
    handle->stCycMgr.u32StartFrame = 0;

    memset(&handle->stCurRecFrame, 0, sizeof(PVR_INDEX_ENTRY_S));
}

/* set current frame size is zero, prevent from repeatly sending the last frame when switch play mode */
HI_S32 PVR_Index_ChangePlayMode(PVR_INDEX_HANDLE handle)
{
    handle->stCurPlayFrame.u32FrameSize = 0;
    return HI_SUCCESS;
}


HI_S32 PVR_Index_GetUsrDataInfo(HI_S32 s32Fd, HI_U8* pBuff, HI_U32 u32BuffSize)
{
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo = {0};
    HI_S32 s32ReadRet;
    HI_U32 u32ReadLen;

    if (HI_SUCCESS != PVRIndexGetHeaderInfo(s32Fd, &stIdxHeaderInfo))
    {
        HI_ERR_PVR("No userDataInfo in this file.\n");
        return HI_ERR_PVR_FILE_CANT_READ;
    }

    u32ReadLen = (stIdxHeaderInfo.u32UsrDataInfoLen > u32BuffSize) ? (u32BuffSize) : (stIdxHeaderInfo.u32UsrDataInfoLen);

    s32ReadRet = PVR_READ(pBuff, u32ReadLen, s32Fd, PVR_GET_USR_DATA_OFFSET(stIdxHeaderInfo));
    if (s32ReadRet != (HI_S32)u32ReadLen)
    {
        HI_ERR_PVR("read usr data info err, read ret:0x%x\n", s32ReadRet);
        return HI_FAILURE;
    }
    return s32ReadRet;
}

HI_S32 PVR_Index_SetUsrDataInfo(HI_S32 s32Fd, HI_U8* pBuff, HI_U32 u32UsrDataLen)
{
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo = {0};
    HI_S32 s32WriteRet = (HI_S32)u32UsrDataLen;

    if (HI_SUCCESS != PVRIndexGetHeaderInfo(s32Fd, &stIdxHeaderInfo))
    {
        return HI_ERR_PVR_FILE_CANT_READ;
    }
    if (stIdxHeaderInfo.u32UsrDataInfoLen < u32UsrDataLen)
    {
        HI_ERR_PVR("usr data len is no enough:%d\n", stIdxHeaderInfo.u32UsrDataInfoLen);
        return HI_FAILURE;
    }

    s32WriteRet = (HI_S32)PVR_WRITE((HI_VOID*)pBuff, (size_t)u32UsrDataLen, s32Fd, (off_t)PVR_GET_USR_DATA_OFFSET(stIdxHeaderInfo));
    if (s32WriteRet != (HI_S32)u32UsrDataLen)
    {
        HI_ERR_PVR("read usr data info err:0x%x\n", s32WriteRet);
        return HI_FAILURE;
    }

    return s32WriteRet;
}

HI_S32 PVR_Index_GetCADataInfo(HI_S32 s32Fd, HI_U8* pBuff, HI_U32 u32BuffSize)
{
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo = {0};
    HI_S32 s32ReadRet;
    HI_U32 u32ReadLen;

    if (HI_SUCCESS != PVRIndexGetHeaderInfo(s32Fd, &stIdxHeaderInfo))
    {
        HI_ERR_PVR("No CADataInfo in this file.\n");
        return HI_ERR_PVR_FILE_CANT_READ;
    }

    u32ReadLen = (stIdxHeaderInfo.u32CADataInfoLen > u32BuffSize) ? (u32BuffSize) : (stIdxHeaderInfo.u32CADataInfoLen);

    s32ReadRet = PVR_READ(pBuff, u32ReadLen, s32Fd, PVR_GET_CA_DATA_OFFSET());
    if (s32ReadRet != u32ReadLen)
    {
        HI_ERR_PVR("read usr CA info err, read ret:0x%x\n", s32ReadRet);
        return HI_FAILURE;
    }

    return s32ReadRet;
}


HI_S32 PVR_Index_SetCADataInfo(HI_S32 s32Fd, HI_U8* pBuff, HI_U32 u32CADataLen)
{
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo = {0};
    HI_S32 s32WriteRet = u32CADataLen;

    if (HI_SUCCESS != PVRIndexGetHeaderInfo(s32Fd, &stIdxHeaderInfo))
    {
        return HI_ERR_PVR_FILE_CANT_READ;
    }

    if (stIdxHeaderInfo.u32CADataInfoLen < u32CADataLen)
    {
        HI_ERR_PVR("CA data len is no enough:%d\n", stIdxHeaderInfo.u32CADataInfoLen);
        return HI_FAILURE;
    }

    s32WriteRet = PVR_WRITE(pBuff, u32CADataLen, s32Fd, PVR_GET_CA_DATA_OFFSET());
    if (s32WriteRet != u32CADataLen)
    {
        HI_ERR_PVR("read CA data info err:0x%x\n", s32WriteRet);
        return HI_FAILURE;
    }

    return s32WriteRet;
}

HI_VOID PVR_Index_GetIdxInfo(PVR_INDEX_HANDLE handle)
{
    HI_S32 i = 0;
    HI_U32 u32StartFrm = 0, u32EndFrm = 0, u32LastFrm = 0;
    HI_U32 u32FindStart = 0;
    PVR_INDEX_ENTRY_S stEntryTmp = {0};
    HI_U32 u32CurGopSize = 0, u32GopSizeSeg = 0;

    u32StartFrm = handle->stCycMgr.u32StartFrame;
    u32EndFrm = (handle->stCycMgr.u32EndFrame == -1)?0:handle->stCycMgr.u32EndFrame;
    u32LastFrm = (handle->stCycMgr.u32LastFrame == -1)?0:handle->stCycMgr.u32LastFrame;

    if (u32StartFrm >= u32EndFrm)
    {
        handle->stRecIdxInfo.stIdxInfo.u32FrameTotalNum = u32LastFrm - u32StartFrm + u32EndFrm;
    }
    else
    {
        handle->stRecIdxInfo.stIdxInfo.u32FrameTotalNum = u32LastFrm + 1;
    }

    for (i = (HI_S32)u32EndFrm; i >= (HI_S32)u32FindStart; i--)
    {
        if (HI_SUCCESS == PVR_Index_GetFrameByNum(handle, &stEntryTmp, i))
        {
            if (0 != (stEntryTmp.u16FrameTypeAndGop & 0x3fff))
            {
                u32CurGopSize = (stEntryTmp.u16FrameTypeAndGop & 0x3fff) + 1;

                handle->stRecIdxInfo.stIdxInfo.u32GopTotalNum++;
                
                if(0 != handle->stRecIdxInfo.stIdxInfo.u32GopTotalNum)
                {
                    u32GopSizeSeg = (u32CurGopSize/10);
                    u32GopSizeSeg = (u32GopSizeSeg > 12) ? 12 : u32GopSizeSeg;
                    handle->stRecIdxInfo.stIdxInfo.u32GopSizeInfo[u32GopSizeSeg]++;
                }

                if (handle->stRecIdxInfo.stIdxInfo.u32MaxGopSize < u32CurGopSize)
                {
                    handle->stRecIdxInfo.stIdxInfo.u32MaxGopSize = u32CurGopSize;
                }

                i -= (HI_S32)(stEntryTmp.u16FrameTypeAndGop & 0x3fff);
            }
        }

        if ((u32StartFrm >= u32EndFrm)&&(i <= 0))
        {
            u32FindStart = u32StartFrm;
            i = (HI_S32)u32LastFrm;
            u32EndFrm = u32LastFrm;
            continue;
        }
    }

    if (HI_SUCCESS == PVR_Index_GetFrameByNum(handle, &stEntryTmp, u32FindStart))
    {
        if (0 != (stEntryTmp.u16FrameTypeAndGop & 0x3fff))
        {
            handle->stRecIdxInfo.stIdxInfo.u32GopTotalNum--;
            u32GopSizeSeg = (u32CurGopSize/10);
            u32GopSizeSeg = (u32GopSizeSeg > 12) ? 12 : u32GopSizeSeg;
            handle->stRecIdxInfo.stIdxInfo.u32GopSizeInfo[u32GopSizeSeg]--;
        }
    }
}

HI_VOID PVR_Index_GetRecIdxInfo(PVR_INDEX_HANDLE handle)
{
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo = {0};
    HI_S32 s32ReadRet = 0;

    if (HI_SUCCESS != PVRIndexGetHeaderInfo(handle->s32HeaderFd, &stIdxHeaderInfo))
    {
        HI_ERR_PVR("Can't get index header info.\n");
        return;
    }

    s32ReadRet = PVR_READ(&(handle->stRecIdxInfo), 
                            sizeof(PVR_REC_INDEX_INFO_S), 
                            handle->s32HeaderFd, 
                            PVR_GET_IDX_INFO_OFFSET(stIdxHeaderInfo));

    if (s32ReadRet != sizeof(PVR_REC_INDEX_INFO_S))
    {
        HI_ERR_PVR("Write index info fail ret=0x%x\n", s32ReadRet);
        return;
    }
}


HI_BOOL PVR_Index_CheckSetRecReachPlay(PVR_INDEX_HANDLE handle, HI_U32 u32MinDistance)
{
    HI_U32 u32ReadFrame = 0;
    HI_U32 u32StartFrame = 0;
    HI_U32 u32EndFrame = 0;
    HI_U32 u32LastFrame = 0;

    PVR_INDEX_LOCK(&handle->stMutex);

    if (handle->bRecReachPlay == HI_TRUE)
    {
        PVR_INDEX_UNLOCK(&handle->stMutex);
        return HI_TRUE;
    }

    u32StartFrame = handle->stCycMgr.u32StartFrame;
    u32EndFrame   = (handle->stCycMgr.u32EndFrame == -1)?0:handle->stCycMgr.u32EndFrame;
    u32ReadFrame  = handle->u32ReadFrame;
    u32LastFrame  = (handle->stCycMgr.u32LastFrame == -1)?0:handle->stCycMgr.u32LastFrame;

    if (u32StartFrame < u32EndFrame) /* NOT cycled, 0--S--R--E--L  */
    {

        if (u32StartFrame + u32MinDistance >= u32ReadFrame)
        {
            HI_WARN_PVR("Rec almost over Play: S/R/E/L: %u,%u,%u,%u.\n",
                         u32StartFrame, u32ReadFrame,u32EndFrame, u32LastFrame);
            handle->bRecReachPlay = HI_TRUE;
            PVR_INDEX_UNLOCK(&handle->stMutex);
            return HI_TRUE;
        }
        else
        {
            PVR_INDEX_UNLOCK(&handle->stMutex);
            return HI_FALSE;
        }
    }
    else  /* Cycled */
    {
        if (u32ReadFrame > u32StartFrame) /* 0----E----S----R--L */
        {
            if (u32ReadFrame - u32StartFrame > u32MinDistance)
            {
                PVR_INDEX_UNLOCK(&handle->stMutex);
                return HI_FALSE;
            }
            else
            {
                HI_WARN_PVR("Rec almost over Play: E/S/R/L: %u,%u,%u,%u.\n",
                             u32EndFrame, u32StartFrame, u32ReadFrame, u32LastFrame);
                handle->bRecReachPlay = HI_TRUE;
                PVR_INDEX_UNLOCK(&handle->stMutex);
                return HI_TRUE;
            }
        }
        else /* 0--R--E----S--L */
        {
            HI_U32 u32StartToLast;

            u32StartToLast = u32LastFrame - u32StartFrame;

            if (u32StartToLast + u32ReadFrame > u32MinDistance)
            {
                PVR_INDEX_UNLOCK(&handle->stMutex);
                return HI_FALSE;
            }
            else
            {
                HI_ERR_PVR("Rec almost over Play: R/E/S/L: %u/%u/%u/%u.\n",
                            u32ReadFrame, u32EndFrame, u32StartFrame, u32LastFrame);

                handle->bRecReachPlay = HI_TRUE;
                PVR_INDEX_UNLOCK(&handle->stMutex);
                return HI_TRUE;
            }
        }
    }
}


/*****************************************************************************
 Prototype       : PVR_IndexGetNextEntry
 Description     : to find next frame,
 first, check whether the read pointer is beyond the mark(by the result of read interface, if failure, the device maybe be unplugged)
 sedond, read frame
 last, move the read pointer to the next frame. again, check the valid, because, the end maybe not the last frame of index file
 so, this interface can be used for checking whether it reach to the end of the index file.
 Input           : handle  **
                   pEntry  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/17
    Author       : q46153
    Modification : Created function

*****************************************************************************/
HI_S32 PVRIndexGetNextEntry(PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pEntry)
{
    ssize_t readNum;
    HI_U32 u32OldFrame;

    HI_ASSERT_RET(NULL != handle);
    HI_ASSERT_RET(NULL != pEntry);

    /*
    HI_INFO_PVR("S:%d, E:%d, L:%d, R:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
               handle->stCycMgr.u32LastFrame, handle->u32ReadFrame);
    */
    //readNum = PVR_READALL(pEntry, sizeof(PVR_INDEX_ENTRY_S), handle->s32ReadFd, (handle->u32ReadFrame * sizeof(PVR_INDEX_ENTRY_S)));
    PVR_READ_INDEX(readNum,pEntry, sizeof(PVR_INDEX_ENTRY_S), handle->s32ReadFd,
                             (handle->u32ReadFrame * sizeof(PVR_INDEX_ENTRY_S)), handle);

    if (readNum != (ssize_t)sizeof(PVR_INDEX_ENTRY_S))
    {
        if (-1 == readNum)
        {
            HI_WARN_PVR("read index error: ");
            return HI_ERR_PVR_FILE_CANT_READ;
        }
        else
        {
            HI_INFO_PVR("read to end, cur and next is same: S:%d, E:%d, L:%d, C:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
                   handle->stCycMgr.u32LastFrame, handle->u32ReadFrame);
            return HI_ERR_PVR_FILE_TILL_END;
        }
    }

    u32OldFrame = handle->u32ReadFrame;
    PVRIndexCycMoveReadFrame(handle, 1);
    if (u32OldFrame == handle->u32ReadFrame)
    {
        HI_WARN_PVR("read to end, S:%d, E:%d, L:%d, C:%d, O:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
                   handle->stCycMgr.u32LastFrame, handle->u32ReadFrame, u32OldFrame);
        return HI_ERR_PVR_FILE_TILL_END;
    }

    HI_INFO_PVR("after get: Read frame:%u, Type:%u, offset:%llu, glboffset %lld PTS:%u, Time:%u \n", handle->u32ReadFrame,
                PVR_INDEX_get_frameType(pEntry), pEntry->u64Offset, pEntry->u64GlobalOffset,pEntry->u32PtsMs, pEntry->u32DisplayTimeMs);
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVR_IndexGetPlayNextEntry
 Description     : to find next frame of current play frame,
 Input           : handle  **
                   pEntry  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 
    Author       : 
    Modification : Created function

*****************************************************************************/
HI_S32 PVRIndexGetPlayNextEntry(PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pEntry)
{
    ssize_t readNum;

    HI_ASSERT_RET(NULL != handle);
    HI_ASSERT_RET(NULL != pEntry);

    PVR_READ_INDEX(readNum, pEntry, sizeof(PVR_INDEX_ENTRY_S), handle->s32ReadFd,
                   (handle->u32ReadFrame * sizeof(PVR_INDEX_ENTRY_S)), handle);

    if (readNum != (ssize_t)sizeof(PVR_INDEX_ENTRY_S))
    {
        if (-1 == readNum)
        {
            HI_WARN_PVR("read index error: ");
            return HI_ERR_PVR_FILE_CANT_READ;
        }
        else
        {
            HI_INFO_PVR("read to end, cur and next is same: S:%d, E:%d, L:%d, C:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
                   handle->stCycMgr.u32LastFrame, handle->u32ReadFrame);
            return HI_ERR_PVR_FILE_TILL_END;
        }
    }
    HI_INFO_PVR("after get: Read frame:%u, Type:%u, offset:%llu, PTS:%u, Time:%u \n", handle->u32ReadFrame,
                PVR_INDEX_get_frameType(pEntry), pEntry->u64Offset, pEntry->u32PtsMs, pEntry->u32DisplayTimeMs);
    return HI_SUCCESS;
}



/*****************************************************************************
 Prototype       : PVRIndexGetNextIEntry
 Description     : to find next I frame
 Input           : handle  **
                   pEntry  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/17
    Author       : q46153
    Modification : Created function

*****************************************************************************/
STATIC INLINE HI_S32 PVRIndexGetNextIEntry(const PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pEntry)
{
    HI_S32 ret;

    HI_ASSERT_RET(NULL != handle);
    HI_ASSERT_RET(NULL != pEntry);

    while (1)
    {
        ret = PVRIndexGetNextEntry(handle, pEntry);
        if (ret != HI_SUCCESS)
        {
            return ret;
        }

        /* I frame, and not found the frame upflow flag*/
        if (PVR_INDEX_is_Iframe(pEntry) && !(pEntry->u16UpFlowFlag))
        {
            break;
        }
    }

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVR_IndexGetPreEntry
 Description     : to find previous frame
 Input           : handle  **
                   pEntry  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/17
    Author       : q46153
    Modification : Created function

*****************************************************************************/
STATIC INLINE HI_S32 PVRIndexGetPreEntry(PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pEntry)
{
    ssize_t readNum ;
    HI_U32 u32OldFrame;

    HI_ASSERT_RET(NULL != handle);
    HI_ASSERT_RET(NULL != pEntry);

    HI_INFO_PVR("S:%d, E:%d, L:%d, R:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
               handle->stCycMgr.u32LastFrame, handle->u32ReadFrame);

    u32OldFrame = handle->u32ReadFrame;
    PVRIndexCycMoveReadFrame(handle, (HI_S32)(-1));

    if (u32OldFrame == handle->u32ReadFrame)
    {
        HI_WARN_PVR("read to start, cur and pre is same: S:%d, E:%d, L:%d, C:%d, O:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
                   handle->stCycMgr.u32LastFrame, handle->u32ReadFrame, u32OldFrame);
        return HI_ERR_PVR_FILE_TILL_START;
    }

    PVR_READ_INDEX(readNum, pEntry, sizeof(PVR_INDEX_ENTRY_S), handle->s32ReadFd,
                             (handle->u32ReadFrame * sizeof(PVR_INDEX_ENTRY_S)), handle);
    if (readNum != (ssize_t)sizeof(PVR_INDEX_ENTRY_S))
    {
        if (-1 == readNum)
        {
            HI_WARN_PVR("read index error: ");
            return HI_ERR_PVR_FILE_CANT_READ;
        }
        else
        {
            HI_WARN_PVR("read to start,  S:%d, E:%d, L:%d, C:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
                   handle->stCycMgr.u32LastFrame, handle->u32ReadFrame);
            return HI_ERR_PVR_FILE_TILL_START;
        }
    }

    HI_INFO_PVR("after get: R:%u, Type:%u, offset:%llu, PTS:%u \n", handle->u32ReadFrame,
                PVR_INDEX_get_frameType(pEntry), pEntry->u64Offset, pEntry->u32PtsMs);

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVR_IndexGetPreIEntry
 Description     : to find the previous I frame
 Input           : handle  **
                   pEntry  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/17
    Author       : q46153
    Modification : Created function

*****************************************************************************/
STATIC INLINE HI_S32 PVRIndexGetPreIEntry(const PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pEntry)
{
    HI_S32 ret;

    HI_ASSERT_RET(NULL != handle);
    HI_ASSERT_RET(NULL != pEntry);

    while (1)
    {
        ret = PVRIndexGetPreEntry(handle, pEntry);
        if (ret != HI_SUCCESS)
        {
            return ret;
        }

        /* I frame, and not found the frame upflow flag*/
        if (PVR_INDEX_is_Iframe(pEntry) && !(pEntry->u16UpFlowFlag))
        {
            break;
        }
    }


    return HI_SUCCESS;
}


/*****************************************************************************
 Prototype       : PVR_IndexGetCurrentEntry
 Description     : to get current frame information
                    if the read pointer reach to the end, it will return failure, because of it reach to the end of the file .
 Input           : handle  **
                   pEntry  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/17
    Author       : q46153
    Modification : Created function

*****************************************************************************/
STATIC INLINE HI_S32 PVRIndexGetCurrentEntry(const PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pEntry)
{
    ssize_t readNum ;

    HI_ASSERT_RET(handle != NULL);
    HI_ASSERT_RET(pEntry != NULL);

    HI_INFO_PVR("S:%d, E:%d, L:%d, C:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
               handle->stCycMgr.u32LastFrame, handle->u32ReadFrame);

    if (handle->u32ReadFrame == handle->stCycMgr.u32EndFrame)
    {
        HI_WARN_PVR("read to end, S:%d, E:%d, L:%d, C:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
               handle->stCycMgr.u32LastFrame, handle->u32ReadFrame);
        return HI_ERR_PVR_FILE_TILL_END;
    }

    PVR_READ_INDEX(readNum, pEntry, sizeof(PVR_INDEX_ENTRY_S), handle->s32ReadFd,
                             (handle->u32ReadFrame * sizeof(PVR_INDEX_ENTRY_S)), handle);
    if (readNum != (ssize_t)sizeof(PVR_INDEX_ENTRY_S))
    {
        /* PVR play to the end of file, no way for PVR_EVENT_PLAY_EOF, AI7D02611 */
        if (-1 == readNum)
        {
            HI_WARN_PVR("read failed in PVRIndexGetCurrentEntry");
            return HI_ERR_PVR_FILE_CANT_READ;
        }
        else
        {
            HI_WARN_PVR("read to end, S:%d, E:%d, L:%d, C:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
                   handle->stCycMgr.u32LastFrame, handle->u32ReadFrame);
            return HI_ERR_PVR_FILE_TILL_END;
        }
    }

    HI_INFO_PVR("frame cur <Read frame:%u, Type:%u, offset:%llu, PTS:%u> \n", handle->u32ReadFrame,
                PVR_INDEX_get_frameType(pEntry), pEntry->u64Offset, pEntry->u32PtsMs);

    return HI_SUCCESS;
}

STATIC INLINE HI_S32 PVRIndexGetEntryByNum(const PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pEntry, HI_U32 u32FrameNum)
{
    ssize_t readNum ;
    PVR_READ_INDEX(readNum, pEntry, sizeof(PVR_INDEX_ENTRY_S), handle->s32ReadFd,
                             (u32FrameNum * sizeof(PVR_INDEX_ENTRY_S)), handle);
    if (readNum != (ssize_t)sizeof(PVR_INDEX_ENTRY_S))
    {
        if (-1 == readNum)
        {
            HI_WARN_PVR("read failed in PVRIndexGetEntryByNum");
            return HI_ERR_PVR_FILE_CANT_READ;
        }
        else
        {
            HI_WARN_PVR("read to end, S:%d, E:%d, L:%d, C:%d G:%d\n", handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame,
                   handle->stCycMgr.u32LastFrame, handle->u32ReadFrame, u32FrameNum);
            return HI_ERR_PVR_FILE_TILL_END;
        }
    }

    return HI_SUCCESS;
}


STATIC HI_U32 PVRIndexSeachByTime(PVR_INDEX_HANDLE handle, HI_U32 timeWant,
                                  HI_U32 start, HI_U32 end,  PVR_FILE seekFd)
{
    ssize_t l_readNum;
    HI_U32 target;
    PVR_INDEX_ENTRY_S entry;
    HI_U32 nextStart, nextEnd;

    memset(&entry, 0, sizeof(PVR_INDEX_ENTRY_S));   
    target = (start + end)/2;

    if (target == start || target == end)
    {
        HI_WARN_PVR("PVRIndexSeachByTime end, ret:%d\n", target);
        return target;
    }

    /* get target's time */
    PVR_READ_INDEX(l_readNum, &entry, sizeof(PVR_INDEX_ENTRY_S), seekFd,
                               (target*sizeof(PVR_INDEX_ENTRY_S)), handle);
    if (l_readNum != (ssize_t)sizeof(PVR_INDEX_ENTRY_S))
    {
        HI_ERR_PVR("read err,  want:%u, get:%u, off:%u\n", (sizeof(PVR_INDEX_ENTRY_S)), (l_readNum), target*sizeof(PVR_INDEX_ENTRY_S));
        if (-1 == l_readNum)
        {
            HI_WARN_PVR("read index error: ");
            return 0;
        }
        else if (0 == l_readNum) /* if meet error at the end of file, return the last frame AI7D03033 */
        {
            HI_U32 u32LastPos;
            u32LastPos = (HI_U32)PVR_SEEK(seekFd, (off_t)(0 - (HI_S32)sizeof(PVR_INDEX_ENTRY_S)), SEEK_END);
            if ((HI_S32)u32LastPos >= 0)
            {
                (void)PVR_READ(&entry, sizeof(PVR_INDEX_ENTRY_S), seekFd, u32LastPos);
                return (u32LastPos / sizeof(PVR_INDEX_ENTRY_S));
            }
            else
            {
                HI_WARN_PVR("can't get the last frame\n");
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    HI_INFO_PVR("^^^^ search time:want=%d, target=%d ^^^^\n", timeWant, entry.u32DisplayTimeMs);
    if (entry.u32DisplayTimeMs <= timeWant)
    {
        nextStart = target;
        nextEnd = end;
    }
    else
    {
        nextStart = start;
        nextEnd = target;
    }

    return PVRIndexSeachByTime(handle, timeWant, nextStart, nextEnd, seekFd);
}

/*****************************************************************************
 Prototype       : PVRIndexFindFrameByTime
 Description     : find a frame match the time
 Input           : handle           **
                   offsetFromStart  **
 Output          : None
 Return Value    : the frame ID from start of file.
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/6/30
    Author       : fd
    Modification : Created function

*****************************************************************************/
STATIC INLINE HI_U32 PVRIndexFindFrameByTime(PVR_INDEX_HANDLE handle, HI_U32 u32FindTime)
{
    HI_U32 u32FrameId;
    HI_U32 u32StartFrame;
    HI_U32 u32EndFrame;
    PVR_INDEX_ENTRY_S lastEntry = {0};
    HI_U32 u32Offset;
    HI_S32 s32Read;
    HI_U32 u32LastFrame;

    u32EndFrame   = (handle->stCycMgr.u32EndFrame == -1)?0:handle->stCycMgr.u32EndFrame;
    u32StartFrame = handle->stCycMgr.u32StartFrame;
    u32LastFrame  = (handle->stCycMgr.u32LastFrame == -1)?0:handle->stCycMgr.u32LastFrame;

    memset(&lastEntry, 0, sizeof(PVR_INDEX_ENTRY_S));   
    /* Not rewind, find it directly*/
    if (u32EndFrame > u32StartFrame)
    {
        u32FrameId = PVRIndexSeachByTime(handle, u32FindTime, u32StartFrame,
                                         u32EndFrame,  handle->s32SeekFd);
    }
    else /* Rewind, find it for two part*/
    {
        u32Offset = (HI_U32)(sizeof(PVR_INDEX_ENTRY_S) * (handle->stCycMgr.u32LastFrame));
        PVR_READ_INDEX(s32Read, &lastEntry, sizeof(PVR_INDEX_ENTRY_S), handle->s32SeekFd, u32Offset, handle);
        if (s32Read != (HI_S32)sizeof(PVR_INDEX_ENTRY_S))
        {
            HI_ERR_PVR("HI_PVR_GetFileAttrByFileName-read idx failed\n");
            return (handle->stCycMgr.u32StartFrame);
        }

        HI_INFO_PVR("last entry PTS=%d ms\n", lastEntry.u32DisplayTimeMs);

        if (u32FindTime <= lastEntry.u32DisplayTimeMs)
        {
            HI_WARN_PVR("u32FindTime:%u, u32DisplayTimeMs:%u, find it in the last section\n", u32FindTime,lastEntry.u32DisplayTimeMs);
            u32FrameId = PVRIndexSeachByTime(handle, u32FindTime, u32StartFrame,
                                             u32LastFrame,  handle->s32SeekFd);
        }
        else /* find it in the start part */
        {
            HI_WARN_PVR("u32FindTime:%u, u32DisplayTimeMs:%u, find it in the first section\n", u32FindTime,lastEntry.u32DisplayTimeMs);
            if (0 == handle->stCycMgr.u32EndFrame)
            {
                return handle->stCycMgr.u32EndFrame;
            }
            else
            {
                u32FrameId = PVRIndexSeachByTime(handle, u32FindTime, 0,
                                                 u32EndFrame,  handle->s32SeekFd);
            }
            
        }
    }

    return u32FrameId;
}

/*****************************************************************************
 Prototype       : PVR_Index_SeekByFrame2I
 Description     : seek by frame
 Input           : handle  **
                   offset  ** number of frame
                   whence  ** from start frame
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/28
    Author       : q46153
    Modification : Created function

*****************************************************************************/
HI_S32 PVR_Index_SeekByFrame2I(PVR_INDEX_HANDLE handle, HI_S32 offset, HI_S32 whence)
{
    HI_S32 ret = HI_SUCCESS;
//    HI_S32 pos;
//    HI_U32 maxFrameNum;

    HI_INFO_PVR("whence:%s, offset:%d\n", WHENCE_STRING(whence), offset);

    PVR_INDEX_LOCK(&(handle->stMutex));
    switch (whence)
    {
    case SEEK_SET:
        handle->u32ReadFrame = handle->stCycMgr.u32StartFrame;
        PVRIndexCycMoveReadFrame(handle, offset);
        break;
    case SEEK_CUR:
        PVRIndexCycMoveReadFrame(handle, offset);
        break;
    case SEEK_END:
        handle->u32ReadFrame = handle->stCycMgr.u32EndFrame;
        PVRIndexCycMoveReadFrame(handle, offset);
        break;
    default:
        PVR_INDEX_UNLOCK(&(handle->stMutex));
        return HI_ERR_PVR_INVALID_PARA;
    }

    if ((SEEK_SET == whence) || ((SEEK_CUR == whence) && (offset > 0)))
    {
        ret = PVRIndexGetNextIEntry(handle, &(handle->stCurPlayFrame));
        if (HI_SUCCESS != ret)
        {
            ret = PVRIndexGetPreIEntry(handle, &(handle->stCurPlayFrame));
            if (HI_SUCCESS != ret)
            {
                HI_ERR_PVR("get next I entry error, file end.\n");
            }
        }
        else
        {
            PVRIndexCycMoveReadFrame(handle, -1);
        }
    }

    if ((SEEK_END == whence) || ((SEEK_CUR == whence) && (offset < 0)))
    {
        ret = PVRIndexGetPreIEntry(handle, &(handle->stCurPlayFrame));
        if (HI_SUCCESS != ret)
        {
            ret = PVRIndexGetNextIEntry(handle, &(handle->stCurPlayFrame));
            if (HI_SUCCESS != ret)
            {
                HI_ERR_PVR("get next I entry error, file end.\n");
            }
            else
            {
                PVRIndexCycMoveReadFrame(handle, -1);
            }
        }
    }

    HI_WARN_PVR("Ret:%#x. Cur frame Type:%lu, PTS:%u, at last seekto:%u\n",
               ret,
               PVR_INDEX_get_frameType (&(handle->stCurPlayFrame)),
               handle->stCurPlayFrame.u32PtsMs,
               handle->u32ReadFrame);

    if (ret != HI_SUCCESS)
    {
        HI_ERR_PVR("can not find I frame@both, Err:%#x\n", ret);
        PVR_INDEX_UNLOCK(&(handle->stMutex));
        return ret;
    }

    handle->bRecReachPlay = HI_FALSE;

    PVR_INDEX_UNLOCK(&(handle->stMutex));
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVR_Index_SeekToTime
 Description     : seek the read pointer of index to I frame closed to the time value
 Input           : handle         **
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/06/02
    Author       : j40671
    Modification : Created function
*****************************************************************************/
HI_S32 PVR_Index_SeekToTime(PVR_INDEX_HANDLE handle, HI_U32 u32TimeMs)
{
    HI_U32 frameToSeek;
    HI_U32 offsetEndFrame = 0;
    HI_U32 offsetStartFrame = 0;

    /* frame position to seek by time*/
    frameToSeek = PVRIndexFindFrameByTime(handle, u32TimeMs);

    HI_WARN_PVR("seek to time:%d, frame pos:%u\n", u32TimeMs, frameToSeek);

    if (PVR_IDX_ENABLE_REWIND(handle)) /* rewind */
    {
        if (HI_FALSE == PVRIndexIsFrameValid(frameToSeek, &handle->stCycMgr))
        {
            /* frame position is invalid, so check which close to the frame, and then set it */
            offsetEndFrame = frameToSeek - handle->stCycMgr.u32EndFrame;
            offsetStartFrame = handle->stCycMgr.u32StartFrame - frameToSeek;

            HI_WARN_PVR("frame position(%u) to seek is invalid\n", frameToSeek);
            HI_WARN_PVR("Now startFrame is %u, endFrame is %u, lastFrame is %u\n", handle->stCycMgr.u32StartFrame,
                handle->stCycMgr.u32EndFrame, handle->stCycMgr.u32LastFrame);

            if(offsetStartFrame > offsetEndFrame)
            {
                frameToSeek = handle->stCycMgr.u32EndFrame;
            }
            else
            {
                frameToSeek = handle->stCycMgr.u32StartFrame+10;
            }
        }

        /* frameToSeek should be the offset from u32StartFrame*/
        if (frameToSeek >= handle->stCycMgr.u32StartFrame)
        {
            frameToSeek -= handle->stCycMgr.u32StartFrame;
        }
        else
        {
            frameToSeek = handle->stCycMgr.u32LastFrame - handle->stCycMgr.u32StartFrame + frameToSeek;
        }
    }

    HI_WARN_PVR("seek frame position is %u to PVR_Index_SeekByFrame2I. S:%u, E:%u, L:%u\n", frameToSeek, handle->stCycMgr.u32StartFrame,
                handle->stCycMgr.u32EndFrame, handle->stCycMgr.u32LastFrame);

    return PVR_Index_SeekByFrame2I(handle, (HI_S32)frameToSeek, SEEK_SET);

}

/*****************************************************************************
 Prototype       : PVR_Index_SeekByTime
 Description     : By current time,  the start and end time will offset some time, in millisecond.
 Input           : handle         **
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/06/02
    Author       : j40671
    Modification : Created function
*****************************************************************************/
HI_S32 PVR_Index_SeekByTime(PVR_INDEX_HANDLE handle, HI_S64 s64Offset, HI_S32 whence, HI_U32 u32CurPlayTime)
{
    HI_S32 ret;
    PVR_INDEX_ENTRY_S stFrameTmp = {0};
    HI_U32 u32CurFrmTime;
    HI_U32 u32StartFrmTime;
    HI_U32 u32EndFrmTime;
    HI_U32 u32SeekToTime = 0;
    HI_U32 u32StartFrmPos;
    HI_U32 u32EndFrmPos;

    HI_INFO_PVR("seek pos(%lld) whence:%s.\n", s64Offset,  WHENCE_STRING(whence));

    memset(&stFrameTmp, 0, sizeof(PVR_INDEX_ENTRY_S));    

    u32StartFrmPos = handle->stCycMgr.u32StartFrame;
    if (handle->stCycMgr.u32EndFrame > 0)
    {
        u32EndFrmPos = handle->stCycMgr.u32EndFrame;
    }
    else
    {
        u32EndFrmPos = handle->stCycMgr.u32LastFrame;
    }

    ret = PVRIndexGetEntryByNum(handle, &stFrameTmp, u32StartFrmPos);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PVR("Can't get StartFrame:%d\n", u32StartFrmPos);
        return ret;
    }
    u32StartFrmTime = stFrameTmp.u32DisplayTimeMs;

    ret = PVRIndexGetEntryByNum(handle, &stFrameTmp, u32EndFrmPos);
    if (ret != HI_SUCCESS)
    {
        HI_ERR_PVR("Can't get EndFrame:%d\n", u32EndFrmPos);
        return ret;
    }
    u32EndFrmTime = stFrameTmp.u32DisplayTimeMs;

    u32CurFrmTime = u32CurPlayTime;

    HI_WARN_PVR("frame info start %d:%d, end %d:%d, cur :%d\n",
                 u32StartFrmPos,u32StartFrmTime, u32EndFrmPos,u32EndFrmTime, u32CurFrmTime);

    if (u32CurFrmTime < u32StartFrmTime)
    {
        u32CurFrmTime = u32StartFrmTime;
    }
    if (u32CurFrmTime > u32EndFrmTime)
    {
        u32CurFrmTime = u32EndFrmTime;
    }

    switch (whence)
    {
    case SEEK_SET:
        u32SeekToTime = (HI_S32)s64Offset;
        break;
    case SEEK_CUR:
        u32SeekToTime = u32CurFrmTime + (HI_S32)s64Offset;
        break;
    case SEEK_END:
        u32SeekToTime = u32EndFrmTime + (HI_S32)s64Offset;
        break;
    default:
        return HI_ERR_PVR_INVALID_PARA;
    }

    if ((HI_S32)u32SeekToTime > (HI_S32)u32EndFrmTime) /* over the end, set it the end */
    {
        u32SeekToTime = u32EndFrmTime;
    }
    else if ((HI_S32)u32SeekToTime < (HI_S32)u32StartFrmTime) /* less the start, set it the start */
    {
        u32SeekToTime = u32StartFrmTime;
    }

    HI_WARN_PVR("seek to time: %u.  whence:%s, offset:%lld, start:%d, end:%d, cur:%d\n",
                 u32SeekToTime, WHENCE_STRING(whence), s64Offset, u32StartFrmTime, u32EndFrmTime, u32CurFrmTime);

    return PVR_Index_SeekToTime(handle, u32SeekToTime);
}

/*****************************************************************************
 Prototype       : PVR_Index_SeekToStart
 Description     : move the read pointer of  index to the start frame. if recording, move it direction backward more 20 frames.
 Input           : handle         **
                   pFrame         **
                   pDisplayTimes  **
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/09/21
    Author       : j40671
    Modification : Created function

*****************************************************************************/
HI_S32 PVR_Index_SeekToStart(PVR_INDEX_HANDLE handle)
{
    HI_U32 u32BeforeSeek;

    HI_ASSERT_RET(handle != NULL);

    PVR_INDEX_LOCK(&(handle->stMutex));
    handle->u32ReadFrame = handle->stCycMgr.u32StartFrame;
    handle->bRecReachPlay = HI_FALSE;
    u32BeforeSeek = handle->u32ReadFrame;

    if ((handle->bIsRec) && (handle->stCycMgr.u32StartFrame >= handle->stCycMgr.u32EndFrame))
    {
        PVRIndexCycMoveReadFrame(handle, PVR_TPLAY_MIN_DISTANCE);
    }

    HI_WARN_PVR("Seek to start, %u --> %u s/e/l %d/%d/%d\n", 
                 u32BeforeSeek, handle->u32ReadFrame, handle->stCycMgr.u32StartFrame, 
                 handle->stCycMgr.u32EndFrame, handle->stCycMgr.u32LastFrame);

    PVR_INDEX_UNLOCK(&(handle->stMutex));

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVR_Index_SeekToEnd
 Description     : move the read pointer of index to the end frame
 Input           : handle         **
                   pFrame         **
                   pDisplayTimes  **
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/09/21
    Author       : j40671
    Modification : Created function

*****************************************************************************/
HI_S32 PVR_Index_SeekToEnd(PVR_INDEX_HANDLE handle)
{
    HI_ASSERT_RET(handle != NULL);

    PVR_INDEX_LOCK(&(handle->stMutex));
    HI_WARN_PVR("seek to end\n");

    handle->u32ReadFrame = handle->stCycMgr.u32EndFrame;
    handle->bRecReachPlay = HI_FALSE;
    PVR_INDEX_UNLOCK(&(handle->stMutex));

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVR_Index_SeekToPauseOrStart
 Description     : on starting to play, seek the read pointer of index to the marked pause frame or start frame.
                        if exist paused frame, seek it to that.
                        if rewritten the pause frame, seek it to the start frame
 Input           : handle         **
                   pFrame         **
                   pDisplayTimes  **
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/06/02
    Author       : j40671
    Modification : Created function

*****************************************************************************/
HI_S32 PVR_Index_SeekToPauseOrStart(PVR_INDEX_HANDLE handle)
{
    HI_S32 ret = HI_SUCCESS;
    PVR_INDEX_ENTRY_S startEntry;
    HI_U32 u32StartFrameNum;
    HI_U32 u32SeekToPos;

    HI_ASSERT_RET(handle != NULL);

    memset(&startEntry, 0, sizeof(PVR_INDEX_ENTRY_S));

    PVR_INDEX_LOCK(&(handle->stMutex));

    /* have been paused, play from pause postion, if the positiong haven't been rewritten by rewind file*/
    if (handle->u64PauseOffset != PVR_INDEX_PAUSE_INVALID_OFFSET)
    {
        HI_ASSERT(handle->u64PauseOffset <= handle->u64GlobalOffset);

        /* straight recording, the start should move direction to the backward, hold some frame(about 20 frames), which prevent  from catching up the live */
        u32StartFrameNum = PVRIndexCalcNewPos(handle, handle->stCycMgr.u32StartFrame, 20);

        ret = PVRIndexGetEntryByNum(handle, &startEntry, u32StartFrameNum);
        if (ret != HI_SUCCESS)
        {
            HI_ERR_PVR("Can't get StartFrame:%d\n", handle->stCycMgr.u32StartFrame);
            PVR_INDEX_UNLOCK(&(handle->stMutex));
            return ret;
        }

        /* check whether pause postion is rewritten or not, if the offset of start frame more than pause frame, it implies rewrite the pause frame */
        if (startEntry.u64GlobalOffset >= handle->u64PauseOffset)
        {
            /* on rewriting, seek it to the start frame */
            u32SeekToPos = u32StartFrameNum;
            HI_INFO_PVR("Pause frame was covered, so seek to start frame:%u\n", u32SeekToPos);
        }
        else
        {
            /* case, not rewrite pause frame, seek to pause frame */
            u32SeekToPos = handle->u32PauseFrame;
            HI_INFO_PVR("Seek to pause frame:%u\n", u32SeekToPos);
        }

        handle->u32ReadFrame = u32SeekToPos;
        handle->u64PauseOffset = PVR_INDEX_PAUSE_INVALID_OFFSET;
        handle->u32PauseFrame = 0;
    }

    PVR_INDEX_UNLOCK(&(handle->stMutex));
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVR_Index_GetNextFrame
 Description     : get next frame for decode
 Input           : handle         **
                   pFrame         **
                   pDisplayTimes  **
 Output          : None
 Return Value    :
 Global Variable
    Read Only    :
    Read & Write :
  History
  1.Date         : 2008/4/28
    Author       : q46153
    Modification : Created function

*****************************************************************************/
HI_S32 PVR_Index_GetNextFrame(PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pstFrame)
{
    HI_S32 ret;

    HI_ASSERT_RET(handle != NULL);
    HI_ASSERT_RET(pstFrame != NULL);

    PVR_INDEX_LOCK(&(handle->stMutex));

    ret = PVRIndexGetNextEntry(handle, pstFrame);
    if (HI_SUCCESS != ret)
    {
        HI_INFO_PVR("get next entry error, file end.\n");
        PVR_INDEX_UNLOCK(&(handle->stMutex));
        return ret;
    }

    if (1 == pstFrame->u16UpFlowFlag)
    {
        ret = PVRIndexGetNextIEntry(handle, pstFrame);
        if (HI_SUCCESS != ret)
        {
            HI_INFO_PVR("get next I entry error, file end.\n");
            PVR_INDEX_UNLOCK(&(handle->stMutex));
            return ret;
        }
    }
    PVR_INDEX_UNLOCK(&(handle->stMutex));
    return HI_SUCCESS;
}

HI_S32 PVR_Index_GetPreFrame(PVR_INDEX_HANDLE handle, PVR_INDEX_ENTRY_S *pFrame)
{
    HI_S32 ret;

    HI_ASSERT_RET(handle != NULL);
    HI_ASSERT_RET(pFrame != NULL);

    PVR_INDEX_LOCK(&(handle->stMutex));

    ret = PVRIndexGetPreEntry(handle, pFrame);
    if (HI_SUCCESS != ret)
    {
        HI_INFO_PVR("get pre entry error, file end.\n");
        PVR_INDEX_UNLOCK(&(handle->stMutex));
        return ret;
    }

    if (1 == pFrame->u16UpFlowFlag)
    {
        ret = PVRIndexGetPreIEntry(handle, pFrame);
        if (HI_SUCCESS != ret)
        {
            HI_INFO_PVR("get pre I entry error, file end.\n");
            PVR_INDEX_UNLOCK(&(handle->stMutex));
            return ret;
        }
    }
    PVR_INDEX_UNLOCK(&(handle->stMutex));
    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVR_Index_GetCurrentFrame
 Description     : get the frame pointed to the current read pointer. not move the read pointer
 Input           : handle         **
                   pFrame         **
                   pDisplayTimes  **
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/06/02
    Author       : j40671
    Modification : Created function
*****************************************************************************/
HI_S32 PVR_Index_GetCurrentFrame(const PVR_INDEX_HANDLE handle,  PVR_INDEX_ENTRY_S *pEntry)
{
    HI_S32 ret;
    HI_ASSERT_RET(NULL != handle);
    HI_ASSERT_RET(NULL != pEntry);

    PVR_INDEX_LOCK(&(handle->stMutex));

    ret = PVRIndexGetCurrentEntry(handle, pEntry);

    PVR_INDEX_UNLOCK(&(handle->stMutex));
    return ret;
}


/*****************************************************************************
 Prototype       : PVR_Index_GetFrameByNum
 Description     : get the index by the num. but not move the read pointer
 Input           : handle         **
                   pFrame         **
                   num  **
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/06/02
    Author       : j40671
    Modification : Created function
*****************************************************************************/

HI_S32 PVR_Index_GetFrameByNum(const PVR_INDEX_HANDLE handle,  PVR_INDEX_ENTRY_S *pEntry, HI_U32 num)
{
    HI_S32 ret;
    HI_ASSERT_RET(NULL != handle);
    HI_ASSERT_RET(NULL != pEntry);

    PVR_INDEX_LOCK(&(handle->stMutex));

    ret = PVRIndexGetEntryByNum(handle,pEntry,num);

    PVR_INDEX_UNLOCK(&(handle->stMutex));
    return ret;
}

HI_S32 PVR_Index_QueryFrameByTime(const PVR_INDEX_HANDLE handle, HI_U32 u32SearchTime, PVR_INDEX_ENTRY_S *pEntry, HI_U32 *pu32Pos)
{
    HI_U32 u32PtsPos;
    HI_S32 ret;

    HI_ASSERT_RET(NULL != handle);
    HI_ASSERT_RET(NULL != pEntry);

    PVR_INDEX_LOCK(&(handle->stMutex));

    u32PtsPos = PVRIndexFindFrameByTime(handle, u32SearchTime);
    *pu32Pos =  u32PtsPos;
    HI_WARN_PVR("search Time:%u, Pos:%u\n", u32SearchTime, u32PtsPos);

    ret = PVRIndexGetEntryByNum(handle, pEntry, u32PtsPos);
    if (ret != HI_SUCCESS)
    {
        if (HI_ERR_PVR_FILE_TILL_END == ret)
        {
            if (HI_SUCCESS != PVRIndexGetEntryByNum(handle, pEntry, --u32PtsPos))
            {
                HI_ERR_PVR("Can't get Frame:%d\n", u32PtsPos);
                PVR_INDEX_UNLOCK(&(handle->stMutex));
                return ret;
            }
        }
    }
    HI_WARN_PVR("Pos:%u, time:%u\n", u32PtsPos, pEntry->u32DisplayTimeMs);

    PVR_INDEX_UNLOCK(&(handle->stMutex));

    return HI_SUCCESS;
}

/*****************************************************************************
 Prototype       : PVR_Index_MarkPausePos
 Description     : mark a flag for timeshift, where flag current record position. if start timeshift, play it from this position
 Input           : handle         **
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/06/02
    Author       : j40671
    Modification : Created function
*****************************************************************************/
HI_S32 PVR_Index_MarkPausePos(PVR_INDEX_HANDLE handle)
{
    /* save the frame number of current recording frame*/

#ifdef HI_PVR_L2_CACHE_SUPPORT
    handle->u32PauseFrame = handle->stCycMgr.u32EndFrame;
#else
    handle->u32PauseFrame = handle->u32WriteFrame;
#endif

    /* save the absolute offset for the current frame, used for checking whether the pause position rewrote or not by rewind, on playing */
    handle->u64PauseOffset = handle->u64GlobalOffset;

    HI_WARN_PVR("<<==PVR_Index_MarkPausePos: frame=%d, global offset=%lld.\n",
                handle->u32PauseFrame, handle->u64PauseOffset);
    return HI_SUCCESS;

}

HI_VOID PVR_Index_GetIdxFileName(HI_CHAR* pIdxFileName, HI_CHAR* pSrcFileName)
{
    HI_CHAR* pSearch = NULL;
    HI_CHAR* pAppend = NULL;

    pSearch = strstr(pSrcFileName, ".idx");
    while(NULL != pSearch)
    {
        if (NULL != pSearch)
        {
            pAppend = pSearch;
            pSearch = strstr(pSearch + 1, ".idx");
        }
    }

    /* make sure it end with the .idx */
    if (NULL != pAppend && *(pAppend + 4) == 0)
    {
        strncpy(pIdxFileName, pSrcFileName,strlen(pSrcFileName)+1);
    }
    else
    {
        snprintf(pIdxFileName, PVR_MAX_FILENAME_LEN,"%s.idx", pSrcFileName);
    }
    return;
}


/*****************************************************************************
 Prototype       : PVR_Index_PlayGetFileAttrByFileName
 Description     : get the current state of the record file by file name. and can't get it without including index file.
 Input           : handle         **
 Output          : None
 Return Value    :
  History
  1.Date         : 2010/06/02
    Author       : j40671
    Modification : Created function
*****************************************************************************/
HI_S32 PVR_Index_PlayGetFileAttrByFileName(const HI_CHAR *pFileName, PVR_INDEX_HANDLE pIdxHandle, HI_UNF_PVR_FILE_ATTR_S *pAttr)
{
    HI_S32            fdIdx;
    HI_CHAR           szIndexName[PVR_MAX_FILENAME_LEN] = {0};
    HI_S32            readNum;
    PVR_INDEX_ENTRY_S startEntry = {0};
    PVR_INDEX_ENTRY_S endEntry = {0};
    HI_S32            s32Offset;
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo = {0};
    HI_BOOL bRetry = HI_FALSE;

    if (!pFileName)
    {
        return HI_ERR_PVR_NUL_PTR;
    }
    if (!pAttr)
    {
        return HI_ERR_PVR_NUL_PTR;
    }

    memset(pAttr,0x0,sizeof(HI_UNF_PVR_FILE_ATTR_S));

    if (HI_NULL != pIdxHandle)
    {
        do
        {
            if (HI_SUCCESS != PVRIndexGetEntryByNum(pIdxHandle, &startEntry, pIdxHandle->stCycMgr.u32StartFrame))
            {
                HI_WARN_PVR("read start_idx failed, start frm:%d end frm:%d last frm:%d.\n", 
                            pIdxHandle->stCycMgr.u32StartFrame, 
                            pIdxHandle->stCycMgr.u32EndFrame,
                            pIdxHandle->stCycMgr.u32LastFrame);
                bRetry = HI_TRUE;
                break;
            }

            if (HI_SUCCESS != PVRIndexGetEntryByNum(pIdxHandle, &endEntry, pIdxHandle->stCycMgr.u32EndFrame))
            {
                HI_WARN_PVR("read end_idx failed, start frm:%d end frm:%d last frm:%d.\n", 
                            pIdxHandle->stCycMgr.u32StartFrame, 
                            pIdxHandle->stCycMgr.u32EndFrame,
                            pIdxHandle->stCycMgr.u32LastFrame);
                bRetry = HI_TRUE;
                break;
            }

            if (pIdxHandle->stCycMgr.u32EndFrame > pIdxHandle->stCycMgr.u32StartFrame)
            {
                pAttr->u32FrameNum = pIdxHandle->stCycMgr.u32EndFrame
                                     - pIdxHandle->stCycMgr.u32StartFrame;
            }
            else
            {
                pAttr->u32FrameNum = pIdxHandle->stCycMgr.u32LastFrame
                                     - pIdxHandle->stCycMgr.u32StartFrame
                                     + pIdxHandle->stCycMgr.u32EndFrame;
            }
            pAttr->u32StartTimeInMs = startEntry.u32DisplayTimeMs;
            pAttr->u32EndTimeInMs = endEntry.u32DisplayTimeMs;

            if (0 < pIdxHandle->stCycMgr.u32CycTimes)
            {
                pAttr->u64ValidSizeInByte = pIdxHandle->stCycMgr.u64MaxCycSize;
            }
            else
            {
                pAttr->u64ValidSizeInByte = endEntry.u64Offset + endEntry.u32FrameSize;
            }
            pAttr->enIdxType = (HI_UNF_PVR_REC_INDEX_TYPE_E)(startEntry.u16IndexType);
        }while(0);

    }
    /*Add condition bRetry ,As some times read index entry may failed ,
    such as rec just start.there is no one index entry.
    we should open the index file again and retry. for DTS2014042105555*/
    if((HI_NULL == pIdxHandle) || bRetry)
    {
        PVR_Index_GetIdxFileName(szIndexName, (HI_CHAR*)pFileName);
        fdIdx = PVR_OPEN(szIndexName, PVR_FOPEN_MODE_DATA_READ);
        if (fdIdx < 0)
        {
            HI_ERR_PVR("can not open index file:%s\n", szIndexName);
            return HI_ERR_PVR_FILE_CANT_OPEN;
        }

        if (HI_SUCCESS != PVRIndexGetHeaderInfo(fdIdx, &stIdxHeaderInfo))
        {
            HI_ERR_PVR("No Header Info in index File:%s\n", szIndexName);
            PVR_CLOSE(fdIdx);
            return HI_ERR_PVR_INDEX_FORMAT_ERR;
        }

        if (((0 == stIdxHeaderInfo.stCycInfo.u32StartFrame)
            && (0 == stIdxHeaderInfo.stCycInfo.u32EndFrame))
            || (0 == stIdxHeaderInfo.stCycInfo.u32LastFrame))
        {
            HI_WARN_PVR("No frame in index File:%s\n", szIndexName);
            pAttr->u32FrameNum = 0;
            pAttr->u32StartTimeInMs = 0;
            pAttr->u32EndTimeInMs = 0;
            pAttr->u64ValidSizeInByte = 0;
            pAttr->enIdxType = HI_UNF_PVR_REC_INDEX_TYPE_NONE;

            PVR_CLOSE(fdIdx);
            return HI_SUCCESS;
        }

        /* deal it with the same mode, regardless of rewind of the index file */

        /* read the start frame info */
        s32Offset = (HI_S32)(stIdxHeaderInfo.u32HeaderLen + sizeof(PVR_INDEX_ENTRY_S) * stIdxHeaderInfo.stCycInfo.u32StartFrame);
        readNum = PVR_READ(&startEntry, sizeof(PVR_INDEX_ENTRY_S), fdIdx, s32Offset);
        if (readNum != (HI_S32)sizeof(PVR_INDEX_ENTRY_S))
        {
            HI_ERR_PVR("read start_idx failed, offset:%d.\n", s32Offset);
            HI_ERR_PVR("The index file is too small, can't play.\n");
            PVR_CLOSE(fdIdx);
            return HI_ERR_PVR_FILE_CANT_READ;
        }

        /* read the end frame info */
        s32Offset = (HI_S32)(stIdxHeaderInfo.u32HeaderLen + sizeof(PVR_INDEX_ENTRY_S) *
                    stIdxHeaderInfo.stCycInfo.u32EndFrame);
        readNum = PVR_READ(&endEntry, sizeof(PVR_INDEX_ENTRY_S), fdIdx, s32Offset);
        if (readNum != (HI_S32)sizeof(PVR_INDEX_ENTRY_S))
        {
            HI_ERR_PVR("read end_idx failed, endframe:%d, offset:%d.\n",stIdxHeaderInfo.stCycInfo.u32EndFrame, s32Offset);
            PVR_CLOSE(fdIdx);
            return HI_ERR_PVR_FILE_CANT_READ;
        }

        if (stIdxHeaderInfo.stCycInfo.u32EndFrame > stIdxHeaderInfo.stCycInfo.u32StartFrame)
        {
            pAttr->u32FrameNum = stIdxHeaderInfo.stCycInfo.u32EndFrame
                                 - stIdxHeaderInfo.stCycInfo.u32StartFrame;
        }
        else
        {
            pAttr->u32FrameNum = stIdxHeaderInfo.stCycInfo.u32LastFrame
                                 - stIdxHeaderInfo.stCycInfo.u32StartFrame
                                 + stIdxHeaderInfo.stCycInfo.u32EndFrame;
        }
        pAttr->u32StartTimeInMs = startEntry.u32DisplayTimeMs;
        pAttr->u32EndTimeInMs = endEntry.u32DisplayTimeMs;
        if (stIdxHeaderInfo.stCycInfo.u32IsRewind)
        {
            pAttr->u64ValidSizeInByte = stIdxHeaderInfo.u64ValidSize;
        }
        else
        {
            pAttr->u64ValidSizeInByte = endEntry.u64Offset + endEntry.u32FrameSize;
        }
        pAttr->enIdxType = (HI_UNF_PVR_REC_INDEX_TYPE_E)(startEntry.u16IndexType);

        PVR_CLOSE(fdIdx);
    }

    return HI_SUCCESS;
}

HI_S32 PVR_Index_GetFrmNumByEntry(PVR_INDEX_HANDLE pstIndexHandle, PTR_PVR_INDEX_ENTRY pstIndexEntry, HI_S32 *ps32FrmNum)
{
    HI_S32 s32Ret = 0;
    HI_U32 u32StartFrmNum = 0;
    HI_U32 u32EndFrmNum = 0;
    HI_U32 u32LastFrmNum = 0;
    HI_U32 u32MidFrmNum = 0;

    PVR_INDEX_ENTRY_S stStartIndexEntry = {0};
    PVR_INDEX_ENTRY_S stEndIndexEntry = {0};
    PVR_INDEX_ENTRY_S stMidIndexEntry = {0};
    PVR_INDEX_ENTRY_S stZeroIndexEntry = {0};
    PVR_INDEX_ENTRY_S stLastIndexEntry = {0};

    u32StartFrmNum = pstIndexHandle->stCycMgr.u32StartFrame;
    u32EndFrmNum = (pstIndexHandle->stCycMgr.u32EndFrame == -1)?0:pstIndexHandle->stCycMgr.u32EndFrame;
    u32LastFrmNum = (pstIndexHandle->stCycMgr.u32LastFrame == -1)?0:pstIndexHandle->stCycMgr.u32LastFrame;

    if(HI_SUCCESS != PVR_Index_GetFrameByNum(pstIndexHandle, &stStartIndexEntry, u32StartFrmNum))
    {
        HI_ERR_PVR("get start index %d entry fail\n", u32StartFrmNum);
        return HI_FAILURE;
    }

    if(HI_SUCCESS != PVR_Index_GetFrameByNum(pstIndexHandle, &stZeroIndexEntry, 0))
    {
        HI_ERR_PVR("get index 0 entry fail\n", 0);
        return HI_FAILURE;
    }

    s32Ret = PVR_Index_GetFrameByNum(pstIndexHandle, &stLastIndexEntry, u32LastFrmNum);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("get last index %d entry fail. ret %x\n", u32LastFrmNum, s32Ret);
        return HI_FAILURE;
    }

    s32Ret = PVR_Index_GetFrameByNum(pstIndexHandle, &stEndIndexEntry, u32EndFrmNum);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("get the %d entry fail. ret %x\n", u32EndFrmNum, s32Ret);
        return HI_FAILURE;
    }

    if (u32EndFrmNum <= u32StartFrmNum)
    {
        if((pstIndexEntry->u64GlobalOffset >= stStartIndexEntry.u64GlobalOffset) &&
           (pstIndexEntry->u64GlobalOffset <= stLastIndexEntry.u64GlobalOffset))
        {
            u32MidFrmNum = (u32LastFrmNum - u32StartFrmNum)/2;
            u32EndFrmNum = u32LastFrmNum;

            if(HI_SUCCESS != PVR_Index_GetFrameByNum(pstIndexHandle, &stEndIndexEntry, u32EndFrmNum))
            {
                HI_ERR_PVR("get the %d entry fail.\n", u32EndFrmNum);
                return HI_FAILURE;
            }
        }
        else if((pstIndexEntry->u64GlobalOffset <= stEndIndexEntry.u64GlobalOffset) &&
               (pstIndexEntry->u64GlobalOffset >= stZeroIndexEntry.u64GlobalOffset))
        {
            u32MidFrmNum = u32EndFrmNum/2;
            u32StartFrmNum = 0;

            if(HI_SUCCESS != PVR_Index_GetFrameByNum(pstIndexHandle, &stStartIndexEntry, u32StartFrmNum))
            {
                HI_ERR_PVR("get the %d entry fail.\n", u32StartFrmNum);
                return HI_FAILURE;
            }
        }
        else
        {
            HI_ERR_PVR("invalid entry offset=%#llx zero(0)ffset=%#llx start(%d)offset=%#llx end(%d)offset=%#llx last(%d)offset=%#llx.\n",
                pstIndexEntry->u64GlobalOffset,stZeroIndexEntry.u64GlobalOffset,
                u32StartFrmNum, stStartIndexEntry.u64GlobalOffset,
                u32EndFrmNum, stEndIndexEntry.u64GlobalOffset,
                u32LastFrmNum, stLastIndexEntry.u64GlobalOffset);
            return HI_FAILURE;
        }
    }
    else
    {
        u32MidFrmNum = u32EndFrmNum/2;
    }

    if(HI_SUCCESS != PVR_Index_GetFrameByNum(pstIndexHandle, &stMidIndexEntry, u32MidFrmNum))
    {
        HI_ERR_PVR("get the %d entry fail.\n", u32MidFrmNum);
        return HI_FAILURE;
    }

    while((HI_S32)u32StartFrmNum <= (HI_S32)u32EndFrmNum)
    {
        u32MidFrmNum = u32StartFrmNum + (u32EndFrmNum - u32StartFrmNum)/2;

        if(HI_SUCCESS != PVR_Index_GetFrameByNum(pstIndexHandle, &stMidIndexEntry, u32MidFrmNum))
        {
            HI_ERR_PVR("get the %d entry fail.\n", u32MidFrmNum);
            return HI_FAILURE;
        }
        
        if(stMidIndexEntry.u64GlobalOffset > pstIndexEntry->u64GlobalOffset)
        {
            u32EndFrmNum = u32MidFrmNum - 1;
        }
        else if(stMidIndexEntry.u64GlobalOffset < pstIndexEntry->u64GlobalOffset)
        {
            u32StartFrmNum = u32MidFrmNum + 1;
        }
        else
        {
            if (HI_TRUE == PVRIndexIsFrameValid(u32MidFrmNum, &pstIndexHandle->stCycMgr))
            {
                *ps32FrmNum = (HI_S32)u32MidFrmNum;
                return HI_SUCCESS;
            }
            else
            {
                HI_ERR_PVR("find invalid frame number %d(start=%d end=%d) from entry offset %#llx pts %d.\n", 
                    u32MidFrmNum, u32StartFrmNum, u32EndFrmNum, pstIndexEntry->u64GlobalOffset,pstIndexEntry->u32PtsMs);
                return HI_FAILURE;
            }
        }
    }
    HI_ERR_PVR("can not find frame number from entry offset %#llx pts %d start=%d end=%d mid=%d. \n", 
               pstIndexEntry->u64GlobalOffset,pstIndexEntry->u32PtsMs, u32StartFrmNum, u32EndFrmNum, u32MidFrmNum);
    return HI_FAILURE;
}


/*get vedio type from index header info   */
HI_S32 PVR_Index_GetVtype(PVR_INDEX_HANDLE handle)
{
    PVR_IDX_HEADER_INFO_S stIdxHeaderInfo;

    memset(&stIdxHeaderInfo, 0, sizeof(PVR_IDX_HEADER_INFO_S));

    /* means not found the header info in this index file */
    if (HI_SUCCESS != PVRIndexGetHeaderInfo(handle->s32HeaderFd, &stIdxHeaderInfo))
    {
        return HI_FAILURE;
    }
    else
        return (stIdxHeaderInfo.u32Reserved & 0xFFFF);
}

/*reserved function for smooth play */
HI_S32 PVR_Index_GetMaxBitrate(PVR_INDEX_HANDLE piIndexHandle)
{
    return 0x100;
}

/*get stream bit rate  */
HI_S32 PVR_Index_GetStreamBitRate(PVR_INDEX_HANDLE piIndexHandle,
                                  HI_U32 *pBitRate,
                                  HI_U32 u32StartFrameNum, 
                                  HI_U32 u32EndFrameNum)
{
    PVR_INDEX_ENTRY_S  stTmpEntry ={0}; 
    HI_U32 i = 0, u32StartTime = 0, u32EndTime = 0;
    HI_U64 u64TotalBytes = 0;

    if (HI_TRUE != PVRIndexIsFrameValid(u32StartFrameNum, &piIndexHandle->stCycMgr))
    {
        HI_ERR_PVR("input start frame number is invalid.\n");
        return HI_FAILURE;
    }

    if (HI_TRUE != PVRIndexIsFrameValid(u32EndFrameNum, &piIndexHandle->stCycMgr))
    {
        HI_ERR_PVR("input end frame number is invalid.\n");
        return HI_FAILURE;
    }

    if(HI_SUCCESS != PVR_Index_GetFrameByNum(piIndexHandle, &stTmpEntry, u32StartFrameNum))
    {
         HI_INFO_PVR("get the %d entry fail.\n", i);
         return HI_FAILURE;
    }
    u32StartTime = stTmpEntry.u32DisplayTimeMs;

    if(HI_SUCCESS != PVR_Index_GetFrameByNum(piIndexHandle, &stTmpEntry, u32EndFrameNum))
    {
         HI_INFO_PVR("get the %d entry fail.\n", i);
         return HI_FAILURE;
    }
    u32EndTime = stTmpEntry.u32DisplayTimeMs;

    if((u32StartTime == u32EndTime) || (u32StartTime >= u32EndTime))
    {
        HI_INFO_PVR("invalid pts, can not get bitrate.\n");
        return HI_FAILURE;
    }

    /* TODO: use global offset to calc total bytes */
    if (u32EndFrameNum < u32StartFrameNum)
    {
        for (i = u32StartFrameNum; i < piIndexHandle->stCycMgr.u32LastFrame; i++)
        {
            if(HI_SUCCESS != PVR_Index_GetFrameByNum(piIndexHandle, &stTmpEntry, i))
            {
                 HI_INFO_PVR("get the %d entry fail.\n", i);
                 return HI_FAILURE;
            }
            
            u64TotalBytes += stTmpEntry.u32FrameSize;
        }

        for (i = 0; i < u32EndFrameNum; i++)
        {
            if(HI_SUCCESS != PVR_Index_GetFrameByNum(piIndexHandle, &stTmpEntry, i))
            {
                 HI_INFO_PVR("get the %d entry fail.\n", i);
                 return HI_FAILURE;
            }
            
            u64TotalBytes += stTmpEntry.u32FrameSize;
        }
    }
    else
    {
        for (i = u32StartFrameNum; i < u32EndFrameNum; i++)
        {
            if(HI_SUCCESS != PVR_Index_GetFrameByNum(piIndexHandle, &stTmpEntry, i))
            {
                 HI_INFO_PVR("get the %d entry fail.\n", i);
                 return HI_FAILURE;
            }
            
            u64TotalBytes += stTmpEntry.u32FrameSize;
        }
    }

    *pBitRate = (u64TotalBytes*8)/((u32EndTime - u32StartTime)/1000);

    return HI_SUCCESS;
}

HI_S32 PVR_Index_GetFrameRate(PVR_INDEX_HANDLE piIndexHandle, HI_U32 *pFrameRate)
{
    PVR_INDEX_ENTRY_S  frame_tmp ={0}; 
    HI_S32 s32Ret = 0;
    HI_U32 u32StartTime = 0, u32EndTime = 0;
    HI_U32 u32TotalFrames = 0;
    HI_U32 u32StartFrmNum = 0;
    HI_U32 u32EndFrmNum = 0;
    HI_U32 u32LastFrmNum = 0;
    HI_U32 u32TotalTimeMs = 0;

    HI_ASSERT_RET(piIndexHandle != NULL);

    PVR_INDEX_LOCK(&piIndexHandle->stMutex);
    u32StartFrmNum = piIndexHandle->stCycMgr.u32StartFrame;
    u32EndFrmNum = (piIndexHandle->stCycMgr.u32EndFrame == -1)?0:piIndexHandle->stCycMgr.u32EndFrame;
    u32LastFrmNum = (piIndexHandle->stCycMgr.u32LastFrame == -1)?0:piIndexHandle->stCycMgr.u32LastFrame;

    if (u32LastFrmNum == 0)
    {
        PVR_INDEX_UNLOCK(&piIndexHandle->stMutex);
        HI_INFO_PVR("There is no rec index\n");
        return HI_FAILURE;
    }

    if(HI_SUCCESS != PVRIndexGetEntryByNum(piIndexHandle, &frame_tmp, u32StartFrmNum))
    {
         HI_INFO_PVR("get the %d entry fail.\n", piIndexHandle->stCycMgr.u32StartFrame);
         PVR_INDEX_UNLOCK(&piIndexHandle->stMutex);
         return HI_FAILURE;
    }
    u32StartTime = frame_tmp.u32DisplayTimeMs;

    s32Ret = PVRIndexGetEntryByNum(piIndexHandle, &frame_tmp, u32EndFrmNum);
    if(HI_SUCCESS != s32Ret)
    {
         if (HI_ERR_PVR_FILE_TILL_END == s32Ret)
         {
            s32Ret = PVRIndexGetEntryByNum(piIndexHandle, &frame_tmp, PVR_IDX_PREV_POS_IN_CYC(u32EndFrmNum, (u32LastFrmNum + 1)));
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_PVR("Get pre endframe %d fail, ret %x\n", 
                            PVR_IDX_PREV_POS_IN_CYC(u32EndFrmNum, (u32LastFrmNum + 1)), s32Ret);
                PVR_INDEX_UNLOCK(&piIndexHandle->stMutex);
                return HI_FAILURE;
            }

            u32EndFrmNum = PVR_IDX_PREV_POS_IN_CYC(u32EndFrmNum, (u32LastFrmNum + 1));
         }
         else
         {
            HI_ERR_PVR("Get endframe %d fail, ret %x\n", u32EndFrmNum, s32Ret);
            PVR_INDEX_UNLOCK(&piIndexHandle->stMutex);
            return HI_FAILURE;
         }
    }

    u32EndTime = frame_tmp.u32DisplayTimeMs;
    if (u32EndTime <= u32StartTime)
    {
        HI_ERR_PVR("StartTime:%d > EndTime:%d, error, S:%d,E:%d,L:%d\n", 
                   u32StartTime, u32EndTime, u32StartFrmNum, u32EndFrmNum, u32LastFrmNum);
        PVR_INDEX_UNLOCK(&piIndexHandle->stMutex);
        return HI_FAILURE;
    }

    if (piIndexHandle->stCycMgr.u32EndFrame <= piIndexHandle->stCycMgr.u32StartFrame)
    {
        u32TotalFrames = (u32LastFrmNum - u32StartFrmNum) + u32EndFrmNum + 1;
    }
    else
    {
        u32TotalFrames = u32LastFrmNum + 1;  
    }

    u32TotalTimeMs = ((u32EndTime - u32StartTime) < 1000) ? 1000 : (u32EndTime - u32StartTime);
   PVR_INDEX_UNLOCK(&piIndexHandle->stMutex);
   
   *pFrameRate =  u32TotalFrames * 10/(u32TotalTimeMs/1000);
    
    if((*pFrameRate)%10 >= 5)
    {
        *pFrameRate = *pFrameRate/10 + 1;
    }
    else
    {
        *pFrameRate = *pFrameRate/10 ;
    }
    
    return HI_SUCCESS;
}

/* get pre I/P/B frame number
   0 == u32Direction BACKWARD
   1 == u32Direction FORWARD*/
HI_S32 PVR_Index_GetFBwardIPBFrameNum(PVR_INDEX_HANDLE handle, HI_U32 u32Direction, HI_U32 u32FrameType, HI_U32 u32CurFrameNum, HI_U32 *pu32NextFrameNum)
{
    return PVRIndexGetFBwardIPBFrameNum(handle,&handle->stCycMgr,u32Direction, u32FrameType, u32CurFrameNum, pu32NextFrameNum);
}


HI_S32 PVR_Index_PushStartWhenTsLead(PVR_INDEX_HANDLE handle, HI_U64 u64CurFileSize)
{
    HI_U32 u32CurFrm = 0, u32NextFrm = 0;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U64 u64TsLeadLen = 0, u64InvalideLen = 0;
    PVR_CYC_MGR_S *pstCycMgr = HI_NULL;
    PVR_INDEX_ENTRY_S stStartEntry = {0};
    PVR_INDEX_ENTRY_S stLastEntry = {0};
    PVR_INDEX_ENTRY_S stNextEntry = {0};

    if (handle == HI_NULL)
    {
        HI_ERR_PVR("Invalide param\n");
        return HI_FAILURE;
    }

    pstCycMgr = &handle->stCycMgr;
    u32CurFrm = pstCycMgr->u32StartFrame;
    u32NextFrm = pstCycMgr->u32StartFrame;

    if (handle->stCycMgr.bIsRewind == HI_FALSE)
        return HI_SUCCESS;

    if (u64CurFileSize <= handle->stCurRecFrame.u64GlobalOffset)
        return HI_SUCCESS;

    u64TsLeadLen = u64CurFileSize - handle->stCurRecFrame.u64GlobalOffset;

    PVR_INDEX_LOCK(&handle->stMutex);

    if (pstCycMgr->u32CycTimes < 1)
    {
        PVR_INDEX_UNLOCK(&handle->stMutex);
        return HI_SUCCESS;
    }

    if (pstCycMgr->u32StartFrame > pstCycMgr->u32EndFrame)
    {
        u64InvalideLen = pstCycMgr->u64StartFrameOffset - 
                        (handle->stCurRecFrame.u64Offset + handle->stCurRecFrame.u32FrameSize);
    }
    else
    {
        s32Ret = PVRIndexGetEntryByNum(handle, &stLastEntry, pstCycMgr->u32LastFrame);
        if (s32Ret == HI_SUCCESS)
        {
            u64InvalideLen = (stLastEntry.u64Offset + stLastEntry.u32FrameSize - 
                              handle->stCurRecFrame.u64Offset - handle->stCurRecFrame.u32FrameSize) 
                              + pstCycMgr->u64StartFrameOffset;
        }
        else
        {
            u64InvalideLen = pstCycMgr->u64StartFrameOffset;
        }
    }

    if (u64InvalideLen >= u64TsLeadLen)
    {
        PVR_INDEX_UNLOCK(&handle->stMutex);
        return HI_SUCCESS;
    }

    s32Ret = PVRIndexGetEntryByNum(handle, &stStartEntry, u32CurFrm);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PVR("Get start frame %d failed, ret %x\n", u32CurFrm, s32Ret);
        PVR_INDEX_UNLOCK(&handle->stMutex);
        return s32Ret;
    }

    do
    {
        u32CurFrm = u32NextFrm;
        s32Ret = PVRIndexGetFBwardIPBFrameNum(handle, pstCycMgr, 1, PVR_INDEX_FRAME_I,
                                              u32CurFrm, &u32NextFrm);
        if (s32Ret == HI_SUCCESS)
        {
            s32Ret = PVRIndexGetEntryByNum(handle, &stNextEntry, u32NextFrm);
            if (s32Ret == HI_SUCCESS)
            {
                if (stNextEntry.u64GlobalOffset <= stStartEntry.u64GlobalOffset)
                {
                    HI_FATAL_PVR("Next %d goffset %llx small than start %d goffset %llx\n",
                                 u32NextFrm, stNextEntry.u64GlobalOffset, 
                                 pstCycMgr->u32StartFrame, stStartEntry.u64GlobalOffset);
                    PVR_INDEX_UNLOCK(&handle->stMutex);
                    return HI_FAILURE;
                }
            }
            else
            {
                HI_ERR_PVR("Get %d frame failed, ret %x\n", u32NextFrm, s32Ret);
                PVR_INDEX_UNLOCK(&handle->stMutex);
                return s32Ret;
            }
        }
        else
        {
            HI_ERR_PVR("Get %d next I frame failed, ret %x!\n", u32CurFrm, s32Ret);
            PVR_INDEX_UNLOCK(&handle->stMutex);
            return s32Ret;
        }
    }while((u64InvalideLen + stNextEntry.u64GlobalOffset - stStartEntry.u64GlobalOffset) < u64TsLeadLen);

    HI_INFO_PVR("Push start %u to %u, InvalideLen %llx pushlen %llx tsleadlen %llx\n",
                pstCycMgr->u32StartFrame, u32NextFrm, u64InvalideLen,
                stNextEntry.u64GlobalOffset - stStartEntry.u64GlobalOffset, u64TsLeadLen);
    pstCycMgr->u32StartFrame = u32NextFrm;
    pstCycMgr->u64StartFrameOffset = stNextEntry.u64Offset;

    (HI_VOID)PVRIndexCheckReadFrmValidWhenTimeshift(handle);
    PVR_INDEX_UNLOCK(&handle->stMutex);

    return HI_SUCCESS;
}

HI_VOID PVR_Index_ProcOverFlow(PVR_INDEX_HANDLE handle)
{
    handle->u64OverflowOffset = handle->stCurRecFrame.u64GlobalOffset + handle->stCurRecFrame.u32FrameSize;
}


/*
����  Forward ���� BackWard ���򣬴ӵ�ǰ֡�� ���ƶ� Distance ֮��õ���֡�ţ�
ע��: �����ƶ�λ�ô��� u32LastFrame ���� u32EndFrame�� ����� u32LastFrame ���� u32EndFrame��
�����ƶ�С�� StartFrame ������� StartFrame��
*/
HI_S32 PVR_Index_CycMoveFrmNum(PVR_INDEX_HANDLE handle, HI_BOOL bForward,HI_S32 s32CurFrmNum,HI_U32 Distance, HI_S32 *ps32NextFrameNum)
{
    HI_S32  s32Range = 0;
    HI_S32  s32NextFrameNum = 0;
    HI_BOOL bRewind = HI_FALSE;
    PVR_CYC_MGR_S* pstCycMgr = HI_NULL;

    HI_ASSERT_RET(handle != NULL);
    HI_ASSERT_RET(ps32NextFrameNum != NULL);

    pstCycMgr = &handle->stCycMgr;
    s32Range  = (bForward)?Distance:(0 - (HI_S32)Distance);
    bRewind   = (pstCycMgr->u32StartFrame > pstCycMgr->u32EndFrame)?HI_TRUE:HI_FALSE;

    if (HI_TRUE != PVRIndexIsFrameValid((HI_U32)s32CurFrmNum, pstCycMgr))
    {
        HI_ERR_PVR("current frame number %d is invalid. start=%d end=%d\n",
                    s32CurFrmNum, handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame);
        return PVR_INDEX_ERR_INVALID;
    }

    /*ͨ��ֻ����һ��GOP��Χ�ƶ�֡�ţ����ô˺�����ʱ����� �ƶ���Χ̫�󣬿������쳣����˱�����ֻ֧�� 512 ��Χ���ƶ�*/
    if (Distance > 512)
    {
        HI_ERR_PVR("move range > 512, This function not support,D:%d,R:%d\n", Distance, s32Range);
    }
    
    /*ͨ������ֵ�͵��������룬����� if-else �����ڴ����쳣*/
    s32NextFrameNum = s32CurFrmNum + s32Range;

    if (bRewind)
    {
        if (bForward)   //FF ����
        {
            //1.  0---c---e---n---s---l     ��ǰ֡��ǰ�β��ҿ����β��
            if ((s32CurFrmNum <= pstCycMgr->u32EndFrame) && 
                (s32NextFrameNum > pstCycMgr->u32EndFrame))
            {
                s32NextFrameNum = pstCycMgr->u32EndFrame;
                *ps32NextFrameNum = s32NextFrameNum;
                return HI_ERR_PVR_FILE_TILL_END;
            }
            //1.  0---n---e---s---c---l     ��ǰ֡�ں������һ֡�����ҿ��δ��β��
            //2.  0---e---n---s---c---l     ��ǰ֡�ں������һ֡�����ҿ����β��
            else if ((s32CurFrmNum >= pstCycMgr->u32StartFrame) && 
                     (s32NextFrameNum > pstCycMgr->u32LastFrame))
            {
                
                s32NextFrameNum = s32NextFrameNum - pstCycMgr->u32LastFrame - 1;
                if (s32NextFrameNum > pstCycMgr->u32EndFrame)
                {
                    s32NextFrameNum = pstCycMgr->u32EndFrame;
                    *ps32NextFrameNum = s32NextFrameNum;
                    return HI_ERR_PVR_FILE_TILL_END;
                }
            }
        }
        else    //FB ����
        {
            //1.  0---c---e---s---n---l     ��ǰ֡��ǰ������һ֡�����ҿ���δ��β��
            //2.  0---c---e---n---s---l     ��ǰ֡��ǰ������һ֡�����ҿ��˵�β��
            if ((s32CurFrmNum <= pstCycMgr->u32EndFrame) && 
                (s32NextFrameNum < 0))
            {
                s32NextFrameNum = s32NextFrameNum + pstCycMgr->u32LastFrame + 1;
                if (s32NextFrameNum < (HI_S32)pstCycMgr->u32StartFrame)
                {
                    s32NextFrameNum = pstCycMgr->u32StartFrame;
                    *ps32NextFrameNum = s32NextFrameNum;
                    return HI_ERR_PVR_FILE_TILL_START;
                }
            }
            //1.  0---e---n---s---c---l     ��ǰ֡�ں���ҿ��˵�β��
            else if ((s32CurFrmNum >= pstCycMgr->u32StartFrame) && 
                     (s32NextFrameNum < (HI_S32)pstCycMgr->u32StartFrame))
            {
                s32NextFrameNum = pstCycMgr->u32StartFrame;
                *ps32NextFrameNum = s32NextFrameNum;
                return HI_ERR_PVR_FILE_TILL_START;
            }
        }
    }
    else
    {
        //1.  0---s---c---e---n---l     �����β��
        //2.  0---s---c---n---e---l     ���δ��β��
        if (bForward)   //FF�ǻ���
        {
            if (s32NextFrameNum > (HI_S32)pstCycMgr->u32EndFrame)
            {
                s32NextFrameNum = pstCycMgr->u32EndFrame;
                *ps32NextFrameNum = s32NextFrameNum;
                return HI_ERR_PVR_FILE_TILL_END;
            }
        }
        //1.  0---s---n---c---e---l     ����δ��ͷ��
        //2.  0---n---s---c---e---l     ���˵�ͷ��
        else    //FB�ǻ���
        {
            if (s32NextFrameNum < (HI_S32)pstCycMgr->u32StartFrame)
            {
                s32NextFrameNum = pstCycMgr->u32StartFrame;
                *ps32NextFrameNum = s32NextFrameNum;
                return HI_ERR_PVR_FILE_TILL_START;
            }
        }
    }

    if (s32NextFrameNum < 0)
    {
        HI_ERR_PVR("Move Frm error, F:%d,c:%d,D:%d,N:%d,S:%d,L:%d,E:%d\n",
                    bForward, s32CurFrmNum, Distance, s32NextFrameNum,
                    pstCycMgr->u32StartFrame, pstCycMgr->u32LastFrame, pstCycMgr->u32EndFrame);
        return PVR_INDEX_ERR_INVALID;
    }

    *ps32NextFrameNum = s32NextFrameNum;

    HI_INFO_PVR("Move , F:%d,c:%d,D:%d,N:%d,S:%d,L:%d,E:%d\n",
                bForward, s32CurFrmNum, Distance, s32NextFrameNum,
                pstCycMgr->u32StartFrame, pstCycMgr->u32LastFrame, pstCycMgr->u32EndFrame);

    return HI_SUCCESS;
}

HI_S32 PVR_Index_GetPreIFrame(PVR_INDEX_HANDLE handle, HI_U32 u32CurFrameNum, HI_U32 *PreIFrameNum, PVR_INDEX_ENTRY_S *PreIFrame)
{
    PVR_INDEX_ENTRY_S stIndexEntry = {0};
    HI_U32 u32PreFrmNum = 0;
    HI_U32 u32PreIOffset = 0;
    HI_S32 ret = 0;

    HI_ASSERT_RET(handle != NULL);
    HI_ASSERT_RET(PreIFrameNum != NULL);

    if (HI_TRUE != PVRIndexIsFrameValid(u32CurFrameNum, &handle->stCycMgr))
    {
        HI_WARN_PVR("current frame number %d is invalid. start=%d end=%d\n",
                    u32CurFrameNum, handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame);
        return PVR_INDEX_ERR_INVALID;
    }

    ret = PVR_Index_CycMoveFrmNum(handle, HI_FALSE, (HI_S32)u32CurFrameNum, 1, (HI_S32 *)&u32PreFrmNum);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    ret = PVR_Index_GetFrameByNum(handle, &stIndexEntry, u32PreFrmNum);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    u32PreIOffset = PVR_INDEX_get_preIoffset(&stIndexEntry);
    ret = PVR_Index_CycMoveFrmNum(handle, HI_FALSE, (HI_S32)u32PreFrmNum, u32PreIOffset, (HI_S32*)PreIFrameNum);
    if ((ret == PVR_INDEX_ERR_INVALID) || (HI_ERR_PVR_FILE_TILL_START == ret))
    {
        HI_WARN_PVR("search pre I frame till start ,can not get\n");
        return ret;
    }

    /*check it is I*/
    (HI_VOID)PVR_Index_GetFrameByNum(handle, &stIndexEntry, *PreIFrameNum);
    if (!PVR_INDEX_is_Iframe(&stIndexEntry))
    {
        HI_WARN_PVR(" c:%d, PI:%d, but not I\n", u32CurFrameNum, *PreIFrameNum);
        return HI_FAILURE;
    }

    memcpy(PreIFrame, &stIndexEntry, sizeof(PVR_INDEX_ENTRY_S));

    HI_INFO_PVR("GetPI: C:%d,PI:%d\n",u32CurFrameNum,*PreIFrameNum);

    return ret;
}

HI_S32 PVR_Index_GetNextIFrame(PVR_INDEX_HANDLE handle, HI_U32 u32CurFrameNum, HI_U32 *pu32NextIFrameNum,PVR_INDEX_ENTRY_S* pstNextIFrame)
{
    HI_U32 u32Step = 0;
    HI_U32 u32Count = 0;
    HI_U32 u32PreIOffset = 0;
    HI_U32 u32PreIFrameNum = 0;
    HI_S32 s32NextIFrameNum = 0;
    HI_S32 ret=0;
    HI_S32 s32TmpStartFrm = 0;/*ÿһ����Ѱ֡�Ŀ�ʼ֡��*/
    HI_S32 s32TmpEndFrameNum = 0;/*ÿһ����Ѱ֡�Ľ��֡��*/
    PVR_INDEX_ENTRY_S stIndexEntry = {0};
    PVR_INDEX_ENTRY_S stPreIFrame = {0};
    PVR_INDEX_INFO_S  *pstIdxInfo = &handle->stRecIdxInfo.stIdxInfo;

    HI_ASSERT_RET(handle != NULL);
    HI_ASSERT_RET(pu32NextIFrameNum != NULL);

    if (HI_TRUE != PVRIndexIsFrameValid(u32CurFrameNum, &handle->stCycMgr))
    {
        HI_WARN_PVR("current frame number %d is invalid. start=%d end=%d\n",
                     u32CurFrameNum, handle->stCycMgr.u32StartFrame, handle->stCycMgr.u32EndFrame);
        return PVR_INDEX_ERR_INVALID;
    }

    (HI_VOID)PVR_Index_GetFrameByNum(handle, &stIndexEntry, u32CurFrameNum);
    if (PVR_INDEX_is_Iframe(&stIndexEntry))
    {
        ret = PVR_Index_GetFBwardIPBFrameNum(handle, 1, PVR_INDEX_FRAME_I, u32CurFrameNum, pu32NextIFrameNum);
        if (HI_SUCCESS == ret)
        {
            ret  = PVR_Index_GetFrameByNum(handle, &stIndexEntry, *pu32NextIFrameNum);
            if (HI_SUCCESS == ret)
            {
                memcpy(pstNextIFrame, &stIndexEntry, sizeof(PVR_INDEX_ENTRY_S));
                HI_INFO_PVR("GetNextI finish: Cur:%d,NextI:%d,ret:0x%x\n",
                             u32CurFrameNum, *pu32NextIFrameNum, ret);
                return HI_SUCCESS;
            }
            HI_ERR_PVR("Get frame by num failed! ret %x\n", ret);
        }
        return ret;
    }

    ret = PVR_Index_GetPreIFrame(handle, u32CurFrameNum, &u32PreIFrameNum, &stPreIFrame);
    if (HI_SUCCESS != ret)
    {
        ret = PVR_Index_GetFBwardIPBFrameNum(handle, 1, PVR_INDEX_FRAME_I,  u32CurFrameNum, pu32NextIFrameNum);
        if (HI_SUCCESS == ret)
        {
            ret = PVR_Index_GetFrameByNum(handle, &stIndexEntry, *pu32NextIFrameNum);
            if (HI_SUCCESS == ret)
            {
                memcpy(pstNextIFrame,&stIndexEntry,sizeof(PVR_INDEX_ENTRY_S));
                HI_INFO_PVR("GetNextI finish: Cur:%d,NextI:%d,ret:0x%x\n", u32CurFrameNum, *pu32NextIFrameNum, ret);
                return HI_SUCCESS;
            }
            HI_ERR_PVR("Get frame by num failed! ret %x\n", ret);
        }
        return ret;
    }

    /*1. ���㲽��ֵ*/
    if (((HI_S32)pstIdxInfo->u32GopTotalNum > 0) && ((HI_S32)pstIdxInfo->u32FrameTotalNum > 0))
    {
        u32Step = pstIdxInfo->u32FrameTotalNum / pstIdxInfo->u32GopTotalNum;
    }
    else
    {
        HI_WARN_PVR("Recorded Gop Num:%d, Frm Num:%d may be error\n",
                     pstIdxInfo->u32GopTotalNum, pstIdxInfo->u32FrameTotalNum);
        u32Step = 50;
    }

    /*2. �ҵ�ĳһ�� TmpFrameNum �� �� u32CurFrameNum ����ĳһ��GOP�е�һ֡��
    ��� do-while ͨ��ѭ��һ���μȿ��ҵ�����һ��֡�������Ȼ�����Եø��ӣ����� ���ļ����٣�IO��������*/ 
    s32TmpStartFrm = u32CurFrameNum;
    do
    {
        u32Count++;
        ret = PVR_Index_CycMoveFrmNum(handle, HI_TRUE, s32TmpStartFrm, u32Step, &s32TmpEndFrameNum); 
        ret |= PVR_Index_GetFrameByNum(handle, &stIndexEntry, s32TmpEndFrameNum);
        u32PreIOffset = PVR_INDEX_get_preIoffset(&stIndexEntry);
        ret |= PVR_Index_CycMoveFrmNum(handle, HI_FALSE, s32TmpEndFrameNum, u32PreIOffset, &s32NextIFrameNum); 

        HI_INFO_PVR("Serach a Next GopFrm: S:%d,E:%d,Step:%d,NextI:%d,ret:0x%x\n",
                     s32TmpStartFrm, s32TmpEndFrameNum, u32Step, s32NextIFrameNum, ret);

        s32TmpStartFrm = s32TmpEndFrameNum;
        if ((PVR_INDEX_ERR_INVALID == ret) || (HI_ERR_PVR_FILE_TILL_END == ret))
        {
            HI_WARN_PVR("serach next I frame till end ,can not get,error\n");
            return HI_FAILURE;
        }
        if (u32Count > 256)
        {
            HI_ERR_PVR("search frame of next gop more than 256 times, something must wrong!Cur:%d", u32CurFrameNum);
            u32Count = 0;
            break;
        }
        if (u32PreIOffset == 0)
        {
            u32Count = 0;
            break;
        }
    } while (u32PreIFrameNum == (HI_U32)s32NextIFrameNum);

    /*3. ����������� do-while �ҵ��� TmpFrameNum ��������� :
    ........u32CurFrameNum......I.......I.........I....       ........TmpFrameNum....I��
    ��Ҫ��������Ѱ��һ�� �� u32CurFrameNum ���ڵ� GOP ��I֡*/
    s32TmpStartFrm = s32TmpEndFrameNum;
    u32Count = 0;

    while (u32PreIFrameNum != (HI_U32)s32NextIFrameNum)
    {
        u32Count++;
        s32TmpEndFrameNum = s32NextIFrameNum;
        ret = PVR_Index_GetPreIFrame(handle, s32TmpStartFrm, (HI_U32*)&s32NextIFrameNum, &stIndexEntry); 
        ret |= PVR_Index_CycMoveFrmNum(handle, HI_FALSE, s32NextIFrameNum, 1, &s32TmpStartFrm); 
        if (HI_SUCCESS != ret)
        {
            u32Count = 0;
            break;
        }
        if (u32Count > 256)
        {
            HI_ERR_PVR("search next I frame more than 256 times, something must wrong!Cur:%d",u32CurFrameNum);
            u32Count = 0;
            break;
        }
        
    }

    s32NextIFrameNum = s32TmpEndFrameNum;

    /*4. check it is I*/
    (HI_VOID)PVR_Index_GetFrameByNum(handle, &stIndexEntry, (HI_U32)s32NextIFrameNum);
    if (PVR_INDEX_is_Iframe(&stIndexEntry))
    {
        *pu32NextIFrameNum = s32NextIFrameNum;
         memcpy(pstNextIFrame, &stIndexEntry, sizeof(PVR_INDEX_ENTRY_S));
    }
    else
    {
        HI_WARN_PVR("Get Next I Frame failed, Cur:%d\n", u32CurFrameNum);
        return HI_FAILURE;
    }

    HI_INFO_PVR("GetNextI finish: Cur:%d,NextI:%d,ret:0x%x\n", u32CurFrameNum, *pu32NextIFrameNum, ret);
    return HI_SUCCESS;
}

/* get frame number, frame attribute, GOP attribute from one frame plus N forward*/
HI_S32 PVR_Index_GetForwardGOPAttr(PVR_INDEX_HANDLE piIndexHandle, 
                                   HI_PVR_FETCH_RESULT_S *pstFetchRes, 
                                   HI_U32 u32StartFrameNum, 
                                   HI_U32 u32FrameNum)
{
    HI_U32 i = 0, u32ReadFrameEnd = 0, u32GopFlag = 0, u32FrmNum = 0;
    HI_S32 ret = 0;
    PVR_INDEX_ENTRY_S *pstFrame = HI_NULL; 

    HI_ASSERT_RET(NULL != piIndexHandle);
    HI_ASSERT_RET(NULL != pstFetchRes);

    if (HI_TRUE != PVRIndexIsFrameValid(u32StartFrameNum, &piIndexHandle->stCycMgr))
    {
        HI_ERR_PVR("Input frame number %d is invalid. S/E/L %d/%d/%d\n", 
                    u32StartFrameNum, 
                    piIndexHandle->stCycMgr.u32StartFrame,
                    piIndexHandle->stCycMgr.u32EndFrame,
                    piIndexHandle->stCycMgr.u32LastFrame);
        return HI_FAILURE;
    }

    memset(pstFetchRes, 0, sizeof(HI_PVR_FETCH_RESULT_S));
    u32ReadFrameEnd = u32StartFrameNum + u32FrameNum;

    for (i = u32StartFrameNum; i < u32ReadFrameEnd; i++)
    { 
        pstFrame = &pstFetchRes->stFrame[u32FrmNum].stIndexEntry;
        if (i > piIndexHandle->stCycMgr.u32LastFrame)
        {
            if (piIndexHandle->stCycMgr.u32EndFrame <= piIndexHandle->stCycMgr.u32StartFrame)
            {
                i = 0;
                u32ReadFrameEnd = u32FrameNum - (piIndexHandle->stCycMgr.u32LastFrame - u32StartFrameNum + 1) - 1;
                u32ReadFrameEnd = (u32ReadFrameEnd >= piIndexHandle->stCycMgr.u32EndFrame) ? piIndexHandle->stCycMgr.u32EndFrame : u32ReadFrameEnd;
            }
            else
                break;
        }
        
        if (HI_TRUE != PVRIndexIsFrameValid(i, &piIndexHandle->stCycMgr))
        {
            return HI_SUCCESS;
        }

        ret = PVR_Index_GetFrameByNum(piIndexHandle, pstFrame, i);
        if(HI_SUCCESS != ret)
        {
             if(ret == HI_ERR_PVR_FILE_TILL_END)
             {
                return HI_SUCCESS;
             }
             else
             {
                HI_WARN_PVR("get the %d entry fail.\n", i);
                return HI_FAILURE;
             }
        }

        pstFetchRes->stFrame[u32FrmNum].u32FrameNum = i;
        pstFetchRes->stFrame[u32FrmNum].u32FrameType = PVR_INDEX_get_frameType(pstFrame);

        u32FrmNum++;
        pstFetchRes->u32TotalFrameNum = u32FrmNum;

        if (PVR_INDEX_is_Iframe(pstFrame))
        {
            u32GopFlag = 1;
            pstFetchRes->u32IFrameNum++;
            pstFetchRes->u32GopNum++;
        }
        else if (PVR_INDEX_is_Bframe(pstFrame))
        {
            pstFetchRes->u32BFrameNum++;
        }
        else if (PVR_INDEX_is_Pframe(pstFrame))
        {
            pstFetchRes->u32PFrameNum++;
        }
    }

    return HI_SUCCESS;
}

/* get frame number, frame attribute, GOP attribute from one frame plus N backward*/
HI_S32 PVR_Index_GetBackwardGOPAttr(PVR_INDEX_HANDLE piIndexHandle, 
                                    HI_PVR_FETCH_RESULT_S *pstFetchRes, 
                                    HI_U32 u32StartFrameNum, 
                                    HI_U32 u32FrameCount)
{
    HI_U32 i, u32GopFlag = 0, u32FrmCount = 0, u32FrmNum = u32StartFrameNum;
    HI_S32 ret = HI_SUCCESS;
    PVR_INDEX_ENTRY_S       *pstEntry = HI_NULL;
    PVR_CYC_MGR_S           *pstCycMgr = HI_NULL;
    HI_PVR_FETCH_GOP_ATTR_S *pstFetchGopAttr = HI_NULL;
    HI_PVR_FETCH_FRAME_S    *pGopReverseFrm, *pTmpFetchFrame = HI_NULL;

    HI_ASSERT_RET(NULL != piIndexHandle);
    HI_ASSERT_RET(NULL != pstFetchRes);
    pstCycMgr = &(piIndexHandle->stCycMgr);

    if (HI_TRUE != PVRIndexIsFrameValid(u32StartFrameNum, pstCycMgr))
    {
        HI_ERR_PVR("Input frame number %d is invalid. S/E/L %d/%d/%d\n", 
                    u32StartFrameNum, 
                    piIndexHandle->stCycMgr.u32StartFrame,
                    piIndexHandle->stCycMgr.u32EndFrame,
                    piIndexHandle->stCycMgr.u32LastFrame);
        return HI_FAILURE;
    }

    pGopReverseFrm = (HI_PVR_FETCH_FRAME_S *)HI_MALLOC(HI_ID_PVR, sizeof(HI_PVR_FETCH_FRAME_S) * MAX_FRAME_NUM_ONCE_FETCH);
    HI_ASSERT_RET(NULL != pGopReverseFrm);

    memset(pGopReverseFrm, 0, sizeof(HI_PVR_FETCH_FRAME_S) * MAX_FRAME_NUM_ONCE_FETCH);
    memset(pstFetchRes, 0, sizeof(HI_PVR_FETCH_RESULT_S));
    pTmpFetchFrame = pGopReverseFrm;
    pstFetchGopAttr = &(pstFetchRes->stGop[0]);

    for (i = u32FrameCount; i > 0; i--)
    {
        pstEntry = &(pTmpFetchFrame->stIndexEntry);

        if (HI_TRUE != PVRIndexIsFrameValid(u32FrmNum, pstCycMgr))
        {
            ret = HI_FAILURE;
            HI_ERR_PVR("Readframe %d is invalide\n", u32FrmNum);
            break;
        }

        ret = PVRIndexGetEntryByNum(piIndexHandle, pstEntry, u32FrmNum);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_PVR("Get the %d entry fail! ret %x\n", u32FrmNum, ret);
            break;
        }

        pTmpFetchFrame->u32FrameNum = u32FrmNum;
        pTmpFetchFrame->u32FrameType = PVR_INDEX_get_frameType(pstEntry);

        u32FrmCount++;
        pstFetchGopAttr->u32TotalFrameNum = u32FrmCount;   //add frm num of this GOP
        pstFetchRes->u32TotalFrameNum++;                   //add frm num of fetch result

        if (PVR_INDEX_is_Iframe(pstEntry))
        {
            u32GopFlag = 1;
            pstFetchRes->u32IFrameNum++;
        }
        else if (PVR_INDEX_is_Bframe(pstEntry))
        {
            pstFetchRes->u32BFrameNum++;
            pstFetchGopAttr->u32BFrameNum++;
        }
        else if (PVR_INDEX_is_Pframe(pstEntry))
        {
            pstFetchRes->u32PFrameNum++;
            pstFetchGopAttr->u32PFrameNum++;
        }

        if (1 == u32GopFlag)
        {
            HI_S32 j = (HI_S32)pstFetchGopAttr->u32TotalFrameNum - 1;
            for (; j >= 0 ; j--)
            {
                memcpy(&pstFetchRes->stFrame[pstFetchRes->u32TotalFrameNum - j - 1], pGopReverseFrm + j, sizeof(HI_PVR_FETCH_FRAME_S));
            }
           
            pstFetchRes->u32GopNum++;
            if (pstFetchRes->u32GopNum >= MAX_GOP_NUM_ONCE_FETCH)
            {
                HI_WARN_PVR("Gop num %d is too large\n", pstFetchRes->u32GopNum);
                break;
            }
            pstFetchGopAttr++;
            u32FrmCount = 0;
            u32GopFlag = 0;
            memset(pGopReverseFrm, 0, sizeof(HI_PVR_FETCH_FRAME_S) * MAX_FRAME_NUM_ONCE_FETCH);
            pTmpFetchFrame = pGopReverseFrm;
        }
        else
        {
            pTmpFetchFrame++;
        }
        u32FrmNum = PVR_IDX_PREV_POS_IN_CYC(u32FrmNum, (pstCycMgr->u32LastFrame + 1));
    }

    HI_FREE(HI_ID_PVR, pGopReverseFrm);
    pGopReverseFrm = HI_NULL;
    pTmpFetchFrame = HI_NULL;
    return ret;
}


/* get current GOP's attribute, include total frame number, numbers of B/P frame, from one I frame */
HI_S32 PVR_Index_GetCurGOPAttr(PVR_INDEX_HANDLE piIndexHandle, 
                               HI_PVR_FETCH_RESULT_S *pstFetchResult, 
                               HI_U32 u32StartIFrameNum)
{
    HI_U32 u32FrameNumTmp = u32StartIFrameNum, u32GopFlag = 0;
    HI_S32 s32Ret = 0;
    HI_U32 i = 0;
    PVR_INDEX_ENTRY_S* pstEntry = HI_NULL;
    
    HI_ASSERT_RET(NULL != piIndexHandle);
    HI_ASSERT_RET(NULL != pstFetchResult);

    pstEntry = &pstFetchResult->stFrame[0].stIndexEntry;
    memset(pstFetchResult, 0, sizeof(HI_PVR_FETCH_RESULT_S));

    if (HI_TRUE != PVRIndexIsFrameValid(u32StartIFrameNum, &piIndexHandle->stCycMgr))
    {
        HI_ERR_PVR("input frame number is invalid.\n");
        return HI_FAILURE;
    }

    if(HI_SUCCESS != PVR_Index_GetFrameByNum(piIndexHandle, pstEntry, u32StartIFrameNum))
    {
         HI_WARN_PVR("get the %d entry fail.\n", u32StartIFrameNum);
         return HI_FAILURE;
    }

    if (!PVR_INDEX_is_Iframe(pstEntry))
    {
        HI_WARN_PVR("Start frame is not a I frame.\n");
        return HI_FAILURE;
    }

    while(1)
    {
        pstEntry = &pstFetchResult->stFrame[i].stIndexEntry;

        if (piIndexHandle->stCycMgr.u32EndFrame <= piIndexHandle->stCycMgr.u32StartFrame)
        {
            if (u32FrameNumTmp > piIndexHandle->stCycMgr.u32LastFrame)
                u32FrameNumTmp = 0;

            if ((u32FrameNumTmp > piIndexHandle->stCycMgr.u32EndFrame) && 
                (u32FrameNumTmp < piIndexHandle->stCycMgr.u32StartFrame))
            {
                HI_ERR_PVR("Curnum %d invalide, can't find next I frame.\n", u32FrameNumTmp);
                return HI_FAILURE;
            }
        }
        else
        {
            if (u32FrameNumTmp > piIndexHandle->stCycMgr.u32LastFrame)
            {
                HI_ERR_PVR("Curnum %d invalide, can't find next I frame.\n", u32FrameNumTmp);
                return HI_FAILURE;
            }
        }

        s32Ret = PVR_Index_GetFrameByNum(piIndexHandle, pstEntry, u32FrameNumTmp);
        if (HI_SUCCESS != s32Ret)
        {   
             if (HI_ERR_PVR_FILE_TILL_END == s32Ret)
             {
                HI_INFO_PVR("Reach the end of index, return success.\n");
                return HI_SUCCESS;
             }
             else
             {
                HI_ERR_PVR("Get the %d entry fail.\n", u32FrameNumTmp);
                return HI_FAILURE;
             }
        }

        if (PVR_INDEX_is_Iframe(pstEntry))
        {
            u32GopFlag++;
            if (u32GopFlag > 1)
                break;
        }

        if (piIndexHandle->stCycMgr.u32EndFrame == u32FrameNumTmp)
        {
            break;
        }

        if (PVR_INDEX_is_Pframe(pstEntry))
        {
            pstFetchResult->u32PFrameNum++;
        }

        if (PVR_INDEX_is_Bframe(pstEntry))
        {
            pstFetchResult->u32BFrameNum++;
        }

        pstFetchResult->stFrame[i].u32FrameNum = u32FrameNumTmp;
        pstFetchResult->stFrame[i].u32FrameType = PVR_INDEX_get_frameType(pstEntry);

        i++;
        u32FrameNumTmp++;
        pstFetchResult->u32TotalFrameNum = i;
    }

    return HI_SUCCESS;
}


/* the following function for get pointer of some filed of structure PVR_INDEX_HANDLE,
for hi_pvr_smooth_ctrl.c will use these pointer.
Attention: if the contents of these structure changed, need re-compile hi_pvr_smooth_ctrl.c*/
PVR_CYC_MGR_S* PVR_Index_GetCycMgr(PVR_INDEX_HANDLE IndexHandle)
{
    if ((PVR_INDEX_HANDLE)NULL == IndexHandle)
    {
        HI_ERR_PVR("NULL pointer error\n");
        return NULL;
    }
    return (PVR_CYC_MGR_S*)&IndexHandle->stCycMgr;    
}

PVR_INDEX_INFO_S* PVR_Index_GetPVRIdxInfo(PVR_INDEX_HANDLE IndexHandle)
{
    if ((PVR_INDEX_HANDLE)NULL == IndexHandle)
    {
        HI_ERR_PVR("NULL pointer error\n");
        return NULL;
    }
    return (PVR_INDEX_INFO_S*)&IndexHandle->stRecIdxInfo.stIdxInfo;    
}

HI_U32 PVR_Index_GetCurReadFrameNum(PVR_INDEX_HANDLE IndexHandle)
{
    if ((PVR_INDEX_HANDLE)NULL == IndexHandle)
    {
        HI_ERR_PVR("NULL pointer error\n");
        return HI_FAILURE;
    }
    return IndexHandle->u32ReadFrame;   
}

HI_S32 PVR_Index_SetCurReadFrameNum(PVR_INDEX_HANDLE handle, HI_U32 u32ReadFrame)
{
    if ((PVR_INDEX_HANDLE)NULL == handle)
    {
        HI_ERR_PVR("NULL pointer error\n");
        return HI_FAILURE;
    }

    PVR_INDEX_LOCK(&handle->stMutex);
    handle->u32ReadFrame = u32ReadFrame;
    if (handle->bIsRec)
    {
        if (handle->bRecReachPlay && PVRIndexIsFrameValid(u32ReadFrame, &handle->stCycMgr))
        {
            handle->bRecReachPlay = HI_FALSE;
        }
    }
    PVR_INDEX_UNLOCK(&handle->stMutex);
    return HI_SUCCESS;   
}

HI_BOOL PVR_Index_CheckIndexFrmValid(HI_U32 u32IndexFrm, PVR_CYC_MGR_S *pstIndexCycMgr)
{
    return PVRIndexIsFrameValid(u32IndexFrm, pstIndexCycMgr);
}

HI_VOID PVR_Index_CycMoveReadFrm(PVR_INDEX_HANDLE handle, HI_S32 s32Offset)
{
    PVR_INDEX_LOCK(&handle->stMutex);
    PVRIndexCycMoveReadFrame(handle, s32Offset);
    PVR_INDEX_UNLOCK(&handle->stMutex);
}

//1--forward direction   0--backward direction
HI_U32 PVR_Index_CalcFrameDistance(HI_U32 u32Dst, HI_U32 u32Src, HI_U32 u32Direction, PVR_CYC_MGR_S *pstCycMgr)
{
    if (pstCycMgr->u32LastFrame == 0)
    {
        return 0;
    }

    if (u32Direction == 1)
    {
        return (u32Dst + pstCycMgr->u32LastFrame + 1 - u32Src)%(pstCycMgr->u32LastFrame + 1);
    }
    else
    {
        return (u32Src + pstCycMgr->u32LastFrame + 1 - u32Dst)%(pstCycMgr->u32LastFrame + 1);
    }
}

HI_U32 PVR_Index_GetNextFrameNum(HI_U32 u32FrmNum, PVR_CYC_MGR_S *pstCycMgr)
{
    return PVR_IDX_NEXT_POS_IN_CYC(u32FrmNum, (pstCycMgr->u32LastFrame + 1));
}

HI_U32 PVR_Index_GetPrevFrameNum(HI_U32 u32FrmNum, PVR_CYC_MGR_S *pstCycMgr)
{
    return PVR_IDX_PREV_POS_IN_CYC(u32FrmNum, (pstCycMgr->u32LastFrame + 1));
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

