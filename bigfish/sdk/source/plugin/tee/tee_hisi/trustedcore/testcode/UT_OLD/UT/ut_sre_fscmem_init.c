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

#include "sre_mem.h"
#include "sre_mem.ph"
#include "iCunit.h"
#include "osTest.h"
#include "sre_sys.h"
#include "app_data_common.h"

extern UINT8  m_aucUtDynplmemRegion[0x00001500];
extern UINT32 osFscMemRegister(UINT8 ucMaxPtNum);
extern VOID   Ut_MemPtDelete(UINT8 ucPtNo);
extern UINT8  m_ucMaxPtNum;
extern UINT8  g_FscPtNo;
extern UINT8  g_FscPtNo2;

extern UINT8 m_aucFscMemRegion0[0x200];
extern UINT8 m_aucFscMemRegion1[0x200];
extern UINT8 m_aucFscMemRegion_hc1[0x11000];


EXTERN_FAR MEM_PT_INFO_S  *m_astMemPtInfo;

/**
*-@test  UT_SRE_FscMemInitRegister_001
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API osFscMemRegister分支覆盖(注册的分区过多)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemInitRegister_001(VOID)
{
    UINT32 uwRet;

    uwRet = osFscMemRegister(OS_MAX_PT_NUM + 1);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_PTNUMBER_OVERMANY, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemInitPtCreate_001
*-@tspec  FSC算法的分区创建UT测试
*-@ttitle  创建一个FSC私用动态内存空间，空间过小
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemInitPtCreate_001(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA  stPara;

    stPara.enArith         = MEM_ARITH_FSC;
    stPara.pPtAddr         = &m_aucUtDynplmemRegion[0];
    stPara.uwPtSize        = 0x00000010;

    uwRet= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemInitPtCreate_002
*-@tspec  FSC算法的分区创建UT测试
*-@ttitle  成功创建一个FSC私用动态内存空间
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemInitPtCreate_002(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA  stPara;

    stPara.enArith         = MEM_ARITH_FSC;
    stPara.pPtAddr         = &m_aucUtDynplmemRegion[0];
    stPara.uwPtSize        = 0x00001500;

    uwRet= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemInitPtCreate_003
*-@tspec  FSC算法的分区创建UT测试
*-@ttitle  在一个已经创建的内存空间创建一个FSC私用动态内存空间
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemInitPtCreate_003(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA  stPara;

    stPara.enArith         = MEM_ARITH_FSC;
    stPara.pPtAddr         = &m_aucUtDynplmemRegion[0];
    stPara.uwPtSize        = 0x00001500;

    uwRet= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PT_ALREADY_CREATED,  uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemPtInit_001
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API osFscMemPtInit分支覆盖(割完64K空间后，剩下的空间为0，直接返回)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemPtInit_001(VOID)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA stPara;
    UINT32 uwIdx;

    for(uwIdx = 3; uwIdx < m_ucMaxPtNum; uwIdx++)
    {
        if(m_astMemPtInfo[uwIdx].bInstalled == FALSE)
        {
            g_FscPtNo2 = uwIdx;
            break;
        }
    }

    memset(&stPara, 0, sizeof(MEM_CREATEPT_PARA));
    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = m_aucFscMemRegion_hc1;
    stPara.uwPtSize = 0x10000;

    uwRet = SRE_MemPtCreate(&stPara, g_FscPtNo2);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    Ut_MemPtDelete(g_FscPtNo2);

    return SRE_OK;
}

/**
*-@test  UT_UT_SRE_FscMemPtInit_002
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API osFscMemPtInit分支覆盖(割完64K空间后，剩下的空间不足以成为一个单独块，则丢弃之)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemPtInit_002(VOID)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA stPara;
    UINT32 uwIdx;

    for(uwIdx = 3; uwIdx < m_ucMaxPtNum; uwIdx++)
    {
        if(m_astMemPtInfo[uwIdx].bInstalled == FALSE)
        {
            g_FscPtNo2 = uwIdx;
            break;
        }
    }

    memset(&stPara, 0, sizeof(MEM_CREATEPT_PARA));
    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = m_aucFscMemRegion_hc1;
    stPara.uwPtSize = 0x10008;

    uwRet = SRE_MemPtCreate(&stPara, g_FscPtNo2);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    Ut_MemPtDelete(g_FscPtNo2);

    return SRE_OK;
}

/**
*-@test  UT_UT_SRE_FscMemDefPtCreate_001
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API osFscMemDefPtCreate分支覆盖(所给的内存大小为0)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemDefPtCreate_001(VOID)
{
    UINT32 uwRet;

    uwRet = osFscMemDefPtCreate(10, m_aucFscMemRegion1, 0);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTCREATE_PARAMETER_INVALID,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemDefPtCreate_002
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API osFscMemDefPtCreate分支覆盖(所给的内存大小太小)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemDefPtCreate_002(VOID)
{
    UINT32 uwRet;

    uwRet = osFscMemDefPtCreate(10, m_aucFscMemRegion1 + 1, 3);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL,uwRet);

    return SRE_OK;
}

OS_SEC_TEXT4_UT void UT_SRE_FscMem_Init(void)
{
    iUINT32 uiSuiteId;
    TEST_ADD_SUITE(uiSuiteId, "UT_SRE_FscMem_Init");

    //SRE_WaitForAllCores();
    TEST_ADD_CASE(UT_SRE_FscMemInitRegister_001, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_FscMemInitPtCreate_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemInitPtCreate_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemInitPtCreate_003, uiSuiteId, Label_RUN);

    if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
    {
        TEST_ADD_CASE(UT_SRE_FscMemPtInit_001, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_SRE_FscMemPtInit_002, uiSuiteId, Label_RUN);
    }

    TEST_ADD_CASE(UT_SRE_FscMemDefPtCreate_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemDefPtCreate_002, uiSuiteId, Label_RUN);

    //SRE_WaitForAllCores();
    Ut_MemPtDelete(UT_LCDYNPLMEM_PTNO);
    //SRE_WaitForAllCores();

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
    Ut_MemPtDelete(UT_LCDYNPLMEM_PTNO);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
