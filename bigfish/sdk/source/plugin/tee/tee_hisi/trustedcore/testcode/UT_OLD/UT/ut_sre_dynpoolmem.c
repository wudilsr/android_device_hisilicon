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

#include "iCunit.h"
#include "sre_mem.h"
#include "sre_mem.ph"
#include "osTest.h"
#include "app_data_common.h"

extern UINT8           m_aucUtDynplmemRegion[0x00001500];
EXTERN_FAR MEM_PT_INFO_S  *m_astMemPtInfo;
extern VOID Ut_MemPtDelete(UINT8 ucPtNo);


/**
*-@test  UT_SRE_DynPoolMemPtCreate
*-@tspec  pool算法的分区创建UT测试
*-@ttitle  成功创建一个POOL私用动态内存空间
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemPtCreate(void)
{
    UINT32 pAddr;
    MEM_CREATEPT_PARA  stPara;

    stPara.enArith         = MEM_ARITH_POOL;
    stPara.pPtAddr         = &m_aucUtDynplmemRegion[0];
    stPara.uwPtSize        = 0x00001500;
    stPara.ausSliceSize[0] = 32;
    stPara.ausSliceSize[1] = 48;
    stPara.ausSliceSize[2] = 64;
    stPara.ausSliceSize[3] = 128;
    stPara.ausSliceSize[4] = 256;
    stPara.ausSliceSize[5] = 512;
    stPara.ausSliceSize[6] = 1024;
    stPara.ausSliceSize[7] = 2048;
    if (!m_astMemPtInfo[UT_LCDYNPLMEM_PTNO].bInstalled)
    {
        pAddr= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
        ICUNIT_ASSERT_EQUAL(pAddr,SRE_OK, pAddr);
    }

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_001
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  在私有动态POOL的分区成功申请内存
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_001(void)
{
    UINT32 *pAddr;
    UINT32  pAddr1;

    pAddr = SRE_MemAlloc(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1,SRE_OK,pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_002
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，1字节对齐方式，申请失败
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_002(void)
{
    UINT32 *pAddr;
    UINT32  pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, (OS_MEM_ALIGN_E)1);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_003
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，2字节对齐方式，申请失败
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_003(void)
{
    UINT32 *pAddr;
    UINT32  pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, (OS_MEM_ALIGN_E)2);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_004
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，4字节对齐方式，申请失败
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_004(void)
{
    UINT32 *pAddr;
    UINT32  pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, (OS_MEM_ALIGN_E)4);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_005
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，8字节对齐方式，申请失败
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_005(void)
{
    UINT32 *pAddr;
    UINT32  pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, (OS_MEM_ALIGN_E)8);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_006
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，16字节对齐方式，申请成功并释放
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_006(void)
{
    UINT32 *pAddr;
    UINT32  pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, MEM_ADDR_ALIGN_016);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1, SRE_OK, pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_007
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，32字节对齐方式，申请成功并释放
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_007(void)
{
    UINT32 *pAddr;
    UINT32 pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM,UT_LCDYNPLMEM_PTNO, 10, MEM_ADDR_ALIGN_032);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr,NULL,pAddr);

    pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1, SRE_OK, pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_008
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，64字节对齐方式，申请成功并释放
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_008(void)
{
    UINT32 *pAddr;
    UINT32 pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, MEM_ADDR_ALIGN_064);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr,NULL,pAddr);

    pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1, SRE_OK, pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_009
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，128字节对齐方式，申请成功并释放
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_009(void)
{
    UINT32 *pAddr;
    UINT32 pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, MEM_ADDR_ALIGN_128);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1, SRE_OK, pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_010
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，256字节对齐方式，申请成功并释放
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_010(void)
{
    UINT32 *pAddr;
    UINT32 pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, MEM_ADDR_ALIGN_256);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1, SRE_OK, pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_011
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，512字节对齐方式，申请成功并释放
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_011(void)
{
    UINT32 *pAddr;
    UINT32 pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10,  (OS_MEM_ALIGN_E)512);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1, OS_ERRNO_MEM_FREE_ADDR_INVALID, pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_012
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，1024字节对齐方式，申请成功并释放
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_012(void)
{
    UINT32 *pAddr;
    UINT32 pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, (OS_MEM_ALIGN_E)1024);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1, OS_ERRNO_MEM_FREE_ADDR_INVALID, pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_013
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，申请大小大于最大块大小，申请失败
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_013(void)
{
    UINT32 *pAddr;
    UINT32 pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, 30, 8000,  MEM_ADDR_ALIGN_032);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 0,  MEM_ADDR_ALIGN_032);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 8000,  MEM_ADDR_ALIGN_032);
    ICUNIT_ASSERT_EQUAL(pAddr, NULL, pAddr);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_014
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，反复申请释放内存10次，16字节方式对齐
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_014(void)
{
    UINT32 *pAddr[10];
    UINT32 pAddr1;
    UINT32 i;
    UINT32 uwFlag    = 0;
    for(i = 0; i < 10; i++)
    {
        pAddr[i] = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, MEM_ADDR_ALIGN_016);
        if(NULL == pAddr[i])
        {
            uwFlag = 1;
        }
    }

    ICUNIT_ASSERT_EQUAL(uwFlag, 0, pAddr);

    if(0 == uwFlag)
    {
        for(i = 0; i < 10; i++)
        {
            pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr[i]);
            ICUNIT_ASSERT_EQUAL(pAddr1, SRE_OK, pAddr1);
        }
    }

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_015
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，反复申请释放内存10次，无对齐
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_015(void)
{
    UINT32 *pAddr[10];
    UINT32 pAddr1;
    UINT32 i;
    UINT32 uwFlag = 0;
    for(i = 0; i < 10; i++)
    {
        pAddr[i] = SRE_MemAlloc(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10);
        if(NULL == pAddr[i])
        {
            uwFlag = 1;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwFlag, 0, uwFlag);

    if(0 == uwFlag)
    {
        for(i = 0; i < 10; i++)
        {
            pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr[i]);
            ICUNIT_ASSERT_EQUAL(pAddr1, SRE_OK, pAddr1);
        }
    }

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_016
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，申请内存后重复释放内存
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_016(void)
{
    UINT32 *pAddr;
    UINT32  pAddr1;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, MEM_ADDR_ALIGN_064);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    if(pAddr != NULL)
    {
        pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
        ICUNIT_ASSERT_EQUAL(pAddr1, SRE_OK,pAddr1);
    }

    pAddr1 =SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1, OS_ERRNO_MEM_FREE_POOL_MEM_ALREADY_FREE,pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_017
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，反复申请释放内存9次，64字节对齐方式
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_017(void)
{
    UINT32 *pAddr[20];
    UINT32  pAddr1;
    UINT32  uwLoop;

    for(uwLoop = 0; uwLoop < 9; uwLoop++)
    {
        pAddr[uwLoop] = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 100, MEM_ADDR_ALIGN_064);
        ICUNIT_ASSERT_NOT_EQUAL(pAddr,NULL,pAddr[uwLoop]);
    }

    for(uwLoop = 0; uwLoop < 9; uwLoop++)
    {
        pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr[uwLoop]);
        ICUNIT_ASSERT_EQUAL(pAddr1, SRE_OK, pAddr1);
    }

    return SRE_OK;
}

/**
*-@test   UT_SRE_DynPoolMemAlloc_018
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  私有动态POOL的分区内存申请，被申请块控制头魔术字被踩后申请内存失败
*-@tprecon 只在LSI和Tensilica中严重
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_018(void)
{
    UINT32 *pAddr;
    UINT32  pAddr1;
    OS_MEM_SLICE_CTRL_HEAD_S    *pstSHead;    /* 指向将被申请的块所在页的页控制头 */
    UINT32 *pAddr2;

    pAddr = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, MEM_ADDR_ALIGN_064);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    if(pAddr != NULL)
    {
        pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
        ICUNIT_ASSERT_EQUAL(pAddr1,SRE_OK,pAddr1);
    }

    pstSHead = (OS_MEM_SLICE_CTRL_HEAD_S *)(*((UINT32 *)pAddr - 1));
    ICUNIT_ASSERT_EQUAL(pstSHead->uwHead,OS_SLICE_HEAD_MAGICWORD,pstSHead->uwHead);

    pstSHead->uwHead = OS_SLICE_HEAD_MAGICWORD - 1;

    pAddr2 = SRE_MemAllocAlign(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10, MEM_ADDR_ALIGN_064);
    ICUNIT_ASSERT_EQUAL(pAddr2, NULL, pAddr2);

    pstSHead=(OS_MEM_SLICE_CTRL_HEAD_S *)(*((UINT32 *)pAddr - 1));
    ICUNIT_ASSERT_EQUAL(pstSHead->uwHead,OS_SLICE_HEAD_MAGICWORD - 1,pstSHead->uwHead);

    pstSHead->uwHead = OS_SLICE_HEAD_MAGICWORD;

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_019
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  POOL内存头被踩然后进行释放操作
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_019(void)
{
    UINT32 *pAddr;
    UINT32  pAddr1;
    OS_MEM_SLICE_CTRL_HEAD_S  *pstSHead; /* 指向将被申请的块所在页的页控制块 */

    pAddr = SRE_MemAlloc(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 10);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr, NULL, pAddr);

    pstSHead = (OS_MEM_SLICE_CTRL_HEAD_S *)(*((UINT32 *)pAddr - 1));
    pstSHead->uwHead = 0x12345678;//内存头被踩

    pAddr1 = SRE_MemFree(OS_MID_MEM, pAddr);
    ICUNIT_ASSERT_EQUAL(pAddr1,OS_ERRNO_MEM_FREE_SH_DAMAGED,pAddr1);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemAlloc_020
*-@tspec  私有动态POOL分区内存申请UT测试
*-@ttitle  动态POOL内存申请时内存空间不够
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemAlloc_020(void)
{
    UINT32 *pAddr1;
    UINT32 *pAddr2;
    UINT32 *pAddr3;

    UINT32  pAddrA;
    UINT32  pAddrB;
    UINT32  pAddrC;

    UINT32 pAddr;
    MEM_CREATEPT_PARA  stPara;

    stPara.enArith         = MEM_ARITH_POOL;
    stPara.pPtAddr         = &m_aucUtDynplmemRegion[0];
    stPara.uwPtSize        = 0x00001500;
    stPara.ausSliceSize[0] = 32;
    stPara.ausSliceSize[1] = 48;
    stPara.ausSliceSize[2] = 64;
    stPara.ausSliceSize[3] = 128;
    stPara.ausSliceSize[4] = 256;
    stPara.ausSliceSize[5] = 512;
    stPara.ausSliceSize[6] = 1024;
    stPara.ausSliceSize[7] = 2048;

    Ut_MemPtDelete(UT_LCDYNPLMEM_PTNO);

    pAddr= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(pAddr,SRE_OK, pAddr);

    pAddr1 = SRE_MemAlloc(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 2048);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr1, NULL, pAddr1);

    pAddr2 = SRE_MemAlloc(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 2048);
    ICUNIT_ASSERT_NOT_EQUAL(pAddr2, NULL, pAddr2);

    pAddr3 = SRE_MemAlloc(OS_MID_MEM, UT_LCDYNPLMEM_PTNO, 2048);
    ICUNIT_ASSERT_EQUAL(pAddr3, NULL, pAddr3);  /*内存申请失败*/

    pAddrA = SRE_MemFree(OS_MID_MEM, pAddr1);
    ICUNIT_ASSERT_EQUAL(pAddrA,SRE_OK,pAddrA);

    pAddrB = SRE_MemFree(OS_MID_MEM, pAddr2);
    ICUNIT_ASSERT_EQUAL(pAddrB,SRE_OK,pAddrB);

    pAddrC = SRE_MemFree(OS_MID_MEM, pAddr3);
    ICUNIT_ASSERT_EQUAL(pAddrA,NULL,pAddrA);

    return SRE_OK;
}

OS_SEC_TEXT3_UT void UT_SRE_DynPoolMem(void)
{
    iUINT32 uiSuiteId;
    TEST_ADD_SUITE(uiSuiteId, "UT_SRE_DynPoolMem");

    //SRE_WaitForAllCores();
    TEST_ADD_CASE(UT_SRE_DynPoolMemPtCreate, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_009, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_010, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_011, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_012, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_013, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_014, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_015, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_016, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_017, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_018, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_019, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemAlloc_020, uiSuiteId, Label_RUN);

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
