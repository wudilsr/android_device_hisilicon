/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon), 
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name           : wmalloc.c
Version             : Initial Draft
Author              : 
Created             : 2014/08/06
Description         :
Function List       : 
History             :
Date                       Author                   Modification
2014/08/06                 y0081162                 Created file        
******************************************************************************/

/*********************************add include here******************************/
#include "tde_define.h"
#include "wmalloc.h"



/***************************** Macro Definition ******************************/
#define TDE_UNIT64_NUM          1536                                                /* 96k */
#define TDE_UNIT128_NUM         640                                                 /* 80k */
#define TDE_UNIT128_OFFSET     (TDE_UNIT64_NUM * 64)
#define TDE_UNIT1024_NUM        32                                                  /* 32k */
#define TDE_UNIT1024_OFFSET     (TDE_UNIT128_OFFSET + TDE_UNIT128_NUM * 128)
#define TDE_MEMPOOL_SIZE        (TDE_UNIT1024_OFFSET + (TDE_UNIT1024_NUM * 1024))    /* 208k */


/*************************** Structure Definition ****************************/
typedef struct _MemoryBlock
{
    HI_U32          nSize;
    HI_U16          nFree;
    HI_U16          nFirst;
    HI_U16          nUnitSize;
    struct _MemoryBlock*    pNext;
    HI_U8*          pStartAddr;
}MemoryBlock;

typedef enum 
{
    UNIT_SIZE_64 = 0,
    UNIT_SIZE_128,
    UNIT_SIZE_1024,
    UNIT_SIZE_BUTT
}UNIT_SIZE_E;


/********************** Global Variable declaration **************************/
static MemoryBlock g_struMemBlock[UNIT_SIZE_BUTT]; 

STATIC HI_U32 g_u32MemPoolPhyAddr;
STATIC HI_U32 g_u32MemPoolVrtAddr;
STATIC HI_U32 g_u32MemPoolSize;

/******************************* API declaration *****************************/
HI_S32 MemoryBlockInit(UNIT_SIZE_E eUnitSize, HI_U32 nUnitNum, HI_U8 *pAddr) 
{
    HI_U16 i;
    HI_U8 *pData = pAddr;
    if((eUnitSize >= UNIT_SIZE_BUTT) || (NULL == pAddr ) || (0 == nUnitNum))
    {
        TDE_TRACE(TDE_KERN_ERR, "\n");
        return HI_FAILURE;
    }
    if(UNIT_SIZE_1024 == eUnitSize)
    {
        g_struMemBlock[eUnitSize].nUnitSize = 1024;
    }
    else
    {
        g_struMemBlock[eUnitSize].nUnitSize = (eUnitSize + 1) * 64;
    }

    for(i = 1; i < nUnitNum; i++)
    {
        /* 最后一个unit不做标记，分配到最后一个unit了就说明所有的unit都分配光了，因而没有下个可分配unit指示 */
        *(HI_U16 *)pData = i;   
        
        pData += g_struMemBlock[eUnitSize].nUnitSize;

    }

    g_struMemBlock[eUnitSize].nFirst = 0;
    g_struMemBlock[eUnitSize].nFree = nUnitNum;
    g_struMemBlock[eUnitSize].nSize = nUnitNum * g_struMemBlock[eUnitSize].nUnitSize;
    g_struMemBlock[eUnitSize].pNext = NULL;
    g_struMemBlock[eUnitSize].pStartAddr = pAddr;

    return HI_SUCCESS;
}

HI_VOID *mallocUnit(UNIT_SIZE_E eUnitSize)
{
    MemoryBlock *pBlock = &g_struMemBlock[eUnitSize];
    HI_U8* pFree = NULL;

    TDE_TRACE(TDE_KERN_DEBUG, "eUnitSize %d, free units:%d, first free unit:%d...\n", eUnitSize, pBlock->nFree, pBlock->nFirst);
    if(!pBlock->nFree)
    {
        return NULL;
    }

    pFree = pBlock->pStartAddr + pBlock->nFirst * pBlock->nUnitSize;
    pBlock->nFirst = *(HI_U16 *)pFree;

    pBlock->nFree--;
    memset(pFree, 0, pBlock->nUnitSize);

    return pFree;
}


HI_VOID *wmalloc(HI_U32 size)
{
    UNIT_SIZE_E i;
    HI_VOID *pMalloc;

    if((size > 1024) || (0 == size))
    {
        return NULL;
    }

    if(size <= 64)
    {
        for(i = UNIT_SIZE_64; i < UNIT_SIZE_BUTT; i++)
        {
            pMalloc = mallocUnit(i);
            if(NULL != pMalloc)
            {
                return pMalloc;
            }
        }

        return NULL;
    }
    else if (size <= 128)
    {
        for(i = UNIT_SIZE_128; i < UNIT_SIZE_BUTT; i++)
        {
            pMalloc = mallocUnit(i);
            if(NULL != pMalloc)
            {
                return pMalloc;
            }
        }

        return NULL;
    }
    else
    {
        return mallocUnit(UNIT_SIZE_1024);
    }
}

HI_S32 freeUnit(UNIT_SIZE_E eUnitSize, HI_VOID *ptr)
{
    MemoryBlock *pBlock = &g_struMemBlock[eUnitSize];

    if(((HI_U32)ptr < (HI_U32)pBlock->pStartAddr) 
        || ((HI_U32)ptr >= ((HI_U32)pBlock->pStartAddr + pBlock->nSize)))
    {
        return HI_FAILURE;
    }

    pBlock->nFree++;
    *(HI_U16*)ptr = pBlock->nFirst; /* 指向下一个可以分配的单元 */
    pBlock->nFirst = ((HI_U32)ptr - (HI_U32)pBlock->pStartAddr)/pBlock->nUnitSize;
    TDE_TRACE(TDE_KERN_DEBUG, "eUnitSize:%d,first free unit:%d\n", pBlock->nUnitSize, pBlock->nFirst);
    TDE_TRACE(TDE_KERN_DEBUG, "eUnitSize:%d,first free unit:%d, free units:%d\n", pBlock->nUnitSize, pBlock->nFirst, pBlock->nFree);

    return HI_SUCCESS;
}

HI_S32 wfree(HI_VOID *ptr)
{
    UNIT_SIZE_E i;
    
    for(i = UNIT_SIZE_64; i < UNIT_SIZE_BUTT; i++)
    {
       if(HI_SUCCESS == freeUnit(i, ptr)) 
       {
            return HI_SUCCESS;
       }
    }

    TDE_TRACE(TDE_KERN_ERR, "Free mem failed!vir:%p, phy:%x\n", ptr, wgetphy(ptr));
    return HI_FAILURE;
}

HI_S32 wmeminit(void)
{

    TDE_MEM_NEW(g_u32MemPoolPhyAddr,TDE_MEMPOOL_SIZE, 4, "ddr", "TDE_MEMPOOL");
    if (0 == g_u32MemPoolPhyAddr)
    {
        return HI_FAILURE;
    }

    g_u32MemPoolVrtAddr = TDE_MEM_MAP(g_u32MemPoolPhyAddr, HI_FALSE);
    if (g_u32MemPoolVrtAddr == 0)
    {
        TDE_MEM_FREE(g_u32MemPoolPhyAddr);
        return HI_FAILURE;
    }

    MemoryBlockInit(UNIT_SIZE_64, TDE_UNIT64_NUM, (HI_VOID *)g_u32MemPoolVrtAddr);
    MemoryBlockInit(UNIT_SIZE_128, TDE_UNIT128_NUM, (HI_VOID *)(g_u32MemPoolVrtAddr + TDE_UNIT128_OFFSET));

    MemoryBlockInit(UNIT_SIZE_1024, TDE_UNIT1024_NUM, (HI_VOID *)(g_u32MemPoolVrtAddr + TDE_UNIT1024_OFFSET));

    g_u32MemPoolSize = TDE_UNIT1024_OFFSET + TDE_UNIT1024_NUM * 1024;
    
    return HI_SUCCESS;
	
}

HI_VOID wmemterm(void)
{
    TDE_MEM_UNMAP(g_u32MemPoolPhyAddr);
    TDE_MEM_FREE(g_u32MemPoolPhyAddr);

    g_u32MemPoolPhyAddr  = 0;
    g_u32MemPoolVrtAddr  = 0;
    g_u32MemPoolSize     = 0;

    return;
    
}

HI_U32 wgetphy(HI_VOID *ptr)
{
    HI_U32 u32MemVrt = (HI_U32)ptr;  

    if((u32MemVrt < g_u32MemPoolVrtAddr)
        || (u32MemVrt >= (g_u32MemPoolVrtAddr + g_u32MemPoolSize)))
    {
        return 0;
    }

    return (g_u32MemPoolPhyAddr + (u32MemVrt - g_u32MemPoolVrtAddr));
}

HI_VOID * wgetvrt(HI_U32 phyaddr)
{
    if((phyaddr < g_u32MemPoolPhyAddr)
        || (phyaddr >= (g_u32MemPoolPhyAddr + g_u32MemPoolSize)))
    {
        return NULL;
    }

    return (HI_VOID *)(g_u32MemPoolVrtAddr + (phyaddr - g_u32MemPoolPhyAddr));
}

HI_U32 wgetfreenum(HI_VOID)
{
    UNIT_SIZE_E eUnitSize = 0;
    HI_U32 u32FreeUnitNum = g_struMemBlock[eUnitSize].nFree;
    

    for(eUnitSize = UNIT_SIZE_64; eUnitSize < UNIT_SIZE_BUTT; eUnitSize++)
    {
        u32FreeUnitNum = (u32FreeUnitNum > g_struMemBlock[eUnitSize].nFree)?g_struMemBlock[eUnitSize].nFree:u32FreeUnitNum;
    }

    return u32FreeUnitNum;
}
