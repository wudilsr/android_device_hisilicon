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

#include "sre_config.h"
#include "sre_fsem.h"
#include "sre_fsem.ph"
#include "sre_err.ph"
#include "sre_task.h"
#include "sre_swi.h"
#include "sre_hwi.h"
#include "sre_mem.h"
#include "sre_sys.h"
#include "sre_hunt.h"
//#include "sre_sync.h"
#include "osTest.h"
#include "app_data_common.h"

extern TSK_HANDLE_T  g_uwIdleTaskID;
extern MCFSEM_POST_FUNC g_pfnMcFsemPost;
extern CDA_INFO_S *g_pstCdaInfoAddr;
extern VOID UT_HwiTrigger(UINT32 uwIntNum);
static UINT32 g_FsemTestCount = 0;

/**
*-@test  UT_SreFsemSet01
*-@tspec  快速信号量设置
*-@ttitle 快速信号量错误码：任务句柄非法（Idle任务）
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemSet01()
{
    UINT32 uwRet;

    uwRet = __SRE_FsemSet(g_uwIdleTaskID, 1);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_TASK_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemSet02
*-@tspec  快速信号量设置
*-@ttitle 快速信号量错误码：任务句柄非法（任务未创建）
*/

OS_SEC_TEXT_UT UINT32 FsemTest_Set02_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemSet02()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 26;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Set02_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;

    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_FsemSet(uwTskHandle, 1);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_TASK_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemSet03
*-@tspec  快速信号量设置
*-@ttitle 快速信号量错误码：任务句柄非法（其他核已创建任务）
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemSet03()
{
#if (OS_SYS_CORE_RUN_NUM > 1)
    UINT32 uwRet;
    UINT32 uwPID;

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_HuntByName(OS_SYS_CORE_START + 1, UT_TEST_TSK_NAME, &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

        uwRet = __SRE_FsemSet(uwPID, 1);
        ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_TASK_INVALID, uwRet);
    }
#endif

    return SRE_OK;
}

/**
*-@test  UT_SreFsemSet04
*-@tspec  快速信号量设置
*-@ttitle 快速信号量错误码：任务句柄非法（任意ID)
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemSet04()
{
    UINT32 uwRet;

    uwRet = __SRE_FsemSet(0xabc, 1);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_TASK_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemSet04
*-@tspec  快速信号量设置
*-@ttitle 快速信号量错误码：设置计数值为非法
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Set05_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemSet05()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 26;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Set05_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;

    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_FsemSet(uwTskHandle, -1);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_FSEM_SET_NEGATIVE, uwRet,EXIT);

    uwRet = __SRE_FsemSet(uwTskHandle, 0xffffffff);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_FSEM_SET_NEGATIVE, uwRet,EXIT);

    uwRet = __SRE_FsemSet(uwTskHandle, 0x80000000);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_FSEM_SET_NEGATIVE, uwRet,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemSet04
*-@tspec  快速信号量设置
*-@ttitle 为已阻塞于快速信号量的任务设置计数值
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Set06_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_FsemPend(1);  //Pend信号量阻塞,回到测试任务
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemSet06()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 20;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Set06_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_FsemSet(uwTskHandle, 1); //该任务阻塞于快速信号量，预期失败
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_FSEM_PENDED, uwRet,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemSet07
*-@tspec  快速信号量设置
*-@ttitle 快速信号量正常功能测试
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Set07_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemSet07()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 26;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Set07_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_FsemSet(uwTskHandle, 0);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

    uwRet = __SRE_FsemSet(uwTskHandle, 0x1);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

    uwRet = __SRE_FsemSet(uwTskHandle, 0x7fffffff);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemGet01
*-@tspec  快速信号量计数值获取
*-@ttitle 快速信号量错误码：任务句柄非法（Idle任务）
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemGet01()
{
    UINT32 uwCount;

    uwCount = __SRE_FsemGet(g_uwIdleTaskID);
    ICUNIT_ASSERT_EQUAL(uwCount,OS_FSEM_COUNT_ERR, uwCount);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemGet02
*-@tspec  快速信号量计数值获取
*-@ttitle 快速信号量错误码：任务句柄非法（任务未创建）
*/

OS_SEC_TEXT_UT UINT32 FsemTest_Get02_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemGet02()
{
    UINT32 uwRet;
    UINT32 uwCount;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 26;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Get02_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwCount = __SRE_FsemGet(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwCount,OS_FSEM_TASK_NO_CREATE, uwCount);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemGet03
*-@tspec  快速信号量计数值获取
*-@ttitle 快速信号量错误码：任务句柄非法（其他核已创建任务）
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemGet03()
{
#if (OS_SYS_CORE_RUN_NUM > 1)
    UINT32 uwRet;
    UINT32 uwCount;
    UINT32 uwPID;

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_HuntByName(OS_SYS_CORE_START + 1, UT_TEST_TSK_NAME, &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

        uwCount = __SRE_FsemGet(uwPID);
        ICUNIT_ASSERT_EQUAL(uwCount,OS_FSEM_COUNT_ERR, uwCount);
    }
#endif

    return SRE_OK;
}

/**
*-@test  UT_SreFsemGet04
*-@tspec  快速信号量计数值获取
*-@ttitle 快速信号量错误码：任务句柄非法（任意ID)
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemGet04()
{
    UINT32 uwCount;

    uwCount = __SRE_FsemGet(0xabc);
    ICUNIT_ASSERT_EQUAL(uwCount,OS_FSEM_COUNT_ERR, uwCount);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemGet05
*-@tspec  快速信号量计数值获取
*-@ttitle 快速信号量正常功能测试
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Get05_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemGet05()
{
    UINT32 uwRet;
    UINT32 uwCount;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 26;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Get05_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwCount = __SRE_FsemGet(uwTskHandle);
    ICUNIT_GOTO_EQUAL(uwCount,0, uwCount,EXIT);

    uwRet = __SRE_FsemSet(uwTskHandle, 1);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

    uwCount = __SRE_FsemGet(uwTskHandle);
    ICUNIT_GOTO_EQUAL(uwCount,1, uwCount,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPend01
*-@tspec  Pend快速信号量
*-@ttitle 硬中断中Pend快速信号量
*/
OS_SEC_TEXT_UT VOID FsemTest_Pend01_Hwi_fun(UINT32 uwArg)
{
    UINT32 uwRet;
    uart_printf("FsemTest_Pend01_Hwi_fun\n");
    uwRet = __SRE_FsemPend(1);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet,OS_ERRNO_FSEM_PEND_INTERR,uwRet);
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPend01()
{
    UINT32 uwRet;
    UINT32 uwCPSR;

    //uwRet = SRE_HwiSetAttr(7, 0, OS_HWI_MODE_ENGROSS);
    // ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    //uart_printf("UT_SreFsemPend01\n");
    uwRet = __SRE_HwiCreate(7,0xa0,IT_HWI_SECURE_MODE, (HWI_PROC_FUNC)FsemTest_Pend01_Hwi_fun, 0);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    __SRE_HwiEnable(7);

    //uwCPSR = __SRE_GetCurrCPSR();
    //uart_printf("uwCPSR = 0x%x\n", uwCPSR);

    __SRE_HwiTrigger(IT_HWI_SECURE_MODE,SRE_GetCoreID(), 7);

    uwRet = __SRE_HwiDelete(7);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPend02
*-@tspec  Pend快速信号量
*-@ttitle 软中断中Pend快速信号量
*/
OS_SEC_TEXT_UT VOID UT_SreFsemPend02_Swi_fun(UINT32 uwArg)
{
    UINT32 uwRet;

    uwRet = __SRE_FsemPend(1);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet,OS_ERRNO_FSEM_PEND_INTERR,uwRet);
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPend02()
{
    UINT32 uwRet;
    UINT32 uwSwiID;
    SWI_INIT_PARA_S stInitPara;

    stInitPara.pcSwiName = "Fsem test";
    stInitPara.pfnHandler = UT_SreFsemPend02_Swi_fun;
    stInitPara.usPriority = 12;
    stInitPara.uwInitValue = 0;

    uwRet = __SRE_SwiCreate(&uwSwiID, &stInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    __SRE_SwiEnable(OS_SWI_PRIORITY_ALL);

    uwRet = __SRE_SwiActivate(uwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

EXIT:
    uwRet = __SRE_SwiDelete(uwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPend03
*-@tspec  Pend快速信号量
*-@ttitle Pend快速信号量，计数值非法
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemPend03()
{
    UINT32 uwRet;

    uwRet = __SRE_FsemPend(0);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_PEND_VAL_INVALID,uwRet);

    uwRet = __SRE_FsemPend(-1);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_PEND_VAL_INVALID,uwRet);

    uwRet = __SRE_FsemPend(0x80000000);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_PEND_VAL_INVALID,uwRet);

    uwRet = __SRE_FsemPend(0xffffffff);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_PEND_VAL_INVALID,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPend04
*-@tspec  Pend快速信号量
*-@ttitle 锁任务下场景下，Pend快速信号量试图引发任务切换
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemPend04()
{
    UINT32 uwRet;

    __SRE_TaskLock();

    uwRet = __SRE_FsemPend(10);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_PEND_IN_LOCK,uwRet);

    __SRE_TaskUnlock();

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPend05
*-@tspec  Pend快速信号量
*-@ttitle 锁任务下场景下，Pend快速信号量(计数值大于等待量)
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemPend05()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    INT32  wCount;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    wCount = __SRE_FsemGet(uwTaskID);

    uwRet = __SRE_FsemSet(uwTaskID, 2);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    __SRE_TaskLock();

    uwRet = __SRE_FsemPend(1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    __SRE_TaskUnlock();

    uwRet = __SRE_FsemSet(uwTaskID, wCount);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPend06
*-@tspec  Pend快速信号量
*-@ttitle Pend快速信号量正常功能测试(等待量大于计数值，引发任务切换)
*/

OS_SEC_TEXT_UT UINT32 FsemTest_Pend06_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;

    g_FsemTestCount = 1;

    uwRet = __SRE_FsemPend(1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    g_FsemTestCount = 3;

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPend06()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    g_FsemTestCount = 0;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 20;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Pend06_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    ICUNIT_ASSERT_EQUAL(g_FsemTestCount,1,g_FsemTestCount);

    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPend07
*-@tspec  Pend快速信号量
*-@ttitle Pend快速信号量正常功能测试(等待量小于计数值，不会引发任务切换)
*/

OS_SEC_TEXT_UT UINT32 FsemTest_Pend07_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskID;

    g_FsemTestCount = 1;

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_FsemSet(uwTaskID, 5);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_FsemPend(1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    g_FsemTestCount = 3;

    __osTskExit(uwTaskID);

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPend07()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    g_FsemTestCount = 0;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 20;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Pend07_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    ICUNIT_ASSERT_EQUAL(g_FsemTestCount,3,g_FsemTestCount);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost01
*-@tspec  Post快速信号量
*-@ttitle 快速信号量错误码：任务句柄非法（Idle任务）
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemPost01()
{
    UINT32 uwRet;

    uwRet = __SRE_FsemPost(g_uwIdleTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_TASK_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost02
*-@tspec  Post快速信号量
*-@ttitle 快速信号量错误码：任务句柄非法（未创建任务）
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post02_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost02()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 26;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post02_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_FsemPost(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_TASK_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost02
*-@tspec  Post快速信号量
*-@ttitle 对本核已创建任务进行Post操作，此任务未阻塞于快速信号量
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post03_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost03()
{
    UINT32 uwRet;
    INT32  wCount;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 26;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post03_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_FsemPost(uwTskHandle);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

    wCount = __SRE_FsemGet(uwTskHandle);
    ICUNIT_GOTO_EQUAL(wCount,1, wCount,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost04
*-@tspec  Post快速信号量
*-@ttitle 对本核已创建任务进行Post操作，此任务阻塞于快速信号量，且计数值为-1
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post04_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    g_FsemTestCount = 1;

    uwRet = __SRE_FsemPend(1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    g_FsemTestCount = 2;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost04()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    g_FsemTestCount = 0;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 20;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post04_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    ICUNIT_GOTO_EQUAL(g_FsemTestCount,1, g_FsemTestCount,EXIT);

    uwRet = __SRE_FsemPost(uwTskHandle);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

    ICUNIT_ASSERT_EQUAL(g_FsemTestCount,2, g_FsemTestCount);

    return SRE_OK;

EXIT:
    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost05
*-@tspec  Post快速信号量
*-@ttitle 对本核已创建任务进行Post操作，此任务阻塞于快速信号量，且计数值为-1
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post05_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    g_FsemTestCount = 1;

    uwRet = __SRE_FsemPend(2);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);


    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost05()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    g_FsemTestCount = 0;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 20;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post05_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    ICUNIT_GOTO_EQUAL(g_FsemTestCount,1, g_FsemTestCount,EXIT);

    uwRet = __SRE_FsemPost(uwTskHandle);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

    ICUNIT_ASSERT_EQUAL(g_FsemTestCount,1, g_FsemTestCount);

EXIT:
    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost06
*-@tspec  Post快速信号量
*-@ttitle 对本核已创建任务进行Post操作，此任务快速信号量计数值为0x7FFFFFFF
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post06_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost06()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTskHandle;
    TSK_INIT_PARAM_S os_task_init_param;

    memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
    os_task_init_param.auwArgs[0] = 0;
    os_task_init_param.uwStackSize = 0x200;
    os_task_init_param.uwPrivateData = 0;

    os_task_init_param.usTaskPrio = 26;
    os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post06_fun;
    os_task_init_param.pcName ="Fsem test";
    os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_FsemSet(uwTskHandle, 0x7fffffff);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet,EXIT);

    uwRet = __SRE_FsemPost(uwTskHandle);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_FSEM_OVERFLOW, uwRet,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTskHandle);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost07
*-@tspec  Post快速信号量
*-@ttitle 关闭核间信号量裁剪开关，对它核已创建任务进行post操作
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemPost07()
{
#if (OS_SYS_CORE_RUN_NUM > 1)
    UINT32 uwRet;
    UINT32 uwPID;
    MCFSEM_POST_FUNC pfnTemp;

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        pfnTemp = g_pfnMcFsemPost;
        g_pfnMcFsemPost = NULL;
        uwRet = __SRE_HuntByName(OS_SYS_CORE_START + 1, UT_TEST_TSK_NAME, &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

        uwRet = __SRE_FsemPost(uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_FSEM_POST_FAIL,uwRet);

        g_pfnMcFsemPost = pfnTemp;
    }
#endif

    return SRE_OK;
}

#if 0
/**
*-@test  UT_SreFsemPost08
*-@tspec  Post快速信号量
*-@ttitle 指定的任务PID中的核号超过最大核号，进行Post操作
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemPost08()
{
    UINT32 uwRet;

    uwRet = __SRE_FsemPost(0xabcd);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MCHWI_DST_INVALID,uwRet);

    return SRE_OK;
}
#endif
/**
*-@test  UT_SreFsemPost09
*-@tspec  Post快速信号量
*-@ttitle 对它核未创建任务进行post操作
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post09_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost09()
{
#if (OS_INCLUDE_MCFSEM == YES)
    UINT32 uwRet;
    UINT32 uwPID;
    UINT32 uwErrCode;
    TSK_HANDLE_T uwTskHandle;
    UINT32 uwRecordIndex;

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        TSK_INIT_PARAM_S os_task_init_param;

        memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
        os_task_init_param.auwArgs[0] = 0;
        os_task_init_param.uwStackSize = 0x200;
        os_task_init_param.uwPrivateData = 0;

        os_task_init_param.usTaskPrio = 26;
        os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post09_fun;
        os_task_init_param.pcName ="Fsem test";
        os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
        uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_HuntByName(OS_SYS_CORE_START + 1, "Fsem test", &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }
    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        uwRet = __SRE_TaskDelete(uwTskHandle);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

        uwErrCode = g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo;
        uwRecordIndex = g_pstCdaInfoAddr->uwRecordIndex;
        g_pstCdaInfoAddr->uwRecordIndex = 0;
        g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo = 0;

    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_FsemPost(uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();
    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo,OS_ERRNO_FSEM_TASK_INVALID,g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo);
        g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo = uwErrCode;
        g_pstCdaInfoAddr->uwRecordIndex = uwRecordIndex;
    }

#endif

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost10
*-@tspec  Post快速信号量
*-@ttitle 对它核Idle任务进行Post操作
*/
OS_SEC_TEXT_UT UINT32 UT_SreFsemPost10()
{
#if (OS_INCLUDE_MCFSEM == YES)
    UINT32 uwRet;
    UINT32 uwPID;
    UINT32 uwErrCode;
    UINT32 uwRecordIndex;

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        uwErrCode = g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo;
        uwRecordIndex = g_pstCdaInfoAddr->uwRecordIndex;
        g_pstCdaInfoAddr->uwRecordIndex = 0;
        g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo = 0;
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        CHAR  acCoreNo[4];
        CHAR  acTskName[OS_TSK_NAME_LEN];
        /*不同核创建的Idle任务名字为IdleCore+核号*/
        strcpy(acTskName,"IdleCore");
        acCoreNo[2] = '0' + (OS_SYS_CORE_START + 1)%10;
        acCoreNo[1] = '0' + ((OS_SYS_CORE_START + 1)/10)%10;
        acCoreNo[0] = '0' + ((OS_SYS_CORE_START + 1)/100)%10;
        acCoreNo[3] = 0;
        strcat(acTskName,acCoreNo);

        uwRet = __SRE_HuntByName(OS_SYS_CORE_START + 1, acTskName, &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

        uwRet = __SRE_FsemPost(uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();
    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo,OS_ERRNO_FSEM_TASK_INVALID,g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo);
        g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo = uwErrCode;
        g_pstCdaInfoAddr->uwRecordIndex = uwRecordIndex;
    }

#endif

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost11
*-@tspec  Post快速信号量
*-@ttitle 对它核已创建任务进行post操作
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post11_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost11()
{
#if (OS_INCLUDE_MCFSEM == YES)
    UINT32 uwRet;
    UINT32 uwPID;
    TSK_HANDLE_T uwTskHandle;

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        TSK_INIT_PARAM_S os_task_init_param;

        memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
        os_task_init_param.auwArgs[0] = 0;
        os_task_init_param.uwStackSize = 0x200;
        os_task_init_param.uwPrivateData = 0;

        os_task_init_param.usTaskPrio = 27;
        os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post09_fun;
        os_task_init_param.pcName ="Fsem test";
        os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
        uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_HuntByName(OS_SYS_CORE_START + 1, "Fsem test", &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_FsemPost(uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();
    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        uwRet = __SRE_TaskDelete(uwTskHandle);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

#endif

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost12
*-@tspec  Post快速信号量
*-@ttitle 对它核已创建任务进行Post操作，此任务阻塞于快速信号量，且计数值为-1
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post12_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    g_FsemTestCount = 1;

    uwRet = __SRE_FsemPend(1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    g_FsemTestCount = 2;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost12()
{
#if (OS_INCLUDE_MCFSEM == YES)
    UINT32 uwRet;
    UINT32 uwPID;

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        TSK_HANDLE_T uwTskHandle;
        TSK_INIT_PARAM_S os_task_init_param;

        g_FsemTestCount = 0;

        memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
        os_task_init_param.auwArgs[0] = 0;
        os_task_init_param.uwStackSize = 0x200;
        os_task_init_param.uwPrivateData = 0;

        os_task_init_param.usTaskPrio = 20;
        os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post12_fun;
        os_task_init_param.pcName ="Fsem test";
        os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
        uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

        ICUNIT_ASSERT_EQUAL(g_FsemTestCount, 1, g_FsemTestCount);
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_HuntByName(OS_SYS_CORE_START + 1, "Fsem test", &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_FsemPost(uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();
    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        ICUNIT_ASSERT_EQUAL(g_FsemTestCount, 2, g_FsemTestCount);
    }

#endif

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost13
*-@tspec  Post快速信号量
*-@ttitle 对它核已创建任务进行Post操作，此任务阻塞于快速信号量，且计数值为-1
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post13_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    g_FsemTestCount = 1;

    uwRet = __SRE_FsemPend(2);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    g_FsemTestCount = 2;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost13()
{
#if (OS_INCLUDE_MCFSEM == YES)
    UINT32 uwRet;
    UINT32 uwPID;
    TSK_HANDLE_T uwTskHandle;

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        TSK_INIT_PARAM_S os_task_init_param;

        g_FsemTestCount = 0;

        memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
        os_task_init_param.auwArgs[0] = 0;
        os_task_init_param.uwStackSize = 0x200;
        os_task_init_param.uwPrivateData = 0;

        os_task_init_param.usTaskPrio = 20;
        os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post13_fun;
        os_task_init_param.pcName ="Fsem test";
        os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
        uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

        ICUNIT_ASSERT_EQUAL(g_FsemTestCount, 1, g_FsemTestCount);
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_HuntByName(OS_SYS_CORE_START + 1, "Fsem test", &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_FsemPost(uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();
    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        ICUNIT_ASSERT_EQUAL(g_FsemTestCount, 1, g_FsemTestCount);
        uwRet = __SRE_TaskDelete(uwTskHandle);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

#endif

    return SRE_OK;
}

/**
*-@test  UT_SreFsemPost14
*-@tspec  Post快速信号量
*-@ttitle 对它核未创建任务进行post操作
*/
OS_SEC_TEXT_UT UINT32 FsemTest_Post14_fun(UINT32 p1,UINT32 p2,UINT32 p3,UINT32 p4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_SreFsemPost14()
{
#if (OS_INCLUDE_MCFSEM == YES)
    UINT32 uwRet;
    UINT32 uwPID;
    UINT32 uwErrCode;
    TSK_HANDLE_T uwTskHandle;
    UINT32 uwRecordIndex;

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        TSK_INIT_PARAM_S os_task_init_param;

        uwErrCode = g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo;
        uwRecordIndex = g_pstCdaInfoAddr->uwRecordIndex;
        g_pstCdaInfoAddr->uwRecordIndex = 0;
        g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo = 0;

        memset(&os_task_init_param, 0, sizeof(TSK_INIT_PARAM_S));
        os_task_init_param.auwArgs[0] = 0;
        os_task_init_param.uwStackSize = 0x200;
        os_task_init_param.uwPrivateData = 0;

        os_task_init_param.usTaskPrio = 26;
        os_task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)FsemTest_Post14_fun;
        os_task_init_param.pcName ="Fsem test";
        os_task_init_param.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
        uwRet = __SRE_TaskCreate(&uwTskHandle, &os_task_init_param);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

        uwRet = __SRE_FsemSet(uwTskHandle, 0x7fffffff);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_HuntByName(OS_SYS_CORE_START + 1, "Fsem test", &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();

    if(OS_SYS_CORE_START == SRE_GetCoreID())
    {
        uwRet = __SRE_FsemPost(uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();
    if(OS_SYS_CORE_START + 1 == SRE_GetCoreID())
    {
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo,OS_ERRNO_FSEM_OVERFLOW,g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo);
        g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo = uwErrCode;
        g_pstCdaInfoAddr->uwRecordIndex = uwRecordIndex;

        uwRet = __SRE_TaskDelete(uwTskHandle);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

#endif

    return SRE_OK;
}

OS_SEC_TEXT_UT VOID UT_sre_fsem(VOID)
{
    iUINT32 uiSuiteId;
    TEST_ADD_SUITE(uiSuiteId, "UT_sre_fsem");

    TEST_ADD_CASE(UT_SreFsemSet01, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemSet02, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemSet03, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemSet04, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemSet05, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemSet06, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemSet07, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SreFsemGet01, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemGet02, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemGet03, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemGet04, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemGet05, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SreFsemPend01, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPend02, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPend03, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPend04, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPend05, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPend06, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPend07, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SreFsemPost01, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost02, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost03, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost04, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost05, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost06, uiSuiteId, Label_RUN);
#if (OS_INCLUDE_MCFSEM == YES && OS_SYS_CORE_RUN_NUM > 1)
    TEST_ADD_CASE(UT_SreFsemPost07, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SreFsemPost08, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost09, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost10, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost11, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost12, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost13, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SreFsemPost14, uiSuiteId, Label_RUN);
#endif

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







                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     