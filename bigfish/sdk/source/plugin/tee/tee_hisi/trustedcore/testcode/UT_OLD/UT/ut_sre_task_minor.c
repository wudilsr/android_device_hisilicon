 /**
 * @file:
 *
 * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * @description：
 */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//#include <string.h>
//#include <stdio.h>
//#include <assert.h>
#include "sre_base.h"
#include "sre_mem.h"
#include "iCunit.h"
#include "sre_task.h"
#include "sre_task.ph"
#include "sre_sys.ph"
#include "sre_sys.h"
#include "sre_hunt.h"
#include "sre_sem.h"
//#include "sre_mcsem.h"
#include "app_data_common.h"
#include "osTest.h"
#include "sre_hwi.h"
#include "sre_msg.h"

#define TST_TSK_IDLE                               (8<<SRE_GetCoreID()+g_uwIdleTaskID ) //IDle任务ID

#define TST_TSK_PRIOR_HIGH2                  OS_TSK_PRIORITY_23
#define TST_TSK_PRIOR_HIGH1                  OS_TSK_PRIORITY_24
#define TST_TSK_PRIOR_LOW1                   OS_TSK_PRIORITY_26
#define TST_TSK_PRIOR_LOW2                   OS_TSK_PRIORITY_27

#define TST_TSK_MAGIC_DATA1                                 0x12345678
#define TST_TSK_MAGIC_DATA2                                 0xabcdef01

#define TST_TSK_INVALID_ID                     0x400
#define TST_TSK_INVALID_ID2                   7

UINT32 m_uwMinorTstValue = 0;
volatile UINT32 m_uwTaskMinorID;
UINT32 m_uwHwiNumMinor = 7;

extern TSK_MOD_INFO_S     m_stTskModInfo;
EXTERN_FAR UINT32 g_uwTskMaxNum;

extern void osAppTskNumGet();
extern UINT32 osTskEntryGetNext(TSK_CB_S *pstBuf, UINT32 * puwPreIdx, TSK_CONTEXT_S *pstContext);
extern UINT32 osTskEntryGetNext(TSK_CB_S *pstBuf, UINT32 * puwPreIdx, TSK_CONTEXT_S *pstContext);
extern UINT32 uniTskPrePrioThdSet(TSK_HANDLE_T uwTaskID, TSK_PRIOR_T usPreemptPri);
extern UINT32 osTskEntryGetNext(TSK_CB_S *pstBuf, UINT32 * puwPreIdx, TSK_CONTEXT_S *pstContext);
extern UINT32  osTskEntryGet(TSK_CB_S * pstBuf, TSK_HANDLE_T uwTaskID, TSK_CONTEXT_S *pstContext);
extern VOID osTskExit(TSK_HANDLE_T uwTaskID);

OS_SEC_TEXT_UT iVOID TST_MinorTskEntry()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    m_uwMinorTstValue++;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT iVOID TST_MinorTskDelayEntry()
{
    static UINT32 s_uwDelayTicks = 0;
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    s_uwDelayTicks += 100;

    (VOID)__SRE_TaskDelay(s_uwDelayTicks);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT iUINT32 TST_MinorTskSetDataEntry()
{
    UINT32 uwTaskID;
    UINT32 uwPrivateData;
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    (VOID)__SRE_TaskSelf(&uwTaskID);
    __SRE_TaskPrivateDataSet(TST_TSK_MAGIC_DATA1);
    uwPrivateData = __SRE_TaskPrivateDataGet();
    ICUNIT_ASSERT_EQUAL(uwPrivateData, TST_TSK_MAGIC_DATA1, uwPrivateData);
    (VOID)__SRE_TaskSuspend(uwTaskID);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return SRE_OK;
}

/**
*-@test UT_sreTaskDelay_001()
*-@tspec  任务模块任务延时功能函数测试
*-@ttitle  设置在硬中断或在软中断的条件下进行任务延迟操作
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskDelay_001()
{
    UINT32 uwRet;
    UINT32 vuwUniFlag;

    vuwUniFlag = g_vuwUniFlag;

    g_vuwUniFlag = OS_FLG_HWI_ACTIVE;
    uwRet = __SRE_TaskDelay(100);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_DELAY_IN_INT, uwRet);

    g_vuwUniFlag = OS_FLG_SWI_ACTIVE;
    uwRet = __SRE_TaskDelay(100);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_DELAY_IN_INT, uwRet);

    g_vuwUniFlag = vuwUniFlag;
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDelay_002
*-@tspec  任务模块任务延时功能函数测试
*-@ttitle  设置在锁任务的状态下进行延时操作
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskDelay_002()
{
    UINT32 uwRet;
    UINT32 uwTaskID;

    (VOID)__SRE_TaskSelf(&uwTaskID);

    (VOID)__SRE_TaskLock();

    uwRet = __SRE_TaskDelay(100);
    ICUNIT_TRACK_EQUAL(uwRet, OS_ERRNO_TSK_DELAY_IN_LOCK, uwRet);

    (VOID)__SRE_TaskUnlock();
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDelay_003
*-@tspec  任务模块任务延时功能函数测试
*-@ttitle  设置输入参数为0(同一优先级队列中执行下一个任务)的分支检测
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskDelay_003()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskDelay(0);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDelay_004
*-@tspec  任务模块任务延时功能函数测试
*-@ttitle  延时成功检测
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskDelay_004_f01()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    m_uwMinorTstValue++;

        uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskDelay_004()
{
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;
    UINT32 uwRet;

    m_uwMinorTstValue = 0;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_sreTaskDelay_004_f01;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelay(1);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(m_uwMinorTstValue, 1, m_uwMinorTstValue);

    m_uwMinorTstValue = 0;

}

/**
*-@test UT_sreTaskDelay_004
*-@tspec  任务模块任务延时功能函数测试
*-@ttitle  延时0成功检测
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskDelay_005_f01()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    m_uwMinorTstValue++;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskDelay_005()
{
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;
    UINT32 uwRet;

    m_uwMinorTstValue = 0;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_sreTaskDelay_005_f01;
    stInitParam.usTaskPrio   = OS_TSK_PRIORITY_25;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelay(0);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(m_uwMinorTstValue, 1, m_uwMinorTstValue);

    m_uwMinorTstValue = 0;

}

/**
*-@test UT_sreTaskIDCheck_001
*-@tspec  任务模块检查任务ID是否合法功能函数测试
*-@ttitle  设置任务ID校验函数输入参数非法
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskIDCheck_001()
{
    BOOL bRet;

    bRet = SRE_TaskIDCheck(TST_TSK_INVALID_ID);
    ICUNIT_ASSERT_EQUAL(bRet, FALSE, bRet);

    bRet = SRE_TaskIDCheck(TST_TSK_INVALID_ID2);
    ICUNIT_ASSERT_EQUAL(bRet, FALSE, bRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskIDCheck_002
*-@tspec  任务模块检查任务ID是否合法功能函数测试
*-@ttitle  任务删除之后校验该任务ID
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskIDCheck_002()
{
    BOOL bRet;
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    bRet = SRE_TaskIDCheck(uwTaskID);
    ICUNIT_ASSERT_EQUAL(bRet, FALSE, bRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskIDCheck_003
*-@tspec  任务模块检查任务ID是否合法功能函数测试
*-@ttitle  校验当前任务ID
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskIDCheck_003()
{
    BOOL bRet;
    UINT32 uwRet;
    UINT32 uwTaskID;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    bRet = SRE_TaskIDCheck(uwTaskID);
    ICUNIT_ASSERT_EQUAL(bRet, TRUE, bRet);

    bRet = SRE_TaskIDCheck(g_uwTskBaseID + g_uwTskMaxNum);
    ICUNIT_ASSERT_EQUAL(bRet, FALSE, bRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskStatusGet_001
*-@tspec  任务模块获取指定任务的状态信息功能函数测试
*-@ttitle  设置获取指定任务状态信息输入参数非法(无效的任务ID)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskStatusGet_001()
{
    TSK_STATUS_T usStatus;

    usStatus = __SRE_TaskStatusGet(TST_TSK_INVALID_ID);
    ICUNIT_ASSERT_EQUAL(usStatus, (TSK_STATUS_T)OS_INVALID, usStatus);

    usStatus = __SRE_TaskStatusGet(TST_TSK_INVALID_ID2);
    ICUNIT_ASSERT_EQUAL(usStatus, (TSK_STATUS_T)OS_INVALID, usStatus);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskStatusGet_002
*-@tspec  任务模块获取指定任务的状态信息功能函数测试
*-@ttitle  在任务删除之后获取该任务的状态信息
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskStatusGet_002()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_STATUS_T usStatus;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usStatus  = __SRE_TaskStatusGet(uwTaskID);
    usStatus &= OS_TSK_UNUSED;
    ICUNIT_ASSERT_NOT_EQUAL(usStatus, 0, usStatus);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskStatusGet_003
*-@tspec  任务模块获取指定任务的状态信息功能函数测试
*-@ttitle  获取当前任务的状态信息
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskStatusGet_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_STATUS_T usStatus;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usStatus  = __SRE_TaskStatusGet(uwTaskID);
    usStatus &= OS_TSK_RUNNING;
    ICUNIT_ASSERT_NOT_EQUAL(usStatus, 0, usStatus);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskStatusGet_004
*-@tspec  任务模块获取指定任务的状态信息功能函数测试
*-@ttitle  获取挂起的任务的状态信息，查看是否是任务挂起
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskStatusGet_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_STATUS_T usStatus;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usStatus  = __SRE_TaskStatusGet(uwTaskID);
    usStatus &= OS_TSK_SUSPEND;
    ICUNIT_ASSERT_NOT_EQUAL(usStatus, 0, usStatus);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskStatusGet_005
*-@tspec  任务模块获取指定任务的状态信息功能函数测试
*-@ttitle  获取任务延时的任务的状态信息，查看是否是任务延时。
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskStatusGet_005()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_STATUS_T usStatus;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskDelayEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usStatus  = __SRE_TaskStatusGet(uwTaskID);
    usStatus &= OS_TSK_DELAY;
    ICUNIT_ASSERT_NOT_EQUAL(usStatus, 0, usStatus);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskInfoGet_001
*-@tspec  任务模块获取指定任务信息功能函数测试
*-@ttitle  设置获取任务信息的函数的输入参数非法(空指针)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskInfoGet_001()
{
    UINT32 uwRet;
    UINT32 uwTaskID;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskInfoGet(uwTaskID, NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskInfoGet_002
*-@tspec  任务模块获取指定任务信息功能函数测试
*-@ttitle  设置获取任务信息的函数的输入参数非法(无效的任务ID)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskInfoGet_002()
{
    UINT32 uwRet;
    TSK_INFO_S stTskInfo;

    uwRet = __SRE_TaskInfoGet(TST_TSK_INVALID_ID, &stTskInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    uwRet = __SRE_TaskInfoGet(TST_TSK_INVALID_ID2, &stTskInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskInfoGet_003
*-@tspec  任务模块获取指定任务信息功能函数测试
*-@ttitle  获取删除之后的任务的任务信息，查看是否是任务未创建
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskInfoGet_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INFO_S stTskInfo;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));
    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet  = __SRE_TaskInfoGet(uwTaskID, &stTskInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskInfoGet_004
*-@tspec  任务模块获取指定任务信息功能函数测试
*-@ttitle  获取任务信息，查看是否和设置的任务信息相同
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskInfoGet_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INFO_S stTskInfo;
    TSK_STATUS_T usStatus;
    TSK_INIT_PARAM_S stInitParam;

    memset(&stInitParam, 0, sizeof(TSK_INIT_PARAM_S));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskInfoGet(uwTaskID, &stTskInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uart_printf("\ntask pc is 0x%x\n", stTskInfo.uwPC);
    uart_printf("task sp is 0x%x\n", stTskInfo.uwSP);
    usStatus  = __SRE_TaskStatusGet(uwTaskID);

    ICUNIT_ASSERT_EQUAL(stTskInfo.uwPC, (UINT32)osTskExit, stTskInfo.uwPC);
    ICUNIT_ASSERT_EQUAL(stTskInfo.usTaskPrio, TST_TSK_PRIOR_LOW1, stTskInfo.usTaskPrio);
    ICUNIT_ASSERT_EQUAL(stTskInfo.uwStackSize, m_stTskModInfo.uwDefaultSize, stTskInfo.uwStackSize);
    ICUNIT_ASSERT_EQUAL(stTskInfo.uwNumOfMsg, 0, stTskInfo.uwNumOfMsg);
    ICUNIT_ASSERT_STRING_EQUAL(&stTskInfo.acName[0], "TstTask10", &stTskInfo.acName[0]);
    ICUNIT_ASSERT_EQUAL(stTskInfo.usTaskStatus, usStatus, stTskInfo.usTaskStatus);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskInfoGet_005
*-@tspec  任务模块获取指定任务信息功能函数测试
*-@ttitle  获取快速切换的任务sp和pc
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskInfoGet_005_f01()
{
    UINT32 uwRet;
    TSK_INFO_S stTskInfo;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskInfoGet(g_TestTskHandle, &stTskInfo);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uart_printf("\ntask pc is 0x%x\n", stTskInfo.uwPC);
    uart_printf("task sp is 0x%x\n", stTskInfo.uwSP);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT iUINT32 UT_sreTaskInfoGet_005()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_STATUS_T usStatus;
    TSK_INIT_PARAM_S stInitParam;

    memset(&stInitParam, 0, sizeof(TSK_INIT_PARAM_S));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_sreTaskInfoGet_005_f01;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0x600;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskInfoGet_005
*-@tspec  任务模块获取指定任务信息功能函数测试
*-@ttitle  获取被中断打断的任务sp和pc
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskInfoGet_006_f01()
{
    UINT32 uwRet;
    UINT32 uwTaskPID;
    uwRet = __SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), m_uwHwiNumMinor);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

volatile UINT32 guw_testGet006 = 0;

OS_SEC_TEXT_UT VOID UT_sreTaskInfoGet_006_f02()
{
    UINT32 uwRet;
    TSK_INFO_S stTskInfo;

    uwRet = __SRE_TaskInfoGet(m_uwTaskMinorID, &stTskInfo);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uart_printf("\ntask pc is 0x%x\n", stTskInfo.uwPC);
    uart_printf("task sp is 0x%x\n", stTskInfo.uwSP);

    guw_testGet006++;
}

OS_SEC_TEXT_UT iUINT32 UT_sreTaskInfoGet_006()
{
    UINT32 uwRet;
    TSK_STATUS_T usStatus;
    TSK_INIT_PARAM_S stInitParam;
    UINT32 uwHwiMode;
    UINTPTR uvIER;

    uwHwiMode = OS_HWI_MODE_ENGROSS;
    //uwRet = SRE_HwiSetAttr(m_uwHwiNumMinor, 0, uwHwiMode);
    //ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK, uwRet);
    uwRet = __SRE_HwiCreate(m_uwHwiNumMinor,0xa0,IT_HWI_SECURE_MODE, UT_sreTaskInfoGet_006_f02, m_uwHwiNumMinor);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet, EXIT1);
    uvIER = __SRE_HwiEnable(m_uwHwiNumMinor);

    memset(&stInitParam, 0, sizeof(TSK_INIT_PARAM_S));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_sreTaskInfoGet_006_f01;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0x600;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&m_uwTaskMinorID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    while(guw_testGet006 == 0)
    {
        uwRet++;
    }

EXIT:
    //(VOID)SRE_HwiRestore(m_uwHwiNumMinor, uvIER);
    uwRet = __SRE_HwiDelete(m_uwHwiNumMinor);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return ICUNIT_SUCCESS;

EXIT1:
    uwRet = __SRE_HwiDelete(m_uwHwiNumMinor);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskContextGet_001
*-@tspec  任务模块获取指定任务的上下文信息功能函数测试
*-@ttitle  设置获取指定任务的上下文参数非法(空指针)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskContextGet_001()
{
    UINT32 uwRet;
    UINT32 uwTaskID;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskContextGet(uwTaskID, NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskContextGet_002
*-@tspec  任务模块获取指定任务的上下文信息功能函数测试
*-@ttitle  设置获取指定任务的上下文参数非法(无效的任务ID)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskContextGet_002()
{
    UINT32 uwRet;
    TSK_CONTEXT_S stTskContext;

    uwRet = SRE_TaskContextGet(TST_TSK_INVALID_ID, &stTskContext);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    uwRet = SRE_TaskContextGet(TST_TSK_INVALID_ID2, &stTskContext);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskContextGet_003
*-@tspec  任务模块获取指定任务的上下文信息功能函数测试
*-@ttitle  设置获取已删除的任务的上下文，查看是否返回任务未创建
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskContextGet_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_CONTEXT_S stTskContext;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet  = SRE_TaskContextGet(uwTaskID, &stTskContext);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskContextGet_004
*-@tspec  任务模块获取指定任务的上下文信息功能函数测试
*-@ttitle  创建一个任务，获取该任务的上下文，查看是否正确(新创建任务)
*-@tprecon
*-@tbrief
*-@texpect
1、获取成功
2、打印结果与cda解析结果一致
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskContextGet_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_CONTEXT_S stTskContext;
    TSK_INIT_PARAM_S stInitParam;
    UINT32 uwLoop;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet  = SRE_TaskContextGet(uwTaskID, &stTskContext);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    if (SRE_GetCoreID() == SRE_GetMasterCore())
    {
        uart_printf("\nnew task:\n");
        uart_printf("pc = 0x%x\n", stTskContext.uwPC);
        uart_printf("ps = 0x%x\n", stTskContext.uwPS);
        uart_printf("lbeg = 0x%x\n", stTskContext.uwLBEG);
        uart_printf("lend = 0x%x\n", stTskContext.uwLEND);
        uart_printf("lcount = 0x%x\n", stTskContext.uwLCOUNT);
        uart_printf("sar = 0x%x\n", stTskContext.uwSAR);

        for (uwLoop = 0; uwLoop < 16; uwLoop++)
        {
            uart_printf("a[%d] = 0x%x\n", uwLoop, stTskContext.auwA[uwLoop]);
        }
    }

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskContextGet_005
*-@tspec  任务模块获取指定任务的上下文信息功能函数测试
*-@ttitle  获取当前任务的上下文，查看是否正确
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskContextGet_005()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_CONTEXT_S stTskContext;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet  = SRE_TaskContextGet(uwTaskID, &stTskContext);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskContextGet_006
*-@tspec  任务模块获取指定任务的上下文信息功能函数测试
*-@ttitle  获取测试任务的上下文，查看结果是否与CDA解析一致(快速切换)
*-@tprecon
*-@tbrief
*-@texpect
1、获取成功
2、打印结果与cda解析结果一致
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskContextGet_006_f01()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwTaskID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}
OS_SEC_TEXT_UT iUINT32 UT_sreTaskContextGet_006()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_CONTEXT_S stTskContext;
    TSK_INIT_PARAM_S stInitParam;
    UINT32 uwLoop;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_sreTaskContextGet_006_f01;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet  = SRE_TaskContextGet(uwTaskID, &stTskContext);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    if (SRE_GetCoreID() == SRE_GetMasterCore())
    {
        uart_printf("\nnew task:\n");
        uart_printf("pc = 0x%x\n", stTskContext.uwPC);
        uart_printf("ps = 0x%x\n", stTskContext.uwPS);
        uart_printf("lbeg = 0x%x\n", stTskContext.uwLBEG);
        uart_printf("lend = 0x%x\n", stTskContext.uwLEND);
        uart_printf("lcount = 0x%x\n", stTskContext.uwLCOUNT);
        uart_printf("sar = 0x%x\n", stTskContext.uwSAR);

        for (uwLoop = 0; uwLoop < 16; uwLoop++)
        {
            uart_printf("a[%d] = 0x%x\n", uwLoop, stTskContext.auwA[uwLoop]);
        }
    }

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;

}

/**
*-@test UT_sreTaskPrivateDataGet_001
*-@tspec  任务模块获取当前任务私有数据功能函数测试
*-@ttitle  设置当前任务的私有数据，然后获取当前任务的私有数据，
查看是否相等。
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPrivateDataGet_001()
{
    UINT32 uwPrivateData;

    __SRE_TaskPrivateDataSet(TST_TSK_MAGIC_DATA1);
    uwPrivateData = __SRE_TaskPrivateDataGet();
    ICUNIT_ASSERT_EQUAL(uwPrivateData, TST_TSK_MAGIC_DATA1, uwPrivateData);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPrivateDataGet_002
*-@tspec  任务模块获取当前任务私有数据功能函数测试
*-@ttitle  设置当前任务的私有数据，然后创建新的任务，再获取当前任务
私有数据，查看是否相等。
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPrivateDataGet_002()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 uwPrivateData;
    TSK_INIT_PARAM_S stInitParam;

    __SRE_TaskPrivateDataSet(TST_TSK_MAGIC_DATA2);

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskSetDataEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwPrivateData = __SRE_TaskPrivateDataGet();
    ICUNIT_ASSERT_EQUAL(uwPrivateData, TST_TSK_MAGIC_DATA2, uwPrivateData);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPriorityGet_001
*-@tspec  任务模块获取当前指定任务优先级函数功能测试
*-@ttitle  设置获取指定任务优先级函数输入参数非法
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPriorityGet_001()
{
    TSK_PRIOR_T usTskPrior;

    usTskPrior = __SRE_TaskPriorityGet(TST_TSK_INVALID_ID);
    ICUNIT_ASSERT_EQUAL(usTskPrior, (TSK_PRIOR_T)OS_INVALID, usTskPrior);

    usTskPrior = __SRE_TaskPriorityGet(TST_TSK_INVALID_ID2);
    ICUNIT_ASSERT_EQUAL(usTskPrior, (TSK_PRIOR_T)OS_INVALID, usTskPrior);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPriorityGet_002
*-@tspec  任务模块获取当前指定任务优先级函数功能测试
*-@ttitle  设置获取已经删除的任务的优先级，查看是否返回无效
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPriorityGet_002()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_PRIOR_T usTskPrior;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usTskPrior = __SRE_TaskPriorityGet(uwTaskID);
    ICUNIT_ASSERT_EQUAL(usTskPrior, (TSK_PRIOR_T)OS_INVALID, usTskPrior);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPrioritySet_001
*-@tspec  任务模块设置指定任务的优先级功能测试
*-@ttitle  设置指定任务优先级输入参数非法(任务ID无效)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPrioritySet_001()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskPrioritySet(TST_TSK_INVALID_ID, TST_TSK_PRIOR_LOW1);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    uwRet = __SRE_TaskPrioritySet(TST_TSK_INVALID_ID2, TST_TSK_PRIOR_LOW1);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPrioritySet_002
*-@tspec  任务模块设置指定任务的优先级功能测试
*-@ttitle  设置IDLE任务的优先级
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPrioritySet_002()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskPrioritySet(TST_TSK_IDLE, TST_TSK_PRIOR_LOW1);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPrioritySet_003
*-@tspec  任务模块设置指定任务的优先级功能测试
*-@ttitle  设定指定任务的优先级输入参数非法(任务优先级无效)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPrioritySet_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskPrioritySet(uwTaskID, OS_TSK_NUM_OF_PRIORITIES);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PRIOR_ERROR, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPrioritySet_004
*-@tspec  任务模块设置指定任务的优先级功能测试
*-@ttitle  设置已删除的任务的优先级，查看是否返回该任务未创建
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPrioritySet_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskPrioritySet(uwTaskID, TST_TSK_PRIOR_LOW2);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPrioritySet_005
*-@tspec  任务模块设置指定任务的优先级功能测试
*-@ttitle  设置任务的优先级之后查看该任务的优先级，是否设置正确
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPrioritySet_005()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_PRIOR_T usTskPrior;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskPrioritySet(uwTaskID, TST_TSK_PRIOR_HIGH1);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usTskPrior = __SRE_TaskPriorityGet(uwTaskID);
    ICUNIT_ASSERT_EQUAL(usTskPrior, TST_TSK_PRIOR_HIGH1, usTskPrior);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return SRE_OK;
}

/**
*-@test UT_sreTaskPrioritySet_006
*-@tspec  任务模块设置指定任务的优先级功能测试
*-@ttitle  把最低优先级的任务设置成最高优先级的任务，查看是否
设置成功
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPrioritySet_006()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    m_uwMinorTstValue = 0;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskPrioritySet(uwTaskID, TST_TSK_PRIOR_HIGH1);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    ICUNIT_ASSERT_EQUAL(m_uwMinorTstValue, 1, m_uwMinorTstValue);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskYield_001
*-@tspec 任务模块调整指定优先级任务调度顺序功能函数测试
*-@ttitle  设置指定优先级任务调度顺序函数的任务ID非法
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskYield_001()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskYield(OS_TSK_NUM_OF_PRIORITIES, OS_TSK_NULL_ID, NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PRIOR_ERROR, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskYield_002
*-@tspec  任务模块调整指定优先级任务调度顺序功能函数测试
*-@ttitle  连续两次设定任务调度ID非法
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskYield_002()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskYield(TST_TSK_PRIOR_LOW1, TST_TSK_INVALID_ID, NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    uwRet = __SRE_TaskYield(TST_TSK_PRIOR_LOW1, TST_TSK_INVALID_ID2, NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskYield_003
*-@tspec  任务模块调整指定优先级任务调度顺序功能函数测试
*-@ttitle  同优先级中只有一个任务，查看是否可以进行调度
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskYield_003()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskYield(TST_TSK_PRIOR_HIGH1, OS_TSK_NULL_ID, NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskYield_004
*-@tspec  任务模块调整指定优先级任务调度顺序功能函数测试
*-@ttitle  优先级任务调度优先级队列中第一个就绪任务调整至队尾
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskYield_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 uwCurrID;
    UINT32 uwYieldID;
    TSK_PRIOR_T usTskPrior;
    TSK_INIT_PARAM_S stInitParam;

    m_uwMinorTstValue = 0;

    uwRet = __SRE_TaskSelf(&uwCurrID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usTskPrior = __SRE_TaskPriorityGet(uwCurrID);

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = usTskPrior;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskYield(usTskPrior, OS_TSK_NULL_ID, &uwYieldID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    ICUNIT_ASSERT_EQUAL(uwYieldID, uwTaskID, uwYieldID);
    ICUNIT_ASSERT_EQUAL(m_uwMinorTstValue, 1, m_uwMinorTstValue);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskYield_005
*-@tspec  任务模块调整指定优先级任务调度顺序功能函数测试
*-@ttitle  创建新任务调度到优先级队列的队首，查看是否成功
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskYield_005()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 uwCurrID;
    UINT32 uwYieldID;
    TSK_PRIOR_T usTskPrior;
    TSK_INIT_PARAM_S stInitParam;

    m_uwMinorTstValue = 0;

    uwRet = __SRE_TaskSelf(&uwCurrID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usTskPrior = __SRE_TaskPriorityGet(uwCurrID);

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = usTskPrior;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskYield(usTskPrior, uwTaskID, &uwYieldID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    ICUNIT_ASSERT_EQUAL(uwYieldID, uwTaskID, uwYieldID);
    ICUNIT_ASSERT_EQUAL(m_uwMinorTstValue, 1, m_uwMinorTstValue);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskYield_006
*-@tspec  任务模块调整指定优先级任务调度顺序功能函数测试
*-@ttitle  挂起任务，查看是否可以进行指定优先级任务调度
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskYield_006()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 uwCurrID;
    UINT32 uwNextID;
    UINT32 uwYieldID;
    TSK_PRIOR_T usTskPrior;
    TSK_INIT_PARAM_S stInitParam;

    uwRet = __SRE_TaskSelf(&uwCurrID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    usTskPrior = __SRE_TaskPriorityGet(uwCurrID);

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = usTskPrior;
    stInitParam.uwStackSize  = 0x400;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_MinorTskEntry;
    stInitParam.usTaskPrio   = usTskPrior;
    stInitParam.uwStackSize  = 0x400;
    stInitParam.pcName       = "TstTask11";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwNextID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwNextID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskYield(usTskPrior, uwNextID, &uwYieldID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_YIELD_INVALID_TASK, uwRet);

    ICUNIT_ASSERT_EQUAL(uwYieldID, uwNextID, uwYieldID);

    uwRet = __SRE_TaskDelete(uwNextID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPrioritySet_007
*-@tspec  任务模块设置指定任务的优先级功能测试
*-@ttitle  设置Idle任务的优先级
设置成功
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT2_UT iUINT32 UT_sreTaskPrioritySet_007()
{
    UINT32 uwRet;
    UINT32 uwTaskID;

    uwRet = __SRE_TaskPrioritySet(g_uwIdleTaskID, TST_TSK_PRIOR_HIGH1);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_OPERATE_IDLE, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPendSemGet_001
*-@tspec  获取任务的PEND状态及PEND的信号量
*-@ttitle  空指针
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPendSemGet_001()
{
    UINT32 uwRet;
    UINT16 usSemId;
    UINT16 usPendState;

    uwRet = __SRE_TaskPendSemGet(0, 0, &usPendState);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);

    uwRet = __SRE_TaskPendSemGet(0, &usSemId, 0);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPendSemGet_002
*-@tspec  获取任务的PEND状态及PEND的信号量
*-@ttitle  任务PID非法
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPendSemGet_002()
{
    UINT32 uwRet;
    UINT16 usSemId;
    UINT16 usPendState;

    uwRet = __SRE_TaskPendSemGet(g_uwTskMaxNum, &usSemId, &usPendState);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    uwRet = __SRE_TaskPendSemGet(COMPOSE_PID(SRE_GetCoreID()+1,0), &usSemId, &usPendState);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPendSemGet_003
*-@tspec  获取任务的PEND状态及PEND的信号量
*-@ttitle  任务未创建
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskPendSemGet_003_tsk(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPendSemGet_003()
{
    UINT32 uwRet;
    UINT16 usSemId;
    UINT16 usPendState;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskPendSemGet_003_tsk, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    TSK_HANDLE_T uwTaskPID;

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);  //任务自删除
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskPendSemGet(uwTaskPID, &usSemId, &usPendState);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPendSemGet_004
*-@tspec  获取任务的PEND状态及PEND的信号量
*-@ttitle  任务未被信号量阻塞
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskPendSemGet_004_tsk(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet;
    UINT16 usSemId;
    UINT16 usPendState;
    TSK_HANDLE_T uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskPendSemGet(uwTaskPID, &usSemId, &usPendState);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_TRACK_EQUAL(usSemId, (UINT16)OS_INVALID, usSemId);
    ICUNIT_TRACK_EQUAL(usPendState, 0, usPendState);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPendSemGet_004()
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskPendSemGet_004_tsk, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    TSK_HANDLE_T uwTaskPID;

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);  //任务自删除
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskPendSemGet_005
*-@tspec  获取任务的PEND状态及PEND的信号量
*-@ttitle  任务阻塞于快速信号量
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskPendSemGet_005_tsk(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    __SRE_FsemPend(1);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}
OS_SEC_TEXT_UT iUINT32 UT_sreTaskPendSemGet_005()
{
    UINT32 uwRet;
    UINT16 usSemId;
    UINT16 usPendState;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskPendSemGet_005_tsk, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    TSK_HANDLE_T uwTaskPID = (UINT32)-1;

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskPendSemGet(uwTaskPID, &usSemId, &usPendState);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(usSemId, (UINT16)OS_INVALID, usSemId, EXIT);
    ICUNIT_GOTO_EQUAL(usPendState, OS_TSK_FSEM_PEND, usPendState, EXIT);

EXIT:
    if (uwTaskPID != (UINT32)-1) (VOID)__SRE_TaskDelete(uwTaskPID);
    return ICUNIT_SUCCESS;
}


/**
*-@test UT_sreTaskPendSemGet_006
*-@tspec  获取任务的PEND状态及PEND的信号量
*-@ttitle  任务阻塞于信号量
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskPendSemGet_006_tsk(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskPendSemGet_006()
{
    UINT32 uwRet;
    UINT16 usSemId;
    UINT16 usPendState;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskPendSemGet_006_tsk, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    TSK_HANDLE_T uwTaskPID   = (UINT32)-1;
    SEM_HANDLE_T usSemHandle = (UINT16)-1;

    uwRet = __SRE_SemCreate(0, &usSemHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitParam.auwArgs[0] = usSemHandle;
    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskPendSemGet(uwTaskPID, &usSemId, &usPendState);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(usSemId, usSemHandle, usSemId, EXIT);
    ICUNIT_GOTO_EQUAL(usPendState, OS_TSK_PEND, usPendState, EXIT);

EXIT:
    if (usSemHandle != (UINT16)-1) __SRE_SemDelete(usSemHandle);
    if (uwTaskPID   != (UINT32)-1) __SRE_TaskDelete(uwTaskPID);
    return ICUNIT_SUCCESS;
}
#if 0
/**
*-@test UT_sreTaskPendSemGet_007
*-@tspec  获取任务的PEND状态及PEND的信号量
*-@ttitle  任务阻塞于信号量
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskPendSemGet_007_tsk(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    SRE_McSemPend(uwParam1, OS_WAIT_FOREVER);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskPendSemGet_007()
{
    UINT32 uwRet;
    UINT16 usSemId;
    UINT16 usPendState;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskPendSemGet_007_tsk, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    TSK_HANDLE_T   uwTaskPID   = (UINT32)-1;
    MCSEM_HANDLE_T usSemHandle = (UINT16)-1;

    uwRet = SRE_McSemCreate(0, 0, &usSemHandle);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitParam.auwArgs[0] = usSemHandle;
    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskPendSemGet(uwTaskPID, &usSemId, &usPendState);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(usSemId, usSemHandle, usSemId, EXIT);
    ICUNIT_GOTO_EQUAL(usPendState, OS_TSK_MCSEM_PEND, usPendState, EXIT);

EXIT:
    if (usSemHandle != (UINT16)-1) SRE_McSemDelete(usSemHandle);
    if (uwTaskPID   != (UINT32)-1) __SRE_TaskDelete(uwTaskPID);
    return ICUNIT_SUCCESS;
}
#endif
/**
*-@test  UT_sreTaskMsgNumGet
*-@tspec  任务消息获取接口测试
*-@ttitle  任务存在未接收消息，获取未接收消息数是否正确
*-@tprecon  任务模块打开
*-@tbrief
1.锁任务调度
2.创建高优先级任务A
3.向高优先级任务队列0发送长消息、短消息、无消息体消息；向高优先级任务队列1发送无消息体消息
4.解锁任务调度
5.高优先级任务处理函数调用消息获取接口
*-@texpect
1.上述操作均成功
2.获取消息队列数正确
*-@tprior  1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskMsgNumGet_f01()
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    m_uwMinorTstValue++;

    uwRet = __SRE_TaskMsgNumGet(0);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, 3, uwRet);

    uwRet = __SRE_TaskMsgNumGet(1);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, 1, uwRet);

    uwRet = __SRE_TaskMsgNumGet(2);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, 0, uwRet);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskMsgNumGet()
{
    UINT32           uwRet;
    TSK_HANDLE_T     uwTaskPID;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskMsgNumGet_f01, TST_TSK_PRIOR_HIGH1, 3, {0}, 0x500, "TaskA", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    UINT16 usSize;
    UINT32 uwMsgHandle;
    UINT32 uwMsgID;

    m_uwMinorTstValue = 0;

    __SRE_TaskLock();

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    usSize = 20;   //长消息
    uwMsgHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_FSC_PT, usSize, 0);
    ICUNIT_GOTO_NOT_EQUAL(uwMsgHandle, OS_MSG_CREATE_ERR, uwMsgHandle, EXIT);

    uwMsgID = 1;
    uwRet = __SRE_MsgQSend(uwMsgHandle, uwMsgID, uwTaskPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    usSize = 6;   //82短消息，8108长消息
    uwMsgHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_FSC_PT, usSize, 0);
    ICUNIT_GOTO_NOT_EQUAL(uwMsgHandle, OS_MSG_CREATE_ERR, uwMsgHandle, EXIT);

    uwMsgID = 2;
    uwRet = __SRE_MsgQSend(uwMsgHandle, uwMsgID, uwTaskPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwMsgID = 2;
    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTaskPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwMsgID = 2;
    uwRet = SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTaskPID, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    __SRE_TaskUnlock();

    ICUNIT_ASSERT_EQUAL(m_uwMinorTstValue, 1, m_uwMinorTstValue);
    return SRE_OK;
}

OS_SEC_TEXT_UT VOID UT_sre_task_minor(VOID)
{
    iUINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_sre_task_minor");

    TEST_ADD_CASE(UT_sreTaskDelay_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskDelay_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskDelay_003, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskIDCheck_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskIDCheck_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskIDCheck_003, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskStatusGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskStatusGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskStatusGet_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskStatusGet_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskStatusGet_005, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskInfoGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskInfoGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskInfoGet_003, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskInfoGet_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskInfoGet_005, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskInfoGet_006, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskContextGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskContextGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskContextGet_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskContextGet_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskContextGet_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskContextGet_006, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskPrivateDataGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskPrivateDataGet_002, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskPriorityGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskPriorityGet_002, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskPrioritySet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskPrioritySet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskPrioritySet_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskPrioritySet_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskPrioritySet_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskPrioritySet_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskPrioritySet_007, uiSuiteId, Label_RUN);

    //TEST_ADD_CASE(UT_sreTaskYield_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskYield_002, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskYield_003, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskYield_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskYield_005, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskYield_006, uiSuiteId, Label_RUN);

    //TEST_ADD_CASE(UT_sreTaskPendSemGet_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskPendSemGet_002, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskPendSemGet_003, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskPendSemGet_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskPendSemGet_005, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskPendSemGet_006, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskPendSemGet_007, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskMsgNumGet, uiSuiteId, Label_RUN);

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            







                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            







                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            







                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           