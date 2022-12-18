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

#include "sre_base.h"
#include "sre_sys.h"
#include "sre_task.h"
#include "iCunit.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#define CACHE_MEM_SIZE            (OS_CACHE_LINE_SIZE*4)        /*��������ڴ��С*/
#define CACHE_TEST_SIZE           (OS_CACHE_LINE_SIZE*2)        /*ʵ�ʲ����ڴ��С*/
#define CACHE_MIN_SIZE            64                            /*Cache ����С����*/
#define CACHE_LOOP_CNT            (CACHE_TEST_SIZE/CACHE_MIN_SIZE) /*ʵ�ʲ�������������ٸ���С����*/

#define TEST_COUNT                40
#define CALC_COUNT                30
#define CACHE_INV_SIZE            (OS_CACHE_LINE_SIZE*4)

VOID uniWaitForAllCores(VOID)
{
    return;
}

UINT8 * m_CacheTestAddr = NULL;

UINT8 m_aucCacheRegion[0x8000];

typedef struct tagCacheTestRec
{
    UINT32 uwAddr;          /* ����ĵ�ַ   */
    UINT32 uwCheckVal;      /* �ȶԵ�ֵ     */
    UINT32 uwReadVal;       /* ��ȡ����ֵ   */
    UINT32 uwStep;          /* �׶���       */
}CACHE_REC_ST;

typedef struct tagOsTestRec
{
    CACHE_REC_ST stCacheTestRec;    /* cache���Խ����¼    */
}OSTESC_REC_ST;

typedef enum
{
    CACHE_NOT_WB = 1,   /* cache�ϵ�����Ϊ�������ݣ��ڴ����������Ϊ0xdd */
    CACHE_WB            /* cache�ϵ��������ڴ��������һ�� */
}CACHE_TEST_ATTR;

typedef struct tagSCJMP_CACHE
{
    UINT16 pat1 : 3;
    UINT16 a1   : 2;
    UINT16 A1   : 3;
    UINT16 pat2 : 8;
    UINT16 A2   : 13;
    UINT16 pat3 : 3;
    UINT16 a2   : 14;
    UINT16 pat4 : 2;
}SCCACHE_JMP_ST;

typedef struct tagSCJMP_OFFSET_CACHE
{
    UINT16 A2   : 13;
    UINT16 A1   : 3;
    UINT16 a2   : 14;
    UINT16 a1   : 2;
}SCCACHE_JMP_OFFSET_ST;

extern void uniWaitForAllCores();
extern UINT32 g_uwBgTsk;



/* cache�������Ĵ�С */
#define CACHE_BUFFER            0x8000   /*32K*/

/* cache ���Դ�С */
#define CACHE_TEST_SIZE_0       0x8000
#define CAHCE_TEST_SIZE_1       0xFFFFFFFF

/* cahce���Ե�д��ֵ */
#define CACHE_TEST_VALUE        0xdd
#define CACHE_TEST_VALUE1        0x5A


#if (OS_HARDWARE_PLATFORM == OS_SC3400)
#pragma section ".CACHE_TEST_DATA"  kind data

/* cache���Ի����� */
UINT8 g_acTestBuf[CACHE_BUFFER] = {1,1,1};
#pragma place g_acTestBuf ".CACHE_TEST_DATA"
#pragma align g_acTestBuf 32768
#endif

volatile UINT32 g_uwICacheTestGuard;


/* cache ����ʱȫ����ȫ�ֱ��� */
UINT32 g_uwIndex;
UINT8  g_ucTestData;
UINT32 g_uwNewFuncFlag = 0;

OSTESC_REC_ST g_stTestRec;


//#if (OS_HARDWARE_PLATFORM == OS_XTENSA2)
#if (OS_HARDWARE_PLATFORM == OS_CORTEX_A9)

//__attribute__((section(".shared.cache.data")))
UINT8 g_acTestBuf[CACHE_BUFFER] ;/* ����̬Pool�ڴ浥Ԫ����ʹ�÷���   */
//UT_TEST   UT�����������


UINT32 UT_CacheFun(UINT32 uwValue, UINT32 uwSize)
{
    UINT8 *puwAddr;
    UINTPTR uwSave = 0;
    /* �ر��ж� */
    uwSave = SRE_IntLock();

    /* ����Ч*/
    SRE_DCacheInv((VOID *)&g_acTestBuf[0], uwSize, 1);

    /* ��0xddд���ڴ��� */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
    }

    /* write 0x55 ro RAM */
    puwAddr = (UINT8*)&g_acTestBuf[0] + 0x80000000;
    memset((UINT8*)puwAddr,CACHE_TEST_VALUE1,uwSize);

    /* ��Ч*/
    SRE_DCacheInv((VOID *)&g_acTestBuf[0], uwSize, 1);

    /* ��TestBuf�ж����ݣ�����Ӧ��д�� */
    for (g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        if (g_acTestBuf[g_uwIndex] == CACHE_TEST_VALUE1)
        {
            continue;
        }
        else
        {
            g_stTestRec.stCacheTestRec.uwAddr = (UINT32)&g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwReadVal = g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwCheckVal = CACHE_TEST_VALUE1;
            g_stTestRec.stCacheTestRec.uwStep = CACHE_NOT_WB;
            ICUNIT_GOTO_EQUAL(2, 1, 2, EXIT);
        }
    }


    /* ��0xddд���ڴ��� */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
    }

    SRE_DCacheFlush((VOID *)&g_acTestBuf[0], uwSize, 1);

    /* test SRE_DCacheFlushInv �͵�ַ˫ӳ��*/
    for (g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex ++)
    {
        if (puwAddr[g_uwIndex] == CACHE_TEST_VALUE)
        {
            continue;
        }
        else
        {
            g_stTestRec.stCacheTestRec.uwAddr = (UINT32)&g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwReadVal = g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwCheckVal = CACHE_TEST_VALUE;
            g_stTestRec.stCacheTestRec.uwStep = CACHE_WB;
            ICUNIT_GOTO_EQUAL(2, 1, 2, EXIT);
        }
    }


    /* ��CACHE_TEST_VALUE1д���ڴ��� */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE1;
    }

    SRE_DCacheFlushInv((VOID *)&g_acTestBuf[0], uwSize, 1);

    /* test cacheWb �͵�ַ˫ӳ��*/
    for (g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex ++)
    {
        if (puwAddr[g_uwIndex] == CACHE_TEST_VALUE1)
        {
            continue;
        }
        else
        {
            g_stTestRec.stCacheTestRec.uwAddr = (UINT32)&g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwReadVal = g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwCheckVal = CACHE_TEST_VALUE1;
            g_stTestRec.stCacheTestRec.uwStep = CACHE_WB;
            ICUNIT_GOTO_EQUAL(2, 1, 2, EXIT);
        }
    }

EXIT:
    /* ���ж� */
    (VOID)SRE_IntRestore(uwSave);
    return ICUNIT_SUCCESS;
}
#endif

UINT32 UTest_CacheIncOld(VOID)
{
    g_uwNewFuncFlag = 1;
    return ICUNIT_SUCCESS;
}

UINT32 UTest_CacheIncNew(VOID)
{
    g_uwNewFuncFlag = 2;
    return ICUNIT_SUCCESS;
}

#if (OS_HARDWARE_PLATFORM == OS_SC3400)
UINT32 UT_CacheFun(UINT32 uwValue, UINT32 uwSize)
{
    /* �ر��ж� */
    UINTPTR uwSave;
    uwSave = SRE_IntLock();

    /* �ر�cache */
    uniDCacheDisable();

    /* ��0xddд���ڴ��� */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
    }

    /* ��cache */
    uniDCacheEnable();

    /* ����Чg_acTestBuf��Ӧ��cache�ռ� */
    SRE_DCacheInv((VOID *)&g_acTestBuf, uwSize, 1);

    /* ���ڴ�ӳ�䵽g_acTestBuf��cache�� */
    for(g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_ucTestData = g_acTestBuf[g_uwIndex];
    }

    /* ��������ȫ��д��cache�ϣ���ͬ����memory */
    g_ucTestData = uwValue;
    for (g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        g_acTestBuf[g_uwIndex] = g_ucTestData;
    }

    uniDCacheDisable();

    /* ��TestBuf�ж����ݣ�����Ӧ��д�� */
    for (g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex++)
    {
        if (g_acTestBuf[g_uwIndex] == CACHE_TEST_VALUE)
        {
            continue;
        }
        else
        {
            g_stTestRec.stCacheTestRec.uwAddr = (UINT32)&g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwReadVal = g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwCheckVal = CACHE_TEST_VALUE;
            g_stTestRec.stCacheTestRec.uwStep = CACHE_NOT_WB;
            ICUNIT_GOTO_EQUAL(2, 1, 2, EXIT);
        }
    }

    uniDCacheEnable();

    SRE_DCacheFlushInv((VOID *)&g_acTestBuf, uwSize, 1);

    uniDCacheDisable();

    for (g_uwIndex = 0; g_uwIndex < uwSize; g_uwIndex ++)
    {
        if (g_acTestBuf[g_uwIndex] == g_ucTestData)
        {
            continue;
        }
        else
        {
            g_stTestRec.stCacheTestRec.uwAddr = (UINT32)&g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwReadVal = g_acTestBuf[g_uwIndex];
            g_stTestRec.stCacheTestRec.uwCheckVal = uwValue;
            g_stTestRec.stCacheTestRec.uwStep = CACHE_WB;
            ICUNIT_GOTO_EQUAL(2, 1, 2, EXIT);
        }
    }

EXIT:
    /* ���ж� */
    (VOID)SRE_IntRestore(uwSave);
    return ICUNIT_SUCCESS;
}
#endif

UINT32 UT_MutiCoreTest(UINT32 uwData, UINT32 uwLen)
{
    UINT32 uwRet = ICUNIT_SUCCESS;

#if (OS_HARDWARE_PLATFORM == OS_SC3400)/* tensilica ������ʱ������*/
    uniWaitForAllCores();
    if(0 == SRE_GetCoreID())
#endif
    {
        uwRet = UT_CacheFun(uwData, uwLen);
        ICUNIT_ASSERT_EQUAL(uwRet, ICUNIT_SUCCESS, uwRet);
    }

/** ����Tensilica ƽ̨����ʱ���Ե���*/
#if (OS_HARDWARE_PLATFORM == OS_SC3400)
    uniWaitForAllCores();
    if(1 == SRE_GetCoreID())
    {
        uwRet = UT_CacheFun(uwData, uwLen);
        ICUNIT_ASSERT_EQUAL(uwRet, ICUNIT_SUCCESS, uwRet);
    }

    uniWaitForAllCores();
    if(2 == SRE_GetCoreID())
    {
        uwRet = UT_CacheFun(uwData, uwLen);
        ICUNIT_ASSERT_EQUAL(uwRet, ICUNIT_SUCCESS, uwRet);
    }
#endif

    return uwRet;
}

/**
*@test UT_uniCacheData_001
*-@tspec cache���ݲ��ԣ����Գ���32k����������0x00
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_001(VOID)
{
    return UT_MutiCoreTest(0x00, CACHE_TEST_SIZE_0);
}

/**
*@test UT_uniCacheData_002
*-@tspec cache���ݲ��ԣ����Գ���32k����������0xff
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_002(VOID)
{
    return UT_MutiCoreTest(0xff, CACHE_TEST_SIZE_0);
}

/**
*@test UT_uniCacheData_003
*-@tspec cache���ݲ��ԣ����Գ���32k����������0x55
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_003(VOID)
{
    return UT_MutiCoreTest(0x55, CACHE_TEST_SIZE_0);
}

/**
*@test UT_uniCacheData_004
*-@tspec cache���ݲ��ԣ����Գ���32k����������0xaa
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_004(VOID)
{
    return UT_MutiCoreTest(0xaa, CACHE_TEST_SIZE_0);
}

/**
*@test UT_uniCacheData_005
*-@tspec cache���ݲ��ԣ����Գ���32k����������0x33
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_005(VOID)
{
    return UT_MutiCoreTest(0x33, CACHE_TEST_SIZE_0);
}

/**
*@test UT_uniCacheData_006
*-@tspec cache���ݲ��ԣ����Գ���32k����������0xcc
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_006(VOID)
{
    return UT_MutiCoreTest(0xcc, CACHE_TEST_SIZE_0);
}

/**
*@test UT_uniCacheData_007
*-@tspec cache���ݲ��ԣ����Գ���32k����������0xf0
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_007(VOID)
{
    return UT_MutiCoreTest(0xf0, CACHE_TEST_SIZE_0);
}

/**
*@test UT_uniCacheData_008
*-@tspec cache���ݲ��ԣ����Գ���32k����������0x0f
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_008(VOID)
{
    return UT_MutiCoreTest(0x0f, CACHE_TEST_SIZE_0);
}

#if (OS_HARDWARE_PLATFORM == OS_SC3400)/* tensilica ������ʱ������*/
/**
*@test UT_uniCacheData_009
*-@tspec cache���ݲ��ԣ����Գ�������cache line����������0x55
*-@ttitle
*-@tbrief
*-#�ر�cache�������˽�0xddд���ڴ棬Ȼ���cache�����˽�0x55д��cache�У�
*-#�Ӻ˶�ȡ����Ϊ0xdd������Ϊ0x55�����˻�д����cache���Ӻ˶�ȡ������Ϊ0x55
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_009(VOID)
{
     //UINT32 uwRet = OS_FAIL;ԭ���������������߼��е����⡣
    UINT32 uwRet = ICUNIT_SUCCESS;
    UINTPTR uwSave = 0;
    /* �ر��ж� */
    uwSave = SRE_IntLock();

    /* �ر�cache */
    uniDCacheDisable();

    uniWaitForAllCores();
    if(0 == SRE_GetCoreID())
    {
        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
        }
    }
    /* ��cache */
    uniDCacheEnable();

    uniWaitForAllCores();
    if(0 != SRE_GetCoreID())
    {
        if(g_acTestBuf[0] != CACHE_TEST_VALUE)
        {
            return OS_FAIL;
        }
    }
    else
    {
        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            g_acTestBuf[g_uwIndex] = 0x55;
        }
    }

    uniWaitForAllCores();
    if(0 == SRE_GetCoreID())
    {
        SRE_DCacheFlush((VOID *)g_acTestBuf, CAHCE_TEST_SIZE_1, 1);
    }
    else
    {
        SRE_DCacheInv((VOID *)g_acTestBuf, CAHCE_TEST_SIZE_1, 1);
    }

    if(0 != SRE_GetCoreID())
    {
        if(g_acTestBuf[0] != 0x55)
        {
            return OS_FAIL;
        }
    }

    /* ���ж� */
    (VOID)SRE_IntRestore(uwSave);
    return uwRet;
}

/**
*@test UTest_uniCacheData_010
*-@tspec cache���ݲ��ԣ����Գ���256�ֽڣ���������0x55
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_010(VOID)
{
    //UINT32 uwRet = OS_FAIL;ԭ���������������߼��е����⡣
    UINT32 uwRet = ICUNIT_SUCCESS;
    UINT32 uwTestSize = 256;
    UINTPTR uwSave = 0;

    if(0 == SRE_GetCoreID())
    {
        /* �ر��ж� */
        uwSave = SRE_IntLock();

        /* �ر�cache */
        uniDCacheDisable();

        /* �ڴ��е�������ȫ��дΪ0xdd */
        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
        }

        /* ��cache */
        uniDCacheEnable();

        for(g_uwIndex = 0; g_uwIndex < uwTestSize; g_uwIndex++)
        {
            g_acTestBuf[g_uwIndex] = 0x55;
        }

        uniDCacheDisable();

        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            if(g_acTestBuf[g_uwIndex] != CACHE_TEST_VALUE)
            {
                asm(" debug");
                return OS_FAIL;
            }
        }

        uniDCacheEnable();

        SRE_DCacheFlushInv((VOID *)g_acTestBuf, uwTestSize, 1);

        uniDCacheDisable();

        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            if(g_uwIndex < uwTestSize)
            {
                if(g_acTestBuf[g_uwIndex] != 0x55)
                {
                    asm(" debug");
                    return OS_FAIL;
                }
            }
            else
            {
                if(g_acTestBuf[g_uwIndex] != CACHE_TEST_VALUE)
                {
                    asm(" debug");

                    return OS_FAIL;
                }
            }
        }

        /* ���ж� */
        SRE_IntRestore(uwSave);
    }

    return uwRet;
}

/**
*@test UTest_uniCacheData_011
*-@tspec cache���ݲ��ԣ����Գ���128�ֽڣ���������0x55
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_uniCacheData_011(VOID)
{
     //UINT32 uwRet = OS_FAIL;ԭ���������������߼��е����⡣
    UINT32 uwRet = ICUNIT_SUCCESS;
    UINT32 uwTestSize = 256;
    UINTPTR uwSave = 0;


    if(0 == SRE_GetCoreID())
    {
        /* �ر��ж� */
        uwSave = SRE_IntLock();

        /* �ر�cache */
        uniDCacheDisable();

        /* �ڴ��е�������ȫ��дΪ0xdd */
        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            g_acTestBuf[g_uwIndex] = CACHE_TEST_VALUE;
        }

        /* ��cache */
        uniDCacheEnable();

        for(g_uwIndex = 0; g_uwIndex < uwTestSize; g_uwIndex++)
        {
            g_acTestBuf[g_uwIndex] = 0x55;
        }

        uniDCacheDisable();

        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            if(g_acTestBuf[g_uwIndex] != CACHE_TEST_VALUE)
            {
                return OS_FAIL;
            }
        }

        uniDCacheEnable();

        SRE_DCacheFlushInv((VOID *)g_acTestBuf, uwTestSize, 1);

        uniDCacheDisable();

        for(g_uwIndex = 0; g_uwIndex < CACHE_BUFFER; g_uwIndex++)
        {
            if(g_uwIndex < uwTestSize)
            {
                if(g_acTestBuf[g_uwIndex] != 0x55)
                {
                    return OS_FAIL;
                }
            }
            else
            {
                if(g_acTestBuf[g_uwIndex] != CACHE_TEST_VALUE)
                {
                    return OS_FAIL;
                }
            }
        }

        /* ���ж� */
        SRE_IntRestore(uwSave);
    }
    return uwRet;
}
UINT32 UT_uniCacheInc_012(VOID)
{
    uniICacheDisable();
    uniICacheEnable();
    return 0;
}
#endif

#if (OS_HARDWARE_PLATFORM == OS_SC3400)
UINT32 UT_uniCacheInc_001(VOID)
{
    UINT32 uwOldAddr;
    UINT32 uwNewAddr;
    SCCACHE_JMP_ST   *pstRepIns;
    SCCACHE_JMP_OFFSET_ST *pstIncAddr;
    CHAR    acStoredInc[12];
    UINT16  acJmp[12];
    UINT32 uvIntSave;
    UINT32 uwIndex;

    if(0 == SRE_GetCoreID())
    {
        uvIntSave = SRE_IntLock();

        uwOldAddr = (UINT32)UTest_CacheIncOld;
        uwNewAddr = (UINT32)UTest_CacheIncNew;

        pstIncAddr = (SCCACHE_JMP_OFFSET_ST *)&uwNewAddr;
        pstRepIns = (SCCACHE_JMP_ST *)acJmp;


        for (uwIndex = 0; uwIndex < 12 ; uwIndex++)
        {
            acStoredInc[uwIndex] = ((CHAR *)uwOldAddr)[uwIndex];
        }

        pstRepIns->pat1 = 4;
        pstRepIns->pat2 = 49;
        pstRepIns->pat3 = 1;
        pstRepIns->pat4 = 2;
        pstRepIns->A1 = pstIncAddr->A1;
        pstRepIns->A2 = pstIncAddr->A2;
        pstRepIns->a1 = pstIncAddr->a1;
        pstRepIns->a2 = pstIncAddr->a2;

        memcpy((VOID *)uwOldAddr, (VOID *)pstRepIns, 12);

        SRE_ICacheInv((VOID *)uwOldAddr, 12, 1);

        UTest_CacheIncOld();

        if(2 != g_uwNewFuncFlag)
        {
            return OS_FAIL;
        }

        memcpy((VOID *)uwOldAddr, (VOID *)acStoredInc, 12);

        SRE_ICacheInv((VOID *)uwOldAddr, 12, 1);
        SRE_IntRestore(uvIntSave);
    }
    return ICUNIT_SUCCESS;
}
#endif


VOID UTTestCacheInit()
{
    UINT8 * pAddrBase = NULL;
    UINT32 uwTotalSize = 0;
    pAddrBase = &m_aucCacheRegion[0] + OS_CACHE_LINE_SIZE;
    m_CacheTestAddr = (UINT8 *)ALIGN((UINT32)pAddrBase, OS_CACHE_LINE_SIZE);

    if(0 == SRE_GetCoreID())
    {
        memset(pAddrBase, 0, CACHE_MEM_SIZE);
        SRE_DCacheFlushInv(pAddrBase, CACHE_MEM_SIZE, TRUE);
    }
    else
    {
        SRE_DCacheInv(pAddrBase, CACHE_MEM_SIZE, TRUE);
    }
    uniWaitForAllCores();

}
extern VOID SRE_DCacheEnable();
extern VOID SRE_ExampleFun();
extern VOID SRE_DCacheDisable();
extern VOID SRE_DCacheFlushAll(VOID);
extern VOID SRE_DCacheFlushInv(VOID *pAddr, UINT32 uwSize, BOOL bWait);
#define TEST_MAGICNUM 0x1234


/**
*@test UT_SRECacheData_001
*-@tspec cacheʹ�ܽ�ֹ����
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_SRECacheData_001(VOID)
{
    UINT32 auwTest[20] = {0};
    UINT32 uwLoop = 0;
    UINT32 uwTemp = 0;
    UINT32 uwReslt = 0;
    SRE_DCacheFlush(auwTest, 80, TRUE);
    for(uwLoop; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // ����Cache�еı���
    }
    SRE_DCacheDisable();
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);
    uwReslt = 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 20, uwReslt);
    SRE_DCacheEnable();

    return SRE_OK;
}

/**
*@test UT_SRECacheData_002
*-@tspec cache���ݲ���
*-@ttitle
*-@tbrief
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_SRECacheData_002(VOID)
{
    UINT32 auwTest[20] = {0};
    UINT32 uwLoop = 0;
    UINT32 uwTemp = 0;
    UINT32 uwReslt = 0;
    SRE_DCacheFlushAll();
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // ����Cache�еı���
    }
    SRE_DCacheInv(auwTest, 80, TRUE);
    uwReslt = 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);
    uwReslt = 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 20, uwReslt);

    return SRE_OK;

}

/**
*@test UT_SRECacheData_003
*-@tspec cache���ݲ���
*-@ttitle
*-@tbrief ��д��ЧSRE_DCacheFlushInv
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_SRECacheData_003(VOID)
{
    UINT32 auwTest[20] = {0};
    UINT32 uwLoop = 0;
    UINT32 uwTemp = 0;
    UINT32 uwReslt = 0;
    SRE_DCacheFlush(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // ����Cache�еı���
    }

    SRE_DCacheFlushInv(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 20, uwReslt);
    uwReslt = 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 20, uwReslt);

    return SRE_OK;
}

/**
*@test UT_SRECacheData_004
*-@tspec cache���ݲ���
*-@ttitle
*-@tbrief flushAll
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_SRECacheData_004(VOID)
{
    UINT32 auwTest[20] = {0};
    UINT32 uwLoop = 0;
    UINT32 uwTemp = 0;
    UINT32 uwReslt = 0;
    SRE_DCacheFlush(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // ����Cache�еı���
    }
    SRE_DCacheFlushAll();              //��Ч֮ǰ��ˢ������
    SRE_DCacheInv(auwTest, 80, TRUE);
    uwReslt= 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {

            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 20, uwReslt);
    uwReslt = 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // ����Cache�еı���
    }

    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 20, uwReslt);

    return SRE_OK;
}
/**
*@test UT_SRECacheData_005
*-@tspec cache���ݲ���
*-@ttitle
*-@tbrief ��ֹʹ�ܺ����cache����Ч֮�����ָ�ʹ��,�ٲ���cache����Ч֮���������flush
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_SRECacheData_005(VOID)
{
    SRE_DCacheFlushAll();
    UINT32 auwTest[20] = {0};
    UINT32 uwLoop = 0;
    UINT32 uwTemp = 0;
    UINT32 uwReslt = 0;
    SRE_DCacheFlush(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // ����Cache�еı���
    }
    SRE_DCacheDisable();
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);
    SRE_DCacheEnable();
    SRE_DCacheInv(auwTest, 80, TRUE);
    uwReslt = 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = 0;  //��ֵ
    }
    SRE_DCacheFlush(auwTest, 80, TRUE); //ˢ�븳ֵ����
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM; //����cache����
    }
    SRE_DCacheInv(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);
    uwReslt = 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;
    }
    SRE_DCacheFlush(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 20, uwReslt);

    return SRE_OK;
}

/**
*@test UT_SRECacheData_006
*-@tspec cache���ݲ���
*-@ttitle
*-@tbrief ��ֹʹ�ܺ����cache����Ч֮�����ָ�ʹ��,�ٲ���cache����Ч֮�����flushALL
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_SRECacheData_006(VOID)
{
    SRE_DCacheFlushAll();
    UINT32 auwTest[20] = {0};
    UINT32 uwLoop = 0;
    UINT32 uwTemp = 0;
    UINT32 uwReslt = 0;
    SRE_DCacheFlush(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // ����Cache�еı���
    }
    SRE_DCacheDisable();
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);
    SRE_DCacheEnable();
    SRE_DCacheInv(auwTest, 80, TRUE);
    uwReslt = 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = 0;  //��ֵ
    }
    SRE_DCacheFlush(auwTest, 80, TRUE); //ˢ�븳ֵ����
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM; //����cache����
    }
    SRE_DCacheInv(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);
    uwReslt = 0;
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;
    }
    SRE_DCacheFlushAll();
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {
            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 20, uwReslt);

    return SRE_OK;
}
/**
*@test UT_SRECacheData_007
*-@tspec cache���ݲ���
*-@ttitle
*-@tbrief �Ȳ������ԣ�����Ч����
*-@texpect
*-@tprior 1
*-@tremark ALL
 */
UINT32 UT_SRECacheData_007(VOID)
{
    UINT32 auwTest[20] = {0};
    UINT32 uwLoop = 0;
    UINT32 uwTemp = 0;
    UINT32 uwReslt = 0;
    SRE_DCacheFlush(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // ����Cache�еı���
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {

            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 20, uwReslt);

    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        uwTemp = auwTest[uwLoop];  // ����cache
    }
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        auwTest[uwLoop] = TEST_MAGICNUM;  // ����Cache�еı���
    }
    SRE_DCacheInv(auwTest, 80, TRUE);
    for(uwLoop = 0; uwLoop < 20; uwLoop++)
    {
        if(auwTest[uwLoop] == TEST_MAGICNUM)
        {

            uwReslt++;
        }
    }
    ICUNIT_ASSERT_EQUAL(uwReslt, 0, uwReslt);

    return SRE_OK;
}
void UT_uni_cache(void)
{
    iUINT32 uiSuiteId;
    UTTestCacheInit();
    SRE_DCacheEnable();


    TEST_ADD_SUITE(uiSuiteId, "UT_uni_cache");
#if 0
    TEST_ADD_CASE(UT_uniCacheData_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheData_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheData_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheData_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheData_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheData_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheData_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheData_008, uiSuiteId, Label_RUN);
#endif
    //UT_SRECacheData_001();
    TEST_ADD_CASE(UT_SRECacheData_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRECacheData_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRECacheData_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRECacheData_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRECacheData_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRECacheData_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRECacheData_007, uiSuiteId, Label_RUN);


#if (OS_HARDWARE_PLATFORM == OS_SC3400)/* tensilica ������ʱ������*/
    TEST_ADD_CASE(UT_uniCacheData_009, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheData_010, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheData_011, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheInc_012, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_uniCacheInc_001, uiSuiteId, Label_RUN);
#endif

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
