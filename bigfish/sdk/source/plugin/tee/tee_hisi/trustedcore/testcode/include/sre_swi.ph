/**
* @file sre_swi.ph
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：软中断模块的内部公共头文件。 \n
*/

#ifndef _SRE_SWI_PH
#define _SRE_SWI_PH

#include "sre_base.h"
#include "sre_swi.h"
#include "sre_list.ph"
#include "sre_sys.ph"
#include "sre_sys.h"
#include "sre_task.h"
#include "sre_err.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define SWI_INVALID_IDX    0xFFFF

#define SWI_MIN_CFG_NUM                0                         /*软中断配置允许的最小个数*/
#define SWI_MAX_CFG_NUM                125                       /*软中断配置允许的最大个数*/

#define GET_SWI_OBJLIST(ptr)           LIST_COMPONENT(ptr, SWI_ATTRIBUTE_S, stObjList)

#define CHECK_SWI_ID(uwSwiID)          ((uwSwiID - OS_SYS_PID_BASE) >= g_usSwiMaxNum)

#define SWI_GET_INDEX(uwSwiID)          ((uwSwiID) & 0x000000FF)

#define GET_SCB_HANDLE(SwiPID)      ((SWI_ATTRIBUTE_S *)&(g_stSwiData.pstList[GET_HANDLE(SwiPID)]))

/*判断是否创建有多个软中断*/
#define CHECK_SWI_MULTI(usPrio)         (g_aucSwiNum[usPrio] > 1)

/*软中断优先级的BIT掩码*/
#define SWI_PRIO_MASK(usPrio)           ((UINT32)0x80000000 >> (usPrio))

/*设置软中断就绪位,参数为软中断优先级的BIT掩码*/
#define SET_SWI_READY(uwPrioMask)       (g_vuwSwiRdy |= (uwPrioMask))

/*清除软中断就绪位,参数为软中断优先级的BIT掩码*/
#define CLR_SWI_READY(uwPrioMask)       (g_vuwSwiRdy &= ~(uwPrioMask))

//#define OS_TRACE_SWI_DEL(uwSwiPid)\
//    ((NULL == g_pfnTraceSwiDel) ? ((VOID)0) : (VOID)g_pfnTraceSwiDel(uwSwiPid))

//typedef UINT32 (*OS_MCSWI_ACTIVE_FUNC) (UINT32, UINT8, UINT32);
typedef UINT32 (*OS_SWI_ACTIVE_FUNC)   (UINT32);
typedef UINT32 (* SWI_NAMEADD_FUNC)    (UINT32 uwSwiID, CHAR* pcName);
typedef VOID   (* SWI_NAMEDEL_FUNC)    (UINT32 uwSwiID);
//typedef UINT32 (* TRACE_INT_DELETE)    (UINT32);
typedef VOID   (* SWI_CORESLEEP_FUNC)  (VOID);

/**
* 软中断属性的结构体定义。
*
* pfnHandler-->uwInitValue的位置不能变动，汇编中已写死，结构大小也固定。
* uwRealValue，uwLockValue的位置不能变动，汇编中已写死。且uwRealValue的地址
   是8的倍数。
* Attention: for performance, the size of SWI_ATTRIBUTE_S must be multiple of 8
*/
typedef struct tagSwiAttribute
{
    SWI_PROC_FUNC pfnHandler;           /* 软中断处理函数           */
    SWI_STATUS_T  usStatus;             /* 软中断状态               */
    SWI_PRIOR_T   usPriority;           /* 软中断优先级             */
    UINT32        uwRealValue;          /* 软中断实时值             */
    UINT32        uwLockValue;          /* 软中断触发时的锁存值     */
    UINT32        uwInitValue;          /* 软中断创建时的初始值     */
    UINT32        uwNumOfMsg;           /* 软中断未接收的消息数     */
    LIST_OBJECT_S stMsgList;            /* 软中断消息列表           */
    /* 软中断未创建时stObjList用于FreeList，创建未激活时为NULL，激活后用于ReadyList */
    LIST_OBJECT_S stObjList;
    /* 软中断触发级别,只有高于该优先级和自身优先级的软中断才能抢占 */
    SWI_PRIOR_T   usPriLevel;
    UINT16        usReserved;
    UINT32        uwSwiPid;
#if  (OS_HAVE_COPROCESSOR1 == YES) /*仅用于Tensilica*/
    VOID         *pCpSaveAreaA;         /* point to context buffer A of coprocessor1 */
    VOID         *pCpSaveAreaB;         /* point to context buffer B of coprocessor1 */
#endif
} SWI_ATTRIBUTE_S;

typedef struct tagSwiList
{
    SWI_ATTRIBUTE_S *pstList;
} SWI_LIST_S;

extern SWI_LIST_S                g_stSwiData;      /* 指向软中断控制块数组 */
extern UINT32                    g_vuwSwiRdy;      /* 软中断就绪队列，位表。若就绪，则相应位为1 */
extern SWI_ATTRIBUTE_S          *g_pstSwiActive;   /* 在软中断处理时，指向当前激活的软中断 */
//extern OS_MCSWI_ACTIVE_FUNC      g_pfnMcSwiActive;
extern LIST_OBJECT_S             g_astSwiReadyList[OS_SWI_PRIORITY_ALL];
extern SWI_HANDLE_T              g_uwIdleSwiID;
extern UINT8                     g_aucSwiNum[OS_SWI_PRIORITY_ALL];
extern SWI_PRIOR_T               g_usSwiPriorityLevel;
//extern TRACE_INT_DELETE          g_pfnTraceSwiDel;
extern SWI_NAMEADD_FUNC          g_pfnSwiNameAdd;
extern SWI_NAMEDEL_FUNC          g_pfnSwiNameDel;
extern UINT16                    g_usSwiMaxNum;        /* 最大可使用的软中断数量 */

extern SWI_PROC_FUNC        g_pfnSwiIdleEntry;

//extern UINT32 osMcSwiActNullHandler(UINT32 uwDstPid, UINT8 ucOprtType, UINT32 uwOprtNum);

extern SWI_ATTRIBUTE_S* osSwiRdyPop(UINT16 usPriority);

/*****************************************************************************
 Description : 增加就绪软中断
 Input       : pSwiCB     --- 软中断的控制块.
               usPrio     --- 软中断的优先级
 Output      : 无
 Return      : 无
 Others      : 传入pSwiCB的优先级是出于激活软中断时性能的考虑，在父函数SRE_SwiActivate中，
 pSwiCB的优先级已知，没必要在osSwiReadyAdd再获取一次pSwiCB的优先级，osSwiReadyDel函数同理
 *****************************************************************************/
OS_SEC_ALW_INLINE INLINE VOID osSwiReadyAdd(SWI_ATTRIBUTE_S *pstSwiCB, UINT16 usSwiPrio)
{
    LIST_OBJECT_S   *pstReadyList;

    if (CHECK_SWI_MULTI(usSwiPrio))
    {
        if (OS_SWI_READY & pstSwiCB->usStatus)
        {
            /* 防止重复激活后，重新排队到Ready队尾。任务Ready队列管理不会重复激活，无此问题。*/
            return;
        }

        /*创建有多个软中断,不论就绪的软中断是否有多个,都放入就绪链表*/
        pstReadyList = &(g_astSwiReadyList[usSwiPrio]);
        ListTailAdd(&(pstSwiCB->stObjList), pstReadyList);
    }
    else
    {
        /*只有一个软中断,前面创建时,已经让pstPrev指向了SCB,此时,直接置就绪位就可以了*/
    }

    SET_SWI_READY(SWI_PRIO_MASK(usSwiPrio)); //置软中断就绪位
    pstSwiCB->usStatus |= OS_SWI_READY;
    g_vuwUniFlag     |= OS_FLG_SWI_REQ;
}

/*****************************************************************************
 Description : 删除就绪的软中断
 Input       : pSwiCB     --- 就绪软中断的控制块.
               usPrio     --- 就绪软中断的优先级
 Output      : 无
 Return      : 无
 *****************************************************************************/
OS_SEC_ALW_INLINE INLINE VOID osSwiReadyDel(SWI_ATTRIBUTE_S *pstSwiCB, UINT16 usPrio)
{
    LIST_OBJECT_S   *pstReadyList;
    UINT32          uwPrioMask;

    uwPrioMask = SWI_PRIO_MASK(usPrio);
    if (CHECK_SWI_MULTI(usPrio))
    {
        /*创建有多个软中断，从优先级的就绪链表中删除*/
        pstReadyList = &(g_astSwiReadyList[usPrio]);
        ListDelete(&pstSwiCB->stObjList);
        if (ListEmpty(pstReadyList))
        {
            CLR_SWI_READY(uwPrioMask);     //清除优先级的就绪位
        }
    }
    else
    {
        CLR_SWI_READY(uwPrioMask);        //清除优先级的就绪位
    }

    pstSwiCB->usStatus &= ~OS_SWI_READY;    //清除软中断的就绪态
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_SWI_PH */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

