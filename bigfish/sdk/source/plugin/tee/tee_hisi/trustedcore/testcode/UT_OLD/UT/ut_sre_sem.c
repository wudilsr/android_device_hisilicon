 /**
  * @file:
  *
  * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
  *
  * @description��
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
 *-@tspec �ź���ģ�����
 *-@ttitle �����ź����������ź�������ֵ�Ϸ���0 �� 0xFFFFFFFE)���ź�����������Ϸ�(��ΪNULL)�������ź����ɹ���
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# �����ź����������ź�������ֵ�Ϸ���0 �� 0xFFFFFFFE)���ź�����������Ϸ�(��ΪNULL)��
 *-@texpect
 *-# �����ź����ɹ�
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
 *-@tspec �ź���ģ�����
 *-@ttitle �����ź����������ź�������ֵ0XFFFFFFFF���ź�����������Ϸ�(��ΪNULL)�������ź���ʧ�ܡ�
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# �����ź����������ź�������ֵ0XFFFFFFFF���ź�����������Ϸ�(��ΪNULL)��
 *-@texpect
 *-# �����ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle �����ź����������ź�������ֵ�Ϸ���0 �� 0xFFFFFFFE)���ź����������ΪNULL�������ź���ʧ�ܡ�
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# �����ź����������ź�������ֵ0���ź����������ΪNULL
 *-@texpect
 *-# �����ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle �����ź��������������������֧�ֵ��ź��������ٴ����ź���ʱ������ʧ�ܣ����ش�����OS_ERRNO_SEM_ALL_BUSY��
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# �����ź��������������������֧�ֵ��ź��������ٴ����ź���
 *-@texpect
 *-# �����ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle ����һ���ź���������������ź��������ɾ�����ź������ź�������Ϸ���ɾ���ɹ�
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# ����һ���ź���������������ź��������ɾ�����ź������ź�������Ϸ���ɾ���ɹ�
 *-@texpect
 *-# ɾ���ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle ɾ���ź���������Ƿ��ź�����������ź���δ����������ɾ��ʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# ɾ���ź���������Ƿ��ź�����������ź���δ����������ɾ��ʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# ɾ���ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle ɾ���ź���������Ƿ��ź�����������ź���δ����������ɾ��ʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# ɾ���ź���������Ƿ��ź�����������ź���δ����������ɾ��ʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# ɾ���ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle ɾ���ź�����������ź�������Ϸ������ź�����������������ɾ��ʧ�ܣ�����OS_ERRNO_SEM_PendED
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# ɾ���ź�����������ź�������Ϸ������ź�����������������ɾ��ʧ�ܣ�����OS_ERRNO_SEM_PendED
 *-@texpect
 *-# ɾ���ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Pend�ź���ʱ������Ƿ��ź�����������������ź�������������Pend�ź���ʧ�ܣ����ط���OS_ERRNO_SEM_INVALID
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Pend�ź���ʱ������Ƿ��ź�����������������ź�������������Pend�ź���ʧ�ܣ����ط���OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# PEND�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Pend�ź���ʱ������Ƿ��ź�����������ź���δ����������Pend�ź���ʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Pend�ź���ʱ������Ƿ��ź�����������ź���δ����������Pend�ź���ʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# PEND�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ��Ϊ0��Pend�ź���ʧ�ܣ�����OS_ERRNO_SEM_UNAVAILABLE
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ��Ϊ0��Pend�ź���ʧ�ܣ�����OS_ERRNO_SEM_UNAVAILABLE
 *-@texpect
 *-# PEND�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0����������жϣ����ж�,Ӳ�жϣ������Pend�ź���ʧ�ܣ�����
 OS_ERRNO_SEM_Pend_INTERR
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0����������жϣ����ж�,Ӳ�жϣ������Pend�ź���ʧ�ܣ�����
 OS_ERRNO_SEM_Pend_INTERR
 *-@texpect
 *-# PEND�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0���Ҳ����жϣ����ж�,Ӳ�жϣ�����£������������Pend
 �ź���ʧ�ܣ�����
 OS_ERRNO_SEM_Pend_IN_LOCK
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0���Ҳ����жϣ����ж�,Ӳ�жϣ�����£������������Pend
 �ź���ʧ�ܣ�����
 OS_ERRNO_SEM_Pend_IN_LOCK
 *-@texpect
 *-# PEND�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0���Ҳ����жϣ����ж�,Ӳ�жϣ�����£�����δ�������ȴ�ʱ��Ϊ
 0xFFFFFFFF
 �������������ź���Pend,���������л���ֱ���ź����п���
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0���Ҳ����жϣ����ж�,Ӳ�жϣ�����£�����δ�������ȴ�ʱ��Ϊ0xFFFFFFFF
 �������������ź���Pend,���������л���ֱ���ź����п���
 *-@texpect
 *-# pend�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0���Ҳ����жϣ����ж�,Ӳ�жϣ�����£�����δ�������ȴ�ʱ��Ϊ1��
 0xFFFFFFFE
 �������������ź���Pend,���������л������ڵȴ�ʱ�����ź���δ��ȡ������Pend�ź���ʧ�ܣ�����OS_ERRNO_SEM_TIMEOUT
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0���Ҳ����жϣ����ж�,Ӳ�жϣ�����£�����δ�������ȴ�ʱ��Ϊ1��
 0xFFFFFFFE
 �������������ź���Pend,���������л������ڵȴ�ʱ�����ź���δ��ȡ������Pend�ź���ʧ�ܣ�����OS_ERRNO_SEM_TIMEOUT
 *-@texpect
 *-# PEND�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0���Ҳ����жϣ����ж�,Ӳ�жϣ�����£�����δ�������ȴ�ʱ��Ϊ1��
 0xFFFFFFFE
 �������������ź���Pend,���������л������ڵȴ�ʱ�������ź������У�Pend�ɹ���
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Pend�ź���ʱ������Ϸ��ź���������ȴ�ʱ���0���Ҳ����жϣ����ж�,Ӳ�жϣ�����£�����δ�������ȴ�ʱ��Ϊ1��
 0xFFFFFFFE
 �������������ź���Pend,���������л������ڵȴ�ʱ�������ź������У�Pend�ɹ���
 *-@texpect
 *-# PEND�ź����ɹ�
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
 *-@tspec �ź���ģ�����
 *-@ttitle Post�ź���ʱ������Ƿ��ź�����������������ź�������������Post�ź���ʧ�ܣ����ط���OS_ERRNO_SEM_INVALID
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Post�ź���ʱ������Ƿ��ź�����������������ź�������������Post�ź���ʧ�ܣ����ط���OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# POST�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Post�ź���ʱ������Ƿ��ź�����������ź���δ����������Post�ź���ʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Post�ź���ʱ������Ƿ��ź�����������ź���δ����������Post�ź���ʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# POST�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Post�ź���ʱ������Ƿ��ź���������ź�������ֵΪ0XFFFFFFFE����Post�ź���ʧ�ܣ�����OS_ERRNO_SEM_OVERFLOW
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Post�ź���ʱ������Ƿ��ź���������ź�������ֵΪ0XFFFFFFFE����Post�ź���ʧ�ܣ�����OS_ERRNO_SEM_OVERFLOW
 *-@texpect
 *-# POST�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Post�ź���ʱ������Ϸ��ź���������������������ڸ��ź������ָ������ĵ�һ�����񣬷��������л���
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Post�ź���ʱ������Ϸ��ź���������������������ڸ��ź������ָ������ĵ�һ�����񣬷��������л���
 *-@texpect
 *-# POST�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle Post�ź���ʱ������Ϸ��ź��������û�����������ڸ��ź������ź�������ֵ+1��
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# Post�ź���ʱ������Ϸ��ź��������û�����������ڸ��ź������ź�������ֵ+1��
 *-@texpect
 *-# POST�ź����ɹ�
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
 *-@tspec �ź���ģ�����
 *-@ttitle �����ź�������ֵʱ������Ƿ��ź�����������������ź������������������ź�������ֵʧ�ܣ����ط���
 OS_ERRNO_SEM_INVALID
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# �����ź�������ֵʱ������Ƿ��ź�����������������ź������������������ź�������ֵʧ�ܣ����ط���
 OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# RESET�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle �����ź�������ֵʱ������Ƿ��ź�����������ź���δ���������������ź�������ֵʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# �����ź�������ֵʱ������Ƿ��ź�����������ź���δ���������������ź�������ֵʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# RESET�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle �����ź�������ֵʱ������Ƿ��ź���������ź�������ֵΪ0XFFFFFFFF���������ź�������ֵʧ�ܣ�����
 OS_ERRNO_SEM_OVERFLOW
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# �����ź�������ֵʱ������Ƿ��ź���������ź�������ֵΪ0XFFFFFFFF���������ź�������ֵʧ�ܣ�����OS_ERRNO_SEM_OVERFLOW
 *-@texpect
 *-# RESET�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle �����ź�������ֵʱ������Ϸ��ź����������������ҽ��ڴ�������ź��������У������ź�������ֵʧ�ܣ�����
 OS_ERRNO_SEM_PENDED
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# �����ź�������ֵʱ������Ϸ��ź����������������ҽ��ڴ�������ź��������У������ź�������ֵʧ�ܣ�����
 OS_ERRNO_SEM_PENDED
 *-@texpect
 *-# reset�ź���ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle
 �����ź�������ֵʱ������Ϸ��ź��������������ҽ��ڴ�������ź��������У������ź�������ֵ�ɹ����ź���ֵ�޸�Ϊ�趨�����
 �
 *-@tbrief
 *-#
 �����ź�������ֵʱ������Ϸ��ź��������������ҽ��ڴ�������ź��������У������ź�������ֵ�ɹ����ź���ֵ�޸�Ϊ�趨�����
 �
 *-@texpect
 *-# RESET�ź����ɹ�
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
 *-@tspec �ź���ģ�����
 *-@ttitle ��ȡָ���ź�������ʱ������Ƿ��ź�����������������ź���������������ȡָ���ź�������ʧ�ܣ����ط���
 OS_ERRNO_SEM_GET_COUNT_ERR
 *-@tbrief
 *-# ��ȡָ���ź�������ʱ������Ƿ��ź�����������������ź���������������ȡָ���ź�������ʧ�ܣ����ط���
 OS_ERRNO_SEM_GET_COUNT_ERR
 *-@texpect
 *-# ��ȡ�ź�������ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle ��ȡָ���ź�������ʱ������Ƿ��ź�����������ź���δ������������ȡָ���ź�������ʧ�ܣ�����OS_ERRNO_SEM_GET_COUNT_ERR
 *-@tbrief
 *-# ��ȡָ���ź�������ʱ������Ƿ��ź�����������ź���δ������������ȡָ���ź�������ʧ�ܣ�����OS_ERRNO_SEM_GET_COUNT_ERR
 *-@texpect
 *-# ��ȡ�ź�������ʧ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle ��ȡָ���ź�������ʱ������Ϸ��ź����������ȡָ���ź��������ɹ������ظ��ź�������ֵ
 *-@tbrief
 *-# ��ȡָ���ź�������ʱ������Ϸ��ź����������ȡָ���ź��������ɹ������ظ��ź�������ֵ
 *-@texpect
 *-# ��ȡ�ź��������ɹ�
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
 *-@tspec  �ź���ģ�����
 *-@ttitle  ��ȡ������ָ�������ź���������PID�嵥ʱ������Ƿ��ź�����������������ź���������������ȡʧ�ܣ�����
 *-@tbrief
 *-# ��ȡ������ָ�������ź���������PID�嵥ʱ������Ƿ��ź�����������������ź���������������ȡʧ�ܣ�����
 *-@texpect
 *-# ��ȡʧ��
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
 *-@tspec  �ź���ģ�����
 *-@ttitle  ��ȡ������ָ�������ź���������PID�嵥ʱ������Ƿ��ź�����������ź���δ������������ȡʧ�ܣ�����
 OS_ERRNO_SEM_INVALID
 *-@tbrief
 *-# ��ȡ������ָ�������ź���������PID�嵥ʱ������Ƿ��ź�����������ź���δ������������ȡʧ�ܣ�����OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# ��ȡʧ��
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
 *-@tspec  �ź���ģ�����
 *-@ttitle  ��ȡ������ָ�������ź���������PID�嵥ʱ��ָ������Ϊ0����ȡʧ�ܣ�����OS_ERRNO_SEM_INPUT_ERROR
 *-@tbrief
 *-# ��ȡ������ָ�������ź���������PID�嵥ʱ��ָ������Ϊ0����ȡʧ�ܣ�����OS_ERRNO_SEM_INPUT_ERROR
 *-@texpect
 *-# ��ȡʧ��
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
 *-@tspec  �ź���ģ�����
 *-@ttitle  ��ȡ������ָ�������ź���������PID�嵥ʱ��PEND��ָ�������ź������������ָ��ΪNULL����ȡʧ�ܣ�����
 OS_ERRNO_SEM_INPUT_ERROR
 *-@tbrief
 *-# ��ȡ������ָ�������ź���������PID�嵥ʱ��PEND��ָ�������ź������������ָ��ΪNULL����ȡʧ�ܣ�����
 OS_ERRNO_SEM_INPUT_ERROR
 *-@texpect
 *-# ��ȡʧ��
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
 *-@tspec  �ź���ģ�����
 *-@ttitle  ��ȡ������ָ�������ź���������PID�嵥ʱ������Ĵ洢����PID���ڴ������׵�ַ�Ƿ���ΪNULL)����ȡʧ�ܣ�����
 OS_ERRNO_SEM_INPUT_ERROR
 *-@tbrief
 *-# ��ȡ������ָ�������ź���������PID�嵥ʱ������Ĵ洢����PID���ڴ������׵�ַ�Ƿ���ΪNULL)����ȡʧ�ܣ�����
 OS_ERRNO_SEM_INPUT_ERROR
 *-@texpect
 *-# ��ȡʧ��
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
 *-@tspec  �ź���ģ�����
 *-@ttitle  ��ȡ������ָ�������ź���������PID�嵥ʱ����ȡ���������ֵ�Ƿ����ڴ治�㣩����ȡʧ�ܣ�����
 OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH
 *-@tbrief
 *-# ��ȡ������ָ�������ź���������PID�嵥ʱ����ȡ���������ֵ�Ƿ����ڴ治�㣩����ȡʧ�ܣ�����
 OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH
 *-@texpect
 *-# ��ȡʧ��
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
 *-@tspec  �ź���ģ�����
 *-@ttitle  ��ȡ������ָ�������ź���������PID�嵥ʱ����������Ϸ������ڴ��ܴ洢����PID�嵥����ȡ�ɹ�
 *-@tbrief
 *-# ��ȡ������ָ�������ź���������PID�嵥ʱ����������Ϸ������ڴ��ܴ洢����PID�嵥����ȡ�ɹ�
 *-@texpect
 *-# ��ȡ�ɹ�
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
 *-@tspec  ��ȡ�����ں����ź����ϵ������嵥
 *-@ttitle  ��ָ��
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
 *-@tspec  ��ȡ�����ں����ź����ϵ������嵥
 *-@ttitle  ��ָ��
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
 *-@tspec �ź���ģ�����
 *-@ttitle �����ź���������uwCountΪ0xffffffff
 *-@tprecon �����ź���ģ�鿪�ش�
 *-@tbrief
 *-# �����ź���
 *-@texpect
 *-# �����ź���ʧ��
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
 *-@tspec  ��ȡ�����ں����ź����ϵ������嵥
 *-@ttitle  �����������ں����ź���
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
 *-@tspec  ��ȡ�����ں����ź����ϵ������嵥
 *-@ttitle  �����������ں����ź�������buf���Ȳ���
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
     /* ------------ �̳����� -----------------------*/
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