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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ����uniHuntByName�ӿڣ�����߳�PID�Ƿ�
*-@tbrief
1. ����uniHuntByName�ӿڣ�����߳�PID�Ƿ�
*-@texpect
1. ��ȡPIDʧ��,���ش�����
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ����uniHuntByName�ӿڣ���κ˺ŷǷ�
*-@tbrief
1. ����uniHuntByName�ӿڣ���κ˺ŷǷ�
*-@texpect
1. ��ȡPIDʧ��,���ش�����
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ����uniHuntByName�ӿڣ�����߳����ַǷ�
*-@tbrief
1. ����uniHuntByName�ӿڣ�����߳����ַǷ�
*-@texpect
1. ��ȡPIDʧ��,���ش�����
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ���������е������У�����uniHuntByName�ӿڣ���ȡ�����̵߳�PID
*-@tbrief
1. ���������е������У�����uniHuntByName�ӿڣ���ȡ�����̵߳�PID
*-@texpect
1. ��ȡPID�ɹ�
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI��XTENSA��FSL8156
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ����uniHuntByName����Ѿ�����������PID�ɹ�
*-@tbrief
*-# ��ȡ�Ѵ���������1PID
*-# ��ȡ�Ѵ���������2PID
*-@texpect
*-# ��ȡPID�ɹ�
*-# ��ȡPID�ɹ�
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ��ȡδ���������߳�PID
*-@tbrief
1. δ�������񣬵���uniHuntByName�ӿڣ���ȡ�����̵߳�PID
*-@texpect
1. ��ȡPIDʧ��
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI��XTENSA��FSL8156
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ����uniHuntByName����Ѿ�ɾ��������PIDʧ��
*-@tbrief
*-# ��ȡ��ɾ��������1PID
*-# ��ȡ��ɾ��������2PID
*-@texpect
*-# ��ȡPIDʧ��
*-# ��ȡPIDʧ��
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   �����ظ�������
*-@tbrief
*-# ��������1PID
*-# �ظ���������1PID
*-@texpect
*-#�ظ�����ʧ��
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ����uniHuntByName���idle����PID
*-@tbrief
1. ����uniHuntByName���idle����PID
*-@texpect
2. ��ȡPID�ɹ�
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI��XTENSA��FSL8156
 */
OS_SEC_TEXT_UT UINT32 UT_sreHunt_009()
{
    UINT32 uwTaskPID;
    CHAR  acCoreNo[4];
    CHAR  acTskName[OS_TSK_NAME_LEN];
    UINT32 uwPID;

    /*��ͬ�˴�����Idle��������ΪIdleCore+�˺�*/
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ���������е����ж��У�����uniHuntByName�ӿڣ���ȡ�����̵߳�PID
*-@tbrief
1. ���������е����ж��У�����uniHuntByName�ӿڣ���ȡ�����̵߳�PID
*-@texpect
1. ��ȡPID�ɹ�
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI��XTENSA��FSL8156
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ��ȡ�����ɹ������ж�PID
*-@tbrief
1.����һ�����жϣ���ȡ�����жϵ�PID
*-@texpect
1. ��ȡPID�ɹ�
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI��XTENSA��FSL8156
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ��ȡδ���������ж�PID
*-@tbrief
1.δ�������жϣ���ȡ���жϵ�PID
*-@texpect
1. ��ȡPIDʧ��
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI��XTENSA��FSL8156
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   ��ȡ��ɾ�������ж�PID
*-@tbrief
1.����һ�����жϣ�ɾ�����ȡ�����жϵ�PID
*-@texpect
1. ��ȡPIDʧ��
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI��XTENSA��FSL8156
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
*-@tspec    Huntģ�鲹�����
*-@ttitle   �����ظ������ж�
*-@tbrief
1.����һ�����жϣ� ���ø���Ϣ�ظ��������ж�
*-@texpect
1.�ظ�����ʧ��
*-@tprior 1
*-@tauto TRUE
*-@tremark LSI��XTENSA��FSL8156
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
        //TEST_ADD_CASE(UT_sreHunt_015, uiSuiteId, Label_RUN);//������Ϊ�ֶ��������򿪺�ᵼ�º��ڽṹ��������ա�
        //TEST_ADD_CASE(UT_sreHunt_016, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_sreHunt_017, uiSuiteId, Label_RUN); //���ܴ������⣬Ҫ���
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