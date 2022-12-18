/**
\file
\brief memory manager in boot
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2010-0513
\version draft
\author a
\date 2010-5-13
*/
#include "higo_common.h"
#include "higo_memory.h"
#include "hi_common.h"
#ifdef __cplusplus
extern "C" {
#endif

#define DEC_BUF_LEN            0x1000000
#ifndef HIGO_CODE_CUT
typedef struct _BT_USED_S
{
    HI_U32 u32Size;
    HI_U8  pData[1];
}BT_USED_S;


static HI_U32  s_bt_BufferSize = 0;
static HI_VOID *s_bt_BufferHead = NULL;
static HI_U32  s_bt_bInitalize = 0;
static HI_U32  s_bt_UsedSize = 0;

#define MEM_ALIGN_SIZE 16
#endif
static BT_FREE_S *s_bt_pFreeBlock = NULL;
static HI_S32 HIGO_InitMemoryBlock(HI_VOID)
{
#ifndef HIGO_CODE_CUT
    s_bt_pFreeBlock = (BT_FREE_S*)s_bt_BufferHead;
    if(NULL == s_bt_pFreeBlock)
    {
        return HI_FAILURE;
    }
    s_bt_pFreeBlock->u32Size = s_bt_BufferSize;
    s_bt_pFreeBlock->pNext = NULL;
    s_bt_bInitalize = 1;
#endif    
    return HI_SUCCESS;
}
HI_S32 HIGO_InitMemory(HI_VOID)
{
#ifndef HIGO_CODE_CUT
    HI_S32 ret;
    MMZ_BUFFER_S  psMBuf;
    
    ret = HI_MEM_Alloc(&psMBuf.u32StartPhyAddr, DEC_BUF_LEN);
    if(ret != HI_SUCCESS)
    {
        HIGO_ERROR(ret);
        return HI_FAILURE;
    }        
    
    if(s_bt_bInitalize) 
    {
        return HI_FAILURE;
    }
    if((0 == psMBuf.u32StartPhyAddr) || (DEC_BUF_LEN < sizeof(BT_FREE_S)))
    {
        return HI_FAILURE;
    }
    s_bt_BufferHead = (HI_VOID*)psMBuf.u32StartPhyAddr;
    s_bt_BufferSize = DEC_BUF_LEN;
  #endif    
    return HIGO_InitMemoryBlock();
}

HI_VOID* HIGO_Malloc2(HI_U32 u32Size)
{
#ifndef HIGO_CODE_CUT
    BT_FREE_S *pCur = NULL,*pPre = NULL;
    HI_U32 umask = MEM_ALIGN_SIZE -1;
    BT_USED_S *pUsed = NULL;
    
    //u32Size = ((u32Size + umask) & ( ~umask )) + sizeof(HI_U32);
    u32Size = ((u32Size + umask) & ( ~umask )) + MEM_ALIGN_SIZE;  //for memory align
    if(s_bt_bInitalize)
    {
    
        if(NULL == s_bt_pFreeBlock)
        {
            return NULL;
        }
        //not enough memory
        if((s_bt_BufferSize - s_bt_UsedSize) < u32Size)
        {
            return NULL;
        }
            
        pCur = s_bt_pFreeBlock;
        while(NULL != pCur)
        {
            if(pCur->u32Size >= u32Size)
            {
                break;
            }
            pPre = pCur;
            pCur = pCur->pNext;
        }
        //couldn't find a block that is larger than the acquiredsize 
        if(NULL == pCur)
        {
            return NULL;
        }
        //find a block 
        if(pCur->u32Size == u32Size)
        {
            // the first block is ok
            if(NULL == pPre)
            {
                s_bt_pFreeBlock = s_bt_pFreeBlock->pNext;
            }
            else
            {
                pPre->pNext = pCur->pNext;
            }
        }
        else
        {
            pCur->u32Size -= u32Size;
            pCur = (BT_FREE_S*)((HI_U8*)pCur + pCur->u32Size);
        }
        //pCur is the block that will be use
        pUsed = (BT_USED_S*)(HI_VOID*)pCur;
        pUsed->u32Size = u32Size;
        s_bt_UsedSize += u32Size;
        return pUsed->pData +(MEM_ALIGN_SIZE -4);
    }
	return NULL;
#else
    HI_S32 ret;
    MMZ_BUFFER_S  psMBuf;
    
    ret = HI_MEM_Alloc(&psMBuf.u32StartPhyAddr, u32Size);
    if(ret != HI_SUCCESS)
    {
        HIGO_ERROR(ret);
        return NULL;
    }  
    return (HI_U8*)psMBuf.u32StartPhyAddr;
#endif
}

HI_VOID HIGO_Free2(HI_VOID* pAddr)
{
#ifndef HIGO_CODE_CUT
    BT_FREE_S *pFree = NULL,*pPre = NULL,*pCur = NULL;
    BT_USED_S *pUsed = NULL;
    if(s_bt_bInitalize)
    {
        if(NULL == pAddr)
        {
            return ;
        }
        pUsed = (BT_USED_S*)((HI_U32)pAddr - MEM_ALIGN_SIZE);
        pFree = (BT_FREE_S*)(HI_VOID*)pUsed;
        if(((HI_U8*)pFree < (HI_U8*)s_bt_BufferHead)
            || ((HI_U8*)pFree >= (HI_U8*)s_bt_BufferHead + s_bt_BufferSize))
        {
            return ;
        }
        if(NULL == s_bt_pFreeBlock)
        {
            s_bt_pFreeBlock = pFree;
            s_bt_pFreeBlock->pNext = NULL;
            s_bt_UsedSize -= pFree->u32Size;
            return ;
        }
        pCur = s_bt_pFreeBlock;
        while(NULL !=pCur && pCur < pFree)
        {
            pPre = pCur;
            pCur = pCur->pNext;
        }
        //in front of the list
        if(NULL == pPre)
        {
            pFree->pNext = s_bt_pFreeBlock;
            if((HI_U8*)pFree + pFree->u32Size == (HI_U8*)s_bt_pFreeBlock)
            {
                pFree->pNext = s_bt_pFreeBlock->pNext;
                pFree->u32Size += s_bt_pFreeBlock->u32Size;
            }
            s_bt_pFreeBlock = pFree;
            s_bt_UsedSize -= pFree->u32Size;
            return ;
        }
        //behide the list
        if(NULL == pCur)
        {
            pPre->pNext = pFree;
            pFree->pNext = NULL;
            if((HI_U8*)pPre + pPre->u32Size == (HI_U8*)pFree)
            {
                pPre->pNext = NULL;
                pPre->u32Size += pFree->u32Size;
            }
            s_bt_UsedSize -= pFree->u32Size;
            return ;
        }
        // pPre ,pCur couldn't be NULL 
        pPre->pNext = pFree;
        pFree->pNext = pCur;
        s_bt_UsedSize -= pFree->u32Size;
        //merge with the pre node
        if((HI_U8*)pPre + pPre->u32Size == (HI_U8*)pFree)
        {
            pPre->pNext = pCur;
            pPre->u32Size += pFree->u32Size;
            pFree = pPre;
        }
        //merge with the post node
        if((HI_U8*)pFree + pFree->u32Size == (HI_U8*)pCur)
        {
            pFree->pNext = pCur->pNext;
            pFree->u32Size += pCur->u32Size;
        }
    }
#endif    
}

HI_VOID HIGO_DeInitMemory(HI_VOID)
{
#ifndef HIGO_CODE_CUT
    if(s_bt_bInitalize)
    {
        s_bt_BufferHead = NULL;
        s_bt_pFreeBlock = NULL;
        s_bt_bInitalize = 0;
        s_bt_BufferSize = 0;
        s_bt_UsedSize =0;
    }
#endif    
    return;
}

BT_FREE_S* HIGO_GetFreeList(HI_VOID)
{
    return s_bt_pFreeBlock;
}

#ifdef __cplusplus
}
#endif

