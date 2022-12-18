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

#include "iCunit.h"
#include "app_data_common.h"
#include "Set_Peg.h"
#include "sre_config.h"
#include "sre_sys.h"
#include "sre_mem.h"
#include "sre_mem.ph"
#include "osTest.h"


extern UINT8 m_aucUtStmemRegion[UT_STATMEM_SIZE];
extern UINT8 m_aucUtDymemRegion[0x00001500];
extern UINT8 m_aucUtDynplmemRegion[0x00001500];
extern UINT8 m_aucUtMcmemRegion[0x00005000];

EXTERN_FAR MEM_PT_INFO_S  *m_astMemPtInfo;
EXTERN_FAR MEM_PT_CHECK_S *g_astMemPtCheck;
EXTERN_FAR UINT8  m_ucMaxPtNum;

extern UINT32 osMemRegMemPtInfo(UINT8 scPtNo, UINT32 uwSize, VOID *pAddr,  OS_MEM_ARITH_E enArith);
extern VOID Ut_MemPtDelete(UINT8 ucPtNo);

OS_SEC_BSS_SHARED UINT8 g_usCoreIDFirst ;
OS_SEC_BSS_SHARED UINT8 g_usCoreIDSecond;

/**
*@test UT_SRE_Mem_InitT_001
*-@tspec �ڴ�����������
*-@ttitle  �ȴ���һ��POOL�����������ɹ����ٴ���һ����ͬSlice��С��POOL������
           ������С��С������ʧ�ܣ��ٴ���һ����ͬSlice��С��POOL�������������ڴ棬���Ƿ�ɹ�
*-@tprecon  ���Ǵ�����ͬSlice��ķ�����������һ��SIZETOTYPE��ķ���������������ʧ��ʱ�᲻�ụ��Ӱ��
*-@tbrief
*-1.
*-@texpect
*-1.
*-@tprior 1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_Mem_Init_001()
{
    UINT32              uwRet;
    MEM_CREATEPT_PARA   stMemPara;
    UINT32              uwIndex;
    VOID                *pAddr[6];


    stMemPara.enArith         = MEM_ARITH_POOL  ;
    stMemPara.bCachable       = FALSE;
    stMemPara.uwPtSize        = 0x200;
    stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x0];
    stMemPara.ausSliceSize[0] = 16;
    stMemPara.ausSliceSize[1] = 32;
    stMemPara.ausSliceSize[2] = 64;
    stMemPara.ausSliceSize[3] = 128;
    stMemPara.ausSliceSize[4] = 256;
    stMemPara.ausSliceSize[5] = 0;
    stMemPara.ausSliceSize[6] = 0;
    stMemPara.ausSliceSize[7] = 0;

    //SRE_WaitForAllCores();

    if( OS_SYS_CORE_MASTER == SRE_GetCoreID() )
    {
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT10);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

        stMemPara.uwPtSize        = 0x2;
        stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x200];
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL, uwRet);

        stMemPara.uwPtSize        = 0x200;
        stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x400];
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT9);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        for (uwIndex = 0; uwIndex < 5; uwIndex ++)
        {
            pAddr[uwIndex]  = SRE_MemAlloc(0, TEST_MEM_POOL_PT9, 16 * ( uwIndex + 1 ));
            ICUNIT_ASSERT_NOT_EQUAL((UINT32)pAddr[uwIndex], NULL, (UINT32)pAddr[uwIndex]);
        }
        for (uwIndex = 0; uwIndex < 5; uwIndex ++)
        {
            uwRet = SRE_MemFree(0, pAddr[uwIndex]);
            ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        }
        Ut_MemPtDelete(TEST_MEM_POOL_PT10);
        Ut_MemPtDelete(TEST_MEM_POOL_PT9);
     }

    //SRE_WaitForAllCores();
    return SRE_OK;
}

/**
*@test UT_SRE_Mem_Init_002
*-@tspec �ڴ�����������
*-@ttitle  �ȴ���һ��POOL�����������ɹ����ٴ���һ����ͬSlice��С��POOL������
           ������С��С������ʧ�ܣ��ٴ���һ����ͬSlice��С��POOL�������������ڴ棬���Ƿ�ɹ�
*-@tprecon  ���Ǵ�����ͬSlice��ķ�����������һ��SIZETOTYPE��ķ���������������ʧ��ʱ�᲻�ụ��Ӱ��
*-@tbrief
*-1.
*-@texpect
*-1.
*-@tprior 1
*-@tauto TRUE
*-@tremark
*/

OS_SEC_TEXT2_UT UINT32 UT_SRE_Mem_Init_002()
{
    UINT32              uwRet;
    MEM_CREATEPT_PARA   stMemPara;

    UINT32              uwIndex;
    VOID                *pAddr[6];

    stMemPara.enArith         = MEM_ARITH_MCPOOL  ;
    stMemPara.bCachable       = FALSE;
    stMemPara.uwPtSize        = 0x200;
    stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x0];
    stMemPara.ausSliceSize[0] = 16;
    stMemPara.ausSliceSize[1] = 32;
    stMemPara.ausSliceSize[2] = 64;
    stMemPara.ausSliceSize[3] = 128;
    stMemPara.ausSliceSize[4] = 256;
    stMemPara.ausSliceSize[5] = 0;
    stMemPara.ausSliceSize[6] = 0;
    stMemPara.ausSliceSize[7] = 0;

    //SRE_WaitForAllCores();

    if( OS_SYS_CORE_MASTER == SRE_GetCoreID() )
    {
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT13);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

        stMemPara.uwPtSize        = 0x2;
        stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x200];
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL, uwRet);

        stMemPara.uwPtSize        = 0x200;
        stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x400];

        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT9);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

        for (uwIndex = 0; uwIndex < 5; uwIndex ++)
        {
            pAddr[uwIndex]  = SRE_MemAlloc(0, TEST_MEM_POOL_PT9, 16 * ( uwIndex + 1 ));
            ICUNIT_ASSERT_NOT_EQUAL((UINT32)pAddr[uwIndex], NULL, (UINT32)pAddr[uwIndex]);
        }

        for (uwIndex = 0; uwIndex < 5; uwIndex ++)
        {
            uwRet  = SRE_MemFree(0, pAddr[uwIndex]);
            ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        }

        Ut_MemPtDelete(TEST_MEM_POOL_PT13);
        Ut_MemPtDelete(TEST_MEM_POOL_PT9);
     }

    //SRE_WaitForAllCores();
    return SRE_OK;
}

/**
*@test UT_SRE_MEM_INIT_003
*-@tspec �ڴ�����������
*-@ttitle  ��ͬ��ʹ��ͬһ�����ţ�������ͬ�㷨�Ĺ�����������ش�����OS_ERRNO_MEM_SHARE_PARA_INCONSISTENT
*-@tprecon
*-@tbrief
*-1.
*-@texpect
*-1.
*-@tprior 1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_Mem_Init_003()
{
    UINT32              uwRet;
    MEM_CREATEPT_PARA   stMemPara;

    stMemPara.enArith         = MEM_ARITH_MCPOOL  ;
    stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x0];
    stMemPara.uwPtSize        = 0x200;
    stMemPara.bCachable       = TRUE;
    stMemPara.ausSliceSize[0] = 0;
    stMemPara.ausSliceSize[1] = 0;
    stMemPara.ausSliceSize[2] = 0;
    stMemPara.ausSliceSize[3] = 0;
    stMemPara.ausSliceSize[4] = 0;
    stMemPara.ausSliceSize[5] = 16;
    stMemPara.ausSliceSize[6] = 32;
    stMemPara.ausSliceSize[7] = 64;

    /** �ñ���g_usCoreIDFirst��g_usCoreIDSecond��¼�˺ţ�ÿ��ƽ̨���������ò�һ����������������Ϊ�ж����� **/
    g_usCoreIDFirst  = 100;
    g_usCoreIDSecond = 100;
    //SRE_WaitForAllCores();
    if ( 100 == g_usCoreIDFirst)
    {
        g_usCoreIDFirst  = SRE_GetCoreID();
    }
    if ( SRE_GetCoreID() != g_usCoreIDFirst)
    {
        g_usCoreIDSecond = SRE_GetCoreID();
    }

    //SRE_WaitForAllCores();
    if (g_usCoreIDFirst == SRE_GetCoreID())
    {
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();
    if ( g_usCoreIDSecond == SRE_GetCoreID())
    {
        stMemPara.enArith = MEM_ARITH_MCDYNFSC;
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
        ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_SHARE_PARA_INCONSISTENT,uwRet);
    }

    //SRE_WaitForAllCores();
    g_usCoreIDFirst = 100;
    g_usCoreIDSecond = 100;
    Ut_MemPtDelete(TEST_MEM_POOL_PT8);
    //SRE_WaitForAllCores();

    return SRE_OK;
}

/**
*@test UT_SRE_MEM_INIT_004
*-@tspec �ڴ�����������
*-@ttitle  ��ͬ��ʹ��ͬһ�����ţ�������ͬ�㷨�Ĺ����������������С ��һ�������ش�����OS_ERRNO_MEM_SHARE_PARA_INCONSISTENT
*-@tprecon
*-@tbrief
*-1.
*-@texpect
*-1.
*-@tprior 1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_Mem_Init_004()
{
    UINT32              uwRet;
    MEM_CREATEPT_PARA   stMemPara;

    stMemPara.enArith         = MEM_ARITH_MCPOOL  ;
    stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x0];
    stMemPara.uwPtSize        = 0x200;
    stMemPara.bCachable       = TRUE;
    stMemPara.ausSliceSize[0] = 0;
    stMemPara.ausSliceSize[1] = 0;
    stMemPara.ausSliceSize[2] = 0;
    stMemPara.ausSliceSize[3] = 0;
    stMemPara.ausSliceSize[4] = 0;
    stMemPara.ausSliceSize[5] = 16;
    stMemPara.ausSliceSize[6] = 32;
    stMemPara.ausSliceSize[7] = 64;

    /** �ñ���g_usCoreIDFirst��g_usCoreIDSecond��¼�˺ţ�ÿ��ƽ̨���������ò�һ����������������Ϊ�ж����� **/
    g_usCoreIDFirst  = 100;
    g_usCoreIDSecond = 100;
    //SRE_WaitForAllCores();
    if ( 100 == g_usCoreIDFirst)
    {
        g_usCoreIDFirst  = SRE_GetCoreID();
    }
    if ( SRE_GetCoreID() != g_usCoreIDFirst)
    {
        g_usCoreIDSecond = SRE_GetCoreID();
    }

    //SRE_WaitForAllCores();
    if (g_usCoreIDFirst == SRE_GetCoreID())
    {
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();
    if (g_usCoreIDSecond == SRE_GetCoreID())
    {
        stMemPara.uwPtSize = 0x300;
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
        ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_SHARE_PARA_INCONSISTENT,uwRet);
    }

    //SRE_WaitForAllCores();
    g_usCoreIDFirst = 100;
    g_usCoreIDSecond = 100;
    Ut_MemPtDelete(TEST_MEM_POOL_PT8);
    //SRE_WaitForAllCores();

    return SRE_OK;
}

/**
*@test UT_SRE_MEM_INIT_005
*-@tspec �ڴ�����������
*-@ttitle  ��ͬ��ʹ��ͬһ�����ţ�������ͬ�㷨�Ȳ�����ȫһ�µķ������������������ص������ش�����OS_ERRNO_MEM_PT_OVERLAP
*-@tprecon
*-@tbrief
*-1.
*-@texpect
*-1.
*-@tprior 1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_Mem_Init_005()
{
    UINT32              uwRet;
    MEM_CREATEPT_PARA   stMemPara;

    stMemPara.enArith         = MEM_ARITH_MCPOOL  ;
    stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x0];
    stMemPara.uwPtSize        = 0x200;
    stMemPara.bCachable       = TRUE;
    stMemPara.ausSliceSize[0] = 0;
    stMemPara.ausSliceSize[1] = 0;
    stMemPara.ausSliceSize[2] = 0;
    stMemPara.ausSliceSize[3] = 0;
    stMemPara.ausSliceSize[4] = 0;
    stMemPara.ausSliceSize[5] = 16;
    stMemPara.ausSliceSize[6] = 32;
    stMemPara.ausSliceSize[7] = 64;

    /** �ñ���g_usCoreIDFirst��g_usCoreIDSecond��¼�˺ţ�ÿ��ƽ̨���������ò�һ����������������Ϊ�ж����� **/
    g_usCoreIDFirst  = 100;
    g_usCoreIDSecond = 100;
    //SRE_WaitForAllCores();
    if ( 100 == g_usCoreIDFirst)
    {
        g_usCoreIDFirst  = SRE_GetCoreID();
    }
    if ( SRE_GetCoreID() != g_usCoreIDFirst)
    {
        g_usCoreIDSecond = SRE_GetCoreID();
    }

    //SRE_WaitForAllCores();
    if (g_usCoreIDFirst == SRE_GetCoreID())
    {
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);
    }

    //SRE_WaitForAllCores();
    if (g_usCoreIDSecond == SRE_GetCoreID())
    {
        stMemPara.pPtAddr = &m_aucUtMcmemRegion[0x200];
        stMemPara.enArith = MEM_ARITH_POOL  ;
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT13);
        ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

        stMemPara.pPtAddr  = &m_aucUtMcmemRegion[0x0];
        stMemPara.uwPtSize = 0x300;
        uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
        ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PT_OVERLAP,uwRet);
    }

    //SRE_WaitForAllCores();
    g_usCoreIDFirst = 100;
    g_usCoreIDSecond = 100;
    Ut_MemPtDelete(TEST_MEM_POOL_PT8);
    Ut_MemPtDelete(TEST_MEM_POOL_PT13);

    //SRE_WaitForAllCores();

    return SRE_OK;
}

/**
*@test UT_SRE_MEM_INIT_006
*-@tspec �ڴ�����������
*-@ttitle  ����POOL�㷨������С���������ش�����OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL
*-@tprecon
*-@tbrief
*-1.
*-@texpect
*-1.
*-@tprior 1
*-@tauto TRUE
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_Mem_Init_006()
{
    UINT32              uwRet;
    MEM_CREATEPT_PARA   stMemPara;

    stMemPara.enArith         = MEM_ARITH_MCPOOL  ;
    stMemPara.pPtAddr         = &m_aucUtMcmemRegion[0x0];
    stMemPara.uwPtSize        = 0x20;
    stMemPara.bCachable       = TRUE;
    stMemPara.ausSliceSize[0] = 0;
    stMemPara.ausSliceSize[1] = 0;
    stMemPara.ausSliceSize[2] = 0;
    stMemPara.ausSliceSize[3] = 0;
    stMemPara.ausSliceSize[4] = 0;
    stMemPara.ausSliceSize[5] = 16;
    stMemPara.ausSliceSize[6] = 32;
    stMemPara.ausSliceSize[7] = 64;

    //SRE_WaitForAllCores();
    uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL,uwRet);

    //SRE_WaitForAllCores();
    stMemPara.ausSliceSize[0] = 16;
    stMemPara.ausSliceSize[1] = 0;
    stMemPara.ausSliceSize[2] = 64;
    stMemPara.ausSliceSize[3] = 0;
    stMemPara.ausSliceSize[4] = 32;
    stMemPara.ausSliceSize[5] = 0;
    stMemPara.ausSliceSize[6] = 0;
    stMemPara.ausSliceSize[7] = 0;
    stMemPara.uwPtSize        = 0x200;

    //SRE_WaitForAllCores();
    uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_MEMSLICE_NOT_INORDER,uwRet);

    //SRE_WaitForAllCores();
    stMemPara.ausSliceSize[0] = 0;
    stMemPara.ausSliceSize[1] = 0;
    stMemPara.ausSliceSize[2] = 0;
    stMemPara.ausSliceSize[3] = 0;
    stMemPara.ausSliceSize[4] = 0;
    stMemPara.ausSliceSize[5] = 0;
    stMemPara.ausSliceSize[6] = 0;
    stMemPara.ausSliceSize[7] = 0;
    stMemPara.uwPtSize        = 0x200;

    //SRE_WaitForAllCores();
    uwRet = SRE_MemPtCreate(&stMemPara, TEST_MEM_POOL_PT8);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_ALLSLICE_ZERO,uwRet);

    //SRE_WaitForAllCores();
    return SRE_OK;
}

/**
*-@test  UT_SRE_MemInitPtCreate_001
*-@tspec  ���������ӿڲ��ԡ�
*-@ttitle ���������Ŵ��ڻ�����������������Ƿ����
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemInitPtCreate_001(void)
{
    UINT32 uwRet;
    UINT32 uwEnArith;
    MEM_CREATEPT_PARA stPara;

    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = m_aucUtStmemRegion;
    stPara.uwPtSize = sizeof(m_aucUtStmemRegion);
    stPara.ausSliceSize[0] = 32;
    stPara.ausSliceSize[1] = 48;
    stPara.ausSliceSize[2] = 64;
    stPara.ausSliceSize[3] = 128;
    stPara.ausSliceSize[4] = 256;
    stPara.ausSliceSize[5] = 512;
    stPara.ausSliceSize[6] = 1024;
    stPara.ausSliceSize[7] = 2048;

    /* �����ŵ����������� */
    uwRet = SRE_MemPtCreate(&stPara, m_ucMaxPtNum);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTNO_INVALID,uwRet);

    /* �����Ŵ����������� */
    uwRet = SRE_MemPtCreate(&stPara, (m_ucMaxPtNum + 1));
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTNO_INVALID,uwRet);

    /* ������С��ϵͳĬ�Ϸ����� */
    uwRet = SRE_MemPtCreate(NULL, 0);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTNO_INVALID,uwRet);

    /* �������ò���Ϊ�� */
    uwRet = SRE_MemPtCreate(NULL, (m_ucMaxPtNum + 1));
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTNO_INVALID,uwRet);

    /* �����㷨�Ƿ� */
    stPara.enArith = MEM_ARITH_BUTT;
    uwRet = SRE_MemPtCreate(&stPara, (m_ucMaxPtNum - 1));
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PT_ARITH_INVALID,uwRet);

    return ICUNIT_SUCCESS;
}

#if 0
/**
*-@test  UT_SRE_MemInitPtCreate_002
*-@tspec  ���������ڲ��ӿ�osMemPtCtrlAlloc���ԡ�
*-@ttitle ����̬fsc�ڴ治�㣬�����Ĺ���pool������С̫С
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/

OS_SEC_TEXT2_UT VOID * UT_SRE_MemInitPtCreate_002_Test(UINT32 uwMid, UINT8 ucPtNo, UINT32 uwSize, OS_MEM_ALIGN_E enAlignPow)
{
    return NULL;
}

OS_SEC_TEXT2_UT UINT32 UT_SRE_MemInitPtCreate_002(void)
{
    UINT32 uwRet;
    MEM_CREATEPT_PARA stPara;
    VOID *pPtCtrl;
    UINT8 ucPtNo = 6;
    SETPEG_JMP_ST stIncSave;

    stPara.enArith = MEM_ARITH_MCPOOL;
    stPara.pPtAddr = (VOID *)(((UINT32)m_aucUtMcmemRegion > 0x80000000) ? ((UINT32)m_aucUtMcmemRegion - 0x80000000) : (UINT32)m_aucUtMcmemRegion);
    stPara.uwPtSize = sizeof(m_aucUtMcmemRegion);
    stPara.ausSliceSize[0] = 32;
    stPara.ausSliceSize[1] = 48;
    stPara.ausSliceSize[2] = 64;
    stPara.ausSliceSize[3] = 128;
    stPara.ausSliceSize[4] = 256;
    stPara.ausSliceSize[5] = 512;
    stPara.ausSliceSize[6] = 1024;
    stPara.ausSliceSize[7] = 2048;

    /* ����̬fsc�ڴ�̫С */
    SET_PEG(SRE_MemAllocAlign, UT_SRE_MemInitPtCreate_002_Test, &stIncSave);

    pPtCtrl = g_astMemPtCheck[ucPtNo].pPtCtrl;
    g_astMemPtCheck[ucPtNo].pPtCtrl = NULL;
    uwRet = SRE_MemPtCreate(&stPara, ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MCSTA_FSCMEM_ALLOC_NO_MEMORY,uwRet);
    g_astMemPtCheck[ucPtNo].pPtCtrl = pPtCtrl;

    CLEAN_PEG(SRE_MemAllocAlign, stIncSave);

    /* �����ķ�����С̫С */
    stPara.uwPtSize = OS_CACHE_LINE_SIZE - 1;
    uwRet = SRE_MemPtCreate(&stPara, ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_PTCREATE_SIZE_TOOSMALL,uwRet);

    return ICUNIT_SUCCESS;
}
#endif

/**
*-@test  UT_SRE_MemInitPtCreate_003
*-@tspec  ���������ӿڲ��ԡ�
*-@ttitle ��������,�����㷨�Ƿ�
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior
*-@tremark
*/
OS_SEC_TEXT2_UT UINT32 UT_SRE_MemInitPtCreate_003(void)
{
    UINT32 uwRet;
    UINT32 uwEnArith;
    MEM_CREATEPT_PARA stPara;
    MEM_PTCREATE_F  pfnPtCreate;

    stPara.enArith = MEM_ARITH_FSC;
    stPara.pPtAddr = m_aucUtStmemRegion;
    stPara.uwPtSize = sizeof(m_aucUtStmemRegion);

    pfnPtCreate = m_astMemArithAPI[MEM_ARITH_FSC].pfnPtCreate;

    //SRE_WaitForAllCores();

    m_astMemArithAPI[MEM_ARITH_FSC].pfnPtCreate = NULL;

    //SRE_WaitForAllCores();

    uwRet = SRE_MemPtCreate(&stPara, m_ucMaxPtNum - 2);

    //SRE_WaitForAllCores();
    m_astMemArithAPI[MEM_ARITH_FSC].pfnPtCreate = pfnPtCreate;
    //SRE_WaitForAllCores();

    ICUNIT_ASSERT_EQUAL(uwRet,OS_ERRNO_MEM_ALGORITHM_UNINSTALLED,uwRet);

    //SRE_WaitForAllCores();

    return ICUNIT_SUCCESS;
}

OS_SEC_TEXT2_UT void UT_SRE_Mem_Init(void)
{
    iUINT32 uiSuiteId;
    //SRE_WaitForAllCores();
    TEST_ADD_SUITE(uiSuiteId, "UT_SRE_Mem_Init");

    TEST_ADD_CASE(UT_SRE_Mem_Init_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_Mem_Init_002, uiSuiteId, Label_RUN);

    //TEST_ADD_CASE(UT_SRE_Mem_Init_003, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_Mem_Init_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_Mem_Init_005, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_Mem_Init_006, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_MemInitPtCreate_001, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_MemInitPtCreate_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemInitPtCreate_003, uiSuiteId, Label_RUN);
    //SRE_WaitForAllCores();
    Ut_MemPtDelete(TEST_MEM_POOL_PT8);
    Ut_MemPtDelete(TEST_MEM_POOL_PT9);
    Ut_MemPtDelete(TEST_MEM_POOL_PT10);
    Ut_MemPtDelete(TEST_MEM_POOL_PT13);
    //SRE_WaitForAllCores();

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
    Ut_MemPtDelete(TEST_MEM_POOL_PT8);
    Ut_MemPtDelete(TEST_MEM_POOL_PT9);
    Ut_MemPtDelete(TEST_MEM_POOL_PT10);
    Ut_MemPtDelete(TEST_MEM_POOL_PT13);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         