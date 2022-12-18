#include <stdlib.h>
#include <string.h>
#include "teletext_utils.h"
#include "teletext_debug.h"

#define TTX_QUEUE_LOCK()  \
   do{\
        int ret = pthread_mutex_lock(&pstQueue->Queue_lock);\
        if(ret != 0){\
            HI_ERR_TTX("TTX call pthread_mutex_lock(QUEUE) failure ret = 0x%x\n",ret);\
        }\
    }while(0)

#define TTX_QUEUE_UNLOCK()  \
    do{\
        int ret = pthread_mutex_unlock(&pstQueue->Queue_lock);\
        if(ret != 0){\
            HI_ERR_TTX("TTX call pthread_mutex_unlock(QUEUE) failure ret = 0x%x\n",ret);\
        }\
    }while(0)

#define MIN_GAP (1536) /* 1.5KBytes*/

static HI_S32 IsEmptyQueue(TTX_SEGMENT_QUEUE_S* pstQueue)
{
    if (pstQueue->pstSegmentFront == pstQueue->pstSegmentRear)
    {
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

static HI_S32 IsFullQueue(TTX_SEGMENT_QUEUE_S* pstQueue)
{
    HI_U32 u32Step = sizeof(TTX_SEGMENT_S) + pstQueue->pstSegmentRear->u16DataLength;

    HI_U32 u32RemainSpace = 0;

    if (pstQueue->pstSegmentRear >= pstQueue->pstSegmentFront)
    {
        u32RemainSpace = ((HI_U32)pstQueue->pu8BaseAddr + pstQueue->u32MaxLen) - (HI_U32)pstQueue->pstSegmentRear;

        if ((HI_U32)pstQueue->pstSegmentFront > (HI_U32)pstQueue->pu8BaseAddr)
        {
            u32RemainSpace += (HI_U32)((HI_U32)pstQueue->pstSegmentFront - MIN_GAP - (HI_U32)pstQueue->pu8BaseAddr);
        }
        else
        {
            u32RemainSpace -= MIN_GAP;
        }
    }
    else
    {
        u32RemainSpace = (HI_U32)pstQueue->pstSegmentFront - MIN_GAP - (HI_U32)pstQueue->pstSegmentRear;
    }

    if (u32Step > u32RemainSpace)
    {
        /* Queue  full*/
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

HI_S32 TTX_PesQueue_IsMemTensity(TTX_SEGMENT_QUEUE_S* pstQueue)
{
    HI_U32 u32RemainSpace = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    if (pstQueue == HI_NULL)
    {
        return HI_FAILURE;
    }

    TTX_QUEUE_LOCK();

    if (pstQueue->pstSegmentRear >= pstQueue->pstSegmentFront)
    {
        u32RemainSpace = ((HI_U32)pstQueue->pu8BaseAddr + pstQueue->u32MaxLen) - (HI_U32)pstQueue->pstSegmentRear;

        if ((HI_U32)pstQueue->pstSegmentFront > (HI_U32)pstQueue->pu8BaseAddr)
        {
            u32RemainSpace += ((HI_U32)pstQueue->pstSegmentFront - (HI_U32)pstQueue->pu8BaseAddr);
        }
        else
        {}
    }
    else
    {
        u32RemainSpace = (HI_U32)pstQueue->pstSegmentFront - (HI_U32)pstQueue->pstSegmentRear;
    }

    if (u32RemainSpace > (pstQueue->u32MaxLen / 6))
    {
        s32Ret = HI_SUCCESS;
    }
    else
    {
        s32Ret = -2;
    }

    TTX_QUEUE_UNLOCK();

    return s32Ret;
}

HI_S32 TTX_PesQueue_Init(TTX_SEGMENT_QUEUE_S* pstQueue, const HI_U8* pszBufAddr, HI_U32 u32BufLen)
{
    if ((pstQueue == NULL) || (pszBufAddr == NULL) || (u32BufLen == 0))
    {
        return HI_FAILURE;
    }

    memset((void*)pszBufAddr, 0, u32BufLen);
    TTX_QUEUE_LOCK();
    pstQueue->pu8BaseAddr = pszBufAddr;
    pstQueue->u32MaxLen = u32BufLen;

    pstQueue->pstSegmentFront = (TTX_SEGMENT_S*)pszBufAddr;
    pstQueue->pstSegmentFront->pu8SegmentData = NULL;
    pstQueue->pstSegmentFront->pstNext = NULL;

    pstQueue->pstSegmentRear = (TTX_SEGMENT_S*)pszBufAddr;
    pstQueue->pstSegmentRear->pu8SegmentData = NULL;
    pstQueue->pstSegmentRear->pstNext = NULL;
    TTX_QUEUE_UNLOCK();
    return HI_SUCCESS;
}

HI_S32 TTX_PesQueue_En(TTX_SEGMENT_QUEUE_S* pstQueue, TTX_SEGMENT_S* pSegment)
{
    HI_U32 u32DataTypeSize = sizeof(TTX_SEGMENT_S);
    HI_U32 u32ItemSize = 0;
    TTX_SEGMENT_S* pstNextSegAddr = NULL;

    if ((pstQueue == NULL) || (pSegment == NULL))
    {
        return HI_FAILURE;
    }

    TTX_QUEUE_LOCK();

    pstQueue->pstSegmentRear->u16DataLength = pSegment->u16DataLength;
    if (IsFullQueue(pstQueue) == HI_SUCCESS)
    {
        TTX_QUEUE_UNLOCK();

        return HI_FAILURE;
    }

    u32ItemSize = u32DataTypeSize + pSegment->u16DataLength;

    if (((HI_U32)pstQueue->pstSegmentRear + u32ItemSize) > ((HI_U32)pstQueue->pu8BaseAddr + pstQueue->u32MaxLen))
    {
        pstQueue->pstSegmentRear->pu8SegmentData = (HI_U8*)((HI_U32)pstQueue->pu8BaseAddr + u32DataTypeSize);
    }
    else
    {
        pstQueue->pstSegmentRear->pu8SegmentData = (HI_U8*)((HI_U32)pstQueue->pstSegmentRear + u32DataTypeSize);
    }

    pstQueue->pstSegmentRear->u16DataLength = pSegment->u16DataLength;

    memcpy(pstQueue->pstSegmentRear->pu8SegmentData, pSegment->pu8SegmentData, pSegment->u16DataLength);

    pstNextSegAddr = (TTX_SEGMENT_S*)((HI_U32)pstQueue->pstSegmentRear + u32ItemSize);
    if (((HI_U32)pstNextSegAddr + u32DataTypeSize) > ((HI_U32)pstQueue->pu8BaseAddr + pstQueue->u32MaxLen))
    {
        pstNextSegAddr = (TTX_SEGMENT_S*)pstQueue->pu8BaseAddr;
    }

    pstNextSegAddr->pu8SegmentData = NULL;
    pstNextSegAddr->pstNext = NULL;
    pstQueue->pstSegmentRear->pstNext = pstNextSegAddr;
    pstQueue->pstSegmentRear = pstNextSegAddr;
    pstQueue->pstSegmentRear->u16DataLength = 0;
    if (IsFullQueue(pstQueue) == HI_SUCCESS)
    {
        TTX_QUEUE_UNLOCK();
        return HI_FAILURE;
    }

    TTX_QUEUE_UNLOCK();
    return HI_SUCCESS;
}

HI_S32 TTX_PesQueue_De(TTX_SEGMENT_QUEUE_S* pstQueue, TTX_SEGMENT_S* pSegment)
{
    TTX_QUEUE_LOCK();

    if (IsEmptyQueue(pstQueue) == HI_SUCCESS)
    {
        TTX_QUEUE_UNLOCK();

        return HI_FAILURE;
    }

    pSegment->u16DataLength = pstQueue->pstSegmentFront->u16DataLength;

    pSegment->pu8SegmentData = pstQueue->pstSegmentFront->pu8SegmentData;
    pSegment->pstNext = NULL;
    pstQueue->pstSegmentFront = pstQueue->pstSegmentFront->pstNext;

    TTX_QUEUE_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 TTX_PesQueue_Reset(TTX_SEGMENT_QUEUE_S* pstQueue, const HI_U8* pszBufAddr, HI_U32 u32BufLen)
{
    if ((pstQueue == NULL) || (pszBufAddr == NULL) || (u32BufLen == 0))
    {
        return HI_FAILURE;
    }

    TTX_QUEUE_LOCK();
    memset((void*)pszBufAddr, 0, u32BufLen);

    pstQueue->pu8BaseAddr = pszBufAddr;
    pstQueue->u32MaxLen = u32BufLen;

    pstQueue->pstSegmentFront = (TTX_SEGMENT_S*)pszBufAddr;
    pstQueue->pstSegmentFront->pu8SegmentData = NULL;
    pstQueue->pstSegmentFront->pstNext = NULL;

    pstQueue->pstSegmentRear = (TTX_SEGMENT_S*)pszBufAddr;
    pstQueue->pstSegmentRear->pu8SegmentData = NULL;
    pstQueue->pstSegmentRear->pstNext = NULL;

    TTX_QUEUE_UNLOCK();
    return HI_SUCCESS;
}
