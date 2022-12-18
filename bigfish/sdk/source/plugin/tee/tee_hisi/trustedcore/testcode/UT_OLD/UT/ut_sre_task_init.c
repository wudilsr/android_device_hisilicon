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

//#include <string.h>
//#include <stdio.h>
//#include <assert.h>
#include "sre_base.h"
#include "sre_mem.h"
#include "sre_task.h"
#include "sre_task.ph"
#include "sre_swi.h"
#include "sre_sys.ph"
#include "sre_sys.h"
#include "iCunit.h"
#include "sre_hunt.h"
#include "sre_err.ph"
#include "sre_buildef.h"
#include "app_data_common.h"
//#include "set_peg.h"
#include "sre_msg.ph"
#if (OS_HARDWARE_PLATFORM == OS_RISC170 || OS_HARDWARE_PLATFORM == OS_DSP170)
#include "sre_asm.ph"
#else
//#include "sre_platform.ph"
#endif


#define TST_TSK_PRIOR_HIGH1            OS_TSK_PRIORITY_24
#define TST_TSK_PRIOR_LOW1             OS_TSK_PRIORITY_26

#define TST_TSK_INVALID_ID                     0x400
#define TST_TSK_INVALID_ID2                   7

#define TST_TSK_STACK_SIZE_ALIGN      16
#define TST_TSK_STACK_ADDR_ALIGN     8

#define TST_TSK_STACK_BLK1             0x80
#define TST_TSK_STACK_BLK2             0x100
#define TST_TSK_STACK_BLK3             0x180
#define TASK_PRIO_TEST  25

#define TST_TSK_IDLE                       (8<<SRE_GetCoreID()+g_uwIdleTaskID )
#define OS_HWI_TICK_INT_TASK      6

TSK_CONTEXT_S m_stContext[5];
UINT32 m_conIdx = 0;
CHAR m_acTstMemArea[0x200];
UINT32 m_uwInitTstTaskID;
UINT32 m_uwInitTstValue;
UINT32 m_uwTaskSwitch;

extern UINT32 osTskRegister(TSK_MOD_INFO_S *pstModInfo);
extern UINT32 osTskInit(VOID);
extern UINT32 osActivate(VOID);
extern VOID * osTskMemAlloc(UINT8 uchPartNo, UINT32 uwSize);
extern UINT32 osTskMemFree(VOID *pAddr, UINT32 uwSize);

extern LIST_OBJECT_S g_stTskRecyleList;
extern LIST_OBJECT_S g_stTskCBFreeList;
EXTERN_FAR TSK_ENTRY_FUNC g_pfnTskIdleEntry;
extern TSK_ENTRY_FUNC g_pfnTskIdleEntry;
extern TSK_STACK_BLK_S    m_stStackFree;
extern TSK_MOD_INFO_S  m_stTskModInfo;
extern CDA_INFO_S  *g_pstCdaInfoAddr;

extern TSK_HANDLE_T g_TestTskHandle;
extern TSK_HANDLE_T g_uwIdleTaskID;

OS_SEC_TEXT_UT VOID TST_InitTskEntry()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    m_uwInitTstValue++;

        uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT VOID TST_ViewTskContext(UINT32 A,UINT32 B,UINT32 C,UINT32 D)
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    SRE_TaskContextGet(m_uwInitTstTaskID, m_stContext + m_conIdx);
    m_conIdx++;
    __SRE_TaskResume(A);

        uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT VOID TST_ViewTskContext_01(UINT32 A,UINT32 B,UINT32 C,UINT32 D)
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;
    UINT32 uwTaskID;
    __SRE_TaskSelf(&uwTaskID);
    SRE_TaskContextGet((m_uwInitTstTaskID - uwTaskID), m_stContext + m_conIdx);
    m_conIdx++;
    __SRE_TaskResume(A);

        uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT VOID TST_TskSuspendEntry()
{
    UINT32 uwTaskID;

    (VOID)__SRE_TaskSelf(&uwTaskID);
    (VOID)__SRE_TaskSuspend(uwTaskID);
    (VOID)__SRE_TaskDelete(uwTaskID);
}

OS_SEC_TEXT_UT UINT32 TST_TskResumeHiEntry( UINT32 uwParam1,
                           UINT32 uwParam2,
                           UINT32 uwParam3,
                           UINT32 uwParam4 )
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    ICUNIT_ASSERT_EQUAL(uwParam1, 1, uwParam1);
    ICUNIT_ASSERT_EQUAL(uwParam2, 2, uwParam2);
    ICUNIT_ASSERT_EQUAL(uwParam3, 3, uwParam3);
    ICUNIT_ASSERT_EQUAL(uwParam4, 4, uwParam4);

    m_uwInitTstValue++;
    (VOID)__SRE_TaskResume(m_uwInitTstTaskID);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 TST_TskHook(UINT32 uwTaskID)
{
    (VOID)uwTaskID;

    m_uwInitTstValue += 10;

    return SRE_OK;
}

OS_SEC_TEXT_UT UINT32 TST_TskCreateHook(UINT32 uwTaskID)
{
    (VOID)uwTaskID;

    m_uwInitTstValue++;

    return SRE_OK;
}

#if 0
OS_SEC_TEXT_UT UINT32 TST_TskDeleteHook(UINT32 uwTaskID)
{
    UINT32 uwRet;
    (VOID)uwTaskID;

    m_uwInitTstValue++;
    __asm__ __volatile__("rsr %0,ps":"=a"(uwRet));


    ICUNIT_ASSERT_EQUAL(uwRet & 0xF, OS_INTLEVEL_HIGHEST, uwRet);
    return SRE_OK;
}
#endif

OS_SEC_TEXT_UT UINT32 TST_TskSwitchHook(UINT32 uwLastTaskID, UINT32 uwNextTaskID)
{
    (VOID)uwLastTaskID;
    (VOID)uwNextTaskID;

    m_uwInitTstValue++;

    return SRE_OK;
}

/**
*-@test UT_osTskRegister_001
*-@tspec  ����ģ������ע�Ṧ�ܺ�������
*-@ttitle  �趨����ģ�����ù��������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskRegister_001()
{
    UINT32 uwRet;
    TSK_MOD_INFO_S stModInfo;

    stModInfo.uwMaxNum = 0xFFFFFFFF;

    uwRet = osTskRegister(&stModInfo);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_CONFIG_TOO_MANY, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_osTskRegister_002
*-@tspec  ����ģ������ע�Ṧ�ܺ�������
*-@ttitle  �趨����ģ�����ù��������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskRegister_002()
{
    UINT32 uwRet;
    TSK_MOD_INFO_S stModInfo;
    UINT32 uwMaxNum;
    UINT32 uwDefaultSize;
    UINT32 uwIdleStackSize;
    UINT32 uwStackAreaAddr;
    UINT32 uwStackAreaSize;
    TSK_ENTRY_FUNC pfnTskIdleEntry;
    UINTPTR uvIntSave;

    uwMaxNum = m_stTskModInfo.uwMaxNum;
    uwDefaultSize = m_stTskModInfo.uwDefaultSize;
    uwIdleStackSize = m_stTskModInfo.uwIdleStackSize;
    uwStackAreaAddr = m_stTskModInfo.uwStackAreaAddr;
    uwStackAreaSize = m_stTskModInfo.uwStackAreaSize;
    pfnTskIdleEntry = g_pfnTskIdleEntry;

    stModInfo.uwMaxNum = OS_TSK_MAX_SUPPORT_NUM;
    stModInfo.uwDefaultSize = OS_TSK_DEFAULT_STACK_SIZE;
    stModInfo.uwIdleStackSize = OS_TSK_IDLE_STACK_SIZE;
    stModInfo.uwStackAreaAddr = 0x00000001;
    stModInfo.uwStackAreaSize = 0;

    uvIntSave = __SRE_IntLock();
    uwRet = osTskRegister(&stModInfo);

    m_stTskModInfo.uwMaxNum = uwMaxNum;
    m_stTskModInfo.uwDefaultSize = uwDefaultSize;
    m_stTskModInfo.uwIdleStackSize = uwIdleStackSize;
    m_stTskModInfo.uwStackAreaAddr = uwStackAreaAddr;
    m_stTskModInfo.uwStackAreaSize = uwStackAreaSize;
    g_pfnTskIdleEntry = pfnTskIdleEntry;

    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_STKAREA_TOO_SMALL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_osTskInit_001
*-@tspec  ����ģ���ʼ���������ܲ���
*-@ttitle  �趨����ģ�������ڴ�ʧ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskInit_001()
{
    UINT32 uwRet;
    UINT32 uwMaxNum;
    UINT32 uwTskMaxNum;
    UINT16 uwTaskMaxNum;
    volatile TSK_CB_S *pRunningTask;
    TSK_HANDLE_T uwTaskPID;
    TSK_STATUS_T usTaskStatus;
    TSK_PRIOR_T usPriority;
    TSK_CB_S *pstTskCBArray;
    UINTPTR uvIntSave;

    uwTskMaxNum = g_uwTskMaxNum;
    uwTaskMaxNum = g_pstCdaInfoAddr->usTaskMaxNum;
    pRunningTask = g_pRunningTask;
    uwTaskPID = g_pRunningTask->uwTaskPID;
    usTaskStatus = g_pRunningTask->usTaskStatus;
    usPriority = g_pRunningTask->usPriority;
    pstTskCBArray = g_pstTskCBArray;
    uwMaxNum = m_stTskModInfo.uwMaxNum;

    //���������������,����osTskInit���������,��TICK�жϴ��,����m_stTskModInfo.uwMaxNumֵ�Ƿ�,�������쳣
    uvIntSave = __SRE_IntLock();
    m_stTskModInfo.uwMaxNum = 0x00492490;

    uwRet = osTskInit();

    g_uwTskMaxNum = uwTskMaxNum;
    g_pstCdaInfoAddr->usTaskMaxNum = (UINT16)uwTaskMaxNum;
    g_pRunningTask = pRunningTask;
    g_pRunningTask->uwTaskPID = uwTaskPID;
    g_pRunningTask->usTaskStatus = usTaskStatus;
    g_pRunningTask->usPriority = usPriority;
    g_pstTskCBArray = pstTskCBArray;
    m_stTskModInfo.uwMaxNum = uwMaxNum;

    __SRE_IntRestore(uvIntSave);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NO_MEMORY, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_osTskMemAlloc_001
*-@tspec  ����ģ������ջ�ռ���书�ܺ�������
*-@ttitle  ����m_stStackFree����������ջ�ڴ�����ӿ�,Ҫ��config������ջ��ʼ��ַ���NULL
*-@tprecon
*-@tbrief
1����ջ�ռ�����0x20��С
2����ջ�ռ�����0x150��С
3������0x200��ջ�ռ䲻��������memAlloc����
4���ͷ�memAlloc������ڴ�
5���ָ��ֳ�
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskMemAlloc_001()
{
    UINT32 uwSize;
    UINT32 uwRet;
    UINT32 *pAddr;
    TSK_STACK_BLK_S *pstBlkNode;
    UINT32 *pAllocAddr;

    pAddr = (VOID *)ALIGN((UINT32)m_acTstMemArea, TST_TSK_STACK_SIZE_ALIGN);

    pstBlkNode = (TSK_STACK_BLK_S *)pAddr;

    pstBlkNode->uwAddr   = (UINT32)pAddr;
    pstBlkNode->uwSize   = 0x180;
    pstBlkNode->pstPrev  = &m_stStackFree;
    pstBlkNode->pstNext  = &m_stStackFree;
    m_stStackFree.pstNext = pstBlkNode;
    m_stStackFree.pstPrev = pstBlkNode;

    uwSize = 0x20;
    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, uwSize);
    ICUNIT_ASSERT_EQUAL((UINT32)pAllocAddr, (UINT32)pAddr + 0x160, (UINT32)pAllocAddr);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, 0x150);
    ICUNIT_ASSERT_EQUAL((UINT32)pAllocAddr, (UINT32)pAddr + 0x10, (UINT32)pAllocAddr);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, 0x200);
    ICUNIT_ASSERT_NOT_EQUAL((UINT32)pAllocAddr, 0, (UINT32)pAllocAddr);

    uwRet = osTskMemFree(pAllocAddr, 0x200);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    return ICUNIT_SUCCESS;

}

/**
*-@test UT_osTskMemAlloc_002
*-@tspec  ����ģ������ջ�ռ���书�ܺ�������
*-@ttitle  ����m_stStackFree����������ջ�ڴ�����ӿ�,Ҫ��config������ջ��ʼ��ַ���NULL
*-@tprecon
*-@tbrief
1����ջ�ռ�����0x20��С
2����ջ�ռ�����0x50��С
3����ջ�ռ�����0x50��С
4��free��2��0x50�ռ�
3������0x200��ջ�ռ䲻��������memAlloc����
4������0x50�ռ䣬��ʱ�ӵ�һ������ڴ�����
5������0x40�ռ䣬��ʱ�ӵ�һ������ڴ�����
6������0x40�ռ䣬��ʱ�ӵڶ�������ڴ�����
7���ָ��ֳ�
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskMemAlloc_002()
{
    UINT32 uwSize;
    UINT32 uwRet;
    UINT32 *pAddr;
    TSK_STACK_BLK_S *pstBlkNode;
    UINT32 *pAllocAddr;
    UINT32 *pAllocAddr1;
    UINT32 uwStartAddr;
    UINT32 uwStackSize;

    pAddr = (VOID *)ALIGN((UINT32)m_acTstMemArea, TST_TSK_STACK_SIZE_ALIGN);

    pstBlkNode = (TSK_STACK_BLK_S *)pAddr;

    pstBlkNode->uwAddr   = (UINT32)pAddr;
    pstBlkNode->uwSize   = 0x180;
    pstBlkNode->pstPrev  = &m_stStackFree;
    pstBlkNode->pstNext  = &m_stStackFree;
    m_stStackFree.pstNext = pstBlkNode;
    m_stStackFree.pstPrev = pstBlkNode;

    uwStartAddr = m_stTskModInfo.uwStackAreaAddr;
    uwStackSize = m_stTskModInfo.uwStackAreaSize;

    m_stTskModInfo.uwStackAreaAddr =(UINT32)pAddr;
    m_stTskModInfo.uwStackAreaSize = 0x180;

    uwSize = 0x20;
    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, uwSize);
    ICUNIT_ASSERT_EQUAL((UINT32)pAllocAddr, (UINT32)pAddr + 0x160, (UINT32)pAllocAddr);

    pAllocAddr1 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, 0x50);
    ICUNIT_ASSERT_EQUAL((UINT32)pAllocAddr1, (UINT32)pAddr + 0x110, (UINT32)pAllocAddr1);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, 0x50);
    ICUNIT_ASSERT_EQUAL((UINT32)pAllocAddr, (UINT32)pAddr + 0xC0, (UINT32)pAllocAddr);

    uwRet = osTskMemFree(pAllocAddr1, 0x50);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, 0x200);
    ICUNIT_ASSERT_NOT_EQUAL((UINT32)pAllocAddr, 0, (UINT32)pAllocAddr);

    uwRet = osTskMemFree(pAllocAddr, 0x200);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, 0x50);
    ICUNIT_ASSERT_EQUAL((UINT32)pAllocAddr, (UINT32)pAddr + 0x70, (UINT32)pAllocAddr);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, 0x40);
    ICUNIT_ASSERT_EQUAL((UINT32)pAllocAddr, (UINT32)pAddr + 0x30, (UINT32)pAllocAddr);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, 0x40);
    ICUNIT_ASSERT_EQUAL((UINT32)pAllocAddr, (UINT32)pAddr + 0x120, (UINT32)pAllocAddr);

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    m_stTskModInfo.uwStackAreaAddr = uwStartAddr;
    m_stTskModInfo.uwStackAreaSize = uwStackSize;
    return ICUNIT_SUCCESS;

}

/**
*-@test UT_osTskMemAlloc_003
*-@tspec  ����ģ������ջ�ռ���书�ܺ�������
*-@ttitle  ����m_stStackFree����������ջ�ڴ�����ӿ�,Ҫ��config������ջ��ʼ��ַ���NULL
*-@tprecon
*-@tbrief
1����ջ�ռ䣬����memAlloc����
2����ջ�ռ䣬����memAlloc����
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskMemAlloc_003()
{
    UINT32 uwSize;
    UINT32 uwRet;
    UINT32 *pAddr;
    TSK_STACK_BLK_S *pstBlkNode;
    UINT32 *pAllocAddr;

    uwSize = 0x20;
    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, uwSize);
    ICUNIT_ASSERT_NOT_EQUAL(pAllocAddr, NULL, pAllocAddr);

    uwRet = osTskMemFree(pAllocAddr, uwSize);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwSize = 0x120;
    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, uwSize);
    ICUNIT_ASSERT_NOT_EQUAL(pAllocAddr, NULL, pAllocAddr);

    uwRet = osTskMemFree(pAllocAddr, uwSize);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}


/**
*-@test UT_osTskMemFree_001
*-@tspec  ����ģ������ջ�ռ��ͷŹ��ܺ�������
*-@ttitle �ͷ�һ���ռ�Ȼ������������һ���ռ䣬�鿴������ַ�Ƿ���ͬ,Ҫ��config������ջ��ʼ��ַ���NULL
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskMemFree_001()
{
    UINT32 uwRet;
    VOID *pAllocAddr;

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_ASSERT_NOT_EQUAL(pAllocAddr, NULL, pAllocAddr);

    uwRet = osTskMemFree(pAllocAddr, TST_TSK_STACK_BLK1);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;

}

/**
*-@test UT_osTskMemFree_002
*-@tspec  ����ģ������ջ�ռ��ͷŹ��ܺ�������,Ҫ��config������ջ��ʼ��ַ���NULL
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskMemFree_002()
{
    UINT32 uwRet;
    VOID *pFreeAddr;
    VOID *pAllocAddr1;
    VOID *pAllocAddr2;
    UINT32 uwStartAddr;
    UINT32 uwSize;

    TSK_STACK_BLK_S stStackFreeBak = m_stStackFree;

    pFreeAddr = (VOID *)ALIGN((UINT32)m_acTstMemArea, TST_TSK_STACK_SIZE_ALIGN);

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    uwStartAddr = m_stTskModInfo.uwStackAreaAddr;
    uwSize = m_stTskModInfo.uwStackAreaSize;

    m_stTskModInfo.uwStackAreaAddr = (UINT32)pFreeAddr;
    m_stTskModInfo.uwStackAreaSize = 0x190;

    uwRet = osTskMemFree(pFreeAddr, TST_TSK_STACK_BLK2);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pAllocAddr2 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(pAllocAddr2, (VOID *)((UINT32)pFreeAddr + TST_TSK_STACK_BLK1), pAllocAddr2, EXIT);

    pAllocAddr1 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(pAllocAddr1, pFreeAddr, pAllocAddr1, EXIT);

EXIT:
    m_stTskModInfo.uwStackAreaAddr = uwStartAddr;
    m_stTskModInfo.uwStackAreaSize = uwSize;

    m_stStackFree = stStackFreeBak;
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_osTskMemFree_003
*-@tspec  ����ģ������ջ�ռ��ͷŹ��ܺ�������
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskMemFree_003()
{
    UINT32 uwRet;
    VOID *pFreeAddr;
    VOID *pAllocAddr;
    VOID *pAllocAddr1;
    VOID *pAllocAddr2;
    VOID *pAllocAddr3;
    UINT32 uwStartAddr;
    UINT32 uwSize;

    TSK_STACK_BLK_S stStackFreeBak = m_stStackFree;

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    pFreeAddr = (VOID *)ALIGN((UINT32)m_acTstMemArea, TST_TSK_STACK_SIZE_ALIGN);

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    uwStartAddr = m_stTskModInfo.uwStackAreaAddr;
    uwSize = m_stTskModInfo.uwStackAreaSize;

    m_stTskModInfo.uwStackAreaAddr = (UINT32)pFreeAddr;
    m_stTskModInfo.uwStackAreaSize = 0x190;

    uwRet = osTskMemFree(pFreeAddr, TST_TSK_STACK_BLK3);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pAllocAddr3 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(pAllocAddr3, (VOID *)((UINT32)pFreeAddr + TST_TSK_STACK_BLK2), pAllocAddr3, EXIT);

    pAllocAddr2 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(pAllocAddr2, (VOID *)((UINT32)pFreeAddr + TST_TSK_STACK_BLK1), pAllocAddr2, EXIT);

    pAllocAddr1 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(pAllocAddr1, pFreeAddr, pAllocAddr1, EXIT);

    uwRet = osTskMemFree(pAllocAddr1, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = osTskMemFree(pAllocAddr3, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = osTskMemFree(pAllocAddr2, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK3);
    ICUNIT_GOTO_EQUAL(pAllocAddr, pFreeAddr, pAllocAddr, EXIT);

EXIT:
    m_stTskModInfo.uwStackAreaAddr = uwStartAddr;
    m_stTskModInfo.uwStackAreaSize = uwSize;

    m_stStackFree = stStackFreeBak;
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_osTskMemFree_004
*-@tspec  ����ģ������ջ�ռ��ͷŹ��ܺ�������
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskMemFree_004()
{
    UINT32 uwRet;
    VOID *pFreeAddr;
    VOID *pAllocAddr;
    VOID *pAllocAddr1;
    VOID *pAllocAddr2;
    UINT32 uwStartAddr;
    UINT32 uwSize;

    TSK_STACK_BLK_S stStackFreeBak = m_stStackFree;

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    pFreeAddr = (VOID *)ALIGN((UINT32)m_acTstMemArea, TST_TSK_STACK_SIZE_ALIGN);

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    uwStartAddr = m_stTskModInfo.uwStackAreaAddr;
    uwSize = m_stTskModInfo.uwStackAreaSize;

    m_stTskModInfo.uwStackAreaAddr =(UINT32) pFreeAddr;
    m_stTskModInfo.uwStackAreaSize = 0x190;

    uwRet = osTskMemFree(pFreeAddr, TST_TSK_STACK_BLK2);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pAllocAddr2 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(pAllocAddr2, (VOID *)((UINT32)pFreeAddr + TST_TSK_STACK_BLK1), pAllocAddr2, EXIT);

    pAllocAddr1 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(pAllocAddr1, pFreeAddr, pAllocAddr1, EXIT);

    uwRet = osTskMemFree(pAllocAddr2, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = osTskMemFree(pAllocAddr1, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK2);
    ICUNIT_GOTO_EQUAL(pAllocAddr, pFreeAddr, pAllocAddr, EXIT);

EXIT:
    m_stTskModInfo.uwStackAreaAddr = uwStartAddr;
    m_stTskModInfo.uwStackAreaSize = uwSize;

    m_stStackFree = stStackFreeBak;
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_osTskMemFree_005
*-@tspec  ����ģ������ջ�ռ��ͷŹ��ܺ�������
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskMemFree_005()
{
    UINT32 uwRet;
    VOID *pFreeAddr;
    VOID *pAllocAddr;
    VOID *pAllocAddr1;
    VOID *pAllocAddr2;
    UINT32 uwStartAddr;
    UINT32 uwSize;

    TSK_STACK_BLK_S stStackFreeBak = m_stStackFree;

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    pFreeAddr = (VOID *)ALIGN((UINT32)m_acTstMemArea, TST_TSK_STACK_SIZE_ALIGN);

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    uwStartAddr = m_stTskModInfo.uwStackAreaAddr;
    uwSize = m_stTskModInfo.uwStackAreaSize;

    m_stTskModInfo.uwStackAreaAddr = (UINT32)pFreeAddr;
    m_stTskModInfo.uwStackAreaSize = 0x190;

    uwRet = osTskMemFree(pFreeAddr, TST_TSK_STACK_BLK2);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pAllocAddr1 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(pAllocAddr1, (VOID *)((UINT32)pFreeAddr + TST_TSK_STACK_BLK1), pAllocAddr1, EXIT);

    pAllocAddr2 = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(pAllocAddr2, pFreeAddr, pAllocAddr2, EXIT);

    uwRet = osTskMemFree(pAllocAddr2, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = osTskMemFree(pAllocAddr1, TST_TSK_STACK_BLK1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pAllocAddr = osTskMemAlloc(OS_MEM_DEFAULT_FSC_PT, TST_TSK_STACK_BLK2);
    ICUNIT_GOTO_EQUAL(pAllocAddr, pFreeAddr, pAllocAddr, EXIT);

EXIT:
    m_stTskModInfo.uwStackAreaAddr = uwStartAddr;
    m_stTskModInfo.uwStackAreaSize = uwSize;

    m_stStackFree = stStackFreeBak;
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_osTskMemFree_006
*-@tspec  ����ģ������ջ�ռ��ͷŹ��ܺ�������
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osTskMemFree_006()
{
    UINT32 uwRet;
    TSK_STACK_BLK_S stStackFree;

    TSK_STACK_BLK_S stStackFreeBak = m_stStackFree;

    m_stStackFree.pstNext = &m_stStackFree;
    m_stStackFree.pstPrev = &m_stStackFree;

    memcpy(&stStackFree, &m_stStackFree, sizeof(TSK_STACK_BLK_S));
    m_stStackFree.uwAddr  = 0;
    m_stStackFree.uwSize  = 0;
    m_stStackFree.pstPrev = &m_stStackFree;
    m_stStackFree.pstNext = &m_stStackFree;

    uwRet = osTskMemFree((VOID *)0xffffffff, 0); //���ܻᵼ�·��ʷǷ���ַ���쳣
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_TSK_FREE_STACK_FAILED, uwRet, EXIT);

    memcpy(&m_stStackFree, &stStackFree, sizeof(TSK_STACK_BLK_S));

EXIT:
    m_stStackFree = stStackFreeBak;
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskResume_001
*-@tspec  ���񼤻�����ԣ�
*-@ttitle  ���񼤻�ɹ�������idle����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_osActivate_001()
{
    UINT32 uwRet;
    TSK_ENTRY_FUNC pfnTskIdleEntry;

    //pfnTskIdleEntry = g_pfnTskIdleEntry;
    //g_pfnTskIdleEntry = NULL;

    uwRet = osActivate();

    //g_pfnTskIdleEntry = pfnTskIdleEntry;
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_HUNT_THREAD_NAME_REPEAT, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskResume_001
*-@tspec  ����ģ��ָ����������ܺ�������
*-@ttitle  �������������Ч
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskResume_001()
{
    UINT32 uwRet;

    UINT32 uwTaskID;

    uwTaskID = g_uwTskMaxNum + g_uwTskBaseID + 1;
    uwRet = __SRE_TaskResume((TSK_HANDLE_T)uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    uwTaskID = g_uwTskMaxNum + g_uwTskBaseID;
    uwRet = __SRE_TaskResume((TSK_HANDLE_T)uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    uwTaskID = g_uwTskMaxNum + g_uwTskBaseID - 1;
    uwRet = __SRE_TaskResume((TSK_HANDLE_T)uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);

    uwRet = __SRE_TaskResume(TST_TSK_INVALID_ID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskResume_002
*-@tspec  ����ģ��ָ����������ܺ�������
*-@ttitle  �ָ�δ�������񣬲鿴�����뷵���Ƿ���ȷ
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskResume_002()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskResume(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskResume_003
*-@tspec  ����ģ��ָ����������ܺ�������
*-@ttitle  �ָ���ǰ���񣬲鿴�Ƿ񷵻ص�ǰ����δ������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskResume_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID;

    (VOID)__SRE_TaskSelf(&uwTaskID);

    uwRet = __SRE_TaskResume(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_SUSPENDED, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskResume_004
*-@tspec  ����ģ��ָ����������ܺ�������
*-@ttitle  ����Ϸ�����������ͻ������鿴�ɹ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskResume_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_TskSuspendEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskResume(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskResume_005
*-@tspec  ����ģ��ָ���������API����
*-@ttitle  �����������Ϊδ��������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreGetTaskInfo()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 i;

    uart_printf("#####################################################\n");

    for (i = 0; i < OS_TSK_MAX_SUPPORT_NUM; i++)
    {
        uart_printf("pStackPointer = 0x%x\n", g_pstTskCBArray[i].pStackPointer);
        uart_printf("usTaskStatus = 0x%x\n", g_pstTskCBArray[i].usTaskStatus);
        uart_printf("uwTaskPID = 0x%x\n", g_pstTskCBArray[i].uwTaskPID);
    }

    return ICUNIT_SUCCESS;
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskResume_005()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 i;

    if (g_uwTskMaxNum > 2)
    {
        uwTaskID = g_uwTskBaseID + 2;
        uwRet = __SRE_TaskResume(uwTaskID);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);
        return ICUNIT_SUCCESS;
    }
    else
    {
        return ICUNIT_SUCCESS;
    }
}

/**
*-@test UT_sreTaskSuspend_001
*-@tspec  ����ģ����������ܺ�������
*-@ttitle  ������������ID�Ƿ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSuspend_001()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskSuspend(TST_TSK_INVALID_ID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    uwRet = __SRE_TaskSuspend(TST_TSK_INVALID_ID2);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSuspend_002
*-@tspec  ����ģ����������ܺ�������
*-@ttitle  ���ù��������IDΪIDLE����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSuspend_002()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskSuspend(g_uwIdleTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_OPERATE_IDLE, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSuspend_003
*-@tspec  ����ģ����������ܺ�������
*-@ttitle  �����Ѿ�ɾ�������񣬲鿴�Ƿ񷵻ظ�����δ����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSuspend_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset(&stInitParam, 0, sizeof(TSK_INIT_PARAM_S));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSuspend_004
*-@tspec  ����ģ����������ܺ�������
*-@ttitle  �����Ѿ���������񣬲鿴�Ƿ񷵻ظø������Ѿ�����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSuspend_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset(&stInitParam, 0, sizeof(TSK_INIT_PARAM_S));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ALREADY_SUSPENDED, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

#if 0
/**
*-@test UT_sreTaskSuspend_005
*-@tspec  ����ģ����������ܺ�������
*-@ttitle  �����Ѿ����������񣬲鿴�Ƿ񷵻ظ������Ѿ�����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
VOID Test_sreErrHandle(CHAR *pcFileName, UINT32 uwLineNo, UINT32 uwErrorNo, UINT32 uwParaLen, VOID  *pPara)
{
    ICUNIT_TRACK_EQUAL(uwErrorNo, OS_ERRNO_TSK_SUSPEND_LOCKED, uwErrorNo);
    return;
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskSuspend_005()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    SETPEG_JMP_ST stIncSave;

    uwRet = SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    SRE_TaskLock();

    //SRE_WaitForAllCores();

#if ((OS_CPU_TYPE != OS_SD6108) || (OS_HARDWARE_PLATFORM == OS_DSP170))  //08CPUƽ̨SRE_ErrHandle����L1��ÿ���˶���Ҫ��׮������ƽ̨����
    if(SRE_GetCoreID() == SRE_GetMasterCore())
#endif
    {
        SET_PEG(SRE_ErrHandle, Test_sreErrHandle, (SETPEG_JMP_ST *)&stIncSave);
    }

    //SRE_WaitForAllCores();

    if(SRE_GetCoreID() != SRE_GetMasterCore())
    {
        SRE_DCacheInv((VOID *)SRE_ErrHandle, 16, 1);
        SRE_ICacheInv((VOID *)SRE_ErrHandle, 16, 1);
    }

    uwRet = SRE_TaskSuspend(uwTaskID);
    ICUNIT_TRACK_EQUAL(uwRet, OS_ERRNO_TSK_SUSPEND_LOCKED, uwRet);

    //SRE_WaitForAllCores();

#if ((OS_CPU_TYPE != OS_SD6108) || (OS_HARDWARE_PLATFORM == OS_DSP170))  //08CPUƽ̨SRE_ErrHandle����L1��ÿ���˶���Ҫ��׮������ƽ̨����
    if(SRE_GetCoreID() == SRE_GetMasterCore())
#endif
    {
        CLEAN_PEG(SRE_ErrHandle, stIncSave);
    }

    //SRE_WaitForAllCores();
    if(SRE_GetCoreID() != SRE_GetMasterCore())
    {
        SRE_DCacheInv((VOID *)SRE_ErrHandle, 16, 1);
        SRE_ICacheInv((VOID *)SRE_ErrHandle, 16, 1);
    }

    SRE_TaskUnlock();
    return ICUNIT_SUCCESS;
}
#endif
/**
*-@test UT_sreTaskSuspend_006
*-@tspec  ����ģ����������ܺ�������
*-@ttitle  �ɹ���������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSuspend_006()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;
    TSK_CB_S *pstTcb;

    memset(&stInitParam, 0, sizeof(TSK_INIT_PARAM_S));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    pstTcb = GET_TCB_HANDLE(uwTaskID);
    ICUNIT_ASSERT_EQUAL(pstTcb->usTaskStatus & OS_TSK_SUSPEND, OS_TSK_SUSPEND, pstTcb->usTaskStatus);

    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSuspend_007
*-@tspec  ����ģ����������ܺ�������
*-@ttitle  ����ǰ������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskSuspend_007_f01()
{
    TSK_CB_S *pstTcb;
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    m_uwInitTstValue++;

    pstTcb = GET_TCB_HANDLE(m_uwInitTstTaskID);
    ICUNIT_ASSERT_EQUAL_VOID(pstTcb->usTaskStatus & OS_TSK_SUSPEND, OS_TSK_SUSPEND, pstTcb->usTaskStatus);

    (VOID)__SRE_TaskResume(m_uwInitTstTaskID);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);


    return ;
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskSuspend_007()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    m_uwInitTstValue = 0;

    memset(&stInitParam, 0, sizeof(TSK_INIT_PARAM_S));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_sreTaskSuspend_007_f01;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.auwArgs[0]   = 1;
    stInitParam.auwArgs[1]   = 2;
    stInitParam.auwArgs[2]   = 3;
    stInitParam.auwArgs[3]   = 4;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSelf(&m_uwInitTstTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(m_uwInitTstTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    m_uwInitTstValue = 0;
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTskSuspend_008
*-@tspec  ����ģ����������ܺ�������
*-@ttitle  ����ǰ������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSuspend_008()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_HANDLE_T puwTskID;
    TSK_INIT_PARAM_S stInitParam;

    uwRet = __SRE_TaskSuspend(g_uwIdleTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_OPERATE_IDLE, uwRet);

    puwTskID = COMPOSE_PID(SRE_GetCoreID(), (g_uwTskMaxNum+1));

    uwRet = __SRE_TaskSuspend(g_uwIdleTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_OPERATE_IDLE, uwRet);

    memset(&stInitParam, 0, sizeof(TSK_INIT_PARAM_S));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_TskResumeHiEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.auwArgs[0]   = 1;
    stInitParam.auwArgs[1]   = 2;
    stInitParam.auwArgs[2]   = 3;
    stInitParam.auwArgs[3]   = 4;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDelete_001
*-@tspec  ����ģ��ɾ�������ܺ�������
*-@ttitle  ��������ID��Ч
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDelete_001()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskDelete(TST_TSK_INVALID_ID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ID_INVALID, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDelete_002
*-@tspec  ����ģ��ɾ�������ܺ�������
*-@ttitle  ��������IDΪIDLE����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDelete_002()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskDelete(g_uwIdleTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_OPERATE_IDLE, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDelete_003
*-@tspec  ����ģ��ɾ�������ܺ�������
*-@ttitle  ɾ���Ѿ�ɾ�������񣬲鿴�Ƿ�������Ϊ����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDelete_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NOT_CREATED, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDelete_004
*-@tspec  ����ģ��ɾ�������ܺ�������
*-@ttitle  ɾ���Ѿ����������񣬲鿴�Ƿ񷵻ظ�ɾ����������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDelete_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;

    (VOID)__SRE_TaskSelf(&uwTaskID);

    (VOID)__SRE_TaskLock();

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_TRACK_EQUAL(uwRet, OS_ERRNO_TSK_DELETE_LOCKED, uwRet);

    (VOID)__SRE_TaskUnlock();

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDelete_005
*-@tspec  ����ģ��ɾ�������ܺ�������
*-@ttitle  ɾ���������Ϣ����Ϊ������񣬲鿴�Ƿ񷵻ظ�������Ϣ����Ϊ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDelete_005()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 uwMsgNum;
    TSK_CB_S *pstTaskCB;

    (VOID)__SRE_TaskSelf(&uwTaskID);

    pstTaskCB = GET_TCB_HANDLE(uwTaskID);
    uwMsgNum  = pstTaskCB->pstMsgQ[0].uwMsgNum;
    pstTaskCB->pstMsgQ[0].uwMsgNum = 1;

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_MSG_NONZERO, uwRet);

    pstTaskCB->pstMsgQ[0].uwMsgNum = uwMsgNum;

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreateHookAdd_001
*-@tspec  ����ģ��ע�����񴴽����Ӻ������ܲ���
*-@ttitle  �����������Ϊ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreateHookAdd_001()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskCreateHookAdd(NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreateHookAdd_002
*-@tspec  ����ģ��ע�����񴴽����Ӻ������ܲ���
*-@ttitle  ����������ȷ�Ĳ���
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreateHookAdd_002()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskCreateHookAdd(TST_TskCreateHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskCreateHookDelete(TST_TskCreateHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreateHookAdd_003
*-@tspec  ����ģ��ע�����񴴽����Ӻ������ܲ���
*-@ttitle  ע�������ӳ������ֵ
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreateHookAdd_003()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskCreateHookAdd(TST_TskCreateHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskCreateHookAdd(TST_TskHook);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_HOOK_IS_FULL, uwRet);

    uwRet = __SRE_TaskCreateHookDelete(TST_TskCreateHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreateHookAdd_004
*-@tspec  ����ģ��ע�����񴴽����Ӻ������ܲ���
*-@ttitle  �л��������ȼ����������лص�ǰ����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreateHookAdd_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    m_uwInitTstValue = 0;

    uwRet = __SRE_TaskCreateHookAdd(TST_TskCreateHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    uwRet = __SRE_TaskCreateHookDelete(TST_TskCreateHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

#if 0
/**
*-@test UT_sreTaskCreateHookAdd_005
*-@tspec  ����ģ��ע�����񴴽����Ӻ������ܲ���
*-@ttitle  ����������ȷ�Ĳ���
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
UINT32 TEST_osHookAdd(const OS_VOID_FUNC pfnHook,
                                       OS_VOID_FUNC apfHookTbl[],
                                       UINT32 *puwUsedEntries,
                                       const UINT32 uwMaxEntries)
{
    return OS_FAIL;
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskCreateHookAdd_005()
{
    UINT32 uwRet;
    SETPEG_JMP_ST stIncSave;
    SETPEG_JMP_ST stIncSave1;

    //SRE_WaitForAllCores();
    if (SRE_GetCoreID() == SRE_GetMasterCore())
    {

        SET_PEG(osHookAdd, TEST_osHookAdd, (SETPEG_JMP_ST *)&stIncSave);
        SET_PEG(osHookDel, TEST_osHookAdd, (SETPEG_JMP_ST *)&stIncSave1);


        uwRet = SRE_TaskCreateHookAdd(TST_TskCreateHook);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_HOOK_IS_FULL, uwRet);

        uwRet = SRE_TaskCreateHookDelete(TST_TskCreateHook);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_HOOK_NOT_MATCH, uwRet);

        CLEAN_PEG(osHookAdd, stIncSave);
        CLEAN_PEG(osHookDel, stIncSave1);
    }
    //SRE_WaitForAllCores();

    return ICUNIT_SUCCESS;
}
#endif
/**
*-@test UT_sreTaskCreateHookDelete_001
*-@tspec  ����ģ��ɾ�������Ӻ������ܲ���
*-@ttitle  ������֤
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreateHookDelete_001()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskCreateHookAdd(TST_TskCreateHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskCreateHookDelete(TST_TskHook);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_HOOK_NOT_MATCH, uwRet);

    uwRet = __SRE_TaskCreateHookDelete(TST_TskCreateHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDeleteHookAdd_001
*-@tspec  ����ģ��ע������ɾ�����Ӻ������ܲ���
*-@ttitle  ���ù��Ӻ���Ϊ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDeleteHookAdd_001()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskDeleteHookAdd(NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);
    return ICUNIT_SUCCESS;
}
#if 0
/**
*-@test UT_sreTaskDeleteHookAdd_002
*-@tspec  ����ģ��ע������ɾ�����Ӻ������ܲ���
*-@ttitle  ���úϷ��Ĳ������鿴�Ƿ�ע��ɹ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDeleteHookAdd_002()
{
    UINT32 uwRet;

    uwRet = SRE_TaskDeleteHookAdd(TST_TskDeleteHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskDeleteHookDelete(TST_TskDeleteHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDeleteHookAdd_003
*-@tspec  ����ģ��ע������ɾ�����Ӻ������ܲ���
*-@ttitle  ע�����������ֵ
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDeleteHookAdd_003()
{
    UINT32 uwRet;

    uwRet = SRE_TaskDeleteHookAdd(TST_TskDeleteHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskDeleteHookAdd(TST_TskHook);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_HOOK_IS_FULL, uwRet);

    uwRet = SRE_TaskDeleteHookDelete(TST_TskDeleteHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDeleteHookAdd_004
*-@tspec  ����ģ��ע������ɾ�����Ӻ������ܲ���
*-@ttitle  �л��������ȼ���Ȼ���л��ص�ǰ����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDeleteHookAdd_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    m_uwInitTstValue = 0;

    uwRet = SRE_TaskDeleteHookAdd(TST_TskDeleteHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    memset(&stInitParam, 0, sizeof(TSK_INIT_PARAM_S));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    ICUNIT_ASSERT_EQUAL(m_uwInitTstValue, 0, m_uwInitTstValue);

    uwRet = SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    ICUNIT_ASSERT_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue);

    uwRet = SRE_TaskDeleteHookDelete(TST_TskDeleteHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskDeleteHookDelete_001
*-@tspec  ����ģ��ȡ��ָ������ɾ�����Ӻ������ܲ���
*-@ttitle  �����Ϸ��Բ���
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskDeleteHookDelete_001()
{
    UINT32 uwRet;

    uwRet = SRE_TaskDeleteHookAdd(TST_TskDeleteHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskDeleteHookDelete(TST_TskHook);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_HOOK_NOT_MATCH, uwRet);

    uwRet = SRE_TaskDeleteHookDelete(TST_TskDeleteHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSwitchHookAdd_001
*-@tspec  ����ģ��ע�������л����Ӻ������ܲ���
*-@ttitle  �����������Ϊ�գ��鿴�Ƿ񷵻ز���Ϊ�յĴ�����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSwitchHookAdd_001()
{
    UINT32 uwRet;

    uwRet = SRE_TaskSwitchHookAdd(NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSwitchHookAdd_002
*-@tspec  ����ģ��ע�������л����Ӻ������ܲ���
*-@ttitle  ����Ϸ��Ĳ������鿴ע�������л����Ӻ����Ƿ�ɹ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSwitchHookAdd_002()
{
    UINT32 uwRet;

    uwRet = SRE_TaskSwitchHookAdd(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(g_vuwUniFlag & OS_FLG_TSK_SWHK, OS_FLG_TSK_SWHK, g_vuwUniFlag);

    uwRet = SRE_TaskSwitchHookDelete(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSwitchHookAdd_003
*-@tspec  ����ģ��ע�������л����Ӻ������ܲ���
*-@ttitle  ע��2�������л����Ӻ������鿴�Ƿ�ɹ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSwitchHookAdd_003()
{
    UINT32 uwRet;

    uwRet = SRE_TaskSwitchHookAdd(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskSwitchHookAdd((TSK_SWITCH_HOOK)TST_TskHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskSwitchHookDelete(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskSwitchHookDelete((TSK_SWITCH_HOOK)TST_TskHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSwitchHookAdd_004
*-@tspec  ����ģ��ע�������л����Ӻ������ܲ���
*-@ttitle  ��������ȼ��������лص�ǰ���񣬲鿴�Ƿ�ɹ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSwitchHookAdd_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    m_uwInitTstValue = 0;

    uwRet = SRE_TaskSwitchHookAdd(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_TskSuspendEntry;
    stInitParam.usTaskPrio   = OS_TSK_PRIORITY_HIGHEST;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask10";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 2, m_uwInitTstValue, EXIT); /* ����Hi�����лص�ǰ���� */

    uwRet = SRE_TaskDelete(uwTaskID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    uwRet = SRE_TaskSwitchHookDelete(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSwitchHookAdd_005
*-@tspec  ����ģ��ע�������л����Ӻ������ܲ���
*-@ttitle  �����л������м������жϣ����Ƿ�ɹ������������ɺ󣬼������жϣ����Ƿ�ɹ���
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskSwitchHookAdd_005_f01()
{
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSwitchHookAdd_005_f02(UINT32 uwLastTaskID, UINT32 uwNextTaskID)
{
    UINT32 uwRet;
    (VOID)uwLastTaskID;
    (VOID)uwNextTaskID;

    m_uwInitTstValue++;
    ICUNIT_ASSERT_EQUAL_VOID(m_uwInitTstValue, 1, m_uwInitTstValue);
    ICUNIT_ASSERT_EQUAL_VOID(g_vuwUniFlag & OS_FLG_SYS_ACTIVE, OS_FLG_SYS_ACTIVE, g_vuwUniFlag);

    uwRet = SRE_TaskSwitchHookDelete(UT_sreTaskSwitchHookAdd_005_f02);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = SRE_SwiActivate(m_uwTaskSwitch);
    ICUNIT_ASSERT_EQUAL_VOID(m_uwInitTstValue, 1, m_uwInitTstValue);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
}

OS_SEC_TEXT_UT VOID UT_sreTaskSwitchHookAdd_005_f03()
{
    UINT32 uwRet;

    uwRet = SRE_TaskResume(g_TestTskHandle);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskSwitchHookAdd_005()
{
    UINT32 uwRet;
    SWI_PRIOR_T usPrior;
    SWI_INIT_PARA_S stInitPara;
    TSK_INIT_PARAM_S stInitParam;
    UINT32 uwTaskID;
    UINTPTR uvIntSave;

    m_uwInitTstValue = 0;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    uwRet = SRE_TaskSwitchHookAdd(UT_sreTaskSwitchHookAdd_005_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_sreTaskSwitchHookAdd_005_f03;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask01";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT2);

    usPrior = 12;
    stInitPara.pcSwiName  = "ut_taskswith";
    stInitPara.usPriority = usPrior;
    stInitPara.pfnHandler = UT_sreTaskSwitchHookAdd_005_f01;
    stInitPara.uwInitValue = 0x1234;

    uwRet = SRE_SwiCreate(&m_uwTaskSwitch, &stInitPara);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT);

    uvIntSave = SRE_HwiDisable(OS_HWI_TICK_INT_TASK);

    uwRet = SRE_TaskSuspend(g_TestTskHandle);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet,EXIT1);
    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT1);
    ICUNIT_ASSERT_EQUAL_VOID(g_vuwUniFlag & OS_FLG_SYS_ACTIVE, 0, g_vuwUniFlag);

    uwRet = SRE_SwiActivate(m_uwTaskSwitch);
    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 2, m_uwInitTstValue, EXIT1);

    SRE_HwiRestore(OS_HWI_TICK_INT_TASK, uvIntSave);

    uwRet = SRE_SwiDelete(m_uwTaskSwitch);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
EXIT1:
    uwRet = SRE_SwiDelete(m_uwTaskSwitch);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskSwitchHookDelete(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    SRE_HwiRestore(OS_HWI_TICK_INT_TASK, uvIntSave);
    return ICUNIT_SUCCESS;
EXIT2:
    uwRet = SRE_TaskSwitchHookDelete(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;

EXIT:
    uwRet = SRE_TaskSwitchHookDelete(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskSwitchHookDelete_001
*-@tspec  ����ģ��ɾ��ָ�������л����Ӻ������ܲ���
*-@ttitle  ������֤
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskSwitchHookDelete_001()
{
    UINT32 uwRet;

    uwRet = SRE_TaskSwitchHookAdd(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskSwitchHookDelete((TSK_SWITCH_HOOK)TST_TskHook);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_HOOK_NOT_MATCH, uwRet);

    uwRet = SRE_TaskSwitchHookDelete(TST_TskSwitchHook);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskHookAdd_001
*-@tspec  ����ģ��ע�������Ӻ������ܲ���
*-@ttitle  ���úϷ�������������鿴ע���������Ƿ�ɹ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskHookAdd_001()
{
    TSK_HOOK pfnHook = (TSK_HOOK)0x1234;
    TSK_HOOK apfHookTbl[4];
    UINT32   uwUsedEntries = 0;
    UINT32   uwRet;

    uwRet = osHookAdd((void*)pfnHook, (void*)apfHookTbl, &uwUsedEntries, sizeof(apfHookTbl)/sizeof(apfHookTbl[0]));
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(uwUsedEntries, 1, uwUsedEntries);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskHookAdd_002
*-@tspec  ����ģ��ע�������Ӻ������ܲ���
*-@ttitle  ���ÿյ������Ӻ������鿴�Ƿ񷵻ز���Ϊ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskHookAdd_002()
{
    TSK_HOOK pfnHook = NULL;
    TSK_HOOK apfHookTbl[4];
    UINT32   uwUsedEntries = 0;
    UINT32   uwRet;

    uwRet = osHookAdd((void*)pfnHook, (void*)apfHookTbl, &uwUsedEntries, sizeof(apfHookTbl)/sizeof(apfHookTbl[0]));
    ICUNIT_ASSERT_EQUAL(uwRet, OS_FAIL, uwRet);
    ICUNIT_ASSERT_EQUAL(uwUsedEntries, 0, uwUsedEntries);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskHookAdd_003
*-@tspec  ����ģ��ע�������Ӻ������ܲ���
*-@ttitle  ���Ӻ���ע��ʧ��, ������������ע�����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskHookAdd_003()
{
    TSK_HOOK pfnHook = (TSK_HOOK)0x1234;
    TSK_HOOK apfHookTbl[4];
    UINT32   uwUsedEntries = sizeof(apfHookTbl)/sizeof(apfHookTbl[0]);
    UINT32   uwRet;

    uwRet = osHookAdd((void*)pfnHook, (void*)apfHookTbl, &uwUsedEntries, sizeof(apfHookTbl)/sizeof(apfHookTbl[0]));
    ICUNIT_ASSERT_EQUAL(uwRet, OS_FAIL, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskHookDel_001
*-@tspec  ����ģ��ɾ�������ӹ��ܺ�������
*-@ttitle  ���Ӻ���ɾ��ʧ��, �����ڵĹ��Ӻ���
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskHookDel_001()
{
    TSK_HOOK pfnHook = NULL;
    TSK_HOOK apfHookTbl[4] = {(TSK_HOOK)0x1234, (TSK_HOOK)0x5678, (TSK_HOOK)0x1000, (TSK_HOOK)0x2000};
    UINT32   uwUsedEntries = sizeof(apfHookTbl)/sizeof(apfHookTbl[0]);
    UINT32   uwRet;

    uwRet = osHookDel((void*)pfnHook, (void*)apfHookTbl, &uwUsedEntries);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_FAIL, uwRet);

    uwUsedEntries = 0;
    pfnHook = (TSK_HOOK)0x1234;
    uwRet = osHookDel((void*)pfnHook, (void*)apfHookTbl, &uwUsedEntries);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_FAIL, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskHookDel_002
*-@tspec  ����ģ��ɾ�������ӹ��ܺ�������
*-@ttitle  ���Ӻ���ɾ���ɹ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskHookDel_002()
{
    TSK_HOOK pfnHook = (TSK_HOOK)0x2000;
    TSK_HOOK apfHookTbl[4] = {(TSK_HOOK)0x1234, (TSK_HOOK)0x5678, (TSK_HOOK)0x1000, (TSK_HOOK)0x2000};
    UINT32   uwUsedEntries = sizeof(apfHookTbl)/sizeof(apfHookTbl[0]);
    UINT32   uwRet;

    uwRet = osHookDel((void*)pfnHook, (void*)apfHookTbl, &uwUsedEntries);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(uwUsedEntries, 3, uwUsedEntries);
    ICUNIT_ASSERT_EQUAL(apfHookTbl[1], (TSK_HOOK)0x5678, apfHookTbl[1]);
    ICUNIT_ASSERT_EQUAL(apfHookTbl[3], NULL, apfHookTbl[3]);

    pfnHook = (TSK_HOOK)0x1234;
    uwRet = osHookDel((void*)pfnHook, (void*)apfHookTbl, &uwUsedEntries);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(uwUsedEntries, 2, uwUsedEntries);
    ICUNIT_ASSERT_EQUAL(apfHookTbl[0], (TSK_HOOK)0x5678, apfHookTbl[0]);
    ICUNIT_ASSERT_EQUAL(apfHookTbl[2], NULL, apfHookTbl[2]);
    return ICUNIT_SUCCESS;
}
#endif
/**
*-@test UT_sreTaskCreate_001
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  �ɹ���������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_001()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask01";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_002
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  �������������ȴ���11������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_002()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName = "StoryTestTask01";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_003
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ������������������ǰ11���ַ���ͬ
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_003()
{
    UINT32 uwRet;
    UINT32 uwTaskID[2];
    TSK_INIT_PARAM_S stInitParam[2];

    memset((VOID*)stInitParam, 0, sizeof(stInitParam));

    stInitParam[0].pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam[0].usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam[0].uwStackSize  = 0;
    stInitParam[0].pcName       = "StoryTstTsk16c_01";
    stInitParam[0].uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID[0], &stInitParam[0]);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitParam[1].pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam[1].usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam[1].uwStackSize  = 0;
    stInitParam[1].pcName       = "StoryTstTsk16c_02";
    stInitParam[1].uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID[1], &stInitParam[1]);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_HUNT_THREAD_NAME_REPEAT, uwRet);
    uwRet = __SRE_TaskDelete(uwTaskID[0]);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    uwRet = __SRE_TaskDelete(uwTaskID[1]);
    ICUNIT_ASSERT_NOT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_004
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ����������Ϊ"\0"������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_004()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "\0";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NAME_EMPTY, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_005
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  �������ֵ�һ����ĸΪ\0
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_005()
{
    UINT32 uwRet;
    UINT32 uwTaskID[2];
    TSK_INIT_PARAM_S stInitParam[2];

    memset((VOID*)stInitParam, 0, sizeof(stInitParam));

    stInitParam[0].pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam[0].usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam[0].uwStackSize  = 0;
    stInitParam[0].pcName       = "TstTask01";
    stInitParam[0].uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID[0], &stInitParam[0]);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    stInitParam[1].pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam[1].usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam[1].uwStackSize  = 0;
    stInitParam[1].pcName       = "\0stTask01";
    stInitParam[1].uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID[1], &stInitParam[1]);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NAME_EMPTY, uwRet);

    uwRet = __SRE_TaskDelete(uwTaskID[0]);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_006
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ��ָ��������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_006()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;
    CHAR aucName[12];

    aucName[0] = '\0';

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = aucName;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NAME_EMPTY, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_007
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ����һ�������ȼ������ȡ����������������Ϣ
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_007()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    m_conIdx = 0;
    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_ViewTskContext;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.auwArgs[0]   = uwTaskID;
    stInitParam.pcName       = "TstTask01";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&m_uwInitTstTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(uwTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(m_conIdx, 1, m_conIdx);

    uwRet = __SRE_TaskDelete(m_uwInitTstTaskID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    m_conIdx = 0;

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_008
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ����һ�������ȼ������ȡ����������������Ϣ
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_008()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_ViewTskContext;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask01";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    __SRE_TaskLock();
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_TRACK_EQUAL(uwRet, SRE_OK, uwRet);

    m_uwInitTstTaskID = uwTaskID;
    __SRE_TaskUnlock();

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_009
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ���������������ȡ����������������Ϣ
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_009()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    UINT32 uwBackID;
    TSK_INIT_PARAM_S stInitParam;


    uwRet = __SRE_TaskSelf(&uwBackID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_ViewTskContext_01;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.auwArgs[0]   = uwBackID;
    stInitParam.pcName       = "TstTask01";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    m_uwInitTstTaskID = uwTaskID;

    strcpy(stInitParam.pcName,"TstTask02");

    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    m_uwInitTstTaskID += uwTaskID;

    __SRE_TaskSuspend(uwBackID);

    __SRE_TaskDelete(uwTaskID);
    __SRE_TaskDelete(m_uwInitTstTaskID - uwTaskID);


    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_010
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ������OS_ERRNO_TSK_TCB_UNAVAILABLE��֧����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_010()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;
    LIST_OBJECT_S stTskCBFreeList;
    LIST_OBJECT_S stTskRecyleList;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask01";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;

    stTskRecyleList.pstPrev = g_stTskRecyleList.pstPrev;
    stTskRecyleList.pstNext = g_stTskRecyleList.pstNext;

    g_stTskRecyleList.pstPrev = &g_stTskRecyleList;
    g_stTskRecyleList.pstNext = &g_stTskRecyleList;

    stTskCBFreeList.pstPrev = g_stTskCBFreeList.pstPrev;
    stTskCBFreeList.pstNext = g_stTskCBFreeList.pstNext;

    g_stTskCBFreeList.pstPrev = &g_stTskCBFreeList;
    g_stTskCBFreeList.pstNext = &g_stTskCBFreeList;

    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);

    g_stTskRecyleList.pstPrev = stTskRecyleList.pstPrev;
    g_stTskRecyleList.pstNext = stTskRecyleList.pstNext;

    g_stTskCBFreeList.pstPrev = stTskCBFreeList.pstPrev;
    g_stTskCBFreeList.pstNext = stTskCBFreeList.pstNext;

    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_TCB_UNAVAILABLE, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_011
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ������OS_ERRNO_TSK_PTR_NULL��֧����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_011()
{
    UINT32 uwRet;

    uwRet = __SRE_TaskCreate(NULL, NULL);

    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_PTR_NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_012
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ������OS_ERRNO_TSK_ENTRY_NULL��֧����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_012()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = NULL;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask01";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);

    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_ENTRY_NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskCreate_013
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ������OS_ERRNO_TSK_MSG_Q_TOO_MANY��֧����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_013()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
    stInitParam.usQNum       = 30;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask01";
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);

    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_MSG_Q_TOO_MANY, uwRet);

    return ICUNIT_SUCCESS;
}
#if 0
/**
*-@test UT_sreTaskCreate_014
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ������OS_ERRNO_TSK_NO_MEMORY��֧����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/

VOID * TEST_osTskMemAlloc(UINT32 uwSize)
{
    return 0;
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_014()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;
    SETPEG_JMP_ST stIncSave;

    //SRE_WaitForAllCores();
    if (SRE_GetCoreID() == SRE_GetMasterCore())
    {
        memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

        stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)TST_InitTskEntry;
        stInitParam.usTaskPrio   = TST_TSK_PRIOR_LOW1;
        stInitParam.uwStackSize  = 0;
        stInitParam.pcName       = "TstTask01";
        stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
        SET_PEG(osTskMemAlloc, TEST_osTskMemAlloc, (SETPEG_JMP_ST *)&stIncSave);

        uwRet = SRE_TaskCreate(&uwTaskID, &stInitParam);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_TSK_NO_MEMORY, uwRet);

        CLEAN_PEG(osTskMemAlloc, stIncSave);
    }
    //SRE_WaitForAllCores();

    return ICUNIT_SUCCESS;
}
#endif
/**
*-@test UT_sreTaskCreate_015
*-@tspec  ����ģ�����񴴽����ܺ�������
*-@ttitle  ����������β��Ժʹ������������״̬�ж�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskCreate_015_f01(UINT32 uwParam1,
                           UINT32 uwParam2,
                           UINT32 uwParam3,
                           UINT32 uwParam4)
{
    UINT32 uwRet;
    UINT32 uwTaskPID;
    TSK_HANDLE_T uwTaskID;
    TSK_CB_S *pstTcb;
    m_uwInitTstValue++;

    ICUNIT_ASSERT_EQUAL_VOID(uwParam1, 0, uwParam1);
    ICUNIT_ASSERT_EQUAL_VOID(uwParam2, 1, uwParam2);
    ICUNIT_ASSERT_EQUAL_VOID(uwParam3, 2, uwParam3);
    ICUNIT_ASSERT_EQUAL_VOID(uwParam4, 3, uwParam4);

    uwRet = __SRE_TaskSelf(&uwTaskID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    pstTcb = GET_TCB_HANDLE(uwTaskID);
    ICUNIT_ASSERT_EQUAL_VOID(pstTcb->usTaskStatus & OS_TSK_RUNNING, OS_TSK_RUNNING, pstTcb->usTaskStatus);
    ICUNIT_ASSERT_EQUAL_VOID(pstTcb->usTaskStatus & OS_TSK_READY, OS_TSK_READY, pstTcb->usTaskStatus);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskCreate_015()
{
    UINT32 uwRet;
    UINT32 uwTaskID;
    TSK_INIT_PARAM_S stInitParam;
    TSK_CB_S *pstTcb;

    m_uwInitTstValue = 0;

    memset((VOID*)&stInitParam, 0, sizeof(stInitParam));

    stInitParam.pfnTaskEntry = (TSK_ENTRY_FUNC)UT_sreTaskCreate_015_f01;
    stInitParam.usTaskPrio   = TST_TSK_PRIOR_HIGH1;
    stInitParam.usQNum       = 0;
    stInitParam.uwStackSize  = 0;
    stInitParam.pcName       = "TstTask01";
    stInitParam.auwArgs[0]   = 0;
    stInitParam.auwArgs[1]   = 1;
    stInitParam.auwArgs[2]   = 2;
    stInitParam.auwArgs[3]   = 3;
    stInitParam.uwUsrSpacePartNo = OS_MEM_DEFAULT_FSC_PT;
    uwRet = __SRE_TaskCreate(&uwTaskID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue);

    pstTcb = GET_TCB_HANDLE(uwTaskID);
    ICUNIT_ASSERT_EQUAL(pstTcb->usTaskStatus & OS_TSK_UNUSED, OS_TSK_UNUSED, pstTcb->usTaskStatus);

    m_uwInitTstValue = 0;
    return ICUNIT_SUCCESS;
}

/**
*-@test UT_sreTaskIdle_001
*-@tspec  �����Ӻ�������
*-@ttitle  ȷ�������Ӻ���m_pfnSysIdleHook�����Ż���
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskIdle_001_f01()
{
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskIdle_001()
{
    UINT32 uwRet;
    TSK_HANDLE_T uwTaskID;

    m_uwInitTstValue = 0;

    uwRet = __SRE_TaskDelay(5);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_IdleHookAdd(UT_sreTaskIdle_001_f01);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskDelay(5);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    m_pfnSysIdleHook = NULL;
    ICUNIT_ASSERT_NOT_EQUAL(m_uwInitTstValue, 0, m_uwInitTstValue);
    m_uwInitTstValue = 0;

    return  SRE_OK;
}

/*����A������*/
OS_SEC_TEXT_UT VOID UT_sreTask_TskA(UINT32 uwParam1,UINT32 uwParam2,UINT32 uwParam3,UINT32 uwParam4)
{
    UINT32          uwRet;
    TSK_HANDLE_T    uwTaskPID;

    m_uwInitTstValue ++;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskPrioritySet(uwTaskPID,TASK_PRIO_TEST + 2);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    m_uwInitTstValue ++;

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 3, m_uwInitTstValue, EXIT);
    m_uwInitTstValue ++;

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return;

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
}

/**
*-@test  UT_sreTask_B001
*-@tspec  ������ϲ���
*-@ttitle  �����������ȼ�ʹ�䴦�ھ���̬
*-@tprecon  ����ģ���
*-@tbrief
1.���������ȼ�����A
2.����AΪ�����ȼ�����
3.�ٴε���AΪ�����ȼ�����
*-@texpect
1.��������ɹ�
2.�������ȼ��ɹ�
3.����A״̬Ǩ��ΪE-R-E
*-@tprior  1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTask_B001()
{
    UINT32           uwRet;
    TSK_HANDLE_T     uwTaskPID;

    TSK_INIT_PARAM_S stInitParam = {UT_sreTask_TskA, TASK_PRIO_TEST - 15, 0, {0}, 0x500, "TaskA", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    m_uwInitTstValue = 0;

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);
    m_uwInitTstValue ++;

    uwRet = __SRE_TaskPrioritySet(uwTaskPID,TASK_PRIO_TEST - 2);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 4, m_uwInitTstValue, EXIT);

    return SRE_OK;

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}


/**
*-@test  UT_sreTask_B002
*-@tspec  ������ϲ���
*-@ttitle  �������Ϊ�����ȼ�������
*-@tprecon  ����ģ���
*-@tbrief
1.��������A
2.����AΪ�����ȼ�����
3.��������A
4.�ָ�����A
5.����AΪ�����ȼ�
*-@texpect
1.��������ɹ�
2.�������ȼ��ɹ�
3.��������ɹ�
4.�ָ�����A�ɹ������ȼ����ú����µ�������
*-@tprior  1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTask_B002()
{
    UINT32           uwRet;
    TSK_HANDLE_T     uwTaskPID;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTask_TskA, TASK_PRIO_TEST - 15, 0, {0}, 0x500, "TaskA", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    m_uwInitTstValue = 0;

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);

    uwRet = __SRE_TaskSuspend(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskResume(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    m_uwInitTstValue ++;

    uwRet = __SRE_TaskPrioritySet(uwTaskPID,TASK_PRIO_TEST - 2);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 4, m_uwInitTstValue, EXIT);

    return SRE_OK;

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}


/**
*-@test  UT_sreTask_B003
*-@tspec  ������ϲ���
*-@ttitle  ���ù�����������ȼ�
*-@tprecon  ����ģ���
*-@tbrief
1.��������A
2.����AΪ�����ȼ�����
3.��������A
4.����AΪ�����ȼ�
5.����AΪ�����ȼ�
6.�ָ�����
7.����AΪ�����ȼ�
*-@texpect
1.�����������ɹ�
2.���񱻹�����������ȼ�����ı�����״̬
*-@tprior  1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTask_B003()
{
    UINT32           uwRet;
    TSK_HANDLE_T     uwTaskPID;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTask_TskA, TASK_PRIO_TEST - 15, 0, {0}, 0x500, "TaskA", 0, 0, OS_MEM_DEFAULT_FSC_PT};

    m_uwInitTstValue = 0;

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);

    uwRet = __SRE_TaskSuspend(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskPrioritySet(uwTaskPID,TASK_PRIO_TEST - 10);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);

    uwRet = __SRE_TaskPrioritySet(uwTaskPID,TASK_PRIO_TEST + 2);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);

    uwRet = __SRE_TaskResume(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    m_uwInitTstValue ++;

    uwRet = __SRE_TaskPrioritySet(uwTaskPID,TASK_PRIO_TEST - 2);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 4, m_uwInitTstValue, EXIT);

    return SRE_OK;

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}


/**
*-@test  UT_sreTask_B004
*-@tspec  ������ϲ���
*-@ttitle  ������ĵ����ȼ��������Ϊ�����ȼ�
*-@tprecon  ����ģ���
*-@tbrief
1.��������A
2.����AΪ�����ȼ�����
3.��������A
4.����AΪ�����ȼ�
5.�ָ�����
*-@texpect
1.�����������ɹ�
2.����ָ��󣬽��е���
*-@tprior  1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_sreTask_B004()
{
    UINT32           uwRet;
    TSK_HANDLE_T     uwTaskPID;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTask_TskA, TASK_PRIO_TEST - 15, 0, {0}, 0x500, "TaskA", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    m_uwInitTstValue = 0;

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);

    uwRet = __SRE_TaskSuspend(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskPrioritySet(uwTaskPID,TASK_PRIO_TEST - 10);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);
    m_uwInitTstValue ++;

    uwRet = __SRE_TaskResume(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 4, m_uwInitTstValue, EXIT);

    return SRE_OK;

EXIT:
    uwRet = __SRE_TaskDelete(uwTaskPID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_sreTaskSelfDel_001
*-@tspec  ������ɾ���ӿڲ���
*-@ttitle  ����״��(�������ȡ���δ������Ϣ)��������ɾ���Ƿ�ɹ�
*-@tprecon  ����ģ���
*-@tbrief
1.ע������ɾ������
2.���������ȼ�����A
3.ע���������
4.�����ȼ�������ɾ��
*-@texpect
1.�����������ɹ�
2.�����ɾ������
3.δ�ϱ������������
*-@tprior  1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_001_f01(CHAR    *pcFileName,
                                     UINT32   uwLineNo,
                                     UINT32   uwErrorNo,
                                     UINT32   uwParaLen,
                                     VOID     *pPara)
{
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_001_f02()
{
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_001_f03()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    SRE_ErrRegHook(UT_sreTaskSelfDel_001_f01);

        uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskSelfDel_001()
{
    UINT32           uwRet;
    TSK_HANDLE_T     uwTaskPID;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskSelfDel_001_f03, TASK_PRIO_TEST - 15, 3, {0}, 0x500, "TaskA", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    m_uwInitTstValue = 0;

    uwRet = __SRE_TaskDeleteHookAdd(UT_sreTaskSelfDel_001_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);

    uwRet = __SRE_TaskStatusGet(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet & OS_TSK_UNUSED, OS_TSK_UNUSED, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_usUniTaskLock, 0, g_usUniTaskLock, EXIT);

    SRE_ErrRegHook(NULL);

    uwRet = __SRE_TaskDeleteHookDelete(UT_sreTaskSelfDel_001_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT:
    SRE_ErrRegHook(NULL);

    uwRet = __SRE_TaskDeleteHookDelete(UT_sreTaskSelfDel_001_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)__SRE_TaskDelete(uwTaskPID);

    return SRE_OK;
}

/**
*-@test  UT_sreTaskSelfDel_002
*-@tspec  ������ɾ���ӿڲ���
*-@ttitle  ��������ɾ���Ƿ�ɹ�
*-@tprecon  ����ģ���
*-@tbrief
1.ע������ɾ������
2.���������ȼ�����A
3.����ɾ������ע���������
4.�����ȼ�����������
5.�����ȼ�������ɾ��
*-@texpect
1.�����������ɹ�
2.�����ɾ������
3.δ�ϱ������������
4.�г��������������
*-@tprior  1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_002_f01(CHAR    *pcFileName,
                                     UINT32   uwLineNo,
                                     UINT32   uwErrorNo,
                                     UINT32   uwParaLen,
                                     VOID     *pPara)
{
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_002_f02()
{
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_002_f03()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    SRE_ErrRegHook(UT_sreTaskSelfDel_002_f01);
    __SRE_TaskLock();
    ICUNIT_ASSERT_NOT_EQUAL_VOID(g_usUniTaskLock, 0, g_usUniTaskLock);

        uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskSelfDel_002()
{
    UINT32           uwRet;
    TSK_HANDLE_T     uwTaskPID;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskSelfDel_002_f03, TASK_PRIO_TEST - 15, 3, {0}, 0x500, "TaskA", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    m_uwInitTstValue = 0;

    uwRet = __SRE_TaskDeleteHookAdd(UT_sreTaskSelfDel_002_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);

    uwRet = __SRE_TaskStatusGet(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet & OS_TSK_UNUSED, OS_TSK_UNUSED, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_usUniTaskLock, 0, g_usUniTaskLock, EXIT);

    SRE_ErrRegHook(NULL);

    uwRet = __SRE_TaskDeleteHookDelete(UT_sreTaskSelfDel_002_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;

EXIT:
    SRE_ErrRegHook(NULL);

    uwRet = __SRE_TaskDeleteHookDelete(UT_sreTaskSelfDel_002_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)__SRE_TaskDelete(uwTaskPID);

    return SRE_OK;
}

/**
*-@test  UT_sreTaskSelfDel_003
*-@tspec  ������ɾ���ӿڲ���
*-@ttitle  �������δ������Ϣ��������ɾ���Ƿ�ɹ�
*-@tprecon  ����ģ���
*-@tbrief
1.ע������ɾ������
2.���������ȼ�����A
3.������ȼ��������0���ͳ���Ϣ������Ϣ������Ϣ����Ϣ
4.����ɾ������ע���������
5.�����ȼ�������ɾ��
*-@texpect
1.�����������ɹ�
2.�����ɾ������
3.δ�ϱ������������
*-@tprior  1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_003_f01(CHAR    *pcFileName,
                                     UINT32   uwLineNo,
                                     UINT32   uwErrorNo,
                                     UINT32   uwParaLen,
                                     VOID     *pPara)
{
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_003_f02()
{
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_003_f03()
{
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

    SRE_ErrRegHook(UT_sreTaskSelfDel_003_f01);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskSelfDel_003()
{
    UINT32           uwRet;
    TSK_HANDLE_T     uwTaskPID;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskSelfDel_003_f03, TASK_PRIO_TEST - 15, 3, {0}, 0x500, "TaskA", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    UINT16 usSize;
    UINT32 uwMsgHandle;
    UINT32 uwMsgID;
    TSK_CB_S *pstTsk;

    m_uwInitTstValue = 0;

    __SRE_TaskLock();

    uwRet = __SRE_TaskDeleteHookAdd(UT_sreTaskSelfDel_003_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);


    usSize = 20;   //����Ϣ
    uwMsgHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_FSC_PT, usSize, 0);
    ICUNIT_GOTO_NOT_EQUAL(uwMsgHandle, OS_MSG_CREATE_ERR, uwMsgHandle, EXIT);

    uwMsgID = 1;
    uwRet = __SRE_MsgQSend(uwMsgHandle, uwMsgID, uwTaskPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    usSize = 6;   //82����Ϣ,8108����Ϣ
    uwMsgHandle = __SRE_MsgAlloc(OS_MEM_DEFAULT_FSC_PT, usSize, 0);
    ICUNIT_GOTO_NOT_EQUAL(uwMsgHandle, OS_MSG_CREATE_ERR, uwMsgHandle, EXIT);

    uwMsgID = 2;
    uwRet = __SRE_MsgQSend(uwMsgHandle, uwMsgID, uwTaskPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwMsgID = 2;
    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTaskPID, 0);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwMsgID = 2;
    uwRet = __SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTaskPID, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pstTsk = GET_TCB_HANDLE(uwTaskPID);
    ICUNIT_GOTO_EQUAL(pstTsk->pstMsgQ[0].uwMsgNum, 3, pstTsk->pstMsgQ[0].uwMsgNum, EXIT);
    ICUNIT_GOTO_EQUAL(pstTsk->pstMsgQ[1].uwMsgNum, 1, pstTsk->pstMsgQ[1].uwMsgNum, EXIT);

    __SRE_TaskUnlock();
    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 1, m_uwInitTstValue, EXIT);

    uwRet = __SRE_TaskStatusGet(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet & OS_TSK_UNUSED, OS_TSK_UNUSED, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_usUniTaskLock, 0, g_usUniTaskLock, EXIT);
    ICUNIT_GOTO_EQUAL(pstTsk->pstMsgQ[0].uwMsgNum, 0, pstTsk->pstMsgQ[0].uwMsgNum, EXIT);
    ICUNIT_GOTO_EQUAL(pstTsk->pstMsgQ[1].uwMsgNum, 0, pstTsk->pstMsgQ[1].uwMsgNum, EXIT);

    SRE_ErrRegHook(NULL);

    uwRet = __SRE_TaskDeleteHookDelete(UT_sreTaskSelfDel_003_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    //SRE_WaitForAllCores();
    UT_sreGetTaskInfo();
    return SRE_OK;
EXIT:
    __SRE_TaskUnlock();

    SRE_ErrRegHook(NULL);

    uwRet = __SRE_TaskDeleteHookDelete(UT_sreTaskSelfDel_003_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)__SRE_TaskDelete(uwTaskPID);

    //SRE_WaitForAllCores();
    UT_sreGetTaskInfo();
    return SRE_OK;
}

#if 0
/**
*-@test  UT_sreTaskSelfDel_004
*-@tspec  ������ɾ���ӿڲ���
*-@ttitle  �������δ������Ϣ��������ɾ���Ƿ�ɹ�
*-@tprecon  ����ģ���
*-@tbrief
1.ע������ɾ������
2.���������ȼ�����A
3.������ȼ��������0���ͳ���Ϣ������Ϣ������Ϣ����Ϣ
4.����ɾ������ע���������
5.�����ȼ�������ɾ��
*-@texpect
1.�����������ɹ�
2.�����ɾ������
3.δ�ϱ������������
*-@tprior  1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_MsgFree_Stub(MSG_HANDLE_T uwMsgHandle)
{
    MSG_HEAD_S  *pstMsgHead;

    /* ������Դ */
    pstMsgHead = (MSG_HEAD_S *)(uwMsgHandle - OS_MSG_HEAD_LEN);

    pstMsgHead->usMagicWord = 0;
    pstMsgHead->stList.pstNext = NULL;
    pstMsgHead->stList.pstPrev = NULL;
    (VOID)SRE_MemFree(OS_MID_MSG, pstMsgHead->pMemBlock);

    return OS_FAIL;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_004_f01(CHAR    *pcFileName,
                                     UINT32   uwLineNo,
                                     UINT32   uwErrorNo,
                                     UINT32   uwParaLen,
                                     VOID     *pPara)
{
    ICUNIT_ASSERT_EQUAL_VOID(uwErrorNo, OS_ERRNO_TSK_SELF_DELETE_ERR, uwErrorNo);
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_004_f02()
{
    m_uwInitTstValue++;
}

OS_SEC_TEXT_UT VOID UT_sreTaskSelfDel_004_f03()
{
    SRE_ErrRegHook(UT_sreTaskSelfDel_004_f01);
}

OS_SEC_TEXT_UT UINT32 UT_sreTaskSelfDel_004()
{
    UINT32           uwRet;
    TSK_HANDLE_T     uwTaskPID;
    TSK_INIT_PARAM_S stInitParam = {UT_sreTaskSelfDel_004_f03, TASK_PRIO_TEST - 15, 3, {0}, 0x500, "TaskA", 0, 0, OS_MEM_DEFAULT_FSC_PT};
    UINT16 usSize;
    UINT32 uwMsgHandle;
    UINT32 uwMsgID;
    TSK_CB_S *pstTsk;
    SETPEG_JMP_ST stIncSave;

    m_uwInitTstValue = 0;

    SRE_TaskLock();

    uwRet = SRE_TaskDeleteHookAdd(UT_sreTaskSelfDel_004_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_TaskCreate(&uwTaskPID, &stInitParam);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);


    usSize = 20;   //����Ϣ
    uwMsgHandle = SRE_MsgAlloc(OS_MEM_DEFAULT_FSC_PT, usSize, 0);
    ICUNIT_GOTO_NOT_EQUAL(uwMsgHandle, OS_MSG_CREATE_ERR, uwMsgHandle, EXIT);

    uwMsgID = 1;
    uwRet = __SRE_MsgSend(uwMsgHandle, uwMsgID, uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    usSize = 6;   //82����Ϣ��8108����Ϣ
    uwMsgHandle = SRE_MsgAlloc(OS_MEM_DEFAULT_FSC_PT, usSize, 0);
    ICUNIT_GOTO_NOT_EQUAL(uwMsgHandle, OS_MSG_CREATE_ERR, uwMsgHandle, EXIT);

    uwMsgID = 2;
    uwRet = __SRE_MsgSend(uwMsgHandle, uwMsgID, uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwMsgID = 2;
    uwRet = __SRE_MsgSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwMsgID = 2;
    uwRet = SRE_MsgQSend(OS_MSG_NO_PAYLOAD, uwMsgID, uwTaskPID, 1);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    pstTsk = GET_TCB_HANDLE(uwTaskPID);
    ICUNIT_GOTO_EQUAL(pstTsk->pstMsgQ[0].uwMsgNum, 3, pstTsk->pstMsgQ[0].uwMsgNum, EXIT);
    ICUNIT_GOTO_EQUAL(pstTsk->pstMsgQ[1].uwMsgNum, 1, pstTsk->pstMsgQ[1].uwMsgNum, EXIT);

    SET_PEG(SRE_MsgDelete, UT_SRE_MsgFree_Stub, (SETPEG_JMP_ST *)&stIncSave);
    SRE_TaskUnlock();
    CLEAN_PEG(SRE_MsgDelete, stIncSave);
    #if (OS_CPU_TYPE == OS_SD6182)
    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 2, m_uwInitTstValue, EXIT);
    #else
    ICUNIT_GOTO_EQUAL(m_uwInitTstValue, 3, m_uwInitTstValue, EXIT);
    #endif
    uwRet = SRE_TaskStatusGet(uwTaskPID);
    ICUNIT_GOTO_EQUAL(uwRet & OS_TSK_UNUSED, OS_TSK_UNUSED, uwRet, EXIT);
    ICUNIT_GOTO_EQUAL(g_usUniTaskLock, 0, g_usUniTaskLock, EXIT);
    ICUNIT_GOTO_EQUAL(pstTsk->pstMsgQ[0].uwMsgNum, 0, pstTsk->pstMsgQ[0].uwMsgNum, EXIT);
    ICUNIT_GOTO_EQUAL(pstTsk->pstMsgQ[1].uwMsgNum, 0, pstTsk->pstMsgQ[1].uwMsgNum, EXIT);

    SRE_ErrRegHook(NULL);

    uwRet = SRE_TaskDeleteHookDelete(UT_sreTaskSelfDel_004_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
EXIT:
    SRE_TaskUnlock();

    SRE_ErrRegHook(NULL);

    uwRet = SRE_TaskDeleteHookDelete(UT_sreTaskSelfDel_004_f02);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    (VOID)SRE_TaskDelete(uwTaskPID);

    return SRE_OK;
}
#endif

UINT32 g_TestTaskNewPID = 0;
extern TSK_HANDLE_T g_TestTskHandle;
#define INT_SECURE                  0x0
UINT32 g_NewHwiFlag = 0;

OS_SEC_TEST_TEXT UINT32 UT_sreTask_NewHwi_Func5(HWI_ARG_T uwArg)
{
    uart_printf("g_vuwUniFlag 7 = 0x%x\n", g_vuwUniFlag);

    SRE_TaskResume(g_TestTskHandle);

    uart_printf("########UT_sreTask_NewHwi_Func5 exit!\n");

    uart_printf("g_vuwUniFlag 8 = 0x%x\n", g_vuwUniFlag);

    g_NewHwiFlag++;
}

OS_SEC_TEST_TEXT UINT32 UT_sreTask_NewHwiSgiCreate_005()
{
    UINT32 uwRet;
    UINT32 uwPerBaseAddr;

    uwRet = __SRE_HwiCreate(1, 0xa0, INT_SECURE, UT_sreTask_NewHwi_Func5, 1);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    uwRet = __SRE_HwiEnable(1);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    __SRE_HwiTrigger(INT_SECURE, 0, 1);           /*�û�̬����жϳ���*/
    //__asm_sre_HwiTrigger(INT_SECURE, 0, 1);

    while(g_NewHwiFlag == 0)
    {
        uwRet++;
    }

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_GOTO_EQUAL(uwRet,SRE_OK,uwRet, EXIT);

    uart_printf("UT_sreTask_NewHwiSgiCreate_005 end!\n");

EXIT:
    return SRE_OK;
}

OS_SEC_TEST_TEXT VOID It_sreTask_New01_Tsk(UINT32 uwParam1,UINT32 uwParam2,UINT32 uwParam3,UINT32 uwParam4)
{
    UINT32  uwRet;
    UINT32  uwTaskPID;

    uart_printf("g_vuwUniFlag 5 = 0x%x\n", g_vuwUniFlag);

    UT_sreTask_NewHwiSgiCreate_005();

    __SRE_TaskResume(g_TestTskHandle);

    uart_printf("g_vuwUniFlag 6 = 0x%x\n", g_vuwUniFlag);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return;
}

OS_SEC_TEST_TEXT UINT32 It_sreTask_New01()
{
    UINT32           uwRet;
    TSK_STATUS_T     usTaskStatus;
    TSK_INIT_PARAM_S stInitParam = {It_sreTask_New01_Tsk, 30, 6, {0}, 0x500, "Task31", 0, 0, OS_MEM_DEFAULT_FSC_PT};

    uwRet = __SRE_TaskCreate(&g_TestTaskNewPID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSuspend(g_TestTskHandle);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uwRet = __SRE_TaskSuspend(g_TestTskHandle);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

EXIT:
    uwRet = __SRE_TaskDelete(g_TestTaskNewPID);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

#if 1
OS_SEC_TEST_TEXT VOID It_sreTask_New02_Tsk(UINT32 uwParam1,UINT32 uwParam2,UINT32 uwParam3,UINT32 uwParam4)
{
    UINT32  uwRet;
    UINT32  uwTaskPID;

    uart_printf("g_vuwUniFlag 3 = 0x%x\n", g_vuwUniFlag);

    UT_sreTask_NewHwiSgiCreate_005();

    uart_printf("It_sreTask_New02_Tsk: secondly excute UT_sreTask_NewHwiSgiCreate_005\n");

    uart_printf("g_vuwUniFlag 4 = 0x%x\n", g_vuwUniFlag);

    UT_sreTask_NewHwiSgiCreate_005();

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

    return;
}

OS_SEC_TEST_TEXT UINT32 It_sreTask_New02()
{
    UINT32           uwRet;
    TSK_STATUS_T     usTaskStatus;
    TSK_INIT_PARAM_S stInitParam = {It_sreTask_New02_Tsk, 30, 6, {0}, 0x500, "Task31", 0, 0, OS_MEM_DEFAULT_FSC_PT};

    uwRet = __SRE_TaskCreate(&g_TestTaskNewPID, &stInitParam);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uart_printf("g_vuwUniFlag 1 = 0x%x\n", g_vuwUniFlag);

    uart_printf("first excute task suspend\n");
    uwRet = __SRE_TaskSuspend(g_TestTskHandle);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uart_printf("g_vuwUniFlag 2 = 0x%x\n", g_vuwUniFlag);

    uart_printf("second excute task suspend\n");
    uwRet = __SRE_TaskSuspend(g_TestTskHandle);
    ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

    uart_printf("end excute task suspend\n");

EXIT:
    uwRet = __SRE_TaskDelete(g_TestTaskNewPID);
    uart_printf("uwRet = 0x%x\n", uwRet);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_HwiDelete(1);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}
#endif

OS_SEC_TEXT_UT VOID UT_sre_task_init()
{
    iUINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_sre_task_init");

    TEST_ADD_CASE(UT_osTskRegister_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osTskRegister_002, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_osTskInit_001, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_osTskMemAlloc_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osTskMemAlloc_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osTskMemAlloc_003, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_osTskMemFree_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osTskMemFree_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osTskMemFree_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_osTskMemFree_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_osTskMemFree_005, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_osTskMemFree_006, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_osActivate_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskResume_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskResume_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskResume_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskResume_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskResume_005, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskSuspend_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSuspend_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSuspend_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSuspend_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskSuspend_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSuspend_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSuspend_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSuspend_008, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskDelete_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskDelete_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskDelete_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskDelete_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskDelete_005, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskCreateHookAdd_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreateHookAdd_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreateHookAdd_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreateHookAdd_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskCreateHookAdd_005, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskCreateHookDelete_001, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskDeleteHookAdd_001, uiSuiteId, Label_RUN);
    #if 0
    TEST_ADD_CASE(UT_sreTaskDeleteHookAdd_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskDeleteHookAdd_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskDeleteHookAdd_004, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskDeleteHookDelete_001, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskSwitchHookAdd_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSwitchHookAdd_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSwitchHookAdd_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSwitchHookAdd_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSwitchHookAdd_005, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskSwitchHookDelete_001, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskHookAdd_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskHookAdd_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskHookAdd_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskHookDel_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskHookDel_002, uiSuiteId, Label_RUN);
    #endif
    TEST_ADD_CASE(UT_sreTaskCreate_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_009, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_010, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_011, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_012, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_013, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_sreTaskCreate_014, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskCreate_015, uiSuiteId, Label_RUN);

    //TEST_ADD_CASE(UT_sreTaskIdle_001, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTask_B001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTask_B002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTask_B003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTask_B004, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_sreTaskSelfDel_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSelfDel_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_sreTaskSelfDel_003, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(It_sreTask_New01, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(It_sreTask_New02, uiSuiteId, Label_RUN);

    if (SRE_GetCoreID() == SRE_GetMasterCore())
    {
       // TEST_ADD_CASE(UT_sreTaskSelfDel_004, uiSuiteId, Label_RUN);
    }


 Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
