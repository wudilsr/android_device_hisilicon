/*
* @file ut_unifscmem.c
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* 描述：私有FSC内存测试代码C文件。 \n
*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "sre_base.h"
#include "sre_mem.h"
#include "sre_config.h"
#include "sre_sys.h"
#include "sre_mem.ph"
#include "iCunit.h"
#include "osTest.h"
#include "app_data_common.h"


#define UT_SRE_FSC_MEM_PT0_SIZE 0x200
#define UT_SRE_FSC_MEM_PT1_SIZE 0x200
#define UT_SRE_FSC_MEM_PT2_SIZE 0x11000

extern UINT8  m_ucMaxPtNum;
extern UINT8  m_aucFscMemRegion_hc1[0x11000];
extern UINT32 osFscMemDefPtCreate(UINT8 ucPtNo, VOID *pAddr, UINT32 uwSize);

extern UINT32 osMemArrayInit(VOID);
extern VOID   Ut_MemPtDelete(UINT8 ucPtNo);

OS_SEC_BSS UINT8 m_aucFscMemRegion0[UT_SRE_FSC_MEM_PT0_SIZE];
OS_SEC_BSS UINT8 m_aucFscMemRegion1[UT_SRE_FSC_MEM_PT1_SIZE];
OS_SEC_BSS UINT8 g_FscPtNo;
OS_SEC_BSS UINT8 g_FscPtNo2;

/******************************************************************************/
/**
*-@test  UT_SRE_FscMemPtCreate_001
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemPtCreate正常功能测试
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemPtCreate_001(VOID)
{
    UINT32 uwIdx;
    UINT32 uwRet;
    MEM_CREATEPT_PARA stPara;

    for(uwIdx = 3; uwIdx < m_ucMaxPtNum; uwIdx++)
    {
        if(m_astMemPtInfo[uwIdx].bInstalled == FALSE)
        {
            g_FscPtNo = uwIdx;
            break;
        }
    }

    memset(&stPara, 0, sizeof(MEM_CREATEPT_PARA));
    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = m_aucFscMemRegion0;
    stPara.uwPtSize = UT_SRE_FSC_MEM_PT0_SIZE;

    uwRet = SRE_MemPtCreate(&stPara, g_FscPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemPtCreate_002
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemPtCreate异常功能测试(参数uwPtSize给为0)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemPtCreate_002(VOID)
{
    UINT32 uwIdx;
    UINT32 uwRet;
    UINT8  ucPtNo;
    MEM_CREATEPT_PARA stPara;

    //SRE_WaitForAllCores();
    for(uwIdx = 3; uwIdx < m_ucMaxPtNum; uwIdx++)
    {
        if(m_astMemPtInfo[uwIdx].bInstalled == FALSE)
        {
            ucPtNo = uwIdx;
            break;
        }
    }

    memset(&stPara, 0, sizeof(MEM_CREATEPT_PARA));
    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = m_aucFscMemRegion0;
    stPara.uwPtSize = 0;

    uwRet = SRE_MemPtCreate(&stPara, ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTCREATE_PARAMETER_INVALID,uwRet);

    return SRE_OK;
}
/**
*-@test  UT_SRE_FscMemPtCreate_003
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemPtCreate异常功能测试(参数pPtAddr给为NULL)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemPtCreate_003(VOID)
{
    UINT32 uwIdx;
    UINT32 uwRet;
    UINT8  ucPtNo;
    MEM_CREATEPT_PARA stPara;

    for(uwIdx = 3; uwIdx < m_ucMaxPtNum; uwIdx++)
    {
        if(m_astMemPtInfo[uwIdx].bInstalled == FALSE)
        {
            ucPtNo = uwIdx;
            break;
        }
    }

    memset(&stPara, 0, sizeof(MEM_CREATEPT_PARA));
    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = NULL;
    stPara.uwPtSize = UT_SRE_FSC_MEM_PT0_SIZE;

    uwRet = SRE_MemPtCreate(&stPara, ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTCREATE_PARAMETER_INVALID,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemPtCreate_004
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemPtCreate异常功能测试(所给空间与已有分区重叠)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemPtCreate_004(VOID)
{
    UINT32 uwIdx;
    UINT32 uwRet;
    UINT8  ucPtNo;
    MEM_CREATEPT_PARA stPara;

    for(uwIdx = 3; uwIdx < m_ucMaxPtNum; uwIdx++)
    {
        if(m_astMemPtInfo[uwIdx].bInstalled == FALSE)
        {
            ucPtNo = uwIdx;
            break;
        }
    }

    memset(&stPara, 0, sizeof(MEM_CREATEPT_PARA));
    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = (m_aucFscMemRegion0 + 1);
    stPara.uwPtSize = (UT_SRE_FSC_MEM_PT0_SIZE - 4);

    uwRet = SRE_MemPtCreate(&stPara, ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PT_OVERLAP,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemPtCreate_005
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemPtCreate异常功能测试(用一个已创建过的分区号创建分区)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemPtCreate_005(VOID)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA stPara;

    memset(&stPara, 0, sizeof(MEM_CREATEPT_PARA));
    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = (m_aucFscMemRegion0 + 1);
    stPara.uwPtSize = (UT_SRE_FSC_MEM_PT0_SIZE - 4);

    uwRet = SRE_MemPtCreate(&stPara, g_FscPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PT_ALREADY_CREATED,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemPtCreate_006
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemPtCreate异常功能测试(所给空间太小,小于20字节)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemPtCreate_006(VOID)
{
    UINT32 uwIdx;
    UINT32 uwRet;
    UINT8  ucPtNo;
    MEM_CREATEPT_PARA stPara;

    for(uwIdx = 3; uwIdx < m_ucMaxPtNum; uwIdx++)
    {
        if(m_astMemPtInfo[uwIdx].bInstalled == FALSE)
        {
            ucPtNo = uwIdx;
            break;
        }
    }

    memset(&stPara, 0, sizeof(MEM_CREATEPT_PARA));
    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = m_aucFscMemRegion1;
    stPara.uwPtSize = 32;

    uwRet = SRE_MemPtCreate(&stPara, ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemPtCreate_007
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemPtCreate正常功能测试(大于64K大小的空间)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemPtCreate_007(VOID)
{
    UINT32 uwIdx;
    UINT32 uwRet;
    MEM_CREATEPT_PARA stPara;

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
    stPara.uwPtSize = UT_SRE_FSC_MEM_PT2_SIZE;

    uwRet = SRE_MemPtCreate(&stPara, g_FscPtNo2);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_000
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc正常功能测试
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_000(VOID)
{
    UINT32 uwRet;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo, 0x20);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}


/**
*-@test  UT_SRE_FscMemAlloc_001
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc正常功能测试
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_001(VOID)
{
    UINT32 uwRet;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo, 0x100);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}
/**
*-@test  UT_SRE_FscMemAlloc_002
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc正常功能测试(申请的内存恰好等于分区剩余内存-4字节)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_002(VOID)
{
    UINT32 uwRet;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo, 0x1DC);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_003
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc正常功能测试(申请的内存恰好等于分区剩余内存)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_003(VOID)
{
    UINT32 uwRet;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo, 0x1D0); //0x1E0
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_004
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc异常功能测试(申请的内存恰好大于分区剩余内存)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_004(VOID)
{
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo, 0x1F0);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_005
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc异常功能测试(申请的内存大小为0)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_005(VOID)
{
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo, 0);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_006
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc正常功能测试(分配较大内存0xffe0字节)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_006(VOID)
{
    UINT32 uwRet;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo2, 0xffe0);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_007
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc正常功能测试(分配较大内存0xffe0字节，再分配0xfe0字节)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_007(VOID)
{
    UINT32 uwRet;
    VOID* pAddr1 = NULL;
    VOID* pAddr2 = NULL;

    pAddr1 = SRE_MemAlloc(0, g_FscPtNo2, 0xffe0);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr1, NULL, pAddr1);

    pAddr2 = SRE_MemAlloc(0, g_FscPtNo2, 0xfe0);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr2, NULL, pAddr2);

    uwRet = SRE_MemFree(0, pAddr1);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_MemFree(0, pAddr2);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_008
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc异常功能测试(分配较大内存0xffe1字节)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_008(VOID)
{
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo2, 0xffe1);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_009
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc异常功能测试(分配较大内存0xffff字节)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_009(VOID)
{
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo2, 0xffff);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_010
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc异常功能测试,内存申请时申请的大小太大(可能为负值)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAlloc_010(VOID)
{
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo2, -1);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAlloc_001
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign正常功能测试(Align 4)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_001(VOID)
{
    UINT32 uwRet;
    UINT32 uwLowBit;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0x100, MEM_ADDR_ALIGN_004);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwLowBit = ((UINT32)pAddr << 30) >> 30;

    ICUNIT_ASSERT_EQUAL(uwLowBit, 0, uwLowBit);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_002
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign正常功能测试(Align 8)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_002(VOID)
{
    UINT32 uwRet;
    UINT32 uwLowBit;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0x100, MEM_ADDR_ALIGN_008);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwLowBit = ((UINT32)pAddr << 29) >> 29;

    ICUNIT_ASSERT_EQUAL(uwLowBit, 0, uwLowBit);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_003
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign正常功能测试(Align 8)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_003(VOID)
{
    UINT32 uwRet;
    UINT32 uwLowBit;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0x100, MEM_ADDR_ALIGN_016);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwLowBit = ((UINT32)pAddr << 28) >> 28;

    ICUNIT_ASSERT_EQUAL(uwLowBit, 0, uwLowBit);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_003
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign正常功能测试(Align 32)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_004(VOID)
{
    UINT32 uwRet;
    UINT32 uwLowBit;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0x100, MEM_ADDR_ALIGN_032);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwLowBit = ((UINT32)pAddr << 27) >> 27;

    ICUNIT_ASSERT_EQUAL(uwLowBit, 0, uwLowBit);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_005
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign正常功能测试(Align 64)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_005(VOID)
{
    UINT32 uwRet;
    UINT32 uwLowBit;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0x100, MEM_ADDR_ALIGN_064);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwLowBit = ((UINT32)pAddr << 26) >> 26;

    ICUNIT_ASSERT_EQUAL(uwLowBit, 0, uwLowBit);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_006
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign正常功能测试(Align 128)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_006(VOID)
{
    UINT32 uwRet;
    UINT32 uwLowBit;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0x100, MEM_ADDR_ALIGN_128);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwLowBit = ((UINT32)pAddr << 25) >> 25;

    ICUNIT_ASSERT_EQUAL(uwLowBit, 0, uwLowBit);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_007
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign正常功能测试(Align 256)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_007(VOID)
{
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0x100, MEM_ADDR_ALIGN_256);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_008
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign正常功能测试(组合测试)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_008(VOID)
{
    UINT32 uwRet;
    UINT32 uwLowBit;
    VOID* pAddr1 = NULL;
    VOID* pAddr2 = NULL;
    VOID* pAddr3 = NULL;
    VOID* pAddr4 = NULL;

    pAddr1 = SRE_MemAllocAlign(0, g_FscPtNo, 0x100, MEM_ADDR_ALIGN_064);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr1, NULL, pAddr1);

    uwLowBit = ((UINT32)pAddr1 << 26) >> 26;
    ICUNIT_ASSERT_EQUAL(uwLowBit, 0, uwLowBit);

    pAddr2 = SRE_MemAllocAlign(0, g_FscPtNo, 0x8, MEM_ADDR_ALIGN_004);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr2, NULL, pAddr2);

    pAddr3 = SRE_MemAllocAlign(0, g_FscPtNo, 0xA0, MEM_ADDR_ALIGN_004);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr3, NULL, pAddr3);

    pAddr4 = SRE_MemAllocAlign(0, g_FscPtNo, 0x10, MEM_ADDR_ALIGN_004);
    ICUNIT_ASSERT_EQUAL(pAddr4, NULL, pAddr4);

    uwRet = SRE_MemFree(0, pAddr1);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_MemFree(0, pAddr2);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_MemFree(0, pAddr3);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_009
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign异常功能测试(Align 值为5)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_009(VOID)
{
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0x100, 5);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    pAddr = SRE_MemAllocAlign(0, m_ucMaxPtNum + 1, 0x100, 5);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);
    //ICUNIT_ASSERT_EQUAL(pAddr, OS_ERRNO_MEM_PTNO_INVALID, pAddr);

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0, 5);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);
    //ICUNIT_ASSERT_EQUAL(pAddr, OS_ERRNO_MEM_ALLOC_SIZE_ZERO, pAddr);

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, m_ucMaxPtNum - 1, 5);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);
    //ICUNIT_ASSERT_EQUAL(pAddr, OS_ERRNO_MEM_PT_NOT_CREATED, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_010
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign异常功能测试(申请的内存大小等于0)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_010(VOID)
{
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0, MEM_ADDR_ALIGN_004);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_011
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAllocAlign异常功能测试(申请的内存恰好大于分区剩余内存)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_011(VOID)
{
    VOID* pAddr = NULL;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo, 0x1F0, MEM_ADDR_ALIGN_004);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemAllocAlign_012
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemAlloc正常功能测试(分配合适大小的内存，确保走到程序走到分支:将空闲尾段另外挂到空闲链表中)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemAllocAlign_012(VOID)
{
    VOID* pAddr = NULL;
    UINT32 uwRet;

    pAddr = SRE_MemAllocAlign(0, g_FscPtNo2, 0x90, MEM_ADDR_ALIGN_256);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    return SRE_OK;
}


/**
*-@test  UT_SRE_FscMemFree_001
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemFree异常功能测试(释放空地址)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemFree_001(VOID)
{
    UINT32 uwRet;

    uwRet = SRE_MemFree(0, NULL);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_FREE_ADDR_INVALID, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemFree_002
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemFree异常功能测试(释放未申请的内存)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemFree_002(VOID)
{
    UINT32 uwRet;

    uwRet = SRE_MemFree(0, m_aucFscMemRegion0);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_FREE_SH_DAMAGED, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemFree_003
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemFree异常功能测试(释放已经释放过的内存)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemFree_003(VOID)
{
    UINT32 uwRet;
    VOID* pAddr = NULL;

    pAddr = SRE_MemAlloc(0, g_FscPtNo, 0x100);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_FREE_SH_DAMAGED, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_FscMemFree_004
*-@tspec  私有FSC内存算法UT测试
*-@ttitle  API SRE_MemFree异常功能测试(释放FSC分区最后预留的尾部控制块内存)
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT4_UT UINT32 UT_SRE_FscMemFree_004(VOID)
{
    UINT32 uwRet;
    VOID* pAddr = (VOID*)(m_aucFscMemRegion0 + UT_SRE_FSC_MEM_PT0_SIZE - 0x10);

    uwRet = SRE_MemFree(0, pAddr);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_FREE_SH_DAMAGED, uwRet);

    return SRE_OK;
}

/*********************************************************************************/
OS_SEC_TEXT4_UT VOID UT_SRE_FscMem(VOID)
{
    UINT32 uiSuiteId;

    //SRE_WaitForAllCores();

    TEST_ADD_SUITE(uiSuiteId, "UT_SRE_FscMem");

    TEST_ADD_CASE(UT_SRE_FscMemPtCreate_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemPtCreate_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemPtCreate_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemPtCreate_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemPtCreate_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemPtCreate_006, uiSuiteId, Label_RUN);
    if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
    {
        TEST_ADD_CASE(UT_SRE_FscMemPtCreate_007, uiSuiteId, Label_RUN);
    }

    TEST_ADD_CASE(UT_SRE_FscMemAlloc_000, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAlloc_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAlloc_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAlloc_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAlloc_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAlloc_005, uiSuiteId, Label_RUN);
    if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
    {
        TEST_ADD_CASE(UT_SRE_FscMemAlloc_006, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_SRE_FscMemAlloc_007, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_SRE_FscMemAlloc_008, uiSuiteId, Label_RUN);
        TEST_ADD_CASE(UT_SRE_FscMemAlloc_009, uiSuiteId, Label_RUN);
    }
    TEST_ADD_CASE(UT_SRE_FscMemAlloc_010, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_007, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_009, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_010, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_011, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemAllocAlign_012, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_FscMemFree_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_FscMemFree_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_FscMemFree_003, uiSuiteId, Label_RUN);
   // TEST_ADD_CASE(UT_SRE_FscMemFree_004, uiSuiteId, Label_RUN);

    Ut_MemPtDelete(g_FscPtNo);
    Ut_MemPtDelete(g_FscPtNo2);

    //SRE_WaitForAllCores();

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
    Ut_MemPtDelete(g_FscPtNo);
    Ut_MemPtDelete(g_FscPtNo2);
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
/**
 * History:
 * 2009-03-30 w00181871: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              