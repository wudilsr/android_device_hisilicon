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

#include "sre_base.h"
#include "sre_mem.h"
#include "iCunit.h"
#include "sre_task.h"
#include "sre_task.ph"
#include "sre_sys.ph"
#include "sre_sys.h"
#include "sre_buildef.h"
#include "osTest.h"
#include "sre_swi.h"
#include "app_data_common.h"
#include "sre_hwi.h"

#define TST_TSK_PRIOR_HIGH1                  OS_TSK_PRIORITY_24

UINT32 m_uwTstValue;
extern TSK_HANDLE_T g_TestTskHandle;

OS_SEC_TEXT_UT VOID TST_TskEntry()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    m_uwTstValue++;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

/**
*-@test UT_sreTaskLock_001
*-@tspec 任务模块锁任务调度函数功能测试
*-@ttitle  锁定任务查看创建任务之后任务是否可运行
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskLock_001()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    __SRE_TaskLock();

    m_uwTstValue = 0;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));
    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_TskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    __SRE_TestTaskSchedule();

    ICUNIT_GOTO_EQUAL(m_uwTstValue, 0, m_uwTstValue, EXIT);

EXIT:
    __SRE_TaskUnlock();
    __SRE_TaskDelete(uwTaskID);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskLock_002
*-@tspec  任务模块锁任务调度函数功能测试
*-@ttitle  锁定任务创建任务解锁之后调度任务，查看任务是否可运行
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskLock_002()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    __SRE_TaskLock();

    m_uwTstValue = 0;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));
    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_TskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    __SRE_TaskUnlock();
    __SRE_TestTaskSchedule();
    ICUNIT_GOTO_EQUAL(m_uwTstValue, 1, m_uwTstValue, EXIT);

EXIT:
    __SRE_TaskUnlock();
    __SRE_TaskDelete(uwTaskID);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskLock_003
*-@tspec  任务模块锁任务调度函数功能测试
*-@ttitle  两次锁任务，解一次锁查看任务是否可运行，解第二次锁查看任务
是否可运行
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskLock_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    __SRE_TaskLock();
    __SRE_TaskLock();

    m_uwTstValue = 0;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));
    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_TskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    __SRE_TaskUnlock();
    __SRE_TestTaskSchedule();
    ICUNIT_GOTO_EQUAL(m_uwTstValue, 0, m_uwTstValue, EXIT);

    __SRE_TaskUnlock();
    __SRE_TestTaskSchedule();
    ICUNIT_GOTO_EQUAL(m_uwTstValue, 1, m_uwTstValue, EXIT);

EXIT:
    __SRE_TaskUnlock();
    __SRE_TaskDelete(uwTaskID);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_SRE_TaskSelf_001
*-@tspec  任务模块获取当前任务ID功能函数测试
*-@ttitle 设置获取当前ID函数参数为空，查看是否返回错误码OS_ERRNO_TSK_PTR_NULL
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_TaskSelf_001()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskSelf(NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_SRE_TaskSelf_002
*-@tspec  任务模块获取当前任务ID功能函数测试
*-@ttitle  设置获取当前ID参数不为空，查看是否返回正确
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_TaskSelf_002()
{
    UINT32 uwRet;
    UINT32 uwTaskID;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(uwTaskID, g_TestTskHandle, uwTaskID);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_uniTskSelf_003
*-@tspec  任务模块获取当前任务ID功能函数测试
*-@ttitle  设置获取当前ID非法，查看是否返回错误码
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_TaskSelf_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINTPTR uvIntSave;
    UINT32 uwTaskPID;

    uvIntSave = __SRE_IntLock();

    uwTaskPID = g_pRunningTask->uwTaskPID;

    g_pRunningTask->uwTaskPID = 0x0000FFFF;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    g_pRunningTask->uwTaskPID = uwTaskPID;

    (VOID)__SRE_IntRestore(uvIntSave);

    return ICUNIT_SUCCESS;
}


/**
*-@test UT_osTskIdleBGD_001
*-@tspec  背景任务测试
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
TSK_HANDLE_T g_vuwTaskID;
VOID UT_osTskIdleBGD_001_func(VOID)
{
    m_uwTstValue++;

    __SRE_TaskResume(g_vuwTaskID);
    return;
}

OS_SEC_TEXT_UT UINT32 UT_osTskIdleBGD_001(VOID)
{
    UINT32 uwRet;
    UINTPTR uvIntSave;
    OS_IDLE_HOOK  pfnSysIdleHook;
    m_uwTstValue = 0;

    __SRE_TaskSelf(&g_vuwTaskID);

    pfnSysIdleHook = m_pfnSysIdleHook;

    m_pfnSysIdleHook = UT_osTskIdleBGD_001_func;

    __SRE_TaskSuspend(g_vuwTaskID);

    ICUNIT_ASSERT_NOT_EQUAL(m_uwTstValue, 0, uwRet);

    m_pfnSysIdleHook = pfnSysIdleHook;

    return ICUNIT_SUCCESS;
}

#if 0
/**
*-@test UT_SRE_TaskStackInfo_001
*-@tspec  任务堆栈信息获取接口入参合法性测试
*-@ttitle  设置结构体指针为空和合法情形，看获取结果是否正确
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_TaskStackInfo_001()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTaskPID;
    STACK_INFO_S *pstStackInfo = NULL;
    STACK_INFO_S stStackInfo;
    TSK_CB_S *pstTaskHandle;
    UINT32 uwTaskBottom;

    uwRet = SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    pstTaskHandle = GET_TCB_HANDLE(uwTaskPID);
    uwTaskBottom = TRUNCATE(((UINT32)(pstTaskHandle->uwTopOfStack) + (pstTaskHandle->uwStackSize)), OS_TSK_STACK_ADDR_ALIGN);

    uwRet = SRE_TaskStackInfoGet(uwTaskPID, pstStackInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);

    uwRet = SRE_TaskStackInfoGet(uwTaskPID, &stStackInfo);
    ICUNIT_ASSERT_EQUAL(stStackInfo.uwTop, pstTaskHandle->uwTopOfStack, stStackInfo.uwTop);
    ICUNIT_ASSERT_EQUAL(stStackInfo.uwBottom, uwTaskBottom, stStackInfo.uwBottom);
    ICUNIT_ASSERT_NOT_EQUAL(stStackInfo.uwPeakUsed, 0xFFFFFFFF, stStackInfo.uwPeakUsed);
    ICUNIT_ASSERT_EQUAL(stStackInfo.bOvf, FALSE, stStackInfo.bOvf);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_SRE_TaskStackInfo_002
*-@tspec  任务堆栈信息获取接口入参合法性测试
*-@ttitle  设置任务pid不合法的情形
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_TaskStackInfo_002()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTaskPID;
    STACK_INFO_S stStackInfo;

    uwRet = SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskStackInfoGet(uwTaskPID + g_uwTskMaxNum +1, &stStackInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_SRE_TaskStackInfo_003
*-@tspec  任务堆栈信息获取接口入参合法性测试
*-@ttitle  设置任务状态不合法的场景进行测试
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_TaskStackInfo_003()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTaskPID;
    STACK_INFO_S stStackInfo;
    TSK_CB_S *pstTaskHandle;
    UINT16 usStatus;
    UINTPTR uvIntSave;

    uvIntSave = __SRE_IntLock();

    uwRet = SRE_TaskSelf(&uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pstTaskHandle = GET_TCB_HANDLE(uwTaskPID);
    usStatus = pstTaskHandle->usTaskStatus;
    pstTaskHandle->usTaskStatus = OS_TSK_UNUSED;

    uwRet = SRE_TaskStackInfoGet(uwTaskPID, &stStackInfo);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet, EXIT1);
EXIT1:
    pstTaskHandle->usTaskStatus = usStatus;
EXIT:
    __SRE_IntRestore(uvIntSave);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_SRE_TaskStackInfo_004
*-@tspec  任务堆栈信息获取接口功能测试
*-@ttitle  获取非运行任务的任务堆栈信息测试。
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_SRE_TaskStackInfo_004_f01()
{
    TSK_CB_S *pstTaskHandle;
    UINT32 uwTaskBottom;
    UINT32 uwRet;
    STACK_INFO_S stStackInfo;

    pstTaskHandle = GET_TCB_HANDLE(g_TestTskHandle);

    uwTaskBottom = TRUNCATE(((UINT32)(pstTaskHandle->uwTopOfStack) + (pstTaskHandle->uwStackSize)), OS_TSK_STACK_ADDR_ALIGN);
    uwRet = SRE_TaskStackInfoGet(g_TestTskHandle, &stStackInfo);
    ICUNIT_ASSERT_EQUAL_VOID(stStackInfo.uwTop, pstTaskHandle->uwTopOfStack, stStackInfo.uwTop);
    ICUNIT_ASSERT_EQUAL_VOID(stStackInfo.uwBottom, uwTaskBottom, stStackInfo.uwBottom);
    ICUNIT_ASSERT_NOT_EQUAL_VOID(stStackInfo.uwPeakUsed, 0xFFFFFFFF, stStackInfo.uwPeakUsed);
    ICUNIT_ASSERT_EQUAL_VOID(stStackInfo.bOvf, FALSE, stStackInfo.bOvf);

    return ;

}

OS_SEC_TEXT_UT UINT32 UT_SRE_TaskStackInfo_004()
{
    UINT32 uwRet;
    TSK_INIT_PARAM_S stInitParam;
    UINT32 uwTaskID;

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_SRE_TaskStackInfo_004_f01;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask01";
    stInitParam.usQNum       = 0;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_SRE_TaskStackInfo_005
*-@tspec  任务堆栈信息获取接口功能测试
*-@ttitle  中断中调用获取信息接口测试，修改测试任务栈顶魔术子，看是否检测到越界。
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_SRE_TaskStackInfo_005_f01(VOID)
{
    TSK_CB_S *pstTaskHandle;
    UINT32 uwTaskBottom;
    UINT32 uwRet;
    STACK_INFO_S stStackInfo;

    pstTaskHandle = GET_TCB_HANDLE(g_TestTskHandle);

    #if (YES == OS_INCLUDE_TSKMON)
    {
        (VOID)SRE_StkMonDisable();
    }
    #endif

    *(UINT32*)pstTaskHandle->uwTopOfStack = 0;

    uwTaskBottom = TRUNCATE(((UINT32)(pstTaskHandle->uwTopOfStack) + (pstTaskHandle->uwStackSize)), OS_TSK_STACK_ADDR_ALIGN);
    uwRet = SRE_TaskStackInfoGet(g_TestTskHandle, &stStackInfo);
    ICUNIT_GOTO_EQUAL(stStackInfo.uwTop, pstTaskHandle->uwTopOfStack, stStackInfo.uwTop, EXIT);
    ICUNIT_GOTO_EQUAL(stStackInfo.uwBottom, uwTaskBottom, stStackInfo.uwBottom, EXIT);
    ICUNIT_GOTO_EQUAL(stStackInfo.uwPeakUsed, 0xFFFFFFFF, stStackInfo.uwPeakUsed, EXIT);
    ICUNIT_GOTO_EQUAL(stStackInfo.bOvf, TRUE, stStackInfo.bOvf, EXIT);
EXIT:
    *(UINT32*)pstTaskHandle->uwTopOfStack = TASK_MAGIC_WORD;
    #if (YES == OS_INCLUDE_TSKMON)
    {
        (VOID)SRE_StkMonRestore();
    }
    #endif
}

OS_SEC_TEXT_UT UINT32 UT_SRE_TaskStackInfo_005(VOID)
{
    UINT32 uwRet;
    UINT32 uwHwiNum = 7;
    UINTPTR uvIER;

   // uwRet = SRE_HwiSetAttr(uwHwiNum, 0, OS_HWI_MODE_ENGROSS);
   // ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    uwRet = SRE_HwiCreate(uwHwiNum, 0xa0,IT_HWI_SECURE_MODE,(HWI_PROC_FUNC)UT_SRE_TaskStackInfo_005_f01, uwHwiNum);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    uvIER = SRE_HwiEnable(uwHwiNum);

    uwRet = SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), uwHwiNum);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:

    //(VOID)SRE_HwiRestore(uwHwiNum, uvIER);

    uwRet = SRE_HwiDelete(uwHwiNum);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}
#endif

OS_SEC_TEXT_UT VOID UT_sre_task()
{
    iUINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_sre_task");

    TEST_ADD_CASE(UT_sreTaskLock_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskLock_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskLock_003, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_TaskSelf_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_TaskSelf_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_TaskSelf_003, uiSuiteId, Label_RUN);

    //TEST_ADD_CASE(UT_osTskIdleBGD_001, uiSuiteId, Label_RUN);
#if 0
    TEST_ADD_CASE(UT_SRE_TaskStackInfo_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_TaskStackInfo_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_TaskStackInfo_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_TaskStackInfo_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_TaskStackInfo_005, uiSuiteId, Label_RUN);
#endif
Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
