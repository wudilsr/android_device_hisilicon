/*****************************************************************************/
/*                                                                           */
/*                Copyright 2008 - 2050, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* Author: gaoxiong                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2011-11-15                                                          */
/*                                                                           */
/* Description:                                                              */
/*     Hardware involved                                                     */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2011-11-15                                                       */
/*    Author: gaoxiong                                                       */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _SRE_HW_PH
#define _SRE_HW_PH

#include "sre_base.h"
#include "sre_task.h"
#include "sre_exc.h"
#include "sre_hwi.h"
#include "sre_asm.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

typedef VOID ( *DBG_VECT_FUNC )(VOID);

#define OS_HW_DCACHE_WB(pAddr, uwSize, bWait)
#define OS_HW_DCACHE_WBINV(pAddr, uwSize, bWait)

#define ARCH_TSK_GET_CONTEXT_PTR(pAddr)                     (0)
#define ARCH_TSK_GET_STKSP_ADDR(pAddr)                      (0)
#define ARCH_TSK_GET_INSTR_ADDR(pAddr)                      (0)

#define OS_EMBED_ASM  __asm__

OS_SEC_ALW_INLINE INLINE UINT32 osMemAddrToUncache(VOID *pAddr)
{
    return (UINT32)pAddr;
}

OS_SEC_ALW_INLINE INLINE UINT32 osMemAddrToOriginal(VOID *pAddr, VOID *pReferAddr)
{
    return (UINT32)(((UINT32)pAddr & 0x7fffffff) | ((UINT32)pReferAddr & 0x80000000));
}


extern VOID _osSwiTrap();

#define osSwiTrap() _osSwiTrap()


#if (OS_BYTE_ORDER == OS_BIG_ENDIAN)
INLINE UINT32 OS_BYTE_ORDER_SWAP32(UINT32 x)
{
    UINT32 uwRet;
    __asm__ __volatile__ (
            "REV %0, %1"
            :"=r"(uwRet) : "r"(x));
    return uwRet;
}
#else
INLINE UINT32 OS_BYTE_ORDER_SWAP32(UINT32 x)
{
    return x;
}
#endif

INLINE UINT32 osGetLMB1(UINT32 uwValue) __attribute__((always_inline));
INLINE UINT32 osGetLMB1(UINT32 uwValue)
{
    UINT32 uwLMB;
    __asm__ __volatile__(
            "CLZ %0, %1"
            :"=r"(uwLMB) : "r"(uwValue));
    return uwLMB;
}

INLINE UINT32 osGetCoreID() __attribute__((always_inline));
INLINE UINT32 osGetCoreID()
{
    UINT32 uwCoreID;
    __asm__ __volatile__( "MRC  p15, 0, %0, c0, c0, 5"
           :"=r"(uwCoreID));
    return uwCoreID & 0x3;
}

extern VOID osHwInit();
extern UINT32 osHwSysInit(VOID);
extern VOID osExcDispatch(UINT32 uwArg);
extern VOID * osTskStackInit(UINT32 uwTaskID, TSK_INIT_PARAM_S *pstTaskInitParam, VOID *pTopStack);
extern VOID * osTskKernelStackInit(UINT32 uwTaskID, UINT32 uwStackSize, VOID *pTopStack);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_CONFIG_H */
