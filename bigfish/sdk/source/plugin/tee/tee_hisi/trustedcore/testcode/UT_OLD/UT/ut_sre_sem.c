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
#include "sre_sem.ph"
#include "sre_task.h"
#include "sre_swi.h"
#include "sre_hwi.h"
#include "sre_mem.h"
#include "sre_sys.h"
#include "sre_sys.ph"
//#include "sre_sync.ph"
#include "sre_task.ph"
#include "sre_list.ph"
#include "sre_hunt.h"
#include "osTest.h"
#include "app_data_common.h"
#include "Set_Peg.h"

 //extern UINT32 osMcComEnQ(UINT32 uwDstPid, UINT8  ucOprtType, UINT32 uwOprtNum);
 static SEM_HANDLE_T   gs_uwSemHandle;
 static UINT32   uwSemCount = 0;
 EXTERN_FAR UINT16        g_usMaxSem;
 EXTERN_FAR LIST_OBJECT_S g_stUnusedSemList;
 extern UINT32 osSemRegister(const SEM_MOD_INFO_S *pstModInfo);

 OS_SEC_TEXT_UT VOID *  UTest_MemAlloc_Sem_Stub()
 {
     return NULL;
 }
 /**
 *@test UT_SRE_Sem_001
 *-@tspec 信号量模块测试
 *-@ttitle 创建信号量，输入信号量计数值合法（0 ～ 0xFFFFFFFE)，信号量操作句柄合法(不为NULL)，创建信号量成功。
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 创建信号量，输入信号量计数值合法（0 ～ 0xFFFFFFFE)，信号量操作句柄合法(不为NULL)，
 *-@texpect
 *-# 创建信号量成功
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_001()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemCreate(0XFFFFFFFE, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_002
 *-@tspec 信号量模块测试
 *-@ttitle 创建信号量，输入信号量计数值0XFFFFFFFF，信号量操作句柄合法(不为NULL)，创建信号量失败。
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 创建信号量，输入信号量计数值0XFFFFFFFF，信号量操作句柄合法(不为NULL)，
 *-@texpect
 *-# 创建信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_002()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0XFFFFFFFF, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_003
 *-@tspec 信号量模块测试
 *-@ttitle 创建信号量，输入信号量计数值合法（0 ～ 0xFFFFFFFE)，信号量操作句柄为NULL，创建信号量失败。
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 创建信号量，输入信号量计数值0，信号量操作句柄为NULL
 *-@texpect
 *-# 创建信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_003()
 {
     UINT32 uwRet;
     SEM_HANDLE_T *uwSemHandle = NULL;

     uwRet = __SRE_SemCreate(0, uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_PTR_NULL, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_004
 *-@tspec 信号量模块测试
 *-@ttitle 创建信号量，连续创建配置最大支持的信号量数，再创建信号量时，创建失败，返回错误码OS_ERRNO_SEM_ALL_BUSY；
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 创建信号量，连续创建配置最大支持的信号量数，再创建信号量
 *-@texpect
 *-# 创建信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_004()
 {
     UINT32 uwRet;
     UINT32 uwLoop;
     SEM_HANDLE_T uwSemHandle[11] ;

     for(uwLoop = 0; uwLoop < g_usMaxSem ; uwLoop++)
     {
         uwRet = __SRE_SemCreate(0, &uwSemHandle[uwLoop]);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     }
     uwRet = __SRE_SemCreate(0, &uwSemHandle[uwLoop]);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_ALL_BUSY, uwRet);

     for(uwLoop = 0; uwLoop < g_usMaxSem ; uwLoop++)
     {
         uwRet = __SRE_SemDelete(uwSemHandle[uwLoop]);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     }

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_005
 *-@tspec 信号量模块测试
 *-@ttitle 创建一个信号量，根据输入的信号量句柄，删除该信号量，信号量句柄合法，删除成功
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 创建一个信号量，根据输入的信号量句柄，删除该信号量，信号量句柄合法，删除成功
 *-@texpect
 *-# 删除信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_005()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_006
 *-@tspec 信号量模块测试
 *-@ttitle 删除信号量，传入非法信号量句柄（该信号量未被创建），删除失败，返回OS_ERRNO_SEM_INVALID
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 删除信号量，传入非法信号量句柄（该信号量未被创建），删除失败，返回OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# 删除信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_006()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_007
 *-@tspec 信号量模块测试
 *-@ttitle 删除信号量，传入非法信号量句柄（该信号量未被创建），删除失败，返回OS_ERRNO_SEM_INVALID
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 删除信号量，传入非法信号量句柄（该信号量未被创建），删除失败，返回OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# 删除信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_007()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_008
 *-@tspec 信号量模块测试
 *-@ttitle 删除信号量，传入的信号量句柄合法，但信号量上有阻塞的任务，删除失败，返回OS_ERRNO_SEM_PendED
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 删除信号量，传入的信号量句柄合法，但信号量上有阻塞的任务，删除失败，返回OS_ERRNO_SEM_PendED
 *-@texpect
 *-# 删除信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_008_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet;
    UINT32 uwTaskPID;

     __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_008()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_008_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_PENDED, uwRet, EXIT2);



 EXIT2:
     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     __SRE_SemDelete(uwSemHandle);
     __SRE_TaskDelete(uwTaskPid1);
     return ICUNIT_SUCCESS;
 EXIT1:
     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_009
 *-@tspec 信号量模块测试
 *-@ttitle Pend信号量时，传入非法信号量句柄（大于配置信号量最大个数），Pend信号量失败，返回返回OS_ERRNO_SEM_INVALID
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Pend信号量时，传入非法信号量句柄（大于配置信号量最大个数），Pend信号量失败，返回返回OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# PEND信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_009()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_010
 *-@tspec 信号量模块测试
 *-@ttitle Pend信号量时，传入非法信号量句柄（该信号量未被创建），Pend信号量失败，返回OS_ERRNO_SEM_INVALID
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Pend信号量时，传入非法信号量句柄（该信号量未被创建），Pend信号量失败，返回OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# PEND信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_010()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }



 /**
 *@test UT_SRE_Sem_011
 *-@tspec 信号量模块测试
 *-@ttitle Pend信号量时，传入合法信号量句柄，等待时间为0，Pend信号量失败，返回OS_ERRNO_SEM_UNAVAILABLE
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Pend信号量时，传入合法信号量句柄，等待时间为0，Pend信号量失败，返回OS_ERRNO_SEM_UNAVAILABLE
 *-@texpect
 *-# PEND信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_011()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemPend(uwSemHandle, 0);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_UNAVAILABLE, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_012
 *-@tspec 信号量模块测试
 *-@ttitle Pend信号量时，传入合法信号量句柄，等待时间非0，如果是在中断（软中断,硬中断）情况，Pend信号量失败，返回
 OS_ERRNO_SEM_Pend_INTERR
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Pend信号量时，传入合法信号量句柄，等待时间非0，如果是在中断（软中断,硬中断）情况，Pend信号量失败，返回
 OS_ERRNO_SEM_Pend_INTERR
 *-@texpect
 *-# PEND信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_012_swi(UINT32 uwValue)
 {

     UINT32 uwRet;

     uwRet = __SRE_SemPend(gs_uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_SEM_PEND_INTERR, uwRet);

     return;

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_012()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     SWI_INIT_PARA_S pstInitPara;
     SWI_PRIOR_T usPrior = 4;
     UINT32  uwInitValue = 0x01;
     UINT32  uwSwiHandle = 0;

     uwRet = __SRE_SemCreate(0,  &gs_uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     pstInitPara.pfnHandler =  UT__SRE_SemPend_012_swi;
     pstInitPara.pcSwiName = "Sem_UT";
     pstInitPara.usPriority = usPrior;
     pstInitPara.uwInitValue = uwInitValue;

     uwRet = __SRE_SwiCreate(&uwSwiHandle,&pstInitPara);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SwiActivate(uwSwiHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     uwRet = __SRE_SwiDelete(uwSwiHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(gs_uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

 }



 /**
 *@test UT_SRE_Sem_013
 *-@tspec 信号量模块测试
 *-@ttitle Pend信号量时，传入合法信号量句柄，等待时间非0，且不在中断（软中断,硬中断）情况下，如果任务被锁，Pend
 信号量失败，返回
 OS_ERRNO_SEM_Pend_IN_LOCK
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Pend信号量时，传入合法信号量句柄，等待时间非0，且不在中断（软中断,硬中断）情况下，如果任务被锁，Pend
 信号量失败，返回
 OS_ERRNO_SEM_Pend_IN_LOCK
 *-@texpect
 *-# PEND信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_013_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
     UINT32 uwTaskPID;

     __SRE_TaskLock();
     uwRet = __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_SEM_PEND_IN_LOCK, uwRet);
     __SRE_TaskUnlock();

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_013()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_013_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};


     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet , EXIT1);

     EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }




 /**
 *@test UT_SRE_Sem_014
 *-@tspec 信号量模块测试
 *-@ttitle Pend信号量时，传入合法信号量句柄，等待时间非0，且不在中断（软中断,硬中断）情况下，任务未被锁，等待时间为
 0xFFFFFFFF
 ，任务阻塞于信号量Pend,发生任务切换，直至信号量有空闲
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Pend信号量时，传入合法信号量句柄，等待时间非0，且不在中断（软中断,硬中断）情况下，任务未被锁，等待时间为0xFFFFFFFF
 ，任务阻塞于信号量Pend,发生任务切换，直至信号量有空闲
 *-@texpect
 *-# pend信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_014_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
     UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_014()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_014_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     __SRE_TaskDelay(10);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_015
 *-@tspec 信号量模块测试
 *-@ttitle Pend信号量时，传入合法信号量句柄，等待时间非0，且不在中断（软中断,硬中断）情况下，任务未被锁，等待时间为1～
 0xFFFFFFFE
 ，任务阻塞于信号量Pend,发生任务切换，如在等待时间内信号量未获取到，则Pend信号量失败，返回OS_ERRNO_SEM_TIMEOUT
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Pend信号量时，传入合法信号量句柄，等待时间非0，且不在中断（软中断,硬中断）情况下，任务未被锁，等待时间为1～
 0xFFFFFFFE
 ，任务阻塞于信号量Pend,发生任务切换，如在等待时间内信号量未获取到，则Pend信号量失败，返回OS_ERRNO_SEM_TIMEOUT
 *-@texpect
 *-# PEND信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_015_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
    UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, 0x10);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_SEM_TIMEOUT, uwRet);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_015()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_015_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);
     __SRE_TaskDelay(20);

 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_016
 *-@tspec 信号量模块测试
 *-@ttitle Pend信号量时，传入合法信号量句柄，等待时间非0，且不在中断（软中断,硬中断）情况下，任务未被锁，等待时间为1～
 0xFFFFFFFE
 ，任务阻塞于信号量Pend,发生任务切换，如在等待时间内有信号量空闲，Pend成功。
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Pend信号量时，传入合法信号量句柄，等待时间非0，且不在中断（软中断,硬中断）情况下，任务未被锁，等待时间为1～
 0xFFFFFFFE
 ，任务阻塞于信号量Pend,发生任务切换，如在等待时间内有信号量空闲，Pend成功。
 *-@texpect
 *-# PEND信号量成功
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_016_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
     UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, 0x20);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_016()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_016_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     __SRE_TaskDelay(10);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);
 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }



 /**
 *@test UT_SRE_Sem_017
 *-@tspec 信号量模块测试
 *-@ttitle Post信号量时，传入非法信号量句柄（大于配置信号量最大个数），Post信号量失败，返回返回OS_ERRNO_SEM_INVALID
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Post信号量时，传入非法信号量句柄（大于配置信号量最大个数），Post信号量失败，返回返回OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# POST信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_017()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_018
 *-@tspec 信号量模块测试
 *-@ttitle Post信号量时，传入非法信号量句柄（该信号量未被创建），Post信号量失败，返回OS_ERRNO_SEM_INVALID
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Post信号量时，传入非法信号量句柄（该信号量未被创建），Post信号量失败，返回OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# POST信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_018()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_019
 *-@tspec 信号量模块测试
 *-@ttitle Post信号量时，传入非法信号量句柄（信号量计数值为0XFFFFFFFE），Post信号量失败，返回OS_ERRNO_SEM_OVERFLOW
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Post信号量时，传入非法信号量句柄（信号量计数值为0XFFFFFFFE），Post信号量失败，返回OS_ERRNO_SEM_OVERFLOW
 *-@texpect
 *-# POST信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_019()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0XFFFFFFFE, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_020
 *-@tspec 信号量模块测试
 *-@ttitle Post信号量时，传入合法信号量句柄，如有任务阻塞于该信号量，恢复阻塞的第一个任务，发生任务切换。
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Post信号量时，传入合法信号量句柄，如有任务阻塞于该信号量，恢复阻塞的第一个任务，发生任务切换。
 *-@texpect
 *-# POST信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_020_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
    UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, 0x100);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
     if(uwRet == SRE_OK)
     {

         uart_printf("task1 pend sem success!");
     }

         uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_020_tsk2(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
    UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, 0x100);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
     if(uwRet == SRE_OK)
     {

         uart_printf("task2 pend sem success!");
     }

        uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_020()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_020_tsk1, 20, 0, {0}, 0x600, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam2 = {UT__SRE_SemPend_020_tsk2, 21, 0, {0}, 0x600, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     __SRE_TaskDelay(10);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);
 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }
     if (uwTaskPid2  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid2);
     }

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_021
 *-@tspec 信号量模块测试
 *-@ttitle Post信号量时，传入合法信号量句柄，没有任务阻塞于该信号量，信号量计数值+1。
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# Post信号量时，传入合法信号量句柄，没有任务阻塞于该信号量，信号量计数值+1。
 *-@texpect
 *-# POST信号量成功
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_021()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);


     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     ICUNIT_GOTO_EQUAL(uwSemCount, 1, uwSemCount, EXIT);

 EXIT:
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_022
 *-@tspec 信号量模块测试
 *-@ttitle 重设信号量计数值时，传入非法信号量句柄（大于配置信号量最大个数），重设信号量计数值失败，返回返回
 OS_ERRNO_SEM_INVALID
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 重设信号量计数值时，传入非法信号量句柄（大于配置信号量最大个数），重设信号量计数值失败，返回返回
 OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# RESET信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_022()
 {
     UINT32 uwRet;
     UINT32 uwCount;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemReset(uwSemHandle , 0);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_023
 *-@tspec 信号量模块测试
 *-@ttitle 重设信号量计数值时，传入非法信号量句柄（该信号量未被创建），重设信号量计数值失败，返回OS_ERRNO_SEM_INVALID
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 重设信号量计数值时，传入非法信号量句柄（该信号量未被创建），重设信号量计数值失败，返回OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# RESET信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_023()
 {
     UINT32 uwRet;
     UINT32 uwCount;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemReset(uwSemHandle , 0);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_024
 *-@tspec 信号量模块测试
 *-@ttitle 重设信号量计数值时，传入非法信号量句柄（信号量计数值为0XFFFFFFFF），重设信号量计数值失败，返回
 OS_ERRNO_SEM_OVERFLOW
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 重设信号量计数值时，传入非法信号量句柄（信号量计数值为0XFFFFFFFF），重设信号量计数值失败，返回OS_ERRNO_SEM_OVERFLOW
 *-@texpect
 *-# RESET信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_024()
 {
     UINT32 uwRet;
     UINT32 uwCount;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemReset(uwSemHandle, 0XFFFFFFFF);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet, EXIT);

     EXIT:
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_025
 *-@tspec 信号量模块测试
 *-@ttitle 重设信号量计数值时，传入合法信号量句柄，但有任务挂接在待重设的信号量链表中，重设信号量计数值失败，返回
 OS_ERRNO_SEM_PENDED
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 重设信号量计数值时，传入合法信号量句柄，但有任务挂接在待重设的信号量链表中，重设信号量计数值失败，返回
 OS_ERRNO_SEM_PENDED
 *-@texpect
 *-# reset信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_025_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
     uwRet = __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_025()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_016_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     uwRet = __SRE_SemReset(uwSemHandle, 1);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_PENDED, uwRet, EXIT1);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }



 /**
 *@test UT_SRE_Sem_026
 *-@tspec 信号量模块测试
 *-@ttitle
 重设信号量计数值时，传入合法信号量句柄，无任务挂接在待重设的信号量链表中，重设信号量计数值成功，信号量值修改为设定计数�
 �
 *-@tbrief
 *-#
 重设信号量计数值时，传入合法信号量句柄，无任务挂接在待重设的信号量链表中，重设信号量计数值成功，信号量值修改为设定计数�
 �
 *-@texpect
 *-# RESET信号量成功
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_026()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemReset(uwSemHandle, 1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(uwSemCount, 1, uwSemCount, EXIT);

     EXIT:
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_027
 *-@tspec 信号量模块测试
 *-@ttitle 获取指定信号量计数时，传入非法信号量句柄（大于配置信号量最大个数），获取指定信号量计数失败，返回返回
 OS_ERRNO_SEM_GET_COUNT_ERR
 *-@tbrief
 *-# 获取指定信号量计数时，传入非法信号量句柄（大于配置信号量最大个数），获取指定信号量计数失败，返回返回
 OS_ERRNO_SEM_GET_COUNT_ERR
 *-@texpect
 *-# 获取信号量计数失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_027()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_GET_COUNT_ERR, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_028
 *-@tspec 信号量模块测试
 *-@ttitle 获取指定信号量计数时，传入非法信号量句柄（该信号量未被创建），获取指定信号量计数失败，返回OS_ERRNO_SEM_GET_COUNT_ERR
 *-@tbrief
 *-# 获取指定信号量计数时，传入非法信号量句柄（该信号量未被创建），获取指定信号量计数失败，返回OS_ERRNO_SEM_GET_COUNT_ERR
 *-@texpect
 *-# 获取信号量计数失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_028()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_GET_COUNT_ERR, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_029
 *-@tspec 信号量模块测试
 *-@ttitle 获取指定信号量计数时，传入合法信号量句柄，获取指定信号量计数成功，返回该信号量计数值
 *-@tbrief
 *-# 获取指定信号量计数时，传入合法信号量句柄，获取指定信号量计数成功，返回该信号量计数值
 *-@texpect
 *-# 获取信号量计数成功
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_029()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     ICUNIT_GOTO_EQUAL(uwSemCount, 0, uwSemCount, EXIT);

     EXIT:
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);


     return ICUNIT_SUCCESS;
 }



 /**
 *-@test UT_SRE_Sem_030
 *-@tspec  信号量模块测试
 *-@ttitle  获取阻塞在指定核内信号量的任务PID清单时，传入非法信号量句柄（大于配置信号量最大个数），获取失败，返回
 *-@tbrief
 *-# 获取阻塞在指定核内信号量的任务PID清单时，传入非法信号量句柄（大于配置信号量最大个数），获取失败，返回
 *-@texpect
 *-# 获取失败
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_030()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[10];


     uwRet = __SRE_SemPendListGet(11, &uwTskCnt, auwPidBuf, sizeof(auwPidBuf));
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_031
 *-@tspec  信号量模块测试
 *-@ttitle  获取阻塞在指定核内信号量的任务PID清单时，传入非法信号量句柄（该信号量未被创建），获取失败，返回
 OS_ERRNO_SEM_INVALID
 *-@tbrief
 *-# 获取阻塞在指定核内信号量的任务PID清单时，传入非法信号量句柄（该信号量未被创建），获取失败，返回OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# 获取失败
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_031()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[10];


     uwRet = __SRE_SemPendListGet(2, &uwTskCnt, auwPidBuf, sizeof(auwPidBuf));
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_032
 *-@tspec  信号量模块测试
 *-@ttitle  获取阻塞在指定核内信号量的任务PID清单时，指定长度为0，获取失败，返回OS_ERRNO_SEM_INPUT_ERROR
 *-@tbrief
 *-# 获取阻塞在指定核内信号量的任务PID清单时，指定长度为0，获取失败，返回OS_ERRNO_SEM_INPUT_ERROR
 *-@texpect
 *-# 获取失败
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_032()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[10];

     uwRet = __SRE_SemPendListGet(2, &uwTskCnt, auwPidBuf, 0);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_ERROR, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_033
 *-@tspec  信号量模块测试
 *-@ttitle  获取阻塞在指定核内信号量的任务PID清单时，PEND在指定核内信号量的任务个数指针为NULL，获取失败，返回
 OS_ERRNO_SEM_INPUT_ERROR
 *-@tbrief
 *-# 获取阻塞在指定核内信号量的任务PID清单时，PEND在指定核内信号量的任务个数指针为NULL，获取失败，返回
 OS_ERRNO_SEM_INPUT_ERROR
 *-@texpect
 *-# 获取失败
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_033()
 {
     UINT32 uwRet;
     UINT32 auwPidBuf[10];

     uwRet = __SRE_SemPendListGet(2, NULL, auwPidBuf, sizeof(auwPidBuf));
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_ERROR, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_034
 *-@tspec  信号量模块测试
 *-@ttitle  获取阻塞在指定核内信号量的任务PID清单时，传入的存储任务PID的内存区域首地址非法（为NULL)，获取失败，返回
 OS_ERRNO_SEM_INPUT_ERROR
 *-@tbrief
 *-# 获取阻塞在指定核内信号量的任务PID清单时，传入的存储任务PID的内存区域首地址非法（为NULL)，获取失败，返回
 OS_ERRNO_SEM_INPUT_ERROR
 *-@texpect
 *-# 获取失败
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_034()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[10];

     uwRet = __SRE_SemPendListGet(2, &uwTskCnt, NULL, sizeof(auwPidBuf));
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_ERROR, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *-@test UT_SRE_Sem_035
 *-@tspec  信号量模块测试
 *-@ttitle  获取阻塞在指定核内信号量的任务PID清单时，获取的任务个数值非法（内存不足），获取失败，返回
 OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH
 *-@tbrief
 *-# 获取阻塞在指定核内信号量的任务PID清单时，获取的任务个数值非法（内存不足），获取失败，返回
 OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH
 *-@texpect
 *-# 获取失败
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPendListGet_035_tsk(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

     __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);

         uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_035()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[2];
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPendListGet_035_tsk, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam2 = {UT__SRE_SemPendListGet_035_tsk, 21, 0, {0}, 0x400, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);


     uwRet = __SRE_SemPendListGet(uwSemHandle, &uwTskCnt, auwPidBuf, sizeof(auwPidBuf[1]));
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH, uwRet, EXIT1);

     EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }
     if (uwTaskPid2  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid2);
     }

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_036
 *-@tspec  信号量模块测试
 *-@ttitle  获取阻塞在指定核内信号量的任务PID清单时，传入参数合法，且内存能存储所有PID清单，获取成功
 *-@tbrief
 *-# 获取阻塞在指定核内信号量的任务PID清单时，传入参数合法，且内存能存储所有PID清单，获取成功
 *-@texpect
 *-# 获取成功
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPendListGet_036_tsk(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

     __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_036()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[2];
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPendListGet_036_tsk, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam2 = {UT__SRE_SemPendListGet_036_tsk, 21, 0, {0}, 0x400, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);


     uwRet = __SRE_SemPendListGet(uwSemHandle, &uwTskCnt, auwPidBuf, sizeof(auwPidBuf));
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);
     ICUNIT_GOTO_EQUAL(uwTskCnt, 2, uwTskCnt, EXIT1);

     EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }
     if (uwTaskPid2  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid2);
     }

     return ICUNIT_SUCCESS;
 }


 /**
 *-@test UT_SRE_Sem_037
 *-@tspec
 *-@ttitle
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_037()
 {
     UINT32 uwRet;
     SEM_MOD_INFO_S stModInfo;

     stModInfo.usMaxNum = 0;

     uwRet = osSemRegister(&stModInfo);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_REG_ERROR, uwRet);

     stModInfo.usMaxNum = 10;

     uwRet = osSemRegister(&stModInfo);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *-@test UT_SRE_Sem_038
 *-@tspec
 *-@ttitle
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_038()
 {
     UINT32  uwRet;
     UINT16  usMaxNumBak = 0;

     usMaxNumBak = g_usMaxSem;

     g_usMaxSem = 0;

     uwRet = osSemInit();
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

      g_usMaxSem = 10;

     uwRet = osSemInit();
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     g_usMaxSem = usMaxNumBak;

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE__sem_init_039
 *-@tspec  获取阻塞于核内信号量上的任务清单
 *-@ttitle  空指针
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_039()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle;
     UINT32 uwCount;
     UINT32 *pstSemLisg;

     uwRet = __SRE_SemCreate(0xffffffff, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet);

     pstSemLisg  = (UINT32 *)g_stUnusedSemList.pstNext;

     g_stUnusedSemList.pstNext = &g_stUnusedSemList;

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_ALL_BUSY, uwRet);

     g_stUnusedSemList.pstNext = (struct tagListObject *)pstSemLisg;

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }

 /**
 *-@test UT_SRE_Sem_038
 *-@tspec  获取阻塞于核内信号量上的任务清单
 *-@ttitle  空指针
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_040()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle;
     UINT32 uwCount;
     SEM_CB_S *pstSemDeleted;
     UINT16 usCpySemStat;

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     pstSemDeleted = GET_SEM(uwSemHandle);
     usCpySemStat = pstSemDeleted->usSemStat;

     pstSemDeleted->usSemStat = 0;

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     pstSemDeleted->usSemStat = usCpySemStat;

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }


 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_041()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     SEM_CB_S  *pstSemPended;
     UINT32 uwCpyCnt = 0;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemPend(0xffff, OS_WAIT_FOREVER);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet, EXIT);

     pstSemPended = GET_SEM(uwSemHandle);

     uwCpyCnt = pstSemPended->uwSemCount;

     pstSemPended->uwSemCount = 1;

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     pstSemPended->uwSemCount = 0;

     uwRet = __SRE_SemPend(uwSemHandle, 0);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_UNAVAILABLE, uwRet, EXIT);

     pstSemPended->uwSemCount = uwCpyCnt;

 EXIT:
     pstSemPended->uwSemCount = uwCpyCnt;
     if (uwSemHandle != (UINT32)-1) __SRE_SemDelete(uwSemHandle);

     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_042()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     SEM_CB_S  *pstSemPosted;
     UINT32 uwCpyCnt = 0;
  //   LIST_OBJECT_S    *pstSemList;

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     pstSemPosted = GET_SEM(uwSemHandle);

     uwCpyCnt = pstSemPosted->uwSemCount;

     pstSemPosted->uwSemCount = OS_SEM_COUNT_MAX;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet, EXIT);

     pstSemPosted->uwSemCount = uwCpyCnt;

     __SRE_TaskLock();

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_PEND_IN_LOCK, uwRet, EXIT);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

 EXIT:

     pstSemPosted->uwSemCount = uwCpyCnt;
     __SRE_TaskUnlock();
     if (uwSemHandle != (UINT32)-1) __SRE_SemDelete(uwSemHandle);

     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_043()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle;
     UINT32 uwSemCount;

     uwRet = __SRE_SemCreate(1,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     __SRE_TaskLock();

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(uwSemCount, 0, uwSemCount, EXIT);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(uwSemCount, 1, uwSemCount, EXIT);

 EXIT:
     __SRE_TaskUnlock();
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_044()
 {
     UINT32 uwRet;

     uwRet = __SRE_SemCreate(2,   NULL);
     ICUNIT_ASSERT_NOT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_045()
 {
     UINT32 i;
     UINT32 j;
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle[OS_SEM_MAX_SUPPORT_NUM+1];

     for (i = 0; i < OS_SEM_MAX_SUPPORT_NUM; i++)
     {
         uwRet = __SRE_SemCreate(2,  &uwSemHandle[i]);
         j = i;
         ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, CLEAN_UP);
     }
     j = OS_SEM_MAX_SUPPORT_NUM;
     uwRet = __SRE_SemCreate(2,  &uwSemHandle[OS_SEM_MAX_SUPPORT_NUM]);
     ICUNIT_GOTO_EQUAL( uwRet, OS_ERRNO_SEM_ALL_BUSY, uwRet, CLEAN_UP);

 CLEAN_UP:
     for (i = 0; i < j; i++)
     {
       uwRet = __SRE_SemDelete(uwSemHandle[i]);
       ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     }

     return SRE_OK;
 }

 /**
 *@test UT_SRE_Sem_046
 *-@tspec 信号量模块测试
 *-@ttitle 创建信号量，传入uwCount为0xffffffff
 *-@tprecon 核内信号量模块开关打开
 *-@tbrief
 *-# 创建信号量
 *-@texpect
 *-# 创建信号量失败
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_046()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle;

     uwRet = __SRE_SemCreate(0xffffffff,  &uwSemHandle);
     ICUNIT_ASSERT_NOT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }


 /**
 *-@test UT_SRE_Sem_007
 *-@tspec  获取阻塞于核内信号量上的任务清单
 *-@ttitle  有任务阻塞于核内信号量
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_047()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     SEM_CB_S  *pstSemPosted;
     UINT32 uwCpyCnt = 0;
 ///  LIST_OBJECT_S    *pstSemList;
 //    TSK_CB_S  *pstRunTsk;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     pstSemPosted = GET_SEM(uwSemHandle);

     uwCpyCnt = pstSemPosted->uwSemCount;

     pstSemPosted->uwSemCount = OS_SEM_COUNT_MAX;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet, EXIT);

     pstSemPosted->uwSemCount = uwCpyCnt;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

 EXIT:
     pstSemPosted->uwSemCount = uwCpyCnt;
     if (uwSemHandle != (UINT32)-1) __SRE_SemDelete(uwSemHandle);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_048
 *-@tspec  获取阻塞于核内信号量上的任务清单
 *-@ttitle  有任务阻塞于核内信号量，但buf长度不足
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT VOID UT_SRE_Sem_048_tsk2(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet = 0;
    UINT32 uwTaskPID = 0;

     __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);

         uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT VOID UT_SRE_Sem_048_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet = 0;
    UINT32 uwTaskPID = 0;

     __SRE_SemPend(uwParam1, 10000);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_048()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[2] = {(UINT32)-1, (UINT32)-1};
     SEM_HANDLE_T   uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT_SRE_Sem_048_tsk2, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_INIT_PARAM_S stInitParam2 = {UT_SRE_Sem_048_tsk1, 18, 0, {0}, 0x400, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     //SRE_WaitForAllCores();

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemPendListGet(uwSemHandle, &uwTskCnt, auwPidBuf, 4);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(auwPidBuf[0], uwTaskPid1, auwPidBuf[0], EXIT);
     ICUNIT_GOTO_EQUAL(auwPidBuf[1], (UINT32)-1, auwPidBuf[1], EXIT);
     ICUNIT_GOTO_EQUAL(uwTskCnt, 2, uwTskCnt, EXIT);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

 EXIT:
     if (uwSemHandle  != (UINT32)-1) __SRE_SemDelete(uwSemHandle);
     if (uwTaskPid1   != (UINT32)-1) __SRE_TaskDelete(uwTaskPid1);
     if (uwTaskPid2   != (UINT32)-1) __SRE_TaskDelete(uwTaskPid2);
     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT VOID UT_SRE_Sem_049_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {

     UINT32 uwRet;
     UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(gs_uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_SEM_PEND_INTERR, uwRet);

     if (gs_uwSemHandle != (UINT32)-1)
     {
         __SRE_SemDelete(gs_uwSemHandle);
     }

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

     return;

 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_049()
 {
     UINT32 uwRet;
 //    UINT32 uwTskCnt;
 //    UINT32 auwPidBuf[2] = {(UINT32)-1, (UINT32)-1};
     SWI_INIT_PARA_S pstInitPara;
     SWI_PRIOR_T usPrior = 4;
     UINT32          uwInitValue = 0x01;
     UINT32          uwSwiHandle = 0;

     //SRE_WaitForAllCores();

     if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
     {
         uwRet = __SRE_SemCreate(0,  &gs_uwSemHandle);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

         pstInitPara.pfnHandler =  UT_SRE_Sem_049_tsk1;
         pstInitPara.pcSwiName = "Sem_UT";
         pstInitPara.usPriority = usPrior;
         pstInitPara.uwInitValue = uwInitValue;

         uwRet = __SRE_SwiCreate(&uwSwiHandle,&pstInitPara);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

         uwRet = __SRE_SwiActivate(uwSwiHandle);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
         uwRet = __SRE_SwiDelete(uwSwiHandle);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     }
     else
     {
         __SRE_TaskDelay(10);
     }
     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT VOID UT_SRE_Sem_050_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     TSK_CB_S  *pstRunTsk;
     UINT32 uwRet = 0;
     UINT32 uwTaskPID;

     pstRunTsk = (TSK_CB_S *)g_pRunningTask;

     pstRunTsk->usTaskStatus |= 0x10;

     __SRE_SemPend(uwParam1, OS_ERRNO_SEM_TIMEOUT);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_050()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[2] = {(UINT32)-1, (UINT32)-1};
     SEM_HANDLE_T   uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT_SRE_Sem_050_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_INIT_PARAM_S stInitParam2 = {UT_SRE_Sem_050_tsk1, 18, 0, {0}, 0x400, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     //SRE_WaitForAllCores();

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemPendListGet(uwSemHandle, &uwTskCnt, auwPidBuf, 4);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(auwPidBuf[0], uwTaskPid1, auwPidBuf[0], EXIT);
     ICUNIT_GOTO_EQUAL(auwPidBuf[1], (UINT32)-1, auwPidBuf[1], EXIT);
     ICUNIT_GOTO_EQUAL(uwTskCnt, 2, uwTskCnt, EXIT);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

 EXIT:
     if (uwSemHandle  != (UINT32)-1) __SRE_SemDelete(uwSemHandle);
     if (uwTaskPid1   != (UINT32)-1) __SRE_TaskDelete(uwTaskPid1);
     if (uwTaskPid2   != (UINT32)-1) __SRE_TaskDelete(uwTaskPid2);
     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_051()
  {
      UINT32 uwRet;
      SEM_HANDLE_T uwSemHandle = (UINT32)-1;

      uwRet = __SRE_SemCreate(1, &uwSemHandle);
      ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

      uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
      ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

      uwRet = __SRE_SemDelete(uwSemHandle);
      ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

      return ICUNIT_SUCCESS;
  }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_052()
  {
      UINT32 uwRet;
      SEM_MOD_INFO_S stModInfo;
      stModInfo.usMaxNum = 0;
      uwRet = osSemRegister(&stModInfo);
      ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_REG_ERROR, uwRet);
      return ICUNIT_SUCCESS;
  }
#if 0
OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_053()
{
    UINT32 uwRet;
    SETPEG_JMP_ST stRebootStub;
    UINT32 uvIntSave;
    SEM_CB_S *pstAllSem;

    uvIntSave = __SRE_IntLock();
    if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
    {
        pstAllSem = g_pstAllSem;
        SET_PEG(SRE_MemAllocAlign, UTest_MemAlloc_Sem_Stub, (SETPEG_JMP_ST *)&stRebootStub);

        uwRet = osSemInit();
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_NO_MEMORY, uwRet);
        g_pstAllSem = pstAllSem;
        CLEAN_PEG(SRE_MemAllocAlign, stRebootStub);
    }
    (VOID)__SRE_IntRestore(uvIntSave);
    return ICUNIT_SUCCESS;
}
#endif
OS_SEC_TEXT_UT VOID UT_SRE_sem(void)
 {

     iUINT32 uiSuiteId;
     TEST_ADD_SUITE(uiSuiteId, "UT_SRE__sem");

     TEST_ADD_CASE(UT_SRE_Sem_001, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_002, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_003, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_004, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_005, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_006, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_007, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_008, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_009, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_010, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_011, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_012, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_013, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_014, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_015, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_016, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_017, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_018, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_019, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_020, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_021, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_022, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_023, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_024, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_025, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_026, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_027, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_028, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_029, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_030, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_031, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_032, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_033, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_034, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_035, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_036, uiSuiteId, Label_RUN);
     /* ------------ 继承用例 -----------------------*/
     #if 0
     TEST_ADD_CASE(UT_SRE_Sem_037, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_038, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_039, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_040, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_041, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_042, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_043, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_044, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_045, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_046, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_047, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_048, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_049, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_050, uiSuiteId, Label_RUN);

     #endif

     TEST_ADD_CASE(UT_SRE_Sem_051, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_052, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_053, uiSuiteId, Label_RUN);
     Label_RUN:
          TEST_RUN_SUITE(uiSuiteId);
 }

#ifdef __cplusplus
#if __cplusplus
 }
#endif /* __cpluscplus */
#endif /* __cpluscplus */

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            





                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              