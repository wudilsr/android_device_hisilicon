 /**
 * @file:
 *
 * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * @description：
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
EXTERN_FAR  MEM_PT_INFO_S  *m_astMemPtInfo;     /*分区控制块信息，分配在缺省的私有静态内存中*/
extern VOID Ut_MemPtDelete(UINT8 ucPtNo);

/**
*-@test  UT_SRE_MemAllocAlign_001
*-@tspec  SRE_MemAllocAlign接口测试
*-@ttitle  缺省静态内存中申请内存，字节对齐参数为1
*-@tprecon  只是判断非NULL比较弱，要通过g_pstCdaInfoAddr->uwErrCode来判断相应的错误码，内存申请失败的测试场景用例都要考虑做成这样
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemAllocAlign_001(void)
{
    UINT32 *uwRet;

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 10, (OS_MEM_ALIGN_E)1);

    /* 如果返回值不为NULL, 返回失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_002
*-@tspec SRE_MemAllocAlign接口测试
*-@ttitle  缺省静态内存中申请内存，字节对齐参数为2
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

    /* 如果返回值不为NULL, 返回失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_003
*-@tspec  SRE_MemAllocAlign接口测试
*-@ttitle  缺省静态内存中申请内存，字节对齐参数为4
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

    /* 如果返回值不为NULL, 返回失败 */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_004
*-@tspec  SRE_MemAllocAlign接口测试
*-@ttitle  缺省静态内存中申请内存，字节对齐参数为8
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

    /* 如果返回值不为NULL, 返回失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_005
*-@tspec  缺省静态内存测试
*-@ttitle  缺省静态内存中申请内存，字节对齐参数为512
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

    /* 如果返回值不为NULL申请成功  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_006
*-@tspec  缺省静态内存测试
*-@ttitle  缺省静态内存中申请内存，字节对齐参数为1024
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

    /* 如果返回值不为NULL申请成功  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_007
*-@tspec  SRE_MemAllocAlign 接口测试
*-@ttitle 分区号大于 m_ucMaxPtNum
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

    /* 申请失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_008
*-@tspec  SRE_MemAllocAlign 接口测试
*-@ttitle 分区还未使用
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

    /* 申请失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_009
*-@tspec  SRE_MemAllocAlign 接口测试
*-@ttitle 分区传入长度为0
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
    /* 申请失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    uwRet = SRE_MemAllocAlign(OS_MID_MEM, OS_MEM_DEFAULT_FSC_PT, 0,  (OS_MEM_ALIGN_E)1);
    /* 申请失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAllocAlign_010
*-@tspec  SRE_MemAllocAlign 接口测试
*-@ttitle 共享静态FSC内存申请的尺寸与同BLOCK已申请的内存尺寸不匹配
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
*-@tspec  SRE_MemAlloc 接口测试
*-@ttitle  分区号大于等于 m_ucMaxPtNum
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
    /* 申请失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    uwRet = SRE_MemAlloc(OS_MID_MEM, (m_ucMaxPtNum + 1), 1);
    /* 申请失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);
    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAlloc_002
*-@tspec  SRE_MemAlloc 接口测试
*-@ttitle 分区还未使用
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

    /* 申请失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemAlloc_003
*-@tspec  SRE_MemAlloc 接口测试
*-@ttitle 分区传入长度为0
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

    /* 申请失败  */
    ICUNIT_ASSERT_EQUAL(uwRet, NULL, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemFree_001
*-@tspec  SRE_MemFree 接口测试
*-@ttitle 释放地址为空&释放非法内存地址（构造内存块被破坏的场景）
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
    /*释放地址为空*/
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_FREE_ADDR_INVALID, uwRet);

    return ICUNIT_SUCCESS;
}

/**
*-@test  UT_SRE_MemFree_002
*-@tspec  SRE_MemFree 接口测试
*-@ttitle 释放内存块所在分区号大于最大分区数
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
