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

/* ˽��FSC��������ͷ */
typedef struct tagFSCMemPtCtrl
{
    UINT32                      uwPeakSize;                  /* ��¼���������������ڴ��β�����ڼ���÷�������ʹ���� */
    OS_FSC_MEM_CTRL_S          *pstFscFreeHead;
}FSCMEM_MEM_PT_CTRL_S;

/* ��������ͷ��С */
#define OS_FSCMEM_MEM_PT_CTRL_SIZE   sizeof(FSCMEM_MEM_PT_CTRL_S)


#define OS_FSC_MEM_MAX_TYPE                                 16  //���֧�ֿ�����Ϊ65535�ֽ�
#define OS_FSC_MEM_IDX_LAST                                 31
#define OS_FSC_MEM_MAX_SIZE                                 0x10000
#define OS_FSC_MEM_PREV_USED                                0
#define OS_FSC_MEM_USED_MAGIC                               (OS_FSC_MEM_CTRL_S*)OS_SLICE_HEAD_MAGICWORD
#define OS_FSC_MEM_SIZE_ALIGN                               4
#define OS_FSC_MEM_SLICE_HEAD_SIZE                          sizeof(OS_FSC_MEM_CTRL_S)
#define OS_FSC_MEM_MIN_SIZE                                 (OS_FSC_MEM_SLICE_HEAD_SIZE + OS_FSC_MEM_SIZE_ALIGN)
#define OS_FSC_MEM_FREE_LIST_HEAD_SHIFT                     8  //������������һ����������ͷ���飬�ڶ�����������ͷ��ַ����ڵ�һ��������ƫ��

/*ȱʡ����̬FSC��������ͷ��С: sizeof(MCMEM_FSCMEM_PT_CTRL_S) + ��������ͷ���� + Ϊʹ�����������ɸ���ͬһ����������ͷ�����Ԥ����8�ֽ�*/
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

