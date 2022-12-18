/*                                                                           */
/* Author: Lei zhen                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2009-06-10                                                          */
/*                                                                           */
/* Description:                                                              */
/*     Hardware interrupt implementation                                     */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2009-06-10                                                       */
/*    Author: Lei zhen                                                       */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _SRE_HWI_PH
#define _SRE_HWI_PH

#include "sre_base.h"
#include "sre_hwi.h"

#include "sre_asm.ph"
#include "sre_err.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */



#define OS_HWI_ALL_BITS                                     0xffffffff

#define OS_SGI_MAX_NUM                                       15

#define OS_HWI_MAX_NUM                                      192
#define OS_HWI_MAX_PRIORITY                               256
#define OS_HWI_MIN                                          0
#define OS_HWI_MAX                                          (OS_HWI_MAX_NUM - 1)
#define OS_HWI_HAC_EXC                                      (OS_HWI_MAX + 1)
#define OS_HWI_MAX_PRIOR                                    4
#define OS_HWI_PRIOR_NORMAL                                 1
#define OS_HWI_MAX_COMBINE_NODE                             8


#define OS_HWI_TIMER0                                       6
#define OS_HWI_TIMER1                                       10
#define OS_HWI_TIMER2                                       13


#define OS_HWI_TICK_INT                                     OS_HWI_TIMER0
#define OS_HWI_MAX_NEST_DEPTH                               6

#define OS_HWI_MODE_UNSET                                   0

#define OS_HWI_SOFT_TRIGGER_HIGH                            11
#define OS_HWI_SOFT_TRIGGER_LOW                             7

#define OS_EVEN_HWSEM_ID                                     8
#define OS_ODD_HWSEM_ID                                      9

typedef struct tagHwiModeForm
{
    HWI_MODE_T usMode;
    UINT16     usReserse;
} HWI_MODE_FORM_S;

typedef struct tagHwiHandleForm
{
    HWI_PROC_FUNC pfnHook;
    HWI_ARG_T     uwParam;
} HWI_HANDLE_FORM_S;

typedef struct tagHwiCombineNode
{
    HWI_PROC_FUNC pfnCmbHook;
    HWI_ARG_T uwCmbParam;
    struct tagHwiCombineNode *pstNext;
} HWI_COMBINE_NODE_S;


typedef UINT32 (*HW_CLEAR_PENDINGBit_FUNC)(UINT32);

extern HWI_MODE_FORM_S m_astHwiModeForm[OS_HWI_MAX_NUM];
extern HWI_HANDLE_FORM_S m_astHwiForm[OS_HWI_MAX_NUM + 2];   /* Resved 2 for hac exception & exception */

extern VOID osHwiDefaultHandler(HWI_ARG_T uwArg);
extern VOID osHwiCombineDispatchHandler(HWI_ARG_T);
extern VOID osHwiRegsInit(VOID);
extern UINT32 osHwiSetHandler(UINT32 uwHwiNum, HWI_PROC_FUNC pfnHandler);

extern UINT32 osHwiClearPendingBit_08(HWI_HANDLE_T uwHwiNum);

extern UINT32 osHwiClearPendingBit_81(HWI_HANDLE_T uwHwiNum);




#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_HWI_PH */

