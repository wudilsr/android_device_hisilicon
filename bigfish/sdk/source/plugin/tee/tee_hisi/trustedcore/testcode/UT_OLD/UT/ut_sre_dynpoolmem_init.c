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

#include "sre_mem.h"
#include "sre_mem.ph"
#include "iCunit.h"
#include "osTest.h"
#include "app_data_common.h"


extern UINT8  m_aucUtDynplmemRegion[0x00001500];
extern UINT32 osDynPoolMemRegister(VOID);
extern VOID Ut_MemPtDelete(UINT8 ucPtNo);
EXTERN_FAR MEM_PT_INFO_S  *m_astMemPtInfo;

/**
*-@test  UT_SRE_DynPoolMemRegister
*-@tspec  pool�㷨�ķ�����Ϣע��UT����
*-@ttitle  pool�㷨�ķ�����Ϣ����ע��
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemRegister(void)
{
    UINT32 uwRet;

    uwRet = osDynPoolMemRegister();
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemPtCreate_001
*-@tspec  pool�㷨�ķ�������UT����
*-@ttitle  ����һ��POOL˽�ö�̬�ڴ�ռ䣬�ռ��С
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemPtCreate_001(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA  stPara;

    stPara.enArith         = MEM_ARITH_POOL;
    stPara.pPtAddr         = &m_aucUtDynplmemRegion[0];
    stPara.uwPtSize        = 0x00000010;
    stPara.ausSliceSize[0] = 32;
    stPara.ausSliceSize[1] = 48;
    stPara.ausSliceSize[2] = 64;
    stPara.ausSliceSize[3] = 128;
    stPara.ausSliceSize[4] = 256;
    stPara.ausSliceSize[5] = 512;
    stPara.ausSliceSize[6] = 1024;
    stPara.ausSliceSize[7] = 2048;

    uwRet= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemPtCreate_002
*-@tspec  pool�㷨�ķ�������UT����
*-@ttitle  ������СС�������С
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemPtCreate_002(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA  stPara;

    stPara.enArith         = MEM_ARITH_POOL;
    stPara.pPtAddr         = &m_aucUtDynplmemRegion[0];
    stPara.uwPtSize        = 0x200;
    stPara.ausSliceSize[0] = 32;
    stPara.ausSliceSize[1] = 48;
    stPara.ausSliceSize[2] = 64;
    stPara.ausSliceSize[3] = 128;
    stPara.ausSliceSize[4] = 256;
    stPara.ausSliceSize[5] = 512;
    stPara.ausSliceSize[6] = 1024;
    stPara.ausSliceSize[7] = 2048;

    uwRet= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemPtCreate_003
*-@tspec  pool�㷨�ķ�������UT����
*-@ttitle  ����Ŀ����Ͳ��ǵ�����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemPtCreate_003(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA  stPara;

    stPara.enArith         = MEM_ARITH_POOL;
    stPara.pPtAddr         = &m_aucUtDynplmemRegion[0];
    stPara.uwPtSize        = 0x1500;
    stPara.ausSliceSize[0] = 32;
    stPara.ausSliceSize[1] = 48;
    stPara.ausSliceSize[2] = 64;
    stPara.ausSliceSize[3] = 128;
    stPara.ausSliceSize[4] = 0;
    stPara.ausSliceSize[5] = 0;
    stPara.ausSliceSize[6] = 1024;
    stPara.ausSliceSize[7] = 2048;

    uwRet= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(uwRet,NULL,  uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemPtCreate_004
*-@tspec  pool�㷨�ķ�������UT����
*-@ttitle  �ɹ�����һ��POOL˽�ö�̬�ڴ�ռ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemPtCreate_004(void)
{
    UINT32 uwRet;
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
    uwRet= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(uwRet,NULL, uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemPtCreate_005
*-@tspec  pool�㷨�ķ�������UT����
*-@ttitle  ��һ���Ѿ��������ڴ�ռ䴴��һ��POOL˽�ö�̬�ڴ�ռ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemPtCreate_005(void)
{
    UINT32 uwRet;
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
    uwRet= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(uwRet,NULL,  uwRet);

    return SRE_OK;
}

/**
*-@test  UT_SRE_DynPoolMemPtCreate_006
*-@tspec  pool�㷨�ķ�������UT����
*-@ttitle  �����ص�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT3_UT UINT32 UT_SRE_DynPoolMemPtCreate_006(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA  stPara;

    stPara.enArith         = MEM_ARITH_POOL;
    stPara.pPtAddr         = &m_aucUtDynplmemRegion[0] + 1;
    stPara.uwPtSize        = 0x1500;
    stPara.ausSliceSize[0] = 32;
    stPara.ausSliceSize[1] = 48;
    stPara.ausSliceSize[2] = 64;
    stPara.ausSliceSize[3] = 128;
    stPara.ausSliceSize[4] = 256;
    stPara.ausSliceSize[5] = 512;
    stPara.ausSliceSize[6] = 1024;
    stPara.ausSliceSize[7] = 2048;

    uwRet= SRE_MemPtCreate(&stPara, UT_LCDYNPLMEM_PTNO);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PT_ALREADY_CREATED,  uwRet);

    return SRE_OK;
}



OS_SEC_TEXT3_UT void UT_SRE_DynPoolMem_Init(void)
{
    iUINT32 uiSuiteId;
    TEST_ADD_SUITE(uiSuiteId, "UT_SRE_DynPoolMem_Init");

    ////SRE_WaitForAllCores();
    TEST_ADD_CASE(UT_SRE_DynPoolMemRegister, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemPtCreate_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemPtCreate_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemPtCreate_003, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_DynPoolMemPtCreate_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemPtCreate_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_DynPoolMemPtCreate_006, uiSuiteId, Label_RUN);

    ////SRE_WaitForAllCores();
    Ut_MemPtDelete(UT_LCDYNPLMEM_PTNO);
    ////SRE_WaitForAllCores();

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
    Ut_MemPtDelete(UT_LCDYNPLMEM_PTNO);

}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
