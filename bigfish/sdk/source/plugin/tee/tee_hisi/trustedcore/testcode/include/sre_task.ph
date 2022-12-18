/**
* @file sre_task.ph
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* ����������ģ����ڲ�ͷ�ļ��� \n
*/

#ifndef _SRE_TASK_PH
#define _SRE_TASK_PH

#include "sre_base.h"
#include "sre_list.ph"
#include "sre_sys.ph"
#include "sre_hw.ph"
#include "sre_task.h"
#include "sre_err.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**�����л�����������Ŀǰʹ������������أ�����ջ��أ�CPUռ���ʣ�8156���¼�����ͳ�ƣ��̼߳�CPUռ���ʣ�TRACE  */
#define MAX_TSK_SWT_HOOK_NUM                                 8

/**���񴴽���������, +1: �ṩ���û�ʹ�õĹ���  */
#define MAX_TSK_CRE_HOOK_NUM                                 1

/**����ɾ����������, +1: �ṩ���û�ʹ�õĹ���  */
#define MAX_TSK_DEL_HOOK_NUM                                 1

#define OS_TSK_STACK_SIZE_ALIGN                              16
#define OS_TSK_STACK_ADDR_ALIGN                              8

#define MAX_TASK_NUM        126  //����һ��idle task���������handleΪFE��FF��ʾӲ�ж��̡߳�

#define OS_TSK_BLOCK        (OS_TSK_DELAY | OS_TSK_PEND | OS_TSK_SUSPEND | OS_TSK_FSEM_PEND | OS_TSK_MSG_PEND | OS_TSK_MCSEM_PEND)
#define TASK_MAGIC_WORD     0xAAAAAAAA

#define TSK_IDX2PID(uwTaskID)                                   ((uwTaskID) + g_uwTskBaseID)
#define TSK_GET_INDEX(uwTaskID)                                 ((uwTaskID) - g_uwTskBaseID)
#define TASK_ID_CHECK(uwTaskID)                                 OS_ASSERT_COND(TSK_GET_INDEX(uwTaskID) < g_uwTskMaxNum)

typedef struct tagMsgQHead
{
    UINT32 uwMsgNum;                /* ��Ϣ�����е���Ϣ��   */
    LIST_OBJECT_S stMsgList;        /* ��Ϣ����ͷ           */
} MSG_QHead_S;

/**
* ������ƿ�Ľṹ�嶨�塣
*
* pStackPointer��usTaskStatus��usPriority��λ�ò��ܱ䶯���������д����
*/
typedef struct tagTskCB
{
    VOID               *pStackPointer;              /* Current SP in the task. */
    TSK_STATUS_T        usTaskStatus;               /* Task flags. */
    TSK_PRIOR_T         usPriority;                 /* Priority of task. */
    UINT32              uwStackSize;                /* Total size of the stack. */
    UINT32              uwTopOfStack;               /* Top of task's stack. */
    TSK_HANDLE_T        uwTaskPID;                   /* Task ID. */
    TSK_ENTRY_FUNC      pfnTaskEntry;               /* Function ran in this task. */
    VOID               *pTaskSem;                   /* Current Sem task is pemding on. */
    INT32               swFsemCount;                /* Fast semaphore counter. */
    UINT32              auwArgs[4];                 /* Task parameters. */
#if  (OS_HAVE_COPROCESSOR1 == YES)                  /* for CP SAVE ,offset = 48 bytes*/
    VOID               *pCpSaveAreaA;               /* point to context buffer A of coprocessor1 */
    VOID               *pCpSaveAreaB;               /* point to context buffer B of coprocessor1 */
#endif
    UINT32              uwReserved;
    UINT16              usQNum;                     /* ��Ϣ������           */
    UINT16              usRecvQID;                  /* ����������Ϣ��QID    */
    UINT32              uwPrivateData;              /* Parameters in and out of the task. */
    MSG_QHead_S        *pstMsgQ;                    /* ָ����Ϣ��������     */
    LIST_OBJECT_S       stPendList;                 /* List of ready or Sem List. */
    LIST_OBJECT_S       stTimerList;                /* List of waiting for timer tasks. */
    UINT64              ullExpirationTick;          /* Value of tick to resume task. */
    VOID               *pKernelStackPointer;    /*�ں�ջ*/
    UINT32              uwKernelTopOfStack;    /*�ں�ջջ��*/
    UINT32              uwKernelBottomStack;
    UINT32              uwUsrSP;
    TSK_MEM_STRUCT_S    usMemStruct;
} TSK_CB_S;

/*�ýṹ���С����С�ڵ���OS_TSK_STACK_SIZE_ALIGN(16bytes)*/
typedef struct tagTskStackBlk
{
    UINT32 uwAddr;
    UINT32 uwSize;
    struct tagTskStackBlk *pstPrev;
    struct tagTskStackBlk *pstNext;
} TSK_STACK_BLK_S;

typedef UINT32 (* TASK_NAMEADD_FUNC)(UINT32 uwTaskID, CHAR* pcName);
typedef VOID   (* TASK_NAMEDEL_FUNC)(UINT32 uwTaskID);
typedef VOID   (* KNL_STAT_TSK_ENTRY)(UINT32 uwPidOut, UINT32 uwPidIn);
typedef UINT32 (* TSK_HOOK)();
typedef VOID   (*TSK_CORESLEEP)(VOID);
typedef VOID   (* TASK_MSGDEL_FUNC)(TSK_CB_S *pstTskCB);

/**
 * �����л�ʱ��¼ϵͳ���ٹ��Ӻ������Ͷ��塣
 */
typedef VOID (* TSK_SWITCH_TRACE_HOOK)(TSK_CB_S *pstSwitchIn, TSK_CB_S *pstSwitchOut);

extern UINT32               g_uwTskBaseID;
extern UINT32               g_uwTskMaxNum;
extern TSK_CB_S            *g_pstTskCBArray;
extern TSK_HANDLE_T         g_uwIdleTaskID;
extern UINT16      g_usUniTaskLock;

extern TSK_CB_S   *g_pRunningTask;
extern TSK_CB_S   *g_pHighestTask;
extern LIST_OBJECT_S            g_astTskReadyList[OS_TSK_NUM_OF_PRIORITIES];
extern UINT32               g_uwTskReadyListBitMap;
extern LIST_OBJECT_S            g_stTskSortedDelayList;
extern TSK_ENTRY_FUNC           g_pfnTskIdleEntry;
extern TASK_NAMEADD_FUNC        g_pfnTaskNameAdd ;  /* �����д���ɾ��ʱ���ù���            */
extern TASK_NAMEDEL_FUNC        g_pfnTaskNameDel;
extern TASK_MSGDEL_FUNC         g_pfnTaskMsgDel;

extern UINT32                   m_uwTskCreHookNum;    /*�Ѵ��������񴴽���������*/
extern TSK_CREATE_HOOK          m_pfnTskCreHook[MAX_TSK_CRE_HOOK_NUM];
extern UINT32                   m_uwTskDelHookNum;    /*�Ѵ���������ɾ����������*/
extern TSK_DELETE_HOOK          m_pfnTskDelHook[MAX_TSK_DEL_HOOK_NUM];
extern UINT32                   m_uwTskSwitchHookNum; /*�Ѵ����������л���������*/
extern TSK_SWITCH_HOOK          m_pfnTskSwitchHook[MAX_TSK_SWT_HOOK_NUM];

#define GET_TCB_PEND(ptr)           LIST_COMPONENT(ptr, TSK_CB_S, stPendList)

#define GET_TCB_HANDLE(TaskPID)      (((TSK_CB_S *)g_pstTskCBArray) + TSK_GET_INDEX(TaskPID))

#define CHECK_TSK_PID_NOIDLE(uwTaskID)       \
                (TSK_GET_INDEX(uwTaskID) >= g_uwTskMaxNum)

#define CHECK_TSK_PID(uwTaskID)       \
                (CHECK_TSK_PID_NOIDLE(uwTaskID) || ((uwTaskID) == g_uwIdleTaskID))

/*****************************************************************************
 Description : Set highest task wait for schedule.
 Input       : None
 Output      : None
 Return      : None
 *****************************************************************************/
OS_SEC_ALW_INLINE INLINE VOID osTskHighestSet(VOID)
{
    UINT32 uwRdyListIdx;
    LIST_OBJECT_S *pstReadyList;

    /* find the highest priority */
    uwRdyListIdx = osGetLMB1(g_uwTskReadyListBitMap);
    pstReadyList = &(g_astTskReadyList[uwRdyListIdx]);

    /*lint -save -e413*/
    g_pHighestTask = GET_TCB_PEND(LIST_FIRST(pstReadyList));
    /*lint -restore*/
}

extern VOID osTskReadyAdd(TSK_CB_S *pstTaskCB);
extern VOID osTskReadyDel(TSK_CB_S *pstTaskCB);
extern VOID osTskTimerAdd(TSK_CB_S *pstTaskCB, UINT32 uwTimeout);
extern VOID osTskExit(TSK_HANDLE_T uwTaskID);
extern UINT32 osTskMonSwitchProc ( UINT32 uwLastTaskID, UINT32 uwNextTaskID );
extern VOID osTaskHuntClear(VOID);/*add by w00164922*/
extern VOID osTskDeleteHook(UINT32 uwTskPid);
extern VOID osTskCreateHook(UINT32 uwTskPid);
//extern VOID osTskSchedule();
//extern VOID osTskScheduleFast();
extern VOID osTaskScan();
extern VOID osTaskSchedule();

#if (OS_HARDWARE_PLATFORM == OS_DSP170 || OS_HARDWARE_PLATFORM == OS_RISC170 || (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220))
extern VOID osTskSchedule();
extern VOID osTskScheduleFast();
#else
extern VOID osTskSchedule(VOID);
#define osTaskTrap() osSwiTrap()
#define osTskScheduleFast() osTskSchedule()
#endif

typedef VOID (* TASK_SCAN_FUNC)(VOID);

#define OS_TASK_SCAN() \
    do \
    { \
        if(NULL != g_pfnTaskScanHook) \
        { \
            g_pfnTaskScanHook(); \
        } \
    }while(0)


typedef VOID (* TASK_SCHEDULE_FUNC)(VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_TASK_PH */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

