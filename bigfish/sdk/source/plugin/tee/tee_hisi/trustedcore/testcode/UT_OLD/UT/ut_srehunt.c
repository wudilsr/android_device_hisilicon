#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "sre_base.h"
#include "sre_sys.h"
#include "sre_typedef.h"
#include "sre_task.h"
#include "sre_hunt.h"
#include "sre_hwi.h"
#include "sre_swi.h"
//#include "SRE_sync.h"
#include "iCunit.h"
#include "osTest.h"
#include "sre_config.h"
#include "app_data_common.h"
#include "sre_hunt.ph"
//#include "Set_Peg.h"
#include "sre_mem.h"

extern SWI_HANDLE_T g_TestSwiHandle;
static  UINT32 g_ITestCheckLc;
EXTERN_FAR TSK_HANDLE_T  g_uwIdleTaskID;
EXTERN_FAR THREADINFO_S *g_pstLocalThreadInfo;
EXTERN_FAR BOOL m_bHuntByMature;
EXTERN_FAR UINT8 g_ucPtNum;
extern volatile UINT32 g_vuwHuntInitPhase;
EXTERN_FAR THREADINFO_S *g_pstGlobalThreadInfo;

OS_SEC_TEXT_UT VOID *  UTest_MemAlloc_Hunt_Stub()
{
    return NULL;
}
/**
*@test UT_sreHunt_001
*-@tspec    Hunt模块补充测试
*-@ttitle   调用uniHuntByName接口，入参线程PID非法
*-@tbrief
1. 调用uniHuntByName接口，入参线程PID非法
*-@texpect
1. 获取PID失败,返回错误码
*-@tprior 1
*-@tauto TRUE
*-@tremark DFX
 */

OS_SEC_TEXT_UT VOID UT_sreHunt_001_TSK(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_001()
{
    UINT32 uwRet;
    UINT32 uwTaskPID1;
    UINT32* uwPID=NULL;
    TSK_INIT_PARAM_S stInitParam1 = {UT_sreHunt_001_TSK, 26, 0, {0}, 0x400, "test001", 0, 0, OS_MEM_DEFAULT_FSC_PT};


    uwRet = __SRE_TaskCreate(&uwTaskPID1, &stInitParam1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(), "test001", uwPID);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HUNT_ILLEGAL_INPUT, uwRet, EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*@test UT_sreHunt_002
*-@tspec    Hunt模块补充测试
*-@ttitle   调用uniHuntByName接口，入参核号非法
*-@tbrief
1. 调用uniHuntByName接口，入参核号非法
*-@texpect
1. 获取PID失败,返回错误码
*-@tprior 1
*-@tauto TRUE
*-@tremark DFX
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_002_TSK(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_002()
{
    UINT32 uwRet;
    UINT32 uwTaskPID1;
    UINT32 uwPID;
    TSK_INIT_PARAM_S stInitParam1 = {UT_sreHunt_002_TSK, 26, 0, {0}, 0x400, "test002", 0, 0, OS_MEM_DEFAULT_FSC_PT};


    uwRet = __SRE_TaskCreate(&uwTaskPID1, &stInitParam1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_HuntByName(OS_SYS_CORE_MAX_NUM, "test002", &uwPID);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HUNT_ILLEGAL_INPUT, uwRet, EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*@test UT_sreHunt_003
*-@tspec    Hunt模块补充测试
*-@ttitle   调用uniHuntByName接口，入参线程名字非法
*-@tbrief
1. 调用uniHuntByName接口，入参线程名字非法
*-@texpect
1. 获取PID失败,返回错误码
*-@tprior 1
*-@tauto TRUE
*-@tremark DFX
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_003_TSK(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_003()
{
    UINT32 uwRet;
    UINT32 uwTaskPID1;
    UINT32 uwPID;
    TSK_INIT_PARAM_S stInitParam1 = {UT_sreHunt_003_TSK, 26, 0, {0}, 0x400, "test0031234567890", 0, 0, OS_MEM_DEFAULT_FSC_PT};

    uwRet = __SRE_TaskCreate(&uwTaskPID1, &stInitParam1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(), "test0031234567890", &uwPID);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK, uwRet, EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}


/**
*@test UT_sreHunt_004
*-@tspec    Hunt模块补充测试
*-@ttitle   在正在运行的任务中，调用uniHuntByName接口，获取自身线程的PID
*-@tbrief
1. 在正在运行的任务中，调用uniHuntByName接口，获取自身线程的PID
*-@texpect
1. 获取PID成功
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI、XTENSA、FSL8156
 */

OS_SEC_TEXT_UT VOID UT_sreHunt_004_TSK(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;
    UINT32 uwTaskPID1;
    UINT32 uwPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(), "test004", &uwPID);
    uwTaskPID1 = uwPID;
    ICUNIT_ASSERT_EQUAL_VOID(uwTaskPID, uwTaskPID1, uwTaskPID);

    g_ITestCheckLc++;

    __osTskExit(uwTaskPID);

    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_004()
{
    UINT32 uwRet;
    UINT32 uwTaskPID1;
    TSK_INIT_PARAM_S stInitParam1 = {UT_sreHunt_004_TSK, 20, 0, {0}, 0x400, "test004", 0, 0, OS_MEM_DEFAULT_FSC_PT};

    g_ITestCheckLc = 0;

    uwRet = __SRE_TaskCreate(&uwTaskPID1, &stInitParam1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    ICUNIT_ASSERT_EQUAL(g_ITestCheckLc, 1, g_ITestCheckLc);

    return SRE_OK;
}


/**
*@test UT_sreHunt_005
*-@tspec    Hunt模块补充测试
*-@ttitle   调用uniHuntByName获得已经创建的任务PID成功
*-@tbrief
*-# 获取已创建的任务1PID
*-# 获取已创建的任务2PID
*-@texpect
*-# 获取PID成功
*-# 获取PID成功
*-@tprior 1
*-@tauto TRUE
*-@tremark DFX
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_005_TSK(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return;
}

OS_SEC_TEXT_UT VOID UT_sreHunt_005_TSK1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_005()
{
    UINT32 uwRet;
    UINT32 uwTaskPID1;
    UINT32 uwTaskPID2;
    UINT32 uwPID;
    TSK_INIT_PARAM_S stInitParam1 = {UT_sreHunt_005_TSK, 26, 0, {0}, 0x400, "hunt_test005_1", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    TSK_INIT_PARAM_S stInitParam2 = {UT_sreHunt_005_TSK1,27, 0, {0}, 0x400, "hunt_test005_2", 0, 0, OS_MEM_DEFAULT_FSC_PT};

    uwRet = __SRE_TaskCreate(&uwTaskPID1, &stInitParam1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_TaskCreate(&uwTaskPID2, &stInitParam2);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet,EXIT);

EXIT:


    uwRet = __SRE_HuntByName(SRE_GetCoreID(), "hunt_test005_1", &uwPID);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(), "hunt_test005_2", &uwPID);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_TaskDelete(uwTaskPID1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_TaskDelete(uwTaskPID2);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return ICUNIT_SUCCESS;
}

/**
*@test UT_sreHunt_006
*-@tspec    Hunt模块补充测试
*-@ttitle   获取未创建任务线程PID
*-@tbrief
1. 未创建任务，调用uniHuntByName接口，获取自身线程的PID
*-@texpect
1. 获取PID失败
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI、XTENSA、FSL8156
 */

OS_SEC_TEXT_UT UINT32 UT_sreHunt_006()
{
    UINT32 uwRet;
    UINT32 uwTaskPID1;
    UINT32 uwTaskPID2;
    UINT32 uwPID;

    uwRet = __SRE_HuntByName(SRE_GetCoreID(), "hunt_test006", &uwPID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_HUNT_THREAD_NOT_CREAT, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*@test UT_sreHunt_007
*-@tspec    Hunt模块补充测试
*-@ttitle   调用uniHuntByName获得已经删除的任务PID失败
*-@tbrief
*-# 获取已删除的任务1PID
*-# 获取已删除的任务2PID
*-@texpect
*-# 获取PID失败
*-# 获取PID失败
*-@tprior 1
*-@tauto TRUE
*-@tremark DFX
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_007_TSK(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwTaskPID;
    UINT32 uwRet;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return;
}

OS_SEC_TEXT_UT VOID UT_sreHunt_007_TSK1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwTaskPID;
    UINT32 uwRet;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_007()
{
    UINT32 uwRet;
    UINT32 uwTaskPID1;
    UINT32 uwTaskPID2;
    UINT32 uwPID;
    TSK_INIT_PARAM_S stInitParam1 = {UT_sreHunt_007_TSK, 26, 0, {0}, 0x400, "hunt_test007_1", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    TSK_INIT_PARAM_S stInitParam2 = {UT_sreHunt_007_TSK1,27, 0, {0}, 0x400, "hunt_test007_2", 0, 0, OS_MEM_DEFAULT_FSC_PT};

    uwRet = __SRE_TaskCreate(&uwTaskPID1, &stInitParam1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_TaskCreate(&uwTaskPID2, &stInitParam2);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet,EXIT);

    uwRet = __SRE_TaskDelete(uwTaskPID2);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet,EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(), "hunt_test007_1", &uwPID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_HUNT_THREAD_NOT_CREAT, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(), "hunt_test007_2", &uwPID);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_HUNT_THREAD_NOT_CREAT,uwRet);

    return ICUNIT_SUCCESS;
}

/**
*@test UT_sreHunt_008
*-@tspec    Hunt模块补充测试
*-@ttitle   创建重复的任务
*-@tbrief
*-# 创建任务1PID
*-# 重复创建任务1PID
*-@texpect
*-#重复创建失败
*-@tprior 1
*-@tauto TRUE
*-@tremark DFX
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_008_TSK(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
{
    UINT32 uwTaskPID;
    UINT32 uwRet;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
    return;
}
OS_SEC_TEXT_UT UINT32 UT_sreHunt_008()
{
    UINT32 uwRet;
    UINT32 uwTaskPID1;
    UINT32 uwTaskPID2;
    UINT32 uwPID;
    TSK_INIT_PARAM_S stInitParam1 = {UT_sreHunt_008_TSK, 26, 0, {0}, 0x400, "hunt_test008", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    TSK_INIT_PARAM_S stInitParam2 = {UT_sreHunt_008_TSK,27, 0, {0}, 0x400, "hunt_test008", 0, 0, OS_MEM_DEFAULT_FSC_PT};

    uwRet = __SRE_TaskCreate(&uwTaskPID1, &stInitParam1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_TaskCreate(&uwTaskPID2, &stInitParam2);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_HUNT_THREAD_NAME_REPEAT,uwRet,EXIT);


EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return ICUNIT_SUCCESS;
}

/**
*@test UT_sreHunt_009
*-@tspec    Hunt模块补充测试
*-@ttitle   调用uniHuntByName获得idle任务PID
*-@tbrief
1. 调用uniHuntByName获得idle任务PID
*-@texpect
2. 获取PID成功
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI、XTENSA、FSL8156
 */
OS_SEC_TEXT_UT UINT32 UT_sreHunt_009()
{
    UINT32 uwTaskPID;
    CHAR  acCoreNo[4];
    CHAR  acTskName[OS_TSK_NAME_LEN];
    UINT32 uwPID;

    /*不同核创建的Idle任务名字为IdleCore+核号*/
    strcpy(acTskName,"IdleCore");
    acCoreNo[3] = 0;
    acCoreNo[2] = '0' + (SRE_GetCoreID())%10;
    acCoreNo[1] = '0' + (SRE_GetCoreID()/10)%10;
    acCoreNo[0] = '0' + (SRE_GetCoreID()/100)%10;

    strcat(acTskName,acCoreNo);

    __SRE_HuntByName(SRE_GetCoreID(), acTskName, &uwPID);
    uwTaskPID = uwPID;
    ICUNIT_ASSERT_EQUAL(uwTaskPID, g_uwIdleTaskID, uwTaskPID);

    return SRE_OK;
}




/**
*@test UT_sreHunt_010
*-@tspec    Hunt模块补充测试
*-@ttitle   在正在运行的软中断中，调用uniHuntByName接口，获取自身线程的PID
*-@tbrief
1. 在正在运行的软中断中，调用uniHuntByName接口，获取自身线程的PID
*-@texpect
1. 获取PID成功
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI、XTENSA、FSL8156
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_010_SWI(UINT32 uwValue)
{
    UINT32 uwRet;
    SWI_HANDLE_T puwSwiID;
    SWI_HANDLE_T puwSwiID1;
    UINT32 uwPID;

    uwRet = __SRE_SwiSelf(&puwSwiID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HuntByName(SRE_GetCoreID(), "test010", &uwPID);
    puwSwiID1 = uwPID;
    ICUNIT_ASSERT_EQUAL_VOID(puwSwiID1, puwSwiID, puwSwiID1);

    g_ITestCheckLc++;
    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_010()
{
    UINT32 uwRet;
    SWI_HANDLE_T puwSwiID;
    g_ITestCheckLc = 0;
    SWI_INIT_PARA_S pstInitPara;

    pstInitPara.pfnHandler = UT_sreHunt_010_SWI;
    pstInitPara.usPriority = OS_SWI_PRIORITY_06;
    pstInitPara.uwInitValue = 1;
    pstInitPara.pcSwiName = "test010";

    uwRet = __SRE_SwiCreate(&puwSwiID,&pstInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_SwiActivate(puwSwiID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, label);

    ICUNIT_GOTO_EQUAL(g_ITestCheckLc, 1, g_ITestCheckLc, label);

label:
    uwRet = __SRE_SwiDelete(puwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*@test UT_sreHunt_011
*-@tspec    Hunt模块补充测试
*-@ttitle   获取创建成功的软中断PID
*-@tbrief
1.创建一个软中断，获取该软中断的PID
*-@texpect
1. 获取PID成功
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI、XTENSA、FSL8156
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_011_SWI(UINT32 uwValue)
{
    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_011()
{
    UINT32 uwRet;
    SWI_HANDLE_T puwSwiID;
    SWI_INIT_PARA_S pstInitPara;
    UINT32 uwPID;
    pstInitPara.pfnHandler = UT_sreHunt_011_SWI;
    pstInitPara.usPriority = OS_SWI_PRIORITY_06;
    pstInitPara.uwInitValue = 1;
    pstInitPara.pcSwiName = "test011";

    uwRet = __SRE_SwiCreate(&puwSwiID,&pstInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_SwiActivate(puwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet =__SRE_HuntByName(SRE_GetCoreID(), "test011", &uwPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, label);

label:
    uwRet = __SRE_SwiDelete(puwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*@test UT_sreHunt_012
*-@tspec    Hunt模块补充测试
*-@ttitle   获取未创建的软中断PID
*-@tbrief
1.未创建软中断，获取软中断的PID
*-@texpect
1. 获取PID失败
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI、XTENSA、FSL8156
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_012_SWI(UINT32 uwValue)
{
    return;
}
OS_SEC_TEXT_UT UINT32 UT_sreHunt_012()
{
    UINT32 uwRet;
    SWI_HANDLE_T puwSwiID;
    SWI_INIT_PARA_S pstInitPara;
    UINT32 uwPID;
    pstInitPara.pfnHandler = UT_sreHunt_012_SWI;
    pstInitPara.usPriority = OS_SWI_PRIORITY_06;
    pstInitPara.uwInitValue = 1;
    pstInitPara.pcSwiName = "test012";

    uwRet =__SRE_HuntByName(SRE_GetCoreID(), "test012", &uwPID);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_HUNT_THREAD_NOT_CREAT, uwRet, label);

label:


    return SRE_OK;
}


/**
*@test UT_sreHunt_013
*-@tspec    Hunt模块补充测试
*-@ttitle   获取已删除的软中断PID
*-@tbrief
1.创建一个软中断，删除后获取该软中断的PID
*-@texpect
1. 获取PID失败
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI、XTENSA、FSL8156
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_013_SWI(UINT32 uwValue)
{
    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_013()
{
    UINT32 uwRet;
    SWI_HANDLE_T puwSwiID;
    SWI_INIT_PARA_S pstInitPara;
    UINT32 uwPID;
    pstInitPara.pfnHandler = UT_sreHunt_013_SWI;
    pstInitPara.usPriority = OS_SWI_PRIORITY_06;
    pstInitPara.uwInitValue = 1;
    pstInitPara.pcSwiName = "test013";

    uwRet = __SRE_SwiCreate(&puwSwiID,&pstInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_SwiActivate(puwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_SwiDelete(puwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet =__SRE_HuntByName(SRE_GetCoreID(), "test011", &uwPID);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_HUNT_THREAD_NOT_CREAT, uwRet, label);

label:

    return SRE_OK;
}


/**
*@test UT_sreHunt_014
*-@tspec    Hunt模块补充测试
*-@ttitle   创建重复的软中断
*-@tbrief
1.创建一个软中断， 利用该信息重复创建软中断
*-@texpect
1.重复创建失败
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI、XTENSA、FSL8156
 */
OS_SEC_TEXT_UT VOID UT_sreHunt_014_SWI(UINT32 uwValue)
{
    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_014()
{
    UINT32 uwRet;
    SWI_HANDLE_T puwSwiID;
    SWI_INIT_PARA_S pstInitPara;
    UINT32 uwPID;
    pstInitPara.pfnHandler = UT_sreHunt_014_SWI;
    pstInitPara.usPriority = OS_SWI_PRIORITY_06;
    pstInitPara.uwInitValue = 1;
    pstInitPara.pcSwiName = "test014";

    uwRet = __SRE_SwiCreate(&puwSwiID,&pstInitPara);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    uwRet = __SRE_SwiCreate(&puwSwiID,&pstInitPara);
    ICUNIT_GOTO_EQUAL(uwRet,OS_ERRNO_HUNT_THREAD_NAME_REPEAT,uwRet,label);


label:
    uwRet = __SRE_SwiDelete(puwSwiID);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_015()
{
    UINT32 uwRet;
    g_pstLocalThreadInfo->pstThreadLst =(THREAD_IDX_S *) 0xfffffffe;
    uwRet = osHuntInit();
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_016()
{
    SRE_HuntMature();
    ICUNIT_ASSERT_EQUAL(m_bHuntByMature,TRUE,m_bHuntByMature);
    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_017()
{
    UINT32 uwRet;
    UINT32 uvIntSave;
    UINT8 ucPtNum;
    UINT32 uwPID;

    uwRet =  __SRE_HuntByName(SRE_GetCoreID(),"HUNT" , &uwPID);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_HUNT_THREAD_NOT_CREAT,uwRet);

    uvIntSave = __SRE_IntLock();

    ucPtNum = g_ucPtNum;
    g_ucPtNum = 0;

    uwRet =  __SRE_HuntByName(SRE_GetCoreID(),"HUNT" , &uwPID);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_HUNT_THREAD_NOT_CREAT,uwRet);

    g_ucPtNum = ucPtNum;

    (VOID)__SRE_IntRestore(uvIntSave);

    return SRE_OK;
}
#if 0
 OS_SEC_TEXT_UT UINT32 UT_sreHunt_018()
{
    UINT32 uwRet;
    UINT32 uvIntSave;
    SETPEG_JMP_ST stRebootStub;
    UINT32 uwHuntInitPhase;
    THREADINFO_S *pstGlobalThreadInfo;


    uvIntSave = __SRE_IntLock();
    if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
    {
        pstGlobalThreadInfo = g_pstGlobalThreadInfo;
        uwHuntInitPhase = g_vuwHuntInitPhase;
        g_vuwHuntInitPhase = OS_MC_PHASE_UNINIT;
        SET_PEG(SRE_MemAllocAlign, UTest_MemAlloc_Hunt_Stub, (SETPEG_JMP_ST *)&stRebootStub);

        uwRet = osHuntInit();
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_HUNT_INIT_ERROR, uwRet);

        g_vuwHuntInitPhase = uwHuntInitPhase;
        g_pstGlobalThreadInfo = pstGlobalThreadInfo;
        CLEAN_PEG(SRE_MemAllocAlign, stRebootStub);
    }
    (VOID)__SRE_IntRestore(uvIntSave);

    return SRE_OK;
}

OS_SEC_TEXT_UT  UINT32 UT_sreHunt_019()
{
    UINT32 uwRet;
    UINT32 uvIntSave;
    SETPEG_JMP_ST stRebootStub;
    UINT8 ucPtNum;
    THREADINFO_S *pstLocalThreadInfo;

    uvIntSave = __SRE_IntLock();
    if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
    {

        SET_PEG(SRE_MemAllocAlign, UTest_MemAlloc_Hunt_Stub, (SETPEG_JMP_ST *)&stRebootStub);
        pstLocalThreadInfo = g_pstLocalThreadInfo;
        ucPtNum = g_ucPtNum;
        g_ucPtNum = 0;
        uwRet = osHuntInit();
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_HUNT_INIT_ERROR, uwRet);

        CLEAN_PEG(SRE_MemAllocAlign, stRebootStub);
        g_ucPtNum = ucPtNum;
        g_pstLocalThreadInfo = pstLocalThreadInfo;
    }
    (VOID)__SRE_IntRestore(uvIntSave);

    return SRE_OK;
}

 OS_SEC_TEXT_UT UINT32 UT_sreHunt_020()
{
    UINT32 uwRet;
    UINT32 uvIntSave;
    SETPEG_JMP_ST stRebootStub;
    UINT8 ucPtNum;
    //THREADINFO_S *pstLocalThreadInfo;
    UINT32 uwHuntInitPhase;

    uvIntSave = __SRE_IntLock();
    if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
    {

        uwHuntInitPhase = g_vuwHuntInitPhase;
        g_vuwHuntInitPhase = OS_MC_PHASE_INITED;
        //pstLocalThreadInfo = g_pstLocalThreadInfo;

        SET_PEG(SRE_MemAllocAlign, UTest_MemAlloc_Hunt_Stub, (SETPEG_JMP_ST *)&stRebootStub);

        uwRet = osHuntInit();
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_HUNT_INIT_ERROR, uwRet);

        CLEAN_PEG(SRE_MemAllocAlign, stRebootStub);

        //g_pstLocalThreadInfo = pstLocalThreadInfo;
        g_vuwHuntInitPhase = uwHuntInitPhase;
    }
    (VOID)__SRE_IntRestore(uvIntSave);

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 UT_sreHunt_021()
{
    UINT32 uwRet;
    UINT32 uvIntSave;
    UINT8 ucPtNum;
    UINT32 uwPID;
    UINT8 ucMature;

    uvIntSave = __SRE_IntLock();
    if(SRE_GetCoreID() == SRE_GetMasterCore())
    {
        ucMature = g_pstGlobalThreadInfo[SRE_GetCoreID()].ucMature;
        g_pstGlobalThreadInfo[SRE_GetCoreID()].ucMature = 0;
    }
    //SRE_WaitForAllCores();
    if(SRE_GetCoreID() == SRE_GetMasterCore())
    {
        SRE_TaskDelay(5);
    }
    if(SRE_GetCoreID() != SRE_GetMasterCore())
    {
        uwRet =  __SRE_HuntByName(SRE_GetMasterCore(),"HUNT" , &uwPID);
        ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_HUNT_THREAD_NOT_CREAT,uwRet);
    }
    else
    {
        g_pstGlobalThreadInfo[SRE_GetCoreID()].ucMature = 1;
    }
    //SRE_WaitForAllCores();
    if(SRE_GetCoreID() == SRE_GetMasterCore())
    {
        g_pstGlobalThreadInfo[SRE_GetCoreID()].ucMature == ucMature;
    }
    (VOID)__SRE_IntRestore(uvIntSave);

    return SRE_OK;
}
#endif
OS_SEC_TEXT_UT VOID UT_SRE_Hunt()
{
    UINT32 uiSuiteId;
    TEST_ADD_SUITE(uiSuiteId, "UT_SREHunt");

        TEST_ADD_CASE(UT_sreHunt_001, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_002, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_003, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_004, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_005, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_006, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_007, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_008, uiSuiteId, Label_RUN);
        //TEST_ADD_CASE(UT_sreHunt_009, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_010, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_011, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_012, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_013, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_014, uiSuiteId, Label_RUN);
        //TEST_ADD_CASE(UT_sreHunt_015, uiSuiteId, Label_RUN);//此用例为手动用例，打开后会导致核内结构体数据清空。
        //TEST_ADD_CASE(UT_sreHunt_016, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_017, uiSuiteId, Label_RUN); //可能存在问题，要解决
        //TEST_ADD_CASE(UT_sreHunt_018, uiSuiteId, Label_RUN);
        //TEST_ADD_CASE(UT_sreHunt_019, uiSuiteId, Label_RUN);
        //TEST_ADD_CASE(UT_sreHunt_020, uiSuiteId, Label_RUN);
        //TEST_ADD_CASE(UT_sreHunt_021, uiSuiteId, Label_RUN);
Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
};

#ifdef __cplusplus
#if __cplusplus
    }
#endif /* __cpluscplus */
#endif /* __cpluscplus */


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            







                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            







                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  