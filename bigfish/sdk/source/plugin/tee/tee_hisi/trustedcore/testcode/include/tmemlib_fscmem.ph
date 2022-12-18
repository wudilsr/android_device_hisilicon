/*****************************************************************************/
/*                                                                           */
/*                Copyright 2008 - 2050, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* Author: Wanghongbo                                                        */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2011-09-17                                                          */
/*                                                                           */
/* Description:                                                              */
/*     Fsc memory implementation                                             */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2011-09-17                                                       */
/*    Author: Wanghongbo                                                     */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _TMEMLIB_FSCMEM_PH
#define _TMEMLIB_FSCMEM_PH

#include "sre_base.h"
#include "sre_mem.h"
#include "tmemlib_mem.ph"
#include "sre_hw.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/* 私有FSC分区控制头 */
typedef struct tagFSCMemPtCtrl
{
    UINT32                      uwPeakSize;                  /* 记录分区中最靠后的申请内存快尾，用于计算该分区最大的使用量 */
    OS_FSC_MEM_CTRL_S          *pstFscFreeHead;
}FSCMEM_MEM_PT_CTRL_S;

/* 分区控制头大小 */
#define OS_FSCMEM_MEM_PT_CTRL_SIZE   sizeof(FSCMEM_MEM_PT_CTRL_S)


#define OS_FSC_MEM_MAX_TYPE                                 16  //最大支持块类型为65535字节
#define OS_FSC_MEM_IDX_LAST                                 31
#define OS_FSC_MEM_MAX_SIZE                                 0x10000
#define OS_FSC_MEM_PREV_USED                                0
#define OS_FSC_MEM_USED_MAGIC                               (OS_FSC_MEM_CTRL_S*)OS_SLICE_HEAD_MAGICWORD
#define OS_FSC_MEM_SIZE_ALIGN                               4
#define OS_FSC_MEM_SLICE_HEAD_SIZE                          sizeof(OS_FSC_MEM_CTRL_S)
#define OS_FSC_MEM_MIN_SIZE                                 (OS_FSC_MEM_SLICE_HEAD_SIZE + OS_FSC_MEM_SIZE_ALIGN)
#define OS_FSC_MEM_FREE_LIST_HEAD_SHIFT                     8  //两个分区复用一个空闲链表头数组，第二个分区空闲头地址相对于第一个分区的偏移

/*缺省共享静态FSC分区控制头大小: sizeof(MCMEM_FSCMEM_PT_CTRL_S) + 空闲链表头数组 + 为使得两个分区可复用同一个空闲链表头数组而预留的8字节*/
#define OS_FSC_MEM_DEF_MCSTAFSCPT_HEAD_SIZE                 (sizeof(MCMEM_FSCMEM_PT_CTRL_S) +\
                                                            sizeof(OS_FSC_MEM_CTRL_S) * OS_FSC_MEM_MAX_TYPE +\
                                                            OS_FSC_MEM_FREE_LIST_HEAD_SHIFT)
#define OS_FSC_MEM_SZ2IDX(uwSize)                           (31 - osGetLMB1(uwSize))
#define OS_FSC_MEM_IDX2BIT(uwIdx)                           ((UINT32)0x80000000 >> (uwIdx))
#define OS_FSC_MEM_SZGET(pstCurrBlk)                        ((UINT32)(pstCurrBlk->usSize))

/*****************************************************************************************************/
OS_SEC_ALW_INLINE INLINE VOID osFscMemDelete(OS_FSC_MEM_CTRL_S *pstCurrBlk)
{
    pstCurrBlk->pstNext->pstPrev = pstCurrBlk->pstPrev;
    pstCurrBlk->pstPrev->pstNext = pstCurrBlk->pstNext;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _TMEMLIB_FSCMEM_PH */

