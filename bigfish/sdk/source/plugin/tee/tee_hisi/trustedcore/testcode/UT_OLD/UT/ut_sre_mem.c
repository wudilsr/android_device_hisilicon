 /**
 * @file:
 *
 * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * @description��
 */

#include "iCunit.h"
#include "app_data_common.h"
#include "osTest.h"
#include "sre_mem.h"
#include "sre_mem.ph"
//#include "sre_mcresleakmon.ph"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

EXTERN_FAR  UINT8           m_ucMaxPtNum;
EXTERN_FAR  MEM_PT_INFO_S  *m_astMemPtInfo;     /*�������ƿ���Ϣ��������ȱʡ��˽�о�̬�ڴ���*/
extern VOID Ut_MemPtDelete(UINT8 ucPtNo);

/**
*-@test  UT_SRE_MemAllocAlign_001
*-@tspec  SRE_MemAllocAlign�ӿڲ���
*-@ttitle  ȱʡ��̬�ڴ��������ڴ棬�ֽڶ������Ϊ1
*-@tprecon  ֻ���жϷ�NULL�Ƚ�����Ҫͨ��g_pstCdaInfoAddr->uwErrCode���ж���Ӧ�Ĵ����룬�ڴ�����ʧ�ܵĲ��Գ���������Ҫ������������
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_001(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 10, (OS_MEM_ALIGN_E)1);

    /* �������ֵ��ΪNULL, ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_002
*-@tspec SRE_MemAllocAlign�ӿڲ���
*-@ttitle  ȱʡ��̬�ڴ��������ڴ棬�ֽڶ������Ϊ2
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_002(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 10, (OS_MEM_ALIGN_E)2);

    /* �������ֵ��ΪNULL, ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_003
*-@tspec  SRE_MemAllocAlign�ӿڲ���
*-@ttitle  ȱʡ��̬�ڴ��������ڴ棬�ֽڶ������Ϊ4
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_003(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 10,  (OS_MEM_ALIGN_E)3);

    /* �������ֵ��ΪNULL, ����ʧ�� */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_004
*-@tspec  SRE_MemAllocAlign�ӿڲ���
*-@ttitle  ȱʡ��̬�ڴ��������ڴ棬�ֽڶ������Ϊ8
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_004(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 10, (OS_MEM_ALIGN_E)5);

    /* �������ֵ��ΪNULL, ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_005
*-@tspec  ȱʡ��̬�ڴ����
*-@ttitle  ȱʡ��̬�ڴ��������ڴ棬�ֽڶ������Ϊ512
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_005(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 10,  (OS_MEM_ALIGN_E)512);

    /* �������ֵ��ΪNULL����ɹ�  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_006
*-@tspec  ȱʡ��̬�ڴ����
*-@ttitle  ȱʡ��̬�ڴ��������ڴ棬�ֽڶ������Ϊ1024
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_006(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 10, (OS_MEM_ALIGN_E)1024);

    /* �������ֵ��ΪNULL����ɹ�  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_007
*-@tspec  SRE_MemAllocAlign �ӿڲ���
*-@ttitle �����Ŵ��� m_ucMaxPtNum
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_007(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_MAX_PT_NUM+OS_MEM_DEFAULT_PTNUM, 1, (OS_MEM_ALIGN_E)1);

    /* ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_008
*-@tspec  SRE_MemAllocAlign �ӿڲ���
*-@ttitle ������δʹ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_008(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_MAX_PT_NUM +4 -1, 1,  (OS_MEM_ALIGN_E)1);

    /* ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_009
*-@tspec  SRE_MemAllocAlign �ӿڲ���
*-@ttitle �������볤��Ϊ0
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_009(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 0,  (OS_MEM_ALIGN_E)4);
    /* ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 0,  (OS_MEM_ALIGN_E)1);
    /* ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_010
*-@tspec  SRE_MemAllocAlign �ӿڲ���
*-@ttitle ����̬FSC�ڴ�����ĳߴ���ͬBLOCK��������ڴ�ߴ粻ƥ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_010(void)
{
    UINT32 *uwRet;
    UINT32  uwSize;

    uwSize = 0x20;
    uwRet = SRE_MemAlloc(OS_MID_MCSEM | OS_MID_MCSEM << 16,OS_MEM_DEFAULT_MCSTA_FSC_PT, uwSize);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwSize = 0x20;
    uwRet = SRE_MemAlloc(OS_MID_MCSEM | OS_MID_MCSEM << 16,OS_MEM_DEFAULT_MCSTA_FSC_PT, uwSize);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwSize = 0xffffffff;
    uwRet =  SRE_MemAllocAlign(OS_MID_BUTT, OS_MEM_DEFAULT_MCSTA_FSC_PT, uwSize,MEM_ADDR_ALIGN_004);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAlloc_001
*-@tspec  SRE_MemAlloc �ӿڲ���
*-@ttitle  �����Ŵ��ڵ��� m_ucMaxPtNum
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAlloc_001(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAlloc(OS_MID_MEM, m_ucMaxPtNum, 1);
    /* ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    uwRet = SRE_MemAlloc(OS_MID_MEM, (m_ucMaxPtNum + 1), 1);
    /* ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAlloc_002
*-@tspec  SRE_MemAlloc �ӿڲ���
*-@ttitle ������δʹ��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAlloc_002(void)
{
    UINT32 *uwRet;
    m_astMemPtInfo[m_ucMaxPtNum-1].bInstalled = 0;

    uwRet = SRE_MemAlloc(OS_MID_MEM, m_ucMaxPtNum-1, 1);

    /* ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAlloc_003
*-@tspec  SRE_MemAlloc �ӿڲ���
*-@ttitle �������볤��Ϊ0
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAlloc_003(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAlloc(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 0);

    /* ����ʧ��  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemFree_001
*-@tspec  SRE_MemFree �ӿڲ���
*-@ttitle �ͷŵ�ַΪ��&�ͷŷǷ��ڴ��ַ�������ڴ�鱻�ƻ��ĳ�����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemFree_001(void)
{
    UINT32 uwRet;

    uwRet = SRE_MemFree(OS_MID_MEM, 0);
    /*�ͷŵ�ַΪ��*/
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_FREE_ADDR_INVALID, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemFree_002
*-@tspec  SRE_MemFree �ӿڲ���
*-@ttitle �ͷ��ڴ�����ڷ����Ŵ�����������
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemFree_002(void)
{
    UINT32 uwRet;
    UINT32 *pAddr;
    UINT8 uwsave;

    uwsave = m_ucMaxPtNum;
    pAddr = SRE_MemAlloc(OS_MID_MEM, 1, 16);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    m_ucMaxPtNum = 2;

    uwRet = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MCSTA_FSCMEM_FREE_ISFORBIDEN, uwRet,ERR);

    m_ucMaxPtNum = 1;

    uwRet = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_MEM_FREE_PTNO_INVALID, uwRet,ERR);
ERR:
    m_ucMaxPtNum = uwsave;
    uwRet = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MCSTA_FSCMEM_FREE_ISFORBIDEN, uwRet);

    return SRE_OK;
}

OS_SEC_TEXT2_UT void UT_SRE_Mem(void)
{
    iUINT32 uiSuiteId;

    //SRE_WaitForAllCores();
    TEST_ADD_SUITE(uiSuiteId, "UT_SRE_Mem");

    TEST_ADD_CASE(UT_SRE_MemAllocAlign_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAllocAlign_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAllocAlign_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAllocAlign_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAllocAlign_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAllocAlign_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAllocAlign_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAllocAlign_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAllocAlign_009, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAllocAlign_010, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_MemAlloc_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAlloc_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemAlloc_003, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_MemFree_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_MemFree_002, uiSuiteId, Label_RUN);

    //SRE_WaitForAllCores();

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
